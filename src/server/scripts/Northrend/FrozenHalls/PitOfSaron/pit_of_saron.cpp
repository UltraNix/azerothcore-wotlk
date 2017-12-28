#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SmartAI.h"
#include "pit_of_saron.h"
#include "PassiveAI.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"
#include "Player.h"
#include "CreatureGroups.h"
#include "MapManager.h"

enum POSLeader
{
    SPELL_STRANGULATE = 69413,
    SPELL_NECROMANTIC_POWER = 69753,
    SPELL_RAISE_DEAD = 69350,
    SPELL_EMPOWERED_BLIZZARD = 70132,
    SPELL_SHRIEK_OF_THE_HIGHBORNE = 59514,
    SPELL_MULTI_SHOT = 70513,
    SPELL_ICE_LANCE_VOLLEY = 70464
};

struct npc_pos_leaderAI : public NullCreatureAI
{
    npc_pos_leaderAI(Creature* creature) : NullCreatureAI(creature), _summons(me)
    {
        _instance = me->GetInstanceScript();
    }

    void Reset() override
    {
        _counter = 0;
        _events.Reset();
        _summons.DespawnAll();
        me->SetVisible(true);

        if (_instance)
            if (_instance->GetData(DATA_INSTANCE_PROGRESS) == INSTANCE_PROGRESS_NONE)
                me->SetVisible(false);
    }

