#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "ulduar.h"
#include "Vehicle.h"
#include "PassiveAI.h"
#include "SpellAuraEffects.h"
#include "Player.h"
#include "Opcodes.h"
#include "GridNotifiers.h"
#include "MoveSplineInit.h"

enum XT002Spells
{
    // BASIC
    SPELL_GRAVITY_BOMB_10                   = 63024,
    SPELL_GRAVITY_BOMB_25                   = 64234,
    SPELL_SEARING_LIGHT_10                  = 63018,
    SPELL_SEARING_LIGHT_25                  = 65121,
    SPELL_TYMPANIC_TANTARUM                 = 62776,
    SPELL_XT002_ENRAGE                      = 26662,

    // HELPERS
    SPELL_ARCING_SMASH                      = 8374,
    SPELL_TRAMPLE                           = 5568,
    SPELL_UPPERCUT                          = 10966,
    SPELL_BOOM                              = 62834,
    SPELL_SCRAP_REPAIR                      = 62832,

    // HEARTBREAK
    SPELL_HEART_OVERLOAD                    = 62789,
    SPELL_EXPOSED_HEART                     = 63849,
    SPELL_ENERGY_ORB                        = 62790,
    SPELL_ENERGY_ORB_TRIGGER                = 62826,
    SPELL_HEARTBREAK_10                     = 65737,
    SPELL_HEARTBREAK_25                     = 64193,

    // VOID ZONE
    SPELL_VOID_ZONE_SUMMON_10               = 64203,
    SPELL_VOID_ZONE_SUMMON_25               = 64235,
    SPELL_VOID_ZONE_DAMAGE                  = 46262,

    // SPARK
    SPELL_SPARK_SUMMON                      = 64210,
    SPELL_SPARK_DAMAGE_10                   = 64227,
    SPELL_SPARK_DAMAGE_25                   = 64236,
    SPELL_SPARK_MELEE                       = 64230,
    SPELL_ARCANE_POWER_STATE                = 49411,

    // Misc
    SPELL_ANIM_TANTRUM                      = 76092, // lil xt tantrum animation, cant find proper emote IDs. works the same
    SPELL_ANIM_TRAIN                        = 76114, // lil xt workout animation, works same on big XT
    SPELL_SCRAPBOT_RIDE_VEHICLE             = 47020
};

enum XT002Events
{
    EVENT_HEALTH_CHECK                      = 1,
    EVENT_GRAVITY_BOMB,
    EVENT_SEARING_LIGHT,
    EVENT_ENRAGE,
    EVENT_TYMPANIC_TANTARUM,
    EVENT_RESTORE,
    EVENT_START_SECOND_PHASE,
    EVENT_REMOVE_EMOTE
};

enum XT002NPCs
{
    NPC_VOID_ZONE                           = 34001,
    NPC_LIFE_SPARK                          = 34004,
    NPC_XT002_HEART                         = 33329,
    NPC_XS013_SCRAPBOT                      = 33343,
    NPC_XM024_PUMMELLER                     = 33344,
    NPC_XE321_BOOMBOT                       = 33346,
    NPC_PILE_TRIGGER                        = 33337
};

enum XT002Sounds
{
    XT_SOUND_AGGRO                          = 15724,
    XT_SOUND_HEART_OPEN                     = 15725,
    XT_SOUND_HEART_CLOSED                   = 15726,
    XT_SOUND_TANTARUM                       = 15727,
    XT_SOUND_SLAY1                          = 15728,
    XT_SOUND_SLAY2                          = 15729,
    XT_SOUND_ENRAGE                         = 15730,
    XT_SOUND_DEATH                          = 15731,
    XT_SOUND_SUMMON                         = 15732
};

enum XT002Misc
{
    HEART_VEHICLE_SEAT                      = 0,
    HEART_VEHICLE_SEAT_EXPOSED              = 1,

    ACTION_AWAKEN_HEART                     = -5,
    ACTION_HIDE_HEART                       = -4,
    ACTION_HEART_BROKEN                     = -3,

    ACHIEVEMENT_MUST_DECONSTRUCT_FASTER    = 21027,

    DATA_XT002_NERF_ENGINEERING             = 50,
    DATA_XT002_GRAVITY_ACHIEV               = 51,

    DATA_SPARK_FOLLOW_TARGET                = 52
};

Position const XTArenaCenterPos = { 816.491455f, -12.355629f, 409.803619f, 5.292682f };

struct boss_xt002AI : BossAI
{
    boss_xt002AI(Creature* creature) : BossAI(creature, TYPE_XT002), _healthCheck(75), _hardMode(false), _nerfAchievement(true), _gravityAchievement(true)
    {
        //boundaryHandler.SetBoundary(new RectangleBoundary(755.0f, 940.0f, -125.0f, 95.0f));
    }

