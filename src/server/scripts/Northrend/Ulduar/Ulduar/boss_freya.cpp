/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ulduar.h"
#include "SpellAuras.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "PassiveAI.h"
#include "Player.h"

enum FreyaSpells
{
    // LIFEBINDER
    SPELL_AUTO_GROW                                = 62559,
    SPELL_LIFEBINDER_PHERONOMES                    = 62619,
    SPELL_LIFEBINDER_VISUAL                        = 62579,
    SPELL_LIFEBINDER_HEAL_10                       = 62584,
    SPELL_LIFEBINDER_HEAL_25                       = 64185,

    // FREYA
    SPELL_TOUCH_OF_EONAR_10                        = 62528,
    SPELL_TOUCH_OF_EONAR_25                        = 62892,
    SPELL_ATTUNED_TO_NATURE                        = 62519,
    SPELL_SUMMON_LIFEBINDER                        = 62870,
    SPELL_SUNBEAM_10                               = 62623,
    SPELL_SUNBEAM_25                               = 62872,
    SPELL_NATURE_BOMB_SELECTOR                     = 64604,
    SPELL_NATURE_BOMB_FLIGHT                       = 64648,
    SPELL_NATURE_BOMB_DAMAGE_10                    = 64587,
    SPELL_NATURE_BOMB_DAMAGE_25                    = 64650,
    SPELL_NATURE_BOMB_SUMMON                       = 64600,
    SPELL_GREEN_BANISH_STATE                       = 32567,
    SPELL_BERSERK                                  = 47008,

    // HARD MODE
    SPELL_GROUND_TREMOR_FREYA_10                   = 62437,
    SPELL_GROUND_TREMOR_FREYA_25                   = 62859,
    SPELL_IRON_ROOTS_FREYA_10                      = 62862,
    SPELL_IRON_ROOTS_FREYA_25                      = 62439,
    SPELL_IRON_ROOTS_FREYA_DAMAGE_10               = 62861,
    SPELL_IRON_ROOTS_FREYA_DAMAGE_25               = 62438,
    SPELL_UNSTABLE_SUN_FREYA_DAMAGE_10             = 62451,
    SPELL_UNSTABLE_SUN_FREYA_DAMAGE_25             = 62865,
    SPELL_UNSTABLE_SUN_VISUAL                      = 62216,

    // ELDERS
    SPELL_DRAINED_OF_POWER                         = 62467,

    SPELL_STONEBARK_ESSENCE_H                      = 62483,
    SPELL_STONEBARK_ESSENCE                        = 65589,

    SPELL_IRONBRANCH_ESSENCE_H                     = 62484,
    SPELL_IRONBRANCH_ESSENCE                       = 65588,

    SPELL_BRIGHTLEAF_ESSENCE_H                     = 62485,
    SPELL_BRIGHTLEAF_ESSENCE                       = 65587,

    // BRIGHTLEAF
    SPELL_BRIGHTLEAF_FLUX                          = 62239,
    SPELL_SOLAR_FLARE_10                           = 62240,
    SPELL_SOLAR_FLARE_25                           = 64087,
    SPELL_UNSTABLE_SUN_BEAM_AURA                   = 62211,
    SPELL_PHOTOSYNTHESIS                           = 62209,
    SPELL_UNSTABLE_SUN_DAMAGE_10                   = 62217,
    SPELL_UNSTABLE_SUN_DAMAGE_25                   = 62922,

    // IRONBRANCH
    SPELL_IMPALE_10                                = 62310,
    SPELL_IMPALE_25                                = 62928,
    SPELL_IRON_ROOTS_10                            = 62275,
    SPELL_IRON_ROOTS_25                            = 62929,
    SPELL_IRON_ROOTS_DAMAGE_10                     = 62283,
    SPELL_IRON_ROOTS_DAMAGE_25                     = 62930,
    SPELL_THORN_SWARM_10                           = 62285,
    SPELL_THORN_SWARM_25                           = 62931,

    // STONEBARK
    SPELL_FISTS_OF_STONE                           = 62344,
    SPELL_GROUND_TREMOR_10                         = 62325,
    SPELL_GROUND_TREMOR_25                         = 62932,
    SPELL_PETRIFIED_BARK_10                        = 62337,
    SPELL_PETRIFIED_BARK_25                        = 62933,

    // SNAPLASHER
    SPELL_HARDENED_BARK_10                         = 62664,
    SPELL_HARDENED_BARK_25                         = 64191,

    // ANCIENT WATER SPIRIT
    SPELL_TIDAL_WAVE_10                            = 62653,
    SPELL_TIDAL_WAVE_25                            = 62935,
    SPELL_TIDAL_WAVE_DAMAGE_10                     = 62654,
    SPELL_TIDAL_WAVE_DAMAGE_25                     = 62936,
    SPELL_TIDAL_WAVE_AURA                          = 62655,

    // STORM LASHER
    SPELL_LIGHTNING_LASH_10                        = 62648,
    SPELL_LIGHTNING_LASH_25                        = 62939,
    SPELL_STORMBOLT_10                             = 62649,
    SPELL_STORMBOLT_25                             = 62938,
    SPELL_STORM_LASHER_VISUAL                      = 62639,

    // ANCIENT CONSERVATOR
    SPELL_CONSERVATOR_GRIP                         = 62532,
    SPELL_NATURE_FURY_10                           = 62589,
    SPELL_NATURE_FURY_25                           = 63571,
    SPELL_POTENT_PHEROMONES                        = 62541,
    SPELL_HEALTHY_SPORE_VISUAL                     = 62538,
    SPELL_HEALTHY_SPORE_SUMMON                     = 62566,
    SPELL_HEALTHY_SPORE_NW                         = 62582,
    SPELL_HEALTHY_SPORE_NE                         = 62591,
    SPELL_HEALTHY_SPORE_SE                         = 62592,
    SPELL_HEALTHY_SPORE_SW                         = 62593,

    // DETONATING LASHER
    SPELL_DETONATE_10                              = 62598,
    SPELL_DETONATE_25                              = 62937,
    SPELL_FLAME_LASH                               = 62608,

    // ACHIEVEMENT
    SPELL_DEFORESTATION_CREDIT                     = 65015,

    //! Attuned to nature stack removal spells
    SPELL_NATURE_REMOVE_25                         = 62521,
    SPELL_NATURE_REMOVE_2                          = 62524,
    SPELL_NATURE_REMOVE_10                         = 62525

};

