#include "hellforge.hpp"

#include "MoveSplineInit.h"
#include "G3D/Vector3.h"
#include "GameObjectAI.h"

#include <algorithm>
#include <array>
#include <chrono>

constexpr size_t SPAWN_IN_TRIGGERS_SIZE{ 40 };
constexpr uint32 SNAKE_MOVEMENT_SIZE{ 22 };
G3D::Vector3 const _snakeMovement[SNAKE_MOVEMENT_SIZE]
{
    { 1329.794f, -432.588f, -92.00099f },
    { 1329.794f, -432.588f, -92.00099f },
    { 1329.655f, -427.900f, -92.00436f },
    { 1331.151f, -410.436f, -92.01847f },
    { 1330.562f, -390.635f, -92.00053f },
    { 1330.352f, -383.568f, -92.01181f },
    { 1329.322f, -375.007f, -92.00355f },
    { 1360.840f, -375.954f, -92.02916f },
    { 1385.120f, -375.355f, -92.01956f },
    { 1406.118f, -375.622f, -92.01409f },
    { 1431.415f, -374.534f, -92.00338f },
    { 1431.113f, -400.188f, -92.01626f },
    { 1431.695f, -427.056f, -92.00615f },
    { 1431.693f, -443.436f, -92.01548f },
    { 1431.691f, -463.246f, -92.01798f },
    { 1431.689f, -477.246f, -92.01263f },
    { 1411.907f, -476.187f, -92.02980f },
    { 1394.363f, -475.247f, -92.01299f },
    { 1373.416f, -475.046f, -92.02066f },
    { 1353.631f, -475.474f, -92.01286f },
    { 1329.024f, -477.966f, -92.01066f },
    { 1329.988f, -454.839f, -92.01718f }
};

constexpr uint32 CROSSFIRE_SPAWN_SIZE{ 16 };
std::array<Position const, CROSSFIRE_SPAWN_SIZE> _crossFireSpawnPositions =
{
    //! spawns are made in pairs, opposing trigger is right after position
    //! ie. trigger spawned at [0] casts at trigger spawned at [1] and [1] casts back at [0]
    // zmienic orientation
    {
        //! 1st pair
        { 1363.363f, -383.868f, -89.524f, 4.711f },
        { 1363.363f, -467.397f, -89.524f, 4.711f },

        //! 2nd pair
        { 1381.295f, -383.868f, -89.524f, 4.711f },
        { 1381.295f, -467.397f, -89.524f, 4.711f },

        //! 3rd pair
        { 1398.105f, -383.868f, -89.524f, 4.711f },
        { 1398.105f, -467.397f, -89.524f, 4.711f },

        //! 4th pair
        { 1407.832f, -392.503f, -89.680f, 3.142f },
        { 1353.895f, -392.503f, -89.680f, 3.142f },

        //! 5th pair
        { 1407.832f, -409.692f, -89.680f, 3.142f },
        { 1353.895f, -409.692f, -89.680f, 3.142f },

        //! 6th pair
        { 1407.832f, -426.692f, -89.680f, 3.142f },
        { 1353.895f, -426.692f, -89.680f, 3.142f },

        //! 7th pair
        { 1407.832f, -442.313f, -89.680f, 3.142f },
        { 1353.895f, -442.313f, -89.680f, 3.142f },

        //! 8th pair
        { 1407.832f, -459.035f, -89.680f, 3.142f },
        { 1353.895f, -459.035f, -89.680f, 3.142f }
    }
};

enum BossTwoSpells
{
    SPELL_BOSS_TWO_BLIGHT_CRYSTAL       = 54087,

    SPELL_SOAKER_VISUAL_ONE             = 43167,
    SPELL_SOAKER_VISUAL_TWO             = 43161,
    SPELL_SOAKER_SLIME_POOL             = 70343,
    SPELL_SOAKER_OOZE_EXPLOSION         = 73030,
    SPELL_SOAKER_DESPAWN_VISUAL         = 52776,
    SPELL_SPAWN_IN_VISUAL_BOSS_TWO      = 73078,
    SPELL_ALTAR_TELEPORT_VISUAL         = 64446,
    SPELL_LAVA_GOUT_EXPLOSION           = 74395,
    SPELL_BASHIR_SPAWN_IN_HELLFORGE     = 41302,
    SPELL_ALTAR_TOXIC_WASTE             = 70274,
    SPELL_BOSS_TWO_CRYSTAL_PRISON       = 32361,
    SPELL_CROSSFIRE_HOLY_BOLT           = 57465,
    SPELL_BLOODY_DEATH                  = 25770,
    SPELL_ENRAGE_VISUAL_SNAKE           = 42438,
    SPELL_ENRAGE_POTENT_JOLT            = 51819,
    SPELL_SNAKE_VENOMOUS_BREATH         = 51415
};

enum BossTwoGOs
{
    //! Has OnGossipHello which triggers sacrifice part of the fight
    GO_SACRIFICE_ALTAR_BOSS_TWO         = 400500,
    GO_COMBAT_GONG                      = 400504
};

enum BossTwoNPCs
{
    NPC_BOSS_TWO_SOAKER                 = 250004,
    NPC_BOSS_TWO_ADD_ONE                = 250005,
    NPC_BOSS_TWO_ADD_TWO                = 250006,
    NPC_BOSS_TWO_CROSSFIRE_TRIGGERS     = 250007,
    NPC_ADD_VISUAL_SPAWN_IN_TRIGGER     = 250008,
    NPC_ADD_ROAMING_GREEN_EXPLOSION     = 250009,
    NPC_ADD_DELAYED_EXPLOSION           = 250010,
    NPC_ADD_FLAME_SPREADER              = 250011,
    NPC_ADD_FLAME_HIT_TARGET            = 250012,
    NPC_ADD_FLAME_SPREADER_CASTER       = 250013,
};

enum BossTwoMisc : uint32
{
    AMOUNT_OF_SOAKERS_TO_SPAWN          = 3,
    DATA_ALTAR_CLICKED,
    DATA_SACRIFICED_PLAYER,
    DATA_ALTAR_ACTIVATED,
    DATA_SOAKER_PREVENTED,
    DATA_IS_SACRIFIED,
    DATA_FINISH_SACRIFICE,
    DATA_ADD_DIED,
    DATA_BEGIN_SNAKE_COMBAT
};

