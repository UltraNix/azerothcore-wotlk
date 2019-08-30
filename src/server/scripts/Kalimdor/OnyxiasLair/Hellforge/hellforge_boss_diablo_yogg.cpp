#include "ScriptedCreature.h"
#include "WorldCache.h"

enum DiabloYoggData
{
    SPELL_SHADOW_FORM                   = 37802,

    SPELL_YOGG_LUNGE                    = 64123,
    SPELL_YOGG_SQUEEZE                  = 64125,
    SPELL_YOGG_SHADOWCRASH              = 60833,
    SPELL_YOGG_SHADOWCRASH_DMG          = 60835,
    SPELL_YOGG_VOID_ZONE_VISUAL         = 69422,
    SPELL_YOGG_SHADOW_NOVA              = 62714,
    SPELL_YOGG_DARK_VOLLEY              = 63038,
    SPELL_YOGG_INDUCE_MADNESS           = 64059,
    SPELL_YOGG_ARCANE_EXPLOSION         = 68002,
    SPELL_YOGG_ANTIMAGIC_ZONE           = 63894,
    SPELL_YOGG_TEMPORAL_VORTEX          = 52657,
    SPELL_YOGG_BERSERK                  = 68378,

    EVENT_YOGG_CONSTRICTOR_TENTACLE     = 1,
    EVENT_YOGG_CORRUPTOR_TENTACLE       = 2,
    EVENT_YOGG_BRAIN_CELL               = 3,

    NPC_CONSTRICTOR_TENTACLE            = 261012,
    NPC_SHADOWCRASH_CASTER              = 261013,
    NPC_SHADOWCRASH_TARGET              = 261014,
    NPC_YOGG_CHILDREN                   = 261015,
    NPC_CRUSHER_TENTACLE                = 261016,
    NPC_CORRUPTOR_TENTACLE              = 261017,
    NPC_YOGG_BRAIN                      = 261018,
    NPC_YOGG_BRAIN_CELL                 = 261019,

    ACTION_SECOND_PHASE                 = 1,

    // CRUSHER TENTACLE
    SPELL_CRUSH                         = 64146,
    SPELL_DIMINISH_POWER                = 64145,
    SPELL_FOCUSED_ANGER                 = 57688,
    SPELL_ERUPT_TENTACLE                = 64144,
    SPELL_VOID_ZONE_LARGE               = 64017,

    EVENT_ACTIVATE_CRUSHER              = 1,
    EVENT_FIND_NEAREST_PLAYER           = 2,

    // CORRUPTOR TENTACLE
    SPELL_APATHY                        = 64156,
    SPELL_BLACK_PLAGUE                  = 64153,
    SPELL_CURSE_OF_DOOM                 = 64157,
    SPELL_DRAINING_POISON               = 64152,

    SPELL_BLOODY_DEATH                  = 25770,

    STAT_YOGG_CONSTRICTOR_TIMER         = 917,
    STAT_YOGG_CORRUPTOR_TIMER           = 918,

    STAT_YOGG_CONSTRICTOR_HEALTH        = 919,
    STAT_YOGG_CONSTRICTOR_KILL_TIMER    = 920,

    STAT_YOGG_SHADOWCRASH_TIMER         = 921,
    STAT_YOGG_SHADOWCRASH_COUNT         = 922,
    STAT_YOGG_SHADOWCRASH_INCREASE_DMG  = 993,

    STAT_YOGG_CHILDREN_HEALTH           = 923,
    STAT_YOGG_CHILDREN_MEELE_DMG        = 924,
    STAT_YOGG_CHILDREN_VOLLEY_TIMER     = 925,
    STAT_YOGG_CHILDREN_VOLLEY_DMG       = 926,

    STAT_YOGG_CRUSHER_HEALTH            = 927,
    STAT_YOGG_CRUSHER_MEELE_DMG         = 928,

    STAT_YOGG_CORRUPTOR_HEALTH          = 929,
    STAT_YOGG_CORRUPTOR_DEBUFF_TIMER    = 930,

