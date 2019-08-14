#include "hellforge.hpp"
#include "MoveSplineInit.h"
#include "GameObject.h"

enum BossFourEvents
{
    EVENT_BOSS_FOUR_LIGHTNING           = 1,

    EVENT_BOSS_FOUR_LIGHTNING_SHIELD,
    EVENT_BOSS_FOUR_CHAIN_LIGHTNING,
    EVENT_BOSS_FOUR_LIGHTNING_NOVA,
    EVENT_BOSS_FOUR_CHAINED_TARGETS,
    EVENT_BOSS_FOUR_CHECK_CHAINED_TARGETS,
    EVENT_BOSS_FOUR_THROW_WEAPON,
    EVENT_BOSS_FOUR_SWITCH_PHASE,
    EVENT_BOSS_FOUR_FROST_ARMOR,
    EVENT_BOSS_FOUR_MIND_WRAP,
    EVENT_BOSS_FOUR_FROST_NOVA,
    EVENT_BOSS_FOUR_FINAL_PHASE,
    EVENT_BOSS_FOUR_SHIELD_WALL,
    EVENT_BOSS_FOUR_REFLECT,
    EVENT_BOSS_FOUR_VEZAX_SHIT,
    EVENT_BOSS_FOUR_CLEAVE,
    EVENT_BOSS_FOUR_BEGIN_FROST_PHASE,
    EVENT_BOSS_FOUR_BEGIN_FINAL_PHASE,
    EVENT_BOSS_FOUR_BEGIN_WIPEOUT,
    EVENT_BOSS_FOUR_CHAINED_TARGETS_FAILURE,
    EVENT_BOSS_FOUR_CHECK_ALIVE_PLAYERS
};

enum BossFourSpells
{
    SPELL_BOSS_FOUR_MOONFIRE_VISUAL     = 36704,
    SPELL_BOSS_FOUR_BLUE_FIRE           = 42610,
    SPELL_BOSS_FOUR_LIGHTNING_NOVA      = 65279,
    SPELL_BOSS_FOUR_LIGHTNING_SHIELD    = 39067,
    SPELL_BOSS_FOUR_CHAIN_LIGHTNING     = 39066,
    SPELL_BOSS_FOUR_LIGHTNING_NOVA_2    = 59835,
    SPELL_BOSS_FOUR_CLOUD_VISUAL        = 62639,
    SPELL_BOSS_FOUR_STARFIRE            = 75332,
    SPELL_BOSS_FOUR_THROW_SPEAR         = 45730,
    SPELL_BOSS_FOUR_DEFEANING_THUNDER   = 62470,
    SPELL_BOSS_FOUR_SOUL_CHARGE         = 32054,
    SPELL_BOSS_FOUR_FROST_ARMOR         = 31256,
    SPELL_BOSS_FOUR_MIND_WRAP           = 38047,
    SPELL_BOSS_FOUR_FROZEN_BITE         = 61185,
    SPELL_BOSS_FOUR_COLD_SLAP           = 46198,
    SPELL_BOSS_FOUR_FROST_NOVA          = 29849,
    SPELL_BOSS_FOUR_BLIZZARD            = 19099,
    SPELL_BOSS_FOUR_SHIELD_WALL         = 41104,
    SPELL_BOSS_FOUR_CHARGE              = 24193,
    SPELL_BOSS_FOUR_REFLECT             = 36096,
    SPELL_BOSS_FOUR_IRONFORM            = 52022,
    SPELL_BOSS_FOUR_SURGE_OF_DARKNESS   = 62662,
    SPELL_BOSS_FOUR_FRENZY              = 40683,
    SPELL_BOSS_FOUR_CLEAVE              = 51917,
    SPELL_BOSS_FOUR_EMP_SHOCKWAVE       = 72815,
    SPELL_BOSS_FOUR_ARCANE_EXPLOSION    = 29973,
    SPELL_BOSS_FOUR_SHIELD_VISUAL       = 74621,
    SPELL_BOSS_FOUR_MARK_OF_CORRU       = 38222,
    SPELL_BOSS_FOUR_VORTEX_ENEMY        = 73037
};

enum BossFourCreatures
{
    NPC_BOSS_FOUR_LIGHTNING_TARGET      = 250017,
    NPC_BOSS_FOUR_BLIZZARD_TARGET       = 250018,
    NPC_BOSS_FOUR_FIERY_ORB             = 250032,
    NPC_BOSS_FOUR_PILLAR_PROTECTION     = 250034
};

enum BossFourMisc
{
    POINT_BOSS_FOUR_PATH_END_POINT          = 5,
    POINT_BOSS_FOUR_CHANGE_EQUIPMENT_FROST  = 9,
    POINT_BOSS_FOUR_CHANGE_EQUIPMENT_FINAL  = 10,
    GO_EQUIPMENT_CHEST                      = 400502,
    EMOTE_BOSS_FOUR_WORK                    = 173
};

enum BossFourPhase
{
    PHASE_BOSS_FOUR_LIGHTNING,
    PHASE_BOSS_FOUR_FROST,
    PHASE_BOSS_FOUR_FINAL
};

enum BossFourStats
{
    BOSS_FOUR_STAT_ID_HEALTH                = 29,
    BOSS_FOUR_STAT_ID_MELEE_DAMAGE          = 30,
    BOSS_FOUR_STAT_ID_FIRST_TRANSITION_PCT  = 31,
    BOSS_FOUR_STAT_ID_SECOND_TRANSITION_PCT = 32,
    BOSS_FOUR_STAT_ID_EMP_SHOCKWAVE         = 33,
    BOSS_FOUR_STAT_ID_STARFIRE_DAMAGE       = 34,
    BOSS_FOUR_STAT_ID_HAMMER_THROW_PCT      = 35,
    BOSS_FOUR_STAT_ID_MIND_WARP_COUNT       = 36,
    BOSS_FOUR_STAT_ID_FROST_NOVA_DAMAGE     = 37,
    BOSS_FOUR_STAT_ID_REFLECT_CHARGES_COUNT = 38,
    BOSS_FOUR_STAT_ID_CLEAVE_DAMAGE         = 39,
    BOSS_FOUR_STAT_ID_ARCANE_EXPLOSION_DMG  = 40,
    BOSS_FOUR_STAT_ID_LIGHTNING_NOVA_DMG    = 41,
    BOSS_FOUR_STAT_ID_BLIZZARD_DAMAGE       = 42,
    BOSS_FOUR_STAT_ID_SOUL_CHARGE_DURATION  = 43,
    BOSS_FOUR_STAT_ID_COLD_SLAP_DAMAGE      = 44,
    BOSS_FOUR_STAT_ID_CHAIN_LIGHTNING_DMG   = 45,
    BOSS_FOUR_STAT_ID_LIGHTNING_NOVA_DMG_2  = 46,
    BOSS_FOUR_STAT_ID_LIGHTNING_SHIELD_CNT  = 47
};

