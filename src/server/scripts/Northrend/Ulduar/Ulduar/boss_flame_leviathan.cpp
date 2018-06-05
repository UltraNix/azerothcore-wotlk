/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SpellScript.h"
#include "ulduar.h"
#include "Vehicle.h"
#include "ScriptedEscortAI.h"
#include "SpellAuras.h"
#include "PassiveAI.h"
#include "SpellAuraEffects.h"
#include "ScriptedGossip.h"
#include "CombatAI.h"
#include "CreatureGroups.h"
#include "Spell.h"
#include "GridNotifiers.h"
#include "Player.h"
#include "Opcodes.h"
#include "Chat.h"
#include "CellImpl.h"
#include "MoveSplineInit.h"
#include "Group.h"

enum LeviathanSpells
{
    // Leviathan basic
    SPELL_PURSUED                     = 62374,
    SPELL_GATHERING_SPEED             = 62375,
    SPELL_BATTERING_RAM               = 62376,
    SPELL_FLAME_VENTS                 = 62396,
    SPELL_MISSILE_BARRAGE             = 62400,
    SPELL_NAPALM_10                   = 63666,
    SPELL_NAPALM_25                   = 65026,
    SPELL_INVIS_AND_STEALTH_DETECT    = 18950,

    // Shutdown spells
    SPELL_SYSTEMS_SHUTDOWN            = 62475,
    SPELL_OVERLOAD_CIRCUIT            = 62399,

    // hard mode
    SPELL_TOWER_OF_STORMS             = 65076,
    SPELL_TOWER_OF_FLAMES             = 65075,
    SPELL_TOWER_OF_FROST              = 65077,
    SPELL_TOWER_OF_LIFE               = 64482,

    SPELL_HODIRS_FURY                 = 62533,
    SPELL_FREYA_WARD                  = 62906, // removed spawn effect
    SPELL_MIMIRONS_INFERNO            = 62909,
    SPELL_THORIMS_HAMMER              = 62911,

    SPELL_FREYA_DUMMY_BLUE            = 63294,
    SPELL_FREYA_DUMMY_GREEN           = 63295,
    SPELL_FREYA_DUMMY_YELLOW          = 63292,

    // Leviathan turret spell
    SPELL_SEARING_FLAME               = 62402,
    // On turret Destory
    SPELL_SMOKE_TRAIL                 = 63575,

    // Pool of tar blaze
    SPELL_BLAZE                       = 62292,

    // Pyrite
    SPELL_LIQUID_PYRITE               = 62494,
    SPELL_DUSTY_EXPLOSION             = 63360,
    SPELL_DUST_CLOUD_IMPACT           = 54740,
    SPELL_PYRITE_RIDE_VEHICLE         = 67390,

    // Ward of Life
    SPELL_WARD_OF_LIFE_LASH           = 65062,

    SPELL_HODIRS_FURY_AURA_FREEZE     = 62297,
    SPELL_MACHINE_FLAMES_TRIGGERED    = 65045
};

enum GosNpcs
{
    NPC_FLAME_LEVIATHAN_TURRET        = 33139,
    NPC_SEAT                          = 33114,
    NPC_MECHANOLIFT                   = 33214,
    NPC_PYRITE_SAFETY_CONTAINER       = 33218,
    NPC_LIQUID                        = 33189,

    // Starting event
    NPC_ULDUAR_COLOSSUS               = 33237,
    NPC_ARCHMAGE_PENTARUS             = 33624,
    NPC_BRANN_RADIO                   = 34054,
    NPC_ULDUAR_GAUNTLET_GENERATOR     = 33571,
    NPC_DEFENDER_GENERATED            = 33572,

    // Hard Mode
    NPC_THORIM_HAMMER_TARGET          = 33364,
    NPC_THORIM_HAMMER                 = 33365,
    NPC_FREYA_WARD_TARGET             = 33366,
    NPC_FREYA_WARD                    = 33367,
    NPC_MIMIRONS_INFERNO_TARGET       = 33369,
    NPC_MIMIRONS_INFERNO              = 33370,
    NPC_HODIRS_FURY_TARGET            = 33108,
    NPC_HODIRS_FURY                   = 33212
};

enum Events
{
    EVENT_PURSUE = 1,
    EVENT_MISSILE,
    EVENT_VENT,
    EVENT_SPEED,
    EVENT_SUMMON,
    EVENT_REINSTALL,
    EVENT_HODIRS_FURY,
    EVENT_FREYA,
    EVENT_MIMIRONS_INFERNO,
    EVENT_THORIMS_HAMMER,
    EVENT_SOUND_BEGINNING,
    EVENT_POSITION_CHECK,
};

enum Sounds
{
    LV_SOUND_AGGRO                    = 15506,
    LV_SOUND_TARGET1                  = 15507,
    LV_SOUND_TARGET2                  = 15508,
    LV_SOUND_TARGET3                  = 15509,
    LV_SOUND_HARD_MODE                = 15510,
    LV_SOUND_TOWER_0                  = 15511,
    LV_SOUND_TOWER_1                  = 15512,
    LV_SOUND_TOWER_2                  = 15513,
    LV_SOUND_TOWER_3                  = 15514,
    LV_SOUND_TOWER_4                  = 15515,
    LV_SOUND_PLAYER_RIDE              = 15516,
    LV_SOUND_OVERLOAD1                = 15517,
    LV_SOUND_OVERLOAD2                = 15518,
    LV_SOUND_OVERLOAD3                = 15519,
    LV_SOUND_DIE                      = 15520,
    LV_SOUND_SLY                      = 15521,

    RSOUND_L0                         = 15807,
    RSOUND_L1                         = 15804,
    RSOUND_L2                         = 15805,
    RSOUND_L3                         = 15806,
    RSOUND_ENGAGE                     = 15794,
    RSOUND_SILOS                      = 15795,
    RSOUND_GENERATORS                 = 15796,
    RSOUND_HODIR                      = 15797,
    RSOUND_FREYA                      = 15798,
    RSOUND_MIMIRON                    = 15799,
    RSOUND_THORIM                     = 15801,
    RSOUND_STATION                    = 15803,
};

enum Seats
{
    SEAT_PLAYER                       = 0,
    SEAT_TURRET                       = 1,
    SEAT_DEVICE                       = 2,
    SEAT_CANNON                       = 7,
};

enum Misc
{
    DATA_EVENT_STARTED                = 1, // unused
    DATA_GET_TOWER_COUNT              = 2,
    DATA_GET_SHUTDOWN                 = 3,

    TOWER_OF_STORMS                   = 2,
    TOWER_OF_FLAMES                   = 1,
    TOWER_OF_FROST                    = 3,
    TOWER_OF_LIFE                     = 0,

    ACTION_START_NORGANNON_EVENT      = 1,
    ACTION_START_NORGANNON_BRANN      = 2,
    ACTION_START_BRANN_EVENT          = 3,
    ACTION_DESPAWN_ADDS               = 4,
    ACTION_DELAY_CANNON               = 5,

    DATA_LOREKEEPER_STARTER_GUID      = 6,

    DATA_GET_FLAMES_HIT_COUNT         = 7
};

#define LV_SAY_PLAYER_RIDE    = "Unauthorized entity attempting circuit overload. Activating anti-personnel countermeasures."

///////////////////////////////////////////
//
// BOSS CODE
//
///////////////////////////////////////////

class boss_flame_leviathan : public CreatureScript
{
public:
    boss_flame_leviathan() : CreatureScript("boss_flame_leviathan") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_flame_leviathanAI (pCreature);
    }

    struct boss_flame_leviathanAI : public ScriptedAI
    {
        boss_flame_leviathanAI(Creature* pCreature) : ScriptedAI(pCreature), vehicle(me->GetVehicleKit()), summons(me)
        {
            m_pInstance = pCreature->GetInstanceScript();
            assert(vehicle);
        }

        InstanceScript* m_pInstance;
        Vehicle* vehicle;
        EventMap events;
        SummonList summons;

        uint32 _startTimer;
        uint32 _speakTimer;
        uint8 _towersCount;
        uint8 _overloadCount;

        bool _shutdown;
        bool _atWardsPhase;
        uint32 _fightTimer;
        bool _hardMode;

        // Custom
        void BindPlayers();
        void RadioSay(const char* text, uint32 soundId);
        void ActivateTowers();
        void TurnGates(bool _start, bool _death);
        void TurnHealStations(bool _apply);
        void ScheduleEvents();
        void SayPursue();
        void SummonTowerHelpers(uint8 towerId);

        // Original
        void JustReachedHome()
        {
            // For achievement
            if (m_pInstance)
                m_pInstance->SetData(DATA_UNBROKEN_ACHIEVEMENT, 0);
            me->setActive(false);
        }

        void JustSummoned(Creature* cr)
        {
            if (cr->GetEntry() != NPC_FLAME_LEVIATHAN_TURRET && cr->GetEntry() != NPC_SEAT)
                summons.Summon(cr);
        }

        void SummonedCreatureDespawn(Creature* cr) { summons.Despawn(cr); }
        void SpellHit(Unit* caster, const SpellInfo* spellInfo);
        void JustDied(Unit*);
        void KilledUnit(Unit* who);

        void AttackStart(Unit* who)
        {
            if (Unit* veh = who->GetVehicleBase())
                ScriptedAI::AttackStart(veh);
            else
                ScriptedAI::AttackStart(who);
        }

        void EnterCombat(Unit*)
        {
            _fightTimer = getMSTime();
            ScheduleEvents();
            me->MonsterYell("Hostile entities detected. Threat assessment protocol active. Primary target engaged. Time minus thirty seconds to re-evaluation.", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(LV_SOUND_AGGRO);

            me->setActive(true);
            me->SetHomePosition(322.4f, -14.3f, 409.8f, 3.23f);
            TurnGates(true, false);
            TurnHealStations(false);
            ActivateTowers();
            if (m_pInstance)
                m_pInstance->SetData(TYPE_LEVIATHAN, SPECIAL);

            me->SetInCombatWithZone();
        }

        void InitializeAI()
        {
            if (m_pInstance && m_pInstance->GetData(TYPE_LEVIATHAN) == SPECIAL)
            {
                me->SetHomePosition(322.4f, -14.3f, 409.8f, 3.23f);
                me->UpdatePosition(322.4f, -14.3f, 409.8f, 3.23f);
                me->StopMovingOnCurrentPos();
            }

            ScriptedAI::InitializeAI();
        }

        void Reset()
        {
            _hardMode = false;
            _fightTimer = 0;
            // Special immunity case
            me->CastSpell(me, SPELL_INVIS_AND_STEALTH_DETECT, true);

            summons.DoAction(ACTION_DESPAWN_ADDS);
            summons.DespawnAll();
            events.Reset();

            _shutdown = false;
            _atWardsPhase = false;
            _startTimer = 1;
            _speakTimer = 0;
            _towersCount = 0;
            _overloadCount = 0;

            if (m_pInstance)
            {
                if (m_pInstance->GetData(TYPE_LEVIATHAN) != SPECIAL)
                {
                    m_pInstance->SetData(TYPE_LEVIATHAN, NOT_STARTED);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }
                else
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    m_pInstance->SetData(DATA_VEHICLE_SPAWN, VEHICLE_POS_LEVIATHAN);
                    _startTimer = 0;
                }
            }

            TurnGates(false, false);
            TurnHealStations(true);
        }

        uint32 GetData(uint32 param) const
        {
            if (param == DATA_GET_TOWER_COUNT)
                return _towersCount;

            if (param == DATA_GET_SHUTDOWN)
                return !_shutdown;

            return 0;
        }

        void CheckWards()
        {
            std::list<Creature*> wards;
            GetCreatureListWithEntryInGrid(wards, me, 33387, 200.0f);
            if (!wards.empty())
                for (std::list<Creature*>::const_iterator itr = wards.begin(); itr != wards.end(); ++itr)
                    if (!(*itr)->IsInCombat())
                         (*itr)->ToCreature()->AI()->AttackStart(me->GetVictim());

            GetCreatureListWithEntryInGrid(wards, me, 34275, 200.0f);
            if (!wards.empty())
                for (std::list<Creature*>::const_iterator itr = wards.begin(); itr != wards.end(); ++itr)
                    if (!(*itr)->IsInCombat())
                        (*itr)->ToCreature()->AI()->AttackStart(me->GetVictim());
        }

        void ThrowPlayers()
        {
            for (uint8 i = RAID_MODE(2, 0); i < 4; i++)
                if (Unit* seat = vehicle->GetPassenger(i))
                    if (seat->GetTypeId() == TYPEID_UNIT)
                        seat->ToCreature()->AI()->EnterEvadeMode();
        }

        void UpdateAI(uint32 diff)
        {
            // THIS IS USED ONLY FOR FIRST ENGAGE!
            if (_startTimer)
            {
                _startTimer += diff;
                if (_startTimer >= 4000)
                {
                    // Colossus dead, players in range
                    if (me->FindNearestCreature(NPC_ULDUAR_COLOSSUS, 250.0f, true) || !SelectTargetFromPlayerList(250.0f))
                        _startTimer = 1;
                    else
                    {
                        _startTimer = 0;
                        _speakTimer = 1;
                    }
                }
                return;
            }

            if (_speakTimer)
            {
                _speakTimer += diff;
                if (_speakTimer <= 10000)
                {
                    RadioSay("You've done it! You've broken the defenses of Ulduar. In a few moments, we will be dropping in to...", RSOUND_L1);
                    _speakTimer = 10000;
                }
                else if (_speakTimer > 16000 && _speakTimer < 20000)
                {
                    _speakTimer = 20000;
                    RadioSay("What is that? Be careful! Something's headed your way!", RSOUND_L2);
                }
                else if (_speakTimer > 24000 && _speakTimer < 40000)
                {
                    _speakTimer = 40000;
                    RadioSay("Quicly! Evasive action! Evasive act--", RSOUND_L3);
                }
                else if (_speakTimer > 41000 && _speakTimer < 60000)
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SendMonsterMove(380.4f, -14.3f, 409.8f, 2000);
                    me->UpdatePosition(380.4f, -14.3f, 409.8f, me->GetOrientation());
                    _speakTimer = 60000;
                }
                else if (_speakTimer > 61500)
                {
                    me->SetInCombatWithZone();
                    if (!me->GetVictim())
                    {
                        me->CastSpell(me, SPELL_PURSUED, false);
                        events.RescheduleEvent(EVENT_PURSUE, 31000);
                    }
                    _speakTimer = 0;
                }
                return;
            }

            if (!UpdateVictim())
                return;

            if (_overloadCount >= RAID_MODE(2, 4))
            {
                _overloadCount = 0;  // Reset count

                me->CastSpell(me, SPELL_SYSTEMS_SHUTDOWN, true);
                me->RemoveAurasDueToSpell(SPELL_OVERLOAD_CIRCUIT);
            }

            if (_atWardsPhase)
                CheckWards();

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
            {
                if (Spell* spell = me->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                    if (spell->GetSpellInfo()->Id != SPELL_FLAME_VENTS)
                        return;
            }

            switch (events.GetEvent())
            {
                case EVENT_POSITION_CHECK:
                    if (me->GetPositionX() > 450.f || me->GetPositionX() < 120.f)
                    {
                        EnterEvadeMode();
                        return;
                    }
                    events.RepeatEvent(5000);
                    break;
                case EVENT_PURSUE:
                    SayPursue();
                    me->CastSpell(me, SPELL_PURSUED, false);
                    events.RescheduleEvent(EVENT_PURSUE, 31000);
                    return;
                case EVENT_SPEED:
                    me->CastSpell(me, SPELL_GATHERING_SPEED, false);
                    events.RepeatEvent(15000);
                    return;
                case EVENT_MISSILE:
                    me->CastSpell(me, SPELL_MISSILE_BARRAGE, true);
                    events.RepeatEvent(4000);
                    return;
                case EVENT_VENT:
                    me->CastSpell(me, SPELL_FLAME_VENTS, false);
                    events.RepeatEvent(20000);
                    return;
                case EVENT_SUMMON:
                    if(summons.size() < 27)
                        if (Creature* lift = DoSummonFlyer(NPC_MECHANOLIFT, me, 30.0f, 50.0f, 0))
                            lift->GetMotionMaster()->MoveRandom(100.0f);

                    events.RepeatEvent(4000);
                    return;
                case EVENT_SOUND_BEGINNING:
                    if (_towersCount)
                    {
                        me->MonsterYell("Orbital countermeasures enabled.", LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(LV_SOUND_HARD_MODE);
                    }
                    else
                    {
                        me->MonsterYell("Alert! Static defense system failure. Orbital countermeasures disabled.", LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(LV_SOUND_TOWER_0);
                    }
                    events.PopEvent();
                    return;
                case EVENT_REINSTALL:
                    events.PopEvent();
                    me->MonsterTextEmote("Flame Leviathan reactivated. Resumming combat functions.", 0, true);
                    return;
                case EVENT_THORIMS_HAMMER:
                    SummonTowerHelpers(TOWER_OF_STORMS);
                    events.RepeatEvent(60000+rand()%60000);
                    me->MonsterTextEmote("Flame Leviathan activates Thorim's Hammer.", 0, true);
                    me->MonsterYell("'Thorim's Hammer' online. Acquiring target.", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(LV_SOUND_TOWER_4);
                    return;
                case EVENT_FREYA:
                    _atWardsPhase = true;
                    SummonTowerHelpers(TOWER_OF_LIFE);
                    events.PopEvent();
                    me->MonsterTextEmote("Flame Leviathan activates Freya's Ward.", 0, true);
                    me->MonsterYell("'Freya's Ward' online. Acquiring target.", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(LV_SOUND_TOWER_3);
                    return;
                case EVENT_MIMIRONS_INFERNO:
                    SummonTowerHelpers(TOWER_OF_FLAMES);
                    events.PopEvent();
                    me->MonsterTextEmote("Flame Leviathan activates Mimiron's Inferno.", 0, true);
                    me->MonsterYell("'Mimiron's Inferno' online. Acquiring target.", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(LV_SOUND_TOWER_2);
                    return;
                case EVENT_HODIRS_FURY:
                    SummonTowerHelpers(TOWER_OF_FROST);
                    events.PopEvent();
                    me->MonsterTextEmote("Flame Leviathan activates Hodir's Fury.", 0, true);
                    me->MonsterYell("'Hodir's Fury' online. Acquiring target.", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(LV_SOUND_TOWER_1);
                    return;
            }

            if(me->isAttackReady() && !me->HasUnitState(UNIT_STATE_STUNNED))
            {
                if(me->IsWithinCombatRange(me->GetVictim(), 15.0f))
                {
                    me->CastSpell(me->GetVictim(), SPELL_BATTERING_RAM, false);
                    me->resetAttackTimer();
                }
            }
        }
    };
};

void boss_flame_leviathan::boss_flame_leviathanAI::BindPlayers()
{
    me->GetMap()->ToInstanceMap()->PermBindAllPlayers();
}

void boss_flame_leviathan::boss_flame_leviathanAI::RadioSay(const char* text, uint32 soundId)
{
    if (Creature *r = me->SummonCreature(NPC_BRANN_RADIO, me->GetPositionX()-150, me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 5000))
    {
        WorldPacket data;
        ChatHandler::BuildChatPacket(data, CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, r, NULL, text);
        r->SendMessageToSetInRange(&data, 200, true);
        r->PlayDirectSound(soundId);
    }
}

void boss_flame_leviathan::boss_flame_leviathanAI::ActivateTowers()
{
    _towersCount = 0;
    me->ResetLootMode();
    for (uint32 i = EVENT_TOWER_OF_LIFE_DESTROYED; i <= EVENT_TOWER_OF_FLAMES_DESTROYED; ++i)
    {
        if (m_pInstance->GetData(i))
        {
            ++_towersCount;
            switch (i)
            {
                case EVENT_TOWER_OF_LIFE_DESTROYED:
                    me->AddAura(SPELL_TOWER_OF_LIFE, me);
                    events.RescheduleEvent(EVENT_FREYA, 30000);
                    break;
                case EVENT_TOWER_OF_STORM_DESTROYED:
                    me->AddAura(SPELL_TOWER_OF_STORMS, me);
                    events.RescheduleEvent(EVENT_THORIMS_HAMMER, 60000);
                    break;
                case EVENT_TOWER_OF_FROST_DESTROYED:
                    me->AddAura(SPELL_TOWER_OF_FROST, me);
                    events.RescheduleEvent(EVENT_HODIRS_FURY, 20000);
                    break;
                case EVENT_TOWER_OF_FLAMES_DESTROYED:
                    me->AddAura(SPELL_TOWER_OF_FLAMES, me);
                    events.RescheduleEvent(EVENT_MIMIRONS_INFERNO, 42000);
                    break;
            }
        }
    }
    if (_towersCount >= 4)
        _hardMode = true;

    if (_towersCount >= 2)
        me->AddLootMode(1 << _towersCount);
}

void boss_flame_leviathan::boss_flame_leviathanAI::TurnGates(bool _start, bool _death)
{
    if (!m_pInstance)
        return;

    if (_start)
    {
        // first one is ALWAYS turned on, unless leviathan is beaten
        GameObject* go = NULL;
        if (go = ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(DATA_LIGHTNING_WALL2)))
            go->SetGoState(GO_STATE_READY);

        if (m_pInstance->GetData(TYPE_LEVIATHAN) == NOT_STARTED)
            if (go = ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(GO_LEVIATHAN_DOORS)))
                go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
    }
    else
    {
        GameObject* go = NULL;
        if (_death)
            if (go = ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(DATA_LIGHTNING_WALL1)))
                go->SetGoState(GO_STATE_ACTIVE);

        if (go = ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(DATA_LIGHTNING_WALL2)))
            go->SetGoState(GO_STATE_ACTIVE);

        if (go = ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(GO_LEVIATHAN_DOORS)))
        {
            if (m_pInstance->GetData(TYPE_LEVIATHAN) == SPECIAL || m_pInstance->GetData(TYPE_LEVIATHAN) == DONE)
                go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
            else
                go->SetGoState(GO_STATE_READY);
        }
    }
}

