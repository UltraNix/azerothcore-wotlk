#include "ScriptedCreature.h"
#include "MoveSplineInit.h"
#include "Vehicle.h"
#include "WorldCache.h"
#include <numeric>

enum DiabloLichKingData
{
    SPELL_SHADOW_FORM               = 37802,

    SPELL_LK_INFEST                 = 70541,
    SPELL_LK_SOUL_REAPER            = 69409,
    SPELL_LK_RAGING_SPIRIT          = 69200,
    SPELL_LK_BLADESTORM             = 26083,
    SPELL_LK_CLEAVE                 = 15496,
    SPELL_LK_BOSS_HITTIN_YA_AURA    = 73879,
    SPELL_LK_COLDFLAME              = 70825,
    SPELL_LK_DEFILE_AURA            = 72743,
    SPELL_LK_DEFILE_GROWTH_AURA     = 72756,
    SPELL_LK_REDUCE_DMG             = 66243,


    EVENT_LK_DEFILE                 = 1,
    EVENT_LK_INFEST                 = 2,
    EVENT_LK_SOUL_REAPER            = 3,
    EVENT_LK_RAGING_SPIRIT          = 4,
    EVENT_LK_SPAWN_VALKYR           = 5,
    EVENT_LK_COLDFLAME              = 6,
    EVENT_LK_BLADESTORM             = 7,
    EVENT_LK_CLEAVE                 = 8,
    EVENT_LK_BOSS_HITTIN_YA         = 9,

    EVENT_GRAB_PLAYER               = 100,
    EVENT_MOVE_TO_DROP_POS          = 101,

    POINT_DROP_PLAYER               = 1,

    NPC_LK_VALKYR_SHADOWGUARD       = 261009,
    NPC_LK_FROSTMOURNE              = 261010,
    NPC_LK_COLDFLAME_SUMMONER       = 261021,
    NPC_LK_COLDFLAME                = 261022,
    NPC_LK_DEFILE                   = 261023,

    ITEM_LK_FROSTMOURNE             = 49706,

    // Val'kyr Shadowguard spells
    SPELL_VALKYR_TARGET_SEARCH      = 69030,
    SPELL_CHARGE                    = 74399,
    SPELL_VALKYR_CARRY              = 74445,
    SPELL_EJECT_ALL_PASSENGERS      = 68576,

    ACTION_PLAYER_KILLED            = 1,

    STAT_LK_HEALTH                  = 971,
    STAT_LK_MEELE_DMG               = 972,
    STAT_LK_INFEST_TIMER            = 973,
    STAT_LK_SOUL_REAPER_TIMER       = 974,
    STAT_LK_RAGING_SPIRIT_TIMER     = 975,
    STAT_LK_SPAWN_VALKYR_TIMER      = 976,
    STAT_LK_DEFILE_TIMER            = 977,
    STAT_LK_DEFILE_TIMER_FIRST      = 978,

    STAT_LK_VALKYR_HEALTH           = 979,

    STAT_LK_FM_HEALTH               = 980,
    STAT_LK_FM_MEELE_DMG            = 981,
    STAT_LK_FM_COLDFLAME_TIMER      = 982,
    STAT_LK_FM_BLADESTORM_TIMER     = 983,
    STAT_LK_FM_CLEAVE_TIMER         = 984
};

Position const DiabloPosition { -26.65f, -211.73f, -83.34f, 3.18f };
Position const ValkyrSpawnPosition { -32.92f, -213.45f, -67.20f, 6.12f };

struct npc_hellforge_diablo_lichkingAI : public ScriptedAI
{
public:
    npc_hellforge_diablo_lichkingAI(Creature* creature) : ScriptedAI(creature), _summons(creature), _secondPhase(false) { }

    void Reset() override
    {
        LoadStats();
        _events.Reset();
        DoCastSelf(SPELL_SHADOW_FORM);
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, ITEM_LK_FROSTMOURNE);
        _secondPhase = false;
        me->SetCanMissSpells(false);

