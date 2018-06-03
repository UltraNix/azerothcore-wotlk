#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "old_hillsbrad.h"

enum EpochSays
{
    SAY_AGGRO                       = 3,
    SAY_SLAY,
    SAY_BREATH,
    SAY_DEATH
};

enum EpochSpells
{
    SPELL_SAND_BREATH               = 31914,
    SPELL_IMPENDING_DEATH           = 31916,
    SPELL_MAGIC_DISRUPTION_AURA     = 33834,
    SPELL_WING_BUFFET               = 31475
};

enum EpochEvents
{
    EVENT_SAND_BREATH               = 1,
    EVENT_IMPENDING_DEATH,
    EVENT_DISRUPTION,
    EVENT_WING_BUFFET
};

struct boss_epoch_hunterAI : public ScriptedAI
{
    boss_epoch_hunterAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _events.Reset();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        Talk(SAY_AGGRO);
        _events.ScheduleEvent(EVENT_SAND_BREATH, 8s);
        _events.ScheduleEvent(EVENT_IMPENDING_DEATH, 2s);
        _events.ScheduleEvent(EVENT_DISRUPTION, 20s);
        _events.ScheduleEvent(EVENT_WING_BUFFET, 14s);
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer())
            Talk(SAY_SLAY);
    }

    void JustDied(Unit* killer) override
    {
        if (killer == me)
            return;

        Talk(SAY_DEATH);
        if (auto instance = me->GetInstanceScript())
        {
            instance->SetData(DATA_ESCORT_PROGRESS, ENCOUNTER_PROGRESS_EPOCH_KILLED);
            if (auto taretha = instance->GetCreature(DATA_TARETHA))
                if (taretha->IsAIEnabled)
                    taretha->AI()->DoAction(me->GetEntry());
        }
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
                case EVENT_SAND_BREATH:
                    if (urand(0, 1))
                        Talk(SAY_BREATH);
                    DoCastVictim(SPELL_SAND_BREATH);
                    _events.Repeat(20s);
                    break;
                case EVENT_IMPENDING_DEATH:
                    DoCastVictim(SPELL_IMPENDING_DEATH);
                    _events.Repeat(30s);
                    break;
                case EVENT_WING_BUFFET:
                    DoCastSelf(SPELL_WING_BUFFET);
                    _events.Repeat(30s);
                    break;
                case EVENT_DISRUPTION:
                    DoCastSelf(SPELL_MAGIC_DISRUPTION_AURA);
                    _events.Repeat(30s);
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
};

void AddSC_boss_epoch_hunter()
{
    new CreatureAILoader<boss_epoch_hunterAI>("boss_epoch_hunter");
}