    void SetData(uint32 type, uint32 /*data*/) override
    {
        if (type == DATA_START_INTRO && _instance->GetData(DATA_INSTANCE_PROGRESS) == INSTANCE_PROGRESS_NONE && _counter == 0 && !me->IsVisible())
        {
            me->setActive(true);
            _events.RescheduleEvent(1, 0s);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        if (!_instance)
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
            case 1:
            {
                if (_counter == 0)
                {
                    me->SetVisible(true);
                    me->GetMotionMaster()->MovePoint(1, LeaderIntroPos);
                }

                uint8 idx = 0;
                idx = (_instance->GetData(DATA_TEAMID_IN_INSTANCE) == TEAM_ALLIANCE ? 0 : 1);
                if (introPositions[_counter].entry[idx] != 0)
                {
                    if (Creature* summon = me->SummonCreature(introPositions[_counter].entry[idx], PortalPos))
                    {
                        summon->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        summon->SetSpeed(MOVE_RUN, 0.8f);
                        summon->GetMotionMaster()->MovePoint(1, introPositions[_counter].endPosition);
                        summon->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
                    }

                    ++_counter;
                    _events.Repeat(150ms);
                }
                else
                    _events.RescheduleEvent(2, 2.5s);
            }
            break;
            case 2:
                if (Creature* tyrannus = _instance->GetCreature(DATA_TYRANNUS_EVENT_GUID))
                {
                    tyrannus->setActive(true);
                    if (tyrannus->IsAIEnabled)
                        tyrannus->AI()->Talk(SAY_TYRANNUS_INTRO_1);
                }
                _events.RescheduleEvent(3, 7s);
                break;
            case 3:
                if (Creature* tyrannus = _instance->GetCreature(DATA_TYRANNUS_EVENT_GUID))
                    if (tyrannus->IsAIEnabled)
                        tyrannus->AI()->Talk(SAY_TYRANNUS_INTRO_2);
                _events.RescheduleEvent(4, 14s);
                break;
            case 4:
            {
                Creature* necrolyteFirst = _instance->instance->GetCreature(_instance->GetData64(DATA_NECROLYTE_1_GUID));
                Creature* necrolyteSecond = _instance->instance->GetCreature(_instance->GetData64(DATA_NECROLYTE_2_GUID));
                if (necrolyteFirst && necrolyteSecond)
                {
                    if (!necrolyteFirst->IsInCombat() && necrolyteFirst->IsAlive())
                    {
                        necrolyteFirst->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        necrolyteFirst->GetMotionMaster()->MovePoint(1, NecrolytePos1);
                        necrolyteFirst->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
                    }
                    if (!necrolyteSecond->IsInCombat() && necrolyteSecond->IsAlive())
                    {
                        necrolyteSecond->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        necrolyteSecond->GetMotionMaster()->MovePoint(1, NecrolytePos2);
                        necrolyteSecond->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
                    }

                    necrolyteFirst->RemoveAura(SPELL_NECROLYTE_CHANNELING);
                    necrolyteSecond->RemoveAura(SPELL_NECROLYTE_CHANNELING);

                    for (SummonList::iterator itr = _summons.begin(); itr != _summons.end(); ++itr)
                        if (Creature* summon = _instance->instance->GetCreature(*itr))
                        {
                            if (summon->GetPositionX() < 440.0f)
                                continue;
                            if (summon->GetPositionY() > 215.0f)
                                summon->GetMotionMaster()->MoveChase(necrolyteSecond, 0.0f, Position::RandomOrientation());
                            else
                                summon->GetMotionMaster()->MoveChase(necrolyteFirst, 0.0f, Position::RandomOrientation());
                        }
                }

                _events.RescheduleEvent(5, 1ms);
                break;
            }
            case 5:
                Talk(me->GetEntry() == NPC_JAINA_PART1 ? SAY_JAINA_INTRO_1 : SAY_SYLVANAS_INTRO_1);
                _events.RescheduleEvent(6, 1s);
                break;
            case 6:
                if (Creature* tyrannus = _instance->GetCreature(DATA_TYRANNUS_EVENT_GUID))
                    if (tyrannus->IsAIEnabled)
                        tyrannus->AI()->Talk(SAY_TYRANNUS_INTRO_3);
                _events.RescheduleEvent(7, 5s);
                break;
            case 7:
                if (Creature* necrolyteFirst = _instance->instance->GetCreature(_instance->GetData64(DATA_NECROLYTE_1_GUID)))
                    if (necrolyteFirst->IsAIEnabled)
                        necrolyteFirst->AI()->DoAction(1337); // remove invincibility
                if (Creature* necrolyteSecond = _instance->instance->GetCreature(_instance->GetData64(DATA_NECROLYTE_2_GUID)))
                    if (necrolyteSecond->IsAIEnabled)
                        necrolyteSecond->AI()->DoAction(1337); // remove invincibility

                for (SummonList::iterator itr = _summons.begin(); itr != _summons.end(); ++itr)
                    if (Creature* summon = _instance->instance->GetCreature(*itr))
                    {
                        if (summon->GetPositionX() < 450.0f)
                            continue;
                        summon->AddUnitState(UNIT_STATE_NO_ENVIRONMENT_UPD);
                        summon->GetMotionMaster()->Clear(false);
                        summon->GetMotionMaster()->MoveIdle();
                        summon->StopMoving();
                        summon->CastSpell(summon, SPELL_STRANGULATE, true);
                        summon->SetCanFly(true);
                        summon->SetDisableGravity(true);
                        summon->SetHover(true);
                        summon->SendMovementFlagUpdate();
                        float dist = frand(0.0f, 2.0f);
                        float angle = Position::RandomOrientation();
                        summon->GetMotionMaster()->MoveTakeoff(0, summon->GetPositionX() + dist*cos(angle), summon->GetPositionY() + dist*sin(angle), summon->GetPositionZ() + 6.0f + frand(0.0f, 4.0f), 1.5f + frand(0.0f, 1.5f));
                    }
                _events.RescheduleEvent(8, 7s);
                break;
            case 8:
                if (Creature* tyrannus = _instance->GetCreature(DATA_TYRANNUS_EVENT_GUID))
                    tyrannus->CastSpell(tyrannus, SPELL_NECROMANTIC_POWER, false);
                _events.RescheduleEvent(9, 0.4s);
                break;
            case 9:
                for (SummonList::iterator itr = _summons.begin(); itr != _summons.end(); ++itr)
                    if (Creature* summon = _instance->instance->GetCreature(*itr))
                    {
                        if (summon->GetPositionX() < 450.0f)
                            continue;
                        Unit::Kill(summon, summon);
                        summon->RemoveAllAuras();
                        summon->GetMotionMaster()->MoveFall(0, true);
                    }
                _events.RescheduleEvent(10, 1s);
                break;
            case 10:
                Talk(me->GetEntry() == NPC_JAINA_PART1 ? SAY_JAINA_INTRO_2 : SAY_SYLVANAS_INTRO_2);
                _events.PopEvent();
                _events.RescheduleEvent(11, 1s);
                break;
            case 11:
                for (SummonList::iterator itr = _summons.begin(); itr != _summons.end(); ++itr)
                    if (Creature* summon = _instance->instance->GetCreature(*itr))
                    {
                        if (summon->GetPositionX() < 450.0f)
                            continue;
                        summon->SetCanFly(false);
                        summon->SetDisableGravity(false);
                        summon->SetHover(false);
                        summon->SendMovementFlagUpdate();
                        summon->CastSpell(summon, SPELL_RAISE_DEAD, true);
                    }

                _events.RescheduleEvent(12, 2s);
                break;
            case 12:
                if (Creature* tyrannus = _instance->GetCreature(DATA_TYRANNUS_EVENT_GUID))
                    if (tyrannus->IsAIEnabled)
                        tyrannus->AI()->Talk(SAY_TYRANNUS_INTRO_4);

                for (SummonList::iterator itr = _summons.begin(); itr != _summons.end(); ++itr)
                    if (Creature* summon = _instance->instance->GetCreature(*itr))
                    {
                        if (summon->GetPositionX() < 450.0f)
                            continue;
                        summon->SetHomePosition(summon->GetPositionX(), summon->GetPositionY(), summon->GetPositionZ(), summon->GetOrientation());
                        summon->Respawn(true);
                        summon->UpdateEntry(36796, 0, false);
                        summon->SetFacingTo(M_PI);
                        summon->SetReactState(REACT_PASSIVE);
                    }

                _events.RescheduleEvent(13, 3s);
                break;
            case 13:
                for (SummonList::iterator itr = _summons.begin(); itr != _summons.end(); ++itr)
                    if (Creature* summon = _instance->instance->GetCreature(*itr))
                    {
                        if (summon->GetPositionX() < 450.0f)
                            continue;
                        summon->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        float dist = urand(0.0f, 1.0f);
                        float angle = Position::RandomOrientation();
                        summon->SetSpeed(MOVE_RUN, 0.8f);
                        summon->SetInCombatWithZone();
                        summon->GetMotionMaster()->MoveChase(me, dist, angle);
                        summon->SetHomePosition(me->GetPositionX() + dist*cos(angle), me->GetPositionY() + dist*sin(angle), me->GetPositionZ(), 0.0f);
                    }

                _events.RescheduleEvent(14, 2s);
                break;
            case 14:
                if (me->GetEntry() == NPC_JAINA_PART1)
                {
                    Talk(SAY_JAINA_INTRO_3);
                    DoCastSelf(SPELL_EMPOWERED_BLIZZARD);
                }
                else
                {
                    DoCastSelf(SPELL_SHRIEK_OF_THE_HIGHBORNE);
                    for (auto itr : { DATA_GUARD_1_GUID, DATA_GUARD_2_GUID })
                        if (Creature* guard = _instance->GetCreature(itr))
                            guard->CastSpell(guard, SPELL_MULTI_SHOT, false);
                }

                _events.RescheduleEvent(15, 2s);
                break;
            case 15:
                if (Creature* tyrannus = _instance->GetCreature(DATA_TYRANNUS_EVENT_GUID))
                    tyrannus->GetMotionMaster()->MovePoint(0, SBSTyrannusStartPos);

                if (me->GetEntry() == NPC_JAINA_PART1)
                {
                    for (auto itr : { DATA_GUARD_1_GUID, DATA_GUARD_2_GUID })
                        if (Creature* guard = _instance->GetCreature(itr))
                            guard->CastSpell(guard, SPELL_ICE_LANCE_VOLLEY, false);
                }

                _events.RescheduleEvent(16, 3s);
                break;
            case 16:
                Talk(me->GetEntry() == NPC_JAINA_PART1 ? SAY_JAINA_INTRO_4 : SAY_SYLVANAS_INTRO_3);
                for (auto itr : { DATA_GUARD_1_GUID, DATA_GUARD_2_GUID })
                    if (Creature* guard = _instance->GetCreature(itr))
                        guard->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);

                for (SummonList::iterator itr = _summons.begin(); itr != _summons.end(); ++itr)
                    if (Creature* summon = _instance->instance->GetCreature(*itr))
                    {
                        if (summon->IsAlive())
                        {
                            if (summon->GetEntry() == NPC_KALIRA || summon->GetEntry() == NPC_ELANDRA || summon->GetEntry() == NPC_LORALEN || summon->GetEntry() == NPC_KORELN)
                                continue;

                            Unit::Kill(summon, summon, false);
                        }
                        summon->DespawnOrUnsummon(10s);
                    }
                _instance->SetData(DATA_INSTANCE_PROGRESS, INSTANCE_PROGRESS_FINISHED_INTRO);
                _events.RescheduleEvent(17, 5s);
                break;
            case 17:
                me->setActive(false);
                Talk(me->GetEntry() == NPC_JAINA_PART1 ? SAY_JAINA_INTRO_5 : SAY_SYLVANAS_INTRO_4);
                break;
            }
        }

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        _summons.Despawn(summon);
    }

    void AttackStart(Unit* who) override {}
    void MoveInLineOfSight(Unit* who) override {}

    private:
        EventMap _events;
        SummonList _summons;
        InstanceScript* _instance;
        uint8 _counter;
};

enum DeathwhisperNecrolyte
{
    EVENT_SHADOW_BOLT = 1,
    EVENT_CONVERSION_BEAM = 2,

    SPELL_SHADOW_BOLT = 69577,
    SPELL_CONVERSION_BEAM = 69578
};

struct npc_pos_deathwhisper_necrolyteAI : public ScriptedAI
{
    npc_pos_deathwhisper_necrolyteAI(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
        _immortal = false;
    }

    void Reset() override
    {
        _events.Reset();
    }

