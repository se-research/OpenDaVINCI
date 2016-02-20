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

#include "opendavinci/odcontext/base/Clock.h"

namespace odcontext {
    namespace base {

        Clock::Clock() :
            m_theTime() {}

        Clock::Clock(const uint32_t &s, const uint32_t &ps) :
            m_theTime(s, ps) {}

        Clock::Clock(const Clock &obj) :
            m_theTime(obj.now()) {}

        Clock::~Clock() {}

        Clock& Clock::operator=(const Clock &obj) {
            m_theTime = obj.now();

            return (*this);
        }

        const ControlledTime Clock::now() const {
            return m_theTime;
        }

        void Clock::increment(const uint32_t &ms) {
            uint32_t newMicroseconds = m_theTime.getPartialMicroseconds() + ms*1000;
            uint32_t additionalSeconds = 0;
            const uint32_t ONESECONDINMICROSECONDS = 1 * 1000 * 1000;
            while (newMicroseconds >= ONESECONDINMICROSECONDS) {
                additionalSeconds++;
                newMicroseconds -= ONESECONDINMICROSECONDS;
            }

            m_theTime.setPartialMicroseconds(newMicroseconds);
            m_theTime.setSeconds(m_theTime.getSeconds() + additionalSeconds);
        }

    }
} // odcontext::base
