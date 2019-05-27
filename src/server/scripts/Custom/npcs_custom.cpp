/*
 * Copyright (C)
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

/* ScriptData
SDName: npcs_custom
SD%Complete: 100
SDComment: To be used for custom NPCs that are located globally.
SDCategory: NPCs
EndScriptData
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "World.h"
#include "CreatureTextMgr.h"
#include "PassiveAI.h"
#include "GameEventMgr.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Cell.h"
#include "CellImpl.h"
#include "SpellAuras.h"
#include "CombatAI.h"
#include "PassiveAI.h"
#include "Pet.h"
#include "Chat.h"
#include "Group.h"
#include "WaypointManager.h"
#include "SmartAI.h"
#include "DBCStructure.h"
#include "Language.h"
#include "CustomEventMgr.h"
#include "BattlegroundMgr.h"
#include "ArenaTeamMgr.h"

/* ######
## npc_schody
##### */

#define PASS "I want to use the entry ticket!"

class npc_schody : public CreatureScript
{
public:
    npc_schody() : CreatureScript("npc_schody") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!sWorld->getBoolConfig(CONFIG_CUSTOM_EVENTS_FEATURES_ENABLE))
            return false;

        if (creature->GetEntry() != 99004 && creature->GetEntry() < 99006)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Entry ticket, please!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        else if (creature->GetEntry() != 99004 && creature->GetEntry() >= 99006)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Check point ticket, please!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        if (creature->GetEntry() == 99000 && player->HasItemCount(86101))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, PASS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

        if (creature->GetEntry() == 99001 && player->HasItemCount(86102))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, PASS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

        if (creature->GetEntry() == 99002 && player->HasItemCount(86103))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, PASS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);

        if (creature->GetEntry() == 99003 && player->HasItemCount(86103))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, PASS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);

        if (creature->GetEntry() == 99004)
        {
            player->SEND_GOSSIP_MENU(999001, creature->GetGUID());
            if (player->HasItemCount(86104))
            {
                sLog->outRewards("Player: %s GUID: %u has complete event 'Schody do nieba'", player->GetName().c_str(), player->GetGUIDLow());
                sWorld->SendWorldText(11050, player->GetName().c_str());
                sWorld->SendWorldText(11051, player->GetName().c_str());

                for (uint8 i = 0; i < 4; i++)
                    if (player->HasItemCount(86101 + i, 1, false))
                        player->DestroyItemCount(86101 + i, 1, true);
            }
        }
        else player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            // Give player a pass
            case GOSSIP_ACTION_INFO_DEF + 1:
            {
                if (creature->GetEntry() == 99000 && !player->HasItemCount(86101))
                    player->AddItem(86101, 1);
                else if (creature->GetEntry() == 99001 && player->HasItemCount(86101))
                    player->AddItem(86102, 1);
                else if (creature->GetEntry() == 99002 && player->HasItemCount(86102))
                    player->AddItem(86103, 1);
                else if (creature->GetEntry() == 99003 && player->HasItemCount(86103))
                    player->AddItem(86104, 1);
                else if (creature->GetEntry() == 99006)
                    player->AddItem(86105, 1);
                else if (creature->GetEntry() == 99007)
                    player->AddItem(86106, 1);
            }
            break;
            // Teleport player
            case GOSSIP_ACTION_INFO_DEF + 2:
            {
                if (player->HasItemCount(86101))
                    player->TeleportTo(37, 656.831f, 108.904f, 328.049f, player->GetOrientation());
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 3:
            {
                if (player->HasItemCount(86102))
                    player->TeleportTo(1, 5261.821f, -2174.786f, 1259.123f, player->GetOrientation());
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 4:
            {
                if (player->HasItemCount(86103))
                    player->TeleportTo(0, 4330.820f, -2880.420f, 0.9257f, player->GetOrientation());
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 5:
            {
                if (player->HasItemCount(86104))
                    player->TeleportTo(37, 51.713f, -176.806f, 402.282f, player->GetOrientation());
            }
            break;
            }
        player->PlayerTalkClass->SendCloseGossip();
        return true;
    }
};

