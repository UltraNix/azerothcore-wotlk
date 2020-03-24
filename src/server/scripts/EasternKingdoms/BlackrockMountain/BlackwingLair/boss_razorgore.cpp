

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "blackwing_lair.h"
#include "Player.h"
#include "GameObjectAI.h"

enum RazorgoreSays
{
    // Razorgore
    SAY_EGGS_BROKEN,
    SAY_WIPE,
    EMOTE_ORB_DEACTIVATE,
    EMOTE_RUN_OFF,

    // Grethok
    SAY_GRETHOK_AGGRO           = 0
};

enum RazorgoreSpells
{
    // Phase 1
    SPELL_MIND_EXHAUSTION       = 23958,
    SPELL_POSSESS               = 19832,
    SPELL_POSSESS_BEAM          = 23014,
    SPELL_DESTROY_EGG           = 19873,
    SPELL_EXPLOSION             = 20038,

    // Phase 2
    SPELL_WAR_STOMP             = 24375,
    SPELL_FIREBALL_VOLLEY       = 22425,
    SPELL_CONFLAGRATION         = 23023,
    SPELL_CLEAVE                = 19632,

    // Grethok
    SPELL_DOMINATE_MIND         = 14515,
    SPELL_POLYMORPH             = 22274,
    SPELL_ARCANE_MISSILES       = 22272,
    SPELL_SLOW                  = 13747
};

enum RazorgoreEvents
{
    EVENT_WAR_STOMP             = 1,
    EVENT_FIREBALL_VOLLEY,
    EVENT_CONFLAGRATION,
    EVENT_CLEAVE,
    EVENT_CHECK_PLAYERS,

    // Orb
    EVENT_PHASE_2               = 1,
    EVENT_SPAWN_ADDS,

    // Grethok
    EVENT_ARCANE_MISSILES       = 1,
    EVENT_POLYMORPH,
    EVENT_DOMINATE_MIND,
    EVENT_SLOW
};

enum RazorgorePhases
{
    PHASE_FIRST                 = 1,
    PHASE_SECOND
};

enum RazorgoreMisc
{
    // Orb
    ACTION_EGG_DESTROYED        = 1,
    ACTION_CAST_TRIGGER,
    ACTION_BEGIN_ENCOUNTER,

    // Razorgore
    ACTION_START_PHASE_2        = 1,

    SUMMON_GROUP_GRETHOK        = 1
};

static const std::vector<Position> summonPositions =
{
    { -7661.207520f, -1043.268188f, 407.199554f, 6.280452f },
    { -7644.145020f, -1065.628052f, 407.204956f, 0.501492f },
    { -7624.260742f, -1095.196899f, 407.205017f, 0.544694f },
    { -7608.501953f, -1116.077271f, 407.199921f, 0.816443f },
    { -7531.841797f, -1063.765381f, 407.199615f, 2.874187f },
    { -7547.319336f, -1040.971924f, 407.205078f, 3.789175f },
    { -7568.547852f, -1013.112488f, 407.204926f, 3.773467f },
    { -7584.175781f, -989.6691289f, 407.199585f, 4.527447f }
};

static const std::vector<uint32> summonEntries = { 12422, 12458, 12416, 12420, 12459 };

struct boss_razorgoreAI : public BossAI
{
    boss_razorgoreAI(Creature* creature) : BossAI(creature, BOSS_RAZORGORE), _explosion(false) { }

    void Reset() override
    {
        _Reset();
        _explosion = false;
        me->SummonCreatureGroup(SUMMON_GROUP_GRETHOK);
        if (GameObject* orb = me->FindNearestGameObject(GO_RAZORGORE_ORB, 250.0f))
            if (orb->AI())
                orb->AI()->DoAction(ACTION_CAST_TRIGGER);

        std::list<GameObject*> eggs;
        me->GetGameObjectListWithEntryInGrid(eggs, GO_RAZORGORE_EGG, 150.f);
        for (GameObject* egg : eggs)
            egg->SetGoState(GO_STATE_READY);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        if (GameObject* orb = me->FindNearestGameObject(GO_RAZORGORE_ORB, 250.0f))
            if (orb->AI())
                orb->AI()->DoAction(ACTION_BEGIN_ENCOUNTER);

        summons.DoZoneInCombat();
        events.SetPhase(PHASE_FIRST);
        events.ScheduleEvent(EVENT_CHECK_PLAYERS, 5s);
        events.ScheduleEvent(EVENT_CLEAVE, 15s);
        events.ScheduleEvent(EVENT_WAR_STOMP, 35s);
        events.ScheduleEvent(EVENT_FIREBALL_VOLLEY, 7s);
        events.ScheduleEvent(EVENT_CONFLAGRATION, 12s);
    }