#define SPELL_GROUND_TREMOR                        RAID_MODE(SPELL_GROUND_TREMOR_10, SPELL_GROUND_TREMOR_25)
#define SPELL_PETRIFIED_BARK                       RAID_MODE(SPELL_PETRIFIED_BARK_10, SPELL_PETRIFIED_BARK_25)
#define SPELL_IRON_ROOTS                           RAID_MODE(SPELL_IRON_ROOTS_10, SPELL_IRON_ROOTS_25)
#define SPELL_IMPALE                               RAID_MODE(SPELL_IMPALE_10, SPELL_IMPALE_25)
#define SPELL_THORN_SWARM                          RAID_MODE(SPELL_THORN_SWARM_10, SPELL_THORN_SWARM_25)
#define SPELL_UNSTABLE_SUN_DAMAGE                  RAID_MODE(SPELL_UNSTABLE_SUN_DAMAGE_10, SPELL_UNSTABLE_SUN_DAMAGE_25)
#define SPELL_SOLAR_FLARE                          RAID_MODE(SPELL_SOLAR_FLARE_10, SPELL_SOLAR_FLARE_25)
#define SPELL_TOUCH_OF_EONAR                       RAID_MODE(SPELL_TOUCH_OF_EONAR_10, SPELL_TOUCH_OF_EONAR_25)
#define SPELL_LIFEBINDER_HEAL                      RAID_MODE(SPELL_LIFEBINDER_HEAL_10, SPELL_LIFEBINDER_HEAL_25)
#define SPELL_TIDAL_WAVE                           RAID_MODE(SPELL_TIDAL_WAVE_10, SPELL_TIDAL_WAVE_25)
#define SPELL_TIDAL_WAVE_DAMAGE                    RAID_MODE(SPELL_TIDAL_WAVE_DAMAGE_10, SPELL_TIDAL_WAVE_DAMAGE_25)
#define SPELL_NATURE_FURY                          RAID_MODE(SPELL_NATURE_FURY_10, SPELL_NATURE_FURY_25)
#define SPELL_HARDENED_BARK                        RAID_MODE(SPELL_HARDENED_BARK_10, SPELL_HARDENED_BARK_25)
#define SPELL_DETONATE                             RAID_MODE(SPELL_DETONATE_10, SPELL_DETONATE_25)
#define SPELL_NATURE_BOMB_DAMAGE                   RAID_MODE(SPELL_NATURE_BOMB_DAMAGE_10, SPELL_NATURE_BOMB_DAMAGE_25)
#define SPELL_SUNBEAM                              RAID_MODE(SPELL_SUNBEAM_10, SPELL_SUNBEAM_25)
#define SPELL_GROUND_TREMOR_FREYA                  RAID_MODE(SPELL_GROUND_TREMOR_FREYA_10, SPELL_GROUND_TREMOR_FREYA_25)
#define SPELL_IRON_ROOTS_FREYA                     RAID_MODE(SPELL_IRON_ROOTS_FREYA_10, SPELL_IRON_ROOTS_FREYA_25)
#define SPELL_UNSTABLE_SUN_FREYA_DAMAGE            RAID_MODE(SPELL_UNSTABLE_SUN_FREYA_DAMAGE_10, SPELL_UNSTABLE_SUN_FREYA_DAMAGE_25)
#define SPELL_LIGHTNING_LASH                       RAID_MODE(SPELL_LIGHTNING_LASH_10, SPELL_LIGHTNING_LASH_25)
#define SPELL_STORMBOLT                            RAID_MODE(SPELL_STORMBOLT_10, SPELL_STORMBOLT_25)

enum FreyaEvents
{
    // FREYA
    EVENT_FREYA_ADDS_SPAM                        = 1,
    EVENT_FREYA_LIFEBINDER                       = 2,
    EVENT_FREYA_NATURE_BOMB                      = 3,
    EVENT_FREYA_SUNBEAM                          = 4,
    EVENT_FREYA_BERSERK                          = 5,
    // HARD MODE
    EVENT_FREYA_GROUND_TREMOR                    = 6,
    EVENT_FREYA_IRON_ROOT                        = 7,
    EVENT_FREYA_UNSTABLE_SUN_BEAM                = 8,
    EVENT_FREYA_RESPAWN_TRIO                     = 9,

    // STONEBARK
    EVENT_STONEBARK_FISTS_OF_STONE               = 10,
    EVENT_STONEBARK_GROUND_TREMOR                = 11,
    EVENT_STONEBARK_PETRIFIED_BARK               = 12,

    // BRIGHTLEAF
    EVENT_BRIGHTLEAF_FLUX                        = 20,
    EVENT_BRIGHTLEAF_SOLAR_FLARE                 = 21,
    EVENT_BRIGHTLEAF_UNSTABLE_SUN_BEAM           = 22,
    EVENT_BRIGHTLEAF_DESPAWN_SUN_BEAM            = 23,

    // IRONBRANCH
    EVENT_IRONBRANCH_IMPALE                      = 30,
    EVENT_IRONBRANCH_IRON_ROOT                   = 31,
    EVENT_IRONBRANCH_THORN_SWARM                 = 32,

    // SUMMONS
    EVENT_ANCIENT_CONSERVATOR_NATURE_FURY        = 40,
    EVENT_WATER_SPIRIT_CHARGE                    = 45,
    EVENT_WATER_SPIRIT_DAMAGE                    = 46,
    EVENT_STORM_LASHER_LIGHTNING_LASH            = 50,
    EVENT_STORM_LASHER_STORMBOLT                 = 51,
    EVENT_DETONATING_LASHER_FLAME_LASH           = 55,
    EVENT_DETONATING_LASHER_START_ATTACK         = 56,
    EVENT_DETONATING_LASHER_CHANGE_TARGET        = 57,
    EVENT_DETONATING_LASHER_ANIM                 = 58
};

enum FreyaSounds
{
    // STONEBARK
    SOUND_STONEBARK_AGGRO                        = 15500,
    SOUND_STONEBARK_SLAY1                        = 15501,
    SOUND_STONEBARK_SLAY2                        = 15502,
    SOUND_STONEBARK_DEATH                        = 15503,

    // IRONBRANCH
    SOUND_IRONBRANCH_AGGRO                       = 15493,
    SOUND_IRONBRANCH_SLAY1                       = 15494,
    SOUND_IRONBRANCH_SLAY2                       = 15495,
    SOUND_IRONBRANCH_DEATH                       = 15496,

    // BRIGHTLEAF
    SOUND_BRIGHTLEAF_AGGRO                       = 15483,
    SOUND_BRIGHTLEAF_SLAY1                       = 15485,
    SOUND_BRIGHTLEAF_SLAY2                       = 15486,
    SOUND_BRIGHTLEAF_DEATH                       = 15487
};

enum FreyaNPCs
{
    NPC_NATURE_BOMB                              = 34129,
    NPC_IRON_ROOT_TRIGGER                        = 33088,
    NPC_IRON_ROOT_TRIGGER_FREYA                  = 33168,
    NPC_FREYA_UNSTABLE_SUN_BEAM                  = 33170,
    NPC_UNSTABLE_SUN_BRIGHTLEAF                  = 33050, // 10 SECS?

    // FIRST WAVE
    NPC_STORM_LASHER                            = 32919,
    NPC_ANCIENT_WATER_SPIRIT                    = 33202,
    NPC_SNAPLASHER                              = 32916,

    // SEC WAVE
    NPC_ANCIENT_CONSERVATOR                     = 33203,
    NPC_HEALTHY_SPORE                           = 33215,

    // THIRD WAVE
    NPC_DETONATING_LASHER                       = 32918
};

enum FreyaSouns
{
    SOUND_AGGRO                                 = 15526,
    SOUND_ELDERS                                = 15527,
    SOUND_CONSERVATOR                           = 15528,
    SOUND_SLAY1                                 = 15529,
    SOUND_SLAY2                                 = 15530,
    SOUND_DEATH                                 = 15531,
    SOUND_BERSERK                               = 15532,
    SOUND_TRIO                                  = 15533,
    SOUND_DETONATING                            = 15534,
    SOUND_ASKHELP                               = 15535
};

enum Misc
{
    ACTION_REMOVE_10_STACK                      = 10,
    ACTION_REMOVE_25_STACK                      = 25,
    ACTION_REMOVE_2_STACK                       = 2,
    ACTION_RESPAWN_TRIO                         = 1,
    ACTION_LUMBERJACKED                         = -1,

    EVENT_PHASE_ADDS                            = 1,
    EVENT_PHASE_FINAL                           = 2,

    DATA_GET_ELDER_COUNT                        = 1,
    DATA_BACK_TO_NATURE                         = 2,
    DATA_FREYA_START_PHASE_TWO                  = 3,

    CRITERIA_LUMBERJACKED                       = 21686,

    ACTION_DESPAWN_COMPLETELY                   = 10,

    MODEL_INVISIBLE_NATURE_BOMB                 = 11686,

    FREYA_EMOTE_TREE                            = 8,
    FREYA_EMOTE_ALLIES                          = 9,
    FREYA_EMOTE_TREMOR                          = 10,
    FREYA_EMOTE_ROOTS                           = 11
};

std::vector<uint32> adds = { NPC_ANCIENT_WATER_SPIRIT, NPC_STORM_LASHER, NPC_SNAPLASHER, NPC_ANCIENT_CONSERVATOR, NPC_DETONATING_LASHER };

