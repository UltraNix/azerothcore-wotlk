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
#include "Lottery.h"

/*######
## npc_lottery_teleporter
######*/

enum LotteryTeleporter {
 
    TELE_TO_CAVE      = 1,
    TELE_TO_DUEL      = 2,
    TELE_TO_KARAZAN   = 3,
    TELE_TO_CAVE_FREE = 4,

    STORY             = 5,
    CLOSE             = 6,
    NPC_WELL          = 91000,
    NPC_HAZARD        = 91001,
    NPC_DUEL          = 91002,

    NPC_TEXT_0        = 1000000,
    NPC_TEXT_1        = 1000001,
    NPC_TEXT_2        = 1000002,
    NPC_TEXT_3        = 1000003,

    TRANSPARENCY      = 44816,
    SPOT_LIGHT        = 34126
};

class npc_lottery_teleporter : public CreatureScript
{
public:
    npc_lottery_teleporter() : CreatureScript("npc_lotery_teleporter") { }

    struct npc_hazard_teleporterAI : public ScriptedAI
    {
        npc_hazard_teleporterAI(Creature* creature) : ScriptedAI(creature)
        {
            creature->CastSpell(creature, TRANSPARENCY);
            creature->CastSpell(creature, SPOT_LIGHT);
        }
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE))
        {
            if (creature->GetEntry() == NPC_WELL)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Ok, pokaz mi to miejsce. (10 Gold)", GOSSIP_SENDER_MAIN, TELE_TO_CAVE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Rozmyslilem sie.", GOSSIP_SENDER_MAIN, CLOSE);
                player->SEND_GOSSIP_MENU(NPC_TEXT_0, creature->GetGUID());
            }
            if (creature->GetEntry() == NPC_HAZARD)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Zabierz mnie pod Karazhan.", GOSSIP_SENDER_MAIN, TELE_TO_KARAZAN);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Co to w ogole za miejsce?", GOSSIP_SENDER_MAIN, STORY);
                player->SEND_GOSSIP_MENU(NPC_TEXT_1, creature->GetGUID());
            }
            if (creature->GetEntry() == NPC_DUEL)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Zabierz mnie z powrotem do Dziupli.", GOSSIP_SENDER_MAIN, TELE_TO_CAVE_FREE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Zabierz mnie pod Karazhan.", GOSSIP_SENDER_MAIN, TELE_TO_KARAZAN);
                player->SEND_GOSSIP_MENU(NPC_TEXT_3, creature->GetGUID());
            }
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case TELE_TO_CAVE:
                if (player->HasEnoughMoney(100000))
                {
                    player->ModifyMoney(-100000);
                    player->TeleportTo(0, -11227.597656f, -1776.532471f, 4.251500f, 4.754688f);
                }
                else creature->MonsterWhisper("Wroc jak bedziesz mial wystarczajaca ilosc zlota!", player);
                break;
            case TELE_TO_CAVE_FREE:
                player->TeleportTo(0, -11227.597656f, -1776.532471f, 4.251500f, 4.754688f);
                break;
            case TELE_TO_KARAZAN:
                player->TeleportTo(0, -11131.884766f, -2030.862305f, 47.077274f, 4.572960f);
                break;
            case STORY:
                player->SetSelectedAuction(STORY);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Juz wiem wszystko!", GOSSIP_SENDER_MAIN, CLOSE);
                player->SEND_GOSSIP_MENU(NPC_TEXT_2, creature->GetGUID());            
                break;
            case CLOSE:
                player->CLOSE_GOSSIP_MENU();
                break;
            default:
                player->CLOSE_GOSSIP_MENU();
                break;
        }
        return false;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hazard_teleporterAI(creature);
    }
};

/*######
## npc_lottery_maker
######*/

enum LotteryBase
{
    GOLD_LOTERRY                   = 1,
    SC_LOTTERY                     = 3,
    SPECTRAL_TIGER_LOTTERY         = 5,
    BATTLE_TANK_LOTTERY            = 7,
    BATTLE_TANK_FLYING_LOTTERY     = 9,
    BLAZING_HIPPOGRYPH_LOTTERY     = 11,
    CELESTIAL_STEED_LOTTERY        = 13,
    RANDOM_PETS_LOTTERY            = 15,
    SHOW_NUMBERS                   = 17,

