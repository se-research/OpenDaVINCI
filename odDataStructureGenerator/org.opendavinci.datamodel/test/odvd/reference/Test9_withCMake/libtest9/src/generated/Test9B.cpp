/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"


#include "test9/generated/Test9B.h"

	using namespace std;
	using namespace odcore::base;


	Test9B::Test9B() :
	    SerializableData(), Visitable()
		, m_attribute1(true) // TODO: Validation if the default value is of the desired type.
	{
	}

	Test9B::Test9B(
		const bool &val0
	) :
	    SerializableData(), Visitable()
		, m_attribute1(val0)
	{
	}

	Test9B::Test9B(const Test9B &obj) :
	    SerializableData(), Visitable()
		, m_attribute1(obj.m_attribute1)
	{
	}
	
	Test9B::~Test9B() {
	}

	Test9B& Test9B::operator=(const Test9B &obj) {
		m_attribute1 = obj.m_attribute1;
		return (*this);
	}

	int32_t Test9B::ID() {
		return 10;
	}

	const string Test9B::ShortName() {
		return "Test9B";
	}

	const string Test9B::LongName() {
		return "Test9B";
	}

	int32_t Test9B::getID() const {
		return Test9B::ID();
	}

	const string Test9B::getShortName() const {
		return Test9B::ShortName();
	}

	const string Test9B::getLongName() const {
		return Test9B::LongName();
	}

	bool Test9B::getAttribute1() const {
		return m_attribute1;
	}
	
	void Test9B::setAttribute1(const bool &val) {
		m_attribute1 = val;
	}

	void Test9B::accept(odcore::base::Visitor &v) {
		v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT, 0, "Test9B.attribute1", "attribute1", m_attribute1);
	}

	const string Test9B::toString() const {
		stringstream s;


		s << "Attribute1: " << getAttribute1() << " ";

		return s.str();
	}

	ostream& Test9B::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
				m_attribute1);
		return out;
	}

	istream& Test9B::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
				m_attribute1);
		return in;
	}
