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
#include "ObjectMgr.h"

class custom_commandscript : public CommandScript
{
public:
    custom_commandscript() : CommandScript("custom_commandscript") { }

    std::vector<ChatCommand> GetCommands() const
    {
        static std::vector<ChatCommand> commandTable =
        {
            { "service",            SEC_ADMINISTRATOR,      CMD_CLI,  &HandleServiceCommand,               "" },
            { "blizzlike",          SEC_PLAYER,             CMD_INGAME, HandleBlizzlikeCommand,              "" },
            { "pvpinfo",            SEC_PLAYER,             CMD_INGAME, HandlePvPInfoCommand,                "" },
            { "dodge",              SEC_PLAYER,             CMD_INGAME, HandleDodgeModeCommand,              "" },
            { "hasblizzlike",       SEC_MODERATOR,          CMD_INGAME, HandleHasBlizzlikeCommand,           "" },
            { "goldban",            SEC_MODERATOR,          CMD_INGAME, &HandleGoldBanCommand,               "" },
            { "speedban",           SEC_MODERATOR,          CMD_INGAME, &HandleSpeedBanCommand,              "" },
            { "englishmute",        SEC_MODERATOR,          CMD_INGAME, &HandleEnglishMuteCommand,           "" },
            { "iccreset",           SEC_MODERATOR,          CMD_INGAME, HandleICCResetCommand,               "" },
            { "bonusxp",            SEC_ADMINISTRATOR,      CMD_CLI,  &HandleBonusXpCommand,               "" },
            { "ninjains",           SEC_GAMEMASTER,         CMD_INGAME, &HandleInsertNinjaCommand,           "" },
            { "ninjalist",          SEC_PLAYER,             CMD_INGAME, &HandleSelectNinjaCommand,           "" },
            { "ninjadel",           SEC_GAMEMASTER,         CMD_INGAME, &HandleDeleteNinjaCommand,           "" },
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
            handler->PSendSysMessage(LANG_BLIZZLIKE_ON);
            handler->SetSentErrorMessage(true);
        }
        else
        {
            player->SetBlizzlikeMode(false);
            handler->PSendSysMessage(LANG_BLIZZLIKE_OFF);
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
            handler->PSendSysMessage(LANG_PVP_ANNOUNCEMENTS_ON);
            handler->SetSentErrorMessage(true);
        }
        else
        {
            player->SetPvPAnnounces(false);
            handler->PSendSysMessage(LANG_PVP_ANNOUNCEMENTS_OFF);
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
            handler->PSendSysMessage(LANG_DODGE_NO_RATING);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!player->IsInDodgeMode())
        {
            player->SetDodgeMode(true);
            handler->PSendSysMessage(LANG_DODGE_ON);
            handler->SetSentErrorMessage(true);
        }
        else
        {
            player->SetDodgeMode(false);
            handler->PSendSysMessage(LANG_DODGE_OFF);
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
            handler->PSendSysMessage(LANG_HAS_BLIZZLIKE_ON, player->GetName().c_str());
        else
            handler->PSendSysMessage(LANG_HAS_BLIZZLIKE_OFF, player->GetName().c_str());

        return true;
    }

    // GoldBan!
    static bool HandleGoldBanCommand(ChatHandler* handler, char const* args)
    {
        Player* target;
        uint64 targetGuid;
        std::string targetName;
        std::string accountName;

        if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid, &targetName))
            return false;

        uint32 accountId = target ? target->GetSession()->GetAccountId() : sObjectMgr->GetPlayerAccountIdByGUID(targetGuid);

        if (target == handler->GetSession()->GetPlayer())
            return false;

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

        sLog->outBan("Game Master: [%s] has banned player: [%s] for gold selling. (30 days)", handler->GetSession()->GetPlayerName().c_str(), targetName.c_str());
        sWorld->SendGMText(LANG_GOLD_BAN, handler->GetSession()->GetPlayerName().c_str(), targetName.c_str());

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

        if (target == handler->GetSession()->GetPlayer())
            return false;

        if (target)
        {
            // check online security
            if (handler->HasLowerSecurity(target, 0))
                return false;

            if (AccountMgr::GetName(target->GetSession()->GetAccountId(), accountName))
                sWorld->BanAccount(BAN_ACCOUNT, accountName.c_str(), "7d", "Speed Hack.", handler->GetSession() ? handler->GetSession()->GetPlayerName() : "");
        }
        else
        {
            // check offline security
            if (handler->HasLowerSecurity(NULL, targetGuid))
                return false;

            if (AccountMgr::GetName(accountId, accountName))
                sWorld->BanAccount(BAN_ACCOUNT, accountName.c_str(), "7d", "Speed Hack.", handler->GetSession() ? handler->GetSession()->GetPlayerName() : "");
        }

