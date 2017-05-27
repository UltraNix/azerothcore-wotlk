/*
REWRITTEN FROM SCRATCH BY PUSSYWIZARD, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "violet_hold.h"

enum LavanthorSpells
{
    SPELL_CAUTERIZING_FLAMES        = 59466,
    SPELL_FIREBOLT                  = 54235,
    SPELL_FLAME_BREATH              = 54282,
    SPELL_LAVA_BURN                 = 54249

};

enum LavanthorEvents
{
    EVENT_FIREBOLT                  = 1,
    EVENT_FLAME_BREATH,
    EVENT_LAVA_BURN,
    EVENT_CAUTERIZING_FLAMES,
};

class boss_lavanthor : public CreatureScript
{
    public:
        boss_lavanthor() : CreatureScript("boss_lavanthor") { }

        struct boss_lavanthorAI : public BossAI
        {
            boss_lavanthorAI(Creature* creature) : BossAI(creature, BOSS_LAVANTHOR) { }

            void EnterCombat(Unit* /*who*/) override
            {
                _EnterCombat();
                events.ScheduleEvent(EVENT_FIREBOLT, 1000);
                events.ScheduleEvent(EVENT_FLAME_BREATH, 5000);
                events.ScheduleEvent(EVENT_LAVA_BURN, 10000);
                if (IsHeroic())
                    events.ScheduleEvent(EVENT_CAUTERIZING_FLAMES, 3000);
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
                    case EVENT_FIREBOLT:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                            DoCast(target, SPELL_FIREBOLT);
                        events.RepeatEvent(urand(5000, 13000));
                        break;
                    case EVENT_FLAME_BREATH:
                        DoCastVictim(SPELL_FLAME_BREATH);
                        events.RepeatEvent(urand(10000, 15000));
                        break;
                    case EVENT_LAVA_BURN:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f))
                            DoCast(target, SPELL_LAVA_BURN);
                        events.RepeatEvent(urand(15000, 23000));
                        break;
                    case EVENT_CAUTERIZING_FLAMES:
                        DoCastAOE(SPELL_CAUTERIZING_FLAMES);
                        events.RepeatEvent(urand(10000, 16000));
                        break;
                    default:
                        break;
                }
            }

            void JustDied(Unit* /*killer*/) override
            {
                _JustDied();
                instance->SetData(DATA_BOSS_DIED, 0);
            }

            void MoveInLineOfSight(Unit* /*who*/) override { } 

            void EnterEvadeMode() override
            {
                _EnterEvadeMode();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                instance->SetData(DATA_FAILED, 1);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new boss_lavanthorAI(creature);
        }
};

void AddSC_boss_lavanthor()
{
    new boss_lavanthor();
}
