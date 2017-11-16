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
#include "Unit.h"
#include "MoveSplineInit.h"
#include "MoveSpline.h"
#include "Group.h"
#include "ScriptedGossip.h"
#include "SpellAuras.h"
#include "old_scarlet_monastery.h"

enum madanSpells
{
    // Visuals
    SPELL_LIGHTNING_ARCSTATE    = 50771,
    SPELL_LIGHTNING_SKYDOME     = 62897,
    SPELL_LIGHTNING_TENDRILS    = 61883, // pre burst (100 energy) visual
    SPELL_RANDOM_LIGHTNING      = 52663,
    // During all phases, if 5 stacks of mystical bolt is on current victim aura will transform into lost soul aura
    // and if player has lost soul aura we reset his threat by 100%
    SPELL_MYSTICAL_BOLT         = 51787,
    SPELL_LOST_SOUL             = 51788,
    // Kamikaze, orbs spawning above random player and flying down, exploding on impact
    SPELL_EXPLODING_AURA        = 69017,
    SPELL_EXPLOSIVE_BARRAGE     = 69019,
    // channel at random non-tank player, everyone near that player are 'safe' everyone outside are getting hit
    SPELL_ELECTRICAL_STORM      = 43648,
    // spawns lightning dome and area persistent dmg aura
    SPELL_SAM_TEST_AURA         = 26659,
    SPELL_LEGION_LIGHTNING      = 45664,
    SPELL_LIGHTNING_FURY        = 37681,
    SPELL_LIGHTNING_DISCHARGE   = 39028, // triggered i co kazde 100 energy, zadaje 75% zycia playera || lightning burst 52269
    SPELL_STORM_CALL            = 56897
};

enum madanEvents
{
    EVENT_MYSTICAL_BOLT         = 1,
    EVENT_KAMIKAZE              = 2,
    EVENT_ELECTRICAL_STORM      = 3,
    EVENT_LEGION_LIGHTNING      = 4,
    EVENT_LIGHTNING_FURY        = 5,
    EVENT_LIGHTNING_DISCHARGE   = 6,
    EVENT_LIGHTNING_AREA_DEBUFF = 7,
    EVENT_PHASE_TRANSITION      = 8,
    EVENT_CAST_DISCHARGE        = 9,
    EVENT_CAST_DISCHARGE_2      = 10,

    EVENT_BEGIN_STORM_CALL      = 1
};

enum madanTexts
{
    SAY_MADAN_0                 = 0, // I am Madantul Rada, the strongest warrior among risens. And who might you be?
    SAY_MADAN_1                 = 1, // Come forth Overlords, Let's finish this.
    SAY_MADAN_2                 = 2, // Have you seen my puppy? Oh there it is. It's feeding time Dera'tin'jeragoth
    SAY_MADAN_3                 = 3, // I haven't used this magic in years. Please survive for a little longer, let me enjoy this moment!
    SAY_MADAN_4                 = 4, // Brr.. it's getting cold in here.
    SAY_MADAN_5                 = 5, // The joy of killing! the joy of seeing killing done - this is what drives me! | Killing is indeed a pleasure unmatched in this world. Perhaps it�s a pleasure we could share
    SAY_MADAN_6                 = 6  // I have failed des..
};

enum madanMisc
{
    SOUND_ID_RUN_COWARD         = 9278 // Run away little girl, run away!
};

Position markerSpawnPos = { 373.92f, -82.51f, 30.83f, 0.05f };
Position markerMovePos = { 431.21f, -88.80f, 30.82f, 6.25f };

class boss_madantul_rada : public CreatureScript
{
public:
    boss_madantul_rada() : CreatureScript("boss_madantul_rada") { }

    struct boss_madantul_radaAI : public BossAI
    {
        boss_madantul_radaAI(Creature* creature) : BossAI(creature, DATA_MADANTUL_RADA)
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
            me->setPowerType(POWER_ENERGY);
            me->SetMaxPower(POWER_ENERGY, 100);
        }

        void Reset() override
        {
            _Reset();
            previousStormcallGUID = 0;
            me->SetPower(POWER_ENERGY, 0);
            events.SetPhase(PHASE_NONE);
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetHealth(me->GetMaxHealth());
            DoCastSelf(SPELL_LIGHTNING_ARCSTATE, true);
            me->SetHover(false);
            scheduledChains = false;
            scheduledKamikaze = false;
        }