constexpr uint32 PROBLEMATIC_SPOTS_POS_SIZE{ 23 };
const std::array<Position const, PROBLEMATIC_SPOTS_POS_SIZE> _problematicSpawnPos
{
    {
        { 1191.118f, -187.228f, -72.91875f, 4.329f },
        { 1189.406f, -185.505f, -72.91612f, 4.031f },
        { 1178.354f, -173.862f, -72.91325f, 4.058f },
        { 1174.513f, -170.103f, -72.91920f, 3.968f },
        { 1170.025f, -174.030f, -72.91953f, 4.521f },
        { 1166.203f, -178.482f, -72.91953f, 4.109f },
        { 1151.484f, -193.147f, -72.91946f, 5.216f },
        { 1148.652f, -195.024f, -72.91946f, 4.737f },
        { 1142.643f, -194.069f, -72.91946f, 3.740f },
        { 1127.898f, -180.448f, -74.92907f, 3.791f },
        { 1123.758f, -177.884f, -72.91956f, 3.536f },
        { 1121.993f, -175.694f, -72.91956f, 3.673f },
        { 1117.067f, -171.180f, -72.91956f, 3.614f },
        { 1113.927f, -168.031f, -72.91687f, 3.614f },
        { 1109.540f, -163.618f, -72.83269f, 3.614f },
        { 1105.781f, -159.832f, -72.76193f, 3.241f },
        { 1109.219f, -155.847f, -74.35954f, 1.619f },
        { 1117.423f, -147.578f, -74.35954f, 1.070f },
        { 1121.901f, -138.772f, -74.35954f, 2.138f },
        { 1117.822f, -133.972f, -74.35954f, 2.330f },
        { 1114.293f, -130.104f, -74.35954f, 2.149f },
        { 1113.503f, -128.906f, -72.72610f, 2.149f },
        { 1116.759f, -125.056f, -72.35286f, 1.694f }
    }
};

constexpr uint32 LIGHTNING_SPAWN_POS_SIZE{ 137 };
const std::array<Position const, LIGHTNING_SPAWN_POS_SIZE> _lightningSpawnPos
{
    {
        { 1206.902100f, -166.427032f, -74.300705f },
        { 1204.605835f, -171.148239f, -74.289276f },
        { 1200.883545f, -175.638581f, -74.300453f },
        { 1196.511108f, -178.541412f, -74.316368f },
        { 1192.976318f, -182.419632f, -74.326820f },
        { 1193.189331f, -174.588348f, -74.357231f },
        { 1196.468750f, -170.929260f, -74.343498f },
        { 1199.331665f, -167.770721f, -74.328430f },
        { 1202.237915f, -161.462891f, -74.317780f },
        { 1201.056763f, -156.834641f, -74.334213f },
        { 1198.025146f, -158.797791f, -74.343124f },
        { 1193.970825f, -162.132065f, -74.359238f },
        { 1194.367432f, -167.625336f, -74.357582f },
        { 1190.283325f, -171.880997f, -74.347549f },
        { 1184.575073f, -167.426682f, -74.359467f },
        { 1180.240845f, -169.701324f, -74.359467f },
        { 1182.145996f, -161.940918f, -74.362411f },
        { 1187.995117f, -157.067886f, -74.363846f },
        { 1194.439819f, -155.807495f, -74.364662f },
        { 1196.908569f, -150.735199f, -74.358131f },
        { 1192.597656f, -146.545456f, -74.368179f },
        { 1189.650879f, -151.107971f, -74.367302f },
        { 1184.784790f, -156.041214f, -74.365074f },
        { 1180.175781f, -159.991241f, -74.363159f },
        { 1174.328003f, -164.010086f, -74.361420f },
        { 1167.780151f, -167.129623f, -74.912109f },
        { 1167.627319f, -172.579681f, -74.919899f },
        { 1161.117554f, -169.601959f, -74.927124f },
        { 1156.426758f, -166.869080f, -74.926872f },
        { 1154.990723f, -172.646851f, -74.928413f },
        { 1157.679565f, -178.022278f, -74.928413f },
        { 1155.550537f, -182.842896f, -74.929314f },
        { 1149.034180f, -177.558350f, -74.929314f },
        { 1150.239624f, -183.657776f, -74.929314f },
        { 1144.471313f, -185.437759f, -74.929314f },
        { 1147.859497f, -191.295517f, -74.929314f },
        { 1142.765625f, -190.624054f, -74.929314f },
        { 1140.036865f, -184.054962f, -74.929314f },
        { 1143.344604f, -180.261612f, -74.929314f },
        { 1138.898315f, -177.533890f, -74.929314f },
        { 1134.524536f, -183.852493f, -74.929314f },
        { 1131.853516f, -178.808395f, -74.929314f },
        { 1128.986450f, -175.717880f, -74.918983f },
        { 1136.580566f, -176.145950f, -74.929214f },
        { 1134.310547f, -170.699112f, -74.925247f },
        { 1128.690674f, -168.963409f, -74.918816f },
        { 1123.145752f, -171.097763f, -74.359314f },
        { 1117.911133f, -165.262787f, -74.359283f },
        { 1112.870483f, -162.624863f, -74.359283f },
        { 1108.336548f, -157.599533f, -74.359283f },
        { 1111.895264f, -154.200806f, -74.359283f },
        { 1117.868408f, -156.648788f, -74.359283f },
        { 1122.888062f, -162.170776f, -74.359283f },
        { 1129.102417f, -163.822556f, -74.915710f },
        { 1136.177246f, -160.575378f, -74.923256f },
        { 1127.515869f, -157.041992f, -74.359383f },
        { 1121.666260f, -153.644058f, -74.359383f },
        { 1121.433838f, -147.492661f, -74.359383f },
        { 1120.718262f, -140.469452f, -74.359383f },
        { 1114.421387f, -136.924011f, -74.359383f },
        { 1110.518799f, -134.185669f, -74.359383f },
        { 1114.167480f, -130.936417f, -74.359383f },
        { 1119.900269f, -134.169647f, -74.359383f },
        { 1121.670288f, -128.459579f, -74.359383f },
        { 1125.119873f, -132.346664f, -74.359383f },
        { 1129.198975f, -139.532639f, -74.359383f },
        { 1133.597046f, -143.092880f, -74.359383f },
        { 1137.954468f, -151.395020f, -74.912521f },
        { 1140.398438f, -158.380417f, -74.923073f },
        { 1146.890503f, -158.432693f, -74.924553f },
        { 1153.999634f, -159.946182f, -74.922302f },
        { 1161.258911f, -157.870483f, -74.912025f },
        { 1166.012573f, -151.766785f, -74.360878f },
        { 1173.023193f, -148.704147f, -74.362289f },
        { 1179.159668f, -145.643021f, -74.365143f },
        { 1183.978027f, -140.466003f, -74.366554f },
        { 1179.494019f, -136.199707f, -74.366554f },
        { 1171.818115f, -134.910217f, -74.366554f },
        { 1170.587280f, -128.367844f, -74.367973f },
        { 1164.752686f, -124.779434f, -74.367973f },
        { 1158.973389f, -125.129791f, -74.367554f },
        { 1153.131470f, -123.664513f, -74.367172f },
        { 1145.568848f, -123.436127f, -74.367172f },
        { 1144.694214f, -118.805183f, -74.367172f },
        { 1136.779175f, -123.912003f, -74.364265f },
        { 1129.895752f, -124.808479f, -74.361191f },
        { 1125.041626f, -122.111282f, -74.360916f },
        { 1129.744507f, -128.559723f, -74.360916f },
        { 1136.393188f, -133.072815f, -74.362343f },
        { 1143.445435f, -134.771057f, -74.363762f },
        { 1142.391602f, -141.804047f, -74.361740f },
        { 1150.744995f, -137.625809f, -74.361740f },
        { 1158.474854f, -138.051590f, -74.363190f },
        { 1165.371948f, -140.723526f, -74.363190f },
        { 1159.795288f, -149.657425f, -74.361389f },
        { 1150.447632f, -152.694427f, -74.915611f },
        { 1140.763306f, -151.349564f, -74.914192f },
        { 1138.952881f, -145.043320f, -74.359474f },
        { 1143.273926f, -138.425858f, -74.362305f },
        { 1138.266968f, -135.526764f, -74.362305f },
        { 1135.243530f, -146.028671f, -74.360924f },
        { 1125.772339f, -144.974258f, -74.359505f },
        { 1130.944580f, -147.879837f, -74.359505f },
        { 1126.780640f, -151.037399f, -74.359505f },
        { 1133.664551f, -155.691010f, -74.915947f },
        { 1144.954590f, -149.128143f, -74.912521f },
        { 1148.982788f, -144.167984f, -74.361069f },
        { 1154.625366f, -146.603104f, -74.361069f },
        { 1160.816406f, -143.987930f, -74.362335f },
        { 1156.096924f, -154.358261f, -74.915367f },
        { 1163.035400f, -163.726730f, -74.913551f },
        { 1167.758545f, -159.541000f, -74.359497f },
        { 1174.246704f, -155.803223f, -74.362320f },
        { 1187.809204f, -163.617676f, -74.361656f },
        { 1183.470459f, -149.433868f, -74.366341f },
        { 1173.979980f, -141.748077f, -74.366341f },
        { 1164.631958f, -134.942169f, -74.365700f },
        { 1164.728882f, -130.008118f, -74.365700f },
        { 1158.685913f, -131.756165f, -74.365700f },
        { 1152.424194f, -130.883636f, -74.365562f },
        { 1145.257324f, -129.019897f, -74.365562f },
        { 1138.212036f, -128.735413f, -74.362801f },
        { 1136.363037f, -139.278229f, -74.361107f },
        { 1131.146118f, -134.827316f, -74.361107f },
        { 1115.680420f, -150.204544f, -74.359505f },
        { 1156.445923f, -118.445473f, -72.688652f },
        { 1164.586426f, -120.754890f, -72.688652f },
        { 1179.254517f, -130.123932f, -72.689064f },
        { 1185.416870f, -135.677078f, -72.689064f },
        { 1190.558960f, -140.958969f, -72.689064f },
        { 1208.274780f, -157.475479f, -72.670921f },
        { 1210.881104f, -163.573151f, -74.313866f },
        { 1174.722168f, -170.376328f, -72.918083f },
        { 1122.948608f, -177.064041f, -72.919540f },
        { 1116.813965f, -170.924789f, -72.919533f },
        { 1107.659302f, -161.657532f, -72.796104f },
        { 1116.615967f, -125.678772f, -72.466469f }
    }
};

