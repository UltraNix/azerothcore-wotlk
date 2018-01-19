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

class spell_cust_black_qiraji_battle_tank : public SpellScriptLoader
{
public:
    spell_cust_black_qiraji_battle_tank() : SpellScriptLoader("spell_cust_black_qiraji_battle_tank") { }

    class spell_cust_black_qiraji_battle_tank_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_cust_black_qiraji_battle_tank_SpellScript);

        SpellCastResult CheckRequirement()
        {
            Player* player = GetCaster()->ToPlayer();

            // Fix for bug that player could use this mount on another mount.
            if (player->IsMounted())
                return SPELL_FAILED_NOT_MOUNTED;

            // Fix for use this mount on falling or moving due to instant cast.
            if (player->isMoving() || player->IsFalling())
                return SPELL_FAILED_MOVING;

            // Disallow to use on Battlegrounds due to instant cast.
            if (player->GetMap()->IsBattleground())
                return SPELL_FAILED_NOT_IN_BATTLEGROUND;

            // Disallow to use on Arenas due to instant cast.
            if (player->GetMap()->IsBattleArena())
                return SPELL_FAILED_NOT_IN_ARENA;

            // Disallow to use on Wintergrasp due to instant cast.
            if (player->GetZoneId() == 4197)
                return SPELL_FAILED_NOT_IN_BATTLEGROUND;

            // Dalaran usage at Spell.cpp due to lack of CheckCast hook.
            return SPELL_CAST_OK;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_cust_black_qiraji_battle_tank_SpellScript::CheckRequirement);
        }
    };

    class spell_cust_black_qiraji_battle_tank_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_cust_black_qiraji_battle_tank_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();

            // Normal Case: Flying only on fly maps.
            //          Outland Map                  Northrend Map
            if (target->GetMapId() != 530 && target->GetMapId() != 571)
                HandleScript(target);

            // Special Case: Disallow to fly on Outland non-flying zones.
            //                                       Eversong Woods                 Ghostland                      Azuremyst Isle                 Bloodmyst Isle                 Silvermoon City                The Exodar                     // Isle of Quel'Danas
            if (target->GetMapId() == 530 && target->GetZoneId() == 3433 || target->GetZoneId() == 3433 || target->GetZoneId() == 3524 || target->GetZoneId() == 3525 || target->GetZoneId() == 3487 || target->GetZoneId() == 3557 || target->GetZoneId() == 4080)
                HandleScript(target);

            // Special Case: Allow to fly on Northrend map with Cold Weather Flying.
            if (target->GetMapId() == 571 && !target->HasSpell(54197))
                HandleScript(target);

            // Special Case: Allow to fly in Dalaran Krasus' Landing.
            if (target->GetZoneId() == 4395 && target->GetAreaId() != 4564)
                HandleScript(target);
        }

        void HandleScript(Unit* caster)
        {
            WorldPacket data(12);
            data.SetOpcode(SMSG_MOVE_UNSET_CAN_FLY);
            data.append(caster->GetPackGUID());
            data << uint32(0);                                      // unknown
            caster->SendMessageToSet(&data, true);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_cust_black_qiraji_battle_tank_AuraScript::OnApply, EFFECT_2, SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED, AURA_EFFECT_HANDLE_REAL);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_cust_black_qiraji_battle_tank_SpellScript();
    }

    AuraScript* GetAuraScript() const
    {
        return new spell_cust_black_qiraji_battle_tank_AuraScript();
    }
};

void AddSC_custom_spell_scripts()
{
    // ours:
    new SpellScriptLoaderEx<spell_cust_shadow_crash_SpellScript>("spell_cust_shadow_crash");
    new SpellScriptLoaderEx<spell_cust_thunder_clap_SpellScript>("spell_cust_thunder_clap");
    new spell_cust_black_qiraji_battle_tank();
}