    STAT_YOGG_BRAIN_HEALTH              = 931,
    STAT_YOGG_BRAIN_SUMMON_CELL_TIMER   = 932,
    STAT_YOGG_BRAIN_SUMMON_CELL_COUNT   = 933,

    STAT_YOGG_BRAIN_CELL_HEALTH         = 934,
    STAT_YOGG_BRAIN_CELL_MEELE_DMG      = 935,
    STAT_YOGG_BRAIN_CELL_EXPLOSION_TIMER= 936,
    STAT_YOGG_BRAIN_WIPE_TIMER          = 937,
    STAT_YOGG_BRAIN_CELL_BUBBLE_DMG     = 992
};

const Position _shadowCrashCasterPosition { -20.16f, -219.13f, -60.55f, 3.14f };
const Position _brainSpawnPosition{ -63.48f, -213.86f, -77.51f, 0.f };

constexpr uint32 CRUSHER_TENTACLE_COUNT = 8;
std::array<Position, CRUSHER_TENTACLE_COUNT> _crusherTentaclePositions =
{
    {
        { -30.49f, -242.86f, -87.84f, 1.65f },
        { -28.41f, -181.80f, -89.17f, 5.43f },
        {  13.83f, -212.32f, -85.90f, 3.18f },
        { -65.29f, -215.10f, -84.35f, 0.01f },
        { -52.73f, -194.83f, -85.73f, 5.77f },
        { -1.10f,  -189.67f, -87.08f, 4.11f },
        { -3.58f,  -233.62f, -87.20f, 2.25f },
        { -52.27f, -230.20f, -85.74f, 0.53f }
    }
};
struct npc_hellforge_diablo_yoggAI : public ScriptedAI
{
public:
    npc_hellforge_diablo_yoggAI(Creature* creature) : ScriptedAI(creature), _summons(creature), _instance(me->GetInstanceScript()) { }

    void Reset() override
    {
        LoadStats();
        _events.Reset();
        _summons.DespawnAll();
        _events.ScheduleEvent(EVENT_YOGG_CONSTRICTOR_TENTACLE, _constrictorTentacleTimerFirst);
        _events.ScheduleEvent(EVENT_YOGG_CORRUPTOR_TENTACLE, _corruptorTentacleTimerFirst);
        me->SetCanMissSpells(false);
        me->SetSelectable(false);
        DoZoneInCombat();
        me->SummonCreature(NPC_SHADOWCRASH_CASTER, _shadowCrashCasterPosition);

        std::random_shuffle(_crusherTentaclePositions.begin(), _crusherTentaclePositions.end());

        me->SummonCreature(NPC_CRUSHER_TENTACLE, _crusherTentaclePositions[0]);
        me->SummonCreature(NPC_CRUSHER_TENTACLE, _crusherTentaclePositions[1]);
    }

