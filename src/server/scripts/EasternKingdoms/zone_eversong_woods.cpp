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

/* ScriptData
SDName: Eversong_Woods
SD%Complete: 95
SDComment: Quest support:
SDCategory: Eversong Woods
EndScriptData */

/* ContentData
EndContentData */

enum mirveda {
    QUEST_UNEXPECTED_RESULTS    = 8488,
    QUEST_CORRUPTED_SOIL        = 8487,

    SPELL_FIREBALL              = 20811,

    SETDATA_SUMMON_TYPE         = 1,
    SETDATA_SUMMON_VALUE        = 1,

    FACTION_EVENT               = 232,
    FACTION_NORMAL              = 1604,

    SAY_0                       = 0
};

struct npc_mirvedaAI : public ScriptedAI
{
    npc_mirvedaAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _scheduler.CancelAll();
        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        me->setFaction(FACTION_NORMAL);
        _summonsKilled = 0;
        _playerGUID = 0;
    }

    void sQuestAccept(Player* player, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_UNEXPECTED_RESULTS)
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->SummonCreatureGroup(0);
            me->setFaction(FACTION_EVENT);
            _playerGUID = player->GetGUID();

            _scheduler.Schedule(90s, [this](TaskContext task)
            {
                Reset();
            });
        }
    }

    void sQuestReward(Player* player, Quest const* quest, uint32 opt) override
    {
        if (quest->GetQuestId() == QUEST_CORRUPTED_SOIL)
        {
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            _scheduler.Schedule(10s, [this](TaskContext task)
            {
                Talk(SAY_0);
                Reset();
            });
        }
    }

    void SetData(uint32 Type, uint32 Data)
    {
        if (Type == SETDATA_SUMMON_TYPE)
            if (Data == SETDATA_SUMMON_VALUE)
                if (++_summonsKilled == 3)
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                    {
                        player->AreaExploredOrEventHappens(QUEST_UNEXPECTED_RESULTS);
                        Reset();
                    }
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(1s, [this](TaskContext task)
        {
            DoCastVictim(SPELL_FIREBALL);
            task.Repeat(5s, 8s);
        });
    }
private:
    TaskScheduler _scheduler;
    uint8 _summonsKilled;
    uint64 _playerGUID;
};

void AddSC_eversong_woods()
{
    new CreatureAILoader<npc_mirvedaAI>("npc_mirveda");
}