class boss_freya : public CreatureScript
{
public:
    boss_freya() : CreatureScript("boss_freya") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_freyaAI (pCreature);
    }

    struct boss_freyaAI : public ScriptedAI
    {
        boss_freyaAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me)
        {
            m_pInstance = pCreature->GetInstanceScript();
            if (!me->IsAlive())
                if (m_pInstance)
                    m_pInstance->SetData(TYPE_FREYA, DONE);
            memset(_elderGUID, 0, sizeof(_elderGUID));
        }

        InstanceScript* m_pInstance;
        EventMap events;
        SummonList summons;

        uint8 _waveNumber;
        uint8 _trioKilled;
        uint8 _spawnedAmount;
        uint8 _lumberjacked;
        bool _respawningTrio;
        bool _backToNature;
        bool _hastenWave;
        bool _firstWaveSpawned;
        uint8 _deforestation;

        uint64 _elderGUID[3];
        uint32 _fightTimer;

        void MoveInLineOfSight(Unit*) { }
        void Reset()
        {
            if (m_pInstance && m_pInstance->GetData(TYPE_FREYA) != DONE)
                m_pInstance->SetData(TYPE_FREYA, NOT_STARTED);

            if (m_pInstance)
            {
                m_pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_IRON_ROOTS_FREYA_DAMAGE_10);
                m_pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_IRON_ROOTS_FREYA_DAMAGE_25);
            }

            _fightTimer = 0;
            CheckRoots();
            events.Reset();
            summons.DespawnAll();

            for (uint8 i = 0; i < 3; ++i)
            {
                if (!_elderGUID[i])
                    continue;

                if (Creature* elder = ObjectAccessor::GetCreature(*me, _elderGUID[i]))
                    elder->AI()->EnterEvadeMode();
                _elderGUID[i] = 0;
            }

            _lumberjacked = 0;
            _spawnedAmount = 0;
            _trioKilled = 0;
            _waveNumber = urand(1,3);
            _hastenWave = false;
            _firstWaveSpawned = false;
            _respawningTrio = false;
            _backToNature = true;
            _deforestation = 0;
        }

        void CheckRoots()
        {
            for (auto& summoned : summons)
            {
                if (Creature* root = ObjectAccessor::GetCreature(*me, summoned))
                    if (root->GetEntry() == NPC_IRON_ROOT_TRIGGER_FREYA)
                        if (root->IsAlive())
                            Unit::Kill(me, root);
            }
        }

        void JustDied(Unit* killer)
        {
            CheckRoots();
            ScriptedAI::JustDied(killer);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() != TYPEID_PLAYER || urand(0,2))
                return;

            if (urand(0,1))
            {
                me->MonsterYell("Forgive me.", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_SLAY1);
            }
            else
            {
                me->MonsterYell("From your death springs life anew!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_SLAY2);
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType, SpellSchoolMask)
        {
            // kaboom!
            if (damage >= me->GetHealth())
            {
                if (!m_pInstance)
                    return;

                if (m_pInstance->GetData(TYPE_FREYA) == DONE)
                    return;

                m_pInstance->SetData(TYPE_FREYA, DONE);

                uint8 _elderCount = 0;
                for (uint8 i = 0; i < 3; ++i)
                {
                    if (!_elderGUID[i])
                        continue;

                    if (Creature* e = ObjectAccessor::GetCreature(*me, _elderGUID[i]))
                    {
                        // persist thru death auras
                        e->RemoveAllAuras();
                        Unit::Kill(e, e);
                    }
                    ++_elderCount;
                }

                uint32 chestId = RAID_MODE(GO_FREYA_CHEST, GO_FREYA_CHEST_HERO);
                chestId -= 2 * _elderCount; // offset
                sLog->outBasic("CHEST ID: %u", chestId);
                if (GameObject* go = me->GetMap()->SummonGameObject(chestId, 2345.61f, -71.20f, 425.104f, 3.0f, 0, 0, 0, 0, 0))
                {
                    go->SetSpellId(1);
                    go->SetUInt32Value(GAMEOBJECT_FLAGS, 0);
                }

                if (Map* map = me->GetMap())
                    CheckCreatureRecord(me->SelectNearestPlayer(150.0f), me->GetCreatureTemplate()->Entry + uint32(_elderCount == 3), Difficulty(map->GetDifficulty() + (_elderCount == 3 ? 2 : 0)), "", 15000, _fightTimer);

                me->MonsterYell("His hold on me dissipates. I can see clearly once more. Thank you, heroes.", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_DEATH);

                damage = 0;
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->setFaction(35);
                me->SetHealth(me->GetMaxHealth());
                me->CombatStop();
                me->RemoveAllAuras();
                events.Reset();
                me->DespawnOrUnsummon(5000);

                summons.DespawnAll();
                events.Reset();
                m_pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_IRON_ROOTS_FREYA_DAMAGE_10);
                m_pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_IRON_ROOTS_FREYA_DAMAGE_25);

                // Defeat credit
                me->CastSpell(me, 65074, true); // credit
                //! 3 knocks
                if (_elderCount >= 3)
                {
                    m_pInstance->SetData(DATA_FREYA_HARDMODE, DATA_FREYA_HARDMODE);
                }
            }
        }

        void JustSummoned(Creature* cr)
        {
            summons.Summon(cr);
        }

        bool IsWaveAlive()
        {
            for (auto itr : adds)
                if (me->FindNearestCreature(itr, 250.0f, true))
                    return true;
            return false;
        }

        Position GenerateRandomPosition() const
        {
            Position finalPos;
            finalPos.m_positionX = me->GetPositionX() + frand(5.f, 15.f);
            finalPos.m_positionY = me->GetPositionY() + frand(5.f, 15.f);
            finalPos.m_positionZ = me->GetMap()->GetHeight(finalPos.GetPositionX(), finalPos.GetPositionY(), MAX_HEIGHT);
            return finalPos;
        }

        void SpawnWave()
        {
            Talk(FREYA_EMOTE_ALLIES);
            _waveNumber = _waveNumber == 1 ? 3 : _waveNumber-1;

            // Wave of three
            if (_waveNumber == 1)
            {
                me->MonsterYell("Children, assist me!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_TRIO);
                me->SummonCreature(NPC_ANCIENT_WATER_SPIRIT, GenerateRandomPosition());
                me->SummonCreature(NPC_STORM_LASHER, GenerateRandomPosition());
                me->SummonCreature(NPC_SNAPLASHER, GenerateRandomPosition());
            }
            // Ancient Conservator
            else if (_waveNumber == 2)
            {
                me->MonsterYell("Eonar, your servant requires aid!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_CONSERVATOR);
                me->SummonCreature(NPC_ANCIENT_CONSERVATOR, GenerateRandomPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 7000);
            }
            // Detonating Lashers
            else if (_waveNumber == 3)
            {
                me->MonsterYell("The swarm of the elements shall overtake you!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_DETONATING);
                for (uint8 i = 0; i < 10; ++i)
                {
                    float angle = i * 2 * M_PI / 10;
                    float x = me->GetPositionX() + cos(angle) * 15.0f;
                    float y = me->GetPositionY() + sin(angle) * 15.0f;
                    float z = me->GetPositionZ();

                    if (Creature* lasher = me->SummonCreature(NPC_DETONATING_LASHER, x, y, z, 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 7000))
                    {
                        lasher->UpdateAllowedPositionZ(x, y, z);
                        lasher->NearTeleportTo(x, y, z, 0.0f);
                    }
                }
            }
        }

        void DoAction(int32 param)
        {
            if (param == ACTION_LUMBERJACKED)
            {
                if (!m_pInstance)
                    return;

                ++_lumberjacked;
                if (_lumberjacked == 1)
                    m_pInstance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, CRITERIA_LUMBERJACKED);
                else if (_lumberjacked == 3)
                    m_pInstance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, 65296 /*SPELL_LUMBERJACKED*/, 0, me);
                return;
            }

            if (param == ACTION_RESPAWN_TRIO)
            {
                if (!_respawningTrio)
                {
                    _respawningTrio = true;
                    events.ScheduleEvent(EVENT_FREYA_RESPAWN_TRIO, 10000);
                }

                ++_trioKilled;
                return;
            }

            // Deforestation Achievement Counter
            if (param == ACTION_REMOVE_10_STACK)
            {
                ++_deforestation;
                if (_deforestation >= 6 && m_pInstance)
                    m_pInstance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_DEFORESTATION_CREDIT, 0, me);
                // do not return
            }
        }

        uint32 GetData(uint32 param) const
        {
            if (param == DATA_GET_ELDER_COUNT)
            {
                uint8 _count = 0;
                for (uint8 i = 0; i < 3; ++i)
                    if (_elderGUID[i])
                        ++_count;

                return _count;
            }
            if (param == DATA_BACK_TO_NATURE)
                return _backToNature;

            return 0;
        }

        void SetData(uint32 type, uint32 data) override
        {
            if (type == DATA_FREYA_START_PHASE_TWO)
            {
                if (!events.IsInPhase(EVENT_PHASE_FINAL))
                {
                    events.SetPhase(EVENT_PHASE_FINAL);
                    events.ScheduleEvent(EVENT_FREYA_NATURE_BOMB, 15000);
                }
            }
        }

        void JustReachedHome() override { me->setActive(false); }

        void EnterCombat(Unit* who) override
        {
            _fightTimer = getMSTime();
            me->setActive(true);
            me->SetInCombatWithZone();
            me->CastSpell(me, SPELL_TOUCH_OF_EONAR, true);
            if (Aura* aur = me->AddAura(SPELL_ATTUNED_TO_NATURE, me))
                aur->SetStackAmount(150);

            events.ScheduleEvent(EVENT_FREYA_ADDS_SPAM, 10000, 0, EVENT_PHASE_ADDS);
            events.ScheduleEvent(EVENT_FREYA_LIFEBINDER, 30000);
            events.ScheduleEvent(EVENT_FREYA_SUNBEAM, urand(23000, 29000));
            events.ScheduleEvent(EVENT_FREYA_BERSERK, sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) ? 480000 : 600000);
            events.SetPhase(EVENT_PHASE_ADDS);

            if( !m_pInstance )
                return;

            if (m_pInstance->GetData(TYPE_FREYA) == DONE)
                return;

            if (who->HasAuraType(SPELL_AURA_MOUNTED))
                who->RemoveAurasByType(SPELL_AURA_MOUNTED);

            m_pInstance->SetData(DATA_FREYA_PULLED, DATA_FREYA_PULLED);
            if (m_pInstance->GetData(TYPE_FREYA) != DONE)
                m_pInstance->SetData(TYPE_FREYA, IN_PROGRESS);

            // HARD MODE CHECKS
            Creature* elder = NULL;
            elder = ObjectAccessor::GetCreature(*me, m_pInstance->GetData64(NPC_ELDER_STONEBARK));
            if (elder && elder->IsAlive())
            {
                elder->CastSpell(elder, SPELL_DRAINED_OF_POWER, true);
                elder->CastSpell(elder, RAID_MODE(SPELL_STONEBARK_ESSENCE, SPELL_STONEBARK_ESSENCE_H), true);
                elder->SetInCombatWithZone();

                events.ScheduleEvent(EVENT_FREYA_GROUND_TREMOR, urand(35000, 43000));
                _elderGUID[0] = elder->GetGUID();
            }

            elder = ObjectAccessor::GetCreature(*me, m_pInstance->GetData64(NPC_ELDER_IRONBRANCH));
            if (elder && elder->IsAlive())
            {
                elder->CastSpell(elder, SPELL_DRAINED_OF_POWER, true);
                elder->CastSpell(elder, RAID_MODE(SPELL_IRONBRANCH_ESSENCE, SPELL_IRONBRANCH_ESSENCE_H), true);
                elder->SetInCombatWithZone();

                events.ScheduleEvent(EVENT_FREYA_IRON_ROOT, 20000);
                _elderGUID[1] = elder->GetGUID();
            }

            elder = ObjectAccessor::GetCreature(*me, m_pInstance->GetData64(NPC_ELDER_BRIGHTLEAF));
            if (elder && elder->IsAlive())
            {
                elder->CastSpell(elder, SPELL_DRAINED_OF_POWER, true);
                elder->CastSpell(elder, RAID_MODE(SPELL_BRIGHTLEAF_ESSENCE, SPELL_BRIGHTLEAF_ESSENCE_H), true);
                elder->SetInCombatWithZone();

                events.ScheduleEvent(EVENT_FREYA_UNSTABLE_SUN_BEAM, urand(40000, 45000));
                _elderGUID[2] = elder->GetGUID();
            }

            if (_elderGUID[0] || _elderGUID[1] || _elderGUID[2])
            {
                me->MonsterYell("Elders, grant me your strength!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_ELDERS);
            }
            else
            {
                me->MonsterYell("The Conservatory must be protected!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_AGGRO);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (_firstWaveSpawned && !_hastenWave && !IsWaveAlive())
            {
                events.RescheduleEvent(EVENT_FREYA_ADDS_SPAM, urand(5000, 10000), 0, EVENT_PHASE_ADDS);
                _hastenWave = true;
            }

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
            case EVENT_FREYA_ADDS_SPAM:
                _hastenWave = false;
                if (!_firstWaveSpawned)
                    _firstWaveSpawned = true;
                if (_spawnedAmount < 6)
                    SpawnWave();
                else
                {
                    events.SetPhase(EVENT_PHASE_FINAL);
                    events.ScheduleEvent(EVENT_FREYA_NATURE_BOMB, 15000);
                    events.PopEvent();
                    return;
                }

                _spawnedAmount++;
                events.PopEvent();
                events.ScheduleEvent(EVENT_FREYA_ADDS_SPAM, 60000, 0, EVENT_PHASE_ADDS);
                break;
            case EVENT_FREYA_LIFEBINDER:
            {
                Talk(FREYA_EMOTE_TREE);
                events.RepeatEvent(urand(40000, 45000));
                float x, y, z;
                for (uint8 i = 0; i < 10; ++i)
                {
                    x = me->GetPositionX()+urand(7,25);
                    y = me->GetPositionY()+urand(7,25);
                    z = me->GetMap()->GetHeight(x, y, MAX_HEIGHT)+0.5f;
                    if (me->IsWithinLOS(x, y, z))
                    {
                        me->CastSpell(x, y, z, SPELL_SUMMON_LIFEBINDER, true);
                        return;
                    }
                }

                me->CastSpell(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), SPELL_SUMMON_LIFEBINDER, true);
                break;
            }
            case EVENT_FREYA_SUNBEAM:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.f, true))
                    me->CastSpell(target, SPELL_SUNBEAM, false);
                events.RepeatEvent(urand(20000, 25000));
                break;
            case EVENT_FREYA_RESPAWN_TRIO:
                events.PopEvent();
                _deforestation = 0;
                _respawningTrio = false;
                if (_trioKilled < 3)
                    summons.DoAction(ACTION_RESPAWN_TRIO);
                else
                    summons.DoAction(ACTION_DESPAWN_COMPLETELY);

                _trioKilled = 0;
                break;
            case EVENT_FREYA_NATURE_BOMB:
            {
                DoCastAOE(SPELL_NATURE_BOMB_SELECTOR, true);
                events.RepeatEvent(15000);
                break;
            }
            case EVENT_FREYA_BERSERK:
                me->MonsterYell("You have strayed too far, wasted too much time!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_BERSERK);
                me->CastSpell(me, SPELL_BERSERK, true);
                events.PopEvent();
                break;
            case EVENT_FREYA_GROUND_TREMOR:
            {
                Talk(FREYA_EMOTE_TREMOR);
                auto timerTillSunBeam = events.GetTimeUntilEvent(EVENT_FREYA_SUNBEAM);
                events.CancelEvent(EVENT_FREYA_SUNBEAM);
                events.ScheduleEvent(EVENT_FREYA_SUNBEAM, timerTillSunBeam + urand(8000, 11000));
                me->CastSpell(me, SPELL_GROUND_TREMOR_FREYA, false);
                events.RepeatEvent(urand(25000, 30000));
                break;
            }
            case EVENT_FREYA_IRON_ROOT:
                Talk(FREYA_EMOTE_ROOTS);
                me->CastCustomSpell(SPELL_IRON_ROOTS_FREYA, SPELLVALUE_MAX_TARGETS, RAID_MODE(1, 3), me, false);
                events.RepeatEvent(urand(40000, 45000));
                break;
            case EVENT_FREYA_UNSTABLE_SUN_BEAM:

                std::vector<Player*> plrlist;
                Map::PlayerList const &pl = me->GetMap()->GetPlayers();
                for (Map::PlayerList::const_iterator itr = pl.begin(); itr != pl.end(); ++itr)
                    if (Player* plr = itr->GetSource())
                        if (plr->IsAlive() && plr != me->GetVictim() && !plr->IsGameMaster())
                            plrlist.push_back(plr);

                for (uint8 i = 0; i < RAID_MODE(1, 3); ++i)
                    if (!plrlist.empty())
                    {
                        uint8 index = urand(0, plrlist.size() - 1);
                        Player* p = plrlist[index];

                        if (Creature* cr = me->SummonCreature(NPC_FREYA_UNSTABLE_SUN_BEAM, p->GetPositionX(), p->GetPositionY(), p->GetPositionZ(), p->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000))
                        {
                            cr->SetDisplayId(INVISIBLE_DISPLAY_ID);
                            cr->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                            cr->CastSpell(cr, SPELL_UNSTABLE_SUN_VISUAL, true);
                            cr->CastSpell(cr, SPELL_UNSTABLE_SUN_FREYA_DAMAGE, true);

                            cr->CastSpell(cr, SPELL_UNSTABLE_SUN_BEAM_AURA, true);
                            cr->CastSpell(cr, SPELL_PHOTOSYNTHESIS, true);
                        }

                        plrlist.erase(plrlist.begin() + index);
                    }

                events.RepeatEvent(urand(40000, 45000));
                break;
            }

            DoMeleeAttackIfReady();
            EnterEvadeIfOutOfCombatArea();
        }

        bool CheckEvadeIfOutOfCombatArea() const
        {
            return me->GetPositionX() < 2135.0f;
        }
    };
};

