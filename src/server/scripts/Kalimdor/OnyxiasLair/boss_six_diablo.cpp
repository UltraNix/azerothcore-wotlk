#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "onyxias_lair.h"
#include "SpellScript.h"
#include "MoveSplineInit.h"
#include "GameObjectAI.h"

enum DiabloSpells
{
    SPELL_DIABLO_NETHER_PORTAL_VISUAL       = 66263, // We have to disable proc on this map
    SPELL_DIABLO_EYE_BEAM                   = 49544,
    SPELL_DIABLO_HEART_BEAM_VISUAL          = 54988,
    SPELL_DIABLO_REALM_OF_SHADOWS           = 52693,
    SPELL_DIABLO_RED_BEAM_DROPS             = 30944,
    SPELL_DIABLO_SMOKEY_MARKER              = 16714,
    SPELL_DIABLO_FLAME_BUFFET               = 34121,
    SPELL_DIABLO_RUNE_DETONATION            = 62527, // used instead of base triggered spell in Armageddon spell
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
    SPELL_DIABLO_THUNDERSHOCK               = 56926
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
    NPC_BOSS_SIX_SHADOW_CRYSTAL             = 250223
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
    POINT_ID_FLAME_ORB_PLAYER
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

static const std::vector<Position> const shadowDrakePositions =
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

constexpr uint32 FIRE_ELEMENTAL_SPAWN_POSITION_SIZE{ 4 };
Position const fireelementalsSpawnPositions[FIRE_ELEMENTAL_SPAWN_POSITION_SIZE] =
{
    { -73.179f, -231.372f, -83.96888f, 0.160f },
    { -69.563f, -197.305f, -84.27898f, 6.247f },
    { 19.7060f, -189.098f, -85.21370f, 3.239f },
    { 25.9200f, -229.868f, -84.14931f, 3.141f }
};

static const std::vector<Position> const meteorSpawnPositions =
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
constexpr uint32 AMOUNT_OF_DRAKES_REQUIRED{ 4 };

// ID - 54111 Summon Target Visual spell pod aure od dmg buff
// ID - 46907 Boss Fel Portal State fajny portal visual

// 18036 fajny infernal visual
// ID - 40736 Death Blast

// + explosion at 5stacks ID - 27676 Exploding Heart
// ID - 72313 Twilight Bloodbolt Visual + ball of flames sphere

//ID - 66186 Napalm - z nieba, co X Sekund
//! teleport za gracza i podniesienie
//! death ray, custom dbc spell, ktory triggeruje jakis cone spell podczas trwania casta eyebeam z kologarna ? lub plasma blast
// SPELL_PLASMA_BLAST_25                            = 64529,


#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct npc_boss_six_diablo_AI : public BossAI
{
    npc_boss_six_diablo_AI(Creature* creature) : BossAI(creature, DATA_DIABLO)
    {
        _myShadowDrakePositions = shadowDrakePositions;
        me->SetFloatValue(UNIT_FIELD_COMBATREACH, 6.5f);
        scheduler.ClearValidator();
        me->SetCanMissSpells(false);
    }

    bool CanEventExecute()
    {
        if (Spell* spell = me->GetCurrentSpell(CURRENT_GENERIC_SPELL))
            if (SpellInfo const* spellInfo = spell->GetSpellInfo())
                if (spellInfo->Id == 64487)
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

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        BossAI::SummonedCreatureDies(summon, killer);
        if (summon->GetEntry() == NPC_BOSS_SIX_HEART_BEAM_TRIGGER)
        {
            me->SetAggressive();
            me->AttackStop();
            me->SetVisible(true);
            DoZoneInCombat(me, 250.f);
            CleanupShadowRealm();

            for (auto const& entry : { NPC_BOSS_SIX_INCREASED_DAMAGE_TRIGGER, NPC_BOSS_SIX_HEART_BEAM_TRIGGER, NPC_BOSS_SIX_FIERY_COMET_TRIGGER })
                summons.DespawnEntry(entry);
            SchedulePhaseOneAbilities();
            scheduler.Schedule(10s, [this](TaskContext /*func*/)
            {
                SpawnFirebeamTriggers();
            });
        }
        else if (summon->GetEntry() == NPC_BOSS_SIX_SHADOW_DRAKE && ++_drakesDead >= AMOUNT_OF_DRAKES_REQUIRED)
        {
            for (auto const& guid : summons)
            {
                Creature* phoenix = ObjectAccessor::GetCreature(*me, guid);
                if (phoenix && phoenix->GetEntry() == NPC_BOSS_SIX_ASHES_OF_ALAR)
                {
                    Player* player = phoenix->GetCharmerOrOwnerPlayerOrPlayerItself();
                    phoenix->m_spells[3] = 21667;//todo

                    //! now, if player exists hence vehicle is occupied
                    //! let's send new list of spells to him
                    //! otherwise dont do anything, it will initialize itself when someone mounts the vehicle
                    if (player)
                        player->VehicleSpellInitialize();
                }
            }
        }
        else if (summon->GetEntry() == NPC_BOSS_SIX_OMOR_COPY)
        {
            if (!me->FindNearestCreature(NPC_BOSS_SIX_OMOR_COPY, 300.f))
            {
                me->AttackStop();
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetAggressive();
                DoZoneInCombat(me, 200.f);
                SchedulePhaseOneAbilities();
            }
        }
        else if (summon->GetEntry() == NPC_BOSS_SIX_SHADOW_CRYSTAL)
            DrawPentagram();
    }

    void OnMeleeAttack(VictimState state, WeaponAttackType attType, Unit* victim) override
    {
        if (!victim)
            return;

        if (!victim->ToPlayer())
            return;

        if (attType == BASE_ATTACK)
        {
            if (!roll_chance_i(50 /*config*/))
                return;

            DoCast(victim, 27673, true); // config
        }
        else if (attType == OFF_ATTACK)
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, 25000); // config
            me->CastCustomSpell(SPELL_DIABLO_FLAMETONGUE_ATTACK, val, victim, TRIGGERED_FULL_MASK);
        }
    }

    void Reset() override
    {
        Trinity::Containers::RandomShuffle(_myShadowDrakePositions);
        me->SetCanDualWield(true);
        me->SetFloatValue(UNIT_FIELD_COMBATREACH, 10.f);
        BossAI::Reset();
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        _pentagramIndex = 0;
        _shadowRealmTargetGUID = 0;
        _elementalPhase = false;
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
            return;
        }

        if (me->HealthBelowPctDamaged(20, damage) && !_elementalPhase)
        {
            _elementalPhase = true;
            DoCastSelf(SPELL_DIABLO_SHADOWFORM_1, true);
            DoCastSelf(SPELL_DIABLO_SHADOWFORM_2, true);
            return;
        }

        if (me->HealthBelowPctDamaged(30, damage) && !_readjustNapalmShells)
        {
            _readjustNapalmShells = true;
            _napalmShellCount = 3;
        }

        if (me->HealthBelowPctDamaged(50, damage) && !_intermission)
        {
            _intermission = true;
            me->MonsterYell("Super add piootrka sie zrespi teraz, beda addy to dorobie jego stanie na srodku i cast co napisales na githubie", LANG_UNIVERSAL, nullptr);
            SchedulePhaseTwoAbilities();
            return;
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
            return object->ToPlayer() && !object->HasAura(SPELL_DIABLO_REALM_OF_SHADOWS) && !object->HasAura(SPELL_DIABLO_BUFFETTING_WINDS);
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
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, 50000);
            val.AddSpellMod(SPELLVALUE_AURA_DURATION, 3500);
            me->CastCustomSpell(SPELL_DIABLO_CONVERSION_BEAM, val, target, TRIGGERED_FULL_MASK);

            scheduler.Schedule(4s, [this](TaskContext /*func*/)
            {
                DoCastAOE(SPELL_DIABLO_EXPLOSION, true);
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
        scheduler.Schedule(1s, [this](TaskContext func)
        {
            for (uint32 i = 0; i < _napalmShellCount; ++i)
            {
                Position spawnPosition = Trinity::Containers::SelectRandomContainerElement(_diabloRandomSpawnPositions);
                spawnPosition.m_positionZ += 15.f;

                if (Creature* trigger = me->SummonCreature(NPC_BOSS_SIX_NAPALAM_SHELL_TRIGGER, spawnPosition))
                {
                    trigger->SetSelectable(false);
                    trigger->SetImmuneToPC(true);
                    Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, [this](Unit* object)
                    {
                        return object->ToPlayer() && !object->GetVehicleBase();
                    });
                    if (target)
                        trigger->CastSpell(target, SPELL_DIABLO_NAPALM_SHELL, true, NullItemRef, (AuraEffect*)nullptr, me->GetGUID());
                    trigger->DespawnOrUnsummon(6s);
                };
            }
        });
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
        DoCastSelf(SPELL_DIABLO_FLAMETONGUE_WEAPON);
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
        if (!UpdateVictim() && me->IsVisible())
            return;

        scheduler.Update(diff);
        if (!me->IsPassive())
            DoMeleeAttackIfReady();
    }


    void SpellHit(Unit* caster, SpellInfo const* spellInfo) override
    {
        if (caster && caster->GetEntry() == NPC_BOSS_SIX_ASHES_OF_ALAR && spellInfo->Id == 21667)
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
        scheduler.Schedule(70s, GROUP_DIABLO_PHASE_ONE_CANCELABLE, [this](TaskContext /*func*/)
        {
            BeginShadowRealm();
            //! re-scheduled when previous add dies
        });

        scheduler.Schedule(6s, GROUP_DIABLO_PHASE_ONE_CANCELABLE, [this](TaskContext func)
        {
            HandleKnockbackPlayer();
            func.Repeat(17s);
        });

        scheduler.Schedule(15s, GROUP_DIABLO_PHASE_ONE_CANCELABLE, [this](TaskContext func)
        {
            HandleShadowstep();
            func.Repeat(18s);
        });
    }

    void SchedulePhaseTwoAbilities()
    {
        scheduler.CancelAll();

        scheduler.Schedule(6s, GROUP_DIABLO_PHASE_ONE_CANCELABLE, [this](TaskContext func)
        {
            if (CanEventExecute())
            {
                if (_knockbackOrShadowstep)
                    HandleKnockbackPlayer();
                else
                    HandleShadowstep();

                _knockbackOrShadowstep = !_knockbackOrShadowstep;
            }

            func.Repeat(12s);
        });


        scheduler.Schedule(5s, [this](TaskContext func)
        {
            auto repeatTime = 8s;
            if (!CanEventExecute())
                repeatTime = 10s;
            else
                HandleNapalmShells();

            func.Repeat(repeatTime);
        });

        scheduler.Schedule(20s, [this](TaskContext func)
        {
            HandleFireElementals();
            func.Repeat(20s);
        });

        scheduler.Schedule(45s, [this](TaskContext func)
        {
            auto repeatTimer = 45s;
            if (!CanEventExecute())
                repeatTimer = 5s;
            else
                HandlePlasmaRay();

            func.Repeat(45s);
        });

        scheduler.Schedule(6s, [this](TaskContext func)
        {
            HandlePheonixPhase();
            func.Repeat(90s);
        });
    }

    //! Spawn wave of adds when fight begins
    void SpawnInitialAdds()
    {
        scheduler.Schedule(5s, [this](TaskContext func)
        {
            for (auto pos : netherPortalSpawnPosition)
            {
                if (Creature* portal = me->SummonCreature(NPC_BOSS_SIX_PORTAL_TRIGGER, pos))
                {
                    portal->SetPassive();
                    portal->SetImmuneToAll(true);
                    portal->CastSpell(portal, SPELL_DIABLO_NETHER_PORTAL_VISUAL, TRIGGERED_DISALLOW_PROC_EVENTS);
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
            return object->ToPlayer() && !object->HasAura(SPELL_DIABLO_REALM_OF_SHADOWS) && !object->GetVehicleBase();
        });

        if (!target)
            return;

        me->AddAura(SPELL_DIABLO_LIGHTNING_MARKER_VISUAL, target);
    }

    /** Shadow realm handling **/
    void BeginShadowRealm()
    {
        CleanupShadowRealm();
        _pentagramIndex = 0;
        Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U, 200.f, true);
        if (!target)
            return;

        me->AddAura(SPELL_DIABLO_REALM_OF_SHADOWS, target);
        _shadowRealmTargetGUID = target->GetGUID();

        SpawnShadowrealm();
        SpawnPentagramTriggers();

        scheduler.Schedule(30s, GROUP_DIABLO_CANCELABLE, [this](TaskContext func)
        {
            if (!_shadowRealmSucceeded)
            {
                if (Unit* player = ObjectAccessor::GetUnit(*me, _shadowRealmTargetGUID))
                {
                    SchedulePhaseOneAbilities();
                    CleanupShadowRealm();
                    DoCast(player, SPELL_DIABLO_MC_INSANE, true);
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

        player->RemoveAurasDueToSpell(SPELL_DIABLO_REALM_OF_SHADOWS);
        player->NearTeleportTo(_shadowRealmExitPosition);
        player->AddAura(SPELL_DIABLO_SELF_STUN, player);
        player->AddAura(SPELL_DIABLO_HEART_BEAM_VISUAL, player);
        if (Creature* heartbeam = me->SummonCreature(NPC_BOSS_SIX_HEART_BEAM_TRIGGER, _shadowRealmExitPosition))
        {
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
        scheduler.CancelGroup(GROUP_DIABLO_PHASE_ONE_CANCELABLE);
    }
    /** END OF SHADOW REALM HANDLING **/

    void HandleTriggerCharge(Unit* summoner, Unit* caster)
    {
        if (!summoner || !caster)
            return;

        Position pos = me->GetPosition();
        pos.SetOrientation(summoner->GetAngle(me->GetPositionX(), me->GetPositionY()));
        me->GetNearPosition(pos, 1.5f, pos.GetOrientation());
        Creature* trigger = caster->SummonCreature(NPC_BOSS_SIX_BEAM_TRIGGER, pos);
        if (!trigger)
            return;

        JustSummoned(trigger);
        trigger->SetCanFly(true);
        trigger->SetDisableGravity(true);
        trigger->SetPassive();
        trigger->SetImmuneToPC(true);

        CustomSpellValues val;
        val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 100.f);
        caster->CastCustomSpell(SPELL_DIABLO_EYE_BEAM, val, trigger, TRIGGERED_FULL_MASK);

        Position initialPosition = trigger->GetPosition();
        Position chargePosition = summoner->GetPosition();
        initialPosition.SetOrientation(trigger->GetAngle(summoner->GetPositionX(), summoner->GetPositionY()));

        Movement::MoveSplineInit init(trigger);
        chargePosition.m_positionZ += 1.5f;
        init.MoveTo({ chargePosition.GetPositionX(), chargePosition.GetPositionY(), chargePosition.GetPositionZ() }, false, false);
        init.SetVelocity(42.f);
        std::chrono::milliseconds _timer(init.Launch());

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
        _bossFireOrbPos.m_positionZ += 10.f;

        if (Creature* selfOrb = me->SummonCreature(NPC_BOSS_SIX_BALL_OF_FLAMES_BOSS, _bossFireOrbPos))
        {
            selfOrb->SetSelectable(false);
            selfOrb->SetCanFly(true);
            selfOrb->SetDisableGravity(true);
            selfOrb->SetPassive();
            selfOrb->CastSpell(selfOrb, SPELL_DIABLO_BALL_OF_FLAMES_VISUAL, true);
        }

        _bossFireOrbPos.m_positionZ += 4.5f;

        auto& players = me->GetMap()->GetPlayers();
        for (auto && source : players)
        {
            Player* player = source.GetSource();
            if (!player)
                continue;

            if (player->isDead() || player->IsGameMaster())
                continue;

            if (Creature* orb = me->SummonCreature(NPC_BOSS_SIX_BALL_OF_FLAMES_PLAYER, player->GetPosition()))
            {
                orb->AI()->SetGUID(player->GetGUID());
                JustSummoned(orb);

                orb->SetSelectable(false);
                orb->SetPassive();
                orb->CastSpell(orb, SPELL_DIABLO_BALL_OF_FLAMES_VISUAL, true);
                orb->SetWalk(true);
                orb->SetCanFly(true);
                orb->SetDisableGravity(true);
                orb->GetMotionMaster()->MovePoint(POINT_ID_FLAME_ORB_PLAYER, _bossFireOrbPos);
            }
        }
    }

    void HandleFireElementals()
    {
        for (auto const& pos : fireelementalsSpawnPositions)
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

        scheduler.Schedule(3s, [this](TaskContext)
        {
            for (auto const& pos : fireelementalsSpawnPositions)
                me->SummonCreature(NPC_BOSS_SIX_UNSTABLE_FIRE_ELEMENTAL, pos);
        });
    }

    void HandlePlasmaRay()
    {
        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U, [this](Unit* object)
        {
            return object->ToPlayer() && !object->GetVehicleBase() && !object->HasAura(SPELL_DIABLO_BUFFETTING_WINDS);
        }))
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, 50000);
            val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 300);
            me->CastCustomSpell(64529, val, target, TRIGGERED_FULL_MASK);
        }
    }

    void HandlePheonixPhase()
    {
        _drakesDead = 0; // config
        me->AttackStop();
        me->SetPassive();
        me->GetMotionMaster()->Clear();
        me->GetMotionMaster()->MoveIdle();
        for (auto const& entry : { NPC_BOSS_SIX_ASHES_OF_ALAR, NPC_BOSS_SIX_SHADOW_DRAKE })
            summons.DespawnEntry(entry);

        scheduler.Schedule(35s, [this](TaskContext)
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_MODIFY_CAST_TIME, 15000);
            me->CastCustomSpell(64487, val, (Unit*)nullptr);
        });

        scheduler.Schedule(51s, [this](TaskContext)
        {
            me->SetAggressive();
            me->AttackStop();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            DoZoneInCombat(me, 250.f);
        });

        for (auto i = 0; i < 2; ++i)
        {
            if (Creature* phoenix = me->GetMap()->SummonCreature(NPC_BOSS_SIX_ASHES_OF_ALAR, ashesOfAlarSpawnPositions[i]))
            {
                phoenix->setPowerType(POWER_ENERGY);
                phoenix->SetMaxPower(POWER_ENERGY, 200);
                phoenix->SetPower(POWER_ENERGY, phoenix->GetMaxPower(POWER_ENERGY));
                JustSummoned(phoenix);
                phoenix->SetCanFly(true);
                phoenix->SetDisableGravity(true);
                phoenix->SetCanMissSpells(false);
            }
        }

        for (uint32 i = 0; i < AMOUNT_OF_DRAKES_REQUIRED; ++i)
        {
            if (Creature* drake = me->SummonCreature(NPC_BOSS_SIX_SHADOW_DRAKE, _myShadowDrakePositions[i]))
            {
                drake->SetCanFly(true);
                drake->SetDisableGravity(true);
                drake->SetCanMissSpells(false);
            }
        }
    }

