/*
 * Copyright (C)
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
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "Player.h"
#include "CombatAI.h"
#include "PassiveAI.h"
#include "SpellInfo.h"
#include "Vehicle.h"
#include "SpellAuras.h"

// Ours
enum AlchemistItemRequirements
{
    QUEST_ALCHEMIST_APPRENTICE        = 12541,
    NPC_FINKLESTEIN                    = 28205,
};

const uint32 AA_ITEM_ENTRY[24] = {38336, 39669, 38342, 38340, 38344, 38369, 38396, 38398, 38338, 38386, 38341, 38384, 38397, 38381, 38337, 38393, 38339, 39668, 39670, 38346, 38379, 38345, 38343, 38370};
const uint32 AA_AURA_ID[24]    = {51095, 53153, 51100, 51087, 51091, 51081, 51072, 51079, 51018, 51067, 51055, 51064, 51077, 51062, 51057, 51069, 51059, 53150, 53158, 51093, 51097, 51102, 51083, 51085};
const char*  AA_ITEM_NAME[24]  = {"Crystallized Hogsnot", "Ghoul Drool", "Trollbane", "Amberseed", "Shrunken Dragon's Claw",
"Wasp's Wings", "Hairy Herring Head", "Icecrown Bottled Water", "Knotroot", "Muddy Mire Maggot", "Pickled Eagle Egg",
"Pulverized Gargoyle Teeth", "Putrid Pirate Perspiration", "Seasoned Slider Cider", "Speckled Guano", "Spiky Spider Egg",
"Withered Batwing", "Abomination Guts", "Blight Crystal", "Chilled Serpent Mucus", "Crushed Basilisk Crystals",
"Frozen Spider Ichor", "Prismatic Mojo", "Raptor Claw"};


class npc_finklestein : public CreatureScript
{
public:
    npc_finklestein() : CreatureScript("npc_finklestein") { }

        struct npc_finklesteinAI : public ScriptedAI
        {
            npc_finklesteinAI(Creature* creature) : ScriptedAI(creature) {}

            std::map<uint64, uint32> questList;

            void ClearPlayerOnTask(uint64 guid)
            {
                std::map<uint64, uint32>::iterator itr = questList.find(guid);
                if (itr != questList.end())
                    questList.erase(itr);
            }

            bool IsPlayerOnTask(uint64 guid)
            {
                std::map<uint64, uint32>::const_iterator itr = questList.find(guid);
                return itr != questList.end();
            }

            void RightClickCauldron(uint64 guid)
            {
                if (questList.empty())
                    return;

                std::map<uint64, uint32>::iterator itr = questList.find(guid);
                if (itr == questList.end())
                    return;

                Player* player = ObjectAccessor::GetPlayer(*me, guid);
                if (player)
                {
                    uint32 itemCode = itr->second;

                    uint32 itemEntry = GetTaskItemEntry(itemCode);
                    uint32 auraId = GetTaskAura(itemCode);
                    uint32 counter = GetTaskCounter(itemCode);
                    if (player->HasAura(auraId))
                    {
                        // player still has aura, but no item. Skip
                        if (!player->HasItemCount(itemEntry))
                            return;

                        // if we are here, all is ok (aura and item present)
                        player->DestroyItemCount(itemEntry, 1, true);
                        player->RemoveAurasDueToSpell(auraId);

                        if (counter < 6)
                        {
                            StartNextTask(player->GetGUID(), counter+1);
                            return;
                        }
                        else
                            player->KilledMonsterCredit(28248, 0);
                    }
                    else
                    {
                        // if we are here, it means we failed :(
                        player->SetQuestStatus(QUEST_ALCHEMIST_APPRENTICE, QUEST_STATUS_FAILED);
                    }
                }
                questList.erase(itr);
            }

            // Generate a Task and announce it to the player
            void StartNextTask(uint64 playerGUID, uint32 counter)
            {
                if (counter > 6)
                    return;

                Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
                if (!player)
                    return;

                // Generate Item Code
                uint32 itemCode = SelectRandomCode(counter);
                questList[playerGUID] = itemCode;

                // Decode Item Entry, Get Item Name, Generate Emotes
                uint32 itemEntry = GetTaskItemEntry(itemCode);
                uint32 auraId = GetTaskAura(itemCode);
                const char* itemName = GetTaskItemName(itemCode);

                switch (counter)
                {
                    case 1:
                        me->MonsterTextEmote("Quickly, get me some...", player, true);
                        me->MonsterTextEmote(itemName, player, true);
                        me->CastSpell(player, auraId, true);
                        break;
                    case 2:
                        me->MonsterTextEmote("Find me some...", player, true);
                        me->MonsterTextEmote(itemName, player, true);
                        me->CastSpell(player, auraId, true);
                        break;
                    case 3:
                        me->MonsterTextEmote("I think it needs...", player, true);
                        me->MonsterTextEmote(itemName, player, true);
                        me->CastSpell(player, auraId, true);
                        break;
                    case 4:
                        me->MonsterTextEmote("Alright, now fetch me some...", player, true);
                        me->MonsterTextEmote(itemName, player, true);
                        me->CastSpell(player, auraId, true);
                        break;
                    case 5:
                        me->MonsterTextEmote("Before it thickens, we must add...", player, true);
                        me->MonsterTextEmote(itemName, player, true);
                        me->CastSpell(player, auraId, true);
                        break;
                    case 6:
                        me->MonsterTextEmote("It's thickening! Quickly get me some...", player, true);
                        me->MonsterTextEmote(itemName, player, true);
                        me->CastSpell(player, auraId, true);
                        break;
                }
            }

            uint32 SelectRandomCode(uint32 counter)  { return (counter * 100 + urand(0,23)); }

            uint32 GetTaskCounter(uint32 itemcode)   { return itemcode / 100; }
            uint32 GetTaskAura(uint32 itemcode)      { return AA_AURA_ID[itemcode % 100]; }
            uint32 GetTaskItemEntry(uint32 itemcode) { return AA_ITEM_ENTRY[itemcode % 100]; }
            const char* GetTaskItemName(uint32 itemcode)  { return AA_ITEM_NAME[itemcode % 100]; }

        };

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_ALCHEMIST_APPRENTICE)
                if (creature->AI() && CAST_AI(npc_finklestein::npc_finklesteinAI, creature->AI()))
                    CAST_AI(npc_finklestein::npc_finklesteinAI, creature->AI())->ClearPlayerOnTask(player->GetGUID());

            return true;
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (creature->IsQuestGiver())
                player->PrepareQuestMenu(creature->GetGUID());

            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

            if (player->GetQuestStatus(QUEST_ALCHEMIST_APPRENTICE) == QUEST_STATUS_INCOMPLETE)
            {
                if (creature->AI() && CAST_AI(npc_finklestein::npc_finklesteinAI, creature->AI()))
                    if (!CAST_AI(npc_finklestein::npc_finklesteinAI, creature->AI())->IsPlayerOnTask(player->GetGUID()))
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'm ready to begin. What is the first ingredient you require?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

                player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            }

            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
        {
            player->CLOSE_GOSSIP_MENU();
            if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
            {
                player->CLOSE_GOSSIP_MENU();
                if (creature->AI() && CAST_AI(npc_finklestein::npc_finklesteinAI, creature->AI()))
                    CAST_AI(npc_finklestein::npc_finklesteinAI, creature->AI())->StartNextTask(player->GetGUID(), 1);
            }

            return true;
        }

    CreatureAI *GetAI(Creature* creature) const
    {
        return new npc_finklesteinAI(creature);
    }
};

class go_finklestein_cauldron : public GameObjectScript
{
public:
    go_finklestein_cauldron() : GameObjectScript("go_finklestein_cauldron") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        Creature* finklestein = go->FindNearestCreature(NPC_FINKLESTEIN, 30.0f, true);
        if (finklestein && finklestein->AI())
            CAST_AI(npc_finklestein::npc_finklesteinAI, finklestein->AI())->RightClickCauldron(player->GetGUID());

        return true;
    }
};

enum eFeedinDaGoolz
{
    NPC_DECAYING_GHOUL                            = 28565,
    GO_BOWL                                     = 190656,
};

class npc_feedin_da_goolz : public CreatureScript
{
public:
    npc_feedin_da_goolz() : CreatureScript("npc_feedin_da_goolz") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_feedin_da_goolzAI(creature);
    }

    struct npc_feedin_da_goolzAI : public NullCreatureAI
    {
        npc_feedin_da_goolzAI(Creature* creature) : NullCreatureAI(creature) { findTimer = 1; checkTimer = 0; ghoulFed = 0; }

        uint32 findTimer;
        uint32 checkTimer;
        uint64 ghoulFed;

        void UpdateAI(uint32 diff)
        {
            if (findTimer)
            {
                findTimer += diff;
                if (findTimer >= 1000)
                {
                    if (Creature* ghoul = me->FindNearestCreature(NPC_DECAYING_GHOUL, 30.0f, true))
                    {
                        ghoul->SetReactState(REACT_DEFENSIVE);
                        float o = me->GetAngle(ghoul);
                        ghoul->GetMotionMaster()->MovePoint(1, me->GetPositionX()+2*cos(o), me->GetPositionY()+2*sin(o), me->GetPositionZ());
                        checkTimer = 1;
                        findTimer = 0;
                    }
                    else
                        findTimer = 1;
                }
                return;
            }

            if (checkTimer)
            {
                checkTimer += diff;
                if (checkTimer >= 1500)
                {
                    checkTimer = 1;
                    if (!ghoulFed)
                    {
                        if (Creature* ghoul = me->FindNearestCreature(NPC_DECAYING_GHOUL, 3.0f, true))
                        {
                            ghoulFed = ghoul->GetGUID();
                            ghoul->HandleEmoteCommand(EMOTE_ONESHOT_EAT);
                        }
                    }
                    else
                    {
                        if (GameObject* bowl = me->FindNearestGameObject(GO_BOWL, 10.0f))
                            bowl->Delete();

                        if (Creature* ghoul = ObjectAccessor::GetCreature(*me, ghoulFed))
                        {
                            ghoul->SetReactState(REACT_AGGRESSIVE);
                            ghoul->GetMotionMaster()->MoveTargetedHome();
                        }

                        if (Unit* owner = me->ToTempSummon()->GetSummoner())
                            if (Player* player = owner->ToPlayer())
                                player->KilledMonsterCredit(me->GetEntry(), 0);

                        me->DespawnOrUnsummon(1);
                    }
                }
            }
        }
    };
};

/*####
## npc_drakuru_shackles
####*/

