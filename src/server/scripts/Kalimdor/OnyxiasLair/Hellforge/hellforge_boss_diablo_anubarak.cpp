#include "ScriptedCreature.h"
#include "WorldCache.h"
#include <numeric>

enum DiabloAnubarakData
{
    SPELL_SHADOW_FORM                   = 37802,

    SPELL_ANUB_FREEZING_SLASH           = 66012,
    SPELL_ANUB_PENETRATING_COLD         = 66013,
    SPELL_ANUB_PERMAFROST               = 66193,
    SPELL_ANUB_FROST_PULSE              = 71271,
    SPELL_ANUB_POUND                    = 53472,
    SPELL_ANUB_SUBMERGE                 = 65981,
    SPELL_ANUB_EMERGE                   = 65982,
    SPELL_ANUB_IMPALE_VISUAL            = 53455,
    SPELL_ANUB_IMPALE_DAMAGE            = 53454,
    SPELL_ANUB_LEECHING_SWARM           = 66118,
    SPELL_ANUB_SELF_ROOT                = 42716,

    EVENT_ANUB_FREEZING_SLASH           = 1,
    EVENT_ANUB_PENETRATING_COLD         = 2,
    EVENT_ANUB_POUND                    = 3,
    EVENT_ANUB_SUBMERGE                 = 4,
    EVENT_ANUB_EMERGE                   = 5,
    EVENT_ANUB_IMPALE                   = 6,
    EVENT_ANUB_ENABLE_ROTATE            = 7,

    NPC_PERMAFROST_TRIGGER              = 261006,
    NPC_ANUB_IMPALE_TARGET              = 261007,

    STAT_ANUB_HEALTH                    = 955,
    STAT_ANUB_MEELE_DMG                 = 956,
    STAT_ANUB_FREEZING_SLASH_TIMER      = 957,
    STAT_ANUB_FREEZING_SLASH_DMG        = 958,
    STAT_ANUB_PENETRATING_COLD_TIMER    = 959,
    STAT_ANUB_PENETRATING_COLD_COUNT    = 960,
    STAT_ANUB_POUND_TIMER               = 961,
    STAT_ANUB_SUBMERGE_TIMER            = 962,
    STAT_ANUB_MERGE_TIMER               = 963,
    STAT_ANUB_IMPALE_TIMER              = 964,
    STAT_ANUB_IMPALE_COUNT              = 965,

    STAT_ANUB_PC_FROST_PULSE_TIMER      = 966,
    STAT_ANUB_PC_FROST_PULSE_DMG        = 967,
    STAT_ANUB_PC_FROST_DESPAWN_TIME     = 968,

    STAT_ANUB_IMPALE_ACTIVATE_TIMER     = 969,
    STAT_ANUB_IMPALE_DMG                = 970,
    
};

struct boss_hellforge_diablo_anubarakAI : public ScriptedAI
{
public:
    boss_hellforge_diablo_anubarakAI(Creature* creature) : ScriptedAI(creature), _summons(creature), _instance(me->GetInstanceScript()), _leechingSwarmCasted(false) { }

    void Reset() override
    {
        _leechingSwarmCasted = false;
        _events.Reset();
        DoCastSelf(SPELL_SHADOW_FORM);
        LoadStats();

        me->SetSelectable(false);
        me->SetCanMissSpells(false);
        me->AddAura(SPELL_ANUB_SUBMERGE, me);
        _scheduler.Schedule(2s, [&](TaskContext /*func*/)
        {
            me->RemoveAura(SPELL_ANUB_SUBMERGE);
            DoCastSelf(SPELL_ANUB_EMERGE);
            me->SetSelectable(true);
            ScheduleCombatEvents(true);
        });
        if (Player * victim = me->SelectNearestPlayer(200.f))
            me->Attack(victim, false);
    }

