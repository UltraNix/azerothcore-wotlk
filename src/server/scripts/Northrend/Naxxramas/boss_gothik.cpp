/* based on work of Treeston and TrinityCore */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "GridNotifiers.h"
#include "CombatAI.h"
#include "naxxramas.h"

/* Constants */
enum Yells
{
    SAY_INTRO_1                 = 0,
    SAY_INTRO_2                 = 1,
    SAY_INTRO_3                 = 2,
    SAY_INTRO_4                 = 3,
    SAY_PHASE_TWO               = 4,
    SAY_DEATH                   = 5,
    SAY_KILL                    = 6,

    EMOTE_PHASE_TWO             = 7,
    EMOTE_GATE_OPENED           = 8
};

enum Spells
{
    /* living knight spells */
    SPELL_SHADOW_MARK           = 27825,

    /* spectral knight spells */
    SPELL_WHIRLWIND             = 56408,

    /* spectral rider spells */
    SPELL_UNHOLY_FRENZY         = 55648,

    /* spectral horse spells */
    SPELL_STOMP                 = 27993,

    /* gothik phase two spells */
    SPELL_HARVEST_SOUL          = 28679,
    SPELL_SHADOW_BOLT           = 29317,

    /* visual spells */
    SPELL_ANCHOR_1_TRAINEE      = 27892,
    SPELL_ANCHOR_1_DK           = 27928,
    SPELL_ANCHOR_1_RIDER        = 27935,

    SPELL_ANCHOR_2_TRAINEE      = 27893,
    SPELL_ANCHOR_2_DK           = 27929,
    SPELL_ANCHOR_2_RIDER        = 27936,

    SPELL_SKULLS_TRAINEE        = 27915,
    SPELL_SKULLS_DK             = 27931,
    SPELL_SKULLS_RIDER          = 27937,

    /* teleport spells */
    SPELL_TELEPORT_DEAD         = 28025,
    SPELL_TELEPORT_LIVE         = 28026
};
#define SPELLHELPER_DEATH_PLAGUE RAID_MODE<uint32>(55604, 55645)
#define SPELLHELPER_SHADOW_BOLT_VOLLEY RAID_MODE<uint32>(27831, 55638)
#define SPELLHELPER_ARCANE_EXPLOSION RAID_MODE<uint32>(27989, 56407)
#define SPELLHELPER_DRAIN_LIFE RAID_MODE<uint32>(27994, 55646)
#define SPELLHELPER_UNHOLY_FRENZY RAID_MODE<uint32>(SPELL_UNHOLY_FRENZY,27995)

enum Creatures
{
    NPC_LIVE_TRAINEE    = 16124,
    NPC_LIVE_KNIGHT     = 16125,
    NPC_LIVE_RIDER      = 16126,
    NPC_DEAD_TRAINEE    = 16127,
    NPC_DEAD_KNIGHT     = 16148,
    NPC_DEAD_RIDER      = 16150,
    NPC_DEAD_HORSE      = 16149,

    NPC_TRIGGER         = 16137
};

enum Phases
{
    PHASE_ONE = 1,
    PHASE_TWO = 2
};

enum Events
{
    EVENT_INTRO_2 = 1,
    EVENT_INTRO_3,
    EVENT_INTRO_4,
    EVENT_PHASE_TWO,
    EVENT_SUMMON,
    EVENT_DOORS_UNLOCK,
    EVENT_TELEPORT,
    EVENT_HARVEST,
    EVENT_BOLT,
    EVENT_RESUME_ATTACK
};

enum Actions
{
    ACTION_GATE_OPENED = 1,
    ACTION_MINION_EVADE,
    ACTION_ACQUIRE_TARGET
};

Position const GothikMiddleOfTheRoom = { 2692.814453f, -3358.323242f, 267.683777f, 3.241947f };

/* Room side checking logic */
#define POS_Y_GATE    -3360.78f
#define POS_Y_WEST    -3285.0f
#define POS_Y_EAST    -3434.0f
#define POS_X_NORTH    2750.49f
#define POS_X_SOUTH    2633.84f

#define IN_LIVE_SIDE(who) (who->GetPositionY() < POS_Y_GATE)

enum Side
{
    SIDE_NONE = 0,
    SIDE_LIVING,
    SIDE_DEAD
};

inline static Side GetSide(Position const* who)
{
    if (IN_LIVE_SIDE(who))
        return SIDE_LIVING;
    else
        return SIDE_DEAD;

    return SIDE_NONE;
}

