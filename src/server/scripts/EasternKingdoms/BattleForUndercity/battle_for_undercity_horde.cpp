
#include "CreatureGroups.h"
#include "Group.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "battle_for_undercity.h"

// 1560.305664 Y: 232.002747 Z: -43.102493 - [Teleport]  Orientation: 1.182560
enum BattleForUndercityHorde
{
    // Spells
    // Thrall
    SPELL_CHAIN_LIGHTNING               = 59517,
    SPELL_LAVA_BURST                    = 59519,
    SPELL_THUNDER                       = 59507,
    SPELL_HEROIC_VANGUARD               = 59506,
    SPELL_WARCHIEFS_BLESSING            = 64670,
    SPELL_TIDAL_WAVE_SUMMON             = 59627,
    // Sylvanas
    SPELL_SONG_OF_SYLVANAS              = 59756,
    SPELL_LEAP_TO_PLATFORM              = 56347,
    // Varimathras
    SPELL_CARION_SWARM                  = 59434,
    SPELL_DRAIN_LIFE                    = 17238,
    SPELL_MIGHT_OF_VARIMATHRAS          = 59424,
    SPELL_SHADOW_BOLT_VOLLEY            = 20741,
    SPELL_AURA_OF_VARIMATHRAS           = 60289,
    SPELL_LEGION_PORTAL                 = 59680,
    SPELL_OPENING_LEGION_PORTALS        = 60224,
    // Other
    SPELL_TIDAL_WAVE                    = 59635,
    SPELL_TIDAY_FURY                    = 59631,
    SPELL_TIDAY_FURY_EFFECT             = 59629,
    SPELL_CALL_OF_AIR                   = 59898,
    SPELL_CYCLONE_FALL                  = 59892,
    SPELL_CALL_OF_EARTH                 = 60207,
    SPELL_PORTAL_COLLAPSE               = 60285,
    SPELL_TELEPORT_SPAWN_VISUAL         = 60427,
    SPELL_SUMMONED_DEMON                = 7741,
    SPELL_DEEP_FREEZE                   = 60511,
    SPELL_GREATER_MASS_TELEPORT         = 60516,
    SPELL_WATER_REVENANT_ENTRANCE       = 55760,

    // NPC's
    NPC_WARSONG_BATTLEGUARD             = 31739,
    NPC_VORTEX                          = 31782,
    NPC_TIDAL_WAVE                      = 31765,
    NPC_WHIRLWIND                       = 31688,
    NPC_CAVE_DUMMY                      = 32200,
    NPC_SLINGER_TRIGGER                 = 31577,
    NPC_OVERLORD_SAURFANG               = 32315,
    NPC_DISTANT_VOICE                   = 31814,

    // GO'S
    GO_BLOCKED_PASSAGE                  = 194935,
    GO_HORDE_BANNER                     = 194004,
    GO_PORTAL_ORGRIMMAR                 = 193427,

    // Misc
    SOUND_LAMENT                        = 10896,

    // Mobs
    NPC_BLIGHT_SPREADER                 = 31831,

    NPC_BLIGHT_ABBERATION               = 31844,

    NPC_VARIMATHRAS                     = 31565,
    NPC_VARIMATHRAS_PORTAL              = 31811,

    NPC_KHANOK                          = 32160,

    NPC_LEGION_OVERLORD                 = 32271,
    NPC_LEGION_INVADER                  = 32269,
    NPC_LEGION_DREADWHISPER             = 32270,

    NPC_VARIAN_H                        = 32303,
    NPC_STORMWIND_ELITE                 = 31639,

    NPC_SAURFANG                        = 32315,

    // Events
    EVENT_UPDATE_INTRO_WORLDSTATE       = 1,
    EVENT_UPDATE_OUTRO_WORLDSTATE       = 2,
    EVENT_START_BATTLE                  = 3,
    EVENT_START_OUTRO_BATTLE            = 4,
};

Position const VortexSpawnPos[2] =
{
    {1877.590332f, 234.105881f, 60.044224f, 1.286632f},
    {1877.750122f, 241.220016f, 60.007225f, 1.286632f}
};

Position const HordeBannerSpawnPos[8] =
{
    {1736.964722f, 239.023056f, 62.685543f, 6.250000f},
    {1750.710327f, 245.470428f, 65.585114f, 6.250000f},
    {1750.461182f, 232.408432f, 64.956978f, 6.250000f},
    {1628.034912f, 249.905167f, 62.853127f, 5.752854f},
    {1632.215454f, 253.885544f, 62.594212f, 5.752854f},
    {1587.852173f, 237.403748f, 60.150764f, 0.007666f},
    {1587.451050f, 243.044586f, 60.150764f, 0.007666f},
    {1592.733154f, 382.058716f, -62.177578f, 0.007666f}
};

Position const HordeGuardSpawnPos[3] =
{
    {1593.744385f, 236.263702f, 60.1506650f, 2.591626f},
    {1534.351196f, 217.998215f, -43.056278f, 4.131000f},
    {1528.664307f, 208.112366f, -43.056278f, 1.048311f}
};

Position const CycloneSpawnPos[4] =
{
    {1544.31f, 241.81f, -41.359f, 6.25f},
    {1544.31f, 241.81f, -20.352f, 6.25f},
    {1544.31f, 241.81f, -4.9818f, 6.25f},
    {1544.31f, 241.81f, 23.3281f, 6.25f}
};

Position const PortalSpawnPos[6] =
{
    {1324.698730f, 355.651215f, -63.661636f, 3.885573f},
    {1336.103516f, 311.884094f, -63.661366f, 2.892038f},
    {1303.705811f, 280.090820f, -63.661320f, 1.787766f},
    {1260.306396f, 292.426483f, -63.661362f, 0.789526f},
    {1248.817139f, 336.162170f, -63.662071f, 6.024203f},
    {1281.007446f, 367.944153f, -63.662357f, 4.987479f}
};

Position const WaveTriggerSpawnPos[11] =
{
    {1736.030762f, 239.754089f, 62.789696f, 6.266412f},
    {1728.583374f, 258.317963f, 64.148369f, 6.231070f},
    {1728.036133f, 220.326035f, 64.148544f, 6.205258f},
    {1595.328491f, 206.539719f, -55.342926f, 1.429556f},
    {1530.924072f, 249.284439f, -62.179073f, 5.237929f},
    {1590.065674f, 300.080414f, -62.177605f, 5.795569f},
    {1562.672485f, 421.463318f, -62.177696f, 5.031369f},
    {1630.124390f, 421.629456f, -62.177422f, 4.520856f},
    {1533.639648f, 342.675690f, -62.165802f, 1.394971f},
    {1653.375610f, 342.042847f, -62.171635f, 1.634523f},
    {1574.694092f, 389.525970f, -47.180653f, 6.241663f}
};

