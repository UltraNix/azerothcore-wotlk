/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "InstanceScript.h"
#include "Map.h"
#include "MotionMaster.h"
#include "Player.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"
#include "TemporarySummon.h"
#include "violet_hold.h"

enum PortalCreatureIds
{
    NPC_AZURE_INVADER_1                 = 30661,
    NPC_AZURE_SPELLBREAKER_1            = 30662,
    NPC_AZURE_BINDER_1                  = 30663,
    NPC_AZURE_MAGE_SLAYER_1             = 30664,
    NPC_VETERAN_MAGE_HUNTER             = 30665,
    NPC_AZURE_CAPTAIN_1                 = 30666,
    NPC_AZURE_SORCEROR_1                = 30667,
    NPC_AZURE_RAIDER_1                  = 30668,

    NPC_AZURE_BINDER_2                  = 30918,
    NPC_AZURE_INVADER_2                 = 30961,
    NPC_AZURE_SPELLBREAKER_2            = 30962,
    NPC_AZURE_MAGE_SLAYER_2             = 30963,
    NPC_AZURE_BINDER_3                  = 31007,
    NPC_AZURE_INVADER_3                 = 31008,
    NPC_AZURE_SPELLBREAKER_3            = 31009,
    NPC_AZURE_MAGE_SLAYER_3             = 31010,
    NPC_AZURE_RAIDER_2                  = 31118,
    NPC_AZURE_STALKER_1                 = 32191
};

enum TrashSays
{
    // Portal Guardian/Keeper
    SAY_SPAWN,
    SAY_AGGRO,
    SAY_DEATH,

    // Portal Creatures
    SAY_PORTAL_AGGRO                           = 0,
    SAY_PORTAL_DEATH
};

enum AzureInvaderSpells
{
    SPELL_CLEAVE                        = 15496,
    SPELL_IMPALE                        = 58459,
    SPELL_BRUTAL_STRIKE                 = 58460,
    SPELL_SUNDER_ARMOR                  = 58461
};

enum AzureSellbreakerSpells
{
    SPELL_ARCANE_BLAST                  = 58462,
    SPELL_SLOW                          = 25603,
    SPELL_CHAINS_OF_ICE                 = 58464,
    SPELL_CONE_OF_COLD                  = 58463,
};

enum AzureBinderSpells
{
    SPELL_ARCANE_BARRAGE                = 58456,
    SPELL_ARCANE_EXPLOSION              = 58455,
    SPELL_FROST_NOVA                    = 58458,
    SPELL_FROSTBOLT                     = 58457,
};

enum AzureMageSlayerSpells
{
    SPELL_ARCANE_EMPOWERMENT            = 58469,
    SPELL_SPELL_LOCK                    = 30849
};

enum AzureCaptainSpells
{
    SPELL_MORTAL_STRIKE                 = 32736,
    SPELL_WHIRLWIND_OF_STEEL            = 41057
};

enum AzureSorcerorSpells
{
    SPELL_ARCANE_STREAM                 = 60181,
    SPELL_MANA_DETONATION               = 60182,
};

enum AzureRaiderSpells
{
    SPELL_CONCUSSION_BLOW               = 52719,
    SPELL_MAGIC_REFLECTION              = 60158
};

enum AzureStalkerSpells
{
    SPELL_BACKSTAB                      = 58471,
    SPELL_TACTICAL_BLINK                = 58470
};

enum AzureSaboteurSpells
{
    SPELL_SHIELD_DISRUPTION             = 58291,
    SPELL_TELEPORT_VISUAL               = 51347
};

enum TrashDoorSpell
{
    SPELL_DESTROY_DOOR_SEAL             = 58040
};

enum DefenseSystemSpells
{
    SPELL_ARCANE_LIGHTNING_DAMAGE       = 57912,
    SPELL_ARCANE_LIGHTNING_INSTAKILL    = 58152,
    SPELL_ARCANE_LIGHTNING_DUMMY        = 57930
};

enum MiscSpells
{
    SPELL_PORTAL_PERIODIC               = 58008,
    SPELL_PORTAL_CHANNEL                = 58012,
    SPELL_CRYSTAL_ACTIVATION            = 57804,

    SPELL_TELEPORT_PLAYER               = 62138,
    SPELL_TELEPORT_PLAYER_EFFECT        = 62139
};

enum MiscData
{
    DATA_PORTAL_PERIODIC_TICK           = 1
};

enum Sinclari
{
    // Sinclari
    SAY_SINCLARI_INTRO_1,
    SAY_SINCLARI_INTRO_2,
    SAY_SINCLARI_OUTRO,

    GOSSIP_MENU_START_ENCOUNTER         = 9998,
    GOSSIP_MENU_SEND_ME_IN              = 10275,

