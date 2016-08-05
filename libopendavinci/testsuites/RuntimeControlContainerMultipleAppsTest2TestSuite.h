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
#include <memory>
#include <string>                       // for string, operator<<, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcontext/base/DirectInterface.h"  // for DirectInterface
#include "opendavinci/odcontext/base/RuntimeControl.h"  // for RuntimeControl, etc
#include "opendavinci/odcontext/base/RuntimeEnvironment.h"  // for RuntimeEnvironment
#include "opendavinci/odcontext/base/SendContainerToSystemsUnderTest.h"
#include "opendavinci/odcontext/base/SystemFeedbackComponent.h"
#include "opendavinci/odcontext/base/SystemReportingComponent.h"
#include "opendavinci/odcore/serialization/Deserializer.h"     // for Deserializer
#include "opendavinci/odcore/base/FIFOQueue.h"        // for FIFOQueue
#include "opendavinci/odcore/base/KeyValueConfiguration.h"  // for KeyValueConfiguration
#include "opendavinci/odcore/base/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/odcore/base/Serializer.h"       // for Serializer
#include "opendavinci/odcore/base/Thread.h"           // for Thread
#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/data/Container.h"        // for Container, etc
#include "opendavinci/odcore/data/SerializableData.h"  // for SerializableData
#include "opendavinci/odcore/data/TimeStamp.h"        // for TimeStamp
#include "opendavinci/generated/odcore/data/dmcp/ModuleExitCodeMessage.h"

namespace odcore { namespace wrapper { class Time; } }

using namespace std;
using namespace odcore::base;
using namespace odcore::base::module;
using namespace odcore::data;
using namespace odcontext::base;

const int32_t Container_POSITION = 15;

class LocalPoint3 : public odcore::data::SerializableData {
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

        int32_t getID() const {
            return 35;
        }

        const string getLongName() const {
            return "LocalPoint3";
        }

        const string getShortName() const {
            return getLongName();
        }

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();;

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            stringstream rawData;
            rawData.precision(10);

            rawData << m_x << endl << m_y << endl << m_z;

            s->write(1,
                    rawData.str());

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();;

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            string data;
            d->read(1,
                   data);

            stringstream rawData;
            rawData.precision(10);
            rawData.str(data);

            rawData >> m_x >> m_y >> m_z;

            return in;
        }
};

class LocalPosition : public odcore::data::SerializableData {
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

        int32_t getID() const {
            return Container_POSITION;
        }

        const string getLongName() const {
            return "LocalPosition";
        }

        const string getShortName() const {
            return getLongName();
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

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(1,
                    m_position);

            s->write(2,
                    m_rotation);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(1,
                   m_position);

            d->read(2,
                   m_rotation);

            return in;
        }
};



class RuntimeControlContainerMultipleAppsTestData : public odcore::data::SerializableData {
    public:
        RuntimeControlContainerMultipleAppsTestData() :
            m_int(0),
            m_id("") {}

        uint32_t m_int;
        string m_id;

        int32_t getID() const {
            return 37;
        }

        const string getLongName() const {
            return "RuntimeControlContainerMultipleAppsTestData";
        }

        const string getShortName() const {
            return getLongName();
        }

        const string toString() const {
            stringstream sstr;
            sstr << m_id << " " << m_int;
            return sstr.str();
        }

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(2, m_int);

            s->write(1, m_id);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(1, m_id);

            d->read(2, m_int);

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

        virtual odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            m_config = getKeyValueConfiguration();

            m_config.getValue<string>("runtimecontrolcontainermultipleappstestmodule.key1");

            addDataStoreFor(Container_POSITION, m_receivedData);
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                m_cycleCounter++;

                stringstream sstrId;
                sstrId << getIdentifier();

