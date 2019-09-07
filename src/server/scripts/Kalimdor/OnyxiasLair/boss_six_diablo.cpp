#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "onyxias_lair.h"
#include "SpellScript.h"
#include "MoveSplineInit.h"
#include "GameObjectAI.h"
#include "WorldCache.h"

enum DiabloSpells
{
    SPELL_DIABLO_NETHER_PORTAL_VISUAL       = 66263,
    SPELL_DIABLO_EYE_BEAM                   = 49544,
    SPELL_DIABLO_HEART_BEAM_VISUAL          = 54988,
    SPELL_DIABLO_REALM_OF_SHADOWS           = 52693,
    SPELL_DIABLO_RED_BEAM_DROPS             = 30944,
    SPELL_DIABLO_SMOKEY_MARKER              = 16714,
    SPELL_DIABLO_FLAME_BUFFET               = 34121,
    SPELL_DIABLO_RUNE_DETONATION            = 62527,
    SPELL_DIABLO_FLAMETONGUE_ATTACK         = 68111,
    SPELL_DIABLO_SHADOWFORM_1               = 55086,
    SPELL_DIABLO_SHADOWFORM_2               = 63359,
    SPELL_DIABLO_SELF_STUN                  = 62794,
    SPELL_DIABLO_RAGING_SPIRIT_VISUAL       = 69198,
    SPELL_DIABLO_MC_INSANE                  = 63120,
    SPELL_DIABLO_FLAMETONGUE_WEAPON         = 65979,
    SPELL_DIABLO_BALL_OF_FLAMES_VISUAL      = 71706,
    SPELL_DIABLO_SOUL_SIPHON                = 43501,
    SPELL_DIABLO_SPIRIT_BURN                = 54651,
    SPELL_DIABLO_SHADOW_STEP_COSMETIC       = 51908,
    SPELL_DIABLO_NAPALM_SHELL               = 68832,
    SPELL_DIABLO_BUFFETTING_WINDS           = 32474,
    SPELL_DIABLO_CONVERSION_BEAM            = 69856,
    SPELL_DIABLO_EXPLOSION                  = 52146,
    SPELL_DIABLO_BLUE_EXPLOSION             = 70509,
    SPELL_DIABLO_PORTAL_STATE_VISUAL        = 46907,
    SPELL_DIABLO_DEVOURING_FLAME            = 63236,
    SPELL_DIABLO_LIGHTNING_MARKER_VISUAL    = 61585,
    SPELL_DIABLO_THUNDERSHOCK               = 56926,
    SPELL_DIABLO_RUNIC_LIGHTNING            = 62445,
    SPELL_DIABLO_TRIGGER_EXPLOSION          = 35470,
    SPELL_DIABLO_TRIGGER_FLAME_PATCH        = 69671,
    SPELL_DIABLO_ELEMENTAL_ADD_EXPLODE      = 69669,
    SPELL_DIABLO_VICINITY_CHECKER_TRIGGER   = 56543,
    SPELL_DIABLO_MAGNETIC_FIELD             = 64668,
    SPELL_DIABLO_EXPLODING_HEART            = 27676,
    SPELL_DIABLO_ARMAGEDDON                 = 20478,
    SPELL_DIABLO_INFERNAL_HELLFIRE          = 65817,
    SPELL_DIABLO_SUMMON_VISUAL              = 54111,
    SPELL_DIABLO_STATIC_OVERLOAD            = 59798,
    SPELL_DIABLO_ASCEND                     = 64487,
    SPELL_DIABLO_FIVE_FAT_FINGERS           = 27673,
    SPELL_DIABLO_WRATH_INTERRUPT            = 21667,
    SPELL_DIABLO_PLASMA_RAY                 = 64529,
    SPELL_DIABLO_COSMETIC_WHITE_SMOKE       = 43467,
    SPELL_DIABLO_METEOR                     = 36837,
    SPELL_DIABLO_RING_OF_FLAME              = 35831,
    SPELL_DIABLO_REFLECT_DAMAGE_FIREBOLT    = 44577,
    SPELL_DIABLO_SHADOW_DRAKE_VOID_BLAST    = 46161,
    SPELL_DIABLO_IMPALE_VISUAL              = 53455
};

enum DiabloCreatures
{
    NPC_BOSS_SIX_DIABLO                     = 250200,
    NPC_BOSS_SIX_PORTAL_TRIGGER             = 250201,
    NPC_BOSS_SIX_ABYSS_KNIGHT               = 250202,
    NPC_BOSS_SIX_OMOR_COPY                  = 250203,
    NPC_BOSS_SIX_BEAM_TRIGGER               = 250204,
    NPC_BOSS_SIX_BEAM_TRIGGER_EXPLO_TRIGGER = 250205,
    NPC_BOSS_SIX_HEART_BEAM_TRIGGER         = 250206,
    NPC_BOSS_SIX_FIERY_COMET_TRIGGER        = 250207,
    NPC_BOSS_SIX_PENTAGON_TRIGGER_1         = 250208, // all the way to 250212
    /* Pentagon triggers gap */

    NPC_BOSS_SIX_DIABOLIC_INFERNAL          = 250213,
    NPC_BOSS_SIX_INCREASED_DAMAGE_TRIGGER   = 250214,
    NPC_BOSS_SIX_UNSTABLE_FIRE_ELEMENTAL    = 250215,
    NPC_BOSS_SIX_BALL_OF_FLAMES_PLAYER      = 250216,
    NPC_BOSS_SIX_BALL_OF_FLAMES_BOSS        = 250217,
    NPC_BOSS_SIX_ASHES_OF_ALAR              = 250218,
    NPC_BOSS_SIX_SHADOW_DRAKE               = 250219,
    NPC_BOSS_SIX_NAPALAM_SHELL_TRIGGER      = 250220,
    NPC_BOSS_SIX_METEOR_CASTER_TRIGGER      = 250221,
    NPC_BOSS_SIX_PORTAL_TRIGGER_VISUAL      = 250222,
    NPC_BOSS_SIX_SHADOW_CRYSTAL             = 250223,

    NPC_WORLD_TRIGGER                       = 22515
};

enum DiabloMisc
{
    DIABLO_MAP_ID                           = 249,
    DATA_SET_DEMON_TYPE,
    DATA_SWITCH_DEMON_TYPE,
    GROUP_DEMON_SWITCHABLE,
    DATA_EXPLOSION_TIMER,
    GROUP_DIABLO_CANCELABLE,
    ACTION_FLAME_ORB_ARRIVED,
    GROUP_DIABLO_PHASE_ONE_CANCELABLE
};

enum DiabloPointIDs
{
    POINT_ID_DIABLO_FIREBEAMS               = 1,
    POINT_ID_FLAME_ORB_PLAYER,
    POINT_ID_MIDDLE_INTERMISSION
};

enum DiabloStatIds
{
    STAT_DIABLO_NAPALAM_SHELL_PERCENTAGE                        = 150,
    STAT_DIABLO_NAPALAM_SHELL_TIMER,
    STAT_DIABLO_NAPALAM_SHELL_READJUST_HEALTH_PERCENTAGE,
    STAT_DIABLO_NAPALAM_SHELL_COUNT,
    STAT_DIABLO_NAPALAM_SHELL_READJUSTED_COUNT,
    STAT_DIABLO_INTERMISSION_PERCENTAGE,
    STAT_DIABLO_SHADOW_STEP_EXPLOSION_DAMAGE,
    STAT_DIABLO_SHADOW_STEP_EXPLOSION_RADIUS_RATIO,
    STAT_DIABLO_NAPALAM_SHELL_DAMAGE,
    STAT_DIABLO_NAPALAM_SHELL_RADIUS_RATIO,
    STAT_DIABLO_SHADOW_REALM_TIMER,
    STAT_DIABLO_P1_KNOCKBACK_TIMER,
    STAT_DIABLO_P1_KNOCKBACK_REPEAT_TIMER,
    STAT_DIABLO_P1_SHADOWSTEP_FIRST_TIMER,
    STAT_DIABLO_P1_SHADOWSTEP_REPEAT_TIMER,
    STAT_DIABLO_P2_SHADOWSTEP_OR_KNOCKBACK_FIRST_TIMER,
    STAT_DIABLO_P2_SHADOWSTEP_OR_KNOCKBACK_REPEAT_TIMER,
    STAT_DIABLO_FIRE_ELEMENTALS_FIRST_SPAWN_TIMER,
    STAT_DIABLO_FIRE_ELEMENTALS_REPEAT_SPAWN_TIMER,
    STAT_DIABLO_PLASMA_RAY_FIRST_TIMER,
    STAT_DIABLO_PLASMA_RAY_REPEAT_TIMER,
    STAT_DIABLO_PHEONIX_FIRST_TIMER,
    STAT_DIABLO_PHEONIX_REPEATE_TIMER,
    STAT_DIABLO_FIREBEAM_TIMER,                                 // executes after shadow realm, fail or not
    STAT_DIABLO_PLAYER_SPHERES_MOVE_RATIO,                      // Ratio for SetSpeedRatio (move run)
    STAT_DIABLO_PLASMA_RAY_DAMAGE,
    STAT_DIABLO_PHEONIX_PHASE_CAST_TIMER,
    STAT_DIABLO_PHEONIX_CAST_TIME,                              // in milliseconds, diablo wipe spell cast time (unless interrupted)
    STAT_DIABLO_ASHES_OF_ALAR_COUNT,
    STAT_DIABLO_SHADOW_DRAKE_COUNT,
    STAT_DIABLO_SHADOW_REALM_FAIL_TIMER,
    STAT_DIABLO_ARMAGEDDON_DURATION,
    STAT_DIABLO_ARMAGEDDON_RADIUS_RATIO,
    STAT_DIABLO_ARMAGEDDON_DAMAGE,
    STAT_DIABLO_WINDS_DAMAGE,
    STAT_DIABLO_SPIRIT_BURN_DAMAGE,
    STAT_DIABLO_PLASMA_RAY_WIDTH,
    STAT_DIABLO_THUNDERSHOCK_DAMAGE,

    /** Misc **/
    // 232 is taken
    STAT_DIABLO_BUFFETING_WINDS_RADIUS                          = 233,
    STAT_DIABLO_FIVE_FAT_FINGERS_PROC_CHANCE                    = 234,
    STAT_DIABLO_OFFHAND_PROC_DAMAGE                             = 235,

    /** Health **/
    STAT_ABYSSAL_KNIGHT_HEALTH,
    STAT_PITLORD_HEALTH,
    STAT_DIABLO_HEALTH,
    STAT_HEARTBEAM_HEALTH,
    STAT_SHADOWCRYSTAL_HEALTH,
    STAT_SHADOW_DRAKE_HEALTH,
    STAT_PHOENIX_HEALTH,
    STAT_WANDERING_ELEMENTAL_HEALTH,

    /** Melee **/
    STAT_ABYSSAL_MELEE_DAMAGE,
    STAT_PIT_LORD_MELEE_DAMAGE,
    STAT_DIABLO_MELEE_DAMAGE,

    /** Additional spell stats **/
    STAT_DIABLO_NAPALM_SHELL_PERIODIC,
    STAT_DIABLO_CONVERSION_BEAM_DAMAGE,
    // those two are used by shadow drake, do not use those IDs
    // 249
    // 250
    // 251
    STAT_DIABLO_RUNIC_LIGHTNING_DAMAGE          = 252
};

constexpr uint32 NETHER_PORTAL_SPAWN_POSITION_SIZE{ 2 };
Position const netherPortalSpawnPosition[NETHER_PORTAL_SPAWN_POSITION_SIZE] =
{
    { 2.635f, -235.231f, -86.79315f, 2.989f }, // left
    { 6.315f, -198.990f, -86.32233f, 3.040f }  // right
};

constexpr uint32 ABYSS_KNIGHT_MOVEMENT_POSITION_SIZE{ 12 };
Position const abyssKnightMovementPosition[ABYSS_KNIGHT_MOVEMENT_POSITION_SIZE] =
{
    // left side move positions
    // first row
    { -25.086f, -237.386f, -89.133f, 3.018f },
    { -24.598f, -233.447f, -89.062f, 3.018f },
    { -23.981f, -228.466f, -89.125f, 3.018f },
    // second row
    { -18.283f, -238.588f, -88.312f, 3.018f },
    { -17.766f, -234.413f, -88.274f, 3.018f },
    { -17.135f, -229.314f, -88.306f, 3.018f },

    // right side move positions
    // first row
    { -20.363f, -195.671f, -88.646f, 3.238f },
    { -21.231f, -190.138f, -88.743f, 3.297f },
    { -21.990f, -185.298f, -88.769f, 3.297f },
    // second row
    { -12.642f, -194.651f, -87.898f, 3.280f },
    { -13.466f, -188.765f, -87.762f, 3.280f },
    { -14.842f, -183.720f, -87.663f, 3.360f }
};

constexpr uint32 ABYSS_KNIGHT_SPAWN_POSITIONS_SIZE{ 3 };
Position const abyssKnightLeftSpawnPos[ABYSS_KNIGHT_SPAWN_POSITIONS_SIZE] =
{
    {  0.724f, -238.747f, -86.92437f, 3.402f },
    { -0.148f, -235.480f, -87.07575f, 3.402f },
    { -1.322f, -231.084f, -86.81894f, 3.402f }
};

Position const abyssKnightRightSpawnPos[ABYSS_KNIGHT_SPAWN_POSITIONS_SIZE] =
{
    { 3.859f, -201.951f, -86.28029f, 3.128f },
    { 2.760f, -197.746f, -86.65012f, 3.128f },
    { 2.832f, -192.615f, -86.78608f, 3.128f }
};

constexpr uint32 FLYING_DOOM_MOVE_POSITION_SIZE{ 2 };
Position const flyingDoomMovePositions[FLYING_DOOM_MOVE_POSITION_SIZE] =
{
    { -10.542f, -245.968f, -83.27728f, 2.379f },
    { -9.295f, -176.949f, -83.61343f, 3.980f }
};

constexpr uint32 PENTAGON_TRIGGER_POSITION_SIZE{ 5 };
Position const pentagonSpawnPositions[PENTAGON_TRIGGER_POSITION_SIZE] =
{
    {  11.383f, -216.512f, -85.07498f, 3.124f },
    { -71.069f, -234.472f, -85.07175f, 0.076f },
    { -30.769f, -178.096f, -85.18916f, 4.808f },
    { -31.841f, -256.225f, -85.55862f, 4.663f },
    { -75.104f, -196.174f, -85.60699f, 1.667f }
};

constexpr uint32 INCREASED_DAMAGE_TRIGGER_POSITION_SIZE{ 3 };
Position const increasedDamageTriggerPositions[INCREASED_DAMAGE_TRIGGER_POSITION_SIZE] =
{
    { -33.114f, -236.784f, -88.78085f },
    { -33.074f, -188.624f, -88.94382f },
    { -71.761f, -213.107f, -83.74525f }
};

