#include "hellforge.hpp"

#include "Group.h"

Position const _gargoyleSpawnPos{ 1104.572f, -252.234f, -48.04752f, 2.191f };
Position const _entranceSpawnPosition{ 1075.500f, -175.851f, -65.245f, 4.069f };
Position const _exitSpawnPosition{ 1045.127f, -207.909f, -61.849f, 0.809f };
constexpr uint32 GARGOYLE_MOVE_POS_SIZE{ 10 };

const std::array<Position, GARGOYLE_MOVE_POS_SIZE> _gargoyleMovePosition
{ {
    { 1085.441040f, -202.515045f, -53.996468f, 2.250942f },
    { 1072.987671f, -205.589783f, -50.605709f, 2.274504f },
    { 1067.412598f, -209.646896f, -50.605709f, 2.199892f },
    { 1060.766724f, -215.694778f, -56.327633f, 1.771850f },
    { 1072.630127f, -215.391129f, -60.905781f, 2.180257f },
    { 1084.969238f, -208.787170f, -61.451782f, 2.298067f },
    { 1092.163940f, -199.647461f, -61.451782f, 3.067757f },
    { 1090.858398f, -216.553406f, -55.073666f, 2.396240f },
    { 1081.992920f, -224.105759f, -55.073666f, 2.148840f },
    { 1070.073242f, -230.373749f, -55.073666f, 1.866096f }
} };

enum GauntletCreatures
{
    NPC_HELLFORGE_GARGOYLE                      = 250020,
    NPC_HELLFORGE_ZOMBIE                        = 250021,
    NPC_HELLFORGE_GHOUL                         = 250022
};

enum GauntletData
{
    DATA_CHARGE_TARGET_GUID                     = 1
};

enum GauntletControllerSpells
{
    SPELL_GAUNTLET_EVIDENCE_MARKER              = 42171
};

enum GauntletMisc
{
    SPELL_BLOODY_GARGOYLE_SHADOW_BOLT           = 17509,
    SPELL_RISEN_WITCH_DOCTOR_SPAWN              = 69639,

    STAT_ID_EMPOWERED_SHOCKWAVE_DAMAGE          = 68,
    STAT_ID_GARGOYLE_MAX_HEALTH                 = 69,
    STAT_ID_GARGOYLE_SHADOWBOLT_DAMAGE          = 70,
    STAT_ID_RISEN_MADMAN_MAX_HEALTH             = 71,
    STAT_ID_RISEN_MADMAN_MELEE_DAMAGE           = 72
};

class StartMovementEvent : public BasicEvent
{
public:
    StartMovementEvent(Creature* summoner, Creature* owner) : _summoner(summoner), _owner(owner) {}

    bool Execute(uint64 /*time*/, uint32 /*diff*/)
    {
        _owner->SetReactState(REACT_AGGRESSIVE);
        if (!_owner->getThreatManager().isThreatListEmpty())
            if (Unit* target = _owner->SelectVictim())
                _owner->AI()->AttackStart(target);

        if (!_owner->GetVictim())
            if (Unit* target = _summoner->AI()->SelectTarget(SELECT_TARGET_RANDOM, 0))
                _owner->AI()->AttackStart(target);

        _owner->AI()->DoZoneInCombat();
        return true;
    }

private:
    Creature* _summoner;
    Creature* _owner;
};

struct npc_gauntlet_controller_hellforge_AI : public ScriptedAI
{
    npc_gauntlet_controller_hellforge_AI(Creature* creature) : ScriptedAI(creature), _instance(me->GetInstanceScript()),
        _eventRunning(false), _eventDone(false), _summons(me)
    {
        _eventDone = _instance->GetData(DATA_GET_HELLFORGE_GAUNTLET_STATE) ? true : false;
    }

    void Reset() override
    {
        _summons.DespawnAll();
        me->setActive(false);
        _task.CancelAll();
        _eventRunning = false;
        _gargoyleCount = 0;
        _deadGargoyleCount = 0;
        if (GameObject* door2 = _instance->GetGameObject(DATA_GO_GAUNTLET_DOORS2))
            door2->SetGoState(GO_STATE_ACTIVE);
    }

