#include "ScriptPCH.h"
#include "halls_of_reflection.h"
#include "MotionMaster.h"

enum Events
{
    EVENT_NONE,

    EVENT_PRE_INTRO_1,
    EVENT_PRE_INTRO_2,
    EVENT_PRE_INTRO_3,

    EVENT_START_INTRO,
    EVENT_SKIP_INTRO,

    EVENT_INTRO_A2_1,
    EVENT_INTRO_A2_2,
    EVENT_INTRO_A2_3,
    EVENT_INTRO_A2_4,
    EVENT_INTRO_A2_5,
    EVENT_INTRO_A2_6,
    EVENT_INTRO_A2_7,
    EVENT_INTRO_A2_8,
    EVENT_INTRO_A2_9,
    EVENT_INTRO_A2_10,
    EVENT_INTRO_A2_11,
    EVENT_INTRO_A2_12,
    EVENT_INTRO_A2_13,
    EVENT_INTRO_A2_14,
    EVENT_INTRO_A2_15,
    EVENT_INTRO_A2_16,
    EVENT_INTRO_A2_17,
    EVENT_INTRO_A2_18,
    EVENT_INTRO_A2_19,

    EVENT_INTRO_H2_1,
    EVENT_INTRO_H2_2,
    EVENT_INTRO_H2_3,
    EVENT_INTRO_H2_4,
    EVENT_INTRO_H2_5,
    EVENT_INTRO_H2_6,
    EVENT_INTRO_H2_7,
    EVENT_INTRO_H2_8,
    EVENT_INTRO_H2_9,
    EVENT_INTRO_H2_10,
    EVENT_INTRO_H2_11,
    EVENT_INTRO_H2_12,
    EVENT_INTRO_H2_13,
    EVENT_INTRO_H2_14,
    EVENT_INTRO_H2_15,

    EVENT_INTRO_LK_1,
    EVENT_INTRO_LK_1_2,
    EVENT_INTRO_LK_1_3,
    EVENT_INTRO_LK_2,
    EVENT_INTRO_LK_3,
    EVENT_INTRO_LK_4,
    EVENT_INTRO_LK_4_2,
    EVENT_INTRO_LK_4_3,
    EVENT_INTRO_LK_5,
    EVENT_INTRO_LK_5_2,
    EVENT_INTRO_LK_6,
    EVENT_INTRO_LK_7,
    EVENT_INTRO_LK_8,
    EVENT_INTRO_LK_9,

    EVENT_INTRO_END,
    EVENT_INTRO_END_SET,
};

class npc_hor_leader : public CreatureScript
{
public:
    npc_hor_leader() : CreatureScript("npc_hor_leader") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
            return true;

        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        bool canStart = true;
        if (InstanceScript* instance = creature->GetInstanceScript())
            if (uint32 bhd = instance->GetData(DATA_BATTERED_HILT))
                if ((bhd & BHSF_FINISHED) == 0)
                    canStart = false;

