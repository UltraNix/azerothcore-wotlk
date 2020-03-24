#ifndef DEF_SHADOWFANG_H
#define DEF_SHADOWFANG_H

constexpr auto DataHeader = "SF";

enum SKEncounters
{
    BOSS_FENRUS,
    BOSS_NANDOS,
    BOSS_ARUGAL,
    BOSS_RETHILGORE,
    MAX_ENCOUNTERS
};

enum SKDataTypes
{
    DATA_COURTYARD,
    DATA_VOIDWALKER_EVENT,
    DATA_VOIDWALKER_DIES,
    DATA_HORDE_ESCORT,
    DATA_ALLIANCE_ESCORT,
    DATA_HORDE_LEVER,
    DATA_ALLIANCE_LEVER,
    DATA_SORCERER_DOOR,
    DATA_COURTYARD_DOOR
};

enum SKEvents
{
    EVENT_ARUGAL_FENRUS             = 1,
    EVENT_ARUGAL_FENRUS_SPAWN,
    EVENT_TALK_ALLIANCE
};

enum SKCreatures
{
    NPC_ALLIANCE_ESCORT             = 3850,
    NPC_HORDE_ESCORT                = 3849,
    NPC_ARCHMAGE_ARUGAL             = 4275,
    NPC_ARUGAL_VOIDWALKER           = 4627,
    NPC_FENRUS                      = 4274
};

enum SKGameObjects
{
    GO_COURTYARD_DOOR               = 18895,
    GO_SORCERER_DOOR                = 18972,
    GO_ARUGAL_DOOR                  = 18971,
    GO_ALLIANCE_LEVER               = 18901,
    GO_HORDE_LEVER                  = 18900
};

#endif
