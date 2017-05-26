/*
REWRITTEN FROM SCRATCH BY PUSSYWIZARD, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "violet_hold.h"

enum ErekemSpells
{
    SPELL_BLOODLUST                             = 54516,
    SPELL_BREAK_BONDS                           = 59463,
    SPELL_CHAIN_HEAL                            = 54481,
    SPELL_EARTH_SHIELD                          = 54479,
    SPELL_EARTH_SHOCK                           = 54511,
    SPELL_LIGHTNING_BOLT                        = 53044,
    SPELL_STORMSTRIKE                           = 51876,
    SPELL_WINDFURY                              = 54493
};

enum ErekemYells
{
    SAY_AGGRO,
    SAY_SLAY,
    SAY_DEATH,
    SAY_SPAWN,
    SAY_ADD_KILLED,
    SAY_BOTH_ADDS_KILLED
};

enum ErekemEvents
{
    EVENT_BLOODLUST                             = 1,
    EVENT_BREAK_BONDS,
    EVENT_CHAIN_HEAL,
    EVENT_EARTH_SHIELD,
    EVENT_EARTH_SHOCK,
    EVENT_LIGHTNING_BOLT
};

enum ErekemMisc
{
    ACTION_GUARD_KILLED                         = 1,
    ACTION_START
};

class boss_erekem : public CreatureScript
{
    public:
        boss_erekem() : CreatureScript("boss_erekem") { }

        struct boss_erekemAI : public BossAI
        {
            boss_erekemAI(Creature* creature) : BossAI(creature, BOSS_EREKEM) { }

            void Reset() override
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC);
                me->SetCanDualWield(false);
                _Reset();
                _deadGuards = 0;
                _guards.clear();
                if (Creature* guard = instance->instance->GetCreature(instance->GetData64(DATA_EREKEM_GUARD_1_GUID)))
                    _guards.push_back(guard);
                if (Creature* guard = instance->instance->GetCreature(instance->GetData64(DATA_EREKEM_GUARD_2_GUID)))
                    _guards.push_back(guard);
            }

            bool CheckGuardAuras(Creature* guard) const
            {
                static uint32 const MechanicImmunityList =
                    (1 << MECHANIC_SNARE)
                    | (1 << MECHANIC_ROOT)
                    | (1 << MECHANIC_FEAR)
                    | (1 << MECHANIC_STUN)
                    | (1 << MECHANIC_SLEEP)
                    | (1 << MECHANIC_CHARM)
                    | (1 << MECHANIC_SAPPED)
                    | (1 << MECHANIC_HORROR)
                    | (1 << MECHANIC_POLYMORPH)
                    | (1 << MECHANIC_DISORIENTED)
                    | (1 << MECHANIC_FREEZE)
                    | (1 << MECHANIC_TURN);
                
                static std::list<AuraType> const AuraImmunityList =
                {
                    SPELL_AURA_MOD_STUN,
                    SPELL_AURA_MOD_DECREASE_SPEED,
                    SPELL_AURA_MOD_ROOT,
                    SPELL_AURA_MOD_CONFUSE,
                    SPELL_AURA_MOD_FEAR
                };

                if (guard->HasAuraWithMechanic(MechanicImmunityList))
                    return true;

                for (AuraType type : AuraImmunityList)
                    if (guard->HasAuraType(type))
                        return true;

                return false;
            }

            void EnterCombat(Unit* /*who*/) override
            {
                _EnterCombat();
                Talk(SAY_AGGRO);
                DoCast(me, SPELL_EARTH_SHIELD);
                events.ScheduleEvent(EVENT_BLOODLUST, 2000);
                if(IsHeroic())
                    events.ScheduleEvent(EVENT_BREAK_BONDS, 0);
                events.ScheduleEvent(EVENT_CHAIN_HEAL, 0);
                events.ScheduleEvent(EVENT_EARTH_SHIELD, 20000);
                events.ScheduleEvent(EVENT_EARTH_SHOCK, urand(2000,8000));
                events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 2000);
            }

            void JustDied(Unit* /*killer*/) override
            {
                instance->SetData(DATA_BOSS_DIED, 0);
                _JustDied();
                Talk(SAY_DEATH);
            }

            void DoAction(int32 actionId) override
            {
                if (!IsHeroic())
                    return;

                if (actionId == ACTION_GUARD_KILLED)
                {
                    switch (++_deadGuards)
                    {
                        case 1:
                            Talk(SAY_ADD_KILLED);
                            break;
                        case 2:
                            Talk(SAY_BOTH_ADDS_KILLED);
                            me->SetCanDualWield(true);
                            DoCast(me, SPELL_WINDFURY, true);
                            break;
                        default:
                            break;
                    }
                }
            }

            void KilledUnit(Unit* victim) override
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_SLAY);
            }

            void EnterEvadeMode() override
            {
                _EnterEvadeMode();
                instance->SetData(DATA_FAILED, 1);
            }

            void MovementInform(uint32 /*type*/, uint32 /*id*/) override
            {
                if (me->movespline->Finalized())
                {
                    if (!_guards.empty())
                        for (auto itr : _guards)
                            if (itr->IsAIEnabled)
                                itr->AI()->DoAction(ACTION_START);

                    me->SetWalk(false);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC);
                    if (Player* target = SelectTargetFromPlayerList(100.0f))
                        AttackStart(target);
                }
            }

            void MoveInLineOfSight(Unit* /*who*/) override {}

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.GetEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BLOODLUST:
                            DoCastAOE(SPELL_BLOODLUST);
                            events.RepeatEvent(urand(35000, 45000));
                            break;
                        case EVENT_BREAK_BONDS:
                        {
                            bool casted = false;
                            if (!_guards.empty())
                            {
                                for (auto itr : _guards)
                                {
                                    if (itr->IsAlive() && CheckGuardAuras(itr))
                                    {
                                        DoCastAOE(SPELL_BREAK_BONDS);
                                        casted = true;
                                        break;
                                    }
                                }
                            }
                            events.RepeatEvent(casted ? 10000 : 500);
                            break;
                        }
                        case EVENT_CHAIN_HEAL:
                            if (Unit* target = DoSelectLowestHpFriendly(40.0f))
                            {
                                DoCast(target, SPELL_CHAIN_HEAL);
                                if (_deadGuards == 2)
                                {
                                    events.RepeatEvent(urand(3000, 6000));
                                    break;
                                }
                            }
                            events.RepeatEvent(urand(8000, 11000));
                            break;
                        case EVENT_EARTH_SHIELD:
                            DoCast(me, SPELL_EARTH_SHIELD);
                            events.RepeatEvent(20000);
                            break;
                        case EVENT_EARTH_SHOCK:
                            DoCastVictim(SPELL_EARTH_SHOCK);
                            events.RepeatEvent(urand(8000, 13000));
                            break;
                        case EVENT_LIGHTNING_BOLT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 35.0f, true))
                                DoCast(target, SPELL_LIGHTNING_BOLT);
                            events.RepeatEvent(2500);
                            break;
                        default:
                            break;
                    }

                    if (me->HasUnitState(UNIT_STATE_CASTING))
                        return;
                }

                if (_deadGuards == 2)
                    DoSpellAttackIfReady(SPELL_STORMSTRIKE);
                else
                    DoMeleeAttackIfReady();
            }

        private:
            uint8 _deadGuards;
            std::vector<Creature*> _guards;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new boss_erekemAI(creature);
        }
};