/*######
## npc_lore
## Not used now.

enum Pytania
{
    ANNOUNCEMENT             = 100,
    QUESTION_1               = 1000,
    QUESTION_2               = 2000,
    QUESTION_3               = 3000,
    QUESTION_4               = 4000,
    QUESTION_5               = 5000,
    QUESTION_6               = 6000,
    QUESTION_7               = 7000,
    QUESTION_8               = 8000,
    QUESTION_9               = 9000,
    QUESTION_10              = 10000,
    QUESTION_11              = 11000,
    QUESTION_CORRECT_ANSWER  = 30000,
    QUESTION_WRONG_ANSWER    = 40000,

    NPC_GREETINGS_TEXT_1    = 970001,
    NPC_GREETINGS_TEXT_2    = 970002,
    NPC_GREETINGS_TEXT_3    = 970003,
    NPC_GREETINGS_TEXT_4    = 970004,
    NPC_GREETINGS_TEXT_5    = 970005,
    NPC_GREETINGS_TEXT_6    = 970006,
    NPC_GREETINGS_TEXT_7    = 970007,
    NPC_GREETINGS_TEXT_8    = 970008,
    NPC_GREETINGS_TEXT_9    = 970009,
    NPC_GREETINGS_TEXT_10   = 970010,
    NPC_GREETINGS_TEXT_11   = 970011,
    NPC_GREETINGS_TEXT_12   = 970012,
    NPC_GREETINGS_TEXT_13   = 970013,
    NPC_QUESTION_TEXT_1     = 970014,
    NPC_QUESTION_TEXT_2     = 970015,
    NPC_QUESTION_TEXT_3     = 970016,
    NPC_QUESTION_TEXT_4     = 970017,
    NPC_QUESTION_TEXT_5     = 970018,
    NPC_QUESTION_TEXT_6     = 970019,
    NPC_QUESTION_TEXT_7     = 970020,
    NPC_QUESTION_TEXT_8     = 970021,
    NPC_QUESTION_TEXT_9     = 970022,
    NPC_QUESTION_TEXT_10    = 970023,
    NPC_QUESTION_TEXT_11    = 970024,

    NPC_CORRECT_TEXT_1      = 980001,
    NPC_CORRECT_TEXT_2      = 980002,
    NPC_CORRECT_TEXT_3      = 980003,
    NPC_CORRECT_TEXT_4      = 980004,
    NPC_CORRECT_TEXT_5      = 980005,
    NPC_CORRECT_TEXT_6      = 980006,
    NPC_CORRECT_TEXT_7      = 980007,
    NPC_CORRECT_TEXT_8      = 980008,
    NPC_CORRECT_TEXT_9      = 980009,
    NPC_CORRECT_TEXT_10     = 980010,
    NPC_CORRECT_TEXT_11     = 980011,
    BLANK                   = 980012
};

class npc_lore : public CreatureScript
{
public:
    npc_lore() : CreatureScript("npc_lore") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        //Announce for next questions
        if (creature->GetEntry() == 96000)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Oczywiscie. Gdzie mam zaczac?", GOSSIP_SENDER_MAIN, ANNOUNCEMENT);
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_1, creature->GetGUID());
        }
        //Question 1
        if (creature->GetEntry() == 96001)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Oczywiscie.", GOSSIP_SENDER_MAIN, QUESTION_1);
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_2, creature->GetGUID());
        }
        //Question 2
        if (creature->GetEntry() == 96002 && player->HasItemCount(86101))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "\"Thus mush talAh rini Dorados'no eraburis.\" Co to znaczy?", GOSSIP_SENDER_MAIN, QUESTION_2);
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_3, creature->GetGUID());
        }
        //Question 3
        if (creature->GetEntry() == 96003 && player->HasItemCount(86102))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "No dobrze, zobaczmy.", GOSSIP_SENDER_MAIN, QUESTION_3);
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_4, creature->GetGUID());
        }
        //Question 4
        if (creature->GetEntry() == 96004 && player->HasItemCount(86103))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Oczywiscie, przeczytaj mi ta zagadke.", GOSSIP_SENDER_MAIN, QUESTION_4);
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_5, creature->GetGUID());
        }
        //Question 5
        if (creature->GetEntry() == 96005 && player->HasItemCount(86104))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Zaczynajmy.", GOSSIP_SENDER_MAIN, QUESTION_5);
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_6, creature->GetGUID());
        }
        //Question 6
        if (creature->GetEntry() == 96006 && player->HasItemCount(86105))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Masz dla mnie jakas zagadke?", GOSSIP_SENDER_MAIN, QUESTION_6);
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_7, creature->GetGUID());
        }
        //Question 7
        if (creature->GetEntry() == 96007 && player->HasItemCount(86106))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Wspaniale, moge poznac jego tresc?", GOSSIP_SENDER_MAIN, QUESTION_7);
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_8, creature->GetGUID());
        }
        //Question 8
        if (creature->GetEntry() == 96008 && player->HasItemCount(86107))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Czy jest cos w czym moge Ci pomoc?", GOSSIP_SENDER_MAIN, QUESTION_8);
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_9, creature->GetGUID());
        }
        //Question 9
        if (creature->GetEntry() == 96009 && player->HasItemCount(86108))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Oczywiscie.", GOSSIP_SENDER_MAIN, QUESTION_9);
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_10, creature->GetGUID());
        }
        //Question 10
        if (creature->GetEntry() == 96010 && player->HasItemCount(86109))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Powiedz mi, co to za wiadomosc.", GOSSIP_SENDER_MAIN, QUESTION_10);
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_11, creature->GetGUID());
        }
        //Question 11
        if (creature->GetEntry() == 96011 && player->HasItemCount(86110))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Slucham wiec.", GOSSIP_SENDER_MAIN, QUESTION_11);
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_12, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case QUESTION_CORRECT_ANSWER:
        {
            switch (player->GetSelectedAuction())
            {
            case QUESTION_1:
                player->SEND_GOSSIP_MENU(NPC_CORRECT_TEXT_1, creature->GetGUID());
                if (!player->HasItemCount(86101))
                    player->AddItem(86101, 1);
                break;
            case QUESTION_2:
                player->SEND_GOSSIP_MENU(NPC_CORRECT_TEXT_2, creature->GetGUID());
                if (!player->HasItemCount(86102))
                    player->AddItem(86102, 1);
                break;
            case QUESTION_3:
                player->SEND_GOSSIP_MENU(NPC_CORRECT_TEXT_3, creature->GetGUID());
                if (!player->HasItemCount(86103))
                    player->AddItem(86103, 1);
                break;
            case QUESTION_4:
                player->SEND_GOSSIP_MENU(NPC_CORRECT_TEXT_4, creature->GetGUID());
                if (!player->HasItemCount(86104))
                    player->AddItem(86104, 1);
                break;
            case QUESTION_5:
                player->SEND_GOSSIP_MENU(NPC_CORRECT_TEXT_5, creature->GetGUID());
                if (!player->HasItemCount(86105))
                    player->AddItem(86105, 1);
                break;
            case QUESTION_6:
                player->SEND_GOSSIP_MENU(NPC_CORRECT_TEXT_6, creature->GetGUID());
                if (!player->HasItemCount(86106))
                    player->AddItem(86106, 1);
                break;
            case QUESTION_7:
                player->SEND_GOSSIP_MENU(NPC_CORRECT_TEXT_7, creature->GetGUID());
                if (!player->HasItemCount(86107))
                    player->AddItem(86107, 1);
                break;
            case QUESTION_8:
                player->SEND_GOSSIP_MENU(NPC_CORRECT_TEXT_8, creature->GetGUID());
                if (!player->HasItemCount(86108))
                    player->AddItem(86108, 1);
                break;
            case QUESTION_9:
                player->SEND_GOSSIP_MENU(NPC_CORRECT_TEXT_9, creature->GetGUID());
                if (!player->HasItemCount(86109))
                    player->AddItem(86109, 1);
                break;
            case QUESTION_10:
                player->SEND_GOSSIP_MENU(NPC_CORRECT_TEXT_10, creature->GetGUID());
                if (!player->HasItemCount(86110))
                    player->AddItem(86110, 1);
                break;
            case QUESTION_11:
            {
                player->SEND_GOSSIP_MENU(NPC_CORRECT_TEXT_11, creature->GetGUID());
                for (uint8 i = 0; i < 10; i++)
                    if (player->HasItemCount(86101 + i, 1, false))
                        player->DestroyItemCount(86101 + i, 1, true);
                std::string message = "Gratulacje ukonczyles event Kroniki Azeroth!";
                std::string s = "Kroniki Azeroth";
                ChatHandler handler(player->GetSession());
                handler.PSendSysMessage(message.c_str());
                sWorld->SendWorldText(LANG_EVENT_WINNER, player->GetName().c_str(), s.c_str());
                sLog->outRewards("Player: %s GUID: %u has complete event 'LORE'", player->GetName().c_str(), player->GetGUIDLow());

            } break;
            default:
                player->CLOSE_GOSSIP_MENU();
                break;
            }
        } break;
        case QUESTION_WRONG_ANSWER:
        {
            std::string message = "";
            ChatHandler handler(player->GetSession());

            switch (player->GetSelectedAuction())
            {
            case QUESTION_1:
                message = "Nie nie nie! Wroc jak zglebisz nieco wiecej wiedzy.";
                break;
            case QUESTION_2:
                message = "Widze, ze tez masz problemy z elfickim jezykiem. Potrzebuje kogos bardziej wykwalifikowanego. Przyjdz, jak dowiesz sie, jaka jest odpowiedz.";
                break;
            case QUESTION_3:
                message = "Co mi po nieskalanym podrozniku, co wiedzy nie ma, idz precz!";
                break;
            case QUESTION_4:
                message = "Zostaw, bo zniszczysz! Nie wiesz, to nie zgaduj! Wroc do mnie jak sobie przypomnisz!";
                break;
            case QUESTION_5:
                message = "Zaufalam Ci! Mogles zablokowac portal, dobrze, ze zabral tylko Ciebie! Wroc tu i tym razem sie nie pomyl, to dla mnie wazne!";
                break;
            case QUESTION_6:
                message = "Kazdy mogl sie pomylic, zasiegnij wiedzy od uczonego nim do mnie wrocisz, dobrze?";
                break;
            case QUESTION_7:
                message = "Nie draznij mnie, nie masz pojecia co mowisz! Nie chce Cie tu widziec, poki nie bedziesz pewien swoich slow!";
                break;
            case QUESTION_8:
                message = "Nie potrafisz mi pomoc? Trudno, znajde kogos, kto wie. Jezeli Ci sie przypomni, przyjdz do mnie i powiedz, co wiesz.";
                break;
            case QUESTION_9:
                message = "Uwazaj! ... Musialem Cie przeteleportowac, inaczej zginalbys od pioruna kulistego. Nie powinienes odpowiadac pochopnie. Przyjdz do mnie, gdy bedziesz znal odpowiedz.";
                break;
            case QUESTION_10:
                message = "Zawiodles. Nawet tajemnicza istota zawibrowala swoja magia w zlosci. Niewiedza niesie za soba kolosalne skutki! Wroc, gdy bedziesz pewien swojej decyzji.";
                break;
            case QUESTION_11:
                message = "Nie nie nie. Zasiegnij wiedzy ze sprawdzonego zrodla i wroc, gdy bedziesz wiedzial, co zrobiles nie tak.";
                break;
            }

            handler.PSendSysMessage(message.c_str());

            if (player->GetTeamId() == TEAM_HORDE)
                player->TeleportTo(0, 2439.0f, 45.0f, 500.0f, player->GetOrientation());
            else
                player->TeleportTo(0, -9444.0f, 1258.0f, 500.0f, player->GetOrientation());

            player->CLOSE_GOSSIP_MENU();
        } break;
        case ANNOUNCEMENT:
        {
            player->SEND_GOSSIP_MENU(NPC_GREETINGS_TEXT_13, creature->GetGUID());
        } break;
        case QUESTION_1:
        {
            player->SetSelectedAuction(QUESTION_1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "A) Courage.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "B) Hope.", GOSSIP_SENDER_MAIN, QUESTION_CORRECT_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "C) Pride.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "D) Fate.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->SEND_GOSSIP_MENU(NPC_QUESTION_TEXT_1, creature->GetGUID());
        } break;
        case QUESTION_2:
        {
            player->SetSelectedAuction(QUESTION_2);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "A) o Lor'Themara.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "B) o Dar'Khana.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "C) o Dath'Remara.", GOSSIP_SENDER_MAIN, QUESTION_CORRECT_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "D) oczywiscie o Andrzeja Golote.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->SEND_GOSSIP_MENU(NPC_QUESTION_TEXT_2, creature->GetGUID());
        } break;
        case QUESTION_3:
        {
            player->SetSelectedAuction(QUESTION_3);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "A) Malfuriona Stormrage'a", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "B) Fandrala Staghelm'a.", GOSSIP_SENDER_MAIN, QUESTION_CORRECT_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "C) Tyrande Whisperwind.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "D) Ysery.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->SEND_GOSSIP_MENU(NPC_QUESTION_TEXT_3, creature->GetGUID());
        } break;
        case QUESTION_4:
        {
            player->SetSelectedAuction(QUESTION_4);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "A) Kaldorei i Quel'dorei.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "B) Kaldorei i Shen'dralar.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "C) Kaldorei i Kaplanki Elune.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "D) Kaplanki Elune i Shen'dralar.", GOSSIP_SENDER_MAIN, QUESTION_CORRECT_ANSWER);

            player->SEND_GOSSIP_MENU(NPC_QUESTION_TEXT_4, creature->GetGUID());
        } break;
        case QUESTION_5:
        {
            player->SetSelectedAuction(QUESTION_5);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "A) Lady Vashj.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "B) Sargeras.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "C) Xavius.", GOSSIP_SENDER_MAIN, QUESTION_CORRECT_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "D) N'Zoth.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->SEND_GOSSIP_MENU(NPC_QUESTION_TEXT_5, creature->GetGUID());
        } break;
        case QUESTION_6:
        {
            player->SetSelectedAuction(QUESTION_6);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "A) Kamienna Statuetka.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "B) Zloty zegarek kieszonkowy.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "C) Czarna ksiega.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "D) Obsydianowa klepsydra.", GOSSIP_SENDER_MAIN, QUESTION_CORRECT_ANSWER);
            player->SEND_GOSSIP_MENU(NPC_QUESTION_TEXT_6, creature->GetGUID());
        } break;
        case QUESTION_7:
        {
            player->SetSelectedAuction(QUESTION_7);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "A) Kaldorei.", GOSSIP_SENDER_MAIN, QUESTION_CORRECT_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "B) Quel'Dorei.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "C) Gnomy.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "D) Ludzie.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->SEND_GOSSIP_MENU(NPC_QUESTION_TEXT_7, creature->GetGUID());
        } break;
        case QUESTION_8:
        {
            player->SetSelectedAuction(QUESTION_8);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "A) Icefang.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "B) Frostclaw.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "C) Snowsong.", GOSSIP_SENDER_MAIN, QUESTION_CORRECT_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "D) Coldpaw.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->SEND_GOSSIP_MENU(NPC_QUESTION_TEXT_8, creature->GetGUID());
        } break;
        case QUESTION_9:
        {
            player->SetSelectedAuction(QUESTION_9);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "A) Drek'Thar.", GOSSIP_SENDER_MAIN, QUESTION_CORRECT_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "B) Ner'Zhul.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "C) Velen.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "D) Blackhand.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->SEND_GOSSIP_MENU(NPC_QUESTION_TEXT_9, creature->GetGUID());
        } break;
        case QUESTION_10:
        {
            player->SetSelectedAuction(QUESTION_10);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "A) Porzucona latajaca forteca.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "B) Swiatynia w zakleciu ochronnym w postaci krysztalu.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "C) Tajny bunkier ludu Draenei.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "D) Miedzywymiarowy statek kosmiczny.", GOSSIP_SENDER_MAIN, QUESTION_CORRECT_ANSWER);
            player->SEND_GOSSIP_MENU(NPC_QUESTION_TEXT_10, creature->GetGUID());
        } break;
        case QUESTION_11:
        {
            player->SetSelectedAuction(QUESTION_11);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "A) Pit Lord Brutallus.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "B) Doom Lord Kazzak.", GOSSIP_SENDER_MAIN, QUESTION_CORRECT_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "C) Pit Lord Magtheridon.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "D) Doom Lord Kaz'Rogal.", GOSSIP_SENDER_MAIN, QUESTION_WRONG_ANSWER);
            player->SEND_GOSSIP_MENU(NPC_QUESTION_TEXT_11, creature->GetGUID());
        } break;
        }

        return true;
    }
};

######*/