    void LoadStats()
    {
        HellforgeStats stats = sWorldCache.GetStatValues({ STAT_YOGG_CONSTRICTOR_TIMER, STAT_YOGG_CORRUPTOR_TIMER });
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_YOGG_CONSTRICTOR_TIMER:
                {
                    _constrictorTentacleTimer = ref.second.StatValue;
                    _constrictorTentacleTimerFirst = _constrictorTentacleTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_YOGG_CORRUPTOR_TIMER:
                {
                    _corruptorTentacleTimer = ref.second.StatValue;
                    _corruptorTentacleTimerFirst = _corruptorTentacleTimer * ref.second.StatVariance;
                    break;
                }
            }
        }

    }

    void EnterEvadeMode() override
    {
        _summons.DespawnAll();
        ScriptedAI::EnterEvadeMode();
    }

    void JustDied(Unit* killer) override
    {
        _summons.DespawnAll();
    }

    void JustSummoned(Creature* creature) override
    {
        _summons.Summon(creature);
    }

    void DoAction(int32 action) override
    {
        if (action == ACTION_SECOND_PHASE)
        {
            _summons.Broadcast([&](Unit* summon) { if (summon->GetEntry() == NPC_CRUSHER_TENTACLE) summon->CastSpell(summon, SPELL_DIMINISH_POWER); });
            _events.CancelEvent(EVENT_YOGG_CORRUPTOR_TENTACLE);
            _events.CancelEvent(EVENT_YOGG_CONSTRICTOR_TENTACLE);
            me->SummonCreature(NPC_YOGG_BRAIN, _brainSpawnPosition);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);
        switch (_events.GetEvent())
        {
            case EVENT_YOGG_CONSTRICTOR_TENTACLE:
            {
                if (Unit * target = FindRandomTarget(SPELL_YOGG_SQUEEZE))
                    me->SummonCreature(NPC_CONSTRICTOR_TENTACLE, target->GetNearPositionFromPos(target->GetPosition(), 5.f));

                _events.RescheduleEvent(EVENT_YOGG_CONSTRICTOR_TENTACLE, _constrictorTentacleTimer);
                break;
            }
            case EVENT_YOGG_CORRUPTOR_TENTACLE:
            {
                if (Unit * target = FindRandomTarget())
                    me->SummonCreature(NPC_CORRUPTOR_TENTACLE, target->GetNearPositionFromPos(target->GetPosition(), 5.f));

                _events.RescheduleEvent(EVENT_YOGG_CORRUPTOR_TENTACLE, _corruptorTentacleTimer);
                break;
            }
        }

        DoMeleeAttackIfReady();
    }

    Player* FindRandomTarget(uint32 excludeAura = 0)
    {
        std::vector<uint64> possibleTargets;
        auto const& pl = me->GetMap()->GetPlayers();
        for (auto itr = pl.begin(); itr != pl.end(); ++itr)
        {
            Player* player = itr->GetSource();
            if (!player || player->IsGameMaster() || !player->IsInWorld() || player->isDead() || (excludeAura && player->HasAura(excludeAura) ))
                continue;
            possibleTargets.push_back(player->GetGUID());
        }
        if (!possibleTargets.empty())
            return ObjectAccessor::GetPlayer(*me, Trinity::Containers::SelectRandomContainerElement(possibleTargets));
        return nullptr;
    }

    void AttackStart(Unit* /*who*/) override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override { damage = 0; }

private:
    EventMap _events;
    SummonList _summons;
    InstanceScript* _instance;

    uint32 _constrictorTentacleTimer;
    uint32 _constrictorTentacleTimerFirst;

    uint32 _corruptorTentacleTimer;
    uint32 _corruptorTentacleTimerFirst;
};