class boss_freya_elder_stonebark : public CreatureScript
{
public:
    boss_freya_elder_stonebark() : CreatureScript("boss_freya_elder_stonebark") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_freya_elder_stonebarkAI (pCreature);
    }

    struct boss_freya_elder_stonebarkAI : public ScriptedAI
    {
        boss_freya_elder_stonebarkAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
        }

        EventMap events;
        uint8 _chargesCount;

        void Reset()
        {
            events.Reset();
            _chargesCount = 0;
        }

        void KilledUnit(Unit*)
        {
            if (urand(0,1))
                return;

            if (urand(0,1))
            {
                me->MonsterTextEmote("Angry roar", 0);
                me->PlayDirectSound(SOUND_STONEBARK_SLAY1);
            }
            else
            {
                me->MonsterYell("Such a waste.", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_STONEBARK_SLAY2);
            }
        }

        void JustDied(Unit* killer)
        {
            if (me->GetEntry() == killer->GetEntry())
                return;
            me->MonsterYell("Matron, flee! They are ruthless....", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(SOUND_STONEBARK_DEATH);

            // Lumberjacked
            if (me->GetInstanceScript())
                if (Creature* freya = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_FREYA)))
                    freya->AI()->DoAction(ACTION_LUMBERJACKED);
        }

        void EnterCombat(Unit*)
        {
            events.ScheduleEvent(EVENT_STONEBARK_FISTS_OF_STONE, 40000);
            events.ScheduleEvent(EVENT_STONEBARK_GROUND_TREMOR, 5000);
            events.ScheduleEvent(EVENT_STONEBARK_PETRIFIED_BARK, 20000);

            me->MonsterYell("This place will serve as your graveyard.", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(SOUND_STONEBARK_AGGRO);
        }

        void DamageTaken(Unit*, uint32& damage, DamageEffectType damageType, SpellSchoolMask damageSchoolMask)
        {
            if ((damageType == DIRECT_DAMAGE || (damageType == SPELL_DIRECT_DAMAGE && damageSchoolMask & SPELL_SCHOOL_MASK_NORMAL)) && _chargesCount)
            {
                --_chargesCount;
                damage = 0;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_STONEBARK_FISTS_OF_STONE:
                    me->CastSpell(me, SPELL_FISTS_OF_STONE, false);
                    events.RepeatEvent(60000);
                    break;
                case EVENT_STONEBARK_GROUND_TREMOR:
                    if (!me->HasAura(SPELL_FISTS_OF_STONE))
                        me->CastSpell(me, SPELL_GROUND_TREMOR, false);
                    events.RepeatEvent(20000);
                    break;
                case EVENT_STONEBARK_PETRIFIED_BARK:
                    _chargesCount = RAID_MODE(60, 120);
                    me->CastSpell(me, SPELL_PETRIFIED_BARK, false);
                    events.RepeatEvent(30000);
                    break;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class boss_freya_elder_brightleaf : public CreatureScript
{
public:
    boss_freya_elder_brightleaf() : CreatureScript("boss_freya_elder_brightleaf") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_freya_elder_brightleafAI (pCreature);
    }

    struct boss_freya_elder_brightleafAI : public ScriptedAI
    {
        boss_freya_elder_brightleafAI(Creature* pCreature) : ScriptedAI(pCreature), summons(pCreature)
        {
        }

        EventMap events;
        SummonList summons;

        void Reset()
        {
            events.Reset();
            summons.DespawnAll();
        }

        void KilledUnit(Unit*)
        {
            if (urand(0,1))
                return;

            if (urand(0,1))
            {
                me->MonsterYell("Fertilizer.", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_BRIGHTLEAF_SLAY1);
            }
            else
            {
                me->MonsterYell("Your corpse will nourish the soil!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_BRIGHTLEAF_SLAY2);
            }
        }

        void JustDied(Unit* killer)
        {
            summons.DespawnAll();

            if (me->GetEntry() == killer->GetEntry())
                return;
            me->MonsterYell("Matron, one has fallen!", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(SOUND_BRIGHTLEAF_DEATH);

            // Lumberjacked
            if (me->GetInstanceScript())
                if (Creature* freya = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_FREYA)))
                    freya->AI()->DoAction(ACTION_LUMBERJACKED);
        }

        void EnterCombat(Unit*)
        {
            events.ScheduleEvent(EVENT_BRIGHTLEAF_FLUX, 10000);
            events.ScheduleEvent(EVENT_BRIGHTLEAF_SOLAR_FLARE, 5000);
            events.ScheduleEvent(EVENT_BRIGHTLEAF_UNSTABLE_SUN_BEAM, 8000);

            me->MonsterYell("Matron, the Conservatory has been breached!", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(SOUND_BRIGHTLEAF_AGGRO);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_BRIGHTLEAF_FLUX:
                    if (Aura* aur = me->AddAura(SPELL_BRIGHTLEAF_FLUX, me))
                        aur->SetStackAmount(urand(1,10));
                    events.RepeatEvent(10000);
                    break;
                case EVENT_BRIGHTLEAF_SOLAR_FLARE:
                    if (Aura* aur = me->GetAura(SPELL_BRIGHTLEAF_FLUX))
                    {
                        me->CastCustomSpell(SPELL_SOLAR_FLARE, SPELLVALUE_MAX_TARGETS, aur->GetStackAmount(), me, false);
                        me->RemoveAura(aur);
                    }
                    events.RepeatEvent(15000);
                    break;
                case EVENT_BRIGHTLEAF_UNSTABLE_SUN_BEAM:
                    events.ScheduleEvent(EVENT_BRIGHTLEAF_DESPAWN_SUN_BEAM, 11000);
                    if (Creature* beam = me->SummonCreature(NPC_UNSTABLE_SUN_BRIGHTLEAF, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()))
                    {
                        beam->CastSpell(beam, SPELL_UNSTABLE_SUN_BEAM_AURA, true);
                        beam->CastSpell(beam, SPELL_PHOTOSYNTHESIS, true);
                        beam->CastSpell(beam, SPELL_UNSTABLE_SUN_FREYA_DAMAGE, true);
                        summons.Summon(beam);
                    }
                    if (Creature* beam = me->SummonCreature(NPC_UNSTABLE_SUN_BRIGHTLEAF, me->GetPositionX()+8, me->GetPositionY()+8, me->GetPositionZ()))
                    {
                        beam->CastSpell(beam, SPELL_UNSTABLE_SUN_BEAM_AURA, true);
                        beam->CastSpell(beam, SPELL_PHOTOSYNTHESIS, true);
                        beam->CastSpell(beam, SPELL_UNSTABLE_SUN_FREYA_DAMAGE, true);
                        summons.Summon(beam);
                    }
                    events.RepeatEvent(20000);
                    break;
                case EVENT_BRIGHTLEAF_DESPAWN_SUN_BEAM:
                    summons.DespawnAll();
                    events.PopEvent();
                    break;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class boss_freya_elder_ironbranch : public CreatureScript
{
public:
    boss_freya_elder_ironbranch() : CreatureScript("boss_freya_elder_ironbranch") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_freya_elder_ironbranchAI (pCreature);
    }

    struct boss_freya_elder_ironbranchAI : public ScriptedAI
    {
        boss_freya_elder_ironbranchAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me) { }

        void Reset()
        {
            events.Reset();
            DespawnRoots();
        }

        void KilledUnit(Unit*)
        {
            if (urand(0,1))
                return;

            if (urand(0,1))
            {
                me->MonsterYell("I return you whence you came!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_IRONBRANCH_SLAY1);
            }
            else
            {
                me->MonsterYell("BEGONE!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_IRONBRANCH_SLAY2);
            }
        }

        void DespawnRoots()
        {
            for (auto& summoned : summons)
            {
                if (Creature* root = ObjectAccessor::GetCreature(*me, summoned))
                    if (root->IsAlive())
                        Unit::Kill(me, root);
            }

            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon) override
        {
            summons.Summon(summon);
        }

        void JustDied(Unit* killer)
        {
            if (me->GetEntry() == killer->GetEntry())
                return;

            DespawnRoots();
            me->MonsterYell("Freya! They come for you.", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(SOUND_IRONBRANCH_DEATH);

            // Lumberjacked
            if (me->GetInstanceScript())
                if (Creature* freya = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_FREYA)))
                    freya->AI()->DoAction(ACTION_LUMBERJACKED);
        }

        void EnterCombat(Unit*)
        {
            events.ScheduleEvent(EVENT_IRONBRANCH_IMPALE, 10000);
            events.ScheduleEvent(EVENT_IRONBRANCH_IRON_ROOT, 15000);
            events.ScheduleEvent(EVENT_IRONBRANCH_THORN_SWARM, 3000);

            me->MonsterYell("Mortals have no place here!", LANG_UNIVERSAL, 0);
            me->PlayDirectSound(SOUND_IRONBRANCH_AGGRO);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_IRONBRANCH_IMPALE:
                    me->CastSpell(me->GetVictim(), SPELL_IMPALE, false);
                    events.RepeatEvent(17000);
                    break;
                case EVENT_IRONBRANCH_IRON_ROOT:
                    me->CastCustomSpell(SPELL_IRON_ROOTS, SPELLVALUE_MAX_TARGETS, 1, me, false);
                    events.RepeatEvent(20000);
                    break;
                case EVENT_IRONBRANCH_THORN_SWARM:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.f, true))
                        me->CastSpell(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), SPELL_THORN_SWARM, false);
                    events.RepeatEvent(14000);
                    break;
            }

            DoMeleeAttackIfReady();
        }
    private:
        SummonList summons;
        EventMap events;
    };
};

class boss_freya_iron_root : public CreatureScript
{
public:
    boss_freya_iron_root() : CreatureScript("boss_freya_iron_root") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_freya_iron_rootAI (pCreature);
    }

    struct boss_freya_iron_rootAI : public NullCreatureAI
    {
        boss_freya_iron_rootAI(Creature* pCreature) : NullCreatureAI(pCreature)
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);

            if (InstanceScript* instance = me->GetInstanceScript())
            {
                Creature* realSummoner = nullptr;

                if (me->GetEntry() == NPC_IRON_ROOT_TRIGGER)
                    realSummoner = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_ELDER_IRONBRANCH));
                else
                    realSummoner = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_FREYA));

                if (realSummoner && realSummoner->IsAIEnabled)
                    realSummoner->AI()->JustSummoned(me);
            }
        }

        void JustDied(Unit*)
        {
            if (!me->IsSummon())
                return;

            if (Unit* target = ObjectAccessor::GetUnit(*me, me->ToTempSummon()->GetSummonerGUID()))
            {
                if (me->GetEntry() == NPC_IRON_ROOT_TRIGGER) // Iron Branch spell
                    target->RemoveAura(target->GetMap()->Is25ManRaid() ? SPELL_IRON_ROOTS_DAMAGE_25 : SPELL_IRON_ROOTS_DAMAGE_10);
                else
                    target->RemoveAura(target->GetMap()->Is25ManRaid() ? SPELL_IRON_ROOTS_FREYA_DAMAGE_25 : SPELL_IRON_ROOTS_FREYA_DAMAGE_10);
            }
        }
    };
};