/*######
## npc_dala_tele
###### */

class npc_dala_tele : public CreatureScript
{
public:
    npc_dala_tele() : CreatureScript("npc_dala_tele") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->TeleportTo(571, 5804.149902f, 624.770996f, 647.767029f, 1.640000f);
        return true;
    }
};

////////////////////////////
// Hunger Games Event
// Currently not used!
///////////////////////////

enum HungerGames
{
    ACTION_ADD_TO_QUEUE        = 1,
    ACTION_QUIT                = 2,
    ACTION_INFO                = 3,
    ACTION_LEAVE_QUEUE         = 4,
    ACTION_ADD_TO_GMLIST       = 5,
    ACTION_REMOVE_FROM_GMLIST  = 6,

    CACTION_START_EVENT        = 100,
    CACTION_PLAYERS_COUNT      = 101,
    CACTION_REVIVE_PLAYERS     = 102,
    CACTION_RESET_EVENT        = 103,
    CACTION_FREEZE_PLAYERS     = 104,
    CACTION_UNFREEZE_PLAYERS   = 105,
    CACTION_ADD_DEBUFF         = 106,
    CACTION_REMOVE_DEBUFF      = 107,
    CACTION_TELEPORT_TO_HORDE  = 108,
    CACTION_SPAWN_ELITE        = 109,
    CACTION_SPAWN_ELITE_ALLY   = 110,
    CACTION_SPAWN_ELITE_HORDE  = 111,
    CACTION_SPAWN_ELITE_MIDDLE = 112,
    CACTION_PLAYERS_NAMES      = 113,
    CACTION_GM_NAMES           = 114,
    CACTION_PLAYERS_STEALTH    = 115,

    NPC_ELITE       = 190103,

    GOSSIP_MAIN     = 1000600,
    GOSSIP_INFO     = 1000601,
    GOSSIP_PROGRESS = 1000602,
    GOSSIP_FULL     = 1000603,
    GOSSIP_LVL      = 1000604
};

Position const elitePos[3] =
{
    { 691.f, 103.f, 279.f },
    { 37.f, 507.f, 294.f },
    { 305.65f, 183.96f, 235.7f }
};

class npc_hunger_games : public CreatureScript 
{
public:
    npc_hunger_games() : CreatureScript("npc_hunger_games") {}