struct boss_hellforge_diablo_yogg_constrictor_tentacleAI : public ScriptedAI
{
    boss_hellforge_diablo_yogg_constrictor_tentacleAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        SetCombatMovement(false);
        me->SetCanFly(true);
        me->SetDisableGravity(true);
        _checkTimer = 1;
        _playerGUID = 0;
    }

    uint32 _checkTimer;
    uint64 _playerGUID;

    void Reset() override
    {
        LoadStats();
        ScheduleGrabPlayer();
    }

    void LoadStats()
    {
        HellforgeStats stats = sWorldCache.GetStatValues({ STAT_YOGG_CONSTRICTOR_HEALTH, STAT_YOGG_CONSTRICTOR_KILL_TIMER });
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_YOGG_CONSTRICTOR_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_YOGG_CONSTRICTOR_KILL_TIMER:
                {
                    _killTimer = ref.second.StatValue;
                    break;
                }
            }
        }
    }

    void ScheduleGrabPlayer(bool first = true)
    {
        if (!first)
        {
            _scheduler.Schedule(3s, [&](TaskContext func)
            {
                if (Unit * target = SelectConstrictTarget(false))
                {
                    me->NearTeleportTo(target->GetPosition());
                    me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                    _playerGUID = target->GetGUID();
                }
            });
        }

        _scheduler.Schedule(1s, [&](TaskContext func)
        {
            Unit* target = nullptr;
            if (_playerGUID)
                target = ObjectAccessor::GetPlayer(*me, _playerGUID);
            else
                target = SelectConstrictTarget();

            if (target)
            {
                target->CastSpell(me, SPELL_YOGG_LUNGE, true);
                target->CastSpell(target, SPELL_YOGG_SQUEEZE, true);
                _playerGUID = target->GetGUID();

                _scheduler.Schedule(std::chrono::milliseconds(_killTimer), [&](TaskContext /*func*/)
                {
                    if (Player * player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                    {
                        player->RemoveAura(SPELL_YOGG_SQUEEZE);
                        me->RemoveAura(SPELL_YOGG_LUNGE);
                        player->Kill(me, player);
                        Position pos = me->GetPosition();
                        pos.RelocateOffset({ 0.f, 0.f, 10.f });
                        me->MovePositionToFirstCollision(pos, 100.f, frand(0, 2 * M_PI));
                        player->GetMotionMaster()->MoveJump(pos, 40.f, 20.f);
                        me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                        ScheduleGrabPlayer(false);
                        _playerGUID = 0;
                    }
                });

            }
            else
                func.Repeat(1s);
        });
    }

    Unit* SelectConstrictTarget(bool onlyNearPlayers = true)
    {
        Player* target = NULL;
        Map::PlayerList const& pList = me->GetMap()->GetPlayers();
        uint8 num = urand(0, pList.getSize() - 1);
        uint8 count = 0;
        for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr, ++count)
        {
            if (onlyNearPlayers && me->GetDistance(itr->GetSource()) > 10.f)
                continue;
            if (!itr->GetSource()->IsAlive() || itr->GetSource()->IsGameMaster())
                continue;
            if (itr->GetSource()->HasAura(SPELL_YOGG_SQUEEZE))
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
        _scheduler.Update(diff);
    }

    void JustDied(Unit*)
    {
        me->DespawnOrUnsummon(2s);
        if (Unit * player = ObjectAccessor::GetUnit(*me, _playerGUID))
            player->RemoveAura(SPELL_YOGG_SQUEEZE);
    }

private:
    TaskScheduler _scheduler;
    uint32 _killTimer;
};

struct boss_hellforge_diablo_yogg_shadowcrash_casterAI : ScriptedAI
{
public:
    boss_hellforge_diablo_yogg_shadowcrash_casterAI(Creature* creature) : ScriptedAI(creature), _shadowCrashCount(0){ }

    void Reset() override
    {
        LoadStats();
        ScheduleEvents();
        me->SetImmuneToPC(false);
        me->SetImmuneToNPC(false);
        me->SetCanMissSpells(false);
        me->CastCustomSpell(SPELL_YOGG_BERSERK, SPELLVALUE_BASE_POINT0, _increaseDMG);
    }

    void LoadStats()
    {
        HellforgeStats stats = sWorldCache.GetStatValues({ STAT_YOGG_SHADOWCRASH_TIMER, STAT_YOGG_SHADOWCRASH_COUNT, STAT_YOGG_SHADOWCRASH_INCREASE_DMG });
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_YOGG_SHADOWCRASH_TIMER:
                {
                    _shadowCrashTimer = ref.second.StatValue;
                    break;
                }
                case STAT_YOGG_SHADOWCRASH_COUNT:
                {
                    _shadowCrashMaxCount = ref.second.StatValue;
                    break;
                }
                case STAT_YOGG_SHADOWCRASH_INCREASE_DMG:
                {
                    _increaseDMG = ref.second.StatValue;
                    break;
                }

            }
        }
    }

    void ScheduleEvents()
    {
        _scheduler.Schedule(std::chrono::milliseconds(_shadowCrashTimer), [&](TaskContext func)
        {
            if (Unit * target = SelectTargetFromPlayerList(200.f, SPELL_YOGG_SQUEEZE))
            {
                me->CastCustomSpell(SPELL_YOGG_SHADOWCRASH, SPELLVALUE_SPELL_RANGE, 200, target, TRIGGERED_FULL_MASK);
                if (Creature * crashTarget = me->SummonCreature(NPC_SHADOWCRASH_TARGET, target->GetPosition()))
                    crashTarget->AI()->SetGUID(me->GetSummoner()->GetGUID());
            }
            if (++_shadowCrashCount >= _shadowCrashMaxCount)
            {
                if (Unit * unit = me->GetSummoner())
                    unit->GetAI()->DoAction(ACTION_SECOND_PHASE);
            }
            else
                func.Repeat(std::chrono::milliseconds(_shadowCrashTimer));
        });
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }
private:
    TaskScheduler _scheduler;
    uint32 _shadowCrashCount;

    uint32 _shadowCrashTimer;
    uint32 _shadowCrashMaxCount;
    uint32 _increaseDMG;
};

