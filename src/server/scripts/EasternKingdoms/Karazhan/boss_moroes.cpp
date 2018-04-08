/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "karazhan.h"
#include "Util.h"

enum MoroesYells
{
    SAY_AGGRO,
    SAY_SPECIAL,
    SAY_KILL,
    SAY_DEATH,
    SAY_OUT_OF_COMBAT,

    SAY_GUEST                       = 0
};

enum MoroesSpells
{
    SPELL_VANISH                    = 29448,
    SPELL_GARROTE                   = 37066,
    SPELL_BLIND                     = 34694,
    SPELL_GOUGE                     = 29425,
    SPELL_FRENZY                    = 37023,

    // Adds
    SPELL_MANABURN                  = 29405,
    SPELL_MIND_FLAY                 = 29570,
    SPELL_SHADOW_WORD_PAIN          = 34441,
    SPELL_SHADOWFORM                = 29406,

    SPELL_HAMMER_OF_JUSTICE         = 13005,
    SPELL_JUDGEMENT_OF_COMMAND      = 29386,
    SPELL_SEAL_OF_COMMAND           = 29385,

    SPELL_DISPELMAGIC               = 15090,
    SPELL_GREATERHEAL               = 29564,
    SPELL_HOLYFIRE                  = 29563,
    SPELL_PWSHIELD                  = 29408,

    SPELL_CLEANSE                   = 29380,
    SPELL_GREATERBLESSOFMIGHT       = 29381,
    SPELL_HOLYLIGHT                 = 29562,
    SPELL_DIVINESHIELD              = 41367,

    SPELL_HAMSTRING                 = 9080,
    SPELL_MORTALSTRIKE              = 29572,
    SPELL_WHIRLWIND                 = 29573,

    SPELL_DISARM                    = 8379,
    SPELL_HEROICSTRIKE              = 29567,
    SPELL_SHIELDBASH                = 11972,
    SPELL_SHIELDWALL                = 29390
};

enum MoroesEvents
{
    EVENT_VANISH                    = 1,
    EVENT_GARROTE,
    EVENT_BLIND,
    EVENT_GOUGE,
    EVENT_FRENZY,
    EVENT_KILL_TALK,
    EVENT_RANDOM_TALK_GUEST,
    EVENT_RANDOM_TALK,

    EVENT_MANA_BURN                 = 1,
    EVENT_MIND_FLAY,
    EVENT_SHADOW_WORD_PAIN,

    EVENT_SEAL_OF_COMMAND           = 1,
    EVENT_JUDGMENT_OF_COMMAND,
    EVENT_HAMMER_OF_JUSTICE,

    EVENT_DISPEL_MAGIC              = 1,
    EVENT_GREATER_HEAL,
    EVENT_HOLY_FIRE,
    EVENT_POWER_WORD_SHIELD,

    EVENT_CLEANSE                   = 1,
    EVENT_GREATER_BLESS,
    EVENT_HOLY_LIGHT,
    EVENT_DIVINE_SHIELD,

    EVENT_HAMSTRING                 = 1,
    EVENT_MORTAL_STRIKE,
    EVENT_WHIRLWIND,

    EVENT_DISARM                    = 1,
    EVENT_HEROIC_STRIKE,
    EVENT_SHIELD_BASH,
    EVENT_SHIELD_WALL
};

enum MoroesPhases
{
    PHASE_INTRO                     = 1,
    PHASE_FIGHT
};

struct boss_moroesAI : public BossAI
{
    boss_moroesAI(Creature* creature) : BossAI(creature, BOSS_MOROES) { }

    void Reset() override
    {
        _Reset();
        _frenzy = false;
        events.SetPhase(PHASE_INTRO);

        // Respawn adds
        std::vector<uint32> adds = { 17007, 19872, 19873, 19874, 19875, 19876 };
        std::vector<Position> spawnLocs =
        {
            { -10991.0f, -1884.33f, 81.73f, 0.614315f },
            { -10989.4f, -1885.88f, 81.73f, 0.904913f },
            { -10978.1f, -1887.07f, 81.73f, 2.035550f },
            { -10975.9f, -1885.81f, 81.73f, 2.253890f },
        };
        Trinity::Containers::RandomResize(adds, 4);
        for (auto i = 0; i < 4; ++i)
            if (auto guest = me->SummonCreature(adds[i], spawnLocs[i]))
                _guestGUIDs.push_back(guest->GetGUID());
        events.ScheduleEvent(EVENT_RANDOM_TALK_GUEST, 10s, 0, PHASE_INTRO);
    }

