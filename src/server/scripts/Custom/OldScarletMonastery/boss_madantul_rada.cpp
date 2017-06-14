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
#include "MoveSplineInit.h"
#include "MoveSpline.h"
#include "Group.h"
#include "ScriptedGossip.h"

enum madanSpells
{
    SPELL_BUFF = 64036,
    SPELL_RED_BEAM_DROPS = 30944,
    SPELL_SLOW = 65210,
    SPELL_ASCEND = 64487,
    SPELL_HOVER = 11010,
    SPELL_BLADESTORM = 69652,
    SPELL_SILENCE = 42201,
    SPELL_MYSTICAL_BOLT = 51787,
    SPELL_LOST_SOUL = 51788,
    SPELL_BUFF_GAIN_VISUAL = 40436,
    SPELL_ENERGY_GAIN_VISUAL = 40387,
    SPELL_ARCANE_EXPLOSION = 36607, // Uzyty w sam test aura jako dmg spell
    SPELL_SAMS_TEST_AURA = 26659, // sam test aura
    SPELL_FEL_BREATH = 40561,
    SPELL_VEIL_OF_SHADOWS = 22687,
    SPELL_HOOK = 71140,
    SPELL_SHADOW_SCYTHE = 23278, // nie uzywane, zrobie spellscript
    SPELL_ARCANE_CLEAVE = 50573,
    SPELL_REARING_STOMP = 51681,
    SPELL_GHOSTBUSTERS_BEAM = 45967, // pierwszy lepszy,trzeba znalezc lepszy
    SPELL_FROST_AURA = 70084,
    SPELL_EXPLODING_AURA = 69017,
    SPELL_EXPLOSIVE_BARRAGE = 69019,
    SPELL_CRUSH = 49639,
    SPELL_DARKNESS = 45996,
    SPELL_ELECTRO_SHOCK = 56319,
};

enum madanTexts
{
    SAY_MADAN_0 = 0, // I am Madantul Rada, the strongest warrior among risens. And who might you be?
    SAY_MADAN_1 = 1, // Come forth Overlords, Let's finish this.
    SAY_MADAN_2 = 2, // Have you seen my puppy? Oh there it is. It's feeding time Dera'tin'jeragoth
    SAY_MADAN_3 = 3, // I haven't used this magic in years. Please survive for a little longer, let me enjoy this moment!
    SAY_MADAN_4 = 4, // Brr.. it's getting cold in here.
    SAY_MADAN_5 = 5, // The joy of killing! the joy of seeing killing done - this is what drives me! | Killing is indeed a pleasure unmatched in this world. Perhaps it�s a pleasure we could share
    SAY_MADAN_6 = 6, // I have failed des..
};

enum madanEvents
{
    EVENT_UPDATE_POWER = 1,
    EVENT_PHASE_TRANSITIONa = 2,
    EVENT_PHASE_TRANSITIONb = 3,
    EVENT_FINISH_ARCANE_PHASE = 4,
    EVENT_SPAWN_HOUNDS = 5,
    EVENT_BLADESTORM = 7,
    EVENT_MYSTICAL_BOLT = 8,
    EVENT_CHECK_AURAS = 9,
    EVENT_KNOCKBACK = 10,
    EVENT_PULL = 11,
    EVENT_TELEPORT = 12,
    EVENT_ENERGY_IN_P2 = 13,
    EVENT_PRE_FEL_BREATH = 14,
    EVENT_VEIL_OF_SHADOWS = 15,
    EVENT_FEL_BREATH = 16,
    EVENT_FINISH_BREATH = 17,
    EVENT_HOOK_MEH_BABY = 18, // dodac tekst "$n, GET YOUR ASS OVER HERE"?
    EVENT_SHADOW_SCYTHE = 19,
    EVENT_ARCANE_CLEAVE = 20,
    EVENT_REARING_STOMP = 21,
    EVENT_SPAWN_MEMORY_OF_ICE = 22,
    EVENT_MEMORY_START_CASTING = 23,
    EVENT_KAMIKAZE = 24,
    EVENT_CRUSH = 25,
    EVENT_CHARGES = 26, // debuff ktory trzeba zbic melee atakami
    EVENT_DERAGOTH_HELPER = 27,
};

