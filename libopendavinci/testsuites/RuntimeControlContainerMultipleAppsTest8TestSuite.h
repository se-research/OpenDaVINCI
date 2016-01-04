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

#ifndef CONTEXT_RUNTIMECONTROLCONTAINERMULTIPLEAPPSTESTSUITE_H_
#define CONTEXT_RUNTIMECONTROLCONTAINERMULTIPLEAPPSTESTSUITE_H_

#include <cmath>                        // for sqrt
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <string>                       // for string, operator<<, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "core/opendavinci.h"
#include "context/base/DirectInterface.h"  // for DirectInterface
#include "context/base/RuntimeControl.h"  // for RuntimeControl, etc
#include "context/base/RuntimeEnvironment.h"  // for RuntimeEnvironment
#include "context/base/SendContainerToSystemsUnderTest.h"
#include "context/base/SystemFeedbackComponent.h"
#include "context/base/SystemReportingComponent.h"
#include "core/SharedPointer.h"         // for SharedPointer
#include "core/base/Deserializer.h"     // for Deserializer
#include "core/base/FIFOQueue.h"        // for FIFOQueue
#include "core/base/Hash.h"             // for CharList, CRC32, etc
#include "core/base/KeyValueConfiguration.h"  // for KeyValueConfiguration
#include "core/base/SerializationFactory.h"  // for SerializationFactory
#include "core/base/Serializer.h"       // for Serializer
#include "core/base/Thread.h"           // for Thread
#include "core/base/module/TimeTriggeredConferenceClientModule.h"
#include "core/data/Container.h"        // for Container, etc
#include "core/data/SerializableData.h"  // for SerializableData
#include "core/data/TimeStamp.h"        // for TimeStamp
#include "generated/coredata/dmcp/ModuleExitCodeMessage.h"

namespace core { namespace wrapper { class Time; } }

using namespace std;
using namespace core::base;
using namespace core::base::module;
using namespace core::data;
using namespace context::base;


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

        double getZ() const {
            return m_z;
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
        LocalPoint3 m_rotation;
    public:
        LocalPosition() :
            m_position(),
            m_rotation() {}

        LocalPosition(const LocalPosition &o) :
            SerializableData(),
            m_position(o.m_position),
            m_rotation(o.m_rotation) {}

        LocalPosition& operator=(const LocalPosition &o) {
            m_position = o.m_position;
            m_rotation = o.m_rotation;
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

        void setRotation(const LocalPoint3 &p) {
            m_rotation = p;
        }

        LocalPoint3 getRotation() const {
            return m_rotation;
        }

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            core::SharedPointer<Serializer> s = sf.getSerializer(out);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('p', 'o', 's') >::RESULT,
                    m_position);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('r', 'o', 't') >::RESULT,
                    m_rotation);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('p', 'o', 's') >::RESULT,
                   m_position);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('r', 'o', 't') >::RESULT,
                   m_rotation);

            return in;
        }
};


class RuntimeControlContainerMultipleAppsTestData : public core::data::SerializableData {
    public:
        RuntimeControlContainerMultipleAppsTestData() :
            m_int(0),
            m_id("") {}

        uint32_t m_int;
        string m_id;

        const string toString() const {
            stringstream sstr;
            sstr << m_id << " " << m_int;
            return sstr.str();
        }

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            core::SharedPointer<Serializer> s = sf.getSerializer(out);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                    m_int);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('m', '_', 'i', 'd') >::RESULT,
                    m_id);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('m', '_', 'i', 'd') >::RESULT,
                   m_id);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                   m_int);

            return in;
        }
};

class RuntimeControlContainerMultipleAppsTestModule : public TimeTriggeredConferenceClientModule {
    public:
        RuntimeControlContainerMultipleAppsTestModule(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "RuntimeControlContainerMultipleAppsTestModule"),
            m_cycleCounter(0),
            m_config(),
            m_receivedData() {}

        virtual void setUp() {}

        virtual void tearDown() {}

        virtual coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            m_config = getKeyValueConfiguration();

            m_config.getValue<string>("runtimecontrolcontainermultipleappstestmodule.key1");

            addDataStoreFor(Container::POSITION, m_receivedData);
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
                m_cycleCounter++;

                stringstream sstrId;
                sstrId << getIdentifier();

                RuntimeControlContainerMultipleAppsTestData tcctsd;
                tcctsd.m_int = m_cycleCounter;
                tcctsd.m_id = sstrId.str();
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

class RuntimeControlContainerMultipleAppsTestModuleForSampleData : public TimeTriggeredConferenceClientModule {
    public:
        RuntimeControlContainerMultipleAppsTestModuleForSampleData(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "RuntimeControlContainerMultipleAppsTestModuleForSampleData"),
            m_cycleCounter(0),
            m_receivedData() {}

        virtual void setUp() {}

        virtual void tearDown() {}

        virtual coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            addDataStoreFor(m_receivedData);
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
                m_cycleCounter++;
            }

