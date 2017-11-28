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

#ifndef TRINITY_CONTAINERS_H
#define TRINITY_CONTAINERS_H

#include "Define.h"
#include <list>

//! Because circular includes are bad
extern uint32 urand(uint32 min, uint32 max);

namespace Trinity
{
    namespace Containers
    {
        // replace with std::size in C++17
        template<class C>
        constexpr inline std::size_t Size(C const& container)
        {
            return container.size();
        }

        template<class T, std::size_t size>
        constexpr inline std::size_t Size(T const(&)[size]) noexcept
        {
            return size;
        }

        // resizes <container> to have at most <requestedSize> elements
        // if it has more than <requestedSize> elements, the elements to keep are selected randomly
        template<class C>
        void RandomResize(C& container, std::size_t requestedSize)
        {
            static_assert(std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<typename C::iterator>::iterator_category>::value, "Invalid container passed to Trinity::Containers::RandomResize");
            if (Size(container) <= requestedSize)
                return;
            auto keepIt = std::begin(container), curIt = std::begin(container);
            uint32 elementsToKeep = requestedSize, elementsToProcess = Size(container);
            while (elementsToProcess)
            {
                // this element has chance (elementsToKeep / elementsToProcess) of being kept
                if (urand(1, elementsToProcess) <= elementsToKeep)
                {
                    *keepIt = std::move(*curIt);
                    ++keepIt;
                    --elementsToKeep;
                }
                ++curIt;
                --elementsToProcess;
            }
            container.erase(keepIt, std::end(container));
        }

        template<class C, class Predicate>
        void RandomResize(C& container, Predicate&& predicate, std::size_t requestedSize)
        {
            //! First use predicate filter
            C containerCopy;
            std::copy_if(std::begin(container), std::end(container), std::inserter(containerCopy, std::end(containerCopy)), predicate);

            if (requestedSize)
                RandomResize(containerCopy, requestedSize);

            container = std::move(containerCopy);
        }

        /*
        * Select a random element from a container.
        *
        * Note: container cannot be empty
        */
        template<class C>
        inline auto SelectRandomContainerElement(C const& container) -> typename std::add_const<decltype(*std::begin(container))>::type&
        {
            auto it = std::begin(container);
            std::advance(it, urand(0, uint32(Size(container)) - 1));
            return *it;
        }
    }
    //! namespace Containers
}
//! namespace Trinity

#endif //! #ifdef TRINITY_CONTAINERS_H