enum madanActions
{
    ACTION_MEMORY_MOVE = 1,
    ACTION_STOP_DERAGOTH = 2,
    ACTION_RESTART_DERAGOTH = 3,
};

enum madanMisc
{
    MAX_ALLOWED_DAMAGE_TAKEN = 100000,
    POINT_ALTAR = 1,
    POINT_STAIRS = 2,
};

Position moveAltarPos = { 373.814f, -105.739f, 34.643f, 4.745f };
Position moveStairsPos = { 374.70f, -82.41f, 30.83f, 1.56f };
Position teleportMidRoom = { 374.68f, -66.23f, 30.82f, 4.75f };
Position memoryOfIceSpawn = { 374.29f, -33.31f, 30.82f, 4.78f };
Position markerSpawnPos = { 373.92f, -82.51f, 30.83f, 0.05f };
Position markerMovePos = { 431.21f, -88.80f, 30.82f, 6.25f };

Position beamChannelersPos[3] =
{
    { 382.690f, -94.273f, 32.494f, 4.011f },
    { 374.318f, -94.074f, 32.495f, 4.745f },
    { 365.852f, -94.520f, 32.495f, 5.319f },
};

Position deragothSpawnPos[2] =
{
    { 368.82f, -47.86f, 30.82f, 4.92f },
    { 379.74f, -48.66f, 30.82f, 4.56f },
};

class boss_madantul_rada : public CreatureScript
{
    public:
        boss_madantul_rada() : CreatureScript("boss_madantul_rada") { }

        struct boss_madantul_radaAI : public BossAI
        {
            boss_madantul_radaAI(Creature* creature) : BossAI(creature, DATA_MADANTUL_RADA)
            {
                instance = me->GetInstanceScript();
                //SetImmuneToPushPullEffects(true);
                me->setPowerType(POWER_ENERGY);
                me->SetMaxPower(POWER_ENERGY, 100);
            }

            void Reset() override
            {
                _Reset();
                me->SetPower(POWER_ENERGY, 0);
                events.SetPhase(PHASE_NONE);
                me->SetReactState(REACT_AGGRESSIVE);
                me->SetHealth(me->GetMaxHealth());
                summons.DespawnAll();
                me->RemoveAurasDueToSpell(SPELL_HOVER);
                previousDamageTaken = 0;
                channelersCounter = 0;
                memoryCounter = 0;
            }

            void EnterCombat(Unit* target) override
            {
                if (!instance->CheckRequiredBosses(DATA_MADANTUL_RADA))
                    return;

                Talk(SAY_MADAN_0);
                _EnterCombat();
                list.clear();
                SaveEveryoneToList();
                events.SetPhase(PHASE_ONE);
                events.ScheduleEvent(EVENT_UPDATE_POWER, 5000);
                events.ScheduleEvent(EVENT_MYSTICAL_BOLT, 6000);
                events.ScheduleEvent(EVENT_TELEPORT, 15000);
                events.ScheduleEvent(EVENT_ARCANE_CLEAVE, 3000);
            }


            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                if (!instance->CheckRequiredBosses(DATA_MADANTUL_RADA))
                    damage = 0;

                if (events.IsInPhase(PHASE_TRANSITION))
                    damage = 0;

                previousDamageTaken += damage;

                if (me->HealthBelowPctDamaged(75, damage) && events.IsInPhase(PHASE_ONE))
                {
                    events.SetPhase(PHASE_TWO);
                    events.ScheduleEvent(EVENT_HOOK_MEH_BABY, urand(6000, 8000));
                    events.ScheduleEvent(EVENT_CHARGES, 15000);
                    events.CancelEvent(EVENT_TELEPORT);
                }

                if (me->HealthBelowPctDamaged(50, damage) && events.IsInPhase(PHASE_TWO))
                {
                    events.SetPhase(PHASE_THREE);
                    events.ScheduleEvent(EVENT_SHADOW_SCYTHE, 1500);
                    events.ScheduleEvent(EVENT_REARING_STOMP, 15000);
                    events.CancelEvent(EVENT_CHARGES);
                }

                if (me->HealthBelowPctDamaged(25, damage) && events.IsInPhase(PHASE_THREE))
                {
                    events.SetPhase(PHASE_FOUR);
                    events.ScheduleEvent(EVENT_KAMIKAZE, 1000);
                    events.ScheduleEvent(EVENT_CRUSH, 2500);
                    events.CancelEvent(EVENT_HOOK_MEH_BABY);
                    events.CancelEvent(EVENT_SPAWN_MEMORY_OF_ICE);
                    summons.DespawnEntry(NPC_MEMORY_OF_ICE);
                }
            }

