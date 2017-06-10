/*
REWRITTEN FROM SCRATCH BY PUSSYWIZARD, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "violet_hold.h"

enum Yells
{
    SAY_AGGRO                                   = 0,
    SAY_SLAY                                    = 1,
    SAY_DEATH                                   = 2,
    SAY_SPAWN                                   = 3,
    SAY_CHARGED                                 = 4,
    SAY_REPEAT_SUMMON                           = 5,
    SAY_SUMMON_ENERGY                           = 6
};

enum eSpells
{
    SPELL_ARCANE_BARRAGE_VOLLEY_N                = 54202,
    SPELL_ARCANE_BARRAGE_VOLLEY_H                = 59483,
    SPELL_ARCANE_BUFFET_N                        = 54226,
    SPELL_ARCANE_BUFFET_H                        = 59485,
    SPELL_SUMMON_ETHEREAL_SPHERE_1                = 54102,
    SPELL_SUMMON_ETHEREAL_SPHERE_2                = 54137,
    SPELL_SUMMON_ETHEREAL_SPHERE_3                = 54138,

    SPELL_ARCANE_POWER_N                        = 54160,
    SPELL_ARCANE_POWER_H                        = 59474,
    //SPELL_SUMMON_PLAYERS                        = 54164, // not used
    //SPELL_POWER_BALL_VISUAL                    = 54141,
};

#define SPELL_ARCANE_BARRAGE_VOLLEY                DUNGEON_MODE(SPELL_ARCANE_BARRAGE_VOLLEY_N, SPELL_ARCANE_BARRAGE_VOLLEY_H)
#define SPELL_ARCANE_BUFFET                        DUNGEON_MODE(SPELL_ARCANE_BUFFET_N, SPELL_ARCANE_BUFFET_H)
#define SPELL_ARCANE_POWER                        DUNGEON_MODE(SPELL_ARCANE_POWER_N, SPELL_ARCANE_POWER_H)

enum eEvents
{
    EVENT_SPELL_ARCANE_BARRAGE_VOLLEY = 1,
    EVENT_SPELL_ARCANE_BUFFET,
    EVENT_SUMMON_SPHERES,
    EVENT_CHECK_DISTANCE,
};

struct boss_xevozzAI : public BossAI
{
    boss_xevozzAI(Creature* creature) : BossAI(creature, BOSS_XEVOZZ) { }

    void EnterCombat(Unit* /*who*/) override
    {
        Talk(SAY_AGGRO);
        _EnterCombat();
        events.ScheduleEvent(EVENT_SPELL_ARCANE_BARRAGE_VOLLEY, urand(16000,20000));
        events.ScheduleEvent(EVENT_SUMMON_SPHERES, 10000);
    }

    void MovementInform(uint32 /*type*/, uint32 /*id*/) override
    {
        if (me->movespline->Finalized())
        {
            me->SetWalk(false);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC);
            if (Player* target = SelectTargetFromPlayerList(100.0f))
                AttackStart(target);
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_SPELL_ARCANE_BARRAGE_VOLLEY:
                me->CastSpell((Unit*)NULL, SPELL_ARCANE_BARRAGE_VOLLEY, false);
                events.Repeat(20000);
                break;
            case EVENT_SPELL_ARCANE_BUFFET:
                me->CastSpell(me->GetVictim(), SPELL_ARCANE_BUFFET, false);
                break;
            case EVENT_SUMMON_SPHERES:
            {
                Talk(SAY_SUMMON_ENERGY);
                summons.DespawnAll();
                uint32 entry1 = RAND(SPELL_SUMMON_ETHEREAL_SPHERE_1, SPELL_SUMMON_ETHEREAL_SPHERE_2, SPELL_SUMMON_ETHEREAL_SPHERE_3);
                me->CastSpell((Unit*)NULL, entry1, true);
                if (IsHeroic())
                {
                    uint32 entry2;
                    do { entry2 = RAND(SPELL_SUMMON_ETHEREAL_SPHERE_1, SPELL_SUMMON_ETHEREAL_SPHERE_2, SPELL_SUMMON_ETHEREAL_SPHERE_3); } while (entry1 == entry2);
                    me->CastSpell((Unit*)NULL, entry2, true);
                }
                events.Repeat(45000);
                events.RescheduleEvent(EVENT_SPELL_ARCANE_BUFFET, 5000);
                events.RescheduleEvent(EVENT_CHECK_DISTANCE, 6000);
            }
            break;
            case EVENT_CHECK_DISTANCE:
            {
                bool found = false;
                std::for_each(summons.begin(), summons.end(), [&](uint64 guid) 
                {
                    if (Creature* summon = summons.GetSummon(guid))
                    {
                        if (me->GetDistance(summon) < 3.0f)
                        {
                            summon->CastSpell(me, SPELL_ARCANE_POWER, false);
                            summon->DespawnOrUnsummon();
                            found = true;
                        }
                    }
                });
                if (found)
                {
                    Talk(SAY_CHARGED);
                    events.Repeat(9000);
                    events.RescheduleEvent(EVENT_SUMMON_SPHERES, 10000);
                }
                else
                    events.Repeat(2000);
            }
            break;
            default:
                break;
        }
    }

    void JustSummoned(Creature* pSummoned) override
    {
        if (pSummoned)
        {
            pSummoned->GetMotionMaster()->MoveFollow(me, 0.0f, 0.0f);
            pSummoned->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
            summons.Summon(pSummoned);
            instance->SetData64(DATA_ADD_TRASH_MOB, pSummoned->GetGUID());
        }
    }

    void SummonedCreatureDespawn(Creature *pSummoned) override
    {
        if (pSummoned)
        {
            summons.Despawn(pSummoned);
            instance->SetData64(DATA_DELETE_TRASH_MOB, pSummoned->GetGUID());
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
        instance->SetData(DATA_BOSS_DIED, 0);
    }

    void KilledUnit(Unit* pVictim) override
    {
        if (pVictim && pVictim->GetGUID() == me->GetGUID())
            return;

        Talk(SAY_SLAY);
    }

    void MoveInLineOfSight(Unit* /*who*/) override {}

    void EnterEvadeMode() override
    {
        _EnterEvadeMode();
        events.Reset();
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        instance->SetData(DATA_FAILED, 1);
    }
};

void AddSC_boss_xevozz()
{
    new CreatureAILoader<boss_xevozzAI>("boss_xevozz");
}