enum DwarfEquipment
{
    DWARF_EQUIP_MAIN_HAND_ONLY          = 1,
    DWARF_EQUIP_FROST_WEAPONS,
    DWARF_EQUIP_MAIN_HAND_SHIELD,

    DWARF_EQUIP_MAX
};

constexpr uint32 MAX_LIGHTNINGS_PER_ROUND{ 40 };
constexpr uint32 MAX_LIGHTNING_ROUNDS{ 20 };
constexpr size_t MAX_CHAINED_PLAYERS_SIZE{ 2 };
constexpr uint32 AMOUNT_OF_FROST_ORBS_TO_SPAWN{ 10 };
Position const _blizzardTargetSpawnPos{ 1114.286f, -134.715f, -74.359f };
Position const _equipmentChestPosition{ 1168.355f, -199.448f, -65.389f, 5.466f };
Position const _centerOfTheRoom{ 1153.109f, -146.495f, -74.361f };
Position const _jumpPosition{ 1129.82f, -148.45f, -74.f };

struct boss_dwarf_boss_four_AI : public BossAI
{
    boss_dwarf_boss_four_AI(Creature* creature) : BossAI(creature, DATA_BOSS_FOUR), _homePosition(me->GetHomePosition())
    {
        _chainedPlayers.reserve(MAX_CHAINED_PLAYERS_SIZE);
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_DISPEL, true);
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_STEAL_BENEFICIAL_BUFF, true);
        //! base validator checks for unit state casting
        //! but we want to keep casting our scheduler events even while casting, so clear it
        scheduler.ClearValidator();
    }

    void Reset() override
    {
        ChangeEqupiment(DWARF_EQUIP_MAIN_HAND_ONLY);
        _hammerCount = 0;
        _wipeoutCount = 0;
        me->SetAggressive();
        _hammerPhase = false;
        _phaseSwitch = true;
        _lightningPhase = true;
        _blizzardPhase = false;
        _lightningRoundCounter = 0;
        BossAI::Reset();
        JustReachedHome();
        LoadBossStats();
        _currentPhase = PHASE_BOSS_FOUR_LIGHTNING;
        Position pillarProtectionPos{ 1145.00f, -168.00f, -70.22f };
        if (Creature* knocker = me->SummonCreature(NPC_BOSS_FOUR_PILLAR_PROTECTION, pillarProtectionPos))
        {
            knocker->SetCanFly(true);
            knocker->SetDisableGravity(true);
        }
        me->SetImmuneToPC(true);
        _fightTimer = 0;
    }

    void LoadBossStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ BOSS_FOUR_STAT_ID_HEALTH, BOSS_FOUR_STAT_ID_MELEE_DAMAGE,
            BOSS_FOUR_STAT_ID_FIRST_TRANSITION_PCT, BOSS_FOUR_STAT_ID_SECOND_TRANSITION_PCT, BOSS_FOUR_STAT_ID_EMP_SHOCKWAVE,
            BOSS_FOUR_STAT_ID_STARFIRE_DAMAGE, BOSS_FOUR_STAT_ID_HAMMER_THROW_PCT, BOSS_FOUR_STAT_ID_MIND_WARP_COUNT,
            BOSS_FOUR_STAT_ID_FROST_NOVA_DAMAGE, BOSS_FOUR_STAT_ID_REFLECT_CHARGES_COUNT, BOSS_FOUR_STAT_ID_CLEAVE_DAMAGE,
            BOSS_FOUR_STAT_ID_ARCANE_EXPLOSION_DMG, BOSS_FOUR_STAT_ID_SOUL_CHARGE_DURATION, BOSS_FOUR_STAT_ID_COLD_SLAP_DAMAGE,
            BOSS_FOUR_STAT_ID_CHAIN_LIGHTNING_DMG, BOSS_FOUR_STAT_ID_LIGHTNING_NOVA_DMG_2, BOSS_FOUR_STAT_ID_LIGHTNING_SHIELD_CNT });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case BOSS_FOUR_STAT_ID_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case BOSS_FOUR_STAT_ID_MELEE_DAMAGE:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case BOSS_FOUR_STAT_ID_FIRST_TRANSITION_PCT:
                {
                    _firstTransitionPercentage = ref.second.StatValue;
                    break;
                }
                case BOSS_FOUR_STAT_ID_SECOND_TRANSITION_PCT:
                {
                    _secondTransitionPercentage = ref.second.StatValue;
                    break;
                }
                case BOSS_FOUR_STAT_ID_EMP_SHOCKWAVE:
                {
                    _empShockwaveDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_FOUR_STAT_ID_STARFIRE_DAMAGE:
                {
                    _starfireDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_FOUR_STAT_ID_HAMMER_THROW_PCT:
                {
                    _hammerHealthPct = ref.second.StatVariance;
                    break;
                }
                case BOSS_FOUR_STAT_ID_MIND_WARP_COUNT:
                {
                    _mindWarpPlayerCount = ref.second.StatValue;
                    break;
                }
                case BOSS_FOUR_STAT_ID_FROST_NOVA_DAMAGE:
                {
                    _frostNovaDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_FOUR_STAT_ID_REFLECT_CHARGES_COUNT:
                {
                    _reflectChargesCount = ref.second.StatValue;
                    break;
                }
                case BOSS_FOUR_STAT_ID_CLEAVE_DAMAGE:
                {
                    _cleavePctDamage = ref.second.StatValue;
                    break;
                }
                case BOSS_FOUR_STAT_ID_ARCANE_EXPLOSION_DMG:
                {
                    _arcaneExplosionDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_FOUR_STAT_ID_SOUL_CHARGE_DURATION:
                {
                    _soulChargeDuration = ref.second.StatValue;
                    break;
                }
                case BOSS_FOUR_STAT_ID_COLD_SLAP_DAMAGE:
                {
                    _coldSnapDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_FOUR_STAT_ID_CHAIN_LIGHTNING_DMG:
                {
                    _chainLightningDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_FOUR_STAT_ID_LIGHTNING_NOVA_DMG_2:
                {
                    _lightningNova2Damage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_FOUR_STAT_ID_LIGHTNING_SHIELD_CNT:
                {
                    _lightningShieldChargesCount = ref.second.StatValue;
                    break;
                }
                default:
                    break;
            }
        }
    }

    void JustReachedHome() override
    {
        BossAI::JustReachedHome();
        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_BOSS_FOUR_WORK);
    }

    void AttackStart(Unit* who) override
    {
        if (_lightningPhase)
            me->Attack(who, false);
        else
            BossAI::AttackStart(who);
    }

    void EnterEvadeMode() override
    {
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BOSS_FOUR_CLOUD_VISUAL);
        me->SetHomePosition(_homePosition);

        if (Unit * champion = instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
            if (champion->IsAIEnabled)
                champion->GetAI()->DoAction(ACTION_DWARF_WIPE);

        BossAI::EnterEvadeMode();
        me->StopMoving();
        me->GetMotionMaster()->MoveIdle();
        me->NearTeleportTo(_homePosition);
    }

    void SpellHitTarget(Unit* who, SpellInfo const* spell) override
    {
        if (spell->Id == SPELL_BOSS_FOUR_MARK_OF_CORRU)
        {
            if (Aura* aura = who->GetAura(SPELL_BOSS_FOUR_MARK_OF_CORRU))
            {
                aura->SetMaxDuration(35000);
                aura->RefreshDuration();
            }
        }
        else if (spell->Id == SPELL_BOSS_FOUR_THROW_SPEAR)
        {
            who->CastSpell(who, SPELL_BOSS_FOUR_DEFEANING_THUNDER, true);

            std::list<Player*> targets;
            Trinity::AnyPlayerInObjectRangeCheck check(who, 15.f, true);
            Trinity::PlayerListSearcherWithSharedVision<Trinity::AnyPlayerInObjectRangeCheck> searcher(who, targets, check);
            who->VisitNearbyWorldObject(8.f, searcher);
            targets.remove_if([&who](Player* _ref)
            {
                return _ref->GetGUID() == who->GetGUID();
            });

            if (_hammerCount != 1)
            {
                for (auto && player : targets)
                {
                    me->AddAura(SPELL_BOSS_FOUR_SOUL_CHARGE, player);
                    if (Aura* aura = player->GetAura(SPELL_BOSS_FOUR_SOUL_CHARGE))
                    {
                        aura->SetMaxDuration(_soulChargeDuration);
                        aura->RefreshDuration();
                    }
                }
            }
        }
    }

    void ChangeEqupiment(DwarfEquipment equip)
    {
        if (equip >= DWARF_EQUIP_MAX)
            return;

        switch (equip)
        {
            case DWARF_EQUIP_MAIN_HAND_ONLY:
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 45900);
                break;
            case DWARF_EQUIP_FROST_WEAPONS:
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 44821);
                break;
            case DWARF_EQUIP_MAIN_HAND_SHIELD:
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 50708);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1, 50729);
                break;
        }
    }

    void ModifyAuraDuration(uint32 auraId, int32 duration)
    {
        if (Aura* aura = me->GetAura(auraId))
        {
            aura->SetMaxDuration(duration);
            aura->RefreshDuration();
        }
    }

    void ScheduleLightningEvents()
    {
        events.Reset();
        events.ScheduleEvent(EVENT_BOSS_FOUR_LIGHTNING_SHIELD, 1s);
        events.ScheduleEvent(EVENT_BOSS_FOUR_CHAIN_LIGHTNING, 6s, 10s);
        events.ScheduleEvent(EVENT_BOSS_FOUR_LIGHTNING_NOVA, 10s, 20s);
        events.ScheduleEvent(EVENT_BOSS_FOUR_CHAINED_TARGETS, 20s);
        events.ScheduleEvent(EVENT_BOSS_FOUR_CHECK_ALIVE_PLAYERS, 10s);
    }

    void ScheduleIceEvents()
    {
        DoCastSelf(SPELL_BOSS_FOUR_FROST_ARMOR);

        DoCastSelf(SPELL_BOSS_FOUR_FROZEN_BITE);
        ModifyAuraDuration(SPELL_BOSS_FOUR_FROST_ARMOR, -1);

        events.ScheduleEvent(EVENT_BOSS_FOUR_MIND_WRAP, 6s, 10s);
        events.ScheduleEvent(EVENT_BOSS_FOUR_FROST_NOVA, 60s);
        events.ScheduleEvent(EVENT_BOSS_FOUR_CHECK_ALIVE_PLAYERS, 10s);
        me->SummonCreature(NPC_BOSS_FOUR_BLIZZARD_TARGET, _blizzardTargetSpawnPos);
        me->SetAggressive();
        DoZoneInCombat();

        scheduler.Schedule(3s, [this](TaskContext func)
        {
            auto& threatList = me->getThreatManager().getThreatList();
            for (auto && ref : threatList)
            {
                Unit* target = ObjectAccessor::GetUnit(*me, ref->getUnitGuid());
                if (!target)
                    continue;

                if (!target->ToPlayer())
                    continue;

                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _coldSnapDamage);
                target->CastCustomSpell(SPELL_BOSS_FOUR_COLD_SLAP, val, target, TRIGGERED_FULL_MASK, NullItemRef, (const AuraEffect*)nullptr, me->GetGUID());
            }

            func.Repeat(3s);
        });
    }

    void ScheduleFinalPhaseEvents()
    {
        events.Reset();
        DoCastSelf(SPELL_BOSS_FOUR_IRONFORM);
        ModifyAuraDuration(SPELL_BOSS_FOUR_IRONFORM, -1);

        events.ScheduleEvent(EVENT_BOSS_FOUR_SHIELD_WALL, 15s);
        events.ScheduleEvent(EVENT_BOSS_FOUR_REFLECT, 25s);
        events.ScheduleEvent(EVENT_BOSS_FOUR_VEZAX_SHIT, 40s);
        events.ScheduleEvent(EVENT_BOSS_FOUR_CLEAVE, 3s);
        events.ScheduleEvent(EVENT_BOSS_FOUR_CHECK_ALIVE_PLAYERS, 10s);
        DoCastSelf(SPELL_BOSS_FOUR_FRENZY, true);

        ModifyAuraDuration(SPELL_BOSS_FOUR_FRENZY, -1);

        me->SetAggressive();
        DoZoneInCombat();
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == WAYPOINT_MOTION_TYPE && pointId == POINT_BOSS_FOUR_PATH_END_POINT)
        {
            me->GetMotionMaster()->MoveJump(_jumpPosition, 20.f, 25.f);

            scheduler.Schedule(3s, [&](TaskContext func)
            {
                if (_currentPhase == PHASE_BOSS_FOUR_LIGHTNING)
                {
                    _phaseSwitch = false;
                    _lightningPhase = false;
                    DoZoneInCombat();
                    me->SetHomePosition(_homePosition);
                }

                switch (_currentPhase)
                {
                    case PHASE_BOSS_FOUR_LIGHTNING:
                        me->MonsterYell("Come here bastards, let's ride the lightning.", LANG_UNIVERSAL, nullptr);
                        ScheduleLightningEvents();
                        break;
                    case PHASE_BOSS_FOUR_FROST:
                        me->MonsterYell("You will freeze to death!", LANG_UNIVERSAL, nullptr);
                        ScheduleIceEvents();
                        break;
                    case PHASE_BOSS_FOUR_FINAL:
                        me->MonsterYell("I WILL CRUSH YOU!", LANG_UNIVERSAL, nullptr);
                        ScheduleFinalPhaseEvents();
                        break;
                }
                me->ClearUnitState(UNIT_STATE_UNATTACKABLE);
                me->SetImmuneToPC(false);
            });

            scheduler.Schedule(5s, [&](TaskContext func)
            {
                if (Unit * champion = instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
                {
                    champion->setFaction(250);
                    champion->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                    champion->CombatStart(me);
                    champion->Attack(me, false);
                }
            });
        }
        else if (type == POINT_MOTION_TYPE)
        {
            if (pointId == POINT_BOSS_FOUR_CHANGE_EQUIPMENT_FROST || pointId == POINT_BOSS_FOUR_CHANGE_EQUIPMENT_FINAL)
            {
                me->SetFacingTo(_equipmentChestPosition.GetOrientation());
                ChangeEqupiment(pointId == POINT_BOSS_FOUR_CHANGE_EQUIPMENT_FROST ? DWARF_EQUIP_FROST_WEAPONS : DWARF_EQUIP_MAIN_HAND_SHIELD);
                _currentPhase = pointId == POINT_BOSS_FOUR_CHANGE_EQUIPMENT_FROST ? PHASE_BOSS_FOUR_FROST : PHASE_BOSS_FOUR_FINAL;
                events.ScheduleEvent(pointId == POINT_BOSS_FOUR_CHANGE_EQUIPMENT_FROST ? EVENT_BOSS_FOUR_BEGIN_FROST_PHASE :
                    EVENT_BOSS_FOUR_BEGIN_FINAL_PHASE, 3s);
            }
        }
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        if (me->HealthBelowPctDamaged(_firstTransitionPercentage, damage) && !_hammerPhase)
        {
            me->CastStop();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            me->SetPassive();
            me->AttackStop();
            _hammerPhase = true;
            DoCastSelf(SPELL_EVIL_TELEPORT_HELLFORGE, true);
            me->NearTeleportTo(_homePosition);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BOSS_FOUR_CLOUD_VISUAL);
            events.Reset();
            events.ScheduleEvent(EVENT_BOSS_FOUR_THROW_WEAPON, 5s);
            events.ScheduleEvent(EVENT_BOSS_FOUR_CHECK_ALIVE_PLAYERS, 10s);
            me->RemoveAurasDueToSpell(SPELL_BOSS_FOUR_LIGHTNING_SHIELD);
            if (Unit * champion = instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
                if (champion->IsAIEnabled)
                    champion->GetAI()->DoAction(ACTION_DWARF_INTERPHASE);
            me->AddUnitState(UNIT_STATE_UNATTACKABLE);
            return;
        }

        if (me->HealthBelowPctDamaged(_secondTransitionPercentage, damage) && !_blizzardPhase)
        {
            me->CastStop();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            me->SetPassive();
            me->AttackStop();
            _blizzardPhase = true;
            DoCastSelf(SPELL_EVIL_TELEPORT_HELLFORGE, true);
            me->NearTeleportTo(_homePosition);
            events.Reset();
            events.ScheduleEvent(EVENT_BOSS_FOUR_BEGIN_WIPEOUT, 4s);
            me->RemoveAurasDueToSpell(SPELL_BOSS_FOUR_FROST_ARMOR);
            me->RemoveAurasDueToSpell(SPELL_BOSS_FOUR_FROZEN_BITE);
            scheduler.CancelAll();
            summons.DespawnEntry(NPC_BOSS_FOUR_BLIZZARD_TARGET);
            me->AddUnitState(UNIT_STATE_UNATTACKABLE);
            return;
        }
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
        if (me->IsInCombat() && !summon->IsTrigger())
            DoZoneInCombat(summon);
    }

    void EnterCombat(Unit* who) override
    {
        if (!instance->CheckRequiredBosses(DATA_BOSS_FOUR))
        {
            HandleRequiredBossFail();
            return;
        }

        _fightTimer = getMSTime();
        BossAI::EnterCombat(who);
        me->MonsterYell("Jonas? I'll smash your head on my anvil, moron.", LANG_UNIVERSAL, nullptr);
        events.ScheduleEvent(EVENT_BOSS_FOUR_LIGHTNING, 5s);
        events.ScheduleEvent(EVENT_BOSS_FOUR_CHECK_ALIVE_PLAYERS, 10s);
        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
        me->AddUnitState(UNIT_STATE_UNATTACKABLE);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_BOSS_FOUR_LIGHTNING:
                {
                    for (auto const& pos : _problematicSpawnPos)
                        me->SummonCreature(NPC_BOSS_FOUR_LIGHTNING_TARGET, pos);

                    for (uint32 i = 0; i < MAX_LIGHTNINGS_PER_ROUND; ++i)
                        me->SummonCreature(NPC_BOSS_FOUR_LIGHTNING_TARGET, Trinity::Containers::SelectRandomContainerElement(_lightningSpawnPos));

                    if (++_lightningRoundCounter >= MAX_LIGHTNING_ROUNDS)
                    {
                        me->AttackStop();
                        me->GetMotionMaster()->MovePath(me->GetEntry() * 10, false);
                    }
                    else
                        events.Repeat(2s);
                    break;
                }
                case EVENT_BOSS_FOUR_LIGHTNING_SHIELD:
                {
                    DoCastSelf(SPELL_BOSS_FOUR_LIGHTNING_SHIELD, true);
                    if (Aura* aura = me->GetAura(SPELL_BOSS_FOUR_LIGHTNING_SHIELD))
                        aura->SetCharges(_lightningShieldChargesCount);
                    events.Repeat(20s);
                    break;
                }
                case EVENT_BOSS_FOUR_CHAIN_LIGHTNING:
                {
                    std::vector<uint64> _possibleTargets;
                    auto& threatList = me->getThreatManager().getThreatList();
                    if (threatList.empty())
                    {
                        events.Repeat(10s, 15s);
                        break;
                    }

                    for (auto && ref : threatList)
                    {
                        Unit* source = ObjectAccessor::GetUnit(*me, ref->getUnitGuid());
                        if (!source)
                            continue;

                        if (!source->ToPlayer())
                            continue;

                        if (source->ToPlayer()->IsGameMaster())
                            continue;

                        if (source->GetDistance(me) < 15.f)
                            continue;

                        _possibleTargets.push_back(source->GetGUID());
                    }

                    Unit* castTarget = nullptr;
                    if (_possibleTargets.size() >= 4)
                        castTarget = ObjectAccessor::GetUnit(*me, Trinity::Containers::SelectRandomContainerElement(_possibleTargets));
                    else
                        castTarget = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.f, true);


                    if (castTarget)
                    {
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_BASE_POINT0, _chainLightningDamage);
                        me->CastCustomSpell(SPELL_BOSS_FOUR_CHAIN_LIGHTNING, val, castTarget, TRIGGERED_FULL_MASK);
                    }

                    events.Repeat(10s, 15s);
                    break;
                }
                case EVENT_BOSS_FOUR_LIGHTNING_NOVA:
                {
                    CustomSpellValues val;
                    val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 800.f); // base radius of spell is 100y
                    val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
                    me->CastCustomSpell(SPELL_BOSS_FOUR_MARK_OF_CORRU, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);

                    val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 4000.f); // equals to 8yards, base radius of spell is 20yards
                    val.AddSpellMod(SPELLVALUE_BASE_POINT0, _lightningNova2Damage);
                    me->CastCustomSpell(SPELL_BOSS_FOUR_LIGHTNING_NOVA_2, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);

                    events.Repeat(30s);
                    break;
                }
                case EVENT_BOSS_FOUR_CHAINED_TARGETS:
                {
                    _chainedPlayers.clear();
                    _chainedPlayers.shrink_to_fit();
                    std::vector<uint64> _targets;
                    auto& threat = me->getThreatManager().getThreatList();
                    for (auto && ref : threat)
                    {
                        Unit* target = ObjectAccessor::GetUnit(*me, ref->getUnitGuid());
                        if (!target)
                            continue;

                        if (!target->IsPlayer())
                            continue;

                        if (target->ToPlayer()->IsGameMaster())
                            continue;

                        if (target->GetDistance(me) >= 15.f)
                            _targets.push_back(target->GetGUID());

                        if (_targets.size() >= 2)
                            break;
                    }

                    if (_targets.size() >= 2)
                    {
                        _chainedPlayers.push_back(_targets.front());
                        _chainedPlayers.push_back(_targets.back());
                        std::for_each(_chainedPlayers.begin(), _chainedPlayers.end(), [this](uint64 guid)
                        {
                            if (Player* player = ObjectAccessor::GetPlayer(*me, guid))
                            {
                                player->CastSpell(player, SPELL_BOSS_FOUR_CLOUD_VISUAL, true);
                                if (Aura* aura = player->GetAura(SPELL_BOSS_FOUR_CLOUD_VISUAL))
                                {
                                    aura->SetMaxDuration(6000);
                                    aura->RefreshDuration();
                                }
                            }
                        });
                    }
                    else
                    {
                        DoCastSelf(SPELL_BOSS_FOUR_CLOUD_VISUAL, true);
                        ModifyAuraDuration(SPELL_BOSS_FOUR_CLOUD_VISUAL, 5000);

                        events.ScheduleEvent(EVENT_BOSS_FOUR_CHAINED_TARGETS_FAILURE, 2s);
                        events.Repeat(20s);
                        break;
                    }

                    events.ScheduleEvent(EVENT_BOSS_FOUR_CHECK_CHAINED_TARGETS, 5s);
                    events.Repeat(20s);
                    break;
                }
                case EVENT_BOSS_FOUR_CHAINED_TARGETS_FAILURE:
                {
                    CustomSpellValues val;
                    val.AddSpellMod(SPELLVALUE_BASE_POINT0, 10000000);
                    me->CastCustomSpell(SPELL_BOSS_FOUR_VORTEX_ENEMY, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                    me->RemoveAurasDueToSpell(SPELL_BOSS_FOUR_CLOUD_VISUAL);
                    instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BOSS_FOUR_CLOUD_VISUAL);
                    break;
                }
                case EVENT_BOSS_FOUR_CHECK_CHAINED_TARGETS:
                {
                    Unit* firstTarget = ObjectAccessor::GetUnit(*me, _chainedPlayers.front());
                    Unit* secondTarget = ObjectAccessor::GetUnit(*me, _chainedPlayers.back());
                    if (!firstTarget || !secondTarget)
                        break;

                    if (firstTarget->GetDistance(secondTarget) > 1.5f)
                    {
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_BASE_POINT0, _starfireDamage);
                        me->CastCustomSpell(SPELL_BOSS_FOUR_STARFIRE, val, firstTarget, TRIGGERED_FULL_MASK);
                        me->CastCustomSpell(SPELL_BOSS_FOUR_STARFIRE, val, secondTarget, TRIGGERED_FULL_MASK);

                        CustomSpellValues val2;
                        val2.AddSpellMod(SPELLVALUE_BASE_POINT0, _empShockwaveDamage);
                        val2.AddSpellMod(SPELLVALUE_RADIUS_MOD, 6500.f);
                        firstTarget->CastCustomSpell(SPELL_BOSS_FOUR_EMP_SHOCKWAVE, val2, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                        secondTarget->CastCustomSpell(SPELL_BOSS_FOUR_EMP_SHOCKWAVE, val2, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                    }

                    instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BOSS_FOUR_CLOUD_VISUAL);
                    break;
                }
                case EVENT_BOSS_FOUR_THROW_WEAPON:
                {
                    Unit* target = nullptr;
                    if (!_hammerCount)
                        target = instance->GetCreature(DATA_NPC_WANDERER_CHAMPION);
                    else
                    {
                        std::vector<uint64> _possibleTargets;
                        auto& players = me->GetMap()->GetPlayers();
                        for (auto && source : players)
                        {
                            Player* player = source.GetSource();
                            if (!player)
                                continue;

                            if (!player->IsAlive())
                                continue;

                            if (player->IsGameMaster())
                                continue;

                            if (player->GetDistance(_centerOfTheRoom) >= 55.5f)
                                continue;

                            _possibleTargets.push_back(player->GetGUID());
                        }

                        if (_possibleTargets.empty())
                        {
                            events.Repeat(4s);
                            break;
                        }
                        target = ObjectAccessor::GetPlayer(*me, Trinity::Containers::SelectRandomContainerElement(_possibleTargets));
                    }

                    if (target)
                    {
                        uint32 damage = target->GetMaxHealth() * _hammerHealthPct;
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_BASE_POINT1, damage);
                        me->CastCustomSpell(SPELL_BOSS_FOUR_THROW_SPEAR, val, target, TRIGGERED_FULL_MASK);
                        if (target->IsPlayer())
                            me->MonsterWhisper("Hephasto is aiming on you!", target->ToPlayer(), true);
                    }
                    if (_hammerCount >= 10 )
                        events.ScheduleEvent(EVENT_BOSS_FOUR_SWITCH_PHASE, 2s);
                    else
                        events.Repeat(4s);
                    ++_hammerCount;
                    break;
                }
                case EVENT_BOSS_FOUR_BEGIN_FROST_PHASE:
                {
                    me->GetMotionMaster()->MovePath(me->GetEntry() * 10, false);
                    break;
                }
                case EVENT_BOSS_FOUR_BEGIN_FINAL_PHASE:
                {
                    me->GetMotionMaster()->MovePath(me->GetEntry() * 10, false);
                    break;
                }
                case EVENT_BOSS_FOUR_SWITCH_PHASE:
                {
                    me->GetMotionMaster()->MovePoint(POINT_BOSS_FOUR_CHANGE_EQUIPMENT_FROST, _equipmentChestPosition);
                    break;
                }
                case EVENT_BOSS_FOUR_MIND_WRAP:
                {
                    std::list<Unit*> _possibleTargets;
                    SelectTargetList(_possibleTargets, [this](Unit* object)
                    {
                        return object->getPowerType() == POWER_MANA && me->GetVictim() && object->GetGUID() != me->GetVictim()->GetGUID() && object->ToPlayer();
                    }, _mindWarpPlayerCount, SELECT_TARGET_RANDOM);
                    for (auto && tar : _possibleTargets)
                        DoCast(tar, SPELL_BOSS_FOUR_MIND_WRAP, true);
                    events.Repeat(15s, 20s);
                    break;
                }
                case EVENT_BOSS_FOUR_FROST_NOVA:
                {
                    CustomSpellValues val;
                    val.AddSpellMod(SPELLVALUE_BASE_POINT0, _frostNovaDamage);
                    val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 500000.f);
                    me->CastCustomSpell(SPELL_BOSS_FOUR_FROST_NOVA, val, (Unit*)nullptr);
                    DoCastAOE(SPELL_BOSS_FOUR_FROST_NOVA);
                    events.Repeat(60s);
                    break;
                }
                case EVENT_BOSS_FOUR_FINAL_PHASE:
                {
                    me->GetMotionMaster()->MovePoint(POINT_BOSS_FOUR_CHANGE_EQUIPMENT_FINAL, _equipmentChestPosition);
                    break;
                }
                case EVENT_BOSS_FOUR_SHIELD_WALL:
                {
                    DoCastSelf(SPELL_BOSS_FOUR_SHIELD_WALL);
                    ModifyAuraDuration(SPELL_BOSS_FOUR_SHIELD_WALL, 6000);
                    events.Repeat(15s);
                    break;
                }
                case EVENT_BOSS_FOUR_REFLECT:
                {
                    DoCastSelf(SPELL_BOSS_FOUR_REFLECT);
                    if (Aura* aura = me->GetAura(SPELL_BOSS_FOUR_REFLECT))
                        aura->SetCharges(_reflectChargesCount);
                    events.Repeat(25s);
                    break;
                }
                case EVENT_BOSS_FOUR_VEZAX_SHIT:
                {
                    me->MonsterYell("Purrree STRENGTH!", LANG_UNIVERSAL, nullptr);
                    DoCastSelf(SPELL_BOSS_FOUR_SURGE_OF_DARKNESS, true);
                    events.Repeat(40s);
                    break;
                }
                case EVENT_BOSS_FOUR_CLEAVE:
                {
                    CustomSpellValues val;
                    val.AddSpellMod(SPELLVALUE_BASE_POINT0, _cleavePctDamage);
                    me->CastCustomSpell(SPELL_BOSS_FOUR_CLEAVE, val, me->GetVictim(), TRIGGERED_FULL_MASK);
                    events.Repeat(5s, 8s);
                    break;
                }
                case EVENT_BOSS_FOUR_BEGIN_WIPEOUT:
                {
                    if (++_wipeoutCount > 5)
                    {
                        summons.DespawnEntry(NPC_BOSS_FOUR_FIERY_ORB);
                        events.ScheduleEvent(EVENT_BOSS_FOUR_FINAL_PHASE, 3s);
                        break;
                    }
                    else
                        events.Repeat(12s);

                    CustomSpellValues val;
                    val.AddSpellMod(SPELLVALUE_BASE_POINT0, _arcaneExplosionDamage);
                    val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 250000.f);
                    me->CastCustomSpell(SPELL_BOSS_FOUR_ARCANE_EXPLOSION, val, (Unit*)nullptr);

                    summons.DespawnEntry(NPC_BOSS_FOUR_FIERY_ORB);

                    for (uint32 i = 0; i < AMOUNT_OF_FROST_ORBS_TO_SPAWN; i++)
                    {
                        Position pos = me->GetNearPositionFromPos(Trinity::Containers::SelectRandomContainerElement(_lightningSpawnPos), 2.5f);
                        if (Creature* orb = me->GetMap()->SummonCreature(NPC_BOSS_FOUR_FIERY_ORB, pos))
                        {
                            JustSummoned(orb);
                            orb->setFaction(35);
                            orb->SetCanFly(true);
                            orb->SetDisableGravity(true);
                            orb->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                            orb->GetMotionMaster()->MoveRandom(6.f);
                        }
                    }
                    break;
                }
                case EVENT_BOSS_FOUR_CHECK_ALIVE_PLAYERS:
                {
                    bool evade = true;
                    auto& threatList = me->getThreatManager().getThreatList();
                    for (auto && ref : threatList)
                    {
                        Unit* target = ref->getTarget();

                        if (!target || !target->IsPlayer() || target->ToPlayer()->IsGameMaster())
                            continue;

                        if (target->IsAlive())
                        {
                            evade = false;
                            break;
                        }
                    }

                    if (evade)
                        EnterEvadeMode();
                    events.Repeat(10s);
                    break;
                }
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        if (!_phaseSwitch)
            DoMeleeAttackIfReady();
        EnterEvadeIfOutOfCombatArea();
    }

    bool CheckEvadeIfOutOfCombatArea() const override
    {
        return me->GetDistance(me->GetHomePosition()) >= 130.f;
    }

    void JustDied(Unit* killer) override
    {
        if (Unit * champion = instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
            if (champion->IsAIEnabled)
                champion->GetAI()->DoAction(ACTION_DWARF_KILLED);

        me->MonsterYell("Black Witch.. forgive me.. he.. he is coming...", LANG_UNIVERSAL, nullptr);
        CheckCreatureRecord(killer, HELLFORGE_CREATURE_RECORD_MIN_VALUE + 3, RAID_DIFFICULTY_10MAN_NORMAL, "", 1, _fightTimer);
        BossAI::JustDied(killer);
    }

private:
    uint32 _lightningRoundCounter;
    uint32 _wipeoutCount;
    bool _lightningPhase;
    bool _phaseSwitch;
    bool _hammerPhase;
    bool _blizzardPhase;
    std::vector<uint64> _chainedPlayers;
    Position _homePosition;
    uint16 _hammerCount;

    uint32 _firstTransitionPercentage;
    uint32 _secondTransitionPercentage;
    uint32 _empShockwaveDamage;
    uint32 _starfireDamage;
    float _hammerHealthPct;
    uint32 _mindWarpPlayerCount;
    uint32 _frostNovaDamage;
    uint32 _reflectChargesCount;
    uint32 _cleavePctDamage;
    uint32 _arcaneExplosionDamage;
    uint32 _soulChargeDuration;
    uint32 _coldSnapDamage;
    uint32 _chainLightningDamage;
    uint32 _lightningNova2Damage;
    uint32 _lightningShieldChargesCount;
    BossFourPhase _currentPhase;
    uint32 _fightTimer;
};

