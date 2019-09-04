#include "ScriptedCreature.h"
#include "WorldCache.h"
#include <numeric>

enum DiabloOnyxiaData
{
    SPELL_SHADOW_FORM                   = 37802,

    SPELL_ONYXIA_FLAMEBREATH            = 18435,
    SPELL_ONYXIA_TAILSWEEP              = 68867,
    SPELL_ONYXIA_CLEAVE                 = 15496,
    SPELL_ONYXIA_FIREBALL_VOLLEY        = 22425,
    SPELL_ONYXIA_BERSERK                = 61714,
    SPELL_ONYXIA_FEAR                   = 51240,

    EVENT_ONYXIA_FLAMEBREATH            = 1,
    EVENT_ONYXIA_TAILSWEEP              = 2,
    EVENT_ONYXIA_CLEAVE                 = 3,
    EVENT_ONYXIA_FIREBALL_VOLLEY        = 4,
    EVENT_ONYXIA_SPAWN_DRAKE            = 5,
    EVENT_ONYXIA_FEAR                   = 6,

    SPELL_DRAKE_GROWTH                  = 36300,
    SPELL_DRAKE_SHADOW_BREATH           = 57570,
    SPELL_DRAKE_SHADOW_FISURE           = 27810,

    EVENT_DRAKE_CHECK_ONYXIA            = 1,
    EVENT_DRAKE_GROWTH                  = 2,
    EVENT_DRAKE_SHADOW_BREATH           = 3,
    EVENT_DRAKE_SHADOW_FISSURE          = 4,


    NPC_ONYXIAN_DRAKE                   = 261004,

    GO_ONYXIA_EGG                       = 177807,

    ACTION_PLAYER_KILLED                = 1,

    STAT_ONYXIA_HEALTH                  = 938,
    STAT_ONYXIA_MEELE_DMG               = 939,
    STAT_ONYXIA_FLAMEBREATH_TIMER       = 940,
    STAT_ONYXIA_FLAMEBREATH_DMG         = 941,
    STAT_ONYXIA_TAILSWEEP_TIMER         = 942,
    STAT_ONYXIA_TAILSWEEP_DMG           = 943,
    STAT_ONYXIA_CLEAVE_TIMER            = 944,
    STAT_ONYXIA_FIREBALL_TIMER          = 945,
    STAT_ONYXIA_FIREBALL_DMG            = 946,
    STAT_ONYXIA_SPAWN_DRAKE_TIMER       = 947,
    STAT_ONYXIA_FEAR_TIMER              = 989,
    STAT_ONYXIA_FEAR_COUNT              = 990,
    STAT_ONYXIA_FEAR_DURATION           = 991,


    STAT_ONYXIAN_DRAKE_HEALTH           = 948,
    STAT_ONYXIAN_DRAKE_MEELE_DMG        = 949,
    STAT_ONYXIAN_DRAKE_GROWTH_TIMER     = 950,
    STAT_ONYXIAN_DRAKE_BREATH_TIMER     = 951,
    STAT_ONYXIAN_DRAKE_BREATH_DMG       = 952,
    STAT_ONYXIAN_DRAKE_FISSURE_TIMER    = 953,

};

constexpr uint32 ONYXIA_EGGS_COUNT{ 6 };

const Position _onyxiaEggsPositions[ONYXIA_EGGS_COUNT] =
{
    {-29.14f, -171.28f, -89.35f, 5.20f},
    {-31.24f, -175.16f, -89.30f, 5.15f},
    {-34.70f, -174.93f, -89.39f, 5.13f},
    {-35.95f, -254.91f, -89.24f, 1.26f},
    {-31.20f, -253.54f, -89.36f, 1.87f},
    {-28.43f, -256.96f, -89.23f, 1.20f}
};

struct npc_hellforge_diablo_onyxiaAI : public ScriptedAI
{
public:
    npc_hellforge_diablo_onyxiaAI(Creature* creature) : ScriptedAI(creature), _summons(creature) { }

    void Reset() override
    {
        me->MonsterYell("Who dares to summon me!", LANG_UNIVERSAL, me);
        _events.Reset();
        DoCastSelf(SPELL_SHADOW_FORM);
        LoadStats();
        me->SetCanMissSpells(false);

        me->SetCanFly(true);
        me->SetDisableGravity(true);
        me->SetHover(true);
        me->SendMovementFlagUpdate();
        me->SetPassive();
        me->SetImmuneToPC(true);

        Position pos = me->GetPosition();     

        me->GetMotionMaster()->MovePoint(1, pos.GetPositionX() - 80.f, pos.GetPositionY(), -79.31f, false);
    }