        if (canStart)
        {
            QuestStatus status = player->GetQuestStatus(creature->GetEntry() == NPC_SYLVANAS_PART1 ? QUEST_DELIVRANCE_FROM_THE_PIT_H2 : QUEST_DELIVRANCE_FROM_THE_PIT_A2);
            if (status == QUEST_STATUS_COMPLETE || status == QUEST_STATUS_REWARDED)
                player->ADD_GOSSIP_ITEM(0, "Can you remove the sword?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            // once last quest is completed, she offers this shortcut of the starting event
            status = player->GetQuestStatus(creature->GetEntry() == NPC_SYLVANAS_PART1 ? QUEST_WRATH_OF_THE_LICH_KING_H2 : QUEST_WRATH_OF_THE_LICH_KING_A2);
            if (status == QUEST_STATUS_COMPLETE || status == QUEST_STATUS_REWARDED)
            {
                if (creature->GetEntry() == NPC_SYLVANAS_PART1)
                    player->ADD_GOSSIP_ITEM(0, "Dark Lady, I think I hear Arthas coming. Whatever you're going to do, do it quickly.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                else
                    player->ADD_GOSSIP_ITEM(0, "My Lady, I think I hear Arthas coming. Whatever you're going to do, do it quickly.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            }
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        if (!creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
            return true;

        InstanceScript* instance = creature->GetInstanceScript();
        if (!instance)
            return true;

        if (uint32 bhd = instance->GetData(DATA_BATTERED_HILT))
            if ((bhd & BHSF_FINISHED) == 0)
                return true;

        instance->SetData(DATA_BATTERED_HILT, 1);

        player->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:
            player->CLOSE_GOSSIP_MENU();
            if (creature->AI())
                creature->AI()->DoAction(ACTION_START_INTRO);
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            player->CLOSE_GOSSIP_MENU();
            if (creature->AI())
                creature->AI()->DoAction(ACTION_SKIP_INTRO);
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
            break;
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hor_leaderAI(creature);
    }

    struct npc_hor_leaderAI : public NullCreatureAI
    {
        npc_hor_leaderAI(Creature* creature) : NullCreatureAI(creature)
        {
            pInstance = me->GetInstanceScript();
            if (!pInstance)
                me->IsAIEnabled = false;
            first = (pInstance && !pInstance->GetData(DATA_INTRO));
        }

        InstanceScript* pInstance;
        EventMap events;
        bool first;
        bool shortver;

        void Reset()
        {
            shortver = false;
            events.Reset();
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
            if (first)
            {
                first = false;
                events.ScheduleEvent(EVENT_PRE_INTRO_1, 10s);
                events.ScheduleEvent(EVENT_PRE_INTRO_2, 11s);
                events.ScheduleEvent(EVENT_PRE_INTRO_3, 17s);
            }
        }

        void DoAction(int32 actionId) override
        {
            switch (actionId)
            {
                case ACTION_START_INTRO:
                    events.ScheduleEvent(EVENT_START_INTRO, 0s);
                    break;
                case ACTION_SKIP_INTRO:
                    events.ScheduleEvent(EVENT_SKIP_INTRO, 0s);
                    break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);
            switch (events.ExecuteEvent())
            {
                case EVENT_PRE_INTRO_1:
                    if (pInstance)
                    {
                        me->SetVisible(true);
                        if (Creature* c = pInstance->instance->GetCreature(pInstance->GetData64(NPC_DARK_RANGER_LORALEN)))
                            c->SetVisible(true);
                    }
                    break;
                case EVENT_PRE_INTRO_2:
                    if (me->GetEntry() == NPC_JAINA_PART1)
                        Talk(SAY_JAINA_INTRO_1);
                    me->GetMotionMaster()->MovePoint(0, SpawnPos);
                    break;
                case EVENT_PRE_INTRO_3:
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    Talk(me->GetEntry() == NPC_JAINA_PART1 ? SAY_JAINA_INTRO_2 : SAY_SYLVANAS_INTRO_1);
                    me->SetFacingTo(0.89f);
                    break;
                case EVENT_START_INTRO:
                    shortver = false;
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                    me->GetMotionMaster()->MovePoint(0, MoveThronePos);
                    if (Creature* c = pInstance->instance->GetCreature(pInstance->GetData64(NPC_DARK_RANGER_LORALEN)))
                        c->GetMotionMaster()->MovePoint(0, LoralenFollowPos);
                    // Begining of intro is differents between factions as the speech sequence and timers are differents.
                    if (me->GetEntry() == NPC_JAINA_PART1)
                        events.ScheduleEvent(EVENT_INTRO_A2_1, 10s);
                    else
                        events.ScheduleEvent(EVENT_INTRO_H2_2, 10s);
                    break;
                case EVENT_SKIP_INTRO:
                    shortver = true;
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, (me->GetEntry() == NPC_JAINA_PART1 ? EMOTE_STATE_READY2H : EMOTE_STATE_READY1H));
                    me->GetMotionMaster()->MovePoint(0, MoveThronePos);
                    if (Creature* c = pInstance->instance->GetCreature(pInstance->GetData64(NPC_DARK_RANGER_LORALEN)))
                        c->GetMotionMaster()->MovePoint(0, LoralenFollowPos);
                    events.ScheduleEvent(EVENT_INTRO_LK_1, 0s);
                    break;

                    // A2 Intro Events
                case EVENT_INTRO_A2_1:
                    Talk(SAY_JAINA_INTRO_3);
                    events.ScheduleEvent(EVENT_INTRO_A2_2, 5s);
                    break;
                case EVENT_INTRO_A2_2:
                    Talk(SAY_JAINA_INTRO_4);
                    events.ScheduleEvent(EVENT_INTRO_A2_3, 10s);
                    break;
                case EVENT_INTRO_A2_3:
                    pInstance->HandleGameObject(pInstance->GetData64(GO_FROSTMOURNE), true);
                    me->CastSpell(me, SPELL_FROSTMOURNE_SPAWN_SOUND, true);
                    me->CastSpell(me, SPELL_ARCANE_CAST_VISUAL, false);
                    events.ScheduleEvent(EVENT_INTRO_A2_4, 10s);
                    break;
                case EVENT_INTRO_A2_4:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                    {
                        pUther->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                        pUther->SetVisible(true);
                        if (Aura* a = pUther->AddAura(SPELL_SHADOWMOURNE_VISUAL, pUther))
                            a->SetDuration(8000);
                    }
                    events.ScheduleEvent(EVENT_INTRO_A2_5, 2s);
                    break;
                case EVENT_INTRO_A2_5:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        pUther->AI()->Talk(SAY_UTHER_INTRO_A2_1);
                    events.ScheduleEvent(EVENT_INTRO_A2_6, 3s);
                    break;
                case EVENT_INTRO_A2_6:
                    Talk(SAY_JAINA_INTRO_5);
                    events.ScheduleEvent(EVENT_INTRO_A2_7, 6s);
                    break;
                case EVENT_INTRO_A2_7:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        pUther->AI()->Talk(SAY_UTHER_INTRO_A2_2);
                    events.ScheduleEvent(EVENT_INTRO_A2_8, 6.5s);
                    break;
                case EVENT_INTRO_A2_8:
                    Talk(SAY_JAINA_INTRO_6);
                    events.ScheduleEvent(EVENT_INTRO_A2_9, 2s);
                    break;
                case EVENT_INTRO_A2_9:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        pUther->AI()->Talk(SAY_UTHER_INTRO_A2_3);
                    events.ScheduleEvent(EVENT_INTRO_A2_10, 9s);
                    break;
                case EVENT_INTRO_A2_10:
                    Talk(SAY_JAINA_INTRO_7);
                    events.ScheduleEvent(EVENT_INTRO_A2_11, 5s);
                    break;
                case EVENT_INTRO_A2_11:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        pUther->AI()->Talk(SAY_UTHER_INTRO_A2_4);
                    events.ScheduleEvent(EVENT_INTRO_A2_12, 11s);
                    break;
                case EVENT_INTRO_A2_12:
                    Talk(SAY_JAINA_INTRO_8);
                    events.ScheduleEvent(EVENT_INTRO_A2_13, 4s);
                    break;
                case EVENT_INTRO_A2_13:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        pUther->AI()->Talk(SAY_UTHER_INTRO_A2_5);
                    events.ScheduleEvent(EVENT_INTRO_A2_14, 12.5s);
                    break;
                case EVENT_INTRO_A2_14:
                    Talk(SAY_JAINA_INTRO_9);
                    events.ScheduleEvent(EVENT_INTRO_A2_15, 10s);
                    break;
                case EVENT_INTRO_A2_15:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        pUther->AI()->Talk(SAY_UTHER_INTRO_A2_6);
                    events.ScheduleEvent(EVENT_INTRO_A2_16, 24s);
                    break;
                case EVENT_INTRO_A2_16:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        pUther->AI()->Talk(SAY_UTHER_INTRO_A2_7);
                    events.ScheduleEvent(EVENT_INTRO_A2_17, 4s);
                    break;
                case EVENT_INTRO_A2_17:
                    Talk(SAY_JAINA_INTRO_10);
                    events.ScheduleEvent(EVENT_INTRO_A2_18, 2s);
                    break;
                case EVENT_INTRO_A2_18:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                    {
                        pUther->HandleEmoteCommand(EMOTE_ONESHOT_NO);
                        pUther->AI()->Talk(SAY_UTHER_INTRO_A2_8);
                    }
                    events.ScheduleEvent(EVENT_INTRO_A2_19, 11s);
                    break;
                case EVENT_INTRO_A2_19:
                    Talk(SAY_JAINA_INTRO_11);
                    events.ScheduleEvent(EVENT_INTRO_LK_1, 2s);
                    break;

                    // H2 Intro Events
                case EVENT_INTRO_H2_2:
                    Talk(SAY_SYLVANAS_INTRO_2);
                    events.ScheduleEvent(EVENT_INTRO_H2_3, 6s);
                    break;
                case EVENT_INTRO_H2_3:
                    Talk(SAY_SYLVANAS_INTRO_3);
                    pInstance->HandleGameObject(pInstance->GetData64(GO_FROSTMOURNE), true);
                    me->CastSpell(me, SPELL_FROSTMOURNE_SPAWN_SOUND, true);
                    me->CastSpell(me, SPELL_ARCANE_CAST_VISUAL, false);
                    events.ScheduleEvent(EVENT_INTRO_H2_4, 6s);
                    break;
                case EVENT_INTRO_H2_4:
                    if (Creature* pUther = pInstance->instance->GetCreature(pInstance->GetData64(NPC_UTHER)))
                    {
                        pUther->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                        pUther->SetVisible(true);
                        if (Aura* a = pUther->AddAura(SPELL_SHADOWMOURNE_VISUAL, pUther))
                            a->SetDuration(8000);
                    }
                    events.ScheduleEvent(EVENT_INTRO_H2_5, 2s);
                    break;
                case EVENT_INTRO_H2_5:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        pUther->AI()->Talk(SAY_UTHER_INTRO_H2_1);
                    events.ScheduleEvent(EVENT_INTRO_H2_6, 11s);
                    break;
                case EVENT_INTRO_H2_6:
                    Talk(SAY_SYLVANAS_INTRO_4);
                    events.ScheduleEvent(EVENT_INTRO_H2_7, 3s);
                    break;
                case EVENT_INTRO_H2_7:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        pUther->AI()->Talk(SAY_UTHER_INTRO_H2_2);
                    events.ScheduleEvent(EVENT_INTRO_H2_8, 6s);
                    break;
                case EVENT_INTRO_H2_8:
                    Talk(SAY_SYLVANAS_INTRO_5);
                    events.ScheduleEvent(EVENT_INTRO_H2_9, 5s);
                    break;
                case EVENT_INTRO_H2_9:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        pUther->AI()->Talk(SAY_UTHER_INTRO_H2_3);
                    events.ScheduleEvent(EVENT_INTRO_H2_10, 19s);
                    break;
                case EVENT_INTRO_H2_10:
                    Talk(SAY_SYLVANAS_INTRO_6);
                    events.ScheduleEvent(EVENT_INTRO_H2_11, 1.5s);
                    break;
                case EVENT_INTRO_H2_11:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        pUther->AI()->Talk(SAY_UTHER_INTRO_H2_4);
                    events.ScheduleEvent(EVENT_INTRO_H2_12, 19.5s);
                    break;
                case EVENT_INTRO_H2_12:
                    Talk(SAY_SYLVANAS_INTRO_7);
                    events.ScheduleEvent(EVENT_INTRO_H2_13, 2s);
                    break;
                case EVENT_INTRO_H2_13:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                    {
                        pUther->HandleEmoteCommand(EMOTE_ONESHOT_NO);
                        pUther->AI()->Talk(SAY_UTHER_INTRO_H2_5);
                    }
                    events.ScheduleEvent(EVENT_INTRO_H2_14, 12s);
                    break;
                case EVENT_INTRO_H2_14:
                    if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        pUther->AI()->Talk(SAY_UTHER_INTRO_H2_6);
                    events.ScheduleEvent(EVENT_INTRO_H2_15, 8s);
                    break;
                case EVENT_INTRO_H2_15:
                    Talk(SAY_SYLVANAS_INTRO_8);
                    events.ScheduleEvent(EVENT_INTRO_LK_1, 2s);
                    break;

                    // Remaining Intro Events common for both faction
                case EVENT_INTRO_LK_1:
                    if (Creature* pLichKing = pInstance->instance->GetCreature(pInstance->GetData64(NPC_LICH_KING_EVENT)))
                    {
                        pInstance->HandleGameObject(pInstance->GetData64(GO_ARTHAS_DOOR), true);
                        pLichKing->SetVisible(true);
                        pLichKing->GetMotionMaster()->MovePoint(0, LichKingMoveThronePos, false);
                    }

                    if (!shortver)
                        if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                        {
                            if (me->GetEntry() == NPC_JAINA_PART1)
                                pUther->AI()->Talk(SAY_UTHER_INTRO_A2_9);
                            else
                                pUther->AI()->Talk(SAY_UTHER_INTRO_H2_7);
                        }

                    events.ScheduleEvent(EVENT_INTRO_LK_1_2, 2s);
                    events.ScheduleEvent(EVENT_INTRO_LK_1_3, 4s);
                    events.ScheduleEvent(EVENT_INTRO_LK_2, 11s);
                    break;

                case EVENT_INTRO_LK_1_2:
                    if (!shortver)
                        if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                            pUther->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_COWER);
                    break;

                case EVENT_INTRO_LK_1_3:
                    pInstance->HandleGameObject(pInstance->GetData64(GO_ARTHAS_DOOR), false);
                    break;

                case EVENT_INTRO_LK_2:
                    if (!shortver)
                        if (Creature* pLichKing = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_LICH_KING_EVENT)))
                            pLichKing->AI()->Talk(SAY_LK_INTRO_1);
                    events.ScheduleEvent(EVENT_INTRO_LK_3, 2s);
                    break;

                case EVENT_INTRO_LK_3:
                    if (!shortver)
                        if (Creature* pUther = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_UTHER)))
                            pUther->SetVisible(false);
                    events.ScheduleEvent(EVENT_INTRO_LK_4, 4s);
                    break;

                case EVENT_INTRO_LK_4:
                    if (Creature* pLichKing = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_LICH_KING_EVENT)))
                        pLichKing->AI()->Talk(SAY_LK_INTRO_2);
                    events.ScheduleEvent(EVENT_INTRO_LK_4_2, 10s);
                    break;

