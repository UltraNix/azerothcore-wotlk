#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "ulduar.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "PassiveAI.h"
#include "Player.h"
#include "GridNotifiers.h"

enum HodirSpellData
{
    SPELL_BERSERK                           = 26662,

    SPELL_BITING_COLD_BOSS_AURA             = 62038,
    SPELL_BITING_COLD_PLAYER_AURA           = 62039,
    SPELL_BITING_COLD_DAMAGE                = 62188,

    SPELL_FREEZE                            = 62469,

    SPELL_FLASH_FREEZE_CAST                 = 61968,
    SPELL_FLASH_FREEZE_INSTAKILL            = 62226,
    SPELL_FLASH_FREEZE_TRAPPED_PLAYER       = 61969,
    SPELL_FLASH_FREEZE_TRAPPED_NPC          = 61990,
    SPELL_FLASH_FREEZE_VISUAL               = 62148,
    SPELL_SAFE_AREA                         = 65705,
    SPELL_SAFE_AREA_TRIGGERED               = 62464,

    SPELL_ICICLE_BOSS_AURA                  = 62227,
    SPELL_ICICLE_TBBA                       = 63545,

    SPELL_ICICLE_FLASH_SELECTOR             = 62476,
    SPELL_ICICLE_VISUAL_UNPACKED            = 62234,
    SPELL_ICICLE_VISUAL_PACKED              = 62462,
    SPELL_ICICLE_VISUAL_FALLING             = 62453,
    SPELL_ICICLE_FALL_EFFECT_UNPACKED       = 62236,
    SPELL_ICICLE_FALL_EFFECT_PACKED         = 62460,
    SPELL_ICE_SHARDS_SMALL                  = 62457,
    SPELL_ICE_SHARDS_BIG                    = 65370,
    SPELL_SNOWDRIFT                         = 62463,

    SPELL_FROZEN_BLOWS_10                   = 62478,
    SPELL_FROZEN_BLOWS_25                   = 63512,

    // Helpers:
    SPELL_PRIEST_DISPELL_MAGIC              = 63499,
    SPELL_PRIEST_GREAT_HEAL                 = 62809,
    SPELL_PRIEST_SMITE                      = 61923,

    SPELL_DRUID_WRATH                       = 62793,
    SPELL_DRUID_STARLIGHT_AREA_AURA         = 62807,

    SPELL_SHAMAN_LAVA_BURST                 = 61924,
    SPELL_SHAMAN_STORM_CLOUD_10             = 65123,
    SPELL_SHAMAN_STORM_CLOUD_25             = 65133,
    SPELL_SHAMAN_STORM_POWER_10             = 63711,
    SPELL_SHAMAN_STORM_POWER_25             = 65134,

    SPELL_MAGE_FIREBALL                     = 61909,
    SPELL_MAGE_MELT_ICE                     = 64528,
    SPELL_MAGE_CONJURE_TOASTY_FIRE          = 62823,
    SPELL_MAGE_SUMMON_TOASTY_FIRE           = 62819,
    SPELL_MAGE_TOASTY_FIRE_AURA             = 62821,
    SPELL_SINGED                            = 65280
};

enum HodirNPCs
{
    //NPC_HODIR                             = 32845,

    // Hodir's Helper NPCs
    NPC_TOR_GREYCLOUD                       = 32941,
    NPC_KAR_GREYCLOUD                       = 33333,
    NPC_EIVI_NIGHTFEATHER                   = 33325,
    NPC_ELLIE_NIGHTFEATHER                  = 32901,
    NPC_SPIRITWALKER_TARA                   = 33332,
    NPC_SPIRITWALKER_YONA                   = 32950,
    NPC_ELEMENTALIST_MAHFUUN                = 33328,
    NPC_ELEMENTALIST_AVUUN                  = 32900,
    NPC_AMIRA_BLAZEWEAVER                   = 33331,
    NPC_VEESHA_BLAZEWEAVER                  = 32946,
    NPC_MISSY_FLAMECUFFS                    = 32893,
    NPC_SISSY_FLAMECUFFS                    = 33327,
    NPC_BATTLE_PRIEST_ELIZA                 = 32948,
    NPC_BATTLE_PRIEST_GINA                  = 33330,
    NPC_FIELD_MEDIC_PENNY                   = 32897,
    NPC_FIELD_MEDIC_JESSI                   = 33326,

    NPC_FLASH_FREEZE_PLR                    = 32926,
    NPC_FLASH_FREEZE_NPC                    = 32938,
    NPC_ICICLE_UNPACKED                     = 33169,
    NPC_ICICLE_PACKED                       = 33173,
    NPC_TOASTY_FIRE                         = 33342
};

enum HodirGOs
{
    GO_HODIR_SNOWDRIFT                      = 194173,
    // GO_HODIR_FROZEN_DOOR                 = 194441,
    // GO_HODIR_DOOR                        = 194634,
};

enum HodirEvents
{
    // Hodir:
    EVENT_FLASH_FREEZE                      = 1,
    EVENT_FROZEN_BLOWS                      = 2,
    EVENT_BERSERK                           = 3,
    EVENT_FREEZE                            = 4,
    EVENT_SMALL_ICICLES_ENABLE              = 5,
    EVENT_HARD_MODE_MISSED                  = 6,

    EVENT_TRY_FREE_HELPER                   = 10,
    EVENT_PRIEST_DISPELL_MAGIC              = 11,
    EVENT_PRIEST_GREAT_HEAL                 = 12,
    EVENT_PRIEST_SMITE                      = 13,
    EVENT_DRUID_WRATH                       = 14,
    EVENT_DRUID_STARLIGHT                   = 15,
    EVENT_SHAMAN_LAVA_BURST                 = 16,
    EVENT_SHAMAN_STORM_CLOUD                = 17,
    EVENT_MAGE_TOASTY_FIRE                  = 18,
    EVENT_MAGE_FIREBALL                     = 19,
    EVENT_MAGE_MELT_ICE                     = 20
};

enum HodirMisc
{
    DATA_FRIENDS_COUNT_25                   = 8,
    DATA_FRIENDS_COUNT_10                   = 4,
    DATA_SPAWN_ENCOUNTER_HELPERS            = 5
};

Position const SummonPositions25[8] =
{
    { 2021.12f, -236.65f, 432.767f, 1.57f }, // Field Medic Penny    &&  Battle-Priest Eliza
    { 2014.18f, -232.80f, 432.767f, 1.57f }, // Eivi Nightfeather    &&  Tor Greycloud
    { 1999.90f, -230.49f, 432.767f, 1.57f }, // Elementalist Mahfuun &&  Spiritwalker Tara
    { 2028.10f, -244.66f, 432.767f, 1.57f }, // Missy Flamecuffs     &&  Amira Blazeweaver
    { 1983.75f, -243.36f, 432.767f, 1.57f }, // Field Medic Jessi    &&  Battle-Priest Gina
    { 1976.60f, -233.53f, 432.767f, 1.57f }, // Ellie Nightfeather   &&  Kar Greycloud
    { 2010.06f, -243.45f, 432.767f, 1.57f }, // Elementalist Avuun   &&  Spiritwalker Yona
    { 1992.90f, -237.54f, 432.767f, 1.57f }, // Sissy Flamecuffs     &&  Veesha Blazeweaver
};

Position const SummonPositions10[4] =
{
    { 1999.90f, -230.49f, 432.767f, 1.57f }, // Eivi Nightfeather    &&  Tor Greycloud
    { 2014.18f, -232.80f, 432.767f, 1.57f }, // Field Medic Penny    &&  Battle-Priest Eliza
    { 1992.90f, -237.54f, 432.767f, 1.57f }, // Missy Flamecuffs     &&  Amira Blazeweaver
    { 2010.06f, -243.45f, 432.767f, 1.57f }, // Elementalist Avuun   &&  Spiritwalker Yona
};