enum DrakuruShackles
{
    NPC_RAGECLAW                             = 29686,
    QUEST_TROLLS_IS_GONE_CRAZY               = 12861,
    SPELL_LEFT_CHAIN                         = 59951,
    SPELL_RIGHT_CHAIN                        = 59952,
    SPELL_UNLOCK_SHACKLE                     = 55083,
    SPELL_FREE_RAGECLAW                      = 55223
};

class npc_drakuru_shackles : public CreatureScript
{
public:
    npc_drakuru_shackles() : CreatureScript("npc_drakuru_shackles") { }

    struct npc_drakuru_shacklesAI : public NullCreatureAI
    {
        npc_drakuru_shacklesAI(Creature* creature) : NullCreatureAI(creature)
        {
            _rageclawGUID = 0;
            timer = 0;
        }

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void UpdateAI(uint32 diff)
        {
            timer += diff;
            if (timer >= 2000)
            {
                timer = 0;
                if (_rageclawGUID)
                    return;

                if (Creature* cr = me->FindNearestCreature(NPC_RAGECLAW, 10.0f))
                {
                    _rageclawGUID = cr->GetGUID();
                    LockRageclaw(cr);
                }
            }
        }

        void LockRageclaw(Creature* rageclaw)
        {
            // pointer check not needed
            me->SetFacingToObject(rageclaw);
            rageclaw->SetFacingToObject(me);

            DoCast(rageclaw, SPELL_LEFT_CHAIN, true);
            DoCast(rageclaw, SPELL_RIGHT_CHAIN, true);
        }

