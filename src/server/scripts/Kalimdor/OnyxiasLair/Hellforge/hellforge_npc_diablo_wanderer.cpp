#include "ScriptedCreature.h"

enum DiabloWandererData
{
    NPC_SOUL_STONE              = 262001,
    NPC_WORLD_TRIGGER           = 22515,

    SPELL_BLOOD_ORB_VISUAL      = 72100,
    SPELL_WELL_OF_SOULS_VISUAL  = 68855,
    SPELL_HUGE_EXPLOSION        = 74550,
    SPELL_DRAIN_SOUL_VISUAL     = 60857,
};

struct npc_hellforge_diablo_wandererAI : public ScriptedAI
{
public:
    npc_hellforge_diablo_wandererAI(Creature* creature) : ScriptedAI(creature), _summons(me), _eventStarted(false), _soulstoneGUID(0) { }

    void Reset() override
    {
        // Diablo may be not created here, so delay changing his phase a bit
        _scheduler.Schedule(100ms, [&](TaskContext /*func*/)
        {
            if (InstanceScript * instance = me->GetInstanceScript())
            {
                if (Creature * diablo = instance->GetCreature(1))
                    diablo->SetPhaseMask(2, true);
            }
        });
        _summons.DespawnAll();
        _eventStarted = false;
        DoCastSelf(SPELL_WELL_OF_SOULS_VISUAL);
        me->SetImmuneToNPC(false);
        me->SetImmuneToPC(true);
        Position pos;
        me->GetNearPosition(pos, 5.f, 0.f);
        pos.RelocateOffset({ 0.f, 0.f, 10.f });
        if (Creature * soulstone = me->SummonCreature(NPC_SOUL_STONE, pos))
        {
            soulstone->SetImmuneToPC(true);
            soulstone->setFaction(250);
            me->CastSpell(soulstone, SPELL_DRAIN_SOUL_VISUAL);
            _soulstoneGUID = soulstone->GetGUID();
        }
    }


    void MoveInLineOfSight(Unit* who) override
    {
        if (_eventStarted || !who || !who->IsPlayer() || who->ToPlayer()->IsGameMaster() || !me->IsWithinDistInMap(who, 20.f))
            return;
        if (Creature * soulstone = ObjectAccessor::GetCreature(*me, _soulstoneGUID))
            if (soulstone->IsAIEnabled)
                soulstone->GetAI()->DoAction(1);

        _scheduler.Schedule(1s, [&](TaskContext func)
        {
            switch (func.GetRepeatCounter())
            {
                case 0:
                {
                    me->MonsterYell("Ahh... you again. I must thank you for receiving my soul stone. Now, I can become... myself...", LANG_UNIVERSAL, me);
                    func.Repeat(5s);
                    break;
                }
                case 1:
                {
                    me->MonsterYell("Now, cover before my true form!", LANG_UNIVERSAL, me);
                    break;
                }
            }
        });

        _eventStarted = true;
    }
    
    void JustDied(Unit* /*killer*/)
    {
        _summons.DespawnAll();
    }
    
    void JustSummoned(Creature* creature)
    {
        _summons.Summon(creature);
    }

    void EnterEvadeMode() override
    {
        _summons.DespawnAll();
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

    void DoAction(int32 param) override
    {
        if (param == 1)
        {
            if (Creature * soulstone = ObjectAccessor::GetCreature(*me, _soulstoneGUID))
            {
                if (Creature * trigger = me->SummonCreature(NPC_WORLD_TRIGGER, me->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 10000))
                {
                    trigger->CastSpell(soulstone, SPELL_HUGE_EXPLOSION);
                }
                soulstone->DespawnOrUnsummon();
            }

            _scheduler.Schedule(800ms, [&](TaskContext /*func*/)
            {
                if (InstanceScript * instance = me->GetInstanceScript())
                {
                    if (Creature * diablo = instance->GetCreature(1))
                    {
                        diablo->SetPhaseMask(1, true);
                        diablo->SetUInt32Value(UNIT_NPC_EMOTESTATE, 434);
                        diablo->AI()->DoAction(1);
                    }
                    me->SetPhaseMask(2, true);
                    me->DespawnOrUnsummon(3s);
                    me->SetRespawnTime(7 * DAY);
                }
            });

            _scheduler.Schedule(1800ms, [&](TaskContext /*func*/)
            {
                if (InstanceScript * instance = me->GetInstanceScript())
                {
                    if (Creature * diablo = instance->GetCreature(1))
                        diablo->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                }
            });
        }
    }

private:
    SummonList _summons;
    bool _eventStarted;
    uint64 _soulstoneGUID;
    TaskScheduler _scheduler;
};

struct npc_hellforge_diablo_wanderer_soulstoneAI : NullCreatureAI
{
    npc_hellforge_diablo_wanderer_soulstoneAI(Creature* creature) : NullCreatureAI(creature){ }
    void DoAction(int32 param) override
    {
        if (param == 1)
        {
            if (Unit * wanderer = me->GetSummoner())
            {
                Position pos;
                wanderer->GetNearPosition(pos, 1.f, 0.f);
                pos.RelocateOffset({ 0.f,0.f, 1.f });
                me->GetMotionMaster()->MovePoint(1, pos);
            }
        }
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == POINT_MOTION_TYPE && id == 1)
        {
            if (Unit * wanderer = me->GetSummoner())
                if (wanderer->IsAIEnabled)
                    wanderer->GetAI()->DoAction(1);
        }
    }

};

void AddSC_hellforge_boss_diablo_wanderer()
{
    new CreatureAILoader<npc_hellforge_diablo_wandererAI>("npc_hellforge_diablo_wanderer");
    new CreatureAILoader<npc_hellforge_diablo_wanderer_soulstoneAI>("npc_hellforge_diablo_wanderer_soulstone");
}