    void JustSummoned(Creature* creature) override
    {
        _summons.Summon(creature);
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        if (summon->GetEntry() == NPC_HELLFORGE_GARGOYLE)
        {
            if (++_deadGargoyleCount >= GARGOYLE_MOVE_POS_SIZE)
            {
                _eventRunning = false;
                _eventDone = true;
                _instance->SetData(DATA_HELLFORGE_GAUNTLET_DONE, DONE);

                if (GameObject* door2 = _instance->GetGameObject(DATA_GO_GAUNTLET_DOORS2))
                    door2->SetGoState(GO_STATE_ACTIVE);
                if (Unit* champion = _instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
                    if (champion->IsAIEnabled && champion->GetAI()->GetData(0) == STATE_DWARF_KILLED)
                        champion->GetAI()->DoAction(ACTION_GAUNTLET_DONE);
            }
        }
    }

    void SetGUID(uint64 guid, int32 data) override
    {
        if (data == DATA_CHARGE_TARGET_GUID)
        {
            std::vector<uint64> _temp;
            for (auto const& guid : _summons)
            {
                if (Creature* sum = ObjectAccessor::GetCreature(*me, guid))
                {
                    if (sum->GetEntry() == NPC_HELLFORGE_GARGOYLE && sum->IsAlive())
                        _temp.push_back(sum->GetGUID());
                }
            }

            if (!_temp.empty())
            {
                if (Creature* gargoyle = ObjectAccessor::GetCreature(*me, Trinity::Containers::SelectRandomContainerElement(_temp)))
                    gargoyle->AI()->SetGUID(guid, DATA_CHARGE_TARGET_GUID);
            }
        }
    }

    void MoveInLineOfSight(Unit* who) override
    {
        Player* player = who->ToPlayer();

        if (!player)
            return;

        if (player->IsGameMaster())
            return;

        if (me->IsWithinDist(player, 5.0f) && !_eventDone && !_eventRunning)
        {
            _eventRunning = true;
            me->setActive(true);
            ScheduleTasks();

            if (Unit * champion = _instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
                if (champion->IsAIEnabled && champion->GetAI()->GetData(0) == STATE_DWARF_KILLED)
                    champion->GetAI()->DoAction(ACTION_GAUNTLET_PULLED);

            _task.Schedule(3s, [&](TaskContext func)
            {
                GameObject* door1 = _instance->GetGameObject(DATA_GO_GAUNTLET_DOORS);
                GameObject* door2 = _instance->GetGameObject(DATA_GO_GAUNTLET_DOORS2);
                if (door1 && door2)
                {
                    door1->SetGoState(GO_STATE_READY);
                    door2->SetGoState(GO_STATE_READY);
                }
            });
        }
    }

    void ScheduleTasks()
    {
        _task.Schedule(1s, [&](TaskContext func)
        {
            if (_gargoyleCount < GARGOYLE_MOVE_POS_SIZE)
            {
                func.Repeat(1s);
                Position pos = me->GetNearPositionFromPos(_gargoyleSpawnPos, 5.0f);
                //! return old position, GetNearPositionFromPos modifies positionZ to ground level
                pos.m_positionZ = _gargoyleSpawnPos.GetPositionZ();
                if (Creature* gargoyle = me->SummonCreature(NPC_HELLFORGE_GARGOYLE, pos))
                {
                    gargoyle->SetCanFly(true);
                    gargoyle->GetMotionMaster()->MovePoint(1, _gargoyleMovePosition[_gargoyleCount]);
                    gargoyle->SetHomePosition(_gargoyleMovePosition[_gargoyleCount]);
                }
            }
            ++_gargoyleCount;
        });

        _task.Schedule(2s, [&](TaskContext func)
        {
            if (_eventRunning)
            {
                HellforgeStatValues val;
                sWorldCache.GetStatValue(STAT_ID_RISEN_MADMAN_MAX_HEALTH, val);
                uint32 healthToSet = val.StatValue;
                sWorldCache.GetStatValue(STAT_ID_RISEN_MADMAN_MELEE_DAMAGE, val);
                //! make them passive and engage couple of seconds later when emerge animation is done
                if (Creature* summon = me->SummonCreature(NPC_HELLFORGE_GHOUL, _exitSpawnPosition))
                {

                    summon->SetMaxHealth(healthToSet);
                    summon->SetFullHealth();
                    uint32 minDamage = val.StatValue * val.StatVariance;
                    uint32 maxDamage = val.StatValue;
                    summon->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    summon->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    summon->UpdateDamagePhysical(BASE_ATTACK);
                    summon->CastSpell(summon, SPELL_RISEN_WITCH_DOCTOR_SPAWN, true);
                    summon->SetReactState(REACT_PASSIVE);
                    summon->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                    summon->m_Events.AddEvent(new StartMovementEvent(me, summon), summon->m_Events.CalculateTime(5000));
                }

                if (Creature* summon = me->SummonCreature(NPC_HELLFORGE_ZOMBIE, _entranceSpawnPosition))
                {
                    summon->SetMaxHealth(healthToSet);
                    summon->SetFullHealth();
                    uint32 minDamage = val.StatValue * val.StatVariance;
                    uint32 maxDamage = val.StatValue;
                    summon->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    summon->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    summon->UpdateDamagePhysical(BASE_ATTACK);
                    summon->CastSpell(summon, SPELL_RISEN_WITCH_DOCTOR_SPAWN, true);
                    summon->SetReactState(REACT_PASSIVE);
                    summon->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                    summon->m_Events.AddEvent(new StartMovementEvent(me, summon), summon->m_Events.CalculateTime(5000));
                }

                func.Repeat(25s);
            }
        });

        _task.Schedule(10s, [&](TaskContext func)
        {
            std::list<Player*> _players;
            float _range = 65.f;
            Trinity::AnyPlayerInObjectRangeCheck checker(me, _range);
            Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, _players, checker);
            me->VisitNearbyWorldObject(_range, searcher);

            _players.remove_if([](Player* obj)
            {
                return obj->IsGameMaster();
            });

            if (_players.empty())
            {
                Reset();
                if (Unit * champion = _instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
                    if (champion->IsAIEnabled && champion->GetAI()->GetData(0) == STATE_DWARF_KILLED)
                        champion->GetAI()->DoAction(ACTION_GAUNTLET_FAILED);
            }

            func.Repeat(5s);
        });

        _task.Schedule(15s, [this](TaskContext func)
        {
            std::list<Player*> _lPlayers;
            float _range = 30.f;
            Trinity::AnyPlayerInObjectRangeCheck checker(me, _range);
            Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, _lPlayers, checker);
            me->VisitNearbyWorldObject(_range, searcher);

            _lPlayers.remove_if([](Player* ref)
            {
                return ref->IsGameMaster();
            });

            if (!_lPlayers.empty())
            {
                Player* player = Trinity::Containers::SelectRandomContainerElement(_lPlayers);
                if (player)
                {
                    player->CastSpell(player, SPELL_GAUNTLET_EVIDENCE_MARKER, true);
                    if (Aura* aura = player->GetAura(SPELL_GAUNTLET_EVIDENCE_MARKER))
                    {
                        aura->SetMaxDuration(3000);
                        aura->RefreshDuration();
                    }
                }
            }

            func.Repeat(15s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!_eventRunning)
            return;

        _task.Update(diff);
    }
private:
    bool _eventRunning;
    bool _eventDone;
    uint32 _gargoyleCount;
    uint32 _deadGargoyleCount;
    InstanceScript* _instance;
    TaskScheduler _task;
    SummonList _summons;
};

struct npc_bloody_gargoyle_hellforge : public ScriptedAI
{
    npc_bloody_gargoyle_hellforge(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _scheduler.CancelAll();
        LoadStats();
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ STAT_ID_EMPOWERED_SHOCKWAVE_DAMAGE, STAT_ID_GARGOYLE_MAX_HEALTH, STAT_ID_GARGOYLE_SHADOWBOLT_DAMAGE });
        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case STAT_ID_EMPOWERED_SHOCKWAVE_DAMAGE:
                {
                    _shockwaveDamage = ref.second.StatValue;
                    break;
                }
                case STAT_ID_GARGOYLE_SHADOWBOLT_DAMAGE:
                {
                    _shadowBoltDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case STAT_ID_GARGOYLE_MAX_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                default:
                    break;
            }
        }
    }

    void AttackStart(Unit* who) override
    {
        me->Attack(who, false);
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        if (pointId == 1)
        {
            me->SetAggressive();
            DoZoneInCombat();

            _scheduler.Schedule(3s, [this](TaskContext func)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _shadowBoltDamage);
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 30.f, true))
                    me->CastCustomSpell(SPELL_BLOODY_GARGOYLE_SHADOW_BOLT, val, target);

                func.Repeat(3s);
            });
        }
        else if (pointId == 20)
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, _shockwaveDamage); //config
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 1600.f);
            me->CastCustomSpell(73037, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
            _scheduler.Schedule(100ms, [this](TaskContext /*func*/)
            {
                me->GetMotionMaster()->MovePoint(1, me->GetHomePosition());
            });
        }
    }

    void SetGUID(uint64 guid, int32 data) override
    {
        if (data == DATA_CHARGE_TARGET_GUID)
        {
            _chargePlayerGUID = guid;
            if (Unit* player = ObjectAccessor::GetUnit(*me, _chargePlayerGUID))
            {
                me->CastStop();
                _scheduler.CancelAll();
                me->GetMotionMaster()->MoveCharge(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ() + 1.5f, 42.f, 20);
            }
            else
                _chargePlayerGUID = 0;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff);
        // does not melee attack at all
    }

private:
    TaskScheduler _scheduler;
    uint64 _chargePlayerGUID;
    uint32 _shockwaveDamage;
    uint32 _shadowBoltDamage;
};

enum HellforgeThrash : uint32
{
    NPC_HELLFORGE_CHAMPION = 250050,
    NPC_HELLFORGE_ADHERENT,
    NPC_DEMONIC_IMP,
    NPC_HELLFORGE_PRIEST,
    NPC_HELLFORGE_FALLEN_FANATIC,
    NPC_HELLFORGE_WITCH_DOCTOR,
    NPC_UNLIVING_DRUID,
    NPC_HELLFORGE_DEFENDER,
    NPC_HELLFORGE_KNIGHT,
    NPC_HELLFORGE_SPY,
    NPC_HELLFORGE_BERSERKER,
    NPC_HELLFORGE_HOUND
};

struct hellforge_trash_AI : public ScriptedAI
{
    hellforge_trash_AI(Creature* creature) : ScriptedAI(creature) { }

    uint32 GetStatValue(HellforgeStatValues element, bool useVariance = true)
    {
        uint32 statValue = element.StatValue;
        if (useVariance)
            statValue *= element.StatVariance;
        return statValue;
    }

    void CastCustomSpell(Unit *caster, Unit *victim, SpellValueMod modifier, uint32 value, uint32 spellId) const
    {
        if (!caster || !victim)
            return;

        CustomSpellValues val;
        val.AddSpellMod(modifier, value);
        caster->CastCustomSpell(spellId, val, victim, TRIGGERED_FULL_MASK);
    }

    Player* GetRandomPlayerInRange(Unit* who, float range) const
    {
        std::vector<uint64> _possibleTargets;
        auto& players = who->GetMap()->GetPlayers();
        for (auto && source : players)
        {
            Player* player = source.GetSource();
            if (!player)
                continue;

            if (!player->IsAlive())
                continue;

            if (player->GetDistance(who->GetPosition()) >= range)
                continue;

            _possibleTargets.push_back(player->GetGUID());
        }

        if (!_possibleTargets.empty())
        {
            if (Player* player = ObjectAccessor::GetPlayer(*who, Trinity::Containers::SelectRandomContainerElement(_possibleTargets)))
                return player;
        }

        return nullptr;
    }

    Player* GetRandomPlayerInRangeWithoutAura(Unit* who, float range, uint32 aura) const
    {
        std::vector<uint64> _possibleTargets;
        auto& players = who->GetMap()->GetPlayers();
        for (auto && source : players)
        {
            Player* player = source.GetSource();
            if (!player)
                continue;

            if (!player->IsAlive())
                continue;

            if (player->GetDistance(who->GetPosition()) >= range)
                continue;

            if (player->HasAura(aura))
                continue;

            _possibleTargets.push_back(player->GetGUID());
        }

        if (!_possibleTargets.empty())
        {
            if (Player* player = ObjectAccessor::GetPlayer(*who, Trinity::Containers::SelectRandomContainerElement(_possibleTargets)))
                return player;
        }

        return nullptr;
    }

