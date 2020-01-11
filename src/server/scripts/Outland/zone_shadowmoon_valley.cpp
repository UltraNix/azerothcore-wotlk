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

/* ScriptData
SDName: Shadowmoon_Valley
SD%Complete: 100
SDComment: Quest support: 10519, 10583, 10601, 10804, 10854, 10458, 10481, 10480, 10781, 10451. Vendor Drake Dealer Hurlunk.
SDCategory: Shadowmoon Valley
EndScriptData */

/* ContentData
npc_mature_netherwing_drake
npc_enslaved_netherwing_drake
npc_drake_dealer_hurlunk
npcs_flanis_swiftwing_and_kagrosh
npc_karynaku
npc_oronok_tornheart
npc_earthmender_wilda
npc_torloth_the_magnificent
npc_illidari_spawn
npc_lord_illidan_stormrage
go_crystal_prison
npc_enraged_spirit
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "Group.h"
#include "SpellScript.h"
#include "Player.h"
#include "WorldSession.h"

// Ours
class spell_q10612_10613_the_fel_and_the_furious : public SpellScriptLoader
{
    public:
        spell_q10612_10613_the_fel_and_the_furious() : SpellScriptLoader("spell_q10612_10613_the_fel_and_the_furious") { }

        class spell_q10612_10613_the_fel_and_the_furious_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_q10612_10613_the_fel_and_the_furious_SpellScript);

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                Player* charmer = GetCaster()->GetCharmerOrOwnerPlayerOrPlayerItself();
                if (!charmer)
                    return;

                std::list<GameObject*> gList;
                GetCaster()->GetGameObjectListWithEntryInGrid(gList, 184979, 30.0f);
                uint8 counter = 0;
                for (std::list<GameObject*>::const_iterator itr = gList.begin(); itr != gList.end(); ++itr, ++counter)
                {
                    if (counter >= 10)
                        break;
                    GameObject* go = *itr;
                    if (!go->isSpawned())
                        continue;
                    Creature* cr2 = go->SummonTrigger(go->GetPositionX(), go->GetPositionY(), go->GetPositionZ()+2.0f, 0.0f, 100);
                    if (cr2)
                    {
                        cr2->setFaction(14);
                        cr2->SetUInt32Value(UNIT_FIELD_FLAGS, 0);
                        GetCaster()->CastSpell(cr2, 38083, true);
                    }

                    go->SetLootState(GO_JUST_DEACTIVATED);
                    charmer->KilledMonsterCredit(21959, 0);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_q10612_10613_the_fel_and_the_furious_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_q10612_10613_the_fel_and_the_furious_SpellScript();
        }
};

class spell_q10563_q10596_to_legion_hold : public SpellScriptLoader
{
public:
    spell_q10563_q10596_to_legion_hold() : SpellScriptLoader("spell_q10563_q10596_to_legion_hold") { }

    class spell_q10563_q10596_to_legion_hold_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_q10563_q10596_to_legion_hold_AuraScript)

        void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Player* player = GetTarget()->ToPlayer())
            {
                player->KilledMonsterCredit(21502, 0);
                player->SetControlled(false, UNIT_STATE_STUNNED);
            }
        }

        void HandleEffectApply(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Player* player = GetTarget()->ToPlayer())
            {
                player->SetControlled(true, UNIT_STATE_STUNNED);
                player->SummonCreature(21633, -3311.13f, 2946.15f, 171.1f, 4.86f, TEMPSUMMON_TIMED_DESPAWN, 64000);
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_q10563_q10596_to_legion_hold_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_TRANSFORM, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_q10563_q10596_to_legion_hold_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_TRANSFORM, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_q10563_q10596_to_legion_hold_AuraScript();
    }
};


// Theirs
/*#####
# npc_invis_infernal_caster
#####*/

enum InvisInfernalCaster
{
    EVENT_CAST_SUMMON_INFERNAL = 1,
    NPC_INFERNAL_ATTACKER      = 21419,
    MODEL_INVISIBLE            = 20577,
    MODEL_INFERNAL             = 17312,
    SPELL_SUMMON_INFERNAL      = 37277,
    TYPE_INFERNAL              = 1,
    DATA_DIED                  = 1
};

class npc_invis_infernal_caster : public CreatureScript
{
public:
    npc_invis_infernal_caster() : CreatureScript("npc_invis_infernal_caster") { }

    struct npc_invis_infernal_casterAI : public ScriptedAI
    {

        npc_invis_infernal_casterAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            ground = 0.f;
        }

        void Reset()
        {
            summons.DespawnAll();
            events.Reset();
            events.ScheduleEvent(EVENT_CAST_SUMMON_INFERNAL, 5s);
            ground = me->GetMap()->GetHeight(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
        }

        void SetData(uint32 type, uint32 data)
        {
            if (type == TYPE_INFERNAL && data == DATA_DIED)
            {
                events.Reset();
                events.ScheduleEvent(EVENT_CAST_SUMMON_INFERNAL, 5s);
            }
        }

        void JustSummoned(Creature* summon) override
        {
            if (summon->GetEntry() == NPC_INFERNAL_ATTACKER)
            {
                summon->SetDisplayId(MODEL_INVISIBLE);
                summons.Summon(summon);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CAST_SUMMON_INFERNAL:
                    {
                        summons.DespawnAll();
                        if (Unit* infernal = me->SummonCreature(NPC_INFERNAL_ATTACKER, me->GetPositionX(), me->GetPositionY(), ground + 0.05f, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000))
                            if (infernal->GetDisplayId() == MODEL_INVISIBLE)
                                me->CastSpell(infernal, SPELL_SUMMON_INFERNAL, true);
                        events.ScheduleEvent(EVENT_CAST_SUMMON_INFERNAL, 60s);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    private:
        EventMap events;
        float ground;
        SummonList summons;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_invis_infernal_casterAI(creature);
    }
};

/*#####
# npc_infernal_attacker
#####*/

class npc_infernal_attacker : public CreatureScript
{
public:
    npc_infernal_attacker() : CreatureScript("npc_infernal_attacker") { }

    struct npc_infernal_attackerAI : public ScriptedAI
    {
        npc_infernal_attackerAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            me->GetMotionMaster()->MoveRandom(5.0f);
        }

        void IsSummonedBy(Unit* summoner)
        {
            if (!summoner)
                return;

            if (summoner->ToCreature())
                casterGUID = summoner->ToCreature()->GetGUID();;
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Creature* caster = ObjectAccessor::GetCreature(*me, casterGUID))
                caster->AI()->SetData(TYPE_INFERNAL, DATA_DIED);
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_SUMMON_INFERNAL)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_PACIFIED | UNIT_FLAG_NOT_SELECTABLE);
                me->SetDisplayId(MODEL_INFERNAL);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

    private:
        uint64 casterGUID;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_infernal_attackerAI(creature);
    }
};

/*#####
# npc_mature_netherwing_drake
#####*/

enum MatureNetherwing
{
    SAY_JUST_EATEN              = 0,

    SPELL_PLACE_CARCASS         = 38439,
    SPELL_JUST_EATEN            = 38502,
    SPELL_NETHER_BREATH         = 38467,
    POINT_ID                    = 1,

    GO_CARCASS                  = 185155,

    QUEST_KINDNESS              = 10804,
    NPC_EVENT_PINGER            = 22131
};

