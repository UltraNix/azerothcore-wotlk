#include "hellforge.hpp"

#include "MoveSplineInit.h"
#include "SpellAuras.h"
#include "Player.h"

#include <array>

enum BossOneSpells
{
    //! boss visuals
    SPELL_RED_SPIRIT_PARTICLES                  = 36725,
    SPELL_LIVING_FLARE_COSMETIC                 = 44880,
    SPELL_HEADLESS_HORSEMAN_BURNING_COSMETIC    = 43184,
    SPELL_HEADLESS_HORSEMAN_BURNING_COSMETIC_2  = 42971,

    //! combat spells
    SPELL_BOSS_ONE_FIRE_NOVA                    = 12470,
    SPELL_DAN_CHANGE_VEHICLE                    = 65431,

    //! explode spells
    SPELL_BOSS_ONE_BONES_VISUAL                 = 51270,
    SPELL_BOSS_ONE_EXPLODE                      = 51874,
    SPELL_ATTACHED_WORM_FIRE_NOVA               = 23462,

    SPELL_BOSS_ONE_FLAMES                       = 64561, // set in creature_template_addon for triggers that do have it
    SPELL_BOSS_ONE_FIRE_SHIELD                  = 11350, // periodic trigger spell
    SPELL_BOSS_ONE_FLAME_BUFFET                 = 64016
};

enum BossOneData
{
    DATA_MAKE_VISIBLE_IN                        = 1,
    DATA_PROVIDE_NEW_TARGET
};

enum BossOneEvents
{
    //! little worms
    EVENT_L_WORM_ENTER_COMBAT                   = 1,

    //! big worm, boss
    EVENT_B_WORM_SPAWN_ATTACHING_WORM           = 20,

    //! exploding worms
    EVENT_WORM_EXPLODE                          = 60,
    EVENT_WORM_SELECT_TARGET,

};

enum BossOneEntries
{
    NPC_LITTLE_WORM                             = 250001,
    NPC_LITTLE_WORM_ON_PLAYER_BACK              = 250002,

    BOSS_DISPLAY_ID_BONES                       = 25539,
    POINT_WORM_MOVE_BACK_TO_BOSS                = 1,
    DATA_WORM_RETURNED_TO_BOSS                  = 2
};

enum BossOneStatId
{
    BOSS_ONE_STAT_ID_FIRE_AURA                  = 0,
    BOSS_ONE_STAT_ID_EXPLODE                    = 1,
    BOSS_ONE_STAT_ID_FIRE_NOVA                  = 2,
    BOSS_ONE_STAT_ID_HEALTH                     = 3,
    BOSS_ONE_STAT_ID_MELEE_DAMAGE               = 4,
    BOSS_ONE_STAT_ID_FIRST_ADD_COUNT            = 75,
    BOSS_ONE_STAT_ID_SECOND_ADD_COUNT           = 76,
    BOSS_ONE_STAT_ID_THIRD_ADD_COUNT            = 77,

    //! Add related stats
    BOSS_ONE_ADD_ONE_HEALTH                     = 5,
    BOSS_ONE_ADD_ONE_MELEE_DAMAGE               = 6,
    BOSS_ONE_ADD_TWO_EXPLODE_DAMAGE             = 7,
    BOSS_ONE_ADD_ONE_BUFFET_CHANCE              = 79
};

static std::array<uint32, 4> visualSpells
{
    SPELL_RED_SPIRIT_PARTICLES,
    SPELL_LIVING_FLARE_COSMETIC,
    SPELL_HEADLESS_HORSEMAN_BURNING_COSMETIC,
    SPELL_HEADLESS_HORSEMAN_BURNING_COSMETIC_2
};

struct boss_hellforge_one_AI : public BossAI
{
    boss_hellforge_one_AI(Creature* creature) : BossAI(creature, DATA_BOSS_ONE), _myLittleWormsPositions(_littleWormsPositions) { }