    GOLD_LOTERRY_NPC               = 91003,
    SC_LOTTERY_NPC                 = 91004,
    SPECTRAL_TIGER_LOTTERY_NPC     = 91005,
    BATTLE_TANK_LOTTERY_NPC        = 91006,
    BATTLE_TANK_FLYING_LOTTERY_NPC = 91007,
    BLAZING_HIPPOGRYPH_LOTTERY_NPC = 91008,
    CELESTIAL_STEED_LOTTERY_NPC    = 91009,
    RANDOM_PETS_LOTTERY_NPC        = 91010,

    NPC_GREETINGS_01               = 1000009,
    NPC_GREETINGS_02               = 1000010,
    NPC_GREETINGS_03               = 1000011,
    NPC_GREETINGS_04               = 1000012,
    NPC_GREETINGS_05               = 1000013,
    NPC_GREETINGS_06               = 1000014,
    NPC_GREETINGS_07               = 1000015,
    NPC_GREETINGS_08               = 1000016,
    NPC_LOSE                       = 1000017,
    NPC_WON                        = 1000018,
    LEAVE                          = 1000019,

    SPECTRAL_TIGER                 = 33225,
    BATTLE_TANK                    = 21176,
    BATTLE_TANK_FLYING             = 64999,
    BLAZING_HIPPOGRYPH             = 54069,
    CELESTIAL_STEED                = 54811,
};

#define MOUNT_WIN_PERCENT 5.0f
#define PET_WIN_PERCENT 10.0f

uint32 pets[] = {39286, 49343, 49693, 13584, 54847};
std::string randomWinQuotes[] = {"W koncu!", "Nie moge w to uwierzyc.", "Dlugo na to czekalem...", "Tylko na to czekalem.", "Tylko o tym marzylem!"};
std::string randomLoseQuotes[] = {"Moze nastepnym razem.", "Kiedys mi sie uda.", "Za kazdym wydanym razem.", "Doszlifuje moje szczesicie.", "Raz sie przegrywa, a raz przegrywa."};

class npc_lottery_maker : public CreatureScript
{
public:
    npc_lottery_maker() : CreatureScript("npc_lotery_maker") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();

        if (sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE))
        {
            switch (creature->GetEntry())
            {
                case SPECTRAL_TIGER_LOTTERY_NPC:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Uda mi sie! (250 Lottery Coins)", GOSSIP_SENDER_MAIN, SPECTRAL_TIGER_LOTTERY);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nie jestem pewien...", GOSSIP_SENDER_MAIN, LEAVE);
                    player->SEND_GOSSIP_MENU(NPC_GREETINGS_03, creature->GetGUID());
                    break;
                case BATTLE_TANK_LOTTERY_NPC:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Lubie ryzyko. (450 Lottery Coins)", GOSSIP_SENDER_MAIN, BATTLE_TANK_LOTTERY);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "To nie dla mnie...", GOSSIP_SENDER_MAIN, LEAVE);
                    player->SEND_GOSSIP_MENU(NPC_GREETINGS_04, creature->GetGUID());
                    break;
                case BATTLE_TANK_FLYING_LOTTERY_NPC:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Sprobujmy.. (600 Lottery Coins)", GOSSIP_SENDER_MAIN, BATTLE_TANK_FLYING_LOTTERY);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nie teraz...", GOSSIP_SENDER_MAIN, LEAVE);
                    player->SEND_GOSSIP_MENU(NPC_GREETINGS_05, creature->GetGUID());
                    break;
                case BLAZING_HIPPOGRYPH_LOTTERY_NPC:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Oczywiscie, ze mam. (300 Lottery Coins)", GOSSIP_SENDER_MAIN, BLAZING_HIPPOGRYPH_LOTTERY);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nie wiem... Chyba nie.", GOSSIP_SENDER_MAIN, LEAVE);
                    player->SEND_GOSSIP_MENU(NPC_GREETINGS_06, creature->GetGUID());
                    break;
                case CELESTIAL_STEED_LOTTERY_NPC:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Zagram o niego. (270 Lottery Coins)", GOSSIP_SENDER_MAIN, CELESTIAL_STEED_LOTTERY);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Poki co podziekuje.", GOSSIP_SENDER_MAIN, LEAVE);
                    player->SEND_GOSSIP_MENU(NPC_GREETINGS_07, creature->GetGUID());
                    break;
                case RANDOM_PETS_LOTTERY_NPC:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Pewnie. (75 Lottery Coins)", GOSSIP_SENDER_MAIN, RANDOM_PETS_LOTTERY);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nie.", GOSSIP_SENDER_MAIN, LEAVE);
                    player->SEND_GOSSIP_MENU(NPC_GREETINGS_08, creature->GetGUID());
                    break;
            }
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case SPECTRAL_TIGER_LOTTERY:
                randomMount(player, creature, SPECTRAL_TIGER, 250);
                break;
            case BATTLE_TANK_LOTTERY:
                randomMount(player, creature, BATTLE_TANK, 450);
                break;
            case BATTLE_TANK_FLYING_LOTTERY:
                randomMount(player, creature, BATTLE_TANK_FLYING, 600);
                break;
            case BLAZING_HIPPOGRYPH_LOTTERY:
                randomMount(player, creature, BLAZING_HIPPOGRYPH, 300);
                break;
            case CELESTIAL_STEED_LOTTERY:
                randomMount(player, creature, CELESTIAL_STEED, 270);
                break;
            case RANDOM_PETS_LOTTERY:
                randomMount(player, creature, pets[urand(0,4)], 75, true);
                break;
            case CLOSE:
            case LEAVE:
                default:
                player->PlayerTalkClass->ClearMenus();
                OnGossipHello(player, creature);
                break;
        }
        return false;
    }

    void randomMount(Player* player, Creature* creature, uint32 itemId, uint32 cost, bool isPetLottery = false) 
    {
        if (Lottery::hasLotteryPoints(player, cost)) 
        {
            Lottery::modifyLotteryPoints(player, -int32(cost));

            float winChance;
            if (isPetLottery) 
                winChance = PET_WIN_PERCENT;
            else 
                winChance = MOUNT_WIN_PERCENT;

            if (!Lottery::randomItemWithPercent(player, itemId, winChance)) 
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, randomLoseQuotes[urand(0,4)], GOSSIP_SENDER_MAIN, CLOSE);
                player->SEND_GOSSIP_MENU(NPC_LOSE, creature->GetGUID());
            }
            else
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, randomWinQuotes[urand(0,4)], GOSSIP_SENDER_MAIN, CLOSE);
                player->SEND_GOSSIP_MENU(NPC_WON, creature->GetGUID());
            }
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            creature->MonsterWhisper("Wroc jak bedzie mial wystarczajaca ilosc monet!", player);
        }
    }
};

