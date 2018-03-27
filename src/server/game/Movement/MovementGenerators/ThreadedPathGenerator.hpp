#ifndef ThreadedPathGenerator_hpp__
#define ThreadedPathGenerator_hpp__

/*
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
*
* Author:           lukaasm <lukaasm@gmail.com>
* Creation date:    24.02.2018 11:10
*
*/

#include "MoveSplineInitArgs.h"
#include "PathGenerator.h"

#include "Threading/SyncQueue.hpp"

#include <G3D/Vector3.h>
#include <future>
#include <chrono>
#include <vector>

namespace Movement
{
    struct Path
    {
        PathType    type;
        PointsArray points;
    };

    using PathFuture = std::future< Path >;
    using PathPromise = std::promise< Path >;

    struct AsyncPathResult
    {
        AsyncPathResult() = default;

        AsyncPathResult( PathFuture && future );
        AsyncPathResult( AsyncPathResult && rhs );

        AsyncPathResult& operator=( AsyncPathResult && rhs );

        bool            IsValid() const;
        bool            IsReady() const;

        void            Invalidate();

        Path            GetPath();

    protected:
        PathFuture      m_future;
    };

    using PathRequest = std::pair< AsyncPathGeneratorContext, PathPromise >;

    using PathGeneratorPool = std::vector< std::thread >;
    using PathRequestQueue = Threading::SyncQueue< PathRequest >;

    class ThreadedPathGenerator
    {
    public:
        ThreadedPathGenerator();

        void                Initialize( size_t threadsCount );
        void                Shutdown();

        AsyncPathResult     RequestPath( AsyncPathGeneratorContext const& params );

    protected:
        void                PreparePath( PathRequest& request );

        std::atomic_bool    m_shutdown;
        std::atomic_bool    m_initialized;

        PathRequestQueue    m_queue;
        PathGeneratorPool   m_pool;
    };

    ThreadedPathGenerator & GetPathGenerator();
}

#endif // ThreadedPathGenerator_hpp__
