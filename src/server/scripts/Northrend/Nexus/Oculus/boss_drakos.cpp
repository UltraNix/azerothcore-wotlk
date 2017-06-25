#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "oculus.h"

enum Spells
{
    SPELL_MAGIC_PULL                    = 51336,
    SPELL_THUNDERING_STOMP              = 50774,

    SPELL_UNSTABLE_SPHERE_PASSIVE       = 50756,
    SPELL_UNSTABLE_SPHERE_PULSE         = 50757,
    SPELL_UNSTABLE_SPHERE_TIMER         = 50758,
    SPELL_TELEPORT_VISUAL               = 52096,
};

enum DrakosNPCs
{
    NPC_UNSTABLE_SPHERE                 = 28166,
};

enum Events
{
    EVENT_MAGIC_PULL                    = 1,
    EVENT_THUNDERING_STOMP,
    EVENT_SUMMON,
    EVENT_SUMMON_x4
};

enum Yells
{
    SAY_AGGRO,
    SAY_KILL,
    SAY_DEATH,
    SAY_PULL,
    SAY_STOMP,
    EMOTE_MAGIC_PULL
};

struct boss_drakosAI : public BossAI
{
    boss_drakosAI(Creature* creature) : BossAI(creature, DATA_DRAKOS) {}

    void EnterCombat(Unit* /*who*/) override
    {
        Talk(SAY_AGGRO);
        _EnterCombat();
        events.ScheduleEvent(EVENT_MAGIC_PULL, urand(10000,15000));
        events.ScheduleEvent(EVENT_SUMMON, 2000);
    }

    void JustDied(Unit* killer) override
    {
        Talk(SAY_DEATH);
        _JustDied();
        instance->SetData(DATA_DRAKOS, DONE);
        for (uint8 i = 0; i<3; ++i)
            if (uint64 guid = instance->GetData64(DATA_DCD_1 + i))
                if (GameObject* go = ObjectAccessor::GetGameObject(*me, guid))
                    if (go->GetGoState() != GO_STATE_ACTIVE)
                    {
                        go->SetLootState(GO_READY);
                        go->UseDoorOrButton(0, false);
                    }
    }

    void KilledUnit(Unit* victim) override
    {
        if(victim->IsPlayer())
            Talk(SAY_KILL);
    }

    void SummonSphere()
    {
        Position position;
        me->GetRandomNearPosition(position, 10.0f);
        me->SummonCreature(NPC_UNSTABLE_SPHERE, position);
    }

    void MoveInLineOfSight(Unit* who) override {}

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_MAGIC_PULL:
                Talk(SAY_PULL);
                Talk(EMOTE_MAGIC_PULL);
                DoCastSelf(SPELL_MAGIC_PULL);
                events.Repeat(urand(15000, 25000));
                events.ScheduleEvent(EVENT_SUMMON_x4, 1500);
                events.ScheduleEvent(EVENT_THUNDERING_STOMP, urand(2000, 2750));
                break;
            case EVENT_THUNDERING_STOMP:
                Talk(SAY_STOMP);
                DoCastSelf(SPELL_THUNDERING_STOMP);
                break;
            case EVENT_SUMMON:
                for (uint8 i = 0; i<2; ++i)
                    SummonSphere();
                events.Repeat(2000);
                break;
            case EVENT_SUMMON_x4:
                for (uint8 i = 0; i<4; ++i)
                    SummonSphere();
                break;
            default:
                break;
        }
    }
};

enum Sphere
{
    EVENT_PERIODIC_PULSE = 1,
    EVENT_TELEPORT_VISUAL
};

struct npc_oculus_unstable_sphereAI : public ScriptedAI
{
    npc_oculus_unstable_sphereAI(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        DoCastSelf(SPELL_TELEPORT_VISUAL);
        me->SetReactState(REACT_PASSIVE);
        me->GetMotionMaster()->MoveRandom(40.0f);

        me->AddAura(SPELL_UNSTABLE_SPHERE_PASSIVE, me);
        me->AddAura(SPELL_UNSTABLE_SPHERE_TIMER, me);

        _events.ScheduleEvent(EVENT_PERIODIC_PULSE, 3000);
        _events.ScheduleEvent(EVENT_TELEPORT_VISUAL, 100);

        me->DespawnOrUnsummon(18000);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_PERIODIC_PULSE:
                    DoCastAOE(SPELL_UNSTABLE_SPHERE_PULSE);
                    _events.Repeat(3000);
                    break;
                case EVENT_TELEPORT_VISUAL:
                    DoCastSelf(SPELL_TELEPORT_VISUAL);
                    break;
                default:
                    break;
            }
        }
    }

private:
    EventMap _events;
};

void AddSC_boss_drakos()
{
    new CreatureAILoader<boss_drakosAI>("boss_drakos");
    new CreatureAILoader<npc_oculus_unstable_sphereAI>("npc_oculus_unstable_sphere");
}
