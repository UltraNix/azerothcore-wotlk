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
#include "MoveSplineInit.h"
#include "MoveSpline.h"

enum Texts
{
    SAY_INTRO_1 = 0,
    SAY_INTRO_2 = 1,
    SAY_INTRO_3 = 2,
    SAY_INTRO_4 = 3,
    SAY_INTRO_5 = 4,
    SAY_BERSERK = 5,
    SAY_PHASE_2 = 6,
    SAY_PHASE_3 = 7,
    SAY_PHASE_4 = 8,
    SAY_HELPERS = 9,
    SAY_AIR = 10,
    SAY_OUTRO_1 = 11,
    SAY_OUTRO_2 = 12,
    SAY_OUTRO_3 = 13
};

enum Events
{
    EVENT_INTRO_1 = 1,
    EVENT_INTRO_2 = 2,
    EVENT_INTRO_3 = 3,
    EVENT_INTRO_4 = 4,
    EVENT_INTRO_5 = 5,
    EVENT_INTRO_6 = 6,
    EVENT_START_FIGHT = 7,
    EVENT_BERSERK = 8,
    EVENT_SHADOW_BREATH = 9,
    EVENT_DEATH_COIL = 10,
    EVENT_CORRUPTION = 11,
    EVENT_SHADOW_CHANNELING = 12,
    EVENT_CONSUMPTION = 13,
    EVENT_VANISH = 14,
    EVENT_PHASE_THREE = 15,
    EVENT_CONSUMPTION_PHASE_THREE = 16,
    EVENT_CONSUMPTION_MARK = 17,
    EVENT_SUMMON_HELPERS = 18,
    EVENT_CHECK_HELPERS = 19,
    EVENT_SPIRIT_BURST = 20,
    EVENT_PHASE_FIVE = 21,
    EVENT_FALLING_ORBS = 22,
    EVENT_SHADOW_BOLT = 23,
    EVENT_ADDS = 24,
    EVENT_CONSUMPTION_PHASE_FIVE = 25,
    EVENT_OUTRO_1 = 26,
    EVENT_OUTRO_2 = 27,
    EVENT_OUTRO_3 = 28,
    EVENT_OUTRO_4 = 29,
    EVENT_OUTRO_5 = 30,

    EVENT_VOID_START_MOVING = 1,
    EVENT_NEXT_VOID = 2,

    EVENT_CLONE_START_ATTACK = 1,
    EVENT_IMMOLATE = 2,
    EVENT_SPELL_LOCK = 3,
    EVENT_KNOCBACK   = 4,

    EVENT_SOLDIER_START_ATTACK = 1,
    EVENT_MORTAL_STRIKE = 2,
    EVENT_CLEAVE = 3,
    EVENT_FRENZY = 4
};

enum Misc
{
    CLONES_COUNT = 4,
    DEFENDERS_COUNT = 5,
    HEALERS_COUNT = 8,
    BUFFERS_COUNT = 3,
    SOLDIERS_COUNT = 5,

    DATA_TARGET_GUID = 1
};

Position StartPos = { 272.603394f, -99.817451f, 28.869148f, 3.146109f };
Position CenterPos = { 255.060928f, -99.802231f, 18.679394f, 3.111331f };
Position ClonesPositions[CLONES_COUNT] =
{
    { 255.206024f, -95.396606f, 18.679392f, 4.717203f },
    { 259.925598f, -100.02620f, 18.679392f, 3.166041f },
    { 255.165695f, -104.67500f, 18.679392f, 1.623518f },
    { 250.597443f, -99.927017f, 18.679392f, 6.244277f }
};

Position DefendersPositions[DEFENDERS_COUNT] =
{
    { 244.021576f, -99.881798f, 23.774134f, 0.045493f },
    { 242.956787f, -112.01619f, 23.774416f, 0.758894f },
    { 253.790054f, -116.87941f, 23.774269f, 1.531205f },
    { 243.181915f, -87.844063f, 23.774210f, 5.468009f },
    { 253.982162f, -82.697487f, 23.774210f, 4.738243f }
};

Position BuffersPositions[BUFFERS_COUNT] =
{
    { 271.556427f, -103.58585f, 28.869169f, 2.901596f },
    { 272.206390f, -99.685287f, 28.869169f, 3.166667f },
    { 271.651947f, -96.474442f, 28.869169f, 3.287749f }
};

