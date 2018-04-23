#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "onyxias_lair.h"
#include "SpellInfo.h"

enum OnyxiaSpells
{
    SPELL_WINGBUFFET                 = 18500,
    SPELL_FLAMEBREATH                = 18435,
    SPELL_CLEAVE                     = 68868,
    SPELL_TAILSWEEP                  = 68867,
    SPELL_FIREBALL                   = 18392,
    SPELL_BELLOWINGROAR              = 18431,

    SPELL_SUMMON_WHELP               = 17646,
    SPELL_SUMMON_LAIR_GUARD          = 68968,
    SPELL_ERUPTION                   = 17731,

    SPELL_OLG_BLASTNOVA              = 68958,
    SPELL_OLG_IGNITEWEAPON           = 68959,
    SPELL_OLG_CLEAVE                 = 15284,

    SPELL_BREATH_N_TO_S              = 17086,
    SPELL_BREATH_S_TO_N              = 18351,
    SPELL_BREATH_E_TO_W              = 18576,
    SPELL_BREATH_W_TO_E              = 18609,
    SPELL_BREATH_SE_TO_NW            = 18564,
    SPELL_BREATH_NW_TO_SE            = 18584,
    SPELL_BREATH_SW_TO_NE            = 18596,
    SPELL_BREATH_NE_TO_SW            = 18617
};

enum OnyxiaEvents
{
    EVENT_SPELL_WINGBUFFET           = 1,
    EVENT_SPELL_FLAMEBREATH,
    EVENT_SPELL_TAILSWEEP,
    EVENT_SPELL_CLEAVE,
    EVENT_START_PHASE_2,
    EVENT_SPELL_FIREBALL_FIRST,
    EVENT_SPELL_FIREBALL_SECOND,
    EVENT_PHASE_2_STEP_CW,
    EVENT_PHASE_2_STEP_ACW,
    EVENT_PHASE_2_STEP_ACROSS,
    EVENT_SPELL_BREATH,
    EVENT_START_PHASE_3,
    EVENT_PHASE_3_ATTACK,
    EVENT_SPELL_BELLOWINGROAR,
    EVENT_WHELP_SPAM,
    EVENT_SUMMON_LAIR_GUARD,
    EVENT_SUMMON_WHELP,
    EVENT_OLG_SPELL_BLASTNOVA,
    EVENT_OLG_SPELL_IGNITEWEAPON,
    EVENT_OLG_CLEAVE,
    EVENT_ERUPTION,

    EVENT_LIFTOFF                    = 31,
    EVENT_FLY_S_TO_N,
    EVENT_LAND,
    EVENT_END_MANY_WHELPS_TIME
};

struct OnyxiaData
{
    uint8 CurrId, DestId;
    uint32 spellId;
    float x, y, z, o;
};

static OnyxiaData OnyxiaMoveData[] =
{
    {0, 0, 0, -64.496f, -214.906f, -84.4f, 0.0f}, // south ground
    {1, 5, SPELL_BREATH_S_TO_N, -64.496f, -214.906f, -60.0f, 0.0f}, // south
    {2, 6, SPELL_BREATH_SW_TO_NE, -59.809f, -190.758f, -60.0f, 7*M_PI/4}, // south-west
    {3, 7, SPELL_BREATH_W_TO_E, -29.450f, -180.600f, -60.0f, M_PI+M_PI/2}, // west
    {4, 8, SPELL_BREATH_NW_TO_SE, 6.895f, -180.246f, -60.0f, M_PI+M_PI/4}, // north-west
    {5, 1, SPELL_BREATH_N_TO_S,  22.876f, -217.152f, -60.0f, M_PI}, // north
    {6, 2, SPELL_BREATH_NE_TO_SW, 10.2191f, -247.912f, -60.0f, 3*M_PI/4}, // north-east
    {7, 3, SPELL_BREATH_E_TO_W, -31.496f, -250.123f, -60.0f, M_PI/2}, // east
    {8, 4, SPELL_BREATH_SE_TO_NW, -63.5156f, -240.096f, -60.0f, M_PI/4}, // south-east
};

enum OnyxiaYells
{
    // Say
    SAY_AGGRO                   = 0,
    SAY_KILL,
    SAY_PHASE_2_TRANS,
    SAY_PHASE_3_TRANS,

    // Emote
    EMOTE_BREATH
};

enum OnyxiaMisc
{
    ACHIEVEMENT_MORE_DOTS    = 6601, // Timed event for achievement 4402, 4005: More Dots! (10,25 player) 5 min kill

