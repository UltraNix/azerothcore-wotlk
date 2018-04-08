/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "karazhan.h"

enum NetherspiteSays
{
    EMOTE_PORTALS,
    EMOTE_BANISH
};

enum NetherspiteSpells
{
    SPELL_NETHERBURN_AURA                   = 30522,
    SPELL_VOID_ZONE                         = 37063,
    SPELL_NETHER_INFUSION                   = 38688,
    SPELL_NETHERBREATH                      = 38523,
    SPELL_BANISH_VISUAL                     = 39833,
    SPELL_BANISH_ROOT                       = 42716,
    SPELL_EMPOWERMENT                       = 38549,
    SPELL_NETHERSPITE_ROAR                  = 38684,

    // Shared portal spells
    SPELL_PORTAL_BEAM_CHECK                 = 30469,

    // Red portal spells
    SPELL_PERSEVERENCE_BEAM_CHECK           = 30396,
    SPELL_PERSEVERENCE_BEAM                 = 30465,
    SPELL_PERSEVERENCE_PLAYER_BUFF          = 30421,
    SPELL_PERSEVERENCE_NETHER_BUFF          = 30466,
    SPELL_PERSEVERENCE_PLAYER_DEBUFF        = 38637,
    SPELL_PERSEVERENCE_VISUAL               = 30487,

    // Green portal spells
    SPELL_SERENITY_BEAM_CHECK               = 30397,
    SPELL_SERENITY_BEAM                     = 30464,
    SPELL_SERENITY_PLAYER_BUFF              = 30422,
    SPELL_SERENITY_NETHER_BUFF              = 30467,
    SPELL_SERENITY_PLAYER_DEBUFF            = 38638,
    SPELL_SERENITY_VISUAL                   = 30490,

    // Blue portal spells
    SPELL_DOMINANCE_BEAM_CHECK              = 30398,
    SPELL_DOMINANCE_BEAM                    = 30463,
    SPELL_DOMINANCE_PLAYER_BUFF             = 30423,
    SPELL_DOMINANCE_NETHER_BUFF             = 30468,
    SPELL_DOMINANCE_PLAYER_DEBUFF           = 38639,
    SPELL_DOMINANCE_VISUAL                  = 30491
};

enum NetherspitePortals
{
    NPC_RED_PORTAL                          = 17369,
    NPC_GREEN_PORTAL                        = 17367,
    NPC_BLUE_PORTAL                         = 17368
};

enum NetherspiteEvents
{
    EVENT_VOID_ZONE                         = 1,
    EVENT_NETHERBREATH,
    EVENT_SET_PORTAL_PHASE,
    EVENT_ACTIVATE_PORTALS,
    EVENT_SET_BANISH_PHASE,
    EVENT_BERSERK,
};

enum NetherspitePhases
{
    PHASE_PORTAL                            = 1,
    PHASE_BANISH
};

struct boss_netherspiteAI : public BossAI
{
    boss_netherspiteAI(Creature* creature) : BossAI(creature, BOSS_NETHERSPITE) { }