struct boss_hellforge_diablo_yogg_shadowcrash_targetAI : ScriptedAI
{
public:
    boss_hellforge_diablo_yogg_shadowcrash_targetAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        me->SetImmuneToNPC(false);
        me->setFaction(250);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        DoCastSelf(SPELL_YOGG_VOID_ZONE_VISUAL);
    }

    void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
    {
        if (spell && spell->Id == SPELL_YOGG_SHADOWCRASH_DMG)
        {
            if (Creature * creature = me->SummonCreature(NPC_YOGG_CHILDREN, me->GetPosition()))
            {
                if (Player * victim = creature->SelectNearestPlayer(100.f))
                    creature->Attack(victim, false);
                if (Creature * yogg = ObjectAccessor::GetCreature(*me, _yoggGUID))
                    yogg->AI()->JustSummoned(creature);
            }
            me->DespawnOrUnsummon();
        }
    }

    void SetGUID(uint64 guid, int32 /*id*/ = 0) override
    {
        _yoggGUID = guid;
    }
private:
    uint64 _yoggGUID;
};

struct boss_hellforge_diablo_yogg_childrenAI : ScriptedAI
{
    boss_hellforge_diablo_yogg_childrenAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        LoadStats();
        DoZoneInCombat();
        _scheduler.Schedule(std::chrono::milliseconds(_volleyTimerFirst), [&](TaskContext func)
        {
            me->CastCustomSpell(SPELL_YOGG_DARK_VOLLEY, SPELLVALUE_BASE_POINT0, _volleyDmg);
            DoCastAOE(SPELL_YOGG_DARK_VOLLEY);
            func.Repeat(std::chrono::milliseconds(_volleyTimer));
        });
        me->SetCanMissSpells(false);
    }

    void LoadStats()
    {
        HellforgeStats stats = sWorldCache.GetStatValues({ STAT_YOGG_CHILDREN_HEALTH, STAT_YOGG_CHILDREN_MEELE_DMG, STAT_YOGG_CHILDREN_VOLLEY_DMG, STAT_YOGG_CHILDREN_VOLLEY_TIMER });
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_YOGG_CHILDREN_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_YOGG_CHILDREN_MEELE_DMG:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case STAT_YOGG_CHILDREN_VOLLEY_TIMER:
                {
                    _volleyTimer = ref.second.StatValue;
                    _volleyTimerFirst = _volleyDmg * ref.second.StatVariance;
                    break;
                }
                case STAT_YOGG_CHILDREN_VOLLEY_DMG:
                {
                    _volleyDmg = ref.second.StatValue;
                    break;
                }
            }
        }
    }

    void JustDied(Unit* killer) override
    {
        DoCastAOE(SPELL_YOGG_SHADOW_NOVA, true);
        if (Creature * tentacle = me->FindNearestCreature(NPC_CRUSHER_TENTACLE, 10.f))
            me->DealDamage(me, tentacle, tentacle->GetMaxHealth() * 0.21f);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff);

        DoMeleeAttackIfReady();
    }

private:
    TaskScheduler _scheduler;

    uint32 _volleyTimer;
    uint32 _volleyTimerFirst;
    uint32 _volleyDmg;
};

