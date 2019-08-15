#include "hellforge.hpp"
#include "Group.h"
#include "MoveSplineInit.h"

enum HellforgeWandererData
{
    QUEST_WANDERER_Q1               = 31000,
    QUEST_WANDERER_Q3               = 31002,
    QUEST_WANDERER_Q4               = 31003,
    QUEST_WANDERER_Q5               = 31004,
    QUEST_WANDERER_Q6               = 31005,

    NPC_Q6_HEAL_CREDIT              = 260003,
    NPC_SOUL_STONE                  = 260004,
    NPC_WORLD_TRIGGER               = 18721,
    NPC_BURNING_WORM                = 260005,
    NPC_HELLFORGE_TYRAEL            = 260006,

    POINT_FIRST_BOSS_DOOR           = 1,
    POINT_SIMON_ROOM                = 2,
    POINT_SIMON_ESCAPE              = 3,
    POINT_DWARF_DOOR                = 4,
    POINT_DWARF_ROOM                = 5,
    POINT_DWARF_ROOM_2              = 6,
    POINT_VAMPIRE_LAVA              = 7,
    POINT_VAMPIRE_CORPSE            = 8,
    POINT_SOULSTONE                 = 9,
    POINT_GAUNTLET                  = 10,
    POINT_VAMPIRE_ROOM              = 11,
    POINT_COCCON                    = 12,
    POINT_VAMPIRE_ROOM_2            = 13,
    POINT_TYRAEL_DOWN               = 14,

    // waypoint points
    POINT_FIRST_BOSS_CORPSE         = 0,
    POINT_CHAMPION_COCCON           = 11,
    POINT_SIMON_DOOR                = 9,
    POINT_SIMON                     = 6,
    POINT_GAUNTLET_2                = 1,

    GO_SIMON_DOOR                   = 170558,

    PATH_SIMON_DOOR                 = 2600001,
    PATH_SIMON_ROOM                 = 2600002,

    SPELL_BOSS_FOUR_THROW_SPEAR     = 45730,
    SPELL_BOSS_FIVE_STRANGULATING   = 69413,
    SPELL_WANDERER_PORTAL           = 68424,
    SPELL_CHAMPION_FLARE            = 66400,
    SPELL_BURNING_WORM_AURA         = 43184,
    SPELL_SLOW_FALL                 = 50237,
    SPELL_TYRAEL_VISUAL             = 70088,
    SPELL_TELEPORT_VISUAL           = 19484,

    ITEM_WANDERER_WEAPON            = 1728,

    CHAMPION_STATS_MAX_HEALTH       = 800,
    GOSSIP_WANDERER                 = 1110010,
    GOSSIP_CHAMPION                 = GOSSIP_WANDERER + 1,
    GOSSIP_TYRAEL                   = GOSSIP_WANDERER + 2,
};

const Position WandererStatePosition[STATE_WANDERER_MAX] =
{
    {1380.27f, -823.86f, -92.72f, 1.65f }, // STATE_RAID_ENTRANCE
    {1379.97f, -722.72f, -92.72f, 1.65f }, // STATE_FIRST_BOSS_DOOR
    {1380.24f, -502.10f, -92.05f, 1.65f }, // STATE_FIRST_BOSS_KILLED
    {1381.02f, -391.38f, -93.21f, 1.58f }, // STATE_CHAMPION_FREED
    {972.47f, -201.33f, -61.78f,  5.47f }  // STATE_ESCAPED
};

const Position ChampionStatePosition[STATE_CHAMPION_MAX] =
{
    { 1381.06f, -386.57f, -92.05f, 4.68f  },  // STATE_TRAPPED
    { 1381.06f, -386.57f, -92.05f, 4.68f  },  // STATE_FREED
    { 1231.81f, -207.f,   -85.5f,  2.37f  },  // STATE_SAIMON_KILLED
    { 1088.11f, -162.62f, -65.31f, 3.93f  },  // STATE_DWARF_KILLED
    { 1029.52f, -223.74f, -61.99f, -2.33f },  // STATE_GAUNTLET_DONE
    { 1029.52f, -223.74f, -61.99f, -2.33f }   // STATE_CHAMPION_DEAD
};

constexpr uint32 FIRST_BOSS_BURNING_WORMS_COUNT{ 2 };
Position const FirstBossBurningWormsPosition[FIRST_BOSS_BURNING_WORMS_COUNT] =
{
    { 1382.74f, -694.44f, -92.05f },
    { 1377.76f, -694.90f, -92.05f }
};

Position const FirstBossBurningWormsPoint[FIRST_BOSS_BURNING_WORMS_COUNT] =
{
    { 1382.98f, -747.60f, -92.72f },
    { 1377.78f, -747.77f, -92.72f }
};

Position const _tyraelPosition = { 1018.06f, -238.21f, -50.25f, 2.7f };

