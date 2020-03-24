#ifndef ThreadedPathGenerator_hpp__
#define ThreadedPathGenerator_hpp__

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

        float       GetPathLength()
        {
            float length = 0.0f;
            for ( auto idx = 1; idx < points.size(); ++idx )
            {
                length += ( points[ idx ] - points[ idx - 1 ] ).length();
            }

            return length;
        }
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