struct boss_hellforge_diablo_yogg_crusher_tentacleAI : public ScriptedAI
{
    boss_hellforge_diablo_yogg_crusher_tentacleAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        SetCombatMovement(false);
        DoCastSelf(SPELL_VOID_ZONE_LARGE, true);
        DoCastAOE(SPELL_ERUPT_TENTACLE);
        me->AddUnitState(UNIT_STATE_UNATTACKABLE);
    }

    void Reset()
    {
        LoadStats();
        _events.Reset();
        me->SetReactState(REACT_PASSIVE);
        _events.ScheduleEvent(EVENT_ACTIVATE_CRUSHER, 2s);
        _events.ScheduleEvent(EVENT_FIND_NEAREST_PLAYER, 5s);
        me->SetInCombatWithZone();
    }

    void LoadStats()
    {
        HellforgeStats stats = sWorldCache.GetStatValues({ STAT_YOGG_CRUSHER_HEALTH, STAT_YOGG_CRUSHER_MEELE_DMG });
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_YOGG_CRUSHER_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_YOGG_CRUSHER_MEELE_DMG:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
            }
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->DespawnOrUnsummon(2s);
    }

    void UpdateAI(uint32 diff)
    {
        _events.Update(diff);
        switch(_events.GetEvent())
        {
            case EVENT_ACTIVATE_CRUSHER:
            {
                me->SetReactState(REACT_AGGRESSIVE);
                DoZoneInCombat(me, 200.f);
                me->CastSpell(me, SPELL_CRUSH, true);
                //me->CastSpell(me, SPELL_FOCUSED_ANGER, true);
                _events.PopEvent();
                break;
            }
            case EVENT_FIND_NEAREST_PLAYER:
            {
                if (Player * player = me->SelectNearestPlayer(10.f))
                    me->Attack(player, false);
                _events.PopEvent();
                break;
            }
        }

        if (me->HasReactState(REACT_PASSIVE))
            return;

        if (me->IsWithinMeleeRange(me->GetVictim()))
            DoMeleeAttackIfReady();
        else
            _events.ScheduleEvent(EVENT_FIND_NEAREST_PLAYER, 1s);
    }
private:
    EventMap _events;
};

struct boss_hellforge_diablo_yogg_corruptor_tentacleAI : public ScriptedAI
{
    boss_hellforge_diablo_yogg_corruptor_tentacleAI(Creature* pCreature) : ScriptedAI(pCreature) { }

    void Reset() override
    {
        LoadStats();
        SetCombatMovement(false);
        DoCastSelf(SPELL_VOID_ZONE_LARGE, true);
        _scheduler.Schedule(std::chrono::milliseconds(_debuffTimer), [&](TaskContext func)
        {
            CastDebuff();
            func.Repeat(std::chrono::milliseconds(_debuffTimer));
        });
    }

    void JustDied(Unit* killer) override
    {
        me->DespawnOrUnsummon(2s);
    }

    void LoadStats()
    {
        HellforgeStats stats = sWorldCache.GetStatValues({ STAT_YOGG_CORRUPTOR_HEALTH, STAT_YOGG_CORRUPTOR_DEBUFF_TIMER });
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_YOGG_CORRUPTOR_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_YOGG_CORRUPTOR_DEBUFF_TIMER:
                {
                    _debuffTimer = ref.second.StatValue;
                    break;
                }
            }
        }
    }

    Unit* SelectCorruptionTarget()
    {
        Player* target = NULL;
        Map::PlayerList const& pList = me->GetMap()->GetPlayers();
        uint8 num = urand(0, pList.getSize() - 1);
        uint8 count = 0;
        for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr, ++count)
        {
            if (me->GetDistance(itr->GetSource()) > 200.f || !itr->GetSource()->IsAlive() || itr->GetSource()->IsGameMaster())
                continue;

            if (count <= num || !target)
                target = itr->GetSource();
            else
                break;
        }

        return target;
    }

    void CastDebuff()
    {
        if (Unit * target = SelectCorruptionTarget())
        {
            uint32 spellid = RAND(SPELL_APATHY, SPELL_BLACK_PLAGUE, SPELL_DRAINING_POISON, SPELL_CURSE_OF_DOOM);
            me->CastSpell(target, spellid, false);
        }
    }

    void UpdateAI(uint32 diff)
    {
        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;
        _scheduler.Update(diff);
    }

