

#include "Common.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "World.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "DatabaseEnv.h"
#include "DBCStores.h"
#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "AuctionHouseMgr.h"
#include "Item.h"
#include "Language.h"
#include "Logging/Log.h"
#include "AvgDiffTracker.h"
#include "AsyncAuctionListing.h"
#include "Profiler.h"
#include "ItemPrototype.h"

#include <vector>

enum eAuctionHouse
{
    AH_MINIMUM_DEPOSIT = 100,
};

AuctionHouseMgr::AuctionHouseMgr()
{
}

AuctionHouseMgr::~AuctionHouseMgr()
{
    mAitems.clear();
}

AuctionHouseObject* AuctionHouseMgr::GetAuctionsMap(uint32 factionTemplateId)
{
    // team have linked auction houses
    FactionTemplateEntry const* u_entry = sFactionTemplateStore.LookupEntry(factionTemplateId);
    if (!u_entry)
        return &mNeutralAuctions;
    else if (u_entry->ourMask & FACTION_MASK_ALLIANCE)
        return &mAllianceAuctions;
    else if (u_entry->ourMask & FACTION_MASK_HORDE)
        return &mHordeAuctions;
    else
        return &mNeutralAuctions;
}

uint32 AuctionHouseMgr::GetAuctionDeposit(AuctionHouseEntry const* entry, uint32 time, ItemRef const& pItem, uint32 count)
{
    uint32 MSV = pItem->GetTemplate()->SellPrice;

    if (MSV <= 0)
        return AH_MINIMUM_DEPOSIT;

    float multiplier = CalculatePct(float(entry->depositPercent), 3);
    uint32 timeHr = (((time / 60) / 60) / 12);
    uint32 deposit = uint32(((multiplier * MSV * count / 3) * timeHr * 3) * sWorld->getRate(RATE_AUCTION_DEPOSIT));

    ;//sLog->outDebug(LOG_FILTER_AUCTIONHOUSE, "MSV:        %u", MSV);
    ;//sLog->outDebug(LOG_FILTER_AUCTIONHOUSE, "Items:      %u", count);
    ;//sLog->outDebug(LOG_FILTER_AUCTIONHOUSE, "Multiplier: %f", multiplier);
    ;//sLog->outDebug(LOG_FILTER_AUCTIONHOUSE, "Deposit:    %u", deposit);

    if (deposit < AH_MINIMUM_DEPOSIT)
        return AH_MINIMUM_DEPOSIT;
    else
        return deposit;
}

//does not clear ram
void AuctionHouseMgr::SendAuctionWonMail(AuctionEntry* auction, SQLTransaction& trans)
{
    AuctionItem* pItem = GetAItem( auction->item_guidlow );
    if (!pItem || !pItem->GetItem())
        return;

    uint64 bidder_guid = MAKE_NEW_GUID(auction->bidder, 0, HIGHGUID_PLAYER);
    uint32 bidder_accId = 0;
    Player* bidder = ObjectAccessor::FindPlayerInOrOutOfWorld(bidder_guid);
    if (bidder)
        bidder_accId = bidder->GetSession()->GetAccountId();
    else
        bidder_accId = sObjectMgr->GetPlayerAccountIdByGUID(bidder_guid);

    // receiver exist
    if (bidder || bidder_accId)
    {
        // set owner to bidder (to prevent delete item with sender char deleting)
        // owner in `data` will set at mail receive and item extracting
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_ITEM_OWNER);
        stmt->setUInt32(0, auction->bidder);
        stmt->setUInt32(1, pItem->GetItem()->GetGUIDLow());
        trans->Append(stmt);

        if (bidder)
        {
            bidder->GetSession()->SendAuctionBidderNotification(auction->GetHouseId(), auction->Id, bidder_guid, 0, 0, auction->item_template);
            // FIXME: for offline player need also
            bidder->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_WON_AUCTIONS, 1);
        }

        MailDraft(auction->BuildAuctionMailSubject(AUCTION_WON), AuctionEntry::BuildAuctionMailBody(auction->owner, auction->bid, auction->buyout, 0, 0))
            .AddItem(pItem->GetItem().Release())
            .SendMailTo(trans, MailReceiver(bidder, auction->bidder), auction, MAIL_CHECK_MASK_COPIED);
    }
    else
    {
        sAuctionMgr->RemoveAItem( auction, true );
    }
}

