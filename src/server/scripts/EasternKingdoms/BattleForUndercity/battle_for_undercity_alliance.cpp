
#include "CreatureGroups.h"
#include "Group.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "battle_for_undercity.h"

enum BattleForUndercityAlliance
{
    // Spells
    // King Varian
    SPELL_HEROIC_LEAP                   = 57793,
    SPELL_WHIRLWIND                     = 41056,
    SPELL_STRENGTH_OF_WRYNN             = 60964,
    SPELL_HEROIC_VANGUARD               = 60966,
    // Jaina
    SPELL_DEEP_FREEZE                   = 61224,
    SPELL_BRILLIANCE_AURA               = 61011,
    SPELL_GREATER_MASS_TELEPORT         = 61225,
    // Putress
    SPELL_BLIGHT_OVERLOAD               = 61181,
    SPELL_THROW_BARREL                  = 59460,
    // Thrall
    SPELL_WARCHIEF_BLESSING             = 61212,
    // Other
    SPELL_BLIGHT_EMPOWEREMENT           = 59449,
    SPELL_PUTRESS_CASTING_STATE         = 59447,
    SPELL_PUTRESS_TESLA_AURA            = 59457,
    SPELL_PUTRESS_TESLA_AURA_EFFECT     = 59456,

    // Mobs
    NPC_BLIGHT_WORM                     = 32483,

    NPC_PUTRESS                         = 31530,
    NPC_FAILED_EXPERIMENT               = 32519,

    // NPCs
    NPC_PUTRESS_TRIGGER                 = 31653,

    NPC_THRALL                          = 32518,
    NPC_SYLVANAS_ALLY                   = 32365,
    NPC_WARSONG_GUARDS                  = 32510,

    // Events
    EVENT_UPDATE_INTRO_WORLDSTATE       = 1,
    EVENT_UPDATE_OUTRO_WORLDSTATE       = 2,
    EVENT_START_BATTLE                  = 3
};

Position const WarsongBattleGuardPos[6] =
{
    {1303.605591f, 343.830933f, -65.027367f, 1.286632f},
    {1302.613892f, 348.721863f, -65.027367f, 1.282705f},
    {1299.280029f, 344.894592f, -65.027367f, 1.231660f},
    {1296.482056f, 345.446838f, -65.027367f, 1.184530f},
    {1295.094971f, 350.319000f, -65.027367f, 1.329828f},
    {1292.646606f, 346.304504f, -65.027367f, 1.380880f}
};

Position const PutressTeslaTriggersPos[5] =
{
    {1432.465698f, 407.467499f, -81.562538f, 1.286632f},
    {1433.350708f, 402.517365f, -80.123451f, 1.282705f},
    {1428.826660f, 399.726105f, -78.834717f, 1.231660f},
    {1425.206543f, 402.368774f, -79.196129f, 1.184530f},
    {1427.398682f, 406.904907f, -77.651726f, 1.329828f}
};

Position const FailedExperimentSpawnPos[4] =
{
    {1453.234009f, 414.391663f, -84.951553f, 1.286632f},
    {1418.966187f, 380.827545f, -84.984756f, 1.282705f},
    {1398.119629f, 413.339478f, -77.239609f, 1.231660f},
    {1422.729004f, 437.508759f, -77.238976f, 1.184530f}
};

Position const StormwindGuardsMovePos[4] =
{
    {1678.658081f, 573.888916f, -16.100155f, 1.286632f},
    {1668.787842f, 571.100952f, -16.439146f, 1.282705f},
    {1662.116089f, 539.267883f, -11.443453f, 1.231660f},
    {1664.450195f, 474.822235f, -11.890506f, 1.184530f}
};

Position const WaveTriggerSpawnPos[12] =
{
    {1599.944214f, 714.258911f, 62.882141f, 1.286632f},
    {1588.120728f, 675.434204f, 50.250622f, 1.282705f},
    {1621.377319f, 647.922974f, 35.587791f, 1.231660f},
    {1668.981812f, 642.816772f, 16.403944f, 1.184530f},
    {1690.942627f, 613.299438f, 2.8395260f, 1.286632f},
    {1678.822876f, 579.608582f, -14.04275f, 1.282705f},

    {1686.036377f, 541.290283f, -12.195216f, 1.231660f},
    {1665.332153f, 536.167542f, -11.386874f, 1.184530f},
    {1680.613159f, 589.291016f, -9.9411620f, 1.286632f},

    {1664.487549f, 479.809479f, -11.890506f, 1.282705f},
    {1486.733521f, 413.235474f, -62.185104f, 1.231660f},
    {1452.400879f, 445.750732f, -65.724861f, 1.184530f}
};