inline static bool IsOnSameSide(Position const* who, Position const* other)
{
    return (GetSide(who) == GetSide(other));
}

static Player* FindEligibleTarget(Creature const* me, bool isGateOpen)
{
    Map::PlayerList const& players = me->GetMap()->GetPlayers();
    for (Map::PlayerList::const_iterator it = players.begin(); it != players.end(); ++it)
    {
        Player* player = it->GetSource();
        if (player && (isGateOpen || IsOnSameSide(me, player)) && me->CanSeeOrDetect(player) && me->IsValidAttackTarget(player) && player->isInAccessiblePlaceFor(me) &&
            player->GetDistance(GothikMiddleOfTheRoom) < 85.0f)
            return player;
    }

    return nullptr;
}


/* Wave data */
typedef std::pair<uint32, uint8> GothikWaveEntry; // (npcEntry, npcCount)
typedef std::set<GothikWaveEntry> GothikWave;
typedef std::pair<GothikWave, uint8> GothikWaveInfo; // (wave, secondsToNext)
typedef std::vector<GothikWaveInfo> GothikWaveData;
const GothikWaveData waves10 =
{
    {
        {{NPC_LIVE_TRAINEE, 2}},
    20},
    {
        {{NPC_LIVE_TRAINEE, 2}},
    20},
    {
        {{NPC_LIVE_TRAINEE, 2}},
    10},
    {
        {{NPC_LIVE_KNIGHT, 1}},
    10},
    {
        {{NPC_LIVE_TRAINEE, 2}},
    15},
    {
        {{NPC_LIVE_KNIGHT, 1}},
    5},
    {
        {{NPC_LIVE_TRAINEE, 2}},
    20},
    {
        {{NPC_LIVE_TRAINEE, 2}, {NPC_LIVE_KNIGHT, 1}},
    10},
    {
        {{NPC_LIVE_RIDER, 1}},
    10},
    {
        {{NPC_LIVE_TRAINEE, 2}},
    5},
    {
        {{NPC_LIVE_KNIGHT, 1}},
    15},
    {
        {{NPC_LIVE_TRAINEE, 2}, {NPC_LIVE_RIDER, 1}},
    10},
    {
        {{NPC_LIVE_KNIGHT, 2}},
    10},
    {
        {{NPC_LIVE_TRAINEE, 2}},
    10},
    {
        {{NPC_LIVE_RIDER, 1}},
    5},
    {
        {{NPC_LIVE_KNIGHT, 1}},
    5},
    {
        {{NPC_LIVE_TRAINEE, 2}},
    20},
    {
        {{NPC_LIVE_RIDER, 1}, {NPC_LIVE_KNIGHT, 1}, {NPC_LIVE_TRAINEE, 2}},
    15},
    {
        {{NPC_LIVE_TRAINEE, 2}},
    0}
};

const GothikWaveData waves25 =
{
    {
        {{NPC_LIVE_TRAINEE, 3}},
    20},
    {
        {{NPC_LIVE_TRAINEE, 3}},
    20},
    {
        {{NPC_LIVE_TRAINEE, 3}},
    10},
    {
        {{NPC_LIVE_KNIGHT, 2}},
    10},
    {
        {{NPC_LIVE_TRAINEE, 3}},
    15},
    {
        {{NPC_LIVE_KNIGHT, 2}},
    5},
    {
        {{NPC_LIVE_TRAINEE, 3}},
    20},
    {
        {{NPC_LIVE_TRAINEE, 3}, {NPC_LIVE_KNIGHT, 2}},
    10},
    {
        {{NPC_LIVE_TRAINEE, 3}},
    10},
    {
        {{NPC_LIVE_RIDER, 1}},
    5},
    {
        {{NPC_LIVE_TRAINEE, 3}},
    15},
    {
        {{NPC_LIVE_RIDER, 1}},
    10},
    {
        {{NPC_LIVE_KNIGHT, 2}},
    10},
    {
        {{NPC_LIVE_RIDER, 1}},
    10},
    {
        {{NPC_LIVE_RIDER, 1}, {NPC_LIVE_TRAINEE, 3}},
    5},
    {
        {{NPC_LIVE_KNIGHT, 1}, {NPC_LIVE_TRAINEE, 3}},
    5},
    {
        {{NPC_LIVE_RIDER, 1}, {NPC_LIVE_TRAINEE, 3}},
    20},
    {
        {{NPC_LIVE_RIDER, 1}, {NPC_LIVE_KNIGHT, 2}, {NPC_LIVE_TRAINEE, 3}},
    0}
};


