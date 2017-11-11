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

#include "BazaarMgr.h"

BazaarMgr* BazaarMgr::instance()
{
    static BazaarMgr instance;
    return &instance;
}

bool BazaarMgr::CheckPremiumAmount(uint32 accountId, uint32 sellAmount)
{
    PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_PREMIUM_POINTS);
    stmt->setUInt32(0, accountId);

    PreparedQueryResult result = LoginDatabase.Query(stmt);

    if (!result)
        return false;

    uint32 accountAmount = (*result)[0].GetUInt32();

    if (sellAmount > accountAmount)
        return false;

    return true;
}

bool BazaarMgr::CheckMoneyAmount(Player* player, uint32 sellAmount)
{
    if (!player)
        return false;

    if (!player->HasEnoughMoney(sellAmount * GOLD))
        return false; 

    return true;
}

bool BazaarMgr::CanEffortAuction(Player* player, uint32 auctionId)
{
    if (!player)
        return false;

    uint32 accId = player->GetSession()->GetAccountId();

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_BAZAR_AUCTION_AMOUNT_EFFORT);
    stmt->setUInt32(0, auctionId);

    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
        return false;

    Field* fields = result->Fetch();
    uint32 moneyAmount   = fields[0].GetUInt32();
    uint32 premiumAmount = fields[1].GetUInt32();
    uint8  auction_type  = fields[2].GetUInt8();

    switch (auction_type)
    {
        case AUCTION_SELL_PREMIUM:
            if (!CheckMoneyAmount(player, moneyAmount))
                return false;
            break;
        case AUCTION_SELL_MONEY:
        case AUCTION_SELL_CHARACTER:
            if (!CheckPremiumAmount(accId, premiumAmount))
                return false;
            break;
    }

    return true;
}

enum TaxRates 
{
    SLAVE_PREMIUM_TAX_RATE_0_500      = 10,
    SLAVE_PREMIUM_TAX_RATE_501_750    = 20,
    SLAVE_PREMIUM_TAX_RATE_751_1000   = 30,
    SLAVE_PREMIUM_TAX_RATE_OVER_1000  = 40,

    SLAVE_GOLD_TAX_RATE_0_500     = 50,
    SLAVE_GOLD_TAX_RATE_501_750   = 100,
    SLAVE_GOLD_TAX_RATE_751_1000  = 150,
    SLAVE_GOLD_TAX_RATE_OVER_1000 = 200,
};

bool BazaarMgr::CanEffortTaxRate(Player* player, uint32 price, uint8 type, bool extraTax)
{
    if (!player)
        return false;

    uint32 accId = player->GetSession()->GetAccountId();
    uint32 BazaarTaxRate = price / TAX_RATE;
    uint32 FinalPremiumTaxRate  = 0;
    uint32 FinalGoldTaxRate     = 0;
    switch (type)
    {
        case AUCTION_SELL_PREMIUM:
            FinalPremiumTaxRate = BazaarTaxRate;
            if (!CheckPremiumAmount(accId, price + BazaarTaxRate))
                return false;
            break;
        case AUCTION_SELL_MONEY:
            FinalGoldTaxRate = BazaarTaxRate;
            if (!CheckMoneyAmount(player, price + BazaarTaxRate))
                return false;
            break;
        case AUCTION_SELL_CHARACTER:
            if (price < 500)
            {
                FinalPremiumTaxRate = SLAVE_PREMIUM_TAX_RATE_0_500;
                FinalGoldTaxRate = SLAVE_GOLD_TAX_RATE_0_500;

                if (!CheckPremiumAmount(accId, SLAVE_PREMIUM_TAX_RATE_0_500))
                    return false;
                if (!CheckMoneyAmount(player, SLAVE_GOLD_TAX_RATE_0_500))
                    return false;
            } 
            else if (price > 500 && price <= 750)
            {
                FinalPremiumTaxRate = SLAVE_PREMIUM_TAX_RATE_501_750;
                FinalGoldTaxRate = SLAVE_GOLD_TAX_RATE_501_750;

                if (!CheckPremiumAmount(accId, SLAVE_PREMIUM_TAX_RATE_501_750))
                    return false;
                if (!CheckMoneyAmount(player, SLAVE_GOLD_TAX_RATE_501_750))
                    return false;
            }
            else if (price > 750 && price <= 1000)
            {
                FinalPremiumTaxRate = SLAVE_PREMIUM_TAX_RATE_751_1000;
                FinalGoldTaxRate = SLAVE_GOLD_TAX_RATE_751_1000;
                if (!CheckPremiumAmount(accId, SLAVE_PREMIUM_TAX_RATE_751_1000))
                    return false;
                if (!CheckMoneyAmount(player, SLAVE_GOLD_TAX_RATE_751_1000))
                    return false;
            }
            else if (price > 1000)
            {
                FinalPremiumTaxRate = SLAVE_PREMIUM_TAX_RATE_OVER_1000;
                FinalGoldTaxRate = SLAVE_GOLD_TAX_RATE_OVER_1000;
                if (!CheckPremiumAmount(accId, SLAVE_PREMIUM_TAX_RATE_OVER_1000))
                    return false;
                if (!CheckMoneyAmount(player, SLAVE_GOLD_TAX_RATE_OVER_1000))
                    return false;
            }
            break;
    }
    
    // Pay the taxes
    TakeRequiredAmount(player, FinalPremiumTaxRate, type);
    // Slave market gold tax
    if (extraTax == true)
        TakeRequiredAmount(player, FinalGoldTaxRate, type, true);

    return true;
}