class boss_freya_lifebinder : public CreatureScript
{
public:
    boss_freya_lifebinder() : CreatureScript("boss_freya_lifebinder") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_freya_lifebinderAI (pCreature);
    }

    struct boss_freya_lifebinderAI : public NullCreatureAI
    {
        boss_freya_lifebinderAI(Creature* pCreature) : NullCreatureAI(pCreature)
        {
        }

        uint32 _healTimer;

        void Reset()
        {
            me->CastSpell(me, SPELL_LIFEBINDER_VISUAL, true);
            me->CastSpell(me, SPELL_LIFEBINDER_PHERONOMES, true);
            me->CastSpell(me, SPELL_AUTO_GROW, true);
            _healTimer = 0;
        }

        void UpdateAI(uint32 diff)
        {
            _healTimer += diff;
            if (_healTimer >= 12000)
            {
                me->RemoveAurasDueToSpell(SPELL_AUTO_GROW);
                me->CastSpell(me, me->GetMap()->Is25ManRaid() ? SPELL_LIFEBINDER_HEAL_25 : SPELL_LIFEBINDER_HEAL_10, true);
                me->DespawnOrUnsummon(2000);
                _healTimer = 0;
            }
        }
    };
};


class boss_freya_healthy_spore : public CreatureScript
{
public:
    boss_freya_healthy_spore() : CreatureScript("boss_freya_healthy_spore") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_freya_healthy_sporeAI (pCreature);
    }

    struct boss_freya_healthy_sporeAI : public NullCreatureAI
    {
        boss_freya_healthy_sporeAI(Creature* pCreature) : NullCreatureAI(pCreature) { }

        uint32 _despawnTimer;

        void Reset()
        {
            me->CastSpell(me, SPELL_POTENT_PHEROMONES, true);
            me->CastSpell(me, SPELL_HEALTHY_SPORE_VISUAL, true);
            me->CastSpell(me, SPELL_AUTO_GROW, true);
            _despawnTimer = 0;
        }

        void UpdateAI(uint32 diff)
        {
            _despawnTimer += diff;
            if (_despawnTimer >= 12000)
            {
                me->RemoveAurasDueToSpell(SPELL_AUTO_GROW);
                me->DespawnOrUnsummon(2200);
                _despawnTimer = 0;
            }
        }
    };
};

