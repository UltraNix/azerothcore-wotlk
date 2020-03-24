
/* ScriptData
SDName: Alterac_Mountains
SD%Complete: 0
SDComment: Placeholder
SDCategory: Alterac Mountains
EndScriptData */

/* ContentData
EndContentData */
   
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Player.h"

/*######
## npc_goldir
######*/

#define QUEST_GOLDIR 503

class npc_goldir : public CreatureScript
{
public:
    npc_goldir() : CreatureScript("npc_goldir") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_goldirAI(creature);
    }

    struct npc_goldirAI : public ScriptedAI
    {
        npc_goldirAI(Creature* creature) : ScriptedAI(creature) { }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!who || who->GetTypeId() != TYPEID_PLAYER || !me->IsWithinDist(who, 10.0f))
                return;

            if (Player* playerWho = who->ToPlayer())
                if (playerWho->GetQuestStatus(QUEST_GOLDIR) == QUEST_STATUS_INCOMPLETE)
                    playerWho->AreaExploredOrEventHappens(QUEST_GOLDIR);
        }

    };
};

void AddSC_alterac_mountains()
{
    new npc_goldir();
}