// Check auction owner by account id
bool BazaarMgr::CheckAuctionOwner(Player* player, uint32 auctionId)
{
    if (!player)
        return false;
    
    uint32 accId = player->GetSession()->GetAccountId();

    if (!accId)
        return false;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_BAZAR_AUCTION_OWNER);
    stmt->setUInt32(0, auctionId);

    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
        return false;

    uint32 auctionOwner = (*result)[0].GetUInt32();

    if (auctionOwner != accId)
        return false;

    return true;
}

// Check auction type
bool BazaarMgr::CheckAuctionType(Player* player, uint32 auctionId)
{
    if (!player)
        return false;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_BAZAR_AUCTION_TYPE);
    stmt->setUInt32(0, auctionId);

    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
        return false;

    uint8 auctionType = (*result)[0].GetUInt8();

    if (auctionType != AUCTION_SELL_CHARACTER)
        return false;

    return true;
}
//CHAR_SEL_BAZAR_AUCTION_TYPE
void BazaarMgr::ReturnAuctionAmount(Player* player, uint32 auctionId, bool buy)
{
    if (!player)
        return;

    uint32 accId = player->GetSession()->GetAccountId();

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_BAZAR_AUCTION_AMOUNT);
    stmt->setUInt32(0, auctionId);

    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
        return;

    Field* fields = result->Fetch();
    uint32 charGuid      = fields[0].GetUInt32();
    uint32 moneyAmount   = fields[1].GetUInt32();
    uint32 premiumAmount = fields[2].GetUInt32();
    uint8  auction_type  = fields[3].GetUInt8();
    std::string name     = fields[4].GetString();

    switch (auction_type)
    {
        case AUCTION_SELL_PREMIUM:
        {
            if (buy)
            {
                player->ModifyMoney(-(int32(moneyAmount * GOLD)));

                stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_PREMIUM_POINTS);
                stmt->setUInt32(0, premiumAmount);
                stmt->setUInt32(1, accId);
                LoginDatabase.Execute(stmt);

                ChatHandler(player->GetSession()).PSendSysMessage("Details: You paid: %u gold for %u Sunwell Coins.", moneyAmount, premiumAmount);
                ChatHandler(player->GetSession()).PSendSysMessage("Points has been added to your account.", moneyAmount, premiumAmount);

                sLog->outBazaar("Auction Id: %u sold, buyer: %s, Sunwell Coins amount: %u, money amount: %u, type: [AUCTION_SELL_PREMIUM]", auctionId, player->GetName().c_str(), premiumAmount, moneyAmount);
            }
            else 
            {
                stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_PREMIUM_POINTS);
                stmt->setUInt32(0, premiumAmount);
                stmt->setUInt32(1, accId);
                LoginDatabase.Execute(stmt);
            }
            break;
        } 
        case AUCTION_SELL_MONEY:
        {
            if (buy)
            {
                player->ModifyMoney(moneyAmount * GOLD);

                stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_PREMIUM_POINTS_REMOVE);
                stmt->setUInt32(0, premiumAmount);
                stmt->setUInt32(1, accId);
                LoginDatabase.Execute(stmt);

                ChatHandler(player->GetSession()).PSendSysMessage("Details: You paid: %u Sunwell Coins for %u gold.", premiumAmount, moneyAmount);
                ChatHandler(player->GetSession()).PSendSysMessage("Gold has been added to your character.", moneyAmount, premiumAmount);

                sLog->outBazaar("Auction Id: %u sold, buyer: %s, Sunwell Coins amount: %u, money amount: %u, type: [AUCTION_SELL_MONEY]", auctionId, player->GetName().c_str(), premiumAmount, moneyAmount);
            }
            else
                player->ModifyMoney(moneyAmount * GOLD);
            break;
        }
        case AUCTION_SELL_CHARACTER:
        {
            if (buy)
            {
                stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_PREMIUM_POINTS_REMOVE);
                stmt->setUInt32(0, premiumAmount);
                stmt->setUInt32(1, accId);
                LoginDatabase.Execute(stmt);

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_SLAVE_ACCOUNT_ID);
                stmt->setUInt32(0, accId);
                stmt->setUInt32(1, charGuid);
                CharacterDatabase.Execute(stmt);

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_SLAVE_CHAR_ACHIEVEMENT);
                stmt->setUInt32(0, charGuid);
                CharacterDatabase.Execute(stmt);

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_ACHIEVEMENT_PROGRESS);
                stmt->setUInt32(0, charGuid);
                CharacterDatabase.Execute(stmt);

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_TITLES_FACTION_CHANGE);
                stmt->setString(0, "0 0 0 0 0 0");
                stmt->setUInt32(1, charGuid);
                CharacterDatabase.Execute(stmt);
               
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_RES_CHAR_TITLES_FACTION_CHANGE);
                stmt->setUInt32(0, charGuid);
                CharacterDatabase.Execute(stmt);
                
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_ADD_AT_LOGIN_FLAG);
                stmt->setUInt16(0, uint16(AT_LOGIN_RENAME));
                stmt->setUInt32(1, charGuid);
                CharacterDatabase.Execute(stmt);

                ChatHandler(player->GetSession()).PSendSysMessage("Details: You paid: %u Sunwell Coins for Character: %s", premiumAmount, name.c_str());
                ChatHandler(player->GetSession()).PSendSysMessage("Character has been added to your account.", moneyAmount, premiumAmount);

                sLog->outSlave("Auction Id: %u sold, buyer: %s GUID: %u, price: %u SC, type: [AUCTION_SELL_CHARACTER] - Character Sold: %s, GUID: %u", auctionId, player->GetName().c_str(), player->GetGUIDLow(), premiumAmount, name.c_str(), charGuid);
            }
            else
            {
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_SLAVE_ACCOUNT_ID);
                stmt->setUInt32(0, accId);
                stmt->setUInt32(1, charGuid);
                CharacterDatabase.Execute(stmt);
            }
            break;
        }
    }
}