    bool OnGossipHello(Player* player, Creature* creature) override 
    {
        if (!sWorld->getBoolConfig(CONFIG_HUNGER_GAMES_ENABLE)) 
            return false;

        if (player->IsGameMaster())
        {
            if (!sCustomEventMgr->isGmInHungerGames(player->GetGUID()))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Dodaj mnie do GM listy.", GOSSIP_SENDER_MAIN, ACTION_ADD_TO_GMLIST);
            else
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Usun mnie z GM listy.", GOSSIP_SENDER_MAIN, ACTION_REMOVE_FROM_GMLIST);
        }
        if (player->getLevel() < 79) 
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tell me more about Hunger Games", GOSSIP_SENDER_MAIN, ACTION_INFO);
            player->SEND_GOSSIP_MENU(GOSSIP_LVL, creature->GetGUID());
            return true;
        }
        else if (sCustomEventMgr->getHungerGamesState() != HUNGER_GAMES_NOT_STARTED)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tell me more about Hunger Games", GOSSIP_SENDER_MAIN, ACTION_INFO);
            player->SEND_GOSSIP_MENU(GOSSIP_PROGRESS, creature->GetGUID());
            return true;
        }
        else if (sCustomEventMgr->isHungerGamesFull() && !sCustomEventMgr->isPlayerInHungerGames(player->GetGUID()))
        {
            player->SEND_GOSSIP_MENU(GOSSIP_FULL, creature->GetGUID());
            return true;
        }

        if (!sCustomEventMgr->isPlayerInHungerGames(player->GetGUID()))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Yes. I am sure. Nothing is beyond me!", GOSSIP_SENDER_MAIN, ACTION_ADD_TO_QUEUE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Well... I have some things to do...", GOSSIP_SENDER_MAIN, ACTION_QUIT);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tell me more about Hunger Games", GOSSIP_SENDER_MAIN, ACTION_INFO);
        }
        else
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I've changed my mind, I don't want to participate in the Games anymore!", GOSSIP_SENDER_MAIN, ACTION_LEAVE_QUEUE);

        player->SEND_GOSSIP_MENU(GOSSIP_MAIN, creature->GetGUID());
        return true;
    }
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override 
    {
        switch (action) 
        {
            case ACTION_ADD_TO_QUEUE:
                sCustomEventMgr->addPlayerToHungerGames(player->GetGUID());
                ChatHandler(player->GetSession()).PSendSysMessage("You have been added to Hunger Games queue!");
                player->CLOSE_GOSSIP_MENU();
                break;
            case ACTION_LEAVE_QUEUE:
                sCustomEventMgr->removePlayerFromHungerGames(player->GetGUID());
                ChatHandler(player->GetSession()).PSendSysMessage("You have been removed from Hunger Games queue!");
                player->CLOSE_GOSSIP_MENU();
                break;
            case ACTION_QUIT:
                player->CLOSE_GOSSIP_MENU();
                break;
            case ACTION_INFO:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Understood", GOSSIP_SENDER_MAIN, ACTION_QUIT);
                player->SEND_GOSSIP_MENU(GOSSIP_INFO, creature->GetGUID());
                break;
            case ACTION_ADD_TO_GMLIST:
                sCustomEventMgr->addGmToHungerGames(player->GetGUID());
                ChatHandler(player->GetSession()).PSendSysMessage("Zostales dodany do listy GMow monitorujacych event");
                player->CLOSE_GOSSIP_MENU();
                break;
            case ACTION_REMOVE_FROM_GMLIST:
                sCustomEventMgr->removeGmFromHungerGames(player->GetGUID());
                ChatHandler(player->GetSession()).PSendSysMessage("Juz nie monitoruejsz eventu. Piootrek jest zawiedziony twoja postawa :(");
                player->CLOSE_GOSSIP_MENU();
                break;
        }
        return true;
    }
};

class npc_hunger_games_control : public CreatureScript 
{
public:
    npc_hunger_games_control() : CreatureScript("npc_hunger_games_control") {}

