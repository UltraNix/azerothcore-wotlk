#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ahnkahet.h"
#include "SpellScript.h"

enum AhnkahetSpells
{
    // Deep Crawler
    SPELL_COMBINED_TOXINS       = 56583,
    SPELL_GLUTINOUS_POISON      = 56580,
    SPELL_FATAL_STING           = 56581,

    // Ahn'kahar Spell Flinger
    SPELL_SHADOW_BLAST          = 56698,
    SPELL_SHADOW_SICKLE         = 56702,
    SPELL_SHADOW_SICKLE_DMG     = 56701,

    // Ahn'kahar Slasher
    SPELL_CLEAVE                = 42746,
    SPELL_TRIPLE_SLASH          = 56643,
    SPELL_TRIPLE_SLASH_DMG      = 56645,
    SPELL_ENRAGE                = 56646,

    // Plundering Geist
    SPELL_PLUNDER_HEALTH        = 56715,

    // Eye of Taldaram
    SPELL_SHADOW_SHOCK          = 17439,
    SPELL_DARK_COUNTERSPELL     = 56730,
    SPELL_EYES_IN_THE_DARK      = 56728,
    SPELL_SHADOWFURY            = 56733,

    // Bonegrinder
    SPELL_TRAMPLE               = 56736,
    SPELL_STOMP                 = 56737,
    SPELL_FRIGTHENING_SHOUT     = 29544,
    SPELL_ENRAGE_2              = 8599,

    // Frostbringer
    SPELL_FROSTBOLT             = 57825,
    SPELL_FROST_NOVA            = 15063,
    SPELL_ICY_WINDS             = 56716,

    // Twilight Apostle
    SPELL_LIGHTNING_SHIELD      = 12550,
    SPELL_HEALING_WAVE          = 11986,
    SPELL_BLOODLUST             = 28902,

    // Twilight Darkcaster
    SPELL_SHADOW_BOLT           = 12739,
    SPELL_CURSE_OF_TONGUES      = 13338,
    SPELL_CORRUPTION            = 56898,

    // Forgotten One
    SPELL_SHADOW_NOVA           = 60845,
    SPELL_SHADOW_CRASH          = 60833,
    SPELL_PSYCHIC_SCREAM        = 34322
};

