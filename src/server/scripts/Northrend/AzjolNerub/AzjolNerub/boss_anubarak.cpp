#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "azjol_nerub.h"
#include "SpellInfo.h"
#include "SpellScript.h"

enum Spells
{
    SPELL_CARRION_BEETLES              = 53520,
    SPELL_SUMMON_CARRION_BEETLES       = 53521,
    SPELL_LEECHING_SWARM               = 53467,
    SPELL_POUND                        = 53472,
    SPELL_POUND_DAMAGE                 = 53509,
    SPELL_IMPALE_VISUAL                = 53455,
    SPELL_IMPALE_PERIODIC              = 53456,
    SPELL_EMERGE                       = 53500,
    SPELL_SUBMERGE                     = 53421,
    SPELL_SELF_ROOT                    = 42716,

    SPELL_SUMMON_DARTER                = 53599,
    SPELL_SUMMON_ASSASSIN              = 53610,
    SPELL_SUMMON_GUARDIAN              = 53614,
    SPELL_SUMMON_VENOMANCER            = 53615
};

enum Yells
{
    SAY_AGGRO                          = 0,
    SAY_SLAY                           = 1,
    SAY_DEATH                          = 2,
    SAY_LOCUST                         = 3,
    SAY_SUBMERGE                       = 4,
    SAY_INTRO                          = 5
};

enum Misc
{
    ACHIEV_TIMED_START_EVENT           = 20381,

    EVENT_CARRION_BEETELS              = 1,
    EVENT_LEECHING_SWARM,
    EVENT_IMPALE,
    EVENT_POUND,
    EVENT_CLOSE_DOORS,
    EVENT_EMERGE,
    EVENT_SUMMON_VENOMANCER,
    EVENT_SUMMON_DARTER,
    EVENT_SUMMON_GUARDIAN,
    EVENT_SUMMON_ASSASSINS,
    EVENT_ENABLE_ROTATE,
    EVENT_KILL_TALK,
    EVENT_CHECK_BOUNDARY
};

static Position _boundaryPos = { 550.378235f, 254.530029f, 223.851212f };

struct boss_anub_arakAI : public BossAI
{
    boss_anub_arakAI(Creature* creature) : BossAI(creature, DATA_ANUBARAK_EVENT)
    {
        me->m_SightDistance = 120.0f;
        _intro = false;
        _phase = 0;
    }

    void EnterEvadeMode() override
    {
        me->DisableRotate(false);
        _DespawnAtEvade();
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (!_intro && who->IsPlayer())
        {
            _intro = true;
            Talk(SAY_INTRO);
        }

        BossAI::MoveInLineOfSight(who);
    }

    void JustDied(Unit* killer) override
    {
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
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

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
        if (!summon->IsTrigger())
            summon->SetInCombatWithZone();
    }

