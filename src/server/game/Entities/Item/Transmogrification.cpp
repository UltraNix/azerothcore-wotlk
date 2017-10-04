#include "Transmogrification.h"

#ifdef PRESETS
void Transmogrification::PresetTransmog(Player* player, Item* itemTransmogrified, uint32 fakeEntry, uint8 slot)
{
    sLog->outDebug(LOG_FILTER_MODULES, "Transmogrification::PresetTransmog");

    if (!EnableSets)
        return;
    if (!player || !itemTransmogrified)
        return;
    if (slot >= EQUIPMENT_SLOT_END)
        return;
    if (!CanTransmogrifyItemWithItem(player, itemTransmogrified->GetTemplate(), sObjectMgr->GetItemTemplate(fakeEntry)))
        return;

    // [AZTH] Custom
    if (GetFakeEntry(itemTransmogrified->GetGUID()))
        DeleteFakeEntry(player, slot, itemTransmogrified);

    SetFakeEntry(player, fakeEntry, slot, itemTransmogrified); // newEntry


    itemTransmogrified->UpdatePlayedTime(player);

    itemTransmogrified->SetOwnerGUID(player->GetGUID());
    itemTransmogrified->SetNotRefundable(player);
    itemTransmogrified->ClearSoulboundTradeable(player);
}

void Transmogrification::LoadPlayerSets(uint64 pGUID)
{
    sLog->outDebug(LOG_FILTER_MODULES, "Transmogrification::LoadPlayerSets");

    for (presetData::iterator it = presetById[pGUID].begin(); it != presetById[pGUID].end(); ++it)
        it->second.clear();

    presetById[pGUID].clear();

    presetByName[pGUID].clear();

    QueryResult result = CharacterDatabase.PQuery("SELECT `PresetID`, `SetName`, `SetData` FROM `custom_transmogrification_sets` WHERE Owner = %u", GUID_LOPART(pGUID));
    if (result)
    {
        do
        {
            uint8 PresetID = (*result)[0].GetUInt8();
            std::string SetName = (*result)[1].GetString();
            std::istringstream SetData((*result)[2].GetString());
            while (SetData.good())
            {
                uint32 slot;
                uint32 entry;
                SetData >> slot >> entry;
                if (SetData.fail())
                    break;
                if (slot >= EQUIPMENT_SLOT_END)
                {
                    sLog->outError("Item entry (FakeEntry: %u, playerGUID: %u, slot: %u, presetId: %u) has invalid slot, ignoring.", entry, GUID_LOPART(pGUID), slot, uint32(PresetID));
                    continue;
                }
                if (sObjectMgr->GetItemTemplate(entry))
                    presetById[pGUID][PresetID][slot] = entry; // Transmogrification::Preset(presetName, fakeEntry);
                                                               //else
                                                               //sLog->outError(LOG_FILTER_SQL, "Item entry (FakeEntry: %u, playerGUID: %u, slot: %u, presetId: %u) does not exist, ignoring.", entry, GUID_LOPART(pGUID), uint32(slot), uint32(PresetID));
            }

            if (!presetById[pGUID][PresetID].empty())
            {
                presetByName[pGUID][PresetID] = SetName;
                // load all presets anyways
                //if (presetByName[pGUID].size() >= GetMaxSets())
                //    break;
            }
            else // should be deleted on startup, so  this never runs (shouldnt..)
            {
                presetById[pGUID].erase(PresetID);
                CharacterDatabase.PExecute("DELETE FROM `custom_transmogrification_sets` WHERE Owner = %u AND PresetID = %u", GUID_LOPART(pGUID), PresetID);
            }
        } while (result->NextRow());
    }
}

bool Transmogrification::GetEnableSets() const
{
    return EnableSets;
}
uint8 Transmogrification::GetMaxSets() const
{
    return MaxSets;
}
float Transmogrification::GetSetCostModifier() const
{
    return SetCostModifier;
}
int32 Transmogrification::GetSetCopperCost() const
{
    return SetCopperCost;
}

void Transmogrification::UnloadPlayerSets(uint64 pGUID)
{
    for (presetData::iterator it = presetById[pGUID].begin(); it != presetById[pGUID].end(); ++it)
        it->second.clear();
    presetById[pGUID].clear();

    presetByName[pGUID].clear();
}
#endif

const char* Transmogrification::GetSlotName(uint8 slot, WorldSession* /*session*/) const
{
    sLog->outDebug(LOG_FILTER_MODULES, "Transmogrification::GetSlotName");

    switch (slot)
    {
        case EQUIPMENT_SLOT_HEAD: return  "Head";// session->GetTrinityString(LANG_SLOT_NAME_HEAD);
        case EQUIPMENT_SLOT_SHOULDERS: return  "Shoulders";// session->GetTrinityString(LANG_SLOT_NAME_SHOULDERS);
        case EQUIPMENT_SLOT_BODY: return  "Shirt";// session->GetTrinityString(LANG_SLOT_NAME_BODY);
        case EQUIPMENT_SLOT_CHEST: return  "Chest";// session->GetTrinityString(LANG_SLOT_NAME_CHEST);
        case EQUIPMENT_SLOT_WAIST: return  "Waist";// session->GetTrinityString(LANG_SLOT_NAME_WAIST);
        case EQUIPMENT_SLOT_LEGS: return  "Legs";// session->GetTrinityString(LANG_SLOT_NAME_LEGS);
        case EQUIPMENT_SLOT_FEET: return  "Feet";// session->GetTrinityString(LANG_SLOT_NAME_FEET);
        case EQUIPMENT_SLOT_WRISTS: return  "Wrists";// session->GetTrinityString(LANG_SLOT_NAME_WRISTS);
        case EQUIPMENT_SLOT_HANDS: return  "Hands";// session->GetTrinityString(LANG_SLOT_NAME_HANDS);
        case EQUIPMENT_SLOT_BACK: return  "Back";// session->GetTrinityString(LANG_SLOT_NAME_BACK);
        case EQUIPMENT_SLOT_MAINHAND: return  "Main hand";// session->GetTrinityString(LANG_SLOT_NAME_MAINHAND);
        case EQUIPMENT_SLOT_OFFHAND: return  "Off hand";// session->GetTrinityString(LANG_SLOT_NAME_OFFHAND);
        case EQUIPMENT_SLOT_RANGED: return  "Ranged";// session->GetTrinityString(LANG_SLOT_NAME_RANGED);
        case EQUIPMENT_SLOT_TABARD: return  "Tabard";// session->GetTrinityString(LANG_SLOT_NAME_TABARD);
        default: return NULL;
    }
}

std::string Transmogrification::GetItemIcon(uint32 entry, uint32 width, uint32 height, int x, int y) const
{
    sLog->outDebug(LOG_FILTER_MODULES, "Transmogrification::GetItemIcon");

    std::ostringstream ss;
    ss << "|TInterface";
    const ItemTemplate* temp = sObjectMgr->GetItemTemplate(entry);
    const ItemDisplayInfoEntry* dispInfo = NULL;
    if (temp)
    {
        dispInfo = sItemDisplayInfoStore.LookupEntry(temp->DisplayInfoID);
        if (dispInfo)
            ss << "/ICONS/" << dispInfo->inventoryIcon;
    }
    if (!dispInfo)
        ss << "/InventoryItems/WoWUnknownItem01";
    ss << ":" << width << ":" << height << ":" << x << ":" << y << "|t";
    return ss.str();
}