#define GOSSIP_TELEPORT     "Teleport me!"

uint32 AllianceWorldStates[] = 
{
    WORLDSTATE_UNDERCITY_CONTROLLED_A,
    WORLDSTATE_MANHUNT_TIMER_STATE,
    WORLDSTATE_MANHUNT_TIMER,
    WORLDSTATE_MANHUNT_BEGUN,
    WORLDSTATE_BATTLING_SEWERS,
    WORLDSTATE_SECURED_SEWERS,
    WORLDSTATE_BATTLING_APOTHECARIUM,
    WORLDSTATE_SECURED_APOTHECARIUM
};

struct npc_varian_battle_undercityAI : public npc_escortAI
{
    npc_varian_battle_undercityAI(Creature* creature) : npc_escortAI(creature), _summons(me) 
    {
        zoneScript = me->GetZoneScript();
        map = me->GetMap();
        phaseMask = me->GetPhaseMask();

        SetDespawnAtEnd(false);
        SetDespawnAtFar(false);
    }

    ZoneScript* zoneScript;
    Map* map;

    EventMap _events;

    SummonList _summons;

    uint64 PlayerGUID;
    uint64 PutressGUID;
    uint64 ThrallGUID;

    uint32 phaseMask;

    uint32 PhaseTimer;
    uint8 Step;
    uint8 EventRepeatCount;

    uint32 WhirlwindTimer;

    bool TalkEvent;
    bool UpdateWorldState;

