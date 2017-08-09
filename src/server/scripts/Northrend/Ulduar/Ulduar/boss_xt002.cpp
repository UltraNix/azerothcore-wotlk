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
};

#define SPELL_GRAVITY_BOMB         RAID_MODE(SPELL_GRAVITY_BOMB_10, SPELL_GRAVITY_BOMB_25)
#define SPELL_SEARING_LIGHT        RAID_MODE(SPELL_SEARING_LIGHT_10, SPELL_SEARING_LIGHT_25)
#define SPELL_HEARTBREAK           RAID_MODE(SPELL_HEARTBREAK_10, SPELL_HEARTBREAK_25)
#define SPELL_SPARK_DAMAGE         RAID_MODE(SPELL_SPARK_DAMAGE_10, SPELL_SPARK_DAMAGE_25)

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

enum NPCs
{
    NPC_VOID_ZONE                           = 34001,
    NPC_LIFE_SPARK                          = 34004,
    NPC_XT002_HEART                         = 33329,
    NPC_XS013_SCRAPBOT                      = 33343,
    NPC_XM024_PUMMELLER                     = 33344,
    NPC_XE321_BOOMBOT                       = 33346,
    NPC_PILE_TRIGGER                        = 33337,
};

enum Sounds
{
    XT_SOUND_AGGRO                          = 15724,
    XT_SOUND_HEART_OPEN                     = 15725,
    XT_SOUND_HEART_CLOSED                   = 15726,
    XT_SOUND_TANTARUM                       = 15727,
    XT_SOUND_SLAY1                          = 15728,
    XT_SOUND_SLAY2                          = 15729,
    XT_SOUND_ENRAGE                         = 15730,
    XT_SOUND_DEATH                          = 15731,
    XT_SOUND_SUMMON                         = 15732,
};

enum Misc
{
    HEART_VEHICLE_SEAT                      = 0,

    ACTION_AWAKEN_HEART                     = -5,
    ACTION_HIDE_HEART                       = -4,
    ACTION_HEART_BROKEN                     = -3,

    ACHIEVEMENT_MUST_DECONSTRUCT_FASTER    = 21027,

    DATA_XT002_NERF_ENGINEERING             = 50,
    DATA_XT002_GRAVITY_ACHIEV               = 51,
};