void BazaarMgr::RemoveOutdatedAuctions(Player* player, uint32 auctionId)
{
    // TO-DO
}

bool BazaarMgr::SendAuctionOffer(Player* player, uint32 auctionId)
{
    if (!auctionId)
        return false;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_BAZAR_AUCTION_AMOUNT_OFFER);
    stmt->setUInt32(0, auctionId);

    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
        return false;

    Field* fields = result->Fetch();

    uint32 account_id   = fields[0].GetUInt32();
    uint32 char_guid    = fields[1].GetUInt32();
    uint32 mo_amount    = fields[2].GetUInt32();
    uint32 dp_amount    = fields[3].GetUInt32();
    uint8 auction_type  = fields[4].GetUInt8();
    std::string name    = fields[5].GetString();

    normalizePlayerName(name);
    
    if (auction_type == AUCTION_SELL_CHARACTER)
        sLog->outSlave("SendAuctionOffer Query: account_id: %u, char_guid: %u, dp_amount: %u, auction_type: %u, name: %s", account_id, char_guid, dp_amount, auction_type, name.c_str());
    else
        sLog->outBazaar("SendAuctionOffer Query: account_id: %u, char_guid: %u, mo_amount: %u, dp_amount: %u, auction_type: %u, name: %s", account_id, char_guid, mo_amount, dp_amount, auction_type, name.c_str());

    switch (auction_type)
    {
        case AUCTION_SELL_PREMIUM:
        {
            if (Player* bidder = ObjectAccessor::FindPlayerByName(name, false))
            {
                int32 new_money = bidder->GetMoney() + (mo_amount * GOLD);
                bidder->SetMoney(new_money);
                ChatHandler(bidder->GetSession()).PSendSysMessage("Bazaar: Your Sunwell Coin auction has been sold.");
                ChatHandler(bidder->GetSession()).PSendSysMessage("Bazaar: %u gold has been added to your character.", mo_amount);
            }
            else
            {
                uint32 new_money = (mo_amount * GOLD);
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_MONEY_AMOUNT);
                stmt->setUInt32(0, new_money);
                stmt->setUInt32(1, char_guid);
                CharacterDatabase.Execute(stmt);
            }
            break;
        }
        case AUCTION_SELL_MONEY:
        {
            if (Player* bidder = ObjectAccessor::FindPlayerByName(name, false))
            {
                ChatHandler(bidder->GetSession()).PSendSysMessage("Bazaar: Your Gold auction has been sold.");
                ChatHandler(bidder->GetSession()).PSendSysMessage("Bazaar: %u Sunwell Coins has been added to your account. ", dp_amount);

                stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_PREMIUM_POINTS);
                stmt->setUInt32(0, dp_amount);
                stmt->setUInt32(1, account_id);
                LoginDatabase.Execute(stmt);
            }
            else 
            {
                stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_PREMIUM_POINTS);
                stmt->setUInt32(0, dp_amount);
                stmt->setUInt32(1, account_id);
                LoginDatabase.Execute(stmt);
            }
            break;
        }
        case AUCTION_SELL_CHARACTER:
        {
            stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_PREMIUM_POINTS);
            stmt->setUInt32(0, dp_amount);
            stmt->setUInt32(1, account_id);
            LoginDatabase.Execute(stmt);
            break;
        }
    }

    return true;
}