    Creature* GetRandomGuest() const
    {
        if (auto guest = Trinity::Containers::SelectRandomContainerElement(_guestGUIDs))
            return ObjectAccessor::GetCreature(*me, guest);
        else
            return nullptr;
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_KILL);
            events.ScheduleEvent(EVENT_KILL_TALK, 5s, 0, PHASE_FIGHT);
        }
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        summons.DoZoneInCombat();

        events.SetPhase(PHASE_FIGHT);
        events.ScheduleEvent(EVENT_VANISH, 30s, 0, PHASE_FIGHT);
        events.ScheduleEvent(EVENT_BLIND, 20s, 0, PHASE_FIGHT);
        events.ScheduleEvent(EVENT_GOUGE, 13s, 0, PHASE_FIGHT);
    }

    void DamageTaken(Unit* /*attacker*/, uint32 &damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*mask*/) override
    {
        if (!_frenzy && me->HealthBelowPctDamaged(30, damage))
        {
            _frenzy = true;
            events.ScheduleEvent(EVENT_FRENZY, 0s, 0, PHASE_FIGHT);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_GARROTE);
        _JustDied();
        Talk(SAY_DEATH);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() && !events.IsInPhase(PHASE_INTRO))
            return;

        events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_RANDOM_TALK_GUEST:
                    if (Creature* guest = GetRandomGuest())
                        if (guest->IsAIEnabled)
                            guest->AI()->Talk(SAY_GUEST);
                    events.ScheduleEvent(EVENT_RANDOM_TALK, 5s, 0, PHASE_INTRO);
                    break;
                case EVENT_RANDOM_TALK:
                    Talk(SAY_OUT_OF_COMBAT);
                    events.ScheduleEvent(EVENT_RANDOM_TALK_GUEST, 1min, 2min, 0, PHASE_INTRO);
                    break;
                case EVENT_VANISH:
                    events.DelayEvents(9s);
                    DoCastSelf(SPELL_VANISH);
                    events.Repeat(30s);
                    events.ScheduleEvent(EVENT_GARROTE, 5s, 7s, 0, PHASE_FIGHT);
                    break;
                case EVENT_GARROTE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        DoCast(target, SPELL_GARROTE, true);
                    break;
                case EVENT_BLIND:
                    if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0, [&](Unit* tar) -> bool
                    {
                        if (Unit* victim = me->GetVictim())
                            return tar->IsPlayer() && tar != victim;
                        else
                            return true;
                    }))
                        DoCast(target, SPELL_BLIND);
                    events.Repeat(25s, 40s);
                    break;
                case EVENT_GOUGE:
                    DoCastVictim(SPELL_GOUGE);
                    if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 1))
                        AttackStart(target);
                    events.Repeat(25s, 40s);
                    break;
                case EVENT_FRENZY:
                    DoCastSelf(EVENT_FRENZY);
                    break;
                default:
                    break;
            }

            if (me->IsCasting())
                return;
        }

        DoMeleeAttackIfReady();
    }

    private:
        std::vector<uint64> _guestGUIDs;
        bool _frenzy;
};

struct npc_moroes_guestAI : public ScriptedAI
{
    npc_moroes_guestAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _events.Reset();
    }

    virtual void DoEvent(uint32 eventId) = 0;

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            DoEvent(eventId);
            if (me->IsCasting())
                return;
        }

        DoMeleeAttackIfReady();
    }

    protected:
        EventMap _events;
};

struct boss_baroness_dorothea_millstipeAI : public npc_moroes_guestAI
{
    boss_baroness_dorothea_millstipeAI(Creature* creature) : npc_moroes_guestAI(creature) { }