private:
    TaskScheduler _scheduler;
    uint32 _debuffTimer;
};

struct boss_hellforge_diablo_yogg_brainAI : public ScriptedAI
{
    boss_hellforge_diablo_yogg_brainAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        LoadStats();
        _scheduler.CancelAll();
        ScheduleEvents();
        SetCombatMovement(false);
        DoZoneInCombat();
    }

    void LoadStats()
    {
        HellforgeStats stats = sWorldCache.GetStatValues({ STAT_YOGG_BRAIN_HEALTH, STAT_YOGG_BRAIN_SUMMON_CELL_TIMER, STAT_YOGG_BRAIN_SUMMON_CELL_COUNT, STAT_YOGG_BRAIN_WIPE_TIMER });
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_YOGG_BRAIN_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_YOGG_BRAIN_SUMMON_CELL_TIMER:
                {
                    _summonCellTimer = ref.second.StatValue;
                    break;
                }
                case STAT_YOGG_BRAIN_SUMMON_CELL_COUNT:
                {
                    _summonCellCount = ref.second.StatValue;
                    break;
                }
                case STAT_YOGG_BRAIN_WIPE_TIMER:
                {
                    _wipeTimer = ref.second.StatValue;
                    me->SetFloatValue(UNIT_MOD_CAST_SPEED, _wipeTimer / 60.f);
                    break;
                }

            }
        }
    }

    void ScheduleEvents()
    {
        _scheduler.Schedule(std::chrono::milliseconds(_wipeTimer * 1000 + 2000), [&](TaskContext /*func*/)
        {
            WipeEntireMap();
        });

        _scheduler.Schedule(2s, [&](TaskContext /*func*/)
        {
            DoCastAOE(SPELL_YOGG_INDUCE_MADNESS);
        });

        _scheduler.Schedule(std::chrono::milliseconds(_summonCellTimer), [&](TaskContext func)
        {
            for (uint32 i = 0; i < _summonCellCount; ++i)
            {
                if(Unit* target = SelectTargetFromPlayerList(200.f))
                {
                    Position pos = target->GetNearPositionFromPos(target->GetPosition(), 20.f);
                    pos.RelocateOffset({ 0.f, 0.f, 20.f });
                    if (Creature * spark = me->SummonCreature(NPC_YOGG_BRAIN_CELL, pos) )
                    {
                        spark->Attack(target, false);
                        if (Creature * yogg = me->GetSummoner())
                            yogg->AI()->JustSummoned(spark);
                    }
                }
            }
            func.Repeat(std::chrono::milliseconds(_summonCellTimer));
        });

    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

    void WipeEntireMap()
    {
        auto const& _players = me->GetMap()->GetPlayers();
        for (auto&& source : _players)
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

    void JustDied(Unit* killer)
    {
        if (Unit * summoner = me->GetSummoner())
            Unit::Kill(killer, summoner);
    }
private:
    TaskScheduler _scheduler;
    uint32 _summonCellTimer;
    uint32 _summonCellCount;
    uint32 _wipeTimer;
};

struct boss_hellforge_diablo_yogg_brain_cellAI : public ScriptedAI
{
    boss_hellforge_diablo_yogg_brain_cellAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset()
    {
        LoadStats();
        _scheduler.CancelAll();

        me->SetInhabitType(INHABIT_ANYWHERE);
        me->SetCanFly(true);
        me->SetDisableGravity(true);
    }

    void LoadStats()
    {
        HellforgeStats stats = sWorldCache.GetStatValues({ STAT_YOGG_BRAIN_CELL_HEALTH, STAT_YOGG_BRAIN_CELL_MEELE_DMG, STAT_YOGG_BRAIN_CELL_EXPLOSION_TIMER, STAT_YOGG_BRAIN_CELL_BUBBLE_DMG });
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_YOGG_BRAIN_CELL_HEALTH:
                {
                    me->SetMaxHealth(urand(ref.second.StatValue * ref.second.StatVariance, ref.second.StatValue ));
                    me->SetFullHealth();
                    break;
                }
                case STAT_YOGG_BRAIN_CELL_MEELE_DMG:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case STAT_YOGG_BRAIN_CELL_EXPLOSION_TIMER:
                {
                    _explosionTimer = ref.second.StatValue;
                    break;
                }
                case STAT_YOGG_BRAIN_CELL_BUBBLE_DMG:
                {
                    _bubbleDmg = ref.second.StatValue;
                    break;
                }
            }
        }
    }

    void EnterCombat(Unit* victim) override
    {
        DoZoneInCombat();
        _scheduler.Schedule(std::chrono::milliseconds(_explosionTimer), [&](TaskContext func)
        {
            DoCastAOE(SPELL_YOGG_ARCANE_EXPLOSION);
            func.Repeat(std::chrono::milliseconds(_explosionTimer));
        });
    }

    void EnterEvadeMode() override { }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override 
    { 
        if (damage >= me->GetHealth())
        {
            _scheduler.CancelAll();
            me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->SetControlled(true, UNIT_STATE_ROOT);
            damage = 0;
            me->SetDisplayId(11686);
            me->SetSelectable(false);
            me->SetObjectScale(0.3f);
            me->GetMotionMaster()->MoveFall();
            me->DisableRotate(true);
            me->SetPassive();

            _scheduler.Schedule(600ms, [this](TaskContext func)
            {
                DoCastSelf(SPELL_YOGG_ANTIMAGIC_ZONE);
            });

            _scheduler.Schedule(3s, [this](TaskContext func)
            {
                std::list<Player*> targets;
                Trinity::AnyPlayerInObjectRangeCheck check(me, 3.5f, true);
                Trinity::PlayerListSearcherWithSharedVision<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, targets, check);
                me->VisitNearbyWorldObject(3.5f, searcher);

                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_YOGG_TEMPORAL_VORTEX);
                for (auto const& player : targets)
                {
                    if (player->IsGameMaster() || player->isDead())
                        continue;

                    if (spellInfo)
                    {
                        int32 base[3] = { (int32)_bubbleDmg - 1, -70, -70 };
                        Aura::TryRefreshStackOrCreate(spellInfo, MAX_EFFECT_MASK, player, me, base);
                    }
                }
                func.Repeat(3s);
            });
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff);
        
        if (!me->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH))
            DoMeleeAttackIfReady();
    }

