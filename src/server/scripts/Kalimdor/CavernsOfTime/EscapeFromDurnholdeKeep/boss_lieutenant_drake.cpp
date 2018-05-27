#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "old_hillsbrad.h"
#include "MoveSplineInit.h"
#include "SmartScriptMgr.h"

enum DrakeSays
{
    SAY_ENTER               = 0,
    SAY_AGGRO,
    SAY_SLAY,
    SAY_MORTAL,
    SAY_SHOUT,
    SAY_DEATH,
};

enum DrakeSpells
{
    SPELL_WHIRLWIND         = 31909,
    SPELL_EXPLODING_SHOT    = 33792,
    SPELL_HAMSTRING         = 9080,
    SPELL_MORTAL_STRIKE     = 31911,
    SPELL_FRIGHTENING_SHOUT = 33789,
};

enum DrakeEvents
{
    EVENT_WHIRLWIND         = 1,
    EVENT_FRIGHTENING_SHOUT,
    EVENT_MORTAL_STRIKE,
    EVENT_HAMSTRING,
    EVENT_EXPLODING_SHOT
};

struct boss_lieutenant_drakeAI : public ScriptedAI
{
    boss_lieutenant_drakeAI(Creature* creature) : ScriptedAI(creature)
    {
        _pathPoints.clear();
        auto path = sSmartWaypointMgr->GetPath(me->GetEntry());
        if (!path || path->empty())
            return;

        _pathPoints.reserve(path->size() + 1);
        _pathPoints.emplace_back(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());

        uint32 wpCounter = 1;
        WPPath::const_iterator itr;
        while ((itr = path->find(wpCounter++)) != path->end())
        {
            auto wp = itr->second;
            _pathPoints.emplace_back(wp->x, wp->y, wp->z);
        }
    }

    void InitializeAI() override
    {
        ScriptedAI::InitializeAI();
        JustReachedHome();
    }

    void JustReachedHome() override
    {
        me->SetWalk(true);
        Movement::MoveSplineInit init(me);
        init.MovebyPath(_pathPoints);
        init.SetCyclic();
        init.Launch();
    }

    void Reset() override
    {
        _events.Reset();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        Talk(SAY_AGGRO);
        _events.ScheduleEvent(EVENT_WHIRLWIND, 4s);
        _events.ScheduleEvent(EVENT_FRIGHTENING_SHOUT, 14s);
        _events.ScheduleEvent(EVENT_MORTAL_STRIKE, 9s);
        _events.ScheduleEvent(EVENT_HAMSTRING, 18s);
        _events.ScheduleEvent(EVENT_EXPLODING_SHOT, 1s);
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer())
            Talk(SAY_SLAY);
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_DEATH);
        if (auto instance = me->GetInstanceScript())
            instance->SetData(DATA_ESCORT_PROGRESS, ENCOUNTER_PROGRESS_DRAKE_KILLED);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->IsCasting())
            return;

        while (auto eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_WHIRLWIND:
                    DoCastSelf(SPELL_WHIRLWIND);
                    _events.Repeat(25s);
                    break;
                case EVENT_EXPLODING_SHOT:
                    if (auto target = SelectTarget(SELECT_TARGET_RANDOM, 1, 40.0f))
                        DoCast(target, SPELL_EXPLODING_SHOT);
                    _events.Repeat(25s);
                    break;
                case EVENT_MORTAL_STRIKE:
                    if (roll_chance_i(40))
                        Talk(SAY_MORTAL);
                    DoCastVictim(SPELL_MORTAL_STRIKE);
                    _events.Repeat(10s);
                    break;
                case EVENT_FRIGHTENING_SHOUT:
                    if (roll_chance_i(40))
                        Talk(SAY_SHOUT);
                    DoCastSelf(SPELL_FRIGHTENING_SHOUT);
                    _events.Repeat(25s);
                    break;
                case EVENT_HAMSTRING:
                    DoCastVictim(SPELL_HAMSTRING);
                    _events.Repeat(25s);
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
        EventMap _events;
        Movement::PointsArray _pathPoints;
};

void AddSC_boss_lieutenant_drake()
{
    new CreatureAILoader<boss_lieutenant_drakeAI>("boss_lieutenant_drake");
}
