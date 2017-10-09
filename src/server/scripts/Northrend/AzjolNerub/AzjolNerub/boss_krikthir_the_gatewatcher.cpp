#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "azjol_nerub.h"

enum Events
{
    // Krik'thir the Gatewatcher
    EVENT_SEND_GROUP            = 1,
    EVENT_SWARM,
    EVENT_MIND_FLAY,
    EVENT_FRENZY,
    EVENT_KILL_TALK,

    // Watchers - Shared
    EVENT_WEB_WRAP,
    EVENT_INFECTED_BITE,

    // Watcher Gashra
    EVENT_ENRAGE,
    // Watcher Narjil
    EVENT_BLINDING_WEBS,
    // Watcher Silthik
    EVENT_POISON_SPRAY,

    // Anubar Skirmisher
    EVENT_ANUBAR_CHARGE,
    EVENT_BACKSTAB,

    // Anubar Shadowcaster
    EVENT_SHADOW_BOLT,
    EVENT_SHADOW_NOVA,

    // Anubar Warrior
    EVENT_STRIKE,
    EVENT_CLEAVE
};

enum Spells
{
    // Krik'thir the Gatewatcher
    SPELL_SUBBOSS_AGGRO_TRIGGER = 52343,
    SPELL_SWARM                 = 52440,
    SPELL_MIND_FLAY             = 52586,
    SPELL_CURSE_OF_FATIGUE      = 52592,
    SPELL_FRENZY                = 28747,

    // Watchers - Shared
    SPELL_WEB_WRAP              = 52086,
    SPELL_WEB_WRAP_WRAPPED      = 52087,
    SPELL_INFECTED_BITE         = 52469,

    // Watcher Gashra
    SPELL_ENRAGE                = 52470,
    // Watcher Narjil
    SPELL_BLINDING_WEBS         = 52524,
    // Watcher Silthik
    SPELL_POISON_SPRAY          = 52493,

    // Anub'ar Warrior
    SPELL_CLEAVE                = 49806,
    SPELL_STRIKE                = 52532,

    // Anub'ar Skirmisher
    SPELL_CHARGE                = 52538,
    SPELL_BACKSTAB              = 52540,
    SPELL_FIXTATE_TRIGGER       = 52536,
    SPELL_FIXTATE_TRIGGERED     = 52537,

    // Anub'ar Shadowcaster
    SPELL_SHADOW_BOLT           = 52534,
    SPELL_SHADOW_NOVA           = 52535,

    // Skittering Infector
    SPELL_ACID_SPLASH           = 52446
};

enum Data
{
    DATA_PET_GROUP
};

enum Actions
{
    ACTION_GASHRA_DIED,
    ACTION_NARJIL_DIED,
    ACTION_SILTHIK_DIED,
    ACTION_WATCHER_ENGAGED,
    ACTION_PET_ENGAGED,
    ACTION_PET_EVADE
};

enum Yells
{
    SAY_AGGRO                   = 0,
    SAY_SLAY,
    SAY_DEATH,
    SAY_SWARM,
    SAY_PREFIGHT,
    SAY_SEND_GROUP
};

struct boss_krik_thirAI : public BossAI
{
    boss_krik_thirAI(Creature* creature) : BossAI(creature, DATA_KRIKTHIR_THE_GATEWATCHER_EVENT) {}

    void SummonAdds()
    {
        if (instance->GetBossState(DATA_KRIKTHIR_THE_GATEWATCHER_EVENT) == DONE)
            return;

        for (uint8 i = 1; i <= 3; ++i)
        {
            std::list<TempSummon*> adds;
            me->SummonCreatureGroup(i, &adds);
            for (TempSummon* add : adds)
                if (add->IsAIEnabled)
                    add->AI()->SetData(DATA_PET_GROUP, i);
        }
    }

    void Reset() override
    {
        _Reset();
        _hadFrenzy = false;
        _petsInCombat = false;
        _greet = false;
        _watchersActive = 0;
        SummonAdds();
    }

