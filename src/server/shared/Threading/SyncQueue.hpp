#ifndef SyncQueue_hpp__
#define SyncQueue_hpp__

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
* Creation date:    24.02.2018 11:11
*
*/

#include <mutex>
#include <deque>
#include <condition_variable>

namespace Threading
{
    template <typename T >
    class SyncQueue
    {
    public:
        bool empty() const
        {
            std::unique_lock<std::mutex> lock( m_mutex );
            return m_queue.empty();
        }

        T pop()
        {
            std::unique_lock<std::mutex> lock( m_mutex );
            while ( m_queue.empty() )
            {
                m_condition.wait( lock );
            }

            auto item = std::move( m_queue.front() );
            m_queue.pop_front();

            return item;
        }

        void push( T&& item )
        {
            std::unique_lock<std::mutex> lock( m_mutex );

            m_queue.push_back( std::move( item ) );

            //! unlock before notifying threads
            lock.unlock();

            m_condition.notify_one();
        }

        void push( T const& item )
        {
            std::unique_lock<std::mutex> lock( m_mutex );

            m_queue.push_back( item );

            //! unlock before notifying threads
            lock.unlock();

            m_condition.notify_one();
        }

    protected:
        std::deque< T >         m_queue;
        std::mutex              m_mutex;
        std::condition_variable m_condition;
    };
}

#endif // SyncQueue_hpp__