class npc_hellforge_wanderer : CreatureScript
{
public:
    npc_hellforge_wanderer() : CreatureScript("npc_hellforge_wanderer") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());
        if (creature->IsAIEnabled)
        {
            HellforgeWandererState state = static_cast<HellforgeWandererState>(creature->GetAI()->GetData(0));
            switch (state)
            {
                case STATE_RAID_ENTRANCE:
                {
                    if(player->IsGameMaster())
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "*DEBUG* Open door", GOSSIP_SENDER_MAIN, ACTION_KILLED_TRASH);
                    break;
                }
                case STATE_CHAMPION_FREED:
                {
                    // If player has group he must be leader or gamemaster
                    if (player->GetGroup() && !player->GetGroup()->IsLeader(player->GetGUID()) && !player->IsGameMaster())
                        break;
                    // Player must has rewarded Q4 quest
                    if (player->GetQuestStatus(QUEST_WANDERER_Q4) != QUEST_STATUS_REWARDED)
                        break;
                    // Champion must has STATE_FREED
                    if (InstanceScript * instance = creature->GetInstanceScript())
                    {
                        if (Unit * champion = instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
                            if (!champion->IsAIEnabled || champion->GetAI()->GetData(0) != STATE_FREED)
                                break;
                    }
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Fair enough friends, shall we go ahead?", GOSSIP_SENDER_MAIN, ACTION_GO_TO_SIMON);
                    break;
                }
            }
        }

        if (player->IsGameMaster())
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "*DEBUG* Change state", GOSSIP_SENDER_MAIN, 1000);
        player->SEND_GOSSIP_MENU(GOSSIP_WANDERER, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)  override
    {
        switch (action)
        {
            case ACTION_KILLED_TRASH:
            {
                if (creature->IsAIEnabled)
                    creature->GetAI()->DoAction(ACTION_KILLED_TRASH);
                player->CLOSE_GOSSIP_MENU();
                break;
            }
            case ACTION_GO_TO_SIMON:
            {
                if (creature->IsAIEnabled)
                    if (creature->GetAI()->GetData(0) == STATE_CHAMPION_FREED)
                        creature->GetAI()->DoAction(ACTION_GO_TO_SIMON);
                break;
            }
            case 1000:
                player->PlayerTalkClass->ClearMenus();
                for (uint32 i = STATE_RAID_ENTRANCE; i < STATE_WANDERER_MAX; ++i)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GetStateName(static_cast<HellforgeWandererState>(i)).c_str(), GOSSIP_SENDER_MAIN, 2000 + i);
                }
                player->SEND_GOSSIP_MENU(GOSSIP_WANDERER, creature->GetGUID());
                break;
        }

        if (player->IsGameMaster() && action >= 2000)
        {
            uint32 state = action - 2000;
            CAST_AI(npc_hellforge_wandererAI, creature->GetAI())->ChangeState((HellforgeWandererState)state, true);
            player->CLOSE_GOSSIP_MENU();
        }

        return true;
    }

    std::string const GetStateName(HellforgeWandererState state) const
    {
        switch (state)
        {
            case STATE_RAID_ENTRANCE:
                return "STATE_RAID_ENTRANCE";
            case STATE_FIRST_BOSS_DOOR:
                return "STATE_FIRST_BOSS_DOOR";
            case STATE_FIRST_BOSS_KILLED:
                return "STATE_FIRST_BOSS_KILLED";
            case STATE_CHAMPION_FREED:
                return "STATE_CHAMPION_FREED";
            case STATE_ESCAPED:
                return "STATE_ESCAPED";
            default:
                return "UNKNOWN";
        }
    }

    struct npc_hellforge_wandererAI : public ScriptedAI
    {
        npc_hellforge_wandererAI(Creature* creature) : ScriptedAI(creature), _state(STATE_RAID_ENTRANCE), _simonDoorOpened(false)
        {
            _instance = me->GetInstanceScript();
            HandleWandererState();
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
                case ACTION_KILLED_TRASH:
                {
                    if (_state != STATE_RAID_ENTRANCE)
                        break;
                    me->MonsterSay("Well done, let's proceed!", LANG_UNIVERSAL, nullptr);
                    me->RemoveFlag(UNIT_NPC_FLAGS, (UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER));
                    me->GetMotionMaster()->MovePoint(POINT_FIRST_BOSS_DOOR, WandererStatePosition[STATE_FIRST_BOSS_DOOR]);
                    ChangeState(STATE_FIRST_BOSS_DOOR);
                    if (_instance && !_instance->instance->GetPlayers().isEmpty())
                    {
                        for (auto itr = _instance->instance->GetPlayers().begin(); itr != _instance->instance->GetPlayers().end(); ++itr)
                            itr->GetSource()->AreaExploredOrEventHappens(QUEST_WANDERER_Q1);
                    }
                    break;
                }
                case ACTION_KILLED_BOSS_ONE:
                {
                    if (_state != STATE_FIRST_BOSS_DOOR)
                        break;
                    me->RemoveFlag(UNIT_NPC_FLAGS, (UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER));
                    me->GetMotionMaster()->MovePath(me->GetEntry() * 10, false);
                    ChangeState(STATE_FIRST_BOSS_KILLED);
                    break;
                }
                case ACTION_SNAKE_KILLED:
                    me->GetMotionMaster()->MovePoint(POINT_COCCON, WandererStatePosition[STATE_CHAMPION_FREED]);
                    me->RemoveFlag(UNIT_NPC_FLAGS, (UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER));
                    break;
                case ACTION_CHAMPION_FREED:
                {
                    ChangeState(STATE_CHAMPION_FREED);
                    break;
                }
                case ACTION_GO_TO_SIMON:
                {
                    if (_state != STATE_CHAMPION_FREED)
                        break;
                    me->RemoveFlag(UNIT_NPC_FLAGS, (UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER));
                    me->GetMotionMaster()->MovePath(PATH_SIMON_DOOR, false);
                    if (!_instance)
                        return;
                    if (Unit * champion = _instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
                        champion->GetMotionMaster()->MoveFollow(me, 1.f, 90.f);
                    break;
                }
                case ACTION_SIMON_DOOR_OPENED:
                {
                    if (_state != STATE_CHAMPION_FREED)
                        break;
                    me->GetMotionMaster()->MovePath(PATH_SIMON_ROOM, false);
                    break;
                }
                case ACTION_VAMPIRE_BIGBANG:
                {
                    if (_state != STATE_ESCAPED)
                        break;
                    me->SetPhaseMask(1, true);
                    me->NearTeleportTo(986.35f, -214.82f, -61.78f, 5.48f);
                    me->CastSpell(me, SPELL_TELEPORT_VISUAL, true);
                    me->setFaction(250);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, ITEM_WANDERER_WEAPON);
                    if (!_instance)
                        return;
                    if (Unit * vampire = _instance->GetCreature(DATA_BOSS_FIVE))
                        me->Attack(vampire, false);
                    break;
                }
                case ACTION_VAMPIRE_KILLED:
                {
                    if (_state != STATE_ESCAPED)
                        break;
                    me->GetMotionMaster()->MovePoint(POINT_VAMPIRE_CORPSE, 1010.51f, -240.49f, -61.38f);
                    break;
                }
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
            {
                switch(id)
                {
                case POINT_FIRST_BOSS_DOOR:
                {
                    if (GameObject * door = _instance->GetGameObject(DATA_GO_FIRST_BOSS_ENTRANCE))
                        door->SetGoState(GO_STATE_ACTIVE);
                    DoFirstBossEntranceEvent();
                    break;
                }
                case POINT_COCCON:
                    me->MonsterSay("Jonas! Good to see you, hope you are not harmed.", LANG_UNIVERSAL, me);
                    me->SetFlag(UNIT_NPC_FLAGS, (UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER));
                    if (Unit * cocoon = _instance->GetCreature(DATA_NPC_CHAMPION_COCCON))
                        cocoon->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    break;
                case POINT_VAMPIRE_CORPSE:
                {
                    DoSoulstoneScene();
                    break;
                }
                }

            }
            else if (type == WAYPOINT_MOTION_TYPE)
            {
                if(_state == STATE_FIRST_BOSS_KILLED)
                {
                    switch (id)
                    {
                    case POINT_FIRST_BOSS_CORPSE:
                            me->MonsterSay("Even after his demise it's hard to withstand here...", LANG_UNIVERSAL, nullptr);
                            _scheduler.Schedule(6s, [&](TaskContext func)
                            {
                                me->MonsterSay("Well done, comrades, let's move on. I feel that my treasure is close.", LANG_UNIVERSAL, nullptr);
                            });
                        break;
                    case POINT_CHAMPION_COCCON:
                            me->SetFlag(UNIT_NPC_FLAGS, (UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER));
                        break;
                    }
                }
                else if (_state == STATE_CHAMPION_FREED)
                {
                    switch (id)
                    {
                        case POINT_SIMON_DOOR:
                        {
                            if (!_instance)
                                return;
                            if (Unit * champion = _instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
                                if (champion->IsAIEnabled)
                                    champion->GetAI()->DoAction(ACTION_SIMON_DOOR);
                            _simonDoorOpened = true;
                            break;
                        }
                        case POINT_SIMON:
                        {
                            if (!_simonDoorOpened)
                                break;
                            me->MonsterSay("What is that noise behind us...? Jonas, lead my companions to Hephasto, recover my stone and I will reward you generously. I am going to secure our backs and will rejoin you soon.", LANG_UNIVERSAL, nullptr);
                            _scheduler.Schedule(15s, [&](TaskContext func)
                            {
                                me->GetMotionMaster()->MovePoint(POINT_SIMON_ESCAPE, 1332.02f, -362.91f, -92.f);
                                _scheduler.Schedule(5s, [&](TaskContext func)
                                {
                                    me->SetPhaseMask(300, true);
                                });
                            });
                            if (!_instance)
                                return;
                            if (Unit * champion = _instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
                            {
                                champion->GetMotionMaster()->MovementExpired(true);
                                if (champion->IsAIEnabled)
                                    champion->GetAI()->DoAction(ACTION_GO_TO_SIMON);
                            }
                            ChangeState(STATE_ESCAPED);
                            break;
                        }
                    }
                }
            }
        }

        void DoFirstBossEntranceEvent()
        {
            for (uint32 i = 0; i < FIRST_BOSS_BURNING_WORMS_COUNT; ++i)
            {
                if (Creature * worm = me->SummonCreature(NPC_BURNING_WORM, FirstBossBurningWormsPosition[i], TEMPSUMMON_TIMED_DESPAWN, 15000))
                {
                    worm->CastSpell(worm, SPELL_BURNING_WORM_AURA);
                    worm->AddAura(44457, worm);
                    worm->SetMaxHealth(urand(354, 521));
                    worm->SetFullHealth();
                    worm->SetRegeneratingHealth(false);
                    Position pos = FirstBossBurningWormsPoint[i];
                    worm->MonsterMoveWithSpeed(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), 3.f);
                }
            }

            _scheduler.Schedule(5s, [&](TaskContext /*func*/)
            {
                me->MonsterYell("What the hell is that?!", LANG_UNIVERSAL, me);
                me->SetFlag(UNIT_NPC_FLAGS, (UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER));
            });
        }

        uint32 GetData(uint32 /*id = 0*/) const override
        {
            return _state;
        }

        void ChangeState(HellforgeWandererState state, bool teleport = false)
        {
            if (state >= STATE_WANDERER_MAX)
                return;

            _state = state;
            if (teleport)
            {
                me->NearTeleportTo(WandererStatePosition[state]);
                if (state == STATE_ESCAPED)
                    me->SetPhaseMask(300, true);
                else
                    me->SetPhaseMask(1, true);
            }
        }

        void EnterEvadeMode() override { }

        void DoSoulstoneScene()
        {
            me->SetStandState(UNIT_STAND_STATE_KNEEL);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
            _scheduler.Schedule(3s, [&](TaskContext func)
            {
                if (Unit * soulstone = me->SummonCreature(NPC_SOUL_STONE, { 1011.57f, -242.20f, -54.14f, 5.14f }, TEMPSUMMON_TIMED_DESPAWN, 5000))
                {
                    soulstone->SetDisableGravity(true);
                    soulstone->SetCanFly(true);
                    soulstone->MonsterMoveWithSpeed(1011.57f, -242.20f, -61.38f, 2.5f);
                }
            });

            _scheduler.Schedule(8s, [&](TaskContext func)
            {
                if (Creature * portal = me->SummonCreature(NPC_WORLD_TRIGGER, { 997.83f, -226.25f, -58.83f, 5.46f }, TEMPSUMMON_TIMED_DESPAWN, 10000))
                {
                    portal->SetReactState(REACT_PASSIVE);
                    portal->CastSpell(portal, SPELL_WANDERER_PORTAL, true);
                }
            });

            _scheduler.Schedule(10s, [&](TaskContext func)
            {
                me->MonsterMoveWithSpeed(997.83f, -226.25f, -61.83f, 3.f);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                me->MonsterTextEmote("The Wanderer smiles.", me);
            });

            _scheduler.Schedule(17s, [&](TaskContext /*func*/)
            {
                me->SetPhaseMask(300, true);
            });

            _scheduler.Schedule(15s, [&](TaskContext /*func*/)
            {
                me->SummonCreature(NPC_HELLFORGE_TYRAEL, _tyraelPosition);
            });
        }

        void UpdateAI(uint32 diff) override
        {
            UpdateVictim();
            _scheduler.Update(diff);
            DoMeleeAttackIfReady();
        }

        void HandleWandererState()
        {
            if (!_instance)
                return;

            if (_instance->GetBossState(DATA_BOSS_FIVE) == DONE)
                ChangeState(STATE_ESCAPED, true);
            else if (_instance->GetData(DATA_GET_HELLFORGE_GAUNTLET_STATE))
                ChangeState(STATE_ESCAPED, true);
            else if (_instance->GetBossState(DATA_BOSS_FOUR) == DONE)
                ChangeState(STATE_ESCAPED, true);
            else if (_instance->GetBossState(DATA_BOSS_THREE) == DONE)
                ChangeState(STATE_ESCAPED, true);
            else if (_instance->GetBossState(DATA_BOSS_TWO) == DONE)
                ChangeState(STATE_CHAMPION_FREED, true);
            else if (_instance->GetBossState(DATA_BOSS_ONE) == DONE)
                ChangeState(STATE_FIRST_BOSS_KILLED, true);
            else if (!_instance->GetData(DATA_GET_HELLFORGE_FIRST_ROOM_TRASH_COUNT))
                //ChangeState(STATE_FIRST_BOSS_DOOR, true);
                DoAction(ACTION_KILLED_TRASH);
            else
                ChangeState(STATE_RAID_ENTRANCE, true);

        }

    private:
        InstanceScript* _instance;
        HellforgeWandererState _state;
        TaskScheduler _scheduler;
        bool _simonDoorOpened;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hellforge_wandererAI(creature);
    }
};