void boss_flame_leviathan::boss_flame_leviathanAI::TurnHealStations(bool _apply)
{
    if (!m_pInstance)
        return;

    GameObject* go = NULL;
    if (_apply)
    {
        if (go = ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(DATA_REPAIR_STATION1)))
            go->SetLootState(GO_READY);
        if (go = ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(DATA_REPAIR_STATION2)))
            go->SetLootState(GO_READY);
    }
    else
    {
        if (go = ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(DATA_REPAIR_STATION1)))
            go->SetLootState(GO_ACTIVATED);
        if (go = ObjectAccessor::GetGameObject(*me, m_pInstance->GetData64(DATA_REPAIR_STATION2)))
            go->SetLootState(GO_ACTIVATED);
    }
}

void boss_flame_leviathan::boss_flame_leviathanAI::ScheduleEvents()
{
    events.RescheduleEvent(EVENT_MISSILE, 5000);
    events.RescheduleEvent(EVENT_VENT, 20000);
    events.RescheduleEvent(EVENT_SPEED, 15000);
    events.RescheduleEvent(EVENT_SUMMON, 10000);
    events.RescheduleEvent(EVENT_SOUND_BEGINNING, 10000);
    events.RescheduleEvent(EVENT_POSITION_CHECK, 5000);

    events.RescheduleEvent(EVENT_PURSUE, 0);
}