                RuntimeControlContainerMultipleAppsTestData tcctsd;
                tcctsd.m_int = m_cycleCounter;
                tcctsd.m_id = sstrId.str();
                Container c(tcctsd);
                getConference().send(c);
            }

            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
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

        virtual odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            addDataStoreFor(m_receivedData);
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                m_cycleCounter++;
            }

            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
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

        virtual void step(const odcore::wrapper::Time &t, SendContainerToSystemsUnderTest &sender) {
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

            Container c(p);
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

        virtual void step(const odcore::wrapper::Time &t, SendContainerToSystemsUnderTest &sender) {
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

            Container c(p);
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

        virtual void report(const odcore::wrapper::Time &t) {
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

        void testRuntimeControlContainerRegularRunReceivingSendingTwoAppsOneReceivingDataFromOtherAppSameFreqOneSP() {
            // Setup configuration.
            stringstream sstr;
            sstr << "runtimecontrolcontainermultipleappstestmodule.key1 = value1" << endl
                 << "runtimecontrolcontainermultipleappstestmodule:241280.key2 = value2" << endl
                 << "RuntimeControlContainerMultipleAppsTestModuleForSampleData.key3 = value3" << endl
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

            string argv0App2("runtimecontrolcontainermultipleappstestmoduleforsampledata");
            string argv1App2("--cid=100");
            int32_t argcApp2 = 2;
            char **argvApp2;
            argvApp2 = new char*[2];
            argvApp2[0] = const_cast<char*>(argv0App2.c_str());
            argvApp2[1] = const_cast<char*>(argv1App2.c_str());

            RuntimeControlContainerMultipleAppsTestModuleForSampleData app2(argcApp2, argvApp2);

            ////////////////////////////////////////////////////////////////////

            RuntimeControlContainerMultipleAppsTestSystemPartReply rtccmatspr(1);

            RuntimeControlContainerMultipleAppsTestSystemReportingComponent reporter1;
            RuntimeControlContainerMultipleAppsTestSystemReportingComponent reporter2;

            RuntimeEnvironment rte;
            rte.add(rtccmatmApp1);
            rte.add(app2);
            rte.add(rtccmatspr);
            rte.add(reporter1);
            rte.add(reporter2);

            // Run application under supervision of RuntimeControl for ten cycles.
            TS_ASSERT(sc.run(rte, 10) == RuntimeControl::RUNTIME_TIMEOUT);

            // At least at the end, the FIFO must be empty.
            const uint32_t SIZE = rtccmatspr.m_receivedDataFIFO.getSize();
            clog << "SIZE: " << SIZE << endl;
            TS_ASSERT(SIZE == 17);
            uint32_t undefDataCnt = 0;
            for(uint32_t i = 0; i < SIZE; i++) {
                Container c = rtccmatspr.m_receivedDataFIFO.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    undefDataCnt++;

                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();

                    clog << "B-i: " << i << ", undefDataCnt: " << undefDataCnt << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (undefDataCnt * 1000 * 1000));

                    TS_ASSERT(undefDataCnt == data.m_int);
                }
            }

            clog << "REPORTER1-SIZE: " << reporter1.m_counter << endl;
            TS_ASSERT(reporter1.m_counter == 30);

            clog << "REPORTER2-SIZE: " << reporter2.m_counter << endl;
            TS_ASSERT(reporter1.m_counter == 30);

            sc.tearDown();

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 = rtccmatmApp1.getReceivedData().getSize();
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1 == 9);
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A1; i++) {
                Container c = rtccmatmApp1.getReceivedData().leave();
                LocalPosition pos = c.getData<LocalPosition>();
                LocalPoint3 p = pos.getPosition();
                LocalPoint3 ref(i+1, i+2, i+3);

                clog << "C1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == ((i+1) * 1000 * 1000));
                TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == ((i+1) * 1000 * 1000));
                TS_ASSERT((p-ref).length() < 1e-5);
            }

            // Check if the received configuration is valid.
            stringstream sstrConfig;
            sstrConfig << "runtimecontrolcontainermultipleappstestmodule.key1=value1" << endl;

            stringstream sstrConfigReceivedA1;
            rtccmatmApp1.getConfiguration().writeTo(sstrConfigReceivedA1);
            TS_ASSERT(sstrConfigReceivedA1.str() == sstrConfig.str());

            ////////////////////////////////////////////////////////////////////

            const uint32_t SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 = app2.getReceivedData().getSize();
            clog << "SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2:" << SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 << endl;
            TS_ASSERT(SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2 == 18);
            uint32_t cntApp2Position = 0;
            uint32_t cntApp2SampleData = 0;
            for(uint32_t i = 0; i < SIZE_RECEIVED_AT_SYSTEM_UNDER_TEST_A2; i++) {
                Container c = app2.getReceivedData().leave();
                if (c.getDataType() == Container_POSITION) {
                    cntApp2Position++;
                    LocalPosition pos = c.getData<LocalPosition>();
                    LocalPoint3 p = pos.getPosition();
                    LocalPoint3 ref(cntApp2Position, cntApp2Position+1, cntApp2Position+2);

                    clog << "D1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp2Position * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp2Position * 1000 * 1000));
                    TS_ASSERT((p-ref).length() < 1e-5);
                }
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    cntApp2SampleData++;
                    RuntimeControlContainerMultipleAppsTestData data = c.getData<RuntimeControlContainerMultipleAppsTestData>();
                    clog << "E1-i: " << i << ", S: " << c.getSentTimeStamp().toMicroseconds() << ", R: " << c.getReceivedTimeStamp().toMicroseconds() << ", data:" << data.m_int << endl;

                    TS_ASSERT(static_cast<uint32_t>(c.getSentTimeStamp().toMicroseconds()) == (cntApp2SampleData * 1000 * 1000));
                    TS_ASSERT(static_cast<uint32_t>(c.getReceivedTimeStamp().toMicroseconds()) == (cntApp2SampleData * 1000 * 1000));
                    TS_ASSERT(cntApp2SampleData == data.m_int);
                }
            }

            // Check if the received configuration is valid.
            // Check if the application was called 9 times (first cycle is head of app's while-loop).
            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << rtccmatmApp1.getCycleCounter() << endl;
            TS_ASSERT(rtccmatmApp1.getCycleCounter() == 9);

            clog << "RuntimeControlContainerMultipleAppsTestModule cycles : " << app2.getCycleCounter() << endl;
            TS_ASSERT(app2.getCycleCounter() == 9);
        }

};

#endif /*CONTEXT_RUNTIMECONTROLCONTAINERMULTIPLEAPPSTESTSUITE_H_*/