        void EnterCombat(Unit* target) override
        {
            if (!instance->CheckRequiredBosses(DATA_MADANTUL_RADA))
                return;

            Talk(SAY_MADAN_0);
            _EnterCombat();
            events.SetPhase(PHASE_ONE);
            events.ScheduleEvent(EVENT_MYSTICAL_BOLT, 6000, 0U, PHASE_ONE);
            events.ScheduleEvent(EVENT_ELECTRICAL_STORM, 10000, 0U, PHASE_ONE);
            events.ScheduleEvent(EVENT_LIGHTNING_AREA_DEBUFF, 5000, 0U, PHASE_ONE);
            events.ScheduleEvent(EVENT_LIGHTNING_FURY, 3500, 0U, PHASE_ONE);
        }


        void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
        {
            if (!instance->CheckRequiredBosses(DATA_MADANTUL_RADA))
            {
                damage = 0;
                EnterEvadeMode();
                return;
            }

            if (me->HealthBelowPctDamaged(50, damage) && !scheduledChains)
            {
                scheduledChains = true;
                events.ScheduleEvent(EVENT_LEGION_LIGHTNING, 3000, 0U, PHASE_ONE);
            }

            if (me->HealthBelowPctDamaged(20, damage) && !scheduledKamikaze)
            {
                scheduledKamikaze = true;
                events.ScheduleEvent(EVENT_KAMIKAZE, 2000, 0U, PHASE_ONE);
                events.CancelEvent(EVENT_ELECTRICAL_STORM);
            }
        }