void AuctionHouseMgr::SendAuctionSalePendingMail(AuctionEntry* auction, SQLTransaction& trans)
{
    uint64 owner_guid = MAKE_NEW_GUID(auction->owner, 0, HIGHGUID_PLAYER);
    Player* owner = ObjectAccessor::FindPlayerInOrOutOfWorld(owner_guid);
    uint32 owner_accId = sObjectMgr->GetPlayerAccountIdByGUID(owner_guid);
    // owner exist (online or offline)
    if (owner || owner_accId)
        MailDraft(auction->BuildAuctionMailSubject(AUCTION_SALE_PENDING), AuctionEntry::BuildAuctionMailBody(auction->bidder, auction->bid, auction->buyout, auction->deposit, auction->GetAuctionCut()))
            .SendMailTo(trans, MailReceiver(owner, auction->owner), auction, MAIL_CHECK_MASK_COPIED);
}

//call this method to send mail to auction owner, when auction is successful, it does not clear ram
void AuctionHouseMgr::SendAuctionSuccessfulMail(AuctionEntry* auction, SQLTransaction& trans)
{
    uint64 owner_guid = MAKE_NEW_GUID(auction->owner, 0, HIGHGUID_PLAYER);
    Player* owner = ObjectAccessor::FindPlayerInOrOutOfWorld(owner_guid);
    uint32 owner_accId = sObjectMgr->GetPlayerAccountIdByGUID(owner_guid);
    // owner exist
    if (owner || owner_accId)
    {
        uint32 profit = auction->bid + auction->deposit - auction->GetAuctionCut();

        if (owner)
        {
            owner->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_GOLD_EARNED_BY_AUCTIONS, profit);
            owner->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_AUCTION_SOLD, auction->bid);
            owner->GetSession()->SendAuctionOwnerNotification(auction);
        }

        MailDraft(auction->BuildAuctionMailSubject(AUCTION_SUCCESSFUL), AuctionEntry::BuildAuctionMailBody(auction->bidder, auction->bid, auction->buyout, auction->deposit, auction->GetAuctionCut()))
            .AddMoney(profit)
            .SendMailTo(trans, MailReceiver(owner, auction->owner), auction, MAIL_CHECK_MASK_COPIED, sWorld->getIntConfig(CONFIG_MAIL_DELIVERY_DELAY));

        if (auction->bid >= 50*GOLD)
            if (const GlobalPlayerData* gpd = sWorld->GetGlobalPlayerData(auction->bidder))
            {
                uint64 bidder_guid = MAKE_NEW_GUID(auction->bidder, 0, HIGHGUID_PLAYER);
                Player* bidder = ObjectAccessor::FindPlayerInOrOutOfWorld(bidder_guid);
                std::string owner_name = "";
                uint8 owner_level = 0;
                if (const GlobalPlayerData* gpd_owner = sWorld->GetGlobalPlayerData(auction->owner))
                {
                    owner_name = gpd_owner->name;
                    owner_level = gpd_owner->level;
                }
                CharacterDatabase.PExecute("INSERT INTO log_money (sender_acc, sender_guid, sender_name, sender_ip, receiver_acc, receiver_name, money, topic, date) VALUES(%u, %u, \"%s\", \"%s\", %u, \"%s\", %u, \"<AH> profit: %ug, bidder: %s %u lvl (guid: %u), seller: %s %u lvl (guid: %u), item %u (%u)\", NOW())", gpd->accountId, auction->bidder, gpd->name.c_str(), bidder ? bidder->GetSession()->GetRemoteAddress().c_str() : "", owner_accId, owner_name.c_str(), auction->bid, (profit/GOLD), gpd->name.c_str(), gpd->level, auction->bidder, owner_name.c_str(), owner_level, auction->owner, auction->item_template, auction->itemCount);
            }
    }
}