    void Reset() override
    {
        _phase = 0;
        _Reset();
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
        instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_TIMED_START_EVENT);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        Talk(SAY_AGGRO);
        instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_TIMED_START_EVENT);

        events.ScheduleEvent(EVENT_CHECK_BOUNDARY, 500, 1);
        events.ScheduleEvent(EVENT_CARRION_BEETELS, urand(14000, 17000));
        events.ScheduleEvent(EVENT_LEECHING_SWARM, urand(5000, 7000));
        events.ScheduleEvent(EVENT_POUND, urand(2000, 4000));
        events.ScheduleEvent(EVENT_CLOSE_DOORS, 5000);
    }

    void SummonHelpers(float x, float y, float z, uint32 spellId)
    {
        const SpellInfo* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        me->SummonCreature(spellInfo->Effects[EFFECT_0].MiscValue, x, y, z);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType det, SpellSchoolMask) override
    {
        if (me->HealthBelowPctDamaged(75, damage) && _phase == 0 || me->HealthBelowPctDamaged(50, damage) && _phase == 1 || me->HealthBelowPctDamaged(25, damage) && _phase == 2)
        {
            ++_phase;
            me->InterruptNonMeleeSpells(true);
            Talk(SAY_SUBMERGE);
            DoCastSelf(SPELL_IMPALE_PERIODIC, true);
            DoCastSelf(SPELL_SUBMERGE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);

            events.DelayEvents(46000, 0);
            events.ScheduleEvent(EVENT_EMERGE, 45000);
            events.ScheduleEvent(EVENT_SUMMON_ASSASSINS, 2000);
            events.ScheduleEvent(EVENT_SUMMON_GUARDIAN, 4000);
            events.ScheduleEvent(EVENT_SUMMON_ASSASSINS, 15000);
            events.ScheduleEvent(EVENT_SUMMON_VENOMANCER, 20000);
            events.ScheduleEvent(EVENT_SUMMON_DARTER, 30000);
            events.ScheduleEvent(EVENT_SUMMON_ASSASSINS, 35000);
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CLOSE_DOORS:
                _EnterCombat();
                break;
            case EVENT_CARRION_BEETELS:
                DoCastSelf(SPELL_CARRION_BEETLES);
                events.Repeat(urand(24000, 27000));
                break;
            case EVENT_LEECHING_SWARM:
                Talk(SAY_LOCUST);
                DoCastSelf(SPELL_LEECHING_SWARM);
                events.Repeat(urand(25000, 28000));
                break;
            case EVENT_POUND:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 10.0f))
                {
                    DoCastSelf(SPELL_SELF_ROOT, true);
                    me->DisableRotate(true);
                    me->SendMovementFlagUpdate();
                    DoCast(target, SPELL_POUND);
                    if (auto sInfo = sSpellMgr->GetSpellInfo(SPELL_POUND))
                        events.ScheduleEvent(EVENT_ENABLE_ROTATE, sInfo->CastTimeEntry->CastTime + 100);

                }
                events.Repeat(urand(26000, 32000));
                break;
            case EVENT_ENABLE_ROTATE:
                me->RemoveAurasDueToSpell(SPELL_SELF_ROOT);
                me->DisableRotate(false);
                break;
            case EVENT_EMERGE:
                me->SetReactState(REACT_AGGRESSIVE);
                DoCastSelf(SPELL_EMERGE, true);
                me->RemoveAura(SPELL_SUBMERGE);
                me->RemoveAura(SPELL_IMPALE_PERIODIC);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                break;
            case EVENT_SUMMON_ASSASSINS:
                SummonHelpers(509.32f, 247.42f, 239.48f, SPELL_SUMMON_ASSASSIN);
                SummonHelpers(589.51f, 240.19f, 236.0f, SPELL_SUMMON_ASSASSIN);
                break;
            case EVENT_SUMMON_DARTER:
                SummonHelpers(509.32f, 247.42f, 239.48f, SPELL_SUMMON_DARTER);
                SummonHelpers(589.51f, 240.19f, 236.0f, SPELL_SUMMON_DARTER);
                break;
            case EVENT_SUMMON_GUARDIAN:
                SummonHelpers(550.34f, 316.00f, 234.30f, SPELL_SUMMON_GUARDIAN);
                break;
            case EVENT_SUMMON_VENOMANCER:
                SummonHelpers(550.34f, 316.00f, 234.30f, SPELL_SUMMON_VENOMANCER);
                break;
            case EVENT_CHECK_BOUNDARY:
                if (me->GetDistance(_boundaryPos) > 15.0f)
                    EnterEvadeMode();
                events.Repeat(500);
                break;
            default:
                break;
        }
    }

    private:
        bool _intro;
        uint8 _phase;
};

class spell_azjol_nerub_carrion_beetelsAuraScript : public AuraScript
{
    PrepareAuraScript(spell_azjol_nerub_carrion_beetelsAuraScript)

    void HandleEffectPeriodic(AuraEffect const* aurEff)
    {
        // Xinef: 2 each second
        GetUnitOwner()->CastSpell(GetUnitOwner(), SPELL_SUMMON_CARRION_BEETLES, true);
        GetUnitOwner()->CastSpell(GetUnitOwner(), SPELL_SUMMON_CARRION_BEETLES, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_azjol_nerub_carrion_beetelsAuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_azjol_nerub_pound_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_azjol_nerub_pound_SpellScript)

    void HandleApplyAura(SpellEffIndex effIndex)
    {
        if (Unit* unitTarget = GetHitUnit())
            GetCaster()->CastSpell(unitTarget, SPELL_POUND_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_azjol_nerub_pound_SpellScript::HandleApplyAura, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};

class spell_azjol_nerub_impale_summon_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_azjol_nerub_impale_summon_SpellScript)

    void SetDest(SpellDestination& dest)
    {
        // Adjust effect summon position
        float floorZ = GetCaster()->GetMap()->GetHeight(GetCaster()->GetPositionX(), GetCaster()->GetPositionY(), GetCaster()->GetPositionZ(), true);
        if (floorZ > INVALID_HEIGHT)
            dest._position.m_positionZ = floorZ;
    }

    void Register()
    {
        OnDestinationTargetSelect += SpellDestinationTargetSelectFn(spell_azjol_nerub_impale_summon_SpellScript::SetDest, EFFECT_0, TARGET_DEST_CASTER);
    }
};

void AddSC_boss_anub_arak()
{
    new CreatureAILoader<boss_anub_arakAI>("boss_anub_arak");
    new AuraScriptLoaderEx<spell_azjol_nerub_carrion_beetelsAuraScript>("spell_azjol_nerub_carrion_beetels");
    new SpellScriptLoaderEx<spell_azjol_nerub_pound_SpellScript>("spell_azjol_nerub_pound");
    new SpellScriptLoaderEx<spell_azjol_nerub_impale_summon_SpellScript>("spell_azjol_nerub_impale_summon");
}
