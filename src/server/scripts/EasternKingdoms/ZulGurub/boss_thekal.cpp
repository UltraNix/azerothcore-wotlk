#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "zulgurub.h"
#include "Spell.h"

enum Says
{
    // High Priest Thekal
    SAY_TRANSFORM           = 0, //Shirvallah, fill me with your RAGE!
    SAY_DEATH_P2            = 1, //Hakkar binds me no more! Peace at last!
    EMOTE_DEATH_THEKAL_P1   = 2, //High Priest Thekal dies.

    // Zealot Lor'Khan
    EMOTE_DEATH_LORKHAN_P1  = 0, //Zealot Lor'Khan dies.

    // Zealot Zath
    EMOTE_DEATH_ZATH_P1     = 0  //Zealot Zath dies.
};

enum Spells
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

enum Events
{
    // High Priest Thekal
    EVENT_MORTALCLEAVE      = 1,
    EVENT_SILENCE,
    EVENT_CHECK_TIMER,
    EVENT_TIGER_FORM,
    EVENT_ENRAGE,
    EVENT_FORCEPUNCH,
    EVENT_SPELL_CHARGE,
    EVENT_SUMMONTIGERS,
    EVENT_DEATH_TIMER,
    EVENT_TRANSFORM,
    EVENT_CHARGE_THEKAL,
    // Zealot Lor'Khan
    EVENT_SHIELD            = 1,
    EVENT_BLOODLUST,
    EVENT_GREATER_HEAL,
    EVENT_DISARM,
    EVENT_CHECK_TIMER_LORKHAN,
    // Zealot Zath
    EVENT_SWEEPING_STRIKES  = 1,
    EVENT_SINISTER_STRIKE,
    EVENT_GOUGE,
    EVENT_KICK,
    EVENT_BLIND,
    EVENT_CHECK_TIMER_ZATH
};

enum Phases
{
    PHASE_ONE               = 1,
    PHASE_TWO
};

enum Actions
{
    // Zealot Lor'Khan
    ACTION_P2_LORKHAN       = 1,
    ACTION_DESPAWN_LORKHAN,

    // Zealot Zath 
    ACTION_P2_ZATH          = 1,
    ACTION_DESPAWN_ZATH
};

struct boss_thekalAI : public BossAI
{
    boss_thekalAI(Creature* creature) : BossAI(creature, DATA_THEKAL) { }

    void Reset() override
    {
        //load weapon, its removed when phase 2 transform occurs
        me->LoadEquipment(me->GetOriginalEquipmentId(), true);
        _Reset();
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
        me->SetReactState(REACT_AGGRESSIVE);
        _died = false;
        _enraged = false;
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        Schedule();
        events.SetPhase(PHASE_ONE);
    }

