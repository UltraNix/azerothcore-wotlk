#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "halls_of_stone.h"
#include "Player.h"

enum KrystallusSpells
{
    SPELL_GROUND_SPIKE                          = 59750,
    SPELL_BOULDER_TOSS                          = 50843,
    SPELL_SHATTER                               = 50810,
    SPELL_STOMP                                 = 50868,
    SPELL_STOMP_H                               = 59744,
    SPELL_GROUND_SLAM                           = 50827,
    SPELL_GROUND_SLAM_STONED_EFFECT             = 50812,
    SPELL_SHATTER_EFFECT                        = 50811
};

enum KrystallusEvents
{
    EVENT_BOULDER                               = 1,
    EVENT_STOMP,
    EVENT_GROUND_SLAM,
    EVENT_GROUND_SPIKE,
    EVENT_SHATTER,
    EVENT_REMOVE_STONED,
    EVENT_KILL_TALK
};

enum KrystallusYells
{
    SAY_AGGRO                                   = 0,
    SAY_KILL,
    SAY_DEATH,
    SAY_SHATTER
};

struct boss_krystallusAI : public BossAI
{
    boss_krystallusAI(Creature* creature) : BossAI(creature, BOSS_KRYSTALLUS) {}

    void Reset() override
    {
        _Reset();
        instance->SetData(BOSS_KRYSTALLUS, NOT_STARTED);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        events.RescheduleEvent(EVENT_BOULDER, urand(3000, 9000));
        events.RescheduleEvent(EVENT_STOMP, urand(20000, 29000));
        events.RescheduleEvent(EVENT_GROUND_SLAM, urand(15000, 18000));
        if (IsHeroic())
            events.RescheduleEvent(EVENT_GROUND_SPIKE, urand(9000, 14000));

        instance->SetData(BOSS_KRYSTALLUS, IN_PROGRESS);

        Talk(SAY_AGGRO);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_BOULDER:
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true, 0))
                    DoCast(target, SPELL_BOULDER_TOSS);

                events.Repeat(urand(9000, 15000));
                break;
            case EVENT_GROUND_SPIKE:
                DoCastVictim(SPELL_GROUND_SPIKE); 
                events.Repeat(urand(8000, 11000));
                break;
            case EVENT_STOMP:
                DoCastSelf(DUNGEON_MODE(SPELL_STOMP, SPELL_STOMP_H));
                events.Repeat(urand(20000, 29000));
                break;
            case EVENT_GROUND_SLAM:
                events.Repeat(urand(15000, 18000));
                DoCastVictim(SPELL_GROUND_SLAM, true);
                events.DelayEvents(10000);
                events.RescheduleEvent(EVENT_SHATTER, 8000);
                break;
            case EVENT_SHATTER:
                DoCastAOE(SPELL_SHATTER);
                Talk(SAY_SHATTER);
                events.RescheduleEvent(EVENT_REMOVE_STONED, 1500);
                break;
            case EVENT_REMOVE_STONED:
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_GROUND_SLAM_STONED_EFFECT);
                break;
            default:
                break;
        }
    }

    void EnterEvadeMode() override
    {
        _DespawnAtEvade();
    }

    void JustDied(Unit* /*killer*/)
    {
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_GROUND_SLAM_STONED_EFFECT);
        Talk(SAY_DEATH);
        instance->SetData(BOSS_KRYSTALLUS, DONE);
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_KILL);
            events.ScheduleEvent(EVENT_KILL_TALK, 6000);
        }
    }
};

class spell_krystallus_shatter_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_krystallus_shatter_SpellScript)

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
        {
            target->RemoveAurasDueToSpell(SPELL_GROUND_SLAM_STONED_EFFECT);
            target->CastSpell((Unit*)nullptr, SPELL_SHATTER_EFFECT, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_krystallus_shatter_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class spell_krystallus_shatter_effect_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_krystallus_shatter_effect_SpellScript)

    void CalculateDamage()
    {
        if (!GetHitUnit())
            return;

        float radius = GetSpellInfo()->Effects[EFFECT_0].CalcRadius(GetCaster());
        if (!radius)
            return;

        float distance = GetCaster()->GetDistance2d(GetHitUnit());
        if (distance > 1.0f)
            SetHitDamage(int32(GetHitDamage() * ((radius - distance) / radius)));
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_krystallus_shatter_effect_SpellScript::CalculateDamage);
    }
};

void AddSC_boss_krystallus()
{
    new CreatureAILoader<boss_krystallusAI>("boss_krystallus");
    new SpellScriptLoaderEx<spell_krystallus_shatter_SpellScript>("spell_krystallus_shatter");
    new SpellScriptLoaderEx<spell_krystallus_shatter_effect_SpellScript>("spell_krystallus_shatter_effect");
}