struct boss_xt002AI : BossAI
{
    explicit boss_xt002AI(Creature* creature) : BossAI(creature, TYPE_XT002), _healthCheck(75), _hardMode(false), _nerfAchievement(true), _gravityAchievement(true)
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
        _Reset();
        me->ResetLootMode();
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
        instance->SetData(TYPE_XT002, NOT_STARTED);
        if (auto go = ObjectAccessor::GetGameObject(*me, instance->GetData64(GO_XT002_DOORS)))
            go->SetGoState(GO_STATE_ACTIVE);
    }

    void MoveInLineOfSight(Unit*) override { }
    void JustSummoned(Creature* cr) override { summons.Summon(cr); }
    void SummonedCreatureDespawn(Creature* cr) override { summons.Despawn(cr); }

    void EnterEvadeMode() override
    {
        instance->SetData(TYPE_XT002, FAIL);
        _DespawnAtEvade();
    }

    void AttachHeart() const
    {
        if (auto heart = me->GetVehicleKit() ? me->GetVehicleKit()->GetPassenger(HEART_VEHICLE_SEAT) : nullptr)
            heart->SetHealth(heart->GetMaxHealth());
        else if (Creature* accessory = me->SummonCreature(NPC_XT002_HEART, *me, TEMPSUMMON_MANUAL_DESPAWN))
        {
            accessory->AddUnitTypeMask(UNIT_MASK_ACCESSORY);
            if (!me->HandleSpellClick(accessory, 0))
                accessory->DespawnOrUnsummon();
        }
    }

    void EnterCombat(Unit*) override
    {
        _EnterCombat();
        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
        events.ScheduleEvent(EVENT_ENRAGE, 600000, 0, 0);
        RescheduleEvents(); // Other events are scheduled here

        me->setActive(true);
        me->MonsterYell("New toys? For me? I promise I won't break them this time!", LANG_UNIVERSAL, nullptr);
        me->PlayDirectSound(XT_SOUND_AGGRO);

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

    void JustDied(Unit* /*victim*/) override
    {
        _JustDied();
        me->MonsterYell("You are bad... Toys... Very... Baaaaad!", LANG_UNIVERSAL, nullptr);
        me->PlayDirectSound(XT_SOUND_DEATH);

        instance->SetData(TYPE_XT002, DONE);
        if (auto go = ObjectAccessor::GetGameObject(*me, instance->GetData64(GO_XT002_DOORS)))
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
            me->SetMaxHealth(me->GetMaxHealth());
            me->SetHealth(me->GetMaxHealth());
            me->SetByteValue(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_STAND); // emerge

            DoCastSelf(SPELL_HEARTBREAK, true);
                
            me->MonsterTextEmote("XT-002 Deconstructor's heart is severed from his body.", nullptr, true);
            events.ScheduleEvent(EVENT_REMOVE_EMOTE, 4000);
            return;
        }

        // damage from heart
        if (param > 0)
        {
            // avoid reducing health under 1
            auto _final = std::min(param, int32(me->GetHealth() - 1));

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

        auto _25man = me->GetMap()->Is25ManRaid() && me->HasAura(SPELL_TYMPANIC_TANTARUM);

        if (me->HasUnitState(UNIT_STATE_CASTING) && !_25man)
            return;

        while (auto eventId = events.ExecuteEvent())
        {
            switch(eventId)
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
                        events.ScheduleEvent(EVENT_START_SECOND_PHASE, 5000);
                        return;
                    }
                    events.Repeat(1000);
                    break;
                    // Abilities events
                case EVENT_GRAVITY_BOMB:
                    me->CastCustomSpell(SPELL_GRAVITY_BOMB, SPELLVALUE_MAX_TARGETS, 1, me, true);
                    events.ScheduleEvent(EVENT_SEARING_LIGHT, 10000, 1);
                    break;
                case EVENT_SEARING_LIGHT:
                    me->CastCustomSpell(SPELL_SEARING_LIGHT, SPELLVALUE_MAX_TARGETS, 1, me, true);
                    events.ScheduleEvent(EVENT_GRAVITY_BOMB, 10000, 1);
                    break;
                case EVENT_TYMPANIC_TANTARUM:
                    me->MonsterTextEmote("XT-002 Deconstructor begins to cause the earth to quake.", nullptr, true);
                    me->MonsterYell("NO! NO! NO! NO! NO!", LANG_UNIVERSAL, nullptr);
                    me->PlayDirectSound(XT_SOUND_TANTARUM);
                    DoCastSelf(SPELL_TYMPANIC_TANTARUM, true);
                    events.Repeat(60000);
                    return;
                case EVENT_ENRAGE:
                    me->MonsterYell("I'm tired of these toys. I don't want to play anymore!", LANG_UNIVERSAL, nullptr);
                    me->PlayDirectSound(XT_SOUND_SUMMON);
                    DoCastSelf(SPELL_XT002_ENRAGE, true);
                    break;
                    // Animation events
                case EVENT_START_SECOND_PHASE:
                    me->MonsterTextEmote("XT-002 Deconstructor's heart is exposed and leaking energy.", nullptr, true);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    if (auto heart = me->GetVehicleKit() ? me->GetVehicleKit()->GetPassenger(HEART_VEHICLE_SEAT) : nullptr)
                        if (heart->IsAIEnabled)
                            heart->GetAI()->DoAction(ACTION_AWAKEN_HEART);

                    events.ScheduleEvent(EVENT_RESTORE, 30000);
                    return;
                    // Restore from heartbreak
                case EVENT_RESTORE:
                    if (_hardMode)
                        return;

                    me->MonsterYell("I'm ready to play!", LANG_UNIVERSAL, nullptr);
                    me->PlayDirectSound(XT_SOUND_HEART_CLOSED);

                    me->SetByteValue(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_STAND); // emerge
                                                                                        // Hide heart
                    if (auto heart = me->GetVehicleKit() ? me->GetVehicleKit()->GetPassenger(HEART_VEHICLE_SEAT) : nullptr)
                        if (heart->IsAIEnabled)
                            heart->GetAI()->DoAction(ACTION_HIDE_HEART);

                    events.ScheduleEvent(EVENT_REMOVE_EMOTE, 4000);
                    return;
                case EVENT_REMOVE_EMOTE:
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    me->SetControlled(false, UNIT_STATE_STUNNED);

                    RescheduleEvents();
                    return;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING) && !_25man)
                return;
        }

        // Disabled by stunned state
        DoMeleeAttackIfReady();
    }