    void ModifyDisplayId(uint32 displayId, bool restoreOriginal = false) const
    {
        if (restoreOriginal)
            me->RestoreDisplayId();
        else
            me->SetDisplayId(displayId);

        me->SetFloatValue(UNIT_FIELD_COMBATREACH, 15.0f);
        me->SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 15.0f);
    }

    void Reset() override
    {
        BossAI::Reset();
        me->RemoveAurasDueToSpell(SPELL_BOSS_ONE_FIRE_SHIELD);
        _reqWormCount = 0;
        _wormCount = 0;
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_DAN_CHANGE_VEHICLE);
        _explosionPhases.fill(false);
        HandleSpellVisuals();
        me->SetReactState(REACT_AGGRESSIVE);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        ModifyDisplayId(0, true);
        DoCastSelf(SPELL_BOSS_HITTIN_YA_HELLFORGE);
        _canCastFireNova = false;
        LoadBossStats();
        _fightTimer = 0;
    }

    void LoadBossStats()
    {
        HellforgeStats _stats =
            sWorldCache.GetStatValues({ BOSS_ONE_STAT_ID_FIRE_AURA, BOSS_ONE_STAT_ID_EXPLODE, BOSS_ONE_STAT_ID_FIRE_NOVA, BOSS_ONE_STAT_ID_HEALTH, BOSS_ONE_STAT_ID_MELEE_DAMAGE,
                BOSS_ONE_STAT_ID_FIRST_ADD_COUNT, BOSS_ONE_STAT_ID_SECOND_ADD_COUNT, BOSS_ONE_STAT_ID_THIRD_ADD_COUNT });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case BOSS_ONE_STAT_ID_FIRE_AURA:
                {
                    _fireAuraDamage = ref.second.StatValue;
                    break;
                }
                case BOSS_ONE_STAT_ID_EXPLODE:
                {
                    _explodeDamage = ref.second.StatValue;
                    break;
                }
                case BOSS_ONE_STAT_ID_FIRE_NOVA:
                {
                    _firenovaDamage = urand(ref.second.StatValue * ref.second.StatVariance, ref.second.StatValue);
                    break;
                }
                case BOSS_ONE_STAT_ID_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    me->SetMaxPower(POWER_MANA, ref.second.StatValue);
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    break;
                }
                case BOSS_ONE_STAT_ID_MELEE_DAMAGE:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case BOSS_ONE_STAT_ID_FIRST_ADD_COUNT:
                {
                    _firstExplosionAddCount = ref.second.StatValue;
                    break;
                }
                case BOSS_ONE_STAT_ID_SECOND_ADD_COUNT:
                {
                    _secondExplosionAddCount = ref.second.StatValue;
                    break;
                }
                case BOSS_ONE_STAT_ID_THIRD_ADD_COUNT:
                {
                    _thirdExplosionAddCount = ref.second.StatValue;
                    break;
                }
                default:
                    break;
            }
        }
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == DATA_WORM_RETURNED_TO_BOSS)
        {
            if (++_wormCount >= _reqWormCount)
            {
                _canCastFireNova = false;
                DisableFireNova();
                me->SetAggressive();
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                ModifyDisplayId(0, true);
                TriggerExplosion();
            }
        }
    }

    void AttackStart(Unit* attacker) override
    {
        me->Attack(attacker, true);
    }

    bool CanAIAttack(Unit const* target) const override
    {
        if (target->GetDistance(me) >= 70.f)
            return false;
        return BossAI::CanAIAttack(target);
    }

    void HandleSpellVisuals()
    {
        for (auto i = 0; i < visualSpells.size(); ++i)
        {
            me->RemoveAurasDueToSpell(visualSpells[i]);
            DoCastSelf(visualSpells[i], true);
        }
    }

    void DisableFireNova()
    {
        scheduler.Schedule(10s, [this](TaskContext func)
        {
            _canCastFireNova = true;
        });
    }

    void EnterCombat(Unit* who) override
    {
        BossAI::EnterCombat(who);
        DisableFireNova();
        events.ScheduleEvent(EVENT_B_WORM_SPAWN_ATTACHING_WORM, 15s);

        DoCastSelf(SPELL_BOSS_ONE_FIRE_SHIELD, true);
        if (Aura* aura = me->GetAura(SPELL_BOSS_ONE_FIRE_SHIELD))
        {
            aura->SetMaxDuration(-1);
            aura->RefreshDuration();
        }

        if (GameObject* entrance = instance->GetGameObject(DATA_GO_FIRST_BOSS_ENTRANCE))
            entrance->SetGoState(GO_STATE_READY);
        me->MonsterYell("Grooooooaaaahahh!", LANG_UNIVERSAL, nullptr);
        _fightTimer = getMSTime();
    }

    void JustDied(Unit* killer) override
    {
        me->RemoveAllAuras();
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_DAN_CHANGE_VEHICLE);
        if (Creature* wanderer = instance->GetCreature(DATA_NPC_WANDERER))
            wanderer->GetAI()->DoAction(ACTION_KILLED_BOSS_ONE);

        if (GameObject* entrance = instance->GetGameObject(DATA_GO_FIRST_BOSS_ENTRANCE))
            entrance->SetGoState(GO_STATE_ACTIVE);

        me->MonsterYell("Urghhh...", LANG_UNIVERSAL, nullptr);
        BossAI::JustDied(killer);
        CheckCreatureRecord(killer, HELLFORGE_CREATURE_RECORD_MIN_VALUE, RAID_DIFFICULTY_10MAN_NORMAL, "", 1, _fightTimer);
    }

    uint64 SelectExplodeVictim() const
    {
        auto threatList = me->getThreatManager().getThreatList();
        if (threatList.empty())
            return 0;

        std::vector<uint64> _tempGUIDs;

        for (auto t : threatList)
        {
            if (Unit* target = ObjectAccessor::GetUnit(*me, t->getUnitGuid()))
            {
                if (!target->IsPlayer())
                    continue;

                if (me->GetVictim() && target->GetGUID() == me->GetVictim()->GetGUID())
                    continue;

                if (target->GetDistance(me) >= 75.f)
                    continue;

                //! already has an exploding worm on itself
                if (target->HasAura(SPELL_DAN_CHANGE_VEHICLE))
                    continue;

                //! target is our current tank, do we allow it? tank switching so one could run away
                if (me->GetVictim() && target->GetGUID() == me->GetVictim()->GetGUID())
                    continue;

                _tempGUIDs.push_back(target->GetGUID());
            }
        }

        if (_tempGUIDs.empty())
            return 0;

        return Trinity::Containers::SelectRandomContainerElement(_tempGUIDs);
    }

    uint64 GetData64(uint32 type) const override
    {
        return SelectExplodeVictim();
    }

    void UpdateAI(uint32 diff) override
    {
        if (!_UpdateVictim())
            return;

        scheduler.Update(diff);
        events.Update(diff);

        while (auto eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_B_WORM_SPAWN_ATTACHING_WORM:
                {
                    if (me->HasReactState(REACT_PASSIVE))
                    {
                        events.Repeat(5s);
                        break;
                    }

                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 120.f, true))
                    {
                        Position spawnPosition;
                        target->GetRandomContactPoint(target, spawnPosition.m_positionX, spawnPosition.m_positionY, spawnPosition.m_positionZ, true);
                        me->SummonCreature(NPC_LITTLE_WORM_ON_PLAYER_BACK, spawnPosition, TEMPSUMMON_MANUAL_DESPAWN, 0);
                    }
                    events.Repeat(20s);
                    break;
                }
                default:
                    break;
            }
        }

        if (me->isAttackReady() && !me->HasReactState(REACT_PASSIVE))
            _DoMeleeAttackIfReady();
    }

    void TriggerExplosion()
    {
        if (!_canCastFireNova)
            return;

        CustomSpellValues val;
        val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 90000.f);
        val.AddSpellMod(SPELLVALUE_BASE_POINT0, _firenovaDamage);
        me->CastCustomSpell(SPELL_BOSS_ONE_FIRE_NOVA, val, (Unit*)nullptr);
    }

    bool _UpdateVictim()
    {
        if (!me->IsInCombat())
            return false;

        if (!me->HasReactState(REACT_PASSIVE))
        {
            if (Unit* victim = me->SelectVictim())
                AttackStart(victim);

            return me->GetVictim();
        }
        else if (me->GetVictim() && me->GetExactDist(me->GetVictim()) < 30.0f)
            return true;
        else if (me->getThreatManager().isThreatListEmpty())
        {
            EnterEvadeMode();
            return false;
        }

        return true;
    }

    void _DoMeleeAttackIfReady()
    {
        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        Unit *victim = me->GetVictim();
        if (!victim || !victim->IsInWorld())
        {
            TriggerExplosion();
            return;
        }

        if (!me->IsWithinMeleeRange(victim))
        {
            TriggerExplosion();
            return;
        }

        float victimRadianRange = 2 * M_PI / 3;
        if (!me->HasInArc(victimRadianRange, victim))
        {
            TriggerExplosion();
            return;
        }

        if (me->isAttackReady())
        {
            me->AttackerStateUpdate(victim);
            me->resetAttackTimer();
        }
    }

    void TriggerPhaseSplit(uint32 summCount, uint32 entry)
    {
        me->MonsterYell("Grrrraaaaaaaaaooo!", LANG_UNIVERSAL, nullptr);
        summons.DespawnEntry(NPC_LITTLE_WORM_ON_PLAYER_BACK);
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_DAN_CHANGE_VEHICLE);
        _reqWormCount = summCount;
        _wormCount = 0;

        Trinity::Containers::RandomShuffle(_myLittleWormsPositions);
        for (uint32 i = 0; i < summCount; ++i)
        {
            if (Creature* worm = me->SummonCreature(entry, _myLittleWormsPositions[i], TEMPSUMMON_MANUAL_DESPAWN))
            {
                worm->SetVisible(false);
                me->CastSpell(_myLittleWormsPositions[i].GetPositionX(), _myLittleWormsPositions[i].GetPositionY(), _myLittleWormsPositions[i].GetPositionZ(), 52336, true);
                float distanceToPos = me->GetDistance(_myLittleWormsPositions[i]);
                uint64 _timeDelay = (uint64)std::floor(distanceToPos / 20.0f * 1000.0f);
                worm->AI()->SetData(DATA_MAKE_VISIBLE_IN, _timeDelay);
            }
        }

        me->SetReactState(REACT_PASSIVE);
        CustomSpellValues val;
        val.AddSpellMod(SPELLVALUE_BASE_POINT0, _explodeDamage);
        val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
        me->CastCustomSpell(SPELL_BOSS_ONE_EXPLODE, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
        ModifyDisplayId(BOSS_DISPLAY_ID_BONES);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (me->HealthBelowPctDamaged(75, damage) && !_explosionPhases[0])
        {
            _explosionPhases[0] = true;
            TriggerPhaseSplit(_firstExplosionAddCount, NPC_LITTLE_WORM);
        }
        else if (me->HealthBelowPctDamaged(50, damage) && !_explosionPhases[1])
        {
            _explosionPhases[1] = true;
            TriggerPhaseSplit(_secondExplosionAddCount, NPC_LITTLE_WORM);
        }
        else if (me->HealthBelowPctDamaged(25, damage) && !_explosionPhases[2])
        {
            _explosionPhases[2] = true;
            TriggerPhaseSplit(_thirdExplosionAddCount, NPC_LITTLE_WORM);
        }
    }

    uint32 GetData(uint32 data) const override
    {
        if (data == BOSS_ONE_STAT_ID_FIRE_AURA)
            return _fireAuraDamage;

        return 0;
    }

    void EnterEvadeMode() override
    {
        if (GameObject * entrance = instance->GetGameObject(DATA_GO_FIRST_BOSS_ENTRANCE))
            entrance->SetGoState(GO_STATE_ACTIVE);
        BossAI::EnterEvadeMode();
    }