    void InitializeAI() override
    {
        if (_instance && _instance->GetData(DATA_INSTANCE_PROGRESS) == INSTANCE_PROGRESS_NONE)
        {
            if (me->GetPositionX() > 490.0f && me->GetPositionX() < 504.0f && me->GetPositionY() > 192.0f && me->GetPositionY() < 206.0f ||
                me->GetPositionX() > 490.0f && me->GetPositionX() < 504.0f && me->GetPositionY() > 240.0f && me->GetPositionY() < 254.0f)
            {
                _immortal = true;
                DoCastSelf(SPELL_NECROLYTE_CHANNELING);

                if (me->GetPositionY() < 206.0f)
                    _instance->SetData64(DATA_NECROLYTE_1_GUID, me->GetGUID());
                else
                    _instance->SetData64(DATA_NECROLYTE_2_GUID, me->GetGUID());
            }
        }

        ScriptedAI::InitializeAI();
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == POINT_MOTION_TYPE && id == 1)
            me->SetFacingTo(M_PI);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        me->RemoveAura(SPELL_NECROLYTE_CHANNELING);
        _events.Reset();
        _events.RescheduleEvent(EVENT_SHADOW_BOLT, 0s);
        _events.RescheduleEvent(EVENT_CONVERSION_BEAM, 5s, 9s);

        if (Creature* leader = _instance->GetCreature(DATA_LEADER_FIRST_GUID))
            if (leader->IsAIEnabled)
                leader->AI()->SetData(DATA_START_INTRO, 0);
    }

    void DamageTaken(Unit* /*doneBy*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (_immortal && damage >= me->GetHealth())
            damage = me->GetHealth() - 1;
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == 1337)
            _immortal = false;
    }

    void UpdateAI(uint32 diff) override
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
                case EVENT_SHADOW_BOLT: // Shadow Bolt
                    DoCastVictim(SPELL_SHADOW_BOLT);
                    _events.Repeat(4s);
                    break;
                case EVENT_CONVERSION_BEAM: // Conversion Beam
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                        DoCast(target, SPELL_CONVERSION_BEAM);
                    _events.Repeat(20s, 25s);
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    void MoveInLineOfSight(Unit* /*who*/) override {}

    private:
        EventMap _events;
        InstanceScript* _instance;
        bool _immortal;
};

struct npc_pos_after_first_bossAI : public NullCreatureAI
{
    npc_pos_after_first_bossAI(Creature* creature) : NullCreatureAI(creature)
    {
        _instance = me->GetInstanceScript();
        me->GetMotionMaster()->MovePoint(1, 695.03f, -149.86f, 527.89f);
    }

    void Reset() override
    {
        _events.Reset();
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        if (id == 1)
            _events.RescheduleEvent(id, 0s);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                {
                    if (_instance)
                        if (Creature* garfrost = _instance->GetCreature(DATA_GARFROST))
                        {
                            float angle = garfrost->GetAngle(me);
                            float x = garfrost->GetPositionX() + cos(angle)*12.0f;
                            float y = garfrost->GetPositionY() + sin(angle)*12.0f;
                            me->GetMotionMaster()->MovePoint(2, x, y, garfrost->GetPositionZ());
                        }

                    uint8 i = 0;
                    while (FBSData[i].entry)
                    {
                        if (Creature* creature = me->SummonCreature(FBSData[i].entry, 688.69f + i*1.8f, FBSSpawnPos.GetPositionY() + (float)irand(-2, 2), FBSSpawnPos.GetPositionZ(), 3 * M_PI / 2))
                            creature->GetMotionMaster()->MovePath(FBSData[i].pathId, false);
                        ++i;
                    }
                    _events.RescheduleEvent(2, 3s);
                    break;
                }
                case 2:
                    if (Creature* tyrannusVoice = me->SummonCreature(NPC_TYRANNUS_VOICE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() - 10.0f, me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 1))
                        if (tyrannusVoice->IsAIEnabled)
                            tyrannusVoice->AI()->Talk(SAY_TYRANNUS_GARFROST);
                    _events.RescheduleEvent(3, 4s);
                    break;
                case 3:
                    Talk(SAY_GENERAL_GARFROST);
                    break;
                default:
                    break;
            }
        }
    }

    private:
        EventMap _events;
        InstanceScript* _instance;
};

enum TyrannusEvents
{
    SPELL_SUMMON_UNDEAD = 69516
};

