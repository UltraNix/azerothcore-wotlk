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
Name: custom_commandscript
%Complete: 100
Comment: All account related commands
Category: commandscripts
EndScriptData */

#include "AccountMgr.h"
#include "Chat.h"
#include "Language.h"
#include "Player.h"
#include "ScriptMgr.h"

class custom_commandscript : public CommandScript
{
public:
    custom_commandscript() : CommandScript("custom_commandscript") { }

    std::vector<ChatCommand> GetCommands() const
    {
        static std::vector<ChatCommand> commandTable =
        {
            { "service",            SEC_ADMINISTRATOR,      true,  &HandleServiceCommand,               "" },
            { "addninja",           SEC_GAMEMASTER,         false, &HandleAddNinjaCommand,              "" },
            { "removeninja",        SEC_GAMEMASTER,         false, &HandleRemoveNinjaCommand,           "" },
            { "listninja",          SEC_PLAYER,             false, HandleListNinjaCommand,              "" },
            { "blizzlike",          SEC_PLAYER,             false, HandleBlizzlikeCommand,              "" },
            { "pvpinfo",            SEC_PLAYER,             false, HandlePvPInfoCommand,                "" },
            { "dodge",              SEC_PLAYER,             false, HandleDodgeModeCommand,              "" },
            { "hasblizzlike",       SEC_MODERATOR,          false, HandleHasBlizzlikeCommand,           "" },
            { "chinaban",           SEC_MODERATOR,          false, &HandleChinaBanCommand,              "" },
            { "speedban",           SEC_MODERATOR,          false, &HandleSpeedBanCommand,              "" },
            { "englishmute",        SEC_MODERATOR,          false, &HandleEnglishMuteCommand,           "" }
        };
        return commandTable;
    }

    static bool HandleServiceCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        // Account Name
        char* aname = strtok((char*)args, " ");
        if (!aname)
            return false;

        std::string accName = aname;
        std::string serviceName;    // To display on output command and log

                                    // Premium Type 
        char* typeStr = strtok(nullptr, " ");
        if (!typeStr || !atoi(typeStr) && typeStr != "0")
            return false;

        // duration of premium service
        char* durationStr = strtok(nullptr, "");
        if (!durationStr)
            return false;

