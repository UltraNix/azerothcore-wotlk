#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "temple_of_ahnqiraj.h"

enum Spells
{
    SPELL_SWEEP                  = 26103,
    SPELL_SANDBLAST              = 26102,
    SPELL_BOULDER                = 26616,
    SPELL_BERSERK                = 26615,
    SPELL_BIRTH                  = 26262,
    SPELL_GROUND_RUPTURE         = 26100,
    SPELL_SUMMON_BASE            = 26133,
    SPELL_SUBMERGE_VISUAL        = 26063,
    SPELL_SUMMON_OURO_MOUNDS     = 26058,
    SPELL_SUMMON_TRIGGER         = 26284,
    SPELL_SUMMON_OURO            = 26061,
    SPELL_SUMMON_OURO_MOUND      = 26617,
    SPELL_DIRTMOUND_PASSIVE      = 26092,
    SPELL_SUMMON_SCARABS         = 26060,
};

enum Events
{
    EVENT_SWEEP                  = 1,
    EVENT_SAND_BLAST,
    EVENT_SUBMERGE,
    EVENT_EMERGE,
    EVENT_SUMMON_BASE,
    EVENT_SUMMON_MOUND,
    EVENT_MELEE_CHECK
};

enum Phases
{
    PHASE_FIGHT                  = 1,
    PHASE_SUBMERGE
};

enum Misc
{
    NPC_OURO_TRIGGER            = 15717,
    NPC_OURO                    = 15517,
    NPC_OURO_SPAWNER            = 15957,
    NPC_DIRT_MOUND              = 15712,
    NPC_OURO_SCARAB             = 15718,
    GO_BASE                     = 180795
};

struct boss_ouroAI : public BossAI
{
    boss_ouroAI(Creature* creature) : BossAI(creature, DATA_OURO)
    {
        SetCombatMovement(false);
    }

    void Reset() override
    {
        _Reset();
        _enraged = false;
        summons.DespawnAll();
        DespawnBase();
        std::list<Creature*> adds;
        me->GetCreatureListWithEntryInGrid(adds, NPC_OURO_SCARAB, 250.0f);
        me->GetCreatureListWithEntryInGrid(adds, NPC_OURO_TRIGGER, 250.0f);
        if(!adds.empty())
            for (auto itr : adds)
                itr->DespawnOrUnsummon();
    }

    void JustSummoned(Creature* summon) override
    {
        BossAI::JustSummoned(summon);
        if (summon->GetEntry() == NPC_OURO_TRIGGER)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                summon->GetMotionMaster()->MoveFollow(target, 0.0f, 0.0f);
            else
                summon->GetMotionMaster()->MoveRandom();
        }
    }

    void DespawnBase()
    {
        std::list<GameObject*> goList;
        me->GetGameObjectListWithEntryInGrid(goList, GO_BASE, 250.0f);
        if (!goList.empty())
            for (auto itr : goList)
                itr->Delete();
    }

    void Schedule()
    {
        events.ScheduleEvent(EVENT_SWEEP, urand(5000, 10000), 0, PHASE_FIGHT);
        events.ScheduleEvent(EVENT_SAND_BLAST, urand(20000, 35000), 0, PHASE_FIGHT);
        events.ScheduleEvent(EVENT_SUBMERGE, 90000, 0, PHASE_FIGHT);
        events.ScheduleEvent(EVENT_SUMMON_BASE, 2000, 0, PHASE_FIGHT);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        events.SetPhase(PHASE_FIGHT);
        Schedule();
    }

    void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (me->HealthBelowPctDamaged(20, damage) && !_enraged)
        {
            _enraged = true;
            DoCastSelf(SPELL_BERSERK);
            events.CancelEvent(EVENT_SUBMERGE);
            events.CancelEvent(EVENT_MELEE_CHECK);
            events.ScheduleEvent(EVENT_SUMMON_MOUND, 10000, 0, PHASE_FIGHT);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (events.GetNextEventTime(EVENT_MELEE_CHECK) && me->IsWithinMeleeRange(me->GetVictim()) && me->IsWithinLOSInMap(me->GetVictim()))
            events.CancelEvent(EVENT_MELEE_CHECK);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SWEEP:
                    DoCastSelf(SPELL_SWEEP);
                    events.Repeat(urand(15000, 30000));
                    break;
                case EVENT_SAND_BLAST:
                    DoCastVictim(SPELL_SANDBLAST);
                    events.Repeat(urand(20000, 35000));
                    break;
                case EVENT_SUBMERGE:
                    events.SetPhase(PHASE_SUBMERGE);
                    DespawnBase();
                    DoCastSelf(SPELL_SUBMERGE_VISUAL);
                    DoCastSelf(SPELL_SUMMON_OURO_MOUNDS, true);
                    DoCastSelf(SPELL_SUMMON_TRIGGER, true);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    events.ScheduleEvent(EVENT_EMERGE, 30000, 0, PHASE_SUBMERGE);
                    break;
                case EVENT_EMERGE:
                    events.SetPhase(PHASE_FIGHT);
                    Schedule();
                    if (Creature* trigger = me->FindNearestCreature(NPC_OURO_TRIGGER, 250.0f))
                        me->NearTeleportTo(trigger->GetPositionX(), trigger->GetPositionY(), trigger->GetPositionZ(), false);
                    DoCastSelf(SPELL_BIRTH);
                    DoCastAOE(SPELL_GROUND_RUPTURE);
                    me->RemoveAurasDueToSpell(SPELL_SUBMERGE_VISUAL);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    events.ScheduleEvent(EVENT_SUBMERGE, 90000, 0, PHASE_FIGHT);
                    break;
                case EVENT_SUMMON_BASE:
                    DoCastSelf(SPELL_SUMMON_BASE, true);
                    break;
                case EVENT_SUMMON_MOUND:
                    DoCastSelf(SPELL_SUMMON_OURO_MOUND);
                    events.Repeat(10000);
                    break;
                case EVENT_MELEE_CHECK:
                    if (!me->SelectNearestPlayer(MELEE_RANGE))
                        events.RescheduleEvent(EVENT_SUBMERGE, 0, 0, PHASE_FIGHT);
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        _DoMeleeAttackIfReady();
    }