    void RescheduleEvents()
    {
        events.RescheduleEvent(EVENT_GRAVITY_BOMB, urand(10000, 15000), 1);
        events.RescheduleEvent(EVENT_TYMPANIC_TANTARUM, 60000, 1);
        if (!_hardMode)
            events.RescheduleEvent(EVENT_HEALTH_CHECK, 2000, 1);
    }

    void Reset() override
    {
        _fightTimer = 0;
        _Reset();
        me->ResetPlayerDamageReq();
        me->ResetLootMode();
        me->AddLootMode(4); // normal emblem marker
        me->RemoveAllAuras();

        // first heart expose
        _healthCheck = 75;
        _hardMode = false;
        _nerfAchievement = true;
        _gravityAchievement = true;

        me->SetByteValue(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_STAND); // emerge
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
        me->SetControlled(false, UNIT_STATE_STUNNED);

        instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEVEMENT_MUST_DECONSTRUCT_FASTER);
        if (instance->GetData(TYPE_XT002) != DONE)
            instance->SetData(TYPE_XT002, NOT_STARTED);
        if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetData64(GO_XT002_DOORS)))
            go->SetGoState(GO_STATE_ACTIVE);
    }

    //! ToDo: ten override nie jest raczej poprawny
    void MoveInLineOfSight(Unit*) override { }

    void EnterEvadeMode() override
    {
        instance->SetData(TYPE_XT002, FAIL);
        _DespawnAtEvade();
    }

    bool CheckEvadeIfOutOfCombatArea() const override
    {
        return !me->IsWithinBox(XTArenaCenterPos, 106.f, 106.f, 30.0f);
    }

    void AttachHeart() const
    {
        if (Unit* heart = me->GetVehicleKit() ? me->GetVehicleKit()->GetPassenger(HEART_VEHICLE_SEAT) : nullptr)
            heart->SetHealth(heart->GetMaxHealth());
        else if (Creature* accessory = me->SummonCreature(NPC_XT002_HEART, *me, TEMPSUMMON_MANUAL_DESPAWN))
        {
            accessory->AddUnitTypeMask(UNIT_MASK_ACCESSORY);
            if (!me->HandleSpellClick(accessory, 0))
                accessory->DespawnOrUnsummon();
        }
    }

    void MovementInform(uint32 type, uint32 pointID) override
    {
        BossAI::MovementInform(type, pointID);

        if (type == WAYPOINT_MOTION_TYPE)
        {
            switch (pointID)
            {
                case 1:
                case 3:
                    DoCast(SPELL_ANIM_TANTRUM);
                    break;
                case 2:
                case 4:
                    me->SetFacingTo(3.14f);
                    DoCast(SPELL_ANIM_TRAIN);
                    break;
            }
        }
    }

    void PassengerBoarded(Unit* who, int8 seatId, bool apply) override
    {
        if (apply && seatId == HEART_VEHICLE_SEAT_EXPOSED && who->GetEntry() == NPC_XT002_HEART)
        {
            //! Riztazz: Move heart to proper offsets
            //! remove this piece of code when we extract m_attachement from game files (bone attachments)
            /*
            ServerToClient: SMSG_MONSTER_MOVE_TRANSPORT (0x02AE) Length: 61 ConnIdx: 0 Time: 07/04/2010 17:33:07.000 Number: 363654
            GUID: Full: 0xF130008231001885 Type: Creature Entry: 33329 Low: 6277
            Transport GUID: Full: 0xF15000820D001884 Type: Vehicle Entry: 33293 Low: 6276
            Transport Seat: 1
            Toggle AnimTierInTrans: false
            Position: X: 1.389038 Y: -0.01501465 Z: 20.14996
            Move Ticks: 101081
            Spline Type: FacingAngle (4)
            Facing Angle: 0
            Spline Flags: Transport (8388608)
            Move Time: 0
            Waypoints: 1
            Waypoint Endpoint: X: 6.6525 Y: 0.7791 Z: 2.66805
            */
            Movement::MoveSplineInit init(who);
            init.DisableTransportPathTransformations();
            init.MoveTo(6.6525f, 0.7791f, 2.66805f, false);
            init.Launch();

            if (me->GetVehicleKit())
                me->GetVehicleKit()->RelocatePassengers();
        }
    }

    void EnterCombat(Unit*) override
    {
        _fightTimer = getMSTime();
        me->RemoveAurasDueToSpell(SPELL_ANIM_TANTRUM);
        me->RemoveAurasDueToSpell(SPELL_ANIM_TRAIN);
        me->CastStop();

        if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF))
            _canCastDuringTantrum = true;
        else
            _canCastDuringTantrum = false;

        _EnterCombat();
        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);

        if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF))
            events.ScheduleEvent(EVENT_ENRAGE, RAID_MODE(7min, 10min), 0, 0);
        else
            events.ScheduleEvent(EVENT_ENRAGE, 10min, 0, 0);

        RescheduleEvents(); // Other events are scheduled here

        me->MonsterYell("New toys? For me? I promise I won't break them this time!", LANG_UNIVERSAL, nullptr);
        me->PlayDirectSound(XT_SOUND_AGGRO);

        instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEVEMENT_MUST_DECONSTRUCT_FASTER);
        instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEVEMENT_MUST_DECONSTRUCT_FASTER);
        instance->SetData(TYPE_XT002, IN_PROGRESS);
        if (auto go = ObjectAccessor::GetGameObject(*me, instance->GetData64(GO_XT002_DOORS)))
            go->SetGoState(GO_STATE_READY);

        me->CallForHelp(175.0f);
        AttachHeart();
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer() && !urand(0,2))
        {
            if (urand(0,1))
            {
                me->MonsterYell("I... I think I broke it.", LANG_UNIVERSAL, nullptr);
                me->PlayDirectSound(XT_SOUND_SLAY1);
            }
            else
            {
                me->MonsterYell("I guess it doesn't bend that way.", LANG_UNIVERSAL, nullptr);
                me->PlayDirectSound(XT_SOUND_SLAY2);
            }
        }
    }

    void JustDied(Unit* killer) override
    {
        if (Map* map = me->GetMap())
            CheckCreatureRecord(killer, me->GetCreatureTemplate()->Entry + _hardMode, Difficulty(map->GetDifficulty() + _hardMode * 2), "", 15000, _fightTimer);

        if (_hardMode)
            instance->SetData(DATA_XT_002_HARDMODE, DATA_XT_002_HARDMODE);
        _JustDied();
        me->MonsterYell("You are bad... Toys... Very... Baaaaad!", LANG_UNIVERSAL, nullptr);
        me->PlayDirectSound(XT_SOUND_DEATH);

        instance->SetData(TYPE_XT002, DONE);
        if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetData64(GO_XT002_DOORS)))
            go->SetGoState(GO_STATE_ACTIVE);
    }

    void DoAction(int32 param) override
    {
        if (param == DATA_XT002_NERF_ENGINEERING)
        {
            _nerfAchievement = false;
            return;
        }
        if (param == DATA_XT002_GRAVITY_ACHIEV)
        {
            _gravityAchievement = false;
            return;
        }

        if (!me->IsAlive() || _hardMode)
            return;

        // heart destory
        if (param == ACTION_HEART_BROKEN)
        {
            _hardMode = true;
            me->SetLootMode(3); // hard mode + normal loot
            me->RemoveLootMode(4); // remove normal mode marker
            me->AddLootMode(8); // hardmode emblem marker
            me->SetMaxHealth(me->GetMaxHealth());
            me->SetHealth(me->GetMaxHealth());
            me->SetByteValue(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_STAND); // emerge

            DoCastSelf(RAID_MODE(SPELL_HEARTBREAK_10, SPELL_HEARTBREAK_25), true);

            me->MonsterTextEmote("XT-002 Deconstructor's heart is severed from his body.", nullptr, true);
            events.ScheduleEvent(EVENT_REMOVE_EMOTE, 4000);
            return;
        }

        // damage from heart
        if (param > 0)
        {
            // avoid reducing health under 1
            int32 _final = std::min(param, int32(me->GetHealth() - 1));

            me->ModifyHealth(-_final);
            me->LowerPlayerDamageReq(_final);
        }
    }

    uint32 GetData(uint32 param) const override
    {
        if (param == DATA_XT002_NERF_ENGINEERING)
            return _nerfAchievement;
        else if (param == DATA_XT002_GRAVITY_ACHIEV)
            return _gravityAchievement;

        return 0;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        bool const _canContinueCasting = _canCastDuringTantrum && me->HasAura(SPELL_TYMPANIC_TANTARUM);
        /// allow to execute stuff while tantrum is up and mode is set to preNerf
        if (me->HasUnitState(UNIT_STATE_CASTING) && !_canContinueCasting)
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_HEALTH_CHECK:
                    if (_hardMode)
                        return;

                    if (me->HealthBelowPct(_healthCheck))
                    {
                        _healthCheck -= 25;
                        me->SetControlled(true, UNIT_STATE_STUNNED);
                        me->SetByteValue(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_SUBMERGED); // submerge with animation

                        me->MonsterYell("So tired. I will rest for just a moment!", LANG_UNIVERSAL, nullptr);
                        me->PlayDirectSound(XT_SOUND_HEART_OPEN);

                        events.CancelEventGroup(1);
                        events.ScheduleEvent(EVENT_START_SECOND_PHASE, 5s);
                        return;
                    }
                    events.Repeat(1000);
                    break;
                // Abilities events
                case EVENT_GRAVITY_BOMB:
                    me->CastCustomSpell(RAID_MODE(SPELL_GRAVITY_BOMB_10, SPELL_GRAVITY_BOMB_25), SPELLVALUE_MAX_TARGETS, 1, me, true);
                    events.ScheduleEvent(EVENT_SEARING_LIGHT, 10s, 1);
                    break;
                case EVENT_SEARING_LIGHT:
                    me->CastCustomSpell(RAID_MODE(SPELL_SEARING_LIGHT_10, SPELL_SEARING_LIGHT_25), SPELLVALUE_MAX_TARGETS, 1, me, true);
                    events.ScheduleEvent(EVENT_GRAVITY_BOMB, 10s, 1);
                    break;
                case EVENT_TYMPANIC_TANTARUM:
                    me->MonsterTextEmote("XT-002 Deconstructor begins to cause the earth to quake.", nullptr, true);
                    me->MonsterYell("NO! NO! NO! NO! NO!", LANG_UNIVERSAL, nullptr);
                    me->PlayDirectSound(XT_SOUND_TANTARUM);
                    DoCastSelf(SPELL_TYMPANIC_TANTARUM, true);
                    events.Repeat(60s);
                    return;
                case EVENT_ENRAGE:
                    me->MonsterYell("I'm tired of these toys. I don't want to play anymore!", LANG_UNIVERSAL, nullptr);
                    me->PlayDirectSound(XT_SOUND_SUMMON);
                    DoCastSelf(SPELL_XT002_ENRAGE, true);
                    break;
                    // Animation events
                case EVENT_START_SECOND_PHASE:
                {
                    me->MonsterTextEmote("XT-002 Deconstructor's heart is exposed and leaking energy.", nullptr, true);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    Unit* heart = me->GetVehicleKit() ? me->GetVehicleKit()->GetPassenger(HEART_VEHICLE_SEAT) : nullptr;
                    if (heart && heart->IsAIEnabled)
                        heart->GetAI()->DoAction(ACTION_AWAKEN_HEART);

                    events.ScheduleEvent(EVENT_RESTORE, 30s);
                    return;
                }
                // Restore from heartbreak
                case EVENT_RESTORE:
                {
                    if (_hardMode)
                        return;

                    me->MonsterYell("I'm ready to play!", LANG_UNIVERSAL, nullptr);
                    me->PlayDirectSound(XT_SOUND_HEART_CLOSED);

                    me->SetByteValue(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_STAND); // emerge
                                                                                        // Hide heart
                    if (Unit* heart = me->GetVehicleKit() ? me->GetVehicleKit()->GetPassenger(HEART_VEHICLE_SEAT_EXPOSED) : nullptr)
                        if (heart->IsAIEnabled)
                            heart->GetAI()->DoAction(ACTION_HIDE_HEART);

                    events.ScheduleEvent(EVENT_REMOVE_EMOTE, 4s);
                    return;
                }
                case EVENT_REMOVE_EMOTE:
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    me->SetControlled(false, UNIT_STATE_STUNNED);

                    RescheduleEvents();
                    return;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING) && !_canCastDuringTantrum)
                return;
        }

        EnterEvadeIfOutOfCombatArea();
        // Disabled by stunned state
        DoMeleeAttackIfReady();
    }

