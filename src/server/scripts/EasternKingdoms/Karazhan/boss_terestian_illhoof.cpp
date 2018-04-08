/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "karazhan.h"

enum TerestianSays
{
    SAY_SLAY,
    SAY_DEATH,
    SAY_AGGRO,
    SAY_SACRIFICE,
    SAY_SUMMON
};

enum TerestianSpells
{
    SPELL_SUMMON_DEMONCHAINS        = 30120,                   // Summons demonic chains that maintain the ritual of sacrifice.
    SPELL_DEMON_CHAINS              = 30206,                   // Instant - Visual Effect
    SPELL_ENRAGE                    = 23537,                   // Increases the caster's attack speed by 50% and the Physical damage it deals by 219 to 281 for 10 min.
    SPELL_SHADOW_BOLT               = 30055,                   // Hurls a bolt of dark magic at an enemy, inflicting Shadow damage.
    SPELL_SACRIFICE                 = 30115,                   // Teleports and adds the debuff
    SPELL_BERSERK                   = 32965,                   // Increases attack speed by 75%. Periodically casts Shadow Bolt Volley.
    SPELL_SUMMON_FIENDISIMP         = 30184,                   // Summons a Fiendish Imp.
    SPELL_SUMMON_IMP                = 30066,                   // Summons Kil'rek
    SPELL_SPAWN_IMP_SELECTOR        = 30191,

    SPELL_FIENDISH_PORTAL           = 30171,                   // Opens portal and summons Fiendish Portal, 2 sec cast
    SPELL_FIENDISH_PORTAL_1         = 30179,                   // Opens portal and summons Fiendish Portal, instant cast

    SPELL_FIREBOLT                  = 30050,                   // Blasts a target for 150 Fire damage.
    SPELL_BROKEN_PACT               = 30065,                   // All damage taken increased by 25%.
    SPELL_AMPLIFY_FLAMES            = 30053                    // Increases the Fire damage taken by an enemy by 500 for 25 sec.
};

enum TerestianEvents
{
    EVENT_SHADOW_BOLT               = 1,
    EVENT_PORTAL,
    EVENT_PORTAL_2,
    EVENT_SUMMON,
    EVENT_SACRIFICE,
    EVENT_RESPAWN,
    EVENT_BERSERK,
    EVENT_KILL_TALK,

    EVENT_AMPLIFY_FLAMES,

    EVENT_FIREBOLT
};

enum TerestianCreatures
{
    NPC_DEMONCHAINS                 = 17248,
    NPC_FIENDISHIMP                 = 17267,
    NPC_PORTAL                      = 17265
};

enum TerestianMisc
{
    ACTION_SCHEDULE_RESPAWN         = 1,
    DATA_SACRIFICED_TARGET          = 1
};

struct boss_terestian_illhoofAI : public BossAI
{
    boss_terestian_illhoofAI(Creature* creature) : BossAI(creature, BOSS_TERESTIAN) { }

    void Reset() override
    {
        _Reset();
        _lastChainsGUID = 0;
        SummonNewKrilek();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
        events.ScheduleEvent(EVENT_SHADOW_BOLT, 5s);
        events.ScheduleEvent(EVENT_PORTAL, 10s);
        events.ScheduleEvent(EVENT_SACRIFICE, 30s);
        events.ScheduleEvent(EVENT_BERSERK, 10min);
    }

    auto GetKilrek() const
    {
        return instance->GetCreature(DATA_KILREK);
    }