    void LoadStats()
    {
        std::vector<uint32> statsIds;
        statsIds.resize(STAT_ONYXIA_SPAWN_DRAKE_TIMER - STAT_ONYXIA_HEALTH + 1);
        std::iota(statsIds.begin(), statsIds.end(), (uint32)STAT_ONYXIA_HEALTH);
        statsIds.push_back(STAT_ONYXIA_FEAR_TIMER);
        statsIds.push_back(STAT_ONYXIA_FEAR_COUNT);
        statsIds.push_back(STAT_ONYXIA_FEAR_DURATION);

        HellforgeStats stats = sWorldCache.GetStatValues(statsIds);
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_ONYXIA_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_ONYXIA_MEELE_DMG:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case STAT_ONYXIA_FLAMEBREATH_TIMER:
                {
                    _flameBreathTimer = ref.second.StatValue;
                    _flameBreathTimerFirst = _flameBreathTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_ONYXIA_FLAMEBREATH_DMG:
                {
                    _flameBreathDMG = ref.second.StatValue;
                    break;
                }
                case STAT_ONYXIA_TAILSWEEP_TIMER:
                {
                    _tailSweepTimer = ref.second.StatValue;
                    break;
                }
                case STAT_ONYXIA_TAILSWEEP_DMG:
                {
                    _tailSweepDMG = ref.second.StatValue;
                    break;
                }
                case STAT_ONYXIA_CLEAVE_TIMER:
                {
                    _cleaveTimer = ref.second.StatValue;
                    break;
                }
                case STAT_ONYXIA_FIREBALL_TIMER:
                {
                    _volleyTimer = ref.second.StatValue;
                    _volleyTimerFirst = _volleyTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_ONYXIA_FIREBALL_DMG:
                {
                    _volleyDMG = ref.second.StatValue * ref.second.StatVariance;
                    break;
                }
                case STAT_ONYXIA_SPAWN_DRAKE_TIMER:
                {
                    _spawnDrakeTimer = ref.second.StatValue;
                    break;
                }
                case STAT_ONYXIA_FEAR_TIMER:
                {
                    _fearTimer = ref.second.StatValue;
                    break;
                }
                case STAT_ONYXIA_FEAR_COUNT:
                {
                    _fearCount = ref.second.StatValue;
                    break;
                }
                case STAT_ONYXIA_FEAR_DURATION:
                {
                    _fearDuration = ref.second.StatValue;
                    break;
                }
            }
        }
    }

    void MovementInform(uint32 type, uint32 point)
    {
        if (type == POINT_MOTION_TYPE && point == 1)
        {
            me->SetCanFly(false);
            me->SetDisableGravity(false);
            me->SetHover(false);
            me->SendMovementFlagUpdate();
            me->SetAggressive();
            me->SetImmuneToPC(false);
            if (Player * victim = me->SelectNearestPlayer(200.f))
                me->Attack(victim, false);
            ScheduleEvents();
        }
    }

    void EnterEvadeMode() override
    {
        me->RemoveAllGameObjects();
        _summons.DespawnAll();
        ScriptedAI::EnterEvadeMode();
        _eggs.clear();

        if (Creature * diablo = me->GetSummoner())
            diablo->AI()->EnterEvadeMode();
    }

    void EnterCombat(Unit* /*victim*/) override
    {
        DoZoneInCombat();
        SpawnEggs();
    }

    void ScheduleEvents()
    {
        _events.ScheduleEvent(EVENT_ONYXIA_FLAMEBREATH, _flameBreathTimerFirst);
        _events.ScheduleEvent(EVENT_ONYXIA_TAILSWEEP, _tailSweepTimer);
        _events.ScheduleEvent(EVENT_ONYXIA_CLEAVE, _cleaveTimer);
        _events.ScheduleEvent(EVENT_ONYXIA_FIREBALL_VOLLEY, _volleyTimerFirst);
        _events.ScheduleEvent(EVENT_ONYXIA_SPAWN_DRAKE, _spawnDrakeTimer);
        _events.ScheduleEvent(EVENT_ONYXIA_FEAR, _fearTimer);
    }

    void SpawnEggs()
    {
        for (uint32 i = 0; i < ONYXIA_EGGS_COUNT; ++i)
        {
            if (GameObject * egg = me->SummonGameObject(GO_ONYXIA_EGG, _onyxiaEggsPositions[i], 0, 0, 0, 0, 7 * DAY))
            {
                _eggs.push_back(egg->GetGUID());
                me->AddGameObject(egg);
            }
        }
    }

    void KilledUnit(Unit* victim) override
    {
        if (!victim->IsPlayer())
            return;
        DoAction(ACTION_PLAYER_KILLED);
    }

