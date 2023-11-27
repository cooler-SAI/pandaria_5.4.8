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

/// \addtogroup Trinityd Trinity Daemon
/// @{
/// \file

#include <openssl/opensslv.h>
#include <openssl/crypto.h>

#include "Common.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "DatabaseLoader.h"
#include "DatabaseWorkerPool.h"
#include "Implementation/LoginDatabase.h"
#include "Implementation/CharacterDatabase.h"
#include "Implementation/WorldDatabase.h"



#include "Master.h"

#include "AppenderDB.h"
#include "AsyncAcceptor.h"
#include "Banner.h"
#include "BigNumber.h"
#include "CliRunnable.h"
#include "DeadlineTimer.h"
#include "GitRevision.h"
#include "IoContext.h"
#include "Log.h"
#include "MySQLThreading.h"
#include "OpenSSLCrypto.h"
#include "ProcessPriority.h"
#include "RASession.h"
#include "RealmList.h"
#include "Resolver.h"
#include "ScriptLoader.h"
#include "ScriptMgr.h"
#include "TCSoap.h"
#include "ThreadPool.h"
#include "World.h"

#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/program_options.hpp>

#ifndef _TRINITY_CORE_CONFIG
# define _TRINITY_CORE_CONFIG  "worldserver.conf"
#endif

#ifdef _WIN32
#include "ServiceWin32.h"
char serviceName[] = "worldserver";
char serviceLongName[] = "SkyFire world service";
char serviceDescription[] = "SkyFire World of Warcraft emulator world service";
/*
 * -1 - not in service mode
 *  0 - stopped
 *  1 - running
 *  2 - paused
 */
int m_ServiceStatus = -1;
#endif

RealmNameMap realmNameStore;

class FreezeDetector
{
    public:
    FreezeDetector(Trinity::Asio::IoContext& ioContext, uint32 maxCoreStuckTime)
        : _timer(ioContext), _worldLoopCounter(0), _lastChangeMsTime(getMSTime()), _maxCoreStuckTimeInMs(maxCoreStuckTime) { }

        static void Start(std::shared_ptr<FreezeDetector> const& freezeDetector)
        {
            freezeDetector->_timer.expires_from_now(boost::posix_time::seconds(5));
            freezeDetector->_timer.async_wait([freezeDetectorRef = std::weak_ptr<FreezeDetector>(freezeDetector)](boost::system::error_code const& error)
            {
                return Handler(freezeDetectorRef, error);
            });
        }

        static void Handler(std::weak_ptr<FreezeDetector> freezeDetectorRef, boost::system::error_code const& error);

    private:
        Trinity::Asio::DeadlineTimer _timer;
        uint32 _worldLoopCounter;
        uint32 _lastChangeMsTime;
        uint32 _maxCoreStuckTimeInMs;
};

void SignalHandler(boost::system::error_code const& error, int signalNumber);
AsyncAcceptor* StartRaSocketAcceptor(Trinity::Asio::IoContext& ioContext);
bool StartDB();
void StopDB();
void WorldUpdateLoop();
void ClearOnlineAccounts();
void ShutdownCLIThread(std::thread* cliThread);
//bool LoadRealmInfo(Trinity::Asio::IoContext& ioContext);

/// Print out the usage string for this program on the console.
void usage(const char* prog)
{
    printf("Usage:\n");
    printf(" %s [<options>]\n", prog);
    printf("    -c config_file           use config_file as configuration file\n");
#ifdef _WIN32
    printf("    Running as service functions:\n");
    printf("    --service                run as service\n");
    printf("    -s install               install service\n");
    printf("    -s uninstall             uninstall service\n");
#endif
}

