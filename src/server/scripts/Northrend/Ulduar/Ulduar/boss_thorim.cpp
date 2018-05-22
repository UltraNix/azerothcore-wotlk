/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "ulduar.h"
#include "ScriptedEscortAI.h"
#include "SpellAuraEffects.h"
#include "PassiveAI.h"
#include "Player.h"
#include "MoveSplineInit.h"

enum ThorimSpells
{
    // THORIM
    SPELL_LIGHTNING_DESTRUCTION                = 62393,
    SPELL_SHEATH_OF_LIGHTNING                  = 62276,
    SPELL_STORMHAMMER                          = 62042,
    SPELL_BERSERK_FRIENDS                      = 62560,
    SPELL_CHAIN_LIGHTNING_10                   = 62131,
    SPELL_CHAIN_LIGHTNING_25                   = 64390,
    SPELL_UNBALANCING_STRIKE                   = 62130,
    SPELL_BERSERK                              = 26662,
    SPELL_DEFEANING_THUNDER                    = 62470,
    SPELL_STORMHAMMER_BACK_TO_THORIM           = 64909,

    SPELL_CHARGE_ORB                           = 62016,
    SPELL_LIGHTNING_PILLAR_P1                  = 63238,

    SPELL_LIGHTNING_ORB_VISUAL                 = 62186,
    SPELL_LIGHTNING_CHARGE_DAMAGE              = 62466,
    SPELL_LIGHTNING_CHARGE_BUFF                = 62279,
    SPELL_LIGHTNING_PILLAR_P2                  = 62976,
    SPELL_LIGHTNING_ORB_CHARGER                = 62278,

    // SIF
    SPELL_TOUCH_OF_DOMINION                    = 62507,
    SPELL_SIF_TRANSFORM                        = 64778,
    SPELL_SIF_CHANNEL_HOLOGRAM                 = 64324,
    SPELL_FROSTBOLT_VOLLEY                     = 62580,
    SPELL_FROSTBOLT_VOLLEY_H                   = 62604,
    SPELL_FROSTNOVA                            = 62597,
    SPELL_FROSTNOVA_H                          = 62605,
    SPELL_FROSTBOLT                            = 62583,
    SPELL_FROSTBOLT_H                          = 62601,
    SPELL_BLIZZARD_10                          = 62577,
    SPELL_BLIZZARD_25                          = 62603,

    // DARK RUNE ACOLYTE
    SPELL_GREATER_HEAL_10                      = 62334,
    SPELL_GREATER_HEAL_25                      = 62442,
    SPELL_HOLY_SMITE_10                        = 62335,
    SPELL_HOLY_SMITE_25                        = 62443,
    SPELL_RENEW_10                             = 62333,
    SPELL_RENEW_25                             = 62441,

    // CAPTURED MERCENARY SOLDIER
    SPELL_BARBED_SHOT                          = 62318,
    SPELL_WING_CLIP                            = 40652,
    SPELL_SHOOT                                = 16496,

    // CAPTURED MERCENARY CAPTAIN
    SPELL_DEVASTATE                            = 62317,
    SPELL_HEROIC_STRIKE                        = 62444,

    // JORMUNGAR BEHEMOTH
    SPELL_ACID_BREATH_10                       = 62315,
    SPELL_ACID_BREATH_25                       = 62415,
    SPELL_SWEEP_10                             = 62316,
    SPELL_SWEEP_25                             = 62417,

    // IRON RING GUARD
    SPELL_IMPALE_10                            = 62331,
    SPELL_IMPALE_25                            = 62418,
    SPELL_WHIRLING_TRIP                        = 64151,

    // IRON HONOR GUARD
    SPELL_SHIELD_SMASH_10                      = 62332,
    SPELL_SHIELD_SMASH_25                      = 62420,
    SPELL_CLEAVE                               = 42724,
    SPELL_HAMSTRING                            = 48639,

    // DARK RUNE WARBRINGER
    SPELL_AURA_OF_CELERITY                     = 62320,
    SPELL_RUNIC_STRIKE                         = 62322,

    // DARK RUNE EVOKER
    SPELL_RUNIC_LIGHTNING_10                   = 62327,
    SPELL_RUNIC_LIGHTNING_25                   = 62445,
    SPELL_RUNIC_MENDING_10                     = 62328,
    SPELL_RUNIC_MENDING_25                     = 62446,
    SPELL_RUNIC_SHIELD_10                      = 62321,
    SPELL_RUNIC_SHIELD_25                      = 62529,

    // DARK RUNE CHAMPION
    SPELL_CHARGE                               = 32323,
    SPELL_MORTAL_STRIKE                        = 35054,
    SPELL_WHIRLWIND                            = 15578,

    // DARK RUNE COMMONER
    SPELL_LOW_BLOW                             = 62326,
    SPELL_PUMMEL                               = 38313,

    // RUNIC COLOSSUS
    SPELL_COLOSSUS_CHARGE_10                   = 62613,
    SPELL_COLOSSUS_CHARGE_25                   = 62614,
    SPELL_RUNIC_BARRIER                        = 62338,
    SPELL_SMASH                                = 62339,
    SPELL_RUNIC_SMASH_LEFT                     = 62057,
    SPELL_RUNIC_SMASH_RIGHT                    = 62058,
    SPELL_RUNIC_SMASH_DAMAGE                   = 62465,

    // ANCIENT RUNE GIANT
    SPELL_RUNE_DETONATION                      = 62526,
    SPELL_RUNIC_FORTIFICATION                  = 62942,
    SPELL_STOMP_10                             = 62411,
    SPELL_STOMP_25                             = 62413,

    // TRAPS
    SPELL_PARALYTIC_FIELD_FIRST                = 62241,
    SPELL_PARALYTIC_FIELD_SECOND               = 63540,

    SPELL_BEAM_VISUAL                          = 45537, // thorim bunnies beam visual
    SPELL_LIGHTNING_FIELD_AURA                 = 64973,
    SPELL_LIGHTNING_FIELD                      = 64972,

    SPELL_STORMHAMMER_SIF                      = 64767
};

enum ThorimDisplayIds
{
    THORIM_WEAPON_DISPLAY_ID = 45900
};

Position const CenterPos = { 2134.897705f, -263.008698f, 419.846619f, 3.418116f };

class HeightPositionCheck
{
public:
    HeightPositionCheck(bool ret) : _ret(ret) { }

    bool operator()(Position const* pos) const
    {
        return (pos->GetPositionZ() > THORIM_BALCONY_Z_CHECK) == _ret;
    }

private:
    bool _ret;

    static float const THORIM_BALCONY_Z_CHECK;
};
float const HeightPositionCheck::THORIM_BALCONY_Z_CHECK = 428.0f;

struct OutOfArenaCheck
{
    bool operator()(Position const* who) const
    {
        return who->GetExactDist(&CenterPos) > 43.0f;
    }
};

class RunicSmashExplosionEvent : public BasicEvent
{
public:
    RunicSmashExplosionEvent(Creature* owner) : _owner(owner) {}

    bool Execute(uint64 /*eventTime*/, uint32 /*updateTime*/) override
    {
        _owner->CastSpell(nullptr, SPELL_RUNIC_SMASH_DAMAGE);
        return true;
    }

private:
    Creature * _owner;
};

#define SPELL_GREATER_HEAL            RAID_MODE(SPELL_GREATER_HEAL_10, SPELL_GREATER_HEAL_25)
#define SPELL_HOLY_SMITE            RAID_MODE(SPELL_HOLY_SMITE_10, SPELL_HOLY_SMITE_25)
#define SPELL_RENEW                    RAID_MODE(SPELL_RENEW_10, SPELL_RENEW_25)
#define SPELL_ACID_BREATH            RAID_MODE(SPELL_ACID_BREATH_10, SPELL_ACID_BREATH_25)
#define SPELL_SWEEP                    RAID_MODE(SPELL_SWEEP_10, SPELL_SWEEP_25)
#define SPELL_IMPALE                RAID_MODE(SPELL_IMPALE_10, SPELL_IMPALE_25)
#define SPELL_COLOSSUS_CHARGE        RAID_MODE(SPELL_COLOSSUS_CHARGE_10, SPELL_COLOSSUS_CHARGE_25)
#define SPELL_STOMP                    RAID_MODE(SPELL_STOMP_10, SPELL_STOMP_25)
#define SPELL_SHIELD_SMASH            RAID_MODE(SPELL_SHIELD_SMASH_10, SPELL_SHIELD_SMASH_25)
#define SPELL_RUNIC_LIGHTNING        RAID_MODE(SPELL_RUNIC_LIGHTNING_10, SPELL_RUNIC_LIGHTNING_25)
#define SPELL_RUNIC_MENDING            RAID_MODE(SPELL_RUNIC_MENDING_10, SPELL_RUNIC_MENDING_25)
#define SPELL_RUNIC_SHIELD            RAID_MODE(SPELL_RUNIC_SHIELD_10, SPELL_RUNIC_SHIELD_25)
#define SPELL_CHAIN_LIGHTNING        RAID_MODE(SPELL_CHAIN_LIGHTNING_10, SPELL_CHAIN_LIGHTNING_25)

enum ThormNPCandGOs
{
    // ARENA INIT
    NPC_DARK_RUNE_ACOLYTE_I                     = 32886,
    NPC_CAPTURED_MERCENARY_SOLDIER_ALLY         = 32885,
    NPC_CAPTURED_MERCENARY_SOLDIER_HORDE        = 32883,
    NPC_CAPTURED_MERCENARY_CAPTAIN_ALLY         = 32908,
    NPC_CAPTURED_MERCENARY_CAPTAIN_HORDE        = 32907,
    NPC_JORMUNGAR_BEHEMOT                       = 32882,

    // ARENA PHASE
    NPC_DARK_RUNE_WARBRINGER                    = 32877,
    NPC_DARK_RUNE_EVOKER                        = 32878,
    NPC_DARK_RUNE_CHAMPION                      = 32876,
    NPC_DARK_RUNE_COMMONER                      = 32904,

    // GAUNTLET
    NPC_IRON_RING_GUARD                         = 32874,
    NPC_RUNIC_COLOSSUS                          = 32872,
    NPC_ANCIENT_RUNE_GIANT                      = 32873,
    NPC_DARK_RUNE_ACOLYTE_G                     = 33110,
    NPC_IRON_HONOR_GUARD                        = 32875,

    // TRIGGERS
    NPC_LIGHTNING_ORB                           = 33138,
    NPC_THUNDER_ORB                             = 33378,
    NPC_PILLAR                                  = 32892,

    NPC_SIF                                     = 33196,
    NPC_GOLEM_RIGHT_HAND_BUNNY                  = 33140,
    NPC_GOLEM_LEFT_HAND_BUNNY                   = 33141
};