struct npc_deep_crawlerAI : public ScriptedAI
{
    npc_deep_crawlerAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _scheduler.CancelAll();
        DoCastSelf(SPELL_COMBINED_TOXINS, true);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(4s, 7s, [this](TaskContext task) {
            DoCastSelf(SPELL_GLUTINOUS_POISON);
            task.Repeat(9s, 12s);
        });
        _scheduler.Schedule(1s, [this](TaskContext task) {
            if (me->GetVictim() && me->GetVictim()->HasAuraState(AURA_STATE_HEALTHLESS_20_PERCENT))
            {
                DoCastVictim(SPELL_FATAL_STING);
                task.Repeat(14s, 17s);
                return;
            }

            task.Repeat(1s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
};

struct npc_ahnkahar_spell_flingerAI : public ScriptedAI
{
    npc_ahnkahar_spell_flingerAI(Creature* creature) : ScriptedAI(creature)
    {
        _scheduler.SetValidator([this] { return !me->HasUnitState(UNIT_STATE_CASTING); });
    }

    void Reset() override
    {
        _scheduler.CancelAll();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(10s, 14s, [this](TaskContext task) {
            DoCastSelf(SPELL_SHADOW_SICKLE);
            task.Repeat(13s, 16s);
        });
        _scheduler.Schedule(0s, [this](TaskContext task) {
            DoCastVictim(SPELL_SHADOW_BLAST);
            task.Repeat(23s, 27s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
};

// 56702, 59103 - Shadow Sickle
class spell_shadow_sickle_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_shadow_sickle_AuraScript);

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        PreventDefaultAction();
        if (GetCaster())
            if (Creature* caster = GetCaster()->ToCreature())
            {
                if (caster->IsAIEnabled)
                    if (Unit* target = caster->AI()->SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        caster->AI()->DoCast(target, SPELL_SHADOW_SICKLE_DMG, true);
            }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_shadow_sickle_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

// 56698, 59102 - Shadow Blast
class spell_shadow_blast_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_shadow_blast_SpellScript);

    void CalculateDamage()
    {
        if (Unit* target = GetHitUnit())
            SetHitDamage(target->CountPctFromMaxHealth(GetSpellInfo()->Effects[EFFECT_0].BasePoints));
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_shadow_blast_SpellScript::CalculateDamage);
    }
};

struct npc_ahnkahar_slasherAI : public ScriptedAI
{
    npc_ahnkahar_slasherAI(Creature* creature) : ScriptedAI(creature)
    {
        _scheduler.SetValidator([this] { return !me->HasUnitState(UNIT_STATE_CASTING); });
    }

    void Reset() override
    {
        _scheduler.CancelAll();
        _enraged = false;
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(4s, 7s, [this](TaskContext task) {
            DoCastVictim(SPELL_CLEAVE);
            task.Repeat(14s, 17s);
        });
        _scheduler.Schedule(9s, 12s, [this](TaskContext task) {
            DoCastSelf(SPELL_TRIPLE_SLASH);
            task.Repeat(15s, 18s);
        });
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*schoolMask*/) override
    {
        if (!_enraged && me->HealthBelowPctDamaged(30, damage))
        {
            _enraged = true;
            DoCastSelf(SPELL_ENRAGE, true);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
        bool _enraged;
};

// 56643 - Triple Slash
class spell_triple_slash_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_triple_slash_AuraScript);

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        PreventDefaultAction();
        if (GetCaster() && GetCaster()->GetVictim())
            GetCaster()->CastSpell(GetCaster()->GetVictim(), SPELL_TRIPLE_SLASH_DMG, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_triple_slash_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

struct npc_plundering_geistAI : public ScriptedAI
{
    npc_plundering_geistAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _scheduler.CancelAll();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(1s, [this](TaskContext task) {
            if (me->GetMaxHealth() > me->GetHealth() + DUNGEON_MODE(500, 1000) && me->GetVictim() && me->IsWithinMeleeRange(me->GetVictim()))
            {
                DoCastVictim(SPELL_PLUNDER_HEALTH);
                task.Repeat(8s, 10s);
                return;
            }

            task.Repeat(1s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
};

struct npc_eye_of_taldaramAI : public ScriptedAI
{
    npc_eye_of_taldaramAI(Creature* creature) : ScriptedAI(creature)
    {
        _scheduler.SetValidator([this] { return !me->HasUnitState(UNIT_STATE_CASTING); });
    }

    void Reset() override
    {
        _scheduler.CancelAll();
    }

    void JustDied(Unit* /*killer*/) override
    {
        DoCastSelf(SPELL_SHADOWFURY, true);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(0s, [this](TaskContext task) {
            DoCastVictim(SPELL_SHADOW_SHOCK);
            task.Repeat(3.4s, 4.8s);
        });
        _scheduler.Schedule(0s, [this](TaskContext task) {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, [this](Unit* tar) { return tar->HasAura(SPELL_EYES_IN_THE_DARK) && tar->HasUnitState(UNIT_STATE_CASTING); }))
            {
                DoCast(target, SPELL_DARK_COUNTERSPELL);
                task.Repeat(6s);
                return;
            }

            task.Repeat(1s);
        });
        _scheduler.Schedule(15s, 19s, [this](TaskContext task) {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true, -SPELL_EYES_IN_THE_DARK))
                DoCast(target, SPELL_EYES_IN_THE_DARK);
            task.Repeat(3.4s, 4.8s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
};

struct npc_bonegrinderAI : public ScriptedAI
{
    npc_bonegrinderAI(Creature* creature) : ScriptedAI(creature)
    {
        _scheduler.SetValidator([this] { return !me->HasUnitState(UNIT_STATE_CASTING); });
    }

    void Reset() override
    {
        _enrage = false;
        _scheduler.CancelAll();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(20s, 23s, [this](TaskContext task) {
            DoCastVictim(SPELL_FRIGTHENING_SHOUT);
            task.Repeat(24s, 27s);
        });
        _scheduler.Schedule(4s, 7s, [this](TaskContext task) {
            DoCastSelf(SPELL_TRAMPLE);
            task.Repeat(18s, 22s);
        });
        _scheduler.Schedule(11s, 14s, [this](TaskContext task) {
            DoCastAOE(SPELL_STOMP);
            task.Repeat(22s, 25s);
        });
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*schoolMask*/) override
    {
        if (!_enrage && me->HealthBelowPctDamaged(30, damage))
        {
            _enrage = true;
            DoCastSelf(SPELL_ENRAGE_2, true);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
        bool _enrage;
};

struct npc_frostbringerAI : public ScriptedAI
{
    npc_frostbringerAI(Creature* creature) : ScriptedAI(creature)
    {
        _scheduler.SetValidator([this] { return !me->HasUnitState(UNIT_STATE_CASTING); });
    }

    void Reset() override
    {
        _winds = false;
        _scheduler.CancelAll();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(0s, [this](TaskContext task) {
            DoCastVictim(SPELL_FROSTBOLT);
            task.Repeat(3.4s, 4.8s);
        });
        _scheduler.Schedule(9s, 12s, [this](TaskContext task) {
            DoCastSelf(SPELL_FROST_NOVA);
            task.Repeat(15s, 18s);
        });
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*schoolMask*/) override
    {
        if (!_winds && me->HealthBelowPctDamaged(50, damage))
        {
            _winds = true;
            DoCastSelf(SPELL_ICY_WINDS, true);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
        bool _winds;
};

struct npc_twilight_apostleAI : public ScriptedAI
{
    npc_twilight_apostleAI(Creature* creature) : ScriptedAI(creature)
    {
        _scheduler.SetValidator([this] { return !me->HasUnitState(UNIT_STATE_CASTING); });
    }

    void Reset() override
    {
        _bloodlust = false;
        _scheduler.CancelAll();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(0s, [this](TaskContext task) {
            DoCastSelf(SPELL_LIGHTNING_SHIELD);
            task.Repeat(10min);
        });

        _scheduler.Schedule(1s, [this](TaskContext task) {
            if (Unit* target = DoSelectLowestHpFriendly(40.0f, 10000))
            {
                DoCast(target, SPELL_HEALING_WAVE);
                task.Repeat(14s, 17s);
                return;
            }

            task.Repeat(1s);
        });
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*schoolMask*/) override
    {
        if (!_bloodlust && me->HealthBelowPctDamaged(30, damage))
        {
            _bloodlust = true;
            DoCastAOE(SPELL_BLOODLUST, true);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
        bool _bloodlust;
};

struct npc_twilight_darkcasterAI : public ScriptedAI
{
    npc_twilight_darkcasterAI(Creature* creature) : ScriptedAI(creature)
    {
        _scheduler.SetValidator([this] { return !me->HasUnitState(UNIT_STATE_CASTING); });
    }

    void Reset() override
    {
        _scheduler.CancelAll();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(0s, [this](TaskContext task) {
            DoCastVictim(SPELL_SHADOW_BOLT);
            task.Repeat(4s, 5s);
        });
        _scheduler.Schedule(12s, 15s, [this](TaskContext task) {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true, -SPELL_CURSE_OF_TONGUES))
                DoCast(target, SPELL_CURSE_OF_TONGUES);
            task.Repeat(19s, 23s);
        });
        _scheduler.Schedule(4s, 7s, [this](TaskContext task) {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true, -SPELL_CORRUPTION))
                DoCast(target, SPELL_CORRUPTION);
            task.Repeat(17s, 20s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
};

struct npc_forgotten_oneAI : public ScriptedAI
{
    npc_forgotten_oneAI(Creature* creature) : ScriptedAI(creature)
    {
        _scheduler.SetValidator([this] { return !me->HasUnitState(UNIT_STATE_CASTING); });
    }

    void Reset() override
    {
        _scheduler.CancelAll();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(0s, [this](TaskContext task) {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 5.0f, true))
            {
                DoCastSelf(SPELL_SHADOW_NOVA);
                task.Repeat(16s, 19s);
                return;
            }
            task.Repeat(5s);
        });
        _scheduler.Schedule(7s, 11s, [this](TaskContext task) {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 70.0f, true))
                DoCast(target, SPELL_SHADOW_CRASH);
            task.Repeat(17s, 20s);
        });
        _scheduler.Schedule(9s, 12s, [this](TaskContext task) {
            DoCastSelf(SPELL_PSYCHIC_SCREAM);
            task.Repeat(18s, 21s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
};

// 56710, 61460 - Aura of Lost Hope
class spell_aura_of_lost_hope_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_aura_of_lost_hope_SpellScript);

    SpellCastResult CheckCast()
    {
        if (!GetCaster()->IsInCombat())
            return SPELL_FAILED_DONT_REPORT;

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_aura_of_lost_hope_SpellScript::CheckCast);
    }
};

void AddSC_ahnkahet()
{
    new CreatureAILoader<npc_deep_crawlerAI>("npc_deep_crawler");
    new CreatureAILoader<npc_ahnkahar_spell_flingerAI>("npc_ahnkahar_spell_flinger");
    new AuraScriptLoaderEx<spell_shadow_sickle_AuraScript>("spell_shadow_sickle");
    new SpellScriptLoaderEx<spell_shadow_blast_SpellScript>("spell_shadow_blast");
    new CreatureAILoader<npc_ahnkahar_slasherAI>("npc_ahnkahar_slasher");
    new AuraScriptLoaderEx<spell_triple_slash_AuraScript>("spell_triple_slash");
    new CreatureAILoader<npc_plundering_geistAI>("npc_plundering_geist");
    new CreatureAILoader<npc_eye_of_taldaramAI>("npc_eye_of_taldaram");
    new CreatureAILoader<npc_bonegrinderAI>("npc_bonegrinder");
    new CreatureAILoader<npc_frostbringerAI>("npc_frostbringer");
    new CreatureAILoader<npc_twilight_apostleAI>("npc_twilight_apostle");
    new CreatureAILoader<npc_twilight_darkcasterAI>("npc_twilight_darkcaster");
    new CreatureAILoader<npc_forgotten_oneAI>("npc_forgotten_one");
    new SpellScriptLoaderEx<spell_aura_of_lost_hope_SpellScript>("spell_aura_of_lost_hope");
}