static const std::vector<Position> shadowDrakePositions =
{
    { -64.555f, -184.492f, -58.58546f, 5.430f },
    { -78.472f, -198.727f, -57.88005f, 5.654f },
    { -85.088f, -220.835f, -57.88005f, 0.034f },
    { -65.356f, -249.468f, -55.74294f, 1.016f },
    { -38.590f, -256.894f, -55.74294f, 1.412f },
    { -15.498f, -252.477f, -55.15099f, 1.609f },
    { 11.1850f, -254.384f, -55.15099f, 1.856f },
    { 32.4240f, -227.423f, -56.01546f, 2.779f },
    { 34.2680f, -197.826f, -56.06656f, 3.344f },
    { 16.0450f, -179.543f, -56.50787f, 3.816f },
    { -13.424f, -172.831f, -61.66817f, 4.295f },
    { -33.990f, -171.855f, -61.91994f, 4.762f },
    { -51.751f, -171.356f, -61.91994f, 5.017f }
};

constexpr uint32 ASHES_OF_ALAR_POSITION_SIZE{ 2 };
Position const ashesOfAlarSpawnPositions[ASHES_OF_ALAR_POSITION_SIZE] =
{
    { -32.258f, -258.014f, -86.95595f, 1.291f },
    { -31.943f, -171.163f, -86.83335f, 4.758f }
};

static const std::vector<Position> fireelementalsSpawnPositions =
{
    { -73.179f, -231.372f, -83.96888f, 0.160f },
    { -69.563f, -197.305f, -84.27898f, 6.247f },
    { 19.7060f, -189.098f, -85.21370f, 3.239f },
    { 25.9200f, -229.868f, -84.14931f, 3.141f }
};

static const std::vector<Position> meteorSpawnPositions =
{
    { -3.7960f, -239.020f, -87.30614f, 1.292f },
    { -3.2450f, -229.691f, -86.86133f, 1.512f },
    { -2.6790f, -216.861f, -86.39458f, 1.559f },
    { -2.6160f, -207.516f, -86.30782f, 1.571f },
    { -3.1250f, -198.811f, -86.97971f, 1.810f },
    { -7.2210f, -188.621f, -87.55802f, 2.541f },
    { -17.114f, -185.088f, -88.04424f, 4.650f },
    { -14.690f, -195.835f, -88.02670f, 4.673f },
    { -16.267f, -207.947f, -88.48183f, 4.583f },
    { -17.334f, -221.896f, -88.60110f, 4.677f },
    { -19.046f, -234.590f, -88.46857f, 4.591f },
    { -20.401f, -245.602f, -88.36201f, 4.591f },
    { -59.238f, -241.401f, -85.22026f, 2.494f },
    { -71.205f, -228.914f, -83.89588f, 2.011f },
    { -72.345f, -204.387f, -83.71380f, 1.292f },
    { -57.967f, -193.932f, -85.24558f, 6.220f },
    { -55.565f, -210.649f, -85.34544f, 4.673f },
    { -59.705f, -221.177f, -84.90156f, 5.353f },
    { -43.628f, -225.143f, -86.17281f, 6.017f },
    { -45.339f, -204.437f, -86.15733f, 0.146f },
    { 6.08100f, -216.623f, -86.07436f, 5.585f },
    { 6.14300f, -232.239f, -86.36105f, 4.474f },
    { 4.44800f, -243.770f, -86.45892f, 4.552f },
    { 7.88500f, -201.638f, -86.18610f, 1.587f },
    { 6.12300f, -185.470f, -86.33523f, 1.917f },
    { -51.400f, -217.346f, -85.81856f, 4.631f },
    { -20.778f, -175.197f, -87.85326f, 3.931f },
    { -46.091f, -186.474f, -86.44711f, 3.621f },
    { -53.845f, -188.988f, -85.63702f, 3.432f }
};

Position const _dummyFacingPosition{ -54.503f, -212.654f, -85.46500f, 6.268f };
Position const _centerOfFightingArea{ -28.712f, -213.297f, -89.08712f, 6.233f };
Position const _shadowRealmExitPosition{ -43.299423f, -216.492767f, -86.663925f, -0.012966f };
Position const _diabloIntermissionPosition{ -26.659204f, -211.738190f, -89.347158f, 3.182097f };