                case EVENT_INTRO_LK_4_2:
                    if (Creature* pLichKing = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_LICH_KING_EVENT)))
                    {
                        pLichKing->LoadEquipment(1, true);
                        pLichKing->SendMovementFlagUpdate();
                        pLichKing->CastSpell(pLichKing, SPELL_FROSTMOURNE_EQUIP, false);
                        pInstance->HandleGameObject(pInstance->GetData64(GO_FROSTMOURNE), false);
                        events.ScheduleEvent(EVENT_INTRO_LK_4_3, 1.75s);
                    }
                    events.ScheduleEvent(EVENT_INTRO_LK_5, 6s);
                    break;

                case EVENT_INTRO_LK_4_3:
                    if (GameObject* go = pInstance->instance->GetGameObject(pInstance->GetData64(GO_FROSTMOURNE)))
                        go->SetPhaseMask(2, true);
                    break;
                case EVENT_INTRO_LK_5:
                    if (Creature* pFalric = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_FALRIC)))
                    {
                        pFalric->UpdatePosition(5274.9f, 2039.2f, 709.319f, 5.4619f, true);
                        pFalric->StopMovingOnCurrentPos();
                        pFalric->SetVisible(true);
                        if (pFalric->IsAlive())
                        {
                            pFalric->GetMotionMaster()->MovePoint(0, FalricMovePos);
                            if (Aura* a = pFalric->AddAura(SPELL_SHADOWMOURNE_VISUAL, pFalric))
                                a->SetDuration(8000);
                        }
                    }
                    if (Creature* pMarwyn = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_MARWYN)))
                    {
                        pMarwyn->UpdatePosition(5343.77f, 1973.86f, 709.319f, 2.35173f, true);
                        pMarwyn->StopMovingOnCurrentPos();
                        pMarwyn->SetVisible(true);
                        if (pMarwyn->IsAlive())
                        {
                            pMarwyn->GetMotionMaster()->MovePoint(0, MarwynMovePos);
                            if (Aura* a = pMarwyn->AddAura(SPELL_SHADOWMOURNE_VISUAL, pMarwyn))
                                a->SetDuration(8000);
                        }
                    }

                    if (Creature* pLichKing = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_LICH_KING_EVENT)))
                        pLichKing->AI()->Talk(SAY_LK_INTRO_3);

                    events.ScheduleEvent(EVENT_INTRO_LK_5_2, 5s);
                    events.ScheduleEvent(EVENT_INTRO_LK_6, 8s);
                    break;

                case EVENT_INTRO_LK_5_2:
                    if (Creature* pLichKing = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_LICH_KING_EVENT)))
                        pLichKing->GetMotionMaster()->MovePoint(0, LichKingMoveAwayPos, false);
                    break;

                case EVENT_INTRO_LK_6:
                    if (Creature* pFalric = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_FALRIC)))
                        pFalric->AI()->Talk(SAY_FALRIC_INTRO_1);

                    events.ScheduleEvent(EVENT_INTRO_LK_7, 2s);
                    break;

                case EVENT_INTRO_LK_7:
                    if (Creature* pMarwyn = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_MARWYN)))
                        pMarwyn->AI()->Talk(SAY_MARWYN_INTRO_1);

                    events.ScheduleEvent(EVENT_INTRO_LK_8, 2s);
                    break;

                case EVENT_INTRO_LK_8:
                    if (Creature* pFalric = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_FALRIC)))
                        pFalric->AI()->Talk(SAY_FALRIC_INTRO_2);
                    pInstance->SetData(ACTION_SHOW_TRASH, 1);

                    pInstance->HandleGameObject(pInstance->GetData64(GO_ARTHAS_DOOR), true);

                    events.ScheduleEvent(EVENT_INTRO_LK_9, 5s);
                    break;

                case EVENT_INTRO_LK_9:
                    if (me->GetEntry() == NPC_JAINA_PART1)
                        Talk(SAY_JAINA_INTRO_END);
                    else
                        Talk(SAY_SYLVANAS_INTRO_END);

                    me->GetMotionMaster()->MovePoint(0, LichKingMoveAwayPos, false);
                    if (Creature* c = pInstance->instance->GetCreature(pInstance->GetData64(NPC_DARK_RANGER_LORALEN)))
                        c->GetMotionMaster()->MovePoint(0, LichKingMoveAwayPos, false);
                    events.ScheduleEvent(EVENT_INTRO_END, 14s);
                    break;
                case EVENT_INTRO_END:
                    pInstance->HandleGameObject(pInstance->GetData64(GO_ARTHAS_DOOR), false);
                    pInstance->HandleGameObject(pInstance->GetData64(GO_FRONT_DOOR), false);
                    events.ScheduleEvent(EVENT_INTRO_END_SET, 10s);
                    break;
                case EVENT_INTRO_END_SET:
                    if (Creature* pLichKing = ObjectAccessor::GetCreature(*me, pInstance->GetData64(NPC_LICH_KING_EVENT)))
                        pLichKing->SetVisible(false);
                    if (Creature* c = pInstance->instance->GetCreature(pInstance->GetData64(NPC_DARK_RANGER_LORALEN)))
                        c->SetVisible(false);
                    me->SetVisible(false);
                    pInstance->SetData(DATA_INTRO, DONE);
                    break;
                default:
                    break;
            }
        }
    };
};

enum TrashSpells
{
    // Ghostly Priest
    SPELL_SHADOW_WORD_PAIN          = 72318,
    SPELL_CIRCLE_OF_DESTRUCTION     = 72320,
    SPELL_COWER_IN_FEAR             = 72321,
    SPELL_DARK_MENDING              = 72322,

    // Phantom Mage
    SPELL_FIREBALL                  = 72163,
    SPELL_FLAMESTRIKE               = 72169,
    SPELL_FROSTBOLT                 = 72166,
    SPELL_CHAINS_OF_ICE             = 72120,
    SPELL_HALLUCINATION             = 72342,

    // Phantom Hallucination (same as phantom mage + HALLUCINATION_2 when dies)
    SPELL_HALLUCINATION_2           = 72344,