uint32 const Entry25Alliance[8] =
{
    NPC_FIELD_MEDIC_PENNY,
    NPC_EIVI_NIGHTFEATHER,
    NPC_ELEMENTALIST_MAHFUUN,
    NPC_MISSY_FLAMECUFFS,
    NPC_FIELD_MEDIC_JESSI,
    NPC_ELLIE_NIGHTFEATHER,
    NPC_ELEMENTALIST_AVUUN,
    NPC_SISSY_FLAMECUFFS
};

uint32 const Entry10Alliance[4] =
{
    NPC_EIVI_NIGHTFEATHER,
    NPC_FIELD_MEDIC_PENNY,
    NPC_MISSY_FLAMECUFFS,
    NPC_ELEMENTALIST_AVUUN
};

uint32 const Entry25Horde[8] =
{
    NPC_BATTLE_PRIEST_ELIZA,
    NPC_TOR_GREYCLOUD,
    NPC_SPIRITWALKER_TARA,
    NPC_AMIRA_BLAZEWEAVER,
    NPC_BATTLE_PRIEST_GINA,
    NPC_KAR_GREYCLOUD,
    NPC_SPIRITWALKER_YONA,
    NPC_VEESHA_BLAZEWEAVER
};

uint32 const Entry10Horde[4] =
{
    NPC_TOR_GREYCLOUD,
    NPC_BATTLE_PRIEST_ELIZA,
    NPC_AMIRA_BLAZEWEAVER,
    NPC_SPIRITWALKER_YONA
};

class DelayedHelperSpawn : public BasicEvent
{
public:
    DelayedHelperSpawn(Unit* me) : _me(me) { }

    bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
    {
        if (_me->IsAIEnabled)
            _me->GetAI()->DoAction(DATA_SPAWN_ENCOUNTER_HELPERS);
        return true;
    }

private:
    Unit * _me;
};

#define SPELL_FROZEN_BLOWS                  RAID_MODE(SPELL_FROZEN_BLOWS_10, SPELL_FROZEN_BLOWS_25)
#define SPELL_SHAMAN_STORM_CLOUD            RAID_MODE(SPELL_SHAMAN_STORM_CLOUD_10, SPELL_SHAMAN_STORM_CLOUD_25)

#define TEXT_HODIR_AGGRO                    "You will suffer for this trespass!"
#define TEXTEMOTE_HODIR_FROZEN_BLOWS        "Hodir roars furious."
#define TEXT_HODIR_FLASH_FREEZE             "Winds of the north consume you!"
#define TEXTEMOTE_HODIR_HARD_MODE_MISSED    "Hodir shatters the Rare Cache of Hodir!"
#define TEXT_HODIR_SLAIN_1                  "Tragic. To come so far, only to fail."
#define TEXT_HODIR_SLAIN_2                  "Welcome to the endless winter."
#define TEXT_HODIR_BERSERK                  "Enough! This ends now!"
#define TEXT_HODIR_DEFEATED                 "I... I am released from his grasp... at last."

enum HodirSounds
{
    SOUND_HODIR_AGGRO                       = 15552,
    SOUND_HODIR_SLAIN_1                     = 15553,
    SOUND_HODIR_SLAIN_2                     = 15554,
    SOUND_HODIR_FLASH_FREEZE                = 15555,
    SOUND_HODIR_FROZEN_BLOWS                = 15556,
    SOUND_HODIR_DEFEATED                    = 15557,
    SOUND_HODIR_BERSERK                     = 15558
};