struct npc_boss_six_diablo_AI : public BossAI
{
    npc_boss_six_diablo_AI(Creature* creature) : BossAI(creature, DATA_DIABLO)
    {
        _myShadowDrakePositions = shadowDrakePositions;
        me->SetFloatValue(UNIT_FIELD_COMBATREACH, 3.5f);
        me->SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 3.5f);
        scheduler.ClearValidator();
        me->SetCanMissSpells(false);
    }

    bool CanEventExecute()
    {
        if (Spell* spell = me->GetCurrentSpell(CURRENT_GENERIC_SPELL))
            if (SpellInfo const* spellInfo = spell->GetSpellInfo())
                if (spellInfo->Id == SPELL_DIABLO_ASCEND)
                    return false;

        return true;
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_BOSS_SIX_ABYSS_KNIGHT || summon->GetEntry() == NPC_BOSS_SIX_OMOR_COPY)
            summons.Summon(summon);
        else
            BossAI::JustSummoned(summon);
    }

    void JustDied(Unit* killer) override
    {
        CheckCreatureRecord(killer, 110000 + 5, RAID_DIFFICULTY_10MAN_NORMAL, "", 1, _fightTimer);
        me->MonsterYell("Damn you mortals... one day I will come back... one day you will feel despair...", LANG_UNIVERSAL, nullptr);
        BossAI::JustDied(killer);
    }

    void KilledUnit(Unit* unit) override
    {
        if (unit->IsPlayer() && !_unitKilledYell)
        {
            _unitKilledYell = true;
            scheduler.Schedule(5s, [this](TaskContext func)
            {
                _unitKilledYell = false;
            });

            std::string _talk = urand(0, 1) ? "Pathetic." : "Another one down!";
            me->MonsterYell(_talk.c_str(), LANG_UNIVERSAL, nullptr);
        }
        BossAI::KilledUnit(unit);
    }

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        BossAI::SummonedCreatureDies(summon, killer);
        if (summon->GetEntry() == NPC_BOSS_SIX_HEART_BEAM_TRIGGER)
        {
            me->SetAggressive();
            me->AttackStop();
            me->SetSelectable(true);
            me->SetVisible(true);
            DoZoneInCombat(me, 250.f);
            CleanupShadowRealm();
            _fightTimer = getMSTime();
            me->MonsterYell("Still alive?", LANG_UNIVERSAL, nullptr);

            for (auto const& entry : { NPC_BOSS_SIX_INCREASED_DAMAGE_TRIGGER, NPC_BOSS_SIX_HEART_BEAM_TRIGGER, NPC_BOSS_SIX_FIERY_COMET_TRIGGER })
                summons.DespawnEntry(entry);
            SchedulePhaseOneAbilities();
            scheduler.Schedule(Seconds(_fireBeamTimer), [this](TaskContext /*func*/)
            {
                SpawnFirebeamTriggers();
            });
        }
        else if (summon->GetEntry() == NPC_BOSS_SIX_SHADOW_DRAKE && ++_drakesDead >= _drakeSpawnCount)
        {
            for (auto const& guid : summons)
            {
                Creature* phoenix = ObjectAccessor::GetCreature(*me, guid);
                if (phoenix && phoenix->GetEntry() == NPC_BOSS_SIX_ASHES_OF_ALAR)
                {
                    Player* player = phoenix->GetCharmerOrOwnerPlayerOrPlayerItself();
                    phoenix->m_spells[3] = SPELL_DIABLO_WRATH_INTERRUPT;

                    //! now, if player exists hence vehicle is occupied
                    //! let's send new list of spells to him
                    //! otherwise dont do anything, it will initialize itself when someone mounts the vehicle
                    if (player)
                        player->VehicleSpellInitialize();
                }
            }

            scheduler.Schedule(Seconds(_phoenixSecondTimer), [this](TaskContext)
            {
                HandlePheonixPhase();
            });
        }
        else if (summon->GetEntry() == NPC_BOSS_SIX_OMOR_COPY)
        {
            if (!me->FindNearestCreature(NPC_BOSS_SIX_OMOR_COPY, 300.f))
            {
                me->AttackStop();
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetSelectable(true);
                me->SetAggressive();
                DoZoneInCombat(me, 200.f);
                SchedulePhaseOneAbilities();
            }
        }
        else if (summon->GetEntry() == NPC_BOSS_SIX_SHADOW_CRYSTAL)
            DrawPentagram();
        else if (summon->GetEntry() == _currentIntermissionBoss)
        {
            summons.DespawnEntry(_currentIntermissionBoss);
            me->SetSelectable(true);
            SchedulePhaseTwoAbilities();
            me->SetAggressive();
            DoZoneInCombat(me, 200.f);
            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                AttackStart(target);
            else
                EnterEvadeMode();
        }
    }

    void OnMeleeAttack(VictimState state, WeaponAttackType attType, Unit* victim, uint32 procAttacker) override
    {
        if (!victim)
            return;

        if (!victim->ToPlayer())
            return;

        //! Proc for melee attacks only, not melee spells and so on and so forth
        if ((procAttacker & (PROC_FLAG_DONE_SPELL_MELEE_DMG_CLASS)) != 0)
            return;

        if (attType == BASE_ATTACK)
        {
            if (!roll_chance_i(_fiveFingersProcChance))
                return;

            DoCast(victim, SPELL_DIABLO_FIVE_FAT_FINGERS, true);
        }
        else if (attType == OFF_ATTACK)
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, _offhandProcDamage);
            me->CastCustomSpell(SPELL_DIABLO_FLAMETONGUE_ATTACK, val, victim, TRIGGERED_FULL_MASK);
        }
    }

    void Reset() override
    {
        BossAI::Reset();
        Trinity::Containers::RandomShuffle(_myShadowDrakePositions);
        me->SetCanDualWield(true);
        me->SetFloatValue(UNIT_FIELD_COMBATREACH, 3.5f);
        me->SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 3.5f);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->SetSelectable(false);
        _pentagramIndex = 0;
        _shadowRealmTargetGUID = 0;
        _napalmPhase = false;
        _intermission = false;
        me->SetVisible(true);
        me->SetAggressive();
        if (Creature* trigger = me->SummonCreature(NPC_BOSS_SIX_METEOR_CASTER_TRIGGER, me->GetHomePosition()))
        {
            trigger->SetSelectable(false);
            trigger->SetPassive();
            _meteorTriggerGUID = trigger->GetGUID();
        }

        _knockbackOrShadowstep = false;
        _napalmShellCount = 1;
        _readjustNapalmShells = false;
        _currentIntermissionBoss = 0;
        _firstPull = false;
        _unitKilledYell = false;
        _fightTimer = 0;
        LoadStats();
    }

    void SpellHitTarget(Unit* who, SpellInfo const* spell) override
    {
        if (who && who->ToPlayer() && spell->Id == SPELL_DIABLO_VICINITY_CHECKER_TRIGGER)
            Unit::Kill(me, who);
    }

    uint32 GetData(uint32 data) const override
    {
        switch (data)
        {
            case STAT_DIABLO_NAPALAM_SHELL_DAMAGE:
                return _napalmShellDamage;
            case STAT_DIABLO_NAPALAM_SHELL_RADIUS_RATIO:
                return _napalamShellRadiusRatio;
            case STAT_DIABLO_ARMAGEDDON_DURATION:
                return _armageddonDuration;
            case STAT_DIABLO_ARMAGEDDON_RADIUS_RATIO:
                return _armageddonRadiusRatio;
            case STAT_DIABLO_ARMAGEDDON_DAMAGE:
                return _armageddonDamage;
            case STAT_DIABLO_WINDS_DAMAGE:
                return _windsDamage;
            case STAT_DIABLO_SPIRIT_BURN_DAMAGE:
                return _spiritBurnDamage;
            case STAT_DIABLO_PLASMA_RAY_DAMAGE:
                return _plasmaRayDamage;
            case STAT_DIABLO_THUNDERSHOCK_DAMAGE:
                return _thundershockDamage;
            default:
                return 0U;
        }

        return 0U;
    }

    float GetFloatData(uint32 data) const override
    {
        if (data == STAT_DIABLO_PLASMA_RAY_WIDTH)
            return _plasmaRayWidth;
        else if (data == STAT_DIABLO_BUFFETING_WINDS_RADIUS)
            return _buffetingWindsRadius;

        return 0.f;
    }

    bool CanAIAttack(Unit const* target) const override
    {
        if (target && target->GetVehicleBase())
            return false;

        return BossAI::CanAIAttack(target);
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues
        ({
           STAT_DIABLO_NAPALAM_SHELL_PERCENTAGE,
           STAT_DIABLO_NAPALAM_SHELL_TIMER,
           STAT_DIABLO_NAPALAM_SHELL_READJUST_HEALTH_PERCENTAGE,
           STAT_DIABLO_NAPALAM_SHELL_COUNT,
           STAT_DIABLO_NAPALAM_SHELL_READJUSTED_COUNT,
           STAT_DIABLO_INTERMISSION_PERCENTAGE,
           STAT_DIABLO_SHADOW_STEP_EXPLOSION_DAMAGE,
           STAT_DIABLO_SHADOW_STEP_EXPLOSION_RADIUS_RATIO,
           STAT_DIABLO_NAPALAM_SHELL_DAMAGE,
           STAT_DIABLO_NAPALAM_SHELL_RADIUS_RATIO,
           STAT_DIABLO_SHADOW_REALM_TIMER,
           STAT_DIABLO_P1_KNOCKBACK_TIMER,
           STAT_DIABLO_P1_KNOCKBACK_REPEAT_TIMER,
           STAT_DIABLO_P1_SHADOWSTEP_FIRST_TIMER,
           STAT_DIABLO_P1_SHADOWSTEP_REPEAT_TIMER,
           STAT_DIABLO_P2_SHADOWSTEP_OR_KNOCKBACK_FIRST_TIMER,
           STAT_DIABLO_P2_SHADOWSTEP_OR_KNOCKBACK_REPEAT_TIMER,
           STAT_DIABLO_FIRE_ELEMENTALS_FIRST_SPAWN_TIMER,
           STAT_DIABLO_FIRE_ELEMENTALS_REPEAT_SPAWN_TIMER,
           STAT_DIABLO_PLASMA_RAY_FIRST_TIMER,
           STAT_DIABLO_PLASMA_RAY_REPEAT_TIMER,
           STAT_DIABLO_PHEONIX_FIRST_TIMER,
           STAT_DIABLO_PHEONIX_REPEATE_TIMER,
           STAT_DIABLO_FIREBEAM_TIMER,
           STAT_DIABLO_PLAYER_SPHERES_MOVE_RATIO,
           STAT_DIABLO_PLASMA_RAY_DAMAGE,
           STAT_DIABLO_PHEONIX_PHASE_CAST_TIMER,
           STAT_DIABLO_PHEONIX_CAST_TIME,
           STAT_DIABLO_ASHES_OF_ALAR_COUNT,
           STAT_DIABLO_SHADOW_DRAKE_COUNT,
           STAT_DIABLO_SHADOW_REALM_FAIL_TIMER,
           STAT_DIABLO_ARMAGEDDON_DURATION,
           STAT_DIABLO_ARMAGEDDON_RADIUS_RATIO,
           STAT_DIABLO_ARMAGEDDON_DAMAGE,
           STAT_DIABLO_WINDS_DAMAGE,
           STAT_DIABLO_SPIRIT_BURN_DAMAGE,
           STAT_DIABLO_PLASMA_RAY_WIDTH,
           STAT_DIABLO_THUNDERSHOCK_DAMAGE,
           STAT_DIABLO_BUFFETING_WINDS_RADIUS,
           STAT_DIABLO_FIVE_FAT_FINGERS_PROC_CHANCE,
           STAT_DIABLO_OFFHAND_PROC_DAMAGE,
           /** health **/
           STAT_ABYSSAL_KNIGHT_HEALTH,
           STAT_PITLORD_HEALTH,
           STAT_DIABLO_HEALTH,
           STAT_HEARTBEAM_HEALTH,
           STAT_SHADOWCRYSTAL_HEALTH,
           STAT_SHADOW_DRAKE_HEALTH,
           STAT_PHOENIX_HEALTH,
           STAT_WANDERING_ELEMENTAL_HEALTH,
           STAT_DIABLO_CONVERSION_BEAM_DAMAGE,
           STAT_DIABLO_RUNIC_LIGHTNING_DAMAGE
        });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
               case STAT_DIABLO_NAPALAM_SHELL_PERCENTAGE:
                   _napalamShellStartPercent = ref.second.StatValue;
                   break;
               case STAT_DIABLO_NAPALAM_SHELL_TIMER:
                   _napalamShellRepeatTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_NAPALAM_SHELL_READJUST_HEALTH_PERCENTAGE:
                   _napalamShellReadjustPercent = ref.second.StatValue;
                   break;
               case STAT_DIABLO_NAPALAM_SHELL_COUNT:
                   _napalamShellNormalCount = ref.second.StatValue;
                   break;
               case STAT_DIABLO_NAPALAM_SHELL_READJUSTED_COUNT:
                   _napalamShellReadjustedCount = ref.second.StatValue;
                   break;
               case STAT_DIABLO_INTERMISSION_PERCENTAGE:
                   _intermissionPercentage = ref.second.StatValue;
                   break;
               case STAT_DIABLO_SHADOW_STEP_EXPLOSION_DAMAGE:
                   _shadowStepExplosionDamage = ref.second.StatValue;
                   break;
               case STAT_DIABLO_SHADOW_STEP_EXPLOSION_RADIUS_RATIO:
                   _shadowStepExplosionRadiusRatio = ref.second.StatValue;
                   break;
               case STAT_DIABLO_NAPALAM_SHELL_DAMAGE:
                   _napalmShellDamage = ref.second.StatValue;
                   break;
               case STAT_DIABLO_NAPALAM_SHELL_RADIUS_RATIO:
                   _napalamShellRadiusRatio = ref.second.StatValue;
                   break;
               case STAT_DIABLO_SHADOW_REALM_TIMER:
                   _shadowRealmFirstTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_P1_KNOCKBACK_TIMER:
                   _knockbackFirstTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_P1_KNOCKBACK_REPEAT_TIMER:
                   _knockbackRepeatTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_P1_SHADOWSTEP_FIRST_TIMER:
                   _shadowStepFirstTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_P1_SHADOWSTEP_REPEAT_TIMER:
                   _shadowStepRepeatTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_P2_SHADOWSTEP_OR_KNOCKBACK_FIRST_TIMER:
                   _knockOrStepFirstTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_P2_SHADOWSTEP_OR_KNOCKBACK_REPEAT_TIMER:
                   _knockOrStepRepeatTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_FIRE_ELEMENTALS_FIRST_SPAWN_TIMER:
                   _fireElementalsFirstTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_FIRE_ELEMENTALS_REPEAT_SPAWN_TIMER:
                   _fireElementalsRepeatTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_PLASMA_RAY_FIRST_TIMER:
                   _plasmaRayFirstTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_PLASMA_RAY_REPEAT_TIMER:
                   _plasmaRayRepeatTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_PHEONIX_FIRST_TIMER:
                   _pheonixFirstTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_PHEONIX_REPEATE_TIMER:
                   _phoenixSecondTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_FIREBEAM_TIMER:
                   _fireBeamTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_PLAYER_SPHERES_MOVE_RATIO:
                   _ballOfFlamesRunRatio = ref.second.StatVariance;
                   break;
               case STAT_DIABLO_PLASMA_RAY_DAMAGE:
                   _plasmaRayDamage = ref.second.StatValue;
                   break;
               case STAT_DIABLO_PHEONIX_PHASE_CAST_TIMER:
                   _phoenixPhaseCastTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_PHEONIX_CAST_TIME:
                   _phoenixPhaseCastLength = ref.second.StatValue;
                   break;
               case STAT_DIABLO_ASHES_OF_ALAR_COUNT:
                   _alarSpawnCount = ref.second.StatValue;
                   break;
               case STAT_DIABLO_SHADOW_DRAKE_COUNT:
                   _drakeSpawnCount = ref.second.StatValue;
                   break;
               case STAT_DIABLO_SHADOW_REALM_FAIL_TIMER:
                   _shadowRealmFailTimer = ref.second.StatValue;
                   break;
               case STAT_DIABLO_ARMAGEDDON_DURATION:
                   _armageddonDuration = ref.second.StatValue;
                   break;
               case STAT_DIABLO_ARMAGEDDON_RADIUS_RATIO:
                   _armageddonRadiusRatio = ref.second.StatValue;
                   break;
               case STAT_DIABLO_ARMAGEDDON_DAMAGE:
                   _armageddonDamage = ref.second.StatValue;
                   break;
               case STAT_DIABLO_WINDS_DAMAGE:
                   _windsDamage = ref.second.StatValue;
                   break;
               case STAT_DIABLO_SPIRIT_BURN_DAMAGE:
                   _spiritBurnDamage = ref.second.StatValue;
                   break;
               case STAT_DIABLO_PLASMA_RAY_WIDTH:
                   _plasmaRayWidth = ref.second.StatVariance;
                   break;
               case STAT_DIABLO_THUNDERSHOCK_DAMAGE:
                   _thundershockDamage = ref.second.StatValue;
                   break;
               case STAT_DIABLO_BUFFETING_WINDS_RADIUS:
                   _buffetingWindsRadius = ref.second.StatVariance;
                   break;
               case STAT_DIABLO_FIVE_FAT_FINGERS_PROC_CHANCE:
                   _fiveFingersProcChance = ref.second.StatValue;
                   break;
               case STAT_DIABLO_OFFHAND_PROC_DAMAGE:
                   _offhandProcDamage = ref.second.StatValue;
                   break;
               case STAT_ABYSSAL_KNIGHT_HEALTH:
                   _abyssalMaxHealth = ref.second.StatValue;
                   break;
               case STAT_PITLORD_HEALTH:
                   _pitlordMaxHealth = ref.second.StatValue;
                   break;
               case STAT_DIABLO_HEALTH:
                   me->SetMaxHealth(ref.second.StatValue);
                   me->SetFullHealth();
                   break;
               case STAT_HEARTBEAM_HEALTH:
                   _heartbeamMaxHealth = ref.second.StatValue;
                   break;
               case STAT_SHADOWCRYSTAL_HEALTH:
                   _shadowcrystalMaxHealth = ref.second.StatValue;
                   break;
               case STAT_SHADOW_DRAKE_HEALTH:
                   _shadowDrakeMaxHealth = ref.second.StatValue;
                   break;
               case STAT_PHOENIX_HEALTH:
                   _phoenixMaxHealth = ref.second.StatValue;
                   break;
               case STAT_WANDERING_ELEMENTAL_HEALTH:
                   _wanderingElementalMaxHealth = ref.second.StatValue;
                   break;
               case STAT_DIABLO_CONVERSION_BEAM_DAMAGE:
                   _conversionBeamDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                   break;
               case STAT_DIABLO_RUNIC_LIGHTNING_DAMAGE:
                   _runicLightningDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                   break;
               default:
                   break;
            }
        }
    }

    uint64 GetGUID(int32 /*data*/) const override
    {
        return _meteorTriggerGUID;
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*Type*/, SpellSchoolMask /*mask*/) override
    {
        if (attacker && attacker->ToCreature() && (attacker->GetEntry() == NPC_BOSS_SIX_ASHES_OF_ALAR || attacker->GetEntry() == NPC_BOSS_SIX_SHADOW_DRAKE))
        {
            damage = 0;
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, attacker->GetMaxHealth() / 2);
            me->CastCustomSpell(SPELL_DIABLO_REFLECT_DAMAGE_FIREBOLT, val, attacker, TRIGGERED_FULL_MASK);
            return;
        }

        if (me->HealthBelowPctDamaged(_napalamShellStartPercent, damage) && !_napalmPhase)
        {
            me->MonsterYell("I am inevitable.", LANG_UNIVERSAL, nullptr);
            _napalmPhase = true;
            _napalmShellCount = _napalamShellNormalCount;
            DoCastSelf(SPELL_DIABLO_SHADOWFORM_1, true);
            DoCastSelf(SPELL_DIABLO_SHADOWFORM_2, true);

            scheduler.Schedule(5s, [this](TaskContext func)
            {
                if (CanEventExecute())
                    HandleNapalmShells();

                func.Repeat(Seconds(_napalamShellRepeatTimer));
            });

            return;
        }

        if (me->HealthBelowPctDamaged(_napalamShellReadjustPercent, damage) && !_readjustNapalmShells)
        {
            me->MonsterYell("BURN TO ASHES!", LANG_UNIVERSAL, nullptr);
            _readjustNapalmShells = true;
            _napalmShellCount = _napalamShellReadjustedCount;
        }

        if (me->HealthBelowPctDamaged(_intermissionPercentage, damage) && !_intermission)
        {
            scheduler.CancelAll();
            _intermission = true;
            _unitKilledYell = false;
            me->SetSelectable(false);
            me->SetPassive();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            me->AttackStop();
            me->GetMotionMaster()->MovePoint(POINT_ID_MIDDLE_INTERMISSION, _diabloIntermissionPosition);

            std::vector<uint32> _bossEntries = { 261000, 261003, 261005, 261008, 261011 };
            _currentIntermissionBoss = Trinity::Containers::SelectRandomContainerElement(_bossEntries);
        }
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        if (pointId == POINT_ID_MIDDLE_INTERMISSION)
        {
            me->SetFacingTo(_diabloIntermissionPosition.GetOrientation());
            scheduler.Schedule(1s, [this](TaskContext func)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
                val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 16000);
                DoCastAOE(SPELL_DIABLO_VICINITY_CHECKER_TRIGGER, true);
                func.Repeat(1s);
            });

            scheduler.Schedule(1s, [this](TaskContext func)
            {
                DoCastSelf(SPELL_DIABLO_RING_OF_FLAME, true);
                func.Repeat(20s);
            });

            if (_currentIntermissionBoss)
                SummonIntermissionCreature();
            else
                EnterEvadeMode();
        }
    }

    void SummonedMovementInform(uint32 type, uint32 pointId, Unit* who) override
    {
        if (type == POINT_MOTION_TYPE && pointId == 100 && who)
            who->SetFacingTo(who->GetAngle(_dummyFacingPosition.GetPositionX(), _dummyFacingPosition.GetPositionY()));
        else if (type == POINT_MOTION_TYPE && pointId == POINT_ID_FLAME_ORB_PLAYER && who && who->ToCreature())
        {
            uint64 targetGUID = who->ToCreature()->AI()->GetGUID();
            if (Unit* target = ObjectAccessor::GetUnit(*me, targetGUID))
            {
                who->ToCreature()->AI()->DoAction(ACTION_FLAME_ORB_ARRIVED);
                HandleTriggerCharge(target, who);
            }
        }
    }

    void HandleShadowstep()
    {
        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U, [this](Unit* object)
        {
            return object->ToPlayer() && !object->HasAura(SPELL_DIABLO_REALM_OF_SHADOWS) && !object->HasAura(SPELL_DIABLO_BUFFETTING_WINDS) && !object->HasAura(SPELL_DIABLO_MC_INSANE)
                && !object->GetVehicleBase();
        }))
        {
            me->AttackStop();
            me->SetPassive();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            DoCastSelf(SPELL_DIABLO_SHADOW_STEP_COSMETIC);
            Position teleportPos;
            target->GetFirstCollisionPosition(teleportPos, 2.f, M_PI);
            me->NearTeleportTo(teleportPos);

            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, _conversionBeamDamage);
            val.AddSpellMod(SPELLVALUE_AURA_DURATION, 3500);
            me->CastCustomSpell(SPELL_DIABLO_CONVERSION_BEAM, val, target, TRIGGERED_FULL_MASK);

            scheduler.Schedule(4s, [this](TaskContext /*func*/)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _shadowStepExplosionDamage);
                val.AddSpellMod(SPELLVALUE_RADIUS_MOD, _shadowStepExplosionRadiusRatio);
                me->CastCustomSpell(SPELL_DIABLO_EXPLOSION, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);

                DoCastSelf(SPELL_DIABLO_BLUE_EXPLOSION, true);

                me->SetAggressive();
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveIdle();
                me->AttackStop();
                DoZoneInCombat(me, 200.f);
                if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                    AttackStart(target);
                else
                    EnterEvadeMode();
            });
        }
    }

    void HandleNapalmShells()
    {
        for (uint32 i = 0; i < _napalmShellCount; ++i)
        {
            Position spawnPosition = Trinity::Containers::SelectRandomContainerElement(_diabloRandomSpawnPositions);
            spawnPosition.m_positionZ += 15.f;

            if (Creature* trigger = me->SummonCreature(NPC_BOSS_SIX_NAPALAM_SHELL_TRIGGER, spawnPosition))
            {
                trigger->SetSelectable(false);
                trigger->SetCanFly(true);
                trigger->SetDisableGravity(true);
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, [this](Unit* object)
                {
                    return object->ToPlayer()
                        && !object->GetVehicleBase()
                        && !object->HasAura(SPELL_DIABLO_MC_INSANE)
                        && !object->HasAura(SPELL_DIABLO_BUFFETTING_WINDS)
                        && !object->HasAura(SPELL_DIABLO_CONVERSION_BEAM);
                });

                if (target)
                {
                    //! damage handled via spellscript, this is triggered spell
                    trigger->CastSpell(target, SPELL_DIABLO_NAPALM_SHELL, true);
                    trigger->AI()->SetGUID(target->GetGUID());
                }

                trigger->DespawnOrUnsummon(30s);
            };
        }
    }

    void AttackStart(Unit* who) override
    {
        if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            me->Attack(who, false);
        else
            BossAI::AttackStart(who);
    }

    void EnterCombat(Unit* who) override
    {
        BossAI::EnterCombat(who);
        SpawnInitialAdds();
    }

    void EnterEvadeMode() override
    {
        auto& players = me->GetMap()->GetPlayers();
        for (auto && source : players)
        {
            if (Player* player = source.GetSource())
            {
                if (!player->IsGameMaster() && player->IsAlive())
                    Unit::Kill(me, player);
            }
        }

        CleanupShadowRealm();
        BossAI::EnterEvadeMode();
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() && (me->IsVisible() && !_intermission))
            return;

        scheduler.Update(diff);
        if (me->IsSelectable())
            DoMeleeAttackIfReady();
    }

    void SpellHit(Unit* caster, SpellInfo const* spellInfo) override
    {
        if (caster && caster->GetEntry() == NPC_BOSS_SIX_ASHES_OF_ALAR && spellInfo->Id == SPELL_DIABLO_WRATH_INTERRUPT)
        {
            if (me->IsCasting())
            {
                me->SetAggressive();
                me->AttackStop();
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveIdle();
                DoZoneInCombat(me, 250.f);
                me->CastStop();
            }
        }
    }

    void SchedulePhaseOneAbilities()
    {
        scheduler.Schedule(Seconds(_shadowRealmFirstTimer), GROUP_DIABLO_PHASE_ONE_CANCELABLE, [this](TaskContext /*func*/)
        {
            BeginShadowRealm();
            //! re-scheduled when previous add dies
        });

        scheduler.Schedule(Seconds(_knockbackFirstTimer), GROUP_DIABLO_PHASE_ONE_CANCELABLE, [this](TaskContext func)
        {
            HandleKnockbackPlayer();
            func.Repeat(Seconds(_knockbackRepeatTimer));
        });

        scheduler.Schedule(Seconds(_shadowStepFirstTimer), GROUP_DIABLO_PHASE_ONE_CANCELABLE, [this](TaskContext func)
        {
            HandleShadowstep();
            func.Repeat(Seconds(_shadowStepRepeatTimer));
        });
    }

    void SchedulePhaseTwoAbilities()
    {
        scheduler.CancelAll();
        _unitKilledYell = false;

        scheduler.Schedule(Seconds(_knockOrStepFirstTimer), GROUP_DIABLO_PHASE_ONE_CANCELABLE, [this](TaskContext func)
        {
            if (CanEventExecute())
            {
                if (_knockbackOrShadowstep)
                    HandleKnockbackPlayer();
                else
                    HandleShadowstep();

                _knockbackOrShadowstep = !_knockbackOrShadowstep;
            }

            func.Repeat(Seconds(_knockOrStepRepeatTimer));
        });

        scheduler.Schedule(Seconds(_fireElementalsFirstTimer), [this](TaskContext func)
        {
            HandleFireElementals();
            func.Repeat(Seconds(_fireElementalsRepeatTimer));
        });

        scheduler.Schedule(Seconds(_plasmaRayFirstTimer), [this](TaskContext func)
        {
            auto _repeatTimer = Seconds(_plasmaRayRepeatTimer);
            if (!CanEventExecute())
                _repeatTimer = 5s;
            else
                HandlePlasmaRay();

            func.Repeat(_repeatTimer);
        });

        scheduler.Schedule(Seconds(_pheonixFirstTimer), [this](TaskContext func)
        {
            HandlePheonixPhase();
        });
    }

    //! Spawn wave of adds when fight begins
    void SpawnInitialAdds()
    {
        scheduler.Schedule(_firstPull ? 12s : 3s, [this](TaskContext func)
        {
            me->MonsterYell("Welcome to hell, where all belongs to me! Minions, erase them!", LANG_UNIVERSAL, me);
            for (auto pos : netherPortalSpawnPosition)
            {
                if (Creature* portal = me->SummonCreature(NPC_BOSS_SIX_PORTAL_TRIGGER, pos))
                {
                    portal->SetSelectable(false);
                    portal->SetPassive();
                    portal->SetImmuneToAll(true);
                    portal->CastSpell(portal, SPELL_DIABLO_NETHER_PORTAL_VISUAL, TRIGGERED_DISALLOW_PROC_EVENTS);
                    portal->DespawnOrUnsummon(25s);
                }
            }

            scheduler.Schedule(2s, [this](TaskContext /*func*/)
            {
                //! spawn first wave
                for (uint32 i = 0; i < 6; ++i)
                {
                    Position spawnPos;
                    Position movePos;
                    if (i < 3)
                    {
                        movePos = abyssKnightMovementPosition[i];
                        spawnPos = abyssKnightLeftSpawnPos[i];
                    }
                    else
                    {
                        spawnPos = abyssKnightRightSpawnPos[i - 3];
                        movePos = abyssKnightMovementPosition[i + 3];
                    }

                    if (Creature* knight = me->SummonCreature(NPC_BOSS_SIX_ABYSS_KNIGHT, spawnPos))
                    {
                        knight->SetMaxHealth(_abyssalMaxHealth);
                        knight->SetFullHealth();
                        knight->SetPassive();
                        knight->SetImmuneToAll(true);
                        knight->SetWalk(true);
                        knight->GetMotionMaster()->MovePoint(100, movePos);
                    }
                }
            });

            //! spawn second wave
            scheduler.Schedule(5s, [this](TaskContext /*func*/)
            {
                for (uint32 i = 6; i < 12; ++i)
                {
                    Position spawnPos;
                    Position movePos;
                    if (i < 9)
                    {
                        spawnPos = abyssKnightLeftSpawnPos[i - 6];
                        movePos = abyssKnightMovementPosition[i - 3];
                    }
                    else
                    {
                        spawnPos = abyssKnightRightSpawnPos[i - 9];
                        movePos = abyssKnightMovementPosition[i];
                    }

                    if (Creature* knight = me->SummonCreature(NPC_BOSS_SIX_ABYSS_KNIGHT, spawnPos))
                    {
                        knight->SetMaxHealth(_abyssalMaxHealth);
                        knight->SetFullHealth();
                        knight->SetPassive();
                        knight->SetImmuneToAll(true);
                        knight->SetWalk(true);
                        knight->GetMotionMaster()->MovePoint(100, movePos);
                    }
                }
            });

            //! spawn third wave
            scheduler.Schedule(9s, [this](TaskContext /*func*/)
            {
                uint32 _moveIndex = 0;
                int32 _demonType = -1;

                for (auto pos : netherPortalSpawnPosition)
                {
                    Position realPosition = pos;
                    realPosition.m_positionZ += 4.5f;
                    if (Creature* flyingDoom = me->SummonCreature(NPC_BOSS_SIX_OMOR_COPY, realPosition))
                    {
                        flyingDoom->AI()->SetData(DATA_SET_DEMON_TYPE, ++_demonType);
                        flyingDoom->SetPassive();
                        flyingDoom->SetImmuneToAll(true);
                        flyingDoom->SetCanFly(true);
                        flyingDoom->SetDisableGravity(true);
                        flyingDoom->GetMotionMaster()->MovePoint(100, flyingDoomMovePositions[_moveIndex]);
                        flyingDoom->SetMaxHealth(_pitlordMaxHealth);
                        flyingDoom->SetFullHealth();
                        ++_moveIndex;
                    }
                }
            });

            scheduler.Schedule(14s, [this](TaskContext /*func*/)
            {
                summons.DespawnEntry(NPC_BOSS_SIX_PORTAL_TRIGGER);

                summons.Broadcast([](Creature* summon)
                {
                    summon->SetAggressive();
                    summon->SetImmuneToAll(false);
                    summon->SetWalk(false);
                    summon->AI()->DoZoneInCombat(summon, 150.f);
                });
            });
        });
    }

    void HandleKnockbackPlayer()
    {
        Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U, [this](Unit* object)
        {
            return object->ToPlayer() && !object->HasAura(SPELL_DIABLO_REALM_OF_SHADOWS) && !object->HasAura(SPELL_DIABLO_MC_INSANE) && !object->GetVehicleBase();
        });

        if (!target)
            return;

        me->MonsterYell("Taste my lightning!", LANG_UNIVERSAL, nullptr);
        CustomSpellValues val;
        val.AddSpellMod(SPELLVALUE_BASE_POINT0, _runicLightningDamage);
        me->CastCustomSpell(SPELL_DIABLO_RUNIC_LIGHTNING, val, target, TRIGGERED_FULL_MASK);
        me->AddAura(SPELL_DIABLO_LIGHTNING_MARKER_VISUAL, target);
    }

    /** Shadow realm handling **/
    void BeginShadowRealm()
    {
        CleanupShadowRealm();
        _pentagramIndex = 0;
        Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U, [this](Unit* object)
        {
            return object->IsPlayer() &&
                !object->HasAura(SPELL_DIABLO_MC_INSANE) &&
                !object->HasAura(SPELL_DIABLO_BUFFETTING_WINDS) &&
                !object->HasAura(SPELL_DIABLO_CONVERSION_BEAM);
        });

        if (!target)
        {
            EnterEvadeMode();
            return;
        }

        me->MonsterYell("Be gone to the realm of the shadows pest!", LANG_UNIVERSAL, nullptr);
        me->AddAura(SPELL_DIABLO_REALM_OF_SHADOWS, target);
        _shadowRealmTargetGUID = target->GetGUID();

        SpawnShadowrealm();
        SpawnPentagramTriggers();

        scheduler.Schedule(Seconds(_shadowRealmFailTimer), GROUP_DIABLO_CANCELABLE, [this](TaskContext func)
        {
            if (!_shadowRealmSucceeded)
            {
                if (Unit* player = ObjectAccessor::GetUnit(*me, _shadowRealmTargetGUID))
                {
                    SchedulePhaseOneAbilities();
                    CleanupShadowRealm();
                    DoCast(player, SPELL_DIABLO_MC_INSANE, true);
                    scheduler.Schedule(Seconds(_fireBeamTimer), [this](TaskContext /*func*/)
                    {
                        SpawnFirebeamTriggers();
                    });
                }
            }
        });
    }

    void CleanupShadowRealm()
    {
        _shadowRealmTargetGUID = 0;
        _shadowRealmSucceeded = false;
        for (uint32 i = 0; i < PENTAGON_TRIGGER_POSITION_SIZE; ++i)
            summons.DespawnEntry(NPC_BOSS_SIX_PENTAGON_TRIGGER_1 + i);
        _pentagramTriggerGUIDs.clear();
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_DIABLO_SELF_STUN);
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_DIABLO_REALM_OF_SHADOWS);
        summons.DespawnEntry(NPC_BOSS_SIX_SHADOW_CRYSTAL);
    }

    void SpawnShadowrealm()
    {
        for (uint32 i = 0; i < PENTAGON_TRIGGER_POSITION_SIZE; ++i)
        {
            Position _spawnPos = pentagonSpawnPositions[i];
            _spawnPos.m_positionZ = me->GetMap()->GetHeight(_spawnPos.GetPositionX(), _spawnPos.GetPositionY(), _spawnPos.GetPositionZ(), true, 100.f);

            if (Creature* shadowCrystal = me->SummonCreature(NPC_BOSS_SIX_SHADOW_CRYSTAL, _spawnPos))
            {
                shadowCrystal->SetMaxHealth(_shadowcrystalMaxHealth);
                shadowCrystal->SetFullHealth();
                shadowCrystal->SetPassive();
                shadowCrystal->SetCanFly(true);
                shadowCrystal->SetPhaseMask(32, true);
            }
        }
    }

    void SpawnPentagramTriggers()
    {
        _pentagramTriggerGUIDs.clear();
        for (uint32 i = 0; i < PENTAGON_TRIGGER_POSITION_SIZE; ++i)
        {
            summons.DespawnEntry(NPC_BOSS_SIX_PENTAGON_TRIGGER_1 + i);
            Position _spawnPos = pentagonSpawnPositions[i];
            _spawnPos.m_positionZ = me->GetMap()->GetHeight(_spawnPos.GetPositionX(), _spawnPos.GetPositionY(), _spawnPos.GetPositionZ(), true, 100.f);
            if (Creature* trigger = me->SummonCreature(NPC_BOSS_SIX_PENTAGON_TRIGGER_1 + i, _spawnPos))
            {
                trigger->SetCanFly(true);
                trigger->SetDisableGravity(true);
                _pentagramTriggerGUIDs.push_back(trigger->GetGUID());
            }
        }
    }

    void DrawPentagram()
    {
        uint64 casterGUID = _pentagramTriggerGUIDs[_pentagramIndex];
        //! if it's last trigger then target trigger at position 0 otherwise get another trigger
        uint64 targetGUID = _pentagramTriggerGUIDs[_pentagramIndex == size_t(_pentagramTriggerGUIDs.size() - 1) ? 0 : _pentagramIndex + 1];
        if (!casterGUID || !targetGUID)
            return;

        Creature* caster = ObjectAccessor::GetCreature(*me, casterGUID);
        Creature* target = ObjectAccessor::GetCreature(*me, targetGUID);
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_DIABLO_RED_BEAM_DROPS, true);

        ++_pentagramIndex;

        if (_pentagramIndex >= size_t(_pentagramTriggerGUIDs.size()))
        {
            _pentagramIndex = 0;
            _shadowRealmSucceeded = true;
            HandleShadowRealmExit(_shadowRealmTargetGUID);
        }
    }

    void HandleShadowRealmExit(uint64 playerGUID)
    {
        Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
        if (!player)
            return;

        me->MonsterYell("ENOUGH!", LANG_UNIVERSAL, nullptr);
        player->RemoveAurasDueToSpell(SPELL_DIABLO_REALM_OF_SHADOWS);
        player->NearTeleportTo(_shadowRealmExitPosition);
        player->AddAura(SPELL_DIABLO_SELF_STUN, player);
        player->AddAura(SPELL_DIABLO_HEART_BEAM_VISUAL, player);
        if (Creature* heartbeam = me->SummonCreature(NPC_BOSS_SIX_HEART_BEAM_TRIGGER, _shadowRealmExitPosition))
        {
            heartbeam->SetMaxHealth(_heartbeamMaxHealth);
            heartbeam->SetFullHealth();
            heartbeam->SetPassive();
            player->CastSpell(heartbeam, SPELL_DIABLO_RAGING_SPIRIT_VISUAL, true);
            heartbeam->CastSpell(heartbeam, SPELL_DIABLO_HEART_BEAM_VISUAL, true);
            for (auto && pos : increasedDamageTriggerPositions)
            {
                Creature* trigger = me->SummonCreature(NPC_BOSS_SIX_INCREASED_DAMAGE_TRIGGER, pos);
                if (trigger)
                    trigger->AI()->SetGUID(heartbeam->GetGUID());
            }
        }

        me->AttackStop();
        me->GetMotionMaster()->Clear();
        me->GetMotionMaster()->MoveIdle();
        me->SetPassive();
        me->SetVisible(false);
        me->SetSelectable(false);
        scheduler.CancelGroup(GROUP_DIABLO_PHASE_ONE_CANCELABLE);
    }
    /** END OF SHADOW REALM HANDLING **/

    void HandleTriggerCharge(Unit* summoner, Unit* caster)
    {
        if (!summoner || !caster)
            return;

        Position pos = caster->GetPosition();
        pos.m_positionZ = caster->GetMap()->GetHeight(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), true, 150.f);
        pos.SetOrientation(summoner->GetAngle(me->GetPositionX(), me->GetPositionY()));
        Creature* trigger = caster->SummonCreature(NPC_BOSS_SIX_BEAM_TRIGGER, pos);
        if (!trigger)
            return;

        JustSummoned(trigger);
        trigger->SetCanFly(true);
        trigger->SetDisableGravity(true);
        trigger->SetPassive();
        trigger->SetImmuneToPC(true);

        CustomSpellValues val;
        val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 300.f);

        Position initialPosition = trigger->GetPosition();
        Position chargePosition = summoner->GetPosition();
        initialPosition.SetOrientation(trigger->GetAngle(summoner->GetPositionX(), summoner->GetPositionY()));

        Movement::MoveSplineInit init(trigger);
        chargePosition.m_positionZ += 1.5f;
        init.MoveTo({ chargePosition.GetPositionX(), chargePosition.GetPositionY(), chargePosition.GetPositionZ() }, false, false);
        init.SetVelocity(42.f);
        std::chrono::milliseconds _timer(init.Launch());
        val.AddSpellMod(SPELLVALUE_AURA_DURATION, _timer.count());
        caster->CastCustomSpell(SPELL_DIABLO_EYE_BEAM, val, trigger, TRIGGERED_FULL_MASK);

        float const distance = trigger->GetDistance2d(summoner);

        for (float f = 0.f; f <= 1.2f; f += 0.1f)
        {
            float x, y, z;
            x = initialPosition.GetPositionX() + ((distance * f) * cos(initialPosition.GetOrientation()));
            y = initialPosition.GetPositionY() + ((distance * f) * sin(initialPosition.GetOrientation()));
            z = trigger->GetMap()->GetHeight(x, y, trigger->GetPositionZ() + 15.f, true, 150.f);

            if (Creature* exploTrigger = me->SummonCreature(NPC_BOSS_SIX_BEAM_TRIGGER_EXPLO_TRIGGER, { x, y, z, trigger->GetOrientation() }))
                exploTrigger->AI()->SetData(DATA_EXPLOSION_TIMER, static_cast<uint32>(_timer.count() * f));
        }
    }

    void SpawnFirebeamTriggers()
    {
        Position _bossFireOrbPos = me->GetPosition();
        _bossFireOrbPos.m_positionZ += 25.f;

        if (Creature* selfOrb = me->SummonCreature(NPC_BOSS_SIX_BALL_OF_FLAMES_BOSS, _bossFireOrbPos, TEMPSUMMON_TIMED_DESPAWN, 60000))
        {
            selfOrb->SetSelectable(false);
            selfOrb->SetCanFly(true);
            selfOrb->SetDisableGravity(true);
            selfOrb->SetPassive();
            selfOrb->CastSpell(selfOrb, SPELL_DIABLO_BALL_OF_FLAMES_VISUAL, true);
        }

        _bossFireOrbPos.m_positionZ += 4.5f;

        Unit* currentTarget = me->GetVictim();
        if (!currentTarget)
            return;

        auto& players = me->GetMap()->GetPlayers();
        for (auto && source : players)
        {
            Player* player = source.GetSource();
            if (!player)
                continue;

            if (player->isDead() || player->IsGameMaster())
                continue;

            // exclude tanks
            if (currentTarget->GetGUID() == player->GetGUID())
                continue;

            if (Creature* orb = me->SummonCreature(NPC_BOSS_SIX_BALL_OF_FLAMES_PLAYER, player->GetPosition()))
            {
                orb->AI()->SetGUID(player->GetGUID());
                JustSummoned(orb);

                orb->SetSelectable(false);
                orb->SetPassive();
                orb->CastSpell(orb, SPELL_DIABLO_BALL_OF_FLAMES_VISUAL, true);
                orb->SetSpeedRate(MOVE_RUN, _ballOfFlamesRunRatio);
                orb->SetSpeedRate(MOVE_WALK, _ballOfFlamesRunRatio);
                orb->SetCanFly(true);
                orb->SetDisableGravity(true);
                orb->GetMotionMaster()->MovePoint(POINT_ID_FLAME_ORB_PLAYER, _bossFireOrbPos);
            }
        }
    }

    void HandleFireElementals()
    {
        std::vector<Position> elementalPositions = fireelementalsSpawnPositions;
        Trinity::Containers::RandomResize(elementalPositions, size_t(2));

        for (auto const& pos : elementalPositions)
        {
            if (Creature* portal = me->SummonCreature(NPC_BOSS_SIX_PORTAL_TRIGGER_VISUAL, pos))
            {
                portal->SetImmuneToAll(true);
                portal->SetPassive();
                portal->SetSelectable(false);
                portal->CastSpell(portal, SPELL_DIABLO_PORTAL_STATE_VISUAL, true);
                portal->DespawnOrUnsummon(5s);
            }
        }

        for (auto const pos : elementalPositions)
        {
            if (Creature* elemental = me->SummonCreature(NPC_BOSS_SIX_UNSTABLE_FIRE_ELEMENTAL, pos))
            {
                elemental->SetMaxHealth(_wanderingElementalMaxHealth);
                elemental->SetFullHealth();
            }
        }
    }

    void HandlePlasmaRay()
    {
        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U, [this](Unit* object)
        {
            return object->ToPlayer()
                && !object->GetVehicleBase()
                && !object->HasAura(SPELL_DIABLO_BUFFETTING_WINDS)
                && !object->HasAura(SPELL_DIABLO_MC_INSANE)
                && !object->HasAura(SPELL_DIABLO_LIGHTNING_MARKER_VISUAL);
        }))
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, _plasmaRayDamage);
            val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 300);
            me->CastCustomSpell(SPELL_DIABLO_PLASMA_RAY, val, target, TRIGGERED_FULL_MASK);
        }
    }

    void HandlePheonixPhase()
    {
        me->MonsterYell("Death from above!", LANG_UNIVERSAL, nullptr);
        _drakesDead = 0;
        for (auto const& entry : { NPC_BOSS_SIX_ASHES_OF_ALAR, NPC_BOSS_SIX_SHADOW_DRAKE })
            summons.DespawnEntry(entry);

        scheduler.Schedule(Seconds(_phoenixPhaseCastTimer), [this](TaskContext)
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_MODIFY_CAST_TIME, _phoenixPhaseCastLength);
            me->CastCustomSpell(SPELL_DIABLO_ASCEND, val, (Unit*)nullptr);
        });

        for (uint32 i = 0; i < _alarSpawnCount; ++i)
        {
            if (Creature* phoenix = me->GetMap()->SummonCreature(NPC_BOSS_SIX_ASHES_OF_ALAR, ashesOfAlarSpawnPositions[i]))
            {
                phoenix->SetMaxHealth(_phoenixMaxHealth);
                phoenix->SetFullHealth();
                phoenix->setPowerType(POWER_ENERGY);
                phoenix->SetMaxPower(POWER_ENERGY, 200);
                phoenix->SetPower(POWER_ENERGY, phoenix->GetMaxPower(POWER_ENERGY));
                JustSummoned(phoenix);
                phoenix->SetCanFly(true);
                phoenix->SetDisableGravity(true);
                phoenix->SetCanMissSpells(false);
            }
        }

        for (uint32 i = 0; i < _drakeSpawnCount; ++i)
        {
            if (Creature* drake = me->SummonCreature(NPC_BOSS_SIX_SHADOW_DRAKE, _myShadowDrakePositions[i], TEMPSUMMON_CORPSE_DESPAWN))
            {
                drake->SetMaxHealth(_shadowDrakeMaxHealth);
                drake->SetFullHealth();
                drake->SetCanFly(true);
                drake->SetDisableGravity(true);
                drake->SetCanMissSpells(false);
            }
        }
    }

    void DoAction(int32 action) override
    {
        if (action == 1)
        {
            _firstPull = true;
            me->MonsterYell("I am complete!", LANG_UNIVERSAL, me);

            if (Player * victim = me->SelectNearestPlayer(200.f))
                me->Attack(victim, false);

            scheduler.Schedule(3s, [&](TaskContext func)
            {
                switch (func.GetRepeatCounter())
                {
                    case 0:
                    {
                        auto &players = instance->instance->GetPlayers();
                        for (auto i = players.begin(); i != players.end(); ++i)
                        {
                            Player* player = i->GetSource();
                            if (!player || player->IsGameMaster())
                                continue;

                            player->Yell("Fuuuuuuuuuuuuckkkkk!!!", LANG_UNIVERSAL);
                        }

                        func.Repeat(4s);
                        break;
                    }
                    case 1:
                    {
                        me->MonsterYell("I'm the end of your world.", LANG_UNIVERSAL, me);
                        break;
                    }
                    default:
                        break;
                }
            });
        }
    }

    void SummonIntermissionCreature()
    {
        if (!_currentIntermissionBoss)
            return;

        // Don't summon portal on Yogg-Saron spawn
        if (_currentIntermissionBoss != 261011)
        {
            if (Creature * trigger = me->SummonCreature(NPC_WORLD_TRIGGER, GetIntermissionSpawnPosition(), TEMPSUMMON_TIMED_DESPAWN, 10000))
            {
                trigger->SetCanFly(true);
                trigger->SetDisableGravity(true);

                float scale = 10.f;
                if (_currentIntermissionBoss == 261005 || _currentIntermissionBoss == 261008)
                    scale = 3.f;

                trigger->SetObjectScale(scale);
                trigger->CastSpell(me, _currentIntermissionBoss != 261005 ? SPELL_DIABLO_NETHER_PORTAL_VISUAL : SPELL_DIABLO_IMPALE_VISUAL);
            }
        }
        scheduler.Schedule(3s, [&](TaskContext /*func*/)
        {
            Position pos = GetIntermissionSpawnPosition();
            if (_currentIntermissionBoss == 261003)
                pos.RelocateOffset({ -20.f, 0.f, 20.f });
            me->SummonCreature(_currentIntermissionBoss, pos, TEMPSUMMON_CORPSE_DESPAWN);
        });
    }

    Position GetIntermissionSpawnPosition()
    {
        switch (_currentIntermissionBoss)
        {
            case 261000: // Kel'thuzad
                return { 24.69f, -209.50f, -84.88f, 3.25f };
            case 261011: // Yogg-Saron
                return me->GetPosition();
            case 261005: // Anub'arak
            case 261008: // Lich King
                return { -59.64f, -214.89f, -84.87f, 0.04f };
            case 261003: // Onyxia
                return { 30.18f, -214.84f, -58.39f, 3.18f };
        }
        return me->GetPosition();
    }