enum GuardSpells
{
    SPELL_GUSHING_WOUND                         = 39215,
    SPELL_HOWLING_SCREECH                       = 54462,
    SPELL_STRIKE                                = 14516
};

enum GuardEvents
{
    EVENT_GUSHING_WOUND                   = 1,
    EVENT_HOWLING_SCREECH,
    EVENT_STRIKE
};


class npc_erekem_guard : public CreatureScript
{
    public:
        npc_erekem_guard() : CreatureScript("npc_erekem_guard") { }

        struct npc_erekem_guardAI : public ScriptedAI
        {
            npc_erekem_guardAI(Creature* creature) : ScriptedAI(creature), instance(me->GetInstanceScript()) { }

            void Reset() override
            {
                _events.Reset();
            }

            void EnterCombat(Unit* /*who*/) override
            {
                DoZoneInCombat();
                _events.Reset();
                _events.ScheduleEvent(EVENT_GUSHING_WOUND, urand(1000,3000));
                _events.ScheduleEvent(EVENT_HOWLING_SCREECH, urand(8000, 13000));
                _events.ScheduleEvent(EVENT_STRIKE, urand(4000, 8000));
            }

            void JustDied(Unit* /*killer*/) override
            {
            	if(instance)
	                if (Creature* erekem = instance->instance->GetCreature(instance->GetData64(DATA_EREKEM_GUID)))
	                    if (erekem->IsAlive() && erekem->IsAIEnabled)
	                        erekem->AI()->DoAction(ACTION_GUARD_KILLED);
            }

            void MoveInLineOfSight(Unit* /*who*/) override {}

            void DoAction(int32 actionId) override
            {
                if (actionId == ACTION_START)
                {
                    me->SetWalk(false);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC);
                    if (Player* target = SelectTargetFromPlayerList(100.0f))
                        AttackStart(target);
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                _events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = _events.GetEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_GUSHING_WOUND:
                            DoCastVictim(SPELL_GUSHING_WOUND);
                            _events.RepeatEvent(urand(7000, 12000));
                            break;
                        case EVENT_HOWLING_SCREECH:
                            DoCastVictim(SPELL_HOWLING_SCREECH);
                            _events.RepeatEvent(urand(8000, 13000));
                            break;
                        case EVENT_STRIKE:
                            DoCastVictim(SPELL_STRIKE);
                            _events.RepeatEvent(urand(4000, 8000));
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
            InstanceScript* instance;
            EventMap _events;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_erekem_guardAI(creature);
        }
};

void AddSC_boss_erekem()
{
    new boss_erekem();
    new npc_erekem_guard();
}
