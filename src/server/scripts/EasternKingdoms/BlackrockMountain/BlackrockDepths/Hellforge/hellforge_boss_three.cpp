#include "hellforge.hpp"

constexpr uint32 PLAYER_POSITIONS_SIZE{ 10 };
const std::array<Position const, PLAYER_POSITIONS_SIZE> _playerPositions
{
    {
        { 1263.138f, -219.382f, -85.67368f, 0.f },
        { 1259.325f, -211.603f, -85.67368f, 0.f },
        { 1258.283f, -218.461f, -85.67368f, 0.f },
        { 1253.536f, -214.152f, -85.67368f, 0.f },
        { 1252.200f, -220.856f, -85.67368f, 0.f },
        { 1241.798f, -233.530f, -85.67368f, 0.f },
        { 1235.436f, -235.864f, -85.67368f, 0.f },
        { 1235.767f, -231.226f, -85.67368f, 0.f },
        { 1238.862f, -226.343f, -85.67368f, 0.f },
        { 1243.888f, -227.128f, -85.67368f, 0.f }
    }
};

constexpr uint32 INITIAL_TORNADO_SPAWN_POSITION_SIZE{ 4 };
const std::array<Position const, INITIAL_TORNADO_SPAWN_POSITION_SIZE> _initialTornadoPositions
{
    {
        { 1222.798f, -249.943f, -81.05050f, 0.781f },
        { 1211.379f, -220.732f, -81.05036f, 0.003f },
        { 1245.953f, -185.845f, -81.04958f, 4.708f },
        { 1274.793f, -197.315f, -81.05134f, 4.079f }
    }
};

constexpr uint32 ADDITIONAL_TORNADO_SPAWN_POSITION_SIZE{ 11 };
const std::array<Position const, ADDITIONAL_TORNADO_SPAWN_POSITION_SIZE> _additionalTornadoPositions
{
    {
        { 1222.547f, -232.854f, -85.67355f, 0.503f },
        { 1232.852f, -207.752f, -85.67355f, 5.424f },
        { 1257.162f, -197.992f, -85.67355f, 4.360f },
        { 1291.528f, -253.817f, -73.59689f, 3.158f },
        { 1282.652f, -268.375f, -78.21836f, 3.064f },
        { 1284.201f, -285.384f, -73.59647f, 2.451f },
        { 1233.308f, -295.509f, -73.59544f, 0.723f },
        { 1260.782f, -274.256f, -78.21806f, 1.772f },
        { 1268.360f, -271.950f, -78.21806f, 1.941f },
        { 1276.515f, -264.330f, -78.21806f, 2.329f },
        { 1281.259f, -253.923f, -78.07471f, 2.738f }
    }
};

const Position _championPosition = { 1244.52f, -210.56f, -85.67f, 5.22f };

Position const CenterOfTheRoom{ 1256.593f, -233.735f, -85.673f };

constexpr uint32 SIMON_MAX_ROUNDS{ 12 };

enum BossThreeEvents
{
    //! add check for players during normal phase
    EVENT_SIMON_SAYS                            = 1,
    EVENT_SIMON_SLAYS,
    EVENT_SIMON_BEGIN_COMBAT,
    EVENT_SPAWN_TORNADO,
    EVENT_SPAWN_SAND_TRAP_VISUAL,
    EVENT_SPAWN_SAND_TRAP,
    EVENT_PETRIFIED_BARK,
    EVENT_ARCTIC_WINDS,
    EVENT_CHECK_ALIVE_PLAYERS,
};

enum BossThreeSpells
{
    SPELL_COSMETIC_FREEZE_ANIM_STUN         = 52656,
    SPELL_GREEN_GHOST_VISUAL                = 25039,
    SPELL_SAND_STORM_BOSS_THREE             = 25160,
    SPELL_BOSS_THREE_PETRIFIED_BARK         = 62933,
    SPELL_BOSS_THREE_HOLY_MOUNT_VISUAL      = 31726,
    SPELL_BOSS_THREE_ARCTIC_WINDS           = 52814,
    SPELL_BOSS_THREE_TORNADO_HARSH_WINDS    = 10093,
    SPELL_BOSS_THREE_STARFIRE               = 75332
};

enum BossThreeNPCs
{
    NPC_BOSS_THREE_TORNADO                  = 250016
};

enum BossThreeMisc
{
    POINT_MOVE_TO_PLAYER_POSITION           = 1,
    DATA_SANDSTORM_BEGIN_MOVE,