void boss_flame_leviathan::boss_flame_leviathanAI::SayPursue()
{
    if (urand(0,1))
        return;

    switch (urand(0,2))
    {
        case 0:
            me->MonsterYell("Threat re-evaluated. Target assessment complete. Changing course.", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(LV_SOUND_TARGET1);
            break;
        case 1:
            me->MonsterYell("Pursuit objective modified. Changing course.", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(LV_SOUND_TARGET2);
            break;
        case 2:
            me->MonsterYell("Hostile entity stratagem predicted. Rerouting battle function. Changing course.", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(LV_SOUND_TARGET3);
            break;
    }
}

void boss_flame_leviathan::boss_flame_leviathanAI::SpellHit(Unit* caster, const SpellInfo* spellInfo)
{
    if (caster->GetTypeId() == TYPEID_PLAYER)
        me->RemoveAurasDueToSpell(spellInfo->Id);

    if (spellInfo->Id == SPELL_OVERLOAD_CIRCUIT)
        ++_overloadCount;

    if (spellInfo->Id == SPELL_SYSTEMS_SHUTDOWN)
    {
        _shutdown = true; // ACHIEVEMENT
        ThrowPlayers();

        me->MonsterTextEmote("Flame Leviathan's circuits overloaded.", 0, true);
        me->MonsterTextEmote("Automatic repair sequence initiated.", 0, true);

        switch (urand(0,2))
        {
        case 0:
            me->MonsterYell("System malfunction. Diverting power to support systems.", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(LV_SOUND_OVERLOAD1);
            break;
        case 1:
            me->MonsterYell("Combat matrix overload. Powering do-o-o-own...", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(LV_SOUND_OVERLOAD2);
            break;
        case 2:
            me->MonsterYell("System restart required. Deactivating weapon systems.", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(LV_SOUND_OVERLOAD3);
            break;
        }

        events.DelayEvents(20 * IN_MILLISECONDS + 1);
        events.ScheduleEvent(EVENT_REINSTALL, 20*IN_MILLISECONDS);
    }
    else if (spellInfo->Id == 62522 /*SPELL_ELECTROSHOCK*/)
        me->InterruptNonMeleeSpells(false);
}

void boss_flame_leviathan::boss_flame_leviathanAI::JustDied(Unit* killer)
{
    // We cannot store all mechanos due to one of them being spawned
    // and others being temps, so we gotta do grid search once
    std::list<Creature*> mechanoList;
    std::list<Creature*> pyriteList;
    me->GetCreatureListWithEntryInGrid(mechanoList, NPC_MECHANOLIFT, 400.0f);
    me->GetCreatureListWithEntryInGrid(pyriteList, NPC_PYRITE_SAFETY_CONTAINER, 400.0f);

    for (auto mechano : mechanoList)
    {
        mechano->SetRespawnDelay(604800);
        mechano->DespawnOrUnsummon();
    }

    for (auto liquid : pyriteList)
        liquid->DespawnOrUnsummon();

    // Despawn Lashers, do before summons clear
    summons.DoAction(ACTION_DESPAWN_ADDS);
    summons.DespawnAll();

    if (m_pInstance)
    {
        m_pInstance->SetData(TYPE_LEVIATHAN, DONE);
        m_pInstance->SetData(DATA_VEHICLE_SPAWN, VEHICLE_POS_NONE);
    }

    me->MonsterYell("Total systems failure. Defense protocols breached. Leviathan Unit shutting down.", LANG_UNIVERSAL, 0);
    me->PlayDirectSound(LV_SOUND_DIE);

    TurnGates(false, true);
    BindPlayers();

    uint64 leaderGUID = 0;

    auto& playerList = me->GetMap()->GetPlayers();

    for (auto& i : playerList)
    {
        Player* player = i.GetSource();

        if (!player)
            continue;

        if (!player->GetGroup())
            continue;

        leaderGUID = player->GetGroup()->GetLeaderGUID();

        if (leaderGUID)
            break;
    }

    if (Map* map = me->GetMap())
    {
        if (Player* player = ObjectAccessor::GetPlayer(*me, leaderGUID))
        {
            if (_hardMode)
                CheckCreatureRecord(killer, me->GetCreatureTemplate()->Entry + 1, Difficulty(map->GetDifficulty() + 2), "", 15000, _fightTimer);
            else
                CheckCreatureRecord(killer, me->GetCreatureTemplate()->Entry, map->GetDifficulty(), "", 15000, _fightTimer);
        }
    }
}

void boss_flame_leviathan::boss_flame_leviathanAI::KilledUnit(Unit* who)
{
    if (who == me->GetVictim())
        events.RescheduleEvent(EVENT_PURSUE, 0);
}

void boss_flame_leviathan::boss_flame_leviathanAI::SummonTowerHelpers(uint8 towerId)
{
    if (towerId == TOWER_OF_LIFE)
    {
        me->SummonCreature(NPC_FREYA_WARD_TARGET, 374, -141, 411, 0, TEMPSUMMON_MANUAL_DESPAWN);
        me->SummonCreature(NPC_FREYA_WARD, 374, -141, 411 + 40.f, 0, TEMPSUMMON_MANUAL_DESPAWN);

        me->SummonCreature(NPC_FREYA_WARD_TARGET, 375.440f, 65.855f, 411.976f, 0, TEMPSUMMON_MANUAL_DESPAWN);
        me->SummonCreature(NPC_FREYA_WARD, 375.440f, 65.855f, 411.976f + 40.f, 0, TEMPSUMMON_MANUAL_DESPAWN);

        me->SummonCreature(NPC_FREYA_WARD_TARGET, 168.850f, 55.403099f, 409.799988f, 0, TEMPSUMMON_MANUAL_DESPAWN);
        me->SummonCreature(NPC_FREYA_WARD, 168.850f, 55.403099f, 409.799988f + 40.f, 0, TEMPSUMMON_MANUAL_DESPAWN);

        me->SummonCreature(NPC_FREYA_WARD_TARGET, 167.067520f, -130.377716f, 409.799988f, 0, TEMPSUMMON_MANUAL_DESPAWN);
        me->SummonCreature(NPC_FREYA_WARD, 167.067520f, -130.377716f, 409.799988f + 40.f, 0, TEMPSUMMON_MANUAL_DESPAWN);
    }
    else if (towerId == TOWER_OF_FROST)
    {
        me->SummonCreature(NPC_HODIRS_FURY_TARGET, 343.4f, -77.5f, 409.8f, 0, TEMPSUMMON_MANUAL_DESPAWN);
        me->SummonCreature(NPC_HODIRS_FURY_TARGET, 222, 41, 409.8f, 0, TEMPSUMMON_MANUAL_DESPAWN);
    }
    else if (towerId == TOWER_OF_FLAMES)
    {
        me->SummonCreature(NPC_MIMIRONS_INFERNO_TARGET, 364.4f, -9.7f, 409.8f, 0, TEMPSUMMON_MANUAL_DESPAWN);
        //me->SummonCreature(NPC_MIMIRONS_INFERNO, 364.4f, -9.7f, 409.8f+40, 0, TEMPSUMMON_MANUAL_DESPAWN);
    }
    else if (towerId == TOWER_OF_STORMS)
    {
        for (uint8 i = 0; i < 8; ++i)
            me->SummonCreature(NPC_THORIM_HAMMER_TARGET, 157+rand()%200, -140+rand()%200, 409.8f, 0, TEMPSUMMON_TIMED_DESPAWN, 24000);
    }
}

class boss_flame_leviathan_seat : public CreatureScript
{
public:
    boss_flame_leviathan_seat() : CreatureScript("boss_flame_leviathan_seat") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_flame_leviathan_seatAI (pCreature);
    }

    struct boss_flame_leviathan_seatAI : public VehicleAI
    {
        boss_flame_leviathan_seatAI(Creature *creature) : VehicleAI(creature), vehicle(creature->GetVehicleKit())
        {
            ASSERT(vehicle);
            me->SetReactState(REACT_PASSIVE);
        }

        Vehicle* vehicle;
        uint32 _despawnTimer;

        void EnterEvadeMode()
        {
            vehicle->InstallAllAccessories(false);
        }

        void Reset()
        {
            _despawnTimer = !me->GetMap()->Is25ManRaid();
        }

        void UpdateAI(uint32 diff)
        {
            if (_despawnTimer)
            {
                _despawnTimer += diff;
                if (_despawnTimer >= 2000)
                {
                    _despawnTimer = 0;
                    if (Vehicle* veh = me->GetVehicle())
                        if (veh->GetPassenger(0) == me || veh->GetPassenger(1) == me)
                            me->DespawnOrUnsummon(1);
                }
            }

             VehicleAI::UpdateAI(diff);
        }

        void AttackStart(Unit*) { }

        void PassengerBoarded(Unit* who, int8 seatId, bool apply)
        {
            if (who->GetTypeId() != TYPEID_PLAYER || !me->GetVehicle())
                return;

            who->ApplySpellImmune(63847, IMMUNITY_ID, 63847, apply); // SPELL_FLAME_VENTS_TRIGGER

            who->ApplySpellImmune(62910, IMMUNITY_ID, 62910, apply); // TOWERS
            who->ApplySpellImmune(62297, IMMUNITY_ID, 62297, apply); // TOWERS
            who->ApplySpellImmune(62907, IMMUNITY_ID, 62907, apply); // TOWERS
            who->ApplySpellImmune(62912, IMMUNITY_ID, 62912, apply); // TOWERS

            who->ApplySpellImmune(SPELL_MISSILE_BARRAGE, IMMUNITY_ID, SPELL_MISSILE_BARRAGE, apply);
            who->ApplySpellImmune(SPELL_BATTERING_RAM, IMMUNITY_ID, SPELL_BATTERING_RAM, apply);

            if (seatId == SEAT_PLAYER)
            {
                if (Unit* turret = me->GetVehicleKit()->GetPassenger(SEAT_TURRET))
                {
                    if (apply)
                    {
                        Movement::MoveSplineInit init(who);
                        init.DisableTransportPathTransformations();
                        init.MoveTo(1.0f, 0.0f, 0.3f, false);
                        init.SetFacing(3.141593f);
                        init.Launch();
                        turret->SetUInt32Value(UNIT_FIELD_FLAGS, 0);
                        turret->GetAI()->AttackStart(who);
                    }
                    else
                    {
                        turret->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_IMMUNE_TO_PC|UNIT_FLAG_IMMUNE_TO_NPC);
                        if (turret->GetTypeId() == TYPEID_UNIT)
                            turret->ToCreature()->AI()->EnterEvadeMode();
                    }
                }
            }
        }
    };
};

class boss_flame_leviathan_defense_turret : public CreatureScript
{
    public:
        boss_flame_leviathan_defense_turret() : CreatureScript("boss_flame_leviathan_defense_turret") { }

        struct boss_flame_leviathan_defense_turretAI : public TurretAI
        {
            boss_flame_leviathan_defense_turretAI(Creature* creature) : TurretAI(creature) { _setHealth = false; }

            bool _setHealth;

            void DamageTaken(Unit* who, uint32 &damage, DamageEffectType, SpellSchoolMask)
            {
                if (!who || !CanAIAttack(who))
                {
                    _setHealth = true;
                     damage = 0;
                }
            }

            void JustDied(Unit* who)
            {
                if (Player* killer = who->ToPlayer())
                    killer->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_GET_KILLING_BLOWS, 1, 0, me);

                if (Vehicle* vehicle = me->GetVehicle())
                    if (Unit* device = vehicle->GetPassenger(SEAT_DEVICE))
                        device->SetUInt32Value(UNIT_FIELD_FLAGS, 0); // unselectable

                if (Creature* _Leviathan = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_LEVIATHAN)))
                    me->CastSpell(_Leviathan, SPELL_OVERLOAD_CIRCUIT, true);
            }

            bool CanAIAttack(Unit const* who) const
            {
                if (who->GetTypeId() != TYPEID_PLAYER || !who->GetVehicle() || who->GetVehicleBase()->GetEntry() != NPC_SEAT)
                    return false;

                return true;
            }

            void UpdateAI(uint32 diff)
            {
                if (_setHealth)
                {
                    me->SetHealth(std::min(me->GetHealth() + 1, me->GetMaxHealth()));
                    _setHealth = false;
                }

                TurretAI::UpdateAI(diff);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_flame_leviathan_defense_turretAI(creature);
        }
};

class boss_flame_leviathan_overload_device : public CreatureScript
{
    public:
        boss_flame_leviathan_overload_device() : CreatureScript("boss_flame_leviathan_overload_device") { }

        struct boss_flame_leviathan_overload_deviceAI : public NullCreatureAI
        {
            boss_flame_leviathan_overload_deviceAI(Creature* creature) : NullCreatureAI(creature)
            {
            }

            void OnSpellClick(Unit* /*clicker*/, bool& result)
            {
                if (!result)
                    return;

                if (me->GetVehicle())
                {
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                    if (Unit* player = me->GetVehicle()->GetPassenger(SEAT_PLAYER))
                    {
                        me->GetVehicleBase()->CastSpell(player, SPELL_SMOKE_TRAIL, true);
                        player->ExitVehicle();
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_flame_leviathan_overload_deviceAI(creature);
        }
};

class npc_freya_ward : public CreatureScript
{
public:
    npc_freya_ward() : CreatureScript("npc_freya_ward") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_freya_wardAI (pCreature);
    }

    struct npc_freya_wardAI : public NullCreatureAI
    {
        npc_freya_wardAI(Creature *c) : NullCreatureAI(c), summons(c)
        {
        }

        SummonList summons;
        uint32 _castTimer;
        bool _summoned;

        void Reset()
        {
            _summoned = false;
            _castTimer = 25000;
            summons.DespawnAll();
            if (Creature* cr = me->FindNearestCreature(NPC_FREYA_WARD_TARGET, 60.0f, true))
                if (Aura* aur = cr->AddAura(SPELL_FREYA_DUMMY_GREEN, cr))
                {
                    aur->SetMaxDuration(-1);
                    aur->SetDuration(-1);
                }
        }

        void JustSummoned(Creature* cr)
        {
            _summoned = true;

            if (cr)
            {
                summons.Summon(cr);
                cr->SetInCombatWithZone();
            }
        }

        void SummonedCreatureDespawn(Creature* cr) { summons.Despawn(cr); }

        void UpdateAI(uint32 diff)
        {
            if (_summoned)
            {
                for (SummonList::const_iterator itr = summons.begin(); itr != summons.end();)
                {
                    Creature* summon = ObjectAccessor::GetCreature(*me, *itr);
                    ++itr;
                    if (summon)
                    {
                        summon->ToTempSummon()->SetTempSummonType(TEMPSUMMON_MANUAL_DESPAWN);
                        if (Unit* target = summon->SelectNearestTarget(200.0f))
                            summon->AI()->AttackStart(target);
                    }
                }
                _summoned = false;
            }

            _castTimer += diff;
            if (_castTimer >= 29*IN_MILLISECONDS)
            {
                if (Creature* cr = me->FindNearestCreature(NPC_FREYA_WARD_TARGET, 60.0f, true))
                {
                    me->CastSpell(cr, SPELL_FREYA_WARD, false);
                    me->CastSpell(cr, 62947 /*SPELL_FREYA_WARD_SECOND_SUMMON*/, false);
                }

                _castTimer = 0;
            }
        }

        void DoAction(int32 param)
        {
            if (param == ACTION_DESPAWN_ADDS)
                summons.DespawnAll();
        }
    };
};

class npc_hodirs_fury : public CreatureScript
{
public:
    npc_hodirs_fury() : CreatureScript("npc_hodirs_fury") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_hodirs_furyAI (pCreature);
    }

    struct npc_hodirs_furyAI : public NullCreatureAI
    {
        npc_hodirs_furyAI(Creature *c) : NullCreatureAI(c)
        {
        }

        uint32 _timeToHit;
        uint32 _switchTargetTimer;

        void Reset()
        {
            _timeToHit = 0;
            _switchTargetTimer = 30000;
            me->SetWalk(true);

            if (Aura* aur = me->AddAura(SPELL_FREYA_DUMMY_BLUE, me))
            {
                aur->SetMaxDuration(-1);
                aur->SetDuration(-1);
            }
        }

        void MovementInform(uint32 type, uint32 param)
        {
            if (type == FOLLOW_MOTION_TYPE && !_timeToHit)
            {
                _timeToHit = 1;
                _switchTargetTimer = 0;
                me->SetControlled(true, UNIT_STATE_STUNNED);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (_timeToHit)
            {
                _timeToHit += diff;
                if (_timeToHit >= 5000)
                {
                    if (Creature* cr = me->SummonCreature(NPC_HODIRS_FURY, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+40, 0, TEMPSUMMON_TIMED_DESPAWN, 10000))
                        cr->CastSpell(me, SPELL_HODIRS_FURY, true);

                    _switchTargetTimer = 25000; // Switch target soon
                    _timeToHit = 0;
                }
                return;
            }

            _switchTargetTimer += diff;
            if (_switchTargetTimer >= 30000)
            {
                if (Unit* target = me->SelectNearbyTarget(NULL, 200.0f))
                {
                    if (target->isDead())
                    {
                        _switchTargetTimer = 2000;
                        return;

                    }

                    if (target->GetVehicleBase() && target->GetVehicleBase()->GetEntry() == NPC_SEAT)
                    {
                        _switchTargetTimer = 20000;
                        return;
                    }
                    me->SetControlled(false, UNIT_STATE_STUNNED);
                    me->GetMotionMaster()->MoveFollow(target, 0.0f, 0.0f);
                    _switchTargetTimer = 0;
                }
                else
                    _switchTargetTimer = 25000;
            }
        }
    };
};

class npc_mimirons_inferno : public CreatureScript
{
public:
    npc_mimirons_inferno() : CreatureScript("npc_mimirons_inferno") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mimirons_infernoAI(creature);
    }

    struct npc_mimirons_infernoAI : public npc_escortAI
    {
        npc_mimirons_infernoAI(Creature* creature) : npc_escortAI(creature), summons(me)
        {
            me->SetReactState(REACT_PASSIVE);
        }

        SummonList summons;
        uint32 _spellTimer;
        uint32 _recastTimer;

        void AttackStart(Unit*) { }
        void MoveInLineOfSight(Unit*) { }
        void WaypointReached(uint32 /*waypointId*/) { }

        void DoAction(int32 param)
        {
            if (param == ACTION_DESPAWN_ADDS)
                summons.DespawnAll();
        }

        void Reset()
        {
            summons.DespawnAll();
            _spellTimer = 0;
            Start(false, false, 0, NULL, false, true);
            if (Aura* aur = me->AddAura(SPELL_FREYA_DUMMY_YELLOW, me))
            {
                aur->SetMaxDuration(-1);
                aur->SetDuration(-1);
            }
        }

        void JustSummoned(Creature* cr) { summons.Summon(cr); }
        void SummonedCreatureDespawn(Creature* cr) { summons.Despawn(cr); }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            _spellTimer += diff;
            if (_spellTimer >= 2000)
            {
                if (Creature* cr = me->SummonCreature(NPC_MIMIRONS_INFERNO, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+40.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 30000))
                {
                    cr->setActive(true);
                    cr->CastSpell(me, SPELL_MIMIRONS_INFERNO, true);
                }

                _spellTimer = 0;
            }
        }
    };

};

class npc_thorims_hammer : public CreatureScript
{
public:
    npc_thorims_hammer() : CreatureScript("npc_thorims_hammer") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_thorims_hammerAI (pCreature);
    }

    struct npc_thorims_hammerAI : public NullCreatureAI
    {
        npc_thorims_hammerAI(Creature *c) : NullCreatureAI(c)
        {
        }

        uint32 _beamTimer;
        uint32 _finishTime;
        uint32 _removeTimer;

        void Reset()
        {
            _finishTime = 5000+rand()%15000;
            _beamTimer = 1;
            _removeTimer = 0;
            me->CastSpell(me, SPELL_FREYA_DUMMY_BLUE, true);
        }

        void UpdateAI(uint32 diff)
        {
            if (_beamTimer)
            {
                _beamTimer += diff;
                if (_beamTimer >= _finishTime)
                {
                    if (Creature* cr = me->SummonCreature(NPC_THORIM_HAMMER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+40, 0, TEMPSUMMON_TIMED_DESPAWN, 5000))
                        cr->CastSpell(me, SPELL_THORIMS_HAMMER, false);

                    _beamTimer = 0;
                    _removeTimer = 1;
                    me->DespawnOrUnsummon(5*IN_MILLISECONDS);
                }
            }
            if (_removeTimer)
            {
                _removeTimer += diff;
                if (_removeTimer >= 3*IN_MILLISECONDS)
                {
                    _removeTimer = 0;
                    me->RemoveAura(SPELL_FREYA_DUMMY_BLUE);
                }
            }
        }
    };
};

class npc_pool_of_tar : public CreatureScript
{
public:
    npc_pool_of_tar() : CreatureScript("npc_pool_of_tar") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_pool_of_tarAI (pCreature);
    }

    struct npc_pool_of_tarAI : public NullCreatureAI
    {
        npc_pool_of_tarAI(Creature *c) : NullCreatureAI(c)
        {
        }

        void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask)
        {
            damage = 0;
            
        }

        void SpellHit(Unit* caster, const SpellInfo* spellInfo)
        {
            if (spellInfo->SchoolMask & SPELL_SCHOOL_MASK_FIRE && !me->HasAura(SPELL_BLAZE))
                me->CastSpell(me, SPELL_BLAZE, true);
        }
    };
};

enum lorekeeperNorgannon
{
    // Norgannon talks
    NORG_SAY_0              = 0, // I was constructed to serve as a repository for essential information regarding this complex. My primary functions include communicating the status of the frontal defense systems and assessing the status of the entity that this complex was built to imprison.
    NORG_SAY_1              = 1, // Access to the interior of the complex is currently restricted. Primary defensive emplacements are active. Secondary systems are currently non-active.
    NORG_SAY_2              = 2, // Compromise of complex detected, security override enabled - query permitted.
    NORG_SAY_3              = 3, // Primary defensive emplacements consist of iron constructs and Storm Beacons, which will generate additional constructs as necessary. Secondary systems consist of orbital defense emplacements.
    NORG_SAY_4              = 4, // Entity designate: Yogg-Saron. Security has been compromised. Prison operational status unknown. Unable to contact Watchers for notification purposes.

