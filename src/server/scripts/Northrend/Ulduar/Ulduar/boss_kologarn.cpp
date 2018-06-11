/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "ulduar.h"
#include "Vehicle.h"
#include "MoveSplineInit.h"
#include "SpellAuraEffects.h"
#include "PassiveAI.h"
#include "Player.h"

enum KologarnSays
{
    SAY_AGGRO              = 0,
    SAY_SLAY               = 1,
    SAY_LEFT_ARM_GONE      = 2,
    SAY_RIGHT_ARM_GONE     = 3,
    SAY_SHOCKWAVE          = 4,
    SAY_GRAB_PLAYER        = 5,
    SAY_DEATH              = 6,
    SAY_BERSERK            = 7,
    EMOTE_STONE_GRIP       = 8,
    EMOTE_EYES             = 9
};

enum KologarnSpells
{
    SPELL_KOLOGARN_REDUCE_PARRY            = 64651,

    // BASIC
    SPELL_OVERHEAD_SMASH_10                = 63356,
    SPELL_OVERHEAD_SMASH_25                = 64003,
    SPELL_ONEARMED_OVERHEAD_SMASH_10       = 63573,
    SPELL_ONEARMED_OVERHEAD_SMASH_25       = 64006,
    SPELL_PETRIFYING_BREATH_10             = 62030,
    SPELL_PETRIFYING_BREATH_25             = 63980,
    SPELL_STONE_SHOUT_10                   = 63716,
    SPELL_STONE_SHOUT_25                   = 64005,

    // EYEBEAM
    SPELL_FOCUSED_EYEBEAM_10               = 63347,
    SPELL_FOCUSED_EYEBEAM_25               = 63977,
    SPELL_FOCUSED_EYEBEAM_RIGHT            = 63676, // NPC -> KOLOGARN
    SPELL_FOCUSED_EYEBEAM_LEFT             = 63352, // KOLOGARN -> NPC
    SPELL_LEFT_EYEBEAM_SUMMON              = 63343,
    SPELL_RIGHT_EYEBEAM_SUMMON             = 63701,
    SPELL_FOCUSED_EYEBEAM_VISUAL           = 63369,
    SPELL_FOCUSED_EYEBEAM_VISUAL_LEFT      = 63676,
    SPELL_FOCUSED_EYEBEAM_VISUAL_RIGHT     = 63702,
    SPELL_FOCUSED_EYEBEAM_HIDDEN_AURA      = 67351,

    // ARMS
    SPELL_ARM_DEAD_10                      = 63629,
    SPELL_ARM_DEAD_25                      = 63979,
    SPELL_RUBBLE_FALL_10                   = 63821,
    SPELL_RUBBLE_FALL_25                   = 64001,
    SPELL_ARM_RESPAWN_VISUAL               = 64753,

    // LEFT ARM
    SPELL_ARM_SWEEP_10                     = 63766,
    SPELL_ARM_SWEEP_25                     = 63983,

    // RIGHT ARM
    SPELL_STONE_GRIP_10                    = 62166,
    SPELL_STONE_GRIP_25                    = 63981,
    SPELL_RIDE_RIGHT_ARM_10                = 62056,
    SPELL_RIDE_RIGHT_ARM_25                = 63985,

    // RUBBLE TRASH
    SPELL_RUBBLE_ATTACK_10                 = 63818,
    SPELL_RUBBLE_ATTACK_25                 = 63978,

    // MISC
    SPELL_STONE_GRIP_DOT_10                = 64290,
    SPELL_STONE_GRIP_DOT_25                = 64292,
    SPELL_SHOCKWAVE_25                     = 63982,
    SPELL_SHOCKWAVE_10                     = 63783,
    SPELL_SHOCKWAVE_VISUAL                 = 63788
};

#define SPELL_PETRIFYING_BREATH            RAID_MODE(SPELL_PETRIFYING_BREATH_10, SPELL_PETRIFYING_BREATH_25)
#define SPELL_OVERHEAD_SMASH               RAID_MODE(SPELL_OVERHEAD_SMASH_10, SPELL_OVERHEAD_SMASH_25)
#define SPELL_ONEARMED_OVERHEAD_SMASH      RAID_MODE(SPELL_ONEARMED_OVERHEAD_SMASH_10, SPELL_ONEARMED_OVERHEAD_SMASH_25)
#define SPELL_ARM_DEAD                     RAID_MODE(SPELL_ARM_DEAD_10, SPELL_ARM_DEAD_25)
#define SPELL_ARM_SWEEP                    RAID_MODE(SPELL_ARM_SWEEP_10, SPELL_ARM_SWEEP_25)
#define SPELL_STONE_GRIP                   RAID_MODE(SPELL_STONE_GRIP_10, SPELL_STONE_GRIP_25)
#define SPELL_FOCUSED_EYEBEAM              RAID_MODE(SPELL_FOCUSED_EYEBEAM_10, SPELL_FOCUSED_EYEBEAM_25)
#define SPELL_RUBBLE_FALL                  RAID_MODE(SPELL_RUBBLE_FALL_10, SPELL_RUBBLE_FALL_25)
#define SPELL_RUBBLE_ATTACK                RAID_MODE(SPELL_RUBBLE_ATTACK_10, SPELL_RUBBLE_ATTACK_25)
#define SPELL_RIDE_RIGHT_ARM               RAID_MODE(SPELL_RIDE_RIGHT_ARM_10, SPELL_RIDE_RIGHT_ARM_25)
#define SPELL_STONE_SHOUT                  RAID_MODE(SPELL_STONE_SHOUT_10, SPELL_STONE_SHOUT_25)
#define SPELL_STONE_GRIP_DOT               RAID_MODE(SPELL_STONE_GRIP_DOT_10, SPELL_STONE_GRIP_DOT_25)

