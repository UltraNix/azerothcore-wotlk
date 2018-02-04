#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ahnkahet.h"
#include "World.h"

enum JedogaYells
{
    SAY_AGGRO,
    SAY_CHOOSE,
    SAY_SACRIFICE,
    SAY_SLAY,
    SAY_DEATH,
    SAY_PREACHING,

    SAY_CHOSEN                      = 0,
    SAY_SACRIFICED
};

enum JedogaSpells
{
    SPELL_RANDOM_LIGHTNING_VISUAL   = 56327,
    SPELL_HOVER_FALL_1              = 56100,
    SPELL_HOVER_FALL_2              = 56157,
    SPELL_SPHERE_VISUAL             = 56075,
    SPELL_LIGHTNING_BOLT            = 56891,
    SPELL_THUNDERSHOCK              = 56926,
    SPELL_CYCLONE_STRIKE            = 56855,
    SPELL_SACRIFICE_BEAM            = 56150,

    //Jedoga Controller
    SPELL_BEAM_VISUAL_JEDOGA        = 56312,
    SPELL_SACRIFICE_VISUAL          = 56133,

    //Twilight Volunteer
    SPELL_SPHERE_VISUAL_VOLUNTEER   = 56102,
    SPELL_PILLAR_OF_LIGHTNING       = 56868
};

enum JedogaEvents
{
    EVENT_INTRO_SAY                 = 1,
    EVENT_START_FIGHT_1,
    EVENT_START_FIGHT_2,
    EVENT_CYCLONE_STRIKE,
    EVENT_LIGHTNING_BOLT,
    EVENT_THUNDERSHOCK,
    EVENT_PRENERF_PHASE_TWO,
    EVENT_START_PHASE_TWO,
    EVENT_FLY_DELAY,
    EVENT_END_PHASE_TWO,
    EVENT_CHOOSE_VOLUNTEER,
    EVENT_SUMMON_VOLUNTEER,
    EVENT_KILL_TALK,

    EVENT_DEAD
};

enum JedogaPhases
{
    PHASE_INTRO                     = 1,
    PHASE_ONE,
    PHASE_TWO,
    PHASE_THREE
};

enum JedogaPoints
{
    POINT_INITIAL_POSITION          = 0,
    POINT_SACRIFICE,
    POINT_GROUND,
    POINT_PHASE_TWO,
    POINT_PHASE_TWO_FLY
};

enum JedogaMisc
{
    SUMMON_GROUP_INITIATES          = 1,
    SUMMON_GROUP_WORSHIPPERS        = 2,
    DATA_VOLUNTEER_WORK             = 1,
    ACTION_CHOSEN                   = 1,
    ACTION_SACRIFICE                = 2,
    TWILIGHT_INITIATES_SIZE         = 15
};

Position const SacrificePosition = { 376.5385f, -707.3567f, -16.14124f };
Position const JedogaGroundPosition = { 371.6281f, -704.4836f, -16.17967f };
Position const JedogaFlyPosition = { 371.627f, -704.4217f, -6.707521f };
Position const JedogaControllerPositions[3] =
{
    { 402.7893f, -748.5251f, 29.39399f, 2.024582f },
    { 420.1999f, -727.0132f, 28.88036f, 2.042035f },
    { 375.4977f, -707.3635f, -16.0964f, 2.426008f }
};