    DELLORAH_SAY_0          = 0, // I heard a story or two of a Lore Keeper in Uldaman that fit your description. Do you serve a similar purpose?
    DELLORAH_SAY_1          = 1, // Frontal defense systems? Is there something I should let Brann know before he has anyone attempt to enter the complex?
    DELLORAH_SAY_2          = 2, // Can you detail the nature of these defense systems?
    DELLORAH_SAY_3          = 3, // Got it. At least we don\'t have to deal with those orbital emplacements.
    DELLORAH_SAY_4          = 4, // Rhydian, make sure you let Brann and Archmage Pentarus know about those defenses immediately.
    DELLORAH_SAY_5          = 5, // And you mentioned an imprisoned entity? What is the nature of this entity and what is its status?
    DELLORAH_SAY_6          = 6, // Yogg-Saron is here? It sounds like we really will have our hands full then.
    DELLORAH_SAY_7          = 7, // What... What did you just do, $n?! Brann! Braaaaannn!
    DELLORAH_SAY_8          = 8, // Brann! $n just activated the orbital defense system! If we don't get out of here soon, we're going to be toast!

    RHYDIAN_SAY_0           = 0,
    RHYDIAN_SAY_1           = 1,

    NORG_DEFAULT_GOSSIP     = 14375,
    NORG_FIRST_STEP_GOSSIP  = 14496,
    NORG_LAST_STEP_GOSSIP   = 14497,

    EVENT_NORG_1             = 1,
    EVENT_NORG_2             = 2,
    EVENT_NORG_3             = 3,
    EVENT_NORG_4             = 4,
    EVENT_NORG_5             = 5,
    EVENT_NORG_6             = 6,
    EVENT_NORG_7             = 7,
    EVENT_NORG_8             = 8,
    EVENT_NORG_9             = 9,
    EVENT_NORG_10            = 10,
    EVENT_NORG_11            = 11,
    EVENT_NORG_12            = 12,
    EVENT_NORG_13            = 13,
    EVENT_NORG_14            = 14,
    EVENT_NORG_15            = 15,
    EVENT_NORG_16            = 16
};

uint32 const rhydianMovementEntranceSize = 3;
G3D::Vector3 const rhydianMovementEntrance[rhydianMovementEntranceSize] =
{
    { -761.094482f, -82.606712f, 429.839539f },
    { -743.694885f, -53.428951f, 429.839661f },
    { -721.041626f, -53.996769f, 429.840942f }
};

class npc_lore_keeper_of_norgannon_ulduar : public CreatureScript
{
public:
    npc_lore_keeper_of_norgannon_ulduar() : CreatureScript("npc_lore_keeper_of_norgannon_ulduar") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        InstanceScript* instance = creature->GetInstanceScript();
        if (!instance)
            return true;

        if (instance->GetData(DATA_ENTRANCE_EVENT_STARTED))
            return true;

        player->SEND_GOSSIP_MENU(NORG_DEFAULT_GOSSIP, creature->GetGUID());
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
    {
        InstanceScript* instance = creature->GetInstanceScript();
        if (!instance)
            return true;

        if (instance->GetData(DATA_ENTRANCE_EVENT_STARTED))
        {
            player->PlayerTalkClass->SendCloseGossip();
            return true;
        }

        player->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
            case 1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Confirmed.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(NORG_FIRST_STEP_GOSSIP, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->SEND_GOSSIP_MENU(NORG_LAST_STEP_GOSSIP, creature->GetGUID());
                creature->AI()->SetGUID(player->GetGUID());
                creature->AI()->DoAction(ACTION_START_NORGANNON_EVENT);
                break;
        }
        return true;
    }

    struct npc_lore_keeper_of_norgannon_ulduarAI : public ScriptedAI
    {
        npc_lore_keeper_of_norgannon_ulduarAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        void SetGUID(uint64 guid, int32 /*data*/) override
        {
            _eventStarterGUID = guid;
        }

        uint64 GetData64(uint32 /*data*/) const override
        {
            return _eventStarterGUID;
        }

        void DoAction(int32 param)
        {
            if (!instance)
                return;

            if (instance->GetData(DATA_ENTRANCE_EVENT_STARTED))
                return;

            if (param == ACTION_START_NORGANNON_EVENT)
            {
                events.Reset();
                instance->SetData(DATA_ENTRANCE_EVENT_STARTED, DATA_ENTRANCE_EVENT_STARTED);

                if (Player* player = ObjectAccessor::GetPlayer(*me, _eventStarterGUID))
                {
                    if (Creature* dell = GetPartner())
                    {
                        dell->AI()->Talk(DELLORAH_SAY_7, player);
                        Movement::PointsArray path(rhydianMovementEntrance, rhydianMovementEntrance + rhydianMovementEntranceSize);
                        Movement::MoveSplineInit init(dell);
                        init.MovebyPath(path, 0);
                        init.SetSmooth();
                        init.SetFacing(6.06f);
                        auto timeToArrive = init.Launch();
                        events.ScheduleEvent(EVENT_NORG_15, timeToArrive);
                    }
                }
            }
        }

        void Reset() override
        {
            events.Reset();
            _executeTalks = true;
            events.ScheduleEvent(EVENT_NORG_1, 10s);
            _eventStarterGUID = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (!_executeTalks)
                return;

            events.Update(diff);

            while (auto eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_NORG_1:
                        if (Creature* dell = GetPartner())
                            dell->AI()->Talk(DELLORAH_SAY_0);
                        events.ScheduleEvent(EVENT_NORG_2, 7s);
                        break;
                    case EVENT_NORG_2:
                        Talk(NORG_SAY_0);
                        events.ScheduleEvent(EVENT_NORG_3, 10s);
                        break;
                    case EVENT_NORG_3:
                        if (Creature* dell = GetPartner())
                            dell->AI()->Talk(DELLORAH_SAY_1);
                        events.ScheduleEvent(EVENT_NORG_4, 12s);
                        break;
                    case EVENT_NORG_4:
                        Talk(NORG_SAY_1);
                        events.ScheduleEvent(EVENT_NORG_5, 7s);
                        break;
                    case EVENT_NORG_5:
                        if (Creature* dell = GetPartner())
                            dell->AI()->Talk(DELLORAH_SAY_2);
                        events.ScheduleEvent(EVENT_NORG_6, 7s);
                        break;
                    case EVENT_NORG_6:
                        Talk(NORG_SAY_2);
                        events.ScheduleEvent(EVENT_NORG_7, 7s);
                        break;
                    case EVENT_NORG_7:
                        Talk(NORG_SAY_3);
                        events.ScheduleEvent(EVENT_NORG_8, 16s);
                        break;
                    case EVENT_NORG_8:
                        if (Creature* dell = GetPartner())
                        {
                            if (Creature* rhydian = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_RHYDIAN_ENTRANCE)))
                                dell->SetFacingTo(dell->GetAngle(rhydian->GetPositionX(), rhydian->GetPositionY()));

                            dell->AI()->Talk(DELLORAH_SAY_4);
                        }
                        events.ScheduleEvent(EVENT_NORG_9, 6s);
                        break;
                    case EVENT_NORG_9:
                        if (Creature* dell = GetPartner())
                        {
                            dell->AI()->Talk(DELLORAH_SAY_5);
                            dell->SetFacingTo(dell->GetAngle(me->GetPositionX(), me->GetPositionY()));
                        }

                        if (Creature* rhydian = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_RHYDIAN_ENTRANCE)))
                        {
                            rhydian->AI()->Talk(RHYDIAN_SAY_0);
                            Movement::PointsArray path(rhydianMovementEntrance, rhydianMovementEntrance + rhydianMovementEntranceSize);
                            Movement::MoveSplineInit init(rhydian);
                            init.MovebyPath(path, 0);
                            init.SetSmooth();
                            init.SetFacing(6.06f);
                            auto timer = init.Launch();
                            events.ScheduleEvent(EVENT_NORG_13, timer);
                        }
                        events.ScheduleEvent(EVENT_NORG_10, 8s);
                        break;
                    case EVENT_NORG_10:
                        Talk(NORG_SAY_4);
                        events.ScheduleEvent(EVENT_NORG_11, 10s);
                        break;
                    case EVENT_NORG_11:
                        if (Creature* dell = GetPartner())
                            dell->AI()->Talk(DELLORAH_SAY_6);

                        events.ScheduleEvent(EVENT_NORG_12, 2min);
                        break;
                    case EVENT_NORG_12:
                        Reset();
                        break;
                    case EVENT_NORG_13:
                        if (Creature* rhydian = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_RHYDIAN_ENTRANCE)))
                            rhydian->AI()->Talk(RHYDIAN_SAY_1);
                        events.ScheduleEvent(EVENT_NORG_14, 5s);
                        break;
                    case EVENT_NORG_14:
                        if (Creature* rhydian = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_RHYDIAN_ENTRANCE)))
                            rhydian->GetMotionMaster()->MoveTargetedHome();
                        break;
                    case EVENT_NORG_15:
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _eventStarterGUID))
                        {
                            if (Creature* dell = GetPartner())
                                dell->AI()->Talk(DELLORAH_SAY_8, player);
                        }
                        events.ScheduleEvent(EVENT_NORG_16, 2s);
                        break;
                    case EVENT_NORG_16:
                        if (Creature* dell = GetPartner())
                            dell->GetMotionMaster()->MovePoint(1, -803.492126f, -78.503876f, 429.842865f);
                        _executeTalks = false;

                        if (Creature* brann = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_BRANN_ENTRANCE)))
                            if (brann->IsAIEnabled)
                                brann->AI()->DoAction(ACTION_START_NORGANNON_BRANN);
                        break;
                }
            }
        }

        //! can return null so make sure the pointer exists
        Creature* GetPartner()
        {
            if (!instance)
                return nullptr;

            Creature* dell = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_DELLORAH));
            return dell->IsAIEnabled ? dell : nullptr;
        }

    private:
        InstanceScript* instance;
        EventMap events;
        bool _executeTalks;
        uint64 _eventStarterGUID;
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_lore_keeper_of_norgannon_ulduarAI(pCreature);
    }
};

enum BrannUlduarEvents
{
    EVENT_BRANN_GATE_0          = 1,
    EVENT_BRANN_GATE_1          = 2,
    EVENT_BRANN_GATE_2          = 3,
    EVENT_BRANN_GATE_3          = 4,
    EVENT_BRANN_GATE_4          = 5,
    EVENT_BRANN_GATE_5          = 6,
    EVENT_BRANN_GATE_6          = 7,
    EVENT_BRANN_GATE_7          = 8,

    BRANN_GATE_SAY_0            = 0,
    BRANN_GATE_SAY_1            = 1,
    BRANN_GATE_SAY_2            = 2,
    BRANN_GATE_SAY_3            = 3,

    PENTARUS_GATE_SAY_0         = 0,
    PENTARUS_GATE_SAY_1         = 1,

    NPC_KIRIN_TOR_MAGE          = 33672,
    NPC_KIRIN_TOR_BATTLE_MAGE   = 33662,
    NPC_ARCHMAGUS_PENTARUS      = 33624,
    NPC_HIRED_ENGINEER_BRANN    = 33626,
    NPC_ULDUAR_SHIELD_BUNNY     = 33779,

    NPC_EARTHEN_STONESHAPER     = 33620,

    SPELL_ARCANE_EXPLOSION_MASS = 63660,

    BRANN_POST_EVENT_GOSSIP     = 14415,
    BRANN_DEFAULT_EVENT_GOSSIP  = 14369,
    BRANN_DEFAULT_GOSSIP_MENU   = 10355
};

uint32 const RightSidePositionsSize = 3;
G3D::Vector3 const RightSidePositions[RightSidePositionsSize] =
{
    { -688.404968f, -83.754547f, 428.292725f }, // middle
    { -688.184875f, -86.861763f, 428.282227f }, // right
    { -688.112976f, -80.261093f, 428.240814f } // left
};

float const _finalSplineOrientation = 0.070714f;

Position const brannMovePosition = { -685.316223f, -49.485359f, 427.607483f, 0.018864f };
G3D::Vector3 const goranMovePosition = { -688.524414f, -18.821848f, 427.918304f };
G3D::Vector3 const leftOfGoranPosition = { -688.957092f, -14.784967f, 427.979889f };
G3D::Vector3 const rightOfGoranPosition = { -688.215576f, -21.703346f, 427.874451f };

float const _finalGoranSplineOrientation = 0.061987f;

class npc_brann_ulduar : public CreatureScript
{
public:
    npc_brann_ulduar() : CreatureScript("npc_brann_ulduar") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        player->PlayerTalkClass->ClearMenus();
        InstanceScript* instance = creature->GetInstanceScript();

        if (!instance)
            return false;

        if (instance->GetData(TYPE_LEVIATHAN) == NOT_STARTED && !instance->GetData(DATA_ENTRANCE_EVENT_STARTED))
        {
            player->PlayerTalkClass->GetGossipMenu().AddMenuItem(BRANN_DEFAULT_GOSSIP_MENU, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            player->PlayerTalkClass->SendGossipMenu(BRANN_DEFAULT_EVENT_GOSSIP, creature->GetGUID());
        }
        else
            player->PlayerTalkClass->SendGossipMenu(BRANN_POST_EVENT_GOSSIP, creature->GetGUID());

        return true;
    }

    struct npc_brann_ulduarAI : public ScriptedAI
    {
        npc_brann_ulduarAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
            Reset();
        }

        void Reset() override
        {
            _running = false;
            events.Reset();
            _pentarusGUID = 0;
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }

