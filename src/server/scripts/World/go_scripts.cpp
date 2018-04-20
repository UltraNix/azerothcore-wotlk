/*
 * Copyright (C)
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

/* ContentData
go_cat_figurine (the "trap" version of GO, two different exist)
go_barov_journal
go_ethereum_prison
go_ethereum_stasis
go_sacred_fire_of_life
go_shrine_of_the_birds
go_southfury_moonstone
go_resonite_cask
go_tablet_of_madness
go_tablet_of_the_seven
go_tele_to_dalaran_crystal
go_tele_to_violet_stand
go_scourge_cage
go_jotunheim_cage
go_table_theka
go_soulwell
go_bashir_crystalforge
go_soulwell
go_dragonflayer_cage
go_tadpole_cage
go_amberpine_outhouse
go_hive_pod
go_veil_skith_cage
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "GameObjectAI.h"
#include "Spell.h"
#include "Player.h"
#include "WorldSession.h"

// Ours
/*######
## go_noblegarden_colored_egg
######*/
class go_noblegarden_colored_egg : public GameObjectScript
{
public:
    go_noblegarden_colored_egg() : GameObjectScript("go_noblegarden_colored_egg") { }

    bool OnGossipHello(Player* player, GameObject* /*pGO*/)
    {
        if (roll_chance_i(5))
            player->CastSpell(player, 61734, true); // SPELL NOBLEGARDEN BUNNY
        return false;
    }
};

class go_seer_of_zebhalak : public GameObjectScript
{
public:
    go_seer_of_zebhalak() : GameObjectScript("go_seer_of_zebhalak") { }

    bool OnGossipHello(Player* player, GameObject* /*pGO*/)
    {
        if (player->GetQuestStatus(12007) == QUEST_STATUS_INCOMPLETE)
            player->CastSpell(player, 47293, true);
        return true;
    }
};

class go_mistwhisper_treasure : public GameObjectScript
{
public:
    go_mistwhisper_treasure() : GameObjectScript("go_mistwhisper_treasure") { }

