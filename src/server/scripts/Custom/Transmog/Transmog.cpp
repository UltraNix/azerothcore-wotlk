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

#include "Transmogrification.h"


#define sT  sTransmogrification
#define GTS session->GetTrinityString // dropped translation support, no one using?

class npc_transmogrifier : public CreatureScript
{
public:
    npc_transmogrifier() : CreatureScript("npc_transmogrifier") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        WorldSession* session = player->GetSession();
        bool noXPGain = player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN);

        if (sT->GetEnableTransmogInfo())
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tHow transmogrification works", EQUIPMENT_SLOT_END + 4, 0);

        for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
        {
            if (const char* slotName = sT->GetSlotName(slot, session))
            {
                ItemRef newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
                uint32 entry = newItem ? sT->GetFakeEntry(newItem->GetGUID()) : 0;
                std::string icon = entry ? sT->GetItemIcon(entry, 30, 30, -18, 0) : sT->GetSlotIcon(slot, 30, 30, -18, 0);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, icon + std::string(slotName), EQUIPMENT_SLOT_END, slot);
            }
        }

        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Enchant_Disenchant:30:30:-18:0|tRemove all transmogrifications", EQUIPMENT_SLOT_END + 2, 0, "Are you sure you want to reset all transmog?", 0, false);

        std::ostringstream ss;
        if (player->HasDisabledTransmogVisibility())
        {
            ss << ((sT->GetVisibilityTransmogCost() / GOLD) * 5) << " gold." << std::endl;
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Enchant_Disenchant:30:30:-18:0|tEnable transmog visibility.", EQUIPMENT_SLOT_END + 900, 0, "Are you sure you want to enable visibility of transmogs?\nIt will cost you: " + ss.str(), 0, false);
        }
        else {
            ss << ((sT->GetVisibilityTransmogCost() / GOLD)) << " gold." << std::endl;
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Enchant_Disenchant:30:30:-18:0|tDisable transmog visibility.", EQUIPMENT_SLOT_END + 900, 0, "Are you sure you want to disable visibility of transmogs?\nIt will cost you: " + ss.str(), 0, false);
        }

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-18:0|tUpdate menu", EQUIPMENT_SLOT_END + 1, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        WorldSession* session = player->GetSession();
        bool noXPGain = player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN);

        switch (sender)
        {
            case EQUIPMENT_SLOT_END: // Show items you can use
                ShowTransmogItems(player, creature, action);
                break;
            case EQUIPMENT_SLOT_END + 1: // Main menu
                OnGossipHello(player, creature);
                break;
            case EQUIPMENT_SLOT_END + 2: // Remove Transmogrifications
            {
                bool removed = false;
                SQLTransaction trans = CharacterDatabase.BeginTransaction();
                for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
                {
                    if (ItemRef newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                    {
                        if (!sT->GetFakeEntry(newItem->GetGUID()))
                            continue;
                        sT->DeleteFakeEntry(player, slot, newItem, &trans);
                        removed = true;
                    }
                }
                if (removed)
                {
                    session->SendAreaTriggerMessage(GTS(LANG_ERR_UNTRANSMOG_OK));
                    CharacterDatabase.CommitTransaction(trans);
                }
                else
                    session->SendNotification(LANG_ERR_UNTRANSMOG_NO_TRANSMOGS);
                OnGossipHello(player, creature);
            } break;
            case EQUIPMENT_SLOT_END + 3: // Remove Transmogrification from single item
            {
                if (ItemRef newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, action))
                {
                    if (sT->GetFakeEntry(newItem->GetGUID()))
                    {
                        sT->DeleteFakeEntry(player, action, newItem);
                        session->SendAreaTriggerMessage(GTS(LANG_ERR_UNTRANSMOG_OK));
                    }
                    else
                        session->SendNotification(LANG_ERR_UNTRANSMOG_NO_TRANSMOGS);
                }
                OnGossipSelect(player, creature, EQUIPMENT_SLOT_END, action);
            } break;
            case EQUIPMENT_SLOT_END + 4: // Transmog info
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tBack.", EQUIPMENT_SLOT_END + 1, 0);
                player->SEND_GOSSIP_MENU(TRANMOG_TEXT_ENTRY_1, creature->GetGUID());
            } break;
            case EQUIPMENT_SLOT_END + 900:
            {
                if (!player->HasEnoughMoney(player->HasDisabledTransmogVisibility() ? (sT->GetVisibilityTransmogCost() * 5) : (sT->GetVisibilityTransmogCost())))
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("You don't have enough money for that.");
                    break;
                }

                if (player->HasDisabledTransmogVisibility())
                    ChatHandler(player->GetSession()).PSendSysMessage("Transmog visibility has been enabled, please relog to apply.");
                else
                    ChatHandler(player->GetSession()).PSendSysMessage("Transmog visibility has been disabled, please relog to apply.");

                player->ModifyMoney(player->HasDisabledTransmogVisibility() ? -(sT->GetVisibilityTransmogCost() * 5) : -(sT->GetVisibilityTransmogCost()));
                player->SetDisabledTransmogVisibility(player->HasDisabledTransmogVisibility() ? false : true);

                OnGossipHello(player, creature);
                return true;

            } break;
            default: // Transmogrify
            {
                if (!sender && !action)
                {
                    OnGossipHello(player, creature);
                    return true;
                }
                // sender = slot, action = display
                TransmogTrinityStrings res = sT->Transmogrify(player, MAKE_NEW_GUID(action, 0, HIGHGUID_ITEM), sender);
                if (res == LANG_ERR_TRANSMOG_OK)
                {
                    session->SendAreaTriggerMessage(GTS(LANG_ERR_TRANSMOG_OK));
                    player->SaveToDB(false, false);
                }
                else
                    session->SendNotification(res);
                // OnGossipSelect(player, creature, EQUIPMENT_SLOT_END, sender);
                // ShowTransmogItems(player, creature, sender);
                player->CLOSE_GOSSIP_MENU(); // Wait for SetMoney to get fixed, issue #10053
            } break;
        }
        return true;
    }
    
    void ShowTransmogItems(Player* player, Creature* creature, uint8 slot) // Only checks bags while can use an item from anywhere in inventory
    {
        WorldSession* session = player->GetSession();
        ItemRef oldItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (oldItem)
        {
            uint32 limit = 0;

            for (uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
            {
                if (limit > MAX_OPTIONS)
                    break;
                ItemRef newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
                if (!newItem)
                    continue;
                if (!sT->CanTransmogrifyItemWithItem(player, oldItem->GetTemplate(), newItem->GetTemplate()))
                    continue;
                if (sT->GetFakeEntry(oldItem->GetGUID()) == newItem->GetEntry())
                    continue;
                ++limit;

                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, sT->GetItemIcon(newItem->GetEntry(), 30, 30, -18, 0) + sT->GetItemLink(newItem, session), slot, newItem->GetGUIDLow(), "Using this item for transmogrify will bind it to you and make it non-refundable and non-tradeable.\nDo you wish to continue?\n\n" + sT->GetItemIcon(newItem->GetEntry(), 40, 40, -15, -10) + sT->GetItemLink(newItem, session) + ShowPrices(player, newItem), 0, false);
            }

            for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
            {
                Bag* bag = player->GetBagByPos(i);
                if (!bag)
                    continue;
                for (uint32 j = 0; j < bag->GetBagSize(); ++j)
                {
                    if (limit > MAX_OPTIONS)
                        break;
                    ItemRef newItem = player->GetItemByPos(i, j);
                    if (!newItem)
                        continue;
                    if (!sT->CanTransmogrifyItemWithItem(player, oldItem->GetTemplate(), newItem->GetTemplate()))
                        continue;
                    if (sT->GetFakeEntry(oldItem->GetGUID()) == newItem->GetEntry())
                        continue;
                    ++limit;

                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, sT->GetItemIcon(newItem->GetEntry(), 30, 30, -18, 0) + sT->GetItemLink(newItem, session), slot, newItem->GetGUIDLow(), "Using this item for transmogrify will bind it to you and make it non-refundable and non-tradeable.\nDo you wish to continue?\n\n" + sT->GetItemIcon(newItem->GetEntry(), 40, 40, -15, -10) + sT->GetItemLink(newItem, session) + ShowPrices(player, newItem), 0, false);
                }
            }
        }

        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Enchant_Disenchant:30:30:-18:0|tRemove transmogrification", EQUIPMENT_SLOT_END + 3, slot, "Are you sure you want to reset transmog?", 0, false);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-18:0|tUpdate menu", EQUIPMENT_SLOT_END, slot);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tBack.", EQUIPMENT_SLOT_END + 1, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
    }

    std::string ShowPrices(Player* player, ItemRef const& item)
    {
        std::ostringstream ss;
        ss << std::endl;

        if (!player || !item)
            return ss.str();

        WorldSession* session = player->GetSession();


        if (item->GetTemplate()->Class == ITEM_CLASS_ARMOR)
            sT->GetTokenEntryArmor() != 0 ? (ss << std::endl << "1" << " x " << sT->GetItemLink(sT->GetTokenEntryArmor(), session)) : ss << "";
        else if (item->GetTemplate()->Class == WEAPON_TRANSMOG && item->GetTemplate()->Quality <= ITEM_QUALITY_EPIC)
            sT->GetTokenEntryArmor() != 0 ? (ss << std::endl << "1" << " x " << sT->GetItemLink(sT->GetTokenEntryWeapon(), session)) : ss << "";
        else if (item->GetTemplate()->Class == WEAPON_TRANSMOG && item->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY)
            sT->GetTokenEntryArmor() != 0 ? (ss << std::endl << "15" << " x " << sT->GetItemLink(sT->GetTokenEntryWeapon(), session)) : ss << "";

        return ss.str();
    }
};