#define DEFAULT_ORIENTATION 3.193500f

enum KologarnEvents
{
    EVENT_SMASH                            = 1,
    EVENT_GRIP                             = 2,
    EVENT_SWEEP                            = 3,
    EVENT_RESTORE_ARM_LEFT                 = 4,
    EVENT_RESTORE_ARM_RIGHT                = 5,
    EVENT_FOCUSED_EYEBEAM                  = 6,
    EVENT_STONE_SHOUT                      = 7,
    EVENT_CLEAR_CHASE_TARGET               = 8,
    EVENT_BEAM_CHASE                       = 9,
    EVENT_EYEBEAM_FORM                     = 10,
    EVENT_UNLOCK_BREATH                    = 11
};

enum KologarnNPCs
{
    NPC_LEFT_ARM                          = 32933,
    NPC_RIGHT_ARM                         = 32934,
    NPC_SWEEP_TRIGGER                     = 33661,
    NPC_EYE_LEFT                          = 33632,
    NPC_EYE_RIGHT                         = 33802,
    NPC_RUBBLE_TRIGGER                    = 33809,
    NPC_RUBBLE_SUMMON                     = 33768
};

enum KologarnSounds
{
    SOUND_AGGRO                           = 15586,
    SOUND_SLAY1                           = 15587,
    SOUND_SLAY2                           = 15588,
    SOUND_LARM_GONE                       = 15589,
    SOUND_RARM_GONE                       = 15590,
    SOUND_SHOCKWAVE                       = 15591,
    SOUND_GRIP                            = 15592,
    SOUND_DEATH                           = 15593,
    SOUND_BERSERK                         = 15594
};

enum Misc
{
    ACHIEVEMENT_DISARMED_CRITERIA         = 21687,

    DATA_KOLOGARN_LOOKS_ACHIEV            = 55,
    DATA_KOLOGARN_RUBBLE_ACHIEV           = 56,
    DATA_KOLOGARN_ARMS_ACHIEV             = 57,
    DATA_CHASE_GUID                       = 58,
    DATA_RESET_DAMAGE_REQUIREMENTS        = 59,
    DATA_ATTACH_ARMS                      = 60
};

class AttachArms : public BasicEvent
{
public:
    AttachArms(Unit* caster) : _caster(caster) { }

    bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
    {
        if (_caster->IsAIEnabled)
            _caster->GetAI()->DoAction(DATA_ATTACH_ARMS);
        return true;
    }

private:
    Unit * _caster;
};