enum BossTwoEvents
{
    //! check if everyone is within fighting area
    EVENT_BOSS_TWO_CHECK_PLAYERS        = 1,
    //! Fires a delayed crystal spell at random player within boss area
    EVENT_FIRE_BLIGHT_CRYSTAL,
    EVENT_SPAWN_SOAKERS,
    EVENT_SPAWN_ALTAR,
    //! executed 10s after EVENT_SPAWN_ALTAR
    //! if _altarHasBeenClicked return false means noone interacted and we wipe entire map
    EVENT_ALTAR_CHECK,
    EVENT_SPAWN_MAIN_ADD,
    EVENT_SNAKE_POTENT_JOLT,
    EVENT_SNAKE_VENOMOUS_BREATH,

    //! soakers events
    EVENT_SOAKER_EXPLOSION              = 10
};

Position const _centerOfFightingArea{ 1380.42f, -425.72f, -94.67f, 0.0f };

constexpr uint32 POSITION_CORNER_SIZE{ 4 };
std::array<const Position, POSITION_CORNER_SIZE> const _fightingAreaCorners =
{ {
    { 1390.760f, -400.398f, -94.674f },
    { 1370.487f, -400.546f, -94.674f },
    { 1370.654f, -451.195f, -94.674f },
    { 1390.833f, -451.444f, -94.674f }
} };

enum BossTwoStats
{
    BOSS_TWO_STAT_ID_HEALTH                     = 8,
    BOSS_TWO_STAT_ID_ADD_HEALTH                 = 9,
    BOSS_TWO_STAT_ID_MELEE_DAMAGE               = 10,
    BOSS_TWO_STAT_ID_ADD_MELEE_DMG              = 11,

    // spells
    BOSS_TWO_STAT_ID_BLIGHT_CRYSTAL_DMG         = 12,
    BOSS_TWO_STAT_ID_BLIGHT_CRYSTAL_PERIODIC    = 13,
    BOSS_TWO_STAT_ID_VENOM_BREATH               = 14,
    BOSS_TWO_STAT_ID_FINAL_PHASE_PERCENT        = 15,
    BOSS_TWO_STAT_ID_SOAK_EXPLOSION_DAMAGE      = 16,
    BOSS_TWO_STAT_ID_ENERGY_PER_SOAK            = 17,
    BOSS_TWO_STAT_ID_MOJO_WAVE_DAMAGE           = 18,
    BOSS_TWO_STAT_ID_CHAOTIC_LIGHT              = 19,
    BOSS_TWO_STAT_ID_EXPLODE_PCT                = 20,
    BOSS_TWO_STAT_ID_EXPLOSION_DAMAGE           = 21,
    BOSS_TWO_STAT_ID_CROSSFIRE_RADIUS           = 22,
    BOSS_TWO_STAT_ID_CROSSFIRE_DAMAGE           = 23,
    BOSS_TWO_STAT_ID_DISTANCE_FROM_POSITION     = 24
};

struct boss_hellforge_boss_two_AI : public BossAI
{
    boss_hellforge_boss_two_AI(Creature* creature) : BossAI(creature, DATA_BOSS_TWO), _phaseTwo(false), _mySoakerSpawnPositions(_soakerSpawnPositions) { }

    void InitializeMovement()
    {
        scheduler.Schedule(1s, [this](TaskContext func)
        {
            me->StopMoving();
            Movement::PointsArray _path(_snakeMovement, _snakeMovement + SNAKE_MOVEMENT_SIZE);
            Movement::MoveSplineInit init(me);
            init.Path() = _path;
            init.SetWalk(false);
            init.SetSmooth();
            auto time = std::chrono::milliseconds(init.Launch());
            sLog->outDebug(LOG_FILTER_TSCR, "Hellforge boss two, function InitializeMovement initializes spline of size (%zu) and duration %d", _path.size(), time.count());
            func.Repeat(time);
        });
    }

    void EnterEvadeMode() override
    {
        if (GameObject* altarBase = me->FindNearestGameObject(GO_SACRIFICE_ALTAR_BOSS_TWO, 200.f))
            altarBase->RemoveFromWorld();

        if (GameObject* cage = instance->GetGameObject(DATA_GO_BOSS_TWO_CAGE))
            cage->SetGoState(GO_STATE_ACTIVE);

        std::list<Creature*> _temp;
        me->GetCreatureListWithEntryInGrid(_temp, NPC_ADD_DELAYED_EXPLOSION, 200.f);
        for (auto const& explo : _temp)
            explo->DespawnOrUnsummon();
        me->NearTeleportTo(me->GetHomePosition());
        _DespawnAtEvade();
    }