class boss_freya_summons : public CreatureScript
{
public:
    boss_freya_summons() : CreatureScript("boss_freya_summons") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_freya_summonsAI (pCreature);
    }

    struct boss_freya_summonsAI : public ScriptedAI
    {
        boss_freya_summonsAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            _freyaGUID = me->GetInstanceScript() ? me->GetInstanceScript()->GetData64(TYPE_FREYA) : 0;
            _isTrio = me->GetEntry() == NPC_ANCIENT_WATER_SPIRIT || me->GetEntry() == NPC_STORM_LASHER || me->GetEntry() == NPC_SNAPLASHER;
            _hasDied = false;
        }

        EventMap events;
        uint64 _freyaGUID;
        uint8 _stackCount;
        bool _hasDied;
        bool _isTrio;

        void Reset()
        {
            _stackCount = 0;
            events.Reset();
            if (me->GetEntry() == NPC_DETONATING_LASHER)
            {
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
                me->SetReactState(REACT_PASSIVE);
                me->SetControlled(true, UNIT_STATE_ROOT);
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, 9);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                events.ScheduleEvent(EVENT_DETONATING_LASHER_START_ATTACK, 2000);
                events.ScheduleEvent(EVENT_DETONATING_LASHER_ANIM, 1000);
            }
            else
                DoZoneInCombat(me, 250.0f);

            if (me->GetEntry() == NPC_STORM_LASHER)
                DoCastSelf(SPELL_STORM_LASHER_VISUAL);
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (me->GetEntry() != NPC_DETONATING_LASHER)
                ScriptedAI::MoveInLineOfSight(who);
        }

        uint32 GetNatureReductionSpell()
        {
            switch (me->GetEntry())
            {
                case NPC_DETONATING_LASHER:
                    return SPELL_NATURE_REMOVE_2;
                case NPC_SNAPLASHER:
                case NPC_ANCIENT_WATER_SPIRIT:
                case NPC_STORM_LASHER:
                    return SPELL_NATURE_REMOVE_10;
                case NPC_ANCIENT_CONSERVATOR:
                    return SPELL_NATURE_REMOVE_25;
            }

            return SPELL_NATURE_REMOVE_2;
        }

        void JustDied(Unit*)
        {
            if (Creature* freya = ObjectAccessor::GetCreature(*me, _freyaGUID))
            {
                if (!_hasDied)
                {
                    me->CastSpell(freya, GetNatureReductionSpell(), true);
                    freya->AI()->DoAction(_stackCount);
                }

                if (_isTrio)
                {
                    freya->AI()->DoAction(ACTION_RESPAWN_TRIO);
                    _hasDied = true;
                }
            }
            if (me->GetEntry() == NPC_DETONATING_LASHER)
                me->CastSpell(me, SPELL_DETONATE, true);
        }

        void DoAction(int32 param)
        {
            if (_isTrio && param == ACTION_RESPAWN_TRIO)
            {
                me->setDeathState(JUST_RESPAWNED);
                Reset();
            }
            else if (_isTrio && param == ACTION_DESPAWN_COMPLETELY)
                me->DespawnOrUnsummon();
        }

        void EnterCombat(Unit* who)
        {
            if (me->GetEntry() == NPC_ANCIENT_CONSERVATOR)
            {
                me->CastSpell(me, SPELL_HEALTHY_SPORE_SUMMON, true);
                me->CastSpell(me, SPELL_CONSERVATOR_GRIP, false);
                events.ScheduleEvent(EVENT_ANCIENT_CONSERVATOR_NATURE_FURY, 14000);
                _stackCount = ACTION_REMOVE_25_STACK;
            }
            else if (me->GetEntry() == NPC_ANCIENT_WATER_SPIRIT)
            {
                events.ScheduleEvent(EVENT_WATER_SPIRIT_CHARGE, 12000);
                _stackCount = ACTION_REMOVE_10_STACK;
            }
            else if (me->GetEntry() == NPC_STORM_LASHER)
            {
                events.ScheduleEvent(EVENT_STORM_LASHER_LIGHTNING_LASH, 10000);
                events.ScheduleEvent(EVENT_STORM_LASHER_STORMBOLT, 6000);
                _stackCount = ACTION_REMOVE_10_STACK;
            }
            else if (me->GetEntry() == NPC_DETONATING_LASHER)
            {
                events.RescheduleEvent(EVENT_DETONATING_LASHER_ANIM, 0);
                events.ScheduleEvent(EVENT_DETONATING_LASHER_FLAME_LASH, 5000);
                events.ScheduleEvent(EVENT_DETONATING_LASHER_CHANGE_TARGET, 7500);
                _stackCount = ACTION_REMOVE_2_STACK;
            }
            else if (me->GetEntry() == NPC_SNAPLASHER)
            {
                me->CastSpell(me, SPELL_HARDENED_BARK, true);

                _stackCount = ACTION_REMOVE_10_STACK;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && me->GetEntry() != NPC_DETONATING_LASHER)
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_ANCIENT_CONSERVATOR_NATURE_FURY:
                    for (uint8 i = 0; i < RAID_MODE(1, 2); ++i)
                    {
                        if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 1, 200, true, -SPELL_NATURE_FURY))
                            me->CastSpell(target, SPELL_NATURE_FURY, true);
                    }
                    events.RepeatEvent(14000);
                    break;
                case EVENT_WATER_SPIRIT_CHARGE:
                    me->CastSpell(me, SPELL_TIDAL_WAVE_AURA, true);
                    me->CastSpell(me->GetVictim(), SPELL_TIDAL_WAVE, false);
                    events.RepeatEvent(12000);
                    break;
                case EVENT_STORM_LASHER_LIGHTNING_LASH:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.f, true))
                        me->CastSpell(target, SPELL_LIGHTNING_LASH, false);
                    events.RepeatEvent(10000);
                    break;
                case EVENT_STORM_LASHER_STORMBOLT:
                    me->CastSpell(me->GetVictim(), SPELL_STORMBOLT, false);
                    events.RepeatEvent(6000);
                    break;
                case EVENT_DETONATING_LASHER_FLAME_LASH:
                    DoCastVictim(SPELL_FLAME_LASH);
                    events.RepeatEvent(urand(5000, 10000));
                    break;
                case EVENT_DETONATING_LASHER_START_ATTACK:
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    me->SetReactState(REACT_AGGRESSIVE);
                    DoZoneInCombat(me, 250.0f);
                    events.PopEvent();
                    break;
                case EVENT_DETONATING_LASHER_CHANGE_TARGET:
                    if (Unit* target = SelectTargetFromPlayerList(80))
                    {
                        // Switching to other target - modify aggro of new target by 20% from current target's aggro
                        if (me->GetVictim())
                            me->AddThreat(target, me->getThreatManager().getThreat(me->GetVictim(), false) * 1.2f);
                        AttackStart(target);
                    }
                    else
                        me->DespawnOrUnsummon(1);
                    events.RepeatEvent(urand(5000, 10000));
                    break;
                case EVENT_DETONATING_LASHER_ANIM:
                    me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                    events.PopEvent();
                    break;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class boss_freya_nature_bomb : public CreatureScript
{
public:
    boss_freya_nature_bomb() : CreatureScript("boss_freya_nature_bomb") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_freya_nature_bombAI (pCreature);
    }

    struct boss_freya_nature_bombAI : public NullCreatureAI
    {
        boss_freya_nature_bombAI(Creature* pCreature) : NullCreatureAI(pCreature)
        {
            _goGUID = 0;
            _exploded = false;
        }

        uint64 _goGUID;
        uint32 _explodeTimer;
        uint32 _despawnTimer;
        bool _exploded;

        void EnterEvadeMode() override { }
        void AttackStart(Unit* /*who*/) override { }
        void EnterCombat(Unit* /*who*/) override { }
        void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override { damage = 0; }

        void Reset() override
        {
            me->SetDisplayId(MODEL_INVISIBLE_NATURE_BOMB);

            _explodeTimer = 0;
            _despawnTimer = 0;
            DoCast(SPELL_NATURE_BOMB_SUMMON);
        }

        void SetGUID(uint64 guid, int32 /*data*/) override
        {
            _goGUID = guid;
        }

        void UpdateAI(uint32 diff) override
        {
            _explodeTimer += diff;
            _despawnTimer += diff;

            if (_explodeTimer >= 10000 && !_exploded)
            {
                _exploded = true;
                me->CastSpell(me, me->GetMap()->Is25ManRaid() ? SPELL_NATURE_BOMB_DAMAGE_25 : SPELL_NATURE_BOMB_DAMAGE_10, false);
                _explodeTimer = 0;
                if (GameObject* go = ObjectAccessor::GetGameObject(*me, _goGUID))
                    go->SetGoState(GO_STATE_ACTIVE);
            }

            if (_despawnTimer >= 14000)
            {
                _despawnTimer = 0;
                if (GameObject* go = ObjectAccessor::GetGameObject(*me, _goGUID))
                    go->SetLootState(LootState::GO_JUST_DEACTIVATED);
                me->DespawnOrUnsummon();
            }
        }
    };
};