        void JustSummoned(Creature* summon) override
        {
            summons.Summon(summon);
            summon->ToTempSummon()->SetTempSummonType(TEMPSUMMON_CORPSE_DESPAWN);
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
            Talk(SAY_MADAN_6);
            me->SummonCreature(NPC_ARROW_MARKER, markerSpawnPos);
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
                    case EVENT_MYSTICAL_BOLT:
                        if (Unit* target = me->SelectVictim())
                            me->CastCustomSpell(SPELL_MYSTICAL_BOLT, SPELLVALUE_BASE_POINT0, urand(15000, 25000), me->SelectVictim(), TRIGGERED_FULL_MASK);

                        events.ScheduleEvent(EVENT_MYSTICAL_BOLT, 6000, 0U, PHASE_ONE);
                        break;
                    case EVENT_ELECTRICAL_STORM:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, [&](Unit* pred)
                        {
                            return me->GetVictim() != pred && !pred->HasAura(SPELL_SAM_TEST_AURA) &&
                                // guid check is just to make sure we're not casting storm on a person that just dropped area debuff
                                pred->IsPlayer() && previousStormcallGUID != pred->GetGUID();
                        }))
                            me->CastSpell(target, SPELL_ELECTRICAL_STORM, TriggerCastFlags(TRIGGERED_IGNORE_POWER_AND_REAGENT_COST | TRIGGERED_IGNORE_AURA_INTERRUPT_FLAGS));

                        events.ScheduleEvent(EVENT_ELECTRICAL_STORM, urand(15000, 20000), 0U, PHASE_ONE);
                        break;
                    }
                    case EVENT_LIGHTNING_AREA_DEBUFF:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, [&](Unit* pred)
                        {
                            return me->GetVictim() != pred && !pred->HasAura(SPELL_SAM_TEST_AURA) && !pred->HasAura(SPELL_ELECTRICAL_STORM)
                                && pred->GetGUID() != previousStormcallGUID && pred->IsPlayer();
                        }))
                        {
                            target->CastSpell(target, SPELL_SAM_TEST_AURA, true);
                            previousStormcallGUID = target->GetGUID();
                        }
                        else
                        {
                            previousStormcallGUID = 0;
                            events.ScheduleEvent(EVENT_LIGHTNING_AREA_DEBUFF, 5000, 0U, PHASE_ONE);
                            break;
                        }

                        me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + 10);
                        if (me->GetPower(POWER_ENERGY) >= 100)
                        {
                            events.SetPhase(PHASE_TWO);
                            events.ScheduleEvent(EVENT_PHASE_TRANSITION, 3000, 0U);
                            events.CancelEvent(EVENT_LIGHTNING_AREA_DEBUFF);
                            break;
                        }

                        events.ScheduleEvent(EVENT_LIGHTNING_AREA_DEBUFF, 5000, 0U, PHASE_ONE);
                        break;
                    }
                    case EVENT_KAMIKAZE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U, 0.0f, true))
                        {
                            Position pos = target->GetPosition();
                            pos.m_positionZ += 10.0f;
                            me->SummonCreature(NPC_KAMIKAZE, pos);
                        }
                        events.ScheduleEvent(EVENT_KAMIKAZE, 2000);
                        break;
                    }
                    case EVENT_PHASE_TRANSITION:
                    {
                        events.SetPhase(PHASE_TWO);
                        DoStopAttack();
                        me->SetReactState(REACT_PASSIVE);
                        DoCastSelf(SPELL_LIGHTNING_TENDRILS, true);
                        me->SetHover(true);
                        events.ScheduleEvent(EVENT_CAST_DISCHARGE, 3500, 0U, PHASE_TWO);
                        break;
                    }
                    case EVENT_CAST_DISCHARGE:
                    {
                        DoCastAOE(SPELL_LIGHTNING_DISCHARGE, true);
                        events.ScheduleEvent(EVENT_CAST_DISCHARGE_2, 1500, 0U, PHASE_TWO);
                        break;
                    }
                    case EVENT_CAST_DISCHARGE_2:
                    {
                        me->SetPower(POWER_ENERGY, 0);
                        me->SetHover(false);
                        me->RemoveAurasDueToSpell(SPELL_LIGHTNING_TENDRILS);
                        me->SetReactState(REACT_AGGRESSIVE);
                        DoZoneInCombat();
                        if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST))
                            AttackStart(target);
                        events.SetPhase(PHASE_ONE);
                        summons.DespawnEntry(NPC_STORM_CALL_TRIGGER);
                        events.ScheduleEvent(EVENT_LIGHTNING_AREA_DEBUFF, 5000, 0U, PHASE_ONE);
                        break;
                    }
                    case EVENT_LIGHTNING_FURY:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 1U, 5.0f, true))
                            me->CastCustomSpell(SPELL_LIGHTNING_FURY, SPELLVALUE_BASE_POINT0, 45, target, TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_LIGHTNING_FURY, urand(5000, 14000));
                        break;
                    }
                    case EVENT_LEGION_LIGHTNING:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 50.0f, true))
                            me->CastCustomSpell(SPELL_LEGION_LIGHTNING, SPELLVALUE_BASE_POINT0, urand(5000, 7000), target, TriggerCastFlags(TRIGGERED_IGNORE_POWER_AND_REAGENT_COST));

                        events.ScheduleEvent(EVENT_LEGION_LIGHTNING, urand(11000, 15000), 0U, PHASE_ONE);
                        break;
                    }
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        uint64 previousStormcallGUID;
        bool scheduledChains;
        bool scheduledKamikaze;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetOldScarletMonasteryAI<boss_madantul_radaAI>(creature);
    }
};

class npc_kamikaze_OLDSM : public CreatureScript
{
public:
    npc_kamikaze_OLDSM() : CreatureScript("npc_kamikaze_OLDSM") { }

    struct npc_kamikaze_OLDSMAI : public ScriptedAI
    {
        npc_kamikaze_OLDSMAI(Creature* creature) : ScriptedAI(creature)
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(1, 3500); // remove magic numbers
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

            if (events.ExecuteEvent() == 1)// remove magic numbers
            {
                Position pos = me->GetPosition();
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

class npc_storm_call_trigger_OSM : public CreatureScript
{
public:
    npc_storm_call_trigger_OSM() : CreatureScript("npc_storm_call_trigger_OSM") { }

    struct npc_storm_call_trigger_OSM_AI : public ScriptedAI
    {
        npc_storm_call_trigger_OSM_AI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
        }

        void Reset() override
        {
            _events.Reset();
            _events.ScheduleEvent(EVENT_BEGIN_STORM_CALL, 1000);
            DoCastSelf(SPELL_LIGHTNING_SKYDOME, true);
            if (Creature* madan = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_MADANTUL_RADA)))
            {
                madan->AI()->JustSummoned(me);
                //! spawned manually OR when encounter failed
                if (instance->GetBossState(DATA_MADANTUL_RADA) != IN_PROGRESS)
                    me->DespawnOrUnsummon();
            }
            else
                //! spawned outside of instance, despawn instantly
                me->DespawnOrUnsummon();
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            if (_events.ExecuteEvent() == EVENT_BEGIN_STORM_CALL)
            {
                me->CastCustomSpell(SPELL_STORM_CALL, SPELLVALUE_BASE_POINT0, irand(10000, 14000), (Unit*)nullptr, TRIGGERED_FULL_MASK);
                _events.Repeat(6000);
            }
        }