        void sGossipSelect(Player* player, uint32 /*sender*/, uint32 action) override
        {
            if (!action)
            {
                if (instance && instance->GetData(TYPE_LEVIATHAN) == NOT_STARTED && !instance->GetData(DATA_ENTRANCE_EVENT_STARTED))
                    DoAction(ACTION_START_BRANN_EVENT);
                player->PlayerTalkClass->SendCloseGossip();
                _playerStarterGUID = player->GetGUID();
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!_running)
                return;

            events.Update(diff);

            while (auto eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BRANN_GATE_0:
                    {
                        Player* player = nullptr;
                        player = ObjectAccessor::GetPlayer(*me, _playerStarterGUID);

                        // Event was started by lorekeeper norgann, try getting guid of the person
                        // who started the event from his script
                        if (!player)
                        {
                            if (Creature* lorekeeper = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_LOREKEEPER_NORG_ENTRANCE)))
                                player = ObjectAccessor::GetPlayer(*me, lorekeeper->AI()->GetData64(DATA_LOREKEEPER_STARTER_GUID));
                        }

                        if (player)
                            Talk(BRANN_GATE_SAY_0, player);
                        else
                            Talk(BRANN_GATE_SAY_0);
                        events.ScheduleEvent(EVENT_BRANN_GATE_1, 7s);
                        break;
                    }
                    case EVENT_BRANN_GATE_1:
                        if (Creature* archmage = ObjectAccessor::GetCreature(*me, _pentarusGUID))
                            if (archmage->IsAIEnabled)
                                archmage->AI()->Talk(PENTARUS_GATE_SAY_0);
                        events.ScheduleEvent(EVENT_BRANN_GATE_2, 8s);
                        break;
                    case EVENT_BRANN_GATE_2:
                    {
                        std::vector<uint64> _vTemp;
                        Talk(BRANN_GATE_SAY_1);
                        if (Creature* battle = me->FindNearestCreature(NPC_KIRIN_TOR_BATTLE_MAGE, 5.0f))
                            _vTemp.push_back(battle->GetGUID());

                        if (Creature* mage = me->FindNearestCreature(NPC_KIRIN_TOR_MAGE, 5.0f))
                            _vTemp.push_back(mage->GetGUID());

                        if (Creature* pentarus = ObjectAccessor::GetCreature(*me, _pentarusGUID))
                        {
                            pentarus->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            _vTemp.push_back(pentarus->GetGUID());
                        }

                        for (auto i = 0; i < _vTemp.size(); ++i)
                        {
                            if (Creature* mobToMove = ObjectAccessor::GetCreature(*me, _vTemp.at(i)))
                            {
                                Movement::MoveSplineInit init(mobToMove);
                                init.MoveTo(RightSidePositions[i]);
                                init.SetFacing(_finalSplineOrientation);
                                init.SetWalk(true);
                                init.Launch();
                            }
                        }
                        Position pos(-808.954285f, -103.394058f, 429.843781f, 3.564962f);
                        if (Creature* engineer = me->FindNearestCreature(NPC_HIRED_ENGINEER_BRANN, 5.0f))
                            engineer->GetMotionMaster()->MovePoint(1, pos);

                        if (Creature* goran = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_GORAN_ENTRANCE)))
                        {
                            goran->GetMotionMaster()->Clear();
                            goran->GetMotionMaster()->MoveIdle();

                            bool moveMembersToTheLeft = true;

                            //! break formation, and move them to proper positions
                            CreatureGroup* formation = goran->GetFormation();
                            if (formation)
                            {
                                for (auto& creature : formation->GetMembers())
                                {
                                    if (!creature.first)
                                        continue;

                                    if (creature.first->GetGUID() == goran->GetGUID())
                                        continue;

                                    if (creature.first->GetFormation())
                                        formation->RemoveMember(creature.first);

                                    Movement::MoveSplineInit init(creature.first);
                                    if (moveMembersToTheLeft)
                                    {
                                        moveMembersToTheLeft = false;
                                        init.MoveTo(leftOfGoranPosition);
                                    }
                                    else
                                        init.MoveTo(rightOfGoranPosition);

                                    init.SetWalk(false);
                                    init.SetFacing(_finalGoranSplineOrientation);
                                    init.Launch();
                                }
                            }

                            Movement::MoveSplineInit init(goran);
                            init.SetFacing(0.123f);
                            init.MoveTo(goranMovePosition);
                            init.Launch();
                        }

                        events.ScheduleEvent(EVENT_BRANN_GATE_3, 10s);
                        break;
                    }
                    case EVENT_BRANN_GATE_3:
                    {
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovePoint(1, brannMovePosition);
                        events.ScheduleEvent(EVENT_BRANN_GATE_4, 10s);
                        break;
                    }
                    case EVENT_BRANN_GATE_4:
                    {
                        if (Creature* pentarus = ObjectAccessor::GetCreature(*me, _pentarusGUID))
                            if (pentarus->IsAIEnabled)
                                pentarus->AI()->Talk(PENTARUS_GATE_SAY_1);

                        events.ScheduleEvent(EVENT_BRANN_GATE_5, 8s);
                        break;
                    }
                    case EVENT_BRANN_GATE_5:
                    {
                        Talk(BRANN_GATE_SAY_2);
                        events.ScheduleEvent(EVENT_BRANN_GATE_6, 8s);
                        break;
                    }
                    case EVENT_BRANN_GATE_6:
                    {
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        if (Creature* pentarus = ObjectAccessor::GetCreature(*me, _pentarusGUID))
                            pentarus->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

                        instance->SetData(DATA_VEHICLE_SPAWN, VEHICLE_POS_START);

                        if (GameObject* go = ObjectAccessor::GetGameObject(*me, instance->GetData64(DATA_STARTING_BARRIER)))
                            go->Delete();

                        if (Creature* trigger = me->FindNearestCreature(NPC_ULDUAR_SHIELD_BUNNY, 10.0f))
                            trigger->CastSpell((Unit*)nullptr, SPELL_ARCANE_EXPLOSION_MASS, true);

                        std::list<Creature*> battleMages;
                        me->GetCreatureListWithEntryInGrid(battleMages, NPC_KIRIN_TOR_BATTLE_MAGE, 50.0f);
                        for (auto creature : battleMages)
                            if (creature && creature->IsCasting())
                                creature->CastStop();
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void DoAction(int32 param) override
        {
            if (!instance)
                return;

            if (instance->GetData(DATA_ENTRANCE_EVENT_STARTED) && param != ACTION_START_NORGANNON_BRANN)
                return;

            // deactivate towers, easy mode
            if (param != ACTION_START_NORGANNON_BRANN)
            {
                instance->ProcessEvent(NULL, EVENT_TOWER_OF_STORM_DESTROYED);
                instance->ProcessEvent(NULL, EVENT_TOWER_OF_FROST_DESTROYED);
                instance->ProcessEvent(NULL, EVENT_TOWER_OF_FLAMES_DESTROYED);
                instance->ProcessEvent(NULL, EVENT_TOWER_OF_LIFE_DESTROYED);
            }

            if (Creature* cr = me->FindNearestCreature(NPC_ARCHMAGE_PENTARUS, 50.0f, true))
                _pentarusGUID = cr->GetGUID();

            instance->SetData(DATA_ENTRANCE_EVENT_STARTED, DATA_ENTRANCE_EVENT_STARTED);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            _running = true;
            events.ScheduleEvent(EVENT_BRANN_GATE_0, 1s);
        }
    private:
        uint64 _pentarusGUID;
        uint64 _playerStarterGUID;
        EventMap events;
        InstanceScript* instance;
        bool _running;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_brann_ulduarAI(creature);
    }
};

class npc_brann_radio : public CreatureScript
{
public:
    npc_brann_radio() : CreatureScript("npc_brann_radio") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_brann_radioAI (pCreature);
    }

    struct npc_brann_radioAI : public NullCreatureAI
    {
        npc_brann_radioAI(Creature* c) : NullCreatureAI(c)
        {
            _lock = (me->GetInstanceScript() && me->GetInstanceScript()->GetData(TYPE_LEVIATHAN) > NOT_STARTED);
            _helpLock = _lock;
        }

        bool _lock;
        bool _helpLock;

        void Reset()
        {
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void Say(const char* text)
        {
            WorldPacket data;
            ChatHandler::BuildChatPacket(data, CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, me, NULL, text);
            me->SendMessageToSetInRange(&data, 100.0f, true);
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!_lock)
            {
                if (who->GetTypeId() != TYPEID_PLAYER && !who->IsVehicle())
                    return;

                // MIMIRON
                if (me->GetDistance2d(-81.9207f, 111.432f) < 5.0f)
                {
                    if (me->GetDistance2d(who) <= 60.0f && who->GetPositionZ() > 430.0f)
                    {
                        Say("This generator powers Mimiron's Gaze. In moments, it can turn earth to ash, stone to magma--we cannot let it reach full power!");
                        me->PlayDirectSound(RSOUND_MIMIRON);
                        _lock = true;
                    }
                }
                // FREYA
                else if (me->GetDistance2d(-221.475f, -271.087f) < 5.0f)
                {
                    if (me->GetDistance2d(who) <= 60.0f && who->GetPositionZ() < 380.0f)
                    {
                        Say("You're approaching the tower of Freya. It contains the power to turn barren wastelands into jungles teeming with life overnight");
                        me->PlayDirectSound(RSOUND_FREYA);
                        _lock = true;
                    }
                }
                // STATIONS
                else if (me->GetDistance2d(73.8978f, -29.3306f) < 5.0f)
                {
                    if (me->GetDistance2d(who) <= 40.0f)
                    {
                        Say("It appears you are near a repair station. Drive your vehicle on to the platform and it should be automatically repaired.");
                        me->PlayDirectSound(RSOUND_STATION);
                        _lock = true;
                    }
                }
                // HODIR
                else if (me->GetDistance2d(68.7679f, -325.026f) < 5.0f)
                {
                    if (me->GetDistance2d(who) <= 40.0f)
                    {
                        Say("This tower powers the hammer of Hodir. It is said to have the power to turn entire armies to ice!");
                        me->PlayDirectSound(RSOUND_HODIR);
                        _lock = true;
                    }
                }
                // THORIM
                else if (me->GetDistance2d(174.442f, 345.679f) < 5.0f)
                {
                    if (me->GetDistance2d(who) <= 60.0f)
                    {
                        Say("Aaaah, the tower of Krolmir. It is said that the power of Thorim has been used only once. And that it turned an entire continent to dust...");
                        me->PlayDirectSound(RSOUND_THORIM);
                        _lock = true;
                    }
                }
                // COME A BIT CLOSER
                else if (me->GetDistance2d(-508.898f, -32.9631f) < 5.0f)
                {
                    if (who->GetPositionX() >= -480.0f)
                    {
                        Say("There are four generators powering the defense structures. If you sabotage the generators, the missile attacks will stop!");
                        me->PlayDirectSound(RSOUND_GENERATORS);
                        _lock = true;
                    }
                }
            }
        }
    };
};

enum beaconEnum
{
    EVENT_SPAWN_DEFENDER                = 1,
    EVENT_CHECK_FOR_NEARBY_PLAYERS      = 2
};

class npc_storm_beacon_spawn : public CreatureScript
{
public:
    npc_storm_beacon_spawn() : CreatureScript("npc_storm_beacon_spawn") { }

    struct npc_storm_beacon_spawnAI : public ScriptedAI
    {
        npc_storm_beacon_spawnAI(Creature* creature) : ScriptedAI(creature) { }

        void DamageTaken(Unit* /*who*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
        {
            damage = 0;
        }

        void Reset() override
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            events.Reset();
            _activated = false;
        }

        bool IsLeviathanVehicle(Unit* who)
        {
            if (!who)
                return false;

            switch (who->GetEntry())
            {
                case NPC_SALVAGED_DEMOLISHER:
                case NPC_SALVAGED_SIEGE_ENGINE:
                case NPC_VEHICLE_CHOPPER:
                    return true;
                default:
                    return false;
            }
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (who && !_activated && who->IsWithinDist(me, 70.0f))
            {
                if (who->ToPlayer() && who->ToPlayer()->IsGameMaster())
                    return;

                if (who->ToCreature() && !IsLeviathanVehicle(who))
                    return;

                _activated = true;
                events.ScheduleEvent(EVENT_SPAWN_DEFENDER, 1s);
                events.ScheduleEvent(EVENT_CHECK_FOR_NEARBY_PLAYERS, 10s);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!_activated)
                return;

            events.Update(diff);

            while (auto eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SPAWN_DEFENDER:
                    {
                        float x, y, z;
                        me->GetClosePoint(x, y, z, me->GetObjectSize() / 3, 9.0f);
                        Position pos(x, y, z, me->GetOrientation());
                        if (Creature* cr = me->SummonCreature(NPC_DEFENDER_GENERATED, pos, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 25000))
                        {
                            if (cr->IsAIEnabled)
                                cr->AI()->DoZoneInCombat(cr, 200.0f);
                        }
                        events.Repeat(2s);
                        break;
                    }
                    case EVENT_CHECK_FOR_NEARBY_PLAYERS:
                    {
                        //! if we find a player nearby then continue the check in 10s
                        //! else reset the entire script
                        if (Player* player = GetPlayerAtMinimumRange(150.f))
                            events.Repeat(10s);
                        else
                            Reset();
                        break;
                    }
                }
            }
        }
    private:
        EventMap events;
        bool _activated;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_storm_beacon_spawnAI(creature);
    }

};

class boss_flame_leviathan_safety_container : public CreatureScript
{
public:
    boss_flame_leviathan_safety_container() : CreatureScript("boss_flame_leviathan_safety_container") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_flame_leviathan_safety_containerAI (pCreature);
    }

    struct boss_flame_leviathan_safety_containerAI : public NullCreatureAI
    {
        boss_flame_leviathan_safety_containerAI(Creature *c) : NullCreatureAI(c)
        {
            _allowTimer = 0;
        }

        uint32 _allowTimer;

        void MovementInform(uint32 type, uint32 id)
        {
            if (id == me->GetEntry())
            {
                if (Creature* liquid = me->SummonCreature(NPC_LIQUID, *me))
                {
                    liquid->CastSpell(liquid, SPELL_LIQUID_PYRITE, true);
                    liquid->CastSpell(liquid, SPELL_DUST_CLOUD_IMPACT, true);
                    liquid->DespawnOrUnsummon(60000);
                }

                me->DespawnOrUnsummon(1);
            }
        }

        void UpdateAI(uint32 diff)
        {
            _allowTimer += diff;
            if (_allowTimer >= 5000 && !me->GetVehicle() && me->GetMotionMaster()->GetCurrentMovementGeneratorType() != POINT_MOTION_TYPE)
            {
                float x, y, z;
                me->GetPosition(x, y, z);
                z = me->GetMap()->GetHeight(me->GetPhaseMask(), x, y, z);
                me->GetMotionMaster()->MovePoint(me->GetEntry(), x, y, z);
                me->SetPosition(x, y, z, 0);
            }
        }
    };
};

class npc_mechanolift : public CreatureScript
{
public:
    npc_mechanolift() : CreatureScript("npc_mechanolift") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_mechanoliftAI (pCreature);
    }

    struct npc_mechanoliftAI : public NullCreatureAI
    {
        npc_mechanoliftAI(Creature *c) : NullCreatureAI(c)
        {
            me->SetSpeedRate(MOVE_RUN, rand_norm()+0.5f);
        }

        int32 _startTimer;
        uint32 _evadeTimer;

        void Reset()
        {
            _startTimer = urand(1,5000);
            _evadeTimer = 0;
        }

        void UpdateAI(uint32 diff)
        {
            if (_startTimer)
            {
                _startTimer -= diff;
                if (_startTimer <= 0)
                {
                    me->GetMotionMaster()->MovePath(3000000+urand(0,11), true);
                    _startTimer = 0;
                }
            }

            _evadeTimer += diff;
            if (_evadeTimer >= 10000)
            {
                _EnterEvadeMode();
                _evadeTimer = 0;
            }
        }
    };
};

class go_ulduar_tower : public GameObjectScript
{
    public:
        go_ulduar_tower() : GameObjectScript("go_ulduar_tower") { }

        void OnDestroyed(GameObject* go, Player* /*player*/)
        {
            std::list<Creature*> _triggerList;
            go->GetCreatureListWithEntryInGrid(_triggerList, NPC_ULDUAR_GAUNTLET_GENERATOR, 30.f);
            for (auto& creature : _triggerList)
            {
                if (creature && creature->IsAlive())
                    creature->DisappearAndDie();
            }
        }
};

std::vector<std::string> LoadCatapultTexts =
{
    { "I am ready, let's do this!" },
    { "I hope I don't chip my nails..." },
    { "Ready, Steady, Go!" },
    { "Fire in the hole!" }
};

class spell_load_into_catapult : public SpellScriptLoader
{
    enum Spells
    {
        SPELL_PASSENGER_LOADED = 62340,
    };

    public:
        spell_load_into_catapult() : SpellScriptLoader("spell_load_into_catapult") { }

        class spell_load_into_catapult_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_load_into_catapult_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* owner = GetOwner()->ToUnit();
                Unit* caster = GetCaster();

                if (owner && caster)
                {
                    std::string loadedText = Trinity::Containers::SelectRandomContainerElement(LoadCatapultTexts);
                    caster->MonsterSay(loadedText.c_str(), 0, nullptr);
                    owner->CastSpell(owner, SPELL_PASSENGER_LOADED, true);
                }
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* owner = GetOwner()->ToUnit();
                if (!owner)
                    return;