std::string Transmogrification::GetSlotIcon(uint8 slot, uint32 width, uint32 height, int x, int y) const
{
    sLog->outDebug(LOG_FILTER_MODULES, "Transmogrification::GetSlotIcon");

    std::ostringstream ss;
    ss << "|TInterface/PaperDoll/";
    switch (slot)
    {
        case EQUIPMENT_SLOT_HEAD: ss << "UI-PaperDoll-Slot-Head"; break;
        case EQUIPMENT_SLOT_SHOULDERS: ss << "UI-PaperDoll-Slot-Shoulder"; break;
        case EQUIPMENT_SLOT_BODY: ss << "UI-PaperDoll-Slot-Shirt"; break;
        case EQUIPMENT_SLOT_CHEST: ss << "UI-PaperDoll-Slot-Chest"; break;
        case EQUIPMENT_SLOT_WAIST: ss << "UI-PaperDoll-Slot-Waist"; break;
        case EQUIPMENT_SLOT_LEGS: ss << "UI-PaperDoll-Slot-Legs"; break;
        case EQUIPMENT_SLOT_FEET: ss << "UI-PaperDoll-Slot-Feet"; break;
        case EQUIPMENT_SLOT_WRISTS: ss << "UI-PaperDoll-Slot-Wrists"; break;
        case EQUIPMENT_SLOT_HANDS: ss << "UI-PaperDoll-Slot-Hands"; break;
        case EQUIPMENT_SLOT_BACK: ss << "UI-PaperDoll-Slot-Chest"; break;
        case EQUIPMENT_SLOT_MAINHAND: ss << "UI-PaperDoll-Slot-MainHand"; break;
        case EQUIPMENT_SLOT_OFFHAND: ss << "UI-PaperDoll-Slot-SecondaryHand"; break;
        case EQUIPMENT_SLOT_RANGED: ss << "UI-PaperDoll-Slot-Ranged"; break;
        case EQUIPMENT_SLOT_TABARD: ss << "UI-PaperDoll-Slot-Tabard"; break;
        default: ss << "UI-Backpack-EmptySlot";
    }
    ss << ":" << width << ":" << height << ":" << x << ":" << y << "|t";
    return ss.str();
}

std::string Transmogrification::GetItemLink(Item* item, WorldSession* session) const
{
    sLog->outDebug(LOG_FILTER_MODULES, "Transmogrification::GetItemLink");

    int loc_idx = session->GetSessionDbLocaleIndex();
    const ItemTemplate* temp = item->GetTemplate();
    std::string name = temp->Name1;
//    if (ItemLocale const* il = sObjectMgr->GetItemLocale(temp->ItemId))
//        ObjectMgr::GetLocaleString(il->Name, loc_idx, name);

    if (int32 itemRandPropId = item->GetItemRandomPropertyId())
    {
        char* const* suffix = NULL;
        if (itemRandPropId < 0)
        {
            const ItemRandomSuffixEntry* itemRandEntry = sItemRandomSuffixStore.LookupEntry(-item->GetItemRandomPropertyId());
            if (itemRandEntry)
                suffix = itemRandEntry->nameSuffix;
        }
        else
        {
            const ItemRandomPropertiesEntry* itemRandEntry = sItemRandomPropertiesStore.LookupEntry(item->GetItemRandomPropertyId());
            if (itemRandEntry)
                suffix = itemRandEntry->nameSuffix;
        }
        if (suffix)
        {
            std::string test(suffix[(name != temp->Name1) ? loc_idx : DEFAULT_LOCALE]);
            if (!test.empty())
            {
                name += ' ';
                name += test;
            }
        }
    }

    std::ostringstream oss;
    oss << "|c" << std::hex << ItemQualityColors[temp->Quality] << std::dec <<
        "|Hitem:" << temp->ItemId << ":" <<
        item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT) << ":" <<
        item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT) << ":" <<
        item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_2) << ":" <<
        item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_3) << ":" <<
        item->GetEnchantmentId(BONUS_ENCHANTMENT_SLOT) << ":" <<
        item->GetItemRandomPropertyId() << ":" << item->GetItemSuffixFactor() << ":" <<
        (uint32)item->GetOwner()->getLevel() << "|h[" << name << "]|h|r";

    return oss.str();
}

std::string Transmogrification::GetItemLink(uint32 entry, WorldSession* session) const
{
    sLog->outDebug(LOG_FILTER_MODULES, "Transmogrification::GetItemLink");

    const ItemTemplate* temp = sObjectMgr->GetItemTemplate(entry);
    int loc_idx = session->GetSessionDbLocaleIndex();
    std::string name = temp->Name1;
//    if (ItemLocale const* il = sObjectMgr->GetItemLocale(entry))
//        ObjectMgr::GetLocaleString(il->Name, loc_idx, name);

    std::ostringstream oss;
    oss << "|c" << std::hex << ItemQualityColors[temp->Quality] << std::dec <<
        "|Hitem:" << entry << ":0:0:0:0:0:0:0:0:0|h[" << name << "]|h|r";

    return oss.str();
}

uint32 Transmogrification::GetFakeEntry(uint64 itemGUID) const
{
    sLog->outDebug(LOG_FILTER_MODULES, "Transmogrification::GetFakeEntry");

    transmogData::const_iterator itr = dataMap.find(itemGUID);
    if (itr == dataMap.end()) return 0;
    transmogMap::const_iterator itr2 = entryMap.find(itr->second);
    if (itr2 == entryMap.end()) return 0;
    transmogData::const_iterator itr3 = itr2->second.find(itemGUID);
    if (itr3 == itr2->second.end()) return 0;
    return itr3->second;
}

void Transmogrification::UpdateItem(Player* player, Item* item) const
{
    sLog->outDebug(LOG_FILTER_MODULES, "Transmogrification::UpdateItem");

    if (item->IsEquipped())
    {
        player->SetVisibleItemSlot(item->GetSlot(), item);
        if (player->IsInWorld())
            item->SendUpdateToPlayer(player);
    }
}

void Transmogrification::DeleteFakeEntry(Player* player, uint8 slot, Item* itemTransmogrified, SQLTransaction* trans)
{
    //if (!GetFakeEntry(item))
    //    return false;
    DeleteFakeFromDB(itemTransmogrified->GetGUID(), trans);
    UpdateItem(player, itemTransmogrified);
}

void Transmogrification::SetFakeEntry(Player* player, uint32 newEntry, uint8 slot, Item* itemTransmogrified)
{
    uint64 itemGUID = itemTransmogrified->GetGUID();
    entryMap[player->GetGUID()][itemGUID] = newEntry;
    dataMap[itemGUID] = player->GetGUID();
    CharacterDatabase.PExecute("REPLACE INTO custom_transmogrification (GUID, FakeEntry, Owner) VALUES (%u, %u, %u)", GUID_LOPART(itemGUID), newEntry, player->GetGUIDLow());
    UpdateItem(player, itemTransmogrified);
}

