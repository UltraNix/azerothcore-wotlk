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
#include "zulaman.h"
#include "GridNotifiers.h"
#include "CellImpl.h"

enum Yells
{
    SAY_AGGRO,
    SAY_FIRE_BOMBS,
    SAY_SUMMON_HATCHER,
    SAY_ALL_EGGS,
    SAY_BERSERK,
    SAY_SLAY,
    SAY_DEATH,
    SAY_EVENT_STRANGERS,
    SAY_EVENT_FRIENDS
};

enum Spells
{
    // Jan'alai
    SPELL_FLAME_BREATH          = 43140,
    SPELL_FIRE_WALL             = 43113,
    SPELL_ENRAGE                = 44779,
    SPELL_SUMMON_PLAYERS        = 43097,
    SPELL_TELE_TO_CENTER        = 43098, // coord
    SPELL_HATCH_ALL             = 43144,
    SPELL_BERSERK               = 45078,

    // Fire Bob Spells
    SPELL_FIRE_BOMB_CHANNEL     = 42621, // last forever
    SPELL_FIRE_BOMB_THROW       = 42628, // throw visual
    SPELL_FIRE_BOMB_DUMMY       = 42629, // bomb visual
    SPELL_FIRE_BOMB_DAMAGE      = 42630,

    // Hatcher Spells
    SPELL_HATCH_EGG             = 42471,   // 43734
    SPELL_SUMMON_HATCHLING      = 42493,

    // Hatchling Spells
    SPELL_FLAMEBUFFET           = 43299
};

enum Creatures
{
    NPC_AMANI_HATCHER           = 23818,
    NPC_HATCHLING               = 23598, // 42493
    NPC_EGG                     = 23817,
    NPC_FIRE_BOMB               = 23920
};

const int area_dx = 44;
const int area_dy = 51;

float JanalainPos[1][3] =
{
    {-33.93f, 1149.27f, 19}
};

float FireWallCoords[4][4] =
{
    {-10.13f, 1149.27f, 19, 3.1415f},
    {-33.93f, 1123.90f, 19, 0.5f*3.1415f},
    {-54.80f, 1150.08f, 19, 0},
    {-33.93f, 1175.68f, 19, 1.5f*3.1415f}
};

float hatcherway[2][5][3] =
{
    {
        {-87.46f, 1170.09f, 6},
        {-74.41f, 1154.75f, 6},
        {-52.74f, 1153.32f, 19},
        {-33.37f, 1172.46f, 19},
        {-33.09f, 1203.87f, 19}
    },
    {
        {-86.57f, 1132.85f, 6},
        {-73.94f, 1146.00f, 6},
        {-52.29f, 1146.51f, 19},
        {-33.57f, 1125.72f, 19},
        {-34.29f, 1095.22f, 19}
    }
};

struct boss_janalaiAI : public ScriptedAI
{
    boss_janalaiAI(Creature* creature) : ScriptedAI(creature)
    {
        instance = creature->GetInstanceScript();
    }

    InstanceScript* instance;

    uint32 FireBreathTimer;
    uint32 BombTimer;
    uint32 BombSequenceTimer;
    uint32 BombCount;
    uint32 HatcherTimer;
    uint32 EnrageTimer;

    bool noeggs;
    bool enraged;
    bool isBombing;

    bool isFlameBreathing;

    uint64 FireBombGUIDs[40];

    void Reset()
    {
        instance->SetData(DATA_JANALAIEVENT, NOT_STARTED);

        FireBreathTimer = 8000;
        BombTimer = 30000;
        BombSequenceTimer = 1000;
        BombCount = 0;
        HatcherTimer = 10000;
        EnrageTimer = MINUTE*5*IN_MILLISECONDS;

        noeggs = false;
        isBombing =false;
        enraged = false;

        isFlameBreathing = false;

        for (uint8 i = 0; i < 40; ++i)
            FireBombGUIDs[i] = 0;

        HatchAllEggs(1);
    }

    void JustDied(Unit* /*killer*/)
    {
        Talk(SAY_DEATH);

        instance->SetData(DATA_JANALAIEVENT, DONE);
    }

    void KilledUnit(Unit* /*victim*/)
    {
        Talk(SAY_SLAY);
    }

