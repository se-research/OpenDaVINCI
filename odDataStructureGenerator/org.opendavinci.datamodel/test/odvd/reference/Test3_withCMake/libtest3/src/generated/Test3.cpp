/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include <opendavinci/odcore/serialization/Deserializer.h>
#include <opendavinci/odcore/serialization/SerializationFactory.h>
#include <opendavinci/odcore/serialization/Serializer.h>

#include "test3/generated/Test3.h"

	using namespace std;
	using namespace odcore::base;
	using namespace odcore::serialization;


	Test3::Test3() :
	    SerializableData(), Visitable()
		, m_attribute1(false)
		, m_attribute2('\0')
		, m_attribute3(0)
		, m_attribute4(0)
		, m_attribute5(0)
		, m_attribute6(0.0)
		, m_attribute7("")
	{
	}

	Test3::Test3(
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

	Test3::Test3(const Test3 &obj) :
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
	
	Test3::~Test3() {
	}

	Test3& Test3::operator=(const Test3 &obj) {
		m_attribute1 = obj.m_attribute1;
		m_attribute2 = obj.m_attribute2;
		m_attribute3 = obj.m_attribute3;
		m_attribute4 = obj.m_attribute4;
		m_attribute5 = obj.m_attribute5;
		m_attribute6 = obj.m_attribute6;
		m_attribute7 = obj.m_attribute7;
		return (*this);
	}

	int32_t Test3::ID() {
		return 3;
	}

	const string Test3::ShortName() {
		return "Test3";
	}

	const string Test3::LongName() {
		return "Test3";
	}

	int32_t Test3::getID() const {
		return Test3::ID();
	}

	const string Test3::getShortName() const {
		return Test3::ShortName();
	}

	const string Test3::getLongName() const {
		return Test3::LongName();
	}

	bool Test3::getAttribute1() const {
		return m_attribute1;
	}
	
	void Test3::setAttribute1(const bool &val) {
		m_attribute1 = val;
	}
	char Test3::getAttribute2() const {
		return m_attribute2;
	}
	
	void Test3::setAttribute2(const char &val) {
		m_attribute2 = val;
	}
	int32_t Test3::getAttribute3() const {
		return m_attribute3;
	}
	
	void Test3::setAttribute3(const int32_t &val) {
		m_attribute3 = val;
	}
	uint32_t Test3::getAttribute4() const {
		return m_attribute4;
	}
	
	void Test3::setAttribute4(const uint32_t &val) {
		m_attribute4 = val;
	}
	float Test3::getAttribute5() const {
		return m_attribute5;
	}
	
	void Test3::setAttribute5(const float &val) {
		m_attribute5 = val;
	}
	double Test3::getAttribute6() const {
		return m_attribute6;
	}
	
	void Test3::setAttribute6(const double &val) {
		m_attribute6 = val;
	}
	std::string Test3::getAttribute7() const {
		return m_attribute7;
	}
	
	void Test3::setAttribute7(const std::string &val) {
		m_attribute7 = val;
	}

	void Test3::accept(odcore::base::Visitor &v) {
		v.beginVisit(ID(), ShortName(), LongName());
		v.visit(1, "Test3.attribute1", "attribute1", m_attribute1);
		v.visit(2, "Test3.attribute2", "attribute2", m_attribute2);
		v.visit(3, "Test3.attribute3", "attribute3", m_attribute3);
		v.visit(4, "Test3.attribute4", "attribute4", m_attribute4);
		v.visit(5, "Test3.attribute5", "attribute5", m_attribute5);
		v.visit(6, "Test3.attribute6", "attribute6", m_attribute6);
		v.visit(7, "Test3.attribute7", "attribute7", m_attribute7);
		v.endVisit();
	}

	const string Test3::toString() const {
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

	ostream& Test3::operator<<(ostream &out) const {
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

	istream& Test3::operator>>(istream &in) {
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