private:
    bool _shadowRealmSucceeded;
    uint32 _pentagramIndex;
    std::vector<uint64> _pentagramTriggerGUIDs;
    uint64 _shadowRealmTargetGUID;
    bool _napalmPhase;
    bool _intermission;
    std::vector<Position> _myShadowDrakePositions;
    uint32 _drakesDead;
    uint64 _meteorTriggerGUID;
    bool _knockbackOrShadowstep;
    uint32 _napalmShellCount;
    bool _readjustNapalmShells;
    uint32 _currentIntermissionBoss;
    bool _firstPull;
    bool _unitKilledYell;
    uint32 _fightTimer;

    // Napalam Shell related
    uint32 _napalamShellStartPercent; // 150
    uint32 _napalamShellRepeatTimer;
    uint32 _napalamShellReadjustPercent;
    uint32 _napalamShellNormalCount;
    uint32 _napalamShellReadjustedCount;
    // Intermission related
    uint32 _intermissionPercentage;
    // shadowstep related
    uint32 _shadowStepExplosionDamage;
    uint32 _shadowStepExplosionRadiusRatio;
    //! trzeba wyrzucic do spell skryptu
    uint32 _napalmShellDamage;
    uint32 _napalamShellRadiusRatio;
    // phase one timers
    uint32 _shadowRealmFirstTimer;
    uint32 _knockbackFirstTimer;
    uint32 _knockbackRepeatTimer;
    uint32 _shadowStepFirstTimer;
    uint32 _shadowStepRepeatTimer;
    // phase two timers
    uint32 _knockOrStepFirstTimer;
    uint32 _knockOrStepRepeatTimer;
    uint32 _fireElementalsFirstTimer;
    uint32 _fireElementalsRepeatTimer;
    uint32 _plasmaRayFirstTimer;
    uint32 _plasmaRayRepeatTimer;
    uint32 _pheonixFirstTimer;
    uint32 _phoenixSecondTimer;
    uint32 _fireBeamTimer;
    uint32 _shadowRealmFailTimer;
    float _ballOfFlamesRunRatio;
    uint32 _plasmaRayDamage;
    uint32 _phoenixPhaseCastTimer; // important, has to be in seconds
    uint32 _phoenixPhaseCastLength; // in milliseconds
    uint32 _alarSpawnCount;
    uint32 _drakeSpawnCount;
    uint32 _armageddonDuration;
    uint32 _armageddonRadiusRatio;
    uint32 _armageddonDamage;
    uint32 _windsDamage;
    uint32 _spiritBurnDamage;
    float _plasmaRayWidth;
    uint32 _thundershockDamage;
    float _buffetingWindsRadius;
    uint32 _fiveFingersProcChance;
    uint32 _offhandProcDamage;

    /** Health **/
    uint32 _abyssalMaxHealth;
    uint32 _pitlordMaxHealth;
    uint32 _heartbeamMaxHealth;
    uint32 _shadowcrystalMaxHealth;
    uint32 _shadowDrakeMaxHealth;
    uint32 _phoenixMaxHealth;
    uint32 _wanderingElementalMaxHealth;
    uint32 _conversionBeamDamage;
    uint32 _runicLightningDamage;
};

