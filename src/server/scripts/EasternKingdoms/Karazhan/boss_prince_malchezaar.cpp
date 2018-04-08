/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "karazhan.h"

enum MalchezaarYells
{
    SAY_AGGRO,
    SAY_AXE_TOSS1,
    SAY_AXE_TOSS2,
    //  SAY_SPECIAL1                = 3, Not used, needs to be implemented, but I don't know where it should be used.
    //  SAY_SPECIAL2                = 4, Not used, needs to be implemented, but I don't know where it should be used.
    //  SAY_SPECIAL3                = 5, Not used, needs to be implemented, but I don't know where it should be used.
    SAY_SLAY                        = 6,
    SAY_SUMMON                      = 7,
    SAY_DEATH                       = 8
};

enum MalchezaarSpells
{
    SPELL_SUMMON_INFERNAL           = 30836,
    SPELL_INFERNAL_RELAY            = 30861,
    SPELL_INFERNAL_RELAY_SELECT     = 30835,
    SPELL_SHADOW_NOVA               = 30852,
    SPELL_THRASH                    = 12787,
    SPELL_SUMMON_AXES               = 30891,
    SPELL_EQUIP_ANIM                = 30857,
    SPELL_SUNDER_ARMOR              = 30901,
    SPELL_CLEAVE                    = 30131,
    SPELL_ENFEEBLE                  = 30843,
    SPELL_HELLFIRE                  = 30859,
    SPELL_AMPLIFY_DAMAGE            = 39095,
    SPELL_SHADOW_WORD_PAIN_PHASE1   = 30854,
    SPELL_SHADOW_WORD_PAIN_PHASE3   = 30898
};

enum MalchezaarMisc
{
    NPC_MALCHEZAAR_INFERNAL         = 17646,
    NPC_FLYING_AXE                  = 17650,
    NPC_INFERNAL_TARGET             = 17644,
    NPC_INFERNAL_RELAY              = 17645,
    EQUIP_ID_AXE                    = 33542
};

enum MalchezaarEvents
{
    // Malchezaar
    EVENT_BURNING_ABYSSAL           = 1,
    EVENT_ENFEEBLE,
    EVENT_SHADOW_NOVA,
    EVENT_THRASH,
    EVENT_SUNDER_ARMOR,
    EVENT_CLEAVE,
    EVENT_AMPLIFY_DAMAGE,
    EVENT_SHADOW_WORD_PAIN,
    EVENT_KILL_TALK,

    // Infernal
    EVENT_HELLFIRE                  = 1,
    EVENT_CLEANUP,
    EVENT_CHECK_ENCOUNTER,

    // Axe
    EVENT_CHANGE_TARGET             = 1
};

enum MalchezaarPhases
{
    PHASE_FIRST                     = 1,
    PHASE_SECOND,
    PHASE_THIRD
};

struct boss_malchezaarAI : public BossAI
{
    boss_malchezaarAI(Creature* creature) : BossAI(creature, BOSS_MALCHEZZAR) { }

    void Reset() override
    {
        _Reset();
        ClearWeapons();
    }