struct npc_pos_tyrannus_eventsAI : public NullCreatureAI
{
    npc_pos_tyrannus_eventsAI(Creature* creature) : NullCreatureAI(creature)
    {
        _instance = me->GetInstanceScript();
        _killsLeft = 0;
        for (int8 i = 0; i < 2; ++i)
            _deathbringerGUIDs.push_back(0);
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == POINT_MOTION_TYPE)
        {
            switch (id)
            {
                case 0:
                    me->setActive(false);
                    break;
                case 1:
                    _events.ScheduleEvent(1, 0s);
                    break;
                case 2:
                    _events.ScheduleEvent(2, 0s);
                    break;
                case 3:
                    _events.ScheduleEvent(4, 0s);
                    break;
                default:
                    break;
            }
        }
        else if (type == EFFECT_MOTION_TYPE && id == 10)
            _events.ScheduleEvent(6, 0s);
    }

    void SetData(uint32 type, uint32 id) override
    {
        if (!me->IsAlive() || _instance->GetBossState(DATA_GARFROST) != DONE || _instance->GetBossState(DATA_ICK) != DONE)
            return;

        if (type == 2)
        {
            if (id == 1)
                if (_killsLeft)
                    --_killsLeft;
            return;
        }

        if (type != 1)
            return;

        switch (id)
        {
            case 1:
                if (_instance->GetData(DATA_INSTANCE_PROGRESS) != INSTANCE_PROGRESS_FINISHED_KRICK_SCENE)
                    return;
                if (me->GetExactDist(&PTSTyrannusWaitPos1) > 3.0f)
                    return;
                _instance->SetData(DATA_INSTANCE_PROGRESS, INSTANCE_PROGRESS_AFTER_WARN_1);
                Talk(SAY_TYRANNUS_AMBUSH_1);
                _killsLeft = 10;
                _events.ScheduleEvent(30, 0s);
                _events.ScheduleEvent(3, 25s);
                break;
            case 2:
                if (_instance->GetData(DATA_INSTANCE_PROGRESS) != INSTANCE_PROGRESS_AFTER_WARN_1)
                    return;
                if (_killsLeft != 0)
                    return;
                _instance->SetData(DATA_INSTANCE_PROGRESS, INSTANCE_PROGRESS_AFTER_WARN_2);
                Talk(SAY_TYRANNUS_AMBUSH_2);
                _killsLeft = (Difficulty(me->GetMap()->GetSpawnMode()) == DUNGEON_DIFFICULTY_HEROIC ? 12 : 6);
                _events.ScheduleEvent(60, 0s);
                _events.ScheduleEvent(5, 20s);
                break;
                break;
            case 3:
                if (_instance->GetData(DATA_INSTANCE_PROGRESS) != INSTANCE_PROGRESS_AFTER_WARN_2)
                    return;
                if (_killsLeft != 0)
                    return;
                _instance->SetData(DATA_INSTANCE_PROGRESS, INSTANCE_PROGRESS_AFTER_TUNNEL_WARN);
                if (Creature* tyrannusVoice = me->SummonCreature(NPC_TYRANNUS_VOICE, 950.16f, -102.17f, 594.90f - 10.0f, 5.43f, TEMPSUMMON_TIMED_DESPAWN, 1))
                    if (tyrannusVoice->IsAIEnabled)
                        tyrannusVoice->AI()->Talk(SAY_TYRANNUS_TRAP_TUNNEL);
                break;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    me->GetMotionMaster()->MovePoint(2, PTSTyrannusWaitPos1, false);
                    break;
                case 2:
                    me->SetFacingTo(PTSTyrannusWaitPos1.GetOrientation());
                    me->setActive(false);
                    break;
                case 3:
                    me->GetMotionMaster()->MovePoint(3, PTSTyrannusWaitPos2, false);
                    break;
                case 4:
                    me->SetFacingTo(PTSTyrannusWaitPos2.GetOrientation());
                    break;
                case 5:
                    me->GetMotionMaster()->MoveTakeoff(10, me->GetPositionX() + 2.0f*cos(me->GetOrientation()), me->GetPositionY() + 2.0f*sin(me->GetOrientation()), me->GetPositionZ() + 30.0f, 7.0f);
                    break;
                case 6:
                    me->GetMotionMaster()->MovePoint(4, PTSTyrannusWaitPos3, false);
                    break;
                case 30:
                {
                    Movement::PointsArray path =
                    {
                        { 950.61f, 50.91f, 567.85f },
                        { 946.48f, 73.25f, 565.89f },
                        { 934.87f, 78.56f, 563.97f },
                        { 915.10f, 75.31f, 553.81f }
                    };
                    if (Creature* deathbringer = me->SummonCreature(NPC_YMIRJAR_DEATHBRINGER, 950.61f, 50.91f, 567.85f, 1.82f))
                    {
                        _deathbringerGUIDs[0] = deathbringer->GetGUID();
                        deathbringer->SetReactState(REACT_PASSIVE);
                        deathbringer->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        deathbringer->SetHomePosition(915.10f, 75.31f, 553.81f, 3.75f);
                        deathbringer->SetWalk(false);
                        deathbringer->GetMotionMaster()->MoveSplinePath(&path);
                    }
                    if (Creature* deathbringer = me->SummonCreature(NPC_YMIRJAR_DEATHBRINGER, 949.05f, 61.18f, 566.60f, 1.73f))
                    {
                        _deathbringerGUIDs[1] = deathbringer->GetGUID();
                        deathbringer->SetReactState(REACT_PASSIVE);
                        deathbringer->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        deathbringer->SetHomePosition(883.15f, 54.6254f, 528.5f, 3.75f);
                        deathbringer->SetWalk(false);
                        path.push_back(G3D::Vector3(883.15f, 54.6254f, 528.5f));
                        deathbringer->GetMotionMaster()->MoveSplinePath(&path);
                    }
                    _events.ScheduleEvent(31, 0.5s);
                    _events.ScheduleEvent(32, 0.5s);
                }
                break;
                case 31:
                    if (Creature* deathbringer = _instance->instance->GetCreature(_deathbringerGUIDs[0]))
                        if (deathbringer->GetMotionMaster()->GetCurrentMovementGeneratorType() != ESCORT_MOTION_TYPE)
                        {
                            deathbringer->CastSpell(deathbringer, SPELL_SUMMON_UNDEAD, false);
                            _events.ScheduleEvent(33, 3s);
                            break;
                        }
                    _events.ScheduleEvent(31, 0.5s);
                    break;
                case 32:
                    if (Creature* deathbringer = _instance->instance->GetCreature(_deathbringerGUIDs[1]))
                        if (deathbringer->GetMotionMaster()->GetCurrentMovementGeneratorType() != ESCORT_MOTION_TYPE)
                        {
                            deathbringer->CastSpell(deathbringer, SPELL_SUMMON_UNDEAD, false);
                            _events.ScheduleEvent(34, 3s);
                            break;
                        }
                    _events.ScheduleEvent(32, 0.5s);
                    break;
                case 33:
                    me->SummonCreature(NPC_YMIRJAR_WRATHBRINGER, 919.733f, 89.0972f, 558.959f, 3.85718f);
                    me->SummonCreature(NPC_YMIRJAR_WRATHBRINGER, 911.936f, 63.3542f, 547.698f, 3.735f);
                    me->SummonCreature(NPC_YMIRJAR_FLAMEBEARER, 909.356f, 83.1684f, 551.717f, 3.57792f);
                    me->SummonCreature(NPC_YMIRJAR_FLAMEBEARER, 920.946f, 69.1667f, 557.594f, 3.1765f);
                    _events.ScheduleEvent(35, 3.5s);
                    break;
                case 34:
                    me->SummonCreature(NPC_YMIRJAR_WRATHBRINGER, 879.464f, 41.1997f, 521.394f, 3.735f);
                    me->SummonCreature(NPC_YMIRJAR_WRATHBRINGER, 885.715f, 65.5156f, 533.631f, 3.85718f);
                    me->SummonCreature(NPC_YMIRJAR_FLAMEBEARER, 876.884f, 61.0139f, 527.715f, 3.57792f);
                    me->SummonCreature(NPC_YMIRJAR_FLAMEBEARER, 889.49f, 45.2865f, 527.233f, 3.97935f);
                    _events.ScheduleEvent(36, 3.5s);
                    break;
                case 35:
                    if (Creature* deathbringer = _instance->instance->GetCreature(_deathbringerGUIDs[0]))
                    {
                        deathbringer->SetReactState(REACT_AGGRESSIVE);
                        deathbringer->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    }
                    break;
                case 36:
                    if (Creature* deathbringer = _instance->instance->GetCreature(_deathbringerGUIDs[1]))
                    {
                        deathbringer->SetReactState(REACT_AGGRESSIVE);
                        deathbringer->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    }
                    break;
                case 60:
                {
                    Position startPos[6] = { { 927.11f, -72.60f, 592.2f, 1.52f },{ 922.92f, -72.64f, 592.3f, 1.52f },{ 930.46f, -72.57f, 592.1f, 1.52f },{ 934.52f, -72.52f, 592.1f, 1.52f },{ 934.57f, -77.66f, 592.20f, 1.52f },{ 927.15f, -77.07f, 592.20f, 1.52f } };
                    Position endPos = { 926.10f, -46.63f, 591.2f, 1.52f };
                    for (uint8 i = 0; i<6; ++i)
                        if (Creature* summon = me->SummonCreature(i < 4 ? NPC_FALLEN_WARRIOR : NPC_WRATHBONE_COLDWRAITH, startPos[i]))
                        {
                            summon->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                            Position finalPos = endPos;
                            summon->MovePosition(finalPos, startPos[i].GetExactDist(&startPos[0]), Position::NormalizeOrientation(startPos[i].GetAngle(&startPos[0]) + 1.52f));

                            Movement::PointsArray path;
                            path.push_back(G3D::Vector3(summon->GetPositionX(), summon->GetPositionY(), summon->GetPositionZ()));
                            path.push_back(G3D::Vector3(finalPos.GetPositionX(), finalPos.GetPositionY(), finalPos.GetPositionZ()));

                            summon->SetHomePosition(finalPos);
                            summon->GetMotionMaster()->MoveSplinePath(&path);
                        }

                    if (Difficulty(me->GetMap()->GetSpawnMode()) == DUNGEON_DIFFICULTY_HEROIC)
                    {
                        Position startPos[6] = { { 925.485f, -65.67f, 592.5f, 1.4f },{ 921.77f, -65.10f, 592.5f, 1.4f },{ 929.19f, -66.24f, 592.5f, 1.4f },{ 932.46f, -66.74f, 592.5f, 1.4f },{ 924.66f, -71.03f, 592.5f, 1.4f },{ 928.81f, -71.66f, 592.5f, 1.4f } };
                        Position middlePos = { 928.43f, -29.31f, 589.0f, 1.4f };
                        Position endPos = { 937.8f, 21.20f, 574.6f, 1.4f };
                        for (uint8 i = 0; i<6; ++i)
                            if (Creature* summon = me->SummonCreature(i < 4 ? NPC_FALLEN_WARRIOR : NPC_WRATHBONE_COLDWRAITH, startPos[i]))
                            {
                                summon->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                                Position midPos = middlePos;
                                Position finalPos = endPos;
                                summon->MovePosition(midPos, startPos[i].GetExactDist(&startPos[0]), Position::NormalizeOrientation(startPos[i].GetAngle(&startPos[0]) + 1.4f));
                                summon->MovePosition(finalPos, startPos[i].GetExactDist(&startPos[0]), Position::NormalizeOrientation(startPos[i].GetAngle(&startPos[0]) + 1.4f));

                                Movement::PointsArray path;
                                path.push_back(G3D::Vector3(summon->GetPositionX(), summon->GetPositionY(), summon->GetPositionZ()));
                                path.push_back(G3D::Vector3(midPos.GetPositionX(), midPos.GetPositionY(), midPos.GetPositionZ()));
                                path.push_back(G3D::Vector3(finalPos.GetPositionX(), finalPos.GetPositionY(), finalPos.GetPositionZ()));

                                summon->SetHomePosition(finalPos);
                                summon->GetMotionMaster()->MoveSplinePath(&path);
                            }
                    }
                }
                break;
            }
        }
    }

    private:
        InstanceScript* _instance;
        EventMap _events;
        uint32 _killsLeft;
        std::vector<uint64> _deathbringerGUIDs;
};

