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

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "CreatureAI.h"
#include "molten_core.h"
#include "TemporarySummon.h"

ObjectData const creatureData[] =
{
    { NPC_GARR    , BOSS_GARR     },
    { NPC_RAGNAROS, BOSS_RAGNAROS },
    { 0,            0             } // END
};

ObjectData const objectData[] =
{
    { GO_CACHE_OF_THE_FIRELORD      , DATA_CACHE_OF_THE_FIRELORD },
    { 0                             , 0 } // END
};

struct instance_molten_core_InstanceMapScript : public InstanceScript
{
    instance_molten_core_InstanceMapScript(Map* map) : InstanceScript(map)
    {
        SetBossNumber(MAX_ENCOUNTER);
        LoadObjectData(creatureData, objectData);
        _executusSchedule = NULL;
        _deadBossCount = 0;
        _ragnarosAddDeaths = 0;
        _isLoading = false;
        _summonedExecutus = false;
    }

    ~instance_molten_core_InstanceMapScript()
    {
        delete _executusSchedule;
    }

    void OnPlayerEnter(Player* /*player*/)
    {
        if (_executusSchedule)
        {
            SummonMajordomoExecutus(*_executusSchedule);
            delete _executusSchedule;
            _executusSchedule = NULL;
        }
    }

    void SetData(uint32 type, uint32 data)
    {
        if (type == DATA_RAGNAROS_ADDS)
        {
            if (data == 1)
                ++_ragnarosAddDeaths;
            else if (data == 0)
                _ragnarosAddDeaths = 0;
        }
    }

    uint32 GetData(uint32 type) const
    {
        switch (type)
        {
            case DATA_RAGNAROS_ADDS:
                return _ragnarosAddDeaths;
        }

        return 0;
    }

    bool SetBossState(uint32 bossId, EncounterState state)
    {
        if (!InstanceScript::SetBossState(bossId, state))
            return false;

        if (state == DONE && bossId < BOSS_MAJORDOMO_EXECUTUS)
            ++_deadBossCount;

        if (_isLoading)
            return true;

        if (_deadBossCount == 8)
            SummonMajordomoExecutus(false);

        if (bossId == BOSS_MAJORDOMO_EXECUTUS && state == DONE)
            DoRespawnGameObject(GetGameObject(DATA_CACHE_OF_THE_FIRELORD)->GetGUID(), 7 * DAY);

        return true;
    }

    void SummonMajordomoExecutus(bool done)
    {
        if (_summonedExecutus)
            return;

        _summonedExecutus = true;
        if (!done)
        {
            if (Creature* majordomo = instance->SummonCreature(NPC_MAJORDOMO_EXECUTUS, SummonPositions[0]))
            {
                majordomo->SummonCreature(NPC_FLAMEWAKER_HEALER, SummonPositions[1]);
                majordomo->SummonCreature(NPC_FLAMEWAKER_HEALER, SummonPositions[2]);
                majordomo->SummonCreature(NPC_FLAMEWAKER_HEALER, SummonPositions[3]);
                majordomo->SummonCreature(NPC_FLAMEWAKER_HEALER, SummonPositions[4]);
                majordomo->SummonCreature(NPC_FLAMEWAKER_ELITE, SummonPositions[5]);
                majordomo->SummonCreature(NPC_FLAMEWAKER_ELITE, SummonPositions[6]);
                majordomo->SummonCreature(NPC_FLAMEWAKER_ELITE, SummonPositions[7]);
                majordomo->SummonCreature(NPC_FLAMEWAKER_ELITE, SummonPositions[8]);
            }
        }
    }

    std::string GetSaveData()
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << "M C " << GetBossSaveData();

        OUT_SAVE_INST_DATA_COMPLETE;
        return saveStream.str();
    }

    void Load(char const* data)
    {
        if (!data)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        _isLoading = true;
        OUT_LOAD_INST_DATA(data);

        char dataHead1, dataHead2;

        std::istringstream loadStream(data);
        loadStream >> dataHead1 >> dataHead2;

        if (dataHead1 == 'M' && dataHead2 == 'C')
        {
            EncounterState states[MAX_ENCOUNTER];
            uint8 executusCounter = 0;

            // need 2 loops to check spawning executus/ragnaros
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            {
                uint32 tmpState;
                loadStream >> tmpState;
                if (tmpState == IN_PROGRESS || tmpState > TO_BE_DECIDED)
                    tmpState = NOT_STARTED;
                states[i] = EncounterState(tmpState);

                    if (tmpState == DONE && i < BOSS_MAJORDOMO_EXECUTUS)
                    ++executusCounter;
            }

            if (executusCounter >= 8 && states[BOSS_RAGNAROS] != DONE)
                _executusSchedule = new bool(states[BOSS_MAJORDOMO_EXECUTUS] == DONE);

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                SetBossState(i, states[i]);
        }
        else
            OUT_LOAD_INST_DATA_FAIL;

        OUT_LOAD_INST_DATA_COMPLETE;
        _isLoading = false;
    }

private:
    bool* _executusSchedule;
    uint8 _deadBossCount;
    uint8 _ragnarosAddDeaths;
    bool _isLoading;
    bool _summonedExecutus;
};

void AddSC_instance_molten_core()
{
    new InstanceMapScriptLoader<instance_molten_core_InstanceMapScript>("instance_molten_core", 409);
}
