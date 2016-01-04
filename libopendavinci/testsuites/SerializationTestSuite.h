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
#include <string>                       // for string, operator<<, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "core/opendavinci.h"
#include "core/SharedPointer.h"         // for SharedPointer
#include "core/base/Deserializer.h"     // for Deserializer
#include "core/base/Hash.h"             // for CharList, CRC32, etc
#include "core/base/Serializable.h"     // for Serializable, operator<<, etc
#include "core/base/SerializationFactory.h"  // for SerializationFactory
#include "core/base/Serializer.h"       // for Serializer

using namespace std;
using namespace core;
using namespace core::base;

class SerializationTestNestedData : public core::base::Serializable {
    public:
        SerializationTestNestedData() :
                m_double(0) {}

        double m_double;

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            core::SharedPointer<Serializer> s = sf.getSerializer(out);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('m', '_', 'd', 'o', 'u', 'b', 'l', 'e') >::RESULT,
                    m_double);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('m', '_', 'd', 'o', 'u', 'b', 'l', 'e') >::RESULT,
                   m_double);

            return in;
        }
};

class SerializationTestSampleData : public core::base::Serializable {
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

            core::SharedPointer<Serializer> s = sf.getSerializer(out);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('m', '_', 'b', 'o', 'o', 'l') >::RESULT,
                    m_bool);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('m', '_', 'n', 'e', 's', 't', 'e', 'd') >::RESULT,
                    m_nestedData);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                    m_int);

            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 's', 't', 'r') >::RESULT,
                    m_string);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('m', '_', 'n', 'e', 's', 't', 'e', 'd') >::RESULT,
                   m_nestedData);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 's', 't', 'r') >::RESULT,
                   m_string);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                   m_int);

            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('m', '_', 'b', 'o', 'o', 'l') >::RESULT,
                   m_bool);

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

        void testArraySerialisation()
        {
            stringstream stream;
            uint32_t array[10];
            for (uint32_t i=0; i<10; ++i)
            {
                array[i] = i;
            }

            SerializationFactory& sf=SerializationFactory::getInstance();

            {
                SharedPointer<Serializer> s = sf.getSerializer(stream);
                s->write(1, &array, 10);
            }


            SharedPointer<Deserializer> d = sf.getDeserializer(stream);
            uint32_t deserializedArray[10];
            d->read(1, &deserializedArray, 10);

            for (uint32_t i=0; i<10; ++i)
            {
                TS_WARN(deserializedArray[i] == i);
                clog << "Is: " << deserializedArray[i] << ", Should: " << i << endl;
            }

        }
};

#endif /*CORE_SERIALIZATIONTESTSUITE_H_*/
