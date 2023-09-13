#include "DatabaseWorkerPool.h"
#include "ProducerConsumerQueue.h"
#include "Implementation/LoginDatabase.h"
#include "Implementation/CharacterDatabase.h"
#include "Implementation/WorldDatabase.h"
#include "Implementation/ArchiveDatabase.h"

template <class T>
DatabaseWorkerPool<T>::DatabaseWorkerPool()
    : _queue(new ProducerConsumerQueue<SQLOperation*>())
{
    WPFatal(mysql_thread_safe(), "Used MySQL library isn't thread-safe.");
    WPFatal(mysql_get_client_version() >= MIN_MYSQL_CLIENT_VERSION, "TrinityCore does not support MySQL versions below 5.1");
}

template <class T>
DatabaseWorkerPool<T>::~DatabaseWorkerPool()
{
    _queue->Cancel();
}

template <class T>
bool DatabaseWorkerPool<T>::Open(const std::string& infoString, uint8 async_threads, uint8 synch_threads)
{
    bool res = true;
    _connectionInfo = MySQLConnectionInfo(infoString);

    TC_LOG_INFO("sql.driver", "Opening DatabasePool '%s'. Asynchronous connections: %u, synchronous connections: %u.",
        GetDatabaseName(), async_threads, synch_threads);

    //! Open asynchronous connections (delayed operations)
    for (uint8 i = 0; i < async_threads; ++i)
    {
        T* t = new T(_connectionInfo, CONNECTION_ASYNC);
        res &= t->Open();
        _workers.push_back(new DatabaseWorker(t));
    }

    //! Open synchronous connections (direct, blocking operations)
    for (uint8 i = 0; i < synch_threads; ++i)
    {
        T* t = new T(_connectionInfo, CONNECTION_SYNCH);
        res &= t->Open();
        _connections.push_back(t);
    }

    if (res)
        TC_LOG_INFO("sql.driver", "DatabasePool '%s' opened successfully. %u total connections running.", GetDatabaseName(),
            (_connections.size() + _workers.size()));
    else
        TC_LOG_ERROR("sql.driver", "DatabasePool %s NOT opened. There were errors opening the MySQL connections. Check your SQLDriverLogFile "
            "for specific errors.", GetDatabaseName());
    return res;
}

template <class T>
void DatabaseWorkerPool<T>::Close()
{
    TC_LOG_INFO("sql.driver", "Closing down DatabasePool '%s'.", GetDatabaseName());

    //! Shuts down delaythreads for this connection pool by underlying deactivate().
    //! The next dequeue attempt in the worker thread tasks will result in an error,
    //! ultimately ending the worker thread task.
    for (auto&& worker : _workers)
        delete worker;

    TC_LOG_INFO("sql.driver", "Asynchronous connections on DatabasePool '%s' terminated. Proceeding with synchronous connections.",
        GetDatabaseName());

    //! Shut down the synchronous connections
    //! There's no need for locking the connection, because DatabaseWorkerPool<>::Close
    //! should only be called after any other thread tasks in the core have exited,
    //! meaning there can be no concurrent access at this point.
    for (auto&& conn : _connections)
        delete conn;

    _connections.clear();

    TC_LOG_INFO("sql.driver", "All connections on DatabasePool '%s' closed.", GetDatabaseName());
}

template <class T>
void DatabaseWorkerPool<T>::Execute(const char* sql)
{
    if (!sql)
        return;

    BasicStatementTask* task = new BasicStatementTask(sql);
    Enqueue(task);
}

template <class T>
void DatabaseWorkerPool<T>::PExecute(const char* sql, ...)
{
    if (!sql)
        return;

    va_list ap;
    char szQuery[MAX_QUERY_LEN];
    va_start(ap, sql);
    vsnprintf(szQuery, MAX_QUERY_LEN, sql, ap);
    va_end(ap);

    Execute(szQuery);
}

template <class T>
void DatabaseWorkerPool<T>::Execute(PreparedStatement* stmt, DBConnection connIndex)
{
    PreparedStatementTask* task = new PreparedStatementTask(stmt);
    Enqueue(task, connIndex);	
}

template <class T>
void DatabaseWorkerPool<T>::DirectExecute(const char* sql)
{
    if (!sql)
        return;

    T* t = GetFreeConnection();
    t->Execute(sql);
    t->Unlock();
}

template <class T>
void DatabaseWorkerPool<T>::DirectPExecute(const char* sql, ...)
{
    if (!sql)
        return;

    va_list ap;
    char szQuery[MAX_QUERY_LEN];
    va_start(ap, sql);
    vsnprintf(szQuery, MAX_QUERY_LEN, sql, ap);
    va_end(ap);

    return DirectExecute(szQuery);
}

template <class T>
void DatabaseWorkerPool<T>::DirectExecute(PreparedStatement* stmt)
{
    T* t = GetFreeConnection();
    t->Execute(stmt);
    t->Unlock();

    //! Delete proxy-class. Not needed anymore
    delete stmt;
}

