/*
 * Copyright (C) 2008-2014 Hellground <http://hellground.net/>
 * Copyright (C) 2018- Sunwell <https://sunwell.pl/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "chess_event.h"

//trigger AI
move_triggerAI::move_triggerAI(Creature *c) : NullCreatureAI(c)
{
    pInstance = me->GetInstanceScript();
    pos.Relocate(me->GetPosition());
    me->CanMissSpells();
}

void move_triggerAI::Reset()
{
    moveTimer = 2000;
    pieceStance = PIECE_NONE;
    unitToMove = 0;
}

void move_triggerAI::SpellHit(Unit *caster,const SpellInfo *spell)
{
    if (pieceStance != PIECE_NONE)
        return;

    switch (spell->Id)
    {
        case SPELL_MOVE_1:
        case SPELL_MOVE_2:
        case SPELL_MOVE_3:
        case SPELL_MOVE_4:
        case SPELL_MOVE_5:
        case SPELL_MOVE_6:
        case SPELL_MOVE_7:
        case SPELL_CHANGE_FACING:
        {
            boss_MedivhAI * medivh = (boss_MedivhAI*)(pInstance->GetCreature(DATA_ECHO_OF_MEDIVH)->AI());
            if (medivh)
            {
                if (spell->Id == SPELL_CHANGE_FACING || medivh->CanMoveTo(me->GetGUID(), caster->GetGUID()))
                {
                    medivh->AddTriggerToMove(me->GetGUID(), caster->GetGUID(), caster->GetCharmerOrOwnerPlayerOrPlayerItself() ? true : false);

                    me->CastSpell(me, SPELL_MOVE_PREVISUAL, false);

                    unitToMove = caster->GetGUID();

                    if (spell->Id == SPELL_CHANGE_FACING)
                        pieceStance = PIECE_CHANGE_FACING;
                    else
                        pieceStance = PIECE_MOVE;
                    me->SetObjectScale(2.f);
                }
            }

            break;
        }
        default:
            break;
    }
}

void move_triggerAI::MakeMove()
{
    ChessPiecesStances tmpStance = pieceStance;

    moveTimer = 2000;
    pieceStance = PIECE_NONE;
    me->SetObjectScale(1.f);
    Creature * temp = pInstance->instance->GetCreature(unitToMove);
    Creature * temp2 = pInstance->GetCreature(DATA_ECHO_OF_MEDIVH);

    if (!temp || !temp->IsAlive())
    {
        unitToMove = 0;
        return;
    }

    temp->GetMotionMaster()->Clear();
    temp->GetMotionMaster()->MoveIdle();
    temp->SetControlled(false, UNIT_STATE_ROOT);

    switch (tmpStance)
    {
        case PIECE_MOVE:
            me->CastSpell(me, SPELL_MOVE_MARKER, false);
            
            temp->GetMotionMaster()->MovePoint(0, pos);
            ((npc_chesspieceAI*)temp->AI())->SetCurrentPosition(pos);
            temp->CastSpell(temp, SPELL_MOVE_CD, false);

            if (temp2)
            {
                ((boss_MedivhAI*)temp2->AI())->ChangePlaceInBoard(unitToMove, me->GetGUID());
                ((boss_MedivhAI*)temp2->AI())->RemoveFromMoveList(me->GetGUID());
            }
            break;
        case PIECE_CHANGE_FACING:
            if (temp2)
            {
                ((boss_MedivhAI*)temp2->AI())->ChangePieceFacing(temp, me);
                ((boss_MedivhAI*)temp2->AI())->RemoveFromMoveList(me->GetGUID());
            }
            break;
        default:
            break;
    }

    unitToMove = 0;
}

void move_triggerAI::RemoveFromMove(uint64 const& piece)
{
    if (unitToMove == piece)
    {
        pieceStance = PIECE_NONE;
        unitToMove = 0;
        moveTimer = 2000;
    }
}

void move_triggerAI::DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*damageSchoolMask*/)
{
    damage = 0;
}

void move_triggerAI::UpdateAI(const uint32 diff)
{
    if (pInstance->GetData(DATA_CHESS_EVENT) != IN_PROGRESS)
        return;

    if (pieceStance)
    {
        if (moveTimer < diff)
            MakeMove();
        else
            moveTimer -= diff;
    }
}

//Chesspieces AI

class npc_chesspiece : public CreatureScript
{
public:
    npc_chesspiece() : CreatureScript("npc_chesspiece") { }