private:
    uint8 _healthCheck;
    uint32 _fightTimer;
    bool _hardMode;
    bool _nerfAchievement;
    bool _gravityAchievement;
    bool _canCastDuringTantrum;
};

struct npc_xt002_heartAI : PassiveAI
{
    npc_xt002_heartAI(Creature* creature) : PassiveAI(creature), summons(me), _damageDone(0), _timerSpawn(0), _spawnSelection(0), _pummelerCount(0)
    {
        instance = me->GetInstanceScript();
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
    }

    void Reset() override
    {
        PassiveAI::Reset();
        if (!instance)
            me->DespawnOrUnsummon();
    }

    void MoveInLineOfSight(Unit*) override { }
    void AttackStart(Unit*) override { }
    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
        if (Unit* owner = me->GetVehicleBase())
            if (owner->GetTypeId() == TYPEID_UNIT && owner->IsAIEnabled)
                owner->ToCreature()->AI()->JustSummoned(summon);
    }

    void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask) override
    {
        _damageDone += damage;
    }

    void SummonPiles() const
    {
        me->SummonCreature(NPC_PILE_TRIGGER, { 893.290f, 66.820f, 409.81f, 4.2f });
        me->SummonCreature(NPC_PILE_TRIGGER, { 898.099f, -88.9115f, 409.887f, 2.23402f });
        me->SummonCreature(NPC_PILE_TRIGGER, { 793.096f, -95.158f,  409.887f, 0.855211f });
        me->SummonCreature(NPC_PILE_TRIGGER, { 794.600f, 59.660f, 409.82f, 5.34f });
    }

    void DoAction(int32 param) override
    {
        if (param == ACTION_AWAKEN_HEART)
        {
            _pummelerCount = 0;
            _spawnSelection = 0;
            _damageDone = 0;
            _timerSpawn = 0;
            me->SetHealth(me->GetMaxHealth());
            DoCastSelf(SPELL_HEART_OVERLOAD, true);
            DoCastSelf(SPELL_EXPOSED_HEART, false);    // Channeled
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->ChangeSeat(HEART_VEHICLE_SEAT_EXPOSED, true);
            if (!summons.HasEntry(NPC_PILE_TRIGGER))
                SummonPiles();

            if (Creature* xt = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_XT002)))
            {
                me->SetOrientation(xt->GetOrientation() * M_PI / 180.f);
                me->SetFacingTo(xt->GetOrientation() * M_PI / 180.f);
            }
        }
        else if (param == ACTION_HIDE_HEART)
        {
            if (Creature* xt = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_XT002)))
            {
                if (xt->IsAIEnabled)
                {
                    xt->AI()->DoAction(_damageDone);
                    _damageDone = 0;
                }
            }

            me->ChangeSeat(HEART_VEHICLE_SEAT, false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->RemoveAllAurasOnDeath();
        }
    }

    void SendEnergyToCorner()
    {
        Unit* pile = nullptr;
        uint8 num = urand(1, 4);

        float const x = me->GetPositionX();
        float const y = me->GetPositionY();

        for (SummonList::const_iterator itr = summons.begin(); itr != summons.end(); ++itr)
        {
            if (Creature* summon = ObjectAccessor::GetCreature(*me, *itr))
                if (summon->GetEntry() == NPC_PILE_TRIGGER && !summon->IsWithinDist2d(x, y, 85.0f))
                {
                    pile = summon;
                    if (!--num)
                        break;
                }
        }

        if (pile)
            DoCast(pile, SPELL_ENERGY_ORB, true);
    }

    void SpellHitTarget(Unit* target, const SpellInfo*spellInfo) override
    {
        // spawn not-so-random robots
        if (spellInfo->Id == SPELL_ENERGY_ORB_TRIGGER && target->GetEntry() == NPC_PILE_TRIGGER)
            switch (_spawnSelection)
            {
                case 0:
                    for (uint8 i = 0; i < 5; ++i)
                        me->SummonCreature(NPC_XS013_SCRAPBOT, target->GetPositionX()+irand(-3, 3), target->GetPositionY()+irand(-3, 3), target->GetPositionZ()+2, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    _spawnSelection++;
                    break;
                case 1:
                    me->SummonCreature(NPC_XE321_BOOMBOT, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ()+2, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);
                    _spawnSelection++;
                    break;
                case 2:
                    for (uint8 i = 0; i < 5; ++i)
                        me->SummonCreature(NPC_XS013_SCRAPBOT, target->GetPositionX()+irand(-3, 3), target->GetPositionY()+irand(-3, 3), target->GetPositionZ()+2, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    _spawnSelection++;
                    break;
                case 3:
                    if(_pummelerCount < 2)
                        me->SummonCreature(NPC_XM024_PUMMELLER, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ()+2, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

                    _pummelerCount++;
                    _spawnSelection++;
                    break;
                case 4:
                    for (uint8 i = 0; i < 5; ++i)
                        me->SummonCreature(NPC_XS013_SCRAPBOT, target->GetPositionX()+irand(-3, 3), target->GetPositionY()+irand(-3, 3), target->GetPositionZ()+2, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    _spawnSelection = 0;
                    break;
                default:
                    break;
            }
    }

    void JustDied(Unit* /*victim*/) override
    {
        me->SetVisible(false);
        if (Creature* xt = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_XT002)))
            if (xt->IsAIEnabled)
                xt->AI()->DoAction(ACTION_HEART_BROKEN);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE))
        {
            _timerSpawn += diff;
            if (_timerSpawn >= 1900)
            {
                SendEnergyToCorner();
                _timerSpawn -= 1900;
            }
        }
    }

