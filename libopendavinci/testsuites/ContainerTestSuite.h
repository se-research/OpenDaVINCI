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

#include <sstream>                      // for stringstream, etc
#include <string>                       // for operator==, basic_string

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/serialization/Serializable.h"     // for operator<<, operator>>
#include "opendavinci/odcore/data/Container.h"        // for Container, etc
#include "opendavinci/odcore/data/TimeStamp.h"        // for TimeStamp
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcore/io/conference/ContainerListenerFork.h"

using namespace std;
using namespace odcore::data;
using namespace odcore::io::conference;

class MyContainerListener : public ContainerListener {
    public:
        MyContainerListener() :
            m_hasReceived(false),
            m_container() {}

        virtual void nextContainer(Container &c) {
            m_hasReceived = true;
            m_container = c;
        }

    public:
        bool m_hasReceived;
        Container m_container;
};

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

            if (c2.getDataType() == 1234) {
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

        void testTimeStamps() {
            TimeStamp ts(9, 10);
            Container c1(ts);
            c1.setSentTimeStamp(TimeStamp(1, 2));
            c1.setReceivedTimeStamp(TimeStamp(3, 4));
            c1.setSampleTimeStamp(TimeStamp(5, 6));

            stringstream s;
            s << c1;
            s.flush();

            Container c2;
            s >> c2;
            TS_ASSERT(c2.getDataType() == ts.getID());

            TimeStamp ts2;
            ts2 = c2.getData<TimeStamp>();

            TS_ASSERT(ts.toString() == ts2.toString());

            TS_ASSERT(c2.getSentTimeStamp().toString() == c1.getSentTimeStamp().toString());
            TS_ASSERT(c2.getReceivedTimeStamp().toString() == c1.getReceivedTimeStamp().toString());
            TS_ASSERT(c2.getSampleTimeStamp().toString() == c1.getSampleTimeStamp().toString());
        }

        void testContainerListenerFork() {
            ContainerListenerFork clf;

            MyContainerListener listener1;
            MyContainerListener listener2;
            MyContainerListener listener3;

            TS_ASSERT(!listener1.m_hasReceived);
            TS_ASSERT(!listener2.m_hasReceived);

            clf.addContainerListener(&listener1);
            TS_ASSERT(!listener1.m_hasReceived);
            TS_ASSERT(!listener3.m_hasReceived);

            clf.addContainerListener(&listener2);
            TS_ASSERT(!listener1.m_hasReceived);
            TS_ASSERT(!listener2.m_hasReceived);
            TS_ASSERT(!listener3.m_hasReceived);

            TimeStamp ts(123, 456);
            Container c(ts);
            clf.nextContainer(c);

            TS_ASSERT(listener1.m_hasReceived);
            TS_ASSERT(listener2.m_hasReceived);
            TS_ASSERT(!listener3.m_hasReceived);

            TS_ASSERT(listener1.m_container.getDataType() == ts.ID());
            TS_ASSERT(listener1.m_container.getData<TimeStamp>().toMicroseconds() == ts.toMicroseconds());

            TS_ASSERT(listener2.m_container.getDataType() == ts.ID());
            TS_ASSERT(listener2.m_container.getData<TimeStamp>().toMicroseconds() == ts.toMicroseconds());

            clf.removeContainerListener(&listener3);

            listener1.m_hasReceived = false;
            listener2.m_hasReceived = false;
            TS_ASSERT(!listener1.m_hasReceived);
            TS_ASSERT(!listener2.m_hasReceived);

            TimeStamp ts2(234, 567);
            Container c2(ts2);
            clf.nextContainer(c2);

            TS_ASSERT(listener1.m_hasReceived);
            TS_ASSERT(listener2.m_hasReceived);
            TS_ASSERT(!listener3.m_hasReceived);

            TS_ASSERT(listener1.m_container.getDataType() == ts2.ID());
            TS_ASSERT(listener1.m_container.getData<TimeStamp>().toMicroseconds() == ts2.toMicroseconds());

            TS_ASSERT(listener2.m_container.getDataType() == ts2.ID());
            TS_ASSERT(listener2.m_container.getData<TimeStamp>().toMicroseconds() == ts2.toMicroseconds());

            clf.removeContainerListener(&listener1);

            listener1.m_hasReceived = false;
            listener2.m_hasReceived = false;
            TS_ASSERT(!listener1.m_hasReceived);
            TS_ASSERT(!listener2.m_hasReceived);

            TimeStamp ts3(345, 678);
            Container c3(ts3);
            clf.nextContainer(c3);

            TS_ASSERT(!listener1.m_hasReceived);
            TS_ASSERT(listener2.m_hasReceived);
            TS_ASSERT(!listener3.m_hasReceived);

            TS_ASSERT(listener2.m_container.getDataType() == ts3.ID());
            TS_ASSERT(listener2.m_container.getData<TimeStamp>().toMicroseconds() == ts3.toMicroseconds());
        }
};

#endif /*CORE_CONTAINERTESTSUITE_H_*/
