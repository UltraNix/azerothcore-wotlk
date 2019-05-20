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
Name: transfer_commandscript
%Complete: 100
Comment: All transfers related commands
Category: commandscripts
EndScriptData */

#include <sstream>

#include "AccountMgr.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "PlayerDump.h"
#include "Player.h"
#include "ReputationMgr.h"
#include "ScriptMgr.h"

class transfer_commandscript : public CommandScript
{
public:
    transfer_commandscript() : CommandScript("transfer_commandscript") { }

    std::vector<ChatCommand> GetCommands() const
    {
        static std::vector<ChatCommand> transferCharacterCommandTable =
        {
                { "newid",       SEC_ADMINISTRATOR,  true,  &HandleTransferCharacterNewIdCommand,        "" }
        };

        static std::vector<ChatCommand> transferItemCommandTable =
        {
                { "newid",       SEC_ADMINISTRATOR,  true,  &HandleTransferItemNewIdCommand,        "" }
        };

        static std::vector<ChatCommand> transferPetCommandTable =
        {
                { "newid",       SEC_ADMINISTRATOR,  true,  &HandleTransferPetNewIdCommand,        "" }
        };

        static std::vector<ChatCommand> transferCommandTable =
        {
            { "character",      SEC_ADMINISTRATOR,     true,  NULL, "", transferCharacterCommandTable },
            { "item",           SEC_ADMINISTRATOR,     true,  NULL, "", transferItemCommandTable },
            { "pet",            SEC_ADMINISTRATOR,     true,  NULL, "", transferPetCommandTable }
        };

        static std::vector<ChatCommand> commandTable =
        {
            { "transfer",       SEC_ADMINISTRATOR,  true,  NULL,                                   "", transferCommandTable },
        };

        return commandTable;
    }

    static bool HandleTransferCharacterNewIdCommand(ChatHandler *handler, char const *args)
    {
        handler->PSendSysMessage("%u", sObjectMgr->GenerateLowGuid(HIGHGUID_PLAYER));
        return true;
    }

    static bool HandleTransferItemNewIdCommand(ChatHandler *handler, char const *args)
    {
        int count = 1;

        if (args && strlen(args) > 0)
        {
            count = atoi(args);
        }

        if (count < 1)
            count = 1;

        std::ostringstream ss;

        for (int i = 0; i < count; ++i)
        {
            ss << sObjectMgr->GenerateLowGuid(HIGHGUID_ITEM) << " ";
        }

        handler->SendSysMessage(ss.str().c_str());
        return true;
    }

    static bool HandleTransferPetNewIdCommand(ChatHandler *handler, char const *args)
    {
        int count = 1;

        if (args && strlen(args) > 0)
        {
            count = atoi(args);
        }

        if (count < 1)
            count = 1;

        std::ostringstream ss;

        for (int i = 0; i < count; ++i)
        {
            ss << sObjectMgr->GenerateLowGuid(HIGHGUID_PET) << " ";
        }

        handler->SendSysMessage(ss.str().c_str());
        return true;
    }
};

void AddSC_transfer_commandscript()
{
    new transfer_commandscript();
}