//! GUID of first trigger NPC (used as offset for guid checks)
//! If you're going to port this script somewhere (INCLUDING SQL) first cGUID in sql is the same as here or change this value to whatever you set it to
// 0-1 are living side soul triggers, 2-3 are spectral side soul triggers, 4 is living rider spawn trigger, 5-7 are living other spawn trigger, 8-12 are skull pile triggers
const uint32 CGUID_TRIGGER = 300000;
/* Creature AI */
class boss_gothik : public CreatureScript
{
    public:
        boss_gothik() : CreatureScript("boss_gothik") { }

        struct boss_gothikAI : public BossAI
        {
            boss_gothikAI(Creature* creature) : BossAI(creature, DATA_GOTHIK)
            {
                Initialize();
            }

            void HandleGothikGate(GOState value)
            {
                if (GameObject* gate = ObjectAccessor::GetGameObject(*me, instance->GetData64(DATA_GOTHIK_INNER_GATE)))
                    gate->SetGoState(value);
            }

            void Initialize()
            {
                _waveCount = 0;
                _gateCanOpen = false;
                _gateIsOpen = true;
                _lastTeleportDead = false;
            }

            void Reset() override
            {
                if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetData64(DATA_GOTHIK_ENTER_GATE)))
                    go->SetGoState(GO_STATE_ACTIVE);
                me->SetReactState(REACT_PASSIVE);
                HandleGothikGate(GO_STATE_ACTIVE);
                instance->SetData(EVENT_GOTHIK, NOT_STARTED);
                _Reset();
                Initialize();
                _fightTimer = 0;
            }

            void EnterCombat(Unit* /*who*/) override
            {
                instance->SetData(EVENT_GOTHIK, IN_PROGRESS);
                _fightTimer = getMSTime();
                _EnterCombat();
                events.SetPhase(PHASE_ONE);
                events.ScheduleEvent(EVENT_SUMMON, 25s, 0, PHASE_ONE);
                events.ScheduleEvent(EVENT_DOORS_UNLOCK, 2.5min, 0, PHASE_ONE);
                events.ScheduleEvent(EVENT_PHASE_TWO, 4.5min, 0, PHASE_ONE);
                Talk(SAY_INTRO_1);
                events.ScheduleEvent(EVENT_INTRO_2, 4s);
                events.ScheduleEvent(EVENT_INTRO_3, 9s);
                events.ScheduleEvent(EVENT_INTRO_4, 4s);
                HandleGothikGate(GO_STATE_READY);
                if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetData64(DATA_GOTHIK_ENTER_GATE)))
                    go->SetGoState(GO_STATE_READY);
                _gateIsOpen = false;
            }

            void JustSummoned(Creature* summon) override
            {
                summons.Summon(summon);
                if (me->IsInCombat())
                {
                    summon->AI()->DoAction(_gateIsOpen ? ACTION_GATE_OPENED : ACTION_ACQUIRE_TARGET);
                }
                else
                    summon->DespawnOrUnsummon();
            }

            void SummonedCreatureDespawn(Creature* summon) override
            {
                summons.Despawn(summon);
            }

            void KilledUnit(Unit* victim) override
            {
                if (!victim->IsPlayer())
                    return;

                if (!urand(0, 3))
                    Talk(SAY_KILL);

                instance->SetData(DATA_IMMORTAL_FAIL, 0);
            }

            void JustDied(Unit* killer) override
            {
                _JustDied();
                instance->SetData(EVENT_GOTHIK, DONE);
                if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetData64(DATA_GOTHIK_ENTER_GATE)))
                    go->SetGoState(GO_STATE_ACTIVE);

                if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetData64(DATA_GOTHIK_EXIT_GATE)))
                    go->SetGoState(GO_STATE_ACTIVE);

                if (Map* map = me->GetMap())
                    CheckCreatureRecord(killer, me->GetCreatureTemplate()->Entry, map->GetDifficulty(), "", 15000, _fightTimer);

                Talk(SAY_DEATH);
                HandleGothikGate(GO_STATE_ACTIVE);
                _gateIsOpen = false;
            }

            void OpenGate()
            {
                if (_gateIsOpen)
                    return;

                HandleGothikGate(GO_STATE_ACTIVE);
                Talk(EMOTE_GATE_OPENED);
                _gateIsOpen = true;

                for (uint64 summonGuid : summons)
                {
                    if (Creature* summon = ObjectAccessor::GetCreature(*me, summonGuid))
                        summon->AI()->DoAction(ACTION_GATE_OPENED);
                    if (summons.empty()) // ACTION_GATE_OPENED may cause an evade, despawning summons and invalidating our iterator
                        break;
                }
            }

            void DamageTaken(Unit* /*who*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
            {
                if (!events.IsInPhase(PHASE_TWO))
                    damage = 0;
            }

            void DoAction(int32 action) override
            {
                switch (action)
                {
                    case ACTION_MINION_EVADE:
                        if (_gateIsOpen || me->getThreatManager().isThreatListEmpty())
                            return EnterEvadeMode();
                        if (_gateCanOpen)
                            OpenGate();
                        break;
                }
            }

            void EnterEvadeMode() override
            {
                BossAI::EnterEvadeMode();
                Position const& home = me->GetHomePosition();
                me->NearTeleportTo(home.GetPositionX(), home.GetPositionY(), home.GetPositionZ(), home.GetOrientation());
                summons.DespawnAll();
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                if (me->HasReactState(REACT_AGGRESSIVE) && !_gateIsOpen && !IsOnSameSide(me, me->GetVictim()))
                {
                    // NBD: this should only happen in practice if there is nobody left alive on our side (we should open gate)
                    // thus we only do a cursory check to make sure (edge cases?)
                    if (Player* newTarget = FindEligibleTarget(me, _gateIsOpen))
                    {
                        me->getThreatManager().resetAllAggro();
                        me->AddThreat(newTarget, 1.0f);
                        AttackStart(newTarget);
                    }
                    else
                        OpenGate();
                }

                events.Update(diff);

                if (!_gateIsOpen && HealthBelowPct(30) && events.IsInPhase(PHASE_TWO))
                    OpenGate();

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SUMMON:
                        {
                            if (RAID_MODE(waves10,waves25).size() <= _waveCount) // bounds check
                            {
                                sLog->outError("scripts", "GothikAI: Wave count %d is out of range for difficulty %d.", _waveCount, GetDifficulty());
                                break;
                            }

                            std::list<Creature*> triggers;
                            me->GetCreatureListWithEntryInGrid(triggers, NPC_TRIGGER, 150.0f);
                            for (GothikWaveEntry entry : RAID_MODE(waves10, waves25)[_waveCount].first)
                                for (uint8 i = 0; i < entry.second; ++i)
                                {
                                    // GUID layout is as follows:
                                    // CGUID+4: center (back of platform) - primary rider spawn
                                    // CGUID+5: north (back of platform) - primary knight spawn
                                    // CGUID+6: center (front of platform) - second spawn
                                    // CGUID+7: south (front of platform) - primary trainee spawn
                                    uint32 targetDBGuid;
                                    switch (entry.first)
                                    {
                                        case NPC_LIVE_RIDER: // only spawns from center (back) > north
                                            targetDBGuid = (CGUID_TRIGGER + 4) + (i % 2);
                                            break;
                                        case NPC_LIVE_KNIGHT: // spawns north > center (front) > south
                                            targetDBGuid = (CGUID_TRIGGER + 5) + (i % 3);
                                            break;
                                        case NPC_LIVE_TRAINEE: // spawns south > center (front) > north
                                            targetDBGuid = (CGUID_TRIGGER + 7) - (i % 3);
                                            break;
                                        default:
                                            targetDBGuid = 0;
                                    }

                                    for (Creature* trigger : triggers)
                                        if (trigger && trigger->GetDBTableGUIDLow() == targetDBGuid)
                                        {
                                            DoSummon(entry.first, trigger, 1.0f, 15 * IN_MILLISECONDS, TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                                            break;
                                        }
                                }

                            if (uint8 timeToNext = RAID_MODE(waves10, waves25)[_waveCount].second)
                                events.Repeat(Seconds(timeToNext));

                            ++_waveCount;
                            break;
                        }
                        case EVENT_DOORS_UNLOCK:
                            _gateCanOpen = true;
                            for (uint64 summonGuid : summons)
                            {
                                if (Creature* summon = ObjectAccessor::GetCreature(*me, summonGuid))
                                {
                                    if (summon->IsAlive() && (!summon->IsInCombat() || summon->IsInEvadeMode()))
                                    {
                                        OpenGate();
                                        break;
                                    }
                                }
                            }
                            break;
                        case EVENT_PHASE_TWO:
                            events.SetPhase(PHASE_TWO);
                            events.ScheduleEvent(EVENT_TELEPORT, 20s, 0, PHASE_TWO);
                            events.ScheduleEvent(EVENT_HARVEST, 15s, 0, PHASE_TWO);
                            events.ScheduleEvent(EVENT_RESUME_ATTACK, 2s, 0, PHASE_TWO);
                            Talk(SAY_PHASE_TWO);
                            Talk(EMOTE_PHASE_TWO);
                            me->SetReactState(REACT_PASSIVE);
                            me->getThreatManager().resetAllAggro();
                            DoCastAOE(SPELL_TELEPORT_LIVE);
                            break;
                        case EVENT_TELEPORT:
                            if (!HealthBelowPct(30))
                            {
                                me->CastStop();
                                me->AttackStop();
                                me->StopMoving();
                                me->SetReactState(REACT_PASSIVE);
                                me->getThreatManager().resetAllAggro();
                                DoCastAOE(_lastTeleportDead ? SPELL_TELEPORT_LIVE : SPELL_TELEPORT_DEAD);
                                _lastTeleportDead = !_lastTeleportDead;

                                events.CancelEvent(EVENT_BOLT);
                                events.ScheduleEvent(EVENT_RESUME_ATTACK, 2 * IN_MILLISECONDS, 0, PHASE_TWO);
                                events.Repeat(20s);
                            }
                            break;

                        case EVENT_HARVEST:
                            DoCastAOE(SPELL_HARVEST_SOUL, true); // triggered allows this to go "through" shadow bolt
                            events.Repeat(15s);
                            break;
                        case EVENT_RESUME_ATTACK:
                            me->SetReactState(REACT_AGGRESSIVE);
                            events.ScheduleEvent(EVENT_BOLT, 0, 0, PHASE_TWO);
                            // return to the start of this method so victim side etc is re-evaluated
                            return UpdateAI(0u); // tail recursion for efficiency
                        case EVENT_BOLT:
                            DoCastVictim(SPELL_SHADOW_BOLT);
                            events.Repeat(2s);
                            break;
                        case EVENT_INTRO_2:
                            Talk(SAY_INTRO_2);
                            break;
                        case EVENT_INTRO_3:
                            Talk(SAY_INTRO_3);
                            break;
                        case EVENT_INTRO_4:
                            Talk(SAY_INTRO_4);
                            break;
                    }
                }
            }

            private:
                uint32 _waveCount;
                bool _gateCanOpen;
                bool _gateIsOpen;
                bool _lastTeleportDead;
                uint32 _fightTimer;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetInstanceAI<boss_gothikAI>(creature);
        }
};

struct npc_gothik_minion_baseAI : public ScriptedAI
{
    public:
        npc_gothik_minion_baseAI(Creature* creature, uint32 deathNotify=0) : ScriptedAI(creature), _deathNotify(deathNotify), _gateIsOpen(false) { }

        void JustDied(Unit* /*killer*/) override
        {
            if (_deathNotify)
                DoCastAOE(_deathNotify, true);
        }

        inline bool isOnSameSide(Unit const* who) const
        {
            return IsOnSameSide(me, who);
        }

        void DamageTaken(Unit* attacker, uint32 &damage, DamageEffectType, SpellSchoolMask) override
        { // do not allow minions to take damage before the gate is opened
            if (!_gateIsOpen && !isOnSameSide(attacker))
                damage = 0;
        }

        void DoAction(int32 action) override
        {
            switch (action)
            {
                case ACTION_GATE_OPENED:
                    _gateIsOpen = true;
                    // intentional missing break
                case ACTION_ACQUIRE_TARGET:
                    if (Player* target = FindEligibleTarget(me, _gateIsOpen))
                    {
                        me->AddThreat(target, 1.0f);
                        AttackStart(target);
                    }
                    else
                        EnterEvadeMode();
                    break;
            }
        }

        void KilledUnit(Unit* who) override
        {
            if (who->GetTypeId() == TYPEID_PLAYER && me->GetInstanceScript())
                me->GetInstanceScript()->SetData(DATA_IMMORTAL_FAIL, 0);
        }

        void EnterEvadeMode() override
        {
            ScriptedAI::EnterEvadeMode();

            if (InstanceScript* instance = me->GetInstanceScript())
                if (Creature* gothik = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_GOTHIK)))
                    gothik->AI()->DoAction(ACTION_MINION_EVADE);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (!_gateIsOpen && !isOnSameSide(me->GetVictim()))
            { // reset threat, then try to find someone on same side as us to attack
                if (Player* newTarget = FindEligibleTarget(me, _gateIsOpen))
                {
                    me->RemoveAurasByType(SPELL_AURA_MOD_TAUNT);
                    me->getThreatManager().resetAllAggro();
                    me->AddThreat(newTarget, 1.0f);
                    AttackStart(newTarget);
                }
                else
                    EnterEvadeMode();
            }

            _UpdateAI(diff);
        }

        virtual void _UpdateAI(uint32 diff) { ScriptedAI::UpdateAI(diff); };

    private:
        uint32 _deathNotify;
        bool _gateIsOpen;
};

