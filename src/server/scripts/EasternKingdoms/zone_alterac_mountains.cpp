/*
 * Copyright (C) 
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
SDName: Alterac_Mountains
SD%Complete: 0
SDComment: Placeholder
SDCategory: Alterac Mountains
EndScriptData */

/* ContentData
EndContentData */
   
#include "ScriptMgr.h"
#include "ScriptedCreature.h"

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
                if (playerWho->ToPlayer()->GetQuestStatus(QUEST_GOLDIR) == QUEST_STATUS_INCOMPLETE)
                    playerWho->AreaExploredOrEventHappens(QUEST_GOLDIR);
        }

    };
};

void AddSC_alterac_mountains()
{
    new npc_goldir();
}
