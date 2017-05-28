/*
 * Copyright (C) 
 * Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "blackwing_lair.h"
#include "ScriptedGossip.h"
#include "Player.h"

enum Says
{
   SAY_LINE1                         = 0,
   SAY_LINE2                         = 1,
   SAY_LINE3                         = 2,
   SAY_HALFLIFE                      = 3,
   SAY_KILLTARGET                    = 4
};

enum Gossip
{
   GOSSIP_ID                         = 21334,
};

enum Spells
{
   SPELL_ESSENCEOFTHERED             = 23513,
   SPELL_FLAMEBREATH                 = 23461,
   SPELL_FIRENOVA                    = 23462,
   SPELL_TAILSWIPE                   = 15847,
   SPELL_BURNINGADRENALINE           = 18173,
   SPELL_BURNINGADRENALINE_EXPLOSION = 23478,
   SPELL_CLEAVE                      = 20684   //Chain cleave is most likely named something different and contains a dummy effect
};

enum Events
{
    EVENT_SPEECH_1                   = 1,
    EVENT_SPEECH_2                   = 2,
    EVENT_SPEECH_3                   = 3,
    EVENT_SPEECH_4                   = 4,
    EVENT_ESSENCEOFTHERED            = 5,
    EVENT_FLAMEBREATH                = 6,
    EVENT_FIRENOVA                   = 7,
    EVENT_TAILSWIPE                  = 8,
    EVENT_CLEAVE                     = 9,
    EVENT_BURNINGADRENALINE_CASTER   = 10,
    EVENT_BURNINGADRENALINE_TANK     = 11
};

enum Phases
{
    PHASE_INTRO                      = 1,
    PHASE_FIGHT,
};

class boss_vaelastrasz : public CreatureScript
{
public:
    boss_vaelastrasz() : CreatureScript("boss_vaelastrasz") { }

    struct boss_vaelAI : public BossAI
    {
        boss_vaelAI(Creature* creature) : BossAI(creature, BOSS_VAELASTRAZ)
        {
            creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            creature->setFaction(35);
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void Initialize()
        {
            PlayerGUID = 0;
            _yelled = false;
        }

        void Reset() override
        {
            _Reset();
            events.SetPhase(PHASE_INTRO);
            me->SetStandState(UNIT_STAND_STATE_DEAD);
            Initialize();
        }

        void EnterCombat(Unit* /*who*/) override
        {
            _EnterCombat();
            me->SetStandState(UNIT_STAND_STATE_STAND);

            events.SetPhase(PHASE_FIGHT);
            DoCast(me, SPELL_ESSENCEOFTHERED);
            me->SetHealth(me->CountPctFromMaxHealth(30));
            // now drop damage requirement to be able to take loot
            me->ResetPlayerDamageReq();

            events.ScheduleEvent(EVENT_CLEAVE, 10000, 0, PHASE_FIGHT);
            events.ScheduleEvent(EVENT_FLAMEBREATH, 15000, PHASE_FIGHT);
            events.ScheduleEvent(EVENT_FIRENOVA, 20000, PHASE_FIGHT);
            events.ScheduleEvent(EVENT_TAILSWIPE, 11000, PHASE_FIGHT);
            events.ScheduleEvent(EVENT_BURNINGADRENALINE_CASTER, 15000, PHASE_FIGHT);
            events.ScheduleEvent(EVENT_BURNINGADRENALINE_TANK, 45000, PHASE_FIGHT);
        }

        void BeginSpeech(Unit* target)
        {
            PlayerGUID = target->GetGUID();
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            events.ScheduleEvent(EVENT_SPEECH_1, 1000, 0, PHASE_INTRO);
        }

        void KilledUnit(Unit* victim) override
        {
            if(victim->GetTypeId() == TYPEID_PLAYER && roll_chance_i(80))
                Talk(SAY_KILLTARGET, victim);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
        {
            if (HealthBelowPct(15) && !_yelled)
            {
                Talk(SAY_HALFLIFE);
                _yelled = true;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if ((!UpdateVictim() || me->GetVictim()->isDead()) && !events.IsInPhase(PHASE_INTRO))
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    // Intro speech
                    case EVENT_SPEECH_1:
                        Talk(SAY_LINE1);
                        me->SetStandState(UNIT_STAND_STATE_STAND);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                        events.ScheduleEvent(EVENT_SPEECH_2, 12000, PHASE_INTRO);
                        break;
                    case EVENT_SPEECH_2:
                        Talk(SAY_LINE2);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                        events.ScheduleEvent(EVENT_SPEECH_3, 12000, PHASE_INTRO);
                        break;
                    case EVENT_SPEECH_3:
                        Talk(SAY_LINE3);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                        events.ScheduleEvent(EVENT_SPEECH_4, 16000, PHASE_INTRO);
                        break;
                    case EVENT_SPEECH_4:
                        me->setFaction(103);
                        if (PlayerGUID && ObjectAccessor::GetUnit(*me, PlayerGUID))
                            AttackStart(ObjectAccessor::GetUnit(*me, PlayerGUID));;
                        break;
                    // Fight
                    case EVENT_CLEAVE:
                        DoCastVictim(SPELL_CLEAVE);
                        events.ScheduleEvent(EVENT_CLEAVE, 15000, 0, PHASE_FIGHT);
                        break;
                    case EVENT_FLAMEBREATH:
                        DoCastVictim(SPELL_FLAMEBREATH);
                        events.ScheduleEvent(EVENT_FLAMEBREATH, urand(8000, 14000), 0, PHASE_FIGHT);
                        break;
                    case EVENT_FIRENOVA:
                        DoCastVictim(SPELL_FIRENOVA);
                        events.ScheduleEvent(EVENT_FIRENOVA, 15000, 0, PHASE_FIGHT);
                        break;
                    case EVENT_TAILSWIPE:
                        DoCastAOE(SPELL_TAILSWIPE);
                        events.ScheduleEvent(EVENT_TAILSWIPE, 15000, 0, PHASE_FIGHT);
                        break;
                    case EVENT_BURNINGADRENALINE_CASTER:
                        if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 1, [&](Unit* u) { return u && !u->IsPet() && u->getPowerType() == POWER_MANA && !u->HasAura(SPELL_BURNINGADRENALINE); }))
                            DoCast(target, SPELL_BURNINGADRENALINE, true);
                        events.ScheduleEvent(EVENT_BURNINGADRENALINE_CASTER, 15000, 0, PHASE_FIGHT);
                        break;
                    case EVENT_BURNINGADRENALINE_TANK:
                        // have the victim cast the spell on himself otherwise the third effect aura will be applied to Vael instead of the player
                        if (!me->GetVictim()->HasAura(SPELL_BURNINGADRENALINE))
                            DoCastVictim(SPELL_BURNINGADRENALINE, true);
                        events.ScheduleEvent(EVENT_BURNINGADRENALINE_TANK, 45000, 0, PHASE_FIGHT);
                        break;
                    default:
                        break;
                }
            }

            if(events.IsInPhase(PHASE_FIGHT))
                DoMeleeAttackIfReady();
        }

        void sGossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            if (sender == GOSSIP_ID && action == 0)
            {
                player->CLOSE_GOSSIP_MENU();
                BeginSpeech(player);
            }
        }

        private:
            uint64 PlayerGUID;
            bool _yelled;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_vaelAI(creature);
    }
};

class spell_vael_burning_adrenaline : public SpellScriptLoader
{
    public:
        spell_vael_burning_adrenaline() : SpellScriptLoader("spell_vael_burning_adrenaline") { }

        class spell_vael_burning_adrenaline_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_vael_burning_adrenaline_AuraScript);

            void OnAuraRemoveHandler(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->CastSpell(GetTarget(), SPELL_BURNINGADRENALINE_EXPLOSION, true);
            }

            void Register() override
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_vael_burning_adrenaline_AuraScript::OnAuraRemoveHandler, EFFECT_2, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_vael_burning_adrenaline_AuraScript();
        }
};


void AddSC_boss_vaelastrasz()
{
    new boss_vaelastrasz();
    new spell_vael_burning_adrenaline();
}