    void Reset() override
    {
        npc_moroes_guestAI::Reset();
        DoCastSelf(SPELL_SHADOWFORM, true);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_MANA_BURN, 7s);
        _events.ScheduleEvent(EVENT_MIND_FLAY, 1s);
        _events.ScheduleEvent(EVENT_SHADOW_WORD_PAIN, 6s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_MANA_BURN:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, [&](Unit* tar) { return tar->IsInRange(me, 0.0f, 30.0f) && tar->getPowerType() == POWER_MANA; }))
                    DoCast(target, SPELL_MANABURN);
                _events.Repeat(5s);
                break;
            case EVENT_MIND_FLAY:
                DoCastVictim(SPELL_MIND_FLAY);
                _events.Repeat(12s);
                break;
            case EVENT_SHADOW_WORD_PAIN:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    DoCast(target, SPELL_SHADOW_WORD_PAIN);
                _events.Repeat(7s);
                break;
            default:
                break;
        }
    }
};

struct boss_baron_rafe_dreugerAI : public npc_moroes_guestAI
{
    boss_baron_rafe_dreugerAI(Creature* creature) : npc_moroes_guestAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_HAMMER_OF_JUSTICE, 1s);
        _events.ScheduleEvent(EVENT_SEAL_OF_COMMAND, 7s);
        _events.ScheduleEvent(EVENT_JUDGMENT_OF_COMMAND, 36s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_HAMMER_OF_JUSTICE:
                DoCastVictim(SPELL_HAMMER_OF_JUSTICE);
                _events.Repeat(12s);
                break;
            case EVENT_SEAL_OF_COMMAND:
                DoCastSelf(SPELL_SEAL_OF_COMMAND);
                _events.Repeat(32s);
                _events.RescheduleEvent(EVENT_JUDGMENT_OF_COMMAND, 29s);
                break;
            case EVENT_JUDGMENT_OF_COMMAND:
                DoCastVictim(SPELL_JUDGEMENT_OF_COMMAND);
                _events.Repeat(29s);
                break;
            default:
                break;
        }
    }
};

struct boss_lady_catriona_von_indiAI : public npc_moroes_guestAI
{
    boss_lady_catriona_von_indiAI(Creature* creature) : npc_moroes_guestAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_DISPEL_MAGIC, 11s);
        _events.ScheduleEvent(EVENT_GREATER_HEAL, 1.5s);
        _events.ScheduleEvent(EVENT_HOLY_FIRE, 5s);
        _events.ScheduleEvent(EVENT_POWER_WORD_SHIELD, 1s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_DISPEL_MAGIC:
            {
                std::list<Creature*> creatureList = DoFindFriendlyMissingBuff(30.0f, 0);
                if (!creatureList.empty())
                {
                    auto min = std::min_element(creatureList.begin(), creatureList.end(), [](const Creature* a, const Creature* b) { return a->GetHealthPct() < b->GetHealthPct(); });
                    if (roll_chance_f(100.0f - (*min)->GetHealthPct()))
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                            DoCast(target, SPELL_DISPELMAGIC);
                    }
                    else
                        DoCast(*min, SPELL_DISPELMAGIC);
                }
                _events.Repeat(25s);
                break;
            }
            case EVENT_GREATER_HEAL:
                if (Unit* target = DoSelectLowestHpFriendly(40.0f, 500))
                    DoCast(target, SPELL_GREATERHEAL);
                _events.Repeat(17s);
                break;
            case EVENT_HOLY_FIRE:
                DoCastVictim(SPELL_HOLYFIRE);
                _events.Repeat(22s);
                break;
            case EVENT_POWER_WORD_SHIELD:
                if (Unit* target = DoSelectLowestHpFriendly(40.0f, 500))
                    DoCast(target, SPELL_PWSHIELD);
                _events.Repeat(15s);
                break;
            default:
                break;
        }
    }
};