    void JustSummoned(Creature* creature) override
    {
        _summons.Summon(creature);
        if (Creature * diablo = me->GetSummoner())
            diablo->AI()->JustSummoned(creature);
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->MonsterYell("This cannot be... not again...", LANG_UNIVERSAL, me);
        _summons.DespawnAll();
    }
    
    void DoAction(int32 action) override
    {
        if (action == ACTION_PLAYER_KILLED)
        {
            if (!urand(0, 3))
            {
                me->MonsterYell(urand(0, 1) ? "Learn your place, mortal!" : "Worthless wretch! Your friends will join you soon enough!", LANG_UNIVERSAL, me);
            }
        }
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
            case EVENT_ONYXIA_FLAMEBREATH: 
            {
                me->MonsterYell("Burn, you rats! Burn!", LANG_UNIVERSAL, me);
                if (Unit * victim = me->GetVictim())
                    me->CastCustomSpell(SPELL_ONYXIA_FLAMEBREATH, SPELLVALUE_BASE_POINT0, _flameBreathDMG, victim);
                _events.RescheduleEvent(EVENT_ONYXIA_FLAMEBREATH, _flameBreathTimer);
                break;
            }
            case EVENT_ONYXIA_TAILSWEEP:
            {
                me->CastCustomSpell(SPELL_ONYXIA_TAILSWEEP, SPELLVALUE_BASE_POINT0, _tailSweepDMG);
                _events.RescheduleEvent(EVENT_ONYXIA_TAILSWEEP, _tailSweepTimer);
                break;
            }
            case EVENT_ONYXIA_CLEAVE:
            {
                if (Unit * victim = me->GetVictim())
                    me->CastSpell(victim, SPELL_ONYXIA_CLEAVE);
                _events.RescheduleEvent(EVENT_ONYXIA_CLEAVE, _cleaveTimer);
                break;
            }
            case EVENT_ONYXIA_FIREBALL_VOLLEY:
            {
                if (Unit * victim = me->GetVictim())
                {
                    CustomSpellValues val;
                    val.AddSpellMod(SPELLVALUE_BASE_POINT0, _volleyDMG);
                    val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 50000);
                    me->CastCustomSpell(SPELL_ONYXIA_FIREBALL_VOLLEY, val, victim);
                }
                _events.RescheduleEvent(EVENT_ONYXIA_FIREBALL_VOLLEY, _volleyTimer);
                break;
            }
            case EVENT_ONYXIA_SPAWN_DRAKE:
            {
                if (_eggs.empty())
                {
                    _events.PopEvent();
                    break;
                }

                me->MonsterYell("Rise!", LANG_UNIVERSAL, me);

                uint64 eggGuid = Trinity::Containers::SelectRandomContainerElement(_eggs);
                GameObject* egg = ObjectAccessor::GetGameObject(*me, eggGuid);
                if (egg)
                {
                    egg->SetGoState(GO_STATE_ACTIVE);
                    if (Creature * drake = me->SummonCreature(NPC_ONYXIAN_DRAKE, egg->GetPosition()))
                    {
                        if (Unit * victim = drake->SelectNearestPlayer(200.f))
                            drake->Attack(victim, false);
                        _eggs.erase(std::remove(_eggs.begin(), _eggs.end(), eggGuid));
                    }
                }
                _events.RescheduleEvent(EVENT_ONYXIA_SPAWN_DRAKE, _spawnDrakeTimer);
                break;
            }
            case EVENT_ONYXIA_FEAR:
            {
                for (uint32 i = 0; i < _fearCount; ++i)
                {
                    if (Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.f, true, -SPELL_ONYXIA_FEAR))
                    {
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_AURA_DURATION, _fearDuration);
                        val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 200);
                        me->CastCustomSpell(SPELL_ONYXIA_FEAR, val, target, TRIGGERED_FULL_MASK);
                    }
                }
                _events.RescheduleEvent(EVENT_ONYXIA_FEAR, _fearTimer);
                break;
            }
           
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
    SummonList _summons;
    std::vector<uint64> _eggs;

    uint32 _flameBreathTimer;
    uint32 _flameBreathTimerFirst;
    uint32 _flameBreathDMG;

    uint32 _tailSweepTimer;
    uint32 _tailSweepDMG;

    uint32 _cleaveTimer;

    uint32 _volleyTimer;
    uint32 _volleyTimerFirst;
    uint32 _volleyDMG;

    uint32 _spawnDrakeTimer;

    uint32 _fearTimer;
    uint32 _fearCount;
    uint32 _fearDuration;
};

struct npc_hellforge_diablo_onyxian_drakeAI : ScriptedAI
{
    npc_hellforge_diablo_onyxian_drakeAI(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->SetCanFly(true);
        me->SetInhabitType(INHABIT_AIR);
        me->CastSpell(me, SPELL_SHADOW_FORM);
        LoadStats();
        me->SetCanMissSpells(false);
    }