class boss_hodir : public CreatureScript
{
public:
    boss_hodir() : CreatureScript("boss_hodir") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_hodirAI(pCreature);
    }

    struct boss_hodirAI : public ScriptedAI
    {
        boss_hodirAI(Creature *pCreature) : ScriptedAI(pCreature), summons(me), _normalChest(0), _hardmodeChest(0)
        {
            pInstance = pCreature->GetInstanceScript();
            if (!me->IsAlive())
                if (pInstance)
                    pInstance->SetData(TYPE_HODIR, DONE);
        }

        void DoAction(int32 action) override
        {
            if (action == DATA_SPAWN_ENCOUNTER_HELPERS)
                DoSummonHelpers();
        }

        void DoSummonHelpers()
        {
            if (!pInstance)
                return;

            bool IsTeamHorde = true;
            uint32 instanceTeamData = pInstance->GetData(DATA_GET_INSTANCE_TEAM_ID);

            if (!instanceTeamData)
                IsTeamHorde = false;

            //! neither horde or alliance, do a fallback search
            if (instanceTeamData > 2)
            {
                auto& _players = me->GetMap()->GetPlayers();
                for (auto iter : _players)
                {
                    if (iter.GetSource()->IsGameMaster())
                        continue;

                    //! break the loop at first valid source
                    //! if its alliance then team in instance is not horde else just leave it as true and break the loop
                    if (iter.GetSource()->GetTeamId() == TEAM_ALLIANCE)
                    {
                        IsTeamHorde = false;
                        break;
                    }
                    else
                        break;
                }
            }

            if (Is25ManRaid())
            {
                for (uint8 n = 0; n < DATA_FRIENDS_COUNT_25; ++n)
                {
                    if (Creature* FrozenHelper = me->SummonCreature(IsTeamHorde ? Entry25Horde[n] : Entry25Alliance[n], SummonPositions25[n], TEMPSUMMON_MANUAL_DESPAWN))
                    {
                        if (Creature* c = FrozenHelper->SummonCreature(NPC_FLASH_FREEZE_NPC, FrozenHelper->GetPositionX(), FrozenHelper->GetPositionY(), FrozenHelper->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 2000))
                        {
                            c->CastSpell(FrozenHelper, SPELL_FLASH_FREEZE_TRAPPED_NPC, true);
                        }
                        FrozenHelper->SetFlag(UNIT_FIELD_FLAGS, (UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC));
                        _helpers.push_back(FrozenHelper->GetGUID());
                    }
                }
            }
            else
            {
                for (uint8 n = 0; n < DATA_FRIENDS_COUNT_10; ++n)
                {
                    if (Creature* FrozenHelper = me->SummonCreature(IsTeamHorde ? Entry10Horde[n] : Entry10Alliance[n], SummonPositions10[n], TEMPSUMMON_MANUAL_DESPAWN))
                    {
                        if (Creature* c = FrozenHelper->SummonCreature(NPC_FLASH_FREEZE_NPC, FrozenHelper->GetPositionX(), FrozenHelper->GetPositionY(), FrozenHelper->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 2000))
                        {
                            c->CastSpell(FrozenHelper, SPELL_FLASH_FREEZE_TRAPPED_NPC, true);
                        }
                        FrozenHelper->SetFlag(UNIT_FIELD_FLAGS, (UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC));
                        _helpers.push_back(FrozenHelper->GetGUID());
                    }
                }
            }
        }

        void SpawnChests()
        {
            if (!_normalChest && !_hardmodeChest)
            {
                // spawn appropriate chests
                uint32 chestId = me->GetMap()->Is25ManRaid() ? GO_HODIR_CHEST_NORMAL_HERO : GO_HODIR_CHEST_NORMAL;
                if (GameObject* go = me->GetMap()->SummonGameObject(chestId, 1969.115f, -212.94f, 432.687f, 3.14f, 0, 0, 0, 0, 0))
                {
                    go->SetSpellId(1);
                    _normalChest = go->GetGUID();
                    go->SetUInt32Value(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                }

                uint32 chestId2 = me->GetMap()->Is25ManRaid() ? GO_HODIR_CHEST_HARD_HERO : GO_HODIR_CHEST_HARD;
                if (GameObject* go = me->GetMap()->SummonGameObject(chestId2, 2031.207f, -213.236f, 432.687f, 3.14f, 0, 0, 0, 0, 0))
                {
                    go->SetSpellId(1);
                    _hardmodeChest = go->GetGUID();
                    go->SetUInt32Value(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                }
            }
            else
            {
                if (GameObject* normalChest = ObjectAccessor::GetGameObject(*me, _normalChest))
                    normalChest->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);

                if (GameObject* hardmodeChest = ObjectAccessor::GetGameObject(*me, _hardmodeChest))
                {
                    hardmodeChest->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                    hardmodeChest->SetPhaseMask(1, true);
                }
            }
        }

        void Reset()
        {
            _fightTimer = 0;
            me->SetReactState(REACT_DEFENSIVE);
            events.Reset();
            summons.DespawnAll();
            _helpers.clear();
            hardmode = true;
            bAchievCheese = true;
            bAchievGettingCold = true;
            bAchievCoolestFriends = true;

            if (pInstance && pInstance->GetData(TYPE_HODIR) != DONE)
            {
                SpawnChests();
                pInstance->SetData(TYPE_HODIR, NOT_STARTED);
                me->m_Events.AddEvent(new DelayedHelperSpawn(me), me->m_Events.CalculateTime(4000));
            }

            if (pInstance)
            {
                pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BITING_COLD_PLAYER_AURA);
                if (GameObject* door = ObjectAccessor::GetGameObject(*me, pInstance->GetData64(GO_HODIR_ENTRANCE_DOOR)))
                {
                    door->SetGoState(GOState::GO_STATE_ACTIVE);
                }
            }
        }

        void EnterCombat(Unit* pWho)
        {
            _fightTimer = getMSTime();
            me->SetReactState(REACT_AGGRESSIVE);
            me->setActive(true);
            me->CastSpell(me, SPELL_BITING_COLD_BOSS_AURA, true);
            SmallIcicles(true);
            events.Reset();
            events.RescheduleEvent(EVENT_FLASH_FREEZE, 60s);
            events.RescheduleEvent(EVENT_FREEZE, 15s);
            if (sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF))
                events.RescheduleEvent(EVENT_HARD_MODE_MISSED, 2min);
            else
                events.RescheduleEvent(EVENT_HARD_MODE_MISSED, 3min);
            events.ScheduleEvent(EVENT_BERSERK, 8min);

            me->MonsterYell(TEXT_HODIR_AGGRO, LANG_UNIVERSAL, 0);
            me->PlayDirectSound(SOUND_HODIR_AGGRO, 0);

            if (pInstance && pInstance->GetData(TYPE_HODIR) != DONE)
                pInstance->SetData(TYPE_HODIR, IN_PROGRESS);

            for (auto& guid : _helpers)
            {
                if (Creature* helper = ObjectAccessor::GetCreature(*me, guid))
                    helper->RemoveFlag(UNIT_FIELD_FLAGS, (UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC));
            }

            if (pInstance)
                if (GameObject* door = ObjectAccessor::GetGameObject(*me, pInstance->GetData64(GO_HODIR_ENTRANCE_DOOR)))
                    door->SetGoState(GOState::GO_STATE_READY);
        }

        void JustReachedHome() { me->setActive(false); }

        void SmallIcicles(bool enable)
        {
            if (enable)
                me->CastSpell(me, SPELL_ICICLE_BOSS_AURA, true);
            else
                me->RemoveAura(SPELL_ICICLE_BOSS_AURA);
        }

        void SpellHitTarget(Unit* target, const SpellInfo* spell)
        {
            switch (spell->Id)
            {
                case SPELL_ICICLE_TBBA:
                    target->CastSpell(target, SPELL_ICICLE_VISUAL_UNPACKED, true);
                    break;
                case SPELL_FLASH_FREEZE_VISUAL:
                {
                    std::list<Creature*> fires;
                    me->GetCreaturesWithEntryInRange(fires, 200.0f, NPC_TOASTY_FIRE);
                    for (std::list<Creature*>::iterator itr = fires.begin(); itr != fires.end(); ++itr)
                        (*itr)->AI()->DoAction(1); // remove it
                    break;
                }
                default:
                    break;
            }
        }

        void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask)
        {
            if (damage >= me->GetHealth() || me->GetHealth() < 150000)
            {
                damage = 0;
                me->SetReactState(REACT_PASSIVE);
                if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                {
                    if (pInstance)
                    {
                        pInstance->SetData(TYPE_HODIR, DONE);
                        me->CastSpell(me, 64899, true); // credit
                    }

                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->setFaction(35);
                    me->GetMotionMaster()->Clear();
                    me->AttackStop();
                    me->CombatStop();
                    me->InterruptNonMeleeSpells(true);
                    me->RemoveAllAuras();
                    pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BITING_COLD_PLAYER_AURA);

                    events.Reset();
                    summons.DespawnAll();
                    _helpers.clear();

                    if (pInstance)
                    {
                        if (GameObject* d = ObjectAccessor::GetGameObject(*me, pInstance->GetData64(GO_HODIR_FROZEN_DOOR)))
                        {
                            if (d->GetGoState() != GO_STATE_ACTIVE)
                            {
                                d->SetLootState(GO_READY);
                                d->UseDoorOrButton(0, false);
                            }
                        }

                        if (GameObject* d = ObjectAccessor::GetGameObject(*me, pInstance->GetData64(GO_HODIR_DOOR)))
                        {
                            if (d->GetGoState() != GO_STATE_ACTIVE)
                            {
                                d->SetLootState(GO_READY);
                                d->UseDoorOrButton(0, false);
                            }
                        }
                    }

                    std::list<Creature*> fires;
                    me->GetCreaturesWithEntryInRange(fires, 200.0f, NPC_TOASTY_FIRE);
                    for (std::list<Creature*>::iterator itr = fires.begin(); itr != fires.end(); ++itr)
                        (*itr)->AI()->DoAction(1); // remove it

                    if (pInstance)
                    {
                        pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SHAMAN_STORM_POWER_10);
                        pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SHAMAN_STORM_POWER_25);
                    }

                    me->MonsterYell(TEXT_HODIR_DEFEATED, LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_HODIR_DEFEATED, 0);
                    me->DespawnOrUnsummon(10s);

                    if (GameObject* normalChest = ObjectAccessor::GetGameObject(*me, _normalChest))
                        normalChest->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);

                    if (hardmode)
                    {
                        if (GameObject* hardmodeChest = ObjectAccessor::GetGameObject(*me, _hardmodeChest))
                            hardmodeChest->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);

                        if (pInstance)
                            pInstance->SetData(DATA_HODIR_HARDMODE, DATA_HODIR_HARDMODE);
                    }

                    if (Map* map = me->GetMap())
                        CheckCreatureRecord(me->SelectNearestPlayer(50.0f), me->GetCreatureTemplate()->Entry + 2 * hardmode, Difficulty(map->GetDifficulty() + hardmode * 2), "", 15000, _fightTimer);
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            {
                if (me->IsInCombat())
                {
                    Map::PlayerList const& pl = me->GetMap()->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = pl.begin(); itr != pl.end(); ++itr)
                        if (!itr->GetSource()->IsGameMaster())
                            itr->GetSource()->CastSpell(itr->GetSource(), SPELL_FLASH_FREEZE_INSTAKILL, true);
                    EnterEvadeMode();
                }
                return;
            }

            if (me->GetPositionX() < 1940.0f || me->GetPositionX() > 2070.0f || me->GetPositionY() < -300.0f || me->GetPositionY() > -155.0f)
            {
                EnterEvadeMode();
                return;
            }

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (auto eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BERSERK:
                    {
                        me->CastSpell(me, SPELL_BERSERK, true);
                        me->MonsterYell(TEXT_HODIR_BERSERK, LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(SOUND_HODIR_BERSERK, 0);
                        break;
                    }
                    case EVENT_HARD_MODE_MISSED:
                    {
                        if (GameObject* normalChest = ObjectAccessor::GetGameObject(*me, _hardmodeChest))
                            normalChest->SetPhaseMask(2, true);

                        hardmode = false;
                        me->MonsterTextEmote(TEXTEMOTE_HODIR_HARD_MODE_MISSED, 0);
                        break;
                    }
                    case EVENT_FLASH_FREEZE:
                    {
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_MAX_TARGETS, 2);
                        me->CastCustomSpell(SPELL_ICICLE_FLASH_SELECTOR, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);

                        me->CastSpell((Unit*)nullptr, SPELL_FLASH_FREEZE_CAST, false);
                        me->MonsterTextEmote("Hodir begins to cast Flash Freeze!", 0, true);
                        me->MonsterYell(TEXT_HODIR_FLASH_FREEZE, LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(SOUND_HODIR_FLASH_FREEZE, 0);
                        SmallIcicles(false);
                        events.Repeat(60s);
                        events.ScheduleEvent(EVENT_SMALL_ICICLES_ENABLE, 12s);
                        events.ScheduleEvent(EVENT_FROZEN_BLOWS, 15s);
                        events.ScheduleEvent(EVENT_FREEZE, 20s);
                        break;
                    }
                    case EVENT_SMALL_ICICLES_ENABLE:
                    {
                        SmallIcicles(true);
                        break;
                    }
                    case EVENT_FROZEN_BLOWS:
                    {
                        me->MonsterTextEmote("Hodir gains Frozen Blows!", 0, true);
                        me->MonsterTextEmote(TEXTEMOTE_HODIR_FROZEN_BLOWS, 0);
                        me->PlayDirectSound(SOUND_HODIR_FROZEN_BLOWS, 0);
                        me->CastSpell(me, SPELL_FROZEN_BLOWS, true);
                        break;
                    }
                    case EVENT_FREEZE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 50.0f, true, -SPELL_FLASH_FREEZE_TRAPPED_PLAYER))
                            DoCast(target, SPELL_FREEZE, false);
                        events.Repeat(15s);
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

        void KilledUnit(Unit* who)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                if (urand(0, 1))
                {
                    me->MonsterYell(TEXT_HODIR_SLAIN_1, LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_HODIR_SLAIN_1, 0);
                }
                else
                {
                    me->MonsterYell(TEXT_HODIR_SLAIN_2, LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_HODIR_SLAIN_2, 0);
                }
            }
        }

        void JustSummoned(Creature* summoned)
        {
            summons.Summon(summoned);
        }

        void SummonedCreatureDespawn(Creature* summoned)
        {
            summons.Despawn(summoned);
        }

        bool CanAIAttack(const Unit* t) const
        {
            if (t->GetTypeId() == TYPEID_PLAYER)
                return !t->HasAura(SPELL_FLASH_FREEZE_TRAPPED_PLAYER);
            else if (t->GetTypeId() == TYPEID_UNIT)
            {
                switch (t->GetEntry())
                {
                    case NPC_TOR_GREYCLOUD:
                    case NPC_KAR_GREYCLOUD:
                    case NPC_EIVI_NIGHTFEATHER:
                    case NPC_ELLIE_NIGHTFEATHER:
                    case NPC_SPIRITWALKER_TARA:
                    case NPC_SPIRITWALKER_YONA:
                    case NPC_ELEMENTALIST_MAHFUUN:
                    case NPC_ELEMENTALIST_AVUUN:
                    case NPC_AMIRA_BLAZEWEAVER:
                    case NPC_VEESHA_BLAZEWEAVER:
                    case NPC_MISSY_FLAMECUFFS:
                    case NPC_SISSY_FLAMECUFFS:
                    case NPC_BATTLE_PRIEST_ELIZA:
                    case NPC_BATTLE_PRIEST_GINA:
                    case NPC_FIELD_MEDIC_PENNY:
                    case NPC_FIELD_MEDIC_JESSI:
                    case NPC_FLASH_FREEZE_NPC:
                    case NPC_FLASH_FREEZE_PLR:
                        return false;
                }
            }

            return true;
        }

        void SetData(uint32 id, uint32 value)
        {
            if (value)
                switch (id)
                {
                    case 1: bAchievCheese = false; break;
                    case 2: bAchievGettingCold = false; break;
                    case 4: bAchievCoolestFriends = false; break;
                }
        }

        uint32 GetData(uint32 id) const
        {
            switch (id)
            {
                case 1: return (bAchievCheese ? 1 : 0);
                case 2: return (bAchievGettingCold ? 1 : 0);
                case 3: return (hardmode ? 1 : 0);
                case 4: return (bAchievCoolestFriends ? 1 : 0);
            }
            return 0;
        }

        void MoveInLineOfSight(Unit* who) { }
    private:
        InstanceScript * pInstance;
        EventMap events;
        SummonList summons;
        //! GUIDs of summoned helpers during encounter
        std::vector<uint64> _helpers;
        bool hardmode;
        bool bAchievCheese;
        bool bAchievGettingCold;
        bool bAchievCoolestFriends;
        uint64 _normalChest;
        uint64 _hardmodeChest;
        uint32 _fightTimer;
    };
};

