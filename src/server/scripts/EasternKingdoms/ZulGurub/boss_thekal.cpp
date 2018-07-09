#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "zulgurub.h"
#include "Spell.h"

enum ThekalSays
{
    EMOTE_DEATH,                // %s dies.
    SAY_TRANSFORM,              // Shirvallah, fill me with your RAGE!
    SAY_DEATH_P2                // Hakkar binds me no more! Peace at last!
};

enum ThekalSpells
{
    // High Priest Thekal
    SPELL_MORTALCLEAVE      = 22859,
    SPELL_SILENCE           = 22666,
    SPELL_TIGER_FORM        = 24169,
    SPELL_RESURRECT         = 24173,
    SPELL_RESURRECT_VISUAL  = 24171,
    SPELL_FORCEPUNCH        = 24189,
    SPELL_CHARGE            = 24193,
    SPELL_ENRAGE            = 8269,
    SPELL_SUMMONTIGERS      = 24183,
    // Zealot Lor'Khan
    SPELL_SHIELD            = 20545,
    SPELL_BLOODLUST         = 24185,
    SPELL_GREATERHEAL       = 24208,
    SPELL_DISARM            = 6713,
    // Zealot Zath
    SPELL_SWEEPINGSTRIKES   = 18765,
    SPELL_SINISTERSTRIKE    = 15581,
    SPELL_GOUGE             = 12540,
    SPELL_KICK              = 15614,
    SPELL_BLIND             = 21060
};

enum ThekalEvents
{
    // High Priest Thekal
    EVENT_MORTALCLEAVE      = 1,
    EVENT_SILENCE,
    EVENT_TIGER_FORM,
    EVENT_ENRAGE,
    EVENT_FORCEPUNCH,
    EVENT_SUMMONTIGERS,
    EVENT_TRANSFORM,
    EVENT_CHARGE_THEKAL,
    // Zealot Lor'Khan
    EVENT_SHIELD,
    EVENT_BLOODLUST,
    EVENT_GREATER_HEAL,
    EVENT_DISARM,
    // Zealot Zath
    EVENT_SWEEPING_STRIKES,
    EVENT_SINISTER_STRIKE,
    EVENT_GOUGE,
    EVENT_KICK,
    EVENT_BLIND,

    // Shared
    EVENT_CHECK_TIMER
};

enum ThekalPhases
{
    PHASE_ONE               = 1,
    PHASE_TWO
};

enum ThekalActions
{
    ACTION_SET_PHASE_2      = 1
};

struct boss_thekal_baseAI : public BossAI
{
    boss_thekal_baseAI(Creature* creature, uint32 bossId) : BossAI(creature, bossId) { }

    void Reset() override
    {
        _Reset();
        SetFeignDeath(false);
        _died = false;
    }

    void SetFeignDeath(bool apply)
    {
        if (apply)
        {
            Talk(EMOTE_DEATH);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->SetReactState(REACT_PASSIVE);
            me->AttackStop();
            events.Reset();
        }
        else
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->SetReactState(REACT_AGGRESSIVE);
        }
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_SET_PHASE_2)
            events.Reset();
    }

    virtual void ScheduleCombatEvents() = 0;

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        ScheduleCombatEvents();
    }

    void SpellHitTarget(Unit* /*target*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_RESURRECT)
        {
            SetFeignDeath(false);
            me->SetFullHealth();
            DoCastSelf(SPELL_RESURRECT_VISUAL, true);
            _died = false;
        }
    }

    bool CheckAllDead() const
    {
        for (uint32 const data : { DATA_THEKAL, DATA_LORKHAN, DATA_ZATH })
            if (Creature* creature = ObjectAccessor::GetCreature(*me, instance->GetData64(data)))
                if (!creature->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH))
                    return false;

        return true;
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageEffectType*/, SpellSchoolMask /*mask*/) override
    {
        if (damage > me->GetHealth() && !events.IsInPhase(PHASE_TWO))
        {
            damage = me->GetHealth() - 1;
            if (!_died)
            {
                SetFeignDeath(true);
                events.ScheduleEvent(EVENT_CHECK_TIMER, 10s);
                _died = true;
            }

            if (CheckAllDead())
                for (uint32 const data : { DATA_THEKAL, DATA_LORKHAN, DATA_ZATH })
                    if (Creature* creature = ObjectAccessor::GetCreature(*me, instance->GetData64(data)))
                        if (creature->IsAIEnabled)
                            creature->AI()->DoAction(ACTION_SET_PHASE_2);
        }
    }

    protected:
        bool _died;
};