class npc_mature_netherwing_drake : public CreatureScript
{
public:
    npc_mature_netherwing_drake() : CreatureScript("npc_mature_netherwing_drake") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mature_netherwing_drakeAI(creature);
    }

    struct npc_mature_netherwing_drakeAI : public ScriptedAI
    {
        npc_mature_netherwing_drakeAI(Creature* creature) : ScriptedAI(creature) { }

        uint64 uiPlayerGUID;

        bool bCanEat;
        bool bIsEating;

        uint32 EatTimer;
        uint32 CastTimer;

        void Reset()
        {
            uiPlayerGUID = 0;

            bCanEat = false;
            bIsEating = false;

            EatTimer = 5000;
            CastTimer = 5000;
        }

        void SpellHit(Unit* pCaster, SpellInfo const* spell)
        {
            if (bCanEat || bIsEating)
                return;

            if (pCaster->GetTypeId() == TYPEID_PLAYER && spell->Id == SPELL_PLACE_CARCASS && !me->HasAura(SPELL_JUST_EATEN))
            {
                uiPlayerGUID = pCaster->GetGUID();
                bCanEat = true;
            }
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            if (id == POINT_ID)
            {
                bIsEating = true;
                EatTimer = 7000;
                me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK_UNARMED);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (bCanEat || bIsEating)
            {
                if (EatTimer <= diff)
                {
                    if (bCanEat && !bIsEating)
                    {
                        if (Unit* unit = ObjectAccessor::GetUnit(*me, uiPlayerGUID))
                        {
                            if (GameObject* go = unit->FindNearestGameObject(GO_CARCASS, 10))
                            {
                                if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == WAYPOINT_MOTION_TYPE)
                                    me->GetMotionMaster()->MovementExpired();

                                me->GetMotionMaster()->MoveIdle();
                                me->StopMoving();

                                me->GetMotionMaster()->MovePoint(POINT_ID, go->GetPositionX(), go->GetPositionY(), go->GetPositionZ());
                            }
                        }
                        bCanEat = false;
                    }
                    else if (bIsEating)
                    {
                        DoCast(me, SPELL_JUST_EATEN);
                        Talk(SAY_JUST_EATEN);

                        if (Player* player = ObjectAccessor::GetPlayer(*me, uiPlayerGUID))
                        {
                            player->KilledMonsterCredit(NPC_EVENT_PINGER, 0);

                            if (GameObject* go = player->FindNearestGameObject(GO_CARCASS, 10))
                                go->Delete();
                        }

                        Reset();
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MovePath(me->GetWaypointPath(), true);
                    }
                }
                else
                    EatTimer -= diff;

            return;
            }

            if (!UpdateVictim())
                return;

            if (CastTimer <= diff)
            {
                DoCastVictim(SPELL_NETHER_BREATH);
                CastTimer = 5000;
            } else CastTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

/*###
# npc_enslaved_netherwing_drake
####*/

enum EnshlavedNetherwingDrake
{
    // Factions
    FACTION_DEFAULT                 = 62,
    FACTION_FRIENDLY                = 1840, // Not sure if this is correct, it was taken off of Mordenai.

    // Spells
    SPELL_HIT_FORCE_OF_NELTHARAKU   = 38762,
    SPELL_FORCE_OF_NELTHARAKU       = 38775,

    // Creatures
    NPC_DRAGONMAW_SUBJUGATOR        = 21718,
    NPC_ESCAPE_DUMMY                = 22317

};

class npc_enslaved_netherwing_drake : public CreatureScript
{
public:
    npc_enslaved_netherwing_drake() : CreatureScript("npc_enslaved_netherwing_drake") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_enslaved_netherwing_drakeAI(creature);
    }

    struct npc_enslaved_netherwing_drakeAI : public ScriptedAI
    {
        npc_enslaved_netherwing_drakeAI(Creature* creature) : ScriptedAI(creature)
        {
            PlayerGUID = 0;
            Tapped = false;
            Reset();
        }

        uint64 PlayerGUID;
        uint32 FlyTimer;
        bool Tapped;

        void Reset()
        {
            if (!Tapped)
                me->setFaction(FACTION_DEFAULT);

            FlyTimer = 10000;
            me->SetDisableGravity(false);
            me->SetVisible(true);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (!caster)
                return;

            if (caster->GetTypeId() == TYPEID_PLAYER && spell->Id == SPELL_HIT_FORCE_OF_NELTHARAKU && !Tapped)
            {
                Tapped = true;
                PlayerGUID = caster->GetGUID();

                me->setFaction(FACTION_FRIENDLY);
                DoCast(caster, SPELL_FORCE_OF_NELTHARAKU, true);

                Unit* Dragonmaw = me->FindNearestCreature(NPC_DRAGONMAW_SUBJUGATOR, 50);
                if (Dragonmaw)
                {
                    me->AddThreat(Dragonmaw, 100000.0f);
                    AttackStart(Dragonmaw);
                }

                HostileReference* ref = me->getThreatManager().getOnlineContainer().getReferenceByTarget(caster);
                if (ref)
                    ref->removeReference();
            }
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            if (id == 1)
            {
                if (PlayerGUID)
                {
                    Unit* player = ObjectAccessor::GetUnit(*me, PlayerGUID);
                    if (player)
                        DoCast(player, SPELL_FORCE_OF_NELTHARAKU, true);

                    PlayerGUID = 0;
                }
                me->SetVisible(false);
                me->SetDisableGravity(false);
                Unit::DealDamage(me, me, me->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                me->RemoveCorpse();
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            {
                if (Tapped)
                {
                    if (FlyTimer <= diff)
                    {
                        Tapped = false;
                        if (PlayerGUID)
                        {
                            Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                            if (player && player->GetQuestStatus(10854) == QUEST_STATUS_INCOMPLETE)
                            {
                                DoCast(player, SPELL_FORCE_OF_NELTHARAKU, true);
                                /*
                                float x, y, z;
                                me->GetPosition(x, y, z);

                                float dx, dy, dz;
                                me->GetRandomPoint(x, y, z, 20, dx, dy, dz);
                                dz += 20; // so it's in the air, not ground*/

                                Position pos;
                                if (Unit* EscapeDummy = me->FindNearestCreature(NPC_ESCAPE_DUMMY, 30))
                                    EscapeDummy->GetPosition(&pos);
                                else
                                {
                                    me->GetRandomNearPosition(pos, 20);
                                    pos.m_positionZ += 25;
                                }

                                me->SetDisableGravity(true);
                                me->GetMotionMaster()->MovePoint(1, pos);
                            }
                        }
                    } else FlyTimer -= diff;
                }
                return;
            }

            DoMeleeAttackIfReady();
        }
    };
};

/*#####
# npc_dragonmaw_peon
#####*/

class npc_dragonmaw_peon : public CreatureScript
{
public:
    npc_dragonmaw_peon() : CreatureScript("npc_dragonmaw_peon") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dragonmaw_peonAI(creature);
    }

    struct npc_dragonmaw_peonAI : public ScriptedAI
    {
        npc_dragonmaw_peonAI(Creature* creature) : ScriptedAI(creature) { }

        uint64 PlayerGUID;
        bool Tapped;
        uint32 PoisonTimer;

        void Reset()
        {
            PlayerGUID = 0;
            Tapped = false;
            PoisonTimer = 0;
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (!caster)
                return;

            if (caster->GetTypeId() == TYPEID_PLAYER && spell->Id == 40468 && !Tapped)
            {
                PlayerGUID = caster->GetGUID();

                Tapped = true;
                float x, y, z;
                caster->GetClosePoint(x, y, z, me->GetObjectSize());

                me->SetWalk(false);
                me->GetMotionMaster()->MovePoint(1, x, y, z);
            }
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            if (id)
            {
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_EAT);
                PoisonTimer = 15000;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (PoisonTimer)
            {
                if (PoisonTimer <= diff)
                {
                    if (PlayerGUID)
                    {
                        Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                        if (player && player->GetQuestStatus(11020) == QUEST_STATUS_INCOMPLETE)
                            player->KilledMonsterCredit(23209, 0);
                    }
                    PoisonTimer = 0;
                    Unit::DealDamage(me, me, me->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                } else PoisonTimer -= diff;
            }
        }
    };
};

/*######
## npc_drake_dealer_hurlunk
######*/

class npc_drake_dealer_hurlunk : public CreatureScript
{
public:
    npc_drake_dealer_hurlunk() : CreatureScript("npc_drake_dealer_hurlunk") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_TRADE)
            player->GetSession()->SendListInventory(creature->GetGUID());

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsVendor() && player->GetReputationRank(1015) == REP_EXALTED)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }
};

/*######
## npc_flanis_swiftwing_and_kagrosh
######*/

#define GOSSIP_HSK1 "Take Flanis's Pack"
#define GOSSIP_HSK2 "Take Kagrosh's Pack"

class npcs_flanis_swiftwing_and_kagrosh : public CreatureScript
{
public:
    npcs_flanis_swiftwing_and_kagrosh() : CreatureScript("npcs_flanis_swiftwing_and_kagrosh") { }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF+1)
        {
            ItemPosCountVec dest;
            uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 30658, 1, NULL);
            if (msg == EQUIP_ERR_OK)
            {
                player->StoreNewItem(dest, 30658, 1, true);
                player->PlayerTalkClass->ClearMenus();
            }
        }
        if (action == GOSSIP_ACTION_INFO_DEF+2)
        {
            ItemPosCountVec dest;
            uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 30659, 1, NULL);
            if (msg == EQUIP_ERR_OK)
            {
                player->StoreNewItem(dest, 30659, 1, true);
                player->PlayerTalkClass->ClearMenus();
            }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(10583) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(30658, 1, true))
            player->ADD_GOSSIP_ITEM(0, GOSSIP_HSK1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        if (player->GetQuestStatus(10601) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(30659, 1, true))
            player->ADD_GOSSIP_ITEM(0, GOSSIP_HSK2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }
};

/*####
# npc_karynaku
####*/

enum Karynaku
{
    QUEST_ALLY_OF_NETHER    = 10870,
    QUEST_ZUHULED_THE_WACK  = 10866,

    NPC_ZUHULED_THE_WACKED  = 11980,

    TAXI_PATH_ID            = 649,
};

