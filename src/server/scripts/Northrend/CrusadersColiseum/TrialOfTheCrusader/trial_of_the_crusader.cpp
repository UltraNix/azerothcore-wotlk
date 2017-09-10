/*
REWRITTEN FROM SCRATCH BY PUSSYWIZARD, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "trial_of_the_crusader.h"
#include "Player.h"
#include "Group.h"

enum MenuTexts
{
    MSG_BEASTS_INITIAL                = 14664,
    MSG_BEASTS_INITIAL_2              = 14665,
    MSG_BEASTS_WIPED                  = 14667,
    MSG_BEASTS_WIPED_2                = 14668,
    MSG_JARAXXUS_INITIAL              = 14678,
    MSG_JARAXXUS_INITIAL_2            = 14680,
    MSG_JARAXXUS_WIPED                = 14679,
    MSG_JARAXXUS_WIPED_2              = 14682,
    MSG_FACTIONS_INITIAL              = 14813,
    MSG_FACTIONS_INITIAL_2            = 14814,
    MSG_FACTIONS_WIPED                = 14815,
    MSG_FACTIONS_WIPED_2              = 14816,
    MSG_VALKYRS_INITIAL               = 14819,
    MSG_VALKYRS_INITIAL_2             = 14821,
    MSG_VALKYRS_WIPED                 = 14820,
    MSG_VALKYRS_WIPED_2               = 14822,
    MSG_ANUBARAK_INITIAL              = 14828,
    MSG_ANUBARAK_INITIAL_2            = 14829,

    MSG_NOT_EGLIBLE_FOR_HEROIC        = 14850,
    MSG_NOT_EGLIBLE_FOR_HEROIC_2      = 500000,

    MSG_TESTED                        = 724001,
    MSG_NEXT_STAGE                    = 724002,
    MSG_CRUSADERS                    = 724003,
    MSG_ANUBARAK                    = 724005,
};

enum Achievements
{
    ACHIEVEMENT_CALL_OF_THE_CRUSADE_10 = 3917,
    ACHIEVEMENT_CALL_OF_THE_CRUSADE_25 = 3916
};

class npc_announcer_toc10 : public CreatureScript
{
public:
    npc_announcer_toc10() : CreatureScript("npc_announcer_toc10") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if( !pCreature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP) )
            return true;

        if (Group* group = pPlayer->GetGroup())
            if (!group->IsLeader(pPlayer->GetGUID()))
                return true;

        InstanceScript* pInstance = pCreature->GetInstanceScript();
        if( !pInstance )
            return true;

        auto map = pInstance->instance;

        if (map && (map->Is25ManRaid() && map->IsHeroic() && !pPlayer->HasAchieved(ACHIEVEMENT_CALL_OF_THE_CRUSADE_25)) /*|| TESTING (map->IsHeroic() && !pPlayer->HasAchieved(ACHIEVEMENT_CALL_OF_THE_CRUSADE_10)*/)
        {
            if (!pPlayer->IsGameMaster())
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I have not completed the Trial of the Crusader.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                pPlayer->SEND_GOSSIP_MENU(MSG_NOT_EGLIBLE_FOR_HEROIC, pCreature->GetGUID());
                return true;
            }
        }

        uint32 gossipTextId = 0;
        switch( pInstance->GetData(TYPE_INSTANCE_PROGRESS) )
        {
            case INSTANCE_PROGRESS_INITIAL:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Yes. We are prepared for the challenges ahead of us.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                gossipTextId = MSG_BEASTS_INITIAL;
                break;
            case INSTANCE_PROGRESS_INTRO_DONE:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "We want another shot at those beasts!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                gossipTextId = MSG_BEASTS_WIPED;
                break;
            case INSTANCE_PROGRESS_BEASTS_DEAD:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "What new challenge awaits us?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                gossipTextId = MSG_JARAXXUS_INITIAL;
                break;
            case INSTANCE_PROGRESS_JARAXXUS_INTRO_DONE:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "We're ready to fight with sorceror again.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                gossipTextId = MSG_JARAXXUS_WIPED;
                break;
            case INSTANCE_PROGRESS_JARAXXUS_DEAD:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Of course!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                gossipTextId = MSG_FACTIONS_INITIAL;
                break;
            case INSTANCE_PROGRESS_FACTION_CHAMPIONS_INTRO_DONE:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You'll be even more amazed after we take them off!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                gossipTextId = MSG_FACTIONS_WIPED;
                break;
            case INSTANCE_PROGRESS_FACTION_CHAMPIONS_DEAD:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "That tough, huh?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                gossipTextId = MSG_VALKYRS_INITIAL;
                break;
            case INSTANCE_PROGRESS_VALKYR_INTRO_DONE:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "We'll just have to improve our own teamwork to match the two of them.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                gossipTextId = MSG_VALKYRS_WIPED;
                break;
            case INSTANCE_PROGRESS_VALKYR_DEAD:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Your words of praise are appreciated, Coliseum Master.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                gossipTextId = MSG_ANUBARAK_INITIAL;
                break;
            case INSTANCE_PROGRESS_DONE:
                pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                return true;
            default:
                return true;
        }

        pPlayer->SEND_GOSSIP_MENU(gossipTextId, pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        InstanceScript* instance = creature->GetInstanceScript();
        if( !instance )
            return true;

        auto map = instance->instance;

        if (map && (map->Is25ManRaid() && map->IsHeroic() && !player->HasAchieved(ACHIEVEMENT_CALL_OF_THE_CRUSADE_25)) /*TESTING|| (map->IsHeroic() && !player->HasAchieved(ACHIEVEMENT_CALL_OF_THE_CRUSADE_10))*/)
        {
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
            {
                if (!player->IsGameMaster())
                {
                    player->SEND_GOSSIP_MENU(MSG_NOT_EGLIBLE_FOR_HEROIC_2, creature->GetGUID());
                    return true;
                }
            }
        }

        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            switch (instance->GetData(TYPE_INSTANCE_PROGRESS))
            {
                case INSTANCE_PROGRESS_INITIAL:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bring forth the first challenge!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MSG_BEASTS_INITIAL_2, creature->GetGUID());
                    break;
                case INSTANCE_PROGRESS_INTRO_DONE:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "We're ready. This time things will be different.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MSG_BEASTS_WIPED_2, creature->GetGUID());
                    break;
                case INSTANCE_PROGRESS_BEASTS_DEAD:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "We're ready for the next challenge.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MSG_JARAXXUS_INITIAL_2, creature->GetGUID());
                    break;
                case INSTANCE_PROGRESS_JARAXXUS_INTRO_DONE:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Now.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MSG_JARAXXUS_WIPED_2, creature->GetGUID());
                    break;
                case INSTANCE_PROGRESS_JARAXXUS_DEAD:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Give the signal! We're ready to go!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MSG_FACTIONS_INITIAL_2, creature->GetGUID());
                    break;
                case INSTANCE_PROGRESS_FACTION_CHAMPIONS_INTRO_DONE:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "We're ready for anything!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MSG_FACTIONS_WIPED_2, creature->GetGUID());
                    break;
                case INSTANCE_PROGRESS_FACTION_CHAMPIONS_DEAD:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Val'kyr? We're ready for them.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MSG_VALKYRS_INITIAL_2, creature->GetGUID());
                    break;
                case INSTANCE_PROGRESS_VALKYR_INTRO_DONE:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Just bring them out again, then watch.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MSG_VALKYRS_WIPED_2, creature->GetGUID());
                    break;
                case INSTANCE_PROGRESS_VALKYR_DEAD:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "That is strange...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MSG_ANUBARAK_INITIAL_2, creature->GetGUID());
                    break;
            }
        }

        if (action == GOSSIP_ACTION_INFO_DEF + 2)
        {
            instance->SetData(TYPE_ANNOUNCER_GOSSIP_SELECT, 0);
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }

        return true;
    }
};

void AddSC_trial_of_the_crusader()
{
    new npc_announcer_toc10();
}
