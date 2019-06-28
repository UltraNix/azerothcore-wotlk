/*
 * Copyright (C) 2018-2019 Sunwell <https://sunwell.pl/>
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

#include "shadowfang_keep.h"

enum ArugalSpells
{
    SPELL_TELE_UPPER            = 7587,
    SPELL_TELE_SPAWN            = 7586,
    SPELL_TELE_STAIRS           = 7136,
    SPELL_ARUGAL_CURSE          = 7621,
    SPELL_THUNDERSHOCK          = 7803,
    SPELL_VOIDBOLT              = 7588
};

enum ArugalTexts
{
    SAY_AGGRO                   = 1,
    SAY_TRANSFORM,
    SAY_SLAY
};

enum ArugalEvents
{
    EVENT_VOID_BOLT             = 1,
    EVENT_TELEPORT,
    EVENT_THUNDERSHOCK,
    EVENT_CURSE
};

struct boss_archmage_arugalAI : public BossAI
{
    boss_archmage_arugalAI(Creature* creature) : BossAI(creature, BOSS_ARUGAL) { }

    void KilledUnit(Unit* who) override
    {
        if (who->IsCasting())
            Talk(SAY_SLAY);
    }

    void SpellHitTarget(Unit* /*target*/, SpellInfo const* spellInfo) override
    {
        if (spellInfo->Id == SPELL_ARUGAL_CURSE)
            Talk(SAY_TRANSFORM);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
        events.ScheduleEvent(EVENT_CURSE, 7s);
        events.ScheduleEvent(EVENT_TELEPORT, 15s);
        events.ScheduleEvent(EVENT_VOID_BOLT, 1s);
        events.ScheduleEvent(EVENT_THUNDERSHOCK, 10s);
    }

    void AttackStart(Unit* who) override
    {
        AttackStartCaster(who, 100.0f);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CURSE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 30.0f, true))
                    DoCast(target, SPELL_ARUGAL_CURSE, true);
                events.Repeat(10s, 15s);
                break;
            case EVENT_TELEPORT:
                // ensure we never cast the same teleport twice in a row
                std::swap(_teleportSpells[0], _teleportSpells[urand(1, _teleportSpells.size() - 1)]);
                DoCastSelf(_teleportSpells[0]);
                events.Repeat(20s);
                break;
            case EVENT_THUNDERSHOCK:
                if (me->SelectNearestTarget(5.0f, true))
                {
                    DoCastSelf(SPELL_THUNDERSHOCK);
                    events.Repeat(15s);
                    break;
                }
                events.Repeat(3s);
                break;
            case EVENT_VOID_BOLT:
                DoCastVictim(SPELL_VOIDBOLT);
                events.Repeat(5s);
                break;
            default:
                break;
        }
    }

    private:
        std::array<uint32, 3> _teleportSpells = { SPELL_TELE_SPAWN, SPELL_TELE_UPPER, SPELL_TELE_STAIRS };
};

void AddSC_boss_archmage_arugal()
{
    new CreatureAILoader<boss_archmage_arugalAI>("boss_archmage_arugal");
}