    GO_BOSS_THREE_SAND_TRAP                 = 180647,
    BOSS_PHASE_TWO_WEAPON_ID                = 33214
};

enum BossThreeStats
{
    BOSS_THREE_STAT_ID_MAX_HEALTH           = 25,
    BOSS_THREE_STAT_ID_MELEE_DAMAGE         = 26,
    BOSS_THREE_STAT_ID_PETR_BARK_CHARGES    = 27,
    BOSS_THREE_STAT_ID_ARCTIC_WIND_DMG      = 28,
    BOSS_THREE_TORNADO_DAMAGE               = 73,
    BOSS_THREE_SAND_TRAP_DAMAGE             = 74,
    BOSS_THREE_STAT_ID_SLAY_TIMER           = 80
};

struct boss_hellforge_boss_three_AI : public BossAI
{
    boss_hellforge_boss_three_AI(Creature* creature) : BossAI(creature, DATA_BOSS_THREE), _emoteMap(_emoteList) { }

    void ScheduleCombatEvents()
    {
        events.ScheduleEvent(EVENT_SPAWN_TORNADO, 5s);
        events.ScheduleEvent(EVENT_SPAWN_SAND_TRAP_VISUAL, 10s, 20s);
        events.ScheduleEvent(EVENT_PETRIFIED_BARK, 11s, 17s);
        events.ScheduleEvent(EVENT_ARCTIC_WINDS, 2s);
        events.ScheduleEvent(EVENT_CHECK_ALIVE_PLAYERS, 10s);
    }

    void SpawnInitialTornados()
    {
        std::for_each(_initialTornadoPositions.begin(), _initialTornadoPositions.end(), [&](Position pos)
        {
            if (Creature* tornado = me->SummonCreature(NPC_BOSS_THREE_TORNADO, pos))
                tornado->SetPassive();
        });
    }

    void TeleportPlayersToStartingPositions()
    {
        auto& threatList = me->getThreatManager().getThreatList();
        uint16 index = 0;
        std::for_each(threatList.begin(), threatList.end(), [&](HostileReference* ref)
        {
            if (Unit* owner = ObjectAccessor::GetUnit(*me, ref->getUnitGuid()))
            {
                if (Player* player = owner->ToPlayer())
                {
                    if (player->GetDistance(me) <= 100.f && !player->IsGameMaster())
                    {
                        player->CastSpell(player, SPELL_EVIL_TELEPORT_HELLFORGE, true);
                        player->CastSpell(player, SPELL_COSMETIC_FREEZE_ANIM_STUN, true);
                        player->CastSpell(player, SPELL_GREEN_GHOST_VISUAL, true);

                        Position pos = _playerPositions[index];
                        pos.SetOrientation(pos.GetAngle(me->GetPositionX(), me->GetPositionY()));
                        player->NearTeleportTo(pos);
                        index = std::min(uint16(_playerPositions.size() - 1), uint16(++index));
                    }
                }
            }
        });

        if (Unit * champion = instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
        {
            if (champion->IsAIEnabled && champion->GetAI()->GetData(0) == STATE_FREED)
            {
                champion->NearTeleportTo(_championPosition);
                champion->CastSpell(champion, SPELL_EVIL_TELEPORT_HELLFORGE, true);
                champion->CastSpell(champion, SPELL_COSMETIC_FREEZE_ANIM_STUN, true);
                champion->CastSpell(champion, SPELL_GREEN_GHOST_VISUAL, true);
                champion->setFaction(250);
                champion->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
            }
        }

    }

    void EnterEvadeMode() override
    {
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_COSMETIC_FREEZE_ANIM_STUN);
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_GREEN_GHOST_VISUAL);

        if (Unit * champion = instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
        {
            if (champion->IsAIEnabled && champion->GetAI()->GetData(0) == STATE_FREED)
            {
                champion->RemoveAurasDueToSpell(SPELL_COSMETIC_FREEZE_ANIM_STUN);
                champion->RemoveAurasDueToSpell(SPELL_GREEN_GHOST_VISUAL);

                champion->NearTeleportTo(1250.13f, -284.04f, -78.21f, 1.25f);
                champion->setFaction(35);
                champion->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
            }
        }

        for (auto && go : _traps)
        {
            if (GameObject* trap = ObjectAccessor::GetGameObject(*me, go))
                trap->RemoveFromWorld();
        }
        _traps.clear();
        _traps.shrink_to_fit();
        BossAI::EnterEvadeMode();
    }

