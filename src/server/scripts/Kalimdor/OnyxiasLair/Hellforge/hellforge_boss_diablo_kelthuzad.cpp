#include "ScriptedCreature.h"
#include "WorldCache.h"
#include <numeric>
#include "SpellScript.h"

enum DiabloKelthuzadData
{
    SPELL_SHADOW_FORM               = 37802,

    EVENT_KEL_ICY_TOUCH             = 1,
    EVENT_KEL_FROST_TOMB            = 2,
    EVENT_KEL_VOLLEY                = 3,
    EVENT_KEL_DETONATE_MANA         = 4,
    EVENT_KEL_SHADOW_FISSURE        = 5,
    EVENT_KEL_SHADOW_WORD_PAIN      = 6,

    SPELL_KEL_ICY_TOUCH             = 67938,
    SPELL_KEL_FROSTBOLT_VOLLEY      = 69273,
    SPELL_KEL_DETONATE_MANA         = 27819,
    SPELL_KEL_SHADOW_FISSURE        = 27810,
    SPELL_KEL_SHADOW_WORD_PAIN      = 15654,
    SPELL_KEL_FROST_FEVER           = 67767,
    SPELL_KEL_BLOOD_TAP             = 28470,

    SPELL_ICE_TOMB_UNTARGETABLE     = 69700,
    SPELL_ICE_TOMB_DAMAGE           = 70157,
    SPELL_ICE_TOMB_DUMMY            = 69675,
    SPELL_ASPHYXIATION              = 71665,

    GO_ICE_BLOCK                    = 201722,

    NPC_GUARDIAN_OF_ICECROWN        = 261002,
    NPC_SHADOW_FISSURE              = 261020,

    STAT_KEL_HEALTH                 = 900,
    STAT_KEL_MEELE_DMG              = 901,
    STAT_KEL_ICY_TOUCH_TIMER        = 902,
    STAT_KEL_ICY_TOUCH_DMG          = 903,
    STAT_KEL_FROST_TOMB_TIMER       = 904, 
    STAT_KEL_FROST_TOMB_COUNT       = 905,
    STAT_KEL_FROST_VOLLEY_TIMER     = 906,
    STAT_KEL_FROST_VOLLEY_DAMAGE    = 907,
    STAT_KEL_DETONATE_MANA_TIMER    = 908,
    STAT_KEL_SHADOW_FISSURE_TIMER   = 909,
    STAT_KEL_SWP_TIMER              = 910,
    STAT_KEL_SWP_DAMAGE             = 911,
    STAT_KEL_FISSURE_COUNT          = 988,

    STAT_KEL_MINION_HEALTH          = 912,
    STAT_KEL_MINION_MEELE_DMG       = 913,
    STAT_KEL_MINION_BLOOD_TAP_TIMER = 914,

    STAT_KEL_FROST_TOMB_HEALTH      = 915,
    STAT_KEL_FROST_TOMB_ASPHYXIATION_TIMER  = 916,

};

struct npc_hellforge_diablo_kelthuzadAI : public ScriptedAI
{
public:
    npc_hellforge_diablo_kelthuzadAI(Creature* creature) : ScriptedAI(creature), _summons(creature), _instance(me->GetInstanceScript()), _addSummoned(false) { }

    void Reset() override
    {
        _events.Reset();
        DoCastSelf(SPELL_SHADOW_FORM);
        _addSummoned = false;
        LoadStats();
        me->SetCanMissSpells(false);
    }