class npc_ulduar_icicle : public CreatureScript
{
public:
    npc_ulduar_icicle() : CreatureScript("npc_ulduar_icicle") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ulduar_icicleAI(pCreature);
    }

    struct npc_ulduar_icicleAI : public NullCreatureAI
    {
        npc_ulduar_icicleAI(Creature *pCreature) : NullCreatureAI(pCreature)
        {
            timer1 = 2000;
            timer2 = 5000;
        }

        uint16 timer1;
        uint16 timer2;

        void UpdateAI(uint32 diff)
        {
            if (timer1 <= diff)
            {
                me->CastSpell(me, (me->GetEntry() == 33169 ? SPELL_ICICLE_FALL_EFFECT_UNPACKED : SPELL_ICICLE_FALL_EFFECT_PACKED), true);
                me->CastSpell(me, SPELL_ICICLE_VISUAL_FALLING, false);
                timer1 = 60000;
            }
            else
                timer1 -= diff;

            if (timer2 <= diff)
            {
                me->SetDisplayId(11686);
                timer2 = 60000;
            }
            else
                timer2 -= diff;
        }
    };
};

class npc_ulduar_flash_freeze : public CreatureScript
{
public:
    npc_ulduar_flash_freeze() : CreatureScript("npc_ulduar_flash_freeze") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ulduar_flash_freezeAI(pCreature);
    }

    struct npc_ulduar_flash_freezeAI : public NullCreatureAI
    {
        npc_ulduar_flash_freezeAI(Creature *pCreature) : NullCreatureAI(pCreature)
        {
            timer = 2500;
            pInstance = me->GetInstanceScript();
        }

        InstanceScript* pInstance;
        uint16 timer;

        void DamageTaken(Unit* doneBy, uint32 &damage, DamageEffectType, SpellSchoolMask)
        {
            if (pInstance && doneBy)
                if (pInstance->GetData(TYPE_HODIR) == NOT_STARTED)
                    if (Creature* hodir = ObjectAccessor::GetCreature(*me, pInstance->GetData64(TYPE_HODIR)))
                        hodir->AI()->AttackStart(doneBy);
        }

        void UpdateAI(uint32 diff)
        {
            if (timer <= diff)
            {
                timer = 2500;
                if (me->IsSummon())
                    if (Unit* s = me->ToTempSummon()->GetSummoner())
                    {
                        if (s->GetTypeId() == TYPEID_PLAYER && !s->HasAura(SPELL_FLASH_FREEZE_TRAPPED_PLAYER) || s->GetTypeId() == TYPEID_UNIT && !s->HasAura(SPELL_FLASH_FREEZE_TRAPPED_NPC))
                            me->DespawnOrUnsummon(2000);
                        else if (s->GetTypeId() == TYPEID_PLAYER)
                            if (InstanceScript* pInstance = me->GetInstanceScript())
                                if (pInstance->GetData(TYPE_HODIR) == NOT_STARTED)
                                {
                                    s->CastSpell(s, SPELL_FLASH_FREEZE_INSTAKILL, true);
                                    me->DespawnOrUnsummon(2000);
                                }
                    }
                    else
                        me->DespawnOrUnsummon(2000);
            }
            else
                timer -= diff;
        }
    };
};

