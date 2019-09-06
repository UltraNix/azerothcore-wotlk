#include "ScriptMgr.h"
#include "Group.h"

constexpr uint32 PORTAL_DEFENDERS_COUNT = 8;

const Position PortalDefendersPosition[PORTAL_DEFENDERS_COUNT] =
{
    {-6549.03f, -1269.19f, 136.23f},
    {-6550.34f, -1271.89f, 136.48f},
    {-6551.65f, -1274.58f, 136.74f},
    {-6552.69f, -1277.29f, 136.87f},
    {-6554.27f, -1279.98f, 136.97f},
    {-6548.95f, -1275.89f, 136.89f},
    {-6550.26f, -1278.59f, 137.12f},
    {-6547.64f, -1273.19f, 136.61f},
};

constexpr uint32 VISUAL_FIRE_TRIGGERS_COUNT = 9;

const Position VisualFireTriggersPosition[VISUAL_FIRE_TRIGGERS_COUNT] =
{
    {-6553.73f, -1273.15f, 136.45f},
    {-6551.44f, -1284.61f, 138.20f},
    {-6543.36f, -1271.97f, 136.52f},
    {-6539.14f, -1274.66f, 136.43f},
    {-6547.22f, -1287.30f, 138.59f},
    {-6543.01f, -1289.99f, 138.80f},
    {-6534.77f, -1277.58f, 136.15f},
    {-6530.72f, -1280.05f, 136.15f},
    {-6538.80f, -1292.69f, 139.05f},
};

constexpr uint32 VISUAL_THUNDER_TARGETS_COUNT = 3;

const Position VisualThunderTargetsPosition[VISUAL_THUNDER_TARGETS_COUNT] =
{
    {-6543.54f, -1275.37f, 136.70f},
    {-6541.31f, -1284.54f, 137.86f},
    {-6534.05f, -1278.52f, 136.21f},
};

const Position VisualThunderTriggerPosition = { -6552.09f, -1274.44f, 136.71f };

enum Events
{
    EVENT_START_EVENT       = 1,
    EVENT_START_EVENT2      = 2,
    EVENT_START_EVENT3      = 3,
    EVENT_NEW_DEFENDER      = 4,
    EVENT_REVIVE_ATTACKER   = 5,
    EVENT_EARTH_QUAKE       = 6,
    EVENT_VISUAL_FIRE       = 7,
    EVENT_VISUAL_THUNDER    = 8,
    EVENT_VISUAL            = 9,
    EVENT_NEXT_VISUAL_FIRE  = 10,
    EVENT_RESET_EVENT       = 11,
};

enum WorldzoneData
{
    DATA_DEAD_ATTACKER          = 1,
    DATA_EVENT_STARTED          = 2,
};

enum NPCs
{
    NPC_EVENT_TRIGGER           = 300000,
    NPC_DEFENDER                = 300001,
    NPC_ATTACKER                = 300002,
    NPC_ATTACKER_LEADER         = 300003,
    NPC_VISUAL_FIRE_TRIGGER     = 300004,
    NPC_VISUAL_THUNDER_TARGET   = 300005,
    NPC_VISUAL_THUNDER_TRIGGER  = 300006,
};

enum Spells
{
    SPELL_REVIVE_VISUAL     = 70088,
    SPELL_FIRE_VISUAL       = 74394,
    SPELL_EARTH_QUAKE       = 33919,
    SPELL_THUNDER           = 23011,
    SPELL_FIRE_NOVA         = 23462,
};

enum Misc
{
    DIABLO_MAP_ID = 249
};

class worldzone_searing_gorge : public WorldMapZoneScript
{
public:
    worldzone_searing_gorge() : WorldMapZoneScript("worldzone_searing_gorge") { }

    struct worldzone_searing_gorge_WorldMapZoneScript : public WorldZoneScript
    {
        worldzone_searing_gorge_WorldMapZoneScript() : WorldZoneScript() { }

        void Initialize() override
        {
            eventStarted = false;
            visualFireIndex = 0;
        }