            void JustSummoned(Creature* summon) override
            {
                summons.Summon(summon);
                summon->ToTempSummon()->SetTempSummonType(TEMPSUMMON_CORPSE_DESPAWN);
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                switch (id)
                {
                case POINT_ALTAR:
                    events.ScheduleEvent(EVENT_PHASE_TRANSITIONb, 100);
                    break;
                case POINT_STAIRS:
                    events.ScheduleEvent(EVENT_UPDATE_POWER, 5000);
                    events.ScheduleEvent(EVENT_SPAWN_HOUNDS, 1000);
                    events.ScheduleEvent(EVENT_ARCANE_CLEAVE, 3000);
                    events.ScheduleEvent(EVENT_MYSTICAL_BOLT, 5500);
                    AttackStart(me->SelectVictim());
                    me->SetReactState(REACT_AGGRESSIVE);
                    previousDamageTaken = 0;
                    break;
                default:
                    break;
                }
            }

            void SummonedCreatureDies(Creature* summon, Unit* killer) override
            {
                switch (summon->GetEntry())
                {
                case NPC_RISEN_OVERLORD:
                    ++channelersCounter;
                    if (channelersCounter == 3)
                    {
                        channelersCounter = 0;
                        events.ScheduleEvent(EVENT_FINISH_ARCANE_PHASE, 1);
                        me->CastStop();
                    }
                    break;
                default:
                    break;
                }
            }