    void EnterEvadeMode() override
    {
        _DespawnAtEvade(10);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*mask*/) override
    {
        if (damage >= me->GetHealth() && events.IsInPhase(PHASE_FIRST))
        {
            damage = me->GetHealth() - 1;
            if (!_explosion)
            {
                _explosion = true;
                //DoCastSelf(SPELL_EXPLOSION);
                for (auto const& ref : instance->instance->GetPlayers())
                    if (Player* player = ref.GetSource())
                        me->Kill(me, player, true, BASE_ATTACK, sSpellMgr->GetSpellInfo(SPELL_EXPLOSION));
                Talk(SAY_WIPE);
                EnterEvadeMode();
            }
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (events.IsInPhase(PHASE_SECOND))
            _JustDied();
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_START_PHASE_2 && events.IsInPhase(PHASE_FIRST))
        {
            Talk(EMOTE_ORB_DEACTIVATE);
            Talk(EMOTE_RUN_OFF);
            events.SetPhase(PHASE_SECOND);
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_WAR_STOMP:
                DoCastSelf(SPELL_WAR_STOMP);
                events.Repeat(15s, 25s);
                break;
            case EVENT_FIREBALL_VOLLEY:
                DoCastSelf(SPELL_FIREBALL_VOLLEY);
                events.Repeat(12s, 15s);
                break;
            case EVENT_CONFLAGRATION:
                DoCastSelf(SPELL_CONFLAGRATION);
                events.Repeat(30s);
                break;
            case EVENT_CLEAVE:
                DoCastVictim(SPELL_CLEAVE);
                events.Repeat(5s, 10s);
                break;
            case EVENT_CHECK_PLAYERS:
                if (!SelectTargetFromPlayerList(100.0f))
                    EnterEvadeMode();
                events.Repeat(5s);
                break;
            default:
                break;
        }
    }

    private:
        bool _explosion;
};

struct npc_grethok_the_controllerAI : public ScriptedAI
{
    npc_grethok_the_controllerAI(Creature* creature) : ScriptedAI(creature)
    {
        // Visual
        me->SetUInt32Value(UNIT_CHANNEL_SPELL, SPELL_POSSESS_BEAM);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.Reset();
        me->SetUInt32Value(UNIT_CHANNEL_SPELL, 0);
        Talk(SAY_GRETHOK_AGGRO);
        if (InstanceScript* instance = me->GetInstanceScript())
            if (Creature* razorgore = instance->GetCreature(BOSS_RAZORGORE))
                DoZoneInCombat(razorgore, 250.0f);
        _events.ScheduleEvent(EVENT_ARCANE_MISSILES, 1s);
        _events.ScheduleEvent(EVENT_POLYMORPH, 15s, 20s);
        _events.ScheduleEvent(EVENT_DOMINATE_MIND, 20s, 30s);
        _events.ScheduleEvent(EVENT_SLOW, 5s, 10s);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_ARCANE_MISSILES:
                    DoCastVictim(SPELL_ARCANE_MISSILES);
                    _events.Repeat(8s, 10s);
                    break;
                case EVENT_POLYMORPH:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true, -SPELL_POLYMORPH))
                        DoCast(target, SPELL_POLYMORPH);
                    _events.Repeat(15s, 20s);
                    break;
                case EVENT_DOMINATE_MIND:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 20.0f, true, -SPELL_DOMINATE_MIND))
                        DoCast(target, SPELL_DOMINATE_MIND);
                    _events.Repeat(20s, 25s);
                    break;
                case EVENT_SLOW:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true, -SPELL_SLOW))
                        DoCast(target, SPELL_SLOW);
                    _events.Repeat(5s, 15s);
                    break;
                default:
                    break;
            }

            if (me->IsCasting())
                return;
        }

        DoMeleeAttackIfReady();
    }

    private:
        EventMap _events;
};

struct go_orb_of_dominationAI : public GameObjectAI
{
    go_orb_of_dominationAI(GameObject* go) : GameObjectAI(go), _instance(go->GetInstanceScript()), _eggCounter(0) { }

    Creature* GetOrSpawnOrbTrigger() const
    {
        if (Creature* trigger = go->FindNearestCreature(12999, 10.0f))
            return trigger;
        else
            return go->SummonCreature(12999, { -7615.f, -1026.072f, 413.4f, 5.28f });
    }

    auto GetRazorgore() const
    {
        return _instance ? _instance->GetCreature(BOSS_RAZORGORE) : nullptr;
    }

    void DoAction(int32 actionId) override
    {
        switch (actionId)
        {
            case ACTION_EGG_DESTROYED:
                if (++_eggCounter >= 30)
                {
                    if (Creature* razorgore = GetRazorgore())
                    {
                        razorgore->RemoveAllAuras();
                        razorgore->SetFullHealth(); // @todo find a spell
                        go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
                        for (auto const guid : _summonGUIDs)
                        {
                            if (Creature* summon = ObjectAccessor::GetCreature(*go, guid))
                            {
                                if (summon->IsAlive())
                                {
                                    summon->SetPassive();
                                    summon->ClearInCombat();
                                    summon->GetMotionMaster()->MovePoint(1, { -7553.7f, -1023.975f, 408.5f });
                                }
                            }
                        }

                        _events.CancelEvent(EVENT_SPAWN_ADDS);
                        _events.ScheduleEvent(EVENT_PHASE_2, 1s);
                    }
                }
                break;
            case ACTION_CAST_TRIGGER:
                // workaround, needs proper gameobject casting
                if (Creature* trigger = GetOrSpawnOrbTrigger())
                    trigger->CastSpell(static_cast<Unit*>(nullptr), SPELL_POSSESS_BEAM);
                _eggCounter = 0;
                go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
                while (!_summonGUIDs.empty())
                {
                    if (Creature* summon = ObjectAccessor::GetCreature(*go, _summonGUIDs.back()))
                        summon->DespawnOrUnsummon();
                    _summonGUIDs.pop_back();
                }
                _events.Reset();
                break;
            case ACTION_BEGIN_ENCOUNTER:
                _events.ScheduleEvent(EVENT_SPAWN_ADDS, 45s);
                break;
            default:
                break;
        }

    }

