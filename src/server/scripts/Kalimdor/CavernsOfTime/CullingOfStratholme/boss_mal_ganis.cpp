#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "culling_of_stratholme.h"
#include "Player.h"

enum Spells
{
    SPELL_CARRION_SWARM                             = 52720,
    SPELL_MIND_BLAST                                = 52722,
    SPELL_SLEEP                                     = 52721,
    SPELL_VAMPIRIC_TOUCH                            = 52723
};

enum Events
{
    EVENT_SPELL_CARRION_SWARM                       = 1,
    EVENT_SPELL_MIND_BLAST,
    EVENT_SPELL_SLEEP,
    EVENT_SPELL_VAMPIRIC_TOUCH,
    EVENT_KILL_TALK
};

enum Yells
{
    SAY_AGGRO                                       = 2,
    SAY_KILL,
    SAY_SLAY,
    SAY_SLEEP,
    SAY_30HEALTH,
    SAY_15HEALTH,
    SAY_ESCAPE_SPEECH_1,
    SAY_ESCAPE_SPEECH_2,
    SAY_OUTRO
};

struct boss_mal_ganisAI : public ScriptedAI
{
    boss_mal_ganisAI(Creature* creature) : ScriptedAI(creature)
    {
        _finished = false;
    }

    void Reset() override
    {
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK_DEST, true);
        events.Reset();
        if (_finished)
        {
            Talk(SAY_OUTRO);
            me->DespawnOrUnsummon(20000);
        }
    }

    void EnterCombat(Unit* /*who*/)
    {
        Talk(SAY_AGGRO);
        events.ScheduleEvent(EVENT_SPELL_CARRION_SWARM, 5000);
        events.ScheduleEvent(EVENT_SPELL_MIND_BLAST, urand(6000, 8000));
        events.ScheduleEvent(EVENT_SPELL_SLEEP, urand(17000, 21000));
        events.ScheduleEvent(EVENT_SPELL_VAMPIRIC_TOUCH, 4000);
    }

    void JustDied(Unit* /*killer*/) override {}

    void KilledUnit(Unit* /*victim*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(RAND(SAY_KILL, SAY_SLAY));
            events.ScheduleEvent(EVENT_KILL_TALK, 6000);
        }
    }

    void DamageTaken(Unit* who, uint32 &damage, DamageEffectType, SpellSchoolMask)
    {
        if (!_finished && damage >= me->GetHealth())
        {
            damage = 0;
            _finished = true;
            me->SetRegeneratingHealth(false);
            me->SetAttackable(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            if (InstanceScript* instance = me->GetInstanceScript())
            {
                if (Creature* cr = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ARTHAS)))
                    cr->AI()->DoAction(ACTION_KILLED_MALGANIS);

                // give credit to players
                DoCastSelf(58630, true);
                instance->SetData(DATA_MALGANIS, DONE);
            }

            // quest completion
            if (who)
                if (Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself())
                    player->RewardPlayerAndGroupAtEvent(31006, player); // Royal Escort quest, Mal'ganis bunny

            EnterEvadeMode();
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (_finished)
            return;

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SPELL_CARRION_SWARM:
                    DoCastVictim(SPELL_CARRION_SWARM);
                    events.Repeat(6000);
                    break;
                case EVENT_SPELL_MIND_BLAST:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true, -int32(sSpellMgr->GetSpellIdForDifficulty(SPELL_SLEEP, me))))
                        DoCast(target, SPELL_MIND_BLAST);
                    else
                        DoCastVictim(SPELL_MIND_BLAST);
                    events.Repeat(urand(8000, 12000));
                    break;
                case EVENT_SPELL_SLEEP:
                    Talk(SAY_SLEEP);
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f))
                        DoCast(target, SPELL_SLEEP);
                    else
                        DoCastVictim(SPELL_SLEEP);
                    events.Repeat(urand(10000, 15000));
                    break;
                case EVENT_SPELL_VAMPIRIC_TOUCH:
                    DoCastSelf(SPELL_VAMPIRIC_TOUCH);
                    events.Repeat(30000);
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
        EventMap events;
        bool _finished;
};


void AddSC_boss_mal_ganis()
{
    new CreatureAILoader<boss_mal_ganisAI>("boss_mal_ganis");
}