        // convert accountname to account ID
        PreparedStatement*  stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_ACCOUNT_ID_BY_NAME);
        stmt->setString(0, accName);
        PreparedQueryResult result = LoginDatabase.Query(stmt);

        if (!result)
            return false;

        uint32 accId = 0;
        Field* fields = result->Fetch();
        accId = fields[0].GetUInt32();

        // if input of time is less than 0 that means we wanna delete service from account
        if (atoi(durationStr) < 0)
        {
            switch (atoi(typeStr))
            {
                case SERVICE_TELEPORT_INPUT: // -> SERVICE_TELEPORT
                    stmt = LoginDatabase.GetPreparedStatement(LOGIN_DEL_PREMIUM_ID);
                    stmt->setUInt32(0, accId);
                    stmt->setUInt32(1, realmID);
                    stmt->setUInt8(2, SERVICE_TELEPORT);
                    LoginDatabase.Execute(stmt);
                    serviceName = "SERVICE_TELEPORT";
                    break;
                case SERVICE_NO_RESSURECTION_SICKNESS:
                    stmt = LoginDatabase.GetPreparedStatement(LOGIN_DEL_PREMIUM_ID);
                    stmt->setUInt32(0, accId);
                    stmt->setUInt32(1, realmID);
                    stmt->setUInt8(2, SERVICE_NO_RESSURECTION_SICKNESS);
                    LoginDatabase.Execute(stmt);
                    serviceName = "SERVICE_NO_RESSURECTION_SICKNESS";
                    break;
                case SERVICE_EXP_BOOST:
                    stmt = LoginDatabase.GetPreparedStatement(LOGIN_DEL_PREMIUM_ID);
                    stmt->setUInt32(0, accId);
                    stmt->setUInt32(1, realmID);
                    stmt->setUInt8(2, SERVICE_EXP_BOOST);
                    LoginDatabase.Execute(stmt);
                    serviceName = "SERVICE_EXP_BOOST";
                    break;
                case SERVICE_NO_DURABILITY_LOSS:
                    stmt = LoginDatabase.GetPreparedStatement(LOGIN_DEL_PREMIUM_ID);
                    stmt->setUInt32(0, accId);
                    stmt->setUInt32(1, realmID);
                    stmt->setUInt8(2, SERVICE_NO_DURABILITY_LOSS);
                    LoginDatabase.Execute(stmt);
                    serviceName = "SERVICE_NO_DURABILITY_LOSS";
                    break;
                case SERVICE_INSTANT_FLIGHT_PATHS:
                    stmt = LoginDatabase.GetPreparedStatement(LOGIN_DEL_PREMIUM_ID);
                    stmt->setUInt32(0, accId);
                    stmt->setUInt32(1, realmID);
                    stmt->setUInt8(2, SERVICE_INSTANT_FLIGHT_PATHS);
                    LoginDatabase.Execute(stmt);
                    serviceName = "SERVICE_INSTANT_FLIGHT_PATHS";
                    break;
                case SERVICE_EXP_BOOST_X4:
                    stmt = LoginDatabase.GetPreparedStatement(LOGIN_DEL_PREMIUM_ID);
                    stmt->setUInt32(0, accId);
                    stmt->setUInt32(1, realmID);
                    stmt->setUInt8(2, SERVICE_EXP_BOOST_X4);
                    LoginDatabase.Execute(stmt);
                    serviceName = "SERVICE_EXP_BOOST_X4";
                    break;
            }
            handler->PSendSysMessage("You have disabled service '%s' on account %s", serviceName.c_str(), accName.c_str());
            sLog->outPremium("Service '%s' has been disabled on account %s", serviceName.c_str(), accName.c_str());
            return true;
        }


        uint32 premiumTime = TimeStringToSecs(durationStr); // duration of premium service
        time_t extraTime;  // is time left of previous active service, if no result then null

                           // Query check for previous premium service, if there is result stack the time of premium service
        PreparedStatement* stmt2 = LoginDatabase.GetPreparedStatement(LOGIN_SEL_PREMIUM_TIME_BY_ID);
        stmt2->setUInt32(0, accId);
        stmt2->setUInt32(1, realmID);
        stmt2->setUInt8(2, atoi(typeStr));
        PreparedQueryResult timeResult = LoginDatabase.Query(stmt2);

        if (timeResult)
        {
            Field* timeFields = timeResult->Fetch();
            extraTime = time_t(timeFields[1].GetUInt32());
            premiumTime = premiumTime + extraTime;
        }
        else
            premiumTime = time(nullptr) + premiumTime;

        switch (atoi(typeStr))
        {
            case SERVICE_TELEPORT_INPUT: // -> SERVICE_TELEPORT
                stmt = LoginDatabase.GetPreparedStatement(LOGIN_REP_ACCOUNT_PREMIUM);
                stmt->setUInt32(0, accId);
                stmt->setUInt32(1, realmID);
                stmt->setUInt8(2, SERVICE_TELEPORT);
                stmt->setUInt32(3, time(nullptr));
                stmt->setUInt32(4, premiumTime);
                LoginDatabase.Execute(stmt);
                serviceName = "SERVICE_TELEPORT";
                break;
            case SERVICE_NO_RESSURECTION_SICKNESS:
                stmt = LoginDatabase.GetPreparedStatement(LOGIN_REP_ACCOUNT_PREMIUM);
                stmt->setUInt32(0, accId);
                stmt->setUInt32(1, realmID);
                stmt->setUInt8(2, SERVICE_NO_RESSURECTION_SICKNESS);
                stmt->setUInt32(3, time(nullptr));
                stmt->setUInt32(4, premiumTime);
                LoginDatabase.Execute(stmt);
                serviceName = "SERVICE_NO_RESSURECTION_SICKNESS";
                break;
            case SERVICE_EXP_BOOST:
                stmt = LoginDatabase.GetPreparedStatement(LOGIN_REP_ACCOUNT_PREMIUM);
                stmt->setUInt32(0, accId);
                stmt->setUInt32(1, realmID);
                stmt->setUInt8(2, SERVICE_EXP_BOOST);
                stmt->setUInt32(3, time(nullptr));
                stmt->setUInt32(4, premiumTime);
                LoginDatabase.Execute(stmt);
                serviceName = "SERVICE_EXP_BOOST";
                break;
            case SERVICE_NO_DURABILITY_LOSS:
                stmt = LoginDatabase.GetPreparedStatement(LOGIN_REP_ACCOUNT_PREMIUM);
                stmt->setUInt32(0, accId);
                stmt->setUInt32(1, realmID);
                stmt->setUInt8(2, SERVICE_NO_DURABILITY_LOSS);
                stmt->setUInt32(3, time(nullptr));
                stmt->setUInt32(4, premiumTime);
                LoginDatabase.Execute(stmt);
                serviceName = "SERVICE_NO_DURABILITY_LOSS";
                break;
            case SERVICE_INSTANT_FLIGHT_PATHS:
                stmt = LoginDatabase.GetPreparedStatement(LOGIN_REP_ACCOUNT_PREMIUM);
                stmt->setUInt32(0, accId);
                stmt->setUInt32(1, realmID);
                stmt->setUInt8(2, SERVICE_INSTANT_FLIGHT_PATHS);
                stmt->setUInt32(3, time(nullptr));
                stmt->setUInt32(4, premiumTime);
                LoginDatabase.Execute(stmt);
                serviceName = "SERVICE_INSTANT_FLIGHT_PATHS";
                break;
            case SERVICE_EXP_BOOST_X4:
                stmt = LoginDatabase.GetPreparedStatement(LOGIN_REP_ACCOUNT_PREMIUM);
                stmt->setUInt32(0, accId);
                stmt->setUInt32(1, realmID);
                stmt->setUInt8(2, SERVICE_EXP_BOOST_X4);
                stmt->setUInt32(3, time(nullptr));
                stmt->setUInt32(4, premiumTime);
                LoginDatabase.Execute(stmt);
                serviceName = "SERVICE_EXP_BOOST_X4";
                break;
        }

        handler->PSendSysMessage("You have enabled service '%s' on account %s for %s", serviceName.c_str(), accName.c_str(), secsToTimeString(TimeStringToSecs(durationStr), true).c_str());
        sLog->outPremium("Service '%s' has been enabled on account %s for %s", serviceName.c_str(), accName.c_str(), secsToTimeString(TimeStringToSecs(durationStr), true).c_str());
        return true;
    }

    static bool HandleAddNinjaCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        // Account Name
        char* inputGuid = strtok((char*)args, " ");
        if (!inputGuid || !atoi(inputGuid) && inputGuid != "0")
            return false;

        uint32 ninjaGuid = atoi(inputGuid);

        if (!ninjaGuid || ninjaGuid <= 0)
            return false;

        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_NINJA_LOOTER_GUID_CHECK);
        stmt->setUInt32(0, ninjaGuid);
        PreparedQueryResult result = CharacterDatabase.Query(stmt);

        if (!result)
        {
            handler->PSendSysMessage("Wrong guid, player doesn't exists in database.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_NINJA_LOOTER);
        stmt->setUInt8(0, 1);
        stmt->setUInt32(1, ninjaGuid);
        CharacterDatabase.Execute(stmt);

        handler->PSendSysMessage("Success! Player with GUID: %u has been added to ninja looter list.", ninjaGuid);

        return true;
    }

    static bool HandleRemoveNinjaCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        // Account Name
        char* inputGuid = strtok((char*)args, " ");
        if (!inputGuid || !atoi(inputGuid) && inputGuid != "0")
            return false;

        uint32 ninjaGuid = atoi(inputGuid);

        if (!ninjaGuid || ninjaGuid <= 0)
            return false;

        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_NINJA_LOOTER_GUID_CHECK);
        stmt->setUInt32(0, ninjaGuid);
        PreparedQueryResult result = CharacterDatabase.Query(stmt);

        if (!result)
        {
            handler->PSendSysMessage("Wrong guid, player doesn't exists in database.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_NINJA_LOOTER);
        stmt->setUInt8(0, 0);
        stmt->setUInt32(1, ninjaGuid);
        CharacterDatabase.Execute(stmt);

        handler->PSendSysMessage("Success! Player with GUID: %u has been removed from ninja looter list.", ninjaGuid);

        return true;
    }

    static bool HandleListNinjaCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_NINJA_LOOTER);
        PreparedQueryResult result = CharacterDatabase.Query(stmt);

        if (!result)
        {
            handler->PSendSysMessage("There are no ninja looters on the list. Sounds good, isn't it?");
            handler->SetSentErrorMessage(true);
            return false;
        }
        else
        {
            do
            {
                Field *fields = result->Fetch();
                std::string name = fields[0].GetString();
                handler->PSendSysMessage("Warning! Player: %s at ninja looter list!", name.c_str());

            } while (result->NextRow());
        }

        return true;
    }

    static bool HandleAccountCommand(ChatHandler* handler, char const* /*args*/)
    {
        AccountTypes gmLevel = handler->GetSession()->GetSecurity();
        handler->PSendSysMessage(LANG_ACCOUNT_LEVEL, uint32(gmLevel));
        return true;
    }

    static bool HandleBlizzlikeCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        if (!player->BlizzlikeMode())
        {
            player->SetBlizzlikeMode(true);
            handler->PSendSysMessage("|cff77a5c4Your experience rate has been changed to blizzlike (x1). You have to relog for the change to apply.|r");
            handler->SetSentErrorMessage(true);
        }
        else
        {
            player->SetBlizzlikeMode(false);
            handler->PSendSysMessage("|cff77a5c4Your experience rate has been changed to default. You have to relog for the change to apply.|r");
            handler->SetSentErrorMessage(true);
        }

        return true;
    }

    static bool HandlePvPInfoCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        if (!player->PvPAnnounces())
        {
            player->SetPvPAnnounces(true);
            handler->PSendSysMessage("|cff77a5c4PvP announcements are |cff06e015enabled|cff77a5c4. You have to relog for the change to apply.|r");
            handler->SetSentErrorMessage(true);
        }
        else
        {
            player->SetPvPAnnounces(false);
            handler->PSendSysMessage("|cff77a5c4PvP announcements are |cffff0000disabled|cff77a5c4. You have to relog for the change to apply.|r");
            handler->SetSentErrorMessage(true);
        }

        return true;
    }

    static bool HandleDodgeModeCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        if (player->GetMaxPersonalArenaRatingRequirement(0) < 2000)
        {
            handler->PSendSysMessage("|cff77a5c42000 Personal Rating is required to use this command.|r");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!player->IsInDodgeMode())
        {
            player->SetDodgeMode(true);
            handler->PSendSysMessage("|cff77a5c4Dodge mode has been |cff06e015enabled|cff77a5c4, display of your location is disabled.|r");
            handler->SetSentErrorMessage(true);
        }
        else
        {
            player->SetDodgeMode(false);
            handler->PSendSysMessage("|cff77a5c4Dodge mode has been |cffff0000disabled|cff77a5c4, display of your location is enabled.|r");
            handler->SetSentErrorMessage(true);
        }

        return true;
    }

    static bool HandleHasBlizzlikeCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player *player = handler->getSelectedPlayer();

        if (!player)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->BlizzlikeMode())
            handler->PSendSysMessage("Player %s has |cff00ff00enabled|cffffff00 Blizzlike Mode.", player->GetName().c_str());
        else
            handler->PSendSysMessage("Player %s has |cffff0000disabled|cffffff00 Blizzlike Mode.", player->GetName().c_str());

        return true;
    }

    // ChinaBan!
    static bool HandleChinaBanCommand(ChatHandler* handler, char const* args)
    {
        Player* target;
        uint64 targetGuid;
        std::string targetName;
        std::string accountName;

        if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid, &targetName))
            return false;

        uint32 accountId = target ? target->GetSession()->GetAccountId() : sObjectMgr->GetPlayerAccountIdByGUID(targetGuid);

        if (target)
        {
            // check online security
            if (handler->HasLowerSecurity(target, 0))
                return false;

            if (AccountMgr::GetName(accountId, accountName))
                sWorld->BanAccount(BAN_ACCOUNT, accountName.c_str(), "-1", "Gold selling.", handler->GetSession() ? handler->GetSession()->GetPlayerName() : "");
        }
        else
        {
            // check offline security
            if (handler->HasLowerSecurity(NULL, targetGuid))
                return false;

            if (AccountMgr::GetName(sObjectMgr->GetPlayerAccountIdByPlayerName(targetName.c_str()), accountName))
                sWorld->BanAccount(BAN_ACCOUNT, accountName.c_str(), "-1", "Gold selling.", handler->GetSession() ? handler->GetSession()->GetPlayerName() : "");
        }

        // pussywizard: notify all online GMs
        TRINITY_READ_GUARD(HashMapHolder<Player>::LockType, *HashMapHolder<Player>::GetLock());
        HashMapHolder<Player>::MapType const& m = sObjectAccessor->GetPlayers();
        for (HashMapHolder<Player>::MapType::const_iterator itr = m.begin(); itr != m.end(); ++itr)
            if (itr->second->GetSession()->GetSecurity())
                ChatHandler(itr->second->GetSession()).PSendSysMessage("Game Master: [%s] has banned player: [%s] for gold selling.", handler->GetSession()->GetPlayerName().c_str(), targetName.c_str());

        return true;
    }

    // SpeedBan!
    static bool HandleSpeedBanCommand(ChatHandler* handler, char const* args)
    {
        Player* target;
        uint64 targetGuid;
        std::string targetName;
        std::string accountName;

        if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid, &targetName))
            return false;

        uint32 accountId = target ? target->GetSession()->GetAccountId() : sObjectMgr->GetPlayerAccountIdByGUID(targetGuid);

        if (target)
        {
            // check online security
            if (handler->HasLowerSecurity(target, 0))
                return false;

            if (AccountMgr::GetName(target->GetSession()->GetAccountId(), accountName))
                sWorld->BanAccount(BAN_ACCOUNT, accountName.c_str(), "30d", "Speed Hack.", handler->GetSession() ? handler->GetSession()->GetPlayerName() : "");
        }
        else
        {
            // check offline security
            if (handler->HasLowerSecurity(NULL, targetGuid))
                return false;

            if (AccountMgr::GetName(accountId, accountName))
                sWorld->BanAccount(BAN_ACCOUNT, accountName.c_str(), "30d", "Speed Hack.", handler->GetSession() ? handler->GetSession()->GetPlayerName() : "");
        }

        // pussywizard: notify all online GMs
        TRINITY_READ_GUARD(HashMapHolder<Player>::LockType, *HashMapHolder<Player>::GetLock());
        HashMapHolder<Player>::MapType const& m = sObjectAccessor->GetPlayers();
        for (HashMapHolder<Player>::MapType::const_iterator itr = m.begin(); itr != m.end(); ++itr)
            if (itr->second->GetSession()->GetSecurity())
                ChatHandler(itr->second->GetSession()).PSendSysMessage("Game Master: [%s] has banned player: [%s] for speed hack.", handler->GetSession()->GetPlayerName().c_str(), targetName.c_str());

        return true;
    }

    // EnglishMute!
    static bool HandleEnglishMuteCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char* nameStr = strtok((char*)args, " ");
        if (!nameStr)
            return false;

        Player* target;
        uint64 targetGuid;
        std::string targetName;
        if (!handler->extractPlayerTarget(nameStr, &target, &targetGuid, &targetName))
            return false;

        uint32 accountId = target ? target->GetSession()->GetAccountId() : sObjectMgr->GetPlayerAccountIdByGUID(targetGuid);

        // find only player from same account if any
        if (!target)
            if (WorldSession* session = sWorld->FindSession(accountId))
                target = session->GetPlayer();

        // must have strong lesser security level
        if (handler->HasLowerSecurity(target, targetGuid, true))
            return false;

        PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_MUTE_TIME);
        std::string muteBy = "";
        if (handler->GetSession())
            muteBy = handler->GetSession()->GetPlayerName();
        else
            muteBy = "Console";

        std::string reason = "Inappropriate language, speak English!";

        if (target)
        {
            // Target is online, mute will be in effect right away.
            int64 muteTime = time(nullptr) + 30 * MINUTE;
            target->GetSession()->m_muteTime = muteTime;
            stmt->setInt64(0, muteTime);
            ChatHandler(target->GetSession()).PSendSysMessage(LANG_YOUR_CHAT_DISABLED, 30, muteBy.c_str(), reason.c_str());
        }
        else
        {
            // Target is offline, mute will be in effect starting from the next login.
            int32 muteTime = -int32(30 * MINUTE);
            stmt->setInt64(0, muteTime);
        }

        stmt->setString(1, reason.c_str());
        stmt->setString(2, muteBy.c_str());
        stmt->setUInt32(3, accountId);
        LoginDatabase.Execute(stmt);
        std::string nameLink = handler->playerLink(targetName);

        // Sitowsky: Mute History
        LoginDatabase.PExecute("REPLACE INTO account_mute_history VALUES ('%u', '%s', '%s', '%s', '%u', NOW())", accountId, targetName.c_str(), reason.c_str(), muteBy.c_str(), 30);

        // pussywizard: notify all online GMs
        TRINITY_READ_GUARD(HashMapHolder<Player>::LockType, *HashMapHolder<Player>::GetLock());
        HashMapHolder<Player>::MapType const& m = sObjectAccessor->GetPlayers();
        for (HashMapHolder<Player>::MapType::const_iterator itr = m.begin(); itr != m.end(); ++itr)
            if (itr->second->GetSession()->GetSecurity())
                ChatHandler(itr->second->GetSession()).PSendSysMessage(target ? LANG_YOU_DISABLE_CHAT : LANG_COMMAND_DISABLE_CHAT_DELAYED, (handler->GetSession() ? handler->GetSession()->GetPlayerName().c_str() : "Console"), nameLink.c_str(), 30, reason.c_str());

        return true;
    }
};

void AddSC_custom_commandscript()
{
    new custom_commandscript();
}