/*######
## npc_lotery_number
######*/

#define EVENT_GOLD_LOTTERY		        132 // Use '.event start 132' or '.event stop 132' to start and stop manually. Event will start automatically every 24h (08:00pm)
#define EVENT_SUNWELL_COINS_LOTTERY		133 // Use '.event start 132' or '.event stop 132' to start and stop manually. Event will start automatically every 24h (08:00pm)

class npc_lotery_number : public CreatureScript
{
public:
    npc_lotery_number() : CreatureScript("npc_lotery_number") { }

    struct npc_lotery_numberAI : public ScriptedAI
    {
        npc_lotery_numberAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        void UpdateAI(uint32 diff)
        {
            if (IsEventActive(EVENT_GOLD_LOTTERY))
            {
                if (me->IsVisible())
                    me->SetVisible(false);

                Lottery::findWinners(me, GOLD_LOTTERY);
            }
            if (IsEventActive(EVENT_SUNWELL_COINS_LOTTERY))
            {
                if (me->IsVisible())
                    me->SetVisible(false);

                Lottery::findWinners(me, SUNWELL_COINS_LOTTERY);
            }
            else me->SetVisible(true);
        }
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();

        if (sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE))
        {
            switch (creature->GetEntry())
            {
                case GOLD_LOTERRY_NPC:
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Gram (50 Lottery Coins)", GOSSIP_SENDER_MAIN, GOLD_LOTERRY, "Wpisz liczby od 1 do 25", 0, true);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Pokaz mi moje numery", GOSSIP_SENDER_MAIN, SHOW_NUMBERS);
                    player->SEND_GOSSIP_MENU(NPC_GREETINGS_01, creature->GetGUID());
                    break;
                case SC_LOTTERY_NPC:
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Oczywiscie (10 Sunwell Coins)", GOSSIP_SENDER_MAIN, SC_LOTTERY, "Wpisz liczby od 1 do 25", 0, true);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Pokaz mi moje numery", GOSSIP_SENDER_MAIN, SHOW_NUMBERS);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Wroce pozniej.", GOSSIP_SENDER_MAIN, LEAVE);
                    player->SEND_GOSSIP_MENU(NPC_GREETINGS_02, creature->GetGUID());
                    break;
            }
        }
        return true;
    }

    bool OnGossipSelectCode(Player* player, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char* code)
    {
        player->PlayerTalkClass->ClearMenus();

        if (uiSender == GOSSIP_SENDER_MAIN)
        {
            switch (uiAction) 
            {
                case GOLD_LOTERRY: 
                {
                    if (!Lottery::hasLotteryPoints(player, LOTTERY_COINS_BETCOST))
                    {
                        player->CLOSE_GOSSIP_MENU();
                        pCreature->MonsterWhisper("Wroc jak bedzie mial wystarczajaca ilosc monet!", player);
                        return false;
                    }
                    if (Lottery::AddNumbers(code, player, pCreature, GOLD_LOTTERY))
                        Lottery::modifyLotteryPoints(player, -LOTTERY_COINS_BETCOST);
                    break;
                }
                case SC_LOTTERY:
                    if (!Lottery::hasSunwellPoints(player, LOTTERY_SC_BETCOST))
                    {
                        player->CLOSE_GOSSIP_MENU();
                        pCreature->MonsterWhisper("Wroc jak bedzie mial wystarczajaco Sunwell Coins!", player);
                        return false;
                    }
                    if (Lottery::AddNumbers(code, player, pCreature, SUNWELL_COINS_LOTTERY))
                        Lottery::modifySunwellPoints(player, -LOTTERY_SC_BETCOST);
                    break;
            }
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case SHOW_NUMBERS:
                Lottery::showNumbers(creature, player, (creature->GetEntry() == GOLD_LOTERRY_NPC) ? GOLD_LOTTERY : SUNWELL_COINS_LOTTERY);
                return false;
            case CLOSE:
            case LEAVE:
            default:
                player->CLOSE_GOSSIP_MENU();
                break;
        }
        return false;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_lotery_numberAI(pCreature);
    }
};

