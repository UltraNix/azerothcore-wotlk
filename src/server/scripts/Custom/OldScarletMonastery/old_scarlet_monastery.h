/*
* Copyright (C) 2015-2015 Theatre of Dreams
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

#ifndef OLD_SCARLET_MONASTRY_H_
#define OLD_SCARLET_MONASTRY_H_

uint32 const EncounterCount = 6;

enum DataTypes
{
    DATA_MAZIN_SOULSTEALER = 0,
    DATA_JAVIER_VOIDBRINGER = 1,
    DATA_REAST = 2,
    DATA_MADANTUL_RADA = 3,
    DATA_DESSEMBRAE = 4,
    DATA_DEVALETH   = 5,

    DATA_DEVALETH_DEATH = 6
};

enum OLDSMCreatureIds
{
    // Javier
    NPC_JAVIER_VOIDBRINGER = 400000,
    NPC_VOID = 400001,
    NPC_JAVIER_CLONE = 400002,
    NPC_JAVIER_DEFENDER = 400003,
    NPC_JAVIER_BUFFER = 400004,
    NPC_JAVIER_HEALER = 400005,
    NPC_JAVIER_SOLDIER = 400006,
    //NPC_TELEPORTER            = 400007,

    // Devaleth
    NPC_DEVALETH = 400008,
    NPC_RISEN_EAGLE = 400009,

    // Dessembrae
    NPC_DESSEMBRAE = 400010,
    NPC_PHYSICAL_BALL = 400011,
    NPC_FROST_BALL = 400012,
    NPC_FIRE_BALL = 400013,
    NPC_ARCANE_BALL = 400014,
    NPC_ARCANE_CHANNELER = 400015,
    NPC_SHADOW_OF_THE_PAST = 400016,
    NPC_CHANNELER_TARGET = 400017,
    NPC_PROTECTOR = 400018,
    NPC_LITTLE_PHEONIX = 400019,

    // Mazin
    NPC_DEATH_ORB = 400020,
    NPC_MAZIN_SOULSTEALER = 400022,
    NPC_SOUL_THRALL = 400023,
    NPC_SOUL_SYLVANAS = 400024,
    NPC_SOUL_KELTHUZAD = 400025,
    NPC_AIR_ELEMENTAL_MAZIN = 400026,
    NPC_EARTH_ELEMENTAL_MAZIN = 400027,
    NPC_FIRE_ELEMENTAL_MAZIN = 400028,
    NPC_ARROW_TRIGGER = 400029,
    NPC_VOID_ZONE = 400030, // Kel\'Thuzad invis agent
    NPC_RAGING_SKELETON = 400031,
    NPC_PURPLE_LIGHT_ORB = 400032,
    // Dessembrae dodatkowe
    // zeby byla kolejnosc;p
    NPC_FLAME_TRIGGER = 400033,
    NPC_ARCANE_ORB = 400034,
    NPC_FORCE_FIELD_DUMMY = 400035,
    NPC_PROTECTOR_BOMBS = 400036,

    // Reast
    NPC_REAST = 400040,
    NPC_REAST2 = 400041,
    NPC_POWER_ORB = 400042,

    // Madantul
    NPC_MADANTUL_RADA = 400043,
    NPC_RISEN_OVERLORD = 400044,
    NPC_STORM_CALL_TRIGGER = 400045,
    NPC_KAMIKAZE = 400047,
    NPC_ARROW_MARKER = 400048,

    // trash
    NPC_DARK_RISEN_STALKER = 400050,
    NPC_DARK_RISEN_COMMANDER = 400051,
    NPC_DARK_RISEN_ZEALOT = 400052,
    NPC_DARK_RISEN_ADHERENT = 400053,
    NPC_RISEN_CONSTRUCT = 400054,

    // gate keeper
    NPC_SIMON = 400049,
    NPC_ARTHUR = 400046
};

enum GameObjectsIds
{
    GO_ENTRANCE_DOORS = 500000,
    GO_GARDEN_ENTRANCE_DOORS,
    GO_GARDEN_EXIT_DOORS,
    GO_GARDEN_SECRET_DOORS,
    GO_HALL_OF_CHAMPIONS_ENTRANCE_1,
    GO_HALL_OF_CHAMPIONS_ENTRANCE_2,
    GO_HALL_OF_CHAMPIONS_EXIT_DOORS,
    GO_BACK_HALL_DOORS,
    GO_BACK_ROOM_DOORS,
    GO_MAIN_HALL_DOORS,
    GO_END_ROOM_DOORS_1,
    GO_END_ROOM_DOORS_2,
    GO_SECRET_DOORS,
    GO_COURTYARD_DOORS,
    GO_CATHEDRAL_DOORS,
    GO_OLD_SCARLET_MONASTERY_ENTRANCE,
    GO_ENERGY_WELL,
    GO_ORB_GATE = 182026,
};

enum Phases
{
    PHASE_NONE = 0,
    PHASE_INTRO = 1,
    PHASE_ONE = 2,
    PHASE_TWO = 3,
    PHASE_THREE = 4,
    PHASE_FOUR = 5,
    PHASE_FIVE = 6,
    PHASE_SIX = 7,
    PHASE_TRANSITION = 8,
};

template<class AI>
CreatureAI* GetOldScarletMonasteryAI(Creature* creature)
{
    if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
        if (instance->GetInstanceScript())
            if (instance->GetScriptId() == sObjectMgr->GetScriptId("instance_old_scarlet_monastery"))
                return new AI(creature);
    return NULL;
}

template<class AI>
GameObjectAI* GetOldScarletMonasteryAI(GameObject* go)
{
    if (InstanceMap* instance = go->GetMap()->ToInstanceMap())
        if (instance->GetInstanceScript())
            if (instance->GetScriptId() == sObjectMgr->GetScriptId("instance_old_scarlet_monastery"))
                return new AI(go);

    return NULL;
}

#endif // OLD_SCARLET_MONASTRY_H_