enum Spells
{
    SPELL_TELEPORT_VISUAL = 60427,
    SPELL_VOID_SUMMON_VISUAL = 19484,
    SPELL_SHADOW_BOLT = 56405,
    SPELL_SHADOW_BREATH = 59126,
    SPELL_DEATH_COIL = 47860,
    SPELL_BERSERK = 68378,
    SPELL_CORRUPTION = 68138,
    SPELL_SHADOW_CHANNELING = 74379,
    SPELL_AURA_BLACK = 46235,
    SPELL_CONSUMPTION = 74800,
    SPELL_IMMOLATE = 75383,
    SPELL_SPELL_LOCK = 30849,
    SPELL_CLONE_TELEPORT_VISUAL = 64446,
    SPELL_TAG_ARROW = 20374,
    SPELL_KNEEL = 39656,
    SPELL_DARK_MENDING = 49204,
    SPELL_BUFF = 64036,
    SPELL_EXPLOSION = 78862,
    SPELL_CLEAVE = 70670,
    SPELL_MORTAL_STRIKE = 67542,
    SPELL_FRENZY = 70747,
    SPELL_SLOW = 65210,
    SPELL_FINAL_EXPLOSION = 64584,
    SPELL_SPIRIT_BURST = 48452,
    SPELL_PRESENCE_OF_MASTER = 58958,
    SPELL_STOP_TIME = 49838,
    SPELL_HARDENED = 62733,

    SPELL_GREEN_BEAM = 72589,
    SPELL_RED_BEAM = 72594,
    SPELL_BLUE_BEAM = 72598,
    SPELL_BLACK_BEAM = 72735,
    SPELL_KNOCKBACK = 10689
};

class boss_javier_voidbringer : public CreatureScript
{
    public:
        boss_javier_voidbringer() : CreatureScript("boss_javier_voidbringer") { }

        struct boss_javier_voidbringerAI : public BossAI
        {
            boss_javier_voidbringerAI(Creature* creature) : BossAI(creature, DATA_JAVIER_VOIDBRINGER)
            {
                instance = me->GetInstanceScript();
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
            }

            void Reset() override
            {
                _Reset();
                me->SetReactState(REACT_AGGRESSIVE);
                SetPhase(PHASE_NONE);
                clonesDead = 0;
                me->SetVisible(true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveAurasDueToSpell(SPELL_HARDENED);
                me->RemoveAura(SPELL_AURA_BLACK);
                me->SetCanFly(false);
                me->SetDisableGravity(false);
                me->SendMovementFlagUpdate();
                me->SetInhabitType(INHABIT_GROUND);
            }

            void EnterCombat(Unit* target) override
            {
                if (!instance->CheckRequiredBosses(DATA_JAVIER_VOIDBRINGER))
                {
                    _DespawnAtEvade(30, me);
                    return;
                }

                _EnterCombat();
                SetPhase(PHASE_ONE);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TAG_ARROW);
                events.ScheduleEvent(EVENT_SHADOW_BREATH, 10000, 0, PHASE_ONE);
                events.ScheduleEvent(EVENT_DEATH_COIL, 7000, 0, PHASE_ONE);
                events.ScheduleEvent(EVENT_CORRUPTION, 9000, 0, PHASE_ONE);
                events.ScheduleEvent(EVENT_CONSUMPTION, 13000, 0, PHASE_ONE);
            }

            void EnterEvadeMode() override
            {
                _DespawnAtEvade(30, me);
            }

            void MoveInLineOfSight(Unit* who) override
            {
                //! all checks split for clarity and for debugging purposes
                if (!instance->CheckRequiredBosses(DATA_JAVIER_VOIDBRINGER))
                    return;

                if (who->GetTypeId() == TYPEID_UNIT)
                    return;

                if (who->ToPlayer()->IsGameMaster())
                    return;

                if (phase == PHASE_NONE && me->GetDistance(who) < 30.0f)
                {
                    SetPhase(PHASE_INTRO);

                    events.ScheduleEvent(EVENT_INTRO_1, 5000);
                    return;
                }

                BossAI::MoveInLineOfSight(who);
            }

            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                if (me->GetHealth() <= damage)
                {
                    if (phase == PHASE_FIVE)
                    {
                        damage = 0;
                        canBeKilled = false;
                        SetPhase(PHASE_SIX);
                    }
                    else if (phase != PHASE_SIX || !canBeKilled)
                        damage = 0;
                }

