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

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "molten_core.h"

enum Emotes
{
    EMOTE_SERVICE
};

enum Spells
{
    SPELL_INFERNO           = 19695,
    SPELL_INFERNO_DAMAGE    = 35283,
    SPELL_IGNITE_MANA       = 19659,
    SPELL_LIVING_BOMB       = 20475,
    SPELL_ARMAGEDDON        = 20478,
};

enum Events
{
    EVENT_INFERNO           = 1,
    EVENT_IGNITE_MANA,
    EVENT_LIVING_BOMB,
};

struct boss_baron_geddonAI : public BossAI
{
    boss_baron_geddonAI(Creature* creature) : BossAI(creature, BOSS_BARON_GEDDON) {}

    void EnterCombat(Unit* /*victim*/) override
    {
        _EnterCombat();
        events.ScheduleEvent(EVENT_INFERNO, 45000);
        events.ScheduleEvent(EVENT_IGNITE_MANA, 30000);
        events.ScheduleEvent(EVENT_LIVING_BOMB, 35000);
        _armageddon = false;
    }

    void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
    {
        // If we are <2% hp and armagedon didn't start, cast Armageddon
        if (!HealthAbovePct(2) && !_armageddon)
        {
            me->InterruptNonMeleeSpells(true);
            Talk(EMOTE_SERVICE);
            DoCast(me, SPELL_ARMAGEDDON);
            _armageddon = true;
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_INFERNO:
                DoCast(me, SPELL_INFERNO);
                events.ScheduleEvent(EVENT_INFERNO, 45000);
                break;
            case EVENT_IGNITE_MANA:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true, -SPELL_IGNITE_MANA))
                    DoCast(target, SPELL_IGNITE_MANA);
                events.ScheduleEvent(EVENT_IGNITE_MANA, 30000);
                break;
            case EVENT_LIVING_BOMB:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                    DoCast(target, SPELL_LIVING_BOMB);
                events.ScheduleEvent(EVENT_LIVING_BOMB, 35000);
                break;
            default:
                break;
        }
    }

private:
    bool _armageddon;
};

class spell_infernoAuraScript : public AuraScript
{
    PrepareAuraScript(spell_infernoAuraScript)
            
        void HandleEffectPeriodic(AuraEffect const* aurEff)
        {
            int32 damage = aurEff->GetAmount() + floor((aurEff->GetTickNumber() - 1)/2) * 500;
            GetUnitOwner()->CastCustomSpell(SPELL_INFERNO_DAMAGE, SPELLVALUE_BASE_POINT0, damage, GetUnitOwner(), TRIGGERED_FULL_MASK);
        }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_infernoAuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

void AddSC_boss_baron_geddon()
{
    new CreatureAILoader<boss_baron_geddonAI>("boss_baron_geddon");
    new AuraScriptLoaderEx<spell_infernoAuraScript>("spell_inferno");
}
