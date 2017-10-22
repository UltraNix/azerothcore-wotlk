/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "vault_of_archavon.h"
#include "SpellAuras.h"
#include "SpellScript.h"

enum Events
{
    // Koralon
    EVENT_BURNING_BREATH            = 1,
    EVENT_FLAME_CINDER                = 2,
    EVENT_METEOR_FISTS                = 3,
    EVENT_RESTORE_ORIENTATION         = 4
};

enum Spells
{
    SPELL_BURNING_FURY                          = 68168,
    SPELL_BURNING_BREATH                        = 66665, // handled by spell_difficulty
    
    SPELL_FLAMING_CINDER                        = 66681,
    SPELL_FLAMING_CINDER_DUMMY                    = 66690,
    SPELL_FLAMING_CINDER_MISSILE                = 66682, // trigger of missile handled by spell_difficulty

    SPELL_METEOR_FISTS                          = 66725, // handled by spell_difficulty
    SPELL_METEOR_FISTS_DAMAGE                   = 66765,
    SPELL_FW_METEOR_FISTS_DAMAGE                = 66809
};

class boss_koralon : public CreatureScript
{
    public:
        boss_koralon() : CreatureScript("boss_koralon") { }

        struct boss_koralonAI : public ScriptedAI
        {
            boss_koralonAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void Reset() override
            {
                me->DisableRotate(false);
                events.Reset();
                if (instance)
                {
                    if (instance->GetData(DATA_STONED))
                    {
                        if (Aura* aur = me->AddAura(SPELL_STONED_AURA, me))
                        {
                            aur->SetMaxDuration(60 * MINUTE* IN_MILLISECONDS);
                            aur->SetDuration(60 * MINUTE* IN_MILLISECONDS);
                        }
                    }
                    instance->SetData(EVENT_KORALON, NOT_STARTED);
                }
            }

            void AttackStart(Unit* who) override
            {
                if (me->HasAura(SPELL_STONED_AURA))
                    return;

                ScriptedAI::AttackStart(who);
            }

            void EnterCombat(Unit* /*who*/) override
            {
                DoCastSelf(SPELL_BURNING_FURY, true);

                events.ScheduleEvent(EVENT_BURNING_BREATH, 10000);
                events.ScheduleEvent(EVENT_METEOR_FISTS, 30000);
                events.ScheduleEvent(EVENT_FLAME_CINDER, 20000);

                if (instance)
                    instance->SetData(EVENT_KORALON, IN_PROGRESS);
            }

            void JustDied(Unit* /*who*/) override
            {
                if (instance)
                    instance->SetData(EVENT_KORALON, DONE);
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BURNING_BREATH:
                            if (auto spellInfo = sSpellMgr->GetSpellInfo(SPELL_BURNING_BREATH))
                            {
                                me->DisableRotate(true);
                                DoCastAOE(SPELL_BURNING_BREATH);
                                events.ScheduleEvent(EVENT_RESTORE_ORIENTATION, spellInfo->CastTimeEntry->CastTime);
                            }
                            events.Repeat(45000);
                            break;
                        case EVENT_RESTORE_ORIENTATION:
                            me->DisableRotate(false);
                            break;
                        case EVENT_METEOR_FISTS:
                            DoCastSelf(SPELL_METEOR_FISTS, true);
                            events.Repeat(45000);
                            break;
                        case EVENT_FLAME_CINDER:
                            DoCastSelf(SPELL_FLAMING_CINDER, true);
                            events.Repeat(30000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_koralonAI(creature);
        }
};

class spell_voa_flaming_cinder : public SpellScriptLoader
{
    public:
        spell_voa_flaming_cinder() : SpellScriptLoader("spell_voa_flaming_cinder") { }

        class spell_voa_flaming_cinder_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_voa_flaming_cinder_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                    GetCaster()->CastSpell(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), SPELL_FLAMING_CINDER_MISSILE, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_voa_flaming_cinder_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_voa_flaming_cinder_SpellScript();
        }
};

class spell_koralon_meteor_fists : public SpellScriptLoader
{
    public:
        spell_koralon_meteor_fists() : SpellScriptLoader("spell_koralon_meteor_fists") { }

        class spell_koralon_meteor_fists_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_koralon_meteor_fists_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_METEOR_FISTS_DAMAGE))
                    return false;
                return true;
            }

            void TriggerFists(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();
                GetTarget()->CastSpell(eventInfo.GetProcTarget(), SPELL_METEOR_FISTS_DAMAGE, true, NULL, aurEff);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_koralon_meteor_fists_AuraScript::TriggerFists, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_koralon_meteor_fists_AuraScript();
        }
};

class spell_flame_warder_meteor_fists : public SpellScriptLoader
{
    public:
        spell_flame_warder_meteor_fists() : SpellScriptLoader("spell_flame_warder_meteor_fists") { }

        class spell_flame_warder_meteor_fists_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_flame_warder_meteor_fists_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_FW_METEOR_FISTS_DAMAGE))
                    return false;
                return true;
            }

            void TriggerFists(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();
                GetTarget()->CastSpell(eventInfo.GetProcTarget(), SPELL_FW_METEOR_FISTS_DAMAGE, true, NULL, aurEff);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_flame_warder_meteor_fists_AuraScript::TriggerFists, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_flame_warder_meteor_fists_AuraScript();
        }
};

void AddSC_boss_koralon()
{
    new boss_koralon();
    new spell_voa_flaming_cinder();
    new spell_koralon_meteor_fists();
    new spell_flame_warder_meteor_fists();
}