private:
    uint8 _healthCheck;
    bool _hardMode;
    bool _nerfAchievement;
    bool _gravityAchievement;
};

struct npc_xt002_heartAI : PassiveAI
{
    explicit npc_xt002_heartAI(Creature* creature) : PassiveAI(creature), summons(me), _damageDone(0), _timerSpawn(0), _spawnSelection(0), _pummelerCount(0)
    {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
    }

    void MoveInLineOfSight(Unit*) override { }
    void AttackStart(Unit*) override { }
    void JustSummoned(Creature* cr) override
    {
        summons.Summon(cr);
        if (auto owner = me->GetVehicleBase())
            if (owner->GetTypeId() == TYPEID_UNIT)
                if (owner->IsAIEnabled)
                    owner->ToCreature()->AI()->JustSummoned(cr);
    }

    void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask) override
    {
        _damageDone += damage;
    }

    void SummonPiles() const
    {
        me->SummonCreature(NPC_PILE_TRIGGER, 893.290f, 66.820f, 409.81f, 4.2f);
        me->SummonCreature(NPC_PILE_TRIGGER, 898.099f, -88.9115f, 409.887f, 2.23402f);
        me->SummonCreature(NPC_PILE_TRIGGER, 793.096f, -95.158f,  409.887f, 0.855211f);
        me->SummonCreature(NPC_PILE_TRIGGER, 794.600f, 59.660f, 409.82f, 5.34f);
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

            if (!summons.HasEntry(NPC_PILE_TRIGGER))
                SummonPiles();

            if (auto pXT002 = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_XT002)))
            {
                me->SetOrientation(pXT002->GetOrientation() * M_PI / 180);
                me->SetFacingTo(pXT002->GetOrientation() * M_PI / 180);
            }
        }
        else if (param == ACTION_HIDE_HEART)
        {
            if (auto pXT002 = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_XT002)))
                if (pXT002->IsAIEnabled)
                {
                    pXT002->AI()->DoAction(_damageDone);
                    _damageDone = 0;
                }
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->RemoveAllAurasOnDeath();
        }
    }

    void SendEnergyToCorner()
    {
        Unit* pile = nullptr;
        uint8 num = urand(1, 4);

        auto x = me->GetPositionX();
        auto y = me->GetPositionY();

        for (SummonList::const_iterator itr = summons.begin(); itr != summons.end(); ++itr)
            if (auto summon = ObjectAccessor::GetCreature(*me, *itr))
                if (summon->GetEntry() == NPC_PILE_TRIGGER && !summon->IsWithinDist2d(x, y, 85.0f))
                {
                    pile = summon;
                    if (--num == 0)
                        break;
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
        if (me->GetInstanceScript())
            if (auto XT002 = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_XT002)))
                if (XT002->IsAIEnabled)
                    XT002->AI()->DoAction(ACTION_HEART_BROKEN);
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
};

struct npc_xt002_scrapbotAI : PassiveAI
{
    explicit npc_xt002_scrapbotAI(Creature* creature) : PassiveAI(creature), _locked(true) { }

