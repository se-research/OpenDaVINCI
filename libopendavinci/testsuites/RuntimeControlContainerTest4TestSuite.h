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

#ifndef CONTEXT_RUNTIMECONTROLCONTAINERTESTSUITE_H_
#define CONTEXT_RUNTIMECONTROLCONTAINERTESTSUITE_H_

#include <cmath>                        // for sqrt
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <string>                       // for string, operator<<, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/context/base/DirectInterface.h"  // for DirectInterface
#include "opendavinci/context/base/RuntimeControl.h"  // for RuntimeControl, etc
#include "opendavinci/context/base/RuntimeEnvironment.h"  // for RuntimeEnvironment
#include "opendavinci/context/base/SendContainerToSystemsUnderTest.h"
#include "opendavinci/context/base/SystemFeedbackComponent.h"
#include "opendavinci/core/SharedPointer.h"         // for SharedPointer
#include "opendavinci/core/base/Deserializer.h"     // for Deserializer
#include "opendavinci/core/base/FIFOQueue.h"        // for FIFOQueue
#include "opendavinci/core/base/Hash.h"             // for CharList, CRC32, etc
#include "opendavinci/core/base/KeyValueConfiguration.h"  // for KeyValueConfiguration
#include "opendavinci/core/base/Thread.h"
#include "opendavinci/core/base/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/core/base/Serializer.h"       // for Serializer
#include "opendavinci/core/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/core/data/Container.h"        // for Container, etc
#include "opendavinci/core/data/SerializableData.h"  // for SerializableData
#include "opendavinci/core/data/TimeStamp.h"        // for TimeStamp
#include "opendavinci/generated/coredata/dmcp/ModuleExitCodeMessage.h"

namespace core { namespace wrapper { class Time; } }

using namespace std;
using namespace core::base;
using namespace core::base::module;
using namespace core::data;
using namespace odcontext::base;

class LocalPoint3 : public core::data::SerializableData {
    private:
        double m_x;
        double m_y;
        double m_z;
    public:
        LocalPoint3() :
            m_x(0),
            m_y(0),
            m_z(0) {}

        LocalPoint3(const double &x, const double &y, const double &z) :
            m_x(x),
            m_y(y),
            m_z(z) {}

        LocalPoint3(const LocalPoint3 &o) :
            SerializableData(),
            m_x(o.m_x),
            m_y(o.m_y),
            m_z(o.m_z) {}

        LocalPoint3& operator=(const LocalPoint3 &o) {
            m_x = o.m_x;
            m_y = o.m_y;
            m_z = o.m_z;
            return *this;
        }

        LocalPoint3 operator-(const LocalPoint3 &other) const {
            LocalPoint3 cc(m_x - other.m_x,
                           m_y - other.m_y,
                           m_z - other.m_z);
            return cc;
        }

        LocalPoint3& operator-=(const LocalPoint3 &other) {
            m_x -= other.m_x;
            m_y -= other.m_y;
            m_z -= other.m_z;
            return (*this);
        }

        double operator*(const LocalPoint3 &other) const {
            return m_x*other.m_x + m_y*other.m_y + m_z*other.m_z;
        }

        double length() const {
            return sqrt(operator*((*this)));
        }


        const string toString() const {
            return "";
        }

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();;

            core::SharedPointer<Serializer> s = sf.getSerializer(out);

            stringstream rawData;
            rawData.precision(10);

            rawData << m_x << endl << m_y << endl << m_z;

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                    rawData.str());

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();;

            core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

            string data;
            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                   data);

            stringstream rawData;
            rawData.precision(10);
            rawData.str(data);

            rawData >> m_x >> m_y >> m_z;

            return in;
        }
};

class LocalPosition : public core::data::SerializableData {
    private:
        LocalPoint3 m_position;
    public:
        LocalPosition() :
            m_position() {}

        LocalPosition(const LocalPosition &o) :
            SerializableData(),
            m_position(o.m_position) {}

