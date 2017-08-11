#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "ulduar.h"
#include "Player.h"

enum AuriayaSpells
{
    // BASIC
    SPELL_TERRIFYING_SCREECH               = 64386,
    SPELL_SENTINEL_BLAST_10                = 64389,
    SPELL_SENTINEL_BLAST_25                = 64678,
    SPELL_SONIC_SCREECH_10                 = 64422,
    SPELL_SONIC_SCREECH_25                 = 64688,
    SPELL_GUARDIAN_SWARM                   = 64396,
    SPELL_ENRAGE                           = 47008,
    SPELL_ACTIVATE_FERAL_DEFENDER          = 64449,

    // Sanctum Sentry
    SPELL_SAVAGE_POUNCE_10                = 64666,
    SPELL_SAVAGE_POUNCE_25                = 64374,
    SPELL_RIP_FLESH_10                    = 64375,
    SPELL_RIP_FLESH_25                    = 64667,
    SPELL_STRENGTH_OF_THE_PACK            = 64369,

    // Feral Defender
    SPELL_FERAL_ESSENCE                   = 64455,
    SPELL_FERAL_POUNCE_10                 = 64478,
    SPELL_FERAL_POUNCE_25                 = 64669,
    SPELL_FERAL_RUSH_10                   = 64496,
    SPELL_FERAL_RUSH_25                   = 64674,
    //SPELL_SEEPING_FERAL_ESSENCE_SUMMON  = 64457,
    SPELL_SEEPING_FERAL_ESSENCE_25        = 64676,
    SPELL_SEEPING_FERAL_ESSENCE_10        = 64458,
};

#define SPELL_SONIC_SCREECH               RAID_MODE(SPELL_SONIC_SCREECH_10, SPELL_SONIC_SCREECH_25)
#define SPELL_SENTINEL_BLAST              RAID_MODE(SPELL_SENTINEL_BLAST_10, SPELL_SENTINEL_BLAST_25)
#define SPELL_SAVAGE_POUNCE               RAID_MODE(SPELL_SAVAGE_POUNCE_10, SPELL_SAVAGE_POUNCE_25)
#define SPELL_RIP_FLESH                   RAID_MODE(SPELL_RIP_FLESH_10, SPELL_RIP_FLESH_25)
#define SPELL_FERAL_POUNCE                RAID_MODE(SPELL_FERAL_POUNCE_10, SPELL_FERAL_POUNCE_25)
#define SPELL_FERAL_RUSH                  RAID_MODE(SPELL_FERAL_RUSH_10, SPELL_FERAL_RUSH_25)
#define SPELL_SEEPING_FERAL_ESSENCE       RAID_MODE(SPELL_SEEPING_FERAL_ESSENCE_10, SPELL_SEEPING_FERAL_ESSENCE_25)

enum AuriayaNPC
{
    NPC_FERAL_DEFENDER                    = 34035,
    NPC_SANCTUM_SENTRY                    = 34014,
    NPC_SEEPING_FERAL_ESSENCE             = 34098,
};

enum AuriayaEvents
{
    EVENT_SUMMON_FERAL_DEFENDER           = 1,
    EVENT_TERRIFYING_SCREECH              = 2,
    EVENT_SONIC_SCREECH                   = 3,
    EVENT_GUARDIAN_SWARM                  = 4,
    EVENT_SENTINEL_BLAST                  = 5,
    EVENT_REMOVE_IMMUNE                   = 6,

    EVENT_RESPAWN_FERAL_DEFENDER          = 9,
    EVENT_ENRAGE                          = 10,
};

enum AuriayaSounds
{
    SOUND_AGGRO                           = 15473,
    SOUND_SLAY1                           = 15474,
    SOUND_SLAY2                           = 15475,
    SOUND_DEATH                           = 15476,
    SOUND_BERSERK                         = 15477,
    SOUND_WOUND                           = 15478,
};