private:
    SummonList summons;
    uint32 _damageDone;
    uint32 _timerSpawn;
    uint8 _spawnSelection;
    uint8 _pummelerCount;
    InstanceScript* instance;
};

struct npc_xt002_scrapbotAI : PassiveAI
{
    npc_xt002_scrapbotAI(Creature* creature) : PassiveAI(creature), _locked(true)
    {
        instance = me->GetInstanceScript();
    }

    void Reset() override
    {
        if (!instance)
        {
            me->DespawnOrUnsummon();
            return;
        }

        me->SetRegeneratingHealth(false);
        me->StopMoving();
        me->SetFloatValue(UNIT_FIELD_COMBATREACH, 6.0f);
        _locked = true;
        _reached = false;
        me->SetWalk(true);
        _rangeCheckTimer = 500;

        if (Creature* xt = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_XT002)))
        {
            if (xt->GetPositionZ() > 411.0f) // he is on stairs... idiot cryness protection
                me->GetMotionMaster()->MovePoint(0, 884.028931f, -14.593809f, 409.786987f);
            else
                _locked = false;
        }
    }

    void JustDied(Unit* killer) override
    {
        // Nerf Scrapbots achievement
        if (killer->GetEntry() == NPC_XE321_BOOMBOT)
        {
            instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_SPELL_TARGET, 65037);
            instance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, 65037);
        }
    }

    void MovementInform(uint32 type, uint32 /*param*/) override
    {
        if (type == POINT_MOTION_TYPE)
        {
            _locked = false;
            return;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (_reached)
            return;

        if (!_locked)
        {
            if (me->GetInstanceScript())
            {
                if (Creature* xt = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_XT002)))
                {
                    me->GetMotionMaster()->MoveChase(xt);
                    _locked = true;
                }
            }
        }

        if (_rangeCheckTimer <= diff)
        {
            if (Creature* xt = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_XT002)))
            {
                if (me->IsWithinCombatRange(xt, 6.f))
                {
                    _reached = true;
                    if (xt->IsAlive())
                    {
                        if (xt->IsAIEnabled)
                            xt->AI()->DoAction(DATA_XT002_NERF_ENGINEERING);
                        xt->CastSpell(me, SPELL_SCRAP_REPAIR, true);
                        me->CastSpell(xt, SPELL_SCRAPBOT_RIDE_VEHICLE, true);
                    }

                    if (roll_chance_i(10))
                        me->MonsterTextEmote("XT-002 Deconstructor consumes scrap bot to repair himself.", nullptr, true);

                    me->DespawnOrUnsummon(1.5s);
                }

                me->GetMotionMaster()->Clear();
                _locked = false;
                _rangeCheckTimer = 500;
            }
        }
        else
            _rangeCheckTimer -= diff;
    }