    void LoadHealthFromHellforgeStats(HellforgeStatValues value)
    {
        uint32 maxHealth = GetStatValue(value);
        me->SetMaxHealth(maxHealth);
        me->SetFullHealth();
    }

    void LoadManaFromHellforgeStats(HellforgeStatValues value)
    {
        uint32 maxMana = GetStatValue(value);
        me->SetMaxPower(POWER_MANA, maxMana);
        me->SetPower(POWER_MANA, maxMana);
    }

    void LoadMeleeDamageFromHellforgeStats(HellforgeStatValues value)
    {
        uint32 minDamage = GetStatValue(value);
        uint32 maxDamage = GetStatValue(value, false);
        me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
        me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
        me->UpdateDamagePhysical(BASE_ATTACK);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        _task.Update(diff);

        DoMeleeAttackIfReady();
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _task.CancelAll();
        ScheduleTasks();
    }

    virtual void ScheduleTasks() { };

protected:
    TaskScheduler _task;
};

enum HellforgeChampion
{
    HELLFORGE_CHAMPION_STAT_ID_HEALTH               = 500,
    HELLFORGE_CHAMPION_STAT_ID_MELEE_DAMAGE         = 501,
    HELLFORGE_CHAMPION_STAT_ID_MORTAL_STRIKE_DMG    = 502,

    SPELL_WHIRLWIND                                 = 63808,
    SPELL_MORTAL_STRIKE                             = 67542,
    SPELL_CHARGE                                    = 25821
};

struct npc_hellforge_championAI : public hellforge_trash_AI
{
    npc_hellforge_championAI(Creature* creature) : hellforge_trash_AI(creature) { }

    void Reset() override
    {
        _task.CancelAll();
        LoadStats();
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ HELLFORGE_CHAMPION_STAT_ID_HEALTH, HELLFORGE_CHAMPION_STAT_ID_MELEE_DAMAGE,
            HELLFORGE_CHAMPION_STAT_ID_MORTAL_STRIKE_DMG });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case HELLFORGE_CHAMPION_STAT_ID_HEALTH:
                {
                    LoadHealthFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_CHAMPION_STAT_ID_MELEE_DAMAGE:
                {
                    LoadMeleeDamageFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_CHAMPION_STAT_ID_MORTAL_STRIKE_DMG:
                {
                    _mortalStrikeDamage = GetStatValue(ref.second);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _task.CancelAll();
        ScheduleTasks();
        if (Player* player = GetRandomPlayerInRange(me, 20.0f))
            me->CastSpell(player, SPELL_CHARGE);
    }

    void ScheduleTasks() override
    {
        _task.Schedule(40s, [&](TaskContext func)
        {
            DoCastSelf(SPELL_WHIRLWIND);
            func.Repeat(30s);
        });

        _task.Schedule(5s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _mortalStrikeDamage, SPELL_MORTAL_STRIKE);
            func.Repeat(10s);
        });

        _task.Schedule(20s, [&](TaskContext func)
        {
            auto repeatTimer = 15s;
            if (Player* player = GetRandomPlayerInRange(me, 30.0f))
                me->CastSpell(player, SPELL_CHARGE);
            else
                repeatTimer = 4s;

            func.Repeat(repeatTimer);
        });
    }
private:
    uint32 _mortalStrikeDamage;
};

enum HellforgeAdherent
{
    HELLFORGE_ADHERENT_STAT_ID_HEALTH                   = 503,
    HELLFORGE_ADHERENT_STAT_ID_MANA                     = 504,
    HELLFORGE_ADHERENT_STAT_ID_FIREBALL_VOLLEY_DAMAGE   = 505,
    HELLFORGE_ADHERENT_STAT_ID_ARCANE_EXPLOSION_DAMAGE  = 506,
    HELLFORGE_ADHERENT_STAT_ID_FLAME_BREATH_DAMAGE      = 507,

    SPELL_FIREBALL_VOLLEY                               = 43240,
    SPELL_SILENCE                                       = 56777,
    SPELL_ARCANE_EXPLOSION                              = 68002,
    SPELL_POLYMORPH                                     = 68311,
    SPELL_FLAME_BREATH                                  = 59692
};

struct npc_hellforge_adherentAI : public hellforge_trash_AI
{
    npc_hellforge_adherentAI(Creature* creature) : hellforge_trash_AI(creature), summons(me) { }

    void Reset() override
    {
        _task.CancelAll();
        LoadStats();
        summons.DespawnAll();

        if (Creature* imp = me->SummonCreature(NPC_DEMONIC_IMP, me->GetPosition()))
            imp->GetMotionMaster()->MoveFollow(me, 3.f, me->GetFollowAngle());
    }

    void JustSummoned(Creature* summon) override
    {
        hellforge_trash_AI::JustSummoned(summon);
        summons.Summon(summon);
    }

    void AttackStart(Unit* who) override
    {
        if (!who)
            return;

        AttackStartCaster(who, 100.0f);
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ HELLFORGE_ADHERENT_STAT_ID_HEALTH, HELLFORGE_ADHERENT_STAT_ID_MANA,
            HELLFORGE_ADHERENT_STAT_ID_FIREBALL_VOLLEY_DAMAGE, HELLFORGE_ADHERENT_STAT_ID_ARCANE_EXPLOSION_DAMAGE,
            HELLFORGE_ADHERENT_STAT_ID_FLAME_BREATH_DAMAGE });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case HELLFORGE_ADHERENT_STAT_ID_HEALTH:
                {
                    LoadHealthFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_ADHERENT_STAT_ID_MANA:
                {
                    LoadManaFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_ADHERENT_STAT_ID_FIREBALL_VOLLEY_DAMAGE:
                {
                    _fireballVolleyDamage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                case HELLFORGE_ADHERENT_STAT_ID_ARCANE_EXPLOSION_DAMAGE:
                {
                    _arcaneExplosionDamage = GetStatValue(ref.second);
                    break;
                }
                case HELLFORGE_ADHERENT_STAT_ID_FLAME_BREATH_DAMAGE:
                {
                    _flameBreathDamage = GetStatValue(ref.second);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void ScheduleTasks() override
    {
        _task.Schedule(5s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _fireballVolleyDamage, SPELL_FIREBALL_VOLLEY);
            func.Repeat(25s);
        });

        _task.Schedule(15s, [&](TaskContext func)
        {
            for (auto i = 0; i < 3; i++)
                if (Player* player = GetRandomPlayerInRangeWithoutAura(me, 30.0f, SPELL_SILENCE))
                    DoCast(player, SPELL_SILENCE);
            func.Repeat(20s);
        });

        _task.Schedule(20s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _arcaneExplosionDamage, SPELL_ARCANE_EXPLOSION);
            func.Repeat(25s);
        });

        _task.Schedule(8s, [&](TaskContext func)
        {
            Player* player = GetRandomPlayerInRangeWithoutAura(me, 30.f, SPELL_POLYMORPH);
            if (!player)
                player = GetRandomPlayerInRange(me, 30.f);

            if (player)
                DoCast(player, SPELL_POLYMORPH);

            func.Repeat(10s);
        });

        _task.Schedule(25s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _flameBreathDamage, SPELL_FLAME_BREATH);
            func.Repeat(35s);
        });
    }

private:
    uint32 _fireballVolleyDamage;
    uint32 _arcaneExplosionDamage;
    uint32 _flameBreathDamage;
    SummonList summons;
};


enum DemonicImp
{
    DEMONIC_IMP_STAT_ID_HEALTH          = 508,
    DEMONIC_IMP_STAT_ID_MANA            = 509,
    DEMONIC_IMP_STAT_ID_MELEE_DAMAGE    = 510,
    DEMONIC_IMP_STAT_ID_FIREBOLT_DMG    = 511,

    SPELL_FIRE_SHIELD                   = 71515,
    SPELL_FIREBOLT                      = 59468
};

