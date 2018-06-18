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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum DoomwalkerTexts
{
    SAY_AGGRO,
    SAY_EARTHQUAKE,
    SAY_OVERRUN,
    SAY_SLAY,
    SAY_DEATH
};

enum DoomwalkerSpells
{
    SPELL_EARTHQUAKE        = 32686,
    SPELL_SUNDER_ARMOR      = 33661,
    SPELL_CHAIN_LIGHTNING   = 33665,
    SPELL_OVERRUN           = 32636,
    SPELL_ENRAGE            = 33653,
    SPELL_MARK_DEATH        = 37128,
    SPELL_AURA_DEATH        = 37131
};

enum DoomwalkerEvents
{
    EVENT_ARMOR             = 1,
    EVENT_CHAIN,
    EVENT_QUAKE,
    EVENT_OVERRUN
};

struct boss_doomwalkerAI : public ScriptedAI
{
    boss_doomwalkerAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _events.Reset();
        _inEnrage = false;
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim)
            victim->CastSpell(victim, SPELL_MARK_DEATH, false);

        if (!urand(0, 4))
            Talk(SAY_SLAY);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*schoolMask*/) override
    {
        if (!_inEnrage && me->HealthBelowPctDamaged(20, damage))
        {
            _inEnrage = true;
            DoCastSelf(SPELL_ENRAGE, true);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_DEATH);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        Talk(SAY_AGGRO);
        _events.ScheduleEvent(EVENT_ARMOR, 5s, 13s);
        _events.ScheduleEvent(EVENT_CHAIN, 10s, 30s);
        _events.ScheduleEvent(EVENT_QUAKE, 25s, 35s);
        _events.ScheduleEvent(EVENT_OVERRUN, 30s, 45s);
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (who && who->IsPlayer() && me->IsValidAttackTarget(who) && who->HasAura(SPELL_MARK_DEATH) && !who->HasAura(27827))
            who->CastSpell(who, SPELL_AURA_DEATH, true);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_OVERRUN:
                    Talk(SAY_OVERRUN);
                    DoCastSelf(SPELL_OVERRUN);
                    _events.Repeat(25s, 40s);
                    break;
                case EVENT_QUAKE:
                    Talk(SAY_EARTHQUAKE);
                    DoCastSelf(SPELL_EARTHQUAKE);
                    _events.Repeat(30s, 55s);
                    break;
                case EVENT_CHAIN:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        DoCast(target, SPELL_CHAIN_LIGHTNING);
                    _events.Repeat(7s, 27s);
                    break;
                case EVENT_ARMOR:
                    DoCastVictim(SPELL_SUNDER_ARMOR);
                    _events.Repeat(10s, 25s);
                    break;
                default:
                    break;
            }

            if (me->IsCasting())
                return;
        }

        DoMeleeAttackIfReady();
    }

    private:
        EventMap _events;
        bool _inEnrage;
};

void AddSC_boss_doomwalker()
{
    new CreatureAILoader<boss_doomwalkerAI>("boss_doomwalker");
}
