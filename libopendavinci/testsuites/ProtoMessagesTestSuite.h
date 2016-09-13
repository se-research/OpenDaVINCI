/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2016 Christian Berger
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
#include <vector>

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/ProtoDeserializer.h"
#include "opendavinci/odcore/serialization/ProtoSerializer.h"
#include "opendavinci/odcore/serialization/ProtoDeserializerVisitor.h"
#include "opendavinci/odcore/serialization/ProtoSerializerVisitor.h"

#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"

#include "opendavinci/generated/odcore/data/LogMessage.h"
#include "opendavinci/generated/odcore/data/reflection/AbstractField.h"
#include "opendavinci/generated/odcore/data/dmcp/ServerInformation.h"
#include "opendavinci/generated/odcore/data/dmcp/DiscoverMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/odcore/data/dmcp/RuntimeStatistic.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStatistic.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStatistics.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStateMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleExitCodeMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/PulseAckMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/PulseMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/PulseAckContainersMessage.h"
#include "opendavinci/generated/odcore/data/Configuration.h"
#include "opendavinci/generated/odcore/data/buffer/MemorySegment.h"
#include "opendavinci/generated/odcore/data/player/PlayerCommand.h"
#include "opendavinci/generated/odcore/data/recorder/RecorderCommand.h"
#include "opendavinci/generated/odcore/data/SharedData.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"
#include "opendavinci/generated/odcore/data/SharedPointCloud.h"

#include "opendavincitestdata/generated/odcore/testdata/TestMessage1.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage2.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage3.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage4.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage5.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage6.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage7.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage8.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage9.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage10.h"

using namespace std;
using namespace odcore::base;
using namespace odcore::data;
using namespace odcore::data::buffer;
using namespace odcore::data::dmcp;
using namespace odcore::data::image;
using namespace odcore::data::player;
using namespace odcore::data::recorder;
using namespace odcore::data::reflection;
using namespace odcore::testdata;
using namespace odcore::serialization;

class SerializationFactoryTestCase : public SerializationFactory {
    public:
        SerializationFactoryTestCase() {
            SerializationFactory::m_singleton = this;
        }

        virtual ~SerializationFactoryTestCase() {
            SerializationFactory::m_singleton = NULL;
        }

        virtual shared_ptr<Serializer> getSerializer(ostream &out) const {
            return shared_ptr<Serializer>(new ProtoSerializer(out));
        }

        virtual shared_ptr<Deserializer> getDeserializer(istream &in) const {
            return shared_ptr<Deserializer>(new ProtoDeserializer(in));
        }
};

class ProtoMessages1SampleDataVersion1 : public odcore::serialization::Serializable {
    public:
        ProtoMessages1SampleDataVersion1() :
            m_bool(false) {}

        bool m_bool;

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(1, m_bool);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(1, m_bool);

            return in;
        }
};

class ProtoMessages1SampleDataVersion2 : public odcore::serialization::Serializable {
    public:
        ProtoMessages1SampleDataVersion2() :
            m_bool(false),
            m_int(37),
            m_string("Hello World") {}

        bool m_bool;
        int32_t m_int;
        string m_string;

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(1, m_bool);

            s->write(2, m_int);

            s->write(3, m_string);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(1, m_bool);

            d->read(2, m_int);

            d->read(3, m_string);

            return in;
        }
};

class ProtoMessages1SampleDataVersion2Reordered : public odcore::serialization::Serializable {
    public:
        ProtoMessages1SampleDataVersion2Reordered() :
            m_bool(false),
            m_int(20),
            m_string("") {}

        bool m_bool;
        int32_t m_int;
        string m_string;

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(1, m_bool);

            s->write(2, m_int);

            s->write(3, m_string);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(2, m_int);

            d->read(1, m_bool);

            d->read(3, m_string);

            return in;
        }
};

