/*
 * Copyright (C)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "blackrock_depths.h"
#include "Player.h"
#include "Group.h"
#include "WorldSession.h"

//go_shadowforge_brazier
class go_shadowforge_brazier : public GameObjectScript
{
public:
    go_shadowforge_brazier() : GameObjectScript("go_shadowforge_brazier") { }

    bool OnGossipHello(Player* /*player*/, GameObject* go)
    {
        if (InstanceScript* instance = go->GetInstanceScript())
        {
            if (instance->GetData(TYPE_LYCEUM) == IN_PROGRESS)
                instance->SetData(TYPE_LYCEUM, DONE);
            else
                instance->SetData(TYPE_LYCEUM, IN_PROGRESS);
            // If used brazier open linked doors (North or South)
            if (go->GetGUID() == instance->GetData64(DATA_SF_BRAZIER_N))
                instance->HandleGameObject(instance->GetData64(DATA_GOLEM_DOOR_N), true);
            else if (go->GetGUID() == instance->GetData64(DATA_SF_BRAZIER_S))
                instance->HandleGameObject(instance->GetData64(DATA_GOLEM_DOOR_S), true);
        }
        return false;
    }
};

enum eChallenge
{
    QUEST_THE_CHALLENGE                    = 9015,
    GO_BANNER_OF_PROVOCATION            = 181058,
    GO_ARENA_SPOILS                        = 181074,

    NPC_GRIMSTONE                        = 10096,
    NPC_THELDREN                        = 16059,
};

uint32 theldrenTeam[] =
{
    16053, 16055, 16050, 16051, 16049, 16052, 16054, 16058
};

uint32 RingMob[]=
{
    8925,                                                   // Dredge Worm
    8926,                                                   // Deep Stinger
    8927,                                                   // Dark Screecher
    8928,                                                   // Burrowing Thundersnout
    8933,                                                   // Cave Creeper
    8932,                                                   // Borer Beetle
};

uint32 RingBoss[]=
{
    9027,                                                   // Gorosh
    9028,                                                   // Grizzle
    9029,                                                   // Eviscerator
    9030,                                                   // Ok'thor
    9031,                                                   // Anub'shiah
    9032,                                                   // Hedrum
};

class at_ring_of_law : public AreaTriggerScript
{
public:
    at_ring_of_law() : AreaTriggerScript("at_ring_of_law") { }

    bool OnTrigger(Player* player, const AreaTriggerEntry* /*at*/)
    {
        if (InstanceScript* instance = player->GetInstanceScript())
        {
            if (instance->GetData(TYPE_RING_OF_LAW) == IN_PROGRESS || instance->GetData(TYPE_RING_OF_LAW) == DONE)
                return false;

            instance->SetData(TYPE_RING_OF_LAW, IN_PROGRESS);
            player->SummonCreature(NPC_GRIMSTONE, 625.559f, -205.618f, -52.735f, 2.609f, TEMPSUMMON_DEAD_DESPAWN, 0);

            return false;
        }
        return false;
    }
};

// npc_grimstone
enum GrimstoneTexts
{
    SAY_TEXT1          = 0,
    SAY_TEXT2          = 1,
    SAY_TEXT3          = 2,
    SAY_TEXT4          = 3,
    SAY_TEXT5          = 4,
    SAY_TEXT6          = 5
};

