#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "forge_of_souls.h"
#include "SpellScript.h"
#include "ScriptedGossip.h"
#include "Player.h"

enum FOSYells
{
    SAY_JAINA_INTRO_1       = 0,
    SAY_JAINA_INTRO_2       = 1,
    SAY_JAINA_INTRO_3       = 2,
    SAY_JAINA_INTRO_4       = 3,
    SAY_JAINA_INTRO_5       = 4,
    SAY_JAINA_INTRO_6       = 5,
    SAY_JAINA_INTRO_7       = 6,
    SAY_JAINA_INTRO_8       = 7,

    SAY_SYLVANAS_INTRO_1    = 0,
    SAY_SYLVANAS_INTRO_2    = 1,
    SAY_SYLVANAS_INTRO_3    = 2,
    SAY_SYLVANAS_INTRO_4    = 3,
    SAY_SYLVANAS_INTRO_5    = 4,
    SAY_SYLVANAS_INTRO_6    = 5,

    SAY_JAINA_OUTRO         = 0,
    SAY_SYLVANAS_OUTRO      = 0
};

enum FOSSpells
{
    SPELL_SHIELD_OF_BONES   = 69642
};

class npc_fos_leader : public CreatureScript
{
public:
    npc_fos_leader() : CreatureScript("npc_fos_leader") { }

    struct npc_fos_leaderAI : public ScriptedAI
    {
        npc_fos_leaderAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset() override
        {
            _events.Reset();
        }

        void DoAction(int32 actionId) override
        {
            if (actionId == 1)
                if (me->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
                {
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    _events.Reset();
                    _events.ScheduleEvent(1, 1000);
                }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 1:
                        if (me->GetEntry() == NPC_JAINA_PART1)
                        {
                            Talk(SAY_JAINA_INTRO_1);
                            _events.ScheduleEvent(2, 8000);
                        }
                        else
                        {
                            Talk(SAY_SYLVANAS_INTRO_1);
                            _events.ScheduleEvent(2, 11500);
                        }
                        break;
                    case 2:
                        if (me->GetEntry() == NPC_JAINA_PART1)
                        {
                            Talk(SAY_JAINA_INTRO_2);
                            _events.ScheduleEvent(3, 9000);
                        }
                        else
                        {
                            Talk(SAY_SYLVANAS_INTRO_2);
                            _events.ScheduleEvent(3, 10500);
                        }
                        break;
                    case 3:
                        if (me->GetEntry() == NPC_JAINA_PART1)
                        {
                            Talk(SAY_JAINA_INTRO_3);
                            _events.ScheduleEvent(4, 8000);
                        }
                        else
                        {
                            Talk(SAY_SYLVANAS_INTRO_3);
                            _events.ScheduleEvent(4, 10500);
                        }
                        break;
                    case 4:
                        if (me->GetEntry() == NPC_JAINA_PART1)
                        {
                            Talk(SAY_JAINA_INTRO_4);
                            _events.ScheduleEvent(5, 10000);
                        }
                        else
                        {
                            Talk(SAY_SYLVANAS_INTRO_4);
                            _events.ScheduleEvent(5, 11000);
                        }
                        break;
                    case 5:
                        if (me->GetEntry() == NPC_JAINA_PART1)
                        {
                            Talk(SAY_JAINA_INTRO_5);
                            _events.ScheduleEvent(6, 8000);
                        }
                        else
                        {
                            Talk(SAY_SYLVANAS_INTRO_5);
                            _events.ScheduleEvent(6, 9500);
                        }
                        break;
                    case 6:
                        if (me->GetEntry() == NPC_JAINA_PART1)
                        {
                            Talk(SAY_JAINA_INTRO_6);
                            _events.ScheduleEvent(7, 12000);
                        }
                        else
                            Talk(SAY_SYLVANAS_INTRO_6);
                        break;
                    case 7:
                        if (me->GetEntry() == NPC_JAINA_PART1)
                        {
                            Talk(SAY_JAINA_INTRO_7);
                            _events.ScheduleEvent(8, 8000);
                        }
                        break;
                    case 8:
                        if (me->GetEntry() == NPC_JAINA_PART1)
                            Talk(SAY_JAINA_INTRO_8);
                        break;
                }
            }


            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
        {
            if (creature->GetEntry() == NPC_JAINA_PART1)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "What would you have of me, my lady?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            else
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "What would you have of me, Banshee Queen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        }

        player->SEND_GOSSIP_MENU(15207, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->CLOSE_GOSSIP_MENU();
                if (creature->IsAIEnabled)
                    creature->AI()->DoAction(1);
                break;
            default:
                break;
        }

        return true;
    }

    CreatureAI *GetAI(Creature* creature) const override
    {
        return new npc_fos_leaderAI(creature);
    }
};

struct npc_fos_leader_secondAI : public ScriptedAI
{
    npc_fos_leader_secondAI(Creature* creature) : ScriptedAI(creature)
    {
        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == POINT_MOTION_TYPE && id == 1)
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            if (me->GetEntry() == NPC_JAINA_PART1)
                Talk(SAY_JAINA_OUTRO);
            else
                Talk(SAY_SYLVANAS_OUTRO);
            me->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
        }
    }
};

class spell_shield_of_bones_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_shield_of_bones_AuraScript)

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SHIELD_OF_BONES });
    }

    bool Load() override
    {
        _fired = false;
        _amount = 0;
        return true;
    }

    void HandleAfterEffectAbsorb(AuraEffect* /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32& absorbAmount)
    {
        _amount += absorbAmount;
        if (!_fired && _amount >= GetSpellInfo()->Effects[EFFECT_0].BasePoints + 1)
            if (Unit* caster = GetCaster())
            {
                _fired = true;
                caster->CastSpell(caster, SPELL_SHIELD_OF_BONES, true);
            }
    }

    int32 _amount;
    bool _fired;

    void Register() override
    {
        AfterEffectAbsorb += AuraEffectAbsorbFn(spell_shield_of_bones_AuraScript::HandleAfterEffectAbsorb, EFFECT_0);
    }
};

void AddSC_forge_of_souls()
{
    new npc_fos_leader();
    new CreatureAILoader<npc_fos_leader_secondAI>("npc_fos_leader_second");
    new AuraScriptLoaderEx<spell_shield_of_bones_AuraScript>("spell_shield_of_bones");
}