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

/*######
## npc_schody
## Not used now.


#define PASS "I want to use the entry ticket!"

class npc_schody : public CreatureScript
{
public:
    npc_schody() : CreatureScript("npc_schody") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!sWorld->getBoolConfig(CONFIG_CUSTOM_EVENT_ENABLE))
            return false;

        if (creature->GetEntry() != 99004 && creature->GetEntry() < 99006)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Entry ticket, please!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        else if (creature->GetEntry() != 99004 && creature->GetEntry() >= 99006)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Check point ticket, please!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        if (creature->GetEntry() == 99000 && player->HasItemCount(86001))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, PASS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

        if (creature->GetEntry() == 99001 && player->HasItemCount(86002))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, PASS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

        if (creature->GetEntry() == 99002 && player->HasItemCount(86003))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, PASS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);

        if (creature->GetEntry() == 99003 && player->HasItemCount(86003))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, PASS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);

        if (creature->GetEntry() == 99004)
        {
            player->SEND_GOSSIP_MENU(999001, creature->GetGUID());
            if (player->HasItemCount(86004))
            {
                sLog->outRewards("Player: %s GUID: %u has complete event 'Schody do nieba'", player->GetName().c_str(), player->GetGUIDLow());
                sWorld->SendWorldText(11050, player->GetName().c_str());
                sWorld->SendWorldText(11051, player->GetName().c_str());

                for (uint8 i = 0; i < 4; i++)
                    if (player->HasItemCount(86001 + i, 1, false))
                        player->DestroyItemCount(86001 + i, 1, true);
            }
        }
        else player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            // Give player a pass
            case GOSSIP_ACTION_INFO_DEF + 1:
            {
                if (creature->GetEntry() == 99000 && !player->HasItemCount(86001))
                    player->AddItem(86001, 1);
                else if (creature->GetEntry() == 99001 && player->HasItemCount(86001))
                    player->AddItem(86002, 1);
                else if (creature->GetEntry() == 99002 && player->HasItemCount(86002))
                    player->AddItem(86003, 1);
                else if (creature->GetEntry() == 99003 && player->HasItemCount(86003))
                    player->AddItem(86004, 1);
                else if (creature->GetEntry() == 99006)
                    player->AddItem(86005, 1);
                else if (creature->GetEntry() == 99007)
                    player->AddItem(86006, 1);
                else if (creature->GetEntry() == 99008)
                    player->AddItem(86007, 1);
                else if (creature->GetEntry() == 99009)
                    player->AddItem(86008, 1);
            }
            break;
            // Teleport player
            case GOSSIP_ACTION_INFO_DEF + 2:
            {
                if (player->HasItemCount(86001))
                    player->TeleportTo(1, 5249.313965f, -1473.966064f, 1360.240723f, player->GetOrientation());
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 3:
            {
                if (player->HasItemCount(86002))
                    player->TeleportTo(0, 4241.554199f, -2741.025879f, 9.378314f, player->GetOrientation());
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 4:
            {
                if (player->HasItemCount(86003))
                    player->TeleportTo(0, -1858.023071f, -4262.541992f, 12.328624f, player->GetOrientation());
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 5:
            {
                if (player->HasItemCount(86004))
                    player->TeleportTo(1, 5262.578125f, -2170.639160f, 1259.369141f, player->GetOrientation());
            }
            break;
            }
        player->PlayerTalkClass->SendCloseGossip();
        return true;
    }
};

######*/

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
## Not used now.

class npc_dala_tele : public CreatureScript
{
public:
    npc_dala_tele() : CreatureScript("npc_dala_tele") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!player->HasItemCount(86001) &&
            !player->HasItemCount(86002) &&
            !player->HasItemCount(86003) &&
            !player->HasItemCount(86004))
        {
            player->TeleportTo(571, 5804.149902f, 624.770996f, 647.767029f, 1.640000f);
            return true;
        }
        return false;
    }
};

######*/

////////////////////////////
// Hunger Games Event
// Currently not used!
///////////////////////////

/*
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
        if (player->getLevel() < 80) 
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

***/

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
        if (!sWorld->getBoolConfig(CONFIG_TEST_SERVER_ENABLE))
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

void AddSC_npcs_custom()
{
    // new npc_schody();
    // new npc_lore();
    // new npc_dala_tele();
    // new npc_hunger_games();
    // new npc_hunger_games_control();
    // new player_script_hunger_games();
    new npc_gmisl_teleporter();
    new npc_test_server();
}