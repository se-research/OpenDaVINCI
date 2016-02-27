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

#include "opendavinci/odcontext/base/ControlledTimeFactory.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/wrapper/Time.h"

namespace odcontext {
    namespace base {

        using namespace odcore::base;

        ControlledTimeFactory::ControlledTimeFactory() :
            m_timeMutex(),
            m_time() {
            odcore::wrapper::TimeFactory::setSingleton(this);
        }

        ControlledTimeFactory::~ControlledTimeFactory() {}

        std::shared_ptr<odcore::wrapper::Time> ControlledTimeFactory::now() {
            std::shared_ptr<odcore::wrapper::Time> t;
            {
                Lock l(m_timeMutex);
                t = std::shared_ptr<odcore::wrapper::Time>(new ControlledTime(m_time));
            }
            return t;
        }

        void ControlledTimeFactory::setTime(const ControlledTime &ct) {
            Lock l(m_timeMutex);
            m_time.setSeconds(ct.getSeconds());
            m_time.setPartialMicroseconds(ct.getPartialMicroseconds());
        }

    }
} // odcontext::base
