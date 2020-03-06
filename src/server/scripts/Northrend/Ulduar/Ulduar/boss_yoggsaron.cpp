
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "ulduar.h"
#include "ScriptedEscortAI.h"
#include "SpellAuras.h"
#include "PassiveAI.h"
#include "Opcodes.h"
#include "Player.h"
#include "Chat.h"
#include "MoveSplineInit.h"

enum YoggSpells
{
    // KEEPERS
    SPELL_KEEPER_ACTIVE                         = 62647,
    SPELL_MIMIRON_PASSIVE                       = 62671,
    SPELL_THORIM_PASSIVE                        = 62702,
    SPELL_HODIR_PASSIVE                         = 62650,
    SPELL_FREYA_PASSIVE                         = 62670,

    SPELL_DESTABILIZATION_MATRIX                = 65206,
    SPELL_DESTABILIZATION_MATRIX_ATTACK         = 65210,
    SPELL_SANITY_WELL_VISUAL                    = 63288,
    SPELL_SANITY_WELL_BUFF                      = 64169,
    SPELL_PROTECTIVE_GAZE                       = 64174, // COOLDOWN 25 SECS BEFORE NEXT USE
    SPELL_HODIR_FLASH_FREEZE                    = 64175,
    SPELL_CONJURE_SANITY_WELL                   = 64170,

    SPELL_TITANIC_STORM_PASSIVE                 = 64171,
    SPELL_WEAKENED                              = 64162,

    // GLOBAL
    SPELL_SANITY_BASE                           = 63786,
    SPELL_SANITY                                = 63050,
    SPELL_EXTINGUISH_ALL_LIFE                   = 64166,
    SPELL_CLOUD_VISUAL                          = 63084,
    SPELL_SUMMON_GUARDIAN_OF_YS                 = 63031,
    SPELL_INSANE1                               = 63120,
    SPELL_INSANE2                               = 64464,
    SPELL_INSANE_PERIODIC                       = 64554, // this checks if player dc'ed and insanes him instantly after logging in
    //! summoning position adjusted in spell script
    SPELL_SUMMON_CRUSHER_TENTACLE               = 64139,
    SPELL_SUMMON_CURRUPTOR_TENTACLE             = 64143,
    SPELL_SUMMON_CONSTRICTOR_TENTACLES_AURA     = 64132,
    SPELL_SUMMON_CONSTRICTOR_TENTACLE           = 64133,
    SPELL_SUMMON_IMMORTAL_GUARDIAN              = 64158,

    // SARA P1
    SPELL_SARAS_FAVOR                           = 63138,
    SPELL_SARAS_FAVOR_TARGET_SELECTOR           = 63747,
    SPELL_SARAS_BLESSING                        = 63134,
    SPELL_SARAS_BLESSING_TARGET_SELECTOR        = 63745,
    SPELL_SARAS_ANGER                           = 63147,
    SPELL_SARAS_ANGER_TARGET_SELECTOR           = 63744,
    SPELL_SHADOWY_BARRIER                       = 64775,

    // GUARDIANS OF YOGG-SARON
    SPELL_SHADOW_NOVA                           = 62714,
    SPELL_DOMINATE_MIND                         = 63042,
    SPELL_DARK_VOLLEY                           = 63038,

    // SARA P2
    SPELL_SARA_PSYCHOSIS_10                     = 63795,
    SPELL_SARA_PSYCHOSIS_25                     = 65301,
    SPELL_MALADY_OF_THE_MIND                    = 63830,
    SPELL_MALADY_OF_THE_MIND_TRIGGER            = 63881,
    SPELL_BRAIN_LINK                            = 63802,
    SPELL_BRAIN_LINK_DAMAGE                     = 63803,
    SPELL_BRAIN_LINK_OK                         = 63804,

    SPELL_DEATH_RAY_DAMAGE_VISUAL               = 63886,
    SPELL_DEATH_RAY_ORIGIN_VISUAL               = 63893,
    SPELL_DEATH_RAY_WARNING                     = 63882,
    SPELL_DEATH_RAY_DAMAGE                      = 63883,
    SPELL_DEATH_RAY_DAMAGE_REAL                 = 63884,
    SPELL_SHADOW_NOVA_GUARDIAN_10               = 62714,
    SPELL_SHADOW_NOVA_GUARDIAN_25               = 65209,
    SPELL_SHADOW_NOVA_GUARDIAN_TARGET_SARA      = 65719,

    // YOGG-SARON P2
    SPELL_SHADOW_BARRIER                        = 63894,
    SPELL_P3_TRANSFORM_YOGG                     = 63895,
    SPELL_KNOCK_AWAY                            = 64022,
    SPELL_YOGG_DEATH_ANIMATION                  = 64165,

    // TENTACLES
    SPELL_VOID_ZONE_SMALL                       = 64384,
    SPELL_VOID_ZONE_LARGE                       = 64017,
    SPELL_TENTACLE_ERUPT                        = 64144,

    // CRUSHER TENTACLE
    SPELL_CRUSH                                 = 64146,
    SPELL_DIMINISH_POWER                        = 64145,
    SPELL_FOCUSED_ANGER                         = 57688,
    SPELL_ERUPT_TENTACLE                        = 64144,

    // CONSTRICTOR TENTACLE
    SPELL_LUNGE                                 = 64123,
    SPELL_SQUEEZE_10                            = 64125,
    SPELL_SQUEEZE_25                            = 64126,

    // CORRUPTOR TENTACLE
    SPELL_APATHY                                = 64156,
    SPELL_BLACK_PLAGUE                          = 64153,
    SPELL_CURSE_OF_DOOM                         = 64157,
    SPELL_DRAINING_POISON                       = 64152,

    // MISC
    SPELL_REVEALED_TENTACLE                     = 64012,
    SPELL_IN_THE_MAWS_OF_THE_OLD_GOD            = 64184,

    // BRAIN OF YOGG-SARON
    SPELL_SHATTERED_ILLUSION                    = 64173,
    SPELL_INDUCE_MADNESS                        = 64059,
    SPELL_BRAIN_HURT_VISUAL                     = 64361,

    // PORTALS
    SPELL_TELEPORT_TO_CHAMBER                   = 63997,
    SPELL_TELEPORT_TO_ICECROWN                  = 63998,
    SPELL_TELEPORT_TO_STORMWIND                 = 63989,
    SPELL_TELEPORT_BACK                         = 63992,
    SPELL_CANCEL_ILLUSION_AURA                  = 63993,
    SPELL_ILLUSION_ROOM                         = 63988,

    // LAUGHING SKULL AND INFLUENCE TENTACLE AND OTHERS
    SPELL_LUNATIC_GAZE                          = 64167,
    SPELL_GRIM_REPRISAL                         = 63305,
    SPELL_GRIM_REPRISAL_DAMAGE                  = 64039,
    SPELL_DEATHGRASP                            = 63037,

    // YOGG-SARON P3
    SPELL_LUNATIC_GAZE_YS                       = 64163,
    SPELL_DEAFENING_ROAR                        = 64189,
    SPELL_SHADOW_BEACON                         = 64465,

    // IMMORTAL GUARDIAN
    SPELL_SIMPLE_TELEPORT                       = 64195,
    SPELL_EMPOWERED                             = 65294,
    SPELL_EMPOWERED_PASSIVE                     = 64161,
    SPELL_DRAIN_LIFE_10                         = 64159,
    SPELL_DRAIN_LIFE_25                         = 64160,
    SPELL_RECENTLY_SPAWNED                      = 64497
};

#define SPELL_PSYCHOSIS             RAID_MODE(SPELL_SARA_PSYCHOSIS_10, SPELL_SARA_PSYCHOSIS_25)
#define SPELL_SQUEEZE               RAID_MODE(SPELL_SQUEEZE_10, SPELL_SQUEEZE_25)
#define SPELL_DRAIN_LIFE            RAID_MODE(SPELL_DRAIN_LIFE_10, SPELL_DRAIN_LIFE_25)

enum YoggEvents
{
    EVENT_SARA_P1_DOORS_CLOSE               = 1,
    EVENT_SARA_P1_SUMMON                    = 2,
    EVENT_SARA_P1_SPELLS                    = 3,
    EVENT_SARA_P1_BERSERK                   = 4,

    EVENT_SARA_P2_START                     = 10,
    EVENT_SARA_P2_SUMMON_T1                 = 11,
    EVENT_SARA_P2_SUMMON_T2                 = 12,
    EVENT_SARA_P2_SUMMON_T3                 = 13,
    EVENT_SARA_P2_BRAIN_LINK                = 14,
    EVENT_SARA_P2_DEATH_RAY                 = 15,
    EVENT_SARA_P2_MALADY                    = 16,
    EVENT_SARA_P2_PSYCHOSIS                 = 17,
    EVENT_SARA_P2_OPEN_PORTALS              = 18,
    EVENT_SARA_P2_REMOVE_STUN               = 19,
    EVENT_SARA_P2_SPAWN_START_TENTACLES     = 20,

    EVENT_YS_LUNATIC_GAZE                   = 30,
    EVENT_YS_DEAFENING_ROAR                 = 31,
    EVENT_YS_SUMMON_GUARDIAN                = 32,
    EVENT_YS_SHADOW_BEACON                  = 33,

    // misc
    EVENT_ACTIVATE_CRUSHER                  = 34
};

enum NPCsGOs
{
    // NPCs
    NPC_OMINOUS_CLOUD                       = 33292,
    NPC_GUARDIAN_OF_YS                      = 33136,
    NPC_SANITY_WELL                         = 33991,
    NPC_YOGG_SARON                          = 33288,
    NPC_VOICE_OF_YOGG_SARON                 = 33280,
    NPC_DEATHRAY                            = 33881,

    NPC_CRUSHER_TENTACLE                    = 33966, // 50 secs ?
    NPC_CONSTRICTOR_TENTACLE                = 33983, // 15-20 secs ?
    NPC_CORRUPTOR_TENTACLE                  = 33985, // 30-40 secs ?

    NPC_INFLUENCE_TENTACLE                  = 33943,
    NPC_DEATH_ORB                           = 33882,
    NPC_DESCEND_INTO_MADNESS                = 34072,
    NPC_LAUGHING_SKULL                      = 33990,

    NPC_IMMORTAL_GUARDIAN                   = 33988,

    // CHAMBER ILLUSION
    NPC_CONSORT_FIRST                       = 33716,
    NPC_CONSORT_LAST                        = 33720,
    NPC_ALEXTRASZA                          = 33536,
    NPC_MALYGOS                             = 33535,
    NPC_NELTHARION                          = 33523,
    NPC_YSERA                               = 33495,
    GO_DRAGON_SOUL                          = 194462,

    // ICECROWN ILLUSION
    NPC_DEATHSWORN_ZEALOT                   = 33567,
    NPC_LICH_KING                           = 33441,
    NPC_IMMOLATED_CHAMPION                  = 33442,

    // STORMWIND ILLUSION
    NPC_SUIT_OF_ARMOR                       = 33433,
    NPC_GARONA                              = 33436,
    NPC_KING_LLANE                          = 33437,

    // GOs
    GO_DOORS                                = 194773,
    GO_FLEE_TO_THE_SURFACE_PORTAL           = 194625,
    GO_CHAMBER_ILLUSION_DOORS               = 194635,
    GO_ICECROWN_ILLUSION_DOORS              = 194636,
    GO_STORMWIND_ILLUSION_DOORS             = 194637,

    // MODELs
    SARA_TRANSFORM_MODEL                    = 29182
};

enum YoggSaronSounds
{
    // SARA
    SARA_AGGRO                              = 15775,
    SARA_P1_CAST1                           = 15773,
    SARA_P1_CAST2                           = 15774,
    SARA_P1_KILL1                           = 15778,
    SARA_P1_KILL2                           = 15779,

    SARA_P2_START                           = 15754,
    SARA_P2_CAST1                           = 15776,
    SARA_P2_CAST2                           = 15777,

    // YOGG-SARON
    YS_OPEN_PORTALS                         = 15756,
    YS_P3_START                             = 15755,
    YS_P3_DEAFENING_ROAR                    = 15758,
    YS_P3_DEATH                             = 15761,
    YS_P3_LUNATIC_GAZE                      = 15757,

    VOYS_P1_WIPE                            = 15780,
    VOYS_INSANE1                            = 15759,
    VOYS_INSANE2                            = 15760,

    // VISIONS
    // STORMWIND
    YS_V1_1                                 = 15762,
    YS_V1_2                                 = 15763,
    YS_V1_3                                 = 15764,
    GAR_1                                   = 15538,
    GAR_2                                   = 15539,
    GAR_3                                   = 15540,
    GAR_4                                   = 15541,
    LL_1                                    = 15585,

    // CHAMBER
    NEL_1                                   = 15631,
    NEL_2                                   = 15632,
    YSE_1                                   = 15784,
    MAL_1                                   = 15610,
    YS_V2_1                                 = 15765,

    // ICECROWN
    LK_1                                    = 15598,
    LK_2                                    = 15599,
    YS_V3_1                                 = 15766,
    YS_V3_2                                 = 15767,
    IC_1                                    = 15470,
    IC_2                                    = 15471
};

enum Misc
{
    ACTION_UNSUMMON_CLOUDS                  = -16,
    ACTION_DESPAWN_ADDS                     = -15,
    ACTION_START_SUMMONING                  = -14,
    ACTION_YOGG_SARON_APPEAR                = -13,
    ACTION_YOGG_SARON_DEATH                 = -12,
    ACTION_YOGG_SARON_START_YELL            = -11,
    ACTION_YOGG_SARON_OPEN_PORTAL_YELL      = -10,
    ACTION_INFLUENCE_TENTACLE_DIED          = -9,
    ACTION_BRAIN_DAMAGED                    = -8,
    ACTION_REMOVE_STUN                      = -7,
    ACTION_YOGG_SARON_START_P3              = -6,
    ACTION_YOGG_SARON_HARD_MODE             = -5,
    ACTION_YOGG_SARON_SHADOW_BEACON         = -4,
    ACTION_THORIM_START_STORM               = -3,
    ACTION_FAILED_DRIVE_ME_CRAZY            = -2,

    ACTION_ILLUSION_DRAGONS                 = 1,
    ACTION_ILLUSION_ICECROWN                = 2,
    ACTION_ILLUSION_STORMWIND               = 3,


    EVENT_PHASE_ONE                         = 1,
    EVENT_PHASE_TWO                         = 2,
    EVENT_PHASE_THREE                       = 3,

    CRITERIA_NOT_GETTING_OLDER              = 21001,

    DATA_GET_KEEPERS_COUNT                  = 1,
    DATA_GET_CURRENT_ILLUSION               = 2,
    DATA_GET_SARA_PHASE                     = 3,
    DATA_SET_ZERO_KEEPERS                   = 4
};

const Position Middle = {1980.28f, -25.5868f, 329.397f};

constexpr uint32 PORTAL_10MAN_SPAWN_POSITION_SIZE = 4;
Position const PortalSpawn10[PORTAL_10MAN_SPAWN_POSITION_SIZE] =
{
    {1967.53f, -48.189f, 324.718f, 6.238f},
    {1987.74f, -50.726f, 324.955f, 6.183f},
    {1967.94f, -4.2267f, 324.991f, 6.027f},
    {1986.20f, -1.799f,  325.219f, 0.000f}
};