enum Misc
{
    ACTION_FERAL_RESPAWN                  = 1,
    ACTION_FERAL_DEATH                    = 2,
    ACTION_DESPAWN_ADDS                   = 3,
    ACTION_FERAL_DEATH_WITH_STACK         = 4,

    DATA_CRAZY_CAT                        = 10,
    DATA_NINE_LIVES                       = 11,
};

struct boss_auriayaAI : BossAI
{
    explicit boss_auriayaAI(Creature* creature) : BossAI(creature, TYPE_AURIAYA), _feralDied(false), _nineLives(false) {}

    void Reset() override
    {
        _Reset();
        _feralDied = false;
        _nineLives = false;

        EntryCheckPredicate pred(NPC_FERAL_DEFENDER);
        summons.DoAction(ACTION_DESPAWN_ADDS, pred);
        summons.DespawnAll();

        instance->SetData(TYPE_AURIAYA, NOT_STARTED);

        for (uint8 i = 0; i < RAID_MODE(2,4); ++i)
            me->SummonCreature(NPC_SANCTUM_SENTRY, me->GetPositionX() + frand(4.0f, 12.0f), me->GetPositionY() + frand(4.0f, 12.0f), me->GetPositionZ());
                
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
    }

    uint32 GetData(uint32 param) const override
    {
        if (param == DATA_CRAZY_CAT)
            return !_feralDied;
        else if (param == DATA_NINE_LIVES)
            return _nineLives;

        return 0;
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_SANCTUM_SENTRY)
            summon->GetMotionMaster()->MoveFollow(me, 6, Position::RandomOrientation());
        else
            summon->SetInCombatWithZone();