    // Shadowy Mercenary
    SPELL_SHADOW_STEP               = 72326,
    SPELL_DEADLY_POISON             = 72329,
    SPELL_ENVENOMED_DAGGER_THROW    = 72333,
    SPELL_KIDNEY_SHOT               = 72335,

    // Spectral Footman
    SPELL_SPECTRAL_STRIKE           = 72198,
    SPELL_SHIELD_BASH               = 72194,
    SPELL_TORTURED_ENRAGE           = 72203,

    // Tortured Rifleman
    SPELL_SHOOT                     = 72208,
    SPELL_CURSED_ARROW              = 72222,
    SPELL_FROST_TRAP                = 72215,
    SPELL_ICE_SHOT                  = 72268
};

enum TrashEvents
{
    EVENT_TRASH_NONE,

    // Ghostly Priest
    EVENT_SHADOW_WORD_PAIN,
    EVENT_CIRCLE_OF_DESTRUCTION,
    EVENT_COWER_IN_FEAR,
    EVENT_DARK_MENDING,

    // Phantom Mage
    EVENT_FIREBALL,
    EVENT_FLAMESTRIKE,
    EVENT_FROSTBOLT,
    EVENT_CHAINS_OF_ICE,
    EVENT_HALLUCINATION,

    // Shadowy Mercenary
    EVENT_SHADOW_STEP,
    EVENT_DEADLY_POISON,
    EVENT_ENVENOMED_DAGGER_THROW,
    EVENT_KIDNEY_SHOT,

    // Spectral Footman
    EVENT_SPECTRAL_STRIKE,
    EVENT_SHIELD_BASH,
    EVENT_TORTURED_ENRAGE,

    // Tortured Rifleman
    EVENT_SHOOT,
    EVENT_CURSED_ARROW,
    EVENT_FROST_TRAP,
    EVENT_ICE_SHOT,
};

struct npc_hor_waves_trashAI : public ScriptedAI
{
    npc_hor_waves_trashAI(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        _events.Reset();
    }

    void AttackStart(Unit* who) override
    {
        if (!me->IsVisible() || me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
            return;

        ScriptedAI::AttackStart(who);
    }

    void EnterEvadeMode() override
    {
        ScriptedAI::EnterEvadeMode();
        if (me->GetInstanceScript()->GetData(DATA_WAVE_NUMBER))
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);
    }

    void DoAction(int32 actionId) override
    {
        if (actionId != 1)
            return;

        me->SetInCombatWithZone();
        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
            AttackStart(target);
    }

    virtual void DoEvent(uint32 eventId) = 0;

    bool StateCheck()
    {
        return me->HasUnitState(UNIT_STATE_CASTING) || me->isFeared() || me->IsCharmed() || me->isFrozen() || me->HasUnitState(UNIT_STATE_STUNNED) || me->HasUnitState(UNIT_STATE_CONFUSED);
    }

    void UpdateAI(uint32 diff)
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (StateCheck())
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            DoEvent(eventId);
            if (StateCheck())
                return;
        }

        if (me->GetEntry() == 38176)
            DoSpellAttackIfReady(SPELL_SHOOT);
        else
            DoMeleeAttackIfReady();
    }

protected:
    EventMap _events;
};

struct npc_ghostly_priestAI : public npc_hor_waves_trashAI
{
    npc_ghostly_priestAI(Creature* creature) : npc_hor_waves_trashAI(creature) { }

    void EnterCombat(Unit* /*who*/) override
    {
        _events.ScheduleEvent(EVENT_SHADOW_WORD_PAIN, 5s);
        _events.ScheduleEvent(EVENT_CIRCLE_OF_DESTRUCTION, 8s);
        _events.ScheduleEvent(EVENT_COWER_IN_FEAR, 10s);
        _events.ScheduleEvent(EVENT_DARK_MENDING, 8s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case EVENT_SHADOW_WORD_PAIN:
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true, -SPELL_SHADOW_WORD_PAIN))
                DoCast(target, SPELL_SHADOW_WORD_PAIN);
            _events.Repeat(5s);
            break;
        case EVENT_CIRCLE_OF_DESTRUCTION:
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 10.0f, true))
                DoCast(target, SPELL_CIRCLE_OF_DESTRUCTION);
            _events.Repeat(12s);
            break;
        case EVENT_COWER_IN_FEAR:
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 20.0f, true, -SPELL_COWER_IN_FEAR))
                DoCast(target, SPELL_COWER_IN_FEAR);
            _events.Repeat(10s);
            break;
        case EVENT_DARK_MENDING:
            if (Unit* target = DoSelectLowestHpFriendly(35.0f, DUNGEON_MODE(20000, 35000)))
            {
                DoCast(target, SPELL_DARK_MENDING);
                _events.Repeat(6s);
            }
            else
                _events.Repeat(3s);
            break;
        default:
            break;
        }
    }
};

struct npc_phantom_mageAI : public npc_hor_waves_trashAI
{
    npc_phantom_mageAI(Creature* creature) : npc_hor_waves_trashAI(creature) { }

    void EnterCombat(Unit* /*who*/) override
    {
        _events.ScheduleEvent(EVENT_FIREBALL, 3s);
        _events.ScheduleEvent(EVENT_FLAMESTRIKE, 6s);
        _events.ScheduleEvent(EVENT_FROSTBOLT, 9s);
        _events.ScheduleEvent(EVENT_CHAINS_OF_ICE, 12s);
        _events.ScheduleEvent(EVENT_HALLUCINATION, 40s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_FIREBALL:
                DoCastVictim(SPELL_FIREBALL);
                _events.Repeat(6s);
                break;
            case EVENT_FLAMESTRIKE:
                DoCastVictim(SPELL_FLAMESTRIKE);
                _events.Repeat(15s);
                break;
            case EVENT_FROSTBOLT:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                    DoCast(target, SPELL_FROSTBOLT);
                _events.Repeat(9s);
                break;
            case EVENT_CHAINS_OF_ICE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true, -SPELL_CHAINS_OF_ICE))
                    DoCast(target, SPELL_CHAINS_OF_ICE);
                _events.Repeat(12s);
                break;
            case EVENT_HALLUCINATION:
                DoCastSelf(SPELL_HALLUCINATION);
                break;
            default:
                break;
        }
    }
};

struct npc_phantom_hallucinationAI : public npc_phantom_mageAI
{
    npc_phantom_hallucinationAI(Creature* creature) : npc_phantom_mageAI(creature)
    {
        _updateAmount = 2;
    }

    void JustDied(Unit* /*who*/) override
    {
        DoCastAOE(SPELL_HALLUCINATION_2);
    }

    void UpdateAI(uint32 diff) override
    {
        if (_updateAmount)
        {
            if (--_updateAmount == 0)
                me->SetInCombatWithZone();
            return;
        }

        npc_phantom_mageAI::UpdateAI(diff);
    }

    void EnterEvadeMode() override
    {
        if (_updateAmount)
            return;

        ScriptedAI::EnterEvadeMode();
        if (me->IsSummon())
            me->ToTempSummon()->DespawnOrUnsummon(1);
    }

    private:
        uint8 _updateAmount;
};

struct npc_shadowy_mercenaryAI : public npc_hor_waves_trashAI
{
    npc_shadowy_mercenaryAI(Creature* creature) : npc_hor_waves_trashAI(creature) { }

    void EnterCombat(Unit* /*who*/) override
    {
        _events.ScheduleEvent(EVENT_SHADOW_STEP, 4s);
        _events.ScheduleEvent(EVENT_DEADLY_POISON, 6s);
        _events.ScheduleEvent(EVENT_ENVENOMED_DAGGER_THROW, 10s);
        _events.ScheduleEvent(EVENT_KIDNEY_SHOT, 5s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_SHADOW_STEP:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                {
                    DoResetThreat();
                    me->AddThreat(target, 5000.0f);
                    AttackStart(target);
                    DoCast(target, SPELL_SHADOW_STEP);
                }
                _events.Repeat(20s);
                break;
            case EVENT_DEADLY_POISON:
                DoCastVictim(SPELL_DEADLY_POISON);
                _events.Repeat(4s);
                break;
            case EVENT_ENVENOMED_DAGGER_THROW:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true, -SPELL_ENVENOMED_DAGGER_THROW))
                    DoCast(target, SPELL_ENVENOMED_DAGGER_THROW);
                _events.Repeat(10s);
                break;
            case EVENT_KIDNEY_SHOT:
                DoCastVictim(SPELL_KIDNEY_SHOT);
                _events.Repeat(10s);
                break;
            default:
                break;
        }
    }
};