constexpr uint32 PORTAL_25MAN_SPAWN_POSITION_SIZE = 10;
Position const PortalSpawn25[PORTAL_25MAN_SPAWN_POSITION_SIZE] =
{
    { 2003.84f, -38.586f, 325.202f, 2.911f },
    { 1996.12f, -45.483f, 325.293f, 1.925f },
    { 1984.43f, -51.423f, 324.677f, 1.689f },
    { 1967.42f, -48.833f, 324.649f, 1.026f },
    { 1957.58f, -25.567f, 324.988f, 0.016f },
    { 1967.16f, -4.5991f, 325.037f, 5.828f },
    { 1978.83f, -2.2408f, 325.139f, 4.556f },
    { 1989.09f, -2.8004f, 325.174f, 4.301f },
    { 2001.32f, -12.787f, 324.947f, 3.625f },
    { 2004.28f, -25.588f, 325.100f, 3.150f }
};

constexpr uint32 SANITY_WELL_POSITIONS_SIZE = 5;
Position const SanityWellPositions[SANITY_WELL_POSITIONS_SIZE] =
{
    { 2042.56f, -40.3667f, 329.274f, 0.0f },
    { 1975.89f, 40.0216f, 331.1f, 0.0f },
    { 1987.12f, -91.2702f, 330.186f, 0.0f },
    { 1900.48f, -51.2386f, 332.13f, 0.0f },
    { 1899.94f, 0.330621f, 332.296f, 0.0f }
};

struct boss_yoggsaron_sara : public ScriptedAI
{
    boss_yoggsaron_sara(Creature* pCreature) : ScriptedAI(pCreature), summons(pCreature)
    {
        m_pInstance = pCreature->GetInstanceScript();
        me->ApplySpellImmune(SPELL_FREYA_PASSIVE, IMMUNITY_ID, SPELL_FREYA_PASSIVE, true);
        me->ApplySpellImmune(SPELL_HODIR_PASSIVE, IMMUNITY_ID, SPELL_HODIR_PASSIVE, true);
        me->ApplySpellImmune(SPELL_MIMIRON_PASSIVE, IMMUNITY_ID, SPELL_MIMIRON_PASSIVE, true);
        me->ApplySpellImmune(SPELL_THORIM_PASSIVE, IMMUNITY_ID, SPELL_THORIM_PASSIVE, true);
        me->ApplySpellImmune(SPELL_PROTECTIVE_GAZE, IMMUNITY_ID, SPELL_PROTECTIVE_GAZE, true);
    }

    void AttackStart(Unit*) override { }
    void MoveInLineOfSight(Unit*) override { }

