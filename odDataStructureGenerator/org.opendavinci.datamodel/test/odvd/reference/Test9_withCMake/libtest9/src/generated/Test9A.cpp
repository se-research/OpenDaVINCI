/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"


#include "test9/generated/Test9A.h"

	using namespace std;
	using namespace core::base;


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

	uint32_t Test9A::getAttribute1() const {
		return m_attribute1;
	}
	
	void Test9A::setAttribute1(const uint32_t &val) {
		m_attribute1 = val;
	}

	void Test9A::accept(core::base::Visitor &v) {
		v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT, 0, "Test9A.attribute1", "attribute1", m_attribute1);
	}

	const string Test9A::toString() const {
		stringstream s;


		s << "Attribute1: " << getAttribute1() << " ";

		return s.str();
	}

	ostream& Test9A::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Serializer> s = sf.getSerializer(out);

		s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
				m_attribute1);
		return out;
	}

	istream& Test9A::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

		d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
				m_attribute1);
		return in;
	}