struct npc_spectral_footmanAI : public npc_hor_waves_trashAI
{
    npc_spectral_footmanAI(Creature* creature) : npc_hor_waves_trashAI(creature) {}

    void EnterCombat(Unit* /*who*/) override
    {
        _events.ScheduleEvent(EVENT_SPECTRAL_STRIKE, 5s);
        _events.ScheduleEvent(EVENT_SHIELD_BASH, 6s);
        _events.ScheduleEvent(EVENT_TORTURED_ENRAGE, 15s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_SPECTRAL_STRIKE:
                DoCastVictim(SPELL_SPECTRAL_STRIKE);
                _events.Repeat(5s);
                break;
            case EVENT_SHIELD_BASH:
                DoCastVictim(SPELL_SHIELD_BASH);
                _events.Repeat(6s);
                break;
            case EVENT_TORTURED_ENRAGE:
                DoCastSelf(SPELL_TORTURED_ENRAGE);
                _events.Repeat(15s);
                break;
            default:
                break;
        }
    }
};

struct npc_tortured_riflemanAI : public npc_hor_waves_trashAI
{
    npc_tortured_riflemanAI(Creature* creature) : npc_hor_waves_trashAI(creature) {}

    void EnterCombat(Unit* /*who*/) override
    {
        _events.ScheduleEvent(EVENT_CURSED_ARROW, 10s);
        _events.ScheduleEvent(EVENT_FROST_TRAP, 15s);
        _events.ScheduleEvent(EVENT_ICE_SHOT, 15s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CURSED_ARROW:
                DoCastVictim(SPELL_CURSED_ARROW);
                _events.Repeat(10s);
                break;
            case EVENT_FROST_TRAP:
                DoCastAOE(SPELL_FROST_TRAP);
                _events.Repeat(30s);
                break;
            case EVENT_ICE_SHOT:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                    DoCast(target, SPELL_ICE_SHOT);
                _events.Repeat(8s);
                break;
            default:
                break;
        }
    }
};

struct boss_frostsworn_generalAI : public ScriptedAI
{
    boss_frostsworn_generalAI(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
    }

    void Reset() override
    {
        _events.Reset();
    }

    void EnterCombat(Unit* /*who*/) override
    {
        Talk(SAY_FROSTSWORN_GENERAL_AGGRO);
        _events.ScheduleEvent(EVENT_ACTIVATE_REFLECTIONS, 8s);
        _events.ScheduleEvent(EVENT_THROW_SHIELD, 6s);
        _instance->SetData(ACTION_SPIRITUAL_REFLECTIONS_COPY, 1);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        Position p = me->GetHomePosition();
        if (me->GetExactDist(&p) > 30.0f)
        {
            EnterEvadeMode();
            return;
        }

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_ACTIVATE_REFLECTIONS:
                    DoCastAOE(SPELL_SUMMON_REFLECTIONS_DUMMY);
                    _instance->SetData(ACTION_SPIRITUAL_REFLECTIONS_ACTIVATE, 1);
                    break;
                case EVENT_THROW_SHIELD:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_THROW_SHIELD);
                    _events.Repeat(10s);
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_FROSTSWORN_GENERAL_DEATH);
        if (_instance)
            _instance->SetData(DATA_FROSTSWORN_GENERAL, DONE);
    }

    void EnterEvadeMode() override
    {
        _instance->SetData(ACTION_SPIRITUAL_REFLECTIONS_HIDE, 1);
        ScriptedAI::EnterEvadeMode();
    }

    private:
        InstanceScript* _instance;
        EventMap _events;
};

struct npc_hor_spiritual_reflectionAI : public ScriptedAI
{
    npc_hor_spiritual_reflectionAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _events.Reset();
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _events.ScheduleEvent(EVENT_BALEFUL_STRIKE, 4s, 7s);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (_events.ExecuteEvent() == EVENT_BALEFUL_STRIKE)
        {
            DoCastVictim(SPELL_BALEFUL_STRIKE);
            _events.Repeat(4s, 7s);
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        DoCastAOE(SPELL_SPIRIT_BURST);
    }

    void EnterEvadeMode() override
    {
        me->UpdatePosition(me->GetHomePosition(), true);
        ScriptedAI::EnterEvadeMode();
        me->SetVisible(false);
    }

    private:
        EventMap _events;
};

class at_hor_shadow_throne : public AreaTriggerScript
{
    public:
        at_hor_shadow_throne() : AreaTriggerScript("at_hor_shadow_throne") { }

        bool OnTrigger(Player* player, const AreaTriggerEntry* /*at*/)
        {
            if (player->IsGameMaster())
                return false;

            InstanceScript* inst = player->GetInstanceScript();
            if (!inst)
                return false;

            if (inst->GetData(DATA_FROSTSWORN_GENERAL) && !inst->GetData(DATA_LK_INTRO))
                inst->SetData(DATA_LK_INTRO, DONE);

            return false;
        }
};

enum eFightEvents
{
    EVENT_EMPTY = 0,
    EVENT_LK_SAY_AGGRO,
    EVENT_JAINA_IMMOBILIZE_LK,
    EVENT_SYLVANAS_IMMOBILIZE_JUMP,
    EVENT_SYLVANAS_DARK_BINDING,
    EVENT_SAY_LEAVE,
    EVENT_ADD_GOSSIP,
    EVENT_START_RUN,
    EVENT_LK_START_FOLLOWING,
    EVENT_SAY_LEADER_STOP_TEXT,
    EVENT_LK_REMORSELESS_WINTER,
    EVENT_LK_CHECK_COMBAT,
    EVENT_LK_KILL_LEADER,
    EVENT_LK_SUMMON,
    EVENT_LK_SUMMON_GHOULS,
    EVENT_LK_SUMMON_RWD,
    EVENT_LK_SUMMON_LA,
    EVENT_LK_SUMMON_NEXT_ICE_WALL,
    EVENT_SAY_OPENING,
    EVENT_DECREASE_REQ_COUNT_BY_100,
};

struct npc_hor_lich_kingAI : public NullCreatureAI
{
    npc_hor_lich_kingAI(Creature* creature) : NullCreatureAI(creature), _summons(me)
    {
        _instance = me->GetInstanceScript();
        if (!_instance)
            me->IsAIEnabled = false;
    }

    InstanceScript* _instance;
    EventMap _events;
    SummonList _summons;
    uint8 _currentWall;
    uint8 _reqKillCount;
    uint8 _div2;