    void sGossipHello(Player* player) override
    {
        float x, y, z;
        me->GetRespawnPosition(x, y, z);
        if (me->GetPositionX() != x || me->GetPositionY() != y)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TELEPORT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(me), me->GetGUID());
        }
    }

    void Reset() override
    {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
        {
            _events.Reset();
            _summons.DespawnAll();

            PlayerGUID = 0;
            PutressGUID = 0;
            ThrallGUID = 0;

            PhaseTimer = 0;
            Step = 0;

            EventRepeatCount = 5;

            TalkEvent = false;
            UpdateWorldState = false;

            WhirlwindTimer = urand(4 * IN_MILLISECONDS, 6 * IN_MILLISECONDS);

            me->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);

            if (Creature* Jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
            {
                Jaina->SearchFormation();
                Jaina->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            }
        }
    }

    void sGossipSelect(Player* player, uint32 sender, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();

        if (!action)
        {
            if (Creature* Jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
            {
                Jaina->RemoveAllAuras();
                float homeX, homeY, homeZ, homeOrient;
                Jaina->GetRespawnPosition(homeX, homeY, homeZ, &homeOrient);
                Jaina->NearTeleportTo(homeX, homeY, homeZ, homeOrient);
                Jaina->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_15);
                if (Jaina->AI())
                    Jaina->AI()->Reset();
                Jaina->SearchFormation();
            }
            EnterEvadeMode();
            me->RemoveAllAuras();
            float homeX, homeY, homeZ, homeOrient;
            me->GetRespawnPosition(homeX, homeY, homeZ, &homeOrient);
            me->NearTeleportTo(homeX, homeY, homeZ, homeOrient);
            JustRespawned();
            if (Group* group = player->GetGroup())
            {
                for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
                    if (Player* member = itr->GetSource())
                        member->NearTeleportTo(homeX, homeY, homeZ, homeOrient);
            }
            else
                player->NearTeleportTo(homeX, homeY, homeZ, homeOrient);

            return;
        }

        JumpToNextStep(100);
        PlayerGUID = player->GetGUID();
    }

    void WaypointReached(uint32 waypointId) override
    {
        switch (waypointId)
        {
            case 5:
                SetEscortPaused(true);
                JumpToNextStep(1000);
                break;
            case 8: 
                SummonTrigger(1);
                break;
            case 10:
                SummonTrigger(2);
                break;
            case 12:
                SummonTrigger(3);
                break;
            case 14:
                SummonTrigger(4);
                break;
            case 17:
                SummonTrigger(5);
                break;
            case 21:
                SetEscortPaused(true);
                Talk(7);
                JumpToNextStep(6000);
                break;
            case 43:
                SetEscortPaused(true);
                JumpToNextStep(2000);
                break;
            case 45:
                me->SetStandState(UNIT_STAND_STATE_KNEEL);
                SetEscortPaused(true);
                JumpToNextStep(1000);
                break;
            case 49:
                SummonTrigger(10);
                break;
            case 53:
                SetEscortPaused(true);
                JumpToNextStep(3000);
                break;
            case 65:
                if (Creature* Putress = me->SummonCreature(NPC_PUTRESS, 1426.14f, 406.23f, -85.25f, 2.27f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000))
                {
                    PutressGUID = Putress->GetGUID();
                    Putress->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC |UNIT_FLAG_IMMUNE_TO_NPC);
                    Putress->CastSpell(Putress, SPELL_PUTRESS_CASTING_STATE, false);
                    if (Putress->GetAI())
                        Putress->GetAI()->SetData(0, 1);
                }
                if (Creature* Jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                {
                    if (Jaina->GetFormation())
                        Jaina->GetFormation()->RemoveMember(Jaina);
                    Jaina->GetMotionMaster()->MovePoint(103, 1419.15f, 410.11f, -84.96f);
                }
                break;
            case 68:
                SetEscortPaused(true);
                Talk(15);
                SetRun(false);
                JumpToNextStep(6000);
                break;
            case 70:
                SetEscortPaused(true);
                Talk(16);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                if (Creature* Jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                    Jaina->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                JumpToNextStep(6000);
                break;
            case 71:
                SetEscortPaused(true);
                me->SetFacingTo(5.499f);
                JumpToNextStep(8000);
                break;
            case 95:
                if (Creature* Thrall = me->SummonCreature(NPC_THRALL, 1299.08f, 348.47f, -65.03f, 1.33f, TEMPSUMMON_MANUAL_DESPAWN))
                {
                    ThrallGUID = Thrall->GetGUID();
                    Thrall->CastSpell(Thrall, SPELL_WARCHIEF_BLESSING, true);
                }
                if (Creature* Sylvanas = me->SummonCreature(NPC_SYLVANAS_ALLY, 1296.28f, 348.07f, -65.03f, 1.34f, TEMPSUMMON_MANUAL_DESPAWN))
                {
                    Sylvanas->SetStandState(UNIT_STAND_STATE_STAND);
                    Sylvanas->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                    Sylvanas->SetSheath(SHEATH_STATE_RANGED);
                }
                for (uint8 i =0; i < 6; ++i)
                    me->SummonCreature(NPC_WARSONG_GUARDS, WarsongBattleGuardPos[i], TEMPSUMMON_MANUAL_DESPAWN);
                break;
            case 99:
                SetEscortPaused(true);
                JumpToNextStep(6000);
                break;
            case 102:
                JumpToNextStep(1000);
                break;
        }
    }

    void JumpToNextStep(uint32 timer)
    {
        if (!zoneScript)
            return;

        TalkEvent = true;
        PhaseTimer = timer;
        ++Step;
    }

    void DoUpdateWorldState(uint32 uiStateId, uint32 uiStateData) const
    {
        if (!map)
            return;

        Map::PlayerList const& players = map->GetPlayers();

        if (!players.isEmpty())
            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                if (Player* player = itr->GetSource())
                    if ((player->GetZoneId() == ZONE_TRISFAL_GLADES || player->GetZoneId() == ZONE_UNDERCITY) 
                        && player->GetPhaseMask() == phaseMask)
                        player->SendUpdateWorldState(uiStateId, uiStateData);

        if (zoneScript)
            zoneScript->SetData(uiStateId, uiStateData);
    }

    void DespawnCreatures(uint32 entry)
    {
        _summons.DespawnEntry(entry);
    }

    void SummonGuards() const
    {
        for (uint8 i = 0; i < 4; ++i)
            if (Creature* guard = me->SummonCreature(NPC_STORMWIND_ELITE_A, 1690.94f, 613.30f, 2.84f, 0.0f))
                guard->GetMotionMaster()->MovePoint(0, StormwindGuardsMovePos[i]);
    }

    void SummonTrigger(uint8 pos) const
    {
        if (Creature* WaveTrigger  = me->SummonCreature(NPC_WAVES_TRIGGER, WaveTriggerSpawnPos[pos]))
            if (WaveTrigger->IsAIEnabled)
                WaveTrigger->GetAI()->SetData(0, pos);
    }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        _summons.Despawn(summon);
    }

    void SpellHit(Unit* /*caster */, SpellInfo const* spellInfo) override
    {
        switch (spellInfo->Id)
        {
            case SPELL_DEEP_FREEZE:
                JumpToNextStep(2000);
                break;
        }
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        npc_escortAI::MovementInform(type, pointId);

        if (type == POINT_MOTION_TYPE && pointId == 103)
        {
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_LOOT);
            JumpToNextStep(4000);

            if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                jaina->GetMotionMaster()->MovePoint(104, 1421.32f, 419.45f, -84.96f);
        }
    }

    void SetData(uint32 /*type*/, uint32 data) override 
    {
        switch (data)
        {
            case 0:
                DespawnCreatures(NPC_WAVES_TRIGGER);
                break;
            case 1:
                DoUpdateWorldState(WORLDSTATE_BATTLING_SEWERS, 0);
                DoUpdateWorldState(WORLDSTATE_SECURED_SEWERS, 1);
                JumpToNextStep(6000);
                break;
            case 2:
                if (Creature* Putress = DoSpawnCreature(NPC_PUTRESS, 0.0f, 0.0f, 20.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 12000))
                {
                    if (Putress->IsAIEnabled)
                        Putress->AI()->Talk(1);
                    Putress->SetVisible(false);
                }
                break;
            case 3:
                Talk(17);
                if (Creature* Jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                {
                    Jaina->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                    if (Jaina->GetFormation())
                        Jaina->GetFormation()->RemoveMember(Jaina);
                }
                DoUpdateWorldState(WORLDSTATE_BATTLING_APOTHECARIUM, 0);
                DoUpdateWorldState(WORLDSTATE_SECURED_APOTHECARIUM, 1);
                JumpToNextStep(6000);
                break;
            case 4:
                DespawnCreatures(NPC_WAVES_TRIGGER);
                Talk(8);
                me->SummonCreature(NPC_BLIGHT_WORM, 1676.43f, 560.439f, -18.411f, 1.345f, TEMPSUMMON_CORPSE_DESPAWN, 120 * IN_MILLISECONDS);
                break;
            case 5:
                DespawnCreatures(NPC_WAVES_TRIGGER);
                if (Creature* Putress = DoSpawnCreature(NPC_PUTRESS, 0.0f, 0.0f, 20.0f, 0, TEMPSUMMON_TIMED_DESPAWN, 12000))
                {
                    if (Putress->IsAIEnabled)
                        Putress->AI()->Talk(1);
                    Putress->SetVisible(false);
                }
                break;
            default:
                break;
        }
    }

    void EnterCombat(Unit* /*victim*/) override
    {
        DoCastSelf(SPELL_HEROIC_VANGUARD);
    }

    void EnterEvadeMode() override
    {
        me->DeleteThreatList();
        me->CombatStop(true);
        me->SetLootRecipient(nullptr);
        me->RemoveAurasDueToSpell(SPELL_HEROIC_VANGUARD);

        if (HasEscortState(STATE_ESCORT_ESCORTING))
        {
            AddEscortState(STATE_ESCORT_RETURNING);
            ReturnToLastPoint();
        }
        else
        {
            me->GetMotionMaster()->MoveTargetedHome();
            Reset();
        }
    }

    void JustDied(Unit* killer) override
    {
        npc_escortAI::JustDied(killer);

        EntryCheckPredicate pred(NPC_WAVES_TRIGGER);
        _summons.DoAction(0, pred);
        _summons.DespawnAll();

        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
        {
            jaina->RemoveAllAuras();
            float homeX, homeY, homeZ, homeOrient;
            jaina->GetRespawnPosition(homeX, homeY, homeZ, &homeOrient);
            jaina->NearTeleportTo(homeX, homeY, homeZ, homeOrient);
            jaina->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_15);
            if (jaina->IsAIEnabled)
                jaina->AI()->Reset();
        }

        for (uint32 i = 0; i < 8; ++i)
            DoUpdateWorldState(AllianceWorldStates[i], i == 0 ? 1: 0);
    }

    void UpdateAI(uint32 diff) override
    {
        npc_escortAI::UpdateAI(diff);

        if (UpdateWorldState)
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_UPDATE_INTRO_WORLDSTATE:
                    {
                        switch (EventRepeatCount)
                        {
                            case 2:
                                Talk(3);
                                break;
                            case 3:
                                Talk(2);
                                break;
                            default:
                                break;
                        }

                        DoUpdateWorldState(WORLDSTATE_MANHUNT_TIMER, EventRepeatCount);
                        if (--EventRepeatCount)
                            _events.ScheduleEvent(EVENT_UPDATE_INTRO_WORLDSTATE, 1min);
                        else
                            _events.ScheduleEvent(EVENT_START_BATTLE, 1min);
                        break;
                    }
                    case EVENT_START_BATTLE:
                        UpdateWorldState = false;
                        Talk(4);

                        DoUpdateWorldState(WORLDSTATE_MANHUNT_TIMER_STATE, 0);
                        DoUpdateWorldState(WORLDSTATE_MANHUNT_TIMER, EventRepeatCount);
                        DoUpdateWorldState(WORLDSTATE_MANHUNT_BEGUN, 1);

                        DoCastSelf(SPELL_STRENGTH_OF_WRYNN);

                        JumpToNextStep(15000);
                        break;
                    default:
                        break;
                }
            }
        }

        if (TalkEvent)
            if (PhaseTimer <= diff)
            {
                switch (Step)
                {
                    case 1:
                        me->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
                        Talk(0);
                        if (Creature* trigger = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_WAVES_TRIGGER)))
                            if (trigger->IsAlive())
                                trigger->Kill(trigger, trigger);
                        DoUpdateWorldState(WORLDSTATE_MANHUNT_TIMER_STATE, 1);
                        DoUpdateWorldState(WORLDSTATE_MANHUNT_TIMER, EventRepeatCount);
                        UpdateWorldState = true;
                        --EventRepeatCount;
                        _events.ScheduleEvent(EVENT_UPDATE_INTRO_WORLDSTATE, 1min);
                        JumpToNextStep(12000);
                        break;
                    case 2:
                        Talk(1);
                        TalkEvent = false;
                        break;
                    case 3:
                        Talk(5);
                        Start(true, true, PlayerGUID);
                        TalkEvent = false;
                        break;
                    case 4:
                        Talk(6);
                        DoUpdateWorldState(WORLDSTATE_UNDERCITY_CONTROLLED_A, 0);
                        DoUpdateWorldState(WORLDSTATE_MANHUNT_BEGUN, 0);
                        DoUpdateWorldState(WORLDSTATE_BATTLING_SEWERS, 1);
                        JumpToNextStep(9000);
                        break;
                    case 5:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                            if (jaina->IsAIEnabled)
                                jaina->AI()->Talk(0);
                        JumpToNextStep(3000);
                        break;
                    case 6:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                            jaina->CastSpell(jaina, SPELL_BRILLIANCE_AURA, false);
                        SetEscortPaused(false);
                        SummonTrigger(0);
                        TalkEvent = false;
                        break;
                    case 7:
                        for (uint8 i = 6; i < 9; ++i)
                            SummonTrigger(i);
                        TalkEvent = false;
                        break;
                    case 8:
                        Talk(9);
                        JumpToNextStep(10000);
                        break;
                    case 9:
                        Talk(10);
                        SummonGuards();
                        JumpToNextStep(12000);
                        break;
                    case 10:
                        SetRun(false);
                        SetEscortPaused(false);
                        TalkEvent = false;
                        SummonTrigger(9);
                        break;
                    case 11:
                        DespawnCreatures(NPC_STORMWIND_ELITE_A);
                        DespawnCreatures(NPC_WAVES_TRIGGER);
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                        {
                            jaina->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                            if (jaina->IsAIEnabled)
                                jaina->AI()->Talk(1);
                        }
                        JumpToNextStep(10000);
                        break;
                    case 12:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                            jaina->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 13:
                        Talk(11);
                        JumpToNextStep(8000);
                        break;
                    case 14:
                        Talk(12);
                        JumpToNextStep(8000);
                        break;
                    case 15:
                        Talk(13);
                        JumpToNextStep(4000);
                        break;
                    case 16:
                        me->HandleEmoteCommand(EMOTE_STATE_POINT);
                        if (Creature* putress = DoSpawnCreature(NPC_PUTRESS, 0.0f, 0.0f, 20.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 12000))
                        {
                            if (putress->IsAIEnabled)
                                putress->AI()->Talk(0);
                            putress->SetVisible(false);
                        }
                        me->SetStandState(UNIT_STAND_STATE_STAND);
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                            jaina->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                        SetRun(true);
                        SetEscortPaused(false);
                        TalkEvent = false;
                        DoUpdateWorldState(WORLDSTATE_BATTLING_APOTHECARIUM, 1);
                        break;
                    case 17:
                        Talk(14);
                        SetEscortPaused(false);
                        TalkEvent = false;
                        SummonTrigger(11);
                        break;
                    case 18:
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 19:
                        if (Creature* putress = ObjectAccessor::GetCreature(*me, PutressGUID))
                            if (putress->IsAIEnabled)
                                putress->AI()->Talk(2);
                        JumpToNextStep(4000);
                        break;
                    case 20:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                            jaina->SearchFormation();
                        if (Creature* putress = ObjectAccessor::GetCreature(*me, PutressGUID))
                            if (putress->IsAIEnabled)
                            {
                                putress->AI()->SetGUID(PlayerGUID);
                                putress->AI()->SetData(0, 2);
                            }
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                        TalkEvent = false;
                        break;
                    case 21:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                            jaina->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                        if (Creature* putress = ObjectAccessor::GetCreature(*me, PutressGUID))
                            me->GetMotionMaster()->MovePoint(103, *putress);
                        TalkEvent = false;
                        break;
                    case 22:
                        Talk(18);
                        JumpToNextStep(6000);
                        break;
                    case 23:
                        Talk(19);
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 24:
                        Talk(20);
                        JumpToNextStep(7000);
                        break;
                    case 25:
                        Talk(21);
                        JumpToNextStep(8000);
                        break;
                    case 26:
                        Talk(22);
                        JumpToNextStep(11000);
                        break;
                    case 27:
                        if (Creature* thrall = DoSpawnCreature(NPC_THRALL, 0.0f, 0.0f, 20.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 5000))
                        {
                            if (thrall->IsAIEnabled)
                                thrall->AI()->Talk(0);
                            thrall->SetVisible(false);
                        }
                        JumpToNextStep(6000);
                        break;
                    case 28:
                        if (Creature* thrall = DoSpawnCreature(NPC_THRALL, 0.0f, 0.0f, 20.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 5000))
                        {
                            if (thrall->IsAIEnabled)
                                thrall->AI()->Talk(1);
                            thrall->SetVisible(false);
                        }
                        JumpToNextStep(6000);
                        break;
                    case 29:
                        Talk(23);
                        JumpToNextStep(5000);
                        break;
                    case 30:
                        Talk(24);
                        JumpToNextStep(4000);
                        break;
                    case 31:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                        {
                            jaina->SetFacingToObject(me);
                            if (jaina->IsAIEnabled)
                                jaina->AI()->Talk(2);
                        }
                        SetRun(true);
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 32:
                        Talk(25);
                        JumpToNextStep(12000);
                        break;
                    case 33:
                        Talk(26);
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 34:
                        Talk(27);
                        JumpToNextStep(17000);
                        break;
                    case 35:
                        Talk(28);
                        JumpToNextStep(13000);
                        break;
                    case 36:
                        Talk(29);
                        JumpToNextStep(17000);
                        break;
                    case 37:
                        Talk(30);
                        JumpToNextStep(12000);
                        break;
                    case 38:
                        Talk(31);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_15);
                        for (auto &guid : _summons)
                            if (Creature* summon = ObjectAccessor::GetCreature(*me, guid))
                            {
                                summon->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_15);
                                if (summon->GetEntry() == NPC_THRALL)
                                    DoCast(summon, SPELL_HEROIC_LEAP, false);
                            }
                        JumpToNextStep(10000);
                        break;
                    case 39:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                        {
                            jaina->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_15);
                            jaina->NearTeleportTo(1305.02f, 370.15f, -67.29f, 4.33f);
                        }
                        JumpToNextStep(1000);
                        break;
                    case 40:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                            if (jaina->IsAIEnabled)
                                jaina->AI()->Talk(3);
                        JumpToNextStep(8000);
                        break;
                    case 41:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                            jaina->GetMotionMaster()->MovePoint(105, 1299.30f, 348.18f, -65.02f);
                        JumpToNextStep(10000);
                        break;
                    case 42:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                            jaina->CastSpell(jaina, SPELL_DEEP_FREEZE, false);
                        TalkEvent = false;
                        break;
                    case 43:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                        {
                            if (jaina->IsAIEnabled)
                                jaina->AI()->Talk(4);
                            jaina->CastSpell(jaina, SPELL_GREATER_MASS_TELEPORT, false);
                        }
                        JumpToNextStep(4000);
                        break;
                    case 44:
                        _summons.DespawnAll();
                        EnterEvadeMode();
                        me->RemoveAllAuras();
                        float homeX, homeY, homeZ, homeOrient;
                        me->GetRespawnPosition(homeX, homeY, homeZ, &homeOrient);
                        me->NearTeleportTo(homeX, homeY, homeZ, homeOrient);
                        JustRespawned();
                        DoUpdateWorldState(WORLDSTATE_SECURED_SEWERS, 0);
                        DoUpdateWorldState(WORLDSTATE_SECURED_APOTHECARIUM, 0);
                        DoUpdateWorldState(WORLDSTATE_UNDERCITY_CONTROLLED_A, 1);
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_JAINA)))
                        {
                            jaina->RemoveAllAuras();
                            float homeX, homeY, homeZ, homeOrient;
                            jaina->GetRespawnPosition(homeX, homeY, homeZ, &homeOrient);
                            jaina->NearTeleportTo(homeX, homeY, homeZ, homeOrient);
                            jaina->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_15);
                            if (jaina->IsAIEnabled)
                            {
                                jaina->AI()->Reset();
                                jaina->SearchFormation();
                            }
                        }
                        TalkEvent = false;
                        break;
                }
            }
            else
                PhaseTimer -= diff;

        if (!UpdateVictim())
            return;

        if (WhirlwindTimer <= diff)
        {
            DoCastVictim(SPELL_WHIRLWIND);
            WhirlwindTimer = urand(6 * IN_MILLISECONDS, 8 * IN_MILLISECONDS);
        }
        else
            WhirlwindTimer -= diff;

        DoMeleeAttackIfReady();
    }

};

