/*
 * Copyright (C) 2018-2019 Sunwell <https://sunwell.pl/>
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

#include "ScriptedEscortAI.h"
#include "shadowfang_keep.h"
#include "InstanceScript.h"
#include "SpellScript.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SpellAuraEffects.h"

enum ShadowfangPrisoner
{
    SAY_FREE_AD,
    SAY_OPEN_DOOR_AD,
    SAY_POST1_DOOR_AD,
    SAY_POST2_DOOR_AD,
    SAY_BOSS_DIE_AD,

    SAY_FREE_AS                 = 0,
    SAY_OPEN_DOOR_AS,
    SAY_POST1_DOOR_AS,
    SAY_POST2_DOOR_AS,
    SAY_BOSS_DIE_AS,

    SPELL_UNLOCK                = 6421,
    SPELL_ASHCROMBE_TELEPORT    = 6422,

    EVENT_END_ESCORT            = 1
};

struct npc_shadowfang_prisonerAI : public npc_escortAI
{
    npc_shadowfang_prisonerAI(Creature* creature) : npc_escortAI(creature), _instance(creature->GetInstanceScript())
    {
        creature->SetDefensive();
    }

    void sGossipHello(Player* player) override
    {
        if (_instance && _instance->GetBossState(BOSS_RETHILGORE) == DONE && !_instance->GetData(DATA_COURTYARD))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, me->GetEntry() == NPC_ALLIANCE_ESCORT ? "Please unlock the courtyard door." : "Thanks, I'll follow you to the door.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(me), me->GetGUID());
    }

    void sGossipSelect(Player* player, uint32 /*sender*/, uint32 /*action*/) override
    {
        Start(false, false);
        SetDespawnAtEnd(false);
        me->SetAggressive();
        player->CLOSE_GOSSIP_MENU();
    }

    void WaypointReached(uint32 pointId) override
    {
        switch (pointId)
        {
            case 0:
                Talk(me->GetEntry() == NPC_ALLIANCE_ESCORT ? SAY_FREE_AS : SAY_FREE_AD);
                break;
            case 10:
                Talk(me->GetEntry() == NPC_ALLIANCE_ESCORT ? SAY_OPEN_DOOR_AS : SAY_OPEN_DOOR_AD);
                break;
            case 11:
                if (me->GetEntry() == NPC_ALLIANCE_ESCORT)
                    DoCastSelf(SPELL_UNLOCK);
                else
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_USE_STANDING);
                break;
            case 12:
                Talk(me->GetEntry() == NPC_ALLIANCE_ESCORT ? SAY_POST1_DOOR_AS : SAY_POST1_DOOR_AD);
                if (_instance)
                    _instance->SetData(DATA_COURTYARD, DONE);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                break;
            case 13:
                if (me->GetEntry() == NPC_HORDE_ESCORT)
                    Talk(SAY_POST2_DOOR_AD);
                else
                    DoCastSelf(SPELL_ASHCROMBE_TELEPORT);
                _events.ScheduleEvent(EVENT_END_ESCORT, 3s);
                break;
            default:
                break;
        }
    }

    void Reset() override { }
    void EnterCombat(Unit* /*attacker*/) override { }
    void UpdateAI(uint32 const diff) override
    {
        npc_escortAI::UpdateAI(diff);
        if (_events.Empty())
            return;
        _events.Update(diff);
        if (_events.ExecuteEvent() == EVENT_END_ESCORT)
        {
            if (me->GetEntry() == NPC_HORDE_ESCORT)
            {
                SetRun(true);
                me->GetMotionMaster()->MovePoint(0, { -226.963f, 2111.13f, 76.890f });
                me->DespawnOrUnsummon(10000);
            }
            else
            {
                Talk(SAY_POST2_DOOR_AD);
                me->SetVisible(false);
                me->DespawnOrUnsummon(1);
            }
        }
    }

    private:
        InstanceScript* _instance;
        EventMap _events;
};

class spell_shadowfang_keep_haunting_spirits_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_shadowfang_keep_haunting_spirits_AuraScript);

    void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = irand(30 * IN_MILLISECONDS, 90 * IN_MILLISECONDS);
    }

    void HandleDummyTick(AuraEffect const* aurEff)
    {
        GetTarget()->CastSpell((Unit*)nullptr, aurEff->GetAmount(), true);
    }

    void HandleUpdatePeriodic(AuraEffect* aurEff)
    {
        aurEff->CalculatePeriodic(GetCaster());
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_shadowfang_keep_haunting_spirits_AuraScript::CalcPeriodic, EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_shadowfang_keep_haunting_spirits_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_shadowfang_keep_haunting_spirits_AuraScript::HandleUpdatePeriodic, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

enum ForsakenSpells
{
    SPELL_FORSAKEN_SKILL_SWORD  = 7038,
    SPELL_FORSAKEN_SKILL_SHADOW = 7053
};

class spell_shadowfang_keep_forsaken_skills_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_shadowfang_keep_forsaken_skills_AuraScript);

    bool Load()
    {
        _forsakenSpell = 0;
        return true;
    }

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        _forsakenSpell = urand(SPELL_FORSAKEN_SKILL_SWORD, SPELL_FORSAKEN_SKILL_SHADOW);
        if (_forsakenSpell == SPELL_FORSAKEN_SKILL_SHADOW - 1)
            ++_forsakenSpell;
        GetUnitOwner()->CastSpell(GetUnitOwner(), _forsakenSpell, true);
    }

    void HandleDummyTick(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        GetUnitOwner()->RemoveAurasDueToSpell(_forsakenSpell);
        _forsakenSpell = urand(SPELL_FORSAKEN_SKILL_SWORD, SPELL_FORSAKEN_SKILL_SHADOW);
        if (_forsakenSpell == SPELL_FORSAKEN_SKILL_SHADOW - 1)
            ++_forsakenSpell;
        GetUnitOwner()->CastSpell(GetUnitOwner(), _forsakenSpell, true);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_shadowfang_keep_forsaken_skills_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_shadowfang_keep_forsaken_skills_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }

    uint32 _forsakenSpell;
};

void AddSC_shadowfang_keep()
{
    new CreatureAILoader<npc_shadowfang_prisonerAI>("npc_shadowfang_prisoner");
    new AuraScriptLoaderEx<spell_shadowfang_keep_haunting_spirits_AuraScript>("spell_shadowfang_keep_haunting_spirits");
    new AuraScriptLoaderEx<spell_shadowfang_keep_forsaken_skills_AuraScript>("spell_shadowfang_keep_forsaken_skills");
}