    void Reset() override
    {
        _currentWall = 0;
        _reqKillCount = 0;
        _events.Reset();
        _events.RescheduleEvent(EVENT_LK_CHECK_COMBAT, 1s);
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_START_LK_FIGHT_REAL)
            _events.ScheduleEvent(EVENT_LK_START_FOLLOWING, 1.5s);
        else if ((actionId == ACTION_INFORM_TRASH_DIED && _reqKillCount) || actionId == ACTION_CHECK_TRASH_DIED)
        {
            if ((actionId == ACTION_CHECK_TRASH_DIED && _reqKillCount == 0) || (actionId == ACTION_INFORM_TRASH_DIED && (--_reqKillCount) == 0))
            {
                _events.CancelEvent(EVENT_DECREASE_REQ_COUNT_BY_100); // just in case, magic happens sometimes
                ++_currentWall;
                _instance->SetData(ACTION_DELETE_ICE_WALL, 1);
                if (_currentWall <= 3)
                {
                    _events.ScheduleEvent(EVENT_LK_SUMMON_NEXT_ICE_WALL, 1s);
                    _events.ScheduleEvent(EVENT_LK_SUMMON, _currentWall == 3 ? 11.0s : 7.5s);
                }
                else
                {
                    me->RemoveAura(SPELL_REMORSELESS_WINTER);
                    me->SetSpeed(MOVE_RUN, me->GetCreatureTemplate()->speed_run * 2.0f);
                }

                if (Creature* leader = _instance->instance->GetCreature(_instance->GetData64(NPC_SYLVANAS_PART2)))
                    if (leader->IsAIEnabled)
                        leader->AI()->DoAction(ACTION_INFORM_WALL_DESTROYED);
            }
        }
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        // Xinef: dont use 0, it is no longer the last point
        // Xinef: if type is escort and spline is finalized, it means that we reached last point from the path
        if (type == ESCORT_MOTION_TYPE && me->movespline->Finalized())
        {
            if (_currentWall == 0)
            {
                Talk(SAY_LK_IW_1);
                me->SetOrientation(4.15f);
                if (Creature* iceWallTarget = _instance->instance->GetCreature(_instance->GetData64(NPC_ICE_WALL_TARGET)))
                {
                    DoCast(iceWallTarget, SPELL_SUMMON_ICE_WALL);
                    _events.ScheduleEvent(EVENT_LK_REMORSELESS_WINTER, 4s);
                }
            }
            else if (_currentWall == 4)
            {
                Talk(SAY_LK_NOWHERE_TO_RUN);
                _instance->SetData(DATA_LICH_KING, DONE);
            }
        }
    }

    void JustSummoned(Creature* summon) override
    {
        ++_reqKillCount;
        if (_events.GetNextEventTime(EVENT_DECREASE_REQ_COUNT_BY_100))
            _events.RescheduleEvent(EVENT_DECREASE_REQ_COUNT_BY_100, 10s);
        _summons.Summon(summon);
        summon->SetHomePosition(PathWaypoints[WP_STOP[_currentWall + 1]]);
        summon->GetMotionMaster()->MovePoint(0, PathWaypoints[WP_STOP[_currentWall + 1]]);
        summon->SetInCombatWithZone();
        if (Unit* target = summon->SelectNearestPlayer(350.0f))
        {
            summon->AddThreat(target, 1000.0f);
            if (summon->IsAIEnabled)
                summon->AI()->AttackStart(target);
        }
        summon->SetHomePosition(PathWaypoints[WP_STOP[_currentWall + 1]]);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        _summons.Despawn(summon);
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spell) override
    {
        if (target && target->IsAlive() && spell->Id == SPELL_LICH_KING_ZAP_PLAYER)
            Unit::DealDamage(me, target, 10000);
    }

    void UpdateAI(uint32 diff) override
    {
        if (me->HealthBelowPct(70))
            me->SetHealth(me->GetMaxHealth() * 3 / 4);

        _events.Update(diff);

        if (me->IsNonMeleeSpellCast(false, true, true))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_LK_CHECK_COMBAT:
                    if (me->isActiveObject()) // during fight
                    {
                        if (Creature* leader = _instance->instance->GetCreature(_instance->GetData64(NPC_SYLVANAS_PART2)))
                            if (leader->IsAlive() && leader->GetPositionX() < 5575.0f && me->GetExactDist2d(leader) <= 12.5f && !leader->HasAura(SPELL_HARVEST_SOUL) && me->HasAura(SPELL_REMORSELESS_WINTER))
                            {
                                me->GetMotionMaster()->MovementExpired();
                                me->StopMoving();
                                _reqKillCount = 255;
                                leader->InterruptNonMeleeSpells(true);
                                DoCast(leader, SPELL_HARVEST_SOUL);
                                _events.ScheduleEvent(EVENT_LK_KILL_LEADER, 3s);
                                _events.ScheduleEvent(EVENT_LK_CHECK_COMBAT, 1s);
                                break;
                            }
                        if (_instance->instance->HavePlayers())
                        {
                            me->SetInCombatWithZone();
                            ++_div2;
                            if (_div2 > 1)
                            {
                                _div2 = 0;
                                if (me->HasAura(SPELL_REMORSELESS_WINTER)) // prevent going behind him during fight
                                {
                                    auto const& players = _instance->instance->GetPlayers();
                                    for (auto itr = players.begin(); itr != players.end(); ++itr)
                                        if (Player* player = itr->GetSource())
                                            if (!player->IsGameMaster() && player->IsAlive() && (player->GetPositionX() - me->GetPositionX() + player->GetPositionY() - me->GetPositionY()) > 20.0f)
                                                me->CastSpell(player, SPELL_LICH_KING_ZAP_PLAYER, true);
                                }
                            }
                        }
                        else
                        {
                            _summons.DespawnAll();
                            _instance->SetData(ACTION_STOP_LK_FIGHT, 1);
                        }
                    }
                    _events.ScheduleEvent(EVENT_LK_CHECK_COMBAT, 1s);
                    break;
                case EVENT_LK_KILL_LEADER:
                    if (Creature* leader = _instance->instance->GetCreature(_instance->GetData64(NPC_SYLVANAS_PART2)))
                    {
                        leader->CastSpell(leader, SPELL_HOR_SUICIDE, true);
                        Unit::Kill(me, leader);
                        me->InterruptNonMeleeSpells(true);
                        DoCastAOE(SPELL_FURY_OF_FROSTMOURNE);
                    }
                    break;
                case EVENT_LK_START_FOLLOWING:
                {
                    me->SetSpeed(MOVE_RUN, 9.0f / 7.0f);
                    Movement::PointsArray path;
                    path.push_back(G3D::Vector3(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()));
                    for (uint8 i = 0; i <= 2; ++i)
                        path.push_back(G3D::Vector3(PathWaypoints[i].GetPositionX(), PathWaypoints[i].GetPositionY(), PathWaypoints[i].GetPositionZ()));
                    me->GetMotionMaster()->MoveSplinePath(&path);
                    break;
                }
                case EVENT_LK_REMORSELESS_WINTER:
                {
                    me->SetSpeed(MOVE_RUN, me->GetCreatureTemplate()->speed_run);
                    Talk(SAY_LK_IW_1_SUMMON);
                    DoCastSelf(SPELL_REMORSELESS_WINTER, true);
                    Movement::PointsArray path;
                    path.push_back(G3D::Vector3(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()));
                    for (uint8 i = 3; i<PATH_WP_COUNT - 1; ++i)
                        path.push_back(G3D::Vector3(PathWaypoints[i].GetPositionX(), PathWaypoints[i].GetPositionY(), PathWaypoints[i].GetPositionZ()));
                    me->GetMotionMaster()->MoveSplinePath(&path);
                    me->GetMotionMaster()->propagateSpeedChange();
                    _events.ScheduleEvent(EVENT_LK_SUMMON, 1s);
                    break;
                }
                case EVENT_LK_SUMMON:
                    switch (_currentWall)
                    {
                    case 0:
                        _events.ScheduleEvent(EVENT_LK_SUMMON_GHOULS, 0s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_RWD, 4s);
                        break;
                    case 1:
                        _events.ScheduleEvent(EVENT_LK_SUMMON_LA, 0s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_GHOULS, 100ms);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_RWD, 4s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_RWD, 5.1s);
                        break;
                    case 2:
                        _events.ScheduleEvent(EVENT_LK_SUMMON_LA, 0s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_GHOULS, 100ms);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_LA, 4s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_RWD, 4.1s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_RWD, 5.2s);
                        break;
                    case 3:
                        _events.ScheduleEvent(EVENT_LK_SUMMON_LA, 0s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_RWD, 100ms);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_GHOULS, 1.2s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_RWD, 5.3s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_RWD, 6.4s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_GHOULS, 12.5s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_LA, 16.5s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_RWD, 16.6s);
                        _events.ScheduleEvent(EVENT_LK_SUMMON_LA, 17.7s);
                        break;
                    }
                    if (_currentWall <= 3)
                    {
                        _reqKillCount = 100;
                        _events.RescheduleEvent(EVENT_DECREASE_REQ_COUNT_BY_100, 10s);
                    }
                    break;
                case EVENT_DECREASE_REQ_COUNT_BY_100:
                    _reqKillCount = (_reqKillCount <= 100 ? 0 : _reqKillCount - 100);
                    DoAction(ACTION_CHECK_TRASH_DIED);
                    break;
                case EVENT_LK_SUMMON_GHOULS:
                    DoCastAOE(SPELL_SUMMON_RAGING_GHOULS);
                    break;
                case EVENT_LK_SUMMON_RWD:
                    DoCastAOE(SPELL_SUMMON_RISEN_WITCH_DOCTOR);
                    break;
                case EVENT_LK_SUMMON_LA:
                    DoCastAOE(SPELL_SUMMON_LUMBERING_ABOMINATION);
                    break;
                case EVENT_LK_SUMMON_NEXT_ICE_WALL:
                    Talk(SAY_LK_IW_1 + _currentWall);
                    if (Creature* iceWallTarget = _instance->instance->GetCreature(_instance->GetData64(NPC_ICE_WALL_TARGET + _currentWall)))
                        DoCast(iceWallTarget, SPELL_SUMMON_ICE_WALL);
                    break;
            }

            if (me->IsNonMeleeSpellCast(false, true, true))
                return;
        }
    }
};