        void OnCreatureCreate(Creature* creature) override
        {
            switch (creature->GetEntry())
            {
            case NPC_EVENT_TRIGGER:
                triggerGUID = creature->GetGUID();
                break;
            case NPC_ATTACKER:
                if (!eventStarted)
                {
                    creature->SetReactState(REACT_PASSIVE);
                    attackersGuids.push_back(creature->GetGUID());
                }
                break;
            case NPC_DEFENDER:
                if (!eventStarted)
                {
                    creature->SetReactState(REACT_PASSIVE);
                    defendersGuids.push_back(creature->GetGUID());
                }
                break;
            case NPC_ATTACKER_LEADER:
                creature->SetReactState(REACT_PASSIVE);
                leaderGUID = creature->GetGUID();
                break;
            case NPC_VISUAL_FIRE_TRIGGER:
                visualFireTriggers.push_back(creature->GetGUID());
                break;
            case NPC_VISUAL_THUNDER_TRIGGER:
                visualThunderTrigger = creature->GetGUID();
                break;
            }
        }

        void OnUnitDeath(Unit* unit) override
        {
            switch (unit->GetEntry())
            {
            case NPC_ATTACKER:
                deadAttackers.push_back(unit->GetGUID());
                if (Unit * unit = sObjectAccessor->FindUnit(leaderGUID))
                    if (unit->IsAIEnabled)
                        unit->GetAI()->DoAction(EVENT_REVIVE_ATTACKER);
                break;
            case NPC_DEFENDER:
                if (Unit * unit = sObjectAccessor->FindUnit(triggerGUID))
                    if (unit->IsAIEnabled)
                        unit->GetAI()->DoAction(EVENT_NEW_DEFENDER);
                break;
            }
        }

        uint64 GetData64(uint32 DataId) const override
        {
            switch (DataId)
            {
            case NPC_EVENT_TRIGGER:
                return triggerGUID;
            case DATA_DEAD_ATTACKER:
                if (!deadAttackers.empty())
                    return deadAttackers.back();
                else
                    return 0;
            case NPC_VISUAL_FIRE_TRIGGER:
                if (!visualFireTriggers.empty())
                    return visualFireTriggers[visualFireIndex];
                else
                    return 0;
            case NPC_VISUAL_THUNDER_TRIGGER:
                return visualThunderTrigger;
            }
            return 0;
        }

        uint32 GetData(uint32 DataId) const override
        {
            switch (DataId)
            {
            case DATA_EVENT_STARTED:
                return eventStarted;
            }
            return 0;
        }

        void ProcessEvent(WorldObject* /*obj*/, uint32 eventId) override
        {
            switch (eventId)
            {
                case EVENT_START_EVENT:
                {
                    if (Unit * unit = sObjectAccessor->FindUnit(leaderGUID))
                    {
                        if (unit->IsAIEnabled)
                            unit->GetAI()->DoAction(1);
                    }
                    break;
                }
                case EVENT_START_EVENT2:
                {
                    for (auto& attacker : attackersGuids)
                    {
                        if (Unit * unit = sObjectAccessor->FindUnit(attacker))
                            unit->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY_UNARMED);
                    }
                    break;
                }
                case EVENT_START_EVENT3:
                {
                    for (auto& attacker : attackersGuids)
                    {
                        if (Unit * unit = sObjectAccessor->FindUnit(attacker))
                            if (Creature * creature = unit->ToCreature())
                            {
                                unit->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                                creature->SetReactState(REACT_AGGRESSIVE);
                                if (Unit * victim = creature->FindNearestCreature(NPC_DEFENDER, 50.f))
                                {
                                    creature->CombatStart(victim);
                                    creature->getThreatManager().addThreat(victim, 1000.f);
                                }
                            }
                    }

                    for (auto& defender : defendersGuids)
                    {
                        if (Unit * unit = sObjectAccessor->FindUnit(defender))
                            if (Creature * creature = unit->ToCreature())
                            {
                                creature->SetReactState(REACT_AGGRESSIVE);
                                if (Unit * victim = creature->FindNearestCreature(NPC_ATTACKER, 50.f))
                                {
                                    creature->CombatStart(victim);
                                    creature->getThreatManager().addThreat(victim, 1000.f);
                                }
                            }
                    }
                    eventStarted = true;
                    break;
                }
                case EVENT_REVIVE_ATTACKER:
                {
                    if (!deadAttackers.empty())
                        deadAttackers.pop_back();
                    break;
                }
                case EVENT_NEXT_VISUAL_FIRE:
                {
                    visualFireIndex = (visualFireIndex + 1) % VISUAL_FIRE_TRIGGERS_COUNT;
                    break;
                }
                case EVENT_RESET_EVENT:
                {
                    eventStarted = false;
                    visualFireIndex = 0;
                    defendersGuids.clear();
                    visualFireTriggers.clear();
                    for (auto& attacker : attackersGuids)
                    {
                        if (Unit * unit = sObjectAccessor->FindUnit(attacker))
                            if (Creature * creature = unit->ToCreature())
                            {
                                creature->SetPassive();
                                if(creature->IsAlive())
                                    creature->GetMotionMaster()->MoveTargetedHome();
                            }
                    }
                    break;
                }
            }
        }