struct boss_thekalAI : public boss_thekal_baseAI
{
    boss_thekalAI(Creature* creature) : boss_thekal_baseAI(creature, DATA_THEKAL) { }

    void Reset() override
    {
        boss_thekal_baseAI::Reset();
        me->LoadEquipment(me->GetOriginalEquipmentId(), true);
        _enraged = false;
    }

    void ScheduleCombatEvents() override
    {
        events.SetPhase(PHASE_ONE);
        events.ScheduleEvent(EVENT_MORTALCLEAVE, 4s, 0, PHASE_ONE);
        events.ScheduleEvent(EVENT_SILENCE, 9s, 0, PHASE_ONE);
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_SET_PHASE_2)
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            Talk(SAY_TRANSFORM);
            events.Reset();
            events.ScheduleEvent(EVENT_TRANSFORM, 2s);
        }
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType damageEffectType, SpellSchoolMask mask) override
    {
        boss_thekal_baseAI::DamageTaken(attacker, damage, damageEffectType, mask);
        if (me->HealthBelowPctDamaged(10, damage) && !_enraged && events.IsInPhase(PHASE_TWO))
        {
            _enraged = true;
            DoCastSelf(SPELL_ENRAGE, true);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        for (uint32 const data : { DATA_LORKHAN, DATA_ZATH })
            if (Creature* creature = ObjectAccessor::GetCreature(*me, instance->GetData64(data)))
            {
                creature->Kill(creature, creature, false);
                creature->SetSelectable(true);
            }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_MORTALCLEAVE:
                DoCastVictim(SPELL_MORTALCLEAVE);
                events.Repeat(15s, 20s);
                break;
            case EVENT_SILENCE:
                DoCastVictim(SPELL_SILENCE);
                events.Repeat(20s, 25s);
                break;
            case EVENT_FORCEPUNCH:
                DoCastVictim(SPELL_FORCEPUNCH);
                events.Repeat(16s, 21s);
                break;
            case EVENT_CHARGE_THEKAL:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                {
                    DoCast(target, SPELL_CHARGE);
                    DoResetThreat();
                    AttackStart(target);
                }
                events.Repeat(15s, 22s);
                break;
            case EVENT_ENRAGE:
                DoCastSelf(SPELL_ENRAGE);
                events.Repeat(30s);
                break;
            case EVENT_SUMMONTIGERS:
                DoCastSelf(SPELL_SUMMONTIGERS);
                events.Repeat(10s, 14s);
                break;
            case EVENT_TRANSFORM:
                _died = false;
                DoCastSelf(SPELL_TIGER_FORM);
                me->LoadEquipment(0, true);
                DoResetThreat();
                SetFeignDeath(false);
                events.SetPhase(PHASE_TWO);
                events.ScheduleEvent(EVENT_FORCEPUNCH, 4s, 0, PHASE_TWO);
                events.ScheduleEvent(EVENT_CHARGE_THEKAL, 12s, 0, PHASE_TWO);
                events.ScheduleEvent(EVENT_SUMMONTIGERS, 25s, 0, PHASE_TWO);
                break;
            case EVENT_CHECK_TIMER:
                if (!CheckAllDead())
                {
                    DoCastSelf(SPELL_RESURRECT, true);
                    ScheduleCombatEvents();
                }
                break;
            default:
                break;
        }
    }

    private:
        bool _enraged;
};

struct npc_zealot_lorkhanAI : public boss_thekal_baseAI
{
    npc_zealot_lorkhanAI(Creature* creature) : boss_thekal_baseAI(creature, DATA_LORKHAN) { }

