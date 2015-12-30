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

#include "core/base/BufferedFIFOQueue.h"
#include "core/macros.h"

namespace core {
    namespace base {

        using namespace data;
        using namespace exceptions;

        BufferedFIFOQueue::BufferedFIFOQueue(const uint32_t &bufferSize) :
                FIFOQueue(),
                m_bufferSize(bufferSize) {}

        BufferedFIFOQueue::~BufferedFIFOQueue() {}

        void BufferedFIFOQueue::enter(const data::Container &container) {
            if (getSize() < m_bufferSize) {
                FIFOQueue::enter(container);
            }
        }

        int32_t BufferedFIFOQueue::getIndexOfLastElement() const {
            return (getSize() - 1);
        }

        const Container BufferedFIFOQueue::getElementAt(const uint32_t &index) const throw (ArrayIndexOutOfBoundsException) {
            if (static_cast<int>(index) > getIndexOfLastElement()) {
                OPENDAVINCI_CORE_THROW_EXCEPTION(ArrayIndexOutOfBoundsException, "Given index is invalid.");
            }

            return get(index);
        }

        bool BufferedFIFOQueue::isFull() const {
        	return (getSize() >= m_bufferSize - 1);
        }

    }
} // core::base
