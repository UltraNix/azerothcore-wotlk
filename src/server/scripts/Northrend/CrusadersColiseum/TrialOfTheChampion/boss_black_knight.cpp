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
    SPELL_RAISE_DEAD_JAEREN     = 67715,
    SPELL_RAISE_DEAD_ARELAS     = 67705,
    SPELL_BK_FEIGN_DEATH        = 67691,
    SPELL_BLACK_KNIGHT_RES      = 67693,
    SPELL_BK_KILL_CREDIT        = 68663,

    // phase 1
    SPELL_PLAGUE_STRIKE         = 67724,
    SPELL_ICY_TOUCH             = 67718,
    SPELL_DEATH_RESPITE         = 67745,
    SPELL_DEATH_RESPITE_DUMMY   = 66798,
    SPELL_OBLITERATE            = 67725,

    // phase 2 (+ abilities from phase 1 without death respite)
    SPELL_ARMY_DEAD             = 67761,
    SPELL_DESECRATION           = 67778,
    SPELL_DESECRATION_SUMMON    = 67779,
    SPELL_BK_GHOUL_EXPLODE      = 67751,

    // phase 3
    SPELL_DEATH_BITE            = 67808,
    SPELL_MARKED_DEATH          = 67823,

    // ghouls
    SPELL_CLAW                  = 67774,
    SPELL_EXPLODE               = 67729,
    SPELL_LEAP                  = 67749
};

enum Events
{
    EVENT_ANNOUNCER_SAY_ZOMBIE  = 1,
    EVENT_SPELL_PLAGUE_STRIKE,
    EVENT_SPELL_ICY_TOUCH,
    EVENT_SPELL_DEATH_RESPITE,
    EVENT_SPELL_OBLITERATE,
    EVENT_SPELL_DESECRATION,
    EVENT_SPELL_DEATH_BITE,
    EVENT_SPELL_MARKED_DEATH,
    EVENT_RANDOM_EXPLODE,

    // ghouls
    EVENT_LEAP                  = 1,
    EVENT_CLAW
};

enum NPCs
{
    NPC_RISEN_CHAMPION          = 35590,
};

enum Models
{
    MODEL_SKELETON              = 29846,
    MODEL_GHOST                 = 21300
};

struct boss_black_knightAI : public BossAI
{
    boss_black_knightAI(Creature* creature) : BossAI(creature, BOSS_BLACK_KNIGHT) {}

    void Reset() override
    {
        _Reset();
        _phase = 1;
        me->SetDisplayId(me->GetNativeDisplayId());
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->SetReactState(REACT_PASSIVE);
        instance->SetData(BOSS_BLACK_KNIGHT, NOT_STARTED);

        //me->SetLootMode(0); // [LOOT]
    }

    void EnterEvadeMode() override
    {
        me->DespawnOrUnsummon(1);
        _EnterEvadeMode();
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        if(id == 195)
            if (Creature* announcer = instance->instance->GetCreature(instance->GetData64(DATA_ANNOUNCER)))
                me->SetFacingToObject(announcer);   
    }