        LocalPosition& operator=(const LocalPosition &o) {
            m_position = o.m_position;
            return *this;
        }

        const string toString() const {
            return "";
        }

        void setPosition(const LocalPoint3 &p) {
            m_position = p;
        }

        LocalPoint3 getPosition() const {
            return m_position;
        }

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            core::SharedPointer<Serializer> s = sf.getSerializer(out);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('p', 'o', 's') >::RESULT,
                    m_position);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('p', 'o', 's') >::RESULT,
                   m_position);

            return in;
        }
};


class RuntimeControlContainerTestSampleData : public core::data::SerializableData {
    public:
        RuntimeControlContainerTestSampleData() :
            m_int(0) {}

        uint32_t m_int;

        const string toString() const {
            stringstream sstr;
            sstr << m_int;
            return sstr.str();
        }

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            core::SharedPointer<Serializer> s = sf.getSerializer(out);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                    m_int);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                   m_int);

            return in;
        }
};

class RuntimeControlContainerTestModule : public TimeTriggeredConferenceClientModule {
    public:
        RuntimeControlContainerTestModule(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "RuntimeControlContainerTestModule"),
            m_cycleCounter(0),
            m_config(),
            m_receivedData() {}

        virtual void setUp() {}

        virtual void tearDown() {}

        virtual coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            m_config = getKeyValueConfiguration();

            m_config.getValue<string>("runtimecontrolcontainertestmodule.key1");

            addDataStoreFor(Container::POSITION, m_receivedData);
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
                m_cycleCounter++;

                RuntimeControlContainerTestSampleData tcctsd;
                tcctsd.m_int = m_cycleCounter;
                Container c(Container::UNDEFINEDDATA, tcctsd);
                getConference().send(c);
            }

            return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }

        KeyValueConfiguration getConfiguration() {
            return m_config;
        }

        uint32_t getCycleCounter() const {
            return m_cycleCounter;
        }

        FIFOQueue& getReceivedData() {
            return m_receivedData;
        }

    private:
        uint32_t m_cycleCounter;
        KeyValueConfiguration m_config;
        FIFOQueue m_receivedData;
};

////////////////////////////////////////////////////////////////////////////////

class RuntimeControlContainerTestDummySystemPart : public SystemFeedbackComponent {
    public:
        RuntimeControlContainerTestDummySystemPart() :
            m_freq(1),
            m_receivedDataFIFO() {}

        float getFrequency() const {
            return m_freq;
        }

        virtual void setup() {}

        virtual void tearDown() {}

        virtual void step(const core::wrapper::Time &t, SendContainerToSystemsUnderTest &/*sender*/) {
            clog << "Call to RuntimeControlContainerTestDummySystemPart for t = " << t.getSeconds() << "." << t.getPartialMicroseconds() << ", containing " << getFIFO().getSize() << " containers." << endl;

            while (!getFIFO().isEmpty()) {
                Container c = getFIFO().leave();
                clog << "(RuntimeControlContainerTestDummySystemPart) Sent at " << c.getSentTimeStamp().toString() << ", Received at " << c.getReceivedTimeStamp().toString() << endl;
                m_receivedDataFIFO.add(c);

                // Wait for adding containers.
                Thread::usleepFor(100);
            }
        }

        const float m_freq;
        FIFOQueue m_receivedDataFIFO;
};

class RuntimeControlContainerTestDummySystemPartReply : public SystemFeedbackComponent {
    public:
        RuntimeControlContainerTestDummySystemPartReply(const float &freq) :
            m_freq(freq),
            m_receivedDataFIFO(),
            m_replyCounter(0) {}

        float getFrequency() const {
            return m_freq;
        }

        virtual void setup() {}

        virtual void tearDown() {}

