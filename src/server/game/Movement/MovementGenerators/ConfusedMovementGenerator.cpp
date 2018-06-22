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

#include "Creature.h"
#include "MapManager.h"
#include "ConfusedMovementGenerator.h"
#include "VMapFactory.h"
#include "MoveSplineInit.h"
#include "MoveSpline.h"
#include "Player.h"

template<class T>
void ConfusedMovementGenerator<T>::DoInitialize(T* unit)
{
    float const wander_distance = 4.0f + i_extendedRange;
    float x = unit->GetPositionX();
    float y = unit->GetPositionY();
    float z = unit->GetPositionZ();

    Map const* map = unit->GetBaseMap();

    bool is_water_ok, is_land_ok;
    _InitSpecific(unit, is_water_ok, is_land_ok);

    i_waypoints.resize( MAX_CONF_WAYPOINTS );
    for (uint8 idx = 0; idx < MAX_CONF_WAYPOINTS; ++idx)
    {
        float wanderX = x + (wander_distance * (float)rand_norm() - wander_distance/2);
        float wanderY = y + (wander_distance * (float)rand_norm() - wander_distance/2);

        // prevent invalid coordinates generation
        Trinity::NormalizeMapCoord(wanderX);
        Trinity::NormalizeMapCoord(wanderY);

        float new_z = map->GetHeight(unit->GetPhaseMask(), wanderX, wanderY, z, true);
        if (new_z <= INVALID_HEIGHT || fabs(z-new_z) > 3.0f)
        {
            i_waypoints[ idx ].x = idx > 0 ? i_waypoints[ idx - 1 ].x : x;
            i_waypoints[ idx ].y = idx > 0 ? i_waypoints[ idx - 1 ].y : y;
            i_waypoints[ idx ].z = idx > 0 ? i_waypoints[ idx - 1 ].z : z;
            continue;
        }
        else if (unit->IsWithinLOS(wanderX, wanderY, z))
        {
            bool is_water = map->IsInWater(wanderX, wanderY, z);

            if ((is_water && !is_water_ok) || (!is_water && !is_land_ok))
            {
                //! Cannot use coordinates outside our InhabitType. Use the current or previous position.
                i_waypoints[ idx ].x = idx > 0 ? i_waypoints[ idx - 1 ].x : x;
                i_waypoints[ idx ].y = idx > 0 ? i_waypoints[ idx - 1 ].y : y;
                i_waypoints[ idx ].z = idx > 0 ? i_waypoints[ idx - 1 ].z : z;
                continue;
            }
        }
        else
        {
            //! Trying to access path outside line of sight. Skip this by using the current or previous position.
            i_waypoints[ idx ].x = idx > 0 ? i_waypoints[ idx - 1 ].x : x;
            i_waypoints[ idx ].y = idx > 0 ? i_waypoints[ idx - 1 ].y : y;
            i_waypoints[ idx ].z = idx > 0 ? i_waypoints[ idx - 1 ].z : z;
            continue;
        }

        //unit->UpdateAllowedPositionZ(wanderX, wanderY, z);

        //! Positions are fine - apply them to this waypoint
        i_waypoints[ idx ].x = wanderX;
        i_waypoints[ idx ].y = wanderY;
        i_waypoints[ idx ].z = new_z;
    }

    unit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit->AddUnitState(UNIT_STATE_CONFUSED);

    unit->StopMovingOnCurrentPos();
    DoUpdate( unit, 1 );
}

template<>
void ConfusedMovementGenerator<Creature>::_InitSpecific(Creature* creature, bool &is_water_ok, bool &is_land_ok)
{
    is_water_ok = creature->CanSwim();
    is_land_ok  = creature->CanWalk();
}

template<>
void ConfusedMovementGenerator<Player>::_InitSpecific(Player* , bool &is_water_ok, bool &is_land_ok)
{
    is_water_ok = true;
    is_land_ok  = true;
}

template<class T>
void ConfusedMovementGenerator<T>::DoReset(T* unit)
{
    DoInitialize(unit);
}

template<class T>
bool ConfusedMovementGenerator<T>::DoUpdate(T* unit, uint32 diff)
{
    if (unit->HasUnitState(UNIT_STATE_NOT_MOVE))
    {
        unit->ClearUnitState( UNIT_STATE_CONFUSED_MOVE );

        if ( !unit->movespline->Finalized() )
        {
            unit->StopMovingOnCurrentPos();
        }

        return true;
    }

    if (unit->movespline->Finalized())
    {
        Movement::MoveSplineInit spline(unit);
        spline.MovebyPath( i_waypoints, urand( 0, MAX_CONF_WAYPOINTS - 1 ) );
        spline.SetCyclic();
        spline.Launch();

        unit->AddUnitState( UNIT_STATE_CONFUSED_MOVE );
    }

    return true;
}

template<>
void ConfusedMovementGenerator<Player>::DoFinalize(Player* unit)
{
    unit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit->ClearUnitState(UNIT_STATE_CONFUSED | UNIT_STATE_CONFUSED_MOVE);

    unit->StopMovingOnCurrentPos();
}

template<>
void ConfusedMovementGenerator<Creature>::DoFinalize(Creature* unit)
{
    unit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit->ClearUnitState(UNIT_STATE_CONFUSED | UNIT_STATE_CONFUSED_MOVE);

    if (unit->GetVictim())
        unit->SetTarget(unit->GetVictim()->GetGUID());

    unit->StopMovingOnCurrentPos();
}

template void ConfusedMovementGenerator<Player>::DoInitialize(Player*);
template void ConfusedMovementGenerator<Creature>::DoInitialize(Creature*);
template void ConfusedMovementGenerator<Player>::DoReset(Player*);
template void ConfusedMovementGenerator<Creature>::DoReset(Creature*);
template bool ConfusedMovementGenerator<Player>::DoUpdate(Player*, uint32 diff);
template bool ConfusedMovementGenerator<Creature>::DoUpdate(Creature*, uint32 diff);