    bool OnGossipHello(Player* pPlayer, GameObject *pGo)
    {
        if (!pGo->FindNearestCreature(28105, 30.0f)) // Tartek
        {
            if (Creature *cr = pGo->SummonCreature(28105, 6708.7f, 5115.45f, -18.3f, 0.7f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
            {
                cr->MonsterYell("My treasure! You no steal from Tartek, dumb big-tongue traitor thing. Tartek and nasty dragon going to kill you! You so dumb.", LANG_UNIVERSAL, 0);
                cr->AI()->AttackStart(pPlayer);
            }
        }
        return false;
    }
};

class go_witherbark_totem_bundle : public GameObjectScript
{
    public:
        go_witherbark_totem_bundle() : GameObjectScript("go_witherbark_totem_bundle") { }

        struct go_witherbark_totem_bundleAI : public GameObjectAI
        {
            go_witherbark_totem_bundleAI(GameObject* gameObject) : GameObjectAI(gameObject)
            {
                _timer = 1;
            }

            void UpdateAI(uint32 diff)
            {
                if (_timer)
                {
                    _timer += diff;
                    if (_timer > 5000)
                    {
                        go->CastSpell(NULL, 9056);
                        go->DestroyForNearbyPlayers();
                        _timer = 0;
                    }
                }
            }

            uint32 _timer;
        };

        GameObjectAI* GetAI(GameObject* go) const
        {
            return new go_witherbark_totem_bundleAI(go);
        }
};

class go_huge_seaforium_bombs : public GameObjectScript
{
public:
	go_huge_seaforium_bombs() : GameObjectScript("go_huge_seaforium_bombs") { }

	struct go_huge_seaforium_bombsAI : public GameObjectAI
	{
		go_huge_seaforium_bombsAI(GameObject* gameObject) : GameObjectAI(gameObject)
		{
			_timer = 1;
			isTimed = false;
		}

		bool GossipHello(Player* /*player*/, bool reportUse)
		{
			go->SetVisible(false);
			isTimed = true;
			return false;
		}

		void UpdateAI(uint32 diff)
		{
			if (_timer && isTimed)
			{
				_timer += diff;
				if (_timer > 10000)
				{
					go->SetVisible(true);
					isTimed = false;
					_timer = 1;
				}
			}
		}

		uint32 _timer;
		bool isTimed;
	};

	GameObjectAI* GetAI(GameObject* go) const
	{
		return new go_huge_seaforium_bombsAI(go);
	}

};

class go_arena_ready_marker : public GameObjectScript
{
public:
    go_arena_ready_marker() : GameObjectScript("go_arena_ready_marker") { }

    bool OnGossipHello(Player* player, GameObject *go)
    {
        if (Battleground* bg = player->GetBattleground())
            bg->ReadyMarkerClicked(player);

        return false;
    }
};

/*######
## go_ethereum_prison
######*/

enum EthereumPrison
{
    SPELL_REP_LC        = 39456,
    SPELL_REP_SHAT      = 39457,
    SPELL_REP_CE        = 39460,
    SPELL_REP_CON       = 39474,
    SPELL_REP_KT        = 39475,
    SPELL_REP_SPOR      = 39476
};

const uint32 NpcPrisonEntry[] =
{
    22810, 22811, 22812, 22813, 22814, 22815,               //good guys
    20783, 20784, 20785, 20786, 20788, 20789, 20790         //bad guys
};

class go_ethereum_prison : public GameObjectScript
{
public:
    go_ethereum_prison() : GameObjectScript("go_ethereum_prison") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        go->SetRespawnTime(60);
        go->SetLootState(GO_JUST_DEACTIVATED);

        int Random = rand() % (sizeof(NpcPrisonEntry) / sizeof(uint32));

        if (Creature* creature = player->SummonCreature(NpcPrisonEntry[Random], go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetAngle(player),
            TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
        {
            if (!creature->IsHostileTo(player))
            {
                uint32 Spell = 0;

                switch (creature->GetEntry())
                {
                    case 22811: Spell = SPELL_REP_LC; break;
                    case 22812: Spell = SPELL_REP_SHAT; break;
                    case 22810: Spell = SPELL_REP_CE; break;
                    case 22813: Spell = SPELL_REP_CON; break;
                    case 22815: Spell = SPELL_REP_KT; break;
                    case 22814: Spell = SPELL_REP_SPOR; break;
                }

                if (Spell)
                    creature->CastSpell(player, Spell, false);
            }
        }

        return false;
    }
};

/*######
## go_stasis_chamber_bashir
######*/

enum bashir
{
    NPC_BASHIR    = 22920
};
class go_stasis_chamber_bashir : public GameObjectScript
{
public:
    go_stasis_chamber_bashir() : GameObjectScript("go_stasis_chamber_bashir") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        go->SetRespawnTime(60);
        go->SetLootState(GO_JUST_DEACTIVATED);

        player->SummonCreature(NPC_BASHIR, go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetAngle(player), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

        return false;
    }
};

/*######
## go_ethereum_stasis
######*/

const uint32 NpcStasisEntry[] =
{
    22825, 20888, 22827, 22826, 22828
};

class go_ethereum_stasis : public GameObjectScript
{
public:
    go_ethereum_stasis() : GameObjectScript("go_ethereum_stasis") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        int Random = rand() % (sizeof(NpcStasisEntry) / sizeof(uint32));

        player->SummonCreature(NpcStasisEntry[Random], go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetAngle(player),
            TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

        return false;
    }
};

/*######
## go_resonite_cask
######*/

enum ResoniteCask
{
    NPC_GOGGEROC    = 11920
};

class go_resonite_cask : public GameObjectScript
{
public:
    go_resonite_cask() : GameObjectScript("go_resonite_cask") { }

    bool OnGossipHello(Player* /*player*/, GameObject* go)
    {
         // xinef: prevent spawning hundreds of them
        if (go->GetGoType() == GAMEOBJECT_TYPE_GOOBER && !go->FindNearestCreature(NPC_GOGGEROC, 20.0f))
            go->SummonCreature(NPC_GOGGEROC, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);

        return false;
    }
};

/*######
## Quest 11560: Oh Noes, the Tadpoles!
## go_tadpole_cage
######*/

enum Tadpoles
{
    QUEST_OH_NOES_THE_TADPOLES                    = 11560,
    NPC_WINTERFIN_TADPOLE                         = 25201
};

class go_tadpole_cage : public GameObjectScript
{
public:
    go_tadpole_cage() : GameObjectScript("go_tadpole_cage") { }

    struct go_tadpole_cageAI : public GameObjectAI
    {
        go_tadpole_cageAI(GameObject* gameObject) : GameObjectAI(gameObject)
        {
            requireSummon = 2;
        }

        uint8 requireSummon;

        void SummonTadpoles()
        {
            requireSummon = 0;
            int8 count = urand(1, 3);
            for (int8 i = 0; i < count; ++i)
                go->SummonCreature(NPC_WINTERFIN_TADPOLE, go->GetPositionX()+cos(2*M_PI*i/3.0f)*0.60f, go->GetPositionY()+sin(2*M_PI*i/3.0f)*0.60f, go->GetPositionZ()+0.5f, go->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
        }

        void OnStateChanged(uint32 state, Unit* unit)
        {
            if (requireSummon == 1 && state == GO_READY)
                requireSummon = 2;
        }

        void UpdateAI(uint32 diff)
        {
            if (go->isSpawned() && requireSummon == 2)
                SummonTadpoles();
        }

        bool GossipHello(Player* player, bool reportUse)
        {
            if (requireSummon)
                return false;

            requireSummon = 1;
            if (player->GetQuestStatus(QUEST_OH_NOES_THE_TADPOLES) == QUEST_STATUS_INCOMPLETE)
            {
                std::list<Creature*> cList;
                GetCreatureListWithEntryInGrid(cList, go, NPC_WINTERFIN_TADPOLE, 5.0f);
                for (std::list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); ++itr)
                {
                    player->KilledMonsterCredit(NPC_WINTERFIN_TADPOLE, 0);
                    (*itr)->DespawnOrUnsummon(urand(45000, 60000));
                    (*itr)->GetMotionMaster()->MoveFollow(player, 1.0f, frand(0.0f, 2*M_PI), MOTION_SLOT_CONTROLLED);
                }
            }
            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return new go_tadpole_cageAI(go);
    }
};



// Theirs
/*######
## go_cat_figurine
######*/

enum CatFigurine
{
    SPELL_SUMMON_GHOST_SABER    = 5968,
};

class go_cat_figurine : public GameObjectScript
{
public:
    go_cat_figurine() : GameObjectScript("go_cat_figurine") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/)
    {
        player->CastSpell(player, SPELL_SUMMON_GHOST_SABER, true);
        return false;
    }
};

/*######
## go_gilded_brazier (Paladin First Trail quest (9678))
######*/

enum GildedBrazier
{
    NPC_STILLBLADE  = 17716,
};

class go_gilded_brazier : public GameObjectScript
{
public:
    go_gilded_brazier() : GameObjectScript("go_gilded_brazier") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
        {
            if (player->GetQuestStatus(9678) == QUEST_STATUS_INCOMPLETE)
            {
                if (Creature* Stillblade = player->SummonCreature(NPC_STILLBLADE, 8106.11f, -7542.06f, 151.775f, 3.02598f, TEMPSUMMON_DEAD_DESPAWN, 60000))
                    Stillblade->AI()->AttackStart(player);
            }
        }
        return true;
    }
};

/*######
## go_tablet_of_madness
######*/

class go_tablet_of_madness : public GameObjectScript
{
public:
    go_tablet_of_madness() : GameObjectScript("go_tablet_of_madness") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/)
    {
        if (player->HasSkill(SKILL_ALCHEMY) && player->GetSkillValue(SKILL_ALCHEMY) >= 300 && !player->HasSpell(24266))
            player->CastSpell(player, 24267, false);

        return true;
    }
};

/*######
## go_tablet_of_the_seven
######*/

class go_tablet_of_the_seven : public GameObjectScript
{
public:
    go_tablet_of_the_seven() : GameObjectScript("go_tablet_of_the_seven") { }

