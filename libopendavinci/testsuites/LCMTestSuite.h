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

#ifndef CORE_LCMTESTSUITE_H_
#define CORE_LCMTESTSUITE_H_

#include <cmath>                        // for fabs
#include <iostream>                     // for stringstream, operator<<, etc
#include <memory>
#include <string>                       // for operator==, basic_string, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"     // for Deserializer
#include "opendavinci/odcore/serialization/LCMDeserializerVisitor.h"
#include "opendavinci/odcore/serialization/LCMSerializerVisitor.h"  // for LCMSerializerVisitor
#include "opendavinci/odcore/base/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/odcore/base/Serializer.h"       // for Serializer
#include "opendavinci/odcore/base/Visitable.h"        // for Visitable
#include "opendavinci/odcore/base/Visitor.h"          // for Visitor
#include "opendavinci/odcore/data/SerializableData.h"  // for SerializableData
#include "opendavinci/generated/odcore/data/SharedData.h"  // for SharedData
#include "opendavinci/generated/odcore/data/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"  // for SharedImage

using namespace std;
using namespace odcore::base;
using namespace odcore::data;
using namespace odcore::data::dmcp;
using namespace odcore::data::image;

class LCMVehicleControl : public odcore::data::SerializableData, public odcore::base::Visitable {
    public:

    LCMVehicleControl() :
        SerializableData(), Visitable()
        , m_speed(0.0)
        , m_acceleration(0.0)
        , m_steeringWheelAngle(0.0)
        , m_brakeLights(false)
        , m_flashingLightsLeft(false)
        , m_flashingLightsRight(false)
    {
    }

