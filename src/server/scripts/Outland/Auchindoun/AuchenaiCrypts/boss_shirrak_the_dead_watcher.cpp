#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Player.h"
#include "SpellInfo.h"
#include "SpellAuras.h"
#include "SpellScript.h"

enum eShirrak
{
    SPELL_INHIBIT_MAGIC                     = 32264,
    SPELL_ATTRACT_MAGIC                     = 32265,
    SPELL_CARNIVOROUS_BITE_N                = 36383,
    SPELL_CARNIVOROUS_BITE_H                = 39382,

    SPELL_FIERY_BLAST_N                     = 32302,
    SPELL_FIERY_BLAST_H                     = 38382,
    SPELL_FOCUS_FIRE_VISUAL                 = 32286,
    SPELL_FOCUS_CAST                        = 32300,

    EVENT_SPELL_INHIBIT_MAGIC               = 1,
    EVENT_SPELL_ATTRACT_MAGIC,
    EVENT_SPELL_CARNIVOROUS,
    EVENT_SPELL_FOCUS_FIRE,
    EVENT_SPELL_FOCUS_FIRE_2,
    EVENT_SPELL_FOCUS_FIRE_3,

    ENTRY_FOCUS_FIRE                        = 18374,

    EMOTE_FOCUSED                           = 0,
};

struct boss_shirrak_the_dead_watcherAI : public ScriptedAI
{
    boss_shirrak_the_dead_watcherAI(Creature* creature) : ScriptedAI(creature) { }

    void EnterEvadeMode() override
    {
        me->SetControlled(false, UNIT_STATE_ROOT);
        ScriptedAI::EnterEvadeMode();
    }

    void Reset() override
    {
        me->DisableRotate(false);
        events.Reset();
        focusGUID = 0;
        me->SetControlled(false, UNIT_STATE_ROOT);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        events.ScheduleEvent(EVENT_SPELL_INHIBIT_MAGIC, 0);
        events.ScheduleEvent(EVENT_SPELL_ATTRACT_MAGIC, 28000);
        events.ScheduleEvent(EVENT_SPELL_CARNIVOROUS, 10000);
        events.ScheduleEvent(EVENT_SPELL_FOCUS_FIRE, 17000);
    }

    void JustSummoned(Creature* summon) override
    {
        summon->CastSpell(summon, SPELL_FOCUS_FIRE_VISUAL, true);
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spellInfo) override
    {
        if (spellInfo->Id == SPELL_FOCUS_CAST)
            target->CastSpell(target, DUNGEON_MODE(SPELL_FIERY_BLAST_N, SPELL_FIERY_BLAST_H), false);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SPELL_INHIBIT_MAGIC:
                    DoCastAOE(SPELL_INHIBIT_MAGIC);
                    events.Repeat(3000);
                    break;
                case EVENT_SPELL_ATTRACT_MAGIC:
                    DoCast(me, SPELL_ATTRACT_MAGIC);
                    events.Repeat(30000);
                    events.RescheduleEvent(EVENT_SPELL_CARNIVOROUS, 1500);
                    break;
                case EVENT_SPELL_CARNIVOROUS:
                    DoCast(me, DUNGEON_MODE(SPELL_CARNIVOROUS_BITE_N, SPELL_CARNIVOROUS_BITE_H));
                    events.Repeat(10000);
                    break;
                case EVENT_SPELL_FOCUS_FIRE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 60.0f, true))
                    {
                        if (Creature* cr = me->SummonCreature(ENTRY_FOCUS_FIRE, *target, TEMPSUMMON_TIMED_DESPAWN, 7000))
                            focusGUID = cr->GetGUID();
                        Talk(EMOTE_FOCUSED, target);
                        me->DisableRotate(true);
                    }
                    events.Repeat(urand(15000, 20000));
                    events.ScheduleEvent(EVENT_SPELL_FOCUS_FIRE_2, 3000);
                    events.ScheduleEvent(EVENT_SPELL_FOCUS_FIRE_2, 3500);
                    events.ScheduleEvent(EVENT_SPELL_FOCUS_FIRE_2, 4000);
                    events.ScheduleEvent(EVENT_SPELL_FOCUS_FIRE_3, 5000);
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    break;
                case EVENT_SPELL_FOCUS_FIRE_2:
                    if (Unit* flare = ObjectAccessor::GetCreature(*me, focusGUID))
                        DoCast(flare, SPELL_FOCUS_CAST, true);
                    break;
                case EVENT_SPELL_FOCUS_FIRE_3:
                    me->DisableRotate(false);
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap events;
    uint64 focusGUID;
};

class spell_auchenai_possess_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_auchenai_possess_AuraScript);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ 32830, 33401 });
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetTarget())
                caster->CastSpell(target, 32830 /*POSSESS*/, true);
    }

    void CalcPeriodic(AuraEffect const* /*effect*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = 2000;
    }

    void Update(AuraEffect* effect)
    {
        // Xinef: Charm is removed when target is at or below 50%hp
        if (Unit* owner = GetUnitOwner())
            if (owner->GetHealthPct() <= 50)
                SetDuration(0);
    }

    void Register() override
    {
        // Base channel
        if (m_scriptSpellId == 33401)
            OnEffectRemove += AuraEffectRemoveFn(spell_auchenai_possess_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        else
        {
            DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_auchenai_possess_AuraScript::CalcPeriodic, EFFECT_0, SPELL_AURA_MOD_CHARM);
            OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_auchenai_possess_AuraScript::Update, EFFECT_0, SPELL_AURA_MOD_CHARM);
        }
    }
};

class spell_inhibit_magic_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_inhibit_magic_SpellScript);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_INHIBIT_MAGIC });
    }

    uint8 getMaxAmount(float dist)
    {
        if (dist < 15.f)
            return 4;
        if (dist < 25.f)
            return 3;
        if (dist < 35.f)
            return 2;
        return 1;
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([&](WorldObject* target) -> bool
        {
            return !target->IsPlayer() || GetCaster()->GetDistance(*target) > 45.f;
        });
    }

    void HandleApplyAura(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
        {
            Aura* aura = GetHitAura();
            float dist = GetCaster()->GetDistance(*target);
            uint8 maxAmount = getMaxAmount(dist);
            if (aura->GetStackAmount() >= maxAmount)
            {
                aura->RefreshDuration();
                aura->ModStackAmount(aura->GetStackAmount() - 1);
            }
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_inhibit_magic_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnEffectHitTarget += SpellEffectFn(spell_inhibit_magic_SpellScript::HandleApplyAura, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};


void AddSC_boss_shirrak_the_dead_watcher()
{
    new CreatureAILoader<boss_shirrak_the_dead_watcherAI>("boss_shirrak_the_dead_watcher");
    new AuraScriptLoaderEx<spell_auchenai_possess_AuraScript>("spell_auchenai_possess");
    new SpellScriptLoaderEx<spell_inhibit_magic_SpellScript>("spell_inhibit_magic");
}
