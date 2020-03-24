

/* ScriptData
Name: account_commandscript
%Complete: 100
Comment: All account related commands
Category: commandscripts
EndScriptData */

#include "AccountMgr.h"
#include "Chat.h"
#include "Language.h"
#include "Player.h"
#include "ScriptMgr.h"

class account_commandscript : public CommandScript
{
public:
    account_commandscript() : CommandScript("account_commandscript") { }

    std::vector<ChatCommand> GetCommands() const
    {
        static std::vector<ChatCommand> commandTable =
        {
            { "account",               SEC_PLAYER,         CMD_INGAME, &HandleAccountCommand,             "" },
            { "money",                 SEC_PLAYER,         CMD_INGAME, &HandleAccountMoneyCommand,        "" }
        };
        return commandTable;
    }

    static bool HandleAccountCommand(ChatHandler* handler, char const* /*args*/)
    {
        AccountTypes gmLevel = handler->GetSession()->GetSecurity();
        handler->PSendSysMessage(LANG_ACCOUNT_LEVEL, uint32(gmLevel));
        return true;
    }

    static bool HandleAccountMoneyCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* target = handler->GetSession()->GetPlayer();

        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ACCOUNT_BY_NAME);
        stmt->setString(0, target->GetName());

        PreparedQueryResult result = CharacterDatabase.Query(stmt);

        if (result) 
        {
            Field* field = result->Fetch();

            QueryResult sunwellCoins = LoginDatabase.PQuery("SELECT dp FROM account WHERE id = %u", field[0].GetUInt32());
            if (sunwellCoins)
                handler->PSendSysMessage("Posiadasz: %u Sunwell Coins.", sunwellCoins->Fetch()->GetUInt32());

            return true;
        }
        return false;
    }
};

void AddSC_account_commandscript()
{
    new account_commandscript();
}