    void Reset() override
    {
        me->StopMoving();
        _locked = true;
        me->SetWalk(true);

        if (me->GetInstanceScript())
            if (auto pXT002 = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_XT002)))
            {
                if (pXT002->GetPositionZ() > 411.0f) // he is on stairs... idiot cryness protection
                    me->GetMotionMaster()->MovePoint(0, 884.028931f, -14.593809f, 409.786987f);
                else
                    _locked = false;
            }
    }

    void JustDied(Unit* killer) override
    {
        // Nerf Scrapbots achievement
        if (killer->GetEntry() == NPC_XE321_BOOMBOT)
            if (me->GetInstanceScript())
            {
                me->GetInstanceScript()->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_SPELL_TARGET, 65037);
                me->GetInstanceScript()->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, 65037);
            }
    }

    // tc idiots, they use updateAI, while we have movementinform :)
    void MovementInform(uint32 type, uint32 /*param*/) override
    {
        if (type == POINT_MOTION_TYPE)
        {
            _locked = false;
            return;
        }

        // we reached the target :)
        if (type == FOLLOW_MOTION_TYPE && me->GetInstanceScript())
            if (auto pXT002 = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_XT002)))
            {
                if (pXT002->IsAlive())
                {
                    if (pXT002->IsAIEnabled)
                        pXT002->AI()->DoAction(DATA_XT002_NERF_ENGINEERING);
                    pXT002->ModifyHealth(pXT002->GetMaxHealth() * 0.01f);
                }

                if (!urand(0,2))
                    me->MonsterTextEmote("XT-002 Deconstructor consumes scrap bot to repair himself.", nullptr, true);
                    
                me->DespawnOrUnsummon(1);
            }
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        if (!_locked)
        {
            if (me->GetInstanceScript())
                if (auto pXT002 = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_XT002)))
                {
                    me->GetMotionMaster()->MoveFollow(pXT002, 0.0f, 0.0f);
                    _locked = true;
                }
        }
    }

private:
    bool _locked;
};

enum Pummeler
{
    EVENT_ARCING_SMASH = 1,
    EVENT_TRAMPLE,
    EVENT_UPPERCUT
};

struct npc_xt002_pummellerAI : ScriptedAI
{
    explicit npc_xt002_pummellerAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _events.ScheduleEvent(EVENT_ARCING_SMASH, 8000);
        _events.ScheduleEvent(EVENT_TRAMPLE, 11000);
        _events.ScheduleEvent(EVENT_UPPERCUT, 14000);

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

        while (auto eventId = _events.ExecuteEvent())
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

            _me->CastSpell(_me, SPELL_BOOM, false);
            return true;
        }

    private:
        Creature* _me;
};

struct npc_xt002_boombotAI : PassiveAI
{
    explicit npc_xt002_boombotAI(Creature* creature) : PassiveAI(creature), _locked(true), _boomed(false) { }

    void Reset() override
    {
        me->StopMoving();
        _locked = true;
        _boomed = false;
        me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);

        if (me->GetInstanceScript())
            if (auto pXT002 = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_XT002)))
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

        WorldPacket data(SMSG_SPELLINSTAKILLLOG, 8+8+4);
        data << uint64(me->GetGUID());
        data << uint64(me->GetGUID());
        data << uint32(SPELL_BOOM);
        me->SendMessageToSet(&data, false);

        Unit::Kill(me, me);

        // Visual only seems to work if the instant kill event is delayed or the spell itself is delayed
        // Casting done from player and caster source has the same targetinfo flags,
        // so that can't be the issue
        // See BoomEvent class
        // Schedule 1s delayed
        me->m_Events.AddEvent(new BoomEvent(me), me->m_Events.CalculateTime(1*IN_MILLISECONDS));
    }

    void JustDied(Unit*) override
    {
        me->m_Events.AddEvent(new BoomEvent(me), me->m_Events.CalculateTime(1*IN_MILLISECONDS));
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

    // tc idiots, they use updateAI, while we have movementinform :)
    void MovementInform(uint32 type, uint32 /*param*/) override
    {
        if (type == POINT_MOTION_TYPE)
            _locked = false;
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        if (!_locked)
        {
            if (me->GetInstanceScript())
                if (auto pXT002 = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_XT002)))
                {
                    me->GetMotionMaster()->MoveFollow(pXT002, 0.0f, 0.0f);
                    _locked = true;
                }
        }
    }