    //TODO: use gossip option ("Transcript the Tablet") instead, if Trinity adds support.
    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (go->GetGoType() != GAMEOBJECT_TYPE_QUESTGIVER)
            return true;

        if (player->GetQuestStatus(4296) == QUEST_STATUS_INCOMPLETE)
            player->CastSpell(player, 15065, false);

        return true;
    }
};

/*#####
## go_jump_a_tron
######*/

class go_jump_a_tron : public GameObjectScript
{
public:
    go_jump_a_tron() : GameObjectScript("go_jump_a_tron") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/)
    {
        if (player->GetQuestStatus(10111) == QUEST_STATUS_INCOMPLETE)
            player->CastSpell(player, 33382, true);

        return true;
    }
};

/*######
## go_sacred_fire_of_life
######*/

enum SacredFireOfLife
{
    NPC_ARIKARA     = 10882
};

class go_sacred_fire_of_life : public GameObjectScript
{
public:
    go_sacred_fire_of_life() : GameObjectScript("go_sacred_fire_of_life") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
            player->SummonCreature(NPC_ARIKARA, -5008.338f, -2118.894f, 83.657f, 0.874f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

        return true;
    }
};

/*######
## go_shrine_of_the_birds
######*/

enum ShrineOfTheBirds
{
    NPC_HAWK_GUARD      = 22992,
    NPC_EAGLE_GUARD     = 22993,
    NPC_FALCON_GUARD    = 22994,
    GO_SHRINE_HAWK      = 185551,
    GO_SHRINE_EAGLE     = 185547,
    GO_SHRINE_FALCON    = 185553,

