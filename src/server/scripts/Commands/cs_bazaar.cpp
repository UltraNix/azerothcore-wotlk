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

#include "Language.h"
#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include "BazaarMgr.h"


class bazaar_commandscript : public CommandScript
{
public:
    bazaar_commandscript() : CommandScript("bazar_commandscript") { }

    std::vector<ChatCommand> GetCommands() const 
    {
        static std::vector<ChatCommand> commandTable =
        {
            { "bazarpp",        SEC_PLAYER,          false, &HandleBazaarPremiumCommand,          "" },
            { "bazargold",      SEC_PLAYER,          false, &HandleBazaarGoldCommand,             "" },
            { "bazaramount",    SEC_PLAYER,          false, &HandleBazaarAmountCommand,           "" },
            { "bazarbuy",       SEC_PLAYER,          false, &HandleBazaarBuyCommand,              "" },
            { "myauctions",     SEC_PLAYER,          false, &HandleMyAuctionsCommand,             "" },
            { "delauction",     SEC_PLAYER,          false, &HandleDeleteAuctionCommand,          "" },
            // Slave Market
            { "slavebuy",       SEC_PLAYER,          false, &HandleSlaveBuyCommand,               "" },
            { "slavesell",      SEC_PLAYER,          false, &HandleSlaveSellCommand,              "" },
        };

        return commandTable;
    }

    static bool HandleBazaarPremiumCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        if (!*args)
            return false;

        char* ppStr = strtok((char*)args, " ");
        if (!ppStr || !atoi(ppStr))
            return false;

        char* moneyStr = strtok(nullptr, "");
        if (!moneyStr || !atoi(moneyStr))
            return false;

        uint32 guidLow = player->GetGUIDLow();
        uint32 accId = player->GetSession()->GetAccountId();

        uint32 dpAmount = atoi(ppStr);
        uint32 moneyAmount = atoi(moneyStr);
        uint32 auctionCount = sBazaarMgr->GetAuctionCount(accId, AUCTION_SELL_PREMIUM);