class ProtoMessageTest : public CxxTest::TestSuite {
    public:
        void testSerializationDeserializationTestMessage1OneField() {
            TestMessage1 tm1;
            tm1.setField1(13);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read from buffer.
            TestMessage1 tm2;
            out >> tm2;

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm2.getField1() == 13);
        }

        void testSerializationDeserializationTestMessage1OneFieldContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            TestMessage1 tm1;
            tm1.setField1(13);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read from buffer.
            Container c2;
            out >> c2;

            TS_ASSERT(c2.getDataType() == TestMessage1::ID());

            TestMessage1 tm2 = c2.getData<TestMessage1>();
            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm2.getField1() == 13);
        }

        void testSerializationDeserializationTestMessage1OneFieldVisitor() {
            TestMessage1 tm1;
            tm1.setField1(11);

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
            TS_ASSERT(tm2.getField1() == 11);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage1CompleteOneField() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            for (uint16_t i = 0; i <= 255; i++) {
                TestMessage1 tm1;
                tm1.setField1(i);

                // Serialize via regular Serializer.
                stringstream out;
                out << tm1;

                // Read from buffer.
                TestMessage1 tm2;
                out >> tm2;

                TS_ASSERT(tm1.getField1() == tm2.getField1());
                TS_ASSERT(tm2.getField1() == i);
            }
        }

        void testSerializationDeserializationTestMessage1CompleteOneFieldContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            for (uint16_t i = 0; i <= 255; i++) {
                TestMessage1 tm1;
                tm1.setField1(i);

                Container c(tm1);

                // Serialize via regular Serializer.
                stringstream out;
                out << c;

                // Read from buffer.
                Container c2;
                out >> c2;
                TS_ASSERT(c2.getDataType() == TestMessage1::ID());

                TestMessage1 tm2 = c2.getData<TestMessage1>();

                TS_ASSERT(tm1.getField1() == tm2.getField1());
                TS_ASSERT(tm2.getField1() == i);
            }
        }

        void testSerializationDeserializationTestMessage1CompleteOneFieldVisitor() {
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
                TS_ASSERT(tm2.getField1() == i);
            }
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage1OneFieldGoogleExample() {
            TestMessage1 tm1;
            tm1.setField1(150);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // According to https://developers.google.com/protocol-buffers/docs/encoding, 150 will be encoded as 0x8 0x96 0x1.
            const string s = out.str();
            TS_ASSERT(s.size() == 3);
            TS_ASSERT(static_cast<uint8_t>(s.at(0)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(1)) == 0x96);
            TS_ASSERT(static_cast<uint8_t>(s.at(2)) == 0x1);

            // Read from buffer.
            TestMessage1 tm2;
            out >> tm2;

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm2.getField1() == 150);
        }

        void testSerializationDeserializationTestMessage1OneFieldGoogleExampleVisitor() {
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
            TS_ASSERT(tm2.getField1() == 150);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage2TwoFieldsA() {
            TestMessage2 tm1;
            tm1.setField1(60);
            tm1.setField2(-60);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read from buffer.
            TestMessage2 tm2;
            out >> tm2;

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm2.getField1() == 60);

            TS_ASSERT(tm1.getField2() == tm2.getField2());
            TS_ASSERT(tm2.getField2() == -60);
        }


        void testSerializationDeserializationTestMessage2TwoFieldsAValidatedWithGoogleProtobuf() {
            TestMessage2 tm1;
            tm1.setField1(123);
            tm1.setField2(-123);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            const string s = out.str();
            TS_ASSERT(s.size() == 5);
            TS_ASSERT(static_cast<uint8_t>(s.at(0)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(1)) == 0x7b);
            TS_ASSERT(static_cast<uint8_t>(s.at(2)) == 0x10);
            TS_ASSERT(static_cast<uint8_t>(s.at(3)) == 0xf5);
            TS_ASSERT(static_cast<uint8_t>(s.at(4)) == 0x1);

            // Read from buffer.
            TestMessage2 tm2;
            out >> tm2;

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm2.getField1() == 123);

            TS_ASSERT(tm1.getField2() == tm2.getField2());
            TS_ASSERT(tm2.getField2() == -123);
        }

        void testSerializationDeserializationTestMessage2TwoFieldsAContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            TestMessage2 tm1;
            tm1.setField1(60);
            tm1.setField2(-60);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read from buffer.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == TestMessage2::ID());

            TestMessage2 tm2 = c2.getData<TestMessage2>();

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm2.getField1() == 60);

            TS_ASSERT(tm1.getField2() == tm2.getField2());
            TS_ASSERT(tm2.getField2() == -60);
        }

        void testSerializationDeserializationTestMessage2TwoFieldsAVisitor() {
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
            TS_ASSERT(tm2.getField1() == 60);

            TS_ASSERT(tm1.getField2() == tm2.getField2());
            TS_ASSERT(tm2.getField2() == -60);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage2TwoFieldsB() {
            TestMessage2 tm1;
            tm1.setField1(12);
            tm1.setField2(-12);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read from buffer.
            TestMessage2 tm2;
            out >> tm2;

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm2.getField1() == 12);

            TS_ASSERT(tm1.getField2() == tm2.getField2());
            TS_ASSERT(tm2.getField2() == -12);
        }

        void testSerializationDeserializationTestMessage2TwoFieldsBContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            TestMessage2 tm1;
            tm1.setField1(12);
            tm1.setField2(-12);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read from buffer.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == TestMessage2::ID());

            TestMessage2 tm2 = c2.getData<TestMessage2>();

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm2.getField1() == 12);

            TS_ASSERT(tm1.getField2() == tm2.getField2());
            TS_ASSERT(tm2.getField2() == -12);
        }

        void testSerializationDeserializationTestMessage2TwoFieldsBVisitor() {
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
            TS_ASSERT(tm2.getField1() == 12);

            TS_ASSERT(tm1.getField2() == tm2.getField2());
            TS_ASSERT(tm2.getField2() == -12);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage2Complete() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            for(uint16_t i = 0; i <= 255; i++) {
                for(int16_t j = -127; j <= 127; j++) {
                    TestMessage2 tm1;
                    tm1.setField1(i);
                    tm1.setField2(j);

                    // Serialize via regular Serializer.
                    stringstream out;
                    out << tm1;

                    // Read from buffer.
                    TestMessage2 tm2;
                    out >> tm2;

                    TS_ASSERT(tm1.getField1() == tm2.getField1());
                    TS_ASSERT(tm2.getField1() == i);

                    TS_ASSERT(tm1.getField2() == tm2.getField2());
                    TS_ASSERT(tm2.getField2() == j);
                }
            }
        }

        void testSerializationDeserializationTestMessage2CompleteContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            for(uint16_t i = 0; i <= 255; i++) {
                for(int16_t j = -127; j <= 127; j++) {
                    TestMessage2 tm1;
                    tm1.setField1(i);
                    tm1.setField2(j);

                    Container c(tm1);

                    // Serialize via regular Serializer.
                    stringstream out;
                    out << c;

                    // Read from buffer.
                    Container c2;
                    out >> c2;
                    TS_ASSERT(c2.getDataType() == TestMessage2::ID());

                    TestMessage2 tm2 = c2.getData<TestMessage2>();

                    TS_ASSERT(tm1.getField1() == tm2.getField1());
                    TS_ASSERT(tm2.getField1() == i);

                    TS_ASSERT(tm1.getField2() == tm2.getField2());
                    TS_ASSERT(tm2.getField2() == j);
                }
            }
        }

        void testSerializationDeserializationTestMessage2CompleteVisitor() {
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
                    TS_ASSERT(tm2.getField1() == i);

                    TS_ASSERT(tm1.getField2() == tm2.getField2());
                    TS_ASSERT(tm2.getField2() == j);
                }
            }
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage3OneFieldGoogleExample() {
            TestMessage3 tm1;
            tm1.setField1("testing");

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

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

            // Read from buffer.
            TestMessage3 tm2;
            out >> tm2;

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm1.getField1() == "testing");
        }

        void testSerializationDeserializationTestMessage3OneFieldGoogleExampleVisitor() {
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

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage4OneFieldGoogleExample() {
            TestMessage4 tm1;
            TestMessage1 tm1Embedded;
            tm1Embedded.setField1(150);
            tm1.setField1(tm1Embedded);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // According to https://developers.google.com/protocol-buffers/docs/encoding, 0x1a 0x03 0x08 0x96 0x01.
            const string s = out.str();
            TS_ASSERT(s.size() == 5);
            TS_ASSERT(static_cast<uint8_t>(s.at(0)) == 0x1a);
            TS_ASSERT(static_cast<uint8_t>(s.at(1)) == 0x3);
            TS_ASSERT(static_cast<uint8_t>(s.at(2)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(3)) == 0x96);
            TS_ASSERT(static_cast<uint8_t>(s.at(4)) == 0x1);

            // Read from buffer.
            TestMessage4 tm2;
            out >> tm2;

            TS_ASSERT(tm1.getField1().getField1() == tm2.getField1().getField1());
            TS_ASSERT(tm1.getField1().getField1() == 150);
        }

        void testSerializationDeserializationTestMessage4OneFieldGoogleExampleVisitor() {
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

        ///////////////////////////////////////////////////////////////////////

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

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

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

            // Read from buffer.
            out >> tm2;

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

        void testSerializationDeserializationTestMessage5ValidatedWithGoogleProtobuf() {
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

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            const string s = out.str();
            TS_ASSERT(s.size() == 69);
            uint32_t cnt = 0;
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x3);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x10);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x5);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x18);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x67);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x20);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xcd);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x1);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x28);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x93);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x4e);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x30);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xa5);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x9c);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x1);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x38);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xb1);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xa8);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x3);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x40);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xe1);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xd0);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x6);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x4d);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xc3);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xd3);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xad);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xc0);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x51);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x1);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x4d);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x84);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xd);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x4f);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x37);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x49);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xc0);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x5a);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x18);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x48);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x65);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x6c);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x6c);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x6f);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x20);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x4f);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x70);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x65);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x6e);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x44);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x61);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x56);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x49);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x4e);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x43);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x49);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x20);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x57);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x6f);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x72);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x6c);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x64);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x21);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x62);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x3);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x96);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x1);

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

            // Read from buffer.
            out >> tm2;

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

        void testSerializationDeserializationTestMessage5Container() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

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

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

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

            // Read from buffer.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == TestMessage5::ID());
            tm2 = c2.getData<TestMessage5>();

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

        void testSerializationDeserializationTestMessage5Visitor() {
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

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationLogMessage() {
            LogMessage tm1;
            tm1.setLogLevel(LogMessage::WARN);
            tm1.setLogMessage("This is a test message!");
            tm1.setComponentName("Component ABC");

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            LogMessage tm2;
            out >> tm2;

            TS_ASSERT(tm1.getLogLevel() == tm2.getLogLevel());
            TS_ASSERT(tm2.getLogLevel() == LogMessage::WARN);

            TS_ASSERT(tm1.getLogMessage() == tm2.getLogMessage());
            TS_ASSERT(tm2.getLogMessage() == "This is a test message!");

            TS_ASSERT(tm1.getComponentName() == tm2.getComponentName());
            TS_ASSERT(tm2.getComponentName() == "Component ABC");
        }

        void testSerializationDeserializationLogMessageContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            LogMessage tm1;
            tm1.setLogLevel(LogMessage::WARN);
            tm1.setLogMessage("This is a test message!");
            tm1.setComponentName("Component ABC");

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == LogMessage::ID());

            LogMessage tm2 = c2.getData<LogMessage>();

            TS_ASSERT(tm1.getLogLevel() == tm2.getLogLevel());
            TS_ASSERT(tm2.getLogLevel() == LogMessage::WARN);

            TS_ASSERT(tm1.getLogMessage() == tm2.getLogMessage());
            TS_ASSERT(tm2.getLogMessage() == "This is a test message!");

            TS_ASSERT(tm1.getComponentName() == tm2.getComponentName());
            TS_ASSERT(tm2.getComponentName() == "Component ABC");
        }

        void testSerializationDeserializationLogMessageVisitor() {
            LogMessage tm1;
            tm1.setLogLevel(LogMessage::WARN);
            tm1.setLogMessage("This is a test message!");
            tm1.setComponentName("Component ABC");

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
            LogMessage tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getLogLevel() == tm2.getLogLevel());
            TS_ASSERT(tm2.getLogLevel() == LogMessage::WARN);

            TS_ASSERT(tm1.getLogMessage() == tm2.getLogMessage());
            TS_ASSERT(tm2.getLogMessage() == "This is a test message!");

            TS_ASSERT(tm1.getComponentName() == tm2.getComponentName());
            TS_ASSERT(tm2.getComponentName() == "Component ABC");
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationAbstractField() {
            AbstractField tm1;
            tm1.setFieldIdentifier(123);
            tm1.setLongFieldName("odcore.data.reflection.AbstractField");
            tm1.setShortFieldName("AbstractField");
            tm1.setFieldDataType(AbstractField::INT8_T);
            tm1.setSize(-12);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            AbstractField tm2;
            out >> tm2;

            TS_ASSERT(tm1.getFieldIdentifier() == tm2.getFieldIdentifier());
            TS_ASSERT(tm2.getFieldIdentifier() == 123);

            TS_ASSERT(tm1.getLongFieldName() == tm2.getLongFieldName());
            TS_ASSERT(tm2.getLongFieldName() == "odcore.data.reflection.AbstractField");

            TS_ASSERT(tm1.getShortFieldName() == tm2.getShortFieldName());
            TS_ASSERT(tm2.getShortFieldName() == "AbstractField");

            TS_ASSERT(tm1.getFieldDataType() == tm2.getFieldDataType());
            TS_ASSERT(tm2.getFieldDataType() == AbstractField::INT8_T);

            TS_ASSERT(tm1.getSize() == tm2.getSize());
            TS_ASSERT(tm2.getSize() == -12);
        }

        void testSerializationDeserializationAbstractFieldContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            AbstractField tm1;
            tm1.setFieldIdentifier(123);
            tm1.setLongFieldName("odcore.data.reflection.AbstractField");
            tm1.setShortFieldName("AbstractField");
            tm1.setFieldDataType(AbstractField::INT8_T);
            tm1.setSize(-12);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == AbstractField::ID());

            AbstractField tm2 = c2.getData<AbstractField>();

            TS_ASSERT(tm1.getFieldIdentifier() == tm2.getFieldIdentifier());
            TS_ASSERT(tm2.getFieldIdentifier() == 123);

            TS_ASSERT(tm1.getLongFieldName() == tm2.getLongFieldName());
            TS_ASSERT(tm2.getLongFieldName() == "odcore.data.reflection.AbstractField");

            TS_ASSERT(tm1.getShortFieldName() == tm2.getShortFieldName());
            TS_ASSERT(tm2.getShortFieldName() == "AbstractField");

            TS_ASSERT(tm1.getFieldDataType() == tm2.getFieldDataType());
            TS_ASSERT(tm2.getFieldDataType() == AbstractField::INT8_T);

            TS_ASSERT(tm1.getSize() == tm2.getSize());
            TS_ASSERT(tm2.getSize() == -12);
        }

        void testSerializationDeserializationAbstractFieldVisitor() {
            AbstractField tm1;
            tm1.setFieldIdentifier(123);
            tm1.setLongFieldName("odcore.data.reflection.AbstractField");
            tm1.setShortFieldName("AbstractField");
            tm1.setFieldDataType(AbstractField::INT8_T);
            tm1.setSize(-12);

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
            AbstractField tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getFieldIdentifier() == tm2.getFieldIdentifier());
            TS_ASSERT(tm2.getFieldIdentifier() == 123);

            TS_ASSERT(tm1.getLongFieldName() == tm2.getLongFieldName());
            TS_ASSERT(tm2.getLongFieldName() == "odcore.data.reflection.AbstractField");

            TS_ASSERT(tm1.getShortFieldName() == tm2.getShortFieldName());
            TS_ASSERT(tm2.getShortFieldName() == "AbstractField");

            TS_ASSERT(tm1.getFieldDataType() == tm2.getFieldDataType());
            TS_ASSERT(tm2.getFieldDataType() == AbstractField::INT8_T);

            TS_ASSERT(tm1.getSize() == tm2.getSize());
            TS_ASSERT(tm2.getSize() == -12);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationServerInformation() {
            ServerInformation tm1;
            tm1.setIP("123.456.789.abc");
            tm1.setPort(7890);
            tm1.setManagedLevel(ServerInformation::ML_PULSE_TIME_ACK);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            ServerInformation tm2;
            out >> tm2;

            TS_ASSERT(tm1.getIP() == tm2.getIP());
            TS_ASSERT(tm2.getIP() == "123.456.789.abc");

            TS_ASSERT(tm1.getPort() == tm2.getPort());
            TS_ASSERT(tm2.getPort() == 7890);

            TS_ASSERT(tm1.getManagedLevel() == tm2.getManagedLevel());
            TS_ASSERT(tm2.getManagedLevel() == ServerInformation::ML_PULSE_TIME_ACK);
        }

        void testSerializationDeserializationServerInformationContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            ServerInformation tm1;
            tm1.setIP("123.456.789.abc");
            tm1.setPort(7890);
            tm1.setManagedLevel(ServerInformation::ML_PULSE_TIME_ACK);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == ServerInformation::ID());

            ServerInformation tm2 = c2.getData<ServerInformation>();

            TS_ASSERT(tm1.getIP() == tm2.getIP());
            TS_ASSERT(tm2.getIP() == "123.456.789.abc");

            TS_ASSERT(tm1.getPort() == tm2.getPort());
            TS_ASSERT(tm2.getPort() == 7890);

            TS_ASSERT(tm1.getManagedLevel() == tm2.getManagedLevel());
            TS_ASSERT(tm2.getManagedLevel() == ServerInformation::ML_PULSE_TIME_ACK);
        }

        void testSerializationDeserializationServerInformationVisitor() {
            ServerInformation tm1;
            tm1.setIP("123.456.789.abc");
            tm1.setPort(7890);
            tm1.setManagedLevel(ServerInformation::ML_PULSE_TIME_ACK);

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
            ServerInformation tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getIP() == tm2.getIP());
            TS_ASSERT(tm2.getIP() == "123.456.789.abc");

            TS_ASSERT(tm1.getPort() == tm2.getPort());
            TS_ASSERT(tm2.getPort() == 7890);

            TS_ASSERT(tm1.getManagedLevel() == tm2.getManagedLevel());
            TS_ASSERT(tm2.getManagedLevel() == ServerInformation::ML_PULSE_TIME_ACK);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationDiscoverMessage() {
            ServerInformation tm1;
            tm1.setIP("456.789.abc.123");
            tm1.setPort(456);
            tm1.setManagedLevel(ServerInformation::ML_PULSE_TIME);

            DiscoverMessage dm;
            dm.setType(DiscoverMessage::RESPONSE);
            dm.setServerInformation(tm1);
            dm.setModuleName("TestComponent");

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << dm;

            // Read back the data.
            DiscoverMessage dm2;
            out >> dm2;

            TS_ASSERT(dm.getServerInformation().getIP() == dm2.getServerInformation().getIP());
            TS_ASSERT(dm2.getServerInformation().getIP() == "456.789.abc.123");

            TS_ASSERT(dm.getServerInformation().getPort() == dm2.getServerInformation().getPort());
            TS_ASSERT(dm2.getServerInformation().getPort() == 456);

            TS_ASSERT(dm.getServerInformation().getManagedLevel() == dm2.getServerInformation().getManagedLevel());
            TS_ASSERT(dm2.getServerInformation().getManagedLevel() == ServerInformation::ML_PULSE_TIME);

            TS_ASSERT(dm.getType() == dm2.getType());
            TS_ASSERT(dm2.getType() == DiscoverMessage::RESPONSE);

            TS_ASSERT(dm.getModuleName() == dm2.getModuleName());
            TS_ASSERT(dm2.getModuleName() == "TestComponent");
        }

        void testSerializationDeserializationDiscoverMessageContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            ServerInformation tm1;
            tm1.setIP("456.789.abc.123");
            tm1.setPort(456);
            tm1.setManagedLevel(ServerInformation::ML_PULSE_TIME);

            DiscoverMessage dm;
            dm.setType(DiscoverMessage::RESPONSE);
            dm.setServerInformation(tm1);
            dm.setModuleName("TestComponent");

            Container c(dm);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == DiscoverMessage::ID());

            DiscoverMessage dm2 = c2.getData<DiscoverMessage>();

            TS_ASSERT(dm.getServerInformation().getIP() == dm2.getServerInformation().getIP());
            TS_ASSERT(dm2.getServerInformation().getIP() == "456.789.abc.123");

            TS_ASSERT(dm.getServerInformation().getPort() == dm2.getServerInformation().getPort());
            TS_ASSERT(dm2.getServerInformation().getPort() == 456);

            TS_ASSERT(dm.getServerInformation().getManagedLevel() == dm2.getServerInformation().getManagedLevel());
            TS_ASSERT(dm2.getServerInformation().getManagedLevel() == ServerInformation::ML_PULSE_TIME);

            TS_ASSERT(dm.getType() == dm2.getType());
            TS_ASSERT(dm2.getType() == DiscoverMessage::RESPONSE);

            TS_ASSERT(dm.getModuleName() == dm2.getModuleName());
            TS_ASSERT(dm2.getModuleName() == "TestComponent");
        }

        void testSerializationDeserializationDiscoverMessageVisitor() {
            ServerInformation tm1;
            tm1.setIP("456.789.abc.123");
            tm1.setPort(456);
            tm1.setManagedLevel(ServerInformation::ML_PULSE_TIME);

            DiscoverMessage dm;
            dm.setType(DiscoverMessage::RESPONSE);
            dm.setServerInformation(tm1);
            dm.setModuleName("TestComponent");

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            dm.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);


            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            DiscoverMessage dm2;
            dm2.accept(protoDeserializerVisitor);

            TS_ASSERT(dm.getServerInformation().getIP() == dm2.getServerInformation().getIP());
            TS_ASSERT(dm2.getServerInformation().getIP() == "456.789.abc.123");

            TS_ASSERT(dm.getServerInformation().getPort() == dm2.getServerInformation().getPort());
            TS_ASSERT(dm2.getServerInformation().getPort() == 456);

            TS_ASSERT(dm.getServerInformation().getManagedLevel() == dm2.getServerInformation().getManagedLevel());
            TS_ASSERT(dm2.getServerInformation().getManagedLevel() == ServerInformation::ML_PULSE_TIME);

            TS_ASSERT(dm.getType() == dm2.getType());
            TS_ASSERT(dm2.getType() == DiscoverMessage::RESPONSE);

            TS_ASSERT(dm.getModuleName() == dm2.getModuleName());
            TS_ASSERT(dm2.getModuleName() == "TestComponent");
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationModuleDescriptor() {
            ModuleDescriptor tm1;
            tm1.setName("My component");
            tm1.setIdentifier("12345");
            tm1.setVersion("XZY");
            tm1.setFrequency(1.2345);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            ModuleDescriptor tm2;
            out >> tm2;

            TS_ASSERT(tm1.getName() == tm2.getName());
            TS_ASSERT(tm2.getName() == "My component");

            TS_ASSERT(tm1.getIdentifier() == tm2.getIdentifier());
            TS_ASSERT(tm2.getIdentifier() == "12345");

            TS_ASSERT(tm1.getVersion() == tm2.getVersion());
            TS_ASSERT(tm2.getVersion() == "XZY");

            TS_ASSERT_DELTA(tm1.getFrequency(), tm2.getFrequency(), 1e-4);
            TS_ASSERT_DELTA(tm2.getFrequency(), 1.2345, 1e-4);
        }

        void testSerializationDeserializationModuleDescriptorContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            ModuleDescriptor tm1;
            tm1.setName("My component");
            tm1.setIdentifier("12345");
            tm1.setVersion("XZY");
            tm1.setFrequency(1.2345);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == ModuleDescriptor::ID());

            ModuleDescriptor tm2 = c2.getData<ModuleDescriptor>();

            TS_ASSERT(tm1.getName() == tm2.getName());
            TS_ASSERT(tm2.getName() == "My component");

            TS_ASSERT(tm1.getIdentifier() == tm2.getIdentifier());
            TS_ASSERT(tm2.getIdentifier() == "12345");

            TS_ASSERT(tm1.getVersion() == tm2.getVersion());
            TS_ASSERT(tm2.getVersion() == "XZY");

            TS_ASSERT_DELTA(tm1.getFrequency(), tm2.getFrequency(), 1e-4);
            TS_ASSERT_DELTA(tm2.getFrequency(), 1.2345, 1e-4);
        }

        void testSerializationDeserializationModuleDescriptorVisitor() {
            ModuleDescriptor tm1;
            tm1.setName("My component");
            tm1.setIdentifier("12345");
            tm1.setVersion("XZY");
            tm1.setFrequency(1.2345);

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
            ModuleDescriptor tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getName() == tm2.getName());
            TS_ASSERT(tm2.getName() == "My component");

            TS_ASSERT(tm1.getIdentifier() == tm2.getIdentifier());
            TS_ASSERT(tm2.getIdentifier() == "12345");

            TS_ASSERT(tm1.getVersion() == tm2.getVersion());
            TS_ASSERT(tm2.getVersion() == "XZY");

            TS_ASSERT_DELTA(tm1.getFrequency(), tm2.getFrequency(), 1e-4);
            TS_ASSERT_DELTA(tm2.getFrequency(), 1.2345, 1e-4);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationRuntimeStatistic() {
            RuntimeStatistic tm1;
            tm1.setSliceConsumption(-7.2345);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            RuntimeStatistic tm2;
            out >> tm2;

            TS_ASSERT_DELTA(tm1.getSliceConsumption(), tm2.getSliceConsumption(), 1e-4);
            TS_ASSERT_DELTA(tm2.getSliceConsumption(), -7.2345, 1e-4);
        }

        void testSerializationDeserializationRuntimeStatisticContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            RuntimeStatistic tm1;
            tm1.setSliceConsumption(-7.2345);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == RuntimeStatistic::ID());

            RuntimeStatistic tm2 = c2.getData<RuntimeStatistic>();

            TS_ASSERT_DELTA(tm1.getSliceConsumption(), tm2.getSliceConsumption(), 1e-4);
            TS_ASSERT_DELTA(tm2.getSliceConsumption(), -7.2345, 1e-4);
        }

        void testSerializationDeserializationRuntimeStatisticVisitor() {
            RuntimeStatistic tm1;
            tm1.setSliceConsumption(-7.2345);

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
            RuntimeStatistic tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT_DELTA(tm1.getSliceConsumption(), tm2.getSliceConsumption(), 1e-4);
            TS_ASSERT_DELTA(tm2.getSliceConsumption(), -7.2345, 1e-4);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationModuleStatistic() {
            ModuleDescriptor md;
            md.setName("My component");
            md.setIdentifier("12345");
            md.setVersion("XZY");
            md.setFrequency(1.2345);

            RuntimeStatistic rs;
            rs.setSliceConsumption(-7.2345);

            ModuleStatistic tm1;
            tm1.setModule(md);
            tm1.setRuntimeStatistic(rs);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            ModuleStatistic tm2;
            out >> tm2;

            TS_ASSERT(tm1.getModule().getName() == tm2.getModule().getName());
            TS_ASSERT(tm2.getModule().getName() == "My component");

            TS_ASSERT(tm1.getModule().getIdentifier() == tm2.getModule().getIdentifier());
            TS_ASSERT(tm2.getModule().getIdentifier() == "12345");

            TS_ASSERT(tm1.getModule().getVersion() == tm2.getModule().getVersion());
            TS_ASSERT(tm2.getModule().getVersion() == "XZY");

            TS_ASSERT_DELTA(tm1.getModule().getFrequency(), tm2.getModule().getFrequency(), 1e-4);
            TS_ASSERT_DELTA(tm2.getModule().getFrequency(), 1.2345, 1e-4);

            TS_ASSERT_DELTA(tm1.getRuntimeStatistic().getSliceConsumption(), tm2.getRuntimeStatistic().getSliceConsumption(), 1e-4);
            TS_ASSERT_DELTA(tm2.getRuntimeStatistic().getSliceConsumption(), -7.2345, 1e-4);
        }

        void testSerializationDeserializationModuleStatisticContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            ModuleDescriptor md;
            md.setName("My component");
            md.setIdentifier("12345");
            md.setVersion("XZY");
            md.setFrequency(1.2345);

            RuntimeStatistic rs;
            rs.setSliceConsumption(-7.2345);

            ModuleStatistic tm1;
            tm1.setModule(md);
            tm1.setRuntimeStatistic(rs);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == ModuleStatistic::ID());

            ModuleStatistic tm2 = c2.getData<ModuleStatistic>();

            TS_ASSERT(tm1.getModule().getName() == tm2.getModule().getName());
            TS_ASSERT(tm2.getModule().getName() == "My component");

            TS_ASSERT(tm1.getModule().getIdentifier() == tm2.getModule().getIdentifier());
            TS_ASSERT(tm2.getModule().getIdentifier() == "12345");

            TS_ASSERT(tm1.getModule().getVersion() == tm2.getModule().getVersion());
            TS_ASSERT(tm2.getModule().getVersion() == "XZY");

            TS_ASSERT_DELTA(tm1.getModule().getFrequency(), tm2.getModule().getFrequency(), 1e-4);
            TS_ASSERT_DELTA(tm2.getModule().getFrequency(), 1.2345, 1e-4);

            TS_ASSERT_DELTA(tm1.getRuntimeStatistic().getSliceConsumption(), tm2.getRuntimeStatistic().getSliceConsumption(), 1e-4);
            TS_ASSERT_DELTA(tm2.getRuntimeStatistic().getSliceConsumption(), -7.2345, 1e-4);
        }

        void testSerializationDeserializationModuleStatisticVisitor() {
            ModuleDescriptor md;
            md.setName("My component");
            md.setIdentifier("12345");
            md.setVersion("XZY");
            md.setFrequency(1.2345);

            RuntimeStatistic rs;
            rs.setSliceConsumption(-7.2345);

            ModuleStatistic tm1;
            tm1.setModule(md);
            tm1.setRuntimeStatistic(rs);

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
            ModuleStatistic tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getModule().getName() == tm2.getModule().getName());
            TS_ASSERT(tm2.getModule().getName() == "My component");

            TS_ASSERT(tm1.getModule().getIdentifier() == tm2.getModule().getIdentifier());
            TS_ASSERT(tm2.getModule().getIdentifier() == "12345");

            TS_ASSERT(tm1.getModule().getVersion() == tm2.getModule().getVersion());
            TS_ASSERT(tm2.getModule().getVersion() == "XZY");

            TS_ASSERT_DELTA(tm1.getModule().getFrequency(), tm2.getModule().getFrequency(), 1e-4);
            TS_ASSERT_DELTA(tm2.getModule().getFrequency(), 1.2345, 1e-4);

            TS_ASSERT_DELTA(tm1.getRuntimeStatistic().getSliceConsumption(), tm2.getRuntimeStatistic().getSliceConsumption(), 1e-4);
            TS_ASSERT_DELTA(tm2.getRuntimeStatistic().getSliceConsumption(), -7.2345, 1e-4);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationModuleStateMessage() {
            ModuleStateMessage tm1;
            tm1.setModuleState(ModuleStateMessage::RUNNING);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            ModuleStateMessage tm2;
            out >> tm2;

            TS_ASSERT(tm1.getModuleState() == tm2.getModuleState());
            TS_ASSERT(tm2.getModuleState() == ModuleStateMessage::RUNNING);
        }

        void testSerializationDeserializationModuleStateMessageContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            ModuleStateMessage tm1;
            tm1.setModuleState(ModuleStateMessage::RUNNING);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == ModuleStateMessage::ID());

            ModuleStateMessage tm2 = c2.getData<ModuleStateMessage>();

            TS_ASSERT(tm1.getModuleState() == tm2.getModuleState());
            TS_ASSERT(tm2.getModuleState() == ModuleStateMessage::RUNNING);
        }

        void testSerializationDeserializationModuleStateMessageVisitor() {
            ModuleStateMessage tm1;
            tm1.setModuleState(ModuleStateMessage::RUNNING);

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
            ModuleStateMessage tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getModuleState() == tm2.getModuleState());
            TS_ASSERT(tm2.getModuleState() == ModuleStateMessage::RUNNING);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationModuleExitCodeMessage() {
            ModuleExitCodeMessage tm1;
            tm1.setModuleExitCode(ModuleExitCodeMessage::CONNECTION_LOST);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            ModuleExitCodeMessage tm2;
            out >> tm2;

            TS_ASSERT(tm1.getModuleExitCode() == tm2.getModuleExitCode());
            TS_ASSERT(tm2.getModuleExitCode() == ModuleExitCodeMessage::CONNECTION_LOST);
        }

        void testSerializationDeserializationModuleExitCodeMessageContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            ModuleExitCodeMessage tm1;
            tm1.setModuleExitCode(ModuleExitCodeMessage::CONNECTION_LOST);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == ModuleExitCodeMessage::ID());

            ModuleExitCodeMessage tm2 = c2.getData<ModuleExitCodeMessage>();

            TS_ASSERT(tm1.getModuleExitCode() == tm2.getModuleExitCode());
            TS_ASSERT(tm2.getModuleExitCode() == ModuleExitCodeMessage::CONNECTION_LOST);
        }

        void testSerializationDeserializationModuleExitCodeMessageVisitor() {
            ModuleExitCodeMessage tm1;
            tm1.setModuleExitCode(ModuleExitCodeMessage::CONNECTION_LOST);

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
            ModuleExitCodeMessage tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getModuleExitCode() == tm2.getModuleExitCode());
            TS_ASSERT(tm2.getModuleExitCode() == ModuleExitCodeMessage::CONNECTION_LOST);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationPulseAckMessage() {
            PulseAckMessage tm1;

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            PulseAckMessage tm2;
            out >> tm2;
        }

        void testSerializationDeserializationPulseAckMessageContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            PulseAckMessage tm1;

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == PulseAckMessage::ID());

            PulseAckMessage tm2 = c2.getData<PulseAckMessage>();
            (void)tm2;
        }

        void testSerializationDeserializationPulseAckMessageVisitor() {
            PulseAckMessage tm1;

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
            PulseAckMessage tm2;
            tm2.accept(protoDeserializerVisitor);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationConfiguration() {
            KeyValueConfiguration kvc;

            // Setup an example configuration.
            stringstream sstrConfiguration;
            sstrConfiguration
                << "key1 = 123" << endl
                << "abc.key2 = value2" << endl
                << "key2:3 = -4.325" << endl;
            kvc.readFrom(sstrConfiguration);

            Configuration tm1;
            tm1.setKeyValueConfiguration(kvc);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            Configuration tm2;
            out >> tm2;

            KeyValueConfiguration kvc2 = tm2.getKeyValueConfiguration();

            TS_ASSERT(kvc.getValue<int>("key1") == kvc2.getValue<int>("key1"));
            TS_ASSERT(kvc2.getValue<int>("key1") == 123);

            TS_ASSERT(kvc.getValue<string>("abc.key2") == kvc2.getValue<string>("abc.key2"));
            TS_ASSERT(kvc2.getValue<string>("abc.key2") == "value2");

            TS_ASSERT_DELTA(kvc.getValue<float>("key2:3"), kvc2.getValue<float>("key2:3"), 1e-3);
            TS_ASSERT_DELTA(kvc2.getValue<float>("key2:3"), -4.325, 1e-3);
        }

        void testSerializationDeserializationConfigurationContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            KeyValueConfiguration kvc;

            // Setup an example configuration.
            stringstream sstrConfiguration;
            sstrConfiguration
                << "key1 = 123" << endl
                << "abc.key2 = value2" << endl
                << "key2:3 = -4.325" << endl;
            kvc.readFrom(sstrConfiguration);

            Configuration tm1;
            tm1.setKeyValueConfiguration(kvc);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == Configuration::ID());

            Configuration tm2 = c2.getData<Configuration>();

            KeyValueConfiguration kvc2 = tm2.getKeyValueConfiguration();

            TS_ASSERT(kvc.getValue<int>("key1") == kvc2.getValue<int>("key1"));
            TS_ASSERT(kvc2.getValue<int>("key1") == 123);

            TS_ASSERT(kvc.getValue<string>("abc.key2") == kvc2.getValue<string>("abc.key2"));
            TS_ASSERT(kvc2.getValue<string>("abc.key2") == "value2");

            TS_ASSERT_DELTA(kvc.getValue<float>("key2:3"), kvc2.getValue<float>("key2:3"), 1e-3);
            TS_ASSERT_DELTA(kvc2.getValue<float>("key2:3"), -4.325, 1e-3);
        }

        void testSerializationDeserializationModuleConfigurationVisitor() {
            KeyValueConfiguration kvc;

            // Setup an example configuration.
            stringstream sstrConfiguration;
            sstrConfiguration
                << "key1 = 123" << endl
                << "abc.key2 = value2" << endl
                << "key2:3 = -4.325" << endl;
            kvc.readFrom(sstrConfiguration);

            Configuration tm1;
            tm1.setKeyValueConfiguration(kvc);

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
            Configuration tm2;
            tm2.accept(protoDeserializerVisitor);

            KeyValueConfiguration kvc2 = tm2.getKeyValueConfiguration();

            TS_ASSERT(kvc.getValue<int>("key1") == kvc2.getValue<int>("key1"));
            TS_ASSERT(kvc2.getValue<int>("key1") == 123);

            TS_ASSERT(kvc.getValue<string>("abc.key2") == kvc2.getValue<string>("abc.key2"));
            TS_ASSERT(kvc2.getValue<string>("abc.key2") == "value2");

            TS_ASSERT_DELTA(kvc.getValue<float>("key2:3"), kvc2.getValue<float>("key2:3"), 1e-3);
            TS_ASSERT_DELTA(kvc2.getValue<float>("key2:3"), -4.325, 1e-3);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationMemorySegment() {
            // Replace default serializer/deserializers (needs to be here as the Container constructor will immediately serialize its argument.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            TimeStamp payload(7, 8);
            Container c(payload);
            c.setSentTimeStamp(TimeStamp(1, 2));
            c.setReceivedTimeStamp(TimeStamp(3, 4));

            MemorySegment ms;
            ms.setHeader(c);
            ms.setSize(123);
            ms.setConsumedSize(567);
            ms.setIdentifier(12);

            // Serialize via regular Serializer.
            stringstream out;
            out << ms;

            // Read back the data.
            MemorySegment ms2;
            out >> ms2;

            Container c2 = ms2.getHeader();
            TimeStamp payload2 = c2.getData<TimeStamp>();

            TS_ASSERT(c2.getDataType() == TimeStamp::ID());
            TS_ASSERT(payload2.getSeconds() == payload.getSeconds());
            TS_ASSERT(payload2.getFractionalMicroseconds() == payload.getFractionalMicroseconds());
            TS_ASSERT(ms2.getSize() == 123);
            TS_ASSERT(ms2.getConsumedSize() == 567);
            TS_ASSERT(ms2.getIdentifier() == 12);
        }

        void testSerializationDeserializationMemorySegmentContainer() {
            // Replace default serializer/deserializers (needs to be here as the Container constructor will immediately serialize its argument.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            TimeStamp payload(7, 8);
            Container c(payload);
            c.setSentTimeStamp(TimeStamp(1, 2));
            c.setReceivedTimeStamp(TimeStamp(3, 4));

            MemorySegment ms;
            ms.setHeader(c);
            ms.setSize(123);
            ms.setConsumedSize(567);
            ms.setIdentifier(12);

            Container _c(ms);

            // Serialize via regular Serializer.
            stringstream out;
            out << _c;

            // Read back the data.
            Container _c2;
            out >> _c2;
            TS_ASSERT(_c2.getDataType() == MemorySegment::ID());

            MemorySegment ms2 = _c2.getData<MemorySegment>();

            Container c2 = ms2.getHeader();
            TimeStamp payload2 = c2.getData<TimeStamp>();

            TS_ASSERT(c2.getDataType() == TimeStamp::ID());
            TS_ASSERT(payload2.getSeconds() == payload.getSeconds());
            TS_ASSERT(payload2.getFractionalMicroseconds() == payload.getFractionalMicroseconds());
            TS_ASSERT(ms2.getSize() == 123);
            TS_ASSERT(ms2.getConsumedSize() == 567);
            TS_ASSERT(ms2.getIdentifier() == 12);
        }

        void testSerializationDeserializationMemorySegmentVisitor() {
            TimeStamp payload(7, 8);
            Container c(payload);
            c.setSentTimeStamp(TimeStamp(1, 2));
            c.setReceivedTimeStamp(TimeStamp(3, 4));

            MemorySegment ms;
            ms.setHeader(c);
            ms.setSize(123);
            ms.setConsumedSize(567);
            ms.setIdentifier(12);

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            ms.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);


            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            MemorySegment ms2;
            ms2.accept(protoDeserializerVisitor);

            Container c2 = ms2.getHeader();
            TimeStamp payload2 = c2.getData<TimeStamp>();

            TS_ASSERT(c2.getDataType() == TimeStamp::ID());
            TS_ASSERT(payload2.getSeconds() == payload.getSeconds());
            TS_ASSERT(payload2.getFractionalMicroseconds() == payload.getFractionalMicroseconds());
            TS_ASSERT(ms2.getSize() == 123);
            TS_ASSERT(ms2.getConsumedSize() == 567);
            TS_ASSERT(ms2.getIdentifier() == 12);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationPlayerCommand() {
            PlayerCommand tm1;
            tm1.setCommand(PlayerCommand::REWIND);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            PlayerCommand tm2;
            out >> tm2;

            TS_ASSERT(tm1.getCommand() == tm2.getCommand());
            TS_ASSERT(tm2.getCommand() == PlayerCommand::REWIND);
        }

        void testSerializationDeserializationPlayerCommandContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            PlayerCommand tm1;
            tm1.setCommand(PlayerCommand::REWIND);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == PlayerCommand::ID());

            PlayerCommand tm2 = c2.getData<PlayerCommand>();

            TS_ASSERT(tm1.getCommand() == tm2.getCommand());
            TS_ASSERT(tm2.getCommand() == PlayerCommand::REWIND);
        }

        void testSerializationDeserializationPlayerCommandVisitor() {
            PlayerCommand tm1;
            tm1.setCommand(PlayerCommand::REWIND);

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
            PlayerCommand tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getCommand() == tm2.getCommand());
            TS_ASSERT(tm2.getCommand() == PlayerCommand::REWIND);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationRecorderCommand() {
            RecorderCommand tm1;
            tm1.setCommand(RecorderCommand::STOP);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            RecorderCommand tm2;
            out >> tm2;

            TS_ASSERT(tm1.getCommand() == tm2.getCommand());
            TS_ASSERT(tm2.getCommand() == RecorderCommand::STOP);
        }

        void testSerializationDeserializationRecorderCommandContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            RecorderCommand tm1;
            tm1.setCommand(RecorderCommand::STOP);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == RecorderCommand::ID());

            RecorderCommand tm2 = c2.getData<RecorderCommand>();

            TS_ASSERT(tm1.getCommand() == tm2.getCommand());
            TS_ASSERT(tm2.getCommand() == RecorderCommand::STOP);
        }

        void testSerializationDeserializationRecorderCommandVisitor() {
            RecorderCommand tm1;
            tm1.setCommand(RecorderCommand::STOP);

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
            RecorderCommand tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getCommand() == tm2.getCommand());
            TS_ASSERT(tm2.getCommand() == RecorderCommand::STOP);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationSharedData() {
            SharedData tm1;
            tm1.setName("Hello Shared Data");
            tm1.setSize(1234);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            SharedData tm2;
            out >> tm2;

            TS_ASSERT(tm1.getName() == tm2.getName());
            TS_ASSERT(tm2.getName() == "Hello Shared Data");

            TS_ASSERT(tm1.getSize() == tm2.getSize());
            TS_ASSERT(tm2.getSize() == 1234);
        }

        void testSerializationDeserializationSharedDataContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            SharedData tm1;
            tm1.setName("Hello Shared Data");
            tm1.setSize(1234);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == SharedData::ID());

            SharedData tm2 = c2.getData<SharedData>();

            TS_ASSERT(tm1.getName() == tm2.getName());
            TS_ASSERT(tm2.getName() == "Hello Shared Data");

            TS_ASSERT(tm1.getSize() == tm2.getSize());
            TS_ASSERT(tm2.getSize() == 1234);
        }

        void testSerializationDeserializationSharedDataVisitor() {
            SharedData tm1;
            tm1.setName("Hello Shared Data");
            tm1.setSize(1234);

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
            SharedData tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getName() == tm2.getName());
            TS_ASSERT(tm2.getName() == "Hello Shared Data");

            TS_ASSERT(tm1.getSize() == tm2.getSize());
            TS_ASSERT(tm2.getSize() == 1234);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationSharedImage() {
            SharedImage tm1;
            tm1.setName("Hello Shared Image");
            tm1.setSize(7890);
            tm1.setWidth(640);
            tm1.setHeight(480);
            tm1.setBytesPerPixel(3);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            SharedImage tm2;
            out >> tm2;

            TS_ASSERT(tm1.getName() == tm2.getName());
            TS_ASSERT(tm2.getName() == "Hello Shared Image");

            TS_ASSERT(tm1.getSize() == tm2.getSize());
            TS_ASSERT(tm2.getSize() == 7890);

            TS_ASSERT(tm1.getWidth() == tm2.getWidth());
            TS_ASSERT(tm2.getWidth() == 640);

            TS_ASSERT(tm1.getHeight() == tm2.getHeight());
            TS_ASSERT(tm2.getHeight() == 480);

            TS_ASSERT(tm1.getBytesPerPixel() == tm2.getBytesPerPixel());
            TS_ASSERT(tm2.getBytesPerPixel() == 3);
        }

        void testSerializationDeserializationSharedImageContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            SharedImage tm1;
            tm1.setName("Hello Shared Image");
            tm1.setSize(7890);
            tm1.setWidth(640);
            tm1.setHeight(480);
            tm1.setBytesPerPixel(3);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == SharedImage::ID());

            SharedImage tm2 = c2.getData<SharedImage>();

            TS_ASSERT(tm1.getName() == tm2.getName());
            TS_ASSERT(tm2.getName() == "Hello Shared Image");

            TS_ASSERT(tm1.getSize() == tm2.getSize());
            TS_ASSERT(tm2.getSize() == 7890);

            TS_ASSERT(tm1.getWidth() == tm2.getWidth());
            TS_ASSERT(tm2.getWidth() == 640);

            TS_ASSERT(tm1.getHeight() == tm2.getHeight());
            TS_ASSERT(tm2.getHeight() == 480);

            TS_ASSERT(tm1.getBytesPerPixel() == tm2.getBytesPerPixel());
            TS_ASSERT(tm2.getBytesPerPixel() == 3);
        }

        void testSerializationDeserializationSharedImageVisitor() {
            SharedImage tm1;
            tm1.setName("Hello Shared Image");
            tm1.setSize(7890);
            tm1.setWidth(640);
            tm1.setHeight(480);
            tm1.setBytesPerPixel(3);

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
            SharedImage tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getName() == tm2.getName());
            TS_ASSERT(tm2.getName() == "Hello Shared Image");

            TS_ASSERT(tm1.getSize() == tm2.getSize());
            TS_ASSERT(tm2.getSize() == 7890);

            TS_ASSERT(tm1.getWidth() == tm2.getWidth());
            TS_ASSERT(tm2.getWidth() == 640);

            TS_ASSERT(tm1.getHeight() == tm2.getHeight());
            TS_ASSERT(tm2.getHeight() == 480);

            TS_ASSERT(tm1.getBytesPerPixel() == tm2.getBytesPerPixel());
            TS_ASSERT(tm2.getBytesPerPixel() == 3);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationSharedPointCloud() {
            SharedPointCloud tm1;
            tm1.setName("Hello Shared Point Cloud");
            tm1.setSize(45678);
            tm1.setWidth(1234);
            tm1.setHeight(5678);
            tm1.setNumberOfComponentsPerPoint(4);
            tm1.setComponentDataType(SharedPointCloud::UINT32_T);
            tm1.setUserInfo(SharedPointCloud::XYZ_INTENSITY);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data.
            SharedPointCloud tm2;
            out >> tm2;

            TS_ASSERT(tm1.getName() == tm2.getName());
            TS_ASSERT(tm2.getName() == "Hello Shared Point Cloud");

            TS_ASSERT(tm1.getSize() == tm2.getSize());
            TS_ASSERT(tm2.getSize() == 45678);

            TS_ASSERT(tm1.getWidth() == tm2.getWidth());
            TS_ASSERT(tm2.getWidth() == 1234);

            TS_ASSERT(tm1.getHeight() == tm2.getHeight());
            TS_ASSERT(tm2.getHeight() == 5678);

            TS_ASSERT(tm1.getNumberOfComponentsPerPoint() == tm2.getNumberOfComponentsPerPoint());
            TS_ASSERT(tm2.getNumberOfComponentsPerPoint() == 4);

            TS_ASSERT(tm1.getComponentDataType() == tm2.getComponentDataType());
            TS_ASSERT(tm2.getComponentDataType() == SharedPointCloud::UINT32_T);

            TS_ASSERT(tm1.getUserInfo() == tm2.getUserInfo());
            TS_ASSERT(tm2.getUserInfo() == SharedPointCloud::XYZ_INTENSITY);
        }

        void testSerializationDeserializationSharedPointCloudContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            SharedPointCloud tm1;
            tm1.setName("Hello Shared Point Cloud");
            tm1.setSize(45678);
            tm1.setWidth(1234);
            tm1.setHeight(5678);
            tm1.setNumberOfComponentsPerPoint(4);
            tm1.setComponentDataType(SharedPointCloud::UINT32_T);
            tm1.setUserInfo(SharedPointCloud::XYZ_INTENSITY);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == SharedPointCloud::ID());

            SharedPointCloud tm2 = c2.getData<SharedPointCloud>();

            TS_ASSERT(tm1.getName() == tm2.getName());
            TS_ASSERT(tm2.getName() == "Hello Shared Point Cloud");

            TS_ASSERT(tm1.getSize() == tm2.getSize());
            TS_ASSERT(tm2.getSize() == 45678);

            TS_ASSERT(tm1.getWidth() == tm2.getWidth());
            TS_ASSERT(tm2.getWidth() == 1234);

            TS_ASSERT(tm1.getHeight() == tm2.getHeight());
            TS_ASSERT(tm2.getHeight() == 5678);

            TS_ASSERT(tm1.getNumberOfComponentsPerPoint() == tm2.getNumberOfComponentsPerPoint());
            TS_ASSERT(tm2.getNumberOfComponentsPerPoint() == 4);

            TS_ASSERT(tm1.getComponentDataType() == tm2.getComponentDataType());
            TS_ASSERT(tm2.getComponentDataType() == SharedPointCloud::UINT32_T);

            TS_ASSERT(tm1.getUserInfo() == tm2.getUserInfo());
            TS_ASSERT(tm2.getUserInfo() == SharedPointCloud::XYZ_INTENSITY);
        }

        void testSerializationDeserializationSharedPointCloudVisitor() {
            SharedPointCloud tm1;
            tm1.setName("Hello Shared Point Cloud");
            tm1.setSize(45678);
            tm1.setWidth(1234);
            tm1.setHeight(5678);
            tm1.setNumberOfComponentsPerPoint(4);
            tm1.setComponentDataType(SharedPointCloud::UINT32_T);
            tm1.setUserInfo(SharedPointCloud::XYZ_INTENSITY);

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
            SharedPointCloud tm2;
            tm2.accept(protoDeserializerVisitor);

            TS_ASSERT(tm1.getName() == tm2.getName());
            TS_ASSERT(tm2.getName() == "Hello Shared Point Cloud");

            TS_ASSERT(tm1.getSize() == tm2.getSize());
            TS_ASSERT(tm2.getSize() == 45678);

            TS_ASSERT(tm1.getWidth() == tm2.getWidth());
            TS_ASSERT(tm2.getWidth() == 1234);

            TS_ASSERT(tm1.getHeight() == tm2.getHeight());
            TS_ASSERT(tm2.getHeight() == 5678);

            TS_ASSERT(tm1.getNumberOfComponentsPerPoint() == tm2.getNumberOfComponentsPerPoint());
            TS_ASSERT(tm2.getNumberOfComponentsPerPoint() == 4);

            TS_ASSERT(tm1.getComponentDataType() == tm2.getComponentDataType());
            TS_ASSERT(tm2.getComponentDataType() == SharedPointCloud::UINT32_T);

            TS_ASSERT(tm1.getUserInfo() == tm2.getUserInfo());
            TS_ASSERT(tm2.getUserInfo() == SharedPointCloud::XYZ_INTENSITY);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationModuleStatistics() {
            ModuleStatistics mss1;

            {
                ModuleDescriptor md;
                md.setName("My component");
                md.setIdentifier("12345");
                md.setVersion("XZY");
                md.setFrequency(1.2345);

                RuntimeStatistic rs;
                rs.setSliceConsumption(-7.2345);

                ModuleStatistic ms1;
                ms1.setModule(md);
                ms1.setRuntimeStatistic(rs);

                mss1.addTo_ListOfModuleStatistics(ms1);
            }

            {
                ModuleDescriptor md;
                md.setName("My component B");
                md.setIdentifier("123456789");
                md.setVersion("XZYABC");
                md.setFrequency(8.2345);

                RuntimeStatistic rs;
                rs.setSliceConsumption(-97.2345);

                ModuleStatistic ms1;
                ms1.setModule(md);
                ms1.setRuntimeStatistic(rs);

                mss1.addTo_ListOfModuleStatistics(ms1);
            }

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << mss1;

            // Read back the data by using the visitor.
            ModuleStatistics mss2;

            // Read from buffer.
            out >> mss2;

            vector<ModuleStatistic> v1 = mss1.getListOfModuleStatistics();
            vector<ModuleStatistic> v2 = mss2.getListOfModuleStatistics();

            TS_ASSERT(v1.size() == 2);
            TS_ASSERT(v2.size() == 2);

            TS_ASSERT(v2.at(0).getModule().getName() == v1.at(0).getModule().getName());
            TS_ASSERT(v2.at(0).getModule().getName() == "My component");

            TS_ASSERT(v2.at(0).getModule().getIdentifier() == v1.at(0).getModule().getIdentifier());
            TS_ASSERT(v2.at(0).getModule().getIdentifier() == "12345");

            TS_ASSERT(v2.at(0).getModule().getVersion() == v1.at(0).getModule().getVersion());
            TS_ASSERT(v2.at(0).getModule().getVersion() == "XZY");

            TS_ASSERT_DELTA(v2.at(0).getModule().getFrequency(), v1.at(0).getModule().getFrequency(), 1e-4);
            TS_ASSERT_DELTA(v2.at(0).getModule().getFrequency(), 1.2345, 1e-4);

            TS_ASSERT_DELTA(v2.at(0).getRuntimeStatistic().getSliceConsumption(), v1.at(0).getRuntimeStatistic().getSliceConsumption(), 1e-4);
            TS_ASSERT_DELTA(v2.at(0).getRuntimeStatistic().getSliceConsumption(), -7.2345, 1e-4);
            TS_ASSERT(v2.at(0).getModule().getName() == v1.at(0).getModule().getName());


            TS_ASSERT(v2.at(1).getModule().getName() == "My component B");

            TS_ASSERT(v2.at(1).getModule().getIdentifier() == v1.at(1).getModule().getIdentifier());
            TS_ASSERT(v2.at(1).getModule().getIdentifier() == "123456789");

            TS_ASSERT(v2.at(1).getModule().getVersion() == v1.at(1).getModule().getVersion());
            TS_ASSERT(v2.at(1).getModule().getVersion() == "XZYABC");

            TS_ASSERT_DELTA(v2.at(1).getModule().getFrequency(), v1.at(1).getModule().getFrequency(), 1e-4);
            TS_ASSERT_DELTA(v2.at(1).getModule().getFrequency(), 8.2345, 1e-4);

            TS_ASSERT_DELTA(v2.at(1).getRuntimeStatistic().getSliceConsumption(), v1.at(1).getRuntimeStatistic().getSliceConsumption(), 1e-4);
            TS_ASSERT_DELTA(v2.at(1).getRuntimeStatistic().getSliceConsumption(), -97.2345, 1e-4);
        }

        void testSerializationDeserializationModuleStatisticsContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            ModuleStatistics mss1;

            {
                ModuleDescriptor md;
                md.setName("My component");
                md.setIdentifier("12345");
                md.setVersion("XZY");
                md.setFrequency(1.2345);

                RuntimeStatistic rs;
                rs.setSliceConsumption(-7.2345);

                ModuleStatistic ms1;
                ms1.setModule(md);
                ms1.setRuntimeStatistic(rs);

                mss1.addTo_ListOfModuleStatistics(ms1);
            }

            {
                ModuleDescriptor md;
                md.setName("My component B");
                md.setIdentifier("123456789");
                md.setVersion("XZYABC");
                md.setFrequency(8.2345);

                RuntimeStatistic rs;
                rs.setSliceConsumption(-97.2345);

                ModuleStatistic ms1;
                ms1.setModule(md);
                ms1.setRuntimeStatistic(rs);

                mss1.addTo_ListOfModuleStatistics(ms1);
            }

            Container c(mss1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read back the data.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == ModuleStatistics::ID());

            ModuleStatistics mss2 = c2.getData<ModuleStatistics>();

            vector<ModuleStatistic> v1 = mss1.getListOfModuleStatistics();
            vector<ModuleStatistic> v2 = mss2.getListOfModuleStatistics();

            TS_ASSERT(v1.size() == 2);
            TS_ASSERT(v2.size() == 2);

            TS_ASSERT(v2.at(0).getModule().getName() == v1.at(0).getModule().getName());
            TS_ASSERT(v2.at(0).getModule().getName() == "My component");

            TS_ASSERT(v2.at(0).getModule().getIdentifier() == v1.at(0).getModule().getIdentifier());
            TS_ASSERT(v2.at(0).getModule().getIdentifier() == "12345");

            TS_ASSERT(v2.at(0).getModule().getVersion() == v1.at(0).getModule().getVersion());
            TS_ASSERT(v2.at(0).getModule().getVersion() == "XZY");

            TS_ASSERT_DELTA(v2.at(0).getModule().getFrequency(), v1.at(0).getModule().getFrequency(), 1e-4);
            TS_ASSERT_DELTA(v2.at(0).getModule().getFrequency(), 1.2345, 1e-4);

            TS_ASSERT_DELTA(v2.at(0).getRuntimeStatistic().getSliceConsumption(), v1.at(0).getRuntimeStatistic().getSliceConsumption(), 1e-4);
            TS_ASSERT_DELTA(v2.at(0).getRuntimeStatistic().getSliceConsumption(), -7.2345, 1e-4);
            TS_ASSERT(v2.at(0).getModule().getName() == v1.at(0).getModule().getName());


            TS_ASSERT(v2.at(1).getModule().getName() == "My component B");

            TS_ASSERT(v2.at(1).getModule().getIdentifier() == v1.at(1).getModule().getIdentifier());
            TS_ASSERT(v2.at(1).getModule().getIdentifier() == "123456789");

            TS_ASSERT(v2.at(1).getModule().getVersion() == v1.at(1).getModule().getVersion());
            TS_ASSERT(v2.at(1).getModule().getVersion() == "XZYABC");

            TS_ASSERT_DELTA(v2.at(1).getModule().getFrequency(), v1.at(1).getModule().getFrequency(), 1e-4);
            TS_ASSERT_DELTA(v2.at(1).getModule().getFrequency(), 8.2345, 1e-4);

            TS_ASSERT_DELTA(v2.at(1).getRuntimeStatistic().getSliceConsumption(), v1.at(1).getRuntimeStatistic().getSliceConsumption(), 1e-4);
            TS_ASSERT_DELTA(v2.at(1).getRuntimeStatistic().getSliceConsumption(), -97.2345, 1e-4);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationPulseMessage() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            PulseMessage pm1;
            pm1.setRealTimeFromSupercomponent(TimeStamp(8, 9));
            pm1.setNominalTimeSlice(12);
            pm1.setCumulatedTimeSlice(34);

            {
                TimeStamp ts(1, 2);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }
            {
                TimeStamp ts(3, 4);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }

            // Serialize via regular Serializer.
            stringstream out;
            out << pm1;

            // Read back the data by using the visitor.
            PulseMessage pm2;

            // Read from buffer.
            out >> pm2;

            vector<Container> v1 = pm1.getListOfContainers();
            vector<Container> v2 = pm2.getListOfContainers();

            TS_ASSERT(v1.size() == 2);
            TS_ASSERT(v2.size() == 2);

            TS_ASSERT(pm1.getRealTimeFromSupercomponent().getSeconds() == pm2.getRealTimeFromSupercomponent().getSeconds());
            TS_ASSERT(pm2.getRealTimeFromSupercomponent().getSeconds() == 8);

            TS_ASSERT(pm1.getRealTimeFromSupercomponent().getFractionalMicroseconds() == pm2.getRealTimeFromSupercomponent().getFractionalMicroseconds());
            TS_ASSERT(pm2.getRealTimeFromSupercomponent().getFractionalMicroseconds() == 9);

            TS_ASSERT(pm1.getNominalTimeSlice() == pm2.getNominalTimeSlice());
            TS_ASSERT(pm2.getNominalTimeSlice() == 12);

            TS_ASSERT(pm1.getCumulatedTimeSlice() == pm2.getCumulatedTimeSlice());
            TS_ASSERT(pm2.getCumulatedTimeSlice() == 34);


            Container v1_c1 = v1.at(0);
            Container v1_c2 = v1.at(1);
            TS_ASSERT(v1_c1.getDataType() == TimeStamp::ID());
            TS_ASSERT(v1_c2.getDataType() == TimeStamp::ID());

            TimeStamp v1_ts1 = v1_c1.getData<TimeStamp>();
            TimeStamp v1_ts2 = v1_c2.getData<TimeStamp>();

            Container v2_c1 = v2.at(0);
            Container v2_c2 = v2.at(1);
            TS_ASSERT(v2_c1.getDataType() == TimeStamp::ID());
            TS_ASSERT(v2_c2.getDataType() == TimeStamp::ID());

            TimeStamp v2_ts1 = v2_c1.getData<TimeStamp>();
            TimeStamp v2_ts2 = v2_c2.getData<TimeStamp>();

            TS_ASSERT(v1_ts1.toMicroseconds() == v2_ts1.toMicroseconds());
            TS_ASSERT(v2_ts1.toMicroseconds() == 1000002);

            TS_ASSERT(v1_ts2.toMicroseconds() == v2_ts2.toMicroseconds());
            TS_ASSERT(v2_ts2.toMicroseconds() == 3000004);
        }

        void testSerializationDeserializationPulseMessageContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            PulseMessage pm1;
            pm1.setRealTimeFromSupercomponent(TimeStamp(8, 9));
            pm1.setNominalTimeSlice(12);
            pm1.setCumulatedTimeSlice(34);

            {
                TimeStamp ts(1, 2);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }
            {
                TimeStamp ts(3, 4);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }

            Container c(pm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read from buffer.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == PulseMessage::ID());

            PulseMessage pm2 = c2.getData<PulseMessage>();

            vector<Container> v1 = pm1.getListOfContainers();
            vector<Container> v2 = pm2.getListOfContainers();

            TS_ASSERT(v1.size() == 2);
            TS_ASSERT(v2.size() == 2);

            TS_ASSERT(pm1.getRealTimeFromSupercomponent().getSeconds() == pm2.getRealTimeFromSupercomponent().getSeconds());
            TS_ASSERT(pm2.getRealTimeFromSupercomponent().getSeconds() == 8);

            TS_ASSERT(pm1.getRealTimeFromSupercomponent().getFractionalMicroseconds() == pm2.getRealTimeFromSupercomponent().getFractionalMicroseconds());
            TS_ASSERT(pm2.getRealTimeFromSupercomponent().getFractionalMicroseconds() == 9);

            TS_ASSERT(pm1.getNominalTimeSlice() == pm2.getNominalTimeSlice());
            TS_ASSERT(pm2.getNominalTimeSlice() == 12);

            TS_ASSERT(pm1.getCumulatedTimeSlice() == pm2.getCumulatedTimeSlice());
            TS_ASSERT(pm2.getCumulatedTimeSlice() == 34);


            Container v1_c1 = v1.at(0);
            Container v1_c2 = v1.at(1);
            TS_ASSERT(v1_c1.getDataType() == TimeStamp::ID());
            TS_ASSERT(v1_c2.getDataType() == TimeStamp::ID());

            TimeStamp v1_ts1 = v1_c1.getData<TimeStamp>();
            TimeStamp v1_ts2 = v1_c2.getData<TimeStamp>();

            Container v2_c1 = v2.at(0);
            Container v2_c2 = v2.at(1);
            TS_ASSERT(v2_c1.getDataType() == TimeStamp::ID());
            TS_ASSERT(v2_c2.getDataType() == TimeStamp::ID());

            TimeStamp v2_ts1 = v2_c1.getData<TimeStamp>();
            TimeStamp v2_ts2 = v2_c2.getData<TimeStamp>();

            TS_ASSERT(v1_ts1.toMicroseconds() == v2_ts1.toMicroseconds());
            TS_ASSERT(v2_ts1.toMicroseconds() == 1000002);

            TS_ASSERT(v1_ts2.toMicroseconds() == v2_ts2.toMicroseconds());
            TS_ASSERT(v2_ts2.toMicroseconds() == 3000004);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationPulseAckContainersMessage() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            PulseAckContainersMessage pm1;

            {
                TimeStamp ts(1, 2);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }
            {
                TimeStamp ts(3, 4);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }


            // Serialize via regular Serializer.
            stringstream out;
            out << pm1;

            // Read back the data by using the visitor.
            PulseAckContainersMessage pm2;

            // Read from buffer.
            out >> pm2;

            vector<Container> v1 = pm1.getListOfContainers();
            vector<Container> v2 = pm2.getListOfContainers();

            TS_ASSERT(v1.size() == 2);
            TS_ASSERT(v2.size() == 2);

            Container v1_c1 = v1.at(0);
            Container v1_c2 = v1.at(1);
            TS_ASSERT(v1_c1.getDataType() == TimeStamp::ID());
            TS_ASSERT(v1_c2.getDataType() == TimeStamp::ID());

            TimeStamp v1_ts1 = v1_c1.getData<TimeStamp>();
            TimeStamp v1_ts2 = v1_c2.getData<TimeStamp>();

            Container v2_c1 = v2.at(0);
            Container v2_c2 = v2.at(1);
            TS_ASSERT(v2_c1.getDataType() == TimeStamp::ID());
            TS_ASSERT(v2_c2.getDataType() == TimeStamp::ID());

            TimeStamp v2_ts1 = v2_c1.getData<TimeStamp>();
            TimeStamp v2_ts2 = v2_c2.getData<TimeStamp>();

            TS_ASSERT(v1_ts1.toMicroseconds() == v2_ts1.toMicroseconds());
            TS_ASSERT(v2_ts1.toMicroseconds() == 1000002);

            TS_ASSERT(v1_ts2.toMicroseconds() == v2_ts2.toMicroseconds());
            TS_ASSERT(v2_ts2.toMicroseconds() == 3000004);
        }

        void testSerializationDeserializationPulseAckContainersMessageContainer() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            PulseAckContainersMessage pm1;

            {
                TimeStamp ts(1, 2);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }
            {
                TimeStamp ts(3, 4);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }

            Container c(pm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read from buffer.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == PulseAckContainersMessage::ID());

            PulseAckContainersMessage pm2 = c2.getData<PulseAckContainersMessage>();

            vector<Container> v1 = pm1.getListOfContainers();
            vector<Container> v2 = pm2.getListOfContainers();

            TS_ASSERT(v1.size() == 2);
            TS_ASSERT(v2.size() == 2);

            Container v1_c1 = v1.at(0);
            Container v1_c2 = v1.at(1);
            TS_ASSERT(v1_c1.getDataType() == TimeStamp::ID());
            TS_ASSERT(v1_c2.getDataType() == TimeStamp::ID());

            TimeStamp v1_ts1 = v1_c1.getData<TimeStamp>();
            TimeStamp v1_ts2 = v1_c2.getData<TimeStamp>();

            Container v2_c1 = v2.at(0);
            Container v2_c2 = v2.at(1);
            TS_ASSERT(v2_c1.getDataType() == TimeStamp::ID());
            TS_ASSERT(v2_c2.getDataType() == TimeStamp::ID());

            TimeStamp v2_ts1 = v2_c1.getData<TimeStamp>();
            TimeStamp v2_ts2 = v2_c2.getData<TimeStamp>();

            TS_ASSERT(v1_ts1.toMicroseconds() == v2_ts1.toMicroseconds());
            TS_ASSERT(v2_ts1.toMicroseconds() == 1000002);

            TS_ASSERT(v1_ts2.toMicroseconds() == v2_ts2.toMicroseconds());
            TS_ASSERT(v2_ts2.toMicroseconds() == 3000004);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationPulseMessageRequireClearFailbit() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            PulseMessage pm1;
            pm1.setRealTimeFromSupercomponent(TimeStamp(8, 9));
            pm1.setNominalTimeSlice(12);
            pm1.setCumulatedTimeSlice(34);

            {
                TimeStamp ts(1, 2);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }
            {
                TimeStamp ts(3, 4);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }

            // Serialize via regular Serializer.
            stringstream out;
            out << pm1;

            // Read back the data by using the visitor.
            PulseMessage pm2;

            // Read from buffer.
            out >> pm2;

            vector<Container> v1 = pm1.getListOfContainers();
            vector<Container> v2 = pm2.getListOfContainers();

            TS_ASSERT(v1.size() == 2);
            TS_ASSERT(v2.size() == 2);

            TS_ASSERT(pm1.getRealTimeFromSupercomponent().getSeconds() == pm2.getRealTimeFromSupercomponent().getSeconds());
            TS_ASSERT(pm2.getRealTimeFromSupercomponent().getSeconds() == 8);

            TS_ASSERT(pm1.getRealTimeFromSupercomponent().getFractionalMicroseconds() == pm2.getRealTimeFromSupercomponent().getFractionalMicroseconds());
            TS_ASSERT(pm2.getRealTimeFromSupercomponent().getFractionalMicroseconds() == 9);

            TS_ASSERT(pm1.getNominalTimeSlice() == pm2.getNominalTimeSlice());
            TS_ASSERT(pm2.getNominalTimeSlice() == 12);

            TS_ASSERT(pm1.getCumulatedTimeSlice() == pm2.getCumulatedTimeSlice());
            TS_ASSERT(pm2.getCumulatedTimeSlice() == 34);

            TS_ASSERT(v1.at(0).getData<TimeStamp>().toMicroseconds() == v2.at(0).getData<TimeStamp>().toMicroseconds());
            TS_ASSERT(v2.at(0).getData<TimeStamp>().toMicroseconds() == 1000002);

            TS_ASSERT(v1.at(1).getData<TimeStamp>().toMicroseconds() == v2.at(1).getData<TimeStamp>().toMicroseconds());
            TS_ASSERT(v2.at(1).getData<TimeStamp>().toMicroseconds() == 3000004);
        }

        void testSerializationDeserializationPulseMessageContainerRequireClearFailbit() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            PulseMessage pm1;
            pm1.setRealTimeFromSupercomponent(TimeStamp(8, 9));
            pm1.setNominalTimeSlice(12);
            pm1.setCumulatedTimeSlice(34);

            {
                TimeStamp ts(1, 2);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }
            {
                TimeStamp ts(3, 4);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }

            Container c(pm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read from buffer.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == PulseMessage::ID());

            PulseMessage pm2 = c2.getData<PulseMessage>();

            vector<Container> v1 = pm1.getListOfContainers();
            vector<Container> v2 = pm2.getListOfContainers();

            TS_ASSERT(v1.size() == 2);
            TS_ASSERT(v2.size() == 2);

            TS_ASSERT(pm1.getRealTimeFromSupercomponent().getSeconds() == pm2.getRealTimeFromSupercomponent().getSeconds());
            TS_ASSERT(pm2.getRealTimeFromSupercomponent().getSeconds() == 8);

            TS_ASSERT(pm1.getRealTimeFromSupercomponent().getFractionalMicroseconds() == pm2.getRealTimeFromSupercomponent().getFractionalMicroseconds());
            TS_ASSERT(pm2.getRealTimeFromSupercomponent().getFractionalMicroseconds() == 9);

            TS_ASSERT(pm1.getNominalTimeSlice() == pm2.getNominalTimeSlice());
            TS_ASSERT(pm2.getNominalTimeSlice() == 12);

            TS_ASSERT(pm1.getCumulatedTimeSlice() == pm2.getCumulatedTimeSlice());
            TS_ASSERT(pm2.getCumulatedTimeSlice() == 34);

            TS_ASSERT(v1.at(0).getData<TimeStamp>().toMicroseconds() == v2.at(0).getData<TimeStamp>().toMicroseconds());
            TS_ASSERT(v2.at(0).getData<TimeStamp>().toMicroseconds() == 1000002);

            TS_ASSERT(v1.at(1).getData<TimeStamp>().toMicroseconds() == v2.at(1).getData<TimeStamp>().toMicroseconds());
            TS_ASSERT(v2.at(1).getData<TimeStamp>().toMicroseconds() == 3000004);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationPulseAckContainersMessageRequireClearFailbit() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            PulseAckContainersMessage pm1;

            {
                TimeStamp ts(1, 2);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }
            {
                TimeStamp ts(3, 4);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }

            // Serialize via regular Serializer.
            stringstream out;
            out << pm1;

            // Read back the data by using the visitor.
            PulseAckContainersMessage pm2;

            // Read from buffer.
            out >> pm2;

            vector<Container> v1 = pm1.getListOfContainers();
            vector<Container> v2 = pm2.getListOfContainers();

            TS_ASSERT(v1.size() == 2);
            TS_ASSERT(v2.size() == 2);

            TS_ASSERT(v1.at(0).getData<TimeStamp>().toMicroseconds() == v2.at(0).getData<TimeStamp>().toMicroseconds());
            TS_ASSERT(v2.at(0).getData<TimeStamp>().toMicroseconds() == 1000002);

            TS_ASSERT(v1.at(1).getData<TimeStamp>().toMicroseconds() == v2.at(1).getData<TimeStamp>().toMicroseconds());
            TS_ASSERT(v2.at(1).getData<TimeStamp>().toMicroseconds() == 3000004);
        }

        void testSerializationDeserializationPulseAckContainersMessageContainerRequireClearFailbit() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            PulseAckContainersMessage pm1;

            {
                TimeStamp ts(1, 2);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }
            {
                TimeStamp ts(3, 4);
                Container c(ts);
                pm1.addTo_ListOfContainers(c);
            }

            Container c(pm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read from buffer.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == PulseAckContainersMessage::ID());

            PulseAckContainersMessage pm2 = c2.getData<PulseAckContainersMessage>();

            vector<Container> v1 = pm1.getListOfContainers();
            vector<Container> v2 = pm2.getListOfContainers();

            TS_ASSERT(v1.size() == 2);
            TS_ASSERT(v2.size() == 2);

            TS_ASSERT(v1.at(0).getData<TimeStamp>().toMicroseconds() == v2.at(0).getData<TimeStamp>().toMicroseconds());
            TS_ASSERT(v2.at(0).getData<TimeStamp>().toMicroseconds() == 1000002);

            TS_ASSERT(v1.at(1).getData<TimeStamp>().toMicroseconds() == v2.at(1).getData<TimeStamp>().toMicroseconds());
            TS_ASSERT(v2.at(1).getData<TimeStamp>().toMicroseconds() == 3000004);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage6() {
            TestMessage6 tm1;

            {
                uint32_t i = 3;
                tm1.addTo_ListOfField1(i);
            }
            {
                uint32_t i = 270;
                tm1.addTo_ListOfField1(i);
            }
            {
                uint32_t i = 86942;
                tm1.addTo_ListOfField1(i);
            }


            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // According to https://developers.google.com/protocol-buffers/docs/encoding, 0x22 0x6 0x3 0x8e 0x2 0x9e 0xa7 0x5.
            const string s = out.str();
            TS_ASSERT(s.size() == 8);
            TS_ASSERT(static_cast<uint8_t>(s.at(0)) == 0x22);
            TS_ASSERT(static_cast<uint8_t>(s.at(1)) == 0x6);
            TS_ASSERT(static_cast<uint8_t>(s.at(2)) == 0x3);
            TS_ASSERT(static_cast<uint8_t>(s.at(3)) == 0x8e);
            TS_ASSERT(static_cast<uint8_t>(s.at(4)) == 0x2);
            TS_ASSERT(static_cast<uint8_t>(s.at(5)) == 0x9e);
            TS_ASSERT(static_cast<uint8_t>(s.at(6)) == 0xa7);
            TS_ASSERT(static_cast<uint8_t>(s.at(7)) == 0x5);

            // Read back the data by using the visitor.
            TestMessage6 tm2;

            // Read from buffer.
            out >> tm2;

            vector<uint32_t> v1 = tm1.getListOfField1();
            vector<uint32_t> v2 = tm2.getListOfField1();

            TS_ASSERT(v1.size() == 3);
            TS_ASSERT(v2.size() == 3);

            TS_ASSERT(v1.at(0) == v2.at(0));
            TS_ASSERT(v2.at(0) == 3);

            TS_ASSERT(v1.at(1) == v2.at(1));
            TS_ASSERT(v2.at(1) == 270);

            TS_ASSERT(v1.at(2) == v2.at(2));
            TS_ASSERT(v2.at(2) == 86942);
        }

        void testSerializationDeserializationTestMessage6Container() {
            TestMessage6 tm1;

            {
                uint32_t i = 3;
                tm1.addTo_ListOfField1(i);
            }
            {
                uint32_t i = 270;
                tm1.addTo_ListOfField1(i);
            }
            {
                uint32_t i = 86942;
                tm1.addTo_ListOfField1(i);
            }


            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read from buffer.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == TestMessage6::ID());

            TestMessage6 tm2 = c2.getData<TestMessage6>();

            vector<uint32_t> v1 = tm1.getListOfField1();
            vector<uint32_t> v2 = tm2.getListOfField1();

            TS_ASSERT(v1.size() == 3);
            TS_ASSERT(v2.size() == 3);

            TS_ASSERT(v1.at(0) == v2.at(0));
            TS_ASSERT(v2.at(0) == 3);

            TS_ASSERT(v1.at(1) == v2.at(1));
            TS_ASSERT(v2.at(1) == 270);

            TS_ASSERT(v1.at(2) == v2.at(2));
            TS_ASSERT(v2.at(2) == 86942);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage7() {
            TestMessage7 tm1;

            {
                float i = -12.345;
                tm1.addTo_ListOfField1(i);
            }
            {
                float i = -34.567;
                tm1.addTo_ListOfField1(i);
            }
            {
                float i = 47.891;
                tm1.addTo_ListOfField1(i);
            }


            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read back the data by using the visitor.
            TestMessage7 tm2;

            // Read from buffer.
            out >> tm2;

            vector<float> v1 = tm1.getListOfField1();
            vector<float> v2 = tm2.getListOfField1();

            TS_ASSERT(v1.size() == 3);
            TS_ASSERT(v2.size() == 3);

            TS_ASSERT_DELTA(v1.at(0), v2.at(0), 1e-3);
            TS_ASSERT_DELTA(v2.at(0), -12.345, 1e-3);

            TS_ASSERT_DELTA(v1.at(1), v2.at(1), 1e-3);
            TS_ASSERT_DELTA(v2.at(1), -34.567, 1e-3);

            TS_ASSERT_DELTA(v1.at(2), v2.at(2), 1e-3);
            TS_ASSERT_DELTA(v2.at(2), 47.891, 1e-3);
        }

        void testSerializationDeserializationTestMessage7ValidatedWithGoogleProtobuf() {
            TestMessage7 tm1;

            {
                float i = -12.345;
                tm1.addTo_ListOfField1(i);
            }
            {
                float i = -34.567;
                tm1.addTo_ListOfField1(i);
            }
            {
                float i = 47.891;
                tm1.addTo_ListOfField1(i);
            }


            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            const string s = out.str();
            TS_ASSERT(s.size() == 14);
            uint32_t cnt=0;
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xa);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xc);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x1f);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x85);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x45);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xc1);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x9c);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x44);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xa);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xc2);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x62);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x90);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x3f);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x42);

            // Read back the data by using the visitor.
            TestMessage7 tm2;

            // Read from buffer.
            out >> tm2;

            vector<float> v1 = tm1.getListOfField1();
            vector<float> v2 = tm2.getListOfField1();

            TS_ASSERT(v1.size() == 3);
            TS_ASSERT(v2.size() == 3);

            TS_ASSERT_DELTA(v1.at(0), v2.at(0), 1e-3);
            TS_ASSERT_DELTA(v2.at(0), -12.345, 1e-3);

            TS_ASSERT_DELTA(v1.at(1), v2.at(1), 1e-3);
            TS_ASSERT_DELTA(v2.at(1), -34.567, 1e-3);

            TS_ASSERT_DELTA(v1.at(2), v2.at(2), 1e-3);
            TS_ASSERT_DELTA(v2.at(2), 47.891, 1e-3);
        }

        void testSerializationDeserializationTestMessage7Container() {
            TestMessage7 tm1;

            {
                float i = -12.345;
                tm1.addTo_ListOfField1(i);
            }
            {
                float i = -34.567;
                tm1.addTo_ListOfField1(i);
            }
            {
                float i = 47.891;
                tm1.addTo_ListOfField1(i);
            }


            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read from buffer.
            Container c2;
            out >> c2;
            TS_ASSERT(c2.getDataType() == TestMessage7::ID());

            TestMessage7 tm2 = c2.getData<TestMessage7>();

            vector<float> v1 = tm1.getListOfField1();
            vector<float> v2 = tm2.getListOfField1();

            TS_ASSERT(v1.size() == 3);
            TS_ASSERT(v2.size() == 3);

            TS_ASSERT_DELTA(v1.at(0), v2.at(0), 1e-3);
            TS_ASSERT_DELTA(v2.at(0), -12.345, 1e-3);

            TS_ASSERT_DELTA(v1.at(1), v2.at(1), 1e-3);
            TS_ASSERT_DELTA(v2.at(1), -34.567, 1e-3);

            TS_ASSERT_DELTA(v1.at(2), v2.at(2), 1e-3);
            TS_ASSERT_DELTA(v2.at(2), 47.891, 1e-3);
        }

        ///////////////////////////////////////////////////////////////////////

        void testProtoKeyValueInt() {
            uint64_t i = 654321;

            ProtoKeyValue pkv(123, i);
            TS_ASSERT(pkv.getKey() == 123);
            TS_ASSERT(pkv.getType() == ProtoSerializer::VARINT);
            TS_ASSERT(pkv.getLength() == 0);
            TS_ASSERT(pkv.getValueAsVarInt() == 654321);
        }

        void testProtoKeyValueFloat() {
            vector<char> v;
            v.resize(4);
            //float *f = (float*)(&v[0]);
            //*f = -3.12345;

            float _f = -3.12345;
            memcpy((&v[0]), &_f, sizeof(float));

            ProtoKeyValue pkv(234, ProtoSerializer::FOUR_BYTES, sizeof(float), v);
            TS_ASSERT(pkv.getKey() == 234);
            TS_ASSERT(pkv.getType() == ProtoSerializer::FOUR_BYTES);
            TS_ASSERT(pkv.getLength() == sizeof(float));
            TS_ASSERT_DELTA(pkv.getValueAsFloat(), -3.12345, 1e-5);
        }

        void testProtoKeyValueDouble() {
            vector<char> v;
            v.resize(8);
            //double *d = (double*)(&v[0]);
            //*d = 3.123456789;

            double _d = 3.123456789;
            memcpy((&v[0]), &_d, sizeof(double));

            ProtoKeyValue pkv(345, ProtoSerializer::EIGHT_BYTES, sizeof(double), v);
            TS_ASSERT(pkv.getKey() == 345);
            TS_ASSERT(pkv.getType() == ProtoSerializer::EIGHT_BYTES);
            TS_ASSERT(pkv.getLength() == sizeof(double));
            TS_ASSERT_DELTA(pkv.getValueAsDouble(), 3.123456789, 1e-9);
        }

        void testProtoKeyValueString() {
            vector<char> v = { 'O', 'p', 'e', 'n', 'D', 'a', 'V', 'I', 'N', 'C', 'I' };

            ProtoKeyValue pkv(456, ProtoSerializer::LENGTH_DELIMITED, 11, v);
            TS_ASSERT(pkv.getKey() == 456);
            TS_ASSERT(pkv.getType() == ProtoSerializer::LENGTH_DELIMITED);
            TS_ASSERT(pkv.getLength() == 11);
            TS_ASSERT(pkv.getValueAsString() == "OpenDaVINCI");
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage1OneFieldDefaultContainer() {
            // Create an uninitialized Container.
            Container c;

            // Force reading from Container must result in default-initialized message
            // as the content of an uninitialized Container is an empty payload that
            // does not carry any meaningful data.
            TestMessage1 tm2 = c.getData<TestMessage1>();
            TS_ASSERT(tm2.getField1() == 12);
        }

        ///////////////////////////////////////////////////////////////////////

        void testReorderedFields() {
            // Create some data.
            ProtoMessages1SampleDataVersion2 sd;
            sd.m_bool = true;
            sd.m_int = 42;
            sd.m_string = "This is an example.";

            // Create a data sink.
            stringstream inout;
            inout << sd;
            inout.flush();

            // Read from the previously created data sink.
            ProtoMessages1SampleDataVersion2Reordered sd2;
            inout >> sd2;

            TS_ASSERT(sd2.m_bool);
            TS_ASSERT(sd2.m_int == 42);
            TS_ASSERT(sd2.m_string == "This is an example.");
        }

        void testExtendedFields() {
            // Create some data.
            ProtoMessages1SampleDataVersion1 sd;
            sd.m_bool = true;

            // Create a data sink.
            stringstream inout;
            inout << sd;
            inout.flush();

            // Read from the previously created data sink.
            ProtoMessages1SampleDataVersion2 sd2;
            inout >> sd2;

            TS_ASSERT(sd2.m_bool);
            TS_ASSERT(sd2.m_int == 37);
            TS_ASSERT(sd2.m_string == "Hello World");
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage8() {
            TestMessage8 tm1;
            tm1.putTo_MapOfField1(1, 8);
            tm1.putTo_MapOfField1(2, 7);
            tm1.putTo_MapOfField1(3, 6);

            TS_ASSERT(tm1.containsKey_MapOfField1(1));
            TS_ASSERT(tm1.containsKey_MapOfField1(2));
            TS_ASSERT(tm1.containsKey_MapOfField1(3));
            TS_ASSERT(!tm1.containsKey_MapOfField1(4));
            TS_ASSERT(tm1.getValueForKey_MapOfField1(1) == 8);
            TS_ASSERT(tm1.getValueForKey_MapOfField1(2) == 7);
            TS_ASSERT(tm1.getValueForKey_MapOfField1(3) == 6);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read from buffer.
            TestMessage8 tm2;
            out >> tm2;

            TS_ASSERT(tm2.containsKey_MapOfField1(1));
            TS_ASSERT(tm2.containsKey_MapOfField1(2));
            TS_ASSERT(tm2.containsKey_MapOfField1(3));
            TS_ASSERT(!tm2.containsKey_MapOfField1(4));
            TS_ASSERT(tm2.getValueForKey_MapOfField1(1) == 8);
            TS_ASSERT(tm2.getValueForKey_MapOfField1(2) == 7);
            TS_ASSERT(tm2.getValueForKey_MapOfField1(3) == 6);
        }

        void testSerializationDeserializationTestMessage8Container() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            TestMessage8 tm1;
            tm1.putTo_MapOfField1(1, 8);
            tm1.putTo_MapOfField1(2, 7);
            tm1.putTo_MapOfField1(3, 6);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read from buffer.
            Container c2;
            out >> c2;

            TS_ASSERT(c2.getDataType() == TestMessage8::ID());

            TestMessage8 tm2 = c2.getData<TestMessage8>();

            TS_ASSERT(tm2.containsKey_MapOfField1(1));
            TS_ASSERT(tm2.containsKey_MapOfField1(2));
            TS_ASSERT(tm2.containsKey_MapOfField1(3));
            TS_ASSERT(!tm2.containsKey_MapOfField1(4));
            TS_ASSERT(tm2.getValueForKey_MapOfField1(1) == 8);
            TS_ASSERT(tm2.getValueForKey_MapOfField1(2) == 7);
            TS_ASSERT(tm2.getValueForKey_MapOfField1(3) == 6);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage9() {
            TestMessage9 tm1;
            {
                TestMessage1 tm;
                tm.setField1(158);
                tm1.putTo_MapOfField1(1, tm);
            }
            {
                TestMessage1 tm;
                tm.setField1(157);
                tm1.putTo_MapOfField1(2, tm);
            }
            {
                TestMessage1 tm;
                tm.setField1(156);
                tm1.putTo_MapOfField1(3, tm);
            }

            TS_ASSERT(tm1.containsKey_MapOfField1(1));
            TS_ASSERT(tm1.containsKey_MapOfField1(2));
            TS_ASSERT(tm1.containsKey_MapOfField1(3));
            TS_ASSERT(!tm1.containsKey_MapOfField1(4));
            TS_ASSERT(tm1.getValueForKey_MapOfField1(1).getField1() == 158);
            TS_ASSERT(tm1.getValueForKey_MapOfField1(2).getField1() == 157);
            TS_ASSERT(tm1.getValueForKey_MapOfField1(3).getField1() == 156);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read from buffer.
            TestMessage9 tm2;
            out >> tm2;

            TS_ASSERT(tm2.containsKey_MapOfField1(1));
            TS_ASSERT(tm2.containsKey_MapOfField1(2));
            TS_ASSERT(tm2.containsKey_MapOfField1(3));
            TS_ASSERT(!tm2.containsKey_MapOfField1(4));
            TS_ASSERT(tm2.getValueForKey_MapOfField1(1).getField1() == 158);
            TS_ASSERT(tm2.getValueForKey_MapOfField1(2).getField1() == 157);
            TS_ASSERT(tm2.getValueForKey_MapOfField1(3).getField1() == 156);
        }

        void testSerializationDeserializationTestMessage9Container() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            TestMessage9 tm1;
            {
                TestMessage1 tm;
                tm.setField1(158);
                tm1.putTo_MapOfField1(1, tm);
            }
            {
                TestMessage1 tm;
                tm.setField1(157);
                tm1.putTo_MapOfField1(2, tm);
            }
            {
                TestMessage1 tm;
                tm.setField1(156);
                tm1.putTo_MapOfField1(3, tm);
            }

            TS_ASSERT(tm1.containsKey_MapOfField1(1));
            TS_ASSERT(tm1.containsKey_MapOfField1(2));
            TS_ASSERT(tm1.containsKey_MapOfField1(3));
            TS_ASSERT(!tm1.containsKey_MapOfField1(4));
            TS_ASSERT(tm1.getValueForKey_MapOfField1(1).getField1() == 158);
            TS_ASSERT(tm1.getValueForKey_MapOfField1(2).getField1() == 157);
            TS_ASSERT(tm1.getValueForKey_MapOfField1(3).getField1() == 156);

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read from buffer.
            Container c2;
            out >> c2;

            TS_ASSERT(c2.getDataType() == TestMessage9::ID());

            TestMessage9 tm2 = c2.getData<TestMessage9>();

            TS_ASSERT(tm2.containsKey_MapOfField1(1));
            TS_ASSERT(tm2.containsKey_MapOfField1(2));
            TS_ASSERT(tm2.containsKey_MapOfField1(3));
            TS_ASSERT(!tm2.containsKey_MapOfField1(4));
            TS_ASSERT(tm2.getValueForKey_MapOfField1(1).getField1() == 158);
            TS_ASSERT(tm2.getValueForKey_MapOfField1(2).getField1() == 157);
            TS_ASSERT(tm2.getValueForKey_MapOfField1(3).getField1() == 156);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessage10() {
            TestMessage10 tm1;
            TS_ASSERT(tm1.getSize_MyArray1() == 2);
            TS_ASSERT(tm1.getSize_MyArray2() == 3);

            uint32_t *tm1_arr1 = tm1.getMyArray1();
            tm1_arr1[0] = 1; tm1_arr1[1] = 2;
            float *tm1_arr2 = tm1.getMyArray2();
            tm1_arr2[0] = -1.2345; tm1_arr2[1] = -2.3456; tm1_arr2[2] = -3.4567;

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            // Read from buffer.
            TestMessage10 tm2;
            out >> tm2;

            uint32_t *tm2_arr1 = tm2.getMyArray1();
            float *tm2_arr2 = tm2.getMyArray2();

            TS_ASSERT(tm2.getSize_MyArray1() == 2);
            TS_ASSERT(tm2.getSize_MyArray2() == 3);
            TS_ASSERT(tm2_arr1[0] == 1);
            TS_ASSERT(tm2_arr1[1] == 2);
            TS_ASSERT_DELTA(tm2_arr2[0], -1.2345, 1e-4);
            TS_ASSERT_DELTA(tm2_arr2[1], -2.3456, 1e-4);
            TS_ASSERT_DELTA(tm2_arr2[2], -3.4567, 1e-4);
        }

        void testSerializationDeserializationTestMessage10ValidatedWithGoogleProtobuf() {
            TestMessage10 tm1;
            TS_ASSERT(tm1.getSize_MyArray1() == 2);
            TS_ASSERT(tm1.getSize_MyArray2() == 3);

            uint32_t *tm1_arr1 = tm1.getMyArray1();
            tm1_arr1[0] = 1; tm1_arr1[1] = 2;
            float *tm1_arr2 = tm1.getMyArray2();
            tm1_arr2[0] = -1.2345; tm1_arr2[1] = -2.3456; tm1_arr2[2] = -3.4567;

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            const string s = out.str();
            TS_ASSERT(s.size() == 18);
            uint32_t cnt=0;
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xa);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x2);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x1);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x2);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x12);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xc);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x19);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x4);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x9e);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xbf);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x4f);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x1e);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x16);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xc0);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x93);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x3a);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x5d);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xc0);

            // Read from buffer.
            TestMessage10 tm2;
            out >> tm2;

            uint32_t *tm2_arr1 = tm2.getMyArray1();
            float *tm2_arr2 = tm2.getMyArray2();

            TS_ASSERT(tm2.getSize_MyArray1() == 2);
            TS_ASSERT(tm2.getSize_MyArray2() == 3);
            TS_ASSERT(tm2_arr1[0] == 1);
            TS_ASSERT(tm2_arr1[1] == 2);
            TS_ASSERT_DELTA(tm2_arr2[0], -1.2345, 1e-4);
            TS_ASSERT_DELTA(tm2_arr2[1], -2.3456, 1e-4);
            TS_ASSERT_DELTA(tm2_arr2[2], -3.4567, 1e-4);
        }

        void testSerializationDeserializationTestMessage10Container() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            TestMessage10 tm1;
            TS_ASSERT(tm1.getSize_MyArray1() == 2);
            TS_ASSERT(tm1.getSize_MyArray2() == 3);

            uint32_t *tm1_arr1 = tm1.getMyArray1();
            tm1_arr1[0] = 1; tm1_arr1[1] = 2;
            float *tm1_arr2 = tm1.getMyArray2();
            tm1_arr2[0] = -1.2345; tm1_arr2[1] = -2.3456; tm1_arr2[2] = -3.4567;

            Container c(tm1);

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            // Read from buffer.
            Container c2;
            out >> c2;

            TS_ASSERT(c2.getDataType() == TestMessage10::ID());

            TestMessage10 tm2 = c2.getData<TestMessage10>();

            uint32_t *tm2_arr1 = tm2.getMyArray1();
            float *tm2_arr2 = tm2.getMyArray2();

            TS_ASSERT(tm2.getSize_MyArray1() == 2);
            TS_ASSERT(tm2.getSize_MyArray2() == 3);
            TS_ASSERT(tm2_arr1[0] == 1);
            TS_ASSERT(tm2_arr1[1] == 2);
            TS_ASSERT_DELTA(tm2_arr2[0], -1.2345, 1e-4);
            TS_ASSERT_DELTA(tm2_arr2[1], -2.3456, 1e-4);
            TS_ASSERT_DELTA(tm2_arr2[2], -3.4567, 1e-4);
        }

        ///////////////////////////////////////////////////////////////////////

        void testSerializationDeserializationTestMessageTimeStampValidatedWithGoogleProtobuf() {
            TimeStamp tm1(123, 456);

            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            // Serialize via regular Serializer.
            stringstream out;
            out << tm1;

            const string s = out.str();
            TS_ASSERT(s.size() == 6);
            uint32_t cnt=0;
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xf6);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x1);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x10);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x90);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x7);

            // Read from buffer.
            TimeStamp tm2;
            out >> tm2;

            TS_ASSERT(tm2.getSeconds() == tm1.getSeconds());
            TS_ASSERT(tm2.getFractionalMicroseconds() == tm1.getFractionalMicroseconds());
        }

        void testSerializationDeserializationTestMessage2IntoContainerValidatedWithGoogleProtobuf() {
            // Replace default serializer/deserializers.
            SerializationFactoryTestCase tmp;
            (void)tmp;

            TestMessage2 tm1;
            tm1.setField1(123);
            tm1.setField2(-123);

            Container c(tm1);
            c.setSentTimeStamp(TimeStamp(456, 789));
            c.setReceivedTimeStamp(TimeStamp(987, 654));
            c.setSampleTimeStamp(TimeStamp(123, 456));

            // Serialize via regular Serializer.
            stringstream out;
            out << c;

            const string s = out.str();
            uint32_t cnt=0;
            TS_ASSERT(s.size() == 39);
            // Container header:
            // d a4 1a 0 0
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x0D);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xA4);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x22);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0);

            // Actual container:
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xd4);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xf);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x12);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x5);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x7b);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x10);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xf5);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x1);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x1a);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x6);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x90);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x7);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x10);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xaa);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xc);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x22);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x6);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xb6);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xf);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x10);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x9c);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xa);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x2a);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x6);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x8);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0xf6);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x1);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x10);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x90);
            TS_ASSERT(static_cast<uint8_t>(s.at(cnt++)) == 0x7);

            // Read from buffer.
            Container c2;
            out >> c2;

            TS_ASSERT(c2.getDataType() == TestMessage2::ID());
            TestMessage2 tm2 = c2.getData<TestMessage2>();

            TS_ASSERT(tm1.getField1() == tm2.getField1());
            TS_ASSERT(tm2.getField1() == 123);

            TS_ASSERT(tm1.getField2() == tm2.getField2());
            TS_ASSERT(tm2.getField2() == -123);
        }

        ///////////////////////////////////////////////////////////////////////

};

#endif /*CORE_PROTOMESSAGESTESTSUITE_H_*/
