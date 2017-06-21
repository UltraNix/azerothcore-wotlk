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
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "molten_core.h"

enum Spells
{
    SPELL_ARCANE_EXPLOSION              = 19712,
    SPELL_SHAZZRAH_CURSE                = 19713,
    SPELL_MAGIC_GROUNDING               = 19714,
    SPELL_COUNTERSPELL                  = 19715,
    SPELL_SHAZZRAH_GATE_DUMMY           = 23138, // Teleports to and attacks a random target.
    SPELL_SHAZZRAH_GATE                 = 23139,
};

enum Events
{
    EVENT_ARCANE_EXPLOSION              = 1,
    EVENT_ARCANE_EXPLOSION_TRIGGERED,
    EVENT_SHAZZRAH_CURSE,
    EVENT_MAGIC_GROUNDING,
    EVENT_COUNTERSPELL,
    EVENT_SHAZZRAH_GATE
};

struct boss_shazzrahAI : public BossAI
{
    boss_shazzrahAI(Creature* creature) : BossAI(creature, BOSS_SHAZZRAH) { }

    void EnterCombat(Unit* /*target*/)
    {
        _EnterCombat();
        events.ScheduleEvent(EVENT_ARCANE_EXPLOSION, 6000);
        events.ScheduleEvent(EVENT_SHAZZRAH_CURSE, 10000);
        events.ScheduleEvent(EVENT_MAGIC_GROUNDING, 24000);
        events.ScheduleEvent(EVENT_COUNTERSPELL, 15000);
        events.ScheduleEvent(EVENT_SHAZZRAH_GATE, 45000);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_ARCANE_EXPLOSION:
                DoCastVictim(SPELL_ARCANE_EXPLOSION);
                events.ScheduleEvent(EVENT_ARCANE_EXPLOSION, urand(4000, 7000));
                break;
                // Triggered subsequent to using "Gate of Shazzrah".
            case EVENT_ARCANE_EXPLOSION_TRIGGERED:
                DoCastVictim(SPELL_ARCANE_EXPLOSION);
                break;
            case EVENT_SHAZZRAH_CURSE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true, -SPELL_SHAZZRAH_CURSE))
                    DoCast(target, SPELL_SHAZZRAH_CURSE);
                events.ScheduleEvent(EVENT_SHAZZRAH_CURSE, urand(25000, 30000));
                break;
            case EVENT_MAGIC_GROUNDING:
                DoCast(me, SPELL_MAGIC_GROUNDING);
                events.ScheduleEvent(EVENT_MAGIC_GROUNDING, 35000);
                break;
            case EVENT_COUNTERSPELL:
                DoCastVictim(SPELL_COUNTERSPELL);
                events.ScheduleEvent(EVENT_COUNTERSPELL, urand(16000, 20000));
                break;
            case EVENT_SHAZZRAH_GATE:
                DoResetThreat();
                DoCastAOE(SPELL_SHAZZRAH_GATE_DUMMY);
                events.ScheduleEvent(EVENT_ARCANE_EXPLOSION_TRIGGERED, 2000);
                events.RescheduleEvent(EVENT_ARCANE_EXPLOSION, urand(3000, 6000));
                events.ScheduleEvent(EVENT_SHAZZRAH_GATE, 45000);
                break;
            default:
                break;
        }
    }
};

// 23138 - Gate of Shazzrah
class spell_shazzrah_gate_dummy_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_shazzrah_gate_dummy_SpellScript);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHAZZRAH_GATE });
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        WorldObject* target = Trinity::Containers::SelectRandomContainerElement(targets);
        targets.clear();
        targets.push_back(target);
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
        {
            target->CastSpell(GetCaster(), SPELL_SHAZZRAH_GATE, true);
            if (Creature* creature = GetCaster()->ToCreature())
                creature->AI()->AttackStart(target); // Attack the target which caster will teleport to.
        }
    }

    void Register()
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_shazzrah_gate_dummy_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnEffectHitTarget += SpellEffectFn(spell_shazzrah_gate_dummy_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_boss_shazzrah()
{
    new CreatureAILoader<boss_shazzrahAI>("boss_shazzrah");
    new SpellScriptLoaderEx<spell_shazzrah_gate_dummy_SpellScript>("spell_shazzrah_gate_dummy");
}
