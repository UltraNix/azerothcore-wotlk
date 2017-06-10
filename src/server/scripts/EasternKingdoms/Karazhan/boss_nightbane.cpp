#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "GameObjectAI.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "karazhan.h"
#include "CreatureTextMgr.h"
#include "SpellScript.h"

enum NightbaneSpells
{
    SPELL_BELLOWING_ROAR    = 36922,
    SPELL_CHARRED_EARTH     = 30129,
    SPELL_CLEAVE            = 30131,
    SPELL_DISTRACTING_ASH   = 30130,
    SPELL_RAIN_OF_BONES     = 37098,
    SPELL_SMOKING_BLAST     = 30128,
    SPELL_SMOKING_BLAST_T   = 37057,
    SPELL_SMOLDERING_BREATH = 30210,
    SPELL_SUMMON_SKELETON   = 30170,
    SPELL_TAIL_SWEEP        = 25653
};

enum Says
{
    EMOTE_SUMMON            = 0,
    YELL_AGGRO,
    YELL_FLY_PHASE,
    YELL_LAND_PHASE,
    EMOTE_BREATH
};

enum NightbanePoints
{
    POINT_INTRO_START       = 0,
    POINT_INTRO_END,
    POINT_INTRO_LANDING,
    POINT_PHASE_TWO_FLY,
    POINT_PHASE_TWO_PRE_FLY,
    POINT_PHASE_TWO_LANDING,
    POINT_PHASE_TWO_END
};

enum NightbanePaths
{
    PATH_INTRO_START        = 10,
    PATH_INTRO_END,
    PATH_INTRO_LANDING,
    PATH_SECOND_LANDING,
    PATH_PHASE_TWO
};

enum NightbaneEvents
{
    EVENT_BELLOWING_ROAR    = 1,
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
    PHASE_INTRO             = 0,
    PHASE_GROUND,
    PHASE_FLY
};

enum NightbaneGroups
{
    GROUP_GROUND            = 1,
    GROUP_FLY
};

enum NightbaneMisc
{
    ACTION_SUMMON           = 1,
    GO_URN                  = 194092,
    GO_DOOR                 = 184280,
    GO_DOOR2                = 184274
};

Position const FlyPosition = { -11160.13f, -1870.683f, 97.73876f, 0.0f };
Position const FlyPositionLeft = { -11094.42f, -1866.992f, 107.8375f, 0.0f };
Position const FlyPositionRight = { -11193.77f, -1921.983f, 107.9845f, 0.0f };
Position const NightbanePath1[] =
{
    { -11003.710f, -1760.1940f, 140.25340f },
    { -11018.860f, -1797.2690f, 172.85250f }
};
Position const NightbanePath2[] =
{
    { -11018.860f, -1797.2690f, 172.85250f },
    { -11105.760f, -1875.9000f, 158.97800f },
    { -11175.100f, -1857.2240f, 101.00590f },
    { -11296.930f, -1764.5310f, 101.00590f },
    { -11258.900f, -1722.3720f, 101.00590f },
    { -11176.760f, -1809.5990f, 101.00590f },
    { -11191.110f, -1889.3960f, 107.89480f },
    { -11152.180f, -1863.3180f, 101.00590f }
};
Position const NightbanePath3[] =
{
    { -11110.670f, -1878.7710f, 107.89690f },
    { -11142.710f, -1891.1930f, 92.250380f }
};
Position const NightbanePath4[] =
{
    { -11162.230f, -1900.3290f, 94.727470f },
    { -11162.230f, -1900.3290f, 91.472650f }
};
Position const NightbanePath5[] =
{
    { -11160.130f, -1870.6830f, 97.738760f },
    { -11117.730f, -1941.2610f, 127.17200f },
    { -11123.780f, -1968.2430f, 125.92200f },
    { -11148.340f, -1972.9800f, 116.69970f },
    { -11161.620f, -1945.7250f, 103.08860f },
    { -11168.010f, -1922.9050f, 97.394150f },
    { -11162.230f, -1900.3290f, 94.727470f }
};

struct boss_nightbaneAI : public BossAI
{
    boss_nightbaneAI(Creature* creature) : BossAI(creature, DATA_NIGHTBANE), _flyCount(0) 
    { 
        me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
    }

