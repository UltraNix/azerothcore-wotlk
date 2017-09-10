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
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Gram (50 Lottery Coins)", GOSSIP_SENDER_MAIN, GOLD_LOTERRY, "Wpisz liczby od 1 do 15", 0, true);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Pokaz mi moje numery", GOSSIP_SENDER_MAIN, SHOW_NUMBERS);
                    player->SEND_GOSSIP_MENU(NPC_GREETINGS_01, creature->GetGUID());
                    break;
                case SC_LOTTERY_NPC:
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Oczywiscie (10 Sunwell Coins)", GOSSIP_SENDER_MAIN, SC_LOTTERY, "Wpisz liczby od 1 do 15", 0, true);
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

#define SPELL_DETECTION    18950

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
            creature->CastSpell(creature, SPELL_DETECTION);
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
                if (player->IsGameMaster() || player->IsBeingTeleported() || player->GetPositionZ() > 0.0f || player->GetPositionZ() < -12.0f)
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

enum MasukaData {
    MASUKA_EVENT_RUN = 1,
    MASUKA_EVENT_DIE = 2,
};

class npc_hazard_masuka : public CreatureScript {
public:
    npc_hazard_masuka() : CreatureScript("npc_hazard_masuka") {}
    struct npc_hazard_masukaAI : public ScriptedAI {
        bool escaping;
        EventMap events;
        npc_hazard_masukaAI(Creature* creature) : ScriptedAI(creature) {}
        void Reset() {
            escaping = false;
            events.Reset();
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!who || !who->IsInWorld())
                return;

            Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself();

            if (!player || player->IsGameMaster()) return;

