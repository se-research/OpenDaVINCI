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

#include "test12/generated/Test12Complex.h"

	using namespace std;
	using namespace odcore::base;


	Test12Complex::Test12Complex() :
	    SerializableData(), Visitable()
		, m_attribute1(true) // TODO: Validation if the default value is of the desired type.
		, m_attribute2('c') // TODO: Validation if the default value is of the desired type.
		, m_attribute3(-12) // TODO: Validation if the default value is of the desired type.
		, m_attribute4(+45) // TODO: Validation if the default value is of the desired type.
		, m_attribute5(-0.12) // TODO: Validation if the default value is of the desired type.
		, m_attribute6(+0.45678) // TODO: Validation if the default value is of the desired type.
		, m_attribute7("Hello World.") // TODO: Validation if the default value is of the desired type.
	{
	}

	Test12Complex::Test12Complex(
		const bool &val0, 
		const char &val1, 
		const int32_t &val2, 
		const uint32_t &val3, 
		const float &val4, 
		const double &val5, 
		const std::string &val6
	) :
	    SerializableData(), Visitable()
		, m_attribute1(val0)
		, m_attribute2(val1)
		, m_attribute3(val2)
		, m_attribute4(val3)
		, m_attribute5(val4)
		, m_attribute6(val5)
		, m_attribute7(val6)
	{
	}

	Test12Complex::Test12Complex(const Test12Complex &obj) :
	    SerializableData(), Visitable()
		, m_attribute1(obj.m_attribute1)
		, m_attribute2(obj.m_attribute2)
		, m_attribute3(obj.m_attribute3)
		, m_attribute4(obj.m_attribute4)
		, m_attribute5(obj.m_attribute5)
		, m_attribute6(obj.m_attribute6)
		, m_attribute7(obj.m_attribute7)
	{
	}
	
	Test12Complex::~Test12Complex() {
	}

	Test12Complex& Test12Complex::operator=(const Test12Complex &obj) {
		m_attribute1 = obj.m_attribute1;
		m_attribute2 = obj.m_attribute2;
		m_attribute3 = obj.m_attribute3;
		m_attribute4 = obj.m_attribute4;
		m_attribute5 = obj.m_attribute5;
		m_attribute6 = obj.m_attribute6;
		m_attribute7 = obj.m_attribute7;
		return (*this);
	}

	int32_t Test12Complex::ID() {
		return 12;
	}

	const string Test12Complex::ShortName() {
		return "Test12Complex";
	}

	const string Test12Complex::LongName() {
		return "Test12Complex";
	}

	int32_t Test12Complex::getID() const {
		return Test12Complex::ID();
	}

	const string Test12Complex::getShortName() const {
		return Test12Complex::ShortName();
	}

	const string Test12Complex::getLongName() const {
		return Test12Complex::LongName();
	}

	bool Test12Complex::getAttribute1() const {
		return m_attribute1;
	}
	
	void Test12Complex::setAttribute1(const bool &val) {
		m_attribute1 = val;
	}
	char Test12Complex::getAttribute2() const {
		return m_attribute2;
	}
	
	void Test12Complex::setAttribute2(const char &val) {
		m_attribute2 = val;
	}
	int32_t Test12Complex::getAttribute3() const {
		return m_attribute3;
	}
	
	void Test12Complex::setAttribute3(const int32_t &val) {
		m_attribute3 = val;
	}
	uint32_t Test12Complex::getAttribute4() const {
		return m_attribute4;
	}
	
	void Test12Complex::setAttribute4(const uint32_t &val) {
		m_attribute4 = val;
	}
	float Test12Complex::getAttribute5() const {
		return m_attribute5;
	}
	
	void Test12Complex::setAttribute5(const float &val) {
		m_attribute5 = val;
	}
	double Test12Complex::getAttribute6() const {
		return m_attribute6;
	}
	
	void Test12Complex::setAttribute6(const double &val) {
		m_attribute6 = val;
	}
	std::string Test12Complex::getAttribute7() const {
		return m_attribute7;
	}
	
	void Test12Complex::setAttribute7(const std::string &val) {
		m_attribute7 = val;
	}

	void Test12Complex::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT, 1, "Test12Complex.attribute1", "attribute1", m_attribute1);
		v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'2', NullType> > > > > > > > > >  >::RESULT, 2, "Test12Complex.attribute2", "attribute2", m_attribute2);
		v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'3', NullType> > > > > > > > > >  >::RESULT, 3, "Test12Complex.attribute3", "attribute3", m_attribute3);
		v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'4', NullType> > > > > > > > > >  >::RESULT, 4, "Test12Complex.attribute4", "attribute4", m_attribute4);
		v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'5', NullType> > > > > > > > > >  >::RESULT, 5, "Test12Complex.attribute5", "attribute5", m_attribute5);
		v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'6', NullType> > > > > > > > > >  >::RESULT, 6, "Test12Complex.attribute6", "attribute6", m_attribute6);
		v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'7', NullType> > > > > > > > > >  >::RESULT, 7, "Test12Complex.attribute7", "attribute7", m_attribute7);
		v.endVisit();
	}

	const string Test12Complex::toString() const {
		stringstream s;

		s << "Attribute1: " << getAttribute1() << " ";
		s << "Attribute2: " << getAttribute2() << " ";
		s << "Attribute3: " << getAttribute3() << " ";
		s << "Attribute4: " << getAttribute4() << " ";
		s << "Attribute5: " << getAttribute5() << " ";
		s << "Attribute6: " << getAttribute6() << " ";
		s << "Attribute7: " << getAttribute7() << " ";

		return s.str();
	}

	ostream& Test12Complex::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		s->write(1,
				m_attribute1);
		s->write(2,
				m_attribute2);
		s->write(3,
				m_attribute3);
		s->write(4,
				m_attribute4);
		s->write(5,
				m_attribute5);
		s->write(6,
				m_attribute6);
		s->write(7,
				m_attribute7);
		return out;
	}

	istream& Test12Complex::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		d->read(1,
				m_attribute1);
		d->read(2,
				m_attribute2);
		d->read(3,
				m_attribute3);
		d->read(4,
				m_attribute4);
		d->read(5,
				m_attribute5);
		d->read(6,
				m_attribute6);
		d->read(7,
				m_attribute7);
		return in;
	}