private:
    InstanceScript* instance;
    bool _locked;
    bool _reached;
    uint32 _rangeCheckTimer;
};

enum Pummeler
{
    EVENT_ARCING_SMASH = 1,
    EVENT_TRAMPLE,
    EVENT_UPPERCUT
};

struct npc_xt002_pummellerAI : ScriptedAI
{
    npc_xt002_pummellerAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _events.ScheduleEvent(EVENT_ARCING_SMASH, 8s);
        _events.ScheduleEvent(EVENT_TRAMPLE, 11s);
        _events.ScheduleEvent(EVENT_UPPERCUT, 14s);

        if (Unit *target = SelectTargetFromPlayerList(200.0f))
            AttackStart(target);
        else
            me->DespawnOrUnsummon(500);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_ARCING_SMASH:
                    DoCastVictim(SPELL_ARCING_SMASH);
                    _events.Repeat(8000);
                    break;
                case EVENT_TRAMPLE:
                    DoCastVictim(SPELL_TRAMPLE);
                    _events.Repeat(11000);
                    break;
                case EVENT_UPPERCUT:
                    DoCastVictim(SPELL_UPPERCUT);
                    _events.Repeat(14000);
                    break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
};

class BoomEvent : public BasicEvent
{
    public:
        explicit BoomEvent(Creature* me) : _me(me) {}