        sLog->outBan("Game Master: [%s] has banned player: [%s] for speed hack. (7 days)", handler->GetSession()->GetPlayerName().c_str(), targetName.c_str());
        sWorld->SendGMText(LANG_SPEED_BAN, handler->GetSession()->GetPlayerName().c_str(), targetName.c_str());

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
        if (sWorld->getBoolConfig(CONFIG_MUTE_HISTORY))
        {
            uint32 rId = sWorld->getBoolConfig(CONFIG_SPECIAL_ANGRATHAR) ? 2 : 1;

            stmt = LoginDatabase.GetPreparedStatement(LOGIN_REP_MUTE_HISTORY);
            stmt->setUInt32(0, accountId);
            stmt->setString(1, targetName.c_str());
            stmt->setString(2, reason.c_str());
            stmt->setString(3, muteBy.c_str());
            stmt->setUInt32(4, 30);
            stmt->setUInt32(5, rId);
            LoginDatabase.Execute(stmt);
        }

        sWorld->SendGMText(target ? LANG_YOU_DISABLE_CHAT : LANG_COMMAND_DISABLE_CHAT_DELAYED, (handler->GetSession() ? handler->GetSession()->GetPlayerName().c_str() : "Console"), nameLink.c_str(), 30, reason.c_str());

