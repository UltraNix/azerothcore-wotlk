
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Spell.h"
#include "zulgurub.h"
#include "Player.h"

enum Says
{
    SAY_VENOXIS_TRANSFORM           = 1,        // Let the coils of hate unfurl!
    SAY_VENOXIS_DEATH                           // Ssserenity.. at lassst!
};

enum Spells
{

    // troll form
    SPELL_DISPEL_MAGIC              = 23859,
    SPELL_RENEW                     = 23895,
    SPELL_HOLY_NOVA                 = 23858,
    SPELL_HOLY_FIRE                 = 23860,
    SPELL_HOLY_WRATH                = 23979,
    // snake form
    SPELL_THRASH                    = 3391,
    SPELL_POISON_CLOUD              = 23861,
    SPELL_VENOM_SPIT                = 23862,

    SPELL_PARASITIC_SERPENT         = 23865,
    SPELL_SUMMON_PARASITIC_SERPENT  = 23866,
    SPELL_PARASITIC_SERPENT_TRIGGER = 23867,
    // used when swapping event-stages
    SPELL_VENOXIS_TRANSFORM         = 23849,    // 50% health - shapechange to cobra
    SPELL_FRENZY                    = 8269      // 20% health - frenzy
};

enum Events
{
    // troll form
    EVENT_DISPEL_MAGIC              = 1,
    EVENT_RENEW,
    EVENT_HOLY_NOVA,
    EVENT_HOLY_FIRE,
    EVENT_HOLY_WRATH,
    // snake form events
    EVENT_THRASH,
    EVENT_POISON_CLOUD,
    EVENT_VENOM_SPIT,
    EVENT_PARASITIC_SERPENT
};

enum Phases
{
    PHASE_ONE                       = 1,    // troll form
    PHASE_TWO                               // snake form
};

struct boss_venoxisAI : public BossAI
{
    boss_venoxisAI(Creature* creature) : BossAI(creature, DATA_VENOXIS) { }

    void Reset()
    {
        _Reset();
        // set some internally used variables to their defaults
        _transformed = false;
        _frenzied = false;
        events.SetPhase(PHASE_ONE);
    }

    void JustDied(Unit* /*killer*/)
    {
        _JustDied();
        Talk(SAY_VENOXIS_DEATH);
    }

    void EnterCombat(Unit* /*who*/)
    {
        _EnterCombat();
        // Phase one events (regular form)
        events.SetPhase(PHASE_ONE);
        events.ScheduleEvent(EVENT_HOLY_NOVA, 7500, 0, PHASE_ONE);
        events.ScheduleEvent(EVENT_DISPEL_MAGIC, 35000, 0, PHASE_ONE);
        events.ScheduleEvent(EVENT_HOLY_FIRE, 10000, 0, PHASE_ONE);
        events.ScheduleEvent(EVENT_RENEW, 30500, 0, PHASE_ONE);
        events.ScheduleEvent(EVENT_HOLY_WRATH, 30000, 0, PHASE_ONE);
    }

    uint8 GetMeleePlayersCount()
    {
        uint8 counter = 0;
        Map::PlayerList const &players = me->GetMap()->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
            if (Player* player = itr->GetSource())
                if (player->IsWithinMeleeRange(me))
                    ++counter;
        return counter;
    }

    void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask)
    {
        // check if venoxis is ready to transform
        if (!_transformed && me->HealthBelowPctDamaged(50, damage))
        {
            _transformed = true;
            DoCast(me, SPELL_VENOXIS_TRANSFORM);
            Talk(SAY_VENOXIS_TRANSFORM);
            DoResetThreat();

            // phase two events (snakeform)
            events.SetPhase(PHASE_TWO);
            events.ScheduleEvent(EVENT_THRASH, 5000, 0, PHASE_TWO);
            events.ScheduleEvent(EVENT_VENOM_SPIT, 5500, 0, PHASE_TWO);
            events.ScheduleEvent(EVENT_POISON_CLOUD, 2000, 0, PHASE_TWO);
            events.ScheduleEvent(EVENT_PARASITIC_SERPENT, 10000, 0, PHASE_TWO);
        }
        // we're losing health, bad, go frenzy
        else if (!_frenzied && me->HealthBelowPctDamaged(20, damage))
        {
            _frenzied = true;
            DoCast(me, SPELL_FRENZY, true);
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            // troll form spells and Actions (first part)
            case EVENT_DISPEL_MAGIC:
                DoCast(me, SPELL_DISPEL_MAGIC);
                events.ScheduleEvent(EVENT_DISPEL_MAGIC, urand(16000, 18000), 0, PHASE_ONE);
                break;
            case EVENT_RENEW:
                DoCast(me, SPELL_RENEW);
                events.ScheduleEvent(EVENT_RENEW, urand(20000, 22000), 0, PHASE_ONE);
                break;
            case EVENT_HOLY_NOVA:
                if (GetMeleePlayersCount() >= 3)
                    DoCast(me, SPELL_HOLY_NOVA);

                events.ScheduleEvent(EVENT_HOLY_NOVA, urand(14000, 16000), 0, PHASE_ONE);
                break;
            case EVENT_HOLY_FIRE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                    DoCast(target, SPELL_HOLY_FIRE);
                events.ScheduleEvent(EVENT_HOLY_FIRE, urand(8000, 12000), 0, PHASE_ONE);
                break;
            case EVENT_HOLY_WRATH:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                    DoCast(target, SPELL_HOLY_WRATH);
                events.ScheduleEvent(EVENT_HOLY_WRATH, urand(15000, 25000), 0, PHASE_ONE);
                break;
            // snake form spells and Actions              
            case EVENT_THRASH:
                DoCast(me, SPELL_THRASH);
                events.Repeat(urand(10000, 20000));
                break;
            case EVENT_VENOM_SPIT:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                    DoCast(target, SPELL_VENOM_SPIT);
                events.ScheduleEvent(EVENT_VENOM_SPIT, urand(15000, 20000), 0, PHASE_TWO);
                break;
            case EVENT_POISON_CLOUD:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                    DoCast(target, SPELL_POISON_CLOUD);
                events.ScheduleEvent(EVENT_POISON_CLOUD, urand(7000, 10000), 0, PHASE_TWO);
                break;
            case EVENT_PARASITIC_SERPENT:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                    DoCast(target, SPELL_SUMMON_PARASITIC_SERPENT);
                events.ScheduleEvent(EVENT_PARASITIC_SERPENT, 10000, 0, PHASE_TWO);
                break;
            default:
                break;
        }
    }

private:
    bool _transformed;
    bool _frenzied;
};

void AddSC_boss_venoxis()
{
    new CreatureAILoader<boss_venoxisAI>("boss_venoxis");
}