//does not clear ram
void AuctionHouseMgr::SendAuctionExpiredMail(AuctionEntry* auction, SQLTransaction& trans)
{
    //return an item in auction to its owner by mail
    AuctionItem* pItem = GetAItem( auction->item_guidlow );
    if (!pItem || !pItem->GetItem())
        return;

    uint64 owner_guid = MAKE_NEW_GUID(auction->owner, 0, HIGHGUID_PLAYER);
    Player* owner = ObjectAccessor::FindPlayerInOrOutOfWorld(owner_guid);
    uint32 owner_accId = sObjectMgr->GetPlayerAccountIdByGUID(owner_guid);

    // owner exist
    if (owner || owner_accId)
    {
        if (owner)
            owner->GetSession()->SendAuctionOwnerNotification(auction);

        MailDraft(auction->BuildAuctionMailSubject(AUCTION_EXPIRED), AuctionEntry::BuildAuctionMailBody(0, 0, auction->buyout, auction->deposit, 0))
            .AddItem(pItem->GetItem().Release())
            .SendMailTo(trans, MailReceiver(owner, auction->owner), auction, MAIL_CHECK_MASK_COPIED, 0);
    }
    else
    {
        sAuctionMgr->RemoveAItem( auction, true );
    }
}

//this function sends mail to old bidder
void AuctionHouseMgr::SendAuctionOutbiddedMail(AuctionEntry* auction, uint32 newPrice, Player* newBidder, SQLTransaction& trans)
{
    uint64 oldBidder_guid = MAKE_NEW_GUID(auction->bidder, 0, HIGHGUID_PLAYER);
    Player* oldBidder = ObjectAccessor::FindPlayerInOrOutOfWorld(oldBidder_guid);

    uint32 oldBidder_accId = 0;
    if (!oldBidder)
        oldBidder_accId = sObjectMgr->GetPlayerAccountIdByGUID(oldBidder_guid);

    // old bidder exist
    if (oldBidder || oldBidder_accId)
    {
        if (oldBidder && newBidder)
            oldBidder->GetSession()->SendAuctionBidderNotification(auction->GetHouseId(), auction->Id, newBidder->GetGUID(), newPrice, auction->GetAuctionOutBid(), auction->item_template);

        MailDraft(auction->BuildAuctionMailSubject(AUCTION_OUTBIDDED), AuctionEntry::BuildAuctionMailBody(auction->owner, auction->bid, auction->buyout, auction->deposit, auction->GetAuctionCut()))
            .AddMoney(auction->bid)
            .SendMailTo(trans, MailReceiver(oldBidder, auction->bidder), auction, MAIL_CHECK_MASK_COPIED);
    }
}

//this function sends mail, when auction is cancelled to old bidder
void AuctionHouseMgr::SendAuctionCancelledToBidderMail(AuctionEntry* auction, SQLTransaction& trans)
{
    uint64 bidder_guid = MAKE_NEW_GUID(auction->bidder, 0, HIGHGUID_PLAYER);
    Player* bidder = ObjectAccessor::FindPlayerInOrOutOfWorld(bidder_guid);

    uint32 bidder_accId = 0;
    if (!bidder)
        bidder_accId = sObjectMgr->GetPlayerAccountIdByGUID(bidder_guid);

    // bidder exist
    if (bidder || bidder_accId)
        MailDraft(auction->BuildAuctionMailSubject(AUCTION_CANCELLED_TO_BIDDER), AuctionEntry::BuildAuctionMailBody(auction->owner, auction->bid, auction->buyout, auction->deposit, 0))
            .AddMoney(auction->bid)
            .SendMailTo(trans, MailReceiver(bidder, auction->bidder), auction, MAIL_CHECK_MASK_COPIED);
}

