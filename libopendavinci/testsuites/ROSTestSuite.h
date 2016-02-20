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

#ifndef CORE_ROSTESTSUITE_H_
#define CORE_ROSTESTSUITE_H_

#include <cmath>                        // for fabs
#include <iostream>                     // for stringstream, operator<<, etc
#include <string>                       // for operator==, string, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/SharedPointer.h"         // for SharedPointer
#include "opendavinci/core/base/Deserializer.h"     // for Deserializer
#include "opendavinci/core/base/ROSDeserializerVisitor.h"
#include "opendavinci/core/base/ROSSerializerVisitor.h"  // for ROSSerializerVisitor
#include "opendavinci/core/base/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/core/base/Serializer.h"       // for Serializer
#include "opendavinci/core/base/Visitable.h"        // for Visitable
#include "opendavinci/core/base/Visitor.h"          // for Visitor
#include "opendavinci/core/data/SerializableData.h"  // for SerializableData
#include "opendavinci/generated/coredata/SharedData.h"  // for SharedData
#include "opendavinci/generated/coredata/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/coredata/image/SharedImage.h"  // for SharedImage

using namespace std;
using namespace core::base;
using namespace coredata;
using namespace coredata::dmcp;
using namespace coredata::image;

/*
  Generated from:

    message ROSVehicleControl [id = 41] {
        double speed [fourbyteid = 0x0E43596B];
        double acceleration [fourbyteid = 0x0E435991];
        double steeringWheelAngle [fourbyteid = 0x0E435969];
        bool brakeLights [fourbyteid = 0x0E43599B];
        bool flashingLightsLeft [fourbyteid = 0x09823BD7];
        bool flashingLightsRight [fourbyteid = 0x0E435996];
    }
 */
class ROSVehicleControl : public core::data::SerializableData, public core::base::Visitable {
	public:

	ROSVehicleControl() :
	    SerializableData(), Visitable()
		, m_speed(0.0)
		, m_acceleration(0.0)
		, m_steeringWheelAngle(0.0)
		, m_brakeLights(false)
		, m_flashingLightsLeft(false)
		, m_flashingLightsRight(false)
	{
	}

	ROSVehicleControl(
		const double &val0, 
		const double &val1, 
		const double &val2, 
		const bool &val3, 
		const bool &val4, 
		const bool &val5
	) :
	    SerializableData(), Visitable()
		, m_speed(val0)
		, m_acceleration(val1)
		, m_steeringWheelAngle(val2)
		, m_brakeLights(val3)
		, m_flashingLightsLeft(val4)
		, m_flashingLightsRight(val5)
	{
	}

	ROSVehicleControl(const ROSVehicleControl &obj) :
	    SerializableData(), Visitable()
		, m_speed(obj.m_speed)
		, m_acceleration(obj.m_acceleration)
		, m_steeringWheelAngle(obj.m_steeringWheelAngle)
		, m_brakeLights(obj.m_brakeLights)
		, m_flashingLightsLeft(obj.m_flashingLightsLeft)
		, m_flashingLightsRight(obj.m_flashingLightsRight)
	{
	}
	
	~ROSVehicleControl() {
	}

	ROSVehicleControl& operator=(const ROSVehicleControl &obj) {
		m_speed = obj.m_speed;
		m_acceleration = obj.m_acceleration;
		m_steeringWheelAngle = obj.m_steeringWheelAngle;
		m_brakeLights = obj.m_brakeLights;
		m_flashingLightsLeft = obj.m_flashingLightsLeft;
		m_flashingLightsRight = obj.m_flashingLightsRight;
		return (*this);
	}

	int32_t ID() {
		return 41;
	}

	const string ShortName() {
		return "VehicleControl";
	}

	const string LongName() {
		return "automotive.VehicleControl";
	}

    int32_t getID() const {
        return 41;
    }

    const string getLongName() const {
        return "automotive.VehicleControl";
    }

    const string getShortName() const {
        return "VehicleControl";
    }

	double getSpeed() const {
		return m_speed;
	}
	
	void setSpeed(const double &val) {
		m_speed = val;
	}
	double getAcceleration() const {
		return m_acceleration;
	}
	
	void setAcceleration(const double &val) {
		m_acceleration = val;
	}
	double getSteeringWheelAngle() const {
		return m_steeringWheelAngle;
	}
	
	void setSteeringWheelAngle(const double &val) {
		m_steeringWheelAngle = val;
	}
	bool getBrakeLights() const {
		return m_brakeLights;
	}
	