    DATA_DEEP_BREATH         = 1,
    DATA_MANY_WHELPS
};

struct boss_onyxiaAI : public BossAI
{
    explicit boss_onyxiaAI(Creature* creature) : BossAI(creature, DATA_ONYXIA), _deepBreath(true), _phase(0), _currentWP(0), _whelpSpam(false), _whelpCount(0), _whelpSpamTimer(0), _manyWhelpsAvailable(false), _manyWhelpsCounter(0) { }

    void SetPhase(uint8 ph)
    {
        events.Reset();
        _phase = ph;
        switch (ph)
        {
            case 1:
                events.ScheduleEvent(EVENT_SPELL_WINGBUFFET, urand(10000, 20000));
                events.ScheduleEvent(EVENT_SPELL_FLAMEBREATH, urand(10000, 20000));
                events.ScheduleEvent(EVENT_SPELL_TAILSWEEP, urand(15000, 20000));
                events.ScheduleEvent(EVENT_SPELL_CLEAVE, urand(2000, 5000));
                break;
            case 2:
                events.ScheduleEvent(EVENT_START_PHASE_2, 0);
                break;
            case 3:
                events.ScheduleEvent(EVENT_START_PHASE_3, 5000);
                break;
            default:
                break;
        }
    }

    void Reset() override
    {
        _Reset();
        _deepBreath = true;
        _currentWP = 0;
        SetPhase(0);
        me->SetReactState(REACT_AGGRESSIVE);
        me->SetCanFly(false);
        me->SetDisableGravity(false);
        me->SetHover(false);
        me->SetSpeedRate(MOVE_RUN, me->GetCreatureTemplate()->speed_run);

        _whelpSpam = false;
        _whelpCount = 0;
        _whelpSpamTimer = 0;
        _manyWhelpsAvailable = false;
        _manyWhelpsCounter;

        instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEVEMENT_MORE_DOTS);
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (me->GetVictim() || me->GetDistance(who) > 30.0f)
            return;