Position const SpreaderSpawnPos[5] =
{
    {1768.496216f, 282.439880f, 70.399712f, 4.691685f},
    {1782.424438f, 281.858643f, 70.399712f, 4.707393f},
    {1818.824097f, 281.003326f, 70.399658f, 4.695614f},
    {1781.788940f, 195.228012f, 70.399864f, 1.550095f},
    {1816.663208f, 195.277527f, 70.399864f, 1.652197f}
};

uint32 HordeWorldStates[] =
{
    WORLDSTATE_UNDERCITY_CONTROLLED_H,
    WORLDSTATE_BATTLE_TIMER_STATE,
    WORLDSTATE_BATTLE_TIMER,
    WORLDSTATE_BATTLE_BEGUN,
    WORLDSTATE_BATTLING_COURTYARD,
    WORLDSTATE_CONTROLL_COURTYARD,
    WORLDSTATE_BATTLING_INNER_SANCTUM,
    WORLDSTATE_CONTROLL_INNER_SANCTUM,
    WORLDSTATE_BATTLING_ROYAL_QUARTER,
    WORLDSTATE_CONTROLL_ROYAL_QUARTER,
    WORLDSTATE_RESET_BATTLE,
    WORLDSTATE_RESET_TIMER
};

#define GOSSIP_TELEPORT     "Teleport me!"

struct npc_thrall_battle_undercityAI : public npc_escortAI
{
    npc_thrall_battle_undercityAI(Creature* creature) : npc_escortAI(creature), _summons(me)
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
    uint64 VarianGUID;
    uint64 JainaGUID;
    uint64 VarimathrasGUID;
    uint64 TidalWaveGUID;
    uint64 PassageGUID;
    uint64 SaurfangGUID;
    uint64 KhanokGUID;

    uint32 phaseMask;
    uint32 PhaseTimer;
    uint8 Step;
    uint8 EventRepeatCount;

    int32 DreadLordCount;

    uint32 ChainTimer;
    uint32 ThunderTimer;
    uint32 LavaBurstTimer;

    bool TalkEvent;
    bool UpdateWorldState;