/// Launch the Trinity server
extern int main(int argc, char** argv)
{
    // Trinity::Impl::CurrentServerProcessHolder::_type = SERVER_PROCESS_WORLDSERVER;
    signal(SIGABRT, &Trinity::AbortHandler);    

    ///- Command line parsing to get the configuration file name
    char const* cfg_file = _TRINITY_CORE_CONFIG;
    int c = 1;
    while (c < argc)
    {
        if (!strcmp(argv[c], "-c"))
        {
            if (++c >= argc)
            {
                printf("Runtime-Error: -c option requires an input argument");
                usage(argv[0]);
                return 1;
            }
            else
                cfg_file = argv[c];
        }

        #ifdef _WIN32
        if (strcmp(argv[c], "-s") == 0) // Services
        {
            if (++c >= argc)
            {
                printf("Runtime-Error: -s option requires an input argument");
                usage(argv[0]);
                return 1;
            }

            if (strcmp(argv[c], "install") == 0)
            {
                if (WinServiceInstall())
                    printf("Installing service\n");
                return 1;
            }
            else if (strcmp(argv[c], "uninstall") == 0)
            {
                if (WinServiceUninstall())
                    printf("Uninstalling service\n");
                return 1;
            }
            else
            {
                printf("Runtime-Error: unsupported option %s", argv[c]);
                usage(argv[0]);
                return 1;
            }
        }

        if (strcmp(argv[c], "--service") == 0)
            WinServiceRun();
        #endif
        ++c;
    }

    std::string configError;
    if (!sConfigMgr->LoadInitial(cfg_file,std::vector<std::string>(argv, argv + argc),configError))
    {
        printf("Invalid or missing configuration file : %s\n", cfg_file);
        printf("Verify that the file exists and has \'[worldserver]' written in the top of the file!\n");
        printf("Error in config file: %s\n", configError.c_str());
        return 1;
    }
    
    //std::vector<std::string> overriddenKeys = sConfigMgr->OverrideWithEnvVariablesIfAny();

    std::shared_ptr<Trinity::Asio::IoContext> ioContext = std::make_shared<Trinity::Asio::IoContext>();

    sLog->RegisterAppender<AppenderDB>();
    // If logs are supposed to be handled async then we need to pass the IoContext into the Log singleton
    sLog->Initialize(sConfigMgr->GetBoolDefault("Log.Async.Enable", false) ? ioContext.get() : nullptr);

    Trinity::Banner::Show("worldserver-daemon",
        [](char const* text)
        {
            TC_LOG_INFO("server.worldserver", "%s", text);
        },
        []()
        {
            TC_LOG_INFO("server.worldserver", "Using configuration file %s.", sConfigMgr->GetFilename().c_str());
            TC_LOG_INFO("server.worldserver", "Using SSL version: %s (library: %s)", OPENSSL_VERSION_TEXT, OpenSSL_version(OPENSSL_VERSION));
            TC_LOG_INFO("server.worldserver", "Using Boost version: %i.%i.%i", BOOST_VERSION / 100000, BOOST_VERSION / 100 % 1000, BOOST_VERSION % 100);
        }
    );

    OpenSSLCrypto::threadsSetup(boost::dll::program_location().remove_filename());

    std::shared_ptr<void> opensslHandle(nullptr, [](void*) { OpenSSLCrypto::threadsCleanup(); });

    // Seed the OpenSSL's PRNG here.
    // That way it won't auto-seed when calling BigNumber::SetRand and slow down the first world login
    BigNumber seed1;
    seed1.SetRand(16 * 8);

    /// worldserver PID file creation
    std::string pidFile = sConfigMgr->GetStringDefault("PidFile", "");
    if (!pidFile.empty())
    {
        if (uint32 pid = CreatePIDFile(pidFile))
            TC_LOG_INFO("server.worldserver", "Daemon PID: %u\n", pid);
        else
        {
            TC_LOG_ERROR("server.worldserver", "Cannot create PID file %s.\n", pidFile.c_str());
            return 1;
        }
    }

    // Set signal handlers (this must be done before starting IoContext threads, because otherwise they would unblock and exit)
    boost::asio::signal_set signals(*ioContext, SIGINT, SIGTERM);
#if TRINITY_PLATFORM == TRINITY_PLATFORM_WINDOWS
    signals.add(SIGBREAK);
#endif
    signals.async_wait(SignalHandler);

    // Start the Boost based thread pool
    int numThreads = sConfigMgr->GetIntDefault("ThreadPool", 1);
    if (numThreads < 1)
        numThreads = 1;

    std::shared_ptr<Trinity::ThreadPool> threadPool = std::make_shared<Trinity::ThreadPool>(numThreads);

    for (int i = 0; i < numThreads; ++i)
        threadPool->PostWork([ioContext]() { ioContext->run(); });

    std::shared_ptr<void> ioContextStopHandle(nullptr, [ioContext](void*) { ioContext->stop(); });

    // Set process priority according to configuration settings
    SetProcessPriority("server.worldserver", sConfigMgr->GetIntDefault(CONFIG_PROCESSOR_AFFINITY, 0), sConfigMgr->GetBoolDefault(CONFIG_HIGH_PRIORITY, false));

    // Start the databases
    if (!StartDB())
        return 1;

    std::shared_ptr<void> dbHandle(nullptr, [](void*) { StopDB(); });

    // set server offline (not connectable)
    LoginDatabase.DirectPExecute("UPDATE realmlist SET flag = (flag & ~%u) | %u WHERE id = '%d'", REALM_FLAG_OFFLINE, REALM_FLAG_INVALID, realm.Id.Realm);

    //LoadRealmInfo(*ioContext);
    sMaster->LoadRealmInfo();

    //sScriptMgr->SetScriptLoader(AddScripts);
    sScriptMgr->SetLoader(AddScripts);
    std::shared_ptr<void> sScriptMgrHandle(nullptr, [](void*)
    {
        sScriptMgr->Unload();
        //sScriptReloadMgr->Unload();
    });

    // Initialize the World
    //sSecretMgr->Initialize();
    sWorld->SetInitialWorldSettings();

    // Start the Remote Access port (acceptor) if enabled
    std::unique_ptr<AsyncAcceptor> raAcceptor;
    if (sConfigMgr->GetBoolDefault("Ra.Enable", false))
        raAcceptor.reset(StartRaSocketAcceptor(*ioContext));

    // Start soap serving thread if enabled
    std::shared_ptr<std::thread> soapThread;
    if (sConfigMgr->GetBoolDefault("SOAP.Enabled", false))
    {
        soapThread.reset(new std::thread(TCSoapThread, sConfigMgr->GetStringDefault("SOAP.IP", "127.0.0.1"), uint16(sConfigMgr->GetIntDefault("SOAP.Port", 7878))),
            [](std::thread* thr)
        {
            thr->join();
            delete thr;
        });
    }

    // Start the freeze check callback cycle in 5 seconds (cycle itself is 1 sec)
    std::shared_ptr<FreezeDetector> freezeDetector;
    if (int coreStuckTime = sConfigMgr->GetIntDefault("MaxCoreStuckTime", 60))
    {
        freezeDetector = std::make_shared<FreezeDetector>(*ioContext, coreStuckTime * 1000);
        FreezeDetector::Start(freezeDetector);
        TC_LOG_INFO("server.worldserver", "Starting up anti-freeze thread (%u seconds max stuck time)...", coreStuckTime);
    }

    // Launch CliRunnable thread
    std::shared_ptr<std::thread> cliThread;
#ifdef _WIN32
    if (sConfigMgr->GetBoolDefault("Console.Enable", true) && (m_ServiceStatus == -1)/* need disable console in service mode*/)
#else
    if (sConfigMgr->GetBoolDefault("Console.Enable", true))
#endif
    {
        cliThread.reset(new std::thread(CliThread), &ShutdownCLIThread);
    }

    //WorldUpdateLoop();

    ///- and run the 'Master'
    /// @todo Why do we need this 'Master'? Can't all of this be in the Main as for Realmd?
    int ret = sMaster->Run();

    // at sMaster return function exist with codes
    // 0 - normal shutdown
    // 1 - shutdown at error
    // 2 - restart command used, this code can be used by restarter for restart Trinityd

    // Shutdown starts here
    ioContextStopHandle.reset();

    threadPool.reset();

    sLog->SetSynchronous();

    sScriptMgr->OnShutdown();

    // set server offline
    LoginDatabase.DirectPExecute("UPDATE realmlist SET flag = flag | %u WHERE id = '%d'", REALM_FLAG_OFFLINE, realm.Id.Realm);

    TC_LOG_INFO("server.worldserver", "Halting process...");

    return ret;
}

