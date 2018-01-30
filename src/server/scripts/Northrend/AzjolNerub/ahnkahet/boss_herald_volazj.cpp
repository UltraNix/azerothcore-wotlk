#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ahnkahet.h"
#include "Player.h"
#include "SpellInfo.h"

enum Spells
{
    // BASIC FIGHT
    SPELL_MIND_FLAY                         = 57941,
    SPELL_MIND_FLAY_H                       = 59974,
    SPELL_SHADOW_BOLT_VOLLEY                = 57942,
    SPELL_SHADOW_BOLT_VOLLEY_H              = 59975,
    SPELL_SHIVER                            = 57949,
    SPELL_SHIVER_H                          = 59978,

    // INSANITY
    SPELL_INSANITY                          = 57496, //Dummy
    INSANITY_VISUAL                         = 57561,
    SPELL_INSANITY_TARGET                   = 57508,
    SPELL_CLONE_PLAYER                      = 57507, //casted on player during insanity
    SPELL_INSANITY_PHASING_1                = 57508,
    SPELL_INSANITY_PHASING_2                = 57509,
    SPELL_INSANITY_PHASING_3                = 57510,
    SPELL_INSANITY_PHASING_4                = 57511,
    SPELL_INSANITY_PHASING_5                = 57512
};

enum Yells
{
    SAY_AGGRO   = 0,
    SAY_SLAY    = 1,
    SAY_DEATH   = 2,
    SAY_PHASE   = 3
};

enum Misc
{
    NPC_TWISTED_VISAGE                        = 30625,
    ACHIEV_QUICK_DEMISE_START_EVENT            = 20382,
};

enum Events
{
    EVENT_HERALD_MIND_FLAY                    = 1,
    EVENT_HERALD_SHADOW                        = 2,
    EVENT_HERALD_SHIVER                        = 3,
    EVENT_HERALD_HEALTH                        = 4,
};

struct boss_volazjAI : public BossAI
{
    boss_volazjAI(Creature* creature) : BossAI(creature, BOSS_VOLAZJ) { }

    uint8 insanityTimes;
    uint8 insanityHandled;

