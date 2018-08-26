#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "molten_core.h"

enum CoreHound
{
    SPELL_SERRATED_BITE     = 19771,
    SPELL_FIRE_NOVA_VISUAL  = 19823,

    EMOTE_FEIGN_DEATH       = 0,
    EMOTE_RESSURRECT        = 1,

    EVENT_CHECK_DEATH       = 1,
    EVENT_SERRATED_BITE     = 2,

    PHASE_FIGHT             = 1,
    PHASE_DEAD              = 2,

    ACTION_FEIGN_DEATH      = 1,
    ACTION_RESSURRECT       = 2
};

struct npc_core_houndAI : public ScriptedAI
{
    npc_core_houndAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        ScriptedAI::Reset();
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        _events.SetPhase(PHASE_FIGHT);
        me->SetHealth(me->GetMaxHealth());
        me->SetStandState(UNIT_STAND_STATE_STAND);
        me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->SetReactState(REACT_AGGRESSIVE);
    }

    void EnterCombat(Unit* victim) override
    {
        ScriptedAI::EnterCombat(victim);
        _events.SetPhase(PHASE_FIGHT);
        _events.ScheduleEvent(EVENT_SERRATED_BITE, urand(4000, 7000), 0, PHASE_FIGHT);
    }

    void DoAction(int32 actionId) override
    {
        switch (actionId)
        {
        case ACTION_FEIGN_DEATH:
            _events.SetPhase(PHASE_DEAD);
            Talk(EMOTE_FEIGN_DEATH);
            me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->SetHealth(0);
            me->RemoveAllAuras();
            me->SetReactState(REACT_PASSIVE);
            me->SetControlled(true, UNIT_STATE_ROOT);
            me->SetTarget(0);
            _events.ScheduleEvent(EVENT_CHECK_DEATH, 10000, 0, PHASE_DEAD);
            break;
        case ACTION_RESSURRECT:
            _events.SetPhase(PHASE_FIGHT);
            Talk(EMOTE_RESSURRECT);
            DoCast(me, SPELL_FIRE_NOVA_VISUAL, true);
            me->SetHealth(me->GetMaxHealth());
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetControlled(false, UNIT_STATE_ROOT);
            _events.ScheduleEvent(EVENT_SERRATED_BITE, urand(4000, 7000), 0, PHASE_FIGHT);
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                AttackStart(target);
            break;
        default:
            break;
        }
    }

    bool checkRemainingHounds()
    {
        bool check = false;
        std::list<Creature*> houndList;
        me->GetCreatureListWithEntryInGrid(houndList, NPC_CORE_HOUND, 100.0f);
        if (!houndList.empty())
        {
            for (auto itr : houndList)
            {
                if (!itr->GetHealth() == 0 && itr->IsInCombat())
                {
                    check = true;
                    break;
                }
            }
        }
        return check;
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
    {
        if (damage > me->GetHealth() && !_events.IsInPhase(PHASE_DEAD))
        {
            damage = me->GetHealth() - 1;
            DoAction(ACTION_FEIGN_DEATH);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (_events.IsInPhase(PHASE_FIGHT))
        {
            if (!UpdateVictim())
                return;

            _events.Update(diff);

            if (_events.ExecuteEvent() == EVENT_SERRATED_BITE)
            {
                DoCastVictim(SPELL_SERRATED_BITE);
                _events.Repeat(urand(4000, 7000));
            }

            DoMeleeAttackIfReady();
        }
        else
        {
            if (!checkRemainingHounds())
            {
                me->SetHealth(1);
                me->Kill(me, me, false);
            }

            _events.Update(diff);

            if (_events.ExecuteEvent() == EVENT_CHECK_DEATH)
            {
                bool check = checkRemainingHounds();
                if (check)
                    DoAction(ACTION_RESSURRECT);
                else
                {
                    me->SetHealth(1);
                    me->Kill(me, me, false);
                }
            }
        }
    }
private:
    EventMap _events;
};

enum AncientCoreHound
{
    SPELL_CONE_OF_FIRE          = 19630,
    SPELL_VICIOUS_BITE          = 19319,
    SPELL_BITE                  = 19771,

    //Random Debuff (each hound has only one of these)
    SPELL_GROUND_STOMP          = 19364,
    SPELL_ANCIENT_DREAD         = 19365,
    SPELL_CAUTERIZING_FLAMES    = 19366,
    SPELL_WITHERING_HEAT        = 19367,
    SPELL_ANCIENT_DESPAIR       = 19369,
    SPELL_ANCIENT_HYSTERIA      = 19372,

    EVENT_CONE_OF_FIRE          = 1,
    EVENT_RANDOM_DEBUFF,
    EVENT_BITE,
    EVENT_VICIOUS_BITE
};

struct npc_ancient_core_houndAI : public ScriptedAI
{
    npc_ancient_core_houndAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        ScriptedAI::Reset();
        _randomSpell = Trinity::Containers::SelectRandomContainerElement(_spells);
    }

    void EnterCombat(Unit* victim) override
    {
        ScriptedAI::EnterCombat(victim);
        _events.ScheduleEvent(EVENT_CONE_OF_FIRE, urand(4000, 7000));
        _events.ScheduleEvent(EVENT_RANDOM_DEBUFF, urand(12000, 15000));
        _events.ScheduleEvent(EVENT_BITE, 4000);
        _events.ScheduleEvent(EVENT_VICIOUS_BITE, 2000);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_CONE_OF_FIRE:
                    DoCastAOE(SPELL_CONE_OF_FIRE);
                    _events.Repeat(urand(6000, 8000));
                    break;
                case EVENT_RANDOM_DEBUFF:
                    DoCastAOE(_randomSpell);
                    _events.Repeat(urand(14000, 24000));
                    break;
                case EVENT_BITE:
                    if (me->IsWithinMeleeRange(me->GetVictim()))
                        DoCastVictim(SPELL_BITE);
                    _events.Repeat(6000);
                    break;
                case EVENT_VICIOUS_BITE:
                    DoCastVictim(SPELL_VICIOUS_BITE);
                    _events.Repeat(2000);
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
    uint32 _randomSpell;
    std::vector<uint32> _spells =
    {
        SPELL_GROUND_STOMP,
        SPELL_ANCIENT_DREAD,
        SPELL_CAUTERIZING_FLAMES,
        SPELL_WITHERING_HEAT,
        SPELL_ANCIENT_DESPAIR,
        SPELL_ANCIENT_HYSTERIA
    };
};

enum Firelord
{
    NPC_LAVA_SPAWN              = 12265,

    EVENT_SOUL_BURN             = 1,
    EVENT_SUMMON_LAVA_SPAWN,

    SPELL_SOUL_BURN             = 19393,
    SPELL_SUMMON_LAVA_SPAWN     = 19392,
    SPELL_INCINERATE_AURA       = 19396
};

struct npc_firelordAI : public ScriptedAI
{
    npc_firelordAI(Creature* creature) : ScriptedAI(creature), summons(me) { }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_LAVA_SPAWN)
        {
            summons.Summon(summon);
            summon->SetInCombatWithZone();
        }
    }

    void EnterEvadeMode() override
    {
        CreatureAI::EnterEvadeMode();
        summons.DespawnAll();
    }

    void EnterCombat(Unit* victim) override
    {
        ScriptedAI::EnterCombat(victim);
        DoCast(me, SPELL_INCINERATE_AURA);
        _events.ScheduleEvent(EVENT_SOUL_BURN, urand(4000, 6000));
        _events.ScheduleEvent(EVENT_SUMMON_LAVA_SPAWN, urand(7500, 12500));
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SOUL_BURN:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        DoCast(target, SPELL_SOUL_BURN);
                    _events.Repeat(urand(3000, 4000));
                    break;
                case EVENT_SUMMON_LAVA_SPAWN:
                    DoCast(me, SPELL_SUMMON_LAVA_SPAWN);
                    _events.Repeat(urand(15000, 20000));
                    break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
    SummonList summons;
};

