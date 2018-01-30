/*
 * Copyright (C) 
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

/* ScriptData
Name: server_commandscript
%Complete: 100
Comment: All server related commands
Category: commandscripts
EndScriptData */

#include "Chat.h"
#include "Config.h"
#include "Language.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SystemConfig.h"
#include "AvgDiffTracker.h"

class server_commandscript : public CommandScript
{
public:
    server_commandscript() : CommandScript("server_commandscript") { }

    std::vector<ChatCommand> GetCommands() const
    {
        static std::vector<ChatCommand> serverIdleRestartCommandTable =
        {
            { "cancel",         SEC_ADMINISTRATOR,  true,  &HandleServerShutDownCancelCommand,      "" },
            { ""   ,            SEC_ADMINISTRATOR,  true,  &HandleServerIdleRestartCommand,         "" }
        };

        static std::vector<ChatCommand> serverIdleShutdownCommandTable =
        {
            { "cancel",         SEC_ADMINISTRATOR,  true,  &HandleServerShutDownCancelCommand,      "" },
            { ""   ,            SEC_ADMINISTRATOR,  true,  &HandleServerIdleShutDownCommand,        "" }
        };

        static std::vector<ChatCommand> serverRestartCommandTable =
        {
            { "cancel",         SEC_ADMINISTRATOR,  true,  &HandleServerShutDownCancelCommand,      "" },
            { ""   ,            SEC_ADMINISTRATOR,  true,  &HandleServerRestartCommand,             "" }
        };

        static std::vector<ChatCommand> serverShutdownCommandTable =
        {
            { "cancel",         SEC_ADMINISTRATOR,  true,  &HandleServerShutDownCancelCommand,      "" },
            { ""   ,            SEC_ADMINISTRATOR,  true,  &HandleServerShutDownCommand,            "" }
        };

        static std::vector<ChatCommand> serverSetCommandTable =
        {
            { "difftime",       SEC_CONSOLE,        true,  &HandleServerSetDiffTimeCommand,         "" },
            { "loglevel",       SEC_CONSOLE,        true,  &HandleServerSetLogLevelCommand,         "" },
            { "logfilelevel",   SEC_CONSOLE,        true,  &HandleServerSetLogFileLevelCommand,     "" },
            { "motd",           SEC_ADMINISTRATOR,  true,  &HandleServerSetMotdCommand,             "" },
            { "closed",         SEC_ADMINISTRATOR,  true,  &HandleServerSetClosedCommand,           "" }
        };

        static std::vector<ChatCommand> serverCommandTable =
        {
            { "corpses",        SEC_GAMEMASTER,     true,  &HandleServerCorpsesCommand,             "" },
            { "exit",           SEC_CONSOLE,        true,  &HandleServerExitCommand,                "" },
            { "idlerestart",    SEC_ADMINISTRATOR,  true,  NULL,                                    "", serverIdleRestartCommandTable },
            { "idleshutdown",   SEC_ADMINISTRATOR,  true,  NULL,                                    "", serverIdleShutdownCommandTable },
            { "info",           SEC_PLAYER,         true,  &HandleServerInfoCommand,                "" },
            { "underground",    SEC_ADMINISTRATOR,  true,  &HandleServerUnderGroundCommand,         "" },
            { "restart",        SEC_ADMINISTRATOR,  true,  NULL,                                    "", serverRestartCommandTable },
            { "shutdown",       SEC_ADMINISTRATOR,  true,  NULL,                                    "", serverShutdownCommandTable },
            { "set",            SEC_ADMINISTRATOR,  true,  NULL,                                    "", serverSetCommandTable },
            { "togglequerylog", SEC_CONSOLE,        true,  &HandleServerToggleQueryLogging,         "" }
        };

        static std::vector<ChatCommand> commandTable =
        {
            { "server",         SEC_ADMINISTRATOR,  true,  NULL,                                    "", serverCommandTable },
            { "info",           SEC_PLAYER,         true,  &HandleServerInfoCommand,                "" },
        };
        return commandTable;
    }

    // Triggering corpses expire check in world
    static bool HandleServerCorpsesCommand(ChatHandler* /*handler*/, char const* /*args*/)
    {
        sObjectAccessor->RemoveOldCorpses();
        return true;
    }