        if (who->GetTypeId() == TYPEID_PLAYER)
            AttackStart(who);
    }

    void DoAction(int32 param) override
    {
        if (param == -1)
            if (_manyWhelpsAvailable)
                ++_manyWhelpsCounter;
    }

    void EnterEvadeMode() override
    {
        _DespawnAtEvade();
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
        SetPhase(1);

        instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEVEMENT_MORE_DOTS); // just in case at reset some players already left the instance
        instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEVEMENT_MORE_DOTS);
    }

    uint32 GetData(uint32 type) const override
    {
        switch (type)
        {
            case DATA_DEEP_BREATH:
                return static_cast<uint32>(_deepBreath);
            case DATA_MANY_WHELPS:
                return static_cast<uint32>(_manyWhelpsCounter >= 50);
        }

        return 0;
    }

    void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask) override
    {
        if (_phase == 1)
        {
            if (me->HealthBelowPctDamaged(65, damage))
                SetPhase(2);
        }
        else if (_phase == 2)
        {
            if (me->HealthBelowPctDamaged(45, damage))
            {
                me->InterruptNonMeleeSpells(false);
                SetPhase(3);
            }
        }
    }

    void JustSummoned(Creature* summon) override
    {
        if (!summon)
            return;

        summons.Summon(summon);

        if (summon->GetEntry() != NPC_ONYXIAN_WHELP && summon->GetEntry() != NPC_ONYXIAN_LAIR_GUARD)
            return;

        if (auto target = summon->SelectNearestTarget(300.0f))
        {
            if (summon->IsAIEnabled)
                summon->AI()->AttackStart(target);
            DoZoneInCombat(summon);
        }
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
            return;

        if (id < 9)
        {
            if (id > 0 && _phase == 2)
            {
                me->SetFacingTo(OnyxiaMoveData[id].o);
                me->SetSpeedRate(MOVE_RUN, 1.6f);
                _currentWP = id;
                events.ScheduleEvent(EVENT_SPELL_FIREBALL_FIRST, 1000);
            }
        }
        else switch (id)
        {
            case 10:
                me->SetFacingTo(OnyxiaMoveData[0].o);
                events.ScheduleEvent(EVENT_LIFTOFF, 0);
                break;
            case 11:
                me->SetFacingTo(OnyxiaMoveData[1].o);
                events.ScheduleEvent(EVENT_FLY_S_TO_N, 0);
                break;
            case 12:
                me->SetFacingTo(OnyxiaMoveData[1].o);
                events.ScheduleEvent(EVENT_LAND, 0);
                break;
            case 13:
                me->SetCanFly(false);
                me->SetDisableGravity(false);
                me->SetHover(false);
                me->SetSpeedRate(MOVE_RUN, me->GetCreatureTemplate()->speed_run);
                events.ScheduleEvent(EVENT_PHASE_3_ATTACK, 0);
                break;
            default:
                break;
        }
    }

    void HandleWhelpSpam(const uint32 diff)
    {
        if (_whelpSpam)
        {
            if (_whelpCount < 40)
            {
                _whelpSpamTimer -= diff;
                if (_whelpSpamTimer <= 0)
                {
                    auto angle = Position::RandomOrientation();
                    auto dist = frand(0.0f, 4.0f);
                    me->CastSpell(-33.18f + cos(angle)*dist, -258.80f + sin(angle)*dist, -89.0f, 17646, true);
                    me->CastSpell(-32.535f + cos(angle)*dist, -170.190f + sin(angle)*dist, -89.0f, 17646, true);
                    _whelpCount += 2;
                    _whelpSpamTimer += 600;
                }
            }
            else
            {
                _whelpSpam = false;
                _whelpCount = 0;
                _whelpSpamTimer = 0;
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);
        HandleWhelpSpam(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SPELL_WINGBUFFET:
                    DoCastSelf(SPELL_WINGBUFFET);
                    events.Repeat(urand(15000, 30000));
                    break;
                case EVENT_SPELL_FLAMEBREATH:
                    DoCastSelf(SPELL_FLAMEBREATH);
                    events.Repeat(urand(10000, 20000));
                    break;
                case EVENT_SPELL_TAILSWEEP:
                    DoCastSelf(SPELL_TAILSWEEP);
                    events.Repeat(urand(15000, 20000));
                    break;
                case EVENT_SPELL_CLEAVE:
                    DoCastVictim(SPELL_CLEAVE);
                    events.Repeat(urand(2000, 5000));
                    break;
                case EVENT_START_PHASE_2:
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    me->StopMoving();
                    DoResetThreat();
                    me->GetMotionMaster()->MovePoint(10, OnyxiaMoveData[0].x, OnyxiaMoveData[0].y, OnyxiaMoveData[0].z);
                    break;
                case EVENT_LIFTOFF:
                    Talk(SAY_PHASE_2_TRANS);
                    me->SendMeleeAttackStop(me->GetVictim());
                    me->GetMotionMaster()->MoveIdle();
                    me->DisableSpline();
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    me->SetHover(true);
                    me->SetOrientation(OnyxiaMoveData[0].o);
                    me->SendMovementFlagUpdate();
                    me->GetMotionMaster()->MoveTakeoff(11, OnyxiaMoveData[1].x + 1.0f, OnyxiaMoveData[1].y, OnyxiaMoveData[1].z, 12.0f);
                    _manyWhelpsAvailable = true;
                    events.RescheduleEvent(EVENT_END_MANY_WHELPS_TIME, 10000);
                    break;
                case EVENT_END_MANY_WHELPS_TIME:
                    _manyWhelpsAvailable = false;
                    break;
                case EVENT_FLY_S_TO_N:
                    me->SetSpeedRate(MOVE_RUN, 2.95f);
                    me->GetMotionMaster()->MovePoint(5, OnyxiaMoveData[5].x, OnyxiaMoveData[5].y, OnyxiaMoveData[5].z);
                    _whelpSpam = true;
                    events.ScheduleEvent(EVENT_WHELP_SPAM, 90000);
                    events.ScheduleEvent(EVENT_SUMMON_LAIR_GUARD, 30000);
                    break;
                case EVENT_SUMMON_LAIR_GUARD:
                    for (uint8 i = 0; i<RAID_MODE(1, 2); ++i)
                        me->CastSpell(-101.654f + frand(-2.0f, 2.0f), -214.491f + frand(-2.0f, 2.0f), -80.70f, SPELL_SUMMON_LAIR_GUARD, true);
                    events.Repeat(30000);
                    break;
                case EVENT_WHELP_SPAM:
                    _whelpSpam = true;
                    events.Repeat(90000);
                    break;
                case EVENT_LAND:
                    Talk(SAY_PHASE_3_TRANS);
                    me->SendMeleeAttackStop(me->GetVictim());
                    me->GetMotionMaster()->MoveLand(13, OnyxiaMoveData[0].x + 1.0f, OnyxiaMoveData[0].y, OnyxiaMoveData[0].z, 12.0f);
                    DoResetThreat();
                    break;
                case EVENT_SPELL_FIREBALL_FIRST:
                    if (auto target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                    {
                        me->SetFacingToObject(target);
                        DoCast(target, SPELL_FIREBALL);
                    }
                    events.ScheduleEvent(EVENT_SPELL_FIREBALL_SECOND, 4000);
                    break;
                case EVENT_SPELL_FIREBALL_SECOND:
                    if (auto target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                    {
                        me->SetFacingToObject(target);
                        DoCast(target, SPELL_FIREBALL);
                    }

                    switch (urand(0, 2))
                    {
                        case 0:
                            events.ScheduleEvent(EVENT_PHASE_2_STEP_CW, 4000);
                            break;
                        case 1:
                            events.ScheduleEvent(EVENT_PHASE_2_STEP_ACW, 4000);
                            break;
                        case 2:
                            events.ScheduleEvent(EVENT_PHASE_2_STEP_ACROSS, 4000);
                            break;
                        default:
                            break;
                    }
                    break;
                case EVENT_PHASE_2_STEP_CW:
                {
                    uint8 newWP = _currentWP + 1;
                    if (newWP > 8)
                        newWP = 1;
                    me->GetMotionMaster()->MovePoint(newWP, OnyxiaMoveData[newWP].x, OnyxiaMoveData[newWP].y, OnyxiaMoveData[newWP].z);
                }
                    break;
                case EVENT_PHASE_2_STEP_ACW:
                {
                    uint8 newWP = _currentWP - 1;
                    if (newWP < 1)
                        newWP = 8;
                    me->GetMotionMaster()->MovePoint(newWP, OnyxiaMoveData[newWP].x, OnyxiaMoveData[newWP].y, OnyxiaMoveData[newWP].z);
                }
                    break;
                case EVENT_PHASE_2_STEP_ACROSS:
                    me->SetFacingTo(OnyxiaMoveData[_currentWP].o);
                    me->MonsterTextEmote("Onyxia takes in a deep breath...", nullptr, true);
                    DoCastSelf(OnyxiaMoveData[_currentWP].spellId);
                    events.ScheduleEvent(EVENT_SPELL_BREATH, 8250);
                    break;
                case EVENT_SPELL_BREATH:
                {
                    auto newWP = OnyxiaMoveData[_currentWP].DestId;
                    me->SetSpeedRate(MOVE_RUN, 2.95f);
                    me->GetMotionMaster()->MovePoint(newWP, OnyxiaMoveData[newWP].x, OnyxiaMoveData[newWP].y, OnyxiaMoveData[newWP].z);
                }
                    break;
                case EVENT_START_PHASE_3:
                    me->SetSpeedRate(MOVE_RUN, 2.95f);
                    me->GetMotionMaster()->MovePoint(12, OnyxiaMoveData[1].x, OnyxiaMoveData[1].y, OnyxiaMoveData[1].z);
                    break;
                case EVENT_PHASE_3_ATTACK:
                    me->SetReactState(REACT_AGGRESSIVE);
                    AttackStart(SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 0, false));
                    DoCastSelf(SPELL_BELLOWINGROAR);

                    events.ScheduleEvent(EVENT_ERUPTION, 0);
                    events.ScheduleEvent(EVENT_SPELL_WINGBUFFET, urand(10000, 20000));
                    events.ScheduleEvent(EVENT_SPELL_FLAMEBREATH, urand(10000, 20000));
                    events.ScheduleEvent(EVENT_SPELL_TAILSWEEP, urand(15000, 20000));
                    events.ScheduleEvent(EVENT_SPELL_CLEAVE, urand(2000, 5000));
                    events.ScheduleEvent(EVENT_SPELL_BELLOWINGROAR, 15000);
                    events.ScheduleEvent(EVENT_SUMMON_WHELP, 10000);
                    break;
                case EVENT_SPELL_BELLOWINGROAR:
                    DoCastSelf(SPELL_BELLOWINGROAR);
                    events.Repeat(22000);
                    events.ScheduleEvent(EVENT_ERUPTION, 0);
                    break;
                case EVENT_ERUPTION:
                    if (_phase == 3)
                        break;
                    if (Creature* trigger = me->SummonCreature(12758, *me, TEMPSUMMON_TIMED_DESPAWN, 1000))
                        trigger->CastSpell(trigger, 17731, false);
                    break;
                case EVENT_SUMMON_WHELP:
                {
                    auto angle = Position::RandomOrientation();
                    auto dist = frand(0.0f, 4.0f);
                    me->CastSpell(-33.18f + cos(angle)*dist, -258.80f + sin(angle)*dist, -89.0f, 17646, true);
                    me->CastSpell(-32.535f + cos(angle)*dist, -170.190f + sin(angle)*dist, -89.0f, 17646, true);
                    events.Repeat(30000);
                }
                break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spell) override
    {
        if (target->GetTypeId() == TYPEID_PLAYER && spell->DurationEntry && spell->DurationEntry->ID == 328 && spell->Effects[EFFECT_1].TargetA.GetTarget() == 1 && (spell->Effects[EFFECT_1].Amplitude == 50 || spell->Effects[EFFECT_1].Amplitude == 150)) // Deep Breath
            _deepBreath = false;
    }

private:
    bool _deepBreath;
    uint8 _phase;
    int8 _currentWP;
    bool _whelpSpam;
    uint8 _whelpCount;
    int32 _whelpSpamTimer;
    bool _manyWhelpsAvailable;
    uint32 _manyWhelpsCounter;
};

struct npc_onyxian_lair_guardAI : public ScriptedAI
{
    explicit npc_onyxian_lair_guardAI(Creature* creature) : ScriptedAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.Reset();
        _events.ScheduleEvent(EVENT_OLG_SPELL_BLASTNOVA, 15000);
        _events.ScheduleEvent(EVENT_OLG_SPELL_IGNITEWEAPON, 10000);
        _events.ScheduleEvent(EVENT_OLG_CLEAVE, 5000);
    }

    void MoveInLineOfSight(Unit *who) override
    {
        if (me->GetVictim() || me->GetDistance(who) > 20.0f)
            return;

        if (who->GetTypeId() == TYPEID_PLAYER)
            AttackStart(who);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (auto eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_OLG_CLEAVE:
                    DoCastVictim(SPELL_CLEAVE);
                    _events.Repeat(15000);
                    break;
                case EVENT_OLG_SPELL_BLASTNOVA:
                    DoCastSelf(SPELL_OLG_BLASTNOVA);
                    _events.Repeat(15000);
                    break;
                case EVENT_OLG_SPELL_IGNITEWEAPON:
                    if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISARMED))
                        _events.Repeat(5000);
                    else
                    {
                        DoCastSelf(SPELL_OLG_IGNITEWEAPON);
                        _events.Repeat(urand(18000, 21000));
                    }
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        if (!me->HasUnitState(UNIT_STATE_CASTING) && me->isAttackReady())
            if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISARMED))
                if (me->HasAura(SPELL_OLG_IGNITEWEAPON))
                    me->RemoveAura(SPELL_OLG_IGNITEWEAPON);

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
};

