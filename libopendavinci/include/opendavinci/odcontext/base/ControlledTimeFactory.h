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

#ifndef CONTEXT_BASE_CONTROLLEDTIMEFACTORY_H_
#define CONTEXT_BASE_CONTROLLEDTIMEFACTORY_H_

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/wrapper/TimeFactory.h"
#include "opendavinci/odcontext/base/ControlledTime.h"

namespace odcore { namespace wrapper { class Time; } }

namespace odcontext {
    namespace base {

        using namespace std;

        /**
         * This class provides controlled time factory.
         */
        class OPENDAVINCI_API ControlledTimeFactory : public odcore::wrapper::TimeFactory {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ControlledTimeFactory(const ControlledTimeFactory &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ControlledTimeFactory& operator=(const ControlledTimeFactory &);

            public:
                ControlledTimeFactory();

                virtual ~ControlledTimeFactory();

                virtual std::shared_ptr<odcore::wrapper::Time> now();

                /**
                 * This method sets the time.
                 *
                 * @param t Time.
                 */
                void setTime(const ControlledTime &ct);

            private:
                odcore::base::Mutex m_timeMutex;
                ControlledTime m_time;
        };

    }
} // odcontext::base

#endif /*CONTEXT_BASE_CONTROLLEDTIMEFACTORY_H_*/