    void SummonNewKrilek()
    {
        me->RemoveAurasDueToSpell(SPELL_BROKEN_PACT);
        if (auto kilrek = GetKilrek())
            kilrek->DespawnOrUnsummon();
        DoCastSelf(SPELL_SUMMON_IMP, true);
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_SCHEDULE_RESPAWN)
            events.RescheduleEvent(EVENT_RESPAWN, 45s);
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_DEMONCHAINS)
            _lastChainsGUID = summon->GetGUID();

        BossAI::JustSummoned(summon);
        switch (summon->GetEntry())
        {
            case NPC_PORTAL:
                events.RescheduleEvent(EVENT_SUMMON, 5s);
                // no break intended
            case NPC_DEMONCHAINS:
                summon->SetControlled(true, UNIT_STATE_ROOT);
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                break;
            default:
                break;
        }
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_SLAY);
            events.ScheduleEvent(EVENT_KILL_TALK, 6s);
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_SHADOW_BOLT:
                DoCastVictim(SPELL_SHADOW_BOLT);
                events.Repeat(8s, 12s);
                break;
            case EVENT_PORTAL:
                Talk(SAY_SUMMON);
                DoCastAOE(SPELL_FIENDISH_PORTAL);
                events.ScheduleEvent(EVENT_PORTAL_2, 2s);
                break;
            case EVENT_PORTAL_2:
                DoCastAOE(SPELL_FIENDISH_PORTAL_1);
                break;
            case EVENT_SUMMON:
                DoCastSelf(SPELL_SPAWN_IMP_SELECTOR, true);
                events.Repeat(5s);
                break;
            case EVENT_SACRIFICE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                {
                    DoCast(target, SPELL_SACRIFICE, true);
                    DoCastAOE(SPELL_SUMMON_DEMONCHAINS, true);
                    if (Creature* chains = ObjectAccessor::GetCreature(*me, _lastChainsGUID))
                        if (chains->IsAIEnabled)
                            chains->AI()->SetGUID(target->GetGUID(), DATA_SACRIFICED_TARGET);
                    Talk(SAY_SACRIFICE);
                }
                events.Repeat(30s);
                break;
            case EVENT_RESPAWN:
                SummonNewKrilek();
                break;
            case EVENT_BERSERK:
                DoCastSelf(SPELL_BERSERK);
                break;
            default:
                break;
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
    }

    private:
        uint64 _lastChainsGUID;
};

struct npc_terestian_imp_baseAI : public ScriptedAI
{
    npc_terestian_imp_baseAI(Creature* creature) : ScriptedAI(creature), _instance(me->GetInstanceScript()) { }

    void Reset() override
    {
        _events.Reset();
    }

    auto GetTerestian() const
    {
        return _instance ? _instance->GetCreature(BOSS_TERESTIAN) : nullptr;
    }

    virtual void DoEvent(uint32 eventId) = 0;

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            DoEvent(eventId);
            if (me->IsCasting())
                return;
        }

        DoMeleeAttackIfReady();
    }

    protected:
        EventMap _events;
        InstanceScript* _instance;
};

struct npc_kilrekAI : public npc_terestian_imp_baseAI
{
    npc_kilrekAI(Creature* creature) : npc_terestian_imp_baseAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_AMPLIFY_FLAMES, 2s);
    }

    void DoEvent(uint32 eventId) override
    {
        if (eventId == EVENT_AMPLIFY_FLAMES)
        {
            DoCastVictim(SPELL_AMPLIFY_FLAMES);
            _events.Repeat(10s, 20s);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        DoCastAOE(SPELL_BROKEN_PACT, true);
        if (Creature* terestian = GetTerestian())
            if (terestian->IsAlive() && terestian->IsAIEnabled)
                terestian->AI()->DoAction(ACTION_SCHEDULE_RESPAWN);
    }
};

struct npc_fiendish_impAI : public npc_terestian_imp_baseAI
{
    npc_fiendish_impAI(Creature* creature) : npc_terestian_imp_baseAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_FIREBOLT, 2s);
    }

    void DoEvent(uint32 eventId) override
    {
        if (eventId == EVENT_FIREBOLT)
        {
            DoCastVictim(SPELL_FIREBOLT);
            _events.Repeat(2.2s);
        }
    }
};

struct npc_demon_chainAI : public ScriptedAI
{
    npc_demon_chainAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        DoCastSelf(SPELL_DEMON_CHAINS, true);
        _sacrificeGUID = 0;
    }

    void SetGUID(uint64 guid, int32 param) override
    {
        if (guid && param == DATA_SACRIFICED_TARGET)
            _sacrificeGUID = guid;
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (Unit* sacrificed = ObjectAccessor::GetUnit(*me, _sacrificeGUID))
            sacrificed->RemoveAurasDueToSpell(SPELL_SACRIFICE);
    }

    private:
        uint64 _sacrificeGUID;
};

class spell_terestian_spawn_imp_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_terestian_spawn_imp_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        Trinity::Containers::RandomResize(targets, 1);
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        GetHitUnit()->CastSpell(GetHitUnit(), SPELL_SUMMON_FIENDISIMP, true, nullptr, nullptr, GetCaster()->GetGUID());
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_terestian_spawn_imp_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_terestian_spawn_imp_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
    }
};

void AddSC_boss_terestian_illhoof()
{
    new CreatureAILoader<boss_terestian_illhoofAI>("boss_terestian_illhoof");
    new CreatureAILoader<npc_kilrekAI>("npc_kilrek");
    new CreatureAILoader<npc_fiendish_impAI>("npc_fiendish_imp");
    new CreatureAILoader<npc_demon_chainAI>("npc_demon_chain");
    new SpellScriptLoaderEx<spell_terestian_spawn_imp_SpellScript>("spell_terestian_spawn_imp");
}