            void KilledUnit(Unit* victim) override
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    if (urand(0, 3))
                        Talk(SAY_MADAN_5);
            }

            void JustDied(Unit* killer) override
            {
                _JustDied();
                summons.DespawnAll();
                Talk(SAY_MADAN_6);
                me->SummonCreature(NPC_ARROW_MARKER, markerSpawnPos);
            }

            void SpellHitTarget(Unit* target, SpellInfo const* spellInfo) override
            {
                if (spellInfo->Id == SPELL_ASCEND)
                    events.ScheduleEvent(EVENT_FINISH_ARCANE_PHASE, 1);
            }

            void SaveEveryoneToList()
            {
                Map* map = me->GetMap();
                if (!map->IsDungeon())
                    return;

                Map::PlayerList const& PlayerList = map->GetPlayers();
                for (Map::PlayerList::const_iterator itr = PlayerList.begin(); itr != PlayerList.end(); ++itr)
                    if (Player* player = itr->GetSource())
                        if (player->IsAlive())
                            list.push_back(player->GetGUID());
            }

            void UpdatePower()
            {
                if (events.IsInPhase(PHASE_FOUR))
                    return;

                if (previousDamageTaken > MAX_ALLOWED_DAMAGE_TAKEN)
                {
                    me->ModifyPower(POWER_ENERGY, 20);
                    DoCast(SPELL_BUFF_GAIN_VISUAL);
                }
                else
                {
                    me->ModifyPower(POWER_ENERGY, 5);
                    DoCast(SPELL_BUFF_GAIN_VISUAL);
                }

                if (me->GetPower(POWER_ENERGY) == 100)
                {
                    if (events.IsInPhase(PHASE_ONE))
                        events.ScheduleEvent(EVENT_PHASE_TRANSITIONa, 1000);
                    else if (events.IsInPhase(PHASE_TWO))
                        events.ScheduleEvent(EVENT_ENERGY_IN_P2, 1000);
                    else if (events.IsInPhase(PHASE_THREE))
                        events.ScheduleEvent(EVENT_SPAWN_MEMORY_OF_ICE, 1000);
                }

                previousDamageTaken = 0;
            }

            void DoPull(float x, float y, float z)
            {
                for (std::list<uint64>::iterator itr = list.begin(); itr != list.end(); ++itr)
                {
                    if (Player* player = ObjectAccessor::FindPlayer(*itr))
                        if (player->IsAlive())
                            if (player->IsWithinDist(me, 300.0f))
                            {
                                player->RemoveAurasDueToSpell(SPELL_SILENCE);
                                player->GetMotionMaster()->MoveJump(x, y, z, 900 * 0.1f, 65 * 0.1f);
                            }
                }
            }

            void DoAoeKnockback(float x, float y, float sXY, float sZ)
            {
                for (std::list<uint64>::iterator itr = list.begin(); itr != list.end(); ++itr)
                {
                    if (Player* player = ObjectAccessor::FindPlayer(*itr))
                        if (player->IsAlive())
                            if (player->IsWithinDist(me, 300.0f))
                            {
                                me->AddAura(SPELL_SILENCE, player);
                                player->KnockbackFrom(x, y, sXY, sZ);
                            }
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                //_DoAggroPulse(diff);
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_UPDATE_POWER:
                        UpdatePower();

                        events.ScheduleEvent(EVENT_UPDATE_POWER, 5000);
                        break;
                    case EVENT_PHASE_TRANSITIONa:
                        // takie cancel event bo cos mi nie przerywalo mystical bolta kiedys,potem wyrzucilem grupy i fazy i juz teraz mi sie nie chce przerabiac na nowo :/
                        Talk(SAY_MADAN_1);
                        events.SetPhase(PHASE_TRANSITION);
                        events.CancelEvent(EVENT_MYSTICAL_BOLT);
                        events.CancelEvent(EVENT_UPDATE_POWER);
                        events.CancelEvent(EVENT_ARCANE_CLEAVE);
                        events.CancelEvent(EVENT_TELEPORT);
                        events.CancelEvent(EVENT_KNOCKBACK);
                        events.CancelEvent(EVENT_PULL);
                        events.CancelEvent(EVENT_BLADESTORM);
                        DoStopAttack();
                        me->SetReactState(REACT_PASSIVE);
                        me->GetMotionMaster()->MovePoint(POINT_ALTAR, moveAltarPos);
                        break;
                    case EVENT_PHASE_TRANSITIONb:
                    {
                        me->SetFacingTo(1.58f);
                        me->CastCustomSpell(SPELL_SLOW, SPELLVALUE_BASE_POINT1, -1500, me, TRIGGERED_FULL_MASK);
                        DoCast(me, SPELL_HOVER, true);

                        CustomSpellValues values;
                        values.AddSpellMod(SPELLVALUE_RADIUS_MOD, me->GetFloatValue(OBJECT_FIELD_SCALE_X) * 50000);
                        values.AddSpellMod(SPELLVALUE_BASE_POINT0, 500000);
                        me->CastCustomSpell(SPELL_ASCEND, values, (Unit*)NULL, TRIGGERED_NONE);

                        for (uint8 i = 0; i < 3; ++i)
                        {
                            if (Creature* channeler = me->SummonCreature(NPC_RISEN_OVERLORD, beamChannelersPos[i]))
                                channeler->AI()->IsSummonedBy(me);
                        }
                        break;
                    }
                    case EVENT_FINISH_ARCANE_PHASE:
                        me->RemoveAurasDueToSpell(SPELL_HOVER);
                        me->RemoveAurasDueToSpell(SPELL_SLOW);
                        me->GetMotionMaster()->MovePoint(POINT_STAIRS, moveStairsPos);
                        me->SetPower(POWER_ENERGY, 0);
                        events.SetPhase(PHASE_ONE);
                        summons.DespawnEntry(NPC_RISEN_OVERLORD);
                        break;
                    case EVENT_SPAWN_HOUNDS:
                        Talk(SAY_MADAN_2);
                        if (Creature* deragoth = me->SummonCreature(NPC_DERAGOTH, deragothSpawnPos[urand(0, 1)], TEMPSUMMON_CORPSE_DESPAWN))
                            deragoth->AI()->IsSummonedBy(me);
                        break;
                    case EVENT_TELEPORT:
                    {
                        EntryCheckPredicate pred(NPC_DERAGOTH);
                        summons.DoAction(ACTION_STOP_DERAGOTH, pred);
                        me->SetReactState(REACT_PASSIVE);
                        DoStopAttack();
                        events.CancelEvent(EVENT_UPDATE_POWER);
                        events.CancelEvent(EVENT_MYSTICAL_BOLT);
                        events.CancelEvent(EVENT_ARCANE_CLEAVE);
                        me->NearTeleportTo(moveStairsPos.GetPositionX(), moveStairsPos.GetPositionY(), moveStairsPos.GetPositionZ(), moveStairsPos.GetOrientation());
                        DoTeleportAll(teleportMidRoom.GetPositionX(), teleportMidRoom.GetPositionY(), teleportMidRoom.GetPositionZ(), teleportMidRoom.GetOrientation());

                        events.ScheduleEvent(EVENT_KNOCKBACK, 200);
                        break;
                    }
                    case EVENT_KNOCKBACK:
                        DoAoeKnockback(me->GetPositionX(), me->GetPositionY(), 80.0f, 15.0f);

                        events.ScheduleEvent(EVENT_PULL, 600);
                        break;
                    case EVENT_PULL:
                        DoPull(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());

                        events.ScheduleEvent(EVENT_BLADESTORM, 2600);
                        events.ScheduleEvent(EVENT_TELEPORT, 80000);
                        break;
                    case EVENT_BLADESTORM:
                    {
                        AttackStart(me->GetVictim());
                        DoCast(SPELL_BLADESTORM);
                        me->SetReactState(REACT_AGGRESSIVE);
                        events.ScheduleEvent(EVENT_UPDATE_POWER, 5000);
                        events.ScheduleEvent(EVENT_MYSTICAL_BOLT, 10000);
                        events.ScheduleEvent(EVENT_ARCANE_CLEAVE, 3500);
                        EntryCheckPredicate pred(NPC_DERAGOTH);
                        summons.DoAction(ACTION_RESTART_DERAGOTH, pred);
                        break;
                    }
                    case EVENT_MYSTICAL_BOLT:
                        me->CastCustomSpell(SPELL_MYSTICAL_BOLT, SPELLVALUE_BASE_POINT0, urand(15000, 25000), me->SelectVictim(), TRIGGERED_FULL_MASK);

                        events.ScheduleEvent(EVENT_MYSTICAL_BOLT, 9000);
                        events.ScheduleEvent(EVENT_CHECK_AURAS, 1000);
                        break;
                    case EVENT_CHECK_AURAS:
                        if (Unit* target = me->GetVictim())
                            if (target->HasAura(SPELL_LOST_SOUL))
                                DoModifyThreatPercent(target, -100);
                        break;
                    case EVENT_ENERGY_IN_P2:
                        me->SummonCreature(NPC_DARKNESS_CASTER, *me);
                        me->SetPower(POWER_ENERGY, 0);
                        Talk(SAY_MADAN_3);
                        break;
                    case EVENT_CHARGES:
                        for (std::list<uint64>::iterator itr = list.begin(); itr != list.end(); ++itr)
                            if (Player* player = ObjectAccessor::FindPlayer(*itr))
                                if (player->IsAlive())
                                    player->CastSpell(player, SPELL_SAMS_TEST_AURA);

                        events.ScheduleEvent(EVENT_CHARGES, 80000);
                    case EVENT_HOOK_MEH_BABY:
                        if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST))
                            me->CastCustomSpell(SPELL_HOOK, SPELLVALUE_BASE_POINT0, urand(4000, 6000), target, TRIGGERED_FULL_MASK);

                        events.ScheduleEvent(EVENT_HOOK_MEH_BABY, urand(20000, 25000));
                        break;
                    case EVENT_ARCANE_CLEAVE:
                        me->CastCustomSpell(SPELL_ARCANE_CLEAVE, SPELLVALUE_BASE_POINT0, 125, me->GetVictim(), TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_ARCANE_CLEAVE, urand(8000, 14000));
                        break;
                    case EVENT_SHADOW_SCYTHE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                            me->CastCustomSpell(SPELL_SHADOW_SCYTHE, SPELLVALUE_BASE_POINT0, urand(8000, 9000), target, TRIGGERED_FULL_MASK);

                        events.ScheduleEvent(EVENT_SHADOW_SCYTHE, urand(30000, 35000));
                        break;
                    case EVENT_REARING_STOMP:
                        me->CastCustomSpell(SPELL_REARING_STOMP, SPELLVALUE_RADIUS_MOD, 2500, (Unit*)nullptr, TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_REARING_STOMP, 45000);
                        break;
                    case EVENT_SPAWN_MEMORY_OF_ICE:
                        Talk(SAY_MADAN_4);
                        ++memoryCounter;
                        me->SetPower(POWER_ENERGY, 0);
                        if (Creature* memory = me->SummonCreature(NPC_MEMORY_OF_ICE, memoryOfIceSpawn))
                        {
                            memory->AI()->IsSummonedBy(me);
                            memory->AI()->DoAction(ACTION_MEMORY_MOVE);
                        }
                        me->RemoveAurasDueToSpell(SPELL_FROST_AURA);
                        me->CastCustomSpell(SPELL_FROST_AURA, SPELLVALUE_BASE_POINT0, 500 * memoryCounter, me, TRIGGERED_NONE);
                        break;
                    case EVENT_KAMIKAZE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                        {
                            Position pos;
                            target->GetPosition(&pos);
                            pos.m_positionZ += 10.0f;
                            me->SummonCreature(NPC_KAMIKAZE, pos);
                        }
                        events.ScheduleEvent(EVENT_KAMIKAZE, 2000);
                        break;
                    case EVENT_CRUSH:
                        me->CastCustomSpell(SPELL_CRUSH, SPELLVALUE_BASE_POINT0, 180, me->SelectVictim(), TRIGGERED_FULL_MASK);

                        events.ScheduleEvent(EVENT_CRUSH, urand(15000, 20000));
                        break;
                    default:
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        private:
            InstanceScript* instance;
            uint32 previousDamageTaken;
            uint32 channelersCounter;
            uint32 memoryCounter;
            std::list<uint64> list;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<boss_madantul_radaAI>(creature);
        }
};