class npc_grimstone : public CreatureScript
{
public:
    npc_grimstone() : CreatureScript("npc_grimstone") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetInstanceAI<npc_grimstoneAI>(creature);
    }

    struct npc_grimstoneAI : public npc_escortAI
    {
        npc_grimstoneAI(Creature* creature) : npc_escortAI(creature), summons(me)
        {
            instance = creature->GetInstanceScript();
            MobSpawnId = rand()%6;
            eventPhase = 0;
            eventTimer = 1000;
            theldrenEvent = false;
            summons.DespawnAll();
        }

        InstanceScript* instance;
        SummonList summons;

        uint8 eventPhase;
        uint32 eventTimer;
        uint8 MobSpawnId;
        bool theldrenEvent;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            if (Unit* target = SelectTargetFromPlayerList(100.0f))
                summon->AI()->AttackStart(target);
        }

        void SummonedCreatureDies(Creature* summon, Unit*)
        {
            summons.Despawn(summon);
            // All Summons killed, next phase
            if (summons.empty())
                eventTimer = 5000;
        }

        void WaypointReached(uint32 waypointId)
        {
            switch (waypointId)
            {
                case 0:
                    Talk(SAY_TEXT1);
                    SetEscortPaused(true);
                    eventTimer = 5000;
                    break;
                case 1:
                    Talk(SAY_TEXT2);
                    SetEscortPaused(true);
                    eventTimer = 5000;
                    break;
                case 2:
                    SetEscortPaused(true);
                    break;
                case 3:
                    Talk(SAY_TEXT3);
                    break;
                case 4:
                    Talk(SAY_TEXT4);
                    SetEscortPaused(true);
                    eventTimer = 5000;
                    break;
                case 5:
                    if (instance)
                    {
                        me->GetMap()->UpdateEncounterState(ENCOUNTER_CREDIT_KILL_CREATURE, NPC_GRIMSTONE, me);
                        instance->SetData(TYPE_RING_OF_LAW, DONE);
                    }
                    break;
            }
        }

        void HandleGameObject(uint32 id, bool open)
        {
            instance->HandleGameObject(instance->GetData64(id), open);
        }

        void SummonBoss()
        {
            if (me->FindNearestGameObject(GO_BANNER_OF_PROVOCATION, 100.0f))
            {
                theldrenEvent = true;
                me->SummonCreature(NPC_THELDREN, 644.300f, -175.989f, -53.739f, 3.418f, TEMPSUMMON_DEAD_DESPAWN, 0);
                uint8 rand = urand(0, 4);
                for (uint8 i = rand; i < rand+4; ++i)
                    me->SummonCreature(theldrenTeam[i], 644.300f, -175.989f, -53.739f, 3.418f, TEMPSUMMON_DEAD_DESPAWN, 0);
            }
            else
                me->SummonCreature(RingBoss[rand()%6], 644.300f, -175.989f, -53.739f, 3.418f, TEMPSUMMON_DEAD_DESPAWN, 0);
        }

        void UpdateEscortAI(uint32 diff)
        {
            if (!instance)
                return;

            if (eventTimer)
            {
                if (eventTimer <= diff)
                {
                    switch (eventPhase)
                    {
                        case 0:
                            Talk(SAY_TEXT5);
                            HandleGameObject(DATA_ARENA4, false);
                            Start(false, false);
                            eventTimer = 0;
                            break;
                        case 1:
                            SetEscortPaused(false);
                            eventTimer = 0;
                            break;
                        case 2:
                            eventTimer = 2000;
                            break;
                        case 3:
                            HandleGameObject(DATA_ARENA1, true);
                            eventTimer = 3000;
                            break;
                        case 4:
                            SetEscortPaused(false);
                            me->SetVisible(false);
                            me->SummonCreature(RingMob[MobSpawnId], 608.960f, -235.322f, -53.907f, 1.857f, TEMPSUMMON_DEAD_DESPAWN, 0);
                            eventTimer = 8000;
                            break;
                        case 5:
                            me->SummonCreature(RingMob[MobSpawnId], 608.960f, -235.322f, -53.907f, 1.857f, TEMPSUMMON_DEAD_DESPAWN, 0);
                            me->SummonCreature(RingMob[MobSpawnId], 608.960f, -235.322f, -53.907f, 1.857f, TEMPSUMMON_DEAD_DESPAWN, 0);
                            eventTimer = 8000;
                            break;
                        case 6:
                            me->SummonCreature(RingMob[MobSpawnId], 608.960f, -235.322f, -53.907f, 1.857f, TEMPSUMMON_DEAD_DESPAWN, 0);
                            eventTimer = 0;
                            break;
                        case 7:
                            me->SetVisible(true);
                            HandleGameObject(DATA_ARENA1, false);
                            Talk(SAY_TEXT6);
                            SetEscortPaused(false);
                            eventTimer = 0;
                            break;
                        case 8:
                            HandleGameObject(DATA_ARENA2, true);
                            eventTimer = 5000;
                            break;
                        case 9:
                            me->SetVisible(false);
                            SummonBoss();
                            eventTimer = 0;
                            break;
                        case 10:
                            if (theldrenEvent)
                            {
                                if (GameObject* go = me->SummonGameObject(GO_ARENA_SPOILS, 596.48f, -187.91f, -54.14f, 4.9f, 0.0f, 0.0f, 0.0f, 0.0f, 300))
                                    go->SetOwnerGUID(0);

                                Map::PlayerList const &pl = me->GetMap()->GetPlayers();
                                for (Map::PlayerList::const_iterator itr = pl.begin(); itr != pl.end(); ++itr)
                                    itr->GetSource()->KilledMonsterCredit(16166, 0);
                            }

                            HandleGameObject(DATA_ARENA2, false);
                            HandleGameObject(DATA_ARENA3, true);
                            HandleGameObject(DATA_ARENA4, true);
                            SetEscortPaused(false);
                            break;
                    }
                    ++eventPhase;
                }
                else
                    eventTimer -= diff;
            }
        }
    };
};

