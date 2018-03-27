#include "ThreadedPathGenerator.hpp"

#include "PathGenerator.h"

namespace Movement
{
    ThreadedPathGenerator::ThreadedPathGenerator()
        : m_shutdown( false )
        , m_initialized( false )
    {
    }

    void ThreadedPathGenerator::Initialize( size_t threadsCount )
    {
        m_pool.reserve( threadsCount );

        for ( size_t idx = 0u; idx < threadsCount; ++idx )
        {
            m_pool.push_back( std::thread( [this]
            {
                while ( !m_shutdown )
                {
                    auto request = m_queue.pop();
                    PreparePath( request );
                }
            } ) );
        }
    }

    void ThreadedPathGenerator::Shutdown()
    {
        m_shutdown = true;
    }

    AsyncPathResult ThreadedPathGenerator::RequestPath( AsyncPathGeneratorContext const& params )
    {
        PathPromise promise;

        AsyncPathResult result( promise.get_future() );
        m_queue.push( { params, std::move( promise ) } );

        return result;
    }

    void ThreadedPathGenerator::PreparePath( PathRequest& request )
    {
        AsyncPathGeneratorContext const& params = request.first;

        PathGenerator generator( &params );

        auto & dest = params.GetEndPosition();
        if ( generator.CalculatePath( dest.x, dest.y, dest.z, params.IsForcingShortcut() ) )
        {
            auto pathType = generator.GetPathType();
            request.second.set_value( { pathType, std::move( generator.StealPath() ) } );
        }
        else
        {
            request.second.set_value( { PATHFIND_NOPATH, PointsArray() } );
        }
    }

    Movement::AsyncPathResult& AsyncPathResult::operator=( AsyncPathResult && rhs )
    {
        m_future = std::move( rhs.m_future );
        return *this;
    }

    AsyncPathResult::AsyncPathResult( AsyncPathResult && rhs )
        : m_future( std::move( rhs.m_future ) )
    {

    }

    AsyncPathResult::AsyncPathResult( PathFuture && future )
        : m_future( std::move( future ) )
    {

    }

    bool AsyncPathResult::IsValid() const
    {
        return m_future.valid();
    }

    bool AsyncPathResult::IsReady() const
    {
        return IsValid() && m_future.wait_for( std::chrono::nanoseconds( 0 ) ) == std::future_status::ready;
    }


    void AsyncPathResult::Invalidate()
    {
        if ( !IsValid() )
            return;

        PathPromise promise;
        m_future = promise.get_future();

        promise.set_value( { PATHFIND_NOPATH, PointsArray() } );
        m_future.get();
    }

    Path AsyncPathResult::GetPath()
    {
        return std::move( m_future.get() );
    }

    ThreadedPathGenerator & GetPathGenerator()
    {
        static ThreadedPathGenerator s_generator;
        return s_generator;
    }
}
