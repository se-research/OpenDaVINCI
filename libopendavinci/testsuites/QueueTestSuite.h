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

#ifndef CORE_QUEUETESTSUITE_H_
#define CORE_QUEUETESTSUITE_H_

#include <sstream>                      // for stringstream, etc
#include <string>                       // for string

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/base/BufferedFIFOQueue.h"  // for BufferedFIFOQueue
#include "opendavinci/odcore/base/BufferedLIFOQueue.h"  // for BufferedLIFOQueue
#include "opendavinci/odcore/base/Condition.h"        // for Condition
#include "opendavinci/odcore/base/Deserializer.h"     // for Deserializer
#include "opendavinci/odcore/base/FIFOQueue.h"        // for FIFOQueue
#include "opendavinci/odcore/base/Hash.h"             // for CharList, CRC32, etc
#include "opendavinci/odcore/base/LIFOQueue.h"        // for LIFOQueue
#include "opendavinci/odcore/base/Lock.h"             // for Lock
#include "opendavinci/odcore/base/Mutex.h"            // for Mutex
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/base/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/odcore/base/Serializer.h"       // for Serializer
#include "opendavinci/odcore/base/Service.h"          // for Service
#include "opendavinci/odcore/data/Container.h"        // for Container, etc
#include "opendavinci/odcore/data/SerializableData.h"  // for SerializableData

using namespace std;
using namespace odcore::base;
using namespace odcore::data;

class QueueTestSampleData : public odcore::data::SerializableData {
    public:
        QueueTestSampleData() :
                m_int(0) {}

        int32_t m_int;

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(
                CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                m_int);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(
                CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                m_int);

            return in;
        }

        int32_t getID() const {
            return 3456;
        }

        const string getLongName() const {
            return getShortName();
        }

        const string getShortName() const {
            return "QueueTestSampleData";
        }

        const string toString() const {
            stringstream s;
            s << m_int << endl;
            return s.str();
        }
};

class QueueTestSuiteLIFOProducer: public Service {
    public:
        QueueTestSuiteLIFOProducer(LIFOQueue &lifo):
                m_lifo(lifo), sampleData() {}

        void beforeStop() {}

        void run() {
            serviceReady();
            while (isRunning()) {
                sampleData.m_int++;
                Container c(sampleData);
                m_lifo.push(c);

                // Yield other threads.
                Thread::usleepFor(1000);
            }
        }

    private:
        LIFOQueue &m_lifo;
        QueueTestSampleData sampleData;
};

class QueueTestSuiteLIFOConsumer: public Service {
    public:
        QueueTestSuiteLIFOConsumer(LIFOQueue &lifo, Condition &blockTestCase):
                m_lifo(lifo),
                m_blockTestCase(blockTestCase),
                m_counterMutex(),
                m_counter(0),
                m_sum(0) {}

        void beforeStop() {}

        uint32_t getNumberOfElements() {
            Lock l(m_counterMutex);
            return m_counter;
        }

        void run() {
            serviceReady();
            while (isRunning()) {
                // Yield other threads.
                Thread::usleepFor(1000*100);

                Container c = m_lifo.pop();
                QueueTestSampleData sampleData;
                sampleData = c.getData<QueueTestSampleData>();
                m_sum += sampleData.m_int;
                {
                    Lock l(m_counterMutex);
                    m_counter++;
                }

                {
                    Lock l(m_blockTestCase);
                    if (m_sum > 1000) {
                        m_blockTestCase.wakeAll();
                        break;
                    }
                }
            }
        }

    private:
        LIFOQueue &m_lifo;
        Condition &m_blockTestCase;
        Mutex m_counterMutex;
        uint32_t m_counter;
        uint32_t m_sum;
};

class QueueTestSuiteFIFOProducer: public Service {
    public:
        QueueTestSuiteFIFOProducer(FIFOQueue &fifo):
                m_fifo(fifo), sampleData() {}

        void beforeStop() {}

        void run() {
            serviceReady();
            while (isRunning()) {
                sampleData.m_int++;
                Container c(sampleData);
                m_fifo.enter(c);

                // Yield other threads.
                Thread::usleepFor(1000);
            }
        }

    private:
        FIFOQueue &m_fifo;
        QueueTestSampleData sampleData;
};

class QueueTestSuiteFIFOConsumer: public Service {
    public:
        QueueTestSuiteFIFOConsumer(FIFOQueue &fifo, Condition &blockTestCase):
                m_fifo(fifo),
                m_blockTestCase(blockTestCase),
                m_counterMutex(),
                m_counter(0),
                m_sum(0) {}

        void beforeStop() {}

        uint32_t getNumberOfElements() {
            Lock l(m_counterMutex);
            return m_counter;
        }