struct npc_demonic_impAI : public hellforge_trash_AI
{
    npc_demonic_impAI(Creature* creature) : hellforge_trash_AI(creature) { }

    void Reset() override
    {
        _task.CancelAll();
        LoadStats();
    }

    void AttackStart(Unit* who) override
    {
        if (!who)
            return;

        AttackStartCaster(who, 100.0f);
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ DEMONIC_IMP_STAT_ID_HEALTH, DEMONIC_IMP_STAT_ID_MANA,
            DEMONIC_IMP_STAT_ID_MELEE_DAMAGE, DEMONIC_IMP_STAT_ID_FIREBOLT_DMG });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case DEMONIC_IMP_STAT_ID_HEALTH:
                {
                    LoadHealthFromHellforgeStats(ref.second);
                    break;
                }
                case DEMONIC_IMP_STAT_ID_MANA:
                {
                    LoadManaFromHellforgeStats(ref.second);
                    break;
                }
                case DEMONIC_IMP_STAT_ID_MELEE_DAMAGE:
                {
                    LoadMeleeDamageFromHellforgeStats(ref.second);
                    break;
                }
                case DEMONIC_IMP_STAT_ID_FIREBOLT_DMG:
                {
                    _firebolt_damage = GetStatValue(ref.second);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void ScheduleTasks() override
    {
        _task.Schedule(3s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _firebolt_damage, SPELL_FIREBOLT);
            func.Repeat(3s);
        });

        _task.Schedule(2s, [&](TaskContext func)
        {
            if (!me->HasAura(SPELL_FIRE_SHIELD))
                DoCastSelf(SPELL_FIRE_SHIELD);
            func.Repeat(30s);
        });
    }

private:
    uint32 _firebolt_damage;
};

enum HellforgePriest
{
    HELLFORGE_PRIEST_STAT_ID_HEALTH             = 512,
    HELLFORGE_PRIEST_STAT_ID_MANA               = 513,
    HELLFORGE_PRIEST_STAT_ID_MANA_BURN          = 514,
    HELLFORGE_PRIEST_STAT_ID_SHADOW_WORD_PAIN   = 515,
    HELLFORGE_PRIEST_STAT_ID_RENEW              = 516,
    HELLFORGE_PRIEST_STAT_ID_MIND_FLAY          = 517,

    SPELL_MANA_BURN                             = 68028,
    SPELL_SHADOW_WORD_PAIN                      = 72319,
    SPELL_SHADOWFORM                            = 63359,
    SPELL_REVIVE                                = 24341,
    SPELL_RENEW                                 = 71932,
    SPELL_MIND_FLAY                             = 68044
};

struct npc_hellforge_priestAI : public hellforge_trash_AI
{
    npc_hellforge_priestAI(Creature* creature) : hellforge_trash_AI(creature) { }

    void Reset() override
    {
        _task.CancelAll();
        LoadStats();
        DoCastSelf(SPELL_SHADOWFORM, true);
    }

    void AttackStart(Unit* who) override
    {
        if (!who)
            return;

        AttackStartCaster(who, 100.0f);
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ HELLFORGE_PRIEST_STAT_ID_HEALTH, HELLFORGE_PRIEST_STAT_ID_MANA,
            HELLFORGE_PRIEST_STAT_ID_MANA_BURN, HELLFORGE_PRIEST_STAT_ID_SHADOW_WORD_PAIN, HELLFORGE_PRIEST_STAT_ID_RENEW, HELLFORGE_PRIEST_STAT_ID_MIND_FLAY });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case HELLFORGE_PRIEST_STAT_ID_HEALTH:
                {
                    LoadHealthFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_PRIEST_STAT_ID_MANA:
                {
                    LoadManaFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_PRIEST_STAT_ID_MANA_BURN:
                {
                    _mana_burn_damage = GetStatValue(ref.second);
                    break;
                }
                case HELLFORGE_PRIEST_STAT_ID_SHADOW_WORD_PAIN:
                {
                    _shadow_word_damage = GetStatValue(ref.second);
                    break;
                }
                case HELLFORGE_PRIEST_STAT_ID_RENEW:
                {
                    _renew_heal = GetStatValue(ref.second);
                    break;
                }
                case HELLFORGE_PRIEST_STAT_ID_MIND_FLAY:
                {
                    _mind_flay_damage = GetStatValue(ref.second);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void ScheduleTasks() override
    {
        _task.Schedule(35s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _mana_burn_damage, SPELL_MANA_BURN);
            func.Repeat(35s);
        });

        _task.Schedule(5s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _shadow_word_damage, SPELL_SHADOW_WORD_PAIN);
            func.Repeat(5s);
        });

        _task.Schedule(60s, [&](TaskContext func)
        {
            auto _repeatTimer = 10s;
            std::vector<HellforgeThrash> trashEntries{ NPC_HELLFORGE_CHAMPION, NPC_HELLFORGE_ADHERENT,
                NPC_DEMONIC_IMP, NPC_HELLFORGE_PRIEST,
                NPC_HELLFORGE_FALLEN_FANATIC, NPC_HELLFORGE_WITCH_DOCTOR,
                NPC_UNLIVING_DRUID, NPC_HELLFORGE_DEFENDER,
                NPC_HELLFORGE_KNIGHT, NPC_HELLFORGE_SPY };

            Trinity::Containers::RandomShuffle(trashEntries);
            for (auto const& entry : trashEntries)
            {
                if (Creature* target = me->FindNearestCreature(entry, 30.0f, false))
                {
                    DoCast(target, SPELL_REVIVE);
                    target->Respawn();
                    if (InstanceScript * instance = me->GetInstanceScript())
                        instance->SetData64(DATA_REVIVE_TRASH, target->GetGUID());
                    _repeatTimer = 60s;
                    break;
                }
            }

            func.Repeat(_repeatTimer);
        });

        _task.Schedule(15s, [&](TaskContext func)
        {
            CastCustomSpell(me, me, SPELLVALUE_BASE_POINT0, _renew_heal, SPELL_RENEW);
            func.Repeat(15s);
        });

        _task.Schedule(5s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT1, _mind_flay_damage, SPELL_MIND_FLAY);
            func.Repeat(5s);
        });
    }

private:
    uint32 _mana_burn_damage, _shadow_word_damage, _renew_heal, _mind_flay_damage;
};

enum HellforgeFallenFanatic
{
    HELLFORGE_FALLEN_FANATIC_STAT_ID_HEALTH                 = 518,
    HELLFORGE_FALLEN_FANATIC_STAT_ID_MELEE_DMG              = 519,
    HELLFORGE_FALLEN_FANATIC_STAT_ID_DIVINE_STORM_DMG       = 520,
    HELLFORGE_FALLEN_FANATIC_STAT_ID_CRUSADER_STRIKE_DMG    = 521,
    HELLFORGE_FALLEN_FANATIC_STAT_ID_FLASH_HEAL             = 522,

    SPELL_DIVINE_STORM                                      = 66006,
    SPELL_CRUSADER_STRIKE                                   = 71549,
    SPELL_BEACON_OF_LIGHT                                   = 53654,
    SPELL_FLASH_HEAL                                        = 71783,
    SPELL_CONCUSSIVE_SHOCK                                  = 71338
};

struct npc_hellforge_fallen_fanaticAI : public hellforge_trash_AI
{
    npc_hellforge_fallen_fanaticAI(Creature* creature) : hellforge_trash_AI(creature) { }

