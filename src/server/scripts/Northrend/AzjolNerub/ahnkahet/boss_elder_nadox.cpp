#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ahnkahet.h"
#include "SpellAuras.h"
#include "SpellScript.h"
#include "World.h"

enum NadoxTexts
{
    SAY_AGGRO,
    SAY_SLAY,
    SAY_DEATH,
    SAY_EGG_SAC,
    EMOTE_HATCHES
};

enum NadoxSpells
{
    // Elder Nadox
    SPELL_BROOD_PLAGUE          = 56130,
    H_SPELL_BROOD_RAGE          = 59465,
    SPELL_ENRAGE                = 26662,
    SPELL_SUMMON_SWARMERS       = 56119,
    SPELL_SUMMON_SWARM_GUARD    = 56120,

    // Adds
    SPELL_SWARM_BUFF            = 56281,
    SPELL_SPRINT                = 56354
};

enum NadoxEvents
{
    EVENT_PLAGUE                = 1,
    EVENT_RAGE,
    EVENT_SWARMER,
    EVENT_CHECK_ENRAGE,
    EVENT_KILL_TALK,

    EVENT_SPRINT
};

enum NadoxMisc
{
    NPC_GUARDIAN_EGG            = 30173,
    NPC_SWARM_EGG               = 30172,

    DATA_RESPECT_YOUR_ELDERS    = 1
};

struct boss_elder_nadoxAI : public BossAI
{
    boss_elder_nadoxAI(Creature* creature) : BossAI(creature, BOSS_NADOX)
    {
        _preNerf = sWorld->PatchNotes(PATCH_MIN, PATCH_332);
    }

    void Reset() override
    {
        _Reset();
        _guardianCount = 0;
        _guardianDied = false;
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
        events.ScheduleEvent(EVENT_PLAGUE, 13s);
        events.ScheduleEvent(EVENT_SWARMER, 10s);

        if (IsHeroic())
        {
            events.ScheduleEvent(EVENT_RAGE, 12s);
            events.ScheduleEvent(EVENT_CHECK_ENRAGE, 5s);
        }
    }

    void JustSummoned(Creature* summon) override
    {
        DoZoneInCombat(summon, 250.0f);
        summons.Summon(summon);
    }

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        if (summon->GetEntry() == NPC_AHNKAHAR_GUARDIAN)
            _guardianDied = true;

        BossAI::SummonedCreatureDies(summon, killer);
    }

    uint32 GetData(uint32 type) const override
    {
        if (type == DATA_RESPECT_YOUR_ELDERS)
        {
            if (IsHeroic())
            {
                return !_guardianDied ? 1 : 0;
            }
        }

        return 0;
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_SLAY);
            events.ScheduleEvent(EVENT_KILL_TALK, 6s);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
    }

    void DoSummon(uint32 spellId) const
    {
        // Couldn't find any spells for target selecting :(
        std::list<Creature*> eggList;
        me->GetCreatureListWithEntryInGrid(eggList, spellId == SPELL_SUMMON_SWARMERS ? NPC_SWARM_EGG : NPC_GUARDIAN_EGG, 250.0f);
        if (eggList.empty())
            return;
        Trinity::Containers::RandomResize(eggList, 1);
        Creature* caster = eggList.front();
        caster->CastSpell(caster, spellId);
    }

    void DamageTaken(Unit* /*attacker*/, uint32 &damage, DamageEffectType /*damageType*/, SpellSchoolMask /*schoolMask*/) override
    {
        bool healthCheck = false;
        if (_preNerf)
        {
            healthCheck = (me->HealthBelowPctDamaged(75, damage) && _guardianCount == 0) ||
                (me->HealthBelowPctDamaged(50, damage) && _guardianCount == 1) ||
                (me->HealthBelowPctDamaged(25, damage) && _guardianCount == 2);
        }
        else
            healthCheck = (me->HealthBelowPctDamaged(50, damage) && _guardianCount == 0);


        if (healthCheck)
        {
            ++_guardianCount;
            Talk(EMOTE_HATCHES);
            DoSummon(SPELL_SUMMON_SWARM_GUARD);
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_PLAGUE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true, -SPELL_BROOD_PLAGUE))
                    DoCast(target, SPELL_BROOD_PLAGUE);
                events.Repeat(15s);
                break;
            case EVENT_RAGE:
                DoCastAOE(H_SPELL_BROOD_RAGE);
                events.Repeat(10s, 50s);
                break;
            case EVENT_SWARMER:
                DoSummon(SPELL_SUMMON_SWARMERS);
                if (!urand(0, 2))
                    Talk(SAY_EGG_SAC);
                events.Repeat(10s);
                break;
            case EVENT_CHECK_ENRAGE:
                if (me->HasAura(SPELL_ENRAGE))
                    return;
                if (me->GetPositionZ() < 24.0f)
                    DoCastSelf(SPELL_ENRAGE, true);
                events.Repeat(5s);
                break;
            default:
                break;
        }
    }

    private:
        uint8 _guardianCount;
        bool _preNerf;
        bool _guardianDied;
};

