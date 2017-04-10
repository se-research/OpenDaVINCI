/**
 * libodcantools - Library to wrap a CAN interface.
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

#ifndef CANTOOLSTESTSUITE_H_
#define CANTOOLSTESTSUITE_H_

#include <string>

#include "cxxtest/TestSuite.h"

#include <opendavinci/odcore/data/TimeStamp.h>
#include <opendavinci/odcore/base/Thread.h>
#include "automotivedata/generated/automotive/GenericCANMessage.h"

#include <opendavinci/odcore/serialization/Deserializer.h>
#include <opendavinci/odcore/reflection/Message.h>
#include <opendavinci/odcore/reflection/MessageToVisitableVisitor.h>
#include <opendavinci/odcore/reflection/MessageFromVisitableVisitor.h>
#include <opendavinci/odcore/serialization/SerializationFactory.h>
#include <opendavinci/odcore/serialization/Serializer.h>
#include <opendavinci/odcore/data/Container.h>

// Include local header files.
#include "../include/CANDevice.h"
#include "../include/CANMessage.h"
#include "../include/GenericCANMessageListener.h"

using namespace std;
using namespace odcore::serialization;
using namespace odcore::base;
using namespace odcore::data;
using namespace automotive;
using namespace automotive::odcantools;

		class OPENDAVINCI_API WheelSpeedHL : public odcore::data::SerializableData, public odcore::base::Visitable {
			public:
				WheelSpeedHL() :
			        SerializableData(), Visitable()
				    , m_frontLeft(0)
				    , m_frontRight(0)
				    , m_rearLeft(0)
				    , m_rearRight(0)
			    {}
			    WheelSpeedHL(const WheelSpeedHL &obj) :
			        SerializableData(), Visitable()
				    , m_frontLeft(obj.m_frontLeft)
				    , m_frontRight(obj.m_frontRight)
				    , m_rearLeft(obj.m_rearLeft)
				    , m_rearRight(obj.m_rearRight)
			    {}
			    ~WheelSpeedHL() {}
		
			    WheelSpeedHL& operator=(const WheelSpeedHL &obj) {
				    m_frontLeft = obj.m_frontLeft;
				    m_frontRight = obj.m_frontRight;
				    m_rearLeft = obj.m_rearLeft;
				    m_rearRight = obj.m_rearRight;
				    return (*this);
			    }
			    int32_t getID() const {
			        return WheelSpeedHL::ID();
		        }
		        const string getShortName() const {
		            return WheelSpeedHL::ShortName();
		        }
		        const string getLongName() const {
		            return WheelSpeedHL::LongName();
		        }
			    static int32_t ID() {
				    return 75;
			    }
			    static const string ShortName() {
				    return "WheelSpeedHL";
			    }
			    static const string LongName() {
				    return "automotive.vehicle.WheelSpeedHL";
			    }
				virtual void accept(odcore::base::Visitor &v) {
				    v.beginVisit(ID(), ShortName(), LongName());
				    v.visit(1, "WheelSpeed.frontLeft", "frontLeft", m_frontLeft);
				    v.visit(2, "WheelSpeed.frontRight", "frontRight", m_frontRight);
				    v.visit(3, "WheelSpeed.rearLeft", "rearLeft", m_rearLeft);
				    v.visit(4, "WheelSpeed.rearRight", "rearRight", m_rearRight);
				    v.endVisit();
			    }
			    ostream& operator<<(ostream &out) const {
				    SerializationFactory& sf = SerializationFactory::getInstance();
				    std::shared_ptr<Serializer> s = sf.getSerializer(out);
				    s->write(1,m_frontLeft);
				    s->write(2,m_frontRight);
				    s->write(3,m_rearLeft);
				    s->write(4,m_rearRight);
				    return out;
			    }
			    istream& operator>>(istream &in) {
				    SerializationFactory& sf = SerializationFactory::getInstance();
				    std::shared_ptr<Deserializer> d = sf.getDeserializer(in);
				    d->read(1,m_frontLeft);
				    d->read(2,m_frontRight);
				    d->read(3,m_rearLeft);
				    d->read(4,m_rearRight);
				    return in;
			    }
				virtual const string toString() const {
				    stringstream s;
				    s << "FrontLeft: " << m_frontLeft << " ";
				    s << "FrontRight: " << m_frontRight << " ";
				    s << "RearLeft: " << m_rearLeft << " ";
				    s << "RearRight: " << m_rearRight << " ";
				    return s.str();
			    }
			private:
				float m_frontLeft;
				float m_frontRight;
				float m_rearLeft;
				float m_rearRight;
		};

class WheelSpeed : public odcore::data::SerializableData, public odcore::base::Visitable {
    public:
        WheelSpeed() :
			odcore::data::SerializableData(),
			odcore::base::Visitable(),
			m_wheelspeedFrontleft(0.0),
			m_wheelspeedFrontright(0.0),
			m_wheelspeedRearleft(0.0),
			m_wheelspeedRearright(0.0),
			m_payloads(),
			m_neededCanMessages(),
			m_index(0),
			m_automotive_vehicle_WheelSpeed()
		{
			m_neededCanMessages.push_back(0x123);
		}
		WheelSpeed(double parameter0, double parameter1, double parameter2, double parameter3) :
			odcore::data::SerializableData(),
			odcore::base::Visitable(),
			m_wheelspeedFrontleft(parameter0),
			m_wheelspeedFrontright(parameter1),
			m_wheelspeedRearleft(parameter2),
			m_wheelspeedRearright(parameter3),
			m_payloads(),
			m_neededCanMessages(),
			m_index(0),
			m_automotive_vehicle_WheelSpeed()
		{
			m_neededCanMessages.push_back(0x123);
		}
        virtual ~WheelSpeed() {}
    	double getWheelspeedFrontleft() const {
			return m_wheelspeedFrontleft;
		}
    	double getWheelspeedFrontright() const {
			return m_wheelspeedFrontright;
		}
    	double getWheelspeedRearleft() const {
			return m_wheelspeedRearleft;
		}
    	double getWheelspeedRearright() const {
			return m_wheelspeedRearright;
		}
        virtual const string toString() const {
			stringstream result;
			result << "Class : WheelSpeed"<<endl
					<<" wheelspeed.frontleft : "<< +m_wheelspeedFrontleft << endl
					<<" wheelspeed.frontright : "<< +m_wheelspeedFrontright << endl
					<<" wheelspeed.rearleft : "<< +m_wheelspeedRearleft << endl
					<<" wheelspeed.rearright : "<< +m_wheelspeedRearright << endl;
			return result.str();
		}
		virtual ostream& operator<<(ostream &out) const {
			odcore::serialization::SerializationFactory& sf = odcore::serialization::SerializationFactory::getInstance();
			std::shared_ptr<odcore::serialization::Serializer> s = sf.getSerializer(out);
	
			s->write(static_cast<uint32_t>(1), m_wheelspeedFrontleft);
			s->write(static_cast<uint32_t>(2), m_wheelspeedFrontright);
			s->write(static_cast<uint32_t>(3), m_wheelspeedRearleft);
			s->write(static_cast<uint32_t>(4), m_wheelspeedRearright);
			return out;
		}
		virtual istream& operator>>(istream &in) {
			odcore::serialization::SerializationFactory& sf = odcore::serialization::SerializationFactory::getInstance();
			std::shared_ptr<odcore::serialization::Deserializer> s = sf.getDeserializer(in);
			
			uint32_t id;
			id=1;
			s->read(static_cast<uint32_t>(id), m_wheelspeedFrontleft);
			id=2;
			s->read(static_cast<uint32_t>(id), m_wheelspeedFrontright);
			id=3;
			s->read(static_cast<uint32_t>(id), m_wheelspeedRearleft);
			id=4;
			s->read(static_cast<uint32_t>(id), m_wheelspeedRearright);
			return in;
		}
		static const string ShortName() {
			return "WheelSpeed";
		}
		static const string LongName() {
			return "WheelSpeed";
		}
        static int32_t ID() {
			return 0;
		}
        int32_t getID() const {
            return WheelSpeed::ID();
        }
        const string getShortName() const {
            return WheelSpeed::ShortName();
        }
        const string getLongName() const {
            return WheelSpeed::LongName();
        }
		virtual void accept(odcore::base::Visitor &v) {
		    v.beginVisit(ID(), ShortName(), LongName());
			v.visit(static_cast<uint32_t>(1), "wheelspeed.frontleft", "frontleft", m_wheelspeedFrontleft);
			v.visit(static_cast<uint32_t>(2), "wheelspeed.frontright", "frontright", m_wheelspeedFrontright);
			v.visit(static_cast<uint32_t>(3), "wheelspeed.rearleft", "rearleft", m_wheelspeedRearleft);
			v.visit(static_cast<uint32_t>(4), "wheelspeed.rearright", "rearright", m_wheelspeedRearright);
		    v.endVisit();
		}
        odcore::data::Container decode(const ::automotive::GenericCANMessage &gcm){
					odcore::data::Container c;
			
				bool reset=false;
				switch(gcm.getIdentifier())
				{
			
			    	case 0x123 : 
			
			// since the order matters:
			if(m_neededCanMessages.at(m_index) == 0x123) // if we got the expected message
			{
				// Store the payload in a map for future use replacing the current content
			m_payloads[0x123] = gcm.getData();
				// modularly increase the internal index
				(m_index==m_neededCanMessages.size()-1) ? m_index=0 : ++m_index;
			}
			else // otherwise reset
				reset=true;
			    	break;
			
				default : return c; // valid id not found
			}
			
			
			if(reset)
			{		
				// reset the payloads and lengths map
				while(! m_payloads.empty())
					m_payloads.erase(m_payloads.begin());
				// reset the internal index
				m_index=0;
			}
				// if we don't have all the needed CAN messages, return 
				if(m_payloads.size()!=m_neededCanMessages.size())
					return c;
			
				// Create a generic message.
				odcore::reflection::Message message;
			
			        ::automotive::odcantools::CANMessage CM_0x123(0x123,8,m_payloads[0x123]);
			
			
			
				// addressing signal wheelspeed.frontleft : 1
				{
					// Add the CAN signal to the CAN message
					::automotive::odcantools::CANSignal wheelspeed_frontleft(0,16,::automotive::odcantools::Signedness::UNSIGNED,::automotive::odcantools::Endianness::LITTLE,0.01,0,0,200);
			                CM_0x123.addSignal(1,wheelspeed_frontleft);
			                m_wheelspeedFrontleft=CM_0x123.decodeSignal(1);
			
					// Create a field for a generic message.
					odcore::reflection::Field<double> *f = new odcore::reflection::Field<double>(m_wheelspeedFrontleft);
					f->setFieldIdentifier(1); // The identifiers specified here must match with the ones defined in the .odvd file!
					f->setLongFieldName("wheelspeed.frontleft");
					f->setShortFieldName("frontleft");
					f->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
					f->setSize(sizeof(m_wheelspeedFrontleft));
			
					// Add created field to generic message.
					message.addField(std::shared_ptr<odcore::data::reflection::AbstractField>(f));
				}
			
			
				// addressing signal wheelspeed.frontright : 2
				{
					// Add the CAN signal to the CAN message
					::automotive::odcantools::CANSignal wheelspeed_frontright(16,16,::automotive::odcantools::Signedness::UNSIGNED,::automotive::odcantools::Endianness::LITTLE,0.01,0,0,200);
			                CM_0x123.addSignal(2,wheelspeed_frontright);
			                m_wheelspeedFrontright=CM_0x123.decodeSignal(2);
			
					// Create a field for a generic message.
					odcore::reflection::Field<double> *f = new odcore::reflection::Field<double>(m_wheelspeedFrontright);
					f->setFieldIdentifier(2); // The identifiers specified here must match with the ones defined in the .odvd file!
					f->setLongFieldName("wheelspeed.frontright");
					f->setShortFieldName("frontright");
					f->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
					f->setSize(sizeof(m_wheelspeedFrontright));
			
					// Add created field to generic message.
					message.addField(std::shared_ptr<odcore::data::reflection::AbstractField>(f));
				}
			
			
				// addressing signal wheelspeed.rearleft : 3
				{
					// Add the CAN signal to the CAN message
					::automotive::odcantools::CANSignal wheelspeed_rearleft(32,16,::automotive::odcantools::Signedness::UNSIGNED,::automotive::odcantools::Endianness::LITTLE,0.01,0,0,200);
			                CM_0x123.addSignal(3,wheelspeed_rearleft);
			                m_wheelspeedRearleft=CM_0x123.decodeSignal(3);
			
					// Create a field for a generic message.
					odcore::reflection::Field<double> *f = new odcore::reflection::Field<double>(m_wheelspeedRearleft);
					f->setFieldIdentifier(3); // The identifiers specified here must match with the ones defined in the .odvd file!
					f->setLongFieldName("wheelspeed.rearleft");
					f->setShortFieldName("rearleft");
					f->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
					f->setSize(sizeof(m_wheelspeedRearleft));
			
					// Add created field to generic message.
					message.addField(std::shared_ptr<odcore::data::reflection::AbstractField>(f));
				}
			
			
				// addressing signal wheelspeed.rearright : 4
				{
					// Add the CAN signal to the CAN message
					::automotive::odcantools::CANSignal wheelspeed_rearright(48,16,::automotive::odcantools::Signedness::UNSIGNED,::automotive::odcantools::Endianness::LITTLE,0.01,0,0,200);
			                CM_0x123.addSignal(4,wheelspeed_rearright);
			                m_wheelspeedRearright=CM_0x123.decodeSignal(4);
			
					// Create a field for a generic message.
					odcore::reflection::Field<double> *f = new odcore::reflection::Field<double>(m_wheelspeedRearright);
					f->setFieldIdentifier(4); // The identifiers specified here must match with the ones defined in the .odvd file!
					f->setLongFieldName("wheelspeed.rearright");
					f->setShortFieldName("rearright");
					f->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
					f->setSize(sizeof(m_wheelspeedRearright));
			
					// Add created field to generic message.
					message.addField(std::shared_ptr<odcore::data::reflection::AbstractField>(f));
				}
				// Depending on the CAN message specification, we are either ready here
				// (i.e. mapping one CAN message to one high-level C++ message), or we have
				// to wait for more low-level CAN messages to complete this high-level C++ message.
				// Thus, our state machine would have to store this (incomplete) "message"
				// variable internally to continue decoding later.
				{
					// As we are ready here, we create a visitor to traverse the 
					// unnamed message and create a named message (i.e. an instance
					// of a high-level C++ message) to be distributed as a Container.
					odcore::reflection::MessageToVisitableVisitor mtvv(message);
					// Letting the high-level message accept the visitor to set the values.
			        	m_automotive_vehicle_WheelSpeed.accept(mtvv);
					// Create the resulting container carrying a valid payload.
					c = odcore::data::Container(m_automotive_vehicle_WheelSpeed);
				}
			
					return c;
				}
        ::automotive::GenericCANMessage encode(odcore::data::Container &c)
				{
			
				::automotive::odcantools::CANMessage CM_0x123(0x123,8,0x00);
			
				if(c.getDataType() != WheelSpeedHL::ID())
				{
					// something went wrong
					::automotive::odcantools::CANMessage error(0x00,0,0x00);
				    return error.getGenericCANMessage();
				}
			
				bool found, extracted, abort=false;
				WheelSpeedHL tempWheelSpeed=c.getData<WheelSpeedHL>();
				odcore::reflection::MessageFromVisitableVisitor mfvv;
				tempWheelSpeed.accept(mfvv);
				odcore::reflection::Message msg=mfvv.getMessage();
			
				
				///////// manipulating signal wheelspeed.frontleft : 1
				found=extracted=false;
				double Wheelspeed_frontleft = msg.getValueFromScalarField<double>(1, found, extracted);
				
				if(found && extracted) {
				    ::automotive::odcantools::CANSignal signal_wheelspeed_frontleft(0,16,::automotive::odcantools::Signedness::UNSIGNED,::automotive::odcantools::Endianness::LITTLE,0.01,0,0,200);
			                CM_0x123.addSignal(1,signal_wheelspeed_frontleft);
			                CM_0x123.encodeSignal(1,Wheelspeed_frontleft);
				}
				else {
					abort=true; // set to true and never reset to false to keep track of failures
				}
				
				///////// manipulating signal wheelspeed.frontright : 2
				found=extracted=false;
				double Wheelspeed_frontright = msg.getValueFromScalarField<double>(2, found, extracted);
				
				if(found && extracted) {
				    ::automotive::odcantools::CANSignal signal_wheelspeed_frontright(16,16,::automotive::odcantools::Signedness::UNSIGNED,::automotive::odcantools::Endianness::LITTLE,0.01,0,0,200);
			                CM_0x123.addSignal(2,signal_wheelspeed_frontright);
			                CM_0x123.encodeSignal(2,Wheelspeed_frontright);
				}
				else {
					abort=true; // set to true and never reset to false to keep track of failures
				}
				
				///////// manipulating signal wheelspeed.rearleft : 3
				found=extracted=false;
				double Wheelspeed_rearleft = msg.getValueFromScalarField<double>(3, found, extracted);
				
				if(found && extracted) {
				    ::automotive::odcantools::CANSignal signal_wheelspeed_rearleft(32,16,::automotive::odcantools::Signedness::UNSIGNED,::automotive::odcantools::Endianness::LITTLE,0.01,0,0,200);
			                CM_0x123.addSignal(3,signal_wheelspeed_rearleft);
			                CM_0x123.encodeSignal(3,Wheelspeed_rearleft);
				}
				else {
					abort=true; // set to true and never reset to false to keep track of failures
				}
				
				///////// manipulating signal wheelspeed.rearright : 4
				found=extracted=false;
				double Wheelspeed_rearright = msg.getValueFromScalarField<double>(4, found, extracted);
				
				if(found && extracted) {
				    ::automotive::odcantools::CANSignal signal_wheelspeed_rearright(48,16,::automotive::odcantools::Signedness::UNSIGNED,::automotive::odcantools::Endianness::LITTLE,0.01,0,0,200);
			                CM_0x123.addSignal(4,signal_wheelspeed_rearright);
			                CM_0x123.encodeSignal(4,Wheelspeed_rearright);
				}
				else {
					abort=true; // set to true and never reset to false to keep track of failures
				}
				
				if(abort) { // if there was at least one failure
				    // discard and return
				    ::automotive::odcantools::CANMessage error(0x00,0,0x00);
				    return error.getGenericCANMessage();
				}
				
				// return the CAN message, or the first CAN message if the mapping is defined over multiple CAN messages
				return CM_0x123.getGenericCANMessage();
				}
	
    private:
    	double m_wheelspeedFrontleft;
    	double m_wheelspeedFrontright;
    	double m_wheelspeedRearleft;
    	double m_wheelspeedRearright;
    	
    	std::map<uint64_t,uint64_t> m_payloads;
    	std::vector<uint64_t> m_neededCanMessages;
    	uint64_t m_index;
    	
        WheelSpeedHL m_automotive_vehicle_WheelSpeed;
    	
}; // end of class "WheelSpeed"

/**
 * The actual testsuite starts here.
 */
