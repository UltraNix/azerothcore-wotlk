#ifndef SyncQueue_hpp__
#define SyncQueue_hpp__

#include "Utilities/Optional.h"

#include <mutex>
#include <deque>
#include <condition_variable>

namespace Threading
{
    template <typename T >
    class SyncQueue
    {
    public:
        SyncQueue()
        {
            m_closed = false;
        }

        ~SyncQueue()
        {
            close();
        }

        void close()
        {
            m_closed = true;
            m_condition.notify_all();
        }

        bool is_closed() const
        {
            return m_closed;
        }

        bool empty() const
        {
            std::unique_lock<std::mutex> lock( m_mutex );
            return m_queue.empty();
        }

        Optional<T> pop()
        {
            std::unique_lock<std::mutex> lock( m_mutex );
            while ( m_queue.empty() && !m_closed )
            {
                m_condition.wait( lock );
            }

            if ( m_closed )
                return {};

            auto item = std::move( m_queue.front() );
            m_queue.pop_front();

            return item;
        }

        template< typename ...Args >
        void emplace( Args && ... args )
        {
            std::unique_lock<std::mutex> lock( m_mutex );
            m_queue.emplace_back( std::forward< Args >( args )... );

            m_condition.notify_one();
        }

        void push( T&& item )
        {
            std::unique_lock<std::mutex> lock( m_mutex );
            m_queue.push_back( std::move( item ) );

            m_condition.notify_one();
        }

        void push( T const& item )
        {
            std::unique_lock<std::mutex> lock( m_mutex );
            m_queue.push_back( item );

            m_condition.notify_one();
        }

    protected:
        std::deque< T >         m_queue;
        std::mutex              m_mutex;
        std::condition_variable m_condition;
        std::atomic_bool        m_closed;
    };
}

#endif // SyncQueue_hpp__