class npc_ulduar_toasty_fire : public CreatureScript
{
public:
    npc_ulduar_toasty_fire() : CreatureScript("npc_ulduar_toasty_fire") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ulduar_toasty_fireAI(pCreature);
    }

    struct npc_ulduar_toasty_fireAI : public NullCreatureAI
    {
        npc_ulduar_toasty_fireAI(Creature *pCreature) : NullCreatureAI(pCreature)
        {
            me->CastSpell(me, SPELL_MAGE_TOASTY_FIRE_AURA, true);
            if (GameObject* fire = me->FindNearestGameObject(194300, 1.0f))
                fire->EnableCollision(false);
        }

        void DoAction(int32 a)
        {
            if (a == 1)
            {
                if (GameObject* fire = me->FindNearestGameObject(194300, 1.0f))
                {
                    fire->SetOwnerGUID(0);
                    fire->Delete();
                }
                me->DespawnOrUnsummon(); // this will remove DynObjects
            }
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            switch (spell->Id)
            {
                case SPELL_ICE_SHARDS_SMALL:
                case SPELL_ICE_SHARDS_BIG:
                    DoAction(1);
                    break;
            }
        }
    };
};

class npc_ulduar_hodir_priest : public CreatureScript
{
public:
    npc_ulduar_hodir_priest() : CreatureScript("npc_ulduar_hodir_priest") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ulduar_hodir_priestAI(pCreature);
    }

    struct npc_ulduar_hodir_priestAI : public ScriptedAI
    {
        npc_ulduar_hodir_priestAI(Creature *pCreature) : ScriptedAI(pCreature)
        {
            pInstance = me->GetInstanceScript();
            events.Reset();
            me->SetReactState(REACT_PASSIVE);
        }

        EventMap events;
        InstanceScript* pInstance;

        void AttackStart(Unit* who)
        {
            AttackStartCaster(who, 17.0f);
        }

        void ScheduleAbilities()
        {
            events.ScheduleEvent(EVENT_PRIEST_DISPELL_MAGIC, 7000);
            events.ScheduleEvent(EVENT_PRIEST_GREAT_HEAL, urand(6000, 7000));
            events.ScheduleEvent(EVENT_PRIEST_SMITE, 2100);
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_FLASH_FREEZE_TRAPPED_NPC)
            {
                events.Reset();
                events.ScheduleEvent(EVENT_TRY_FREE_HELPER, 2000);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case 0:
                    break;
                case EVENT_TRY_FREE_HELPER:
                {
                    if (!me->HasAura(SPELL_FLASH_FREEZE_TRAPPED_NPC))
                        if (pInstance)
                            if (uint64 g = pInstance->GetData64(TYPE_HODIR))
                                if (Creature* hodir = ObjectAccessor::GetCreature(*me, g))
                                {
                                    AttackStart(hodir);
                                    events.PopEvent();
                                    ScheduleAbilities();
                                    break;
                                }
                    events.RepeatEvent(2000);
                }
                break;
                case EVENT_PRIEST_DISPELL_MAGIC:
                    me->CastCustomSpell(SPELL_PRIEST_DISPELL_MAGIC, SPELLVALUE_MAX_TARGETS, 1, (Unit*)NULL, false);
                    events.RepeatEvent(7000);
                    break;
                case EVENT_PRIEST_GREAT_HEAL:
                    me->CastSpell(me, SPELL_PRIEST_GREAT_HEAL, false);
                    events.RepeatEvent(urand(6000, 7000));
                    break;
                case EVENT_PRIEST_SMITE:
                    if (Unit* victim = me->GetVictim())
                        me->CastSpell(victim, SPELL_PRIEST_SMITE, false);
                    events.RepeatEvent(2100);
                    break;
            }
        }

        void MoveInLineOfSight(Unit* who) {}
        void EnterEvadeMode() {}
        bool CanAIAttack(const Unit* t) const { return t->GetEntry() == NPC_HODIR; }

        void JustDied(Unit* /*killer*/)
        {
            if (pInstance)
                if (Creature* hodir = pInstance->instance->GetCreature(pInstance->GetData64(TYPE_HODIR)))
                    hodir->AI()->SetData(4, 1);
        }
    };
};

class npc_ulduar_hodir_druid : public CreatureScript
{
public:
    npc_ulduar_hodir_druid() : CreatureScript("npc_ulduar_hodir_druid") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ulduar_hodir_druidAI(pCreature);
    }

    struct npc_ulduar_hodir_druidAI : public ScriptedAI
    {
        npc_ulduar_hodir_druidAI(Creature *pCreature) : ScriptedAI(pCreature)
        {
            pInstance = me->GetInstanceScript();
            events.Reset();
            me->SetReactState(REACT_PASSIVE);
        }

        EventMap events;
        InstanceScript* pInstance;

        void AttackStart(Unit* who)
        {
            AttackStartCaster(who, 22.0f);
        }

        void ScheduleAbilities()
        {
            events.ScheduleEvent(EVENT_DRUID_WRATH, 1600);
            events.ScheduleEvent(EVENT_DRUID_STARLIGHT, 10000);
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_FLASH_FREEZE_TRAPPED_NPC)
            {
                events.Reset();
                events.ScheduleEvent(EVENT_TRY_FREE_HELPER, 2000);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case 0:
                    break;
                case EVENT_TRY_FREE_HELPER:
                {
                    if (!me->HasAura(SPELL_FLASH_FREEZE_TRAPPED_NPC))
                        if (pInstance)
                            if (uint64 g = pInstance->GetData64(TYPE_HODIR))
                                if (Creature* hodir = ObjectAccessor::GetCreature(*me, g))
                                {
                                    AttackStart(hodir);
                                    events.PopEvent();
                                    ScheduleAbilities();
                                    break;
                                }
                    events.RepeatEvent(2000);
                }
                break;
                case EVENT_DRUID_WRATH:
                    if (Unit* victim = me->GetVictim())
                        me->CastSpell(victim, SPELL_DRUID_WRATH, false);
                    events.RepeatEvent(1600);
                    break;
                case EVENT_DRUID_STARLIGHT:
                    if (me->GetPositionZ() < 433.0f) // ensure npc is on the ground
                    {
                        me->CastSpell(me, SPELL_DRUID_STARLIGHT_AREA_AURA, false);
                        events.RepeatEvent(15000);
                        break;
                    }
                    events.RepeatEvent(3000);
                    break;
            }
        }

        void MoveInLineOfSight(Unit* who) {}
        void EnterEvadeMode() {}
        bool CanAIAttack(const Unit* t) const { return t->GetEntry() == NPC_HODIR; }

        void JustDied(Unit* /*killer*/)
        {
            if (pInstance)
                if (Creature* hodir = pInstance->instance->GetCreature(pInstance->GetData64(TYPE_HODIR)))
                    hodir->AI()->SetData(4, 1);
        }
    };
};

