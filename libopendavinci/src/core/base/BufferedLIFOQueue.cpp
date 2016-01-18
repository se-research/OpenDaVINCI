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

#include "opendavinci/core/base/BufferedLIFOQueue.h"
#include "opendavinci/core/opendavinci.h"

namespace core {
    namespace base {

        using namespace data;
        using namespace exceptions;

        BufferedLIFOQueue::BufferedLIFOQueue(const uint32_t &bufferSize) :
                LIFOQueue(),
                m_bufferSize(bufferSize) {}

        BufferedLIFOQueue::~BufferedLIFOQueue() {}

        void BufferedLIFOQueue::push(const data::Container &container) {
            if (getSize() < m_bufferSize) {
                LIFOQueue::push(container);
            }
        }

        int32_t BufferedLIFOQueue::getIndexOfLastElement() const {
            return (getSize() - 1);
        }

        const Container BufferedLIFOQueue::getElementAt(const uint32_t &index) const throw (ArrayIndexOutOfBoundsException) {
            if (static_cast<int>(index) > getIndexOfLastElement()) {
                OPENDAVINCI_CORE_THROW_EXCEPTION(ArrayIndexOutOfBoundsException, "Given index is invalid.");
            }

            return get(index);
        }

    }
} // core::base