class boss_kologarn : public CreatureScript
{
public:
    boss_kologarn() : CreatureScript("boss_kologarn") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_kologarnAI (pCreature);
    }

    struct boss_kologarnAI : public ScriptedAI
    {
        boss_kologarnAI(Creature* pCreature) : ScriptedAI(pCreature), vehicle(me->GetVehicleKit()),
            _left(0), _right(0), summons(me)
        {
            m_pInstance = me->GetInstanceScript();
            assert(vehicle);
            me->SetStandState(UNIT_STAND_STATE_SUBMERGED);
        }

        InstanceScript* m_pInstance;

        Vehicle* vehicle;
        uint64 _left, _right;
        EventMap events;
        SummonList summons;

        //! Delay kologarns breath when noone is nearby for 3 seconds(event) when body pulled
        bool _lockBreath;
        bool _looksAchievement;
        uint8 _rubbleAchievement;
        uint64 eyebeamTarget;
        uint32 _fightTimer;

        void MoveInLineOfSight(Unit* who) override
        {
            if (who->GetTypeId() == TYPEID_PLAYER && me->GetExactDist2d(who) < 45.0f && me->getStandState() == UNIT_STAND_STATE_SUBMERGED)
            {
                me->SetStandState(UNIT_STAND_STATE_STAND);
            }

            if (who->GetTypeId() == TYPEID_PLAYER && me->GetExactDist2d(who) < 30.0f && me->getStandState() != UNIT_STAND_STATE_SUBMERGED)
                ScriptedAI::MoveInLineOfSight(who);
        }

        void EnterEvadeMode()
        {
            if (!_EnterEvadeMode())
                return;

            _right = 0;
            _left = 0;
            Reset();
            me->setActive(false);
        }

        void AttachLeftArm()
        {
            if (Unit* arm = ObjectAccessor::GetCreature(*me, _left))
                arm->SetHealth(arm->GetMaxHealth());
            else if (Creature* accessory = me->SummonCreature(NPC_LEFT_ARM, *me, TEMPSUMMON_MANUAL_DESPAWN))
            {
                accessory->AddUnitTypeMask(UNIT_MASK_ACCESSORY);
                if (!me->HandleSpellClick(accessory, 0))
                    accessory->DespawnOrUnsummon();
                else
                {
                    accessory->SetOrientation(M_PI);
                    accessory->CastSpell(accessory, SPELL_ARM_RESPAWN_VISUAL, true);
                }
            }
        }

        void AttachRightArm()
        {
            if (Unit* arm = ObjectAccessor::GetCreature(*me, _right))
                arm->SetHealth(arm->GetMaxHealth());
            else if (Creature* accessory = me->SummonCreature(NPC_RIGHT_ARM, *me, TEMPSUMMON_MANUAL_DESPAWN))
            {
                accessory->AddUnitTypeMask(UNIT_MASK_ACCESSORY);
                if (!me->HandleSpellClick(accessory, 1))
                    accessory->DespawnOrUnsummon();
                else
                {
                    accessory->SetOrientation(M_PI);
                    accessory->CastSpell(accessory, SPELL_ARM_RESPAWN_VISUAL, true);
                }
            }
        }

        void Reset()
        {
            _fightTimer = 0;
            eyebeamTarget = 0;
            _rubbleAchievement = 0;
            _looksAchievement = true;
            _lockBreath = true;
            me->SetOrientation(DEFAULT_ORIENTATION);

            me->SetDisableGravity(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->DisableRotate(true);

            events.Reset();
            summons.DespawnAll();

            if (m_pInstance)
                if (m_pInstance->GetData(TYPE_KOLOGARN) != DONE)
                    m_pInstance->SetData(TYPE_KOLOGARN, NOT_STARTED);

            me->m_Events.AddEvent(new AttachArms(me), me->m_Events.CalculateTime(4000));
        }

        void DoAction(int32 param)
        {
            switch (param)
            {
                case DATA_KOLOGARN_LOOKS_ACHIEV:
                {
                    _looksAchievement = false;
                    break;
                }
                case DATA_KOLOGARN_RUBBLE_ACHIEV:
                {
                    // Means arm died
                    if (m_pInstance && (!_left || !_right))
                        m_pInstance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEVEMENT_DISARMED_CRITERIA);

                    ++_rubbleAchievement;
                    break;
                }
                case DATA_ATTACH_ARMS:
                {
                    AttachLeftArm();
                    AttachRightArm();
                    break;
                }
            }
        }

        uint32 GetData(uint32 param) const
        {
            if (param == DATA_KOLOGARN_LOOKS_ACHIEV)
                return _looksAchievement;
            else if (param == DATA_KOLOGARN_RUBBLE_ACHIEV)
                return (_rubbleAchievement >= 5);
            else if (param == DATA_KOLOGARN_ARMS_ACHIEV)
                return !_rubbleAchievement;

            return 0;
        }

        void AttackStart(Unit* who)
        {
            me->Attack(who, true);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);

            if (summon->GetEntry() == NPC_RIGHT_ARM)
                _right = summon->GetGUID();

            if (summon->GetEntry() == NPC_LEFT_ARM)
                _left = summon->GetGUID();
            if (summon->GetEntry() == NPC_EYE_LEFT || summon->GetEntry() == NPC_EYE_RIGHT)
            {
                summon->CastSpell(me, summon->GetEntry() == NPC_EYE_LEFT ? SPELL_FOCUSED_EYEBEAM_VISUAL_LEFT : SPELL_FOCUSED_EYEBEAM_VISUAL_RIGHT, true);
                // test summon->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                summon->CastSpell(summon, SPELL_FOCUSED_EYEBEAM, true);
                summon->CastSpell(summon, SPELL_FOCUSED_EYEBEAM_VISUAL, true);
                summon->SetReactState(REACT_PASSIVE);
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                // One of the above spells is a channeled spell, we need to clear this unit state for MoveChase to work
                summon->ClearUnitState(UNIT_STATE_CASTING);

                // Victim gets 67351
                if (eyebeamTarget)
                {
                    if (Unit* target = ObjectAccessor::GetUnit(*summon, eyebeamTarget))
                    {
                        summon->Attack(target, false);
                        summon->AI()->SetGUID(eyebeamTarget, DATA_CHASE_GUID);
                    }
                }
            }
        }

        void JustDied(Unit* killer)
        {
            summons.DespawnAll();
            me->StopMoving();
            if (m_pInstance)
                m_pInstance->SetData(TYPE_KOLOGARN, DONE);

            Talk(SAY_DEATH);

            if (GameObject* bridge = me->FindNearestGameObject(GO_KOLOGARN_BRIDGE, 100.f))
                bridge->SetGoState(GO_STATE_READY);

            // Summon Chest
            if (GameObject* go = me->GetMap()->SummonGameObject(RAID_MODE(GO_KOLOGARN_CHEST, GO_KOLOGARN_CHEST_HERO), 1839.62f, -35.98f, 448.81f, 3.6f, 0, 0, 0, 0, 7*86400))
            {
                me->RemoveGameObject(go, false);
                go->SetSpellId(1); // hack to make it despawn
                go->SetUInt32Value(GAMEOBJECT_FLAGS, 0);
            }

            if (Creature* arm = ObjectAccessor::GetCreature(*me, _left))
                arm->DespawnOrUnsummon(3000); // visual
            if (Creature* arm = ObjectAccessor::GetCreature(*me, _right))
                arm->DespawnOrUnsummon(3000); // visual

            me->SetOrientation(DEFAULT_ORIENTATION);
            me->SetCorpseDelay(WEEK);
            me->SaveRespawnTime();

            if (Map* map = me->GetMap())
                CheckCreatureRecord(killer, me->GetCreatureTemplate()->Entry, Difficulty(map->GetDifficulty()), "", 15000, _fightTimer);
        }

        void KilledUnit(Unit*)
        {
            if (!urand(0,2))
                return;

            Talk(SAY_SLAY);
        }

        void PassengerBoarded(Unit* who, int8 seatId, bool apply)
        {
            if (!me->IsAlive())
                return;

            if (!apply)
            {
                // left arm
                if (who->GetGUID() == _left)
                {
                    _left = 0;
                    if (me->IsInCombat())
                    {
                        Talk(SAY_LEFT_ARM_GONE);
                        events.ScheduleEvent(EVENT_RESTORE_ARM_LEFT, 45000, 2);
                    }
                }
                else
                {
                    _right = 0;
                    if (me->IsInCombat())
                    {
                        Talk(SAY_RIGHT_ARM_GONE);
                        events.ScheduleEvent(EVENT_RESTORE_ARM_RIGHT, 45000, 2);
                    }
                }

                if (InstanceScript* instance = me->GetInstanceScript())
                    if (!me->IsInEvadeMode() && instance->GetData(TYPE_KOLOGARN) == IN_PROGRESS)
                        me->CastSpell(me, SPELL_ARM_DEAD, true);

                if (!_right && !_left)
                    events.ScheduleEvent(EVENT_STONE_SHOUT, 5000, 1);
            }
            else
            {
                Movement::MoveSplineInit init(who);
                init.DisableTransportPathTransformations();
                init.MoveTo(0.f, 0.f, 0.f);
                init.Launch();
            }
        }

        bool CanAIAttack(const Unit* target) const override
        {
            return target->GetDistance(me->GetPosition()) < 60.0f;
        }

        void DamageTaken(Unit* who, uint32& damage, DamageEffectType, SpellSchoolMask)
        {
            if (who && who->GetEntry() == me->GetEntry() && me->GetHealth())
            {
                damage = std::min(damage, me->GetHealth()-1);
                me->LowerPlayerDamageReq(damage);
            }
        }

        void EnterCombat(Unit* who) override
        {
            if (m_pInstance)
                m_pInstance->SetData(TYPE_KOLOGARN, IN_PROGRESS);

            _fightTimer = getMSTime();
            DoZoneInCombat();
            events.ScheduleEvent(EVENT_SMASH, 8000, 1);
            events.ScheduleEvent(EVENT_SWEEP, 17000, 1);
            events.ScheduleEvent(EVENT_GRIP, 15000, 1);
            events.ScheduleEvent(EVENT_FOCUSED_EYEBEAM, 25000, 1);
            events.ScheduleEvent(EVENT_UNLOCK_BREATH, 3s);
            //events.ScheduleEvent(EVENT_ENRAGE, x); no info

            Talk(SAY_AGGRO);
            me->setActive(true);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (auto eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_UNLOCK_BREATH:
                    {
                        _lockBreath = false;
                        break;
                    }
                    case EVENT_STONE_SHOUT:
                        if (_left || _right)
                        {
                            events.PopEvent();
                            return;
                        }

                        me->CastSpell(me->GetVictim(), SPELL_STONE_SHOUT, false);
                        events.Repeat(2s);
                        break;
                    case EVENT_SMASH:
                        if (_left || _right)
                            me->setAttackTimer(BASE_ATTACK, 2000);

                        if (_left && _right)
                            me->CastSpell(me->GetVictim(), SPELL_OVERHEAD_SMASH, false);
                        else if (_left || _right)
                            me->CastSpell(me->GetVictim(), SPELL_ONEARMED_OVERHEAD_SMASH, false);

                        events.DelayEvents(1000, 1);
                        events.Repeat(14s);
                        break;
                    case EVENT_SWEEP:
                        if (_left)
                        {
                            if (Creature* cr = me->FindNearestCreature(NPC_SWEEP_TRIGGER, 300.f))
                            {
                                if (cr->IsAIEnabled)
                                {
                                    if (Is25ManRaid())
                                        cr->AI()->DoCastAOE(SPELL_SHOCKWAVE_25, true);
                                    else
                                        cr->AI()->DoCastAOE(SPELL_SHOCKWAVE_10, true);

                                    cr->AI()->DoCastSelf(SPELL_SHOCKWAVE_VISUAL);
                                }
                            }

                            if (urand(0, 1))
                                Talk(SAY_SHOCKWAVE);
                        }

                        events.DelayEvents(1000, 1);
                        events.Repeat(17s);
                        break;
                    case EVENT_GRIP:
                        events.Repeat(25s);
                        if (!_right)
                            break;

                        if (Creature* arm = ObjectAccessor::GetCreature(*me, _right))
                            if (arm->IsAIEnabled)
                                arm->AI()->SetData(DATA_RESET_DAMAGE_REQUIREMENTS, DATA_RESET_DAMAGE_REQUIREMENTS);

                        me->CastSpell(me, SPELL_STONE_GRIP, false);
                        Talk(SAY_GRAB_PLAYER);
                        Talk(EMOTE_STONE_GRIP);
                        break;
                    case EVENT_FOCUSED_EYEBEAM:
                    {
                        if (Unit* eyebeamTargetUnit = GetEyeBeamTarget())
                        {
                            eyebeamTarget = eyebeamTargetUnit->GetGUID();
                            me->MonsterWhisper("Kologarn focuses his eyes on you!", eyebeamTargetUnit->ToPlayer(), true);
                            eyebeamTargetUnit->CastSpell(eyebeamTargetUnit, SPELL_LEFT_EYEBEAM_SUMMON, true, nullptr, nullptr, me->GetGUID());
                            eyebeamTargetUnit->CastSpell(eyebeamTargetUnit, SPELL_RIGHT_EYEBEAM_SUMMON, true, nullptr, nullptr, me->GetGUID());
                        }
                        else if (Unit* eyebeamTargetUnit = SelectTarget(SELECT_TARGET_RANDOM, 0, 60.0f, true, -SPELL_STONE_GRIP_DOT))
                        {
                            eyebeamTarget = eyebeamTargetUnit->GetGUID();
                            me->MonsterWhisper("Kologarn focuses his eyes on you!", eyebeamTargetUnit->ToPlayer(), true);
                            eyebeamTargetUnit->CastSpell(eyebeamTargetUnit, SPELL_LEFT_EYEBEAM_SUMMON, true, nullptr, nullptr, me->GetGUID());
                            eyebeamTargetUnit->CastSpell(eyebeamTargetUnit, SPELL_RIGHT_EYEBEAM_SUMMON, true, nullptr, nullptr, me->GetGUID());
                        }
                        events.ScheduleEvent(EVENT_CLEAR_CHASE_TARGET, 11s);
                        events.Repeat(25s, 30s);
                        break;
                    }
                    case EVENT_CLEAR_CHASE_TARGET:
                        eyebeamTarget = 0;
                        break;
                    case EVENT_RESTORE_ARM_LEFT:
                        // shouldn't happen
                        AttachLeftArm();
                        break;
                    case EVENT_RESTORE_ARM_RIGHT:
                        // shouldn't happen
                        AttachRightArm();
                        break;
                }
            }

            //Make sure our attack is ready and we aren't currently casting before checking distance
            if (me->isAttackReady() && me->GetVictim() && !_lockBreath) // victim could die by a spell (IMPORTANT!!!) and kologarn entered evade mode
            {
                //If we are within range melee the target
                if (me->IsWithinMeleeRange(me->GetVictim()))
                {
                    if (events.GetTimeUntilEvent(EVENT_SMASH) >= 2000)
                    {
                        me->AttackerStateUpdate(me->GetVictim());
                        me->resetAttackTimer();
                    }
                    return;
                }

                me->CastSpell(me->GetVictim(), SPELL_PETRIFYING_BREATH, false);
                me->resetAttackTimer();
            }
        }

        // try to get ranged target, not too far away
        Unit* GetEyeBeamTarget()
        {
            std::vector<Player*> playerTargets;
            std::list<HostileReference*> const& threatList = me->getThreatManager().getThreatList();
            for (auto& i : threatList)
            {
                if (Unit* unit = i->getTarget())
                {
                    if (Player* player = unit->ToPlayer())
                    {
                        if (player->isDead() || player->HasAura(SPELL_STONE_GRIP_DOT) || player->IsGameMaster() ||
                            player->GetDistance(me->GetPosition()) < 20.0f || player->GetDistance(me->GetPosition()) > 60.0f)
                            continue;

                        playerTargets.push_back(player);
                    }
                }
            }

            uint32 requiredSize = 3;
            if (Is25ManRaid())
                requiredSize = 7;

            if (playerTargets.size() < requiredSize)
                return nullptr;
            else
                return Trinity::Containers::SelectRandomContainerElement(playerTargets);
        }
    };
};