class npc_karynaku : public CreatureScript
{
    public:
        npc_karynaku() : CreatureScript("npc_karynaku") { }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_ALLY_OF_NETHER)
                player->ActivateTaxiPathTo(TAXI_PATH_ID);

            if (quest->GetQuestId() == QUEST_ZUHULED_THE_WACK)
                creature->SummonCreature(NPC_ZUHULED_THE_WACKED, -4204.94f, 316.397f, 122.508f, 1.309f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);

            return true;
        }
};

/*####
# npc_earthmender_wilda
####*/

enum EarthmenderWilda
{
    SAY_WIL_START               = 0,
    SAY_WIL_AGGRO,
    SAY_WIL_PROGRESS1,
    SAY_WIL_PROGRESS2,
    SAY_WIL_FIND_EXIT,
    SAY_WIL_JUST_AHEAD,
    SAY_WIL_END,
    SAY_END,
    SAY_PROGRESS6,
    SAY_PROGRESS5,
    SAY_PROGRESS4,
    SAY_PROGRESS3,
    SAY_PROGRESS2,
    SAY_PROGRESS1,
    ASSASSIN_SAY_AGGRO2,
    ASSASSIN_SAY_AGGRO1,
    SAY_AGGRO2,
    SAY_AGGRO1,
    SAY_START_2,

    SPELL_CHAIN_LIGHTNING               = 16006,
    SPELL_EARTHBING_TOTEM               = 15786,
    SPELL_FROST_SHOCK                   = 12548,
    SPELL_HEALING_WAVE                  = 12491,
    SPELL_BUBBLE                        = 35929,
    SPELL_WATERY_PRISON                 = 35928,

    QUEST_ESCAPE_FROM_COILSKAR_CISTERN  = 10451,
    QUEST_ESCAPE_COILSCAR               = 10451,
    FACTION_EARTHEN                     = 1726, //guessed

    NPC_COILSKAR_ASSASSIN               = 21044,
    NPC_VISUAL_TRIGGER                  = 21310,
    NPC_WATER_SPIRIT                    = 21029,

    EVENT_PRISON_WILDA                  = 1,
    EVENT_FREED_WILDA,
    EVENT_RESTORE_NPC_FLAG,
    EVENT_FREE_ELEMENTAL,
    EVENT_ELEMENTAL_FOLLOW
};

class npc_earthmender_wilda : public CreatureScript
{
public:
    npc_earthmender_wilda() : CreatureScript("npc_earthmender_wilda") { }

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_ESCAPE_FROM_COILSKAR_CISTERN)
        {
            creature->setFaction(113);
            if (npc_earthmender_wildaAI* pEscortAI = CAST_AI(npc_earthmender_wildaAI, creature->AI()))
                pEscortAI->Start(false, false, player->GetGUID(), quest);
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        npc_earthmender_wildaAI* earthmender_wildaAI = new npc_earthmender_wildaAI(creature);
        earthmender_wildaAI->AddWaypoint(0, -2648.3f, 1355.91f, 35.2048f);
        earthmender_wildaAI->AddWaypoint(1, -2648.3f, 1355.91f, 35.2048f);
        earthmender_wildaAI->AddWaypoint(2, -2668.9f, 1347.68f, 34.4454f);
        earthmender_wildaAI->AddWaypoint(3, -2687.85f, 1338.78f, 34.4454f);
        earthmender_wildaAI->AddWaypoint(4, -2704.67f, 1330.64f, 34.4454f);
        earthmender_wildaAI->AddWaypoint(5, -2726.72f, 1319.96f, 33.3934f);
        earthmender_wildaAI->AddWaypoint(6, -2745.86f, 1311.33f, 33.6216f);
        earthmender_wildaAI->AddWaypoint(7, -2761.46f, 1297.27f, 33.2179f);
        earthmender_wildaAI->AddWaypoint(8, -2753.54f, 1277.31f, 33.4097f);
        earthmender_wildaAI->AddWaypoint(9, -2737.02f, 1253.25f, 33.4268f);
        earthmender_wildaAI->AddWaypoint(10, -2723.61f, 1237.14f, 33.4294f, 10000); // FREE ELEMENTALS
        earthmender_wildaAI->AddWaypoint(11, -2733.69f, 1251.44f, 33.7245f);
        earthmender_wildaAI->AddWaypoint(12, -2753.47f, 1278.85f, 33.3997f);
        earthmender_wildaAI->AddWaypoint(13, -2762.9f, 1293.56f, 33.209f);
        earthmender_wildaAI->AddWaypoint(14, -2737.7f, 1314.38f, 33.4618f);
        earthmender_wildaAI->AddWaypoint(15, -2721.36f, 1323.13f, 33.847f);
        earthmender_wildaAI->AddWaypoint(16, -2708.74f, 1307.83f, 33.0673f);
        earthmender_wildaAI->AddWaypoint(17, -2697.79f, 1291.25f, 33.9619f);
        earthmender_wildaAI->AddWaypoint(18, -2677.01f, 1283.67f, 30.2953f);
        earthmender_wildaAI->AddWaypoint(19, -2661.24f, 1279.51f, 26.5944f);
        earthmender_wildaAI->AddWaypoint(20, -2644.76f, 1264.76f, 23.5552f, 3000); // SAY PROGRESS
        earthmender_wildaAI->AddWaypoint(21, -2630.88f, 1250.65f, 17.73f);
        earthmender_wildaAI->AddWaypoint(22, -2638.11f, 1237.29f, 13.4125f);
        earthmender_wildaAI->AddWaypoint(23, -2648.96f, 1214.01f, 7.92752f);
        earthmender_wildaAI->AddWaypoint(24, -2660.74f, 1199.59f, 5.47501f);
        earthmender_wildaAI->AddWaypoint(25, -2677.96f, 1179.13f, 4.84202f);
        earthmender_wildaAI->AddWaypoint(26, -2693.49f, 1166.91f, 5.37836f);
        earthmender_wildaAI->AddWaypoint(27, -2706.32f, 1153.42f, 4.42537f);
        earthmender_wildaAI->AddWaypoint(28, -2715.87f, 1141.6f, 1.452f);
        earthmender_wildaAI->AddWaypoint(29, -2735.48f, 1138.9f, 3.05414f);
        earthmender_wildaAI->AddWaypoint(30, -2753.81f, 1146.88f, 5.83016f);
        earthmender_wildaAI->AddWaypoint(31, -2771.29f, 1162.3f, 6.46434f);
        earthmender_wildaAI->AddWaypoint(32, -2782.89f, 1173.76f, 6.0197f);
        earthmender_wildaAI->AddWaypoint(33, -2795.0f, 1189.45f, 5.22805f);
        earthmender_wildaAI->AddWaypoint(34, -2803.13f, 1200.84f, 6.33987f);
        earthmender_wildaAI->AddWaypoint(35, -2813.41f, 1216.36f, 6.26596f);
        earthmender_wildaAI->AddWaypoint(36, -2826.56f, 1231.18f, 6.17901f);
        earthmender_wildaAI->AddWaypoint(37, -2839.15f, 1243.21f, 6.48784f);
        earthmender_wildaAI->AddWaypoint(38, -2850.29f, 1253.52f, 7.05257f);
        earthmender_wildaAI->AddWaypoint(39, -2852.3f, 1266.18f, 6.88055f);
        earthmender_wildaAI->AddWaypoint(40, -2845.29f, 1276.82f, 6.96451f);
        earthmender_wildaAI->AddWaypoint(41, -2843.1f, 1283.38f, 7.68115f);
        earthmender_wildaAI->AddWaypoint(42, -2843.73f, 1291.55f, 6.5211f);
        earthmender_wildaAI->AddWaypoint(43, -2856.87f, 1296.37f, 6.80744f);
        earthmender_wildaAI->AddWaypoint(44, -2874.1f, 1303.6f, 6.66064f, 5000); // END

        return new npc_earthmender_wildaAI(creature);
    }
    struct npc_earthmender_wildaAI : public npc_escortAI
    {
        npc_earthmender_wildaAI(Creature* creature) : npc_escortAI(creature)
        {
            me->SetDisableGravity(true);
            me->SetHover(true);
            me->SetCanFly(true);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            events.Reset();
            events.ScheduleEvent(EVENT_PRISON_WILDA, 3s);
            elementalCounter = 0;
            angle = 0.0f;
            dist = 0.0f;
        }

        void Reset()
        {
            me->setFaction(1726);
            Completed = false;
        }

        void WaypointReached(uint32 waypointId)
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            switch (waypointId)
            {
            case 0: Talk(SAY_START_2); break;
            case 10:
                events.ScheduleEvent(EVENT_FREE_ELEMENTAL, 1s); break;
            case 15: Talk(SAY_PROGRESS1);
                SummonAssassin();
                break;
            case 20: SummonAssassin(); break;
            case 25:
                Talk(RAND(SAY_PROGRESS2, SAY_PROGRESS4, SAY_PROGRESS5));
                break;
            case 28: SummonAssassin(); break;
            case 31: Talk(SAY_PROGRESS6); break;
            case 35:
                Talk(RAND(SAY_PROGRESS2, SAY_PROGRESS4, SAY_PROGRESS5));
                break;
            case 40: SummonAssassin(); break;
            case 44:
                Talk(SAY_END);
                std::list<Creature*> _creatures;
                me->GetCreatureListWithEntryInGrid(_creatures, NPC_WATER_SPIRIT, 35.0f);
                std::for_each(_creatures.begin(), _creatures.end(), [](Creature* creature)
                {
                    creature->DespawnOrUnsummon();
                });
                player->GroupEventHappens(QUEST_ESCAPE_FROM_COILSKAR_CISTERN, 0);
                Completed = true;
                break;
            }
        }

        void JustRespawned()
        {
            npc_escortAI::JustRespawned();
            me->SetDisableGravity(true);
            me->SetHover(true);
            me->SetCanFly(true);
        }

        void JustDied(Unit* killer)
        {
            if (!Completed)
            {
                Player* player = GetPlayerForEscort();
                if (player)
                    player->FailQuest(QUEST_ESCAPE_FROM_COILSKAR_CISTERN);
            }
        }

        void JustSummoned(Creature* summoned)
        {
            if (summoned->GetEntry() == NPC_COILSKAR_ASSASSIN)
                summoned->AI()->AttackStart(me);
        }

        void SummonAssassin()
        {
            Player* player = GetPlayerForEscort();

            Unit* CoilskarAssassin = me->SummonCreature(NPC_COILSKAR_ASSASSIN, me->GetPositionX() - 1.0f, me->GetPositionY() - 1.0f, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0);
            if (CoilskarAssassin)
            {
                CoilskarAssassin->ToCreature()->AI()->Talk(RAND(ASSASSIN_SAY_AGGRO1, ASSASSIN_SAY_AGGRO2));

                ((Creature*)CoilskarAssassin)->AI()->AttackStart(me);
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            if (type == 4 && data == 4)
            {
                events.ScheduleEvent(EVENT_FREED_WILDA, 10s);
            }
        }
        void UpdateAI(uint32 uiDiff)
        {
            npc_escortAI::UpdateAI(uiDiff);

            if (!events.Empty())
            {
                events.Update(uiDiff);
                std::list<Creature*> _creatures;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_PRISON_WILDA:
                            me->GetCreatureListWithEntryInGrid(_creatures, NPC_VISUAL_TRIGGER, 35.0f);
                            for (std::list<Creature*>::const_iterator i = _creatures.begin(); i != _creatures.end(); ++i)
                            {
                                (*i)->CastSpell(me, SPELL_WATERY_PRISON, true);
                            };
                            DoCastSelf(SPELL_BUBBLE, true);
                            break;
                        case EVENT_FREED_WILDA:
                            me->GetMotionMaster()->MovePoint(70, { -2638.74f, 1359.6f, 35.94f, 3.62f });
                            me->GetCreatureListWithEntryInGrid(_creatures, NPC_VISUAL_TRIGGER, 35.0f);
                            std::for_each(_creatures.begin(), _creatures.end(), [](Creature* creature)
                            {
                                creature->DespawnOrUnsummon();
                            });
                            events.ScheduleEvent(EVENT_RESTORE_NPC_FLAG, 3s);
                            break;
                        case EVENT_RESTORE_NPC_FLAG:
                            me->RemoveAurasDueToSpell(SPELL_BUBBLE);
                            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                            me->SetDisableGravity(false);
                            me->SetHover(false);
                            me->SetCanFly(false);
                            break;
                        case EVENT_FREE_ELEMENTAL:
                            me->GetCreatureListWithEntryInGrid(_creatures, NPC_WATER_SPIRIT, 50.0f);
                            for (std::list<Creature*>::const_iterator i = _creatures.begin(); i != _creatures.end(); ++i)
                            {
                                switch (elementalCounter)
                                {
                                case 0:
                                    dist = 4.0f;
                                    angle = 0.6f * M_PI;
                                    break;
                                case 1:
                                    dist = 3.5f;
                                    angle = 0.8f * M_PI;
                                    break;
                                case 2:
                                    dist = 3.0f;
                                    angle = M_PI;
                                    break;
                                case 3:
                                    dist = 3.5f;
                                    angle = 1.2f * M_PI;
                                    break;
                                case 4:
                                    dist = 4.0f;
                                    angle = 1.4f * M_PI;
                                    break;
                                default:
                                    dist = urand(1, 4);
                                    angle = M_PI;
                                    break;
                                }

                                (*i)->RemoveAurasDueToSpell(SPELL_BUBBLE);
                                (*i)->GetMotionMaster()->MoveFollow(me, dist, angle);
                                elementalCounter++;
                            }
                            events.ScheduleEvent(EVENT_ELEMENTAL_FOLLOW, 3s);
                            break;
                        case EVENT_ELEMENTAL_FOLLOW:
                            std::list<Creature*> _creatures;
                            me->GetCreatureListWithEntryInGrid(_creatures, NPC_WATER_SPIRIT, 35.0f);
                            std::for_each(_creatures.begin(), _creatures.end(), [](Creature* creature)
                            {
                                creature->SetDisableGravity(false);
                                creature->SetHover(false);
                                creature->SetCanFly(false);
                            });
                            break;
                    }
                }
            }
        }

        private:
            bool Completed;
            EventMap events;
            uint8 elementalCounter;
            float angle;
            float dist;
    };
};