    void sGossipHello(Player* player) override
    {
        if (me->IsQuestGiver())
            player->PrepareQuestMenu(me->GetGUID());

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
            VarianGUID = 0;
            JainaGUID = 0;
            VarimathrasGUID = 0;
            TidalWaveGUID = 0;
            PassageGUID = 0;
            SaurfangGUID = 0;
            KhanokGUID = 0;

            PhaseTimer = 0;
            Step = 0;

            DreadLordCount = 0;

            EventRepeatCount = 5;

            ChainTimer = urand(12000, 15000);
            ThunderTimer = urand(6000, 8000);
            LavaBurstTimer = urand(16000, 20000);

            TalkEvent = false;
            UpdateWorldState = false;

            me->SetStandState(UNIT_STAND_STATE_STAND);
            me->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
            {
                sylvanas->SearchFormation();
                sylvanas->Mount(10719);
                sylvanas->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            }
        }
    }

    void sGossipSelect(Player* player, uint32 sender, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();

        if (!action)
        {
            if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
            {
                sylvanas->RemoveAllAuras();
                float homeX, homeY, homeZ, homeOrient;
                sylvanas->GetRespawnPosition(homeX, homeY, homeZ, &homeOrient);
                sylvanas->NearTeleportTo(homeX, homeY, homeZ, homeOrient);
                sylvanas->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_15);
                if (sylvanas->IsAIEnabled)
                    sylvanas->AI()->Reset();
                sylvanas->SearchFormation();
            }

            EnterEvadeMode();
            me->RemoveAllAuras();
            float homeX, homeY, homeZ, homeOrient;
            me->GetRespawnPosition(homeX, homeY, homeZ, &homeOrient);
            me->NearTeleportTo(homeX, homeY, homeZ, homeOrient);
            JustRespawned();
            if (Group* group = player->GetGroup())
            {
                for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
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
            case 1:
                SetEscortPaused(true);
                SetRun(false);

                me->Dismount();
                me->LoadEquipment(1, true);

                if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                {
                    sylvanas->Dismount();
                    sylvanas->LoadEquipment(1, true);
                }

                JumpToNextStep(2000);
                break;
            case 6:
                SetEscortPaused(true);
                DespawnCreatures(NPC_VORTEX);
                JumpToNextStep(2000);
                break;
            case 7:
                if (!_summons.empty())
                    SetEscortPaused(true);
                break;
            case 8:
                SetRun(false);
                break;
            case 9:
                SetEscortPaused(true);
                JumpToNextStep(3000);
                break;
            case 13:
                for (uint8 i = 3; i < 5; ++i)
                {
                    float x, y, z, orient;
                    HordeBannerSpawnPos[i].GetPosition(x, y, z, orient);
                    me->SummonGameObject(GO_HORDE_BANNER, x, y, z, orient, 0, 0, 0, 0, 120);
                }
                break;
            case 15:
                for (uint8 i = 5; i < 7; ++i)
                {
                    float x, y, z, orient;
                    HordeBannerSpawnPos[i].GetPosition(x, y, z, orient);
                    me->SummonGameObject(GO_HORDE_BANNER, x, y, z, orient, 0, 0, 0, 0, 120);
                }
                me->SummonCreature(NPC_WARSONG_BATTLEGUARD, HordeGuardSpawnPos[0]);
                break;
            case 17:
                SetEscortPaused(true);
                for (uint8 i = 1; i < 3; ++i)
                    me->SummonCreature(NPC_WARSONG_BATTLEGUARD, HordeGuardSpawnPos[i]);
                JumpToNextStep(3000);
                break;
            case 19:
                SetEscortPaused(true);
                Talk(17);
                DoUpdateWorldState(WORLDSTATE_BATTLING_INNER_SANCTUM, 1);
                JumpToNextStep(1500);
                break;
            case 20:
                DespawnCreatures(NPC_WARSONG_BATTLEGUARD);
                me->SummonCreature(NPC_TREACHEROUS_GUARDIAN_H, 1596.074829f, 273.708984f, -55.342854f, 4.594717f);
                break;
            case 21:
                SummonTrigger(3);
                break;
            case 22:
                SetEscortPaused(true);
                JumpToNextStep(1500);
                break;
            case 29:
                DespawnCreatures(NPC_WAVES_TRIGGER);
                for (uint8 i = 4; i < 6; ++i)
                    SummonTrigger(i);
                break;
            case 32:
                SetEscortPaused(true);
                DespawnCreatures(NPC_WAVES_TRIGGER);
                JumpToNextStep(2000);
                break;
            case 33:
                SetEscortPaused(true);
                JumpToNextStep(2000);
                break;
            case 36:
                SetEscortPaused(true);
                JumpToNextStep(1500);
                break;
            case 38:
                SetEscortPaused(true);
                JumpToNextStep(500);
                break;
            case 44:
                SetEscortPaused(true);
                if (Creature* varimathras = me->SummonCreature(NPC_VARIMATHRAS, 1289.77f, 314.98f, -57.32f, 1.30f))
                {
                    VarimathrasGUID = varimathras->GetGUID();
                    if (varimathras->IsAIEnabled)
                        varimathras->GetAI()->SetData(0, 1);

                    varimathras->CastSpell(varimathras, SPELL_AURA_OF_VARIMATHRAS, true);
                }
                JumpToNextStep(1500);
                break;
            case 45:
                SetEscortPaused(true);
                JumpToNextStep(4000);
                break;
            case 46:
                SetEscortPaused(true);
                JumpToNextStep(7000);
                break;
            case 47:
                SetEscortPaused(true);
                JumpToNextStep(5000);
                break;
            case 48:
                SetEscortPaused(true);
                JumpToNextStep(1000);
                break;
        }
    }

    void JumpToNextStep(uint32 Timer)
    {
        if (!zoneScript)
            return;

        TalkEvent = true;
        PhaseTimer = Timer;
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

    void SummonTrigger(uint8 pos) const
    {
        if (Creature* trigger  = me->SummonCreature(NPC_WAVES_TRIGGER, WaveTriggerSpawnPos[pos]))
            if (trigger->IsAIEnabled)
                trigger->GetAI()->SetData(0, pos + 12);
    }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        _summons.Despawn(summon);

        switch (summon->GetEntry())
        {
            case NPC_BLIGHT_ABBERATION:
            {
                EntryCheckPredicate pred(NPC_WAVES_TRIGGER);
                _summons.DoAction(0, pred);
                _summons.DespawnAll();

                SetEscortPaused(false);
                DoUpdateWorldState(WORLDSTATE_BATTLING_COURTYARD, 0);
                DoUpdateWorldState(WORLDSTATE_CONTROLL_COURTYARD, 1);
                break;
            }
            case NPC_KHANOK:
            {
                float x, y, z, orient;
                HordeBannerSpawnPos[7].GetPosition(x, y, z, orient);
                me->SummonGameObject(GO_HORDE_BANNER, x, y, z, orient, 0, 0, 0, 0, 60);

                DespawnCreatures(NPC_WAVES_TRIGGER);
                SetEscortPaused(false);
                SetRun(false);
                DoUpdateWorldState(WORLDSTATE_BATTLING_INNER_SANCTUM, 0);
                DoUpdateWorldState(WORLDSTATE_CONTROLL_INNER_SANCTUM, 1);
                break;
            }
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
                if (Creature* khanok = ObjectAccessor::GetCreature(*me, KhanokGUID))
                {
                    khanok->SetInCombatWith(me);
                    me->SetInCombatWith(khanok);
                    khanok->AddThreat(me, 10000.0f);
                    me->AddThreat(khanok, 10000.0f);
                    if (khanok->IsAIEnabled)
                        khanok->AI()->AttackStart(me);
                    AttackStart(khanok);
                }
                break;
            case 2:
                if (Creature* varimathras = ObjectAccessor::GetCreature(*me, VarimathrasGUID))
                    me->GetMotionMaster()->MovePoint(0, *varimathras);
                JumpToNextStep(2000);
                break;
            case 4:
                if (Creature* abberation = me->SummonCreature(NPC_BLIGHT_ABBERATION, 1805.87f, 296.87f, 70.40f, 4.68f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000))
                {
                    abberation->m_CombatDistance = 50.0f;
                    if (abberation->IsAIEnabled)
                    {
                        abberation->SetInCombatWith(me);
                        me->SetInCombatWith(abberation);
                        abberation->AddThreat(me, 10000.0f);
                        me->AddThreat(abberation, 10000.0f);
                        abberation->AI()->AttackStart(me);
                        AttackStart(abberation);
                    }
                }
                break;
            default:
                break;
        }
    }

    void DoAction(int32 /*actionId*/) override
    {
        ++DreadLordCount;
        if (DreadLordCount >= 10)
        {
            DespawnCreatures(NPC_WAVES_TRIGGER);
            SummonTrigger(10);
            if (Creature* khanok = me->SummonCreature(NPC_KHANOK, 1545.863403f, 390.755585f, -66.059479f, 0.206661f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000))
            {
                khanok->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                KhanokGUID = khanok->GetGUID();
            }
        }
    }

    void EnterCombat(Unit* /*victim*/) override
    {
        DoCastSelf(SPELL_HEROIC_VANGUARD);
    }

    bool CanAIAttack(Unit const* victim) const override
    {
        return victim->GetEntry() != NPC_DOOMGUARD_PILLARGER;
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

        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
        {
            sylvanas->RemoveAllAuras();
            float homeX, homeY, homeZ, homeOrient;
            sylvanas->GetRespawnPosition(homeX, homeY, homeZ, &homeOrient);
            sylvanas->NearTeleportTo(homeX, homeY, homeZ, homeOrient);
            sylvanas->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_15);
            if (sylvanas->IsAIEnabled)
                sylvanas->AI()->Reset();
        }

        for (uint32 i = 0; i < 12; ++i)
            DoUpdateWorldState(HordeWorldStates[i], i == 0 ? 1: 0);
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
                            case 1:
                                Talk(5);
                                break;
                            case 2:
                                Talk(4);
                                break;
                            case 3:
                                Talk(3);
                                break;
                            case 4:
                                Talk(2);
                                break;
                            default:
                                break;
                        }

                        DoUpdateWorldState(WORLDSTATE_BATTLE_TIMER, EventRepeatCount);
                        if (--EventRepeatCount)
                            _events.ScheduleEvent(EVENT_UPDATE_INTRO_WORLDSTATE, 1min);
                        else
                            _events.ScheduleEvent(EVENT_START_BATTLE, 1min);
                        break;
                    }
                    case EVENT_START_BATTLE:
                        UpdateWorldState = false;
                        Talk(6);

                        DoUpdateWorldState(WORLDSTATE_BATTLE_TIMER_STATE, 0);
                        DoUpdateWorldState(WORLDSTATE_BATTLE_TIMER, EventRepeatCount);
                        DoUpdateWorldState(WORLDSTATE_BATTLE_BEGUN, 1);

                        DoCastSelf(SPELL_WARCHIEFS_BLESSING);

                        JumpToNextStep(11000);
                        break;
                    case EVENT_START_OUTRO_BATTLE:
                        DoUpdateWorldState(WORLDSTATE_RESET_TIMER, EventRepeatCount);
                        if (--EventRepeatCount)
                            _events.ScheduleEvent(EVENT_START_OUTRO_BATTLE, 1min);
                        else
                            _events.ScheduleEvent(EVENT_UPDATE_OUTRO_WORLDSTATE, 1min);
                        break;
                    case EVENT_UPDATE_OUTRO_WORLDSTATE:
                        UpdateWorldState = false;
                        DoUpdateWorldState(WORLDSTATE_RESET_BATTLE, 0);
                        DoUpdateWorldState(WORLDSTATE_RESET_TIMER, EventRepeatCount);
                        DoUpdateWorldState(WORLDSTATE_CONTROLL_ROYAL_QUARTER, 0);
                        DoUpdateWorldState(WORLDSTATE_UNDERCITY_CONTROLLED_H, 1);

                        _summons.DespawnAll();
                        me->RemoveAllAuras();
                        me->setActive(false);
                        float homeX, homeY, homeZ, homeOrient;
                        me->GetRespawnPosition(homeX, homeY, homeZ, &homeOrient);
                        me->NearTeleportTo(homeX, homeY, homeZ, homeOrient);
                        JustRespawned();
                        me->Mount(me->GetCreatureAddon()->mount);
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                        {
                            sylvanas->RemoveAllAuras();
                            float homeX, homeY, homeZ, homeOrient;
                            sylvanas->GetRespawnPosition(homeX, homeY, homeZ, &homeOrient);
                            sylvanas->NearTeleportTo(homeX, homeY, homeZ, homeOrient);
                            sylvanas->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_15);
                            if (sylvanas->IsAIEnabled)
                            {
                                sylvanas->AI()->Reset();
                                sylvanas->SearchFormation();
                                sylvanas->Mount(10719);
                            }
                        }
                        TalkEvent = false;
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
                        DoUpdateWorldState(WORLDSTATE_BATTLE_TIMER_STATE, 1);
                        DoUpdateWorldState(WORLDSTATE_BATTLE_TIMER, EventRepeatCount);
                        UpdateWorldState = true;
                        --EventRepeatCount;
                        _events.ScheduleEvent(EVENT_UPDATE_INTRO_WORLDSTATE, 1min);
                        JumpToNextStep(7000);
                        break;
                    case 2:
                        Talk(1);
                        TalkEvent = false;
                        break;
                    case 3:
                        Talk(7);
                        Start(true, true, PlayerGUID);
                        TalkEvent = false;
                        break;
                    case 4:
                        me->SetSheath(SHEATH_STATE_MELEE);
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            sylvanas->SetSheath(SHEATH_STATE_RANGED);
                        Talk(8);
                        JumpToNextStep(3000);
                        break;
                    case 5:
                        Talk(9);
                        for (uint8 i = 0; i < 2; ++i)
                            if (Creature* vortex = me->SummonCreature(NPC_VORTEX, VortexSpawnPos[i]))
                                vortex->GetMotionMaster()->MovePath(NPC_VORTEX * 10 + i, false);
                        JumpToNextStep(8000);
                        break;
                    case 6:
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 7:
                        Talk(10);
                        JumpToNextStep(6000);
                        break;
                    case 8:
                        if (Creature* varimathras = me->SummonCreature(NPC_VARIMATHRAS, 1810.511597f, 236.830002f, 62.753681f))
                        {
                            varimathras->SetWalk(true);
                            VarimathrasGUID = varimathras->GetGUID();
                        }
                        JumpToNextStep(3000);
                        break;
                    case 9:
                        if (Creature* varimathras = ObjectAccessor::GetCreature(*me, VarimathrasGUID))
                            if (varimathras->IsAIEnabled)
                                varimathras->AI()->Talk(2);
                        JumpToNextStep(7000);
                        break;
                    case 10:
                        if (Creature* varimathras = ObjectAccessor::GetCreature(*me, VarimathrasGUID))
                            if (varimathras->IsAIEnabled)
                                varimathras->AI()->Talk(3);
                        JumpToNextStep(10000);
                        break;
                    case 11:
                            if (Creature* varimathras = ObjectAccessor::GetCreature(*me, VarimathrasGUID))
                            if (varimathras->IsAIEnabled)
                                varimathras->AI()->Talk(4);
                        JumpToNextStep(6000);
                        break;
                    case 12:
                        if (Creature* varimathras = ObjectAccessor::GetCreature(*me, VarimathrasGUID))
                            varimathras->CastSpell(varimathras, SPELL_LEGION_PORTAL, false);
                        JumpToNextStep(12000);
                        break;
                    case 13:
                        if (Creature* varimathras = ObjectAccessor::GetCreature(*me, VarimathrasGUID))
                            varimathras->GetMotionMaster()->MovePoint(0, 1800.72f, 237.11f, 62.76f);
                        JumpToNextStep(2000);
                        break;
                    case 14:
                    {
                        Talk(11);
                        if (Creature* varimathras = ObjectAccessor::GetCreature(*me, VarimathrasGUID))
                            varimathras->DespawnOrUnsummon();
                        DoCastAOE(SPELL_TIDAL_WAVE_SUMMON);
                        Position pos;
                        me->GetNearPosition(pos, 15.0f, 0.0f);
                        pos.SetOrientation(6.25f);
                        if (Creature* wave = me->SummonCreature(NPC_TIDAL_WAVE, pos))
                            TidalWaveGUID = wave->GetGUID();
                        JumpToNextStep(1000);
                        break;
                    }
                    case 15:
                        if (Creature* wave = ObjectAccessor::GetCreature(*me, TidalWaveGUID))
                        {
                            wave->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                            wave->SetSpeedRate(MOVE_RUN, 1.5f);
                            wave->CastSpell(wave, SPELL_TIDAY_FURY, true);
                            wave->CastSpell(wave, SPELL_TIDAL_WAVE, true);
                            wave->GetMotionMaster()->MovePoint(0, 1741.84f, 238.88f, 62.24f);
                        }
                        JumpToNextStep(8000);
                        break;
                    case 16:
                        SetEscortPaused(false);
                        SetRun(true);
                        Talk(12);
                        DoUpdateWorldState(WORLDSTATE_UNDERCITY_CONTROLLED_H, 0);
                        DoUpdateWorldState(WORLDSTATE_BATTLE_BEGUN, 0);
                        DoUpdateWorldState(WORLDSTATE_BATTLING_COURTYARD, 1);
                        if (Creature* wave = ObjectAccessor::GetCreature(*me, TidalWaveGUID))
                            wave->DespawnOrUnsummon();
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            sylvanas->m_CombatDistance = 50.0f;
                        for (uint8 i = 0; i < 5; ++i)
                        {
                            if (Creature* spreader = me->SummonCreature(NPC_BLIGHT_SPREADER, SpreaderSpawnPos[i]))
                            {
                                spreader->m_CombatDistance = 120.0f;
                                if (spreader->IsAIEnabled)
                                    spreader->AI()->AttackStart(me);
                            }

                            if (i > 2)
                                continue;

                            SummonTrigger(i);
                        }
                        JumpToNextStep(10000);
                        break;
                    case 17:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                        {
                            sylvanas->CastSpell(sylvanas, SPELL_SONG_OF_SYLVANAS, true);
                            DoPlaySoundToSet(sylvanas, SOUND_LAMENT);
                            if (sylvanas->IsAIEnabled)
                                sylvanas->AI()->Talk(0);
                        }
                        TalkEvent = false;
                        break;
                    case 18:
                        Talk(13);
                        for (uint8 i = 0; i < 3; ++i)
                        {
                            float x, y, z, orient;
                            HordeBannerSpawnPos[i].GetPosition(x, y, z, orient);
                            me->SummonGameObject(GO_HORDE_BANNER, x, y, z, orient, 0, 0, 0, 0, 30);
                        }
                        JumpToNextStep(6000);
                        break;
                    case 19:
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 20:
                        Talk(14);
                        JumpToNextStep(4000);
                        break;
                    case 21:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            if (sylvanas->IsAIEnabled)
                                sylvanas->AI()->Talk(1);
                        JumpToNextStep(5000);
                        break;
                    case 22:
                        Talk(15);
                        DoCastSelf(SPELL_CALL_OF_AIR);
                        JumpToNextStep(5000);
                        break;
                    case 23:
                        for (uint8 i = 0; i < 4; ++i)
                            me->SummonCreature(NPC_WHIRLWIND, CycloneSpawnPos[i]);
                        JumpToNextStep(8000);
                        break;
                    case 24:
                        SetRun(true);
                        Talk(16);
                        if (Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID))
                            if (Group* group = player->GetGroup())
                            {
                                for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
                                    if (Player* member = itr->GetSource())
                                        if (member->IsAlive())
                                            member->CastSpell(player, SPELL_CYCLONE_FALL, true);
                            }
                            else
                                player->CastSpell(player, SPELL_CYCLONE_FALL, true);
                        JumpToNextStep(5000);
                        break;
                    case 25:
                        me->GetMotionMaster()->MoveJump(1547.29f, 248.38f, -19.62f, 10.0f, 20.0f, 1);
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                        {
                            if (sylvanas->GetFormation())
                                sylvanas->GetFormation()->RemoveMember(sylvanas);
                            sylvanas->GetMotionMaster()->MoveJump(1547.29f, 248.38f, -19.62f, 10.0f, 10.0f, 1);
                        }
                        JumpToNextStep(10000);
                        break;
                    case 26:
                        me->GetMotionMaster()->MoveJump(1537.12f, 240.63f, -41.36f, 10.0f, 20.0f, 2);
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            sylvanas->GetMotionMaster()->MoveJump(1537.12f, 240.63f, -41.36f, 10.0f, 10.0f, 2);
                        JumpToNextStep(10000);
                        break;
                    case 27:
                        SetRun(false);
                        if (Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID))
                            if (Group* group = player->GetGroup())
                            {
                                for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
                                    if (Player* member = itr->GetSource())
                                        member->RemoveAurasDueToSpell(SPELL_CYCLONE_FALL);
                            }
                            else
                                player->RemoveAurasDueToSpell(SPELL_CYCLONE_FALL);
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            sylvanas->SearchFormation();
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 28:
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 29:
                        DespawnCreatures(NPC_WHIRLWIND);
                        me->SetFacingTo(0.133856f);
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            sylvanas->SetFacingTo(0.133856f);
                        JumpToNextStep(1500);
                        break;
                    case 30:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            if (sylvanas->IsAIEnabled)
                                sylvanas->AI()->Talk(2);
                        JumpToNextStep(6500);
                        break;
                    case 31:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            if (sylvanas->IsAIEnabled)
                                sylvanas->AI()->Talk(3);
                        JumpToNextStep(8500);
                        break;
                    case 32:
                        Talk(18);
                        JumpToNextStep(8000);
                        break;
                    case 33:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            if (sylvanas->IsAIEnabled)
                                sylvanas->AI()->Talk(4);
                        JumpToNextStep(1100);
                        break;
                    case 34:
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 35:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                        {
                            sylvanas->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                            if (sylvanas->IsAIEnabled)
                                sylvanas->AI()->Talk(5);
                        }
                        JumpToNextStep(6000);
                        break;
                    case 36:
                        if (Creature* varimathras = me->SummonCreature(NPC_VARIMATHRAS, 1596.60f, 419.62f, -45.41f, 4.66f))
                        {
                            if (varimathras->IsAIEnabled)
                                varimathras->AI()->Talk(5);
                            varimathras->SetWalk(true);
                            VarimathrasGUID = varimathras->GetGUID();
                        }
                        JumpToNextStep(4000);
                        break;
                    case 37:
                        if (Creature* varimathras = ObjectAccessor::GetCreature(*me, VarimathrasGUID))
                        {
                            if (varimathras->IsAIEnabled)
                                varimathras->AI()->Talk(6);
                            varimathras->CastSpell(varimathras, SPELL_LEGION_PORTAL, false);
                        }
                        JumpToNextStep(4000);
                        break;
                    case 38:
                        if (Creature* varimathras = ObjectAccessor::GetCreature(*me, VarimathrasGUID))
                        {
                            Position pos;
                            varimathras->GetNearPosition(pos, 15.0f, M_PI);
                            varimathras->GetMotionMaster()->MovePoint(0, pos);
                        }
                        JumpToNextStep(2000);
                        break;
                    case 39:
                        if (Creature* varimathras = ObjectAccessor::GetCreature(*me, VarimathrasGUID))
                            varimathras->DespawnOrUnsummon();
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            sylvanas->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                        DespawnCreatures(NPC_WAVES_TRIGGER);
                        for (uint8 i = 6; i < 11; ++i)
                            SummonTrigger(i);
                        TalkEvent = false;
                        break;
                    case 40:
                        Talk(19);
                        JumpToNextStep(5000);
                        break;
                    case 41:
                        Talk(20);
                        JumpToNextStep(6000);
                        break;
                    case 42:
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 43:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            if (sylvanas->IsAIEnabled)
                                sylvanas->AI()->Talk(6);
                        JumpToNextStep(4000);
                        break;
                    case 44:
                        if (Creature* varimathras = DoSpawnCreature(NPC_VARIMATHRAS, 0.0f, 0.0f, 20.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10000))
                        {
                            if (varimathras->IsAIEnabled)
                                varimathras->AI()->Talk(7);
                            varimathras->SetVisible(false);
                        }
                        me->SummonCreature(NPC_CAVE_DUMMY, 1442.34f, 398.28f, -57.86f, 5.42f);
                        if (GameObject* passage = me->SummonGameObject(GO_BLOCKED_PASSAGE, 1442.34f, 398.28f, -57.86f, 5.42f, 0, 0, 0, 0, 300))
                        {
                            PassageGUID = passage->GetGUID();
                            passage->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                        }
                        JumpToNextStep(3000);
                        break;
                    case 45:
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 46:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            sylvanas->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                        JumpToNextStep(3000);
                        break;
                    case 47:
                        Talk(21);
                        JumpToNextStep(10000);
                        break;
                    case 48:
                        Talk(22);
                        DoCastAOE(SPELL_CALL_OF_EARTH);
                        JumpToNextStep(6000);
                        break;
                    case 49:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            sylvanas->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                        DoUpdateWorldState(WORLDSTATE_BATTLING_ROYAL_QUARTER, 1);
                        if (GameObject* passage = ObjectAccessor::GetGameObject(*me, PassageGUID))
                            passage->UseDoorOrButton();
                        JumpToNextStep(3000);
                        break;
                    case 50:
                        if (GameObject* passage = ObjectAccessor::GetGameObject(*me, PassageGUID))
                            passage->Delete();
                        DespawnCreatures(NPC_CAVE_DUMMY);
                        JumpToNextStep(3000);
                        break;
                    case 51:
                        Talk(23);
                        SetRun(true);
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 52:
                        Talk(24);
                        JumpToNextStep(4000);
                        break;
                    case 53:
                        if (Creature* varimathras = ObjectAccessor::GetCreature(*me, VarimathrasGUID))
                            if (varimathras->IsAIEnabled)
                            {
                                varimathras->AI()->Talk(8);
                                varimathras->AI()->SetData(0, 2);
                            }
                        TalkEvent = false;
                        break;
                    case 54:
                        Talk(25);
                        JumpToNextStep(4500);
                        break;
                    case 55:
                        Talk(26);
                        JumpToNextStep(6000);
                        break;
                    case 56:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            if (sylvanas->GetFormation())
                                sylvanas->GetFormation()->RemoveMember(sylvanas);
                        SetRun(true);
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 57:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            me->SetFacingToObject(sylvanas);
                        JumpToNextStep(1500);
                        break;
                    case 58:
                        Talk(27);
                        JumpToNextStep(4000);
                        break;
                    case 59:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            sylvanas->CastSpell(sylvanas, SPELL_LEAP_TO_PLATFORM, true);
                        JumpToNextStep(6000);
                        break;
                    case 60:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            if (sylvanas->IsAIEnabled)
                                sylvanas->AI()->Talk(7);
                        JumpToNextStep(500);
                        break;
                    case 61:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                            me->SetFacingToObject(sylvanas);
                        JumpToNextStep(8000);
                        break;
                    case 62:
                        Talk(28);
                        SetRun(false);
                        SetEscortPaused(false);
                        JumpToNextStep(5000);
                        break;
                    case 63:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                        {
                            sylvanas->SetWalk(true);
                            sylvanas->GetMotionMaster()->MovePoint(2, 1300.53f, 341.01f, -60.08f);
                        }
                        TalkEvent = false;
                        break;
                    case 64:
                    {
                        if (Creature* varian = me->SummonCreature(NPC_VARIAN_H, 1312.927490f, 396.034393f, -62.858009f, 4.392927f))
                        {
                            VarianGUID = varian->GetGUID();

                            for (uint8 i = 0; i < 10; ++i)
                            {
                                float angle = (M_PI / 10) * i - M_PI;
                                Position pos;
                                varian->GetNearPosition(pos, 2.0f, angle);
                                if (Creature* elite = me->SummonCreature(NPC_STORMWIND_ELITE, pos))
                                {
                                    elite->SetFacingTo(varian->GetOrientation());
                                    elite->GetMotionMaster()->MoveFollow(varian, 1.0f, varian->GetAngle(elite));
                                }
                            }
                        }
                        Talk(29);
                        Position pos;
                        me->GetNearPosition(pos, 5.0f, 0.0f);
                        me->GetMotionMaster()->MoveJump(pos, 10.0f, 10.0f);
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, zoneScript->GetData64(DATA_SYLVANAS)))
                        {
                            sylvanas->GetNearPosition(pos, 5.0f, 0.0f);
                            sylvanas->GetMotionMaster()->MoveJump(pos, 10.0f, 10.0f);
                        }
                        JumpToNextStep(6000);
                        break;
                    }
                    case 65:
                        if (Creature* varian = ObjectAccessor::GetCreature(*me, VarianGUID))
                            varian->GetMotionMaster()->MovePoint(0, 1302.529f, 359.509f, -67.295f);
                        JumpToNextStep(8000);
                        break;
                    case 66:
                        if (Creature* varian = ObjectAccessor::GetCreature(*me, VarianGUID))
                            if (varian->IsAIEnabled)
                                varian->AI()->Talk(0);
                        JumpToNextStep(17000);
                        break;
                    case 67:
                        if (Creature* varian = ObjectAccessor::GetCreature(*me, VarianGUID))
                            if (varian->IsAIEnabled)
                                varian->AI()->Talk(1);
                        JumpToNextStep(13000);
                        break;
                    case 68:
                        if (Creature* varian = ObjectAccessor::GetCreature(*me, VarianGUID))
                            if (varian->IsAIEnabled)
                                varian->AI()->Talk(2);
                        JumpToNextStep(17000);
                        break;
                    case 69:
                        if (Creature* varian = ObjectAccessor::GetCreature(*me, VarianGUID))
                            if (varian->IsAIEnabled)
                                varian->AI()->Talk(3);
                        JumpToNextStep(12000);
                        break;
                    case 70:
                        if (Creature* varian = ObjectAccessor::GetCreature(*me, VarianGUID))
                            if (varian->IsAIEnabled)
                                varian->AI()->Talk(4);
                        for(auto &guid : _summons)
                            if (Creature* summon = ObjectAccessor::GetCreature(*me, guid))
                            {
                                summon->Dismount();
                                summon->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_15 | UNIT_FLAG_PACIFIED);
                                if (summon->IsAIEnabled)
                                    summon->AI()->AttackStart(me);
                            }
                        JumpToNextStep(10000);
                        break;
                    case 71:
                        if (Creature* jaina = me->SummonCreature(NPC_JAINA_PROUDMORE, 1305.02f, 370.15f, -67.29f, 4.33f))
                        {
                            JainaGUID = jaina->GetGUID();
                            jaina->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_UNK_15 | UNIT_FLAG_PACIFIED);
                        }
                        JumpToNextStep(1000);
                        break;
                    case 72:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, JainaGUID))
                            if (jaina->IsAIEnabled)
                                jaina->AI()->Talk(3);
                        JumpToNextStep(8000);
                        break;
                    case 73:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, JainaGUID))
                            jaina->GetMotionMaster()->MovePoint(1, 1299.30f, 348.18f, -65.02f);
                        JumpToNextStep(10000);
                        break;
                    case 74:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, JainaGUID))
                            jaina->CastSpell(jaina, SPELL_DEEP_FREEZE, false);
                        JumpToNextStep(5000);
                        break;
                    case 75:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, JainaGUID))
                            if (jaina->IsAIEnabled)
                                jaina->AI()->Talk(4);
                        JumpToNextStep(7000);
                        break;
                    case 76:
                        if (Creature* jaina = ObjectAccessor::GetCreature(*me, JainaGUID))
                            jaina->CastSpell(jaina, SPELL_GREATER_MASS_TELEPORT, false);
                        JumpToNextStep(4500);
                        break;
                    case 77:
                        DespawnCreatures(NPC_VARIAN_H);
                        DespawnCreatures(NPC_STORMWIND_ELITE);
                        JumpToNextStep(4000);
                        break;
                    case 78:
                        me->setActive(true);
                        DespawnCreatures(NPC_JAINA_PROUDMORE);
                        EventRepeatCount = 5;
                        DoUpdateWorldState(WORLDSTATE_CONTROLL_COURTYARD, 0);
                        DoUpdateWorldState(WORLDSTATE_CONTROLL_INNER_SANCTUM, 0);
                        DoUpdateWorldState(WORLDSTATE_BATTLING_ROYAL_QUARTER, 0);
                        DoUpdateWorldState(WORLDSTATE_CONTROLL_ROYAL_QUARTER, 1);
                        DoUpdateWorldState(WORLDSTATE_RESET_BATTLE, 1);
                        DoUpdateWorldState(WORLDSTATE_RESET_TIMER, EventRepeatCount);
                        UpdateWorldState = true;
                        --EventRepeatCount;
                        _events.ScheduleEvent(EVENT_START_OUTRO_BATTLE, 1min);
                        JumpToNextStep(4000);
                        break;
                    case 79:
                        me->SummonGameObject(GO_PORTAL_ORGRIMMAR, 1289.77f, 314.98f, -57.32f, 1.30f, 0, 0, 0, 0, 300);
                        SetRun(false);
                        Talk(30);
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 80:
                        Talk(31);
                        JumpToNextStep(15000);
                        break;
                    case 81:
                        SetEscortPaused(false);
                        TalkEvent = false;
                        break;
                    case 82:
                        me->SetFacingTo(1.239064f);
                        JumpToNextStep(1000);
                        break;
                    case 83:
                        Talk(32);
                        me->SetStandState(UNIT_STAND_STATE_SIT);
                        JumpToNextStep(3000);
                        me->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        break;
                    case 84:
                        if (Creature* saurfang = me->SummonCreature(NPC_SAURFANG, 1302.25f, 338.33f, -60.083f, 1.02f))
                        {
                            SaurfangGUID = saurfang->GetGUID();
                            saurfang->SetWalk(true);
                            Position pos;
                            saurfang->GetNearPosition(pos, 5.0f, 0.0f);
                            saurfang->GetMotionMaster()->MoveJump(pos, 10.0f, 10.0f);
                        }
                        JumpToNextStep(1000);
                        break;
                    case 85:
                        if (Creature* saurfang = ObjectAccessor::GetCreature(*me, SaurfangGUID))
                            saurfang->GetMotionMaster()->MovePoint(1, 1303.50f, 352.05f, -65.63f);
                        JumpToNextStep(6000);
                        break;
                    case 86:
                        if (Creature* saurfang = ObjectAccessor::GetCreature(*me, SaurfangGUID))
                        {
                            saurfang->SetStandState(UNIT_STAND_STATE_SIT);
                            if (saurfang->IsAIEnabled)
                                saurfang->AI()->Talk(0);
                        }
                        JumpToNextStep(5000);
                        break;
                    case 87:
                        if (Creature* saurfang = ObjectAccessor::GetCreature(*me, SaurfangGUID))
                            if (saurfang->IsAIEnabled)
                                saurfang->AI()->Talk(1);
                        JumpToNextStep(7000);
                        break;
                    case 88:
                        if (Creature* saurfang = ObjectAccessor::GetCreature(*me, SaurfangGUID))
                            if (saurfang->IsAIEnabled)
                                saurfang->AI()->Talk(2);
                        JumpToNextStep(4000);
                        break;
                    case 89:
                        Talk(34);
                        JumpToNextStep(5000);
                        break;
                    case 90:
                        Talk(33);
                        TalkEvent = false;
                        break;
                }
            }
            else
                PhaseTimer -= diff;

        if (!UpdateVictim())
            return;

        if (ChainTimer <= diff)
        {
            DoCastVictim(SPELL_CHAIN_LIGHTNING);
            ChainTimer = urand(20000, 25000);
        }
        else
            ChainTimer -= diff;

        if (ThunderTimer <= diff)
        {
            DoCastVictim(SPELL_THUNDER);
            ThunderTimer = urand(12000, 18000);
        }
        else
            ThunderTimer -= diff;

        if (LavaBurstTimer <= diff)
        {
            DoCastVictim(SPELL_LAVA_BURST);
            LavaBurstTimer = urand(26000, 30000);
        }
        else
            LavaBurstTimer -= diff;

        DoMeleeAttackIfReady();
    }

};