private:
    std::array<bool, 3> _explosionPhases;
    std::vector<Position> _myLittleWormsPositions;
    uint32 _reqWormCount;
    uint32 _wormCount;
    bool _canCastFireNova;
    uint32 _firenovaDamage;
    uint32 _fireAuraDamage;
    uint32 _explodeDamage;
    uint32 _firstExplosionAddCount;
    uint32 _secondExplosionAddCount;
    uint32 _thirdExplosionAddCount;
    uint32 _fightTimer;
};

struct npc_little_worm_boss_one_AI : public ScriptedAI
{
    npc_little_worm_boss_one_AI(Creature* creature) : ScriptedAI(creature)
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ BOSS_ONE_ADD_ONE_HEALTH, BOSS_ONE_ADD_ONE_MELEE_DAMAGE, BOSS_ONE_ADD_ONE_BUFFET_CHANCE });
        for (auto && ref : _stats)
        {
            switch (ref.first)
            {
                case BOSS_ONE_ADD_ONE_HEALTH:
                {
                    uint32 minHealth = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxHealth = ref.second.StatValue;
                    me->SetMaxHealth(urand(minHealth, maxHealth));
                    me->SetFullHealth();
                    break;
                }
                case BOSS_ONE_ADD_ONE_MELEE_DAMAGE:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case BOSS_ONE_ADD_ONE_BUFFET_CHANCE:
                {
                    _buffetChance = static_cast<double>(ref.second.StatVariance);
                    break;
                }
                default:
                    break;
            }
        }

        me->SetReactState(REACT_PASSIVE);
        _events.Reset();
        _isLowHealth = false;
        _alreadyInformed = false;
    }

    void SetData(uint32 data, uint32 value) override
    {
        if (data == DATA_MAKE_VISIBLE_IN)
            _events.ScheduleEvent(EVENT_L_WORM_ENTER_COMBAT, value);
    }

    void OnMeleeAttack(VictimState state, WeaponAttackType /*attackType*/, Unit* victim, uint32 /*procAttacker*/) override
    {
        if (victim && state == VICTIMSTATE_HIT && rand_norm() >= _buffetChance)
        {
            if (Aura* aura = victim->GetAura(SPELL_BOSS_ONE_FLAME_BUFFET))
            {
                uint8 stackAmount = std::min(uint8(255), uint8(aura->GetStackAmount() + 1));
                aura->SetStackAmount(stackAmount);
                aura->RefreshDuration();
            }
            else
                me->AddAura(SPELL_BOSS_ONE_FLAME_BUFFET, victim);
        }
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        if (pointId == POINT_WORM_MOVE_BACK_TO_BOSS && !_alreadyInformed)
        {
            _alreadyInformed = true;
            if (Creature* boss = me->GetSummoner())
            {
                boss->AI()->SetData(DATA_WORM_RETURNED_TO_BOSS, DATA_WORM_RETURNED_TO_BOSS);
                Movement::MoveSplineInit init(me);
                float x = boss->GetPositionX();
                float y = boss->GetPositionY();
                float z = boss->GetPositionZ() + 6.5f;
                init.MoveTo(x, y, z);
                init.SetParabolic(15.f, 0);
                init.SetVelocity(10.f);
                me->DespawnOrUnsummon(init.Launch() - 500); // -500 so it despawns mid-animation
            }
        }
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (damage >= me->GetHealth())
        {
            damage = 0;
            if (!_isLowHealth)
            {
                _isLowHealth = true;
                if (Creature* summoner = me->GetSummoner())
                {
                    Position movePos;
                    summoner->GetNearPosition(movePos, 8.f, Position::RandomOrientation());
                    me->SetPassive();
                    me->AttackStop();
                    me->SetSelectable(false);
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->GetMotionMaster()->MovePoint(POINT_WORM_MOVE_BACK_TO_BOSS, movePos);
                }
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (_isLowHealth)
            return;

        _events.Update(diff);

        while (auto eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_L_WORM_ENTER_COMBAT:
                {
                    me->SetVisible(true);
                    me->SetReactState(REACT_AGGRESSIVE);
                    DoZoneInCombat(me, 150.f);
                    break;
                }
                default:
                    break;
            }
        }

        if (_events.Empty())
            UpdateVictim();

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
    bool _isLowHealth;
    bool _alreadyInformed;
    double _buffetChance;
};

struct npc_exploding_worm_AI : public ScriptedAI
{
    npc_exploding_worm_AI(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
        _firstSelection = true;
        _counter = 0;
        _attachedToGUID = 0;
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->SetReactState(REACT_PASSIVE);
        HellforgeStatValues val;
        sWorldCache.GetStatValue(BOSS_ONE_ADD_TWO_EXPLODE_DAMAGE, val);
        _explodeDamage = urand((val.StatValue * val.StatVariance), val.StatValue);
    }

    void Reset() override
    {
        _counter = 0;
        _attachedToGUID = 0;
        if (_firstSelection)
        {
            _firstSelection = false;
            _events.ScheduleEvent(EVENT_WORM_SELECT_TARGET, 1s);
        }
        else
            _events.ScheduleEvent(EVENT_WORM_SELECT_TARGET, 10s, 15s);
    }

    void EnterCombat(Unit* /*who*/) override { }
    void AttackStart(Unit* /*who*/) override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        damage = 0;
    }

    void DoExplode()
    {
        CustomSpellValues val;
        val.AddSpellMod(SPELLVALUE_BASE_POINT0, _explodeDamage);
        val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 1500.f);
        val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
        me->CastCustomSpell(SPELL_ATTACHED_WORM_FIRE_NOVA, val, (Unit*)nullptr);
        if (Player* player = ObjectAccessor::GetPlayer(*me, _attachedToGUID))
            player->RemoveAurasDueToSpell(SPELL_DAN_CHANGE_VEHICLE);
        Reset();
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (auto eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_WORM_SELECT_TARGET:
                {
                    if (!_instance)
                        return;

                    Creature* boss = _instance->GetCreature(DATA_BOSS_ONE);
                    if (!boss)
                        return;

                    uint64 newTargetGUID = boss->AI()->GetData64(DATA_PROVIDE_NEW_TARGET);
                    if (!newTargetGUID)
                        return;

                    Unit* target = ObjectAccessor::GetUnit(*me, newTargetGUID);
                    if (!target)
                        return;

                    if (!target->ToPlayer())
                        return;

                    me->CastSpell(target, SPELL_DAN_CHANGE_VEHICLE, true);
                    DoCastSelf(SPELL_EVIL_TELEPORT_HELLFORGE, true);
                    Position pos;
                    me->GetRandomContactPoint(target, pos.m_positionX, pos.m_positionY, pos.m_positionZ, true);
                    me->NearTeleportTo(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation());
                    me->EnterVehicleUnattackable(target, 1);
                    _attachedToGUID = target->GetGUID();
                    me->MonsterWhisper("YOU HAVE BEEN AFFLICTED BY UGLY WORM!", target->ToPlayer(), true);
                    _events.ScheduleEvent(EVENT_WORM_EXPLODE, 1s);
                    break;
                }
                case EVENT_WORM_EXPLODE:
                    if (++_counter >= 6)
                        DoExplode();
                    else
                    {
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _attachedToGUID))
                        {
                            std::ostringstream explodeString{ };
                            explodeString << "You will explode in " << static_cast<uint32>(6 - _counter) << " seconds!";
                            me->MonsterWhisper(explodeString.str().c_str(), player, true);
                        }
                        _events.Repeat(1s);
                    }
                    break;
            }
        }
    }

