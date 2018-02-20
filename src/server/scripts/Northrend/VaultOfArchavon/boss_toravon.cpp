#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "vault_of_archavon.h"
#include "SpellAuras.h"
#include "PassiveAI.h"
#include "Player.h"

enum ToravonSpells
{
    // Toravon
    SPELL_FREEZING_GROUND               = 72090,
    SPELL_FROZEN_ORB                    = 72091,
    SPELL_WHITEOUT                      = 72034,
    SPELL_FROZEN_MALLET                 = 71993,
    SPELL_FROSTBITE                     = 72004,

    // Frozen Orb
    SPELL_FROZEN_ORB_DMG                = 72081,
    SPELL_FROZEN_ORB_AURA               = 72067,
    SPELL_RANDOM_AGGRO                  = 72084
};

enum ToravonMisc
{
    NPC_FROZEN_ORB                      = 38456,
    NPC_FROZEN_ORB_STALKER              = 38461
};

struct boss_toravonAI : public BossAI
{
    boss_toravonAI(Creature* creature) : BossAI(creature, EVENT_TORAVON) { }

    void Reset() override
    {
        _Reset();
        if (instance->GetData(DATA_STONED))
        {
            if (Aura* aura = me->AddAura(SPELL_STONED_AURA, me))
            {
                aura->SetMaxDuration(60 * MINUTE* IN_MILLISECONDS);
                aura->SetDuration(60 * MINUTE* IN_MILLISECONDS);
            }
        }

        instance->SetData(EVENT_TORAVON, NOT_STARTED);
    }

    void AttackStart(Unit* who) override
    {
        if (me->HasAura(SPELL_STONED_AURA))
            return;

        BossAI::AttackStart(who);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();

        DoCastSelf(SPELL_FROZEN_MALLET);
        scheduler.Schedule(12s, [this](TaskContext task)
        {
            me->CastCustomSpell(SPELL_FROZEN_ORB, SPELLVALUE_MAX_TARGETS, RAID_MODE(1, 3), me, false);
            task.Repeat(32s);
        });
        scheduler.Schedule(25s, [this](TaskContext task)
        {
            DoCastSelf(SPELL_WHITEOUT);
            task.Repeat(38s);
        });
        scheduler.Schedule(7s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1))
                DoCast(target, SPELL_FREEZING_GROUND);
            task.Repeat(38s);
        });


        instance->SetData(EVENT_TORAVON, IN_PROGRESS);
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        instance->SetData(EVENT_TORAVON, DONE);
        for (uint32 spellId : { sSpellMgr->GetSpellIdForDifficulty(SPELL_WHITEOUT, me), sSpellMgr->GetSpellIdForDifficulty(SPELL_FROSTBITE, me) })
            instance->DoRemoveAurasDueToSpellOnPlayers(spellId);
    }

    void EnterEvadeMode() override
    {
        for (uint32 spellId : { sSpellMgr->GetSpellIdForDifficulty(SPELL_WHITEOUT, me), sSpellMgr->GetSpellIdForDifficulty(SPELL_FROSTBITE, me) })
            instance->DoRemoveAurasDueToSpellOnPlayers(spellId);
        BossAI::EnterEvadeMode();
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff,
            std::bind(&BossAI::DoMeleeAttackIfReady, this));
    }
};

struct npc_frozen_orbAI : public ScriptedAI
{
    npc_frozen_orbAI(Creature* creature) : ScriptedAI(creature) { }

    void IsSummonedBy(Unit* /*summoner*/) override
    {
        DoCastSelf(SPELL_FROZEN_ORB_AURA, true);
        DoCastSelf(SPELL_FROZEN_ORB_DMG, true);
        DoCastSelf(SPELL_RANDOM_AGGRO, true);

        if (InstanceScript* instance = me->GetInstanceScript())
        {
            if (Creature* toravon = instance->instance->GetCreature(instance->GetData64(EVENT_TORAVON)))
            {
                if (toravon->IsInCombat())
                {
                    toravon->AI()->JustSummoned(me);
                    DoZoneInCombat();
                }
                else
                    me->DespawnOrUnsummon();
            }
        }
    }

    void UpdateAI(uint32 /*diff*/) override { }
};

// 46523 - Random Aggro
class spell_toravon_random_aggro_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_toravon_random_aggro_SpellScript);

    bool Load() override
    {
        return GetCaster()->IsCreature();
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        Creature* caster = GetCaster()->ToCreature();
        if (!caster->IsAIEnabled)
            return;

        caster->getThreatManager().resetAllAggro();

        if (Unit* target = caster->AI()->SelectTarget(SELECT_TARGET_RANDOM, 1))
            caster->getThreatManager().addThreat(target, 1000000.0f);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_toravon_random_aggro_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_boss_toravon()
{
    new CreatureAILoader<boss_toravonAI>("boss_toravon");
    new CreatureAILoader<npc_frozen_orbAI>("npc_frozen_orb");
    new SpellScriptLoaderEx<spell_toravon_random_aggro_SpellScript>("spell_toravon_random_aggro");
}