        summons.Summon(summon);
    }

    void EnterEvadeMode() override
    {
        instance->SetData(TYPE_AURIAYA, FAIL);
        _DespawnAtEvade();
    }

    void SummonedCreatureDies(Creature* summon, Unit*) override
    {
        if (summon->GetEntry() == NPC_SANCTUM_SENTRY)
            _feralDied = true;
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        instance->SetData(TYPE_AURIAYA, IN_PROGRESS);

        events.ScheduleEvent(EVENT_TERRIFYING_SCREECH, 35000);
        events.ScheduleEvent(EVENT_SONIC_SCREECH, 45000);
        events.ScheduleEvent(EVENT_GUARDIAN_SWARM, 70000);
        events.ScheduleEvent(EVENT_SUMMON_FERAL_DEFENDER, 60000);
        events.ScheduleEvent(EVENT_SENTINEL_BLAST, 36000);
        events.ScheduleEvent(EVENT_ENRAGE, 600000);

        summons.DoZoneInCombat(NPC_SANCTUM_SENTRY);

        me->MonsterYell("Some things are better left alone!", LANG_UNIVERSAL, nullptr);
        me->PlayDirectSound(SOUND_AGGRO);
    }

    void KilledUnit(Unit* victim) override
    {
        if (!victim->IsPlayer())
            return;

        if (urand(0,1))
        {
            me->MonsterYell("The secret dies with you!", LANG_UNIVERSAL, nullptr);
            me->PlayDirectSound(SOUND_SLAY1);
        }
        else
        {
            me->MonsterYell("There is no escape!", LANG_UNIVERSAL, nullptr);
            me->PlayDirectSound(SOUND_SLAY2);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        instance->SetData(TYPE_AURIAYA, DONE);

        EntryCheckPredicate pred(NPC_FERAL_DEFENDER);
        summons.DoAction(ACTION_DESPAWN_ADDS, pred);
        _JustDied();
        me->MonsterTextEmote("Auriaya screams in agony.", nullptr);
        me->PlayDirectSound(SOUND_DEATH);
    }

    void DoAction(int32 param) override
    {
        if (param == ACTION_FERAL_DEATH_WITH_STACK)
            events.ScheduleEvent(EVENT_RESPAWN_FERAL_DEFENDER, 25000);
        else if (param == ACTION_FERAL_DEATH)
            _nineLives = true;
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch(eventId)
        {
            case EVENT_SUMMON_FERAL_DEFENDER:
                me->MonsterTextEmote("Auriaya begins to activate Feral Defender.", nullptr, true);
                DoCastSelf(SPELL_ACTIVATE_FERAL_DEFENDER, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
                events.ScheduleEvent(EVENT_REMOVE_IMMUNE, 3000);
                break;
            case EVENT_REMOVE_IMMUNE:
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                break;
            case EVENT_TERRIFYING_SCREECH:
                me->MonsterTextEmote("Auriaya begins to cast Terrifying Screech.", nullptr, true);
                DoCastSelf(SPELL_TERRIFYING_SCREECH);
                events.Repeat(35000);
                break;
            case EVENT_SONIC_SCREECH:
                DoCastSelf(SPELL_SONIC_SCREECH);
                events.Repeat(50000);
                break;
            case EVENT_GUARDIAN_SWARM:
                DoCastVictim(SPELL_GUARDIAN_SWARM);
                events.Repeat(40000);
                break;
            case EVENT_SENTINEL_BLAST:
                DoCastSelf(SPELL_SENTINEL_BLAST);
                events.Repeat(35000);
                events.DelayEvents(5000, 0);
                break;
            case EVENT_RESPAWN_FERAL_DEFENDER:
            {
                EntryCheckPredicate pred(NPC_FERAL_DEFENDER);
                summons.DoAction(ACTION_FERAL_RESPAWN, pred);
                break;
            }
            case EVENT_ENRAGE:
                me->MonsterTextEmote("You waste my time!", nullptr);
                me->PlayDirectSound(SOUND_BERSERK);
                DoCastSelf(SPELL_ENRAGE, true);
                break;
            default:
                break;
        }
    }

private:
    bool _feralDied;
    bool _nineLives;
};

enum Sentry
{
    EVENT_SAVAGE_POUNCE = 1,
    EVENT_RIP_FLESH 
};

struct npc_auriaya_sanctum_sentryAI : ScriptedAI
{
    explicit npc_auriaya_sanctum_sentryAI(Creature* creature) : ScriptedAI(creature), _savagePounceTimer(5000), _ripFleshTimer(0) { }

    uint32 _savagePounceTimer;
    uint32 _ripFleshTimer;

    void EnterCombat(Unit* /*attacker*/) override
    {
        if (me->GetInstanceScript())
            if (auto cr = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_AURIAYA)))
                cr->SetInCombatWithZone();
    }

    void Reset() override
    {
        _events.ScheduleEvent(EVENT_SAVAGE_POUNCE, 0);
        _events.ScheduleEvent(EVENT_RIP_FLESH, 10000);

        DoCastSelf(SPELL_STRENGTH_OF_THE_PACK, true);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        while(uint32 eventId = _events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_SAVAGE_POUNCE:
                    if(auto victim = me->GetVictim())
                    {
                        if (me->IsInRange(victim, 8.0f, 25.0f) && me->IsWithinLOSInMap(victim))
                        {
                            DoCastVictim(SPELL_SAVAGE_POUNCE);
                            _events.Repeat(5000);
                            break;
                        }
                    }
                    _events.Repeat(200);
                    break;
                case EVENT_RIP_FLESH:
                    DoCastVictim(SPELL_RIP_FLESH);
                    _events.Repeat(10000); 
                    break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
};

enum Defender
{
    EVENT_FERAL_RUSH    = 1,
    EVENT_FERAL_POUNCE,
};

struct npc_auriaya_feral_defenderAI : ScriptedAI
{
    explicit npc_auriaya_feral_defenderAI(Creature* creature) : ScriptedAI(creature), _feralEssenceStack(8), summons(creature) { }

    void Reset() override
    {
        summons.DespawnAll();
        _events.ScheduleEvent(EVENT_FERAL_RUSH, 3000);
        _events.ScheduleEvent(EVENT_FERAL_POUNCE, 6000);
        _feralEssenceStack = 8;

        if (auto aur = me->AddAura(SPELL_FERAL_ESSENCE, me))
            aur->SetStackAmount(_feralEssenceStack);
    }

    void JustDied(Unit*) override
    {
        // inform about our death, start timer
        if (me->GetInstanceScript())
            if (auto auriaya = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(TYPE_AURIAYA)))
                if (auriaya->IsAIEnabled)
                    auriaya->AI()->DoAction(_feralEssenceStack ? ACTION_FERAL_DEATH_WITH_STACK : ACTION_FERAL_DEATH);

        if (_feralEssenceStack)
        {
            if (Creature *cr = me->SummonCreature(NPC_SEEPING_FERAL_ESSENCE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f))
                summons.Summon(cr);

            --_feralEssenceStack;
        }
    }

    void DoAction(int32 param) override
    {
        if (param == ACTION_FERAL_RESPAWN)
        {
            me->setDeathState(JUST_RESPAWNED);

            if (auto target = SelectTargetFromPlayerList(200.0f))
                AttackStart(target);
            else
            {
                summons.DespawnAll();
                me->DespawnOrUnsummon(1);
            }

            if (_feralEssenceStack)
                if (auto aur = me->AddAura(SPELL_FERAL_ESSENCE, me))
                    aur->SetStackAmount(_feralEssenceStack);
        }
        else if (param == ACTION_DESPAWN_ADDS)
            summons.DespawnAll();
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        while(auto eventId = _events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_FERAL_RUSH:
                    DoResetThreat();
                    if (!UpdateVictim())
                        return;

                    DoCastVictim(SPELL_FERAL_RUSH, true);
                    _events.Repeat(6000);
                    break;
                case EVENT_FERAL_POUNCE:
                    DoCastVictim(SPELL_FERAL_POUNCE);
                    _events.Repeat(6000);
                    break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
    uint8 _feralEssenceStack;
    SummonList summons;
};

class spell_auriaya_sentinel_blast_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_auriaya_sentinel_blast_SpellScript);

    bool Validate(const SpellInfo* spellInfo) override
    {
        return ValidateSpellInfo({ SPELL_SENTINEL_BLAST_10, SPELL_SENTINEL_BLAST_25 });
    }

    void FilterTargets(std::list<WorldObject*>& unitList)
    {
        unitList.remove_if(PlayerOrPetCheck());
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_auriaya_sentinel_blast_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

class achievement_auriaya_crazy_cat_lady : public AchievementCriteriaScript
{
    public:
        achievement_auriaya_crazy_cat_lady() : AchievementCriteriaScript("achievement_auriaya_crazy_cat_lady") {}

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            if (target)
                if (auto instance = target->GetInstanceScript())
                    if (auto cr = ObjectAccessor::GetCreature(*target, instance->GetData64(TYPE_AURIAYA)))
                        if (cr->IsAIEnabled)
                            return cr->AI()->GetData(DATA_CRAZY_CAT);
                        
            return false;
        }
};

class achievement_auriaya_nine_lives : public AchievementCriteriaScript
{
    public:
        achievement_auriaya_nine_lives() : AchievementCriteriaScript("achievement_auriaya_nine_lives") {}

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            if (target)
                if (auto instance = target->GetInstanceScript())
                    if (auto cr = ObjectAccessor::GetCreature(*target, instance->GetData64(TYPE_AURIAYA)))
                        if (cr->IsAIEnabled)
                            return cr->AI()->GetData(DATA_NINE_LIVES);

            return false;
        }
};

void AddSC_boss_auriaya()
{
    new CreatureAILoader<boss_auriayaAI>("boss_auriaya");
    new CreatureAILoader<npc_auriaya_sanctum_sentryAI>("npc_auriaya_sanctum_sentry");
    new CreatureAILoader<npc_auriaya_feral_defenderAI>("npc_auriaya_feral_defender");

    new SpellScriptLoaderEx<spell_auriaya_sentinel_blast_SpellScript>("spell_auriaya_sentinel_blast");

    new achievement_auriaya_crazy_cat_lady();
    new achievement_auriaya_nine_lives();
}
