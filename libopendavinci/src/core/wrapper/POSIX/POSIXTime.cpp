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

#include <sys/time.h>

#include "opendavinci/core/wrapper/POSIX/POSIXTime.h"

namespace core {
    namespace wrapper {
        namespace POSIX {

            POSIXTime::POSIXTime() :
                m_seconds(0),
                m_partialMicroseconds(0) {
                struct timeval t;
                gettimeofday(&t, NULL);
                m_seconds = t.tv_sec;
                m_partialMicroseconds = t.tv_usec;
            }

            POSIXTime::~POSIXTime() {}

            int32_t POSIXTime::getSeconds() const {
                return m_seconds;
            }

            int32_t POSIXTime::getPartialMicroseconds() const {
                return m_partialMicroseconds;
            }

        }
    }
} // core::wrapper::POSIX