    void EnterCombat(Unit* /*who*/)
    {
        instance->SetData(DATA_JANALAIEVENT, IN_PROGRESS);

        Talk(SAY_AGGRO);
    }

    void DamageDealt(Unit* target, uint32 &damage, DamageEffectType /*damagetype*/)
    {
        if (isFlameBreathing)
        {
            if (!me->HasInArc(M_PI/6, target))
                damage = 0;
        }
    }

    void FireWall()
    {
        uint8 WallNum;
        Creature* wall = nullptr;
        for (uint8 i = 0; i < 4; ++i)
        {
            if (i == 0 || i == 2)
                WallNum = 3;
            else
                WallNum = 2;

            for (uint8 j = 0; j < WallNum; j++)
            {
                if (WallNum == 3)
                    wall = me->SummonCreature(NPC_FIRE_BOMB, FireWallCoords[i][0], FireWallCoords[i][1]+5*(j-1), FireWallCoords[i][2], FireWallCoords[i][3], TEMPSUMMON_TIMED_DESPAWN, 15000);
                else
                    wall = me->SummonCreature(NPC_FIRE_BOMB, FireWallCoords[i][0]-2+4*j, FireWallCoords[i][1], FireWallCoords[i][2], FireWallCoords[i][3], TEMPSUMMON_TIMED_DESPAWN, 15000);
                if (wall) wall->CastSpell(wall, SPELL_FIRE_WALL, true);
            }
        }
    }

    void SpawnBombs()
    {
        float dx, dy;
        for (int i(0); i < 40; ++i)
        {
            dx = float(irand(-area_dx/2, area_dx/2));
            dy = float(irand(-area_dy/2, area_dy/2));

            Creature* bomb = DoSpawnCreature(NPC_FIRE_BOMB, dx, dy, 0, 0, TEMPSUMMON_TIMED_DESPAWN, 15000);
            if (bomb)
                FireBombGUIDs[i] = bomb->GetGUID();
        }
        BombCount = 0;
    }

    bool HatchAllEggs(uint32 action) //1: reset, 2: isHatching all
    {
        std::list<Creature*> templist;
        float x, y, z;
        me->GetPosition(x, y, z);
        me->GetCreatureListWithEntryInGrid(templist, NPC_EGG, 100.0f);

        if (templist.empty())
            return false;

        for (auto itr : templist)
        {
            if (action == 1)
                itr->SetDisplayId(10056);
            else if (action == 2 && itr->GetDisplayId() != 11686)
                itr->CastSpell(itr, SPELL_HATCH_EGG, false);
        }
        return true;
    }

    void Boom()
    {
        std::list<Creature*> templist;
        float x, y, z;
        me->GetPosition(x, y, z);
        me->GetCreatureListWithEntryInGrid(templist, NPC_FIRE_BOMB, 100.0f);
        for (auto itr : templist)
        {
            itr->CastSpell(itr, SPELL_FIRE_BOMB_DAMAGE, true);
            itr->RemoveAllAuras();
        }
    }