    void Reset() override
    {
        _first = true;
        me->RemoveAllAuras();
        _Reset();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        events.ScheduleEvent(EVENT_SET_PORTAL_PHASE, 0s);
        events.ScheduleEvent(EVENT_VOID_ZONE, 15s);
        events.ScheduleEvent(EVENT_BERSERK, 9min);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_VOID_ZONE:
                if (events.IsInPhase(PHASE_PORTAL))
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 45.0f, true))
                        DoCast(target, SPELL_VOID_ZONE);
                events.Repeat(15s);
                break;
            case EVENT_BERSERK:
                DoCastSelf(SPELL_NETHERSPITE_ROAR);
                break;
            case EVENT_SET_PORTAL_PHASE:
            {
                me->RemoveAurasDueToSpell(SPELL_BANISH_VISUAL);
                me->RemoveAurasDueToSpell(SPELL_BANISH_ROOT);

                std::vector<Position> portalPositions =
                {
                    { -11195.353516f, -1613.237183f, 278.237258f }, // Left side
                    { -11137.846680f, -1685.607422f, 278.239258f }, // Right side
                    { -11094.493164f, -1591.969238f, 279.949188f }  // Back side
                };
                std::vector<uint32> portalEntry = { NPC_RED_PORTAL, NPC_GREEN_PORTAL, NPC_BLUE_PORTAL };

                if (_first)
                    _first = false;
                else
                    Talk(EMOTE_PORTALS);

                events.SetPhase(PHASE_PORTAL);
                std::random_shuffle(std::begin(portalPositions), std::end(portalPositions));
                for (uint8 i = 0; i < 3; ++i)
                    me->SummonCreature(portalEntry[i], portalPositions[i], TEMPSUMMON_TIMED_DESPAWN, 64000);

                events.ScheduleEvent(EVENT_ACTIVATE_PORTALS, 12s, 0, PHASE_PORTAL);
                events.ScheduleEvent(EVENT_SET_BANISH_PHASE, 64s, 0, PHASE_PORTAL);
                break;
            }
            case EVENT_ACTIVATE_PORTALS:
                for (auto entry : { NPC_RED_PORTAL, NPC_GREEN_PORTAL, NPC_BLUE_PORTAL })
                    if (Creature* portal = me->FindNearestCreature(entry, 250.0f))
                    {
                        switch (entry)
                        {
                            case NPC_RED_PORTAL:
                                portal->CastSpell(portal, SPELL_PERSEVERENCE_BEAM_CHECK);
                                break;
                            case NPC_GREEN_PORTAL:
                                portal->CastSpell(portal, SPELL_SERENITY_BEAM_CHECK);
                                break;
                            case NPC_BLUE_PORTAL:
                                portal->CastSpell(portal, SPELL_DOMINANCE_BEAM_CHECK);
                                break;
                            default:
                                break;
                        }
                    }

                DoCastSelf(SPELL_NETHERBURN_AURA);
                DoCastSelf(SPELL_EMPOWERMENT);
                break;
            case EVENT_SET_BANISH_PHASE:
                Talk(EMOTE_BANISH);
                events.SetPhase(PHASE_BANISH);
                me->RemoveAurasDueToSpell(SPELL_EMPOWERMENT);
                me->RemoveAurasDueToSpell(SPELL_NETHERBURN_AURA);
                DoCastSelf(SPELL_BANISH_VISUAL, true);
                DoCastSelf(SPELL_BANISH_ROOT, true);
                events.ScheduleEvent(EVENT_NETHERBREATH, 3s, 0, PHASE_BANISH);
                events.ScheduleEvent(EVENT_SET_PORTAL_PHASE, 30s, 0, PHASE_BANISH);
                break;
            case EVENT_NETHERBREATH:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                    DoCast(target, SPELL_NETHERBREATH);
                events.Repeat(5s, 7s);
                break;
            default:
                break;
        }
    }

    private:
        bool _first;
};

class spell_netherspite_roar_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_netherspite_roar_SpellScript);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetCaster(), SPELL_NETHER_INFUSION, true);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_netherspite_roar_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

