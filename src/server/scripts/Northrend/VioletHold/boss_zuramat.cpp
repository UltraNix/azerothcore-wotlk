/*
REWRITTEN FROM SCRATCH BY PUSSYWIZARD, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "violet_hold.h"
#include "PassiveAI.h"

enum Yells
{
    SAY_AGGRO                                   = 0,
    SAY_SLAY                                    = 1,
    SAY_DEATH                                   = 2,
    SAY_SPAWN                                   = 3,
    SAY_SHIELD                                  = 4,
    SAY_WHISPER                                 = 5
};

enum eSpells
{
    SPELL_SHROUD_OF_DARKNESS_N                        = 54524,
    SPELL_SHROUD_OF_DARKNESS_H                        = 59745,
    SPELL_VOID_SHIFT_N                                = 54361,
    SPELL_VOID_SHIFT_H                                = 59743,
    SPELL_SUMMON_VOID_SENTRY                        = 54369,
    SPELL_SUMMON_VOID_SENTRY_BALL                    = 58650,

    //SPELL_ZURAMAT_ADD_2_N                            = 54342,
    //SPELL_ZURAMAT_ADD_2_H                            = 59747,
};

#define NPC_VOID_SENTRY_BALL                        29365
#define SPELL_SHROUD_OF_DARKNESS                    DUNGEON_MODE(SPELL_SHROUD_OF_DARKNESS_N, SPELL_SHROUD_OF_DARKNESS_H)
#define SPELL_VOID_SHIFT                            DUNGEON_MODE(SPELL_VOID_SHIFT_N, SPELL_VOID_SHIFT_H)

enum eEvents
{
    EVENT_SPELL_SHROUD_OF_DARKNESS = 1,
    EVENT_SPELL_VOID_SHIFT,
    EVENT_SPELL_SUMMON_VOID_SENTRY,
};

struct boss_zuramatAI : public BossAI
{
    boss_zuramatAI(Creature* creature) : BossAI(creature, BOSS_ZURAMAT) { }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
        events.ScheduleEvent(EVENT_SPELL_SHROUD_OF_DARKNESS, urand(5000,7000));
        events.ScheduleEvent(EVENT_SPELL_VOID_SHIFT, urand(23000,25000));
        events.ScheduleEvent(EVENT_SPELL_SUMMON_VOID_SENTRY, 10000);
        instance->SetData(DATA_ACHIEV, 1);
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
            case EVENT_SPELL_SHROUD_OF_DARKNESS:
                me->CastSpell(me, SPELL_SHROUD_OF_DARKNESS, false);
                Talk(SAY_SHIELD);
                events.Repeat(20000);
                break;
            case EVENT_SPELL_VOID_SHIFT:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 60.0f, true))
                {
                    me->CastSpell(target, SPELL_VOID_SHIFT, false);
                    me->MonsterWhisper("Gaze... into the void.", target->ToPlayer(), false);
                }
                events.Repeat(urand(18000, 22000));
                break;
            case EVENT_SPELL_SUMMON_VOID_SENTRY:
                me->CastSpell((Unit*)NULL, SPELL_SUMMON_VOID_SENTRY, false);
                events.Repeat(12000);
                break;
            default:
                break;
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
        instance->SetData(DATA_BOSS_DIED, 0);
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim && victim->GetGUID() == me->GetGUID())
            return;

        Talk(SAY_SLAY);
    }

    void JustSummoned(Creature* pSummoned) override
    {
        if (pSummoned)
        {
            summons.Summon(pSummoned);
            pSummoned->SetPhaseMask(16, true);
            instance->SetData64(DATA_ADD_TRASH_MOB, pSummoned->GetGUID());
        }
    }

    void SummonedCreatureDespawn(Creature *pSummoned) override
    {
        if (pSummoned)
        {
            summons.Despawn(pSummoned);
            if (pSummoned->IsAIEnabled)
                pSummoned->AI()->DoAction(-1337);
                
            instance->SetData64(DATA_DELETE_TRASH_MOB, pSummoned->GetGUID());
        }
    }

    void MoveInLineOfSight(Unit* /*who*/) override {} 

    void EnterEvadeMode() override
    {
        ScriptedAI::EnterEvadeMode();
        events.Reset();
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        instance->SetData(DATA_FAILED, 1);
    }
};

struct npc_vh_void_sentryAI : public NullCreatureAI
{
    npc_vh_void_sentryAI(Creature *c) : NullCreatureAI(c)
    {
        pInstance = c->GetInstanceScript();
        SummonedGUID = 0;
        checkTimer = 5000;
        //me->CastSpell(me, SPELL_SUMMON_VOID_SENTRY_BALL, true);
        if (Creature* pSummoned = me->SummonCreature(NPC_VOID_SENTRY_BALL, *me, TEMPSUMMON_TIMED_DESPAWN, 300000))
        {
            pSummoned->SetPhaseMask(1, true);
            SummonedGUID = pSummoned->GetGUID();
            pInstance->SetData64(DATA_ADD_TRASH_MOB, pSummoned->GetGUID());
        }
    }

    InstanceScript* pInstance;
    uint64 SummonedGUID;
    uint16 checkTimer;

    void DoAction(int32 a) override
    {
        if (a == -1337)
            if (Creature* c = pInstance->instance->GetCreature(SummonedGUID))
                c->DespawnOrUnsummon();
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (pInstance)
        {
            pInstance->SetData(DATA_ACHIEV, 0);
            if (Creature* c = pInstance->instance->GetCreature(SummonedGUID))
                c->DespawnOrUnsummon();
        }
        me->DespawnOrUnsummon(5000);
    }

    void SummonedCreatureDespawn(Creature *pSummoned) override
    {
        if (pSummoned)
            pInstance->SetData64(DATA_DELETE_TRASH_MOB, pSummoned->GetGUID());
    }

    void UpdateAI(uint32 diff) override
    {
        if (checkTimer <= diff)
        {
            checkTimer = 5000;
            bool good = false;
            if (me->IsSummon())
                if (Unit* s = me->ToTempSummon()->GetSummoner())
                    if (s->IsAlive())
                        good = true;
            if (!good)
                Unit::Kill(me, me);
        }
        else
            checkTimer -= diff;
    }
};

void AddSC_boss_zuramat()
{
    new CreatureAILoader<boss_zuramatAI>("boss_zuramat");
    new CreatureAILoader<npc_vh_void_sentryAI>("npc_vh_void_sentry");
}