    void Reset() override
    {
        _additionalTornadoPosIndex = 0;
        _questionPhase = true;
        _round = 0;
        _savedPlayers.clear();
        BossAI::Reset();
        LoadBossStats();
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 0);
        _fightTimer = 0;
    }

    void HandleRequiredBossFail() override
    {
        auto const& players = me->GetMap()->GetPlayers();
        for (auto const& player : players)
            if (Player* _player = player.GetSource())
                if (_player->IsAlive() && _player->GetDistance(me) <= 100.f && !_player->IsGameMaster())
                    Unit::Kill(me, _player, true);
        EnterEvadeMode();
    }

    void LoadBossStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ BOSS_THREE_STAT_ID_MAX_HEALTH, BOSS_THREE_STAT_ID_MELEE_DAMAGE,
            BOSS_THREE_STAT_ID_PETR_BARK_CHARGES, BOSS_THREE_STAT_ID_ARCTIC_WIND_DMG, BOSS_THREE_STAT_ID_SLAY_TIMER });
        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case BOSS_THREE_STAT_ID_MAX_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case BOSS_THREE_STAT_ID_MELEE_DAMAGE:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case BOSS_THREE_STAT_ID_PETR_BARK_CHARGES:
                {
                    _petrifiedCharges = ref.second.StatValue;
                    break;
                }
                case BOSS_THREE_STAT_ID_ARCTIC_WIND_DMG:
                {
                    _arcticWindsDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_THREE_STAT_ID_SLAY_TIMER:
                {
                    _slayTimer = ref.second.StatValue;
                    break;
                }
                default:
                    break;
            }
        }
    }

    void AttackStart(Unit* who) override
    {
        if (!_questionPhase)
            BossAI::AttackStart(who);
        else
            me->Attack(who, false);
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
        if (me->IsInCombat())
        {
            if (!_questionPhase)
                DoZoneInCombat(summon, 200.f);
        }
    }

    void EnterCombat(Unit* who) override
    {
        if (!instance->CheckRequiredBosses(DATA_BOSS_THREE))
        {
            HandleRequiredBossFail();
            return;
        }

        _fightTimer = getMSTime();
        BossAI::EnterCombat(who);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->MonsterYell("HA! Got ya, let's play a game, shall we?", LANG_UNIVERSAL, nullptr);
        events.ScheduleEvent(EVENT_SIMON_SAYS, 5s);
        TeleportPlayersToStartingPositions();
        SpawnInitialTornados();
    }

    void ReceiveEmote(Player* player, uint32 emoteId) override
    {
        if (emoteId == _currentRequiredEmote)
            _savedPlayers.insert(player->GetGUID());
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SIMON_BEGIN_COMBAT:
                {
                    for (auto && i : summons)
                    {
                        if (Creature* summon = ObjectAccessor::GetCreature(*me, i))
                        {
                            summon->SetAggressive();
                            if (summon->IsAIEnabled)
                            {
                                summon->AI()->SetData(DATA_SANDSTORM_BEGIN_MOVE, DATA_SANDSTORM_BEGIN_MOVE);
                                summon->AI()->DoZoneInCombat(summon, 150.f);
                            }
                        }
                    }

                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    _questionPhase = false;
                    me->AttackStop();
                    ScheduleCombatEvents();
                    instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_COSMETIC_FREEZE_ANIM_STUN);
                    instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_GREEN_GHOST_VISUAL);

                    if (Unit * champion = instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
                    {
                        if (champion->IsAIEnabled && champion->GetAI()->GetData(0) == STATE_FREED)
                        {
                            champion->RemoveAurasDueToSpell(SPELL_COSMETIC_FREEZE_ANIM_STUN);
                            champion->RemoveAurasDueToSpell(SPELL_GREEN_GHOST_VISUAL);
                            champion->Attack(me, false);
                        }
                    }

                    DoZoneInCombat();
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, BOSS_PHASE_TWO_WEAPON_ID);
                    break;
                }
                case EVENT_SIMON_SAYS:
                {
                    if (_round > SIMON_MAX_ROUNDS)
                    {
                        events.ScheduleEvent(EVENT_SIMON_BEGIN_COMBAT, 2s);
                        break;
                    }
                    _savedPlayers.clear();
                    auto iterator = std::next(_emoteMap.begin(), urand(0, _emoteMap.size() - 1));
                    _currentRequiredEmote = iterator->first;
                    me->MonsterYell(iterator->second.c_str(), 0, nullptr);
                    events.ScheduleEvent(EVENT_SIMON_SLAYS, std::chrono::milliseconds(_slayTimer));
                    //events.ScheduleEvent(EVENT_WANDERER_RESPONSE, 2.5s); ToDo
                    ++_round;
                    break;
                }
                case EVENT_SIMON_SLAYS:
                {
                    auto& threatList = me->getThreatManager().getThreatList();
                    std::for_each(threatList.begin(), threatList.end(), [&](HostileReference* ref)
                    {
                        Unit* who = ObjectAccessor::GetUnit(*me, ref->getUnitGuid());
                        if (who && who->ToPlayer())
                        {
                            if (_savedPlayers.find(who->GetGUID()) == _savedPlayers.end())
                            {
                                Position spawnPos;

                                //! out of bounds, choose whatever and calculate nearby position
                                if (_additionalTornadoPosIndex >= ADDITIONAL_TORNADO_SPAWN_POSITION_SIZE)
                                    spawnPos = me->GetNearPositionFromPos(Trinity::Containers::SelectRandomContainerElement(_additionalTornadoPositions), 3.0f);
                                else
                                    spawnPos = _additionalTornadoPositions[_additionalTornadoPosIndex];

                                if (Creature* tornado = me->SummonCreature(NPC_BOSS_THREE_TORNADO, spawnPos))
                                    tornado->SetPassive();

                                ++_additionalTornadoPosIndex;
                                me->CastCustomSpell(SPELL_BOSS_THREE_STARFIRE, SPELLVALUE_BASE_POINT0, 0, who, TRIGGERED_FULL_MASK);
                            }
                        }
                    });

                    std::ostringstream stream;
                    stream << "N";
                    for (uint32 i = 0; i < _round; ++i)
                        stream << "E";
                    stream << "XT!";
                    me->MonsterYell(stream.str().c_str(), LANG_UNIVERSAL, nullptr);
                    events.ScheduleEvent(EVENT_SIMON_SAYS, 3s);
                    break;
                }
                case EVENT_SPAWN_TORNADO:
                {
                    if (Creature* tornado = me->SummonCreature(NPC_BOSS_THREE_TORNADO, Trinity::Containers::SelectRandomContainerElement(_additionalTornadoPositions)))
                        tornado->AI()->SetData(DATA_SANDSTORM_BEGIN_MOVE, DATA_SANDSTORM_BEGIN_MOVE);
                    events.Repeat(30s);
                    break;
                }
                case EVENT_SPAWN_SAND_TRAP_VISUAL:
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.f, true))
                    {
                        _sandTrapSpawnPosition = target->GetPosition();
                        target->CastSpell(target, SPELL_BOSS_THREE_HOLY_MOUNT_VISUAL, true);
                        events.ScheduleEvent(EVENT_SPAWN_SAND_TRAP, 5s);
                    }
                    events.Repeat(15s, 25s);
                    break;
                }
                case EVENT_SPAWN_SAND_TRAP:
                {
                    if (GameObject* sandTrap = me->SummonGameObject(GO_BOSS_THREE_SAND_TRAP, _sandTrapSpawnPosition, 0.f, 0.f, 0.f, 0.f, 0))
                        _traps.push_back(sandTrap->GetGUID());
                    break;
                }
                case EVENT_PETRIFIED_BARK:
                {
                    DoCastSelf(SPELL_BOSS_THREE_PETRIFIED_BARK, true);
                    if (Aura* aura = me->GetAura(SPELL_BOSS_THREE_PETRIFIED_BARK))
                        aura->SetCharges(_petrifiedCharges);
                    events.Repeat(30s);
                    break;
                }
                case EVENT_ARCTIC_WINDS:
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 30.f, true))
                    {
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_BASE_POINT0, _arcticWindsDamage);
                        me->CastCustomSpell(SPELL_BOSS_THREE_ARCTIC_WINDS, val, target, TRIGGERED_FULL_MASK);
                    }
                    events.Repeat(10s);
                    break;
                }
                case EVENT_CHECK_ALIVE_PLAYERS:
                {
                    bool evade = true;
                    auto& threatList = me->getThreatManager().getThreatList();
                    for (auto && ref : threatList)
                    {
                        Unit* target = ref->getTarget();
                        if (!target)
                            continue;

                        if (!target->IsPlayer() || target->ToPlayer()->IsGameMaster())
                            continue;

                        if (target->IsAlive() && target->IsWithinDistInMap(me, 150.f))
                        {
                            evade = false;
                            break;
                        }
                    }

                    if (evade)
                        EnterEvadeMode();
                    events.Repeat(10s);
                    break;
                }
                default:
                    break;
            }
        }

        if (!_questionPhase)
            DoMeleeAttackIfReady();
        EnterEvadeIfOutOfCombatArea();
    }

    bool CheckEvadeIfOutOfCombatArea() const override
    {
        return me->GetDistance(me->GetHomePosition()) >= 100.f;
    }

    void JustDied(Unit* killer) override
    {
        if (Unit * champion = instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
        {
            if (champion->IsAIEnabled && champion->GetAI()->GetData(0) == STATE_FREED)
            {
                champion->setFaction(35);
                champion->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                champion->GetAI()->DoAction(ACTION_SIMON_KILLED);
                champion->SetFullHealth();
            }
        }

        me->MonsterYell("Ahhhh, what a beautiful game it was..", LANG_UNIVERSAL, nullptr);
        CheckCreatureRecord(killer, HELLFORGE_CREATURE_RECORD_MIN_VALUE + 2, RAID_DIFFICULTY_10MAN_NORMAL, "", 1, _fightTimer);
        BossAI::JustDied(killer);
    }

private:
    bool _questionPhase;
    uint16 _currentRequiredEmote;
    uint16 _round;
    std::set<uint64> _savedPlayers;
    std::unordered_map<uint32, std::string> _emoteMap;
    uint16 _additionalTornadoPosIndex;
    Position _sandTrapSpawnPosition;
    std::vector<uint64> _traps;

    uint32 _petrifiedCharges;
    uint32 _arcticWindsDamage;
    uint32 _slayTimer;
    uint32 _fightTimer;
};