struct npc_boss_four_lightning_target_AI : public ScriptedAI
{
    npc_boss_four_lightning_target_AI(Creature* creature) : ScriptedAI(creature)
    {
        me->SetPassive();
        HellforgeStatValues val;
        sWorldCache.GetStatValue(BOSS_FOUR_STAT_ID_LIGHTNING_NOVA_DMG, val);
        _lightningNovaDamage = urand((val.StatValue * val.StatVariance), val.StatValue);
    }

    void Reset() override
    {
        DoCastSelf(SPELL_BOSS_FOUR_BLUE_FIRE, true);
        _task.Schedule(3s, [&](TaskContext func)
        {
            DoCastSelf(SPELL_BOSS_FOUR_MOONFIRE_VISUAL, true);
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, _lightningNovaDamage);
            val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 500.f);
            me->CastCustomSpell(SPELL_BOSS_FOUR_LIGHTNING_NOVA, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
            me->RemoveAllAuras();
            me->DespawnOrUnsummon(2s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        _task.Update(diff);
    }
private:
    TaskScheduler _task;
    uint32 _lightningNovaDamage;
};

struct npc_boss_four_blizzard_target_AI : public ScriptedAI
{
    npc_boss_four_blizzard_target_AI(Creature* creature) : ScriptedAI(creature)
    {
        HellforgeStatValues val;
        sWorldCache.GetStatValue(BOSS_FOUR_STAT_ID_BLIZZARD_DAMAGE, val);
        _blizzarDamage = urand((val.StatValue * val.StatVariance), val.StatValue);

        me->SetWalk(true);
        _task.CancelAll();
        _task.Schedule(2s, [this](TaskContext func)
        {
            DoCastAOE(SPELL_BOSS_FOUR_BLIZZARD);
            func.Repeat(2s);
        });

        _task.Schedule(2s, [this](TaskContext func)
        {
            std::vector<uint64> _possibleTargets;
            auto& players = me->GetMap()->GetPlayers();
            for (auto && source : players)
            {
                Player* player = source.GetSource();
                if (!player)
                    continue;

                if (!player->IsAlive())
                    continue;

                if (player->GetDistance(_centerOfTheRoom) >= 55.5f)
                    continue;

                if (player->IsGameMaster())
                    continue;

                _possibleTargets.push_back(player->GetGUID());
            }

            if (!_possibleTargets.empty())
            {
                if (Player* player = ObjectAccessor::GetPlayer(*me, Trinity::Containers::SelectRandomContainerElement(_possibleTargets)))
                    me->GetMotionMaster()->MovePoint(10, player->GetPosition());
            }

            func.Repeat(5s);
        });
    }

    uint32 GetData(uint32 id) const override
    {
        if (id == BOSS_FOUR_STAT_ID_BLIZZARD_DAMAGE)
            return _blizzarDamage;
        return 0;
    }

    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }
    void UpdateAI(uint32 diff) override
    {
        _task.Update(diff);
    }
private:
    TaskScheduler _task;
    uint32 _blizzarDamage;
};

struct npc_boss_fiery_orb_AI : public ScriptedAI
{
    npc_boss_fiery_orb_AI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override { DoCastSelf(55928, true); }
    void EnterCombat(Unit* /*who*/) override { }
    void AttackStart(Unit* /*who*/) override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }
    void UpdateAI(uint32 /*diff*/) override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override { damage = 0; }

