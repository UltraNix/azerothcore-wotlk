#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "molten_core.h"

enum Texts
{
    EMOTE_FRENZY        = 0
};

enum Spells
{
    SPELL_FRENZY        = 19451,
    SPELL_MAGMA_SPIT    = 19449,
    SPELL_PANIC         = 19408,
    SPELL_LAVA_BOMB     = 19411,
    SPELL_SUMMON_FLAME  = 20494
};

enum Events
{
    EVENT_FRENZY        = 1,
    EVENT_PANIC,
    EVENT_LAVA_BOMB
};

struct boss_magmadarAI : public BossAI
{
    boss_magmadarAI(Creature* creature) : BossAI(creature, BOSS_MAGMADAR) { }

    void Reset() override
    {
        _Reset();
        DoCast(me, SPELL_MAGMA_SPIT, true);
    }

    void EnterCombat(Unit* /*victim*/) override
    {
        _EnterCombat();
        events.ScheduleEvent(EVENT_FRENZY, 30000);
        events.ScheduleEvent(EVENT_PANIC, 7000);
        events.ScheduleEvent(EVENT_LAVA_BOMB, 12000);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        while (uint32 eventId = events.GetEvent())
        {
            switch (eventId)
            {
                case EVENT_FRENZY:
                    Talk(EMOTE_FRENZY);
                    DoCast(me, SPELL_FRENZY);
                    events.RepeatEvent(urand(15000, 20000));
                    break;
                case EVENT_PANIC:
                    DoCastVictim(SPELL_PANIC);
                    events.RepeatEvent(urand(30000, 40000));
                    break;
                case EVENT_LAVA_BOMB:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        DoCast(target, SPELL_LAVA_BOMB);
                    events.RepeatEvent(urand(12000, 15000));
                    break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }
};

class spell_magmadar_lava_bomb_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_magmadar_lava_bomb_SpellScript);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        ValidateSpellInfo({ SPELL_LAVA_BOMB, SPELL_SUMMON_FLAME });
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            target->CastSpell(target, SPELL_SUMMON_FLAME, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_magmadar_lava_bomb_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_boss_magmadar()
{
    new CreatureAILoader<boss_magmadarAI>("boss_magmadar");
    new SpellScriptLoaderEx<spell_magmadar_lava_bomb_SpellScript>("spell_magmadar_lava_bomb");
}