    EAGLE_GUARD_POSITION     = 0,
    HAWK_GUARD_POSITION      = 1,
    FALCON_GUARD_POSITION    = 2
};

Position const guardPosition[3] =
{
    { -2623.18f, 4573.95f, 138.77f, 1.78f }, // Eagle Guarsd
    { -4363.11f, 4625.4f, -39.01f, 0.46f }, // Hawk Guard
    { -3165.45f, 3808.17f, 59.98f, 1.90f } // Falcon Guard
};

class go_shrine_of_the_birds : public GameObjectScript
{
public:
    go_shrine_of_the_birds() : GameObjectScript("go_shrine_of_the_birds") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        uint32 BirdEntry = 0;
        uint8 PositionIndex = 0;

        switch (go->GetEntry())
        {
            case GO_SHRINE_HAWK:
                BirdEntry = NPC_HAWK_GUARD;
                PositionIndex = HAWK_GUARD_POSITION;
                break;
            case GO_SHRINE_EAGLE:
                BirdEntry = NPC_EAGLE_GUARD;
                PositionIndex = EAGLE_GUARD_POSITION;
                break;
            case GO_SHRINE_FALCON:
                BirdEntry = NPC_FALCON_GUARD;
                PositionIndex = FALCON_GUARD_POSITION;
                break;
        }

        if (BirdEntry)
            player->SummonCreature(BirdEntry, guardPosition[PositionIndex], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);

        return false;
    }
};

/*######
## go_southfury_moonstone
######*/

enum Southfury
{
    NPC_RIZZLE                  = 23002,
    SPELL_BLACKJACK             = 39865, //stuns player
    SPELL_SUMMON_RIZZLE         = 39866
};

class go_southfury_moonstone : public GameObjectScript
{
public:
    go_southfury_moonstone() : GameObjectScript("go_southfury_moonstone") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/)
    {
        //implicitTarget=48 not implemented as of writing this code, and manual summon may be just ok for our purpose
        //player->CastSpell(player, SPELL_SUMMON_RIZZLE, false);

        if (Creature* creature = player->SummonCreature(NPC_RIZZLE, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0))
            creature->CastSpell(player, SPELL_BLACKJACK, false);

        return false;
    }
};

/*######
## go_tele_to_dalaran_crystal
######*/

enum DalaranCrystal
{
    QUEST_LEARN_LEAVE_RETURN    = 12790,
    QUEST_TELE_CRYSTAL_FLAG     = 12845
};

#define GO_TELE_TO_DALARAN_CRYSTAL_FAILED   "This teleport crystal cannot be used until the teleport crystal in Dalaran has been used at least once."

class go_tele_to_dalaran_crystal : public GameObjectScript
{
public:
    go_tele_to_dalaran_crystal() : GameObjectScript("go_tele_to_dalaran_crystal") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/)
    {
        if (player->GetQuestRewardStatus(QUEST_TELE_CRYSTAL_FLAG))
            return false;

        player->GetSession()->SendNotification(GO_TELE_TO_DALARAN_CRYSTAL_FAILED);

        return true;
    }
};

/*######
## go_tele_to_violet_stand
######*/

class go_tele_to_violet_stand : public GameObjectScript
{
public:
    go_tele_to_violet_stand() : GameObjectScript("go_tele_to_violet_stand") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/)
    {
        if (player->GetQuestRewardStatus(QUEST_LEARN_LEAVE_RETURN) || player->GetQuestStatus(QUEST_LEARN_LEAVE_RETURN) == QUEST_STATUS_INCOMPLETE)
            return false;

        return true;
    }
};

/*######
## go_fel_crystalforge
######*/

#define GOSSIP_FEL_CRYSTALFORGE_TEXT 31000
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_TEXT_RETURN 31001
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_1 "Purchase 1 Unstable Flask of the Beast for the cost of 10 Apexis Shards"
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_5 "Purchase 5 Unstable Flask of the Beast for the cost of 50 Apexis Shards"
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_RETURN "Use the fel crystalforge to make another purchase."

enum FelCrystalforge
{
    SPELL_CREATE_1_FLASK_OF_BEAST   = 40964,
    SPELL_CREATE_5_FLASK_OF_BEAST   = 40965,
};

class go_fel_crystalforge : public GameObjectScript
{
public:
    go_fel_crystalforge() : GameObjectScript("go_fel_crystalforge") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER) /* != GAMEOBJECT_TYPE_QUESTGIVER) */
            player->PrepareQuestMenu(go->GetGUID()); /* return true*/

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(GOSSIP_FEL_CRYSTALFORGE_TEXT, go->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF:
                player->CastSpell(player, SPELL_CREATE_1_FLASK_OF_BEAST, false);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(GOSSIP_FEL_CRYSTALFORGE_ITEM_TEXT_RETURN, go->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->CastSpell(player, SPELL_CREATE_5_FLASK_OF_BEAST, false);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(GOSSIP_FEL_CRYSTALFORGE_ITEM_TEXT_RETURN, go->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(GOSSIP_FEL_CRYSTALFORGE_TEXT, go->GetGUID());
                break;
        }
        return true;
    }
};