/// @}

void ShutdownCLIThread(std::thread* cliThread)
{
    if (cliThread != nullptr)
    {
#ifdef _WIN32
        // First try to cancel any I/O in the CLI thread
        if (!CancelSynchronousIo(cliThread->native_handle()))
        {
            // if CancelSynchronousIo() fails, print the error and try with old way
            DWORD errorCode = GetLastError();
            LPCSTR errorBuffer;

            DWORD formatReturnCode = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
                                                   nullptr, errorCode, 0, (LPTSTR)&errorBuffer, 0, nullptr);
            if (!formatReturnCode)
                errorBuffer = "Unknown error";

            TC_LOG_DEBUG("server.worldserver", "Error cancelling I/O of CliThread, error code %u, detail: %s", uint32(errorCode), errorBuffer);

            if (!formatReturnCode)
                LocalFree((LPSTR)errorBuffer);

            // send keyboard input to safely unblock the CLI thread
            INPUT_RECORD b[4];
            HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
            b[0].EventType = KEY_EVENT;
            b[0].Event.KeyEvent.bKeyDown = TRUE;
            b[0].Event.KeyEvent.uChar.AsciiChar = 'X';
            b[0].Event.KeyEvent.wVirtualKeyCode = 'X';
            b[0].Event.KeyEvent.wRepeatCount = 1;

            b[1].EventType = KEY_EVENT;
            b[1].Event.KeyEvent.bKeyDown = FALSE;
            b[1].Event.KeyEvent.uChar.AsciiChar = 'X';
            b[1].Event.KeyEvent.wVirtualKeyCode = 'X';
            b[1].Event.KeyEvent.wRepeatCount = 1;

            b[2].EventType = KEY_EVENT;
            b[2].Event.KeyEvent.bKeyDown = TRUE;
            b[2].Event.KeyEvent.dwControlKeyState = 0;
            b[2].Event.KeyEvent.uChar.AsciiChar = '\r';
            b[2].Event.KeyEvent.wVirtualKeyCode = VK_RETURN;
            b[2].Event.KeyEvent.wRepeatCount = 1;
            b[2].Event.KeyEvent.wVirtualScanCode = 0x1c;

            b[3].EventType = KEY_EVENT;
            b[3].Event.KeyEvent.bKeyDown = FALSE;
            b[3].Event.KeyEvent.dwControlKeyState = 0;
            b[3].Event.KeyEvent.uChar.AsciiChar = '\r';
            b[3].Event.KeyEvent.wVirtualKeyCode = VK_RETURN;
            b[3].Event.KeyEvent.wVirtualScanCode = 0x1c;
            b[3].Event.KeyEvent.wRepeatCount = 1;
            DWORD numb;
            WriteConsoleInput(hStdIn, b, 4, &numb);
        }
#endif
        cliThread->join();
        delete cliThread;
    }
}