    void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask) override
    {
        if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
        {
            damage = 0;
            return;
        }

        if (_phase < 3 && damage >= me->GetHealth())
        {
            damage = 0;
            me->SetHealth(me->GetMaxHealth());
            events.Reset();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->RemoveAllAuras();
            me->SetControlled(true, UNIT_STATE_STUNNED);
            for (auto itr : summons)
            {
                if (Creature* summon = instance->instance->GetCreature(itr))
                    if (summon->IsAIEnabled)
                        summon->AI()->DoAction(1);

            }
            summons.clear();

            DoCastSelf(SPELL_BK_FEIGN_DEATH, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_29);
            me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
            me->AddUnitState(UNIT_STATE_DIED);
        }
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        DoAction(1);
    }

    void DoAction(int32 param) override
    {
        if (param == -1)
            summons.DespawnAll();
        else if (param == 1)
        {
            instance->SetData(BOSS_BLACK_KNIGHT, IN_PROGRESS);
            Talk(TEXT_BK_AGGRO);
            DoCastAOE(instance->GetData(DATA_TEAMID_IN_INSTANCE) == TEAM_HORDE ? SPELL_RAISE_DEAD_JAEREN : SPELL_RAISE_DEAD_ARELAS);
            if (Creature* announcer = instance->instance->GetCreature(instance->GetData64(DATA_ANNOUNCER)))
                announcer->DespawnOrUnsummon();

            events.Reset();
            events.ScheduleEvent(EVENT_ANNOUNCER_SAY_ZOMBIE, 2500);
            events.ScheduleEvent(EVENT_SPELL_PLAGUE_STRIKE, urand(7000, 9000));
            events.ScheduleEvent(EVENT_SPELL_ICY_TOUCH, urand(3500, 7000));
            events.ScheduleEvent(EVENT_SPELL_DEATH_RESPITE, urand(13000, 15000));
            events.ScheduleEvent(EVENT_SPELL_OBLITERATE, urand(11000, 19000));
        }
    }

    void SpellHitTarget(Unit* /*target*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_BLACK_KNIGHT_RES)
        {
            me->SetHealth(me->GetMaxHealth());
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetControlled(false, UNIT_STATE_STUNNED);

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_29);
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
            me->ClearUnitState(UNIT_STATE_DIED);

            ++_phase;

            switch (_phase)
            {
                case 2:
                    me->SetDisplayId(MODEL_SKELETON);
                    Talk(TEXT_BK_SKELETON_RES);
                    DoCastSelf(SPELL_ARMY_DEAD);

                    events.Reset();
                    events.ScheduleEvent(EVENT_RANDOM_EXPLODE, 15000);
                    events.ScheduleEvent(EVENT_SPELL_PLAGUE_STRIKE, urand(7000, 9000));
                    events.ScheduleEvent(EVENT_SPELL_ICY_TOUCH, urand(3500, 7000));
                    events.ScheduleEvent(EVENT_SPELL_OBLITERATE, urand(11000, 19000));
                    events.ScheduleEvent(EVENT_SPELL_DESECRATION, urand(2000, 3000));
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
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_ANNOUNCER_SAY_ZOMBIE:
                if (!summons.empty())
                    if (Creature* ghoul = instance->instance->GetCreature(*summons.begin()))
                        ghoul->MonsterYell("[Zombie] .... . Brains ....", LANG_UNIVERSAL, 0);
                break;
            case EVENT_SPELL_PLAGUE_STRIKE:
                DoCastVictim(SPELL_PLAGUE_STRIKE);
                events.Repeat(urand(10000, 12000));
                break;
            case EVENT_SPELL_ICY_TOUCH:
                DoCastVictim(SPELL_ICY_TOUCH);
                events.Repeat(urand(5000, 6000));
                break;
            case EVENT_SPELL_DEATH_RESPITE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    DoCast(target, SPELL_DEATH_RESPITE);
                events.Repeat(urand(13000, 15000));
                break;
            case EVENT_RANDOM_EXPLODE:
                DoCastAOE(SPELL_BK_GHOUL_EXPLODE);
                events.Repeat(15000);
                break;
            case EVENT_SPELL_OBLITERATE:
                DoCastVictim(SPELL_OBLITERATE);
                events.Repeat(urand(15000, 17000));
                break;
            case EVENT_SPELL_DESECRATION:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    DoCast(target, SPELL_DESECRATION);
                events.Repeat(urand(14000, 17000));
                break;
            case EVENT_SPELL_DEATH_BITE:
                DoCastAOE(SPELL_DEATH_BITE);
                events.Repeat(urand(2000, 4000));
                break;
            case EVENT_SPELL_MARKED_DEATH:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                    DoCast(target, SPELL_MARKED_DEATH);
                events.Repeat(9000);
                break;
            default:
                break;
        }
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
        if (Unit* target = summon->SelectNearestTarget(200.0f))
        {
            summon->AI()->AttackStart(target);
            DoZoneInCombat(summon);
        }
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer())
            Talk(urand(0, 1) ? TEXT_BK_SLAIN_1 : TEXT_BK_SLAIN_2);
    }

    void JustDied(Unit* /*killer*/) override
    {
        instance->SetData(247, 0);
        DoCastAOE(SPELL_BK_KILL_CREDIT, true);
        Talk(TEXT_BK_DEATH);
        instance->SetData(BOSS_BLACK_KNIGHT, DONE);
        if (me->ToTempSummon())
            me->ToTempSummon()->SetTempSummonType(TEMPSUMMON_MANUAL_DESPAWN);
    }

    void MoveInLineOfSight(Unit* /*who*/) override {}

