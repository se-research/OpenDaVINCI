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

#include <opendavinci/odcore/data/TimeStamp.h>
#include <opendavinci/odcore/base/Thread.h>
#include "automotivedata/generated/automotive/GenericCANMessage.h"

// Include local header files.
#include "../include/PCANDevice.h"
#include "../include/SocketCANDevice.h"
#include "../include/GenericCANMessageListener.h"

using namespace std;
using namespace odcore::base;
using namespace odcore::data;
using namespace automotive;
using namespace automotive::odcantools;

/**
 * The actual testsuite starts here.
 */
class CANToolsTest : public CxxTest::TestSuite, public GenericCANMessageListener {
    public:
        virtual void nextGenericCANMessage(const GenericCANMessage &gcm) {
            cout << gcm.toString() << ", " << gcm.getDriverTimeStamp().getYYYYMMDD_HHMMSSms() << endl;
        }

        void testCase1() {
            TS_ASSERT(1 != 0);
        }

        void NO_testSocketCAN() {
            // To use this test case on Linux, run:
            //
            // sudo apt-get install --no-install-recommends can-utils
            // sudo modprobe can
            // sudo modprobe vcan
            // sudo ip link add type vcan
            // sudo ip link add dev vcan42 type vcan
            // sudo ip -details -statistics link show vcan42
            //
            // Send test data: cansend vcan42 5A1#11.2233.44556677.88
            // Receive test using cansniffer: cansniffer vcan42

            const string DEV_NODE = "vcan42";
            SocketCANDevice scan(DEV_NODE, *this);
            cout << endl;
            cout << "Starting CAN receive..." << endl;
            scan.start();
            Thread::usleepFor(10 * 1000 * 1000);

            cout << "Sending CAN data..." << endl;
            Thread::usleepFor(1 * 1000 * 1000);
            GenericCANMessage gcm;
            gcm.setIdentifier(123);
            gcm.setLength(2);
            gcm.setData(0xABCD);
            scan.write(gcm);

            cout << "Stopping CAN receive..." << endl;
            scan.stop();
        }

        // This is just for testing purposes.
        void NO_testCase1() {
            TimeStamp ts(1476343200, 705547);
            cout << endl;
            cout << ts.toString() << endl;
            cout << ts.getYYYYMMDD_HHMMSSms() << endl;
            const string DEV_NODE = "/dev/pcan32";
            PCANDevice dev(DEV_NODE, *this);
            cout << endl;
            cout << "Starting CAN receive..." << endl;
            dev.start();
            Thread::usleepFor(5 * 1000);
            cout << "Stopping CAN receive..." << endl;
            dev.stop();
        }
};

#endif /*CANTOOLSTESTSUITE_H_*/