void WorldUpdateLoop()
{
    uint32 minUpdateDiff = uint32(sConfigMgr->GetIntDefault("MinWorldUpdateTime", 1));
    uint32 realCurrTime = 0;
    uint32 realPrevTime = getMSTime();

    uint32 maxCoreStuckTime = uint32(sConfigMgr->GetIntDefault("MaxCoreStuckTime", 60)) * 1000;
    uint32 halfMaxCoreStuckTime = maxCoreStuckTime / 2;
    if (!halfMaxCoreStuckTime)
        halfMaxCoreStuckTime = std::numeric_limits<uint32>::max();

    LoginDatabase.WarnAboutSyncQueries(true);
    CharacterDatabase.WarnAboutSyncQueries(true);
    WorldDatabase.WarnAboutSyncQueries(true);

    ///- While we have not World::m_stopEvent, update the world
    while (!World::IsStopped())
    {
        ++World::m_worldLoopCounter;
        realCurrTime = getMSTime();

        uint32 diff = getMSTimeDiff(realPrevTime, realCurrTime);
        if (diff < minUpdateDiff)
        {
            uint32 sleepTime = minUpdateDiff - diff;
            if (sleepTime >= halfMaxCoreStuckTime)
                TC_LOG_ERROR("server.worldserver", "WorldUpdateLoop() waiting for %u ms with MaxCoreStuckTime set to %u ms", sleepTime, maxCoreStuckTime);
            // sleep until enough time passes that we can update all timers
            std::this_thread::sleep_for(Milliseconds(sleepTime));
            continue;
        }

        sWorld->Update(diff);
        realPrevTime = realCurrTime;

#ifdef _WIN32
        if (m_ServiceStatus == 0)
            World::StopNow(SHUTDOWN_EXIT_CODE);

        while (m_ServiceStatus == 2)
            Sleep(1000);
#endif
    }

    LoginDatabase.WarnAboutSyncQueries(false);
    CharacterDatabase.WarnAboutSyncQueries(false);
    WorldDatabase.WarnAboutSyncQueries(false);
}

