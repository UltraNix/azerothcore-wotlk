#include "CreatureGroups.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "ulduar.h"
#include "Player.h"
#include "MoveSplineInit.h"

enum AuriayaSpells
{
    // BASIC
    SPELL_TERRIFYING_SCREECH               = 64386,
    SPELL_SENTINEL_BLAST_10                = 64389,
    SPELL_SENTINEL_BLAST_25                = 64678,
    SPELL_SONIC_SCREECH_10                 = 64422,
    SPELL_SONIC_SCREECH_25                 = 64688,
    SPELL_GUARDIAN_SWARM                   = 64396,
    SPELL_ENRAGE                           = 47008,
    SPELL_ACTIVATE_FERAL_DEFENDER          = 64449,

    // Sanctum Sentry
    SPELL_SAVAGE_POUNCE_10                = 64666,
    SPELL_SAVAGE_POUNCE_25                = 64374,
    SPELL_RIP_FLESH_10                    = 64375,
    SPELL_RIP_FLESH_25                    = 64667,
    SPELL_STRENGTH_OF_THE_PACK            = 64369,

    // Feral Defender
    SPELL_FERAL_ESSENCE                   = 64455,
    SPELL_FERAL_POUNCE_10                 = 64478,
    SPELL_FERAL_POUNCE_25                 = 64669,
    SPELL_FERAL_RUSH_10                   = 64496,
    SPELL_FERAL_RUSH_25                   = 64674,
    //SPELL_SEEPING_FERAL_ESSENCE_SUMMON  = 64457,
    SPELL_SEEPING_FERAL_ESSENCE_25        = 64676,
    SPELL_SEEPING_FERAL_ESSENCE_10        = 64458,
    SPELL_SHADOW_PAWS                     = 64479, // visual effect on feral defender paws
    SPELL_CRITICAL_HIT_REDUCE             = 64481, // reduces ability to crit by -999
    SPELL_FERAL_FULL_HEAL                 = 64460, // heals feral defende to full health
    SPELL_PERM_FEIGN_DEATH                = 58951, // this is what feral defender casts to appear dead
                                                   // currently unused due to this aura not removing properly ToDo: FixMe
    SPELL_SWARM_POUNCE                    = 64399, // Swarming guardian
    SPELL_SWARM_FOCUS                     = 65029
};

#define SPELL_SONIC_SCREECH               RAID_MODE(SPELL_SONIC_SCREECH_10, SPELL_SONIC_SCREECH_25)
#define SPELL_SENTINEL_BLAST              RAID_MODE(SPELL_SENTINEL_BLAST_10, SPELL_SENTINEL_BLAST_25)
#define SPELL_SAVAGE_POUNCE               RAID_MODE(SPELL_SAVAGE_POUNCE_10, SPELL_SAVAGE_POUNCE_25)
#define SPELL_RIP_FLESH                   RAID_MODE(SPELL_RIP_FLESH_10, SPELL_RIP_FLESH_25)
#define SPELL_FERAL_POUNCE                RAID_MODE(SPELL_FERAL_POUNCE_10, SPELL_FERAL_POUNCE_25)
#define SPELL_FERAL_RUSH                  RAID_MODE(SPELL_FERAL_RUSH_10, SPELL_FERAL_RUSH_25)
#define SPELL_SEEPING_FERAL_ESSENCE       RAID_MODE(SPELL_SEEPING_FERAL_ESSENCE_10, SPELL_SEEPING_FERAL_ESSENCE_25)

enum AuriayaNPC
{
    NPC_FERAL_DEFENDER                    = 34035,
    NPC_SEEPING_FERAL_ESSENCE             = 34098
};

enum AuriayaEvents
{
    EVENT_SUMMON_FERAL_DEFENDER           = 1,
    EVENT_TERRIFYING_SCREECH              = 2,
    EVENT_SONIC_SCREECH                   = 3,
    EVENT_GUARDIAN_SWARM                  = 4,
    EVENT_SENTINEL_BLAST                  = 5,
    EVENT_REMOVE_IMMUNE                   = 6,
    EVENT_ENRAGE                          = 9,
    EVENT_DEFENDER_RESPAWN                = 10
};