enum IcicleTrigger
{
    EVENT_TRIGGER = 1,
};

struct npc_pos_icicle_triggerAI : public NullCreatureAI
{
    npc_pos_icicle_triggerAI(Creature* creature) : NullCreatureAI(creature)
    {
        _instance = me->GetInstanceScript();
        _events.ScheduleEvent(EVENT_TRIGGER, 0s, 16s);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!_instance)
            return;

        _events.Update(diff);

        if (_events.ExecuteEvent() == EVENT_TRIGGER)
        {
            if (_instance->GetData(DATA_INSTANCE_PROGRESS) == INSTANCE_PROGRESS_AFTER_TUNNEL_WARN)
                DoCastSelf(SPELL_TUNNEL_ICICLE);
            _events.Repeat(16s, 24s);
        }
    }

    private:
        InstanceScript* _instance;
        EventMap _events;
};

enum Icicle
{
    SPELL_ICICLE_1 = 69428,
    SPELL_ICICLE_2 = 69426,

    EVENT_ICICLE_1 = 1,
    EVENT_ICICLE_2
};

struct npc_pos_collapsing_icicleAI : public NullCreatureAI
{
    npc_pos_collapsing_icicleAI(Creature* creature) : NullCreatureAI(creature)
    {
        _instance = me->GetInstanceScript();
        _events.ScheduleEvent(EVENT_ICICLE_1, 2.5s);
        _events.ScheduleEvent(EVENT_ICICLE_2, 7s);
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spell) override
    {
        if (target && spell && target->GetTypeId() == TYPEID_PLAYER && spell->Id == 70827 && _instance)
            _instance->SetData(DATA_ACHIEV_DONT_LOOK_UP, 0);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_ICICLE_1:
                    DoCastSelf(SPELL_ICICLE_1);
                    DoCastSelf(SPELL_ICICLE_2, true);
                    _events.Repeat(1min);
                    break;
                case EVENT_ICICLE_2:
                    me->SetDisplayId(11686);
                    _events.Repeat(1min);
                    break;
            }
        }
    }

private:
    InstanceScript* _instance;
    EventMap _events;
};