    void Reset() override
    {
        _Reset();
        insanityTimes = insanityHandled = 0;

        // Visible for all players in insanity
        me->SetPhaseMask((1|16|32|64|128|256), true);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->SetControlled(false, UNIT_STATE_STUNNED);
        ResetPlayersPhaseMask();

        instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_QUICK_DEMISE_START_EVENT);
    }

    void SpellHitTarget(Unit* pTarget, const SpellInfo *spell) override
    {
        if (spell->Id == SPELL_INSANITY)
        {
            // Not good target or too many players
            if (pTarget->GetTypeId() != TYPEID_PLAYER || insanityHandled > 4)
                return;

            // First target - start channel visual and set self as unnattackable
            if (!insanityHandled)
            {
                me->RemoveAllAuras();
                me->CastSpell(me, INSANITY_VISUAL, true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetControlled(true, UNIT_STATE_STUNNED);
            }

            // phase mask
            pTarget->CastSpell(pTarget, SPELL_INSANITY_TARGET+insanityHandled, true);
                
            // summon twisted party members for this target
            Map::PlayerList const &players = me->GetMap()->GetPlayers();
            for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
            {
                Player *plr = i->GetSource();
                if (plr)
                    if (!plr->IsAlive() || pTarget->GetGUID() == plr->GetGUID() || plr->IsGameMaster())
                        continue;

                // Summon clone
                if (Unit* summon = me->SummonCreature(NPC_TWISTED_VISAGE, plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), plr->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 0))
                {
                    summon->AddThreat(pTarget, 0.0f);
                    summon->SetInCombatWith(pTarget);
                    pTarget->SetInCombatWith(summon);

                    plr->CastSpell(summon, SPELL_CLONE_PLAYER, true);
                    summon->SetPhaseMask(1|(1<<(4+insanityHandled)), true);
                    summon->SetUInt32Value(UNIT_FIELD_MINDAMAGE, plr->GetUInt32Value(UNIT_FIELD_MINDAMAGE));
                    summon->SetUInt32Value(UNIT_FIELD_MAXDAMAGE, plr->GetUInt32Value(UNIT_FIELD_MAXDAMAGE));
                }
            }

            ++insanityHandled;
        }
    }

    void ResetPlayersPhaseMask()
    {
        Map::PlayerList const &players = me->GetMap()->GetPlayers();
        for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
        {
            if (Player* pPlayer = i->GetSource())
                if (!pPlayer->IsGameMaster())
                    if (uint32 spellId = GetSpellForPhaseMask(pPlayer->GetPhaseMask()))
                        pPlayer->RemoveAurasDueToSpell(spellId);
        }
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();

        events.ScheduleEvent(EVENT_HERALD_MIND_FLAY, 8000);
        events.ScheduleEvent(EVENT_HERALD_SHADOW, 5000);
        events.ScheduleEvent(EVENT_HERALD_SHIVER, 15000);
        events.ScheduleEvent(EVENT_HERALD_HEALTH, 1000);

        Talk(SAY_AGGRO);

        instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_QUICK_DEMISE_START_EVENT);
    }

    void JustSummoned(Creature *summon) { summons.Summon(summon); }

    uint32 GetSpellForPhaseMask(uint32 phase)
    {
        uint32 spell = 0;
        switch (phase)
        {
            case 16:
                spell = SPELL_INSANITY_PHASING_1;
                break;
            case 32:
                spell = SPELL_INSANITY_PHASING_2;
                break;
            case 64:
                spell = SPELL_INSANITY_PHASING_3;
                break;
            case 128:
                spell = SPELL_INSANITY_PHASING_4;
                break;
            case 256:
                spell = SPELL_INSANITY_PHASING_5;
                break;
        }
        return spell;
    }

    bool CheckPhaseMinions()
    {
        summons.RemoveNotExisting();
        if (summons.empty())
        {
            ResetPlayersPhaseMask();
            return true;
        }

        uint16 phase = 1;
        for (std::list<uint64>::iterator itr = summons.begin(); itr != summons.end(); ++itr)
        {
            if (Creature *summon = ObjectAccessor::GetCreature(*me, *itr))
                phase |= summon->GetPhaseMask();
        }

        Map::PlayerList const &players = me->GetMap()->GetPlayers();
        for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
        {
            if (Player* pPlayer = i->GetSource())
                if (!pPlayer->IsGameMaster())
                    if ((pPlayer->GetPhaseMask() & phase) == 0)
                        pPlayer->RemoveAurasDueToSpell(GetSpellForPhaseMask(pPlayer->GetPhaseMask()));
        }

        return false;
    }

    void UpdateAI(uint32 diff) override
    {
        //Return since we have no target
        if (!UpdateVictim())
            return;

        if (insanityHandled)
        {
            if (!CheckPhaseMinions())
                return;

            insanityHandled = 0;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetControlled(false, UNIT_STATE_STUNNED);
            me->RemoveAurasDueToSpell(INSANITY_VISUAL);
        }

        events.Update(diff);
        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        switch (events.GetEvent())
        {
            case EVENT_HERALD_HEALTH:
            {
                if (insanityTimes == 0 && me->GetHealthPct() <= 66)
                {
                    me->CastSpell(me, SPELL_INSANITY, false);
                    insanityTimes++;
                }
                else if (insanityTimes == 1 && me->GetHealthPct() <= 33)
                {
                    me->CastSpell(me, SPELL_INSANITY, false);
                    insanityTimes++;
                }

                events.RepeatEvent(1000);
                break;
            }
            case EVENT_HERALD_MIND_FLAY:
            {
                me->CastSpell(me->GetVictim(), IsHeroic() ? SPELL_MIND_FLAY_H : SPELL_MIND_FLAY, false);
                events.RepeatEvent(20000);
                break;
            }
            case EVENT_HERALD_SHADOW:
            {
                me->CastSpell(me->GetVictim(), IsHeroic() ? SPELL_SHADOW_BOLT_VOLLEY_H : SPELL_SHADOW_BOLT_VOLLEY, false);
                events.RepeatEvent(5000);
                break;
            }
            case EVENT_HERALD_SHIVER:
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    me->CastSpell(pTarget, IsHeroic() ? SPELL_SHIVER_H : SPELL_SHIVER, false);

                events.RepeatEvent(15000);
                break;
            }
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_DEATH);

        _JustDied();

        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->SetControlled(false, UNIT_STATE_STUNNED);
        summons.DespawnAll();
        ResetPlayersPhaseMask();
    }

    void KilledUnit(Unit * /*victim*/) override
    {
        Talk(SAY_SLAY);
    }
};

void AddSC_boss_volazj()
{
    new CreatureAILoader<boss_volazjAI>("boss_volazj");
}
