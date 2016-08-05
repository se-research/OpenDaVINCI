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

#ifndef CORE_SERIALIZATIONTESTSUITE_H_
#define CORE_SERIALIZATIONTESTSUITE_H_

#include <cmath>                        // for sqrt
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <memory>
#include <string>                       // for string, operator<<, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"     // for Deserializer
#include "opendavinci/odcore/serialization/Serializable.h"     // for Serializable, operator<<, etc
#include "opendavinci/odcore/serialization/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/odcore/serialization/Serializer.h"       // for Serializer

using namespace std;
using namespace odcore;
using namespace odcore::base;

class SerializationTestNestedData : public odcore::serialization::Serializable {
    public:
        SerializationTestNestedData() :
                m_double(0) {}

        double m_double;

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(1, m_double);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(1, m_double);

            return in;
        }
};

class SerializationTestSampleData : public odcore::serialization::Serializable {
    public:
        SerializationTestSampleData() :
                m_bool(false),
                m_int(0),
                m_string(""),
                m_nestedData() {}

        bool m_bool;
        int32_t m_int;
        string m_string;
        SerializationTestNestedData m_nestedData;

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(1, m_bool);

            s->write(2, m_nestedData);

            s->write(3, m_int);

            s->write(4, m_string);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(1, m_bool);

            d->read(2, m_nestedData);

            d->read(3, m_int);

            d->read(4, m_string);

            return in;
        }
};


class SerializationTest : public CxxTest::TestSuite {
    public:
        void testSerializationDeserialization() {
            // Create some data.
            SerializationTestSampleData sd;
            sd.m_bool = true;
            sd.m_int = 42;
            sd.m_nestedData.m_double = -42.42;
            sd.m_string = "This is an example.";

            // Create a data sink.
            stringstream inout("testoutput");
            inout << sd;
            inout.flush();

            // Read from the previously created data sink.
            SerializationTestSampleData sd2;
            inout >> sd2;

            TS_ASSERT(sd2.m_bool);
            TS_ASSERT(sd2.m_int == 42);
            TS_ASSERT(sd2.m_string == "This is an example.");
            TS_ASSERT_DELTA(sd2.m_nestedData.m_double, -42.42, 1e-5);
        }
};

#endif /*CORE_SERIALIZATIONTESTSUITE_H_*/