        me->SetPassive();
        Position pos;
        me->GetNearPosition(pos, 10.f, 0.f);
        me->SetWalk(true);
        me->GetMotionMaster()->MovePoint(1, pos);
        me->SetImmuneToPC(true);
    }

    void LoadStats()
    {
        std::vector<uint32> statsIds;
        statsIds.resize(STAT_LK_DEFILE_TIMER_FIRST - STAT_LK_HEALTH + 1);
        std::iota(statsIds.begin(), statsIds.end(), (uint32)STAT_LK_HEALTH);
        HellforgeStats stats = sWorldCache.GetStatValues(statsIds);

        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_LK_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_LK_MEELE_DMG:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);;
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case STAT_LK_INFEST_TIMER:
                {
                    _infestTimer = ref.second.StatValue;
                    _infestTimerFirst = _infestTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_LK_SOUL_REAPER_TIMER:
                {
                    _soulReaperTimer = ref.second.StatValue;
                    _soulReaperTimerFirst = _infestTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_LK_RAGING_SPIRIT_TIMER:
                {
                    _ragingSpiritTimer = ref.second.StatValue;
                    _ragingSpiritTimerFirst = _ragingSpiritTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_LK_SPAWN_VALKYR_TIMER:
                {
                    _spawnValkyrTimer = ref.second.StatValue;
                    _spawnValkyrTimerFirst = _spawnValkyrTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_LK_DEFILE_TIMER:
                {
                    _defileTimer = ref.second.StatValue;
                    _defileTimerSecondPhase = ref.second.StatValue * ref.second.StatVariance;
                    break;
                }
                case STAT_LK_DEFILE_TIMER_FIRST:
                {
                    _defileTimerFirst = ref.second.StatValue;
                    break;
                }
            }
        }

    }

    void MovementInform(uint32 type, uint32 point) override
    {
        if (type == POINT_MOTION_TYPE && point == 1)
        {
            me->SetAggressive();
            me->SetWalk(false);
            me->SetImmuneToPC(false);
            if (Player * victim = me->SelectNearestPlayer(200.f))
                me->Attack(victim, false);
        }
    }

    void EnterEvadeMode() override
    {
        _summons.DespawnAll();
        ScriptedAI::EnterEvadeMode();

        if (Creature * diablo = me->GetSummoner())
            diablo->AI()->EnterEvadeMode();
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override 
    { 
        if (!_secondPhase && me->HealthBelowPctDamaged(30, damage))
        {
            _events.CancelEvent(EVENT_LK_SPAWN_VALKYR);
            _events.CancelEvent(EVENT_LK_RAGING_SPIRIT);
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 0);
            Position pos;
            me->GetNearPosition(pos, 5.f, M_PI / 2.f);
            me->SummonCreature(NPC_LK_FROSTMOURNE, pos);
            _secondPhase = true;
        }
    }

    void EnterCombat(Unit* /*victim*/)
    {
        me->MonsterYell("How is this possible? I've been summoned? You will regret it...", LANG_UNIVERSAL, me);
        DoZoneInCombat();
        _events.ScheduleEvent(EVENT_LK_DEFILE, _defileTimerFirst);
        _events.ScheduleEvent(EVENT_LK_INFEST, _infestTimerFirst);
        _events.ScheduleEvent(EVENT_LK_SOUL_REAPER, _soulReaperTimerFirst);
        _events.ScheduleEvent(EVENT_LK_RAGING_SPIRIT, _ragingSpiritTimerFirst);
        _events.ScheduleEvent(EVENT_LK_SPAWN_VALKYR, _spawnValkyrTimerFirst);
        _events.ScheduleEvent(EVENT_LK_BOSS_HITTIN_YA, 3s);
    }

    void JustSummoned(Creature* creature) override
    {
        _summons.Summon(creature);
        if (Creature * diablo = me->GetSummoner())
            diablo->AI()->JustSummoned(creature);

        if (Creature * diablo = me->GetSummoner())
            diablo->AI()->JustSummoned(creature);
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->MonsterYell("I... I failed you father...", LANG_UNIVERSAL, me);
        _summons.DespawnAll();
    }

    void DoAction(int32 action) override
    {
        if (action == ACTION_PLAYER_KILLED)
        {
            if(!urand(0,3))
                me->MonsterYell(urand(0,1) ? "The end has come!" : "Begone!", LANG_UNIVERSAL, me);
        }
    }

    void KilledUnit(Unit* victim) override
    {
        if (!victim->IsPlayer())
            DoAction(ACTION_PLAYER_KILLED);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        switch (_events.GetEvent())
        {
            case EVENT_LK_DEFILE:
            {
                if (Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.f, true, -SPELL_VALKYR_TARGET_SEARCH))
                {
                    me->MonsterYell("Are you ready for reversed one?", LANG_UNIVERSAL, me);
                    Position pos = target->GetPosition();
                    pos.RelocateOffset({ 0.f, 0.f, 1.f });
                    if (Creature * defile = me->SummonCreature(NPC_LK_DEFILE, pos))
                    {
                        defile->SetInhabitType(INHABIT_AIR);
                        defile->SetCanFly(true);
                        defile->SetDisableGravity(true);
                        defile->SetControlled(true, UNIT_STATE_ROOT);
                    }
                }
                _events.RescheduleEvent(EVENT_LK_DEFILE, _secondPhase ? _defileTimerSecondPhase : _defileTimer);
                break;
            }
            case EVENT_LK_INFEST:
            {
                me->CastSpell(me, SPELL_LK_INFEST, false);
                _events.RescheduleEvent(EVENT_LK_INFEST, _infestTimer);
                break;
            }
            case EVENT_LK_SOUL_REAPER:
            {
                DoCastVictim(SPELL_LK_SOUL_REAPER);
                _events.RescheduleEvent(EVENT_LK_SOUL_REAPER, _soulReaperTimer);
                break;
            }
            case EVENT_LK_RAGING_SPIRIT:
            {
                if (Unit * target = SelectTarget(SELECT_TARGET_RANDOM,0, 200.f, true, -SPELL_VALKYR_TARGET_SEARCH))
                    me->CastSpell(target, SPELL_LK_RAGING_SPIRIT);
                _events.RescheduleEvent(EVENT_LK_RAGING_SPIRIT, _ragingSpiritTimer);
                break;
            }
            case EVENT_LK_SPAWN_VALKYR:
            {
                me->MonsterYell("Val'kyr, your master calls! Take them to Diablo!", LANG_UNIVERSAL, me);
                me->SummonCreature(NPC_LK_VALKYR_SHADOWGUARD, ValkyrSpawnPosition);
                _events.RescheduleEvent(EVENT_LK_SPAWN_VALKYR, _spawnValkyrTimer);
                break;
            }
            case EVENT_LK_BOSS_HITTIN_YA:
            {
                me->CastCustomSpell(SPELL_LK_BOSS_HITTIN_YA_AURA, SPELLVALUE_AURA_DURATION, 5000, me->GetVictim());
                _events.RescheduleEvent(EVENT_LK_BOSS_HITTIN_YA, 3s);
                break;
            }
        }

        DoMeleeAttackIfReady();
    }
    bool CanAIAttack(Unit const* target) const
    {
        return target->GetVehicle() ? false : ScriptedAI::CanAIAttack(target);
    }