    bool OnGossipHello(Player* player, Creature* creature) override 
    {
        if (!sWorld->getBoolConfig(CONFIG_HUNGER_GAMES_ENABLE)) 
            return false;

        if (player->GetSession()->GetSecurity() < 4)
            return false;

        if (sCustomEventMgr->isHungerGamesEventInProgress()) 
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "****Event w trakcie****", GOSSIP_SENDER_MAIN, ACTION_QUIT);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return true;
        }

        switch (sCustomEventMgr->getHungerGamesState())
        {
            case HUNGER_GAMES_NOT_STARTED:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Rozpocznij event", GOSSIP_SENDER_MAIN, CACTION_START_EVENT);
                break;
            case HUNGER_GAMES_PREPARATION:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Resnij ludzi", GOSSIP_SENDER_MAIN, CACTION_REVIVE_PLAYERS);
                break;
            case HUNGER_GAMES_STARTED:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Zfreezuj graczy", GOSSIP_SENDER_MAIN, CACTION_FREEZE_PLAYERS);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Unfreezuj graczy", GOSSIP_SENDER_MAIN, CACTION_UNFREEZE_PLAYERS);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Daj debuffa +50% dmg taken", GOSSIP_SENDER_MAIN, CACTION_ADD_DEBUFF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Zabierz debuffa +50% dmg taken", GOSSIP_SENDER_MAIN, CACTION_REMOVE_DEBUFF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleportuj wszystkich do bazy Hordy", GOSSIP_SENDER_MAIN, CACTION_TELEPORT_TO_HORDE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Zespawnuj elite", GOSSIP_SENDER_MAIN, CACTION_SPAWN_ELITE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Kto ukrywa sie w stealth?", GOSSIP_SENDER_MAIN, CACTION_PLAYERS_STEALTH);
                break;
        }

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ile osob zostalo?", GOSSIP_SENDER_MAIN, CACTION_PLAYERS_COUNT);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Kto zostal?", GOSSIP_SENDER_MAIN, CACTION_PLAYERS_NAMES);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Lista Gmow monitorujacych event", GOSSIP_SENDER_MAIN, CACTION_GM_NAMES);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Resetuj stan eventu", GOSSIP_SENDER_MAIN, CACTION_RESET_EVENT);


        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        switch (action)
        {
            case CACTION_START_EVENT:
                sCustomEventMgr->startHungerGamesEvent(HUNGER_GAMES_EVENT_TELE);
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_REVIVE_PLAYERS:
                sCustomEventMgr->startHungerGamesEvent(HUNGER_GAMES_EVENT_REV);
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_PLAYERS_COUNT:
            {
                std::string s = "Zostalo " + std::to_string(sCustomEventMgr->getHungerGamesPlayersCount()) + " osob";
                ChatHandler(player->GetSession()).PSendSysMessage(s.c_str());
                player->CLOSE_GOSSIP_MENU();
            }
            break;
            case CACTION_RESET_EVENT:
                sCustomEventMgr->resetHungerGamesState();
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_FREEZE_PLAYERS:
                sCustomEventMgr->startHungerGamesEvent(HUNGER_GAMES_EVENT_FR);
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_UNFREEZE_PLAYERS:
                sCustomEventMgr->startHungerGamesEvent(HUNGER_GAMES_EVENT_UNFR);
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_ADD_DEBUFF:
                sCustomEventMgr->startHungerGamesEvent(HUNGER_GAMES_EVENT_DEBUFF);
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_REMOVE_DEBUFF:
                sCustomEventMgr->applyHungerGamesDebuff(false);
                player->CLOSE_GOSSIP_MENU();
                break;
            case ACTION_QUIT:
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_TELEPORT_TO_HORDE:
                sCustomEventMgr->startHungerGamesEvent(HUNGER_GAMES_EVENT_TELE_HORDE);
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_SPAWN_ELITE:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Zespawnuj elite pod baza Alliance", GOSSIP_SENDER_MAIN, CACTION_SPAWN_ELITE_ALLY);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Zespawnuj elite pod baza Hordy", GOSSIP_SENDER_MAIN, CACTION_SPAWN_ELITE_HORDE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Zespawnuj elite po srodku", GOSSIP_SENDER_MAIN, CACTION_SPAWN_ELITE_MIDDLE);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                break;
            case CACTION_SPAWN_ELITE_ALLY:
                CAST_AI(npc_hunger_games_control::npc_hunger_games_controlAI, creature->GetAI())->spawnElite(0);
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_SPAWN_ELITE_HORDE:
                CAST_AI(npc_hunger_games_control::npc_hunger_games_controlAI, creature->GetAI())->spawnElite(1);
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_SPAWN_ELITE_MIDDLE:
                CAST_AI(npc_hunger_games_control::npc_hunger_games_controlAI, creature->GetAI())->spawnElite(2);
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_PLAYERS_NAMES:
                sCustomEventMgr->printHungerGamesPlayers(player);
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_GM_NAMES:
                sCustomEventMgr->printHungerGamesGms(player);
                player->CLOSE_GOSSIP_MENU();
                break;
            case CACTION_PLAYERS_STEALTH:
                sCustomEventMgr->printHungerGamesStealthedPlayers(player);
                player->CLOSE_GOSSIP_MENU();
                break;
        }

        return true;
    }

    struct npc_hunger_games_controlAI : public ScriptedAI 
    {
        npc_hunger_games_controlAI(Creature *creature) : ScriptedAI(creature) {}

        void spawnElite(uint8 loc) 
        {
            if (me->GetMapId() != 37) 
                return;

            if (loc >= 3) 
                return;
            
            if (Creature *c = me->SummonCreature(NPC_ELITE, elitePos[loc].m_positionX, elitePos[loc].m_positionY, elitePos[loc].m_positionZ, 0.f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 600000))
            {
                std::string msg = "Kozrum, the Hunger Giant, has emerged from the depths! He is under the ";

                switch (loc)
                {
                    case 0: //Alliance
                        msg += "Alliance base!";
                        break;
                    case 1: //Horde
                        msg += "Horde base!";
                        break;
                    case 2: //Middle
                        msg += "middle of Azshara Crater!";
                        break;
                }

                msg += " Get him quickly!";
                sCustomEventMgr->sendAnnounceToHungerGamesPlayers(msg);
                sCustomEventMgr->setPoiToHungerGamesPlayers(loc);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hunger_games_controlAI(creature);
    }

};

class player_script_hunger_games : public PlayerScript {
public:
    player_script_hunger_games() : PlayerScript("player_script_hunger_games") {}

    void OnPVPKill(Player* killer, Player* killed) override 
    {
        if (sCustomEventMgr->getHungerGamesState() == HUNGER_GAMES_NOT_STARTED || !killer || !killed || killed->GetMapId() != 37 || !sCustomEventMgr->isPlayerInHungerGames(killer->GetGUID())) 
            return;

        std::string msg = "Player " + killed->GetName() + " has been killed by player " + killer->GetName() + ". " + std::to_string(sCustomEventMgr->getHungerGamesPlayersCount() - 1) + " left!";
        sCustomEventMgr->sendAnnounceToHungerGamesPlayers(msg, true);
        sCustomEventMgr->removePlayerFromHungerGames(killed->GetGUID());
    }

    void OnPlayerKilledByCreature(Creature* killer, Player* killed) override 
    {
        if (sCustomEventMgr->getHungerGamesState() == HUNGER_GAMES_NOT_STARTED || !killer || !killed || !sCustomEventMgr->isPlayerInHungerGames(killed->GetGUID()) || killed->GetMapId() != 37)
            return;

        std::string msg = "Player " + killed->GetName() + " has been killed by creature " + killer->GetName() + ". " + std::to_string(sCustomEventMgr->getHungerGamesPlayersCount() - 1) + " left!";
        sCustomEventMgr->sendAnnounceToHungerGamesPlayers(msg, true);
        sCustomEventMgr->removePlayerFromHungerGames(killed->GetGUID());

    }

    void OnLogin(Player* player) override 
    {
        if (!player || sCustomEventMgr->getHungerGamesState() == HUNGER_GAMES_NOT_STARTED) 
            return;

        if (player->GetMapId() == 37)
            player->TeleportTo(player->m_homebindMapId, player->m_homebindX, player->m_homebindY, player->m_homebindZ, 0.f);
    }
    void OnLogout(Player* player) override
    {
        if (!player)
            return;

        if (sCustomEventMgr->isPlayerInHungerGames(player->GetGUID()))
        {
            if (sCustomEventMgr->getHungerGamesState() != HUNGER_GAMES_NOT_STARTED) {
                std::string msg = "Player " + player->GetName() + " has left Hunger Games. " + std::to_string(sCustomEventMgr->getHungerGamesPlayersCount() - 1) + " left!";
                sCustomEventMgr->sendAnnounceToHungerGamesPlayers(msg, true);
            }
            sCustomEventMgr->removePlayerFromHungerGames(player->GetGUID());
        }

        if (sCustomEventMgr->isGmInHungerGames(player->GetGUID()))
            sCustomEventMgr->removeGmFromHungerGames(player->GetGUID());
    }
    void OnMapChanged(Player* player) override
    {
        if (!player || sCustomEventMgr->getHungerGamesState() == HUNGER_GAMES_NOT_STARTED || player->GetMapId() == 37 || !sCustomEventMgr->isPlayerInHungerGames(player->GetGUID())) 
            return;

        std::string msg = "Player " + player->GetName() + " has left Hunger Games. " + std::to_string(sCustomEventMgr->getHungerGamesPlayersCount() - 1) + " left!";
        sCustomEventMgr->sendAnnounceToHungerGamesPlayers(msg, true);
        sCustomEventMgr->removePlayerFromHungerGames(player->GetGUID());
    }
};



class npc_gmisl_teleporter : public CreatureScript
{
public:
    npc_gmisl_teleporter() : CreatureScript("npc_gmisl_teleporter"){}

    bool OnGossipHello(Player* player, Creature* creature) 
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport me to GM Island.", GOSSIP_SENDER_MAIN, 1);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action) 
    {
        switch (action) {
            case 1:
                player->TeleportTo(1, 16226.20f, 16257.f, 13.2f, 1.65f);
                player->CLOSE_GOSSIP_MENU();
                break;
        }
        return true;
    }
};

const uint32 DeathKnightQuests[46] =
{
    12593,  // [In Service Of The Lich King]
    12619,  // [The Emblazoned Runeblade]
    12842,  // [Runeforging: Preparation For Battle]
    12848,  // [The Endless Hunger]
    12636,  // [The Eye Of Acherus]
    12641,  // [Death Comes From On High]
    12657,  // [The Might Of The Scourge]
    12850,  // [Report To Scourge Commander Thalanor]
    12670,  // [The Scarlet Harvest]
    12678,  // [If Chaos Drives, Let Suffering Hold The Reins]
    12680,  // [Grand Theft Palomino]
    12687,  // [Into the Realm of Shadows]
    12679,  // [Tonight We Dine In Havenshire]
    12733,  // [Death's Challenge]
    12711,  // [Abandoned Mail]
    12697,  // [Gothik the Harvester]
    12698,  // [The Gift That Keeps On Giving]
    12700,  // [An Attack Of Opportunity]
    12701,  // [Massacre At Light's Point]
    12706,  // [Victory At Death's Breach!]
    12714,  // [The Will Of The Lich King]
    12849,  // [The Power Of Blood, Frost And Unholy]
    12715,  // [The Crypt of Remembrance]
    12716,  // [The Plaguebringer's Request]
    12717,  // [Noth's Special Brew]
    12718,  // [More Skulls For Brew]
    12719,  // [Nowhere To Run And Nowhere To Hide]
    12722,  // [Lambs To The Slaughter]
    12720,  // [How To Win Friends And Influence Enemies]
    12723,  // [Behind Scarlet Lines]
    12724,  // [The Path Of The Righteous Crusader]
    12725,  // [Brothers In Death]
    12727,  // [Bloody Breakout]
    12738,  // [A Cry For Vengeance!]
    12743,  // [A Special Surprise]
    12751,  // [A Sort Of Homecoming]
    12754,  // [Ambush At The Overlook]
    12755,  // [A Meeting With Fate]
    12756,  // [The Scarlet Onslaught Emerges]
    12757,  // [Scarlet Armies Approach...]
    12778,  // [The Scarlet Apocalypse]
    12779,  // [An End To All Things...]
    12800,  // [The Lich King's Command]
    12801,  // [The Light of Dawn]
    13165,  // [Taking Back Acherus]
    13166   // [The Battle For The Ebon Hold]
};

enum TestNpcData 
{
    COMPLETE_DK_CHAIN    = 0,
    TEACH_WEAPON_SKILLS  = 1,
    TEACH_RIDING         = 2,
};

enum skills
{
    CHECK_SKILL_ONE_HAND_AXE   = 196,
    CHECK_SKILL_TWO_HAND_AXE   = 197,
    CHECK_SKILL_ONE_HAND_MACE  = 198,
    CHECK_SKILL_TWO_HAND_MACE  = 199,
    CHECK_SKILL_POLEARMS       = 200,
    CHECK_SKILL_ONE_HAND_SWORD = 201,
    CHECK_SKILL_TWO_HAND_SWORD = 202,
    CHECK_SKILL_STAVES         = 227,
    CHECK_SKILL_BOWS           = 264,
    CHECK_SKILL_GUNS           = 266,
    CHECK_SKILL_DAGGERS        = 1180,
    CHECK_SKILL_THROWNS        = 2567,
    CHECK_SKILL_WANDS          = 5009,
    CHECK_SKILL_CROSSBOWS      = 5011,
    CHECK_SKILL_FIST           = 15590,
    CHECK_SKILL_PLATE          = 750,
    CHECK_SKILL_MAIL           = 8737
};
enum riding
{
    MOUNT        = 38576,
    MOUNT_FLY    = 32458,
    RIDING_1     = 33388,
    RIDING_2     = 33391,
    RIDING_3     = 34090,
    RIDING_4     = 34091,
    COLD_WEATHER = 54197
};

class npc_test_server : CreatureScript 
{
public:
    npc_test_server() : CreatureScript("npc_test_server") {}

    bool OnGossipHello(Player* player, Creature* creature) override 
    {
        if (!sWorld->getBoolConfig(CONFIG_PTR_REALM))
            return false;

        if (player->getClass() == CLASS_DEATH_KNIGHT && !player->GetQuestRewardStatus(13166))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Complete Death Knight Chain (you will be kicked)", GOSSIP_SENDER_MAIN, COMPLETE_DK_CHAIN);

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teach me weapon skills.", GOSSIP_SENDER_MAIN, TEACH_WEAPON_SKILLS);

        if (!player->HasSpell(RIDING_1))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teach me riding", GOSSIP_SENDER_MAIN, TEACH_RIDING);

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action) override 
    {
        switch (action) 
        {
            case COMPLETE_DK_CHAIN:
                CompleteDeathKnightChain(player);
                player->GetSession()->KickPlayer(true);
            break;
            case TEACH_WEAPON_SKILLS:
                TeachWeaponSkills(player);
                player->CLOSE_GOSSIP_MENU();
                break;
            case TEACH_RIDING:
                player->learnSpell(RIDING_1);
                player->learnSpell(RIDING_2);
                player->learnSpell(RIDING_3);
                player->learnSpell(RIDING_4);
                player->learnSpell(COLD_WEATHER);
                player->AddItem(MOUNT, 1);
                player->AddItem(MOUNT_FLY, 1);
                player->CLOSE_GOSSIP_MENU();
                break;
        }
        return true;
    }

private:
    bool CompleteDeathKnightChain(Player *player) 
    {
            if (!player)
                return false;

            if (player->getClass() != CLASS_DEATH_KNIGHT)
                return false;

            PreparedStatement* stmt = NULL;
            SQLTransaction trans = CharacterDatabase.BeginTransaction();

            for (int i = 0; i < 47; i++)
            {
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_CHAR_QUESTSTATUS_REWARDED);
                stmt->setUInt32(0, player->GetGUIDLow());

                if (i < 46)
                    stmt->setUInt32(1, DeathKnightQuests[i]);
                else if (i == 46)
                {
                    if (player->GetTeamId() == TEAM_ALLIANCE)
                        stmt->setUInt32(1, 13188);
                    else
                        stmt->setUInt32(1, 13189);
                }

                trans->Append(stmt);
            }

            CharacterDatabase.CommitTransaction(trans);

            // Runeforging
            player->CastSpell(player, 53431, true);
            return true;
    }

    bool TeachWeaponSkills(Player* player)
    {
        if (!player)
            return false;

        switch (player->getClass())
        {
            case CLASS_DRUID:
            {
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_MACE))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_MACE);
                if (!player->HasSpell(CHECK_SKILL_POLEARMS))
                    player->learnSpell(CHECK_SKILL_POLEARMS);
                if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                    player->learnSpell(CHECK_SKILL_DAGGERS);
                if (!player->HasSpell(CHECK_SKILL_STAVES))
                    player->learnSpell(CHECK_SKILL_STAVES);

            } break;
            case CLASS_HUNTER:
            {
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_AXE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_AXE);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_SWORD))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_SWORD);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_AXE))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_AXE);
                if (!player->HasSpell(CHECK_SKILL_POLEARMS))
                    player->learnSpell(CHECK_SKILL_POLEARMS);
                if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                    player->learnSpell(CHECK_SKILL_DAGGERS);
                if (!player->HasSpell(CHECK_SKILL_BOWS))
                    player->learnSpell(CHECK_SKILL_BOWS);
                if (!player->HasSpell(CHECK_SKILL_GUNS))
                    player->learnSpell(CHECK_SKILL_GUNS);
                if (!player->HasSpell(CHECK_SKILL_CROSSBOWS))
                    player->learnSpell(CHECK_SKILL_CROSSBOWS);
                if (!player->HasSpell(CHECK_SKILL_STAVES))
                    player->learnSpell(CHECK_SKILL_STAVES);
                if (!player->HasSpell(CHECK_SKILL_MAIL))
                    player->learnSpell(CHECK_SKILL_MAIL);
            } break;
            case CLASS_MAGE:
            {
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                    player->learnSpell(CHECK_SKILL_DAGGERS);
                if (!player->HasSpell(CHECK_SKILL_STAVES))
                    player->learnSpell(CHECK_SKILL_STAVES);
                if (!player->HasSpell(CHECK_SKILL_WANDS))
                    player->learnSpell(CHECK_SKILL_WANDS);
            } break;
            case CLASS_PALADIN:
            {
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_AXE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_AXE);
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_SWORD))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_SWORD);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_AXE))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_AXE);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_MACE))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_MACE);
                if (!player->HasSpell(CHECK_SKILL_POLEARMS))
                    player->learnSpell(CHECK_SKILL_POLEARMS);
                if (!player->HasSpell(CHECK_SKILL_PLATE))
                    player->learnSpell(CHECK_SKILL_PLATE);
            } break;
            case CLASS_PRIEST:
            {
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                    player->learnSpell(CHECK_SKILL_DAGGERS);
                if (!player->HasSpell(CHECK_SKILL_STAVES))
                    player->learnSpell(CHECK_SKILL_STAVES);
                if (!player->HasSpell(CHECK_SKILL_WANDS))
                    player->learnSpell(CHECK_SKILL_WANDS);
            } break;
            case CLASS_ROGUE:
            {
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_AXE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_AXE);
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                    player->learnSpell(CHECK_SKILL_DAGGERS);
                if (!player->HasSpell(CHECK_SKILL_THROWNS))
                    player->learnSpell(CHECK_SKILL_THROWNS);
                if (!player->HasSpell(CHECK_SKILL_CROSSBOWS))
                    player->learnSpell(CHECK_SKILL_CROSSBOWS);
            } break;
            case CLASS_SHAMAN:
            {
                if (!player->HasSpell(CHECK_SKILL_FIST))
                    player->learnSpell(CHECK_SKILL_FIST);
                if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                    player->learnSpell(CHECK_SKILL_DAGGERS);
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                if (!player->HasSpell(CHECK_SKILL_STAVES))
                    player->learnSpell(CHECK_SKILL_STAVES);
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_AXE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_AXE);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_AXE))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_AXE);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_MACE))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_MACE);
                if (!player->HasSpell(CHECK_SKILL_MAIL))
                    player->learnSpell(CHECK_SKILL_MAIL);
            } break;
            case CLASS_WARLOCK:
            {
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                if (!player->HasSpell(CHECK_SKILL_DAGGERS))
                    player->learnSpell(CHECK_SKILL_DAGGERS);
                if (!player->HasSpell(CHECK_SKILL_STAVES))
                    player->learnSpell(CHECK_SKILL_STAVES);
                if (!player->HasSpell(CHECK_SKILL_WANDS))
                    player->learnSpell(CHECK_SKILL_WANDS);
            } break;
            case CLASS_WARRIOR:
            {
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_AXE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_AXE);
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_AXE))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_AXE);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_MACE))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_MACE);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_SWORD))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_SWORD);
                if (!player->HasSpell(CHECK_SKILL_POLEARMS))
                    player->learnSpell(CHECK_SKILL_POLEARMS);
                if (!player->HasSpell(CHECK_SKILL_BOWS))
                    player->learnSpell(CHECK_SKILL_BOWS);
                if (!player->HasSpell(CHECK_SKILL_THROWNS))
                    player->learnSpell(CHECK_SKILL_THROWNS);
                if (!player->HasSpell(CHECK_SKILL_GUNS))
                    player->learnSpell(CHECK_SKILL_GUNS);
                if (!player->HasSpell(CHECK_SKILL_CROSSBOWS))
                    player->learnSpell(CHECK_SKILL_CROSSBOWS);
                if (!player->HasSpell(CHECK_SKILL_PLATE))
                    player->learnSpell(CHECK_SKILL_PLATE);

            } break;
            case CLASS_DEATH_KNIGHT:
            {
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_AXE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_AXE);
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_MACE))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_MACE);
                if (!player->HasSpell(CHECK_SKILL_ONE_HAND_SWORD))
                    player->learnSpell(CHECK_SKILL_ONE_HAND_SWORD);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_AXE))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_AXE);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_MACE))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_MACE);
                if (!player->HasSpell(CHECK_SKILL_TWO_HAND_SWORD))
                    player->learnSpell(CHECK_SKILL_TWO_HAND_SWORD);
                if (!player->HasSpell(CHECK_SKILL_POLEARMS))
                    player->learnSpell(CHECK_SKILL_POLEARMS);

            } break;
        }
        player->UpdateSkillsToMaxSkillsForLevel();
        return true;
    }

};

