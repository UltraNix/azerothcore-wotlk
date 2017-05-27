#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "molten_core.h"

enum Spells
{
    // Garr
    SPELL_ANTIMAGIC_PULSE           = 19492,
    SPELL_MAGMA_SHACKLES            = 19496,
    SPELL_ENRAGE                    = 19516,
    SPELL_THRASH                    = 8876,
    SPELL_SEPARATION_ANXIETY_EFFECT = 23492,

    // Adds
    SPELL_ERUPTION                  = 19497,
    SPELL_IMMOLATE                  = 15733,
};

enum Events
{
    // Garr
    EVENT_ANTIMAGIC_PULSE           = 1,
    EVENT_MAGMA_SHACKLES,

    // Adds
    EVENT_CHECK_RANGE               = 1
};

class boss_garr : public CreatureScript
{
    public:
        boss_garr() : CreatureScript("boss_garr") { }

        struct boss_garrAI : public BossAI
        {
            boss_garrAI(Creature* creature) : BossAI(creature, BOSS_GARR) { }

            void EnterCombat(Unit* /*victim*/) override
            {
                _EnterCombat();
                events.ScheduleEvent(EVENT_ANTIMAGIC_PULSE, 25000);
                events.ScheduleEvent(EVENT_MAGMA_SHACKLES, 15000);
            }

            void ExecuteEvent(uint32 eventId) override
            {
                switch (eventId)
                {
                    case EVENT_ANTIMAGIC_PULSE:
                        DoCast(me, SPELL_ANTIMAGIC_PULSE);
                        events.ScheduleEvent(EVENT_ANTIMAGIC_PULSE, urand(10000, 15000));
                        break;
                    case EVENT_MAGMA_SHACKLES:
                        DoCast(me, SPELL_MAGMA_SHACKLES);
                        events.ScheduleEvent(EVENT_MAGMA_SHACKLES, urand(8000, 12000));
                        break;
                    default:
                        break;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new boss_garrAI(creature);
        }
};

class npc_firesworn : public CreatureScript
{
    public:
        npc_firesworn() : CreatureScript("npc_firesworn") { }

        struct npc_fireswornAI : public ScriptedAI
        {
            npc_fireswornAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() 
            {
                DoCast(me, SPELL_THRASH, true);
                DoCast(me, SPELL_IMMOLATE, true);
            }

            void EnterCombat(Unit* victim) override
            {
                CreatureAI::EnterCombat(victim);
                _events.ScheduleEvent(EVENT_CHECK_RANGE, 5000);
            }

            void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override
            {
                if (me->HealthBelowPctDamaged(10, damage))
                {
                    damage = me->GetHealth() - 1;
                    DoCastVictim(SPELL_ERUPTION);
                    me->DespawnOrUnsummon();
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                _events.Update(diff);

                if (_events.GetEvent() == EVENT_CHECK_RANGE)
                {
                    if (Creature* garr = me->FindNearestCreature(NPC_GARR, 200.0f, true))
                        if (!garr->IsInRange(me, 0.0f, 50.0f) && garr->IsAlive())
                            DoCast(me, SPELL_SEPARATION_ANXIETY_EFFECT, true);
                    _events.ScheduleEvent(EVENT_CHECK_RANGE, 5000);
                }

                DoMeleeAttackIfReady();
            }

        private:
            EventMap _events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fireswornAI(creature);
        }
};

void AddSC_boss_garr()
{
    new boss_garr();
    new npc_firesworn();
}