// Dera''tin''jeragoth
class npc_deragoth_hound : CreatureScript
{
    public:
        npc_deragoth_hound() : CreatureScript("npc_deragoth_hound") { }

        struct npc_deragoth_houndAI : public ScriptedAI
        {
            npc_deragoth_houndAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void Reset() override
            {
                events.Reset();
                DoZoneInCombat(me, 200.0f);
                me->SetInCombatWithZone();
            }

            void EnterCombat(Unit* target) override
            {
                events.ScheduleEvent(EVENT_PRE_FEL_BREATH, 8000);
                events.ScheduleEvent(EVENT_VEIL_OF_SHADOWS, 3000);
                events.ScheduleEvent(EVENT_DERAGOTH_HELPER, 3500);
            }

            void DoAction(int32 param) override
            {
                switch (param)
                {
                case ACTION_STOP_DERAGOTH:
                    me->SetControlled(true, UNIT_STATE_STUNNED);
                    break;
                case ACTION_RESTART_DERAGOTH:
                    me->SetControlled(false, UNIT_STATE_STUNNED);
                    break;
                default:
                    break;
                }
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (id == 10000)
                {
                    DoStopAttack();
                    me->SetReactState(REACT_PASSIVE);
                    events.ScheduleEvent(EVENT_FEL_BREATH, 1500);
                }
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
                    case EVENT_PRE_FEL_BREATH:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                            me->GetMotionMaster()->MoveCharge(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 42.0f, 10000, nullptr, true);
                        break;
                    case EVENT_FEL_BREATH:
                        me->GetMotionMaster()->MoveRotate(15000, ROTATE_DIRECTION_RIGHT);
                        me->CastCustomSpell(SPELL_FEL_BREATH, SPELLVALUE_BASE_POINT1, urand(4500, 7000), (Unit*)nullptr, TRIGGERED_FULL_MASK);

                        events.ScheduleEvent(EVENT_FINISH_BREATH, 10000);
                        events.ScheduleEvent(EVENT_PRE_FEL_BREATH, 80000);
                        break;
                    case EVENT_FINISH_BREATH:
                        AttackStart(me->SelectVictim());
                        me->SetReactState(REACT_AGGRESSIVE);
                        break;
                    case EVENT_VEIL_OF_SHADOWS:
                        DoCast(SPELL_VEIL_OF_SHADOWS);

                        events.ScheduleEvent(EVENT_VEIL_OF_SHADOWS, 19000);
                        break;
                    case EVENT_DERAGOTH_HELPER:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                            target->CastCustomSpell(SPELL_ELECTRO_SHOCK, SPELLVALUE_BASE_POINT0, 100000, (Unit*)nullptr, TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_DERAGOTH_HELPER, 10000);
                        break;
                    default:
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }

        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_deragoth_houndAI>(creature);
        }
};