enum ThorimEvents
{
    EVENT_THORIM_START_PHASE1                   = 1,
    EVENT_THORIM_STORMHAMMER                    = 2,
    EVENT_THORIM_CHARGE_ORB                     = 3,
    EVENT_THORIM_LIGHTNING_ORB                  = 4,
    EVENT_THORIM_NOT_REACH_IN_TIME              = 5,
    EVENT_THORIM_FILL_ARENA                     = 6,
    EVENT_THORIM_UNBALANCING_STRIKE             = 7,
    EVENT_THORIM_LIGHTNING_CHARGE               = 8,
    EVENT_THORIM_CHAIN_LIGHTNING                = 9,
    EVENT_THORIM_BERSERK                        = 10,
    EVENT_THORIM_AGGRO                          = 11,
    EVENT_THORIM_AGGRO2                         = 12,
    EVENT_THORIM_OUTRO1                         = 13,
    EVENT_THORIM_OUTRO2                         = 14,
    EVENT_THORIM_OUTRO3                         = 15,

    EVENT_DR_ACOLYTE_GH                         = 20,
    EVENT_DR_ACOLYTE_HS                         = 21,
    EVENT_DR_ACOLYTE_R                          = 22,

    EVENT_CM_SOLDIER_BS                         = 30,
    EVENT_CM_SOLDIER_S                          = 31,
    EVENT_CM_SOLDIER_WC                         = 32,

    EVENT_CM_CAPTAIN_D                          = 40,
    EVENT_CM_CAPTAIN_HC                         = 41,

    EVENT_JB_ACID_BREATH                        = 50,
    EVENT_JB_SWEEP                              = 51,

    EVENT_IR_GUARD_IMPALE                       = 60,
    EVENT_IR_GUARD_WHIRL                        = 61,

    EVENT_RC_RUNIC_BARRIER                      = 70,
    EVENT_RC_SMASH                              = 71,
    EVENT_RC_RUNIC_SMASH                        = 72,
    EVENT_RC_RUNIC_SMASH_TRIGGER                = 73,
    EVENT_RC_CHARGE                             = 74,

    EVENT_ARG_RD                                = 80,
    EVENT_ARG_RF                                = 81,
    EVENT_ARG_STOMP                             = 82,
    EVENT_ARG_SPAWN                             = 83,

    EVENT_IH_GUARD_CLEAVE                       = 90,
    EVENT_IH_GUARD_HAMSTRING                    = 91,
    EVENT_IH_GUARD_SHIELD_SMASH                 = 92,

    EVENT_SIF_START_TALK                        = 100,
    EVENT_SIF_JOIN_TALK                         = 101,
    EVENT_SIF_FINISH_DOMINION                   = 102,
    EVENT_SIF_FROSTBOLT_VALLEY                  = 103,
    EVENT_SIF_BLIZZARD                          = 104,
    EVENT_SIF_FROST_NOVA_START                  = 105,
    EVENT_SIF_FROST_NOVA_CAST                   = 106,
    EVENT_SIF_FROSTBOLT                         = 107,

    EVENT_DR_WARBRINGER_RS                      = 110,

    EVENT_DR_EVOKER_RL                          = 120,
    EVENT_DR_EVOKER_RM                          = 121,
    EVENT_DR_EVOKER_RS                          = 122,

    EVENT_DR_CHAMPION_WH                        = 130,
    EVENT_DR_CHAMPION_CH                        = 131,
    EVENT_DR_CHAMPION_MS                        = 132,

    EVENT_DR_COMMONER_PM                        = 140,
    EVENT_DR_COMMONER_LB                        = 141,

    EVENT_PROTECT_THE_PLATFORM                  = 142,
    EVENT_RESET_POST_LIGHTNING_CHARGE           = 143
};

const Position ArenaNPCs[] =
{
    {2178.5f,  -300.2f,  441.97f, 2.5f},
    {2188.12f, -295.1f,  443.75,  2.5f},
    {2180.9f,  -286.8f,  433.3f,  2.49f},
    {2193.2f,  -280.6f,  443.14f, 2.79f},
    {2191.8f,  -270.2f,  438.3f,  3.0f},
    {2186.84f, -238.5f,  439.7f,  3.4f},
    {2166.3f,  -213.0f,  440.0f,  4.1f},
    {2100.5f,  -213.5f,  441.66f, 5.4f},
    {2091.0f,  -231.26f, 435.17f, 5.5f},
    {2083.2f,  -239.2f,  438.77f, 5.85f},
    {2081.54f, -253.27f, 434.67f, 6.19f},
    {2077.65f, -272.73f, 439.12f, 0.15f},
    {2084.36f, -282.12f, 435.87f, 0.24f},
    {2087.46f, -298.71f, 440.5f,  0.59f}
};

enum ThorimSounds
{
    SOUND_AGGRO1                    = 15733,
    SOUND_AGGRO2                    = 15734,
    SOUND_SPECIAL1                  = 15735,
    SOUND_SPECIAL2                  = 15736,
    SOUND_SPECIAL3                  = 15737,
    SOUND_JUMPDOWN                  = 15738,
    SOUND_SLAY1                     = 15739,
    SOUND_SLAY2                     = 15740,
    SOUND_BERSERK                   = 15741,
    SOUND_AWIPE                     = 15742,
    SOUND_DEFEATED                  = 15743,
    SOUND_NORM1                     = 15744,
    SOUND_NORM2                     = 15745,
    SOUND_NORM3                     = 15746,
    SOUND_HARD1                     = 15747,
    SOUND_HARD2                     = 15748,
    SOUND_HARD3                     = 15749,

    SOUND_SIF_START                 = 15668,
    SOUND_SIF_DESPAWN               = 15669,
    SOUND_SIF_EVENT                 = 15670
};

enum Misc
{
    ACTION_START_TRASH_DIED         = 1,
    ACTION_ALLOW_HIT                = 2,
    ACTION_SIF_JOIN_FIGHT           = 3,
    ACTION_SIF_START_TALK           = 4,
    ACTION_SIF_START_DOMINION       = 5,
    ACTION_SIF_TRANSFORM            = 6,
    ACTION_IRON_HONOR_DIED          = 7,

    EVENT_PHASE_START               = 1,
    EVENT_PHASE_RING                = 2,
    EVENT_PHASE_OUTRO               = 3,

    DATA_HIT_BY_LIGHTNING           = 1,
    DATA_LOSE_YOUR_ILLUSION         = 2,

    DATA_INFORM_PRE_COMBAT_SUMMONS  = 3
};

const Position Middle = {2134.68f, -263.13f, 419.44f};

const uint32 RollTable[3] = { 32877, 32878, 32876 };

uint32 const orbsArcSize = 6;
Position const orbsArcPositions[orbsArcSize] =
{
    { 2164.36f, -299.721f, 440.061f, 1.69570f }, // 1
    { 2155.11f, -291.608f, 440.110f, 1.38940f }, // 2
    { 2142.04f, -286.111f, 440.117f, 1.29121f }, // 3
    { 2128.06f, -286.153f, 440.118f, 1.83707f }, // 4
    { 2115.31f, -290.850f, 439.973f, 1.49542f }, // 5
    { 2105.33f, -300.063f, 441.116f, 1.32656f } // 6
};

uint32 const platformProtectorsSize = 7;
Position const platformProtectorsPositions[platformProtectorsSize] =
{
    { 2130.08f, -298.506f, 438.248f, 1.53782f },
    { 2121.38f, -304.514f, 438.248f, 1.53782f },
    { 2134.89f, -297.546f, 438.248f, 1.53782f },
    { 2139.67f, -298.940f, 438.248f, 1.53782f },
    { 2147.50f, -304.214f, 438.248f, 1.53782f },
    { 2150.75f, -298.838f, 438.248f, 1.39174f },
    { 2122.15f, -297.791f, 438.248f, 1.55275f }
};