    // Sinclari Trigger
    SAY_SINCLARI_ELITE_SQUAD            = 0,
    SAY_SINCLARI_PORTAL_GUARDIAN,
    SAY_SINCLARI_PORTAL_KEEPER
};

Position const FirstPortalWPs[] =
{
    {1877.670288f, 842.280273f, 43.333591f},
    {1877.338867f, 834.615356f, 38.762287f},
    {1872.161011f, 823.854309f, 38.645401f},
    {1864.860474f, 815.787170f, 38.784843f},
    {1858.953735f, 810.048950f, 44.008759f},
    {1843.707153f, 805.807739f, 44.135197f}
};

Position const SecondPortalFirstWPs[] =
{
    {1902.561401f, 853.334656f, 47.106117f},
    {1895.486084f, 855.376404f, 44.334591f},
    {1882.805176f, 854.993286f, 43.333591f},
    {1877.670288f, 842.280273f, 43.333591f},
    {1877.338867f, 834.615356f, 38.762287f},
    {1872.161011f, 823.854309f, 38.645401f},
    {1864.860474f, 815.787170f, 38.784843f},
    {1858.953735f, 810.048950f, 44.008759f},
    {1843.707153f, 805.807739f, 44.135197f}
};

Position const SecondPortalSecondWPs[] =
{
    {1929.392212f, 837.614990f, 47.136166f},
    {1928.290649f, 824.750427f, 45.474411f},
    {1915.544922f, 826.919373f, 38.642811f},
    {1900.933960f, 818.855652f, 38.801647f},
    {1886.810547f, 813.536621f, 38.490490f},
    {1869.079712f, 808.701538f, 38.689003f},
    {1860.843384f, 806.645020f, 44.008789f},
    {1843.707153f, 805.807739f, 44.135197f}
};

Position const ThirdPortalWPs[] =
{
    {1934.049438f, 815.778503f, 52.408699f},
    {1928.290649f, 824.750427f, 45.474411f},
    {1915.544922f, 826.919373f, 38.642811f},
    {1900.933960f, 818.855652f, 38.801647f},
    {1886.810547f, 813.536621f, 38.490490f},
    {1869.079712f, 808.701538f, 38.689003f},
    {1860.843384f, 806.645020f, 44.008789f},
    {1843.707153f, 805.807739f, 44.135197f}
};

Position const FourthPortalWPs[] =
{
    {1921.658447f, 761.657043f, 50.866741f},
    {1910.559814f, 755.780457f, 47.701447f},
    {1896.664673f, 752.920898f, 47.667004f},
    {1887.398804f, 763.633240f, 47.666851f},
    {1879.020386f, 775.396973f, 38.705990f},
    {1872.439087f, 782.568604f, 38.808292f},
    {1863.573364f, 791.173584f, 38.743660f},
    {1857.811890f, 796.765564f, 43.950329f},
    {1845.577759f, 800.681152f, 44.104248f}
};

Position const FifthPortalWPs[] =
{
    {1887.398804f, 763.633240f, 47.666851f},
    {1879.020386f, 775.396973f, 38.705990f},
    {1872.439087f, 782.568604f, 38.808292f},
    {1863.573364f, 791.173584f, 38.743660f},
    {1857.811890f, 796.765564f, 43.950329f},
    {1845.577759f, 800.681152f, 44.104248f}
};

Position const SixthPortalWPs[] =
{
    {1888.861084f, 805.074768f, 38.375790f},
    {1869.793823f, 804.135804f, 38.647018f},
    {1861.541504f, 804.149780f, 43.968292f},
    {1843.567017f, 804.288208f, 44.139091f}
};

Position const DefaultPortalWPs[] =
{
    { 1843.567017f, 804.288208f, 44.139091f }
};

Position const SinclariPositions[] = // sniff
{
    { 1829.142f, 798.219f,  44.36212f, 0.122173f }, // 0 - Crystal
    { 1820.12f,  803.916f,  44.36466f, 0.0f      }, // 1 - Outside
    { 1816.185f, 804.0629f, 44.44799f, 3.176499f }, // 2 - Second Spawn Point
    { 1827.886f, 804.0555f, 44.36467f, 0.0f      }  // 3 - Outro
};

Position const GuardsMovePosition = { 1802.099f, 803.7724f, 44.36466f, 0.0f }; // sniff

struct npc_sinclariAI : public ScriptedAI
{
    npc_sinclariAI(Creature* creature) : ScriptedAI(creature), _summons(creature)
    {
        _instance = creature->GetInstanceScript();
    }