void BazaarMgr::TakeRequiredAmount(Player* player, int32 amount, uint8 type, bool extraTax)
{
    if (!player)
        return;

    uint32 accId = player->GetSession()->GetAccountId();

    switch (type)
    {
        case AUCTION_SELL_PREMIUM:
        case AUCTION_SELL_CHARACTER:
        {
            if (extraTax == true)
            {
                player->ModifyMoney(-(amount * GOLD));
                break;
            }

            PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_PREMIUM_POINTS);
            stmt->setInt32(0, -(amount));
            stmt->setUInt32(1, accId);
            LoginDatabase.Execute(stmt);
            break;
        }
        case AUCTION_SELL_MONEY:
            player->ModifyMoney(-(amount * GOLD));
            break;
    }
}

bool BazaarMgr::CreateBazaarAuction(Player* player, uint32 moneyAmount, uint32 dpAmount, uint8 type, uint8 mainSpec, uint8 offSpec, std::string description)
{
    if (!player)
        return false;

    uint32 guidLow   = player->GetGUIDLow();
    uint32 accId     = player->GetSession()->GetAccountId();
    uint32 auctionId = sObjectMgr->GenerateBazaarID();
    std::string name = player->GetName().c_str();
    std::string mainSpecStr, offSpecStr = "";

    if (type == AUCTION_SELL_CHARACTER)
    {
        switch (player->getClass())
        {
            case CLASS_WARRIOR:
            {
                if (mainSpec == 1)
                    mainSpecStr = "Arms";
                else if (mainSpec == 2)
                    mainSpecStr = "Fury";
                else if (mainSpec == 3)
                    mainSpecStr = "Protection";
                else
                    mainSpecStr = "None";

                if (offSpec == 1)
                    offSpecStr = "Arms";
                else if (offSpec == 2)
                    offSpecStr = "Fury";
                else if (offSpec == 3)
                    offSpecStr = "Protection";
                else
                    offSpecStr = "None";
            } break;
            case CLASS_PALADIN:
            {
                if (mainSpec == 1)
                    mainSpecStr = "Holy";
                else if (mainSpec == 2)
                    mainSpecStr = "Protection";
                else if (mainSpec == 3)
                    mainSpecStr = "Retribution";
                else
                    mainSpecStr = "None";

                if (offSpec == 1)
                    offSpecStr = "Holy";
                else if (offSpec == 2)
                    offSpecStr = "Protection";
                else if (offSpec == 3)
                    offSpecStr = "Retribution";
                else
                    offSpecStr = "None";
            } break;
            case CLASS_HUNTER:
            {
                if (mainSpec == 1)
                    mainSpecStr = "Beast Mastery";
                else if (mainSpec == 2)
                    mainSpecStr = "Marksmanship";
                else if (mainSpec == 3)
                    mainSpecStr = "Survival";
                else
                    mainSpecStr = "None";

                if (offSpec == 1)
                    offSpecStr = "Beast Mastery";
                else if (offSpec == 2)
                    offSpecStr = "Marksmanship";
                else if (offSpec == 3)
                    offSpecStr = "Survival";
                else
                    offSpecStr = "None";
            } break;
            case CLASS_ROGUE:
            {
                if (mainSpec == 1)
                    mainSpecStr = "Assassination";
                else if (mainSpec == 2)
                    mainSpecStr = "Combat";
                else if (mainSpec == 3)
                    mainSpecStr = "Subtlety";
                else
                    mainSpecStr = "None";

                if (offSpec == 1)
                    offSpecStr = "Assassination";
                else if (offSpec == 2)
                    offSpecStr = "Combat";
                else if (offSpec == 3)
                    offSpecStr = "Subtlety";
                else
                    offSpecStr = "None";
            } break;
            case CLASS_PRIEST:
            {
                if (mainSpec == 1)
                    mainSpecStr = "Discipline";
                else if (mainSpec == 2)
                    mainSpecStr = "Holy";
                else if (mainSpec == 3)
                    mainSpecStr = "Shadow";
                else
                    mainSpecStr = "None";

                if (offSpec == 1)
                    offSpecStr = "Discipline";
                else if (offSpec == 2)
                    offSpecStr = "Holy";
                else if (offSpec == 3)
                    offSpecStr = "Shadow";
                else
                    offSpecStr = "None";
            } break;
            case CLASS_DEATH_KNIGHT:
            {
                if (mainSpec == 1)
                    mainSpecStr = "Blood";
                else if (mainSpec == 2)
                    mainSpecStr = "Frost";
                else if (mainSpec == 3)
                    mainSpecStr = "Unholy";
                else
                    mainSpecStr = "None";

                if (offSpec == 1)
                    offSpecStr = "Blood";
                else if (offSpec == 2)
                    offSpecStr = "Frost";
                else if (offSpec == 3)
                    offSpecStr = "Unholy";
                else
                    offSpecStr = "None";
            } break;
            case CLASS_SHAMAN:
            {
                if (mainSpec == 1)
                    mainSpecStr = "Elemental";
                else if (mainSpec == 2)
                    mainSpecStr = "Enhancement";
                else if (mainSpec == 3)
                    mainSpecStr = "Restoration";
                else
                    mainSpecStr = "None";

                if (offSpec == 1)
                    offSpecStr = "Elemental";
                else if (offSpec == 2)
                    offSpecStr = "Enhancement";
                else if (offSpec == 3)
                    offSpecStr = "Restoration";
                else
                    offSpecStr = "None";
            } break;
            case CLASS_MAGE:
            {
                if (mainSpec == 1)
                    mainSpecStr = "Arcane";
                else if (mainSpec == 2)
                    mainSpecStr = "Fire";
                else if (mainSpec == 3)
                    mainSpecStr = "Frost";
                else
                    mainSpecStr = "None";

                if (offSpec == 1)
                    offSpecStr = "Arcane";
                else if (offSpec == 2)
                    offSpecStr = "Fire";
                else if (offSpec == 3)
                    offSpecStr = "Frost";
                else
                    offSpecStr = "None";
            } break;
            case CLASS_WARLOCK:
            {
                if (mainSpec == 1)
                    mainSpecStr = "Affliction";
                else if (mainSpec == 2)
                    mainSpecStr = "Demonology";
                else if (mainSpec == 3)
                    mainSpecStr = "Destruction";
                else
                    mainSpecStr = "None";

                if (offSpec == 1)
                    offSpecStr = "Affliction";
                else if (offSpec == 2)
                    offSpecStr = "Demonology";
                else if (offSpec == 3)
                    offSpecStr = "Destruction";
                else
                    offSpecStr = "None";
            } break;
            case CLASS_DRUID:
            {
                if (mainSpec == 1)
                    mainSpecStr = "Balance";
                else if (mainSpec == 2)
                    mainSpecStr = "Feral Combat";
                else if (mainSpec == 3)
                    mainSpecStr = "Restoration";
                else
                    mainSpecStr = "None";

                if (offSpec == 1)
                    offSpecStr = "Balance";
                else if (offSpec == 2)
                    offSpecStr = "Feral Combat";
                else if (offSpec == 3)
                    offSpecStr = "Restoration";
                else
                    offSpecStr = "None";
            } break;
        }
    }

    // SLAVE MARKET ONLY
    uint8 slave_race    = (type == AUCTION_SELL_CHARACTER ? player->getRace() : 0);
    uint8 slave_class   = (type == AUCTION_SELL_CHARACTER ? player->getClass() : 0);
    uint8 slave_gender  = (type == AUCTION_SELL_CHARACTER ? player->getGender() : 0);
    uint8 slave_level   = (type == AUCTION_SELL_CHARACTER ? player->getLevel() : 0);
    uint8 slave_team    = (type == AUCTION_SELL_CHARACTER ? player->GetTeamId() : 0);
    uint32 slave_money  = (type == AUCTION_SELL_CHARACTER ? player->GetMoney() / GOLD : 0);
    uint32 slave_arena  = (type == AUCTION_SELL_CHARACTER ? player->GetArenaPoints() : 0);
    uint32 slave_honor  = (type == AUCTION_SELL_CHARACTER ? player->GetHonorPoints() : 0);
    uint32 slave_riding = (type == AUCTION_SELL_CHARACTER ? player->GetBaseSkillValue(SKILL_RIDING) : 0);
    // SLAVE MARKET ONLY

    PreparedStatement* stmt = NULL;

    switch (type)
    {
        case AUCTION_SELL_PREMIUM:
        {
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_BAZAR_AUCTION);
            stmt->setUInt32(0, auctionId);
            stmt->setUInt32(1, accId);
            stmt->setUInt32(2, guidLow);
            stmt->setUInt32(3, moneyAmount);
            stmt->setUInt32(4, dpAmount);
            stmt->setUInt8(5, AUCTION_SELL_PREMIUM);
            stmt->setString(6, name);
            stmt->setUInt8(7, slave_race);
            stmt->setUInt8(8, slave_class);
            stmt->setUInt8(9, slave_gender);
            stmt->setUInt8(10, slave_level);
            stmt->setUInt32(11, slave_money);
            stmt->setUInt32(12, slave_arena);
            stmt->setUInt32(13, slave_honor);
            stmt->setUInt32(14, slave_riding);
            stmt->setString(15, mainSpecStr);
            stmt->setString(16, offSpecStr);
            stmt->setUInt16(17, 0);

            for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; i++)
                stmt->setUInt32(18 + i, 0);

            stmt->setString(37, description);
            stmt->setUInt8(38, slave_team);
            stmt->setUInt32(39, sWorld->GetGameTime());
            break;
        }
        case AUCTION_SELL_MONEY:
        {
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_BAZAR_AUCTION);
            stmt->setUInt32(0, auctionId);
            stmt->setUInt32(1, accId);
            stmt->setUInt32(2, guidLow);
            stmt->setUInt32(3, moneyAmount);
            stmt->setUInt32(4, dpAmount);
            stmt->setUInt8(5, AUCTION_SELL_MONEY);
            stmt->setString(6, name);
            stmt->setUInt8(7, slave_race);
            stmt->setUInt8(8, slave_class);
            stmt->setUInt8(9, slave_gender);
            stmt->setUInt8(10, slave_level);
            stmt->setUInt32(11, slave_money);
            stmt->setUInt32(12, slave_arena);
            stmt->setUInt32(13, slave_honor);
            stmt->setUInt32(14, slave_riding);
            stmt->setString(15, mainSpecStr);
            stmt->setString(16, offSpecStr);
            stmt->setUInt16(17, 0);

            for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; i++)
                stmt->setUInt32(18 + i, 0);

            stmt->setString(37, description);
            stmt->setUInt8(38, slave_team);
            stmt->setUInt32(39, sWorld->GetGameTime());
            break;
        }
        case AUCTION_SELL_CHARACTER:
        {
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_BAZAR_AUCTION);
            stmt->setUInt32(0, auctionId);
            stmt->setUInt32(1, accId);
            stmt->setUInt32(2, guidLow);
            stmt->setUInt32(3, moneyAmount);
            stmt->setUInt32(4, dpAmount);
            stmt->setUInt8(5, AUCTION_SELL_CHARACTER);
            stmt->setString(6, name);
            stmt->setUInt8(7, slave_race);
            stmt->setUInt8(8, slave_class);
            stmt->setUInt8(9, slave_gender);
            stmt->setUInt8(10, slave_level);
            stmt->setUInt32(11, slave_money);
            stmt->setUInt32(12, slave_arena);
            stmt->setUInt32(13, slave_honor);
            stmt->setUInt32(14, slave_riding);
            stmt->setString(15, mainSpecStr);
            stmt->setString(16, offSpecStr);
            stmt->setUInt16(17, player->GetAverageItemLevel());

            for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; i++)
                if (player->GetItemIdForSlaveMarket(i) != 0)
                    stmt->setUInt32(18 + i, player->GetItemIdForSlaveMarket(i));
                else
                    stmt->setUInt32(18 + i, 0);

            stmt->setString(37, description);
            stmt->setUInt8(38, slave_team);
            stmt->setUInt32(39, sWorld->GetGameTime());
            break;
        }
    }

    CharacterDatabase.Execute(stmt);

    if (type == AUCTION_SELL_CHARACTER)
    {
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_SLAVE_ACCOUNT_ID);
        stmt->setUInt32(0, BAZAAR_ACCOUNT);
        stmt->setUInt32(1, guidLow);
        CharacterDatabase.Execute(stmt);
        sLog->outSlave("[DETAILS] Id: %u, Player: %s (ACC ID: %u), Description: [%s]", auctionId, player->GetName().c_str(), player->GetSession()->GetAccountId(), description.c_str());
    }
    else
    {
        ChatHandler(player->GetSession()).PSendSysMessage("Your bazaar auction has been created.");

        if (type == AUCTION_SELL_MONEY)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Details: Id: %u,  Type (1 - Gold Auction), Price: %u Sunwell Coins for %u Gold", auctionId, dpAmount, moneyAmount);
            ChatHandler(player->GetSession()).PSendSysMessage("Total tax rate: 10% of gold price (%u) - non-refundable", moneyAmount / TAX_RATE);
        }
        else
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Details: Id: %u, Type (0 - Sunwell Auction), Price: %u Gold for %u Sunwell Coins", auctionId, moneyAmount, dpAmount);
            ChatHandler(player->GetSession()).PSendSysMessage("Total tax rate: 10% (%u) - non-refundable", dpAmount / TAX_RATE);
        }

        if (type == AUCTION_SELL_MONEY)
            sLog->outBazaar("Auction Id: %u created by Player: %s GUID: %u, gold amount: %u, sunwell coins amount: %u, type: [AUCTION_SELL_MONEY]", auctionId, player->GetName().c_str(), player->GetGUIDLow(), moneyAmount, dpAmount);
        else
            sLog->outBazaar("Auction Id: %u created by Player: %s GUID: %u, sunwell coins amount: %u, gold amount: %u, type: [AUCTION_SELL_PREMIUM]", auctionId, player->GetName().c_str(), player->GetGUIDLow(), dpAmount, moneyAmount);
    }

    return true;
}