enum DemonSpells
{
    SPELL_DEMON_REFLECT_SPELLS              = 35158,
    SPELL_DEMON_SHADOW_NOVA                 = 51073,
    SPELL_DEMON_NETHER_POWER                = 67108
};

enum DemonStatId
{
    STAT_DEMON_SHADOW_NOVA_TIMER            = 200,
    STAT_DEMON_SHADOW_NOVA_RADIUS_RATIO,
    STAT_DEMON_SHADOW_NOVA_DAMAGE,
    STAT_DEMON_SHADOW_NOVA_REPEAT_TIMER,
    STAT_DEMON_DEMON_SWITCH_TIMER,
    STAT_DEMON_NEARBY_DEMON_RADIUS,
    STAT_DEMON_NEARBY_DEMON_CHECK_TIMER
};

struct npc_boss_six_flying_demon_AI : public ScriptedAI
{
    npc_boss_six_flying_demon_AI(Creature* creature) : ScriptedAI(creature)
    {
        _reflectingDemonType = false;
        LoadStats();
    }

    void Reset() override
    {
        _scheduler.CancelAll();
        ScriptedAI::Reset();
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ STAT_DEMON_SHADOW_NOVA_TIMER, STAT_DEMON_SHADOW_NOVA_RADIUS_RATIO,
            STAT_DEMON_SHADOW_NOVA_DAMAGE, STAT_DEMON_SHADOW_NOVA_REPEAT_TIMER, STAT_DEMON_DEMON_SWITCH_TIMER, STAT_DEMON_NEARBY_DEMON_RADIUS, STAT_DEMON_NEARBY_DEMON_CHECK_TIMER });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case STAT_DEMON_SHADOW_NOVA_TIMER:
                    _shadowNovaTimer = ref.second.StatValue;
                    break;
                case STAT_DEMON_SHADOW_NOVA_RADIUS_RATIO:
                    _shadowNovaRadiusRatio = ref.second.StatValue;
                    break;
                case STAT_DEMON_SHADOW_NOVA_DAMAGE:
                    _shadowNovaDamage = ref.second.StatValue;
                    break;
                case STAT_DEMON_SHADOW_NOVA_REPEAT_TIMER:
                    _shadowNovaRepeatTimer = ref.second.StatValue;
                    break;
                case STAT_DEMON_DEMON_SWITCH_TIMER:
                    _demonSwitchTimer = ref.second.StatValue;
                    break;
                case STAT_DEMON_NEARBY_DEMON_RADIUS:
                    _demonNearbyRadius = ref.second.StatVariance;
                    break;
                case STAT_DEMON_NEARBY_DEMON_CHECK_TIMER:
                    _demonNearbyCheckTimer = ref.second.StatValue;
                    break;
                default:
                    break;
            }
        }
    }

    void SetData(uint32 type, uint32 value)
    {
        if (type == DATA_SET_DEMON_TYPE)
        {
            if (!value)
                _reflectingDemonType = true;
        }
        else if (type == DATA_SWITCH_DEMON_TYPE)
        {
            me->RemoveAurasDueToSpell(SPELL_DEMON_REFLECT_SPELLS);
            _reflectingDemonType = !_reflectingDemonType;
        }

        ScheduleCombatEvents();
    }

    void ScheduleCombatEvents()
    {
        _scheduler.CancelGroup(GROUP_DEMON_SWITCHABLE);
        if (_reflectingDemonType)
        {
            DoCastSelf(SPELL_DEMON_REFLECT_SPELLS, true);
            if (Aura* aura = me->GetAura(SPELL_DEMON_REFLECT_SPELLS))
            {
                aura->SetCharges(0);
                aura->SetMaxDuration(-1);
                aura->RefreshDuration();
            }
        }
        else
        {
            _scheduler.Schedule(Seconds(_shadowNovaTimer), GROUP_DEMON_SWITCHABLE, [this](TaskContext func)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_RADIUS_MOD, _shadowNovaRadiusRatio);
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _shadowNovaDamage);
                me->CastCustomSpell(SPELL_DEMON_SHADOW_NOVA, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                func.Repeat(Seconds(_shadowNovaRepeatTimer));
            });
        }
    }

    void EnterCombat(Unit* who) override
    {
        ScriptedAI::EnterCombat(who);
        _scheduler.Schedule(Seconds(_demonSwitchTimer), [this](TaskContext func)
        {
            SetData(DATA_SWITCH_DEMON_TYPE, DATA_SWITCH_DEMON_TYPE);
            func.Repeat(Seconds(_demonSwitchTimer));
        });

        //! Nerfed those, they no longer stack that aura when they're nearby
        //_scheduler.Schedule(Seconds(_demonNearbyCheckTimer), [this](TaskContext func)
        //{
        //    std::list<Creature*> _demons;
        //    me->GetCreatureListWithEntryInGrid(_demons, me->GetEntry(), _demonNearbyRadius);
        //    _demons.remove_if([this](Creature* ref)
        //    {
        //        return ref->GetGUID() == me->GetGUID();
        //    });

        //    if (!_demons.empty())
        //    {
        //        DoCastSelf(SPELL_DEMON_NETHER_POWER, true);
        //        if (Aura* aura = me->GetAura(SPELL_DEMON_NETHER_POWER))
        //        {
        //            aura->SetMaxDuration(-1);
        //            aura->RefreshDuration();
        //        }
        //    }

        //    func.Repeat(Seconds(_demonNearbyCheckTimer));
        //});
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
        DoMeleeAttackIfReady();
    }