class spell_netherspite_nether_beam_selector_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_netherspite_nether_beam_selector_SpellScript);

    bool Load() override
    {
        switch (GetCaster()->GetEntry())
        {
            case NPC_RED_PORTAL:
                _beamSpell = SPELL_PERSEVERENCE_BEAM;
                break;
            case NPC_GREEN_PORTAL:
                _beamSpell = SPELL_SERENITY_BEAM;
                break;
            case NPC_BLUE_PORTAL:
                _beamSpell = SPELL_DOMINANCE_BEAM;
                break;
            default:
                _beamSpell = 0;
        }

        return GetCaster()->ToCreature();
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (!_beamSpell)
            return;

        Creature* boss = nullptr;

        if (InstanceScript* instance = GetCaster()->GetInstanceScript())
        {
            boss = instance->GetCreature(BOSS_NETHERSPITE);
            targets.push_back(boss);
        }

        if (!boss)
            return;

        Trinity::Containers::Erase_if(targets, [this, boss](WorldObject* target) -> bool
        {
            if (target->IsPlayer())
                return !target->IsInBetween(GetCaster(), boss, 2.5f);
            else
                return false;
        });

        // Get closest target
        if (!targets.empty())
        {
            targets.sort(Trinity::ObjectDistanceOrderPred(GetCaster()));
            targets.resize(1);
        }
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (Unit* target = GetHitUnit())
            if (target->GetGUID() != caster->GetTarget())
            {
                caster->CastSpell(target, _beamSpell);
                caster->SetTarget(target->GetGUID());
            }
    }

    uint32 _beamSpell;

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_netherspite_nether_beam_selector_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ENTRY);
        OnEffectHitTarget += SpellEffectFn(spell_netherspite_nether_beam_selector_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

enum PortalSpells : uint8
{
    PORTAL_PLAYER_BUFF,
    PORTAL_BOSS_BUFF,
    PORTAL_PLAYER_DEBUFF
};

class spell_netherspite_nether_beam_effect_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_netherspite_nether_beam_effect_AuraScript);

    bool Load() override
    {
        switch (m_scriptSpellId)
        {
            case SPELL_PERSEVERENCE_BEAM:
                _buffSpells = { SPELL_PERSEVERENCE_PLAYER_BUFF, SPELL_PERSEVERENCE_NETHER_BUFF, SPELL_PERSEVERENCE_PLAYER_DEBUFF };
                break;
            case SPELL_SERENITY_BEAM:
                _buffSpells = { SPELL_SERENITY_PLAYER_BUFF, SPELL_SERENITY_NETHER_BUFF, SPELL_SERENITY_PLAYER_DEBUFF };
                break;
            case SPELL_DOMINANCE_BEAM:
                _buffSpells = { SPELL_DOMINANCE_PLAYER_BUFF, SPELL_DOMINANCE_NETHER_BUFF, SPELL_DOMINANCE_PLAYER_DEBUFF };
                break;
        }

        return true;
    }

    void HandleDummyTick(AuraEffect const* aurEff)
    {
        if (_buffSpells.empty())
            return;

        if (Unit* target = GetTarget())
        {
            if (target->IsPlayer() && !target->HasAura(_buffSpells[PORTAL_PLAYER_DEBUFF]))
                target->CastSpell(target, _buffSpells[PORTAL_PLAYER_BUFF], true);
            else if (target->GetEntry() == NPC_NETHERSPITE)
                target->CastSpell(target, _buffSpells[PORTAL_BOSS_BUFF], true);
        }
    }

    std::vector<uint32> _buffSpells;

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_netherspite_nether_beam_effect_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_netherspite_player_debuff_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_netherspite_player_debuff_AuraScript);

    bool Load() override
    {
        switch (m_scriptSpellId)
        {
            case SPELL_PERSEVERENCE_PLAYER_BUFF:
                _debuffSpell = SPELL_PERSEVERENCE_PLAYER_DEBUFF;
                break;
            case SPELL_SERENITY_PLAYER_BUFF:
                _debuffSpell = SPELL_SERENITY_PLAYER_DEBUFF;
                break;
            case SPELL_DOMINANCE_PLAYER_BUFF:
                _debuffSpell = SPELL_DOMINANCE_PLAYER_DEBUFF;
                break;
        }

        return true;
    }

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (!_debuffSpell)
            return;

        if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE)
            GetTarget()->CastSpell(GetTarget(), _debuffSpell, true);
    }

    uint32 _debuffSpell;

    void Register() override
    {
        if (m_scriptSpellId == SPELL_PERSEVERENCE_PLAYER_BUFF)
            AfterEffectRemove += AuraEffectRemoveFn(spell_netherspite_player_debuff_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        else if (m_scriptSpellId == SPELL_SERENITY_PLAYER_BUFF)
            AfterEffectRemove += AuraEffectRemoveFn(spell_netherspite_player_debuff_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_HEALING_DONE_PERCENT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        else if (m_scriptSpellId == SPELL_DOMINANCE_PLAYER_BUFF)
            AfterEffectRemove += AuraEffectRemoveFn(spell_netherspite_player_debuff_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

void AddSC_boss_netherspite()
{
    new CreatureAILoader<boss_netherspiteAI>("boss_netherspite");
    new SpellScriptLoaderEx<spell_netherspite_roar_SpellScript>("spell_netherspite_roar");
    new SpellScriptLoaderEx<spell_netherspite_nether_beam_selector_SpellScript>("spell_netherspite_nether_beam_selector");
    new AuraScriptLoaderEx<spell_netherspite_nether_beam_effect_AuraScript>("spell_netherspite_nether_beam_effect");
    new AuraScriptLoaderEx<spell_netherspite_player_debuff_AuraScript>("spell_netherspite_player_debuff");
}
