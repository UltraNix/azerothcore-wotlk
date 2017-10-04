#ifndef DEF_TRANSMOGRIFICATION_H
#define DEF_TRANSMOGRIFICATION_H

#include <vector>
#include "Define.h"
#include "ScriptPCH.h"
#include "Language.h"
#include "Config.h"

#define PRESETS // comment this line to disable preset feature totally
#define MAX_OPTIONS 25 // do not alter

class Item;
class Player;
class WorldSession;
struct ItemTemplate;

enum TransmogTrinityStrings // Language.h might have same entries, appears when executing SQL, change if needed
{
    LANG_ERR_TRANSMOG_OK = 11100, // change this
    LANG_ERR_TRANSMOG_INVALID_SLOT,
    LANG_ERR_TRANSMOG_INVALID_SRC_ENTRY,
    LANG_ERR_TRANSMOG_MISSING_SRC_ITEM,
    LANG_ERR_TRANSMOG_MISSING_DEST_ITEM,
    LANG_ERR_TRANSMOG_INVALID_ITEMS,
    LANG_ERR_TRANSMOG_NOT_ENOUGH_MONEY,
    LANG_ERR_TRANSMOG_NOT_ENOUGH_TOKENS,

    LANG_ERR_UNTRANSMOG_OK,
    LANG_ERR_UNTRANSMOG_NO_TRANSMOGS,

#ifdef PRESETS
    LANG_PRESET_ERR_INVALID_NAME,
#endif
};

enum TransmogTokens
{
    TOKEN_ENTRY_RDF      = 50000,
    TOKEN_ENTRY_BG       = 50001,
    TOKEN_ENTRY_WG       = 50002,
    TOKEN_ENTRY_2V2      = 50003,
    TOKEN_ENTRY_3V3      = 50003,
    TOKEN_ENTRY_BG_TWINK = 50004,
    CRUSADER_ORB_ENTRY   = 50005,
    EPIC_GEM_ENTRY       = 50006
};

enum TransmogModels
{
    MODEL_PVE = 0, // PvE Model
    MODEL_PVP = 1, // PvP Model
    MODEL_MIX = 2, // Mix Model
    MODEL_TWK = 3  // Twink Model
};

class Transmogrification
{
public:
    typedef std::unordered_map<uint64, uint64> transmogData;
    typedef std::unordered_map<uint64, transmogData> transmogMap;
    transmogMap entryMap; // entryMap[pGUID][iGUID] = entry
    transmogData dataMap; // dataMap[iGUID] = pGUID

#ifdef PRESETS
    bool EnableSetInfo;
    uint32 SetNpcText;

    typedef std::map<uint8, uint32> slotMap;
    typedef std::map<uint8, slotMap> presetData;
    typedef std::unordered_map<uint64, presetData> presetDataMap;
    presetDataMap presetById; // presetById[pGUID][presetID][slot] = entry
    typedef std::map<uint8, std::string> presetIdMap;
    typedef std::unordered_map<uint64, presetIdMap> presetNameMap;
    presetNameMap presetByName; // presetByName[pGUID][presetID] = presetName

    void PresetTransmog(Player* player, Item* itemTransmogrified, uint32 fakeEntry, uint8 slot);

    bool EnableSets;
    uint8 MaxSets;
    float SetCostModifier;
    int32 SetCopperCost;

    bool GetEnableSets() const;
    uint8 GetMaxSets() const;
    float GetSetCostModifier() const;
    int32 GetSetCopperCost() const;

    void LoadPlayerSets(uint64 pGUID);
    void UnloadPlayerSets(uint64 pGUID);
#endif

    bool EnableTransmogInfo;
    uint32 TransmogNpcText;
    uint32 TransmogModelText;

    // Use IsAllowed() and IsNotAllowed()
    // these are thread unsafe, but assumed to be static data so it should be safe
    std::set<uint32> Allowed;
    std::set<uint32> NotAllowed;

    float ScaledCostModifier;
    int32 CopperCost;

    bool RequireToken;
    uint32 TokenEntry;
    uint32 TokenAmount;

    bool CustomModelCost;

    // Model PvE
    uint8 pve_token_rdf;
    uint8 pve_token_bg;
    uint8 pve_token_wg;
    uint8 pve_token_2v2;
    uint8 pve_token_3v3;
    uint8 pve_token_orb;
    uint8 pve_token_gem;
    int32 pve_money_amount;