    void JustSummoned(Creature* creature)
    {
        summons.Summon(creature);
        if (creature->GetEntry() >= NPC_FREYA_KEEPER && creature->GetEntry() <= NPC_THORIM_KEEPER)
        {
            if (creature->GetEntry() == NPC_FREYA_KEEPER)
                creature->CastSpell(creature, SPELL_CONJURE_SANITY_WELL, false);
            _keepersGUID[creature->GetEntry() - NPC_FREYA_KEEPER] = creature->GetGUID();
        }
        else if (creature->GetEntry() == NPC_SANITY_WELL)
            creature->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_SCALE, true);
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        switch (summon->GetEntry())
        {
            case NPC_CORRUPTOR_TENTACLE:
            case NPC_CRUSHER_TENTACLE:
                summon->DespawnOrUnsummon(2s);
                break;
        }
    }

    void SpawnClouds()
    {
        for (uint8 i = 0; i < 6; ++i)
        {
            float Zplus = i > 2 ? (i - 2) * 1.6f : 0;
            if (i % 2)
                me->SummonCreature(NPC_OMINOUS_CLOUD, me->GetPositionX() + 8 + i * 7, me->GetPositionY() + 8 + i * 7, 326 + Zplus, 0);
            else
                me->SummonCreature(NPC_OMINOUS_CLOUD, me->GetPositionX() - 8 - i * 7, me->GetPositionY() - 8 - i * 7, 326 + Zplus, 0);
        }
    }

    void SpawnWells()
    {
        for (Position const& position : SanityWellPositions)
            me->SummonCreature(NPC_SANITY_WELL, position);
    }

    void EnterEvadeMode() override
    {
        if (!_EnterEvadeMode())
            return;

        me->NearTeleportTo(me->GetHomePosition());
        Reset();
        me->setActive(false);
    }

    void EnableSara(bool apply)
    {
        if (apply)
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->DisableRotate(false);
            me->ClearUnitState(UNIT_STATE_ROOT);
        }
        else
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->DisableRotate(true);
            me->AddUnitState(UNIT_STATE_ROOT);
        }
    }

    void Reset() override
    {
        _keeperHelperCount = 0;
        _fightTimer = 0;
        summons.DoAction(ACTION_DESPAWN_ADDS);
        events.Reset();
        summons.DespawnAll();

        me->SetHealth(me->GetMaxHealth());
        me->setFaction(35);
        me->SetVisible(true);
        me->SetDisplayId(me->GetNativeDisplayId());
        me->SetDisableGravity(true);
        EnableSara(false);
        SpawnClouds();

        yoggGUID = 0;
        _initFight = 1;
        memset(_keepersGUID, 0, sizeof(_keepersGUID));
        _summonedGuardiansCount = 0;
        _p2TalkTimer = 0;
        _secondPhase = false;
        _brainEventCount = 0;
        _currentIllusion = urand(1, 3);
        _isIllusionReversed = urand(0, 1);

        if (m_pInstance)
        {
            m_pInstance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, CRITERIA_NOT_GETTING_OLDER);
            m_pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SANITY);
            m_pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SQUEEZE_10);
            m_pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SQUEEZE_25);
            m_pInstance->SetData(TYPE_YOGGSARON, NOT_STARTED);
            if (GameObject* go = ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(GO_YOGG_SARON_DOORS)))
                go->SetGoState(GO_STATE_ACTIVE);
        }

        //! Should never happen, but just to make sure
        if (m_pInstance->GetData(TYPE_YOGGSARON) == DONE)
            return;

        if (Creature* yogg = me->SummonCreature(NPC_YOGG_SARON, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), M_PI))
        {
            yoggGUID = yogg->GetGUID();
            yogg->SetStandState(UNIT_STAND_STATE_SUBMERGED);
            yogg->SetFlag(UNIT_FIELD_FLAGS, (UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC));
        }
    }

    void InitFight(Unit* target)
    {
        if (!m_pInstance)
            return;

        if (m_pInstance->GetData(TYPE_VEZAX) != DONE || m_pInstance->GetData(TYPE_XT002) != DONE)
            return;

        if (m_pInstance->GetData(TYPE_YOGGSARON) == DONE)
            return;

        uint32 _keeperCount = 0;
        for (uint8 i = 0; i < 4; ++i)
        {
            if (m_pInstance->GetData(TYPE_WATCHERS) & (1 << i))
            {
                switch (i)
                {
                    case KEEPER_FREYA:
                        ++_keeperCount;
                        break;
                    case KEEPER_HODIR:
                        ++_keeperCount;
                        break;
                    case KEEPER_MIMIRON:
                        ++_keeperCount;
                        break;
                    case KEEPER_THORIM:
                        ++_keeperCount;
                        break;
                }
            }
        }
        _keeperHelperCount = _keeperCount;

        if (!_keeperCount && Is25ManRaid() && sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF))
        {
            bool const mimironHM = m_pInstance->GetData(DATA_MIMIRON_HARDMODE) != 0;
            bool const hodirHM = m_pInstance->GetData(DATA_HODIR_HARDMODE) != 0;
            bool const thorimHM = m_pInstance->GetData(DATA_THORIM_HARDMODE) != 0;
            bool const freyaHM = m_pInstance->GetData(DATA_FREYA_HARDMODE) != 0;
            bool const xtHM = m_pInstance->GetData(DATA_XT_002_HARDMODE) != 0;
            if (!mimironHM || !hodirHM || !thorimHM || !freyaHM || !xtHM)
            {
                me->MonsterTextEmote("You are not worthy to face Yogg-saron without the aid of keepers!", nullptr, true);
                return;
            }

            if (Creature* yogg = ObjectAccessor::GetCreature(*me, yoggGUID))
            {
                if (yogg->IsAIEnabled)
                    yogg->AI()->SetData(DATA_SET_ZERO_KEEPERS, DATA_SET_ZERO_KEEPERS);
            }
        }


        _fightTimer = getMSTime();
        m_pInstance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, CRITERIA_NOT_GETTING_OLDER);
        m_pInstance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, CRITERIA_NOT_GETTING_OLDER);
        m_pInstance->SetData(TYPE_YOGGSARON, IN_PROGRESS);
        me->SetInCombatWithZone();
        AttackStart(target);
        me->SetHealth(me->GetMaxHealth());
        me->CastSpell(me, SPELL_SANITY_BASE, true);

        SaveKeepers();

        events.ScheduleEvent(EVENT_SARA_P1_DOORS_CLOSE, 15000, 0, EVENT_PHASE_ONE);
        events.ScheduleEvent(EVENT_SARA_P1_BERSERK, 15min);
        events.ScheduleEvent(EVENT_SARA_P1_SUMMON, 0, 0, EVENT_PHASE_ONE);
        events.SetPhase(EVENT_PHASE_ONE);

        me->MonsterYell("The time to strike at the head of the beast will soon be upon us! Focus your anger and hatred on his minions!", LANG_UNIVERSAL, 0);
        me->PlayDirectSound(SARA_AGGRO);
        me->setActive(true);
    }

    void SaveKeepers()
    {
        for (uint8 i = 0; i < 4; ++i)
            if (m_pInstance->GetData(TYPE_WATCHERS) & (1 << i))
            {
                switch (i)
                {
                    case KEEPER_FREYA:
                        SpawnWells();
                        me->SummonCreature(NPC_FREYA_KEEPER, 1939.32f, 42.165f, 338.415f, 5.17955f);
                        break;
                    case KEEPER_HODIR:
                        me->SummonCreature(NPC_HODIR_KEEPER, 1939.13f, -90.8332f, 338.415f, 1.00123f);
                        break;
                    case KEEPER_MIMIRON:
                        me->SummonCreature(NPC_MIMIRON_KEEPER, 2036.81f, 25.6646f, 338.415f, 3.74227f);
                        break;
                    case KEEPER_THORIM:
                        me->SummonCreature(NPC_THORIM_KEEPER, 2036.59f, -73.8499f, 338.415f, 2.34819f);
                        break;
                }
            }
    }

    void InformCloud()
    {
        Creature* cloud = NULL;
        for (SummonList::const_iterator itr = summons.begin(); itr != summons.end();)
        {
            Creature* summon = ObjectAccessor::GetCreature(*me, *itr);
            ++itr;
            if (!summon || summon->GetEntry() != NPC_OMINOUS_CLOUD || me->GetDistance(summon) < 20)
                continue;

            if ((!cloud || urand(0, 1) && !summon->HasAura(SPELL_SUMMON_GUARDIAN_OF_YS)))
                cloud = summon;
        }

        if (cloud)
            cloud->AI()->DoAction(ACTION_START_SUMMONING);
    }

    void SummonDeathOrbs()
    {
        for (uint8 i = 0; i < 4; ++i)
        {
            uint32 dist = urand(38, 48);
            float o = rand_norm() * M_PI * 2;
            float Zplus = (dist - 38) / 6.5f;
            me->SummonCreature(NPC_DEATH_ORB, me->GetPositionX() + dist * cos(o), me->GetPositionY() + dist * sin(o), 327.2 + Zplus, 0, TEMPSUMMON_TIMED_DESPAWN, 20000);
        }
    }

    void AddPortals()
    {
        ++_brainEventCount;

        if (Is25ManRaid())
        {
            for (Position const& position : PortalSpawn25)
            {
                if (Creature* portal = me->SummonCreature(NPC_DESCEND_INTO_MADNESS, position, TEMPSUMMON_TIMED_DESPAWN, 15000))
                {
                    portal->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE);
                    portal->SetArmor(_currentIllusion);
                }
            }
        }
        else
        {
            for (Position const& position : PortalSpawn10)
            {
                if (Creature* portal = me->SummonCreature(NPC_DESCEND_INTO_MADNESS, position, TEMPSUMMON_TIMED_DESPAWN, 15000))
                {
                    portal->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE);
                    portal->SetArmor(_currentIllusion);
                }
            }
        }

        EntryCheckPredicate pred(NPC_BRAIN_OF_YOGG_SARON);
        summons.DoAction(_currentIllusion, pred);

        if (_isIllusionReversed)
            _currentIllusion = _currentIllusion == 3 ? 1 : ++_currentIllusion;
        else
            _currentIllusion = _currentIllusion == 1 ? 3 : --_currentIllusion;
    }

    void SpellSounds()
    {
        if (urand(0, 9))
            return;

        if (urand(0, 1))
        {
            me->MonsterYell(_secondPhase ? "Tremble, mortals, before the coming of the end!" : "Yes! YES! Show them no mercy! Give no pause to your attacks!", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(_secondPhase ? SARA_P2_CAST2 : SARA_P1_CAST1);
        }
        else
        {
            me->MonsterYell(_secondPhase ? "Suffocate upon your own hate!" : "Let hatred and rage guide your blows!", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(_secondPhase ? SARA_P2_CAST1 : SARA_P1_CAST2);
        }
    }

    void KilledUnit(Unit* who) override
    {
        if (who->GetTypeId() != TYPEID_PLAYER && roll_chance_i(50))
            return;

        if (urand(0, 1))
        {
            me->MonsterYell("Could they have been saved?", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(SARA_P1_KILL2);
        }
        else
        {
            me->MonsterYell("Powerless to act...", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(SARA_P1_KILL1);
        }
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spellInfo) override
    {
        if (spellInfo->Id == SPELL_SANITY)
            if (Aura* aur = target->GetAura(SPELL_SANITY))
                aur->SetStackAmount(100);
    }

    uint32 GetData(uint32 param) const override
    {
        if (param == DATA_GET_KEEPERS_COUNT)
        {
            uint8 _count = 0;
            for (uint8 i = 0; i < 4; ++i)
                if (_keepersGUID[i])
                    ++_count;

            return _count;
        }
        else if (param == DATA_GET_SARA_PHASE)
            return _secondPhase;

        return 4; // just to be sure, return max numer of keepers
    }

    void DoAction(int32 param)
    {
        if (param == ACTION_BRAIN_DAMAGED)
        {
            summons.DoAction(ACTION_REMOVE_STUN);

            EntryCheckPredicate pred2(NPC_YOGG_SARON);
            summons.DoAction(ACTION_YOGG_SARON_START_P3, pred2);

            EntryCheckPredicate pred3(NPC_THORIM_KEEPER);
            summons.DoAction(ACTION_THORIM_START_STORM, pred3);

            if (!(_keepersGUID[0] && _keepersGUID[1] && _keepersGUID[2] && _keepersGUID[3]) && me->GetMap()->Is25ManRaid())
                summons.DoAction(ACTION_YOGG_SARON_HARD_MODE, pred2);

            summons.DespawnEntry(NPC_DEATH_ORB);
            events.SetPhase(EVENT_PHASE_THREE);

            me->RemoveAllAuras();
            me->SetVisible(false);
            return;
        }
        else if (param == ACTION_YOGG_SARON_DEATH)
        {
            summons.DespawnEntry(NPC_VOICE_OF_YOGG_SARON);
            summons.DespawnEntry(NPC_BRAIN_OF_YOGG_SARON);
            summons.DespawnEntry(NPC_MIMIRON_KEEPER);
            summons.DespawnEntry(NPC_HODIR_KEEPER);
            summons.DespawnEntry(NPC_FREYA_KEEPER);
            summons.DespawnEntry(NPC_THORIM_KEEPER);
            summons.DespawnEntry(NPC_SANITY_WELL);

            if (Map* map = me->GetMap())
                if (const CreatureTemplate* cInfo = sObjectMgr->GetCreatureTemplate(NPC_YOGG_SARON))
                    CheckCreatureRecord(me->SelectNearestPlayer(150.0f), (map->GetDifficulty() ? cInfo->DifficultyEntry[map->GetDifficulty() - 1] :
                        cInfo->Entry) + uint32(_keeperHelperCount == 0), Difficulty(map->GetDifficulty() + (_keeperHelperCount == 0 ? 2 : 0)),
                        "Yogg Saron", 15000, _fightTimer);
            Unit::Kill(me, me);
            return;
        }

        // Determine shatter duration
        if (param <= 0)
            return;

        // Illusion shatters (param - stun time)
        WorldPacket data;
        ChatHandler::BuildChatPacket(data, CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL, me, NULL, "Illusion shatters and a path to the central chamber opens!");
        me->SendMessageToSetInRange(&data, 500, false);

        uint32 timer = events.GetNextEventTime(EVENT_SARA_P2_OPEN_PORTALS);
        uint32 portalTime = (timer > events.GetTimer() ? timer - events.GetTimer() : 0);
        //! When stun expires, a set of tentacles should spawn right away, we will reschedule those events there
        events.CancelEvent(EVENT_SARA_P2_SUMMON_T1);
        events.CancelEvent(EVENT_SARA_P2_SUMMON_T2);
        events.CancelEvent(EVENT_SARA_P2_SUMMON_T3);
        events.DelayEvents(param + 100);
        events.RescheduleEvent(EVENT_SARA_P2_OPEN_PORTALS, portalTime, 0, EVENT_PHASE_TWO);
        events.ScheduleEvent(EVENT_SARA_P2_REMOVE_STUN, param, 0, EVENT_PHASE_TWO);
        me->CastSpell(me, SPELL_SHATTERED_ILLUSION, true);
    }

    void DamageTaken(Unit* who, uint32& damage, DamageEffectType, SpellSchoolMask)
    {
        if (who && who->GetEntry() == NPC_GUARDIAN_OF_YS && !_secondPhase)
        {
            // START PHASE 2
            if (me->GetHealth() <= damage)
            {
                _secondPhase = true;
                damage = 0;

                events.SetPhase(EVENT_PHASE_TWO);
                me->SetHealth(me->GetMaxHealth());

                _p2TalkTimer++;
                me->MonsterYell("I am the lucid dream.", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SARA_P2_START);
            }
            return;
        }

        damage = 0;
    }

    void UpdateAI(uint32 diff)
    {
        if (_initFight)
        {
            _initFight += diff;
            if (_initFight > 5000)
            {
                if (Unit* target = SelectTargetFromPlayerList(90.f))
                {
                    _initFight = 0;
                    InitFight(target);
                }
                else
                    _initFight = 1;
            }
            return;
        }

        if (!SelectTargetFromPlayerList(105, SPELL_INSANE1))
        {
            m_pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_INSANE1);
            EnterEvadeMode();
            return;
        }

        if (_p2TalkTimer)
        {
            _p2TalkTimer += diff;
            if (_p2TalkTimer >= 4000 && _p2TalkTimer < 20000)
            {
                EntryCheckPredicate pred(NPC_OMINOUS_CLOUD);
                summons.DoAction(ACTION_UNSUMMON_CLOUDS, pred);
                me->MonsterYell("The monster in your nightmares.", LANG_UNIVERSAL, 0);
                _p2TalkTimer = 20000;
            }
            else if (_p2TalkTimer >= 25000 && _p2TalkTimer < 40000)
            {
                summons.DespawnEntry(NPC_OMINOUS_CLOUD);
                me->MonsterYell("The fiend of a thousand faces.", LANG_UNIVERSAL, 0);
                _p2TalkTimer = 40000;
            }
            else if (_p2TalkTimer >= 44500 && _p2TalkTimer < 60000)
            {
                me->MonsterYell("Cower before my true form.", LANG_UNIVERSAL, 0);
                _p2TalkTimer = 60000;
            }
            else if (_p2TalkTimer >= 64000)
            {
                EntryCheckPredicate pred(NPC_YOGG_SARON);
                summons.DoAction(ACTION_YOGG_SARON_START_YELL, pred);
                _p2TalkTimer = 0;
                events.ScheduleEvent(EVENT_SARA_P2_START, 500, 0, EVENT_PHASE_TWO);
            }
            return;
        }

        events.Update(diff);
        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        switch (events.GetEvent())
        {
            case EVENT_SARA_P1_DOORS_CLOSE:
                // Whispers of YS
                me->SummonCreature(NPC_VOICE_OF_YOGG_SARON, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());

                if (m_pInstance)
                    if (GameObject* go = ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(GO_YOGG_SARON_DOORS)))
                        go->SetGoState(GO_STATE_READY);

                events.ScheduleEvent(EVENT_SARA_P1_SPELLS, 0, 1, EVENT_PHASE_ONE);
                events.PopEvent();
                break;
            case EVENT_SARA_P1_SUMMON:
                events.RepeatEvent(20000 - (std::min(_summonedGuardiansCount, (uint8)5) * 2000));
                ++_summonedGuardiansCount;
                InformCloud();
                break;
            case EVENT_SARA_P1_SPELLS:
            {
                uint32 spell = RAND(SPELL_SARAS_ANGER_TARGET_SELECTOR, SPELL_SARAS_BLESSING_TARGET_SELECTOR, SPELL_SARAS_FAVOR_TARGET_SELECTOR);
                DoCastAOE(spell);
                SpellSounds();
                events.RepeatEvent(me->GetMap()->Is25ManRaid() ? urand(0, 3000) : 4000 + urand(0, 2000));
                break;
            }
            case EVENT_SARA_P2_START:
            {
                events.PopEvent();
                EntryCheckPredicate pred(NPC_YOGG_SARON);
                summons.DoAction(ACTION_YOGG_SARON_APPEAR, pred);
                events.RescheduleEvent(EVENT_SARA_P2_SPAWN_START_TENTACLES, 500, 0, EVENT_PHASE_TWO);

                // Spawn Brain!
                Creature* brain = me->SummonCreature(NPC_BRAIN_OF_YOGG_SARON, 1981.3f, -25.43f, 265);
                if (brain && brain->IsAIEnabled)
                {
                    if (!_keeperHelperCount && Is25ManRaid() && sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF))
                        brain->AI()->SetData(DATA_SET_ZERO_KEEPERS, DATA_SET_ZERO_KEEPERS);
                }
                break;
            }
            case EVENT_SARA_P2_MALADY:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    if (Aura* aur = target->GetAura(SPELL_SANITY))
                        if (aur->GetStackAmount() >= 31)
                            me->CastSpell(target, SPELL_MALADY_OF_THE_MIND, false);

                events.RepeatEvent(20000);
                break;
            case EVENT_SARA_P2_PSYCHOSIS:
                SpellSounds();

                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    if (Aura* aur = target->GetAura(SPELL_SANITY))
                        if (aur->GetStackAmount() >= 31)
                            me->CastSpell(target, SPELL_PSYCHOSIS, false);

                events.RepeatEvent(RAID_MODE(3000, 1100));
                break;
            case EVENT_SARA_P2_DEATH_RAY:
            {
                Position pos = me->GetPosition();
                pos.m_positionZ += 2.0f;
                if (Creature* rayTarget = me->SummonCreature(NPC_DEATHRAY, pos, TEMPSUMMON_TIMED_DESPAWN, 17000))
                {
                    rayTarget->SetDisplayId(17612);
                    rayTarget->SetCanFly(true);
                    rayTarget->SetDisableGravity(true);
                }
                SummonDeathOrbs();
                events.RepeatEvent(20000);
                break;
            }
            case EVENT_SARA_P2_SUMMON_T1: // CRUSHER
                DoCastAOE(SPELL_SUMMON_CRUSHER_TENTACLE, true);
                if (_brainEventCount < 4)
                    events.RepeatEvent(50000);
                else
                    events.RepeatEvent(25000);
                break;
            case EVENT_SARA_P2_SUMMON_T2: // CONSTRICTOR
                DoCastAOE(SPELL_SUMMON_CONSTRICTOR_TENTACLES_AURA, true);
                if (_brainEventCount < 4)
                    events.RepeatEvent(15000);
                else
                    events.RepeatEvent(7500);
                break;
            case EVENT_SARA_P2_SUMMON_T3: // CORRUPTOR
                DoCastAOE(SPELL_SUMMON_CURRUPTOR_TENTACLE);
                if (_brainEventCount < 4)
                    events.RepeatEvent(30000);
                else
                    events.RepeatEvent(15000);
                break;
            case EVENT_SARA_P2_BRAIN_LINK:
                me->CastCustomSpell(SPELL_BRAIN_LINK, SPELLVALUE_MAX_TARGETS, 1, me, false);
                events.RepeatEvent(30000);
                break;
            case EVENT_SARA_P2_OPEN_PORTALS:
            {
                AddPortals();
                EntryCheckPredicate pred(NPC_YOGG_SARON);
                summons.DoAction(ACTION_YOGG_SARON_OPEN_PORTAL_YELL, pred);
                events.RepeatEvent(80000);
                break;
            }
            case EVENT_SARA_P2_REMOVE_STUN:
            {
                me->RemoveAura(SPELL_SHATTERED_ILLUSION);
                events.PopEvent();
                summons.DoAction(ACTION_REMOVE_STUN);
                events.ScheduleEvent(EVENT_SARA_P2_SUMMON_T1, 1000ms, 0, EVENT_PHASE_TWO);
                events.ScheduleEvent(EVENT_SARA_P2_SUMMON_T2, 1000ms, 0, EVENT_PHASE_TWO);
                events.ScheduleEvent(EVENT_SARA_P2_SUMMON_T3, 1000ms, 0, EVENT_PHASE_TWO);
                break;
            }
            case EVENT_SARA_P2_SPAWN_START_TENTACLES:
                events.PopEvent();

                me->setFaction(16);
                me->SetOrientation(M_PI);
                me->SetDisplayId(SARA_TRANSFORM_MODEL);

                me->SendMonsterMove(me->GetPositionX(), me->GetPositionY(), 355, 2000, SPLINEFLAG_FLYING);
                me->SetPosition(me->GetPositionX(), me->GetPositionY(), 355, me->GetOrientation());

                DoCastAOE(SPELL_SUMMON_CONSTRICTOR_TENTACLES_AURA, true);
                DoCastAOE(SPELL_SUMMON_CRUSHER_TENTACLE, true);
                DoCastAOE(SPELL_SUMMON_CURRUPTOR_TENTACLE, true);
                DoCastAOE(SPELL_SUMMON_CURRUPTOR_TENTACLE, true);

                events.ScheduleEvent(EVENT_SARA_P2_MALADY, 7000, 0, EVENT_PHASE_TWO);
                events.ScheduleEvent(EVENT_SARA_P2_PSYCHOSIS, 3000, 0, EVENT_PHASE_TWO);
                events.ScheduleEvent(EVENT_SARA_P2_DEATH_RAY, 15000, 0, EVENT_PHASE_TWO);
                events.ScheduleEvent(EVENT_SARA_P2_SUMMON_T1, 50000 + urand(0, 10000), 0, EVENT_PHASE_TWO);
                events.ScheduleEvent(EVENT_SARA_P2_SUMMON_T2, 15000 + urand(0, 5000), 0, EVENT_PHASE_TWO);
                events.ScheduleEvent(EVENT_SARA_P2_SUMMON_T3, 30000 + urand(0, 10000), 0, EVENT_PHASE_TWO);
                events.ScheduleEvent(EVENT_SARA_P2_BRAIN_LINK, 0, 0, EVENT_PHASE_TWO);
                events.ScheduleEvent(EVENT_SARA_P2_OPEN_PORTALS, 60000, 0, EVENT_PHASE_TWO);
                break;
            case EVENT_SARA_P1_BERSERK:
                DoCastAOE(SPELL_EXTINGUISH_ALL_LIFE, true);
                events.RepeatEvent(5000);
                break;
        }
    }
private:
    InstanceScript* m_pInstance;
    EventMap events;
    SummonList summons;

    uint32 _initFight;
    uint64 _keepersGUID[4];
    uint8 _summonedGuardiansCount;
    uint32 _p2TalkTimer;
    bool _secondPhase;
    uint32 _brainEventCount;
    uint8 _currentIllusion;
    bool _isIllusionReversed;
    uint32 _fightTimer;
    uint32 _keeperHelperCount;
    uint64 yoggGUID;
};

struct boss_yoggsaron_cloud : public ScriptedAI
{
    boss_yoggsaron_cloud(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    void JustSummoned(Creature* creature) override
    {
        creature->ToTempSummon()->SetTempSummonType(TEMPSUMMON_CORPSE_DESPAWN);

        _isSummoning = false;
        if (me->GetInstanceScript())
            if (Creature* sara = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(NPC_SARA)))
                sara->AI()->JustSummoned(creature);
    }

    void MoveInLineOfSight(Unit* /*who*/) override { }
    void AttackStart(Unit* /*who*/) override { }

    void Reset() override
    {
        InitWaypoint();
        me->CastSpell(me, SPELL_CLOUD_VISUAL, true);
        _checkTimer = 0;
        _isSummoning = false;
    }

    void DoAction(int32 param) override
    {
        if (param == ACTION_UNSUMMON_CLOUDS)
        {
            me->RemoveAllAuras();
        }
        else if (param == ACTION_START_SUMMONING)
        {
            _isSummoning = true;
            me->CastSpell(me, SPELL_SUMMON_GUARDIAN_OF_YS, true);
        }
    }

    void FillCirclePath(Position const& centerPos, float radius, float z, Movement::PointsArray& path, bool clockwise)
    {
        float step = clockwise ? -M_PI / 4.0f : M_PI / 4.0f;
        float angle = centerPos.GetAngle(me->GetPositionX(), me->GetPositionY());

        for (uint8 i = 0; i < 8; angle += step, ++i)
        {
            G3D::Vector3 point;
            point.x = centerPos.GetPositionX() + radius * cosf(angle);
            point.y = centerPos.GetPositionY() + radius * sinf(angle);
            point.z = z;
            path.push_back(point);
        }
    }

    void InitWaypoint()
    {
        float dist = Middle.GetExactDist(me);
        Movement::MoveSplineInit init(me);
        if (me->GetPositionX() > Middle.GetPositionX())
            FillCirclePath(Middle, dist, me->GetPositionZ(), init.Path(), true);
        else
            FillCirclePath(Middle, dist, me->GetPositionZ(), init.Path(), false);

        init.SetWalk(false);
        init.SetSmooth();
        init.SetCyclic();
        init.Launch();
    }

