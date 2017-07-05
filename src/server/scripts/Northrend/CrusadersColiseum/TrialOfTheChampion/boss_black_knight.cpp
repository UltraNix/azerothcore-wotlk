/*
REWRITTEN FROM SCRATCH BY PUSSYWIZARD, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "trial_of_the_champion.h"
#include "SpellInfo.h"

enum Spells
{
    SPELL_RAISE_DEAD_JAEREN            = 67715,
    SPELL_RAISE_DEAD_ARELAS            = 67705,
    SPELL_BK_FEIGN_DEATH            = 67691,
    SPELL_BLACK_KNIGHT_RES            = 67693,
    SPELL_BK_KILL_CREDIT            = 68663,

    // phase 1
    SPELL_PLAGUE_STRIKE_N            = 67724,
    SPELL_PLAGUE_STRIKE_H            = 67884,
    SPELL_ICY_TOUCH_N                = 67718,
    SPELL_ICY_TOUCH_H                = 67881,
    SPELL_DEATH_RESPITE_N            = 67745,
    SPELL_DEATH_RESPITE_H            = 68306,
    SPELL_DEATH_RESPITE_DUMMY        = 66798,
    SPELL_OBLITERATE_N                = 67725,
    SPELL_OBLITERATE_H                = 67883,

    // phase 2 (+ abilities from phase 1 without death respite)
    SPELL_ARMY_DEAD_N                = 67761,
    SPELL_ARMY_DEAD_H                = 67874,
    SPELL_DESECRATION_N                = 67778,
    SPELL_DESECRATION_H                = 67877,
    SPELL_DESECRATION_SUMMON        = 67779,
    SPELL_BK_GHOUL_EXPLODE            = 67751,

    // phase 3
    SPELL_DEATH_BITE_N                = 67808,
    SPELL_DEATH_BITE_H                = 67875,
    SPELL_MARKED_DEATH_N            = 67823,
    SPELL_MARKED_DEATH_H            = 67882,

    // ghouls
    SPELL_CLAW_N                    = 67774,
    SPELL_CLAW_H                    = 67879,
    SPELL_EXPLODE_N                    = 67729,
    SPELL_EXPLODE_H                    = 67886,
    SPELL_LEAP_N                    = 67749,
    SPELL_LEAP_H                    = 67880,
};
#define SPELL_LEAP                    DUNGEON_MODE(SPELL_LEAP_N, SPELL_LEAP_H)
#define SPELL_EXPLODE                DUNGEON_MODE(SPELL_EXPLODE_N, SPELL_EXPLODE_H)

#define SPELL_PLAGUE_STRIKE            DUNGEON_MODE(SPELL_PLAGUE_STRIKE_N, SPELL_PLAGUE_STRIKE_H)
#define SPELL_ICY_TOUCH                DUNGEON_MODE(SPELL_ICY_TOUCH_N, SPELL_ICY_TOUCH_H)
#define SPELL_DEATH_RESPITE            DUNGEON_MODE(SPELL_DEATH_RESPITE_N, SPELL_DEATH_RESPITE_H)
#define SPELL_OBLITERATE            DUNGEON_MODE(SPELL_OBLITERATE_N, SPELL_OBLITERATE_H)
#define SPELL_ARMY_DEAD                DUNGEON_MODE(SPELL_ARMY_DEAD_N, SPELL_ARMY_DEAD_H)
#define SPELL_DESECRATION            DUNGEON_MODE(SPELL_DESECRATION_N, SPELL_DESECRATION_H)
#define SPELL_DEATH_BITE            DUNGEON_MODE(SPELL_DEATH_BITE_N, SPELL_DEATH_BITE_H)
#define SPELL_MARKED_DEATH            DUNGEON_MODE(SPELL_MARKED_DEATH_N, SPELL_MARKED_DEATH_H)

enum Events
{
    EVENT_ANNOUNCER_SAY_ZOMBIE = 1,
    EVENT_SPELL_PLAGUE_STRIKE,
    EVENT_SPELL_ICY_TOUCH,
    EVENT_SPELL_DEATH_RESPITE,
    EVENT_SPELL_OBLITERATE,
    EVENT_SPELL_DESECRATION,
    EVENT_SPELL_DEATH_BITE,
    EVENT_SPELL_MARKED_DEATH,
};

enum NPCs
{
    NPC_RISEN_CHAMPION                = 35590,
};

enum Models
{
    MODEL_SKELETON                    = 29846,
    MODEL_GHOST                        = 21300
};


class boss_black_knight : public CreatureScript
{
public:
    boss_black_knight() : CreatureScript("boss_black_knight") { }

    struct boss_black_knightAI : public ScriptedAI
    {
        boss_black_knightAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me)
        {
            pInstance = pCreature->GetInstanceScript();
        }

        InstanceScript* pInstance;
        EventMap events;
        SummonList summons;
        uint8 Phase;

        void Reset()
        {
            events.Reset();
            summons.DespawnAll();
            Phase = 1;
            me->SetDisplayId(me->GetNativeDisplayId());
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            if( pInstance )
                pInstance->SetData(BOSS_BLACK_KNIGHT, NOT_STARTED);

            //me->SetLootMode(0); // [LOOT]
        }

        void EnterEvadeMode()
        {
            me->DespawnOrUnsummon(1);
            ScriptedAI::EnterEvadeMode();
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != POINT_MOTION_TYPE)
                return;

            if(id == 195)
                if (Creature* announcer = pInstance->instance->GetCreature(pInstance->GetData64(DATA_ANNOUNCER)))
                    me->SetFacingToObject(announcer);   
        }

        void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask)
        {
            if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            {
                damage = 0;
                return;
            }

            if( Phase < 3 && damage >= me->GetHealth() )
            {
                damage = 0;
                me->SetHealth(me->GetMaxHealth());
                events.Reset();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveAllAuras();
                me->SetControlled(true, UNIT_STATE_STUNNED);
                me->CastSpell(me, SPELL_BK_GHOUL_EXPLODE, true);
                summons.clear();

                me->CastSpell(me, SPELL_BK_FEIGN_DEATH, true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_29);
                me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                me->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                me->AddUnitState(UNIT_STATE_DIED);

            }
        }

        void DoAction(int32 param)
        {
            if( param == -1 )
            {
                summons.DespawnAll();
            }
            else if( param == 1 )
            {
                if( !pInstance )
                    return;

                pInstance->SetData(BOSS_BLACK_KNIGHT, IN_PROGRESS);
                Talk(TEXT_BK_AGGRO);
                me->CastSpell((Unit*)NULL, (pInstance->GetData(DATA_TEAMID_IN_INSTANCE)==TEAM_HORDE ? SPELL_RAISE_DEAD_JAEREN : SPELL_RAISE_DEAD_ARELAS), false);
                if( Creature* announcer = pInstance->instance->GetCreature(pInstance->GetData64(DATA_ANNOUNCER)) )
                    announcer->DespawnOrUnsummon();

                events.Reset();
                events.ScheduleEvent(EVENT_ANNOUNCER_SAY_ZOMBIE, 2500);
                events.ScheduleEvent(EVENT_SPELL_PLAGUE_STRIKE, urand(7000,9000));
                events.ScheduleEvent(EVENT_SPELL_ICY_TOUCH, urand(3500,7000));
                events.ScheduleEvent(EVENT_SPELL_DEATH_RESPITE, urand(13000,15000));
                events.ScheduleEvent(EVENT_SPELL_OBLITERATE, urand(11000,19000));
            }
        }

        void SpellHitTarget(Unit* target, const SpellInfo* spell)
        {
            switch( spell->Id )
            {
                case SPELL_BLACK_KNIGHT_RES:
                    me->SetHealth(me->GetMaxHealth());
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetControlled(false, UNIT_STATE_STUNNED);
                    
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_29);
                    me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                    me->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                    me->ClearUnitState(UNIT_STATE_DIED);

                    ++Phase;

                    switch( Phase )
                    {
                        case 2:
                            me->SetDisplayId(MODEL_SKELETON);
                            Talk(TEXT_BK_SKELETON_RES);
                            me->CastSpell(me, SPELL_ARMY_DEAD, false);

                            events.Reset();
                            events.ScheduleEvent(EVENT_SPELL_PLAGUE_STRIKE, urand(7000,9000));
                            events.ScheduleEvent(EVENT_SPELL_ICY_TOUCH, urand(3500,7000));
                            events.ScheduleEvent(EVENT_SPELL_OBLITERATE, urand(11000,19000));
                            events.ScheduleEvent(EVENT_SPELL_DESECRATION, urand(2000,3000));
                            break;
                        case 3:
                            me->SetDisplayId(MODEL_GHOST);
                            Talk(TEXT_BK_GHOST_RES);

                            events.Reset();
                            events.ScheduleEvent(EVENT_SPELL_DEATH_BITE, 2000);
                            events.ScheduleEvent(EVENT_SPELL_MARKED_DEATH, 1000);
                            break;
                        default:
                            EnterEvadeMode();
                            break;
                    }
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if( !UpdateVictim() )
                return;

            events.Update(diff);

            if( me->HasUnitState(UNIT_STATE_CASTING) )
                return;

            switch( events.GetEvent() )
            {
                case 0:
                    break;
                case EVENT_ANNOUNCER_SAY_ZOMBIE:
                    if( pInstance && !summons.empty() )
                        if( Creature* ghoul = pInstance->instance->GetCreature(*summons.begin()) )
                            ghoul->MonsterYell("[Zombie] .... . Brains ....", LANG_UNIVERSAL, 0);
                    events.PopEvent();
                    break;
                case EVENT_SPELL_PLAGUE_STRIKE:
                    if( me->GetVictim() )
                        me->CastSpell(me->GetVictim(), SPELL_PLAGUE_STRIKE, false);
                    events.RepeatEvent(urand(10000,12000));
                    break;
                case EVENT_SPELL_ICY_TOUCH:
                    if( me->GetVictim() )
                        me->CastSpell(me->GetVictim(), SPELL_ICY_TOUCH, false);
                    events.RepeatEvent(urand(5000,6000));
                    break;
                case EVENT_SPELL_DEATH_RESPITE:
                    if( Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true) )
                        me->CastSpell(target, SPELL_DEATH_RESPITE, false);
                    events.RepeatEvent(urand(13000,15000));
                    break;
                case EVENT_SPELL_OBLITERATE:
                    if( me->GetVictim() )
                        me->CastSpell(me->GetVictim(), SPELL_OBLITERATE, false);
                    events.RepeatEvent(urand(15000,17000));
                    break;
                case EVENT_SPELL_DESECRATION:
                    if( Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true) )
                        me->CastSpell(target, SPELL_DESECRATION, false);
                    events.RepeatEvent(urand(14000,17000));
                    break;
                case EVENT_SPELL_DEATH_BITE:
                    me->CastSpell((Unit*)NULL, SPELL_DEATH_BITE, false);
                    events.RepeatEvent(urand(2000,4000));
                    break;
                case EVENT_SPELL_MARKED_DEATH:
                    if( Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.000000f, true) )
                        me->CastSpell(target, SPELL_MARKED_DEATH, false);
                    events.RepeatEvent(9000);
                    break;
            }

            DoMeleeAttackIfReady();
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            if( Unit* target = summon->SelectNearestTarget(200.0f) )
            {
                summon->AI()->AttackStart(target);
                DoZoneInCombat(summon);
            }
        }

        void KilledUnit(Unit* victim)
        {
            if( victim->GetTypeId() == TYPEID_PLAYER )
            {
                if( urand(0,1) )
                    Talk(TEXT_BK_SLAIN_1);
                else
                    Talk(TEXT_BK_SLAIN_2);
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            me->CastSpell((Unit*)NULL, SPELL_BK_KILL_CREDIT, true);
            Talk(TEXT_BK_DEATH);
            if( pInstance )
                pInstance->SetData(BOSS_BLACK_KNIGHT, DONE);
            if( me->ToTempSummon() )
                me->ToTempSummon()->SetTempSummonType(TEMPSUMMON_MANUAL_DESPAWN);
        }
    };

    CreatureAI* GetAI(Creature *pCreature) const
    {
        return new boss_black_knightAI (pCreature);
    }
};

class npc_black_knight_skeletal_gryphon : public CreatureScript
{
public:
    npc_black_knight_skeletal_gryphon() : CreatureScript("npc_black_knight_skeletal_gryphon") {}

    struct npc_black_knight_skeletal_gryphonAI : public npc_escortAI
    {
        npc_black_knight_skeletal_gryphonAI(Creature* pCreature) : npc_escortAI(pCreature) {}

        void Reset()
        {
            // Black Knight is flying towards arena
            AddWaypoint(0, 766.99f, 657.16f, 457.43f);
            AddWaypoint(1, 747.28f, 659.71f, 440.49f);
            AddWaypoint(2, 730.03f, 639.59f, 428.16f);
            AddWaypoint(3, 721.13f, 621.49f, 423.16f);
            AddWaypoint(4, 731.72f, 599.81f, 421.99f);
            AddWaypoint(5, 753.71f, 591.09f, 420.63f);
            AddWaypoint(6, 776.53f, 597.52f, 418.05f);
            AddWaypoint(7, 787.38f, 617.07f, 417.49f);
            AddWaypoint(8, 777.06f, 636.98f, 416.57f);
            AddWaypoint(9, 760.6f, 642.12f, 414.71f);
            AddWaypoint(10, 751.697144f, 632.806641f, 411.573242f);
            // The vehicle starts flying away
            AddWaypoint(11, 748.89f, 633.61f, 415.24f);
            AddWaypoint(12, 740.42f, 636.31f, 418.32f);
            AddWaypoint(13, 727.49f, 637.4f, 422.24f);
            AddWaypoint(14, 716.59f, 617.99f, 422.24f);
            AddWaypoint(15, 727.18f, 599.29f, 422.24f);
            AddWaypoint(16, 746.63f, 587.77f, 422.24f);
            AddWaypoint(17, 765.6f, 599.52f, 422.24f);
            AddWaypoint(18, 777.01f, 618.79f, 422.24f);
            AddWaypoint(19, 761.84f, 642.18f, 422.24f);
            AddWaypoint(20, 746.09f, 670.33f, 429.68f);
            AddWaypoint(21, 748.02f, 728.22f, 466.68f);
            AddWaypoint(22, 779.44f, 797.49f, 477.79f);
            AddWaypoint(23, 859.14f, 807.98f, 477.79f);
            Start(false,true,0,NULL);
            SetDespawnAtEnd(true);
        }

        void DoAction(int32 param)
        {
            if( param == 1 )
            {
                me->SetCanFly(true);
                me->SetDisableGravity(true);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                SetEscortPaused(false);
            }
        }

        void WaypointReached(uint32 i)
        {
            if (i == 10)
            {
                SetEscortPaused(true);
                me->SetCanFly(false);
                me->SetDisableGravity(false);
                if (InstanceScript* instance = me->GetInstanceScript())
                {
                    if (Creature* announcer = instance->instance->GetCreature(instance->GetData64(DATA_ANNOUNCER)))
                    {
                        me->SetOrientation(me->GetAngle(announcer));
                        me->SetFacingToObject(announcer);
                    }

                    instance->SetData(DATA_SKELETAL_GRYPHON_LANDED, 0);
                }
            }
        }

        void UpdateAI(uint32 uiDiff)
        {
            npc_escortAI::UpdateAI(uiDiff);
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_black_knight_skeletal_gryphonAI(pCreature);
    }
};

class npc_black_knight_ghoul : public CreatureScript
{
public:
    npc_black_knight_ghoul() : CreatureScript("npc_black_knight_ghoul") { }

    struct npc_black_knight_ghoulAI : public ScriptedAI
    {
        npc_black_knight_ghoulAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            pInstance = pCreature->GetInstanceScript();
        }

        InstanceScript* pInstance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* who)
        {
            events.Reset();
            if (me->GetEntry() == NPC_RISEN_JAEREN || me->GetEntry() == NPC_RISEN_ARELAS)
                events.RescheduleEvent(1, 1000); // leap
            events.RescheduleEvent(2, urand(3000,4000)); // claw
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_BK_GHOUL_EXPLODE)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
                me->CastSpell(me, SPELL_EXPLODE, false);
            }
        }

        void SpellHitTarget(Unit* target, const SpellInfo* spell)
        {
            switch(spell->Id)
            {
                case SPELL_CLAW_N:
                case SPELL_CLAW_H:
                    DoResetThreat();
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f))
                    {
                        me->AddThreat(target, 100.0f);
                        AttackStart(target);
                    }
                    break;
                case SPELL_EXPLODE_H:
                    if (target && target->GetTypeId() == TYPEID_PLAYER)
                        if (pInstance)
                            pInstance->SetData(DATA_ACHIEV_IVE_HAD_WORSE, 0);
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if( !UpdateVictim() )
                return;

            events.Update(diff);

            if( me->HasUnitState(UNIT_STATE_CASTING) )
                return;

            switch( events.GetEvent() )
            {
                case 0:
                    break;
                case 1: // leap
                    if (Unit* target = me->GetVictim())
                        if (me->GetDistance(target) > 5.0f && me->GetDistance(target) < 30.0f)
                        {
                            me->CastSpell(target, SPELL_LEAP, false);
                            events.PopEvent();
                            break;
                        }
                    events.RepeatEvent(1000);
                    break;
                case 2: // claw
                    if (Unit* target = me->GetVictim())
                        me->CastSpell(target, SPELL_CLAW_N, false);
                    events.RepeatEvent(urand(6000,8000));
                    break;
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature *pCreature) const
    {
        return new npc_black_knight_ghoulAI (pCreature);
    }
};

void AddSC_boss_black_knight()
{
    new boss_black_knight();
    new npc_black_knight_skeletal_gryphon();
    new npc_black_knight_ghoul();
}