    void OnSpellClick(Unit* clicker, bool& /*result*/) override
    {
        if (clicker)
        {
            clicker->CastSpell(clicker, SPELL_BOSS_FOUR_SHIELD_VISUAL, true);
            if (Aura* aura = clicker->GetAura(SPELL_BOSS_FOUR_SHIELD_VISUAL))
            {
                aura->SetMaxDuration(3000);
                aura->RefreshDuration();
            }
        }
        me->DespawnOrUnsummon();
    }
};

struct npc_boss_four_pillar_protection : public ScriptedAI
{
    npc_boss_four_pillar_protection(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override { }
    void EnterCombat(Unit* /*who*/) override { }
    void AttackStart(Unit* /*who*/) override { }
    void MoveInLineOfSight(Unit* who) override
    {
        if (!who->ToPlayer())
            return;

        if (who->ToPlayer()->IsGameMaster())
            return;

        if (who->GetPositionZ() >= -72.35f && me->IsWithinDistInMap(who, 5.5f, false))
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, 75);
            me->CastCustomSpell(66797, val, who, TRIGGERED_FULL_MASK);
        }
    }
    void UpdateAI(uint32 /*diff*/) override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override { damage = 0; }
};

class spell_boss_four_lightning_shield : public AuraScript
{
    PrepareAuraScript(spell_boss_four_lightning_shield);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetProcTarget();
        if (!target)
            return false;