    void UpdateAI(uint32 diff) override
    {
        _checkTimer += diff;
        if (_checkTimer >= 500 && !_isSummoning)
        {
            bool canSpawn = false;
            if (me->GetInstanceScript())
                if (me->GetInstanceScript()->GetData(TYPE_YOGGSARON) == IN_PROGRESS)
                    canSpawn = true;

            Unit* who = me->SelectNearbyTarget(NULL, 6.0f);
            if (who && canSpawn && who->GetTypeId() == TYPEID_PLAYER && !me->HasAura(SPELL_SUMMON_GUARDIAN_OF_YS) && !who->HasAura(SPELL_HODIR_FLASH_FREEZE))
            {
                _isSummoning = true;
                Talk(0, who);
                me->CastSpell(me, SPELL_SUMMON_GUARDIAN_OF_YS, true);
            }

            _checkTimer = 0;
        }
    }
private:
    uint32 _checkTimer;
    bool _isSummoning;
};

enum guardianOfYSEvents
{
    EVENT_GUARDIAN_DARK_VOLLEY      = 1,
    EVENT_GUARDIAN_DOMINATE_MIND    = 2
};

struct boss_yoggsaron_guardian_of_ys : public ScriptedAI
{
    boss_yoggsaron_guardian_of_ys(Creature* creature) : ScriptedAI(creature)
    {
        _zeroKeepers = false;
    }

    void OnMeleeOutcome(WeaponAttackType type, Unit const* victim, MeleeHitOutcome& outcome, VictimAvoidanceStats stats) override
    {
        if (!victim->IsPlayer())
            return;

        if (type > OFF_ATTACK)
            return;

        //! Dont do anything if victim is over avoidance cap
        if (stats.parryChance + stats.dodgeChance + stats.missChance > 100.f)
            return;

        if (!_ignoreMeleeAvoidance)
            return;

        switch (outcome)
        {
            case MELEE_HIT_DODGE:
            case MELEE_HIT_PARRY:
            case MELEE_HIT_MISS:
            {
                outcome = MELEE_HIT_NORMAL;
                break;
            }
            default:
                break;
        }
    }

    void Reset()
    {
        _ignoreMeleeAvoidance = false;
        task.CancelAll();
        events.Reset();
        events.ScheduleEvent(EVENT_GUARDIAN_DARK_VOLLEY, 8s);
        events.ScheduleEvent(EVENT_GUARDIAN_DOMINATE_MIND, 25s);
        me->SetInCombatWithZone();
        task.Schedule(15s, [&](TaskContext func)
        {
            _ignoreMeleeAvoidance = !_ignoreMeleeAvoidance;

            if (_ignoreMeleeAvoidance)
                func.Repeat(6s);
            else
                func.Repeat(15s);
        });
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == DATA_SET_ZERO_KEEPERS)
            _zeroKeepers = true;
    }

    void JustSummoned(Creature* summoner) override
    {
        if (me->GetInstanceScript())
        {
            if (Creature* sara = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(NPC_SARA)))
                if (sara->IsAIEnabled)
                    sara->AI()->JustSummoned(me);
        }
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) && Is25ManRaid() && _zeroKeepers)
            damage = damage * 0.9f;
    }

    void JustDied(Unit*)
    {
        DoCastAOE(SPELL_SHADOW_NOVA_GUARDIAN_TARGET_SARA, true);
        DoCastAOE(RAID_MODE(SPELL_SHADOW_NOVA_GUARDIAN_10, SPELL_SHADOW_NOVA_GUARDIAN_25), true);
    }

    void UpdateAI(uint32 diff)
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_GUARDIAN_DARK_VOLLEY:
                {
                    DoCastAOE(SPELL_DARK_VOLLEY);
                    events.Repeat(8s);
                    break;
                }
                case EVENT_GUARDIAN_DOMINATE_MIND:
                {
                    CustomSpellValues val;
                    val.AddSpellMod(SPELLVALUE_MAX_TARGETS, 1);
                    me->CastCustomSpell(SPELL_DOMINATE_MIND, val, (Unit*)nullptr, TRIGGERED_NONE);
                    events.Repeat(25s);
                    break;
                }
            }
        }

        DoMeleeAttackIfReady();
    }
private:
    EventMap events;
    bool _zeroKeepers;
    TaskScheduler task;
    bool _ignoreMeleeAvoidance;
};

struct boss_yoggsaron : public ScriptedAI
{
    boss_yoggsaron(Creature* creature) : ScriptedAI(creature), summons(creature)
    {
        m_pInstance = me->GetInstanceScript();
        _thirdPhase = false;
        _usedInsane = false;
        _died = false;
        _zeroKeepers = false;
        summons.DespawnAll();
        events.Reset();

        _beaconCounter = 3;
        task.CancelAll();
    }

    void AttackStart(Unit* /*who*/) override { }
    bool CanBeChainPulled() const override { return false; }
    void JustSummoned(Creature* creature) override
    {
        summons.Summon(creature);
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == DATA_SET_ZERO_KEEPERS)
            _zeroKeepers = true;
    }

    void EnterCombat(Unit* /*who*/) override
    {
        me->ResetLootMode();
        uint8 _count = 4;
        me->SetLootMode(31); // 1 + 2 + 4 + 8 + 16, remove with watchers addition
        if (m_pInstance)
        {
            for (uint8 i = 0; i < 4; ++i)
            {
                if (m_pInstance->GetData(TYPE_WATCHERS) & (1 << i))
                {
                    me->RemoveLootMode(1 << _count);
                    --_count;
                }
            }
        }

        if (!Is25ManRaid() && _count < 3)
            me->AddLootMode(64); // emblem marker for 10 man, because emblems differ depending on watcher count and this entire loot handling sucks
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) && Is25ManRaid() && _zeroKeepers)
            damage = damage * 0.9f;
    }

    void SummonImmortalGuardian()
    {
        uint32 dist = urand(38, 48);
        float o = rand_norm() * M_PI * 2;
        float Zplus = (dist - 38) / 6.5f;
        me->SummonCreature(NPC_IMMORTAL_GUARDIAN, me->GetPositionX() + dist * cos(o), me->GetPositionY() + dist * sin(o), 327.2 + Zplus, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);
    }

    void JustDied(Unit* who) override
    {
        DoCastSelf(SPELL_YOGG_DEATH_ANIMATION, true);
        summons.DespawnAll();
        events.Reset();

        me->MonsterYell("Your fate is sealed. The end of days is finally upon you and ALL who inhabit this miserable little seedling. Uulwi ifis halahs gag erh'ongg w'ssh.", LANG_UNIVERSAL, 0);
        me->PlayDirectSound(YS_P3_DEATH);

        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_YOGGSARON, DONE);
            if (Creature* sara = ObjectAccessor::GetCreature(*me, m_pInstance->GetData64(NPC_SARA)))
                sara->AI()->DoAction(ACTION_YOGG_SARON_DEATH);
            if (GameObject* go = ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(GO_YOGG_SARON_DOORS)))
                go->SetGoState(GO_STATE_ACTIVE);
        }

        Map::PlayerList const& pList = me->GetMap()->GetPlayers();
        for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
        {
            itr->GetSource()->RemoveAura(SPELL_SANITY);
            itr->GetSource()->RemoveAura(SPELL_INSANE1);
            itr->GetSource()->RemoveAura(SPELL_INSANE2);
        }
    }

    void DoAction(int32 param) override
    {
        if (param == ACTION_DESPAWN_ADDS)
            summons.DespawnAll();
        else if (param == ACTION_YOGG_SARON_APPEAR)
        {
            me->CastSpell(me, SPELL_SHADOW_BARRIER, true);
            me->CastSpell(me, SPELL_KNOCK_AWAY, true);
            me->RemoveFlag(UNIT_FIELD_FLAGS, (UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC));
            me->SetStandState(UNIT_STAND_STATE_STAND);
            me->SetInCombatWithZone();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_PACIFIED);
        }
        else if (param == ACTION_YOGG_SARON_START_YELL)
        {
            me->MonsterYell("BOW DOWN BEFORE THE GOD OF DEATH!", LANG_UNIVERSAL, 0);
        }
        else if (param == ACTION_YOGG_SARON_OPEN_PORTAL_YELL)
        {
            me->MonsterYell("MADNESS WILL CONSUME YOU!", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(YS_OPEN_PORTALS);
        }
        else if (param == ACTION_YOGG_SARON_START_P3)
        {
            if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) && Is25ManRaid() && _zeroKeepers)
            {
                uint32 fullHealth = me->GetMaxHealth() * 0.3f;
                me->SetMaxHealth(fullHealth);
                me->SetFullHealth();
            }
            else
            {
                me->SetHealth(me->GetMaxHealth() * 0.3f);
                me->LowerPlayerDamageReq(me->GetMaxHealth() * 0.3f);
            }

            me->RemoveAura(SPELL_SHADOW_BARRIER);
            DoCastSelf(SPELL_P3_TRANSFORM_YOGG);

            events.ScheduleEvent(EVENT_YS_LUNATIC_GAZE, 7000);
            events.ScheduleEvent(EVENT_YS_SHADOW_BEACON, 45000);
            events.ScheduleEvent(EVENT_YS_SUMMON_GUARDIAN, 0);
            _thirdPhase = true;

            me->MonsterYell("Look upon the true face of death and know that your end comes soon!", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(YS_P3_START);
        }
        else if (param == ACTION_YOGG_SARON_HARD_MODE)
        {
            events.ScheduleEvent(EVENT_YS_DEAFENING_ROAR, 50000);
        }
        else if (param == ACTION_YOGG_SARON_SHADOW_BEACON)
        {
            events.RescheduleEvent(EVENT_YS_SHADOW_BEACON, 45000);
        }
        else if (param == ACTION_REMOVE_STUN)
        {
            me->RemoveAura(SPELL_SHATTERED_ILLUSION);
            me->SetControlled(true, UNIT_STATE_ROOT);
        }
        else if (param == ACTION_FAILED_DRIVE_ME_CRAZY)
            _usedInsane = true;
    }

    uint32 GetData(uint32 param) const override
    {
        if (param == ACTION_FAILED_DRIVE_ME_CRAZY)
            return !_usedInsane;

        return 0;
    }

    void SpellHit(Unit* caster, const SpellInfo* spellInfo) override
    {
        if (spellInfo->Id == SPELL_IN_THE_MAWS_OF_THE_OLD_GOD)
            me->AddLootMode(32);
    }

    void UpdateAI(uint32 diff) override
    {
        task.Update(diff);
        if (!_thirdPhase)
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        float HealthFlo = 1.46f; // <= 1.45f
        int32 HealthPct = (int32)HealthFlo;

        if (me->HealthBelowPct(HealthPct) && !_died)
        {
            _died = true;
            Unit::DealDamage(me, me, me->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        }

        switch (events.GetEvent())
        {
            case EVENT_YS_LUNATIC_GAZE:
                me->MonsterYell("Hoohehehahahaha... AHAHAHAHAHAHA!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(YS_P3_LUNATIC_GAZE);
                me->CastSpell(me, SPELL_LUNATIC_GAZE_YS, true);
                events.RepeatEvent(12000);
                break;
            case EVENT_YS_DEAFENING_ROAR:
                me->MonsterTextEmote("Yogg-Saron opens his mouth wide!", 0, true);
                me->MonsterYell("Eternal suffering awaits!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(YS_P3_DEAFENING_ROAR);
                me->CastSpell(me, SPELL_DEAFENING_ROAR, false);
                events.RepeatEvent(50000);
                break;
            case EVENT_YS_SHADOW_BEACON:
            {
                uint8 count = me->GetMap()->Is25ManRaid() ? _beaconCounter : 2;
                events.RepeatEvent(5000);
                me->CastCustomSpell(SPELL_SHADOW_BEACON, SPELLVALUE_MAX_TARGETS, count, me, false);
                if (_beaconCounter < 5)
                    ++_beaconCounter;
                break;
            }
            case EVENT_YS_SUMMON_GUARDIAN:
                SummonImmortalGuardian();
                events.RepeatEvent(10000);
                break;
        }
    }
private:
    InstanceScript* m_pInstance;
    EventMap events;
    SummonList summons;
    bool _thirdPhase;
    bool _usedInsane;
    bool _died;
    uint32 _beaconCounter;
    bool _zeroKeepers;
    TaskScheduler task;
};

struct boss_yoggsaron_brain : public NullCreatureAI
{
    boss_yoggsaron_brain(Creature* creature) : NullCreatureAI(creature), summons(creature)
    {
        me->SetDisableGravity(true);
        _tentacleCount = 0;
        _activeIllusion = 0;
        _induceTimer = 0;
        _brainDamaged = false;
        _isChamberCount = false;
        _isIcecrownCount = false;
        _isStormwindCount = false;
        me->SetRegeneratingHealth(false);
        _zeroKeepers = false;
        _defeatHealthPct = 30;
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == DATA_SET_ZERO_KEEPERS)
        {
            _zeroKeepers = true;
            _defeatHealthPct = 1;
        }
    }

    void Reset() override { }
    void JustSummoned(Creature* creature) override
    {
        if (creature->GetEntry() == NPC_INFLUENCE_TENTACLE)
        {
            if (creature->IsAIEnabled && _zeroKeepers)
                creature->AI()->SetData(DATA_SET_ZERO_KEEPERS, DATA_SET_ZERO_KEEPERS);

            // Dragons Illusion
            if (creature->GetPositionX() > 2000.0f && creature->GetPositionX() < 2150.0f)
                creature->UpdateEntry(urand(NPC_CONSORT_FIRST, NPC_CONSORT_LAST));
            // Icecrown Illusion
            else if (creature->GetPositionY() > -150.0f && creature->GetPositionY() < -90.0f)
            {
                creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                creature->UpdateEntry(NPC_DEATHSWORN_ZEALOT);
            }
            // Stormwind Illusion
            else
                creature->UpdateEntry(NPC_SUIT_OF_ARMOR);
        }
        else if (creature->GetEntry() == NPC_LICH_KING)
        {
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE);
            creature->CastSpell(creature, SPELL_DEATHGRASP, false);
        }

        summons.Summon(creature);
    }

    void PrepareChamberIllusion()
    {
        _isChamberCount = true;
        _isIcecrownCount = false;
        _isStormwindCount = false;

        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 2060.34f, -5.46f, 239.75f, 5.96f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 2082.21f, 15.18f, 239.78f, 5.25f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 2118.13f, 18.31f, 239.72f, 4.15f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 2138.94f, 2.96f, 239.71f, 3.83f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 2143.16f, -49.81f, 239.75f, 2.79f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 2119.95f, -66.53f, 239.72f, 2.39f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 2084.66f, -63.61f, 239.72f, 0.99f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 2063.71f, -44.22f, 239.71f, 0.39f);

        // Laughing Skulls
        if (urand(0, 1))
            me->SummonCreature(NPC_LAUGHING_SKULL, 2139.13f, -59.0848f, 239.728f, 2.2974f);
        else
            me->SummonCreature(NPC_LAUGHING_SKULL, 2083, -25.66f, 244, 0);
        if (urand(0, 1))
            me->SummonCreature(NPC_LAUGHING_SKULL, 2066.67f, -59.8984f, 239.72f, 0.718747f);
        else
            me->SummonCreature(NPC_LAUGHING_SKULL, 2126.22f, -25.86f, 244, 0);

        me->SummonCreature(NPC_LAUGHING_SKULL, 2133.09f, 15.341f, 239.72f, 4.0724f);
        me->SummonCreature(NPC_LAUGHING_SKULL, 2065.83f, 12.3772f, 239.792f, 5.49789f);

        // Aspects
        me->SummonCreature(NPC_ALEXTRASZA, 2091.92f, -25.8f, 242.647f, 0);
        me->SummonCreature(NPC_YSERA, 2116, -25.8f, 242.647f, 3.14f);
        me->SummonCreature(NPC_NELTHARION, 2103.6f, -35.8f, 242.64f, 1.5f);
        me->SummonCreature(NPC_MALYGOS, 2103.6f, -15.8f, 242.64f, 4.7f);
    }

    void PrepareIceCrownIllusion()
    {
        _isChamberCount = false;
        _isIcecrownCount = true;
        _isStormwindCount = false;

        // Laughing Skulls
        me->SummonCreature(NPC_LAUGHING_SKULL, 1931.12f, -92.702f, 239.991f, 5.2819f);
        if (urand(0, 1))
            me->SummonCreature(NPC_LAUGHING_SKULL, 1969.88f, -147.729f, 239.991f, 2.37593f);
        else
            me->SummonCreature(NPC_LAUGHING_SKULL, 1878, -93.3f, 240, 0);
        if (urand(0, 1))
            me->SummonCreature(NPC_LAUGHING_SKULL, 1950.78f, -167.902f, 239.991f, 2.34844f);
        else
            me->SummonCreature(NPC_LAUGHING_SKULL, 1938.45f, -116.5f, 240, 0);
        if (urand(0, 1))
            me->SummonCreature(NPC_LAUGHING_SKULL, 1896.45f, -141.469f, 239.991f, 6.12227f);
        else
            me->SummonCreature(NPC_LAUGHING_SKULL, 1921, -158, 240, 0);

        // Influence
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1958.29f, -128.65f, 239.99f, 3.61293f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1957.78f, -134.368f, 239.99f, 3.35375f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1953.04f, -137.843f, 239.99f, 3.55796f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1900.31f, -93.5241f, 239.99f, 4.50043f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1895.03f, -98.0773f, 239.99f, 4.88135f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1895.19f, -104.587f, 239.99f, 5.02271f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1923.31f, -125.980f, 239.99f, 4.2f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1921.05f, -122.362f, 239.99f, 4.2f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1927.53f, -126.284f, 239.99f, 4.2f);

        // Others
        me->SummonCreature(NPC_LICH_KING, 1906.98f, -153, 240, 4.2f);
        me->SummonCreature(NPC_IMMOLATED_CHAMPION, 1902.03f, -161.7f, 240, 1.07f);
    }

    void PrepareStormwindIllusion()
    {
        _isChamberCount = false;
        _isIcecrownCount = false;
        _isStormwindCount = true;

        // Laughing Skulls
        if (urand(0, 1))
            me->SummonCreature(NPC_LAUGHING_SKULL, 1916.36f, 28.05f, 239.666f, 1.30238f);
        else
            me->SummonCreature(NPC_LAUGHING_SKULL, 1966.7f, 57.8f, 239.66f, 0);
        if (urand(0, 1))
            me->SummonCreature(NPC_LAUGHING_SKULL, 1902, 75.1362f, 239.666f, 6.06189f);
        else
            me->SummonCreature(NPC_LAUGHING_SKULL, 1933, 91, 240, 0);
        me->SummonCreature(NPC_LAUGHING_SKULL, 1914.42f, 90.8465f, 239.666f, 5.25294f);
        me->SummonCreature(NPC_LAUGHING_SKULL, 1963.68f, 89.7549f, 239.667f, 3.70571f);

        // Influence
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1931.41f, 39.0711f, 239.66f, 1.82467f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1908.67f, 45.5867f, 239.666f, 0.72119f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1897.68f, 66.1274f, 239.666f, 6.27395f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1950.73f, 49.3446f, 239.666f, 2.63756f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1923.16f, 97.5586f, 239.666f, 4.74635f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1956.16f, 72.1403f, 239.666f, 3.19518f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1944.81f, 92.3154f, 239.666f, 4.03556f);
        me->SummonCreature(NPC_INFLUENCE_TENTACLE, 1904.97f, 85.8025f, 239.666f, 5.67568f);

        // Others
        me->SummonCreature(NPC_GARONA, 1928.58f, 65.64f, 242.37f, 2.1f);
        me->SummonCreature(NPC_KING_LLANE, 1925.14f, 71.74f, 242.37f, 5.17f);
    }

    void DoAction(int32 param) override
    {
        if (param == ACTION_DESPAWN_ADDS)
        {
            summons.DespawnAll();
            return;
        }
        else if (param == ACTION_INFLUENCE_TENTACLE_DIED)
        {
            _tentacleCount++;

            /*TENTACLES COUNT*/
            if ((_isChamberCount && _tentacleCount >= 8) || (_isStormwindCount && _tentacleCount >= 8) || (_isIcecrownCount && _tentacleCount >= 9))
            {
                // Stun
                if (me->GetInstanceScript())
                    if (Creature* sara = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(NPC_SARA)))
                        sara->AI()->DoAction(MINUTE * IN_MILLISECONDS - std::min((uint32)MINUTE * IN_MILLISECONDS, _induceTimer));

                _induceTimer = 0;
                summons.DespawnEntry(NPC_LAUGHING_SKULL);
                if (GameObject* go = me->FindNearestGameObject(GO_CHAMBER_ILLUSION_DOORS + _activeIllusion, 150.0f))
                    go->SetGoState(GO_STATE_ACTIVE);
            }
            return;
        }
        else if (param == ACTION_REMOVE_STUN)
            return;

        summons.DespawnAll();
        switch (param)
        {
            case ACTION_ILLUSION_STORMWIND: PrepareStormwindIllusion(); break;
            case ACTION_ILLUSION_DRAGONS:   PrepareChamberIllusion();   break;
            case ACTION_ILLUSION_ICECROWN:  PrepareIceCrownIllusion();  break;
        }

        for (uint32 i = GO_CHAMBER_ILLUSION_DOORS; i <= GO_STORMWIND_ILLUSION_DOORS; ++i)
            if (GameObject* go = me->FindNearestGameObject(i, 150.0f))
                go->SetGoState(GO_STATE_READY);

        _activeIllusion = param - 1;
        _tentacleCount = 0;
        _induceTimer = 1;

        me->CastSpell(me, SPELL_INDUCE_MADNESS, false);
    }

    uint32 GetData(uint32 param) const
    {
        if (param == DATA_GET_CURRENT_ILLUSION)
            return _activeIllusion + 1;

        return 0;
    }

    void DamageTaken(Unit* who, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (_tentacleCount < 7) // if all tentacles aren't killed
        {
            damage = 0;
            //if (who)
                //Unit::Kill(who, who);
            return;
        }

        if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) && me->GetMap()->Is25ManRaid() && _zeroKeepers)
            damage = damage * 0.9f;

        if (damage >= me->GetHealth())
            damage = me->GetHealth() - 1;

        if (!_brainDamaged)
        {
            // START PHASE 3
            if (me->HealthBelowPctDamaged(_defeatHealthPct, damage))
            {
                me->SetRegeneratingHealth(false);
                _EnterEvadeMode();
                _brainDamaged = true;

                me->CastSpell(me, SPELL_BRAIN_HURT_VISUAL, true);
                if (me->GetInstanceScript())
                    if (Creature* sara = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(NPC_SARA)))
                        sara->AI()->DoAction(ACTION_BRAIN_DAMAGED);
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (_induceTimer)
            _induceTimer += diff;
    }