class npc_gothik_minion_livingtrainee : public CreatureScript
{
    public:
        npc_gothik_minion_livingtrainee() : CreatureScript("npc_gothik_minion_livingtrainee") { }

        struct npc_gothik_minion_livingtraineeAI : public npc_gothik_minion_baseAI
        {
            npc_gothik_minion_livingtraineeAI(Creature* creature) : npc_gothik_minion_baseAI(creature, SPELL_ANCHOR_1_TRAINEE), _deathPlagueTimer(urand(5000, 20000)) { }

            void _UpdateAI(uint32 diff)
            {
                if (diff < _deathPlagueTimer)
                    _deathPlagueTimer -= diff;
                else
                {
                    DoCastAOE(SPELLHELPER_DEATH_PLAGUE);
                    _deathPlagueTimer = urand(5000, 20000);
                }
                DoMeleeAttackIfReady();
            }
            uint32 _deathPlagueTimer;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetInstanceAI<npc_gothik_minion_livingtraineeAI>(creature);
        }
};

class npc_gothik_minion_livingknight : public CreatureScript
{
    public:
        npc_gothik_minion_livingknight() : CreatureScript("npc_gothik_minion_livingknight") { }

        struct npc_gothik_minion_livingknightAI : public npc_gothik_minion_baseAI
        {
            npc_gothik_minion_livingknightAI(Creature* creature) : npc_gothik_minion_baseAI(creature, SPELL_ANCHOR_1_DK), _whirlwindTimer(urand(5000, 20000)) { }