void AuctionHouseMgr::LoadAuctionItems()
{
    uint32 oldMSTime = getMSTime();

    // need to clear in case we are reloading
    if (!mAitems.empty())
    {
        mAitems.clear();
    }

    // data needs to be at first place for Item::LoadFromDB
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_AUCTION_ITEMS);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
    {
        sLog->outString(">> Loaded 0 auction items. DB table `auctionhouse` or `item_instance` is empty!");
        sLog->outString();
        return;
    }

    uint32 count = 0;

    do
    {

        Field* fields = result->Fetch();

        uint32 item_guid        = fields[11].GetUInt32();
        uint32 item_template    = fields[12].GetUInt32();

        ItemTemplate const* proto = sObjectMgr->GetItemTemplate(item_template);
        if (!proto)
        {
            sLog->outError("AuctionHouseMgr::LoadAuctionItems: Unknown item (GUID: %u id: #%u) in auction, skipped.", item_guid, item_template);
            continue;
        }

        ItemRef item = NewItemOrBag(proto);
        if (!item->LoadFromDB(item_guid, 0, fields, item_template))
        {
            item.Delete();
            continue;
        }

        AddAItem(item);

        ++count;
    }
    while (result->NextRow());

    sLog->outString(">> Loaded %u auction items in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

void AuctionHouseMgr::LoadAuctions()
{
    uint32 oldMSTime = getMSTime();

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_AUCTIONS);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
    {
        sLog->outString(">> Loaded 0 auctions. DB table `auctionhouse` is empty.");
        sLog->outString();
        return;
    }

    uint32 count = 0;

    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    do
    {
        Field* fields = result->Fetch();

        AuctionEntry* aItem = new AuctionEntry();
        if (!aItem->LoadFromDB(fields))
        {
            aItem->DeleteFromDB(trans);
            delete aItem;
            continue;
        }

        //! item should be already loaded
        aItem->aitem = GetAItem( aItem->item_guidlow );
        aItem->auctionBirthTime = time(nullptr);
        GetAuctionsMap(aItem->factionTemplateId)->AddAuction(aItem);
        count++;
    } while (result->NextRow());

    CharacterDatabase.CommitTransaction(trans);

    sLog->outString(">> Loaded %u auctions in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

const AuctionItem* AuctionHouseMgr::AddAItem(ItemRef const& it)
{
    ASSERT(it);
    ASSERT(mAitems.find(it->GetGUIDLow()) == mAitems.end());

    auto it2 = mAitems.emplace( std::make_pair( it->GetGUIDLow(), AuctionItem{ *it } ) );
    return &(it2.first->second);
}

bool AuctionHouseMgr::RemoveAItem(AuctionEntry* entry, bool deleteFromDB)
{
    uint32 id = entry->item_guidlow;
    entry->aitem = nullptr;

    AuctionItemMap::iterator it = mAitems.find(id);
    if (it == mAitems.end())
        return false;

    if (deleteFromDB && it->second.GetItem())
    {
        SQLTransaction trans = CharacterDatabase.BeginTransaction();

        Item * item = it->second.GetItem().Release();
        item->FSetState(ITEM_REMOVED);
        item->SaveToDB(trans);

        CharacterDatabase.CommitTransaction(trans);
    }

    mAitems.erase( it );
    return true;
}

void AuctionHouseMgr::Update()
{
    PROFILE_SCOPE( "AuctionHouseMgr::Update" );

    mHordeAuctions.Update();
    mAllianceAuctions.Update();
    mNeutralAuctions.Update();
}

AuctionHouseEntry const* AuctionHouseMgr::GetAuctionHouseEntry(uint32 factionTemplateId)
{
    uint32 houseid = 7; // goblin auction house

    switch (factionTemplateId)
    {
        case   12: houseid = 1; break; // human
        case   29: houseid = 6; break; // orc, and generic for horde
        case   55: houseid = 2; break; // dwarf, and generic for alliance
        case   68: houseid = 4; break; // undead
        case   80: houseid = 3; break; // n-elf
        case  104: houseid = 5; break; // trolls
        case  120: houseid = 7; break; // booty bay, neutral
        case  474: houseid = 7; break; // gadgetzan, neutral
        case  855: houseid = 7; break; // everlook, neutral
        case 1604: houseid = 6; break; // b-elfs,
        default:                       // for unknown case
        {
            FactionTemplateEntry const* u_entry = sFactionTemplateStore.LookupEntry(factionTemplateId);
            if (!u_entry)
                houseid = 7; // goblin auction house
            else if (u_entry->ourMask & FACTION_MASK_ALLIANCE)
                houseid = 1; // human auction house
            else if (u_entry->ourMask & FACTION_MASK_HORDE)
                houseid = 6; // orc auction house
            else
                houseid = 7; // goblin auction house
            break;
        }
    }

    return sAuctionHouseStore.LookupEntry(houseid);
}

void AuctionHouseObject::AddAuction(AuctionEntry* auction)
{
    ASSERT(auction);

    if ( auction->aitem == nullptr )
    {
        auction->aitem = sAuctionMgr->GetAItem( auction->item_guidlow );
    }

    m_auctionsMap.insert( std::make_pair( auction->Id, auction ) );

    auto & auctions = m_ownerAuctionsMap[ auction->owner ];
    auctions.push_back( auction->Id );

    sScriptMgr->OnAuctionAdd(this, auction);
}

bool AuctionHouseObject::RemoveAuction(AuctionEntry* auction)
{
    bool wasInMap = m_auctionsMap.erase(auction->Id) ? true : false;

    sScriptMgr->OnAuctionRemove(this, auction);

    // we need to delete the entry, it is not referenced any more
    delete auction;
    auction = NULL;

    return wasInMap;
}

void AuctionHouseObject::Update()
{
    time_t checkTime = sWorld->GetGameTime() + 60;
    ///- Handle expired auctions

    // If storage is empty, no need to update. next == NULL in this case.
    if (m_auctionsMap.empty())
        return;

    SQLTransaction trans = CharacterDatabase.BeginTransaction();

    for (AuctionEntryMap::iterator itr, iter = m_auctionsMap.begin(); iter != m_auctionsMap.end(); )
    {
        itr = iter++;
        AuctionEntry* auction = (*itr).second;

        if (auction->expire_time > checkTime)
            continue;

        ///- Either cancel the auction if there was no bidder
        if (auction->bidder == 0)
        {
            sAuctionMgr->SendAuctionExpiredMail(auction, trans);
            sScriptMgr->OnAuctionExpire(this, auction);
        }
        ///- Or perform the transaction
        else
        {
            //we should send an "item sold" message if the seller is online
            //we send the item to the winner
            //we send the money to the seller
            sAuctionMgr->SendAuctionSuccessfulMail(auction, trans);
            sAuctionMgr->SendAuctionWonMail(auction, trans);
            sScriptMgr->OnAuctionSuccessful(this, auction);
        }

        ///- In any case clear the auction
        auction->DeleteFromDB(trans);

        sAuctionMgr->RemoveAItem(auction);
        RemoveAuction(auction);
    }
    CharacterDatabase.CommitTransaction(trans);
}

void AuctionHouseObject::BuildListBidderItems(WorldPacket& data, Player* player, uint32& count, uint32& totalcount)
{
    for ( AuctionEntryMap::const_iterator it = m_auctionsMap.begin(); it != m_auctionsMap.end(); ++it )
    {
        auto entry = it->second;
        if ( entry && entry->bidder == player->GetGUIDLow() )
        {
            if ( entry->BuildAuctionInfo( data ) )
                ++count;

            ++totalcount;
        }
    }
}

void AuctionHouseObject::BuildListOwnerItems(WorldPacket& data, Player* player, uint32& count, uint32& totalcount)
{
    auto it = m_ownerAuctionsMap.find( player->GetGUIDLow() );
    if ( it == m_ownerAuctionsMap.end() )
        return;

    for ( uint32 auctionId : it->second )
    {
        auto entry = GetAuction( auctionId );
        if ( entry != nullptr )
        {
            if ( entry->BuildAuctionInfo( data ) )
            {
                ++count;
            }

            ++totalcount;
        }
    }
}

bool AuctionHouseObject::BuildListAuctionItems(WorldPacket& data, Player* player,
    std::wstring const& wsearchedname, uint32 listfrom, uint8 levelmin, uint8 levelmax, uint8 usable,
    uint32 inventoryType, uint32 itemClass, uint32 itemSubClass, uint32 quality,
    uint32& count, uint32& totalcount, uint8 getAll)
{
    uint32 itrcounter = 0;

    // pussywizard: optimization, this is a simplified case
    if (itemClass == 0xffffffff && itemSubClass == 0xffffffff && inventoryType == 0xffffffff && quality == 0xffffffff && levelmin == 0x00 && levelmax == 0x00 && usable == 0x00 && wsearchedname.empty())
    {
        totalcount = Getcount();
        if (listfrom < totalcount)
        {
            AuctionEntryMap::iterator itr = m_auctionsMap.begin();
            std::advance(itr, listfrom);
            for (; itr != m_auctionsMap.end(); ++itr)
            {
                itr->second->BuildAuctionInfo(data);
                if ((++count) >= 50)
                    break;
            }
        }
        return true;
    }

    LocaleConstant loc_idx = player->GetSession()->GetSessionDbLocaleIndex();
    LocaleConstant locdbc_idx = player->GetSession()->GetSessionDbcLocale();
    time_t curTime = sWorld->GetGameTime();

    for ( AuctionEntryMap::const_iterator itr = m_auctionsMap.begin(); itr != m_auctionsMap.end(); ++itr )
    {
        if ( AsyncAuctionListingMgr::IsAuctionListingAllowed() == false ) // pussywizard: World::Update is waiting for us...
        {
            if ( ( itrcounter++ ) % 100 == 0 ) // check condition every 100 iterations
            {
                if ( avgDiffTracker.getAverage() >= 250 || getMSTimeDiff( World::GetGameTimeMS(), getMSTime() ) >= 200 ) // pussywizard: stop immediately if diff is high or waiting too long
                    return false;
            }
        }

        AuctionEntry* Aentry = itr->second;
        // Skip expired auctions
        if ( Aentry->expire_time < curTime )
            continue;

        const AuctionItem* item = Aentry->aitem;//sAuctionMgr->GetAItem( Aentry->item_guidlow );
        if ( !item || !item->GetItem() )
            continue;

        ItemTemplate const* proto = item->GetItemTemplate();
        if ( proto == nullptr )
            continue;

        if ( itemClass != 0xffffffff && proto->Class != itemClass )
            continue;

        if ( itemSubClass != 0xffffffff && proto->SubClass != itemSubClass )
            continue;

        if ( inventoryType != 0xffffffff && proto->InventoryType != inventoryType )
        {
            // xinef: exception, robes are counted as chests
            if ( inventoryType != INVTYPE_CHEST || proto->InventoryType != INVTYPE_ROBE )
                continue;
        }

        if ( quality != 0xffffffff && proto->Quality != quality )
            continue;

        if ( levelmin != 0x00 && ( proto->RequiredLevel < levelmin || ( levelmax != 0x00 && proto->RequiredLevel > levelmax ) ) )
            continue;

        if ( usable != 0x00 )
        {
            if ( player->CanUseItem( item->GetItem() ) != EQUIP_ERR_OK )
                continue;

            // xinef: check already learded recipes and pets
            if ( proto->Spells[ 1 ].SpellTrigger == ITEM_SPELLTRIGGER_LEARN_SPELL_ID && player->HasSpell( proto->Spells[ 1 ].SpellId ) )
                continue;
        }

        if ( !wsearchedname.empty() )
        {
            const std::wstring & wname = item->GetLocalizedName( loc_idx );
            if ( wname.empty() )
                continue;

            // Perform the search (with or without suffix)
            if ( wname.find( wsearchedname ) == std::wstring::npos )
                continue;
        }

        // Add the item if no search term or if entered search term was found
        if ( count < 50 && totalcount >= listfrom )
        {
            ++count;
            Aentry->BuildAuctionInfo( data );
        }
        ++totalcount;
    }

    return true;
}

//this function inserts to WorldPacket auction's data
bool AuctionEntry::BuildAuctionInfo(WorldPacket& data) const
{
    //const AuctionItem* aitem = sAuctionMgr->GetAItem(item_guidlow);
    if (!aitem || !aitem->GetItem())
    {
        sLog->outError("AuctionEntry::BuildAuctionInfo: Auction %u has a non-existent item: %u", Id, item_guidlow);
        return false;
    }

    auto & item = aitem->GetItem();

    data << uint32(Id);
    data << uint32(item->GetEntry());

    for (uint8 i = 0; i < MAX_INSPECTED_ENCHANTMENT_SLOT; ++i)
    {
        data << uint32(item->GetEnchantmentId(EnchantmentSlot(i)));
        data << uint32(item->GetEnchantmentDuration(EnchantmentSlot(i)));
        data << uint32(item->GetEnchantmentCharges(EnchantmentSlot(i)));
    }

    data << int32(item->GetItemRandomPropertyId());                 // Random item property id
    data << uint32(item->GetItemSuffixFactor());                    // SuffixFactor
    data << uint32(item->GetCount());                               // item->count
    data << uint32(item->GetSpellCharges(0, false));                // item->charge FFFFFFF
    data << uint32(0);                                              // Unknown
    data << uint64(owner);                                          // Auction->owner
    data << uint32(startbid);                                       // Auction->startbid (not sure if useful)
    data << uint32(bid ? GetAuctionOutBid() : 0);
    // Minimal outbid
    data << uint32(buyout);                                         // Auction->buyout
    data << uint32((expire_time - sWorld->GetGameTime()) * IN_MILLISECONDS);   // time left
    data << uint64(bidder);                                         // auction->bidder current
    data << uint32(bid);                                            // current bid
    return true;
}

uint32 AuctionEntry::GetAuctionCut() const
{
    int32 cut = int32(CalculatePct(bid, auctionHouseEntry->cutPercent) * sWorld->getRate(RATE_AUCTION_CUT));
    return std::max(cut, 0);
}

/// the sum of outbid is (1% from current bid)*5, if bid is very small, it is 1c
uint32 AuctionEntry::GetAuctionOutBid() const
{
    uint32 outbid = CalculatePct(bid, 5);
    return outbid ? outbid : 1;
}

void AuctionEntry::DeleteFromDB(SQLTransaction& trans) const
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_AUCTION);
    stmt->setUInt32(0, Id);
    trans->Append(stmt);
}