private:
    uint8 _phase;
};

struct npc_black_knight_skeletal_gryphonAI : public npc_escortAI
{
    npc_black_knight_skeletal_gryphonAI(Creature* creature) : npc_escortAI(creature) {}

    void Reset() override
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
        Start(false, true, 0, nullptr);
        SetDespawnAtEnd(true);
    }

    void DoAction(int32 param) override
    {
        if (param == 1)
        {
            me->SetCanFly(true);
            me->SetDisableGravity(true);
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
            SetEscortPaused(false);
        }
    }

    void WaypointReached(uint32 point) override
    {
        if (point == 10)
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

    void UpdateAI(uint32 diff) override
    {
        npc_escortAI::UpdateAI(diff);
    }
};

struct npc_black_knight_ghoulAI : public ScriptedAI
{
    npc_black_knight_ghoulAI(Creature* creature) : ScriptedAI(creature)
    {
        instance = me->GetInstanceScript();
    }

    void Reset() override
    {
        _explode = false;
        _events.Reset();
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _events.Reset();
        if (me->GetEntry() == NPC_RISEN_JAEREN || me->GetEntry() == NPC_RISEN_ARELAS)
            _events.RescheduleEvent(EVENT_LEAP, 1000); 
        _events.RescheduleEvent(EVENT_CLAW, urand(3000, 4000)); 
    }

    void DoExplode()
    {
        if (!_explode)
        {
            _explode = true;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
            me->AddAura(SPELL_BK_GHOUL_EXPLODE, me);
            DoCastSelf(SPELL_EXPLODE);
        }
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == 1)
            DoExplode();
    }

    void SpellHit(Unit* /*caster*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_BK_GHOUL_EXPLODE)
            DoExplode();
    }

    void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask) override
    {
        if (me->HealthBelowPctDamaged(30, damage))
            DoExplode();
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spell)
    {
        switch (spell->Id)
        {
            case SPELL_CLAW:
                DoResetThreat();
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f))
                {
                    me->AddThreat(target, 100.0f);
                    AttackStart(target);
                }
                break;
            case SPELL_EXPLODE:
                if (target && target->IsPlayer())
                    if (instance)
                        instance->SetData(DATA_ACHIEV_IVE_HAD_WORSE, 0);
                break;
            default:
                break;
        }
    }

    void UpdateAI(uint32 diff)
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_LEAP: 
                    if (Unit* target = me->GetVictim())
                        if (me->IsInRange(target, 5.0f, 30.0f))
                        {
                            DoCast(target, SPELL_LEAP);
                            break;
                        }
                    _events.Repeat(1000);
                    break;
                case EVENT_CLAW: 
                    DoCastVictim(SPELL_CLAW);
                    _events.Repeat(urand(6000, 8000));
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

private:
    InstanceScript* instance;
    EventMap _events;
    bool _explode;
};

void AddSC_boss_black_knight()
{
    new CreatureAILoader<boss_black_knightAI>("boss_black_knight");
    new CreatureAILoader<npc_black_knight_skeletal_gryphonAI>("npc_black_knight_skeletal_gryphon");
    new CreatureAILoader<npc_black_knight_ghoulAI>("npc_black_knight_ghoul");
}
