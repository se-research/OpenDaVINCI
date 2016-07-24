/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>
#include <cstring>
#include "opendavinci/odcore/opendavinci.h"

#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"


#include "test18/generated/Test18.h"

	using namespace std;
	using namespace odcore::base;


	Test18::Test18() :
	    SerializableData(), Visitable()
		, m_myArray1()
		, m_myArray2()
		, m_myAtt1(0)
		, m_myAtt2(0)
		, m_myAtt3(0)
	{
		m_myArray1 = new uint32_t[getSize_MyArray1()];
		for(uint32_t i = 0; i < getSize_MyArray1(); i++) {
			m_myArray1[i] = 0;
		}
		m_myArray2 = new float[getSize_MyArray2()];
		for(uint32_t i = 0; i < getSize_MyArray2(); i++) {
			m_myArray2[i] = 0;
		}
	}

	Test18::Test18(
		const uint32_t *val0, 
		const float *val1, 
		const uint32_t &val2, 
		const uint32_t &val3, 
		const uint32_t &val4
	) :
	    SerializableData(), Visitable()
		, m_myArray1() // The content from obj will be copied in the copy-constructor's body.
		, m_myArray2() // The content from obj will be copied in the copy-constructor's body.
		, m_myAtt1(val2)
		, m_myAtt2(val3)
		, m_myAtt3(val4)
	{
		m_myArray1 = new uint32_t[getSize_MyArray1()];
		::memcpy(m_myArray1, val0, getSize_MyArray1() * sizeof(*m_myArray1));
		m_myArray2 = new float[getSize_MyArray2()];
		::memcpy(m_myArray2, val1, getSize_MyArray2() * sizeof(*m_myArray2));
	}

	Test18::Test18(const Test18 &obj) :
	    SerializableData(), Visitable()
		, m_myArray1() // The content from obj will be copied in the copy-constructor's body.
		, m_myArray2() // The content from obj will be copied in the copy-constructor's body.
		, m_myAtt1(obj.m_myAtt1)
		, m_myAtt2(obj.m_myAtt2)
		, m_myAtt3(obj.m_myAtt3)
	{
		m_myArray1 = new uint32_t[getSize_MyArray1()];
		::memcpy(m_myArray1, obj.m_myArray1, obj.getSize_MyArray1() * sizeof(*m_myArray1));
		m_myArray2 = new float[getSize_MyArray2()];
		::memcpy(m_myArray2, obj.m_myArray2, obj.getSize_MyArray2() * sizeof(*m_myArray2));
	}
	
	Test18::~Test18() {
		OPENDAVINCI_CORE_DELETE_ARRAY(m_myArray1);
		OPENDAVINCI_CORE_DELETE_ARRAY(m_myArray2);
	}

	Test18& Test18::operator=(const Test18 &obj) {
		::memcpy(m_myArray1, obj.m_myArray1, obj.getSize_MyArray1() * sizeof(*m_myArray1));
		::memcpy(m_myArray2, obj.m_myArray2, obj.getSize_MyArray2() * sizeof(*m_myArray2));
		m_myAtt1 = obj.m_myAtt1;
		m_myAtt2 = obj.m_myAtt2;
		m_myAtt3 = obj.m_myAtt3;
		return (*this);
	}

	int32_t Test18::ID() {
		return 18;
	}

	const string Test18::ShortName() {
		return "Test18";
	}

	const string Test18::LongName() {
		return "Test18";
	}

	int32_t Test18::getID() const {
		return Test18::ID();
	}

	const string Test18::getShortName() const {
		return Test18::ShortName();
	}

	const string Test18::getLongName() const {
		return Test18::LongName();
	}

	uint32_t* Test18::getMyArray1() {
		return m_myArray1;
	}
	
	uint32_t Test18::getSize_MyArray1() const {
		return 2;
	}
	float* Test18::getMyArray2() {
		return m_myArray2;
	}
	
	uint32_t Test18::getSize_MyArray2() const {
		return 3;
	}
	uint32_t Test18::getMyAtt1() const {
		return m_myAtt1;
	}
	
	void Test18::setMyAtt1(const uint32_t &val) {
		m_myAtt1 = val;
	}
	uint32_t Test18::getMyAtt2() const {
		return m_myAtt2;
	}
	
	void Test18::setMyAtt2(const uint32_t &val) {
		m_myAtt2 = val;
	}
	uint32_t Test18::getMyAtt3() const {
		return m_myAtt3;
	}
	
	void Test18::setMyAtt3(const uint32_t &val) {
		m_myAtt3 = val;
	}

	void Test18::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.visit(CRC32 < CharList<'m', CharList<'y', CharList<'A', CharList<'t', CharList<'t', CharList<'1', NullType> > > > > >  >::RESULT, 3, "Test18.myAtt1", "myAtt1", m_myAtt1);
		v.visit(CRC32 < CharList<'m', CharList<'y', CharList<'A', CharList<'t', CharList<'t', CharList<'2', NullType> > > > > >  >::RESULT, 4, "Test18.myAtt2", "myAtt2", m_myAtt2);
		v.visit(CRC32 < CharList<'m', CharList<'y', CharList<'A', CharList<'t', CharList<'t', CharList<'3', NullType> > > > > >  >::RESULT, 5, "Test18.myAtt3", "myAtt3", m_myAtt3);
		v.endVisit();
	}

	const string Test18::toString() const {
		stringstream s;


		s << "myArray1: (";
		for(uint32_t i = 0; i < getSize_MyArray1(); i++) {
			s << (m_myArray1[i]) << (((i+1) < getSize_MyArray1()) ? ", " : "");
		}
		s << ")" << " ";
		s << "myArray2: (";
		for(uint32_t i = 0; i < getSize_MyArray2(); i++) {
			s << (m_myArray2[i]) << (((i+1) < getSize_MyArray2()) ? ", " : "");
		}
		s << ")" << " ";
		s << "MyAtt1: " << getMyAtt1() << " ";
		s << "MyAtt2: " << getMyAtt2() << " ";
		s << "MyAtt3: " << getMyAtt3() << " ";

		return s.str();
	}

	ostream& Test18::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		s->write(1,
				m_myArray1, getSize_MyArray1() * (sizeof(uint32_t)/sizeof(char)));
		s->write(2,
				m_myArray2, getSize_MyArray2() * (sizeof(float)/sizeof(char)));
		s->write(3,
				m_myAtt1);
		s->write(4,
				m_myAtt2);
		s->write(5,
				m_myAtt3);
		return out;
	}

	istream& Test18::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		d->read(1,
		       m_myArray1, getSize_MyArray1() * (sizeof(uint32_t)/sizeof(char)));
		d->read(2,
		       m_myArray2, getSize_MyArray2() * (sizeof(float)/sizeof(char)));
		d->read(3,
				m_myAtt1);
		d->read(4,
				m_myAtt2);
		d->read(5,
				m_myAtt3);
		return in;
	}
