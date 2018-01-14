#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "forge_of_souls.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "PassiveAI.h"
#include "GridNotifiers.h"

enum BronjahmYells
{
    SAY_AGGRO                       = 0,
    SAY_SLAY,
    SAY_DEATH,
    SAY_SOUL_STORM,
    SAY_CORRUPT_SOUL
};

enum BronjahmSpells
{
    SPELL_SOULSTORM_CHANNEL_OOC     = 69008,

    SPELL_SHADOW_BOLT               = 70043,
    SPELL_FEAR                      = 68950,
    SPELL_MAGICS_BANE               = 68793,

    SPELL_CORRUPT_SOUL              = 68839,
    SPELL_KNOCK_DOWN                = 68848,
    SPELL_CONSUME_SOUL              = 68861,
    SPELL_PURPLE_BANISH_VISUAL      = 68862,  // Used by Soul Fragment (Aura)

    SPELL_TELEPORT                  = 68988,
    SPELL_TELEPORT_VISUAL           = 52096,

    SPELL_SOULSTORM_VISUAL          = 68870,
    SPELL_SOULSTORM                 = 68872
};

enum BronjahmEvents
{
    EVENT_FEAR                      = 1,
    EVENT_MAGICS_BANE,
    EVENT_CORRUPT_SOUL,
    EVENT_START_SOULSTORM,
    EVENT_SCAN_FOR_SOULS,
    EVENT_KILL_TALK
};

struct boss_bronjahmAI : public BossAI
{
    boss_bronjahmAI(Creature* creature) : BossAI(creature, DATA_BRONJAHM) {}

    void Reset() override
    {
        _Reset();
        SetCombatMovement(true);
        DoCastSelf(SPELL_SOULSTORM_CHANNEL_OOC, true);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
        me->RemoveAurasDueToSpell(SPELL_SOULSTORM_CHANNEL_OOC);
        events.ScheduleEvent(EVENT_MAGICS_BANE, urand(7000, 12000), 1);
        events.ScheduleEvent(EVENT_CORRUPT_SOUL, urand(14000, 20000), 1);
        events.ScheduleEvent(EVENT_SCAN_FOR_SOULS, 100);
    }

    bool IsInPhase2() const
    {
        return !IsCombatMovementAllowed();
    }

    void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (!IsInPhase2() && me->HealthBelowPctDamaged(35, damage) && !me->HasUnitState(UNIT_STATE_CASTING))
        {
            SetCombatMovement(false);
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            DoCastSelf(SPELL_TELEPORT);
            events.CancelEvent(EVENT_CORRUPT_SOUL);
            events.DelayEvents(6000, 1); // bronjahm should still heal with souls
        }
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_TELEPORT)
        {
            DoCastSelf(SPELL_TELEPORT_VISUAL, true);
            events.ScheduleEvent(EVENT_START_SOULSTORM, 1, 1);
            events.ScheduleEvent(EVENT_FEAR, 5s, 1);
        }
    }

    uint32 GetData(uint32 type) const override
    {
        if (type == DATA_SOUL_POWER)
        {
            uint32 count = 0;
            for (auto guid : summons)
            {
                if (Creature* summon = instance->instance->GetCreature(guid))
                    if (summon->GetEntry() == NPC_CORRUPTED_SOUL_FRAGMENT && summon->IsAlive())
                        ++count;
            }
            return count;
        }

        return 0;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_FEAR:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 10.0f, true))
                        me->CastCustomSpell(SPELL_FEAR, SPELLVALUE_MAX_TARGETS, 1, target, false);
                    events.Repeat(urand(8000, 12000));
                    break;
                case EVENT_MAGICS_BANE:
                    DoCastAOE(SPELL_MAGICS_BANE);
                    events.Repeat(urand(7000, 20000));
                    break;
                case EVENT_CORRUPT_SOUL:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                    {
                        Talk(SAY_CORRUPT_SOUL);
                        DoCast(target, SPELL_CORRUPT_SOUL);
                    }
                    events.Repeat(urand(18000, 25000));
                    break;
                case EVENT_START_SOULSTORM:
                    Talk(SAY_SOUL_STORM);
                    DoCastSelf(SPELL_SOULSTORM);
                    DoCastSelf(SPELL_SOULSTORM_VISUAL, true);
                    break;
                case EVENT_SCAN_FOR_SOULS:
                    for (auto guid : summons)
                        if (auto soul = instance->instance->GetCreature(guid))
                            if (me->IsInRange(soul, 0.0f, 2.0f))
                            {
                                soul->GetMotionMaster()->MoveIdle();
                                soul->CastSpell(me, SPELL_CONSUME_SOUL, true);
                                soul->DespawnOrUnsummon(1);
                            }

                    events.Repeat(100);
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

        }

        if (IsInPhase2() || (!IsInPhase2() && !me->IsWithinMeleeRange(me->GetVictim())))
        {
            DoSpellAttackIfReady(SPELL_SHADOW_BOLT);
            return;
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
    }

    void KilledUnit(Unit* who) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_SLAY);
            events.ScheduleEvent(EVENT_KILL_TALK, 6000);
        }
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_CORRUPTED_SOUL_FRAGMENT)
        {
            summons.Summon(summon);
            summon->SetReactState(REACT_PASSIVE);
            summon->GetMotionMaster()->MoveFollow(me, 0.0f, 0.0f);
            summon->CastSpell(summon, SPELL_PURPLE_BANISH_VISUAL, true);
        }
    }

    void EnterEvadeMode() override
    {
        _DespawnAtEvade();
    }
};