                owner->RemoveAurasDueToSpell(SPELL_PASSENGER_LOADED);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_load_into_catapult_AuraScript::OnApply, EFFECT_0, SPELL_AURA_CONTROL_VEHICLE, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_load_into_catapult_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_CONTROL_VEHICLE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        class spell_load_into_catapult_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_load_into_catapult_SpellScript);

            SpellCastResult CheckCast()
            {
                if (!GetCaster()->IsPlayer())
                    return SPELL_FAILED_DONT_REPORT;

                //! We're getting the seat we're currently on
                //! so in theory we're getting mechanical seat on demolisher
                Unit* vehicleBase = GetCaster()->GetVehicleBase();
                if (!vehicleBase)
                    return SPELL_FAILED_DONT_REPORT;

                //! Try getting vehicleBase of mechanical seat
                Unit* vehicleBaseMain = vehicleBase->GetVehicleBase();
                if (!vehicleBaseMain)
                    return SPELL_FAILED_DONT_REPORT;

                //! Now try getting vehicle kit of main vehicle (demolisher) that the mechanic seat is placed upon
                Vehicle* vehicle = vehicleBaseMain->GetVehicleKit();
                if (!vehicle)
                    return SPELL_FAILED_DONT_REPORT;

                //! do not allow the spell to be casted if catapult is occupied currently
                if (vehicle->GetPassenger(3))
                    return SPELL_FAILED_DONT_REPORT;

                return SPELL_CAST_OK;
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_load_into_catapult_SpellScript::CheckCast);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_load_into_catapult_AuraScript();
        }

        SpellScript* GetSpellScript() const override
        {
            return new spell_load_into_catapult_SpellScript();
        }
};

class spell_auto_repair : public SpellScriptLoader
{
    enum Spells
    {
        SPELL_AUTO_REPAIR = 62705,
    };

    public:
        spell_auto_repair() : SpellScriptLoader("spell_auto_repair") {}

        class spell_auto_repair_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_auto_repair_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                std::list<WorldObject*> tmplist;
                for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    if (!(*itr)->ToUnit()->HasAura(SPELL_AUTO_REPAIR))
                        tmplist.push_back(*itr);

                 targets.clear();
                 for (std::list<WorldObject*>::iterator itr = tmplist.begin(); itr != tmplist.end(); ++itr)
                     targets.push_back(*itr);
            }

            void HandleScript(SpellEffIndex /*eff*/)
            {
                Vehicle* vehicle = GetHitUnit()->GetVehicleKit();
                if (!vehicle)
                    return;

                Player* driver = vehicle->GetPassenger(0) ? vehicle->GetPassenger(0)->ToPlayer() : NULL;
                if (!driver)
                    return;

                driver->MonsterTextEmote("Automatic repair sequence initiated.", driver, true);

                // Actually should/could use basepoints (100) for this spell effect as percentage of health, but oh well.
                vehicle->GetBase()->SetFullHealth();

                // Achievement
                if (InstanceScript* instance = vehicle->GetBase()->GetInstanceScript())
                    instance->SetData(DATA_UNBROKEN_ACHIEVEMENT, 0);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_auto_repair_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_DEST_AREA_ENTRY);
                OnEffectHitTarget += SpellEffectFn(spell_auto_repair_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_auto_repair_SpellScript();
        }
};

class spell_systems_shutdown : public SpellScriptLoader
{
    public:
        spell_systems_shutdown() : SpellScriptLoader("spell_systems_shutdown") { }

        class spell_systems_shutdown_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_systems_shutdown_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Creature* owner = GetOwner()->ToCreature();
                if (!owner)
                    return;

                owner->SetControlled(true, UNIT_STATE_STUNNED);
                owner->RemoveAurasDueToSpell(SPELL_GATHERING_SPEED);
                if (Vehicle* veh = owner->GetVehicleKit())
                    if (Unit* cannon = veh->GetPassenger(SEAT_CANNON))
                        cannon->GetAI()->DoAction(ACTION_DELAY_CANNON);
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Creature* owner = GetOwner()->ToCreature();
                if (!owner)
                    return;

                owner->SetControlled(false, UNIT_STATE_STUNNED);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_systems_shutdown_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_systems_shutdown_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_systems_shutdown_AuraScript();
        }
};

class FlameLeviathanPursuedTargetSelector
{
    enum Area
    {
        AREA_FORMATION_GROUNDS = 4652,
    };

    public:
        explicit FlameLeviathanPursuedTargetSelector(Unit* unit) : _me(unit) {};

        bool operator()(WorldObject* target) const
        {
            //! No players, only vehicles (todo: check if blizzlike)
            Creature* creatureTarget = target->ToCreature();
            if (!creatureTarget)
                return true;

            //! NPC entries must match
            if (creatureTarget->GetEntry() != NPC_SALVAGED_DEMOLISHER && creatureTarget->GetEntry() != NPC_SALVAGED_SIEGE_ENGINE)
                return true;

            //! NPC must be a valid vehicle installation
            Vehicle* vehicle = creatureTarget->GetVehicleKit();
            if (!vehicle)
                return true;

            //! Entity needs to be in appropriate area
            if (target->GetAreaId() != AREA_FORMATION_GROUNDS)
                return true;

            //! Vehicle must be in use by player
            bool playerFound = false;
            for (SeatMap::const_iterator itr = vehicle->Seats.begin(); itr != vehicle->Seats.end() && !playerFound; ++itr)
                if (IS_PLAYER_GUID(itr->second.Passenger.Guid))
                    playerFound = true;

            return !playerFound;
        }

    private:
        Unit const* _me;
};

class spell_pursue : public SpellScriptLoader
{
    public:
        spell_pursue() : SpellScriptLoader("spell_pursue") {}

        class spell_pursue_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pursue_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(FlameLeviathanPursuedTargetSelector(GetCaster()));

                if (!targets.empty())
                {
                    //! In the end, only one target should be selected
                    WorldObject* _target = Trinity::Containers::SelectRandomContainerElement(targets);
                    targets.clear();
                    if (_target)
                        targets.push_back(_target);
                }
            }


            void HandleScript(SpellEffIndex /*eff*/)
            {
                Creature* target = GetHitCreature();
                Unit* caster = GetCaster();
                if (!target || !caster)
                    return;

                caster->getThreatManager().resetAllAggro();
                caster->GetAI()->AttackStart(target);    // Chase target
                caster->AddThreat(target, 10000000.0f);
                if (target->GetVehicleKit())
                    for (SeatMap::const_iterator itr = target->GetVehicleKit()->Seats.begin(); itr != target->GetVehicleKit()->Seats.end(); ++itr)
                        if (IS_PLAYER_GUID(itr->second.Passenger.Guid))
                        {
                            caster->MonsterTextEmote("Flame Leviathan pursues $N.", ObjectAccessor::GetPlayer(*caster, itr->second.Passenger.Guid), true);
                            return;
                        }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pursue_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_pursue_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_pursue_SpellScript();
        }
};

class spell_vehicle_throw_passenger : public SpellScriptLoader
{
    public:
        spell_vehicle_throw_passenger() : SpellScriptLoader("spell_vehicle_throw_passenger") {}

        class spell_vehicle_throw_passenger_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_vehicle_throw_passenger_SpellScript);
            void HandleScript()
            {
                Spell* baseSpell = GetSpell();
                SpellCastTargets targets = baseSpell->m_targets;
                if (Vehicle* vehicle = GetCaster()->GetVehicleKit())
                    if (Unit* passenger = vehicle->GetPassenger(3))
                    {
                        // use 99 because it is 3d search
                        std::list<WorldObject*> targetList;
                        Trinity::WorldObjectSpellAreaTargetCheck check(99, GetExplTargetDest(), GetCaster(), GetCaster(), GetSpellInfo(), TARGET_CHECK_DEFAULT, NULL);
                        Trinity::WorldObjectListSearcher<Trinity::WorldObjectSpellAreaTargetCheck> searcher(GetCaster(), targetList, check);
                        GetCaster()->GetMap()->VisitAll(GetCaster()->m_positionX, GetCaster()->m_positionY, 99, searcher);
                        float minDist = 99 * 99;
                        Unit* target = NULL;
                        for (std::list<WorldObject*>::iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                        {
                            if (Unit* unit = (*itr)->ToUnit())
                                if (unit->GetEntry() == NPC_SEAT)
                                    if (Vehicle* seat = unit->GetVehicleKit())
                                        if (!seat->GetPassenger(0))
                                            if (Unit* device = seat->GetPassenger(2))
                                                if (!device->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                                                {
                                                    float dist = unit->GetExactDistSq(targets.GetDstPos());
                                                    if (dist < minDist)
                                                    {
                                                        minDist = dist;
                                                        target = unit;
                                                    }
                                                }
                        }
                        if (target && target->IsWithinDist2d(targets.GetDstPos(), GetSpellInfo()->Effects[EFFECT_0].CalcRadius() * 8)) // now we use *2 because the location of the seat is not correct
                        {
                            passenger->ExitVehicle();
                            passenger->EnterVehicle(target, 0);
                        }
                        else
                        {
                            passenger->ExitVehicle();
                            float x, y, z;
                            targets.GetDstPos()->GetPosition(x, y, z);
                            passenger->GetMotionMaster()->MoveJump(x, y, z, targets.GetSpeedXY(), targets.GetSpeedZ());
                        }
                    }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_vehicle_throw_passenger_SpellScript::HandleScript);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_vehicle_throw_passenger_SpellScript();
        }
};

class spell_tar_blaze : public SpellScriptLoader
{
    public:
        spell_tar_blaze() : SpellScriptLoader("spell_tar_blaze") { }

        class spell_tar_blaze_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_tar_blaze_AuraScript);

            void OnPeriodic(AuraEffect const* aurEff)
            {
                GetUnitOwner()->CastSpell((Unit*)NULL, GetSpellInfo()->Effects[aurEff->GetEffIndex()].TriggerSpell, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_tar_blaze_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_tar_blaze_AuraScript();
        }
};

class spell_vehicle_grab_pyrite : public SpellScriptLoader
{
    public:
        spell_vehicle_grab_pyrite() : SpellScriptLoader("spell_vehicle_grab_pyrite") {}

        class spell_vehicle_grab_pyrite_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_vehicle_grab_pyrite_SpellScript);
            void HandleScript(SpellEffIndex effIndex)
            {
                if (Unit* target = GetHitUnit())
                {
                    if (!target->HasAura(62495))
                        return;

                    if (Unit* seat = GetCaster()->GetVehicleBase())
                    {
                        if (Vehicle* vSeat = seat->GetVehicleKit())
                        {
                            //! spell has delay, vehicle base can change before the spell hits
                            //! and if it changes to demolisher then he will drop the turret out of the entire vehicle
                            //! just make sure its actually turret, some visuals might be lost in edge cases
                            //! but regenerating power will still work
                            if (vSeat->GetCreatureEntry() == NPC_SALVAGED_DEMOLISHER_TURRET)
                            {
                                if (Unit* pyrite = vSeat->GetPassenger(1))
                                    pyrite->ExitVehicle();
                            }
                        }

                        if (Unit* parent = seat->GetVehicleBase())
                        {
                            GetCaster()->CastSpell(parent, 62496 /*SPELL_ADD_PYRITE*/, true);
                            target->CastSpell(seat, GetEffectValue());

                            if (target->GetTypeId() == TYPEID_UNIT)
                                target->ToCreature()->DespawnOrUnsummon(1300);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_vehicle_grab_pyrite_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_vehicle_grab_pyrite_SpellScript();
        }
};

class spell_vehicle_chopper_grab_pyrite : public SpellScriptLoader
{
public:
    spell_vehicle_chopper_grab_pyrite() : SpellScriptLoader("spell_vehicle_chopper_grab_pyrite") {}

    class spell_vehicle_chopper_grab_pyrite_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_vehicle_chopper_grab_pyrite_SpellScript);
        void HandleScript(SpellEffIndex effIndex)
        {
            if (Unit* target = GetHitUnit())
                if (Unit* seat = GetCaster()->GetVehicleBase())
                    if (Vehicle* chopper = seat->GetVehicleKit())
                        if (chopper->HasEmptySeat(1))
                            target->EnterVehicle(seat, 1);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_vehicle_chopper_grab_pyrite_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_vehicle_chopper_grab_pyrite_SpellScript();
    }
};

class spell_vehicle_circuit_overload : public SpellScriptLoader
{
    public:
        spell_vehicle_circuit_overload() : SpellScriptLoader("spell_vehicle_circuit_overload") { }

        class spell_vehicle_circuit_overload_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_vehicle_circuit_overload_AuraScript);

            void OnPeriodic(AuraEffect const* aurEff)
            {
                /*
                if (Unit* target = GetTarget())
                    if (int(target->GetAppliedAuras().count(SPELL_OVERLOAD_CIRCUIT)) >= (target->GetMap()->Is25ManRaid() ? 4 : 2))
                    {
                        target->CastSpell(target, SPELL_SYSTEMS_SHUTDOWN, true);
                        target->RemoveAurasDueToSpell(SPELL_OVERLOAD_CIRCUIT);
                    }
                */
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_vehicle_circuit_overload_AuraScript::OnPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_vehicle_circuit_overload_AuraScript();
        }
};

class spell_orbital_supports : public SpellScriptLoader
{
    public:
        spell_orbital_supports() : SpellScriptLoader("spell_orbital_supports") { }

        class spell_orbital_supports_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_orbital_supports_AuraScript);

            bool CheckAreaTarget(Unit* target)
            {
                return target->GetEntry() == NPC_LEVIATHAN;
            }
            void Register()
            {
                DoCheckAreaTarget += AuraCheckAreaTargetFn(spell_orbital_supports_AuraScript::CheckAreaTarget);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_orbital_supports_AuraScript();
        }
};

uint32 const SPELL_PARACHUTE_SMOKE_TRAIL = 61242;

class spell_thorims_hammer : public SpellScriptLoader
{
    public:
        spell_thorims_hammer() : SpellScriptLoader("spell_thorims_hammer") { }

        class spell_thorims_hammer_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_thorims_hammer_SpellScript);

            void RecalculateDamage(SpellEffIndex effIndex)
            {
                if (!GetHitUnit() || effIndex == EFFECT_1)
                {
                    PreventHitDefaultEffect(effIndex);
                    return;
                }

                //if (GetHitUnit()->HasAura(SPELL_SMOKE_TRAIL) || GetHitUnit()->HasAura(SPELL_PARACHUTE_SMOKE_TRAIL))
                //{
                    //PreventHitDefaultEffect(effIndex);
                    //return;
                //}

                float dist = GetHitUnit()->GetExactDist2d(GetCaster());
                if (dist <= 7.0f)
                    SetHitDamage(GetSpellInfo()->Effects[EFFECT_1].CalcValue());
                else
                {
                    dist -= 6.0f;
                    SetHitDamage(int32(GetSpellInfo()->Effects[EFFECT_1].CalcValue() / std::max(dist, 1.0f)));
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_thorims_hammer_SpellScript::RecalculateDamage, EFFECT_ALL, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_thorims_hammer_SpellScript();
        }
};

class spell_shield_generator : public SpellScriptLoader
{
    public:
        spell_shield_generator() : SpellScriptLoader("spell_shield_generator") { }