private:
    EventMap _events;
    SummonList _summons;
    bool _secondPhase;

    uint32 _infestTimer;
    uint32 _infestTimerFirst;
    uint32 _soulReaperTimer;
    uint32 _soulReaperTimerFirst;
    uint32 _ragingSpiritTimer;
    uint32 _ragingSpiritTimerFirst;
    uint32 _spawnValkyrTimer;
    uint32 _spawnValkyrTimerFirst;
    uint32 _defileTimer;
    uint32 _defileTimerSecondPhase;
    uint32 _defileTimerFirst;
};

struct npc_hellforge_diablo_valkyr_shadowguardAI : public ScriptedAI
{
    npc_hellforge_diablo_valkyr_shadowguardAI(Creature* creature) : ScriptedAI(creature), _grabbedPlayer(0), dropped(false), _instance(creature->GetInstanceScript()) { }

    void Reset() override
    {
        // me->SetReactState(REACT_PASSIVE);
        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
        _events.Reset();
        _events.ScheduleEvent(EVENT_GRAB_PLAYER, 2500);
        me->SetWalk(false);
        DoCastSelf(SPELL_SHADOW_FORM);

        LoadStats();
    }

    void LoadStats()
    {
        HellforgeStatValues val;
        sWorldCache.GetStatValue(STAT_LK_VALKYR_HEALTH, val);
        me->SetMaxHealth(val.StatValue);
        me->SetFullHealth();
    }

