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

#include "MySQLThreading.h"


#include "Log.h"
#include "Master.h"
#include "World.h"

#include "AsyncAcceptor.h"
#include "DeadlineTimer.h"
#include "IoContext.h"
#include "ThreadPool.h"
#include "RASession.h"

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
uint32 realmID;                                             ///< Id of the realm

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

AsyncAcceptor* StartRaSocketAcceptor(Trinity::Asio::IoContext& ioContext);

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
    
    std::shared_ptr<Trinity::Asio::IoContext> ioContext = std::make_shared<Trinity::Asio::IoContext>();

    sLog->Initialize(sConfigMgr->GetBoolDefault("Log.Async.Enable", false) ? ioContext.get() : nullptr);

    TC_LOG_INFO("server.worldserver", "Using configuration file %s.", cfg_file);

    TC_LOG_INFO("server.worldserver", "Using SSL version: %s (library: %s)", OPENSSL_VERSION_TEXT, SSLeay_version(SSLEAY_VERSION));

    // Start the Boost based thread pool
    int numThreads = sConfigMgr->GetIntDefault("ThreadPool", 1);
    if (numThreads < 1)
        numThreads = 1;

    std::shared_ptr<Trinity::ThreadPool> threadPool = std::make_shared<Trinity::ThreadPool>(numThreads);

    for (int i = 0; i < numThreads; ++i)
        threadPool->PostWork([ioContext]() { ioContext->run(); });

    // Start the Remote Access port (acceptor) if enabled
    std::unique_ptr<AsyncAcceptor> raAcceptor;
    if (sConfigMgr->GetBoolDefault("Ra.Enable", false))
        raAcceptor.reset(StartRaSocketAcceptor(*ioContext));


    // Start the freeze check callback cycle in 5 seconds (cycle itself is 1 sec)
    std::shared_ptr<FreezeDetector> freezeDetector;
    if (int coreStuckTime = sConfigMgr->GetIntDefault("MaxCoreStuckTime", 60))
    {
        freezeDetector = std::make_shared<FreezeDetector>(*ioContext, coreStuckTime * 1000);
        FreezeDetector::Start(freezeDetector);
        TC_LOG_INFO("server.worldserver", "Starting up anti-freeze thread (%u seconds max stuck time)...", coreStuckTime);
    }


    ///- and run the 'Master'
    /// @todo Why do we need this 'Master'? Can't all of this be in the Main as for Realmd?
    int ret = sMaster->Run();

    // at sMaster return function exist with codes
    // 0 - normal shutdown
    // 1 - shutdown at error
    // 2 - restart command used, this code can be used by restarter for restart Trinityd

    return ret;
}

/// @}

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