enum AuriayaSounds
{
    SOUND_AGGRO                           = 15473,
    SOUND_SLAY1                           = 15474,
    SOUND_SLAY2                           = 15475,
    SOUND_DEATH                           = 15476,
    SOUND_BERSERK                         = 15477,
    SOUND_WOUND                           = 15478
};

enum Misc
{
    ACTION_FERAL_RESPAWN                  = 1,
    ACTION_FERAL_DEATH                    = 2,
    ACTION_DESPAWN_ADDS                   = 3,
    ACTION_FERAL_DEATH_WITH_STACK         = 4,

    DATA_CRAZY_CAT                        = 10,
    DATA_NINE_LIVES                       = 11,
    DATA_SENTRY_DIED                      = 12,
    DATA_FERAL_RUSH                       = 13
};

struct boss_auriayaAI : BossAI
{
    explicit boss_auriayaAI(Creature* creature) : BossAI(creature, TYPE_AURIAYA), _feralDied(false), _nineLives(false) {}

    void Reset() override
    {
        _fightTimer = 0;
        _Reset();
        _feralDied = false;
        _nineLives = false;
        defenderLives = 9;
        defenderGUID = 0;
        swarmingTargetGUID = 0;

        summons.DespawnAll();

        if (instance->GetData(TYPE_AURIAYA) != DONE)
        {
            instance->SetData(TYPE_AURIAYA, NOT_STARTED);
            instance->SetData(DATA_RESPAWN_SENTRIES, DATA_RESPAWN_SENTRIES);
        }

        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
    }

    void SetData(uint32 type, uint32 data) override
    {
        if (type == DATA_SENTRY_DIED)
            _feralDied = true;
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        switch (summon->GetEntry())
        {
            case NPC_FERAL_DEFENDER:
                me->SummonCreature(NPC_SEEPING_FERAL_ESSENCE, *summon);
                // 1st summon - defenderLives(8) 8 stack
                // 2nd summon - defenderLives(7) 7 stack
                // 3rd summon - defenderLives(6) 6 stack
                // 4th summon - defenderLives(5) 5 stack
                // 5th summon - defenderLives(4) 4 stack
                // 6th summon - defenderLives(3) 3 stack
                // 7th summon - defenderLives(2) 2 stack
                // 8th summon - defenderLives(1) no stack aura
                // 9th summon - defenderLives(0) lack of aura and after that
                // if defender dies he is supposed to stay DEAD!
                if (defenderLives)
                {
                    --defenderLives;
                    events.ScheduleEvent(EVENT_DEFENDER_RESPAWN, 30s);
                }
                else
                    _nineLives = true;
                break;
            default:
                break;
        }
    }

    uint32 GetData(uint32 param) const override
    {
        if (param == DATA_CRAZY_CAT)
            return !_feralDied;
        else if (param == DATA_NINE_LIVES)
            return _nineLives;

        return 0;
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);

        if (summon->GetEntry() == NPC_FERAL_DEFENDER)
            defenderGUID = summon->GetGUID();