            return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }

        uint32_t getCycleCounter() const {
            return m_cycleCounter;
        }

        FIFOQueue& getReceivedData() {
            return m_receivedData;
        }

    private:
        uint32_t m_cycleCounter;
        FIFOQueue m_receivedData;
};

////////////////////////////////////////////////////////////////////////////////

class RuntimeControlContainerMultipleAppsTestSystemPartReply : public SystemFeedbackComponent {
    public:
        RuntimeControlContainerMultipleAppsTestSystemPartReply(const float &freq) :
            m_freq(freq),
            m_receivedDataFIFO(),
            m_replyCounter(0) {}

        float getFrequency() const {
            return m_freq;

        }

        virtual void setup() {}

        virtual void tearDown() {}

        virtual void step(const core::wrapper::Time &t, SendContainerToSystemsUnderTest &sender) {
            clog << "Call to RuntimeControlContainerMultipleAppsTestSystemPartReply for t = " << t.getSeconds() << "." << t.getPartialMicroseconds() << ", containing " << getFIFO().getSize() << " containers." << endl;

            const uint32_t SIZE = getFIFO().getSize();
            for (uint32_t i = 0; i < SIZE; i++) {
                Container c = getFIFO().leave();
                clog << "(RuntimeControlContainerMultipleAppsTestSystemPartReply) Sent at " << c.getSentTimeStamp().toString() << ", Received at " << c.getReceivedTimeStamp().toString() << endl;
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

class RuntimeControlContainerMultipleAppsTestSystemPartReplyRotation : public SystemFeedbackComponent {
    public:
        RuntimeControlContainerMultipleAppsTestSystemPartReplyRotation(const float &freq) :
            m_freq(freq),
            m_receivedDataFIFO(),
            m_replyCounter(0) {}

        float getFrequency() const {
            return m_freq;
        }

        virtual void setup() {}

        virtual void tearDown() {}

        virtual void step(const core::wrapper::Time &t, SendContainerToSystemsUnderTest &sender) {
            clog << "Call to RuntimeControlContainerMultipleAppsTestSystemPartReply for t = " << t.getSeconds() << "." << t.getPartialMicroseconds() << ", containing " << getFIFO().getSize() << " containers." << endl;

            const uint32_t SIZE = getFIFO().getSize();
            for (uint32_t i = 0; i < SIZE; i++) {
                Container c = getFIFO().leave();
                clog << "(RuntimeControlContainerMultipleAppsTestSystemPartReply) Sent at " << c.getSentTimeStamp().toString() << ", Received at " << c.getReceivedTimeStamp().toString() << endl;
                m_receivedDataFIFO.add(c);

                // Wait for adding containers.
                Thread::usleepFor(100);
            }

            LocalPosition p;
            p.setRotation(LocalPoint3(m_replyCounter, m_replyCounter+1, m_replyCounter+2));

            Container c(Container::POSITION, p);
            sender.sendToSystemsUnderTest(c);

            m_replyCounter++;
        }

        const float m_freq;
        FIFOQueue m_receivedDataFIFO;
        uint32_t m_replyCounter;
};

class RuntimeControlContainerMultipleAppsTestSystemReportingComponent : public SystemReportingComponent {
    public:
        RuntimeControlContainerMultipleAppsTestSystemReportingComponent() :
            m_counter(0) {}

        virtual void setup() {}

        virtual void tearDown() {}

        virtual void report(const core::wrapper::Time &t) {
            clog << "Call to RuntimeControlContainerMultipleAppsTestSystemReportingComponent for t = " << t.getSeconds() << "." << t.getPartialMicroseconds() << ", containing " << getFIFO().getSize() << " containers." << endl;

            // Simply remove all entries.
            getFIFO().clear();

            m_counter++;
        }

        uint32_t m_counter;
};

////////////////////////////////////////////////////////////////////////////////

class RuntimeControlContainerMultipleAppsTest : public CxxTest::TestSuite {
    public:

        void testRuntimeControlContainerRegularRunReceivingSendingTwoAppsSameFreqTwoSystemPartsSP2TwiceAsFastAsSP1() {
            // Setup configuration.
            stringstream sstr;
            sstr << "runtimecontrolcontainermultipleappstestmodule.key1 = value1" << endl
                 << "runtimecontrolcontainermultipleappstestmodule:241280.key2 = value2" << endl
                 << "othermodule.key2 = value2" << endl;

            DirectInterface di("225.0.0.100", 100, sstr.str());
            RuntimeControl sc(di);
            sc.setup(RuntimeControl::TAKE_CONTROL);

            ////////////////////////////////////////////////////////////////////

            // Setup application.
            string argv0App1("runtimecontrolcontainermultipleappstestmodule");
            string argv1App1("--cid=100");
            int32_t argcApp1 = 2;
            char **argvApp1;
            argvApp1 = new char*[2];
            argvApp1[0] = const_cast<char*>(argv0App1.c_str());
            argvApp1[1] = const_cast<char*>(argv1App1.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp1(argcApp1, argvApp1);

            string argv0App2("runtimecontrolcontainermultipleappstestmodule");
            string argv1App2("--cid=100");
            int32_t argcApp2 = 2;
            char **argvApp2;
            argvApp2 = new char*[2];
            argvApp2[0] = const_cast<char*>(argv0App2.c_str());
            argvApp2[1] = const_cast<char*>(argv1App2.c_str());

            RuntimeControlContainerMultipleAppsTestModule rtccmatmApp2(argcApp2, argvApp2);

            ////////////////////////////////////////////////////////////////////

            RuntimeControlContainerMultipleAppsTestSystemPartReply rtccmatspr(1);

            RuntimeControlContainerMultipleAppsTestSystemPartReplyRotation rtccmatsprRotation(2);

            RuntimeEnvironment rte;
            rte.add(rtccmatmApp1);
            rte.add(rtccmatmApp2);
            rte.add(rtccmatspr);
            rte.add(rtccmatsprRotation);

            // Run application under supervision of RuntimeControl for ten cycles.
            TS_ASSERT(sc.run(rte, 10) == RuntimeControl::RUNTIME_TIMEOUT);

            // At least at the end, the FIFO must be empty.
            const uint32_t SIZE = rtccmatspr.m_receivedDataFIFO.getSize();
            clog << "SIZE: " << SIZE << endl;
            TS_ASSERT(SIZE == 43);
            uint32_t undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatspr.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));

                    TS_ASSERT(((undefDataCnt/2)+1) == data.m_int);
                    undefDataCnt++;
                }
            }

            const uint32_t SIZE_SP2 = rtccmatsprRotation.m_receivedDataFIFO.getSize();
            clog << "SIZE_SP2: " << SIZE_SP2 << endl;
            TS_ASSERT(SIZE_SP2 == 47);
            undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatsprRotation.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (((undefDataCnt/2)+1) * 1000 * 1000));

