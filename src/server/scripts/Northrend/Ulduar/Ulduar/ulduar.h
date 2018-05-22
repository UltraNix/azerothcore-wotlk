/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
Riztazz: chuj, a nie owns
*/

#ifndef DEF_ULDUAR_H
#define DEF_ULDUAR_H

enum UlduarEncounters
{
    MAX_ENCOUNTER                          = 15,

    TYPE_LEVIATHAN                         = 0,
    TYPE_IGNIS                             = 1,
    TYPE_RAZORSCALE                        = 2,
    TYPE_XT002                             = 3,
    TYPE_ASSEMBLY                          = 4,
    TYPE_KOLOGARN                          = 5,
    TYPE_AURIAYA                           = 6,
    TYPE_FREYA                             = 7,
    TYPE_HODIR                             = 8,
    TYPE_MIMIRON                           = 9,
    TYPE_THORIM                            = 10,
    TYPE_VEZAX                             = 11,
    TYPE_YOGGSARON                         = 12,
    TYPE_ALGALON                           = 13,
    TYPE_WATCHERS                          = 14
};

enum UlduarData
{
    // Flame Leviathan
    DATA_VEHICLE_SPAWN                     = 100,
    DATA_LIGHTNING_WALL1                   = 101,
    DATA_LIGHTNING_WALL2                   = 102,
    DATA_REPAIR_STATION1                   = 103,
    DATA_REPAIR_STATION2                   = 104,
    DATA_UNBROKEN_ACHIEVEMENT              = 105,

    // Razorscales Harpoon Fire State GUIDs
    DATA_HARPOON_FIRE_STATE_1              = 200,
    DATA_HARPOON_FIRE_STATE_2              = 201,
    DATA_HARPOON_FIRE_STATE_3              = 202,
    DATA_HARPOON_FIRE_STATE_4              = 203,

    // Mimiron's first vehicle (spawned by default)
    DATA_MIMIRON_LEVIATHAN_MKII            = 301,
    DATA_MIMIRON_VX001                     = 302,
    DATA_MIMIRON_ACU                       = 303,
    DATA_MIMIRON_DB_TARGET                 = 304,

    // Mimiron's Doors
    DATA_GO_MIMIRON_DOOR_1                 = 311,
    DATA_GO_MIMIRON_DOOR_2                 = 312,
    DATA_GO_MIMIRON_DOOR_3                 = 313,

    // Thorim
    DATA_THORIM_LEVER_GATE                 = 500,
    DATA_THORIM_LEVER                      = 501,
    DATA_THORIM_FENCE                      = 502,
    DATA_THORIM_FIRST_DOORS                = 503,
    DATA_THORIM_SECOND_DOORS               = 504,

    // Assembly of Iron
    DATA_STEELBREAKER                      = 20,
    DATA_MOLGEIM                           = 21,
    DATA_BRUNDIR                           = 22,

    // Algalon the Observer
    DATA_ALGALON_SUMMON_STATE              = 600,
    DATA_DESPAWN_ALGALON                   = 601,
    DATA_ALGALON_DEFEATED                  = 602,
    DATA_GIFT_OF_THE_OBSERVER              = 603,

    // Achievements
    DATA_DWARFAGEDDON                      = 700,

    // Tram
    DATA_CALL_TRAM                         = 710,

    DATA_EXPEDITION_COMMANDER              = 711,
    DATA_FREYA_PULLED                      = 712,
    DATA_ENTRANCE_EVENT_STARTED            = 713,
    DATA_DELLORAH                          = 714,
    DATA_RHYDIAN_ENTRANCE                  = 715,
    DATA_BRANN_ENTRANCE                    = 716,
    DATA_LOREKEEPER_NORG_ENTRANCE          = 717,
    DATA_GORAN_ENTRANCE                    = 718,
    DATA_STARTING_BARRIER                  = 719,
    DATA_RESPAWN_SENTRIES                  = 720,
    DATA_DESPAWN_SENTRIES                  = 721,
    DATA_SIF_BLIZZARD                      = 722,