        if ((moneyAmount > 50000))
        {
            handler->PSendSysMessage("Please try again, price too high.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if ((dpAmount < 50))
        {
            handler->PSendSysMessage("Please try again, offer too low.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sBazaarMgr->AuctionTime(player))
        {
            handler->PSendSysMessage("You need to wait 3 seconds between create another auction.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (auctionCount >= 3)
        {
            handler->PSendSysMessage("You can't have more than 3 auctions of this type at one account.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sBazaarMgr->CheckPremiumAmount(accId, dpAmount))
        {
            handler->PSendSysMessage("You don't have enough points to do that.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (sBazaarMgr->CreateBazaarAuction(player, moneyAmount, dpAmount, AUCTION_SELL_PREMIUM, 0, 0))
            sBazaarMgr->TakeRequiredAmount(player, dpAmount, AUCTION_SELL_PREMIUM);
        else
        {
            handler->PSendSysMessage("Something wrong! Please notice an GameMaster.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        return true;
    }

    static bool HandleBazaarGoldCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        if (!*args)
            return false;

        char* moneyStr = strtok((char*)args, " ");
        if (!moneyStr || !atoi(moneyStr))
            return false;

        char* ppStr = strtok(nullptr, "");
        if (!ppStr || !atoi(ppStr))
            return false;

        uint32 accId = player->GetSession()->GetAccountId();

        uint32 dpAmount    = atoi(ppStr);
        uint32 moneyAmount = atoi(moneyStr);
        uint32 auctionCount = sBazaarMgr->GetAuctionCount(accId, AUCTION_SELL_MONEY);

        if ((dpAmount > 2000))
        {
            handler->PSendSysMessage("Please try again, price too high.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if ((moneyAmount < 500))
        {
            handler->PSendSysMessage("Please try again, offer too low.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sBazaarMgr->AuctionTime(player))
        {
            handler->PSendSysMessage("You need to wait 3 seconds between create another auction.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        
        if (auctionCount >= 3)
        {
            handler->PSendSysMessage("You can't have more than 3 auctions of this type at one account.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sBazaarMgr->CheckMoneyAmount(player, moneyAmount))
        {
            handler->PSendSysMessage("You don't have enough money to do that.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (sBazaarMgr->CreateBazaarAuction(player, moneyAmount, dpAmount, AUCTION_SELL_MONEY, 0, 0))
            sBazaarMgr->TakeRequiredAmount(player, moneyAmount, AUCTION_SELL_MONEY);
        else
        {
            handler->PSendSysMessage("Something wrong! Please notice an GameMaster.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        return true;
    }

    static bool HandleDeleteAuctionCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        if (!*args)
            return false;

        char* idStr = strtok((char*)args, " ");
        if (!idStr || !atoi(idStr))
            return false;

        uint32 auctionId = atoi(idStr);
        uint32 accId = player->GetSession()->GetAccountId();

        if (!sBazaarMgr->CheckAuctionOwner(player, auctionId))
        {
            handler->PSendSysMessage("That auction is not belong to your character.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sBazaarMgr->CheckCharacterCount(player, accId, auctionId))
        {
            handler->PSendSysMessage("You can't have more than 10 characters on account.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        sBazaarMgr->ReturnAuctionAmount(player, auctionId, false);
        sBazaarMgr->DeleteBazaarAuction(auctionId);

        handler->PSendSysMessage("Auction Id: %u has been deleted.", auctionId);
        sLog->outBazaar("Auction Id: %u has been deleted by: %s.", auctionId, player->GetName().c_str());

        return true;
    }

    static bool HandleBazaarAmountCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        sBazaarMgr->PremiumAmount(player);
        return true;
    }

    static bool HandleBazaarBuyCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        if (!*args)
            return false;

        char* idStr = strtok((char*)args, " ");
        if (!idStr || !atoi(idStr))
            return false;

        uint32 auctionId = atoi(idStr);

        if (sBazaarMgr->CheckAuctionType(player, auctionId))
        {
            handler->PSendSysMessage("Wrong auction type, try again.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (sBazaarMgr->CheckAuctionOwner(player, auctionId))
        {
            handler->PSendSysMessage("You can't buy own auctions.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sBazaarMgr->CanEffortAuction(player, auctionId))
        {
            handler->PSendSysMessage("You can't effort that or auction has been sold.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (sBazaarMgr->SendAuctionOffer(player, auctionId))
        {
            sBazaarMgr->ReturnAuctionAmount(player, auctionId, true);
            sBazaarMgr->DeleteBazaarAuction(auctionId);
            handler->PSendSysMessage("You bought Auction Id: %u", auctionId);
        }

        return true;
    }

    static bool HandleMyAuctionsCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        sBazaarMgr->PlayerAuctions(player);
        return true;
    }

    static bool HandleSlaveBuyCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        if (!*args)
            return false;

        char* idStr = strtok((char*)args, " ");
        if (!idStr || !atoi(idStr))
            return false;

        uint32 auctionId = atoi(idStr);
        uint32 accId = player->GetSession()->GetAccountId();

        if (!sBazaarMgr->CheckAuctionType(player, auctionId))
        {
            handler->PSendSysMessage("Wrong auction type, try again.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (sBazaarMgr->CheckAuctionOwner(player, auctionId))
        {
            handler->PSendSysMessage("You can't buy own characters.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sBazaarMgr->CanEffortAuction(player, auctionId))
        {
            handler->PSendSysMessage("You can't effort that or character has been sold.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sBazaarMgr->CheckCharacterCount(player, accId, auctionId))
        {
            handler->PSendSysMessage("You can't have more than 10 characters on account.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (sBazaarMgr->SendAuctionOffer(player, auctionId))
        {
            sBazaarMgr->ReturnAuctionAmount(player, auctionId, true);
            sBazaarMgr->DeleteBazaarAuction(auctionId);
            handler->PSendSysMessage("You bought character from auction Id: %u", auctionId);
        }

        return true;
    }

    static bool HandleSlaveSellCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        if (!*args)
            return false;

        // Price 
        char* ppStr = strtok((char*)args, " ");
        if (!ppStr || !atoi(ppStr))
            return false;

        // Main Spec 
        char* mainSpecStr = strtok(nullptr, " ");
        if (!mainSpecStr || !atoi(mainSpecStr) && mainSpecStr != "0")
            return false;

        // Off Spec 
        char* offSpecStr = strtok(nullptr, " ");
        if (!offSpecStr || !atoi(offSpecStr) && offSpecStr != "0")
            return false;

        uint32 accId = player->GetSession()->GetAccountId();

        uint32 dpAmount = atoi(ppStr);
        uint8  mainSpec = atoi(mainSpecStr);
        uint8  offSpec  = atoi(offSpecStr);

        uint32 auctionCount = sBazaarMgr->GetAuctionCount(accId, AUCTION_SELL_CHARACTER);

        if (mainSpec > 3)
        {
            handler->PSendSysMessage("Wrong main spec.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (offSpec > 4)
        {
            handler->PSendSysMessage("Wrong off spec.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->getLevel() < 70)
        {
            handler->PSendSysMessage("You can't sell characters below level 70.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if ((dpAmount < 250))
        {
            handler->PSendSysMessage("Please try again, offer too low.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (auctionCount >= 3)
        {
            handler->PSendSysMessage("You can't have more than 3 auctions of this type at one account.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (sBazaarMgr->CreateBazaarAuction(player, 0, dpAmount, AUCTION_SELL_CHARACTER, mainSpec, offSpec))
            sBazaarMgr->LogoutCharacterAfterAuction(player);
        else
        {
            handler->PSendSysMessage("Something wrong! Please notice an GameMaster.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        return true;
    }
};

enum NpcBazaarActions
{
    // will be used for scrolling
    NPC_BAZAAR_ACTION_LIST_PREMIUM_AUCTIONS = 1000,
    NPC_BAZAAR_ACTION_LIST_GOLD_AUCTIONS    = 2000,
    NPC_BAZAAR_ACTION_SELECTED_AUCTION      = 3000,
    NPC_BAZAAR_ACTION_ACCEPT_OFFER          = 2000000,
    NPC_BAZAAR_ACTION_RETURN_MAIN           = 2000001,
    NPC_BAZAAR_ACTION_CLOSE                 = 2000002
};

const uint8  AuctionsOnPage    = 20;

class npc_bazaar : public CreatureScript
{
public:
    npc_bazaar() : CreatureScript("npc_bazaar") { }

    uint16 count = 0; 
    uint32 id[2000];
    uint32 selectedAuctionId = 0;
    bool auctionGold = false;

    bool OnGossipHello(Player* player, Creature* creature)
    {
        selectedAuctionId = 0;
        auctionGold = false;
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View premium auctions...", GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_LIST_PREMIUM_AUCTIONS);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View gold auctions...", GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_LIST_GOLD_AUCTIONS);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        
        if (action >= NPC_BAZAAR_ACTION_LIST_PREMIUM_AUCTIONS && action < NPC_BAZAAR_ACTION_LIST_GOLD_AUCTIONS)
        {
            LoadBazaarAuctions(AUCTION_SELL_PREMIUM);
            ShowPage(player, action - NPC_BAZAAR_ACTION_LIST_PREMIUM_AUCTIONS, false);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action >= NPC_BAZAAR_ACTION_LIST_GOLD_AUCTIONS && action < NPC_BAZAAR_ACTION_SELECTED_AUCTION)
        {
            LoadBazaarAuctions(AUCTION_SELL_MONEY);
            ShowPage(player, action - NPC_BAZAAR_ACTION_LIST_GOLD_AUCTIONS, true);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action == NPC_BAZAAR_ACTION_ACCEPT_OFFER)
        {
            std::string s = std::to_string(player->GetSelectedAuction());
            ChatHandler handler(player->GetSession());
            bazaar_commandscript::HandleBazaarBuyCommand(&handler, s.c_str());
            player->CLOSE_GOSSIP_MENU();
        }
        else if (action == NPC_BAZAAR_ACTION_RETURN_MAIN)
        {
            selectedAuctionId = 0;
            auctionGold = false;
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View premium auctions...", GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_LIST_PREMIUM_AUCTIONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View gold auctions...", GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_LIST_GOLD_AUCTIONS);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action == NPC_BAZAAR_ACTION_CLOSE)
            player->CLOSE_GOSSIP_MENU();
        else
        {
            selectedAuctionId = action - NPC_BAZAAR_ACTION_SELECTED_AUCTION;
            player->SetSelectedAuction(selectedAuctionId);

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GetAuctionAcceptStringData(player->GetSelectedAuction(), auctionGold), GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_ACCEPT_OFFER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Return.", GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_RETURN_MAIN);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }

        return true;
    }

    void LoadBazaarAuctions(uint8 type)
    {
        count = 0;
        
        QueryResult result = CharacterDatabase.PQuery("SELECT auctionId FROM bazar_auction WHERE auction_type = %u", type);

        if (result)
        {
            do
            {
                Field *fields = result->Fetch();
                uint32 auctionId = fields[0].GetUInt32();

                count++;
                id[count] = auctionId;

            } while (result->NextRow());
        }
    }

    std::string GetAuctionStringData(uint32 auctionId, bool gold)
    {
        if (!auctionId)
        {
            std::string data = "Auction Sold Out";
            return data;
        }

        QueryResult result = CharacterDatabase.PQuery("SELECT mo_amount, dp_amount, owner_name FROM bazar_auction WHERE auctionId = %u", auctionId);

        if (!result)
        {
            std::string data = "Auction Sold Out";
            return data;
        }

        std::string auctionList[3];

        if (result)
        {
            Field *fields = result->Fetch();

            auctionList[0] = fields[0].GetString();
            auctionList[1] = fields[1].GetString();
            auctionList[2] = fields[2].GetString();
        }

        std::string data = gold ? ("Offer: " + auctionList[0] + "g for " + auctionList[1] + "pp - by: " + auctionList[2]) : ("Offer: " + auctionList[1] + "pp for " + auctionList[0] + "g - by: " + auctionList[2]);
        return data;
    }

    std::string GetAuctionAcceptStringData(uint32 auctionId, bool gold)
    {
        if (!auctionId)
        {
            std::string data = "Auction Sold Out";
            return data;
        }

        QueryResult result = CharacterDatabase.PQuery("SELECT mo_amount, dp_amount FROM bazar_auction WHERE auctionId = %u", auctionId);

        if (!result)
        {
            std::string data = "Auction Sold Out";
            return data;
        }

        std::string auctionList[2];

        if (result)
        {
            Field *fields = result->Fetch();

            auctionList[0] = fields[0].GetString();
            auctionList[1] = fields[1].GetString();
        }

        std::string data = gold ? ("Accept Offer: " + auctionList[0] + "g for " + auctionList[1] + "pp") : ("Accept Offer: " + auctionList[1] + "pp for " + auctionList[0] + "g");
        return data;
    }

    void ShowPage(Player *player, uint16 page, bool gold)
    {
        uint16 auctions = 0;
        bool haveNextPage = false;

        if (gold)
            auctionGold = true;

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Main Menu", GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_RETURN_MAIN);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Close", GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_CLOSE);

        for (uint16 i = 0; i < count; ++i)
        {
            auctions++;
            if (auctions > (page + 1) * AuctionsOnPage)
            {
                haveNextPage = true;
                break;
            }

            if (auctions >= page * AuctionsOnPage && !gold)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, GetAuctionStringData(id[auctions], false), GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_SELECTED_AUCTION + id[auctions]);
            else if (auctions >= page * AuctionsOnPage && gold)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, GetAuctionStringData(id[auctions], true), GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_SELECTED_AUCTION + id[auctions]);
        }

        if (page > 0 && !gold)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Previous page...", GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_LIST_PREMIUM_AUCTIONS + page - 1);
        else if (page > 0 && gold)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Previous page...", GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_LIST_GOLD_AUCTIONS + page - 1);

        if (haveNextPage && !gold)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Next page...", GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_LIST_PREMIUM_AUCTIONS + page + 1);
        else if (haveNextPage && gold)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Next page...", GOSSIP_SENDER_MAIN, NPC_BAZAAR_ACTION_LIST_GOLD_AUCTIONS + page + 1);
    }
};

enum NpcSlaveActions
{
    // will be used for scrolling
    NPC_SLAVE_ACTION_LIST_CHARACTER_WARRIOR_AUCTIONS      = 1000,
    NPC_SLAVE_ACTION_LIST_CHARACTER_PALADIN_AUCTIONS      = 2000,
    NPC_SLAVE_ACTION_LIST_CHARACTER_HUNTER_AUCTIONS       = 3000,
    NPC_SLAVE_ACTION_LIST_CHARACTER_ROGUE_AUCTIONS        = 4000,
    NPC_SLAVE_ACTION_LIST_CHARACTER_PRIEST_AUCTIONS       = 5000,
    NPC_SLAVE_ACTION_LIST_CHARACTER_DEATH_KNIGHT_AUCTIONS = 6000,
    NPC_SLAVE_ACTION_LIST_CHARACTER_SHAMAN_AUCTIONS       = 7000,
    NPC_SLAVE_ACTION_LIST_CHARACTER_MAGE_AUCTIONS         = 8000,
    NPC_SLAVE_ACTION_LIST_CHARACTER_WARLOCK_AUCTIONS      = 9000,
    NPC_SLAVE_ACTION_LIST_CHARACTER_DRUID_AUCTIONS        = 10000,

    NPC_SLAVE_ACTION_SELECTED_AUCTION        = 20000,
    NPC_SLAVE_ACTION_ACCEPT_OFFER            = 3000000,
    NPC_SLAVE_ACTION_RETURN_MAIN             = 3000001,
    NPC_SLAVE_ACTION_CLOSE                   = 3000002,
    NPC_SLAVE_OUTPUT_ARMORY_LINK             = 3000003,
    NPC_SLAVE_ACTION_SEND_ITEM_LIST          = 3000004,
    NPC_SLAVE_ACTION_CONFIRM_OFFER           = 3000005,
};

class npc_slave : public CreatureScript
{
public:
    npc_slave() : CreatureScript("npc_slave") { }

    uint32 type = 0;
    uint16 count = 0;
    uint32 id[2000];
    uint32 selectedAuctionId = 0;

    bool OnGossipHello(Player* player, Creature* creature)
    {
        selectedAuctionId = 0; type = 0;

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "View Warrior auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_WARRIOR_AUCTIONS);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "View Paladin auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_PALADIN_AUCTIONS);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "View Hunter auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_HUNTER_AUCTIONS);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "View Rogue auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_ROGUE_AUCTIONS);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "View Priest auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_PRIEST_AUCTIONS);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "View Death Knight auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_DEATH_KNIGHT_AUCTIONS);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "View Shaman auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_SHAMAN_AUCTIONS);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "View Mage auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_MAGE_AUCTIONS);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "View Warlock auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_WARLOCK_AUCTIONS);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "View Druid auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_DRUID_AUCTIONS);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());


        ChatHandler handler(player->GetSession());
        //handler.PSendSysMessage("Tip: Prat lets you copy links not text, http:// and will turn it into a link.");
        handler.PSendSysMessage("Tip: Pobierz addon prat, a swobodnie dostaniesz kopie linku do armory!");
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        if (action >= NPC_SLAVE_ACTION_LIST_CHARACTER_WARRIOR_AUCTIONS && action < NPC_SLAVE_ACTION_LIST_CHARACTER_PALADIN_AUCTIONS)
        {
            type = NPC_SLAVE_ACTION_LIST_CHARACTER_WARRIOR_AUCTIONS;
            LoadSlaveAuctions(CLASS_WARRIOR);
            ShowPage(player, action - NPC_SLAVE_ACTION_LIST_CHARACTER_WARRIOR_AUCTIONS);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action >= NPC_SLAVE_ACTION_LIST_CHARACTER_PALADIN_AUCTIONS && action < NPC_SLAVE_ACTION_LIST_CHARACTER_HUNTER_AUCTIONS)
        {
            type = NPC_SLAVE_ACTION_LIST_CHARACTER_PALADIN_AUCTIONS;
            LoadSlaveAuctions(CLASS_PALADIN);
            ShowPage(player, action - NPC_SLAVE_ACTION_LIST_CHARACTER_PALADIN_AUCTIONS);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action >= NPC_SLAVE_ACTION_LIST_CHARACTER_HUNTER_AUCTIONS && action < NPC_SLAVE_ACTION_LIST_CHARACTER_ROGUE_AUCTIONS)
        {
            type = NPC_SLAVE_ACTION_LIST_CHARACTER_HUNTER_AUCTIONS;
            LoadSlaveAuctions(CLASS_HUNTER);
            ShowPage(player, action - NPC_SLAVE_ACTION_LIST_CHARACTER_HUNTER_AUCTIONS);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action >= NPC_SLAVE_ACTION_LIST_CHARACTER_ROGUE_AUCTIONS && action < NPC_SLAVE_ACTION_LIST_CHARACTER_PRIEST_AUCTIONS)
        {
            type = NPC_SLAVE_ACTION_LIST_CHARACTER_ROGUE_AUCTIONS;
            LoadSlaveAuctions(CLASS_ROGUE);
            ShowPage(player, action - NPC_SLAVE_ACTION_LIST_CHARACTER_ROGUE_AUCTIONS);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action >= NPC_SLAVE_ACTION_LIST_CHARACTER_PRIEST_AUCTIONS && action < NPC_SLAVE_ACTION_LIST_CHARACTER_DEATH_KNIGHT_AUCTIONS)
        {
            type = NPC_SLAVE_ACTION_LIST_CHARACTER_PRIEST_AUCTIONS;
            LoadSlaveAuctions(CLASS_PRIEST);
            ShowPage(player, action - NPC_SLAVE_ACTION_LIST_CHARACTER_PRIEST_AUCTIONS);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action >= NPC_SLAVE_ACTION_LIST_CHARACTER_DEATH_KNIGHT_AUCTIONS && action < NPC_SLAVE_ACTION_LIST_CHARACTER_SHAMAN_AUCTIONS)
        {
            type = NPC_SLAVE_ACTION_LIST_CHARACTER_DEATH_KNIGHT_AUCTIONS;
            LoadSlaveAuctions(CLASS_DEATH_KNIGHT);
            ShowPage(player, action - NPC_SLAVE_ACTION_LIST_CHARACTER_DEATH_KNIGHT_AUCTIONS);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action >= NPC_SLAVE_ACTION_LIST_CHARACTER_SHAMAN_AUCTIONS && action < NPC_SLAVE_ACTION_LIST_CHARACTER_MAGE_AUCTIONS)
        {
            type = NPC_SLAVE_ACTION_LIST_CHARACTER_SHAMAN_AUCTIONS;
            LoadSlaveAuctions(CLASS_SHAMAN);
            ShowPage(player, action - NPC_SLAVE_ACTION_LIST_CHARACTER_SHAMAN_AUCTIONS);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action >= NPC_SLAVE_ACTION_LIST_CHARACTER_MAGE_AUCTIONS && action < NPC_SLAVE_ACTION_LIST_CHARACTER_WARLOCK_AUCTIONS)
        {
            type = NPC_SLAVE_ACTION_LIST_CHARACTER_MAGE_AUCTIONS;
            LoadSlaveAuctions(CLASS_MAGE);
            ShowPage(player, action - NPC_SLAVE_ACTION_LIST_CHARACTER_MAGE_AUCTIONS);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action >= NPC_SLAVE_ACTION_LIST_CHARACTER_WARLOCK_AUCTIONS && action < NPC_SLAVE_ACTION_LIST_CHARACTER_DRUID_AUCTIONS)
        {
            type = NPC_SLAVE_ACTION_LIST_CHARACTER_WARLOCK_AUCTIONS;
            LoadSlaveAuctions(CLASS_WARLOCK);
            ShowPage(player, action - NPC_SLAVE_ACTION_LIST_CHARACTER_WARLOCK_AUCTIONS);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action >= NPC_SLAVE_ACTION_LIST_CHARACTER_DRUID_AUCTIONS && action < NPC_SLAVE_ACTION_SELECTED_AUCTION)
        {
            type = NPC_SLAVE_ACTION_LIST_CHARACTER_DRUID_AUCTIONS;
            LoadSlaveAuctions(CLASS_DRUID);
            ShowPage(player, action - NPC_SLAVE_ACTION_LIST_CHARACTER_DRUID_AUCTIONS);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action == NPC_SLAVE_ACTION_ACCEPT_OFFER)
        {
            std::string s = std::to_string(player->GetSelectedAuction());
            ChatHandler handler(player->GetSession());
            bazaar_commandscript::HandleSlaveBuyCommand(&handler, s.c_str());
            player->CLOSE_GOSSIP_MENU();
        }
        else if (action == NPC_SLAVE_ACTION_RETURN_MAIN)
        {
            selectedAuctionId = 0; type = 0;
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View Warrior auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_WARRIOR_AUCTIONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View Paladin auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_PALADIN_AUCTIONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View Hunter auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_HUNTER_AUCTIONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View Rogue auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_ROGUE_AUCTIONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View Priest auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_PRIEST_AUCTIONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View Death Knight auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_DEATH_KNIGHT_AUCTIONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View Shaman auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_SHAMAN_AUCTIONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View Mage auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_MAGE_AUCTIONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View Warlock auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_WARLOCK_AUCTIONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View Druid auctions...", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_LIST_CHARACTER_DRUID_AUCTIONS);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else if (action == NPC_SLAVE_ACTION_CLOSE)
            player->CLOSE_GOSSIP_MENU();
        else if (action == NPC_SLAVE_OUTPUT_ARMORY_LINK)
        {
            if (sendArmoryLink(player, player->GetSelectedAuction()))
            {
                for (uint8 i = 0; i < 14; i++)
                    if (i == 13)
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GetAuctionAcceptStringData(player->GetSelectedAuction(), i), GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_SEND_ITEM_LIST);
                    else
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GetAuctionAcceptStringData(player->GetSelectedAuction(), i), GOSSIP_SENDER_MAIN, NPC_SLAVE_OUTPUT_ARMORY_LINK);

                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Buy This Character.", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_ACCEPT_OFFER);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Return.", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_RETURN_MAIN);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }
        else if (action == NPC_SLAVE_ACTION_SEND_ITEM_LIST)
        {
            if (sendCharacterInfo(player, player->GetSelectedAuction()))
            {
                for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
                    sendItemList(player, player->GetSelectedAuction(), i);

                for (uint8 i = 0; i < 14; i++)
                    if (i == 13)
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GetAuctionAcceptStringData(player->GetSelectedAuction(), i), GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_SEND_ITEM_LIST);
                    else
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GetAuctionAcceptStringData(player->GetSelectedAuction(), i), GOSSIP_SENDER_MAIN, NPC_SLAVE_OUTPUT_ARMORY_LINK);

                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Buy This Character.", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_ACCEPT_OFFER);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Return.", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_RETURN_MAIN);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }

        }
        else if (action == NPC_SLAVE_ACTION_CONFIRM_OFFER)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, GetAuctionConfirmStringData(player->GetSelectedAuction()), GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_ACCEPT_OFFER);        
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Return.", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_RETURN_MAIN);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else
        {
            selectedAuctionId = action - NPC_SLAVE_ACTION_SELECTED_AUCTION; type = 0;
            player->SetSelectedAuction(selectedAuctionId);

            for (uint8 i = 0; i < 14; i++)
                if (i == 13)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GetAuctionAcceptStringData(player->GetSelectedAuction(), i), GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_SEND_ITEM_LIST);
                else
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GetAuctionAcceptStringData(player->GetSelectedAuction(), i), GOSSIP_SENDER_MAIN, NPC_SLAVE_OUTPUT_ARMORY_LINK);

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Buy This Character.", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_CONFIRM_OFFER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Return.", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_RETURN_MAIN);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }

        return true;
    }

    void LoadSlaveAuctions(uint32 slave_class)
    {
        count = 0;
                                                                                                                 // AUCTION_SELL_CHARACTER = 0x02
        QueryResult result = CharacterDatabase.PQuery("SELECT auctionId FROM bazar_auction WHERE slave_class = %u AND auction_type = 2", slave_class);

        if (result)
        {
            do
            {
                Field *fields = result->Fetch();
                uint32 auctionId = fields[0].GetUInt32();

                count++;
                id[count] = auctionId;

            } while (result->NextRow());
        }
    }

    std::string GetAuctionStringData(uint32 auctionId)
    {
        if (!auctionId)
        {
            std::string data = "Character Sold Out";
            return data;
        }

        QueryResult result = CharacterDatabase.PQuery("SELECT dp_amount, owner_name FROM bazar_auction WHERE auctionId = %u", auctionId);

        if (!result)
        {
            std::string data = "Character Sold Out";
            return data;
        }

        std::string auctionList[2];

        if (result)
        {
            Field *fields = result->Fetch();

            auctionList[0] = fields[0].GetString();
            auctionList[1] = fields[1].GetString();
        }

        std::string data = "Char: " + auctionList[1] + " for " + auctionList[0] + "pp (details)";
        return data;
    }

    bool sendArmoryLink(Player* player, uint32 auctionId)
    {
        if (!player)
            return false;

        if (!auctionId)
            return false;

        QueryResult result = CharacterDatabase.PQuery("SELECT char_guid FROM bazar_auction WHERE auctionId = %u", auctionId);

        if (!result)
            return false;

        uint32 armoryGuid;

        if (result)
        {
            Field *fields = result->Fetch();
            armoryGuid = fields[0].GetUInt32();
        }

        ChatHandler handler(player->GetSession());
        handler.PSendSysMessage("Armory Link: http://sunwell.pl/character/1/%u", armoryGuid);
        return true;
    }

    bool sendCharacterInfo(Player* player, uint32 auctionId)
    {
        if (!player)
            return false;

        if (!auctionId)
            return false;

        QueryResult result = CharacterDatabase.PQuery("SELECT owner_name, slave_avgitemlevel FROM bazar_auction WHERE auctionId = %u", auctionId);

        if (!result)
            return false;

        std::string name = "";
        uint32 avg = 0;

        if (result)
        {
            Field *fields = result->Fetch();
            name = fields[0].GetString();
            avg = fields[1].GetUInt32();
        }

        ChatHandler handler(player->GetSession());
        handler.PSendSysMessage("Player: %s Average Item Level: %u", name.c_str(), avg);
        return true;
    }

    void sendItemList(Player* player, uint32 auctionId, uint8 slot)
    {
        if (!player)
            return;

        if (!auctionId)
            return;

        QueryResult result = CharacterDatabase.PQuery("SELECT slave_level_slot1, slave_level_slot2, slave_level_slot3, slave_level_slot4, slave_level_slot5, slave_level_slot6, slave_level_slot7, slave_level_slot8, slave_level_slot9, slave_level_slot10, slave_level_slot11, slave_level_slot12, slave_level_slot13, slave_level_slot14, slave_level_slot15, slave_level_slot16, slave_level_slot17, slave_level_slot18, slave_level_slot19 FROM bazar_auction WHERE auctionId = %u", auctionId);

        if (!result)
            return;

        uint32 itemId = 0;
        uint8 quality = 0;

        std::string itemName = "";
        std::string color[6];

        // Grey
        color[0] = "|cff9d9d9d";
        // White
        color[1] = "|cffffffff";
        // Green
        color[2] = "|cff1eff00";
        // Rare
        color[3] = "|cff0070dd";
        // Epic
        color[4] = "|cffa335ee";
        // Legendary
        color[5] = "|cffff8000";

        if (result)
        {
            Field *fields = result->Fetch();
            itemId = fields[slot].GetUInt32();
        }

        ChatHandler handler(player->GetSession());

        QueryResult result1 = WorldDatabase.PQuery("SELECT name, Quality FROM item_template WHERE entry = %u", itemId);

        if (!result1)
        {
            switch (slot)
            {
                case EQUIPMENT_SLOT_HEAD:
                    handler.PSendSysMessage("[HEAD]: -");
                    break;
                case EQUIPMENT_SLOT_NECK:
                    handler.PSendSysMessage("[NECK]: -");
                    break;
                case EQUIPMENT_SLOT_SHOULDERS:
                    handler.PSendSysMessage("[SHOULDERS]: -");
                    break;
                case EQUIPMENT_SLOT_BODY:
                    handler.PSendSysMessage("[BODY]: -");
                    break;
                case EQUIPMENT_SLOT_CHEST:
                    handler.PSendSysMessage("[CHEST]: -");
                    break;
                case EQUIPMENT_SLOT_WAIST:
                    handler.PSendSysMessage("[WAIST]: -");
                    break;
                case EQUIPMENT_SLOT_LEGS:
                    handler.PSendSysMessage("[LEGS]: -");
                    break;
                case EQUIPMENT_SLOT_FEET:
                    handler.PSendSysMessage("[FEET]: -");
                    break;
                case EQUIPMENT_SLOT_WRISTS:
                    handler.PSendSysMessage("[WRISTS]: -");
                    break;
                case EQUIPMENT_SLOT_HANDS:
                    handler.PSendSysMessage("[HANDS]: -");
                    break;
                case EQUIPMENT_SLOT_FINGER1:
                    handler.PSendSysMessage("[FINGER1]: -");
                    break;
                case EQUIPMENT_SLOT_FINGER2:
                    handler.PSendSysMessage("[FINGER2]: -");
                    break;
                case EQUIPMENT_SLOT_TRINKET1:
                    handler.PSendSysMessage("[TRINKET1]: -");
                    break;
                case EQUIPMENT_SLOT_TRINKET2:
                    handler.PSendSysMessage("[TRINKET2]: -");
                    break;
                case EQUIPMENT_SLOT_MAINHAND:
                    handler.PSendSysMessage("[MAINHAND]: -");
                    break;
                case EQUIPMENT_SLOT_OFFHAND:
                    handler.PSendSysMessage("[OFFHAND]: -");
                    break;
                case EQUIPMENT_SLOT_RANGED:
                    handler.PSendSysMessage("[RANGED]: -");
                    break;
                case EQUIPMENT_SLOT_TABARD:
                    handler.PSendSysMessage("[TABARD]: -");
                    break;
            }
        }

        if (result1)
        {
            Field *fields = result1->Fetch();
            itemName = fields[0].GetString();
            quality  = fields[1].GetUInt8();
 
            switch (slot)
            {
                case EQUIPMENT_SLOT_HEAD:
                    handler.PSendSysMessage("[HEAD] - %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_NECK:
                    handler.PSendSysMessage("[NECK]: - %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_SHOULDERS:
                    handler.PSendSysMessage("[SHOULDERS]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_BODY:
                    handler.PSendSysMessage("[BODY]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_CHEST:
                    handler.PSendSysMessage("[CHEST]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_WAIST:
                    handler.PSendSysMessage("[WAIST]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_LEGS:
                    handler.PSendSysMessage("[LEGS]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_FEET:
                    handler.PSendSysMessage("[FEET]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_WRISTS:
                    handler.PSendSysMessage("[WRISTS]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_HANDS:
                    handler.PSendSysMessage("[HANDS]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_FINGER1:
                    handler.PSendSysMessage("[FINGER1]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_FINGER2:
                    handler.PSendSysMessage("[FINGER2]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_TRINKET1:
                    handler.PSendSysMessage("[TRINKET1]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_TRINKET2:
                    handler.PSendSysMessage("[TRINKET2]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_MAINHAND:
                    handler.PSendSysMessage("[MAINHAND]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_OFFHAND:
                    handler.PSendSysMessage("[OFFHAND]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_RANGED:
                    handler.PSendSysMessage("[RANGED]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
                case EQUIPMENT_SLOT_TABARD:
                    handler.PSendSysMessage("[TABARD]: %s|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r", color[quality].c_str(), itemId, itemName.c_str());
                    break;
            }
        }
    }

    std::string GetAuctionAcceptStringData(uint32 auctionId, uint8 info_return)
    {
        if (!auctionId)
        {
            std::string data = "Character Sold Out";
            return data;
        }

        QueryResult result = CharacterDatabase.PQuery("SELECT char_guid, dp_amount, owner_name, slave_race, slave_class, slave_gender, slave_level, slave_money, slave_arena, slave_honor, slave_riding, slave_mainspec, slave_offspec, slave_avgitemlevel FROM bazar_auction WHERE auctionId = %u", auctionId);

        if (!result)
        {
            std::string data = "Character Sold Out";
            return data;
        }

        std::string auctionList;
        uint32 auctionListAlternative;

        if (result)
        {
            Field *fields = result->Fetch();

            auctionList = fields[info_return].GetString();
            auctionListAlternative = fields[info_return].GetUInt32();
        }

        std::string data;

        switch (info_return)
        {
            case 0:
                data = "Armory: sunwell.pl/character/1/" + auctionList;
                break;
            case 1:
                data = "Price: " + auctionList + " Premium";
                break;
            case 2:
                data = "Name: " + auctionList;
                break;
            case 3:
                switch (auctionListAlternative)
                {
                    case 1:
                        data = "Race: Human";
                        break;
                    case 2:
                        data = "Race: Orc";
                        break;
                    case 3:
                        data = "Race: Dwarf";
                        break;
                    case 4:
                        data = "Race: Night Elf";
                        break;
                    case 5:
                        data = "Race: Undead";
                        break;
                    case 6:
                        data = "Race: Tauren";
                        break;
                    case 7:
                        data = "Race: Gnome";
                        break;
                    case 8:
                        data = "Race: Troll";
                        break;
                    case 10:
                        data = "Race: Blood Elf";
                        break;
                    case 11:
                        data = "Race: Draenei";
                        break;
                    default:
                        data = "Race: Unknown";
                        break;
                }
                break;
            case 4:
                switch (auctionListAlternative)
                {
                    case 1:
                        data = "Class: Warrior";
                        break;
                    case 2:
                        data = "Class: Paladin";
                        break;
                    case 3:
                        data = "Class: Hunter";
                        break;
                    case 4:
                        data = "Class: Rogue";
                        break;
                    case 5:
                        data = "Class: Priest";
                        break;
                    case 6:
                        data = "Class: Death Knight";
                        break;
                    case 7:
                        data = "Class: Shaman";
                        break;
                    case 8:
                        data = "Class: Mage";
                        break;
                    case 9:
                        data = "Class: Warlock";
                        break;
                    case 11:
                        data = "Class: Druid";
                        break;
                    default:
                        data = "Class: Unknown";
                        break;
                }
                break;
            case 5:
                switch (auctionListAlternative)
                {
                    case 0:
                        data = "Gender: Male";
                        break;
                    case 1:
                        data = "Gender: Female";
                        break;
                    default:
                        data = "Gender: Unknown";
                        break;
                }
                break;
            case 6:
                data = "Level: " + auctionList;
                break;
            case 7:
                data = "Gold: " + auctionList + "g";
                break;
            case 8:
                data = "Arena Points: " + auctionList;
                break;
            case 9:
                data = "Honor Points: " + auctionList;
                break;
            case 10:
                data = "Riding Skill: " + auctionList;
                break;
            case 11:
                data = "MainSpec: " + auctionList;
                break;
            case 12:
                data = "Offspec: " + auctionList;
                break;
            case 13:
                data = "Average Item Level: " + auctionList + " [show items]";
                break;
            default:
                data = "Unknown";
                break;
        }
        return data;
    }

    std::string GetAuctionConfirmStringData(uint32 auctionId)
    {
        if (!auctionId)
        {
            std::string data = "Character Sold Out";
            return data;
        }

        QueryResult result = CharacterDatabase.PQuery("SELECT dp_amount, owner_name FROM bazar_auction WHERE auctionId = %u", auctionId);

        if (!result)
        {
            std::string data = "Character Sold Out";
            return data;
        }

        std::string auctionList[2];

        if (result)
        {
            Field *fields = result->Fetch();

            auctionList[0] = fields[0].GetString();
            auctionList[1] = fields[1].GetString();
        }

        std::string data = "Slave: " + auctionList[1] + " for " + auctionList[0] + "pp [Confirm]";

        return data;
    }

    void ShowPage(Player *player, uint16 page)
    {
        uint16 auctions = 0;
        bool haveNextPage = false;

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Main Menu", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_RETURN_MAIN);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Close", GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_CLOSE);

        for (uint16 i = 0; i < count; ++i)
        {
            auctions++;
            if (auctions >(page + 1) * AuctionsOnPage)
            {
                haveNextPage = true;
                break;
            }

            if (auctions >= page * AuctionsOnPage)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GetAuctionStringData(id[auctions]), GOSSIP_SENDER_MAIN, NPC_SLAVE_ACTION_SELECTED_AUCTION + id[auctions]);
        }

        if (page > 0)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Previous page...", GOSSIP_SENDER_MAIN, type + page - 1);

        if (haveNextPage)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Next page...", GOSSIP_SENDER_MAIN, type + page + 1);
    }
};

void AddSC_bazaar_commandscript()
{
    new bazaar_commandscript();
    new npc_bazaar();
    new npc_slave();
}