struct npc_putress_battle_undercityAI : public ScriptedAI
{
    npc_putress_battle_undercityAI(Creature* creature) : ScriptedAI(creature), _summons(me) { }

    SummonList _summons;

    uint64 VarianGUID;
    uint64 PlayerGUID;

    uint32 PhaseTimer;
    uint8 Phase;

    uint32 SpawnTimer;
    uint32 SummonedKilledCounter;

    uint32 BarrelTimer;

    bool Encountered;
    bool StartBattle;

    void Reset() override
    {
        VarianGUID = 0;
        PlayerGUID = 0;

        Encountered= false;
        StartBattle = false;

        PhaseTimer = 1000;
        Phase = 0;

        SpawnTimer = 0;
        SummonedKilledCounter = 0;

        BarrelTimer = urand(10 * IN_MILLISECONDS, 12 * IN_MILLISECONDS);
    }

    void IsSummonedBy(Unit* summoner) override
    {
        if (summoner->GetEntry() != NPC_VARIAN)
            return;

        VarianGUID = summoner->GetGUID();
    }

    void JustSummoned(Creature* creature) override
    {
        _summons.Summon(creature);
    }

    void SummonedCreatureDies(Creature* creature, Unit* /*killer*/) override
    {
        _summons.Despawn(creature);

        if (creature->GetEntry() != NPC_FAILED_EXPERIMENT)
            return;

        if (!StartBattle)
        {
            ++SummonedKilledCounter;
            if (SummonedKilledCounter >= 100)
                StartBattle = true;
        }
    }

