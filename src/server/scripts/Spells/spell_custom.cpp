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
 * Scripts for spells with SPELLFAMILY_GENERIC which cannot be included in AI script file
 * of creature using it or can't be bound to any player class.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_gen_"
 */

#include "ScriptMgr.h"
#include "Battlefield.h"
#include "BattlefieldMgr.h"
#include "Battleground.h"
#include "BattlegroundMgr.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Group.h"
#include "InstanceScript.h"
#include "LFGMgr.h"
#include "Pet.h"
#include "ReputationMgr.h"
#include "SkillDiscovery.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Chat.h"
#include "Vehicle.h"


// @kruulevent
class spell_cust_shadow_crash : public SpellScriptLoader
{
public:
    spell_cust_shadow_crash() : SpellScriptLoader("spell_cust_shadow_crash") { }

    class spell_cust_shadow_crash_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_cust_shadow_crash_SpellScript)

        void HandleSchoolDMG(SpellEffIndex effIndex)
        {
           Player* target = GetHitPlayer();
           
           if (!target || target->GetMap()->Instanceable())
               return;

           float horizontalSpeed = 20.0f + (40.0f - GetCaster()->GetDistance(target));
           float verticalSpeed = 8.0f;
           // This method relies on the Dalaran Sewer map disposition and Water Spout position
           // What we do is knock the player from a position exactly behind him and at the end of the pipe
           target->KnockbackFrom(target->GetPositionX(), target->GetPositionY(), horizontalSpeed, verticalSpeed);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_cust_shadow_crash_SpellScript::HandleSchoolDMG, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_cust_shadow_crash_SpellScript();
    }

};

// @kruulevent
class spell_cust_thunder_clap : public SpellScriptLoader
{
public:
    spell_cust_thunder_clap() : SpellScriptLoader("spell_cust_thunder_clap") { }

    class spell_cust_thunder_clap_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_cust_thunder_clap_SpellScript)

        void HandleSchoolDMG(SpellEffIndex effIndex)
        {
            Player* target = GetHitPlayer();

            if (!target || target->GetMap()->Instanceable())
                return;
            
            // Silence
            target->AddAura(29943, target);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_cust_thunder_clap_SpellScript::HandleSchoolDMG, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_cust_thunder_clap_SpellScript();
    }

};

void AddSC_custom_spell_scripts()
{
    // ours:
    new spell_cust_shadow_crash();
    new spell_cust_thunder_clap();
}
