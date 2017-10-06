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
#include "BazaarMgr.h"

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

        if ((player->HasTransmogModelPvE() || player->HasTransmogModelPvP() || player->HasTransmogModelMIX() || player->HasTransmogModelTWK() && sT->CustomModelCost) || !sT->CustomModelCost)
        {
            if (sT->GetEnableTransmogInfo())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tHow transmogrification works", EQUIPMENT_SLOT_END + 4, 0);

            for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
            {
                if (const char* slotName = sT->GetSlotName(slot, session))
                {
                    Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
                    uint32 entry = newItem ? sT->GetFakeEntry(newItem->GetGUID()) : 0;
                    std::string icon = entry ? sT->GetItemIcon(entry, 30, 30, -18, 0) : sT->GetSlotIcon(slot, 30, 30, -18, 0);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, icon + std::string(slotName), EQUIPMENT_SLOT_END, slot);
                }
            }

            std::ostringstream ss;
            ss << (sT->GetFullRemoveCost() / GOLD)<< " gold." << std::endl;
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Enchant_Disenchant:30:30:-18:0|tRemove all transmogrifications", EQUIPMENT_SLOT_END + 2, 0, "Remove transmogrifications from all equipped items?\n\nAre you sure you want to reset all transmog?\nIt will cost you: " + ss.str(), 0, false);

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tReset the Model.", EQUIPMENT_SLOT_END + 900, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-18:0|tUpdate menu", EQUIPMENT_SLOT_END + 1, 0);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        else
        {
            if (noXPGain)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tThrough Twink model.", EQUIPMENT_SLOT_END + 800, 0);
            else
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tThrough PvE model.", EQUIPMENT_SLOT_END + 500, 0);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tThrough PvP model.", EQUIPMENT_SLOT_END + 600, 0);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tThrough Mixed model.", EQUIPMENT_SLOT_END + 700, 0);
            } 

            player->SEND_GOSSIP_MENU(TRANMOG_TEXT_ENTRY_2, creature->GetGUID());
        }
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
                    if (Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                    {
                        if (!sT->GetFakeEntry(newItem->GetGUID()))
                            continue;
                        sT->DeleteFakeEntry(player, slot, newItem, &trans);
                        removed = true;
                    }
                }
                if (removed)
                {
                    player->ModifyMoney(-sT->GetFullRemoveCost());
                    session->SendAreaTriggerMessage(GTS(LANG_ERR_UNTRANSMOG_OK));
                    CharacterDatabase.CommitTransaction(trans);
                }
                else
                    session->SendNotification(LANG_ERR_UNTRANSMOG_NO_TRANSMOGS);
                OnGossipHello(player, creature);
            } break;
            case EQUIPMENT_SLOT_END + 3: // Remove Transmogrification from single item
            {
                if (Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, action))
                {
                    if (sT->GetFakeEntry(newItem->GetGUID()))
                    {
                        player->ModifyMoney(-sT->GetRemoveCost());
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
            // PvE Model
            case EQUIPMENT_SLOT_END + 500:
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tUse PvE model.", EQUIPMENT_SLOT_END + 501, 0);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tBack.", EQUIPMENT_SLOT_END + 1, 0);
                player->SEND_GOSSIP_MENU(TRANMOG_TEXT_ENTRY_4, creature->GetGUID());
                return true;
            } break;
            case EQUIPMENT_SLOT_END + 501:
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tConfirm PvE model.", EQUIPMENT_SLOT_END + 502, 0);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tBack.", EQUIPMENT_SLOT_END + 1, 0);
                player->SEND_GOSSIP_MENU(TRANMOG_TEXT_ENTRY_8, creature->GetGUID());
                return true;
            } break;
            case EQUIPMENT_SLOT_END + 502:
            {
                player->SaveToDB(false, true);
                player->SetTransmogModelPvE();
                OnGossipHello(player, creature);
                return true;
            } break;
            // PvP Model
            case EQUIPMENT_SLOT_END + 600:
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tUse PvP model.", EQUIPMENT_SLOT_END + 601, 0);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tBack.", EQUIPMENT_SLOT_END + 1, 0);
                player->SEND_GOSSIP_MENU(TRANMOG_TEXT_ENTRY_3, creature->GetGUID());
                return true;
            } break;
            case EQUIPMENT_SLOT_END + 601:
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tConfirm PvP model.", EQUIPMENT_SLOT_END + 602, 0);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tBack.", EQUIPMENT_SLOT_END + 1, 0);
                player->SEND_GOSSIP_MENU(TRANMOG_TEXT_ENTRY_7, creature->GetGUID());
                return true;
            } break;
            case EQUIPMENT_SLOT_END + 602:
            {
                player->SetTransmogModelPvP();
                player->SaveToDB(false, false);
                OnGossipHello(player, creature);
                return true;
            } break;
            // Mixed Model
            case EQUIPMENT_SLOT_END + 700:
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tUse Mixed model.", EQUIPMENT_SLOT_END + 701, 0);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tBack.", EQUIPMENT_SLOT_END + 1, 0);
                player->SEND_GOSSIP_MENU(TRANMOG_TEXT_ENTRY_6, creature->GetGUID());
                return true;
            } break;
            case EQUIPMENT_SLOT_END + 701:
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tConfirm Mixed model.", EQUIPMENT_SLOT_END + 702, 0);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tBack.", EQUIPMENT_SLOT_END + 1, 0);
                player->SEND_GOSSIP_MENU(TRANMOG_TEXT_ENTRY_10, creature->GetGUID());
                return true;
            } break;
            case EQUIPMENT_SLOT_END + 702:
            {
                player->SetTransmogModelMIX();
                player->SaveToDB(false, false);
                OnGossipHello(player, creature);
                return true;
            } break;
            // Twink Model
            case EQUIPMENT_SLOT_END + 800:
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tUse Twink model.", EQUIPMENT_SLOT_END + 801, 0);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tBack.", EQUIPMENT_SLOT_END + 1, 0);
                player->SEND_GOSSIP_MENU(TRANMOG_TEXT_ENTRY_5, creature->GetGUID());
                return true;
            } break;
            case EQUIPMENT_SLOT_END + 801:
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tConfirm Twink model.", EQUIPMENT_SLOT_END + 802, 0);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tBack.", EQUIPMENT_SLOT_END + 1, 0);
                player->SEND_GOSSIP_MENU(TRANMOG_TEXT_ENTRY_9, creature->GetGUID());
                return true;
            } break;
            case EQUIPMENT_SLOT_END + 802:
            {
                if (!noXPGain)
                {
                    session->SendNotification(LANG_ERR_TRANSMOG_TWINK_EXPERIENCE);
                    OnGossipHello(player, creature);
                    return true;
                }

                player->SetTransmogModelTWK();
                player->SaveToDB(false, false);
                OnGossipHello(player, creature);
                return true;
            } break;
            // Model Reset
            case EQUIPMENT_SLOT_END + 900:
            {
                std::ostringstream ss;
                ss << "Model Reset\n\n" << "It will cost you:\n\n " << sT->GetResetCoinCost() << " Sunwell Coins and " << (sT->GetResetGoldCost() / GOLD) <<  " gold." << std::endl;
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Gizmo_02:30:30:-18:0|tYes, I am sure.", EQUIPMENT_SLOT_END + 901, 0,  ss.str(), 0, false);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tNo, go back.", EQUIPMENT_SLOT_END + 1, 0);
                player->SEND_GOSSIP_MENU(TRANMOG_TEXT_ENTRY_12, creature->GetGUID());
                return true;
            } break;
            case EQUIPMENT_SLOT_END + 901:
            {
                uint32 accId = session->GetAccountId();
                if (!sBazaarMgr->CheckPremiumAmount(accId, sT->GetResetCoinCost()) || !player->HasEnoughMoney(sT->GetResetGoldCost()))
                {
                    session->SendNotification(LANG_ERR_TRANSMOG_MISSING_COINS);
                    OnGossipHello(player, creature);
                    return true;
                }

                sBazaarMgr->TakeRequiredAmount(player, sT->GetResetCoinCost(), AUCTION_SELL_PREMIUM);
                player->ModifyMoney(-sT->GetResetGoldCost());
                player->ResetTransmogModel();
                player->SaveToDB(false, false);
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
        Item* oldItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (oldItem)
        {
            uint32 limit = 0;
            std::ostringstream ss;
            ss << std::endl;

            for (uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
            {
                if (limit > MAX_OPTIONS)
                    break;
                Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
                if (!newItem)
                    continue;
                if (!sT->CanTransmogrifyItemWithItem(player, oldItem->GetTemplate(), newItem->GetTemplate()))
                    continue;
                if (sT->GetFakeEntry(oldItem->GetGUID()) == newItem->GetEntry())
                    continue;
                ++limit;

                if (sT->GetCustomModelCost())
                {
                    if (player->HasTransmogModelPvE())
                    {
                        if (newItem->GetTemplate()->Quality != ITEM_QUALITY_LEGENDARY)
                        {
                            sT->GetAmountTokenRDF_PvE() != 0 ? (ss << std::endl << sT->GetAmountTokenRDF_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                            sT->GetAmountTokenBG_PvE()  != 0 ? (ss << std::endl << sT->GetAmountTokenBG_PvE()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                            sT->GetAmountTokenWG_PvE()  != 0 ? (ss << std::endl << sT->GetAmountTokenWG_PvE()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                            sT->GetAmountToken2V2_PvE() != 0 ? (ss << std::endl << sT->GetAmountToken2V2_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                            sT->GetAmountToken3V3_PvE() != 0 ? (ss << std::endl << sT->GetAmountToken3V3_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                            sT->GetAmountTokenORB_PvE() != 0 ? (ss << std::endl << sT->GetAmountTokenORB_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                            sT->GetAmountTokenGEM_PvE() != 0 ? (ss << std::endl << sT->GetAmountTokenGEM_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                            sT->GetMoneyAmount_PvE()    != 0 ? (ss << std::endl << (sT->GetMoneyAmount_PvE() / GOLD) << " gold. ") : ss << "";
                        }
                        else
                        {
                            sT->GetLegendaryAmountTokenRDF_PvE() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenRDF_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenBG_PvE()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenBG_PvE()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenWG_PvE()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenWG_PvE()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                            sT->GetLegendaryAmountToken2V2_PvE() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken2V2_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                            sT->GetLegendaryAmountToken3V3_PvE() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken3V3_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenORB_PvE() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenORB_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenGEM_PvE() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenGEM_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                            sT->GetLegendaryMoneyAmount_PvE()    != 0 ? (ss << std::endl << (sT->GetLegendaryMoneyAmount_PvE() / GOLD) << " gold. ") : ss << "";
                        }
                    }
                    else if (player->HasTransmogModelPvP())
                    {
                        if (newItem->GetTemplate()->Quality != ITEM_QUALITY_LEGENDARY)
                        {
                            sT->GetAmountTokenRDF_PvP() != 0 ? (ss << std::endl << sT->GetAmountTokenRDF_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                            sT->GetAmountTokenBG_PvP()  != 0 ? (ss << std::endl << sT->GetAmountTokenBG_PvP()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                            sT->GetAmountTokenWG_PvP()  != 0 ? (ss << std::endl << sT->GetAmountTokenWG_PvP()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                            sT->GetAmountToken2V2_PvP() != 0 ? (ss << std::endl << sT->GetAmountToken2V2_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                            sT->GetAmountToken3V3_PvP() != 0 ? (ss << std::endl << sT->GetAmountToken3V3_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                            sT->GetAmountTokenORB_PvP() != 0 ? (ss << std::endl << sT->GetAmountTokenORB_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                            sT->GetAmountTokenGEM_PvP() != 0 ? (ss << std::endl << sT->GetAmountTokenGEM_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                            sT->GetMoneyAmount_PvP()    != 0 ? (ss << std::endl << (sT->GetMoneyAmount_PvP() / GOLD) << " gold. ") : ss << "";
                        }
                        else
                        {

                            sT->GetLegendaryAmountTokenRDF_PvP() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenRDF_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenBG_PvP()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenBG_PvP()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenWG_PvP()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenWG_PvP()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                            sT->GetLegendaryAmountToken2V2_PvP() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken2V2_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                            sT->GetLegendaryAmountToken3V3_PvP() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken3V3_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenORB_PvP() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenORB_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenGEM_PvP() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenGEM_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                            sT->GetLegendaryMoneyAmount_PvP()    != 0 ? (ss << std::endl << (sT->GetLegendaryMoneyAmount_PvP() / GOLD) << " gold. ") : ss << "";
                        }
                    }
                    else if (player->HasTransmogModelMIX())
                    {
                        if (newItem->GetTemplate()->Quality != ITEM_QUALITY_LEGENDARY)
                        {
                            sT->GetAmountTokenRDF_Mix() != 0 ? (ss << std::endl << sT->GetAmountTokenRDF_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                            sT->GetAmountTokenBG_Mix()  != 0 ? (ss << std::endl << sT->GetAmountTokenBG_Mix()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                            sT->GetAmountTokenWG_Mix()  != 0 ? (ss << std::endl << sT->GetAmountTokenWG_Mix()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                            sT->GetAmountToken2V2_Mix() != 0 ? (ss << std::endl << sT->GetAmountToken2V2_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                            sT->GetAmountToken3V3_Mix() != 0 ? (ss << std::endl << sT->GetAmountToken3V3_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                            sT->GetAmountTokenORB_Mix() != 0 ? (ss << std::endl << sT->GetAmountTokenORB_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                            sT->GetAmountTokenGEM_Mix() != 0 ? (ss << std::endl << sT->GetAmountTokenGEM_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                            sT->GetMoneyAmount_Mix()    != 0 ? (ss << std::endl << (sT->GetMoneyAmount_Mix() / GOLD) << " gold. ") : ss << "";
                        }
                        else
                        {
                            sT->GetLegendaryAmountTokenRDF_Mix() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenRDF_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenBG_Mix()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenBG_Mix()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenWG_Mix()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenWG_Mix()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                            sT->GetLegendaryAmountToken2V2_Mix() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken2V2_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                            sT->GetLegendaryAmountToken3V3_Mix() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken3V3_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenORB_Mix() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenORB_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenGEM_Mix() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenGEM_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                            sT->GetLegendaryMoneyAmount_Mix()    != 0 ? (ss << std::endl << (sT->GetLegendaryMoneyAmount_Mix() / GOLD) << " gold. ") : ss << "";
                        }
                    }
                    else if (player->HasTransmogModelTWK())
                    {
                        if (newItem->GetTemplate()->Quality != ITEM_QUALITY_LEGENDARY)
                        {
                            sT->GetAmountTokenRDF_Twink() != 0 ? (ss << std::endl << sT->GetAmountTokenRDF_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                            sT->GetAmountTokenBG_Twink()  != 0 ? (ss << std::endl << sT->GetAmountTokenBG_Twink()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                            sT->GetAmountTokenWG_Twink()  != 0 ? (ss << std::endl << sT->GetAmountTokenWG_Twink()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                            sT->GetAmountToken2V2_Twink() != 0 ? (ss << std::endl << sT->GetAmountToken2V2_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                            sT->GetAmountToken3V3_Twink() != 0 ? (ss << std::endl << sT->GetAmountToken3V3_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                            sT->GetAmountTokenORB_Twink() != 0 ? (ss << std::endl << sT->GetAmountTokenORB_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                            sT->GetAmountTokenGEM_Twink() != 0 ? (ss << std::endl << sT->GetAmountTokenGEM_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                            sT->GetMoneyAmount_Twink()    != 0 ? (ss << std::endl << (sT->GetMoneyAmount_Twink() / GOLD) << " gold. ") : ss << "";
                        }
                        else
                        {
                            sT->GetLegendaryAmountTokenRDF_Twink() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenRDF_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenBG_Twink()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenBG_Twink()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenWG_Twink()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenWG_Twink()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                            sT->GetLegendaryAmountToken2V2_Twink() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken2V2_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                            sT->GetLegendaryAmountToken3V3_Twink() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken3V3_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenORB_Twink() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenORB_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                            sT->GetLegendaryAmountTokenGEM_Twink() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenGEM_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                            sT->GetLegendaryMoneyAmount_Twink()    != 0 ? (ss << std::endl << (sT->GetLegendaryMoneyAmount_Twink() / GOLD) << " gold. ") : ss << "";
                        }
                    }
                }

                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, sT->GetItemIcon(newItem->GetEntry(), 30, 30, -18, 0) + sT->GetItemLink(newItem, session), slot, newItem->GetGUIDLow(), "Using this item for transmogrify will bind it to you and make it non-refundable and non-tradeable.\nDo you wish to continue?\n\n" + sT->GetItemIcon(newItem->GetEntry(), 40, 40, -15, -10) + sT->GetItemLink(newItem, session) + ss.str(), 0, false);
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
                    Item* newItem = player->GetItemByPos(i, j);
                    if (!newItem)
                        continue;
                    if (!sT->CanTransmogrifyItemWithItem(player, oldItem->GetTemplate(), newItem->GetTemplate()))
                        continue;
                    if (sT->GetFakeEntry(oldItem->GetGUID()) == newItem->GetEntry())
                        continue;
                    ++limit;

                    if (sT->GetCustomModelCost())
                    {
                        if (player->HasTransmogModelPvE())
                        {
                            if (newItem->GetTemplate()->Quality != ITEM_QUALITY_LEGENDARY)
                            {
                                sT->GetAmountTokenRDF_PvE() != 0 ? (ss << std::endl << sT->GetAmountTokenRDF_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                                sT->GetAmountTokenBG_PvE()  != 0 ? (ss << std::endl << sT->GetAmountTokenBG_PvE()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                                sT->GetAmountTokenWG_PvE()  != 0 ? (ss << std::endl << sT->GetAmountTokenWG_PvE()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                                sT->GetAmountToken2V2_PvE() != 0 ? (ss << std::endl << sT->GetAmountToken2V2_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                                sT->GetAmountToken3V3_PvE() != 0 ? (ss << std::endl << sT->GetAmountToken3V3_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                                sT->GetAmountTokenORB_PvE() != 0 ? (ss << std::endl << sT->GetAmountTokenORB_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                                sT->GetAmountTokenGEM_PvE() != 0 ? (ss << std::endl << sT->GetAmountTokenGEM_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                                sT->GetMoneyAmount_PvE()    != 0 ? (ss << std::endl << (sT->GetMoneyAmount_PvE() / GOLD) << " gold. ") : ss << "";
                            }
                            else
                            {
                                sT->GetLegendaryAmountTokenRDF_PvE() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenRDF_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenBG_PvE()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenBG_PvE()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenWG_PvE()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenWG_PvE()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                                sT->GetLegendaryAmountToken2V2_PvE() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken2V2_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                                sT->GetLegendaryAmountToken3V3_PvE() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken3V3_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenORB_PvE() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenORB_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenGEM_PvE() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenGEM_PvE() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                                sT->GetLegendaryMoneyAmount_PvE()    != 0 ? (ss << std::endl << (sT->GetLegendaryMoneyAmount_PvE() / GOLD) << " gold. ") : ss << "";
                            }
                        }
                        else if (player->HasTransmogModelPvP())
                        {
                            if (newItem->GetTemplate()->Quality != ITEM_QUALITY_LEGENDARY)
                            {
                                sT->GetAmountTokenRDF_PvP() != 0 ? (ss << std::endl << sT->GetAmountTokenRDF_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                                sT->GetAmountTokenBG_PvP()  != 0 ? (ss << std::endl << sT->GetAmountTokenBG_PvP()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                                sT->GetAmountTokenWG_PvP()  != 0 ? (ss << std::endl << sT->GetAmountTokenWG_PvP()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                                sT->GetAmountToken2V2_PvP() != 0 ? (ss << std::endl << sT->GetAmountToken2V2_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                                sT->GetAmountToken3V3_PvP() != 0 ? (ss << std::endl << sT->GetAmountToken3V3_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                                sT->GetAmountTokenORB_PvP() != 0 ? (ss << std::endl << sT->GetAmountTokenORB_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                                sT->GetAmountTokenGEM_PvP() != 0 ? (ss << std::endl << sT->GetAmountTokenGEM_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                                sT->GetMoneyAmount_PvP()    != 0 ? (ss << std::endl << (sT->GetMoneyAmount_PvP() / GOLD) << " gold. ") : ss << "";
                            }
                            else
                            {

                                sT->GetLegendaryAmountTokenRDF_PvP() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenRDF_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenBG_PvP()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenBG_PvP()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenWG_PvP()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenWG_PvP()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                                sT->GetLegendaryAmountToken2V2_PvP() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken2V2_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                                sT->GetLegendaryAmountToken3V3_PvP() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken3V3_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenORB_PvP() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenORB_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenGEM_PvP() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenGEM_PvP() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                                sT->GetLegendaryMoneyAmount_PvP()    != 0 ? (ss << std::endl << (sT->GetLegendaryMoneyAmount_PvP() / GOLD) << " gold. ") : ss << "";
                            }
                        }
                        else if (player->HasTransmogModelMIX())
                        {
                            if (newItem->GetTemplate()->Quality != ITEM_QUALITY_LEGENDARY)
                            {
                                sT->GetAmountTokenRDF_Mix() != 0 ? (ss << std::endl << sT->GetAmountTokenRDF_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                                sT->GetAmountTokenBG_Mix()  != 0 ? (ss << std::endl << sT->GetAmountTokenBG_Mix()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                                sT->GetAmountTokenWG_Mix()  != 0 ? (ss << std::endl << sT->GetAmountTokenWG_Mix()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                                sT->GetAmountToken2V2_Mix() != 0 ? (ss << std::endl << sT->GetAmountToken2V2_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                                sT->GetAmountToken3V3_Mix() != 0 ? (ss << std::endl << sT->GetAmountToken3V3_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                                sT->GetAmountTokenORB_Mix() != 0 ? (ss << std::endl << sT->GetAmountTokenORB_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                                sT->GetAmountTokenGEM_Mix() != 0 ? (ss << std::endl << sT->GetAmountTokenGEM_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                                sT->GetMoneyAmount_Mix()    != 0 ? (ss << std::endl << (sT->GetMoneyAmount_Mix() / GOLD) << " gold. ") : ss << "";
                            }
                            else
                            {
                                sT->GetLegendaryAmountTokenRDF_Mix() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenRDF_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenBG_Mix()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenBG_Mix()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenWG_Mix()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenWG_Mix()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                                sT->GetLegendaryAmountToken2V2_Mix() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken2V2_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                                sT->GetLegendaryAmountToken3V3_Mix() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken3V3_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenORB_Mix() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenORB_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenGEM_Mix() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenGEM_Mix() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                                sT->GetLegendaryMoneyAmount_Mix()    != 0 ? (ss << std::endl << (sT->GetLegendaryMoneyAmount_Mix() / GOLD) << " gold. ") : ss << "";
                            }
                        }
                        else if (player->HasTransmogModelTWK())
                        {
                            if (newItem->GetTemplate()->Quality != ITEM_QUALITY_LEGENDARY)
                            {
                                sT->GetAmountTokenRDF_Twink() != 0 ? (ss << std::endl << sT->GetAmountTokenRDF_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                                sT->GetAmountTokenBG_Twink()  != 0 ? (ss << std::endl << sT->GetAmountTokenBG_Twink()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                                sT->GetAmountTokenWG_Twink()  != 0 ? (ss << std::endl << sT->GetAmountTokenWG_Twink()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                                sT->GetAmountToken2V2_Twink() != 0 ? (ss << std::endl << sT->GetAmountToken2V2_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                                sT->GetAmountToken3V3_Twink() != 0 ? (ss << std::endl << sT->GetAmountToken3V3_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                                sT->GetAmountTokenORB_Twink() != 0 ? (ss << std::endl << sT->GetAmountTokenORB_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                                sT->GetAmountTokenGEM_Twink() != 0 ? (ss << std::endl << sT->GetAmountTokenGEM_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                                sT->GetMoneyAmount_Twink()    != 0 ? (ss << std::endl << (sT->GetMoneyAmount_Twink() / GOLD) << " gold. ") : ss << "";
                            }
                            else
                            {
                                sT->GetLegendaryAmountTokenRDF_Twink() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenRDF_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntryRDF(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenBG_Twink()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenBG_Twink()  << " x " << sT->GetItemLink(sT->GetTokenEntryBG(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenWG_Twink()  != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenWG_Twink()  << " x " << sT->GetItemLink(sT->GetTokenEntryWG(), session)) : ss << "";
                                sT->GetLegendaryAmountToken2V2_Twink() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken2V2_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntry2V2(), session)) : ss << "";
                                sT->GetLegendaryAmountToken3V3_Twink() != 0 ? (ss << std::endl << sT->GetLegendaryAmountToken3V3_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntry3V3(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenORB_Twink() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenORB_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra1(), session)) : ss << "";
                                sT->GetLegendaryAmountTokenGEM_Twink() != 0 ? (ss << std::endl << sT->GetLegendaryAmountTokenGEM_Twink() << " x " << sT->GetItemLink(sT->GetTokenEntryExtra2(), session)) : ss << "";
                                sT->GetLegendaryMoneyAmount_Twink()    != 0 ? (ss << std::endl << (sT->GetLegendaryMoneyAmount_Twink() / GOLD) << " gold. ") : ss << "";
                            }
                        }
                    }
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, sT->GetItemIcon(newItem->GetEntry(), 30, 30, -18, 0) + sT->GetItemLink(newItem, session), slot, newItem->GetGUIDLow(), "Using this item for transmogrify will bind it to you and make it non-refundable and non-tradeable.\nDo you wish to continue?\n\n" + sT->GetItemIcon(newItem->GetEntry(), 40, 40, -15, -10) + sT->GetItemLink(newItem, session) + ss.str(), 0, false);
                }
            }
        }

        std::ostringstream ss;
        ss << (sT->GetRemoveCost() / GOLD) << " gold." << std::endl;

        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Enchant_Disenchant:30:30:-18:0|tRemove transmogrification", EQUIPMENT_SLOT_END + 3, slot, "Remove transmogrification from the slot?\n\nAre you sure you want to reset transmog?\nIt will cost you: " + ss.str(), 0, false);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-18:0|tUpdate menu", EQUIPMENT_SLOT_END, slot);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:30:30:-18:0|tBack.", EQUIPMENT_SLOT_END + 1, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
    }
};

class PS_Transmogrification : public PlayerScript
{
public:
    PS_Transmogrification() : PlayerScript("Player_Transmogrify") { }

    void OnAfterSetVisibleItemSlot(Player* player, uint8 slot, Item *item) {
        if (!item)
            return;

        if (uint32 entry = sT->GetFakeEntry(item->GetGUID()))
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (slot * 2), entry);
    }

    void OnAfterMoveItemFromInventory(Player* player, Item* it, uint8 bag, uint8 slot, bool update) {
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
                if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
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
        
        void OnMirrorImageDisplayItem(const Item *item, uint32 &display) {
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

