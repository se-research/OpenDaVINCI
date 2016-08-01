/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"

#include "test4/generated/Test4.h"

	using namespace std;
	using namespace odcore::base;


	Test4::Test4() :
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

	Test4::Test4(
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

	Test4::Test4(const Test4 &obj) :
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
	
	Test4::~Test4() {
	}

	Test4& Test4::operator=(const Test4 &obj) {
		m_attribute1 = obj.m_attribute1;
		m_attribute2 = obj.m_attribute2;
		m_attribute3 = obj.m_attribute3;
		m_attribute4 = obj.m_attribute4;
		m_attribute5 = obj.m_attribute5;
		m_attribute6 = obj.m_attribute6;
		m_attribute7 = obj.m_attribute7;
		return (*this);
	}

	int32_t Test4::ID() {
		return 4;
	}

	const string Test4::ShortName() {
		return "Test4";
	}

	const string Test4::LongName() {
		return "Test4";
	}

	int32_t Test4::getID() const {
		return Test4::ID();
	}

	const string Test4::getShortName() const {
		return Test4::ShortName();
	}

	const string Test4::getLongName() const {
		return Test4::LongName();
	}

	bool Test4::getAttribute1() const {
		return m_attribute1;
	}
	
	void Test4::setAttribute1(const bool &val) {
		m_attribute1 = val;
	}
	char Test4::getAttribute2() const {
		return m_attribute2;
	}
	
	void Test4::setAttribute2(const char &val) {
		m_attribute2 = val;
	}
	int32_t Test4::getAttribute3() const {
		return m_attribute3;
	}
	
	void Test4::setAttribute3(const int32_t &val) {
		m_attribute3 = val;
	}
	uint32_t Test4::getAttribute4() const {
		return m_attribute4;
	}
	
	void Test4::setAttribute4(const uint32_t &val) {
		m_attribute4 = val;
	}
	float Test4::getAttribute5() const {
		return m_attribute5;
	}
	
	void Test4::setAttribute5(const float &val) {
		m_attribute5 = val;
	}
	double Test4::getAttribute6() const {
		return m_attribute6;
	}
	
	void Test4::setAttribute6(const double &val) {
		m_attribute6 = val;
	}
	std::string Test4::getAttribute7() const {
		return m_attribute7;
	}
	
	void Test4::setAttribute7(const std::string &val) {
		m_attribute7 = val;
	}

	void Test4::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.visit(0, 1, "Test4.attribute1", "attribute1", m_attribute1);
		v.visit(0, 2, "Test4.attribute2", "attribute2", m_attribute2);
		v.visit(0, 3, "Test4.attribute3", "attribute3", m_attribute3);
		v.visit(0, 4, "Test4.attribute4", "attribute4", m_attribute4);
		v.visit(0, 5, "Test4.attribute5", "attribute5", m_attribute5);
		v.visit(0, 6, "Test4.attribute6", "attribute6", m_attribute6);
		v.visit(0, 7, "Test4.attribute7", "attribute7", m_attribute7);
		v.endVisit();
	}

	const string Test4::toString() const {
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

	ostream& Test4::operator<<(ostream &out) const {
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

	istream& Test4::operator>>(istream &in) {
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