class PS_Transmogrification : public PlayerScript
{
public:
    PS_Transmogrification() : PlayerScript("Player_Transmogrify") { }

    void OnAfterSetVisibleItemSlot(Player* player, uint8 slot, ItemRef const& item) {
        if (!item)
            return;

        if (uint32 entry = sT->GetFakeEntry(item->GetGUID()))
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (slot * 2), entry);
    }

    void OnAfterMoveItemFromInventory(Player* player, ItemRef const& it, uint8 bag, uint8 slot, bool update) {
        sT->DeleteFakeFromDB(it->GetGUIDLow());
    }
    
    void OnLogin(Player* player)
    {
        uint64 playerGUID = player->GetGUID();
        sT->entryMap.erase(playerGUID);
        QueryResult result = CharacterDatabase.PQuery("SELECT GUID, FakeEntry FROM custom_transmogrification WHERE Owner = %u", player->GetGUIDLow());
        if (result)
        {
            do
            {
                uint64 itemGUID = MAKE_NEW_GUID((*result)[0].GetUInt32(), 0, HIGHGUID_ITEM);
                uint32 fakeEntry = (*result)[1].GetUInt32();
                if (sObjectMgr->GetItemTemplate(fakeEntry))
                {
                    sT->dataMap[itemGUID] = playerGUID;
                    sT->entryMap[playerGUID][itemGUID] = fakeEntry;
                }
                else
                {
                    //sLog->outError(LOG_FILTER_SQL, "Item entry (Entry: %u, itemGUID: %u, playerGUID: %u) does not exist, ignoring.", fakeEntry, GUID_LOPART(itemGUID), player->GetGUIDLow());
                    // CharacterDatabase.PExecute("DELETE FROM custom_transmogrification WHERE FakeEntry = %u", fakeEntry);
                }
            } while (result->NextRow());

            for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
            {
                if (ItemRef item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                    player->SetVisibleItemSlot(slot, item);
            }
        }
    }
};

