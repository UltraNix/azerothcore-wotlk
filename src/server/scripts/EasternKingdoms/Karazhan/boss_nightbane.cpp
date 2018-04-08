/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "InstanceScript.h"
#include "karazhan.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "ScriptedCreature.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"

enum NightbaneSpells
{
    SPELL_BELLOWING_ROAR        = 36922,
    SPELL_CHARRED_EARTH         = 30129,
    SPELL_CLEAVE                = 30131,
    SPELL_DISTRACTING_ASH       = 30130,
    SPELL_RAIN_OF_BONES         = 37098,
    SPELL_SMOKING_BLAST         = 30128,
    SPELL_SMOKING_BLAST_T       = 37057,
    SPELL_SMOLDERING_BREATH     = 30210,
    SPELL_SUMMON_SKELETON       = 30170,
    SPELL_TAIL_SWEEP            = 25653
};

enum NightbaneYells
{
    EMOTE_SUMMON,
    YELL_AGGRO,
    YELL_FLY_PHASE,
    YELL_LAND_PHASE,
    EMOTE_BREATH
};

enum NightbanePoints
{
    POINT_INTRO_START,
    POINT_INTRO_END,
    POINT_INTRO_LANDING,
    POINT_PHASE_TWO_FLY,
    POINT_PHASE_TWO_PRE_FLY,
    POINT_PHASE_TWO_LANDING,
    POINT_PHASE_TWO_END
};

enum NightbaneSplineChain
{
    SPLINE_CHAIN_INTRO_START    = 1,
    SPLINE_CHAIN_INTRO_END,
    SPLINE_CHAIN_INTRO_LANDING,
    SPLINE_CHAIN_SECOND_LANDING,
    SPLINE_CHAIN_PHASE_TWO
};

enum NightbaneEvents
{
    EVENT_BELLOWING_ROAR        = 1,
    EVENT_CHARRED_EARTH,
    EVENT_CLEAVE,
    EVENT_DISTRACTING_ASH,
    EVENT_EMOTE_BREATH,
    EVENT_END_INTRO,
    EVENT_END_PHASE_TWO,
    EVENT_INTRO_LANDING,
    EVENT_LAND,
    EVENT_LANDED,
    EVENT_PRE_FLY_END,
    EVENT_PRE_LAND,
    EVENT_RAIN_OF_BONES,
    EVENT_SMOLDERING_BREATH,
    EVENT_SMOKING_BLAST,
    EVENT_SMOKING_BLAST_T,
    EVENT_START_INTRO_PATH,
    EVENT_TAIL_SWEEP
};

enum NightbanePhases
{
    PHASE_INTRO,
    PHASE_GROUND,
    PHASE_FLY
};

enum NightbaneGroups
{
    GROUP_GROUND                = 1,
    GROUP_FLY
};

enum NightbaneMisc
{
    ACTION_SUMMON,
    PATH_PHASE_TWO              = 13547500
};

Position const FlyPosition = { -11160.13f, -1870.683f, 97.73876f, 0.0f };
Position const FlyPositionLeft = { -11094.42f, -1866.992f, 107.8375f, 0.0f };
Position const FlyPositionRight = { -11193.77f, -1921.983f, 107.9845f, 0.0f };

struct boss_nightbaneAI : public BossAI
{
    boss_nightbaneAI(Creature* creature) : BossAI(creature, BOSS_NIGHTBANE), _flyCount(0) { }

    void Reset() override
    {
        _Reset();
        _flyCount = 0;
        me->SetDisableGravity(true);
        HandleTerraceDoors(true);
        if (GameObject* urn = instance->GetGameObject(DATA_GO_BLACKENED_URN))
            urn->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
    }

    void EnterEvadeMode() override
    {
        me->SetDisableGravity(true);
        CreatureAI::EnterEvadeMode();
    }

    void JustReachedHome() override
    {
        _DespawnAtEvade(10);
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        HandleTerraceDoors(true);
    }

    void DoAction(int32 action) override
    {
        if (action == ACTION_SUMMON)
        {
            Talk(EMOTE_SUMMON);
            events.SetPhase(PHASE_INTRO);
            me->setActive(true);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->GetMotionMaster()->MoveAlongSplineChain(POINT_INTRO_START, SPLINE_CHAIN_INTRO_START, false);
            HandleTerraceDoors(false);
        }
    }