    void Reset() override
    {
        _task.CancelAll();
        LoadStats();
        DoCastSelf(SPELL_SHADOWFORM, true);
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ HELLFORGE_FALLEN_FANATIC_STAT_ID_HEALTH, HELLFORGE_FALLEN_FANATIC_STAT_ID_MELEE_DMG,
            HELLFORGE_FALLEN_FANATIC_STAT_ID_DIVINE_STORM_DMG, HELLFORGE_FALLEN_FANATIC_STAT_ID_CRUSADER_STRIKE_DMG, HELLFORGE_FALLEN_FANATIC_STAT_ID_FLASH_HEAL });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case HELLFORGE_FALLEN_FANATIC_STAT_ID_HEALTH:
                {
                    LoadHealthFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_FALLEN_FANATIC_STAT_ID_MELEE_DMG:
                {
                    LoadMeleeDamageFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_FALLEN_FANATIC_STAT_ID_DIVINE_STORM_DMG:
                {
                    _divine_storm_damage = GetStatValue(ref.second);
                    break;
                }
                case HELLFORGE_FALLEN_FANATIC_STAT_ID_CRUSADER_STRIKE_DMG:
                {
                    _crusader_strike_damage = GetStatValue(ref.second);
                    break;
                }
                case HELLFORGE_FALLEN_FANATIC_STAT_ID_FLASH_HEAL:
                {
                    _flash_heal = GetStatValue(ref.second);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void ScheduleTasks() override
    {
        _task.Schedule(20s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT1, _divine_storm_damage, SPELL_DIVINE_STORM);
            func.Repeat(20s);
        });

        _task.Schedule(5s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT1, _crusader_strike_damage, SPELL_CRUSADER_STRIKE);
            func.Repeat(5s);
        });

        _task.Schedule(15s, [&](TaskContext func)
        {
            bool healed = false;
            std::vector<HellforgeThrash> trashEntries{ NPC_HELLFORGE_CHAMPION, NPC_HELLFORGE_ADHERENT,
                NPC_DEMONIC_IMP, NPC_HELLFORGE_PRIEST,
                NPC_HELLFORGE_FALLEN_FANATIC, NPC_HELLFORGE_WITCH_DOCTOR,
                NPC_UNLIVING_DRUID, NPC_HELLFORGE_DEFENDER,
                NPC_HELLFORGE_KNIGHT, NPC_HELLFORGE_SPY };

            Trinity::Containers::RandomShuffle(trashEntries);
            for (auto const& entry : trashEntries)
            {
                if (Creature* target = me->FindNearestCreature(entry, 30.0f, true))
                {
                    if (target->GetHealthPct() < 80)
                    {
                        CastCustomSpell(me, target, SPELLVALUE_BASE_POINT0, _flash_heal, SPELL_FLASH_HEAL);
                        healed = true;
                        break;
                    }
                }
            }

            if (!healed && me->GetHealthPct() < 80)
                CastCustomSpell(me, me, SPELLVALUE_BASE_POINT0, _flash_heal, SPELL_FLASH_HEAL);

            func.Repeat(15s);
        });

        _task.Schedule(5s, [&](TaskContext func)
        {
            bool beaconApplied = false;
            std::vector<HellforgeThrash> trashEntries{ NPC_HELLFORGE_CHAMPION, NPC_HELLFORGE_ADHERENT,
                NPC_DEMONIC_IMP, NPC_HELLFORGE_PRIEST,
                NPC_HELLFORGE_FALLEN_FANATIC, NPC_HELLFORGE_WITCH_DOCTOR,
                NPC_UNLIVING_DRUID, NPC_HELLFORGE_DEFENDER,
                NPC_HELLFORGE_KNIGHT, NPC_HELLFORGE_SPY };

            Trinity::Containers::RandomShuffle(trashEntries);
            for (auto const& entry : trashEntries)
            {
                if (Creature* target = me->FindNearestCreature(entry, 30.0f, true))
                {
                    if (target->GetHealthPct() < 80)
                    {
                        DoCast(target, SPELL_BEACON_OF_LIGHT);
                        beaconApplied = true;
                        break;
                    }
                }
            }

            if (!beaconApplied && me->GetHealthPct() < 80)
                DoCastSelf(SPELL_BEACON_OF_LIGHT);

            func.Repeat(60s);
        });

        _task.Schedule(12s, [&](TaskContext func)
        {
            DoCastVictim(SPELL_CONCUSSIVE_SHOCK);
            func.Repeat(12s);
        });
    }

private:
    uint32 _flash_heal, _crusader_strike_damage, _divine_storm_damage;
};

enum HellforgeWitchDoctor
{
    HELLFORGE_WITCH_DOCTOR_STAT_ID_HEALTH           = 523,
    HELLFORGE_WITCH_DOCTOR_STAT_ID_MANA             = 524,
    HELLFORGE_WITCH_DOCTOR_STAT_ID_CORRUPTION_DMG   = 525,
    HELLFORGE_WITCH_DOCTOR_STAT_ID_THROW_SLIME_DMG  = 526,
    HELLFORGE_WITCH_DOCTOR_STAT_ID_INCINERATE_DMG   = 527,
    HELLFORGE_WITCH_DOCTOR_STAT_ID_CHAOS_BOLT_DMG   = 528,
    HELLFORGE_WITCH_DOCTOR_STAT_ID_SHADOWFURY       = 529,

    SPELL_CURSE_OF_EXHAUSTION                       = 65815,
    SPELL_CORRUPTION                                = 71937,
    SPELL_TOXIC_SLIME                               = 37615,
    SPELL_INCINERATE                                = 71135,
    SPELL_CHAOS_BOLT                                = 71108,
    SPELL_FEAR                                      = 29321,
    SPELL_SHADOWFURY                                = 47847
};

struct npc_hellforge_witch_doctorAI : public hellforge_trash_AI
{
    npc_hellforge_witch_doctorAI(Creature* creature) : hellforge_trash_AI(creature) { }

    void Reset() override
    {
        _task.CancelAll();
        LoadStats();
    }

    void AttackStart(Unit* who) override
    {
        if (!who)
            return;

        AttackStartCaster(who, 100.0f);
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ HELLFORGE_WITCH_DOCTOR_STAT_ID_HEALTH, HELLFORGE_WITCH_DOCTOR_STAT_ID_MANA,
            HELLFORGE_WITCH_DOCTOR_STAT_ID_CORRUPTION_DMG, HELLFORGE_WITCH_DOCTOR_STAT_ID_THROW_SLIME_DMG, HELLFORGE_WITCH_DOCTOR_STAT_ID_INCINERATE_DMG, HELLFORGE_WITCH_DOCTOR_STAT_ID_CHAOS_BOLT_DMG,
            HELLFORGE_WITCH_DOCTOR_STAT_ID_SHADOWFURY });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case HELLFORGE_WITCH_DOCTOR_STAT_ID_HEALTH:
                {
                    LoadHealthFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_WITCH_DOCTOR_STAT_ID_MANA:
                {
                    LoadManaFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_WITCH_DOCTOR_STAT_ID_CORRUPTION_DMG:
                {
                    _corruption_damage = GetStatValue(ref.second);
                    break;
                }
                case HELLFORGE_WITCH_DOCTOR_STAT_ID_THROW_SLIME_DMG:
                {
                    _throw_slime_damage = GetStatValue(ref.second);
                    break;
                }
                case HELLFORGE_WITCH_DOCTOR_STAT_ID_INCINERATE_DMG:
                {
                    _incinerate_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                case HELLFORGE_WITCH_DOCTOR_STAT_ID_CHAOS_BOLT_DMG:
                {
                    _chaos_bolt_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                case HELLFORGE_WITCH_DOCTOR_STAT_ID_SHADOWFURY:
                {
                    _shadowfury_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                default:
                    break;
            }
        }
    }

    void ScheduleTasks() override
    {
        _task.Schedule(5s, [&](TaskContext func)
        {
            DoCastVictim(SPELL_CURSE_OF_EXHAUSTION);
            func.Repeat(10s);
        });

        _task.Schedule(10s, [&](TaskContext func)
        {
            Player* player = GetRandomPlayerInRangeWithoutAura(me, 30.f, SPELL_CORRUPTION);
            if (!player)
                player = GetRandomPlayerInRange(me, 30.f);

            if (player)
                CastCustomSpell(me, player, SPELLVALUE_BASE_POINT0, _corruption_damage, SPELL_CORRUPTION);
            func.Repeat(10s);
        });

        _task.Schedule(20s, [&](TaskContext func)
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, _throw_slime_damage);
            val.AddSpellMod(SPELLVALUE_BASE_POINT2, _throw_slime_damage);
            if (me->GetVictim())
                me->CastCustomSpell(SPELL_TOXIC_SLIME, val, me->GetVictim(), TRIGGERED_FULL_MASK);
            func.Repeat(10s);
        });

        _task.Schedule(10s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _incinerate_damage, SPELL_INCINERATE);
            func.Repeat(10s);
        });

        _task.Schedule(35s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _chaos_bolt_damage, SPELL_CHAOS_BOLT);
            func.Repeat(35s);
        });

        _task.Schedule(15s, [&](TaskContext func)
        {
            DoCast(SPELL_FEAR);
            func.Repeat(15s);
        });

        _task.Schedule(30s, [&](TaskContext func)
        {
            if (Player* pl = GetRandomPlayerInRange(me, 30.0f))
                CastCustomSpell(me, pl, SPELLVALUE_BASE_POINT0, _shadowfury_damage, SPELL_SHADOWFURY);
            func.Repeat(35s);
        });
    }