private:
    bool _brainDamaged;
    bool _isChamberCount;
    bool _isIcecrownCount;
    bool _isStormwindCount;
    bool _zeroKeepers;

    uint8 _tentacleCount;
    uint8 _activeIllusion;
    uint32 _induceTimer;
    uint32 _defeatHealthPct;
    SummonList summons;
};

struct boss_yoggsaron_death_orb : public NullCreatureAI
{
    boss_yoggsaron_death_orb(Creature* pCreature) : NullCreatureAI(pCreature)
    {
        me->CastSpell(me, SPELL_DEATH_RAY_WARNING, true);
        _startTimer = 1;
        moving = true;
    }

    void DoRandomMove()
    {
        Position pos;
        me->GetNearPoint2D(pos.m_positionX, pos.m_positionY, 10, float(2 * M_PI * rand_norm()));
        pos.m_positionZ = me->GetPositionZ();
        pos.m_positionZ = me->GetMap()->GetHeight(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), true, 50.0f);
        me->SetWalk(true);
        me->GetMotionMaster()->MovePoint(1, pos);
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        if (id != 1)
            return;

        moving = false;
    }

    void UpdateAI(uint32 diff) override
    {
        if (_startTimer)
        {
            _startTimer += diff;
            if (_startTimer > 4000)
            {
                me->CastSpell(me, SPELL_DEATH_RAY_DAMAGE_VISUAL, true);
                me->CastSpell(me, SPELL_DEATH_RAY_DAMAGE, true);

                _startTimer = 0;
                me->SetSpeedRate(MOVE_WALK, 2);
                me->SetSpeedRate(MOVE_RUN, 2);
                moving = false;
                //me->GetMotionMaster()->MoveRandom(20.0f);
            }
        }

        if (!moving)
        {
            DoRandomMove();
            moving = true;
        }
    }
private:
    uint32 _startTimer;
    bool moving;
};

struct boss_yoggsaron_crusher_tentacle : public ScriptedAI
{
    boss_yoggsaron_crusher_tentacle(Creature* pCreature) : ScriptedAI(pCreature)
    {
        _zeroKeepers = false;
        SetCombatMovement(false);
        DoCastSelf(SPELL_VOID_ZONE_LARGE, true);
        DoCastAOE(SPELL_ERUPT_TENTACLE);
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == DATA_SET_ZERO_KEEPERS)
            _zeroKeepers = true;
    }

    void Reset() override
    {
        _events.Reset();
        me->SetReactState(REACT_PASSIVE);
        _events.ScheduleEvent(EVENT_ACTIVATE_CRUSHER, 2s);
        me->SetInCombatWithZone();
    }

    void OnMeleeAttackTaken(Unit* attacker) override
    {
        me->InterruptNonMeleeSpells(false);
    }

    void DamageTaken(Unit* who, uint32& damage, DamageEffectType damagetype, SpellSchoolMask) override
    {
        if (who && damagetype == DIRECT_DAMAGE)
            AttackStart(who);

        if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) && Is25ManRaid() && _zeroKeepers)
            damage = damage * 0.9f;
    }

    void DoAction(int32 param) override
    {
        if (param == ACTION_REMOVE_STUN)
            me->RemoveAura(SPELL_SHATTERED_ILLUSION);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        if (_events.ExecuteEvent() == EVENT_ACTIVATE_CRUSHER)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            DoZoneInCombat(me, 200.f);
            me->CastSpell(me, SPELL_CRUSH, true);
            me->CastSpell(me, SPELL_FOCUSED_ANGER, true);
            me->CastSpell(me, SPELL_DIMINISH_POWER, false);
        }

        if (me->HasReactState(REACT_PASSIVE))
            return;

        if (me->IsWithinMeleeRange(me->GetVictim()))
        {
            DoMeleeAttackIfReady();
            return;
        }

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        me->CastSpell(me, SPELL_DIMINISH_POWER, false);
    }
private:
    EventMap _events;
    bool _zeroKeepers;
};

struct boss_yoggsaron_corruptor_tentacle : public ScriptedAI
{
    boss_yoggsaron_corruptor_tentacle(Creature* creature) : ScriptedAI(creature)
    {
        _zeroKeepers = false;
        SetCombatMovement(false);
        DoCastSelf(SPELL_VOID_ZONE_LARGE, true);

        if (me->GetInstanceScript())
        {
            if (Creature* sara = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(NPC_SARA)))
                if (sara->IsAIEnabled)
                    sara->AI()->JustSummoned(me);
        }
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == DATA_SET_ZERO_KEEPERS)
            _zeroKeepers = true;
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) && me->GetMap()->Is25ManRaid() && _zeroKeepers)
            damage = damage * 0.9f;
    }

    void DoAction(int32 param)
    {
        if (param == ACTION_REMOVE_STUN)
            me->RemoveAura(SPELL_SHATTERED_ILLUSION);
    }

    Unit* SelectCorruptionTarget()
    {
        Player* target = NULL;
        Map::PlayerList const& pList = me->GetMap()->GetPlayers();
        uint8 num = urand(0, pList.getSize() - 1);
        uint8 count = 0;
        for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr, ++count)
        {
            if (me->GetDistance(itr->GetSource()) > 200.f || itr->GetSource()->GetPositionZ() < 300.f || !itr->GetSource()->IsAlive() || itr->GetSource()->IsGameMaster())
                continue;

            if (count <= num || !target)
                target = itr->GetSource();
            else
                break;
        }

        return target;
    }

    void UpdateAI(uint32 diff)
    {
        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (Unit* target = SelectCorruptionTarget())
        {
            uint32 spellid = RAND(SPELL_APATHY, SPELL_BLACK_PLAGUE, SPELL_DRAINING_POISON, SPELL_CURSE_OF_DOOM);
            me->CastSpell(target, spellid, false);
        }
    }
private:
    bool _zeroKeepers;
};

struct boss_yoggsaron_constrictor_tentacle : public ScriptedAI
{
    boss_yoggsaron_constrictor_tentacle(Creature* creature) : ScriptedAI(creature)
    {
        _zeroKeepers = false;
        SetCombatMovement(false);
        me->SetCanFly(true);
        me->SetDisableGravity(true);
        _checkTimer = 1;
        _playerGUID = 0;
        DoCastSelf(SPELL_VOID_ZONE_LARGE, true);

        if (me->GetInstanceScript())
        {
            if (Creature* sara = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(NPC_SARA)))
                if (sara->IsAIEnabled)
                    sara->AI()->JustSummoned(me);
        }
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == DATA_SET_ZERO_KEEPERS)
            _zeroKeepers = true;
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) && me->GetMap()->Is25ManRaid() && _zeroKeepers)
            damage = damage * 0.9f;
    }

    Unit* SelectConstrictTarget()
    {
        Player* target = NULL;
        Map::PlayerList const& pList = me->GetMap()->GetPlayers();
        uint8 num = urand(0, pList.getSize() - 1);
        uint8 count = 0;
        for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr, ++count)
        {
            if (me->GetDistance(itr->GetSource()) > 10.f || !itr->GetSource()->IsAlive() || itr->GetSource()->IsGameMaster())
                continue;
            if (itr->GetSource()->HasAura(SPELL_SQUEEZE) || itr->GetSource()->HasAura(SPELL_INSANE1))
                continue;

            if (count <= num || !target)
                target = itr->GetSource();
            else
                break;
        }

        return target;
    }

    void UpdateAI(uint32 diff) override
    {
        if (_checkTimer)
        {
            _checkTimer += diff;
            if (_checkTimer >= 1000 && !me->HasUnitState(UNIT_STATE_STUNNED))
            {
                if (Unit* target = SelectConstrictTarget())
                {
                    target->CastSpell(me, SPELL_LUNGE, true);
                    target->CastSpell(target, SPELL_SQUEEZE, true);
                    _playerGUID = target->GetGUID();
                    _checkTimer = 0;
                    return;
                }

                _checkTimer = 1;
            }
        }
    }

    void DoAction(int32 param) override
    {
        if (param == ACTION_REMOVE_STUN)
            me->RemoveAura(SPELL_SHATTERED_ILLUSION);
    }

    void JustDied(Unit*) override
    {
        me->DespawnOrUnsummon(2s);
        if (Unit* player = ObjectAccessor::GetUnit(*me, _playerGUID))
            player->RemoveAura(SPELL_SQUEEZE);
    }
