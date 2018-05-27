#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "old_hillsbrad.h"
#include "Player.h"

enum OHFSays
{
    SAY_START_EVENT_PART1       = 0,
    SAY_ARMORY,
    SAY_SKARLOC_MEET,
    SAY_SKARLOC_TAUNT,
    SAY_START_EVENT_PART2,
    SAY_MOUNTS_UP,
    SAY_CHURCH_END,
    SAY_MEET_TARETHA,
    SAY_EPOCH_WONDER,
    SAY_EPOCH_KILL_TARETHA,
    SAY_EVENT_COMPLETE,
    SAY_RANDOM_LOW_HP,
    SAY_RANDOM_DIE,
    SAY_RANDOM_AGGRO,
    SAY_RANDOM_KILL,
    SAY_LEAVE_COMBAT,
    SAY_KILL_ARMORER,
    SAY_GO_ARMORED,
    SAY_ENTER_CHURCH,
    SAY_GREET_TARETHA,
    SAY_CHAT_TARETHA1,

    SAY_TARETHA_FREE            = 0,
    SAY_TARETHA_ESCAPED,
    SAY_TARETHA_TALK1,
    SAY_TARETHA_TALK2,

    SAY_ARMORER_THRALL          = 0,

    SAY_LOOKOUT_SAW             = 0,
    SAY_LOOKOUT_GO,
    SAY_LOOKOUT_CHURCH,
    SAY_LOOKOUT_INN,

    SAY_EPOCH_ENTER1            = 0,
    SAY_EPOCH_ENTER2,
    SAY_EPOCH_ENTER3,

    SAY_EROZION_1               = 0,
    SAY_EROZION_2,
    SAY_EROZION_3
};

enum OHFSpells
{
    SPELL_STRIKE                = 14516,
    SPELL_SHIELD_BLOCK          = 12169,
    SPELL_SUMMON_EROZION_IMAGE  = 33954,

    SPELL_SHADOW_PRISON         = 33071,
    SPELL_SHADOW_SPIKE          = 33125,

    SPELL_TELEPORT              = 34776,
    SPELL_MEMORY_WIPE           = 33336,
    SPELL_MEMORY_WIPE_RESUME    = 33337
};

enum OHFNPCs
{
    NPC_TM_GUARDSMAN            = 18092,
    NPC_TM_PROTECTOR            = 18093,
    NPC_TM_LOOKOUT              = 18094,

    NPC_EPOCH_GUARDSMAN         = 23175,
    NPC_EPOCH_PROTECTOR         = 23179,
    NPC_EPOCH_LOOKOUT           = 23177,

    NPC_INFINITE_DEFILER        = 18171,
    NPC_INFINITE_SABOTEUR       = 18172,
    NPC_INFINITE_SLAYER         = 18170
};

enum OHFMisc
{
    THRALL_WEAPON_ITEM          = 927,
    THRALL_SHIELD_ITEM          = 2129,
    THRALL_MODEL_UNEQUIPPED     = 17292,
    THRALL_MODEL_EQUIPPED       = 18165,

    ACTION_SET_IMMUNE_FLAG      = 1,
    ACTION_REMOVE_IMMUNE_FLAG,
    ACTION_TRANSFORM,
    ACTION_MOVE,
    ACTION_START_COMBAT
};

#define SPEED_RUNNING            1.0f
#define SPEED_MOUNTED            1.6f

enum Events
{
    // Combat
    EVENT_CHECK_HEALTH          = 1,
    EVENT_STRIKE,
    EVENT_SHIELD_BLOCK,

    EVENT_OPEN_DOORS            = 6,
    EVENT_START_WP,

    EVENT_SET_FACING            = 9,
    EVENT_KILL_ARMORER,
    EVENT_TALK_KILL_ARMORER,

    EVENT_DRESSING_KNEEL        = 20,
    EVENT_DRESSING_ARMOR,
    EVENT_DRESSING_STAND,
    EVENT_DRESSING_AXE,
    EVENT_DRESSING_SHIELD,
    EVENT_DRESSING_TALK,

    EVENT_ENTER_MOUNT           = 30,
    EVENT_TALK_START_RIDE,

    EVENT_LOOK_1                = 40,
    EVENT_MOVE_AROUND,
    EVENT_LOOK_2,
    EVENT_LOOK_3,
    EVENT_SUMMON_GUARDS,
    EVENT_SUMMON_TALK1,
    EVENT_SUMMON_TALK2,

    EVENT_LOOK_4                = 50,
    EVENT_SUMMON_GUARDS_2,
    EVENT_SUMMON_TALK3,

    EVENT_THRALL_TALK           = 60,
    EVENT_SUMMON_CHRONO,
    EVENT_THRALL_TALK_2,
    EVENT_TARETHA_FALL,
    EVENT_THRALL_TALK_3,
    EVENT_THRALL_MOVE_DOWN,

