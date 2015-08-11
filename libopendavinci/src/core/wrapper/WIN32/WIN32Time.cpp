/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

// Using c++11 standard.
#include <chrono>

#include "core/wrapper/WIN32/WIN32Time.h"

namespace core {
    namespace wrapper {
        namespace WIN32Impl {

            WIN32Time::WIN32Time() :
                m_seconds(0),
                m_partialMicroseconds(0) {
                std::chrono::time_point<std::chrono::system_clock> t(std::chrono::system_clock::now());
                auto duration = t.time_since_epoch();

                typedef std::chrono::duration<int32_t> seconds_type;
				typedef std::chrono::duration<int64_t, std::micro> microseconds_type;

                seconds_type s = std::chrono::duration_cast<seconds_type>(duration);
                microseconds_type us = std::chrono::duration_cast<microseconds_type>(duration);

                microseconds_type partial_us = us - std::chrono::duration_cast<microseconds_type>(s); // The seconds are converted to microseconds and subtracted from the microseconds representation of duration. Thus, we end up with the same behavior as gettimeofday.

                // The following calculations ensure identical behavior to the gettimeofday call.
                m_seconds = s.count();
                m_partialMicroseconds = partial_us.count();
            }

            WIN32Time::~WIN32Time() {}

            int32_t WIN32Time::getSeconds() const {
                return m_seconds;
            }

            int32_t WIN32Time::getPartialMicroseconds() const {
                return m_partialMicroseconds;
            }

        }
    }
} // core::wrapper::WIN32Impl
