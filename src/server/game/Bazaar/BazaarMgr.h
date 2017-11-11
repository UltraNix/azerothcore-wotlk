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

#ifndef SC_BZMGR_H
#define SC_BZMGR_H

#include "Common.h"
#include "SharedDefines.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include "AccountMgr.h"

// Bazaar Tax Rate 10%
#define TAX_RATE 10
// Account ID where characters are stored
#define BAZAAR_ACCOUNT 1

enum BazarAuctionTypes
{
    AUCTION_SELL_PREMIUM   = 0x00,
    AUCTION_SELL_MONEY     = 0x01,
    AUCTION_SELL_CHARACTER = 0x02
};

class BazaarMgr
{
    BazaarMgr() {}
    ~BazaarMgr() {}

    public:
        static BazaarMgr* instance();

        bool CheckPremiumAmount(uint32 accountId, uint32 sellAmount);
        bool CheckMoneyAmount(Player* player, uint32 sellAmount);
        bool CanEffortAuction(Player* player, uint32 auctionId);
        bool CanEffortTaxRate(Player* player, uint32 price, uint8 type, bool extraTax = false);
        bool CheckAuctionOwner(Player* player, uint32 auctionId);
        bool CheckAuctionType(Player* player, uint32 auctionId);
        void ReturnAuctionAmount(Player* player, uint32 auctionId, bool buy = false);
        bool SendAuctionOffer(Player* player, uint32 auctionId);
        bool CheckCharacterCount(Player* player, uint32 accountId, uint32 auctionId);

        void RemoveOutdatedAuctions(Player* player, uint32 auctionId);

        void TakeRequiredAmount(Player* player, int32 amount, uint8 type, bool extraTax = false);
        bool CreateBazaarAuction(Player* player, uint32 moneyAmount, uint32 dpAmount, uint8 type, uint8 mainSpec, uint8 offSpec, std::string description);
        void DeleteBazaarAuction(uint32 auctionId);
        void PremiumAmount(Player* player);
        bool AuctionTime(Player* player);
        void PlayerAuctions(Player* player);

        uint32 GetAuctionCount(uint32 accountId, uint8 type);

        // Slave Market
        void LogoutCharacterAfterAuction(Player* player);
};

#define sBazaarMgr BazaarMgr::instance()

#endif