struct npc_tidal_waveAI : public ScriptedAI
{
    npc_tidal_waveAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        DoCastSelf(SPELL_WATER_REVENANT_ENTRANCE);
    }

    void SpellHitTarget(Unit* target, SpellInfo const* spellInfo) override
    {
        if (spellInfo->Id != SPELL_TIDAY_FURY_EFFECT)
            return;

        if (Creature* creature = target->ToCreature())
            creature->DespawnOrUnsummon(5s);
    }
};

struct npc_varimathras_battle_undercityAI : public ScriptedAI
{
    npc_varimathras_battle_undercityAI(Creature* creature) : ScriptedAI(creature), _summons(me)
    {
        ThrallGUID = 0;
    }

    SummonList _summons;
    std::list<Creature*> Portals;

    bool StartEvent;

    uint64 ThrallGUID;
    uint32 EventTimer;
    uint32 WaveTimer;
    uint8 WaveCount;
    uint8 EventPhase;

    uint32 CarrionSwarmTimer;
    uint32 DrainLifeTimer;
    uint32 ShadowBoltVolleyTimer;

    void Reset() override
    {
        _summons.DespawnAll();
        Portals.clear();

        StartEvent = false;
        EventTimer = 54000;
        WaveTimer = 6000;
        WaveCount = 0;
        EventPhase = 0;

        CarrionSwarmTimer = urand(15500, 30000);
        DrainLifeTimer = urand(12500, 15000);
        ShadowBoltVolleyTimer = urand(5000, 10000);
    }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);

        if (summon->GetEntry() == NPC_VARIMATHRAS_PORTAL)
            Portals.push_back(summon);
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        _summons.Despawn(summon);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        _summons.Despawn(summon);

        if (summon->GetEntry() == NPC_VARIMATHRAS_PORTAL)
            Portals.remove(summon);
    }

    void IsSummonedBy(Unit* summoner) override
    {
        ThrallGUID = summoner->GetGUID();
    }

    void EnterCombat(Unit* target)
    {
        DoCastSelf(SPELL_MIGHT_OF_VARIMATHRAS);
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(15);
        _summons.DespawnAll();
        if (Creature* thrall = ObjectAccessor::GetCreature(*me, ThrallGUID))
            if (thrall->IsAIEnabled)
                thrall->GetAI()->SetData(0, 2);
    }

    void SetData(uint32 type, uint32 data) override
    {
        switch (data)
        {
            case 1:
                for (uint8 i = 0; i < 6; ++i)
                    if (Creature* portal = me->SummonCreature(NPC_VARIMATHRAS_PORTAL, PortalSpawnPos[i]))
                        portal->CastSpell(me, SPELL_OPENING_LEGION_PORTALS, true);
                break;
            case 2:
                StartEvent = true;
                break;
        }
    }

    void DoAction(int32 /*action*/) override
    {
        switch (++EventPhase)
        {
            case 1:
                Talk(9);
                EventTimer = 60000;
                break;
            case 2:
                Talk(10);
                EventTimer = 30000;
                break;
            case 3:
                Talk(11);
                EventTimer = 30000;
                break;
            case 4:
                Talk(12);
                EventTimer = 15000;
                break;
            case 5:
                Talk(13);
                EventTimer = 3000;
                break;
            case 6:
                Talk(14);
                EventTimer = 6000;
                break;
        }
    }

    void DestroyPortal() const
    {
        if (!Portals.empty())
            if (Creature* portal = Trinity::Containers::SelectRandomContainerElement(Portals))
                portal->CastSpell(me, SPELL_PORTAL_COLLAPSE, false);
    }

    void SummonMobs()
    {
        WaveTimer = 6000;

        if (!Portals.empty())
            for (auto portal : Portals)
            {
                uint32 WaveEntry = 0;
                switch (WaveCount)
                {
                    case 0:
                        WaveEntry = NPC_LEGION_INVADER;
                        break;
                    case 1:
                        WaveEntry = NPC_LEGION_DREADWHISPER;
                        break;
                    case 2:
                        WaveEntry = RAND(NPC_LEGION_INVADER, NPC_LEGION_DREADWHISPER, NPC_LEGION_OVERLORD);
                        WaveTimer = 12000;
                        break;
                }

                if (!WaveEntry)
                    return;

                ++WaveCount;
                if (WaveCount > 2)
                    WaveCount = 0;

                Position pos;
                portal->GetNearPosition(pos, 2.0f, 0.0f);
                if (Creature* summon = me->SummonCreature(WaveEntry, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000))
                {
                    summon->m_CombatDistance = 50.0f;
                    if (Creature* thrall = ObjectAccessor::GetCreature(*me, ThrallGUID))
                        if (summon->IsAIEnabled)
                            summon->AI()->AttackStart(thrall);
                }
            }
    }

    void UpdateAI(uint32 diff) override
    {
        if (StartEvent)
        {
            if (WaveTimer <= diff)
                SummonMobs();
            else
                WaveTimer -= diff;

            if (EventTimer <= diff)
            {
                switch (EventPhase)
                {
                    case 5:
                        if (Creature* voice = DoSpawnCreature(NPC_DISTANT_VOICE, 0.0f, 0.0f, 20.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10000))
                        {
                            if (voice->IsAIEnabled)
                                voice->AI()->Talk(6);
                            voice->SetVisible(false);
                        }
                        DestroyPortal();
                        EventTimer = 60000;
                        break;
                    case 6:
                        StartEvent = false;
                        me->RemoveAllAuras();
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                        if (Creature* thrall = ObjectAccessor::GetCreature(*me, ThrallGUID))
                            AttackStart(thrall);
                        EventTimer = 60000;
                        break;
                    default:
                        DestroyPortal();
                        EventTimer = 60000;
                        break;
                }
            }
            else
                EventTimer -= diff;
        }

        if (!UpdateVictim())
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING) || me->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
            return;

        if (CarrionSwarmTimer <= diff)
        {
            DoCastVictim(SPELL_CARION_SWARM);
            CarrionSwarmTimer = urand(21000, 30000);
        }
        else
            CarrionSwarmTimer -= diff;

        if (DrainLifeTimer <= diff)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f))
                DoCast(target, SPELL_DRAIN_LIFE, false);
            DrainLifeTimer = urand(12000, 15000);
        }
        else
            DrainLifeTimer -= diff;

        if (ShadowBoltVolleyTimer <= diff)
        {
            DoCastVictim(SPELL_SHADOW_BOLT_VOLLEY);
            ShadowBoltVolleyTimer = urand(7000, 12000);
        }
        else
            ShadowBoltVolleyTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

