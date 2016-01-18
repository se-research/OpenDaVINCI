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

#ifndef CONTEXT_CLOCKTESTSUITE_H_
#define CONTEXT_CLOCKTESTSUITE_H_

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/context/base/Clock.h"         // for Clock
#include "opendavinci/context/base/ControlledTime.h"  // for ControlledTime

using namespace std;
using namespace context::base;

class ClockTest : public CxxTest::TestSuite {
    public:
        void testClock() {
            Clock clock;

            ControlledTime time = clock.now();

            TS_ASSERT(time.getSeconds() == 0);
            TS_ASSERT(time.getPartialMicroseconds() == 0);

            // Add 1 ms.
            clock.increment(1);

            time = clock.now();
            TS_ASSERT(time.getSeconds() == 0);
            TS_ASSERT(time.getPartialMicroseconds() == 1000);

            // Add 1 ms.
            clock.increment(1);

            time = clock.now();
            TS_ASSERT(time.getSeconds() == 0);
            TS_ASSERT(time.getPartialMicroseconds() == 2000);

            // Add 997 ms.
            clock.increment(997);

            time = clock.now();
            TS_ASSERT(time.getSeconds() == 0);
            TS_ASSERT(time.getPartialMicroseconds() == 999000);

            // Add 1 ms.
            clock.increment(1);

            time = clock.now();
            TS_ASSERT(time.getSeconds() == 1);
            TS_ASSERT(time.getPartialMicroseconds() == 0);

            // Add 2500 ms.
            clock.increment(2500);

            time = clock.now();
            TS_ASSERT(time.getSeconds() == 3);
            TS_ASSERT(time.getPartialMicroseconds() == 500000);
        }

        void testCopyClock() {
            Clock clock1;
            clock1.increment(12300);

            Clock clock2(clock1);
            Clock clock3 = clock2;

            TS_ASSERT(clock1.now().getSeconds() == clock2.now().getSeconds());
            TS_ASSERT(clock1.now().getPartialMicroseconds() == clock2.now().getPartialMicroseconds());

            TS_ASSERT(clock3.now().getSeconds() == clock2.now().getSeconds());
            TS_ASSERT(clock3.now().getPartialMicroseconds() == clock2.now().getPartialMicroseconds());
        }
};

#endif /*CONTEXT_CLOCKTESTSUITE_H_*/