                if (me->HealthBelowPctDamaged(60, damage) && events.IsInPhase(PHASE_ONE))
                {
                    SetPhase(PHASE_TWO);
                    me->SetReactState(REACT_PASSIVE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
                    me->AttackStop();
                    Talk(SAY_PHASE_2);
                    events.ScheduleEvent(EVENT_VANISH, 3000, 0, PHASE_TWO);
                    return;
                }

                if (me->HealthBelowPctDamaged(10, damage) && events.IsInPhase(PHASE_THREE))
                {
                    DoCast(SPELL_TELEPORT_VISUAL);
                    me->StopMovingOnCurrentPos();
                    me->StopMoving();
                    me->GetMotionMaster()->Clear();
                    me->SetReactState(REACT_PASSIVE);
                    me->AttackStop();
                    me->NearTeleportTo(CenterPos.GetPositionX(), CenterPos.GetPositionY(), CenterPos.GetPositionZ(), CenterPos.GetOrientation());
                    SetPhase(PHASE_FOUR);
                    instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TAG_ARROW);
                    DoCast(me, SPELL_KNEEL, true);
                    Talk(SAY_PHASE_4);
                    events.ScheduleEvent(EVENT_SUMMON_HELPERS, 4000);
                    return;
                }
            }

            void SummonedCreatureDies(Creature* summon, Unit* killer) override
            {
                switch (summon->GetEntry())
                {
                case NPC_JAVIER_CLONE:
                    summon->RemoveCorpse();
                    if (++clonesDead >= CLONES_COUNT)
                    {
                        me->SetVisible(true);
                        Talk(SAY_PHASE_3);
                        events.ScheduleEvent(EVENT_PHASE_THREE, 3000);
                    }
                    break;
                case NPC_JAVIER_HEALER:
                    --healersCount;
                    break;
                case NPC_JAVIER_DEFENDER:
                    --defendersCount;
                    break;
                case NPC_JAVIER_BUFFER:
                    --buffersCount;
                    break;
                case NPC_VOID:
                    summon->RemoveCorpse();
                    break;
                default:
                    break;
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (phase != PHASE_INTRO && !UpdateVictim())
                    return;

                if (!CheckInRoom() && !me->IsInEvadeMode())
                    EnterEvadeMode();

                events.Update(diff);
                //_DoAggroPulse(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_INTRO_1:
                        me->SetReactState(REACT_PASSIVE);
                        Talk(SAY_INTRO_1);
                        events.ScheduleEvent(EVENT_INTRO_2, 4000);
                        break;
                    case EVENT_INTRO_2:
                        Talk(SAY_INTRO_2);
                        events.ScheduleEvent(EVENT_INTRO_3, 5000);
                        break;
                    case EVENT_INTRO_3:
                        Talk(SAY_INTRO_3);
                        DoCast(SPELL_SHADOW_CHANNELING);
                        events.ScheduleEvent(EVENT_INTRO_4, 10000);
                        break;
                    case EVENT_INTRO_4:
                        SummonVoids();
                        events.ScheduleEvent(EVENT_INTRO_5, 3000);
                        break;
                    case EVENT_INTRO_5:
                        DoCast(SPELL_TELEPORT_VISUAL);
                        me->NearTeleportTo(CenterPos.GetPositionX(), CenterPos.GetPositionY(), CenterPos.GetPositionZ(), CenterPos.GetOrientation());
                        Talk(SAY_INTRO_4);
                        events.ScheduleEvent(EVENT_INTRO_6, 4000);
                        break;
                    case EVENT_INTRO_6:
                        Talk(SAY_INTRO_5);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                        DoCast(SPELL_PRESENCE_OF_MASTER);
                        events.ScheduleEvent(EVENT_START_FIGHT, 3000);
                        break;
                    case EVENT_START_FIGHT:
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        events.ScheduleEvent(EVENT_BERSERK, 780000);
                        if (Player* player = me->SelectNearestPlayer(30.0f))
                            AttackStart(player);
                        break;
                    case EVENT_SHADOW_BREATH:
                        DoCast(SPELL_SHADOW_BREATH);
                        events.ScheduleEvent(EVENT_SHADOW_BREATH, 20000, 0, PHASE_ONE);
                        break;
                    case EVENT_DEATH_COIL:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                            me->CastCustomSpell(SPELL_DEATH_COIL, SPELLVALUE_BASE_POINT0, 12000, target, TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_DEATH_COIL, urand(12000, 18000));
                        break;
                    case EVENT_CORRUPTION:
                    {
                        std::list<Unit*> targets;
                        SelectTargetList(targets, 10, SELECT_TARGET_RANDOM, 0.0f, true);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            if (urand(0, 1))
                                DoCast(*itr, SPELL_CORRUPTION, true);
                        events.ScheduleEvent(EVENT_CORRUPTION, 25000);
                        break;
                    }
                    case EVENT_CONSUMPTION:
                    {
                        std::list<Unit*> targets;
                        SelectTargetList(targets, 2, SELECT_TARGET_RANDOM, 0.0f, true);
                        for (std::list<Unit*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            if (me->GetMapId() == (*itr)->GetMapId())
                                (*itr)->CastSpell(*itr, SPELL_CONSUMPTION, TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_CONSUMPTION, 40000, 0, PHASE_ONE);
                        break;
                    }
                    case EVENT_VANISH:
                        clonesDead = 0;
                        SummonClones();
                        me->SetVisible(false);
                        me->NearTeleportTo(CenterPos.GetPositionX(), CenterPos.GetPositionY(), CenterPos.GetPositionZ(), CenterPos.GetOrientation());
                        break;
                    case EVENT_PHASE_THREE:
                        SetPhase(PHASE_THREE);
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
                        AttackStart(me->SelectVictim());
                        events.ScheduleEvent(EVENT_CONSUMPTION_MARK, 4000, 0, PHASE_THREE);
                        events.ScheduleEvent(EVENT_CORRUPTION, 6000);
                        break;
                    case EVENT_CONSUMPTION_MARK:
                    {
                        consumptionTargets.clear();
                        SelectTargetList(consumptionTargets, 3, SELECT_TARGET_RANDOM, 0.0f, true);
                        for (std::list<Unit*>::const_iterator itr = consumptionTargets.begin(); itr != consumptionTargets.end(); ++itr)
                            DoCast(*itr, SPELL_TAG_ARROW, true);
                        events.ScheduleEvent(EVENT_CONSUMPTION_PHASE_THREE, 3000, 0, PHASE_THREE);
                        break;
                    }
                    case EVENT_CONSUMPTION_PHASE_THREE:
                    {
                        for (std::list<Unit*>::const_iterator itr = consumptionTargets.begin(); itr != consumptionTargets.end(); ++itr)
                        {
                            if (me->GetMapId() == (*itr)->GetMapId())
                            {
                                (*itr)->CastSpell(*itr, SPELL_CONSUMPTION, TRIGGERED_FULL_MASK);
                                (*itr)->RemoveAura(SPELL_TAG_ARROW);
                            }
                        }
                        events.ScheduleEvent(EVENT_CONSUMPTION_MARK, 7000, 0, PHASE_THREE);
                        break;
                    }
                    case EVENT_SUMMON_HELPERS:
                        Talk(SAY_HELPERS);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        DoCast(me, SPELL_HARDENED, true);
                        SummonHelpers();
                        events.ScheduleEvent(EVENT_CHECK_HELPERS, 1000);
                        events.ScheduleEvent(EVENT_SPIRIT_BURST, 1000);
                        break;
                    case EVENT_CHECK_HELPERS:
                        if (healersCount > 0)
                            DoCast(me, SPELL_DARK_MENDING, true);
                        if (!defendersCount && me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        if (buffersCount > 0)
                        {
                            Aura* aura = me->GetAura(SPELL_BUFF);
                            if (!aura || aura->GetStackAmount() < 255) // prevent buff reset
                                DoCast(me, SPELL_BUFF, true);
                        }
                        if (healersCount + defendersCount + buffersCount == 0)
                        {
                            events.CancelEvent(EVENT_SPIRIT_BURST);
                            events.ScheduleEvent(EVENT_PHASE_FIVE, 3000);
                            DoCast(SPELL_AURA_BLACK);
                            Talk(SAY_AIR);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NON_ATTACKABLE);
                            me->RemoveAurasDueToSpell(SPELL_HARDENED);
                        }
                        else
                            events.ScheduleEvent(EVENT_CHECK_HELPERS, 2000);
                        break;
                    case EVENT_SPIRIT_BURST:
                        DoCast(me, SPELL_SPIRIT_BURST, true);
                        if (phase == PHASE_FOUR || phase == PHASE_SIX)
                            events.ScheduleEvent(EVENT_SPIRIT_BURST, 2000);
                        break;
                    case EVENT_PHASE_FIVE:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NON_ATTACKABLE);
                        me->RemoveAurasDueToSpell(SPELL_HARDENED);
                        me->RemoveAura(SPELL_KNEEL);
                        me->SetInhabitType(INHABIT_AIR);
                        me->SetCanFly(true);
                        me->SetDisableGravity(true);
                        me->StopMoving();
                        me->StopMovingOnCurrentPos();
                        me->GetMotionMaster()->Clear();
                        me->NearTeleportTo(CenterPos.GetPositionX(), CenterPos.GetPositionY(), CenterPos.GetPositionZ() + 20.0f, CenterPos.GetOrientation());
                        me->SendMovementFlagUpdate();
                        DoCast(SPELL_TELEPORT_VISUAL);
                        SetPhase(PHASE_FIVE);
                        if (Player* player = me->SelectNearestPlayer(80.0f))
                            AttackStartCaster(player, 80.0f);
                        events.ScheduleEvent(EVENT_FALLING_ORBS, 3000, 0, PHASE_FIVE);
                        events.ScheduleEvent(EVENT_SHADOW_BOLT, 2000, 0, PHASE_FIVE);
                        summonAddsTimer = 30000;
                        events.ScheduleEvent(EVENT_ADDS, 6000, 0, PHASE_FIVE);
                        events.ScheduleEvent(EVENT_CONSUMPTION_PHASE_FIVE, 7000, 0, PHASE_FIVE);
                        break;
                    case EVENT_FALLING_ORBS:
                        if (summons.HasEntry(NPC_VOID))
                            for (SummonList::iterator itr = summons.begin(); itr != summons.end(); ++itr)
                                if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
                                    if (summon->GetEntry() == NPC_VOID && summon->AI()->GetGUID() == 0)
                                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                                        {
                                            summon->GetMotionMaster()->Clear();
                                            summon->GetMotionMaster()->MoveFollow(target, 0.0f, 0.0f);
                                            summon->AI()->SetGUID(target->GetGUID(), DATA_TARGET_GUID);
                                            events.ScheduleEvent(EVENT_FALLING_ORBS, 1000);
                                            break;
                                        }
                        break;
                    case EVENT_SHADOW_BOLT:
                        if (!me->HasUnitState(UNIT_STATE_CASTING))
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                                DoCast(target, SPELL_SHADOW_BOLT);
                        events.ScheduleEvent(EVENT_SHADOW_BOLT, 1500, 0, PHASE_FIVE);
                        break;
                    case EVENT_CONSUMPTION_PHASE_FIVE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                            if (target->GetMapId() == me->GetMapId())
                                target->CastSpell(target, SPELL_CONSUMPTION, TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_CONSUMPTION_PHASE_FIVE, 8000, 0, PHASE_FIVE);
                        break;
                    case EVENT_ADDS:
                        SummonAdds();
                        events.ScheduleEvent(EVENT_ADDS, summonAddsTimer, 0, PHASE_FIVE);
                        summonAddsTimer = summonAddsTimer > 10000 ? summonAddsTimer - 3000 : summonAddsTimer;
                        break;
                    case EVENT_OUTRO_1:
                        Talk(SAY_OUTRO_1);
                        events.ScheduleEvent(EVENT_OUTRO_2, 5000);
                        break;
                    case EVENT_OUTRO_2:
                        Talk(SAY_OUTRO_2);
                        events.ScheduleEvent(EVENT_OUTRO_3, 4000);
                        break;
                    case EVENT_OUTRO_3:
                        me->RemoveAura(SPELL_KNEEL);
                        me->CastCustomSpell(SPELL_DARK_MENDING, SPELLVALUE_BASE_POINT0, 1000000, me, TRIGGERED_FULL_MASK);
                        canBeKilled = true;
                        DoCast(me, SPELL_SLOW, true);
                        DoCast(SPELL_FINAL_EXPLOSION);
                        events.ScheduleEvent(EVENT_SPIRIT_BURST, 1000);
                        events.ScheduleEvent(EVENT_OUTRO_4, 32000);
                        break;
                    case EVENT_OUTRO_4:
                        DoCast(me, SPELL_STOP_TIME, true);
                        DoCast(SPELL_KNEEL);
                        events.ScheduleEvent(EVENT_OUTRO_5, 3000);
                        break;
                    case EVENT_OUTRO_5:
                        Talk(SAY_OUTRO_3);
                        if (Unit* victim = me->SelectVictim())
                            if (victim->IsAlive())
                                victim->DealDamage(me, victim, me->GetHealth());
                        break;
                    case EVENT_BERSERK:
                        Talk(SAY_BERSERK);
                        DoCast(me, SPELL_BERSERK, true);
                        break;
                    default:
                        break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void SetPhase(uint32 _phase)
            {
                events.SetPhase(_phase);
                phase = _phase;
                switch (phase)
                {
                case PHASE_TWO:
                case PHASE_FOUR:
                    events.CancelEvent(EVENT_CORRUPTION);
                    events.CancelEvent(EVENT_DEATH_COIL);
                    break;
                case PHASE_SIX:
                    me->SetCanFly(false);
                    me->SetDisableGravity(false);
                    me->SendMovementFlagUpdate();
                    me->GetMotionMaster()->MoveFall(0, CenterPos.GetPositionZ());
                    DoCast(me, SPELL_KNEEL, true);
                    me->RemoveAura(SPELL_AURA_BLACK);
                    summons.DespawnAll();
                    events.ScheduleEvent(EVENT_OUTRO_1, 3000);
                    break;
                default:
                    break;
                }
            }

            void SummonVoids()
            {
                float radius = CenterPos.GetExactDist2d(me->GetPositionX(), me->GetPositionY());
                float angle = CenterPos.GetAngle(me->GetPositionX(), me->GetPositionY());
                float step = M_PI / 8.0f;

                float z = me->GetPositionZ() + 10.0f;
                for (uint8 i = 0; i < 16; angle += step, ++i)
                {
                    float x = CenterPos.GetPositionX() + radius * cosf(angle);
                    float y = CenterPos.GetPositionY() + radius * sinf(angle);
                    me->SummonCreature(NPC_VOID, x, y, z);
                }
            }

            void SummonClones()
            {
                for (uint8 i = 0; i < CLONES_COUNT; ++i)
                    me->SummonCreature(NPC_JAVIER_CLONE, ClonesPositions[i]);
            }

            void SummonHelpers()
            {
                for (int i = 0; i < DEFENDERS_COUNT; ++i)
                    me->SummonCreature(NPC_JAVIER_DEFENDER, DefendersPositions[i]);
                for (int i = 0; i < BUFFERS_COUNT; ++i)
                    me->SummonCreature(NPC_JAVIER_BUFFER, BuffersPositions[i]);

                float radius = 6.5f;
                float angle = 0.0f;
                float step = 2 * M_PI / HEALERS_COUNT;

                float z = me->GetPositionZ();
                for (uint8 i = 0; i < HEALERS_COUNT; angle += step, ++i)
                {
                    float x = CenterPos.GetPositionX() + radius * cosf(angle);
                    float y = CenterPos.GetPositionY() + radius * sinf(angle);
                    me->SummonCreature(NPC_JAVIER_HEALER, x, y, z);
                }

                defendersCount = DEFENDERS_COUNT;
                buffersCount = BUFFERS_COUNT;
                healersCount = HEALERS_COUNT;
            }

            void SummonAdds()
            {
                float radius = 6.5f;
                float angle = 0.0f;
                float step = 2 * M_PI / SOLDIERS_COUNT;

                float z = CenterPos.GetPositionZ();
                for (uint8 i = 0; i < SOLDIERS_COUNT; angle += step, ++i)
                {
                    float x = CenterPos.GetPositionX() + radius * cosf(angle);
                    float y = CenterPos.GetPositionY() + radius * sinf(angle);
                    me->SummonCreature(NPC_JAVIER_SOLDIER, x, y, z);
                }
            }

        private:
            InstanceScript* instance;
            uint8 phase;
            uint8 clonesDead;
            uint8 clonesCount;
            std::list<Unit*> consumptionTargets;
            uint8 defendersCount;
            uint8 buffersCount;
            uint8 healersCount;
            uint32 summonAddsTimer;
            bool canBeKilled;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<boss_javier_voidbringerAI>(creature);
        }
};

class npc_void : public CreatureScript
{
    public:
        npc_void() : CreatureScript("npc_void") { }