    static bool HandleServerInfoCommand(ChatHandler* handler, char const* /*args*/)
    {
        std::string realmName = sWorld->GetRealmName();
        uint32 playerCount = sWorld->GetPlayerCount();
        uint32 activeSessionCount = sWorld->GetActiveSessionCount();
        uint32 queuedSessionCount = sWorld->GetQueuedSessionCount();
        std::string uptime = secsToTimeString(sWorld->GetUptime()).append(".");
        uint32 updateTime = sWorld->GetUpdateTime();
        uint32 avgUpdateTime = avgDiffTracker.getAverage();

        float boostPercentage = sWorld->getFloatConfig(CONFIG_BOOST_PERCENTAGE_ONLINE);
        if (sWorld->getBoolConfig(CONFIG_BOOST_PERCENTAGE_ONLINE_ENABLE))
        {
            activeSessionCount = (activeSessionCount + (activeSessionCount * boostPercentage));
            playerCount = (playerCount + (playerCount * boostPercentage));
        }

        char buff[20];
        time_t now = sWorld->GetGameTime();
        strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));

        sWorld->GetRevision() != 0 ? handler->PSendSysMessage(LANG_SERVER_HASH_WITH_REVISION, sWorld->GetRealmName().c_str(), sWorld->GetRevision(), _HASH) : handler->PSendSysMessage(LANG_SERVER_HASH, sWorld->GetRealmName().c_str(), _HASH);
        queuedSessionCount != 0 ? handler->PSendSysMessage(LANG_CONNECTED_USERS_QUE, activeSessionCount, playerCount, queuedSessionCount) : handler->PSendSysMessage(LANG_CONNECTED_USERS, activeSessionCount, playerCount);
        handler->PSendSysMessage(LANG_UPTIME, uptime.c_str());
        handler->PSendSysMessage(LANG_SERVER_TIME, buff);
        handler->PSendSysMessage(LANG_UPDATE_DIFF, updateTime, avgUpdateTime);

        if (handler->GetSession())
            if (Player* p = handler->GetSession()->GetPlayer())
                if (p->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_DEVELOPER))
                    handler->PSendSysMessage(LANG_SERVER_DEV_INFO, avgDiffTracker.getTimeWeightedAverage(), devDiffTracker.getMax(), devDiffTracker.getAverage(), lfgDiffTracker.getAverage(), lfgDiffTracker.getMax());

        //! Can't use sWorld->ShutdownMsg here in case of console command
        if (sWorld->IsShuttingDown())
        {
            handler->PSendSysMessage(LANG_SERVER_SHUTDOWN_WARNING, (sWorld->GetShutdownMask() & SHUTDOWN_MASK_RESTART ? "restart" : "be shutteddown"), secsToTimeString(sWorld->GetShutDownTimeLeft()).append(".").c_str());
            handler->PSendSysMessage(LANG_SERVER_SHUTDOWN_REASON, sWorld->GetShutdownReason());
        }

        return true;
    }

    static bool HandleServerUnderGroundCommand(ChatHandler* handler, char const* /*args*/)
    {
        uint32 playerCount = sWorld->GetPlayerCount();
        uint32 activeSessionCount = sWorld->GetActiveSessionCount();

        handler->PSendSysMessage(LANG_SERVER_BOOST);
        handler->PSendSysMessage(LANG_SERVER_BOOST_INFO, activeSessionCount, playerCount);
        handler->PSendSysMessage(LANG_SERVER_BOOST);

        return true;
    }

    // Display the 'Message of the day' for the realm
    static bool HandleServerMotdCommand(ChatHandler* handler, char const* /*args*/)
    {
        handler->PSendSysMessage(LANG_MOTD_CURRENT, sWorld->GetMotd());
        return true;
    }

    static bool HandleServerShutDownCancelCommand(ChatHandler* handler, char const* /*args*/)
    {
        sWorld->ShutdownCancel();

        return true;
    }

    static bool HandleServerShutDownCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char const* timeStr = strtok((char*) args, " ");
        char const* exitmsg = strtok(nullptr, "");

        int32 time = atoi(timeStr);

        // Prevent interpret wrong arg value as 0 secs shutdown time
        if ((time == 0 && (timeStr[0] != '0' || timeStr[1] != '\0')) || time < 0)
            return false;

        if (exitmsg)
            sWorld->ShutdownServ(time, 0, SHUTDOWN_EXIT_CODE, exitmsg);
        else
            sWorld->ShutdownServ(time, 0, SHUTDOWN_EXIT_CODE);

        return true;
    }

    static bool HandleServerRestartCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char const* timeStr = strtok((char*) args, " ");
        char const* exitCodeStr = strtok(nullptr, "");

        int32 time = atoi(timeStr);

        //  Prevent interpret wrong arg value as 0 secs shutdown time
        if ((time == 0 && (timeStr[0] != '0' || timeStr[1] != '\0')) || time < 0)
            return false;

        if (exitCodeStr)
            sWorld->ShutdownServ(time, SHUTDOWN_MASK_RESTART, RESTART_EXIT_CODE, exitCodeStr);
        else
            sWorld->ShutdownServ(time, SHUTDOWN_MASK_RESTART, RESTART_EXIT_CODE);

        return true;
    }

    static bool HandleServerIdleRestartCommand(ChatHandler* /*handler*/, char const* args)
    {
        if (!*args)
            return false;

        char const* timeStr = strtok((char*) args, " ");
        char const* exitCodeStr = strtok(nullptr, "");

        int32 time = atoi(timeStr);

        // Prevent interpret wrong arg value as 0 secs shutdown time
        if ((time == 0 && (timeStr[0] != '0' || timeStr[1] != '\0')) || time < 0)
            return false;

        if (exitCodeStr)
            sWorld->ShutdownServ(time, SHUTDOWN_MASK_RESTART | SHUTDOWN_MASK_IDLE, RESTART_EXIT_CODE, exitCodeStr);
        else
            sWorld->ShutdownServ(time, SHUTDOWN_MASK_RESTART | SHUTDOWN_MASK_IDLE, RESTART_EXIT_CODE);

        return true;
    }

    static bool HandleServerIdleShutDownCommand(ChatHandler* /*handler*/, char const* args)
    {
        if (!*args)
            return false;

        char* timeStr = strtok((char*) args, " ");
        char* exitCodeStr = strtok(NULL, "");

        int32 time = atoi(timeStr);

        // Prevent interpret wrong arg value as 0 secs shutdown time
        if ((time == 0 && (timeStr[0] != '0' || timeStr[1] != '\0')) || time < 0)
            return false;

        if (exitCodeStr)
            sWorld->ShutdownServ(time, SHUTDOWN_MASK_IDLE, SHUTDOWN_EXIT_CODE, exitCodeStr);
        else
            sWorld->ShutdownServ(time, SHUTDOWN_MASK_IDLE, SHUTDOWN_EXIT_CODE);

        return true;
    }

    // Exit the realm
    static bool HandleServerExitCommand(ChatHandler* handler, char const* /*args*/)
    {
        handler->SendSysMessage(LANG_COMMAND_EXIT);
        World::StopNow(SHUTDOWN_EXIT_CODE);
        return true;
    }

    // Define the 'Message of the day' for the realm
    static bool HandleServerSetMotdCommand(ChatHandler* handler, char const* args)
    {
        sWorld->SetMotd(args);
        handler->PSendSysMessage(LANG_MOTD_NEW, args);
        return true;
    }

    // Set whether we accept new clients
    static bool HandleServerSetClosedCommand(ChatHandler* handler, char const* args)
    {
        if (strncmp(args, "on", 3) == 0)
        {
            handler->SendSysMessage(LANG_WORLD_CLOSED);
            sWorld->SetClosed(true);
            return true;
        }
        else if (strncmp(args, "off", 4) == 0)
        {
            handler->SendSysMessage(LANG_WORLD_OPENED);
            sWorld->SetClosed(false);
            return true;
        }

        handler->SendSysMessage(LANG_USE_BOL);
        handler->SetSentErrorMessage(true);
        return false;
    }

    // Set the level of logging
    static bool HandleServerSetLogFileLevelCommand(ChatHandler* /*handler*/, char const* args)
    {
        if (!*args)
            return false;

        char* newLevel = strtok((char*)args, " ");
        if (!newLevel)
            return false;

        sLog->SetLogFileLevel(newLevel);
        return true;
    }

    // Set the level of logging
    static bool HandleServerSetLogLevelCommand(ChatHandler* /*handler*/, char const* args)
    {
        if (!*args)
            return false;

        char* newLevel = strtok((char*)args, " ");
        if (!newLevel)
            return false;

        sLog->SetLogLevel(newLevel);
        return true;
    }

    // set diff time record interval
    static bool HandleServerSetDiffTimeCommand(ChatHandler* /*handler*/, char const* args)
    {
        if (!*args)
            return false;

        char* newTimeStr = strtok((char*)args, " ");
        if (!newTimeStr)
            return false;

        int32 newTime = atoi(newTimeStr);
        if (newTime < 0)
            return false;

        sWorld->SetRecordDiffInterval(newTime);
        printf("Record diff every %u ms\n", newTime);

        return true;
    }

    // toggle sql driver query logging
    static bool HandleServerToggleQueryLogging(ChatHandler* handler, char const* /*args*/)
    {
        sLog->SetSQLDriverQueryLogging(!sLog->GetSQLDriverQueryLogging());

        if (sLog->GetSQLDriverQueryLogging())
            handler->PSendSysMessage(LANG_SQLDRIVER_QUERY_LOGGING_ENABLED);
        else
            handler->PSendSysMessage(LANG_SQLDRIVER_QUERY_LOGGING_DISABLED);
        return true;
    }
};

void AddSC_server_commandscript()
{
    new server_commandscript();
}