class npc_ulduar_hodir_shaman : public CreatureScript
{
public:
    npc_ulduar_hodir_shaman() : CreatureScript("npc_ulduar_hodir_shaman") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ulduar_hodir_shamanAI(pCreature);
    }

    struct npc_ulduar_hodir_shamanAI : public ScriptedAI
    {
        npc_ulduar_hodir_shamanAI(Creature *pCreature) : ScriptedAI(pCreature)
        {
            pInstance = me->GetInstanceScript();
            events.Reset();
            me->SetReactState(REACT_PASSIVE);
        }

        EventMap events;
        InstanceScript* pInstance;

        void AttackStart(Unit* who)
        {
            AttackStartCaster(who, 25.0f);
        }

        void ScheduleAbilities()
        {
            events.ScheduleEvent(EVENT_SHAMAN_LAVA_BURST, 2600);
            events.ScheduleEvent(EVENT_SHAMAN_STORM_CLOUD, 10000);
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_FLASH_FREEZE_TRAPPED_NPC)
            {
                events.Reset();
                events.ScheduleEvent(EVENT_TRY_FREE_HELPER, 2000);
            }
        }

        void SpellHitTarget(Unit* target, const SpellInfo* spell)
        {
            if (target && spell->Id == SPELL_SHAMAN_STORM_CLOUD)
                if (Aura* a = target->GetAura(SPELL_SHAMAN_STORM_CLOUD, me->GetGUID()))
                    a->SetStackAmount(spell->StackAmount);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case 0:
                    break;
                case EVENT_TRY_FREE_HELPER:
                {
                    if (!me->HasAura(SPELL_FLASH_FREEZE_TRAPPED_NPC))
                        if (pInstance)
                            if (uint64 g = pInstance->GetData64(TYPE_HODIR))
                                if (Creature* hodir = ObjectAccessor::GetCreature(*me, g))
                                {
                                    AttackStart(hodir);
                                    events.PopEvent();
                                    ScheduleAbilities();
                                    break;
                                }
                    events.RepeatEvent(2000);
                }
                break;
                case EVENT_SHAMAN_LAVA_BURST:
                    if (Unit* victim = me->GetVictim())
                        me->CastSpell(victim, SPELL_SHAMAN_LAVA_BURST, false);
                    events.RepeatEvent(2600);
                    break;
                case EVENT_SHAMAN_STORM_CLOUD:
                    if (Player* target = ScriptedAI::SelectTargetFromPlayerList(35.0f, SPELL_SHAMAN_STORM_CLOUD))
                        me->CastSpell(target, SPELL_SHAMAN_STORM_CLOUD, false);
                    events.RepeatEvent(30000);
                    break;
            }
        }

        void MoveInLineOfSight(Unit* who) {}
        void EnterEvadeMode() {}
        bool CanAIAttack(const Unit* t) const { return t->GetEntry() == NPC_HODIR; }

        void JustDied(Unit* /*killer*/)
        {
            if (pInstance)
                if (Creature* hodir = pInstance->instance->GetCreature(pInstance->GetData64(TYPE_HODIR)))
                    hodir->AI()->SetData(4, 1);
        }
    };
};

class npc_ulduar_hodir_mage : public CreatureScript
{
public:
    npc_ulduar_hodir_mage() : CreatureScript("npc_ulduar_hodir_mage") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ulduar_hodir_mageAI(pCreature);
    }

    struct npc_ulduar_hodir_mageAI : public ScriptedAI
    {
        npc_ulduar_hodir_mageAI(Creature *pCreature) : ScriptedAI(pCreature)
        {
            pInstance = me->GetInstanceScript();
            events.Reset();
            me->SetReactState(REACT_PASSIVE);
        }

        EventMap events;
        InstanceScript* pInstance;

        void AttackStart(Unit* who)
        {
            AttackStartCaster(who, 30.0f);
        }

        void ScheduleAbilities()
        {
            events.ScheduleEvent(EVENT_MAGE_FIREBALL, 3100);
            events.ScheduleEvent(EVENT_MAGE_TOASTY_FIRE, 6000);
            events.ScheduleEvent(EVENT_MAGE_MELT_ICE, 1000);
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_FLASH_FREEZE_TRAPPED_NPC)
            {
                events.Reset();
                events.ScheduleEvent(EVENT_TRY_FREE_HELPER, 2000);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case 0:
                    break;
                case EVENT_TRY_FREE_HELPER:
                {
                    if (!me->HasAura(SPELL_FLASH_FREEZE_TRAPPED_NPC))
                        if (pInstance)
                            if (uint64 g = pInstance->GetData64(TYPE_HODIR))
                                if (Creature* hodir = ObjectAccessor::GetCreature(*me, g))
                                {
                                    AttackStart(hodir);
                                    events.PopEvent();
                                    ScheduleAbilities();
                                    break;
                                }
                    events.RepeatEvent(2000);
                }
                break;
                case EVENT_MAGE_FIREBALL:
                    if (Unit* victim = me->GetVictim())
                        me->CastSpell(victim, SPELL_MAGE_FIREBALL, false);
                    events.RepeatEvent(3100);
                    break;
                case EVENT_MAGE_TOASTY_FIRE:
                    me->CastSpell(me, SPELL_MAGE_CONJURE_TOASTY_FIRE, false);
                    events.RepeatEvent(22000);
                    break;
                case EVENT_MAGE_MELT_ICE:
                {
                    std::list<Creature*> FB;
                    bool found = false;
                    me->GetCreaturesWithEntryInRange(FB, 150.0f, NPC_FLASH_FREEZE_NPC);
                    for (std::list<Creature*>::const_iterator itr = FB.begin(); itr != FB.end(); ++itr)
                        if (!((*itr)->HasAura(SPELL_MAGE_MELT_ICE)))
                        {
                            me->CastSpell((*itr), SPELL_MAGE_MELT_ICE, false);
                            found = true;
                            break;
                        }

                    if (found)
                    {
                        events.DelayEvents(2000);
                        events.RepeatEvent(1999);
                        break;
                    }
                    events.RepeatEvent(5000);
                }
                break;
            }
        }

        void MoveInLineOfSight(Unit* who) {}
        void EnterEvadeMode() {}
        bool CanAIAttack(const Unit* t) const { return t->GetEntry() == NPC_HODIR; }

        void JustDied(Unit* /*killer*/)
        {
            if (pInstance)
                if (Creature* hodir = pInstance->instance->GetCreature(pInstance->GetData64(TYPE_HODIR)))
                    hodir->AI()->SetData(4, 1);
        }
    };
};

class spell_hodir_biting_cold_main_aura : public SpellScriptLoader
{
public:
    spell_hodir_biting_cold_main_aura() : SpellScriptLoader("spell_hodir_biting_cold_main_aura") { }