struct npc_hellforge_wanderer_champion_cocoonAI : public ScriptedAI
{
    npc_hellforge_wanderer_champion_cocoonAI(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
        
        if(_instance)
        {
            Creature* defender = _instance->GetCreature(DATA_NPC_TRASH_HELLFORGE_DEFENDER);

            if (defender && defender->IsAlive())
            {
                me->SetPhaseMask(defender->GetPhaseMask(), true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }
        }
    }

    void Reset() override
    {
        me->SetMaxHealth(2);
        me->setFaction(14);
        me->SetReactState(REACT_DEFENSIVE);
        me->SetControlled(true, UNIT_STATE_ROOT);
        me->SetRespawnDelay(7 * DAY);
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*damageSchoolMask*/) override
    {
        if (!_instance)
            return;

        if (Creature* snake = _instance->GetCreature(DATA_BOSS_TWO))
        {
            if (_instance->GetBossState(DATA_BOSS_TWO) != DONE)
            {
                if (!snake->IsVisible() && snake->IsAlive())
                {
                    snake->AI()->SetData(11, 11);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                }
                me->DeleteThreatList();
                me->CombatStop(true);
                me->getHostileRefManager().deleteReferences();
                damage = 0;
            }
        }
    }

    void JustDied(Unit* killer) override
    {
        if (!_instance)
            return;

        if (Creature* champion = _instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
        {
            if (champion->IsAIEnabled)
                champion->GetAI()->DoAction(ACTION_CHAMPION_FREED);
        }
    }

    bool CanAIAttack(Unit const* victim) const override
    {
        return false;
    }

    void UpdateAI(uint32 diff) override { }

    void DoAction(int32 param) override
    {
        switch(param)
        {
        case ACTION_SHOW_COCCON:
            me->SetPhaseMask(1, true);
            break;
        case ACTION_TRASH_DEFENDER_KILLED:
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            break;
        }
            
    }

private:
    InstanceScript* _instance;
};

class npc_hellforge_wanderer_champion : public CreatureScript
{
public:
    npc_hellforge_wanderer_champion() : CreatureScript("npc_hellforge_wanderer_champion") {}

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (creature->IsAIEnabled)
        {
            HellforgeChampionState state = static_cast<HellforgeChampionState>(creature->GetAI()->GetData(0));
            if (state == STATE_SAIMON_KILLED)
            {
                if(InstanceScript* instance = creature->GetInstanceScript())
                {
                    if(!instance->GetData(DATA_GET_HELLFORGE_DWARF_ROOM_TRASH_COUNT) || player->IsGameMaster())
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Let's finish this", GOSSIP_SENDER_MAIN, ACTION_DWARF_PULLED);
                }
            }
        }

        if (player->IsGameMaster())
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "*DEBUG* Change state", GOSSIP_SENDER_MAIN, 1000);

        player->SEND_GOSSIP_MENU(GOSSIP_CHAMPION, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        switch (action)
        {
            case ACTION_DWARF_PULLED:
                if (creature->IsAIEnabled)
                    creature->GetAI()->DoAction(ACTION_DWARF_PULLED);
                player->CLOSE_GOSSIP_MENU();
                break;
            case 1000:
                player->PlayerTalkClass->ClearMenus();
                for (uint32 i = STATE_TRAPPED; i < STATE_CHAMPION_MAX; ++i)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GetStateName(static_cast<HellforgeChampionState>(i)).c_str(), GOSSIP_SENDER_MAIN, 2000 + i);
                }
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                break;
        }