        if (summon->GetEntry() == NPC_SWARMING_GUARDIAN)
            if (summon->IsAIEnabled)
                summon->AI()->SetGUID(swarmingTargetGUID, 1);
    }

    void EnterEvadeMode() override
    {
        instance->SetData(DATA_DESPAWN_SENTRIES, DATA_DESPAWN_SENTRIES);
        instance->SetData(TYPE_AURIAYA, FAIL);
        _DespawnAtEvade();
    }

    void EnterCombat(Unit* /*who*/) override
    {
        //! if for some reason sentries did not respawn
        //! evade right away
        std::list<Creature*> sentries;
        me->GetCreatureListWithEntryInGrid(sentries, NPC_SANCTUM_SENTRY, 100.f);
        if (sentries.empty())
        {
            EnterEvadeMode();
            return;
        }

        _fightTimer = getMSTime();
        _EnterCombat();
        instance->SetData(TYPE_AURIAYA, IN_PROGRESS);

        events.ScheduleEvent(EVENT_TERRIFYING_SCREECH, 35000);
        events.ScheduleEvent(EVENT_SONIC_SCREECH, 45000);
        events.ScheduleEvent(EVENT_GUARDIAN_SWARM, 70000);
        events.ScheduleEvent(EVENT_SUMMON_FERAL_DEFENDER, 60000);
        events.ScheduleEvent(EVENT_SENTINEL_BLAST, 36000);
        events.ScheduleEvent(EVENT_ENRAGE, 600000);

        me->MonsterYell("Some things are better left alone!", LANG_UNIVERSAL, nullptr);
        me->PlayDirectSound(SOUND_AGGRO);
    }

    void KilledUnit(Unit* victim) override
    {
        if (!victim->IsPlayer())
            return;

        if (urand(0,1))
        {
            me->MonsterYell("The secret dies with you!", LANG_UNIVERSAL, nullptr);
            me->PlayDirectSound(SOUND_SLAY1);
        }
        else
        {
            me->MonsterYell("There is no escape!", LANG_UNIVERSAL, nullptr);
            me->PlayDirectSound(SOUND_SLAY2);
        }
    }

    void JustDied(Unit* killer) override
    {
        instance->SetData(TYPE_AURIAYA, DONE);
        instance->SetData(DATA_DESPAWN_SENTRIES, DATA_DESPAWN_SENTRIES);

        if (Map* map = me->GetMap())
            CheckCreatureRecord(killer, me->GetCreatureTemplate()->Entry, Difficulty(map->GetDifficulty()), "", 15 * IN_MILLISECONDS, _fightTimer);

        summons.DespawnAll();
        _JustDied();
        me->MonsterTextEmote("Auriaya screams in agony.", nullptr);
        me->PlayDirectSound(SOUND_DEATH);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch(eventId)
        {
            case EVENT_SUMMON_FERAL_DEFENDER:
                --defenderLives;
                me->MonsterTextEmote("Auriaya begins to activate Feral Defender.", nullptr, true);
                DoCastSelf(SPELL_ACTIVATE_FERAL_DEFENDER, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
                events.ScheduleEvent(EVENT_REMOVE_IMMUNE, 3000);
                break;
            case EVENT_REMOVE_IMMUNE:
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                break;
            case EVENT_TERRIFYING_SCREECH:
                me->MonsterTextEmote("Auriaya begins to cast Terrifying Screech.", nullptr, true);
                DoCastSelf(SPELL_TERRIFYING_SCREECH);
                events.Repeat(35000);
                break;
            case EVENT_SONIC_SCREECH:
                DoCastSelf(SPELL_SONIC_SCREECH);
                events.Repeat(50000);
                break;
            case EVENT_GUARDIAN_SWARM:
                DoCastVictim(SPELL_GUARDIAN_SWARM);
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                {
                    swarmingTargetGUID = target->GetGUID();
                    DoCast(target, SPELL_GUARDIAN_SWARM);
                }
                events.Repeat(40s);
                break;
            case EVENT_SENTINEL_BLAST:
                DoCastSelf(SPELL_SENTINEL_BLAST);
                events.Repeat(35000);
                events.DelayEvents(5000, 0);
                break;
            case EVENT_ENRAGE:
                me->MonsterTextEmote("You waste my time!", nullptr);
                me->PlayDirectSound(SOUND_BERSERK);
                DoCastSelf(SPELL_ENRAGE, true);
                break;
            case EVENT_DEFENDER_RESPAWN:
            {
                if (Creature* defender = ObjectAccessor::GetCreature(*me, defenderGUID))
                {
                    if (Aura* aura = defender->GetAura(SPELL_FERAL_ESSENCE))
                    {
                        switch (defenderLives)
                        {
                            case 1:
                            {
                                aura->Remove();
                                // no stack modification, just pure cast
                                // otherwise we have a visual that aura applies 0% dmg increase
                                defender->AI()->DoCast(defender, SPELL_FERAL_ESSENCE, true);
                                break;
                            case 0:
                                // This is defenders last live
                                // No aura at this point
                                aura->Remove();
                                break;
                            default:
                                aura->SetStackAmount(defenderLives);
                                break;
                            }
                        }
                    }

                    // Move defender Z position a little above ground
                    defender->SetDisableGravity(true);
                    defender->SetInhabitType(INHABIT_AIR);
                    Position pos = defender->GetPosition();
                    pos.m_positionZ += 3.0f;
                    Movement::MoveSplineInit init(defender);
                    init.MoveTo(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), true, true);
                    init.SetAnimation(Movement::ToFly);
                    init.SetVelocity(0.7f);
                    auto timer = init.Launch();
                    // This will trigger EVENT_REVIVE in defenders script
                    defender->AI()->SetData(1, timer);
                }
                break;
            }
            default:
                break;
        }
    }