    void KilledUnit(Unit* victim) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_SLAY);
            events.ScheduleEvent(EVENT_KILL_TALK, 6000);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (auto door = me->FindNearestGameObject(192395, 100.0f))
            door->AddObjectToRemoveList();

        summons.clear();
        _JustDied();
        Talk(SAY_DEATH);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _petsInCombat = false;
        summons.DoZoneInCombat();

        events.CancelEvent(EVENT_SEND_GROUP);
        events.ScheduleEvent(EVENT_SWARM, 5000);
        events.ScheduleEvent(EVENT_MIND_FLAY, urand(1000, 3000));

        _EnterCombat();
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (!_greet)
        {
            _greet = true;
            Talk(SAY_PREFIGHT);
        }

        ScriptedAI::MoveInLineOfSight(who);
    }

    void EnterEvadeMode() override
    {
        summons.DespawnAll();
        _DespawnAtEvade();
    }

    void DoAction(int32 action) override
    {
        switch (action)
        {
            case ACTION_GASHRA_DIED:
            case ACTION_NARJIL_DIED:
            case ACTION_SILTHIK_DIED:
                if (!_watchersActive) // something is wrong
                {
                    EnterEvadeMode();
                    return;
                }
                if (!--_watchersActive) // if there are no watchers currently in combat...
                    events.RescheduleEvent(EVENT_SEND_GROUP, 5000); // ...send the next watcher after the targets sooner
                break;
            case ACTION_WATCHER_ENGAGED:
                ++_watchersActive;
                break;
            case ACTION_PET_ENGAGED:
                if (_petsInCombat || me->IsInCombat())
                    break;
                _petsInCombat = true;
                Talk(SAY_AGGRO);
                events.ScheduleEvent(EVENT_SEND_GROUP, 70000);
                break;
            case ACTION_PET_EVADE:
                EnterEvadeMode();
                break;

        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() && !_petsInCombat)
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;
                
        if (me->HealthBelowPct(10) && !_hadFrenzy)
        {
            _hadFrenzy = true;
            events.ScheduleEvent(EVENT_FRENZY, 1000);
        }

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SEND_GROUP:
                    DoCastAOE(SPELL_SUBBOSS_AGGRO_TRIGGER, true);
                    events.Repeat(70000);
                    break;
                case EVENT_SWARM:
                    DoCastAOE(SPELL_SWARM);
                    Talk(SAY_SWARM);
                    break;
                case EVENT_MIND_FLAY:
                    DoCastVictim(SPELL_MIND_FLAY);
                    events.Repeat(urand(9000, 11000));
                    break;
                case EVENT_FRENZY:
                    DoCastSelf(SPELL_FRENZY);
                    DoCastAOE(SPELL_CURSE_OF_FATIGUE);
                    events.Repeat(15000);
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    void SpellHit(Unit* /*whose*/, SpellInfo const* spell) override
    {
        if (spell->Id == SPELL_SUBBOSS_AGGRO_TRIGGER)
            DoZoneInCombat();
    }

    void SpellHitTarget(Unit* /*who*/, SpellInfo const* spell) override
    {
        if (spell->Id == SPELL_SUBBOSS_AGGRO_TRIGGER)
            Talk(SAY_SEND_GROUP);
    }

private:
    bool _greet;
    bool _hadFrenzy;
    bool _petsInCombat;
    uint8 _watchersActive;
};

struct npc_gatewatcher_petAI : public ScriptedAI
{
    npc_gatewatcher_petAI(Creature* creature, bool isWatcher) : ScriptedAI(creature), _instance(creature->GetInstanceScript()), _petGroup(0), _isWatcher(isWatcher) 
    { 
        if (me->IsSummon())
            me->SetNoCallAssistance(true);
    }

    virtual void _EnterCombat() = 0;
    void EnterCombat(Unit* who) override
    {
        if (!me->IsSummon())
        {
            _EnterCombat();
            return;
        }

        if (_isWatcher)
        {
            _isWatcher = false;
            if (TempSummon* meSummon = me->ToTempSummon())
                if (Creature* summoner = meSummon->GetSummonerCreatureBase())
                    summoner->AI()->DoAction(ACTION_WATCHER_ENGAGED);
        }

        std::list<Creature*> others;

        for (int i = 28729; i <= 28734; ++i)
            me->GetCreatureListWithEntryInGrid(others, i, 100.0f);

        for (Creature* other : others)
            if (other->IsAIEnabled)
                if (other->AI()->GetData(DATA_PET_GROUP) == _petGroup)
                    other->AI()->AttackStart(who);

        if (TempSummon* meSummon = me->ToTempSummon())
            if (Creature* summoner = meSummon->GetSummonerCreatureBase())
                summoner->AI()->DoAction(ACTION_PET_ENGAGED);

        _EnterCombat();
        ScriptedAI::EnterCombat(who);
    }

    void SetData(uint32 data, uint32 value) override
    {
        if (data == DATA_PET_GROUP)
            _petGroup = value;
    }

    uint32 GetData(uint32 data) const override
    {
        if (data == DATA_PET_GROUP)
            return _petGroup;
        return 0;
    }