    void WipeEntireMap()
    {
        auto const& _players = me->GetMap()->GetPlayers();
        for (auto && source : _players)
        {
            Player* player = source.GetSource();
            if (!player)
                continue;

            if (player->IsGameMaster())
                continue;

            player->CastSpell(player, SPELL_BLOODY_DEATH, true);
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_BLOODY_DEATH);
            Unit::Kill(me, player, true, BASE_ATTACK, spellInfo ? spellInfo : nullptr);
        }
    }

    void AttackStart(Unit* attacker) override
    {
        if (_phaseTwo)
            BossAI::AttackStart(attacker);
        else
            me->Attack(attacker, false);
    }

    void SetGUID(uint64 guid, int32 type) override
    {
        if (type == DATA_SACRIFICED_PLAYER)
            _sacrificedPlayer = guid;
        else if (type == DATA_FINISH_SACRIFICE)
            _sacrificedPlayer = 0;
    }

    bool CheckGUID(uint64 guid, int32 type) const override
    {
        if (type == DATA_IS_SACRIFIED && guid)
            return guid == _sacrificedPlayer;

        return false;
    }

    void Reset() override
    {
        me->SetVisible(false);
        if (GameObject* gong = me->FindNearestGameObject(GO_COMBAT_GONG, 200.f))
            gong->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);

        _phaseTwo = false;
        Trinity::Containers::RandomShuffle(_mySoakerSpawnPositions);
        BossAI::Reset();
        Position pos = _centerOfFightingArea;
        pos.m_positionZ += 11.f;
        me->SummonCreature(NPC_ADD_FLAME_SPREADER_CASTER, pos);
        LoadBossStats();
        _fightTimer = 0;
    }

    void LoadBossStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ BOSS_TWO_STAT_ID_HEALTH, BOSS_TWO_STAT_ID_MELEE_DAMAGE,
            BOSS_TWO_STAT_ID_BLIGHT_CRYSTAL_DMG, BOSS_TWO_STAT_ID_BLIGHT_CRYSTAL_PERIODIC,
            BOSS_TWO_STAT_ID_VENOM_BREATH, BOSS_TWO_STAT_ID_FINAL_PHASE_PERCENT });

        for (auto && ref : _stats)
        {
            switch (ref.first)
            {
                case BOSS_TWO_STAT_ID_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case BOSS_TWO_STAT_ID_MELEE_DAMAGE:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case BOSS_TWO_STAT_ID_BLIGHT_CRYSTAL_DMG:
                {
                    _blightCrystalDirectDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_TWO_STAT_ID_BLIGHT_CRYSTAL_PERIODIC:
                {
                    _blightCrystalPeriodicDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_TWO_STAT_ID_VENOM_BREATH:
                {
                    _venomBreathDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_TWO_STAT_ID_FINAL_PHASE_PERCENT:
                {
                    _finalPhaseHealthPercentage = ref.second.StatVariance;
                    break;
                }
                default:
                    break;
            }
        }
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (!me->IsVisible())
            return;

        BossAI::MoveInLineOfSight(who);
    }

    uint32 GetData(uint32 id) const override
    {
        switch (id)
        {
            case BOSS_TWO_STAT_ID_BLIGHT_CRYSTAL_DMG:
                return _blightCrystalDirectDamage;
            case BOSS_TWO_STAT_ID_BLIGHT_CRYSTAL_PERIODIC:
                return _blightCrystalPeriodicDamage;
            default:
                return 0;
        }

        return 0;
    }

    void EnterCombat(Unit* who) override
    {
        if (!instance->CheckRequiredBosses(DATA_BOSS_TWO))
        {
            HandleRequiredBossFail();
            return;
        }

        _fightTimer = getMSTime();
        BossAI::EnterCombat(who);
        events.ScheduleEvent(EVENT_FIRE_BLIGHT_CRYSTAL, 20s);
        events.ScheduleEvent(EVENT_SPAWN_SOAKERS, 15s);
        events.ScheduleEvent(EVENT_SPAWN_ALTAR, 5s);
        events.ScheduleEvent(EVENT_BOSS_TWO_CHECK_PLAYERS, 10s);
        events.ScheduleEvent(EVENT_SPAWN_MAIN_ADD, 1s);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);
        scheduler.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (auto eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SPAWN_MAIN_ADD:
                    me->SummonCreature(NPC_BOSS_TWO_ADD_ONE, Trinity::Containers::SelectRandomContainerElement(_fightingAreaCorners));
                    break;
                case EVENT_BOSS_TWO_CHECK_PLAYERS:
                {
                    auto& _players = me->GetMap()->GetPlayers();
                    for (auto && src : _players)
                    {
                        if (Player* player = src.GetSource())
                        {
                            if (player->IsGameMaster())
                                continue;

                            if (!player->IsWithinBox(_centerOfFightingArea, 15.f, 35.f, 10.f))
                                player->TeleportTo(me->GetMapId(), _centerOfFightingArea);
                        }
                    }
                    events.Repeat(5s);
                    break;
                }
                case EVENT_FIRE_BLIGHT_CRYSTAL:
                {
                    std::vector<Player*> _tempTargets;

                    auto threatList = me->getThreatManager().getThreatList();
                    for (auto ref : threatList)
                    {
                        if (Unit* obj = ObjectAccessor::GetUnit(*me, ref->getUnitGuid()))
                        {
                            //! ignore non-players alltogether
                            if (!obj->ToPlayer())
                                continue;

                            if (IsCurrentlySacrificed(obj->GetGUID()))
                                continue;

                            //! if player is within fighting area
                            if (obj->IsWithinBox(_centerOfFightingArea, 15.f, 35.f, 10.f))
                                _tempTargets.push_back(obj->ToPlayer());
                        }
                    }

                    if (_tempTargets.empty())
                    {
                        events.Repeat(20s);
                        break;
                    }

                    std::sort(_tempTargets.begin(), _tempTargets.end(), Trinity::PositionDistanceOrderPred(_centerOfFightingArea, false));

                    //! get farthest player, cast blight crystal at him
                    //! blight crystal triggers DYNOBj aura on hit
                    Unit* validTarget = _tempTargets.front();
                    if (validTarget)
                        DoCast(validTarget, SPELL_BOSS_TWO_BLIGHT_CRYSTAL, true);

                    events.Repeat(30s);
                    break;
                }
                case EVENT_SPAWN_SOAKERS:
                {
                    for (uint32 i = 0; i < AMOUNT_OF_SOAKERS_TO_SPAWN; ++i)
                    {
                        std::rotate(_mySoakerSpawnPositions.begin(), _mySoakerSpawnPositions.begin() + urand(1, 3), _mySoakerSpawnPositions.end());
                        me->SummonCreature(NPC_BOSS_TWO_SOAKER, _mySoakerSpawnPositions.back());
                    }

                    events.Repeat(25s);
                    break;
                }
                case EVENT_SPAWN_ALTAR:
                {
                    me->GetMap()->SummonGameObject(GO_SACRIFICE_ALTAR_BOSS_TWO, _centerOfFightingArea, 0.f, 0.f, 0.f, 0.f, 0);
                    _altarHasBeenClicked = false;
                    events.ScheduleEvent(EVENT_ALTAR_CHECK, 10s);
                    events.Repeat(2min);
                    break;
                }
                case EVENT_ALTAR_CHECK:
                {
                    if (!_altarHasBeenClicked)
                        WipeEntireMap();
                    break;
                }
                case EVENT_SNAKE_POTENT_JOLT:
                {
                    DoCastSelf(SPELL_ENRAGE_POTENT_JOLT, true);
                    events.Repeat(2.5s);
                    break;
                }
                case EVENT_SNAKE_VENOMOUS_BREATH:
                {
                    CustomSpellValues val;
                    val.AddSpellMod(SPELLVALUE_BASE_POINT0, _venomBreathDamage);
                    val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
                    me->CastCustomSpell(SPELL_SNAKE_VENOMOUS_BREATH, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                    events.Repeat(10s);
                    break;
                }
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
        EnterEvadeIfOutOfCombatArea();
    }

    bool CheckEvadeIfOutOfCombatArea() const override
    {
        return me->GetDistance(_centerOfFightingArea) >= 180.f;
    }

    const bool IsCurrentlySacrificed(uint64 const guid) const
    {
        Player const* player = ObjectAccessor::GetPlayer(*me, guid);
        if (!player)
            return false;

        return guid == _sacrificedPlayer;
    }

    void SetData(uint32 type, uint32 value) override
    {
        switch (type)
        {
            case DATA_SOAKER_PREVENTED:
            {
                //! inform all adds about soaker being prevented
                //! ie. big add gets his energy when soaker gets soaked
                summons.Broadcast([](Creature* summon) { summon->AI()->SetData(DATA_SOAKER_PREVENTED, DATA_SOAKER_PREVENTED); });
                break;
            }
            case DATA_ALTAR_CLICKED:
            {
                _altarHasBeenClicked = true;
                break;
            }
            case DATA_ALTAR_ACTIVATED:
            {
                if (GameObject* altarBase = me->FindNearestGameObject(GO_SACRIFICE_ALTAR_BOSS_TWO, 200.f))
                    altarBase->RemoveFromWorld();
                break;
            }
            case DATA_ADD_DIED:
            {
                me->StopMoving();
                me->AttackStop();
                DoResetThreat();
                _phaseTwo = true;
                me->NearTeleportTo(_centerOfFightingArea);
                events.Reset();
                uint32 healthToSet = me->GetMaxHealth() * _finalPhaseHealthPercentage;
                me->SetHealth(healthToSet);
                me->MonsterYell("I need your blood!", LANG_UNIVERSAL, nullptr);

                DoCastSelf(SPELL_ENRAGE_VISUAL_SNAKE, true);
                events.ScheduleEvent(EVENT_SNAKE_POTENT_JOLT, 5s);
                events.ScheduleEvent(EVENT_SNAKE_VENOMOUS_BREATH, 10s);
                DoZoneInCombat();
                break;
            }
            case DATA_BEGIN_SNAKE_COMBAT:
            {
                if (me->IsInCombat())
                    return;

                me->SetVisible(true);
                DoZoneInCombat(me, 200.f);
                InitializeMovement();
                if (!me->IsInCombat())
                    EnterEvadeMode();
                scheduler.Schedule(3s, [this](TaskContext /*func*/)
                {
                    if (GameObject* cage = instance->GetGameObject(DATA_GO_BOSS_TWO_CAGE))
                        cage->SetGoState(GO_STATE_READY);
                });
                break;
            }
            default:
                break;
        }
    }

    void JustDied(Unit* killer) override
    {
        if (GameObject * cage = instance->GetGameObject(DATA_GO_BOSS_TWO_CAGE))
            cage->SetGoState(GO_STATE_ACTIVE);
        if (Unit * wanderer = instance->GetCreature(DATA_NPC_WANDERER))
            if (wanderer->IsAIEnabled)
                wanderer->GetAI()->DoAction(ACTION_SNAKE_KILLED);
        CheckCreatureRecord(killer, HELLFORGE_CREATURE_RECORD_MIN_VALUE + 1, RAID_DIFFICULTY_10MAN_NORMAL, "", 1, _fightTimer);
        BossAI::JustDied(killer);
    }

    void JustRespawned() override
    {
        if (Unit * cocoon = instance->GetCreature(DATA_NPC_CHAMPION_COCCON))
            cocoon->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        BossAI::JustRespawned();
    }
private:
    //! GUID of player that are currently sacrificing
    uint64 _sacrificedPlayer;
    bool _phaseTwo;
    bool _altarHasBeenClicked;
    std::vector<Position> _mySoakerSpawnPositions;
    uint32 _blightCrystalDirectDamage;
    uint32 _blightCrystalPeriodicDamage;
    uint32 _venomBreathDamage;
    float _finalPhaseHealthPercentage;
    uint32 _fightTimer;
};

struct npc_boss_two_soaker_AI : public ScriptedAI
{
    npc_boss_two_soaker_AI(Creature* creature) : ScriptedAI(creature)
    {
        _events.Reset();
        HellforgeStatValues val;
        sWorldCache.GetStatValue(BOSS_TWO_STAT_ID_SOAK_EXPLOSION_DAMAGE, val);
        _soakerExplosionDamage = urand((val.StatValue * val.StatVariance), val.StatValue);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        damage = 0;
    }

    void Reset() override
    {
        _events.ScheduleEvent(EVENT_SOAKER_EXPLOSION, 10s);
        me->SetPassive();
        me->CastSpell(me, SPELL_SOAKER_VISUAL_ONE, true);
        me->CastSpell(me, SPELL_SOAKER_VISUAL_TWO, true);
        me->CastSpell(me, SPELL_SOAKER_SLIME_POOL, true);
    }

    void AttackStart(Unit* /*who*/) override { }
    void UpdateAI(uint32 diff) override
    {
        if (_events.Empty())
            return;

        _events.Update(diff);

        if (_events.ExecuteEvent() == EVENT_SOAKER_EXPLOSION)
            ExplodeOrDespawn();
    }

    //! if no players within range, do explode and damage everyone within 100y
    //! else play visuals and despawn
    void ExplodeOrDespawn()
    {
        me->RemoveAllAuras();
        std::list<Player*> _lPlayers;
        float _range = 2.5f;
        Trinity::AnyPlayerInObjectRangeCheck checker(me, _range);
        Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, _lPlayers, checker);
        me->VisitNearbyWorldObject(_range, searcher);

        if (_lPlayers.empty())
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 100000.f);
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, _soakerExplosionDamage);
            val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
            me->CastCustomSpell(SPELL_SOAKER_OOZE_EXPLOSION, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
            me->DespawnOrUnsummon(3s);
        }
        else
        {
            if (me->GetSummoner() && me->GetSummoner()->IsAIEnabled)
                me->GetSummoner()->AI()->SetData(DATA_SOAKER_PREVENTED, DATA_SOAKER_PREVENTED);

            DoCastSelf(SPELL_SOAKER_DESPAWN_VISUAL, true);
            me->DespawnOrUnsummon(4s);
        }
    }