    void Schedule()
    {
        events.ScheduleEvent(EVENT_MORTALCLEAVE, 4000, 0, PHASE_ONE);
        events.ScheduleEvent(EVENT_SILENCE, 9000, 0, PHASE_ONE);
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH_P2);
        if (Unit* lorkhan = ObjectAccessor::GetUnit(*me, instance->GetData64(DATA_LORKHAN)))
            lorkhan->GetAI()->DoAction(ACTION_DESPAWN_LORKHAN);
        if (Unit* zath = ObjectAccessor::GetUnit(*me, instance->GetData64(DATA_ZATH)))
            zath->GetAI()->DoAction(ACTION_DESPAWN_ZATH);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageeffecttype*/, SpellSchoolMask /*spellschoolmask*/) override
    {
        //prevent killing before phase 2
        if (damage > me->GetHealth() && events.IsInPhase(PHASE_ONE))
            damage = me->GetHealth() - 1;

        if (events.IsInPhase(PHASE_TWO) && HealthBelowPct(11) && !_enraged)
        {
            _enraged = true;
            events.ScheduleEvent(EVENT_ENRAGE, 0, 0, PHASE_TWO);
        }

        if ((events.IsInPhase(PHASE_ONE)) && !HealthAbovePct(5) && !_died)
        {
            _died = true;
            Talk(EMOTE_DEATH_THEKAL_P1);
            me->RemoveAllAuras();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->AttackStop();
            me->SetReactState(REACT_PASSIVE);
            instance->SetBossState(DATA_THEKAL, SPECIAL);
            events.ScheduleEvent(EVENT_CHECK_TIMER, 10000);
        }
    }

    void SpellHitTarget(Unit* /*target*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_RESURRECT)
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->SetFullHealth();
            DoCast(me, SPELL_RESURRECT_VISUAL);
            _died = false;
            me->SetReactState(REACT_AGGRESSIVE);
            instance->SetBossState(DATA_THEKAL, IN_PROGRESS);
            Schedule();
        }
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
                case EVENT_MORTALCLEAVE:
                    DoCastVictim(SPELL_MORTALCLEAVE);
                    events.Repeat(urand(15000, 20000));
                    break;
                case EVENT_SILENCE:
                    DoCastVictim(SPELL_SILENCE);
                    events.Repeat(urand(20000, 25000));
                    break;
                case EVENT_FORCEPUNCH:
                    DoCastVictim(SPELL_FORCEPUNCH);
                    events.Repeat(urand(16000, 21000));
                    break;
                case EVENT_CHARGE_THEKAL:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                    {
                        DoCast(target, SPELL_CHARGE);
                        DoResetThreat();
                        AttackStart(target);
                    }
                    events.Repeat(urand(15000, 22000));
                    break;
                case EVENT_ENRAGE:
                    DoCast(me, SPELL_ENRAGE);
                    events.Repeat(30000);
                    break;
                case EVENT_SUMMONTIGERS:
                    DoCastVictim(SPELL_SUMMONTIGERS);
                    events.Repeat(urand(10000, 14000));
                    break;
                case EVENT_CHECK_TIMER:
                    DoCast(me, SPELL_RESURRECT, true);
                    break;
                case EVENT_TRANSFORM:
                    //cancel the event, otherwise thekal will cast resurrect after 10 seconds anyways 
                    events.CancelEvent(EVENT_CHECK_TIMER);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->SetFullHealth();
                    _died = false;
                    me->SetReactState(REACT_AGGRESSIVE);
                    DoCast(me, SPELL_TIGER_FORM, true);
                    //thekal shouldn't have weapon now
                    me->LoadEquipment(0, true);
                    DoResetThreat();
                    events.ScheduleEvent(EVENT_FORCEPUNCH, 4000, 2, PHASE_TWO);
                    events.ScheduleEvent(EVENT_SPELL_CHARGE, 12000, 2, PHASE_TWO);
                    events.ScheduleEvent(EVENT_SUMMONTIGERS, 25000, 2, PHASE_TWO);
                    if (Unit* lorkhan = ObjectAccessor::GetUnit(*me, instance->GetData64(DATA_LORKHAN)))
                        lorkhan->GetAI()->DoAction(ACTION_P2_LORKHAN);
                    if (Unit* zath = ObjectAccessor::GetUnit(*me, instance->GetData64(DATA_ZATH)))
                        zath->GetAI()->DoAction(ACTION_P2_ZATH);
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        if (instance->GetBossState(DATA_LORKHAN) == SPECIAL && instance->GetBossState(DATA_ZATH) == SPECIAL && instance->GetBossState(DATA_THEKAL) == SPECIAL && events.IsInPhase(PHASE_ONE))
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            //override the animation
            me->SetStandState(UNIT_STAND_STATE_STAND);
            events.SetPhase(PHASE_TWO);
            Talk(SAY_TRANSFORM);
            //transform should be slightly delayed
            events.ScheduleEvent(EVENT_TRANSFORM, 2000);
        }

        DoMeleeAttackIfReady();
    }

private:
    bool _died;
    bool _enraged;
};

struct npc_zealot_lorkhanAI : public BossAI
{
    npc_zealot_lorkhanAI(Creature* creature) : BossAI(creature, DATA_LORKHAN) { }

    void Reset() override
    {
        _Reset();
        _died = false;
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
        me->SetReactState(REACT_AGGRESSIVE);
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_P2_LORKHAN)
            events.CancelEvent(EVENT_CHECK_TIMER_LORKHAN);
        if (actionId == ACTION_DESPAWN_LORKHAN)
            me->DespawnOrUnsummon(1);
    }

    void EnterCombat(Unit* who) override
    {
        _EnterCombat();
        Schedule();
    }

    void Schedule()
    {
        events.ScheduleEvent(EVENT_SHIELD, 1000, 1);
        events.ScheduleEvent(EVENT_BLOODLUST, 16000, 1);
        events.ScheduleEvent(EVENT_GREATER_HEAL, 32000, 1);
        events.ScheduleEvent(EVENT_DISARM, 6000, 1);
    }

    void SpellHitTarget(Unit* /*target*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_RESURRECT)
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->SetFullHealth();
            _died = false;
            me->SetReactState(REACT_AGGRESSIVE);
            instance->SetBossState(DATA_LORKHAN, IN_PROGRESS);
            Schedule();
        }
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
    {
        //should be handled by thekal death
        if (damage > me->GetHealth())
            damage = me->GetHealth() - 1;

        if (!HealthAbovePct(5) && !_died)
        {
            _died = true;
            Talk(EMOTE_DEATH_LORKHAN_P1);
            me->InterruptNonMeleeSpells(false);
            events.CancelEventGroup(1);
            me->SetReactState(REACT_PASSIVE);
            me->RemoveAllAuras();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->AttackStop();
            instance->SetBossState(DATA_LORKHAN, SPECIAL);
            events.ScheduleEvent(EVENT_CHECK_TIMER_LORKHAN, 10000);
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_SHIELD:
                DoCast(me, SPELL_SHIELD);
                events.Repeat(61000);
                break;
            case EVENT_BLOODLUST:
                DoCast(me, SPELL_BLOODLUST);
                events.Repeat(urand(20000, 28000));
                break;
            case EVENT_GREATER_HEAL:
                if (Unit* target = DoSelectLowestHpFriendly(15.0f, 1))
                    DoCast(target, SPELL_GREATERHEAL);
                events.Repeat(urand(15000, 20000));
                break;
            case EVENT_DISARM:
                DoCastVictim(SPELL_DISARM);
                events.Repeat(urand(15000, 25000));
                break;
            case EVENT_CHECK_TIMER_LORKHAN:
                DoCast(me, SPELL_RESURRECT, true);
                break;
            default:
                break;
        }
    }

private:
    bool _died;
};

struct npc_zealot_zathAI : public BossAI
{
    npc_zealot_zathAI(Creature* creature) : BossAI(creature, DATA_ZATH) { }

    void Reset() override
    {
        _Reset();
        _died = false;
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
        me->SetReactState(REACT_AGGRESSIVE);
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_P2_ZATH)
            events.CancelEvent(EVENT_CHECK_TIMER_ZATH);
        if (actionId == ACTION_DESPAWN_ZATH)
            me->DespawnOrUnsummon(1);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        Schedule();
    }

    void SpellHitTarget(Unit* /*target*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_RESURRECT)
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->SetFullHealth();
            _died = false;
            me->SetReactState(REACT_AGGRESSIVE);
            instance->SetBossState(DATA_ZATH, IN_PROGRESS);
            Schedule();
        }
    }

    void Schedule()
    {
        events.ScheduleEvent(EVENT_SWEEPING_STRIKES, 13000, 1);
        events.ScheduleEvent(EVENT_SINISTER_STRIKE, 8000, 1);
        events.ScheduleEvent(EVENT_GOUGE, 25000, 1);
        events.ScheduleEvent(EVENT_KICK, 18000, 1);
        events.ScheduleEvent(EVENT_BLIND, 5000, 1);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageeffecttype*/, SpellSchoolMask /*spellschoolmask*/) override
    {
        //should be handled by thekal death
        if (damage > me->GetHealth())
            damage = me->GetHealth() - 1;

        if (!HealthAbovePct(5) && !_died)
        {
            _died = true;
            Talk(EMOTE_DEATH_ZATH_P1);
            events.CancelEventGroup(1);
            me->SetReactState(REACT_PASSIVE);
            me->RemoveAllAuras();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->AttackStop();
            instance->SetBossState(DATA_ZATH, SPECIAL);
            events.ScheduleEvent(EVENT_CHECK_TIMER_ZATH, 10000);
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_SWEEPING_STRIKES:
                DoCastVictim(SPELL_SWEEPINGSTRIKES);
                events.Repeat(urand(22000, 26000));
                break;
            case EVENT_SINISTER_STRIKE:
                DoCastVictim(SPELL_SINISTERSTRIKE);
                events.Repeat(urand(8000, 16000));
                break;
            case EVENT_GOUGE:
                DoCastVictim(SPELL_GOUGE);
                if (DoGetThreat(me->GetVictim()))
                    DoModifyThreatPercent(me->GetVictim(), -100);
                events.Repeat(urand(17000, 27000));
                break;
            case EVENT_KICK:
                DoCastVictim(SPELL_KICK);
                events.Repeat(urand(15000, 25000));
                break;
            case EVENT_BLIND:
                DoCastVictim(SPELL_BLIND);
                events.Repeat(urand(10000, 20000));
                break;
            case EVENT_CHECK_TIMER_ZATH:
                DoCast(me, SPELL_RESURRECT, true);
                break;
            default:
                break;
        }
    }

private:
    bool _died;
};

// 24169 - Tiger Form 
class spell_thekal_tiger_form_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_thekal_tiger_form_AuraScript);

    bool Validate(SpellInfo const* /* spellEntry */) override
    {
        return ValidateSpellInfo({ SPELL_TIGER_FORM });
    }

    void OnApply(AuraEffect const* /* auraEffect */, AuraEffectHandleModes /* handleModes */)
    {
        GetCaster()->HandleStatModifier(UNIT_MOD_DAMAGE_MAINHAND, TOTAL_PCT, 40.0f, true); // hack
    }

    void OnRemove(AuraEffect const* /* auraEffect */, AuraEffectHandleModes /* handleModes */)
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