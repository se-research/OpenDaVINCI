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

#ifndef CONTEXT_TIMEFACTORYTESTSUITE_H_
#define CONTEXT_TIMEFACTORYTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <iostream>

#include "core/macros.h"
#include "core/SharedPointer.h"
#include "core/data/TimeStamp.h"
#include "core/wrapper/TimeFactory.h"
#include "core/wrapper/Time.h"
#include "context/base/ControlledTime.h"
#include "context/base/ControlledTimeFactory.h"

using namespace std;
using namespace core;
using namespace core::base;
using namespace core::data;
using namespace context::base;

class TimeFactoryTestDisableTimeFactory : public core::wrapper::TimeFactory {
    public:
        void disable() {
            core::wrapper::TimeFactory::setSingleton(NULL);
        }
        SharedPointer<core::wrapper::Time> now() {
            SharedPointer<core::wrapper::Time> t;
            return t;
        }
};

class TimeFactoryTest : public CxxTest::TestSuite {
    public:
        void testCopyControlledTime() {
            ControlledTime t1(1, 2);
            ControlledTime t2(t1);
            ControlledTime t3;
            t3 = t2;

            TS_ASSERT(t1.getSeconds() == t2.getSeconds());
            TS_ASSERT(t1.getPartialMicroseconds() == t2.getPartialMicroseconds());

            TS_ASSERT(t2.getSeconds() == t3.getSeconds());
            TS_ASSERT(t2.getPartialMicroseconds() == t3.getPartialMicroseconds());
        }

        void testControlledTimeFactoryTestSuite() {
            // Initialize the TimeFactory for the very first usage.
            TimeStamp ts0;
            TS_ASSERT(ts0.getSeconds() > 1000);

            // DO NOT Destroy any existing TimeFactory since DisposalService will do that for us. Instead, set singleton to NULL.
            TimeFactoryTestDisableTimeFactory disableTF;
            disableTF.disable();

            // Create regular TimeFactory by simply using TimeStamp.
            TimeStamp ts;
            TS_ASSERT(ts.getSeconds() > 1000);

            // DO NOT Destroy any existing TimeFactory since DisposalService will do that for us. Instead, set singleton to NULL.
            disableTF.disable();

            // Exchange TimeFactory.
            ControlledTimeFactory *controlledTF = new ControlledTimeFactory();
            core::wrapper::TimeFactory &controlledtf = core::wrapper::TimeFactory::getInstance();
            core::wrapper::TimeFactory *tf2 = &controlledtf;
            TS_ASSERT(tf2 == controlledTF);

            // Get TimeStamp;
            TimeStamp ts2;
            TS_ASSERT(ts2.getSeconds() == 0);
            TS_ASSERT(ts2.getFractionalMicroseconds() == 0);
            TS_ASSERT(ts2.toMicroseconds() == 0);

            // Modify global time.
            controlledTF->setTime(ControlledTime(1, 2));

            // Get updated time.
            TimeStamp ts3;
            TS_ASSERT(ts3.getSeconds() == 1);
            TS_ASSERT(ts3.getFractionalMicroseconds() == 2);
            TS_ASSERT(ts3.toMicroseconds() == 1000002);

            // Destroy existing TimeFactory. At this time, controlledTF gets destroyed.
            OPENDAVINCI_CORE_DELETE_POINTER(tf2);

            // DO NOT Destroy any existing TimeFactory since DisposalService will do that for us. Instead, set singleton to NULL.
            disableTF.disable();

            // Check if regular TimeFactory is working again.
            TimeStamp ts4;
            TS_ASSERT(ts4.getSeconds() > 1000);
            TS_ASSERT(!(ts.toMicroseconds() > ts4.toMicroseconds()));
        }
};

#endif /*CONTEXT_TIMEFACTORYTESTSUITE_H_*/
