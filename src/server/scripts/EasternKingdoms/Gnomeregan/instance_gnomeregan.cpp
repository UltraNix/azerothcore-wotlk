/*
REWRITTEN BY XINEF
*/

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "PetDefines.h"
#include "PassiveAI.h"
#include "Player.h"
#include "SpellScript.h"

class instance_gnomeregan : public InstanceMapScript
{
    public:
        instance_gnomeregan() : InstanceMapScript("instance_gnomeregan", 90) { }

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_gnomeregan_InstanceMapScript(map);
        }

        struct instance_gnomeregan_InstanceMapScript : public InstanceScript
        {
            instance_gnomeregan_InstanceMapScript(Map* map) : InstanceScript(map)
            {
            }
        };
};

enum eKernobee
{
    QUEST_A_FINE_MESS            = 2904,
};

class npc_kernobee : public CreatureScript
{
    public:
        npc_kernobee() : CreatureScript("npc_kernobee") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_kernobeeAI(creature);
        }

        bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest)
        {
            if (quest->GetQuestId() == QUEST_A_FINE_MESS)
            {
                creature->SetStandState(UNIT_STAND_STATE_STAND);
                creature->AI()->SetGUID(player->GetGUID(), 0);
                creature->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, M_PI, MOTION_SLOT_CONTROLLED);
            }
            return true;
        }

        struct npc_kernobeeAI : public PassiveAI
        {
            npc_kernobeeAI(Creature* creature) : PassiveAI(creature)
            {
                playerGUID = 0;
                checkTimer = 0;
            }

            uint32 checkTimer;
            uint64 playerGUID;

            void SetGUID(uint64 guid, int32)
            {
                playerGUID = guid;
            }

            void UpdateAI(uint32 diff)
            {
                checkTimer += diff;
                if (checkTimer >= 2000)
                {
                    checkTimer = 0;
                    if (me->GetDistance(-332.2f, -2.8f, -152.8f) < 5.0f)
                    {
                        if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                            player->GroupEventHappens(QUEST_A_FINE_MESS, me);
                        me->DespawnOrUnsummon(1000);
                    }
                }
            }
        };
};

class spell_gnomeregan_radiation_bolt : public SpellScriptLoader
{
    public:
        spell_gnomeregan_radiation_bolt() : SpellScriptLoader("spell_gnomeregan_radiation_bolt") { }

        class spell_gnomeregan_radiation_bolt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gnomeregan_radiation_bolt_SpellScript);

            void HandleTriggerSpell(SpellEffIndex effIndex)
            {
                if (roll_chance_i(80))
                    PreventHitDefaultEffect(effIndex);
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_gnomeregan_radiation_bolt_SpellScript::HandleTriggerSpell, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gnomeregan_radiation_bolt_SpellScript;
        }
};

enum MiscSpells
{
    SPELL_WALKING_BOMB_EFFECT   = 11504
};

class BoomEvent : public BasicEvent
{
public:
    explicit BoomEvent(Creature* me) : _me(me) {}

    bool Execute(uint64 /*time*/, uint32 /*diff*/) override
    {
        if (!_me)
            return false;

        // This hack is here because we suspect our implementation of spell effect execution on targets
        // is done in the wrong order. We suspect that EFFECT_0 needs to be applied on all targets,
        // then EFFECT_1, etc - instead of applying each effect on target1, then target2, etc.
        // The above situation causes the visual for this spell to be bugged, so we remove the instakill
        // effect and implement a script hack for that.

        WorldPacket data(SMSG_SPELLINSTAKILLLOG, 8 + 8 + 4);
        data << uint64(_me->GetGUID());
        data << uint64(_me->GetGUID());
        data << uint32(SPELL_WALKING_BOMB_EFFECT);
        _me->SendMessageToSet(&data, false);

        Unit::Kill(_me, _me);
        return true;
    }

private:
    Creature * _me;
};

class spell_walking_bomb_effect_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_walking_bomb_effect_SpellScript);

    bool Load() override
    {
        _exploded = false;
        return true;
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (!_exploded)
        {
            _exploded = true;
            if (GetCaster()->ToCreature())
            {
                GetCaster()->ToCreature()->SetReactState(REACT_PASSIVE);
                GetCaster()->ToCreature()->AttackStop();
                GetCaster()->m_Events.AddEvent(new BoomEvent(GetCaster()->ToCreature()), GetCaster()->m_Events.CalculateTime(1 * IN_MILLISECONDS));
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_walking_bomb_effect_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
private:
    bool _exploded;
};

void AddSC_instance_gnomeregan()
{
    new instance_gnomeregan();
    new npc_kernobee();
    new spell_gnomeregan_radiation_bolt();
    new SpellScriptLoaderEx<spell_walking_bomb_effect_SpellScript>("spell_walking_bomb_effect");
}
