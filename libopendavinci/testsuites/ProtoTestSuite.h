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

#ifndef CORE_PROTOTESTSUITE_H_
#define CORE_PROTOTESTSUITE_H_

#include <cmath>                        // for fabs
#include <iostream>                     // for stringstream, operator<<, etc
#include <memory>
#include <string>                       // for operator==, basic_string, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"     // for Deserializer
#include "opendavinci/odcore/serialization/ProtoDeserializerVisitor.h"
#include "opendavinci/odcore/serialization/ProtoSerializerVisitor.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/odcore/serialization/Serializer.h"       // for Serializer
#include "opendavinci/odcore/base/Visitable.h"        // for Visitable
#include "opendavinci/odcore/base/Visitor.h"          // for Visitor
#include "opendavinci/odcore/data/SerializableData.h"  // for SerializableData
#include "opendavinci/generated/odcore/data/SharedData.h"  // for SharedData
#include "opendavinci/generated/odcore/data/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"  // for SharedImage
#include "opendavinci/generated/odcore/data/dmcp/ServerInformation.h"

using namespace std;
using namespace odcore::base;
using namespace odcore::data;
using namespace odcore::data::dmcp;
using namespace odcore::data::image;

/*
  Generated from:

    message ProtoVehicleControl [id = 41] {
        double speed [id = 1, fourbyteid = 0x0E43596B];
        double acceleration [id = 2, fourbyteid = 0x0E435991];
        double steeringWheelAngle [id = 3, fourbyteid = 0x0E435969];
        bool brakeLights [id = 4, fourbyteid = 0x0E43599B];
        bool flashingLightsLeft [id = 5, fourbyteid = 0x09823BD7];
        bool flashingLightsRight [id = 6, fourbyteid = 0x0E435996];
    }
 */
class ProtoVehicleControl : public odcore::data::SerializableData, public odcore::base::Visitable {
    public:

    ProtoVehicleControl() :
        SerializableData(), Visitable()
        , m_speed(0.0)
        , m_acceleration(0.0)
        , m_steeringWheelAngle(0.0)
        , m_brakeLights(false)
        , m_flashingLightsLeft(false)
        , m_flashingLightsRight(false)
    {
    }

    ProtoVehicleControl(
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

    ProtoVehicleControl(const ProtoVehicleControl &obj) :
        SerializableData(), Visitable()
        , m_speed(obj.m_speed)
        , m_acceleration(obj.m_acceleration)
        , m_steeringWheelAngle(obj.m_steeringWheelAngle)
        , m_brakeLights(obj.m_brakeLights)
        , m_flashingLightsLeft(obj.m_flashingLightsLeft)
        , m_flashingLightsRight(obj.m_flashingLightsRight)
    {
    }
    
    ~ProtoVehicleControl() {
    }

    ProtoVehicleControl& operator=(const ProtoVehicleControl &obj) {
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

    void accept(odcore::base::Visitor &v) {
        v.beginVisit();
        v.visit(1, "ProtoVehicleControl.speed", "speed", m_speed);
        v.visit(2, "ProtoVehicleControl.acceleration", "acceleration", m_acceleration);
        v.visit(3, "ProtoVehicleControl.steeringWheelAngle", "steeringWheelAngle", m_steeringWheelAngle);
        v.visit(4, "ProtoVehicleControl.brakeLights", "brakeLights", m_brakeLights);
        v.visit(5, "ProtoVehicleControl.flashingLightsLeft", "flashingLightsLeft", m_flashingLightsLeft);
        v.visit(6, "ProtoVehicleControl.flashingLightsRight", "flashingLightsRight", m_flashingLightsRight);
        v.endVisit();
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

        std::shared_ptr<Serializer> s = sf.getSerializer(out);

        s->write(1, m_speed);
        s->write(2, m_acceleration);
        s->write(3, m_steeringWheelAngle);
        s->write(4, m_brakeLights);
        s->write(5, m_flashingLightsLeft);
        s->write(6, m_flashingLightsRight);
        return out;
    }

    istream& operator>>(istream &in) {

        SerializationFactory& sf = SerializationFactory::getInstance();

        std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

        d->read(1, m_speed);
        d->read(2, m_acceleration);
        d->read(3, m_steeringWheelAngle);
        d->read(4, m_brakeLights);
        d->read(5, m_flashingLightsLeft);
        d->read(6, m_flashingLightsRight);
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


class ProtoTest : public CxxTest::TestSuite {
    public:
        void testSerializationDeserialization() {
            SharedData sd;
            sd.setName("Hello World!");
            sd.setSize(42);

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            sd.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);


            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            SharedData sd2;
            sd2.accept(protoDeserializerVisitor);

            TS_ASSERT(sd.getName() == sd2.getName());
            TS_ASSERT(sd.getSize() == sd2.getSize());
        }

        void testSerializationDeserializationEnum() {
            ServerInformation si;
            si.setIP("localhost");
            si.setPort(7890);
            si.setManagedLevel(ServerInformation::ML_SIMULATION_RT);

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            si.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);

            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            ServerInformation si2;
            si2.accept(protoDeserializerVisitor);

            TS_ASSERT(si.getIP() == si2.getIP());
            TS_ASSERT(si.getPort() == si2.getPort());
            TS_ASSERT(si.getManagedLevel() == si2.getManagedLevel());
        }

        void testSerializationDeserializationInheritance() {
            SharedImage si;
            si.setName("Hello World!");
            si.setSize(42);
            si.setWidth(2);
            si.setHeight(21);
            si.setBytesPerPixel(1);

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            si.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);

            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            SharedImage si2;
            si2.accept(protoDeserializerVisitor);

            TS_ASSERT(si.getName() == si2.getName());
            TS_ASSERT(si.getSize() == si2.getSize());
            TS_ASSERT(si.getWidth() == si2.getWidth());
            TS_ASSERT(si.getHeight() == si2.getHeight());
            TS_ASSERT(si.getBytesPerPixel() == si2.getBytesPerPixel());
        }

        void testSerializationDeserializationFloatingPoint() {
            ModuleDescriptor md;
            md.setName("Hello World!");
            md.setIdentifier("42");
            md.setVersion("2");
            md.setFrequency(1.234);

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            md.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);

            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            ModuleDescriptor md2;
            md2.accept(protoDeserializerVisitor);

            TS_ASSERT(md.getName() == md2.getName());
            TS_ASSERT(md.getIdentifier() == md2.getIdentifier());
            TS_ASSERT(md.getVersion() == md2.getVersion());
            TS_ASSERT(fabs(md.getFrequency() - md2.getFrequency()) < 1e-4);
        }