class npc_drops_channeler : CreatureScript
{
    public:
        npc_drops_channeler() : CreatureScript("npc_drops_channeler") { }

        struct npc_drops_channelerAI : public ScriptedAI
        {
            npc_drops_channelerAI(Creature* creature) : ScriptedAI(creature)
            {
                //SetImmuneToPushPullEffects(true);
                instance = me->GetInstanceScript();
                me->SetReactState(REACT_PASSIVE);
            }

            void Reset() override
            {
                if (Creature* madantul = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_MADANTUL_RADA)))
                    DoCast(madantul, SPELL_RED_BEAM_DROPS);
            }

        private:
            InstanceScript* instance;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_drops_channelerAI>(creature);
        }
};

class npc_memory_of_ice_OLDSM : CreatureScript
{
    public:
        npc_memory_of_ice_OLDSM() : CreatureScript("npc_memory_of_ice_OLDSM") { }

        struct npc_memory_of_ice_OLDSMAI : public ScriptedAI
        {
            npc_memory_of_ice_OLDSMAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetReactState(REACT_PASSIVE);
                instance = me->GetInstanceScript();
                me->SetObjectScale(0.50f);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }

            Position GenerateRandomPositionFromPosition(Position fromPos, float radius)
            {
                Position pos = fromPos;
                me->MovePosition(pos, radius * (float)rand_norm(), (float)rand_norm() * static_cast<float>(2 * M_PI));
                return pos;
            }