    DATA_GET_INSTANCE_TEAM_ID              = 723,

    DATA_MIMIRON_HARDMODE                  = 724,
    DATA_HODIR_HARDMODE                    = 725,
    DATA_THORIM_HARDMODE                   = 726,
    DATA_FREYA_HARDMODE                    = 727
};

enum UlduarNPCs
{
    // General
    NPC_LEVIATHAN                          = 33113,
    NPC_IGNIS                              = 33118,
    NPC_RAZORSCALE                         = 33186,
    NPC_XT002                              = 33293,
    NPC_STEELBREAKER                       = 32867,
    NPC_MOLGEIM                            = 32927,
    NPC_BRUNDIR                            = 32857,
    NPC_KOLOGARN                           = 32930,
    NPC_AURIAYA                            = 33515,
    NPC_MIMIRON                            = 33350,
    NPC_HODIR                              = 32845,
    NPC_THORIM                             = 32865,
    NPC_FREYA                              = 32906,
    NPC_VEZAX                              = 33271,
    NPC_SARA                               = 33134,
    NPC_YOGGSARON                          = 33288,
    NPC_BRAIN_OF_YOGG_SARON                = 33890,
    NPC_ALGALON                            = 32871,

    // Razorscale
    NPC_HARPOON_FIRE_STATE                 = 33282,
    NPC_EXPEDITION_COMMANDER               = 33210,

    // Mimiron
    NPC_MIMIRON_LEVIATHAN_MKII             = 33432,
    NPC_MIMIRON_VX001                      = 33651,
    NPC_MIMIRON_ACU                        = 33670,
    NPC_MIMIRON_DB_TARGET                  = 33576,

    // Freya
    NPC_ELDER_BRIGHTLEAF                   = 32915,
    NPC_ELDER_STONEBARK                    = 32914,
    NPC_ELDER_IRONBRANCH                   = 32913,

    // Yogg-Saron
    NPC_FREYA_GOSSIP                       = 33241,
    NPC_HODIR_GOSSIP                       = 33213,
    NPC_THORIM_GOSSIP                      = 33242,
    NPC_MIMIRON_GOSSIP                     = 33244,
    NPC_FREYA_KEEPER                       = 33410,
    NPC_HODIR_KEEPER                       = 33411,
    NPC_MIMIRON_KEEPER                     = 33412,
    NPC_THORIM_KEEPER                      = 33413,

    // Flame Leviathan
    NPC_SALVAGED_SIEGE_ENGINE              = 33060,
    NPC_SALVAGED_SIEGE_ENGINE_TURRET       = 33067,
    NPC_VEHICLE_CHOPPER                    = 33062,
    NPC_SALVAGED_DEMOLISHER                = 33109,
    NPC_SALVAGED_DEMOLISHER_TURRET         = 33167,
    NPC_BRANN_BRONZEBEARD_FL               = 34119,

    // Algalon the Observer
    NPC_BRANN_BRONZBEARD_ALG               = 34064,
    NPC_AZEROTH                            = 34246,
    NPC_LIVING_CONSTELLATION               = 33052,
    NPC_ALGALON_STALKER                    = 33086,
    NPC_COLLAPSING_STAR                    = 32955,
    NPC_BLACK_HOLE                         = 32953,
    NPC_WORM_HOLE                          = 34099,
    NPC_ALGALON_VOID_ZONE_VISUAL_STALKER   = 34100,
    NPC_ALGALON_STALKER_ASTEROID_TARGET_01 = 33104,
    NPC_ALGALON_STALKER_ASTEROID_TARGET_02 = 33105,
    NPC_UNLEASHED_DARK_MATTER              = 34097,

    // Auriaya
    NPC_SANCTUM_SENTRY                     = 34014,
    NPC_SWARMING_GUARDIAN                  = 34034,