            void _UpdateAI(uint32 diff)
            {
                if (diff < _whirlwindTimer)
                    _whirlwindTimer -= diff;
                else
                {
                    DoCastAOE(SPELL_SHADOW_MARK);
                    _whirlwindTimer = urand(5000, 20000);
                }
                DoMeleeAttackIfReady();
            }
            uint32 _whirlwindTimer;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetInstanceAI<npc_gothik_minion_livingknightAI>(creature);
        }
};

class npc_gothik_minion_livingrider : public CreatureScript
{
    public:
        npc_gothik_minion_livingrider() : CreatureScript("npc_gothik_minion_livingrider") { }

        struct npc_gothik_minion_livingriderAI : public npc_gothik_minion_baseAI
        {
            npc_gothik_minion_livingriderAI(Creature* creature) : npc_gothik_minion_baseAI(creature, SPELL_ANCHOR_1_RIDER), _boltVolleyTimer(urand(5000, 10000)) { }

            void _UpdateAI(uint32 diff)
            {
                if (diff < _boltVolleyTimer)
                    _boltVolleyTimer -= diff;
                else
                {
                    DoCastAOE(SPELLHELPER_SHADOW_BOLT_VOLLEY);
                    _boltVolleyTimer = urand(5000, 10000);
                }
                if (!me->HasUnitState(UNIT_STATE_CASTING))
                    DoMeleeAttackIfReady();
            }
            uint32 _boltVolleyTimer;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetInstanceAI<npc_gothik_minion_livingriderAI>(creature);
        }
};