    class spell_hodir_biting_cold_main_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hodir_biting_cold_main_aura_AuraScript)

        void HandleEffectPeriodic(AuraEffect const* aurEff)
        {
            if (Unit* target = GetTarget())
                if (target->GetTypeId() == TYPEID_PLAYER && !target->isMoving() && !target->HasAura(SPELL_BITING_COLD_PLAYER_AURA) && !target->HasAura(SPELL_MAGE_TOASTY_FIRE_AURA))
                    target->CastSpell(target, SPELL_BITING_COLD_PLAYER_AURA, true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_hodir_biting_cold_main_aura_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript *GetAuraScript() const
    {
        return new spell_hodir_biting_cold_main_aura_AuraScript();
    }
};

class spell_hodir_biting_cold_player_aura : public SpellScriptLoader
{
public:
    spell_hodir_biting_cold_player_aura() : SpellScriptLoader("spell_hodir_biting_cold_player_aura") {}

    class spell_hodir_biting_cold_player_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hodir_biting_cold_player_aura_AuraScript);

        bool Load() override
        {
            _counter = 0;
            return true;
        }

        void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTarget())
                pos = GetTarget()->GetPosition();
        }

        void HandleEffectPeriodic(AuraEffect const * aurEff)
        {
            if (Unit* target = GetTarget())
            {
                Position currentPos = target->GetPosition();
                if (currentPos != pos || target->HasAura(SPELL_MAGE_TOASTY_FIRE_AURA))
                    ModStackAmount(-1);
                else
                {
                    if (++_counter >= 4)
                    {
                        _counter = 0;
                        ModStackAmount(1);
                        if (GetStackAmount() >= 2)
                            if (InstanceScript* instance = target->GetInstanceScript())
                                if (Creature* hodir = ObjectAccessor::GetCreature(*target, instance->GetData64(TYPE_HODIR)))
                                    hodir->AI()->SetData(2, 1);
                    }
                }

                pos = target->GetPosition();
                const int32 dmg = 200 * pow(2.0f, GetStackAmount());
                target->CastCustomSpell(target, SPELL_BITING_COLD_DAMAGE, &dmg, 0, 0, true);
            }
        }
    private:
        Position pos;
        uint8 _counter;

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_hodir_biting_cold_player_aura_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_hodir_biting_cold_player_aura_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript *GetAuraScript() const
    {
        return new spell_hodir_biting_cold_player_aura_AuraScript();
    }
};

class spell_hodir_periodic_icicle : public SpellScriptLoader
{
public:
    spell_hodir_periodic_icicle() : SpellScriptLoader("spell_hodir_periodic_icicle") {}

    class spell_hodir_periodic_icicle_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hodir_periodic_icicle_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(Trinity::ObjectTypeIdCheck(TYPEID_PLAYER, false));
            targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_FLASH_FREEZE_TRAPPED_PLAYER));
            Trinity::Containers::RandomResize(targets, 1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hodir_periodic_icicle_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hodir_periodic_icicle_SpellScript();
    }
};

class FlashFreezeCheck
{
public:
    FlashFreezeCheck() {}

    bool operator()(WorldObject* target) const
    {
        if (Unit* unit = target->ToUnit())
            return unit->HasAura(SPELL_SAFE_AREA_TRIGGERED) || unit->IsPet() || (unit->IsSummon() && !unit->ToCreature()->isElite());

        return true;
    }
};

class spell_hodir_flash_freeze : public SpellScriptLoader
{
public:
    spell_hodir_flash_freeze() : SpellScriptLoader("spell_hodir_flash_freeze") {}

    class spell_hodir_flash_freeze_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hodir_flash_freeze_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(FlashFreezeCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hodir_flash_freeze_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hodir_flash_freeze_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    class spell_hodir_flash_freeze_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hodir_flash_freeze_AuraScript)

            void HandleEffectPeriodic(AuraEffect const * aurEff)
        {
            if (aurEff->GetTickNumber() == aurEff->GetTotalTicks() - 1)
            {
                Unit* target = GetTarget();
                Unit* caster = GetCaster();
                if (!target || !caster || caster->GetTypeId() != TYPEID_UNIT)
                    return;

                if (Aura* aur = target->GetAura(target->GetTypeId() == TYPEID_PLAYER ? SPELL_FLASH_FREEZE_TRAPPED_PLAYER : SPELL_FLASH_FREEZE_TRAPPED_NPC))
                {
                    if (Unit* caster = aur->GetCaster())
                        if (caster->GetTypeId() == TYPEID_UNIT)
                            caster->ToCreature()->DespawnOrUnsummon();
                    target->CastSpell(target, SPELL_FLASH_FREEZE_INSTAKILL, true);
                    return;
                }
                if (target->GetTypeId() == TYPEID_PLAYER)
                {
                    caster->ToCreature()->AI()->SetData(1, 1);
                    if (Creature* c = target->SummonCreature(NPC_FLASH_FREEZE_PLR, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 5 * 60 * 1000))
                    {
                        c->CastSpell(target, SPELL_FLASH_FREEZE_TRAPPED_PLAYER, true);
                        caster->ToCreature()->AI()->JustSummoned(c);
                    }
                }
                else if (target->GetTypeId() == TYPEID_UNIT)
                {
                    if (Creature* c = target->SummonCreature(NPC_FLASH_FREEZE_NPC, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 2000))
                    {
                        c->CastSpell(target, SPELL_FLASH_FREEZE_TRAPPED_NPC, true);
                        caster->ToCreature()->AI()->JustSummoned(c);
                    }
                }
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_hodir_flash_freeze_AuraScript::HandleEffectPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hodir_flash_freeze_SpellScript();
    }

    AuraScript *GetAuraScript() const
    {
        return new spell_hodir_flash_freeze_AuraScript();
    }
};

class spell_hodir_storm_power : public SpellScriptLoader
{
public:
    spell_hodir_storm_power() : SpellScriptLoader("spell_hodir_storm_power") {}

    class spell_hodir_storm_power_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hodir_storm_power_AuraScript)

            void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (Aura* a = caster->GetAura(GetId() == SPELL_SHAMAN_STORM_POWER_10 ? SPELL_SHAMAN_STORM_CLOUD_10 : SPELL_SHAMAN_STORM_CLOUD_25))
                    a->ModStackAmount(-1);
        }

        void HandleAfterEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
                if (target->GetTypeId() == TYPEID_PLAYER)
                    target->ToPlayer()->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2, GetId(), 0, GetCaster());
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_hodir_storm_power_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_CRIT_DAMAGE_BONUS, AURA_EFFECT_HANDLE_REAL);
            AfterEffectApply += AuraEffectApplyFn(spell_hodir_storm_power_AuraScript::HandleAfterEffectApply, EFFECT_0, SPELL_AURA_MOD_CRIT_DAMAGE_BONUS, AURA_EFFECT_HANDLE_SEND_FOR_CLIENT_MASK);
        }
    };

    AuraScript *GetAuraScript() const
    {
        return new spell_hodir_storm_power_AuraScript();
    }
};

class spell_hodir_storm_cloud : public SpellScriptLoader
{
public:
    spell_hodir_storm_cloud() : SpellScriptLoader("spell_hodir_storm_cloud") {}