private:
    bool _shadowRealmSucceeded;
    uint32 _pentagramIndex;
    std::vector<uint64> _pentagramTriggerGUIDs;
    uint64 _shadowRealmTargetGUID;
    bool _elementalPhase;
    bool _intermission;
    std::vector<Position> _myShadowDrakePositions;
    uint32 _drakesDead;
    uint64 _meteorTriggerGUID;
    bool _knockbackOrShadowstep;
    uint32 _napalmShellCount;
    bool _readjustNapalmShells;
};

enum DemonSpells
{
    SPELL_DEMON_REFLECT_SPELLS              = 35158,
    SPELL_DEMON_SHADOW_NOVA                 = 51073, // radius_mod 8000 and damage of 5k config
    SPELL_DEMON_NETHER_POWER                = 67108
};

#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct npc_boss_six_flying_demon_AI : public ScriptedAI
{
    npc_boss_six_flying_demon_AI(Creature* creature) : ScriptedAI(creature)
    {
        _reflectingDemonType = false;
    }

    void Reset() override
    {
        _scheduler.CancelAll();
        ScriptedAI::Reset();
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
            _scheduler.Schedule(5s, GROUP_DEMON_SWITCHABLE, [this](TaskContext func)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 8000); // config
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, 5000/*config*/);
                me->CastCustomSpell(SPELL_DEMON_SHADOW_NOVA, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                func.Repeat(1s);
            });
        }
    }

    void EnterCombat(Unit* who) override
    {
        ScriptedAI::EnterCombat(who);
        _scheduler.Schedule(20s, [this](TaskContext func)
        {
            SetData(DATA_SWITCH_DEMON_TYPE, DATA_SWITCH_DEMON_TYPE);
            func.Repeat(20s);
        });

        _scheduler.Schedule(2s, [this](TaskContext func)
        {
            std::list<Creature*> _demons;
            me->GetCreatureListWithEntryInGrid(_demons, me->GetEntry(), 20.f/*config*/);
            _demons.remove_if([this](Creature* ref)
            {
                return ref->GetGUID() == me->GetGUID();
            });

            if (!_demons.empty())
            {
                DoCastSelf(SPELL_DEMON_NETHER_POWER, true);
                if (Aura* aura = me->GetAura(SPELL_DEMON_NETHER_POWER))
                {
                    aura->SetMaxDuration(-1);
                    aura->RefreshDuration();
                }
            }

            func.Repeat(2s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
        DoMeleeAttackIfReady();
    }
private:
    TaskScheduler _scheduler;
    bool _reflectingDemonType;
};

#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct npc_boss_six_beam_trigger : public ScriptedAI
{
    npc_boss_six_beam_trigger(Creature* creature) : ScriptedAI(creature) { }

    void MoveInLineOfSight(Unit* who) override { }
    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
};

struct npc_boss_six_beam_trigger_explosion : public ScriptedAI
{
    npc_boss_six_beam_trigger_explosion(Creature* creature) : ScriptedAI(creature)
    {
        _scheduler.CancelAll();
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
            DoCastSelf(35470, true);
            DoCastSelf(69671, true);
        });
    }

private:
    TaskScheduler _scheduler;
};