void SignalHandler(boost::system::error_code const& error, int /*signalNumber*/)
{
    if (!error)
        World::StopNow(SHUTDOWN_EXIT_CODE);
}

void FreezeDetector::Handler(std::weak_ptr<FreezeDetector> freezeDetectorRef, boost::system::error_code const& error)
{
    if (!error)
    {
        if (std::shared_ptr<FreezeDetector> freezeDetector = freezeDetectorRef.lock())
        {
            uint32 curtime = getMSTime();

            uint32 worldLoopCounter = World::m_worldLoopCounter;
            if (freezeDetector->_worldLoopCounter != worldLoopCounter)
            {
                freezeDetector->_lastChangeMsTime = curtime;
                freezeDetector->_worldLoopCounter = worldLoopCounter;
            }
            // possible freeze
            else
            {
                uint32 msTimeDiff = getMSTimeDiff(freezeDetector->_lastChangeMsTime, curtime);
                if (msTimeDiff > freezeDetector->_maxCoreStuckTimeInMs)
                {
                    TC_LOG_ERROR("server.worldserver", "World Thread hangs for %u ms, forcing a crash!", msTimeDiff);
                    ABORT_MSG("World Thread hangs for %u ms, forcing a crash!", msTimeDiff);
                }
            }

            freezeDetector->_timer.expires_from_now(boost::posix_time::seconds(1));
            freezeDetector->_timer.async_wait([freezeDetectorRef](boost::system::error_code const& timerError)
            {
                return Handler(freezeDetectorRef, timerError);
            });
        }
    }
}

AsyncAcceptor* StartRaSocketAcceptor(Trinity::Asio::IoContext& ioContext)
{
    uint16 raPort = uint16(sConfigMgr->GetIntDefault("Ra.Port", 3443));
    std::string raListener = sConfigMgr->GetStringDefault("Ra.IP", "0.0.0.0");

    AsyncAcceptor* acceptor = new AsyncAcceptor(ioContext, raListener, raPort);
    if (!acceptor->Bind())
    {
        TC_LOG_ERROR("server.worldserver", "Failed to bind RA socket acceptor");
        delete acceptor;
        return nullptr;
    }

    acceptor->AsyncAccept<RASession>();
    return acceptor;
}

// bool LoadRealmInfo(Trinity::Asio::IoContext& ioContext)
// {
//     QueryResult result = LoginDatabase.PQuery("SELECT id, name, address, localAddress, localSubnetMask, port, icon, flag, timezone, allowedSecurityLevel, population, gamebuild FROM realmlist WHERE id = %u", realm.Id.Realm);
//     if (!result)
//         return false;

//     Trinity::Asio::Resolver resolver(ioContext);

//     Field* fields = result->Fetch();
//     realm.Name = fields[1].GetString();
//     Optional<boost::asio::ip::tcp::endpoint> externalAddress = resolver.Resolve(boost::asio::ip::tcp::v4(), fields[2].GetString(), "");
//     if (!externalAddress)
//     {
//         TC_LOG_ERROR("server.worldserver", "Could not resolve address %s", fields[2].GetString().c_str());
//         return false;
//     }