    uint8 pve_token_rdf_legendary;
    uint8 pve_token_bg_legendary;
    uint8 pve_token_wg_legendary;
    uint8 pve_token_2v2_legendary;
    uint8 pve_token_3v3_legendary;
    uint8 pve_token_orb_legendary;
    uint8 pve_token_gem_legendary;
    int32 pve_money_amount_legendary;

    // Model PvP
    uint8 pvp_token_rdf;
    uint8 pvp_token_bg;
    uint8 pvp_token_wg;
    uint8 pvp_token_2v2;
    uint8 pvp_token_3v3;
    uint8 pvp_token_orb;
    uint8 pvp_token_gem;
    int32 pvp_money_amount;

    uint8 pvp_token_rdf_legendary;
    uint8 pvp_token_bg_legendary;
    uint8 pvp_token_wg_legendary;
    uint8 pvp_token_2v2_legendary;
    uint8 pvp_token_3v3_legendary;
    uint8 pvp_token_orb_legendary;
    uint8 pvp_token_gem_legendary;
    int32 pvp_money_amount_legendary;

    // Model Mix
    uint8 mix_token_rdf;
    uint8 mix_token_bg;
    uint8 mix_token_wg;
    uint8 mix_token_2v2;
    uint8 mix_token_3v3;
    uint8 mix_token_orb;
    uint8 mix_token_gem;
    int32 mix_money_amount;

    uint8 mix_token_rdf_legendary;
    uint8 mix_token_bg_legendary;
    uint8 mix_token_wg_legendary;
    uint8 mix_token_2v2_legendary;
    uint8 mix_token_3v3_legendary;
    uint8 mix_token_orb_legendary;
    uint8 mix_token_gem_legendary;
    int32 mix_money_amount_legendary;

    // Model Twink
    uint8 twink_token_rdf;
    uint8 twink_token_bg;
    uint8 twink_token_wg;
    uint8 twink_token_2v2;
    uint8 twink_token_3v3;
    uint8 twink_token_orb;
    uint8 twink_token_gem;
    int32 twink_money_amount;

    uint8 twink_token_rdf_legendary;
    uint8 twink_token_bg_legendary;
    uint8 twink_token_wg_legendary;
    uint8 twink_token_2v2_legendary;
    uint8 twink_token_3v3_legendary;
    uint8 twink_token_orb_legendary;
    uint8 twink_token_gem_legendary;
    int32 twink_money_amount_legendary;

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
    std::string GetItemLink(Item* item, WorldSession* session) const;
    std::string GetItemLink(uint32 entry, WorldSession* session) const;
    uint32 GetFakeEntry(uint64 itemGUID) const;
    void UpdateItem(Player* player, Item* item) const;
    void DeleteFakeEntry(Player* player, uint8 slot, Item* itemTransmogrified, SQLTransaction* trans = NULL);
    void SetFakeEntry(Player* player, uint32 newEntry, uint8 slot, Item* itemTransmogrified);

    TransmogTrinityStrings Transmogrify(Player* player, uint64 itemGUID, uint8 slot, /*uint32 newEntry, */bool no_cost = false);
    bool CanTransmogrifyItemWithItem(Player* player, ItemTemplate const* destination, ItemTemplate const* source) const;
    bool SuitableForTransmogrification(Player* player, ItemTemplate const* proto) const;
    bool EffortModel(Player* player, uint8 model, bool Legendary) const;
    void ChargeModelCost(Player* player, uint8 model, bool Legendary) const;
    // bool CanBeTransmogrified(Item const* item);
    // bool CanTransmogrify(Item const* item);
    uint32 GetSpecialPrice(ItemTemplate const* proto) const;

    void DeleteFakeFromDB(uint64 itemGUID, SQLTransaction* trans = NULL);
    float GetScaledCostModifier() const;
    int32 GetCopperCost() const;

    bool GetRequireToken() const;
    bool GetCustomModelCost() const;
    
    uint32 GetTokenEntry() const;
    uint32 GetTokenAmount() const;

    // Model PvE
    uint8 GetAmountTokenRDF_PvE() const;
    uint8 GetAmountTokenBG_PvE() const;
    uint8 GetAmountTokenWG_PvE() const;
    uint8 GetAmountToken2V2_PvE() const;
    uint8 GetAmountToken3V3_PvE() const;
    uint8 GetAmountTokenORB_PvE() const;
    uint8 GetAmountTokenGEM_PvE() const;
    int32 GetMoneyAmount_PvE() const;

