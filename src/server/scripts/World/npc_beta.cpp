/*
* Copyright (C) 2006-2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* Copyright (C) 2008-2014 Hellground <http://hellground.net/>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

/* ScriptData
SDName: 
SD%Complete: 100
SDComment: To be used for instant 60 custom quests.
SDCategory: NPCs
EndScriptData
*/

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "SpellAuras.h"
#include "Chat.h"

enum skills 
{
    CHECK_SKILL_ONE_HAND_AXE      = 196,
    CHECK_SKILL_TWO_HAND_AXE      = 197,
    CHECK_SKILL_ONE_HAND_MACE     = 198,
    CHECK_SKILL_TWO_HAND_MACE     = 199,
    CHECK_SKILL_POLEARMS          = 200,
    CHECK_SKILL_ONE_HAND_SWORD    = 201,
    CHECK_SKILL_TWO_HAND_SWORD    = 202,
    CHECK_SKILL_STAVES            = 227,
    CHECK_SKILL_BOWS              = 264,
    CHECK_SKILL_GUNS              = 266,
    CHECK_SKILL_DAGGERS           = 1180,
    CHECK_SKILL_THROWNS           = 2567,
    CHECK_SKILL_WANDS             = 5009,
    CHECK_SKILL_CROSSBOWS         = 5011,
    CHECK_SKILL_FIST              = 15590
};