    void SetData(uint32 /*type*/, uint32 data) override
    {
        switch (data)
        {
            case 1:
            {
                for (uint8 i = 0; i < 5; ++i)
                    if (Creature* tesla = me->SummonCreature(NPC_PUTRESS_TRIGGER, PutressTeslaTriggersPos[i]))
                    {
                        tesla->RemoveAurasDueToSpell(49132);
                        tesla->CastSpell(me, SPELL_BLIGHT_EMPOWEREMENT, false, nullptr, nullptr, me->GetGUID());
                    }
                break;
            }
            case 2:
                Encountered = true;
                StartSpawningAdds();
                break;
        }
    }

    void SpellHitTarget(Unit* target, SpellInfo const* spellInfo) override
    {
        if (spellInfo->Id == SPELL_PUTRESS_TESLA_AURA_EFFECT)
            if (!target->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                target->CastSpell(me, SPELL_BLIGHT_EMPOWEREMENT, false, nullptr, nullptr, me->GetGUID());
    }

    void SetGUID(uint64 guid, int32 /*id*/) override
    {
        PlayerGUID = guid;
    }

    void JustDied(Unit* /*killer*/) override
    {
        _summons.DespawnAll();

        if (Creature* Varian = ObjectAccessor::GetCreature(*me, VarianGUID))
            if (Varian->IsAIEnabled)
                Varian->GetAI()->SetData(0, 3);
    }

    void StartSpawningAdds()
    {
        for (uint8 i = 0; i < 4; ++i)
            for (uint8 j = 0; j < urand(1, 5); ++j)
                if (Creature* Experiment = me->SummonCreature(NPC_FAILED_EXPERIMENT, FailedExperimentSpawnPos[i], TEMPSUMMON_CORPSE_DESPAWN))
                    if (Unit* target = ObjectAccessor::GetUnit(*me, PlayerGUID ? PlayerGUID : VarianGUID))
                        if (Experiment->IsAIEnabled)
                        {
                            Experiment->AddThreat(target, 10000.0f);
                            Experiment->AI()->AttackStart(target);
                        }

        SpawnTimer = 5 * IN_MILLISECONDS;
    }

    void JumpToNextStep(uint32 Timer)
    {
        PhaseTimer = Timer;
        ++Phase;
    }

    void UpdateAI(uint32 diff) 
    {
        if (!Encountered)
            return;

        if (!StartBattle && me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (SpawnTimer <= diff)
            StartSpawningAdds();
        else
            SpawnTimer -= diff;

        if (StartBattle)
        {
            if (PhaseTimer <= diff)
            {
                switch (Phase)
                {
                    case 0:
                        Talk(3);
                        JumpToNextStep(5000);
                        break;
                    case 1:
                        Talk(4);
                        JumpToNextStep(5000);
                        break;
                    case 2:
                        Talk(5);
                        JumpToNextStep(12000);
                        break;
                    case 3:
                        Talk(6);
                        JumpToNextStep(8000);
                        break;
                    case 4:
                        Talk(7);
                        JumpToNextStep(5000);
                        break;
                    case 5:
                        StartBattle = false;
                        me->RemoveAurasDueToSpell(SPELL_PUTRESS_CASTING_STATE);
                        DoCastSelf(SPELL_PUTRESS_TESLA_AURA, true);
                        DoCastSelf(SPELL_BLIGHT_OVERLOAD);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_15);
                        if (Creature* Varian = ObjectAccessor::GetCreature(*me, VarianGUID))
                            if (Varian->IsAIEnabled)
                                Varian->GetAI()->AttackStart(me);
                        break;
                }
            }
            else
                PhaseTimer -= diff;
        }

        if (!UpdateVictim())
            return;

        if (BarrelTimer <= diff)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f))
                DoCast(target, SPELL_THROW_BARREL, false);
            BarrelTimer = urand(12 * IN_MILLISECONDS, 15 * IN_MILLISECONDS);
        }
        else
            BarrelTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

void AddSC_battle_for_undercity_alliance()
{
    new CreatureAILoader<npc_varian_battle_undercityAI>("npc_varian_battle_undercity");
    new CreatureAILoader<npc_putress_battle_undercityAI>("npc_putress_battle_undercity");
}