void AuctionEntry::SaveToDB(SQLTransaction& trans) const
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_AUCTION);
    stmt->setUInt32(0, Id);
    stmt->setUInt32(1, auctioneer);
    stmt->setUInt32(2, item_guidlow);
    stmt->setUInt32(3, owner);
    stmt->setUInt32 (4, buyout);
    stmt->setUInt32(5, uint32(expire_time));
    stmt->setUInt32(6, bidder);
    stmt->setUInt32 (7, bid);
    stmt->setUInt32 (8, startbid);
    stmt->setUInt32 (9, deposit);
    trans->Append(stmt);
}

bool AuctionEntry::LoadFromDB(Field* fields)
{
    Id = fields[0].GetUInt32();
    auctioneer = fields[1].GetUInt32();
    item_guidlow = fields[2].GetUInt32();
    item_template = fields[3].GetUInt32();
    itemCount = fields[4].GetUInt32();
    owner = fields[5].GetUInt32();
    buyout = fields[6].GetUInt32();
    expire_time = fields[7].GetUInt32();
    bidder = fields[8].GetUInt32();
    bid = fields[9].GetUInt32();
    startbid = fields[10].GetUInt32();
    deposit = fields[11].GetUInt32();

    CreatureData const* auctioneerData = sObjectMgr->GetCreatureData(auctioneer);
    if (!auctioneerData)
    {
        sLog->outError("Auction %u has not a existing auctioneer (GUID : %u)", Id, auctioneer);
        return false;
    }

    CreatureTemplate const* auctioneerInfo = sObjectMgr->GetCreatureTemplate(auctioneerData->id);
    if (!auctioneerInfo)
    {
        sLog->outError("Auction %u has not a existing auctioneer (GUID : %u Entry: %u)", Id, auctioneer, auctioneerData->id);
        return false;
    }

    factionTemplateId = auctioneerInfo->faction;
    auctionHouseEntry = AuctionHouseMgr::GetAuctionHouseEntry(factionTemplateId);
    if (!auctionHouseEntry)
    {
        sLog->outError("Auction %u has auctioneer (GUID : %u Entry: %u) with wrong faction %u", Id, auctioneer, auctioneerData->id, factionTemplateId);
        return false;
    }

    // check if sold item exists for guid
    // and item_template in fact (GetAItem will fail if problematic in result check in AuctionHouseMgr::LoadAuctionItems)

    aitem = sAuctionMgr->GetAItem( item_guidlow );
    if (!aitem)
    {
        sLog->outError("Auction %u has not a existing item : %u", Id, item_guidlow);
        return false;
    }
    return true;
}