// npc_kharan_mighthammer
enum KharamQuests
{
    QUEST_4001                          = 4001,
    QUEST_4342                          = 4342
};

#define GOSSIP_ITEM_KHARAN_1    "I need to know where the princess are, Kharan!"
#define GOSSIP_ITEM_KHARAN_2    "All is not lost, Kharan!"
#define GOSSIP_ITEM_KHARAN_3    "Gor'shak is my friend, you can trust me."
#define GOSSIP_ITEM_KHARAN_4    "Not enough, you need to tell me more."
#define GOSSIP_ITEM_KHARAN_5    "So what happened?"
#define GOSSIP_ITEM_KHARAN_6    "Continue..."
#define GOSSIP_ITEM_KHARAN_7    "So you suspect that someone on the inside was involved? That they were tipped off?"
#define GOSSIP_ITEM_KHARAN_8    "Continue with your story please."
#define GOSSIP_ITEM_KHARAN_9    "Indeed."
#define GOSSIP_ITEM_KHARAN_10   "The door is open, Kharan. You are a free man."

class npc_kharan_mighthammer : public CreatureScript
{
public:
    npc_kharan_mighthammer() : CreatureScript("npc_kharan_mighthammer") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(2475, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                player->SEND_GOSSIP_MENU(2476, creature->GetGUID());
                break;

            case GOSSIP_ACTION_INFO_DEF+3:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                player->SEND_GOSSIP_MENU(2477, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                player->SEND_GOSSIP_MENU(2478, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+5:
                 player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                player->SEND_GOSSIP_MENU(2479, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+6:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_8, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
                player->SEND_GOSSIP_MENU(2480, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+7:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_9, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
                player->SEND_GOSSIP_MENU(2481, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+8:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_10, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
                player->SEND_GOSSIP_MENU(2482, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+9:
                player->CLOSE_GOSSIP_MENU();
                if (player->GetTeamId() == TEAM_HORDE)
                    player->AreaExploredOrEventHappens(QUEST_4001);
                else
                    player->AreaExploredOrEventHappens(QUEST_4342);
                break;
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_4001) == QUEST_STATUS_INCOMPLETE)
             player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        if (player->GetQuestStatus(4342) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);

        if (player->GetTeamId() == TEAM_HORDE)
            player->SEND_GOSSIP_MENU(2473, creature->GetGUID());
        else
            player->SEND_GOSSIP_MENU(2474, creature->GetGUID());

        return true;
    }
};

// npc_lokhtos_darkbargainer
enum LokhtosItems
{
    ITEM_THRORIUM_BROTHERHOOD_CONTRACT                     = 18628,
    ITEM_SULFURON_INGOT                                    = 17203
};

enum LokhtosQuests
{
    QUEST_A_BINDING_CONTRACT                               = 7604
};

enum LokhtosSpells
{
    SPELL_CREATE_THORIUM_BROTHERHOOD_CONTRACT_DND          = 23059
};

#define GOSSIP_ITEM_SHOW_ACCESS     "Show me what I have access to, Lothos."
#define GOSSIP_ITEM_GET_CONTRACT    "Get Thorium Brotherhood Contract"

class npc_lokhtos_darkbargainer : public CreatureScript
{
public:
    npc_lokhtos_darkbargainer() : CreatureScript("npc_lokhtos_darkbargainer") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, SPELL_CREATE_THORIUM_BROTHERHOOD_CONTRACT_DND, false);
        }
        if (action == GOSSIP_ACTION_TRADE)
            player->GetSession()->SendListInventory(creature->GetGUID());

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (creature->IsVendor() && player->GetReputationRank(59) >= REP_FRIENDLY)
              player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_ITEM_SHOW_ACCESS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

        if (player->GetQuestRewardStatus(QUEST_A_BINDING_CONTRACT) != 1 &&
            !player->HasItemCount(ITEM_THRORIUM_BROTHERHOOD_CONTRACT, 1, true) &&
            player->HasItemCount(ITEM_SULFURON_INGOT))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GET_CONTRACT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        }

        if (player->GetReputationRank(59) < REP_FRIENDLY)
            player->SEND_GOSSIP_MENU(3673, creature->GetGUID());
        else
            player->SEND_GOSSIP_MENU(3677, creature->GetGUID());

        return true;
    }
};