    void LoadStats()
    {
        std::vector<uint32> statsIds;
        statsIds.resize(STAT_KEL_SWP_DAMAGE - STAT_KEL_HEALTH + 1);
        std::iota(statsIds.begin(), statsIds.end(), (uint32)STAT_KEL_HEALTH);
        statsIds.push_back(STAT_KEL_FISSURE_COUNT);

        HellforgeStats stats = sWorldCache.GetStatValues(statsIds);
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_KEL_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_KEL_MEELE_DMG:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case STAT_KEL_ICY_TOUCH_TIMER:
                {
                    _icyTouchTimer = ref.second.StatValue;
                    _icyTouchTimerFirst = _icyTouchTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_KEL_ICY_TOUCH_DMG:
                {
                    _icyTouchDamage = ref.second.StatValue;
                    break;
                }
                case STAT_KEL_FROST_TOMB_TIMER:
                {
                    _frostTombTimer = ref.second.StatValue;
                    _frostTombTimerFirst = _frostTombTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_KEL_FROST_TOMB_COUNT:
                {
                    _frostTombCount = ref.second.StatValue;
                    break;
                }
                case STAT_KEL_FROST_VOLLEY_TIMER:
                {
                    _frostVolleyTimer = ref.second.StatValue;
                    break;
                }
                case STAT_KEL_FROST_VOLLEY_DAMAGE:
                {
                    _frostVolleyDamage = ref.second.StatValue;
                    break;
                }
                case STAT_KEL_DETONATE_MANA_TIMER:
                {
                    _detonateManaTimer = ref.second.StatValue;
                    _detonateManaTimerFirst = _detonateManaTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_KEL_SHADOW_FISSURE_TIMER:
                {
                    _shadowFissureTimer = ref.second.StatValue;
                    _shadowFissureTimerFirst = _shadowFissureTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_KEL_SWP_TIMER:
                {
                    _shadowWordPainTimer = ref.second.StatValue;
                    _shadowWordPainTimerFirst = _shadowWordPainTimer * ref.second.StatVariance;
                    break;
                }
                case STAT_KEL_SWP_DAMAGE:
                {
                    _shadowWordPainDamage = ref.second.StatValue;
                }
                case STAT_KEL_FISSURE_COUNT:
                {
                    _fissureCount = ref.second.StatValue;
                    break;
                }
            }
        }
    }

    void EnterEvadeMode() override
    {
        for (auto const& spellId : { SPELL_ICE_TOMB_DUMMY, SPELL_ICE_TOMB_UNTARGETABLE, SPELL_ICE_TOMB_DAMAGE, SPELL_ASPHYXIATION })
            _instance->DoRemoveAurasDueToSpellOnPlayers(spellId);
        _summons.DespawnAll();

        ScriptedAI::EnterEvadeMode();
    }

    void EnterCombat(Unit* /*victim*/) override
    {
        DoZoneInCombat();

        _events.ScheduleEvent(EVENT_KEL_ICY_TOUCH, _icyTouchTimerFirst);
        _events.ScheduleEvent(EVENT_KEL_FROST_TOMB, _frostTombTimerFirst);
        _events.ScheduleEvent(EVENT_KEL_DETONATE_MANA, _detonateManaTimerFirst);
        _events.ScheduleEvent(EVENT_KEL_SHADOW_FISSURE, _shadowFissureTimerFirst);
        _events.ScheduleEvent(EVENT_KEL_SHADOW_WORD_PAIN, _shadowWordPainTimerFirst);
    }

    void JustSummoned(Creature* creature) override
    {
        _summons.Summon(creature);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        if (me->HealthBelowPctDamaged(80, damage) && !_addSummoned)
        {
            if (Creature * creature = me->SummonCreature(NPC_GUARDIAN_OF_ICECROWN, -40.71f, -212.53f, -86.66f, 0.f))
            {
                creature->CastSpell(creature, SPELL_SHADOW_FORM);
                if (Unit * victim = creature->SelectNearestPlayer(200.f))
                    creature->Attack(victim, false);
            }
            _addSummoned = true;
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        _summons.DespawnAll();
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
            case EVENT_KEL_ICY_TOUCH:
            {
                auto threatList = me->getThreatManager().getThreatList();
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _icyTouchDamage);
                val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 200);
                for (auto ref : threatList)
                {
                    if (!ref->isOnline())
                        continue;
                    Unit* target = ref->getTarget();
                    if (!target)
                        continue;
                    me->CastCustomSpell(SPELL_KEL_ICY_TOUCH, val, target);
                    target->RemoveAurasDueToSpell(SPELL_KEL_FROST_FEVER);
                }
                _events.RescheduleEvent(EVENT_KEL_ICY_TOUCH, _icyTouchTimer);
                break;
            }
            case EVENT_KEL_FROST_TOMB:
            {
                for (uint32 i = 0; i < _frostTombCount; ++i)
                {
                    if (Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 0, [&](Unit* unit) { return !unit->HasAura(SPELL_ICE_TOMB_UNTARGETABLE) && unit != me->GetVictim(); }))
                        me->CastSpell(target, SPELL_ICE_TOMB_DAMAGE);
                }

                _events.RescheduleEvent(EVENT_KEL_FROST_TOMB, _frostTombTimer);
                _events.ScheduleEvent(EVENT_KEL_VOLLEY, _frostVolleyTimer);
                break;
            }
            case EVENT_KEL_VOLLEY:
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _frostVolleyDamage);
                val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 100000);
                me->CastCustomSpell(SPELL_KEL_FROSTBOLT_VOLLEY, val, nullptr);
                _events.PopEvent();
                break;
            }
            case EVENT_KEL_DETONATE_MANA:
            {
                std::vector<Unit*> unitList;
                ThreatContainer::StorageType const& threatList = me->getThreatManager().getThreatList();
                for (ThreatContainer::StorageType::const_iterator itr = threatList.begin(); itr != threatList.end(); ++itr)
                {
                    if ((*itr)->getTarget()->GetTypeId() == TYPEID_PLAYER
                        && (*itr)->getTarget()->getPowerType() == POWER_MANA
                        && (*itr)->getTarget()->GetPower(POWER_MANA)
                        && !(*itr)->getTarget()->HasAura(SPELL_ICE_TOMB_UNTARGETABLE))
                        unitList.push_back((*itr)->getTarget());
                }

                if (!unitList.empty())
                {
                    Unit* target = Trinity::Containers::SelectRandomContainerElement(unitList);
                    if (target)
                        me->CastSpell(target, SPELL_KEL_DETONATE_MANA, false);
                }
                _events.RescheduleEvent(EVENT_KEL_DETONATE_MANA, _detonateManaTimer);
                break;
            }
            case EVENT_KEL_SHADOW_FISSURE:
            {
                std::list<Unit*> targets;
                SelectTargetList(targets, _fissureCount, SELECT_TARGET_RANDOM, 0.F, true, -SPELL_ICE_TOMB_UNTARGETABLE);
                for (auto& target : targets)
                {
                    me->CastSpell(target, SPELL_KEL_SHADOW_FISSURE);
                }
                _events.RescheduleEvent(EVENT_KEL_SHADOW_FISSURE, _shadowFissureTimer);
                break;
            }
            case EVENT_KEL_SHADOW_WORD_PAIN:
            {
                if (Unit* target = me->SelectVictim())
                    me->CastCustomSpell(SPELL_KEL_SHADOW_WORD_PAIN, SPELLVALUE_BASE_POINT0, _shadowWordPainDamage, target);
                _events.RescheduleEvent(EVENT_KEL_SHADOW_WORD_PAIN, _shadowWordPainTimer);
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
    SummonList _summons;
    InstanceScript* _instance;
    bool _addSummoned;

    uint32 _icyTouchTimer;
    uint32 _icyTouchTimerFirst;
    uint32 _icyTouchDamage;

    uint32 _frostTombTimer;
    uint32 _frostTombTimerFirst;
    uint32 _frostTombCount;

    uint32 _frostVolleyTimer;
    uint32 _frostVolleyDamage;

    uint32 _detonateManaTimer;
    uint32 _detonateManaTimerFirst;

    uint32 _shadowFissureTimer;
    uint32 _shadowFissureTimerFirst;
    uint32 _fissureCount;

    uint32 _shadowWordPainTimer;
    uint32 _shadowWordPainTimerFirst;
    uint32 _shadowWordPainDamage;

};