    void LoadStats()
    {
        std::vector<uint32> statsIds;
        statsIds.resize(STAT_ANUB_IMPALE_COUNT - STAT_ANUB_HEALTH + 1);
        std::iota(statsIds.begin(), statsIds.end(), (uint32)STAT_ANUB_HEALTH);

        HellforgeStats stats = sWorldCache.GetStatValues(statsIds);
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_ANUB_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_ANUB_MEELE_DMG:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case STAT_ANUB_FREEZING_SLASH_TIMER:
                {
                    _freezingSlashTimer = ref.second.StatValue;
                    _freezingSlashTimerFirst = _freezingSlashTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_ANUB_FREEZING_SLASH_DMG:
                {
                    _freezingSlashDMG = ref.second.StatValue;
                    break;
                }
                case STAT_ANUB_PENETRATING_COLD_TIMER:
                {
                    _penetratingColdTimer = ref.second.StatValue;
                    _penetratingColdTimerFirst = _penetratingColdTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_ANUB_PENETRATING_COLD_COUNT:
                {
                    _penetratingColdCount = ref.second.StatValue;
                    break;
                }
                case STAT_ANUB_POUND_TIMER:
                {
                    _poundTimer = ref.second.StatValue;
                    _poundTimerFirst = _poundTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_ANUB_SUBMERGE_TIMER:
                {
                    _submergeTimer = ref.second.StatValue;
                    break;
                }
                case STAT_ANUB_MERGE_TIMER:
                {
                    _mergeTimer = ref.second.StatValue;
                    break;
                }
                case STAT_ANUB_IMPALE_TIMER:
                {
                    _impaleTimer = ref.second.StatValue;
                    break;
                }
                case STAT_ANUB_IMPALE_COUNT:
                {
                    _impaleCount = ref.second.StatValue;
                    break;
                }
            }
        }

    }

    void EnterEvadeMode() override
    {
        _summons.DespawnAll();
        _instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_ANUB_PENETRATING_COLD);
        ScriptedAI::EnterEvadeMode();

        if (Creature * diablo = me->GetSummoner())
            diablo->AI()->EnterEvadeMode();
    }

    void JustSummoned(Creature* creature) override
    {
        _summons.Summon(creature);
    }

    void EnterCombat(Unit* /*victim*/)
    {
        DoZoneInCombat();
        _events.ScheduleEvent(EVENT_ANUB_SUBMERGE, _submergeTimer);
        me->MonsterYell("I remember you... die!", LANG_UNIVERSAL, me);
    }