    void HandleBombSequence()
    {
        if (BombCount < 40)
        {
            if (Unit* FireBomb = ObjectAccessor::GetUnit(*me, FireBombGUIDs[BombCount]))
            {
                FireBomb->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                DoCast(FireBomb, SPELL_FIRE_BOMB_THROW, true);
                FireBomb->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }
            ++BombCount;
            if (BombCount == 40)
            {
                BombSequenceTimer = 5000;
            } else BombSequenceTimer = 100;
        }
        else
        {
            Boom();
            isBombing = false;
            BombTimer = urand(20000, 40000);
            me->RemoveAurasDueToSpell(SPELL_FIRE_BOMB_CHANNEL);
            if (EnrageTimer <= 10000)
                EnrageTimer = 0;
            else
                EnrageTimer -= 10000;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (isFlameBreathing)
        {
            if (!me->IsNonMeleeSpellCast(false))
                isFlameBreathing = false;
            else
                return;
        }

        if (isBombing)
        {
            if (BombSequenceTimer <= diff)
                HandleBombSequence();
            else
                BombSequenceTimer -= diff;
            return;
        }

        if (!UpdateVictim())
            return;

        //enrage if under 25% hp before 5 min.
        if (!enraged && HealthBelowPct(25))
            EnrageTimer = 0;

        if (EnrageTimer <= diff)
        {
            if (!enraged)
            {
                DoCast(me, SPELL_ENRAGE, true);
                enraged = true;
                EnrageTimer = 300000;
            }
            else
            {
                Talk(SAY_BERSERK);
                DoCast(me, SPELL_BERSERK, true);
                EnrageTimer = 300000;
            }
        } else EnrageTimer -= diff;

        if (BombTimer <= diff)
        {
            Talk(SAY_FIRE_BOMBS);

            me->AttackStop();
            me->GetMotionMaster()->Clear();
            me->NearTeleportTo(JanalainPos[0][0], JanalainPos[0][1], JanalainPos[0][2], me->GetOrientation());
            me->StopMovingOnCurrentPos();
            DoCast(me, SPELL_FIRE_BOMB_CHANNEL, false);

            FireWall();
            SpawnBombs();
            isBombing = true;
            BombSequenceTimer = 100;

            //Teleport every Player into the middle
            Map* map = me->GetMap();
            if (!map->IsDungeon())
                return;

            Map::PlayerList const &PlayerList = map->GetPlayers();
            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                if (Player* i_pl = i->GetSource())
                    if (i_pl->IsAlive())
                        DoTeleportPlayer(i_pl, JanalainPos[0][0]-5+rand()%10, JanalainPos[0][1]-5+rand()%10, JanalainPos[0][2], 0);
            return;
        } else BombTimer -= diff;

        if (!noeggs)
        {
            if (HealthBelowPct(35))
            {
                Talk(SAY_ALL_EGGS);

                me->AttackStop();
                me->GetMotionMaster()->Clear();
                me->NearTeleportTo(JanalainPos[0][0], JanalainPos[0][1], JanalainPos[0][2], me->GetOrientation());
                me->StopMovingOnCurrentPos();
                DoCast(me, SPELL_HATCH_ALL, false);
                HatchAllEggs(2);
                noeggs = true;
            }
            else if (HatcherTimer <= diff)
            {
                if (HatchAllEggs(0))
                {
                    Talk(SAY_SUMMON_HATCHER);
                    me->SummonCreature(NPC_AMANI_HATCHER, hatcherway[0][0][0], hatcherway[0][0][1], hatcherway[0][0][2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                    me->SummonCreature(NPC_AMANI_HATCHER, hatcherway[1][0][0], hatcherway[1][0][1], hatcherway[1][0][2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                    HatcherTimer = 90000;
                }
                else
                    noeggs = true;
            } else HatcherTimer -= diff;
        }

        EnterEvadeIfOutOfCombatArea();

        DoMeleeAttackIfReady();

        if (FireBreathTimer <= diff)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
            {
                me->AttackStop();
                me->GetMotionMaster()->Clear();
                DoCast(target, SPELL_FLAME_BREATH, false);
                me->StopMoving();
                isFlameBreathing = true;
            }
            FireBreathTimer = 8000;
        } else FireBreathTimer -= diff;
    }
                    
    bool CheckEvadeIfOutOfCombatArea() const override
    {
        return me->GetPositionZ() <= 12.0f;
    }

private:
    EventMap events;
};

struct npc_janalai_firebombAI : public ScriptedAI
{
    npc_janalai_firebombAI(Creature* creature) : ScriptedAI(creature){ }

    void Reset() override { }

    void SpellHit(Unit* /*caster*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_FIRE_BOMB_THROW)
            DoCast(me, SPELL_FIRE_BOMB_DUMMY, true);
    }

    void EnterCombat(Unit* /*who*/) override { }
    void AttackStart(Unit* /*who*/) override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }
    void UpdateAI(uint32 /*diff*/) override { }
};

struct npc_janalai_hatcherAI : public ScriptedAI
{
    npc_janalai_hatcherAI(Creature* creature) : ScriptedAI(creature)
    {
        instance = creature->GetInstanceScript();
    }

    InstanceScript* instance;

    uint32 waypoint;
    uint32 HatchNum;
    uint32 WaitTimer;

    bool side;
    bool hasChangedSide;
    bool isHatching;

    void Reset() override
    {
        me->SetWalk(true);
        side =(me->GetPositionY() < 1150);
        waypoint = 0;
        isHatching = false;
        hasChangedSide = false;
        WaitTimer = 1;
        HatchNum = 0;
    }

    bool HatchEggs(uint32 num)
    {
        std::list<Creature*> templist;
        float x, y, z;
        me->GetPosition(x, y, z);
        me->GetCreatureListWithEntryInGrid(templist, 23817, 50.0f);
        for (auto itr : templist)
        {
            if (itr->GetDisplayId() != 11686)
            {
                itr->CastSpell(itr, SPELL_HATCH_EGG, false);
                num--;
            }
        }

        return num == 0;   // if num == 0, no more templist
    }

    void EnterCombat(Unit* /*who*/) override { }
    void AttackStart(Unit* /*who*/) override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }

    void MovementInform(uint32, uint32) override
    {
        if (waypoint == 5)
        {
            isHatching = true;
            HatchNum = 1;
            WaitTimer = 5000;
        }
        else
            WaitTimer = 1;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!instance || !(instance->GetData(DATA_JANALAIEVENT) == IN_PROGRESS))
        {
            me->DisappearAndDie();
            return;
        }

        if (!isHatching)
        {
            if (WaitTimer)
            {
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MovePoint(0, hatcherway[side][waypoint][0], hatcherway[side][waypoint][1], hatcherway[side][waypoint][2]);
                ++waypoint;
                WaitTimer = 0;
            }
        }
        else
        {
            if (WaitTimer <= diff)
            {
                if (HatchEggs(HatchNum))
                {
                    ++HatchNum;
                    WaitTimer = 10000;
                }
                else if (!hasChangedSide)
                {
                    side = side ? 0 : 1;
                    isHatching = false;
                    waypoint = 3;
                    WaitTimer = 1;
                    hasChangedSide = true;
                }
                else
                    me->DisappearAndDie();

            } else WaitTimer -= diff;
        }
    }
};

enum Hatchling
{
    EVENT_FLAMEBUFFET = 1
};

struct npc_janalai_hatchlingAI : public ScriptedAI
{
    npc_janalai_hatchlingAI(Creature* creature) : ScriptedAI(creature)
    {
        instance = creature->GetInstanceScript();
    }

