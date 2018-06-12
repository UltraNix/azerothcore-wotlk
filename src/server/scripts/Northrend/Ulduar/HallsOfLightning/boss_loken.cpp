/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "halls_of_lightning.h"
#include "Player.h"

enum LokenSpells
{
    SPELL_ARC_LIGHTNING                = 52921,
    SPELL_LIGHTNING_NOVA_N             = 52960,
    SPELL_LIGHTNING_NOVA_H             = 59835,
    SPELL_LIGHTNING_NOVA_VISUAL        = 56502,
    SPELL_LIGHTNING_NOVA_THUNDERS      = 52663,

    SPELL_PULSING_SHOCKWAVE_N          = 52961,
    SPELL_PULSING_SHOCKWAVE_H          = 59836,
    SPELL_PULSING_SHOCKWAVE_AURA       = 59414,

    // Achievement
    ACHIEVEMENT_TIMELY_DEATH           = 20384
};

enum Yells
{
    SAY_INTRO_1                     = 0,
    SAY_INTRO_2,
    SAY_AGGRO,
    SAY_NOVA,
    SAY_SLAY,
    SAY_75HEALTH,
    SAY_50HEALTH,
    SAY_25HEALTH,
    SAY_DEATH,
    EMOTE_NOVA
};

enum LokenEvents
{
    EVENT_LIGHTNING_NOVA            = 1,
    EVENT_SHOCKWAVE,
    EVENT_ARC_LIGHTNING,
    EVENT_AURA_REMOVE,
    EVENT_INTRO_DIALOGUE,
    EVENT_CHECK_HEALTH
};

enum Phases
{
    PHASE_INTRO                     = 1,
    PHASE_NORMAL
};

class boss_loken : public CreatureScript
{
public:
    boss_loken() : CreatureScript("boss_loken") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_lokenAI (creature);
    }

    struct boss_lokenAI : public ScriptedAI
    {
        boss_lokenAI(Creature* creature) : ScriptedAI(creature)
        {
            m_pInstance = creature->GetInstanceScript();

            me->SetControlled(true, UNIT_STATE_ROOT);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            _isIntroDone = false;
            events.IsInPhase(PHASE_INTRO);
        }

        InstanceScript* m_pInstance;
        EventMap events;

        bool _isIntroDone;
        uint8 HealthCheck;

        void MoveInLineOfSight(Unit* who) override
        {
            if (!_isIntroDone && me->IsValidAttackTarget(who) && me->IsWithinDistInMap(who, 40.0f))
            {
                _isIntroDone = true;
                Talk(SAY_INTRO_1);
                events.ScheduleEvent(EVENT_INTRO_DIALOGUE, 20000, 0, PHASE_INTRO);
            }
        }

        void Reset()
        {
            events.Reset();
            if (m_pInstance)
            {
                m_pInstance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEVEMENT_TIMELY_DEATH);
                m_pInstance->SetData(TYPE_LOKEN, NOT_STARTED);
            }

            HealthCheck = 75;
            me->RemoveAllAuras();
        }

        void EnterCombat(Unit*)
        {
            Talk(SAY_AGGRO);
            events.SetPhase(PHASE_NORMAL);
            events.ScheduleEvent(EVENT_ARC_LIGHTNING, 15000);
            events.ScheduleEvent(EVENT_SHOCKWAVE, 1000);
            events.ScheduleEvent(EVENT_LIGHTNING_NOVA, 20000);

            if (m_pInstance)
                if (me->GetMap()->IsHeroic())
                    m_pInstance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEVEMENT_TIMELY_DEATH);
        }

        void JustDied(Unit*)
        {
            Talk(SAY_DEATH);

            if (m_pInstance)
            {
                m_pInstance->SetData(TYPE_LOKEN, DONE);
                m_pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_PULSING_SHOCKWAVE_AURA);

            }
        }

        void LokenSpeach(bool hp)
        {
            if (hp)
            {
                switch(HealthCheck)
                {
                    case 75: Talk(SAY_75HEALTH); break;
                    case 50: Talk(SAY_50HEALTH); break;
                    case 25: Talk(SAY_25HEALTH); break;
                }
            }
            else
                Talk(SAY_NOVA);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() != TYPEID_PLAYER)
                return;

            Talk(SAY_SLAY);
        }

        void UpdateAI(uint32 diff)
        {
            //Return since we have no target
            if (events.IsInPhase(PHASE_NORMAL) && !UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_CHECK_HEALTH:
                    if (HealthBelowPct(HealthCheck))
                    {
                        LokenSpeach(true);
                        HealthCheck -= 25;
                    }

                    events.RepeatEvent(1000);
                    break;
                case EVENT_LIGHTNING_NOVA:
                    events.RepeatEvent(15000);
                    me->CastSpell(me, SPELL_LIGHTNING_NOVA_VISUAL, true);
                    me->CastSpell(me, SPELL_LIGHTNING_NOVA_THUNDERS, true);

                    events.DelayEvents(5001);
                    events.ScheduleEvent(EVENT_AURA_REMOVE, me->GetMap()->IsHeroic() ? 4000 : 5000);

                    me->CastSpell(me, me->GetMap()->IsHeroic() ? SPELL_LIGHTNING_NOVA_H : SPELL_LIGHTNING_NOVA_N, false);
                    break;
                case EVENT_SHOCKWAVE:
                    me->CastSpell(me, me->GetMap()->IsHeroic() ? SPELL_PULSING_SHOCKWAVE_H : SPELL_PULSING_SHOCKWAVE_N, false);
                    events.PopEvent();
                    break;
                case EVENT_ARC_LIGHTNING:
                    if (Unit* target = SelectTargetFromPlayerList(100, SPELL_ARC_LIGHTNING))
                        me->CastSpell(target, SPELL_ARC_LIGHTNING, false);

                    events.RepeatEvent(12000);
                    break;
                case EVENT_AURA_REMOVE:
                    me->RemoveAura(SPELL_LIGHTNING_NOVA_THUNDERS);
                    events.PopEvent();
                    break;
                case EVENT_INTRO_DIALOGUE:
                    Talk(SAY_INTRO_2);
                    events.SetPhase(PHASE_NORMAL);
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    if (Player* target = me->SelectNearestPlayer(40.0f))
                        AttackStart(target);
                    break;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class spell_loken_pulsing_shockwave : public SpellScriptLoader
{
    public:
        spell_loken_pulsing_shockwave() : SpellScriptLoader("spell_loken_pulsing_shockwave") { }

        class spell_loken_pulsing_shockwave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_loken_pulsing_shockwave_SpellScript);

            void CalculateDamage(SpellEffIndex /*effIndex*/)
            {
                if (!GetHitUnit())
                    return;

                float distance = GetCaster()->GetDistance2d(GetHitUnit());
                if (distance > 1.0f)
                    SetHitDamage(int32(GetHitDamage() * distance));
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_loken_pulsing_shockwave_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_loken_pulsing_shockwave_SpellScript();
        }
};

void AddSC_boss_loken()
{
    new boss_loken();
    new spell_loken_pulsing_shockwave();
}
