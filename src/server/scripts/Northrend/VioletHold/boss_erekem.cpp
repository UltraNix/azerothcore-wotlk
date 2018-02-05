/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
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
#include "InstanceScript.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "ScriptedCreature.h"
#include "violet_hold.h"

enum ErekemSpells
{
    SPELL_BLOODLUST                             = 54516,
    SPELL_BREAK_BONDS                           = 59463,
    SPELL_CHAIN_HEAL                            = 54481,
    SPELL_EARTH_SHIELD                          = 54479,
    SPELL_EARTH_SHOCK                           = 54511,
    SPELL_LIGHTNING_BOLT                        = 53044,
    SPELL_STORMSTRIKE                           = 51876,
    SPELL_WINDFURY                              = 54493
};

enum ErekemYells
{
    SAY_AGGRO                                   = 0,
    SAY_SLAY                                    = 1,
    SAY_DEATH                                   = 2,
    SAY_SPAWN                                   = 3,
    SAY_ADD_KILLED                              = 4,
    SAY_BOTH_ADDS_KILLED                        = 5
};

struct boss_erekemAI : public BossAI
{
    boss_erekemAI(Creature* creature) : BossAI(creature, DATA_EREKEM) { }

    void Reset() override
    {
        me->SetWalk(true);
        _phase = 0;
        _Reset();
        me->SetCanDualWield(false);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        me->SetWalk(false);
        _EnterCombat();
        Talk(SAY_AGGRO);
        DoCastSelf(SPELL_EARTH_SHIELD);

        std::list<Creature*> guardList;
        me->GetCreatureListWithEntryInGrid(guardList, NPC_EREKEM_GUARD, 50.0f);
        if (!guardList.empty())
            for (auto guard : guardList)
                _guardList.push_back(guard->GetGUID());

        scheduler.Schedule(20s, [this](TaskContext task)
        {
            if (Unit* ally = DoSelectLowestHpFriendly(30.0f))
                DoCast(ally, SPELL_EARTH_SHIELD);

            task.Repeat(20s);
        });

        scheduler.Schedule(2s, [this](TaskContext task)
        {
            DoCastSelf(SPELL_BLOODLUST);
            task.Repeat(35s, 45s);
        });

        scheduler.Schedule(2s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f))
                DoCast(target, SPELL_LIGHTNING_BOLT);

            task.Repeat(2500ms);
        });

        scheduler.Schedule(10s, [this](TaskContext task)
        {
            if (Unit* ally = DoSelectLowestHpFriendly(40.0f))
                DoCast(ally, SPELL_CHAIN_HEAL);

            if (!CheckGuardAlive())
                task.Repeat(5s);
            else
                task.Repeat(8s, 11s);
        });

        scheduler.Schedule(2s, 8s, [this](TaskContext task)
        {
            DoCastVictim(SPELL_EARTH_SHOCK);
            task.Repeat(8s, 13s);
        });

        scheduler.Schedule(0s, [this](TaskContext task)
        {
            for (auto guid : _guardList)
            {
                if (Creature* guard = ObjectAccessor::GetCreature(*me, guid))
                {
                    if (guard->IsAlive() && CheckGuardAuras(guard))
                    {
                        DoCastSelf(SPELL_BREAK_BONDS);
                        task.Repeat(10s);
                        return;
                    }
                }
            }

            task.Repeat(500ms);
        });
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == EFFECT_MOTION_TYPE && pointId == POINT_INTRO)
            me->SetFacingTo(4.921828f);
    }

    void JustReachedHome() override
    {
        _JustReachedHome();
        instance->SetData(DATA_HANDLE_CELLS, DATA_EREKEM);
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->GetTypeId() == TYPEID_PLAYER)
            Talk(SAY_SLAY);
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
    }

    bool CheckGuardAuras(Creature* guard) const
    {
        static uint32 const MechanicImmunityList =
              (1 << MECHANIC_SNARE)
            | (1 << MECHANIC_ROOT)
            | (1 << MECHANIC_FEAR)
            | (1 << MECHANIC_STUN)
            | (1 << MECHANIC_SLEEP)
            | (1 << MECHANIC_CHARM)
            | (1 << MECHANIC_SAPPED)
            | (1 << MECHANIC_HORROR)
            | (1 << MECHANIC_POLYMORPH)
            | (1 << MECHANIC_DISORIENTED)
            | (1 << MECHANIC_FREEZE)
            | (1 << MECHANIC_TURN);

        static std::list<AuraType> const AuraImmunityList =
        {
            SPELL_AURA_MOD_STUN,
            SPELL_AURA_MOD_DECREASE_SPEED,
            SPELL_AURA_MOD_ROOT,
            SPELL_AURA_MOD_CONFUSE,
            SPELL_AURA_MOD_FEAR
        };

        if (guard->HasAuraWithMechanic(MechanicImmunityList))
            return true;

        for (AuraType type : AuraImmunityList)
            if (guard->HasAuraType(type))
                return true;

        return false;
    }

    bool CheckGuardAlive() const
    {
        for (auto guid : _guardList)
        {
            if (Creature* guard = ObjectAccessor::GetCreature(*me, guid))
                if (guard->IsAlive())
                    return true;
        }

        return false;
    }

    Unit* GetChainHealTarget() const
    {
        if (HealthBelowPct(85))
            return me;

        for (auto guid : _guardList)
        {
            if (Creature* guard = ObjectAccessor::GetCreature(*me, guid))
                if (guard->IsAlive() && !guard->HealthAbovePct(75))
                    return guard;
        }

        return nullptr;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (_phase == 0 && !CheckGuardAlive())
        {
            _phase = 1;
            me->SetCanDualWield(true);
            DoCastSelf(SPELL_WINDFURY, true);
        }

        scheduler.Update(diff, [this]
        {
            if (_phase == 1)
                DoSpellAttackIfReady(SPELL_STORMSTRIKE);
            else
                DoMeleeAttackIfReady();
        });
    }

    private:
        uint8 _phase;
        std::vector<uint64> _guardList;
};

enum GuardSpells
{
    SPELL_GUSHING_WOUND                   = 39215,
    SPELL_HOWLING_SCREECH                 = 54462,
    SPELL_STRIKE                          = 14516
};

struct npc_erekem_guardAI : public ScriptedAI
{
    npc_erekem_guardAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        me->SetWalk(true);
        _scheduler.CancelAll();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        me->SetWalk(false);

        _scheduler.Schedule(4s, 8s, [this](TaskContext task)
        {
            DoCastVictim(SPELL_STRIKE);
            task.Repeat(4s, 8s);
        });

        _scheduler.Schedule(8s, 13s, [this](TaskContext task)
        {
            DoCastSelf(SPELL_HOWLING_SCREECH);
            task.Repeat(8s, 13s);
        });

        _scheduler.Schedule(1s, 3s, [this](TaskContext task)
        {
            DoCastVictim(SPELL_GUSHING_WOUND);
            task.Repeat(7s, 12s);
        });

        DoZoneInCombat();
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff,
            std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
};

void AddSC_boss_erekem()
{
    new CreatureAILoader<boss_erekemAI>("boss_erekem");
    new CreatureAILoader<npc_erekem_guardAI>("npc_erekem_guard");
}
