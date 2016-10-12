/**
 * libodcantools - Library to wrap a CAN interface.
 * Copyright (C) 2015 Christian Berger
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

#ifndef CANTOOLSTESTSUITE_H_
#define CANTOOLSTESTSUITE_H_

#include <string>

#include "cxxtest/TestSuite.h"

#include <opendavinci/odcore/base/Thread.h>
#include "automotivedata/generated/automotive/GenericCANMessage.h"

// Include local header files.
#include "../include/CANDevice.h"
#include "../include/GenericCANMessageListener.h"

using namespace std;
using namespace odcore::base;
using namespace automotive;
using namespace automotive::odcantools;

/**
 * The actual testsuite starts here.
 */
class CANToolsTest : public CxxTest::TestSuite, public GenericCANMessageListener {
    public:
        virtual void nextGenericCANMessage(const GenericCANMessage &gcm) {
            cout << gcm.toString() << endl;
        }

        void testCase1() {
            const string DEV_NODE = "/dev/pcan0";
            CANDevice dev(DEV_NODE, *this);
            cout << endl;
            cout << "Starting CAN receive..." << endl;
            dev.start();
            Thread::usleepFor(5 * 1000 * 1000);
            dev.stop();
            cout << "Stopping CAN receive..." << endl;
        }
};

#endif /*CANTOOLSTESTSUITE_H_*/