        bool Execute(uint64 /*time*/, uint32 /*diff*/) override
        {
            // This hack is here because we suspect our implementation of spell effect execution on targets
            // is done in the wrong order. We suspect that EFFECT_0 needs to be applied on all targets,
            // then EFFECT_1, etc - instead of applying each effect on target1, then target2, etc.
            // The above situation causes the visual for this spell to be bugged, so we remove the instakill
            // effect and implement a script hack for that.

            WorldPacket data(SMSG_SPELLINSTAKILLLOG, 8 + 8 + 4);
            data << uint64(_me->GetGUID());
            data << uint64(_me->GetGUID());
            data << uint32(SPELL_BOOM);
            _me->SendMessageToSet(&data, false);

            Unit::Kill(_me, _me);
            return true;
        }

    private:
        Creature* _me;
};

struct npc_xt002_boombotAI : PassiveAI
{
    npc_xt002_boombotAI(Creature* creature) : PassiveAI(creature), _locked(true), _boomed(false)
    {
        me->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
        instance = me->GetInstanceScript();
    }

    void Reset() override
    {
        if (!instance)
        {
            me->DespawnOrUnsummon();
            return;
        }

        me->StopMoving();
        _locked = true;
        _boomed = false;
        me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);

        if (Creature* pXT002 = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_XT002)))
        {
            if (pXT002->GetPositionZ() > 411.0f) // he is on stairs... idiot cryness protection
                me->GetMotionMaster()->MovePoint(0, 884.028931f, -14.593809f, 409.786987f);
            else
                _locked = false;
        }
    }

    void Explode()
    {
        if (_boomed)
            return;

            _boomed = true; // Prevent recursive calls

        // Visual only seems to work if the instant kill event is delayed or the spell itself is delayed
        // Casting done from player and caster source has the same targetinfo flags,
        // so that can't be the issue
        // See BoomEvent class
        // Schedule 1s delayed
        me->CastSpell(me, SPELL_BOOM, true);
        me->m_Events.AddEvent(new BoomEvent(me), me->m_Events.CalculateTime(100));
    }

    void JustDied(Unit*) override
    {
        Explode();
    }

    void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask) override
    {
        if (_boomed)
            damage = 0;

        if (me->HealthBelowPctDamaged(50, damage) && !_boomed)
        {
            damage = 0;
            Explode();
        }
    }

    void MovementInform(uint32 type, uint32 /*param*/) override
    {
        if (type == POINT_MOTION_TYPE)
            _locked = false;
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        if (!_locked)
        {
            if (Creature* xt = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_XT002)))
            {
                me->GetMotionMaster()->MoveFollow(xt, 0.0f, 0.0f);
                _locked = true;
            }
        }
    }

