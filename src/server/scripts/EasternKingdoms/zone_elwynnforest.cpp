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
SDName: Elwynn_Forest
SD%Complete: 0
SDComment: Placeholder
SDCategory: Elwynn Forest
EndScriptData */

/* ContentData
EndContentData */
   
#include "ScriptMgr.h"
#include "ScriptedCreature.h"

/*######
## npc_elwynn_wolf
######*/

uint32 Northshire[8][9]
{
    { 79946, 80156, 80164, 80165, 79928, 79938, 80140, 80141, 80142 },
    { 80143, 80144, 80176, 80261, 79945, 79961, 80157, 79936, 79937 },
    { 79933, 79934, 79935, 79939, 80134, 80135, 80139, 80129, 80138 },
    { 80146, 79954, 79957, 79959, 79960, 79940, 79941, 79955, 79956 },
    { 79958, 80130, 80131, 80136, 80113, 79974, 79985, 79987, 79988 },
    { 79989, 79990, 79975, 79976, 79977, 79978, 79980, 79981, 79982 },
    { 79983, 79984, 80007, 79979, 80006, 80106, 80101, 79997, 80009 },
    { 80025, 80027, 80040, 80043, 80008, 80010, 80041, 80042, 80161 }
};
class npc_elwynn_wolf : public CreatureScript
{
public:
    npc_elwynn_wolf() : CreatureScript("npc_elwynn_wolf") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_elwynn_wolfAI(creature);
    }

    struct npc_elwynn_wolfAI : public ScriptedAI
    {
        npc_elwynn_wolfAI(Creature* creature) : ScriptedAI(creature) { NorthshireWolf = false; }

        void Reset() override
        {
            if (!NorthshireWolf)
                CheckNorthshire();
        }

        void MoveInLineOfSight(Unit* who) override
        { 
            if (!who || NorthshireWolf)
                return;

            ScriptedAI::MoveInLineOfSight(who);
        }

        void CheckNorthshire()
        {
            for (uint8 i = 0; i < 8; ++i)
                for (uint8 j = 0; j < 9; ++j)
                    if (me->GetDBTableGUIDLow() == Northshire[i][j])
                        NorthshireWolf = true;
        }
        private:
            bool NorthshireWolf;
    };
};

void AddSC_zone_elwynn_forest()
{
    new npc_elwynn_wolf();
}
