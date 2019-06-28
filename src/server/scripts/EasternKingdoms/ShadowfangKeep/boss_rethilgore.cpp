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

enum RethilgoreSpells
{
    SPELL_SOUL_DRAIN = 7295
};

struct boss_rethilgoreAI : public BossAI
{
    boss_rethilgoreAI(Creature* creature) : BossAI(creature, BOSS_RETHILGORE) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        scheduler.Schedule(1s, 6s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
            {
                DoCast(target, SPELL_SOUL_DRAIN);
                task.Repeat(8s, 12s);
            }
            else
                task.Repeat(2s, 3s);
        });
    }
};

void AddSC_boss_rethilgore()
{
    new CreatureAILoader<boss_rethilgoreAI>("boss_rethilgore");
}
