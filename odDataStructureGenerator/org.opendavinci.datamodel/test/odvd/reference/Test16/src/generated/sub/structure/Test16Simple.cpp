/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"

#include "test16/generated/sub/structure/Test16Simple.h"

namespace sub {
	namespace structure {
			using namespace std;
			using namespace odcore::base;
		
		
			Test16Simple::Test16Simple() :
			    SerializableData(), Visitable()
				, m_myData(4.6) // TODO: Validation if the default value is of the desired type.
				, m_myValue(1) // TODO: Validation if the default value is of the desired type.
			{
			}
		
			Test16Simple::Test16Simple(
				const double &val0, 
				const int32_t &val1
			) :
			    SerializableData(), Visitable()
				, m_myData(val0)
				, m_myValue(val1)
			{
			}
		
			Test16Simple::Test16Simple(const Test16Simple &obj) :
			    SerializableData(), Visitable()
				, m_myData(obj.m_myData)
				, m_myValue(obj.m_myValue)
			{
			}
			
			Test16Simple::~Test16Simple() {
			}
		
			Test16Simple& Test16Simple::operator=(const Test16Simple &obj) {
				m_myData = obj.m_myData;
				m_myValue = obj.m_myValue;
				return (*this);
			}
		
			int32_t Test16Simple::ID() {
				return 16;
			}
		
			const string Test16Simple::ShortName() {
				return "Test16Simple";
			}
		
			const string Test16Simple::LongName() {
				return "sub.structure.Test16Simple";
			}
		
			int32_t Test16Simple::getID() const {
				return Test16Simple::ID();
			}
		
			const string Test16Simple::getShortName() const {
				return Test16Simple::ShortName();
			}
		
			const string Test16Simple::getLongName() const {
				return Test16Simple::LongName();
			}
		
			double Test16Simple::getMyData() const {
				return m_myData;
			}
			
			void Test16Simple::setMyData(const double &val) {
				m_myData = val;
			}
			int32_t Test16Simple::getMyValue() const {
				return m_myValue;
			}
			
			void Test16Simple::setMyValue(const int32_t &val) {
				m_myValue = val;
			}
		
			void Test16Simple::accept(odcore::base::Visitor &v) {
				v.beginVisit();
				v.visit(0, 1, "Test16Simple.myData", "myData", m_myData);
				v.visit(0, 2, "Test16Simple.myValue", "myValue", m_myValue);
				v.endVisit();
			}
		
			const string Test16Simple::toString() const {
				stringstream s;
		
				s << "MyData: " << getMyData() << " ";
				s << "MyValue: " << getMyValue() << " ";
		
				return s.str();
			}
		
			ostream& Test16Simple::operator<<(ostream &out) const {
				SerializationFactory& sf = SerializationFactory::getInstance();
		
				std::shared_ptr<Serializer> s = sf.getSerializer(out);
		
				s->write(1,
						m_myData);
				s->write(2,
						m_myValue);
				return out;
			}
		
			istream& Test16Simple::operator>>(istream &in) {
				SerializationFactory& sf = SerializationFactory::getInstance();
		
				std::shared_ptr<Deserializer> d = sf.getDeserializer(in);
		
				d->read(1,
						m_myData);
				d->read(2,
						m_myValue);
				return in;
			}
	} // structure
} // sub