class npc_hor_leader_second : public CreatureScript
{
public:
    npc_hor_leader_second() : CreatureScript("npc_hor_leader_second") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 /*actionId*/) override
    {
        if (!creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
            return true;

        player->PlayerTalkClass->ClearMenus();

        if (InstanceScript* instance = creature->GetInstanceScript())
            if (!instance->GetData(DATA_LICH_KING))
            {
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                if (creature->IsAIEnabled)
                    creature->AI()->DoAction(ACTION_START_LK_FIGHT_REAL);
                return true;
            }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hor_leader_secondAI(creature);
    }

    struct npc_hor_leader_secondAI : public NullCreatureAI
    {
        npc_hor_leader_secondAI(Creature* creature) : NullCreatureAI(creature)
        {
            _instance = me->GetInstanceScript();
            if (!_instance)
                me->IsAIEnabled = false;
        }

        void Reset() override
        {
            _currentPoint = 0;
            _events.Reset();
        }

        void DoAction(int32 actionId) override
        {
            switch (actionId)
            {
            case ACTION_START_INTRO:
                _events.ScheduleEvent(EVENT_LK_SAY_AGGRO, 0s);
                break;
            case ACTION_START_LK_FIGHT_REAL:
                _events.ScheduleEvent(EVENT_START_RUN, 0s);
                break;
            case ACTION_INFORM_WALL_DESTROYED:
                MoveToNextStopPoint();
                if (_currentPoint == 5)
                    _events.ScheduleEvent(EVENT_SAY_OPENING, 3s);
                break;
            }
        }

        void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override
        {
            if (damage >= me->GetHealth())
                damage = me->GetHealth() - 1;
        }

        void MoveToNextStopPoint()
        {
            me->InterruptNonMeleeSpells(true);
            ++_currentPoint;
            Movement::PointsArray path;
            path.push_back(G3D::Vector3(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()));
            for (uint8 i = WP_STOP[_currentPoint - 1] + (_currentPoint == 1 ? 0 : 1); i <= WP_STOP[_currentPoint]; ++i)
                path.push_back(G3D::Vector3(PathWaypoints[i].GetPositionX(), PathWaypoints[i].GetPositionY(), PathWaypoints[i].GetPositionZ()));
            me->GetMotionMaster()->MoveSplinePath(&path);
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == ESCORT_MOTION_TYPE && me->movespline->Finalized())
                _events.ScheduleEvent(EVENT_SAY_LEADER_STOP_TEXT, 1s);
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_LK_SAY_AGGRO:
                        if (Creature* lichKing = _instance->instance->GetCreature(_instance->GetData64(NPC_LICH_KING_BOSS)))
                            if (lichKing->IsAIEnabled)
                                lichKing->AI()->Talk(me->GetEntry() == NPC_JAINA_PART2 ? SAY_LK_AGGRO_ALLY : SAY_LK_AGGRO_HORDE);
                        _events.ScheduleEvent(me->GetEntry() == NPC_JAINA_PART2 ? EVENT_JAINA_IMMOBILIZE_LK : EVENT_SYLVANAS_IMMOBILIZE_JUMP, 12s);
                        break;
                    case EVENT_JAINA_IMMOBILIZE_LK:
                        if (Creature* lichKing = _instance->instance->GetCreature(_instance->GetData64(NPC_LICH_KING_BOSS)))
                        {
                            lichKing->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            DoCast(lichKing, SPELL_JAINA_ICE_PRISON);
                            _events.ScheduleEvent(EVENT_SAY_LEAVE, 5s);
                        }
                        break;
                    case EVENT_SYLVANAS_IMMOBILIZE_JUMP:
                        if (Creature* lichKing = _instance->instance->GetCreature(_instance->GetData64(NPC_LICH_KING_BOSS)))
                        {
                            lichKing->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            me->KnockbackFrom(lichKing->GetPositionX(), lichKing->GetPositionY(), 10.0f, 3.0f);
                            _events.ScheduleEvent(EVENT_SYLVANAS_DARK_BINDING, 1.5s);
                        }
                        break;
                    case EVENT_SYLVANAS_DARK_BINDING:
                        if (Creature* lichKing = _instance->instance->GetCreature(_instance->GetData64(NPC_LICH_KING_BOSS)))
                            DoCast(lichKing, SPELL_SYLVANAS_DARK_BINDING);
                        _events.ScheduleEvent(EVENT_SAY_LEAVE, 3.5s);
                        break;
                    case EVENT_SAY_LEAVE:
                    {
                        auto const& players = _instance->instance->GetPlayers();
                        for (auto itr = players.begin(); itr != players.end(); ++itr)
                            if (Player* player = itr->GetSource())
                                player->KilledMonsterCredit(me->GetEntry(), 0); // for quest

                        Talk(me->GetEntry() == NPC_JAINA_PART2 ? SAY_JAINA_LEAVE : SAY_SYLVANAS_LEAVE);
                        me->GetMotionMaster()->MovePoint(0, LeaderEscapePos);
                        _events.ScheduleEvent(EVENT_ADD_GOSSIP, 8s);
                        break;
                    }
                    case EVENT_ADD_GOSSIP:
                        me->RemoveAura(me->GetEntry() == NPC_JAINA_PART2 ? SPELL_JAINA_ICE_BARRIER : SPELL_SYLVANAS_CLOAK_OF_DARKNESS);
                        me->SetFacingTo(LeaderEscapePos.GetOrientation());
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        break;
                    case EVENT_START_RUN:
                    {
                        _instance->SetData(ACTION_START_LK_FIGHT, 1);
                        me->setActive(true);
                        MoveToNextStopPoint();
                        if (Creature* lichKing = _instance->instance->GetCreature(_instance->GetData64(NPC_LICH_KING_BOSS)))
                        {
                            lichKing->setActive(true);
                            lichKing->SetInCombatWithZone();
                            lichKing->RemoveAura(me->GetEntry() == NPC_JAINA_PART2 ? SPELL_JAINA_ICE_PRISON : SPELL_SYLVANAS_DARK_BINDING);
                            if (lichKing->IsAIEnabled)
                                lichKing->AI()->DoAction(ACTION_START_LK_FIGHT_REAL);
                        }
                        break;
                    }
                    case EVENT_SAY_LEADER_STOP_TEXT:
                    {
                        int32 textId = 0;
                        switch (_currentPoint)
                        {
                            case 1: textId = SAY_SYLVANAS_IW_1; break;
                            case 2: textId = SAY_SYLVANAS_IW_2; break;
                            case 3: textId = SAY_SYLVANAS_IW_3; break;
                            case 4: textId = SAY_SYLVANAS_IW_4; break;
                            case 5: textId = SAY_SYLVANAS_END; break;
                        }
                        if (me->GetEntry() == NPC_JAINA_PART2)
                            textId += 10;
                        Talk(textId);
                        if (_currentPoint <= 4)
                            DoCastAOE(me->GetEntry() == NPC_JAINA_PART2 ? SPELL_DESTROY_WALL_JAINA : SPELL_DESTROY_WALL_SYLVANAS);
                        else
                        {
                            me->SetFacingTo(PathWaypoints[PATH_WP_COUNT - 1].GetOrientation());
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_READY1H);
                        }
                        break;
                    }
                    case EVENT_SAY_OPENING:
                        Talk(me->GetEntry() == NPC_JAINA_PART2 ? SAY_JAINA_OPENING : SAY_SYLVANAS_OPENING);
                        break;
                }
            }
        }

        private:
            InstanceScript* _instance;
            EventMap _events;
            uint8 _currentPoint;
    };
};

