#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "molten_core.h"

enum Spells
{
    // Sulfuron Harbringer
    SPELL_DARK_STRIKE           = 19777,
    SPELL_DEMORALIZING_SHOUT    = 19778,
    SPELL_INSPIRE               = 19779,
    SPELL_KNOCKDOWN             = 19780,
    SPELL_FLAMESPEAR            = 19781,

    // Adds
    SPELL_HEAL                  = 19775,
    SPELL_SHADOWWORDPAIN        = 19776,
    SPELL_IMMOLATE              = 20294,
};

enum Events
{
    EVENT_DARK_STRIKE           = 1,
    EVENT_DEMORALIZING_SHOUT,
    EVENT_INSPIRE,
    EVENT_KNOCKDOWN,
    EVENT_FLAMESPEAR,

    EVENT_HEAL,
    EVENT_SHADOW_WORD_PAIN,
    EVENT_IMMOLATE
};

struct boss_sulfuronAI : public BossAI
{
    boss_sulfuronAI(Creature* creature) : BossAI(creature, BOSS_SULFURON_HARBINGER) { }

    void EnterCombat(Unit* victim)
    {
        _EnterCombat();
        events.ScheduleEvent(EVENT_DARK_STRIKE, 10000);
        events.ScheduleEvent(EVENT_DEMORALIZING_SHOUT, 15000);
        events.ScheduleEvent(EVENT_INSPIRE, 3000);
        events.ScheduleEvent(EVENT_KNOCKDOWN, 6000);
        events.ScheduleEvent(EVENT_FLAMESPEAR, 2000);
    }

    void EnterEvadeMode() override
    {
        std::list<Creature*> addList;
        me->GetCreatureListWithEntryInGrid(addList, 11662, 100.0f);
        if (!addList.empty())
        {
            for (auto itr : addList)
            {
                if (!itr->IsAlive())
                    itr->Respawn();
                if (itr->IsAIEnabled)
                    itr->AI()->EnterEvadeMode();
            }
        }
        CreatureAI::EnterEvadeMode();
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_DARK_STRIKE:
                DoCast(me, SPELL_DARK_STRIKE);
                events.Repeat(urand(15000, 18000));
                break;
            case EVENT_DEMORALIZING_SHOUT:
                DoCastVictim(SPELL_DEMORALIZING_SHOUT);
                events.Repeat(urand(15000, 20000));
                break;
            case EVENT_INSPIRE:
            {
                std::list<Creature*> healers = DoFindFriendlyMissingBuff(45.0f, SPELL_INSPIRE);
                healers.remove_if([&](Creature* healer) -> bool
                {
                    return healer->GetEntry() != NPC_FLAMEWAKER_HEALER;
                });
                if (!healers.empty())
                    DoCast(Trinity::Containers::SelectRandomContainerElement(healers), SPELL_INSPIRE);

                DoCast(me, SPELL_INSPIRE);
                events.Repeat(urand(20000, 26000));
                break;
            }
            case EVENT_KNOCKDOWN:
                DoCastVictim(SPELL_KNOCKDOWN);
                events.Repeat(urand(12000, 15000));
                break;
            case EVENT_FLAMESPEAR:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                    DoCast(target, SPELL_FLAMESPEAR);
                events.Repeat(urand(12000, 16000));
                break;
            default:
                break;
        }
    }
};

struct npc_flamewaker_priestAI : public ScriptedAI
{
    npc_flamewaker_priestAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset()
    {
        _events.Reset();
    }

    void JustDied(Unit* /*killer*/)
    {
        _events.Reset();
    }

    void EnterCombat(Unit* victim)
    {
        ScriptedAI::EnterCombat(victim);
        _events.ScheduleEvent(EVENT_HEAL, urand(15000, 30000));
        _events.ScheduleEvent(EVENT_SHADOW_WORD_PAIN, 2000);
        _events.ScheduleEvent(EVENT_IMMOLATE, 8000);
    }

    void UpdateAI(uint32 diff)
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_HEAL:
                    if (Unit* target = DoSelectLowestHpFriendly(60.0f, 1))
                        DoCast(target, SPELL_HEAL);
                    _events.Repeat(urand(15000, 20000));
                    break;
                case EVENT_SHADOW_WORD_PAIN:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true, -SPELL_SHADOWWORDPAIN))
                        DoCast(target, SPELL_SHADOWWORDPAIN);
                    _events.Repeat(urand(18000, 26000));
                    break;
                case EVENT_IMMOLATE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true, -SPELL_IMMOLATE))
                        DoCast(target, SPELL_IMMOLATE);
                    _events.Repeat(urand(15000, 25000));
                    break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
};

void AddSC_boss_sulfuron()
{
    new CreatureAILoader<boss_sulfuronAI>("boss_sulfuron");
    new CreatureAILoader<npc_flamewaker_priestAI>("npc_flamewaker_priest");
}