struct npc_nadox_addAI : public ScriptedAI
{
    npc_nadox_addAI(Creature* creature) : ScriptedAI(creature) { }

    void JustSummoned(Creature* summon) override
    {
        // Inform boss
        if (InstanceScript* instance = me->GetInstanceScript())
            if (Creature* nadox = instance->GetCreature(BOSS_NADOX))
                if (nadox->IsAIEnabled)
                    nadox->AI()->JustSummoned(summon);
    }

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        // Inform boss
        if (InstanceScript* instance = me->GetInstanceScript())
            if (Creature* nadox = instance->GetCreature(BOSS_NADOX))
                if (nadox->IsAIEnabled)
                    nadox->AI()->SummonedCreatureDies(summon, killer);
    }
};

struct npc_ahnkahar_nerubianAI : public npc_nadox_addAI
{
    npc_ahnkahar_nerubianAI(Creature* creature) : npc_nadox_addAI(creature) { }

    void Reset() override
    {
        _events.Reset();
        _events.ScheduleEvent(EVENT_SPRINT, 13s);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SPRINT:
                    DoCastSelf(SPELL_SPRINT);
                    _events.Repeat(20s);
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    private:
        EventMap _events;
};

struct npc_nadox_eggAI : public npc_nadox_addAI
{
    npc_nadox_eggAI(Creature* creature) : npc_nadox_addAI(creature)
    {
        SetCombatMovement(false);
        me->SetReactState(REACT_PASSIVE);
    }
};

// 56159 - Swarm
class spell_ahn_kahet_swarmer_aura_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_ahn_kahet_swarmer_aura_SpellScript)

    void CountTargets(std::list<WorldObject*>& targets)
    {
        _targetCount = targets.size();
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (_targetCount)
        {
            if (Aura* aura = GetCaster()->GetAura(SPELL_SWARM_BUFF))
            {
                aura->SetStackAmount(_targetCount);
                aura->RefreshDuration();
            }
            else
                GetCaster()->CastCustomSpell(SPELL_SWARM_BUFF, SPELLVALUE_AURA_STACK, _targetCount, GetCaster(), TRIGGERED_FULL_MASK);
        }
        else
            GetCaster()->RemoveAurasDueToSpell(SPELL_SWARM_BUFF);
    }

    uint32 _targetCount = 0;

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ahn_kahet_swarmer_aura_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
        OnEffectHit += SpellEffectFn(spell_ahn_kahet_swarmer_aura_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

class achievement_respect_your_elders : public AchievementCriteriaScript
{
    public:
        achievement_respect_your_elders() : AchievementCriteriaScript("achievement_respect_your_elders") { }

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            return target && target->IsAIEnabled && target->GetAI()->GetData(DATA_RESPECT_YOUR_ELDERS);
        }
};

void AddSC_boss_elder_nadox()
{
    new CreatureAILoader<boss_elder_nadoxAI>("boss_elder_nadox");
    new CreatureAILoader<npc_ahnkahar_nerubianAI>("npc_ahnkahar_nerubian");
    new CreatureAILoader<npc_nadox_eggAI>("npc_nadox_egg");
    new SpellScriptLoaderEx<spell_ahn_kahet_swarmer_aura_SpellScript>("spell_ahn_kahet_swarmer_aura");
    new achievement_respect_your_elders();
}
