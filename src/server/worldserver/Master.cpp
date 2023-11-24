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

/** \file
    \ingroup Trinityd
*/


#include "Common.h"
#include "SystemConfig.h"
#include "SignalHandler.h"
#include "World.h"
#include "WorldRunnable.h"
#include "WorldSocket.h"
#include "WorldSocketMgr.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "DatabaseLoader.h"
#include "DatabaseWorkerPool.h"

#include "CliRunnable.h"
#include "Log.h"
#include "Master.h"
#include "TCSoap.h"
#include "Timer.h"
#include "Util.h"
#include "AuthSocket.h"
#include "RealmList.h"
#include "ScriptLoader.h"
#include "ScriptMgr.h"

#include "BigNumber.h"
#include "OpenSSLCrypto.h"

#include "Banner.h"
#include "MySQLThreading.h"

#ifdef _WIN32
#include <TlHelp32.h>
#include "ServiceWin32.h"
extern int m_ServiceStatus;
#endif

#ifdef __linux__
#include <sched.h>
#include <sys/resource.h>
#define PROCESS_HIGH_PRIORITY -15 // [-20, 19], default is 0
#endif

void RunAuthserverIfNeed()
{
#ifdef _WIN32
    std::string authServerProcessName = sConfigMgr->GetStringDefault("AuthServer.Process", "");     // name.exe
    std::string authServerStartCommand = sConfigMgr->GetStringDefault("AuthServer.Command", "");    // start /d "path" name.exe
    if (authServerProcessName.empty() || authServerStartCommand.empty())
        return;

    DWORD pid = 0;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);

    if (Process32First(snapshot, &process))
    {
        do
        {
            if (std::string(process.szExeFile) == authServerProcessName)
            {
                pid = process.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &process));
    }

    CloseHandle(snapshot);

    if (pid != 0)
        return;

    system(authServerStartCommand.c_str());
#endif
}

Master* Master::instance()
{
    static Master instance;
    return &instance;
}

/// Main function
int Master::Run()
{

    // After loadeding comfig from DB
    RunAuthserverIfNeed();

    ///- Launch WorldRunnable thread
    MopCore::Thread worldThread(new WorldRunnable);
    worldThread.setPriority(MopCore::Priority_Highest);


#if defined(_WIN32) || defined(__linux__)
    ///- Handle affinity for multiple processors and process priority
    uint32 affinity = sConfigMgr->GetIntDefault("UseProcessors", 0);
    bool highPriority = sConfigMgr->GetBoolDefault("ProcessPriority", false);

#ifdef _WIN32 // Windows

    HANDLE hProcess = GetCurrentProcess();

    if (affinity > 0)
    {
        ULONG_PTR appAff;
        ULONG_PTR sysAff;

        if (GetProcessAffinityMask(hProcess, &appAff, &sysAff))
        {
            ULONG_PTR currentAffinity = affinity & appAff;            // remove non accessible processors

            if (!currentAffinity)
                TC_LOG_ERROR("server.worldserver", "Processors marked in UseProcessors bitmask (hex) %x are not accessible for the worldserver. Accessible processors bitmask (hex): %x", affinity, appAff);
            else if (SetProcessAffinityMask(hProcess, currentAffinity))
                TC_LOG_INFO("server.worldserver", "Using processors (bitmask, hex): %x", currentAffinity);
            else
                TC_LOG_ERROR("server.worldserver", "Can't set used processors (hex): %x", currentAffinity);
        }
    }

    if (highPriority)
    {
        if (SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS))
            TC_LOG_INFO("server.worldserver", "worldserver process priority class set to HIGH");
        else
            TC_LOG_ERROR("server.worldserver", "Can't set worldserver process priority class.");
    }
#else // Linux

    if (affinity > 0)
    {
        cpu_set_t mask;
        CPU_ZERO(&mask);

        for (unsigned int i = 0; i < sizeof(affinity) * 8; ++i)
            if (affinity & (1 << i))
                CPU_SET(i, &mask);

        if (sched_setaffinity(0, sizeof(mask), &mask))
            TC_LOG_ERROR("server.worldserver", "Can't set used processors (hex): %x, error: %s", affinity, strerror(errno));
        else
        {
            CPU_ZERO(&mask);
            sched_getaffinity(0, sizeof(mask), &mask);
            TC_LOG_INFO("server.worldserver", "Using processors (bitmask, hex): %lx", *(__cpu_mask*)(&mask));
        }
    }

    if (highPriority)
    {
        if (setpriority(PRIO_PROCESS, 0, PROCESS_HIGH_PRIORITY))
            TC_LOG_ERROR("server.worldserver", "Can't set worldserver process priority class, error: %s", strerror(errno));
        else
            TC_LOG_INFO("server.worldserver", "worldserver process priority class set to %i", getpriority(PRIO_PROCESS, 0));
    }

#endif
#endif

    ///- Launch the world listener socket
    uint16 worldPort = uint16(sWorld->getIntConfig(CONFIG_PORT_WORLD));
    std::string bindIp = sConfigMgr->GetStringDefault("BindIP", "0.0.0.0");

    if (sWorldSocketMgr.StartNetwork(worldPort, bindIp.c_str()) == -1)
    {
        TC_LOG_ERROR("server.worldserver", "Failed to start network");
        World::StopNow(ERROR_EXIT_CODE);
        // go down and shutdown the server
    }

    // set server online (allow connecting now)
    LoginDatabase.DirectPExecute("UPDATE realmlist SET flag = flag & ~%u, population = 0 WHERE id = '%u'", REALM_FLAG_INVALID, realmID);

    TC_LOG_INFO("server.worldserver", "%s (worldserver-daemon) ready...", _FULLVERSION);

    // when the main thread closes the singletons get unloaded
    // since worldrunnable uses them, it will crash if unloaded after master
    worldThread.wait();

    // set server offline
    LoginDatabase.DirectPExecute("UPDATE realmlist SET flag = flag | %u WHERE id = '%d'", REALM_FLAG_OFFLINE, realmID);

    ///- Clean database before leaving
    ClearOnlineAccounts();

    TC_LOG_INFO("server.worldserver", "Halting process...");

    // for some unknown reason, unloading scripts here and not in worldrunnable
    // fixes a memory leak related to detaching threads from the module
    //UnloadScriptingModule();

    // Exit the process with specified return value
    return World::GetExitCode();
}

/// Clear 'online' status for all accounts with characters in this realm
void Master::ClearOnlineAccounts()
{
    // Reset online status for all accounts with characters on the current realm
    LoginDatabase.DirectPExecute("UPDATE account SET online = 0 WHERE online > 0 AND id IN (SELECT acctid FROM realmcharacters WHERE realmid = %d)", realmID);

    // Reset online status for all characters
    CharacterDatabase.DirectExecute("UPDATE characters SET online = 0 WHERE online <> 0");

    // Battleground instance ids reset at server restart
    CharacterDatabase.DirectExecute("UPDATE character_battleground_data SET instanceId = 0");
}