TransmogTrinityStrings Transmogrification::Transmogrify(Player* player, uint64 itemGUID, uint8 slot, /*uint32 newEntry, */bool no_cost)
{
    int32 cost = 0;
    // slot of the transmogrified item
    if (slot >= EQUIPMENT_SLOT_END)
    {
        // TC_LOG_DEBUG(LOG_FILTER_NETWORKIO, "WORLD: HandleTransmogrifyItems - Player (GUID: %u, name: %s) tried to transmogrify an item (lowguid: %u) with a wrong slot (%u) when transmogrifying items.", player->GetGUIDLow(), player->GetName().c_str(), GUID_LOPART(itemGUID), slot);
        return LANG_ERR_TRANSMOG_INVALID_SLOT;
    }

    Item* itemTransmogrifier = NULL;
    // guid of the transmogrifier item, if it's not 0
    if (itemGUID)
    {
        itemTransmogrifier = player->GetItemByGuid(itemGUID);
        if (!itemTransmogrifier)
        {
            //TC_LOG_DEBUG(LOG_FILTER_NETWORKIO, "WORLD: HandleTransmogrifyItems - Player (GUID: %u, name: %s) tried to transmogrify with an invalid item (lowguid: %u).", player->GetGUIDLow(), player->GetName().c_str(), GUID_LOPART(itemGUID));
            return LANG_ERR_TRANSMOG_MISSING_SRC_ITEM;
        }
    }

    // transmogrified item
    Item* itemTransmogrified = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
    if (!itemTransmogrified)
    {
        //TC_LOG_DEBUG(LOG_FILTER_NETWORKIO, "WORLD: HandleTransmogrifyItems - Player (GUID: %u, name: %s) tried to transmogrify an invalid item in a valid slot (slot: %u).", player->GetGUIDLow(), player->GetName().c_str(), slot);
        return LANG_ERR_TRANSMOG_MISSING_DEST_ITEM;
    }

    if (!itemTransmogrifier) // reset look newEntry
    {
        // Custom
        DeleteFakeEntry(player, slot, itemTransmogrified);
    }
    else
    {
        if (!CanTransmogrifyItemWithItem(player, itemTransmogrified->GetTemplate(), itemTransmogrifier->GetTemplate()))
        {
            //TC_LOG_DEBUG(LOG_FILTER_NETWORKIO, "WORLD: HandleTransmogrifyItems - Player (GUID: %u, name: %s) failed CanTransmogrifyItemWithItem (%u with %u).", player->GetGUIDLow(), player->GetName().c_str(), itemTransmogrified->GetEntry(), itemTransmogrifier->GetEntry());
            return LANG_ERR_TRANSMOG_INVALID_ITEMS;
        }

        if (CustomModelCost)
        {
            if (player->hasTransmogModelPvE())
            {
                if (EffortModel(player, MODEL_PVE, itemTransmogrified->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false))
                    ChargeModelCost(player, MODEL_PVE, itemTransmogrified->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false);
                else
                    return LANG_ERR_TRANSMOG_NOT_ENOUGH_TOKENS;
            }
            else if (player->hasTransmogModelPvP())
            {
                if (EffortModel(player, MODEL_PVP, itemTransmogrified->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false))
                    ChargeModelCost(player, MODEL_PVP, itemTransmogrified->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false);
                else
                    return LANG_ERR_TRANSMOG_NOT_ENOUGH_TOKENS;
            }
            else if (player->hasTransmogModelMIX())
            {
                if (EffortModel(player, MODEL_MIX, itemTransmogrified->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false))
                    ChargeModelCost(player, MODEL_MIX, itemTransmogrified->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false);
                else
                    return LANG_ERR_TRANSMOG_NOT_ENOUGH_TOKENS;
            }
            else if (player->hasTransmogModelTWK())
            {
                if (EffortModel(player, MODEL_TWK, itemTransmogrified->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false))
                    ChargeModelCost(player, MODEL_TWK, itemTransmogrified->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false);
                else
                    return LANG_ERR_TRANSMOG_NOT_ENOUGH_TOKENS;
            }
        }
        else if (!no_cost && !CustomModelCost)
        {
            if (RequireToken)
            {
                if (player->HasItemCount(TokenEntry, TokenAmount))
                    player->DestroyItemCount(TokenEntry, TokenAmount, true);
                else
                    return LANG_ERR_TRANSMOG_NOT_ENOUGH_TOKENS;
            }

            cost = GetSpecialPrice(itemTransmogrified->GetTemplate());
            cost *= ScaledCostModifier;
            cost += CopperCost;

            if (cost) // 0 cost if reverting look
            {
                if (cost < 0)
                    sLog->outDebug(LOG_FILTER_MODULES,  "Transmogrification::Transmogrify - %s (%u) transmogrification invalid cost (non negative, amount %i). Transmogrified %u with %u", player->GetName().c_str(), player->GetGUIDLow(), -cost, itemTransmogrified->GetEntry(), itemTransmogrifier->GetEntry());
                else
                {
                    if (!player->HasEnoughMoney(cost))
                        return LANG_ERR_TRANSMOG_NOT_ENOUGH_MONEY;
                    player->ModifyMoney(-cost, false);
                }
            }
        }

        // Custom
        SetFakeEntry(player, itemTransmogrifier->GetEntry(), slot, itemTransmogrified); // newEntry

        itemTransmogrified->UpdatePlayedTime(player);

        itemTransmogrified->SetOwnerGUID(player->GetGUID());
        itemTransmogrified->SetNotRefundable(player);
        itemTransmogrified->ClearSoulboundTradeable(player);

        if (itemTransmogrifier->GetTemplate()->Bonding == BIND_WHEN_EQUIPED || itemTransmogrifier->GetTemplate()->Bonding == BIND_WHEN_USE)
            itemTransmogrifier->SetBinding(true);

        itemTransmogrifier->SetOwnerGUID(player->GetGUID());
        itemTransmogrifier->SetNotRefundable(player);
        itemTransmogrifier->ClearSoulboundTradeable(player);
    }

    // trusting the client, if it got here it has to have enough money
    // ... unless client was modified
    if (cost) // 0 cost if reverting look
        player->ModifyMoney(-1 * cost, false);

    return LANG_ERR_TRANSMOG_OK;
}

