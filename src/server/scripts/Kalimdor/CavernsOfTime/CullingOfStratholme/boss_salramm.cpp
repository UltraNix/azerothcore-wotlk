#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "culling_of_stratholme.h"

enum SalrammSpells
{
    SPELL_CURSE_OF_TWISTED_FLESH    = 58845,
    SPELL_EXPLODE_GHOUL             = 52480,
    SPELL_SHADOW_BOLT               = 57725,
    SPELL_STEAL_FLESH               = 52708,
    SPELL_STEAL_FLESH_DEBUFF        = 52711,
    SPELL_STEAL_FLESH_BUFF          = 52712,
    SPELL_SUMMON_GHOULS             = 52451
};

enum SalrammYells
{
    SAY_AGGRO                       = 0,
    SAY_SPAWN,
    SAY_SLAY,
    SAY_DEATH,
    SAY_EXPLODE_GHOUL,
    SAY_STEAL_FLESH,
    SAY_SUMMON_GHOULS
};

enum SalrammEvents
{
    EVENT_CURSE_FLESH               = 1,
    EVENT_EXPLODE_GHOUL1,
    EVENT_EXPLODE_GHOUL2,
    EVENT_SHADOW_BOLT,
    EVENT_STEAL_FLESH,
    EVENT_SUMMON_GHOULS,
    EVENT_KILL_TALK
};

struct boss_salrammAI : public BossAI
{
    boss_salrammAI(Creature* creature) : BossAI(creature, DATA_SALRAMM) 
    { 
        Talk(SAY_SPAWN);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        Talk(SAY_AGGRO);
        _EnterCombat();

        events.ScheduleEvent(EVENT_SUMMON_GHOULS, urand(19000, 24000));
        events.ScheduleEvent(EVENT_SHADOW_BOLT, 2000);
        events.ScheduleEvent(EVENT_STEAL_FLESH, urand(25000, 35000));
        if (IsHeroic())
            events.ScheduleEvent(EVENT_CURSE_FLESH, 40000);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CURSE_FLESH:
                DoCastVictim(SPELL_CURSE_OF_TWISTED_FLESH);
                events.Repeat(37000);
                break;
            case EVENT_SUMMON_GHOULS:
                Talk(SAY_SUMMON_GHOULS);
                DoCastAOE(SPELL_SUMMON_GHOULS);
                events.ScheduleEvent(EVENT_EXPLODE_GHOUL1, urand(20000, 24000));
                events.ScheduleEvent(EVENT_EXPLODE_GHOUL2, urand(25000, 29000));
                break;
            case EVENT_SHADOW_BOLT:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                    DoCast(target, SPELL_SHADOW_BOLT);
                events.Repeat(3000);
                break;
            case EVENT_STEAL_FLESH:
                Talk(SAY_STEAL_FLESH);
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 50.0f, true))
                    DoCast(target, SPELL_STEAL_FLESH);
                events.Repeat(urand(15000, 20000));
                break;
            case EVENT_EXPLODE_GHOUL2:
                events.ScheduleEvent(EVENT_SUMMON_GHOULS, 4000);
                // intentional missing break
            case EVENT_EXPLODE_GHOUL1:
                Talk(SAY_EXPLODE_GHOUL);
                DoCastAOE(SPELL_EXPLODE_GHOUL, true);
                break;
            default:
                break;
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_DEATH);
        _JustDied();
    }

    void KilledUnit(Unit* victim) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_SLAY);
            events.ScheduleEvent(EVENT_KILL_TALK, 6000);
        }
    }
};

class spell_salramm_steal_flesh_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_salramm_steal_flesh_AuraScript)

    void HandlePeriodic(AuraEffect const* /*eff*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(caster, SPELL_STEAL_FLESH_BUFF, true);
            caster->CastSpell(GetTarget(), SPELL_STEAL_FLESH_DEBUFF, true);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_salramm_steal_flesh_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_boss_salramm()
{
    new CreatureAILoader<boss_salrammAI>("boss_salramm");
    new AuraScriptLoaderEx<spell_salramm_steal_flesh_AuraScript>("spell_salramm_steal_flesh");
}