    // Misc
    NPC_FREYA_TRASH_0                      = 33431,
    NPC_FREYA_TRASH_1                      = 33528,
    NPC_FREYA_TRASH_2                      = 33527,
    NPC_FREYA_TRASH_3                      = 33525,
    NPC_FREYA_TRASH_4                      = 33526,
    NPC_FREYA_TRASH_5                      = 33430,
    NPC_FREYA_TRASH_6                      = 33355,
    NPC_FREYA_TRASH_7                      = 33354,
    NPC_HIGH_EXPLORER_DELLORAH             = 33701,
    NPC_ARCHMAGE_RHYDIAN                   = 33696,
    NPC_START_BRANN_BRONZEBEARD            = 33579,
    NPC_LOREKEEPER_NORG                    = 33686,
    NPC_GORAN_STEELBREAKER                 = 33622,
    NPC_SIF_BLIZZARD                       = 32879,
    NPC_POOL_OF_TAR_LEVIATHAN              = 33090,

    // Vezax Trash
    NPC_TRASH_TWILIGHT_GUARDIAN            = 33822,
    NPC_TRASH_TWILIGHT_PYROMANCER          = 33820,
    NPC_TRASH_FIRE_ELEMENTAL               = 33838,
    NPC_TRASH_TWILIGHT_ADHERENT            = 33818,
    NPC_TRASH_TWILIGHT_FROST_MAGE          = 33819,
    NPC_TRASH_FACELESS_HORROR              = 33772
};

enum UlduarGameObjects
{
    // Chests
    GO_KOLOGARN_CHEST                      = 195046,
    GO_KOLOGARN_CHEST_HERO                 = 195047,
    GO_THORIM_CHEST                        = 194312,
    GO_THORIM_CHEST_HERO                   = 194314,
    GO_HODIR_CHEST_NORMAL                  = 194307,
    GO_HODIR_CHEST_NORMAL_HERO             = 194308,
    GO_HODIR_CHEST_HARD                    = 194200,
    GO_HODIR_CHEST_HARD_HERO               = 194201,
    GO_FREYA_CHEST                         = 194330, // Normal, -2 - elder offset
    GO_FREYA_CHEST_HERO                    = 194331, // Hero, -2 - elder offset
    GO_MIMIRON_CHEST                       = 194789,
    GO_MIMIRON_CHEST_HARD                  = 194957,
    GO_MIMIRON_CHEST_HERO                  = 194956,
    GO_MIMIRON_CHEST_HERO_HARD             = 194958,
    GO_ALGALON_CHEST                       = 194821,
    GO_ALGALON_CHEST_HERO                  = 194822,

    // Flame Leviathan
    GO_REPAIR_STATION_TRAP                 = 194262,
    GO_LEVIATHAN_DOORS                     = 194630,
    GO_LIGHTNING_WALL1                     = 194905,
    GO_LIGHTNING_WALL2                     = 194416,
    GO_MIMIRONS_TARGETTING_CRYSTAL         = 194705,
    GO_FREYAS_TARGETTING_CRYSTAL           = 194704,
    GO_HODIRS_TARGETTING_CRYSTAL           = 194707,
    GO_THORIMS_TARGETTING_CRYSTAL          = 194706,
    GO_MIMIRONS_GENERATOR                  = 194664,
    GO_FREYAS_GENERATOR                    = 194663,
    GO_HODIRS_GENERATOR                    = 194665,
    GO_THORIMS_GENERATOR                   = 194666,
    GO_STORM_BEACON                        = 194414,
    GO_STARTING_BARRIER                    = 194484,

    // Middle
    GO_ARCHIVUM_DOORS                      = 194556,
    GO_ASSEMBLY_DOORS                      = 194554,
    GO_KOLOGARN_BRIDGE                     = 194232,
    GO_KOLOGARN_DOORS                      = 194553,
    GO_KEEPERS_GATE                        = 194255,
    GO_XT002_DOORS                         = 194631,
    GO_MIMIRON_TRAM                        = 194675,