private:
    uint32 _corruption_damage, _throw_slime_damage, _incinerate_damage, _chaos_bolt_damage, _shadowfury_damage;
};

enum HellforgeUnlivingDruid
{
    HELLFORGE_UNLIVING_DRUID_STAT_ID_HEALTH             = 530,
    HELLFORGE_UNLIVING_DRUID_STAT_ID_MANA               = 531,
    HELLFORGE_UNLIVING_DRUID_STAT_ID_TYPHOON_DMG        = 532,
    HELLFORGE_UNLIVING_DRUID_STAT_ID_REJUVENATION_HEAL  = 533,
    HELLFORGE_UNLIVING_DRUID_STAT_ID_WRATH_DMG          = 534,

    SPELL_STARFALL                                      = 61986,
    SPELL_CYCLONE                                       = 65859,
    SPELL_TYPHOON                                       = 69823,
    SPELL_REJUVENATION                                  = 71142,
    SPELL_WRATH                                         = 75327
};

struct npc_unliving_druidAI : public hellforge_trash_AI
{
    npc_unliving_druidAI(Creature* creature) : hellforge_trash_AI(creature) {}

    void Reset() override
    {
        _task.CancelAll();
        LoadStats();
        DoCastSelf(SPELL_SHADOWFORM, true);
    }

    void AttackStart(Unit* who) override
    {
        if (!who)
            return;

        AttackStartCaster(who, 100.0f);
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ HELLFORGE_UNLIVING_DRUID_STAT_ID_HEALTH, HELLFORGE_UNLIVING_DRUID_STAT_ID_MANA,
            HELLFORGE_UNLIVING_DRUID_STAT_ID_TYPHOON_DMG, HELLFORGE_UNLIVING_DRUID_STAT_ID_REJUVENATION_HEAL, HELLFORGE_UNLIVING_DRUID_STAT_ID_WRATH_DMG});

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case HELLFORGE_UNLIVING_DRUID_STAT_ID_HEALTH:
                {
                    LoadHealthFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_UNLIVING_DRUID_STAT_ID_MANA:
                {
                    LoadManaFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_UNLIVING_DRUID_STAT_ID_TYPHOON_DMG:
                {
                    _typhoon_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                case HELLFORGE_UNLIVING_DRUID_STAT_ID_REJUVENATION_HEAL:
                {
                    _rejuvenation_heal = GetStatValue(ref.second);
                    break;
                }
                case HELLFORGE_UNLIVING_DRUID_STAT_ID_WRATH_DMG:
                {
                    _wrath_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                default:
                    break;
                }
        }
    }

    void ScheduleTasks() override
    {
        _task.Schedule(1s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _wrath_damage, SPELL_WRATH);
            func.Repeat(4s);
        });

        _task.Schedule(30s, [&](TaskContext func)
        {
            DoCast(SPELL_STARFALL);
            func.Repeat(60s);
        });

        _task.Schedule(4s, [&](TaskContext func)
        {
            if (Player* pl = GetRandomPlayerInRange(me, 30.0f))
                DoCast(pl, SPELL_CYCLONE);
            func.Repeat(15s);
        });

        _task.Schedule(1s, [&](TaskContext func)
        {
            if (me->GetDistance(me->GetVictim()->GetPosition()) < 15.0f)
                CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT1, _typhoon_damage, SPELL_TYPHOON);
            func.Repeat(20s);
        });

        _task.Schedule(10s, [&](TaskContext func)
        {
            bool rejuvenationApplied = false;
            std::vector<HellforgeThrash> trashEntries{ NPC_HELLFORGE_CHAMPION, NPC_HELLFORGE_ADHERENT,
                NPC_DEMONIC_IMP, NPC_HELLFORGE_PRIEST,
                NPC_HELLFORGE_FALLEN_FANATIC, NPC_HELLFORGE_WITCH_DOCTOR,
                NPC_UNLIVING_DRUID, NPC_HELLFORGE_DEFENDER,
                NPC_HELLFORGE_KNIGHT, NPC_HELLFORGE_SPY };

            Trinity::Containers::RandomShuffle(trashEntries);
            for (auto const& entry : trashEntries)
            {
                if (Creature* target = me->FindNearestCreature(entry, 30.0f, true))
                {
                    if (target->GetHealthPct() < 80)
                    {
                        CastCustomSpell(me, target, SPELLVALUE_BASE_POINT0, _rejuvenation_heal, SPELL_REJUVENATION);
                        rejuvenationApplied = true;
                        break;
                    }
                }
            }

            if (!rejuvenationApplied && me->GetHealthPct() < 80)
                CastCustomSpell(me, me, SPELLVALUE_BASE_POINT0, _rejuvenation_heal, SPELL_REJUVENATION);

            func.Repeat(20s);
        });
    }

private:
    uint32 _typhoon_damage, _rejuvenation_heal, _wrath_damage;
};

enum HellforgeDefender
{
    HELLFORGE_DEFENEDER_STAT_ID_HEALTH          = 535,
    HELLFORGE_DEFENEDER_STAT_ID_MELEE_DMG       = 536,
    HELLFORGE_DEFENEDER_STAT_ID_SHOCKWAVE_DMG   = 537,
    HELLFORGE_DEFENEDER_STAT_ID_SHIELD_SLAM_DMG = 538,
    HELLFORGE_DEFENEDER_STAT_ID_ENRAGE_DMG      = 539,

    SPELL_SLAM                                  = 50782,
    SPELL_ENRAGE                                = 12686,
    SPELL_SHIELD_SLAM                           = 72645,
    SPELL_SHOCKWAVE                             = 75418,
    SPELL_CLEAVE                                = 74524
};

struct npc_hellforge_defenderAI : public hellforge_trash_AI
{
    npc_hellforge_defenderAI(Creature* creature) : hellforge_trash_AI(creature)
    {
        if(InstanceScript* instance = me->GetInstanceScript())
            if(instance->GetData(DATA_GET_HELLFORGE_SNAKE_ROOM_TRASH_COUNT))
                me->SetPhaseMask(300, true);
    }

    void Reset() override
    {
        _task.CancelAll();
        LoadStats();
    }

    void DoAction(int32 param) override
    {
        if (param == ACTION_SHOW_COCCON)
        {
            me->SetPhaseMask(1, true);
            me->MonsterYell("Who dares to profane this holy place?! Show yourself and face me!", LANG_UNIVERSAL, me);
        }
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ HELLFORGE_DEFENEDER_STAT_ID_HEALTH, HELLFORGE_DEFENEDER_STAT_ID_MELEE_DMG,
            HELLFORGE_DEFENEDER_STAT_ID_SHOCKWAVE_DMG, HELLFORGE_DEFENEDER_STAT_ID_SHIELD_SLAM_DMG, HELLFORGE_DEFENEDER_STAT_ID_ENRAGE_DMG });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case HELLFORGE_DEFENEDER_STAT_ID_HEALTH:
                {
                    LoadHealthFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_DEFENEDER_STAT_ID_MELEE_DMG:
                {
                    LoadMeleeDamageFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_DEFENEDER_STAT_ID_SHOCKWAVE_DMG:
                {
                    _shockwave_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                case HELLFORGE_DEFENEDER_STAT_ID_SHIELD_SLAM_DMG:
                {
                    _shield_slam_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                case HELLFORGE_DEFENEDER_STAT_ID_ENRAGE_DMG:
                {
                    _enrage_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                default:
                    break;
                }
        }
    }

    void ScheduleTasks() override
    {
        _task.Schedule(5s, [&](TaskContext func)
        {
            DoCastVictim(SPELL_SLAM);
            func.Repeat(10s);
        });

        _task.Schedule(13s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT1, _shield_slam_damage, SPELL_SHIELD_SLAM);
            func.Repeat(10s);
        });

        _task.Schedule(10s, [&](TaskContext func)
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, _enrage_damage);
            val.AddSpellMod(SPELLVALUE_BASE_POINT1, _enrage_damage);
            if (me->GetVictim())
                me->CastCustomSpell(SPELL_ENRAGE, val, me, TRIGGERED_FULL_MASK);
            func.Repeat(15s);
        });

        _task.Schedule(1s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT1, _shockwave_damage, SPELL_SHOCKWAVE);
            func.Repeat(35s);
        });

        _task.Schedule(3s, [&](TaskContext func)
        {
            DoCastVictim(SPELL_CLEAVE);
            func.Repeat(15s);
        });
    }

    void JustDied(Unit* killer) override
    {
        if(InstanceScript* instance = me->GetInstanceScript())
            if (Creature * coccon = instance->GetCreature(DATA_NPC_CHAMPION_COCCON))
                if (coccon->IsAIEnabled)
                    coccon->GetAI()->DoAction(ACTION_TRASH_DEFENDER_KILLED);
    }

