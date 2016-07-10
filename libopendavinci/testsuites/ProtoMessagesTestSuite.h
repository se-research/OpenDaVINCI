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

#ifndef CORE_PROTOMESSAGESTESTSUITE_H_
#define CORE_PROTOMESSAGESTESTSUITE_H_

#include <cmath>                        // for fabs
#include <iostream>                     // for stringstream, operator<<, etc
#include <string>                       // for operator==, basic_string, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/ProtoDeserializerVisitor.h"
#include "opendavinci/odcore/base/ProtoSerializerVisitor.h"

#include "opendavincitestdata/generated/odcore/testdata/TestMessage1.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage2.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage3.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage4.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage5.h"

using namespace std;
using namespace odcore::base;
using namespace odcore::testdata;

class ProtoMessageTest : public CxxTest::TestSuite {
    public:
        void testSerializationDeserializationTestMessage1OneField() {
            TestMessage1 tm1;
            tm1.setField1(12);

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            tm1.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedDataWithHeader(out);


            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFromWithHeader(out);

            // Read back the data by using the visitor.
            TestMessage1 tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm1.getField1() == 12);
        }

        void testSerializationDeserializationTestMessage1CompleteOneField() {
            for (uint16_t i = 0; i <= 255; i++) {
                TestMessage1 tm1;
                tm1.setField1(i);

                // Create a Proto serialization visitor.
                ProtoSerializerVisitor protoSerializerVisitor;
                tm1.accept(protoSerializerVisitor);

                // Write the data to a stringstream.
                stringstream out;
                protoSerializerVisitor.getSerializedData(out);


                // Create a Proto deserialization visitor.
                ProtoDeserializerVisitor protoDeserializerVisitor;
                protoDeserializerVisitor.deserializeDataFrom(out);

                // Read back the data by using the visitor.
                TestMessage1 tm2;
                tm2.accept(protoDeserializerVisitor);

                TS_ASSERT(tm1.getField1() == tm2.getField1());
                TS_ASSERT(tm1.getField1() == i);
            }
        }

        void testSerializationDeserializationTestMessage1OneFieldGoogleExample() {
            TestMessage1 tm1;
            tm1.setField1(150);

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            tm1.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);

            // According to https://developers.google.com/protocol-buffers/docs/encoding, 150 will be encoded as 0x8 0x96 0x1.
            const string s = out.str();
            TS_ASSERT(s.size() == 3);
            TS_ASSERT(static_cast<uint8_t>(s.at(0)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(1)) == 0x96);
            TS_ASSERT(static_cast<uint8_t>(s.at(2)) == 0x1);

            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            TestMessage1 tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm1.getField1() == 150);
        }

        void testSerializationDeserializationTestMessage2TwoFieldsA() {
            TestMessage2 tm1;
            tm1.setField1(60);
            tm1.setField2(-60);

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            tm1.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);


            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            TestMessage2 tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm1.getField1() == 60);

            TS_ASSERT(tm1.getField2() == tm2.getField2());
            TS_ASSERT(tm1.getField2() == -60);
        }

        void testSerializationDeserializationTestMessage2TwoFieldsB() {
            TestMessage2 tm1;
            tm1.setField1(12);
            tm1.setField2(-12);

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            tm1.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);


            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            TestMessage2 tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm1.getField1() == 12);

            TS_ASSERT(tm1.getField2() == tm2.getField2());
            TS_ASSERT(tm1.getField2() == -12);
        }

        void testSerializationDeserializationTestMessage2Complete() {
            for(uint16_t i = 0; i <= 255; i++) {
                for(int16_t j = -127; j <= 127; j++) {
                    TestMessage2 tm1;
                    tm1.setField1(i);
                    tm1.setField2(j);

                    // Create a Proto serialization visitor.
                    ProtoSerializerVisitor protoSerializerVisitor;
                    tm1.accept(protoSerializerVisitor);

                    // Write the data to a stringstream.
                    stringstream out;
                    protoSerializerVisitor.getSerializedData(out);


                    // Create a Proto deserialization visitor.
                    ProtoDeserializerVisitor protoDeserializerVisitor;
                    protoDeserializerVisitor.deserializeDataFrom(out);

                    // Read back the data by using the visitor.
                    TestMessage2 tm2;
                    tm2.accept(protoDeserializerVisitor);

                    TS_ASSERT(tm1.getField1() == tm2.getField1());
                    TS_ASSERT(tm1.getField1() == i);

                    TS_ASSERT(tm1.getField2() == tm2.getField2());
                    TS_ASSERT(tm1.getField2() == j);
                }
            }
        }

        void testSerializationDeserializationTestMessage3OneFieldGoogleExample() {
            TestMessage3 tm1;
            tm1.setField1("testing");

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            tm1.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);

            // According to https://developers.google.com/protocol-buffers/docs/encoding, "testing" will be encoded as 0x12 0x07 0x74 0x65 0x73 0x74 0x69 0x6e 0x67.
            const string s = out.str();
            TS_ASSERT(s.size() == 9);
            TS_ASSERT(static_cast<uint8_t>(s.at(0)) == 0x12);
            TS_ASSERT(static_cast<uint8_t>(s.at(1)) == 0x7);
            TS_ASSERT(static_cast<uint8_t>(s.at(2)) == 0x74);
            TS_ASSERT(static_cast<uint8_t>(s.at(3)) == 0x65);
            TS_ASSERT(static_cast<uint8_t>(s.at(4)) == 0x73);
            TS_ASSERT(static_cast<uint8_t>(s.at(5)) == 0x74);
            TS_ASSERT(static_cast<uint8_t>(s.at(6)) == 0x69);
            TS_ASSERT(static_cast<uint8_t>(s.at(7)) == 0x6e);
            TS_ASSERT(static_cast<uint8_t>(s.at(8)) == 0x67);

            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            TestMessage3 tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm1.getField1() == "testing");
        }

        void testSerializationDeserializationTestMessage4OneFieldGoogleExample() {
            TestMessage4 tm1;
            TestMessage1 tm1Embedded;
            tm1Embedded.setField1(150);
            tm1.setField1(tm1Embedded);

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            tm1.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);

            // According to https://developers.google.com/protocol-buffers/docs/encoding, 0x1a 0x03 0x08 0x96 0x01.
            const string s = out.str();
            TS_ASSERT(s.size() == 5);
            TS_ASSERT(static_cast<uint8_t>(s.at(0)) == 0x1a);
            TS_ASSERT(static_cast<uint8_t>(s.at(1)) == 0x3);
            TS_ASSERT(static_cast<uint8_t>(s.at(2)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(3)) == 0x96);
            TS_ASSERT(static_cast<uint8_t>(s.at(4)) == 0x1);

            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            TestMessage4 tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getField1().getField1() == tm2.getField1().getField1());
            TS_ASSERT(tm1.getField1().getField1() == 150);
        }

        void testSerializationDeserializationTestMessage5() {
            TestMessage5 tm1;
            TS_ASSERT(tm1.getField1() == 1);
            TS_ASSERT(tm1.getField2() == -1);
            TS_ASSERT(tm1.getField3() == 100);
            TS_ASSERT(tm1.getField4() == -100);
            TS_ASSERT(tm1.getField5() == 10000);
            TS_ASSERT(tm1.getField6() == -10000);
            TS_ASSERT(tm1.getField7() == 12345);
            TS_ASSERT(tm1.getField8() == -12345);
            TS_ASSERT_DELTA(tm1.getField9(), -1.2345, 1e-4);
            TS_ASSERT_DELTA(tm1.getField10(), -10.2345, 1e-4);
            TS_ASSERT(tm1.getField11() == "Hello World!");
            TS_ASSERT(tm1.getField12().getField1() == 12);

            TestMessage1 tm1Embedded;
            tm1Embedded.setField1(150);
            tm1.setField12(tm1Embedded);

            tm1.setField1(3);
            tm1.setField2(-3);
            tm1.setField3(103);
            tm1.setField4(-103);
            tm1.setField5(10003);
            tm1.setField6(-10003);
            tm1.setField7(54321);
            tm1.setField8(-54321);
            tm1.setField9(-5.4321);
            tm1.setField10(-50.4321);
            tm1.setField11("Hello OpenDaVINCI World!");

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            tm1.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);


            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Create a new message instance.
            TestMessage5 tm2;
            TS_ASSERT(tm2.getField1() == 1);
            TS_ASSERT(tm2.getField2() == -1);
            TS_ASSERT(tm2.getField3() == 100);
            TS_ASSERT(tm2.getField4() == -100);
            TS_ASSERT(tm2.getField5() == 10000);
            TS_ASSERT(tm2.getField6() == -10000);
            TS_ASSERT(tm2.getField7() == 12345);
            TS_ASSERT(tm2.getField8() == -12345);
            TS_ASSERT_DELTA(tm2.getField9(), -1.2345, 1e-4);
            TS_ASSERT_DELTA(tm2.getField10(), -10.2345, 1e-4);
            TS_ASSERT(tm2.getField11() == "Hello World!");
            TS_ASSERT(tm2.getField12().getField1() == 12);

            // Read back the data by using the visitor.
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm2.getField1() == 3);
            TS_ASSERT(tm2.getField2() == -3);
            TS_ASSERT(tm2.getField3() == 103);
            TS_ASSERT(tm2.getField4() == -103);
            TS_ASSERT(tm2.getField5() == 10003);
            TS_ASSERT(tm2.getField6() == -10003);
            TS_ASSERT(tm2.getField7() == 54321);
            TS_ASSERT(tm2.getField8() == -54321);
            TS_ASSERT_DELTA(tm2.getField9(), -5.4321, 1e-4);
            TS_ASSERT_DELTA(tm2.getField10(), -50.4321, 1e-4);
            TS_ASSERT(tm2.getField11() == "Hello OpenDaVINCI World!");
            TS_ASSERT(tm2.getField12().getField1() == 150);

            TS_ASSERT(tm2.getField1() == tm1.getField1());
            TS_ASSERT(tm2.getField2() == tm1.getField2());
            TS_ASSERT(tm2.getField3() == tm1.getField3());
            TS_ASSERT(tm2.getField4() == tm1.getField4());
            TS_ASSERT(tm2.getField5() == tm1.getField5());
            TS_ASSERT(tm2.getField6() == tm1.getField6());
            TS_ASSERT(tm2.getField7() == tm1.getField7());
            TS_ASSERT(tm2.getField8() == tm1.getField8());
            TS_ASSERT_DELTA(tm2.getField9(), tm1.getField9(), 1e-4);
            TS_ASSERT_DELTA(tm2.getField10(), tm1.getField10(), 1e-4);
            TS_ASSERT(tm2.getField11() == tm1.getField11());
            TS_ASSERT(tm2.getField12().getField1() == tm1.getField12().getField1());
        }
};

#endif /*CORE_PROTOMESSAGESTESTSUITE_H_*/
