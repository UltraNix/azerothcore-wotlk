

/* ScriptData
SDName: Boss_Gahz'ranka
SD%Complete: 85
SDComment: Massive Geyser with knockback not working. Spell buggy.
SDCategory: Zul'Gurub
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "zulgurub.h"
#include "SpellScript.h"

enum Spells
{
    SPELL_FROSTBREATH               = 16099,
    SPELL_MASSIVEGEYSER             = 22421, // Not working. (summon)
    SPELL_SLAM                      = 24326
};

enum Events
{
    EVENT_FROSTBREATH               = 1,
    EVENT_MASSIVEGEYSER             = 2,
    EVENT_SLAM                      = 3
};

enum GahzMisc
{
    POINT_ID_GHAZ_END               = 3
};

class boss_gahzranka : public CreatureScript // gahzranka
{
    public: boss_gahzranka() : CreatureScript("boss_gahzranka") { }

        struct boss_gahzrankaAI : public BossAI
        {
            boss_gahzrankaAI(Creature* creature) : BossAI(creature, DATA_GAHZRANKA), _introFinished(false) { }

            void Reset()
            {
                if (instance->GetBossState(DATA_GAHZRANKA) == DONE)
                {
                    me->DespawnOrUnsummon();
                    return;
                }

                _Reset();
                if (!_introFinished)
                    me->GetMotionMaster()->MovePath(me->GetEntry() * 10, false);
            }

            void MovementInform(uint32 type, uint32 pointId) override
            {
                if (type != WAYPOINT_MOTION_TYPE)
                    return;

                if (pointId == POINT_ID_GHAZ_END)
                    DoZoneInCombat(me, 100.f);
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
            }

            void EnterCombat(Unit* /*who*/)
            {
                _EnterCombat();
                events.ScheduleEvent(EVENT_FROSTBREATH, 8000);
                events.ScheduleEvent(EVENT_MASSIVEGEYSER, 25000);
                events.ScheduleEvent(EVENT_SLAM, 17000);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FROSTBREATH:
                            DoCastVictim(SPELL_FROSTBREATH, true);
                            events.ScheduleEvent(EVENT_FROSTBREATH, urand(7000, 11000));
                            break;
                        case EVENT_MASSIVEGEYSER:
                            DoCastVictim(SPELL_MASSIVEGEYSER, true);
                            events.ScheduleEvent(EVENT_MASSIVEGEYSER, urand(22000, 32000));
                            break;
                        case EVENT_SLAM:
                            DoCastVictim(SPELL_SLAM, true);
                            events.ScheduleEvent(EVENT_SLAM, urand(12000, 20000));
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        private:
            bool _introFinished;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_gahzrankaAI(creature);
        }
};

constexpr uint32 SPELL_PAGLE_POINT_SPLASH_AND_QUAKE{ 24593 };
class spell_pagle_point_spawn_ghaz : public SpellScript
{
    PrepareSpellScript(spell_pagle_point_spawn_ghaz);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        //! This should spawn a barrel and after 2 seconds we should cast splash and quake
        //! But i cannot find which barrel it is without sniffs
        if (GetCaster())
            GetCaster()->CastSpell(GetCaster(), SPELL_PAGLE_POINT_SPLASH_AND_QUAKE, true);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_pagle_point_spawn_ghaz::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_boss_gahzranka()
{
    new SpellScriptLoaderEx<spell_pagle_point_spawn_ghaz>("spell_pagle_point_spawn_ghaz");
    new boss_gahzranka();
}