private:
    bool _feralDied;
    bool _nineLives;
    int8 defenderLives;
    uint64 defenderGUID;
    uint64 swarmingTargetGUID;
    uint32 _fightTimer;
};

enum Sentry
{
    EVENT_SAVAGE_POUNCE = 1,
    EVENT_RIP_FLESH
};

struct npc_auriaya_sanctum_sentryAI : ScriptedAI
{
    explicit npc_auriaya_sanctum_sentryAI(Creature* creature) : ScriptedAI(creature), _savagePounceTimer(5000), _ripFleshTimer(0) { }

    uint32 _savagePounceTimer;
    uint32 _ripFleshTimer;

    void EnterCombat(Unit* /*attacker*/) override
    {
        DoZoneInCombat(me, 350.0f);
        _events.Reset();
        _events.ScheduleEvent(EVENT_SAVAGE_POUNCE, 0);
        _events.ScheduleEvent(EVENT_RIP_FLESH, 10000);
    }

    void Reset() override
    {
        DoCastSelf(SPELL_STRENGTH_OF_THE_PACK, true);
    }

    void JustDied(Unit* killer) override
    {
        ScriptedAI::JustDied(killer);
        if (InstanceScript* instance = me->GetInstanceScript())
        {
            if (Creature* auriaya = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_AURIAYA)))
                if (auriaya->IsAIEnabled)
                    auriaya->AI()->SetData(DATA_SENTRY_DIED, DATA_SENTRY_DIED);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        while(uint32 eventId = _events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_SAVAGE_POUNCE:
                    if(auto victim = me->GetVictim())
                    {
                        if (me->IsInRange(victim, 8.0f, 25.0f) && me->IsWithinLOSInMap(victim))
                        {
                            DoCastVictim(SPELL_SAVAGE_POUNCE);
                            _events.Repeat(5000);
                            break;
                        }
                    }
                    _events.Repeat(200);
                    break;
                case EVENT_RIP_FLESH:
                    DoCastVictim(SPELL_RIP_FLESH);
                    _events.Repeat(10000);
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

enum feralDefender
{
    // Feral Defender
    EVENT_FERAL_POUNCE = 10,
    EVENT_RUSH,
    EVENT_TARGET,
    EVENT_REVIVE,
    EVENT_APPLY_ALL_AURAS,
    EVENT_SWARM_JUMP,
    EVENT_RESTORE_REACT,
    EVENT_SWARM_RESET
};

struct npc_auriaya_feral_defenderAI : public ScriptedAI
{
    npc_auriaya_feral_defenderAI(Creature* creature) : ScriptedAI(creature)
    {
        instance = me->GetInstanceScript();
    }

    void Reset() override
    {
        me->SetDisableGravity(false);
        canTakeDamage = true;
        canReallyDie = false;
        rushCount = 0;
        deathCount = 0;
        lastRushGUID = 0;
        events.Reset();
        DoZoneInCombat();
        me->SetInhabitType(INHABIT_GROUND);
        events.ScheduleEvent(EVENT_FERAL_POUNCE, 20s);
        events.ScheduleEvent(EVENT_RUSH, 1s);
        events.ScheduleEvent(EVENT_TARGET, 6s, 8s);
        events.ScheduleEvent(EVENT_APPLY_ALL_AURAS, 0.5s);
    }

    void SetData(uint32 type, uint32 value) override
    {
        switch (type)
        {
            case 1:
                events.ScheduleEvent(EVENT_REVIVE, value + 1500);
                break;
            case DATA_FERAL_RUSH:
            {
                if (++rushCount > 13)
                {
                    rushCount = 0;
                    events.CancelEvent(EVENT_RESTORE_REACT);
                    events.ScheduleEvent(EVENT_RESTORE_REACT, 1s);
                    events.ScheduleEvent(EVENT_RUSH, 13s);
                    events.ScheduleEvent(EVENT_FERAL_POUNCE, 4s);
                    events.ScheduleEvent(EVENT_TARGET, 7s);
                }
                else
                    events.ScheduleEvent(EVENT_RUSH, value);
                break;
            }
        }
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (damage >= me->GetHealth() && !canReallyDie)
            damage = me->GetHealth() - 1;

        if (damage >= me->GetHealth() - 1 && canTakeDamage && !canReallyDie)
        {
            if (!instance)
                return;

            me->StopMovingOnCurrentPos();
            events.CancelEvent(EVENT_RESTORE_REACT);
            events.CancelEvent(EVENT_FERAL_POUNCE);
            events.CancelEvent(EVENT_RUSH);
            events.CancelEvent(EVENT_TARGET);

            if (Creature* auriaya = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_AURIAYA)))
                auriaya->AI()->SummonedCreatureDies(me, me);

            RemoveAllAurasExceptSelfCasted();
            canTakeDamage = false;
            me->SetStandState(UNIT_STAND_STATE_DEAD);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->AttackStop();
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->Clear();
        }
    }