    void Reset() override
    {
        if (me->GetPositionY() > 1150)
            me->GetMotionMaster()->MovePoint(0, hatcherway[0][3][0]+rand()%4-2, 1150.0f+rand()%4-2, hatcherway[0][3][2]);
        else
            me->GetMotionMaster()->MovePoint(0, hatcherway[1][3][0]+rand()%4-2, 1150.0f+rand()%4-2, hatcherway[1][3][2]);

        me->SetDisableGravity(true);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _events.ScheduleEvent(EVENT_FLAMEBUFFET, 7000);
    }

    void UpdateAI(uint32 diff)
    {
        if (!instance || !(instance->GetData(DATA_JANALAIEVENT) == IN_PROGRESS))
        {
            me->DisappearAndDie();
            return;
        }

        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (_events.ExecuteEvent() == EVENT_FLAMEBUFFET)
        {
            DoCastVictim(SPELL_FLAMEBUFFET);
            _events.Repeat(10000);
        }

        DoMeleeAttackIfReady();
    }

private:
    InstanceScript* instance;
    EventMap _events;
};

struct npc_janalai_eggAI : public ScriptedAI
{
    npc_janalai_eggAI(Creature* creature) : ScriptedAI(creature){ }

    void Reset() override { }

    void UpdateAI(uint32 /*diff*/) override { }

    void SpellHit(Unit* /*caster*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_HATCH_EGG)
            DoCast(SPELL_SUMMON_HATCHLING);
    }
};

void AddSC_boss_janalai()
{
    new CreatureAILoader<boss_janalaiAI>("boss_janalai");
    new CreatureAILoader<npc_janalai_firebombAI>("npc_janalai_firebomb");
    new CreatureAILoader<npc_janalai_hatcherAI>("npc_janalai_hatcher");
    new CreatureAILoader<npc_janalai_hatchlingAI>("npc_janalai_hatchling");
    new CreatureAILoader<npc_janalai_eggAI>("npc_janalai_egg");
}