/*######
## npc_lotery_coins
######*/

enum Coins 
{
    BACK             = 1,
    ADD_25_LC_SC     = 5,
    ADD_75_LC_SC     = 13,
    ADD_150_LC_SC    = 25,
    ADD_500_LC_SC    = 90,
    GOLDY            = 7,
    SC               = 6,
    ADD_25_LC_G      = 50,
    ADD_75_LC_G      = 140,
    ADD_150_LC_G     = 270,
    ADD_500_LC_G     = 920,
 
    TEXT_WELCOME     = 1000019,
    TEXT_END         = 1000020,
    TEXT_NEXT        = 1000021,

    NPC              = 92006,
};

class npc_lotery_coins : public CreatureScript {
public:
    npc_lotery_coins() : CreatureScript("npc_lottery_coins") {}

    bool OnGossipHello(Player* player, Creature* creature) 
    {
        if (sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE))
        {
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tak, za zloto.", GOSSIP_SENDER_MAIN, GOLDY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tak, za Sunwell Coins.", GOSSIP_SENDER_MAIN, SC);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Jednak nie.", GOSSIP_SENDER_MAIN, LEAVE);
            player->SEND_GOSSIP_MENU(TEXT_WELCOME, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case GOLDY: 
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "<25 Lottery Coins (50 golda)>", GOSSIP_SENDER_MAIN, ADD_25_LC_G);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "<75 Lottery Coins (140 golda)>", GOSSIP_SENDER_MAIN, ADD_75_LC_G);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "<150 Lottery Coins (270 golda)>", GOSSIP_SENDER_MAIN, ADD_150_LC_G);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "<500 Lottery Coins (920 golda)>", GOSSIP_SENDER_MAIN, ADD_500_LC_G);
                player->SEND_GOSSIP_MENU(TEXT_NEXT, creature->GetGUID());
                break;
            }
            case SC: 
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "<25 Lottery Coins (5 Sunwell Coins)>", GOSSIP_SENDER_MAIN, ADD_25_LC_SC);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "<75 Lottery Coins (13 Sunwell Coins)>", GOSSIP_SENDER_MAIN, ADD_75_LC_SC);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "<150 Lottery Coins (25 Sunwell Coins)>", GOSSIP_SENDER_MAIN, ADD_150_LC_SC);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "<500 Lottery Coins (90 Sunwell Coins)>", GOSSIP_SENDER_MAIN, ADD_500_LC_SC);
                player->SEND_GOSSIP_MENU(TEXT_NEXT, creature->GetGUID());
                break;
            }
            case ADD_25_LC_G:
            case ADD_75_LC_G:
            case ADD_150_LC_G:
            case ADD_500_LC_G:
            {
                if (player->HasEnoughMoney(action * 10000)) 
                {
                    player->ModifyMoney(-(int32(action)) * 10000);
                    uint32 lotteryCoins;

                    if (action == ADD_25_LC_G)  lotteryCoins = 25;
                    if (action == ADD_75_LC_G)  lotteryCoins = 75;
                    if (action == ADD_150_LC_G) lotteryCoins = 150;
                    if (action == ADD_500_LC_G) lotteryCoins = 500;
                    Lottery::modifyLotteryPoints(player, lotteryCoins);

                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "<Jeszcze chcialbym...>", GOSSIP_SENDER_MAIN, BACK);
                    player->SEND_GOSSIP_MENU(TEXT_END, creature->GetGUID());
                }
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterWhisper("Wroc jak bedzie mial wystarczajaca ilosc zlota!", player);
                }
                break;
            }
            case ADD_25_LC_SC:
            case ADD_75_LC_SC:
            case ADD_150_LC_SC:
            case ADD_500_LC_SC:
            {
                if (Lottery::hasSunwellPoints(player, action))
                {
                    Lottery::modifySunwellPoints(player, -(int32(action)));
                    uint32 lotteryCoins;

                    if (action == ADD_25_LC_SC)  lotteryCoins = 25;
                    if (action == ADD_75_LC_SC)  lotteryCoins = 75;
                    if (action == ADD_150_LC_SC) lotteryCoins = 150;
                    if (action == ADD_500_LC_SC) lotteryCoins = 500;

                    Lottery::modifyLotteryPoints(player, lotteryCoins);

                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "<Jeszcze chcialbym...>", GOSSIP_SENDER_MAIN, BACK);
                    player->SEND_GOSSIP_MENU(TEXT_END, creature->GetGUID());
                }
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterWhisper("Wroc jak bedzie mial wystarczajaca ilosc zlota!", player);
                }
                break;
            }
            case LEAVE:
                player->CLOSE_GOSSIP_MENU();
                break;
            case BACK:
            default:
                player->PlayerTalkClass->ClearMenus();
                OnGossipHello(player, creature);
                break;
        }
        return false;
    }
};