    void MoveByPath(uint8 id)
    {
        if (id < PATH_INTRO_START || id > PATH_PHASE_TWO)
            return;

        me->SetWalk(true);

        Movement::PointsArray path;
        switch (id)
        {
            case PATH_INTRO_START:
                for (uint8 i = 0; i < 2; ++i)
                    path.push_back(G3D::Vector3(NightbanePath1[i].GetPositionX(), NightbanePath1[i].GetPositionY(), NightbanePath1[i].GetPositionZ()));
                break;
            case PATH_INTRO_END:
                for (uint8 i = 0; i < 8; ++i)
                    path.push_back(G3D::Vector3(NightbanePath2[i].GetPositionX(), NightbanePath2[i].GetPositionY(), NightbanePath2[i].GetPositionZ()));
                break;
            case PATH_INTRO_LANDING:
                for (uint8 i = 0; i < 2; ++i)
                    path.push_back(G3D::Vector3(NightbanePath3[i].GetPositionX(), NightbanePath3[i].GetPositionY(), NightbanePath3[i].GetPositionZ()));
                break;
            case PATH_SECOND_LANDING:
                for (uint8 i = 0; i < 2; ++i)
                    path.push_back(G3D::Vector3(NightbanePath4[i].GetPositionX(), NightbanePath4[i].GetPositionY(), NightbanePath4[i].GetPositionZ()));
                break;
            case PATH_PHASE_TWO:
                for (uint8 i = 0; i < 7; ++i)
                    path.push_back(G3D::Vector3(NightbanePath5[i].GetPositionX(), NightbanePath5[i].GetPositionY(), NightbanePath5[i].GetPositionZ()));
                break;
        }

        me->GetMotionMaster()->MoveSplinePath(&path);
    }

    void Reset() override
    {
        _Reset();
        me->SetStandState(UNIT_STAND_STATE_DEAD);
        _flyCount = 0;
        me->SetDisableGravity(true);
        if (GameObject* urn = me->FindNearestGameObject(GO_URN, 500.0f))
            urn->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
    }