    bool OnGossipHello(Player* player, Creature* _Creature) 
    { 
        InstanceScript* pInstance = _Creature->GetInstanceScript();

        if (!pInstance)
            return false;

        if (pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_ALLIANCE && _Creature->getFaction() != A_FACTION)
            return true;

        if (pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_HORDE && _Creature->getFaction() != H_FACTION)
            return true;

        if (player->HasAura(SPELL_RECENTLY_IN_GAME) || _Creature->HasAura(SPELL_RECENTLY_IN_GAME))
        {
            player->SEND_GOSSIP_MENU(10505, _Creature->GetGUID());
            return true;
        }

        if (pInstance->GetData(DATA_CHESS_EVENT) != IN_PROGRESS)
            if (_Creature->GetEntry() != NPC_KING_A && _Creature->GetEntry() != NPC_KING_H)
                return true;

        if (!(_Creature->isPossessedByPlayer()))
        {
            switch (_Creature->GetEntry())
            {
            case NPC_PAWN_H:
                player->ADD_GOSSIP_ITEM(0, "Control Orc Grunt", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(10425, _Creature->GetGUID());
                break;
            case NPC_PAWN_A:
                player->ADD_GOSSIP_ITEM(0, "Control Human Footman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(8952, _Creature->GetGUID());
                break;
            case NPC_KNIGHT_H:
                player->ADD_GOSSIP_ITEM(0, "Control Orc Wolf", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(10439, _Creature->GetGUID());
                break;
            case NPC_KNIGHT_A:
                player->ADD_GOSSIP_ITEM(0, "Control Human Charger", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(10414, _Creature->GetGUID());
                break;
            case NPC_QUEEN_H:
                player->ADD_GOSSIP_ITEM(0, "Control Orc Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(10440, _Creature->GetGUID());
                break;
            case NPC_QUEEN_A:
                player->ADD_GOSSIP_ITEM(0, "Control Human Conjurer", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(10417, _Creature->GetGUID());
                break;
            case NPC_BISHOP_H:
                player->ADD_GOSSIP_ITEM(0, "Control Orc Necrolyte", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(10434, _Creature->GetGUID());
                break;
            case NPC_BISHOP_A:
                player->ADD_GOSSIP_ITEM(0, "Control Human Cleric", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(10416, _Creature->GetGUID());
                break;
            case NPC_ROOK_H:
                player->ADD_GOSSIP_ITEM(0, "Control Summoned Daemon", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(10426, _Creature->GetGUID());
                break;
            case NPC_ROOK_A:
                player->ADD_GOSSIP_ITEM(0, "Control Conjured Water Elemental", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(10413, _Creature->GetGUID());
                break;
            case NPC_KING_H:
                player->ADD_GOSSIP_ITEM(0, "Control Warchief Blackhand", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(10442, _Creature->GetGUID());
                break;
            case NPC_KING_A:
                player->ADD_GOSSIP_ITEM(0, "Control King Llane", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(10418, _Creature->GetGUID());
                break;
            }
        }

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* _Creature, uint32 sender, uint32 action) override 
    {
        InstanceScript* pInstance = _Creature->GetInstanceScript();
        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            if (_Creature->GetEntry() == NPC_KING_A || _Creature->GetEntry() == NPC_KING_H)
                ((boss_MedivhAI*)(pInstance->GetCreature(DATA_ECHO_OF_MEDIVH)->AI()))->StartEvent();

            player->TeleportTo(_Creature->GetMapId(), -11108.2f, -1841.56f, 229.625f, 5.39745f);
            player->CastSpell(_Creature, SPELL_POSSES_CHESSPIECE, true);
        }

        player->CLOSE_GOSSIP_MENU();

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override 
    {
        return new npc_chesspieceAI(creature);
    }
};

npc_chesspieceAI::npc_chesspieceAI(Creature *c) : ScriptedAI(c)
{
    pInstance = me->GetInstanceScript();

    me->setActive(true);
    me->SetCanMissSpells(false);
}

void npc_chesspieceAI::EnterEvadeMode() { }

void npc_chesspieceAI::SetSpellsAndCooldowns()
{
    switch(me->GetEntry())
    {
        case NPC_KING_A:
            ability1ID = SPELL_KING_A_1;
            ability1Timer = CD_KING_1;
            ability1Cooldown = CD_KING_1;

            ability2ID = SPELL_KING_A_2;
            ability2Timer = CD_KING_2;
            ability2Cooldown = CD_KING_2;

            moveID = SPELL_MOVE_5;
            break;

        case NPC_KING_H:
            ability1ID = SPELL_KING_H_1 ;
            ability1Timer = CD_KING_1;
            ability1Cooldown = CD_KING_1;

            ability2ID = SPELL_KING_H_2;
            ability2Timer = CD_KING_2;
            ability2Cooldown = CD_KING_2;

            moveID = SPELL_MOVE_5;
            break;

        case NPC_QUEEN_A:
            ability1ID = SPELL_QUEEN_A_1 ;
            ability1Timer = CD_QUEEN_1;
            ability1Cooldown = CD_QUEEN_1;

            ability2ID = SPELL_QUEEN_A_2;
            ability2Timer = CD_QUEEN_2;
            ability2Cooldown = CD_QUEEN_2;

            moveID = SPELL_MOVE_4;
            break;

        case NPC_QUEEN_H:
            ability1ID = SPELL_QUEEN_H_1 ;
            ability1Timer = CD_QUEEN_1;
            ability1Cooldown = CD_QUEEN_1;

            ability2ID = SPELL_QUEEN_H_2;
            ability2Timer = CD_QUEEN_2;
            ability2Cooldown = CD_QUEEN_2;

            moveID = SPELL_MOVE_4;
            break;

        case NPC_BISHOP_A:
            ability1ID = SPELL_BISHOP_A_1 ;
            ability1Timer = CD_BISHOP_1;
            ability1Cooldown = CD_BISHOP_1;

            ability2ID = SPELL_BISHOP_A_2;
            ability2Timer = CD_BISHOP_2;
            ability2Cooldown = CD_BISHOP_2;

            moveID = SPELL_MOVE_6;
            break;

        case NPC_BISHOP_H:
            ability1ID = SPELL_BISHOP_H_1 ;
            ability1Timer = CD_BISHOP_1;
            ability1Cooldown = CD_BISHOP_1;

            ability2ID = SPELL_BISHOP_H_2;
            ability2Timer = CD_BISHOP_2;
            ability2Cooldown = CD_BISHOP_2;

            moveID = SPELL_MOVE_6;
            break;

        case NPC_KNIGHT_A:
            ability1ID = SPELL_KNIGHT_A_1 ;
            ability1Timer = CD_KNIGHT_1;
            ability1Cooldown = CD_KNIGHT_1;

            ability2ID = SPELL_KNIGHT_A_2;
            ability2Timer = CD_KNIGHT_2;
            ability2Cooldown = CD_KNIGHT_2;

            moveID = SPELL_MOVE_3;
            break;

        case NPC_KNIGHT_H:
            ability1ID = SPELL_KNIGHT_H_1 ;
            ability1Timer = CD_KNIGHT_1;
            ability1Cooldown = CD_KNIGHT_1;

            ability2ID = SPELL_KNIGHT_H_2;
            ability2Timer = CD_KNIGHT_2;
            ability2Cooldown = CD_KNIGHT_2;

            moveID = SPELL_MOVE_3;
            break;

        case NPC_ROOK_A:
            ability1ID = SPELL_ROOK_A_1 ;
            ability1Timer = CD_ROOK_1;
            ability1Cooldown = CD_ROOK_1;

            ability2ID = SPELL_ROOK_A_2;
            ability2Timer = CD_ROOK_2;
            ability2Cooldown = CD_ROOK_2;

            moveID = SPELL_MOVE_7;
            break;

        case NPC_ROOK_H:
            ability1ID = SPELL_ROOK_H_1 ;
            ability1Timer = CD_ROOK_1;
            ability1Cooldown = CD_ROOK_1;

            ability2ID = SPELL_ROOK_H_2;
            ability2Timer = CD_ROOK_2;
            ability2Cooldown = CD_ROOK_2;

            moveID = SPELL_MOVE_7;
            break;

        case NPC_PAWN_A:
            ability1ID = SPELL_PAWN_A_1 ;
            ability1Timer = CD_PAWN_1;
            ability1Cooldown = CD_PAWN_1;

            ability2ID = SPELL_PAWN_H_2;
            ability2Timer = CD_PAWN_2;
            ability2Cooldown = CD_PAWN_2;

            moveID = SPELL_MOVE_1;
            break;

        case NPC_PAWN_H:
            ability1ID = SPELL_PAWN_H_1 ;
            ability1Timer = CD_PAWN_1;
            ability1Cooldown = CD_PAWN_1;

            ability2ID = SPELL_PAWN_H_2;
            ability2Timer = CD_PAWN_2;
            ability2Cooldown = CD_PAWN_2;

            moveID = SPELL_MOVE_1;
            break;
        default:
            break;
    }

    attackTimer = attackCooldown;
}

bool npc_chesspieceAI::IsOnSelfSpell(uint32 spell)
{
    switch (spell)
    {
        case SPELL_KING_H_2:
        case SPELL_KING_A_2:
        case SPELL_ROOK_H_2:
        case SPELL_ROOK_A_2:
        case SPELL_PAWN_H_2:
        case SPELL_PAWN_A_2:
            return true;

        default:
            return false;
    }

    return false;
}

bool npc_chesspieceAI::IsHealingSpell(uint32 spell)
{
    switch (spell)
    {
        case SPELL_BISHOP_A_1:
        case SPELL_BISHOP_H_1:
            return true;

        default:
            return false;
    }

    return false;
}

bool npc_chesspieceAI::IsNullTargetSpell(uint32 spell)
{
    switch (spell)
    {
        case SPELL_KING_H_1:
        case SPELL_KING_A_1:
        case SPELL_KNIGHT_H_1:
        case SPELL_KNIGHT_A_1:
        case SPELL_ROOK_H_1:
        case SPELL_ROOK_A_1:
        case SPELL_PAWN_H_1:
        case SPELL_PAWN_A_1:
        case SPELL_KING_H_2:
        case SPELL_KING_A_2:
        case SPELL_BISHOP_H_2:
        case SPELL_BISHOP_A_2:
        case SPELL_KNIGHT_H_2:
        case SPELL_KNIGHT_A_2:
        case SPELL_ROOK_H_2:
        case SPELL_ROOK_A_2:
            return true;

        default:
            return false;
    }

    return false;
}

void npc_chesspieceAI::Reset()
{
    me->LoadEquipment(1);
    ReturnToHome = true;
    InGame = true;
    CanMove = false;
    me->setActive(true);

    SetSpellsAndCooldowns();

    ability1Chance = urand(ABILITY_1_CHANCE_MIN, ABILITY_1_CHANCE_MAX);
    ability2Chance = urand(ABILITY_2_CHANCE_MIN, ABILITY_2_CHANCE_MAX);

    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

    nextTryTimer = urand(500, 5000);

    changeFacingTimer = urand (3000, 7500);
    SetHealth();
    moving = false;
}

void npc_chesspieceAI::MovementInform(uint32 type, uint32 data)
{
    if (type != POINT_MOTION_TYPE)
        return;

    if (moving && me->GetExactDist(&currentPos) > 0.5f) // movement was interrupted (probably player left chess piece), start again
    {
        _scheduler.Schedule(1ms, [&](TaskContext func)
        {
            me->GetMotionMaster()->MovePoint(1, currentPos);
        });
    }
    else
    {
        if (Creature* npc_medivh = pInstance->GetCreature(DATA_ECHO_OF_MEDIVH))
            ((boss_MedivhAI*)npc_medivh->AI())->SetOrientation(me->GetGUID());
    }
    moving = false;
}

void npc_chesspieceAI::OnCharmed(bool apply)
{
    if (apply)
        me->SetControlled(true, UNIT_STATE_ROOT);

    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);

    me->SetWalk(true);

    // set proper faction after charm
    if (pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_ALLIANCE)
        me->setFaction(A_FACTION);
    else
        me->setFaction(H_FACTION);  

    if (!apply && !me->isMoving())
        if (Creature* medivh = pInstance->GetCreature(DATA_ECHO_OF_MEDIVH))
            ((boss_MedivhAI*)medivh->AI())->SetOrientation(me->GetGUID());
}

void npc_chesspieceAI::SpellHit(Unit * caster, const SpellInfo * spell)
{
    if (spell->Id == SPELL_MOVE_MARKER)
        ((Creature*)me)->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
}

void npc_chesspieceAI::SpellHitTarget(Unit * caster, const SpellInfo* spell)
{
    if (spell->Id == moveID)
        ((Creature*)me)->HandleEmoteCommand(EMOTE_ONESHOT_BOW);
}

void npc_chesspieceAI::DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*damageSchoolMask*/)
{
    if (!attacker)
        return;
    if (Player* tmpPl = attacker->GetCharmerOrOwnerPlayerOrPlayerItself())
        if (attacker->GetTypeId() == TYPEID_UNIT && tmpPl->GetTeamId() == pInstance->GetData(DATA_CHESS_EVENT_TEAM))
            pInstance->SetData(DATA_CHESS_DAMAGE, pInstance->GetData(DATA_CHESS_DAMAGE) + damage);

    if (Player * tmpPl = me->GetCharmerOrOwnerPlayerOrPlayerItself())
        if (damage >= me->GetHealth())
            tmpPl->RemoveAurasDueToSpell(SPELL_POSSES_CHESSPIECE);
    me->SetPassive();
    InGame = false;
}

void npc_chesspieceAI::UpdateAI(const uint32 diff)
{
    if (pInstance->GetData(DATA_CHESS_EVENT) == DONE || pInstance->GetData(DATA_CHESS_EVENT) == FAIL)
    {
        if (me->IsInCombat())
            me->CombatStop();

        if (me->isPossessed())
            me->RemoveCharmedBy(me->GetCharmer());
    }

    if (pInstance->GetData(DATA_CHESS_EVENT) != IN_PROGRESS)
        return;

    if (!InGame)
        return;

    if ((me->getFaction() == A_FACTION && pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_HORDE) ||
       (me->getFaction() == H_FACTION && pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_ALLIANCE))
    {
#ifndef CHESS_EVENT_DISSABLE_MEDIVH_PIECES_SPELLS
        uint64 ab1 = 0;
        bool ab1Self = false;
        uint64 ab2 = 0;
        bool ab2Self = false;

        if (ability1Timer <= diff)
        {
            Creature * medivh = pInstance->GetCreature(DATA_ECHO_OF_MEDIVH);
            if (medivh && urand(0, ABILITY_CHANCE_MAX) < ability1Chance)
            {
                if (IsOnSelfSpell(ability1ID))
                {
                    ab1 = me->GetGUID();
                    ab1Self = true;
                }
                else
                    ab1 = ((boss_MedivhAI*)medivh->AI())->GetSpellTarget(me->GetGUID(), ability1ID);
            }
            else
                ability1Timer = urand(500, 5000);
        }
        else
            ability1Timer -= diff;

        if (ability2Timer <= diff)
        {
            Creature * medivh = pInstance->GetCreature(DATA_ECHO_OF_MEDIVH);
            if (medivh && urand(0, ABILITY_CHANCE_MAX) < ability2Chance)
            {
                if (IsOnSelfSpell(ability2ID))
                {
                    ab2 = me->GetGUID();
                    ab2Self = true;
                }
                else
                    ab2 = ((boss_MedivhAI*)medivh->AI())->GetSpellTarget(me->GetGUID(), ability2ID);
            }
            else
                ability2Timer = urand(500, 5000);
        }
        else
            ability2Timer -= diff;


        if (ab1 && ab2)
        {
            if (urand(0, ABILITY_CHANCE_MAX) < (IsHealingSpell(ability1ID) ? (uint32)HEALING_ABILITY_CHANCE : (uint32)NORMAL_ABILITY_CHANCE))
                ab2 = 0;
            else
                ab1 = 0;
        }

        if (ab1)
        {
            _scheduler.Schedule(100ms, [&](TaskContext /*func*/)
            {
                if (IsNullTargetSpell(ability1ID))
                    DoCastAOE(ability1ID);
                else
                {
                    if (Creature * victim = ObjectAccessor::GetCreature(*me, ab1))
                        me->CastSpell(victim, ability1ID);
                }
            });

            ability1Timer = ability1Cooldown;
            ability2Timer = SHARED_COOLDOWN;
        }
        else if (ab2)
        {
            _scheduler.Schedule(100ms, [&](TaskContext /*func*/)
            {
                if (IsNullTargetSpell(ability2ID))
                    DoCastAOE(ability2ID);
                else
                {
                    if (Creature * victim = ObjectAccessor::GetCreature(*me, ab2))
                        me->CastSpell(victim, ability2ID);
                }
            });

            ability2Timer = ability1Cooldown;
            ability1Timer = SHARED_COOLDOWN;
        }
#endif

#ifndef CHESS_EVENT_DISSABLE_FACING
        if (changeFacingTimer <= diff)
        {
            changeFacingTimer = urand(3000, 7500);

            Creature * medivh = pInstance->GetCreature(DATA_ECHO_OF_MEDIVH);

            if (!medivh)
                return;

            ((boss_MedivhAI*)medivh->AI())->CheckChangeFacing(me->GetGUID());
        }
        else
            changeFacingTimer -= diff;
#endif
    }

    if (!me->IsCasting())
        _scheduler.Update(diff);

#ifndef CHESS_EVENT_DISSABLE_MELEE
    if (attackTimer <= diff)
    {
        attackTimer = attackCooldown;
        Creature * medivh = pInstance->GetCreature(DATA_ECHO_OF_MEDIVH);

        if (!medivh)
            return;

        if (Unit * uVictim = pInstance->instance->GetCreature(((boss_MedivhAI*)medivh->AI())->GetMeleeTarget(me->GetGUID())))
            me->CastSpell(uVictim, SPELL_MELEE_DAMAGE, true);
    }
    else
        attackTimer -= diff;
#endif
}

void npc_chesspieceAI::JustDied(Unit * killer)
{
    me->RemoveAurasDueToSpell(SPELL_POSSES_CHESSPIECE);

    if (pInstance->GetData(DATA_CHESS_EVENT) == IN_PROGRESS)
        if (Creature* npc_medivh = pInstance->GetCreature(DATA_ECHO_OF_MEDIVH))
            ((boss_MedivhAI*)npc_medivh->AI())->RemoveChessPieceFromBoard(me);
}

void npc_chesspieceAI::AttackStart(Unit* pWho)
{
    if (!pWho)
        return;

    if (me->Attack(pWho, true))
        DoStartNoMovement(pWho);
}

void npc_chesspieceAI::SetCurrentPosition(Position pos)
{
    moving = true;
    currentPos = pos;
}

void npc_chesspieceAI::SetData(uint32 type, uint32)
{
    InGame = false;
}

void npc_chesspieceAI::SetHealth()
{
    uint32 health = 50000;
    switch (me->GetEntry())
    {
        case NPC_PAWN_A:
        case NPC_PAWN_H:
            health = 50000;
            break;
        case NPC_KNIGHT_A:
        case NPC_KNIGHT_H:
            health = 65000;
            break;
        case NPC_BISHOP_A:
        case NPC_BISHOP_H:
            health = 60000;
            break;
        case NPC_ROOK_A:
        case NPC_ROOK_H:
            health = 80000;
            break;
        case NPC_QUEEN_A:
        case NPC_QUEEN_H:
            health = 80000;
            break;
        case NPC_KING_A:
        case NPC_KING_H:
            health = 150000;
            break;
    }

    me->SetMaxHealth(health);
    me->SetFullHealth();
}
//Medivh AI

class npc_echo_of_medivh : CreatureScript
{
public:
    npc_echo_of_medivh() : CreatureScript("npc_echo_of_medivh") { }

    bool OnGossipHello(Player* player, Creature* _Creature) override
    { 
        if (((boss_MedivhAI*)_Creature->AI())->IsEventStarted())
        {
            player->SEND_GOSSIP_MENU(10506, _Creature->GetGUID());
            return true;
        }

        player->ADD_GOSSIP_ITEM(0, EVENT_START, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->SEND_GOSSIP_MENU(10506, _Creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* _Creature, uint32 sender, uint32 action) 
    { 
        InstanceScript* pInstance = _Creature->GetInstanceScript();

        if (action == GOSSIP_ACTION_INFO_DEF)
        {
            _Creature->AI()->Talk(SCRIPTTEXT_AT_EVENT_START);

            ((boss_MedivhAI*)_Creature->AI())->StartMiniEvent();

            pInstance->SetData(DATA_CHESS_EVENT_TEAM, player->GetTeamId());
            _Creature->GetMotionMaster()->MoveRandom(5.f);
        }

        player->CLOSE_GOSSIP_MENU();

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override
    { 
        return new boss_MedivhAI(creature);
    }
};

boss_MedivhAI::boss_MedivhAI(Creature *c) : ScriptedAI(c)
{
    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

    pInstance = me->GetInstanceScript();
    pos.Relocate(me->GetPosition());
    tpPos.Relocate(-11108.2f, -1841.56f, 229.625f, 5.39745f);

    this->chanceToMove = urand(MIN_MOVE_CHANCE, MAX_MOVE_CHANCE);

    chanceToSelfMove = urand(MIN_SELF_MOVE_CHANCE, MAX_SELF_MOVE_CHANCE);

    /*
                   j

          0  1  2  3  4  5  6  7
        0 H  H  H  H  H  H  H  H
        1 H  H  H  H  H  H  H  H
        2 E  E  E  E  E  E  E  E
    i   3 E  E  E  E  E  E  E  E
        4 E  E  E  E  E  E  E  E
        5 E  E  E  E  E  E  E  E
        6 A  A  A  A  A  A  A  A
        7 A  A  A  A  A  A  A  A
    */

    // calc positions:

    for (uint8 i = 0; i < 8; ++i)
    {
        for (uint8 j = 0; j < 8; ++j)
            chessBoard[i][j].position.Relocate(-11077.66f + 3.48f * j - 4.32f * i, -1849.02f - 4.365f * j - 3.41f * i, 221.1f);
    }
    int j = 15;
    for (int i = 0; i < 16; ++i)
    {
        allianceSideDeadWP[0][i] = (i < 8 ? ALLIANCE_DEAD_X2 : ALLIANCE_DEAD_X1) - 2.2 * 0.75 * (j < 8 ? j : j - 8);
        allianceSideDeadWP[1][i] = (i < 8 ? ALLIANCE_DEAD_Y2 : ALLIANCE_DEAD_Y1) - 1.7 * 0.75 * (j < 8 ? j : j - 8);
        hordeSideDeadWP[0][i] = (i < 8 ? HORDE_DEAD_X2 : HORDE_DEAD_X1) + 2.2 * 0.75 * (j < 8 ? j : j - 8);
        hordeSideDeadWP[1][i] = (i < 8 ? HORDE_DEAD_Y2 : HORDE_DEAD_Y1) + 1.7 * 0.75 * (j < 8 ? j : j - 8);
        j--;
    }
}

int boss_MedivhAI::GetMoveRange(uint64 const& piece)
{
    return (GetMoveRange(pInstance->instance->GetCreature(piece)));
}

int boss_MedivhAI::GetMoveRange(Unit * piece)
{
    if (!piece)
        return 0;

    switch (piece->GetEntry())
    {
        case NPC_PAWN_A:
        case NPC_PAWN_H:
        case NPC_KING_A:
        case NPC_KING_H:
        case NPC_BISHOP_A:
        case NPC_BISHOP_H:
        case NPC_ROOK_A:
        case NPC_ROOK_H:
            return 8;

        case NPC_KNIGHT_A:
        case NPC_KNIGHT_H:
            return 15;

        case NPC_QUEEN_A:
        case NPC_QUEEN_H:
            return 20;

        default:
            break;
    }

    return 0;
}

bool boss_MedivhAI::Enemy(uint64 const& piece1, uint64 const& piece2)
{
    Creature * tmp1, * tmp2;

    if (!piece1 || !piece2)
        return false;

    tmp1 = ObjectAccessor::GetCreature(*me, piece1);
    tmp2 = ObjectAccessor::GetCreature(*me, piece2);

    if (!tmp1 || !tmp2)
        return false;

    return tmp1->getFaction() != tmp2->getFaction();
}

int boss_MedivhAI::GetCountOfEnemyInMelee(uint64 const& piece, bool strafe)
{
    int tmpCount = 0, tmpI = -1, tmpJ = -1, tmpOffsetI, tmpOffsetJ;

    //search for position in tab of piece

    if (!FindPlaceInBoard(piece, tmpI, tmpJ))
        return 0;

    if (strafe)
    {
        for (int i = 0; i < OFFSET8COUNT; ++i)
        {
            tmpOffsetI = tmpI + offsetTab8[i][0];
            tmpOffsetJ = tmpJ + offsetTab8[i][1];
            if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                tmpOffsetJ >= 0 && tmpOffsetJ < 8 &&
                Enemy(piece, chessBoard[tmpOffsetI][tmpOffsetJ].piece))
                ++tmpCount;
        }
    }
    else
    {
        for (int i = 0; i < OFFSETMELEECOUNT; ++i)
        {
            tmpOffsetI = tmpI + offsetTabMelee[i][0];
            tmpOffsetJ = tmpJ + offsetTabMelee[i][1];
            if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                tmpOffsetJ >= 0 && tmpOffsetJ < 8 &&
                Enemy(piece, chessBoard[tmpOffsetI][tmpOffsetJ].piece))
                ++tmpCount;
        }
    }

    return tmpCount;
}

int boss_MedivhAI::GetCountOfPiecesInRange(uint64 const& trigger, int range, bool friendly)
{
    int count = 0;

    int tmpI, tmpJ, i, tmpOffsetI, tmpOffsetJ;
    uint64 tmpGUID;

    if (!FindPlaceInBoard(trigger, tmpI, tmpJ))
        return 0;

    switch (range)
    {
        case 25:
            for (i = 0; i < OFFSET25COUNT; i++)
            {
                tmpOffsetI = tmpI + offsetTab25[i][0];
                tmpOffsetJ = tmpJ + offsetTab25[i][1];

                if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                    tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                {
                    tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                    if (friendly)
                    {
                        if (tmpGUID && IsMedivhsPiece(tmpGUID))
                            ++count;
                    }
                    else
                    {
                        if (tmpGUID && !IsMedivhsPiece(tmpGUID))
                            ++count;
                    }
                }
            }
        case 20:
            for (i = 0; i < OFFSET20COUNT; i++)
            {
                tmpOffsetI = tmpI + offsetTab20[i][0];
                tmpOffsetJ = tmpJ + offsetTab20[i][1];

                if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                    tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                {
                    tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                    if (friendly)
                    {
                        if (tmpGUID && IsMedivhsPiece(tmpGUID))
                            ++count;
                    }
                    else
                    {
                        if (tmpGUID && !IsMedivhsPiece(tmpGUID))
                            ++count;
                    }
                }
            }
        case 15:
            for (i = 0; i < OFFSET15COUNT; i++)
            {
                tmpOffsetI = tmpI + offsetTab15[i][0];
                tmpOffsetJ = tmpJ + offsetTab15[i][1];

                if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                    tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                {
                    tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                    if (friendly)
                    {
                        if (tmpGUID && IsMedivhsPiece(tmpGUID))
                            ++count;
                    }
                    else
                    {
                        if (tmpGUID && !IsMedivhsPiece(tmpGUID))
                            ++count;
                    }
                }
            }
        case 8:
        default:
            for (i = 0; i < OFFSET8COUNT; i++)
            {
                tmpOffsetI = tmpI + offsetTab8[i][0];
                tmpOffsetJ = tmpJ + offsetTab8[i][1];

                if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                    tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                {
                    tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                    if (friendly)
                    {
                        if (tmpGUID && IsMedivhsPiece(tmpGUID))
                            ++count;
                    }
                    else
                    {
                        if (tmpGUID && !IsMedivhsPiece(tmpGUID))
                            ++count;
                    }
                }
            break;
            }
    }

    return count;
}

int boss_MedivhAI::GetLifePriority(uint64 const& piece)
{
    Unit * uPiece = pInstance->instance->GetCreature(piece);

    if (!uPiece)
        return 0;

    int tmpPriority = 0;

    switch (uPiece->GetEntry())
    {
        case NPC_PAWN_A:
        case NPC_PAWN_H:
            tmpPriority += 10;
            break;
        case NPC_KING_A:
        case NPC_KING_H:
            tmpPriority += 50;
            break;
        case NPC_BISHOP_A:
        case NPC_BISHOP_H:
            tmpPriority += 50;
            break;
        case NPC_ROOK_A:
        case NPC_ROOK_H:
            tmpPriority += 20;
            break;
        case NPC_KNIGHT_A:
        case NPC_KNIGHT_H:
            tmpPriority += 30;
            break;
        case NPC_QUEEN_A:
        case NPC_QUEEN_H:
            tmpPriority += 40;
            break;
        default:
            break;
    }

    tmpPriority += tmpPriority * (1- (uPiece->GetHealth()/uPiece->GetMaxHealth()));

    return tmpPriority;
}

int boss_MedivhAI::GetAttackPriority(uint64 const& piece)
{
    Unit * uPiece = pInstance->instance->GetCreature(piece);

    if (!uPiece)
        return 0;

    int tmpPriority = START_PRIORITY;

    switch (uPiece->GetEntry())
    {
        case NPC_PAWN_A:
        case NPC_PAWN_H:
            tmpPriority += 5;
            break;
        case NPC_KING_A:
        case NPC_KING_H:
            tmpPriority += 15;
            break;
        case NPC_BISHOP_A:
        case NPC_BISHOP_H:
            tmpPriority += 15;
            break;
        case NPC_ROOK_A:
        case NPC_ROOK_H:
            tmpPriority += 5;
            break;
        case NPC_KNIGHT_A:
        case NPC_KNIGHT_H:
            tmpPriority += 5;
            break;
        case NPC_QUEEN_A:
        case NPC_QUEEN_H:
            tmpPriority += 10;
            break;
        default:
            break;
    }

    tmpPriority += tmpPriority * (1 - (uPiece->GetHealth()/(double)uPiece->GetMaxHealth()));

    return tmpPriority;
}

bool boss_MedivhAI::IsEmptySquareInRange(uint64 const& piece, int range)
{
    if (!piece || !range)
        return false;

    int tmpI = -1, tmpJ = -1, tmpOffsetI, tmpOffsetJ;
    int i;

    //search for position in tab of piece

    if (!FindPlaceInBoard(piece, tmpI, tmpJ))
        return false;

    switch (range)
    {
        case 25:
            for (i = 0; i < OFFSET25COUNT; i++)
            {
                tmpOffsetI = tmpI + offsetTab25[i][0];
                tmpOffsetJ = tmpJ + offsetTab25[i][1];

                if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                    tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    if (!chessBoard[tmpOffsetI][tmpOffsetJ].piece)
                        return true;
            }
        case 20:
            for (i = 0; i < OFFSET20COUNT; i++)
            {
                tmpOffsetI = tmpI + offsetTab20[i][0];
                tmpOffsetJ = tmpJ + offsetTab20[i][1];
                if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                    tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    if (!chessBoard[tmpOffsetI][tmpOffsetJ].piece)
                        return true;
            }
        case 15:
            for (i = 0; i < OFFSET15COUNT; i++)
            {
                tmpOffsetI = tmpI + offsetTab15[i][0];
                tmpOffsetJ = tmpJ + offsetTab15[i][1];

                if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                    tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    if (!chessBoard[tmpOffsetI][tmpOffsetJ].piece)
                        return true;
            }
        case 8:
            for (i = 0; i < OFFSET8COUNT; i++)
            {
                tmpOffsetI = tmpI + offsetTab8[i][0];
                tmpOffsetJ = tmpJ + offsetTab8[i][1];

                if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                    tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    if (!chessBoard[tmpOffsetI][tmpOffsetJ].piece)
                        return true;
            }
            break;
        default:
            break;
    }

    return false;
}

bool boss_MedivhAI::IsPositive(uint32 spell)
{
    switch (spell)
    {
        case SPELL_PAWN_A_2:
        case SPELL_PAWN_H_2:
        case SPELL_ROOK_A_2:
        case SPELL_ROOK_H_2:
        case SPELL_KING_A_2:
        case SPELL_KING_H_2:
        case SPELL_BISHOP_A_1:
        case SPELL_BISHOP_H_1:
            return true;

        default:
            return false;
    }

    return false;
}

int boss_MedivhAI::GetAbilityRange(uint32 spell)
{
    /*returns:
    0   - spell needs check if there are any target in melee range, if yes then casts spell on self
    5   - spell needs target in front of caster
    6   - spell needs target in 1 -> 3 targets in front (clave/swipe)
    20  - long range (7x7 - 5 squares) - normal check
    25  - long range (7x7 - 1 squares) - normal check

    0                   - caster;
    1 + 2 + 3           - return 0
    2                   - return 5
    3 + 2               - return 6
    4 + 1 + 2 + 3       - return 20
    5 + 4 + 1 + 2 + 3   - return 25

     5 4 4 4 4 4 5
     4 4 4 4 4 4 4
     4 4 3 2 3 4 4
     4 4 1 0 1 4 4
     4 4 1 1 1 4 4
     4 4 4 4 4 4 4
     5 4 4 4 4 4 5

    ranges for spells can be wrong !
    */

    switch (spell)
    {
        case SPELL_KING_H_1:
        case SPELL_KING_A_1:
            return 6;

        case SPELL_QUEEN_H_1:
        case SPELL_QUEEN_A_1:
        case SPELL_QUEEN_A_2:
        case SPELL_QUEEN_H_2:
            return 25;

        case SPELL_BISHOP_A_1:
        case SPELL_BISHOP_H_1:
            return 20;

        case SPELL_PAWN_H_1:
        case SPELL_PAWN_A_1:
        case SPELL_KNIGHT_H_1:
        case SPELL_KNIGHT_A_1:
            return 5;

        default:
            return 0;
    }

    return 0;
}

bool boss_MedivhAI::IsHealingSpell(uint32 spell)
{
    switch (spell)
    {
        case SPELL_BISHOP_A_1:
        case SPELL_BISHOP_H_1:
            return true;

        default:
            return false;
    }

    return false;
}

bool boss_MedivhAI::Heal(uint32 spell, uint64 const& guid)
{
    if (!IsHealingSpell(spell))
        return true;

    Creature * tmpC = ObjectAccessor::GetCreature(*me, guid);

    if (!tmpC)
        return false;

    return tmpC->GetHealth() != tmpC->GetMaxHealth();
}

uint64 const& boss_MedivhAI::GetSpellTarget(uint64 const& caster, uint32 spell)
{
    int tmpI = -1, tmpJ = -1, i, tmpOffsetI, tmpOffsetJ;

    if (!FindPlaceInBoard(caster, tmpI, tmpJ))
        return 0;

    std::list<Priority> tmpList;
    GuidList tmpPossibleTargetsList;
    uint64 tmpGUID;

    if (IsPositive(spell))
    {
        //create possible target list

        switch (GetAbilityRange(spell))
        {
            case 25:
                for (i = 0; i < OFFSET25COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab25[i][0];
                    tmpOffsetJ = tmpJ + offsetTab25[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    {
                        tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                        if (tmpGUID && IsMedivhsPiece(tmpGUID) && Heal(spell, tmpGUID))
                            tmpPossibleTargetsList.push_back(tmpGUID);
                    }
                }
            case 20:
                for (i = 0; i < OFFSET20COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab20[i][0];
                    tmpOffsetJ = tmpJ + offsetTab20[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    {
                        tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                        if (tmpGUID && IsMedivhsPiece(tmpGUID) && Heal(spell, tmpGUID))
                            tmpPossibleTargetsList.push_back(tmpGUID);
                    }
                }
            case 15:
                for (i = 0; i < OFFSET15COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab15[i][0];
                    tmpOffsetJ = tmpJ + offsetTab15[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    {
                        tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                        if (tmpGUID && IsMedivhsPiece(tmpGUID) && Heal(spell, tmpGUID))
                            tmpPossibleTargetsList.push_back(tmpGUID);
                    }
                }
            case 8:
                for (i = 0; i < OFFSET8COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab8[i][0];
                    tmpOffsetJ = tmpJ + offsetTab8[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    {
                        tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                        if (tmpGUID && IsMedivhsPiece(tmpGUID) && Heal(spell, tmpGUID))
                            tmpPossibleTargetsList.push_back(tmpGUID);
                    }
                }
                break;
            case 6: // 3 targets in front
                switch (chessBoard[tmpI][tmpJ].ori)
                {
                    case CHESS_ORI_E:
                        if (tmpJ + 1 >= 0)
                        {
                            if (!Enemy(caster, chessBoard[tmpI][tmpJ + 1].piece))
                                return caster;

                            if (tmpI - 1 >= 0 && !Enemy(caster, chessBoard[tmpI - 1][tmpJ + 1].piece))
                                return caster;

                            if (tmpI + 1 < 8 && !Enemy(caster, chessBoard[tmpI + 1][tmpJ + 1].piece))
                                return caster;
                        }
                        break;
                    case CHESS_ORI_N:
                        if (tmpI - 1 >= 0)
                        {
                            if (!Enemy(caster, chessBoard[tmpI - 1][tmpJ].piece))
                                return caster;

                            if (tmpJ - 1 >= 0 && !Enemy(caster, chessBoard[tmpI - 1][tmpJ - 1].piece))
                                return caster;

                            if (tmpJ + 1 < 8 && !Enemy(caster, chessBoard[tmpI - 1][tmpJ + 1].piece))
                                return caster;
                        }
                        break;
                    case CHESS_ORI_S:
                        if (tmpI + 1 >= 0)
                        {
                            if (!Enemy(caster, chessBoard[tmpI + 1][tmpJ].piece))
                                return caster;

                            if (tmpJ - 1 >= 0 && !Enemy(caster, chessBoard[tmpI + 1][tmpJ - 1].piece))
                                return caster;

                            if (tmpJ + 1 < 8 && !Enemy(caster, chessBoard[tmpI + 1][tmpJ + 1].piece))
                                return caster;
                        }
                        break;
                    case CHESS_ORI_W:
                        if (tmpJ - 1 >= 0)
                        {
                            if (!Enemy(caster, chessBoard[tmpI][tmpJ - 1].piece))
                                return caster;

                            if (tmpI - 1 >= 0 && !Enemy(caster, chessBoard[tmpI - 1][tmpJ - 1].piece))
                                return caster;

                            if (tmpI + 1 < 8 && !Enemy(caster, chessBoard[tmpI + 1][tmpJ - 1].piece))
                                return caster;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case 5: // 1 target in front
                switch (chessBoard[tmpI][tmpJ].ori)
                {
                    case CHESS_ORI_E:
                        if (tmpJ + 1 >= 0)
                            if (!Enemy(caster, chessBoard[tmpI][tmpJ + 1].piece))
                                return chessBoard[tmpI][tmpJ + 1].piece;
                        break;
                    case CHESS_ORI_N:
                        if (tmpI - 1 >= 0)
                            if (!Enemy(caster, chessBoard[tmpI - 1][tmpJ].piece))
                                return chessBoard[tmpI - 1][tmpJ].piece;
                        break;
                    case CHESS_ORI_S:
                        if (tmpI + 1 >= 0)
                            if (!Enemy(caster, chessBoard[tmpI + 1][tmpJ].piece))
                                return chessBoard[tmpI + 1][tmpJ].piece;
                        break;
                    case CHESS_ORI_W:
                        if (tmpJ - 1 >= 0)
                            if (!Enemy(caster, chessBoard[tmpI][tmpJ - 1].piece))
                                return chessBoard[tmpI][tmpJ - 1].piece;
                        break;
                    default:
                        break;
                }
                break;
            case 0: // check if is any piece in melee
                for (i = 0; i < OFFSET8COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab8[i][0];
                    tmpOffsetJ = tmpJ + offsetTab8[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    {
                        tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                        if (tmpGUID && IsMedivhsPiece(tmpGUID))
                            return caster;
                    }
                }
                break;
            default:
                break;
        }

        if (tmpPossibleTargetsList.empty())
            return 0;

        // calculate and add priority

        int prioritySum = 0;

        for (uint64 const& guid : tmpPossibleTargetsList)
        {
            Priority tempPriority;
            tempPriority.prior = START_PRIORITY;
            tempPriority.GUIDfrom = guid;

            tempPriority.prior += GetCountOfEnemyInMelee(guid) * MELEE_PRIORITY + urand(0, RAND_PRIORITY) + GetLifePriority(guid);

            prioritySum += tempPriority.prior;
            tmpList.push_back(tempPriority);
        }

        switch (rand()%2)
        {
            case 0:
            {
                int chosen = urand(0, prioritySum), prevPrior = 0;

                for (std::list<Priority>::iterator i = tmpList.begin(); i!= tmpList.end(); ++i)
                {
                    if (prevPrior < chosen && (*i).prior >= chosen)
                        return (*i).GUIDfrom;
                    prevPrior = (*i).prior;
                }
                break;
            }
            case 1:
            default:
            {
                Priority best;
                std::list<Priority> bestList;
                best = tmpList.front();

                for (std::list<Priority>::iterator i = tmpList.begin(); i!= tmpList.end(); ++i)
                {
                    if (best.prior < (*i).prior)
                    {
                        best = *i;
                        bestList.clear();
                        bestList.push_back(*i);
                    }
                    else if (best.prior == (*i).prior)
                        bestList.push_back(*i);
                }

                if (bestList.empty())
                    return 0;

                std::list<Priority>::iterator tmpItr = bestList.begin();

                advance(tmpItr, urand(0, bestList.size() - 1));

                return (*tmpItr).GUIDfrom;

                break;
            }
        }
    }
    else        //if !positive
    {
        //create possible targets list

        switch (GetAbilityRange(spell))
        {
            case 25:
                for (i = 0; i < OFFSET25COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab25[i][0];
                    tmpOffsetJ = tmpJ + offsetTab25[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    {
                        tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                        if (tmpGUID && !IsMedivhsPiece(tmpGUID))
                            tmpPossibleTargetsList.push_back(tmpGUID);
                    }
                }
            case 20:
                for (i = 0; i < OFFSET20COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab20[i][0];
                    tmpOffsetJ = tmpJ + offsetTab20[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    {
                        tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                        if (tmpGUID && !IsMedivhsPiece(tmpGUID))
                            tmpPossibleTargetsList.push_back(tmpGUID);
                    }
                }
            case 15:
                for (i = 0; i < OFFSET15COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab15[i][0];
                    tmpOffsetJ = tmpJ + offsetTab15[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    {
                        tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                        if (tmpGUID && !IsMedivhsPiece(tmpGUID))
                            tmpPossibleTargetsList.push_back(tmpGUID);
                    }
                }
            case 8:
                for (i = 0; i < OFFSET8COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab8[i][0];
                    tmpOffsetJ = tmpJ + offsetTab8[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    {
                        tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                        if (tmpGUID && !IsMedivhsPiece(tmpGUID))
                            tmpPossibleTargetsList.push_back(tmpGUID);
                    }
                }
                break;
            case 6: // 3 targets in front
                switch (chessBoard[tmpI][tmpJ].ori)
                {
                    case CHESS_ORI_E:
                        if (tmpJ + 1 >= 0)
                        {
                            if (Enemy(caster, chessBoard[tmpI][tmpJ + 1].piece))
                                return caster;

                            if (tmpI - 1 >= 0 && Enemy(caster, chessBoard[tmpI - 1][tmpJ + 1].piece))
                                return caster;

                            if (tmpI + 1 < 8 && Enemy(caster, chessBoard[tmpI + 1][tmpJ + 1].piece))
                                return caster;
                        }
                        break;
                    case CHESS_ORI_N:
                        if (tmpI - 1 >= 0)
                        {
                            if (Enemy(caster, chessBoard[tmpI - 1][tmpJ].piece))
                                return caster;

                            if (tmpJ - 1 >= 0 && Enemy(caster, chessBoard[tmpI - 1][tmpJ - 1].piece))
                                return caster;

                            if (tmpJ + 1 < 8 && Enemy(caster, chessBoard[tmpI - 1][tmpJ + 1].piece))
                                return caster;
                        }
                        break;
                    case CHESS_ORI_S:
                        if (tmpI + 1 >= 0)
                        {
                            if (Enemy(caster, chessBoard[tmpI + 1][tmpJ].piece))
                                return caster;

                            if (tmpJ - 1 >= 0 && Enemy(caster, chessBoard[tmpI + 1][tmpJ - 1].piece))
                                return caster;

                            if (tmpJ + 1 < 8 && Enemy(caster, chessBoard[tmpI + 1][tmpJ + 1].piece))
                                return caster;
                        }
                        break;
                    case CHESS_ORI_W:
                        if (tmpJ - 1 >= 0)
                        {
                            if (Enemy(caster, chessBoard[tmpI][tmpJ - 1].piece))
                                return caster;

                            if (tmpI - 1 >= 0 && Enemy(caster, chessBoard[tmpI - 1][tmpJ - 1].piece))
                                return caster;

                            if (tmpI + 1 < 8 && Enemy(caster, chessBoard[tmpI + 1][tmpJ - 1].piece))
                                return caster;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case 5: // 1 target in front
                switch (chessBoard[tmpI][tmpJ].ori)
                {
                    case CHESS_ORI_E:
                        if (tmpJ + 1 >= 0)
                            if (Enemy(caster, chessBoard[tmpI][tmpJ + 1].piece))
                                return chessBoard[tmpI][tmpJ + 1].piece;
                        break;
                    case CHESS_ORI_N:
                        if (tmpI - 1 >= 0)
                            if (Enemy(caster, chessBoard[tmpI - 1][tmpJ].piece))
                                return chessBoard[tmpI - 1][tmpJ].piece;
                        break;
                    case CHESS_ORI_S:
                        if (tmpI + 1 >= 0)
                            if (Enemy(caster, chessBoard[tmpI + 1][tmpJ].piece))
                                return chessBoard[tmpI + 1][tmpJ].piece;
                        break;
                    case CHESS_ORI_W:
                        if (tmpJ - 1 >= 0)
                            if (Enemy(caster, chessBoard[tmpI][tmpJ - 1].piece))
                                return chessBoard[tmpI][tmpJ - 1].piece;
                        break;
                    default:
                        break;
                }
                break;
            case 0: // check if is any piece in melee
                for (i = 0; i < OFFSET8COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab8[i][0];
                    tmpOffsetJ = tmpJ + offsetTab8[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    {
                        tmpGUID = chessBoard[tmpOffsetI][tmpOffsetJ].piece;

                        if (tmpGUID && !IsMedivhsPiece(tmpGUID))
                            return caster;
                    }
                }
                break;
            default:
                break;
        }

        if (tmpPossibleTargetsList.empty())
            return 0;
        // calculate and add priority

        int prioritySum = 0;

        for (uint64 const& guid : tmpPossibleTargetsList)
        {
            Priority tempPriority;
            tempPriority.prior = START_PRIORITY;
            tempPriority.GUIDfrom = guid;

            tempPriority.prior += GetCountOfEnemyInMelee(guid) * MELEE_PRIORITY + urand(0, RAND_PRIORITY) + GetAttackPriority(guid);

            prioritySum += tempPriority.prior;
            tmpList.push_back(tempPriority);
        }

        switch (rand()%2)
        {
            case 0:
            {
                int chosen = urand(0, prioritySum), prevPrior = 0;

                for (std::list<Priority>::iterator i = tmpList.begin(); i!= tmpList.end(); ++i)
                {
                    if (prevPrior < chosen && (*i).prior >= chosen)
                        return (*i).GUIDfrom;
                    prevPrior = (*i).prior;
                }
                break;
            }
            case 1:
            default:
            {
                Priority best;
                std::list<Priority> bestList;
                best = tmpList.front();

                for (std::list<Priority>::iterator i = tmpList.begin(); i!= tmpList.end(); ++i)
                {
                    if (best.prior < (*i).prior)
                    {
                        best = *i;
                        bestList.clear();
                        bestList.push_back(*i);
                    }
                    else if (best.prior == (*i).prior)
                        bestList.push_back(*i);
                }

                if (bestList.empty())
                    return 0;

                std::list<Priority>::iterator tmpItr = bestList.begin();

                advance(tmpItr, urand(0, bestList.size() - 1));

                return (*tmpItr).GUIDfrom;
            }
        }
    }

    return 0;
}

uint64 const& boss_MedivhAI::GetMeleeTarget(uint64 const& piece)
{
    int tmpi, tmpj;    //temporary piece position

    if (!FindPlaceInBoard(piece, tmpi, tmpj))
        return 0;

    switch (chessBoard[tmpi][tmpj].ori)
    {
        case CHESS_ORI_N:
            if (tmpi > 0)
            {
                //front
                if (Enemy(piece, chessBoard[tmpi - 1][tmpj].piece))
                    return chessBoard[tmpi - 1][tmpj].piece;

                //strafe
                if (tmpj < 7 && Enemy(piece, chessBoard[tmpi - 1][tmpj + 1].piece))
                    return chessBoard[tmpi - 1][tmpj + 1].piece;

                if (tmpj > 0 && Enemy(piece, chessBoard[tmpi - 1][tmpj - 1].piece))
                    return chessBoard[tmpi - 1][tmpj - 1].piece;
            }
            break;
        case CHESS_ORI_E:
            if (tmpj < 7)
            {
                //front
                if (Enemy(piece, chessBoard[tmpi][tmpj + 1].piece))
                    return chessBoard[tmpi][tmpj + 1].piece;

                //strafe
                if (tmpi < 7 && Enemy(piece, chessBoard[tmpi + 1][tmpj + 1].piece))
                    return chessBoard[tmpi + 1][tmpj + 1].piece;

                if (tmpi > 0 && Enemy(piece, chessBoard[tmpi - 1][tmpj + 1].piece))
                    return chessBoard[tmpi - 1][tmpj + 1].piece;
            }
            break;
        case CHESS_ORI_S:
            if (tmpi < 7)
            {
                //front
                if (Enemy(piece, chessBoard[tmpi + 1][tmpj].piece))
                    return chessBoard[tmpi + 1][tmpj].piece;

                //strafe
                if (tmpj < 7 && Enemy(piece, chessBoard[tmpi + 1][tmpj + 1].piece))
                    return chessBoard[tmpi + 1][tmpj + 1].piece;

                if (tmpj > 0 && Enemy(piece, chessBoard[tmpi + 1][tmpj - 1].piece))
                    return chessBoard[tmpi + 1][tmpj - 1].piece;
            }
            break;
        case CHESS_ORI_W:
            if (tmpj > 0)
            {
                //front
                if (Enemy(piece, chessBoard[tmpi][tmpj - 1].piece))
                    return chessBoard[tmpi][tmpj - 1].piece;

                //strafe
                if (tmpi < 7 && Enemy(piece, chessBoard[tmpi + 1][tmpj - 1].piece))
                    return chessBoard[tmpi + 1][tmpj - 1].piece;

                if (tmpi > 0 && Enemy(piece, chessBoard[tmpi - 1][tmpj - 1].piece))
                    return chessBoard[tmpi - 1][tmpj - 1].piece;
            }
            break;
        default:
            break;
    }

    return 0;
}


bool boss_MedivhAI::IsChessPiece(Unit * unit)
{
    switch (unit->GetEntry())
    {
        case NPC_BISHOP_A:
        case NPC_BISHOP_H:
        case NPC_KING_A:
        case NPC_KING_H:
        case NPC_KNIGHT_A:
        case NPC_KNIGHT_H:
        case NPC_PAWN_A:
        case NPC_PAWN_H:
        case NPC_QUEEN_A:
        case NPC_QUEEN_H:
        case NPC_ROOK_A:
        case NPC_ROOK_H:
            return true;
        default:
            return false;
    }

    return false;
}

bool boss_MedivhAI::IsKing(uint64 const& piece)
{
    return IsKing(ObjectAccessor::GetCreature(*me, piece));
}

bool boss_MedivhAI::IsHealer(uint64 const& piece)
{
    return IsHealer(ObjectAccessor::GetCreature(*me, piece));
}

bool boss_MedivhAI::IsKing(Creature * piece)
{
    if (!piece)
        return false;

    switch (piece->GetEntry())
    {
        case NPC_KING_H:
        case NPC_KING_A:
            return true;

        default:
            return false;
    }

    return false;
}

bool boss_MedivhAI::IsHealer(Creature * piece)
{
    if (!piece)
        return false;

    switch (piece->GetEntry())
    {
        case NPC_BISHOP_H:
        case NPC_BISHOP_A:
            return true;

        default:
            return false;
    }

    return false;
}

bool boss_MedivhAI::IsMedivhsPiece(Unit * unit)
{
    if (unit)
    {
        switch (pInstance->GetData(DATA_CHESS_EVENT_TEAM))
        {
            case TEAM_ALLIANCE:
                if (unit->getFaction() == H_FACTION)
                    return true;
                break;
            case TEAM_HORDE:
                if (unit->getFaction() == A_FACTION)
                    return true;
                break;
        }
    }

    return false;
}

bool boss_MedivhAI::IsMedivhsPiece(uint64 const& unit)
{
    for (uint64 const& guid : medivhSidePieces)
        if (guid == unit)
            return true;

    return false;
}

bool boss_MedivhAI::IsInMoveList(uint64 const& unit, bool trigger)
{
    if (!trigger)
    {
        for (std::list<ChessTile>::iterator i = moveList.begin(); i != moveList.end(); ++i)
            if ((*i).piece == unit)
                return true;
    }
    else
    {
        for (std::list<ChessTile>::iterator i = moveList.begin(); i != moveList.end(); ++i)
            if ((*i).trigger == unit)
                return true;
    }

    return false;
}

bool boss_MedivhAI::IsInMoveRange(uint64 const& from, uint64 const& to, int range)
{
    if (!from || !to || !range)
        return false;

    int tmpI = -1, tmpJ = -1, i, tmpOffsetI, tmpOffsetJ;

    if (!FindPlaceInBoard(from, tmpI, tmpJ))
        return false;

    switch (range)
    {
        case 25:
            for (i = 0; i < OFFSET25COUNT; i++)
            {
                tmpOffsetI = tmpI + offsetTab25[i][0];
                tmpOffsetJ = tmpJ + offsetTab25[i][1];

                if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                    tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    if (chessBoard[tmpOffsetI][tmpOffsetJ].piece == to ||
                        chessBoard[tmpOffsetI][tmpOffsetJ].trigger == to)
                        return true;
            }
        case 20:
            for (i = 0; i < OFFSET20COUNT; i++)
            {
                tmpOffsetI = tmpI + offsetTab20[i][0];
                tmpOffsetJ = tmpJ + offsetTab20[i][1];

                if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                    tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    if (chessBoard[tmpOffsetI][tmpOffsetJ].piece == to ||
                        chessBoard[tmpOffsetI][tmpOffsetJ].trigger == to)
                        return true;
            }
        case 15:
            for (i = 0; i < OFFSET15COUNT; i++)
            {
                tmpOffsetI = tmpI + offsetTab15[i][0];
                tmpOffsetJ = tmpJ + offsetTab15[i][1];

                if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                    tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    if (chessBoard[tmpOffsetI][tmpOffsetJ].piece == to ||
                        chessBoard[tmpOffsetI][tmpOffsetJ].trigger == to)
                        return true;
            }
        case 8:
            for (i = 0; i < OFFSET8COUNT; i++)
            {
                tmpOffsetI = tmpI + offsetTab8[i][0];
                tmpOffsetJ = tmpJ + offsetTab8[i][1];

                if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                    tmpOffsetJ >= 0 && tmpOffsetJ < 8)
                    if (chessBoard[tmpOffsetI][tmpOffsetJ].piece == to ||
                        chessBoard[tmpOffsetI][tmpOffsetJ].trigger == to)
                        return true;
            }
            break;
        default:
            break;
    }

    return false;
}

void boss_MedivhAI::Reset()
{
    eventStarted = false;
    miniEventState = MINI_EVENT_NONE;
    miniEventTimer = 5000;
    endGameEventState = GAMEEND_NONE;
    endEventTimer = 2500;
    hordePieces = 16;
    alliancePieces = 16;
    medivhSidePieces.clear();
    tpList.clear();
    moveList.clear();

    chestGUID = 0;

    pInstance->SetData(DATA_CHESS_EVENT, NOT_STARTED);

    if (Creature* statusTrigger = pInstance->GetCreature(DATA_CHESS_STATUS))
        statusTrigger->AI()->DoAction(CHESS_STATUS_TRIGGER_END);
}

void boss_MedivhAI::EnterEvadeMode()
{
    me->GetMotionMaster()->MovementExpired();
    ScriptedAI::EnterEvadeMode();
}

void boss_MedivhAI::SayChessPieceDied(Unit * piece)
{
    if (pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_HORDE)
    {
        switch(piece->GetEntry())
        {
            case NPC_ROOK_H:
                Talk(SCRIPTTEXT_LOSE_ROOK_P);
                break;
            case NPC_ROOK_A:
                Talk(SCRIPTTEXT_LOSE_ROOK_M);
                break;
            case NPC_QUEEN_H:
                Talk(SCRIPTTEXT_LOSE_QUEEN_P);
                break;
            case NPC_QUEEN_A:
                Talk(SCRIPTTEXT_LOSE_QUEEN_M);
                break;
            case NPC_BISHOP_H:
                Talk(SCRIPTTEXT_LOSE_BISHOP_P);
                break;
            case NPC_BISHOP_A:
                Talk(SCRIPTTEXT_LOSE_BISHOP_M);
                break;
            case NPC_KNIGHT_H:
                Talk(SCRIPTTEXT_LOSE_KNIGHT_P);
                break;
            case NPC_KNIGHT_A:
                Talk(SCRIPTTEXT_LOSE_KNIGHT_M);
                break;
            case NPC_PAWN_H:
                Talk(RAND(SCRIPTTEXT_LOSE_PAWN_P_1, SCRIPTTEXT_LOSE_PAWN_P_2, SCRIPTTEXT_LOSE_PAWN_P_3));
                break;
            case NPC_PAWN_A:
                Talk(RAND(SCRIPTTEXT_LOSE_PAWN_M_1, SCRIPTTEXT_LOSE_PAWN_M_2));
                break;
            case NPC_KING_H:
                Talk(SCRIPTTEXT_MEDIVH_WIN);
                pInstance->SetData(DATA_CHESS_EVENT, FAIL);
                endGameEventState = GAMEEND_MEDIVH_WIN;
                endEventTimer = 2500;
                endEventCount = 0;
                break;
            case NPC_KING_A:
                if (pInstance->GetBossState(BOSS_CHESS) != DONE)
                    chestGUID = me->SummonGameObject(DUST_COVERED_CHEST, DUST_COVERED_CHEST_LOCATION, 0, 0, 0, 0, 7200000)->GetGUID();

                Talk(SCRIPTTEXT_PLAYER_WIN);
                pInstance->SetBossState(BOSS_CHESS, DONE);
                pInstance->SetData(DATA_CHESS_EVENT, DONE);
                endGameEventState = GAMEEND_MEDIVH_LOSE;
                endEventTimer = 2500;
                endEventCount = 0;
                break;

            default:
                break;
        }
    }
    else
    {
        switch(piece->GetEntry())
        {
            case NPC_ROOK_A:
                Talk(SCRIPTTEXT_LOSE_ROOK_P);
                break;
            case NPC_ROOK_H:
                Talk(SCRIPTTEXT_LOSE_ROOK_M);
                break;
            case NPC_QUEEN_A:
                Talk(SCRIPTTEXT_LOSE_QUEEN_P);
                break;
            case NPC_QUEEN_H:
                Talk(SCRIPTTEXT_LOSE_QUEEN_M);
                break;
            case NPC_BISHOP_A:
                Talk(SCRIPTTEXT_LOSE_BISHOP_P);
                break;
            case NPC_BISHOP_H:
                Talk(SCRIPTTEXT_LOSE_BISHOP_M);
                break;
            case NPC_KNIGHT_A:
                Talk(SCRIPTTEXT_LOSE_KNIGHT_P);
                break;
            case NPC_KNIGHT_H:
                Talk(SCRIPTTEXT_LOSE_KNIGHT_M);
                break;
            case NPC_PAWN_A:

                Talk(RAND(SCRIPTTEXT_LOSE_PAWN_P_1, SCRIPTTEXT_LOSE_PAWN_P_2, SCRIPTTEXT_LOSE_PAWN_P_3));
                break;

            case NPC_PAWN_H:

                Talk(RAND(SCRIPTTEXT_LOSE_PAWN_M_1, SCRIPTTEXT_LOSE_PAWN_M_2));
                break;

            case NPC_KING_A:

                Talk(SCRIPTTEXT_MEDIVH_WIN);
                pInstance->SetData(DATA_CHESS_EVENT, FAIL);
                endGameEventState = GAMEEND_MEDIVH_WIN;
                endEventTimer = 2500;
                endEventCount = 0;
                break;

            case NPC_KING_H:

                if (pInstance->GetBossState(BOSS_CHESS) != DONE)
                    chestGUID = me->SummonGameObject(DUST_COVERED_CHEST, DUST_COVERED_CHEST_LOCATION, 0, 0, 0, 0, 7200000)->GetGUID();

                Talk(SCRIPTTEXT_PLAYER_WIN);
                pInstance->SetBossState(BOSS_CHESS, DONE);
                pInstance->SetData(DATA_CHESS_EVENT, DONE);
                endGameEventState = GAMEEND_MEDIVH_LOSE;
                endEventTimer = 2500;
                endEventCount = 0;
                break;

            default:
                break;
        }
    }
}

void boss_MedivhAI::RemoveChessPieceFromBoard(uint64 const& piece)
{
    RemoveChessPieceFromBoard(pInstance->instance->GetCreature(piece));
}

void boss_MedivhAI::RemoveChessPieceFromBoard(Creature * piece)
{
    if (!piece)
        return;

    Creature * tmpC;
    uint32 tmpEntry = piece->GetEntry();

    if (piece->getFaction() == A_FACTION)
    {
        --alliancePieces;
        if (tmpC = me->SummonCreature(tmpEntry, allianceSideDeadWP[0][alliancePieces], allianceSideDeadWP[1][alliancePieces], POSITION_Z + 1.f, ORI_E, TEMPSUMMON_CORPSE_DESPAWN, 0))
            tmpC->AI()->SetData(1, 1);
    }
    else
    {
        --hordePieces;
        if (tmpC = me->SummonCreature(tmpEntry, hordeSideDeadWP[0][hordePieces], hordeSideDeadWP[1][hordePieces], POSITION_Z + 1, ORI_W, TEMPSUMMON_CORPSE_DESPAWN, 0))
            tmpC->AI()->SetData(1, 1);
    }

    if (tmpC)
    {
        tmpC->CombatStop();
        tmpC->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
    }

    int tmpI = -1, tmpJ = -1;
    uint64 tmpGUID = piece->GetGUID();

    RemoveFromMoveList(tmpGUID);

    if (FindPlaceInBoard(tmpGUID, tmpI, tmpJ))
        chessBoard[tmpI][tmpJ].piece = 0;

    bool medivhPiece = false;

    for (GuidList::iterator itr = medivhSidePieces.begin(); itr != medivhSidePieces.end();)
    {
        GuidList::iterator tmpItr = itr;
        ++itr;

        if ((*tmpItr) == tmpGUID)
        {
            medivhSidePieces.erase(tmpItr);
            medivhPiece = true;
            if (tmpC)
                unusedMedivhPieces.push_back(tmpC->GetGUID());
            break;
        }
    }

    if (!medivhPiece && tmpC)
        unusedPlayerPieces.push_back(tmpC->GetGUID());

    SayChessPieceDied(piece);
}

void boss_MedivhAI::SpawnPawns()
{
    Creature * tmp[2][8];

    for (int i = 0; i < 8; i++)
    {
        tmp[0][i] = me->SummonCreature(NPC_PAWN_A, SPAWN_POS, ORI_N, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);
        tmp[1][i] = me->SummonCreature(NPC_PAWN_H, SPAWN_POS, ORI_S, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);
        if (tmp[0][i])
        {
            chessBoard[6][i].piece = tmp[0][i]->GetGUID();
            tmp[0][i]->SetReactState(REACT_PASSIVE);
            tmp[0][i]->GetMotionMaster()->MovePoint(0, chessBoard[6][i].position);
        }
        chessBoard[6][i].ori = CHESS_ORI_N;
        if (tmp[1][i])
        {
            chessBoard[1][i].piece = tmp[1][i]->GetGUID();
            tmp[1][i]->SetReactState(REACT_PASSIVE);
            tmp[1][i]->GetMotionMaster()->MovePoint(0, chessBoard[1][i].position);
        }
        chessBoard[1][i].ori = CHESS_ORI_S;
    }

    if (pInstance)
    {
        if (pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_ALLIANCE)
            for (int i = 0; i < 8; i++)
                medivhSidePieces.push_back(tmp[1][i]->GetGUID());
        else
            for (int i = 0; i < 8; i++)
                medivhSidePieces.push_back(tmp[0][i]->GetGUID());
    }

    miniEventTimer = 10000;
}

void boss_MedivhAI::SpawnRooks()
{
    Creature * tmp1, * tmp2, * tmp3, * tmp4;

    tmp1 = me->SummonCreature(NPC_ROOK_A, SPAWN_POS, ORI_N, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp1)
    {
        chessBoard[7][0].piece = tmp1->GetGUID();
        chessBoard[7][0].ori = CHESS_ORI_N;
        tmp1->SetReactState(REACT_PASSIVE);
        tmp1->GetMotionMaster()->MovePoint(0, chessBoard[7][0].position);
    }

    tmp2 = me->SummonCreature(NPC_ROOK_A, SPAWN_POS, ORI_N, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp2)
    {
        chessBoard[7][7].piece = tmp2->GetGUID();
        chessBoard[7][7].ori = CHESS_ORI_N;
        tmp2->SetReactState(REACT_PASSIVE);
        tmp2->GetMotionMaster()->MovePoint(0, chessBoard[7][7].position);
    }


    tmp3 = me->SummonCreature(NPC_ROOK_H, SPAWN_POS, ORI_S, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp3)
    {
        chessBoard[0][0].piece = tmp3->GetGUID();
        chessBoard[0][0].ori = CHESS_ORI_S;
        tmp3->SetReactState(REACT_PASSIVE);
        tmp3->GetMotionMaster()->MovePoint(0, chessBoard[0][0].position);
    }

    tmp4 = me->SummonCreature(NPC_ROOK_H, SPAWN_POS, ORI_S, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp4)
    {
        chessBoard[0][7].piece = tmp4->GetGUID();
        chessBoard[0][7].ori = CHESS_ORI_S;
        tmp4->SetReactState(REACT_PASSIVE);
        tmp4->GetMotionMaster()->MovePoint(0, chessBoard[0][7].position);
    }

    if (pInstance && tmp1 && tmp2 && tmp3 && tmp4)
    {
        if (pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_ALLIANCE)
        {
            medivhSidePieces.push_back(tmp3->GetGUID());
            medivhSidePieces.push_back(tmp4->GetGUID());
        }
        else
        {
            medivhSidePieces.push_back(tmp1->GetGUID());
            medivhSidePieces.push_back(tmp2->GetGUID());
        }
    }
    miniEventTimer = 5000;
}

void boss_MedivhAI::SpawnKnights()
{
    Creature * tmp1, * tmp2, * tmp3, * tmp4;

    tmp1 = me->SummonCreature(NPC_KNIGHT_A, SPAWN_POS, ORI_N, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp1)
    {
        chessBoard[7][1].piece = tmp1->GetGUID();
        chessBoard[7][1].ori = CHESS_ORI_N;
        tmp1->SetReactState(REACT_PASSIVE);
        tmp1->GetMotionMaster()->MovePoint(0, chessBoard[7][1].position);
    }

    tmp2 = me->SummonCreature(NPC_KNIGHT_A, SPAWN_POS, ORI_N, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp2)
    {
        chessBoard[7][6].piece = tmp2->GetGUID();
        chessBoard[7][6].ori = CHESS_ORI_N;
        tmp2->SetReactState(REACT_PASSIVE);
        tmp2->GetMotionMaster()->MovePoint(0, chessBoard[7][6].position);
    }


    tmp3 = me->SummonCreature(NPC_KNIGHT_H, SPAWN_POS, ORI_S, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp3)
    {
        chessBoard[0][1].piece = tmp3->GetGUID();
        chessBoard[0][1].ori = CHESS_ORI_S;
        tmp3->SetReactState(REACT_PASSIVE);
        tmp3->GetMotionMaster()->MovePoint(0, chessBoard[0][1].position);
    }

    tmp4 = me->SummonCreature(NPC_KNIGHT_H, SPAWN_POS, ORI_S, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp4)
    {
        chessBoard[0][6].piece = tmp4->GetGUID();
        chessBoard[0][6].ori = CHESS_ORI_S;
        tmp4->SetReactState(REACT_PASSIVE);
        tmp4->GetMotionMaster()->MovePoint(0, chessBoard[0][6].position);
    }

    if (pInstance && tmp1 && tmp2 && tmp3 && tmp4)
    {
        if (pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_ALLIANCE)
        {
            medivhSidePieces.push_back(tmp3->GetGUID());
            medivhSidePieces.push_back(tmp4->GetGUID());
        }
        else
        {
            medivhSidePieces.push_back(tmp1->GetGUID());
            medivhSidePieces.push_back(tmp2->GetGUID());
        }
    }
    miniEventTimer = 5000;
}

void boss_MedivhAI::SpawnBishops()
{
    Creature * tmp1, * tmp2, * tmp3, * tmp4;

    tmp1 = me->SummonCreature(NPC_BISHOP_A, SPAWN_POS, ORI_N, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp1)
    {
        chessBoard[7][2].piece = tmp1->GetGUID();
        chessBoard[7][2].ori = CHESS_ORI_N;
        tmp1->SetReactState(REACT_PASSIVE);
        tmp1->GetMotionMaster()->MovePoint(0, chessBoard[7][2].position);
    }

    tmp2 = me->SummonCreature(NPC_BISHOP_A, SPAWN_POS, ORI_N, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp2)
    {
        chessBoard[7][5].piece = tmp2->GetGUID();
        chessBoard[7][5].ori = CHESS_ORI_N;
        tmp2->SetReactState(REACT_PASSIVE);
        tmp2->GetMotionMaster()->MovePoint(0, chessBoard[7][5].position);
    }


    tmp3 = me->SummonCreature(NPC_BISHOP_H, SPAWN_POS, ORI_S, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp3)
    {
        chessBoard[0][2].piece = tmp3->GetGUID();
        chessBoard[0][2].ori = CHESS_ORI_S;
        tmp3->SetReactState(REACT_PASSIVE);
        tmp3->GetMotionMaster()->MovePoint(0, chessBoard[0][2].position);
    }

    tmp4 = me->SummonCreature(NPC_BISHOP_H, SPAWN_POS, ORI_S, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp4)
    {
        chessBoard[0][5].piece = tmp4->GetGUID();
        chessBoard[0][5].ori = CHESS_ORI_S;
        tmp4->SetReactState(REACT_PASSIVE);
        tmp4->GetMotionMaster()->MovePoint(0, chessBoard[0][5].position);
    }

    if (pInstance && tmp1 && tmp2 && tmp3 && tmp4)
    {
        if (pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_ALLIANCE)
        {
            medivhSidePieces.push_back(tmp3->GetGUID());
            medivhSidePieces.push_back(tmp4->GetGUID());
        }
        else
        {
            medivhSidePieces.push_back(tmp1->GetGUID());
            medivhSidePieces.push_back(tmp2->GetGUID());
        }
    }

    miniEventTimer = 5000;
}

void boss_MedivhAI::SpawnQueens()
{
    Creature * tmp1, * tmp2;

    tmp1 = me->SummonCreature(NPC_QUEEN_A, SPAWN_POS, ORI_N, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp1)
    {
        chessBoard[7][3].piece = tmp1->GetGUID();
        chessBoard[7][3].ori = CHESS_ORI_N;
        tmp1->SetReactState(REACT_PASSIVE);
        tmp1->GetMotionMaster()->MovePoint(0, chessBoard[7][3].position);
    }

    tmp2 = me->SummonCreature(NPC_QUEEN_H, SPAWN_POS, ORI_S, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp2)
    {
        chessBoard[0][3].piece = tmp2->GetGUID();
        chessBoard[0][3].ori = CHESS_ORI_S;
        tmp2->SetReactState(REACT_PASSIVE);
        tmp2->GetMotionMaster()->MovePoint(0, chessBoard[0][3].position);
    }

    if (pInstance && tmp1 && tmp2)
    {
        if (pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_ALLIANCE)
            medivhSidePieces.push_back(tmp2->GetGUID());
        else
            medivhSidePieces.push_back(tmp1->GetGUID());
    }
    miniEventTimer = 5000;
}

void boss_MedivhAI::SpawnKings()
{
    Creature * tmp1, * tmp2;

    tmp1 = me->SummonCreature(NPC_KING_A, SPAWN_POS, ORI_N, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp1)
    {
        chessBoard[7][4].piece = tmp1->GetGUID();
        chessBoard[7][4].ori = CHESS_ORI_N;
        tmp1->SetReactState(REACT_PASSIVE);
        tmp1->GetMotionMaster()->MovePoint(0, chessBoard[7][4].position);
    }

    tmp2 = me->SummonCreature(NPC_KING_H, SPAWN_POS, ORI_S, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);

    if (tmp2)
    {
        chessBoard[0][4].piece = tmp2->GetGUID();
        chessBoard[0][4].ori = CHESS_ORI_S;
        tmp2->SetReactState(REACT_PASSIVE);
        tmp2->GetMotionMaster()->MovePoint(0, chessBoard[0][4].position);
    }

    if (pInstance && tmp1 && tmp2)
    {
        if (pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_ALLIANCE)
            medivhSidePieces.push_back(tmp2->GetGUID());
        else
            medivhSidePieces.push_back(tmp1->GetGUID());
    }
    miniEventTimer = 5000;
}

void boss_MedivhAI::SpawnTriggers()
{
    Creature * tmp = NULL;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            tmp = me->SummonCreature(TRIGGER_ID, chessBoard[i][j].position.GetPositionX(), chessBoard[i][j].position.GetPositionY(), chessBoard[i][j].position.GetPositionZ(), ORI_W, TEMPSUMMON_DEAD_DESPAWN, 0);
            if (tmp)
            {
                chessBoard[i][j].trigger = tmp->GetGUID();
                if (i > 1 && i < 6)
                {
                    chessBoard[i][j].piece = 0;
                    chessBoard[i][j].ori = CHESS_ORI_CHOOSE;
                }
                tmp->SetReactState(REACT_PASSIVE);
            }
        }
    }
}

void boss_MedivhAI::ClearBoard()
{
    Creature * tmpC;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (tmpC = ObjectAccessor::GetCreature(*me, chessBoard[i][j].piece))
            {
                tmpC->DespawnOrUnsummon();
            }

            if (tmpC = ObjectAccessor::GetCreature(*me, chessBoard[i][j].trigger))
            {
                tmpC->DespawnOrUnsummon();   
            }

            chessBoard[i][j].piece = 0;
            chessBoard[i][j].trigger = 0;
            chessBoard[i][j].ori = CHESS_ORI_CHOOSE;
        }
    }

    for (uint64 const& guid : unusedMedivhPieces)
    {
        if (tmpC = ObjectAccessor::GetCreature(*me, guid))
        {
            tmpC->DespawnOrUnsummon();
        }
    }

    for (uint64 const& guid : unusedPlayerPieces)
    {
        if (tmpC = ObjectAccessor::GetCreature(*me, guid))
        {
            tmpC->DespawnOrUnsummon();
        }
    }

    unusedMedivhPieces.clear();
    unusedPlayerPieces.clear();
    medivhSidePieces.clear();

    Map::PlayerList const &plList = me->GetMap()->GetPlayers();
    for (Map::PlayerList::const_iterator itr = plList.begin(); itr != plList.end(); ++itr)
        if (Player * plr = itr->GetSource())
            plr->RemoveAurasDueToSpell(SPELL_POSSES_CHESSPIECE);
}

void boss_MedivhAI::PrepareBoardForEvent()
{
    SpawnTriggers();
    SpawnKings();

    cheatTimer = CHEAT_TIMER;

    firstCheatDamageReq = urand(FIRST_CHEAT_HP_MIN*1000, FIRST_CHEAT_HP_MAX*1000)/1000.0; 
    secondCheatDamageReq = urand(SECOND_CHEAT_HP_MIN*1000, SECOND_CHEAT_HP_MAX*1000)/1000.0;
    thirdCheatDamagereq = urand(THIRD_CHEAT_HP_MIN*1000, THIRD_CHEAT_HP_MAX*1000)/1000.0;

    currentCheatMask = 0;
    cheatMask = 0;

    pInstance->SetData(DATA_CHESS_DAMAGE, 0);
}

void boss_MedivhAI::StartMiniEvent()
{
    eventStarted = true;

    ClearBoard();

    if (chestGUID)
        return;

    miniEventState = MINI_EVENT_KING;
}

void boss_MedivhAI::StartEvent()
{
    if (pInstance->GetData(DATA_CHESS_EVENT) == IN_PROGRESS)
        return;

    pInstance->SetData(DATA_CHESS_EVENT, IN_PROGRESS);
    DoZoneInCombat();
    addPieceToMoveCheckTimer = 10000;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (Creature* tmpC = ObjectAccessor::GetCreature(*me, chessBoard[i][j].piece))
            {
                tmpC->CastSpell(tmpC, SPELL_MOVE_MARKER, false);
                tmpC->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
            }

    if (Creature* statusTrigger = pInstance->GetCreature(DATA_CHESS_STATUS))
        statusTrigger->AI()->DoAction(CHESS_STATUS_TRIGGER_START);
}

bool boss_MedivhAI::IsEventStarted()
{
    return eventStarted;
}

void boss_MedivhAI::UpdateAI(const uint32 diff)
{
    if (miniEventState)
    {
        if (miniEventTimer < diff)
        {
            switch (miniEventState)
            {
                case MINI_EVENT_KING:
                    PrepareBoardForEvent();
                    miniEventState = MINI_EVENT_QUEEN;
                    break;
                case MINI_EVENT_QUEEN:
                    SpawnQueens();
                    miniEventState = MINI_EVENT_BISHOP;
                    break;
                case MINI_EVENT_BISHOP:
                    SpawnBishops();
                    miniEventState = MINI_EVENT_KNIGHT;
                    break;
                case MINI_EVENT_KNIGHT:
                    SpawnKnights();
                    miniEventState = MINI_EVENT_ROOK;
                    break;
                case MINI_EVENT_ROOK:
                    SpawnRooks();
                    miniEventState = MINI_EVENT_PAWN;
                    break;
                case MINI_EVENT_PAWN:
                    SpawnPawns();
                    miniEventState = MINI_EVENT_END;
                    break;
                case MINI_EVENT_END:
                    for (int i = 0; i < 8; i++)
                        for (int j = 0; j < 8; j++)
                        {
                            ChangePieceFacing(chessBoard[i][j].piece, chessBoard[4][j].trigger);

                            if (Creature* tmpC = ObjectAccessor::GetCreature(*me, chessBoard[i][j].piece))
                            {
                                tmpC->SetWalk(true);
                                tmpC->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            }
                        }
                    // no break;
                default:
                    miniEventState = MINI_EVENT_NONE;
                    break;
            }
        }
        else
            miniEventTimer -= diff;
        return;
    }

    if (endGameEventState)
    {
        if (endEventTimer < diff)
        {
            Creature * tmpC;
            endEventTimer = 2500;
            switch (endGameEventState)
            {
                case GAMEEND_MEDIVH_WIN:
                    for (uint64 const& guid : unusedMedivhPieces)
                        if (tmpC = ObjectAccessor::GetCreature(*me, guid))
                            tmpC->HandleEmoteCommand(RAND(EMOTE_ONESHOT_CHEER, EMOTE_ONESHOT_APPLAUD));

                    for (uint64 const& guid : unusedPlayerPieces)
                        if (tmpC = ObjectAccessor::GetCreature(*me, guid))
                            tmpC->HandleEmoteCommand(EMOTE_ONESHOT_CRY);

                    if (endEventCount >= 5)
                        endGameEventState = GAMEEND_CLEAR_BOARD;
                    break;
                case GAMEEND_MEDIVH_LOSE:
                    for (uint64 const& guid : unusedPlayerPieces)
                        if (tmpC = ObjectAccessor::GetCreature(*me, guid))
                            tmpC->HandleEmoteCommand(RAND(EMOTE_ONESHOT_CHEER, EMOTE_ONESHOT_APPLAUD));

                    for (uint64 const& guid : unusedMedivhPieces)
                        if (tmpC = ObjectAccessor::GetCreature(*me, guid))
                            tmpC->HandleEmoteCommand(EMOTE_ONESHOT_CRY);

                    if (endEventCount >= 5)
                        endGameEventState = GAMEEND_CLEAR_BOARD;
                    break;
                case GAMEEND_CLEAR_BOARD:
                    ClearBoard();

                    if (chestGUID)
                    {
                        endGameEventState = GAMEEND_DESPAWN_CHEST;
                        endEventTimer = 180000;
                    }
                    else
                        EnterEvadeMode();
                    break;
                case GAMEEND_DESPAWN_CHEST:
                    EnterEvadeMode();
                    return;
            }
            endEventCount++;
        }
        else
            endEventTimer -= diff;

        /*if (endEventLightningTimer < diff)
        {
            Creature * tmpC;
            int count = rand()%5;

            for (int i = 0; i < count; ++i)
                if (tmpC = ObjectAccessor::GetCreature(*me, chessBoard[rand()%8][rand()%8].trigger))
                    me->CastSpell(tmpC, SPELL_GAME_OVER, true);
            endEventLightningTimer = urand(100, 1000);
        }
        else
            endEventLightningTimer -= diff;*/

        return;
    }

    if (pInstance->GetData(DATA_CHESS_EVENT) != IN_PROGRESS)
        return;

    if (addPieceToMoveCheckTimer <= diff)
    {
        if (urand(0, 100) < chanceToSelfMove)
            ChoosePieceToMove();

        addPieceToMoveCheckTimer = ADD_PIECE_TO_MOVE_TIMER;
    }
    else
        addPieceToMoveCheckTimer -= diff;

    if (cheatTimer <= diff)
    {
        uint32 oldCheatMask = cheatMask;

        if (firstCheatDamageReq < pInstance->GetData(DATA_CHESS_DAMAGE))
            cheatMask |= FIRST_CHEAT_MASK;

        if (secondCheatDamageReq < pInstance->GetData(DATA_CHESS_DAMAGE) && !(oldCheatMask & SECOND_CHEAT_MASK))
        {
            cheatMask |= SECOND_CHEAT_MASK;
            if (oldCheatMask & FIRST_CHEAT_MASK)
                currentCheatMask |= FIRST_CHEAT_MASK;
        }

        if (thirdCheatDamagereq < pInstance->GetData(DATA_CHESS_DAMAGE) && !(oldCheatMask & THIRD_CHEAT_MASK))
        {
            cheatMask |= THIRD_CHEAT_MASK;
            if (oldCheatMask & SECOND_CHEAT_MASK)
                currentCheatMask |= SECOND_CHEAT_MASK;
            if (oldCheatMask & FIRST_CHEAT_MASK)
                currentCheatMask |= FIRST_CHEAT_MASK;
        }

        if (!(currentCheatMask & FIRST_CHEAT_MASK) && (cheatMask & FIRST_CHEAT_MASK))
        {
            currentCheatMask |= FIRST_CHEAT_MASK;

            std::list<ChessTile> tmpList;

            for (int i = 0; i < 8; ++i)
                for (int j = 0; j < 8; ++j)
                    if (chessBoard[i][j].piece && !IsMedivhsPiece(chessBoard[i][j].piece))
                        tmpList.push_back(ChessTile(chessBoard[i][j]));

            int tmp = 3;
            if (tmpList.size() < 3)
                tmp = tmpList.size();

            for (int i = 0; i < tmp; ++i)
            {
                std::list<ChessTile>::iterator itr = tmpList.begin();
                advance(itr, urand(0, tmpList.size() - 1));

                if (Creature * tmpC = ObjectAccessor::GetCreature(*me, (*itr).trigger))
                    if (Creature* trigger = tmpC->SummonCreature(CHEAT_TRIGGER_ID, *tmpC, TEMPSUMMON_TIMED_DESPAWN, 60000))
                    {
                        trigger->SetPassive();
                        trigger->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED | UNIT_FLAG_NON_ATTACKABLE);
                        trigger->CastSpell(trigger, SPELL_FURY_OF_MEDIVH, false);
                    }

                tmpList.erase(itr);
            }

            Talk(SCRIPTTEXT_MEDIVH_CHEAT_1);

            cheatTimer = CHEAT_TIMER;
        }
        else if (!(currentCheatMask & SECOND_CHEAT_MASK) && (cheatMask & SECOND_CHEAT_MASK))
        {
            currentCheatMask |= SECOND_CHEAT_MASK;

            std::list<ChessTile> tmpList;

            for (int i = 0; i < 8; ++i)
                for (int j = 0; j < 8; ++j)
                    if (chessBoard[i][j].piece && IsMedivhsPiece(chessBoard[i][j].piece))
                        tmpList.push_back(ChessTile(chessBoard[i][j]));

            int tmp = 3;
            if (tmpList.size() < 3)
                tmp = tmpList.size();

            for (int i = 0; i < tmp; ++i)
            {
                std::list<ChessTile>::iterator itr = tmpList.begin();
                advance(itr, urand(0, tmpList.size() - 1));

                if (Creature * tmpC = ObjectAccessor::GetCreature(*me, (*itr).trigger))
                    me->CastSpell(tmpC, SPELL_HAND_OF_MEDIVH, true);

                tmpList.erase(itr);
            }

            Talk(SCRIPTTEXT_MEDIVH_CHEAT_2);

            cheatTimer = CHEAT_TIMER;
        }
        else if (!(currentCheatMask & THIRD_CHEAT_MASK) && (cheatMask & SECOND_CHEAT_MASK) && thirdCheatDamagereq < pInstance->GetData(DATA_CHESS_DAMAGE))
        {
            currentCheatMask |= THIRD_CHEAT_MASK;

            for (uint64 const& guid : medivhSidePieces)
                if (Creature * tmpC = ObjectAccessor::GetCreature(*me, guid))
                    tmpC->SetHealth(tmpC->GetMaxHealth());

            Talk(SCRIPTTEXT_MEDIVH_CHEAT_3);

            cheatTimer = CHEAT_TIMER;
        }
        else
            cheatTimer = 5000; // next check in 5 seconds
    }
    else
        cheatTimer -= diff;

    // reset mask
    if (currentCheatMask && currentCheatMask >= cheatMask)
    {
        currentCheatMask = 0;

        if (!(cheatMask & THIRD_CHEAT_MASK))
            cheatTimer += 60000;
    }
}

void boss_MedivhAI::SetOrientation(uint64 const& piece, ChessOrientation ori)
{
    int tmpi = -1, tmpj = -1;    //temp piece location in array

    if (!FindPlaceInBoard(piece, tmpi, tmpj))
        return;

    if (ori == CHESS_ORI_CHOOSE)
    {
        float tmpN = 99, tmpS = 99, tmpE = 99, tmpW = 99;
        float pieceOri;

        Creature * tmpPiece = pInstance->instance->GetCreature(piece);
        if (tmpPiece)
        {
            pieceOri = tmpPiece->GetOrientation();
            if (pieceOri <0)
                pieceOri += 2* M_PI;
            if (pieceOri > ORI_N && pieceOri <= ORI_W)
            {
                tmpN = pieceOri - ORI_N;
                tmpW = ORI_W - pieceOri;

                if (tmpN < tmpW)
                    ori = CHESS_ORI_N;
                else
                    ori = CHESS_ORI_W;
            }
            else if (pieceOri > ORI_W && pieceOri <= ORI_S)
            {
                tmpW = pieceOri - ORI_W;
                tmpS = ORI_S - pieceOri;

                if (tmpW < tmpS)
                    ori = CHESS_ORI_W;
                else
                    ori = CHESS_ORI_S;
            }
            else if (pieceOri > ORI_S && pieceOri <= ORI_E)
            {
                tmpS = pieceOri - ORI_S;
                tmpE = ORI_E - pieceOri;

                if (tmpS < tmpE)
                    ori = CHESS_ORI_S;
                else
                    ori = CHESS_ORI_E;
            }
            else if (pieceOri > ORI_E)
            {
                tmpE = pieceOri - ORI_E;
                tmpN = 6.28 + ORI_N - pieceOri;

                if (tmpE < tmpN)
                    ori = CHESS_ORI_E;
                else
                    ori = CHESS_ORI_N;
            }
            else if (pieceOri <= ORI_N)
            {
                tmpW = 6.28 + pieceOri - ORI_E;
                tmpN = ORI_N - pieceOri;

                if (tmpE < tmpN)
                    ori = CHESS_ORI_E;
                else
                    ori = CHESS_ORI_N;
            }
        }
    }

    chessBoard[tmpi][tmpj].ori = ori;

    Creature * cPiece = me->GetMap()->GetCreature(piece);

    float Orientation = 0.f;

    if (cPiece)
    {
        switch (ori)
        {
            case CHESS_ORI_N:
                Orientation = ORI_N;
                break;
            case CHESS_ORI_E:
                Orientation = ORI_E;
                break;
            case CHESS_ORI_S:
                Orientation = ORI_S;
                break;
            case CHESS_ORI_W:
                Orientation = ORI_W;
                break;
            default:
                break;
        }

        cPiece->SetFacingTo(Orientation);
/*
        me->GetMap()->CreatureRelocation(cPiece, chessBoard[tmpi][tmpj].position.GetPositionX(), chessBoard[tmpi][tmpj].position.GetPositionY(), chessBoard[tmpi][tmpj].position.GetPositionZ(), cPiece->GetOrientation());

        Map::PlayerList const& players = me->GetMap()->GetPlayers();

        if (!players.isEmpty())
            for(Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                if (Player* plr = itr->getSource())
                    cPiece->NearTeleportTo(chessBoard[tmpi][tmpj].position.GetPositionX(), chessBoard[tmpi][tmpj].position.GetPositionY(), chessBoard[tmpi][tmpj].position.GetPositionZ(), 0);
*/
    }
}

uint64 boss_MedivhAI::FindTriggerGUID(uint64 const& piece)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chessBoard[i][j].piece == piece)
                return chessBoard[i][j].trigger;
        }
    }

    return 0;
}

Creature * boss_MedivhAI::FindTrigger(uint64 const& piece)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chessBoard[i][j].piece == piece)
                return pInstance->instance->GetCreature(chessBoard[i][j].trigger);
        }
    }

    return NULL;
}

bool boss_MedivhAI::ChessSquareIsEmpty(uint64 const& trigger)
{
    if (IsInMoveList(trigger, true))
        return false;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chessBoard[i][j].trigger == trigger)
            {
                if (chessBoard[i][j].piece)
                    return false;
                else
                    return true;
            }
        }
    }

    return false;
}

bool boss_MedivhAI::ChessSquareIsEmpty(int i, int j)
{
    if (IsInMoveList(chessBoard[i][j].trigger))
        return false;

    if (chessBoard[i][j].piece)
        return false;

    return true;
}

bool boss_MedivhAI::CanMoveTo(uint64 const& trigger, uint64 const& piece)
{
    if (!trigger || !piece)
        return false;

    int moveRange = GetMoveRange(piece);
    bool inRange = IsInMoveRange(piece, trigger, moveRange);
    bool isEmpty = ChessSquareIsEmpty(trigger);
    return inRange && isEmpty;
}

void boss_MedivhAI::AddTriggerToMove(uint64 const& trigger, uint64 const& piece, bool player)
{
    RemoveFromMoveList(piece);
    ChessTile tmp;
    tmp.piece = piece;
    tmp.trigger = trigger;

    moveList.push_back(tmp);

    uint16 tmpChance = urand(0, 100);

    //check, if tmpChance is higher than chanceToMove then medivh also can move one of his pieces
    if (player && tmpChance < chanceToMove)
        ChoosePieceToMove();
}

void boss_MedivhAI::RemoveFromMoveList(uint64 const& unit)
{
    for (std::list<ChessTile>::iterator itr = moveList.begin(); itr != moveList.end();)
    {
        std::list<ChessTile>::iterator tmpItr = itr;
        ++itr;
        if ((*tmpItr).piece == unit || (*tmpItr).trigger == unit)
        {
            if (Creature * tmpC = ObjectAccessor::GetCreature(*me, (*tmpItr).trigger))
                ((move_triggerAI*)tmpC->AI())->RemoveFromMove((*tmpItr).piece);

            moveList.erase(tmpItr);
            return;
        }
    }
}

void boss_MedivhAI::ChangePlaceInBoard(uint64 const& piece, uint64 const& destTrigger)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (chessBoard[i][j].piece == piece && chessBoard[i][j].trigger != destTrigger)
            {
                chessBoard[i][j].piece = 0;
                chessBoard[i][j].ori = CHESS_ORI_CHOOSE;
            }

            if (chessBoard[i][j].trigger == destTrigger)
            {
                chessBoard[i][j].piece = piece;
                chessBoard[i][j].ori = CHESS_ORI_CHOOSE;
            }
        }
    }

}

void boss_MedivhAI::ChangePieceFacing(uint64 const& piece, uint64 const& destTrigger)
{
    ChangePieceFacing(ObjectAccessor::GetCreature(*me, piece), ObjectAccessor::GetCreature(*me, destTrigger));
}

void boss_MedivhAI::ChangePieceFacing(Creature * piece, Creature * destTrigger)
{
    if (!piece || !destTrigger)
        return;

    piece->SetInFront(destTrigger);
    SetOrientation(piece->GetGUID());
/*
    int tmpI = -1, tmpJ = -1;

    if (!FindPlaceInBoard(piece->GetGUID(), tmpI, tmpJ))
        return;

    Creature * tmpC = NULL;
    switch (chessBoard[tmpI][tmpJ].ori)
    {
        case CHESS_ORI_N:
            tmpC = ObjectAccessor::GetCreature(*me, chessBoard[tmpI - 1][tmpJ].trigger);
            break;
        case CHESS_ORI_E:
            tmpC = ObjectAccessor::GetCreature(*me, chessBoard[tmpI][tmpJ + 1].trigger);
            break;
        case CHESS_ORI_S:
            tmpC = ObjectAccessor::GetCreature(*me, chessBoard[tmpI + 1][tmpJ].trigger);
            break;
        case CHESS_ORI_W:
            tmpC = ObjectAccessor::GetCreature(*me, chessBoard[tmpI][tmpJ - 1].trigger);
            break;
    }

    if (tmpC)
        piece->SetFacingToObject(tmpC);
*/
}

uint32 boss_MedivhAI::GetMoveSpell(Creature * piece)
{
    switch (piece->GetEntry())
    {
        case NPC_QUEEN_A:
        case NPC_QUEEN_H:
            return SPELL_MOVE_4;
        case NPC_KING_A:
        case NPC_KING_H:
            return SPELL_MOVE_5;
        case NPC_BISHOP_A:
        case NPC_BISHOP_H:
            return SPELL_MOVE_6;
        case NPC_KNIGHT_A:
        case NPC_KNIGHT_H:
            return SPELL_MOVE_3;
        case NPC_ROOK_A:
        case NPC_ROOK_H:
            return SPELL_MOVE_7;
        case NPC_PAWN_A:
        case NPC_PAWN_H:
            return SPELL_MOVE_1;
    }

    return 0;
}

bool boss_MedivhAI::FindPlaceInBoard(uint64 const& unit, int & i, int & j)
{
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            if (chessBoard[x][y].piece == unit || chessBoard[x][y].trigger == unit)
            {
                i = x;
                j = y;
                return true;
            }
        }
    }
    return false;
}

/*
pseudocode:

    for each medivh piece:
        calculate actual square priority
        for each square in range:
            if square is empty and isn't in move list then:
                calculate priority
                if priority is > 0
                    add square info (priority) to list
                    sum priority
        if square info list in not empty
            choose random priority from 0 to priority sum
            search for square for randomed priority
            if chosen position is better than actual position (rand(0, chosen+actual) > actual)
                add possible move to list

    sum square move priorities
    choose random (or best ?) move from list

    make move to chosen

Calculate Priority:
    set base priority for square
    modify priority based on count of enemies in melee
    modify priority based on way were we want to move
*/

int boss_MedivhAI::CalculatePriority(uint64 const& piece, uint64 const& trigger)
{
    // set base priority for square
    int tmpPrior = START_PRIORITY;
    int pieceId = GetEntry(piece);

    // modify priority based on count of enemies in melee

    int meleeCount = GetCountOfEnemyInMelee(piece, true);

    switch (pieceId)
    {
        case NPC_PAWN_A:
        case NPC_PAWN_H:
            switch (meleeCount)
            {
                case 0:
                    tmpPrior += MELEE_PRIORITY_1_0;
                    break;
                case 1:
                    tmpPrior += MELEE_PRIORITY_1_1;
                    break;
                case 2:
                    tmpPrior += MELEE_PRIORITY_1_2;
                    break;
                case 3:
                    tmpPrior += MELEE_PRIORITY_1_3;
                    break;
                default:
                    tmpPrior += MELEE_PRIORITY_1_4;
                    break;
            }
            break;

        case NPC_ROOK_A:
        case NPC_ROOK_H:
        case NPC_KNIGHT_A:
        case NPC_KNIGHT_H:
            switch (meleeCount)
            {
                case 0:
                    tmpPrior += MELEE_PRIORITY_2_0;
                    break;
                case 1:
                    tmpPrior += MELEE_PRIORITY_2_1;
                    break;
                case 2:
                    tmpPrior += MELEE_PRIORITY_2_2;
                    break;
                case 3:
                    tmpPrior += MELEE_PRIORITY_2_3;
                    break;
                default:
                    tmpPrior += MELEE_PRIORITY_2_4;
                    break;
            }
            break;

        case NPC_KING_A:
        case NPC_KING_H:
            switch (meleeCount)
            {
                case 0:
                    tmpPrior += MELEE_PRIORITY_3_0;
                    break;
                case 1:
                    tmpPrior += MELEE_PRIORITY_3_1;
                    break;
                case 2:
                    tmpPrior += MELEE_PRIORITY_3_2;
                    break;
                case 3:
                    tmpPrior += MELEE_PRIORITY_3_3;
                    break;
                default:
                    tmpPrior += MELEE_PRIORITY_3_4;
                    break;
            }
            break;

        case NPC_QUEEN_A:
        case NPC_QUEEN_H:
        case NPC_BISHOP_A:
        case NPC_BISHOP_H:
            switch (meleeCount)
            {
                case 0:
                    tmpPrior += MELEE_PRIORITY_4_0;
                    break;
                case 1:
                    tmpPrior += MELEE_PRIORITY_4_1;
                    break;
                case 2:
                    tmpPrior += MELEE_PRIORITY_4_2;
                    break;
                case 3:
                    tmpPrior += MELEE_PRIORITY_4_3;
                    break;
                default:
                    tmpPrior += MELEE_PRIORITY_4_4;
                    break;
            }
            break;
    }

    // modify priority based on way were we want to move

    int tmpIP, tmpJP, tmpIT, tmpJT;

    if (FindPlaceInBoard(piece, tmpIP, tmpJP) && FindPlaceInBoard(trigger, tmpIT, tmpJT))
    {
        if (tmpIP == tmpIT && tmpJP == tmpJT)
            tmpPrior += STAY_IN_PLACE_PRIOR_MOD;
        else
        {
            if (pInstance->GetData(DATA_CHESS_EVENT_TEAM) == TEAM_ALLIANCE)   // if player is alliance
            {
                if (tmpIP < 2)
                {
                    if (tmpIP > tmpIT)
                        tmpPrior += MOVE_BACK_PRIOR_MOD;
                    else if (/*tmpIP == tmpIT && */tmpJP != tmpJT)
                        tmpPrior += (tmpIP != tmpIT ? MOVE_STRAFE_PRIOR_MOD/4 : MOVE_STRAFE_PRIOR_MOD);
                    else
                        tmpPrior += MOVE_DEFAULT_PRIOR_MOD;
                }
                else
                {
                    if (tmpIP > 5)
                    {
                        if (tmpIP < tmpIT)
                            tmpPrior += MOVE_BACK_PRIOR_MOD;
                        else if (/*tmpIP == tmpIT && */tmpJP != tmpJT)
                            tmpPrior += (tmpIP != tmpIT ? MOVE_STRAFE_PRIOR_MOD/4 : MOVE_STRAFE_PRIOR_MOD);
                        else
                            tmpPrior += MOVE_DEFAULT_PRIOR_MOD;
                    }
                    else
                    {
                        if (tmpIP < 4)
                        {
                            if (tmpIP > tmpIT)
                                tmpPrior += MOVE_BACK_PRIOR_MOD/2;
                            else if (/*tmpIP == tmpIT && */tmpJP != tmpJT)
                                tmpPrior += (tmpIP != tmpIT ? MOVE_STRAFE_PRIOR_MOD/8 : MOVE_STRAFE_PRIOR_MOD/4);
                            else
                                tmpPrior += MOVE_DEFAULT_PRIOR_MOD;
                        }
                        else
                        {
                            if (tmpIP > 3)
                            {
                                if (tmpIP > tmpIT)
                                    tmpPrior += MOVE_BACK_PRIOR_MOD/3;
                                else if (/*tmpIP == tmpIT && */tmpJP != tmpJT)
                                    tmpPrior += (tmpIP != tmpIT ? MOVE_STRAFE_PRIOR_MOD/8 : MOVE_STRAFE_PRIOR_MOD/4);
                                else
                                    tmpPrior += MOVE_DEFAULT_PRIOR_MOD;
                            }
                        }
                    }
                }
            }
            else
            {
                if (tmpIP > 5)
                {
                    if (tmpIP < tmpIT)
                        tmpPrior += MOVE_BACK_PRIOR_MOD;
                    else if (/*tmpIP == tmpIT && */tmpJP != tmpJT)
                        tmpPrior += (tmpIP != tmpIT ? MOVE_STRAFE_PRIOR_MOD/4 : MOVE_STRAFE_PRIOR_MOD);
                    else
                        tmpPrior += MOVE_DEFAULT_PRIOR_MOD;
                }
                else
                {
                    if (tmpIP < 2)
                    {
                        if (tmpIP > tmpIT)
                            tmpPrior += MOVE_BACK_PRIOR_MOD;
                        else if (/*tmpIP == tmpIT && */tmpJP != tmpJT)
                            tmpPrior += (tmpIP != tmpIT ? MOVE_STRAFE_PRIOR_MOD/4 : MOVE_STRAFE_PRIOR_MOD);
                        else
                            tmpPrior += MOVE_DEFAULT_PRIOR_MOD;
                    }
                    else
                    {
                        if (tmpIP > 3)
                        {
                            if (tmpIP < tmpIT)
                                tmpPrior += MOVE_BACK_PRIOR_MOD/2;
                            else if (/*tmpIP == tmpIT && */tmpJP != tmpJT)
                                tmpPrior += (tmpIP != tmpIT ? MOVE_STRAFE_PRIOR_MOD/8 : MOVE_STRAFE_PRIOR_MOD/4);
                            else
                                tmpPrior += MOVE_DEFAULT_PRIOR_MOD;
                        }
                        else
                        {
                            if (tmpIP < 4)
                            {
                                if (tmpIP < tmpIT)
                                    tmpPrior += MOVE_BACK_PRIOR_MOD/3;
                                else if (/*tmpIP == tmpIT && */tmpJP != tmpJT)
                                    tmpPrior += (tmpIP != tmpIT ? MOVE_STRAFE_PRIOR_MOD/8 : MOVE_STRAFE_PRIOR_MOD/4);
                                else
                                    tmpPrior += MOVE_DEFAULT_PRIOR_MOD;
                            }
                        }
                    }
                }
            }
        }
    }

    return tmpPrior;
}

void boss_MedivhAI::ChoosePieceToMove()
{
    std::list<Priority> possibleMoveList;
    int possibleMovePrioritySum = 0;

    // for each medivh piece
    for (uint64 const& guid : medivhSidePieces)
    {
        if (IsInMoveList(guid))
            continue;

        std::list<Priority> tmpPriorList;
        int priorSum = 0, i, tmpOffsetI, tmpOffsetJ, tmpI, tmpJ;
        // calculate actual square prior
        uint32 actualPriority = CalculatePriority(guid, FindTriggerGUID(guid));

        if (!FindPlaceInBoard(guid, tmpI, tmpJ))
            continue;

        // for each sqare in range
        switch (GetMoveRange(guid))
        {
            case 25:
                for (i = 0; i < OFFSET25COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab25[i][0];
                    tmpOffsetJ = tmpJ + offsetTab25[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8 &&
                        !chessBoard[tmpOffsetI][tmpOffsetJ].piece &&                // if square is empty
                        !IsInMoveList(chessBoard[tmpOffsetI][tmpOffsetJ].trigger, true))// and isn't in move list
                    {
                        Priority prior;
                        prior.GUIDfrom = guid;
                        prior.GUIDto = chessBoard[tmpOffsetI][tmpOffsetJ].trigger;

                        // calculate priority
                        prior.prior = CalculatePriority(prior.GUIDfrom, prior.GUIDto);

                        // if priority is > 0
                        if (prior.prior > 0)
                        {
                            tmpPriorList.push_back(prior);  // add square info (priority) to list
                            priorSum += prior.prior;        // sum priority
                        }
                    }
                }
            case 20:
                for (i = 0; i < OFFSET20COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab20[i][0];
                    tmpOffsetJ = tmpJ + offsetTab20[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8 &&
                        !chessBoard[tmpOffsetI][tmpOffsetJ].piece &&                // if square is empty
                        !IsInMoveList(chessBoard[tmpOffsetI][tmpOffsetJ].trigger, true))// and isn't in move list
                    {
                        Priority prior;
                        prior.GUIDfrom = guid;
                        prior.GUIDto = chessBoard[tmpOffsetI][tmpOffsetJ].trigger;

                        // calculate priority
                        prior.prior = CalculatePriority(prior.GUIDfrom, prior.GUIDto);

                        // if priority is > 0
                        if (prior.prior > 0)
                        {
                            tmpPriorList.push_back(prior);  // add square info (priority) to list
                            priorSum += prior.prior;        // sum priority
                        }
                    }

                }
            case 15:
                for (i = 0; i < OFFSET15COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab15[i][0];
                    tmpOffsetJ = tmpJ + offsetTab15[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8 &&
                        !chessBoard[tmpOffsetI][tmpOffsetJ].piece &&                // if square is empty
                        !IsInMoveList(chessBoard[tmpOffsetI][tmpOffsetJ].trigger, true))// and isn't in move list
                    {
                        Priority prior;
                        prior.GUIDfrom = guid;
                        prior.GUIDto = chessBoard[tmpOffsetI][tmpOffsetJ].trigger;

                        // calculate priority
                        prior.prior = CalculatePriority(prior.GUIDfrom, prior.GUIDto);

                        // if priority is > 0
                        if (prior.prior > 0)
                        {
                            tmpPriorList.push_back(prior);  // add square info (priority) to list
                            priorSum += prior.prior;        // sum priority
                        }
                    }

                }
            case 8:
                for (i = 0; i < OFFSET8COUNT; i++)
                {
                    tmpOffsetI = tmpI + offsetTab8[i][0];
                    tmpOffsetJ = tmpJ + offsetTab8[i][1];

                    if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
                        tmpOffsetJ >= 0 && tmpOffsetJ < 8 &&
                        !chessBoard[tmpOffsetI][tmpOffsetJ].piece &&                // if square is empty
                        !IsInMoveList(chessBoard[tmpOffsetI][tmpOffsetJ].trigger, true))// and isn't in move list
                    {
                        Priority prior;
                        prior.GUIDfrom = guid;
                        prior.GUIDto = chessBoard[tmpOffsetI][tmpOffsetJ].trigger;

                        // calculate priority
                        prior.prior = CalculatePriority(prior.GUIDfrom, prior.GUIDto);

                        // if priority is > 0
                        if (prior.prior > 0)
                        {
                            tmpPriorList.push_back(prior);  // add square info (priority) to list
                            priorSum += prior.prior;        // sum priority
                        }
                    }

                }
                break;
            default:
                break;
        }

        // if square info list in not empty
        if (tmpPriorList.empty() || priorSum <= 0)
            continue;

        switch (rand()%2)
        {
            case 0:
            {
                // choose random priority from 0 to priority sum
                int chosenPrior = urand(0, priorSum);
                int tmpPriorSum = 0;
                // search for randomed square
                for (std::list<Priority>::iterator priorItr = tmpPriorList.begin(); priorItr != tmpPriorList.end(); ++ priorItr)
                {
                    if (chosenPrior >= tmpPriorSum && chosenPrior < tmpPriorSum + (*priorItr).prior)
                    {
                        // rand if chosen position is better than actual position
                        if (urand(0, actualPriority + (*priorItr).prior) > actualPriority)
                        {
                            possibleMoveList.push_back(*priorItr);          // add possible move to list
                            possibleMovePrioritySum += (*priorItr).prior;   // sum square move priorities
                        }
                        break;
                    }

                    tmpPriorSum += (*priorItr).prior;
                }
                break;
            }
            case 1:
            {
                std::list<Priority> bestList;
                if (tmpPriorList.empty())
                    continue;

                Priority best = tmpPriorList.front();
                for (std::list<Priority>::iterator itr = tmpPriorList.begin(); itr != tmpPriorList.end(); ++itr)
                {
                    if (best.prior < (*itr).prior)
                    {
                        best = *itr;
                        bestList.clear();
                        bestList.push_back(*itr);
                    }
                    else if (best.prior == (*itr).prior)
                    {
                        bestList.push_back(*itr);
                    }
                }

                if (bestList.empty())
                    continue;

                std::list<Priority>::iterator itr = bestList.begin();
                advance(itr, urand(0, bestList.size()-1));

                possibleMoveList.push_back(*itr);          // add possible move to list
                possibleMovePrioritySum += (*itr).prior;   // sum square move priorities
                break;
            }
        }
    }

    if (possibleMoveList.empty())
        return;

    Priority chosen;
    if (rand()%2)
    {
        // choose random move from list
        int tmpChosenPrior = urand(0, possibleMovePrioritySum);
        int tmpPriorSum = 0;
        for (std::list<Priority>::iterator itr = possibleMoveList.begin(); itr != possibleMoveList.end(); ++itr)
        {
            if (tmpChosenPrior >= tmpPriorSum && tmpChosenPrior < tmpPriorSum + (*itr).prior)
            {
                chosen = *itr;
                break;
            }

            tmpPriorSum += (*itr).prior;
        }
    }
    else
    {
        // choose best move from list
        Priority best = possibleMoveList.front();
        for (std::list<Priority>::iterator itr = possibleMoveList.begin(); itr != possibleMoveList.end(); ++itr)
            if (best.prior < (*itr).prior)
                best = *itr;

        chosen = best;
    }

    if (!chosen.GUIDfrom || !chosen.GUIDto)
        return;

    // make move to chosen
    Creature * tmpC = ObjectAccessor::GetCreature(*me, chosen.GUIDfrom);
    Creature * tmpT = ObjectAccessor::GetCreature(*me, chosen.GUIDto);

    if (tmpC && tmpT)
        tmpC->CastSpell(tmpT, GetMoveSpell(tmpC), false);
}

uint32 boss_MedivhAI::GetEntry(uint64 const& piece)
{
    Creature * tmp = ObjectAccessor::GetCreature(*me, piece);
    if (!tmp)
        return 0;

    return tmp->GetEntry();
}

uint32 boss_MedivhAI::GetDeadEntryForPiece(Creature * piece)
{
    if (!piece)
        return 0;

    return GetDeadEntryForPiece(piece->GetEntry());
}

uint32 boss_MedivhAI::GetDeadEntryForPiece(uint32 entry)
{
    switch (entry)
    {
        case NPC_PAWN_H:
            return 16556;
        case NPC_PAWN_A:
            return 16567;
        case NPC_KNIGHT_H:
            return 16561;
        case NPC_KNIGHT_A:
            return 16569;
        case NPC_QUEEN_H:
            return 16557;
        case NPC_QUEEN_A:
            return 16572;
        case NPC_BISHOP_H:
            return 16560;
        case NPC_BISHOP_A:
            return 16571;
        case NPC_ROOK_H:
            return 16562;
        case NPC_ROOK_A:
            return 16570;
        case NPC_KING_H:
            return 16563;
        case NPC_KING_A:
            return 16581;
        default:
            return 0;
    }

    return 0;
}

void boss_MedivhAI::CheckChangeFacing(uint64 const& piece, int i, int j)
{
    if (i == -1 || j == -1)
        if (!FindPlaceInBoard(piece, i, j))
            return;

    if (IsInMoveList(piece))
        return;

    ChessOrientation actualOri = chessBoard[i][j].ori;
    ChessOrientation tmpOri = CHESS_ORI_N;
    ChessOrientation targetOri = CHESS_ORI_CHOOSE;
    uint64 target, tmpTarget, targetTrigger;
    int targetPrior = 0, tmpPrior = 0;

    for (int k = 0; k < OFFSETMELEECOUNT; ++k)
    {
        int tmpOffsetI = offsetTabMelee[k][0];
        int tmpOffsetJ = offsetTabMelee[k][1];

        if (tmpOffsetI == 0)
        {
            if (tmpOffsetJ == 1)
                tmpOri = CHESS_ORI_E;
            else
                tmpOri = CHESS_ORI_W;
        }
        else if (tmpOffsetJ == 0)
        {
            if (tmpOffsetI == 1)
                tmpOri = CHESS_ORI_S;
            else
                tmpOri = CHESS_ORI_N;
        }

        tmpOffsetI += i;
        tmpOffsetJ += j;

        if (tmpOffsetI >= 0 && tmpOffsetI < 8 &&
            tmpOffsetJ >= 0 && tmpOffsetJ < 8)
        {
            tmpTarget = chessBoard[tmpOffsetI][tmpOffsetJ].piece;
            if (Enemy(piece, tmpTarget))
            {
                tmpPrior = GetAttackPriority(tmpTarget);

                if (tmpPrior > targetPrior)
                {
                    target = tmpTarget;
                    targetOri = tmpOri;
                    targetPrior = tmpPrior;
                    targetTrigger = chessBoard[tmpOffsetI][tmpOffsetJ].trigger;

                }
            }
        }
    }

    if (targetOri != CHESS_ORI_CHOOSE)
    {
        if (targetOri != actualOri)
        {
            Creature * tmpC = ObjectAccessor::GetCreature(*me, piece);
            Creature * tmpT = ObjectAccessor::GetCreature(*me, targetTrigger);
            if (tmpC && tmpT)
                tmpC->CastSpell(tmpT, SPELL_CHANGE_FACING, false);
        }
    }
}

//other

void npc_chess_statusAI::Reset()
{
    me->SetDisableGravity(true);
    me->NearTeleportTo(-11080.599609f, -1876.380005f, 231.000092f, 0.0f);
}

void npc_chess_statusAI::DoAction(const int32 param)
{
    switch (param)
    {
        case CHESS_STATUS_TRIGGER_START:
            me->CastSpell(me, SPELL_GAME_IN_SESSION, false);
            break;
        case CHESS_STATUS_TRIGGER_END:
            me->RemoveAurasDueToSpell(SPELL_GAME_IN_SESSION);
            break;
        default:
            break;
    }
}

void AddSC_chess_event()
{
    new npc_chesspiece();
    new npc_echo_of_medivh();
    new CreatureAILoader<move_triggerAI>("chess_move_trigger");
    new CreatureAILoader<npc_chess_statusAI>("npc_chess_status");
}
