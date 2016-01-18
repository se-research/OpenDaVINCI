/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"


#include "test12/generated/Test12Simple.h"

	using namespace std;
	using namespace core::base;


	Test12Simple::Test12Simple() :
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

	Test12Simple::Test12Simple(
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

	Test12Simple::Test12Simple(const Test12Simple &obj) :
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
	
	Test12Simple::~Test12Simple() {
	}

	Test12Simple& Test12Simple::operator=(const Test12Simple &obj) {
		m_attribute1 = obj.m_attribute1;
		m_attribute2 = obj.m_attribute2;
		m_attribute3 = obj.m_attribute3;
		m_attribute4 = obj.m_attribute4;
		m_attribute5 = obj.m_attribute5;
		m_attribute6 = obj.m_attribute6;
		m_attribute7 = obj.m_attribute7;
		return (*this);
	}

	int32_t Test12Simple::ID() {
		return 11;
	}

	const string Test12Simple::ShortName() {
		return "Test12Simple";
	}

	const string Test12Simple::LongName() {
		return "Test12Simple";
	}

	bool Test12Simple::getAttribute1() const {
		return m_attribute1;
	}
	
	void Test12Simple::setAttribute1(const bool &val) {
		m_attribute1 = val;
	}
	char Test12Simple::getAttribute2() const {
		return m_attribute2;
	}
	
	void Test12Simple::setAttribute2(const char &val) {
		m_attribute2 = val;
	}
	int32_t Test12Simple::getAttribute3() const {
		return m_attribute3;
	}
	
	void Test12Simple::setAttribute3(const int32_t &val) {
		m_attribute3 = val;
	}
	uint32_t Test12Simple::getAttribute4() const {
		return m_attribute4;
	}
	
	void Test12Simple::setAttribute4(const uint32_t &val) {
		m_attribute4 = val;
	}
	float Test12Simple::getAttribute5() const {
		return m_attribute5;
	}
	
	void Test12Simple::setAttribute5(const float &val) {
		m_attribute5 = val;
	}
	double Test12Simple::getAttribute6() const {
		return m_attribute6;
	}
	
	void Test12Simple::setAttribute6(const double &val) {
		m_attribute6 = val;
	}
	std::string Test12Simple::getAttribute7() const {
		return m_attribute7;
	}
	
	void Test12Simple::setAttribute7(const std::string &val) {
		m_attribute7 = val;
	}

	void Test12Simple::accept(core::base::Visitor &v) {
		v.visit(1, 0, "Test12Simple.attribute1", "attribute1", m_attribute1);
		v.visit(2, 0, "Test12Simple.attribute2", "attribute2", m_attribute2);
		v.visit(3, 0, "Test12Simple.attribute3", "attribute3", m_attribute3);
		v.visit(4, 0, "Test12Simple.attribute4", "attribute4", m_attribute4);
		v.visit(5, 0, "Test12Simple.attribute5", "attribute5", m_attribute5);
		v.visit(6, 0, "Test12Simple.attribute6", "attribute6", m_attribute6);
		v.visit(7, 0, "Test12Simple.attribute7", "attribute7", m_attribute7);
	}

	const string Test12Simple::toString() const {
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

	ostream& Test12Simple::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Serializer> s = sf.getSerializer(out);

		s->write(1, m_attribute1);
		s->write(2, m_attribute2);
		s->write(3, m_attribute3);
		s->write(4, m_attribute4);
		s->write(5, m_attribute5);
		s->write(6, m_attribute6);
		s->write(7, m_attribute7);
		return out;
	}

	istream& Test12Simple::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

		d->read(1, m_attribute1);
		d->read(2, m_attribute2);
		d->read(3, m_attribute3);
		d->read(4, m_attribute4);
		d->read(5, m_attribute5);
		d->read(6, m_attribute6);
		d->read(7, m_attribute7);
		return in;
	}