        if (player->IsGameMaster() && action >= 2000)
        {
            uint32 state = action - 2000;
            CAST_AI(npc_hellforge_wanderer_championAI, creature->GetAI())->ChangeState(static_cast<HellforgeChampionState>(state), true);
            player->CLOSE_GOSSIP_MENU();
        }

        return true;
    }

    std::string const GetStateName(HellforgeChampionState state) const
    {
        switch (state)
        {
            case STATE_TRAPPED:
                return "STATE_TRAPPED";
            case STATE_FREED:
                return "STATE_FREED";
            case STATE_SAIMON_KILLED:
                return "STATE_SAIMON_KILLED";
            case STATE_DWARF_KILLED:
                return "STATE_DWARF_KILLED";
            case STATE_GAUNTLET_DONE:
                return "STATE_GAUNTLET_DONE";
            case STATE_CHAMPION_DEAD:
                return "STATE_CHAMPION_DEAD";
            default:
                return "UNKNOWN";
        }
    }

    struct npc_hellforge_wanderer_championAI : public ScriptedAI
    {
        npc_hellforge_wanderer_championAI(Creature* creature) : ScriptedAI(creature), _state(STATE_TRAPPED)
        {
            _instance = me->GetInstanceScript();
            me->SetRespawnTime(7 * DAY);
            HandleChampionState();
        }

        void Reset() override
        {
            LoadStats();
        }

        void LoadStats()
        {
            HellforgeStats _stats = sWorldCache.GetStatValues({ CHAMPION_STATS_MAX_HEALTH });
            for (auto const& ref : _stats)
            {
                switch (ref.first)
                {
                    case CHAMPION_STATS_MAX_HEALTH:
                    {
                        me->SetMaxHealth(ref.second.StatValue);
                        me->SetFullHealth();
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*damageSchoolMask*/) override
        {
            if (damage >= me->GetHealth())
                damage = 0;
        }

        void EnterEvadeMode() override { }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
            {
                switch (id)
                {
                    case POINT_SIMON_ROOM:
                    {
                        me->SetFacingTo(1.25f);
                        break;
                    }
                    case POINT_DWARF_ROOM:
                    {
                        if (!_instance)
                            return;
                        me->CastSpell(me, SPELL_CHAMPION_FLARE);
                        me->MonsterSay("Let's do it.", LANG_UNIVERSAL, me);
                        _scheduler.Schedule(2s, [&](TaskContext /*func*/)
                        {
                            if (Creature * dwarf = _instance->GetCreature(DATA_BOSS_FOUR))
                            {
                                Player* victim = nullptr;
                                auto const& pl = _instance->instance->GetPlayers();
                                for (auto itr = pl.begin(); itr != pl.end(); ++itr)
                                {
                                    if (itr->GetSource()->IsGameMaster())
                                        continue;
                                    victim = itr->GetSource();
                                    break;
                                }
                                if (victim)
                                {
                                    dwarf->Attack(victim, false);
                                    DoZoneInCombat(dwarf, 100.f);
                                }
                                if (!dwarf->IsInCombat())
                                    DoAction(ACTION_DWARF_WIPE);
                            }
                        });
                        break;
                    }
                    case POINT_DWARF_ROOM_2:
                    {
                        me->SetFacingTo(2.37f);
                        break;
                    }
                    case POINT_VAMPIRE_LAVA:
                    {
                        _scheduler.Schedule(3s, [&](TaskContext func)
                        {
                            me->RemoveAllAuras();
                            me->SetCanFly(false);
                            me->SetDisableGravity(false);
                            me->GetMotionMaster()->MoveFall();
                        });
                        _scheduler.Schedule(10s, [&](TaskContext func)
                        {
                            me->DespawnOrUnsummon();
                            ChangeState(STATE_CHAMPION_DEAD);
                        });
                        break;
                    }
                    case POINT_GAUNTLET:
                    {
                        me->SetImmuneToNPC(false);
                        me->setFaction(250);
                        if (Unit * victim = me->SelectNearestTarget(15.f))
                            me->Attack(victim, false);
                        me->MonsterSay("Watch your left!", LANG_UNIVERSAL, nullptr);
                        break;
                    }
                    case POINT_VAMPIRE_ROOM:
                    {
                        me->MonsterSay("Stay! Don't cross the gate!", LANG_UNIVERSAL, me);
                        _scheduler.Schedule(3s, [&](TaskContext func)
                        {
                            me->MonsterSay("Black Witch is completely blind. If we creep down enough, we will enter her lounge and she won't even notice!", LANG_UNIVERSAL, me);
                        });
                        _scheduler.Schedule(4s, [&](TaskContext func)
                        {
                            if (GameObject * gate = _instance->GetGameObject(DATA_GO_GAUNTLET_DOORS))
                                gate->SetGoState(GO_STATE_ACTIVE);
                        });
                        _scheduler.Schedule(5s, [&](TaskContext func)
                        {
                            me->SetWalk(true);
                            me->GetMotionMaster()->MovePoint(POINT_VAMPIRE_ROOM_2, ChampionStatePosition[STATE_GAUNTLET_DONE]);
                        });
                        break;
                    }
                    case POINT_VAMPIRE_ROOM_2:
                    {
                        me->SetWalk(false);
                        if (Creature * vampire = _instance->GetCreature(DATA_BOSS_FIVE))
                            vampire->ClearUnitState(UNIT_STATE_UNATTACKABLE);
                        ChangeState(STATE_GAUNTLET_DONE);
                        break;
                    }
                    default:
                        break;
                }
            }
            else if (type == WAYPOINT_MOTION_TYPE)
            {
                if (_state == STATE_DWARF_KILLED && id == POINT_GAUNTLET_2)
                {
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                }
            }
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_BOSS_FOUR_THROW_SPEAR)
            {
                me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                me->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                me->SetImmuneToNPC(true);
                me->setFaction(35);
                me->SetHealth(1);
                me->StopMoving();
            }
        }

        void HealReceived(Unit* healer, uint32& heal) override
        {
            if (me->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) && me->HealthAbovePctHealed(100, heal))
            {
                auto const& players = me->GetMap()->GetPlayers();
                for (auto const& _ref : players)
                {
                    Player* player = _ref.GetSource();
                    if (!player)
                        continue;

                    if (player->GetQuestStatus(QUEST_WANDERER_Q6) == QUEST_STATUS_INCOMPLETE)
                        player->KilledMonsterCredit(NPC_Q6_HEAL_CREDIT, 0);
                }

                me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                me->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                me->MonsterSay("Thank you for recovery heroes, that was rough!", LANG_UNIVERSAL, me);

                _scheduler.Schedule(6s, [&](TaskContext /*func*/)
                {
                    me->MonsterSay("We have to go forward... to find this vampire.", LANG_UNIVERSAL, me);

                    _scheduler.Schedule(6s, [&](TaskContext /*func*/)
                    {
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        me->GetMotionMaster()->MovePath(me->GetEntry() * 10, false);
                    });

                });
            }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
                case ACTION_CHAMPION_FREED:
                {
                    if (_state != STATE_TRAPPED)
                        break;
                    me->SetPhaseMask(1, true);
                    me->MonsterSay("Free at last!", LANG_UNIVERSAL, nullptr);
                    ChangeState(STATE_FREED);

                    if (!_instance)
                        return;

                    auto const& players = me->GetMap()->GetPlayers();
                    for (auto const& _ref : players)
                    {
                        Player* player = _ref.GetSource();
                        if (!player)
                            continue;

                        player->AreaExploredOrEventHappens(QUEST_WANDERER_Q3);
                    }

                    if (Unit* wanderer = _instance->GetCreature(DATA_NPC_WANDERER))
                        if (wanderer->IsAIEnabled)
                            wanderer->GetAI()->DoAction(ACTION_CHAMPION_FREED);
                    break;
                }
                case ACTION_SIMON_DOOR:
                {
                    if (_state != STATE_FREED)
                        break;

                    if (!_instance)
                        return;

                    me->MonsterSay("This hall leads to Hephasto's forge, give me a moment...", LANG_UNIVERSAL, nullptr);
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_USE_STANDING);

                    _scheduler.Schedule(5s, [&](TaskContext /*func*/)
                    {
                        if (GameObject* door = me->FindNearestGameObject(GO_SIMON_DOOR, 20.f))
                        {
                            door->UseDoorOrButton();
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                        }

                        _scheduler.Schedule(5s, [&](TaskContext /*func*/)
                        {
                            if (Unit * wanderer = _instance->GetCreature(DATA_NPC_WANDERER))
                                if (wanderer->IsAIEnabled)
                                    wanderer->GetAI()->DoAction(ACTION_SIMON_DOOR_OPENED);
                            me->MonsterYell("Forward!", LANG_UNIVERSAL, nullptr);
                        });
                    });
                    break;
                }
                case ACTION_SIMON_KILLED:
                {
                    if (_state != STATE_FREED)
                        break;

                    me->MonsterSay("Hephasto, you bastard, we are coming for you!", LANG_UNIVERSAL, me);
                    me->GetMotionMaster()->MovePoint(POINT_DWARF_DOOR, 1231.81f, -207.f, -85.5f);
                    ChangeState(STATE_SAIMON_KILLED);
                    break;
                }
                case ACTION_DWARF_PULLED:
                {
                    if (_state != STATE_SAIMON_KILLED)
                        break;

                    me->GetMotionMaster()->MovePoint(POINT_DWARF_ROOM, 1200.41f, -174.63f, -74.3f);
                    me->RemoveFlag(UNIT_NPC_FLAGS, (UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER));
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
                }
                case ACTION_DWARF_INTERPHASE:
                {
                    if (_state != STATE_SAIMON_KILLED)
                        break;

                    me->CombatStop();
                    me->SetReactState(REACT_PASSIVE);
                    me->GetMotionMaster()->MovePoint(POINT_DWARF_ROOM_2, 1200.41f, -174.63f, -74.3f);
                    break;
                }
                case ACTION_DWARF_WIPE:
                {
                    if (_state != STATE_SAIMON_KILLED)
                        break;

                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                    me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                    me->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                    me->SetFlag(UNIT_NPC_FLAGS, (UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER));
                    me->setFaction(35);
                    me->SetHealth(me->GetMaxHealth());
                    me->CombatStop();
                    me->getThreatManager().clearReferences();
                    me->AttackStop();
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->NearTeleportTo({ 1231.81f, -207.f, -85.5f, 2.37f });
                    me->SetReactState(REACT_PASSIVE);
                    break;
                }
                case ACTION_DWARF_KILLED:
                {
                    if (_state != STATE_SAIMON_KILLED)
                        break;

                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                    me->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                    me->SetFlag(UNIT_NPC_FLAGS, (UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER));
                    me->setFaction(35);
                    ChangeState(STATE_DWARF_KILLED);
                    break;
                }
                case ACTION_VAMPIRE_STRANGULATE:
                {
                    if (_state != STATE_GAUNTLET_DONE)
                        break;

                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_BOSS_FIVE_STRANGULATING);
                    if (spellInfo)
                        Aura::TryRefreshStackOrCreate(spellInfo, MAX_EFFECT_MASK, me, me);
                    me->MonsterYell("Arghhhh!", LANG_UNIVERSAL, me);
                    me->SetInhabitType(INHABIT_ANYWHERE);
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    _scheduler.Schedule(3s, [&](TaskContext /*func*/)
                    {
                        me->GetMotionMaster()->MovePoint(POINT_VAMPIRE_LAVA, 1043.63f, -272.33f, -58.24f, false);
                    });
                    break;
                }
                case ACTION_GAUNTLET_PULLED:
                {
                    if (_state != STATE_DWARF_KILLED)
                        break;

                    me->GetMotionMaster()->MovePoint(POINT_GAUNTLET, 1068.86f, -187.03f, -64.02f);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    break;
                }
                case ACTION_GAUNTLET_FAILED:
                {
                    if (_state != STATE_DWARF_KILLED)
                        break;

                    me->SetImmuneToNPC(true);
                    me->setFaction(35);
                    me->NearTeleportTo(ChampionStatePosition[STATE_DWARF_KILLED]);
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    break;
                }
                case ACTION_GAUNTLET_DONE:
                {
                    if (_state != STATE_DWARF_KILLED)
                        break;

                    me->SetImmuneToNPC(true);
                    me->setFaction(35);
                    me->GetMotionMaster()->MovePoint(POINT_VAMPIRE_ROOM, 1046.58f, -206.61f, -61.98f);
                    if (Creature* vampire = _instance->GetCreature(DATA_BOSS_FIVE))
                        vampire->AddUnitState(UNIT_STATE_UNATTACKABLE);
                    break;
                }
                case ACTION_GO_TO_SIMON:
                    _scheduler.Schedule(6s, [&](TaskContext /*func*/)
                    {
                        me->MonsterSay("Aye! Follow me, heroes!", LANG_UNIVERSAL, me);
                        _scheduler.Schedule(2s, [&](TaskContext /*func*/)
                        {
                            me->GetMotionMaster()->MovePoint(POINT_SIMON_ROOM, 1250.13f, -284.04f, -78.21f);
                        });
                    });
                    break;
            }
        }

        void ChangeState(HellforgeChampionState state, bool teleport = false)
        {
            if (state >= STATE_CHAMPION_MAX)
                return;

            _state = state;
            if (teleport)
            {
                if (state != STATE_CHAMPION_DEAD)
                    me->Respawn();

                me->NearTeleportTo(ChampionStatePosition[state]);
                if (state == STATE_CHAMPION_DEAD || state == STATE_TRAPPED)
                    me->SetPhaseMask(300, true);
                else
                    me->SetPhaseMask(1, true);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _scheduler.Update(diff);
            UpdateVictim();
            DoMeleeAttackIfReady();
        }

        uint32 GetData(uint32 /*id = 0*/) const override
        {
            return _state;
        }

        void HandleChampionState()
        {
            if (!_instance)
                return;

            if (_instance->GetBossState(DATA_BOSS_FIVE) == DONE)
                ChangeState(STATE_CHAMPION_DEAD, true);
            else if (_instance->GetData(DATA_GET_HELLFORGE_GAUNTLET_STATE))
                ChangeState(STATE_GAUNTLET_DONE, true);
            else if (_instance->GetBossState(DATA_BOSS_FOUR) == DONE)
                ChangeState(STATE_DWARF_KILLED, true);
            else if (_instance->GetBossState(DATA_BOSS_THREE) == DONE)
                ChangeState(STATE_SAIMON_KILLED, true);
            else if (_instance->GetBossState(DATA_BOSS_TWO) == DONE)
                ChangeState(STATE_FREED, true);
            else
                ChangeState(STATE_TRAPPED, true);
        }

    private:
        InstanceScript* _instance;
        HellforgeChampionState _state;
        TaskScheduler _scheduler;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hellforge_wanderer_championAI(creature);
    }
};