#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct npc_boss_diablo_playerclone : public ScriptedAI
{
    npc_boss_diablo_playerclone(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
        _myMeteorSpawnPositions = meteorSpawnPositions;
    }

    void Reset() override { }
    void AttackStart(Unit* /*attacker*/) override { }
    void EnterCombat(Unit* /*who*/) override { }

    void IsSummonedBy(Unit* /*summoner*/) override
    {
        _scheduler.CancelAll();
        DoZoneInCombat(me, 200.f);
        _scheduler.Schedule(4s, [this](TaskContext func)
        {
            for (uint32 i = 0; i < 3/*config*/; ++i)
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
            func.Repeat(14s); // config
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

#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct npc_boss_diablo_comet_trigger : public ScriptedAI
{
    npc_boss_diablo_comet_trigger(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
        _didSpawnInfernal = false;
        me->SetCanMissSpells(false);
    }

    void Reset() override
    {
        DoCastSelf(43467);
        me->SetSelectable(false);
        _scheduler.CancelAll();

        _scheduler.Schedule(10s, [this](TaskContext /*func*/)
        {
            Creature* diablo = _instance->GetCreature(DATA_DIABLO);
            if (diablo)
            {
                Creature* _caster = ObjectAccessor::GetCreature(*me, diablo->AI()->GetGUID());
                if (_caster)
                    _caster->CastSpell(me, 36837, true, NullItemRef, (AuraEffect*)nullptr, me->GetGUID());
            }
        });

        me->DespawnOrUnsummon(20s);
    }

    void SetData(uint32 type, uint32 value) override
    {
#pragma message(CompileMessage "zmienic magic numbers")
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

#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct npc_boss_six_diabolic_infernal : public NullCreatureAI
{
    npc_boss_six_diabolic_infernal(Creature* creature) : NullCreatureAI(creature) { }

    void DamageTaken(Unit* /*att*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        damage = 0;
    }

    void Reset() override
    {
        me->SetSelectable(false);
        _scheduler.CancelAll();
        _scheduler.Schedule(2s, [this](TaskContext func)
        {
            if (!me->IsCasting())
            {
                //! change radius of trigger spell
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT1, 0);
                me->CastCustomSpell(68147, val, (Unit*)nullptr, TRIGGERED_IGNORE_POWER_AND_REAGENT_COST);
            }

            func.Repeat(4s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

private:
    TaskScheduler _scheduler;
};

struct npc_boss_six_increased_damage_trigger : public NullCreatureAI
{
    npc_boss_six_increased_damage_trigger(Creature* creature) : NullCreatureAI(creature)
    {
        _scheduler.ClearValidator();
        _heartBeamTargetGUID = 0;
        me->SetCanMissSpells(false);
    }

    void Reset() override
    {
        DoCastSelf(54111);
        _scheduler.CancelAll();
        me->SetSelectable(false);
        _scheduler.Schedule(2s, [this](TaskContext func)
        {
            _playerNearby = false;
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
            me->CastCustomSpell(56543, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);

#pragma message(CompileMessage "Ten szajs sie nie refreshuje poprawnie jezeli zmienimy castera - retest")
            val.AddSpellMod(SPELLVALUE_AURA_DURATION, 35000);
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, 5000); // config
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 1); // 1/1000 = 0.0001 | base radius of 50,000 * 0.0001 equals 5 yards radius
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
                            val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 100.f);
                            me->CastCustomSpell(64668, val, clone, TRIGGERED_FULL_MASK);
                        }
                    }
                }
                else
                    me->CastStop();
            });

            func.Repeat(2s);
        });
    }

    void SpellHitTarget(Unit* who, SpellInfo const* spellInfo) override
    {
        if (spellInfo->Id == 56543 && who && who->IsPlayer())
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
#pragma message(CompileMessage "wyjebac magiczne liczby z calego pliku")
            GetHitUnit()->CastSpell(GetHitUnit(), 27676, true);
            GetHitUnit()->RemoveAurasDueToSpell(GetSpellInfo()->Id);
            if (GetHitUnit()->GetMapId() == 249/*onyxias lair*/)
            {
                GetHitUnit()->CastSpell(GetHitUnit(), 20478, true);
                if (InstanceScript* instance = GetHitUnit()->GetInstanceScript())
                {
                    if (Creature* diablo = instance->GetCreature(DATA_DIABLO))
                        diablo->getThreatManager().modifyThreatPercent(GetHitUnit(), -100);
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

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        if (GetTarget() && GetTarget()->GetMapId() == 249)
        {
            PreventDefaultAction();
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 6666);
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, 500000/*config*/);
            val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
            GetTarget()->CastCustomSpell(SPELL_DIABLO_RUNE_DETONATION, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_boss_diablo_armageddon_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

class spell_buffeting_winds_diablo : public AuraScript
{
    PrepareAuraScript(spell_buffeting_winds_diablo);

    void OnEffectRemoved(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEFAULT && GetTarget() && GetTarget()->GetMapId() == 249)
        {
            //59798
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_ENABLE_SHARE_DAMAGE, 1);
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, 50000);
            GetTarget()->CastCustomSpell(59798, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_buffeting_winds_diablo::OnEffectRemoved, EFFECT_0, SPELL_AURA_SAFE_FALL, AURA_EFFECT_HANDLE_REAL);
    }
};

struct npc_boss_diablo_fire_elementals : public NullCreatureAI
{
    npc_boss_diablo_fire_elementals(Creature* creature) : NullCreatureAI(creature) { }

    void Reset() override
    {
        me->SetSpeedRate(MOVE_RUN, 0.3f);
        me->SetSpeedRate(MOVE_WALK, 0.3f);
        me->SetWalk(true);

        _scheduler.CancelAll();
        if (Unit* target = me->GetSummoner())
        {
            float angle = me->GetAngle(target->GetPositionX(), target->GetPositionY());
            me->GetMotionMaster()->MoveFollow(target, 0.2f, angle, MOTION_SLOT_CONTROLLED);
        }

        _scheduler.Schedule(5s, [this](TaskContext func)
        {
            bool _repeat = true;
            if (Unit* target = me->GetSummoner())
            {
                if (target->GetDistance2d(me) <= 0.5f)
                {
                    me->MonsterYell("DOSZEDLEM DO BOSSA, DESPAWN. Nie ma dmg, znalezc spell, ile ma bic", LANG_UNIVERSAL, nullptr);
                    JustDied(target);
                    me->DespawnOrUnsummon(1s);
                    _repeat = false;
                }
            }

            if (_repeat)
            {
                me->DealDamage(me, me, me->GetMaxHealth() * 0.1);
                func.Repeat(2s);
            }
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
        val.AddSpellMod(SPELLVALUE_BASE_POINT0, 5000); // config
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
        isPeriodic = true;
        amplitude = 1500;
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        if (GetTarget() && GetCaster())
            GetCaster()->CastSpell(GetTarget(), SPELL_DIABLO_SPIRIT_BURN, true);
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_diablo_siphon_soul::CalcPeriodic, EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_diablo_siphon_soul::HandlePeriodic, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

struct npc_boss_diablo_shadow_drake : public ScriptedAI
{
    npc_boss_diablo_shadow_drake(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        ScriptedAI::Reset();
        _scheduler.CancelAll();
    }

    void IsSummonedBy(Unit* summoner) override
    {
        me->GetMotionMaster()->MoveTargetedHome(); // call any motionmaster so they do not fall to the ground instantly
        ScriptedAI::IsSummonedBy(summoner);
        DoZoneInCombat(me, 250.f);
        ScheduleAttacks();
    }

    void ScheduleAttacks()
    {
        _scheduler.Schedule(2s, [this](TaskContext func)
        {
            Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, [this](Unit* object)
            {
                return object->IsPlayer() && !object->GetVehicleBase();
            });

            if (target)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 300.f);
                me->CastCustomSpell(SPELL_DIABLO_DEVOURING_FLAME, val, target);
            }

            func.Repeat(5s);
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
};

constexpr uint32 SPELL_DIABLO_INFERNAL_HELLFIRE_TRIGGERED{ 68144 };
class spell_boss_diablo_hellfire_effect : public AuraScript
{
    PrepareAuraScript(spell_boss_diablo_hellfire_effect);

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        if (GetCaster() && GetCaster()->GetMapId() == DIABLO_MAP_ID)
        {
            PreventDefaultAction();
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, 50000);
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 5000);
            GetCaster()->CastCustomSpell(SPELL_DIABLO_INFERNAL_HELLFIRE_TRIGGERED, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_boss_diablo_hellfire_effect::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
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

                if (GetCaster()->HasInLine(target, 1.f/*config*/))
                {
                    float resistance = float(target->GetResistance(SPELL_SCHOOL_MASK_FIRE));
                    // copy paste of sindragosas script
                    float resistFactor = ((resistance * 2.0f) / (resistance + 510.f));
                    uint32 damage = 10000 * (1.0f - resistFactor);
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

            if (diablo)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, 15000 /*config*/);
                val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 400.f);
                diablo->CastCustomSpell(SPELL_DIABLO_THUNDERSHOCK, val, target, TRIGGERED_FULL_MASK);
            }

            target->KnockbackFrom(target->GetPositionX(), target->GetPositionY(), 0.1f, 45.f);
            target->CastSpell(target, SPELL_DIABLO_BUFFETTING_WINDS, true);

            std::list<Player*> targets;
            Trinity::AnyPlayerInObjectRangeCheck check(target, 10.f, true);
            Trinity::PlayerListSearcherWithSharedVision<Trinity::AnyPlayerInObjectRangeCheck> searcher(target, targets, check);
            target->VisitNearbyWorldObject(10.f, searcher);
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


                player->KnockbackFrom(target->GetPositionX(), target->GetPositionY(), 0.1f, 45.f);
            }
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_lightning_marker_visual::OnEffectRemoved, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
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

    new AuraScriptLoaderEx<spell_boss_diablo_nether_portal_AuraScript>("spell_boss_diablo_nether_portal");
    new SpellScriptLoaderEx<spell_boss_six_diablo_meteor>("spell_boss_six_diablo_meteor");
    new SpellScriptLoaderEx<spell_five_finger_death_punch>("spell_five_finger_death_punch");
    new AuraScriptLoaderEx<spell_boss_diablo_armageddon_AuraScript>("spell_boss_diablo_armageddon");
    new AuraScriptLoaderEx<spell_buffeting_winds_diablo>("spell_buffeting_winds_diablo");
    new AuraScriptLoaderEx<spell_boss_diablo_flametongue_weapon>("spell_boss_diablo_flametongue_weapon");
    new AuraScriptLoaderEx<spell_diablo_siphon_soul>("spell_diablo_siphon_soul");
    new AuraScriptLoaderEx<spell_boss_diablo_hellfire_effect>("spell_boss_diablo_hellfire_effect");
    new AuraScriptLoaderEx<spell_boss_diablo_plasma_blast>("spell_boss_diablo_plasma_blast");
    new AuraScriptLoaderEx<spell_lightning_marker_visual>("spell_lightning_marker_visual");
}