class spell_hurl_boulder_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_hurl_boulder_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        Trinity::Containers::RandomResize(targets, 1);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hurl_boulder_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
    }
};

class spell_blight_barrel_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_blight_barrel_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        Trinity::Containers::RandomResize(targets, 1);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_blight_barrel_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
    }
};

class spell_portal_collapse_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_portal_collapse_SpellScript);

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            if (Creature* portal = caster->ToCreature())
            {
                if (Creature* varimathras = portal->ToTempSummon()->GetSummonerCreatureBase())
                    if (varimathras->IsAIEnabled)
                        varimathras->GetAI()->DoAction(0);

                portal->CastSpell(caster, SPELL_TELEPORT_SPAWN_VISUAL, true);
                portal->DespawnOrUnsummon(1.5s);
            }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_portal_collapse_SpellScript::HandleAfterCast);
    }
};

void AddSC_battle_for_undercity_horde()
{
    new CreatureAILoader<npc_thrall_battle_undercityAI>("npc_thrall_battle_undercity");
    new CreatureAILoader<npc_tidal_waveAI>("npc_tidal_wave");
    new CreatureAILoader<npc_varimathras_battle_undercityAI>("npc_varimathras_battle_undercity");
    new SpellScriptLoaderEx<spell_hurl_boulder_SpellScript>("spell_hurl_boulder");
    new SpellScriptLoaderEx<spell_blight_barrel_SpellScript>("spell_blight_barrel");
    new SpellScriptLoaderEx<spell_portal_collapse_SpellScript>("spell_portal_collapse");
}
