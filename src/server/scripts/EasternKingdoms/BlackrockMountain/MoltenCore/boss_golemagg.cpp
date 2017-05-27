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
SDName: Boss_Golemagg
SD%Complete: 90
SDComment: Timers need to be confirmed, Golemagg's Trust need to be checked
SDCategory: Molten Core
EndScriptData */

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "molten_core.h"

enum Texts
{
    EMOTE_LOWHP             = 0,
};

enum Spells
{
    // Golemagg
    SPELL_MAGMA_SPLASH      = 13879,
    SPELL_PYROBLAST         = 20228,
    SPELL_EARTHQUAKE        = 19798,
    SPELL_ENRAGE            = 19953,
    SPELL_GOLEMAGG_TRUST    = 20553,
    SPELL_DOUBLE_ATTACK     = 18943,

    // Core Rager
    SPELL_THRASH            = 12787,
    SPELL_MANGLE            = 19820
};

enum Events
{
    // Golemagg
    EVENT_PYROBLAST         = 1,
    EVENT_EARTHQUAKE,

    // Core Rager
    EVENT_MANGLE            = 1,
    EVENT_TRUST
};

class boss_golemagg : public CreatureScript
{
    public:
        boss_golemagg() : CreatureScript("boss_golemagg") { }

        struct boss_golemaggAI : public BossAI
        {
            boss_golemaggAI(Creature* creature) : BossAI(creature, BOSS_GOLEMAGG_THE_INCINERATOR) { }

            void Reset()
            {
                _Reset();
                DoCast(me, SPELL_MAGMA_SPLASH, true);
            }

            void EnterCombat(Unit* /*victim*/)
            {
                _EnterCombat();
                me->CallForHelp(15.0f);
                events.ScheduleEvent(EVENT_PYROBLAST, 7000);
            }

            void EnterEvadeMode() override
            {
                std::list<Creature*> addList;
                me->GetCreatureListWithEntryInGrid(addList, 11672, 100.0f);
                if (!addList.empty())
                {
                    for (auto itr : addList)
                    {
                        if (!itr->IsAlive())
                            itr->Respawn();
                        if (itr->IsAIEnabled)
                            itr->AI()->EnterEvadeMode();
                    }
                }
                CreatureAI::EnterEvadeMode();
            }

            void DamageTaken(Unit*, uint32& /*damage*/, DamageEffectType, SpellSchoolMask)
            {
                if (!HealthBelowPct(10) || me->HasAura(SPELL_ENRAGE))
                    return;

                DoCast(me, SPELL_ENRAGE, true);
                events.ScheduleEvent(EVENT_EARTHQUAKE, 3000);
            }

            void ExecuteEvent(uint32 eventId) override
            {
                switch (eventId)
                {
                    case EVENT_PYROBLAST:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            DoCast(target, SPELL_PYROBLAST);
                        events.ScheduleEvent(EVENT_PYROBLAST, 7000);
                        break;
                    case EVENT_EARTHQUAKE:
                        DoCastVictim(SPELL_EARTHQUAKE);
                        events.ScheduleEvent(EVENT_EARTHQUAKE, 3000);
                        break;
                    default:
                        break;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_golemaggAI(creature);
        }
};

class npc_core_rager : public CreatureScript
{
    public:
        npc_core_rager() : CreatureScript("npc_core_rager") { }

        struct npc_core_ragerAI : public ScriptedAI
        {
            npc_core_ragerAI(Creature* creature) : ScriptedAI(creature), instance(creature->GetInstanceScript()) { }

            void EnterCombat(Unit* victim)
            {
                CreatureAI::EnterCombat(victim);
                _events.ScheduleEvent(EVENT_TRUST, 2000);
            }

            void DamageTaken(Unit*, uint32& /*damage*/, DamageEffectType, SpellSchoolMask)
            {
                if (HealthAbovePct(50) || !instance)
                    return;

                if (Creature* pGolemagg = instance->instance->GetCreature(instance->GetData64(BOSS_GOLEMAGG_THE_INCINERATOR)))
                {
                    if (pGolemagg->IsAlive())
                    {
                        Talk(EMOTE_LOWHP);
                        me->SetFullHealth();
                    }
                    else
                        me->DespawnOrUnsummon();
                }
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                _events.Update(diff);

                while (uint32 eventId = _events.GetEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_MANGLE:
                            DoCastVictim(SPELL_MANGLE);
                            _events.RepeatEvent(10000);
                            break;
                        case EVENT_TRUST:
                            if (Creature* hound = me->FindNearestCreature(11672, 30.0f, true))
                                me->AddAura(SPELL_GOLEMAGG_TRUST, me);
                            _events.RepeatEvent(2000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

        private:
            InstanceScript* instance;
            EventMap _events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetInstanceAI<npc_core_ragerAI>(creature);
        }
};

void AddSC_boss_golemagg()
{
    new boss_golemagg();
    new npc_core_rager();
}