    LCMVehicleControl(
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

    LCMVehicleControl(const LCMVehicleControl &obj) :
        SerializableData(), Visitable()
        , m_speed(obj.m_speed)
        , m_acceleration(obj.m_acceleration)
        , m_steeringWheelAngle(obj.m_steeringWheelAngle)
        , m_brakeLights(obj.m_brakeLights)
        , m_flashingLightsLeft(obj.m_flashingLightsLeft)
        , m_flashingLightsRight(obj.m_flashingLightsRight)
    {
    }
    
    ~LCMVehicleControl() {
    }

    LCMVehicleControl& operator=(const LCMVehicleControl &obj) {
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
        v.visit(1, "automotive.LCMVehicleControl.speed", "speed", m_speed);
        v.visit(2, "automotive.LCMVehicleControl.acceleration", "acceleration", m_acceleration);
        v.visit(3, "automotive.LCMVehicleControl.steeringWheelAngle", "steeringWheelAngle", m_steeringWheelAngle);
        v.visit(4, "automotive.LCMVehicleControl.brakeLights", "brakeLights", m_brakeLights);
        v.visit(5, "automotive.LCMVehicleControl.flashingLightsLeft", "flashingLightsLeft", m_flashingLightsLeft);
        v.visit(6, "automotive.LCMVehicleControl.flashingLightsRight", "flashingLightsRight", m_flashingLightsRight);
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


class LCMTest : public CxxTest::TestSuite {
    public:
        void testSerializationDeserialization() {
            SharedData sd;
            sd.setName("Hello World!");
            sd.setSize(42);

            // Create an LCM serialization visitor.
            LCMSerializerVisitor lcmSerializerVisitor;
            lcmSerializerVisitor.setChannelName("Test Channel");
            sd.accept(lcmSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            lcmSerializerVisitor.getSerializedData(out);

            // Create an LCM deserialization visitor.
            LCMDeserializerVisitor lcmDeserializerVisitor;
            lcmDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            SharedData sd2;
            sd2.accept(lcmDeserializerVisitor);

            TS_ASSERT(lcmDeserializerVisitor.getChannelName() == "Test Channel");
            TS_ASSERT(lcmSerializerVisitor.getHash() == lcmDeserializerVisitor.getDecodedHash());
            TS_ASSERT(lcmSerializerVisitor.getHash() == lcmDeserializerVisitor.getCalculatedHash());

            TS_ASSERT(sd.getName() == sd2.getName());
            TS_ASSERT(sd.getSize() == sd2.getSize());
        }

        void testSerializationDeserializationInheritance() {
            SharedImage si;
            si.setName("Hello World!");
            si.setSize(42);
            si.setWidth(2);
            si.setHeight(21);
            si.setBytesPerPixel(1);

            // Create an LCM serialization visitor.
            LCMSerializerVisitor lcmSerializerVisitor;
            lcmSerializerVisitor.setChannelName("Test Channel2");
            si.accept(lcmSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            lcmSerializerVisitor.getSerializedData(out);

            // Create an LCM deserialization visitor.
            LCMDeserializerVisitor lcmDeserializerVisitor;
            lcmDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            SharedImage si2;
            si2.accept(lcmDeserializerVisitor);

            TS_ASSERT(lcmDeserializerVisitor.getChannelName() == "Test Channel2");
            TS_ASSERT(lcmSerializerVisitor.getHash() == lcmDeserializerVisitor.getDecodedHash());
            TS_ASSERT(lcmSerializerVisitor.getHash() == lcmDeserializerVisitor.getCalculatedHash());

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

            // Create an LCM serialization visitor.
            LCMSerializerVisitor lcmSerializerVisitor;
            lcmSerializerVisitor.setChannelName("Test Channel3");
            md.accept(lcmSerializerVisitor);

            // Write the data to a stringstream.
            stringstream out;
            lcmSerializerVisitor.getSerializedData(out);

            // Create an LCM deserialization visitor.
            LCMDeserializerVisitor lcmDeserializerVisitor;
            lcmDeserializerVisitor.deserializeDataFrom(out);

            // Read back the data by using the visitor.
            ModuleDescriptor md2;
            md2.accept(lcmDeserializerVisitor);

            TS_ASSERT(lcmDeserializerVisitor.getChannelName() == "Test Channel3");
            TS_ASSERT(lcmSerializerVisitor.getHash() == lcmDeserializerVisitor.getDecodedHash());
            TS_ASSERT(lcmSerializerVisitor.getHash() == lcmDeserializerVisitor.getCalculatedHash());

            TS_ASSERT(md.getName() == md2.getName());
            TS_ASSERT(md.getIdentifier() == md2.getIdentifier());
            TS_ASSERT(md.getVersion() == md2.getVersion());
            TS_ASSERT(fabs(md.getFrequency() - md2.getFrequency()) < 1e-4);
        }

        void testLcmSerialisation() {
            /*
                Reference data structure in LCM (observe, no m_ precede the typenames):

                package automotive;

                struct VehicleControl
                {
                    double speed;
                    double acceleration;
                    double steeringWheelAngle;
                    boolean brakeLights;
                    boolean flashingLightsLeft;
                    boolean flashingLightsRight;
                }
            */

            // Reference data structure.
            LCMVehicleControl vcRef;
            vcRef.setSpeed(2.0);
            vcRef.setAcceleration(1.6);
            vcRef.setSteeringWheelAngle(32);
            vcRef.setBrakeLights(true);
            vcRef.setLeftFlashingLights(false);
            vcRef.setRightFlashingLights(true);

            stringstream rawDataStream;

            // Serialized raw data.
            string data = "76 67 48 50 0 0 0 0 52 49 0 -11 47 60 -13 -45 -45 -79 -114 64 0 0 0 0 0 0 0 63 -7 -103 -103 -103 -103 -103 -102 64 64 0 0 0 0 0 0 1 0 1";
            stringstream sstr(data);
            while (sstr.good()) {
                int i = 0;
                sstr >> i;
                char c = (char)i;
                rawDataStream << c; 
            }

            // Deserialize from raw data.
            LCMDeserializerVisitor lcmDeserializerVisitor;
            lcmDeserializerVisitor.deserializeDataFrom(rawDataStream);

            // Set data in data structure.
            LCMVehicleControl vc;
            vc.accept(lcmDeserializerVisitor);

            // Compare deserialized data with reference data.
            TS_ASSERT(fabs(vc.getSpeed() - vcRef.getSpeed()) < 1e-5);
            TS_ASSERT(fabs(vc.getAcceleration() - vcRef.getAcceleration()) < 1e-5);
            TS_ASSERT(fabs(vc.getSteeringWheelAngle() - vcRef.getSteeringWheelAngle()) < 1e-5);
            TS_ASSERT(vc.getBrakeLights() == vcRef.getBrakeLights());
            TS_ASSERT(vc.getLeftFlashingLights() == vcRef.getLeftFlashingLights());
            TS_ASSERT(vc.getRightFlashingLights() == vcRef.getRightFlashingLights());

            // Serialize reference data.
            LCMSerializerVisitor lcmSerializerVisitor;
            lcmSerializerVisitor.setChannelName("41");
            vcRef.accept(lcmSerializerVisitor);

            // Compare hash codes.
            TS_ASSERT(lcmDeserializerVisitor.getDecodedHash() == lcmSerializerVisitor.getHash());
            TS_ASSERT(lcmDeserializerVisitor.getCalculatedHash() == lcmSerializerVisitor.getHash());

            // Get serialized bytes.
            stringstream out;
            lcmSerializerVisitor.getSerializedData(out);

            // Read back from serialized bytes re-using the deserializer.
            lcmDeserializerVisitor.deserializeDataFrom(out);

            // Fill new data structure.
            LCMVehicleControl vc3;
            vc3.accept(lcmDeserializerVisitor);

            TS_ASSERT(fabs(vc3.getSpeed() - vcRef.getSpeed()) < 1e-5);
            TS_ASSERT(fabs(vc3.getAcceleration() - vcRef.getAcceleration()) < 1e-5);
            TS_ASSERT(fabs(vc3.getSteeringWheelAngle() - vcRef.getSteeringWheelAngle()) < 1e-5);
            TS_ASSERT(vc3.getBrakeLights() == vcRef.getBrakeLights());
            TS_ASSERT(vc3.getLeftFlashingLights() == vcRef.getLeftFlashingLights());
            TS_ASSERT(vc3.getRightFlashingLights() == vcRef.getRightFlashingLights());
        }

};

#endif /*CORE_LCMTESTSUITE_H_*/