    void SpellHit(Unit* /*whose*/, SpellInfo const* spell) override
    {
        if (spell->Id == SPELL_SUBBOSS_AGGRO_TRIGGER)
            DoZoneInCombat();
    }

    void EnterEvadeMode() override
    {
        if (TempSummon* meSummon = me->ToTempSummon())
        {
            if (Creature* summoner = meSummon->GetSummonerCreatureBase())
                summoner->AI()->DoAction(ACTION_PET_EVADE);
            else
                me->DespawnOrUnsummon();
            return;
        }

        ScriptedAI::EnterEvadeMode();
    }

    EventMap _events;
    InstanceScript* _instance;
    uint32 _petGroup;
    bool _isWatcher;
};

struct npc_watcher_gashraAI : public npc_gatewatcher_petAI
{
    npc_watcher_gashraAI(Creature* creature) : npc_gatewatcher_petAI(creature, true) { }

    void Reset() override
    {
        _events.Reset();
    }

    void _EnterCombat() override
    {
        _events.ScheduleEvent(EVENT_ENRAGE, urand(3000, 5000));
        _events.ScheduleEvent(EVENT_WEB_WRAP, urand(16000, 19000));
        _events.ScheduleEvent(EVENT_INFECTED_BITE, urand(7000, 11000));
    }

    void JustDied(Unit* /*killer*/) override
    {
        Creature* krikthir = _instance->GetCreature(DATA_KRIKTHIR_THE_GATEWATCHER_EVENT);
        if (krikthir && krikthir->IsAlive() && krikthir->IsAIEnabled)
            krikthir->AI()->DoAction(ACTION_GASHRA_DIED);
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
                case EVENT_ENRAGE:
                    DoCastSelf(SPELL_ENRAGE);
                    _events.Repeat(urand(12000, 20000));
                    break;
                case EVENT_WEB_WRAP:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f))
                        DoCast(target, SPELL_WEB_WRAP);
                    _events.Repeat(urand(13000, 19000));
                    break;
                case EVENT_INFECTED_BITE:
                    DoCastVictim(SPELL_INFECTED_BITE);
                    _events.Repeat(urand(23000, 27000));
                    break;
                default:
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

struct npc_watcher_narjilAI : public npc_gatewatcher_petAI
{
    npc_watcher_narjilAI(Creature* creature) : npc_gatewatcher_petAI(creature, true) { }

    void Reset() override
    {
        _events.Reset();
    }

    void _EnterCombat() override
    {
        _events.ScheduleEvent(EVENT_BLINDING_WEBS, urand(13000, 18000));
        _events.ScheduleEvent(EVENT_WEB_WRAP, urand(3000, 5000));
        _events.ScheduleEvent(EVENT_INFECTED_BITE, urand(7000, 11000));
    }

    void JustDied(Unit* /*killer*/) override
    {
        Creature* krikthir = _instance->GetCreature(DATA_KRIKTHIR_THE_GATEWATCHER_EVENT);
        if (krikthir && krikthir->IsAlive() && krikthir->IsAIEnabled)
            krikthir->AI()->DoAction(ACTION_NARJIL_DIED);
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
                case EVENT_BLINDING_WEBS:
                    DoCastVictim(SPELL_BLINDING_WEBS);
                    _events.Repeat(urand(23000, 27000));
                    break;
                case EVENT_WEB_WRAP:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true, -SPELL_WEB_WRAP))
                        DoCast(target, SPELL_WEB_WRAP);
                    _events.Repeat(urand(13000, 19000));
                    break;
                case EVENT_INFECTED_BITE:
                    DoCastVictim(SPELL_INFECTED_BITE);
                    _events.Repeat(urand(20000, 25000));
                    break;
                default:
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

struct npc_watcher_silthikAI : public npc_gatewatcher_petAI
{
    npc_watcher_silthikAI(Creature* creature) : npc_gatewatcher_petAI(creature, true) { }

    void Reset() override
    {
        _events.Reset();
    }

    void _EnterCombat() override
    {
        _events.ScheduleEvent(EVENT_POISON_SPRAY, urand(16000, 19000));
        _events.ScheduleEvent(EVENT_WEB_WRAP, urand(7000, 11000));
        _events.ScheduleEvent(EVENT_INFECTED_BITE, urand(3000, 5000));
    }