    void ScheduleCombatEvents(bool first = false)
    {
        if (first)
        {
            _events.ScheduleEvent(EVENT_ANUB_FREEZING_SLASH, _freezingSlashTimerFirst);
            _events.ScheduleEvent(EVENT_ANUB_PENETRATING_COLD, _penetratingColdTimerFirst);
            _events.ScheduleEvent(EVENT_ANUB_POUND, _poundTimerFirst);
        }
        else
        {
            _events.ScheduleEvent(EVENT_ANUB_FREEZING_SLASH, _freezingSlashTimer);
            _events.ScheduleEvent(EVENT_ANUB_PENETRATING_COLD, _penetratingColdTimer);
            _events.ScheduleEvent(EVENT_ANUB_POUND, _poundTimer);
        }
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*det*/, SpellSchoolMask) override
    {
        if (me->HealthBelowPctDamaged(30, damage) && !_leechingSwarmCasted)
        {
            _leechingSwarmCasted = true;
            _events.CancelEvent(EVENT_ANUB_SUBMERGE);
            DoCastSelf(SPELL_ANUB_LEECHING_SWARM);
            me->MonsterYell("The pestilence upon you!", LANG_UNIVERSAL, me);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);
        _scheduler.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;
        switch (_events.GetEvent())
        {
            case EVENT_ANUB_FREEZING_SLASH:
            {
                me->CastCustomSpell(SPELL_ANUB_FREEZING_SLASH, SPELLVALUE_BASE_POINT0, _freezingSlashDMG, me->GetVictim());

                // Find target with highest health except tank
                Unit* target2 = nullptr;
                auto threatList = me->getThreatManager().getThreatList();
                for (auto ref : threatList)
                {
                    if (!ref->isOnline())
                        continue;

                    Unit* source = ObjectAccessor::GetUnit(*me, ref->getUnitGuid());
                    if (!source)
                        continue;

                    if (!source->ToPlayer())
                        continue;

                    if (source->ToPlayer()->IsGameMaster())
                        continue;

                    if (source->GetGUID() == me->GetVictim()->GetGUID())
                        continue;

                    if (!source->IsWithinMeleeRange(me))
                        continue;

                    if (!target2 || target2->GetMaxHealth() < source->GetMaxHealth())
                        target2 = source;
                }
                if (target2)
                    me->CastCustomSpell(SPELL_ANUB_FREEZING_SLASH, SPELLVALUE_BASE_POINT0, _freezingSlashDMG, target2);
                _events.RescheduleEvent(EVENT_ANUB_FREEZING_SLASH, _freezingSlashTimer);
                break;
            }
            case EVENT_ANUB_PENETRATING_COLD:
            {
                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_ANUB_PENETRATING_COLD);
                if (spellInfo)
                {
                    for (uint32 i = 0; i < _penetratingColdCount; ++i)
                    {
                        Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, [&](Unit* unit) { return unit && me->GetVictim()->GetGUID() != unit->GetGUID() && !unit->HasAura(SPELL_ANUB_PENETRATING_COLD); });
                        if (target)
                            Aura::TryRefreshStackOrCreate(spellInfo, MAX_EFFECT_MASK, target, me);
                    }
                }
                _events.RescheduleEvent(EVENT_ANUB_PENETRATING_COLD, _penetratingColdTimer);
                break;
            }
            case EVENT_ANUB_POUND:
            {
                DoCastSelf(SPELL_ANUB_SELF_ROOT, true);
                me->DisableRotate(true);
                me->SendMovementFlagUpdate();
                DoCastVictim(SPELL_ANUB_POUND);
                if (auto sInfo = sSpellMgr->GetSpellInfo(SPELL_ANUB_POUND))
                    _events.ScheduleEvent(EVENT_ANUB_ENABLE_ROTATE, sInfo->CastTimeEntry->CastTime + 100);
                
                _events.RescheduleEvent(EVENT_ANUB_POUND, _poundTimer);
                break;
            }
            case EVENT_ANUB_ENABLE_ROTATE:
            {
                me->RemoveAurasDueToSpell(SPELL_ANUB_SELF_ROOT);
                me->DisableRotate(false);
                _events.PopEvent();
                break;
            }
            case EVENT_ANUB_SUBMERGE:
            {
                me->RemoveAurasDueToSpell(SPELL_ANUB_SELF_ROOT);
                me->DisableRotate(false);
                me->MonsterYell("Auum na-l ak-k-k-k, isshhh. Devour...", LANG_UNIVERSAL, me);
                me->SetSelectable(false);
                DoCastSelf(SPELL_ANUB_SUBMERGE);
                _events.Reset();
                _events.ScheduleEvent(EVENT_ANUB_EMERGE, _mergeTimer);
                _events.ScheduleEvent(EVENT_ANUB_IMPALE, _impaleTimer);
                break;
            }
            case EVENT_ANUB_EMERGE:
            {
                me->MonsterYell("Feast on your flesh!", LANG_UNIVERSAL, me);
                me->RemoveAura(SPELL_ANUB_SUBMERGE);
                DoCastSelf(SPELL_ANUB_EMERGE);
                me->SetSelectable(true);
                _events.Reset();
                ScheduleCombatEvents();
                _events.ScheduleEvent(EVENT_ANUB_SUBMERGE, _submergeTimer);
                break;
            }
            case EVENT_ANUB_IMPALE:
            {
                std::list<Unit*> targets;
                SelectTargetList(targets, _impaleCount, SELECT_TARGET_RANDOM);
                for (auto& target : targets)
                {
                    me->SummonCreature(NPC_ANUB_IMPALE_TARGET, target->GetPosition());
                }
                _events.RescheduleEvent(EVENT_ANUB_IMPALE, _impaleTimer);
                break;
            }
        }
        DoMeleeAttackIfReady();
    }

    void KilledUnit(Unit* victim) override
    {
        if (!victim->IsPlayer())
            return;
        if (!urand(0, 3))
        {
            me->MonsterYell("One more soul to my collection.", LANG_UNIVERSAL, me);
        }
    }

    void JustDied(Unit* killer) override
    {
        me->MonsterYell("Never thought... I would be free of him...", LANG_UNIVERSAL, me);
    }

private:
    EventMap _events;
    TaskScheduler _scheduler;
    SummonList _summons;
    InstanceScript* _instance;
    bool _leechingSwarmCasted;

    uint32 _freezingSlashTimer;
    uint32 _freezingSlashTimerFirst;
    uint32 _freezingSlashDMG;

    uint32 _penetratingColdTimer;
    uint32 _penetratingColdTimerFirst;
    uint32 _penetratingColdCount;

    uint32 _poundTimer;
    uint32 _poundTimerFirst;

    uint32 _submergeTimer;
    uint32 _mergeTimer;
    uint32 _impaleTimer;
    uint32 _impaleCount;
};

struct boss_hellforge_diablo_anubarak_permafrostAI : public ScriptedAI
{
    boss_hellforge_diablo_anubarak_permafrostAI(Creature* creature) : ScriptedAI(creature), _anubGuid(0)
    {
        me->SetCanMissSpells(false);
        me->SetSelectable(false);
    }

    void Reset() override
    {
        LoadStats();
        DoCastSelf(SPELL_ANUB_PERMAFROST);
        _scheduler.CancelAll();
        ScheduleEvents();
    }