struct npc_boss_three_tornado_AI : public ScriptedAI
{
    npc_boss_three_tornado_AI(Creature* creature) : ScriptedAI(creature), _previousMoveTarget(0)
    {
        HellforgeStatValues stat;
        sWorldCache.GetStatValue(BOSS_THREE_TORNADO_DAMAGE, stat);
        _tornadoDamage = stat.StatValue;
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type != DATA_SANDSTORM_BEGIN_MOVE)
            return;

        _task.Schedule(3s, [&](TaskContext func)
        {
            std::vector<uint64> _possibleTargets;
            auto& playerList = me->GetMap()->GetPlayers();
            for (auto && ref : playerList)
            {
                Player* player = ref.GetSource();
                if (!player)
                    continue;

                if (player->GetGUID() == _previousMoveTarget)
                    continue;

                if (player->IsGameMaster())
                    continue;

                _possibleTargets.push_back(player->GetGUID());
            }

            _previousMoveTarget = 0;
            if (!_possibleTargets.empty())
            {
                if (Player* player = ObjectAccessor::GetPlayer(*me, Trinity::Containers::SelectRandomContainerElement(_possibleTargets)))
                {
                    _previousMoveTarget = player->GetGUID();
                    me->GetMotionMaster()->MovePoint(POINT_MOVE_TO_PLAYER_POSITION, player->GetPosition());
                }
            }

            func.Repeat(10s);
        });