	void setBrakeLights(const bool &val) {
		m_brakeLights = val;
	}
	bool getLeftFlashingLights() const {
		return m_flashingLightsLeft;
	}
	
	void setLeftFlashingLights(const bool &val) {
		m_flashingLightsLeft = val;
	}
	bool getRightFlashingLights() const {
		return m_flashingLightsRight;
	}
	
	void setRightFlashingLights(const bool &val) {
		m_flashingLightsRight = val;
	}

	void accept(core::base::Visitor &v) {
		v.visit(0x0E43596B, 0, "ROSVehicleControl.speed", "speed", m_speed);
		v.visit(0x0E435991, 0, "ROSVehicleControl.acceleration", "acceleration", m_acceleration);
		v.visit(0x0E435969, 0, "ROSVehicleControl.steeringWheelAngle", "steeringWheelAngle", m_steeringWheelAngle);
		v.visit(0x0E43599B, 0, "ROSVehicleControl.brakeLights", "brakeLights", m_brakeLights);
		v.visit(0x09823BD7, 0, "ROSVehicleControl.flashingLightsLeft", "flashingLightsLeft", m_flashingLightsLeft);
		v.visit(0x0E435996, 0, "ROSVehicleControl.flashingLightsRight", "flashingLightsRight", m_flashingLightsRight);
	}

	const string toString() const {
		stringstream s;


		s << "Speed: " << getSpeed() << " ";
		s << "Acceleration: " << getAcceleration() << " ";
		s << "SteeringWheelAngle: " << getSteeringWheelAngle() << " ";
		s << "BrakeLights: " << getBrakeLights() << " ";
		s << "FlashingLightsLeft: " << getLeftFlashingLights() << " ";
		s << "FlashingLightsRight: " << getRightFlashingLights() << " ";

		return s.str();
	}

	ostream& operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Serializer> s = sf.getSerializer(out);

		s->write(0x0E43596B, m_speed);
		s->write(0x0E435991, m_acceleration);
		s->write(0x0E435969, m_steeringWheelAngle);
		s->write(0x0E43599B, m_brakeLights);
		s->write(0x09823BD7, m_flashingLightsLeft);
		s->write(0x0E435996, m_flashingLightsRight);
		return out;
	}

	istream& operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

		d->read(0x0E43596B, m_speed);
		d->read(0x0E435991, m_acceleration);
		d->read(0x0E435969, m_steeringWheelAngle);
		d->read(0x0E43599B, m_brakeLights);
		d->read(0x09823BD7, m_flashingLightsLeft);
		d->read(0x0E435996, m_flashingLightsRight);
		return in;
	}

	private:
		double m_speed;
	private:
		double m_acceleration;
	private:
		double m_steeringWheelAngle;
	private:
		bool m_brakeLights;
	private:
		bool m_flashingLightsLeft;
	private:
		bool m_flashingLightsRight;
};


