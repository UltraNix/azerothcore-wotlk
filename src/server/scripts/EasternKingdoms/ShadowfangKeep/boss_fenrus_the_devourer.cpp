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
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "InstanceScript.h"

enum FenrusSpells
{
    SPELL_TOXIC_SALIVA = 7125
};

struct boss_fenrus_the_devourerAI : public BossAI
{
    boss_fenrus_the_devourerAI(Creature* creature) : BossAI(creature, BOSS_FENRUS) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        scheduler.Schedule(2s, 6s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 5.0f, true))
            {
                DoCast(target, SPELL_TOXIC_SALIVA);
                task.Repeat(10s, 15s);
            }
            else
                task.Repeat(2s, 3s);
        });
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        instance->SetData(DATA_VOIDWALKER_EVENT, 1);
    }
};

enum ArugalVoidwalker
{
    SPELL_DARK_OFFERING = 7154,
};

struct npc_arugal_voidwalkerAI : public ScriptedAI
{
    npc_arugal_voidwalkerAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _scheduler.CancelAll();
        _scheduler.Schedule(2s, [this](TaskContext task)
        {
            DoZoneInCombat();
        });
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(1s, 3s, [this](TaskContext task)
        {
            if (Unit* target = DoSelectLowestHpFriendly(10.0f, 300))
            {
                DoCast(target, SPELL_DARK_OFFERING);
                task.Repeat(10s, 15s);
            }
            else
                task.Repeat(2s, 3s);
        });
    }

    void EnterEvadeMode() override
    {
        me->DespawnOrUnsummon();
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (InstanceScript* instance = me->GetInstanceScript())
            instance->SetData(DATA_VOIDWALKER_DIES, 1);
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

    private:
        TaskScheduler _scheduler;
};

void AddSC_boss_fenrus_the_devourer()
{
    new CreatureAILoader<boss_fenrus_the_devourerAI>("boss_fenrus_the_devourer");
    new CreatureAILoader<npc_arugal_voidwalkerAI>("npc_arugal_voidwalker");
}
