#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "molten_core.h"

enum Texts
{
    SAY_SUMMON_RAG_3            = 2,
    SAY_REINFORCEMENTS_1,
    SAY_REINFORCEMENTS_2,
    SAY_HAMMER,
    SAY_WRATH,
    SAY_KILL,
    SAY_MAGMA_BURST
};

enum Spells
{
    SPELL_WRATH_OF_RAGNAROS     = 20566,
    SPELL_ELEMENTAL_FIRE        = 20563,                    // Aura, proc spell 20564 when doing melee damage
    SPELL_MAGMA_BLAST           = 20565,                    // Ranged attack if nobody is in melee range
    SPELL_MELT_WEAPON           = 21387,
    SPELL_RAGNA_SUBMERGE        = 21107,                    // Stealth aura
    SPELL_RAGNA_EMERGE          = 20568,                    // Emerge from lava
    SPELL_SUBMERGE_EFFECT       = 21859,                    // Make Ragnaros immune and passive while submerged
    SPELL_ELEMENTAL_FIRE_KILL   = 19773,
    SPELL_MIGHT_OF_RAGNAROS     = 21154,
    SPELL_INTENSE_HEAT          = 21155,
    SPELL_LAVA_BURST            = 21908,                    // Randomly trigger one of spells 21886, 21900 - 21907 which summons Go 178088
    SPELL_LAVA_SHIELD           = 21857                     // Son of Flame mana drain aura
};

enum Events
{
    EVENT_RAG_SUMMON_9          = 1,
    EVENT_AGGRO,
    EVENT_WRATH_OF_RAGNAROS,
    EVENT_LAVA_BURST,
    EVENT_HAMMER_OF_RAGNAROS,
    EVENT_SUBMERGE,
    EVENT_EMERGE
};

enum Phases
{
    PHASE_FIGHT                 = 1,
    PHASE_SUBMERGE,
};

enum Misc
{
    ACTION_START                = 1
};

struct boss_ragnarosAI : public BossAI
{
    boss_ragnarosAI(Creature* creature) : BossAI(creature, BOSS_RAGNAROS)
    {
        Initialize();
        _introDone = false;
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
        SetCombatMovement(false);
    }

    void Initialize()
    {
        _addCount = 0;
        _submergedOnce = false;
        _yelled = false;
    }

    void Reset() override
    {
        summons.DespawnAll();
        events.SetPhase(PHASE_FIGHT);
        me->RemoveAurasDueToSpell(SPELL_RAGNA_SUBMERGE);
        me->RemoveAurasDueToSpell(SPELL_SUBMERGE_EFFECT);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        Initialize();
        _Reset();
    }