    void ScheduleCombatEvents() override
    {
        events.ScheduleEvent(EVENT_SHIELD, 1s);
        events.ScheduleEvent(EVENT_BLOODLUST, 16s);
        events.ScheduleEvent(EVENT_GREATER_HEAL, 32s);
        events.ScheduleEvent(EVENT_DISARM, 6s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_SHIELD:
                DoCastSelf(SPELL_SHIELD);
                events.Repeat(1min);
                break;
            case EVENT_BLOODLUST:
                DoCastSelf(SPELL_BLOODLUST);
                events.Repeat(20s, 28s);
                break;
            case EVENT_GREATER_HEAL:
                if (Unit* target = DoSelectLowestHpFriendly(30.0f, 1000))
                    DoCast(target, SPELL_GREATERHEAL);
                events.Repeat(15s, 20s);
                break;
            case EVENT_DISARM:
                DoCastVictim(SPELL_DISARM);
                events.Repeat(15s, 25s);
                break;
            case EVENT_CHECK_TIMER:
                if (!CheckAllDead())
                {
                    DoCastSelf(SPELL_RESURRECT, true);
                    ScheduleCombatEvents();
                }
                break;
            default:
                break;
        }
    }
};

struct npc_zealot_zathAI : public boss_thekal_baseAI
{
    npc_zealot_zathAI(Creature* creature) : boss_thekal_baseAI(creature, DATA_ZATH) { }

    void ScheduleCombatEvents() override
    {
        events.ScheduleEvent(EVENT_SWEEPING_STRIKES, 13s);
        events.ScheduleEvent(EVENT_SINISTER_STRIKE, 8s);
        events.ScheduleEvent(EVENT_GOUGE, 25s);
        events.ScheduleEvent(EVENT_KICK, 18s);
        events.ScheduleEvent(EVENT_BLIND, 5s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CHECK_TIMER:
                if (!CheckAllDead())
                {
                    DoCastSelf(SPELL_RESURRECT, true);
                    ScheduleCombatEvents();
                }
                break;
            case EVENT_SWEEPING_STRIKES:
                DoCastVictim(SPELL_SWEEPINGSTRIKES);
                events.Repeat(22s, 26s);
                break;
            case EVENT_SINISTER_STRIKE:
                DoCastVictim(SPELL_SINISTERSTRIKE);
                events.Repeat(8s, 16s);
                break;
            case EVENT_GOUGE:
                if (Unit* victim = me->GetVictim())
                {
                    DoCast(victim, SPELL_GOUGE);
                    if (DoGetThreat(victim))
                        DoModifyThreatPercent(victim, -100);
                }
                events.Repeat(17s, 27s);
                break;
            case EVENT_KICK:
                DoCastVictim(SPELL_KICK);
                events.Repeat(15s, 25s);
                break;
            case EVENT_BLIND:
                DoCastVictim(SPELL_BLIND);
                events.Repeat(10s, 20s);
                break;
            default:
                break;
        }
    }
};

// 24169 - Tiger Form
class spell_thekal_tiger_form_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_thekal_tiger_form_AuraScript);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo({ SPELL_TIGER_FORM });
    }

    void OnApply(AuraEffect const* /*auraEffect*/, AuraEffectHandleModes /*handleModes*/)
    {
        GetCaster()->HandleStatModifier(UNIT_MOD_DAMAGE_MAINHAND, TOTAL_PCT, 40.0f, true); // hack
    }

    void OnRemove(AuraEffect const* /*auraEffect*/, AuraEffectHandleModes /*handleModes*/)
    {
        GetCaster()->HandleStatModifier(UNIT_MOD_DAMAGE_MAINHAND, TOTAL_PCT, 100.0f, true); // hack
    }

    void Register()
    {
        AfterEffectApply += AuraEffectApplyFn(spell_thekal_tiger_form_AuraScript::OnApply, EFFECT_0, SPELL_AURA_TRANSFORM, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        AfterEffectRemove += AuraEffectRemoveFn(spell_thekal_tiger_form_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_TRANSFORM, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

void AddSC_boss_thekal()
{
    new CreatureAILoader<boss_thekalAI>("boss_thekal");
    new CreatureAILoader<npc_zealot_lorkhanAI>("npc_zealot_lorkhan");
    new CreatureAILoader<npc_zealot_zathAI>("npc_zealot_zath");
    new AuraScriptLoaderEx<spell_thekal_tiger_form_AuraScript>("spell_thekal_tiger_form");
}