struct npc_pos_martin_or_gorkun_secondAI : public NullCreatureAI
{
    npc_pos_martin_or_gorkun_secondAI(Creature* creature) : NullCreatureAI(creature), _summons(me)
    {
        _instance = me->GetInstanceScript();
        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
        i = 0;
        _events.Reset();
        _events.RescheduleEvent(1, 0.5s);
        _events.RescheduleEvent(2, 15s);

        if (_instance && _instance->GetBossState(DATA_TYRANNUS) != DONE)
            if (Creature* tyrannus = _instance->GetCreature(DATA_TYRANNUS))
            {
                me->SetAttackable(false);
                tyrannus->AI()->Talk(SAY_PREFIGHT_1);
                tyrannus->SetReactState(REACT_AGGRESSIVE);
                if (Player* player = tyrannus->SelectNearestPlayer(100.0f))
                {
                    if (tyrannus->IsAIEnabled)
                        tyrannus->AI()->AttackStart(player);
                    DoZoneInCombat(tyrannus);
                }
            }
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == POINT_MOTION_TYPE && id == 2)
            _events.RescheduleEvent(5, 1s);
    }

    void DoAction(int32 actionId) override
    {
        switch (actionId)
        {
            case 1:
                _summons.DespawnAll();
                break;
            case 2:
                _events.Reset();
                _summons.DespawnEntry(NPC_FALLEN_WARRIOR);

                if (!_instance)
                    return;

                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                me->GetMotionMaster()->MovePoint(2, TSCenterPos);

                for (auto itr = _summons.begin(); itr != _summons.end(); ++itr)
                    if (Creature* creature = _instance->instance->GetCreature(*itr))
                    {
                        float hx, hy, hz, ho;
                        creature->GetHomePosition(hx, hy, hz, ho);
                        creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_CHEER);
                        float ang = frand(1.92f, 2.36f);
                        float dist = frand(50.0f, 85.0f);
                        creature->GetMotionMaster()->MovePoint(0, TSSpawnPos.GetPositionX() + cos(ang)*dist, TSSpawnPos.GetPositionY() + sin(ang)*dist, 628.2f);
                    }
                break;
            case 3:
                if (_instance)
                    if (Creature* sindragosa = _instance->GetCreature(DATA_SINDRAGOSA_GUID))
                    {
                        for (auto itr = _summons.begin(); itr != _summons.end(); ++itr)
                            if (Creature* creature = _instance->instance->GetCreature(*itr))
                                if (creature->IsAlive())
                                    Unit::Kill(sindragosa, creature);
                        if (me->IsAlive())
                            Unit::Kill(sindragosa, me);
                    }
                break;
            default:
                break;
        }
    }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        _summons.Despawn(summon);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        if (!_instance)
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1:
                    if (TSData[i].entry)
                    {
                        if (Creature* creature = me->SummonCreature(TSData[i].entry, TSSpawnPos))
                        {
                            creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
                            creature->GetMotionMaster()->MovePoint(0, TSData[i].x, TSData[i].y, TSHeight);
                        }
                        ++i;
                        _events.ScheduleEvent(1, 150ms);
                    }
                    break;
                case 2:
                    Talk(me->GetEntry() == NPC_MARTIN_VICTUS_2 ? SAY_GENERAL_ALLIANCE_TRASH : SAY_GENERAL_HORDE_TRASH);
                    _events.RescheduleEvent(3, 8s);
                    break;
                case 3:
                    if (Creature* tyrannus = _instance->GetCreature(DATA_TYRANNUS))
                        if (tyrannus->IsAIEnabled)
                            tyrannus->AI()->Talk(SAY_PREFIGHT_2);

                    me->SetFacingTo(5.26f);
                    me->SetOrientation(5.26f);
                    me->SetHomePosition(*me);
                    for (auto itr = _summons.begin(); itr != _summons.end(); ++itr)
                        if (Creature* summon = _instance->instance->GetCreature(*itr))
                        {
                            summon->SetFacingTo(5.26f);
                            summon->SetOrientation(5.26f);
                            summon->SetHomePosition(*summon);
                        }
                    _events.RescheduleEvent(10, 15s);
                    _events.RescheduleEvent(4, 15s);
                    break;
                case 4:
                    if (Creature* tyrannus = _instance->GetCreature(DATA_TYRANNUS))
                        if (tyrannus->IsAIEnabled)
                            tyrannus->AI()->DoAction(1);
                    break;
                case 5:
                    me->SetFacingTo(TSCenterPos.GetOrientation());
                    Talk(me->GetEntry() == NPC_MARTIN_VICTUS_2 ? SAY_GENERAL_ALLIANCE_OUTRO_1 : SAY_GENERAL_HORDE_OUTRO_1);
                    if (Creature* leader = _instance->GetCreature(DATA_LEADER_SECOND_GUID))
                        if (leader->IsAIEnabled)
                            leader->AI()->DoAction(1);
                    break;
                case 10:
                    if (_summons.GetEntryCount(NPC_FALLEN_WARRIOR) < 3)
                        if (Creature* warrior = me->SummonCreature(NPC_FALLEN_WARRIOR, 1060.95f, 102.79f, 630.2f, 2.01f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
                        {
                            warrior->GetMotionMaster()->MovePoint(0, 1047.0f + frand(0.0f, 10.0f), 118.0f + frand(0.0f, 10.0f), 628.2f);
                            warrior->SetHomePosition(*me);
                            for (auto itr = _summons.begin(); itr != _summons.end(); ++itr)
                                if (Creature* summon = _instance->instance->GetCreature(*itr))
                                {
                                    if (summon->GetEntry() == NPC_FALLEN_WARRIOR)
                                        continue;
                                    warrior->SetInCombatWith(summon);
                                    summon->SetInCombatWith(warrior);
                                    warrior->AddThreat(summon, 0.0f);
                                    summon->AddThreat(warrior, 0.0f);
                                }
                        }
                    _events.RescheduleEvent(10, 3s);
                    break;
                default:
                    break;
            }
        }

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

    private:
        InstanceScript* _instance;
        EventMap _events;
        SummonList _summons;
        uint8 i;
};

struct npc_pos_freed_slaveAI : public SmartAI
{
    npc_pos_freed_slaveAI(Creature* creature) : SmartAI(creature)
    {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE);
        // immune to falling icicles
        for (auto spellId : { 69425, 70827 })
            me->ApplySpellImmune(0, IMMUNITY_ID, spellId, true);
    }

    bool CanAIAttack(const Unit* who) const override
    {
        return who->GetEntry() == NPC_FALLEN_WARRIOR;
    }

    void EnterEvadeMode() override
    {
        if (!me->IsAlive() || me->IsInEvadeMode())
            return;

        me->RemoveEvadeAuras();
        me->DeleteThreatList();
        me->CombatStop(true);
        me->LoadCreaturesAddon(true);
        me->SetLootRecipient(nullptr);
        me->ResetPlayerDamageReq();
        me->SetLastDamagedTime(0);
    }
};

enum POSLeaderSecond
{
    ACTION_START_OUTRO = 1,

    EVENT_LEADER_SECOND_OUTRO_1 = 1,
    EVENT_LEADER_SECOND_OUTRO_2,
    EVENT_LEADER_SECOND_OUTRO_3,
    EVENT_LEADER_SECOND_OUTRO_4,
    EVENT_LEADER_SECOND_OUTRO_5,
    EVENT_LEADER_SECOND_OUTRO_6,
    EVENT_LEADER_SECOND_OUTRO_7,
    EVENT_LEADER_SECOND_OUTRO_8,
    EVENT_LEADER_SECOND_OUTRO_9
};

struct npc_pos_leader_secondAI : public NullCreatureAI
{
    npc_pos_leader_secondAI(Creature* creature) : NullCreatureAI(creature)
    {
        _instance = me->GetInstanceScript();
        _barrierGUID = 0;
        _events.Reset();
        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);

