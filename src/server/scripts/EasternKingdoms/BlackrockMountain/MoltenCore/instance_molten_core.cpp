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
    }

    void OnPlayerEnter(Player* /*player*/) override
    {
        if (!_events.GetNextEventTime(EVENT_CHECK_ENCOUNTER_STATE))
            _events.ScheduleEvent(EVENT_CHECK_ENCOUNTER_STATE, 10s);
    }

    void SummonMajordomoOrRagnaros() const
    {
        bool canSummon = true;
        if (GetCreature(BOSS_MAJORDOMO_EXECUTUS))
            canSummon = false;

        if (canSummon && GetBossState(BOSS_MAJORDOMO_EXECUTUS) == DONE && !GetCreature(BOSS_RAGNAROS))
        {
            if (Creature* ragnaros = instance->SummonCreature(NPC_RAGNAROS, RagnarosSummonPos, nullptr, 172800000))
            {
                ragnaros->SetReactState(REACT_AGGRESSIVE);
                ragnaros->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
                return;
            }
        }

        for (uint16 bossId = 0; bossId != BOSS_MAJORDOMO_EXECUTUS; ++bossId)
            if (GetBossState(bossId) != DONE)
                canSummon = false;

        if (canSummon)
            if (Creature* majordomo = instance->SummonCreature(NPC_MAJORDOMO_EXECUTUS, MajordomoSummonPos))
                majordomo->SummonCreatureGroup(SUMMON_GROUP_MAJORDOMO);
    }

    bool SetBossState(uint32 bossId, EncounterState state)
    {
        if (!InstanceScript::SetBossState(bossId, state))
            return false;

        SummonMajordomoOrRagnaros();

        if (bossId == BOSS_MAJORDOMO_EXECUTUS && state == DONE)
            DoRespawnGameObject(GetGameObject(DATA_CACHE_OF_THE_FIRELORD)->GetGUID(), 7 * DAY);

        return true;
    }

    void Update(uint32 diff) override
    {
        _events.Update(diff);

        if (_events.ExecuteEvent() == EVENT_CHECK_ENCOUNTER_STATE)
        {
            SummonMajordomoOrRagnaros();
            _events.Repeat(10s);
        }
    }

    private:
        EventMap _events;
};

void AddSC_instance_molten_core()
{
    new InstanceMapScriptLoader<instance_molten_core_InstanceMapScript>("instance_molten_core", 409);
}
