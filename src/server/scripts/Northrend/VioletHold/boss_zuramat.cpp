#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "ScriptedCreature.h"
#include "violet_hold.h"

enum ZuramatSpells
{
    SPELL_SHROUD_OF_DARKNESS                    = 54524,
    SPELL_SUMMON_VOID_SENTRY                    = 54369,
    SPELL_VOID_SHIFT                            = 54361,
    SPELL_VOID_SHIFTED                          = 54343,
    SPELL_ZURAMAT_ADD                           = 54341,
    SPELL_ZURAMAT_ADD_2                         = 54342,
    SPELL_ZURAMAT_ADD_DUMMY                     = 54351,
    SPELL_SUMMON_VOID_SENTRY_BALL               = 58650
};

enum ZuramatYells
{
    SAY_AGGRO,
    SAY_SLAY,
    SAY_DEATH,
    SAY_SPAWN,
    SAY_SHIELD,
    SAY_WHISPER
};

enum ZuramatMisc
{
    ACTION_DESPAWN_VOID_SENTRY_BALL             = 1,
    DATA_VOID_DANCE                             = 2153
};

struct boss_zuramatAI : public BossAI
{
    boss_zuramatAI(Creature* creature) : BossAI(creature, DATA_ZURAMAT) { }

    void Reset() override
    {
        me->SetWalk(true);
        _voidDance = true;
        _Reset();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        me->SetWalk(false);
        _EnterCombat();
        Talk(SAY_AGGRO);
        scheduler.Schedule(4s, [this](TaskContext task)
        {
            DoCastSelf(SPELL_SUMMON_VOID_SENTRY);
            task.Repeat(7s, 10s);
        });

        scheduler.Schedule(9s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 60.0f, true))
                DoCast(target, SPELL_VOID_SHIFT);
            task.Repeat(15s);
        });

        scheduler.Schedule(18s, 20s, [this](TaskContext task)
        {
            DoCastSelf(SPELL_SHROUD_OF_DARKNESS);
            task.Repeat();
        });
    }

    void JustReachedHome() override
    {
        _JustReachedHome();
        instance->SetData(DATA_HANDLE_CELLS, DATA_ZURAMAT);
    }

    void SummonedCreatureDies(Creature* summon, Unit* who) override
    {
        if (summon->GetEntry() == NPC_VOID_SENTRY && summon->IsAIEnabled)
            _voidDance = false;
        BossAI::SummonedCreatureDies(summon, who);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_VOID_SENTRY && summon->IsAIEnabled)
            summon->AI()->DoAction(ACTION_DESPAWN_VOID_SENTRY_BALL);
        BossAI::SummonedCreatureDespawn(summon);
    }

    uint32 GetData(uint32 type) const override
    {
        if (type == DATA_VOID_DANCE)
            return _voidDance ? 1 : 0;

        return 0;
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer())
            Talk(SAY_SLAY);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff,
            std::bind(&BossAI::DoMeleeAttackIfReady, this));
    }

    private:
        bool _voidDance;
};

struct npc_void_sentryAI : public ScriptedAI
{
    npc_void_sentryAI(Creature* creature) : ScriptedAI(creature), _summons(creature)
    {
        me->SetReactState(REACT_PASSIVE);
    }

    void IsSummonedBy(Unit* /*summoner*/) override
    {
        DoCastSelf(SPELL_SUMMON_VOID_SENTRY_BALL, true);
    }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);
        summon->SetReactState(REACT_PASSIVE);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        _summons.Despawn(summon);
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_DESPAWN_VOID_SENTRY_BALL)
            _summons.DespawnAll();
    }

    void JustDied(Unit* /*killer*/) override
    {
        DoAction(ACTION_DESPAWN_VOID_SENTRY_BALL);
    }

    void UpdateAI(uint32 diff) override
    {
        if (InstanceScript* instance = me->GetInstanceScript())
            if (instance->GetBossState(DATA_ZURAMAT) != IN_PROGRESS)
                me->DespawnOrUnsummon();
    }

    private:
        SummonList _summons;
};

class achievement_void_dance : public AchievementCriteriaScript
{
    public:
        achievement_void_dance() : AchievementCriteriaScript("achievement_void_dance") { }

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            if (!target)
                return false;

            if (Creature* Zuramat = target->ToCreature())
                if (Zuramat->IsAIEnabled && Zuramat->AI()->GetData(DATA_VOID_DANCE) && Zuramat->GetMap()->IsHeroic())
                    return true;

            return false;
        }
};

void AddSC_boss_zuramat()
{
    new CreatureAILoader<boss_zuramatAI>("boss_zuramat");
    new CreatureAILoader<npc_void_sentryAI>("npc_void_sentry");
    new achievement_void_dance();
}