    bool GossipHello(Player* player, bool /*reportUse*/) override
    {
        if (!_instance || player->HasAura(SPELL_MIND_EXHAUSTION))
            return false;

        if (_instance->GetBossState(BOSS_RAZORGORE) != IN_PROGRESS)
            return false;

        if (Creature* razorgore = GetRazorgore())
            if (!razorgore->HasAura(SPELL_POSSESS))
                player->CastSpell(static_cast<Unit*>(nullptr), SPELL_POSSESS, true);

        return true;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!_instance || _instance->GetBossState(BOSS_RAZORGORE) != IN_PROGRESS)
            return;

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_PHASE_2:
                    if (Creature* razorgore = GetRazorgore())
                        if (razorgore->IsAIEnabled)
                            razorgore->AI()->DoAction(ACTION_START_PHASE_2);
                    break;
                case EVENT_SPAWN_ADDS:
                    Trinity::Containers::Erase_if(_summonGUIDs, [this](uint64 const guid) { return !ObjectAccessor::GetCreature(*go, guid); });
                    if (Creature* razorgore = GetRazorgore())
                        for (uint8 i = urand(2, 5); i > 0; --i)
                            if (Creature* summon = go->SummonCreature(Trinity::Containers::SelectRandomContainerElement(summonEntries), Trinity::Containers::SelectRandomContainerElement(summonPositions)))
                            {
                                _summonGUIDs.emplace_back(summon->GetGUID());
                                if (summon->IsAIEnabled)
                                    summon->AI()->AttackStart(razorgore);
                            }

                    _events.Repeat(12s, 17s);
                    break;
                default:
                    break;
            }

        }
    }

    private:
        std::vector<uint64> _summonGUIDs;
        InstanceScript* _instance;
        EventMap _events;
        uint8 _eggCounter;
};

// 19873 - Destroy Egg
class spell_razorgore_destroy_egg_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_razorgore_destroy_egg_SpellScript);

    bool Load() override
    {
        _eggGUID = 0;
        return GetCaster()->GetEntry() == NPC_RAZORGORE;
    }

    SpellCastResult CheckTarget()
    {
        std::list<GameObject*> eggs;
        GetCaster()->GetGameObjectListWithEntryInGrid(eggs, GO_RAZORGORE_EGG, 10.0f);
        for (GameObject* egg : eggs)
            if (egg->GetGoState() == GO_STATE_READY)
            {
                _eggGUID = egg->GetGUID();
                return SPELL_CAST_OK;
            }

        return SPELL_FAILED_BAD_TARGETS;
    }

    void HandleOnHit()
    {
        if (Creature* razorgore = GetCaster()->ToCreature())
        {
            if (GameObject* egg = ObjectAccessor::GetGameObject(*razorgore, _eggGUID))
            {
                if (GameObject* orb = razorgore->FindNearestGameObject(GO_RAZORGORE_ORB, 250.0f))
                {
                    if (razorgore->IsAIEnabled && orb->AI())
                    {
                        if (urand(0, 1))
                            razorgore->AI()->Talk(SAY_EGGS_BROKEN);

                        orb->AI()->DoAction(ACTION_EGG_DESTROYED);
                        egg->SetGoState(GO_STATE_ACTIVE);
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_razorgore_destroy_egg_SpellScript::CheckTarget);
        OnHit += SpellHitFn(spell_razorgore_destroy_egg_SpellScript::HandleOnHit);
    }

    uint64 _eggGUID;
};

// 19832 - Possess
class spell_razorgore_possess_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_razorgore_possess_AuraScript);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->GetMotionMaster()->MoveIdle();
        GetTarget()->StopMoving();
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->IsPlayer())
                caster->CastSpell(caster, SPELL_MIND_EXHAUSTION, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectRemoveFn(spell_razorgore_possess_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_POSSESS, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_razorgore_possess_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_POSSESS, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_boss_razorgore()
{
    new CreatureAILoader<boss_razorgoreAI>("boss_razorgore");
    new CreatureAILoader<npc_grethok_the_controllerAI>("npc_grethok_the_controller");
    new GameObjectAILoader<go_orb_of_dominationAI>("go_orb_of_domination");
    new SpellScriptLoaderEx<spell_razorgore_destroy_egg_SpellScript>("spell_razorgore_destroy_egg");
    new AuraScriptLoaderEx<spell_razorgore_possess_AuraScript>("spell_razorgore_possess");
}
