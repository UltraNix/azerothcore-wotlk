/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "utgarde_pinnacle.h"
#include "Vehicle.h"
#include "CombatAI.h"
#include "Player.h"
#include "SpellInfo.h"
#include "World.h"

enum Misc
{
    // TEXTS
    SAY_AGGRO                            = 0,
    SAY_KILL                             = 1,
    SAY_DEATH                            = 3,
    SAY_DRAKE_DEATH                      = 5,
    SAY_DRAKE_BREATH                     = 6,

    // SPELLS
    SPELL_CRUSH                          = 50234,
    SPELL_POISONED_SPEAR                 = 50255,
    SPELL_POISONED_SPEAR_PERIODIC        = 50258,
    SPELL_WHIRLWIND                      = 50228,

    SPELL_SKADI_TELEPORT                 = 61790,
    SPELL_RIDE_GRAUF                     = 61791,

    SPELL_FREEZING_CLOUD                 = 47579,
    SPELL_FREEZING_CLOUD_RIGHT_PERIODIC  = 47592,
    SPELL_FREEZING_CLOUD_LEFT_PERIODIC   = 47590,

    SPELL_LAUNCH_HARPOON                 = 48642,

    // NPCS
    NPC_YMIRJAR_WARRIOR                  = 26690,
    NPC_YMIRJAR_WITCH_DOCTOR             = 26691,
    NPC_YMIRJAR_HARPOONER                = 26692,
    NPC_GRAUF                            = 26893,
    NPC_BREATH_TRIGGER                   = 28351,
    EQUIP_MACE                           = 17193,

    // ACTIONS
    ACTION_START_EVENT                   = 1,
    ACTION_PHASE2                        = 2,
    ACTION_MYGIRL_ACHIEVEMENT            = 3,

    // ACHIEVEMENTS
    ACHIEV_TIMED_LODI_DODI                = 17726,
};

enum Events
{
    // SKADI
    EVENT_SKADI_START                    = 1,
    EVENT_SKADI_CRUSH,
    EVENT_SKADI_SPEAR,
    EVENT_SKADI_WHIRLWIND,

    // GRAUF
    EVENT_GRAUF_START,
    EVENT_GRAUF_MOVE,
    EVENT_GRAUF_SUMMON_HELPERS,
    EVENT_GRAUF_CHECK,
    EVENT_ANNOUNCE
};

Position const TrashPosition[]=
{
    {441.236f, -512.000f, 104.930f},
    {478.436f, -494.475f, 104.730f}
};

Position const SkadiPosition[] =
{
    {338.679f, -507.254f, 124.122f},
    {338.679f, -513.254f, 124.122f},
    {490.096f, -510.86f, 123.368f},
    {490.76f, -517.389f, 123.368f}
};

Position const FirstWaveLocations[] =
{
    { 458.5323f, -516.2537f, 104.617f },
    { 429.4242f, -517.5624f, 104.8936f },
    { 394.4955f, -514.6144f, 104.7235f },
    { 362.2862f, -515.8771f, 104.7539f },
    { 333.5374f, -514.7942f, 104.4779f },
    { 457.6105f, -508.8362f, 104.4013f },
    { 427.4026f, -510.7716f, 104.8802f },
    { 392.5114f, -507.9429f, 104.7433f },
    { 362.9511f, -508.4115f, 104.7218f },
    { 333.536f,  -506.0805f, 104.4258f },
    { 478.31f,   -511.049f,  104.7242f, 3.263766f },
    { 482.25f,   -514.1273f, 104.7234f, 3.263766f },
    { 481.3883f, -507.1089f, 104.7241f, 3.263766f },
};

Position const SpawnLocation = { 477.5808f, -484.5591f, 104.8221f, 4.677482f };

#define EMOTE_IN_RANGE "Skadi the Ruthless is within range of the harpoon launchers!"
#define EMOTE_BREATH "Grauf takes a deep breath."

enum phase
{
    PHASE_NONE,
    PHASE_START,
    PHASE_FLIGHT,
    PHASE_LAND,
    PHASE_GROUND
};

class boss_skadi : public CreatureScript
{
public:
    boss_skadi() : CreatureScript("boss_skadi") { }

    struct boss_skadiAI : public ScriptedAI
    {
        boss_skadiAI(Creature* creature) : ScriptedAI(creature), summons(me), instance(creature->GetInstanceScript()) { }

