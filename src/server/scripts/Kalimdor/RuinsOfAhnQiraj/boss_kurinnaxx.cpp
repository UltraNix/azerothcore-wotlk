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

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ruins_of_ahnqiraj.h"
#include "CreatureTextMgr.h"

enum Spells
{
    SPELL_MORTALWOUND       = 25646,
    SPELL_SANDTRAP          = 25648,
    SPELL_ENRAGE            = 26527,
    SPELL_SUMMON_PLAYER     = 26446,
    SPELL_TRASH             =  3391, // Should perhaps be triggered by an aura? Couldn't find any though
    SPELL_WIDE_SLASH        = 25814
};

enum Events
{
    EVENT_MORTAL_WOUND      = 1,
    EVENT_SANDTRAP,
    EVENT_TRASH,
    EVENT_WIDE_SLASH
};

enum Texts
{
    SAY_KURINAXX_DEATH      = 5, // Yelled by Ossirian the Unscarred
};

struct boss_kurinnaxxAI : public BossAI
{
    boss_kurinnaxxAI(Creature* creature) : BossAI(creature, DATA_KURINNAXX) { }

    void Reset() override
    {
        _Reset();
        _enraged = false;
        events.ScheduleEvent(EVENT_MORTAL_WOUND, 7000);
        events.ScheduleEvent(EVENT_SANDTRAP, 7000);
        events.ScheduleEvent(EVENT_TRASH, 10000);
        events.ScheduleEvent(EVENT_WIDE_SLASH, 15000);
    }

    void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (!_enraged && me->HealthBelowPctDamaged(30, damage))
        {
            DoCast(me, SPELL_ENRAGE);
            _enraged = true;
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Position pos;
        me->GetPosition(&pos);
        pos.m_positionZ -= 55.0f;
        if (Creature* ossirian = me->SummonCreature(15339, pos, TEMPSUMMON_MANUAL_DESPAWN))
        {
            ossirian->SetVisible(false);
            sCreatureTextMgr->SendChat(ossirian, SAY_KURINAXX_DEATH, nullptr, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_ZONE);
            ossirian->DespawnOrUnsummon();
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_MORTAL_WOUND:
                DoCastVictim(SPELL_MORTALWOUND);
                events.ScheduleEvent(EVENT_MORTAL_WOUND, 9000);
                break;
            case EVENT_SANDTRAP:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    target->CastSpell(target, SPELL_SANDTRAP, true);
                events.ScheduleEvent(EVENT_SANDTRAP, urand(5000, 15000));
                break;
            case EVENT_WIDE_SLASH:
                DoCastVictim(SPELL_WIDE_SLASH);
                events.ScheduleEvent(EVENT_WIDE_SLASH, urand(10000, 20000));
                break;
            case EVENT_TRASH:
                DoCastSelf(SPELL_TRASH);
                events.ScheduleEvent(EVENT_TRASH, urand(10000, 20000));
                break;
            default:
                break;
        }
    }

    private:
        bool _enraged;
};

void AddSC_boss_kurinnaxx()
{
    new CreatureAILoader<boss_kurinnaxxAI>("boss_kurinnaxx");
}