        struct npc_voidAI : public ScriptedAI
        {
            npc_voidAI(Creature *creature) : ScriptedAI(creature)
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
                instance = creature->GetInstanceScript();
                homePos = creature->GetHomePosition();
                me->SetReactState(REACT_PASSIVE);
                _targetGUID = 0;
                _exploded = false;
                events.Reset();
            }

            Position homePos;
            InstanceScript* instance;
            EventMap events;
            uint64 _targetGUID;
            bool _exploded;

            void IsSummonedBy(Unit* summoner) override
            {
                events.ScheduleEvent(EVENT_VOID_START_MOVING, 2000);
                DoCast(SPELL_VOID_SUMMON_VISUAL);
                _targetGUID = 0;
            }

            void MovePath()
            {
                Movement::MoveSplineInit init(me);
                FillCirclePath(CenterPos, homePos.GetExactDist2d(CenterPos.GetPositionX(), CenterPos.GetPositionY()), me->GetPositionZ(), init.Path(), true);
                init.SetWalk(false);
                init.SetCyclic();
                init.Launch();
            }

            void FillCirclePath(Position const& centerPos, float radius, float z, Movement::PointsArray& path, bool clockwise)
            {
                float step = clockwise ? -M_PI / 8.0f : M_PI / 8.0f;
                float angle = centerPos.GetAngle(me->GetPositionX(), me->GetPositionY());

                for (uint8 i = 0; i < 16; angle += step, ++i)
                {
                    G3D::Vector3 point;
                    point.x = centerPos.GetPositionX() + radius * cosf(angle);
                    point.y = centerPos.GetPositionY() + radius * sinf(angle);
                    point.z = z;
                    path.push_back(point);
                }
            }