private:
    TaskScheduler _scheduler;
    bool _reflectingDemonType;

    uint32 _shadowNovaTimer;
    float _shadowNovaRadiusRatio;
    float _shadowNovaDamage;
    uint32 _shadowNovaRepeatTimer;
    uint32 _demonSwitchTimer;
    float _demonNearbyRadius;
    uint32 _demonNearbyCheckTimer;
};

struct npc_boss_six_beam_trigger : public ScriptedAI
{
    npc_boss_six_beam_trigger(Creature* creature) : ScriptedAI(creature) { }

    void MoveInLineOfSight(Unit* who) override { }
    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
};

enum BeamStatIDs
{
    STAT_BEAM_FIREBEAM_EXPLOSION_DAMAGE         = 207,
    STAT_BEAM_FIREBEAM_EXPLOSION_RADIUS_RATIO,
    STAT_BEAM_FIREBEAM_FLAME_PATCH_PCT_DMG,
    STAT_BEAM_FIREBEAM_FLAME_PATCH_RADIUS_RATIO,
    STAT_BEAM_FIREBEAM_DESPAWN_TIMER
};

struct npc_boss_six_beam_trigger_explosion : public ScriptedAI
{
    npc_boss_six_beam_trigger_explosion(Creature* creature) : ScriptedAI(creature)
    {
        _scheduler.CancelAll();
        me->DespawnOrUnsummon(25s);
        LoadStats();
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues
        ({ STAT_BEAM_FIREBEAM_EXPLOSION_DAMAGE, STAT_BEAM_FIREBEAM_EXPLOSION_RADIUS_RATIO, STAT_BEAM_FIREBEAM_FLAME_PATCH_PCT_DMG,
            STAT_BEAM_FIREBEAM_FLAME_PATCH_RADIUS_RATIO, STAT_BEAM_FIREBEAM_DESPAWN_TIMER });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case STAT_BEAM_FIREBEAM_EXPLOSION_DAMAGE:
                    _firebeamExplosionDamage = ref.second.StatValue;
                    break;
                case STAT_BEAM_FIREBEAM_EXPLOSION_RADIUS_RATIO:
                    _firebeamExplosionRadiusRatio = ref.second.StatValue;
                    break;
                case STAT_BEAM_FIREBEAM_FLAME_PATCH_PCT_DMG:
                    _firebeamFlamePatchPercentDamage = ref.second.StatValue;
                    break;
                case STAT_BEAM_FIREBEAM_FLAME_PATCH_RADIUS_RATIO:
                    _firebeamFlamePatchRadiusRatio = ref.second.StatValue;
                    break;
                case STAT_BEAM_FIREBEAM_DESPAWN_TIMER:
                    _firebeamDespawnTimer = ref.second.StatValue;
                    break;
            }
        }
    }

    void MoveInLineOfSight(Unit* who) override { }
    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type != DATA_EXPLOSION_TIMER)
            return;

        _scheduler.Schedule(std::chrono::milliseconds(value), [this](TaskContext func)
        {
            if (InstanceScript* instance = me->GetInstanceScript())
            {
                Creature* diablo = instance->GetCreature(DATA_DIABLO);
                if (diablo)
                {
                    CustomSpellValues val;
                    val.AddSpellMod(SPELLVALUE_BASE_POINT0, _firebeamExplosionDamage);
                    val.AddSpellMod(SPELLVALUE_RADIUS_MOD, _firebeamExplosionRadiusRatio);
                    val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
                    me->CastCustomSpell(SPELL_DIABLO_TRIGGER_EXPLOSION, val, (Unit*) nullptr, TRIGGERED_FULL_MASK, NullItemRef, (const AuraEffect*)nullptr, diablo->GetGUID());

                    val.AddSpellMod(SPELLVALUE_BASE_POINT0, _firebeamFlamePatchPercentDamage);
                    val.AddSpellMod(SPELLVALUE_RADIUS_MOD, _firebeamFlamePatchRadiusRatio);
                    val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
                    me->CastCustomSpell(SPELL_DIABLO_TRIGGER_FLAME_PATCH, val, (Unit*) nullptr, TRIGGERED_FULL_MASK, NullItemRef, (const AuraEffect*)nullptr, diablo->GetGUID());

                    me->DespawnOrUnsummon(Seconds(_firebeamDespawnTimer));
                }
            }
        });
    }

private:
    TaskScheduler _scheduler;

    uint32 _firebeamExplosionDamage;
    uint32 _firebeamExplosionRadiusRatio;
    uint32 _firebeamFlamePatchPercentDamage;
    uint32 _firebeamFlamePatchRadiusRatio;
    uint32 _firebeamDespawnTimer;
};

enum PlayerCloneStatId
{
    STAT_PLAYERCLONE_COMET_COUNT            = 212,
    STAT_PLAYERCLONE_COMET_TIMER,
    STAT_PLAYERCLONE_COMET_REPEAT_TIMER,
};

struct npc_boss_diablo_playerclone : public ScriptedAI
{
    npc_boss_diablo_playerclone(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
        _myMeteorSpawnPositions = meteorSpawnPositions;
        LoadStats();
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues
        ({ STAT_PLAYERCLONE_COMET_COUNT, STAT_PLAYERCLONE_COMET_TIMER, STAT_PLAYERCLONE_COMET_REPEAT_TIMER });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case STAT_PLAYERCLONE_COMET_COUNT:
                    _playerCloneCometCount = ref.second.StatValue;
                    break;
                case STAT_PLAYERCLONE_COMET_TIMER:
                    _playerCloneCometTimer = ref.second.StatValue;
                    break;
                case STAT_PLAYERCLONE_COMET_REPEAT_TIMER:
                    _playerCloneCometRepeatTimer = ref.second.StatValue;
                    break;
                default:
                    break;

            }
        }
    }

    void Reset() override { }
    void AttackStart(Unit* /*attacker*/) override { }
    void EnterCombat(Unit* /*who*/) override { }

    void IsSummonedBy(Unit* /*summoner*/) override
    {
        _scheduler.CancelAll();
        DoZoneInCombat(me, 200.f);
        _scheduler.Schedule(Seconds(_playerCloneCometTimer), [this](TaskContext func)
        {
            for (uint32 i = 0; i < _playerCloneCometCount; ++i)
            {
                Player* player = me->SelectNearestPlayer(150.f);
                Creature* diablo = _instance->GetCreature(DATA_DIABLO);

                if (player && diablo)
                {
                    Trinity::Containers::RandomShuffle(_myMeteorSpawnPositions);
                    Position pos = _myMeteorSpawnPositions.front();

                    if (Creature* trigger = player->SummonCreature(NPC_BOSS_SIX_FIERY_COMET_TRIGGER, pos))
                    {
                        diablo->AI()->JustSummoned(trigger);
                        trigger->SetCanFly(true);
                        trigger->SetDisableGravity(true);
                        trigger->CastSpell(trigger, SPELL_DIABLO_SMOKEY_MARKER, true);
                    }
                }
            }

            func.Repeat(Seconds(_playerCloneCometRepeatTimer));
        });
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

private:
    InstanceScript* _instance;
    TaskScheduler _scheduler;
    std::vector<Position> _myMeteorSpawnPositions;

    uint32 _playerCloneCometTimer;
    uint32 _playerCloneCometCount;
    uint32 _playerCloneCometRepeatTimer;
};

class spell_boss_diablo_nether_portal_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_boss_diablo_nether_portal_AuraScript);

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        if (GetTarget() && GetTarget()->GetMapId() == DIABLO_MAP_ID)
            PreventDefaultAction();
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_boss_diablo_nether_portal_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

class spell_boss_diablo_flametongue_weapon : public AuraScript
{
    PrepareAuraScript(spell_boss_diablo_flametongue_weapon);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return !(eventInfo.GetActor() && eventInfo.GetActionTarget()->GetMapId() == DIABLO_MAP_ID);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_boss_diablo_flametongue_weapon::CheckProc);
    }
};

enum CometStatId
{
    STAT_COMET_METEOR_HIT_TIMER         = 215,
    STAT_COMET_METEOR_HIT_DAMAGE,
    STAT_COMET_METEOR_RADIUS_RATIO,
    STAT_COMET_HIT_PLAYERS_ONLY,
    STAT_COMET_SPLIT_DAMAGE
};

struct npc_boss_diablo_comet_trigger : public ScriptedAI
{
    npc_boss_diablo_comet_trigger(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
        _didSpawnInfernal = false;
        me->SetCanMissSpells(false);
        LoadStats();
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues
        ({ STAT_COMET_METEOR_HIT_TIMER, STAT_COMET_METEOR_HIT_DAMAGE, STAT_COMET_METEOR_RADIUS_RATIO,
            STAT_COMET_HIT_PLAYERS_ONLY, STAT_COMET_SPLIT_DAMAGE });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case STAT_COMET_METEOR_HIT_TIMER:
                    _meteorHitTimer = ref.second.StatValue;
                    break;
                case STAT_COMET_METEOR_HIT_DAMAGE:
                    _meteorHitDamage = ref.second.StatValue;
                    break;
                case STAT_COMET_METEOR_RADIUS_RATIO:
                    _meteorRadiusRatio = ref.second.StatValue;
                    break;
                case STAT_COMET_HIT_PLAYERS_ONLY:
                    _meteorTargetPlayersOnly = ref.second.StatValue;
                    break;
                case STAT_COMET_SPLIT_DAMAGE:
                    _meteorShareDamage = ref.second.StatValue;
                    break;
                default:
                    break;
            }
        }
    }

    void HandleMeteor()
    {
        Creature* diablo = _instance->GetCreature(DATA_DIABLO);
        if (diablo)
        {
            Creature* _caster = ObjectAccessor::GetCreature(*me, diablo->AI()->GetGUID());
            if (_caster)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _meteorHitDamage);
                val.AddSpellMod(SPELLVALUE_RADIUS_MOD, _meteorRadiusRatio);
                val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, _meteorTargetPlayersOnly);
                val.AddSpellMod(SPELLVALUE_ENABLE_SHARE_DAMAGE, _meteorShareDamage);
                _caster->CastCustomSpell(SPELL_DIABLO_METEOR, val, me, TRIGGERED_FULL_MASK, NullItemRef, (const AuraEffect*)nullptr, me->GetGUID());
            }
        }
    }

    void Reset() override
    {
        DoCastSelf(SPELL_DIABLO_COSMETIC_WHITE_SMOKE);
        me->SetSelectable(false);
        _scheduler.CancelAll();

        _scheduler.Schedule(Seconds(_meteorHitTimer), [this](TaskContext /*func*/)
        {
            HandleMeteor();
        });

        me->DespawnOrUnsummon(20s);
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == 52 && value)
            _didSpawnInfernal = true;
        //! if we didnt hit anything, spawn infernal
        else if (type == 51)/* && !_didSpawnInfernal)*/
        {
            _scheduler.Schedule(4s, [this](TaskContext /*func*/)
            {
                if (!_didSpawnInfernal)
                {
                    if (_instance)
                    {
                        Creature* diablo = _instance->GetCreature(DATA_DIABLO);
                        if (diablo)
                            diablo->SummonCreature(NPC_BOSS_SIX_DIABOLIC_INFERNAL, me->GetPosition());
                    }

                    me->RemoveAllAuras();
                }
                me->DespawnOrUnsummon();
            });


        }
    }

    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }
private:
    InstanceScript* _instance;
    TaskScheduler _scheduler;
    bool _didSpawnInfernal;

    uint32 _meteorHitTimer;
    uint32 _meteorHitDamage;
    uint32 _meteorRadiusRatio;
    uint32 _meteorTargetPlayersOnly;
    uint32 _meteorShareDamage;
};

class spell_boss_six_diablo_meteor : public SpellScript
{
    PrepareSpellScript(spell_boss_six_diablo_meteor);