    void SetupGroundPhase()
    {
        events.SetPhase(PHASE_GROUND);
        events.ScheduleEvent(EVENT_CLEAVE, 0s, 15s, GROUP_GROUND);
        events.ScheduleEvent(EVENT_TAIL_SWEEP, 4s, 23s, GROUP_GROUND);
        events.ScheduleEvent(EVENT_BELLOWING_ROAR, 48s, GROUP_GROUND);
        events.ScheduleEvent(EVENT_CHARRED_EARTH, 12s, 18s, GROUP_GROUND);
        events.ScheduleEvent(EVENT_SMOLDERING_BREATH, 26s, 30s, GROUP_GROUND);
        events.ScheduleEvent(EVENT_DISTRACTING_ASH, 82s, GROUP_GROUND);
    }

    void HandleTerraceDoors(bool open)
    {
        instance->HandleGameObject(instance->GetGuidData(DATA_MASTERS_TERRACE_DOOR_1), open);
        instance->HandleGameObject(instance->GetGuidData(DATA_MASTERS_TERRACE_DOOR_2), open);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        me->SetDisableGravity(false);
        _EnterCombat();
        Talk(YELL_AGGRO);
        SetupGroundPhase();
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*mask*/) override
    {
        if (events.IsInPhase(PHASE_FLY))
        {
            if (damage >= me->GetHealth())
                damage = me->GetHealth() -1;
            return;
        }

        if ((_flyCount == 0 && HealthBelowPct(75)) || (_flyCount == 1 && HealthBelowPct(50)) || (_flyCount == 2 && HealthBelowPct(25)))
        {
            events.SetPhase(PHASE_FLY);
            StartPhaseFly();
        }
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == SPLINE_CHAIN_MOTION_TYPE)
        {
            switch (pointId)
            {
                case POINT_INTRO_START:
                    me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 0, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
                    events.ScheduleEvent(EVENT_START_INTRO_PATH, 1ms);
                    break;
                case POINT_INTRO_END:
                    events.ScheduleEvent(EVENT_END_INTRO, 2s);
                    break;
                case POINT_INTRO_LANDING:
                    me->SetDisableGravity(false);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
                    events.ScheduleEvent(EVENT_INTRO_LANDING, 3s);
                    break;
                case POINT_PHASE_TWO_LANDING:
                    events.SetPhase(PHASE_GROUND);
                    me->SetDisableGravity(false);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
                    events.ScheduleEvent(EVENT_LANDED, 3s);
                    break;
                case POINT_PHASE_TWO_END:
                    events.ScheduleEvent(EVENT_END_PHASE_TWO, 1ms);
                    break;
                default:
                    break;
            }
        }
        else if (type == POINT_MOTION_TYPE)
        {
            if (pointId == POINT_PHASE_TWO_FLY)
            {
                events.ScheduleEvent(EVENT_PRE_LAND, 33s, GROUP_FLY);
                events.ScheduleEvent(EVENT_EMOTE_BREATH, 2s, GROUP_FLY);
                events.ScheduleEvent(EVENT_SMOKING_BLAST_T, 21s, GROUP_FLY);
                events.ScheduleEvent(EVENT_SMOKING_BLAST, 17s, GROUP_FLY);
            }
            else if (pointId == POINT_PHASE_TWO_PRE_FLY)
                events.ScheduleEvent(EVENT_PRE_FLY_END, 1ms);
        }
    }

    void StartPhaseFly()
    {
        ++_flyCount;
        Talk(YELL_FLY_PHASE);
        events.CancelEventGroup(GROUP_GROUND);
        me->InterruptNonMeleeSpells(false);
        me->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
        me->SetDisableGravity(true);
        me->SetPassive();
        me->AttackStop();

        if (me->GetDistance(FlyPositionLeft) < me->GetDistance(FlyPosition))
            me->GetMotionMaster()->MovePoint(POINT_PHASE_TWO_PRE_FLY, FlyPositionLeft, true);
        else if (me->GetDistance(FlyPositionRight) < me->GetDistance(FlyPosition))
            me->GetMotionMaster()->MovePoint(POINT_PHASE_TWO_PRE_FLY, FlyPositionRight, true);
        else
            me->GetMotionMaster()->MovePoint(POINT_PHASE_TWO_FLY, FlyPosition, true);
        }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() && !events.IsInPhase(PHASE_INTRO))
            return;

        events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_BELLOWING_ROAR:
                    DoCastSelf(SPELL_BELLOWING_ROAR);
                    break;
                case EVENT_CHARRED_EARTH:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        DoCast(target, SPELL_CHARRED_EARTH);
                    events.Repeat(18s, 21s);
                    break;
                case EVENT_CLEAVE:
                    DoCastVictim(SPELL_CLEAVE);
                    events.Repeat(6s, 15s);
                    break;
                case EVENT_DISTRACTING_ASH:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        DoCast(target, SPELL_DISTRACTING_ASH);
                    break;
                case EVENT_EMOTE_BREATH:
                    Talk(EMOTE_BREATH);
                    events.ScheduleEvent(EVENT_RAIN_OF_BONES, 3s, GROUP_FLY);
                    break;
                case EVENT_END_INTRO:
                    me->GetMotionMaster()->MoveAlongSplineChain(POINT_INTRO_LANDING, SPLINE_CHAIN_INTRO_LANDING, false);
                    break;
                case EVENT_END_PHASE_TWO:
                    me->GetMotionMaster()->MoveAlongSplineChain(POINT_PHASE_TWO_LANDING, SPLINE_CHAIN_SECOND_LANDING, false);
                    break;
                case EVENT_INTRO_LANDING:
                    me->SetImmuneToPC(false);
                    DoZoneInCombat();
                    break;
                case EVENT_LAND:
                    Talk(YELL_LAND_PHASE);
                    me->SetDisableGravity(true);
                    me->GetMotionMaster()->MoveAlongSplineChain(POINT_PHASE_TWO_END, SPLINE_CHAIN_PHASE_TWO, false);
                    break;
                case EVENT_LANDED:
                    SetupGroundPhase();
                    me->SetAggressive();
                    break;
                case EVENT_PRE_FLY_END:
                    me->GetMotionMaster()->MovePoint(POINT_PHASE_TWO_FLY, FlyPosition, true);
                    break;
                case EVENT_PRE_LAND:
                    events.CancelEventGroup(GROUP_FLY);
                    events.ScheduleEvent(EVENT_LAND, 2s, GROUP_GROUND);
                    break;
                case EVENT_START_INTRO_PATH:
                    me->GetMotionMaster()->MoveAlongSplineChain(POINT_INTRO_END, SPLINE_CHAIN_INTRO_END, false);
                    break;
                case EVENT_RAIN_OF_BONES:
                    me->getThreatManager().resetAllAggro();
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                    {
                        me->SetFacingToObject(target);
                        DoCast(target, SPELL_RAIN_OF_BONES);
                    }
                    break;
                case EVENT_SMOLDERING_BREATH:
                    DoCastVictim(SPELL_SMOLDERING_BREATH);
                    events.Repeat(28s, 40s);
                    break;
                case EVENT_SMOKING_BLAST:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        DoCast(target, SPELL_SMOKING_BLAST);
                    events.Repeat(1400ms);
                    break;
                case EVENT_SMOKING_BLAST_T:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        DoCast(target, SPELL_SMOKING_BLAST_T);
                    events.Repeat(5s, 7s);
                    break;
                case EVENT_TAIL_SWEEP:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, [this](Unit* tar) { return !me->HasInArc(static_cast<float>(M_PI), tar); }))
                        DoCast(target, SPELL_TAIL_SWEEP);
                    events.Repeat(20s, 30s);
                    break;
                default:
                    break;
            }

            if (me->IsCasting())
                return;
        }

        DoMeleeAttackIfReady();
    }

    private:
        uint8 _flyCount;
};