    // Remove all owned not casted by self
    // and make it appear as if target died
    // ie. this creature casts buff spell feral essence and shadow paws
    // we need those buffs to stay on feral defender because he is not really dying
    // but all other dots and stuff like that should disappear
    void RemoveAllAurasExceptSelfCasted()
    {
        Unit::AuraMap & auraOwnedMap = me->GetOwnedAuras();
        for (Unit::AuraMap::iterator iter = auraOwnedMap.begin(); iter != auraOwnedMap.end();)
        {
            Aura* aura = iter->second;
            if (aura->GetCasterGUID() != me->GetGUID())
                me->RemoveOwnedAura(iter, AURA_REMOVE_BY_DEATH);
            else
                ++iter;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_FERAL_POUNCE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 45.0f, true))
                        DoCast(target, RAID_MODE(SPELL_FERAL_POUNCE_10, SPELL_FERAL_POUNCE_25));
                    events.ScheduleEvent(EVENT_FERAL_POUNCE, 20s);
                    break;
                case EVENT_RUSH:
                    if (!me->HasReactState(REACT_PASSIVE))
                    {
                        events.ScheduleEvent(EVENT_RESTORE_REACT, 8s);
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        me->GetMotionMaster()->Clear();
                        events.CancelEvent(EVENT_TARGET);
                        events.CancelEvent(EVENT_FERAL_POUNCE);
                    }