struct boss_lady_keira_berrybuckAI : public npc_moroes_guestAI
{
    boss_lady_keira_berrybuckAI(Creature* creature) : npc_moroes_guestAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_CLEANSE, 13s);
        _events.ScheduleEvent(EVENT_GREATER_BLESS, 1s);
        _events.ScheduleEvent(EVENT_HOLY_LIGHT, 7s);
        _events.ScheduleEvent(EVENT_DIVINE_SHIELD, 31s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CLEANSE:
            {
                std::list<Creature*> creatureList = DoFindFriendlyMissingBuff(30.0f, 0);
                if (!creatureList.empty())
                    if (Unit* target = Trinity::Containers::SelectRandomContainerElement(creatureList))
                        DoCast(target, SPELL_CLEANSE);
                _events.Repeat(10s);
                break;
            }
            case EVENT_GREATER_BLESS:
            {
                std::list<Creature*> creatureList = DoFindFriendlyMissingBuff(30.0f, SPELL_GREATERBLESSOFMIGHT);
                if (!creatureList.empty())
                    if (Unit* target = Trinity::Containers::SelectRandomContainerElement(creatureList))
                        DoCast(target, SPELL_GREATERBLESSOFMIGHT);
                _events.Repeat(50s);
                break;
            }
            case EVENT_HOLY_LIGHT:
                if (Unit* target = DoSelectLowestHpFriendly(40.0f, 4625))
                    DoCast(target, SPELL_HOLYLIGHT);
                _events.Repeat(10s);
                break;
            case EVENT_DIVINE_SHIELD:
                DoCastSelf(SPELL_DIVINESHIELD);
                _events.Repeat(31s);
                break;
            default:
                break;
        }
    }
};

struct boss_lord_robin_darisAI : public npc_moroes_guestAI
{
    boss_lord_robin_darisAI(Creature* creature) : npc_moroes_guestAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_HAMSTRING, 7s);
        _events.ScheduleEvent(EVENT_MORTAL_STRIKE, 10s);
        _events.ScheduleEvent(EVENT_WHIRLWIND, 21s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_HAMSTRING:
                DoCastVictim(SPELL_HAMSTRING);
                _events.Repeat(12s);
                break;
            case EVENT_MORTAL_STRIKE:
                DoCastVictim(SPELL_MORTALSTRIKE);
                _events.Repeat(18s);
                break;
            case EVENT_WHIRLWIND:
                DoCastSelf(SPELL_WHIRLWIND);
                _events.Repeat(21s);
                break;
            default:
                break;
        }
    }
};

struct boss_lord_crispin_ferenceAI : public npc_moroes_guestAI
{
    boss_lord_crispin_ferenceAI(Creature* creature) : npc_moroes_guestAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_DISARM, 6s);
        _events.ScheduleEvent(EVENT_HEROIC_STRIKE, 10s);
        _events.ScheduleEvent(EVENT_SHIELD_BASH, 8s);
        _events.ScheduleEvent(EVENT_SHIELD_WALL, 4s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_DISARM:
                DoCastVictim(SPELL_DISARM);
                _events.Repeat(12s);
                break;
            case EVENT_HEROIC_STRIKE:
                DoCastVictim(SPELL_HEROICSTRIKE);
                _events.Repeat(10s);
                break;
            case EVENT_SHIELD_BASH:
                DoCastVictim(SPELL_SHIELDBASH);
                _events.Repeat(13s);
                break;
            case EVENT_SHIELD_WALL:
                DoCastSelf(SPELL_SHIELDWALL);
                _events.Repeat(21s);
                break;
            default:
                break;
        }
    }
};

void AddSC_boss_moroes()
{
    new CreatureAILoader<boss_moroesAI>("boss_moroes");
    new CreatureAILoader<boss_baroness_dorothea_millstipeAI>("boss_baroness_dorothea_millstipe");
    new CreatureAILoader<boss_baron_rafe_dreugerAI>("boss_baron_rafe_dreuger");
    new CreatureAILoader<boss_lady_catriona_von_indiAI>("boss_lady_catriona_von_indi");
    new CreatureAILoader<boss_lady_keira_berrybuckAI>("boss_lady_keira_berrybuck");
    new CreatureAILoader<boss_lord_robin_darisAI>("boss_lord_robin_daris");
    new CreatureAILoader<boss_lord_crispin_ferenceAI>("boss_lord_crispin_ference");
}