/*######
## go_bashir_crystalforge
######*/

#define GOSSIP_BASHIR_CRYSTALFORGE_TEXT 31100
#define GOSSIP_BASHIR_CRYSTALFORGE_ITEM_TEXT_RETURN 31101
#define GOSSIP_BASHIR_CRYSTALFORGE_ITEM_1 "Purchase 1 Unstable Flask of the Sorcerer for the cost of 10 Apexis Shards"
#define GOSSIP_BASHIR_CRYSTALFORGE_ITEM_5 "Purchase 5 Unstable Flask of the Sorcerer for the cost of 50 Apexis Shards"
#define GOSSIP_BASHIR_CRYSTALFORGE_ITEM_RETURN "Use the bashir crystalforge to make another purchase."

enum BashirCrystalforge
{
    SPELL_CREATE_1_FLASK_OF_SORCERER   = 40968,
    SPELL_CREATE_5_FLASK_OF_SORCERER   = 40970,
};

class go_bashir_crystalforge : public GameObjectScript
{
public:
    go_bashir_crystalforge() : GameObjectScript("go_bashir_crystalforge") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER) /* != GAMEOBJECT_TYPE_QUESTGIVER) */
            player->PrepareQuestMenu(go->GetGUID()); /* return true*/

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(GOSSIP_BASHIR_CRYSTALFORGE_TEXT, go->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF:
                player->CastSpell(player, SPELL_CREATE_1_FLASK_OF_SORCERER, false);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(GOSSIP_BASHIR_CRYSTALFORGE_ITEM_TEXT_RETURN, go->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->CastSpell(player, SPELL_CREATE_5_FLASK_OF_SORCERER, false);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(GOSSIP_BASHIR_CRYSTALFORGE_ITEM_TEXT_RETURN, go->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(GOSSIP_BASHIR_CRYSTALFORGE_TEXT, go->GetGUID());
                break;
        }
        return true;
    }
};

/*######
## go_scourge_cage
######*/

enum ScourgeCage
{
    NPC_SCOURGE_PRISONER = 25610
};

class go_scourge_cage : public GameObjectScript
{
public:
    go_scourge_cage() : GameObjectScript("go_scourge_cage") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        go->UseDoorOrButton();
        if (Creature* pNearestPrisoner = go->FindNearestCreature(NPC_SCOURGE_PRISONER, 5.0f, true))
        {
            player->KilledMonsterCredit(NPC_SCOURGE_PRISONER, pNearestPrisoner->GetGUID());
            pNearestPrisoner->DisappearAndDie();
        }

        return true;
    }
};

/*######
## go_arcane_prison
######*/

enum ArcanePrison
{
    QUEST_PRISON_BREAK                  = 11587,
    SPELL_ARCANE_PRISONER_KILL_CREDIT   = 45456
};

class go_arcane_prison : public GameObjectScript
{
public:
    go_arcane_prison() : GameObjectScript("go_arcane_prison") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        // xinef: prevent spawning hundreds of them
        if (player->GetQuestStatus(QUEST_PRISON_BREAK) == QUEST_STATUS_INCOMPLETE && !go->FindNearestCreature(25318, 20.0f))
        {
            go->SummonCreature(25318, 3485.089844f, 6115.7422188f, 70.966812f, 0, TEMPSUMMON_TIMED_DESPAWN, 60000);
            player->CastSpell(player, SPELL_ARCANE_PRISONER_KILL_CREDIT, true);
            return true;
        }
        return false;
    }
};

/*######
## go_jotunheim_cage
######*/

enum JotunheimCage
{
    NPC_EBON_BLADE_PRISONER_HUMAN   = 30186,
    NPC_EBON_BLADE_PRISONER_NE      = 30194,
    NPC_EBON_BLADE_PRISONER_TROLL   = 30196,
    NPC_EBON_BLADE_PRISONER_ORC     = 30195,

    SPELL_SUMMON_BLADE_KNIGHT_H     = 56207,
    SPELL_SUMMON_BLADE_KNIGHT_NE    = 56209,
    SPELL_SUMMON_BLADE_KNIGHT_ORC   = 56212,
    SPELL_SUMMON_BLADE_KNIGHT_TROLL = 56214
};

