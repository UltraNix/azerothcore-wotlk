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

        if (CustomModelCost)
        {
            if (player->HasTransmogModelPvE())
            {
                if (EffortModel(player, MODEL_PVE, itemTransmogrifier->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false))
                    ChargeModelCost(player, MODEL_PVE, itemTransmogrifier->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false);
                else
                    return LANG_ERR_TRANSMOG_MISSING_MATERIAL;
            }
            else if (player->HasTransmogModelPvP())
            {
                if (EffortModel(player, MODEL_PVP, itemTransmogrifier->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false))
                    ChargeModelCost(player, MODEL_PVP, itemTransmogrifier->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false);
                else
                    return LANG_ERR_TRANSMOG_MISSING_MATERIAL;
            }
            else if (player->HasTransmogModelMIX())
            {
                if (EffortModel(player, MODEL_MIX, itemTransmogrifier->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false))
                    ChargeModelCost(player, MODEL_MIX, itemTransmogrifier->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false);
                else
                    return LANG_ERR_TRANSMOG_MISSING_MATERIAL;
            }
            else if (player->HasTransmogModelTWK())
            {
                if (EffortModel(player, MODEL_TWK, itemTransmogrifier->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false))
                    ChargeModelCost(player, MODEL_TWK, itemTransmogrifier->GetTemplate()->Quality == ITEM_QUALITY_LEGENDARY ? true : false);
                else
                    return LANG_ERR_TRANSMOG_MISSING_MATERIAL;
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

    return LANG_ERR_TRANSMOG_OK;
}

bool Transmogrification::CanTransmogrifyItemWithItem(Player* player, ItemTemplate const* target, ItemTemplate const* source) const
{
    if (!target || !source)
        return false;

    bool isWarglaive = source->ItemId == 32837 || source->ItemId == 32838;

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

    if ((!SuitableForTransmogrification(player, target) && !(isWarglaive && player->getClass() == CLASS_DEATH_KNIGHT)) || (!SuitableForTransmogrification(player, source) && !(isWarglaive && player->getClass() == CLASS_DEATH_KNIGHT))) // if (!transmogrified->CanTransmogrify() || !transmogrifier->CanBeTransmogrified())
        return false;

    if (IsRangedWeapon(source->Class, source->SubClass) != IsRangedWeapon(target->Class, target->SubClass))
        return false;

    if (source->SubClass != target->SubClass && !IsRangedWeapon(target->Class, target->SubClass))
    {
        if (source->Class == ITEM_CLASS_ARMOR && !AllowMixedArmorTypes)
            return false;
        if (source->Class == ITEM_CLASS_WEAPON && !AllowMixedWeaponTypes && !isWarglaive)
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

    CustomModelCost = sConfigMgr->GetBoolDefault("Transmogrification.CustomModelCost", false);

    // Tokens entries
    TokenEntryRDF    = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenEntryRDF", 92000));
    TokenEntryBG     = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenEntryBG", 92001));
    TokenEntryWG     = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenEntryWG", 43589));
    TokenEntry2V2    = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenEntry2V2", 92002));
    TokenEntry3v3    = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenEntry3V3", 92003));
    TokenEntryTwink  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenEntryTwink", 92004));

    TokenEntryExtra1 = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenEntryExtra1", 47556));
    TokenEntryExtra2 = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenEntryExtra2", 36919));

    // Rewards
    IsTokenRewardEnabled  = sConfigMgr->GetBoolDefault("Transmogrification.Rewards.Enable", false);
    TokenRewardCountRDF   = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenRewardRDF.Count", 1));
    TokenRewardCountBG    = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenRewardBG.Count", 1));
    TokenRewardCount2V2   = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenReward2V2.Count", 1));
    TokenRewardCount3V3   = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenReward3V3.Count", 1));
    TokenRewardCountTwink = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenRewardTwink.Count", 1));

    // Model PvE
    pve_token_rdf = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.PvE.Count", 12));
    pve_token_bg  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.PvE.Count", 5));
    pve_token_wg  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.PvE.Count", 9));
    pve_token_2v2 = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.PvE.Count", 0));
    pve_token_3v3 = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.PvE.Count", 0));
    pve_token_orb = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.PvE.Count", 0));
    pve_token_gem = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.PvE.Count", 1));
    pve_money_amount = int32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.PvE", 1500));

    // Legendary PvE
    pve_token_rdf_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.PvE.Legendary.Count", 60));
    pve_token_bg_legendary  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.PvE.Legendary.Count", 30));
    pve_token_wg_legendary  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.PvE.Legendary.Count", 40));
    pve_token_2v2_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.PvE.Legendary.Count", 0));
    pve_token_3v3_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.PvE.Legendary.Count", 0));
    pve_token_orb_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.PvE.Legendary.Count", 5));
    pve_token_gem_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.PvE.Legendary.Count", 5));
    pve_money_amount_legendary = int32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.Legendary.PvE", 5000));

    // Model PvP
    pvp_token_rdf = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.PvP.Count", 3));
    pvp_token_bg  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.PvP.Count", 12));
    pvp_token_wg  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.PvP.Count", 9));
    pvp_token_2v2 = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.PvP.Count", 0));
    pvp_token_3v3 = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.PvP.Count", 15));
    pvp_token_orb = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.PvP.Count", 0));
    pvp_token_gem = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.PvP.Count", 1));
    pvp_money_amount = int32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.PvP", 1500));

    // Legendary PvP
    pvp_token_rdf_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.PvP.Legendary.Count", 18));
    pvp_token_bg_legendary  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.PvP.Legendary.Count", 48));
    pvp_token_wg_legendary  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.PvP.Legendary.Count", 40));
    pvp_token_2v2_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.PvP.Legendary.Count", 0));
    pvp_token_3v3_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.PvP.Legendary.Count", 75));
    pvp_token_orb_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.PvP.Legendary.Count", 5));
    pvp_token_gem_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.PvP.Legendary.Count", 5));
    pvp_money_amount_legendary = int32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.Legendary.PvP", 5000));

    // Model Mix
    mix_token_rdf = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.Mix.Count", 5));
    mix_token_bg  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.Mix.Count", 6));
    mix_token_wg  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.Mix.Count", 6));
    mix_token_2v2 = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.Mix.Count", 20));
    mix_token_3v3 = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.Mix.Count", 10));
    mix_token_orb = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.Mix.Count", 0));
    mix_token_gem = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.Mix.Count", 0));
    mix_money_amount = int32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.Mix", 500));

    // Legendary Mix
    mix_token_rdf_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.Mix.Legendary.Count", 25));
    mix_token_bg_legendary  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.Mix.Legendary.Count", 30));
    mix_token_wg_legendary  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.Mix.Legendary.Count", 30));
    mix_token_2v2_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.Mix.Legendary.Count", 100));
    mix_token_3v3_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.Mix.Legendary.Count", 60));
    mix_token_orb_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.Mix.Legendary.Count", 3));
    mix_token_gem_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.Mix.Legendary.Count", 5));
    mix_money_amount_legendary = int32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.Legendary.Mix", 3500));

    // Model Twink
    twink_token_rdf    = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.Twink.Count", 0));
    twink_token_bg     = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.Twink.Count", 30));
    twink_token_wg     = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.Twink.Count", 0));
    twink_token_2v2    = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.Twink.Count", 0));
    twink_token_3v3    = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.Twink.Count", 0));
    twink_token_twink  = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenTwink.Twink.Count", 0));
    twink_token_orb    = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.Twink.Count", 0));
    twink_token_gem    = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.Twink.Count", 0));
    twink_money_amount = int32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.Twink", 500));

    // Legendary Twink
    twink_token_rdf_legendary   = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenRDF.Twink.Legendary.Count", 0));
    twink_token_bg_legendary    = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenBG.Twink.Legendary.Count", 180));
    twink_token_wg_legendary    = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenWG.Twink.Legendary.Count", 0));
    twink_token_2v2_legendary   = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token2V2.Twink.Legendary.Count", 0));
    twink_token_3v3_legendary   = uint32(sConfigMgr->GetIntDefault("Transmogrification.Token3V3.Twink.Legendary.Count", 0));
    twink_token_twink_legendary = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenTwink.Twink.Legendary.Count", 0));
    twink_token_orb_legendary   = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenORB.Twink.Legendary.Count", 4));
    twink_token_gem_legendary   = uint32(sConfigMgr->GetIntDefault("Transmogrification.TokenGEM.Twink.Legendary.Count", 0));
    twink_money_amount_legendary = int32(sConfigMgr->GetIntDefault("Transmogrification.MoneyAmount.Legendary.Twink", 4000));

    // Model Reset
    model_reset_coin_cost = uint32(sConfigMgr->GetIntDefault("Transmogrification.ModelReset.CoinCost", 100));
    model_reset_gold_cost = int32(sConfigMgr->GetIntDefault("Transmogrification.ModelReset.GoldCost", 500));

    // Model Remove
    model_remove_cost      = int32(sConfigMgr->GetIntDefault("Transmogrification.ModelRemove.Cost", 50));
    model_full_remove_cost = int32(sConfigMgr->GetIntDefault("Transmogrification.FullModelRemove.Cost", 500));

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
bool Transmogrification::GetCustomModelCost() const
{
    return CustomModelCost;
}
// Token entries
uint32 Transmogrification::GetTokenEntryRDF() const
{
    return TokenEntryRDF;
}
uint32 Transmogrification::GetTokenEntryBG() const
{
    return TokenEntryBG;
}
uint32 Transmogrification::GetTokenEntryWG() const
{
    return TokenEntryWG;
}
uint32 Transmogrification::GetTokenEntry2V2() const
{
    return TokenEntry2V2;
}
uint32 Transmogrification::GetTokenEntry3V3() const
{
    return TokenEntry3v3;
}
uint32 Transmogrification::GetTokenEntryTwink() const
{
    return TokenEntryTwink;
}
uint32 Transmogrification::GetTokenEntryExtra1() const
{
    return TokenEntryExtra1;
}
uint32 Transmogrification::GetTokenEntryExtra2() const
{
    return TokenEntryExtra2;
}
bool Transmogrification::TokenRewardEnabled() const
{
    return IsTokenRewardEnabled;
}
// Rewards
uint32 Transmogrification::GetTokenRewardCountRDF() const
{
    return TokenRewardCountRDF;
}
uint32 Transmogrification::GetTokenRewardCountBG() const
{
    return TokenRewardCountBG;
}
uint32 Transmogrification::GetTokenRewardCount2V2() const
{
    return TokenRewardCount2V2;
}
uint32 Transmogrification::GetTokenRewardCount3V3() const
{
    return TokenRewardCount3V3;
}
uint32 Transmogrification::GetTokenRewardCountTwink() const
{
    return TokenRewardCountTwink;
}
// Model PvE
uint32 Transmogrification::GetAmountTokenRDF_PvE() const
{
    return pve_token_rdf;
}
uint32 Transmogrification::GetAmountTokenBG_PvE() const
{
    return pve_token_bg;
}
uint32 Transmogrification::GetAmountTokenWG_PvE() const
{
    return pve_token_wg;
}
uint32 Transmogrification::GetAmountToken2V2_PvE() const
{
    return pve_token_2v2;
}
uint32 Transmogrification::GetAmountToken3V3_PvE() const
{
    return pve_token_3v3;
}
uint32 Transmogrification::GetAmountTokenORB_PvE() const
{
    return pve_token_orb;
}
uint32 Transmogrification::GetAmountTokenGEM_PvE() const
{
    return pve_token_gem;
}
int32 Transmogrification::GetMoneyAmount_PvE() const
{
    return pve_money_amount * GOLD;
}
// Legendary PvE
uint32 Transmogrification::GetLegendaryAmountTokenRDF_PvE() const
{
    return pve_token_rdf_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenBG_PvE() const
{
    return pve_token_bg_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenWG_PvE() const
{
    return pve_token_wg_legendary;
}
uint32 Transmogrification::GetLegendaryAmountToken2V2_PvE() const
{
    return pve_token_2v2_legendary;
}
uint32 Transmogrification::GetLegendaryAmountToken3V3_PvE() const
{
    return pve_token_3v3_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenORB_PvE() const
{
    return pve_token_orb_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenGEM_PvE() const
{
    return pve_token_gem_legendary;
}
int32 Transmogrification::GetLegendaryMoneyAmount_PvE() const
{
    return pve_money_amount_legendary * GOLD;
}
// Model PvP
uint32 Transmogrification::GetAmountTokenRDF_PvP() const
{
    return pvp_token_rdf;
}
uint32 Transmogrification::GetAmountTokenBG_PvP() const
{
    return pvp_token_bg;
}
uint32 Transmogrification::GetAmountTokenWG_PvP() const
{
    return pvp_token_wg;
}
uint32 Transmogrification::GetAmountToken2V2_PvP() const
{
    return pvp_token_2v2;
}
uint32 Transmogrification::GetAmountToken3V3_PvP() const
{
    return pvp_token_3v3;
}
uint32 Transmogrification::GetAmountTokenORB_PvP() const
{
    return pvp_token_orb;
}
uint32 Transmogrification::GetAmountTokenGEM_PvP() const
{
    return pvp_token_gem;
}
int32 Transmogrification::GetMoneyAmount_PvP() const
{
    return pvp_money_amount * GOLD;
}
// Legendary PvP
uint32 Transmogrification::GetLegendaryAmountTokenRDF_PvP() const
{
    return pvp_token_rdf_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenBG_PvP() const
{
    return pvp_token_bg_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenWG_PvP() const
{
    return pvp_token_wg_legendary;
}
uint32 Transmogrification::GetLegendaryAmountToken2V2_PvP() const
{
    return pvp_token_2v2_legendary;
}
uint32 Transmogrification::GetLegendaryAmountToken3V3_PvP() const
{
    return pvp_token_3v3_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenORB_PvP() const
{
    return pvp_token_orb_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenGEM_PvP() const
{
    return pvp_token_gem_legendary;
}
int32 Transmogrification::GetLegendaryMoneyAmount_PvP() const
{
    return pvp_money_amount_legendary * GOLD;
}
// Model Mix
uint32 Transmogrification::GetAmountTokenRDF_Mix() const
{
    return mix_token_rdf;
}
uint32 Transmogrification::GetAmountTokenBG_Mix() const
{
    return mix_token_bg;
}
uint32 Transmogrification::GetAmountTokenWG_Mix() const
{
    return mix_token_wg;
}
uint32 Transmogrification::GetAmountToken2V2_Mix() const
{
    return mix_token_2v2;
}
uint32 Transmogrification::GetAmountToken3V3_Mix() const
{
    return mix_token_3v3;
}
uint32 Transmogrification::GetAmountTokenORB_Mix() const
{
    return mix_token_orb;
}
uint32 Transmogrification::GetAmountTokenGEM_Mix() const
{
    return mix_token_gem;
}
int32 Transmogrification::GetMoneyAmount_Mix() const
{
    return mix_money_amount * GOLD;
}
// Legendary Mix
uint32 Transmogrification::GetLegendaryAmountTokenRDF_Mix() const
{
    return mix_token_rdf_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenBG_Mix() const
{
    return mix_token_bg_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenWG_Mix() const
{
    return mix_token_wg_legendary;
}
uint32 Transmogrification::GetLegendaryAmountToken2V2_Mix() const
{
    return mix_token_2v2_legendary;
}
uint32 Transmogrification::GetLegendaryAmountToken3V3_Mix() const
{
    return mix_token_3v3_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenORB_Mix() const
{
    return mix_token_orb_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenGEM_Mix() const
{
    return mix_token_gem_legendary;
}
int32 Transmogrification::GetLegendaryMoneyAmount_Mix() const
{
    return mix_money_amount_legendary * GOLD;
}
// Model Twink
uint32 Transmogrification::GetAmountTokenRDF_Twink() const
{
    return twink_token_rdf;
}
uint32 Transmogrification::GetAmountTokenBG_Twink() const
{
    return twink_token_bg;
}
uint32 Transmogrification::GetAmountTokenWG_Twink() const
{
    return twink_token_wg;
}
uint32 Transmogrification::GetAmountToken2V2_Twink() const
{
    return twink_token_2v2;
}
uint32 Transmogrification::GetAmountToken3V3_Twink() const
{
    return twink_token_3v3;
}
uint32 Transmogrification::GetAmountTokenTwink_Twink() const
{
    return twink_token_twink;
}
uint32 Transmogrification::GetAmountTokenORB_Twink() const
{
    return twink_token_orb;
}
uint32 Transmogrification::GetAmountTokenGEM_Twink() const
{
    return twink_token_gem;
}
int32 Transmogrification::GetMoneyAmount_Twink() const
{
    return twink_money_amount * GOLD;
}
// Legendary Twink
uint32 Transmogrification::GetLegendaryAmountTokenRDF_Twink() const
{
    return twink_token_rdf_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenBG_Twink() const
{
    return twink_token_bg_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenWG_Twink() const
{
    return twink_token_wg_legendary;
}
uint32 Transmogrification::GetLegendaryAmountToken2V2_Twink() const
{
    return twink_token_2v2_legendary;
}
uint32 Transmogrification::GetLegendaryAmountToken3V3_Twink() const
{
    return twink_token_3v3_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenTwink_Twink() const
{
    return twink_token_twink_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenORB_Twink() const
{
    return twink_token_orb_legendary;
}
uint32 Transmogrification::GetLegendaryAmountTokenGEM_Twink() const
{
    return twink_token_gem_legendary;
}
int32 Transmogrification::GetLegendaryMoneyAmount_Twink() const
{
    return twink_money_amount_legendary * GOLD;
}
// Model Reset
uint32 Transmogrification::GetResetCoinCost() const
{
    return model_reset_coin_cost;
}
int32 Transmogrification::GetResetGoldCost() const
{
    return model_reset_gold_cost * GOLD;
}
// Model Remove
int32 Transmogrification::GetRemoveCost() const
{
    return model_remove_cost * GOLD;
}
int32 Transmogrification::GetFullRemoveCost() const
{
    return model_full_remove_cost * GOLD;
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
    if (!player || !model || model >= MODEL_MAX)
        return false;

    switch (model)
    {
        case MODEL_PVE:
        {

            if (!Legendary)
                return 
                   (GetAmountTokenRDF_PvE() != 0 ? player->HasItemCount(GetTokenEntryRDF(), GetAmountTokenRDF_PvE()) : true)
                && (GetAmountTokenBG_PvE()  != 0 ? player->HasItemCount(GetTokenEntryBG(), GetAmountTokenBG_PvE()) : true)
                && (GetAmountTokenWG_PvE()  != 0 ? player->HasItemCount(GetTokenEntryWG(), GetAmountTokenWG_PvE()) : true)
                && (GetAmountToken2V2_PvE() != 0 ? player->HasItemCount(GetTokenEntry2V2(), GetAmountToken2V2_PvE()) : true)
                && (GetAmountToken3V3_PvE() != 0 ? player->HasItemCount(GetTokenEntry3V3(), GetAmountToken3V3_PvE()) : true)
                && (GetAmountTokenORB_PvE() != 0 ? player->HasItemCount(GetTokenEntryExtra1(), GetAmountTokenORB_PvE()) : true)
                && (GetAmountTokenGEM_PvE() != 0 ? player->HasItemCount(GetTokenEntryExtra2(), GetAmountTokenGEM_PvE()) : true)
                && (GetMoneyAmount_PvE()    != 0 ? player->HasEnoughMoney(GetMoneyAmount_PvE()) : true);
            else
                return 
                   (GetLegendaryAmountTokenRDF_PvE() != 0 ? player->HasItemCount(GetTokenEntryRDF(), GetLegendaryAmountTokenRDF_PvE()) : true)
                && (GetLegendaryAmountTokenBG_PvE()  != 0 ? player->HasItemCount(GetTokenEntryBG(), GetLegendaryAmountTokenBG_PvE()) : true)
                && (GetLegendaryAmountTokenWG_PvE()  != 0 ? player->HasItemCount(GetTokenEntryWG(), GetLegendaryAmountTokenWG_PvE()) : true)
                && (GetLegendaryAmountToken2V2_PvE() != 0 ? player->HasItemCount(GetTokenEntry2V2(), GetLegendaryAmountToken2V2_PvE()) : true)
                && (GetLegendaryAmountToken3V3_PvE() != 0 ? player->HasItemCount(GetTokenEntry3V3(), GetLegendaryAmountToken3V3_PvE()) : true)
                && (GetLegendaryAmountTokenORB_PvE() != 0 ? player->HasItemCount(GetTokenEntryExtra1(), GetLegendaryAmountTokenORB_PvE()) : true)
                && (GetLegendaryAmountTokenGEM_PvE() != 0 ? player->HasItemCount(GetTokenEntryExtra2(), GetLegendaryAmountTokenGEM_PvE()) : true)
                && (GetLegendaryMoneyAmount_PvE()    != 0 ? player->HasEnoughMoney(GetLegendaryMoneyAmount_PvE()) : true);
        }
        case MODEL_PVP:
        {
            if (!Legendary)
                return 
                   (GetAmountTokenRDF_PvP() != 0 ? player->HasItemCount(GetTokenEntryRDF(), GetAmountTokenRDF_PvP()) : true)
                && (GetAmountTokenBG_PvP()  != 0 ? player->HasItemCount(GetTokenEntryBG(), GetAmountTokenBG_PvP()) : true)
                && (GetAmountTokenWG_PvP()  != 0 ? player->HasItemCount(GetTokenEntryWG(), GetAmountTokenWG_PvP()) : true)
                && (GetAmountToken2V2_PvP() != 0 ? player->HasItemCount(GetTokenEntry2V2(), GetAmountToken2V2_PvP()) : true)
                && (GetAmountToken3V3_PvP() != 0 ? player->HasItemCount(GetTokenEntry3V3(), GetAmountToken3V3_PvP()) : true)
                && (GetAmountTokenORB_PvP() != 0 ? player->HasItemCount(GetTokenEntryExtra1(), GetAmountTokenORB_PvP()) : true)
                && (GetAmountTokenGEM_PvP() != 0 ? player->HasItemCount(GetTokenEntryExtra2(), GetAmountTokenGEM_PvP()) : true)
                && (GetMoneyAmount_PvP()    != 0 ? player->HasEnoughMoney(GetMoneyAmount_PvP()) : true);
            else
                return 
                   (GetLegendaryAmountTokenRDF_PvP() != 0 ? player->HasItemCount(GetTokenEntryRDF(), GetLegendaryAmountTokenRDF_PvP()) : true)
                && (GetLegendaryAmountTokenBG_PvP()  != 0 ? player->HasItemCount(GetTokenEntryBG(), GetLegendaryAmountTokenBG_PvP()) : true)
                && (GetLegendaryAmountTokenWG_PvP()  != 0 ? player->HasItemCount(GetTokenEntryWG(), GetLegendaryAmountTokenWG_PvP()) : true)
                && (GetLegendaryAmountToken2V2_PvP() != 0 ? player->HasItemCount(GetTokenEntry2V2(), GetLegendaryAmountToken2V2_PvP()) : true)
                && (GetLegendaryAmountToken3V3_PvP() != 0 ? player->HasItemCount(GetTokenEntry3V3(), GetLegendaryAmountToken3V3_PvP()) : true)
                && (GetLegendaryAmountTokenORB_PvP() != 0 ? player->HasItemCount(GetTokenEntryExtra1(), GetLegendaryAmountTokenORB_PvP()) : true)
                && (GetLegendaryAmountTokenGEM_PvP() != 0 ? player->HasItemCount(GetTokenEntryExtra2(), GetLegendaryAmountTokenGEM_PvP()) : true)
                && (GetLegendaryMoneyAmount_PvP()    != 0 ? player->HasEnoughMoney(GetLegendaryMoneyAmount_PvP()) : true);
        }
        case MODEL_MIX:
        {
            if (!Legendary)
                return 
                   (GetAmountTokenRDF_Mix() != 0 ? player->HasItemCount(GetTokenEntryRDF(), GetAmountTokenRDF_Mix()) : true)
                && (GetAmountTokenBG_Mix()  != 0 ? player->HasItemCount(GetTokenEntryBG(), GetAmountTokenBG_Mix()) : true)
                && (GetAmountTokenWG_Mix()  != 0 ? player->HasItemCount(GetTokenEntryWG(), GetAmountTokenWG_Mix()) : true)
                && (GetAmountToken2V2_Mix() != 0 ? player->HasItemCount(GetTokenEntry2V2(), GetAmountToken2V2_Mix()) : true)
                && (GetAmountToken3V3_Mix() != 0 ? player->HasItemCount(GetTokenEntry3V3(), GetAmountToken3V3_Mix()) : true)
                && (GetAmountTokenORB_Mix() != 0 ? player->HasItemCount(GetTokenEntryExtra1(), GetAmountTokenORB_Mix()) : true)
                && (GetAmountTokenGEM_Mix() != 0 ? player->HasItemCount(GetTokenEntryExtra2(), GetAmountTokenGEM_Mix()) : true)
                && (GetMoneyAmount_Mix()    != 0 ? player->HasEnoughMoney(GetMoneyAmount_Mix()) : true);
            else
                return 
                   (GetLegendaryAmountTokenRDF_Mix() != 0 ? player->HasItemCount(GetTokenEntryRDF(), GetLegendaryAmountTokenRDF_Mix()) : true)
                && (GetLegendaryAmountTokenBG_Mix()  != 0 ? player->HasItemCount(GetTokenEntryBG(), GetLegendaryAmountTokenBG_Mix()) : true)
                && (GetLegendaryAmountTokenWG_Mix()  != 0 ? player->HasItemCount(GetTokenEntryWG(), GetLegendaryAmountTokenWG_Mix()) : true)
                && (GetLegendaryAmountToken2V2_Mix() != 0 ? player->HasItemCount(GetTokenEntry2V2(), GetLegendaryAmountToken2V2_Mix()) : true)
                && (GetLegendaryAmountToken3V3_Mix() != 0 ? player->HasItemCount(GetTokenEntry3V3(), GetLegendaryAmountToken3V3_Mix()) : true)
                && (GetLegendaryAmountTokenORB_Mix() != 0 ? player->HasItemCount(GetTokenEntryExtra1(), GetLegendaryAmountTokenORB_Mix()) : true)
                && (GetLegendaryAmountTokenGEM_Mix() != 0 ? player->HasItemCount(GetTokenEntryExtra2(), GetLegendaryAmountTokenGEM_Mix()) : true)
                && (GetLegendaryMoneyAmount_Mix()    != 0 ? player->HasEnoughMoney(GetLegendaryMoneyAmount_Mix()) : true);
        }
        case MODEL_TWK:
        {
            if (!Legendary)
                return 
                   (GetAmountTokenRDF_Twink()   != 0 ? player->HasItemCount(GetTokenEntryRDF(), GetAmountTokenRDF_Twink()) : true)
                && (GetAmountTokenBG_Twink()    != 0 ? player->HasItemCount(GetTokenEntryBG(), GetAmountTokenBG_Twink()) : true)
                && (GetAmountTokenWG_Twink()    != 0 ? player->HasItemCount(GetTokenEntryWG(), GetAmountTokenWG_Twink()) : true)
                && (GetAmountToken2V2_Twink()   != 0 ? player->HasItemCount(GetTokenEntry2V2(), GetAmountToken2V2_Twink()) : true)
                && (GetAmountToken3V3_Twink()   != 0 ? player->HasItemCount(GetTokenEntry3V3(), GetAmountToken3V3_Twink()) : true)
                && (GetAmountTokenTwink_Twink() != 0 ? player->HasItemCount(GetTokenEntryTwink(), GetAmountTokenTwink_Twink()) : true)
                && (GetAmountTokenORB_Twink()   != 0 ? player->HasItemCount(GetTokenEntryExtra1(), GetAmountTokenORB_Twink()) : true)
                && (GetAmountTokenGEM_Twink(  ) != 0 ? player->HasItemCount(GetTokenEntryExtra2(), GetAmountTokenGEM_Twink()) : true)
                && (GetMoneyAmount_Twink()      != 0 ? player->HasEnoughMoney(GetMoneyAmount_Twink()) : true);
            else
                return 
                   (GetLegendaryAmountTokenRDF_Twink() != 0 ? player->HasItemCount(GetTokenEntryRDF(), GetLegendaryAmountTokenRDF_Twink()) : true)
                && (GetLegendaryAmountTokenBG_Twink()  != 0 ? player->HasItemCount(GetTokenEntryBG(), GetLegendaryAmountTokenBG_Twink()) : true)
                && (GetLegendaryAmountTokenWG_Twink()  != 0 ? player->HasItemCount(GetTokenEntryWG(), GetLegendaryAmountTokenWG_Twink()) : true)
                && (GetLegendaryAmountToken2V2_Twink() != 0 ? player->HasItemCount(GetTokenEntry2V2(), GetLegendaryAmountToken2V2_Twink()) : true)
                && (GetLegendaryAmountToken3V3_Twink() != 0 ? player->HasItemCount(GetTokenEntry3V3(), GetLegendaryAmountToken3V3_Twink()) : true)
                && (GetLegendaryAmountTokenTwink_Twink() != 0 ? player->HasItemCount(GetTokenEntryTwink(), GetLegendaryAmountTokenTwink_Twink()) : true)
                && (GetLegendaryAmountTokenORB_Twink() != 0 ? player->HasItemCount(GetTokenEntryExtra1(), GetLegendaryAmountTokenORB_Twink()) : true)
                && (GetLegendaryAmountTokenGEM_Twink() != 0 ? player->HasItemCount(GetTokenEntryExtra2(), GetLegendaryAmountTokenGEM_Twink()) : true)
                && (GetLegendaryMoneyAmount_Twink()    != 0 ? player->HasEnoughMoney(GetLegendaryMoneyAmount_Twink()) : true);
        }
    }

    return false;
}

void Transmogrification::ChargeModelCost(Player* player, uint8 model, bool Legendary) const
{
    if (!player || !model || model >= MODEL_MAX)
        return;

    switch (model)
    {
        // Model PvE
        case MODEL_PVE:
        {
            if (!Legendary)
            {
                if (GetAmountTokenRDF_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntryRDF(), GetAmountTokenRDF_PvE(), true, false);
                if (GetAmountTokenBG_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntryBG(), GetAmountTokenBG_PvE(), true, false);
                if (GetAmountTokenWG_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntryWG(), GetAmountTokenWG_PvE(), true, false);
                if (GetAmountToken2V2_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntry2V2(), GetAmountToken2V2_PvE(), true, false);
                if (GetAmountToken3V3_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntry3V3(), GetAmountToken3V3_PvE(), true, false);
                if (GetAmountTokenORB_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra1(), GetAmountTokenORB_PvE(), true, false);
                if (GetAmountTokenGEM_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra2(), GetAmountTokenGEM_PvE(), true, false);
                if (GetMoneyAmount_PvE() != 0)
                    player->ModifyMoney(-GetMoneyAmount_PvE(), false);
            }
            else
            {
                if (GetLegendaryAmountTokenRDF_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntryRDF(), GetLegendaryAmountTokenRDF_PvE(), true, false);
                if (GetLegendaryAmountTokenBG_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntryBG(), GetLegendaryAmountTokenBG_PvE(), true, false);
                if (GetLegendaryAmountTokenWG_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntryWG(), GetLegendaryAmountTokenWG_PvE(), true, false);
                if (GetLegendaryAmountToken2V2_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntry2V2(), GetLegendaryAmountToken2V2_PvE(), true, false);
                if (GetLegendaryAmountToken3V3_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntry3V3(), GetLegendaryAmountToken3V3_PvE(), true, false);
                if (GetLegendaryAmountTokenORB_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra1(), GetLegendaryAmountTokenORB_PvE(), true, false);
                if (GetLegendaryAmountTokenGEM_PvE() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra2(), GetLegendaryAmountTokenGEM_PvE(), true, false);
                if (GetLegendaryMoneyAmount_PvE() != 0)
                    player->ModifyMoney(-GetLegendaryMoneyAmount_PvE(), false);
            }
        } 
        break;
        // Model PvP
        case MODEL_PVP:
        {
            if (!Legendary)
            {
                if (GetAmountTokenRDF_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntryRDF(), GetAmountTokenRDF_PvP(), true, false);
                if (GetAmountTokenBG_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntryBG(), GetAmountTokenBG_PvP(), true, false);
                if (GetAmountTokenWG_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntryWG(), GetAmountTokenWG_PvP(), true, false);
                if (GetAmountToken2V2_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntry2V2(), GetAmountToken2V2_PvP(), true, false);
                if (GetAmountToken3V3_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntry3V3(), GetAmountToken3V3_PvP(), true, false);
                if (GetAmountTokenORB_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra1(), GetAmountTokenORB_PvP(), true, false);
                if (GetAmountTokenGEM_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra2(), GetAmountTokenGEM_PvP(), true, false);
                if (GetMoneyAmount_PvP() != 0)
                    player->ModifyMoney(-GetMoneyAmount_PvP(), false);
            }
            else
            {
                if (GetLegendaryAmountTokenRDF_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntryRDF(), GetLegendaryAmountTokenRDF_PvP(), true, false);
                if (GetLegendaryAmountTokenBG_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntryBG(), GetLegendaryAmountTokenBG_PvP(), true, false);
                if (GetLegendaryAmountTokenWG_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntryWG(), GetLegendaryAmountTokenWG_PvP(), true, false);
                if (GetLegendaryAmountToken2V2_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntry2V2(), GetLegendaryAmountToken2V2_PvP(), true, false);
                if (GetLegendaryAmountToken3V3_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntry3V3(), GetLegendaryAmountToken3V3_PvP(), true, false);
                if (GetLegendaryAmountTokenORB_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra1(), GetLegendaryAmountTokenORB_PvP(), true, false);
                if (GetLegendaryAmountTokenGEM_PvP() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra2(), GetLegendaryAmountTokenGEM_PvP(), true, false);
                if (GetLegendaryMoneyAmount_PvP() != 0)
                    player->ModifyMoney(-GetLegendaryMoneyAmount_PvP(), false);
            }
        } 
        break;
        // Model Mix
        case MODEL_MIX:
        {
            if (!Legendary)
            {
                if (GetAmountTokenRDF_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntryRDF(), GetAmountTokenRDF_Mix(), true, false);
                if (GetAmountTokenBG_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntryBG(), GetAmountTokenBG_Mix(), true, false);
                if (GetAmountTokenWG_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntryWG(), GetAmountTokenWG_Mix(), true, false);
                if (GetAmountToken2V2_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntry2V2(), GetAmountToken2V2_Mix(), true, false);
                if (GetAmountToken3V3_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntry3V3(), GetAmountToken3V3_Mix(), true, false);
                if (GetAmountTokenORB_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra1(), GetAmountTokenORB_Mix(), true, false);
                if (GetAmountTokenGEM_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra2(), GetAmountTokenGEM_Mix(), true, false);
                if (GetMoneyAmount_Mix() != 0)
                    player->ModifyMoney(-GetMoneyAmount_Mix(), false);
            }
            else
            {
                if (GetLegendaryAmountTokenRDF_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntryRDF(), GetLegendaryAmountTokenRDF_Mix(), true, false);
                if (GetLegendaryAmountTokenBG_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntryBG(), GetLegendaryAmountTokenBG_Mix(), true, false);
                if (GetLegendaryAmountTokenWG_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntryWG(), GetLegendaryAmountTokenWG_Mix(), true, false);
                if (GetLegendaryAmountToken2V2_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntry2V2(), GetLegendaryAmountToken2V2_Mix(), true, false);
                if (GetLegendaryAmountToken3V3_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntry3V3(), GetLegendaryAmountToken3V3_Mix(), true, false);
                if (GetLegendaryAmountTokenORB_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra1(), GetLegendaryAmountTokenORB_Mix(), true, false);
                if (GetLegendaryAmountTokenGEM_Mix() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra2(), GetLegendaryAmountTokenGEM_Mix(), true, false);
                if (GetLegendaryMoneyAmount_Mix() != 0)
                    player->ModifyMoney(-GetLegendaryMoneyAmount_Mix(), false);
            }
        } 
        break;
        // Model Twink
        case MODEL_TWK:
        {
            if (!Legendary)
            {
                if (GetAmountTokenRDF_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntryRDF(), GetAmountTokenRDF_Twink(), true, false);
                if (GetAmountTokenBG_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntryBG(), GetAmountTokenBG_Twink(), true, false);
                if (GetAmountTokenWG_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntryWG(), GetAmountTokenWG_Twink(), true, false);
                if (GetAmountToken2V2_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntry2V2(), GetAmountToken2V2_Twink(), true, false);
                if (GetAmountToken3V3_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntry3V3(), GetAmountToken3V3_Twink(), true, false);
                if (GetAmountTokenTwink_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntryTwink(), GetAmountTokenTwink_Twink(), true, false);
                if (GetAmountTokenORB_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra1(), GetAmountTokenORB_Twink(), true, false);
                if (GetAmountTokenGEM_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra2(), GetAmountTokenGEM_Twink(), true, false);
                if (GetMoneyAmount_Twink() != 0)
                    player->ModifyMoney(-GetMoneyAmount_Twink(), false);
            }
            else
            {
                if (GetLegendaryAmountTokenRDF_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntryRDF(), GetLegendaryAmountTokenRDF_Twink(), true, false);
                if (GetLegendaryAmountTokenBG_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntryBG(), GetLegendaryAmountTokenBG_Twink(), true, false);
                if (GetLegendaryAmountTokenWG_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntryWG(), GetLegendaryAmountTokenWG_Twink(), true, false);
                if (GetLegendaryAmountToken2V2_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntry2V2(), GetLegendaryAmountToken2V2_Twink(), true, false);
                if (GetLegendaryAmountToken3V3_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntry3V3(), GetLegendaryAmountToken3V3_Twink(), true, false);
                if (GetLegendaryAmountTokenTwink_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntryTwink(), GetLegendaryAmountTokenTwink_Twink(), true, false);
                if (GetLegendaryAmountTokenORB_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra1(), GetLegendaryAmountTokenORB_Twink(), true, false);
                if (GetLegendaryAmountTokenGEM_Twink() != 0)
                    player->DestroyItemCount(GetTokenEntryExtra2(), GetLegendaryAmountTokenGEM_Twink(), true, false);
                if (GetLegendaryMoneyAmount_Twink() != 0)
                    player->ModifyMoney(-GetLegendaryMoneyAmount_Twink(), false);
            }
        } 
        break;
    }
}