        void EnterCombat(Unit* /*who*/) override { }
        void AttackStart(Unit* /*who*/) override { }
        void MoveInLineOfSight(Unit* /*who*/) override { }
        void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
        {
            damage = 0;
        }

    private:
        EventMap _events;
        InstanceScript* instance;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetOldScarletMonasteryAI<npc_storm_call_trigger_OSM_AI>(creature);
    }
};

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
                me->AddAura(42171, me); // marker aura // remove magic numbers
                me->GetMotionMaster()->MovePoint(1, markerMovePos);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_arrow_marker_OLDSMAI>(creature);
        }
};

class spell_electrical_storm_damage_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_electrical_storm_damage_SpellScript);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (GetHitUnit() && GetHitUnit()->GetMapId() == 44)
            SetHitDamage(GetHitUnit()->GetMaxHealth() * 0.08);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_electrical_storm_damage_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_storm_call_old_scarlet_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_storm_call_old_scarlet_AuraScript);

    bool CheckAreaTarget(Unit* target)
    {
        if (!GetCaster())
            return false;

        return GetCaster()->GetDistance(target) < 5.0f;
    }

    void Register() override
    {
        DoCheckAreaTarget += AuraCheckAreaTargetFn(spell_storm_call_old_scarlet_AuraScript::CheckAreaTarget);
    }
};

class spell_sam_test_aura_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_sam_test_aura_AuraScript);

    void OnApply(AuraEffect const* /*AuraEff*/, AuraEffectHandleModes /*AuraEff*/)
    {
        if (Player* player = GetTarget()->ToPlayer())
        {
            std::ostringstream stream;
            stream << "RUN " << player->GetName().c_str() << "!";
            player->MonsterWhisper(stream.str().c_str(), player, true);
            player->SendPlaySound(SOUND_ID_RUN_COWARD, true);
            player->CastSpell(player, SPELL_RANDOM_LIGHTNING, true);
        }
    }

    void OnRemove(AuraEffect const* /*AuraEff*/, AuraEffectHandleModes /*AuraEff*/)
    {
        GetTarget()->SummonCreature(NPC_STORM_CALL_TRIGGER, GetTarget()->GetPosition());
        GetTarget()->RemoveAurasDueToSpell(SPELL_RANDOM_LIGHTNING);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_sam_test_aura_AuraScript::OnApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_sam_test_aura_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_lightning_discharge_osm_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_lightning_discharge_osm_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (GetCaster()->GetMapId() == 44)
            return;

        //! Riztazz: I've changed this spell radius entry in SpellMgr.cpp because i need it for OSM
        //! this filter target below will make it work as its supposed to outside of OSM
        targets.remove_if([&](WorldObject* object)
        {
            return GetCaster()->GetDistance(object) > 50.0f;
        });
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        //! osm
        if (GetCaster()->GetMapId() == 44)
            if (GetHitUnit())
                SetHitDamage(GetHitUnit()->GetMaxHealth() * 0.5);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_lightning_discharge_osm_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_lightning_discharge_osm_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

void AddSC_boss_madantul_rada()
{
    new boss_madantul_rada();
    new npc_kamikaze_OLDSM();
    new npc_arrow_marker_OLDSM();
    new SpellScriptLoaderEx<spell_electrical_storm_damage_SpellScript>("spell_electrical_storm_damage");
    new AuraScriptLoaderEx<spell_storm_call_old_scarlet_AuraScript>("spell_storm_call_old_scarlet");
    new SpellScriptLoaderEx<spell_lightning_discharge_osm_SpellScript>("spell_lightning_discharge_osm");
    new AuraScriptLoaderEx<spell_sam_test_aura_AuraScript>("spell_sam_test_aura");
    new npc_storm_call_trigger_OSM();
}