/*######
## npc_wypierdalator
## ~by Piootrek
######*/

class npc_wypierdalator : public CreatureScript
{
public:
    npc_wypierdalator() : CreatureScript("npc_wypierdalator") { }

    struct npc_wypierdalatorAI : public ScriptedAI
    {
        npc_wypierdalatorAI(Creature* creature) : ScriptedAI(creature)
        {
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            creature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_NORMAL, true);
            creature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_MAGIC, true);
            creature->SetVisible(false);
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!who || !who->IsInWorld())
                return;

            if (!me->IsWithinDist(who, 40.0f, false))
                return;

            if (Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                if (player->IsGameMaster() || player->IsBeingTeleported() || player->GetPositionZ() > 0.0f || player->GetPositionZ() < -25.0f)
                    return;

                player->TeleportTo(0, -11215.127930f, -1777.774292f, 4.252191f, 4.792066f);
                me->SetOrientation(me->GetHomePosition().GetOrientation());
            }
        }

        void Reset() { checkTimer = 1000; }

        void UpdateAI(uint32 diff)
        {
            if (checkTimer <= diff)
            {
                Map* map = me->GetMap();
                Map::PlayerList const &PlayerList = map->GetPlayers();

                if (!PlayerList.isEmpty())
                {
                    for (Map::PlayerList::const_iterator itr = PlayerList.begin(); itr != PlayerList.end(); ++itr)
                    {
                        if (Player* plr = itr->GetSource())
                            if (plr->IsWithinDist(me, 100.0f, false))
                                Ressurect(plr);
                    }
                }
                checkTimer = 1000;
            }
            else
                checkTimer -= diff;
        }

        void Ressurect(Player* player)
        {
             if (!player || player->GetTypeId() != TYPEID_PLAYER)
                return;

            if (player->IsAlive() || !player->IsInWorld())
                return;

            if (Player* target = player->ToPlayer())
            {
                target->ResurrectPlayer(!AccountMgr::IsPlayerAccount(player->GetSession()->GetSecurity()) ? 1.0f : 0.5f);
                target->SpawnCorpseBones();
                target->SaveToDB(false, false);
            }
        }

   private:
        uint32 checkTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wypierdalatorAI(creature);
    }
};

/*######
## npc_hazard_wpierdalator
######*/

enum WpierdalatorEnums { WPIERDALATOR_HELLO_TEXT = 1000031 };

class npc_wpierdalator : public CreatureScript
{
public:
    npc_wpierdalator() : CreatureScript("npc_wpierdalator") { }

    struct npc_wpierdalatorAI : public ScriptedAI
    {
        npc_wpierdalatorAI(Creature* creature) : ScriptedAI(creature)
        {
            creature->CastSpell(creature, TRANSPARENCY);
        }
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tak, zabierz mnie do Mordowni.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nie.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU(WPIERDALATOR_HELLO_TEXT, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->TeleportTo(0, -11215.13f, -1779.58f, 4.25f, 4.77f);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                break;
        }