private:
    bool _zeroKeepers;
    uint32 _checkTimer;
    uint64 _playerGUID;
};

struct boss_yoggsaron_keeper : public NullCreatureAI
{
    boss_yoggsaron_keeper(Creature* creature) : NullCreatureAI(creature)
    {
        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_SCALE, true);
        task.CancelAll();
        if (me->GetEntry() == NPC_MIMIRON_KEEPER)
        {
            task.Schedule(2s, [&](TaskContext func)
            {
                me->CastSpell(me, SPELL_DESTABILIZATION_MATRIX, false);
                func.Repeat(2s);
            });
        }
    }

    void DoAction(int32 param) override
    {
        if (me->GetEntry() == NPC_THORIM_KEEPER && param == ACTION_THORIM_START_STORM)
            me->CastSpell(me, SPELL_TITANIC_STORM_PASSIVE, false);
    }

    void UpdateAI(uint32 diff) override
    {
        if (me->GetInstanceScript())
            if (me->GetInstanceScript()->GetData(TYPE_YOGGSARON) != IN_PROGRESS)
                return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        task.Update(diff);
    }
private:
    TaskScheduler task;
};

class boss_yoggsaron_descend_portal : public CreatureScript
{
public:
    boss_yoggsaron_descend_portal() : CreatureScript("boss_yoggsaron_descend_portal") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!creature->GetUInt32Value(UNIT_NPC_FLAGS))
            return true;
        switch (creature->GetArmor())
        {
            case ACTION_ILLUSION_DRAGONS:    player->CastSpell(player, SPELL_TELEPORT_TO_CHAMBER, true); break;
            case ACTION_ILLUSION_ICECROWN:    player->CastSpell(player, SPELL_TELEPORT_TO_ICECROWN, true); break;
            case ACTION_ILLUSION_STORMWIND: player->CastSpell(player, SPELL_TELEPORT_TO_STORMWIND, true); break;
        }

        creature->SetUInt32Value(UNIT_NPC_FLAGS, 0);
        creature->DespawnOrUnsummon(1000);
        return true;
    }
};

struct boss_yoggsaron_influence_tentacle : public NullCreatureAI
{
    boss_yoggsaron_influence_tentacle(Creature* creature) : NullCreatureAI(creature)
    {
        _zeroKeepers = false;
        me->CastSpell(me, SPELL_GRIM_REPRISAL, true);
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == DATA_SET_ZERO_KEEPERS)
            _zeroKeepers = true;
    }

    void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (me->GetEntry() != NPC_INFLUENCE_TENTACLE)
            me->UpdateEntry(NPC_INFLUENCE_TENTACLE, 0, false);

        if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) && me->GetMap()->Is25ManRaid() && _zeroKeepers)
            damage = damage * 0.9f;
    }

    void JustDied(Unit* /*who*/) override
    {
        if (Creature* sara = me->GetSummoner())
            sara->AI()->DoAction(ACTION_INFLUENCE_TENTACLE_DIED);
    }
private:
    bool _zeroKeepers;
};

struct boss_yoggsaron_immortal_guardian : public ScriptedAI
{
    boss_yoggsaron_immortal_guardian(Creature* creature) : ScriptedAI(creature)
    {
        task.CancelAll();
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
        _ignoreMeleeAvoidance = false;
        _canAttack = false;
        _zeroKeepers = false;
        ScheduleTasks();
        me->SetVisible(false);
        if (Aura* aur = me->AddAura(SPELL_EMPOWERED_PASSIVE, me))
            aur->SetStackAmount(9);
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == DATA_SET_ZERO_KEEPERS)
            _zeroKeepers = true;
    }

    void AttackStart(Unit* who) override
    {
        if (!_canAttack)
            return;

        ScriptedAI::AttackStart(who);
    }

    void OnMeleeOutcome(WeaponAttackType type, Unit const* victim, MeleeHitOutcome& outcome, VictimAvoidanceStats stats) override
    {
        if (!victim->IsPlayer())
            return;

        if (type > OFF_ATTACK)
            return;

        //! Dont do anything if victim is over avoidance cap
        if (stats.parryChance + stats.dodgeChance + stats.missChance > 100.f)
            return;

        if (!_ignoreMeleeAvoidance)
            return;

        switch (outcome)
        {
            case MELEE_HIT_DODGE:
            case MELEE_HIT_PARRY:
            case MELEE_HIT_MISS:
            {
                outcome = MELEE_HIT_NORMAL;
                break;
            }
            default:
                break;
        }
    }

    void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (damage >= me->GetHealth())
            damage = me->GetHealth() - 1;

        if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) && me->GetMap()->Is25ManRaid() && _zeroKeepers)
            damage = damage * 0.9f;
    }

    void SpellHit(Unit* caster, const SpellInfo* spellInfo) override
    {
        if (spellInfo->Id == SPELL_SHADOW_BEACON)
        {
            caster->GetAI()->DoAction(ACTION_YOGG_SARON_SHADOW_BEACON);
            me->SetName("Marked Immortal Guardian");
        }
    }

    void ScheduleTasks()
    {
        task.Schedule(1s, [&](TaskContext /*func*/)
        {
            me->SetVisible(true);
        });

        task.Schedule(2s, [&](TaskContext /*func*/)
        {
            me->CastSpell(me, SPELL_RECENTLY_SPAWNED, true);
            me->CastSpell(me, SPELL_SIMPLE_TELEPORT, true);
        });

        task.Schedule(4s, [&](TaskContext /*func*/)
        {
            _canAttack = true;
            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                AttackStart(target);

            DoZoneInCombat(me, 250.f);
        });

        task.Schedule(15s, [&](TaskContext func)
        {
            Seconds repeatTimer = 13s;
            if (me->HealthBelowPct(85))
            {
                if (Unit* target = SelectTargetFromPlayerList(40.f))
                    me->CastSpell(target, SPELL_DRAIN_LIFE, false);
            }
            else repeatTimer = 4s;

            func.Repeat(repeatTimer);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        task.Update(diff);

        if (_canAttack)
            DoMeleeAttackIfReady();
    }
private:
    bool _zeroKeepers;
    bool _ignoreMeleeAvoidance;
    bool _canAttack;
    uint32 realDisplayId;
    TaskScheduler task;
};

struct boss_yoggsaron_lich_king : public NullCreatureAI
{
    boss_yoggsaron_lich_king(Creature* creature) : NullCreatureAI(creature) { }

    void Reset() override
    {
        _running = true;
        _checkTimer = 0;
        _step = 0;
        _championGUID = 0;
        if (me->GetInstanceScript())
            _yoggGUID = me->GetInstanceScript()->GetData64(TYPE_YOGGSARON);
    }

    void NextStep(const uint32 time)
    {
        _step++;
        _checkTimer = time;
    }

    void Say(std::string text, uint64 guid, bool yell, uint32 soundId)
    {
        Creature* creature = guid ? ObjectAccessor::GetCreature(*me, guid) : me;
        if (!creature)
            return;

        WorldPacket data;
        if (creature->GetGUID() != _yoggGUID)
        {
            ChatHandler::BuildChatPacket(data, yell ? CHAT_MSG_MONSTER_YELL : CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, creature, NULL, text);
            creature->SendMessageToSetInRange(&data, 90, true);
        }
        else if (Creature* cr = me->SummonTrigger(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() - 5, 0, 5000))
        {
            ChatHandler::BuildChatPacket(data, yell ? CHAT_MSG_MONSTER_YELL : CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, creature, NULL, text);
            cr->SendMessageToSetInRange(&data, 90, true);
        }
        else
            return;

        PlaySound(soundId);
    }

    void PlaySound(uint32 soundId)
    {
        WorldPacket data(SMSG_PLAY_SOUND, 4);
        data << uint32(soundId);
        me->SendMessageToSetInRange(&data, 90, false);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!_running)
            return;

        if (_checkTimer != 0)
        {
            _checkTimer -= diff;
            if (_checkTimer < 0)
                _checkTimer = 0;
        }
        else
        {
            switch (_step)
            {
                case 0:
                    NextStep(5000);
                    break;
                case 1:
                    if (Creature* cr = me->FindNearestCreature(NPC_IMMOLATED_CHAMPION, 50))
                        _championGUID = cr->GetGUID();
                    Say("Your resilience is admirable.", 0, false, LK_1);
                    NextStep(7000);
                    break;
                case 2:
                    Say("Arrrrrrgh!", _championGUID, true, IC_1);
                    NextStep(6000);
                    break;
                case 3:
                    Say("I'm not afraid of you!", _championGUID, false, IC_2);
                    NextStep(6500);
                    break;
                case 4:
                    Say("I will break you as I broke him.", 0, false, LK_2);
                    NextStep(7500);
                    break;
                case 5:
                    Say("Yrr n'lyeth... shuul anagg!", _yoggGUID, false, YS_V3_1);
                    NextStep(5000);
                    break;
                case 6:
                    Say("He will learn... no king rules forever; only death is eternal!", _yoggGUID, false, YS_V3_2);
                    _running = false;
                    break;
            }
        }
    }
private:
    bool _running;
    int32 _checkTimer;
    uint8 _step;
    uint64 _championGUID;
    uint64 _yoggGUID;
};

struct boss_yoggsaron_llane : public NullCreatureAI
{
    boss_yoggsaron_llane(Creature* creature) : NullCreatureAI(creature) { }

    void Reset() override
    {
        _running = true;
        _checkTimer = 0;
        _step = 0;
        _garonaGUID = 0;
        if (me->GetInstanceScript())
            _yoggGUID = me->GetInstanceScript()->GetData64(TYPE_YOGGSARON);
    }

    void NextStep(const uint32 time)
    {
        _step++;
        _checkTimer = time;
    }

    void Say(std::string text, uint64 guid, bool yell, uint32 soundId)
    {
        Creature* creature = guid ? ObjectAccessor::GetCreature(*me, guid) : me;
        if (!creature)
            return;

        WorldPacket data;
        if (creature->GetGUID() != _yoggGUID)
        {
            ChatHandler::BuildChatPacket(data, yell ? CHAT_MSG_MONSTER_YELL : CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, creature, NULL, text);
            creature->SendMessageToSetInRange(&data, 90, true);
        }
        else if (Creature* cr = me->SummonTrigger(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() - 5, 0, 5000))
        {
            ChatHandler::BuildChatPacket(data, yell ? CHAT_MSG_MONSTER_YELL : CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, creature, NULL, text);
            cr->SendMessageToSetInRange(&data, 90, true);
        }
        else
            return;

        PlaySound(soundId);
    }

    void PlaySound(uint32 soundId)
    {
        WorldPacket data(SMSG_PLAY_SOUND, 4);
        data << uint32(soundId);
        me->SendMessageToSetInRange(&data, 90, false);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!_running)
            return;

        if (_checkTimer != 0)
        {
            _checkTimer -= diff;
            if (_checkTimer < 0)
                _checkTimer = 0;
        }
        else
        {
            switch (_step)
            {
                case 0:
                    NextStep(5000);
                    break;
                case 1:
                    if (Creature* cr = me->FindNearestCreature(NPC_GARONA, 50))
                        _garonaGUID = cr->GetGUID();
                    Say("Bad news sire. The clans are united under Blackhand in this assault. They will stand together until Stormwind has fallen.", _garonaGUID, false, GAR_1);
                    NextStep(2000);
                    break;
                case 2:
                    PlaySound(GAR_2);
                    NextStep(6500);
                    break;
                case 3:
                    Say("Gul'dan is bringing up his warlocks by nightfall. Until then, the Blackrock clan will be trying to take the Eastern Wall.", _garonaGUID, false, GAR_3);
                    NextStep(11000);
                    break;
                case 4:
                    Say("A thousand deaths... or one murder.", _yoggGUID, false, YS_V1_1);
                    NextStep(2500);
                    break;
                case 5:
                    PlaySound(YS_V1_2);
                    NextStep(2500);
                    break;
                case 6:
                    Say("We will hold until the reinforcements come. As long as men with stout hearts are manning the walls and throne Stormwind will hold.", 0, false, LL_1);
                    NextStep(10000);
                    break;
                case 7:
                    Say("The orc leaders agree with your assessment.", _garonaGUID, false, GAR_4);
                    NextStep(5000);
                    break;
                case 8:
                    Say("Your petty quarrels only make me stronger!", _yoggGUID, false, YS_V1_3);
                    _running = false;
                    break;
            }
        }
    }
private:
    bool _running;
    int32 _checkTimer;
    uint8 _step;
    uint64 _garonaGUID;
    uint64 _yoggGUID;
};

struct boss_yoggsaron_neltharion : public ScriptedAI
{
    boss_yoggsaron_neltharion(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _running = true;
        _checkTimer = 0;
        _step = 0;
        if (me->GetInstanceScript())
            _yoggGUID = me->GetInstanceScript()->GetData64(TYPE_YOGGSARON);
    }

    void NextStep(const uint32 time)
    {
        _step++;
        _checkTimer = time;
    }

    void Say(std::string text, uint64 guid, bool yell, uint32 soundId)
    {
        Creature* creature = guid ? ObjectAccessor::GetCreature(*me, guid) : me;
        if (!creature)
            return;

        WorldPacket data;
        if (creature->GetGUID() != _yoggGUID)
        {
            ChatHandler::BuildChatPacket(data, yell ? CHAT_MSG_MONSTER_YELL : CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, creature, NULL, text);
            creature->SendMessageToSetInRange(&data, 90, true);
        }
        else if (Creature* cr = me->SummonTrigger(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() - 5, 0, 5000))
        {
            ChatHandler::BuildChatPacket(data, yell ? CHAT_MSG_MONSTER_YELL : CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, creature, NULL, text);
            cr->SendMessageToSetInRange(&data, 90, true);
        }
        else
            return;

        PlaySound(soundId);
    }

    void PlaySound(uint32 soundId)
    {
        WorldPacket data(SMSG_PLAY_SOUND, 4);
        data << uint32(soundId);
        me->SendMessageToSetInRange(&data, 90, false);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!_running)
            return;