class spell_bronjahm_magic_bane_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_bronjahm_magic_bane_SpellScript)

    void RecalculateDamage()
    {
        if (GetHitUnit()->getPowerType() != POWER_MANA)
            return;

        Unit* caster = GetCaster();
        const int32 maxDamage = caster->GetMap()->GetSpawnMode() == 1 ? 15000 : 10000;
        int32 newDamage = GetHitDamage();
        newDamage += GetHitUnit()->GetMaxPower(POWER_MANA) / 2;
        newDamage = std::min<int32>(maxDamage, newDamage);

        SetHitDamage(newDamage);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_bronjahm_magic_bane_SpellScript::RecalculateDamage);
    }
};

class spell_bronjahm_soulstorm_channel_ooc_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_bronjahm_soulstorm_channel_ooc_AuraScript)

    void HandlePeriodicTick(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        GetTarget()->CastSpell(GetTarget(), 68904 + (aurEff->GetTickNumber() % 4), true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_bronjahm_soulstorm_channel_ooc_AuraScript::HandlePeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_bronjahm_soulstorm_visual_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_bronjahm_soulstorm_visual_AuraScript)

        void HandlePeriodicTick(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        uint32 spellId = 0;
        switch (aurEff->GetTickNumber() % 4)
        {
            case 0: spellId = 68886; break;
            case 1: spellId = 68896; break;
            case 2: spellId = 68897; break;
            case 3: spellId = 68898; break;
        }

        if (spellId)
            GetTarget()->CastSpell(GetTarget(), spellId, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_bronjahm_soulstorm_visual_AuraScript::HandlePeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_bronjahm_soulstorm_targeting_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_bronjahm_soulstorm_targeting_SpellScript)

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Trinity::AllWorldObjectsInExactRange(GetCaster(), 10.0f, false));
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_bronjahm_soulstorm_targeting_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class spell_bronjahm_corrupt_soul_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_bronjahm_corrupt_soul_AuraScript)

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_CONSUME_SOUL, SPELL_KNOCK_DOWN });
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
        if (removeMode != AURA_REMOVE_BY_EXPIRE)
            return;

        GetTarget()->CastSpell(GetTarget(), SPELL_KNOCK_DOWN, true);
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_bronjahm_corrupt_soul_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class achievement_bronjahm_soul_power : public AchievementCriteriaScript
{
public:
    achievement_bronjahm_soul_power() : AchievementCriteriaScript("achievement_bronjahm_soul_power") { }

    bool OnCheck(Player* /*source*/, Unit* target) override
    {
        if (target && target->ToUnit() && target->ToUnit()->IsAIEnabled && target->GetMap()->IsHeroic())
            return target->GetAI()->GetData(DATA_SOUL_POWER) >= 4;
        return false;
    }
};

void AddSC_boss_bronjahm()
{
    new CreatureAILoader<boss_bronjahmAI>("boss_bronjahm");
    new SpellScriptLoaderEx<spell_bronjahm_magic_bane_SpellScript>("spell_bronjahm_magic_bane");
    new AuraScriptLoaderEx<spell_bronjahm_soulstorm_channel_ooc_AuraScript>("spell_bronjahm_soulstorm_channel_ooc");
    new AuraScriptLoaderEx<spell_bronjahm_soulstorm_visual_AuraScript>("spell_bronjahm_soulstorm_visual");
    new SpellScriptLoaderEx<spell_bronjahm_soulstorm_targeting_SpellScript>("spell_bronjahm_soulstorm_targeting");
    new AuraScriptLoaderEx<spell_bronjahm_corrupt_soul_AuraScript>("spell_bronjahm_corrupt_soul");
    new achievement_bronjahm_soul_power();
}