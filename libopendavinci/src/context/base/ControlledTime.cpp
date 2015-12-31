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

#include "context/base/ControlledTime.h"

namespace context {
    namespace base {

        ControlledTime::ControlledTime() :
            Time(),
            m_seconds(0),
            m_partialMicroseconds(0) {}

        ControlledTime::ControlledTime(const uint32_t &s, const uint32_t &ps) :
            Time(),
            m_seconds(s),
            m_partialMicroseconds(ps) {}

        ControlledTime::ControlledTime(const ControlledTime &ct) :
            Time(ct),
            m_seconds(ct.getSeconds()),
            m_partialMicroseconds(ct.getPartialMicroseconds()) {}

        ControlledTime::~ControlledTime() {}

        ControlledTime& ControlledTime::operator=(const ControlledTime &ct) {
            setSeconds(ct.getSeconds());
            setPartialMicroseconds(ct.getPartialMicroseconds());

            return (*this);
        }

        int32_t ControlledTime::getSeconds() const {
            return m_seconds;
        }

        int32_t ControlledTime::getPartialMicroseconds() const {
            return m_partialMicroseconds;
        }

        void ControlledTime::setSeconds(const int32_t &s) {
            m_seconds = s;
        }

        void ControlledTime::setPartialMicroseconds(const int32_t &partialMS) {
            m_partialMicroseconds = partialMS;
        }

    }
} // context::base
