#ifndef DEF_ZULFARRAK_H
#define DEF_ZULFARRAK_H

enum ZulFarrakData
{
    ENTRY_ZUM_RAH       = 7271,
    ENTRY_BLY           = 7604,
    ENTRY_RAVEN         = 7605,
    ENTRY_ORO           = 7606,
    ENTRY_WEEGLI        = 7607,
    ENTRY_MURTA         = 7608,
    ENTRY_GAHZRILLA     = 7273,

    GO_END_DOOR         = 146084,

    EVENT_PYRAMID       = 1,
    EVENT_GAHZRILLA,

    PATH_ADDS           = 81553
};

enum PyramidPhases
{
    PYRAMID_NOT_STARTED, //default
    PYRAMID_CAGES_OPEN, //happens in GO hello for cages
    PYRAMID_ARRIVED_AT_STAIR, //happens in Weegli's movementinform
    PYRAMID_WAVE_1,
    PYRAMID_PRE_WAVE_2,
    PYRAMID_WAVE_2,
    PYRAMID_PRE_WAVE_3,
    PYRAMID_WAVE_3,
    PYRAMID_KILLED_ALL_TROLLS,
};

#endif