private:
    TaskScheduler _scheduler;
    uint32 _explosionTimer;
    uint32 _bubbleDmg;
};

void AddSC_hellforge_boss_diablo_yogg()
{
    new CreatureAILoader<npc_hellforge_diablo_yoggAI>("boss_hellforge_diablo_yogg");
    new CreatureAILoader<boss_hellforge_diablo_yogg_constrictor_tentacleAI>("boss_hellforge_diablo_yogg_constrictor_tentacle");
    new CreatureAILoader<boss_hellforge_diablo_yogg_crusher_tentacleAI>("boss_hellforge_diablo_yogg_crusher_tentacle");
    new CreatureAILoader<boss_hellforge_diablo_yogg_corruptor_tentacleAI>("boss_hellforge_diablo_yogg_corruptor_tentacle");
    new CreatureAILoader<boss_hellforge_diablo_yogg_shadowcrash_casterAI>("boss_hellforge_diablo_yogg_shadowcrash_caster");
    new CreatureAILoader<boss_hellforge_diablo_yogg_shadowcrash_targetAI>("boss_hellforge_diablo_yogg_shadowcrash_target");
    new CreatureAILoader<boss_hellforge_diablo_yogg_childrenAI>("boss_hellforge_diablo_yogg_children");
    new CreatureAILoader<boss_hellforge_diablo_yogg_brainAI>("boss_hellforge_diablo_yogg_brain");
    new CreatureAILoader<boss_hellforge_diablo_yogg_brain_cellAI>("boss_hellforge_diablo_yogg_brain_cell");
}
