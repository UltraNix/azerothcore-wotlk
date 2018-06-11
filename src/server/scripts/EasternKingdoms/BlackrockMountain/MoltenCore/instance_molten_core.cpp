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

enum InstanceMoltenCore
{
    EVENT_CHECK_ENCOUNTER_STATE  = 1
};

ObjectData const creatureData[] =
{
    { NPC_GARR              , BOSS_GARR                 },
    { NPC_RAGNAROS          , BOSS_RAGNAROS             },
    { NPC_MAJORDOMO_EXECUTUS, BOSS_MAJORDOMO_EXECUTUS   },
    { 0                     , 0                         } // END
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
        SetHeaders(DataHeader);
        SetBossNumber(MAX_ENCOUNTER);
        LoadObjectData(creatureData, objectData);
        _ragnarosEngaged = false;
    }

    void OnPlayerEnter(Player* /*player*/) override
    {
        if (instance->GetPlayersCount() == 1)
            SummonMajordomoOrRagnaros();
    }

    bool CanSummonMajordomo() const
    {
        if (GetCreature(BOSS_MAJORDOMO_EXECUTUS))
            return false;

        if (!_ragnarosEngaged && GetBossState(BOSS_MAJORDOMO_EXECUTUS) == DONE)
            return true;

        for (uint32 bossId = 0; bossId != BOSS_MAJORDOMO_EXECUTUS; ++bossId)
            if (GetBossState(bossId) != DONE)
                return false;

        return !_ragnarosEngaged;
    }

    bool CanSummonRagnaros() const
    {
        if (GetCreature(BOSS_RAGNAROS) || GetBossState(BOSS_RAGNAROS) == DONE || GetBossState(BOSS_MAJORDOMO_EXECUTUS) != DONE)
            return false;

        return _ragnarosEngaged;
    }

    void SummonMajordomoOrRagnaros() const
    {
        if (CanSummonMajordomo())
        {
            if (GetBossState(BOSS_MAJORDOMO_EXECUTUS) != DONE)
            {
                if (Creature* majordomo = instance->SummonCreature(NPC_MAJORDOMO_EXECUTUS, MajordomoSummonPos))
                    majordomo->SummonCreatureGroup(SUMMON_GROUP_MAJORDOMO);
            }
            else if (Creature* majordomo = instance->SummonCreature(NPC_MAJORDOMO_EXECUTUS, { 847.103f, -816.153f, -229.775f, 4.344f }))
            {
                majordomo->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                majordomo->setFaction(35);
            }
        }
        else if (CanSummonRagnaros())
        {
            if (Creature* ragnaros = instance->SummonCreature(NPC_RAGNAROS, RagnarosSummonPos, nullptr, 172800000))
            {
                ragnaros->SetReactState(REACT_AGGRESSIVE);
                ragnaros->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
            }
        }
    }

    bool SetBossState(uint32 bossId, EncounterState state) override
    {
        if (!InstanceScript::SetBossState(bossId, state))
            return false;

        SummonMajordomoOrRagnaros();

        if (!_ragnarosEngaged && bossId == BOSS_RAGNAROS && state == IN_PROGRESS)
        {
            _ragnarosEngaged = true;
            SaveToDB();
        }

        if (bossId == BOSS_MAJORDOMO_EXECUTUS && state == DONE)
            DoRespawnGameObject(GetGameObject(DATA_CACHE_OF_THE_FIRELORD)->GetGUID(), 7 * DAY);

        return true;
    }

    void WriteSaveDataMore(std::ostringstream& data) override
    {
        data << _ragnarosEngaged;
    }

    void ReadSaveDataMore(std::istringstream& data) override
    {
        data >> _ragnarosEngaged;
    }

    private:
        bool _ragnarosEngaged;
};

void AddSC_instance_molten_core()
{
    new InstanceMapScriptLoader<instance_molten_core_InstanceMapScript>("instance_molten_core", 409);
}