            void DoAction(int32 param) override
            {
                if (param == ACTION_MEMORY_MOVE)
                    me->GetMotionMaster()->MovePoint(1, GenerateRandomPositionFromPosition(teleportMidRoom, 10.0f));
            }

            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                damage = 0;
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (id == 1)
                {
                    Position pos;
                    me->GetPosition(&pos);
                    pos.m_positionZ += 8.0f;
                    me->GetMotionMaster()->MoveTakeoff(10, pos, 1.f);
                    events.ScheduleEvent(EVENT_MEMORY_START_CASTING, 2000);
                }
            }

            void UpdateAI(uint32 diff) override
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_MEMORY_START_CASTING)
                {
                    if (Creature* madan = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_MADANTUL_RADA)))
                    {
                        me->SetFacingTo(me->GetAngle(madan->GetPositionX(), madan->GetPositionY()));
                        DoCast(madan, SPELL_GHOSTBUSTERS_BEAM);
                    }
                }
            }
        private:
            InstanceScript* instance;
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_memory_of_ice_OLDSMAI>(creature);
        }
};

class npc_kamikaze_OLDSM : public CreatureScript
{
    public:
        npc_kamikaze_OLDSM() : CreatureScript("npc_kamikaze_OLDSM") { }

        struct npc_kamikaze_OLDSMAI : public ScriptedAI
        {
            npc_kamikaze_OLDSMAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() override
            {
                me->SetReactState(REACT_PASSIVE);
                events.ScheduleEvent(1, 3500);
                me->AddAura(SPELL_EXPLODING_AURA, me);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (id == 10000)
                {
                    me->CastCustomSpell(SPELL_EXPLOSIVE_BARRAGE, SPELLVALUE_BASE_POINT0, 15000, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                    me->DespawnOrUnsummon(1000);
                }
            }

            void UpdateAI(uint32 diff) override
            {
                events.Update(diff);

                if (events.ExecuteEvent() == 1)
                {
                    Position pos;
                    me->GetPosition(&pos);
                    me->GetMotionMaster()->MoveCharge(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ() - 10.0f, 25.0f, 10000);
                }
            }
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_kamikaze_OLDSMAI>(creature);
        }
};

// czemu nie sai? Zeby wszystko bylo w jednym miejscu na przyszlosc;p
class npc_arrow_marker_OLDSM : public CreatureScript
{
    public:
        npc_arrow_marker_OLDSM() : CreatureScript("npc_arrow_marker_OLDSM") { }

        struct npc_arrow_marker_OLDSMAI : public ScriptedAI
        {
            npc_arrow_marker_OLDSMAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() override
            {
                me->SetWalk(true);
                me->SetObjectScale(2.0f);
                me->AddAura(42171, me); // marker aura
                me->GetMotionMaster()->MovePoint(1, markerMovePos);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_arrow_marker_OLDSMAI>(creature);
        }
};

class npc_darkness_caster_OLDSM : public CreatureScript
{
    public:
        npc_darkness_caster_OLDSM() : CreatureScript("npc_darkness_caster_OLDSM") { }

