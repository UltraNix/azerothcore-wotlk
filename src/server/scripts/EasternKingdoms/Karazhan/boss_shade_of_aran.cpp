/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "karazhan.h"
#include "SpellScript.h"
#include "Spell.h"

enum AranYells
{
    SAY_AGGRO,
    SAY_FLAME_WREATH,
    SAY_BLIZZARD,
    SAY_EXPLOSION,
    SAY_DRINK,
    SAY_ELEMENTALS,
    SAY_KILL,
    SAY_TIMEOVER,
    SAY_DEATH,
    SAY_ATIESH
};

enum AranSpells
{
    SPELL_FROSTBOLT                 = 29954,
    SPELL_FIREBALL                  = 29953,
    SPELL_ARCANE_MISSILES           = 29955,
    SPELL_CHAINS_OF_ICE             = 29991,
    SPELL_AOE_COUNTERSPELL          = 29961,
    SPELL_BLINK_CENTER              = 29967,
    SPELL_MASS_SLOW                 = 30035,
    SPELL_PLAYER_PULL               = 32265,
    SPELL_ARCANE_EXPLOSION          = 29973,
    SPELL_WATER_ELEMENTAL1          = 29962,
    SPELL_WATER_ELEMENTAL2          = 37053,
    SPELL_WATER_ELEMENTAL3          = 37051,
    SPELL_WATER_ELEMENTAL4          = 37052,
    SPELL_FLAME_WREATH_SELECTOR     = 30004,
    SPELL_FLAME_WREATH_EFFECT       = 29946,
    SPELL_FLAME_WREATH_FIRE         = 29947,
    SPELL_EXPLOSION                 = 20476,
    SPELL_BLIZZARD_ACTIVATE         = 29969,
    SPELL_CIRCULAR_BLIZZARD         = 29952,
    SPELL_MASS_POLY                 = 29963,
    SPELL_CONJURE                   = 29975,
    SPELL_DRINK                     = 30024,
    SPELL_AOE_PYROBLAST             = 29978,

    // Elemental
    SPELL_WATERBOLT                 = 31012
};

enum AranEvents
{
    EVENT_FROSTBOLT                 = 1,
    EVENT_FIREBALL,
    EVENT_ARCANE_MISSILES,
    EVENT_COUNTERSPELL,
    EVENT_SPECIAL,
    EVENT_FLAME_WREATH,
    EVENT_BLIZZARD,
    EVENT_ARCANE_EXPLOSION,
    EVENT_CAST_EXPLOSION,
    EVENT_REGEN_MANA,
    EVENT_CONJURE,
    EVENT_DRINK,
    EVENT_STAND_UP,
    EVENT_PYROBLAST,
    EVENT_RETURN,
    EVENT_BERSERK,
    EVENT_KILL_TALK
};

enum AranPhases
{
    PHASE_NORMAL                    = 1,
    PHASE_SPECIAL,
    PHASE_DRINK
};

enum AranMisc
{
    NPC_SHADOW_OF_ARAN              = 18254
};

struct boss_shade_of_aranAI : public BossAI
{
    boss_shade_of_aranAI(Creature* creature) : BossAI(creature, BOSS_ARAN) { }

    void Reset() override
    {
        _Reset();
        _elementalsSpawned = false;
        _drinking = false;
        _lastSpecialId = 0;
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->SetAggressive();
    }

    bool AnyPlayerHasAtiesh() const
    {
        auto const& players = me->GetMap()->GetPlayers();
        for (auto const& player : players)
            if (Player* playerPointer = player.GetSource())
                for (auto itemId : { 22632, 22631, 22630, 22589 })
                    if (playerPointer->GetItemCount(itemId, true))
                        return true;

        return false;
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        events.SetPhase(PHASE_NORMAL);
        _EnterCombat();
        Talk(AnyPlayerHasAtiesh() ? SAY_ATIESH : SAY_AGGRO);
        events.ScheduleEvent(EVENT_COUNTERSPELL, 10s, 20s, 0, PHASE_NORMAL);
        events.ScheduleEvent(EVENT_SPECIAL, 35s, 0, PHASE_NORMAL);
        events.ScheduleEvent(EVENT_BERSERK, 12min, 0, PHASE_NORMAL);
    }

    void HandleCasts()
    {
        std::vector<uint32> eventIds = { EVENT_FROSTBOLT, EVENT_FIREBALL, EVENT_ARCANE_MISSILES };
        events.ScheduleEvent(Trinity::Containers::SelectRandomContainerElement(eventIds), 0s, 0, PHASE_NORMAL);
    }