        if (_checkTimer != 0)
        {
            _checkTimer -= diff;
            if (_checkTimer < 0)
                _checkTimer = 0;
        }
        else
        {
            switch (_step)
            {
                case 0:
                    NextStep(5000);
                    break;
                case 1:
                    Say("It is done... All have been given that which must be given. I now seal the Dragon Soul forever...", 0, false, NEL_1);
                    NextStep(10000);
                    break;
                case 2:
                    if (Creature* cr = me->FindNearestCreature(NPC_YSERA, 50))
                        Say("That terrible glow... should that be?", cr->GetGUID(), false, YSE_1);
                    NextStep(4000);
                    break;
                case 3:
                    Say("For it to be as it must, yes.", 0, false, NEL_2);
                    NextStep(4000);
                    break;
                case 4:
                    if (Creature* cr = me->FindNearestCreature(NPC_MALYGOS, 50))
                        Say("It is a weapon like no other. It must be like no other.", cr->GetGUID(), false, MAL_1);
                    NextStep(8000);
                    break;
                case 5:
                    Say("His brood learned their lesson before too long, you shall soon learn yours!", _yoggGUID, false, YS_V2_1);
                    _running = false;
                    break;
            }
        }
    }
private:
    bool _running;
    int32 _checkTimer;
    uint8 _step;
    uint64 _yoggGUID;
};

struct boss_yoggsaron_voice : public NullCreatureAI
{
    boss_yoggsaron_voice(Creature* creature) : NullCreatureAI(creature)
    {
        _targets.clear();
        _current = 0;
    }

    void Reset() override
    {
        me->CastSpell(me, SPELL_INSANE_PERIODIC, true);
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spellInfo) override
    {
        if (spellInfo->Id == SPELL_INSANE1)
        {
            // Drive Me Crazy achievement failed
            if (me->GetInstanceScript())
                if (Creature* yogg = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_YOGGSARON)))
                    yogg->AI()->DoAction(ACTION_FAILED_DRIVE_ME_CRAZY);

            events.ScheduleEvent(40, 8000);
            _targets.push_back(target->GetGUID());
        }
    }

    void UpdateAI(uint32 diff) override
    {
        events.Update(diff);
        switch (events.GetEvent())
        {
            case 40:
            {
                events.PopEvent();
                uint64 _guid = _targets.at(_current);
                ++_current;

                if (Player* player = ObjectAccessor::GetPlayer(*me, _guid))
                {
                    me->PlayDirectSound(15760, player);
                    me->MonsterWhisper("Destroy them minion, your master commands it!", player, false);
                }
                break;
            }
        }
    }
private:
    EventMap events;
    std::vector<uint64> _targets;
    uint32 _current;
};

class spell_yogg_saron_malady_of_the_mind : public SpellScriptLoader
{
    public:
        spell_yogg_saron_malady_of_the_mind() : SpellScriptLoader("spell_yogg_saron_malady_of_the_mind") { }

        class spell_yogg_saron_malady_of_the_mind_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_yogg_saron_malady_of_the_mind_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetUnitOwner()->ApplySpellImmune(SPELL_DEATH_RAY_DAMAGE_REAL, IMMUNITY_ID, SPELL_DEATH_RAY_DAMAGE_REAL, true);
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetUnitOwner()->ApplySpellImmune(SPELL_DEATH_RAY_DAMAGE_REAL, IMMUNITY_ID, SPELL_DEATH_RAY_DAMAGE_REAL, false);
                GetUnitOwner()->CastCustomSpell(SPELL_MALADY_OF_THE_MIND_TRIGGER, SPELLVALUE_MAX_TARGETS, 1, GetUnitOwner(), true);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_yogg_saron_malady_of_the_mind_AuraScript::OnApply, EFFECT_1, SPELL_AURA_MOD_FEAR, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_yogg_saron_malady_of_the_mind_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_MOD_FEAR, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_yogg_saron_malady_of_the_mind_AuraScript();
        }
};

class spell_yogg_saron_brain_link : public SpellScriptLoader
{
    public:
        spell_yogg_saron_brain_link() : SpellScriptLoader("spell_yogg_saron_brain_link") { }

        class spell_yogg_saron_brain_link_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_yogg_saron_brain_link_AuraScript);

            void HandleOnEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                PreventDefaultAction();
                Player* target = NULL;
                Map::PlayerList const& pList = GetUnitOwner()->GetMap()->GetPlayers();
                uint8 _offset = urand(0, pList.getSize()-1);
                uint8 _counter = 0;
                for(Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr, ++_counter)
                {
                    if (itr->GetSource() == GetUnitOwner() || GetUnitOwner()->GetDistance(itr->GetSource()) > 50.0f || !itr->GetSource()->IsAlive() || itr->GetSource()->IsGameMaster())
                        continue;

                    if (_counter <= _offset || !target)
                        target = itr->GetSource();
                    else
                        break;
                }

                if (!target)
                    SetDuration(0);
                else
                    _targetGUID = target->GetGUID();
            }

            void OnPeriodic(AuraEffect const* aurEff)
            {
                Unit* owner = GetUnitOwner();
                Unit* _target = ObjectAccessor::GetUnit(*owner, _targetGUID);
                if (!owner || !_target || !_target->IsAlive() || fabs(owner->GetPositionZ() - _target->GetPositionZ()) > 10.0f) // Target or owner underground
                {
                    SetDuration(0);
                    return;
                }

                if (owner->GetDistance(_target) > 20.0f)
                {
                    owner->CastSpell(_target, SPELL_BRAIN_LINK_DAMAGE, true);
                    owner->CastSpell(owner, SPELL_BRAIN_LINK_DAMAGE, true);
                }
                else
                    owner->CastSpell(_target, SPELL_BRAIN_LINK_OK, true);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_yogg_saron_brain_link_AuraScript::HandleOnEffectApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_yogg_saron_brain_link_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }

            protected:
                uint64 _targetGUID;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_yogg_saron_brain_link_AuraScript();
        }

        class spell_yogg_saron_brain_link_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_yogg_saron_brain_link_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                std::list<WorldObject*> tempList;
                for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    if ((*itr)->GetPositionZ() > 300.0f)
                        tempList.push_back(*itr);

                targets.clear();
                for (std::list<WorldObject*>::iterator itr = tempList.begin(); itr != tempList.end(); ++itr)
                    targets.push_back(*itr);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_yogg_saron_brain_link_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_yogg_saron_brain_link_SpellScript();
        }
};

class spell_yogg_saron_destabilization_matrix : public SpellScriptLoader
{
    public:
        spell_yogg_saron_destabilization_matrix() : SpellScriptLoader("spell_yogg_saron_destabilization_matrix") { }

        class spell_yogg_saron_destabilization_matrix_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_yogg_saron_destabilization_matrix_SpellScript);

            void HandleDummyEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                if (Unit* target = GetHitUnit())
                    GetCaster()->CastSpell(target, SPELL_DESTABILIZATION_MATRIX_ATTACK, false);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                WorldObject* target = NULL;
                for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    if (!(*itr)->ToUnit()->HasAura(SPELL_DESTABILIZATION_MATRIX_ATTACK))
                    {
                        target = *itr;
                        break;
                    }

                targets.clear();
                if (target)
                    targets.push_back(target);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_yogg_saron_destabilization_matrix_SpellScript::HandleDummyEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_yogg_saron_destabilization_matrix_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_yogg_saron_destabilization_matrix_SpellScript();
        }
};

class spell_yogg_saron_titanic_storm : public SpellScriptLoader
{
    public:
        spell_yogg_saron_titanic_storm() : SpellScriptLoader("spell_yogg_saron_titanic_storm") { }

        class spell_yogg_saron_titanic_storm_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_yogg_saron_titanic_storm_SpellScript);

            void HandleDummyEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                if (Unit* target = GetHitUnit())
                    Unit::Kill(GetCaster(), target);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                WorldObject* target = NULL;
                for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    if ((*itr)->ToUnit()->HasAura(SPELL_WEAKENED))
                    {
                        target = *itr;
                        break;
                    }

                targets.clear();
                if (target)
                    targets.push_back(target);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_yogg_saron_titanic_storm_SpellScript::HandleDummyEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_yogg_saron_titanic_storm_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_yogg_saron_titanic_storm_SpellScript();
        }
};

class spell_yogg_saron_lunatic_gaze : public SpellScriptLoader
{
    public:
        spell_yogg_saron_lunatic_gaze() : SpellScriptLoader("spell_yogg_saron_lunatic_gaze") { }

        class spell_yogg_saron_lunatic_gaze_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_yogg_saron_lunatic_gaze_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if([&](WorldObject* object)
                {
                    return !object->HasInArc(static_cast<float>(M_PI), GetCaster());
                });
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_yogg_saron_lunatic_gaze_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_yogg_saron_lunatic_gaze_SpellScript();
        }
};

// Protective Gaze
class spell_yogg_saron_protective_gaze : public SpellScriptLoader
{
public:
    spell_yogg_saron_protective_gaze() : SpellScriptLoader("spell_yogg_saron_protective_gaze") { }

    class spell_yogg_saron_protective_gaze_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_yogg_saron_protective_gaze_AuraScript);


        void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
        {
            // Set absorbtion amount to unlimited
            amount = -1;
        }

        void Absorb(AuraEffect * /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit* target = GetTarget();

            if (target->GetTypeId() != TYPEID_PLAYER)
                return;

            if (dmgInfo.GetDamage() < target->GetHealth() || !GetCaster() || GetCaster()->ToCreature()->HasSpellCooldown(SPELL_HODIR_FLASH_FREEZE))
                return;

            target->CastSpell(target, SPELL_HODIR_FLASH_FREEZE, true);
            GetCaster()->AddSpellCooldown(SPELL_HODIR_FLASH_FREEZE, 0, 0);
            absorbAmount = dmgInfo.GetDamage();
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_yogg_saron_protective_gaze_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_yogg_saron_protective_gaze_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript *GetAuraScript() const
    {
        return new spell_yogg_saron_protective_gaze_AuraScript();
    }
};

class spell_yogg_saron_empowered : public SpellScriptLoader
{
    public:
        spell_yogg_saron_empowered() : SpellScriptLoader("spell_yogg_saron_empowered") { }

        class spell_yogg_saron_empowered_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_yogg_saron_empowered_AuraScript);

            void OnPeriodic(AuraEffect const* aurEff)
            {
                Unit* target = GetUnitOwner();
                uint8 stack = std::min(uint8(target->GetHealthPct()/10), (uint8)9);

                if (!stack)
                {
                    target->RemoveAura(SPELL_EMPOWERED);
                    target->CastSpell(target, SPELL_WEAKENED, true);
                }
                else if (Aura* aur = target->AddAura(SPELL_EMPOWERED, target))
                {
                    aur->SetStackAmount(stack);
                    target->RemoveAurasDueToSpell(SPELL_WEAKENED);
                }
            }

            void Register() override
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_yogg_saron_empowered_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_yogg_saron_empowered_AuraScript();
        }
};

class spell_yogg_saron_insane_periodic_trigger : public SpellScriptLoader
{
    public:
        spell_yogg_saron_insane_periodic_trigger() : SpellScriptLoader("spell_yogg_saron_insane_periodic_trigger") { }

        class spell_yogg_saron_insane_periodic_trigger_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_yogg_saron_insane_periodic_trigger_SpellScript);

            void HandleDummyEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Player* target = GetHitPlayer();
                if (!target)
                    return;

                Unit* caster = GetCaster();
                caster->PlayDirectSound(VOYS_INSANE1, target);
                caster->MonsterWhisper("Your will is no longer you own...", target, false);
                caster->CastSpell(target, SPELL_INSANE1, true);
                target->CastSpell(target, SPELL_INSANE2, true);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                std::list<WorldObject*> tmplist;
                for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    if ((*itr)->GetTypeId() == TYPEID_PLAYER && !(*itr)->ToPlayer()->HasAuraType(SPELL_AURA_AOE_CHARM) && !(*itr)->ToPlayer()->HasAura(SPELL_SANITY))
                        tmplist.push_back(*itr);

                 targets.clear();
                 for (std::list<WorldObject*>::iterator itr = tmplist.begin(); itr != tmplist.end(); ++itr)
                     targets.push_back(*itr);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_yogg_saron_insane_periodic_trigger_SpellScript::HandleDummyEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_yogg_saron_insane_periodic_trigger_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_yogg_saron_insane_periodic_trigger_SpellScript();
        }
};

class spell_yogg_saron_insane : public SpellScriptLoader
{
    public:
        spell_yogg_saron_insane() : SpellScriptLoader("spell_yogg_saron_insane") { }

        class spell_yogg_saron_insane_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_yogg_saron_insane_AuraScript);

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit::Kill(GetUnitOwner(), GetUnitOwner());
            }

            void Register()
            {
                 OnEffectRemove += AuraEffectRemoveFn(spell_yogg_saron_insane_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_AOE_CHARM, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_yogg_saron_insane_AuraScript();
        }
};

class spell_yogg_saron_sanity_well : public SpellScriptLoader
{
    public:
        spell_yogg_saron_sanity_well() : SpellScriptLoader("spell_yogg_saron_sanity_well") { }

        class spell_yogg_saron_sanity_well_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_yogg_saron_sanity_well_AuraScript);

            void HandleEffectCalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
            {
                isPeriodic = true;
                amplitude = 2*IN_MILLISECONDS;
            }

            void HandleEffectPeriodic(AuraEffect const * aurEff)
            {
                Unit* target = GetTarget();
                if (!target || target->GetTypeId() != TYPEID_PLAYER)
                    return;

                if (Aura* aur = target->GetAura(SPELL_SANITY))
                    aur->SetStackAmount(std::min(100, aur->GetStackAmount()+20));
            }

            void Register()
            {
                DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_yogg_saron_sanity_well_AuraScript::HandleEffectCalcPeriodic, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_yogg_saron_sanity_well_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_yogg_saron_sanity_well_AuraScript();
        }
};

class spell_yogg_saron_sanity_reduce : public SpellScriptLoader
{
public:
    spell_yogg_saron_sanity_reduce() : SpellScriptLoader("spell_yogg_saron_sanity_reduce") { }

    class spell_yogg_saron_sanity_reduce_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_yogg_saron_sanity_reduce_SpellScript);

        void HandleScriptEffect(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            Player* target = GetHitPlayer();
            if (!target)
                return;

            uint8 _reduceAmount = 0;
            switch (GetSpellInfo()->Id)
            {
                case SPELL_SARA_PSYCHOSIS_10:             _reduceAmount = 9; break;
                case SPELL_SARA_PSYCHOSIS_25:             _reduceAmount = 12; break;
                case SPELL_MALADY_OF_THE_MIND:            _reduceAmount = 3; break;
                case SPELL_MALADY_OF_THE_MIND_TRIGGER:    _reduceAmount = 3; break;
                case SPELL_BRAIN_LINK_DAMAGE:             _reduceAmount = 2; break;
                case SPELL_DOMINATE_MIND:                 _reduceAmount = 4; break;
                case 64168 /*SPELL_LUNATIC_GAZE*/:        _reduceAmount = 2; break;
                case 64164 /*SPELL_YS_LUNATIC_GAZE*/:     _reduceAmount = 4; break;
                case SPELL_INDUCE_MADNESS:
                    // Teleported out of brain
                    if (target->GetPositionZ() > 300.0f)
                        return;
                    else
                        target->CastSpell(target, SPELL_CANCEL_ILLUSION_AURA, true); // else we are underground, remove illusion aura and teleport outside
                    _reduceAmount = 100;
                    break;
            }

            if (Aura* aur = target->GetAura(SPELL_SANITY))
            {
                if ((aur->GetStackAmount() - _reduceAmount) <= 20)
                    target->CastSpell(target, 63752 /*SANITY_SCREEN_EFFECT*/, true);
                aur->ModStackAmount(-_reduceAmount);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_yogg_saron_sanity_reduce_SpellScript::HandleScriptEffect, EFFECT_FIRST_FOUND, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_yogg_saron_sanity_reduce_SpellScript();
    }
};