/*#####
# Quest: Battle of the crimson watch
#####*/

/* ContentData
Battle of the crimson watch - creatures, gameobjects and defines
npc_illidari_spawn : Adds that are summoned in the Crimson Watch battle.
npc_torloth_the_magnificent : Final Creature that players have to face before quest is completed
npc_lord_illidan_stormrage : Creature that controls the event.
go_crystal_prison : GameObject that begins the event and hands out quest
EndContentData */

#define QUEST_BATTLE_OF_THE_CRIMSON_WATCH 10781
#define EVENT_AREA_RADIUS 65 //65yds
#define EVENT_COOLDOWN 30000 //in ms. appear after event completed or failed (should be = Adds despawn time)

struct TorlothCinematic
{
    uint32 creature, Timer;
};

// Creature 0 - Torloth, 1 - Illidan
static TorlothCinematic TorlothAnim[]=
{
    {0, 2000},
    {1, 7000},
    {0, 3000},
    {0, 2000}, // Torloth stand
    {0, 1000},
    {0, 3000},
    {0, 0}
};

struct Location
{
    float x, y, z, o;
};

//Cordinates for Spawns
static Location SpawnLocation[]=
{
    //Cords used for:
    {-4615.8556f, 1342.2532f, 139.9f, 1.612f}, //Illidari Soldier
    {-4598.9365f, 1377.3182f, 139.9f, 3.917f}, //Illidari Soldier
    {-4598.4697f, 1360.8999f, 139.9f, 2.427f}, //Illidari Soldier
    {-4589.3599f, 1369.1061f, 139.9f, 3.165f}, //Illidari Soldier
    {-4608.3477f, 1386.0076f, 139.9f, 4.108f}, //Illidari Soldier
    {-4633.1889f, 1359.8033f, 139.9f, 0.949f}, //Illidari Soldier
    {-4623.5791f, 1351.4574f, 139.9f, 0.971f}, //Illidari Soldier
    {-4607.2988f, 1351.6099f, 139.9f, 2.416f}, //Illidari Soldier
    {-4633.7764f, 1376.0417f, 139.9f, 5.608f}, //Illidari Soldier
    {-4600.2461f, 1369.1240f, 139.9f, 3.056f}, //Illidari Mind Breaker
    {-4631.7808f, 1367.9459f, 139.9f, 0.020f}, //Illidari Mind Breaker
    {-4600.2461f, 1369.1240f, 139.9f, 3.056f}, //Illidari Highlord
    {-4631.7808f, 1367.9459f, 139.9f, 0.020f}, //Illidari Highlord
    {-4615.5586f, 1353.0031f, 139.9f, 1.540f}, //Illidari Highlord
    {-4616.4736f, 1384.2170f, 139.9f, 4.971f}, //Illidari Highlord
    {-4627.1240f, 1378.8752f, 139.9f, 2.544f} //Torloth The Magnificent
};

struct WaveData
{
    uint8 SpawnCount, UsedSpawnPoint;
    uint32 CreatureId, SpawnTimer, YellTimer;
};

static WaveData WavesInfo[]=
{
    {9, 0, 22075, 10000, 7000},   //Illidari Soldier
    {2, 9, 22074, 10000, 7000},   //Illidari Mind Breaker
    {4, 11, 19797, 10000, 7000},  //Illidari Highlord
    {1, 15, 22076, 10000, 7000}   //Torloth The Magnificent
};

struct SpawnSpells
{
 uint32 Timer1, Timer2, SpellId;
};