        class spell_shield_generator_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_shield_generator_AuraScript);

            uint32 absorbPct;

            bool Load()
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                // Set absorbtion amount to unlimited
                amount = -1;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_shield_generator_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_shield_generator_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_shield_generator_AuraScript();
        }
};


class spell_demolisher_ride_vehicle : public SpellScriptLoader
{
    public:
        spell_demolisher_ride_vehicle() : SpellScriptLoader("spell_demolisher_ride_vehicle") {}

        class spell_demolisher_ride_vehicle_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_demolisher_ride_vehicle_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return SPELL_CAST_OK;

                Unit* target = this->GetExplTargetUnit();
                if (!target || target->GetEntry() != NPC_SALVAGED_DEMOLISHER)
                    return SPELL_FAILED_DONT_REPORT;

                Vehicle* veh = target->GetVehicleKit();
                if (veh && veh->GetPassenger(0))
                {
                    if (Unit* target2 = veh->GetPassenger(1))
                    {
                        if (Vehicle* veh2 = target2->GetVehicleKit())
                        {
                            if (!veh2->GetPassenger(0))
                                target2->HandleSpellClick(GetCaster());

                            return SPELL_FAILED_DONT_REPORT;
                        }
                    }
                }
                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_demolisher_ride_vehicle_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_demolisher_ride_vehicle_SpellScript();
        }
};

class achievement_flame_leviathan_towers : public AchievementCriteriaScript
{
    public:
        achievement_flame_leviathan_towers(char const* name, uint32 count) : AchievementCriteriaScript(name),
            _towerCount(count)
        {
        }

        bool OnCheck(Player* player, Unit* target /*Flame Leviathan*/)
        {
            return target && _towerCount <= target->GetAI()->GetData(DATA_GET_TOWER_COUNT);
        }

    private:
        uint32 const _towerCount;
};

class achievement_flame_leviathan_shutout : public AchievementCriteriaScript
{
    public:
        achievement_flame_leviathan_shutout() : AchievementCriteriaScript("achievement_flame_leviathan_shutout") {}

        bool OnCheck(Player* player, Unit* target /*Flame Leviathan*/)
        {
            if (target)
                if (target->GetAI()->GetData(DATA_GET_SHUTDOWN))
                    return true;
            return false;
        }
};

class achievement_flame_leviathan_garage : public AchievementCriteriaScript
{
    public:
        achievement_flame_leviathan_garage(char const* name, uint32 entry1, uint32 entry2) : AchievementCriteriaScript(name),
            _entry1(entry1), _entry2(entry2)
        {
        }

        bool OnCheck(Player* player, Unit*)
        {
            if (Vehicle* vehicle = player->GetVehicle())
                if (vehicle->GetCreatureEntry() == _entry1 || vehicle->GetCreatureEntry() == _entry2)
                    return true;
            return false;
        }

    private:
        uint32 const _entry1;
        uint32 const _entry2;
};

class achievement_flame_leviathan_unbroken : public AchievementCriteriaScript
{
    public:
        achievement_flame_leviathan_unbroken() : AchievementCriteriaScript("achievement_flame_leviathan_unbroken") {}

        bool OnCheck(Player* player, Unit*)
        {
            if (player->GetInstanceScript())
                if (player->GetInstanceScript()->GetData(DATA_UNBROKEN_ACHIEVEMENT))
                    return true;
            return false;
        }
};

class npc_ward_of_life : public CreatureScript
{
public:
    npc_ward_of_life() : CreatureScript("npc_ward_of_life") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ward_of_lifeAI(pCreature);
    }

    struct npc_ward_of_lifeAI : public ScriptedAI
    {
        npc_ward_of_lifeAI(Creature *c) : ScriptedAI(c) { }

        uint32 _lashTimer;

        void Reset() { _lashTimer = 2000; }

        bool CanAIAttack(Unit const* who) const
        {
            if (who->GetAreaId() != 4652)
                return false;

            if (who->GetTypeId() == TYPEID_PLAYER)
                return false;

            return true;
        }

        void AttackStart(Unit* who)
        {
            if (CanAIAttack(who))
                ScriptedAI::AttackStart(who);
        }

        void JustDied(Unit* /*who*/) { me->DisappearAndDie(); }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (_lashTimer <= diff)
            {
                DoCast(me->GetVictim(), SPELL_WARD_OF_LIFE_LASH);
                _lashTimer = 2000;
            }
            else _lashTimer -= diff;
        }
    };
};

struct npc_liquid_piryte_flame_leviathanAI : public ScriptedAI
{
    npc_liquid_piryte_flame_leviathanAI(Creature* creature) : ScriptedAI(creature)
    {
        me->CastSpell(me, 62495, true);
    }

    void EnterEvadeMode() {}

    void SpellHit(Unit* /*caster*/, SpellInfo const* spellInfo) override
    {
        if (spellInfo->Id == SPELL_PYRITE_RIDE_VEHICLE)
        {
            me->DespawnOrUnsummon(15s);
            me->RemoveAurasDueToSpell(SPELL_LIQUID_PYRITE);
        }
    }
};

struct npc_flame_leviathan_vehicles_AI : public ScriptedAI
{
    npc_flame_leviathan_vehicles_AI(Creature* creature) : ScriptedAI(creature)
    {
        me->DisableChangeAI(true);
        me->SetReactState(REACT_PASSIVE);
        _counter = 0;
    }

    void EnterEvadeMode() override { }
    void AttackStart(Unit* who) override { }
    void Reset() override { }
    void OnCharmed(bool apply) override { }

    void SpellHit(Unit* caster, const SpellInfo* spellInfo) override
    {
        if (spellInfo->Id == SPELL_MACHINE_FLAMES_TRIGGERED)
            ++_counter;
    }

    uint32 GetData(uint32 data) const override
    {
        if (data == DATA_GET_FLAMES_HIT_COUNT)
            return _counter;

        return 0;
    }

    //! attack vehicleBase instead of turret
    void EnterCombat(Unit* who) override
    {
        if (who->GetTypeId() == TYPEID_UNIT && who->GetEntry() == NPC_MECHANOLIFT)
            return;

        if (me->GetEntry() == NPC_SALVAGED_SIEGE_ENGINE_TURRET || me->GetEntry() == NPC_SALVAGED_DEMOLISHER_TURRET)
            if (who->GetTypeId() == TYPEID_UNIT && me->GetVehicleBase())
                who->ToCreature()->AI()->AttackStart(me->GetVehicleBase());
    }

    //! redirect all threat to vehicle base
    void DamageDealt(Unit* victim, uint32& damage, DamageEffectType /*damageType*/) override
    {
        if (me->GetEntry() == NPC_SALVAGED_SIEGE_ENGINE_TURRET || me->GetEntry() == NPC_SALVAGED_DEMOLISHER_TURRET)
            if (victim && victim->GetTypeId() == TYPEID_UNIT && victim->GetEntry() != NPC_MECHANOLIFT && me->GetVehicleBase())
                victim->ToCreature()->AddThreat(me->GetVehicleBase(), damage + 100);
    }

    void PassengerBoarded(Unit* who, int8 seatId, bool apply) override
    {
        if (!apply)
            _counter = 0;

        if (me->GetEntry() != NPC_SALVAGED_SIEGE_ENGINE)
            return;

        if (who->IsPlayer())
        {
            if (apply)
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
            else
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
        }
        else if (who->GetEntry() == NPC_SALVAGED_SIEGE_ENGINE_TURRET)
            who->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }
private:
    uint32 _counter;
};

