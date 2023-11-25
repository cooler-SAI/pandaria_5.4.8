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