    void ClearWeapons()
    {
        SetEquipmentSlots(false, EQUIP_UNEQUIP, EQUIP_UNEQUIP, EQUIP_NO_CHANGE);
        me->SetCanDualWield(false);
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_SLAY);
            events.ScheduleEvent(EVENT_KILL_TALK, 6s);
        }
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
        events.SetPhase(PHASE_FIRST);
        events.ScheduleEvent(EVENT_SHADOW_WORD_PAIN, 20s);
        events.ScheduleEvent(EVENT_BURNING_ABYSSAL, 40s);
        events.ScheduleEvent(EVENT_ENFEEBLE, 30s);
    }

    void JustSummoned(Creature* summon) override
    {
        switch (summon->GetEntry())
        {
            case NPC_MALCHEZAAR_INFERNAL:
                summons.Summon(summon);
                summon->SetSelectable(false);
                summon->SetPassive();
                break;
            case NPC_FLYING_AXE:
                summon->SetSelectable(false);
                BossAI::JustSummoned(summon);
                break;
            default:
                break;
        }

    }

    void DamageTaken(Unit* attacker, uint32 &damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*schoolmask*/) override
    {
        if (events.IsInPhase(PHASE_FIRST) && me->HealthBelowPctDamaged(60, damage))
        {
            DoCastSelf(SPELL_THRASH, true);
            events.SetPhase(PHASE_SECOND);
            me->SetCanDualWield(true);
            me->InterruptNonMeleeSpells(false);
            DoCastSelf(SPELL_EQUIP_ANIM);
            Talk(SAY_AXE_TOSS1);
            SetEquipmentSlots(false, EQUIP_ID_AXE, EQUIP_ID_AXE, EQUIP_NO_CHANGE);
            me->SetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE, me->GetCreatureTemplate()->mindmg);
            me->SetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE, me->GetCreatureTemplate()->maxdmg);
            me->SetAttackTime(OFF_ATTACK, (me->GetAttackTime(BASE_ATTACK) * 150) / 100);
            events.ScheduleEvent(EVENT_SUNDER_ARMOR, 5s, 10s, 0, PHASE_SECOND);
            events.ScheduleEvent(EVENT_CLEAVE, 8s, 0, PHASE_SECOND);
        }
        else if (events.IsInPhase(PHASE_SECOND) && me->HealthBelowPctDamaged(30, damage))
        {
            events.SetPhase(PHASE_THIRD);
            Talk(SAY_AXE_TOSS2);
            ClearWeapons();
            events.RescheduleEvent(EVENT_BURNING_ABYSSAL, 15s);
            events.RescheduleEvent(EVENT_SHADOW_NOVA, 25s);
            events.ScheduleEvent(EVENT_AMPLIFY_DAMAGE, 5s);
            me->RemoveAurasDueToSpell(SPELL_THRASH);
            events.CancelEvent(EVENT_ENFEEBLE);
            DoCastAOE(SPELL_SUMMON_AXES, true);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->IsCasting() || me->HasUnitState(UNIT_STATE_STUNNED))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SHADOW_WORD_PAIN:
                    if (events.IsInPhase(PHASE_FIRST))
                        DoCastVictim(SPELL_SHADOW_WORD_PAIN_PHASE1);
                    else if (events.IsInPhase(PHASE_THIRD))
                        DoCastSelf(SPELL_SHADOW_WORD_PAIN_PHASE3);
                    events.Repeat(20s);
                    break;
                case EVENT_BURNING_ABYSSAL:
                    Talk(SAY_SUMMON);
                    DoCastAOE(SPELL_INFERNAL_RELAY);
                    events.Repeat(events.IsInPhase(PHASE_THIRD) ? 15s : 45s);
                    break;
                case EVENT_ENFEEBLE:
                    DoCastSelf(SPELL_ENFEEBLE);
                    events.ScheduleEvent(EVENT_SHADOW_NOVA, 5s);
                    events.Repeat(30s);
                    break;
                case EVENT_SHADOW_NOVA:
                    DoCastSelf(SPELL_SHADOW_NOVA);
                    if (events.IsInPhase(PHASE_THIRD))
                        events.Repeat(31s);
                    break;
                case EVENT_SUNDER_ARMOR:
                    DoCastVictim(SPELL_SUNDER_ARMOR);
                    events.Repeat(10s, 18s);
                    break;
                case EVENT_CLEAVE:
                    DoCastVictim(SPELL_CLEAVE);
                    events.Repeat(6s, 12s);
                    break;
                case EVENT_AMPLIFY_DAMAGE:
                    DoCastSelf(SPELL_AMPLIFY_DAMAGE);
                    events.Repeat(20s, 30s);
                    break;
                default:
                    break;
            }

            if (me->IsCasting() || me->HasUnitState(UNIT_STATE_STUNNED))
                return;
        }

        DoMeleeAttackIfReady();
    }
};

struct npc_malchezaar_addAI : public ScriptedAI
{
    npc_malchezaar_addAI(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
    }

    void Reset() override
    {
        _events.Reset();
    }

    void DamageTaken(Unit* /*attacker*/, uint32 &damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*schoolmask*/) override
    {
        damage = 0;
    }

    void KilledUnit(Unit* who) override
    {
        if (Creature* malchezzar = _instance->GetCreature(BOSS_MALCHEZZAR))
            if (malchezzar->IsAIEnabled)
                malchezzar->AI()->KilledUnit(who);
    }

    virtual void DoEvent(uint32 /*eventId*/) = 0;

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
            DoEvent(eventId);

        if (me->GetEntry() == NPC_FLYING_AXE)
            DoMeleeAttackIfReady();
    }

    protected:
        EventMap _events;
    private:
        InstanceScript* _instance;
};

struct netherspite_infernalAI : public npc_malchezaar_addAI
{
    netherspite_infernalAI(Creature* creature) : npc_malchezaar_addAI(creature) { }

    void Reset() override
    {
        _events.ScheduleEvent(EVENT_HELLFIRE, 4s);
        _events.ScheduleEvent(EVENT_CLEANUP, 3min);
        _events.ScheduleEvent(EVENT_CHECK_ENCOUNTER, 0s);
    }

    void MoveInLineOfSight(Unit* /*who*/) override { }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_HELLFIRE:
                DoCastSelf(SPELL_HELLFIRE);
                break;
            case EVENT_CLEANUP:
                me->DespawnOrUnsummon();
                break;
            case EVENT_CHECK_ENCOUNTER:
                // Infernal may spawn when fight already ends
                if (auto instance = me->GetInstanceScript())
                    if (instance->GetBossState(BOSS_MALCHEZZAR) != IN_PROGRESS)
                        _events.RescheduleEvent(EVENT_CLEANUP, 0s);
                _events.Repeat(5s);
                break;
            default:
                break;
        }
    }
};