struct boss_hellforge_diablo_kelthuzad_minionAI : public ScriptedAI
{
    boss_hellforge_diablo_kelthuzad_minionAI(Creature* c) : ScriptedAI(c) {}

    void Reset() override
    {
        _scheduler.CancelAll();
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
        LoadStats();
        me->SetCanMissSpells(false);
    }

    void LoadStats()
    {
        HellforgeStats stats = sWorldCache.GetStatValues({ STAT_KEL_MINION_HEALTH,  STAT_KEL_MINION_MEELE_DMG, STAT_KEL_MINION_BLOOD_TAP_TIMER });
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_KEL_MINION_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_KEL_MINION_MEELE_DMG:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case STAT_KEL_MINION_BLOOD_TAP_TIMER:
                {
                    _bloodTapTimer = ref.second.StatValue;
                    break;
                }

            }
        }
    }

    void EnterCombat(Unit* who) override
    {
        DoZoneInCombat();
        _scheduler.Schedule(std::chrono::milliseconds(_bloodTapTimer), [&](TaskContext func)
        {
            DoCastVictim(SPELL_KEL_BLOOD_TAP);
            func.Repeat(std::chrono::milliseconds(_bloodTapTimer));
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;
        
        _scheduler.Update(diff);

        DoMeleeAttackIfReady();
    }

private:
    TaskScheduler _scheduler;
    uint32 _bloodTapTimer;
};

struct npc_ice_tombAI : public NullCreatureAI
{
    npc_ice_tombAI(Creature* creature) : NullCreatureAI(creature)
    {
        me->SetReactState(REACT_PASSIVE);
        _trappedPlayerGUID = 0;
        _existenceCheckTimer = 1000;
    }

    void EnterEvadeMode() override { }

    void Reset() override
    {
        me->SetControlled(true, UNIT_STATE_ROOT);
        DoZoneInCombat();
        LoadStats();
    }

    void LoadStats()
    {
        HellforgeStats stats = sWorldCache.GetStatValues({ STAT_KEL_FROST_TOMB_HEALTH, STAT_KEL_FROST_TOMB_ASPHYXIATION_TIMER });
        for (auto const& ref : stats)
        {
            switch (ref.first)
            {
                case STAT_KEL_FROST_TOMB_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case STAT_KEL_FROST_TOMB_ASPHYXIATION_TIMER:
                {
                    _asphyxiationTimer = ref.second.StatValue;
                    return;
                }
            }
        }
    }

    void SetGUID(uint64 guid, int32 /*type*/) override
    {
        _trappedPlayerGUID = guid;
        _scheduler.Schedule(std::chrono::milliseconds(_asphyxiationTimer), [&](TaskContext /*func*/)
        {
            if (Player * player = ObjectAccessor::GetPlayer(*me, _trappedPlayerGUID))
                player->CastSpell(player, SPELL_ASPHYXIATION, true);
        });
    }

    void DamageTaken(Unit*, uint32& dmg, DamageEffectType, SpellSchoolMask) override
    {
        if (dmg >= me->GetHealth())
            me->m_positionZ = me->GetPositionZ() - 5.0f;
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->RemoveAllGameObjects();

        if (Player * player = ObjectAccessor::GetPlayer(*me, _trappedPlayerGUID))
        {
            _trappedPlayerGUID = 0;
            player->RemoveAurasDueToSpell(SPELL_ICE_TOMB_DAMAGE);
            player->RemoveAurasDueToSpell(SPELL_ASPHYXIATION);
            player->RemoveAurasDueToSpell(SPELL_ICE_TOMB_UNTARGETABLE);
            me->DespawnOrUnsummon(5000);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!_trappedPlayerGUID)
            return;

        _scheduler.Update(diff);

        if (_existenceCheckTimer <= diff)
        {
            Player* player = ObjectAccessor::GetPlayer(*me, _trappedPlayerGUID);
            if (!player || !player->IsAlive() || !player->HasAura(SPELL_ICE_TOMB_DAMAGE))
            {
                // Remove object
                JustDied(me);
                me->DespawnOrUnsummon();
                return;
            }
            _existenceCheckTimer = 1000;
        }
        else
            _existenceCheckTimer -= diff;
    }

private:
    TaskScheduler _scheduler;
    uint32 _asphyxiationTimer;
    uint64 _trappedPlayerGUID;
    uint32 _existenceCheckTimer;
};

struct boss_hellforge_diablo_kelthuzad_fissureAI : public NullCreatureAI
{
    boss_hellforge_diablo_kelthuzad_fissureAI(Creature* creature) : NullCreatureAI(creature) { }

    void Reset() override
    {
        _scheduler.Schedule(5s, [&](TaskContext /*func*/)
        {
            me->CastCustomSpell(SPELL_KEL_SHADOW_FISSURE, SPELLVALUE_BASE_POINT0, 500000 /*config*/);
            me->DespawnOrUnsummon(1s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

private:
    TaskScheduler _scheduler;
};

class spell_hellforge_diablo_kelthuzad_volley_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_hellforge_diablo_kelthuzad_volley_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (!GetCaster() || GetCaster()->GetMapId() != 249 /* Onyxia's Lair - Hellforge */)
            return;
        targets.remove_if([&](WorldObject* object) -> bool
        {
            return object->GetGUID() == GetCaster()->GetVictim()->GetGUID();
        });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hellforge_diablo_kelthuzad_volley_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

void AddSC_hellforge_boss_diablo_kelthuzad()
{
    new CreatureAILoader<npc_hellforge_diablo_kelthuzadAI>("boss_hellforge_diablo_kelthuzad");
    new CreatureAILoader<npc_ice_tombAI>("npc_hellforge_ice_tomb");
    new CreatureAILoader< boss_hellforge_diablo_kelthuzad_minionAI>("boss_hellforge_diablo_kelthuzad_minion");
    new SpellScriptLoaderEx<spell_hellforge_diablo_kelthuzad_volley_SpellScript>("spell_hellforge_diablo_kelthuzad_volley");
}