    private:
        bool eventStarted;
        uint64 triggerGUID;
        uint64 leaderGUID;
        uint64 visualThunderTrigger;
        uint32 visualFireIndex;
        std::vector<uint64> defendersGuids;
        std::vector<uint64> attackersGuids;
        std::vector<uint64> deadAttackers;
        std::vector<uint64> visualFireTriggers;
    };

    WorldZoneScript* GetWorldZoneScript() const override
    {
        return new worldzone_searing_gorge_WorldMapZoneScript();
    }
};

struct npc_hellforge_portal_event_AI : public ScriptedAI
{

    npc_hellforge_portal_event_AI(Creature* creature) : ScriptedAI(creature), _summons(creature) { }

    void Reset()
    {
        if (eventStarted)
        {
            if (ZoneScript * zoneScript = me->GetZoneScript())
                zoneScript->ProcessEvent(nullptr, EVENT_RESET_EVENT);
        }
        _summons.DespawnAll();
        _scheduler.CancelAll();
        events.Reset();
        _canUsePortal = false;
        eventStarted = false;
        visualsFireTriggered = 0;
        visualsThunderTriggered = 0;
    }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (!who || !who->IsPlayer() || who->ToPlayer()->IsGameMaster())
            return;
        if (!eventStarted)
        {
            events.ScheduleEvent(EVENT_START_EVENT, 5s);
            eventStarted = true;
            _scheduler.Schedule(10s, [&](TaskContext /*func*/)
            {
                _canUsePortal = true;
            });
        }
        else
            TeleportToDiablo(who);
    }

    void TeleportToDiablo(Unit* who)
    {
        if (!_canUsePortal)
            return;

        _canUsePortal = false;
        _scheduler.Schedule(1s, [this](TaskContext /*func*/)
        {
            _canUsePortal = true;
        });

        Player* player = who->ToPlayer();
        if (!player)
            return;

        if (me->GetDistance(player) > 2.5f)
            return;

        bool _canEnter = false;
        Group* group = player->GetGroup();
        _canEnter = group && group->isRaidGroup();

        if (!_canEnter)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You must be in a raid group to enter this instance.");
            return;
        }

        if (player->GetDifficulty(true) != RAID_DIFFICULTY_25MAN_HEROIC)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Wrong difficulty setting, please set 25 man heroic in order to enter Hellforge.");
            return;
        }

        if (!player->IsBeingTeleported())
        {
            if (player->GetMapId() != DIABLO_MAP_ID)
            {
                if (!sMapMgr->CanPlayerEnter(DIABLO_MAP_ID, player, false))
                    return;

                player->TeleportTo(DIABLO_MAP_ID, { -176.27f, -205.96f, -66.43f, 6.17f });
            }
        }
    }

    void DoAction(int32 param) override
    {
        if (param == EVENT_NEW_DEFENDER)
        {
            events.ScheduleEvent(EVENT_NEW_DEFENDER, 5s, 8s);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!eventStarted)
            return;

        events.Update(diff);
        _scheduler.Update(diff);
        switch (events.GetEvent())
        {
            case EVENT_START_EVENT:
            {
                StartEvent();
                events.PopEvent();
                break;
            }
            case EVENT_NEW_DEFENDER:
            {
                SummonDefender(0);
                events.PopEvent();
                break;
            }
            case EVENT_EARTH_QUAKE:
            {
                me->CastCustomSpell(SPELL_EARTH_QUAKE, SPELLVALUE_BASE_POINT1, 0, nullptr, TRIGGERED_FULL_MASK);
                events.RescheduleEvent(EVENT_EARTH_QUAKE, 30s, 60s);
                break;
            }
            case EVENT_VISUAL_FIRE:
            {
                uint32 count = !visualsFireTriggered ? 3 : 2;
                for (uint32 i = 0; i < count; ++i)
                {
                    if (ZoneScript * zoneScript = me->GetZoneScript())
                    {
                        if (Unit * unit = sObjectAccessor->FindUnit(zoneScript->GetData64(NPC_VISUAL_FIRE_TRIGGER)))
                        {
                            me->CastCustomSpell(SPELL_FIRE_VISUAL, SPELLVALUE_BASE_POINT0, 0, unit, TRIGGERED_FULL_MASK);

                            CustomSpellValues vals;
                            vals.AddSpellMod(SPELLVALUE_RADIUS_MOD, 800);
                            vals.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
                            unit->CastCustomSpell(SPELL_FIRE_NOVA, vals, unit, TRIGGERED_FULL_MASK);
                        }
                        zoneScript->ProcessEvent(nullptr, EVENT_NEXT_VISUAL_FIRE);
                    }
                }
                if (visualsFireTriggered >= (VISUAL_FIRE_TRIGGERS_COUNT / 2) - 1)
                {
                    events.RescheduleEvent(EVENT_VISUAL_FIRE, 10s, 20s);
                    visualsFireTriggered = 0;
                }
                else
                {
                    events.RescheduleEvent(EVENT_VISUAL_FIRE, 250ms);
                    ++visualsFireTriggered;
                }
                break;
            }
            case EVENT_VISUAL_THUNDER:
            {
                if (ZoneScript * zoneScript = me->GetZoneScript())
                {
                    if (Unit * unit = sObjectAccessor->FindUnit(zoneScript->GetData64(NPC_VISUAL_THUNDER_TRIGGER)))
                    {
                        unit->CastCustomSpell(SPELL_THUNDER, SPELLVALUE_BASE_POINT0, 0);
                    }
                }
                events.RescheduleEvent(EVENT_VISUAL_THUNDER, 30s, 60s);
                break;
            }
            case EVENT_RESET_EVENT:
            {
                std::list<Player*> _players;
                float _range = 65.f;
                Trinity::AnyPlayerInObjectRangeCheck checker(me, _range);
                Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, _players, checker);
                me->VisitNearbyWorldObject(_range, searcher);

                _players.remove_if([](Player* obj)
                {
                    return obj->IsGameMaster();
                });

                if (_players.empty())
                    Reset();

                events.RescheduleEvent(EVENT_RESET_EVENT, 2min);
                break;
            }
        }
    }

    void StartEvent()
    {
        for (uint32 i = 0; i < PORTAL_DEFENDERS_COUNT; ++i)
            SummonDefender(i, true);

        for (uint32 i = 0; i < VISUAL_FIRE_TRIGGERS_COUNT; ++i)
            me->SummonCreature(NPC_VISUAL_FIRE_TRIGGER, VisualFireTriggersPosition[i]);

        for (uint32 i = 0; i < VISUAL_THUNDER_TARGETS_COUNT; ++i)
            me->SummonCreature(NPC_VISUAL_THUNDER_TARGET, VisualThunderTargetsPosition[i]);

        me->SummonCreature(NPC_VISUAL_THUNDER_TRIGGER, VisualThunderTriggerPosition);

        if (ZoneScript * zoneScript = me->GetZoneScript())
            zoneScript->ProcessEvent(nullptr, EVENT_START_EVENT);
        events.ScheduleEvent(EVENT_VISUAL_FIRE, 3s);
        events.ScheduleEvent(EVENT_VISUAL_THUNDER, 4s);
        events.ScheduleEvent(EVENT_EARTH_QUAKE, 30s, 60s);
        events.ScheduleEvent(EVENT_RESET_EVENT, 2min);
    }

    void SummonDefender(uint32 positionId, bool first = false)
    {
        if (Creature * creature = me->SummonCreature(NPC_DEFENDER, me->GetPosition()))
        {
            if (first)
                creature->SetPassive();
            Position pos = PortalDefendersPosition[positionId];
            creature->MonsterMoveWithSpeed(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), 3);
            creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY_UNARMED);
            creature->SetHomePosition(PortalDefendersPosition[positionId]);
        }
    }