    void Reset() override
    {
        _summons.DespawnAll();
        for (uint8 i = 0; i < PortalIntroCount; ++i)
            if (Creature* summon = me->SummonCreature(NPC_TELEPORTATION_PORTAL_INTRO, PortalIntroPositions[i], TEMPSUMMON_MANUAL_DESPAWN))
                if (summon->IsAIEnabled)
                    summon->AI()->SetData(DATA_PORTAL_LOCATION, i);

        me->SetVisible(true);
        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

        std::list<Creature*> guardList;
        me->GetCreatureListWithEntryInGrid(guardList, NPC_VIOLET_HOLD_GUARD, 100.0f);
        for (Creature* guard : guardList)
        {
            guard->Respawn(true);
            guard->SetVisible(true);
            guard->SetReactState(REACT_AGGRESSIVE);
            guard->AI()->EnterEvadeMode();
        }
    }

    void sGossipHello(Player* player) override
    {
        // override default gossip
        switch (_instance->GetData(DATA_MAIN_EVENT_STATE))
        {
            case IN_PROGRESS:
                player->PrepareGossipMenu(me, GOSSIP_MENU_SEND_ME_IN, true);
                player->SendPreparedGossip(me);
                return;
            case DONE:
                player->CLOSE_GOSSIP_MENU();
                return; // NYI
            case NOT_STARTED:
            case FAIL:
            default:
                player->PrepareGossipMenu(me, 9997, true);
                break;
        }
    }

    void sGossipSelect(Player* player, uint32 sender, uint32 action) override
    {
        if (sender == GOSSIP_MENU_START_ENCOUNTER && action == 0)
        {
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            _instance->SetData(DATA_MAIN_EVENT_STATE, SPECIAL);
            ScheduleIntro();
            player->PlayerTalkClass->SendCloseGossip();
        }
        else if (sender == GOSSIP_MENU_SEND_ME_IN && action == 0)
        {
            me->CastSpell(player, SPELL_TELEPORT_PLAYER, true);
            player->PlayerTalkClass->SendCloseGossip();
        }
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_SINCLARI_OUTRO)
        {
            me->SetVisible(true);
            ScheduleOutro();
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

    void ScheduleIntro()
    {
        _scheduler.Schedule(1s, [this](TaskContext task)
        {
            switch (task.GetRepeatCounter())
            {
                case 0:
                    me->SetWalk(true);
                    me->GetMotionMaster()->MovePoint(0, SinclariPositions[0]);
                    task.Repeat(1s);
                    break;
                case 1:
                    me->HandleEmoteCommand(EMOTE_ONESHOT_USE_STANDING);
                    me->GetMap()->SummonCreature(NPC_DEFENSE_SYSTEM, DefenseSystemLocation);
                    task.Repeat(3s);
                    break;
                case 2:
                    me->SetFacingTo(SinclariPositions[0].GetOrientation());
                    Talk(SAY_SINCLARI_INTRO_1);

                    task.Schedule(1s, [this](TaskContext /*task*/)
                    {
                        std::list<Creature*> guardList;
                        me->GetCreatureListWithEntryInGrid(guardList, NPC_VIOLET_HOLD_GUARD, 100.0f);
                        for (Creature* guard : guardList)
                        {
                            if (!guard->IsAlive())
                                continue;
                            guard->SetReactState(REACT_PASSIVE);
                            guard->SetWalk(false);
                            guard->GetMotionMaster()->MovePoint(0, GuardsMovePosition);
                        }
                    });

                    task.Repeat(2s);
                    break;
                case 3:
                    me->GetMotionMaster()->MovePoint(0, SinclariPositions[1]);
                    _summons.DespawnAll();
                    task.Repeat(5s);
                    break;
                case 4:
                    me->SetFacingTo(SinclariPositions[1].GetOrientation());

                    task.Schedule(1s, [this](TaskContext /*task*/)
                    {
                        std::list<Creature*> guardList;
                        me->GetCreatureListWithEntryInGrid(guardList, NPC_VIOLET_HOLD_GUARD, 100.0f);
                        for (Creature* guard : guardList)
                            guard->SetVisible(false);
                    });

                    task.Repeat(6s);
                    break;
                case 5:
                    Talk(SAY_SINCLARI_INTRO_2);
                    task.Repeat(4s);
                    break;
                case 6:
                    me->HandleEmoteCommand(EMOTE_ONESHOT_TALK_NO_SHEATHE);
                    task.Repeat(1s);
                    break;
                case 7:
                    if (GameObject* mainDoor = _instance->GetGameObject(DATA_MAIN_DOOR))
                    {
                        mainDoor->SetGoState(GO_STATE_READY);
                        mainDoor->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
                    }
                    task.Repeat(5s);
                    break;
                case 8:
                    _instance->SetData(DATA_MAIN_EVENT_STATE, IN_PROGRESS);
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    break;
                default:
                    break;
            }
        });
    }

    void ScheduleOutro()
    {
        _scheduler.Schedule(4s, [this](TaskContext task)
        {
            Talk(SAY_SINCLARI_OUTRO);
            me->GetMotionMaster()->MovePoint(0, SinclariPositions[3]);

            task.Schedule(10s, [this](TaskContext /*task*/)
            {
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            });
        });
    }

    void JustSummoned(Creature* summon) override
    {
        ScriptedAI::JustSummoned(summon);
        _summons.Summon(summon);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        _summons.Despawn(summon);
        ScriptedAI::SummonedCreatureDespawn(summon);
    }

    private:
        InstanceScript* _instance;
        TaskScheduler _scheduler;

        SummonList _summons;
};

struct npc_azure_saboteurAI : public ScriptedAI
{
    npc_azure_saboteurAI(Creature* creature) : ScriptedAI(creature)
    {
        _instance = creature->GetInstanceScript();

        if (_instance->GetData(DATA_WAVE_COUNT) == 6)
            _bossId = _instance->GetData(DATA_1ST_BOSS);
        else
            _bossId = _instance->GetData(DATA_2ND_BOSS);
    }