class achievement_freya_getting_back_to_nature : public AchievementCriteriaScript
{
    public:
        achievement_freya_getting_back_to_nature() : AchievementCriteriaScript("achievement_freya_getting_back_to_nature") {}

        bool OnCheck(Player* player, Unit* target /*Freya*/)
        {
            if (target)
                if (target->GetAI()->GetData(DATA_BACK_TO_NATURE))
                    return true;
            return false;
        }
};

class achievement_freya_knock_on_wood : public AchievementCriteriaScript
{
    public:
        achievement_freya_knock_on_wood(char const* name, uint32 count) : AchievementCriteriaScript(name),
            _elderCount(count)
        {
        }

        bool OnCheck(Player* player, Unit* target /*Freya*/)
        {
            return target && _elderCount <= target->GetAI()->GetData(DATA_GET_ELDER_COUNT);
        }

    private:
        uint32 const _elderCount;
};

class spell_ancient_summon_healthy_spores_periodic_SpellScript : public AuraScript
{
    PrepareAuraScript(spell_ancient_summon_healthy_spores_periodic_SpellScript);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        PreventDefaultAction();

        GetCaster()->CastSpell((Unit*)nullptr, SPELL_HEALTHY_SPORE_NW, true);
        GetCaster()->CastSpell((Unit*)nullptr, SPELL_HEALTHY_SPORE_NE, true);
        GetCaster()->CastSpell((Unit*)nullptr, SPELL_HEALTHY_SPORE_SE, true);
        GetCaster()->CastSpell((Unit*)nullptr, SPELL_HEALTHY_SPORE_SW, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_ancient_summon_healthy_spores_periodic_SpellScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_ancient_water_spirit_tidal_wave_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_ancient_water_spirit_tidal_wave_SpellScript);