struct npc_hellforge_tyraelAI : public ScriptedAI
{
    npc_hellforge_tyraelAI(Creature* creature) : ScriptedAI(creature) {}

    void sGossipHello(Player* player)
    {
        if (me->IsQuestGiver())
           player->PrepareQuestMenu(me->GetGUID());
        player->SEND_GOSSIP_MENU(GOSSIP_TYRAEL, me->GetGUID());
    }

    void Reset() override
    {
        me->RemoveFlag(UNIT_NPC_FLAGS, (UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER));
        me->SetPhaseMask(300, true);

        float speedZ = 20.f;
        float moveTimeHalf = speedZ / Movement::gravity;
        float max_height = -Movement::computeFallElevation(moveTimeHalf, false, -speedZ);

        Movement::MoveSplineInit init(me);
        init.MoveTo(1018.05f, -238.21f, -61.62f);
        init.SetParabolic(max_height, 0);
        init.SetVelocity(1.f);

        std::chrono::milliseconds timer(init.Launch());

        _scheduler.Schedule(3s, [&](TaskContext func)
        {
            me->SetPhaseMask(1, true);
        });

        _scheduler.Schedule(timer, [&](TaskContext func)
        {
            switch (func.GetRepeatCounter())
            {
                case 0:
                    me->CastSpell(me, SPELL_TYRAEL_VISUAL);
                    func.Repeat(1s);
                    break;
                case 1:
                    me->MonsterSay("Mortals...", LANG_UNIVERSAL, me);
                    func.Repeat(3s);
                    break;
                case 2:
                    me->MonsterSay("You just helped inconceivable evil to recover its powers...", LANG_UNIVERSAL, me);
                    func.Repeat(3s);
                    break;
                case 3:
                    me->MonsterSay("Now you must face real opponent to save this world.", LANG_UNIVERSAL, me);
                    func.Repeat(1s);
                    break;
                case 4:
                    me->SetFlag(UNIT_NPC_FLAGS, (UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER));
                    break;
                default:
                    break;
            }
        });
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

private:
    TaskScheduler _scheduler;
};

void AddSC_hellforge_npc_wanderer()
{
    new npc_hellforge_wanderer();
    new npc_hellforge_wanderer_champion();
    new CreatureAILoader<npc_hellforge_wanderer_champion_cocoonAI>("npc_hellforge_wanderer_champion_cocoon");
    new CreatureAILoader<npc_hellforge_tyraelAI>("npc_hellforge_tyrael");
}
