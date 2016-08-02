/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"

#include "test11/generated/Test11Simple.h"

	using namespace std;
	using namespace odcore::base;


	Test11Simple::Test11Simple() :
	    SerializableData(), Visitable()
		, m_data1(0)
		, m_data2(0)
	{
	}

	Test11Simple::Test11Simple(
		const uint32_t &val0, 
		const uint32_t &val1
	) :
	    SerializableData(), Visitable()
		, m_data1(val0)
		, m_data2(val1)
	{
	}

	Test11Simple::Test11Simple(const Test11Simple &obj) :
	    SerializableData(), Visitable()
		, m_data1(obj.m_data1)
		, m_data2(obj.m_data2)
	{
	}
	
	Test11Simple::~Test11Simple() {
	}

	Test11Simple& Test11Simple::operator=(const Test11Simple &obj) {
		m_data1 = obj.m_data1;
		m_data2 = obj.m_data2;
		return (*this);
	}

	int32_t Test11Simple::ID() {
		return 11;
	}

	const string Test11Simple::ShortName() {
		return "Test11Simple";
	}

	const string Test11Simple::LongName() {
		return "Test11Simple";
	}

	int32_t Test11Simple::getID() const {
		return Test11Simple::ID();
	}

	const string Test11Simple::getShortName() const {
		return Test11Simple::ShortName();
	}

	const string Test11Simple::getLongName() const {
		return Test11Simple::LongName();
	}

	uint32_t Test11Simple::getData1() const {
		return m_data1;
	}
	
	void Test11Simple::setData1(const uint32_t &val) {
		m_data1 = val;
	}
	uint32_t Test11Simple::getData2() const {
		return m_data2;
	}
	
	void Test11Simple::setData2(const uint32_t &val) {
		m_data2 = val;
	}

	void Test11Simple::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.visit(1, "Test11Simple.data1", "data1", m_data1);
		v.visit(2, "Test11Simple.data2", "data2", m_data2);
		v.endVisit();
	}

	const string Test11Simple::toString() const {
		stringstream s;

		s << "Data1: " << getData1() << " ";
		s << "Data2: " << getData2() << " ";

		return s.str();
	}

	ostream& Test11Simple::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		s->write(1,
				m_data1);
		s->write(2,
				m_data2);
		return out;
	}

	istream& Test11Simple::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		d->read(1,
				m_data1);
		d->read(2,
				m_data2);
		return in;
	}
