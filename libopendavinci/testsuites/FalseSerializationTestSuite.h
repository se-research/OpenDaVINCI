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

#ifndef CORE_FALSESERIALIZATIONTESTSUITE_H_
#define CORE_FALSESERIALIZATIONTESTSUITE_H_

#include <iostream>                     // for stringstream, istream, etc
#include <string>                       // for operator==, string, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include <memory>
#include "opendavinci/odcore/base/Deserializer.h"     // for Deserializer
#include "opendavinci/odcore/base/Hash.h"             // for CharList, CRC32, etc
#include "opendavinci/odcore/base/Serializable.h"     // for operator<<, operator>>, etc
#include "opendavinci/odcore/base/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/odcore/base/Serializer.h"       // for Serializer
#include "opendavinci/odcore/data/TimeStamp.h"        // for TimeStamp

using namespace std;
using namespace odcore::base;
using namespace odcore::data;

class FalseSerializationTestSuiteNestedData : public odcore::base::Serializable {
    public:
        FalseSerializationTestSuiteNestedData() :
                m_string("BlaBla") {}

        string m_string;

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'e', 's', 't') >::RESULT,
                    m_string);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'e', 's', 't') >::RESULT,
                   m_string);

            return in;
        }
};

class FalseSerializationTestSuiteSampleData : public odcore::base::Serializable {
    public:
        FalseSerializationTestSuiteSampleData() :
                m_string("Bla"), m_nestedData() {}

        string m_string;
        FalseSerializationTestSuiteNestedData m_nestedData;

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'e', 's', 't') >::RESULT,
                    m_string);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('n', 'e', 's', 't', 'e', 'd') >::RESULT,
                    m_nestedData);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'e', 's', 't') >::RESULT,
                   m_string);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('n', 'e', 's', 't', 'e', 'd') >::RESULT,
                   m_nestedData);

            return in;
        }
};

class FalseSerializationTest : public CxxTest::TestSuite {
    public:
        void testSerializationDeserialization() {
            // Create some data.
            FalseSerializationTestSuiteSampleData sd;
            sd.m_string = "RealData";
            sd.m_nestedData.m_string = "NestedData";

            // Create a data sink.
            stringstream inout;
            inout << sd;
            inout.flush();

            // Read from the previously created data sink.
            FalseSerializationTestSuiteSampleData sd2;
            inout >> sd2;

            TS_ASSERT(sd2.m_string == "RealData");
            TS_ASSERT(sd2.m_nestedData.m_string == "NestedData");
        }

        void testTimeStamp35() {
            // This test case yielded an error if the payload contains a '#' sign in the last few bytes.
            stringstream sstr;
            TimeStamp ts1(0, 35);
            sstr << ts1;

            TimeStamp ts2;
            sstr >> ts2;
            TS_ASSERT(ts1.toMicroseconds() == ts2.toMicroseconds());
            TS_ASSERT(ts1.toString() == ts2.toString());
        }
};

#endif /*CORE_FALSESERIALIZATIONTESTSUITE_H_*/
