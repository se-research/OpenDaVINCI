/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"


#include "test20/generated/Test20a.h"

	using namespace std;
	using namespace core::base;


	Test20a::Test20a() :
	    SerializableData(), Visitable()
		, m_val1(0)
		, m_timeStamp()
	{
	}

	Test20a::Test20a(
		const uint32_t &val0, 
		const core::data::TimeStamp &val1
	) :
	    SerializableData(), Visitable()
		, m_val1(val0)
		, m_timeStamp(val1)
	{
	}

	Test20a::Test20a(const Test20a &obj) :
	    SerializableData(), Visitable()
		, m_val1(obj.m_val1)
		, m_timeStamp(obj.m_timeStamp)
	{
	}
	
	Test20a::~Test20a() {
	}

	Test20a& Test20a::operator=(const Test20a &obj) {
		m_val1 = obj.m_val1;
		m_timeStamp = obj.m_timeStamp;
		return (*this);
	}

	int32_t Test20a::ID() {
		return 20;
	}

	const string Test20a::ShortName() {
		return "Test20a";
	}

	const string Test20a::LongName() {
		return "Test20a";
	}

	uint32_t Test20a::getVal1() const {
		return m_val1;
	}
	
	void Test20a::setVal1(const uint32_t &val) {
		m_val1 = val;
	}
	core::data::TimeStamp Test20a::getTimeStamp() const {
		return m_timeStamp;
	}
	
	void Test20a::setTimeStamp(const core::data::TimeStamp &val) {
		m_timeStamp = val;
	}

	void Test20a::accept(core::base::Visitor &v) {
		v.visit(CRC32 < CharList<'v', CharList<'a', CharList<'l', CharList<'1', NullType> > > >  >::RESULT, 0, "Test20a.val1", "val1", m_val1);
		v.visit(CRC32 < CharList<'t', CharList<'i', CharList<'m', CharList<'e', CharList<'S', CharList<'t', CharList<'a', CharList<'m', CharList<'p', NullType> > > > > > > > >  >::RESULT, 0, "Test20a.timeStamp", "timeStamp", m_timeStamp);
	}

	const string Test20a::toString() const {
		stringstream s;


		s << "Val1: " << getVal1() << " ";
		s << "TimeStamp: " << getTimeStamp().toString() << " ";

		return s.str();
	}

	ostream& Test20a::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Serializer> s = sf.getSerializer(out);

		s->write(CRC32 < CharList<'v', CharList<'a', CharList<'l', CharList<'1', NullType> > > >  >::RESULT,
				m_val1);
		s->write(CRC32 < CharList<'t', CharList<'i', CharList<'m', CharList<'e', CharList<'S', CharList<'t', CharList<'a', CharList<'m', CharList<'p', NullType> > > > > > > > >  >::RESULT,
				m_timeStamp);
		return out;
	}

	istream& Test20a::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

		d->read(CRC32 < CharList<'v', CharList<'a', CharList<'l', CharList<'1', NullType> > > >  >::RESULT,
				m_val1);
		d->read(CRC32 < CharList<'t', CharList<'i', CharList<'m', CharList<'e', CharList<'S', CharList<'t', CharList<'a', CharList<'m', CharList<'p', NullType> > > > > > > > >  >::RESULT,
				m_timeStamp);
		return in;
	}