        void Reset() override
        {
            events.Reset();
            summons.DespawnAll();
            if (Creature* grauf = me->SummonCreature(NPC_GRAUF, 341.741f, -516.955f, 104.669f, 3.12414f))
                GraufGUID = grauf->GetGUID();
            SecondPhase = false;
            EventStarted = false;

            me->RemoveAllAuras();
            me->SetControlled(false, UNIT_STATE_ROOT);
            me->UpdatePosition(343.02f, -507.325f, 104.567f, M_PI, true);
            me->StopMovingOnCurrentPos();

            if(instance)
            {
                instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_TIMED_LODI_DODI);
                instance->SetData(DATA_SKADI_THE_RUTHLESS, NOT_STARTED);
                instance->SetData(SKADI_IN_RANGE, 0);
                instance->SetData(DATA_SKADI_ACHIEVEMENT, false);
            }
        }

        void JustSummoned(Creature* summon) override
        {
            summons.Summon(summon);
        }

        void SpawnFirstWave()
        {
            for (uint8 i = 0; i < 10; i++)
                if (Creature* summon = me->SummonCreature(NPC_YMIRJAR_WARRIOR, SpawnLocation, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
                    summon->GetMotionMaster()->MovePoint(0, FirstWaveLocations[i]);

            if (Creature* crea = me->SummonCreature(NPC_YMIRJAR_WITCH_DOCTOR, SpawnLocation, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
                crea->GetMotionMaster()->MovePoint(0, FirstWaveLocations[10]);
            if (Creature* crea = me->SummonCreature(NPC_YMIRJAR_HARPOONER, SpawnLocation, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
                crea->GetMotionMaster()->MovePoint(0, FirstWaveLocations[11]);
            if (Creature* crea = me->SummonCreature(NPC_YMIRJAR_HARPOONER, SpawnLocation, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
                crea->GetMotionMaster()->MovePoint(0, FirstWaveLocations[12]);
        }

        void SpawnHelpers(uint8 Spot)
        {
            if (Creature* Harpooner = me->SummonCreature(NPC_YMIRJAR_HARPOONER, TrashPosition[Spot].GetPositionX() + rand() % 5, TrashPosition[Spot].GetPositionY() + rand() % 5, TrashPosition[Spot].GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
            {
                Harpooner->SetInCombatWithZone();
                summons.Summon(Harpooner);
            }
            if (Creature* Second = me->SummonCreature((urand(0, 1) ? NPC_YMIRJAR_WARRIOR : NPC_YMIRJAR_WITCH_DOCTOR), TrashPosition[Spot].GetPositionX() + rand() % 5, TrashPosition[Spot].GetPositionY() + rand() % 5, TrashPosition[Spot].GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
            {
                Second->SetInCombatWithZone();
                summons.Summon(Second);
            }
        }

        Creature* GetGrauf() { return ObjectAccessor::GetCreature(*me, GraufGUID); }

        void EnterCombat(Unit* /*attacker*/) override
        {
            if (!EventStarted)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                EventStarted = true;
                SpawnFirstWave();
                Talk(SAY_AGGRO);
                if (instance)
                {
                    if (IsHeroic())
                        instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_TIMED_LODI_DODI);
                    
                    instance->SetData(DATA_SKADI_THE_RUTHLESS, IN_PROGRESS);
                }

                me->SetControlled(true, UNIT_STATE_ROOT);
                me->SetInCombatWithZone();
                events.RescheduleEvent(EVENT_SKADI_START, 2000);
            }
        }

        void DoAction(int32 param) override
        {   
            if (param == ACTION_PHASE2)
            {
                Talk(SAY_DRAKE_DEATH);
                DoCast(me, SPELL_SKADI_TELEPORT, true);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                SecondPhase = true;
                events.ScheduleEvent(EVENT_SKADI_CRUSH, 8000);
                events.ScheduleEvent(EVENT_SKADI_SPEAR, 10000);
                events.ScheduleEvent(EVENT_SKADI_WHIRLWIND, 15000);

                if (me->GetVictim())
                    me->GetMotionMaster()->MoveChase(me->GetVictim());
                else
                    me->SetInCombatWithZone();
            }
        }

        void SetData(uint32 type, uint32 data) override
        {
            if (type == 0)
                SpawnHelpers(data);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim() && SecondPhase)
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_SKADI_START:
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    if (Creature* grauf = GetGrauf())
                    {
                        DoCast(grauf, SPELL_RIDE_GRAUF);
                        if(grauf->IsAIEnabled)
                            grauf->AI()->DoAction(ACTION_START_EVENT);
                    }
                    else
                        EnterEvadeMode();

                    events.PopEvent();
                    break;
                case EVENT_SKADI_CRUSH:
                    DoCastVictim(SPELL_CRUSH);
                    events.RepeatEvent(8000);
                    break;
                case EVENT_SKADI_SPEAR:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        DoCast(target, SPELL_POISONED_SPEAR);
                    events.RepeatEvent(10000);
                    break;
                case EVENT_SKADI_WHIRLWIND:
                    DoCastAOE(SPELL_WHIRLWIND);
                    events.RepeatEvent(urand(15000, 20000));
                    events.DelayEvents(10000);
                    break;
                default:
                    break;
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/) override
        {
            summons.DespawnAll();
            Talk(SAY_DEATH);

            if (instance)
            {
                instance->SetData(DATA_SKADI_THE_RUTHLESS, DONE);
                instance->HandleGameObject(instance->GetData64(SKADI_DOOR), true);
            }
        }

        void KilledUnit(Unit* victim) override
        {
            if(roll_chance_i(50))
                Talk(SAY_KILL);
        }

        private:
            InstanceScript* instance;
            EventMap events;
            SummonList summons;
            uint64 GraufGUID;
            bool SecondPhase, EventStarted;
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_skadiAI(pCreature);
    }
};

class boss_skadi_grauf : public CreatureScript
{
public:
    boss_skadi_grauf() : CreatureScript("boss_skadi_grauf") { }

    struct boss_skadi_graufAI : public VehicleAI
    {
        boss_skadi_graufAI(Creature* creature) : VehicleAI(creature), summons(me), instance(creature->GetInstanceScript()) 
        { 
            preNerf = sWorld->PatchNotes(PATCH_MIN, PATCH_332);
            harpoonReqCount = preNerf ? 5 : 3;
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetRegeneratingHealth(false);
            me->SetSpeedRate(MOVE_RUN, 2.5f);
            events.Reset();
            summons.DespawnAll();
            currentPos = 0;
            died = false;
            AchievementHitCount = 0;
            me->RemoveAllAuras();
        }

        void DoAction(int32 param) override
        {
            if (param == ACTION_START_EVENT)
            {
                events.RescheduleEvent(EVENT_GRAUF_CHECK, 5000);
                events.RescheduleEvent(EVENT_GRAUF_START, 2000);
            }
            else if (param == ACTION_MYGIRL_ACHIEVEMENT)
            {
                AchievementHitCount++;
                if (AchievementHitCount >= harpoonReqCount && instance)
                    instance->SetData(DATA_SKADI_ACHIEVEMENT, true);
            }
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (instance)
                instance->SetData(SKADI_IN_RANGE, 0);

            RemoveSkadi(false);
            me->DespawnOrUnsummon(1000);
        }

        void SpawnFlameTriggers(uint8 point)
        {
            switch (point)
            {
                case 0:
                    DoCast(SPELL_FREEZING_CLOUD_LEFT_PERIODIC);
                    break;
                case 1:
                    DoCast(SPELL_FREEZING_CLOUD_RIGHT_PERIODIC);
                    break;
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            switch(id)
            {
                case 0:
                case 1:
                    me->RemoveAurasDueToSpell(SPELL_FREEZING_CLOUD_LEFT_PERIODIC);
                    me->RemoveAurasDueToSpell(SPELL_FREEZING_CLOUD_RIGHT_PERIODIC);
                    me->SetFacingTo(M_PI*2);
                    break;
                case 2:
                case 3:
                    if (instance)
                        instance->SetData(SKADI_IN_RANGE, 1);
                    events.ScheduleEvent(EVENT_ANNOUNCE, 10000);
                    me->MonsterTextEmote(EMOTE_IN_RANGE, nullptr, true);
                    me->SetFacingTo(M_PI);
                    break;
            }
        }

        uint8 SelectNextPos(uint8 Position)
        {
            switch (Position)
            {
                case 0:
                case 1:
                    return 2+urand(0,1);
                default:
                    if (me->GetPositionY() < -515.0f)
                        return 1;
                    else
                        return 0;
            }
        }

        void EnterCombat(Unit* /*attacker*/)
        {
            me->SetInCombatWithZone();
        }

        void RemoveSkadi(bool withEvade)
        {
            if (Unit *skadi = me->GetVehicleKit()->GetPassenger(0))
            {
                summons.DespawnAll();
                skadi->ExitVehicle();
                if (withEvade)
                {
                    skadi->ToCreature()->AI()->EnterEvadeMode();
                    skadi->UpdatePosition(343.02f, -507.325f, 104.567f, M_PI, true);
                }
                else
                    skadi->ToCreature()->AI()->DoAction(ACTION_PHASE2);

                skadi->StopMovingOnCurrentPos();
            }
        }

        void CheckPlayers()
        {
            Map::PlayerList const& pList = me->GetMap()->GetPlayers();
            for(Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
            {
                if (itr->GetSource()->GetPositionX() < 320.0f || itr->GetSource()->IsGameMaster() || !itr->GetSource()->IsAlive())
                    continue;

                return;
            }
            
            RemoveSkadi(true);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);
            switch (events.GetEvent())
            {
                case EVENT_GRAUF_CHECK:
                {
                    CheckPlayers();
                    events.RepeatEvent(2000);
                    break;
                }
                case EVENT_GRAUF_START:
                {
                    me->GetMotionMaster()->Clear(true);
                    me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
                    me->GetMotionMaster()->MoveTakeoff(10, SkadiPosition[0].GetPositionX(), SkadiPosition[0].GetPositionY(), SkadiPosition[0].GetPositionZ(), 3.0f);

                    events.ScheduleEvent(EVENT_GRAUF_MOVE, 15000);
                    events.ScheduleEvent(EVENT_GRAUF_SUMMON_HELPERS, 20000);
                    events.PopEvent();
                    break;
                }
                case EVENT_GRAUF_MOVE:
                {
                    AchievementHitCount = 0;
                    uint8 targetPoint = SelectNextPos(currentPos);
                    me->GetMotionMaster()->MovePoint(targetPoint, SkadiPosition[targetPoint].GetPositionX(), SkadiPosition[targetPoint].GetPositionY(), SkadiPosition[targetPoint].GetPositionZ());
                    if (targetPoint <= 1)
                        SpawnFlameTriggers(targetPoint);
                    currentPos = targetPoint;
                    events.RepeatEvent(25000);
                    break;
                }
                case EVENT_GRAUF_SUMMON_HELPERS:
                {
                    if (Creature* skadi = me->FindNearestCreature(NPC_SKADI_THE_RUTHLESS, 100.0f, true))
                        skadi->AI()->SetData(0, 1);
                    events.RepeatEvent(15000);
                    break;
                }
                case EVENT_ANNOUNCE:
                {
                    if (instance)
                        instance->SetData(SKADI_IN_RANGE, 0);
                    me->MonsterTextEmote(EMOTE_BREATH, nullptr, true);
                    if (Creature* skadi = me->FindNearestCreature(NPC_SKADI_THE_RUTHLESS, 100.0f, true))
                        skadi->AI()->Talk(SAY_DRAKE_BREATH);
                    events.PopEvent();
                    break;
                }
            }
        }
        private:
            InstanceScript* instance;
            EventMap events;
            SummonList summons;
            uint8 currentPos, AchievementHitCount, harpoonReqCount;
            bool preNerf, died;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_skadi_graufAI(creature);
    }
};

class go_harpoon_canon : public GameObjectScript
{ 
public: 
    go_harpoon_canon() : GameObjectScript("go_harpoon_canon") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        InstanceScript* instance = go->GetInstanceScript();
        if (instance && instance->GetData(DATA_SKADI_THE_RUTHLESS) == IN_PROGRESS)
            if (instance->GetData(SKADI_IN_RANGE) == 1)
            {
                if (Creature *grauf = ObjectAccessor::GetCreature(*player, instance->GetData64(DATA_GRAUF)))
                {
                    go->CastSpell(grauf, SPELL_LAUNCH_HARPOON);
                    grauf->AI()->DoAction(ACTION_MYGIRL_ACHIEVEMENT);
                }
            }
            else
                return false;

        return true;
    }
};

struct npc_skadi_trashAI : public ScriptedAI
{
    npc_skadi_trashAI(Creature* creature) : ScriptedAI(creature) { }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        if (pointId == 0)
        {
            me->SetFacingTo(M_PI);
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, me->GetEntry() == NPC_YMIRJAR_WARRIOR ? EMOTE_STATE_READY1H : EMOTE_STATE_READY2HL);
        }
    }

    virtual void EnterCombat(Unit* /*attacker*/) = 0;
    virtual void UpdateAI(uint32 diff) = 0;
};

enum YmirjarWarrior
{
    SPELL_HAMSTRING = 48639,
    SPELL_STRIKE    = 48640,

    EVENT_HAMSTRING = 1,
    EVENT_STRIKE
};

class npc_ymirjar_warrior : public CreatureScript
{
public:
    npc_ymirjar_warrior() : CreatureScript("npc_ymirjar_warrior") { }

    struct npc_ymirjar_warriorAI : public npc_skadi_trashAI
    {
        npc_ymirjar_warriorAI(Creature* creature) : npc_skadi_trashAI(creature) { }

        void EnterCombat(Unit* attacker) override
        {
            CreatureAI::EnterCombat(attacker);
            _events.ScheduleEvent(EVENT_HAMSTRING, 2000);
            _events.ScheduleEvent(EVENT_STRIKE, 9000);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_HAMSTRING:
                        DoCastVictim(SPELL_HAMSTRING);
                        _events.RepeatEvent(urand(11000, 18000));
                        break;
                    case EVENT_STRIKE:
                        DoCastVictim(SPELL_STRIKE);
                        _events.RepeatEvent(urand(10000, 13000));
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        private:
            EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_ymirjar_warriorAI>(creature);
    }
};

enum YmirjarWitchDoctor
{
    SPELL_SHADOW_BOLT = 49084,
    SPELL_SHRINK      = 49089,

    EVENT_SHADOW_BOLT = 1,
    EVENT_SHRINK
};

class npc_ymirjar_witch_doctor : public CreatureScript
{
public:
    npc_ymirjar_witch_doctor() : CreatureScript("npc_ymirjar_witch_doctor") { }

    struct npc_ymirjar_witch_doctorAI : public npc_skadi_trashAI
    {
        npc_ymirjar_witch_doctorAI(Creature* creature) : npc_skadi_trashAI(creature) { }

        void EnterCombat(Unit* attacker) override
        {
            CreatureAI::EnterCombat(attacker);
            _events.ScheduleEvent(EVENT_SHADOW_BOLT, 2000);
            _events.ScheduleEvent(EVENT_SHRINK, urand(20000, 34000));
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_HAMSTRING:
                    DoCastVictim(SPELL_SHADOW_BOLT);
                    _events.RepeatEvent(2000);
                    break;
                case EVENT_STRIKE:
                    DoCastVictim(SPELL_SHRINK);
                    _events.RepeatEvent(urand(20000, 34000));
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_ymirjar_witch_doctorAI>(creature);
    }
};

enum YmirjarHarpooner
{
    SPELL_NET            = 49092,
    SPELL_THROW          = 49091,
    SPELL_SUMMON_HARPOON = 56789,

    EVENT_NET            = 1,
    EVENT_THROW
};

class npc_ymirjar_harpooner : public CreatureScript
{
public:
    npc_ymirjar_harpooner() : CreatureScript("npc_ymirjar_harpooner") { }

    struct npc_ymirjar_harpoonerAI : public npc_skadi_trashAI
    {
        npc_ymirjar_harpoonerAI(Creature* creature) : npc_skadi_trashAI(creature) { }

        void EnterCombat(Unit* attacker) override
        {
            CreatureAI::EnterCombat(attacker);
            _events.ScheduleEvent(EVENT_NET, 13000);
            _events.ScheduleEvent(EVENT_THROW, 2000);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_NET:
                    if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 30.0f, true))
                        DoCast(target, SPELL_NET);
                    _events.RepeatEvent(13000);
                    break;
                case EVENT_THROW:
                    DoCastVictim(SPELL_THROW);
                    _events.RepeatEvent(2000);
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/) override
        {
            DoCast(SPELL_SUMMON_HARPOON);
        }

    private:
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_ymirjar_harpoonerAI>(creature);
    }
};

class spell_skadi_poisoned_spear : public SpellScriptLoader
{
public:
    spell_skadi_poisoned_spear() : SpellScriptLoader("spell_skadi_poisoned_spear") { }

    class spell_skadi_poisoned_spear_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_skadi_poisoned_spear_SpellScript);

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            GetHitUnit()->CastSpell(GetHitUnit(), SPELL_POISONED_SPEAR_PERIODIC, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_skadi_poisoned_spear_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_skadi_poisoned_spear_SpellScript();
    }
};

class spell_skadi_launch_harpoon : public SpellScriptLoader
{
public:
    spell_skadi_launch_harpoon() : SpellScriptLoader("spell_skadi_launch_harpoon") { }

    class spell_skadi_launch_harpoon_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_skadi_launch_harpoon_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.size() >= 2)
                targets.remove_if([](WorldObject* obj) -> bool 
                { 
                    return obj->GetEntry() != NPC_GRAUF; 
                });
        }

        void HandleDamageCalc()
        {
            if (Unit* target = GetHitUnit())
                SetHitDamage(target->CountPctFromMaxHealth(sWorld->PatchNotes(PATCH_MIN, PATCH_332) ? 20 : 35));
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_skadi_launch_harpoon_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ENTRY);
            OnHit += SpellHitFn(spell_skadi_launch_harpoon_SpellScript::HandleDamageCalc);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_skadi_launch_harpoon_SpellScript();
    }
};

class spell_freezing_cloud_area_right : public SpellScriptLoader
{
public:
    spell_freezing_cloud_area_right() : SpellScriptLoader("spell_freezing_cloud_area_right") { }

    class spell_freezing_cloud_area_right_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_freezing_cloud_area_right_SpellScript);

        bool Validate(SpellInfo const* /*spell*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_FREEZING_CLOUD))
                return false;
            return true;
        }

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if([](WorldObject* obj) -> bool
            {
                return obj->GetPositionY() > -511.0f; 
            });
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            GetHitUnit()->CastSpell(GetHitUnit(), SPELL_FREEZING_CLOUD, true);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_freezing_cloud_area_right_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnEffectHitTarget += SpellEffectFn(spell_freezing_cloud_area_right_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_freezing_cloud_area_right_SpellScript();
    }
};

class spell_freezing_cloud_area_left : public SpellScriptLoader
{
public:
    spell_freezing_cloud_area_left() : SpellScriptLoader("spell_freezing_cloud_area_left") { }

    class spell_freezing_cloud_area_left_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_freezing_cloud_area_left_SpellScript);

        bool Validate(SpellInfo const* /*spell*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_FREEZING_CLOUD))
                return false;
            return true;
        }

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if([](WorldObject* obj) -> bool
            { 
                return obj->GetPositionY() < -511.0f; 
            });
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            GetHitUnit()->CastSpell(GetHitUnit(), SPELL_FREEZING_CLOUD, true);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_freezing_cloud_area_left_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnEffectHitTarget += SpellEffectFn(spell_freezing_cloud_area_left_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_freezing_cloud_area_left_SpellScript();
    }
};

class spell_freezing_cloud_damage : public SpellScriptLoader
{
public:
    spell_freezing_cloud_damage() : SpellScriptLoader("spell_freezing_cloud_damage") { }

    class spell_freezing_cloud_damage_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_freezing_cloud_damage_AuraScript);

        bool CanBeAppliedOn(Unit* target)
        {
            if (Aura* aur = target->GetAura(GetId()))
                if (aur->GetOwner() != GetOwner())
                    return false;

            return true;
        }

        void Register() override
        {
            DoCheckAreaTarget += AuraCheckAreaTargetFn(spell_freezing_cloud_damage_AuraScript::CanBeAppliedOn);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_freezing_cloud_damage_AuraScript();
    }
};

void AddSC_boss_skadi()
{
    new boss_skadi();
    new boss_skadi_grauf();
    new go_harpoon_canon();
    new npc_ymirjar_warrior();
    new npc_ymirjar_witch_doctor();
    new npc_ymirjar_harpooner();
    new spell_skadi_poisoned_spear();
    new spell_skadi_launch_harpoon();
    new spell_freezing_cloud_area_left();
    new spell_freezing_cloud_area_right();
    new spell_freezing_cloud_damage();
}