    void StartPath(Movement::PointsArray path)
    {
        me->GetMotionMaster()->MoveSplinePath(&path);
    }

    void StartMovement()
    {
        switch (_bossId)
        {
            case DATA_MORAGG:
                me->GetMotionMaster()->MovePoint(0, { 1894.603f, 739.9231f, 47.66684f });
                break;
            case DATA_EREKEM:
                me->GetMotionMaster()->MovePoint(0, { 1873.747f, 864.1373f, 43.33349f });
                break;
            case DATA_ICHORON:
                me->GetMotionMaster()->MovePoint(0, { 1901.987f, 793.3254f, 38.65126f });
                break;
            case DATA_LAVANTHOR:
                me->GetMotionMaster()->MovePoint(0, { 1853.304f, 759.0161f, 38.65761f });
                break;
            case DATA_XEVOZZ:
                me->GetMotionMaster()->MovePoint(0, { 1906.666f, 842.3111f, 38.63351f });
                break;
            case DATA_ZURAMAT:
                me->GetMotionMaster()->MovePoint(0, { 1927.947f, 852.2986f, 47.19637f });
                break;
        }
    }

    void Reset() override
    {
        _scheduler.CancelAll();
        _scheduler.Schedule(2s, [this](TaskContext /*task*/)
        {
            StartMovement();
        });
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == POINT_MOTION_TYPE && pointId == 0)
        {
            _scheduler.Schedule(0s, [this](TaskContext task)
            {
                DoCastSelf(SPELL_SHIELD_DISRUPTION);

                if (task.GetRepeatCounter() < 2)
                    task.Repeat(1s);
                else
                {
                    task.Schedule(2s, [this](TaskContext /*task*/)
                    {
                        _instance->SetData(DATA_START_BOSS_ENCOUNTER, 1);
                        DoCastSelf(SPELL_TELEPORT_VISUAL);
                        me->DespawnOrUnsummon(1s);
                    });
                }
            });
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

    private:
        InstanceScript* _instance;
        TaskScheduler _scheduler;

        uint32 _bossId;
};

struct npc_violet_hold_teleportation_portal_commonAI : public ScriptedAI
{
    npc_violet_hold_teleportation_portal_commonAI(Creature* creature) : ScriptedAI(creature), _summons(me)
    {
        _instance = creature->GetInstanceScript();
        _portalLocation = 0;
    }

    void InitializeAI() override
    {
        ScriptedAI::InitializeAI();
        ScheduleTasks();
    }

    void SetData(uint32 type, uint32 data) override
    {
        if (type == DATA_PORTAL_LOCATION)
            _portalLocation = uint8(data);
    }

    void MoveInLineOfSight(Unit* /*who*/) override { }

    void EnterCombat(Unit* /*who*/) override { }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);
        if (summon->IsAIEnabled)
            summon->AI()->SetData(DATA_PORTAL_LOCATION, _portalLocation);
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        _summons.Despawn(summon);
    }

    virtual void ScheduleTasks() { }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

    protected:
        InstanceScript* _instance;
        SummonList _summons;
        TaskScheduler _scheduler;
        uint8 _portalLocation;
};

struct npc_violet_hold_teleportation_portalAI : public npc_violet_hold_teleportation_portal_commonAI
{
    npc_violet_hold_teleportation_portalAI(Creature* creature) : npc_violet_hold_teleportation_portal_commonAI(creature) { }

    void InitializeAI() override
    {
        npc_violet_hold_teleportation_portal_commonAI::InitializeAI();
        DoCastSelf(SPELL_PORTAL_PERIODIC, true);
        me->DisableRotate(true);
    }