    //! this executes after BeforeBHit()
    //! BeforeBHit sets a value in trigger script
    //! and HandleHit informs trigger that effect was executed
    //! and we then check if BeforeBHit was ever true
    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* oCaster = GetOriginalCaster();
        if (oCaster && oCaster->IsCreature())
            oCaster->ToCreature()->AI()->SetData(51, 51);
    }


    void BeforeBHit()
    {
        if (Player* target = GetHitPlayer())
            GetOriginalCaster()->ToCreature()->AI()->SetData(52, uint32(true));
    }

    void Register() override
    {
        BeforeHit += SpellHitFn(spell_boss_six_diablo_meteor::BeforeBHit);
        OnEffectHit += SpellEffectFn(spell_boss_six_diablo_meteor::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

enum InfernalStatId
{
    STAT_INFERNAL_HELLFIRE_TIMER            = 219,
    STAT_INFERNAL_HELLFIRE_DAMAGE,
    STAT_INFERNAL_HELLFIRE_RADIUS_RATIO,
    STAT_INFERNAL_HELLFIRE_REPEAT_TIMER
};

struct npc_boss_six_diabolic_infernal : public NullCreatureAI
{
    npc_boss_six_diabolic_infernal(Creature* creature) : NullCreatureAI(creature)
    {
        LoadStats();
    }

    void DamageTaken(Unit* /*att*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        damage = 0;
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues
        ({ STAT_INFERNAL_HELLFIRE_TIMER, STAT_INFERNAL_HELLFIRE_DAMAGE, STAT_INFERNAL_HELLFIRE_RADIUS_RATIO, STAT_INFERNAL_HELLFIRE_REPEAT_TIMER });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case STAT_INFERNAL_HELLFIRE_TIMER:
                    _infernalHellfireFirstTimer = ref.second.StatValue;
                    break;
                case STAT_INFERNAL_HELLFIRE_DAMAGE:
                    _hellfireDamage = ref.second.StatValue;
                    break;
                case STAT_INFERNAL_HELLFIRE_RADIUS_RATIO:
                    _hellfireRadiusRatio = ref.second.StatValue;
                    break;
                case STAT_INFERNAL_HELLFIRE_REPEAT_TIMER:
                    _infernalHellfireRepeatTimer = ref.second.StatValue;
                    break;
            }
        }
    }

    void Reset() override
    {
        me->SetSelectable(false);
        _scheduler.CancelAll();

        _scheduler.Schedule(Seconds(_infernalHellfireFirstTimer), [this](TaskContext func)
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, _hellfireDamage);
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, _hellfireRadiusRatio);
            me->CastCustomSpell(SPELL_DIABLO_INFERNAL_HELLFIRE, val, (Unit*)nullptr, TRIGGERED_IGNORE_POWER_AND_REAGENT_COST);

            func.Repeat(Seconds(_infernalHellfireRepeatTimer));
        });
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

private:
    TaskScheduler _scheduler;

    uint32 _infernalHellfireFirstTimer;
    uint32 _infernalHellfireRepeatTimer;
    uint32 _hellfireDamage;
    uint32 _hellfireRadiusRatio;
};

enum IncreasedDamageTriggerStats
{
    STAT_DAMAGE_TRIGGER_CHECK_TIMER                 = 223,
    STAT_DAMAGE_TRIGGER_BUFFFET_DURATION,
    STAT_DAMAGE_TRIGGET_FLAME_BUFFET_DMG,
    STAT_DAMAGE_TRIGGER_FLAME_BUFFET_RADIUS_RATIO
};

struct npc_boss_six_increased_damage_trigger : public NullCreatureAI
{
    npc_boss_six_increased_damage_trigger(Creature* creature) : NullCreatureAI(creature)
    {
        _scheduler.ClearValidator();
        _heartBeamTargetGUID = 0;
        me->SetCanMissSpells(false);
        LoadStats();
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues
        ({ STAT_DAMAGE_TRIGGER_CHECK_TIMER, STAT_DAMAGE_TRIGGER_BUFFFET_DURATION, STAT_DAMAGE_TRIGGET_FLAME_BUFFET_DMG, STAT_DAMAGE_TRIGGER_FLAME_BUFFET_RADIUS_RATIO });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case STAT_DAMAGE_TRIGGER_CHECK_TIMER:
                    _increasedDamageTriggerCheckTimer = ref.second.StatValue;
                    break;
                case STAT_DAMAGE_TRIGGER_BUFFFET_DURATION:
                    _flameBuffetAuraDuration = ref.second.StatValue;
                    break;
                case STAT_DAMAGE_TRIGGET_FLAME_BUFFET_DMG:
                    _flameBuffetDamage = ref.second.StatValue;
                    break;
                case STAT_DAMAGE_TRIGGER_FLAME_BUFFET_RADIUS_RATIO:
                    _flameBuffetRadiusRatio = ref.second.StatValue;
                    break;
            }
        }
    }

    void Reset() override
    {
        DoCastSelf(SPELL_DIABLO_SUMMON_VISUAL);
        _scheduler.CancelAll();
        me->SetSelectable(false);

        _scheduler.Schedule(Seconds(_increasedDamageTriggerCheckTimer), [this](TaskContext func)
        {
            _playerNearby = false;
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
            me->CastCustomSpell(SPELL_DIABLO_VICINITY_CHECKER_TRIGGER, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);

            val.AddSpellMod(SPELLVALUE_AURA_DURATION, _flameBuffetAuraDuration);
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, _flameBuffetDamage);
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, _flameBuffetRadiusRatio);
            me->CastCustomSpell(SPELL_DIABLO_FLAME_BUFFET, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);

            _scheduler.Schedule(1s, [this](TaskContext /*func*/)
            {
                if (_playerNearby)
                {
                    if (Creature* clone = ObjectAccessor::GetCreature(*me, _heartBeamTargetGUID))
                    {
                        if (!me->IsCasting())
                        {
                            CustomSpellValues val;
                            val.AddSpellMod(SPELLVALUE_AURA_DURATION, 30000);
                            val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 150.f);
                            me->CastCustomSpell(SPELL_DIABLO_MAGNETIC_FIELD, val, clone, TRIGGERED_FULL_MASK);
                        }
                    }
                }
                else
                    me->CastStop();
            });

            func.Repeat(Seconds(_increasedDamageTriggerCheckTimer));
        });
    }

    void SpellHitTarget(Unit* who, SpellInfo const* spellInfo) override
    {
        if (spellInfo->Id == SPELL_DIABLO_VICINITY_CHECKER_TRIGGER && who && who->IsPlayer())
            _playerNearby = true;
    }

    void SetGUID(uint64 guid, int32 /*data*/) override
    {
        _heartBeamTargetGUID = guid;
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }
private:
    TaskScheduler _scheduler;
    uint64 _heartBeamTargetGUID;
    bool _playerNearby;

    uint32 _increasedDamageTriggerCheckTimer;
    uint32 _flameBuffetDamage;
    uint32 _flameBuffetRadiusRatio;
    uint32 _flameBuffetAuraDuration;
};

class spell_five_finger_death_punch : public SpellScript
{
    PrepareSpellScript(spell_five_finger_death_punch);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (!GetHitUnit())
            return;

        Aura* aura = GetHitUnit()->GetAura(GetSpellInfo()->Id);
        if (!aura)
            return;

        if (aura->GetStackAmount() >= 5)
        {
            GetHitUnit()->CastSpell(GetHitUnit(), SPELL_DIABLO_EXPLODING_HEART, true);
            GetHitUnit()->RemoveAurasDueToSpell(GetSpellInfo()->Id);
            if (GetHitUnit()->GetMapId() == DIABLO_MAP_ID)
            {
                if (InstanceScript* instance = GetHitUnit()->GetInstanceScript())
                {
                    if (Creature* diablo = instance->GetCreature(DATA_DIABLO))
                    {
                        diablo->getThreatManager().modifyThreatPercent(GetHitUnit(), -100);
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_AURA_DURATION, diablo->AI()->GetData(STAT_DIABLO_ARMAGEDDON_DURATION));
                        GetHitUnit()->CastCustomSpell(SPELL_DIABLO_ARMAGEDDON, val, GetHitUnit(), TRIGGERED_FULL_MASK, NullItemRef, (const AuraEffect*)nullptr, diablo->GetGUID());
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_five_finger_death_punch::HandleHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};

class spell_boss_diablo_armageddon_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_boss_diablo_armageddon_AuraScript);

    void CalcPeriodic(AuraEffect const* aurEff, bool& isPeriodic, int32& amplitude)
    {
        if (GetCaster() && GetCaster()->GetMapId() == DIABLO_MAP_ID)
        {
            InstanceScript* instance = GetCaster()->GetInstanceScript();
            if (!instance)
                return;

            Creature* diablo = instance->GetCreature(DATA_DIABLO);
            if (!diablo)
                return;

            isPeriodic = true;
            amplitude = diablo->AI()->GetData(STAT_DIABLO_ARMAGEDDON_DURATION) - 500;
        }
    }

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        if (GetTarget() && GetTarget()->GetMapId() == DIABLO_MAP_ID)
        {
            InstanceScript* instance = GetCaster()->GetInstanceScript();
            if (!instance)
                return;

            Creature* diablo = instance->GetCreature(DATA_DIABLO);
            if (!diablo)
                return;

            PreventDefaultAction();
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, diablo->AI()->GetData(STAT_DIABLO_ARMAGEDDON_RADIUS_RATIO));
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, diablo->AI()->GetData(STAT_DIABLO_ARMAGEDDON_DAMAGE));
            val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
            GetTarget()->CastCustomSpell(SPELL_DIABLO_RUNE_DETONATION, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_boss_diablo_armageddon_AuraScript::CalcPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_boss_diablo_armageddon_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

class spell_buffeting_winds_diablo : public AuraScript
{
    PrepareAuraScript(spell_buffeting_winds_diablo);

    void OnEffectRemoved(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEFAULT && GetTarget() && GetTarget()->GetMapId() == DIABLO_MAP_ID)
        {
            InstanceScript* instance = GetTarget()->GetInstanceScript();
            if (!instance)
                return;

            Creature* diablo = instance->GetCreature(DATA_DIABLO);
            if (!diablo)
                return;

            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_ENABLE_SHARE_DAMAGE, 1);
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, diablo->AI()->GetData(STAT_DIABLO_WINDS_DAMAGE));
            GetTarget()->CastCustomSpell(SPELL_DIABLO_STATIC_OVERLOAD, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_buffeting_winds_diablo::OnEffectRemoved, EFFECT_0, SPELL_AURA_SAFE_FALL, AURA_EFFECT_HANDLE_REAL);
    }
};

enum ElementalStats
{
    STAT_ELEMENTAL_DIABLO_DISTANCE          = 227,
    STAT_ELEMENTAL_SELF_DAMAGE_RATIO,
    STAT_ELEMENTAL_CHECK_TIMER,
    STAT_ELEMENTAL_EXPLOSION_DAMAGE,
    STAT_ELEMENTAL_EXPLOSION_RADIUS_RATIO
};

struct npc_boss_diablo_fire_elementals : public NullCreatureAI
{
    npc_boss_diablo_fire_elementals(Creature* creature) : NullCreatureAI(creature)
    {
        LoadStats();
        me->SetCanMissSpells(false);
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues
        ({ STAT_ELEMENTAL_DIABLO_DISTANCE, STAT_ELEMENTAL_SELF_DAMAGE_RATIO, STAT_ELEMENTAL_CHECK_TIMER,
            STAT_ELEMENTAL_EXPLOSION_DAMAGE, STAT_ELEMENTAL_EXPLOSION_RADIUS_RATIO });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case STAT_ELEMENTAL_DIABLO_DISTANCE:
                    _elementalDistanceToDiablo = ref.second.StatVariance;
                    break;
                case STAT_ELEMENTAL_SELF_DAMAGE_RATIO:
                    _elementalSelfDamageRatio = ref.second.StatVariance;
                    break;
                case STAT_ELEMENTAL_CHECK_TIMER:
                    _elementalCheckTimer = ref.second.StatValue;
                    break;
                case STAT_ELEMENTAL_EXPLOSION_DAMAGE:
                    _elementalExplosionDamage = ref.second.StatValue;
                    break;
                case STAT_ELEMENTAL_EXPLOSION_RADIUS_RATIO:
                    _elementalExplosionRadiusRatio = ref.second.StatValue;
                    break;
                default:
                    break;
            }
        }
    }

    void Reset() override
    {
        _exploded = false;
        me->SetWalk(true);
        _scheduler.CancelAll();
        if (Unit* target = me->GetSummoner())
        {
            float angle = me->GetAngle(target->GetPositionX(), target->GetPositionY());
            me->GetMotionMaster()->MoveFollow(target, 0.2f, angle, MOTION_SLOT_CONTROLLED);
        }

        _scheduler.Schedule(1s, [this](TaskContext func)
        {
            if (Unit* target = me->GetSummoner())
            {
                if (target->GetDistance2d(me) <= _elementalDistanceToDiablo)
                    TriggerExplosion();
                else
                {
                    me->DealDamage(me, me, me->GetMaxHealth() * _elementalSelfDamageRatio);
                    func.Repeat(Seconds(_elementalCheckTimer));
                }
            }
        });
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        if (damage >= me->GetHealth())
        {
            damage = 0;
            if (!_exploded)
                TriggerExplosion();
        }
    }

    void TriggerExplosion()
    {
        _exploded = true;
        me->SetSelectable(false);
        me->GetMotionMaster()->Clear();
        me->GetMotionMaster()->MoveIdle();
        _scheduler.CancelAll();
        CustomSpellValues val;

        val.AddSpellMod(SPELLVALUE_BASE_POINT0, _elementalExplosionDamage);
        val.AddSpellMod(SPELLVALUE_RADIUS_MOD, _elementalExplosionRadiusRatio);
        val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
        me->CastCustomSpell(SPELL_DIABLO_ELEMENTAL_ADD_EXPLODE, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
        _scheduler.Schedule(1s, [this](TaskContext)
        {
            Unit::Kill(me, me);
        });
    }

    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }
private:
    TaskScheduler _scheduler;
    bool _exploded;

    float _elementalDistanceToDiablo;
    float _elementalSelfDamageRatio;
    uint32 _elementalCheckTimer;
    uint32 _elementalExplosionDamage;
    uint32 _elementalExplosionRadiusRatio;
};

struct npc_boss_player_flame_sphere : public ScriptedAI
{
    npc_boss_player_flame_sphere(Creature* creature) : ScriptedAI(creature)
    {
        me->SetCanMissSpells(false);
        _arrived = false;
        _targetGUID = 0;
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        damage = 0;
    }

    void DoAction(int32 /*param*/) override
    {
        _arrived = true;
    }

    uint64 GetGUID(int32 data) const override
    {
        return _targetGUID;
    }

    void AttackStart(Unit* who) override
    {
        if (me->Attack(who, false))
            who->AddThreat(me, 100000.f);
    }

    void MoveInLineOfSight(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }

    void SetGUID(uint64 guid, int32 data) override
    {
        _targetGUID = guid;

        Unit* target = ObjectAccessor::GetUnit(*me, guid);
        if (!target)
            return;

        AttackStart(target);
        CustomSpellValues val;
        val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 200);
        me->CastCustomSpell(SPELL_DIABLO_SOUL_SIPHON, val, target, TRIGGERED_FULL_MASK);
    }

private:
    bool _arrived;
    uint64 _targetGUID;
};

class spell_diablo_siphon_soul : public AuraScript
{
    PrepareAuraScript(spell_diablo_siphon_soul);

    void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        if (GetCaster() && GetCaster()->GetMapId() == DIABLO_MAP_ID)
        {
            isPeriodic = true;
            amplitude = 1500;
        }
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        if (GetTarget() && GetCaster())
        {
            InstanceScript* instance = GetTarget()->GetInstanceScript();
            if (!instance)
                return;

            Creature* diablo = instance->GetCreature(DATA_DIABLO);
            if (!diablo)
                return;

            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, diablo->AI()->GetData(STAT_DIABLO_SPIRIT_BURN_DAMAGE));
            GetCaster()->CastSpell(GetTarget(), SPELL_DIABLO_SPIRIT_BURN, true);
        }
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_diablo_siphon_soul::CalcPeriodic, EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_diablo_siphon_soul::HandlePeriodic, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