    EVENT_EPOCH_INTRO           = 70,
    EVENT_SUMMON_INFINITES,
    EVENT_TRANSFORM,
    EVENT_START_WAVE_1,
    EVENT_CHECK_WAVE_1,
    EVENT_CHECK_WAVE_2,
    EVENT_CHECK_WAVE_3,
    EVENT_CALL_EPOCH,

    EVENT_THRALL_FACE_TARETHA   = 80,
    EVENT_THRALL_TALK_4,
    EVENT_TARETHA_TALK_1,
    EVENT_THRALL_TALK_5,
    EVENT_SUMMON_EROZION,
    EVENT_EROZION_TALK_1,
    EVENT_EROZION_ACTION_1,
    EVENT_EROZION_TALK_2,
    EVENT_EROZION_ACTION_2,
    EVENT_EROZION_TALK_3,
    EVENT_THRALL_TALK_6,
    EVENT_THRALL_RUN_AWAY,
    EVENT_TARETHA_TALK_2
};

class npc_thrall_old_hillsbrad : public CreatureScript
{
    public:
        npc_thrall_old_hillsbrad() : CreatureScript("npc_thrall_old_hillsbrad") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            auto instance = creature->GetInstanceScript();
            if (!instance)
                return true;

            auto menuId = creature->GetCreatureTemplate()->GossipMenuId;
            switch (instance->GetData(DATA_ESCORT_PROGRESS))
            {
                case ENCOUNTER_PROGRESS_SKARLOC_KILLED:
                    menuId = 7830;
                    break;
                case ENCOUNTER_PROGRESS_TARREN_MILL:
                    menuId = 7840;
                    break;
                case ENCOUNTER_PROGRESS_TARETHA_MEET:
                    menuId = 7853;
                    break;
                default:
                    break;
            }

            player->PrepareGossipMenu(creature, menuId, true);
            player->SendPreparedGossip(creature);
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
        {
            auto const* gossipMenuItemData = player->PlayerTalkClass->GetGossipMenu().GetItemData(0);
            auto instance = creature->GetInstanceScript();
            if (!instance || (gossipMenuItemData && gossipMenuItemData->GossipActionMenuId != 0))
                return false;

            player->PlayerTalkClass->ClearMenus();
            player->CLOSE_GOSSIP_MENU();

            if (creature->IsAIEnabled)
                creature->AI()->DoAction(instance->GetData(DATA_ESCORT_PROGRESS));
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
            return true;
        }

        struct npc_thrall_old_hillsbradAI : public npc_escortAI
        {
            npc_thrall_old_hillsbradAI(Creature* creature) : npc_escortAI(creature), _summons(me)
            {
                _instance = creature->GetInstanceScript();
            }

            void DoAction(int32 param) override
            {
                switch (param)
                {
                    case ENCOUNTER_PROGRESS_DRAKE_KILLED:
                        _events.ScheduleEvent(EVENT_OPEN_DOORS, 0s);
                        _events.ScheduleEvent(EVENT_START_WP, 3s);
                        break;
                    case ENCOUNTER_PROGRESS_THRALL_ARMORED:
                    case ENCOUNTER_PROGRESS_AMBUSHES_1:
                    case ENCOUNTER_PROGRESS_SKARLOC_KILLED:
                    case ENCOUNTER_PROGRESS_TARREN_MILL:
                        SetEscortPaused(false);
                        break;
                    case ENCOUNTER_PROGRESS_TARETHA_MEET:
                        _events.ScheduleEvent(EVENT_SUMMON_CHRONO, 0s);
                        _events.ScheduleEvent(EVENT_THRALL_TALK_2, 6s);
                        _events.ScheduleEvent(EVENT_TARETHA_FALL, 11s);
                        _events.ScheduleEvent(EVENT_THRALL_TALK_3, 14s);
                        _events.ScheduleEvent(EVENT_THRALL_MOVE_DOWN, 17s);
                        break;
                    case NPC_TARETHA:
                        _events.ScheduleEvent(EVENT_THRALL_FACE_TARETHA, 0s);
                        _events.ScheduleEvent(EVENT_THRALL_TALK_4, 4s);
                        _events.ScheduleEvent(EVENT_TARETHA_TALK_1, 13s);
                        _events.ScheduleEvent(EVENT_THRALL_TALK_5, 17s);
                        _events.ScheduleEvent(EVENT_SUMMON_EROZION, 17.5s);
                        _events.ScheduleEvent(EVENT_EROZION_TALK_1, 18s);
                        _events.ScheduleEvent(EVENT_EROZION_ACTION_1, 26s);
                        _events.ScheduleEvent(EVENT_EROZION_TALK_2, 29s);
                        _events.ScheduleEvent(EVENT_EROZION_TALK_3, 42s);
                        _events.ScheduleEvent(EVENT_EROZION_ACTION_2, 47s);
                        _events.ScheduleEvent(EVENT_THRALL_TALK_6, 48s);
                        _events.ScheduleEvent(EVENT_THRALL_RUN_AWAY, 51s);
                        _events.ScheduleEvent(EVENT_TARETHA_TALK_2, 53s);
                        break;
                    default:
                        break;
                }
            }