            void SetGUID(uint64 guid, int32 type) override
            {
                if (type == DATA_TARGET_GUID)
                {
                    _targetGUID = guid;
                    _exploded = false;
                }
            }

            uint64 GetGUID(int32 type) const override
            {
                return _targetGUID;
            }

            void UpdateAI(uint32 diff) override
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_VOID_START_MOVING:
                        MovePath();
                        break;
                    default:
                        break;
                    }
                }

                if (_targetGUID && !_exploded)
                {
                    if (Player* target = ObjectAccessor::GetPlayer(*me, _targetGUID))
                        if (target->IsWithinDist(me, 5.0f))
                        {
                            _exploded = true;
                            me->GetMotionMaster()->Clear();
                            DoCast(me, SPELL_EXPLOSION, true);
                            me->DespawnOrUnsummon(1000);
                        }
                }
            }

            void SpellHit(Unit* attacker, const SpellInfo* info) override
            {
                if (info->ManaCost || info->ManaCostPercentage)
                    me->CastSpell(attacker, SPELL_SHADOW_BOLT, TRIGGERED_FULL_MASK);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_voidAI>(creature);
        }
};

class npc_javier_clone : public CreatureScript
{
    public:
        npc_javier_clone() : CreatureScript("npc_javier_clone") { }