static SpawnSpells SpawnCast[]=
{
    {10000, 15000, 35871},  // Illidari Soldier Cast - Spellbreaker
    {10000, 10000, 38985},  // Illidari Mind Breake Cast - Focused Bursts
    {35000, 35000, 22884},  // Illidari Mind Breake Cast - Psychic Scream
    {20000, 20000, 17194},  // Illidari Mind Breake Cast - Mind Blast
    {8000, 15000, 38010},   // Illidari Highlord Cast - Curse of Flames
    {12000, 20000, 16102},  // Illidari Highlord Cast - Flamestrike
    {10000, 15000, 15284},  // Torloth the Magnificent Cast - Cleave
    {18000, 20000, 39082},  // Torloth the Magnificent Cast - Shadowfury
    {25000, 28000, 33961}   // Torloth the Magnificent Cast - Spell Reflection
};

/*######
# npc_torloth_the_magnificent
#####*/

class npc_torloth_the_magnificent : public CreatureScript
{
public:
    npc_torloth_the_magnificent() : CreatureScript("npc_torloth_the_magnificent") { }

    CreatureAI* GetAI(Creature* c) const
    {
        return new npc_torloth_the_magnificentAI(c);
    }

    struct npc_torloth_the_magnificentAI : public ScriptedAI
    {
        npc_torloth_the_magnificentAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 AnimationTimer, SpellTimer1, SpellTimer2, SpellTimer3;

        uint8 AnimationCount;

        uint64 LordIllidanGUID;
        uint64 AggroTargetGUID;

        bool Timers;

        void Reset()
        {
            AnimationTimer = 4000;
            AnimationCount = 0;
            LordIllidanGUID = 0;
            AggroTargetGUID = 0;
            Timers = false;

            me->AddUnitState(UNIT_STATE_ROOT);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetTarget(0);
        }

        void EnterCombat(Unit* /*who*/) { }

        void HandleAnimation()
        {
            Creature* creature = me;

            if (TorlothAnim[AnimationCount].creature == 1)
            {
                creature = (ObjectAccessor::GetCreature(*me, LordIllidanGUID));

                if (!creature)
                    return;
            }

            AnimationTimer = TorlothAnim[AnimationCount].Timer;

            switch (AnimationCount)
            {
            case 0:
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, 8);
                me->AI()->Talk(0);
                if (Creature* LordIllidan = (ObjectAccessor::GetCreature(*me, LordIllidanGUID)))
                    LordIllidan->AI()->Talk(12);
                break;
            case 3:
                me->RemoveFlag(UNIT_FIELD_BYTES_1, 8);
                me->AI()->Talk(1);
                break;
            case 5:
                if (Player* AggroTarget = ObjectAccessor::GetPlayer(*me, AggroTargetGUID))
                {
                    me->SetTarget(AggroTarget->GetGUID());
                    me->AddThreat(AggroTarget, 1);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                    me->AI()->Talk(2);
                }
                break;
            case 6:
                if (Player* AggroTarget = ObjectAccessor::GetPlayer(*me, AggroTargetGUID))
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->ClearUnitState(UNIT_STATE_ROOT);

                    float x, y, z;
                    AggroTarget->GetPosition(x, y, z);
                    me->GetMotionMaster()->MovePoint(0, x, y, z);
                }
                break;
            }
            ++AnimationCount;
        }

        void UpdateAI(uint32 diff)
        {
            if (AnimationTimer)
            {
                if (AnimationTimer <= diff)
                {
                    HandleAnimation();
                } else AnimationTimer -= diff;
            }

            if (AnimationCount < 6)
            {
                me->CombatStop();
            } else if (!Timers)
            {
                SpellTimer1 = SpawnCast[6].Timer1;
                SpellTimer2 = SpawnCast[7].Timer1;
                SpellTimer3 = SpawnCast[8].Timer1;
                Timers = true;
            }

            if (!UpdateVictim())
                return;

            if (Timers)
            {
                if (SpellTimer1 <= diff)
                {
                    DoCastVictim(SpawnCast[6].SpellId);//Cleave
                    SpellTimer1 = SpawnCast[6].Timer2 + (rand()%10 * 1000);
                } else SpellTimer1 -= diff;

                if (SpellTimer2 <= diff)
                {
                    DoCastVictim(SpawnCast[7].SpellId);//Shadowfury
                    SpellTimer2 = SpawnCast[7].Timer2 + (rand()%5 * 1000);
                } else SpellTimer2 -= diff;

                if (SpellTimer3 <= diff)
                {
                    DoCast(me, SpawnCast[8].SpellId);
                    SpellTimer3 = SpawnCast[8].Timer2 + (rand()%7 * 1000);//Spell Reflection
                } else SpellTimer3 -= diff;
            }

            DoMeleeAttackIfReady();
        }

        void EnterEvadeMode() override
        {
            if (Creature* LordIllidan = (ObjectAccessor::GetCreature(*me, LordIllidanGUID)))
                LordIllidan->AI()->EnterEvadeMode();
        }

        void JustDied(Unit* killer)
        {
            if (Creature* LordIllidan = (ObjectAccessor::GetCreature(*me, LordIllidanGUID)))
            {
                LordIllidan->AI()->Talk(11);
                if (Creature* Auralion = me->FindNearestCreature(22073, 50))
                    Auralion->AI()->Talk(1);
            }
            switch (killer->GetTypeId())
            {
                case TYPEID_UNIT:
                    if (Unit* owner = killer->GetOwner())
                        if (Player* player = owner->ToPlayer())
                            player->GroupEventHappens(QUEST_BATTLE_OF_THE_CRIMSON_WATCH, me);
                    break;
                case TYPEID_PLAYER:
                    if (Player* player = killer->ToPlayer())
                        player->GroupEventHappens(QUEST_BATTLE_OF_THE_CRIMSON_WATCH, me);
                    break;
                default:
                    break;
            }

            if (Creature* LordIllidan = (ObjectAccessor::GetCreature(*me, LordIllidanGUID)))
                LordIllidan->AI()->EnterEvadeMode();
        }
    };
};

/*#####
# npc_lord_illidan_stormrage
#####*/

class npc_lord_illidan_stormrage : public CreatureScript
{
public:
    npc_lord_illidan_stormrage() : CreatureScript("npc_lord_illidan_stormrage") { }

    CreatureAI* GetAI(Creature* c) const
    {
        return new npc_lord_illidan_stormrageAI(c);
    }

    struct npc_lord_illidan_stormrageAI : public ScriptedAI
    {
        npc_lord_illidan_stormrageAI(Creature* creature) : ScriptedAI(creature), summons(me) { }

        uint64 PlayerGUID;

        uint32 WaveTimer;
        uint32 AnnounceTimer;

        int8 LiveCount;
        uint8 WaveCount;

        bool EventStarted;
        bool Announced;
        bool Failed;

        SummonList summons;

        void Reset()
        {
            PlayerGUID = 0;

            WaveTimer = 10000;
            AnnounceTimer = 7000;
            LiveCount = 0;
            WaveCount = 0;

            EventStarted = false;
            Announced = false;
            Failed = false;

            me->SetVisible(false);

            summons.DespawnAll();
        }

        void EnterCombat(Unit* /*who*/) { }
        void MoveInLineOfSight(Unit* /*who*/) { }

        void AttackStart(Unit* /*who*/) { }

        void SummonNextWave();

        void JustSummoned(Creature* creature)
        {
            summons.Summon(creature);
        }

        void CheckEventFail()
        {
            Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
            if (!player)
            {
                Failed = true;
                return;
            }

            if (Group* EventGroup = player->GetGroup())
            {
                uint8 GroupMemberCount = 0;
                uint8 DeadMemberCount = 0;
                uint8 FailedMemberCount = 0;

                Group::MemberSlotList const& members = EventGroup->GetMemberSlots();

                for (Group::member_citerator itr = members.begin(); itr!= members.end(); ++itr)
                {
                    Player* GroupMember = ObjectAccessor::GetPlayer(*me, itr->guid);
                    if (!GroupMember)
                        continue;
                    if (!GroupMember->IsWithinDistInMap(me, EVENT_AREA_RADIUS) && GroupMember->GetQuestStatus(QUEST_BATTLE_OF_THE_CRIMSON_WATCH) == QUEST_STATUS_INCOMPLETE)
                    {
                        GroupMember->FailQuest(QUEST_BATTLE_OF_THE_CRIMSON_WATCH);
                        ++FailedMemberCount;
                    }
                    ++GroupMemberCount;

                    if (GroupMember->isDead())
                        ++DeadMemberCount;
                }

                if (GroupMemberCount == FailedMemberCount)
                {
                    Failed = true;
                }

                if (GroupMemberCount == DeadMemberCount)
                {
                    for (Group::member_citerator itr = members.begin(); itr!= members.end(); ++itr)
                    {
                        if (Player* groupMember = ObjectAccessor::GetPlayer(*me, itr->guid))
                            if (groupMember->GetQuestStatus(QUEST_BATTLE_OF_THE_CRIMSON_WATCH) == QUEST_STATUS_INCOMPLETE)
                                groupMember->FailQuest(QUEST_BATTLE_OF_THE_CRIMSON_WATCH);
                    }
                    Failed = true;
                }
            } else if (player->isDead() || !player->IsWithinDistInMap(me, EVENT_AREA_RADIUS))
            {
                player->FailQuest(QUEST_BATTLE_OF_THE_CRIMSON_WATCH);
                Failed = true;
            }
        }