    // Legendary PvE
    uint8 GetLegendaryAmountTokenRDF_PvE() const;
    uint8 GetLegendaryAmountTokenBG_PvE() const;
    uint8 GetLegendaryAmountTokenWG_PvE() const;
    uint8 GetLegendaryAmountToken2V2_PvE() const;
    uint8 GetLegendaryAmountToken3V3_PvE() const;
    uint8 GetLegendaryAmountTokenORB_PvE() const;
    uint8 GetLegendaryAmountTokenGEM_PvE() const;
    int32 GetLegendaryMoneyAmount_PvE() const;

    // Model PvP
    uint8 GetAmountTokenRDF_PvP() const;
    uint8 GetAmountTokenBG_PvP() const;
    uint8 GetAmountTokenWG_PvP() const;
    uint8 GetAmountToken2V2_PvP() const;
    uint8 GetAmountToken3V3_PvP() const;
    uint8 GetAmountTokenORB_PvP() const;
    uint8 GetAmountTokenGEM_PvP() const;
    int32 GetMoneyAmount_PvP() const;

    // Legendary PvP
    uint8 GetLegendaryAmountTokenRDF_PvP() const;
    uint8 GetLegendaryAmountTokenBG_PvP() const;
    uint8 GetLegendaryAmountTokenWG_PvP() const;
    uint8 GetLegendaryAmountToken2V2_PvP() const;
    uint8 GetLegendaryAmountToken3V3_PvP() const;
    uint8 GetLegendaryAmountTokenORB_PvP() const;
    uint8 GetLegendaryAmountTokenGEM_PvP() const;
    int32 GetLegendaryMoneyAmount_PvP() const;

    // Model Mix
    uint8 GetAmountTokenRDF_Mix() const;
    uint8 GetAmountTokenBG_Mix() const;
    uint8 GetAmountTokenWG_Mix() const;
    uint8 GetAmountToken2V2_Mix() const;
    uint8 GetAmountToken3V3_Mix() const;
    uint8 GetAmountTokenORB_Mix() const;
    uint8 GetAmountTokenGEM_Mix() const;
    int32 GetMoneyAmount_Mix() const;

    // Legendary Mix
    uint8 GetLegendaryAmountTokenRDF_Mix() const;
    uint8 GetLegendaryAmountTokenBG_Mix() const;
    uint8 GetLegendaryAmountTokenWG_Mix() const;
    uint8 GetLegendaryAmountToken2V2_Mix() const;
    uint8 GetLegendaryAmountToken3V3_Mix() const;
    uint8 GetLegendaryAmountTokenORB_Mix() const;
    uint8 GetLegendaryAmountTokenGEM_Mix() const;
    int32 GetLegendaryMoneyAmount_Mix() const;

    // Model Twink
    uint8 GetAmountTokenRDF_Twink() const;
    uint8 GetAmountTokenBG_Twink() const;
    uint8 GetAmountTokenWG_Twink() const;
    uint8 GetAmountToken2V2_Twink() const;
    uint8 GetAmountToken3V3_Twink() const;
    uint8 GetAmountTokenORB_Twink() const;
    uint8 GetAmountTokenGEM_Twink() const;
    int32 GetMoneyAmount_Twink() const;

    // Legendary Mix
    uint8 GetLegendaryAmountTokenRDF_Twink() const;
    uint8 GetLegendaryAmountTokenBG_Twink() const;
    uint8 GetLegendaryAmountTokenWG_Twink() const;
    uint8 GetLegendaryAmountToken2V2_Twink() const;
    uint8 GetLegendaryAmountToken3V3_Twink() const;
    uint8 GetLegendaryAmountTokenORB_Twink() const;
    uint8 GetLegendaryAmountTokenGEM_Twink() const;
    int32 GetLegendaryMoneyAmount_Twink() const;

    bool GetAllowMixedArmorTypes() const;
    bool GetAllowMixedWeaponTypes() const;

    // Config
    bool GetEnableTransmogInfo() const;
    uint32 GetTransmogNpcText() const;
    uint32 GetTransmogModelText() const;
    bool GetEnableSetInfo() const;
    uint32 GetSetNpcText() const;
};
#define sTransmogrification ACE_Singleton<Transmogrification, ACE_Null_Mutex>::instance()

#endif