    void DamageTaken(Unit* /*attacker*/, uint32 &damage, DamageEffectType damageType, SpellSchoolMask /*schoolmask*/) override
    {
        if (events.IsInPhase(PHASE_DRINK) && damage && damageType != DOT)
            events.RescheduleEvent(EVENT_STAND_UP, 0.5s, 0, PHASE_DRINK);

        if (!_elementalsSpawned && me->HealthBelowPctDamaged(40, damage))
        {
            _elementalsSpawned = true;
            Talk(SAY_ELEMENTALS);
            for (auto const& spellId : { SPELL_WATER_ELEMENTAL1, SPELL_WATER_ELEMENTAL2, SPELL_WATER_ELEMENTAL3, SPELL_WATER_ELEMENTAL4 })
                DoCastAOE(spellId, true);
        }
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_KILL);
            events.ScheduleEvent(EVENT_KILL_TALK, 5s);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->GetPowerPct(POWER_MANA) < 20.0f && !events.IsInPhase(PHASE_DRINK))
        {
            events.SetPhase(PHASE_DRINK);
            events.ScheduleEvent(EVENT_REGEN_MANA, 0s, 0, PHASE_DRINK);
            return;
        }

        if (me->IsCasting())
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_FROSTBOLT:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f))
                        DoCast(target, SPELL_FROSTBOLT);
                    break;
                case EVENT_FIREBALL:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f))
                        DoCast(target, SPELL_FIREBALL);
                    break;
                case EVENT_ARCANE_MISSILES:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f))
                        DoCast(target, SPELL_ARCANE_MISSILES);
                    break;
                case EVENT_COUNTERSPELL:
                    DoCastSelf(SPELL_AOE_COUNTERSPELL, true);
                    events.Repeat(10s, 20s);
                    break;
                case EVENT_SPECIAL:
                {
                    std::vector<uint32> eventIds = { EVENT_FLAME_WREATH, EVENT_ARCANE_EXPLOSION, EVENT_BLIZZARD };
                    Trinity::Containers::RandomResize(eventIds, [&](uint32 eventId) -> bool { return eventId != _lastSpecialId; }, 1);
                    // We shouldn't allow to cast two same special events in a row
                    events.Repeat(30s, 35s);
                    events.SetPhase(PHASE_SPECIAL);
                    events.ScheduleEvent(eventIds.front(), 0s, 0, PHASE_SPECIAL);
                    break;
                }
                case EVENT_FLAME_WREATH:
                    _lastSpecialId = EVENT_FLAME_WREATH;
                    Talk(SAY_FLAME_WREATH);
                    DoCastSelf(SPELL_FLAME_WREATH_SELECTOR);
                    events.SetPhase(PHASE_NORMAL);
                    break;
                case EVENT_ARCANE_EXPLOSION:
                    events.SetPhase(PHASE_SPECIAL);
                    _lastSpecialId = EVENT_ARCANE_EXPLOSION;
                    Talk(SAY_EXPLOSION);
                    DoCastSelf(SPELL_BLINK_CENTER);
                    DoCastSelf(SPELL_PLAYER_PULL);
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    events.ScheduleEvent(EVENT_CAST_EXPLOSION, 1s, 0, PHASE_SPECIAL);
                    break;
                case EVENT_CAST_EXPLOSION:
                    DoCastSelf(SPELL_MASS_SLOW);
                    DoCastSelf(SPELL_ARCANE_EXPLOSION);
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    events.SetPhase(PHASE_NORMAL);
                    break;
                case EVENT_BLIZZARD:
                    _lastSpecialId = EVENT_BLIZZARD;
                    Talk(SAY_BLIZZARD);
                    DoCastAOE(SPELL_BLIZZARD_ACTIVATE);
                    events.SetPhase(PHASE_NORMAL);
                    break;
                case EVENT_REGEN_MANA:
                    Talk(SAY_DRINK);
                    me->InterruptNonMeleeSpells(false);
                    me->SetPassive();
                    DoCastSelf(SPELL_MASS_POLY);
                    events.ScheduleEvent(EVENT_CONJURE, 1s, 0, PHASE_DRINK);
                    break;
                case EVENT_CONJURE:
                    DoCastSelf(SPELL_CONJURE);
                    events.ScheduleEvent(EVENT_DRINK, 2.5s, 0, PHASE_DRINK);
                    break;
                case EVENT_DRINK:
                    DoCastSelf(SPELL_DRINK);
                    me->SetStandState(UNIT_STAND_STATE_SIT);
                    events.ScheduleEvent(EVENT_STAND_UP, 5s, 0, PHASE_DRINK);
                    break;
                case EVENT_STAND_UP:
                    me->SetStandState(UNIT_STAND_STATE_STAND);
                    events.ScheduleEvent(EVENT_PYROBLAST, 0.75s, 0, PHASE_DRINK);
                    break;
                case EVENT_PYROBLAST:
                    DoCastSelf(SPELL_AOE_PYROBLAST);
                    events.ScheduleEvent(EVENT_RETURN, 2s, 0, PHASE_DRINK);
                    break;
                case EVENT_RETURN:
                    me->SetAggressive();
                    events.SetPhase(PHASE_NORMAL);
                    break;
                case EVENT_BERSERK:
                    Talk(SAY_TIMEOVER);
                    for (uint8 i = 0; i < 5; ++i)
                    {
                        if (Creature* center = me->FindNearestCreature(17176, 50.0f))
                        {
                            Position pos;
                            center->GetRandomNearPosition(pos, 15.0f);
                            me->SummonCreature(NPC_SHADOW_OF_ARAN, pos, TEMPSUMMON_CORPSE_DESPAWN);
                        }
                    }
                    break;
                default:
                    break;
            }

            if (me->IsCasting())
                return;
        }

        HandleCasts();
    }

    private:
        bool _elementalsSpawned;
        bool _drinking;
        uint32 _lastSpecialId;
};