        player->CLOSE_GOSSIP_MENU();
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wpierdalatorAI(creature);
    }

};

/*######
## npc_crypt_tele
######*/

enum CryptTeleEnums { CRYPT_TELEPORTER_HELLO_TEXT = 1000023 };

class npc_crypt_tele : public CreatureScript
{
public:
    npc_crypt_tele() : CreatureScript("npc_crypt_tele") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Wiem, inaczej bym tu nie przychodzil. (50 Gold)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Brzmi interesujaco, ale na razie odpuszcze.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU(CRYPT_TELEPORTER_HELLO_TEXT, creature->GetGUID());
        }

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (!player->HasEnoughMoney(50 * GOLD))
                {
                    creature->MonsterWhisper("Nie rozsmieszaj mnie! Wroc, jak bedziesz mial zloto.", player);
                    break;
                }

                player->ModifyMoney((-50 * GOLD));
                player->TeleportTo(0, -11068.243f, -1811.258f, 52.831f, 1.58f);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                break;
        }

        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

/*######
## npc_burn_flag_horde
######*/

enum BurningFlag
{
    EVENT_BURNING_FLAG = 1,
    EVENT_RESTORE_FLAG = 2,

    BANNER_ALLIANCE    = 192423,
    BANNER_HORDE       = 192289,

    HORDE_HELLO_TEXT    = 1000028,
    ALLIANCE_HELLO_TEXT = 1000029
};

class npc_burn_flag_horde : public CreatureScript
{
public:
    npc_burn_flag_horde() : CreatureScript("npc_burn_flag_horde") { }

    struct npc_burn_flag_hordeAI : public ScriptedAI
    {
        npc_burn_flag_hordeAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        void SetFlagResetTimer()
        {
            events.ScheduleEvent(EVENT_BURNING_FLAG, 1000);
            events.ScheduleEvent(EVENT_RESTORE_FLAG, 600000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            switch (events.ExecuteEvent())
            {
                case EVENT_BURNING_FLAG:
                    me->SetPhaseMask(2, true);
                    break;
                case EVENT_RESTORE_FLAG:
                    me->SetPhaseMask(1, true);

                    if (GameObject* flag = me->FindNearestGameObject(BANNER_ALLIANCE, 5.0f))
                    {
                        flag->SetLootState(GO_READY);
                        flag->UseDoorOrButton(10000, false);
                    }
                    break;
            }
        }
        private:
            EventMap events;
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE))
        {
            if (player->GetTeamId() == TEAM_HORDE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Trzeba! (50 Gold)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            player->SEND_GOSSIP_MENU(HORDE_HELLO_TEXT, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (!player->HasEnoughMoney(50 * GOLD))
                {
                    creature->MonsterWhisper("Ha! Nawet na to cie nie stac? Wszystko wydales na kosmetyki, Alluszku?", player);
                    break;
                }

                player->ModifyMoney((-50 * GOLD));

                if (GameObject* flag = creature->FindNearestGameObject(BANNER_ALLIANCE, 5.0f))
                    flag->SendObjectDeSpawnAnim(flag->GetGUID());

                char buffer[100];
                sprintf(buffer, "|cff00ccff%s spalil flage Alliance.", player->GetName().c_str());
                sWorld->SendServerMessage(SERVER_MSG_STRING, buffer);

                CAST_AI(npc_burn_flag_horde::npc_burn_flag_hordeAI, creature->AI())->SetFlagResetTimer();
                break;
        }

        player->CLOSE_GOSSIP_MENU();
        return true;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_burn_flag_hordeAI(pCreature);
    }
};

/*######
## npc_burn_flag_alliance
######*/

class npc_burn_flag_alliance : public CreatureScript
{
public:
    npc_burn_flag_alliance() : CreatureScript("npc_burn_flag_alliance") { }

