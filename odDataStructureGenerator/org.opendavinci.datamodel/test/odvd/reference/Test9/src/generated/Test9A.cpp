/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include <opendavinci/odcore/serialization/Deserializer.h>
#include <opendavinci/odcore/serialization/SerializationFactory.h>
#include <opendavinci/odcore/serialization/Serializer.h>

#include "test9/generated/Test9A.h"

	using namespace std;
	using namespace odcore::base;
	using namespace odcore::serialization;


	Test9A::Test9A() :
	    SerializableData(), Visitable()
		, m_attribute1(0)
	{
	}

	Test9A::Test9A(
		const uint32_t &val0
	) :
	    SerializableData(), Visitable()
		, m_attribute1(val0)
	{
	}

	Test9A::Test9A(const Test9A &obj) :
	    SerializableData(), Visitable()
		, m_attribute1(obj.m_attribute1)
	{
	}
	
	Test9A::~Test9A() {
	}

	Test9A& Test9A::operator=(const Test9A &obj) {
		m_attribute1 = obj.m_attribute1;
		return (*this);
	}

	int32_t Test9A::ID() {
		return 9;
	}

	const string Test9A::ShortName() {
		return "Test9A";
	}

	const string Test9A::LongName() {
		return "Test9A";
	}

	int32_t Test9A::getID() const {
		return Test9A::ID();
	}

	const string Test9A::getShortName() const {
		return Test9A::ShortName();
	}

	const string Test9A::getLongName() const {
		return Test9A::LongName();
	}

	uint32_t Test9A::getAttribute1() const {
		return m_attribute1;
	}
	
	void Test9A::setAttribute1(const uint32_t &val) {
		m_attribute1 = val;
	}

	void Test9A::accept(odcore::base::Visitor &v) {
		v.beginVisit(ID(), ShortName(), LongName());
		v.visit(1, "Test9A.attribute1", "attribute1", m_attribute1);
		v.endVisit();
	}

	const string Test9A::toString() const {
		stringstream s;

		s << "Attribute1: " << getAttribute1() << " ";

		return s.str();
	}

	ostream& Test9A::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		s->write(1,
				m_attribute1);
		return out;
	}

	istream& Test9A::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		d->read(1,
				m_attribute1);
		return in;
	}