bool AuctionEntry::LoadFromFieldList(Field* fields)
{
    // Loads an AuctionEntry item from a field list. Unlike "LoadFromDB()", this one
    //  does not require the AuctionEntryMap to have been loaded with items. It simply
    //  acts as a wrapper to fill out an AuctionEntry struct from a field list

    Id = fields[0].GetUInt32();
    auctioneer = fields[1].GetUInt32();
    item_guidlow = fields[2].GetUInt32();
    item_template = fields[3].GetUInt32();
    itemCount = fields[4].GetUInt32();
    owner = fields[5].GetUInt32();
    buyout = fields[6].GetUInt32();
    expire_time = fields[7].GetUInt32();
    bidder = fields[8].GetUInt32();
    bid = fields[9].GetUInt32();
    startbid = fields[10].GetUInt32();
    deposit = fields[11].GetUInt32();

    CreatureData const* auctioneerData = sObjectMgr->GetCreatureData(auctioneer);
    if (!auctioneerData)
    {
        sLog->outError("AuctionEntry::LoadFromFieldList() - Auction %u has not a existing auctioneer (GUID : %u)", Id, auctioneer);
        return false;
    }

    CreatureTemplate const* auctioneerInfo = sObjectMgr->GetCreatureTemplate(auctioneerData->id);
    if (!auctioneerInfo)
    {
        sLog->outError("AuctionEntry::LoadFromFieldList() - Auction %u has not a existing auctioneer (GUID : %u Entry: %u)", Id, auctioneer, auctioneerData->id);
        return false;
    }

    factionTemplateId = auctioneerInfo->faction;
    auctionHouseEntry = AuctionHouseMgr::GetAuctionHouseEntry(factionTemplateId);

    if (!auctionHouseEntry)
    {
        sLog->outError("AuctionEntry::LoadFromFieldList() - Auction %u has auctioneer (GUID : %u Entry: %u) with wrong faction %u", Id, auctioneer, auctioneerData->id, factionTemplateId);
        return false;
    }

    return true;
}

