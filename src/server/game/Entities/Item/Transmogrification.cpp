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

const char* Transmogrification::GetSlotName(uint8 slot, WorldSession* /*session*/) const
{
    sLog->outDebug(LOG_FILTER_MODULES, "Transmogrification::GetSlotName");

    switch (slot)
    {
        case EQUIPMENT_SLOT_HEAD:      return  "Head";         // session->GetTrinityString(LANG_SLOT_NAME_HEAD);
        case EQUIPMENT_SLOT_SHOULDERS: return  "Shoulders";    // session->GetTrinityString(LANG_SLOT_NAME_SHOULDERS);
        case EQUIPMENT_SLOT_BODY:      return  "Shirt";        // session->GetTrinityString(LANG_SLOT_NAME_BODY);
        case EQUIPMENT_SLOT_CHEST:     return  "Chest";        // session->GetTrinityString(LANG_SLOT_NAME_CHEST);
        case EQUIPMENT_SLOT_WAIST:     return  "Waist";        // session->GetTrinityString(LANG_SLOT_NAME_WAIST);
        case EQUIPMENT_SLOT_LEGS:      return  "Legs";         // session->GetTrinityString(LANG_SLOT_NAME_LEGS);
        case EQUIPMENT_SLOT_FEET:      return  "Feet";         // session->GetTrinityString(LANG_SLOT_NAME_FEET);
        case EQUIPMENT_SLOT_WRISTS:    return  "Wrists";       // session->GetTrinityString(LANG_SLOT_NAME_WRISTS);
        case EQUIPMENT_SLOT_HANDS:     return  "Hands";        // session->GetTrinityString(LANG_SLOT_NAME_HANDS);
        case EQUIPMENT_SLOT_BACK:      return  "Back";         // session->GetTrinityString(LANG_SLOT_NAME_BACK);
        case EQUIPMENT_SLOT_MAINHAND:  return  "Main hand";    // session->GetTrinityString(LANG_SLOT_NAME_MAINHAND);
        case EQUIPMENT_SLOT_OFFHAND:   return  "Off hand";     // session->GetTrinityString(LANG_SLOT_NAME_OFFHAND);
        case EQUIPMENT_SLOT_RANGED:    return  "Ranged";       // session->GetTrinityString(LANG_SLOT_NAME_RANGED);
        case EQUIPMENT_SLOT_TABARD:    return  "Tabard";       // session->GetTrinityString(LANG_SLOT_NAME_TABARD);
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
        case EQUIPMENT_SLOT_HEAD:      ss << "UI-PaperDoll-Slot-Head"; break;
        case EQUIPMENT_SLOT_SHOULDERS: ss << "UI-PaperDoll-Slot-Shoulder"; break;
        case EQUIPMENT_SLOT_BODY:      ss << "UI-PaperDoll-Slot-Shirt"; break;
        case EQUIPMENT_SLOT_CHEST:     ss << "UI-PaperDoll-Slot-Chest"; break;
        case EQUIPMENT_SLOT_WAIST:     ss << "UI-PaperDoll-Slot-Waist"; break;
        case EQUIPMENT_SLOT_LEGS:      ss << "UI-PaperDoll-Slot-Legs"; break;
        case EQUIPMENT_SLOT_FEET:      ss << "UI-PaperDoll-Slot-Feet"; break;
        case EQUIPMENT_SLOT_WRISTS:    ss << "UI-PaperDoll-Slot-Wrists"; break;
        case EQUIPMENT_SLOT_HANDS:     ss << "UI-PaperDoll-Slot-Hands"; break;
        case EQUIPMENT_SLOT_BACK:      ss << "UI-PaperDoll-Slot-Chest"; break;
        case EQUIPMENT_SLOT_MAINHAND:  ss << "UI-PaperDoll-Slot-MainHand"; break;
        case EQUIPMENT_SLOT_OFFHAND:   ss << "UI-PaperDoll-Slot-SecondaryHand"; break;
        case EQUIPMENT_SLOT_RANGED:    ss << "UI-PaperDoll-Slot-Ranged"; break;
        case EQUIPMENT_SLOT_TABARD:    ss << "UI-PaperDoll-Slot-Tabard"; break;
        default: ss << "UI-Backpack-EmptySlot";
    }

    ss << ":" << width << ":" << height << ":" << x << ":" << y << "|t";
    return ss.str();
}