        struct npc_darkness_caster_OLDSMAI : public ScriptedAI
        {
            npc_darkness_caster_OLDSMAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetReactState(REACT_PASSIVE);
                me->setFaction(16);
                SetCombatMovement(false);
            }

            void DamageTaken(Unit* attacker, uint32&damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                damage = 0;
            }

            void Reset() override
            {
                me->CastCustomSpell(SPELL_DARKNESS, SPELLVALUE_BASE_POINT0, 1000, (Unit*)nullptr, TRIGGERED_NONE);
                me->DespawnOrUnsummon(21000);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_darkness_caster_OLDSMAI>(creature);
        }
};

// to jest w sumie fix do spella w dragonblight, bo nie dzialal
class spell_mystical_bolt : public SpellScriptLoader
{
    public:
        spell_mystical_bolt() : SpellScriptLoader("spell_mystical_bolt") { }

        class spell_mystical_bolt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mystical_bolt_SpellScript);

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    if (Aura* aur = target->GetAura(SPELL_MYSTICAL_BOLT))
                    {
                        if (aur->GetStackAmount() >= 5)
                        {
                            target->CastSpell(target, SPELL_LOST_SOUL);
                            target->RemoveAurasDueToSpell(SPELL_MYSTICAL_BOLT);
                        }
                    }
                }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_mystical_bolt_SpellScript::HandleScriptEffect, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_mystical_bolt_SpellScript();
        }
};

class spell_shadow_scythe : public SpellScriptLoader
{
    public:
        spell_shadow_scythe() : SpellScriptLoader("spell_shadow_scythe") { }

        class spell_shadow_scythe_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_shadow_scythe_SpellScript);

            void OnEffectHit()
            {
                if (Player* player = GetHitPlayer())
                    if (player->GetMapId() == 44) // Old SM
                        if (Group* group = player->GetGroup())
                        {
                            std::list<Player*> partyList;
                            for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
                            {
                                Player* member = itr->GetSource();
                                if (!member || member->GetGUID() == player->GetGUID() || !member->IsInWorld() || member->GetDistance2d(player) > 35.0f)
                                    continue;

                                partyList.push_back(member);
                            }

                            if (!partyList.empty())
                            {
                                partyList.sort(Trinity::ObjectDistanceOrderPred(player));
                                if (Player* target = partyList.front())
                                    player->CastCustomSpell(SPELL_SHADOW_SCYTHE, SPELLVALUE_BASE_POINT0, urand(4000, 6000), target, TRIGGERED_FULL_MASK);
                            }
                        }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_shadow_scythe_SpellScript::OnEffectHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_shadow_scythe_SpellScript();
        }
};

class aura_sam_test_aura_OLDSM : public SpellScriptLoader
{
    public:
        aura_sam_test_aura_OLDSM() : SpellScriptLoader("aura_sam_test_aura_OLDSM") { }

        class aura_sam_test_aura_OLDSM_AuraScript : public AuraScript
        {
            PrepareAuraScript(aura_sam_test_aura_OLDSM_AuraScript);

            void OnRemove(AuraEffect const* /*AuraEff*/, AuraEffectHandleModes /*AuraEff*/)
            {
                if (Unit* target = GetTarget())
                {
                    uint32 damage = GetCharges() * 3000;
                    target->CastCustomSpell(SPELL_ARCANE_EXPLOSION, SPELLVALUE_BASE_POINT0, damage, target, TRIGGERED_FULL_MASK);
                }
            }

            void Register() override
            {
                OnEffectRemove += AuraEffectRemoveFn(aura_sam_test_aura_OLDSM_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new aura_sam_test_aura_OLDSM_AuraScript();
        }
};

void AddSC_boss_madantul_rada()
{
    new boss_madantul_rada();
    new npc_drops_channeler();
    new npc_deragoth_hound();
    new npc_memory_of_ice_OLDSM();
    new npc_kamikaze_OLDSM();
    new npc_darkness_caster_OLDSM();
    new npc_arrow_marker_OLDSM();

    new spell_mystical_bolt();
    new aura_sam_test_aura_OLDSM();
    new spell_shadow_scythe();
}