            void WaypointStart(uint32 waypointId) override
            {
                if (waypointId == 30)
                    Talk(SAY_START_EVENT_PART2);
            }

            void WaypointReached(uint32 waypointId) override
            {
                if (!_instance)
                    return;

                switch (waypointId)
                {
                    case 0:
                        Talk(SAY_START_EVENT_PART1);
                        break;
                    case 8:
                        _events.ScheduleEvent(EVENT_SET_FACING, 0.5s);
                        break;
                    case 9:
                        SetRun(false);
                        _events.ScheduleEvent(EVENT_KILL_ARMORER, 0.5s);
                        _events.ScheduleEvent(EVENT_TALK_KILL_ARMORER, 4s);
                        break;
                    case 10:
                        SetRun(true);
                        _events.ScheduleEvent(EVENT_DRESSING_KNEEL, 0.5s);
                        _events.ScheduleEvent(EVENT_DRESSING_ARMOR, 3s);
                        _events.ScheduleEvent(EVENT_DRESSING_STAND, 4s);
                        _events.ScheduleEvent(EVENT_DRESSING_AXE, 7s);
                        _events.ScheduleEvent(EVENT_DRESSING_SHIELD, 9s);
                        _events.ScheduleEvent(EVENT_DRESSING_TALK, 12s);
                        break;
                    case 13:
                        me->SummonCreature(NPC_DURNHOLDE_SENTRY, 2200.28f, 137.37f, 87.93f, 5.07f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_DURNHOLDE_SENTRY, 2197.44f, 131.83f, 87.93f, 0.78f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_DURNHOLDE_MAGE, 2203.62f, 135.40f, 87.93f, 3.70f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_DURNHOLDE_VETERAN, 2200.75f, 130.13f, 87.93f, 1.48f, TEMPSUMMON_MANUAL_DESPAWN);
                        break;
                    case 16:
                        me->SummonCreature(NPC_DURNHOLDE_SENTRY, 2147.43f, 122.194f, 76.422f, 0.67f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_DURNHOLDE_SENTRY, 2146.27f, 126.13f, 76.241f, 0.60f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_DURNHOLDE_MAGE, 2142.62f, 120.38f, 75.862f, 0.48f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_DURNHOLDE_VETERAN, 2141.74f, 123.95f, 75.732f, 0.24f, TEMPSUMMON_MANUAL_DESPAWN);
                        break;
                    case 18:
                        me->SummonCreature(NPC_DURNHOLDE_SENTRY, 2138.37f, 167.98f, 66.23f, 2.59f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_DURNHOLDE_WARDEN, 2142.76f, 173.62f, 66.23f, 2.59f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_DURNHOLDE_MAGE, 2140.96f, 168.64f, 66.23f, 2.59f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_DURNHOLDE_VETERAN, 2142.53f, 171.03f, 66.23f, 2.59f, TEMPSUMMON_MANUAL_DESPAWN);
                        break;
                    case 22:
                        me->SummonCreature(NPC_DURNHOLDE_SENTRY, 2108.73f, 190.43f, 66.23f, 5.56f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_DURNHOLDE_MAGE, 2109.74f, 195.29f, 66.23f, 5.56f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_DURNHOLDE_MAGE, 2107.74f, 192.59f, 66.23f, 5.56f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_DURNHOLDE_SENTRY, 2112.26f, 195.13f, 66.23f, 5.56f, TEMPSUMMON_MANUAL_DESPAWN);
                        break;
                    case 27:
                        _instance->SetData(DATA_ESCORT_PROGRESS, ENCOUNTER_PROGRESS_AMBUSHES_1);
                        break;
                    case 28:
                        me->SummonCreature(NPC_CAPTAIN_SKARLOC, 1995.78f, 277.46f, 66.64f, 0.74f, TEMPSUMMON_MANUAL_DESPAWN);
                        break;
                    case 29:
                        SetEscortPaused(true);
                        Talk(SAY_SKARLOC_MEET);
                        break;
                    case 30:
                        _events.ScheduleEvent(EVENT_ENTER_MOUNT, 3s);
                        _events.ScheduleEvent(EVENT_TALK_START_RIDE, 7s);
                        break;
                    case 59:
                        _instance->SetData(DATA_ESCORT_PROGRESS, ENCOUNTER_PROGRESS_TARREN_MILL);
                        me->SummonCreature(NPC_SKARLOC_MOUNT, 2488.64f, 625.77f, 58.26f, 4.71f, TEMPSUMMON_TIMED_DESPAWN, 7000);
                        UnMountSelf();
                        _mounted = false;
                        SetRun(false);
                        break;
                    case 60:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                        if (auto horse = me->FindNearestCreature(NPC_SKARLOC_MOUNT, 10.0f))
                            horse->GetMotionMaster()->MovePoint(0, 2501.15f, 572.14f, 54.13f);

                        SetEscortPaused(true);
                        SetRun(true);
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        break;
                    case 64:
                        SetRun(false);
                        break;
                    case 67:
                        _events.ScheduleEvent(EVENT_LOOK_1, 0.5s);
                        _events.ScheduleEvent(EVENT_MOVE_AROUND, 3.5s);
                        _events.ScheduleEvent(EVENT_LOOK_2, 5s);
                        _events.ScheduleEvent(EVENT_LOOK_3, 6.7s);
                        _events.ScheduleEvent(EVENT_SUMMON_GUARDS, 6s);
                        _events.ScheduleEvent(EVENT_SUMMON_TALK1, 6.5s);
                        _events.ScheduleEvent(EVENT_SUMMON_TALK2, 12s);
                        break;
                    case 82:
                        _events.ScheduleEvent(EVENT_LOOK_4, 0.5s);
                        _events.ScheduleEvent(EVENT_SUMMON_GUARDS_2, 1s);
                        _events.ScheduleEvent(EVENT_SUMMON_TALK3, 1.5s);
                        break;
                    case 91:
                        me->SummonCreature(NPC_TM_PROTECTOR, 2652.71f, 660.31f, 61.93f, 1.67f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_TM_LOOKOUT, 2648.96f, 662.59f, 61.93f, 0.79f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_TM_GUARDSMAN, 2657.36f, 662.34f, 61.93f, 2.68f, TEMPSUMMON_MANUAL_DESPAWN);
                        me->SummonCreature(NPC_TM_GUARDSMAN, 2656.39f, 659.77f, 61.93f, 2.61f, TEMPSUMMON_MANUAL_DESPAWN);
                        if (auto summon = _summons.GetCreatureWithEntry(NPC_TM_LOOKOUT))
                            if (summon->IsAIEnabled)
                                summon->AI()->Talk(SAY_LOOKOUT_INN);
                        break;
                    case 92:
                        SetRun(false);
                        break;
                    case 94:
                        _summons.DespawnAll();
                        SetEscortPaused(true);
                        SetRun(true);
                        _instance->SetData(DATA_ESCORT_PROGRESS, ENCOUNTER_PROGRESS_TARETHA_MEET);
                        if (auto taretha = _instance->GetCreature(DATA_TARETHA))
                            if (taretha->IsAIEnabled)
                                taretha->AI()->Talk(SAY_TARETHA_ESCAPED);
                        _events.ScheduleEvent(EVENT_THRALL_TALK, 2s);
                        break;
                    case 101:
                        SetEscortPaused(true);
                        _events.ScheduleEvent(EVENT_EPOCH_INTRO, 0.5s);
                        _events.ScheduleEvent(EVENT_SUMMON_INFINITES, 1.5s);
                        _events.ScheduleEvent(EVENT_TRANSFORM, 8s);
                        _events.ScheduleEvent(EVENT_START_WAVE_1, 25s);
                        break;
                    case 103:
                        if (auto erozion = _summons.GetCreatureWithEntry(NPC_EROZION))
                            erozion->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        _instance->SetData(DATA_ESCORT_PROGRESS, ENCOUNTER_PROGRESS_FINISHED);
                        me->SetVisible(false);
                        break;
                }
            }

