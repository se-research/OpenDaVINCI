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

#include "context/base/ControlledTimeFactory.h"
#include "core/base/Lock.h"
#include "core/wrapper/Time.h"

namespace context {
    namespace base {

        using namespace core::base;

        ControlledTimeFactory::ControlledTimeFactory() :
            m_timeMutex(),
            m_time() {
            core::wrapper::TimeFactory::setSingleton(this);
        }

        ControlledTimeFactory::~ControlledTimeFactory() {}

        core::SharedPointer<core::wrapper::Time> ControlledTimeFactory::now() {
            core::SharedPointer<core::wrapper::Time> t;
            {
                Lock l(m_timeMutex);
                t = core::SharedPointer<core::wrapper::Time>(new ControlledTime(m_time));
            }
            return t;
        }

        void ControlledTimeFactory::setTime(const ControlledTime &ct) {
            Lock l(m_timeMutex);
            m_time.setSeconds(ct.getSeconds());
            m_time.setPartialMicroseconds(ct.getPartialMicroseconds());
        }

    }
} // context::base