    void HandleCast()
    {
        if (GetCaster())
            if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF))
                GetCaster()->CastSpell((Unit*)nullptr, GetCaster()->GetMap()->Is25ManRaid() ? SPELL_TIDAL_WAVE_DAMAGE_25 : SPELL_TIDAL_WAVE_DAMAGE_10, true);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_ancient_water_spirit_tidal_wave_SpellScript::HandleCast);
    }
};

class spell_freya_attuned_to_nature_dose_reduction_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_freya_attuned_to_nature_dose_reduction_SpellScript);

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        if (!GetCaster() || GetCaster()->GetTypeId() != TYPEID_UNIT)
            return;

        Creature* target = GetHitCreature();
        if (!target)
            return;
        SpellInfo const* spellInfo = GetSpellInfo();
        switch (spellInfo->Id)
        {
            case SPELL_NATURE_REMOVE_2:
                if (target->HasAura(SPELL_ATTUNED_TO_NATURE))
                    for (uint8 n = 0; n < 2; ++n)
                        target->RemoveAuraFromStack(GetEffectValue(), 0, AURA_REMOVE_BY_DEFAULT);
                break;
            case SPELL_NATURE_REMOVE_10:
                if (target->HasAura(SPELL_ATTUNED_TO_NATURE))
                    for (uint8 n = 0; n < 10; ++n)
                        target->RemoveAuraFromStack(GetEffectValue(), 0, AURA_REMOVE_BY_DEFAULT);
                break;
            case SPELL_NATURE_REMOVE_25:
                if (target->HasAura(SPELL_ATTUNED_TO_NATURE))
                    for (uint8 n = 0; n < 25; ++n)
                        target->RemoveAuraFromStack(GetEffectValue(), 0, AURA_REMOVE_BY_DEFAULT);
                break;
            default:
                break;
        }

        if (!target->HasAura(GetEffectValue()))
            if (target->IsAIEnabled && target->IsInCombat() && !target->IsInEvadeMode())
                target->AI()->SetData(DATA_FREYA_START_PHASE_TWO, DATA_FREYA_START_PHASE_TWO);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_freya_attuned_to_nature_dose_reduction_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class spell_freya_nature_bomb_selector_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_freya_nature_bomb_selector_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([](WorldObject* object)
        {
            return !object->IsPlayer();
        });

        if (targets.empty())
            return;

        bool Is25ManRaid = GetCaster()->GetMap()->Is25ManRaid();
        Trinity::Containers::RandomResize(targets, Is25ManRaid ? 12 : 5);
    }

    void HandleLaunch(SpellEffIndex /*effIndex*/)
    {
        if (GetCaster() && GetHitUnit())
            GetCaster()->CastSpell(GetHitUnit(), SPELL_NATURE_BOMB_FLIGHT, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_freya_nature_bomb_selector_SpellScript::HandleLaunch, EFFECT_0, SPELL_EFFECT_FORCE_CAST);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_freya_nature_bomb_selector_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

class spell_summon_nature_bomb_freya_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_summon_nature_bomb_freya_SpellScript);

    void HandleSummon(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);

        if (GetCaster() && GetCaster()->IsInWorld() && !GetCaster()->IsDuringRemoveFromWorld())
        {
            Position pos = GetCaster()->GetPosition();
            pos.m_positionZ = GetCaster()->GetMap()->GetHeight(pos.GetPositionX(), pos.GetPositionY(), MAX_HEIGHT);
            GetCaster()->SummonCreature(NPC_NATURE_BOMB, pos);
            std::cout << "pos x: " << std::to_string(pos.GetPositionX()) << " " << std::to_string(pos.GetPositionY()) << " " << std::to_string(pos.GetPositionZ()) << "\n" << std::endl;
        }
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_summon_nature_bomb_freya_SpellScript::HandleSummon, EFFECT_0, SPELL_EFFECT_SUMMON);
    }
};

void AddSC_boss_freya()
{
    new boss_freya();
    new boss_freya_elder_stonebark();
    new boss_freya_elder_brightleaf();
    new boss_freya_elder_ironbranch();
    new boss_freya_iron_root();
    new boss_freya_lifebinder();
    new boss_freya_healthy_spore();
    new boss_freya_summons();
    new boss_freya_nature_bomb();

    new AuraScriptLoaderEx<spell_ancient_summon_healthy_spores_periodic_SpellScript>("spell_ancient_summon_healthy_spores_periodic");
    new SpellScriptLoaderEx<spell_ancient_water_spirit_tidal_wave_SpellScript>("spell_ancient_water_spirit_tidal_wave");
    new SpellScriptLoaderEx<spell_freya_attuned_to_nature_dose_reduction_SpellScript>("spell_freya_attuned_to_nature_dose_reduction");
    new SpellScriptLoaderEx<spell_freya_nature_bomb_selector_SpellScript>("spell_freya_nature_bomb_selector");
    new SpellScriptLoaderEx<spell_summon_nature_bomb_freya_SpellScript>("spell_summon_nature_bomb_freya");

    new achievement_freya_getting_back_to_nature();
    new achievement_freya_knock_on_wood("achievement_freya_knock_on_wood", 1);
    new achievement_freya_knock_on_wood("achievement_freya_knock_knock_on_wood", 2);
    new achievement_freya_knock_on_wood("achievement_freya_knock_knock_knock_on_wood", 3);
}