        if (_instance)
        {
            if (Creature* rimefang = _instance->GetCreature(DATA_RIMEFANG_GUID))
            {
                rimefang->RemoveAllAuras();
                rimefang->GetMotionMaster()->Clear();
                rimefang->GetMotionMaster()->MoveIdle();
                rimefang->SetVisible(false);
            }

            if (Creature* martinOrGorkun = _instance->GetCreature(DATA_MARTIN_OR_GORKUN_GUID))
                if (martinOrGorkun->IsAIEnabled)
                    martinOrGorkun->AI()->DoAction(2);
        }
    }

    void DoAction(int32 actionId) override
    {
        if (actionId != ACTION_START_OUTRO)
            return;

        _events.RescheduleEvent(EVENT_LEADER_SECOND_OUTRO_1, me->GetEntry() == NPC_JAINA_PART2 ? 15.5s : 18.0s);
        _events.RescheduleEvent(EVENT_LEADER_SECOND_OUTRO_2, me->GetEntry() == NPC_JAINA_PART2 ? 16.5s : 19.0s);
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spell) override
    {
        if (!spell || !target)
            return;

        if ((spell->Id == SPELL_TELEPORT_JAINA || spell->Id == SPELL_TELEPORT_SYLVANAS) && target->GetTypeId() == TYPEID_PLAYER)
        {
            Position teleportPosition(*me);
            me->GetRandomNearPosition(teleportPosition, 4.0f);
            target->ToPlayer()->NearTeleportTo(teleportPosition.GetPositionX(), teleportPosition.GetPositionY(), me->GetPositionZ(), me->GetOrientation());
        }
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type != WAYPOINT_MOTION_TYPE)
            return;

        switch (id)
        {
            case 0:
                Talk(me->GetEntry() == NPC_JAINA_PART2 ? SAY_JAINA_OUTRO_2 : SAY_SYLVANAS_OUTRO_2);
                break;
            case 1:
                if (me->GetEntry() == NPC_JAINA_PART2)
                    Talk(SAY_JAINA_OUTRO_3);
                break;
            case 6:
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                if (GameObject* portcullis = _instance->GetGameObject(DATA_PORTCULLIS))
                    portcullis->SetGoState(GO_STATE_ACTIVE);
                break;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        if (!_instance)
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_LEADER_SECOND_OUTRO_1:
                    if (Creature* sindragosa = me->SummonCreature(NPC_SINDRAGOSA, TSSindragosaPos1))
                    {
                        sindragosa->SetCanFly(true);
                        sindragosa->SetDisableGravity(true);
                        sindragosa->SetHover(true);
                        sindragosa->GetMotionMaster()->MovePoint(0, TSSindragosaPos2);
                    }
                    break;
                case EVENT_LEADER_SECOND_OUTRO_2:
                    if (Creature* martinOrGorkun = _instance->GetCreature(DATA_MARTIN_OR_GORKUN_GUID))
                        if (martinOrGorkun->IsAIEnabled)
                            martinOrGorkun->AI()->Talk(SAY_GENERAL_OUTRO_2);
                    _events.RescheduleEvent(EVENT_LEADER_SECOND_OUTRO_3, me->GetEntry() == NPC_JAINA_PART2 ? 7s : 8s);
                    break;
                case EVENT_LEADER_SECOND_OUTRO_3:
                    Talk(me->GetEntry() == NPC_JAINA_PART2 ? SAY_JAINA_OUTRO_1 : SAY_SYLVANAS_OUTRO_1);
                    DoCastSelf(me->GetEntry() == NPC_JAINA_PART2 ? SPELL_TELEPORT_JAINA_VISUAL : SPELL_TELEPORT_SYLVANAS_VISUAL, true);
                    _events.RescheduleEvent(EVENT_LEADER_SECOND_OUTRO_4, 2s);
                    break;
                case EVENT_LEADER_SECOND_OUTRO_4:
                    DoCastSelf(me->GetEntry() == NPC_JAINA_PART2 ? SPELL_TELEPORT_JAINA : SPELL_TELEPORT_SYLVANAS, true);
                    if (GameObject* barrier = me->SummonGameObject(203005, 1055.49f, 115.03f, 628.15f, 2.08f, 0.0f, 0.0f, 0.0f, 0.0f, 86400, false))
                        _barrierGUID = barrier->GetGUID();
                    _events.RescheduleEvent(EVENT_LEADER_SECOND_OUTRO_5, 1.5s);
                    break;
                case EVENT_LEADER_SECOND_OUTRO_5:
                    if (Creature* martinOrGorkun = _instance->GetCreature(DATA_MARTIN_OR_GORKUN_GUID))
                    {
                        if (Creature* sindragosa = _instance->GetCreature(DATA_SINDRAGOSA_GUID))
                            sindragosa->CastSpell(martinOrGorkun->GetPositionX(), martinOrGorkun->GetPositionY(), martinOrGorkun->GetPositionZ(), SPELL_SINDRAGOSA_FROST_BOMB_POS, true);
                    }
                    _events.RescheduleEvent(EVENT_LEADER_SECOND_OUTRO_6, 5s);
                    _events.RescheduleEvent(EVENT_LEADER_SECOND_OUTRO_9, 2s);
                    break;
                case EVENT_LEADER_SECOND_OUTRO_6:
                    if (Creature* sindragosa = _instance->GetCreature(DATA_SINDRAGOSA_GUID))
                        sindragosa->GetMotionMaster()->MovePoint(0, TSSindragosaPos1);
                    _events.RescheduleEvent(EVENT_LEADER_SECOND_OUTRO_7, 4.5s);
                    break;
                case EVENT_LEADER_SECOND_OUTRO_7:
                    if (Creature* sindragosa = _instance->GetCreature(DATA_SINDRAGOSA_GUID))
                        sindragosa->SetVisible(false);
                    if (GameObject* barrier = me->GetMap()->GetGameObject(_barrierGUID))
                    {
                        barrier->AddObjectToRemoveList();
                        _barrierGUID = 0;
                    }
                    _events.RescheduleEvent(EVENT_LEADER_SECOND_OUTRO_8, 2s);
                    break;
                case EVENT_LEADER_SECOND_OUTRO_8:
                    me->GetMotionMaster()->MovePath(me->GetEntry() == NPC_JAINA_PART2 ? PATH_BEGIN_VALUE + 16 : PATH_BEGIN_VALUE + 17, false);
                    break;
                case EVENT_LEADER_SECOND_OUTRO_9:
                    if (Creature* martinOrGorkun = _instance->GetCreature(DATA_MARTIN_OR_GORKUN_GUID))
                        if (martinOrGorkun->IsAIEnabled)
                            martinOrGorkun->AI()->DoAction(3);
                    break;
                default:
                    break;
            }
        }

    }

    private:
        InstanceScript* _instance;
        EventMap _events;
        uint64 _barrierGUID;
};

enum FrostbiteStalker
{
    EVENT_FREEZING_CIRCLE_DMG = 1,
};