// npc_rocknot
enum RocknotSays
{
    SAY_GOT_BEER                       = 0
};

enum RocknotSpells
{
    SPELL_DRUNKEN_RAGE                 = 14872
};

enum RocknotQuests
{
    QUEST_ALE                          = 4295
};

class npc_rocknot : public CreatureScript
{
public:
    npc_rocknot() : CreatureScript("npc_rocknot") { }

    bool OnQuestReward(Player* /*player*/, Creature* creature, Quest const* quest, uint32 /*item*/)
    {
        InstanceScript* instance = creature->GetInstanceScript();
        if (!instance)
            return true;

        if (instance->GetData(TYPE_BAR) == DONE || instance->GetData(TYPE_BAR) == SPECIAL)
            return true;

        if (quest->GetQuestId() == QUEST_ALE)
        {
            if (instance->GetData(TYPE_BAR) != IN_PROGRESS)
                instance->SetData(TYPE_BAR, IN_PROGRESS);

            instance->SetData(TYPE_BAR, SPECIAL);

            //keep track of amount in instance script, returns SPECIAL if amount ok and event in progress
            if (instance->GetData(TYPE_BAR) == SPECIAL)
            {
                creature->AI()->Talk(SAY_GOT_BEER);
                creature->CastSpell(creature, SPELL_DRUNKEN_RAGE, false);

                if (npc_escortAI* escortAI = CAST_AI(npc_rocknot::npc_rocknotAI, creature->AI()))
                    escortAI->Start(false, false);
            }
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetInstanceAI<npc_rocknotAI>(creature);
    }

    struct npc_rocknotAI : public npc_escortAI
    {
        npc_rocknotAI(Creature* creature) : npc_escortAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 BreakKeg_Timer;
        uint32 BreakDoor_Timer;

        void Reset()
        {
            if (HasEscortState(STATE_ESCORT_ESCORTING))
                return;

            BreakKeg_Timer = 0;
            BreakDoor_Timer = 0;
        }

        void DoGo(uint32 id, uint32 state)
        {
            if (GameObject* go = instance->instance->GetGameObject(instance->GetData64(id)))
                go->SetGoState((GOState)state);
        }

        void WaypointReached(uint32 waypointId)
        {
            switch (waypointId)
            {
                case 1:
                    me->HandleEmoteCommand(EMOTE_ONESHOT_KICK);
                    break;
                case 2:
                    me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK_UNARMED);
                    break;
                case 3:
                    me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK_UNARMED);
                    break;
                case 4:
                    me->HandleEmoteCommand(EMOTE_ONESHOT_KICK);
                    break;
                case 5:
                    me->HandleEmoteCommand(EMOTE_ONESHOT_KICK);
                    BreakKeg_Timer = 2000;
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (BreakKeg_Timer)
            {
                if (BreakKeg_Timer <= diff)
                {
                    DoGo(DATA_GO_BAR_KEG, 0);
                    BreakKeg_Timer = 0;
                    BreakDoor_Timer = 1000;
                } else BreakKeg_Timer -= diff;
            }

            if (BreakDoor_Timer)
            {
                if (BreakDoor_Timer <= diff)
                {
                    DoGo(DATA_GO_BAR_DOOR, 2);
                    DoGo(DATA_GO_BAR_KEG_TRAP, 0);               //doesn't work very well, leaving code here for future
                    //spell by trap has effect61, this indicate the bar go hostile

                    if (Unit* tmp = ObjectAccessor::GetUnit(*me, instance->GetData64(DATA_PHALANX)))
                        tmp->setFaction(14);

                    //for later, this event(s) has alot more to it.
                    //optionally, DONE can trigger bar to go hostile.
                    instance->SetData(TYPE_BAR, DONE);

                    BreakDoor_Timer = 0;
                } else BreakDoor_Timer -= diff;
            }

            npc_escortAI::UpdateAI(diff);
        }
    };
};