// also used for left arm, all functions except JustDied wont be used by left arm
class boss_kologarn_arms : public CreatureScript
{
public:
    boss_kologarn_arms() : CreatureScript("boss_kologarn_arms") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_kologarn_armsAI (pCreature);
    }

    struct boss_kologarn_armsAI : public ScriptedAI
    {
        boss_kologarn_armsAI(Creature* c) : ScriptedAI(c) { }

        int32 _damageDone;
        bool _combatStarted;

        void EnterEvadeMode() { }
        void AttackStart(Unit*) { }
        void UpdateAI(uint32 /*diff*/) { }
        void MoveInLineOfSight(Unit* /*who*/) override { }

        float GetMeleeRadianRange() const override { return 3.49066f; }

        void Reset()
        {
            _combatStarted = false;
            _damageDone = 0;
        }

        void SetData(uint32 type, uint32 value) override
        {
            if (type == DATA_RESET_DAMAGE_REQUIREMENTS)
                _damageDone = 0;
        }

        void PassengerBoarded(Unit* who, int8 seatId, bool apply)
        {
            if (apply)
            {
                //who->ClearUnitState(UNIT_STATE_ONVEHICLE);
                if (!_damageDone)
                    _damageDone = RAID_MODE(100000, 480000);
            }
        }

        void DamageTaken(Unit* who, uint32& damage, DamageEffectType, SpellSchoolMask)
        {
            if (!_combatStarted)
                if (InstanceScript* instance = me->GetInstanceScript())
                    if (Creature* cr = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_KOLOGARN)))
                    {
                        _combatStarted = true;
                        if (!cr->IsInCombat() && who)
                            cr->AI()->AttackStart(who);
                    }

            if (_damageDone > 0)
            {
                _damageDone -= damage;
                if (_damageDone <= 0 || damage >= me->GetHealth())
                    me->RemoveAurasByType(SPELL_AURA_CONTROL_VEHICLE);
            }
        }

        void JustDied(Unit*)
        {
            float x, y, z;
            // left arm
            if( me->GetEntry() == NPC_LEFT_ARM )
            {
                x = 1776.97f; y = -44.8396f; z = 448.888f;
            }
            else
            {
                x = 1777.82f; y = -3.50803f; z = 448.888f;
            }

            if (Creature *cr = me->SummonTrigger(x, y, z, 0, 5000))
            {
                cr->CastSpell(cr, SPELL_RUBBLE_FALL, true);

                if (me->GetInstanceScript())
                    if (Creature* kologarn = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_KOLOGARN)))
                        for (uint8 i = 0; i < 5; ++i)
                            if (Creature* cr2 = kologarn->SummonCreature(NPC_RUBBLE_SUMMON, cr->GetPositionX()+irand(-5,5), cr->GetPositionY()+irand(-5,5), cr->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000))
                            {
                                cr2->SetInCombatWithZone();
                                if (Unit *target = SelectTargetFromPlayerList(100))
                                    cr2->AI()->AttackStart(target);
                            }
            }

            if (me->GetInstanceScript())
                if (Creature* cr = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_KOLOGARN)))
                    cr->AI()->DoAction(DATA_KOLOGARN_RUBBLE_ACHIEV);

            me->ExitVehicle();
        }
    };
};

