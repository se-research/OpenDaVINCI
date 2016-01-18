/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2015 Christian Berger
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

#ifndef CORE_VISITABLETESTSUITE_H_
#define CORE_VISITABLETESTSUITE_H_

#include <iostream>                     // for operator<<, basic_ostream, etc
#include <string>                       // for operator<<, string, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/SharedPointer.h"         // for SharedPointer
#include "opendavinci/core/base/Deserializer.h"     // for Deserializer
#include "opendavinci/core/base/Hash.h"             // for CharList, CRC32, etc
#include "opendavinci/core/base/QueryableNetstringsDeserializerVisitor.h"
#include "opendavinci/core/base/QueryableNetstringsSerializerVisitor.h"
#include "opendavinci/core/base/Serializable.h"     // for operator<<, Serializable
#include "opendavinci/core/base/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/core/base/Serializer.h"       // for Serializer
#include "opendavinci/core/base/Visitable.h"        // for Visitable
#include "opendavinci/core/base/Visitor.h"          // for Visitor

using namespace std;
using namespace core;
using namespace core::base;

// An example data object.
class MyNestedVisitable : public core::base::Serializable {
    public:
        MyNestedVisitable() :
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

class MyVisitable : public Serializable, public Visitable {
    public:
        MyVisitable() :
            Serializable(),
            Visitable(),
            m_att1(0),
            m_att2(0),
            m_att3(0),
            m_att4(""),
            m_att5() {}

        MyVisitable(const MyVisitable &obj) :
            Serializable(obj),
            Visitable(obj),
            m_att1(obj.m_att1),
            m_att2(obj.m_att2),
            m_att3(obj.m_att3),
            m_att4(obj.m_att4),
            m_att5() {}

        ~MyVisitable() {}

        MyVisitable& operator=(const MyVisitable &obj) {
            m_att1 = obj.m_att1;
            m_att2 = obj.m_att2;
            m_att3 = obj.m_att3;
            m_att4 = obj.m_att4;
            m_att5 = obj.m_att5;
            return *this;
        }

        virtual ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();
		
			SharedPointer<Serializer> s = sf.getSerializer(out);
		
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'1', NullType> > > > >::RESULT,
					m_att1);

			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'2', NullType> > > > >::RESULT,
					m_att2);

			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'3', NullType> > > > >::RESULT,
					m_att3);

			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'4', NullType> > > > >::RESULT,
					m_att4);

			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'5', NullType> > > > >::RESULT,
					m_att5);

			return out;
        }

        virtual istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();
		
			SharedPointer<Deserializer> d = sf.getDeserializer(in);
		
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'1', NullType> > > > >::RESULT,
					m_att1);

			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'2', NullType> > > > >::RESULT,
					m_att2);

			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'3', NullType> > > > >::RESULT,
					m_att3);

			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'4', NullType> > > > >::RESULT,
					m_att4);

			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'5', NullType> > > > >::RESULT,
					m_att5);

			return in;
        }

        virtual void accept(core::base::Visitor &v) {
            v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'1', NullType> > > > >::RESULT, 1, "MyVisitable::att1", "att1", m_att1);
            v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'2', NullType> > > > >::RESULT, 2, "MyVisitable::att2", "att2", m_att2);
            v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'3', NullType> > > > >::RESULT, 3, "MyVisitable::att3", "att3", m_att3);
            v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'4', NullType> > > > >::RESULT, 4, "MyVisitable::att4", "att4", m_att4);
            v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'5', NullType> > > > >::RESULT, 5, "MyVisitable::att5", "att5", m_att5);
        }

    public:
        uint32_t m_att1;
        float m_att2;
        double m_att3;
        string m_att4;
        MyNestedVisitable m_att5;
};

// Pretty printer.
class MyPrintVisitor : public Visitor {
    public:
        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, Serializable &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, bool &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, char &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, unsigned char &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int8_t &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int16_t &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint16_t &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int32_t &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint32_t &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int64_t &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint64_t &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, float &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, double &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, string &v) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << v << endl;
        }

        virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, void *data, const uint32_t &size) {
            cout << longId << ", " << (int)shortId << ", " << longName << ", " << shortName << ", " << data << ", " << size << endl;
        }
};