        void LiveCounter()
        {
            --LiveCount;
            if (!LiveCount)
                Announced = false;
        }

        void UpdateAI(uint32 diff)
        {
            if (!PlayerGUID || !EventStarted)
                return;

            if (!LiveCount && WaveCount < 4)
            {
                if (!Announced && AnnounceTimer <= diff)
                {
                    Announced = true;
                }
                else
                    AnnounceTimer -= diff;

                if (WaveTimer <= diff)
                {
                    SummonNextWave();
                }
                else
                    WaveTimer -= diff;
            }
            CheckEventFail();

            if (Failed)
                EnterEvadeMode();
        }

        void SummonedCreatureDespawn(Creature* summon) override
        {
            // If any of summoned creatures was despawned for some reason - reset
            if (summon->IsAlive())
                Failed = true;
        }
    };
};

/*######
# npc_illidari_spawn
######*/

class npc_illidari_spawn : public CreatureScript
{
public:
    npc_illidari_spawn() : CreatureScript("npc_illidari_spawn") { }

    CreatureAI* GetAI(Creature* c) const
    {
        return new npc_illidari_spawnAI(c);
    }

    struct npc_illidari_spawnAI : public ScriptedAI
    {
        npc_illidari_spawnAI(Creature* creature) : ScriptedAI(creature) { }

        uint64 LordIllidanGUID;
        uint32 SpellTimer1, SpellTimer2, SpellTimer3, DespawnTimer;
        bool Timers;

        void Reset()
        {
            LordIllidanGUID = 0;
            Timers = false;
            DespawnTimer = 0;
        }

        void EnterCombat(Unit* /*who*/) { }

        void JustDied(Unit* /*killer*/)
        {
            me->RemoveCorpse();
            if (Creature* LordIllidan = (ObjectAccessor::GetCreature(*me, LordIllidanGUID)))
                if (LordIllidan)
                    CAST_AI(npc_lord_illidan_stormrage::npc_lord_illidan_stormrageAI, LordIllidan->AI())->LiveCounter();
        }

        void EnterEvadeMode() override
        {
            if (Creature* LordIllidan = (ObjectAccessor::GetCreature(*me, LordIllidanGUID)))
                LordIllidan->AI()->EnterEvadeMode();
        }

        void UpdateAI(uint32 diff)
        {
            // Reset event 30 seconds OOC
            if (!me->IsInCombat())
            {
                DespawnTimer += diff;
                if (DespawnTimer >= 30000)
                    if (Creature* LordIllidan = (ObjectAccessor::GetCreature(*me, LordIllidanGUID)))
                        LordIllidan->AI()->EnterEvadeMode();
            }
            else
                DespawnTimer = 0;

            if (!UpdateVictim())
                return;

            if (!Timers)
            {
                if (me->GetEntry() == 22075)//Illidari Soldier
                {
                    SpellTimer1 = SpawnCast[0].Timer1 + (rand()%4 * 1000);
                }
                if (me->GetEntry() == 22074)//Illidari Mind Breaker
                {
                    SpellTimer1 = SpawnCast[1].Timer1 + (rand()%10 * 1000);
                    SpellTimer2 = SpawnCast[2].Timer1 + (rand()%4 * 1000);
                    SpellTimer3 = SpawnCast[3].Timer1 + (rand()%4 * 1000);
                }
                if (me->GetEntry() == 19797)// Illidari Highlord
                {
                    SpellTimer1 = SpawnCast[4].Timer1 + (rand()%4 * 1000);
                    SpellTimer2 = SpawnCast[5].Timer1 + (rand()%4 * 1000);
                }
                Timers = true;
            }
            //Illidari Soldier
            if (me->GetEntry() == 22075)
            {
                if (SpellTimer1 <= diff)
                {
                    DoCastVictim(SpawnCast[0].SpellId);//Spellbreaker
                    SpellTimer1 = SpawnCast[0].Timer2 + (rand()%5 * 1000);
                } else SpellTimer1 -= diff;
            }
            //Illidari Mind Breaker
            if (me->GetEntry() == 22074)
            {
                if (SpellTimer1 <= diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    {
                        if (target->GetTypeId() == TYPEID_PLAYER)
                        {
                            DoCast(target, SpawnCast[1].SpellId); //Focused Bursts
                            SpellTimer1 = SpawnCast[1].Timer2 + (rand()%5 * 1000);
                        } else SpellTimer1 = 2000;
                    }
                } else SpellTimer1 -= diff;

                if (SpellTimer2 <= diff)
                {
                    DoCastVictim(SpawnCast[2].SpellId);//Psychic Scream
                    SpellTimer2 = SpawnCast[2].Timer2 + (rand()%13 * 1000);
                } else SpellTimer2 -= diff;

                if (SpellTimer3 <= diff)
                {
                    DoCastVictim(SpawnCast[3].SpellId);//Mind Blast
                    SpellTimer3 = SpawnCast[3].Timer2 + (rand()%8 * 1000);
                } else SpellTimer3 -= diff;
            }
            //Illidari Highlord
            if (me->GetEntry() == 19797)
            {
                if (SpellTimer1 <= diff)
                {
                    DoCastVictim(SpawnCast[4].SpellId);//Curse Of Flames
                    SpellTimer1 = SpawnCast[4].Timer2 + (rand()%10 * 1000);
                } else SpellTimer1 -= diff;

                if (SpellTimer2 <= diff)
                {
                    DoCastVictim(SpawnCast[5].SpellId);//Flamestrike
                    SpellTimer2 = SpawnCast[5].Timer2 + (rand()%7 * 13000);
                } else SpellTimer2 -= diff;
            }

            DoMeleeAttackIfReady();
        }
    };
};

void npc_lord_illidan_stormrage::npc_lord_illidan_stormrageAI::SummonNextWave()
{
    uint8 count = WavesInfo[WaveCount].SpawnCount;
    uint8 locIndex = WavesInfo[WaveCount].UsedSpawnPoint;
    uint8 FelguardCount = 0;
    uint8 DreadlordCount = 0;
    bool sayWave1 = false;
    bool sayWave2 = false;
    bool sayWave3 = false;

    for (uint8 i = 0; i < count; ++i)
    {
        Creature* Spawn = NULL;
        float X = SpawnLocation[locIndex + i].x;
        float Y = SpawnLocation[locIndex + i].y;
        float Z = SpawnLocation[locIndex + i].z;
        float O = SpawnLocation[locIndex + i].o;
        Spawn = me->SummonCreature(WavesInfo[WaveCount].CreatureId, X, Y, Z, O, TEMPSUMMON_MANUAL_DESPAWN);
        ++LiveCount;

        if (Spawn)
        {
            if (WaveCount == 0)//1 Wave
            {
                if (!sayWave1)
                {
                    me->AI()->Talk(7);
                    sayWave1 = true;
                }
                if (rand()%3 == 1 && FelguardCount<2)
                {
                    Spawn->SetDisplayId(18654);
                    ++FelguardCount;
                }
                else if (DreadlordCount < 3)
                {
                    Spawn->SetDisplayId(19991);
                    ++DreadlordCount;
                }
                else if (FelguardCount<2)
                {
                    Spawn->SetDisplayId(18654);
                    ++FelguardCount;
                }
            }
            else if (WaveCount == 1) //2 Wave Ann
            {
                if (!sayWave2)
                {
                    me->AI()->Talk(8);
                    sayWave2 = true;
                }
            }
            else if (WaveCount == 2) //3 Wave Ann
            {
                if (!sayWave3)
                {
                    me->AI()->Talk(9);
                    sayWave3 = true;
                }
            }

            if (WaveCount < 3)//1-3 Wave
            {
                if (PlayerGUID)
                {
                    if (Player* target = ObjectAccessor::GetPlayer(*me, PlayerGUID))
                    {
                        float x, y, z;
                        target->GetPosition(x, y, z);
                        Spawn->GetMotionMaster()->MovePoint(0, x, y, z);
                    }
                }
                CAST_AI(npc_illidari_spawn::npc_illidari_spawnAI, Spawn->AI())->LordIllidanGUID = me->GetGUID();
            }

            if (WavesInfo[WaveCount].CreatureId == 22076) // Torloth
            {
                me->AI()->Talk(10);
                CAST_AI(npc_torloth_the_magnificent::npc_torloth_the_magnificentAI, Spawn->AI())->LordIllidanGUID = me->GetGUID();
                if (PlayerGUID)
                    CAST_AI(npc_torloth_the_magnificent::npc_torloth_the_magnificentAI, Spawn->AI())->AggroTargetGUID = PlayerGUID;
            }
        }
    }
    ++WaveCount;
    WaveTimer = WavesInfo[WaveCount].SpawnTimer;
    AnnounceTimer = WavesInfo[WaveCount].YellTimer;
}