class boss_kologarn_eyebeam : public CreatureScript
{
public:
    boss_kologarn_eyebeam() : CreatureScript("boss_kologarn_eyebeam") { }

    struct boss_kologarn_eyebeamAI : public ScriptedAI
    {
        boss_kologarn_eyebeamAI(Creature* creature) : ScriptedAI(creature), _damaged(false)
        {
            chaseTargetGUID = 0;
        }

        void SetGUID(uint64 guid, int32 type /*= 0 */) override
        {
            if (type == DATA_CHASE_GUID)
            {
                chaseTargetGUID = guid;
                if (Player* target = ObjectAccessor::GetPlayer(*me, chaseTargetGUID))
                    pos = target->GetPosition();
            }
        }

        void Reset() override
        {
            me->SetSpeedRate(MOVE_WALK, 1.0f);
            me->SetSpeedRate(MOVE_RUN, 1.0f);
            events.Reset();
            events.ScheduleEvent(EVENT_EYEBEAM_FORM, 1s);
            events.ScheduleEvent(EVENT_BEAM_CHASE, 1.7s);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (auto eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_EYEBEAM_FORM:
                    {
                        me->GetMotionMaster()->MovePoint(1, pos);
                        break;
                    }
                    case EVENT_BEAM_CHASE:
                    {
                        if (Player* target = ObjectAccessor::FindPlayer(chaseTargetGUID))
                        {
                            me->GetMotionMaster()->MovePoint(1, target->GetPosition());
                        }
                        events.ScheduleEvent(EVENT_BEAM_CHASE, 250);
                        break;
                    }
                }
            }
            // No melee attacks
        }