typedef std::pair<Position, Position> VolunteerPositionPair;
std::vector<VolunteerPositionPair> const VolunteerSpotPositions =
{
    { { 400.7701f, -784.8928f, -31.60143f },{ 365.9514f, -719.1235f, -16.17974f } },
    { { 397.3595f, -788.5157f, -31.59679f },{ 359.7433f, -715.017f,  -16.17974f } },
    { { 399.3177f, -787.2599f, -31.59631f },{ 362.0263f, -719.1036f, -16.17974f } },
    { { 460.4623f, -719.2227f, -31.58718f },{ 389.266f,  -679.3693f, -16.17973f } },
    { { 456.0909f, -724.3412f, -31.58718f },{ 400.5992f, -691.7954f, -16.17973f } },
    { { 452.6613f, -726.9518f, -31.58718f },{ 400.3423f, -701.5115f, -16.17974f } },
    { { 447.8852f, -732.3298f, -31.58718f },{ 389.861f,  -710.6993f, -16.17974f } },
    { { 457.562f,  -721.1855f, -31.58718f },{ 395.4494f, -684.5345f, -16.17973f } },
    { { 451.7243f, -730.2181f, -31.58718f },{ 397.0945f, -708.4188f, -15.99747f } },
    { { 413.9582f, -777.132f,  -31.58716f },{ 388.1394f, -723.124f,  -15.9938f } },
    { { 411.5661f, -781.2356f, -31.58716f },{ 381.7102f, -730.0745f, -15.99554f } },
    { { 407.395f,  -786.793f,  -31.58716f },{ 366.9791f, -737.3303f, -16.17974f } },
    { { 404.9166f, -788.3472f, -31.58716f },{ 358.6124f, -735.9944f, -15.9855f } },
    { { 401.5697f, -791.2033f, -31.58717f },{ 351.9383f, -729.6436f, -16.17974f } },
    { { 410.1105f, -785.4691f, -31.58716f },{ 373.1659f, -736.2893f, -16.17974f } },
    { { 442.5644f, -730.2499f, -31.59826f },{ 390.5955f, -714.6851f, -16.17974f } },
    { { 445.5233f, -725.9542f, -31.60173f },{ 393.9694f, -708.1727f, -16.17974f } },
    { { 448.5531f, -722.5888f, -31.60066f },{ 395.2702f, -702.556f,  -16.17974f } },
    { { 449.8521f, -719.7265f, -31.58849f },{ 394.5757f, -695.1004f, -16.17974f } },
    { { 453.5134f, -717.7018f, -31.59883f },{ 387.6152f, -690.1782f, -16.17974f } },
    { { 457.8564f, -711.7424f, -31.59773f },{ 378.6874f, -687.1343f, -16.17973f } },
    { { 410.0583f, -774.4119f, -31.60115f },{ 383.8151f, -723.4276f, -16.17974f } },
    { { 408.7458f, -777.955f,  -31.59873f },{ 376.9857f, -725.0735f, -16.17974f } },
    { { 405.2404f, -779.6614f, -31.60512f },{ 373.3736f, -722.7498f, -16.17974f } },
    { { 404.0797f, -783.829f,  -31.59497f },{ 367.8631f, -722.5212f, -16.17974f } }
};

struct boss_jedoga_shadowseekerAI : public BossAI
{
    boss_jedoga_shadowseekerAI(Creature* creature) : BossAI(creature, BOSS_JEDOGA) 
    { 
        _preNerf = sWorld->PatchNotes(PATCH_MIN, PATCH_332);
    }

    void Reset() override
    {
        _Reset();
        events.SetPhase(PHASE_INTRO);
        me->SetReactState(REACT_PASSIVE);
        me->SummonCreatureGroup(SUMMON_GROUP_INITIATES);
        SetFlying(true);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        _initiatesKilled = 0;
        _volunteerWork = true;

        if (TempSummon* controller = me->SummonCreature(NPC_JEDOGA_CONTROLLER, JedogaControllerPositions[0], TEMPSUMMON_MANUAL_DESPAWN))
            controller->CastSpell(me, SPELL_BEAM_VISUAL_JEDOGA);
        if (TempSummon* controller = me->SummonCreature(NPC_JEDOGA_CONTROLLER, JedogaControllerPositions[1], TEMPSUMMON_MANUAL_DESPAWN))
            controller->CastSpell(me, SPELL_BEAM_VISUAL_JEDOGA);

        events.ScheduleEvent(EVENT_INTRO_SAY, 2min, 0, PHASE_INTRO);
    }