        void run() {
            serviceReady();
            while (isRunning()) {
                Container c = m_fifo.leave();
                QueueTestSampleData sampleData;
                sampleData = c.getData<QueueTestSampleData>();
                m_sum += sampleData.m_int;
                {
                    Lock l(m_counterMutex);
                    m_counter++;
                }

                {
                    Lock l(m_blockTestCase);
                    if (m_sum > 1000) {
                        m_blockTestCase.wakeAll();
                        break;
                    }
                }

                // Yield other threads.
                Thread::usleepFor(1000);
            }
        }

    private:
        FIFOQueue &m_fifo;
        Condition &m_blockTestCase;
        Mutex m_counterMutex;
        uint32_t m_counter;
        uint32_t m_sum;
};

class QueueTest : public CxxTest::TestSuite {
    public:
        void testLIFO() {
            Condition blockTestCase;
            LIFOQueue lifo;

            QueueTestSuiteLIFOProducer producer(lifo);
            QueueTestSuiteLIFOConsumer consumer(lifo, blockTestCase);

            producer.start();
            consumer.start();

            {
                Lock l(blockTestCase);
                blockTestCase.waitOnSignal();
            }

            TS_ASSERT(consumer.getNumberOfElements() < 30);

            consumer.stop();
            producer.stop();
        }

        void testFIFO() {
            Condition blockTestCase;
            FIFOQueue fifo;

            QueueTestSuiteFIFOProducer producer(fifo);
            QueueTestSuiteFIFOConsumer consumer(fifo, blockTestCase);

            producer.start();
            consumer.start();

            {
                Lock l(blockTestCase);
                blockTestCase.waitOnSignal();
            }
            TS_ASSERT(consumer.getNumberOfElements() > 35);

            consumer.stop();
            producer.stop();
        }

        void testBufferedFIFOAsRegularFIFO() {
            Condition blockTestCase;
            BufferedFIFOQueue bufferedFifo(1000);

            QueueTestSuiteFIFOProducer producer(bufferedFifo);
            QueueTestSuiteFIFOConsumer consumer(bufferedFifo, blockTestCase);

            producer.start();
            consumer.start();

            {
                Lock l(blockTestCase);
                blockTestCase.waitOnSignal();
            }
            TS_ASSERT(consumer.getNumberOfElements() > 35);

            consumer.stop();
            producer.stop();
        }

        void testBufferedFIFO() {
            bool failed = true;
            BufferedFIFOQueue bufferedFifo(1000);

            TS_ASSERT(bufferedFifo.isEmpty());
            TS_ASSERT(bufferedFifo.getIndexOfLastElement() == -1);

            failed = true;
            try {
                bufferedFifo.getElementAt(1);
                failed = true;
            } catch (...) {
                failed = false;
            }

            TS_ASSERT(!failed);

            QueueTestSampleData sampleData;
            sampleData.m_int = 10;
            Container c1(sampleData);
            bufferedFifo.enter(c1);

            TS_ASSERT(bufferedFifo.getSize() == 1);

            sampleData.m_int = 20;
            Container c2(sampleData);
            bufferedFifo.enter(c2);

            TS_ASSERT(bufferedFifo.getSize() == 2);

            sampleData.m_int = 30;
            Container c3(sampleData);
            bufferedFifo.enter(c3);

            TS_ASSERT(bufferedFifo.getSize() == 3);

            TS_ASSERT(!bufferedFifo.isEmpty());
            TS_ASSERT(bufferedFifo.getSize() == 3);
            TS_ASSERT(bufferedFifo.getIndexOfLastElement() == 2);

            Container retrievedContainer3 = bufferedFifo.getElementAt(2);
            TS_ASSERT(retrievedContainer3.getDataType() == sampleData.getID());
            sampleData = retrievedContainer3.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 30);