        struct npc_javier_cloneAI : public ScriptedAI
        {
            npc_javier_cloneAI(Creature *creature) : ScriptedAI(creature)
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                interrupted = false;
                events.Reset();
            }

            void IsSummonedBy(Unit* summoner) override
            {
                DoCast(SPELL_CLONE_TELEPORT_VISUAL);
                events.ScheduleEvent(EVENT_CLONE_START_ATTACK, 3000);
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CLONE_START_ATTACK:
                            me->SetReactState(REACT_AGGRESSIVE);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            if (Player* player = me->SelectNearestPlayer(30.0f))
                                me->AI()->AttackStart(player);
                            DoZoneInCombat();
                            events.ScheduleEvent(EVENT_IMMOLATE, 3000);
                            events.ScheduleEvent(EVENT_SPELL_LOCK, urand(5000, 9000));
                            events.ScheduleEvent(EVENT_KNOCBACK, urand(5000, 15000));
                            break;
                        case EVENT_IMMOLATE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                                DoCast(target, SPELL_IMMOLATE, false);
                            events.ScheduleEvent(EVENT_IMMOLATE, urand(6000, 12000));
                            break;
                        case EVENT_SPELL_LOCK:
                            interrupted = false;
                            for (auto threat : me->getThreatManager().getThreatList())
                            {
                                if (Unit* target = ObjectAccessor::GetUnit(*me, threat->getUnitGuid()))
                                {
                                    if (target && target->GetTypeId() == TYPEID_PLAYER && target->ToPlayer()->IsNonMeleeSpellCast(false, false, true) && !urand(0, 2))
                                    {
                                        DoCast(target, SPELL_SPELL_LOCK, true);
                                        events.ScheduleEvent(EVENT_SPELL_LOCK, urand(8000, 12000));
                                        interrupted = true;
                                        break;
                                    }
                                }
                            }
                            if (!interrupted)
                                events.ScheduleEvent(EVENT_SPELL_LOCK, urand(1000, 2000));
                            break;
                        case EVENT_KNOCBACK:
                        {
                            std::vector<uint64> playerGUIDs;
                            for (auto threat : me->getThreatManager().getThreatList())
                            {
                                if (Player* player = ObjectAccessor::GetPlayer(*me, threat->getUnitGuid()))
                                    if (player && me->IsWithinDist2d(player, 7.0f))
                                        playerGUIDs.push_back(player->GetGUID());
                            }

                            if (!playerGUIDs.empty())
                            {
                                if (Player* target = ObjectAccessor::GetPlayer(*me, Trinity::Containers::SelectRandomContainerElement(playerGUIDs)))
                                    DoCast(target, SPELL_KNOCKBACK, true);
                                events.Repeat(urand(15000, 25000));
                                break;
                            }
                            else
                                events.Repeat(1000);
                            break;
                        }
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            EventMap events;
            bool interrupted;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_javier_cloneAI>(creature);
        }
};