                    TS_ASSERT(((undefDataCnt/2)+1) == data.m_int);
                    undefDataCnt++;
                }
            }

            sc.tearDown();

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 = rtccmatmApp1.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1: " << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 == 28);
            uint32_t cntSP1 = 0;
            uint32_t cntSP2 = 0;
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1; i++) {
                Container c = rtccmatmApp1.getReceivedData().leave();
                LocalPosition pos = c.getData<LocalPosition>();

                LocalPoint3 p;
                if (pos.getPosition().getZ() > 0) {
                    cntSP1++;
                    p = pos.getPosition();
                    LocalPoint3 ref(cntSP1, cntSP1+1, cntSP1+2);

                    clog << "C1a-i: " << i << ", cntSP1: " << cntSP1 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
                if (pos.getRotation().getZ() > 0) {
                    cntSP2++;
                    p = pos.getRotation();
                    LocalPoint3 ref(cntSP2, cntSP2+1, cntSP2+2);

                    clog << "C1b-i: " << i << ", cntSP2: " << cntSP2 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
            }

            // Check if the received configuration is valid.
            stringstream sstrConfig;
            sstrConfig << "runtimecontrolcontainermultipleappstestmodule.key1=value1" << endl;

            stringstream sstrConfigReceivedA1;
            rtccmatmApp1.getConfiguration().writeTo(sstrConfigReceivedA1);
            TS_ASSERT(sstrConfigReceivedA1.str() == sstrConfig.str());

            ////////////////////////////////////////////////////////////////////

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 = rtccmatmApp2.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2: " << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 == 28);
            cntSP1 = 0;
            cntSP2 = 0;
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2; i++) {
                Container c = rtccmatmApp2.getReceivedData().leave();
                LocalPosition pos = c.getData<LocalPosition>();

                LocalPoint3 p;
                if (pos.getPosition().getZ() > 0) {
                    cntSP1++;
                    p = pos.getPosition();
                    LocalPoint3 ref(cntSP1, cntSP1+1, cntSP1+2);

                    clog << "D1a-i: " << i << ", cntSP1: " << cntSP1 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP1 * 1000 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
                if (pos.getRotation().getZ() > 0) {
                    cntSP2++;
                    p = pos.getRotation();
                    LocalPoint3 ref(cntSP2, cntSP2+1, cntSP2+2);

                    clog << "D1b-i: " << i << ", cntSP2: " << cntSP2 << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntSP2 * 500 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
            }

            // Check if the received configuration is valid.
            stringstream sstrConfigReceivedA2;
            rtccmatmApp2.getConfiguration().writeTo(sstrConfigReceivedA2);
            TS_ASSERT(sstrConfigReceivedA2.str() == sstrConfig.str());

            // Check if the application was called 9 times (first cycle is head of app's while-loop).
            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp1.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp1.getCycleCounter() == 9);

            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp2.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp2.getCycleCounter() == 9);
        }

};

#endif /*CONTEXT_RUNTIMECONTROLCONTAINERMULTIPLEAPPSTESTSUITE_H_*/
