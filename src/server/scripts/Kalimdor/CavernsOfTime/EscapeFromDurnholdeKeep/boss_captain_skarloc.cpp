#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "old_hillsbrad.h"

enum SkarlocSays
{
    SAY_ENTER,
    SAY_TAUNT,
    SAY_SLAY,
    SAY_DEATH
};

enum SkarlocSpells
{
    SPELL_HOLY_LIGHT                = 29427,
    SPELL_CLEANSE                   = 29380,
    SPELL_HAMMER_OF_JUSTICE         = 13005,
    SPELL_HOLY_SHIELD               = 31904,
    SPELL_DEVOTION_AURA             = 8258,
    SPELL_CONSECRATION              = 38385
};

enum SkarlocEvents
{
    EVENT_INITIAL_TALK              = 1,
    EVENT_START_FIGHT,

    EVENT_CLEANSE                   = 10,
    EVENT_HAMMER,
    EVENT_HOLY_LIGHT,
    EVENT_HOLY_SHIELD,
    EVENT_CONSECRATION
};

enum SkarlocPhases
{
    PHASE_INTRO                     = 1,
    PHASE_FIGHT
};

static const G3D::Vector3 startPath[4] =
{
    { 2008.38f, 281.57f, 65.70f },
    { 2035.71f, 271.38f, 63.495f },
    { 2049.12f, 252.31f, 62.855f },
    { 2058.77f, 236.04f, 63.92f }
};

struct boss_captain_skarlocAI : public ScriptedAI
{
    boss_captain_skarlocAI(Creature* creature) : ScriptedAI(creature), _summons(me) { }

    void Reset() override
    {
        _events.Reset();
        _summons.DespawnAll();
        _events.SetPhase(PHASE_INTRO);
    }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);
        summon->SetImmuneToAll(true);

        if (auto instance = me->GetInstanceScript())
            if (auto thrall = instance->GetCreature(DATA_THRALL))
                if (thrall->IsAIEnabled)
                    thrall->AI()->JustSummoned(summon);

        if (summon->GetEntry() == NPC_SKARLOC_MOUNT)
            return;

        if (_summons.size() == 1)
            summon->GetMotionMaster()->MovePoint(0, 2060.788f, 237.301f, 63.999f);
        else
            summon->GetMotionMaster()->MovePoint(0, 2056.870f, 234.853f, 63.839f);
    }

    void InitializeAI() override
    {
        ScriptedAI::InitializeAI();

        Movement::PointsArray path;
        path.reserve(Trinity::Containers::Size(startPath));
        path.emplace_back(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
        for (auto const& pos : startPath)
            path.emplace_back(pos);

        me->GetMotionMaster()->MoveSplinePath(&path);
        me->SetImmuneToAll(true);
        me->Mount(SKARLOC_MOUNT_MODEL);
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type != ESCORT_MOTION_TYPE)
            return;

        // Xinef: we can rely here on internal counting
        if (id == 1)
        {
            me->SummonCreature(NPC_DURNHOLDE_MAGE, 2038.549f, 273.303f, 63.420f, 5.30f, TEMPSUMMON_MANUAL_DESPAWN);
            me->SummonCreature(NPC_DURNHOLDE_VETERAN, 2032.810f, 269.416f, 63.561f, 5.30f, TEMPSUMMON_MANUAL_DESPAWN);
        }
        else if (id == 2)
        {
            me->SummonCreature(NPC_SKARLOC_MOUNT, 2049.12f, 252.31f, 62.855f, me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
            me->Dismount();
            me->SetWalk(true);
            _summons.Broadcast([](Creature* summon) { summon->SetWalk(true); });
        }

        if (me->movespline->Finalized())
        {
            _events.ScheduleEvent(EVENT_INITIAL_TALK, 0.5s, 0, PHASE_INTRO);
            _events.ScheduleEvent(EVENT_START_FIGHT, 8s, 0, PHASE_INTRO);
        }
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.SetPhase(PHASE_FIGHT);
        DoCastSelf(SPELL_DEVOTION_AURA, true);
        _events.ScheduleEvent(EVENT_HOLY_LIGHT, 15s, 0, PHASE_FIGHT);
        _events.ScheduleEvent(EVENT_CLEANSE, 6s, 0, PHASE_FIGHT);
        _events.ScheduleEvent(EVENT_HAMMER, 20s, 0, PHASE_FIGHT);
        _events.ScheduleEvent(EVENT_HOLY_SHIELD, 10s, 0, PHASE_FIGHT);
        if (IsHeroic())
            _events.ScheduleEvent(EVENT_CONSECRATION, 1s, 0, PHASE_FIGHT);
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
        {
            instance->SetData(DATA_ESCORT_PROGRESS, ENCOUNTER_PROGRESS_SKARLOC_KILLED);
            instance->SetData(DATA_THRALL_ADD_FLAG, 0);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() && !_events.IsInPhase(PHASE_INTRO))
            return;

        _events.Update(diff);

        if (me->IsCasting())
            return;

        while (auto eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_INITIAL_TALK:
                    Talk(SAY_ENTER);
                    break;
                case EVENT_START_FIGHT:
                    me->SetImmuneToAll(false);
                    DoZoneInCombat();
                    _summons.Broadcast([this](Creature* summon)
                    {
                        if (summon->GetEntry() != NPC_SKARLOC_MOUNT)
                        {
                            summon->SetImmuneToAll(false);
                            DoZoneInCombat(summon);
                        }
                    });
                    break;
                case EVENT_HOLY_LIGHT:
                    DoCastSelf(SPELL_HOLY_LIGHT);
                    _events.Repeat(20s);
                    break;
                case EVENT_CLEANSE:
                    if (!urand(0, 2))
                        Talk(SAY_TAUNT);
                    DoCastSelf(SPELL_CLEANSE);
                    _events.Repeat(10s);
                    break;
                case EVENT_HAMMER:
                    DoCastVictim(SPELL_HAMMER_OF_JUSTICE);
                    _events.Repeat(30s);
                    break;
                case EVENT_HOLY_SHIELD:
                    DoCastSelf(SPELL_CLEANSE);
                    _events.Repeat(30s);
                    break;
                case EVENT_CONSECRATION:
                    DoCastSelf(SPELL_CONSECRATION);
                    _events.Repeat(20s);
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
        SummonList _summons;
};

void AddSC_boss_captain_skarloc()
{
    new CreatureAILoader<boss_captain_skarlocAI>("boss_captain_skarloc");
}