constexpr uint32 STAT_SHADOW_DRAKE_FLAME_TIMER{ 232 };
constexpr uint32 STAT_SHADOW_DRAKE_VOID_BLAST_TIMER{ 249 };
constexpr uint32 STAT_SHADOW_DRAKE_DEVOURING_FLAME_DAMAGE{ 250 };
constexpr uint32 STAT_SHADOW_DRAKE_VOID_BLAST_DAMAGE{ 251 };
struct npc_boss_diablo_shadow_drake : public ScriptedAI
{
    npc_boss_diablo_shadow_drake(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        ScriptedAI::Reset();
        _scheduler.CancelAll();
        LoadStats();
        _scheduler.ClearValidator();
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ STAT_SHADOW_DRAKE_FLAME_TIMER, STAT_SHADOW_DRAKE_VOID_BLAST_TIMER, STAT_SHADOW_DRAKE_VOID_BLAST_DAMAGE });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case STAT_SHADOW_DRAKE_FLAME_TIMER:
                    _shadowDrakeDevouringFlameTimer = ref.second.StatValue;
                    break;
                case STAT_SHADOW_DRAKE_VOID_BLAST_TIMER:
                    _voidBlastTimer = ref.second.StatValue;
                    break;
                case STAT_SHADOW_DRAKE_VOID_BLAST_DAMAGE:
                    _voidblastDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                default:
                    break;
            }
        }
    }

    void IsSummonedBy(Unit* summoner) override
    {
        me->GetMotionMaster()->MoveTargetedHome(); // call any motionmaster so they do not fall to the ground instantly
        ScriptedAI::IsSummonedBy(summoner);
        DoZoneInCombat(me, 250.f);
        ScheduleAttacks();
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        if (attacker && attacker->IsPlayer())
            damage = 0;
    }

    void ScheduleAttacks()
    {
        _scheduler.Schedule(2s, [this](TaskContext func)
        {
            Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, [this](Unit* object)
            {
                return object->IsPlayer() && !object->GetVehicleBase()
                    && !object->HasAura(SPELL_DIABLO_MC_INSANE)
                    && !object->HasAura(SPELL_DIABLO_LIGHTNING_MARKER_VISUAL)
                    && !object->HasAura(SPELL_DIABLO_BUFFETTING_WINDS);

            });

            bool const IsCasting = me->IsCasting();
            if (target && !IsCasting)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 300.f);
                me->CastCustomSpell(SPELL_DIABLO_DEVOURING_FLAME, val, target);
            }

            if (IsCasting)
                func.Repeat(1s);
            else
                func.Repeat(Seconds(_shadowDrakeDevouringFlameTimer));
        });

        _scheduler.Schedule(Seconds(_voidBlastTimer), [this](TaskContext func)
        {
            Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, [this](Unit* object)
            {
                return object->IsPlayer() && !object->GetVehicleBase()
                    && !object->HasAura(SPELL_DIABLO_MC_INSANE)
                    && !object->HasAura(SPELL_DIABLO_LIGHTNING_MARKER_VISUAL)
                    && !object->HasAura(SPELL_DIABLO_BUFFETTING_WINDS);

            });

            bool const IsCasting = me->IsCasting();
            if (target && !IsCasting)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 500);
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _voidblastDamage);
                me->CastCustomSpell(SPELL_DIABLO_SHADOW_DRAKE_VOID_BLAST, val, target);
            }

            if (IsCasting)
                func.Repeat(Seconds(_voidBlastTimer));
            else
                func.Repeat(Seconds(_voidBlastTimer));
        });
    }

    void AttackStart(Unit* who) override
    {
        me->Attack(who, false);
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }
private:
    TaskScheduler _scheduler;

    uint32 _shadowDrakeDevouringFlameTimer;
    uint32 _voidBlastTimer;
    uint32 _voidblastDamage;
};

class spell_boss_diablo_plasma_blast : public AuraScript
{
    PrepareAuraScript(spell_boss_diablo_plasma_blast);

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        if (!GetCaster())
            return;

        if (!GetCaster()->IsCreature())
            return;

        if (GetCaster()->GetMapId() != DIABLO_MAP_ID)
            return;

        if (GetCaster() && GetTarget())
        {
            float angle = GetCaster()->GetAngle(GetTarget()->GetPositionX(), GetTarget()->GetPositionY());
            GetCaster()->SetFacingTo(angle);
            auto _threatList = GetCaster()->getThreatManager().getThreatList();
            for (auto const& ref : _threatList)
            {
                if (!ref->isOnline())
                    continue;

                Unit* target = ObjectAccessor::GetUnit(*GetCaster(), ref->getUnitGuid());
                if (!target)
                    continue;

                if (target == GetTarget())
                    continue;

                InstanceScript* instance = target->GetInstanceScript();
                if (!instance)
                    continue;

                Creature* diablo = instance->GetCreature(DATA_DIABLO);
                if (!diablo)
                    continue;

                if (GetCaster()->HasInLine(target, diablo->AI()->GetFloatData(STAT_DIABLO_PLASMA_RAY_WIDTH)))
                {
                    float resistance = float(target->GetResistance(SPELL_SCHOOL_MASK_FIRE));
                    float resistFactor = ((resistance * 2.0f) / (resistance + 510.f));
                    uint32 damage = diablo->AI()->GetData(STAT_DIABLO_PLASMA_RAY_DAMAGE) * (1.0f - resistFactor);
                    SpellNonMeleeDamage damageInfo(GetCaster(), target, GetSpellInfo()->Id, SPELL_SCHOOL_MASK_FIRE);
                    damageInfo.damage = damage;
                    damageInfo.target = target;
                    GetCaster()->SendSpellNonMeleeDamageLog(&damageInfo);
                    GetCaster()->DealSpellDamage(&damageInfo, false);
                }
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_boss_diablo_plasma_blast::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

class spell_lightning_marker_visual : public AuraScript
{
    PrepareAuraScript(spell_lightning_marker_visual);

    void OnEffectRemoved(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE && GetTarget() && GetTarget()->GetMapId() == DIABLO_MAP_ID)
        {
            Unit* target = GetTarget();
            InstanceScript* instance = target->GetInstanceScript();
            Creature* diablo = nullptr;
            if (instance)
                diablo = instance->GetCreature(DATA_DIABLO);

            if (!diablo)
                return;

            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, diablo->AI()->GetData(STAT_DIABLO_THUNDERSHOCK_DAMAGE));
            val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 400.f);
            diablo->CastCustomSpell(SPELL_DIABLO_THUNDERSHOCK, val, target, TRIGGERED_FULL_MASK);

            target->KnockbackFrom(target->GetPositionX(), target->GetPositionY(), 0.1f, 45.f);
            target->CastSpell(target, SPELL_DIABLO_BUFFETTING_WINDS, true);

            float radius = diablo->AI()->GetFloatData(STAT_DIABLO_BUFFETING_WINDS_RADIUS);
            std::list<Player*> targets;
            Trinity::AnyPlayerInObjectRangeCheck check(target, radius, true);
            Trinity::PlayerListSearcherWithSharedVision<Trinity::AnyPlayerInObjectRangeCheck> searcher(target, targets, check);
            target->VisitNearbyWorldObject(radius, searcher);

            targets.remove_if([&target](Player* _ref)
            {
                return _ref->GetGUID() == target->GetGUID();
            });

            for (auto && player : targets)
            {
                if (player->IsGameMaster() || player->isDead())
                    continue;

                if (player->HasAura(SPELL_DIABLO_REALM_OF_SHADOWS))
                    continue;

                if (player->GetVehicleBase())
                    continue;

                if (player->HasAura(SPELL_DIABLO_BUFFETTING_WINDS))
                    continue;

                player->KnockbackFrom(player->GetPositionX(), player->GetPositionY(), 0.1f, 45.f);
                player->CastSpell(player, SPELL_DIABLO_BUFFETTING_WINDS, true);
            }
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_lightning_marker_visual::OnEffectRemoved, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_napalm_shell_triggered_damage : public SpellScript
{
    PrepareSpellScript(spell_napalm_shell_triggered_damage);

    void HandleHit(SpellEffIndex /*eff*/)
    {
        HellforgeStatValues stat;
        sWorldCache.GetStatValue(STAT_DIABLO_NAPALAM_SHELL_DAMAGE, stat);
        uint32 damage = urand((stat.StatValue * stat.StatVariance), stat.StatValue);
        SetEffectValue(damage);
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_napalm_shell_triggered_damage::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_napalm_shell_triggered_damage_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_napalm_shell_triggered_damage_AuraScript);

    void CalculateDamageAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (!GetCaster())
            return;

        if (GetCaster()->GetMapId() != DIABLO_MAP_ID)
            return;

        InstanceScript* instance = GetCaster()->GetInstanceScript();
        if (!instance)
            return;

        Creature* diablo = instance->GetCreature(DATA_DIABLO);
        if (!diablo)
            return;

        HellforgeStatValues stat;
        sWorldCache.GetStatValue(STAT_DIABLO_NAPALM_SHELL_PERIODIC, stat);
        amount = urand((stat.StatValue * stat.StatVariance), stat.StatValue);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_napalm_shell_triggered_damage_AuraScript::CalculateDamageAmount, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

struct npc_diablo_napalm_shell_trigger : public NullCreatureAI
{
    npc_diablo_napalm_shell_trigger(Creature* creature) : NullCreatureAI(creature) { }

    void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        damage = 0;
    }

    void UpdateAI(uint32 /*diff*/) override { }
    void SetGUID(uint64 guid, int32 /*=data*/) override
    {
        _cachedTargetGUID = guid;
    }

    uint64 GetGUID(int32 /*=data*/) const override
    {
        return _cachedTargetGUID;
    }
private:
    uint64 _cachedTargetGUID;
};

constexpr uint32 SPELL_DEVOURING_FLAME_TRIGGERED{ 64733 };
class spell_devouring_flame_diablo_hellforge : public AuraScript
{
    PrepareAuraScript(spell_devouring_flame_diablo_hellforge);

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        if (GetTarget() && GetTarget()->GetMapId() == DIABLO_MAP_ID)
        {
            InstanceScript* instance = GetCaster()->GetInstanceScript();
            if (!instance)
                return;

            Creature* diablo = instance->GetCreature(DATA_DIABLO);
            if (!diablo)
                return;

            PreventDefaultAction();

            HellforgeStatValues stat;
            sWorldCache.GetStatValue(STAT_SHADOW_DRAKE_DEVOURING_FLAME_DAMAGE, stat);
            CustomSpellValues val;

            val.AddSpellMod(SPELLVALUE_BASE_POINT0, stat.StatValue);
            val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
            GetTarget()->CastCustomSpell(SPELL_DEVOURING_FLAME_TRIGGERED, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_devouring_flame_diablo_hellforge::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

class spell_diablo_conversion_beam : public AuraScript
{
    PrepareAuraScript(spell_diablo_conversion_beam);

    void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        if (GetCaster() && GetCaster()->GetMapId() == DIABLO_MAP_ID)
        {
            isPeriodic = true;
            amplitude = 500;
        }
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_diablo_conversion_beam::CalcPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

class spell_heart_beam_visual : public AuraScript
{
    PrepareAuraScript(spell_heart_beam_visual);

    void OnEffectRemoved(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetTarget())
            return;

        GetTarget()->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, false);
    }

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetTarget())
            return;

        GetTarget()->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_heart_beam_visual::OnEffectRemoved, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectApply += AuraEffectApplyFn(spell_heart_beam_visual::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_diablo_fire_elemental_explosion : public SpellScript
{
    PrepareSpellScript(spell_diablo_fire_elemental_explosion);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([](WorldObject* object)
        {
            return object && object->ToPlayer() && !object->ToPlayer()->GetVehicleBase();
        });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_diablo_fire_elemental_explosion::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

void AddSC_hellforge_boss_six()
{
    new CreatureAILoader<npc_boss_six_diablo_AI>("npc_boss_six_diablo");
    new CreatureAILoader<npc_boss_six_flying_demon_AI>("npc_boss_six_flying_demon");
    new CreatureAILoader<npc_boss_six_beam_trigger>("npc_boss_six_beam_trigger");
    new CreatureAILoader<npc_boss_six_beam_trigger_explosion>("npc_boss_six_beam_trigger_explosion");
    new CreatureAILoader<npc_boss_diablo_playerclone>("npc_boss_diablo_playerclone");
    new CreatureAILoader<npc_boss_diablo_comet_trigger>("npc_boss_diablo_comet_trigger");
    new CreatureAILoader<npc_boss_six_diabolic_infernal>("npc_boss_six_diabolic_infernal");
    new CreatureAILoader<npc_boss_six_increased_damage_trigger>("npc_boss_six_increased_damage_trigger");
    new CreatureAILoader<npc_boss_diablo_fire_elementals>("npc_boss_diablo_fire_elementals");
    new CreatureAILoader<npc_boss_player_flame_sphere>("npc_boss_player_flame_sphere");
    new CreatureAILoader<npc_boss_diablo_shadow_drake>("npc_boss_diablo_shadow_drake");
    new CreatureAILoader<npc_diablo_napalm_shell_trigger>("npc_diablo_napalm_shell_trigger");

    new AuraScriptLoaderEx<spell_boss_diablo_nether_portal_AuraScript>("spell_boss_diablo_nether_portal");
    new SpellScriptLoaderEx<spell_boss_six_diablo_meteor>("spell_boss_six_diablo_meteor");
    new SpellScriptLoaderEx<spell_five_finger_death_punch>("spell_five_finger_death_punch");
    new SpellScriptLoaderEx<spell_diablo_fire_elemental_explosion>("spell_diablo_fire_elemental_explosion");
    new AuraScriptLoaderEx<spell_boss_diablo_armageddon_AuraScript>("spell_boss_diablo_armageddon");
    new AuraScriptLoaderEx<spell_buffeting_winds_diablo>("spell_buffeting_winds_diablo");
    new AuraScriptLoaderEx<spell_boss_diablo_flametongue_weapon>("spell_boss_diablo_flametongue_weapon");
    new AuraScriptLoaderEx<spell_diablo_siphon_soul>("spell_diablo_siphon_soul");
    new AuraScriptLoaderEx<spell_boss_diablo_plasma_blast>("spell_boss_diablo_plasma_blast");
    new AuraScriptLoaderEx<spell_lightning_marker_visual>("spell_lightning_marker_visual");
    new AuraScriptLoaderEx<spell_devouring_flame_diablo_hellforge>("spell_devouring_flame_diablo_hellforge");
    new AuraScriptLoaderEx<spell_diablo_conversion_beam>("spell_diablo_conversion_beam");
    new AuraScriptLoaderEx<spell_heart_beam_visual>("spell_heart_beam_visual");
    new SpellAuraScriptLoaderEx<spell_napalm_shell_triggered_damage, spell_napalm_shell_triggered_damage_AuraScript>("spell_napalm_shell_triggered_damage");
}