private:
    InstanceScript* instance;
    bool _locked;
    bool _boomed;
};

struct npc_xt002_life_sparkAI : ScriptedAI
{
    explicit npc_xt002_life_sparkAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        if (InstanceScript* instance = me->GetInstanceScript())
            if (Creature* xt = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_XT002)))
                if (!xt->IsInCombat() || xt->IsInEvadeMode())
                    me->DespawnOrUnsummon();

        me->SetReactState(REACT_PASSIVE);
        scheduler.CancelAll();
        _playerGUID = 0;
        DoCastSelf(SPELL_ARCANE_POWER_STATE, true);
        DoCastSelf(RAID_MODE(SPELL_SPARK_DAMAGE_10, SPELL_SPARK_DAMAGE_25), true);
    }

    void SetGUID(uint64 guid, int32 data) override
    {
        if (data == DATA_SPARK_FOLLOW_TARGET)
        {
            _playerGUID = guid;

            scheduler.Schedule(2s, [this](TaskContext task)
            {
                me->SetReactState(REACT_AGGRESSIVE);
                if (Unit* object = ObjectAccessor::GetUnit(*me, _playerGUID))
                {
                    AttackStart(object);
                    DoZoneInCombat(me, 200.0f);
                }
                else // find anything
                    DoZoneInCombat(me, 200.0f);
            });
        }
    }

    void UpdateAI(uint32 diff) override
    {
        scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        if (me->isAttackReady() && me->GetVictim())
        {
            DoCastVictim(SPELL_SPARK_MELEE, true);
            me->resetAttackTimer();
        }
    }
private:
    TaskScheduler scheduler;
    uint64 _playerGUID;
};

class spell_xt002_tympanic_tantrum_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_xt002_tympanic_tantrum_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(PlayerOrPetCheck());
    }

    void RecalculateDamage()
    {
        if (GetHitUnit())
            SetHitDamage(GetHitUnit()->CountPctFromMaxHealth(GetHitDamage()));
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_xt002_tympanic_tantrum_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ENEMY);
        OnHit += SpellHitFn(spell_xt002_tympanic_tantrum_SpellScript::RecalculateDamage);
    }
};