private:
    bool eventStarted;
    uint32 visualsFireTriggered;
    uint32 visualsThunderTriggered;
    EventMap events;
    TaskScheduler _scheduler;
    SummonList _summons;

    bool _canUsePortal;
};

struct npc_hellforge_portal_defender_AI : public ScriptedAI
{

    npc_hellforge_portal_defender_AI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        if (ZoneScript * zoneScript = me->GetZoneScript())
        {
            if (zoneScript->GetData(DATA_EVENT_STARTED))
                if (Unit * unit = me->FindNearestCreature(NPC_ATTACKER, 50.f))
                {
                    me->CombatStart(unit);
                    me->getThreatManager().addThreat(unit, 1000.f);
                }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        UpdateVictim();
        DoMeleeAttackIfReady();
    }

private:
    EventMap events;
};

struct npc_hellforge_portal_attacker_AI : public ScriptedAI
{

    npc_hellforge_portal_attacker_AI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        if (ZoneScript * zoneScript = me->GetZoneScript())
        {
            if (zoneScript->GetData(DATA_EVENT_STARTED))
                if (Unit * unit = me->FindNearestCreature(NPC_DEFENDER, 50.f))
                {
                    me->CombatStart(unit);
                    me->getThreatManager().addThreat(unit, 1000.f);
                }
        }
    }