class npc_javier_helper : public CreatureScript
{
    public:
        npc_javier_helper() : CreatureScript("npc_javier_helper") { }

        struct npc_javier_helperAI : public ScriptedAI
        {
            npc_javier_helperAI(Creature *creature) : ScriptedAI(creature)
            {
                me->SetReactState(REACT_PASSIVE);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
            }

            void IsSummonedBy(Unit* summoner) override
            {
                DoCast(SPELL_CLONE_TELEPORT_VISUAL);
                if (summoner)
                {
                    me->SetFacingToObject(summoner);
                    javierGUID = summoner->GetGUID();
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (Creature* javier = ObjectAccessor::GetCreature(*me, javierGUID))
                {
                    switch (me->GetEntry())
                    {
                    case NPC_JAVIER_BUFFER:
                        DoCast(javier, SPELL_RED_BEAM);
                        break;
                    case NPC_JAVIER_DEFENDER:
                        DoCast(javier, SPELL_BLUE_BEAM);
                        break;
                    case NPC_JAVIER_HEALER:
                        DoCast(javier, SPELL_GREEN_BEAM);
                        break;
                    default:
                        break;
                    }
                }
            }

            uint64 javierGUID;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_javier_helperAI>(creature);
        }
};

class npc_javier_soldier : public CreatureScript
{
    public:
        npc_javier_soldier() : CreatureScript("npc_javier_soldier") { }