struct npc_restless_skeletonAI : public ScriptedAI
{
    npc_restless_skeletonAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        if (InstanceScript* instance = me->GetInstanceScript())
            if (instance->GetBossState(BOSS_NIGHTBANE) == IN_PROGRESS)
                DoZoneInCombat();
    }
};

// 37098 - Rain of Bones
class spell_rain_of_bones_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_rain_of_bones_AuraScript);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SUMMON_SKELETON });
    }

    void OnTrigger(AuraEffect const* aurEff)
    {
        if (aurEff->GetTickNumber() % 5 == 0)
            GetTarget()->CastSpell(GetTarget(), SPELL_SUMMON_SKELETON, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_rain_of_bones_AuraScript::OnTrigger, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

struct go_blackened_urnAI : GameObjectAI
{
    go_blackened_urnAI(GameObject* go) : GameObjectAI(go), _instance(go->GetInstanceScript()) { }

    bool GossipHello(Player* /*player*/, bool /*reportUse*/) override
    {
        if (go->HasFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE))
            return false;

        if (_instance->GetBossState(BOSS_NIGHTBANE) == DONE || _instance->GetBossState(BOSS_NIGHTBANE) == IN_PROGRESS)
            return false;

        if (Creature* nightbane = _instance->GetCreature(BOSS_NIGHTBANE))
        {
            go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
            nightbane->AI()->DoAction(ACTION_SUMMON);
        }

        return false;
    }

    private:
        InstanceScript* _instance;
};

void AddSC_boss_nightbane()
{
    new CreatureAILoader<boss_nightbaneAI>("boss_nightbane");
    new CreatureAILoader<npc_restless_skeletonAI>("npc_restless_skeleton");
    new AuraScriptLoaderEx<spell_rain_of_bones_AuraScript>("spell_rain_of_bones");
    new GameObjectAILoader<go_blackened_urnAI>("go_blackened_urn");
}