private:
    EventMap _events;
    uint64 _attachedToGUID;
    uint32 _counter;
    bool _firstSelection;
    InstanceScript* _instance;
    uint32 _explodeDamage;
};

constexpr uint32 SPELL_BOSS_ONE_FIRE_SHIELD_TRIGGERED{ 11351 };
class spell_boss_one_fire_shield_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_boss_one_fire_shield_AuraScript);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (GetCaster() && GetCaster()->ToCreature() && GetCaster()->GetMapId() == HELLFORGE_MAP_ID)
        {
            PreventDefaultAction();
            auto _damage = GetCaster()->ToCreature()->AI()->GetData(BOSS_ONE_STAT_ID_FIRE_AURA);
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, _damage);
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 300000.f); // evaluates to 150y radius
            val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
            GetCaster()->CastCustomSpell(SPELL_BOSS_ONE_FIRE_SHIELD_TRIGGERED, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_boss_one_fire_shield_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

void AddSC_hellforge_boss_one()
{
    new CreatureAILoader<boss_hellforge_one_AI>("boss_hellforge_one");
    new CreatureAILoader<npc_little_worm_boss_one_AI>("npc_little_worm_boss_one");
    new CreatureAILoader<npc_exploding_worm_AI>("npc_exploding_worm");

    new AuraScriptLoaderEx<spell_boss_one_fire_shield_AuraScript>("spell_boss_one_fire_shield");
}