        void DamageDealt(Unit* /*victim*/, uint32& damage, DamageEffectType /*damageType*/)
        {
            if (damage > 0 && !_damaged && me->GetInstanceScript())
            {
                _damaged = true;
                if (Creature* cr = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_KOLOGARN)))
                    cr->AI()->DoAction(DATA_KOLOGARN_LOOKS_ACHIEV);
            }
        }
    private:
        bool _damaged;
        uint64 chaseTargetGUID;
        EventMap events;
        Position pos;
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_kologarn_eyebeamAI(pCreature);
    }
};


// predicate function to select non main tank target
class StoneGripTargetSelector : public std::unary_function<Unit*, bool>
{
    public:
        StoneGripTargetSelector(Creature* me, Unit const* victim) : _me(me), _victim(victim) {}

        bool operator() (WorldObject* target) const
        {
            if (target == _victim)
                return true;

            if (target->GetTypeId() != TYPEID_PLAYER)
                return true;

            if (target->ToPlayer()->HasAura(SPELL_FOCUSED_EYEBEAM_HIDDEN_AURA))
                return true;

            if (target->GetDistance(_me->GetPosition()) > 60.f)
                return true;

            return false;
        }

        Creature* _me;
        Unit const* _victim;
};

class spell_ulduar_stone_grip_cast_target : public SpellScriptLoader
{
    public:
        spell_ulduar_stone_grip_cast_target() : SpellScriptLoader("spell_ulduar_stone_grip_cast_target") { }