            if (!me->IsWithinDist(who, 5.0f, false))
                return;
            if (!escaping) {
                me->MonsterYell("JESTEM WOLNY!", 0, nullptr);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                me->RemoveAllAuras();
                events.ScheduleEvent(MASUKA_EVENT_RUN, 1500);
                escaping = true;
            }
        }
        void UpdateAI(uint32 diff)
        {
            events.Update(diff);
            switch (events.GetEvent()) {
            case MASUKA_EVENT_RUN:
                me->MonsterYell("Czas sprzedac troche golda!", 0, nullptr);
                me->MonsterTextEmote("Masuka laughs.", nullptr);
                me->MonsterMoveWithSpeed(-11062.98f, -1592.51f, 27.96f, 10.f);
                events.ScheduleEvent(MASUKA_EVENT_DIE, 5000);
                events.PopEvent();
                break;
            case MASUKA_EVENT_DIE:
                me->DisappearAndDie();
                events.PopEvent();
                break;
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const {
        return new npc_hazard_masukaAI(creature);
    }
};

enum PiooRadeData {
    PIOORADE_EVENT_TALK				= 1,
    PIOORADE_EVENT_RUN				= 2,
    PIOORADE_EVENT_DESPAWN			= 3,
    PIOORADE_EVENT_SUMMON_COINS		= 4,
    PIOORADE_EVENT_RUN_BACK			= 5,
    PIOORADE_EVENT_RUN2				= 6,
    PIOORADE_EVENT_DESPAWN_COINS	= 7,
    PIOORADE_NPC_PIOO				= 91036,
    PIOORADE_NPC_RADE				= 91037,
    PIOORADE_GOB_COINS				= 1000005,
};
class npc_hazard_pioorade : public CreatureScript {
public:
    npc_hazard_pioorade() : CreatureScript("npc_hazard_pioorade") {}

    struct npc_hazard_piooradeAI : public ScriptedAI {
        bool talking;
        EventMap events;
        uint8 currentTalkID;
        Position coinsPos;
        std::string texts[6];
        GameObject* coins;
        npc_hazard_piooradeAI(Creature *creature) : ScriptedAI(creature) {
            texts[0] = "I wtedy powiedzialem mu, ze odbanuje jego postac za 100zl.";
            texts[1] = "Jasne, pamietam o naszym ukladzie.";
            texts[2] = "Zauwazyli nas. Uciekamy Pioo!";
            texts[3] = "Ale pamietasz, ze polowa hajsu do mnie?";
            texts[4] = "Uwielbiam robic z toba interesy.";
            texts[5] = "Wiejemy!";
        }
        void Reset() {
            talking = false;
            coins = nullptr;
            currentTalkID = 0;
            events.Reset();
        }
        void MoveInLineOfSight(Unit* who)
        {
            if (!who || !who->IsInWorld())
                return;

            Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself();

            if (!player || player->IsGameMaster()) return;
			if (!me->IsWithinDist(who, 30.0f, false) || who->GetPosition().GetPositionZ() > 0.f)
				return;
            if (!me->FindNearestCreature(me->GetEntry() == PIOORADE_NPC_RADE ? PIOORADE_NPC_PIOO : PIOORADE_NPC_RADE, 10.f)) //script wont start if 2nd npc is dead
                return;
            
            if (!talking) {
                talking = true;
                events.ScheduleEvent(PIOORADE_EVENT_TALK, me->GetEntry() == PIOORADE_NPC_RADE ? 1000 : 4000);
            }
        }
        void UpdateAI(uint32 diff) {
            events.Update(diff);
            switch (events.GetEvent()) {
            case PIOORADE_EVENT_TALK:
                me->MonsterSay(texts[me->GetEntry() == PIOORADE_NPC_RADE ? currentTalkID : currentTalkID + 3].c_str(), 0, nullptr);
                if (currentTalkID < 2) {
                    ++currentTalkID;
                    events.RepeatEvent(8000);
                }
                else {
                    events.ScheduleEvent(PIOORADE_EVENT_RUN, 1000);
                    events.PopEvent();
                }
                break;
            case PIOORADE_EVENT_RUN:
                me->MonsterMoveWithSpeed(-11144.96f, -1703.38f, -28.5f, 10.f);
                me->CastSpell(me, 54861); //nitro boots
                if (me->GetEntry() == PIOORADE_NPC_RADE) events.ScheduleEvent(PIOORADE_EVENT_DESPAWN, 7000);
                else events.ScheduleEvent(PIOORADE_EVENT_SUMMON_COINS, 3000);
                events.PopEvent();
                break;
            case PIOORADE_EVENT_DESPAWN:
                me->DisappearAndDie();
                events.PopEvent();
                break;
            case PIOORADE_EVENT_SUMMON_COINS:
                me->GetPosition(&coinsPos);
                coins = me->SummonGameObject(PIOORADE_GOB_COINS, coinsPos.GetPositionX(), coinsPos.GetPositionY(), coinsPos.GetPositionZ(), 0.f, 0.f, 0.f, 0.f, 0.f, 1000);
                events.ScheduleEvent(PIOORADE_EVENT_RUN_BACK, 1000);
                events.PopEvent();
                break;
            case PIOORADE_EVENT_RUN_BACK:
                me->MonsterYell("Zgubilem szekle!", 0, nullptr);
                me->MonsterMoveWithSpeed(coinsPos.GetPositionX(), coinsPos.GetPositionY(), coinsPos.GetPositionZ(), 10.f);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_WHIRLWIND);
                events.ScheduleEvent(PIOORADE_EVENT_DESPAWN_COINS, 5000);
                events.PopEvent();
                break;
            case PIOORADE_EVENT_DESPAWN_COINS:
                if (coins) coins->Delete();
                events.ScheduleEvent(PIOORADE_EVENT_RUN2, 2000);
                events.PopEvent();
                break;
            case PIOORADE_EVENT_RUN2:
                me->MonsterYell("Rade zaczekaj!", 0, nullptr);
                me->MonsterMoveWithSpeed(-11144.96f, -1703.38f, -28.5f, 10.f);
                events.ScheduleEvent(PIOORADE_EVENT_DESPAWN, 5000);
                events.PopEvent();
                break;
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const {
        return new npc_hazard_piooradeAI(creature);
    }
};

enum PswzrdXinefData {
    PSWZRDXINEF_EVENT_TALK		= 1,
    PSWZRDXINEF_EVENT_MORPH		= 2,
    PSWZRDXINEF_EVENT_TALK2		= 3,
    PSWZRDXINEF_EVENT_ROTATE	= 4,
    PSWZRDXINEF_EVENT_CRASH		= 5,
    PSWZRDXINEF_EVENT_DESPAWN	= 6,
    PSWZRDXINEF_MORPH_XINEF		= 23574,
    PSWZRDXINEF_MORPH_PSWZRD	= 5555,
    PSWZRDXINEF_NPC_XINEF		= 91038,
    PSWZRDXINEF_NPC_PSWZRD		= 91039,
};
class npc_hazard_pswzrdxinef : public CreatureScript {
public:
    npc_hazard_pswzrdxinef() : CreatureScript("npc_hazard_pswzrdxinef") {}
    struct npc_hazard_pswzrdxinefAI : public ScriptedAI {
        bool eventStart;
        EventMap events;
        npc_hazard_pswzrdxinefAI(Creature *creature) : ScriptedAI(creature) {}
        void Reset() {
            events.Reset();
            eventStart = false;
            events.ScheduleEvent(PSWZRDXINEF_EVENT_TALK, me->GetEntry() == PSWZRDXINEF_NPC_XINEF ? 4000 : 1000);
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!who || !who->IsInWorld())
                return;

            Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself();

            if (!player || player->IsGameMaster()) return;

			if (!me->IsWithinDist(who, 8.f, false))
				return;

            if (!me->FindNearestCreature(me->GetEntry() == PSWZRDXINEF_NPC_XINEF ? PSWZRDXINEF_NPC_PSWZRD : PSWZRDXINEF_NPC_XINEF, 10.f)) //script wont start if 2nd npc is dead
                return;
           
            if (!eventStart) {
                eventStart = true;
                events.Reset();
                events.ScheduleEvent(PSWZRDXINEF_EVENT_ROTATE, 1000);
            }
        }

        void UpdateAI(uint32 diff) {
            events.Update(diff);
            switch (events.GetEvent()) {
            case PSWZRDXINEF_EVENT_TALK: {
                std::string text;
                for (uint8 i = 0; i < 16; ++i) {
                    text += std::to_string(urand(0, 1));
                }
                me->MonsterSay(text.c_str(), 0, nullptr);
                events.RepeatEvent(6000);
                break;
            }
            case PSWZRDXINEF_EVENT_ROTATE:
                me->SetFacingTo(me->GetEntry() == PSWZRDXINEF_NPC_XINEF ? 1.89f : 1.26f);
                events.ScheduleEvent(PSWZRDXINEF_EVENT_MORPH, 2000);
                events.PopEvent();
                break;
            case PSWZRDXINEF_EVENT_MORPH:
                me->CastSpell(me, 12244, false);
                me->SetDisplayId(me->GetEntry() == PSWZRDXINEF_NPC_PSWZRD ? PSWZRDXINEF_MORPH_PSWZRD : PSWZRDXINEF_MORPH_XINEF);
                events.ScheduleEvent(PSWZRDXINEF_EVENT_TALK2, me->GetEntry() == PSWZRDXINEF_NPC_XINEF ? 3000 : 2000);
                events.PopEvent();
                break;
            case PSWZRDXINEF_EVENT_TALK2:
                me->MonsterSay(me->GetEntry() == PSWZRDXINEF_NPC_XINEF ? "Kraa?" : "Meeeow", 0, nullptr);
                events.ScheduleEvent(PSWZRDXINEF_EVENT_CRASH, 3000);
                events.PopEvent();
                break;
            case PSWZRDXINEF_EVENT_CRASH:
                me->MonsterYell(me->GetEntry() == PSWZRDXINEF_NPC_XINEF ? "System Failure" : "Access Violation", 0, nullptr);
                me->CastSpell(me, 62834, false);
                events.ScheduleEvent(PSWZRDXINEF_EVENT_DESPAWN, 1000);
                events.PopEvent();
                break;
            case PSWZRDXINEF_EVENT_DESPAWN:
                me->setDeathState(DeathState::JUST_DIED);
                events.PopEvent();
                break;
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const {
        return new npc_hazard_pswzrdxinefAI(creature);
    }
};

enum SenPenData {
    SENPEN_EVENT_START		= 1,
    SENPEN_EVENT_SLAM		= 2,
    SENPEN_EVENT_TALK		= 3,
    SENPEN_EVENT_BLIZZLIKE	= 4,
    SENPEN_EVENT_DESPAWN	= 5,
    SENPEN_SPELL_SLAM		= 69903,
    SENPEN_NPC_SENSI		= 91040,
    SENPEN_NPC_PENDU		= 91041,
    SENPEN_NPC_PSWZRD		= 91042,
};

class npc_hazard_senpen : public CreatureScript {
public:
    npc_hazard_senpen() : CreatureScript("npc_hazard_senpen") {}

    struct npc_hazard_senpenAI : public ScriptedAI {
        bool eventStart;
        EventMap events;
        Creature *pendu;

        npc_hazard_senpenAI(Creature *creature) : ScriptedAI(creature) {}
        void Reset() {
            eventStart = false;
            events.Reset();
        }
        void MoveInLineOfSight(Unit* who)
        {
            if (!who || !who->IsInWorld())
                return;

            Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself();
            if (!player || player->IsGameMaster()) return;
            
            if (!me->IsWithinDist(who, 15.f, false))
                return;
			if (!me->FindNearestCreature(me->GetEntry() == SENPEN_NPC_PENDU ? SENPEN_NPC_SENSI : SENPEN_NPC_PENDU, 10.f)) //script wont start if 2nd npc is dead
				return;
            if (!eventStart) {
                eventStart = true;
                if (me->GetEntry() == SENPEN_NPC_SENSI)
                    events.ScheduleEvent(SENPEN_EVENT_START, 1000);
            }
        }

        void UpdateAI(uint32 diff) {
            events.Update(diff);
            switch (events.GetEvent()) {
            case SENPEN_EVENT_START:
                me->MonsterSay("Dobra, to testujemy.", 0, nullptr);
                events.ScheduleEvent(SENPEN_EVENT_SLAM, 5000);
                events.PopEvent();
                break;
            case SENPEN_EVENT_SLAM: {
                if (pendu = me->FindNearestCreature(SENPEN_NPC_PENDU, 10.f)) {
                    int32 dmg = 63042;
                    me->CastCustomSpell(pendu, SENPEN_SPELL_SLAM, nullptr, &dmg, nullptr, false);
                    events.ScheduleEvent(SENPEN_EVENT_TALK, 2000);
                    if (pendu->isDead())
                        me->MonsterTextEmote("Sensimilek's Shield Slam hits Pendu for 63042. (Critical)", nullptr);
                }
                else
                    events.ScheduleEvent(SENPEN_EVENT_DESPAWN, 1000);
                events.PopEvent();
                break;
            }
            case SENPEN_EVENT_TALK:
                if (pendu->isDead()) {
                    me->MonsterSay("Przeciez na WotLK nie powinno sie dac zadac tyle damage.", 0, nullptr);
                    events.ScheduleEvent(SENPEN_EVENT_BLIZZLIKE, 3000);
                }
                else {
                    me->MonsterSay("Miss? Brak hit capa boli. Jeszcze raz Pendu! Siadaj!", 0, nullptr);
                    pendu->CombatStop();
                    pendu->SetStandState(UNIT_STAND_STATE_SIT);
                    pendu->SetFacingTo(pendu->GetHomePosition().GetOrientation());
                    events.ScheduleEvent(SENPEN_EVENT_SLAM, 3000);
                }
                events.PopEvent();
                break;
            case SENPEN_EVENT_BLIZZLIKE: {
                Creature *pswzrd = me->FindNearestCreature(SENPEN_NPC_PSWZRD, 20.f);
                if (pswzrd) pswzrd->MonsterYell("Blizzlike!", 0, nullptr);
                events.ScheduleEvent(SENPEN_EVENT_DESPAWN, 1000);
                events.PopEvent();
                break;
            }
            case SENPEN_EVENT_DESPAWN:
                me->DisappearAndDie();
                events.PopEvent();
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const {
        return new npc_hazard_senpenAI(creature);
    }
};

enum WarmaneData {
    WARMANE_EVENT_WORMS = 1,
    WARMANE_EVENT_DESPAWN = 2,
    WARMANE_WORMS_COUNT = 16,
    WARMANE_NPC_WORM = 7395,
};
class npc_hazard_warmane : public CreatureScript {
public:
    npc_hazard_warmane() : CreatureScript("npc_hazard_warmane") {}
    struct npc_hazard_warmaneAI : public ScriptedAI {
        uint8 wormsCount;
        bool eventStart;
        EventMap events;
        npc_hazard_warmaneAI(Creature *creature) : ScriptedAI(creature) {}
        void Reset() {
            wormsCount = 0;
            eventStart = false;
            events.Reset();
        }
        void MoveInLineOfSight(Unit* who)
        {
            if (!who || !who->IsInWorld())
                return;

            Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself();

            if (!player || player->IsGameMaster()) return;
            if (!me->IsWithinDist(who, 15.f, false))
                return;
            if (!eventStart) {
                eventStart = true;
                events.ScheduleEvent(WARMANE_EVENT_WORMS, 1000);
                me->MonsterTextEmote("Kaleb the Warmane is being swarmed by bugs!", nullptr);
            }
        }
        void UpdateAI(uint32 diff) {
            events.Update(diff);
            switch (events.GetEvent()) {
            case WARMANE_EVENT_WORMS:
                if (wormsCount < WARMANE_WORMS_COUNT) {
                    ++wormsCount;
                    Position pos;
                    me->GetRandomNearPosition(pos, (urand(2, 5)));
                    if (Creature *creature = me->SummonCreature(WARMANE_NPC_WORM, pos, TEMPSUMMON_TIMED_DESPAWN, 10000))
                        creature->GetMotionMaster()->MoveRandom(5.f);
                    events.RepeatEvent(300);
                }
                else {
                    events.ScheduleEvent(WARMANE_EVENT_DESPAWN, 3000);
                    events.PopEvent();
                }
                break;
            case WARMANE_EVENT_DESPAWN:
                me->DisappearAndDie();
                events.PopEvent();
                break;
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const {
        return new npc_hazard_warmaneAI(creature);
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

    new npc_hazard_masuka();
    new npc_hazard_pioorade();
    new npc_hazard_pswzrdxinef();
    new npc_hazard_senpen();
    new npc_hazard_warmane();
}