private:
    uint32 _shockwave_damage, _shield_slam_damage, _enrage_damage;
};

enum HellforgeKnight
{
    HELLFORGE_KNIGHT_STAT_ID_HEALTH                 = 540,
    HELLFORGE_KNIGHT_STAT_ID_MELEE_DMG              = 541,
    HELLFORGE_KNIGHT_STAT_ID_DEATH_AND_DECAY_DMG    = 542,
    HELLFORGE_KNIGHT_STAT_ID_ICY_TOUCH_DMG          = 543,
    HELLFORGE_KNIGHT_STAT_ID_SCOURGE_STRIKE_DMG     = 544,

    SPELL_DEATH_GRIP                                = 64429,
    SPELL_DEATH_AND_DECAY                           = 72110,
    SPELL_ICY_TOUCH                                 = 69916,
    SPELL_SCOURGE_STRIKE                            = 71488
};

struct npc_hellforge_knightAI : public hellforge_trash_AI
{
    npc_hellforge_knightAI(Creature* creature) : hellforge_trash_AI(creature) {}

    void Reset() override
    {
        _task.CancelAll();
        LoadStats();
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ HELLFORGE_KNIGHT_STAT_ID_HEALTH, HELLFORGE_KNIGHT_STAT_ID_MELEE_DMG,
            HELLFORGE_KNIGHT_STAT_ID_DEATH_AND_DECAY_DMG, HELLFORGE_KNIGHT_STAT_ID_ICY_TOUCH_DMG, HELLFORGE_KNIGHT_STAT_ID_SCOURGE_STRIKE_DMG });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case HELLFORGE_KNIGHT_STAT_ID_HEALTH:
                {
                    LoadHealthFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_KNIGHT_STAT_ID_MELEE_DMG:
                {
                    LoadMeleeDamageFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_KNIGHT_STAT_ID_DEATH_AND_DECAY_DMG:
                {
                    _death_and_decay_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                case HELLFORGE_KNIGHT_STAT_ID_ICY_TOUCH_DMG:
                {
                    _icy_touch_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                case HELLFORGE_KNIGHT_STAT_ID_SCOURGE_STRIKE_DMG:
                {
                    _scourge_strike_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                default:
                    break;
            }
        }
    }

    void ScheduleTasks() override
    {
        _task.Schedule(10s, [&](TaskContext func)
        {
            if (Player* pl = GetRandomPlayerInRange(me, 30.0f))
                DoCast(pl, SPELL_DEATH_GRIP);
            func.Repeat(35s);
        });

        _task.Schedule(20s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _death_and_decay_damage, SPELL_DEATH_AND_DECAY);
            func.Repeat(20s);
        });

        _task.Schedule(2s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _icy_touch_damage, SPELL_ICY_TOUCH);
            func.Repeat(3s);
        });

        _task.Schedule(2s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _scourge_strike_damage, SPELL_SCOURGE_STRIKE);
            func.Repeat(3s);
        });
    }

private:
    uint32 _death_and_decay_damage, _icy_touch_damage, _scourge_strike_damage;
};

enum HellforgeSpy
{
    HELLFORGE_SPY_STAT_ID_HEALTH            = 545,
    HELLFORGE_SPY_STAT_ID_MELEE_DMG         = 546,
    HELLFORGE_SPY_STAT_ID_AMBUSH_DMG        = 547,
    HELLFORGE_SPY_STAT_ID_CHEAP_SHOT_DMG    = 548,
    HELLFORGE_SPY_STAT_ID_MULTILATE_DMG     = 549,

    SPELL_STEALTH                           = 8218,
    SPELL_AMBUSH                            = 41390,
    SPEL_CHEAP_SHOT                         = 31843,
    SPELL_VANISH                            = 71400,
    SPELL_MULTILATE                         = 41103,
    SPELL_DUAL_WIELD                        = 674
};

struct npc_hellforge_spyAI : public hellforge_trash_AI
{
    npc_hellforge_spyAI(Creature* creature) : hellforge_trash_AI(creature) { }

    void Reset() override
    {
        _task.CancelAll();
        LoadStats();
        DoCastSelf(SPELL_DUAL_WIELD);
        DoCastSelf(SPELL_STEALTH, true);
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ HELLFORGE_SPY_STAT_ID_HEALTH, HELLFORGE_SPY_STAT_ID_MELEE_DMG,
            HELLFORGE_SPY_STAT_ID_AMBUSH_DMG, HELLFORGE_SPY_STAT_ID_CHEAP_SHOT_DMG, HELLFORGE_SPY_STAT_ID_MULTILATE_DMG });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case HELLFORGE_SPY_STAT_ID_HEALTH:
                {
                    LoadHealthFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_SPY_STAT_ID_MELEE_DMG:
                {
                    LoadMeleeDamageFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_SPY_STAT_ID_CHEAP_SHOT_DMG:
                {
                    _cheap_shot_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                case HELLFORGE_SPY_STAT_ID_AMBUSH_DMG:
                {
                    _ambush_damager = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                case HELLFORGE_SPY_STAT_ID_MULTILATE_DMG:
                {
                    _multilate_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                default:
                    break;
            }
        }
    }

    void ScheduleTasks() override
    {
        _task.Schedule(1s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _ambush_damager, SPELL_AMBUSH);
        });

        _task.Schedule(20s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _cheap_shot_damage, SPEL_CHEAP_SHOT);
            func.Repeat(20s);
        });

        _task.Schedule(15s, [&](TaskContext func)
        {
            if (Player* pl = GetRandomPlayerInRange(me, 30.0f))
                DoCast(pl, SPELL_VANISH);
            func.Repeat(60s);
        });

        _task.Schedule(3s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _multilate_damage, SPELL_MULTILATE);
            func.Repeat(3s);
        });
    }

private:
    uint32 _cheap_shot_damage, _ambush_damager, _multilate_damage;
};

enum HellforgeBerserker
{
    HELLFORGE_BERSERKER_STAT_ID_HEALTH          = 550,
    HELLFORGE_BERSERKER_STAT_ID_MELEE_DMG       = 551,
    HELLFORGE_BERSERKER_STAT_ID_MANA            = 552,
    HELLFORGE_BERSERKER_STAT_ID_STORMSTRIKE_DMG = 553,
    HELLFORGE_BERSERKER_STAT_ID_LAVA_LASH_DMG   = 554,

    SPELL_BLOODLUST                             = 37067,
    SPELL_STORMSTRIKE                           = 65972,
    SPELL_WINDFURY_WEAPON                       = 65975,
    SPELL_LAVA_LASH                             = 65974
};

struct npc_hellforge_berserkerAI : public hellforge_trash_AI
{
    npc_hellforge_berserkerAI(Creature* creature) : hellforge_trash_AI(creature) {}

