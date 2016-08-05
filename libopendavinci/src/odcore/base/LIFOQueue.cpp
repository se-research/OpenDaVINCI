/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/LIFOQueue.h"

namespace odcore {
    namespace base {

        using namespace data;

        LIFOQueue::LIFOQueue() :
                m_mutexQueue(),
                m_queue() {}

        LIFOQueue::~LIFOQueue() {
            wakeAll();
        }

        void LIFOQueue::clear() {
            {
                Lock l(m_mutexQueue);
                m_queue.clear();
            }

            wakeAll();
        }

        void LIFOQueue::push(const Container &container) {
            {
                Lock l(m_mutexQueue);
                m_queue.push_front(container);
            }

            wakeAll();
        }

        const Container LIFOQueue::pop() {
            waitForData();

            Container container;
            if (!isEmpty()) {
                Lock l(m_mutexQueue);
                container = m_queue.front();
                m_queue.pop_front();
            }

            return container;
        }

        const Container LIFOQueue::get(const uint32_t &index) const {
            Container container;

            if (!isEmpty()) {
                if (index < getSize()) {
                    Lock l(m_mutexQueue);
                    container = m_queue[index];
                }
            }

            return container;
        }

        void LIFOQueue::add(Container &container) {
            push(container);
        }

        uint32_t LIFOQueue::getSize() const {
            Lock l(m_mutexQueue);
            return static_cast<uint32_t>(m_queue.size());
        }

        bool LIFOQueue::isEmpty() const {
            Lock l(m_mutexQueue);
            return m_queue.empty();
        }

    }
} // odcore::base
