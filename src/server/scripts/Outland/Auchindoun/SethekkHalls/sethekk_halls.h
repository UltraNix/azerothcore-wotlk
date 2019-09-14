/*
REWRITTEN BY XINEF
*/

#ifndef DEF_SETHEKK_HALLS_H
#define DEF_SETHEKK_HALLS_H

enum eTypes
{
    DATA_IKISSDOOREVENT = 1,
    TYPE_ANZU_ENCOUNTER = 2,
    DATA_ANZU_STARTEVENT = 3,
};

enum SethekkHalls
{
    BOSS_IKIS       = 1,
    BOSS_DARKWEAVER = 2,
    BOSS_ANZU       = 3,

    ENCOUNTERS      = 3
};

enum eIds
{
    NPC_VOICE_OF_THE_RAVEN_GOD  = 21851,
    NPC_ANZU                    = 23035,
    NPC_RAVEN_GOD_CASTER        = 23058,
    NPC_RAVEN_GOD_TARGET        = 23057,
    NPC_RAVEN_GOD_PORTAL        = 23046,

    GO_IKISS_DOOR               = 177203,
    GO_THE_TALON_KINGS_COFFER   = 187372,
    GO_RIFT                     = 185595,
    GO_MOONSTONE                = 185590,
    GO_RAVENS_CLAW              = 185554,

    NPC_HAWK_SPIRIT             = 23134,
    NPC_EAGLE_SPIRIT            = 23136,
    NPC_FALCON_SPIRIT           = 23135,
    NPC_BROOD_OF_ANZU           = 23132,
    NPC_AVIAN_FLYER             = 21931,
};

enum anzuEvents
{
    EVENT_ANZU_1        = 1,
    EVENT_ANZU_2,
    EVENT_ANZU_3,
    EVENT_ANZU_4,
    EVENT_ANZU_5,
    EVENT_SPAWN_LAKKA
};

enum anzuSpellIDs
{
    SPELL_PORTAL            = 39952,
    SPELL_SUMMONING_BEAMS   = 39978,
    SPELL_RED_LIGHTNING     = 39990,
    SPELL_SHAKE_CAMERA      = 39983,
    SPELL_PURPLE_BANISH     = 32566
};

#endif
