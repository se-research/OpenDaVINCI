/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"

#include "test9/generated/subpackage/Test9C.h"

namespace subpackage {
		using namespace std;
		using namespace odcore::base;
	
	
		Test9C::Test9C() :
		    SerializableData(), Visitable()
			, m_attribute1("")
		{
		}
	
		Test9C::Test9C(
			const std::string &val0
		) :
		    SerializableData(), Visitable()
			, m_attribute1(val0)
		{
		}
	
		Test9C::Test9C(const Test9C &obj) :
		    SerializableData(), Visitable()
			, m_attribute1(obj.m_attribute1)
		{
		}
		
		Test9C::~Test9C() {
		}
	
		Test9C& Test9C::operator=(const Test9C &obj) {
			m_attribute1 = obj.m_attribute1;
			return (*this);
		}
	
		int32_t Test9C::ID() {
			return 11;
		}
	
		const string Test9C::ShortName() {
			return "Test9C";
		}
	
		const string Test9C::LongName() {
			return "subpackage.Test9C";
		}
	
		int32_t Test9C::getID() const {
			return Test9C::ID();
		}
	
		const string Test9C::getShortName() const {
			return Test9C::ShortName();
		}
	
		const string Test9C::getLongName() const {
			return Test9C::LongName();
		}
	
		std::string Test9C::getAttribute1() const {
			return m_attribute1;
		}
		
		void Test9C::setAttribute1(const std::string &val) {
			m_attribute1 = val;
		}
	
		void Test9C::accept(odcore::base::Visitor &v) {
			v.beginVisit();
			v.visit(1, "Test9C.attribute1", "attribute1", m_attribute1);
			v.endVisit();
		}
	
		const string Test9C::toString() const {
			stringstream s;
	
			s << "Attribute1: " << getAttribute1() << " ";
	
			return s.str();
		}
	
		ostream& Test9C::operator<<(ostream &out) const {
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			std::shared_ptr<Serializer> s = sf.getSerializer(out);
	
			s->write(1,
					m_attribute1);
			return out;
		}
	
		istream& Test9C::operator>>(istream &in) {
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			std::shared_ptr<Deserializer> d = sf.getDeserializer(in);
	
			d->read(1,
					m_attribute1);
			return in;
		}
} // subpackage