private:
    bool _enraged;
    void _DoMeleeAttackIfReady()
    {
        if (me->HasUnitState(UNIT_STATE_CASTING) || !me->isAttackReady() || events.IsInPhase(PHASE_SUBMERGE))
            return;

        if (Unit* victim = me->GetVictim())
        {
            if (!me->IsWithinMeleeRange(victim) || !me->IsWithinLOSInMap(victim))
            {
                if (Unit* target = me->SelectNearestPlayer(MELEE_RANGE))
                {
                    AttackStart(target);
                    me->AttackerStateUpdate(target);
                }
                else
                {
                    if (!events.GetNextEventTime(EVENT_MELEE_CHECK) && !_enraged)
                        events.ScheduleEvent(EVENT_MELEE_CHECK, 10000, 0, PHASE_FIGHT);
                    else if (_enraged)
                    {
                        if (Unit* target = SelectTargetFromPlayerList(100.0f))
                            DoCast(target, SPELL_BOULDER);
                    }
                }
            }
            else
                me->AttackerStateUpdate(victim);

            me->resetAttackTimer();
        }
    }
};

enum Spawner
{
    EVENT_CHECK = 1
};

struct npc_ouro_spawnerAI : public ScriptedAI
{
    npc_ouro_spawnerAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
        _summoned = false;
        _events.ScheduleEvent(EVENT_CHECK, 2000);
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_OURO)
        {
            summon->CastSpell(summon, SPELL_BIRTH);
            me->DespawnOrUnsummon();
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        if (_events.ExecuteEvent() == EVENT_CHECK)
        {
            if (_summoned)
                return;

            if (me->SelectNearestPlayer(2.0f))
            {
                _summoned = true;
                DoCastAOE(SPELL_SUMMON_OURO, true);
            }
            else
                _events.Repeat(2000);
        }
    }

private:
    bool _summoned;
    EventMap _events;
};

enum DirtMound
{
    EVENT_DESPAWN       = 1,
    EVENT_CHANGE_TARGET
};

struct npc_dirt_moundAI : public ScriptedAI
{
    npc_dirt_moundAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        DoCastSelf(SPELL_DIRTMOUND_PASSIVE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
        _events.ScheduleEvent(EVENT_DESPAWN, 30000);
        _events.ScheduleEvent(EVENT_CHANGE_TARGET, 0);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_DESPAWN:
                    DoCastAOE(SPELL_SUMMON_SCARABS, true);
                    me->DespawnOrUnsummon();
                    break;
                case EVENT_CHANGE_TARGET:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f))
                        AttackStart(target);
                    else
                        me->GetMotionMaster()->MoveRandom();
                    _events.Repeat(urand(0, 10000));
                    break;
                default:
                    break;
            }
        }
    }

private:
    EventMap _events;
};

void AddSC_boss_ouro()
{
    new CreatureAILoader<boss_ouroAI>("boss_ouro");
    new CreatureAILoader<npc_ouro_spawnerAI>("npc_ouro_spawner");
    new CreatureAILoader<npc_dirt_moundAI>("npc_dirt_mound");
}
