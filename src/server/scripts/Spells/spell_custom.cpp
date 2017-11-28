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

#include "ScriptMgr.h"
#include "SpellScript.h"

// @kruulevent
class spell_cust_shadow_crash_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_cust_shadow_crash_SpellScript)

    void HandleSchoolDMG(SpellEffIndex effIndex)
    {
        Player* target = GetHitPlayer();
           
        if (!target)
            return;

        if (target->GetMap()->Instanceable())
            return;

        float horizontalSpeed = 20.0f + (40.0f - GetCaster()->GetDistance(target));
        float verticalSpeed = 8.0f;
        // This method relies on the Dalaran Sewer map disposition and Water Spout position
        // What we do is knock the player from a position exactly behind him and at the end of the pipe
        target->KnockbackFrom(target->GetPositionX(), target->GetPositionY(), horizontalSpeed, verticalSpeed);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_cust_shadow_crash_SpellScript::HandleSchoolDMG, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// @kruulevent
class spell_cust_thunder_clap_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_cust_thunder_clap_SpellScript)

    void HandleSchoolDMG(SpellEffIndex effIndex)
    {
        Player* target = GetHitPlayer();

        if (!target)
            return;

        if (target->GetMap()->Instanceable())
            return;
            
        // Silence
        target->AddAura(29943, target);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_cust_thunder_clap_SpellScript::HandleSchoolDMG, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_custom_spell_scripts()
{
    // ours:
    new SpellScriptLoaderEx<spell_cust_shadow_crash_SpellScript>("spell_cust_shadow_crash");
    new SpellScriptLoaderEx<spell_cust_thunder_clap_SpellScript>("spell_cust_thunder_clap");
}