class boss_thorim : public CreatureScript
{
public:
    boss_thorim() : CreatureScript("boss_thorim") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thorimAI (pCreature);
    }

    struct boss_thorimAI : public ScriptedAI
    {
        boss_thorimAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me)
        {
            m_pInstance = pCreature->GetInstanceScript();
            if (_encounterFinished = (!me->IsAlive()))
                if (m_pInstance)
                    m_pInstance->SetData(TYPE_THORIM, DONE);
        }

        bool _isArenaEmpty;
        bool _encounterFinished;
        bool _spawnCommoners;
        bool _hardMode;
        bool _isHitAllowed;
        bool _isAfertHitFromPlayer;
        bool _isAlly;
        bool _summonsInformed;
        uint8 _trashCounter;

        InstanceScript* m_pInstance;
        EventMap events;
        SummonList summons;

        bool _hitByLightning;
        uint32 _fightTimer;

        void DisableThorim(bool apply)
        {
            if (apply)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_PACIFIED);
                me->DisableRotate(true);
                me->AddUnitState(UNIT_STATE_ROOT);
            }
            else
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_PACIFIED);
                me->DisableRotate(false);
                me->ClearUnitState(UNIT_STATE_ROOT);
                me->resetAttackTimer(BASE_ATTACK);
            }
        }

        void SetData(uint32 type, uint32 value) override
        {
            if (type == DATA_INFORM_PRE_COMBAT_SUMMONS && value == DATA_INFORM_PRE_COMBAT_SUMMONS && !_summonsInformed)
            {
                _summonsInformed = true;
                for (auto& summoned : summons)
                {
                    if (Creature* arenaSummon = ObjectAccessor::GetCreature(*me, summoned))
                    {
                        switch (arenaSummon->GetEntry())
                        {
                            case NPC_CAPTURED_MERCENARY_SOLDIER_ALLY:
                            case NPC_CAPTURED_MERCENARY_SOLDIER_HORDE:
                            case NPC_JORMUNGAR_BEHEMOT:
                            case NPC_CAPTURED_MERCENARY_CAPTAIN_ALLY:
                            case NPC_CAPTURED_MERCENARY_CAPTAIN_HORDE:
                            case NPC_DARK_RUNE_ACOLYTE_I:
                            {
                                arenaSummon->getThreatManager().resetAllAggro();
                                if (arenaSummon->IsAIEnabled)
                                {
                                    if (arenaSummon->GetEntry() == NPC_JORMUNGAR_BEHEMOT)
                                        arenaSummon->setFaction(1692); // make him friendly to NPCs
                                    arenaSummon->CastStop();
                                    if (Player* player = arenaSummon->SelectNearestPlayer(50.0f))
                                    {
                                        arenaSummon->AddThreat(player, 1000.f);
                                        arenaSummon->AI()->AttackStart(player);
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }

        GameObject* GetThorimObject(uint32 entry)
        {
            if (m_pInstance)
                return ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(entry));
            return NULL;
        }

        void JustSummoned(Creature* cr) { summons.Summon(cr); }

        void SpawnAllNPCs()
        {
            // Jormungar Behemoth 32882
            me->SummonCreature(NPC_JORMUNGAR_BEHEMOT, 2149.68f, -263.477f, 419.679f, 3.12102f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

            // Captured Mercenary Soldier 32885
            me->SummonCreature(_isAlly ? NPC_CAPTURED_MERCENARY_SOLDIER_ALLY : NPC_CAPTURED_MERCENARY_SOLDIER_HORDE, 2127.24f, -251.309f, 419.793f, 5.89921f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);
            me->SummonCreature(_isAlly ? NPC_CAPTURED_MERCENARY_SOLDIER_ALLY : NPC_CAPTURED_MERCENARY_SOLDIER_HORDE, 2120.1f, -258.99f, 419.764f, 6.24828f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);
            me->SummonCreature(_isAlly ? NPC_CAPTURED_MERCENARY_SOLDIER_ALLY : NPC_CAPTURED_MERCENARY_SOLDIER_HORDE, 2123.32f, -254.771f, 419.789f, 6.17846f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

            // Captured Mercenary Captain 32908
            me->SummonCreature(_isAlly ? NPC_CAPTURED_MERCENARY_CAPTAIN_ALLY : NPC_CAPTURED_MERCENARY_CAPTAIN_HORDE, 2131.31f, -259.182f, 419.974f, 5.91667f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

            // Dark Rune Acolyte (arena) 32886
            me->SummonCreature(NPC_DARK_RUNE_ACOLYTE_I, 2129.09f, -277.142f, 419.756f, 1.22173f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

            // Iron Ring Guard 32874
            me->SummonCreature(NPC_IRON_RING_GUARD, 2217.69f, -337.394f, 412.177f, 1.23918f);
            me->SummonCreature(NPC_IRON_RING_GUARD, 2218.38f, -297.505f, 412.176f, 1.02974f);
            me->SummonCreature(NPC_IRON_RING_GUARD, 2235.26f, -338.345f, 412.134f, 1.58979f);
            me->SummonCreature(NPC_IRON_RING_GUARD, 2235.07f, -297.985f, 412.134f, 1.61336f);
            me->SummonCreature(NPC_IRON_RING_GUARD, 2165.515869f, -435.509003f, 438.245911f, 0.282268f);

            // Dark Rune Acolyte (gauntlet) 33110
            me->SummonCreature(NPC_DARK_RUNE_ACOLYTE_G, 2198.29f, -436.92f, 419.985f, 0.261799f);
            me->SummonCreature(NPC_DARK_RUNE_ACOLYTE_G, 2227.58f, -308.303f, 412.134f, 1.59372f);
            me->SummonCreature(NPC_DARK_RUNE_ACOLYTE_G, 2227.47f, -345.375f, 412.134f, 1.56622f);
            me->SummonCreature(NPC_DARK_RUNE_ACOLYTE_G, 2168.105713f, -445.899750f, 438.245911f, 0.246925f);
            me->SummonCreature(NPC_DARK_RUNE_ACOLYTE_G, 2231.024414f, -436.539551f, 412.177307f, 1.702249f);

            // Iron Honor Guard 32875
            me->SummonCreature(NPC_IRON_HONOR_GUARD, 2198.05f, -428.769f, 419.985f, 6.05629f);
            me->SummonCreature(NPC_IRON_HONOR_GUARD, 2220.31f, -436.22f, 412.26f, 1.06465f);

            // Runic Colossus 32872
            me->SummonCreature(NPC_RUNIC_COLOSSUS, 2227.5f, -396.179f, 412.176f, 1.79769f);

            // Ancient Rune Giant 32873
            me->SummonCreature(NPC_ANCIENT_RUNE_GIANT, 2134.57f, -440.318f, 438.331f, 0.226893f);

            // Sif 33196
            me->SummonCreature(NPC_SIF, 2147.86f, -301.2f, 438.246f, 2.488f);
        }

        void CloseDoors()
        {
            GameObject* go;
            if (go = GetThorimObject(DATA_THORIM_LEVER))
            {
                go->SetUInt32Value(GAMEOBJECT_FLAGS, 48);
                go->SetGoState(GO_STATE_READY);
            }
            if (go = GetThorimObject(DATA_THORIM_FIRST_DOORS))
                go->SetGoState(GO_STATE_READY);

            if (go = GetThorimObject(DATA_THORIM_SECOND_DOORS))
                go->SetGoState(GO_STATE_READY);

            if (go = GetThorimObject(DATA_THORIM_FENCE))
                go->SetGoState(GO_STATE_ACTIVE);
        }

        void EnterEvadeMode()
        {
            DisableThorim(false);
            CreatureAI::EnterEvadeMode();
        }

        void Reset()
        {
            if (m_pInstance && !_encounterFinished)
                m_pInstance->SetData(TYPE_THORIM, NOT_STARTED);

            _fightTimer = 0;
            events.Reset();
            me->SetReactState(REACT_AGGRESSIVE);
            events.SetPhase(0);
            summons.DespawnAll();
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, THORIM_WEAPON_DISPLAY_ID);
            _trashCounter = 0;
            _isAlly = true;
            _isHitAllowed = false;
            _isAfertHitFromPlayer = false;
            _spawnCommoners = false;
            _hardMode = false;
            _isArenaEmpty = false;
            _hitByLightning = false;
            _summonsInformed = false;

            if (Player *t = SelectTargetFromPlayerList(1000))
                if (t->GetTeamId() == TEAM_HORDE)
                    _isAlly = false;

            SpawnAllNPCs();

            CloseDoors();
            DisableThorim(false);

            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_PERIODIC_MANA_LEECH, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_POWER_BURN, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_POWER_BURN, true);
        }

        uint32 GetData(uint32 param) const
        {
            if (param == DATA_HIT_BY_LIGHTNING)
                return !_hitByLightning;
            if (param == DATA_LOSE_YOUR_ILLUSION)
                return _hardMode;

            return 0;
        }

        void DoAction(int32 param)
        {
            if (param == ACTION_START_TRASH_DIED)
            {
                _trashCounter++;
                // activate levar
                if (_trashCounter >= 6)
                {
                    if (GameObject* go = GetThorimObject(DATA_THORIM_LEVER))
                        go->RemoveFlag(GAMEOBJECT_FLAGS, 48);

                    events.SetPhase(EVENT_PHASE_START);
                    events.ScheduleEvent(EVENT_THORIM_AGGRO, 0, 0, EVENT_PHASE_START);
                    events.ScheduleEvent(EVENT_THORIM_START_PHASE1, 20000, 0, EVENT_PHASE_START);
                    _trashCounter = 0;
                }
            }
            else if (param == ACTION_ALLOW_HIT)
                _isHitAllowed = true;
        }

        void KilledUnit(Unit*)
        {
            if (urand(0,2))
                return;

            if (urand(0,1))
            {
                me->MonsterYell("Can't you at least put up a fight!?", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_SLAY1);
            }
            else
            {
                me->MonsterYell("Pathetic!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_SLAY2);
            }
        }

        void JustReachedHome() { me->setActive(false); }

        void EnterCombat(Unit*)
        {
            _fightTimer = getMSTime();
            if (m_pInstance && !_encounterFinished)
                m_pInstance->SetData(TYPE_THORIM, IN_PROGRESS);
            me->setActive(true);
            DisableThorim(true);
            me->CastSpell(me, SPELL_SHEATH_OF_LIGHTNING, true);
            //me->CastSpell(me, SPELL_TOUCH_OF_DOMINION, true);
        }

        void DamageTaken(Unit* who, uint32& damage, DamageEffectType, SpellSchoolMask)
        {
            if (who && _isHitAllowed && who->GetPositionZ() > 430 && who->GetTypeId() == TYPEID_PLAYER)
            {
                _isHitAllowed = false;
                _isAfertHitFromPlayer = true;
                DisableThorim(false);

                events.SetPhase(EVENT_PHASE_RING);
                events.ScheduleEvent(EVENT_THORIM_UNBALANCING_STRIKE, 8000, 0, EVENT_PHASE_RING);
                events.ScheduleEvent(EVENT_THORIM_LIGHTNING_CHARGE, 12500, 0, EVENT_PHASE_RING);
                events.ScheduleEvent(EVENT_THORIM_CHAIN_LIGHTNING, 13000, 0, EVENT_PHASE_RING);
                events.ScheduleEvent(EVENT_THORIM_BERSERK, 300000, 0, EVENT_PHASE_RING);

                me->GetMotionMaster()->MoveChase(me->GetVictim());
                me->GetMotionMaster()->MoveJump(Middle.GetPositionX(), Middle.GetPositionY(), Middle.GetPositionZ(), 20, 20);
                events.ScheduleEvent(EVENT_PROTECT_THE_PLATFORM, 10s);
                me->RemoveAura(SPELL_SHEATH_OF_LIGHTNING);

                me->MonsterYell("Impertinent whelps! You dare challenge me atop my pedestal! I will crush you myself!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_JUMPDOWN);

                // Hard Mode
                if (!me->HasAura(62565 /*TOUCH OF DOMINION TRIGGER*/))
                {
                    if (m_pInstance)
                        m_pInstance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, 64980 /*SIFFED ACHIEVEMENT*/);

                    _hardMode = true;
                    EntryCheckPredicate pred(NPC_SIF);
                    summons.DoAction(ACTION_SIF_JOIN_FIGHT, pred);
                }

                DoResetThreat();
                if (Player* player = GetArenaPlayer())
                    me->AddThreat(player, 1000.0f);
            }

            if (damage >= me->GetHealth())
            {
                damage = 0;
                if (!_encounterFinished)
                {
                    _encounterFinished = true;
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->setFaction(35);
                    me->SetHealth(me->GetMaxHealth());
                    me->CombatStop();
                    me->RemoveAllAuras();
                    for (auto& summon : summons)
                        if (Creature* summonedCreature = ObjectAccessor::GetCreature(*me, summon))
                            if (summonedCreature->GetEntry() != NPC_SIF)
                                summonedCreature->DespawnOrUnsummon();

                    events.Reset();
                    DisableThorim(true);

                    me->MonsterYell("Stay your arms! I yield!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_DEFEATED);

                    events.SetPhase(EVENT_PHASE_OUTRO);
                    events.ScheduleEvent(EVENT_THORIM_OUTRO1, 2000, 0, EVENT_PHASE_OUTRO);

                    GameObject* go = NULL;
                    if (go = GetThorimObject(DATA_THORIM_FENCE))
                        go->SetGoState(GO_STATE_ACTIVE);

                    uint32 chestId = me->GetMap()->Is25ManRaid() ? GO_THORIM_CHEST_HERO : GO_THORIM_CHEST;
                    if (_hardMode)
                        chestId += 1; // hard mode offset

                    if (go = me->GetMap()->SummonGameObject(chestId, 2134.73f, -286.32f, 419.51f, 1.67f, 0, 0, 0, 0, 0))
                    {
                        go->SetSpellId(1);
                        go->SetUInt32Value(GAMEOBJECT_FLAGS, 0);
                    }

                    if (Map* map = me->GetMap())
                        CheckCreatureRecord(me->SelectNearestPlayer(150.0f), me->GetCreatureTemplate()->Entry + _hardMode, Difficulty(map->GetDifficulty() + _hardMode * 2), "", 15000, _fightTimer);

                    // Defeat credit
                    if (m_pInstance)
                    {
                        if (_hardMode)
                            m_pInstance->SetData(DATA_THORIM_HARDMODE, DATA_THORIM_HARDMODE);
                        me->CastSpell(me, 64985, true); // credit
                        m_pInstance->SetData(TYPE_THORIM, DONE);
                    }
                }
            }
        }

        void SpawnArenaNPCs()
        {
            Creature* cr;
            uint8 rnd;
            if (_spawnCommoners || urand(0,2))
                _spawnCommoners = !_spawnCommoners;

            for (uint8 i = 0; i < (_spawnCommoners ? 7 : 2); ++i)
            {
                rnd = urand(0, 13);
                if (cr = me->SummonCreature((_spawnCommoners ? NPC_DARK_RUNE_COMMONER : RollTable[urand(0,2)]), ArenaNPCs[rnd], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
                    cr->GetMotionMaster()->MoveJump(
                        Middle.GetPositionX()+urand(19,24)*cos(Middle.GetAngle(cr)),
                        Middle.GetPositionY()+urand(19,24)*sin(Middle.GetAngle(cr)),
                        Middle.GetPositionZ(), 20, 20);
            }
        }

        void SpellHit(Unit* caster, const SpellInfo* spellInfo)
        {
            if (spellInfo->Id == SPELL_LIGHTNING_ORB_CHARGER && _isAfertHitFromPlayer && !_encounterFinished)
            {
                me->GetMotionMaster()->Clear();
                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
                me->SetOrientation(me->GetAngle(caster));
                me->SetFacingToObject(caster);
                me->CastSpell(caster, SPELL_LIGHTNING_CHARGE_DAMAGE);
                me->CastSpell(me, SPELL_LIGHTNING_CHARGE_BUFF, true);
                events.RescheduleEvent(EVENT_THORIM_LIGHTNING_CHARGE, 10000, 0, EVENT_PHASE_RING);
            }
        }

        void SpellHitTarget(Unit* target, const SpellInfo* spellInfo)
        {
            if (spellInfo->Id == SPELL_LIGHTNING_CHARGE_DAMAGE)
            {
                if (target->GetTypeId() == TYPEID_PLAYER)
                    _hitByLightning = true;

                events.ScheduleEvent(EVENT_RESET_POST_LIGHTNING_CHARGE, 1s, 0, EVENT_PHASE_RING);
            }
        }

        void PlaySpecial()
        {
            if (urand(0,9))
                return;

            switch (urand(0,2))
            {
                case 0:
                    me->MonsterYell("Behold the power of the storms and despair!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_SPECIAL1);
                    break;
                case 1:
                    me->MonsterYell("Do not hold back! Destroy them!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_SPECIAL2);
                    break;
                case 2:
                    me->MonsterYell("Have you begun to regret your intrusion? ", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_SPECIAL3);
                    break;
            }
        }

        Player* GetArenaPlayer()
        {
            Map::PlayerList const& pList = me->GetMap()->GetPlayers();
            for(Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
                if (Player *p = itr->GetSource())
                    if (p->GetPositionX() > 2085 && p->GetPositionX() < 2185 && p->GetPositionY() < -214 && p->GetPositionY() > -305 && p->IsAlive() && p->GetPositionZ() < 425)
                        return p;
            return NULL;
        }

        void UpdateAI(uint32 diff)
        {
            if (!_encounterFinished && !UpdateVictim())
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_RESET_POST_LIGHTNING_CHARGE:
                    me->SetReactState(REACT_AGGRESSIVE);
                    if (me->GetVictim())
                        AttackStart(me->GetVictim());
                    events.PopEvent();
                    break;
                case EVENT_THORIM_AGGRO:
                    me->MonsterYell("Interlopers! You mortals who dare to interfere with my sport will pay... Wait--you...", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_AGGRO1);
                    events.ScheduleEvent(EVENT_THORIM_AGGRO2, 8000, 0, EVENT_PHASE_START);
                    events.PopEvent();

                    if (GameObject* go = GetThorimObject(DATA_THORIM_FENCE))
                        go->SetGoState(GO_STATE_READY);

                    break;
                case EVENT_THORIM_AGGRO2:
                {
                    me->MonsterYell("I remember you... In the mountains... But you... what is this? Where am--", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_AGGRO2);
                    events.PopEvent();

                    EntryCheckPredicate pred(NPC_SIF);
                    summons.DoAction(ACTION_SIF_START_TALK, pred);
                    break;
                }
                case EVENT_THORIM_START_PHASE1:
                {
                    events.PopEvent();
                    events.ScheduleEvent(EVENT_THORIM_STORMHAMMER, 8000, 0, EVENT_PHASE_START);
                    events.ScheduleEvent(EVENT_THORIM_CHARGE_ORB, 14000, 0, EVENT_PHASE_START);
                    events.ScheduleEvent(EVENT_THORIM_FILL_ARENA, 0, 0, EVENT_PHASE_START);
                    events.ScheduleEvent(EVENT_THORIM_LIGHTNING_ORB, 5000, 0, EVENT_PHASE_START); // checked every 5 secs if there are players on arena
                    events.ScheduleEvent(EVENT_THORIM_NOT_REACH_IN_TIME, 300000, 0, EVENT_PHASE_START);

                    EntryCheckPredicate pred(NPC_SIF);
                    summons.DoAction(ACTION_SIF_START_DOMINION, pred);
                    break;
                }
                case EVENT_THORIM_STORMHAMMER:
                    me->CastCustomSpell(SPELL_STORMHAMMER, SPELLVALUE_MAX_TARGETS, 1, me->GetVictim(), false);
                    events.RepeatEvent(16000);
                    PlaySpecial();
                    break;
                case EVENT_THORIM_CHARGE_ORB:
                    me->CastCustomSpell(SPELL_CHARGE_ORB, SPELLVALUE_MAX_TARGETS, 1, me, false);
                    events.RepeatEvent(16000);
                    PlaySpecial();
                    break;
                case EVENT_THORIM_LIGHTNING_ORB:
                {
                    if (GetArenaPlayer())
                    {
                        // Player found, repeat and return
                        events.RepeatEvent(5000);
                        return;
                    }

                    // No players found
                    me->MonsterYell("Failures! Weaklings!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_AWIPE);
                    me->SummonCreature(NPC_LIGHTNING_ORB, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());

                    _isArenaEmpty = true;
                    events.PopEvent();
                    events.CancelEvent(EVENT_THORIM_NOT_REACH_IN_TIME);
                    break;
                }
                case EVENT_THORIM_NOT_REACH_IN_TIME:
                    _isArenaEmpty = true;
                    events.PopEvent();
                    events.CancelEvent(EVENT_THORIM_LIGHTNING_ORB);
                    me->CastSpell(me, SPELL_BERSERK_FRIENDS, true);
                    me->SummonCreature(NPC_LIGHTNING_ORB, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                    break;
                case EVENT_THORIM_FILL_ARENA:
                    SpawnArenaNPCs();
                    events.RepeatEvent(10000);
                    PlaySpecial();
                    break;
                case EVENT_THORIM_UNBALANCING_STRIKE:
                    me->CastSpell(me->GetVictim(), SPELL_UNBALANCING_STRIKE, false);
                    events.RepeatEvent(20000);
                    break;
                case EVENT_THORIM_LIGHTNING_CHARGE:
                    me->CastSpell(me, SPELL_LIGHTNING_PILLAR_P2, true);
                    events.PopEvent();
                    break;
                case EVENT_THORIM_CHAIN_LIGHTNING:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                        me->CastSpell(target, SPELL_CHAIN_LIGHTNING, false);
                    events.RepeatEvent(15000);
                    break;
                case EVENT_THORIM_BERSERK:
                    me->CastSpell(me, SPELL_BERSERK, true);
                    events.PopEvent();
                    me->MonsterYell("My patience has reached its limit!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_BERSERK);
                    break;
                case EVENT_THORIM_OUTRO1:
                    events.PopEvent();
                    if (_hardMode)
                    {
                        me->MonsterYell("You! Fiend! You are not my beloved! Be gone!", LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(SOUND_HARD1);
                        events.ScheduleEvent(EVENT_THORIM_OUTRO2, 5000, 0, 3);
                        DoCastAOE(SPELL_STORMHAMMER_SIF, true);
                    }
                    else
                    {
                        me->MonsterYell("I feel as though I am awakening from a nightmare, but the shadows in this place yet linger.", LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(SOUND_NORM1);
                        events.ScheduleEvent(EVENT_THORIM_OUTRO2, 9000, 0, 3);
                    }
                    break;
                case EVENT_THORIM_OUTRO2:
                    events.PopEvent();
                    if (_hardMode)
                    {
                        me->MonsterYell("Behold the hand behind all the evil that has befallen Ulduar! Left my kingdom in ruins, corrupted my brother and slain my wife!", LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(SOUND_HARD2);
                        events.ScheduleEvent(EVENT_THORIM_OUTRO3, 12000, 0, 3);
                    }
                    else
                    {
                        me->MonsterYell("Sif... was Sif here? Impossible--she died by my brother's hand. A dark nightmare indeed....", LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(SOUND_NORM2);
                        events.ScheduleEvent(EVENT_THORIM_OUTRO3, 10000, 0, 3);
                    }
                    break;
                case EVENT_THORIM_OUTRO3:
                    events.PopEvent();
                    if (_hardMode)
                    {
                        me->MonsterYell("And now it falls to you, champions, to avenge us all! The task before you is great, but I will lend you my aid as I am able. You must prevail!", LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(SOUND_HARD3);
                    }
                    else
                    {
                        me->MonsterYell("I need time to reflect.... I will aid your cause if you should require it. I owe you at least that much. Farewell.", LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(SOUND_NORM3);
                    }

                    // Defeat credit
                    if (m_pInstance)
                        m_pInstance->SetData(TYPE_THORIM, DONE);

                    me->DespawnOrUnsummon(8000);
                    break;
                case EVENT_PROTECT_THE_PLATFORM:
                {
                    std::vector<uint64> _tempArcGUIDs;
                    for (auto i = 0; i < orbsArcSize; ++i)
                    {
                        if (Creature* eventBunny = me->SummonCreature(NPC_PILLAR, orbsArcPositions[i]))
                        {
                            eventBunny->SetDisplayId(11686);
                            _tempArcGUIDs.push_back(eventBunny->GetGUID());
                        }
                    }

                    for (auto i = 0; i < _tempArcGUIDs.size() - 1; ++i)
                    {
                        if (Creature* bunny = ObjectAccessor::GetCreature(*me, _tempArcGUIDs.at(i)))
                        {
                            if (Creature* nextBunny = ObjectAccessor::GetCreature(*me, _tempArcGUIDs.at(i + 1)))
                                bunny->CastSpell(nextBunny, SPELL_BEAM_VISUAL, true);
                        }
                    }

                    for (auto i = 0; i < platformProtectorsSize; ++i)
                    {
                        if (Creature* protectorBunny = me->SummonCreature(NPC_PILLAR, platformProtectorsPositions[i]))
                            protectorBunny->CastSpell(protectorBunny, SPELL_LIGHTNING_FIELD_AURA, true);
                    }
                    events.PopEvent();
                    break;
                }
            }

            if (!_encounterFinished)
                DoMeleeAttackIfReady();
        }
    };
};

class boss_thorim_sif : public CreatureScript
{
public:
    boss_thorim_sif() : CreatureScript("boss_thorim_sif") { }

    struct boss_thorim_sifAI : public ScriptedAI
    {
        boss_thorim_sifAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit*) {}

        bool _allowCast;
        EventMap events;

        void Reset()
        {
            events.Reset();
            me->SetReactState(REACT_PASSIVE);
            _allowCast = false;
        }

        void DoAction(int32 param)
        {
            if (param == ACTION_SIF_START_TALK)
                events.ScheduleEvent(EVENT_SIF_START_TALK, 8000);
            else if (param == ACTION_SIF_START_DOMINION)
            {
                if (me->GetInstanceScript())
                    if (Creature* cr = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_THORIM)))
                        me->CastSpell(cr, SPELL_TOUCH_OF_DOMINION, false);

                events.ScheduleEvent(EVENT_SIF_FINISH_DOMINION, 150000);
            }
            else if (param == ACTION_SIF_JOIN_FIGHT)
            {
                me->InterruptNonMeleeSpells(false);
                events.ScheduleEvent(EVENT_SIF_JOIN_TALK, 9000);
                events.CancelEvent(EVENT_SIF_START_TALK);
                events.CancelEvent(EVENT_SIF_FINISH_DOMINION);
            }
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spellInfo) override
        {
            if (spellInfo->Id == SPELL_STORMHAMMER_SIF)
            {
                me->DespawnOrUnsummon(7000);
                events.Reset();
                _allowCast = false;
                me->InterruptSpell(CURRENT_GENERIC_SPELL);
                me->SetReactState(REACT_PASSIVE);
                me->AttackStop();
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (auto eventID = events.ExecuteEvent())
            {
                switch (eventID)
                {
                    case EVENT_SIF_FINISH_DOMINION:
                        me->PlayDirectSound(SOUND_SIF_DESPAWN);
                        me->MonsterYell("This pathetic morons are harmless. Relive my station, dispose of them!", LANG_UNIVERSAL, 0);
                        me->DespawnOrUnsummon(5s);
                        break;
                    case EVENT_SIF_START_TALK:
                        if (Creature* colossus = me->FindNearestCreature(32872, 500.0f, true))
                            if (colossus->IsAIEnabled)
                                colossus->AI()->DoAction(1);
                        me->MonsterYell("Thorim, my lord, why else would these invaders have come into your sanctum but to slay you? They must be stopped!", LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(SOUND_SIF_START);
                        break;
                    case EVENT_SIF_JOIN_TALK:
                        me->PlayDirectSound(SOUND_SIF_EVENT);
                        me->MonsterYell("Impossible! Lord Thorim, I will bring your foes a frigid death!", LANG_UNIVERSAL, 0);
                        events.ScheduleEvent(EVENT_SIF_FROST_NOVA_START, 1000);
                        events.ScheduleEvent(EVENT_SIF_FROSTBOLT, 3500);
                        events.ScheduleEvent(EVENT_SIF_FROSTBOLT_VALLEY, 11000);
                        events.ScheduleEvent(EVENT_SIF_BLIZZARD, 15000, 1);
                        break;
                    case EVENT_SIF_FROSTBOLT_VALLEY:
                        me->CastSpell(me, RAID_MODE(SPELL_FROSTBOLT_VOLLEY, SPELL_FROSTBOLT_VOLLEY_H), false);
                        events.Repeat(13s);
                        events.DelayEvents(1500, 0);
                        return;
                    case EVENT_SIF_FROSTBOLT:
                        if (_allowCast)
                            if (Player* target = SelectTargetFromPlayerList(70))
                            {
                                me->CastSpell(target, RAID_MODE(SPELL_FROSTBOLT, SPELL_FROSTBOLT_H), false);
                                me->StopMoving();
                                events.DelayEvents(1500, 0);
                            }
                        events.Repeat(2.5s);
                        return;
                    case EVENT_SIF_BLIZZARD:
                        //! check wheter blizzard target is moving, if its not moving then call his Reset() hook
                        //! to execute movement code again
                        if (InstanceScript* instance = me->GetInstanceScript())
                        {
                            if (Creature* blizzardTarget = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_SIF_BLIZZARD)))
                                if (!blizzardTarget->isMoving())
                                    if (blizzardTarget->IsAIEnabled)
                                        blizzardTarget->AI()->Reset();
                        }

                        DoCastAOE(RAID_MODE(SPELL_BLIZZARD_10, SPELL_BLIZZARD_25), true);
                        events.Repeat(40s);
                        return;
                    case EVENT_SIF_FROST_NOVA_START:
                        me->NearTeleportTo(2108 + urand(0, 42), -238 - irand(0, 46), 420.02f, me->GetAngle(&Middle));
                        events.Repeat(20s);
                        events.DelayEvents(5001, 0);
                        events.ScheduleEvent(EVENT_SIF_FROST_NOVA_CAST, 2.5);
                        _allowCast = false;
                        return;
                    case EVENT_SIF_FROST_NOVA_CAST:
                        _allowCast = true;
                        me->CastSpell(me, RAID_MODE(SPELL_FROSTNOVA, SPELL_FROSTNOVA_H), false);
                        return;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thorim_sifAI(pCreature);
    }
};

class boss_thorim_lightning_orb : public CreatureScript
{
public:
    boss_thorim_lightning_orb() : CreatureScript("boss_thorim_lightning_orb") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thorim_lightning_orbAI (pCreature);
    }

    struct boss_thorim_lightning_orbAI : public npc_escortAI
    {
        boss_thorim_lightning_orbAI(Creature* pCreature) : npc_escortAI(pCreature)
        {
            InitWaypoint();
            Reset();
            Start(false, true, 0);
        }

        uint32 Timer;

        void EnterEvadeMode() {}
        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit*) {}

        void InitWaypoint()
        {
            AddWaypoint(1, 2135, -304, 438.24f, 0);
            AddWaypoint(2, 2132, -441, 438.24f, 0);
            AddWaypoint(3, 2167, -442, 438.24f, 0);
            AddWaypoint(4, 2227, -432, 412.18f, 0);
            AddWaypoint(5, 2227, -263, 412.17f, 0);
            AddWaypoint(6, 2179, -262, 414.7f, 0);
            AddWaypoint(7, 2169, -261, 419.3f, 0);
            AddWaypoint(8, 2110, -251, 419.42f, 0);
        }

        void Reset()
        {
            me->CastSpell(me, SPELL_LIGHTNING_DESTRUCTION, true);
        }

        void WaypointReached(uint32 point)
        {
        }
    };
};

class boss_thorim_trap : public CreatureScript
{
public:
    boss_thorim_trap() : CreatureScript("boss_thorim_trap") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thorim_trapAI (pCreature);
    }

    struct boss_thorim_trapAI : public NullCreatureAI
    {
        boss_thorim_trapAI(Creature* pCreature) : NullCreatureAI(pCreature) { }

        uint32 _checkTimer;

        void Reset() { _checkTimer = 1; }
        void UpdateAI(uint32 diff)
        {
            if (_checkTimer)
            {
                _checkTimer += diff;
                if ((_checkTimer >= 1000 && _checkTimer < 10000) || _checkTimer >= 60000)
                {
                    if (me->SelectNearbyTarget(NULL, 12.0f))
                    {
                        me->CastSpell(me, SPELL_LIGHTNING_FIELD, true);
                        me->CastSpell(me, (me->GetEntry() == 33054 /*NPC_THORIM_TRAP_BUNNY*/ ? SPELL_PARALYTIC_FIELD_FIRST : SPELL_PARALYTIC_FIELD_SECOND), true);
                        _checkTimer = 10000;
                        return;
                    }
                    _checkTimer = 1;
                }
            }
        }
    };
};

class boss_thorim_sif_blizzard : public CreatureScript
{
public:
    boss_thorim_sif_blizzard() : CreatureScript("boss_thorim_sif_blizzard") { }

    struct boss_thorim_sif_blizzardAI : public ScriptedAI
    {
        boss_thorim_sif_blizzardAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            Reset();
            me->setActive(true);
            me->SetReactState(REACT_PASSIVE);
            me->SetWalk(false);
        }

        void MoveInLineOfSight(Unit *who) override { }
        void EnterCombat(Unit *who) override { }
        void AttackStart(Unit *who) override { }

        void FillCirclePath(Position const& centerPos, float radius, float z, Movement::PointsArray& path)
        {
            float step = -M_PI / 8.0f;
            float angle = centerPos.GetAngle(me->GetPositionX(), me->GetPositionY());

            for (uint8 i = 0; i < 16; angle += step, ++i)
            {
                G3D::Vector3 point;
                point.x = centerPos.GetPositionX() + radius * cosf(angle);
                point.y = centerPos.GetPositionY() + radius * sinf(angle);
                point.z = z;
                path.push_back(point);
            }
        }

        void MoveCyclicPath()
        {
            Movement::MoveSplineInit init(me);
            FillCirclePath(CenterPos, me->GetHomePosition().GetExactDist2d(CenterPos.GetPositionX(), CenterPos.GetPositionY()), me->GetPositionZ(), init.Path());
            init.SetWalk(false);
            init.SetSmooth();
            init.SetCyclic();
            init.Launch();
        }

        void Reset() override
        {
            me->SetSpeedRate(MOVE_RUN, 0.8f);
            me->SetSpeedRate(MOVE_FLIGHT, 0.8f);
            MoveCyclicPath();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thorim_sif_blizzardAI(pCreature);
    }
};

class boss_thorim_pillar : public CreatureScript
{
public:
    boss_thorim_pillar() : CreatureScript("boss_thorim_pillar") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thorim_pillarAI (pCreature);
    }

    struct boss_thorim_pillarAI : public NullCreatureAI
    {
        boss_thorim_pillarAI(Creature* pCreature) : NullCreatureAI(pCreature) { }

        uint32 _resetTimer;

        void Reset()
        {
            _resetTimer = 0;
            me->SetControlled(true, UNIT_STATE_STUNNED);
            me->SetDisableGravity(true);
        }

        void SpellHit(Unit*, const SpellInfo* spellInfo)
        {
            if (spellInfo->Id == SPELL_CHARGE_ORB)
                me->CastSpell(me, SPELL_LIGHTNING_PILLAR_P1, true);
            else if (spellInfo->Id == SPELL_LIGHTNING_PILLAR_P2)
            {
                if (Creature *cr = me->FindNearestCreature(NPC_THUNDER_ORB, 100))
                    cr->CastSpell(cr, SPELL_LIGHTNING_ORB_VISUAL, true);
            }
        }

        void UpdateAI(uint32 diff)
        {
            _resetTimer += diff;
            if (_resetTimer >= 10000)
                Reset(); // _resetTimer set to 0
        }
    };
};

class boss_thorim_start_npcs : public CreatureScript
{
public:
    boss_thorim_start_npcs() : CreatureScript("boss_thorim_start_npcs") { }

    struct boss_thorim_start_npcsAI : public ScriptedAI
    {
        boss_thorim_start_npcsAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            if (me->GetEntry() == NPC_JORMUNGAR_BEHEMOT)
                me->setFaction(1693);
            else
                me->setFaction(1692);
        }

        void Reset() override
        {
            events.Reset();
            _isCaster = (me->GetEntry() == NPC_DARK_RUNE_ACOLYTE_I);
            _playerAttack = false;
            if (me->GetEntry() != NPC_JORMUNGAR_BEHEMOT)
                if (Creature* cr = me->FindNearestCreature(NPC_JORMUNGAR_BEHEMOT, 30.0f))
                {
                    AttackStart(cr);
                    if (me->GetEntry() == NPC_CAPTURED_MERCENARY_CAPTAIN_ALLY || me->GetEntry() == NPC_CAPTURED_MERCENARY_CAPTAIN_HORDE)
                        cr->AddThreat(me, 990000.f);
                }
        }

        void EnterEvadeMode() override
        {
            if (me->GetInstanceScript())
                if (Creature* thorim = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_THORIM)))
                    if (thorim->IsAIEnabled)
                        thorim->AI()->EnterEvadeMode();
        }

        bool CheckEvadeIfOutOfCombatArea() const override
        {
            Position roomCenter(2134.571289f, -263.170441f, 419.846710f, 1.582209f);
            return me->GetDistance2d(roomCenter.GetPositionX(), roomCenter.GetPositionY()) > 40.f;
        }

        void AttackStart(Unit* who) override
        {
            switch (me->GetEntry())
            {
                case NPC_CAPTURED_MERCENARY_CAPTAIN_ALLY:
                case NPC_CAPTURED_MERCENARY_CAPTAIN_HORDE:
                case NPC_JORMUNGAR_BEHEMOT:
                    UnitAI::AttackStart(who);
                    return;
            }
            UnitAI::AttackStartCaster(who, 12.f);
        }

        void DamageTaken(Unit* who, uint32&, DamageEffectType, SpellSchoolMask)
        {
            if (!_playerAttack && who && (who->GetTypeId() == TYPEID_PLAYER || IS_PLAYER_GUID(who->GetOwnerGUID())))
            {
                if (me->GetInstanceScript())
                    if (Creature* thorim = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_THORIM)))
                    {
                        if (!thorim->IsInCombat())
                        {
                            thorim->AI()->SetData(DATA_INFORM_PRE_COMBAT_SUMMONS, DATA_INFORM_PRE_COMBAT_SUMMONS);
                            thorim->SetInCombatWithZone();
                            thorim->AI()->AttackStart(who);
                        }
                    }
                _playerAttack = true;
            }

            if (!_playerAttack && me->HealthBelowPct(60))
                me->SetHealth(me->GetMaxHealth());
        }

        void JustDied(Unit*)
        {
            if (me->GetInstanceScript())
                if (Creature* thorim = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_THORIM)))
                    thorim->AI()->DoAction(ACTION_START_TRASH_DIED);
        }

        void EnterCombat(Unit* who)
        {
            if (me->GetEntry() == NPC_DARK_RUNE_ACOLYTE_I)
            {
                events.ScheduleEvent(EVENT_DR_ACOLYTE_GH, 10000);
                events.ScheduleEvent(EVENT_DR_ACOLYTE_HS, 5000);
                events.ScheduleEvent(EVENT_DR_ACOLYTE_R, 7000);
            }
            else if (me->GetEntry() == NPC_CAPTURED_MERCENARY_SOLDIER_ALLY || me->GetEntry() == NPC_CAPTURED_MERCENARY_SOLDIER_HORDE)
            {
                events.ScheduleEvent(EVENT_CM_SOLDIER_BS, 9000);
                events.ScheduleEvent(EVENT_CM_SOLDIER_WC, 5000);
                events.ScheduleEvent(EVENT_CM_SOLDIER_S, 0);
            }
            else if (me->GetEntry() == NPC_CAPTURED_MERCENARY_CAPTAIN_ALLY || me->GetEntry() == NPC_CAPTURED_MERCENARY_CAPTAIN_HORDE)
            {
                events.ScheduleEvent(EVENT_CM_CAPTAIN_D, 9000);
                events.ScheduleEvent(EVENT_CM_CAPTAIN_HC, 5000);
            }
            else if (me->GetEntry() == NPC_JORMUNGAR_BEHEMOT)
            {
                events.ScheduleEvent(EVENT_JB_ACID_BREATH, 12000);
                events.ScheduleEvent(EVENT_JB_SWEEP, 5000);
            }

            me->CallForHelp(10.f);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_DR_ACOLYTE_GH:
                    if (HealthBelowPct(60))
                        me->CastSpell(me, SPELL_GREATER_HEAL, false);
                    else if (Unit* target = DoSelectLowestHpFriendly(60.0f, 20))
                        me->CastSpell(target, SPELL_GREATER_HEAL, false);
                    events.RepeatEvent(10000);
                    break;
                case EVENT_DR_ACOLYTE_HS:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        me->CastSpell(target, SPELL_HOLY_SMITE, false);
                    events.RepeatEvent(1600);
                    break;
                case EVENT_DR_ACOLYTE_R:
                    if (HealthBelowPct(75) && !me->HasAura(SPELL_RENEW))
                        me->CastSpell(me, SPELL_GREATER_HEAL, false);
                    else if (Unit* target = DoSelectLowestHpFriendly(60.0f, 10))
                        me->CastSpell(target, SPELL_RENEW, false);
                    events.RepeatEvent(7000);
                    break;
                case EVENT_CM_SOLDIER_BS:
                    me->CastSpell(me->GetVictim(), SPELL_BARBED_SHOT, false);
                    events.RepeatEvent(9000);
                    break;
                case EVENT_CM_SOLDIER_WC:
                    me->CastSpell(me->GetVictim(), SPELL_WING_CLIP, false);
                    events.RepeatEvent(5000);
                    break;
                case EVENT_CM_SOLDIER_S:
                    if (me->GetDistance(me->GetVictim()) > 8)
                        me->CastSpell(me->GetVictim(), SPELL_SHOOT, false);

                    events.RepeatEvent(1500);
                    break;
                case EVENT_CM_CAPTAIN_D:
                    me->CastSpell(me->GetVictim(), SPELL_DEVASTATE, false);
                    events.RepeatEvent(9000);
                    break;
                case EVENT_CM_CAPTAIN_HC:
                    me->CastSpell(me->GetVictim(), SPELL_HEROIC_STRIKE, false);
                    events.RepeatEvent(5000);
                    break;
                case EVENT_JB_ACID_BREATH:
                    me->CastSpell(me->GetVictim(), SPELL_ACID_BREATH, false);
                    events.RepeatEvent(12000);
                    break;
                case EVENT_JB_SWEEP:
                    me->CastSpell(me->GetVictim(), SPELL_SWEEP, false);
                    events.RepeatEvent(5000);
                    break;
            }

            EnterEvadeIfOutOfCombatArea();
            if (!_isCaster || (me->GetPower(POWER_MANA) * 100 / me->GetMaxPower(POWER_MANA) < 10))
                DoMeleeAttackIfReady();
        }
    private:
        EventMap events;
        bool _isCaster;
        bool _playerAttack;
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thorim_start_npcsAI(pCreature);
    }
};

class boss_thorim_gauntlet_npcs : public CreatureScript
{
public:
    boss_thorim_gauntlet_npcs() : CreatureScript("boss_thorim_gauntlet_npcs") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thorim_gauntlet_npcsAI (pCreature);
    }

    struct boss_thorim_gauntlet_npcsAI : public ScriptedAI
    {
        boss_thorim_gauntlet_npcsAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        EventMap events;
        bool _isCaster;

        void Reset()
        {
            events.Reset();
            _isCaster = (me->GetEntry() == NPC_DARK_RUNE_ACOLYTE_G);
        }

        void EnterCombat(Unit* who)
        {
            if (me->GetEntry() == NPC_IRON_RING_GUARD)
            {
                events.ScheduleEvent(EVENT_IR_GUARD_IMPALE, 12000);
                events.ScheduleEvent(EVENT_IR_GUARD_WHIRL, 5000);
            }
            else if (me->GetEntry() == NPC_DARK_RUNE_ACOLYTE_I || me->GetEntry() == NPC_DARK_RUNE_ACOLYTE_G)
            {
                events.ScheduleEvent(EVENT_DR_ACOLYTE_GH, 10000);
                events.ScheduleEvent(EVENT_DR_ACOLYTE_HS, 5000);
                events.ScheduleEvent(EVENT_DR_ACOLYTE_R, 7000);
            }
            else if (me->GetEntry() == NPC_IRON_HONOR_GUARD)
            {
                events.ScheduleEvent(EVENT_IH_GUARD_CLEAVE, 6000);
                events.ScheduleEvent(EVENT_IH_GUARD_HAMSTRING, 9000);
                events.ScheduleEvent(EVENT_IH_GUARD_SHIELD_SMASH, 15000);

                if (Creature* runeGiant = me->FindNearestCreature(NPC_ANCIENT_RUNE_GIANT, 200.0f))
                    runeGiant->AI()->DoAction(ACTION_IRON_HONOR_DIED);
            }

            me->CallForHelp(25);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_IR_GUARD_IMPALE:
                    me->CastSpell(me->GetVictim(), SPELL_IMPALE, false);
                    events.RepeatEvent(12000);
                    break;
                case EVENT_IR_GUARD_WHIRL:
                    me->CastSpell(me->GetVictim(), SPELL_WHIRLING_TRIP, false);
                    events.RepeatEvent(5000);
                    break;
                case EVENT_DR_ACOLYTE_GH:
                    if (HealthBelowPct(60))
                        me->CastSpell(me, SPELL_GREATER_HEAL, false);
                    else if (Unit* target = DoSelectLowestHpFriendly(60.0f, 20))
                        me->CastSpell(target, SPELL_GREATER_HEAL, false);
                    events.RepeatEvent(10000);
                    break;
                case EVENT_DR_ACOLYTE_HS:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0))
                        me->CastSpell(target, SPELL_HOLY_SMITE, false);
                    events.RepeatEvent(1600);
                    break;
                case EVENT_DR_ACOLYTE_R:
                    if (HealthBelowPct(75) && !me->HasAura(SPELL_RENEW))
                        me->CastSpell(me, SPELL_GREATER_HEAL, false);
                    else if (Unit* target = DoSelectLowestHpFriendly(60.0f, 10))
                        me->CastSpell(target, SPELL_RENEW, false);
                    events.RepeatEvent(7000);
                    break;
                case EVENT_IH_GUARD_CLEAVE:
                    me->CastSpell(me->GetVictim(), SPELL_CLEAVE, false);
                    events.RepeatEvent(6000);
                    break;
                case EVENT_IH_GUARD_HAMSTRING:
                    me->CastSpell(me->GetVictim(), SPELL_HAMSTRING, false);
                    events.RepeatEvent(9000);
                    break;
                case EVENT_IH_GUARD_SHIELD_SMASH:
                    me->CastSpell(me->GetVictim(), SPELL_SHIELD_SMASH, false);
                    events.RepeatEvent(15000);
                    break;
            }

            if (!_isCaster || (me->GetPower(POWER_MANA)*100 / me->GetMaxPower(POWER_MANA) < 10))
                DoMeleeAttackIfReady();
        }
    };
};

class boss_thorim_runic_colossus : public CreatureScript
{
public:
    boss_thorim_runic_colossus() : CreatureScript("boss_thorim_runic_colossus") { }

    struct boss_thorim_runic_colossusAI : public ScriptedAI
    {
        boss_thorim_runic_colossusAI(Creature* pCreature) : ScriptedAI(pCreature) {}

        void Reset()
        {
            _checkTarget = false;
            events.Reset();
        }

        void DoAction(int32 actionId) override
        {
            if (actionId == 1)
                events.ScheduleEvent(EVENT_RC_RUNIC_SMASH, 10000);
        }

        void JustDied(Unit*)
        {
            if (me->GetInstanceScript())
                if (GameObject *go = ObjectAccessor::GetGameObject(*me, me->GetInstanceScript()->GetData64(DATA_THORIM_FIRST_DOORS)))
                    go->SetGoState(GO_STATE_ACTIVE);
        }

        void EnterCombat(Unit*)
        {
            events.Reset();
            events.ScheduleEvent(EVENT_RC_RUNIC_BARRIER, 10000);
            events.ScheduleEvent(EVENT_RC_SMASH, 18000);
            events.ScheduleEvent(EVENT_RC_CHARGE, 15000);

            _checkTarget = true;
            me->InterruptNonMeleeSpells(false);
        }

        void UpdateAI(uint32 diff)
        {
            if (_checkTarget && !UpdateVictim())
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_RC_RUNIC_SMASH:
                    DoCast(me, RAND(SPELL_RUNIC_SMASH_LEFT, SPELL_RUNIC_SMASH_RIGHT));

                    events.RepeatEvent(11000);
                    break;
                case EVENT_RC_RUNIC_BARRIER:
                    me->CastSpell(me, SPELL_RUNIC_BARRIER, false);
                    me->MonsterTextEmote("Runic Colossus surrounds itself with a crackling Runic Barrier!", 0, true);
                    events.RepeatEvent(20000);
                    break;
                case EVENT_RC_SMASH:
                    me->CastSpell(me->GetVictim(), SPELL_SMASH, false);
                    events.RepeatEvent(10000);
                    break;
                case EVENT_RC_CHARGE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        me->CastSpell(target, SPELL_CHARGE, false);
                    events.RepeatEvent(15000);
                    break;
            }

            DoMeleeAttackIfReady();
        }
    private:
        EventMap events;
        bool _checkTarget;
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thorim_runic_colossusAI(pCreature);
    }
};

class boss_thorim_ancient_rune_giant : public CreatureScript
{
public:
    boss_thorim_ancient_rune_giant() : CreatureScript("boss_thorim_ancient_rune_giant") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thorim_ancient_rune_giantAI (pCreature);
    }

    struct boss_thorim_ancient_rune_giantAI : public ScriptedAI
    {
        boss_thorim_ancient_rune_giantAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        EventMap events;
        bool _isInCombat;

        void Reset()
        {
            _isInCombat = false;
            events.Reset();
        }

        void EnterCombat(Unit*)
        {
            _isInCombat = true;
            events.CancelEvent(EVENT_ARG_SPAWN);
            events.ScheduleEvent(EVENT_ARG_RD, 12000);
            events.ScheduleEvent(EVENT_ARG_STOMP, 8000);

            me->CastSpell(me, SPELL_RUNIC_FORTIFICATION, false);
            me->MonsterTextEmote("Ancient Rune Giant fortifies nearby allies with runic might", 0, true);
        }

        void JustDied(Unit*)
        {
            if (InstanceScript* pInstance = me->GetInstanceScript())
            {
                if (GameObject* go = ObjectAccessor::GetGameObject(*me, pInstance->GetData64(DATA_THORIM_SECOND_DOORS)))
                    go->SetGoState(GO_STATE_ACTIVE);

                if (Creature* thorim = ObjectAccessor::GetCreature(*me, pInstance->GetData64(TYPE_THORIM)))
                    thorim->AI()->DoAction(ACTION_ALLOW_HIT);
            }
        }

        void DoAction(int32 param)
        {
            if (param == ACTION_IRON_HONOR_DIED)
                events.RescheduleEvent(EVENT_ARG_SPAWN, 20000);
        }

        void UpdateAI(uint32 diff)
        {
            if (_isInCombat && !UpdateVictim())
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_ARG_RD:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                        me->CastSpell(target, SPELL_RUNE_DETONATION, false);
                    events.RepeatEvent(12000);
                    break;
                case EVENT_ARG_STOMP:
                    me->CastSpell(me->GetVictim(), SPELL_STOMP, false);
                    events.RepeatEvent(8000);
                    break;
                case EVENT_ARG_SPAWN:
                    if (Creature *cr = me->SummonCreature(NPC_IRON_HONOR_GUARD, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000))
                        if (Unit* target = SelectTargetFromPlayerList(150.0f))
                            cr->AI()->AttackStart(target);
                    events.RepeatEvent(10000);
                    break;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class boss_thorim_arena_npcs : public CreatureScript
{
public:
    boss_thorim_arena_npcs() : CreatureScript("boss_thorim_arena_npcs") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thorim_arena_npcsAI (pCreature);
    }

    struct boss_thorim_arena_npcsAI : public ScriptedAI
    {
        boss_thorim_arena_npcsAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        EventMap events;
        bool _isCaster;

        void Reset()
        {
            _isCaster = (me->GetEntry() == NPC_DARK_RUNE_EVOKER);
            events.Reset();
            if (me->GetEntry() == NPC_DARK_RUNE_WARBRINGER)
                me->CastSpell(me, SPELL_AURA_OF_CELERITY, true);
        }

        void EnterCombat(Unit*)
        {
            if (me->GetEntry() == NPC_DARK_RUNE_WARBRINGER)
            {
                events.ScheduleEvent(EVENT_DR_WARBRINGER_RS, 8000);
            }
            else if (me->GetEntry() == NPC_DARK_RUNE_EVOKER)
            {
                events.ScheduleEvent(EVENT_DR_EVOKER_RL, 2500);
                events.ScheduleEvent(EVENT_DR_EVOKER_RM, 4000);
                events.ScheduleEvent(EVENT_DR_EVOKER_RS, 10000);
            }
            else if (me->GetEntry() == NPC_DARK_RUNE_CHAMPION)
            {
                events.ScheduleEvent(EVENT_DR_CHAMPION_WH, 6000);
                events.ScheduleEvent(EVENT_DR_CHAMPION_CH, 12000);
                events.ScheduleEvent(EVENT_DR_CHAMPION_MS, 8000);
            }
            else if (me->GetEntry() == NPC_DARK_RUNE_COMMONER)
            {
                events.ScheduleEvent(EVENT_DR_COMMONER_LB, 5000);
                events.ScheduleEvent(EVENT_DR_COMMONER_PM, 6000);
            }
        }

        bool CanAIAttack(const Unit* target) const
        {
            return target->GetPositionX() < 2180 && target->GetPositionZ() < 425;
        }

        bool SelectT()
        {
            Player* target = NULL;
            Map::PlayerList const& pList = me->GetMap()->GetPlayers();
            uint8 num = urand(0, pList.getSize()-1);
            uint8 count = 0;
            for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr, ++count)
            {
                if (itr->GetSource()->GetPositionX() > 2180 || !itr->GetSource()->IsAlive() || itr->GetSource()->GetPositionZ() > 425 || itr->GetSource()->IsGameMaster())
                    continue;

                if (count <= num || !target)
                    target = itr->GetSource();
                else
                    break;
            }

            if (target)
            {
                AttackStart(target);
                me->AddThreat(target, 500.0f);
                if (me->GetEntry() == NPC_DARK_RUNE_EVOKER && urand(0,1))
                    me->CastSpell(me, SPELL_RUNIC_SHIELD, false);
                else if (me->GetEntry() == NPC_DARK_RUNE_CHAMPION && !urand(0,2))
                    me->CastSpell(target, SPELL_CHARGE, false);
                return true;
            }
            return false;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && !SelectT())
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_DR_WARBRINGER_RS:
                    me->CastSpell(me->GetVictim(), SPELL_RUNIC_STRIKE, false);
                    events.RepeatEvent(8000);
                    break;
                case EVENT_DR_EVOKER_RL:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        me->CastSpell(target, SPELL_RUNIC_LIGHTNING, false);
                    events.RepeatEvent(2500);
                    break;
                case EVENT_DR_EVOKER_RM:
                    if (Unit* target = DoSelectLowestHpFriendly(40.0f, 15))
                        me->CastSpell(target, SPELL_RUNIC_MENDING, false);
                    else
                        me->CastSpell(me, SPELL_RUNIC_MENDING, false);
                    events.RepeatEvent(4000);
                    break;
                case EVENT_DR_EVOKER_RS:
                    me->CastSpell(me, SPELL_RUNIC_SHIELD, false);
                    events.RepeatEvent(10000);
                    break;
                case EVENT_DR_CHAMPION_CH:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        me->CastSpell(target, SPELL_CHARGE, false);
                    events.RepeatEvent(12000);
                    break;
                case EVENT_DR_CHAMPION_WH:
                    if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISARMED))
                        me->CastSpell(me, SPELL_WHIRLWIND, false);
                    events.RepeatEvent(6000);
                    break;
                case EVENT_DR_CHAMPION_MS:
                    me->CastSpell(me->GetVictim(), SPELL_MORTAL_STRIKE, false);
                    events.RepeatEvent(8000);
                    break;
                case EVENT_DR_COMMONER_LB:
                    me->CastSpell(me->GetVictim(), SPELL_LOW_BLOW, false);
                    events.RepeatEvent(5000);
                    break;
                case EVENT_DR_COMMONER_PM:
                    me->CastSpell(me->GetVictim(), SPELL_PUMMEL, false);
                    events.RepeatEvent(6000);
                    break;
            }

            if (!_isCaster || (me->GetPower(POWER_MANA)*100 / me->GetMaxPower(POWER_MANA) < 10))
                DoMeleeAttackIfReady();
        }
    };
};