class go_jotunheim_cage : public GameObjectScript
{
public:
    go_jotunheim_cage() : GameObjectScript("go_jotunheim_cage") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        go->UseDoorOrButton();
        Creature* pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_HUMAN, 5.0f, true);
        if (!pPrisoner)
        {
            pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_TROLL, 5.0f, true);
            if (!pPrisoner)
            {
                pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_ORC, 5.0f, true);
                if (!pPrisoner)
                    pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_NE, 5.0f, true);
            }
        }
        if (!pPrisoner || !pPrisoner->IsAlive())
            return false;

        pPrisoner->DespawnOrUnsummon();
        player->KilledMonsterCredit(NPC_EBON_BLADE_PRISONER_HUMAN, 0);
        switch (pPrisoner->GetEntry())
        {
            case NPC_EBON_BLADE_PRISONER_HUMAN:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_H, true);
                break;
            case NPC_EBON_BLADE_PRISONER_NE:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_NE, true);
                break;
            case NPC_EBON_BLADE_PRISONER_TROLL:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_TROLL, true);
                break;
            case NPC_EBON_BLADE_PRISONER_ORC:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_ORC, true);
                break;
        }
        return true;
    }
};

enum TableTheka
{
    GOSSIP_TABLE_THEKA = 1653,

    QUEST_SPIDER_GOLD = 2936
};

class go_table_theka : public GameObjectScript
{
public:
    go_table_theka() : GameObjectScript("go_table_theka") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_SPIDER_GOLD) == QUEST_STATUS_INCOMPLETE)
            player->AreaExploredOrEventHappens(QUEST_SPIDER_GOLD);

        player->SEND_GOSSIP_MENU(GOSSIP_TABLE_THEKA, go->GetGUID());

        return true;
    }
};

/*######
## go_inconspicuous_landmark
######*/

enum InconspicuousLandmark
{
    SPELL_SUMMON_PIRATES_TREASURE_AND_TRIGGER_MOB    = 11462,
    ITEM_CUERGOS_KEY                                 = 9275,
};

class go_inconspicuous_landmark : public GameObjectScript
{
    public:
        go_inconspicuous_landmark() : GameObjectScript("go_inconspicuous_landmark")
        {
            _lastUsedTime = time(nullptr);
        }

        bool OnGossipHello(Player* player, GameObject* /*go*/)
        {
            if (player->HasItemCount(ITEM_CUERGOS_KEY))
                return true;

            if (_lastUsedTime > time(nullptr))
                return true;

            _lastUsedTime = time(nullptr) + MINUTE;
            player->CastSpell(player, SPELL_SUMMON_PIRATES_TREASURE_AND_TRIGGER_MOB, true);
            return true;
        }

    private:
        uint32 _lastUsedTime;
};

/*######
## Quest 11255: Prisoners of Wyrmskull
## go_dragonflayer_cage
######*/

enum PrisonersOfWyrmskull
{
    QUEST_PRISONERS_OF_WYRMSKULL                  = 11255,
    NPC_PRISONER_PRIEST                           = 24086,
    NPC_PRISONER_MAGE                             = 24088,
    NPC_PRISONER_WARRIOR                          = 24089,
    NPC_PRISONER_PALADIN                          = 24090
};

class go_dragonflayer_cage : public GameObjectScript
{
public:
    go_dragonflayer_cage() : GameObjectScript("go_dragonflayer_cage") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        go->UseDoorOrButton();
        if (player->GetQuestStatus(QUEST_PRISONERS_OF_WYRMSKULL) != QUEST_STATUS_INCOMPLETE)
            return true;

        Creature* pPrisoner = go->FindNearestCreature(NPC_PRISONER_PRIEST, 2.0f);
        if (!pPrisoner)
        {
            pPrisoner = go->FindNearestCreature(NPC_PRISONER_MAGE, 2.0f);
            if (!pPrisoner)
            {
                pPrisoner = go->FindNearestCreature(NPC_PRISONER_WARRIOR, 2.0f);
                if (!pPrisoner)
                    pPrisoner = go->FindNearestCreature(NPC_PRISONER_PALADIN, 2.0f);
            }
        }

        if (!pPrisoner || !pPrisoner->IsAlive())
            return true;

        Quest const* qInfo = sObjectMgr->GetQuestTemplate(QUEST_PRISONERS_OF_WYRMSKULL);
        if (qInfo)
        {
            /// @todo prisoner should help player for a short period of time
            player->KilledMonsterCredit(qInfo->RequiredNpcOrGo[0], 0);
            pPrisoner->DisappearAndDie();
        }
        return true;
    }
};

/*######
## go_amberpine_outhouse
######*/