struct npc_onyxia_whelpAI : public ScriptedAI
{
    explicit npc_onyxia_whelpAI(Creature* creature) : ScriptedAI(creature) {}

    void MoveInLineOfSight(Unit* who) override
    {
        if (me->GetVictim() || me->GetDistance(who) > 20.0f)
            return;

        if (who->GetTypeId() == TYPEID_PLAYER)
            AttackStart(who);
    }
};

struct npc_onyxia_triggerAI : public ScriptedAI
{
    explicit npc_onyxia_triggerAI(Creature* creature) : ScriptedAI(creature) {}

    void MoveInLineOfSight(Unit* who) override {}
    void UpdateAI(uint32 diff) override {}
};

class achievement_onyxia_deep_breath : public AchievementCriteriaScript
{
    public:
        achievement_onyxia_deep_breath() : AchievementCriteriaScript("achievement_onyxia_deep_breath") { }

        bool OnCheck(Player* /*source*/, Unit* target) override
        {
            if (target && target->ToCreature())
                return target->ToCreature()->AI()->GetData(DATA_DEEP_BREATH);

            return false;
        }
};

class achievement_onyxia_many_whelps : public AchievementCriteriaScript
{
    public:
        achievement_onyxia_many_whelps() : AchievementCriteriaScript("achievement_onyxia_many_whelps") { }

        bool OnCheck(Player* /*source*/, Unit* target) override
        {
            if (target && target->ToCreature())
                return target->ToCreature()->AI()->GetData(DATA_MANY_WHELPS);

            return false;
        }
};

void AddSC_boss_onyxia()
{
    new CreatureAILoader<boss_onyxiaAI>("boss_onyxia");
    new CreatureAILoader<npc_onyxian_lair_guardAI>("npc_onyxian_lair_guard");
    new CreatureAILoader<npc_onyxia_whelpAI>("npc_onyxia_whelp");
    new CreatureAILoader<npc_onyxia_triggerAI>("npc_onyxia_trigger");
    new achievement_onyxia_deep_breath();
    new achievement_onyxia_many_whelps();
}