enum ArenaSpectatorData
{
    GOSSIP_ACTION_2V2               = 1000,
    GOSSIP_ACTION_3V3               = 2000,
    GOSSIP_ACTION_5V5               = 3000,
    GOSSIP_ACTION_BACK              = 4000,
    GOSSIP_ACTION_SPECTATE_ARENA    = 1000000,

    GOSSIP_AS_MAIN                  = 1100000,
    GOSSIP_AS_NO_TEAMS              = 1100001,
    GOSSIP_AS_CHOOSE_TEAM           = 1100002,
    GOSSIP_AS_LEAVE_ARENA           = 1100003,

    ARENAS_PER_PAGE                 = 25,
};

class npc_arena_spectator : public CreatureScript
{
public:
    npc_arena_spectator() : CreatureScript("npc_arena_spectator") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        DisplayHelloGossips(player);
       
        player->SEND_GOSSIP_MENU(GOSSIP_AS_MAIN, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        ArenaType type;
        uint8 page;
        if (action == GOSSIP_ACTION_BACK)
        {
            DisplayHelloGossips(player);
            player->SEND_GOSSIP_MENU(GOSSIP_AS_MAIN, creature->GetGUID());
            return true;
        }
        else if (action > GOSSIP_ACTION_SPECTATE_ARENA)
        {
            uint64 playerGuid = action - GOSSIP_ACTION_SPECTATE_ARENA;
            if (Player* arenaPlayer = sObjectAccessor->FindPlayer(playerGuid))
            {
                std::ostringstream os;
                os << ".spec spec " << arenaPlayer->GetName();
                ChatHandler(player->GetSession()).ParseCommands(os.str().c_str());
            }
            player->PlayerTalkClass->SendCloseGossip();
            return true;
        }
        else if (action >= GOSSIP_ACTION_5V5)
        {
            type = ARENA_TYPE_5v5;
            page = action - GOSSIP_ACTION_5V5;
        }
        else if (action >= GOSSIP_ACTION_3V3)
        {
            type = ARENA_TYPE_3v3;
            page = action - GOSSIP_ACTION_3V3;
        }
        else if (action >= GOSSIP_ACTION_2V2)
        {
            type = ARENA_TYPE_2v2;
            page = action - GOSSIP_ACTION_2V2;
        }
        uint32 size;
        if (DisplayArenas(player, type, page, size))
        {
            if (page != 0)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Show previous page", GOSSIP_SENDER_MAIN, action - 1);
            if (size > static_cast<uint32>((page+1) * ARENAS_PER_PAGE))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Show next page", GOSSIP_SENDER_MAIN, action + 1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_BACK);
            player->SEND_GOSSIP_MENU(GOSSIP_AS_CHOOSE_TEAM, creature->GetGUID());
        }
        else
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_BACK);
            player->SEND_GOSSIP_MENU(GOSSIP_AS_NO_TEAMS, creature->GetGUID());
        }
        return true;
    }

    bool DisplayArenas(Player* player, ArenaType type, uint8 page, uint32 &size)
    {
        BattlegroundContainer arenaContainer;
        
        uint32 begin = page * ARENAS_PER_PAGE;
        uint32 end = (page + 1) * ARENAS_PER_PAGE - 1;
        uint32 count = 0;
        if (sBattlegroundMgr->GetArenaListByType(arenaContainer, type))
        {
            size = arenaContainer.size();
            for (auto &arena : arenaContainer)
            {
                if (count < begin)
                {
                    ++count;
                    continue;
                }
                else if (count > end)
                    break;
                ++count;

                if (!arena.second)
                    continue;
                uint32 teamId1 = 0;
                uint32 teamId2 = 0;
                uint64 playerGuid = 0;

                // Get arena teams from players in arena
                for (auto &arenaPlayer : arena.second->GetPlayers())
                {
                    if (!arenaPlayer.second)
                        continue;
                    playerGuid = arenaPlayer.second->GetGUID();
                    uint32 teamId = arenaPlayer.second->GetArenaTeamId(ArenaTeam::GetSlotByType(type));
                    if (!teamId)
                        continue;

                    if (!teamId1)
                        teamId1 = teamId;
                    else if (teamId != teamId1)
                    {
                        teamId2 = teamId;
                        break;
                    }
                }
                ArenaTeam *arenaTeam1 = sArenaTeamMgr->GetArenaTeamById(teamId1);
                ArenaTeam *arenaTeam2 = sArenaTeamMgr->GetArenaTeamById(teamId2);
                if (!arenaTeam1 || !arenaTeam2)
                    continue;

                std::ostringstream os;
                os << arenaTeam1->GetName() << " (Rating: " << arenaTeam1->GetRating() << ") vs " << arenaTeam2->GetName() << " (Rating: " << arenaTeam2->GetRating() << ")";
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, os.str().c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_SPECTATE_ARENA + playerGuid);
            }
            return true;
        }
        return false;
    }

    void DisplayHelloGossips(Player* player)
    {
        player->PlayerTalkClass->ClearMenus();
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "2v2", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_2V2);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "3v3", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_3V3);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "5v5", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_5V5);
    }
};

