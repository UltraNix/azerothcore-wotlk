#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "culling_of_stratholme.h"
#include "SpellInfo.h"

enum Spells
{
    SPELL_CURSE_OF_EXERTION     = 52772,
    SPELL_TIME_WARP             = 52766,
    SPELL_TIME_STOP             = 58848,
    SPELL_WOUNDING_STRIKE       = 52771,
    SPELL_TIME_STEP_DUMMY       = 52736,
    SPELL_TIME_STEP_CHARGE      = 52737
};

enum Events
{
    EVENT_CURSE_OF_EXERTION     = 1,
    EVENT_TIME_WARP,
    EVENT_TIME_STOP,
    EVENT_WOUNDING_STRIKE,
    EVENT_TIME_STEP,
    EVENT_KILL_TALK
};

enum Yells
{
    SAY_INTRO                   = 0,
    SAY_AGGRO,
    SAY_TIME_WARP,
    SAY_SLAY,
    SAY_DEATH
};

struct boss_epochAI : public BossAI
{
    boss_epochAI(Creature* creature) : BossAI(creature, DATA_EPOCH) { }

    void EnterCombat(Unit* /*who*/) override
    {
        Talk(SAY_AGGRO);
        _EnterCombat();
        _stepTargetIndex = 0;
        _stepTargets.clear();
        events.ScheduleEvent(EVENT_WOUNDING_STRIKE, urand(4000, 6000));
        events.ScheduleEvent(EVENT_CURSE_OF_EXERTION, urand(10000, 17000));
        events.ScheduleEvent(EVENT_TIME_WARP, 25000);
        if (IsHeroic())
            events.ScheduleEvent(EVENT_TIME_STOP, 15000);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CURSE_OF_EXERTION:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    DoCast(target, SPELL_CURSE_OF_EXERTION);
                events.Repeat(9300);
                break;
            case EVENT_TIME_WARP:
                Talk(SAY_TIME_WARP);
                DoCastAOE(SPELL_TIME_WARP);
                DoCastAOE(SPELL_TIME_STEP_DUMMY);
                events.Repeat(25000);
                break;
            case EVENT_TIME_STOP:
                DoCastAOE(SPELL_TIME_STOP);
                events.Repeat(25000);
                break;
            case EVENT_WOUNDING_STRIKE:
                DoCastVictim(SPELL_WOUNDING_STRIKE);
                events.Repeat(urand(12000, 18000));
                break;
            case EVENT_TIME_STEP:
            {
                // In each step, we charge to a random target that was previously hit by SPELL_TIME_STEP_DUMMY
                // Once we run out of targets, we charge back to the tank, then stop
                uint32 nTargets = _stepTargets.size();
                Unit* target = nullptr;
                while (nTargets > _stepTargetIndex)
                {
                    uint32 selected = urand(_stepTargetIndex, nTargets - 1);
                    if (_stepTargetIndex != selected)
                        std::swap(_stepTargets[_stepTargetIndex], _stepTargets[selected]);
                    if ((target = ObjectAccessor::GetUnit(*me, _stepTargets[_stepTargetIndex++])))
                        break;
                }
                if (target)
                    events.Repeat(500);
                else
                    target = me->GetVictim();

                if (target)
                    DoCast(target, SPELL_TIME_STEP_CHARGE, true);
                break;
            }
            default:
                break;
        }
    }

    void SpellHitTarget(Unit* target, SpellInfo const* info) override
    {
        if (info->Id == SPELL_TIME_STEP_DUMMY && me->IsHostileTo(target))
        {
            _stepTargets.push_back(target->GetGUID());
            events.RescheduleEvent(EVENT_TIME_STEP, 500);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_DEATH);
        _JustDied();
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->GetTypeId() == TYPEID_PLAYER)
            Talk(SAY_SLAY);
    }

    private:
        uint32 _stepTargetIndex;
        std::vector<uint64> _stepTargets;
};

void AddSC_boss_epoch()
{
    new CreatureAILoader<boss_epochAI>("boss_epoch");
}