    void EnterEvadeMode() override
    {
        events.Reset();
        HandleTerraceDoors(true);
        _EnterEvadeMode();
        me->GetMotionMaster()->MoveTargetedHome();
        me->SetDisableGravity(true);
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
            me->SetStandState(UNIT_STAND_STATE_STAND);
            sCreatureTextMgr->SendChat(me, EMOTE_SUMMON, nullptr, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_ZONE);
            events.SetPhase(PHASE_INTRO);
            me->setActive(true);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

            MoveByPath(PATH_INTRO_START);
            HandleTerraceDoors(false);
        }
    }

    void SetupGroundPhase()
    {
        events.SetPhase(PHASE_GROUND);
        events.ScheduleEvent(EVENT_CLEAVE, urand(0, 15000), GROUP_GROUND);
        events.ScheduleEvent(EVENT_TAIL_SWEEP, urand(4, 23000), GROUP_GROUND);
        events.ScheduleEvent(EVENT_BELLOWING_ROAR, 48000, GROUP_GROUND);
        events.ScheduleEvent(EVENT_CHARRED_EARTH, urand(12000, 18000), GROUP_GROUND);
        events.ScheduleEvent(EVENT_SMOLDERING_BREATH, urand(26000, 30000), GROUP_GROUND);
        events.ScheduleEvent(EVENT_DISTRACTING_ASH, 82000, GROUP_GROUND);
    }

    void HandleTerraceDoors(bool open)
    {
        if(GameObject* door = me->FindNearestGameObject(GO_DOOR, 500.f))
            instance->HandleGameObject(door->GetGUID(), open);
        if (GameObject* door = me->FindNearestGameObject(GO_DOOR2, 500.f))
            instance->HandleGameObject(door->GetGUID(), open);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        Talk(YELL_AGGRO);
        SetupGroundPhase();
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
    {
        if (events.IsInPhase(PHASE_FLY))
        {
            if (damage >= me->GetHealth())
                damage = me->GetHealth() - 1;
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
        me->SetWalk(false);

        if (me->movespline->Finalized() && me->movespline->CurrentDestination() == G3D::Vector3(NightbanePath1[1].GetPositionX(), NightbanePath1[1].GetPositionY(), NightbanePath1[1].GetPositionZ()))
            events.ScheduleEvent(EVENT_START_INTRO_PATH, 1);
        if (me->movespline->Finalized() && me->movespline->CurrentDestination() == G3D::Vector3(NightbanePath2[7].GetPositionX(), NightbanePath2[7].GetPositionY(), NightbanePath2[7].GetPositionZ()))
            events.ScheduleEvent(EVENT_END_INTRO, 2000);
        if (me->movespline->Finalized() && me->movespline->CurrentDestination() == G3D::Vector3(NightbanePath3[1].GetPositionX(), NightbanePath3[1].GetPositionY(), NightbanePath3[1].GetPositionZ()))
        {
            me->SetDisableGravity(false);
            me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
            events.ScheduleEvent(EVENT_INTRO_LANDING, 3000);
        }
        if (me->movespline->Finalized() && me->movespline->CurrentDestination() == G3D::Vector3(NightbanePath4[1].GetPositionX(), NightbanePath4[1].GetPositionY(), NightbanePath4[1].GetPositionZ()))
        {
            events.SetPhase(PHASE_GROUND);
            me->SetDisableGravity(false);
            me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
            events.ScheduleEvent(EVENT_LANDED, 3000);
        }
        if (me->movespline->Finalized() && me->movespline->CurrentDestination() == G3D::Vector3(NightbanePath5[6].GetPositionX(), NightbanePath5[6].GetPositionY(), NightbanePath5[6].GetPositionZ()))
            events.ScheduleEvent(EVENT_END_PHASE_TWO, 1);

        if (type == POINT_MOTION_TYPE)
        {
            if (pointId == POINT_PHASE_TWO_FLY)
            {
                events.ScheduleEvent(EVENT_PRE_LAND, 33000, GROUP_FLY);
                events.ScheduleEvent(EVENT_EMOTE_BREATH, 2000, GROUP_FLY);
                events.ScheduleEvent(EVENT_SMOKING_BLAST_T, 21000, GROUP_FLY);
                events.ScheduleEvent(EVENT_SMOKING_BLAST, 17000, GROUP_FLY);
            }
            else if (pointId == POINT_PHASE_TWO_PRE_FLY)
                events.ScheduleEvent(EVENT_PRE_FLY_END, 1);
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
        me->SetReactState(REACT_PASSIVE);
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

        if (!me->IsInCombat() && !events.IsInPhase(PHASE_INTRO) && me->GetDistance(me->GetHomePosition()) > 50.0f)
            EnterEvadeMode();

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_BELLOWING_ROAR:
                    DoCastAOE(SPELL_BELLOWING_ROAR);
                    break;
                case EVENT_CHARRED_EARTH:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        DoCast(target, SPELL_CHARRED_EARTH);
                    events.Repeat(urand(18000, 21000));
                    break;
                case EVENT_CLEAVE:
                    DoCastVictim(SPELL_CLEAVE);
                    events.Repeat(urand(6000, 15000));
                    break;
                case EVENT_DISTRACTING_ASH:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        DoCast(target, SPELL_DISTRACTING_ASH);
                    break;
                case EVENT_EMOTE_BREATH:
                    Talk(EMOTE_BREATH);
                    events.ScheduleEvent(EVENT_RAIN_OF_BONES, 3000, GROUP_FLY);
                    break;
                case EVENT_END_INTRO:
                    MoveByPath(PATH_INTRO_LANDING);
                    break;
                case EVENT_END_PHASE_TWO:
                    MoveByPath(PATH_SECOND_LANDING);
                    break;
                case EVENT_INTRO_LANDING:
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                    me->SetInCombatWithZone();
                    break;
                case EVENT_LAND:
                    Talk(YELL_LAND_PHASE);
                    me->SetDisableGravity(true);
                    MoveByPath(PATH_PHASE_TWO);
                    break;
                case EVENT_LANDED:
                    SetupGroundPhase();
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
                case EVENT_PRE_FLY_END:
                    me->GetMotionMaster()->MovePoint(POINT_PHASE_TWO_FLY, FlyPosition, true);
                    break;
                case EVENT_PRE_LAND:
                    events.CancelEventGroup(GROUP_FLY);
                    events.ScheduleEvent(EVENT_LAND, 2000, GROUP_GROUND);
                    break;
                case EVENT_START_INTRO_PATH:
                    MoveByPath(PATH_INTRO_END);
                    break;
                case EVENT_RAIN_OF_BONES:
                    DoResetThreat();
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                    {
                        me->SetFacingToObject(target);
                        DoCast(target, SPELL_RAIN_OF_BONES);
                    }
                    break;
                case EVENT_SMOLDERING_BREATH:
                    DoCastVictim(SPELL_SMOLDERING_BREATH);
                    events.Repeat(urand(28000, 40000));
                    break;
                case EVENT_SMOKING_BLAST:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        DoCast(target, SPELL_SMOKING_BLAST);
                    events.Repeat(1400);
                    break;
                case EVENT_SMOKING_BLAST_T:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        DoCast(target, SPELL_SMOKING_BLAST_T);
                    events.Repeat(urand(5000, 7000));
                    break;
                case EVENT_TAIL_SWEEP:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        if (!me->HasInArc(float(M_PI), target))
                            DoCast(target, SPELL_TAIL_SWEEP);
                    events.Repeat(urand(20000, 30000));
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

private:
    uint8 _flyCount;
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
            GetCaster()->CastSpell(GetTarget(), SPELL_SUMMON_SKELETON, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_rain_of_bones_AuraScript::OnTrigger, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

class go_blackened_urn : public GameObjectScript
{
    public:
        go_blackened_urn() : GameObjectScript("go_blackened_urn") { }

        bool OnGossipHello(Player* player, GameObject *go)
        {
            if (go->HasFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE))
                return false;

            if (InstanceScript* instance = go->GetInstanceScript())
            {
                if (Creature* nightbane = ObjectAccessor::GetCreature(*player, instance->GetData64(DATA_NIGHTBANE)))
                {
                    if (nightbane->GetDistance(nightbane->GetHomePosition()) < 10.0f)
                    {
                        go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
                        nightbane->AI()->DoAction(ACTION_SUMMON);
                    }
                }
            }
            return false;
        }
};

void AddSC_boss_nightbane()
{
    new CreatureAILoader<boss_nightbaneAI>("boss_nightbane");
    new AuraScriptLoaderEx<spell_rain_of_bones_AuraScript>("spell_rain_of_bones");
    new go_blackened_urn();
}