struct npc_frostbite_invisible_stalkerAI : public NullCreatureAI
{
    npc_frostbite_invisible_stalkerAI(Creature* creature) : NullCreatureAI(creature)
    {
        _events.ScheduleEvent(EVENT_FREEZING_CIRCLE_DMG, 3.5s);
        for (uint8 i = 0; i<3; ++i)
        {
            me->SetOrientation(i*M_PI / 3);
            DoCastSelf(34740, true);
            DoCastSelf(34746, true);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        if (_events.ExecuteEvent() == EVENT_FREEZING_CIRCLE_DMG)
        {
            int32 dmg = 2200;
            me->CastCustomSpell(me, 34779, 0, &dmg, 0, true);
        }
    }

private:
    EventMap _events;
};

class spell_pos_empowered_blizzard_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_pos_empowered_blizzard_AuraScript)

    void HandleEffectPeriodic(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        if (Unit* caster = GetCaster())
            caster->CastSpell(frand(447.0f, 480.0f), frand(200.0f, 235.0f), 528.71f, 70131, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pos_empowered_blizzard_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

const char* slaveTexts[23] = {
    "I owe you a long night of drinking, my friend.",
    "Don't let a single one of them live.",
    "I can barely feel my arms, but I'll stand with you once I find some weapons.",
    "I can hardly believe my eyes. Thank you. Really, thank you.",
    "I owe you my life.",
    "I thought I might die in this pit. Thank you!",
    "I will find a way to repay you someday, hero.",
    "I'd almost given up hope.",
    "I'd lost all track of time in this forsaken place. You're a sight for sore eyes, friend.",
    "I'll fight by your side. Offer them no mercy.",
    "I'll join you as soon as I catch my breath, heroes. Thank you.",
    "I'm going to return to help free the rest of the slaves. Thank you again, hero.",
    "I'm going to return to the front of the quarry. Kill a few extra for me.",
    "I'm so glad you're here. I wouldn't have made it much longer.",
    "I'm with you, hero.",
    "If by life or death I can repay you, I will.",
    "Now is the time for revenge.",
    "Please, carry out our vengeance on the Scourgelord.",
    "Too many of us died in this pit. Far too many.",
    "When you kill the Pit Master, spit on his corpse for me, will you?",
    "You're a beautiful sight... you have no idea.",
    "Have my babies.",
    "I could just kiss you!"
};

const Position slaveFreePos[4] = {
    { 699.82f, -82.68f, 512.6f, 0.0f },
    { 643.51f, 79.20f, 511.57f, 0.0f },
    { 800.09f, 78.66f, 510.2f, 0.0f },
    { 528.26f, 187.04f, 528.75f, 0.0f }
};

class SlaveRunEvent : public BasicEvent
{
    public:
        SlaveRunEvent(Creature& owner) : _owner(owner) { }

        bool Execute(uint64 /*eventTime*/, uint32 /*updateTime*/) override
        {
            uint32 pointId = 0;
            float minDist = _owner.GetExactDist2dSq(&slaveFreePos[pointId]);
            for (uint32 i = 1; i<4; ++i)
            {
                float dist = _owner.GetExactDist2dSq(&slaveFreePos[i]);
                if (dist < minDist)
                {
                    minDist = dist;
                    pointId = i;
                }
            }

            if (minDist < 200.0f*200.0f)
                _owner.GetMotionMaster()->MovePoint(0, slaveFreePos[pointId], true, false);
            return true;
        }

    private:
        Creature& _owner;
};

class spell_pos_slave_trigger_closest_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_pos_slave_trigger_closest_SpellScript)

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            if (target->GetUInt32Value(UNIT_NPC_EMOTESTATE)) // prevent using multiple times
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    player->RewardPlayerAndGroupAtEvent(36764, GetCaster()); // alliance
                    player->RewardPlayerAndGroupAtEvent(36770, GetCaster()); // horde
                }
                target->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                if (Creature* slave = target->ToCreature())
                {
                    slave->DespawnOrUnsummon(7s);
                    slave->MonsterSay(slaveTexts[urand(0, (slave->getGender() == GENDER_FEMALE ? 22 : 20))], LANG_UNIVERSAL, 0);
                    slave->m_Events.AddEvent(new SlaveRunEvent(*slave), slave->m_Events.CalculateTime(3000));
                }
            }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pos_slave_trigger_closest_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

class spell_pos_rimefang_frost_nova_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_pos_rimefang_frost_nova_SpellScript)

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
        {
            Unit::Kill(GetCaster(), target);
            if (target->GetTypeId() == TYPEID_UNIT)
                target->ToCreature()->DespawnOrUnsummon(30s);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pos_rimefang_frost_nova_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

enum Blight
{
    SPELL_BLIGHT = 69604
};

class spell_pos_blight_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_pos_blight_AuraScript)

    void HandleEffectPeriodic(AuraEffect const * aurEff)
    {
        if (aurEff->GetTickNumber() == aurEff->GetTotalTicks())
            if (Unit* target = GetTarget())
                target->CastSpell(target, SPELL_BLIGHT, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pos_blight_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

class spell_pos_glacial_strike_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_pos_glacial_strike_AuraScript)

    void HandleEffectPeriodic(AuraEffect const* aurEff)
    {
        if (Unit* target = GetTarget())
            if (target->GetHealth() == target->GetMaxHealth())
            {
                PreventDefaultAction();
                aurEff->GetBase()->Remove(AURA_REMOVE_BY_EXPIRE);
            }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pos_glacial_strike_AuraScript::HandleEffectPeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
    }
};

class at_tyrannus_event_starter : public AreaTriggerScript
{
    public:
        at_tyrannus_event_starter() : AreaTriggerScript("at_tyrannus_event_starter") { }

        bool OnTrigger(Player* player, const AreaTriggerEntry* /*at*/)
        {
            InstanceScript* instance = player->GetInstanceScript();
            if (!instance)
                return false;

            if (instance->GetData(DATA_INSTANCE_PROGRESS) < INSTANCE_PROGRESS_AFTER_TUNNEL_WARN)
                return false;

            if (instance->GetBossState(DATA_GARFROST) == DONE && instance->GetBossState(DATA_ICK) == DONE && instance->GetBossState(DATA_TYRANNUS) != DONE && !instance->GetCreature(DATA_MARTIN_OR_GORKUN_GUID))
            {
                if (Creature* gorkun = instance->instance->SummonCreature(NPC_GORKUN_IRONSKULL_2, TSSpawnPos))
                    gorkun->GetMotionMaster()->MovePoint(0, TSMidPos);

                instance->SetData(DATA_INSTANCE_PROGRESS, INSTANCE_PROGRESS_TYRANNUS_INTRO);
            }

            return false;
        }
};

void AddSC_pit_of_saron()
{
    new CreatureAILoader<npc_pos_leaderAI>("npc_pos_leader");
    new CreatureAILoader<npc_pos_deathwhisper_necrolyteAI>("npc_pos_deathwhisper_necrolyte");
    new CreatureAILoader<npc_pos_after_first_bossAI>("npc_pos_after_first_boss");
    new CreatureAILoader<npc_pos_tyrannus_eventsAI>("npc_pos_tyrannus_events");
    new CreatureAILoader<npc_pos_icicle_triggerAI>("npc_pos_icicle_trigger");
    new CreatureAILoader<npc_pos_collapsing_icicleAI>("npc_pos_collapsing_icicle");
    new CreatureAILoader<npc_pos_martin_or_gorkun_secondAI>("npc_pos_martin_or_gorkun_second");
    new CreatureAILoader<npc_pos_freed_slaveAI>("npc_pos_freed_slave");
    new CreatureAILoader<npc_pos_leader_secondAI>("npc_pos_leader_second");
    new CreatureAILoader<npc_frostbite_invisible_stalkerAI>("npc_frostbite_invisible_stalker");

    new AuraScriptLoaderEx<spell_pos_empowered_blizzard_AuraScript>("spell_pos_empowered_blizzard");
    new SpellScriptLoaderEx<spell_pos_slave_trigger_closest_SpellScript>("spell_pos_slave_trigger_closest");
    new SpellScriptLoaderEx<spell_pos_rimefang_frost_nova_SpellScript>("spell_pos_rimefang_frost_nova");
    new AuraScriptLoaderEx<spell_pos_blight_AuraScript>("spell_pos_blight");
    new AuraScriptLoaderEx<spell_pos_glacial_strike_AuraScript>("spell_pos_glacial_strike");

    new at_tyrannus_event_starter();
}