    void JustDied(Unit* /*killer*/) override
    {
        Creature* krikthir = _instance->GetCreature(DATA_KRIKTHIR_THE_GATEWATCHER_EVENT);
        if (krikthir && krikthir->IsAlive() && krikthir->IsAIEnabled)
            krikthir->AI()->DoAction(ACTION_SILTHIK_DIED);
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
                case EVENT_POISON_SPRAY:
                    DoCastVictim(SPELL_POISON_SPRAY);
                    _events.Repeat(urand(13000, 19000));
                    break;
                case EVENT_WEB_WRAP:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        DoCast(target, SPELL_WEB_WRAP);
                    _events.Repeat(urand(13000, 17000));
                    break;
                case EVENT_INFECTED_BITE:
                    DoCastVictim(SPELL_INFECTED_BITE);
                    _events.Repeat(urand(20000, 24000));
                    break;
                default:
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

struct npc_anub_ar_warriorAI : public npc_gatewatcher_petAI
{
    npc_anub_ar_warriorAI(Creature* creature) : npc_gatewatcher_petAI(creature, false) { }

    void Reset() override
    {
        _events.Reset();
    }

    void _EnterCombat() override
    {
        _events.ScheduleEvent(EVENT_CLEAVE, urand(7000, 9000));
        _events.ScheduleEvent(EVENT_STRIKE, urand(5000, 10000));
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
                case EVENT_CLEAVE:
                    DoCastVictim(SPELL_CLEAVE);
                    _events.Repeat(urand(10000, 16000));
                    break;
                case EVENT_STRIKE:
                    DoCastVictim(SPELL_STRIKE);
                    _events.Repeat(urand(15000, 19000));
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }
};

struct npc_anub_ar_skirmisherAI : public npc_gatewatcher_petAI
{
    npc_anub_ar_skirmisherAI(Creature* creature) : npc_gatewatcher_petAI(creature, false) { }

    void Reset() override
    {
        _events.Reset();
    }

    void _EnterCombat() override
    {
        _events.ScheduleEvent(EVENT_ANUBAR_CHARGE, urand(6000, 8000));
        _events.ScheduleEvent(EVENT_BACKSTAB, urand(7000, 9000));
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
                case EVENT_ANUBAR_CHARGE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        DoCast(target, SPELL_CHARGE);
                    _events.Repeat(urand(20000, 25000));
                    break;
                case EVENT_BACKSTAB:
                    if (me->GetVictim() && me->GetVictim()->isInBack(me))
                        DoCastVictim(SPELL_BACKSTAB);
                    _events.Repeat(urand(10000, 13000));
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    void SpellHitTarget(Unit* target, SpellInfo const* spell) override
    {
        if (spell->Id == SPELL_CHARGE && target)
            DoCast(target, SPELL_FIXTATE_TRIGGER);
    }
};

struct npc_anub_ar_shadowcasterAI : public npc_gatewatcher_petAI
{
    npc_anub_ar_shadowcasterAI(Creature* creature) : npc_gatewatcher_petAI(creature, false) { }

    void Reset() override
    {
        _events.Reset();
    }

    void _EnterCombat() override
    {
        _events.ScheduleEvent(EVENT_SHADOW_BOLT, 4000);
        _events.ScheduleEvent(EVENT_SHADOW_NOVA, urand(10000, 14000));
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
                case EVENT_SHADOW_BOLT:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        DoCast(target, SPELL_SHADOW_BOLT);
                    _events.Repeat(urand(2000, 4000));
                    break;
                case EVENT_SHADOW_NOVA:
                    DoCastVictim(SPELL_SHADOW_NOVA);
                    _events.Repeat(urand(10000, 16000));
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }
};

struct npc_skittering_swarmerAI : public ScriptedAI
{
    npc_skittering_swarmerAI(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        ScriptedAI::InitializeAI();
        if (Creature* gatewatcher = me->GetInstanceScript()->GetCreature(DATA_KRIKTHIR_THE_GATEWATCHER_EVENT))
        {
            if (Unit* target = gatewatcher->getAttackerForHelper())
                AttackStart(target);

            if (gatewatcher->IsAIEnabled)
                gatewatcher->AI()->JustSummoned(me);
        }
    }
};

struct npc_skittering_infectorAI : public ScriptedAI
{
    npc_skittering_infectorAI(Creature* creature) : ScriptedAI(creature) { }

    void InitializeAI() override
    {
        ScriptedAI::InitializeAI();
        if (Creature* gatewatcher = me->GetInstanceScript()->GetCreature(DATA_KRIKTHIR_THE_GATEWATCHER_EVENT))
        {
            if (Unit* target = gatewatcher->getAttackerForHelper())
                AttackStart(target);

            if (gatewatcher->IsAIEnabled)
                gatewatcher->AI()->JustSummoned(me);
        }
    }

    void JustDied(Unit* killer) override
    {
        DoCastAOE(SPELL_ACID_SPLASH);
        ScriptedAI::JustDied(killer);
    }
};

struct npc_gatewatcher_web_wrapAI : public NullCreatureAI
{
    npc_gatewatcher_web_wrapAI(Creature* creature) : NullCreatureAI(creature) { }

    void JustDied(Unit* /*killer*/) override
    {
        if (TempSummon* meSummon = me->ToTempSummon())
            if (Unit* summoner = meSummon->GetSummoner())
                summoner->RemoveAurasDueToSpell(SPELL_WEB_WRAP_WRAPPED);
    }
};

class spell_gatewatcher_subboss_trigger_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_gatewatcher_subboss_trigger_SpellScript)

    void HandleTargets(std::list<WorldObject*>& targetList)
    {
        // Remove any Watchers that are already in combat
        auto it = targetList.begin();
        while (it != targetList.end())
        {
            if (Creature* creature = (*it)->ToCreature())
                if (creature->IsAlive() && !creature->IsInCombat())
                {
                    ++it;
                    continue;
                }
            it = targetList.erase(it);
        }

        // Default to Krik'thir himself if he isn't engaged
        WorldObject* target = nullptr;
        if (GetCaster() && !GetCaster()->IsInCombat())
            target = GetCaster();
        // Unless there are Watchers that aren't engaged yet
        if (!targetList.empty())
        {
            // If there are, pick one of them at random
            target = Trinity::Containers::SelectRandomContainerElement(targetList);
        }
        // And hit only that one
        targetList.clear();
        if (target)
            targetList.push_back(target);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gatewatcher_subboss_trigger_SpellScript::HandleTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
    }
};

class spell_anub_ar_skirmisher_fixtate_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_anub_ar_skirmisher_fixtate_SpellScript)

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({ SPELL_FIXTATE_TRIGGERED });
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            target->CastSpell(GetCaster(), SPELL_FIXTATE_TRIGGERED, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_anub_ar_skirmisher_fixtate_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class spell_gatewatcher_web_wrap_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_gatewatcher_web_wrap_AuraScript)

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({ SPELL_WEB_WRAP_WRAPPED });
    }

    void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_EXPIRE)
            return;

        if (Unit* target = GetTarget())
            target->CastSpell(target, SPELL_WEB_WRAP_WRAPPED, true);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_gatewatcher_web_wrap_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_MOD_ROOT, AURA_EFFECT_HANDLE_REAL);
    }
};

