#include "Language.h"
#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include "World.h"
#include "ArenaTeamMgr.h"

class arena_commandscript : public CommandScript
{
public:
    arena_commandscript() : CommandScript("arena_commandscript") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> arenaCommandTable =
        {
            { "setpersonalrating",         SEC_GAMEMASTER,      CMD_CLI,  &HandleArenaSetPersonalRating,         "" },
        };

        static std::vector<ChatCommand> commandTable =
        {
            { "arena",      SEC_MODERATOR,     CMD_CLI, NULL,                     "",  arenaCommandTable}
        };

        return commandTable;
    }

    static bool HandleArenaSetPersonalRating(ChatHandler* handler, const char* args)
    {
        //! args: player GUID, arena type, new personal rating
        if (!args)
        {
            handler->PSendSysMessage("No arguments, returning. Syntax: arena setpersonalrating playerName arenaSlot(0 - 2s, 1 - 3s, 2 - 5s)"
                "new personalRating (ex. arena setpersonalrating test 0 2000");
            return false;
        }

        char* c_PlayerName = strtok((char*)args, " ");
        if (!c_PlayerName)
            return false;

        std::string playerName(c_PlayerName);
        char* cArenaSlot = strtok(nullptr, " ");
        if (!cArenaSlot)
            return false;

        uint32 arenaSlot = atoi(cArenaSlot);
        char* cPersonalRating = strtok(nullptr, " ");
        if (!cPersonalRating)
            return false;

        uint32 newPersonalRating = atoi(cPersonalRating);

        if (!normalizePlayerName(playerName))
            return false;

        Player* player = ObjectAccessor::FindPlayerByName(playerName);
        if (!player)
        {
            handler->PSendSysMessage("Couldn't find player (%s), either wrong name or player is offline", playerName);
            return true;
        }

        uint32 playerLowGUID = player->GetGUIDLow();
        GlobalPlayerData const* playerCache = sWorld->GetGlobalPlayerData(playerLowGUID);
        if (!playerCache)
        {
            handler->PSendSysMessage("Global cache for LowGuid %u doesnt exist.", playerLowGUID);
            return true;
        }

        if (arenaSlot > MAX_ARENA_SLOT)
        {
            handler->PSendSysMessage("Invalid arena slot, valid arena slots: 0 for 2s, 1 for 3s and 2 for 5s");
            return true;
        }

        uint32 arenaTeamId = playerCache->arenaTeamId[arenaSlot];

        if (ArenaTeam* at = sArenaTeamMgr->GetArenaTeamById(arenaTeamId))
        {
            if (at->IsFighting())
            {
                handler->PSendSysMessage("Arena team %s is currently fighting, cannot change personal rating.", at->GetName());
                return true;
            }

            at->ForcePersonalRatingChange(player, newPersonalRating, 0);
            at->SaveToDB();
            handler->PSendSysMessage("Successfuly changed personal rating and matchmaking rating to (%u) for player (%s)", newPersonalRating, player->GetName());
            return true;
        }
        else
        {
            handler->PSendSysMessage("Something went wrong, arena team with arena team id %u doesnt exist.", arenaSlot);
            return true;
        }

        return false;
    }
};

void AddSC_arena_commandscript()
{
    new arena_commandscript();
}