class npc_beta : public CreatureScript
{
public:
    npc_beta() : CreatureScript("npc_beta") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        player->ADD_GOSSIP_ITEM(0, "Weapon skill, quest spells.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
            {
                player->CLOSE_GOSSIP_MENU();
                CheckHasWeaponSkill(player);
            } break;
        }
        return true;
    }


    bool CheckHasWeaponSkill(Player* player)
    {
        if (!player)
            return false;

        switch (player->getClass())
        {
                case CLASS_DRUID:
                {
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                    if (!player->HasSpell(CHECK_SKILL_TWO_HAND_MACE))
                        player->learnSpell(CHECK_SKILL_TWO_HAND_MACE);
                    if (!player->HasSpell(CHECK_SKILL_POLEARMS))
                        player->learnSpell(CHECK_SKILL_POLEARMS);
                    if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                        player->learnSpell(CHECK_SKILL_DAGGERS);
                    if (!player->HasSpell(CHECK_SKILL_STAVES))
                        player->learnSpell(CHECK_SKILL_STAVES);

                } break;
                case CLASS_HUNTER:
                {
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_AXE))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_AXE);
                    if (!player->HasSpell(CHECK_SKILL_TWO_HAND_SWORD))
                        player->learnSpell(CHECK_SKILL_TWO_HAND_SWORD);
                    if (!player->HasSpell(CHECK_SKILL_TWO_HAND_AXE))
                        player->learnSpell(CHECK_SKILL_TWO_HAND_AXE);
                    if (!player->HasSpell(CHECK_SKILL_POLEARMS))
                        player->learnSpell(CHECK_SKILL_POLEARMS);
                    if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                        player->learnSpell(CHECK_SKILL_DAGGERS);
                    if (!player->HasSpell(CHECK_SKILL_BOWS))
                        player->learnSpell(CHECK_SKILL_BOWS);
                    if (!player->HasSpell(CHECK_SKILL_GUNS))
                        player->learnSpell(CHECK_SKILL_GUNS);
                    if (!player->HasSpell(CHECK_SKILL_CROSSBOWS))
                        player->learnSpell(CHECK_SKILL_CROSSBOWS);
                } break;
                case CLASS_MAGE:
                {
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                    if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                        player->learnSpell(CHECK_SKILL_DAGGERS);
                    if (!player->HasSpell(CHECK_SKILL_STAVES))
                        player->learnSpell(CHECK_SKILL_STAVES);
                    if (!player->HasSpell(CHECK_SKILL_WANDS))
                        player->learnSpell(CHECK_SKILL_WANDS);
                } break;
                case CLASS_PALADIN:
                {
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_AXE))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_AXE);
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                    if (!player->HasSpell(CHECK_SKILL_TWO_HAND_SWORD))
                        player->learnSpell(CHECK_SKILL_TWO_HAND_SWORD);
                    if (!player->HasSpell(CHECK_SKILL_TWO_HAND_AXE))
                        player->learnSpell(CHECK_SKILL_TWO_HAND_AXE);
                    if (!player->HasSpell(CHECK_SKILL_TWO_HAND_MACE))
                        player->learnSpell(CHECK_SKILL_TWO_HAND_MACE);
                    if (!player->HasSpell(CHECK_SKILL_POLEARMS))
                        player->learnSpell(CHECK_SKILL_POLEARMS);
                } break;
                case CLASS_PRIEST:
                {
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                    if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                        player->learnSpell(CHECK_SKILL_DAGGERS);
                    if (!player->HasSpell(CHECK_SKILL_STAVES))
                        player->learnSpell(CHECK_SKILL_STAVES);
                    if (!player->HasSpell(CHECK_SKILL_WANDS))
                        player->learnSpell(CHECK_SKILL_WANDS);
                } break;
                case CLASS_ROGUE:
                {
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_AXE))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_AXE);
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                    if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                        player->learnSpell(CHECK_SKILL_DAGGERS);
                    if (!player->HasSpell(CHECK_SKILL_THROWNS))
                        player->learnSpell(CHECK_SKILL_THROWNS);
                } break;
                case CLASS_SHAMAN:
                {
                    if (!player->HasSpell(CHECK_SKILL_FIST))
                        player->learnSpell(CHECK_SKILL_FIST);
                    if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                        player->learnSpell(CHECK_SKILL_DAGGERS);
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                    if (!player->HasSpell(CHECK_SKILL_STAVES))
                        player->learnSpell(CHECK_SKILL_STAVES);
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_AXE))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_AXE);
                    if (!player->HasSpell(CHECK_SKILL_TWO_HAND_AXE))
                        player->learnSpell(CHECK_SKILL_TWO_HAND_AXE);
                    if (!player->HasSpell(CHECK_SKILL_TWO_HAND_MACE))
                        player->learnSpell(CHECK_SKILL_TWO_HAND_MACE);
                } break;
                case CLASS_WARLOCK:
                {
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                    if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                        player->learnSpell(CHECK_SKILL_DAGGERS);
                    if (!player->HasSpell(CHECK_SKILL_STAVES))
                        player->learnSpell(CHECK_SKILL_STAVES);
                    if (!player->HasSpell(CHECK_SKILL_WANDS))
                        player->learnSpell(CHECK_SKILL_WANDS);
                } break;
                case CLASS_WARRIOR:
                {
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_AXE))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_AXE);
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                    if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                        player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                    if (!player->HasSpell(CHECK_SKILL_TWO_HAND_AXE))
                        player->learnSpell(CHECK_SKILL_TWO_HAND_AXE);
                    if (!player->HasSpell(CHECK_SKILL_TWO_HAND_MACE))
                        player->learnSpell(CHECK_SKILL_TWO_HAND_MACE);
                    if (!player->HasSpell(CHECK_SKILL_TWO_HAND_SWORD))
                        player->learnSpell(CHECK_SKILL_TWO_HAND_SWORD);
                    if (!player->HasSpell(CHECK_SKILL_POLEARMS))
                        player->learnSpell(CHECK_SKILL_POLEARMS);
                    if (!player->HasSpell(CHECK_SKILL_BOWS))
                        player->learnSpell(CHECK_SKILL_BOWS);
                    if (!player->HasSpell(CHECK_SKILL_THROWNS))
                        player->learnSpell(CHECK_SKILL_THROWNS);
                    if (!player->HasSpell(CHECK_SKILL_GUNS))
                        player->learnSpell(CHECK_SKILL_GUNS);
                    if (!player->HasSpell(CHECK_SKILL_CROSSBOWS))
                        player->learnSpell(CHECK_SKILL_CROSSBOWS);

                } break;
        }
        return true;
    }

    struct npc_betaAI : public ScriptedAI
    {
        npc_betaAI(Creature* creature) : ScriptedAI(creature) {}

    };
};

void AddSC_npc_beta()
{
    new npc_beta();
}