class achievement_watch_him_die : public AchievementCriteriaScript
{
    public:
        achievement_watch_him_die() : AchievementCriteriaScript("achievement_watch_him_die") { }

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            if (!target)
                return false;

            InstanceScript* instance = target->GetInstanceScript();
            if (!instance)
                return false;

            for (auto watcherData : {DATA_WATCHER_GASHRA, DATA_WATCHER_NARJIL, DATA_WATCHER_SILTHIK})
            {
                if (Creature* watcher = instance->GetCreature(watcherData))
                    if (watcher->IsAlive())
                        continue;
                return false;
            }

            return true;
    }
};

void AddSC_boss_krik_thir()
{
    new CreatureAILoader<boss_krik_thirAI>("boss_krik_thir");
    new CreatureAILoader<npc_watcher_gashraAI>("npc_watcher_gashra");
    new CreatureAILoader<npc_watcher_narjilAI>("npc_watcher_narjil");
    new CreatureAILoader<npc_watcher_silthikAI>("npc_watcher_silthik");
    new CreatureAILoader<npc_anub_ar_warriorAI>("npc_anub_ar_warrior");
    new CreatureAILoader<npc_anub_ar_skirmisherAI>("npc_anub_ar_skirmisher");
    new CreatureAILoader<npc_anub_ar_shadowcasterAI>("npc_anub_ar_shadowcaster");
    new CreatureAILoader<npc_skittering_swarmerAI>("npc_skittering_swarmer");
    new CreatureAILoader<npc_skittering_infectorAI>("npc_skittering_infector");
    new CreatureAILoader<npc_gatewatcher_web_wrapAI>("npc_gatewatcher_web_wrap");
    new SpellScriptLoaderEx<spell_gatewatcher_subboss_trigger_SpellScript>("spell_gatewatcher_subboss_trigger");
    new SpellScriptLoaderEx<spell_anub_ar_skirmisher_fixtate_SpellScript>("spell_anub_ar_skirmisher_fixtate");
    new AuraScriptLoaderEx<spell_gatewatcher_web_wrap_AuraScript>("spell_gatewatcher_web_wrap");
    new achievement_watch_him_die();
}
