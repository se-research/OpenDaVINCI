/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"

#include "test8/generated/testpackage/Test8A.h"

namespace testpackage {
		using namespace std;
		using namespace odcore::base;
	
	
		Test8A::Test8A() :
		    SerializableData(), Visitable()
			, m_attribute1(0)
		{
		}
	
		Test8A::Test8A(
			const uint32_t &val0
		) :
		    SerializableData(), Visitable()
			, m_attribute1(val0)
		{
		}
	
		Test8A::Test8A(const Test8A &obj) :
		    SerializableData(), Visitable()
			, m_attribute1(obj.m_attribute1)
		{
		}
		
		Test8A::~Test8A() {
		}
	
		Test8A& Test8A::operator=(const Test8A &obj) {
			m_attribute1 = obj.m_attribute1;
			return (*this);
		}
	
		int32_t Test8A::ID() {
			return 8;
		}
	
		const string Test8A::ShortName() {
			return "Test8A";
		}
	
		const string Test8A::LongName() {
			return "testpackage.Test8A";
		}
	
		int32_t Test8A::getID() const {
			return Test8A::ID();
		}
	
		const string Test8A::getShortName() const {
			return Test8A::ShortName();
		}
	
		const string Test8A::getLongName() const {
			return Test8A::LongName();
		}
	
		uint32_t Test8A::getAttribute1() const {
			return m_attribute1;
		}
		
		void Test8A::setAttribute1(const uint32_t &val) {
			m_attribute1 = val;
		}
	
		void Test8A::accept(odcore::base::Visitor &v) {
			v.beginVisit();
			v.visit(1, "Test8A.attribute1", "attribute1", m_attribute1);
			v.endVisit();
		}
	
		const string Test8A::toString() const {
			stringstream s;
	
			s << "Attribute1: " << getAttribute1() << " ";
	
			return s.str();
		}
	
		ostream& Test8A::operator<<(ostream &out) const {
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			std::shared_ptr<Serializer> s = sf.getSerializer(out);
	
			s->write(1,
					m_attribute1);
			return out;
		}
	
		istream& Test8A::operator>>(istream &in) {
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			std::shared_ptr<Deserializer> d = sf.getDeserializer(in);
	
			d->read(1,
					m_attribute1);
			return in;
		}
} // testpackage