    void SetData(uint32 type, uint32 data) override
    {
        npc_violet_hold_teleportation_portal_commonAI::SetData(type, data);

        if (type == DATA_PORTAL_PERIODIC_TICK)
        {
            if (data == 1)
            {
                uint32 entry = RAND(NPC_PORTAL_GUARDIAN, NPC_PORTAL_KEEPER);
                if (Creature* portalKeeper = DoSummon(entry, me, 2.0f, 0, TEMPSUMMON_DEAD_DESPAWN))
                    me->CastSpell(portalKeeper, SPELL_PORTAL_CHANNEL, false);

                if (Creature* sinclariTrigger = _instance->GetCreature(DATA_SINCLARI_TRIGGER))
                {
                    if (sinclariTrigger->IsAIEnabled)
                    {
                        if (entry == NPC_PORTAL_GUARDIAN)
                            sinclariTrigger->AI()->Talk(SAY_SINCLARI_PORTAL_GUARDIAN);
                        else if (entry == NPC_PORTAL_KEEPER)
                            sinclariTrigger->AI()->Talk(SAY_SINCLARI_PORTAL_KEEPER);
                    }
                }
            }
            else
            {
                uint8 k = _instance->GetData(DATA_WAVE_COUNT) < 12 ? 3 : 4;
                while (k--)
                {
                    uint32 entry = RAND(NPC_AZURE_INVADER_1, NPC_AZURE_INVADER_2, NPC_AZURE_SPELLBREAKER_1, NPC_AZURE_SPELLBREAKER_2, NPC_AZURE_MAGE_SLAYER_1, NPC_AZURE_MAGE_SLAYER_2, NPC_AZURE_BINDER_1, NPC_AZURE_BINDER_2);
                    DoSummon(entry, me, 2.0f, 20000, TEMPSUMMON_DEAD_DESPAWN);
                }
            }
        }
    }

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        npc_violet_hold_teleportation_portal_commonAI::SummonedCreatureDies(summon, killer);

        if (summon->GetEntry() == NPC_PORTAL_GUARDIAN || summon->GetEntry() == NPC_PORTAL_KEEPER)
        {
            _instance->SetData(DATA_WAVE_COUNT, _instance->GetData(DATA_WAVE_COUNT) + 1);
            me->DespawnOrUnsummon();
        }
    }
};

struct npc_violet_hold_teleportation_portal_eliteAI : public npc_violet_hold_teleportation_portal_commonAI
{
    npc_violet_hold_teleportation_portal_eliteAI(Creature* creature) : npc_violet_hold_teleportation_portal_commonAI(creature) { }

    void ScheduleTasks() override
    {
        _scheduler.Schedule(15s, [this](TaskContext task)
        {
            uint8 k = _instance->GetData(DATA_WAVE_COUNT) < 12 ? 3 : 4;
            while (k--)
            {
                uint32 entry = RAND(NPC_AZURE_CAPTAIN_1, NPC_AZURE_RAIDER_1, NPC_AZURE_STALKER_1, NPC_AZURE_SORCEROR_1);
                DoSummon(entry, me, 2.0f, 20000, TEMPSUMMON_DEAD_DESPAWN);
            }

            if (Creature* sinclariTrigger = _instance->GetCreature(DATA_SINCLARI_TRIGGER))
                if (sinclariTrigger->IsAIEnabled)
                    sinclariTrigger->AI()->Talk(SAY_SINCLARI_ELITE_SQUAD);

            task.Schedule(1s, [this](TaskContext /*task*/)
            {
                me->SetVisible(false);
            });
        });
    }

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        npc_violet_hold_teleportation_portal_commonAI::SummonedCreatureDies(summon, killer);

        if (_summons.empty())
        {
            _instance->SetData(DATA_WAVE_COUNT, _instance->GetData(DATA_WAVE_COUNT) + 1);
            me->DespawnOrUnsummon();
        }
    }
};

struct npc_violet_hold_teleportation_portal_introAI : public npc_violet_hold_teleportation_portal_commonAI
{
    npc_violet_hold_teleportation_portal_introAI(Creature* creature) : npc_violet_hold_teleportation_portal_commonAI(creature) { }

    void ScheduleTasks() override
    {
        if (_instance->GetData(DATA_MAIN_EVENT_STATE) != NOT_STARTED)
            return;

        _scheduler.Schedule(15s, [this](TaskContext task)
        {
            uint32 entry = RAND(NPC_AZURE_INVADER_1, NPC_AZURE_MAGE_SLAYER_1, NPC_AZURE_BINDER_1);
            DoSummon(entry, me, 2.0f, 20000, TEMPSUMMON_DEAD_DESPAWN);

            task.Repeat();
        });
    }
};