template <class T>
QueryResult DatabaseWorkerPool<T>::Query(const char* sql, T* conn)
{
    if (!conn)
        conn = GetFreeConnection();

    ResultSet* result = conn->Query(sql);
    conn->Unlock();
    if (!result || !result->GetRowCount())
    {
        delete result;
        return QueryResult(NULL);
    }

    result->NextRow();
    return QueryResult(result);
}

template <class T>
QueryResult DatabaseWorkerPool<T>::PQuery(const char* sql, T* conn, ...)
{
    if (!sql)
        return QueryResult(NULL);

    va_list ap;
    char szQuery[MAX_QUERY_LEN];
    va_start(ap, conn);
    vsnprintf(szQuery, MAX_QUERY_LEN, sql, ap);
    va_end(ap);

    return Query(szQuery, conn);
}

template <class T>
QueryResult DatabaseWorkerPool<T>::PQuery(const char* sql, ...)
{
    if (!sql)
        return QueryResult(NULL);

    va_list ap;
    char szQuery[MAX_QUERY_LEN];
    va_start(ap, sql);
    vsnprintf(szQuery, MAX_QUERY_LEN, sql, ap);
    va_end(ap);

    return Query(szQuery);	
}

template <class T>
PreparedQueryResult DatabaseWorkerPool<T>::Query(PreparedStatement* stmt)
{
    T* t = GetFreeConnection();
    PreparedResultSet* ret = t->Query(stmt);
    t->Unlock();

    //! Delete proxy-class. Not needed anymore
    delete stmt;

    if (!ret || !ret->GetRowCount())
    {
        delete ret;
        return PreparedQueryResult(NULL);
    }

    return PreparedQueryResult(ret);	
}

template <class T>
QueryResultFuture DatabaseWorkerPool<T>::AsyncQuery(const char* sql)
{
    QueryResultFuture res;
    BasicStatementTask* task = new BasicStatementTask(sql, res);
    Enqueue(task);
    return res;         //! Actual return value has no use yet
}

template <class T>
QueryResultFuture DatabaseWorkerPool<T>::AsyncPQuery(const char* sql, ...)
{
    va_list ap;
    char szQuery[MAX_QUERY_LEN];
    va_start(ap, sql);
    vsnprintf(szQuery, MAX_QUERY_LEN, sql, ap);
    va_end(ap);

    return AsyncQuery(szQuery);    
}

template <class T>
PreparedQueryResultFuture DatabaseWorkerPool<T>::AsyncQuery(PreparedStatement* stmt)
{
    PreparedQueryResultFuture res;
    PreparedStatementTask* task = new PreparedStatementTask(stmt, res);
    Enqueue(task);
    return res;    
}

template <class T>
QueryResultHolderFuture DatabaseWorkerPool<T>::DelayQueryHolder(SQLQueryHolder* holder)
{
    QueryResultHolderFuture res;
    SQLQueryHolderTask* task = new SQLQueryHolderTask(holder, res);
    Enqueue(task);
    return res;     //! Fool compiler, has no use yet    
}

template <class T>
SQLTransaction DatabaseWorkerPool<T>::BeginTransaction()
{
    return SQLTransaction(new Transaction);
}

template <class T>
void DatabaseWorkerPool<T>::CommitTransaction(SQLTransaction transaction, DBConnection connIndex)
{
    #ifdef TRINITY_DEBUG
    //! Only analyze transaction weaknesses in Debug mode.
    //! Ideally we catch the faults in Debug mode and then correct them,
    //! so there's no need to waste these CPU cycles in Release mode.
    switch (transaction->GetSize())
    {
        case 0:
            TC_LOG_DEBUG("sql.driver", "Transaction contains 0 queries. Not executing.");
            return;
        case 1:
            TC_LOG_DEBUG("sql.driver", "Warning: Transaction only holds 1 query, consider removing Transaction context in code.");
            break;
        default:
            break;
    }
    #endif // TRINITY_DEBUG

    Enqueue(new TransactionTask(std::move(transaction)), connIndex);
}

template <class T>
void DatabaseWorkerPool<T>::DirectCommitTransaction(SQLTransaction& transaction)
{
    T* con = GetFreeConnection();
    if (con->ExecuteTransaction(transaction))
    {
        con->Unlock();      // OK, operation succesful
        return;
    }

    //! Handle MySQL Errno 1213 without extending deadlock to the core itself
    /// @todo More elegant way
    if (con->GetLastError() == 1213)
    {
        uint8 loopBreaker = 5;
        for (uint8 i = 0; i < loopBreaker; ++i)
        {
            if (con->ExecuteTransaction(transaction))
                break;
        }
    }

    //! Clean up now.
    transaction->Cleanup();

    con->Unlock();    
}

template <class T>
void DatabaseWorkerPool<T>::ExecuteOrAppend(SQLTransaction& trans, PreparedStatement* stmt, DBConnection connIndex)
{
    if (!trans)
        Execute(stmt, connIndex);
    else
        trans->Append(stmt);    
}