        _task.Schedule(6s, [&](TaskContext func)
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
            val.AddSpellMod(SPELLVALUE_BASE_POINT2, _tornadoDamage);
            me->CastCustomSpell(SPELL_BOSS_THREE_TORNADO_HARSH_WINDS, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
            func.Repeat(2s, 3s);
        });
    }

    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        damage = 0;
    }

    void UpdateAI(uint32 diff) override
    {
        _task.Update(diff);
    }

    bool CanAIAttack(Unit const* victim) const override
    {
        return victim->GetEntry() == NPC_WANDERER_CHAMPION ? false : ScriptedAI::CanAIAttack(victim);
    }
private:
    TaskScheduler _task;
    uint64 _previousMoveTarget;
    uint32 _tornadoDamage;
};

class spell_hellforge_sandtrap : public SpellScript
{
    PrepareSpellScript(spell_hellforge_sandtrap);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (GetCaster() && GetCaster()->GetMapId() == HELLFORGE_MAP_ID)
        {
            HellforgeStatValues val;
            sWorldCache.GetStatValue(BOSS_THREE_SAND_TRAP_DAMAGE, val);
            SetEffectValue(val.StatValue);
        }
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_hellforge_sandtrap::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_hellforge_boss_three()
{
    new CreatureAILoader<boss_hellforge_boss_three_AI>("boss_hellforge_boss_three");
    new CreatureAILoader<npc_boss_three_tornado_AI>("npc_boss_three_tornado");

    new SpellScriptLoaderEx<spell_hellforge_sandtrap>("spell_hellforge_sandtrap");
}
