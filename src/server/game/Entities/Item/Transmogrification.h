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
    MODEL_PVE = 0x01,  // PvE Model
    MODEL_PVP = 0x02,  // PvP Model
    MODEL_MIX = 0x03,  // Mix Model
    MODEL_TWK = 0x04,  // Twink Model
    MODEL_MAX = 0x05,
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

    bool CustomModelCost;
    bool IsTokenRewardEnabled;

    // Token entries
    uint32 TokenEntryRDF;
    uint32 TokenEntryBG;
    uint32 TokenEntryWG;
    uint32 TokenEntry2V2;
    uint32 TokenEntry3v3;
    uint32 TokenEntryTwink;
    uint32 TokenEntryExtra1;
    uint32 TokenEntryExtra2;

    // Rewards
    uint32 TokenRewardCountRDF;
    uint32 TokenRewardCountBG;
    uint32 TokenRewardCount2V2;
    uint32 TokenRewardCount3V3;
    uint32 TokenRewardCountTwink;

    // Model PvE
    uint32 pve_token_rdf;
    uint32 pve_token_bg;
    uint32 pve_token_wg;
    uint32 pve_token_2v2;
    uint32 pve_token_3v3;
    uint32 pve_token_orb;
    uint32 pve_token_gem;
    int32 pve_money_amount;

    uint32 pve_token_rdf_legendary;
    uint32 pve_token_bg_legendary;
    uint32 pve_token_wg_legendary;
    uint32 pve_token_2v2_legendary;
    uint32 pve_token_3v3_legendary;
    uint32 pve_token_orb_legendary;
    uint32 pve_token_gem_legendary;
    int32 pve_money_amount_legendary;

    // Model PvP
    uint32 pvp_token_rdf;
    uint32 pvp_token_bg;
    uint32 pvp_token_wg;
    uint32 pvp_token_2v2;
    uint32 pvp_token_3v3;
    uint32 pvp_token_orb;
    uint32 pvp_token_gem;
    int32 pvp_money_amount;

    uint32 pvp_token_rdf_legendary;
    uint32 pvp_token_bg_legendary;
    uint32 pvp_token_wg_legendary;
    uint32 pvp_token_2v2_legendary;
    uint32 pvp_token_3v3_legendary;
    uint32 pvp_token_orb_legendary;
    uint32 pvp_token_gem_legendary;
    int32 pvp_money_amount_legendary;

    // Model Mix
    uint32 mix_token_rdf;
    uint32 mix_token_bg;
    uint32 mix_token_wg;
    uint32 mix_token_2v2;
    uint32 mix_token_3v3;
    uint32 mix_token_orb;
    uint32 mix_token_gem;
    int32 mix_money_amount;

    uint32 mix_token_rdf_legendary;
    uint32 mix_token_bg_legendary;
    uint32 mix_token_wg_legendary;
    uint32 mix_token_2v2_legendary;
    uint32 mix_token_3v3_legendary;
    uint32 mix_token_orb_legendary;
    uint32 mix_token_gem_legendary;
    int32 mix_money_amount_legendary;

    // Model Twink
    uint32 twink_token_rdf;
    uint32 twink_token_bg;
    uint32 twink_token_wg;
    uint32 twink_token_2v2;
    uint32 twink_token_3v3;
    uint32 twink_token_twink;
    uint32 twink_token_orb;
    uint32 twink_token_gem;
    int32 twink_money_amount;

    uint32 twink_token_rdf_legendary;
    uint32 twink_token_bg_legendary;
    uint32 twink_token_wg_legendary;
    uint32 twink_token_2v2_legendary;
    uint32 twink_token_3v3_legendary;
    uint32 twink_token_twink_legendary;
    uint32 twink_token_orb_legendary;
    uint32 twink_token_gem_legendary;
    int32 twink_money_amount_legendary;

    // Model Reset
    uint32 model_reset_coin_cost;
    int32 model_reset_gold_cost;
    // Model Remove
    int32 model_remove_cost;
    int32 model_full_remove_cost;

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
    bool EffortModel(Player* player, uint8 model, bool Legendary) const;
    void ChargeModelCost(Player* player, uint8 model, bool Legendary) const;

    void DeleteFakeFromDB(uint64 itemGUID, SQLTransaction* trans = NULL);

	void TakeRequiredAmount(Player* player, int32 amount);
    bool GetCustomModelCost() const;
    bool TokenRewardEnabled() const;

    // Token entries
    uint32 GetTokenEntryRDF() const;
    uint32 GetTokenEntryBG() const;
    uint32 GetTokenEntryWG() const;
    uint32 GetTokenEntry2V2() const;
    uint32 GetTokenEntry3V3() const;
    uint32 GetTokenEntryTwink() const;
    uint32 GetTokenEntryExtra1() const;
    uint32 GetTokenEntryExtra2() const;

    // Rewards
    uint32 GetTokenRewardCountRDF() const;
    uint32 GetTokenRewardCountBG() const;
    uint32 GetTokenRewardCount2V2() const;
    uint32 GetTokenRewardCount3V3() const;
    uint32 GetTokenRewardCountTwink() const;

    // Model PvE
    uint32 GetAmountTokenRDF_PvE() const;
    uint32 GetAmountTokenBG_PvE() const;
    uint32 GetAmountTokenWG_PvE() const;
    uint32 GetAmountToken2V2_PvE() const;
    uint32 GetAmountToken3V3_PvE() const;
    uint32 GetAmountTokenORB_PvE() const;
    uint32 GetAmountTokenGEM_PvE() const;
    int32 GetMoneyAmount_PvE() const;

    // Legendary PvE
    uint32 GetLegendaryAmountTokenRDF_PvE() const;
    uint32 GetLegendaryAmountTokenBG_PvE() const;
    uint32 GetLegendaryAmountTokenWG_PvE() const;
    uint32 GetLegendaryAmountToken2V2_PvE() const;
    uint32 GetLegendaryAmountToken3V3_PvE() const;
    uint32 GetLegendaryAmountTokenORB_PvE() const;
    uint32 GetLegendaryAmountTokenGEM_PvE() const;
    int32 GetLegendaryMoneyAmount_PvE() const;

    // Model PvP
    uint32 GetAmountTokenRDF_PvP() const;
    uint32 GetAmountTokenBG_PvP() const;
    uint32 GetAmountTokenWG_PvP() const;
    uint32 GetAmountToken2V2_PvP() const;
    uint32 GetAmountToken3V3_PvP() const;
    uint32 GetAmountTokenORB_PvP() const;
    uint32 GetAmountTokenGEM_PvP() const;
    int32 GetMoneyAmount_PvP() const;

    // Legendary PvP
    uint32 GetLegendaryAmountTokenRDF_PvP() const;
    uint32 GetLegendaryAmountTokenBG_PvP() const;
    uint32 GetLegendaryAmountTokenWG_PvP() const;
    uint32 GetLegendaryAmountToken2V2_PvP() const;
    uint32 GetLegendaryAmountToken3V3_PvP() const;
    uint32 GetLegendaryAmountTokenORB_PvP() const;
    uint32 GetLegendaryAmountTokenGEM_PvP() const;
    int32 GetLegendaryMoneyAmount_PvP() const;

    // Model Mix
    uint32 GetAmountTokenRDF_Mix() const;
    uint32 GetAmountTokenBG_Mix() const;
    uint32 GetAmountTokenWG_Mix() const;
    uint32 GetAmountToken2V2_Mix() const;
    uint32 GetAmountToken3V3_Mix() const;
    uint32 GetAmountTokenORB_Mix() const;
    uint32 GetAmountTokenGEM_Mix() const;
    int32 GetMoneyAmount_Mix() const;

    // Legendary Mix
    uint32 GetLegendaryAmountTokenRDF_Mix() const;
    uint32 GetLegendaryAmountTokenBG_Mix() const;
    uint32 GetLegendaryAmountTokenWG_Mix() const;
    uint32 GetLegendaryAmountToken2V2_Mix() const;
    uint32 GetLegendaryAmountToken3V3_Mix() const;
    uint32 GetLegendaryAmountTokenORB_Mix() const;
    uint32 GetLegendaryAmountTokenGEM_Mix() const;
    int32 GetLegendaryMoneyAmount_Mix() const;

    // Model Twink
    uint32 GetAmountTokenRDF_Twink() const;
    uint32 GetAmountTokenBG_Twink() const;
    uint32 GetAmountTokenWG_Twink() const;
    uint32 GetAmountToken2V2_Twink() const;
    uint32 GetAmountToken3V3_Twink() const;
    uint32 GetAmountTokenTwink_Twink() const;
    uint32 GetAmountTokenORB_Twink() const;
    uint32 GetAmountTokenGEM_Twink() const;
    int32 GetMoneyAmount_Twink() const;

    // Legendary Twink
    uint32 GetLegendaryAmountTokenRDF_Twink() const;
    uint32 GetLegendaryAmountTokenBG_Twink() const;
    uint32 GetLegendaryAmountTokenWG_Twink() const;
    uint32 GetLegendaryAmountToken2V2_Twink() const;
    uint32 GetLegendaryAmountToken3V3_Twink() const;
    uint32 GetLegendaryAmountTokenTwink_Twink() const;
    uint32 GetLegendaryAmountTokenORB_Twink() const;
    uint32 GetLegendaryAmountTokenGEM_Twink() const;
    int32 GetLegendaryMoneyAmount_Twink() const;

    // Model Reset
    uint32 GetResetCoinCost() const;
    int32  GetResetGoldCost() const;

    // Model Remove
    int32 GetRemoveCost() const;
    int32 GetFullRemoveCost() const;

    bool GetAllowMixedArmorTypes() const;
    bool GetAllowMixedWeaponTypes() const;

    // Config
    bool GetEnableTransmogInfo() const;
};
#define sTransmogrification ACE_Singleton<Transmogrification, ACE_Null_Mutex>::instance()

#endif