            void MountSelf() const
            {
                me->Mount(SKARLOC_MOUNT_MODEL);
                me->SetSpeedRate(MOVE_RUN, SPEED_MOUNTED);
            }

            void UnMountSelf() const
            {
                me->Dismount();
                me->SetSpeedRate(MOVE_RUN, SPEED_RUNNING);
            }

            void MovementInform(uint32 type, uint32 point) override
            {
                npc_escortAI::MovementInform(type, point);
                if (type == POINT_MOTION_TYPE && point == 0xFFFFFF /*POINT_LAST_POINT*/)
                {
                    if (roll_chance_i(30))
                        Talk(SAY_LEAVE_COMBAT);
                    if (_mounted)
                        MountSelf();
                }
            }

            void EnterCombat(Unit* /*attacker*/) override
            {
                _combatEvents.Reset();
                _combatEvents.ScheduleEvent(EVENT_CHECK_HEALTH, 0.5s);
                _combatEvents.ScheduleEvent(EVENT_SHIELD_BLOCK, 8s);
                _combatEvents.ScheduleEvent(EVENT_STRIKE, 2s);

                if (urand(0, 1))
                    Talk(SAY_RANDOM_AGGRO);

                if (me->IsMounted())
                {
                    _mounted = true;
                    UnMountSelf();
                }
            }

            void Reset() override
            {
                _mounted = false;
                _events.Reset();
                _combatEvents.Reset();
                _summons.DespawnAll();

                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                _instance->SetData(DATA_THRALL_REPOSITION, 1);

                auto data = _instance->GetData(DATA_ESCORT_PROGRESS);
                if (data >= ENCOUNTER_PROGRESS_THRALL_ARMORED)
                    ReorderInstance(data);
            }

            void KilledUnit(Unit* /*victim*/) override
            {
                Talk(SAY_RANDOM_KILL);
            }