        void UnlockRageclaw(Unit* who, Creature* rageclaw)
        {
            // pointer check not needed
            DoCast(rageclaw, SPELL_FREE_RAGECLAW, true);
            _rageclawGUID = 0;
            me->DespawnOrUnsummon(1);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_UNLOCK_SHACKLE)
            {
                if (caster->ToPlayer()->GetQuestStatus(QUEST_TROLLS_IS_GONE_CRAZY) == QUEST_STATUS_INCOMPLETE)
                {
                    if (Creature* rageclaw = ObjectAccessor::GetCreature(*me, _rageclawGUID))
                    {
                        UnlockRageclaw(caster, rageclaw);
                        caster->ToPlayer()->KilledMonster(rageclaw->GetCreatureTemplate(), _rageclawGUID);
                        me->DespawnOrUnsummon();
                    }
                    else
                        me->setDeathState(JUST_DIED);
                }
            }
        }

        private:
            uint64 _rageclawGUID;
            uint32 timer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_drakuru_shacklesAI(creature);
    }
};

/*####
## npc_captured_rageclaw
####*/

enum Rageclaw
{
    SPELL_UNSHACKLED                         = 55085,
    SPELL_KNEEL                              = 39656,
    SAY_RAGECLAW                             = 0
};

class npc_captured_rageclaw : public CreatureScript
{
public:
    npc_captured_rageclaw() : CreatureScript("npc_captured_rageclaw") { }

