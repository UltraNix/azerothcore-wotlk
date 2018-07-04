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

#ifndef DEF_TRANSMOGRIFICATION_H
#define DEF_TRANSMOGRIFICATION_H

#include <vector>
#include "Define.h"
#include "ScriptPCH.h"
#include "Language.h"
#include "Config.h"

#define MAX_OPTIONS 25 // do not alter

class Item;
class Player;
class WorldSession;
struct ItemTemplate;

enum TransmogTrinityStrings // Language.h might have same entries, appears when executing SQL, change if needed
{
    LANG_ERR_TRANSMOG_OK                 = 12000,
    LANG_ERR_TRANSMOG_INVALID_SLOT       = 12001,
    LANG_ERR_TRANSMOG_MISSING_SRC_ITEM   = 12002,
    LANG_ERR_TRANSMOG_MISSING_DEST_ITEM  = 12003,
    LANG_ERR_TRANSMOG_INVALID_ITEMS      = 12004,
    LANG_ERR_UNTRANSMOG_OK               = 12005,
    LANG_ERR_UNTRANSMOG_NO_TRANSMOGS     = 12006,
    LANG_ERR_TRANSMOG_TWINK_EXPERIENCE   = 12007,
    LANG_ERR_TRANSMOG_MISSING_MATERIAL   = 12008,
    LANG_ERR_TRANSMOG_MISSING_COINS      = 12009
};

enum TransmogTexts
{
    TRANMOG_TEXT_ENTRY_1     = 1000500, // Transmogrification allows you to change how your items ...
    TRANMOG_TEXT_ENTRY_2     = 1000501, // Hello, $n. I can change the appearance of your armor for you ... 
    TRANMOG_TEXT_ENTRY_3     = 1000502, // PvP Model requires you to gather the following tokens: 3 Heroic Tokens ...
    TRANMOG_TEXT_ENTRY_4     = 1000503, // PvE Model requires you to gather the following tokens: 12 Heroic Tokens ...
    TRANMOG_TEXT_ENTRY_5     = 1000504, // Twink model requires you to gather the following tokens: 30 Twink ...
    TRANMOG_TEXT_ENTRY_6     = 1000505, // Mixed model requires you to gather the following tokens: 5 Heroic Tokens ...
    TRANMOG_TEXT_ENTRY_7     = 1000506, // Are you sure you want to use PvP Model ...
    TRANMOG_TEXT_ENTRY_8     = 1000507, // Are you sure you want to use PvE Model ...
    TRANMOG_TEXT_ENTRY_9     = 1000508, // Are you sure you want to use Twink Model ...
    TRANMOG_TEXT_ENTRY_10    = 1000509, // Are you sure you want to use Mixed Model ...
    TRANMOG_TEXT_ENTRY_11    = 1000510, // Hello, $n. What do you want to transmogrify? ..
    TRANMOG_TEXT_ENTRY_12    = 1000511, // Are you sure you want to change the model of acquiring ...
};

enum TransmogModels
{
    ARMORY_TRANSMOG = 0x01,  // PvE Model
    WEAPON_TRANSMOG = 0x02,  // PvP Model
    LEGEND_TRANSMOG = 0x03,  // Mix Model
    MAX_TRANSMOG    = 0x04,
};

class Transmogrification
{
public:
    typedef std::unordered_map<uint64, uint64> transmogData;
    typedef std::unordered_map<uint64, transmogData> transmogMap;
    transmogMap entryMap; // entryMap[pGUID][iGUID] = entry
    transmogData dataMap; // dataMap[iGUID] = pGUID

    bool EnableTransmogInfo;
    uint32 TransmogNpcText;
    uint32 TransmogModelText;

    // Use IsAllowed() and IsNotAllowed()
    // these are thread unsafe, but assumed to be static data so it should be safe
    std::set<uint32> Allowed;
    std::set<uint32> NotAllowed;

    bool IsTokenRewardEnabled;

    uint32 TokenEntryArmor;
    uint32 TokenEntryWeapon;
    uint32 TokenEntryLegend;

    int32 remove_transmog_visiblility_cost;

    bool AllowPoor;
    bool AllowCommon;
    bool AllowUncommon;
    bool AllowRare;
    bool AllowEpic;
    bool AllowLegendary;
    bool AllowArtifact;
    bool AllowHeirloom;

    bool AllowMixedArmorTypes;
    bool AllowMixedWeaponTypes;
    bool AllowFishingPoles;

    bool IgnoreReqRace;
    bool IgnoreReqClass;
    bool IgnoreReqSkill;
    bool IgnoreReqSpell;
    bool IgnoreReqLevel;
    bool IgnoreReqEvent;
    bool IgnoreReqStats;

    bool IsAllowed(uint32 entry) const;
    bool IsNotAllowed(uint32 entry) const;
    bool IsAllowedQuality(uint32 quality) const;
    bool IsRangedWeapon(uint32 Class, uint32 SubClass) const;

    void LoadConfig(bool reload); // thread unsafe

    std::string GetItemIcon(uint32 entry, uint32 width, uint32 height, int x, int y) const;
    std::string GetSlotIcon(uint8 slot, uint32 width, uint32 height, int x, int y) const;
    const char * GetSlotName(uint8 slot, WorldSession* session) const;
    std::string GetItemLink(ItemRef & item, WorldSession* session) const;
    std::string GetItemLink(uint32 entry, WorldSession* session) const;
    uint32 GetFakeEntry(uint64 itemGUID) const;
    void UpdateItem(Player* player, ItemRef & item) const;
    void DeleteFakeEntry(Player* player, uint8 slot, ItemRef & itemTransmogrified, SQLTransaction* trans = NULL);
    void SetFakeEntry(Player* player, uint32 newEntry, uint8 slot, ItemRef & itemTransmogrified);

    TransmogTrinityStrings Transmogrify(Player* player, uint64 itemGUID, uint8 slot /*uint32 newEntry*/);
    bool CanTransmogrifyItemWithItem(Player* player, ItemTemplate const* destination, ItemTemplate const* source) const;
    bool SuitableForTransmogrification(Player* player, ItemTemplate const* proto) const;
    bool EffortModel(Player* player, uint8 model) const;
    void ChargeModelCost(Player* player, uint8 model) const;

    void DeleteFakeFromDB(uint64 itemGUID, SQLTransaction* trans = NULL);
	void TakeRequiredAmount(Player* player, int32 amount);

    uint32 GetTokenEntryArmor() const;
    uint32 GetTokenEntryWeapon() const;
    uint32 GetTokenEntryLegend() const;
    int32 GetVisibilityTransmogCost() const;

    // Config
    bool GetEnableTransmogInfo() const;
};
#define sTransmogrification ACE_Singleton<Transmogrification, ACE_Null_Mutex>::instance()

#endif