        class spell_ulduar_stone_grip_cast_target_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ulduar_stone_grip_cast_target_SpellScript);

            bool Load()
            {
                if (GetCaster()->GetTypeId() != TYPEID_UNIT)
                    return false;
                return true;
            }

            void FilterTargetsInitial(std::list<WorldObject*>& targets)
            {
                // Remove "main tank" and non-player targets
                targets.remove_if (StoneGripTargetSelector(GetCaster()->ToCreature(), GetCaster()->GetVictim()));
                // Maximum affected targets per difficulty mode
                uint32 maxTargets = 1;
                if (GetSpellInfo()->Id == 63981)
                    maxTargets = 3;

                // Return a random amount of targets based on maxTargets
                while (maxTargets < targets.size())
                {
                    std::list<WorldObject*>::iterator itr = targets.begin();
                    advance(itr, urand(0, targets.size()-1));
                    targets.erase(itr);
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ulduar_stone_grip_cast_target_SpellScript::FilterTargetsInitial, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ulduar_stone_grip_cast_target_SpellScript();
        }
};

class spell_ulduar_stone_grip : public SpellScriptLoader
{
    public:
        spell_ulduar_stone_grip() : SpellScriptLoader("spell_ulduar_stone_grip") { }

        class spell_ulduar_stone_grip_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ulduar_stone_grip_AuraScript);

            void OnRemoveStun(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Player* owner = GetOwner()->ToPlayer())
                    owner->RemoveAurasDueToSpell(aurEff->GetAmount());
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_ulduar_stone_grip_AuraScript::OnRemoveStun, EFFECT_2, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_ulduar_stone_grip_AuraScript();
        }
};

class spell_ulduar_squeezed_lifeless : public SpellScriptLoader
{
    public:
        spell_ulduar_squeezed_lifeless() : SpellScriptLoader("spell_ulduar_squeezed_lifeless") { }

        class spell_ulduar_squeezed_lifeless_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ulduar_squeezed_lifeless_SpellScript);

            void HandleInstaKill(SpellEffIndex effIndex)
            {
                if (!GetHitPlayer() || !GetHitPlayer()->GetVehicle())
                    return;

                // Hack to set correct position is in _ExitVehicle()
                Position pos(1756.25f + frand(-3.f, 3.f), -8.3f + frand(-3.f, 3.f), 449.0f);
                GetHitPlayer()->Relocate(pos);
                GetHitPlayer()->ExitVehicle();
                GetHitPlayer()->GetMotionMaster()->MoveJump(pos, 10, 10);            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_ulduar_squeezed_lifeless_SpellScript::HandleInstaKill, EFFECT_1, SPELL_EFFECT_INSTAKILL);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ulduar_squeezed_lifeless_SpellScript();
        }
};


class spell_ulduar_squeezed_lifeless_periodic : public SpellScriptLoader
{
public:
    spell_ulduar_squeezed_lifeless_periodic() : SpellScriptLoader("spell_ulduar_squeezed_lifeless_periodic") { }

    class spell_ulduar_squeezed_lifeless_periodic_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ulduar_squeezed_lifeless_periodic_AuraScript);

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE)
                return;

            if (GetTarget() && GetTarget()->GetVehicle())
            {
                Position pos(1756.25f + frand(-3.f, 3.f), -8.3f + frand(-3.f, 3.f), 449.0f);
                GetTarget()->Relocate(pos);
                GetTarget()->ExitVehicle();
                GetTarget()->GetMotionMaster()->MoveJump(pos, 10, 10);
            }
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_ulduar_squeezed_lifeless_periodic_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_ulduar_squeezed_lifeless_periodic_AuraScript();
    }
};

class spell_kologarn_stone_shout : public SpellScriptLoader
{
    public:
        spell_kologarn_stone_shout() :  SpellScriptLoader("spell_kologarn_stone_shout") { }