struct npc_aran_elementalAI : public ScriptedAI
{
    npc_aran_elementalAI(Creature* creature) : ScriptedAI(creature) { }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (me->IsCasting())
            return;

        DoCastVictim(SPELL_WATERBOLT);
    }
};

struct npc_aran_blizzardAI : public ScriptedAI
{
    npc_aran_blizzardAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        me->GetMotionMaster()->MovePath(171760, true);
    }
};

class spell_aran_flame_wreath_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_aran_flame_wreath_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        Trinity::Containers::RandomResize(targets, [&](WorldObject* target) -> bool { return target->IsPlayer(); }, 3);
    }

    void HandleOnHit()
    {
        if (Unit* target = GetHitUnit())
            GetCaster()->CastSpell(target, SPELL_FLAME_WREATH_EFFECT, true);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_aran_flame_wreath_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnHit += SpellHitFn(spell_aran_flame_wreath_SpellScript::HandleOnHit);
    }
};

class spell_aran_flame_wreath_effect_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_aran_flame_wreath_effect_AuraScript);

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (auto obj = GetDynobjOwner())
        {
            obj->Remove();
            GetTarget()->CastSpell(GetTarget(), SPELL_FLAME_WREATH_FIRE, true);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_aran_flame_wreath_effect_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_aran_flame_wreath_aura_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_aran_flame_wreath_aura_AuraScript);

    void OnPeriodic(AuraEffect const* aurEff)
    {
        if (Unit* target = GetTarget())
        {
            target->CastSpell(target, SPELL_EXPLOSION, true);
            target->RemoveAurasDueToSpell(GetAura()->GetId());
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_aran_flame_wreath_aura_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

class spell_aran_blizzard_activate_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_aran_blizzard_activate_SpellScript);

    void HandleOnHit()
    {
        if (Unit* target = GetHitUnit())
            target->CastSpell(target, SPELL_CIRCULAR_BLIZZARD, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_aran_blizzard_activate_SpellScript::HandleOnHit);
    }
};

class spell_aran_frostbolt_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_aran_frostbolt_AuraScript);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        // ~33% chance
        if (!urand(0, 2))
            if (Unit* caster = GetCaster())
                caster->CastSpell(GetTarget(), SPELL_CHAINS_OF_ICE, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_aran_frostbolt_AuraScript::OnApply, EFFECT_1, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_boss_shade_of_aran()
{
    new CreatureAILoader<boss_shade_of_aranAI>("boss_shade_of_aran");
    new CreatureAILoader<npc_aran_elementalAI>("npc_aran_elemental");
    new CreatureAILoader<npc_aran_blizzardAI>("npc_aran_blizzard");
    new SpellScriptLoaderEx<spell_aran_flame_wreath_SpellScript>("spell_aran_flame_wreath");
    new AuraScriptLoaderEx<spell_aran_flame_wreath_effect_AuraScript>("spell_aran_flame_wreath_effect");
    new AuraScriptLoaderEx<spell_aran_flame_wreath_aura_AuraScript>("spell_aran_flame_wreath_aura");
    new SpellScriptLoaderEx<spell_aran_blizzard_activate_SpellScript>("spell_aran_blizzard_activate");
    new AuraScriptLoaderEx<spell_aran_frostbolt_AuraScript>("spell_aran_frostbolt");
}