    void LoadStats()
    {
        std::vector<uint32> statsIds;
        statsIds.resize(STAT_ONYXIAN_DRAKE_FISSURE_TIMER - STAT_ONYXIAN_DRAKE_HEALTH + 1);
        std::iota(statsIds.begin(), statsIds.end(), (int)STAT_ONYXIAN_DRAKE_HEALTH);
        HellforgeStats stats = sWorldCache.GetStatValues(statsIds);

        for (auto const& ref : stats)
        {
            switch(ref.first)
            {
                case STAT_ONYXIAN_DRAKE_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_ONYXIAN_DRAKE_MEELE_DMG:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case STAT_ONYXIAN_DRAKE_GROWTH_TIMER:
                {
                    _growthTimer = ref.second.StatValue;
                    break;
                }
                case STAT_ONYXIAN_DRAKE_BREATH_TIMER:
                {
                    _breathTimer = ref.second.StatValue;
                    break;
                }
                case STAT_ONYXIAN_DRAKE_BREATH_DMG:
                {
                    _breathDMG = ref.second.StatValue;
                    break;
                }
                case STAT_ONYXIAN_DRAKE_FISSURE_TIMER:
                {
                    _fissureTimer = ref.second.StatValue;
                    _fissureTimerFirst = _fissureTimer * ref.second.StatVariance;
                    break;
                }
                
            }
        }
    }

    void KilledUnit(Unit* victim) override
    {
        if (!victim->IsPlayer())
            return;
        if (Unit * onyxia = me->GetSummoner())
            onyxia->GetAI()->DoAction(ACTION_PLAYER_KILLED);
    }

    void EnterCombat(Unit* /*victim*/) override
    {
        _events.ScheduleEvent(EVENT_DRAKE_CHECK_ONYXIA, 5s);
        _events.ScheduleEvent(EVENT_DRAKE_GROWTH, _growthTimer);
        _events.ScheduleEvent(EVENT_DRAKE_SHADOW_BREATH, _breathTimer);
        _events.ScheduleEvent(EVENT_DRAKE_SHADOW_FISSURE, _fissureTimerFirst);

        DoZoneInCombat();
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        switch (_events.GetEvent())
        {
            case EVENT_DRAKE_CHECK_ONYXIA:
            {
                if (Unit * onyxia = me->GetSummoner())
                {
                    if (me->IsWithinDistInMap(onyxia, 5.f))
                    {
                        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_ONYXIA_BERSERK);
                        if (spellInfo)
                            Aura::TryRefreshStackOrCreate(spellInfo, MAX_EFFECT_MASK, onyxia, onyxia);
                        _events.PopEvent();
                        break;
                    }
                }
                _events.RescheduleEvent(EVENT_DRAKE_CHECK_ONYXIA, 5s);
                break;
            }
            case EVENT_DRAKE_GROWTH:
            {
                DoCastSelf(SPELL_DRAKE_GROWTH);
                _events.RescheduleEvent(EVENT_DRAKE_GROWTH, _growthTimer);
                break;
            }
            case EVENT_DRAKE_SHADOW_BREATH:
            {
                me->CastCustomSpell(SPELL_DRAKE_SHADOW_BREATH, SPELLVALUE_BASE_POINT0, _breathDMG);
                _events.RescheduleEvent(EVENT_DRAKE_SHADOW_BREATH, _breathTimer);
                break;
            }
            case EVENT_DRAKE_SHADOW_FISSURE:
            {
                Unit* target1 = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.f, true);
                Unit* target2 = SelectTarget(SELECT_TARGET_RANDOM, 0, [&](Unit* unit) { return unit->GetGUID() != target1->GetGUID(); });

                if (target1)
                    me->CastSpell(target1, SPELL_DRAKE_SHADOW_FISURE);

                if (target2)
                    me->CastSpell(target2, SPELL_DRAKE_SHADOW_FISURE);

                _events.RescheduleEvent(EVENT_DRAKE_SHADOW_FISSURE, _fissureTimer);
                break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;

    uint32 _growthTimer;
    uint32 _breathTimer;

    uint32 _breathDMG;

    uint32 _fissureTimer;
    uint32 _fissureTimerFirst;
};

void AddSC_hellforge_boss_diablo_onyxia()
{
    new CreatureAILoader<npc_hellforge_diablo_onyxiaAI>("boss_hellforge_diablo_onyxia");
    new CreatureAILoader<npc_hellforge_diablo_onyxian_drakeAI>("npc_hellforge_diablo_onyxian_drake");
}
