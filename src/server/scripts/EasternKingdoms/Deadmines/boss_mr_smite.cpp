#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "deadmines.h"
#include "GameObjectAI.h"

enum SmiteSays
{
    SAY_CANNON_EVENT,
    SAY_CANNON_EVENT_1,
    SAY_SWAP1,
    SAY_SWAP2
};

enum SmiteSpells
{
    // Mr Smite
    SPELL_SMITE_STOMP       = 6432,
    SPELL_SMITE_SLAM        = 6435,
    SPELL_SMITE_DUAL_WIELD  = 6440,
    SPELL_SMITE_HAMMER      = 6436,
    SPELL_NIMBLE_REFLEXES   = 6433,
    SPELL_THRASH            = 3417,

    // Cannon Event
    SPELL_FIRE_CANNON       = 6250
};

enum SmiteMisc
{
    // Mr Smite
    EQUIP_TWO_AXES          = 2183,
    EQUIP_MACE              = 10756,

    DATA_RUN_DOWN           = 1,
    POINT_AGGRO             = 1,

    // Cannon Event
    SUMMON_GROUP_CANNON     = 1
};

struct boss_mr_smiteAI : public BossAI
{
    boss_mr_smiteAI(Creature* creature) : BossAI(creature, BOSS_MR_SMITE) 
    { 
        _run = false;
    }

    void Reset() override
    {
        _phase = 0;
        _Reset();
        SetEquipmentSlots(true);
        me->SetCanDualWield(false);
        me->SetStandState(UNIT_STAND_STATE_STAND);
        me->SetReactState(REACT_AGGRESSIVE);
        DoCastSelf(SPELL_NIMBLE_REFLEXES, true);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*damageSchoolMask*/) override
    {
        if ((_phase == 0 && me->HealthBelowPctDamaged(66, damage)) || (_phase == 1 && me->HealthBelowPctDamaged(33, damage)))
        {
            me->SetTarget(0);
            me->RemoveAurasDueToSpell(SPELL_NIMBLE_REFLEXES);
            me->RemoveAurasDueToSpell(SPELL_THRASH);
            DoCastSelf(SPELL_SMITE_STOMP);
            scheduler.DelayAll(10s);
            uint8 tempPhase = _phase;
            scheduler.Schedule(1s, [this, tempPhase](TaskContext task) 
            {
                Talk(tempPhase == 0 ? SAY_SWAP1 : SAY_SWAP2);
                scheduler.Schedule(1500ms, [this, tempPhase](TaskContext task) 
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MovePoint(tempPhase == 0 ? EQUIP_TWO_AXES : EQUIP_MACE, 1.859f, -780.72f, 9.831f);
                });
            });
            me->StopMoving();
            me->AttackStop();
            me->SetReactState(REACT_PASSIVE);
            ++_phase;
        }
    }

    void SetData(uint32 field, uint32 data) override
    {
        if (!_run && field == DATA_RUN_DOWN && data == 1)
        {
            Position pos = { -2.501920f, -781.920959f, 9.943743f, 1.247590f };
            _run = true;
            me->GetMotionMaster()->MovePoint(POINT_AGGRO, pos);
            me->SetHomePosition(pos);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff,
            std::bind(&BossAI::DoMeleeAttackIfReady, this));
    }

    void MovementInform(uint32 type, uint32 point) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        if (point == POINT_AGGRO)
        {
            DoZoneInCombat();
            return;
        }

        me->SetFacingTo(5.558f);

        scheduler.Schedule(1500ms, [this, point](TaskContext task) 
        {
            if (point == EQUIP_TWO_AXES)
            {
                SetEquipmentSlots(false, EQUIP_TWO_AXES, EQUIP_TWO_AXES);
                me->SetCanDualWield(true);
                DoCastSelf(SPELL_SMITE_DUAL_WIELD);
            }
            else if (point == EQUIP_MACE)
            {
                SetEquipmentSlots(false, EQUIP_MACE, EQUIP_UNEQUIP);
                me->SetCanDualWield(false);
                DoCastSelf(SPELL_SMITE_HAMMER);
                me->RemoveAurasDueToSpell(SPELL_SMITE_DUAL_WIELD);
            }
        });

        scheduler.Schedule(3s, [this](TaskContext task) 
        {
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetStandState(UNIT_STAND_STATE_STAND);
            if (me->GetVictim())
            {
                me->GetMotionMaster()->MoveChase(me->GetVictim());
                me->SetTarget(me->GetVictim()->GetGUID());
            }
            if (_phase == 1)
                DoCastSelf(SPELL_THRASH);
            else if (_phase == 2)
            {
                scheduler.Schedule(3s, [this](TaskContext task) 
                {
                    DoCastVictim(SPELL_SMITE_SLAM);
                    task.Repeat(15s);
                });
            }
        });

        me->SetStandState(UNIT_STAND_STATE_KNEEL);
    }

    private:
        bool _run;
        uint8 _phase;
};

struct go_deadmines_defias_cannonAI : public GameObjectAI
{
    public:
        go_deadmines_defias_cannonAI(GameObject* go) : GameObjectAI(go) { }

        void SpellHit(Unit* /*unit*/, const SpellInfo* spellInfo) override
        {
            if (spellInfo->Id == SPELL_FIRE_CANNON)
            {
                if (InstanceScript* instance = go->GetInstanceScript())
                {
                    if (GameObject* door = instance->GetGameObject(DATA_IRON_CLAD_DOOR))
                    {
                        if (instance->GetData(DATA_CANNON_EVENT))
                            return;

                        go->SendCustomAnim(0);
                        _scheduler.Schedule(1s, [this, door, instance](TaskContext /*task*/) 
                        {
                            instance->SetData(DATA_CANNON_EVENT, true);
                            door->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                            go->SummonCreatureGroup(SUMMON_GROUP_CANNON);
                        });
                        if (Creature* smite = instance->GetCreature(BOSS_MR_SMITE))
                        {
                            if (smite->IsAIEnabled)
                                smite->AI()->Talk(SAY_CANNON_EVENT);

                            _scheduler.Schedule(10s, [smite](TaskContext /*task*/) 
                            {
                                if (smite->IsAIEnabled)
                                    smite->AI()->Talk(SAY_CANNON_EVENT_1);
                            });
                        }
                    }
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _scheduler.Update(diff);
        }

    private:
        TaskScheduler _scheduler;
};

void AddSC_boss_mr_smite()
{
    new CreatureAILoader<boss_mr_smiteAI>("boss_mr_smite");
    new GameObjectAILoader<go_deadmines_defias_cannonAI>("go_deadmines_defias_cannon");
}