class ROSTest : public CxxTest::TestSuite {
    public:
        void testSerializationDeserialization() {
            SharedData sd;
            sd.setName("Hello World!");
            sd.setSize(42);

            // Create an LCM serialization visitor.
            ROSSerializerVisitor rosSerializerVisitor;
            rosSerializerVisitor.setMessageID(2);
            sd.accept(rosSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            rosSerializerVisitor.getSerializedData(out);

            // Create an LCM deserialization visitor.
            ROSDeserializerVisitor rosDeserializerVisitor;
            rosDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            SharedData sd2;
            sd2.accept(rosDeserializerVisitor);

            TS_ASSERT(sd.getName() == sd2.getName());
            TS_ASSERT(sd.getSize() == sd2.getSize());
            TS_ASSERT(rosDeserializerVisitor.getMessageID() == 2);
        }

        void testSerializationDeserializationInheritance() {
            SharedImage si;
            si.setName("Hello World!");
            si.setSize(42);
            si.setWidth(2);
            si.setHeight(21);
            si.setBytesPerPixel(1);

            // Create an LCM serialization visitor.
            ROSSerializerVisitor rosSerializerVisitor;
            rosSerializerVisitor.setMessageID(3);
            si.accept(rosSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            rosSerializerVisitor.getSerializedData(out);

            // Create an LCM deserialization visitor.
            ROSDeserializerVisitor rosDeserializerVisitor;
            rosDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            SharedImage si2;
            si2.accept(rosDeserializerVisitor);

            TS_ASSERT(si.getName() == si2.getName());
            TS_ASSERT(si.getSize() == si2.getSize());
            TS_ASSERT(si.getWidth() == si2.getWidth());
            TS_ASSERT(si.getHeight() == si2.getHeight());
            TS_ASSERT(si.getBytesPerPixel() == si2.getBytesPerPixel());
            TS_ASSERT(rosDeserializerVisitor.getMessageID() == 3);
        }

        void testSerializationDeserializationFloatingPoint() {
            ModuleDescriptor md;
            md.setName("Hello World!");
            md.setIdentifier("42");
            md.setVersion("2");
            md.setFrequency(1.234);

            // Create an LCM serialization visitor.
            ROSSerializerVisitor rosSerializerVisitor;
            rosSerializerVisitor.setMessageID(4);
            md.accept(rosSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            rosSerializerVisitor.getSerializedData(out);

            // Create an LCM deserialization visitor.
            ROSDeserializerVisitor rosDeserializerVisitor;
            rosDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            ModuleDescriptor md2;
            md2.accept(rosDeserializerVisitor);

            TS_ASSERT(md.getName() == md2.getName());
            TS_ASSERT(md.getIdentifier() == md2.getIdentifier());
            TS_ASSERT(md.getVersion() == md2.getVersion());
            TS_ASSERT(fabs(md.getFrequency() - md2.getFrequency()) < 1e-4);
            TS_ASSERT(rosDeserializerVisitor.getMessageID() == 4);
        }

        void testRosSerialisation() {
            // Reference data structure.
            ROSVehicleControl vcRef;
            vcRef.setSpeed(2.0);
            vcRef.setAcceleration(1.6);
            vcRef.setSteeringWheelAngle(32);
            vcRef.setBrakeLights(true);
            vcRef.setLeftFlashingLights(false);
            vcRef.setRightFlashingLights(true);

            stringstream rawDataStream;

            // Serialized raw data.
            string data = "0 0 0 0 0 0 1 0 64 0 0 0 0 0 0 0 63 -7 -103 -103 -103 -103 -103 -102 64 64 0 0 0 0 0 0 1 0 1 0";
            stringstream sstr(data);
            while (sstr.good()) {
                int i = 0;
                sstr >> i;
                char c = (char)i;
                rawDataStream << c; 
            }

            // Deserialize from raw data.
            ROSDeserializerVisitor rosDeserializerVisitor;
            rosDeserializerVisitor.deserializeDataFrom(rawDataStream);

            // Set data in data structure.
            ROSVehicleControl vc;
            vc.accept(rosDeserializerVisitor);

            // Compare deserialized data with reference data.
            TS_ASSERT(fabs(vc.getSpeed() - vcRef.getSpeed()) < 1e-5);
            TS_ASSERT(fabs(vc.getAcceleration() - vcRef.getAcceleration()) < 1e-5);
            TS_ASSERT(fabs(vc.getSteeringWheelAngle() - vcRef.getSteeringWheelAngle()) < 1e-5);
            TS_ASSERT(vc.getBrakeLights() == vcRef.getBrakeLights());
            TS_ASSERT(vc.getLeftFlashingLights() == vcRef.getLeftFlashingLights());
            TS_ASSERT(vc.getRightFlashingLights() == vcRef.getRightFlashingLights());

            // Serialize reference data.
            ROSSerializerVisitor rosSerializerVisitor;
            vcRef.accept(rosSerializerVisitor);

            // Get serialized bytes.
            stringstream out;
            rosSerializerVisitor.getSerializedData(out);

            // Read back from serialized bytes re-using the deserializer.
            rosDeserializerVisitor.deserializeDataFrom(out);

            // Fill new data structure.
            ROSVehicleControl vc3;
            vc3.accept(rosDeserializerVisitor);

            TS_ASSERT(fabs(vc3.getSpeed() - vcRef.getSpeed()) < 1e-5);
            TS_ASSERT(fabs(vc3.getAcceleration() - vcRef.getAcceleration()) < 1e-5);
            TS_ASSERT(fabs(vc3.getSteeringWheelAngle() - vcRef.getSteeringWheelAngle()) < 1e-5);
            TS_ASSERT(vc3.getBrakeLights() == vcRef.getBrakeLights());
            TS_ASSERT(vc3.getLeftFlashingLights() == vcRef.getLeftFlashingLights());
            TS_ASSERT(vc3.getRightFlashingLights() == vcRef.getRightFlashingLights());
        }

};

#endif /*CORE_ROSTESTSUITE_H_*/
