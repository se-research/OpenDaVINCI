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

#ifndef CONTEXT_BASE_CLOCK_H_
#define CONTEXT_BASE_CLOCK_H_

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/context/base/ControlledTime.h"

namespace odcontext {
    namespace base {

        /**
         * This class provides a clock.
         */
        class OPENDAVINCI_API Clock {
            public:
                Clock();

                /**
                 * Constructor.
                 *
                 * @param s Seconds.
                 * @param ps Partial microseconds.
                 */
                Clock(const uint32_t &s, const uint32_t &ps);

                /**
                 * Copy constructor.
                 *
                 * @param obj Object from same type.
                 */
                Clock(const Clock &obj);

                virtual ~Clock();

                /**
                 * Assignment operator.
                 *
                 * @param obj Object from same type.
                 * @return (*this).
                 */
                Clock& operator=(const Clock &obj);

                /**
                 * This method returns the actual time.
                 *
                 * @return Actual time.
                 */
                const ControlledTime now() const;

                /**
                 * This method increments the clock for
                 * the given amount of milliseconds.
                 *
                 * @param ms.
                 */
                void increment(const uint32_t &ms);

            private:
                ControlledTime m_theTime;
        };

    }
} // odcontext::base

#endif /*CONTEXT_BASE_CLOCK_H_*/