                    if (Unit* target = GetFeralRushTarget())
                        DoCast(target, SPELL_FERAL_RUSH);
                    else // failed to find target, repeat in 10s
                    {
                        events.CancelEvent(EVENT_RESTORE_REACT);
                        events.ScheduleEvent(EVENT_RESTORE_REACT, 1s);
                        rushCount = 0;
                        events.Repeat(13s);
                    }
                    break;
                case EVENT_TARGET:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true, -SPELL_SWARM_FOCUS))
                    {
                        DoResetThreat();
                        target->AddThreat(me, 9999999.9f);
                        AttackStart(target);
                        events.ScheduleEvent(eventId, 3000);
                    }
                    events.Repeat(10s);
                    break;
                case EVENT_REVIVE:
                    canTakeDamage = true;
                    DoCast(SPELL_FERAL_FULL_HEAL);
                    me->SetInhabitType(INHABIT_GROUND);
                    me->SetDisableGravity(false);
                    me->SetStandState(UNIT_STAND_STATE_STAND);
                    me->SetReactState(REACT_AGGRESSIVE);
                    DoZoneInCombat();
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    events.ScheduleEvent(EVENT_FERAL_POUNCE, 20s);
                    events.ScheduleEvent(EVENT_RUSH, 1s);
                    events.ScheduleEvent(EVENT_TARGET, 6s, 8s);
                    ++deathCount;
                    // Defender lost eight lives at this point
                    // Next death is permanent
                    if (deathCount == 8)
                        canReallyDie = true;
                    break;
                case EVENT_APPLY_ALL_AURAS:
                    DoCast(SPELL_CRITICAL_HIT_REDUCE);
                    DoCast(SPELL_SHADOW_PAWS);
                    DoCast(SPELL_FERAL_ESSENCE);
                    // This is max possible stack amount of this aura
                    // This event is called only once - on reset
                    me->SetAuraStack(SPELL_FERAL_ESSENCE, me, 8);
                    break;
                case EVENT_RESTORE_REACT:
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->UpdateSpeed(MOVE_RUN);
                    if (me->GetVictim())
                        AttackStart(me->GetVictim());
                    break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

    Unit* GetFeralRushTarget()
    {
        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, [&](Unit* object)
        {
            // lambda, do not select last rush target as proper target and target has to be player
            return object->IsPlayer() && object->GetGUID() != lastRushGUID;
        }))
        {
            lastRushGUID = target->GetGUID();
            return target;
        }

        return nullptr;
    }
private:
    InstanceScript * instance;
    EventMap events;
    bool canTakeDamage, canReallyDie;
    uint32 deathCount;
    uint8 rushCount;
    uint64 lastRushGUID;
};

struct npc_swarming_guardian_auriaya_AI : public ScriptedAI
{
    npc_swarming_guardian_auriaya_AI(Creature* creature) : ScriptedAI(creature)
    {
        instance = me->GetInstanceScript();
        attackTargetGUID = 0;
        me->SetNoCallAssistance(true);
        me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
    }

    void IsSummonedBy(Unit* summoner) override
    {
        if (summoner->GetTypeId() != TYPEID_PLAYER)
            return;

        if (instance)
        {
            // Override summoner and make auriaya summoner
            if (Creature* auriaya = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_AURIAYA)))
            {
                if (auriaya->IsAIEnabled)
                    auriaya->AI()->JustSummoned(me);

                if (!auriaya->IsInCombat())
                    me->DespawnOrUnsummon();
            }
        }
    }

    void SetGUID(uint64 guid, int32 type) override
    {
        if (type == 1)
            attackTargetGUID = guid;
    }

    void Reset() override
    {
        events.Reset();
        events.ScheduleEvent(EVENT_SWARM_JUMP, 0.5s);
        events.ScheduleEvent(EVENT_SWARM_RESET, 5s);
    }

    void UpdateAI(uint32 diff) override
    {
        events.Update(diff);

        while (auto eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SWARM_JUMP:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, attackTargetGUID))
                    {
                        DoCast(player, SPELL_SWARM_POUNCE, true);
                        AttackStart(player);
                        player->AddThreat(me, 100000.0f);
                    }
                    break;
                }
                case EVENT_SWARM_RESET:
                {
                    if (instance)
                    {
                        if (Creature* auriaya = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_AURIAYA)))
                        {
                            if (instance->GetData(TYPE_AURIAYA) == DONE)
                                me->DespawnOrUnsummon();
                        }
                    }
                    events.Repeat(5s);
                    break;
                }
            }
        }
        DoMeleeAttackIfReady();
    }
