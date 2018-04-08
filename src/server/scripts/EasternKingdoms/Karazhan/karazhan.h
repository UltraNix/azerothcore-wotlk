/*
 * Rewritten by Afgann
 */

#ifndef DEF_KARAZHAN_H
#define DEF_KARAZHAN_H

#define DataHeader "KA"

enum DataTypes
{
    BOSS_ATTUMEN,
    BOSS_MOROES,
    BOSS_MAIDEN,
    BOSS_SERVANT_QUARTERS,
    BOSS_OPERA,
    BOSS_CURATOR,
    BOSS_ARAN,
    BOSS_TERESTIAN,
    BOSS_NETHERSPITE,
    BOSS_CHESS,
    BOSS_MALCHEZZAR,
    BOSS_NIGHTBANE,

    DATA_KILREK,

    DATA_OPERA_PERFORMANCE,
    DATA_OPERA_OZ_DEATHCOUNT,

    DATA_GO_CURTAINS,
    DATA_GO_STAGEDOORLEFT,
    DATA_GO_STAGEDOORRIGHT,
    DATA_GO_LIBRARY_DOOR,
    DATA_GO_MASSIVE_DOOR,
    DATA_GO_NETHER_DOOR,
    DATA_GO_GAME_DOOR,
    DATA_GO_GAME_EXIT_DOOR,

    DATA_IMAGE_OF_MEDIVH,
    DATA_ECHO_OF_MEDIVH,
    DATA_MASTERS_TERRACE_DOOR_1,
    DATA_MASTERS_TERRACE_DOOR_2,
    DATA_GO_SIDE_ENTRANCE_DOOR,

    DATA_SERVANT_QUARTERS_TRASH,
    DATA_SERVANT_QUARTERS_AGGRO,
    DATA_SELECTED_RARE,
    DATA_DUST_COVERED_CHEST,
    DATA_ROMULO,
    DATA_JULIANNE,
    DATA_BARNES,
    DATA_CRONE,
    DATA_DOROTHEE,
    DATA_MIDNIGHT,
    DATA_BLACKENED_URN,
    DATA_STRAWMAN,
    DATA_TINHEAD,
    DATA_ROAR,
    DATA_GO_BLACKENED_URN
};

enum InstanceOperaEvents
{
    OPERA_EVENT_RED_RIDING_HOOD,
    OPERA_EVENT_WIZARD_OF_OZ,
    OPERA_EVENT_ROMULO_AND_JULIANNE
};

enum KarazhanNPCs
{
    NPC_HYAKISS_THE_LURKER              = 16179,
    NPC_SHADIKITH_THE_GLIDER            = 16180,
    NPC_ROKAD_THE_RAVAGER               = 16181,
    NPC_KILREK                          = 17229,
    NPC_TERESTIAN                       = 15688,
    NPC_MOROES                          = 15687,
    NPC_ECHO_OF_MEDIVH                  = 16816,
    NPC_IMAGE_OF_MEDIVH                 = 17651,
    NPC_MALCHEZAAR                      = 15690,
    NPC_NETHERSPITE                     = 15689,
    NPC_ROMULO                          = 17533,
    NPC_JULIANNE                        = 17534,
    NPC_BARNES                          = 16812,
    NPC_CRONE                           = 18168,
    NPC_DOROTHEE                        = 17535,
    NPC_STRAWMAN                        = 17543,
    NPC_TINHEAD                         = 17547,
    NPC_ROAR                            = 17546,
    NPC_ATTUMEN_UNMOUNTED               = 15550,
    NPC_ATTUMEN_MOUNTED                 = 16152,
    NPC_MIDNIGHT                        = 16151,
    NPC_NIGHTBANE                       = 17225
};

enum KarazhanGOs
{
    GO_STAGEDOORLEFT                    = 184278,
    GO_STAGEDOORRIGHT                   = 184279,
    GO_CURTAINS                         = 183932,
    GO_LIBRARY_DOOR                     = 184517,
    GO_MASSIVE_DOOR                     = 185521,
    GO_SIDE_ENTRANCE_DOOR               = 184275,
    GO_GAME_DOOR                        = 184276,
    GO_GAME_EXIT_DOOR                   = 184277,
    GO_NETHER_DOOR                      = 185134,
    GO_MASTERS_TERRACE_DOOR_1           = 184274,
    GO_MASTERS_TERRACE_DOOR_2           = 184280,
    GO_DUST_COVERED_CHEST               = 185119,
    GO_BLACKENED_URN                    = 194092
};

#endif