std::string AuctionEntry::BuildAuctionMailSubject(MailAuctionAnswers response) const
{
    std::ostringstream strm;
    strm << item_template << ":0:" << response << ':' << Id << ':' << itemCount;
    return strm.str();
}

std::string AuctionEntry::BuildAuctionMailBody(uint32 lowGuid, uint32 bid, uint32 buyout, uint32 deposit, uint32 cut)
{
    std::ostringstream strm;
    strm.width(16);
    strm << std::right << std::hex << MAKE_NEW_GUID(lowGuid, 0, HIGHGUID_PLAYER);   // HIGHGUID_PLAYER always present, even for empty guids
    strm << std::dec << ':' << bid << ':' << buyout;
    strm << ':' << deposit << ':' << cut;
    return strm.str();
}

AuctionItem::AuctionItem( Item * item )
    : m_item( item )
    , m_itemTemplate( item->GetTemplate() )
{
    for ( auto locale = (int)LOCALE_enUS; locale < TOTAL_LOCALES; ++locale )
    {
        std::string name = m_itemTemplate->Name1;
        if ( ItemLocale const* il = sObjectMgr->GetItemLocale( m_itemTemplate->ItemId ) )
        {
            ObjectMgr::GetLocaleString( il->Name, locale, name );
        }

        if ( int32 propRefID = item->GetItemRandomPropertyId() )
        {
            if ( const ItemRandomSuffixEntry* itemRandEntry = sItemRandomSuffixStore.LookupEntry( abs( item->GetItemRandomPropertyId() ) ) )
            {
                name.append( " " );
                name.append( itemRandEntry->nameSuffix[ ( int )locale ] );
            }
        }

        Utf8toWStr( name, m_localizedNames[ locale ] );
        wstrToLower( m_localizedNames[ locale ] );
    }
}

const std::wstring & AuctionItem::GetLocalizedName( LocaleConstant locale ) const
{
    return m_localizedNames[ locale ];
}
