#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Player.h"
#include "blackwing_lair.h"

enum Emotes
{
    EMOTE_FRENZY                = 1,
    EMOTE_SHIMMER
};

enum Spells
{
    SPELL_FIRE_VULNERABILITY    = 22277,
    SPELL_FROST_VULNERABILITY   = 22278,
    SPELL_SHADOW_VULNERABILITY  = 22279,
    SPELL_NATURE_VULNERABILITY  = 22280,
    SPELL_ARCANE_VULNERABILITY  = 22281,
    SPELL_INCINERATE            = 23308,
    SPELL_TIMELAPSE             = 23310,
    SPELL_CORROSIVEACID         = 23313,
    SPELL_IGNITEFLESH           = 23315,
    SPELL_FROSTBURN             = 23187,
    SPELL_BROODAF_BLUE          = 23153,
    SPELL_BROODAF_BLACK         = 23154,
    SPELL_BROODAF_RED           = 23155,
    SPELL_BROODAF_BRONZE        = 23170,
    SPELL_BROODAF_GREEN         = 23169,
    SPELL_CHROMATIC_MUT_1       = 23174,
    SPELL_FRENZY                = 28371,
    SPELL_ENRAGE                = 28747,
    SPELL_BROOD_AFFLICTION      = 23173
};

enum Events
{
    EVENT_SHIMMER               = 1,
    EVENT_BREATH_1,
    EVENT_BREATH_2,
    EVENT_AFFLICTION,
    EVENT_FRENZY
};

class boss_chromaggus : public CreatureScript
{
    public:
        boss_chromaggus() : CreatureScript("boss_chromaggus") { }

        struct boss_chromaggusAI : public BossAI
        {
            boss_chromaggusAI(Creature* creature) : BossAI(creature, BOSS_CHROMAGGUS)
            {
                std::vector<uint32> breaths = 
                {
                    SPELL_INCINERATE,
                    SPELL_TIMELAPSE,
                    SPELL_CORROSIVEACID,
                    SPELL_IGNITEFLESH,
                    SPELL_FROSTBURN
                };
                _firstBreath = Trinity::Containers::SelectRandomContainerElement(breaths);
                breaths.erase(std::remove(breaths.begin(), breaths.end(), _firstBreath), breaths.end());
                _secondBreath = Trinity::Containers::SelectRandomContainerElement(breaths);
            }

            void Initialize()
            {
                _currentVulnerabilitySpell = 0;
                _enraged = false;
                _firstShimmerDone = false;
            }

            void Reset() override
            {
                _Reset();
                Initialize();
            }

            void EnterCombat(Unit* /*who*/) override
            {
                if (instance->GetBossState(BOSS_FLAMEGOR) != DONE)
                {
                    EnterEvadeMode();
                    return;
                }

                _EnterCombat();

                events.ScheduleEvent(EVENT_SHIMMER, 0);
                events.ScheduleEvent(EVENT_BREATH_1, 30000);
                events.ScheduleEvent(EVENT_BREATH_2, 60000);
                events.ScheduleEvent(EVENT_AFFLICTION, 10000);
                events.ScheduleEvent(EVENT_FRENZY, 15000);
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                if (me->HealthBelowPctDamaged(20, damage) && !_enraged)
                {
                    _enraged = true;
                    DoCast(me, SPELL_ENRAGE);
                }
            }

            void ExecuteEvent(uint32 eventId) override
            {
                switch (eventId)
                {
                case EVENT_SHIMMER:
                {
                    if (_currentVulnerabilitySpell)
                        me->RemoveAurasDueToSpell(_currentVulnerabilitySpell);
                    std::vector<uint32> spells(_vulnerabilitySpells);
                    spells.erase(std::remove(spells.begin(), spells.end(), _currentVulnerabilitySpell), spells.end());
                    uint32 spell = Trinity::Containers::SelectRandomContainerElement(spells);
                    DoCast(me, spell);
                    _currentVulnerabilitySpell = spell;
                    if (_firstShimmerDone)
                        Talk(EMOTE_SHIMMER);
                    else
                        _firstShimmerDone = true;
                    events.ScheduleEvent(EVENT_SHIMMER, 45000);
                    break;
                }
                case EVENT_BREATH_1:
                    DoCastVictim(_firstBreath);
                    events.ScheduleEvent(EVENT_BREATH_1, 60000);
                    break;
                case EVENT_BREATH_2:
                    DoCastVictim(_secondBreath);
                    events.ScheduleEvent(EVENT_BREATH_2, 60000);
                    break;
                case EVENT_AFFLICTION:
                    DoCastAOE(SPELL_BROOD_AFFLICTION);
                    events.ScheduleEvent(EVENT_AFFLICTION, 10000);
                    break;
                case EVENT_FRENZY:
                    Talk(EMOTE_FRENZY);
                    DoCast(me, SPELL_FRENZY);
                    events.ScheduleEvent(EVENT_FRENZY, urand(10000, 15000));
                    break;
                default:
                    break;
                }
            }

        private:
            bool _enraged, _firstShimmerDone;
            uint32 _firstBreath, _secondBreath, _currentVulnerabilitySpell;
            std::vector<uint32> _vulnerabilitySpells =
            {
                SPELL_FIRE_VULNERABILITY,
                SPELL_FROST_VULNERABILITY,
                SPELL_SHADOW_VULNERABILITY,
                SPELL_NATURE_VULNERABILITY,
                SPELL_ARCANE_VULNERABILITY
            };
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetInstanceAI<boss_chromaggusAI>(creature);
        }
};

class spell_chromaggus_brood_affliction : public SpellScriptLoader
{
    public:
        spell_chromaggus_brood_affliction() : SpellScriptLoader("spell_chromaggus_brood_affliction") { }

        class spell_chromaggus_brood_affliction_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_chromaggus_brood_affliction_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if([&](WorldObject* target) -> bool
                {
                    return target->GetTypeId() != TYPEID_PLAYER || target->ToUnit()->HasAura(SPELL_CHROMATIC_MUT_1);
                });
            }

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    GetCaster()->CastSpell(target, RAND(SPELL_BROODAF_BLUE, SPELL_BROODAF_BLACK, SPELL_BROODAF_RED, SPELL_BROODAF_BRONZE, SPELL_BROODAF_GREEN), true);
                    if (target->HasAura(SPELL_BROODAF_BLUE) && target->HasAura(SPELL_BROODAF_BLACK) && target->HasAura(SPELL_BROODAF_RED) && target->HasAura(SPELL_BROODAF_BRONZE) && target->HasAura(SPELL_BROODAF_GREEN))
                        GetCaster()->CastSpell(target, SPELL_CHROMATIC_MUT_1, true);
                }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_chromaggus_brood_affliction_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_chromaggus_brood_affliction_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_chromaggus_brood_affliction_SpellScript();
        }
};

void AddSC_boss_chromaggus()
{
    new boss_chromaggus();
    new spell_chromaggus_brood_affliction();
}