/*######
## COMMANDER GOR'SHAK
######*/
enum Gorshak
{
    NPC_FOOTMAN                             = 8892,
    NPC_GUARDSMAN                           = 8891,

    QUEST_WHATS_GOING_ON                    = 3982,

    EVENT_SECONDWAVE                        = 1,
    EVENT_WHAT_IS_GOING_ON_COMPLETE         = 2
};

Position const AddSpawnPos[4] =
{
    { 375.73f, -201.22f, -70.37f, 2.03f },
    { 379.39f, -199.37f, -69.68f, 1.87f },
    { 382.15f, -198.50f, -69.11f, 1.87f },
    { 377.89f, -195.24f, -70.12f, 1.90f }
};

class npc_commander_gorshak : public CreatureScript
{
public:
    npc_commander_gorshak() : CreatureScript("npc_commander_gorshak") { }

    struct npc_commander_gorshakAI : ScriptedAI
    {
        npc_commander_gorshakAI(Creature* creature) : ScriptedAI(creature), Summons(me) { }

        void Reset() override
        {
            me->setFaction(35);
            playerGUID = 0;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void StartEvent(uint64 GUID)
        {
            playerGUID = GUID;

            for (auto i = 0; i < 4; ++i)
                me->SummonCreature(NPC_FOOTMAN, AddSpawnPos[i], TEMPSUMMON_MANUAL_DESPAWN, 180000);

            events.ScheduleEvent(EVENT_SECONDWAVE, 20s);
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                player->FailQuest(QUEST_WHATS_GOING_ON);

            Summons.DespawnAll();
        }

        void JustSummoned(Creature* summoned) override
        {
            Summons.Summon(summoned);
            summoned->AI()->AttackStart(me);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SECONDWAVE:
                    {
                        for (auto i = 0; i < 4; ++i)
                            me->SummonCreature(NPC_GUARDSMAN, AddSpawnPos[i], TEMPSUMMON_MANUAL_DESPAWN, 180000);
                        events.ScheduleEvent(EVENT_WHAT_IS_GOING_ON_COMPLETE, 30s);
                        break;
                    }
                    case EVENT_WHAT_IS_GOING_ON_COMPLETE:
                    {
                        if (!me->IsAlive())
                            return;

                        if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                            player->GroupEventHappens(QUEST_WHATS_GOING_ON, me);

                        me->GetMotionMaster()->MoveTargetedHome();
                        me->DespawnOrUnsummon(40s);
                        me->setFaction(35);
                        break;
                    }
                }
            }
            DoMeleeAttackIfReady();
        }

        void JustReachedHome() override
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            ScriptedAI::JustReachedHome();
        }
    private:
        uint64 playerGUID;
        EventMap events;
        SummonList Summons;
    };

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest) override
    {
        if (quest->GetQuestId() == QUEST_WHATS_GOING_ON)
        {
            if (creature->GetAI())
            {
                CAST_AI(npc_commander_gorshak::npc_commander_gorshakAI, creature->AI())->StartEvent(player->GetGUID());
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                creature->setFaction(113);
            }
            return true;
        }
        return false;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_commander_gorshakAI(creature);
    }
};

void AddSC_blackrock_depths()
{
    new go_shadowforge_brazier();
    new at_ring_of_law();
    new npc_grimstone();
    new npc_kharan_mighthammer();
    new npc_lokhtos_darkbargainer();
    new npc_rocknot();
    new npc_commander_gorshak();
}