class npc_gothik_minion_spectraltrainee : public CreatureScript
{
    public:
    npc_gothik_minion_spectraltrainee() : CreatureScript("npc_gothik_minion_spectraltrainee") { }

    struct npc_gothik_minion_spectraltraineeAI : public npc_gothik_minion_baseAI
    {
        npc_gothik_minion_spectraltraineeAI(Creature* creature) : npc_gothik_minion_baseAI(creature), _explosionTimer(2 * IN_MILLISECONDS) { }

        void _UpdateAI(uint32 diff)
        {
            if (diff < _explosionTimer)
                _explosionTimer -= diff;
            else
            {
                DoCastAOE(SPELLHELPER_ARCANE_EXPLOSION);
                _explosionTimer = 2 * IN_MILLISECONDS;
            }
            DoMeleeAttackIfReady();
        }
        uint32 _explosionTimer;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_gothik_minion_spectraltraineeAI>(creature);
    }
};

class npc_gothik_minion_spectralknight : public CreatureScript
{
    public:
    npc_gothik_minion_spectralknight() : CreatureScript("npc_gothik_minion_spectralknight") { }

    struct npc_gothik_minion_spectralknightAI : public npc_gothik_minion_baseAI
    {
        npc_gothik_minion_spectralknightAI(Creature* creature) : npc_gothik_minion_baseAI(creature), _whirlwindTimer(urand(15000, 25000)) { }