    // Mimiron, Hodir, Vezax
    GO_MIMIRON_ELEVATOR                    = 194749,
    GO_MIMIRON_DOOR_1                      = 194776,
    GO_MIMIRON_DOOR_2                      = 194774,
    GO_MIMIRON_DOOR_3                      = 194775,
    GO_HODIR_FROZEN_DOOR                   = 194441,
    GO_HODIR_DOOR                          = 194634,
    GO_VEZAX_DOOR                          = 194750,
    GO_HODIR_ENTRANCE_DOOR                 = 194442,

    GO_SNOW_MOUND                          = 194907,

    // Thorim
    GO_ARENA_LEVER_GATE                    = 194560,
    GO_ARENA_LEVER                         = 194264,
    GO_ARENA_FENCE                         = 194559,
    GO_FIRST_COLOSSUS_DOORS                = 194557,
    GO_SECOND_COLOSSUS_DOORS               = 194558,

    // Yogg-Saron
    GO_YOGG_SARON_DOORS                    = 194773,

    // Algalon the Observer
    GO_CELESTIAL_PLANETARIUM_ACCESS_10     = 194628,
    GO_CELESTIAL_PLANETARIUM_ACCESS_25     = 194752,
    GO_DOODAD_UL_SIGILDOOR_01              = 194767,
    GO_DOODAD_UL_SIGILDOOR_02              = 194911,
    GO_DOODAD_UL_SIGILDOOR_03              = 194910,
    GO_DOODAD_UL_UNIVERSEFLOOR_01          = 194715,
    GO_DOODAD_UL_UNIVERSEFLOOR_02          = 194716,
    GO_DOODAD_UL_UNIVERSEGLOBE01           = 194148,
    GO_DOODAD_UL_ULDUAR_TRAPDOOR_03        = 194253,
    GO_GIFT_OF_THE_OBSERVER_10             = 194821,
    GO_GIFT_OF_THE_OBSERVER_25             = 194822
};

enum UlduarMisc
{
    // Flame Leviathan
    VEHICLE_POS_START                      = 0,
    VEHICLE_POS_LEVIATHAN                  = 1,
    VEHICLE_POS_NONE                       = 2,

    EVENT_TOWER_OF_STORM_DESTROYED         = 21031,
    EVENT_TOWER_OF_FROST_DESTROYED         = 21032,
    EVENT_TOWER_OF_FLAMES_DESTROYED        = 21033,
    EVENT_TOWER_OF_LIFE_DESTROYED          = 21030,

    ACTION_LEVIATHAN_REFRESH_TOWERS        = -1,
    ACTION_TOWER_OF_STORM_DESTROYED        = 1,
    ACTION_TOWER_OF_FROST_DESTROYED        = 2,
    ACTION_TOWER_OF_FLAMES_DESTROYED       = 3,
    ACTION_TOWER_OF_LIFE_DESTROYED         = 4,


    // Algalon the Observer
    WORLD_STATE_ALGALON_DESPAWN_TIMER      = 4131,
    WORLD_STATE_ALGALON_TIMER_ENABLED      = 4132,

    EVENT_UPDATE_ALGALON_TIMER             = 1,
    ACTION_FEEDS_ON_TEARS_FAILED           = 0,
    ACTION_INIT_ALGALON                    = 1,
    ACTION_DESPAWN_ALGALON                 = 2,

    TIMER_ALGALON_DEFEATED                 = 300,
    TIMER_ALGALON_TO_SUMMON                = 200,
    TIMER_ALGALON_SUMMONED                 = 100,

    KEEPER_FREYA                           = 0,
    KEEPER_HODIR                           = 1,
    KEEPER_MIMIRON                         = 2,
    KEEPER_THORIM                          = 3,

    // Achievement
    SPELL_DWARFAGEDDON                     = 65387 // not exists in dbc
};

Position const AlgalonSummonPos = {1632.531f, -304.8516f, 450.1123f, 1.530165f};
Position const AlgalonLandPos   = {1632.668f, -302.7656f, 417.3211f, 1.530165f};

#endif
