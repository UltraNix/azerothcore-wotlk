/*
* Copyright (C) 2015-2015 Theatre of Dreams
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
#include "SpellScript.h"
#include "Spell.h"
#include "old_scarlet_monastery.h"
#include "Unit.h"

enum Spells
{
    SPELL_BERSERK = 68378,
    SPELL_FEIGN_DEATH = 70592,
    SPELL_SHADOWBOLT_VOLLEY = 45770,
    SPELL_SWARMING_SHADOWS = 71264,
    SPELL_SWARMING_PASSIVE = 72985,
    SPELL_SHADOW_BUFFET = 38143,
    SPELL_SHADOW_REJUVENATION = 29587,
    SPELL_FINGER_OF_DEATH = 31984,
    SPELL_SHROUD_OF_SORROW = 70986,
    SPELL_SHADOW_BOLT = 54113,
    SPELL_SHADOW_RESONANCE = 41961,
    SPELL_SHIELD = 70768,
    SPELL_GRIP_OF_DARKNESS = 64429,
    SPELL_DARKNESS = 45996,
    SPELL_SHADOW_NOVA = 45329,
    SPELL_PHASE_SHADOW_NOVA = 36127,
    SPELL_TAG_ARROW = 20374,
    SPELL_ORB_VISUAL = 75099,
    SPELL_NERF = 72341,
};

enum Events
{
    EVENT_BERSERK = 1,
    EVENT_REINCARNATE = 2,
    EVENT_SHADOWBOLT_VOLLEY = 3,
    EVENT_SHADOW_BUFFET = 4,
    EVENT_SHADOW_REJUVENATION = 5,
    EVENT_SHADOW_BOLT = 6,
    EVENT_SHADOW_RESONANCE = 7,
    EVENT_GRIP_OF_DARKNESS = 8,
    EVENT_TAG_ARROW = 9,
    EVENT_SHADOW_NOVA = 10,
    EVENT_SWARMING_SHADOWS = 11,
    EVENT_FINGER_OF_DEATH = 12,
    EVENT_SUMMON_ORBS = 13
};

enum Misc
{
    GROUP_DELAYABLE = 1,
    MAX_ORBS = 8
};

Position orbPositions[MAX_ORBS] =
{
    { 186.754654f, 16.022705f, 31.036940f, 0.345569f },
    { 207.019638f, 15.611312f, 30.839573f, 6.209872f },
    { 207.237045f, 36.069584f, 31.086300f, 0.453819f },
    { 187.094742f, 36.292271f, 31.062311f, 3.128756f },
    { 198.388931f, 33.605419f, 30.839043f, 2.077921f },
    { 206.871933f, 25.846926f, 30.840313f, 3.008201f },
    { 196.831375f, 15.735995f, 30.840244f, 1.487408f },
    { 186.895828f, 25.956270f, 30.839060f, 6.125315f }
};

class boss_reast : public CreatureScript
{
    public:
        boss_reast() : CreatureScript("boss_reast") { }

        struct boss_reastAI : public BossAI
        {
            boss_reastAI(Creature* creature) : BossAI(creature, DATA_REAST)
            {
                instance = me->GetInstanceScript();
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
            }

            void Reset() override
            {
                _Reset();
                me->SetReactState(REACT_AGGRESSIVE);
                SetPhase(PHASE_ONE);
                me->UpdateEntry(NPC_REAST);
                novaTargets.clear();
                me->RemoveAurasDueToSpell(SPELL_SHROUD_OF_SORROW);
                swarmTargetsNum = 0;
                summonedOrbs = 0;
            }

            void EnterCombat(Unit* target) override
            {
                if (phase != PHASE_ONE)
                    return;
                if (!instance->CheckRequiredBosses(DATA_REAST))
                {
                    EnterEvadeMode();
                    return;
                }

                if (!me->HasAura(SPELL_SHROUD_OF_SORROW))
                    me->AddAura(SPELL_SHROUD_OF_SORROW, me);
                if (!me->HasAura(SPELL_NERF))
                    me->AddAura(SPELL_NERF, me);

                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SHIELD);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TAG_ARROW);
                events.ScheduleEvent(EVENT_BERSERK, 600000);
                events.ScheduleEvent(EVENT_SHADOWBOLT_VOLLEY, urand(5000, 8000), GROUP_DELAYABLE);
                events.ScheduleEvent(EVENT_SHADOW_REJUVENATION, 20000, GROUP_DELAYABLE);
                events.ScheduleEvent(EVENT_SHADOW_BOLT, urand(3000, 4000), GROUP_DELAYABLE);
                events.ScheduleEvent(EVENT_SHADOW_RESONANCE, 10000, GROUP_DELAYABLE);
                events.ScheduleEvent(EVENT_GRIP_OF_DARKNESS, 20000, 0);
                _EnterCombat();
            }

            void EnterEvadeMode() override
            {
                if (me->HasAura(SPELL_FEIGN_DEATH))
                    return;

                me->RemoveAurasDueToSpell(SPELL_SHROUD_OF_SORROW);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SHIELD);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TAG_ARROW);
                BossAI::EnterEvadeMode();
                Reset();
            }

            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                if (me->GetHealth() < damage)
                    if (phase == PHASE_ONE)
                    {
                        damage = 0;
                        DoCast(me, SPELL_FEIGN_DEATH, true);
                        me->RemoveAllAuras();
                        me->SetReactState(REACT_PASSIVE);
                        DoStopAttack();
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
                        events.ScheduleEvent(EVENT_REINCARNATE, 3000);
                    }
            }

            void JustDied(Unit* killer) override
            {
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SHIELD);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TAG_ARROW);
                _JustDied();
            }

            void MoveInLineOfSight(Unit* who) override { }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                if (!CheckInRoom() && !me->IsInEvadeMode())
                    EnterEvadeMode();

                events.Update(diff);
                //_DoAggroPulse(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_BERSERK:
                        DoCast(me, SPELL_BERSERK, true);
                        break;
                    case EVENT_REINCARNATE:
                        me->UpdateEntry(NPC_REAST2);
                        me->SetFullHealth();
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NON_ATTACKABLE);
                        SetPhase(PHASE_TWO);
                        me->CastCustomSpell(SPELL_PHASE_SHADOW_NOVA, SPELLVALUE_BASE_POINT0, 12000, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                        me->AddAura(SPELL_SHROUD_OF_SORROW, me);
                        DoZoneInCombat();
                        me->Attack(me->GetVictim(), true);
                        break;
                    case EVENT_SHADOWBOLT_VOLLEY:
                        me->CastCustomSpell(SPELL_SHADOWBOLT_VOLLEY, SPELLVALUE_BASE_POINT0, 4000, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_SHADOWBOLT_VOLLEY, urand(15000, 18000), GROUP_DELAYABLE);
                        break;
                    case EVENT_SHADOW_REJUVENATION:
                        me->CastCustomSpell(SPELL_SHADOW_REJUVENATION, SPELLVALUE_BASE_POINT0, 50000, me, TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_SHADOW_REJUVENATION, 20000, GROUP_DELAYABLE);
                        break;
                    case EVENT_SHADOW_BOLT:
                    {
                        CustomSpellValues values;
                        values.AddSpellMod(SPELLVALUE_BASE_POINT0, 20000);
                        values.AddSpellMod(SPELLVALUE_MAX_TARGETS, 1);
                        me->CastCustomSpell(SPELL_SHADOW_BOLT, values, me->GetVictim(), TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_SHADOW_BOLT, urand(3000, 4000), GROUP_DELAYABLE);
                        break;
                    }
                    case EVENT_SHADOW_RESONANCE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 2, 0.0f, true))
                            DoCast(target, SPELL_SHADOW_RESONANCE, true);
                        DoCastVictim(SPELL_SHADOW_RESONANCE, true);
                        events.ScheduleEvent(EVENT_SHADOW_RESONANCE, 10000, GROUP_DELAYABLE);
                        break;
                    case EVENT_GRIP_OF_DARKNESS:
                    {
                        events.DelayEvents(4000, GROUP_DELAYABLE);
                        std::list<Unit*> targets;
                        SelectTargetList(targets, NonTankTargetSelector(me, true), 10, SELECT_TARGET_NEAREST);
                        targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_SWARMING_PASSIVE));
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            DoCast(*itr, SPELL_GRIP_OF_DARKNESS, true);
                            (*itr)->CastSpell(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 57604, true);
                        }
                        novaTargets.clear();
                        SelectTargetList(novaTargets, NonTankTargetSelector(me, true), 2, SELECT_TARGET_RANDOM);
                        novaTargets.remove_if(Trinity::UnitAuraCheck(true, SPELL_SWARMING_PASSIVE));
                        for (std::list<Unit*>::const_iterator itr = novaTargets.begin(); itr != novaTargets.end(); ++itr)
                            DoCast(*itr, SPELL_TAG_ARROW, true);
                        events.ScheduleEvent(EVENT_GRIP_OF_DARKNESS, 30000, 0);
                        events.ScheduleEvent(EVENT_SHADOW_NOVA, 4000, 0);
                        break;
                    }
                    case EVENT_SHADOW_NOVA:
                        for (std::list<Unit*>::const_iterator itr = novaTargets.begin(); itr != novaTargets.end(); ++itr)
                        {
                            me->CastCustomSpell(SPELL_SHADOW_NOVA, SPELLVALUE_BASE_POINT0, 10000, *itr, TRIGGERED_FULL_MASK);
                            (*itr)->RemoveAurasDueToSpell(SPELL_TAG_ARROW);
                        }
                        break;
                    case EVENT_SWARMING_SHADOWS:
                    {
                        std::list<Unit*> targets;
                        SelectTargetList(targets, NonTankTargetSelector(me), swarmTargetsNum++ / 3, SELECT_TARGET_RANDOM);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            DoCast(*itr, SPELL_SWARMING_SHADOWS, true);
                        events.ScheduleEvent(EVENT_SWARMING_SHADOWS, 20000, GROUP_DELAYABLE);
                        break;

                    }
                    case EVENT_FINGER_OF_DEATH:
                        DoCastVictim(SPELL_FINGER_OF_DEATH, true);
                        events.ScheduleEvent(EVENT_FINGER_OF_DEATH, 15000, GROUP_DELAYABLE);
                        break;
                    case EVENT_SUMMON_ORBS:
                        if (summonedOrbs < MAX_ORBS)
                        {
                            SummonOrbs();
                            events.ScheduleEvent(EVENT_SUMMON_ORBS, 20000);
                        }
                        break;
                    default:
                        break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void SetPhase(uint8 phase_)
            {
                events.SetPhase(phase);
                phase = phase_;
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TAG_ARROW);
                if (phase == PHASE_TWO)
                {
                    events.CancelEventGroup(GROUP_DELAYABLE);
                    events.CancelEvent(EVENT_GRIP_OF_DARKNESS);
                    novaTargets.clear();

                    events.ScheduleEvent(EVENT_SHADOW_BOLT, urand(3000, 4000), GROUP_DELAYABLE);
                    events.ScheduleEvent(EVENT_SHADOW_RESONANCE, 10000, GROUP_DELAYABLE);
                    events.ScheduleEvent(EVENT_GRIP_OF_DARKNESS, 20000, 0);
                    events.ScheduleEvent(EVENT_SWARMING_SHADOWS, 8000, GROUP_DELAYABLE);
                    events.ScheduleEvent(EVENT_FINGER_OF_DEATH, 15000, GROUP_DELAYABLE);
                    events.ScheduleEvent(EVENT_SUMMON_ORBS, 60000);
                }
            }

            void SummonOrbs()
            {
                if (Creature* orb = me->SummonCreature(NPC_POWER_ORB, orbPositions[summonedOrbs], TEMPSUMMON_TIMED_DESPAWN, 30000))
                    ++summonedOrbs;
            }

        private:
            InstanceScript* instance;
            uint8 phase;
            std::list<Unit*> novaTargets;
            uint8 swarmTargetsNum;
            uint8 summonedOrbs;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<boss_reastAI>(creature);
        }
};

class npc_reast_orb : public CreatureScript
{
    public:
        npc_reast_orb() : CreatureScript("npc_reast_orb") { }

        struct npc_reast_orbAI : public ScriptedAI
        {
            npc_reast_orbAI(Creature *creature) : ScriptedAI(creature)
            {
                me->SetReactState(REACT_AGGRESSIVE);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
            }

            void IsSummonedBy(Unit* summoner) override
            {
                DoCast(SPELL_ORB_VISUAL);
            }

            void MoveInLineOfSight(Unit* target) override
            {
                if (!guids.count(target->GetGUID()))
                    if (target->IsWithinDist2d(me, 3.0f))
                    {
                        guids.insert(target->GetGUID());
                        target->AddAura(SPELL_SHIELD, target);
                    }
            }

            void UpdateAI(uint32 diff) override { }

        private:
            std::unordered_set<uint64> guids;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_reast_orbAI>(creature);
        }
};

void AddSC_boss_reast()
{
    new boss_reast();
    new npc_reast_orb();
}