    void OnCharmed(bool apply) { }
    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }

    void PassengerBoarded(Unit* pass, int8 seat, bool apply) 
    {
        if (apply)
        {
            /// !HACK!
            /// Lack of attachment calculations, gotta do it this way
            /// We need to figure out where blizzard stores vehicle seat attachment offsets
            Movement::MoveSplineInit init(pass);
            init.DisableTransportPathTransformations();
            init.MoveTo(0.4018555f, -2.024658f, -4.000122f, false);
            init.SetFacing(3.141593f);
            init.Launch();
            return;
        }
        pass->RemoveAurasDueToSpell(VEHICLE_SPELL_PARACHUTE);
        if (dropped)
            return;
        me->DespawnOrUnsummon(1000);
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type != POINT_MOTION_TYPE)
            return;

        switch (id)
        {
            case EVENT_CHARGE:
            {
                bool valid = false;
                if (Player * target = ObjectAccessor::GetPlayer(*me, _grabbedPlayer))
                    if (target->FindMap() == me->GetMap() && target->GetExactDist(me) < 15.0f && !target->GetVehicle())
                    {
                        valid = true;

                        target->GetMotionMaster()->Clear();
                        target->UpdatePosition(*me, true);
                        target->StopMovingOnCurrentPos();
                        target->SendMeleeAttackStop();

                        me->CastSpell(target, SPELL_VALKYR_CARRY, false);
                        _destPoint.Relocate(DiabloPosition);
                        _events.Reset();
                        _events.ScheduleEvent(EVENT_MOVE_TO_DROP_POS, 1000);
                    }
                        
                if (!valid)
                {
                    _events.Reset();
                    _events.ScheduleEvent(EVENT_GRAB_PLAYER, 500);
                    _grabbedPlayer = 0;
                }
                break;
            }
            case POINT_DROP_PLAYER:
            {
                if (dropped)
                    break;
                if (me->GetExactDist(&_destPoint) > 1.5f) // movement was interrupted (probably by a stun, start again)
                {
                    _events.Reset();
                    _events.ScheduleEvent(EVENT_MOVE_TO_DROP_POS, 0);
                    break;
                }
                dropped = true;
                _events.Reset();
                me->CastSpell((Unit*)NULL, SPELL_EJECT_ALL_PASSENGERS, false);
                me->MonsterSay("Order completed my king.", LANG_UNIVERSAL, 0);
                me->DespawnOrUnsummon(1000);
                break;
            }
        }
    }

    void SetGUID(uint64 guid, int32 /* = 0*/)
    {
        _grabbedPlayer = guid;
    }

    void ValkyrVictimUpdate()
    {
        if (!me->IsInCombat())
            return;

        if (me->getThreatManager().isThreatListEmpty())
        {
            EnterEvadeMode();
            return;
        }

        if (Unit * victim = me->SelectVictim())
            AttackStart(victim);
    }

    void UpdateAI(uint32 diff)
    {
        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING | UNIT_STATE_STUNNED))
            return;

        switch (uint32 eventId = _events.ExecuteEvent())
        {
        case EVENT_GRAB_PLAYER:
            if (!_grabbedPlayer)
            {
                DoZoneInCombat();
                me->CastSpell((Unit*)NULL, SPELL_VALKYR_TARGET_SEARCH, false);
                _events.ScheduleEvent(EVENT_GRAB_PLAYER, 2000);
            }
            break;
        case EVENT_MOVE_TO_DROP_POS:
            me->AddUnitState(UNIT_STATE_NO_ENVIRONMENT_UPD);
            me->SetDisableGravity(false);
            me->SetHover(false);
            me->SetCanFly(false);
            me->GetMotionMaster()->MovePoint(POINT_DROP_PLAYER, _destPoint, false);
            me->SetDisableGravity(true, true);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            break;
        default:
            break;
        }
    }
private:
    EventMap _events;
    InstanceScript* _instance;
    Position _destPoint;
    uint64 _grabbedPlayer;
    bool dropped;
};

struct npc_hellforge_diablo_frostmourneAI : ScriptedAI
{
public:
    npc_hellforge_diablo_frostmourneAI(Creature* creature) : ScriptedAI(creature), _summons(me) { }