    struct npc_burn_flag_allianceAI : public ScriptedAI
    {
        npc_burn_flag_allianceAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        void SetFlagResetTimer()
        {
            events.ScheduleEvent(EVENT_BURNING_FLAG, 1000);
            events.ScheduleEvent(EVENT_RESTORE_FLAG, 600000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            switch (events.ExecuteEvent())
            {
                case EVENT_BURNING_FLAG:
                    me->SetPhaseMask(2, true);
                    break;
                case EVENT_RESTORE_FLAG:
                    me->SetPhaseMask(1, true);

                    if (GameObject* flag = me->FindNearestGameObject(BANNER_HORDE, 5.0f))
                    {
                        flag->SetLootState(GO_READY);
                        flag->UseDoorOrButton(10000, false);
                    }
                    break;
            }
        }
    private:
        EventMap events;
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE))
        {
            if (player->GetTeamId() == TEAM_ALLIANCE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tez tak mysle! (50 Gold)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            player->SEND_GOSSIP_MENU(ALLIANCE_HELLO_TEXT, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (!player->HasEnoughMoney(50 * GOLD))
                {
                    creature->MonsterWhisper("Nie stac cie nawet na to? A moze to ty jestes tym smierdzielem z Hordy?", player);
                    break;
                }

                player->ModifyMoney((-50 * GOLD));

                if (GameObject* flag = creature->FindNearestGameObject(BANNER_HORDE, 5.0f))
                    flag->SendObjectDeSpawnAnim(flag->GetGUID());

                char buffer[100];
                sprintf(buffer, "|cffff6060%s spalil flage Hordy.", player->GetName().c_str());
                sWorld->SendServerMessage(SERVER_MSG_STRING, buffer);

                CAST_AI(npc_burn_flag_alliance::npc_burn_flag_allianceAI, creature->AI())->SetFlagResetTimer();
                break;
        }

        player->CLOSE_GOSSIP_MENU();
        return true;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_burn_flag_allianceAI(pCreature);
    }
};

/*######
## npc_female_emote
######*/

enum FemaleEmote 
{ 
    RESET_EMOTE       = 1,
    FEMALE_HELLO_TEXT = 1000026,
    MALE_HELLO_TEXT   = 1000027
};

class npc_female_emote : public CreatureScript
{
public:
    npc_female_emote() : CreatureScript("npc_female_emote") { }

    struct npc_female_emoteAI : public ScriptedAI
    {
        npc_female_emoteAI(Creature* creature) : ScriptedAI(creature) { }

        void DoEmote(Player* player, uint32 emote)
        {
            char buffer[100];

            switch (emote)
            {
                case TEXT_EMOTE_SPIT:
                   me->HandleEmoteCommand(EMOTE_ONESHOT_KISS);
                   sprintf(buffer, "%s spits on %s.", me->GetName().c_str(), player->GetName().c_str());
                   me->MonsterTextEmote(buffer, nullptr, true);
                   break;
                case TEXT_EMOTE_SMILE:
                    sprintf(buffer, "%s smiles at %s.", me->GetName().c_str(), player->GetName().c_str());
                    me->MonsterTextEmote(buffer, nullptr, true);;
                    break;
                case TEXT_EMOTE_HUG:
                    sprintf(buffer, "%s hugs %s.", me->GetName().c_str(), player->GetName().c_str());
                    me->MonsterTextEmote(buffer, nullptr, true);;
                    break;
                case TEXT_EMOTE_LOVE:
                    sprintf(buffer, "%s loves %s.", me->GetName().c_str(), player->GetName().c_str());
                    me->MonsterTextEmote(buffer, nullptr, true);;
                    break;
                case TEXT_EMOTE_KNEEL:
                    sprintf(buffer, "%s kneels before %s.", me->GetName().c_str(), player->GetName().c_str());
                    me->MonsterTextEmote(buffer, nullptr, true);
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_KNEEL);
                    events.ScheduleEvent(RESET_EMOTE, 3000);
                    break;
                case TEXT_EMOTE_LICK:
                    sprintf(buffer, "%s licks %s.", me->GetName().c_str(), player->GetName().c_str());
                    me->MonsterTextEmote(buffer, nullptr, true);
                    break;
            }

        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            switch (events.ExecuteEvent())
            {
                case RESET_EMOTE:
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                    break;
            }
        }

    private:
        EventMap events;
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Napluj na mnie. (1 Gold)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Usmiechnij sie! (10 Gold)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Przytul... (30 Gold)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Kochaj mnie! (50 Gold... ale nawet to nie pomoze)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Kleknij przede mna. (100 Gold)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Wyciagnij swoj jezyczek... (250 Gold)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);