private:
    EventMap _events;
    uint32 _soakerExplosionDamage;
};

struct go_altar_of_sacrifice_hellforge_AI : public GameObjectAI
{
    go_altar_of_sacrifice_hellforge_AI(GameObject* go) : GameObjectAI(go), _instance(go->GetInstanceScript()), _sacrified(false) { }

    void Reset() override
    {
        go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
    }

    void OnUnlockAttempt(SpellCastResult res, Player* player) override
    {
        if (res == SPELL_CAST_OK && player && !_sacrified)
        {
            _sacrified = true;
            _sacrifiedPlayer = player->GetGUID();
            player->CastSpell(player, SPELL_ALTAR_TELEPORT_VISUAL, TRIGGERED_FULL_MASK);

            Creature* snakeBoss = _instance->GetCreature(DATA_BOSS_TWO);

            if (!snakeBoss)
                return;

            snakeBoss->AI()->SetData(DATA_ALTAR_CLICKED, DATA_ALTAR_CLICKED);
            snakeBoss->AI()->SetGUID(player->GetGUID(), DATA_SACRIFICED_PLAYER);

            go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);

            Position pos = go->GetPosition();

            pos.m_positionZ += 10.f;
            player->CastSpell(player, SPELL_EVIL_TELEPORT_HELLFORGE, true);
            player->NearTeleportTo(pos);
            pos.m_positionZ -= 10.f;
            if (Creature* spreader = snakeBoss->SummonCreature(NPC_ADD_FLAME_SPREADER, pos))
                player->CastSpell(spreader, 530, true);

            player->AddAura(SPELL_BOSS_TWO_CRYSTAL_PRISON, player);
            if (Aura* aura = player->GetAura(SPELL_BOSS_TWO_CRYSTAL_PRISON))
            {
                aura->SetMaxDuration(30000);
                aura->RefreshDuration();
            }

            if (InstanceScript* instance = go->GetInstanceScript())
            {
                if (Creature* boss = instance->GetCreature(DATA_BOSS_TWO))
                    boss->AI()->SetData(DATA_ALTAR_ACTIVATED, DATA_ALTAR_ACTIVATED);
            }
        }
    }