class WS_Transmogrification : public WorldScript
{
public:
    WS_Transmogrification() : WorldScript("WS_Transmogrification") { }

    void OnConfigLoad(bool reload)
    {
        if (reload)
            sT->LoadConfig(reload);
    }

    void OnStartup()
    {
        sT->LoadConfig(false);
        //sLog->outInfo(LOG_FILTER_SERVER_LOADING, "Deleting non-existing transmogrification entries...");
        CharacterDatabase.Execute("DELETE FROM custom_transmogrification WHERE NOT EXISTS (SELECT 1 FROM item_instance WHERE item_instance.guid = custom_transmogrification.GUID)");
    }
};

class global_transmog_script : public GlobalScript {
    public:
        global_transmog_script() : GlobalScript("global_transmog_script") { }
        
        void OnItemDelFromDB(SQLTransaction& trans, uint32 itemGuid) {
            sT->DeleteFakeFromDB(itemGuid, &trans);
        }
        
        void OnMirrorImageDisplayItem( ItemRef const& item, uint32 &display) {
            if (uint32 entry = sTransmogrification->GetFakeEntry(item->GetGUID()))
                display=uint32(sObjectMgr->GetItemTemplate(entry)->DisplayInfoID);
        }
};

void AddSC_transmog() {
    new global_transmog_script();
    new npc_transmogrifier();
    new PS_Transmogrification();
    new WS_Transmogrification();
}