    struct npc_captured_rageclawAI : public NullCreatureAI
    {
        npc_captured_rageclawAI(Creature* creature) : NullCreatureAI(creature) { }

        void Reset()
        {
            me->setFaction(35);
            DoCast(me, SPELL_KNEEL, true); // Little Hack for kneel - Thanks Illy :P
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_FREE_RAGECLAW)
            {
                me->RemoveAurasDueToSpell(SPELL_LEFT_CHAIN);
                me->RemoveAurasDueToSpell(SPELL_RIGHT_CHAIN);
                me->RemoveAurasDueToSpell(SPELL_KNEEL);
                me->setFaction(me->GetCreatureTemplate()->faction);
                DoCast(me, SPELL_UNSHACKLED, true);
                Talk(SAY_RAGECLAW);
                me->GetMotionMaster()->MoveRandom(10);
                me->DespawnOrUnsummon(10000);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_captured_rageclawAI(creature);
    }
};


// Theirs
/*####
## npc_released_offspring_harkoa
####*/

class npc_released_offspring_harkoa : public CreatureScript
{
public:
    npc_released_offspring_harkoa() : CreatureScript("npc_released_offspring_harkoa") { }

    struct npc_released_offspring_harkoaAI : public ScriptedAI
    {
        npc_released_offspring_harkoaAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            float x, y, z;
            me->GetClosePoint(x, y, z, me->GetObjectSize() / 3, 25.0f);
            me->GetMotionMaster()->MovePoint(0, x, y, z);
        }

        void MovementInform(uint32 Type, uint32 /*uiId*/)
        {
            if (Type != POINT_MOTION_TYPE)
                return;
            me->DespawnOrUnsummon();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_released_offspring_harkoaAI(creature);
    }
};

/*######
## npc_crusade_recruit
######*/

enum CrusadeRecruit
{
    SPELL_QUEST_CREDIT                       = 50633,
    QUEST_TROLL_PATROL_INTESTINAL_FORTITUDE  = 12509,
    SAY_RECRUIT                              = 0
};

enum CrusadeRecruitEvents
{
    EVENT_RECRUIT_1                          = 1,
    EVENT_RECRUIT_2                          = 2
};

class npc_crusade_recruit : public CreatureScript
{
public:
    npc_crusade_recruit() : CreatureScript("npc_crusade_recruit") { }

    struct npc_crusade_recruitAI : public ScriptedAI
    {
        npc_crusade_recruitAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_COWER);
            _heading = me->GetOrientation();
        }

        void UpdateAI(uint32 diff)
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RECRUIT_1:
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                        Talk(SAY_RECRUIT);
                        _events.ScheduleEvent(EVENT_RECRUIT_2, 3000);
                        break;
                    case EVENT_RECRUIT_2:
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovePoint(0, me->GetPositionX() + (cos(_heading) * 10), me->GetPositionY() + (sin(_heading) * 10), me->GetPositionZ());
                        me->DespawnOrUnsummon(5000);
                        break;
                    default:
                        break;
                }
            }

            if (!UpdateVictim())
                return;
        }

        void sGossipSelect(Player* player, uint32 /*sender*/, uint32 /*action*/)
        {
            _events.ScheduleEvent(EVENT_RECRUIT_1, 100);
            player->CLOSE_GOSSIP_MENU();
            me->CastSpell(player, SPELL_QUEST_CREDIT, true);
            me->SetFacingToObject(player);
        }

        private:
        EventMap _events;
        float    _heading; // Store creature heading
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_crusade_recruitAI(creature);
    }
};

/*######
## Quest 12916: Our Only Hope!
## go_scourge_enclosure
######*/