        virtual void step(const core::wrapper::Time &t, SendContainerToSystemsUnderTest &sender) {
            clog << "Call to RuntimeControlContainerTestDummySystemPart for t = " << t.getSeconds() << "." << t.getPartialMicroseconds() << ", containing " << getFIFO().getSize() << " containers." << endl;

            while (!getFIFO().isEmpty()) {
                Container c = getFIFO().leave();
                clog << "(RuntimeControlContainerTestDummySystemPartReply) Sent at " << c.getSentTimeStamp().toString() << ", Received at " << c.getReceivedTimeStamp().toString() << endl;
                m_receivedDataFIFO.add(c);

                // Wait for adding containers.
                Thread::usleepFor(100);
            }

            LocalPosition p;
            p.setPosition(LocalPoint3(m_replyCounter, m_replyCounter+1, m_replyCounter+2));

            Container c(Container::POSITION, p);
            sender.sendToSystemsUnderTest(c);

            m_replyCounter++;
        }

        const float m_freq;
        FIFOQueue m_receivedDataFIFO;
        uint32_t m_replyCounter;
};

class RuntimeControlContainerTest : public CxxTest::TestSuite {
    public:

        void testRuntimeControlContainerRegularRunReceivingSendingAppHalfAsFastAsSC() {
            // Setup configuration.
            stringstream sstr;
            sstr << "runtimecontrolcontainertestmodule.key1 = value1" << endl
                 << "runtimecontrolcontainertestmodule:241280.key2 = value2" << endl
                 << "othermodule.key2 = value2" << endl;

            DirectInterface di("225.0.0.100", 100, sstr.str());
            RuntimeControl sc(di);
            sc.setup(RuntimeControl::TAKE_CONTROL);

            // Setup application.
            string argv0("runtimecontrolcontainertestmodule");
            string argv1("--cid=100");
            int32_t argc = 2;
            char **argv;
            argv = new char*[2];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());

            RuntimeControlContainerTestModule rcctm(argc, argv);

            RuntimeControlContainerTestDummySystemPartReply rcctdscr(2);

            RuntimeEnvironment rte;
            rte.add(rcctm);
            rte.add(rcctdscr);

            // Run application under supervision of RuntimeControl for ten cycles.
            TS_ASSERT(sc.run(rte, 10) == RuntimeControl::RUNTIME_TIMEOUT);

            // At least at the end, the FIFO must be empty.
            const uint32_t SIZE = rcctdscr.m_receivedDataFIFO.getSize();
            clog << "SIZE: " << SIZE << endl;
            TS_ASSERT(SIZE == 28);
            uint32_t undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rcctdscr.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    undefDataCnt++;
                    RuntimeControlContainerTestSampleData data = c.getData<RuntimeControlContainerTestSampleData>();

                    clog << "2-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;
                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));
                    TS_ASSERT(undefDataCnt == data.m_int);
                }
            }

            sc.tearDown();

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST = rcctm.getReceivedData().getSize();
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST == 19);
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST; i++) {
                Container c = rcctm.getReceivedData().leave();
                LocalPosition pos = c.getData<LocalPosition>();
                LocalPoint3 p = pos.getPosition();
                LocalPoint3 ref(i+1, i+2, i+3);

                // The app receives the data with a shift of +1.
                TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == ((i+1) * 500 * 1000));
                TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == ((i+1) * 500 * 1000));
                TS_ASSERT((p-ref).length() < 1e-5);
            }

            // Check if the received configuration is valid.
            stringstream sstrConfigReceived;
            rcctm.getConfiguration().writeTo(sstrConfigReceived);
            stringstream sstrConfig;
            sstrConfig << "runtimecontrolcontainertestmodule.key1=value1" << endl;
            TS_ASSERT(sstrConfigReceived.str() == sstrConfig.str());

            // Check if the application was called 9 times (first cycle is head of app's while-loop).
            clog << "testRuntimeControlContainerRegularRunReceivingSendingAppHalfAsFastAsSC cycles : " << rcctm.getCycleCounter() << endl;
            TS_ASSERT(rcctm.getCycleCounter() == 9);
        }
};

#endif /*CONTEXT_RUNTIMECONTROLCONTAINERTESTSUITE_H_*/