bool Transmogrification::CanTransmogrifyItemWithItem(Player* player, ItemTemplate const* target, ItemTemplate const* source) const
{

    if (!target || !source)
        return false;

    if (source->ItemId == target->ItemId)
        return false;

    if (source->DisplayInfoID == target->DisplayInfoID)
        return false;

    if (source->Class != target->Class)
        return false;

    if (source->InventoryType == INVTYPE_BAG ||
        source->InventoryType == INVTYPE_RELIC ||
        // source->InventoryType == INVTYPE_BODY ||
        source->InventoryType == INVTYPE_FINGER ||
        source->InventoryType == INVTYPE_TRINKET ||
        source->InventoryType == INVTYPE_AMMO ||
        source->InventoryType == INVTYPE_QUIVER)
        return false;

    if (target->InventoryType == INVTYPE_BAG ||
        target->InventoryType == INVTYPE_RELIC ||
        // target->InventoryType == INVTYPE_BODY ||
        target->InventoryType == INVTYPE_FINGER ||
        target->InventoryType == INVTYPE_TRINKET ||
        target->InventoryType == INVTYPE_AMMO ||
        target->InventoryType == INVTYPE_QUIVER)
        return false;

    if (!SuitableForTransmogrification(player, target) || !SuitableForTransmogrification(player, source)) // if (!transmogrified->CanTransmogrify() || !transmogrifier->CanBeTransmogrified())
        return false;

    if (IsRangedWeapon(source->Class, source->SubClass) != IsRangedWeapon(target->Class, target->SubClass))
        return false;

    if (source->SubClass != target->SubClass && !IsRangedWeapon(target->Class, target->SubClass))
    {
        if (source->Class == ITEM_CLASS_ARMOR && !AllowMixedArmorTypes)
            return false;
        if (source->Class == ITEM_CLASS_WEAPON && !AllowMixedWeaponTypes)
            return false;
    }

    if (source->InventoryType != target->InventoryType)
    {
        if (source->Class == ITEM_CLASS_WEAPON && !(IsRangedWeapon(target->Class, target->SubClass) ||
            (
                // [AZTH] Yehonal: fixed weapon check
                (target->InventoryType == INVTYPE_WEAPON || target->InventoryType == INVTYPE_2HWEAPON || target->InventoryType == INVTYPE_WEAPONMAINHAND || target->InventoryType == INVTYPE_WEAPONOFFHAND)
                && (source->InventoryType == INVTYPE_WEAPON || source->InventoryType == INVTYPE_2HWEAPON || source->InventoryType == INVTYPE_WEAPONMAINHAND || source->InventoryType == INVTYPE_WEAPONOFFHAND)
            )
        ))
            return false;
        if (source->Class == ITEM_CLASS_ARMOR &&
            !((source->InventoryType == INVTYPE_CHEST || source->InventoryType == INVTYPE_ROBE) &&
                (target->InventoryType == INVTYPE_CHEST || target->InventoryType == INVTYPE_ROBE)))
            return false;
    }

    return true;
}