class spell_yogg_saron_empowering_shadows : public SpellScriptLoader
{
    public:
        spell_yogg_saron_empowering_shadows() : SpellScriptLoader("spell_yogg_saron_empowering_shadows") { }

        class spell_yogg_saron_empowering_shadows_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_yogg_saron_empowering_shadows_SpellScript);

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, target->GetMap()->Is25ManRaid() ? 64486 : 64468, true); // SPELL_EMPOWERING_SHADOWS_HEAL
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_yogg_saron_empowering_shadows_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_yogg_saron_empowering_shadows_SpellScript();
        }
};

class spell_yogg_saron_in_the_maws_of_the_old_god : public SpellScriptLoader
{
    public:
        spell_yogg_saron_in_the_maws_of_the_old_god() : SpellScriptLoader("spell_yogg_saron_in_the_maws_of_the_old_god") {}

        class spell_yogg_saron_in_the_maws_of_the_old_god_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_yogg_saron_in_the_maws_of_the_old_god_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return SPELL_FAILED_BAD_TARGETS;

                Unit* target = GetCaster()->ToPlayer()->GetSelectedUnit();
                if (!target || target->GetEntry() != NPC_YOGG_SARON)
                    return SPELL_FAILED_BAD_TARGETS;

                Spell* spell = target->GetCurrentSpell(CURRENT_GENERIC_SPELL);
                if (!spell || spell->GetSpellInfo()->Id != SPELL_DEAFENING_ROAR)
                    return SPELL_FAILED_TARGET_AURASTATE;

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_yogg_saron_in_the_maws_of_the_old_god_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_yogg_saron_in_the_maws_of_the_old_god_SpellScript();
        }
};

class spell_yogg_saron_target_selectors : public SpellScriptLoader    // 63744, 63745, 63747, 65206
{
    public:
        spell_yogg_saron_target_selectors() : SpellScriptLoader("spell_yogg_saron_target_selectors") { }

        class spell_yogg_saron_target_selectors_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_yogg_saron_target_selectors_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                WorldObject* target = nullptr;
                //! destabilization matrix can hit non-player targets
                if (GetSpellInfo()->Id != SPELL_DESTABILIZATION_MATRIX)
                {
                    targets.remove_if([](WorldObject* object)
                    {
                        return !object->IsPlayer();
                    });
                }
                if (!targets.empty())
                {
                    target = Trinity::Containers::SelectRandomContainerElement(targets);
                }

                targets.clear();
                if (target)
                    targets.push_back(target);
            }

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    GetCaster()->SetFacingToObject(target);
                    GetCaster()->CastSpell(target, uint32(GetEffectValue()));
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_yogg_saron_target_selectors_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
                OnEffectHitTarget += SpellEffectFn(spell_yogg_saron_target_selectors_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_yogg_saron_target_selectors_SpellScript();
        }
};

class spell_yogg_saron_grim_reprisal : public SpellScriptLoader     // 63305
{
    public:
        spell_yogg_saron_grim_reprisal() : SpellScriptLoader("spell_yogg_saron_grim_reprisal") { }

        class spell_yogg_saron_grim_reprisal_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_yogg_saron_grim_reprisal_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_GRIM_REPRISAL_DAMAGE))
                    return false;
                return true;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                int32 damage = CalculatePct(int32(eventInfo.GetDamageInfo()->GetDamage()), 60);
                GetTarget()->CastCustomSpell(SPELL_GRIM_REPRISAL_DAMAGE, SPELLVALUE_BASE_POINT0, damage, eventInfo.GetDamageInfo()->GetAttacker(), true, NULL, aurEff);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_yogg_saron_grim_reprisal_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_yogg_saron_grim_reprisal_AuraScript();
        }
};

class spell_summon_tentacle_position_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_summon_tentacle_position_SpellScript);

    void ChangeSummonPos(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        Position casterPos = caster->GetPosition();

        WorldLocation summonPos = *GetExplTargetDest();

        float angle = (float)rand_norm()*static_cast<float>(2 * M_PI);
        float dist;

        dist = frand(30.0f, 38.0f); // for summon Constrictor && Corruptor tentacles
        if (GetSpellInfo()->Id == SPELL_SUMMON_CONSTRICTOR_TENTACLE)
            dist = 8.f;

        summonPos.m_positionX = casterPos.m_positionX + dist * std::cos(angle);
        summonPos.m_positionY = casterPos.m_positionY + dist * std::sin(angle);
        summonPos.m_positionZ = caster->GetMap()->GetHeight(caster->GetPhaseMask(), summonPos.m_positionX, summonPos.m_positionY, casterPos.m_positionZ);
        //! something went wrong, we've got position below arena
        if (summonPos.m_positionZ < 324.88f)
            //! fallback position
            summonPos.m_positionZ = 330.50f;

        SetExplTargetDest(summonPos);
        GetHitDest()->Relocate(summonPos);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_summon_tentacle_position_SpellScript::ChangeSummonPos, EFFECT_0, SPELL_EFFECT_SUMMON);
    }
};

class spell_yogg_saron_constrictor_tentacle : public SpellScriptLoader
{
public:
    spell_yogg_saron_constrictor_tentacle() : SpellScriptLoader("spell_yogg_saron_constrictor_tentacle") {}

    class spell_yogg_saron_constrictor_tentacle_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_yogg_saron_constrictor_tentacle_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            WorldObject* _target = nullptr;

            targets.remove_if([](WorldObject* object) -> bool
            {
                if (!object->ToPlayer())
                    return true;

                if (object->ToPlayer()->HasAura(SPELL_SQUEEZE_10) || object->ToPlayer()->HasAura(SPELL_SQUEEZE_25))
                    return true;

                if (object->ToPlayer()->HasAuraWithMechanic(1 << MECHANIC_IMMUNE_SHIELD))
                    return true;

                if (object->ToPlayer()->HasAura(SPELL_ILLUSION_ROOM))
                    return true;

                if (object->GetPositionZ() < 320.f)
                    return true;

                return false;
            });

            if (!targets.empty())
            {
                _target = Trinity::Containers::SelectRandomContainerElement(targets);

                if (_target)
                {
                    targets.clear();
                    targets.push_back(_target);
                }
            }
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_yogg_saron_constrictor_tentacle_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    class spell_yogg_saron_constrictor_tentacle_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_yogg_saron_constrictor_tentacle_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTarget())
                GetTarget()->CastSpell(GetTarget(), SPELL_SUMMON_CONSTRICTOR_TENTACLE);
        }

        void Register() override
        {
            AfterEffectApply += AuraEffectApplyFn(spell_yogg_saron_constrictor_tentacle_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_yogg_saron_constrictor_tentacle_SpellScript();
    }

    AuraScript* GetAuraScript() const override
    {
        return new spell_yogg_saron_constrictor_tentacle_AuraScript();
    }
};

uint32 const SPELL_BLACK_PLAGUE_TRIGGERED = 64155;

class spell_black_plague_yogg_saron_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_black_plague_yogg_saron_AuraScript);

    void OnPeriodic(AuraEffect const* aurEff)
    {
        PreventDefaultAction();

        if (GetTarget())
            GetTarget()->CastSpell(GetTarget(), SPELL_BLACK_PLAGUE_TRIGGERED, TRIGGERED_NONE, nullptr, nullptr, GetTarget()->GetGUID());
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_black_plague_yogg_saron_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

class spell_squeeze_tentacle_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_squeeze_tentacle_AuraScript);

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        //! Hack till we rewrite immunity handling which is screwed up right now, im crying inside :(
        if (GetTarget())
        {
            if (GetTarget()->HasAura(1022) || GetTarget()->HasAura(5599) || GetTarget()->HasAura(10278) || GetTarget()->HasAura(66009))
                PreventDefaultAction();
        }
    }

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetTarget())
            GetTarget()->ApplySpellImmune(SPELL_DEATH_RAY_DAMAGE_REAL, IMMUNITY_ID, SPELL_DEATH_RAY_DAMAGE_REAL, true);
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetTarget())
            GetTarget()->ApplySpellImmune(SPELL_DEATH_RAY_DAMAGE_REAL, IMMUNITY_ID, SPELL_DEATH_RAY_DAMAGE_REAL, false);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_squeeze_tentacle_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_squeeze_tentacle_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_squeeze_tentacle_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

class spell_dominate_mind_guardian_of_ys_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_dominate_mind_guardian_of_ys_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (!GetCaster())
            return;

        targets.remove_if([&](WorldObject* object)
        {
            return GetCaster()->GetVictim() == object;
        });
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (!GetHitUnit())
            return;

        if (Aura* aur = GetHitUnit()->GetAura(SPELL_SANITY))
        {
            if ((aur->GetStackAmount() - 4) > 20)
            {
                GetHitUnit()->CastSpell(GetHitUnit(), 63752 /*SANITY_SCREEN_EFFECT*/, true);
                aur->ModStackAmount(-4);
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dominate_mind_guardian_of_ys_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dominate_mind_guardian_of_ys_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

class achievement_yogg_saron_drive_me_crazy : public AchievementCriteriaScript
{
    public:
        achievement_yogg_saron_drive_me_crazy() : AchievementCriteriaScript("achievement_yogg_saron_drive_me_crazy") {}

        bool OnCheck(Player* player, Unit* target)
        {
            return target && target->GetAI()->GetData(ACTION_FAILED_DRIVE_ME_CRAZY); // target = Yogg-Saron
        }
};

class achievement_yogg_saron_darkness : public AchievementCriteriaScript
{
    public:
        achievement_yogg_saron_darkness(char const* name, uint32 count) : AchievementCriteriaScript(name),
            _keepersCount(count)
        {
        }

        bool OnCheck(Player* player, Unit* target /*Yogg-Saron*/)
        {
            if (player->GetInstanceScript())
                if (Creature* sara = ObjectAccessor::GetCreature(*player, player->GetInstanceScript()->GetData64(NPC_SARA)))
                    return sara->GetAI()->GetData(DATA_GET_KEEPERS_COUNT) <= _keepersCount;

            return false;
        }

    private:
        uint32 const _keepersCount;
};

class achievement_yogg_saron_he_waits_dreaming : public AchievementCriteriaScript
{
    public:
        achievement_yogg_saron_he_waits_dreaming(char const* name, uint8 illusion) : AchievementCriteriaScript(name),
            _requiredIllusion(illusion)
        {
        }

        bool OnCheck(Player* player, Unit* target /*Yogg-Saron*/)
        {
            if (player->GetInstanceScript())
                if (Creature* sara = ObjectAccessor::GetCreature(*player, player->GetInstanceScript()->GetData64(NPC_BRAIN_OF_YOGG_SARON)))
                    return sara->GetAI()->GetData(DATA_GET_CURRENT_ILLUSION) == _requiredIllusion;

            return false;
        }

    private:
        uint8 const _requiredIllusion;
};


class achievement_yogg_saron_kiss_and_make_up : public AchievementCriteriaScript
{
    public:
        achievement_yogg_saron_kiss_and_make_up() : AchievementCriteriaScript("achievement_yogg_saron_kiss_and_make_up") {}

        bool OnCheck(Player* player, Unit* target /*Sara*/)
        {
            return target && target->GetEntry() == NPC_SARA && target->GetAI() && target->GetAI()->GetData(DATA_GET_SARA_PHASE);
        }
};

void AddSC_boss_yoggsaron()
{
    RegisterCreatureAI(boss_yoggsaron);
    RegisterCreatureAI(boss_yoggsaron_sara);
    RegisterCreatureAI(boss_yoggsaron_cloud);
    RegisterCreatureAI(boss_yoggsaron_guardian_of_ys);
    RegisterCreatureAI(boss_yoggsaron_brain);
    RegisterCreatureAI(boss_yoggsaron_death_orb);
    RegisterCreatureAI(boss_yoggsaron_crusher_tentacle);
    RegisterCreatureAI(boss_yoggsaron_corruptor_tentacle);
    RegisterCreatureAI(boss_yoggsaron_constrictor_tentacle);
    RegisterCreatureAI(boss_yoggsaron_keeper);
    new boss_yoggsaron_descend_portal();
    RegisterCreatureAI(boss_yoggsaron_influence_tentacle);
    RegisterCreatureAI(boss_yoggsaron_immortal_guardian);
    RegisterCreatureAI(boss_yoggsaron_lich_king);
    RegisterCreatureAI(boss_yoggsaron_llane);
    RegisterCreatureAI(boss_yoggsaron_neltharion);
    RegisterCreatureAI(boss_yoggsaron_voice);

    // SPELLS
    new spell_yogg_saron_malady_of_the_mind();
    new spell_yogg_saron_brain_link();
    new spell_yogg_saron_destabilization_matrix();
    new spell_yogg_saron_titanic_storm();
    new spell_yogg_saron_lunatic_gaze();
    new spell_yogg_saron_protective_gaze();
    new spell_yogg_saron_empowered();
    new spell_yogg_saron_insane_periodic_trigger();
    new spell_yogg_saron_insane();
    new spell_yogg_saron_sanity_well();
    new spell_yogg_saron_sanity_reduce();
    new spell_yogg_saron_empowering_shadows();
    new spell_yogg_saron_in_the_maws_of_the_old_god();
    new spell_yogg_saron_target_selectors();
    new spell_yogg_saron_grim_reprisal();
    new SpellScriptLoaderEx<spell_summon_tentacle_position_SpellScript>("spell_summon_tentacle_position");
    new spell_yogg_saron_constrictor_tentacle();
    new AuraScriptLoaderEx<spell_squeeze_tentacle_AuraScript>("spell_squeeze_tentacle");
    new AuraScriptLoaderEx<spell_black_plague_yogg_saron_AuraScript>("spell_black_plague_yogg_saron");
    new SpellScriptLoaderEx<spell_dominate_mind_guardian_of_ys_SpellScript>("spell_dominate_mind_guardian_of_ys");

    // ACHIEVEMENTS
    new achievement_yogg_saron_drive_me_crazy();
    new achievement_yogg_saron_darkness("achievement_yogg_saron_three_lights_in_the_darkness", 3);
    new achievement_yogg_saron_darkness("achievement_yogg_saron_two_lights_in_the_darkness", 2);
    new achievement_yogg_saron_darkness("achievement_yogg_saron_one_light_in_the_darkness", 1);
    new achievement_yogg_saron_darkness("achievement_yogg_saron_alone_in_the_darkness", 0);
    new achievement_yogg_saron_he_waits_dreaming("achievement_yogg_saron_he_waits_dreaming_stormwind", ACTION_ILLUSION_STORMWIND);
    new achievement_yogg_saron_he_waits_dreaming("achievement_yogg_saron_he_waits_dreaming_chamber", ACTION_ILLUSION_DRAGONS);
    new achievement_yogg_saron_he_waits_dreaming("achievement_yogg_saron_he_waits_dreaming_icecrown", ACTION_ILLUSION_ICECROWN);
    new achievement_yogg_saron_kiss_and_make_up();
}