class spell_xt002_gravity_bomb_aura_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_xt002_gravity_bomb_aura_AuraScript);

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Player* player = GetOwner()->ToPlayer())
            if (Unit* xt002 = GetCaster())
                if (xt002->HasAura(aurEff->GetAmount()))   // Heartbreak aura indicating hard mode
                    if (Creature* voidZone = xt002->SummonCreature(NPC_VOID_ZONE, player->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 180000))
                        voidZone->CastSpell(voidZone, SPELL_VOID_ZONE_DAMAGE, true);
    }

    void OnPeriodic(AuraEffect const* aurEff)
    {
        Unit* xt = GetCaster();
        if (!xt)
            return;

        Unit* owner = GetOwner()->ToUnit();
        if (!owner)
            return;

        if (aurEff->GetAmount() >= int32(owner->GetHealth()) && xt->IsAIEnabled)
            xt->GetAI()->DoAction(DATA_XT002_GRAVITY_ACHIEV);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_xt002_gravity_bomb_aura_AuraScript::OnPeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE);
        AfterEffectRemove += AuraEffectRemoveFn(spell_xt002_gravity_bomb_aura_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_xt002_gravity_bomb_aura_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_xt002_gravity_bomb_aura_SpellScript);

    void SelectTarget(std::list<WorldObject*>& targets)
    {
        if (Unit* victim = GetCaster()->GetVictim())
            targets.remove_if(Trinity::ObjectGUIDCheck(victim->GetGUID(), true));
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_xt002_gravity_bomb_aura_SpellScript::SelectTarget, EFFECT_ALL, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class spell_xt002_gravity_bomb_damage_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_xt002_gravity_bomb_damage_SpellScript);

    void HandleScript(SpellEffIndex /*eff*/)
    {
        Unit* caster = GetCaster();
        if (!caster || !caster->IsAIEnabled)
            return;

        if (GetHitDamage() >= int32(GetHitUnit()->GetHealth()))
            caster->GetAI()->DoAction(DATA_XT002_GRAVITY_ACHIEV);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_xt002_gravity_bomb_damage_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_xt002_searing_light_spawn_life_spark_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_xt002_searing_light_spawn_life_spark_AuraScript);

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Player* player = GetOwner()->ToPlayer())
        {
            if (Unit* xt = GetCaster())
                if (xt->HasAura(aurEff->GetAmount()))   // Heartbreak aura indicating hard mode
                    if (Creature* spark = xt->SummonCreature(NPC_LIFE_SPARK, player->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 180000))
                        if (spark->IsAIEnabled)
                            spark->AI()->SetGUID(player->GetGUID(), DATA_SPARK_FOLLOW_TARGET);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_xt002_searing_light_spawn_life_spark_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_xt002_searing_light_spawn_life_spark_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_xt002_searing_light_spawn_life_spark_SpellScript);

    void SelectTarget(std::list<WorldObject*>& targets)
    {
        if (Unit* victim = GetCaster()->GetVictim())
            targets.remove_if(Trinity::ObjectGUIDCheck(victim->GetGUID(), true));
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_xt002_searing_light_spawn_life_spark_SpellScript::SelectTarget, EFFECT_ALL, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class achievement_xt002_nerf_engineering : public AchievementCriteriaScript
{
    public:
        achievement_xt002_nerf_engineering() : AchievementCriteriaScript("achievement_xt002_nerf_engineering") {}

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            if (!target)
                return false;

            InstanceScript* instance = target->GetInstanceScript();
            Creature* xt = ObjectAccessor::GetCreature(*target, instance->GetData64(TYPE_XT002));
            if (instance && xt && xt->IsAIEnabled)
                return xt->AI()->GetData(DATA_XT002_NERF_ENGINEERING);

            return false;
        }
};

class achievement_xt002_nerf_gravity_bombs : public AchievementCriteriaScript
{
    public:
        achievement_xt002_nerf_gravity_bombs() : AchievementCriteriaScript("achievement_xt002_nerf_gravity_bombs") {}

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            if (!target)
                return false;

            InstanceScript* instance = target->GetInstanceScript();
            Creature* xt = ObjectAccessor::GetCreature(*target, instance->GetData64(TYPE_XT002));
            if (instance && xt && xt->IsAIEnabled)
                return xt->AI()->GetData(DATA_XT002_GRAVITY_ACHIEV);

            return false;
        }
};

void AddSC_boss_xt002()
{
    // Npcs
    new CreatureAILoader<boss_xt002AI>("boss_xt002");
    new CreatureAILoader<npc_xt002_heartAI>("npc_xt002_heart");
    new CreatureAILoader<npc_xt002_scrapbotAI>("npc_xt002_scrapbot");
    new CreatureAILoader<npc_xt002_pummellerAI>("npc_xt002_pummeller");
    new CreatureAILoader<npc_xt002_boombotAI>("npc_xt002_boombot");
    new CreatureAILoader<npc_xt002_life_sparkAI>("npc_xt002_life_spark");

    // Spells
    new SpellScriptLoaderEx<spell_xt002_tympanic_tantrum_SpellScript>("spell_xt002_tympanic_tantrum");
    new SpellAuraScriptLoaderEx<spell_xt002_gravity_bomb_aura_SpellScript, spell_xt002_gravity_bomb_aura_AuraScript>("spell_xt002_gravity_bomb_aura");
    new SpellScriptLoaderEx<spell_xt002_gravity_bomb_damage_SpellScript>("spell_xt002_gravity_bomb_damage");
    new SpellAuraScriptLoaderEx<spell_xt002_searing_light_spawn_life_spark_SpellScript, spell_xt002_searing_light_spawn_life_spark_AuraScript>("spell_xt002_searing_light_spawn_life_spark");

    // Achievements
    new achievement_xt002_nerf_engineering();
    new achievement_xt002_nerf_gravity_bombs();
}
