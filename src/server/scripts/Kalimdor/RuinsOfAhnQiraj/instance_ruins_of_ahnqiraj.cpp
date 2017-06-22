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
#include "InstanceScript.h"
#include "ruins_of_ahnqiraj.h"

ObjectData const creatureData[] =
{
    { NPC_KURINAXX , DATA_KURINNAXX },
    { NPC_RAJAXX   , DATA_RAJAXX    },
    { NPC_MOAM     , DATA_MOAM      },
    { NPC_BURU     , DATA_BURU      },
    { NPC_AYAMISS  , DATA_AYAMISS   },
    { NPC_OSSIRIAN , DATA_OSSIRIAN  },
    { 0            , 0              }// END
};

struct instance_ruins_of_ahnqiraj_InstanceMapScript : public InstanceScript
{
    instance_ruins_of_ahnqiraj_InstanceMapScript(Map* map) : InstanceScript(map)
    {
        SetBossNumber(NUM_ENCOUNTER);
        LoadObjectData(creatureData, nullptr);
        _paralyzedGUID  = 0;
    }

    bool SetBossState(uint32 bossId, EncounterState state)
    {
        if (!InstanceScript::SetBossState(bossId, state))
            return false;

        return true;
    }

    void SetData64(uint32 type, uint64 data)
    {
        if (type == DATA_PARALYZED)
            _paralyzedGUID = data;
    }

    uint64 GetData64(uint32 type) const
    {
        switch (type)
        {
            case DATA_PARALYZED:
                return _paralyzedGUID;
        }

        return 0;
    }

    std::string GetSaveData()
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << "R A" << GetBossSaveData();

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

        OUT_LOAD_INST_DATA(data);

        char dataHead1, dataHead2;

        std::istringstream loadStream(data);
        loadStream >> dataHead1 >> dataHead2;

        if (dataHead1 == 'R' && dataHead2 == 'A')
        {
            for (uint8 i = 0; i < NUM_ENCOUNTER; ++i)
            {
                uint32 tmpState;
                loadStream >> tmpState;
                if (tmpState == IN_PROGRESS || tmpState > TO_BE_DECIDED)
                    tmpState = NOT_STARTED;
                SetBossState(i, EncounterState(tmpState));
            }
        }
        else
            OUT_LOAD_INST_DATA_FAIL;

        OUT_LOAD_INST_DATA_COMPLETE;
    }

private:
    uint64 _paralyzedGUID;
};

void AddSC_instance_ruins_of_ahnqiraj()
{
    new InstanceMapScriptLoader<instance_ruins_of_ahnqiraj_InstanceMapScript>("instance_ruins_of_ahnqiraj", 509);
}