    void Reset() override
    {
        _events.Reset();
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, ITEM_LK_FROSTMOURNE);
        me->SetObjectScale(2.f);
        LoadStats();
        me->SetCanMissSpells(false);
    }

    void LoadStats()
    {
        std::vector<uint32> statsIds;
        statsIds.resize(STAT_LK_FM_CLEAVE_TIMER - STAT_LK_FM_HEALTH + 1);
        std::iota(statsIds.begin(), statsIds.end(), (uint32)STAT_LK_FM_HEALTH);
        HellforgeStats stats = sWorldCache.GetStatValues(statsIds);
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_LK_FM_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_LK_FM_MEELE_DMG:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case STAT_LK_FM_COLDFLAME_TIMER:
                {
                    _coldFlameTimer = ref.second.StatValue;
                    break;
                }
                case STAT_LK_FM_BLADESTORM_TIMER:
                {
                    _bladestormTimer = ref.second.StatValue;
                    break;
                }
                case STAT_LK_FM_CLEAVE_TIMER:
                {
                    _cleaveTimer = ref.second.StatValue;
                    break;
                }
            }
        }
    }

    void EnterEvadeMode() override
    {
        _summons.DespawnAll();
    }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);
    }

    void KilledUnit(Unit* victim) override
    {
        if (!victim->IsPlayer())
        {
            if(Creature* lichking = me->GetSummoner())
                lichking->GetAI()->DoAction(ACTION_PLAYER_KILLED);
        }
    }

    void IsSummonedBy(Unit* /*summoner*/)
    {
        if (Unit * target = me->SelectNearestPlayer(100.f))
        {
            me->Attack(target, false);
            DoZoneInCombat();
        }
    }

    void EnterCombat(Unit* victim) override
    {
        _events.ScheduleEvent(EVENT_LK_COLDFLAME, _coldFlameTimer);
        _events.ScheduleEvent(EVENT_LK_BLADESTORM, _bladestormTimer);
        _events.ScheduleEvent(EVENT_LK_CLEAVE, _cleaveTimer);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        switch (_events.GetEvent())
        {
            case EVENT_LK_COLDFLAME:
            {
                std::array<uint32, 4> directions = { 0, 1, 2 ,3 };
                Trinity::Containers::RandomShuffle(directions);

                Position pos = me->GetPosition();
                Creature* lichKing = me->GetSummoner();

                for (uint32 i = 0; i < 2; ++i)
                {
                    if (Creature * coldflame = me->SummonCreature(NPC_LK_COLDFLAME_SUMMONER, pos))
                    {
                        if (lichKing)
                            coldflame->AI()->SetGUID(lichKing->GetGUID());
                        coldflame->AI()->SetData(1, directions[i]);
                    }
                }
                
                _events.RescheduleEvent(EVENT_LK_COLDFLAME, _coldFlameTimer);
                break;
            }
            case EVENT_LK_BLADESTORM:
            {
                if (Aura * aura = me->AddAura(SPELL_LK_REDUCE_DMG, me))
                {
                    aura->SetMaxDuration(8000);
                    aura->RefreshDuration();
                }
                DoCastVictim(SPELL_LK_BLADESTORM);
                if (Aura * aura = me->GetAura(SPELL_LK_BLADESTORM))
                {
                    aura->SetMaxDuration(8000);
                    aura->RefreshDuration();
                }
                _events.RescheduleEvent(EVENT_LK_BLADESTORM, _bladestormTimer);
                break;
            }
            case EVENT_LK_CLEAVE:
            {
                DoCastVictim(SPELL_LK_CLEAVE);
                _events.RescheduleEvent(EVENT_LK_CLEAVE, _cleaveTimer);
                break;
            }
        }

        DoMeleeAttackIfReady();

    }
private:
    EventMap _events;
    SummonList _summons;

    uint32 _coldFlameTimer;
    uint32 _bladestormTimer;
    uint32 _cleaveTimer;
};

struct boss_hellforge_diablo_lk_coldflame_summonerAI : public ScriptedAI
{
    boss_hellforge_diablo_lk_coldflame_summonerAI(Creature* creature) : ScriptedAI(creature) { }
    
    void Reset() override
    {
        me->SetCanFly(false);
        me->SetDisableGravity(false);
        me->SetInhabitType(INHABIT_GROUND);

        if (Creature * lichking = me->GetSummoner())
            lichking->AI()->JustSummoned(me);
    }