void BazaarMgr::PremiumAmount(Player* player)
{
    if (!player)
        return;

    uint32 accId = player->GetSession()->GetAccountId();

    PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_PREMIUM_POINTS);
    stmt->setUInt32(0, accId);

    PreparedQueryResult result = LoginDatabase.Query(stmt);

    if (!result)
        return;

    uint32 amount = (*result)[0].GetUInt32();

    ChatHandler(player->GetSession()).PSendSysMessage("Your Sunwell Coins status: %u", amount);
}

void BazaarMgr::DeleteBazaarAuction(uint32 auctionId)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_BAZAR_AUCTION);
    stmt->setUInt32(0, auctionId);
    CharacterDatabase.Execute(stmt);
}

uint32 BazaarMgr::GetAuctionCount(uint32 accountId, uint8 type)
{
    // check character count
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_BAZAR_AUCTION_COUNT);
    stmt->setUInt32(0, accountId);
    stmt->setUInt8(1, type);

    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    return (result) ? (*result)[0].GetUInt32() : 0;
}

bool BazaarMgr::AuctionTime(Player* player)
{
    if (!player)
        return false;

    uint32 guid = player->GetGUIDLow();
    
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_BAZAR_AUCTION_TIME);
    stmt->setUInt32(0, guid);

    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    uint32 create_time = (result) ? (*result)[0].GetUInt32() : 0;

    if (create_time != 0)
        if (getMSTimeDiff(create_time, World::GetGameTimeMS()) <= 3000)
            return false;

    return true;
}