// The actual test case.
class VisitableTest : public CxxTest::TestSuite {
    public:
        void testSerializationDeserializationVisitors() {
            MyVisitable myV;

            // Pretty print the object's attributes.
            MyPrintVisitor print;
            myV.accept(print);

            // Set the object's attributes.
            myV.m_att1 = 1;
            myV.m_att2 = 3.2;
            myV.m_att3 = -1.3;
            myV.m_att4 = "Hello World!";
            myV.m_att5.m_double=-31e-2;
            myV.accept(print);

            // Serialize the object using the default implementation.
            stringstream sstr;
            sstr << myV;

            // Instantiate a serialization visitor.
            QueryableNetstringsSerializerVisitor serVisitor;
            myV.accept(serVisitor);

            // Write the serialization data into a stringstream object.
            stringstream ser_sstr;
            serVisitor.getSerializedData(ser_sstr);
            TS_ASSERT(ser_sstr.str() == sstr.str());

            // A new object shall not match the existing object.
            MyVisitable myV2;
            stringstream sstr2;
            sstr2 << myV2;
            TS_ASSERT(ser_sstr.str() != sstr2.str());

            // Deserialize the object using a visitor.
            QueryableNetstringsDeserializerVisitor deserVisitor;
            deserVisitor.deserializeDataFrom(ser_sstr);
            myV2.accept(deserVisitor);

            TS_ASSERT_DELTA(myV2.m_att5.m_double, -31e-2, 1e-5);
            
            stringstream sstr3;
            sstr3 << myV2;
            TS_ASSERT(ser_sstr.str() == sstr3.str());

            // Read a second time from the deserialized object.
            MyVisitable myV3;
            myV3.accept(deserVisitor);

            stringstream sstr4;
            sstr4 << myV3;
            TS_ASSERT(ser_sstr.str() == sstr4.str());
        }

        void testReuseDeserializationVisitors() {
            MyVisitable myV;

            // Pretty print the object's attributes.
            MyPrintVisitor print;
            myV.accept(print);

            // Set the object's attributes.
            myV.m_att1 = 1;
            myV.m_att2 = 3.2;
            myV.m_att3 = -1.3;
            myV.m_att4 = "Hello World!";
            myV.m_att5.m_double=-31e-2;
            myV.accept(print);

            // Serialize the object using the default implementation.
            stringstream sstr;
            sstr << myV;

            // Instantiate a serialization visitor.
            QueryableNetstringsSerializerVisitor serVisitor;
            myV.accept(serVisitor);

            // Write the serialization data into a stringstream object.
            stringstream ser_sstr;
            serVisitor.getSerializedData(ser_sstr);
            TS_ASSERT(ser_sstr.str() == sstr.str());

            // A new object shall not match the existing object.
            MyVisitable myV2;
            stringstream sstr2;
            sstr2 << myV2;
            TS_ASSERT(ser_sstr.str() != sstr2.str());

            // Deserialize the object using a visitor.
            QueryableNetstringsDeserializerVisitor deserVisitor;
            deserVisitor.deserializeDataFrom(ser_sstr);
            myV2.accept(deserVisitor);

            stringstream sstr3;
            sstr3 << myV2;
            TS_ASSERT(ser_sstr.str() == sstr3.str());

            // Modify the object's attributes.
            myV.m_att1 = -1;
            myV.m_att2 = -3.2;
            myV.m_att3 = 1.3;
            myV.m_att4 = "Hello again, World!";
            myV.m_att5.m_double=31e-2;
            myV.accept(print);

            sstr.str("");
            sstr << myV;
            TS_ASSERT(ser_sstr.str() != sstr.str());
            TS_ASSERT(sstr.str() != sstr3.str());

            deserVisitor.deserializeDataFrom(sstr);
            myV2.accept(deserVisitor);

            // Reuse the same deserialization visitor but deserialize from different data.
            sstr3.str("");
            sstr3 << myV2;
            TS_ASSERT(sstr.str() == sstr3.str());
        }
};

#endif /*CORE_VISITABLETESTSUITE_H_*/