template <class T>
void DatabaseWorkerPool<T>::ExecuteOrAppend(SQLTransaction& trans, const char* sql)
{
    if (!trans)
        Execute(sql);
    else
        trans->Append(sql);    
}

template <class T>
PreparedStatement* DatabaseWorkerPool<T>::GetPreparedStatement(uint32 index)
{
    return new PreparedStatement(index);
}


template <class T>
void DatabaseWorkerPool<T>::EscapeString(std::string& str)
{
    if (str.empty())
        return;

    char* buf = new char[str.size()*2+1];
    EscapeString(buf, str.c_str(), str.size());
    str = buf;
    delete[] buf;	
}

template <class T>
void DatabaseWorkerPool<T>::KeepAlive()
{
    //! Ping synchronous connections
    for (auto&& conn : _connections)
    {
        if (conn->LockIfReady())
        {
            conn->Ping();
            conn->Unlock();
        }
    }

    //! Assuming all worker threads are free, every worker thread will receive 1 ping operation request
    //! If one or more worker threads are busy, the ping operations will not be split evenly, but this doesn't matter
    //! as the sole purpose is to prevent connections from idling.
    for (auto&& worker : _workers)
        worker->Enqueue(new PingOperation());	
}

template <class T>
Task<QueryResult>* DatabaseWorkerPool<T>::Async(char const* sql, ...)
{
    va_list ap;
    char szQuery[MAX_QUERY_LEN];
    va_start(ap, sql);
    vsnprintf(szQuery, MAX_QUERY_LEN, sql, ap);
    va_end(ap);

    QueryResultFuture res;
    WaitResultTask<QueryResult>* wait = new WaitResultTask<QueryResult>(res);
    Enqueue(new BasicStatementTask(szQuery, res));
    return wait;	
}

template <class T>
Task<PreparedQueryResult>* DatabaseWorkerPool<T>::Async(PreparedStatement* stmt, DBConnection connIndex)
{
    PreparedQueryResultFuture res;
    WaitResultTask<PreparedQueryResult>* wait = new WaitResultTask<PreparedQueryResult>(res);
    Enqueue(new PreparedStatementTask(stmt, res), connIndex);
    return wait;
}

template <class T>
Task<SQLQueryHolder*>* DatabaseWorkerPool<T>::Async(SQLQueryHolder* holder)
{
    QueryResultHolderFuture res;
    WaitResultTask<SQLQueryHolder*>* wait = new WaitResultTask<SQLQueryHolder*>(res);
    Enqueue(new SQLQueryHolderTask(holder, res));
    return wait;	
}

template <class T>
Task<bool>* DatabaseWorkerPool<T>::Async(SQLTransaction& trans, DBConnection connIndex)
{
    Task<bool>* next = new Task<bool>();
    Enqueue(new TransactionTask(std::move(trans), next), connIndex);
    return next;	
}

template <class T>
Task<bool>* DatabaseWorkerPool<T>::SafeAsync(SQLTransaction& trans)
{
    Task<bool>* next = new Task<bool>();
    Enqueue(new SafeTransactionTask(std::move(trans), next));
    return next;	
}

template <class T>
unsigned long DatabaseWorkerPool<T>::EscapeString(char *to, const char *from, unsigned long length)
{
    if (!to || !from || !length)
        return 0;

    return mysql_real_escape_string(_connections[0]->GetHandle(), to, from, length);	
}


template <class T>
void DatabaseWorkerPool<T>::Enqueue(SQLOperation* op, DBConnection connIndex)
{
    int32 i = int32(connIndex);
    if (i < 0)
        GetWorker()->Enqueue(op);
    else
    {
        int32 n = _workers.size() - 1 - i;
        if (n < 0)  // Not enouth threads. Use the last one
            _workers.back()->Enqueue(op);
        else
            _workers[n]->Enqueue(op);
    }
}

template <class T>
T* DatabaseWorkerPool<T>::GetFreeConnection()
{
    while (true)
    {
        //! Block forever until a connection is free
        for (auto&& conn : _connections)
        {
            //! Must be matched with t->Unlock() or you will get deadlocks
            if (conn->LockIfReady())
                return conn;
        }
    }

    std::abort();	
}

template <class T>
DatabaseWorker* DatabaseWorkerPool<T>::GetWorker()
{
    int32 min = 0;
    DatabaseWorker* worker = _workers.front();
    for (auto&& iter : _workers)
    {
        int32 c = iter->Count();
        if (!c)
            return iter;

        if (c < min)
        {
            min = c;
            worker = iter;
        }
    }
    return worker;	
}

template <class T>
char const* DatabaseWorkerPool<T>::GetDatabaseName() const
{
	return _connectionInfo.database.c_str();
}

template class DatabaseWorkerPool<LoginDatabaseConnection>;
template class DatabaseWorkerPool<WorldDatabaseConnection>;
template class DatabaseWorkerPool<CharacterDatabaseConnection>;
template class DatabaseWorkerPool<ArchiveDatabaseConnection>;