private:
    bool _locked;
    bool _boomed;
};

struct npc_xt002_life_sparkAI : ScriptedAI
{
    explicit npc_xt002_life_sparkAI(Creature* creature) : ScriptedAI(creature)
    {
        me->SetMaxHealth(RAID_MODE(54000, 172000 * 2));
        me->SetHealth(me->GetMaxHealth());
        DoCastSelf(SPELL_SPARK_DAMAGE, true);
    }

    void Reset() override
    {
        if (Unit *target = SelectTargetFromPlayerList(DEFAULT_COMBAT_REACH))
            AttackStart(target);
        else
            me->DespawnOrUnsummon();
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        if (!UpdateVictim())
            return;

        DoCastVictim(SPELL_SPARK_MELEE);
        DoMeleeAttackIfReady();
    }
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
        if (auto player = GetOwner()->ToPlayer())
            if (auto xt002 = GetCaster())
                if (xt002->HasAura(aurEff->GetAmount()))   // Heartbreak aura indicating hard mode
                    if (Creature* cr = xt002->SummonCreature(NPC_VOID_ZONE, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 180000))
                        cr->CastSpell(cr, SPELL_VOID_ZONE_DAMAGE, true);
    }

    void OnPeriodic(AuraEffect const* aurEff)
    {
        auto xt002 = GetCaster();
        if (!xt002)
            return;

        auto owner = GetOwner()->ToUnit();
        if (!owner)
            return;

        if (aurEff->GetAmount() >= int32(owner->GetHealth()))
            if (xt002->IsAIEnabled)
                xt002->GetAI()->DoAction(DATA_XT002_GRAVITY_ACHIEV);
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
        if (auto victim = GetCaster()->GetVictim())
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
        auto caster = GetCaster();
        if (!caster)
            return;

        if (GetHitDamage() >= int32(GetHitUnit()->GetHealth()))
            if (caster->IsAIEnabled)
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

    bool Load() override { x = 0.0f, y = 0.0f, z = 0.0f; return true; }

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (auto player = GetOwner()->ToPlayer())
        {
            auto x = player->GetPositionX();
            auto y = player->GetPositionY();
            auto z = player->GetPositionZ();

            if (auto xt002 = GetCaster())
                if (xt002->HasAura(aurEff->GetAmount()))   // Heartbreak aura indicating hard mode
                    xt002->SummonCreature(NPC_LIFE_SPARK, x, y, z, 0, TEMPSUMMON_TIMED_DESPAWN, 180000);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_xt002_searing_light_spawn_life_spark_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }

    float x, y, z;
};

class spell_xt002_searing_light_spawn_life_spark_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_xt002_searing_light_spawn_life_spark_SpellScript);

    void SelectTarget(std::list<WorldObject*>& targets)
    {
        if (auto victim = GetCaster()->GetVictim())
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
            if (target)
                if (auto instance = target->GetInstanceScript())
                    if (auto cr = ObjectAccessor::GetCreature(*target, instance->GetData64(TYPE_XT002)))
                        if (cr->IsAIEnabled)
                            return cr->AI()->GetData(DATA_XT002_NERF_ENGINEERING);
                        
            return false;
        }
};

class achievement_xt002_nerf_gravity_bombs : public AchievementCriteriaScript
{
    public:
        achievement_xt002_nerf_gravity_bombs() : AchievementCriteriaScript("achievement_xt002_nerf_gravity_bombs") {}

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            if (target)
                if (auto instance = target->GetInstanceScript())
                    if (auto cr = ObjectAccessor::GetCreature(*target, instance->GetData64(TYPE_XT002)))
                        if (cr->IsAIEnabled)
                            return cr->AI()->GetData(DATA_XT002_GRAVITY_ACHIEV);
                        
            return false;
        }
};

void AddSC_boss_xt002()
{
    // Npcs
    new CreatureAILoader<boss_xt002AI>("boss_xt002AI");
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