        class spell_kologarn_stone_shout_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_kologarn_stone_shout_AuraScript);

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                uint32 triggerSpellId = GetSpellInfo()->Effects[EFFECT_0].TriggerSpell;
                if (Unit* caster = GetCaster())
                    caster->CastSpell(caster, triggerSpellId, false);
            }

            void Register()
            {
                if (m_scriptSpellId == SPELL_STONE_SHOUT_10 || m_scriptSpellId == SPELL_STONE_SHOUT_25)
                    OnEffectPeriodic += AuraEffectPeriodicFn(spell_kologarn_stone_shout_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_kologarn_stone_shout_AuraScript();
        }

        class spell_kologarn_stone_shout_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_kologarn_stone_shout_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if (PlayerOrPetCheck());
            }

            void Register()
            {
                if (m_scriptSpellId != SPELL_STONE_SHOUT_10 && m_scriptSpellId != SPELL_STONE_SHOUT_25)
                    OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_kologarn_stone_shout_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_kologarn_stone_shout_SpellScript();
        }
};

class spell_kologarn_shockwave_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_kologarn_shockwave_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Trinity::UnitAuraCheck(true, GetCaster()->GetMap()->Is25ManRaid() ? SPELL_STONE_GRIP_DOT_25 : SPELL_STONE_GRIP_DOT_10));
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_kologarn_shockwave_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

class spell_kologarn_arms_despawn_deal_damage_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_kologarn_arms_despawn_deal_damage_SpellScript);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        uint32 damage = 0;

        if (GetHitUnit())
            damage = GetHitUnit()->GetMaxHealth() * 0.15f;

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_kologarn_arms_despawn_deal_damage_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class achievement_kologarn_looks_could_kill : public AchievementCriteriaScript
{
    public:
        achievement_kologarn_looks_could_kill() : AchievementCriteriaScript("achievement_kologarn_looks_could_kill") {}

        bool OnCheck(Player* player, Unit* target)
        {
            if (target)
                if (InstanceScript* instance = target->GetInstanceScript())
                    if (Creature* cr = ObjectAccessor::GetCreature(*target, instance->GetData64(TYPE_KOLOGARN)))
                        return cr->AI()->GetData(DATA_KOLOGARN_LOOKS_ACHIEV);

            return false;
        }
};

class achievement_kologarn_rubble_and_roll : public AchievementCriteriaScript
{
    public:
        achievement_kologarn_rubble_and_roll() : AchievementCriteriaScript("achievement_kologarn_rubble_and_roll") {}

        bool OnCheck(Player* player, Unit* target)
        {
            if (target)
                if (InstanceScript* instance = target->GetInstanceScript())
                    if (Creature* cr = ObjectAccessor::GetCreature(*target, instance->GetData64(TYPE_KOLOGARN)))
                        return cr->AI()->GetData(DATA_KOLOGARN_RUBBLE_ACHIEV);

            return false;
        }
};

class achievement_kologarn_with_open_arms : public AchievementCriteriaScript
{
    public:
        achievement_kologarn_with_open_arms() : AchievementCriteriaScript("achievement_kologarn_with_open_arms") {}

        bool OnCheck(Player* player, Unit* target)
        {
            if (target)
                if (InstanceScript* instance = target->GetInstanceScript())
                    if (Creature* cr = ObjectAccessor::GetCreature(*target, instance->GetData64(TYPE_KOLOGARN)))
                        return cr->AI()->GetData(DATA_KOLOGARN_ARMS_ACHIEV);

            return false;
        }
};

class at_kologarn_feet_ulduar : public AreaTriggerScript
{
public:
    at_kologarn_feet_ulduar() : AreaTriggerScript("at_kologarn_feet_ulduar") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
    {
        if (player->IsAlive())
        {
            if (InstanceScript* instance = player->GetInstanceScript())
            {
                if (instance->GetData(TYPE_KOLOGARN) == DONE)
                    player->NearTeleportTo(1776.064941f, -23.578545f, 448.805298f, 0.106107f);
                else
                    Unit::Kill(player, player, true);
            }
        }
        return true;
    }
};

void AddSC_boss_kologarn()
{
    // Npcs
    new boss_kologarn();
    new boss_kologarn_arms();
    new boss_kologarn_eyebeam();

    // Areatrigger
    new at_kologarn_feet_ulduar();

    // Spells
    new spell_ulduar_stone_grip_cast_target();
    new spell_ulduar_stone_grip();
    new spell_ulduar_squeezed_lifeless_periodic();
    new spell_ulduar_squeezed_lifeless();
    new spell_kologarn_stone_shout();
    new SpellScriptLoaderEx<spell_kologarn_shockwave_SpellScript>("spell_kologarn_shockwave");
    new SpellScriptLoaderEx<spell_kologarn_arms_despawn_deal_damage_SpellScript>("spell_kologarn_arms_despawn_deal_damage");

    // Achievements
    new achievement_kologarn_looks_could_kill();
    new achievement_kologarn_rubble_and_roll();
    new achievement_kologarn_with_open_arms();
}