    void LoadStats()
    {
        HellforgeStats stats = sWorldCache.GetStatValues({ STAT_ANUB_PC_FROST_PULSE_TIMER , STAT_ANUB_PC_FROST_PULSE_DMG, STAT_ANUB_PC_FROST_DESPAWN_TIME });
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_ANUB_PC_FROST_PULSE_TIMER:
                {
                    _frostPulseTimerStart = ref.second.StatValue * ref.second.StatVariance;
                    _frostPulseTimer = ref.second.StatValue;
                    break;
                }
                case STAT_ANUB_PC_FROST_PULSE_DMG:
                {
                    _frostPulseDMG = ref.second.StatValue;
                    break;
                }
                case STAT_ANUB_PC_FROST_DESPAWN_TIME:
                {
                    _despawnTime = ref.second.StatValue;
                    break;
                }
            }
        }
    }
    
    void ScheduleEvents()
    {
        _scheduler.Schedule(std::chrono::milliseconds(_frostPulseTimerStart), [this](TaskContext func)
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, _frostPulseDMG);
            val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 5000);
            me->CastCustomSpell(SPELL_ANUB_FROST_PULSE, val, nullptr, TRIGGERED_FULL_MASK);
            func.Repeat(std::chrono::milliseconds(_frostPulseTimer));
        });

        me->DespawnOrUnsummon(std::chrono::milliseconds(_despawnTime));
    }

    void SetGUID(uint64 guid, int32 /*type*/)
    {
        if (Creature * anub = ObjectAccessor::GetCreature(*me, guid))
            anub->AI()->JustSummoned(me);
    }

    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }
    void EnterEvadeMode() override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override { damage = 0; }
    void UpdateAI(uint32 diff) override { _scheduler.Update(diff); }
private:
    TaskScheduler _scheduler;
    uint64 _anubGuid;

    uint32 _frostPulseTimerStart;
    uint32 _frostPulseTimer;
    uint32 _frostPulseDMG;
    uint32 _despawnTime;
};

struct boss_hellforge_diablo_anubarak_impale_targetAI : ScriptedAI
{
public:
    boss_hellforge_diablo_anubarak_impale_targetAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        LoadStats();
        DoCastSelf(SPELL_ANUB_IMPALE_VISUAL);
        _scheduler.Schedule(std::chrono::milliseconds(_impaleActivateTimer), [&](TaskContext /*func*/)
        {
            me->CastCustomSpell(SPELL_ANUB_IMPALE_DAMAGE, SPELLVALUE_BASE_POINT0, _impaleDMG, me);
        });
        me->DespawnOrUnsummon(7s);
    }

    void LoadStats()
    {
        HellforgeStats stats = sWorldCache.GetStatValues({ STAT_ANUB_IMPALE_ACTIVATE_TIMER, STAT_ANUB_IMPALE_DMG });
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_ANUB_IMPALE_ACTIVATE_TIMER:
                {
                    _impaleActivateTimer = ref.second.StatValue;
                    break;
                }
                case STAT_ANUB_IMPALE_DMG:
                {
                    _impaleDMG = ref.second.StatValue;
                    break;
                }
            }
        }
    }

    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }
    void EnterEvadeMode() override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override { damage = 0; }
    void UpdateAI(uint32 diff) override { _scheduler.Update(diff); }

private:
    TaskScheduler _scheduler;

    uint32 _impaleActivateTimer;
    uint32 _impaleDMG;
};

class spell_anubarak_penetraing_cold_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_anubarak_penetraing_cold_AuraScript);

    void ExtraRemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetCaster() || !GetCaster()->IsInCombat() || !GetTarget() || GetTarget()->GetMapId() != 249 /* Onyxia's Lair - Hellforge */)
            return;
        Position pos = GetTarget()->GetPosition();
        if (Creature * trigger = GetCaster()->SummonCreature(NPC_PERMAFROST_TRIGGER, pos))
            trigger->AI()->SetGUID(GetCaster()->GetGUID());
    }

    void Register()
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_anubarak_penetraing_cold_AuraScript::ExtraRemoveEffect, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_hellforge_boss_diablo_anubarak()
{
    new CreatureAILoader<boss_hellforge_diablo_anubarakAI>("boss_hellforge_diablo_anubarak");
    new CreatureAILoader<boss_hellforge_diablo_anubarak_permafrostAI>("boss_hellforge_diablo_anubarak_permafrost");
    new CreatureAILoader<boss_hellforge_diablo_anubarak_impale_targetAI>("boss_hellforge_diablo_anubarak_impale_target");
    new AuraScriptLoaderEx<spell_anubarak_penetraing_cold_AuraScript>("spell_anubarak_penetraing_cold");
}
