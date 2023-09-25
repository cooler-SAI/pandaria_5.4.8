/*
* This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "TaskMgr.h"
#include "Task.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "Optional.h"

class ThreadPool
{
    typedef std::unique_ptr<boost::asio::io_service::work> worker;
    typedef boost::asio::io_service service;
    typedef boost::thread_group pool;
public:
    ThreadPool(size_t threads)
        : _worker(new worker::element_type{ _service })
    {
        while (threads--)
        {
            auto worker = boost::bind(&service::run, &(this->_service));
            _pool.add_thread(new boost::thread(worker));
        }
    }

    void Stop()
    {
        _worker.reset();
        _pool.join_all();
        _service.stop();
    }

    template<class F>
    void Enqueue(F f)
    {
        _service.post(f);
    }

private:
    service _service;
    worker  _worker;
    pool    _pool;
};

//ThreadPool TaskMgr::_pool{ 1 };
std::unique_ptr<ThreadPool> TaskMgr::_pool(new ThreadPool{1});

// Yes, this must be here.
TaskMgr::~TaskMgr()
{
}

TaskMgr* TaskMgr::Default()
{
    static TaskMgr _default;
    return &_default;
}

void TaskMgr::Update()
{
    TaskObject task;
    while (_queue.next(task))
        _tasks.push_back(task);

    if (_tasks.empty())
        return;

    using namespace std::chrono;
    steady_clock::time_point end = steady_clock::now() + _max;

    auto it = _tasks.begin();

    do
    {
        if (!(*it)->Update()) // even if task canceled, it is not in process, we can delete it now
            _tasks.erase(it++);
        else
            ++it;
    } while (it != _tasks.end() && steady_clock::now() < end);
}

void TaskMgr::ScheduleInvocation(std::function<void()> func)
{
    _queue.add(TaskObject{ new CallbackTask(std::move(func)) });
}

void TaskMgr::ScheduleInvocation(TaskBase* task)
{
    _queue.add(TaskObject{ task });
}

void Schedulable::NewAction(TaskBase* task)
{
    CancelationToken tok = task->GetToken();
    for (auto&& token : _tokens)
    {
        if (token->IsExpired())
        {
            token = std::move(tok);
            return;
        }
    }

    _tokens.push_back(std::move(tok));
}

void TaskMgr::Async(std::function<void()> func)
{
    _pool->Enqueue(func);
}

void TaskMgr::Stop()
{
    _pool->Stop();
}