//     realm.ExternalAddress = std::make_unique<boost::asio::ip::address>(externalAddress->address());

//     Optional<boost::asio::ip::tcp::endpoint> localAddress = resolver.Resolve(boost::asio::ip::tcp::v4(), fields[3].GetString(), "");
//     if (!localAddress)
//     {
//         TC_LOG_ERROR("server.worldserver", "Could not resolve address %s", fields[3].GetString().c_str());
//         return false;
//     }

//     realm.LocalAddress = std::make_unique<boost::asio::ip::address>(localAddress->address());

//     Optional<boost::asio::ip::tcp::endpoint> localSubmask = resolver.Resolve(boost::asio::ip::tcp::v4(), fields[4].GetString(), "");
//     if (!localSubmask)
//     {
//         TC_LOG_ERROR("server.worldserver", "Could not resolve address %s", fields[4].GetString().c_str());
//         return false;
//     }

//     realm.LocalSubnetMask = std::make_unique<boost::asio::ip::address>(localSubmask->address());

//     realm.Port = fields[5].GetUInt16();
//     realm.Type = fields[6].GetUInt8();
//     realm.Flags = RealmFlags(fields[7].GetUInt8());
//     realm.Timezone = fields[8].GetUInt8();
//     realm.AllowedSecurityLevel = AccountTypes(fields[9].GetUInt8());
//     realm.PopulationLevel = fields[10].GetFloat();
//     realm.Build = fields[11].GetUInt32();
//     return true;
// }

/// Initialize connection to the databases
bool StartDB()
{
    MySQL::Library_Init();

    // Load databases
    DatabaseLoader loader("server.worldserver", DatabaseLoader::DATABASE_NONE);
    loader
        .AddDatabase(LoginDatabase, "Login")
        .AddDatabase(CharacterDatabase, "Character")
        .AddDatabase(WorldDatabase, "World");

    if (!loader.Load())
        return false;

    ///- Get the realm Id from the configuration file
    realm.Id.Realm = sConfigMgr->GetIntDefault("RealmID", 0);
    if (!realm.Id.Realm)
    {
        TC_LOG_ERROR("server.worldserver", "Realm ID not defined in configuration file");
        return false;
    }

    // Load realm names into a store
    LoginDatabasePreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_REALMLIST);
    PreparedQueryResult result = LoginDatabase.Query(stmt);
    if (result)
    {
        do
        {
            Field* fields = result->Fetch();
            realmNameStore[fields[0].GetUInt32()] = fields[1].GetString(); // Store the realm name into the store
        }
        while (result->NextRow());
    }

    TC_LOG_INFO("server.worldserver", "Realm running as realm ID %d", realm.Id.Realm);

    ///- Clean the database before starting
    ClearOnlineAccounts();

    ///- Insert version info into DB
    WorldDatabase.PExecute("UPDATE version SET core_version = '%s', core_revision = '%s'", GitRevision::GetFullVersion(), GitRevision::GetHash());        // One-time query

    sWorld->LoadDBVersion();

    TC_LOG_INFO("server.worldserver", "Using World DB: %s", sWorld->GetDBVersion());
    return true;
}

void StopDB()
{
    CharacterDatabase.Close();
    WorldDatabase.Close();
    LoginDatabase.Close();

    MySQL::Library_End();
}

/// Clear 'online' status for all accounts with characters in this realm
void ClearOnlineAccounts()
{
    // Reset online status for all accounts with characters on the current realm
    LoginDatabase.DirectPExecute("UPDATE account SET online = 0 WHERE online > 0 AND id IN (SELECT acctid FROM realmcharacters WHERE realmid = %d)", realm.Id.Realm);

    // Reset online status for all characters
    CharacterDatabase.DirectExecute("UPDATE characters SET online = 0 WHERE online <> 0");

    // Battleground instance ids reset at server restart
    CharacterDatabase.DirectExecute("UPDATE character_battleground_data SET instanceId = 0");
}