#define GOSSIP_USE_OUTHOUSE "Use the outhouse."
#define GO_ANDERHOLS_SLIDER_CIDER_NOT_FOUND "Quest item Anderhol's Slider Cider not found."

enum AmberpineOuthouse
{
    ITEM_ANDERHOLS_SLIDER_CIDER     = 37247,
    NPC_OUTHOUSE_BUNNY              = 27326,
    QUEST_DOING_YOUR_DUTY           = 12227,
    SPELL_INDISPOSED                = 48323,
    SPELL_INDISPOSED_III            = 48341,
    SPELL_CREATE_AMBERSEEDS         = 48330,
    GOSSIP_OUTHOUSE_INUSE           = 12775,
    GOSSIP_OUTHOUSE_VACANT          = 12779
};

class go_amberpine_outhouse : public GameObjectScript
{
public:
    go_amberpine_outhouse() : GameObjectScript("go_amberpine_outhouse") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        QuestStatus status = player->GetQuestStatus(QUEST_DOING_YOUR_DUTY);
        if (status == QUEST_STATUS_INCOMPLETE || status == QUEST_STATUS_COMPLETE || status == QUEST_STATUS_REWARDED)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_USE_OUTHOUSE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(GOSSIP_OUTHOUSE_VACANT, go->GetGUID());
        }
        else
            player->SEND_GOSSIP_MENU(GOSSIP_OUTHOUSE_INUSE, go->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF +1)
        {
            player->CLOSE_GOSSIP_MENU();
            Creature* target = GetClosestCreatureWithEntry(player, NPC_OUTHOUSE_BUNNY, 3.0f);
            if (target)
            {
                target->AI()->SetData(1, player->getGender());
                go->CastSpell(target, SPELL_INDISPOSED_III);
            }
            go->CastSpell(player, SPELL_INDISPOSED);
            if (player->HasItemCount(ITEM_ANDERHOLS_SLIDER_CIDER))
                player->CastSpell(player, SPELL_CREATE_AMBERSEEDS, true);
            return true;
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification(GO_ANDERHOLS_SLIDER_CIDER_NOT_FOUND);
            return false;
        }
    }
};

/*######
## Quest 1126: Hive in the Tower
## go_hive_pod
######*/

enum Hives
{
    QUEST_HIVE_IN_THE_TOWER                       = 9544,
    NPC_HIVE_AMBUSHER                             = 13301
};

class go_hive_pod : public GameObjectScript
{
public:
    go_hive_pod() : GameObjectScript("go_hive_pod") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        player->SendLoot(go->GetGUID(), LOOT_CORPSE);

        // xinef: prevent spawning hundreds of them
        if (go->FindNearestCreature(NPC_HIVE_AMBUSHER, 20.0f))
            return true;

        go->SummonCreature(NPC_HIVE_AMBUSHER, go->GetPositionX()+1, go->GetPositionY(), go->GetPositionZ(), go->GetAngle(player), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
        go->SummonCreature(NPC_HIVE_AMBUSHER, go->GetPositionX(), go->GetPositionY()+1, go->GetPositionZ(), go->GetAngle(player), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
        return true;
    }
};

class go_massive_seaforium_charge : public GameObjectScript
{
    public:
        go_massive_seaforium_charge() : GameObjectScript("go_massive_seaforium_charge") { }

        bool OnGossipHello(Player* /*player*/, GameObject* go)
        {
            go->SetLootState(GO_JUST_DEACTIVATED);
            return true;
        }
};

/*########
#### go_veil_skith_cage
#####*/

enum MissingFriends
{
   QUEST_MISSING_FRIENDS    = 10852,
   NPC_CAPTIVE_CHILD        = 22314,
   SAY_FREE_0               = 0,
};

class go_veil_skith_cage : public GameObjectScript
{
    public:
       go_veil_skith_cage() : GameObjectScript("go_veil_skith_cage") { }