    class spell_hodir_storm_cloud_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hodir_storm_cloud_AuraScript)

            void HandleEffectPeriodic(AuraEffect const * aurEff)
        {
            PreventDefaultAction();
            if (Unit* target = GetTarget())
                target->CastSpell((Unit*)NULL, (GetId() == SPELL_SHAMAN_STORM_CLOUD_10 ? SPELL_SHAMAN_STORM_POWER_10 : SPELL_SHAMAN_STORM_POWER_25), true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_hodir_storm_cloud_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    class spell_hodir_storm_cloud_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hodir_storm_cloud_SpellScript);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            if (Aura* aura = GetHitUnit()->GetAura(GetSpellInfo()->Id))
                aura->SetStackAmount(GetSpellInfo()->Effects[EFFECT_0].BasePoints + 1);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hodir_storm_cloud_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hodir_storm_cloud_SpellScript();
    }

    AuraScript *GetAuraScript() const
    {
        return new spell_hodir_storm_cloud_AuraScript();
    }
};

class achievement_cheese_the_freeze : public AchievementCriteriaScript
{
public:
    achievement_cheese_the_freeze() : AchievementCriteriaScript("achievement_cheese_the_freeze") {}

    bool OnCheck(Player* player, Unit* target)
    {
        return target && target->GetEntry() == NPC_HODIR && target->GetTypeId() == TYPEID_UNIT && target->ToCreature()->AI()->GetData(1);
    }
};

class achievement_getting_cold_in_here : public AchievementCriteriaScript
{
public:
    achievement_getting_cold_in_here() : AchievementCriteriaScript("achievement_getting_cold_in_here") {}

    bool OnCheck(Player* player, Unit* target)
    {
        return target && target->GetEntry() == NPC_HODIR && target->GetTypeId() == TYPEID_UNIT && target->ToCreature()->AI()->GetData(2);
    }
};

class achievement_i_could_say_that_this_cache_was_rare : public AchievementCriteriaScript
{
public:
    achievement_i_could_say_that_this_cache_was_rare() : AchievementCriteriaScript("achievement_i_could_say_that_this_cache_was_rare") {}

    bool OnCheck(Player* player, Unit* target)
    {
        return target && target->GetEntry() == NPC_HODIR && target->GetTypeId() == TYPEID_UNIT && target->ToCreature()->AI()->GetData(3);
    }
};

class achievement_i_have_the_coolest_friends : public AchievementCriteriaScript
{
public:
    achievement_i_have_the_coolest_friends() : AchievementCriteriaScript("achievement_i_have_the_coolest_friends") {}

    bool OnCheck(Player* player, Unit* target)
    {
        return target && target->GetEntry() == NPC_HODIR && target->GetTypeId() == TYPEID_UNIT && target->ToCreature()->AI()->GetData(4);
    }
};

class achievement_staying_buffed_all_winter_10 : public AchievementCriteriaScript
{
public:
    achievement_staying_buffed_all_winter_10() : AchievementCriteriaScript("achievement_staying_buffed_all_winter_10") {}

    bool OnCheck(Player* player, Unit* target)
    {
        return player && player->HasAura(SPELL_MAGE_TOASTY_FIRE_AURA) && player->HasAura(SPELL_DRUID_STARLIGHT_AREA_AURA) && player->HasAura(SPELL_SHAMAN_STORM_POWER_10);
    }
};

class achievement_staying_buffed_all_winter_25 : public AchievementCriteriaScript
{
public:
    achievement_staying_buffed_all_winter_25() : AchievementCriteriaScript("achievement_staying_buffed_all_winter_25") {}

    bool OnCheck(Player* player, Unit* target)
    {
        return player && player->HasAura(SPELL_MAGE_TOASTY_FIRE_AURA) && player->HasAura(SPELL_DRUID_STARLIGHT_AREA_AURA) && player->HasAura(SPELL_SHAMAN_STORM_POWER_25);
    }
};

class spell_hodir_toasty_fire : public SpellScriptLoader
{
public:
    spell_hodir_toasty_fire() : SpellScriptLoader("spell_hodir_toasty_fire") {}

    class spell_hodir_toasty_fire_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hodir_toasty_fire_AuraScript);

        void HandleAfterEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
                if (target->GetTypeId() == TYPEID_PLAYER)
                    target->ToPlayer()->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2, SPELL_MAGE_TOASTY_FIRE_AURA, 0, GetCaster());
        }

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_hodir_toasty_fire_AuraScript::HandleAfterEffectApply, EFFECT_0, SPELL_AURA_MOD_STAT, AURA_EFFECT_HANDLE_SEND_FOR_CLIENT_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_hodir_toasty_fire_AuraScript();
    }
};

class spell_hodir_starlight : public SpellScriptLoader
{
public:
    spell_hodir_starlight() : SpellScriptLoader("spell_hodir_starlight") {}

    class spell_hodir_starlight_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hodir_starlight_AuraScript);

        void HandleAfterEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
                if (target->GetTypeId() == TYPEID_PLAYER)
                    target->ToPlayer()->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2, SPELL_DRUID_STARLIGHT_AREA_AURA, 0, GetCaster());
        }

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_hodir_starlight_AuraScript::HandleAfterEffectApply, EFFECT_0, SPELL_AURA_MELEE_SLOW, AURA_EFFECT_HANDLE_SEND_FOR_CLIENT_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_hodir_starlight_AuraScript();
    }
};

class spell_summon_icicle_flash_freeze_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_summon_icicle_flash_freeze_SpellScript);

    void ModDest(SpellDestination& dest)
    {
        Position pos = GetCaster()->GetPosition();
        pos.m_positionZ = 432.7f;
        dest.Relocate(pos);
    }

    void Register() override
    {
        OnDestinationTargetSelect += SpellDestinationTargetSelectFn(spell_summon_icicle_flash_freeze_SpellScript::ModDest, EFFECT_0, TARGET_DEST_CASTER);
        OnDestinationTargetSelect += SpellDestinationTargetSelectFn(spell_summon_icicle_flash_freeze_SpellScript::ModDest, EFFECT_1, TARGET_DEST_CASTER);
    }
};

class spell_summon_icicle_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_summon_icicle_SpellScript);

    void ModDest(SpellDestination& dest)
    {
        Position pos = GetCaster()->GetPosition();
        pos.m_positionZ = 432.7f;
        dest.Relocate(pos);
    }

    void Register() override
    {
        OnDestinationTargetSelect += SpellDestinationTargetSelectFn(spell_summon_icicle_SpellScript::ModDest, EFFECT_0, TARGET_DEST_TARGET_ANY);
        OnDestinationTargetSelect += SpellDestinationTargetSelectFn(spell_summon_icicle_SpellScript::ModDest, EFFECT_1, TARGET_DEST_TARGET_ANY);
    }
};

void AddSC_boss_hodir()
{
    new boss_hodir();
    new npc_ulduar_icicle();
    new npc_ulduar_flash_freeze();
    new npc_ulduar_toasty_fire();

    new npc_ulduar_hodir_priest();
    new npc_ulduar_hodir_druid();
    new npc_ulduar_hodir_shaman();
    new npc_ulduar_hodir_mage();

    new spell_hodir_biting_cold_main_aura();
    new spell_hodir_biting_cold_player_aura();
    new spell_hodir_periodic_icicle();
    new spell_hodir_flash_freeze();
    new spell_hodir_storm_power();
    new spell_hodir_storm_cloud();
    new SpellScriptLoaderEx<spell_summon_icicle_flash_freeze_SpellScript>("spell_summon_icicle_flash_freeze");
    new SpellScriptLoaderEx<spell_summon_icicle_SpellScript>("spell_summon_icicle");

    new achievement_cheese_the_freeze();
    new achievement_getting_cold_in_here();
    new achievement_i_could_say_that_this_cache_was_rare();
    new achievement_i_have_the_coolest_friends();
    new achievement_staying_buffed_all_winter_10();
    new achievement_staying_buffed_all_winter_25();
    new spell_hodir_toasty_fire();
    new spell_hodir_starlight();
}