struct violet_hold_trashAI : public npc_escortAI
{
    violet_hold_trashAI(Creature* creature) : npc_escortAI(creature)
    {
        _instance = creature->GetInstanceScript();

        _lastWaypointId = 0;

        SetDespawnAtEnd(false);

        _scheduler.SetValidator([this]
        {
            return !me->HasUnitState(UNIT_STATE_CASTING);
        });
    }

    void Reset() override
    {
        _scheduler.CancelAll();
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (roll_chance_i(20) && me->GetEntry() != 30664 && me->GetEntry() != 30963)
            Talk(SAY_PORTAL_DEATH);
    }

    template <size_t N>
    Position const* GetPathAndInitLastWaypointFrom(Position const (&path)[N])
    {
        _lastWaypointId = N - 1;
        return &path[0];
    }

    void SetData(uint32 type, uint32 data) override
    {
        if (type == DATA_PORTAL_LOCATION)
        {
            Position const* path = nullptr;

            switch (data)
            {
                case 0:
                    path = GetPathAndInitLastWaypointFrom(FirstPortalWPs);
                    break;
                case 7:
                    switch (urand(0, 1))
                    {
                        case 0:
                            path = GetPathAndInitLastWaypointFrom(SecondPortalFirstWPs);
                            break;
                        case 1:
                            path = GetPathAndInitLastWaypointFrom(SecondPortalSecondWPs);
                            break;
                    }
                    break;
                case 2:
                    path = GetPathAndInitLastWaypointFrom(ThirdPortalWPs);
                    break;
                case 6:
                    path = GetPathAndInitLastWaypointFrom(FourthPortalWPs);
                    break;
                case 1:
                    path = GetPathAndInitLastWaypointFrom(FifthPortalWPs);
                    break;
                case 5:
                    path = GetPathAndInitLastWaypointFrom(SixthPortalWPs);
                    break;
                default:
                    path = GetPathAndInitLastWaypointFrom(DefaultPortalWPs);
                    break;
            }

            if (path)
            {
                for (uint32 i = 0; i <= _lastWaypointId; i++)
                    AddWaypoint(i, path[i].GetPositionX() + irand(-1, 1), path[i].GetPositionY() + irand(-1, 1), path[i].GetPositionZ(), 0);
                me->SetHomePosition(path[_lastWaypointId].GetPositionX(), path[_lastWaypointId].GetPositionY(), path[_lastWaypointId].GetPositionZ(), float(M_PI));
            }

            Start(true, true);
        }
    }

    void WaypointReached(uint32 waypointId) override
    {
        if (waypointId == _lastWaypointId)
            CreatureStartAttackDoor();
    }

    void EnterCombat(Unit* who) override
    {
        if (roll_chance_i(50) && me->GetEntry() != 30664 && me->GetEntry() != 30963)
            Talk(SAY_PORTAL_AGGRO);

        npc_escortAI::EnterCombat(who);
        ScheduledTasks();
    }

    void UpdateEscortAI(uint32 diff) override
    {
        if (_instance->GetData(DATA_MAIN_EVENT_STATE) != IN_PROGRESS)
            me->CastStop();

        if (!UpdateVictim())
            return;

        _scheduler.Update(diff,
            std::bind(&npc_escortAI::DoMeleeAttackIfReady, this));
    }

    virtual void ScheduledTasks() { }

    void CreatureStartAttackDoor()
    {
        me->SetReactState(REACT_DEFENSIVE);
        DoCastAOE(SPELL_DESTROY_DOOR_SEAL);
    }

    protected:
        InstanceScript* _instance;
        TaskScheduler _scheduler;

        uint32 _lastWaypointId;
};

struct npc_azure_invaderAI : public violet_hold_trashAI
{
    npc_azure_invaderAI(Creature* creature) : violet_hold_trashAI(creature) { }

    void ScheduledTasks() override
    {
        Talk(SAY_AGGRO);
        if (me->GetEntry() == NPC_AZURE_INVADER_1)
        {
            _scheduler.Schedule(5s, [this](TaskContext task)
            {
                DoCastVictim(SPELL_CLEAVE);
                task.Repeat();
            });

            _scheduler.Schedule(4s, [this](TaskContext task)
            {
                DoCastVictim(SPELL_IMPALE);
                task.Repeat();
            });
        }
        else if (me->GetEntry() == NPC_AZURE_INVADER_2)
        {
            _scheduler.Schedule(5s, [this](TaskContext task)
            {
                DoCastVictim(SPELL_BRUTAL_STRIKE);
                task.Repeat();
            });

            _scheduler.Schedule(4s, [this](TaskContext task)
            {
                DoCastVictim(SPELL_SUNDER_ARMOR);
                task.Repeat(8s, 10s);
            });
        }
    }
};

struct npc_azure_binderAI : public violet_hold_trashAI
{
    npc_azure_binderAI(Creature* creature) : violet_hold_trashAI(creature) { }