            Container retrievedContainer1 = bufferedFifo.getElementAt(0);
            TS_ASSERT(retrievedContainer1.getDataType() == sampleData.getID());
            sampleData = retrievedContainer1.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 10);

            Container retrievedContainer2 = bufferedFifo.getElementAt(1);
            TS_ASSERT(retrievedContainer2.getDataType() == sampleData.getID());
            sampleData = retrievedContainer2.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 20);

            Container retrievedContainer3a = bufferedFifo.getElementAt(bufferedFifo.getIndexOfLastElement());
            TS_ASSERT(retrievedContainer3a.getDataType() == sampleData.getID());
            sampleData = retrievedContainer3a.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 30);

            failed = true;
            try {
                bufferedFifo.getElementAt(5);
                failed = true;
            } catch (...) {
                failed = false;
            }

            TS_ASSERT(!failed);
        }

        void testFixedSizeBufferedFIFO() {
            bool failed = true;
            // Create a buffered FIFO of fixed size 2.
            BufferedFIFOQueue bufferedFifo(2);

            TS_ASSERT(bufferedFifo.isEmpty());
            TS_ASSERT(bufferedFifo.getIndexOfLastElement() == -1);

            failed = true;
            try {
                bufferedFifo.getElementAt(1);
                failed = true;
            } catch (...) {
                failed = false;
            }

            TS_ASSERT(!failed);

            QueueTestSampleData sampleData;
            sampleData.m_int = 10;
            Container c1(sampleData);
            bufferedFifo.enter(c1);

            TS_ASSERT(bufferedFifo.getSize() == 1);

            sampleData.m_int = 20;
            Container c2(sampleData);
            bufferedFifo.enter(c2);

            TS_ASSERT(bufferedFifo.getSize() == 2);

            sampleData.m_int = 30;
            Container c3(sampleData);
            bufferedFifo.enter(c3);

            TS_ASSERT(!bufferedFifo.isEmpty());
            TS_ASSERT(bufferedFifo.getSize() == 2);
            TS_ASSERT(bufferedFifo.getIndexOfLastElement() == 1);

            Container retrievedContainer1 = bufferedFifo.getElementAt(0);
            TS_ASSERT(retrievedContainer1.getDataType() == sampleData.getID());
            sampleData = retrievedContainer1.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 10);

            Container retrievedContainer2 = bufferedFifo.getElementAt(1);
            TS_ASSERT(retrievedContainer2.getDataType() == sampleData.getID());
            sampleData = retrievedContainer2.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 20);

            Container retrievedContainer3a = bufferedFifo.getElementAt(bufferedFifo.getIndexOfLastElement());
            TS_ASSERT(retrievedContainer3a.getDataType() == sampleData.getID());
            sampleData = retrievedContainer3a.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 20);

            failed = true;
            try {
                bufferedFifo.getElementAt(5);
                failed = true;
            } catch (...) {
                failed = false;
            }

            TS_ASSERT(!failed);

            // Remove first entry.
            bufferedFifo.leave();

            TS_ASSERT(!bufferedFifo.isEmpty());
            TS_ASSERT(bufferedFifo.getSize() == 1);
            TS_ASSERT(bufferedFifo.getIndexOfLastElement() == 0);

            retrievedContainer2 = bufferedFifo.getElementAt(0);
            TS_ASSERT(retrievedContainer2.getDataType() == sampleData.getID());
            sampleData = retrievedContainer2.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 20);

            sampleData.m_int = 30;
            c3 = Container(sampleData);
            bufferedFifo.enter(c3);

            TS_ASSERT(!bufferedFifo.isEmpty());
            TS_ASSERT(bufferedFifo.getSize() == 2);
            TS_ASSERT(bufferedFifo.getIndexOfLastElement() == 1);

            Container retrievedContainer3 = bufferedFifo.getElementAt(bufferedFifo.getIndexOfLastElement());
            TS_ASSERT(retrievedContainer3.getDataType() == sampleData.getID());
            sampleData = retrievedContainer3.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 30);
        }

        void testBufferedLIFOAsRegularLIFO() {
// This test case does not succeed on Windows 7 but on Windows 8.1 and Windows 10.
#ifndef _WIN32
            Condition blockTestCase;
            BufferedLIFOQueue bufferedLifo(1000);

            QueueTestSuiteLIFOProducer producer(bufferedLifo);
            QueueTestSuiteLIFOConsumer consumer(bufferedLifo, blockTestCase);

            producer.start();
            consumer.start();

            {
                Lock l(blockTestCase);
                blockTestCase.waitOnSignal();
            }
            TS_ASSERT(consumer.getNumberOfElements() < 30);

            consumer.stop();
            producer.stop();
#endif
        }

        void testBufferedLIFO() {
            bool failed = true;
            BufferedLIFOQueue bufferedLifo(1000);

            TS_ASSERT(bufferedLifo.isEmpty());
            TS_ASSERT(bufferedLifo.getIndexOfLastElement() == -1);

            failed = true;
            try {
                bufferedLifo.getElementAt(1);
                failed = true;
            } catch (...) {
                failed = false;
            }

            TS_ASSERT(!failed);

            QueueTestSampleData sampleData;
            sampleData.m_int = 10;
            Container c1(sampleData);
            bufferedLifo.push(c1);

            TS_ASSERT(bufferedLifo.getSize() == 1);

            sampleData.m_int = 20;
            Container c2(sampleData);
            bufferedLifo.push(c2);

            TS_ASSERT(bufferedLifo.getSize() == 2);

            sampleData.m_int = 30;
            Container c3(sampleData);
            bufferedLifo.push(c3);

            TS_ASSERT(bufferedLifo.getSize() == 3);

            TS_ASSERT(!bufferedLifo.isEmpty());
            TS_ASSERT(bufferedLifo.getSize() == 3);
            TS_ASSERT(bufferedLifo.getIndexOfLastElement() == 2);

            Container retrievedContainer3 = bufferedLifo.getElementAt(2);
            TS_ASSERT(retrievedContainer3.getDataType() == sampleData.getID());
            sampleData = retrievedContainer3.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 10);

            Container retrievedContainer1 = bufferedLifo.getElementAt(0);
            TS_ASSERT(retrievedContainer1.getDataType() == sampleData.getID());
            sampleData = retrievedContainer1.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 30);

            Container retrievedContainer2 = bufferedLifo.getElementAt(1);
            TS_ASSERT(retrievedContainer2.getDataType() == sampleData.getID());
            sampleData = retrievedContainer2.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 20);

            Container retrievedContainer3a = bufferedLifo.getElementAt(bufferedLifo.getIndexOfLastElement());
            TS_ASSERT(retrievedContainer3a.getDataType() == sampleData.getID());
            sampleData = retrievedContainer3a.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 10);

            failed = true;
            try {
                bufferedLifo.getElementAt(5);
                failed = true;
            } catch (...) {
                failed = false;
            }

            TS_ASSERT(!failed);
        }

        void testFixedSizeBufferedLIFO() {
            bool failed = true;
            // Create a buffered LIFO of fixed size 2.
            BufferedLIFOQueue bufferedLifo(2);

            TS_ASSERT(bufferedLifo.isEmpty());
            TS_ASSERT(bufferedLifo.getIndexOfLastElement() == -1);

            failed = true;
            try {
                bufferedLifo.getElementAt(1);
                failed = true;
            } catch (...) {
                failed = false;
            }

            TS_ASSERT(!failed);

            QueueTestSampleData sampleData;
            sampleData.m_int = 10;
            Container c1(sampleData);
            bufferedLifo.push(c1);

            TS_ASSERT(bufferedLifo.getSize() == 1);

            sampleData.m_int = 20;
            Container c2(sampleData);
            bufferedLifo.push(c2);

            TS_ASSERT(bufferedLifo.getSize() == 2);

            sampleData.m_int = 30;
            Container c3(sampleData);
            bufferedLifo.push(c3);

            TS_ASSERT(!bufferedLifo.isEmpty());
            TS_ASSERT(bufferedLifo.getSize() == 2);
            TS_ASSERT(bufferedLifo.getIndexOfLastElement() == 1);

            Container retrievedContainer1 = bufferedLifo.getElementAt(0);
            TS_ASSERT(retrievedContainer1.getDataType() == sampleData.getID());
            sampleData = retrievedContainer1.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 20);

            Container retrievedContainer2 = bufferedLifo.getElementAt(1);
            TS_ASSERT(retrievedContainer2.getDataType() == sampleData.getID());
            sampleData = retrievedContainer2.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 10);

            Container retrievedContainer3a = bufferedLifo.getElementAt(bufferedLifo.getIndexOfLastElement());
            TS_ASSERT(retrievedContainer3a.getDataType() == sampleData.getID());
            sampleData = retrievedContainer3a.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 10);

            failed = true;
            try {
                bufferedLifo.getElementAt(5);
                failed = true;
            } catch (...) {
                failed = false;
            }

            TS_ASSERT(!failed);

            // Remove first entry.
            bufferedLifo.pop();

            TS_ASSERT(!bufferedLifo.isEmpty());
            TS_ASSERT(bufferedLifo.getSize() == 1);
            TS_ASSERT(bufferedLifo.getIndexOfLastElement() == 0);

            retrievedContainer2 = bufferedLifo.getElementAt(0);
            TS_ASSERT(retrievedContainer2.getDataType() == sampleData.getID());
            sampleData = retrievedContainer2.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 10);

            sampleData.m_int = 30;
            c3 = Container(sampleData);
            bufferedLifo.push(c3);

            TS_ASSERT(!bufferedLifo.isEmpty());
            TS_ASSERT(bufferedLifo.getSize() == 2);
            TS_ASSERT(bufferedLifo.getIndexOfLastElement() == 1);

            Container retrievedContainer3 = bufferedLifo.getElementAt(bufferedLifo.getIndexOfLastElement());
            TS_ASSERT(retrievedContainer3.getDataType() == sampleData.getID());
            sampleData = retrievedContainer3.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 10);

            retrievedContainer1 = bufferedLifo.getElementAt(0);
            TS_ASSERT(retrievedContainer1.getDataType() == sampleData.getID());
            sampleData = retrievedContainer1.getData<QueueTestSampleData>();
            TS_ASSERT(sampleData.m_int == 30);
        }
};

#endif /*CORE_QUEUETESTSUITE_H_*/
