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

/*
Blasted_Lands
Quest support: 3628. Teleporter to Rise of the Defiler.
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SpellScript.h"
#include "Player.h"
#include "Group.h"

/*#####
# spell_razelikh_teleport_group
#####*/

enum DeathlyUsher
{
    SPELL_TELEPORT_SINGLE               = 12885,
    SPELL_TELEPORT_SINGLE_IN_GROUP      = 13142,
    SPELL_TELEPORT_GROUP                = 27686
};

class spell_razelikh_teleport_group : public SpellScriptLoader
{
    public: spell_razelikh_teleport_group() : SpellScriptLoader("spell_razelikh_teleport_group") { }

        class spell_razelikh_teleport_group_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_razelikh_teleport_group_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_TELEPORT_SINGLE) && !sSpellMgr->GetSpellInfo(SPELL_TELEPORT_SINGLE_IN_GROUP))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex /* effIndex */)
            {
                if (Player* player = GetHitPlayer())
                {
                    if (Group* group = player->GetGroup())
                    {
                        for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
                            if (Player* member = itr->GetSource())
                                if (member->IsWithinDistInMap(player, 20.0f) && !member->isDead())
                                    member->CastSpell(member, SPELL_TELEPORT_SINGLE_IN_GROUP, true);
                    }
                    else
                        player->CastSpell(player, SPELL_TELEPORT_SINGLE, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_razelikh_teleport_group_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_razelikh_teleport_group_SpellScript();
        }
};

enum StoneOfBindin
{
    NPC_RAZELIKH            = 7668,
    NPC_GOL                 = 7669,
    NPC_ALLISTARJ           = 7670,
    NPC_SEVINE              = 7671,

    SPELL_RAZELIKH          = 10805,
    SPELL_GOL               = 10834,
    SPELL_ALLISTARJ         = 10835,
    SPELL_SEVINE            = 10836,

    GO_RAZELIKH             = 141812,
    GO_GOL                  = 141857,
    GO_ALLISTARJ            = 141858,
    GO_SEVINE               = 141859
};

class go_stone_of_binding : public GameObjectScript
{
public:
    go_stone_of_binding() : GameObjectScript("go_stone_of_binding") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        go->SetRespawnTime(60);
        go->SetLootState(GO_JUST_DEACTIVATED);

        switch (go->GetEntry()) {
            case GO_RAZELIKH:
                servantEntry = NPC_RAZELIKH;
                spellId = SPELL_RAZELIKH;
                break;
            case GO_GOL:
                servantEntry = NPC_GOL;
                spellId = SPELL_GOL;
                break;
            case GO_ALLISTARJ:
                servantEntry = NPC_ALLISTARJ;
                spellId = SPELL_ALLISTARJ;
                break;
            case GO_SEVINE:
                servantEntry = NPC_SEVINE;
                spellId = SPELL_SEVINE;
                break;
        }

        if (servantEntry)
            if (Creature* cr = go->FindNearestCreature(servantEntry, 10.0f))
                go->CastSpell(cr, spellId);
        return false;
    }

private:
    uint32 servantEntry;
    uint32 spellId;
};

void AddSC_blasted_lands()
{
    new spell_razelikh_teleport_group();
    new go_stone_of_binding();
}