    void ScheduledTasks() override
    {
        if (me->GetEntry() == NPC_AZURE_BINDER_1)
        {
            _scheduler.Schedule(5s, [this](TaskContext task)
            {
                DoCastSelf(SPELL_ARCANE_EXPLOSION);
                task.Repeat();
            });

            _scheduler.Schedule(4s, [this](TaskContext task)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f))
                    DoCast(target, SPELL_ARCANE_BARRAGE);
                task.Repeat(6s);
            });
        }
        else if (me->GetEntry() == NPC_AZURE_BINDER_2)
        {
            _scheduler.Schedule(5s, [this](TaskContext task)
            {
                DoCastSelf(SPELL_FROST_NOVA);
                task.Repeat();
            });

            _scheduler.Schedule(4s, [this](TaskContext task)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f))
                    DoCast(target, SPELL_FROSTBOLT);
                task.Repeat(6s);
            });
        }
    }
};

struct npc_azure_mage_slayerAI : public violet_hold_trashAI
{
    npc_azure_mage_slayerAI(Creature* creature) : violet_hold_trashAI(creature) { }

    void ScheduledTasks() override
    {
        if (me->GetEntry() == NPC_AZURE_MAGE_SLAYER_1)
        {
            _scheduler.Schedule(5s, [this](TaskContext task)
            {
                DoCastSelf(SPELL_ARCANE_EMPOWERMENT);
                task.Repeat(14s);
            });
        }
        else if (me->GetEntry() == NPC_AZURE_MAGE_SLAYER_2)
        {
            _scheduler.Schedule(5s, [this](TaskContext task)
            {
                // wrong spellid?
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f))
                    DoCast(target, SPELL_SPELL_LOCK);
                task.Repeat(9s);
            });
        }
    }
};

struct npc_azure_raiderAI : public violet_hold_trashAI
{
    npc_azure_raiderAI(Creature* creature) : violet_hold_trashAI(creature) { }

    void ScheduledTasks() override
    {
        _scheduler.Schedule(5s, [this](TaskContext task)
        {
            DoCastVictim(SPELL_CONCUSSION_BLOW);
            task.Repeat();
        });

        _scheduler.Schedule(8s, [this](TaskContext task)
        {
            DoCastSelf(SPELL_MAGIC_REFLECTION);
            task.Repeat(10s, 15s);
        });
    }
};

struct npc_azure_stalkerAI : public violet_hold_trashAI
{
    npc_azure_stalkerAI(Creature* creature) : violet_hold_trashAI(creature) { }

    void ScheduledTasks() override
    {
        _scheduler.Schedule(8s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f))
                DoCast(target, SPELL_TACTICAL_BLINK);

            task.Schedule(1300ms, [this](TaskContext /*task*/)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0, 5.0f))
                    DoCast(target, SPELL_BACKSTAB);
            });

            task.Repeat();
        });
    }
};

struct npc_azure_spellbreakerAI : public violet_hold_trashAI
{
    npc_azure_spellbreakerAI(Creature* creature) : violet_hold_trashAI(creature) { }

    void ScheduledTasks() override
    {
        if (me->GetEntry() == NPC_AZURE_SPELLBREAKER_1)
        {
            _scheduler.Schedule(5s, [this](TaskContext task)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f))
                    DoCast(target, SPELL_ARCANE_BLAST);
                task.Repeat(6s);
            });

            _scheduler.Schedule(4s, [this](TaskContext task)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f))
                    DoCast(target, SPELL_SLOW);
                task.Repeat(5s);
            });
        }
        else if (me->GetEntry() == NPC_AZURE_SPELLBREAKER_2)
        {
            _scheduler.Schedule(5s, [this](TaskContext task)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f))
                    DoCast(target, SPELL_CHAINS_OF_ICE);
                task.Repeat(7s);
            });

            _scheduler.Schedule(4s, [this](TaskContext task)
            {
                DoCastAOE(SPELL_CONE_OF_COLD);
                task.Repeat(3s);
            });
        }
    }
};

struct npc_azure_captainAI : public violet_hold_trashAI
{
    npc_azure_captainAI(Creature* creature) : violet_hold_trashAI(creature) { }

    void ScheduledTasks() override
    {
        _scheduler.Schedule(5s, [this](TaskContext task)
        {
            DoCastVictim(SPELL_MORTAL_STRIKE);
            task.Repeat();
        });

        _scheduler.Schedule(8s, [this](TaskContext task)
        {
            DoCastSelf(SPELL_WHIRLWIND_OF_STEEL);
            task.Repeat();
        });
    }
};

struct npc_azure_sorcerorAI : public violet_hold_trashAI
{
    npc_azure_sorcerorAI(Creature* creature) : violet_hold_trashAI(creature) { }