class spell_flames_flame_leviathan_fury_remover_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_flames_flame_leviathan_fury_remover_SpellScript);

    void HandleHit(SpellEffIndex effIndex)
    {
        if (!GetHitUnit())
            return;

        if (GetHitUnit()->ToCreature())
        {
            if (GetHitUnit()->ToCreature()->GetEntry() == NPC_POOL_OF_TAR_LEVIATHAN)
                SetHitDamage(0);
        }

        if (!GetHitUnit()->HasAura(SPELL_HODIRS_FURY_AURA_FREEZE))
            return;

        if (GetHitUnit()->IsPlayer())
            GetHitUnit()->RemoveAurasDueToSpell(SPELL_HODIRS_FURY_AURA_FREEZE);
        else if (GetHitUnit()->ToCreature())
        {
            switch (GetHitUnit()->GetEntry())
            {
                case NPC_SALVAGED_DEMOLISHER:
                case NPC_SALVAGED_SIEGE_ENGINE:
                case NPC_VEHICLE_CHOPPER:
                {
                    if (Creature* veh = GetHitUnit()->ToCreature())
                    {
                        if (veh->IsAIEnabled)
                            if (veh->AI()->GetData(DATA_GET_FLAMES_HIT_COUNT) >= 4)
                            {
                                veh->RemoveAurasDueToSpell(SPELL_HODIRS_FURY_AURA_FREEZE);
                                if (veh->GetVehicleKit())
                                    for (int i = 0; i < 8; i++)
                                        if (Unit* passenger = veh->GetVehicleKit()->GetPassenger(i))
                                            passenger->RemoveAurasDueToSpell(SPELL_HODIRS_FURY_AURA_FREEZE);
                                if (veh->GetVehicleBase())
                                    veh->GetVehicleBase()->RemoveAurasDueToSpell(SPELL_HODIRS_FURY_AURA_FREEZE);
                            }
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_flames_flame_leviathan_fury_remover_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

/* Post Flame Leviathan Event */
enum FL_EVENT
{
    SPELL_SIMPLE_TELEPORT_EFFECT_FL     = 12980,
    NPC_BRANN_FLYING_MACHINE            = 34120,
    NPC_ARCHMAGE_RHYDIAN_FL             = 33696,
    SPELL_KIRIN_TOR_BATTLE_CHANNEL      = 39550,
    SPELL_BRANN_RIDE_VEHICLE_FL         = 43671,
    NPC_EXPEDITION_ENGINEER_FL          = 34145,
    NPC_EXPEDITION_MERCENARY_FL         = 34144,
    GO_PORTAL_TO_DALARAN_FL             = 194481,
    NPC_KIRIN_TOR_MAGE_FL               = 33672,
    NPC_KIRIN_TOR_BATTLE_MAGE_FL        = 33662,

    // Bran bronzebeard talks
    SAY_BRAN_0                          = 0,
    SAY_BRAN_1                          = 1,
    SAY_BRAN_2                          = 2,
    SAY_BRAN_3                          = 3,
    SAY_BRAN_4                          = 4,
    SAY_BRAN_5                          = 5,

    // Archmage Rhydian talks
    SAY_ARCHMAGE_0                      = 2,
    SAY_ARCHMAGE_1                      = 3,
    SAY_ARCHMAGE_2                      = 4,
    SAY_ARCHMAGE_3                      = 5,
    SAY_ARCHMAGE_4                      = 6
};

enum FL_BRAN_EVENTS
{
    EVENT_BRAN_DISMOUNT                 = 1,
    EVENT_BRAN_SUMMON_RHYDIAN,
    EVENT_BRAN_FL_TALK_0,
    EVENT_BRAN_FL_TALK_1,
    EVENT_BRAN_FL_TALK_2,
    EVENT_BRAN_FL_TALK_3,
    EVENT_BRAN_FL_TALK_4,
    EVENT_BRAN_FL_TALK_5,
    EVENT_BRAN_FL_TALK_6,
    EVENT_BRAN_FL_TALK_7,
    EVENT_BRAN_FL_TALK_8,
    EVENT_BRAN_FL_TALK_9,
    EVENT_BRAN_FL_TALK_10
};

Position const portalPositionFLEvent = { 235.4194f, -138.5261f, 409.5674f, 1.57f };
Position const brannStartingPosition = { 162.3139f, -298.5704f, 499.2952f };
Position const vehicleExitPositionBranFL = { 243.6023f, -79.01531f, 409.7794f, 4.208384f };

Position const kirinTorBattleMageFL[2] =
{
    { 240.250f, -136.4786f, 409.6524f, 3.455752f }, // right
    { 230.508f, -137.1488f, 409.6508f, 5.846853f }  // left
};

Position const kirinTorMagePositions[12] =
{
    { 221.007355f, -127.571465f, 409.568756f, 1.573857f },
    { 216.576416f, -127.550148f, 409.579193f, 1.522789f },
    { 212.555832f, -127.530800f, 409.580444f, 1.565986f },
    { 222.949249f, -118.436378f, 409.587036f, 1.565988f },
    { 218.763290f, -118.416252f, 409.567413f, 1.565988f },
    { 214.773331f, -118.397072f, 409.567413f, 1.565988f }, // End of kirin tor positions for left side
    { 250.144745f, -127.903687f, 409.803650f, 1.646995f },
    { 254.231949f, -127.990219f, 409.803650f, 1.568455f },
    { 258.403931f, -127.999985f, 409.803650f, 1.568455f },
    { 252.595261f, -118.692635f, 409.803650f, 1.584163f },
    { 256.717896f, -118.637527f, 409.803650f, 1.584163f },
    { 260.489441f, -118.972153f, 409.803650f, 1.540966f }  // End of kirin tor positions for right side
};

uint32 const brannsFlyingMachinePathSize = 14;
G3D::Vector3 const brannsFlyingMachinePath[brannsFlyingMachinePathSize] =
{
    { 162.3139f, -298.5704f, 499.2952f },
    { 163.2536f, -298.2284f, 499.2952f },
    { 187.4006f, -142.1330f, 499.758f  },
    { 216.5235f, -102.9176f, 475.6192f },
    { 207.2646f, -0.70204f,  460.2581f },
    { 201.753f,  29.9802f,   465.3137f },
    { 231.985f,  47.57292f,  459.2859f },
    { 247.2324f, 44.02615f,  459.1748f },
    { 253.0585f, 22.74127f,  446.1193f },
    { 255.5544f, -23.08404f, 431.0082f },
    { 260.4913f, -54.52697f, 421.7027f },
    { 246.4216f, -80.03793f, 416.2025f },
    { 246.4216f, -80.03793f, 416.2025f },
    { 246.4216f, -80.03793f, 409.8195f }
};

uint32 const archmageMovePositionsSize = 4;
G3D::Vector3 const archmageMovePositions[archmageMovePositionsSize] =
{
    { 235.3159f, -132.4290f, 409.6924f },
    { 239.1959f, -128.4492f, 410.2823f },
    { 243.6766f, -126.2547f, 410.3174f },
    { 243.0223f, -123.5293f, 410.3174f }
};

uint32 const brannMovePositionsSize = 4;
G3D::Vector3 const brannMovePositions[brannMovePositionsSize] =
{
    { 243.6023f, -79.01531f, 409.7794f },
    { 236.0326f, -102.8987f, 409.8174f },
    { 232.6663f, -111.3207f, 409.8174f },
    { 233.9606f, -123.4371f, 409.6924f }
};

Position const expeditionGroupOne[3] =
{
    { 155.992462f, -50.251137f, 409.804169f, 6.275795f },
    { 146.416718f, -50.180374f, 409.804169f, 6.275795f },
    { 137.979446f, -50.118023f, 409.804169f, 6.275795f }
};

Position const expeditionGroupTwo[3] =
{
    { 156.043152f, -43.391323f, 409.804138f, 6.275795f },
    { 147.893875f, -43.331100f, 409.804138f, 6.275795f },
    { 139.564606f, -43.269547f, 409.804138f, 6.275795f }
};

Position const expeditionGroupThree[3] =
{
    { 156.084015f, -37.861473f, 409.804138f, 6.275795f },
    { 147.079758f, -37.794933f, 409.804138f, 6.275795f },
    { 139.452469f, -37.738567f, 409.804138f, 6.275795f }
};

Position const expeditionGroupFour[3] =
{
    { 156.110397f, -34.291569f, 409.804138f, 6.275795f },
    { 149.099594f, -34.239758f, 409.804138f, 6.275795f },
    { 141.575806f, -34.184158f, 409.804138f, 6.275795f }
};

// final positions for expedition mobs
Position const expeditionRowOne[3] =
{
    { 214.013275f, -97.513832f, 409.803680f, 4.701086f },
    { 213.903244f, -92.399666f, 409.803680f, 4.693233f },
    { 213.992020f, -87.765518f, 409.803680f, 4.693233f }
};

Position const expeditionRowTwo[3] =
{
    { 223.576248f, -97.301590f, 409.803680f, 4.693235f },
    { 223.579483f, -92.586304f, 409.803680f, 4.728576f },
    { 223.669128f, -87.971825f, 409.803680f, 4.685381f }
};

Position const expeditionRowThree[3] =
{
    { 250.864594f, -98.393715f, 409.803680f, 4.708945f },
    { 251.168930f, -93.569145f, 409.803680f, 4.697157f },
    { 251.242889f, -88.714211f, 409.803680f, 4.697157f }
};

Position const expeditionRowFour[3] =
{
    { 260.802795f, -98.680420f, 409.804230f, 4.701888f },
    { 260.841431f, -93.244629f, 409.611877f, 4.713668f },
    { 260.835907f, -88.938133f, 409.760468f, 4.713668f }
};

G3D::Vector3 const expeditionPathOne[2] =
{
    { 164.793686f, -52.793915f, 409.804230f },
    { 212.562424f, -68.838150f, 409.802338f }
};

G3D::Vector3 const expeditionPathTwo[2] =
{
    { 175.779526f, -43.769566f, 409.804138f },
    { 222.570480f, -71.293839f, 409.801697f }
};

G3D::Vector3 const expeditionPathThree[2] =
{
    { 189.624115f, -39.830769f, 409.530487f },
    { 251.580994f, -67.265602f, 409.801971f }
};

G3D::Vector3 const expeditionPathFour[2] =
{
    { 197.288651f, -35.162113f, 409.726837f },
    { 258.137024f, -36.326141f, 409.534363f }
};

struct npc_brann_bronzebeard_flame_leviathanAI : public ScriptedAI
{
    npc_brann_bronzebeard_flame_leviathanAI(Creature* creature) : ScriptedAI(creature)
    {
        _rhyrdianGUID = 0;
        _eventInProgress = false;
    }

    void Reset() override
    {
        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        _eventInProgress = true;
        _events.Reset();
        me->setActive(true);
        if (Creature* flying = me->SummonCreature(NPC_BRANN_FLYING_MACHINE, me->GetPosition()))
        {
            flying->SetHover(true);
            flying->setActive(true);
            DoCast(flying, SPELL_BRANN_RIDE_VEHICLE_FL, true);

            Movement::PointsArray path(brannsFlyingMachinePath, brannsFlyingMachinePath + brannsFlyingMachinePathSize);

            Movement::MoveSplineInit init(flying);
            init.SetSmooth();
            init.MovebyPath(path, 0);
            auto splineDuration = init.Launch();
            _events.ScheduleEvent(EVENT_BRAN_DISMOUNT, splineDuration + 2000);
            _events.ScheduleEvent(EVENT_BRAN_SUMMON_RHYDIAN, 2s);
        }

        me->SummonGameObject(GO_PORTAL_TO_DALARAN_FL, portalPositionFLEvent.GetPositionX(), portalPositionFLEvent.GetPositionY(), portalPositionFLEvent.GetPositionZ(), portalPositionFLEvent.GetOrientation(),
                             0.f, 0.f, 0.f, 1.f, 0, false);

        //! spawn kirin tor mobs
        for (auto i = 0; i < 12; ++i)
        {
            if (Creature* kirinTor = me->SummonCreature(NPC_KIRIN_TOR_MAGE_FL, kirinTorMagePositions[i]))
                kirinTor->CastSpell((Unit*)nullptr, SPELL_SIMPLE_TELEPORT_EFFECT_FL, true);
        }

        for (auto i = 0; i < 2; ++i)
        {
            if (Creature* battleMage = me->SummonCreature(NPC_KIRIN_TOR_BATTLE_MAGE_FL, kirinTorBattleMageFL[i]))
            {
                battleMage->CastSpell((Unit*)nullptr, SPELL_SIMPLE_TELEPORT_EFFECT_FL, true);
                battleMage->CastSpell((Unit*)nullptr, SPELL_KIRIN_TOR_BATTLE_CHANNEL, true);
            }
        }

        //! spawn expedition mobs and move them to correct positions
        for (auto i = 0; i < 3; ++i)
        {
            if (Creature* expedition = me->SummonCreature(roll_chance_i(50) ? NPC_EXPEDITION_ENGINEER_FL : NPC_EXPEDITION_MERCENARY_FL, expeditionGroupOne[i]))
            {
                Movement::PointsArray path(expeditionPathOne, expeditionPathOne + 2);
                path.push_back(G3D::Vector3(expeditionRowOne[i].GetPositionX(), expeditionRowOne[i].GetPositionY(), expeditionRowOne[i].GetPositionZ()));
                Movement::MoveSplineInit init(expedition);
                init.SetSmooth();
                init.MovebyPath(path, 0);
                init.Launch();
            }
        }

        for (auto i = 0; i < 3; ++i)
        {
            if (Creature* expedition = me->SummonCreature(roll_chance_i(50) ? NPC_EXPEDITION_ENGINEER_FL : NPC_EXPEDITION_MERCENARY_FL, expeditionGroupTwo[i]))
            {
                Movement::PointsArray path(expeditionPathTwo, expeditionPathTwo + 2);
                path.push_back(G3D::Vector3(expeditionRowTwo[i].GetPositionX(), expeditionRowTwo[i].GetPositionY(), expeditionRowTwo[i].GetPositionZ()));
                Movement::MoveSplineInit init(expedition);
                init.SetSmooth();
                init.MovebyPath(path, 0);
                init.Launch();
            }
        }

        for (auto i = 0; i < 3; ++i)
        {
            if (Creature* expedition = me->SummonCreature(roll_chance_i(50) ? NPC_EXPEDITION_ENGINEER_FL : NPC_EXPEDITION_MERCENARY_FL, expeditionGroupThree[i]))
            {
                Movement::PointsArray path(expeditionPathThree, expeditionPathThree + 2);
                path.push_back(G3D::Vector3(expeditionRowThree[i].GetPositionX(), expeditionRowThree[i].GetPositionY(), expeditionRowThree[i].GetPositionZ()));
                Movement::MoveSplineInit init(expedition);
                init.SetSmooth();
                init.MovebyPath(path, 0);
                init.Launch();
            }
        }

        for (auto i = 0; i < 3; ++i)
        {
            if (Creature* expedition = me->SummonCreature(roll_chance_i(50) ? NPC_EXPEDITION_ENGINEER_FL : NPC_EXPEDITION_MERCENARY_FL, expeditionGroupFour[i]))
            {
                Movement::PointsArray path(expeditionPathFour, expeditionPathFour + 2);
                path.push_back(G3D::Vector3(expeditionRowFour[i].GetPositionX(), expeditionRowFour[i].GetPositionY(), expeditionRowFour[i].GetPositionZ()));
                Movement::MoveSplineInit init(expedition);
                init.SetSmooth();
                init.MovebyPath(path, 0);
                init.Launch();
            }
        }
    }

    void RhyrdianTalk(uint8 talkId)
    {
        if (Creature* rhyr = ObjectAccessor::GetCreature(*me, _rhyrdianGUID))
            if (rhyr->IsAIEnabled)
                rhyr->AI()->Talk(talkId);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!_eventInProgress)
            return;

        _events.Update(diff);

        while (auto eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_BRAN_DISMOUNT:
                {
                    me->ExitVehicle(&vehicleExitPositionBranFL);

                    Movement::PointsArray path(brannMovePositions, brannMovePositions + brannMovePositionsSize);
                    Movement::MoveSplineInit init(me);
                    init.SetWalk(true);
                    init.SetSmooth();
                    init.SetFacing(6.280275f);
                    init.MovebyPath(path, 0);
                    auto splineDuration = init.Launch();
                    _events.ScheduleEvent(EVENT_BRAN_FL_TALK_0, splineDuration + 1000);
                    break;
                }
                case EVENT_BRAN_SUMMON_RHYDIAN:
                {
                    if (Creature* archmage = me->SummonCreature(NPC_ARCHMAGE_RHYDIAN_FL, portalPositionFLEvent))
                    {
                        _rhyrdianGUID = archmage->GetGUID();
                        archmage->CastSpell((Unit*)nullptr, SPELL_SIMPLE_TELEPORT_EFFECT_FL, true);

                        Movement::PointsArray path(archmageMovePositions, archmageMovePositions + archmageMovePositionsSize);
                        Movement::MoveSplineInit init(archmage);
                        init.SetFacing(3.0570000f);
                        init.SetSmooth();
                        init.SetWalk(true);
                        init.MovebyPath(path, 0);
                        init.Launch();
                    }
                    break;
                }
                case EVENT_BRAN_FL_TALK_0:
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    Talk(SAY_BRAN_0);
                    _events.ScheduleEvent(EVENT_BRAN_FL_TALK_1, 8s);
                    break;
                case EVENT_BRAN_FL_TALK_1:
                    RhyrdianTalk(SAY_ARCHMAGE_0);
                    _events.ScheduleEvent(EVENT_BRAN_FL_TALK_2, 9s);
                    break;
                case EVENT_BRAN_FL_TALK_2:
                    Talk(SAY_BRAN_1);
                    _events.ScheduleEvent(EVENT_BRAN_FL_TALK_3, 9s);
                    break;
                case EVENT_BRAN_FL_TALK_3:
                    RhyrdianTalk(SAY_ARCHMAGE_1);
                    _events.ScheduleEvent(EVENT_BRAN_FL_TALK_4, 9s);
                    break;
                case EVENT_BRAN_FL_TALK_4:
                    Talk(SAY_BRAN_2);
                    _events.ScheduleEvent(EVENT_BRAN_FL_TALK_5, 8s);
                    break;
                case EVENT_BRAN_FL_TALK_5:
                    Talk(SAY_BRAN_3);
                    _events.ScheduleEvent(EVENT_BRAN_FL_TALK_6, 8s);
                    break;
                case EVENT_BRAN_FL_TALK_6:
                    RhyrdianTalk(SAY_ARCHMAGE_2);
                    _events.ScheduleEvent(EVENT_BRAN_FL_TALK_7, 9s);
                    break;
                case EVENT_BRAN_FL_TALK_7:
                    RhyrdianTalk(SAY_ARCHMAGE_3);
                    _events.ScheduleEvent(EVENT_BRAN_FL_TALK_8, 8s);
                    break;
                case EVENT_BRAN_FL_TALK_8:
                    Talk(SAY_BRAN_4);
                    _events.ScheduleEvent(EVENT_BRAN_FL_TALK_9, 9s);
                    break;
                case EVENT_BRAN_FL_TALK_9:
                    RhyrdianTalk(SAY_ARCHMAGE_4);
                    _events.ScheduleEvent(EVENT_BRAN_FL_TALK_10, 8s);
                    break;
                case EVENT_BRAN_FL_TALK_10:
                    Talk(SAY_BRAN_5);
                    break;
            }
        }
    }
private:
    bool _eventInProgress;
    EventMap _events;
    uint64 _rhyrdianGUID;
};

class spell_hurl_boulder_leviathan_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_hurl_boulder_leviathan_SpellScript);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (GetHitUnit() && GetHitUnit()->ToCreature())
            if (GetHitUnit()->GetEntry() == NPC_POOL_OF_TAR_LEVIATHAN)
                SetHitDamage(0);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hurl_boulder_leviathan_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_mortar_flames_leviathan_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_mortar_flames_leviathan_SpellScript);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (GetHitUnit() && GetHitUnit()->ToCreature())
            if (GetHitUnit()->GetEntry() == NPC_POOL_OF_TAR_LEVIATHAN)
                SetHitDamage(0);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_mortar_flames_leviathan_SpellScript::HandleHit, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_boss_flame_leviathan()
{
    new boss_flame_leviathan();
    new boss_flame_leviathan_seat();
    new boss_flame_leviathan_defense_turret();
    new boss_flame_leviathan_overload_device();
    new npc_pool_of_tar();
    new CreatureAILoader<npc_brann_bronzebeard_flame_leviathanAI>("npc_brann_bronzebeard_flame_leviathan");

    // Hard Mode
    new npc_freya_ward();
    new npc_thorims_hammer();
    new npc_mimirons_inferno();
    new npc_hodirs_fury();

    // Helpers
    new npc_lore_keeper_of_norgannon_ulduar();
    new npc_brann_ulduar();
    new npc_brann_radio();
    new npc_storm_beacon_spawn();
    new boss_flame_leviathan_safety_container();
    new npc_mechanolift();
    new npc_ward_of_life();
    new CreatureAILoader<npc_liquid_piryte_flame_leviathanAI>("npc_liquid_piryte_flame_leviathan");
    new CreatureAILoader<npc_flame_leviathan_vehicles_AI>("npc_flame_leviathan_vehicles");

    // GOs
    new go_ulduar_tower();

    // Spells
    new spell_load_into_catapult();
    new spell_auto_repair();
    new spell_systems_shutdown();
    new spell_pursue();
    new spell_vehicle_throw_passenger();
    new spell_tar_blaze();
    new spell_vehicle_grab_pyrite();
    new spell_vehicle_chopper_grab_pyrite();
    new spell_vehicle_circuit_overload();
    new spell_orbital_supports();
    new spell_thorims_hammer();
    new spell_shield_generator();
    new spell_demolisher_ride_vehicle();
    new SpellScriptLoaderEx<spell_flames_flame_leviathan_fury_remover_SpellScript>("spell_flames_flame_leviathan_fury_remover");
    new SpellScriptLoaderEx<spell_hurl_boulder_leviathan_SpellScript>("spell_hurl_boulder_leviathan");
    new SpellScriptLoaderEx<spell_mortar_flames_leviathan_SpellScript>("spell_mortar_flames_leviathan");

    // Achievements
    new achievement_flame_leviathan_towers("achievement_flame_leviathan_orbital_bombardment", 1);
    new achievement_flame_leviathan_towers("achievement_flame_leviathan_orbital_devastation", 2);
    new achievement_flame_leviathan_towers("achievement_flame_leviathan_nuked_from_orbit", 3);
    new achievement_flame_leviathan_towers("achievement_flame_leviathan_orbituary", 4);
    new achievement_flame_leviathan_shutout();
    new achievement_flame_leviathan_garage("achievement_flame_leviathan_garage_chopper", NPC_VEHICLE_CHOPPER, 0);
    new achievement_flame_leviathan_garage("achievement_flame_leviathan_garage_siege_engine", NPC_SALVAGED_SIEGE_ENGINE, NPC_SALVAGED_SIEGE_ENGINE_TURRET);
    new achievement_flame_leviathan_garage("achievement_flame_leviathan_garage_demolisher", NPC_SALVAGED_DEMOLISHER, NPC_SALVAGED_DEMOLISHER_TURRET);
    new achievement_flame_leviathan_unbroken();
}