private:
    InstanceScript* _instance;
    uint64  _sacrifiedPlayer;
    bool _sacrified;
};

enum BossTwoAdd
{
    SPELL_BOSS_TWO_MOJO_WAVE                = 58993,
    SPELL_BOSS_SPIRIT_FOUNT                 = 59321,
    SPELL_BOSS_CHAOTIC_LIGHT                = 41063,
    SPELL_BOSS_CARRION_SWARM                = 31306
};

struct npc_hellforge_boss_two_add_AI : public ScriptedAI
{
    npc_hellforge_boss_two_add_AI(Creature* creature) : ScriptedAI(creature), _instance(me->GetInstanceScript()), _currentCarrier(0), _summons(me), _exploded(false)
    {
        _spawnInTriggers.reserve(SPAWN_IN_TRIGGERS_SIZE);
        me->SetReactState(REACT_PASSIVE);
        me->SetFlag(UNIT_FIELD_FLAGS, (UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_ATTACKABLE_1));
        _summons.DespawnAll();
        _canRegeneratePower = true;
        ResetPower();
        me->SetFacingTo(me->GetAngle(_centerOfFightingArea.GetPositionX(), _centerOfFightingArea.GetPositionY()));
        _task.CancelAll();
        SpawnVisualTriggers(10.0f);
        _exploded = false;
        LoadBossStats();
    }

    bool CheckEvadeIfOutOfCombatArea() const override
    {
        return me->GetDistance(_centerOfFightingArea) >= 180.f;
    }