struct npc_majordomo_summonerAI : public ScriptedAI
{
    npc_majordomo_summonerAI(Creature* creature) : ScriptedAI(creature) 
    { 
        instance = creature->GetInstanceScript();
        summoned = false;
    }

    void Reset() override {}

    void MoveInLineOfSight(Unit* who)
    {
        if (summoned)
            return;
        if (instance->GetBossState(BOSS_MAJORDOMO_EXECUTUS) != DONE)
            return;
        if (who->GetTypeId() != TYPEID_PLAYER || me->GetDistance(who) > 120.0f)
            return;
        if (me->FindNearestCreature(NPC_MAJORDOMO_EXECUTUS, 150.0f))
            return;
        if (me->FindNearestCreature(NPC_RAGNAROS, 100.0f))
            return;
        if (Creature* majordomo = me->SummonCreature(NPC_MAJORDOMO_EXECUTUS, 847.103f, -816.153f, -229.775f, 4.344f, TEMPSUMMON_CORPSE_DESPAWN))
        {
            majordomo->setFaction(35);
            majordomo->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            majordomo->setActive(true);
            summoned = true;
        }
    }

    void UpdateAI(uint32 diff) override  {}

private:
    InstanceScript* instance;
    bool summoned;
};


enum Firewalker
{
    SPELL_FIREBLOSSOM_DAMAGE    = 19637,
    SPELL_FIREBLOSSOM           = 19636
};

class spell_firewalker_fireblossom_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_firewalker_fireblossom_AuraScript);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_FIREBLOSSOM, SPELL_FIREBLOSSOM_DAMAGE });
    }

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        PreventDefaultAction();
        if (Unit* victim = GetTarget()->GetVictim())
            GetTarget()->CastSpell(victim, SPELL_FIREBLOSSOM_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_firewalker_fireblossom_AuraScript::OnPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

void AddSC_molten_core()
{
    new CreatureAILoader<npc_core_houndAI>("npc_core_hound");
    new CreatureAILoader<npc_ancient_core_houndAI>("npc_ancient_core_hound");
    new CreatureAILoader<npc_firelordAI>("npc_firelord");
    new CreatureAILoader<npc_majordomo_summonerAI>("npc_majordomo_summoner");
    new AuraScriptLoaderEx<spell_firewalker_fireblossom_AuraScript>("spell_firewalker_fireblossom");
}