       bool OnGossipHello(Player* player, GameObject* go)
       {
           go->UseDoorOrButton();
           if (player->GetQuestStatus(QUEST_MISSING_FRIENDS) == QUEST_STATUS_INCOMPLETE)
           {
               std::list<Creature*> childrenList;
               GetCreatureListWithEntryInGrid(childrenList, go, NPC_CAPTIVE_CHILD, INTERACTION_DISTANCE);
               for (std::list<Creature*>::const_iterator itr = childrenList.begin(); itr != childrenList.end(); ++itr)
               {
                   player->KilledMonsterCredit(NPC_CAPTIVE_CHILD, (*itr)->GetGUID());
                   (*itr)->DespawnOrUnsummon(5000);
                   (*itr)->GetMotionMaster()->MovePoint(1, go->GetPositionX()+5, go->GetPositionY(), go->GetPositionZ());
                   (*itr)->AI()->Talk(SAY_FREE_0);
                   (*itr)->GetMotionMaster()->Clear();
               }
           }
           return false;
       }
};

/*######
## go_lard_picnic_basket
######*/

enum LardLostHisLunch
{
    QUEST_LARD_LOST_HIS_LUNCH     = 7840,
    CREATURE_VILEBRANCH_KIDNAPPER = 14748
};

static Position KidnapperPosition[3] =
{
    { 421.5f, -4811.76f, 12.03f, 4.35f },
    { 414.5f, -4812.67f, 12.54f, 4.48f },
    { 417.0f, -4817.01f, 12.06f, 4.58f }
};

class go_lard_picnic_basket : public GameObjectScript
{
public:
    go_lard_picnic_basket() : GameObjectScript("go_lard_picnic_basket") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (!player || !go)
            return true;

        // sitdev: prevent spawning hundreds of them
        if (player->GetQuestStatus(QUEST_LARD_LOST_HIS_LUNCH) == QUEST_STATUS_INCOMPLETE && go->GetGoType() == GAMEOBJECT_TYPE_GOOBER && !go->FindNearestCreature(CREATURE_VILEBRANCH_KIDNAPPER, 20.0f))
            for (uint8 i = 0; i < 3; ++i)
                go->SummonCreature(CREATURE_VILEBRANCH_KIDNAPPER, KidnapperPosition[i], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 600000);

        return false;
    }
};

/*######
## go_war_horn_of_jotunheim
######*/

enum BansheeRevenge
{
    QUEST_BANSHEE_REVENGE         = 13142,
    CREATURE_OVERTHANE_BALARGARDE = 31016
};

static Position BalargardePosition[] =
{
    { 7088.22f, 4380.14f, 872.267f, 4.36759f }
};

class go_war_horn_of_jotunheim : public GameObjectScript
{
public:
    go_war_horn_of_jotunheim() : GameObjectScript("go_war_horn_of_jotunheim") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (!player || !go)
            return true;

        // sitdev: prevent spawning hundreds of them
        if (player->GetQuestStatus(QUEST_BANSHEE_REVENGE) == QUEST_STATUS_INCOMPLETE && go->GetGoType() == GAMEOBJECT_TYPE_GOOBER && !go->FindNearestCreature(CREATURE_OVERTHANE_BALARGARDE, 120.0f))
            go->SummonCreature(CREATURE_OVERTHANE_BALARGARDE, BalargardePosition[0], TEMPSUMMON_CORPSE_DESPAWN, 0);

        return false;
    }
};

/*######
## go_dirt_mound
######*/

enum DirtMound
{
	NPC_HEAD = 160839
};

class go_dirt_mound : public GameObjectScript
{
public:
	go_dirt_mound() : GameObjectScript("go_dirt_mound") { }

	bool OnGossipHello(Player* /*player*/, GameObject* go)
	{
        if (!go)
            return true;

		if (!go->FindNearestGameObject(NPC_HEAD, 5.0f))
			go->SummonGameObject(NPC_HEAD, -7944.65f, -2639.17f, 218.81f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10000, false);

		return false;
	}
};

void AddSC_go_scripts()
{
    // Ours
    new go_noblegarden_colored_egg();
    new go_seer_of_zebhalak();
    new go_mistwhisper_treasure();
    new go_witherbark_totem_bundle();
    new go_arena_ready_marker();
    new go_ethereum_prison();
    new go_ethereum_stasis();
    new go_resonite_cask();
    new go_tadpole_cage();
    new go_lard_picnic_basket();
    new go_war_horn_of_jotunheim();
    new go_dirt_mound();
	new go_huge_seaforium_bombs();

    // Theirs
    new go_cat_figurine();
    new go_gilded_brazier();
    new go_shrine_of_the_birds();
    new go_southfury_moonstone();
    new go_tablet_of_madness();
    new go_tablet_of_the_seven();
    new go_jump_a_tron();
    new go_sacred_fire_of_life();
    new go_tele_to_dalaran_crystal();
    new go_tele_to_violet_stand();
    new go_fel_crystalforge();
    new go_bashir_crystalforge();
    new go_scourge_cage();
    new go_arcane_prison();
    new go_jotunheim_cage();
    new go_table_theka();
    new go_inconspicuous_landmark();
    new go_dragonflayer_cage();
    new go_amberpine_outhouse();
    new go_hive_pod();
    new go_massive_seaforium_charge();
    new go_veil_skith_cage();
    new go_stasis_chamber_bashir();
}
