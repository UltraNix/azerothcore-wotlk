/*
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

/*
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "npc_pet_dk_".
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "CombatAI.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "SpellAuraEffects.h"
#include "PassiveAI.h"

enum DeathKnightSpells
{
    SPELL_DK_SUMMON_GARGOYLE_1 = 49206,
    SPELL_DK_SUMMON_GARGOYLE_2 = 50514,
    SPELL_DK_DISMISS_GARGOYLE  = 50515,
    SPELL_DK_SANCTUARY         = 54661,
    SPELL_DK_NIGHT_OF_THE_DEAD = 62137,
    SPELL_DK_PET_SCALING       = 61017
};

class npc_pet_dk_ebon_gargoyle : public CreatureScript
{
    public:
        npc_pet_dk_ebon_gargoyle() : CreatureScript("npc_pet_dk_ebon_gargoyle") { }

        struct npc_pet_dk_ebon_gargoyleAI : ScriptedAI
        {
            npc_pet_dk_ebon_gargoyleAI(Creature* creature) : ScriptedAI(creature)
            {
                _despawnTimer = 36000; // 30 secs + 4 fly out + 2 initial attack timer
                _checkGhoulTimer = 500;
                _despawning = false;
                _initialSelection = true;
                _atStayCommand = false;
                _atFollowCommand = false;
                _atAttackCommand = false;
                _withGhoul       = false;
                _targetGUID = 0;
            }

            void MovementInform(uint32 type, uint32 point)
            {
                if (type == POINT_MOTION_TYPE && point == 1)
                {
                    me->SetCanFly(false);
                    me->SetDisableGravity(false);
                }
            }

            void InitializeAI()
            {
                ScriptedAI::InitializeAI();
                Unit* owner = me->GetOwner();
                if (!owner)
                    return;

                // Xinef: Night of the Dead avoidance
                if (Aura *aur = me->GetAura(SPELL_DK_NIGHT_OF_THE_DEAD))
                    if (Unit* owner = me->GetOwner())
                        if (AuraEffect *aurEff = owner->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_DEATHKNIGHT, 2718, 0))
                            if (aur->GetEffect(0))
                                aur->GetEffect(0)->SetAmount(-aurEff->GetSpellInfo()->Effects[EFFECT_2].CalcValue());

                float tz = me->GetMap()->GetHeight(me->GetPhaseMask(), me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), true, MAX_FALL_DISTANCE);
                me->GetMotionMaster()->MoveCharge(me->GetPositionX(), me->GetPositionY(), tz, 7.0f, 1);
                me->AddUnitState(UNIT_STATE_NO_ENVIRONMENT_UPD);
                me->SetCanFly(true);
                me->SetDisableGravity(true);
                _selectionTimer = 2000;
                _initialCastTimer = 0;
            }

            void MySelectNextTarget()
            {
                if (!_withGhoul)
                {
                    Unit* owner = me->GetOwner();
                    if (owner && owner->GetTypeId() == TYPEID_PLAYER && (!me->GetVictim() || me->GetVictim()->IsImmunedToSpell(sSpellMgr->GetSpellInfo(51963)) || !me->IsValidAttackTarget(me->GetVictim()) || !owner->CanSeeOrDetect(me->GetVictim())))
                    {
                        Unit* selection = owner->ToPlayer()->GetSelectedUnit();
                        if (selection && selection != me->GetVictim() && me->IsValidAttackTarget(selection))
                        {
                            me->GetMotionMaster()->Clear(false);
                            SetGazeOn(selection);
                        }
                        else if (!me->GetVictim() || !owner->CanSeeOrDetect(me->GetVictim()))
                        {
                            me->CombatStop(true);
                            me->GetMotionMaster()->Clear(false);
                            me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, 0.0f);
                            RemoveTargetAura();
                        }
                    }
                }
            }

            void AttackStart(Unit* who)
            {
                RemoveTargetAura();
                _targetGUID = who->GetGUID();
                me->AddAura(SPELL_DK_SUMMON_GARGOYLE_1, who);
                ScriptedAI::AttackStart(who);
            }

            void RemoveTargetAura()
            {
                if (Unit* target = ObjectAccessor::GetUnit(*me, _targetGUID))
                    target->RemoveAura(SPELL_DK_SUMMON_GARGOYLE_1, me->GetGUID());
            }

            void Reset()
            {
                _selectionTimer = 0;
                me->SetReactState(REACT_PASSIVE);
                MySelectNextTarget();
            }

            // Fly away when dismissed
            void FlyAway()
            {
                RemoveTargetAura();

                // Stop Fighting
                me->CombatStop(true);
                me->ApplyModFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE, true);

                // Sanctuary
                me->CastSpell(me, SPELL_DK_SANCTUARY, true);
                me->SetReactState(REACT_PASSIVE);

                me->SetSpeedRate(MOVE_FLIGHT, 1.0f);
                me->SetSpeedRate(MOVE_RUN, 1.0f);
                float x = me->GetPositionX() + 20 * cos(me->GetOrientation());
                float y = me->GetPositionY() + 20 * sin(me->GetOrientation());
                float z = me->GetPositionZ() + 40;
                me->DisableSpline();
                me->GetMotionMaster()->Clear(false);

                me->GetMotionMaster()->MoveCharge(x, y, z, 7.0f, 1);
                me->SetCanFly(true);
                me->SetDisableGravity(true);

                _despawning = true;
            }

            void GhoulAI()
            {
                Unit* owner = me->GetOwner();
                if (!owner)
                    return;

                Unit* Ghoul = owner->GetFirstMinion();

                if (!Ghoul)
                {
                    _withGhoul = false;
                    return;
                }
                else
                    _withGhoul = true;

                CharmInfo* charmInfo = Ghoul->GetCharmInfo();

                if (!charmInfo)
                    return;

                if (_withGhoul)
                {
                    // Ghoul: COMMAND_STAY
                    if (charmInfo->HasCommandState(COMMAND_STAY) && !_atStayCommand)
                    {
                        // Return to previous position where stay was clicked
                        if (me->GetMotionMaster()->GetMotionSlotType(MOTION_SLOT_CONTROLLED) == NULL_MOTION_TYPE)
                        {
                            me->StopMovingOnCurrentPos();
                            me->GetMotionMaster()->Clear(false);
                            me->GetMotionMaster()->MoveIdle();
                        }

                        _atStayCommand = true; _atFollowCommand = false; _atAttackCommand = false;
                    }
                    // Ghoul: COMMAND_FOLLOW
                    else if (charmInfo->HasCommandState(COMMAND_FOLLOW) && !_atFollowCommand && !_initialSelection && !Ghoul->GetVictim())
                    {
                        if (me->GetMotionMaster()->GetMotionSlotType(MOTION_SLOT_CONTROLLED) == NULL_MOTION_TYPE)
                        {
                            me->AttackStop();
                            me->InterruptNonMeleeSpells(false);
                            me->SetTarget(0);
                            me->ClearInCombat();
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle());
                        }

                        _atStayCommand = false; _atFollowCommand = true; _atAttackCommand = false;
                    }
                    // Ghoul: COMMAND_ATTACK
                    else if (Ghoul->GetVictim())
                    {
                        if (me->GetVictim() != Ghoul->GetVictim())
                        {
                            me->InterruptNonMeleeSpells(false);
                            AttackStart(Ghoul->GetVictim());
                        }
                        if (_atStayCommand || _atFollowCommand)
                        {
                            _atStayCommand = false; _atFollowCommand = false;
                        }
                    }
                }
            }
            void UpdateAI(uint32 diff)
            {
                if (_initialSelection)
                {
                    _initialSelection = false;
                    // Find victim of Summon Gargoyle spell
                    std::list<Unit*> targets;
                    Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(me, me, 50);
                    Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                    me->VisitNearbyObject(50, searcher);
                    for (std::list<Unit*>::const_iterator iter = targets.begin(); iter != targets.end(); ++iter)
                        if ((*iter)->GetAura(SPELL_DK_SUMMON_GARGOYLE_1, me->GetOwnerGUID()))
                        {
                            (*iter)->RemoveAura(SPELL_DK_SUMMON_GARGOYLE_1, me->GetOwnerGUID());
                            SetGazeOn(*iter);
                            _targetGUID = (*iter)->GetGUID();
                            break;
                        }
                }

                if (_checkGhoulTimer <= diff)
                    GhoulAI();
                else
                    _checkGhoulTimer -= diff;

                if (_despawnTimer > 4000)
                {
                    _despawnTimer -= diff;

                    if (!_withGhoul)
                    {
                        if (!UpdateVictimWithGaze())
                        {
                            MySelectNextTarget();
                            return;
                        }
                    }

                    _initialCastTimer += diff;

                    if (!_withGhoul)
                    {
                        _selectionTimer += diff;

                        if (_selectionTimer >= 1000)
                        {
                            MySelectNextTarget();
                            _selectionTimer = 0;
                        }
                    }

                    if (_initialCastTimer >= 2000 && !me->HasUnitState(UNIT_STATE_CASTING|UNIT_STATE_LOST_CONTROL) && me->GetMotionMaster()->GetMotionSlotType(MOTION_SLOT_CONTROLLED) == NULL_MOTION_TYPE)
                        me->CastSpell(me->GetVictim(), 51963, false);
                }
                else
                {
                    if (!_despawning)
                        FlyAway();

                    if (_despawnTimer > diff)
                        _despawnTimer -= diff;
                    else
                        me->DespawnOrUnsummon();
                }
            }

        private:
            uint64 _targetGUID;
            uint32 _despawnTimer;
            uint32 _selectionTimer;
            uint32 _initialCastTimer;
            uint32 _checkGhoulTimer;
            bool _despawning;
            bool _initialSelection;
            bool _atStayCommand;
            bool _atFollowCommand;
            bool _atAttackCommand;
            bool _withGhoul;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_pet_dk_ebon_gargoyleAI(creature);
        }
};

class npc_pet_dk_ghoul : public CreatureScript
{
    public:
        npc_pet_dk_ghoul() : CreatureScript("npc_pet_dk_ghoul") { }

        struct npc_pet_dk_ghoulAI : public CombatAI
        {
            npc_pet_dk_ghoulAI(Creature *c) : CombatAI(c) { }

            void JustDied(Unit *who)
            {
                if (me->IsGuardian() || me->IsSummon())
                    me->ToTempSummon()->UnSummon();
            }

            void UpdateAI(uint32 diff)
            {
                if (me->GetVictim() || UpdateVictim())
                {
                    events.Update(diff);

                    if (me->HasUnitState(UNIT_STATE_CASTING))
                        return;

                    if (uint32 spellId = events.ExecuteEvent())
                    {
                        DoCast(spellId);
                        events.ScheduleEvent(spellId, AISpellInfo[spellId].cooldown + rand() % AISpellInfo[spellId].cooldown);
                    }
                    else
                        DoMeleeAttackIfReady();
                }
            }
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_pet_dk_ghoulAI (pCreature);
        }
};

class npc_pet_dk_army_of_the_dead : public CreatureScript
{
    public:
        npc_pet_dk_army_of_the_dead() : CreatureScript("npc_pet_dk_army_of_the_dead") { }

        struct npc_pet_dk_army_of_the_deadAI : public CombatAI
        {
            npc_pet_dk_army_of_the_deadAI(Creature* creature) : CombatAI(creature) { }

            void InitializeAI()
            {
                CombatAI::InitializeAI();
                ((Minion*)me)->SetFollowAngle(rand_norm()*2*M_PI);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_pet_dk_army_of_the_deadAI (creature);
        }
};

enum DancingRuneWeapon
{
    SPELL_DK_DRW_COPY_VISUAL     = 53160, // Copies weapon visual from owner
    SPELL_DK_DANCING_RUNE_WEAPON = 49028, // EFFECT_2 is aura applied on current DK target when summoning DRW, Rune Weapon should attack this target
    SPELL_DK_DRW_SCALING         = 51906, // Reduces damage by 50%
};

struct npc_pet_dk_dancing_rune_weaponAI : public ScriptedAI
{
    npc_pet_dk_dancing_rune_weaponAI(Creature* creature) : ScriptedAI(creature)
    {
        // Needed to load proper weapon model
        EnterEvadeMode();
    }

    void SelectNextTarget()
    {
        Unit* owner = me->GetOwner();
        if (owner && owner->IsPlayer() && (!me->GetVictim() || !me->IsValidAttackTarget(me->GetVictim()) || !owner->CanSeeOrDetect(me->GetVictim())))
        {
            Unit* selection = owner->ToPlayer()->GetSelectedUnit();
            if (selection && selection != me->GetVictim() && me->IsValidAttackTarget(selection))
            {
                me->GetMotionMaster()->Clear(false);
                SetGazeOn(selection);
                _targetGUID = selection->GetGUID();
            }
            else if (!me->GetVictim() || !owner->CanSeeOrDetect(me->GetVictim()))
            {
                me->CombatStop(true);
                me->GetMotionMaster()->Clear(false);
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, 0.0f);
            }
        }
    }

    void IsSummonedBy(Unit* summoner) override
    {
        if (!summoner)
            return;

        _changeTargetTimer.Reset(1000);
        _targetGUID = 0;
        me->SetDefensive();
        DoCastSelf(SPELL_WARLOCK_PET_SCALING_05, true);
        DoCastSelf(SPELL_DK_PET_SCALING_03, true);
        DoCastSelf(SPELL_DK_DRW_SCALING, true);
        DoCastSelf(SPELL_DK_DRW_COPY_VISUAL, true);
    }

    // Called from spell_dk_dancing_rune_weapon_AuraScript::HandleEffectApply
    void SetGUID(uint64 guid, int32 /*id*/) override
    {
        _targetGUID = guid;
        if (Unit* target = ObjectAccessor::GetUnit(*me, guid))
            SetGazeOn(target);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictimWithGaze())
        {
            SelectNextTarget();
            return;
        }

        if (Unit* target = ObjectAccessor::GetUnit(*me, _targetGUID))
            if (!target || !target->IsInWorld() || !target->IsAlive())
            {
                _changeTargetTimer.Update(diff);
                if (_changeTargetTimer.Passed())
                {
                    SelectNextTarget();
                    _changeTargetTimer.Reset(1000);
                    return;
                }
            }

        DoMeleeAttackIfReady();
    }

    private:
        uint64 _targetGUID;
        TimeTrackerSmall _changeTargetTimer;
};

void AddSC_deathknight_pet_scripts()
{
    new npc_pet_dk_ebon_gargoyle();
    new npc_pet_dk_ghoul();
    new npc_pet_dk_army_of_the_dead();
    new CreatureAILoader<npc_pet_dk_dancing_rune_weaponAI>("npc_pet_dk_dancing_rune_weapon");
}
