/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"

#include "test10/generated/Test10Point.h"

	using namespace std;
	using namespace odcore::base;


	Test10Point::Test10Point() :
	    SerializableData(), Visitable()
		, m_x(0)
		, m_y(0)
	{
	}

	Test10Point::Test10Point(
		const float &val0, 
		const float &val1
	) :
	    SerializableData(), Visitable()
		, m_x(val0)
		, m_y(val1)
	{
	}

	Test10Point::Test10Point(const Test10Point &obj) :
	    SerializableData(), Visitable()
		, m_x(obj.m_x)
		, m_y(obj.m_y)
	{
	}
	
	Test10Point::~Test10Point() {
	}

	Test10Point& Test10Point::operator=(const Test10Point &obj) {
		m_x = obj.m_x;
		m_y = obj.m_y;
		return (*this);
	}

	int32_t Test10Point::ID() {
		return 10;
	}

	const string Test10Point::ShortName() {
		return "Test10Point";
	}

	const string Test10Point::LongName() {
		return "Test10Point";
	}

	int32_t Test10Point::getID() const {
		return Test10Point::ID();
	}

	const string Test10Point::getShortName() const {
		return Test10Point::ShortName();
	}

	const string Test10Point::getLongName() const {
		return Test10Point::LongName();
	}

	float Test10Point::getX() const {
		return m_x;
	}
	
	void Test10Point::setX(const float &val) {
		m_x = val;
	}
	float Test10Point::getY() const {
		return m_y;
	}
	
	void Test10Point::setY(const float &val) {
		m_y = val;
	}

	void Test10Point::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.visit(0, 1, "Test10Point.x", "x", m_x);
		v.visit(0, 2, "Test10Point.y", "y", m_y);
		v.endVisit();
	}

	const string Test10Point::toString() const {
		stringstream s;

		s << "X: " << getX() << " ";
		s << "Y: " << getY() << " ";

		return s.str();
	}

	ostream& Test10Point::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		s->write(1,
				m_x);
		s->write(2,
				m_y);
		return out;
	}

	istream& Test10Point::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		d->read(1,
				m_x);
		d->read(2,
				m_y);
		return in;
	}