class CANToolsTest : public CxxTest::TestSuite, public GenericCANMessageListener {
    public:
        virtual void nextGenericCANMessage(const GenericCANMessage &gcm) {
            cout << gcm.toString() << ", " << gcm.getDriverTimeStamp().getYYYYMMDD_HHMMSSms() << endl;
        }

        void testCase1() {
            TS_ASSERT(1 != 0);
        }
    public:
        void testSer_Deser() {
        	
        	
        	WheelSpeed automotive_vehicle_WheelSpeed_1(-6779.5226880684695, -4754.9318150574145, 3023.9560379370487, 6337.597133830897);
        	WheelSpeed automotive_vehicle_WheelSpeed_2;
        	
        	stringstream ss1,ss2;
        	ss1 << automotive_vehicle_WheelSpeed_1;
        	
            TS_ASSERT(ss1.str().compare(ss2.str())!=0);
            
            ss1 >> automotive_vehicle_WheelSpeed_2;
            ss2 << automotive_vehicle_WheelSpeed_2;
            
            TS_ASSERT(ss1.str().compare(ss2.str())==0);
        }

	void testDecode() {
		{
			// Mapping name automotive.vehicle.WheelSpeed
			// id 0x123
			// payload 0x3C2217220D220722 : length 8 bytes

				::automotive::GenericCANMessage gcm_1;
				gcm_1.setIdentifier(0x123);
				gcm_1.setLength(8);
				gcm_1.setData(0x3C2217220D220722);

			WheelSpeed test_0;
			
			test_0.decode(gcm_1);
			
			TS_ASSERT_DELTA(test_0.getWheelspeedFrontleft() , 87.64, 1e-4);
			TS_ASSERT_DELTA(test_0.getWheelspeedFrontright() , 87.27, 1e-4);
			TS_ASSERT_DELTA(test_0.getWheelspeedRearleft() , 87.17, 1e-4);
			TS_ASSERT_DELTA(test_0.getWheelspeedRearright() , 87.11, 1e-4);
		}
    }