class npc_arena_spectator_leave : public CreatureScript
{
public:
    npc_arena_spectator_leave() : CreatureScript("npc_arena_spectator_leave") {}
    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Yes", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "No", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(GOSSIP_AS_LEAVE_ARENA, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        switch(action)
        {
        case GOSSIP_ACTION_INFO_DEF:
            if (!player->IsSpectator() || !player->FindMap() || !player->FindMap()->IsBattleArena())
                return true;
            player->TeleportToEntryPoint();
            break;
        }
        player->PlayerTalkClass->SendCloseGossip();
        return true;
    }

    struct npc_arena_spectator_leaveAI : public ScriptedAI
    {
        npc_arena_spectator_leaveAI(Creature* creature) : ScriptedAI(creature) {}
        bool CanBeSeen(Player const* player)
        {
            return player->IsSpectator() || player->IsGameMaster();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_arena_spectator_leaveAI(creature);
    }
};

//! Make sure to make those NPCs immune to everything in DB
//! NPCs & PC as well
struct npc_custom_guild_bank_companion_AI : public ScriptedAI
{
    npc_custom_guild_bank_companion_AI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        //! test
        me->SetPassive();
        me->SetImmuneToAll(true);
        me->setFaction(35);
        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GUILD_BANKER);
        if (!me->ToTempSummon())
        {
            me->DespawnOrUnsummon();
            return;
        }

        if (Unit* owner = me->ToTempSummon()->GetSummoner())
            me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
        me->DespawnOrUnsummon(300s);
    }
};

struct WandererDalaranNPC
{
    uint32 guid;
    uint32 entry;
};

constexpr uint32 WANDERER_DALARAN_NPC_COUNT = 77;