    void LoadBossStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ BOSS_TWO_STAT_ID_ADD_HEALTH, BOSS_TWO_STAT_ID_ADD_MELEE_DMG,
            BOSS_TWO_STAT_ID_ENERGY_PER_SOAK, BOSS_TWO_STAT_ID_MOJO_WAVE_DAMAGE, BOSS_TWO_STAT_ID_CHAOTIC_LIGHT });
        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case BOSS_TWO_STAT_ID_ADD_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case BOSS_TWO_STAT_ID_ADD_MELEE_DMG:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case BOSS_TWO_STAT_ID_ENERGY_PER_SOAK:
                {
                    _energyPerSoak = ref.second.StatValue;
                    break;
                }
                case BOSS_TWO_STAT_ID_MOJO_WAVE_DAMAGE:
                {
                    _mojowaveDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_TWO_STAT_ID_CHAOTIC_LIGHT:
                {
                    _chaoticLightDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_TWO_STAT_ID_EXPLODE_PCT:
                {
                    _explodePercentage = ref.second.StatValue;
                    break;
                }
                case BOSS_TWO_STAT_ID_EXPLOSION_DAMAGE:
                {
                    _explosionDamage = ref.second.StatValue;
                    break;
                }
                default:
                    break;
            }
        }
    }

    void JustSummoned(Creature* creature) override
    {
        _summons.Summon(creature);
    }

    void JustDied(Unit* killer) override
    {
        _summons.DespawnAll();
        if (Creature* boss = _instance->GetCreature(DATA_BOSS_TWO))
            boss->AI()->SetData(DATA_ADD_DIED, DATA_ADD_DIED);
        me->MonsterYell("What a shame… God... help us…", LANG_UNIVERSAL, nullptr);
        ScriptedAI::JustDied(killer);
    }

    void EnterEvadeMode() override
    {
        _summons.DespawnAll();
        ScriptedAI::EnterEvadeMode();
    }

    void HandleCrossfire()
    {
        std::vector<Creature*> _triggers;
        for (auto && pos : _crossFireSpawnPositions)
        {
            if (Creature* trigger = me->SummonCreature(NPC_BOSS_TWO_CROSSFIRE_TRIGGERS, pos))
            {
                trigger->DespawnOrUnsummon(20s);
                trigger->SetReactState(REACT_PASSIVE);
                _triggers.emplace_back(trigger);
            }
            else
            {
                std::for_each(_triggers.begin(), _triggers.end(), [](Creature* trigger) { trigger->DespawnOrUnsummon(); });
                break;
            }
        }

        for (auto i = 0; i < _triggers.size(); ++i)
        {
            if (i % 2 == 0)
                continue;

            Creature* _first = _triggers[i - 1];
            Creature* _second = _triggers[i];
            if (_first && _second)
            {
                _first->SetFacingTo(_first->GetAngle(_second->GetPositionX(), _second->GetPositionY()));
                _second->SetFacingTo(_second->GetAngle(_first->GetPositionX(), _first->GetPositionY()));
                _first->CastSpell(_second, 40639, true);
                _second->CastSpell(_first, 40639, true);
            }
        }
    }

    void ResetPower()
    {
        me->setPowerType(POWER_ENERGY);
        me->SetMaxPower(POWER_ENERGY, 100);
        me->SetPower(POWER_ENERGY, 0);
    }

    void HandleTriggerVisuals()
    {
        for (auto && guid : _spawnInTriggers)
        {
            if (Creature* trigger = ObjectAccessor::GetCreature(*me, guid))
                trigger->CastSpell(me, SPELL_BASHIR_SPAWN_IN_HELLFORGE, true);
        }
    }

    void SpawnVisualTriggers(float radius)
    {
        //! Spawn them around the boss, with different PositionZ for additional cool effect
        float angle = 0.f;
        for (uint32 i = 0; i < 32; ++i)
        {
            float posZ = me->GetPositionZ() + frand(5.0f, 20.f);
            float x = me->GetPositionX() + radius * cosf(angle);
            float y = me->GetPositionY() + radius * sinf(angle);
            if (Creature* trigger = me->SummonCreature(NPC_ADD_VISUAL_SPAWN_IN_TRIGGER, { x, y, posZ }, TEMPSUMMON_MANUAL_DESPAWN, 35000))
            {
                _spawnInTriggers.push_back(trigger->GetGUID());
                trigger->SetCanFly(true);
            }

            angle += M_PI / 8;
            if (angle >= 2 * M_PI)
                angle = 0.f;
        }

        //! handle casting visuals at boss, after 10 repetitions despawn them
        //! and creature enters the fight
        _task.Schedule(1s, [this](TaskContext func)
        {
            HandleTriggerVisuals();
            if (func.GetRepeatCounter() < static_cast<uint32>(10))
                func.Repeat(0.5s, 1.1s);
            else
            {
                for (auto && guid : _spawnInTriggers)
                {
                    if (Creature* tri = ObjectAccessor::GetCreature(*me, guid))
                        tri->DespawnOrUnsummon();
                }

                _spawnInTriggers.clear();
                _spawnInTriggers.shrink_to_fit();
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, (UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_ATTACKABLE_1));
                DoZoneInCombat();
                ScheduleCombatEvents();
                me->MonsterYell("Truthless! You will meet our GOD sooner or later!", LANG_UNIVERSAL, nullptr);
            }
        });
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == DATA_SOAKER_PREVENTED && _canRegeneratePower)
        {
            uint32 energy = std::min(100U, me->GetPower(POWER_ENERGY) + _energyPerSoak);
            me->SetPower(POWER_ENERGY, energy);
            if (energy == 100)
            {
                _canRegeneratePower = false;
                HandleCrossfire();
                ResetPower();
                //! for 10 seconds after crossfire boss, cannot get regenerate energy
                _task.Schedule(15s, [&](TaskContext /*func*/) { _canRegeneratePower = true; });
            }
        }
    }

    void ScheduleCombatEvents()
    {
        _task.Schedule(15s, [&](TaskContext func)
        {
            auto repeatTime = 20s;
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U, [&](Unit const* unit)
            {
                return CanAIAttack(unit) && unit->GetDistance(me) <= 65.f && unit->ToPlayer();
            }))
            {
                //! massive workaround to make this work
                //! SPELL_BOSS_CARRION_SWARM is cone spell
                //! and boss won't turn around to target, no matter what kind of core hacks i use :P
                Position pos = me->GetPosition();
                pos.m_orientation = pos.GetAngle(target);
                if (Creature* trigger = me->SummonCreature(WORLD_TRIGGER, pos))
                {
                    CustomSpellValues val;
                    val.AddSpellMod(SPELLVALUE_BASE_POINT0, _mojowaveDamage);
                    trigger->CastCustomSpell(SPELL_BOSS_TWO_MOJO_WAVE, val, target, TRIGGERED_FULL_MASK, NullItemRef, (const AuraEffect*)nullptr, me->GetGUID());
                    trigger->DespawnOrUnsummon(5s);
                    me->MonsterYell("Take this, rats!", LANG_UNIVERSAL, nullptr);
                }
            }
            else
                repeatTime = 5s;

            func.Repeat(repeatTime);
        });

        //! activates on next melee swing
        //! does aoe CONE damage, base radius of 25.f
        _task.Schedule(10s, [&](TaskContext func)
        {
            Unit* victim = me->GetVictim();
            if (victim)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT1, _chaoticLightDamage);
                val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 50000.f);
                me->CastCustomSpell(SPELL_BOSS_CHAOTIC_LIGHT, val, victim);
            }
            func.Repeat(5s, 8s);
        });

        //! Spawn lava gout trigger
        //! all of those explode at 20%
        _task.Schedule(15s, [&](TaskContext func)
        {
            auto repeatTimer = 7s;
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U, 120.f, true))
            {
                _currentCarrier = target->GetGUID();
                me->MonsterWhisper("You're affected by Lava Gout!", target->ToPlayer());
            }
            else
            {
                _currentCarrier = 0;
                repeatTimer = 8s;
            }

            _task.Schedule(5s, [&](TaskContext func)
            {
                if (Player* player = ObjectAccessor::GetPlayer(*me, _currentCarrier))
                {
                    if (Creature* bomb = me->SummonCreature(NPC_ADD_DELAYED_EXPLOSION, player->GetPosition()))
                        //! magic number because MSVC has an issue with lambdas and enums in some specific cases
                        //! this spell is only visual
                        bomb->CastSpell(bomb, /*SPELL_BLOB_SPIRIT_PARTICLES*/43167, true);

                    _currentCarrier = 0;
                }
            });

            func.Repeat(repeatTimer);
        });
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        if (me->HealthBelowPctDamaged(20, damage) && !_exploded)
        {
            _exploded = true;
            HandleExplosion();
        }
    }

    void HandleExplosion()
    {
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_LAVA_GOUT_EXPLOSION);
        if (spellInfo)
        {
            std::list<Creature*> _temp;
            me->GetCreatureListWithEntryInGrid(_temp, NPC_ADD_DELAYED_EXPLOSION, 250.f);

            for (auto const& ref : _temp)
            {
                std::list<Player*> _lPlayers;
                float _range = 6.5f;
                Trinity::AnyPlayerInObjectRangeCheck checker(ref, _range);
                Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(ref, _lPlayers, checker);
                ref->VisitNearbyWorldObject(_range, searcher);

                std::for_each(_lPlayers.begin(), _lPlayers.end(), [&ref, &spellInfo, this](Player* player)
                {
                    Unit::DealDamage(ref, player, _explosionDamage, nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, spellInfo, true);
                });

                ref->RemoveAllAuras();
                ref->CastSpell(ref, SPELL_LAVA_GOUT_EXPLOSION, true);
                ref->DespawnOrUnsummon(2s);
            }
        }

    }

    bool CanAIAttack(Unit const* who) const override
    {
        Creature* boss = _instance->GetCreature(DATA_BOSS_TWO);
        if (!boss)
            return false;

        if (boss->AI()->CheckGUID(who->GetGUID(), DATA_IS_SACRIFIED))
            return false;

        return ScriptedAI::CanAIAttack(who);
    }

    void UpdateAI(uint32 diff) override
    {
        _task.Update(diff);
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
        EnterEvadeIfOutOfCombatArea();
    }

