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

#ifndef CORE_DATASTORESIMPLEDBTESTSUITE_H_
#define CORE_DATASTORESIMPLEDBTESTSUITE_H_

#include <cstdlib>                      // for random
#include <fstream>
#include <string>                       // for string, operator<<, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/base/Deserializer.h"     // for Deserializer
#include "opendavinci/odcore/base/Hash.h"             // for CharList, CRC32, etc
#include "opendavinci/odcore/base/KeyValueDataStore.h"  // for KeyValueDataStore
#include "opendavinci/odcore/base/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/odcore/base/Serializer.h"       // for Serializer
#include "opendavinci/odcore/base/Service.h"          // for Service
#include "opendavinci/odcore/base/Thread.h"           // for Thread
#include "opendavinci/odcore/data/Container.h"        // for Container, etc
#include "opendavinci/odcore/data/SerializableData.h"  // for SerializableData
#include "opendavinci/odcore/data/TimeStamp.h"        // for TimeStamp
#include "opendavinci/odcore/wrapper/KeyValueDatabase.h"  // for KeyValueDatabase
#include "opendavinci/odcore/wrapper/SimpleDB/SimpleDB.h"  // for SimpleDB

using namespace std;
using namespace odcore::base;
using namespace odcore::data;

class MySimpleDB : public odcore::wrapper::SimpleDB::SimpleDB {
    public:
        MySimpleDB() : odcore::wrapper::SimpleDB::SimpleDB() {}
};

class DataStoreTestService : public Service {
    public:
        DataStoreTestService(KeyValueDataStore &ds) :
                m_ds(ds), m_found(false) {
        }

        void beforeStop() {}

        void run() {
            serviceReady();
            while (isRunning()) {
                Container c = m_ds.get(0);
                m_found |= (c.getDataType() == TimeStamp::ID());

                // Yield other threads.
                Thread::usleepFor(10);
            }
        }

        bool hasFound() {
            return m_found;
        }

    private:
        KeyValueDataStore &m_ds;
        bool m_found;
};

class DataStoreTestNestedData : public odcore::data::SerializableData {
    public:
        DataStoreTestNestedData() :
                m_double(0) {
        }

        double m_double;

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('m', '_', 'd', 'o', 'u',
                    'b', 'l', 'e') >::RESULT, m_double);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('m', '_', 'd', 'o', 'u',
                    'b', 'l', 'e') >::RESULT, m_double);

            return in;
        }

        const string toString() const {
            stringstream s;
            s << m_double << endl;
            return s.str();
        }

        int32_t getID() const {
            return 0;
        }

        const string getLongName() const {
            return "DataStoreTestNestedData";
        }

        const string getShortName() const {
            return getLongName();
        }
};

class DataStoreTestSampleData : public odcore::data::SerializableData {
    public:
        DataStoreTestSampleData() :
                m_bool(false), m_int(0), m_string(""), m_nestedData() {
        }

        bool m_bool;
        int32_t m_int;
        string m_string;
        DataStoreTestNestedData m_nestedData;

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('m', '_', 'n', 'e', 's',
                    't', 'e', 'd') >::RESULT, m_nestedData);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('m', '_', 'b', 'o', 'o',
                    'l') >::RESULT, m_bool);

            s->write(
                CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                m_int);

            s->write(
                CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 's', 't', 'r') >::RESULT,
                m_string);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('m', '_', 'n', 'e', 's',
                    't', 'e', 'd') >::RESULT, m_nestedData);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('m', '_', 'b', 'o', 'o',
                    'l') >::RESULT, m_bool);

            d->read(
                CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                m_int);

            d->read(
                CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 's', 't', 'r') >::RESULT,
                m_string);

            return in;
        }

        const string toString() const {
            stringstream s;
            s << m_bool << endl << m_int << endl << m_string << endl
            << m_nestedData.toString();
            return s.str();
        }

        int32_t getID() const {
            return 0;
        }

        const string getLongName() const {
            return "DataStoreTestSampleData";
        }

        const string getShortName() const {
            return getLongName();
        }
};

class DataStoreTest : public CxxTest::TestSuite {
    public:

        void testDataStore() {
            KeyValueDataStore *ds = new KeyValueDataStore(std::shared_ptr<odcore::wrapper::KeyValueDatabase>(new MySimpleDB()));
            int32_t key1 = 1;
            TimeStamp ts1(0, 35);
            Container v1(ts1);
            ds->put(key1, v1);

            Container v2;
            v2 = ds->get(key1);
            TimeStamp ts2;
            ts2 = v2.getData<TimeStamp>();
            TS_ASSERT(ts1.toString() == ts2.toString());

            // Test for no entry.
            Container v3 = ds->get(key1 - 1);
            TS_ASSERT(v3.getDataType() == Container::UNDEFINEDDATA);

            // Clean up.
            delete ds;
        }

        void testMassData() {
            KeyValueDataStore *ds = new KeyValueDataStore(std::shared_ptr<odcore::wrapper::KeyValueDatabase>(new MySimpleDB()));

            const uint32_t size = 4096;
            // Generate data.
            Container *c = new Container[size];
            for (uint32_t i = 0; i < size; i++) {
                TimeStamp ts;
                c[i] = Container(ts);
                Thread::usleepFor(10);
            }
#ifndef WIN32
            long start = clock();
#endif
            for (uint32_t i = 0; i < size; i++) {
                ds->put(i, c[i]);
            }
#ifndef WIN32
            long end = clock();
            double duration = ((end - start) * 1000) / CLOCKS_PER_SEC;
            clog << size << " entries of type TIMESTAMP each containing "
                 << sizeof(c[0]) << " bytes stored in " << duration
                 << "ms." << endl;
#endif

#ifndef WIN32
            start = clock();
#endif
            for (uint32_t i = 0; i < size; i++) {
                TimeStamp retrievedTimeStamp = ds->get(i).getData<TimeStamp>();
                TimeStamp originalTimeStamp = c[i].getData<TimeStamp>();
                TS_ASSERT(originalTimeStamp.toMicroseconds() == retrievedTimeStamp.toMicroseconds());
            }
#ifndef WIN32
            end = clock();
            duration = ((end - start) * 1000) / CLOCKS_PER_SEC;
            clog << size
                 << " entries each containing " << sizeof(c[0]) << " bytes retrieved and compared in "
                 << duration << "ms." << endl;
#endif

            // Clean up.
            delete ds;
        }

        void testSerializationDeserialization() {
            KeyValueDataStore *ds = new KeyValueDataStore(std::shared_ptr<odcore::wrapper::KeyValueDatabase>(new MySimpleDB()));

            DataStoreTestSampleData sd1;
            sd1.m_bool = true;
            sd1.m_int = 42;
            sd1.m_nestedData.m_double = -21.54;
            sd1.m_string = "This is an example for marshalling data.";

            // This is only undefined data.
            Container c(sd1, Container::UNDEFINEDDATA);
            ds->put(1, c);

            Container c2 = ds->get(1);
            DataStoreTestSampleData sd2;
            sd2 = c2.getData<DataStoreTestSampleData>();

            TS_ASSERT(sd1.m_bool == sd2.m_bool);
            TS_ASSERT(sd1.m_int == sd2.m_int);
            TS_ASSERT(sd1.m_string == sd2.m_string);
            TS_ASSERT_DELTA(sd1.m_nestedData.m_double, sd2.m_nestedData.m_double, 1e-4);

            // Clean up.
            delete ds;
        }

        /**
         * This test case uses the SimpleDB for data interchange.
         */
        void testDataStoreForDataExchange() {
            bool failed = true;
            try {
                KeyValueDataStore *ds = new KeyValueDataStore(std::shared_ptr<odcore::wrapper::KeyValueDatabase>(new MySimpleDB()));

                DataStoreTestService s(*ds);
                s.start();

                TimeStamp ts;
                Container timeStampContainer(ts);
                DataStoreTestSampleData sd;
                Container undefinedDataContainer(sd, Container::UNDEFINEDDATA);

                for (int32_t i = 0; i < 10240; i++) {
                    Thread::usleepFor(10); // Allow the service to check for data.
#if defined(WIN32)
                    if (i < 1024*3) {
                        ds->put(0, timeStampContainer);
                    } else {
                        ds->put(0, undefinedDataContainer);
                    }
#else
                    double r = (random() % 100);
                    if (r < 51) {
                        ds->put(0, timeStampContainer);
                    } else {
                        ds->put(0, undefinedDataContainer);
                    }
#endif
                }

                s.stop();

                // Clean up.
                delete ds;

                TS_ASSERT(s.hasFound());

                failed = false;
            } catch (...) {

            }
            TS_ASSERT(!failed);
        }

};

#endif /*CORE_DATASTORESIMPLEDBTESTSUITE_H_*/