std::string Transmogrification::GetItemLink(ItemRef & item, WorldSession* session) const
{
    sLog->outDebug(LOG_FILTER_MODULES, "Transmogrification::GetItemLink");

    int loc_idx = session->GetSessionDbLocaleIndex();
    const ItemTemplate* temp = item->GetTemplate();
    std::string name = temp->Name1;

    //if (ItemLocale const* il = sObjectMgr->GetItemLocale(temp->ItemId))
    //    ObjectMgr::GetLocaleString(il->Name, loc_idx, name);

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

    //if (ItemLocale const* il = sObjectMgr->GetItemLocale(entry))
    //    ObjectMgr::GetLocaleString(il->Name, loc_idx, name);

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

void Transmogrification::UpdateItem(Player* player, ItemRef & item) const
{
    sLog->outDebug(LOG_FILTER_MODULES, "Transmogrification::UpdateItem");

    if (item->IsEquipped())
    {
        player->SetVisibleItemSlot(item->GetSlot(), item);
        if (player->IsInWorld())
            item->SendUpdateToPlayer(player);
    }
}

void Transmogrification::DeleteFakeEntry(Player* player, uint8 slot, ItemRef & itemTransmogrified, SQLTransaction* trans)
{
    if (!GetFakeEntry(itemTransmogrified->GetGUID()))
        return;

    DeleteFakeFromDB(itemTransmogrified->GetGUID(), trans);
    UpdateItem(player, itemTransmogrified);
}

void Transmogrification::SetFakeEntry(Player* player, uint32 newEntry, uint8 slot, ItemRef & itemTransmogrified)
{
    uint64 itemGUID = itemTransmogrified->GetGUID();
    entryMap[player->GetGUID()][itemGUID] = newEntry;
    dataMap[itemGUID] = player->GetGUID();
    CharacterDatabase.PExecute("REPLACE INTO custom_transmogrification (GUID, FakeEntry, Owner) VALUES (%u, %u, %u)", GUID_LOPART(itemGUID), newEntry, player->GetGUIDLow());
    UpdateItem(player, itemTransmogrified);
}

TransmogTrinityStrings Transmogrification::Transmogrify(Player* player, uint64 itemGUID, uint8 slot /*uint32 newEntry*/)
{
    // slot of the transmogrified item
    if (slot >= EQUIPMENT_SLOT_END)
    {
        // TC_LOG_DEBUG(LOG_FILTER_NETWORKIO, "WORLD: HandleTransmogrifyItems - Player (GUID: %u, name: %s) tried to transmogrify an item (lowguid: %u) with a wrong slot (%u) when transmogrifying items.", player->GetGUIDLow(), player->GetName().c_str(), GUID_LOPART(itemGUID), slot);
        return LANG_ERR_TRANSMOG_INVALID_SLOT;
    }

    ItemRef itemTransmogrifier = NULL;
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
    ItemRef itemTransmogrified = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
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

        if (itemTransmogrifier->GetTemplate()->Class == ITEM_CLASS_ARMOR)
        {
            if (EffortModel(player, ARMORY_TRANSMOG))
                ChargeModelCost(player, ARMORY_TRANSMOG);
            else
                return LANG_ERR_TRANSMOG_MISSING_MATERIAL;
        }
        else if (itemTransmogrifier->GetTemplate()->Class == ITEM_CLASS_WEAPON && itemTransmogrifier->GetTemplate()->Quality <= ITEM_QUALITY_EPIC)
        {

            if (EffortModel(player, WEAPON_TRANSMOG))
                ChargeModelCost(player, WEAPON_TRANSMOG);
            else
                return LANG_ERR_TRANSMOG_MISSING_MATERIAL;
        }
        else if (itemTransmogrifier->GetTemplate()->Class == ITEM_CLASS_WEAPON && itemTransmogrifier->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY)
        {

            if (EffortModel(player, LEGEND_TRANSMOG))
                ChargeModelCost(player, LEGEND_TRANSMOG);
            else
                return LANG_ERR_TRANSMOG_MISSING_MATERIAL;
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

    if (!SuitableForTransmogrification(player, target) || !SuitableForTransmogrification(player, source))
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
                (target->InventoryType == INVTYPE_WEAPON 
                    || target->InventoryType == INVTYPE_2HWEAPON 
                    || target->InventoryType == INVTYPE_WEAPONMAINHAND 
                    || target->InventoryType == INVTYPE_WEAPONOFFHAND)
                && (source->InventoryType == INVTYPE_WEAPON 
                    || source->InventoryType == INVTYPE_2HWEAPON 
                    || source->InventoryType == INVTYPE_WEAPONMAINHAND 
                    || source->InventoryType == INVTYPE_WEAPONOFFHAND)
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

    if (proto->Class != ITEM_CLASS_ARMOR && proto->Class != ITEM_CLASS_WEAPON)
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
        case ITEM_QUALITY_POOR:      return AllowPoor;
        case ITEM_QUALITY_NORMAL:    return AllowCommon;
        case ITEM_QUALITY_UNCOMMON:  return AllowUncommon;
        case ITEM_QUALITY_RARE:      return AllowRare;
        case ITEM_QUALITY_EPIC:      return AllowEpic;
        case ITEM_QUALITY_LEGENDARY: return AllowLegendary;
        case ITEM_QUALITY_ARTIFACT:  return AllowArtifact;
        case ITEM_QUALITY_HEIRLOOM:  return AllowHeirloom;
        default: return false;
    }
}

void Transmogrification::LoadConfig(bool reload)
{
    EnableTransmogInfo = sConfigMgr->GetBoolDefault("Transmogrification.EnableTransmogInfo", true);

    {
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
    }

    AllowPoor      = sConfigMgr->GetBoolDefault("Transmogrification.AllowPoor", false);
    AllowCommon    = sConfigMgr->GetBoolDefault("Transmogrification.AllowCommon", false);
    AllowUncommon  = sConfigMgr->GetBoolDefault("Transmogrification.AllowUncommon", true);
    AllowRare      = sConfigMgr->GetBoolDefault("Transmogrification.AllowRare", true);
    AllowEpic      = sConfigMgr->GetBoolDefault("Transmogrification.AllowEpic", true);
    AllowLegendary = sConfigMgr->GetBoolDefault("Transmogrification.AllowLegendary", false);
    AllowArtifact  = sConfigMgr->GetBoolDefault("Transmogrification.AllowArtifact", false);
    AllowHeirloom  = sConfigMgr->GetBoolDefault("Transmogrification.AllowHeirloom", true);

    AllowMixedArmorTypes  = sConfigMgr->GetBoolDefault("Transmogrification.AllowMixedArmorTypes", false);
    AllowMixedWeaponTypes = sConfigMgr->GetBoolDefault("Transmogrification.AllowMixedWeaponTypes", false);
    AllowFishingPoles     = sConfigMgr->GetBoolDefault("Transmogrification.AllowFishingPoles", false);

    IgnoreReqRace  = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqRace", false);
    IgnoreReqClass = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqClass", false);
    IgnoreReqSkill = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqSkill", false);
    IgnoreReqSpell = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqSpell", false);
    IgnoreReqLevel = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqLevel", false);
    IgnoreReqEvent = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqEvent", false);
    IgnoreReqStats = sConfigMgr->GetBoolDefault("Transmogrification.IgnoreReqStats", false);

    // Tokens entries
    TokenEntryArmor  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenEntryArmor", 37711));
    TokenEntryWeapon = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenEntryWeapon", 37742));
    TokenEntryLegend = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenEntryLegend", 37742));

    // Disable Transmog Visibility
    remove_transmog_visiblility_cost = int32(sConfigMgr->GetIntDefault("Transmogrification.Visibility.GoldCost", 500));
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

void Transmogrification::TakeRequiredAmount(Player* player, int32 amount)
{
    if (!player)
        return;

	PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_PREMIUM_POINTS);
	stmt->setInt32(0, -(amount));
	stmt->setUInt32(1, player->GetSession()->GetAccountId());
	LoginDatabase.Execute(stmt);
}

bool Transmogrification::GetEnableTransmogInfo() const
{
    return EnableTransmogInfo;
}

// Token entries
uint32 Transmogrification::GetTokenEntryArmor() const
{
    return TokenEntryArmor;
}
uint32 Transmogrification::GetTokenEntryWeapon() const
{
    return TokenEntryWeapon;
}
uint32 Transmogrification::GetTokenEntryLegend() const
{
    return TokenEntryLegend;
}

int32 Transmogrification::GetVisibilityTransmogCost() const
{
    return remove_transmog_visiblility_cost * GOLD;
}

bool Transmogrification::EffortModel(Player* player, uint8 model) const
{
    if (!player || !model || model >= MAX_TRANSMOG)
        return false;

    switch (model)
    {
        case ARMORY_TRANSMOG:
            return player->HasItemCount(GetTokenEntryArmor(), 1);
        case WEAPON_TRANSMOG:
            return player->HasItemCount(GetTokenEntryWeapon(), 1);
        case LEGEND_TRANSMOG:
            return player->HasItemCount(GetTokenEntryWeapon(), 15);
    }

    return false;
}

void Transmogrification::ChargeModelCost(Player* player, uint8 model) const
{
    if (!player || !model || model >= MAX_TRANSMOG)
        return;

    switch (model)
    {
        case ARMORY_TRANSMOG:
            player->DestroyItemCount(GetTokenEntryArmor(), 1, true, false);
            break;
        case WEAPON_TRANSMOG:
            player->DestroyItemCount(GetTokenEntryWeapon(), 1, true, false);
            break;
        case LEGEND_TRANSMOG:
            player->DestroyItemCount(GetTokenEntryWeapon(), 15, true, false);
            break;
    }
}