private:
    TaskScheduler _task;
    std::vector<uint64> _spawnInTriggers;
    uint64 _currentCarrier;
    InstanceScript* _instance;
    SummonList _summons;

    bool _canRegeneratePower;
    bool _exploded;
    bool _introInProgress;

    uint32 _energyPerSoak;
    uint32 _mojowaveDamage;
    uint32 _chaoticLightDamage;
    int32 _explodePercentage;
    uint32 _explosionDamage;
};

struct npc_boss_two_crossfire_trigger_AI : public ScriptedAI
{
    npc_boss_two_crossfire_trigger_AI(Creature* creature) : ScriptedAI(creature), instance(me->GetInstanceScript())
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ BOSS_TWO_STAT_ID_CROSSFIRE_RADIUS, BOSS_TWO_STAT_ID_CROSSFIRE_DAMAGE });
        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case BOSS_TWO_STAT_ID_CROSSFIRE_RADIUS:
                {
                    _crossfireRadius = ref.second.StatVariance;
                    break;
                }
                case BOSS_TWO_STAT_ID_CROSSFIRE_DAMAGE:
                {
                    _holyboltDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
            }
        }

        _scheduler.CancelAll();
        _scheduler.Schedule(5s, [&](TaskContext /*context*/)
        {
            auto& _players = me->GetMap()->GetPlayers();
            for (auto && source : _players)
            {
                Player* player = source.GetSource();
                if (!player)
                    continue;

                if (player->IsGameMaster())
                    continue;

                if (me->HasInLine(player, _crossfireRadius))
                {
                    CustomSpellValues val;
                    val.AddSpellMod(SPELLVALUE_BASE_POINT0, _holyboltDamage);
                    me->CastCustomSpell(SPELL_CROSSFIRE_HOLY_BOLT, val, player, TRIGGERED_FULL_MASK, NullItemRef, (const AuraEffect*)nullptr, instance->GetCreature(DATA_BOSS_TWO)->GetGUID());
                }
            }

            me->DespawnOrUnsummon(1s);
        });
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        damage = 0;
    }

    void AttackStart(Unit* /*attacker*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void UpdateAI(uint32 diff) override { _scheduler.Update(diff); }

private:
    TaskScheduler _scheduler;
    InstanceScript* instance;
    float _crossfireRadius;
    uint32 _holyboltDamage;
};

//! Unused currently, saving it as we might use it afterall later on
//enum FloatingBlob
//{
//    SPELL_BLOB_MAGNETO_SPHERE                = 37830,
//    SPELL_BLOB_SPIRIT_PARTICLES              = 43167,
//    SPELL_BLOB_GREEN_CRYSTAL_BEAM            = 44808,
//    SPELL_BLOB_SPIRIT_FOUNT                  = 59321,
//
//    TASK_GROUP_FOUNT                         = 10
//};
//
//struct npc_boss_two_floating_blob_AI : public ScriptedAI
//{
//    npc_boss_two_floating_blob_AI(Creature* creature) : ScriptedAI(creature)\
//    {
//        _task.CancelAll();
//        currentTarget = 0;
//        me->SetDisableGravity(true);
//        me->SetHover(true);
//    }
//
//    void Reset() override
//    {
//        _task.CancelAll();
//        _task.Schedule(3s, [&](TaskContext func)
//        {
//            //! Remove task that handles dealing damage (SPELL_BLOB_SPIRIT_FOUNT)
//            _task.CancelGroup(TASK_GROUP_FOUNT);
//            //! Check previous target, if exists
//            if (Player* player = ObjectAccessor::GetPlayer(*me, currentTarget))
//            {
//                player->RemoveAurasDueToSpell(SPELL_BLOB_GREEN_CRYSTAL_BEAM);
//                currentTarget = 0;
//            }
//
//            //! We need boss pointer to check whether player is currently sacrificed
//            //! since we do not want to follow said player
//            Creature* boss{ nullptr };
//            if (InstanceScript* instance = me->GetInstanceScript())
//                boss = instance->GetCreature(DATA_BOSS_TWO);
//
//            std::vector<uint64> _possibleTargets;
//            auto _players = me->GetMap()->GetPlayers();
//            std::for_each(_players.begin(), _players.end(), [&](MapReference ref)
//            {
//                if (Player* player = ref.GetSource())
//                {
//                    if (boss && !boss->AI()->CheckGUID(player->GetGUID(), DATA_IS_SACRIFIED) &&
//                        player->IsWithinBox(_centerOfFightingArea, 15.f, 35.f, 10.f) &&
//                        player->IsAlive())
//                        _possibleTargets.push_back(player->GetGUID());
//                }
//            });
//
//            if (!_possibleTargets.empty())
//                DoFollowVictim(Trinity::Containers::SelectRandomContainerElement(_possibleTargets));
//            func.Repeat(30s);
//        });
//    }
//
//    //! this one never dies
//    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*eff*/, SpellSchoolMask /*mask*/) override { damage = 0; }
//
//    void DoFollowVictim(uint64 guid)
//    {
//        if (Player* player = ObjectAccessor::GetPlayer(*me, guid))
//        {
//            me->CastSpell(me, SPELL_BLOB_MAGNETO_SPHERE, true);
//            me->CastSpell(player, SPELL_BLOB_GREEN_CRYSTAL_BEAM, true);
//            me->SetWalk(true);
//            me->GetMotionMaster()->MoveChase(player);
//
//            _task.Schedule(2s, TASK_GROUP_FOUNT, [&](TaskContext func)
//            {
//                me->CastSpell(nullptr, SPELL_BLOB_SPIRIT_FOUNT, TRIGGERED_FULL_MASK);
//                func.Repeat(2s, 2.5s);
//            });
//        }
//    }
//
//    void UpdateAI(uint32 diff) override { _task.Update(diff); }
//    void AttackStart(Unit* /*who*/) override { }
//    void EnterCombat(Unit* /*who*/) override { }
//private:
//    TaskScheduler _task;
//    uint64 currentTarget;
//};

class spell_surge_of_power_periodic_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_surge_of_power_periodic_AuraScript);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (GetCaster()->GetMapId() == HELLFORGE_MAP_ID)
            PreventDefaultAction();
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_surge_of_power_periodic_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