    void SetData(uint32 /*id*/, uint32 value) override
    {
        Position pos = me->GetPosition();
        pos.RelocateOffset({ 0.f,0.f,2.f });
        me->MovePosition(pos, 50.f, (M_PI / 2.f) * value);
        me->UpdateAllowedPositionZ(pos.m_positionX, pos.m_positionY, pos.m_positionZ);
        me->GetMotionMaster()->MovePoint(1, pos);

        _scheduler.Schedule(1ms, [&](TaskContext func)
        {
            if (Creature * coldflame = me->SummonCreature(NPC_LK_COLDFLAME, me->GetPosition()))
                coldflame->AI()->SetGUID(_lichKingGuid);
            func.Repeat(700ms);
        });

    }

    void SetGUID(uint64 guid, int32 /* = 0*/)
    {
        _lichKingGuid = guid;
    }

    void MovementInform(uint32 type, uint32 point)
    {
        if (type == POINT_MOTION_TYPE && point == 1)
            me->DespawnOrUnsummon();
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

private:
    TaskScheduler _scheduler;
    uint64 _lichKingGuid;
};

struct boss_hellforge_diablo_lk_coldflameAI : public ScriptedAI
{
    boss_hellforge_diablo_lk_coldflameAI(Creature* creature) : ScriptedAI(creature) { }
    void Reset() override
    {
        me->SetImmuneToPC(false);
        _scheduler.Schedule(500ms, [&](TaskContext func)
        {
            DoCastAOE(SPELL_LK_COLDFLAME);
            func.Repeat(3s);
        });
        me->DespawnOrUnsummon(20s);
        me->SetControlled(true, UNIT_STATE_ROOT);
        me->SetPassive();
    }

    void SetGUID(uint64 guid, int32 /* = 0*/)
    {
        if (Creature * lichKing = ObjectAccessor::GetCreature(*me, guid))
        {
            lichKing->AI()->JustSummoned(me);
        }
        _lichKingGUID = guid;
    }

    void UpdateAI(uint32 diff)
    {
        _scheduler.Update(diff);
    }

    void KilledUnit(Unit* victim) override
    {
        if (!victim->IsPlayer())
        {
            if (Creature * lichking = ObjectAccessor::GetCreature(*me, _lichKingGUID))
                lichking->GetAI()->DoAction(ACTION_PLAYER_KILLED);
        }
    }

private:
    TaskScheduler _scheduler;
    uint64 _lichKingGUID;
};

struct boss_hellforge_diablo_lk_defileAI : ScriptedAI
{
    boss_hellforge_diablo_lk_defileAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset()
    {
        me->SetImmuneToPC(false);
        me->CastCustomSpell(SPELL_LK_DEFILE_AURA, SPELLVALUE_AURA_DURATION, 300000, me);
        if (Aura * defile = me->AddAura(SPELL_LK_DEFILE_GROWTH_AURA, me))
        {
            defile->SetStackAmount(5);
        }

        _scheduler.Schedule(1s, [this](TaskContext func)
        {
            if (Aura * defile = me->GetAura(SPELL_LK_DEFILE_GROWTH_AURA))
            {
                defile->SetStackAmount(std::min(defile->GetStackAmount() + 1, 255));
            }   
            func.Repeat(3s);
        });
    }

    void DoAction(int32 action)
    {
        _scheduler.CancelAll();
        me->SetObjectScale(0.1f);
        me->DespawnOrUnsummon(1.8s);
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

private:
    TaskScheduler _scheduler;
};

void AddSC_hellforge_boss_diablo_lichking()
{
    new CreatureAILoader<npc_hellforge_diablo_lichkingAI>("boss_hellforge_diablo_lichking");
    new CreatureAILoader<npc_hellforge_diablo_valkyr_shadowguardAI>("npc_hellforge_diablo_valkyr_shadowguard");
    new CreatureAILoader<npc_hellforge_diablo_frostmourneAI>("npc_hellforge_diablo_frostmourne");
    new CreatureAILoader<boss_hellforge_diablo_lk_coldflame_summonerAI>("boss_hellforge_diablo_lk_coldflame_summoner");
    new CreatureAILoader<boss_hellforge_diablo_lk_coldflameAI>("boss_hellforge_diablo_lk_coldflame");
    new CreatureAILoader<boss_hellforge_diablo_lk_defileAI>("boss_hellforge_diablo_lk_defile");
}