bool Transmogrification::SuitableForTransmogrification(Player* player, ItemTemplate const* proto) const
{
    // ItemTemplate const* proto = item->GetTemplate();
    if (!player || !proto)
        return false;

    if (proto->Class != ITEM_CLASS_ARMOR &&
        proto->Class != ITEM_CLASS_WEAPON)
        return false;

    // Skip all checks for allowed items
    if (IsAllowed(proto->ItemId))
        return true;

    if (IsNotAllowed(proto->ItemId))
        return false;

    if (!AllowFishingPoles && proto->Class == ITEM_CLASS_WEAPON && proto->SubClass == ITEM_SUBCLASS_WEAPON_FISHING_POLE)
        return false;

    if (!IsAllowedQuality(proto->Quality)) // (proto->Quality == ITEM_QUALITY_LEGENDARY)
        return false;

    if ((proto->Flags2 & ITEM_FLAGS_EXTRA_HORDE_ONLY) && player->GetTeamId() != TEAM_HORDE)
        return false;

    if ((proto->Flags2 & ITEM_FLAGS_EXTRA_ALLIANCE_ONLY) && player->GetTeamId() != TEAM_ALLIANCE)
        return false;

    if (!IgnoreReqClass && (proto->AllowableClass & player->getClassMask()) == 0)
        return false;

    if (!IgnoreReqRace && (proto->AllowableRace & player->getRaceMask()) == 0)
        return false;

    if (!IgnoreReqSkill && proto->RequiredSkill != 0)
    {
        if (player->GetSkillValue(proto->RequiredSkill) == 0)
            return false;
        else if (player->GetSkillValue(proto->RequiredSkill) < proto->RequiredSkillRank)
            return false;
    }

    if (!IgnoreReqSpell && proto->RequiredSpell != 0 && !player->HasSpell(proto->RequiredSpell))
        return false;

    if (!IgnoreReqLevel && player->getLevel() < proto->RequiredLevel)
        return false;

    // If World Event is not active, prevent using event dependant items
    if (!IgnoreReqEvent && proto->HolidayId && !IsHolidayActive((HolidayIds)proto->HolidayId))
        return false;

    if (!IgnoreReqStats)
    {
        if (!proto->RandomProperty && !proto->RandomSuffix
                /*[AZTH] Yehonal: we should transmorg also items without stats*/
                && proto->StatsCount > 0)
        {
            bool found = false;
            for (uint8 i = 0; i < proto->StatsCount; ++i)
            {
                if (proto->ItemStat[i].ItemStatValue != 0)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
                return false;
        }
    }

    return true;
}

uint32 Transmogrification::GetSpecialPrice(ItemTemplate const* proto) const
{
    uint32 cost = proto->SellPrice < 10000 ? 10000 : proto->SellPrice;
    return cost;
}
bool Transmogrification::IsRangedWeapon(uint32 Class, uint32 SubClass) const
{
    return Class == ITEM_CLASS_WEAPON && (
        SubClass == ITEM_SUBCLASS_WEAPON_BOW ||
        SubClass == ITEM_SUBCLASS_WEAPON_GUN ||
        SubClass == ITEM_SUBCLASS_WEAPON_CROSSBOW);
}

bool Transmogrification::IsAllowed(uint32 entry) const
{
    return Allowed.find(entry) != Allowed.end();
}

bool Transmogrification::IsNotAllowed(uint32 entry) const
{
    return NotAllowed.find(entry) != NotAllowed.end();
}

bool Transmogrification::IsAllowedQuality(uint32 quality) const
{
    switch (quality)
    {
        case ITEM_QUALITY_POOR: return AllowPoor;
        case ITEM_QUALITY_NORMAL: return AllowCommon;
        case ITEM_QUALITY_UNCOMMON: return AllowUncommon;
        case ITEM_QUALITY_RARE: return AllowRare;
        case ITEM_QUALITY_EPIC: return AllowEpic;
        case ITEM_QUALITY_LEGENDARY: return AllowLegendary;
        case ITEM_QUALITY_ARTIFACT: return AllowArtifact;
        case ITEM_QUALITY_HEIRLOOM: return AllowHeirloom;
        default: return false;
    }
}

void Transmogrification::LoadConfig(bool reload)
{
#ifdef PRESETS
    EnableSetInfo = sConfigMgr->GetBoolDefault("Transmogrification.EnableSetInfo", true);
    SetNpcText = uint32(sConfigMgr->GetIntDefault("Transmogrification.SetNpcText", 50001));

    EnableSets = sConfigMgr->GetBoolDefault("Transmogrification.EnableSets", true);
    MaxSets = (uint8)sConfigMgr->GetIntDefault("Transmogrification.MaxSets", 10);
    SetCostModifier = sConfigMgr->GetFloatDefault("Transmogrification.SetCostModifier", 3.0f);
    SetCopperCost = sConfigMgr->GetIntDefault("Transmogrification.SetCopperCost", 0);

    if (MaxSets > MAX_OPTIONS)
        MaxSets = MAX_OPTIONS;

    if (reload) // dont store presets for nothing
    {
        SessionMap const& sessions = sWorld->GetAllSessions();
        for (SessionMap::const_iterator it = sessions.begin(); it != sessions.end(); ++it)
        {
            if (Player* player = it->second->GetPlayer())
            {
                // skipping session check
                UnloadPlayerSets(player->GetGUID());
                if (GetEnableSets())
                    LoadPlayerSets(player->GetGUID());
            }
        }
    }
#endif

    EnableTransmogInfo = sConfigMgr->GetBoolDefault("Transmogrification.EnableTransmogInfo", true);
    TransmogNpcText = uint32(sConfigMgr->GetIntDefault("Transmogrification.TransmogNpcText", 50000));
    TransmogModelText = uint32(sConfigMgr->GetIntDefault("Transmogrification.TransmogModelText", 60000));

    std::istringstream issAllowed(sConfigMgr->GetStringDefault("Transmogrification.Allowed", ""));
    std::istringstream issNotAllowed(sConfigMgr->GetStringDefault("Transmogrification.NotAllowed", ""));
    while (issAllowed.good())
    {
        uint32 entry;
        issAllowed >> entry;
        if (issAllowed.fail())
            break;
        Allowed.insert(entry);
    }
    while (issNotAllowed.good())
    {
        uint32 entry;
        issNotAllowed >> entry;
        if (issNotAllowed.fail())
            break;
        NotAllowed.insert(entry);
    }

    ScaledCostModifier = sConfigMgr->GetFloatDefault("Transmogrification.ScaledCostModifier", 1.0f);
    CopperCost = sConfigMgr->GetIntDefault("Transmogrification.CopperCost", 0);

    RequireToken = sConfigMgr->GetBoolDefault("Transmogrification.RequireToken", false);
    TokenEntry = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenEntry", 49426));
    TokenAmount = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenAmount", 1));

    AllowPoor = sConfigMgr->GetBoolDefault("Transmogrification.AllowPoor", false);
    AllowCommon = sConfigMgr->GetBoolDefault("Transmogrification.AllowCommon", false);
    AllowUncommon = sConfigMgr->GetBoolDefault("Transmogrification.AllowUncommon", true);
    AllowRare = sConfigMgr->GetBoolDefault("Transmogrification.AllowRare", true);
    AllowEpic = sConfigMgr->GetBoolDefault("Transmogrification.AllowEpic", true);
    AllowLegendary = sConfigMgr->GetBoolDefault("Transmogrification.AllowLegendary", false);
    AllowArtifact = sConfigMgr->GetBoolDefault("Transmogrification.AllowArtifact", false);
    AllowHeirloom = sConfigMgr->GetBoolDefault("Transmogrification.AllowHeirloom", true);

    AllowMixedArmorTypes = sConfigMgr->GetBoolDefault("Transmogrification.AllowMixedArmorTypes", false);
    AllowMixedWeaponTypes = sConfigMgr->GetBoolDefault("Transmogrification.AllowMixedWeaponTypes", false);
    AllowFishingPoles = sConfigMgr->GetBoolDefault("Transmogrification.AllowFishingPoles", false);

    IgnoreReqRace = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqRace", false);
    IgnoreReqClass = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqClass", false);
    IgnoreReqSkill = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqSkill", false);
    IgnoreReqSpell = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqSpell", false);
    IgnoreReqLevel = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqLevel", false);
    IgnoreReqEvent = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqEvent", false);
    IgnoreReqStats = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqStats", false);

    CustomModelCost = sConfigMgr->GetBoolDefault("Transmogrification.CustmModelCost", false);

    // Model PvE
    pve_token_rdf = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.PvE.Count", 1));
    pve_token_bg = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.PvE.Count", 1));
    pve_token_wg  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.PvE.Count", 1));
    pve_token_2v2 = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.PvE.Count", 1));
    pve_token_3v3 = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.PvE.Count", 1));
    pve_token_orb = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.PvE.Count", 1));
    pve_token_gem = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.PvE.Count", 1));
    pve_money_amount = uint32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.PvE", 1));

    // Legendary PvE
    pve_token_rdf_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.PvE.Legendary.Count", 1));
    pve_token_bg_legendary  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.PvE.Count", 1));
    pve_token_wg_legendary  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.PvE.Legendary.Count", 1));
    pve_token_2v2_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.PvE.Legendary.Count", 1));
    pve_token_3v3_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.PvE.Legendary.Count", 1));
    pve_token_orb_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.PvE.Legendary.Count", 1));
    pve_token_gem_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.PvE.Legendary.Count", 1));
    pve_money_amount_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.Legendary.PvE", 1));

    // Model PvP
    pvp_token_rdf = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.PvP.Count", 1));
    pvp_token_bg = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.PvP.Count", 1));
    pvp_token_wg  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.PvP.Count", 1));
    pvp_token_2v2 = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.PvP.Count", 1));
    pvp_token_3v3 = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.PvP.Count", 1));
    pvp_token_orb = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.PvP.Count", 1));
    pvp_token_gem = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.PvP.Count", 1));

    // Legendary PvP
    pvp_token_rdf_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.PvP.Legendary.Count", 1));
    pvp_token_bg_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.PvP.Legendary.Count", 1));
    pvp_token_wg_legendary  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.PvP.Legendary.Count", 1));
    pvp_token_2v2_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.PvP.Legendary.Count", 1));
    pvp_token_3v3_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.PvP.Legendary.Count", 1));
    pvp_token_orb_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.PvP.Legendary.Count", 1));
    pvp_token_gem_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.PvP.Legendary.Count", 1));
    pvp_money_amount_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.Legendary.PvP", 1));

    // Model Mix
    mix_token_rdf = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.Mix.Count", 1));
    mix_token_bg  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.Mix.Count", 1));
    mix_token_wg  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.Mix.Count", 1));
    mix_token_2v2 = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.Mix.Count", 1));
    mix_token_3v3 = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.Mix.Count", 1));
    mix_token_orb = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.Mix.Count", 1));
    mix_token_gem = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.Mix.Count", 1));
    // Legendary Mix
    mix_token_rdf_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.Mix.Legendary.Count", 1));
    mix_token_bg_legendary  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.Mix.Legendary.Count", 1));
    mix_token_wg_legendary  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.Mix.Legendary.Count", 1));
    mix_token_2v2_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.Mix.Legendary.Count", 1));
    mix_token_3v3_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.Mix.Legendary.Count", 1));
    mix_token_orb_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.Mix.Legendary.Count", 1));
    mix_token_gem_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.Mix.Legendary.Count", 1));
    mix_money_amount_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.Legendary.Mix", 1));

    // Model Twink
    twink_token_rdf = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.Twink.Count", 1));
    twink_token_bg  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.Twink.Count", 1));
    twink_token_wg  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.Twink.Count", 1));
    twink_token_2v2 = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.Twink.Count", 1));
    twink_token_3v3 = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.Twink.Count", 1));
    twink_token_orb = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.Twink.Count", 1));
    twink_token_gem = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.Twink.Count", 1));

    // Legendary Twink
    twink_token_rdf_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.Twink.Legendary.Count", 1));
    twink_token_bg_legendary  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.Twink.Legendary.Count", 1));
    twink_token_wg_legendary  = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.Twink.Legendary.Count", 1));
    twink_token_2v2_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.Twink.Legendary.Count", 1));
    twink_token_3v3_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.Twink.Legendary.Count", 1));
    twink_token_orb_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.Twink.Legendary.Count", 1));
    twink_token_gem_legendary = uint8(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.Twink.Legendary.Count", 1));
    twink_money_amount_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.Legendary.Twink", 1));

    if (!sObjectMgr->GetItemTemplate(TokenEntry))
    {
        //sLog->outError(LOG_FILTER_SERVER_LOADING, "Transmogrification.TokenEntry (%u) does not exist. Using default.", TokenEntry);
        TokenEntry = 49426;
    }
}

void Transmogrification::DeleteFakeFromDB(uint64 itemGUID, SQLTransaction* trans)
{
    if (dataMap.find(itemGUID) != dataMap.end())
    {
        if (entryMap.find(dataMap[itemGUID]) != entryMap.end())
            entryMap[dataMap[itemGUID]].erase(itemGUID);
        dataMap.erase(itemGUID);
    }
    if (trans)
        (*trans)->PAppend("DELETE FROM custom_transmogrification WHERE GUID = %u", GUID_LOPART(itemGUID));
    else
        CharacterDatabase.PExecute("DELETE FROM custom_transmogrification WHERE GUID = %u", GUID_LOPART(itemGUID));
}

bool Transmogrification::GetEnableTransmogInfo() const
{
    return EnableTransmogInfo;
}
uint32 Transmogrification::GetTransmogNpcText() const
{
    return TransmogNpcText;
}
uint32 Transmogrification::GetTransmogModelText() const
{
    return TransmogModelText;
}

bool Transmogrification::GetEnableSetInfo() const
{
    return EnableSetInfo;
}
uint32 Transmogrification::GetSetNpcText() const
{
    return SetNpcText;
}
float Transmogrification::GetScaledCostModifier() const
{
    return ScaledCostModifier;
}
int32 Transmogrification::GetCopperCost() const
{
    return CopperCost;
}
bool Transmogrification::GetRequireToken() const
{
    return RequireToken;
}
uint32 Transmogrification::GetTokenEntry() const
{
    return TokenEntry;
}
uint32 Transmogrification::GetTokenAmount() const
{
    return TokenAmount;
}
bool Transmogrification::GetCustomModelCost() const
{
    return CustomModelCost;
}

// Model PvE
uint8 Transmogrification::GetAmountTokenRDF_PvE() const
{
    return pve_token_rdf;
}
uint8 Transmogrification::GetAmountTokenBG_PvE() const
{
    return pve_token_bg;
}
uint8 Transmogrification::GetAmountTokenWG_PvE() const
{
    return pve_token_wg;
}
uint8 Transmogrification::GetAmountToken2V2_PvE() const
{
    return pve_token_2v2;
}
uint8 Transmogrification::GetAmountToken3V3_PvE() const
{
    return pve_token_3v3;
}
uint8 Transmogrification::GetAmountTokenORB_PvE() const
{
    return pve_token_orb;
}
uint8 Transmogrification::GetAmountTokenGEM_PvE() const
{
    return pve_token_gem;
}
int32 Transmogrification::GetMoneyAmount_PvE() const
{
    return pve_money_amount;
}

// Legendary PvE
uint8 Transmogrification::GetLegendaryAmountTokenRDF_PvE() const
{
    return pve_token_rdf_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenBG_PvE() const
{
    return pve_token_bg_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenWG_PvE() const
{
    return pve_token_wg_legendary;
}
uint8 Transmogrification::GetLegendaryAmountToken2V2_PvE() const
{
    return pve_token_2v2_legendary;
}
uint8 Transmogrification::GetLegendaryAmountToken3V3_PvE() const
{
    return pve_token_3v3_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenORB_PvE() const
{
    return pve_token_orb_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenGEM_PvE() const
{
    return pve_token_gem_legendary;
}
int32 Transmogrification::GetLegendaryMoneyAmount_PvE() const
{
    return pve_money_amount_legendary;
}

// Model PvP
uint8 Transmogrification::GetAmountTokenRDF_PvP() const
{
    return pvp_token_rdf;
}
uint8 Transmogrification::GetAmountTokenBG_PvP() const
{
    return pvp_token_bg;
}
uint8 Transmogrification::GetAmountTokenWG_PvP() const
{
    return pvp_token_wg;
}
uint8 Transmogrification::GetAmountToken2V2_PvP() const
{
    return pvp_token_2v2;
}
uint8 Transmogrification::GetAmountToken3V3_PvP() const
{
    return pvp_token_3v3;
}
uint8 Transmogrification::GetAmountTokenORB_PvP() const
{
    return pvp_token_orb;
}
uint8 Transmogrification::GetAmountTokenGEM_PvP() const
{
    return pvp_token_gem;
}
int32 Transmogrification::GetMoneyAmount_PvP() const
{
    return pvp_money_amount;
}

// Legendary PvP
uint8 Transmogrification::GetLegendaryAmountTokenRDF_PvP() const
{
    return pvp_token_rdf_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenBG_PvP() const
{
    return pvp_token_bg_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenWG_PvP() const
{
    return pvp_token_wg_legendary;
}
uint8 Transmogrification::GetLegendaryAmountToken2V2_PvP() const
{
    return pvp_token_2v2_legendary;
}
uint8 Transmogrification::GetLegendaryAmountToken3V3_PvP() const
{
    return pvp_token_3v3_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenORB_PvP() const
{
    return pvp_token_orb_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenGEM_PvP() const
{
    return pvp_token_gem_legendary;
}
int32 Transmogrification::GetLegendaryMoneyAmount_PvP() const
{
    return pvp_money_amount_legendary;
}

// Model Mix
uint8 Transmogrification::GetAmountTokenRDF_Mix() const
{
    return mix_token_rdf;
}
uint8 Transmogrification::GetAmountTokenBG_Mix() const
{
    return mix_token_bg;
}
uint8 Transmogrification::GetAmountTokenWG_Mix() const
{
    return mix_token_wg;
}
uint8 Transmogrification::GetAmountToken2V2_Mix() const
{
    return mix_token_2v2;
}
uint8 Transmogrification::GetAmountToken3V3_Mix() const
{
    return mix_token_3v3;
}
uint8 Transmogrification::GetAmountTokenORB_Mix() const
{
    return mix_token_orb;
}
uint8 Transmogrification::GetAmountTokenGEM_Mix() const
{
    return mix_token_gem;
}
int32 Transmogrification::GetMoneyAmount_Mix() const
{
    return mix_money_amount;
}

// Legendary Mix
uint8 Transmogrification::GetLegendaryAmountTokenRDF_Mix() const
{
    return mix_token_rdf_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenBG_Mix() const
{
    return mix_token_bg_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenWG_Mix() const
{
    return mix_token_wg_legendary;
}
uint8 Transmogrification::GetLegendaryAmountToken2V2_Mix() const
{
    return mix_token_2v2_legendary;
}
uint8 Transmogrification::GetLegendaryAmountToken3V3_Mix() const
{
    return mix_token_3v3_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenORB_Mix() const
{
    return mix_token_orb_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenGEM_Mix() const
{
    return mix_token_gem_legendary;
}
int32 Transmogrification::GetLegendaryMoneyAmount_Mix() const
{
    return mix_money_amount_legendary;
}

// Model Twink
uint8 Transmogrification::GetAmountTokenRDF_Twink() const
{
    return twink_token_rdf;
}
uint8 Transmogrification::GetAmountTokenBG_Twink() const
{
    return twink_token_bg;
}
uint8 Transmogrification::GetAmountTokenWG_Twink() const
{
    return twink_token_wg;
}
uint8 Transmogrification::GetAmountToken2V2_Twink() const
{
    return twink_token_2v2;
}
uint8 Transmogrification::GetAmountToken3V3_Twink() const
{
    return twink_token_3v3;
}
uint8 Transmogrification::GetAmountTokenORB_Twink() const
{
    return twink_token_orb;
}
uint8 Transmogrification::GetAmountTokenGEM_Twink() const
{
    return twink_token_gem;
}
int32 Transmogrification::GetMoneyAmount_Twink() const
{
    return twink_money_amount;
}

// Legendary Twink
uint8 Transmogrification::GetLegendaryAmountTokenRDF_Twink() const
{
    return twink_token_rdf_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenBG_Twink() const
{
    return twink_token_bg_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenWG_Twink() const
{
    return twink_token_wg_legendary;
}
uint8 Transmogrification::GetLegendaryAmountToken2V2_Twink() const
{
    return twink_token_2v2_legendary;
}
uint8 Transmogrification::GetLegendaryAmountToken3V3_Twink() const
{
    return twink_token_3v3_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenORB_Twink() const
{
    return twink_token_orb_legendary;
}
uint8 Transmogrification::GetLegendaryAmountTokenGEM_Twink() const
{
    return twink_token_gem_legendary;
}
int32 Transmogrification::GetLegendaryMoneyAmount_Twink() const
{
    return twink_money_amount_legendary;
}

bool Transmogrification::GetAllowMixedArmorTypes() const
{
    return AllowMixedArmorTypes;
};
bool Transmogrification::GetAllowMixedWeaponTypes() const
{
    return AllowMixedWeaponTypes;
};

bool Transmogrification::EffortModel(Player* player, uint8 model, bool Legendary) const
{
    if (!player || !model)
        return false;

    switch (model)
    {
        case MODEL_PVE:
        {

            if (!Legendary)
                return player->HasItemCount(TOKEN_ENTRY_RDF, GetAmountTokenRDF_PvE())
                && player->HasItemCount(TOKEN_ENTRY_BG, GetAmountTokenBG_PvE())
                && player->HasItemCount(TOKEN_ENTRY_WG, GetAmountTokenWG_PvE())
                && player->HasItemCount(TOKEN_ENTRY_2V2, GetAmountToken2V2_PvE())
                && player->HasItemCount(TOKEN_ENTRY_3V3, GetAmountToken3V3_PvE())
                && player->HasItemCount(CRUSADER_ORB_ENTRY, GetAmountTokenORB_PvE())
                && player->HasItemCount(EPIC_GEM_ENTRY, GetAmountTokenGEM_PvE())
                && player->HasEnoughMoney(GetMoneyAmount_PvE());
            else
                return player->HasItemCount(TOKEN_ENTRY_RDF, GetLegendaryAmountTokenRDF_PvE())
                && player->HasItemCount(TOKEN_ENTRY_BG, GetLegendaryAmountTokenBG_PvE())
                && player->HasItemCount(TOKEN_ENTRY_WG, GetLegendaryAmountTokenWG_PvE())
                && player->HasItemCount(TOKEN_ENTRY_2V2, GetLegendaryAmountToken2V2_PvE())
                && player->HasItemCount(TOKEN_ENTRY_3V3, GetLegendaryAmountToken3V3_PvE())
                && player->HasItemCount(CRUSADER_ORB_ENTRY, GetLegendaryAmountTokenORB_PvE())
                && player->HasItemCount(EPIC_GEM_ENTRY, GetLegendaryAmountTokenGEM_PvE())
                && player->HasEnoughMoney(GetLegendaryMoneyAmount_PvE());
        }
        case MODEL_PVP:
        {
            if (!Legendary)
                return player->HasItemCount(TOKEN_ENTRY_RDF, GetAmountTokenRDF_PvP())
                && player->HasItemCount(TOKEN_ENTRY_BG, GetAmountTokenBG_PvP())
                && player->HasItemCount(TOKEN_ENTRY_WG, GetAmountTokenWG_PvP())
                && player->HasItemCount(TOKEN_ENTRY_2V2, GetAmountToken2V2_PvP())
                && player->HasItemCount(TOKEN_ENTRY_3V3, GetAmountToken3V3_PvP())
                && player->HasItemCount(CRUSADER_ORB_ENTRY, GetAmountTokenORB_PvP())
                && player->HasItemCount(EPIC_GEM_ENTRY, GetAmountTokenGEM_PvP())
                && player->HasEnoughMoney(GetMoneyAmount_PvP());
            else
                return player->HasItemCount(TOKEN_ENTRY_RDF, GetLegendaryAmountTokenRDF_PvP())
                && player->HasItemCount(TOKEN_ENTRY_BG, GetLegendaryAmountTokenBG_PvP())
                && player->HasItemCount(TOKEN_ENTRY_WG, GetLegendaryAmountTokenWG_PvP())
                && player->HasItemCount(TOKEN_ENTRY_2V2, GetLegendaryAmountToken2V2_PvP())
                && player->HasItemCount(TOKEN_ENTRY_3V3, GetLegendaryAmountToken3V3_PvP())
                && player->HasItemCount(CRUSADER_ORB_ENTRY, GetLegendaryAmountTokenORB_PvP())
                && player->HasItemCount(EPIC_GEM_ENTRY, GetLegendaryAmountTokenGEM_PvP())
                && player->HasEnoughMoney(GetLegendaryMoneyAmount_PvP());
        }
        case MODEL_MIX:
        {
            if (!Legendary)
                return player->HasItemCount(TOKEN_ENTRY_RDF, GetAmountTokenRDF_Mix())
                && player->HasItemCount(TOKEN_ENTRY_BG, GetAmountTokenBG_Mix())
                && player->HasItemCount(TOKEN_ENTRY_WG, GetAmountTokenWG_Mix())
                && player->HasItemCount(TOKEN_ENTRY_2V2, GetAmountToken2V2_Mix())
                && player->HasItemCount(TOKEN_ENTRY_3V3, GetAmountToken3V3_Mix())
                && player->HasItemCount(CRUSADER_ORB_ENTRY, GetAmountTokenORB_Mix())
                && player->HasItemCount(EPIC_GEM_ENTRY, GetAmountTokenGEM_Mix())
                && player->HasEnoughMoney(GetMoneyAmount_Mix());
            else
                return player->HasItemCount(TOKEN_ENTRY_RDF, GetLegendaryAmountTokenRDF_Mix())
                && player->HasItemCount(TOKEN_ENTRY_BG, GetLegendaryAmountTokenBG_Mix())
                && player->HasItemCount(TOKEN_ENTRY_WG, GetLegendaryAmountTokenWG_Mix())
                && player->HasItemCount(TOKEN_ENTRY_2V2, GetLegendaryAmountToken2V2_Mix())
                && player->HasItemCount(TOKEN_ENTRY_3V3, GetLegendaryAmountToken3V3_Mix())
                && player->HasItemCount(CRUSADER_ORB_ENTRY, GetAmountTokenORB_Mix())
                && player->HasItemCount(EPIC_GEM_ENTRY, GetLegendaryAmountTokenGEM_Mix())
                && player->HasEnoughMoney(GetLegendaryMoneyAmount_Mix());
        }
        case MODEL_TWK:
        {
            if (!Legendary)
                return player->HasItemCount(TOKEN_ENTRY_RDF, GetAmountTokenRDF_Twink())
                && player->HasItemCount(TOKEN_ENTRY_BG, GetAmountTokenBG_Twink())
                && player->HasItemCount(TOKEN_ENTRY_WG, GetAmountTokenWG_Twink())
                && player->HasItemCount(TOKEN_ENTRY_2V2, GetAmountToken2V2_Twink())
                && player->HasItemCount(TOKEN_ENTRY_3V3, GetAmountToken3V3_Twink())
                && player->HasItemCount(CRUSADER_ORB_ENTRY, GetAmountTokenORB_Twink())
                && player->HasItemCount(EPIC_GEM_ENTRY, GetAmountTokenGEM_Twink())
                && player->HasEnoughMoney(GetMoneyAmount_Twink());
            else
                return player->HasItemCount(TOKEN_ENTRY_RDF, GetLegendaryAmountTokenRDF_Twink())
                && player->HasItemCount(TOKEN_ENTRY_BG, GetLegendaryAmountTokenBG_Twink())
                && player->HasItemCount(TOKEN_ENTRY_WG, GetLegendaryAmountTokenWG_Twink())
                && player->HasItemCount(TOKEN_ENTRY_2V2, GetLegendaryAmountToken2V2_Twink())
                && player->HasItemCount(TOKEN_ENTRY_3V3, GetLegendaryAmountToken3V3_Twink())
                && player->HasItemCount(CRUSADER_ORB_ENTRY, GetLegendaryAmountTokenORB_Twink())
                && player->HasItemCount(EPIC_GEM_ENTRY, GetLegendaryAmountTokenGEM_Twink())
                && player->HasEnoughMoney(GetLegendaryMoneyAmount_Twink());
        }
    }

}

void Transmogrification::ChargeModelCost(Player* player, uint8 model, bool Legendary) const
{
    if (!player || !model)
        return;

    switch (model)
    {
        case MODEL_PVE:
        {
            if (!Legendary)
            {
                player->DestroyItemCount(TOKEN_ENTRY_RDF, GetAmountTokenRDF_PvE(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG, GetAmountTokenBG_PvE(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_WG, GetAmountTokenWG_PvE(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_2V2, GetAmountToken2V2_PvE(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_3V3, GetAmountToken3V3_PvE(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG_TWINK, GetAmountTokenORB_PvE(), true, false);
                player->DestroyItemCount(CRUSADER_ORB_ENTRY, GetAmountTokenGEM_PvE(), true, false);
                player->ModifyMoney(-GetMoneyAmount_PvE(), false);
            }
            else
            {
                player->DestroyItemCount(TOKEN_ENTRY_RDF, GetLegendaryAmountTokenRDF_PvE(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG, GetLegendaryAmountTokenBG_PvE(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_WG, GetLegendaryAmountTokenWG_PvE(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_2V2, GetLegendaryAmountToken2V2_PvE(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_3V3, GetLegendaryAmountToken3V3_PvE(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG_TWINK, GetLegendaryAmountTokenORB_PvE(), true, false);
                player->DestroyItemCount(CRUSADER_ORB_ENTRY, GetLegendaryAmountTokenGEM_PvE(), true, false);
                player->ModifyMoney(-GetLegendaryMoneyAmount_PvE(), false);
            }
        }
        case MODEL_PVP:
        {
            if (!Legendary)
            {
                player->DestroyItemCount(TOKEN_ENTRY_RDF, GetAmountTokenRDF_PvP(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG, GetAmountTokenBG_PvP(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_WG, GetAmountTokenWG_PvP(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_2V2, GetAmountToken2V2_PvP(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_3V3, GetAmountToken3V3_PvP(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG_TWINK, GetAmountTokenORB_PvP(), true, false);
                player->DestroyItemCount(CRUSADER_ORB_ENTRY, GetAmountTokenGEM_PvP(), true, false);
                player->ModifyMoney(-GetMoneyAmount_PvP(), false);
            }
            else
            {
                player->DestroyItemCount(TOKEN_ENTRY_RDF, GetLegendaryAmountTokenRDF_PvP(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG, GetLegendaryAmountTokenBG_PvP(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_WG, GetLegendaryAmountTokenWG_PvP(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_2V2, GetLegendaryAmountToken2V2_PvP(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_3V3, GetLegendaryAmountToken3V3_PvP(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG_TWINK, GetLegendaryAmountTokenORB_PvP(), true, false);
                player->DestroyItemCount(CRUSADER_ORB_ENTRY, GetLegendaryAmountTokenGEM_PvP(), true, false);
                player->ModifyMoney(-GetLegendaryMoneyAmount_PvP(), false);
            }
        }
        case MODEL_MIX:
        {
            if (!Legendary)
            {
                player->DestroyItemCount(TOKEN_ENTRY_RDF, GetAmountTokenRDF_Mix(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG, GetAmountTokenBG_Mix(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_WG, GetAmountTokenWG_Mix(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_2V2, GetAmountToken2V2_Mix(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_3V3, GetAmountToken3V3_Mix(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG_TWINK, GetAmountTokenORB_Mix(), true, false);
                player->DestroyItemCount(CRUSADER_ORB_ENTRY, GetAmountTokenGEM_Mix(), true, false);
                player->ModifyMoney(-GetMoneyAmount_Mix(), false);
            }
            else
            {
                player->DestroyItemCount(TOKEN_ENTRY_RDF, GetLegendaryAmountTokenRDF_Mix(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG, GetLegendaryAmountTokenBG_Mix(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_WG, GetLegendaryAmountTokenWG_Mix(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_2V2, GetLegendaryAmountToken2V2_Mix(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_3V3, GetLegendaryAmountToken3V3_Mix(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG_TWINK, GetLegendaryAmountTokenORB_Mix(), true, false);
                player->DestroyItemCount(CRUSADER_ORB_ENTRY, GetLegendaryAmountTokenGEM_Mix(), true, false);
                player->ModifyMoney(-GetLegendaryMoneyAmount_Mix(), false);
            }
        }
        case MODEL_TWK:
        {
            if (!Legendary)
            {
                player->DestroyItemCount(TOKEN_ENTRY_RDF, GetAmountTokenRDF_Twink(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG, GetAmountTokenBG_Twink(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_WG, GetAmountTokenWG_Twink(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_2V2, GetAmountToken2V2_Twink(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_3V3, GetAmountToken3V3_Twink(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG_TWINK, GetAmountTokenORB_Twink(), true, false);
                player->DestroyItemCount(CRUSADER_ORB_ENTRY, GetAmountTokenGEM_Twink(), true, false);
                player->ModifyMoney(-GetMoneyAmount_Twink(), false);
            }
            else
            {
                player->DestroyItemCount(TOKEN_ENTRY_RDF, GetLegendaryAmountTokenRDF_Twink(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG, GetLegendaryAmountTokenBG_Twink(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_WG, GetLegendaryAmountTokenWG_Twink(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_2V2, GetLegendaryAmountToken2V2_Twink(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_3V3, GetLegendaryAmountToken3V3_Twink(), true, false);
                player->DestroyItemCount(TOKEN_ENTRY_BG_TWINK, GetLegendaryAmountTokenORB_Twink(), true, false);
                player->DestroyItemCount(CRUSADER_ORB_ENTRY, GetLegendaryAmountTokenGEM_Twink(), true, false);
                player->ModifyMoney(-GetLegendaryMoneyAmount_Twink(), false);
            }
        }
    }
}