struct npc_add_poison_spreader_AI : public ScriptedAI
{
    npc_add_poison_spreader_AI(Creature * creature) : ScriptedAI(creature), _failCounter(0), pos(me->GetPosition()), charmerGUID(0)
    {
        HellforgeStatValues val;
        sWorldCache.GetStatValue(BOSS_TWO_STAT_ID_DISTANCE_FROM_POSITION, val);
        _distanceFromPosition = val.StatVariance;

        me->SetImmuneToAll(true);
        _task.CancelAll();
        _task.Schedule(7s, [&](TaskContext func)
        {
            Player* player = me->GetCharmerOrOwnerPlayerOrPlayerItself();
            if (player && !charmerGUID)
                charmerGUID = player->GetGUID();
            //! if player didnt move from home pos, on top of a toxic waste
            //! for specific times, we kill the player
            if (me->GetDistance(pos) <= _distanceFromPosition)
            {
                if (player)
                {
                    if (_failCounter >= 3)
                    {
                        Unit::Kill(me, player);
                    }
                    else
                        me->MonsterWhisper("You have to move!", player);
                }

                ++_failCounter;
            }

            // set new position
            pos = me->GetPosition();

            if (player && me->GetInstanceScript())
            {
                if (Creature* boss = me->GetInstanceScript()->GetCreature(DATA_BOSS_TWO))
                {
                    if (Creature* hitTarget = boss->SummonCreature(NPC_ADD_FLAME_HIT_TARGET, me->GetPosition()))
                    {
                        hitTarget->SetReactState(REACT_PASSIVE);
                        hitTarget->DespawnOrUnsummon(10s);
                        hitTarget->setFaction(player->getFaction());

                        if (Creature* caster = player->FindNearestCreature(NPC_ADD_FLAME_SPREADER_CASTER, 100.f))
                        {
                            caster->setFaction(boss->getFaction());
                            caster->CastSpell(hitTarget, SPELL_ALTAR_TOXIC_WASTE, true);
                        }
                    }
                }

                if (func.GetRepeatCounter() >= 4)
                    me->DespawnOrUnsummon();
                else
                    func.Repeat(5s);
            }
        });
    }

    void UpdateAI(uint32 diff) override { _task.Update(diff); }
    void EnterEvadeMode() override { }
    void OnCharmed(bool apply) override
    {
        if (!apply)
        {
            if (InstanceScript* instance = me->GetInstanceScript())
            {
                if (Creature* boss = instance->GetCreature(DATA_BOSS_TWO))
                    boss->AI()->SetGUID(charmerGUID, DATA_FINISH_SACRIFICE);
            }
            me->DespawnOrUnsummon();
        }
    }
    void AttackStart(Unit* /*attacker*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void Reset() override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        damage = 0;
    }
private:
    TaskScheduler _task;
    Position pos;
    uint16 _failCounter;
    uint64 charmerGUID;
    float _distanceFromPosition;
};

class spell_boss_two_crystal_prison_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_boss_two_crystal_prison_AuraScript);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetTarget())
        {
            if (InstanceScript* instance = GetTarget()->GetInstanceScript())
            {
                if (Creature* boss = instance->GetCreature(DATA_BOSS_TWO))
                    boss->AI()->SetGUID(GetTarget()->GetGUID(), DATA_FINISH_SACRIFICE);
            }
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_boss_two_crystal_prison_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE_PERCENT, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_boss_two_blight_crystal_damage : public SpellScriptLoader
{
public:
    spell_boss_two_blight_crystal_damage() : SpellScriptLoader("spell_boss_two_blight_crystal_damage") { }

    class spell_boss_two_blight_crystal_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_boss_two_blight_crystal_damage_SpellScript);

        void HandleHit(SpellEffIndex /*eff*/)
        {
            if (GetCaster() && GetCaster()->ToCreature() && GetCaster()->GetMapId() == HELLFORGE_MAP_ID)
            {
                auto _damage = GetCaster()->ToCreature()->AI()->GetData(BOSS_TWO_STAT_ID_BLIGHT_CRYSTAL_DMG);
                SetHitDamage(_damage);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_boss_two_blight_crystal_damage_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    class spell_boss_two_blight_crystal_damage_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_boss_two_blight_crystal_damage_AuraScript);

        void OnPeriodic(AuraEffect const* aurEff)
        {
            if (GetAura() && GetAura()->GetEffect(aurEff->GetEffIndex()) && GetCaster())
            {
                auto _damage = aurEff->GetAmount();
                if (GetCaster()->GetMapId() == HELLFORGE_MAP_ID && GetCaster()->ToCreature())
                    _damage = GetCaster()->ToCreature()->AI()->GetData(BOSS_TWO_STAT_ID_BLIGHT_CRYSTAL_PERIODIC);

                GetAura()->GetEffect(aurEff->GetEffIndex())->SetAmount(_damage);
            }
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_boss_two_blight_crystal_damage_AuraScript::OnPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_boss_two_blight_crystal_damage_SpellScript();
    }

    AuraScript* GetAuraScript() const override
    {
        return new spell_boss_two_blight_crystal_damage_AuraScript();
    }
};

struct go_gong_of_boss_two : public GameObjectAI
{
    go_gong_of_boss_two(GameObject* go) : GameObjectAI(go)
    {
        go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
    }

    bool GossipHello(Player* player, bool /*reportUse*/) override
    {
        if (InstanceScript* instance = go->GetInstanceScript())
        {
            if (Creature* snake = instance->GetCreature(DATA_BOSS_TWO))
            {
                if (!snake->IsVisible() && snake->IsAlive())
                {
                    snake->AI()->SetData(DATA_BEGIN_SNAKE_COMBAT, DATA_BEGIN_SNAKE_COMBAT);
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                }
            }
        }

        return false;
    }
};

void AddSC_hellforge_boss_two()
{
    new spell_boss_two_blight_crystal_damage();

    new AuraScriptLoaderEx<spell_surge_of_power_periodic_AuraScript>("spell_surge_of_power_periodic");
    new AuraScriptLoaderEx<spell_boss_two_crystal_prison_AuraScript>("spell_boss_two_crystal_prison");

    new GameObjectAILoader<go_altar_of_sacrifice_hellforge_AI>("go_altar_of_sacrifice_hellforge");
    new GameObjectAILoader<go_gong_of_boss_two>("go_gong_of_boss_two");

    new CreatureAILoader<npc_boss_two_crossfire_trigger_AI>("npc_boss_two_crossfire_trigger");
    new CreatureAILoader<npc_hellforge_boss_two_add_AI>("npc_hellforge_boss_two_add");
    new CreatureAILoader<npc_boss_two_soaker_AI>("npc_boss_two_soaker");
    new CreatureAILoader<boss_hellforge_boss_two_AI>("boss_hellforge_boss_two");
    new CreatureAILoader<npc_add_poison_spreader_AI>("npc_add_poison_spreader");
}