        void _UpdateAI(uint32 diff)
        {
            if (diff < _whirlwindTimer)
                _whirlwindTimer -= diff;
            else
            {
                DoCastAOE(SPELL_WHIRLWIND);
                _whirlwindTimer = urand(15000, 25000);
            }
            DoMeleeAttackIfReady();
        }
        uint32 _whirlwindTimer;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_gothik_minion_spectralknightAI>(creature);
    }
};

class npc_gothik_minion_spectralrider : public CreatureScript
{
    public:
    npc_gothik_minion_spectralrider() : CreatureScript("npc_gothik_minion_spectralrider") { }

    struct npc_gothik_minion_spectralriderAI : public npc_gothik_minion_baseAI
    {
        npc_gothik_minion_spectralriderAI(Creature* creature) : npc_gothik_minion_baseAI(creature), _frenzyTimer(urand(2000, 5000)), _drainTimer(urand(8000,12000)) { }

        void _UpdateAI(uint32 diff)
        {
            if (diff < _frenzyTimer)
                _frenzyTimer -= diff;
            else if (me->HasUnitState(UNIT_STATE_CASTING))
                _frenzyTimer = 0;
            else
            { // target priority: knight > other rider > horse > gothik
                std::list<Creature*> potentialTargets = DoFindFriendlyMissingBuff(30.0, SPELLHELPER_UNHOLY_FRENZY);
                Creature *knightTarget = nullptr, *riderTarget = nullptr, *horseTarget = nullptr, *gothikTarget = nullptr;
                for (Creature* pTarget : potentialTargets)
                {
                    switch (pTarget->GetEntry())
                    {
                        case NPC_DEAD_KNIGHT:
                            knightTarget = pTarget;
                            break;
                        case NPC_DEAD_RIDER:
                            riderTarget = pTarget;
                            break;
                        case NPC_DEAD_HORSE:
                            horseTarget = pTarget;
                            break;
                        case NPC_GOTHIK:
                            gothikTarget = pTarget;
                            break;
                    }
                    if (knightTarget)
                        break;
                }
                Creature* target = knightTarget ? knightTarget : riderTarget ? riderTarget : horseTarget ? horseTarget : gothikTarget ? gothikTarget : nullptr;
                if (target)
                    DoCast(target, SPELL_UNHOLY_FRENZY);
                _frenzyTimer = 20 * IN_MILLISECONDS;
            }

            if (diff < _drainTimer)
                _drainTimer -= diff;
            else
            {
                DoCastVictim(SPELLHELPER_DRAIN_LIFE);
                _drainTimer = urand(10000, 15000);
            }

            if (!me->HasUnitState(UNIT_STATE_CASTING))
                DoMeleeAttackIfReady();
        }
        uint32 _frenzyTimer, _drainTimer;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_gothik_minion_spectralriderAI>(creature);
    }
};

class npc_gothik_minion_spectralhorse : public CreatureScript
{
    public:
    npc_gothik_minion_spectralhorse() : CreatureScript("npc_gothik_minion_spectralhorse") { }

    struct npc_gothik_minion_spectralhorseAI : public npc_gothik_minion_baseAI
    {
        npc_gothik_minion_spectralhorseAI(Creature* creature) : npc_gothik_minion_baseAI(creature), _stompTimer(urand(10000, 15000)) { }

        void _UpdateAI(uint32 diff)
        {
            if (diff < _stompTimer)
                _stompTimer -= diff;
            else
            {
                DoCastAOE(SPELL_STOMP);
                _stompTimer = urand(14000, 18000);
            }
            DoMeleeAttackIfReady();
        }
        uint32 _stompTimer;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_gothik_minion_spectralhorseAI>(creature);
    }
};