struct npc_hor_lk_trash_templateAI : public ScriptedAI
{
    npc_hor_lk_trash_templateAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _events.Reset();
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING) || me->isFeared() || me->IsCharmed() || me->isFrozen() || me->HasUnitState(UNIT_STATE_STUNNED) || me->HasUnitState(UNIT_STATE_CONFUSED))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
            DoEvent(eventId);

        DoMeleeAttackIfReady();
    }

    virtual void DoEvent(uint32 /*eventId*/) = 0;

    void JustDied(Unit* /*killer*/) override
    {
        me->SetCorpseDelay(10);
        if (InstanceScript* instance = me->GetInstanceScript())
            if (Creature* lichKing = instance->instance->GetCreature(instance->GetData64(NPC_LICH_KING_BOSS)))
                if (lichKing->IsAIEnabled)
                    lichKing->AI()->DoAction(ACTION_INFORM_TRASH_DIED);
    }

    protected:
        EventMap _events;
};

enum RagingGhoul
{
    SPELL_LEAP = 70150
};

struct npc_hor_raging_ghoulAI : public npc_hor_lk_trash_templateAI
{
    npc_hor_raging_ghoulAI(Creature* creature) : npc_hor_lk_trash_templateAI(creature) { }

    void Reset() override
    {
        _leaped = false;
    }

    void DoEvent(uint32 eventId) override { }

    void UpdateAI(uint32 diff) override
    {
        npc_hor_lk_trash_templateAI::UpdateAI(diff);

        if (!_leaped)
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
            {
                AttackStart(target);
                DoCast(target, SPELL_LEAP);
                _leaped = true;
            }
    }

    private:
        bool _leaped;
};

enum RisenWitchDoctor
{
    EVENT_CURSE_OF_DOOM = 1,
    EVENT_SHADOW_BOLT,
    EVENT_SHADOW_BOLT_VOLLEY,

    SPELL_CURSE_OF_DOOM = 70144,
    SPELL_SHADOW_BOLT = 70080,
    SPELL_SHADOW_BOLT_VOLLEY = 70145
};

struct npc_hor_risen_witch_doctorAI : public npc_hor_lk_trash_templateAI
{
    npc_hor_risen_witch_doctorAI(Creature* creature) : npc_hor_lk_trash_templateAI(creature) { }

    void EnterCombat(Unit* /*who*/) override
    {
        _events.ScheduleEvent(EVENT_CURSE_OF_DOOM, 10s);
        _events.ScheduleEvent(EVENT_SHADOW_BOLT, 4.5s);
        _events.ScheduleEvent(EVENT_SHADOW_BOLT_VOLLEY, 9s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CURSE_OF_DOOM:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true, -SPELL_CURSE_OF_DOOM))
                    DoCast(target, SPELL_CURSE_OF_DOOM);
                _events.Repeat(12s);
                break;
            case EVENT_SHADOW_BOLT:
                DoCastVictim(SPELL_SHADOW_BOLT);
                _events.Repeat(4.5s);
                break;
            case EVENT_SHADOW_BOLT_VOLLEY:
                DoCastVictim(SPELL_SHADOW_BOLT_VOLLEY);
                _events.Repeat(9s);
                break;
            default:
                break;
        }
    }
};

enum LumberingAbomination
{
    EVENT_VOMIT_SPRAY   = 1,

    SPELL_CLEAVE        = 40505,
    SPELL_VOMIT_SPRAY   = 70176
};

struct npc_hor_lumbering_abominationAI : public npc_hor_lk_trash_templateAI
{
    npc_hor_lumbering_abominationAI(Creature* creature) : npc_hor_lk_trash_templateAI(creature) {}

    void EnterCombat(Unit* /*who*/) override
    {
        _events.ScheduleEvent(EVENT_VOMIT_SPRAY, 5s);
    }

    void UpdateAI(uint32 diff) override
    {
        npc_hor_lk_trash_templateAI::UpdateAI(diff);

        DoSpellAttackIfReady(SPELL_CLEAVE);
    }

    void DoEvent(uint32 eventId) override
    {
        if (eventId == EVENT_VOMIT_SPRAY)
        {
            if (me->IsWithinMeleeRange(me->GetVictim()))
            {
                DoCastVictim(SPELL_VOMIT_SPRAY);
                _events.Repeat(18s);
            }
            else
                _events.Repeat(3s);
        }
    }
};

enum CannonFire
{
    SPELL_GUNSHIP_CANNON_FIRE = 70021
};

class spell_hor_gunship_cannon_fire_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_hor_gunship_cannon_fire_AuraScript)

    void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
    {
        PreventDefaultAction();
        if (Unit* caster = GetCaster())
            if (Creature* trigger = caster->SummonCreature(WORLD_TRIGGER, CannonFirePos[caster->GetEntry() == NPC_JAINA_PART2 ? 0 : 1][urand(0, 2)], TEMPSUMMON_TIMED_DESPAWN, 1))
                trigger->CastSpell((Unit*)nullptr, SPELL_GUNSHIP_CANNON_FIRE, true);
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_hor_gunship_cannon_fire_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

/* BATTERED HILT BELOW */
enum BatteredHilt
{
    ITEM_TEMPERED_QUELDELAR     = 49766,

    SPELL_QUELDELARS_COMPULSION = 70013,
    SPELL_QUELDELARS_WILL       = 70698
};

class at_hor_battered_hilt_start : public AreaTriggerScript
{
    public:
        at_hor_battered_hilt_start() : AreaTriggerScript("at_hor_battered_hilt_start") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
        {
            if (player->HasAura(SPELL_QUELDELARS_COMPULSION))
                if (InstanceScript* instance = player->GetInstanceScript())
                    instance->SetData(DATA_BATTERED_HILT, 2);
            return true;
        }
};

class at_hor_battered_hilt_throw : public AreaTriggerScript
{
    public:
        at_hor_battered_hilt_throw() : AreaTriggerScript("at_hor_battered_hilt_throw") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
        {
            if (player->HasAura(SPELL_QUELDELARS_COMPULSION))
                if (InstanceScript* instance = player->GetInstanceScript())
                {
                    uint32 bhd = instance->GetData(DATA_BATTERED_HILT);
                    if (bhd == BHSF_NONE || bhd != BHSF_STARTED)
                        return true;
                    player->CastSpell(player, SPELL_QUELDELARS_WILL, true);
                    player->DestroyItemCount(ITEM_TEMPERED_QUELDELAR, 1, true);
                    instance->SetData(DATA_BATTERED_HILT, 3);
                }
            return true;
        }
};

void AddSC_halls_of_reflection()
{
    new npc_hor_leader();

    new CreatureAILoader<npc_ghostly_priestAI>("npc_ghostly_priest");
    new CreatureAILoader<npc_phantom_mageAI>("npc_phantom_mage");
    new CreatureAILoader<npc_phantom_hallucinationAI>("npc_phantom_hallucination");
    new CreatureAILoader<npc_shadowy_mercenaryAI>("npc_shadowy_mercenary");
    new CreatureAILoader<npc_spectral_footmanAI>("npc_spectral_footman");
    new CreatureAILoader<npc_tortured_riflemanAI>("npc_tortured_rifleman");

    new CreatureAILoader<boss_frostsworn_generalAI>("boss_frostsworn_general");
    new CreatureAILoader<npc_hor_spiritual_reflectionAI>("npc_hor_spiritual_reflection");

    new at_hor_shadow_throne();
    new CreatureAILoader<npc_hor_lich_kingAI>("npc_hor_lich_king");
    new npc_hor_leader_second();
    new CreatureAILoader<npc_hor_raging_ghoulAI>("npc_hor_raging_ghoul");
    new CreatureAILoader<npc_hor_risen_witch_doctorAI>("npc_hor_risen_witch_doctor");
    new CreatureAILoader<npc_hor_lumbering_abominationAI>("npc_hor_lumbering_abomination");
    new AuraScriptLoaderEx<spell_hor_gunship_cannon_fire_AuraScript>("spell_hor_gunship_cannon_fire");

    new at_hor_battered_hilt_start();
    new at_hor_battered_hilt_throw();
}