private:
    InstanceScript * instance;
    uint64 attackTargetGUID;
    EventMap events;
};

class spell_auriaya_sentinel_blast_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_auriaya_sentinel_blast_SpellScript);

    bool Validate(const SpellInfo* spellInfo) override
    {
        return ValidateSpellInfo({ SPELL_SENTINEL_BLAST_10, SPELL_SENTINEL_BLAST_25 });
    }

    void FilterTargets(std::list<WorldObject*>& unitList)
    {
        unitList.remove_if(PlayerOrPetCheck());
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_auriaya_sentinel_blast_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

class achievement_auriaya_crazy_cat_lady : public AchievementCriteriaScript
{
    public:
        achievement_auriaya_crazy_cat_lady() : AchievementCriteriaScript("achievement_auriaya_crazy_cat_lady") {}

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            if (target)
                if (auto instance = target->GetInstanceScript())
                    if (auto cr = ObjectAccessor::GetCreature(*target, instance->GetData64(TYPE_AURIAYA)))
                        if (cr->IsAIEnabled)
                            return cr->AI()->GetData(DATA_CRAZY_CAT);

            return false;
        }
};

class achievement_auriaya_nine_lives : public AchievementCriteriaScript
{
    public:
        achievement_auriaya_nine_lives() : AchievementCriteriaScript("achievement_auriaya_nine_lives") {}

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            if (target)
                if (auto instance = target->GetInstanceScript())
                    if (auto cr = ObjectAccessor::GetCreature(*target, instance->GetData64(TYPE_AURIAYA)))
                        if (cr->IsAIEnabled)
                            return cr->AI()->GetData(DATA_NINE_LIVES);

            return false;
        }
};

class spell_feral_rush_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_feral_rush_SpellScript);

    void HandleEffectJump(SpellEffIndex effIndex)
    {
        if (!GetHitUnit())
            return;

        PreventHitDefaultEffect(effIndex);

        float x, y, z;

        GetHitUnit()->GetContactPoint(GetCaster(), x, y, z, CONTACT_DISTANCE);
        auto distance = GetCaster()->GetDistance2d(x, y);
        Movement::MoveSplineInit init(GetCaster());
        init.MoveTo(x, y, z);

        if (distance > 5.0f)
            init.SetParabolic(2.5f, 0);

        init.SetVelocity(25.f);
        init.SetFacing(GetCaster()->GetAngle(x, y));
        auto destinationTimer = init.Launch();

        if (Creature* feral = GetCaster()->ToCreature())
        {
            if (feral->IsAIEnabled)
                feral->AI()->SetData(DATA_FERAL_RUSH, destinationTimer + 150);
        }
    }

    void Register()
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_feral_rush_SpellScript::HandleEffectJump, EFFECT_0, SPELL_EFFECT_JUMP);
    }
};

void AddSC_boss_auriaya()
{
    new CreatureAILoader<boss_auriayaAI>("boss_auriaya");
    new CreatureAILoader<npc_auriaya_sanctum_sentryAI>("npc_auriaya_sanctum_sentry");
    new CreatureAILoader<npc_auriaya_feral_defenderAI>("npc_auriaya_feral_defender");
    new CreatureAILoader<npc_swarming_guardian_auriaya_AI>("npc_swarming_guardian_auriaya");

    new SpellScriptLoaderEx<spell_auriaya_sentinel_blast_SpellScript>("spell_auriaya_sentinel_blast");
    new SpellScriptLoaderEx<spell_feral_rush_SpellScript>("spell_feral_rush");

    new achievement_auriaya_crazy_cat_lady();
    new achievement_auriaya_nine_lives();
}