        if (target->GetMapId() == HELLFORGE_MAP_ID && !target->IsPlayer())
            return false;

        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_boss_four_lightning_shield::CheckProc);
    }
};

class spell_boss_four_frost_armor_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_boss_four_frost_armor_AuraScript);

    bool CheckProc(ProcEventInfo& /*eventInfo*/)
    {
        if (GetTarget() && GetTarget()->GetMapId() == HELLFORGE_MAP_ID)
            return roll_chance_i(5);
        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_boss_four_frost_armor_AuraScript::CheckProc);
    }
};

class spell_boss_four_frozen_bites_triggered_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_boss_four_frozen_bites_triggered_AuraScript);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
    {
        if (GetUnitOwner() && GetUnitOwner()->GetMapId() == HELLFORGE_MAP_ID)
            amount = -20;
    }

    void Register()
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_boss_four_frozen_bites_triggered_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_DECREASE_SPEED);
    }
};

class spell_boss_four_arcane_explosion_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_boss_four_arcane_explosion_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([](WorldObject* object) -> bool
        {
            if (!object->IsPlayer())
                return true;

            return object->ToUnit() && object->ToUnit()->HasAura(SPELL_BOSS_FOUR_SHIELD_VISUAL);
        });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_boss_four_arcane_explosion_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