        void testSerializationDeserializationNullValues() {
            ProtoVehicleControl vcRef;
            vcRef.setSpeed(0);
            vcRef.setAcceleration(0);
            vcRef.setSteeringWheelAngle(0);
            vcRef.setBrakeLights(true);
            vcRef.setLeftFlashingLights(false);
            vcRef.setRightFlashingLights(true);

            // Create a Proto serialization visitor.
            ProtoSerializerVisitor protoSerializerVisitor;
            vcRef.accept(protoSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            protoSerializerVisitor.getSerializedData(out);

            // Create a Proto deserialization visitor.
            ProtoDeserializerVisitor protoDeserializerVisitor;
            protoDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            ProtoVehicleControl vcRef2;
            vcRef2.setSpeed(2);
            vcRef2.setAcceleration(5);
            vcRef2.setSteeringWheelAngle(9);
            vcRef2.setBrakeLights(false);
            vcRef2.setLeftFlashingLights(true);
            vcRef2.setRightFlashingLights(false);

            // Verify that both data structures are different.
            TS_ASSERT(fabs(vcRef.getSpeed() - vcRef2.getSpeed()) > 1e-4);
            TS_ASSERT(fabs(vcRef.getAcceleration() - vcRef2.getAcceleration()) > 1e-4);
            TS_ASSERT(fabs(vcRef.getSteeringWheelAngle() - vcRef2.getSteeringWheelAngle()) > 1e-4);
            TS_ASSERT(vcRef.getBrakeLights() != vcRef2.getBrakeLights());
            TS_ASSERT(vcRef.getLeftFlashingLights() != vcRef2.getLeftFlashingLights());
            TS_ASSERT(vcRef.getRightFlashingLights() != vcRef2.getRightFlashingLights());

            // Read back the data using the deserializer.
            vcRef2.accept(protoDeserializerVisitor);

            // Verify that the two data structures are identical.
            TS_ASSERT(fabs(vcRef.getSpeed() - vcRef2.getSpeed()) < 1e-4);
            TS_ASSERT(fabs(vcRef.getAcceleration() - vcRef2.getAcceleration()) < 1e-4);
            TS_ASSERT(fabs(vcRef.getSteeringWheelAngle() - vcRef2.getSteeringWheelAngle()) < 1e-4);
            TS_ASSERT(vcRef.getBrakeLights() == vcRef2.getBrakeLights());
            TS_ASSERT(vcRef.getLeftFlashingLights() == vcRef2.getLeftFlashingLights());
            TS_ASSERT(vcRef.getRightFlashingLights() == vcRef2.getRightFlashingLights());
        }
};

#endif /*CORE_PROTOTESTSUITE_H_*/