    void SetFlying(bool apply) const
    {
        me->SetDisableGravity(apply);
        me->SetCanFly(apply);
        me->SetInhabitType(apply ? INHABIT_AIR : INHABIT_GROUND);
        if (apply)
            me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
        else
            me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
        me->SendMovementFlagUpdate(true);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        me->RemoveAurasDueToSpell(SPELL_SPHERE_VISUAL);
        me->RemoveAurasDueToSpell(SPELL_RANDOM_LIGHTNING_VISUAL);
        me->SummonCreatureGroup(SUMMON_GROUP_WORSHIPPERS);

        _EnterCombat();
        Talk(SAY_AGGRO);
        events.SetPhase(PHASE_ONE);

        for (VolunteerPositionPair posPair : VolunteerSpotPositions)
        {
            if (TempSummon* volunteer = me->SummonCreature(NPC_TWILIGHT_VOLUNTEER, posPair.first, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000))
            {
                volunteer->GetMotionMaster()->MovePoint(POINT_INITIAL_POSITION, posPair.second);
                _volunteerGUIDS.push_back(volunteer->GetGUID());
            }
        }
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_SLAY);
            events.ScheduleEvent(EVENT_KILL_TALK, 6s);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
    }

    uint32 GetData(uint32 type) const override
    {
        if (type == DATA_VOLUNTEER_WORK)
            return _volunteerWork ? 1 : 0;

        return 0;
    }

    void SetPhaseTwo()
    {
        events.Reset();
        events.SetPhase(PHASE_TWO);
        events.ScheduleEvent(EVENT_START_PHASE_TWO, 1s);
    }

    void DamageTaken(Unit* /*attacker*/, uint32 &damage, DamageEffectType /*damageType*/, SpellSchoolMask /*schoolMask*/) override
    {
        if (!_preNerf)
            if (me->HealthBelowPctDamaged(55, damage) && events.IsInPhase(PHASE_ONE))
                SetPhaseTwo();
    }

    void DoAction(int32 action) override
    {
        if (action == ACTION_SACRIFICE)
        {
            Talk(SAY_SACRIFICE);
            DoCastAOE(SPELL_SACRIFICE_BEAM);
            events.ScheduleEvent(EVENT_END_PHASE_TWO, 3s);
            events.RescheduleEvent(EVENT_SUMMON_VOLUNTEER, 15s);
        }
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_TWILIGHT_WORSHIPPER)
        {
            summon->SetStandState(UNIT_STAND_STATE_KNEEL);
            summons.Summon(summon);
            return;
        }
        else if (summon->GetEntry() == NPC_JEDOGA_CONTROLLER)
        {
            summons.Summon(summon);
            return;
        }

        BossAI::JustSummoned(summon);
    }

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        if (summon->GetEntry() == NPC_TWILIGHT_INITIATE)
        {
            if (++_initiatesKilled == TWILIGHT_INITIATES_SIZE)
            {
                DoCastSelf(SPELL_HOVER_FALL_1);
                events.ScheduleEvent(EVENT_START_FIGHT_1, 1s);
            }
        }
        else if (summon->GetEntry() == NPC_TWILIGHT_VOLUNTEER)
        {
            _volunteerWork = false;

            if (events.IsInPhase(PHASE_TWO))
            {
                events.SetPhase(PHASE_THREE);
                events.RescheduleEvent(EVENT_END_PHASE_TWO, 1s);
            }

            events.RescheduleEvent(EVENT_SUMMON_VOLUNTEER, 10s);
        }

        BossAI::SummonedCreatureDies(summon, killer);
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
            return;

        switch (pointId)
        {
            case POINT_GROUND:
                SetFlying(false);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetReactState(REACT_AGGRESSIVE);
                DoZoneInCombat();
                events.ScheduleEvent(EVENT_CYCLONE_STRIKE, 3s);
                events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 7s);
                events.ScheduleEvent(EVENT_THUNDERSHOCK, 12s);
                if (_preNerf)
                    events.ScheduleEvent(EVENT_PRENERF_PHASE_TWO, 20s, 25s);
                break;
            case POINT_PHASE_TWO:
                events.ScheduleEvent(EVENT_FLY_DELAY, 2s);
                break;
            case POINT_PHASE_TWO_FLY:
                events.ScheduleEvent(EVENT_CHOOSE_VOLUNTEER, 2s);
                break;
            default:
                break;
        }
    }

    void EnterEvadeMode() override
    {
        summons.DespawnAll();
        _EnterEvadeMode();
        _DespawnAtEvade(15);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() && !events.IsInPhase(PHASE_INTRO))
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_INTRO_SAY:
                    if (instance->GetBossState(BOSS_TALDARAM) == DONE)
                        Talk(SAY_PREACHING);
                    events.Repeat(2min);
                    break;
                case EVENT_START_FIGHT_1:
                    me->RemoveAurasDueToSpell(SPELL_BEAM_VISUAL_JEDOGA);
                    events.ScheduleEvent(EVENT_START_FIGHT_2, 1s);
                    break;
                case EVENT_START_FIGHT_2:
                    summons.DespawnEntry(NPC_JEDOGA_CONTROLLER);
                    me->GetMotionMaster()->MovePoint(POINT_GROUND, JedogaGroundPosition, me->GetSpeed(MOVE_RUN));
                    break;
                case EVENT_PRENERF_PHASE_TWO:
                    SetPhaseTwo();
                    break;
                case EVENT_START_PHASE_TWO:
                    me->SetReactState(REACT_PASSIVE);
                    me->AttackStop();
                    me->InterruptNonMeleeSpells(true);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->GetMotionMaster()->MovePoint(POINT_PHASE_TWO, JedogaGroundPosition);
                    break;
                case EVENT_FLY_DELAY:
                    SetFlying(true);
                    me->GetMotionMaster()->MovePoint(POINT_PHASE_TWO_FLY, JedogaFlyPosition, me->GetSpeed(MOVE_RUN));
                    break;
                case EVENT_CHOOSE_VOLUNTEER:
                    if (TempSummon* controller = me->SummonCreature(NPC_JEDOGA_CONTROLLER, JedogaControllerPositions[2], TEMPSUMMON_MANUAL_DESPAWN))
                    {
                        me->SetReactState(REACT_PASSIVE);
                        me->SetFacingToObject(controller);
                        controller->CastSpell(controller, SPELL_SACRIFICE_VISUAL);
                    }

                    Talk(SAY_CHOOSE);

                    if (_volunteerGUIDS.empty())
                    {
                        // In case something went wrong
                        events.RescheduleEvent(EVENT_END_PHASE_TWO, 3s);
                        break;
                    }

                    _selectedVolunteerGUID = Trinity::Containers::SelectRandomContainerElement(_volunteerGUIDS);
                    if (Creature* volunteer = ObjectAccessor::GetCreature(*me, _selectedVolunteerGUID))
                        if (volunteer->IsAIEnabled)
                            volunteer->AI()->DoAction(ACTION_CHOSEN);
                    break;
                case EVENT_SUMMON_VOLUNTEER:
                {
                    uint32 pos = std::distance(_volunteerGUIDS.begin(), std::find(_volunteerGUIDS.begin(), _volunteerGUIDS.end(), _selectedVolunteerGUID));
                    if (pos < VolunteerSpotPositions.size())
                    {
                        VolunteerPositionPair posPair = VolunteerSpotPositions.at(pos);
                        if (TempSummon* volunteer = me->SummonCreature(NPC_TWILIGHT_VOLUNTEER, posPair.first, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000))
                        {
                            volunteer->GetMotionMaster()->MovePoint(POINT_INITIAL_POSITION, posPair.second);
                            _volunteerGUIDS[pos] = volunteer->GetGUID();
                        }
                    }
                    break;
                }
                case EVENT_END_PHASE_TWO:
                    summons.DespawnEntry(NPC_JEDOGA_CONTROLLER);
                    DoCastSelf(SPELL_HOVER_FALL_2);
                    me->GetMotionMaster()->MovePoint(POINT_GROUND, JedogaGroundPosition, me->GetSpeed(MOVE_RUN));
                    break;
                case EVENT_CYCLONE_STRIKE:
                    DoCastSelf(SPELL_CYCLONE_STRIKE);
                    events.Repeat(15s, 30s);
                    break;
                case EVENT_LIGHTNING_BOLT:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        DoCast(target, SPELL_LIGHTNING_BOLT);
                    events.Repeat(15s, 30s);
                    break;
                case EVENT_THUNDERSHOCK:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        DoCast(target, SPELL_THUNDERSHOCK);
                    events.Repeat(15s, 30s);
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
        bool _preNerf;
        uint8 _initiatesKilled;
        bool _volunteerWork;
        std::vector<uint64> _volunteerGUIDS;
        uint64 _selectedVolunteerGUID;
};