class spell_boss_four_frost_nova_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_boss_four_frost_nova_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (GetCaster()->GetMapId() == HELLFORGE_MAP_ID)
            targets.remove_if([](WorldObject* object)
        {
            return !object->IsPlayer();
        });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_boss_four_frost_nova_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

class spell_boss_four_blizzard_damage_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_boss_four_blizzard_damage_AuraScript);

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        if (GetAura() && GetAura()->GetEffect(aurEff->GetEffIndex()) && GetCaster())
        {
            auto _damage = aurEff->GetAmount();
            if (GetCaster()->GetMapId() == HELLFORGE_MAP_ID && GetCaster()->ToCreature())
                _damage = GetCaster()->ToCreature()->AI()->GetData(BOSS_FOUR_STAT_ID_BLIZZARD_DAMAGE);

            GetAura()->GetEffect(aurEff->GetEffIndex())->SetAmount(_damage);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_boss_four_blizzard_damage_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

class spell_defeaning_thunder_boss_four : public SpellScript
{
    PrepareSpellScript(spell_defeaning_thunder_boss_four);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (GetCaster()->GetMapId() == HELLFORGE_MAP_ID)
        {
            targets.remove_if([this](WorldObject* object)
            {
                return GetCaster()->GetGUID() == object->GetGUID();
            });
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_defeaning_thunder_boss_four::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ALLY);
    }
};

