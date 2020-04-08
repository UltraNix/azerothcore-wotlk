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

#ifndef TRINITY_CONFUSEDGENERATOR_H
#define TRINITY_CONFUSEDGENERATOR_H

#include "MovementGenerator.h"
#include "ThreadedPathGenerator.hpp"
#include "Timer.h"

constexpr int CONFUSED_MOVEMENT_STEP_AMOUNT = 3;

template<class T>
class ConfusedMovementGenerator : public MovementGeneratorMedium< T, ConfusedMovementGenerator<T> >
{
public:
    explicit ConfusedMovementGenerator(float extendedRange = 0.0f) : _extendedRange(extendedRange), _timer(0), _reference(), _interrupt(false), _smallPath(false) { }

    void                        DoInitialize(T*);
    void                        DoFinalize(T*);
    void                        DoReset(T*);
    bool                        DoUpdate(T*, uint32);

    MovementGeneratorType       GetMovementGeneratorType() { return CONFUSED_MOTION_TYPE; }

private:
    void                        InitIsSmallPath(T*);
    void                        SetLocation(T*);
    float                       _extendedRange;
    G3D::Vector3                _reference;
    TimeTracker                 _timer;
    Movement::AsyncPathResult   _pathRequest;
    bool                        _waterOK;
    bool                        _landOK;
    bool                        _interrupt;
    bool                        _smallPath;
};
#endif