void BazaarMgr::PlayerAuctions(Player* player)
{
    if (!player)
        return;

    uint32 accId = player->GetSession()->GetAccountId();

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_BAZAR_AUCTION_OWNER_AUCTIONS);
    stmt->setUInt32(0, accId);

    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
        return;

    do
    {
        Field *fields     = result->Fetch();
        uint32 auctionId  = fields[0].GetUInt32();
        uint32 mo_amount  = fields[1].GetUInt32();
        uint32 dp_amount  = fields[2].GetUInt32();
        uint8 auctionType = fields[3].GetUInt8();
        std::string name  = fields[4].GetString();

        switch (auctionType)
        {
            case AUCTION_SELL_PREMIUM:
                ChatHandler(player->GetSession()).PSendSysMessage("Auction ID: %u Sunwell Auction (Price: %u g for %u sc)", auctionId, mo_amount, dp_amount);
                break;
            case AUCTION_SELL_MONEY:
                ChatHandler(player->GetSession()).PSendSysMessage("Auction ID: %u Gold Auction (Price: %u sc for %u g)", auctionId, dp_amount, mo_amount);
                break;
            case AUCTION_SELL_CHARACTER:
                ChatHandler(player->GetSession()).PSendSysMessage("Auction ID: %u Character Auction (Character Name: %s for %u sc)", auctionId, name.c_str(), dp_amount);
                break;
        }

    } while (result->NextRow());

}

bool BazaarMgr::CheckCharacterCount(Player* player, uint32 accountId, uint32 auctionId)
{
    if (!player || !accountId || !auctionId)
        return false;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_BAZAR_AUCTION_TYPE);
    stmt->setUInt32(0, auctionId);

    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
        return false;

    uint8 auctionType = (*result)[0].GetUInt8();
    uint32 characterCount = AccountMgr::GetCharactersCount(accountId);

    // Check only for Slave Auctions.
    if (auctionType == AUCTION_SELL_CHARACTER)
        if (characterCount >= 10)
            return false;

    return true;
}

// Slave Market: Safe logout after auction creation
void BazaarMgr::LogoutCharacterAfterAuction(Player* player)
{
    if (!player)
        return;

    player->SaveToDB(false, true);
    player->GetSession()->KickPlayer(true);
}