class npc_gothik_trigger : public CreatureScript
{
public:
    npc_gothik_trigger() : CreatureScript("npc_gothik_trigger") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_gothik_triggerAI>(creature);
    }

    struct npc_gothik_triggerAI : public ScriptedAI
    {
        npc_gothik_triggerAI(Creature* creature) : ScriptedAI(creature) { creature->SetDisableGravity(true); }

        void EnterEvadeMode() override { }
        void UpdateAI(uint32 /*diff*/) override { }
        void EnterCombat(Unit* /*who*/) override { }
        void DamageTaken(Unit* /*who*/, uint32& damage, DamageEffectType, SpellSchoolMask) override { damage = 0;  }

        Creature* SelectRandomSkullPile()
        {
            std::list<Creature*> triggers;
            me->GetCreatureListWithEntryInGrid(triggers, NPC_TRIGGER, 150.0f);
            uint32 targetDBGuid = CGUID_TRIGGER + urand(8, 12); // CGUID+8 to CGUID+12 are the triggers for the skull piles on dead side
            for (Creature* trigger : triggers)
                if (trigger && trigger->GetDBTableGUIDLow() == targetDBGuid)
                    return trigger;

            return nullptr;
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
        {
            if (!spell)
                return;

            switch (spell->Id)
            {
                case SPELL_ANCHOR_1_TRAINEE:
                    DoCastAOE(SPELL_ANCHOR_2_TRAINEE, true);
                    break;
                case SPELL_ANCHOR_1_DK:
                    DoCastAOE(SPELL_ANCHOR_2_DK, true);
                    break;
                case SPELL_ANCHOR_1_RIDER:
                    DoCastAOE(SPELL_ANCHOR_2_RIDER, true);
                    break;
                case SPELL_ANCHOR_2_TRAINEE:
                    if (Creature* target = SelectRandomSkullPile())
                        DoCast(target, SPELL_SKULLS_TRAINEE, true);
                    break;
                case SPELL_ANCHOR_2_DK:
                    if (Creature* target = SelectRandomSkullPile())
                        DoCast(target, SPELL_SKULLS_DK, true);
                    break;
                case SPELL_ANCHOR_2_RIDER:
                    if (Creature* target = SelectRandomSkullPile())
                        DoCast(target, SPELL_SKULLS_RIDER, true);
                    break;
                case SPELL_SKULLS_TRAINEE:
                    DoSummon(NPC_DEAD_TRAINEE, me, 4.0f, 15 * IN_MILLISECONDS, TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                    break;
                case SPELL_SKULLS_DK:
                    DoSummon(NPC_DEAD_KNIGHT, me, 4.0f, 15 * IN_MILLISECONDS, TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                    break;
                case SPELL_SKULLS_RIDER:
                    DoSummon(NPC_DEAD_RIDER, me, 4.0f, 15 * IN_MILLISECONDS, TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                    DoSummon(NPC_DEAD_HORSE, me, 4.0f, 15 * IN_MILLISECONDS, TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                    break;
            }
        }

        // dead side summons are "owned" by gothik
        void JustSummoned(Creature* summon) override
        {
            if (Creature* gothik = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(DATA_GOTHIK)))
                gothik->AI()->JustSummoned(summon);
        }

        void SummonedCreatureDespawn(Creature* summon) override
        {
            if (Creature* gothik = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(DATA_GOTHIK)))
                gothik->AI()->SummonedCreatureDespawn(summon);
        }
    };
};

class spell_gothik_shadow_bolt_volley : public SpellScriptLoader
{
    public:
        spell_gothik_shadow_bolt_volley() : SpellScriptLoader("spell_gothik_shadow_bolt_volley") { }

        class spell_gothik_shadow_bolt_volley_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gothik_shadow_bolt_volley_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(Trinity::UnitAuraCheck(false, SPELL_SHADOW_MARK));
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gothik_shadow_bolt_volley_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_gothik_shadow_bolt_volley_SpellScript();
        }
};

void AddSC_boss_gothik()
{
    new boss_gothik();
    new npc_gothik_minion_livingtrainee();
    new npc_gothik_minion_livingknight();
    new npc_gothik_minion_livingrider();
    new npc_gothik_minion_spectraltrainee();
    new npc_gothik_minion_spectralknight();
    new npc_gothik_minion_spectralrider();
    new npc_gothik_minion_spectralhorse();
    new npc_gothik_trigger();
    new spell_gothik_shadow_bolt_volley();
}