    void EnterCombat(Unit* /*victim*/) override
    {
        _EnterCombat();
        DoCast(me, SPELL_MELT_WEAPON);
        DoCast(me, SPELL_ELEMENTAL_FIRE);
        events.SetPhase(PHASE_FIGHT);
        events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, 30000, 0, PHASE_FIGHT);
        events.ScheduleEvent(EVENT_HAMMER_OF_RAGNAROS, 11000, 0, PHASE_FIGHT);
        events.ScheduleEvent(EVENT_SUBMERGE, 180000, 0, PHASE_FIGHT);
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        if (summon->GetEntry() == NPC_SON_OF_FLAME)
        {
            summon->DespawnOrUnsummon();
            if (--_addCount == 0)
                events.RescheduleEvent(EVENT_EMERGE, std::min(1000U, events.GetTimeUntilEvent(EVENT_EMERGE)), 0, PHASE_SUBMERGE);
        }
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
        if (summon->GetEntry() == NPC_SON_OF_FLAME)
        {
            summon->CastSpell(summon, SPELL_LAVA_SHIELD, true);
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                summon->AI()->AttackStart(target);
        }
        if (summon->GetEntry() == NPC_FLAME_OF_RAGNAROS)
        {
            summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            summon->CastSpell(summon, SPELL_INTENSE_HEAT, true, nullptr, nullptr, me->GetGUID());
        }
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_START)
            events.ScheduleEvent(EVENT_RAG_SUMMON_9, 10000);
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->GetTypeId() == TYPEID_PLAYER && roll_chance_i(75))
            Talk(SAY_KILL);
    }

    void UpdateAI(uint32 diff) override
    {
        if (instance->GetBossState(BOSS_RAGNAROS) != IN_PROGRESS && !_introDone)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RAG_SUMMON_9:
                        Talk(SAY_SUMMON_RAG_3);
                        events.ScheduleEvent(EVENT_AGGRO, 3000);
                        break;
                    case EVENT_AGGRO:
                    {
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
                        _introDone = true;
                        if (Player* player = SelectTargetFromPlayerList(100.0f, 0, true))
                            AttackStart(player);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        else
        {
            if (!UpdateVictim() && !events.IsInPhase(PHASE_SUBMERGE))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_WRATH_OF_RAGNAROS:
                        Talk(SAY_WRATH);
                        DoCastAOE(SPELL_WRATH_OF_RAGNAROS);
                        events.Repeat(25000);
                        break;
                    case EVENT_LAVA_BURST:
                        DoCastAOE(SPELL_LAVA_BURST);
                        events.Repeat(urand(5000, 25000));
                        break;
                    case EVENT_HAMMER_OF_RAGNAROS:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1))
                        {
                            DoCast(target, SPELL_MIGHT_OF_RAGNAROS);
                            Talk(SAY_HAMMER);
                        }
                        events.Repeat(urand(11000, 33000));
                        break;
                    case EVENT_SUBMERGE:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_SUBMERGE);
                        events.SetPhase(PHASE_SUBMERGE);
                        for (auto itr : _sonSpawnPositions) // should be handled by spell
                        {
                            if (Creature* summon = me->SummonCreature(NPC_SON_OF_FLAME, *me))
                                summon->GetMotionMaster()->MoveJump(itr, 25.f, 25.f);
                        }
                        DoCast(me, SPELL_RAGNA_SUBMERGE, true);
                        DoCast(me, SPELL_SUBMERGE_EFFECT, true);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        Talk(_submergedOnce ? SAY_REINFORCEMENTS_2 : SAY_REINFORCEMENTS_1);
                        if(!_submergedOnce)
                            _submergedOnce = true;
                        _addCount = 8;
                        events.ScheduleEvent(EVENT_EMERGE, 90000, 0, PHASE_SUBMERGE); 
                        break;
                    case EVENT_EMERGE:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                        events.SetPhase(PHASE_FIGHT);
                        me->RemoveAurasDueToSpell(SPELL_RAGNA_SUBMERGE);
                        me->RemoveAurasDueToSpell(SPELL_SUBMERGE_EFFECT);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        events.ScheduleEvent(EVENT_SUBMERGE, 180000, 0, PHASE_FIGHT);
                        break;
                    default:
                        break;
                }
            }

            _DoMeleeAttackIfReady();
        }
    }

private:
    bool _introDone;
    bool _submergedOnce;
    bool _yelled;
    uint8 _addCount;
    Position const _sonSpawnPositions[8] = 
    {
        { 829.505f, -815.090f, -228.959f },
        { 844.504f, -814.744f, -229.959f },
        { 852.855f, -824.128f, -229.223f },
        { 855.441f, -835.294f, -228.813f },
        { 854.456f, -844.900f, -228.524f },
        { 846.322f, -850.209f, -229.208f },
        { 838.246f, -850.036f, -229.100f },
        { 824.968f, -844.214f, -229.661f }
    };
    void _DoMeleeAttackIfReady()
    {
        if (!me->isAttackReady() || events.IsInPhase(PHASE_SUBMERGE))
            return;

        Unit* victim = me->GetVictim();
        if (!victim)
            return;

        if (!me->IsWithinMeleeRange(victim) || !me->IsWithinLOSInMap(victim))
        {
            std::vector<Player*> playersAtMelee;
            Map::PlayerList const &players = me->GetMap()->GetPlayers();
            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                if (Player* player = itr->GetSource())
                    if (player->IsWithinMeleeRange(me) && player->IsWithinLOSInMap(me))
                        playersAtMelee.push_back(player);
            if (playersAtMelee.empty())
            {
                if (!_yelled)
                {
                    Talk(SAY_MAGMA_BURST);
                    _yelled = true;
                }
                DoCastVictim(SPELL_MAGMA_BLAST);
            }
            else
            {
                _yelled = false;
                Unit* target = Trinity::Containers::SelectRandomContainerElement(playersAtMelee);
                AttackStart(target);
                me->AttackerStateUpdate(target);
            }
        }
        else
        {
            _yelled = false;
            me->AttackerStateUpdate(victim);
        }

        me->resetAttackTimer();
    }
};

void AddSC_boss_ragnaros()
{
    new CreatureAILoader<boss_ragnarosAI>("boss_ragnaros");
}