const WandererDalaranNPC wandererDalaranNPCs[WANDERER_DALARAN_NPC_COUNT] =
{
    {12402,32720},{28686,32719},{85208,33938},{85210,33936},{85214,35471},{96496,32515},{97931,28691},{97932,29715},{97989,28692},{98070,28694},{98178,28697},
    {98346,28699},{98421,28700},{98866,28704},{99029,28706},{99201,28708},{100897,31031},{100940,29496},{101236,37776},{101356,29499},{101811,28990},{102033,28993},
    {102048,29505},{102070,28994},{102323,31557},{102325,28997},{102387,29254},{102397,29254},{102399,28742},{102417,29255},{102418,29255},{102419,29255},{102420,29255},
    {102427,29255},{102428,29255},{102430,29255},{102500,29512},{102516,32329},{102530,29513},{102606,29514},{102673,32332},{102693,32333},{102700,29261},{103296,29523},
    {104242,29533},{105534,29547},{105660,29548},{107612,29568},{111283,32675},{111306,32420},{111374,32677},{111461,32678},{111691,32679},{111719,32680},
    {111858,32681},{112052,32683},{112329,32685},{112385,32686},{112609,32688},{112639,32689},{112686,32690},{112852,32691},{112965,32693},{113397,30137},{114292,32706},
    {114331,32451},{114781,29640},{115281,32718},{116617,32216},{117830,32743},{119625,32251},{120324,32253},{133649,37780},{137702,36670},{207871,30567},{207873,30567},
    {249559,80003}
};

enum WandererData
{
    WANDERER_EVENT_CHECKHOUR        = 1,
    WANDERER_EVENT_CAST_FIRE        = 2,
    WANDERER_EVENT_SUMMON_SKELETON  = 3,
    WANDERER_EVENT_DESPAWN          = 4,
    WANDERER_EVENT_SAY              = 5,

    WANDERER_SPELL_FIRE             = 39199,
    WANDERER_SPELL_FEIGN_DEATH      = 71598,

    WANDERER_GOSSIP_HELLO           = 1110000,

    SKELETON_EVENT_CLEAVE           = 1,
    SKELETON_EVENT_FIRE_NOVA        = 2,

    SKELETON_SPELL_CLEAVE           = 20677,
    SKELETON_SPELL_FIRE_NOVA        = 68969,

    WANDERER_NPC_SKELETON           = 200001,
};

class npc_wanderer : public CreatureScript
{
public:
    npc_wanderer() : CreatureScript("npc_wanderer") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Who are you?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "***DEBUG*** Start event", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
        player->SEND_GOSSIP_MENU(WANDERER_GOSSIP_HELLO, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "What brings you here?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU(WANDERER_GOSSIP_HELLO + 1, creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Maybe I can help you?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->SEND_GOSSIP_MENU(WANDERER_GOSSIP_HELLO + 2, creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            player->SEND_GOSSIP_MENU(WANDERER_GOSSIP_HELLO + 3, creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 100:
            creature->GetAI()->DoAction(1);
            player->PlayerTalkClass->SendCloseGossip();
            break;
        }
        return true;
    }

    struct npc_wandererAI : public ScriptedAI
    {
        npc_wandererAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset() override
        {
            events.Reset();
            events.ScheduleEvent(WANDERER_EVENT_CHECKHOUR, 1s);
            events.ScheduleEvent(WANDERER_EVENT_SAY, 1min, 5min);
        }

        void DoAction(int32 /*param*/) override
        {
            StartEvent();
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);
            switch (events.GetEvent())
            {
            case WANDERER_EVENT_CHECKHOUR:
            {
                time_t now = time(nullptr);
                tm* aTm = localtime(&now);

                // Event should start at 10, 13, 16, 19, 22;
                if (aTm->tm_min == 0 && aTm->tm_hour > 9 && aTm->tm_hour < 23 && aTm->tm_hour % 3 == 1)
                    StartEvent();

                events.RescheduleEvent(WANDERER_EVENT_CHECKHOUR, 1min);
                break;
            }
            case WANDERER_EVENT_SAY:
                Talk(urand(0, 3));
                events.RescheduleEvent(WANDERER_EVENT_SAY, 1min, 5min);
                break;
            }
        }

        void StartEvent()
        {
            Talk(urand(4, 7));
            for (uint8 i = 0; i < 5; ++i)
            {
                uint32 id = urand(0, WANDERER_DALARAN_NPC_COUNT - 1);
                if (Unit* npc = sObjectAccessor->FindUnit(MAKE_NEW_GUID(wandererDalaranNPCs[id].guid, wandererDalaranNPCs[id].entry, HIGHGUID_UNIT)))
                {
                    if (npc->IsAIEnabled)
                        npc->GetAI()->DoAction(100);
                }
            }
        }

    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wandererAI(creature);
    }
};


class npc_wanderer_dalaranNPC : public CreatureScript
{
public:
    npc_wanderer_dalaranNPC() : CreatureScript("npc_wanderer_dalaranNPC") {}
    struct npc_wanderer_dalaranNPCAI : public ScriptedAI
    {
        npc_wanderer_dalaranNPCAI(Creature* creature) : ScriptedAI(creature) {}

        void DoAction(int32 param) override
        {
            if (param == 100)
            {
                me->CastSpell(me, WANDERER_SPELL_FEIGN_DEATH);
                events.ScheduleEvent(WANDERER_EVENT_CAST_FIRE, 2s);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);
            switch (events.GetEvent())
            {
            case WANDERER_EVENT_CAST_FIRE:
                me->CastSpell(me, WANDERER_SPELL_FIRE, true);
                events.ScheduleEvent(WANDERER_EVENT_SUMMON_SKELETON, 5s);
                events.PopEvent();
                break;
            case WANDERER_EVENT_SUMMON_SKELETON:
                if (Creature* c = me->SummonCreature(WANDERER_NPC_SKELETON, me->GetPosition()))
                {
                    if (Unit* victim = c->SelectNearestTarget(50.f, true))
                        c->CombatStart(victim);
                }
                me->DespawnOrUnsummon(5s);
                events.PopEvent();
                break;
            }
        }

    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wanderer_dalaranNPCAI(creature);
    }
};

class npc_wanderer_skeleton : public CreatureScript
{
public:
    npc_wanderer_skeleton() : CreatureScript("npc_wanderer_skeleton") {}
    struct npc_wanderer_skeletonAI : public ScriptedAI
    {
        npc_wanderer_skeletonAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset() override
        {
            events.Reset();
            events.ScheduleEvent(SKELETON_EVENT_CLEAVE, 5s, 10s);
            events.ScheduleEvent(SKELETON_EVENT_FIRE_NOVA, 10s, 15s);
        }

        void EnterEvadeMode() override
        {
            me->SetHealth(me->GetMaxHealth());
            Reset();
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);
            switch (events.GetEvent())
            {
            case SKELETON_EVENT_CLEAVE:
                me->CastSpell(me->GetVictim(), SKELETON_SPELL_CLEAVE);
                events.RescheduleEvent(SKELETON_EVENT_CLEAVE, 5s, 10s);
                break;
            case SKELETON_EVENT_FIRE_NOVA:
                me->CastCustomSpell(SKELETON_SPELL_FIRE_NOVA, SPELLVALUE_RADIUS_MOD, 5000, me->GetVictim());
                events.RescheduleEvent(SKELETON_EVENT_FIRE_NOVA, 5s, 10s);
                break;
            }

            DoMeleeAttackIfReady();
        }

    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wanderer_skeletonAI(creature);
    }
};

void AddSC_npcs_custom()
{
    new npc_schody();
    // new npc_lore();
    new npc_dala_tele();
    new npc_hunger_games();
    new npc_hunger_games_control();
    new player_script_hunger_games();
    new npc_gmisl_teleporter();
    new npc_test_server();
    new npc_arena_spectator();
    new npc_arena_spectator_leave();
    new CreatureAILoader<npc_custom_guild_bank_companion_AI>("npc_custom_guild_bank_companion");
    new npc_wanderer();
    new npc_wanderer_dalaranNPC();
    new npc_wanderer_skeleton();
}