class go_thorim_lever : public GameObjectScript
{
public:
    go_thorim_lever() : GameObjectScript("go_thorim_lever") { }

    bool OnGossipHello(Player* pPlayer, GameObject* pGo)
    {
        if (GameObject *g = pPlayer->FindNearestGameObject(GO_ARENA_LEVER_GATE, 50))
        {
            g->UseDoorOrButton();
        }

        pGo->UseDoorOrButton();
        return true;
    }
};

struct npc_thorim_golem_left_right_bunny_AI : public ScriptedAI
{
    npc_thorim_golem_left_right_bunny_AI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void AttackStart(Unit* /*who*/) override { }
    void DamageTaken(Unit* /*who*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        damage = 0;
    }
};

class spell_thorim_lightning_pillar_P2 : public SpellScriptLoader
{
public:
    spell_thorim_lightning_pillar_P2() : SpellScriptLoader("spell_thorim_lightning_pillar_P2") {}

    class spell_thorim_lightning_pillar_P2_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_thorim_lightning_pillar_P2_AuraScript);

        void OnPeriodic(AuraEffect const* aurEff)
        {
            PreventDefaultAction();
            if (Unit* caster = GetCaster())
                GetUnitOwner()->CastSpell(caster, GetSpellInfo()->Effects[aurEff->GetEffIndex()].TriggerSpell, true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_thorim_lightning_pillar_P2_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    class spell_thorim_lightning_pillar_P2_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_thorim_lightning_pillar_P2_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if([](WorldObject* object)
            {
                //! There is tons of same entry triggers during thorim encounter
                //! those are not doing anything in particular but this spell can target them
                //! they're above so we can filter them out by position Z
                return object->GetPositionZ() > 426.f;
            });
            if (targets.empty())
                return;

            WorldObject* properTarget = Trinity::Containers::SelectRandomContainerElement(targets);
            targets.clear();
            if (properTarget)
                targets.push_back(properTarget);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_thorim_lightning_pillar_P2_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_thorim_lightning_pillar_P2_SpellScript();
    }

    AuraScript* GetAuraScript() const
    {
        return new spell_thorim_lightning_pillar_P2_AuraScript();
    }
};

class spell_thorim_trash_impale : public SpellScriptLoader
{
    public:
        spell_thorim_trash_impale() : SpellScriptLoader("spell_thorim_trash_impale") { }

        class spell_thorim_trash_impale_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_thorim_trash_impale_AuraScript);

            void OnPeriodic(AuraEffect const* aurEff)
            {
                // deals damage until target is healed above 90%
                if (GetUnitOwner()->HealthAbovePct(90))
                    SetDuration(0);
            }

            void Register()
            {
                 OnEffectPeriodic += AuraEffectPeriodicFn(spell_thorim_trash_impale_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_thorim_trash_impale_AuraScript();
        }
};

class achievement_thorim_stand_in_the_lightning : public AchievementCriteriaScript
{
    public:
        achievement_thorim_stand_in_the_lightning() : AchievementCriteriaScript("achievement_thorim_stand_in_the_lightning") {}

        bool OnCheck(Player* player, Unit*)
        {
            if (InstanceScript* instance = player->GetInstanceScript())
                if (Creature* cr = ObjectAccessor::GetCreature(*player, instance->GetData64(TYPE_THORIM)))
                    return cr->AI()->GetData(DATA_HIT_BY_LIGHTNING);

            return false;
        }
};

class achievement_thorim_lose_your_illusion : public AchievementCriteriaScript
{
    public:
        achievement_thorim_lose_your_illusion() : AchievementCriteriaScript("achievement_thorim_lose_your_illusion") {}

        bool OnCheck(Player* player, Unit*)
        {
            if (InstanceScript* instance = player->GetInstanceScript())
                if (Creature* cr = ObjectAccessor::GetCreature(*player, instance->GetData64(TYPE_THORIM)))
                    return cr->AI()->GetData(DATA_LOSE_YOUR_ILLUSION);

            return false;
        }
};

class spell_thorim_stormhammer_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_thorim_stormhammer_SpellScript);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_STORMHAMMER_BACK_TO_THORIM, SPELL_DEFEANING_THUNDER });
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([](WorldObject* target) -> bool
        {
            return HeightPositionCheck(true)(target) || OutOfArenaCheck()(target);
        });

        if (targets.empty())
        {
            FinishCast(SPELL_FAILED_NO_VALID_TARGETS);
            return;
        }

        WorldObject* target = Trinity::Containers::SelectRandomContainerElement(targets);
        targets.clear();
        targets.push_back(target);
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
        {
            target->CastSpell(target, SPELL_DEFEANING_THUNDER, true);
            target->CastSpell(GetCaster(), SPELL_STORMHAMMER_BACK_TO_THORIM, true);
        }
    }

    void LoseHammer()
    {
        GetCaster()->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 0);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_thorim_stormhammer_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ENEMY);
        AfterCast += SpellCastFn(spell_thorim_stormhammer_SpellScript::LoseHammer);
        OnEffectHitTarget += SpellEffectFn(spell_thorim_stormhammer_SpellScript::HandleScript, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class spell_thorim_stormhammer_boomerang_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_thorim_stormhammer_boomerang_SpellScript);

    void RecoverHammer(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, THORIM_WEAPON_DISPLAY_ID);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_thorim_stormhammer_boomerang_SpellScript::RecoverHammer, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

class spell_thorim_runic_smash_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_thorim_runic_smash_SpellScript);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_RUNIC_SMASH_DAMAGE });
    }

    void HandleScript(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);

        std::list<Creature*> triggers;
        GetCaster()->GetCreatureListWithEntryInGrid(triggers, GetSpellInfo()->Id == SPELL_RUNIC_SMASH_LEFT ? NPC_GOLEM_RIGHT_HAND_BUNNY : NPC_GOLEM_LEFT_HAND_BUNNY, 150.0f);
        for (Creature* trigger : triggers)
        {
            float dist = GetCaster()->GetExactDist(trigger);
            trigger->m_Events.AddEvent(new RunicSmashExplosionEvent(trigger), trigger->m_Events.CalculateTime(uint64(dist * 30.f)));
        };
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_thorim_runic_smash_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_TRIGGER_SPELL);
    }
};

class spell_lightning_charge_selector_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_lightning_charge_selector_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targetList)
    {
        targetList.remove_if([&](WorldObject* object) -> bool
        {
            return !object->isInFront(GetCaster(), 1.0472f) || OutOfArenaCheck()(object);
        });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_lightning_charge_selector_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_CONE_ENEMY_104);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_lightning_charge_selector_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_CONE_ENTRY);
    }
};

class spell_thorim_stormhammer_sif_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_thorim_stormhammer_sif_SpellScript);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_STORMHAMMER_BACK_TO_THORIM, SPELL_SIF_TRANSFORM });
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
        {
            target->CastSpell(GetCaster(), SPELL_STORMHAMMER_BACK_TO_THORIM, true);
            target->CastSpell(target, SPELL_SIF_TRANSFORM, true);
        }
    }

    void LoseHammer()
    {
        GetCaster()->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 0);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_thorim_stormhammer_sif_SpellScript::LoseHammer);
        OnEffectHitTarget += SpellEffectFn(spell_thorim_stormhammer_sif_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

void AddSC_boss_thorim()
{
    // Main encounter
    new boss_thorim();
    new boss_thorim_sif();
    new boss_thorim_lightning_orb();
    new boss_thorim_trap();
    new boss_thorim_pillar();
    new boss_thorim_sif_blizzard();

    // Trash
    new boss_thorim_start_npcs();
    new boss_thorim_gauntlet_npcs();
    new boss_thorim_arena_npcs();
    new CreatureAILoader<npc_thorim_golem_left_right_bunny_AI>("npc_thorim_golem_left_right_bunny");

    // Mini bosses
    new boss_thorim_runic_colossus();
    new boss_thorim_ancient_rune_giant();

    // GOs
    new go_thorim_lever();

    // Spells
    new spell_thorim_lightning_pillar_P2();
    new spell_thorim_trash_impale();
    new SpellScriptLoaderEx<spell_thorim_stormhammer_SpellScript>("spell_thorim_stormhammer");
    new SpellScriptLoaderEx<spell_thorim_stormhammer_boomerang_SpellScript>("spell_thorim_stormhammer_boomerang");
    new SpellScriptLoaderEx<spell_thorim_runic_smash_SpellScript>("spell_thorim_runic_smash");
    new SpellScriptLoaderEx<spell_lightning_charge_selector_SpellScript>("spell_lightning_charge_selector");
    new SpellScriptLoaderEx<spell_thorim_stormhammer_sif_SpellScript>("spell_thorim_stormhammer_sif");

    // Achievements
    new achievement_thorim_stand_in_the_lightning();
    new achievement_thorim_lose_your_illusion();
}