private:
    EventMap events;
};

struct npc_hellforge_portal_attacker_leader_AI : public ScriptedAI
{

    npc_hellforge_portal_attacker_leader_AI(Creature* creature) : ScriptedAI(creature) { }

    void DoAction(int32 param) override
    {
        switch (param)
        {
        case EVENT_START_EVENT:
            events.ScheduleEvent(EVENT_START_EVENT, 5s);
            break;
        case EVENT_REVIVE_ATTACKER:
            events.ScheduleEvent(EVENT_REVIVE_ATTACKER, 5s, 8s);
            break;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        UpdateVictim();

        events.Update(diff);
        switch (events.GetEvent())
        {
        case EVENT_START_EVENT:
            me->MonsterSay("Now is the time! Push forward and don't let them pass!", LANG_UNIVERSAL, nullptr);
            events.ScheduleEvent(EVENT_START_EVENT2, 5s);
            events.PopEvent();
            break;
        case EVENT_START_EVENT2:
            me->MonsterSay("Kill them and destroy the portal!", LANG_UNIVERSAL, nullptr);
            if (ZoneScript * zonescript = me->GetZoneScript())
                zonescript->ProcessEvent(nullptr, EVENT_START_EVENT2);
            events.ScheduleEvent(EVENT_START_EVENT3, 1s);
            events.PopEvent();
            break;
        case EVENT_START_EVENT3:
            if (ZoneScript * zonescript = me->GetZoneScript())
                zonescript->ProcessEvent(nullptr, EVENT_START_EVENT3);
            events.PopEvent();
            break;
        case EVENT_REVIVE_ATTACKER:
            if (ZoneScript * zonescript = me->GetZoneScript())
            {
                if (Unit * unit = sObjectAccessor->FindUnit(zonescript->GetData64(DATA_DEAD_ATTACKER)))
                {
                    if (unit->IsCreature())
                    {
                        unit->ToCreature()->Respawn();
                        if (!zonescript->GetData(DATA_EVENT_STARTED))
                            unit->ToCreature()->SetPassive();
                    }
                    me->MonsterSay("This death cannot be in vain! Push harder!", LANG_UNIVERSAL, nullptr);
                    me->CastSpell(unit, SPELL_REVIVE_VISUAL);
                    zonescript->ProcessEvent(nullptr, EVENT_REVIVE_ATTACKER);
                }
            }
            events.PopEvent();
            break;
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap events;
};

void AddSC_worldzone_searing_gorge()
{
    new worldzone_searing_gorge();
    new CreatureAILoader<npc_hellforge_portal_event_AI>("npc_hellforge_portal_event");
    new CreatureAILoader<npc_hellforge_portal_defender_AI>("npc_hellforge_portal_defender");
    new CreatureAILoader<npc_hellforge_portal_attacker_leader_AI>("npc_hellforge_portal_attacker_leader");
    new CreatureAILoader<npc_hellforge_portal_attacker_AI>("npc_hellforge_portal_attacker");
}