    void testEncode() {
{
 // Mapping name automotive.vehicle.WheelSpeed


			// id 0x123
			// payload 0x3C2217220D220722 : length 8

			odcore::reflection::Message message;


    			odcore::reflection::Field<double> *f_1 = new odcore::reflection::Field<double>(87.64);
    			f_1->setFieldIdentifier(1);
    			f_1->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
    			message.addField(std::shared_ptr<odcore::data::reflection::AbstractField>(f_1));
    			odcore::reflection::Field<double> *f_2 = new odcore::reflection::Field<double>(87.27);
    			f_2->setFieldIdentifier(2);
    			f_2->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
    			message.addField(std::shared_ptr<odcore::data::reflection::AbstractField>(f_2));
    			odcore::reflection::Field<double> *f_3 = new odcore::reflection::Field<double>(87.17);
    			f_3->setFieldIdentifier(3);
    			f_3->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
    			message.addField(std::shared_ptr<odcore::data::reflection::AbstractField>(f_3));
    			odcore::reflection::Field<double> *f_4 = new odcore::reflection::Field<double>(87.11);
    			f_4->setFieldIdentifier(4);
    			f_4->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
    			message.addField(std::shared_ptr<odcore::data::reflection::AbstractField>(f_4));

			odcore::reflection::MessageToVisitableVisitor mtvv(message);
			WheelSpeedHL HLClass;
			HLClass.accept(mtvv);
			odcore::data::Container c(HLClass);
			
			WheelSpeed test_0;
			::automotive::GenericCANMessage GCM;
			GCM=test_0.encode(c);

// Testing the ID of the resulting CAN message
TS_ASSERT_EQUALS(GCM.getIdentifier(),0x123);
			// Testing the length of the resulting CAN message
			TS_ASSERT_EQUALS(GCM.getLength(),8);
// Testing the payload of the resulting CAN message
			TS_ASSERT_EQUALS(GCM.getData(),static_cast<uint64_t>(0x3C2217220D220722));
}
    }
};

#endif /*CANTOOLSTESTSUITE_H_*/