/*#####
# go_crystal_prison
######*/

class go_crystal_prison : public GameObjectScript
{
public:
    go_crystal_prison() : GameObjectScript("go_crystal_prison") { }

    bool OnQuestAccept(Player* player, GameObject* /*go*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_BATTLE_OF_THE_CRIMSON_WATCH)
        {
            Creature* Illidan = player->FindNearestCreature(22083, 50);
            if (Creature* Auralion = player->FindNearestCreature(22073, 50))
                Auralion->AI()->Talk(0);

            if (Illidan && !CAST_AI(npc_lord_illidan_stormrage::npc_lord_illidan_stormrageAI, Illidan->AI())->EventStarted)
            {
                CAST_AI(npc_lord_illidan_stormrage::npc_lord_illidan_stormrageAI, Illidan->AI())->PlayerGUID = player->GetGUID();
                CAST_AI(npc_lord_illidan_stormrage::npc_lord_illidan_stormrageAI, Illidan->AI())->LiveCount = 0;
                CAST_AI(npc_lord_illidan_stormrage::npc_lord_illidan_stormrageAI, Illidan->AI())->EventStarted=true;
            }
        }
     return true;
    }
};

/*####
# npc_enraged_spirits
####*/

enum Enraged_Dpirits
{
// QUESTS
    QUEST_ENRAGED_SPIRITS_FIRE_EARTH        = 10458,
    QUEST_ENRAGED_SPIRITS_AIR               = 10481,
    QUEST_ENRAGED_SPIRITS_WATER             = 10480,

    // Totem
    ENTRY_TOTEM_OF_SPIRITS                  = 21071,
    RADIUS_TOTEM_OF_SPIRITS                 = 15,

    // SPIRITS
    NPC_ENRAGED_EARTH_SPIRIT                = 21050,
    NPC_ENRAGED_FIRE_SPIRIT                 = 21061,
    NPC_ENRAGED_AIR_SPIRIT                  = 21060,
    NPC_ENRAGED_WATER_SPIRIT                = 21059,

    // SOULS
    NPC_EARTHEN_SOUL                        = 21073,
    NPC_FIERY_SOUL                          = 21097,
    NPC_ENRAGED_AIRY_SOUL                   = 21116,
    NPC_ENRAGED_WATERY_SOUL                 = 21109, // wrong model

    // SPELL KILLCREDIT - not working!?! - using KilledMonsterCredit
    SPELL_EARTHEN_SOUL_CAPTURED_CREDIT      = 36108,
    SPELL_FIERY_SOUL_CAPTURED_CREDIT        = 36117,
    SPELL_AIRY_SOUL_CAPTURED_CREDIT         = 36182,
    SPELL_WATERY_SOUL_CAPTURED_CREDIT       = 36171,

    // KilledMonsterCredit Workaround
    NPC_CREDIT_FIRE                         = 21094,
    NPC_CREDIT_WATER                        = 21095,
    NPC_CREDIT_AIR                          = 21096,
    NPC_CREDIT_EARTH                        = 21092,

    // Captured Spell / Buff
    SPELL_SOUL_CAPTURED                     = 36115,

    // Factions
    FACTION_ENRAGED_SOUL_FRIENDLY           = 35,
    FACTION_ENRAGED_SOUL_HOSTILE            = 14
};

class npc_enraged_spirit : public CreatureScript
{
public:
    npc_enraged_spirit() : CreatureScript("npc_enraged_spirit") { }

    CreatureAI* GetAI(Creature* creature) const
    {
    return new npc_enraged_spiritAI(creature);
    }

    struct npc_enraged_spiritAI : public ScriptedAI
    {
        npc_enraged_spiritAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() { }

        void EnterCombat(Unit* /*who*/) { }

        void JustDied(Unit* /*killer*/)
        {
            // always spawn spirit on death
            // if totem around
            // move spirit to totem and cast kill count
            uint32 entry = 0;
            uint32 credit = 0;

            switch (me->GetEntry())
            {
                  case NPC_ENRAGED_FIRE_SPIRIT:
                    entry  = NPC_FIERY_SOUL;
                    //credit = SPELL_FIERY_SOUL_CAPTURED_CREDIT;
                    credit = NPC_CREDIT_FIRE;
                    break;
                  case NPC_ENRAGED_EARTH_SPIRIT:
                    entry  = NPC_EARTHEN_SOUL;
                    //credit = SPELL_EARTHEN_SOUL_CAPTURED_CREDIT;
                    credit = NPC_CREDIT_EARTH;
                    break;
                  case NPC_ENRAGED_AIR_SPIRIT:
                    entry  = NPC_ENRAGED_AIRY_SOUL;
                    //credit = SPELL_AIRY_SOUL_CAPTURED_CREDIT;
                    credit = NPC_CREDIT_AIR;
                    break;
                  case NPC_ENRAGED_WATER_SPIRIT:
                    entry  = NPC_ENRAGED_WATERY_SOUL;
                    //credit = SPELL_WATERY_SOUL_CAPTURED_CREDIT;
                    credit = NPC_CREDIT_WATER;
                    break;
                default:
                    break;
            }

            // Spawn Soul on Kill ALWAYS!
            Creature* Summoned = NULL;
            Unit* totemOspirits = NULL;

            if (entry != 0)
                Summoned = DoSpawnCreature(entry, 0, 0, 1, 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 5000);

            // FIND TOTEM, PROCESS QUEST
            if (Summoned)
            {
                 totemOspirits = me->FindNearestCreature(ENTRY_TOTEM_OF_SPIRITS, RADIUS_TOTEM_OF_SPIRITS);
                 if (totemOspirits)
                 {
                     Summoned->setFaction(FACTION_ENRAGED_SOUL_FRIENDLY);
                     Summoned->GetMotionMaster()->MovePoint(0, totemOspirits->GetPositionX(), totemOspirits->GetPositionY(), Summoned->GetPositionZ());

                     if (Unit* owner = totemOspirits->GetOwner())
                         if (Player* player = owner->ToPlayer())
                             player->KilledMonsterCredit(credit, 0);
                     DoCast(totemOspirits, SPELL_SOUL_CAPTURED);
                 }
            }
        }
    };
};

enum ShadowMoonTuberEnum
{
    SPELL_WHISTLE               = 36652,
    SPELL_SHADOWMOON_TUBER      = 36462,

    NPC_BOAR_ENTRY              = 21195,
    GO_SHADOWMOON_TUBER_MOUND   = 184701,

    POINT_TUBER                 = 1,
    TYPE_BOAR                   = 1,
    DATA_BOAR                   = 1
};

class npc_shadowmoon_tuber_node : public CreatureScript
{
public:
    npc_shadowmoon_tuber_node() : CreatureScript("npc_shadowmoon_tuber_node") { }

    struct npc_shadowmoon_tuber_nodeAI : public ScriptedAI
    {
        npc_shadowmoon_tuber_nodeAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            tapped = false;
            tuberGUID = 0;
            resetTimer = 60000;
        }

        void SetData(uint32 id, uint32 data)
        {
            if (id == TYPE_BOAR && data == DATA_BOAR)
            {
                // Spawn chest GO
                DoCast(SPELL_SHADOWMOON_TUBER);

                // Despawn the tuber
                if (GameObject* tuber = me->FindNearestGameObject(GO_SHADOWMOON_TUBER_MOUND, 5.0f))
                {
                    tuberGUID = tuber->GetGUID();
                    // @Workaround: find how to properly despawn the GO
                    tuber->SetPhaseMask(2, true);
                }
            }
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (!tapped && spell->Id == SPELL_WHISTLE)
            {
                if (Creature* boar = me->FindNearestCreature(NPC_BOAR_ENTRY, 30.0f))
                {
                    // Disable trigger and force nearest boar to walk to him
                    tapped = true;
                    boar->SetWalk(false);
                    boar->GetMotionMaster()->MovePoint(POINT_TUBER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (tapped)
            {
                if (resetTimer <= diff)
                {
                    // Respawn the tuber
                    if (tuberGUID)
                        if (GameObject* tuber = ObjectAccessor::GetGameObject(*me, tuberGUID))
                        // @Workaround: find how to properly respawn the GO
                            tuber->SetPhaseMask(1, true);

                    Reset();
                }
                else
                    resetTimer -= diff;
            }
        }
    private:
        bool tapped;
        uint64 tuberGUID;
        uint32 resetTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shadowmoon_tuber_nodeAI(creature);
    }
};

enum karsius
{
    EMOTE_STATE_KARSIUS         = 333,
    SPELL_KARSIUS_TERON_GORE    = 37748,
    SPELL_KARSIUS_FORCE_REACT   = 37782,
    NPC_KARS_TERON              = 21867,
    NPC_KARS_ANCIENT_SHADOW     = 21797,
    NPC_KARS_CHAINS             = 21876,

    EVENT_CHECK_FLAGS           = 1
};

class npc_karsius_the_ancient : public CreatureScript
{
public:
    npc_karsius_the_ancient() : CreatureScript("npc_karsius_the_ancient") { }

    struct npc_karsius_the_ancient_AI : public ScriptedAI
    {
        npc_karsius_the_ancient_AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            if (Creature* ancient = me->FindNearestCreature(NPC_KARS_TERON, 100.0f, true))
                ancient->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
        }

        void SetData(uint32 type, uint32 value) override
        {
            if (type == 2 && value == 2)
                me->DespawnOrUnsummon();
        }

        void JustDied(Unit* /*killer*/) override
        {
            std::list<Creature*> tempList;
            me->GetCreatureListWithEntryInGrid(tempList, NPC_KARS_CHAINS, 100.0f);
            for (auto i : tempList)
                if (Creature* chain = i)
                    chain->DespawnOrUnsummon();

            if (Creature* ancient = me->FindNearestCreature(NPC_KARS_TERON, 100.0f, true))
            {
                ancient->RemoveAurasDueToSpell(SPELL_KARSIUS_TERON_GORE);
                ancient->AI()->SetData(1, 1);
            }

            if (Player* player = me->SelectNearestPlayer(100.0f))
                if (player->HasAura(SPELL_KARSIUS_FORCE_REACT))
                    player->RemoveAurasDueToSpell(SPELL_KARSIUS_FORCE_REACT);
            Talk(1);
        }

        void EnterEvadeMode() override
        {
            if (Player* player = me->SelectNearestPlayer(100.0f))
                if (player->HasAura(SPELL_KARSIUS_FORCE_REACT))
                    player->RemoveAurasDueToSpell(SPELL_KARSIUS_FORCE_REACT);

            std::list<Creature*> tempList;
            me->GetCreatureListWithEntryInGrid(tempList, NPC_KARS_CHAINS, 100.0f);
            for (auto i : tempList)
                if (Creature* chain = i)
                    chain->DespawnOrUnsummon();

            if (Creature* ancient = me->FindNearestCreature(NPC_KARS_TERON, 100.0f, true))
                ancient->DespawnOrUnsummon();

            if (Creature* teron = me->FindNearestCreature(NPC_KARS_ANCIENT_SHADOW, 100.0f, true))
                teron->DespawnOrUnsummon();

            me->DespawnOrUnsummon();
        }

        bool CanAIAttack(Unit const* target) const override
        {
            return target->GetTypeId() == TYPEID_UNIT;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_karsius_the_ancient_AI(creature);
    }
};

/*####
# Dragonmaw Race quest chain
####*/
enum DragonmawRaceData
{
    SPELL_SKY_SHATTER = 40945,
    QUEST_CAPTAIN_SKYSHATTER = 11071,
    NPC_DRAGONMAW_RACE_SKYSHATTERS_TARGET = 23361,
    MAX_MISSLES = 5,
    SAY_START = 0,
    SAY_FINISH = 1
};
/*####
# Dragonmaw race 6: npc_captain_skyshatter
####*/
class npc_captain_skyshatter : public CreatureScript
{
public:
    npc_captain_skyshatter() : CreatureScript("npc_captain_skyshatter") { }

    bool OnQuestAccept(Player* player, Creature* creature, const Quest *quest) override
    {
        if (quest->GetQuestId() == QUEST_CAPTAIN_SKYSHATTER)
        {
            if (npc_captain_skyshatterAI* tropeAI = CAST_AI(npc_captain_skyshatter::npc_captain_skyshatterAI, creature->AI()))
            {
                tropeAI->Start(false, false, player->GetGUID(), quest, true, true);
                tropeAI->Talk(SAY_START, player);
                return true;
            }
        }
        return false;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_captain_skyshatterAI(creature);
    }

    struct npc_captain_skyshatterAI : public npc_escortAI
    {
        npc_captain_skyshatterAI(Creature* creature) : npc_escortAI(creature) {}

        void Reset() override
        {
            me->setActive(false);
            if (!HasEscortState(STATE_ESCORT_ESCORTING))
            {
                me->SetCanFly(false);
                me->SetWalk(true);
                SetMaxPlayerDistance(100.0f);
                SetDespawnAtFar(false);
                rangeCheckTimer = 2000;

                for (int i = 0; i < MAX_MISSLES; i++)
                    missleTimer[i] = 0;

                if (CreatureTemplate const* cinfo = me->GetCreatureTemplate())
                    me->SetUInt32Value(UNIT_NPC_FLAGS, cinfo->npcflag);
            }
            me->SetSpeedRate(MOVE_RUN, 1.14f);
        }

        void UpdateEscortAI(uint32 const diff) override
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            if (rangeCheckTimer <= diff)
            {
                if (!me->IsWithinDistInMap(player, 60.0f))
                {
                    if (player->GetQuestStatus(QUEST_CAPTAIN_SKYSHATTER) == QUEST_STATUS_INCOMPLETE)
                        player->FailQuest(QUEST_CAPTAIN_SKYSHATTER);

                    me->setActive(true);
                    float homeX, homeY, homeZ, homeOrient;
                    me->GetRespawnPosition(homeX, homeY, homeZ, &homeOrient);
                    me->NearTeleportTo(homeX, homeY, homeZ, homeOrient);
                    JustRespawned();
                }
                rangeCheckTimer = 2000;
            }
            else
                rangeCheckTimer -= diff;

            for (int i = 0; i < MAX_MISSLES; i++)
            {
                if (missleTimer[i] != 0 && missleTimer[i] <= diff)
                {
                    if (target = me->SummonCreature(NPC_DRAGONMAW_RACE_SKYSHATTERS_TARGET, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ()), TEMPSUMMON_TIMED_DESPAWN, 5000)
                    {
                        me->CastSpell(target, SPELL_SKY_SHATTER, true);
                        missleTimer[i] = 0;

                        if (i == MAX_MISSLES - 1)
                        {
                            missleTimer[0] = urand(4000, 8000);
                            for (int j = 1; j < MAX_MISSLES; j++)
                                missleTimer[j] = missleTimer[j - 1] + urand(300, 1000);
                        }
                    }
                }
                else
                    missleTimer[i] -= diff;
            }

        }

        void WaypointReached(uint32 waypointId) override
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            if (waypointId == 5)
            {
                missleTimer[0] = urand(4000, 8000);
                for (int j = 1; j < MAX_MISSLES; j++)
                    missleTimer[j] = missleTimer[j - 1] + urand(300, 1000);
            }

            switch (waypointId)
            {
            case 3:
                Talk(2, player);
                me->SetReactState(REACT_PASSIVE);
            case 4:
                me->SetWalk(false);
                me->SetCanFly(true);
                break;
            case 5:
                me->SetSpeedRate(MOVE_FLIGHT, 3.5f);
                me->SetSpeedRate(MOVE_RUN, 3.5f);
                break;
            case 43:
                me->SetSpeedRate(MOVE_RUN, 1.0f);
                for (int i = 0; i < MAX_MISSLES; i++)
                    missleTimer[i] = 0;
                break;
            case 44:
                me->SetWalk(true);
                me->SetCanFly(false);
                break;
            case 45:
                Talk(SAY_FINISH, player);
                player->AreaExploredOrEventHappens(QUEST_CAPTAIN_SKYSHATTER);
                break;
            case 47:
                me->Respawn(true);
                break;
            }
        }

    private:
        uint32 missleTimer[MAX_MISSLES];
        uint32 rangeCheckTimer;
        TempSummon* target;

    };
};

void AddSC_shadowmoon_valley()
{
    // Ours
    new spell_q10612_10613_the_fel_and_the_furious();
    new spell_q10563_q10596_to_legion_hold();
    new npc_karsius_the_ancient();

    // Theirs
    new npc_invis_infernal_caster();
    new npc_infernal_attacker();
    new npc_mature_netherwing_drake();
    new npc_enslaved_netherwing_drake();
    new npc_dragonmaw_peon();
    new npc_drake_dealer_hurlunk();
    new npcs_flanis_swiftwing_and_kagrosh();
    new npc_karynaku();
    new npc_earthmender_wilda();
    new npc_lord_illidan_stormrage();
    new go_crystal_prison();
    new npc_illidari_spawn();
    new npc_torloth_the_magnificent();
    new npc_enraged_spirit();
    new npc_shadowmoon_tuber_node();
    new npc_captain_skyshatter();
}
