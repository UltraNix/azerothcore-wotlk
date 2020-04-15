

/* ScriptData
Name: message_commandscript
%Complete: 100
Comment: All message related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "Chat.h"
#include "ChannelMgr.h"
#include "Language.h"
#include "Player.h"

class message_commandscript : public CommandScript
{
public:
    message_commandscript() : CommandScript("message_commandscript") { }

    std::vector<ChatCommand> GetCommands() const
    {
        static std::vector<ChatCommand> commandTable =
        {
            { "nameannounce",   SEC_GAMEMASTER,      CMD_CLI,   &HandleNameAnnounceCommand,         "" },
            { "gmnameannounce", SEC_GAMEMASTER,      CMD_CLI,   &HandleGMNameAnnounceCommand,       "" },
            { "announce",       SEC_GAMEMASTER,      CMD_CLI,   &HandleAnnounceCommand,             "" },
            { "gmannounce",     SEC_GAMEMASTER,      CMD_CLI,   &HandleGMAnnounceCommand,           "" },
            { "notify",         SEC_GAMEMASTER,      CMD_CLI,   &HandleNotifyCommand,               "" },
            { "gmnotify",       SEC_GAMEMASTER,      CMD_CLI,   &HandleGMNotifyCommand,             "" },
            { "whispers",       SEC_GAMEMASTER,      CMD_INGAME,  &HandleWhispersCommand,             "" },
            { "annhorde",       SEC_ADMINISTRATOR,  CMD_INGAME,   &HandleAnnHordeCommand,             "" },
            { "annalliance",    SEC_ADMINISTRATOR,  CMD_INGAME,   &HandleAnnAllianceCommand,          "" },
        };
        return commandTable;
    }

    static bool HandleNameAnnounceCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        std::string name("Console");
        if (WorldSession* session = handler->GetSession())
            name = session->GetPlayer()->GetName();

        sWorld->SendWorldText(LANG_ANNOUNCE_COLOR, name.c_str(), args);
        return true;
    }

    static bool HandleGMNameAnnounceCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        std::string name("Console");
        if (WorldSession* session = handler->GetSession())
            name = session->GetPlayer()->GetName();

        sWorld->SendGMText(LANG_GM_ANNOUNCE_COLOR, name.c_str(), args);
        return true;
    }
    // global announce
    static bool HandleAnnounceCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char buff[2048];
        sprintf(buff, handler->GetTrinityString(LANG_SYSTEMMESSAGE), args);
        sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
        return true;
    }
    // announce to logged in GMs
    static bool HandleGMAnnounceCommand(ChatHandler* /*handler*/, char const* args)
    {
        if (!*args)
            return false;

        sWorld->SendGMText(LANG_GM_BROADCAST, args);
        return true;
    }
    // notification player at the screen
    static bool HandleNotifyCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        std::string str = handler->GetTrinityString(LANG_GLOBAL_NOTIFY);
        str += args;

        WorldPacket data(SMSG_NOTIFICATION, (str.size()+1));
        data << str;
        sWorld->SendGlobalMessage(&data);

        return true;
    }
    // notification GM at the screen
    static bool HandleGMNotifyCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        std::string str = handler->GetTrinityString(LANG_GM_NOTIFY);
        str += args;

        WorldPacket data(SMSG_NOTIFICATION, (str.size()+1));
        data << str;
        sWorld->SendGlobalGMMessage(&data);

        return true;
    }
    // Enable\Dissable accept whispers (for GM)
    static bool HandleWhispersCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
        {
            handler->PSendSysMessage(LANG_COMMAND_WHISPERACCEPTING, handler->GetSession()->GetPlayer()->isAcceptWhispers() ?  handler->GetTrinityString(LANG_ON) : handler->GetTrinityString(LANG_OFF));
            return true;
        }

        std::string argStr = (char*)args;
        // whisper on
        if (argStr == "on")
        {
            handler->GetSession()->GetPlayer()->SetAcceptWhispers(true);
            handler->SendSysMessage(LANG_COMMAND_WHISPERON);
            return true;
        }

        // whisper off
        if (argStr == "off")
        {
            // Remove all players from the Gamemaster's whisper whitelist
            handler->GetSession()->GetPlayer()->ClearWhisperWhiteList();
            handler->GetSession()->GetPlayer()->SetAcceptWhispers(false);
            handler->SendSysMessage(LANG_COMMAND_WHISPEROFF);
            return true;
        }

        handler->SendSysMessage(LANG_USE_BOL);
        handler->SetSentErrorMessage(true);
        return false;
    }

    static bool HandleAnnHordeCommand(ChatHandler* handler, char const* args)
    {
        if (!args)
            return false;
        return SendFactionAnnounce(handler, args, TEAM_HORDE);
    }

    static bool HandleAnnAllianceCommand(ChatHandler* handler, char const* args)
    {
        if (!args)
            return false;
        return SendFactionAnnounce(handler, args, TEAM_ALLIANCE);
    }

    static bool SendFactionAnnounce(ChatHandler* handler, char const* args, TeamId teamId)
    {
        char buff[2048];
        sprintf(buff, handler->GetTrinityString(LANG_SYSTEMMESSAGE), args);
        sWorld->SendServerMessage(SERVER_MSG_STRING, buff, nullptr, teamId);

        //Send additional ann to GM if he is from second faction
        Player *player = handler->GetSession()->GetPlayer();
        if (player && player->GetTeam(CrossFactionTeam::Discard) != teamId) {
            sWorld->SendServerMessage(SERVER_MSG_STRING, buff, player);
        }
        return true;
    }
};

void AddSC_message_commandscript()
{
    new message_commandscript();
}