struct npc_flying_axeAI : public npc_malchezaar_addAI
{
    npc_flying_axeAI(Creature* creature) : npc_malchezaar_addAI(creature) { }

    void EnterCombat(Unit* /*who*/) override
    {
        _events.ScheduleEvent(EVENT_CHANGE_TARGET, 7.5s, 20.0s);
    }

    void DoEvent(uint32 eventId) override
    {
        if (eventId != EVENT_CHANGE_TARGET)
            return;

        if (Unit* victim = me->GetVictim())
            DoModifyThreatPercent(victim, -100);

        if (Unit* target = SelectTargetFromPlayerList(100.0f))
        {
            AttackStart(target);
            me->AddThreat(target, 1000000.0f);
        }

        _events.Repeat(7.5s, 20.0s);
    }
};

struct npc_infernal_targetAI : public ScriptedAI
{
    npc_infernal_targetAI(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
    }

    void JustSummoned(Creature* summon) override
    {
        // Inform boss
        if (_instance)
            if (Creature* malchezzar = _instance->GetCreature(BOSS_MALCHEZZAR))
                if (malchezzar->IsAIEnabled)
                    malchezzar->AI()->JustSummoned(summon);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        // Inform boss
        if (_instance)
            if (Creature* malchezzar = _instance->GetCreature(BOSS_MALCHEZZAR))
                if (malchezzar->IsAIEnabled)
                    malchezzar->AI()->SummonedCreatureDespawn(summon);
    }

private:
    InstanceScript* _instance;
};

class spell_malchezzar_enfeeble_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_malchezzar_enfeeble_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        Trinity::Containers::RandomResize(targets, [&](WorldObject* target)
        {
            if (!target->IsPlayer())
                return false;

            // Exclude tank from target list
            if (Unit* victim = GetCaster()->GetVictim())
                if (victim == target)
                    return false;

            return true;
        }, 5);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_malchezzar_enfeeble_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_malchezzar_enfeeble_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

class spell_malchezzar_enfeeble_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_malchezzar_enfeeble_AuraScript);

    float _healthPct;

    bool Load() override
    {
        _healthPct = 0;
        return true;
    }

    void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        _healthPct = GetTarget()->GetHealthPct();
        GetTarget()->SetHealth(1);
    }

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->SetHealth(GetTarget()->CountPctFromMaxHealth(_healthPct));
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_malchezzar_enfeeble_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_HEALING_PCT, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_malchezzar_enfeeble_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_HEALING_PCT, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_malchezzar_infernal_relay_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_malchezzar_infernal_relay_SpellScript);

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            target->CastSpell(target, SPELL_INFERNAL_RELAY_SELECT, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_malchezzar_infernal_relay_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class spell_malchezzar_infernal_relay_selector_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_malchezzar_infernal_relay_selector_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        Trinity::Containers::RandomResize(targets, [](WorldObject* target) -> bool { return target->GetEntry() == NPC_INFERNAL_TARGET && !target->FindNearestCreature(NPC_MALCHEZAAR_INFERNAL, 2.0f); }, 1);
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            target->CastSpell(target, SPELL_SUMMON_INFERNAL, true);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_malchezzar_infernal_relay_selector_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        OnEffectHitTarget += SpellEffectFn(spell_malchezzar_infernal_relay_selector_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class spell_malchezzar_amplify_damage_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_malchezzar_amplify_damage_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        Trinity::Containers::RandomResize(targets, [](WorldObject* target) -> bool { return target->IsPlayer(); }, 1);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_malchezzar_amplify_damage_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

class spell_malchezzar_shadow_word_pain_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_malchezzar_shadow_word_pain_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        Trinity::Containers::RandomResize(targets, [](WorldObject* target) -> bool { return target->IsPlayer(); }, 1);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_malchezzar_shadow_word_pain_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

void AddSC_boss_malchezaar()
{
    new CreatureAILoader<boss_malchezaarAI>("boss_malchezaar");
    new CreatureAILoader<netherspite_infernalAI>("netherspite_infernal");
    new CreatureAILoader<npc_flying_axeAI>("npc_flying_axe");
    new CreatureAILoader<npc_infernal_targetAI>("npc_infernal_target");
    new SpellAuraScriptLoaderEx<spell_malchezzar_enfeeble_SpellScript, spell_malchezzar_enfeeble_AuraScript>("spell_malchezzar_enfeeble");
    new SpellScriptLoaderEx<spell_malchezzar_infernal_relay_SpellScript>("spell_malchezzar_infernal_relay");
    new SpellScriptLoaderEx<spell_malchezzar_infernal_relay_selector_SpellScript>("spell_malchezzar_infernal_relay_selector");
    new SpellScriptLoaderEx<spell_malchezzar_amplify_damage_SpellScript>("spell_malchezzar_amplify_damage");
    new SpellScriptLoaderEx<spell_malchezzar_shadow_word_pain_SpellScript>("spell_malchezzar_shadow_word_pain");
}