        return true;
    }

    static bool HandleICCResetCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        uint32 iccMapID = 631;

        if (!player)
            return false;

        if (player->GetMap()->Instanceable())
        {
            handler->PSendSysMessage("You can't do that here.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
            sInstanceSaveMgr->PlayerUnbindInstance(player->GetGUIDLow(), iccMapID, Difficulty(i), true, player);

        handler->PSendSysMessage("ICC has been successfully reset.");
        return true;
    }

    // Event x4
    static bool HandleBonusXpCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        // Account Name
        char* aname = strtok((char*)args, " ");
        if (!aname)
            return false;

        std::string accName = aname;
        std::string serviceName;      // To display on output command and log

        // convert accountname to account ID
        PreparedStatement*  stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_ACCOUNT_ID_BY_NAME);
        stmt->setString(0, accName);
        PreparedQueryResult result = LoginDatabase.Query(stmt);

        if (!result)
            return false;

        uint32 accId = 0;
        Field* fields = result->Fetch();
        accId = fields[0].GetUInt32();

        uint32 premiumTime = 4 * DAY; // duration of premium service
        time_t extraTime;             // is time left of previous active service, if no result then null

        // Query check for previous premium service, if there is result stack the time of premium service
        PreparedStatement* stmt2 = LoginDatabase.GetPreparedStatement(LOGIN_SEL_PREMIUM_TIME_BY_ID);
        stmt2->setUInt32(0, accId);
        stmt2->setUInt32(1, realmID);
        stmt2->setUInt8(2, SERVICE_EXP_BOOST_X4);
        PreparedQueryResult timeResult = LoginDatabase.Query(stmt2);

        if (timeResult)
        {
            Field* timeFields = timeResult->Fetch();
            extraTime = time_t(timeFields[1].GetUInt32());
            premiumTime = premiumTime + extraTime;
            handler->PSendSysMessage("Warning! Account: %s already got X4 bonus.", accName.c_str());
        }
        else
            premiumTime = time(nullptr) + premiumTime;

        stmt = LoginDatabase.GetPreparedStatement(LOGIN_REP_ACCOUNT_PREMIUM);
        stmt->setUInt32(0, accId);
        stmt->setUInt32(1, realmID);
        stmt->setUInt8(2, SERVICE_EXP_BOOST_X4);
        stmt->setUInt32(3, time(nullptr));
        stmt->setUInt32(4, premiumTime);
        LoginDatabase.Execute(stmt);
        serviceName = "SERVICE_EXP_BOOST_X4";

        handler->PSendSysMessage("You have enabled service '%s' on account %s for 4 days.", serviceName.c_str(), accName.c_str());
        sLog->outPremium("Service '%s' has been enabled on account %s for 4 days.", serviceName.c_str(), accName.c_str());
        return true;
    }

    static PreparedQueryResult SelectNinjaLooter( uint32 loGuid )
    {
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_NINJA_LOOTER_PER_GUID);
        stmt->setUInt32(0, loGuid);

        return std::move(CharacterDatabase.Query(stmt));
    };

    static bool HandleInsertNinjaCommand(ChatHandler* handler, char const* args)
    {
        if (!sWorld->getBoolConfig(CONFIG_NINJA_LOOTER_LIST))
        {
            handler->SendSysMessage("Feature disabled.");
            return true;
        }

        char* nameStr;
        char* postStr;
        handler->extractOptFirstArg((char*)args, &nameStr, &postStr);

        if (postStr == nullptr || ( !atoi(postStr) && postStr != "0" ))
            return false;

        uint64 targetGuid;
        std::string targetName;
        if (!handler->extractPlayerTarget(nameStr, nullptr, &targetGuid, &targetName))
            return false;

        uint32 loGuid = GUID_LOPART(targetGuid);
        uint32 postId = atoi(postStr);

        if (PreparedQueryResult result = SelectNinjaLooter(loGuid))
        {
            Field* fields = result->Fetch();

            uint32 postId = fields[2].GetUInt32();
            handler->PSendSysMessage( "Player: %s (Guid: %u) has already been added to ninja looter list with forum report ID: %u", targetName.c_str(), loGuid, postId);
            return true;
        }

        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_NINJA_LOOTER);
        stmt->setUInt32(0, loGuid);
        stmt->setString(1, targetName);
        stmt->setUInt32(2, postId);
        CharacterDatabase.DirectExecute(stmt);

        if (PreparedQueryResult result = SelectNinjaLooter(loGuid))
            handler->PSendSysMessage("Player: %s (Guid: %u) has been added to ninja looter list with forum report ID: %u", targetName.c_str(), loGuid, postId);
        else
            handler->PSendSysMessage("Something went wrong! Probably wrong name or missing report Id?");

        return true;
    }

    static bool HandleDeleteNinjaCommand(ChatHandler* handler, char const* args)
    {
        if (!sWorld->getBoolConfig(CONFIG_NINJA_LOOTER_LIST))
        {
            handler->SendSysMessage("Feature disabled.");
            return true;
        }

        if (!*args)
            return false;

        char* input = strtok((char*)args, " ");
        if (input == nullptr || (!atoi(input) && input != "0"))
            return false;

        uint32 loGuid = GUID_LOPART( atoi( input ) );

        if (PreparedQueryResult result = SelectNinjaLooter(loGuid))
            handler->PSendSysMessage("Player GUID: %u going to be removed from the Ninja List.", loGuid);
        else
        {
            handler->PSendSysMessage("Cannot find player with GUID: %u on the list, maybe already removed?", loGuid);
            return true;
        }

        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_NINJA_LOOTER);
        stmt->setUInt32(0, loGuid);
        CharacterDatabase.Execute(stmt);
        return true;
    }

    static bool HandleSelectNinjaCommand(ChatHandler* handler, char const* /*args*/)
    {
        if (!sWorld->getBoolConfig(CONFIG_NINJA_LOOTER_LIST))
        {
            handler->SendSysMessage("Feature disabled.");
            return true;
        }

        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_NINJA_LOOTER);

        handler->PSendSysMessage( "--- Sunwell Ninja List begin ---" );
        if (PreparedQueryResult result = CharacterDatabase.Query(stmt))
        {
            do
            {
                Field *fields = result->Fetch();

                uint32 guid      = fields[0].GetUInt32();
                std::string name = fields[1].GetString();
                uint32 reportId  = fields[2].GetUInt32();

                //! Check for real player name
                sObjectMgr->GetPlayerNameByGUID( guid, name );

                WorldSession* session = handler->GetSession();
                if ( session != nullptr && session->GetSecurity() > SEC_PLAYER )
                {
                    handler->PSendSysMessage( "Player: %s (GUID: %u) is on Ninja List! Report ID: %u", name.c_str(), guid, reportId );
                }
                else
                {
                    handler->PSendSysMessage( "Player: %s is on Ninja List! Report ID: %u", name.c_str(), reportId );
                }

            } while (result->NextRow());
        }

        handler->PSendSysMessage( "--- Sunwell Ninja List end ---" );

        return true;
    }
};

void AddSC_custom_commandscript()
{
    new custom_commandscript();
}
