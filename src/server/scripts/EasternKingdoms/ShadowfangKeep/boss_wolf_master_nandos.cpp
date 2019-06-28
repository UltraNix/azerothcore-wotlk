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

enum NandosSpells
{
    SPELL_BLEAK_WORG        = 7487,
    SPELL_SLAVERING_WORG    = 7488,
    SPELL_LUPINE_HORROR     = 7489
};

struct boss_wolf_master_nandosAI : public BossAI
{
    boss_wolf_master_nandosAI(Creature* creature) : BossAI(creature, BOSS_NANDOS) { }

    void Reset() override
    {
        _Reset();
        _offset = 0;
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*mask*/) override
    {
        int32 hpPct = std::max(0, 75 - (_offset * 25));
        if (hpPct && me->HealthBelowPctDamaged(hpPct, damage))
        {
            DoCastSelf(SPELL_BLEAK_WORG + _offset);
            ++_offset;
        }
    }

    private:
        int32 _offset;
};

void AddSC_boss_wolf_master_nandos()
{
    new CreatureAILoader<boss_wolf_master_nandosAI>("boss_wolf_master_nandos");
}