enum ScourgeEnclosure
{
    QUEST_OUR_ONLY_HOPE                      = 12916,
    NPC_GYMER_DUMMY                          = 29928, // From quest template
    SPELL_GYMER_LOCK_EXPLOSION               = 55529
};

class go_scourge_enclosure : public GameObjectScript
{
public:
    go_scourge_enclosure() : GameObjectScript("go_scourge_enclosure") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        go->UseDoorOrButton();
        if (player->GetQuestStatus(QUEST_OUR_ONLY_HOPE) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* gymerDummy = go->FindNearestCreature(NPC_GYMER_DUMMY, 20.0f);
            if (gymerDummy)
            {
                player->KilledMonsterCredit(gymerDummy->GetEntry(), gymerDummy->GetGUID());
                gymerDummy->CastSpell(gymerDummy, SPELL_GYMER_LOCK_EXPLOSION, true);
                gymerDummy->DespawnOrUnsummon();
            }
        }
        return true;
    }
};



enum StormCloud
{
    STORM_COULD         = 29939,
    HEALING_WINDS       = 55549,
    STORM_VISUAL        = 55708,
    GYMERS_GRAB         = 55516,
    RIDE_VEHICLE        = 43671
};

class npc_storm_cloud : public CreatureScript
{
public:
    npc_storm_cloud() : CreatureScript("npc_storm_cloud") { }

    struct npc_storm_cloudAI : public ScriptedAI
    {
        npc_storm_cloudAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            me->CastSpell(me, STORM_VISUAL, true);
        }

        void JustRespawned()
        {
            Reset();
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id != GYMERS_GRAB)
                return;

            if (Vehicle* veh = caster->GetVehicleKit())
                if (veh->GetAvailableSeatCount() != 0)
            {
                me->CastSpell(caster, RIDE_VEHICLE, true);
                me->CastSpell(caster, HEALING_WINDS, true);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_storm_cloudAI(creature);
    }
};

Position const drakuruSpawnPosition = { 6175.25f, -2017.66f, 590.961f, 2.98451f };
uint32 const drakuruEntry = 28998;

enum drakuruMidLevel
{
    SPELL_KILL_CREDIT_1     = 52224,
    SPELL_KILL_CREDIT_2     = 52253,
    SPELL_KILL_CREDIT_3     = 52355,
    SPELL_KILL_CREDIT_4     = 52680,
    SPELL_KILL_CREDIT_5     = 52675,

    SPELL_DRAKURU_TELE      = 52863
};

struct npc_overlord_drakuru_midlevel_AI : public ScriptedAI
{
    npc_overlord_drakuru_midlevel_AI(Creature* creature) : ScriptedAI(creature) { }

    void sGossipSelect(Player* player, uint32 sender, uint32 actionId) override
    {
        if (!player)
            return;

        switch (actionId)
        {
            case 0:
            {
                Creature* drakuru = ObjectAccessor::GetCreature(*me, _drakuruGUID);

                if (!drakuru)
                    if (Creature* drakuruProper = me->SummonCreature(drakuruEntry, drakuruSpawnPosition, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 600000))
                        _drakuruGUID = drakuruProper->GetGUID();

                player->CastSpell(player, SPELL_DRAKURU_TELE, true);
                break;
            }
            case 1:
                DoCast(player, SPELL_KILL_CREDIT_1, true);
                break;
            case 2:
                DoCast(player, SPELL_KILL_CREDIT_2, true);
                break;
            case 3:
                DoCast(player, SPELL_KILL_CREDIT_3, true);
                break;
            case 4:
                DoCast(player, SPELL_KILL_CREDIT_4, true);
                break;
            case 5:
                DoCast(player, SPELL_KILL_CREDIT_5, true);
                break;
        }

        player->PlayerTalkClass->SendCloseGossip();
    }
private:
    uint64 _drakuruGUID;
};


void AddSC_zuldrak()
{
    // Ours
    new npc_finklestein();
    new go_finklestein_cauldron();
    new npc_feedin_da_goolz();
    new npc_drakuru_shackles();
    new npc_captured_rageclaw();
    new CreatureAILoader<npc_overlord_drakuru_midlevel_AI>("npc_overlord_drakuru_midlevel");

    // Theirs
    new npc_released_offspring_harkoa();
    new npc_crusade_recruit();
    new go_scourge_enclosure();
    new npc_storm_cloud();
}
