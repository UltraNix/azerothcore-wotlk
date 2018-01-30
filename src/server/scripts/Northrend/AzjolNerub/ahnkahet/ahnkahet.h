#ifndef DEF_AHNKAHET_H
#define DEF_AHNKAHET_H

enum AKData
{
    BOSS_NADOX,
    BOSS_TALDARAM,
    BOSS_JEDOGA,
    BOSS_VOLAZJ,
    BOSS_AMANITAR,
    MAX_ENCOUNTER,

    DATA_TALDARAM_SHIELD,
    DATA_SPHERE_EVENT_1,
    DATA_SPHERE_EVENT_2
};

enum AKCreatureEntries
{
    NPC_ELDER_NADOX                     = 29309,
    NPC_PRINCE_TALDARAM                 = 29308,
    NPC_JEDOGA_SHADOWSEEKER             = 29310,
    NPC_HERALD_JOLAZJ                   = 29311,
    NPC_AMANITAR                        = 30258,

    // Elder Nadox
    NPC_AHNKAHAR_GUARDIAN               = 30176,
    NPC_AHNKAHAR_SWARMER                = 30178,
    
    // Amanitar
    NPC_HEALTHY_MUSHROOM                = 30391,
    NPC_POISONOUS_MUSHROOM              = 30435,

    // Jedoga Shadowseeker
    NPC_TWILIGHT_INITIATE               = 30114,
    NPC_TWILIGHT_VOLUNTEER              = 30385,
    NPC_TWILIGHT_WORSHIPPER             = 30111,
    NPC_JEDOGA_CONTROLLER               = 30181
};

enum AKGameObjectEntries
{
    GO_TALDARAM_SHIELD                  = 193564,
    GO_TALDARAM_WEB_GATE                = 192236,
    GO_TALDARAM_SPHERE_1                = 193093,
    GO_TALDARAM_SPHERE_2                = 193094
};

#endif
