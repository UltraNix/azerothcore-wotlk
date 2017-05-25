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
SDName: Boss_Fankriss
SD%Complete: 100
SDComment: sound not implemented
SDCategory: Temple of Ahn'Qiraj
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "temple_of_ahnqiraj.h"

#define SOUND_SENTENCE_YOU 8588
#define SOUND_SERVE_TO     8589
#define SOUND_LAWS         8590
#define SOUND_TRESPASS     8591
#define SOUND_WILL_BE      8592

enum Spells
{
    SPELL_MORTAL_WOUND      = 28467,
    SPELL_ENTANGLE_1        = 720,
    SPELL_ENTANGLE_2        = 731,
    SPELL_ENTANGLE_3        = 1121,
    SPELL_SUMMON_WORM_1     = 518,
    SPELL_SUMMON_WORM_2     = 25831,
    SPELL_SUMMON_WORM_3     = 25832,
};

enum Events
{
    EVENT_MORTAL_WOUND      = 1,
    EVENT_SUMMON_ADDS,
    EVENT_ENTANGLE,
    EVENT_SUMMON_ENTANGLE
};

enum Misc
{
    NPC_HATCHLING           = 15962,
};

class boss_fankriss : public CreatureScript
{
    public:
        boss_fankriss() : CreatureScript("boss_fankriss") { }

        struct boss_fankrissAI : public BossAI
        {
            boss_fankrissAI(Creature* creature) : BossAI(creature, DATA_FANKRISS) { }

            void Reset() override
            {
                _Reset();
                _entangledPlayer = nullptr;
            }

            void EnterCombat(Unit* /*who*/) override
            {
                _EnterCombat();
                events.ScheduleEvent(EVENT_MORTAL_WOUND, urand(10000, 15000));
                events.ScheduleEvent(EVENT_SUMMON_ADDS, urand(30000, 50000));
                events.ScheduleEvent(EVENT_ENTANGLE, urand(25000, 40000));
            }

            void JustSummoned(Creature* summon) override
            {
                if (summon->GetEntry() == NPC_HATCHLING && summon->IsAIEnabled)
                {
                    summons.Summon(summon);
                    if (Player* target = _entangledPlayer)
                        summon->AI()->AttackStart(target);
                    return;
                }

                BossAI::JustSummoned(summon);
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                switch (events.GetEvent())
                {
                    case EVENT_MORTAL_WOUND:
                        DoCastVictim(SPELL_MORTAL_WOUND);
                        events.RepeatEvent(urand(7000, 14000));
                        break;
                    case EVENT_ENTANGLE:
                        if (Player* target = SelectTargetFromPlayerList(100.0f))
                        {
                            _entangledPlayer = target;
                            DoCast(target, RAND(SPELL_ENTANGLE_1, SPELL_ENTANGLE_2, SPELL_ENTANGLE_3));
                            events.ScheduleEvent(EVENT_SUMMON_ENTANGLE, 1000);
                        }
                        events.RepeatEvent(urand(40000, 70000));
                        break;
                    case EVENT_SUMMON_ENTANGLE:
                        if (Player* target = _entangledPlayer)
                        {
                            for (uint8 itr = 0; itr < 4; ++itr)
                            {
                                Position pos;
                                target->GetPosition(&pos);
                                if (pos.IsPositionValid())
                                {
                                    pos.m_positionX += frand(-3.0f, 3.0f);
                                    pos.m_positionY += frand(-3.0f, 3.0f);
                                    me->SummonCreature(NPC_HATCHLING, pos, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
                                }
                            }
                        }
                        events.PopEvent();
                        break;
                    case EVENT_SUMMON_ADDS:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            DoCast(target, RAND(SPELL_SUMMON_WORM_1, SPELL_SUMMON_WORM_2, SPELL_SUMMON_WORM_3));
                        events.RepeatEvent(urand(15000, 40000));
                        break;
                    default:
                        break;
                }

                DoMeleeAttackIfReady();
            }
            private:
                Player* _entangledPlayer;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_fankrissAI(creature);
        }
};

void AddSC_boss_fankriss()
{
    new boss_fankriss();
}