            if (player->getGender() == GENDER_FEMALE)
                player->SEND_GOSSIP_MENU(FEMALE_HELLO_TEXT, creature->GetGUID());
            else
                player->SEND_GOSSIP_MENU(MALE_HELLO_TEXT, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (!player->HasEnoughMoney(1 * GOLD))
                {
                    creature->MonsterWhisper("Widze, ze zawartosc twojej sakiewki jest taka sama, jak twoich spodni... Nic tam nie ma!", player);
                    break;
                }

                player->ModifyMoney(-(1 * GOLD));
                CAST_AI(npc_female_emote::npc_female_emoteAI, creature->AI())->DoEmote(player, TEXT_EMOTE_SPIT);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                if (!player->HasEnoughMoney(10 * GOLD))
                {
                    creature->MonsterWhisper("Widze, ze zawartosc twojej sakiewki jest taka sama, jak twoich spodni... Nic tam nie ma!", player);
                    break;
                }

                player->ModifyMoney(-(10 * GOLD));
                CAST_AI(npc_female_emote::npc_female_emoteAI, creature->AI())->DoEmote(player, TEXT_EMOTE_SMILE);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                if (!player->HasEnoughMoney(30 * GOLD))
                {
                    creature->MonsterWhisper("Widze, ze zawartosc twojej sakiewki jest taka sama, jak twoich spodni... Nic tam nie ma!", player);
                    break;
                }

                player->ModifyMoney(-(30 * GOLD));
                CAST_AI(npc_female_emote::npc_female_emoteAI, creature->AI())->DoEmote(player, TEXT_EMOTE_HUG);
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                if (!player->HasEnoughMoney(50 * GOLD))
                {
                    creature->MonsterWhisper("Widze, ze zawartosc twojej sakiewki jest taka sama, jak twoich spodni... Nic tam nie ma!", player);
                    break;
                }

                player->ModifyMoney(-(50 * GOLD));
                CAST_AI(npc_female_emote::npc_female_emoteAI, creature->AI())->DoEmote(player, TEXT_EMOTE_LOVE);
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                if (!player->HasEnoughMoney(100 * GOLD))
                {
                    creature->MonsterWhisper("Widze, ze zawartosc twojej sakiewki jest taka sama, jak twoich spodni... Nic tam nie ma!", player);
                    break;
                }

                player->ModifyMoney(-(100 * GOLD));
                CAST_AI(npc_female_emote::npc_female_emoteAI, creature->AI())->DoEmote(player, TEXT_EMOTE_KNEEL);
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                if (!player->HasEnoughMoney(250 * GOLD))
                {
                    creature->MonsterWhisper("Widze, ze zawartosc twojej sakiewki jest taka sama, jak twoich spodni... Nic tam nie ma!", player);
                    break;
                }

                player->ModifyMoney(-(250 * GOLD));
                CAST_AI(npc_female_emote::npc_female_emoteAI, creature->AI())->DoEmote(player, TEXT_EMOTE_LICK);
                break;
        }

        player->CLOSE_GOSSIP_MENU();
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_female_emoteAI(creature);
    }

};

/*######
## npc_gambler
## @Gambling
######*/

enum GamblerEnums 
{ 
    GAMBLER_HELLO_TEXT = 1000024, 
    GAMBLER_INFO_TEXT  = 1000025
};

class npc_gambler : public CreatureScript
{
public:
    npc_gambler() : CreatureScript("npc_gambler") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE) && !player->duel)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stawka: 50 gold.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stawka: 100 gold.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stawka: 200 gold.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stawka: 500 gold.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stawka: 1000 gold.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Resetuj stawke.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "O co chodzi z pojedynkami za gold?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);

            player->SEND_GOSSIP_MENU(GAMBLER_HELLO_TEXT, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        bool close = true;
        
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->SetResetDuelSetting();
                player->SetDuelSetting50G();
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->SetResetDuelSetting();
                player->SetDuelSetting100G();
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->SetResetDuelSetting();
                player->SetDuelSetting200G();
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->SetResetDuelSetting();
                player->SetDuelSetting500G();
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                player->SetResetDuelSetting();
                player->SetDuelSetting1000G();
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                player->SetResetDuelSetting();
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:
                close = false;
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Dziekuje za wyjasnienie.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->SEND_GOSSIP_MENU(GAMBLER_INFO_TEXT, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:
                player->CLOSE_GOSSIP_MENU();
                break;
        }

        if (close)
            player->CLOSE_GOSSIP_MENU();

        // Prevent cheating.
        if (player->duel)
            player->SetResetDuelSetting();

        return true;
    }
};

void AddSC_npcs_hazard()
{
    new npc_lottery_teleporter();
    new npc_lottery_maker();
    new npc_lotery_number();
    new npc_lotery_coins();

    new npc_wypierdalator();
    new npc_wpierdalator();

    new npc_crypt_tele();
    new npc_burn_flag_horde();
    new npc_burn_flag_alliance();
    new npc_female_emote();
    new npc_gambler();
}