    void Reset() override
    {
        _task.CancelAll();
        LoadStats();

        for (auto i = 0; i < 2; i++)
            if (Creature* cr = me->FindNearestCreature(NPC_HELLFORGE_HOUND, 50.0f, false))
                cr->Respawn();
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ HELLFORGE_BERSERKER_STAT_ID_HEALTH, HELLFORGE_BERSERKER_STAT_ID_MELEE_DMG,
           HELLFORGE_BERSERKER_STAT_ID_MANA, HELLFORGE_BERSERKER_STAT_ID_STORMSTRIKE_DMG, HELLFORGE_BERSERKER_STAT_ID_LAVA_LASH_DMG });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case HELLFORGE_BERSERKER_STAT_ID_HEALTH:
                {
                    LoadHealthFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_BERSERKER_STAT_ID_MANA:
                {
                    LoadManaFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_BERSERKER_STAT_ID_MELEE_DMG:
                {
                    LoadMeleeDamageFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_BERSERKER_STAT_ID_LAVA_LASH_DMG:
                {
                    _lava_lash_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                case HELLFORGE_BERSERKER_STAT_ID_STORMSTRIKE_DMG:
                {
                    _stormstrike_damage = urand(GetStatValue(ref.second), GetStatValue(ref.second, false));
                    break;
                }
                default:
                    break;
            }
        }
    }

    void ScheduleTasks() override
    {
        _task.Schedule(15s, [&](TaskContext func)
        {
            std::vector<HellforgeThrash> trashEntries{ NPC_HELLFORGE_CHAMPION, NPC_HELLFORGE_ADHERENT,
                NPC_DEMONIC_IMP, NPC_HELLFORGE_PRIEST,
                NPC_HELLFORGE_FALLEN_FANATIC, NPC_HELLFORGE_WITCH_DOCTOR,
                NPC_UNLIVING_DRUID, NPC_HELLFORGE_DEFENDER,
                NPC_HELLFORGE_KNIGHT, NPC_HELLFORGE_SPY,
                NPC_HELLFORGE_BERSERKER, NPC_HELLFORGE_HOUND };
            Trinity::Containers::RandomShuffle(trashEntries);
            for (auto const& entry : trashEntries)
                if (Creature* target = me->FindNearestCreature(entry, 30.0f, true))
                        DoCast(target, SPELL_BLOODLUST);

            DoCastSelf(SPELL_BLOODLUST);

            func.Repeat(20s);
        });

        _task.Schedule(10s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _stormstrike_damage, SPELL_STORMSTRIKE);
            func.Repeat(10s);
        });

        _task.Schedule(5s, [&](TaskContext func)
        {
            CastCustomSpell(me, me->GetVictim(), SPELLVALUE_BASE_POINT0, _lava_lash_damage, SPELL_LAVA_LASH);
            func.Repeat(25s);
        });

        _task.Schedule(8s, [&](TaskContext func)
        {
            DoCastSelf(SPELL_WINDFURY_WEAPON);
            func.Repeat(8s);
        });
    }

private:
    uint32 _stormstrike_damage, _lava_lash_damage;
};

enum HellforgeHound
{
    HELLFORGE_HOUND_STAT_ID_HEALTH      = 555,
    HELLFORGE_HOUND_STAT_ID_MELEE_DMG   = 556,

    SPELL_SHRED                         = 61548,
    SPELL_STRENGHT_OF_PACK              = 64369
};

struct npc_hellforge_houndAI : public hellforge_trash_AI
{
    npc_hellforge_houndAI(Creature* creature) : hellforge_trash_AI(creature) {}

    void Reset() override
    {
        _task.CancelAll();
        LoadStats();
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _task.CancelAll();
        ScheduleTasks();
        DoCastSelf(SPELL_STRENGHT_OF_PACK);
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ HELLFORGE_HOUND_STAT_ID_HEALTH, HELLFORGE_HOUND_STAT_ID_MELEE_DMG });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case HELLFORGE_HOUND_STAT_ID_HEALTH:
                {
                    LoadHealthFromHellforgeStats(ref.second);
                    break;
                }
                case HELLFORGE_HOUND_STAT_ID_MELEE_DMG:
                {
                    LoadMeleeDamageFromHellforgeStats(ref.second);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void ScheduleTasks() override
    {
        _task.Schedule(1s, [&](TaskContext func)
        {
            DoCastVictim(SPELL_SHRED);
            func.Repeat(4s);
        });
    }
};

class spell_evidence_marker_hellforge_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_evidence_marker_hellforge_AuraScript);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetCaster())
            return;

        if (InstanceScript* instance = GetCaster()->GetInstanceScript())
        {
            if (Creature* controller = instance->GetCreature(DATA_GAUNTLET_CONTROLLER))
                controller->AI()->SetGUID(GetCaster()->GetGUID(), DATA_CHARGE_TARGET_GUID);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_evidence_marker_hellforge_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

constexpr uint32 QUEST_MEETING_IN_HELLFORGE{ 30012 };
struct npc_hellforge_teleporter : public ScriptedAI
{
    npc_hellforge_teleporter(Creature* creature) : ScriptedAI(creature)
    {
        me->SetSelectable(false);
    }

    void Reset() override
    {
        _canUsePortal = true;
        _scheduler.CancelAll();
    }

    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }

    void MoveInLineOfSight(Unit* who) override
    {
        if (!_canUsePortal)
            return;

        _canUsePortal = false;
        _scheduler.Schedule(1s, [this](TaskContext /*func*/)
        {
            _canUsePortal = true;
        });

        Player* player = who->ToPlayer();
        if (!player)
            return;

        if (me->GetDistance(player) > 2.5f)
            return;

        bool _canEnter = player->GetQuestStatus(QUEST_MEETING_IN_HELLFORGE) == QUEST_STATUS_COMPLETE ||
            player->GetQuestStatus(QUEST_MEETING_IN_HELLFORGE) == QUEST_STATUS_REWARDED;

        if (!_canEnter)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You must have active or completed \"Meeting in Hellforge\" quest.");
            return;
        }

        Group* group = player->GetGroup();
        _canEnter = group && group->isRaidGroup();

        if (!_canEnter)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You must be in a raid group to enter this instance.");
            return;
        }

        if (player->GetDifficulty(false) != DUNGEON_DIFFICULTY_HEROIC)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Wrong difficulty setting, please set 5 man heroic in order to enter Hellforge.");
            return;
        }

        if (!player->IsBeingTeleported())
        {
            if (player->GetMapId() != HELLFORGE_MAP_ID)
            {
                if (!sMapMgr->CanPlayerEnter(HELLFORGE_MAP_ID, player, false))
                    return;

                player->TeleportTo(HELLFORGE_MAP_ID, { 1380.748f, -819.692f, -92.722f, 1.516f });
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

private:
    TaskScheduler _scheduler;
    bool _canUsePortal;
};

void AddSC_hellforge_trash()
{
    /** Gauntlet start **/
    new CreatureAILoader<npc_gauntlet_controller_hellforge_AI>("npc_gauntlet_controller_hellforge");
    new CreatureAILoader<npc_bloody_gargoyle_hellforge>("npc_bloody_gargoyle_hellforge");
    new AuraScriptLoaderEx<spell_evidence_marker_hellforge_AuraScript>("spell_evidence_marker_hellforge");
    new CreatureAILoader<npc_hellforge_teleporter>("npc_hellforge_teleporter");
    /** Gauntlet end **/

    new CreatureAILoader<npc_hellforge_championAI>("npc_hellforge_champion");
    new CreatureAILoader<npc_hellforge_adherentAI>("npc_hellforge_adherent");
    new CreatureAILoader<npc_hellforge_priestAI>("npc_hellforge_priest");
    new CreatureAILoader<npc_hellforge_fallen_fanaticAI>("npc_hellforge_fallen_fanatic");
    new CreatureAILoader<npc_demonic_impAI>("npc_demonic_imp");
    new CreatureAILoader<npc_hellforge_witch_doctorAI>("npc_hellforge_witch_doctor");
    new CreatureAILoader<npc_unliving_druidAI>("npc_unliving_druid");
    new CreatureAILoader<npc_hellforge_defenderAI>("npc_hellforge_defender");
    new CreatureAILoader<npc_hellforge_knightAI>("npc_hellforge_knight");
    new CreatureAILoader<npc_hellforge_spyAI>("npc_hellforge_spy");
    new CreatureAILoader<npc_hellforge_berserkerAI>("npc_hellforge_berserker");
    new CreatureAILoader<npc_hellforge_houndAI>("npc_hellforge_hound");
}