            void JustSummoned(Creature* summon) override
            {
                if (summon->GetEntry() == NPC_INFINITE_SLAYER || summon->GetEntry() == NPC_INFINITE_SABOTEUR || summon->GetEntry() == NPC_INFINITE_DEFILER)
                    summon->GetMotionMaster()->MovePoint(10, 2634.25f, 672.01f, 54.445f);

                _summons.Summon(summon);
            }
            void SummonedCreatureDespawn(Creature* summon) override { _summons.Despawn(summon); }
            void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override { _summons.Despawn(summon); }

            void JustDied(Unit* killer) override
            {
                if (killer == me)
                    return;

                _summons.DespawnAll();
                Talk(SAY_RANDOM_DIE);
                RemoveEscortState(STATE_ESCORT_ESCORTING);
                _instance->SetData(DATA_THRALL_REPOSITION, 3);
                if (_instance->GetData(DATA_ATTEMPTS_COUNT) < 20)
                    DoCastSelf(SPELL_SUMMON_EROZION_IMAGE, true);
                else
                    me->SetRespawnTime(DAY);
            }

            void UpdateAI(uint32 diff) override
            {
                npc_escortAI::UpdateAI(diff);

                _events.Update(diff);

                while (auto eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_OPEN_DOORS:
                            if (auto door = me->FindNearestGameObject(GO_PRISON_DOOR, 10.0f))
                                door->SetGoState(GO_STATE_ACTIVE);
                            break;
                        case EVENT_START_WP:
                            Start(true, true);
                            SetDespawnAtEnd(false);
                            break;
                        case EVENT_SET_FACING:
                            if (auto armorer = me->FindNearestCreature(NPC_DURNHOLDE_ARMORER, 30.0f))
                            {
                                if (armorer->IsAIEnabled)
                                    armorer->AI()->Talk(SAY_ARMORER_THRALL);
                                armorer->SetFacingToObject(me);
                                me->SetFacingToObject(armorer);
                            }
                            break;
                        case EVENT_KILL_ARMORER:
                            me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK_UNARMED);
                            if (auto armorer = me->FindNearestCreature(NPC_DURNHOLDE_ARMORER, 30.0f))
                                armorer->SetStandState(UNIT_STAND_STATE_DEAD);
                            break;
                        case EVENT_TALK_KILL_ARMORER:
                            Talk(SAY_KILL_ARMORER);
                            break;
                        case EVENT_DRESSING_KNEEL:
                            me->SetFacingTo(2.61f);
                            Talk(SAY_ARMORY);
                            me->SetStandState(UNIT_STAND_STATE_KNEEL);
                            break;
                        case EVENT_DRESSING_ARMOR:
                            me->SetDisplayId(THRALL_MODEL_EQUIPPED);
                            break;
                        case EVENT_DRESSING_STAND:
                            me->SetStandState(UNIT_STAND_STATE_STAND);
                            break;
                        case EVENT_DRESSING_AXE:
                            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, THRALL_WEAPON_ITEM);
                            break;
                        case EVENT_DRESSING_SHIELD:
                            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1, THRALL_SHIELD_ITEM);
                            break;
                        case EVENT_DRESSING_TALK:
                            _instance->SetData(DATA_ESCORT_PROGRESS, ENCOUNTER_PROGRESS_THRALL_ARMORED);
                            Talk(SAY_GO_ARMORED);
                            break;
                        case EVENT_ENTER_MOUNT:
                            MountSelf();
                            if (auto mount = me->FindNearestCreature(NPC_SKARLOC_MOUNT, 10.0f))
                            {
                                me->SetFacingTo(mount->GetOrientation());
                                mount->DespawnOrUnsummon();
                            }
                            break;
                        case EVENT_TALK_START_RIDE:
                            Talk(SAY_MOUNTS_UP);
                            break;
                        case EVENT_LOOK_1:
                            me->SetFacingTo(5.058f);
                            break;
                        case EVENT_MOVE_AROUND:
                            me->GetMotionMaster()->MovePoint(0, 2477.146f, 695.041f, 55.801f);
                            break;
                        case EVENT_LOOK_2:
                            me->SetFacingTo(2.297f);
                            break;
                        case EVENT_LOOK_3:
                            me->SetFacingTo(0.64f);
                            break;
                        case EVENT_SUMMON_GUARDS:
                            SetRun(true);
                            me->SummonCreature(NPC_TM_PROTECTOR, 2501.34f, 700.80f, 55.573f, 3.92f, TEMPSUMMON_MANUAL_DESPAWN);
                            me->SummonCreature(NPC_TM_LOOKOUT, 2503.02f, 699.11f, 55.57f, 3.92f, TEMPSUMMON_MANUAL_DESPAWN);
                            me->SummonCreature(NPC_TM_GUARDSMAN, 2503.04f, 702.495f, 50.63f, 3.92f, TEMPSUMMON_MANUAL_DESPAWN);
                            me->SummonCreature(NPC_TM_GUARDSMAN, 2504.72f, 700.806f, 55.62f, 3.92f, TEMPSUMMON_MANUAL_DESPAWN);
                            _summons.DoAction(ACTION_SET_IMMUNE_FLAG);
                            break;
                        case EVENT_SUMMON_TALK1:
                            if (auto summon = _summons.GetCreatureWithEntry(NPC_TM_LOOKOUT))
                                if (summon->IsAIEnabled)
                                    summon->AI()->Talk(SAY_LOOKOUT_SAW);
                            break;
                        case EVENT_SUMMON_TALK2:
                            if (auto summon = _summons.GetCreatureWithEntry(NPC_TM_LOOKOUT))
                                if (summon->IsAIEnabled)
                                    summon->AI()->Talk(SAY_LOOKOUT_GO);
                            _summons.DoAction(ACTION_REMOVE_IMMUNE_FLAG);
                            break;
                        case EVENT_LOOK_4:
                            me->SetFacingTo(0.41f);
                            Talk(SAY_ENTER_CHURCH);
                            break;
                        case EVENT_SUMMON_GUARDS_2:
                            me->SummonCreature(NPC_TM_PROTECTOR, 2630.75f, 664.80f, 54.28f, 4.37f, TEMPSUMMON_MANUAL_DESPAWN);
                            me->SummonCreature(NPC_TM_LOOKOUT, 2632.20f, 661.98f, 54.30f, 4.37f, TEMPSUMMON_MANUAL_DESPAWN);
                            me->SummonCreature(NPC_TM_GUARDSMAN, 2630.02f, 662.75f, 54.28f, 4.37f, TEMPSUMMON_MANUAL_DESPAWN);
                            me->SummonCreature(NPC_TM_GUARDSMAN, 2632.86f, 664.05f, 54.31f, 4.37f, TEMPSUMMON_MANUAL_DESPAWN);
                            break;
                        case EVENT_SUMMON_TALK3:
                            if (auto summon = _summons.GetCreatureWithEntry(NPC_TM_LOOKOUT))
                                if (summon->IsAIEnabled)
                                    summon->AI()->Talk(SAY_LOOKOUT_CHURCH);
                            break;
                        case EVENT_THRALL_TALK:
                            Talk(SAY_MEET_TARETHA);
                            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            break;
                        case EVENT_SUMMON_CHRONO:
                            if (auto epoch = me->SummonCreature(NPC_EPOCH_HUNTER, 2640.49f, 696.15f, 64.31f, 4.51f, TEMPSUMMON_MANUAL_DESPAWN))
                            {
                                epoch->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                                if (epoch->IsAIEnabled)
                                    epoch->AI()->Talk(SAY_EPOCH_ENTER1);
                            }
                            break;
                        case EVENT_THRALL_TALK_2:
                            me->SetFacingTo(2.67f);
                            Talk(SAY_EPOCH_WONDER);
                            break;
                        case EVENT_TARETHA_FALL:
                            if (auto epoch = _summons.GetCreatureWithEntry(NPC_EPOCH_HUNTER))
                                if (epoch->IsAIEnabled)
                                    epoch->AI()->Talk(SAY_EPOCH_ENTER2);
                            if (auto taretha = _instance->GetCreature(DATA_TARETHA))
                            {
                                taretha->CastSpell(taretha, SPELL_SHADOW_SPIKE);
                                taretha->SetStandState(UNIT_STAND_STATE_DEAD);
                            }
                            break;
                        case EVENT_THRALL_TALK_3:
                            me->SetFacingTo(5.78f);
                            Talk(SAY_EPOCH_KILL_TARETHA);
                            break;
                        case EVENT_THRALL_MOVE_DOWN:
                            SetEscortPaused(false);
                            break;
                        case EVENT_EPOCH_INTRO:
                            me->SetFacingTo(1.33f);
                            if (auto epoch = _summons.GetCreatureWithEntry(NPC_EPOCH_HUNTER))
                                if (epoch->IsAIEnabled)
                                    epoch->AI()->Talk(SAY_EPOCH_ENTER3);
                            break;
                        case EVENT_SUMMON_INFINITES:
                            me->SummonCreature(NPC_EPOCH_LOOKOUT, 2647.57f, 701.17f, 56.215f, 4.3f, TEMPSUMMON_MANUAL_DESPAWN);
                            me->SummonCreature(NPC_EPOCH_GUARDSMAN, 2629.46f, 704.76f, 56.286f, 4.98f, TEMPSUMMON_MANUAL_DESPAWN);
                            me->SummonCreature(NPC_EPOCH_PROTECTOR, 2640.14f, 709.44f, 56.135f, 4.70f, TEMPSUMMON_MANUAL_DESPAWN);
                            _summons.DoAction(ACTION_SET_IMMUNE_FLAG);
                            _summons.DoAction(ACTION_MOVE);
                            break;
                        case EVENT_TRANSFORM:
                            _summons.DoAction(ACTION_TRANSFORM);
                            _summons.DoAction(ACTION_SET_IMMUNE_FLAG);
                            break;
                        case EVENT_START_WAVE_1:
                            _events.ScheduleEvent(EVENT_CHECK_WAVE_1, 0.5s);
                            _summons.DoAction(ACTION_REMOVE_IMMUNE_FLAG);
                            _summons.DoAction(ACTION_START_COMBAT);
                            break;
                        case EVENT_CHECK_WAVE_1:
                            if (_summons.size() == 1)
                            {
                                me->SummonCreature(NPC_INFINITE_SABOTEUR, 2599.57f, 683.72f, 55.975f, 0.05f, TEMPSUMMON_MANUAL_DESPAWN);
                                me->SummonCreature(NPC_INFINITE_SLAYER, 2599.57f, 677.0f, 55.975f, 0.05f, TEMPSUMMON_MANUAL_DESPAWN);
                                me->SummonCreature(NPC_INFINITE_DEFILER, 2592.57f, 680.0f, 55.975f, 0.05f, TEMPSUMMON_MANUAL_DESPAWN);
                                _summons.DoAction(ACTION_START_COMBAT);
                                _events.ScheduleEvent(EVENT_CHECK_WAVE_2, 0.5s);
                                break;
                            }
                            _events.Repeat(0.5s);
                            break;
                        case EVENT_CHECK_WAVE_2:
                            if (_summons.size() == 1)
                            {
                                me->SummonCreature(NPC_INFINITE_SLAYER, 2642.62f, 701.43f, 55.965f, 4.46f, TEMPSUMMON_MANUAL_DESPAWN);
                                me->SummonCreature(NPC_INFINITE_SLAYER, 2638.62f, 701.43f, 55.965f, 4.46f, TEMPSUMMON_MANUAL_DESPAWN);
                                me->SummonCreature(NPC_INFINITE_SABOTEUR, 2638.62f, 705.43f, 55.965f, 4.46f, TEMPSUMMON_MANUAL_DESPAWN);
                                me->SummonCreature(NPC_INFINITE_DEFILER, 2642.62f, 705.43f, 55.965f, 4.46f, TEMPSUMMON_MANUAL_DESPAWN);
                                _summons.DoAction(ACTION_START_COMBAT);
                                _events.ScheduleEvent(EVENT_CHECK_WAVE_3, 0.5s);
                                break;
                            }
                            _events.Repeat(0.5s);
                            break;
                        case EVENT_CHECK_WAVE_3:
                            if (_summons.size() == 1)
                            {
                                me->SetHomePosition(2634.79f, 672.964f, 54.8577f, 1.33f);
                                me->GetMotionMaster()->MoveTargetedHome();
                                _events.ScheduleEvent(EVENT_CALL_EPOCH, 8s);
                                break;
                            }
                            _events.Repeat(0.5s);
                            break;
                        case EVENT_CALL_EPOCH:
                            if (auto epoch = _summons.GetCreatureWithEntry(NPC_EPOCH_HUNTER))
                            {
                                epoch->SetImmuneToAll(false);
                                epoch->GetMotionMaster()->MovePoint(0, *me, false, true);
                            }
                            break;
                        case EVENT_THRALL_FACE_TARETHA:
                        {
                            auto const& players = me->GetMap()->GetPlayers();
                            for (auto const& ref : players)
                                if (auto player = ref.GetSource())
                                    player->KilledMonsterCredit(20156, 0);

                            me->SetFacingTo(5.76f);
                            break;
                        }
                        case EVENT_THRALL_TALK_4:
                            Talk(SAY_GREET_TARETHA);
                            break;
                        case EVENT_TARETHA_TALK_1:
                            if (auto taretha = _instance->GetCreature(DATA_TARETHA))
                                if (taretha->IsAIEnabled)
                                    taretha->AI()->Talk(SAY_TARETHA_TALK1);
                            break;
                        case EVENT_THRALL_TALK_5:
                            Talk(SAY_CHAT_TARETHA1);
                            break;
                        case EVENT_SUMMON_EROZION:
                            if (auto erozion = me->SummonCreature(NPC_EROZION, 2646.31f, 680.01f, 55.36f, 3.76f, TEMPSUMMON_MANUAL_DESPAWN))
                                erozion->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
                            break;
                        case EVENT_EROZION_TALK_1:
                            if (auto erozion = _summons.GetCreatureWithEntry(NPC_EROZION))
                            {
                                erozion->CastSpell(erozion, SPELL_TELEPORT, true);
                                if (erozion->IsAIEnabled)
                                    erozion->AI()->Talk(SAY_EROZION_1);
                            }
                            break;
                        case EVENT_EROZION_ACTION_1:
                            if (auto erozion = _summons.GetCreatureWithEntry(NPC_EROZION))
                                erozion->CastSpell(erozion, SPELL_MEMORY_WIPE, false);
                            break;
                        case EVENT_EROZION_TALK_2:
                            if (auto erozion = _summons.GetCreatureWithEntry(NPC_EROZION))
                                if (erozion->IsAIEnabled)
                                    erozion->AI()->Talk(SAY_EROZION_2);
                            break;
                        case EVENT_EROZION_TALK_3:
                            if (auto erozion = _summons.GetCreatureWithEntry(NPC_EROZION))
                                if (erozion->IsAIEnabled)
                                    erozion->AI()->Talk(SAY_EROZION_3);
                            break;
                        case EVENT_EROZION_ACTION_2:
                            if (auto erozion = _summons.GetCreatureWithEntry(NPC_EROZION))
                                erozion->CastSpell(erozion, SPELL_MEMORY_WIPE_RESUME, false);
                            break;
                        case EVENT_THRALL_TALK_6:
                            Talk(SAY_EVENT_COMPLETE);
                            break;
                        case EVENT_THRALL_RUN_AWAY:
                            me->SetImmuneToAll(true);
                            me->SetReactState(REACT_PASSIVE);
                            SetEscortPaused(false);
                            break;
                        case EVENT_TARETHA_TALK_2:
                            if (auto taretha = _instance->GetCreature(DATA_TARETHA))
                            {
                                taretha->SetFacingTo(4.233f);
                                if (taretha->IsAIEnabled)
                                    taretha->AI()->Talk(SAY_TARETHA_TALK2);
                            }
                            break;
                        default:
                            break;
                    }
                }
            }

            void UpdateEscortAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                _combatEvents.Update(diff);

                while (auto eventId = _combatEvents.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHECK_HEALTH:
                            if (me->HealthBelowPct(20))
                            {
                                Talk(SAY_RANDOM_LOW_HP);
                                break;
                            }
                            _combatEvents.Repeat(0.5s);
                            break;
                        case EVENT_STRIKE:
                            DoCastVictim(SPELL_STRIKE);
                            _combatEvents.Repeat(6s);
                            break;
                        case EVENT_SHIELD_BLOCK:
                            DoCastSelf(SPELL_SHIELD_BLOCK);
                            _combatEvents.Repeat(6s);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void ReorderInstance(uint32 data)
            {
                Start(true, true);
                SetEscortPaused(true);
                SetDespawnAtEnd(false);

                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);

                if (data < ENCOUNTER_PROGRESS_THRALL_ARMORED)
                {
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 0);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1, 0);
                    me->SetDisplayId(THRALL_MODEL_UNEQUIPPED);
                }
                else
                {
                    me->SetDisplayId(THRALL_MODEL_EQUIPPED);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, THRALL_WEAPON_ITEM);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1, THRALL_SHIELD_ITEM);
                }

                switch (data)
                {
                    case ENCOUNTER_PROGRESS_THRALL_ARMORED:
                        SetNextWaypoint(11, false);
                        break;
                    case ENCOUNTER_PROGRESS_AMBUSHES_1:
                        SetNextWaypoint(27, false);
                        break;
                    case ENCOUNTER_PROGRESS_SKARLOC_KILLED:
                        me->SummonCreature(NPC_SKARLOC_MOUNT, 2049.12f, 252.31f, 62.855f, me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                        SetNextWaypoint(30, false);
                        break;
                    case ENCOUNTER_PROGRESS_TARREN_MILL:
                        SetNextWaypoint(61, false);
                        break;
                    case ENCOUNTER_PROGRESS_TARETHA_MEET:
                        SetNextWaypoint(95, false);
                        if (auto taretha = _instance->GetCreature(DATA_TARETHA))
                            taretha->SetStandState(UNIT_STAND_STATE_STAND);
                        break;
                }
            }

        private:
            InstanceScript* _instance;
            EventMap _events;
            EventMap _combatEvents;
            SummonList _summons;
            bool _mounted;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetInstanceAI<npc_thrall_old_hillsbradAI>(creature);
        }
};

struct npc_tarethaAI : public npc_escortAI
{
    npc_tarethaAI(Creature* creature) : npc_escortAI(creature) { }

    void DoAction(int32 /*actionId*/) override
    {
        me->SetStandState(UNIT_STAND_STATE_STAND);
        me->RemoveAllAuras();
        Start(false, true);
    }

    void WaypointReached(uint32 waypointId)
    {
        switch (waypointId)
        {
            case 7:
                SetRun(false);
                Talk(SAY_TARETHA_FREE);
                me->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                if (auto instance = me->GetInstanceScript())
                    if (auto thrall = instance->GetCreature(DATA_THRALL))
                        if (thrall->IsAIEnabled)
                            thrall->AI()->DoAction(me->GetEntry());
                break;
            case 9:
                me->SetVisible(false);
            default:
                break;
        }
    }

    void Reset() override
    {
        me->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
        DoCastSelf(SPELL_SHADOW_PRISON, true);
    }

    void AttackStart(Unit* /*victim*/) override { }
    void MoveInLineOfSight(Unit* /*victim*/) override { }
};

void AddSC_old_hillsbrad()
{
    new npc_thrall_old_hillsbrad();
    new CreatureAILoader<npc_tarethaAI>("npc_taretha");
}