class spell_gen_proc_on_players_only_hellforge : public AuraScript
{
    PrepareAuraScript(spell_gen_proc_on_players_only_hellforge);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetActor() && eventInfo.GetActionTarget())
        {
            if (eventInfo.GetActor()->GetMapId() == HELLFORGE_MAP_ID && eventInfo.GetActor()->GetTypeId() != TYPEID_PLAYER)
                return false;
        }
        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_gen_proc_on_players_only_hellforge::CheckProc);
    }
};

void AddSC_hellforge_boss_four()
{
    new CreatureAILoader<boss_dwarf_boss_four_AI>("boss_dwarf_boss_four");
    new CreatureAILoader<npc_boss_four_lightning_target_AI>("npc_boss_four_lightning_target");
    new CreatureAILoader<npc_boss_four_blizzard_target_AI>("npc_boss_four_blizzard_target");
    new CreatureAILoader<npc_boss_fiery_orb_AI>("npc_boss_fiery_orb");
    new CreatureAILoader<npc_boss_four_pillar_protection>("npc_boss_four_pillar_protection");

    new AuraScriptLoaderEx<spell_boss_four_frost_armor_AuraScript>("spell_boss_four_frost_armor");
    new AuraScriptLoaderEx<spell_boss_four_lightning_shield>("spell_boss_four_lightning_shield");
    new AuraScriptLoaderEx<spell_boss_four_frozen_bites_triggered_AuraScript>("spell_boss_four_frozen_bites_triggered");
    new SpellScriptLoaderEx<spell_boss_four_arcane_explosion_SpellScript>("spell_boss_four_arcane_explosion");
    new SpellScriptLoaderEx<spell_boss_four_frost_nova_SpellScript>("spell_boss_four_frost_nova");
    new AuraScriptLoaderEx<spell_boss_four_blizzard_damage_AuraScript>("spell_boss_four_blizzard_damage");
    new SpellScriptLoaderEx<spell_defeaning_thunder_boss_four>("spell_defeaning_thunder_boss_four");
    new AuraScriptLoaderEx<spell_gen_proc_on_players_only_hellforge>("spell_gen_proc_on_players_only_hellforge");
}
