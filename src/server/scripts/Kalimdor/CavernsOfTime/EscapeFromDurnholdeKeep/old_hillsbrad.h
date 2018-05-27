#ifndef DEF_OLD_HILLSBRAD_H
#define DEF_OLD_HILLSBRAD_H

#define DataHeader "OH"

enum DataIds
{
    DATA_ESCORT_PROGRESS                = 0,

    DATA_BOMBS_PLACED                   = 10,
    DATA_THRALL_REPOSITION,
    DATA_THRALL_ADD_FLAG,
    DATA_THRALL,
    DATA_TARETHA,
    DATA_ATTEMPTS_COUNT
};

enum NpcIds
{
    NPC_EROZION                         = 18723,
    NPC_THRALL                          = 17876,
    NPC_TARETHA                         = 18887,
    NPC_EPOCH_HUNTER                    = 18096,
    NPC_LIEUTENANT_DRAKE                = 17848,

    NPC_LODGE_QUEST_TRIGGER             = 20155,
    NPC_ORC_PRISONER                    = 18598,

    NPC_DURNHOLDE_ARMORER               = 18764,
    NPC_DURNHOLDE_WARDEN                = 17833,
    NPC_DURNHOLDE_VETERAN               = 17860,
    NPC_DURNHOLDE_MAGE                  = 17860,
    NPC_DURNHOLDE_SENTRY                = 17860,

    NPC_CAPTAIN_SKARLOC                 = 17862,
    NPC_SKARLOC_MOUNT                   = 18798,

    NPC_LORDAERON_SENTRY                = 17815,
    NPC_LORDAERON_WATCHMAN              = 17814
};

enum GobjectIds
{
    GO_BARREL                           = 182589,
    GO_ROARING_FLAME                    = 182592,
    GO_PRISON_DOOR                      = 184393
};

enum MiscIds
{
    QUEST_DIVERSION                     = 10283,
    WORLD_STATE_BARRELS_PLANTED         = 2436,
    SKARLOC_MOUNT_MODEL                 = 18223,

    ENCOUNTER_PROGRESS_NONE             = 0,
    ENCOUNTER_PROGRESS_BARRELS,
    ENCOUNTER_PROGRESS_DRAKE_KILLED,
    ENCOUNTER_PROGRESS_THRALL_ARMORED,
    ENCOUNTER_PROGRESS_AMBUSHES_1,
    ENCOUNTER_PROGRESS_SKARLOC_KILLED,
    ENCOUNTER_PROGRESS_TARREN_MILL,
    ENCOUNTER_PROGRESS_TARETHA_MEET,
    ENCOUNTER_PROGRESS_EPOCH_KILLED,
    ENCOUNTER_PROGRESS_FINISHED,

    EVENT_INITIAL_BARRELS_FLAME         = 1,
    EVENT_FINAL_BARRELS_FLAME,
    EVENT_SUMMON_LIEUTENANT,
    EVENT_THRALL_REPOSITION,

    INSTANCE_POSITIONS_COUNT            = 3,
    THRALL_POSITIONS_COUNT              = 5
};

#endif