struct npc_twilight_volunteerAI : public ScriptedAI
{
    npc_twilight_volunteerAI(Creature* creature) : ScriptedAI(creature), _instance(creature->GetInstanceScript())
    {
        me->SetReactState(REACT_PASSIVE);
    }

    void DoAction(int32 action) override
    {
        if (action == ACTION_CHOSEN)
        {
            DoCastSelf(SPELL_PILLAR_OF_LIGHTNING);
            me->RemoveAurasDueToSpell(SPELL_SPHERE_VISUAL_VOLUNTEER);
            Talk(SAY_CHOSEN);
            me->SetStandState(UNIT_STAND_STATE_STAND);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetWalk(true);
            me->GetMotionMaster()->MovePoint(POINT_SACRIFICE, SacrificePosition);
        }
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        switch (pointId)
        {
            case POINT_INITIAL_POSITION:
                if (Creature* jedoga = _instance->GetCreature(BOSS_JEDOGA))
                    me->SetFacingToObject(jedoga);

                DoCastSelf(SPELL_SPHERE_VISUAL_VOLUNTEER);
                me->SetStandState(UNIT_STAND_STATE_KNEEL);
                break;
            case POINT_SACRIFICE:
                if (Creature* jedoga = _instance->GetCreature(BOSS_JEDOGA))
                {
                    me->SetStandState(UNIT_STAND_STATE_KNEEL);
                    if (jedoga->IsAIEnabled)
                        jedoga->AI()->DoAction(ACTION_SACRIFICE);
                    Talk(SAY_SACRIFICED);

                    _events.ScheduleEvent(EVENT_DEAD, 3s);
                }
                break;
            default:
                break;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        if (_events.ExecuteEvent() == EVENT_DEAD)
        {
            me->SetStandState(UNIT_STAND_STATE_DEAD);
            me->DespawnOrUnsummon(Seconds(5));
        }
    }

    private:
        InstanceScript* _instance;
        EventMap _events;
};

// 56328 - Random Lightning Visual Effect
class spell_random_lightning_visual_effect_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_random_lightning_visual_effect_SpellScript);

    void ModDestHeight(SpellDestination& dest)
    {
        Position const offset = { frand(-7.5f, 7.5f), frand(-7.5f, 7.5f), -19.0f, 0.0f };
        dest.RelocateOffset(offset);
    }

    void Register() override
    {
        OnDestinationTargetSelect += SpellDestinationTargetSelectFn(spell_random_lightning_visual_effect_SpellScript::ModDestHeight, EFFECT_0, TARGET_DEST_CASTER_RANDOM);
    }
};

class achievement_volunteer_work : public AchievementCriteriaScript
{
    public:
        achievement_volunteer_work() : AchievementCriteriaScript("achievement_volunteer_work") { }

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            if (!target)
                return false;

            if (Creature* jedoga = target->ToCreature())
                if (jedoga->IsAIEnabled)
                    if (jedoga->AI()->GetData(DATA_VOLUNTEER_WORK) == 1)
                        return true;

            return false;
        }
};

void AddSC_boss_jedoga_shadowseeker()
{
    new CreatureAILoader<boss_jedoga_shadowseekerAI>("boss_jedoga_shadowseeker");
    new CreatureAILoader<npc_twilight_volunteerAI>("npc_twilight_volunteer");
    new SpellScriptLoaderEx<spell_random_lightning_visual_effect_SpellScript>("spell_random_lightning_visual_effect");
    new achievement_volunteer_work();
}
