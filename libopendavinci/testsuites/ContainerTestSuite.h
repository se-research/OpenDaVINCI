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

#ifndef CORE_CONTAINERTESTSUITE_H_
#define CORE_CONTAINERTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <sstream>

#include "core/data/Container.h"
#include "core/data/TimeStamp.h"

using namespace std;
using namespace core::data;

class ContainerTest : public CxxTest::TestSuite {
    public:
        void testTimeStampData() {
            TimeStamp ts(1, -2);

            stringstream s;
            s << ts;
            s.flush();

            TimeStamp ts2;
            s >> ts2;

            TS_ASSERT(ts.toString() == ts2.toString());
        }

        void testContainerData() {
            TimeStamp ts(12345, -3000);
            Container c(ts);

            stringstream s;
            s << c;
            s.flush();

            Container c2;
            s >> c2;
            TimeStamp ts2;
            ts2 = c2.getData<TimeStamp>();

            TS_ASSERT(ts.toString() == ts2.toString());
        }

        void testContainerDataUserType() {
            TimeStamp ts;
            Container c(ts, 1234);

            stringstream s;
            s << c;
            s.flush();

            Container c2;
            s >> c2;
            TS_ASSERT(c2.getDataType() == 1234);

            if (c2.getDataType() == Container::USER_DATA_9) {
                TimeStamp ts2;
                ts2 = c2.getData<TimeStamp>();

                TS_ASSERT(ts.toString() == ts2.toString());
            }
        }

        void testSimpleContainerConstructor() {
            TimeStamp ts(1, 2);
            Container c(ts);

            stringstream s;
            s << c;
            s.flush();

            Container c2;
            s >> c2;
            TS_ASSERT(c2.getDataType() == ts.getID());

            TimeStamp ts2;
            ts2 = c2.getData<TimeStamp>();

            TS_ASSERT(ts.toString() == ts2.toString());
        }

        void testInt32ContainerConstructor() {
            TimeStamp ts(3, 4);
            Container c(ts, ts.getID());

            stringstream s;
            s << c;
            s.flush();

            Container c2;
            s >> c2;
            TS_ASSERT(c2.getDataType() == ts.getID());

            TimeStamp ts2;
            ts2 = c2.getData<TimeStamp>();

            TS_ASSERT(ts.toString() == ts2.toString());
        }
};

#endif /*CORE_CONTAINERTESTSUITE_H_*/
