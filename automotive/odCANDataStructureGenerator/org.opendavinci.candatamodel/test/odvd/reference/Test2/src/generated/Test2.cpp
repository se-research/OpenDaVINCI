/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"


#include "generated/Test2.h"

	using namespace std;
	using namespace core::base;


	Test2::Test2() :
	    SerializableData(), Visitable()
		, m_attribute1(0)
	{
	}

	Test2::Test2(
		const uint32_t &val0
	) :
	    SerializableData(), Visitable()
		, m_attribute1(val0)
	{
	}

	Test2::Test2(const Test2 &obj) :
	    SerializableData(), Visitable()
		, m_attribute1(obj.m_attribute1)
	{
	}
	
	Test2::~Test2() {
	}

	Test2& Test2::operator=(const Test2 &obj) {
		m_attribute1 = obj.m_attribute1;
		return (*this);
	}

	int32_t Test2::ID() {
		return 2;
	}

	const string Test2::ShortName() {
		return "Test2";
	}

	const string Test2::LongName() {
		return "Test2";
	}

	uint32_t Test2::getAttribute1() const {
		return m_attribute1;
	}
	
	void Test2::setAttribute1(const uint32_t &val) {
		m_attribute1 = val;
	}

	void Test2::accept(core::base::Visitor &v) {
		v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT, 0, "Test2.attribute1", "attribute1", m_attribute1);
	}

	const string Test2::toString() const {
		stringstream s;


		s << "Attribute1: " << getAttribute1() << " ";

		return s.str();
	}

	ostream& Test2::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Serializer> s = sf.getSerializer(out);

		s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
				m_attribute1);
		return out;
	}

	istream& Test2::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

		d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
				m_attribute1);
		return in;
	}
