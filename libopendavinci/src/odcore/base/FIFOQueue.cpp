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

#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/base/FIFOQueue.h"

namespace core {
    namespace base {

        using namespace data;

        FIFOQueue::FIFOQueue() :
                m_mutexQueue(),
                m_queue() {}

        FIFOQueue::~FIFOQueue() {
            wakeAll();
        }

        void FIFOQueue::clear() {
            {
                Lock l(m_mutexQueue);
                m_queue.clear();
            }
            wakeAll();
        }

        void FIFOQueue::enter(const Container &container) {
            {
                Lock l(m_mutexQueue);
                m_queue.push_back(container);
            }
            wakeAll();
        }

        const Container FIFOQueue::leave() {
            waitForData();

            Container container;
            if (!isEmpty()) {
                Lock l(m_mutexQueue);
                container = m_queue.front();
                m_queue.pop_front();
            }

            return container;
        }

        const Container FIFOQueue::get(const uint32_t &index) const {
            Container container;

            if (!isEmpty()) {
                if (index < getSize()) {
                    Lock l(m_mutexQueue);
                    container = m_queue[index];
                }
            }

            return container;
        }

        void FIFOQueue::add(const Container &container) {
            enter(container);
        }

        uint32_t FIFOQueue::getSize() const {
            Lock l(m_mutexQueue);
            return static_cast<uint32_t>(m_queue.size());
        }

        bool FIFOQueue::isEmpty() const {
            Lock l(m_mutexQueue);
            return m_queue.empty();
        }
    }
} // core::base