        struct npc_javier_soldierAI : public ScriptedAI
        {
            npc_javier_soldierAI(Creature *creature) : ScriptedAI(creature)
            {
                events.Reset();
                me->SetReactState(REACT_AGGRESSIVE);
                enraged = false;
            }

            void IsSummonedBy(Unit* summoner) override
            {
                events.ScheduleEvent(EVENT_SOLDIER_START_ATTACK, 2000);
                DoCast(SPELL_TELEPORT_VISUAL);
                me->SetControlled(true, UNIT_STATE_STUNNED);
            }

            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                if (!enraged)
                    if (me->HealthBelowPctDamaged(8, damage))
                    {
                        enraged = true;
                        DoCast(me, SPELL_FRENZY, true);
                    }
            }

            void UpdateAI(uint32 diff) override
            {
                UpdateVictim();
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_SOLDIER_START_ATTACK:
                        me->SetControlled(false, UNIT_STATE_STUNNED);
                        if (Unit* target = me->SelectVictim())
                            AttackStart(target);
                        else if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST))
                            AttackStart(target);
                        events.ScheduleEvent(EVENT_CLEAVE, urand(5000, 7000));
                        events.ScheduleEvent(EVENT_MORTAL_STRIKE, 3000);
                        break;
                    case EVENT_MORTAL_STRIKE:
                        if (me->GetVictim())
                            DoCast(me->GetVictim(), SPELL_MORTAL_STRIKE, true);
                        events.ScheduleEvent(EVENT_MORTAL_STRIKE, urand(20000, 30000));
                        break;
                    case EVENT_CLEAVE:
                        if (me->GetVictim())
                            DoCast(me->GetVictim(), SPELL_CLEAVE, true);
                        events.ScheduleEvent(EVENT_CLEAVE, urand(6000, 8000));
                        break;
                    default:
                        break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            EventMap events;
            bool enraged;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_javier_soldierAI>(creature);
        }
};

void AddSC_boss_javier_voidbringer()
{
    new boss_javier_voidbringer();
    new npc_void();
    new npc_javier_clone();
    new npc_javier_helper();
    new npc_javier_soldier();
}