    void ScheduledTasks() override
    {
        _scheduler.Schedule(4s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 35.0f))
                DoCast(target, SPELL_ARCANE_STREAM);
            task.Repeat(5s, 10s);
        });

        _scheduler.Schedule(0s, [this](TaskContext task)
        {
            DoCastSelf(SPELL_MANA_DETONATION);
            task.Repeat(2s, 6s);
        });
    }
};

struct npc_violet_hold_defense_systemAI : public ScriptedAI
{
    npc_violet_hold_defense_systemAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        ScheduledTasks();
        me->DespawnOrUnsummon(7s);
    }

    void ScheduledTasks()
    {
        _scheduler.Schedule(Seconds(4), [this](TaskContext task)
        {
            DoCastAOE(SPELL_ARCANE_LIGHTNING_DAMAGE);
            DoCastAOE(SPELL_ARCANE_LIGHTNING_DUMMY);
            if (task.GetRepeatCounter() == 2)
                DoCastAOE(SPELL_ARCANE_LIGHTNING_INSTAKILL);
            else
                task.Repeat(1s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

    private:
        TaskScheduler _scheduler;
};

class go_activation_crystal : public GameObjectScript
{
    public:
        go_activation_crystal() : GameObjectScript("go_activation_crystal") { }

        bool OnGossipHello(Player* player, GameObject* go) override
        {
            player->CastSpell(player, SPELL_CRYSTAL_ACTIVATION, true);
            return false;
        }
};

// 58040 - Destroy Door Seal
class spell_violet_hold_destroy_door_seal_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_violet_hold_destroy_door_seal_AuraScript);

    bool Load() override
    {
        _instance = GetUnitOwner()->GetInstanceScript();
        return _instance != nullptr;
    }

    void PeriodicTick(AuraEffect const* /*aurEff*/)
    {
        PreventDefaultAction();
        if (uint32 integrity = _instance->GetData(DATA_DOOR_INTEGRITY))
            _instance->SetData(DATA_DOOR_INTEGRITY, integrity - 1);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_violet_hold_destroy_door_seal_AuraScript::PeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }

    private:
        InstanceScript* _instance = nullptr;
};

// 58008 - Portal Periodic
class spell_violet_hold_portal_periodic_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_violet_hold_portal_periodic_AuraScript);

    void PeriodicTick(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        if (GetTarget()->IsAIEnabled)
            GetTarget()->GetAI()->SetData(DATA_PORTAL_PERIODIC_TICK, aurEff->GetTickNumber());
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_violet_hold_portal_periodic_AuraScript::PeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

// 62138 - Teleport to Inside Violet Hold
class spell_violet_hold_teleport_player_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_violet_hold_teleport_player_SpellScript);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_TELEPORT_PLAYER_EFFECT });
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            target->CastSpell(target, SPELL_TELEPORT_PLAYER_EFFECT, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_violet_hold_teleport_player_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

void AddSC_violet_hold()
{
    new CreatureAILoader<npc_sinclariAI>("npc_sinclari_vh");
    new CreatureAILoader<npc_violet_hold_teleportation_portalAI>("npc_violet_hold_teleportation_portal");
    new CreatureAILoader<npc_violet_hold_teleportation_portal_eliteAI>("npc_violet_hold_teleportation_portal_elite");
    new CreatureAILoader<npc_violet_hold_teleportation_portal_introAI>("npc_violet_hold_teleportation_portal_intro");
    new CreatureAILoader<npc_azure_invaderAI>("npc_azure_invader");
    new CreatureAILoader<npc_azure_spellbreakerAI>("npc_azure_spellbreaker");
    new CreatureAILoader<npc_azure_binderAI>("npc_azure_binder");
    new CreatureAILoader<npc_azure_mage_slayerAI>("npc_azure_mage_slayer");
    new CreatureAILoader<npc_azure_captainAI>("npc_azure_captain");
    new CreatureAILoader<npc_azure_sorcerorAI>("npc_azure_sorceror");
    new CreatureAILoader<npc_azure_raiderAI>("npc_azure_raider");
    new CreatureAILoader<npc_azure_stalkerAI>("npc_azure_stalker");
    new CreatureAILoader<npc_azure_saboteurAI>("npc_azure_saboteur");
    new CreatureAILoader<npc_violet_hold_defense_systemAI>("npc_violet_hold_defense_system");
    new go_activation_crystal();
    new AuraScriptLoaderEx<spell_violet_hold_destroy_door_seal_AuraScript>("spell_violet_hold_destroy_door_seal");
    new AuraScriptLoaderEx<spell_violet_hold_portal_periodic_AuraScript>("spell_violet_hold_portal_periodic");
    new SpellScriptLoaderEx<spell_violet_hold_teleport_player_SpellScript>("spell_violet_hold_teleport_player");
}
