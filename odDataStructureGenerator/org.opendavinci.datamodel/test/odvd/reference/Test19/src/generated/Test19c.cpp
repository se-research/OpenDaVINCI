/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"

#include "test19/generated/Test19c.h"

	using namespace std;
	using namespace odcore::base;

	const uint32_t Test19c::MAGIC_NUMBER = 42;
	const float Test19c::PI = 3.14159;

	Test19c::Test19c() :
	    SerializableData(), Visitable()
	{
	}


	Test19c::Test19c(const Test19c &obj) :
	    SerializableData(), Visitable()
	{
		(void)obj; // Avoid unused parameter warning.
	}
	
	Test19c::~Test19c() {
	}

	Test19c& Test19c::operator=(const Test19c &obj) {
		(void)obj; // Avoid unused parameter warning.
		return (*this);
	}

	int32_t Test19c::ID() {
		return 21;
	}

	const string Test19c::ShortName() {
		return "Test19c";
	}

	const string Test19c::LongName() {
		return "Test19c";
	}

	int32_t Test19c::getID() const {
		return Test19c::ID();
	}

	const string Test19c::getShortName() const {
		return Test19c::ShortName();
	}

	const string Test19c::getLongName() const {
		return Test19c::LongName();
	}


	void Test19c::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.endVisit();
	}

	const string Test19c::toString() const {
		stringstream s;


		return s.str();
	}

	ostream& Test19c::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);(void)s; // Avoid unused variable warning.

		return out;
	}

	istream& Test19c::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);(void)d; // Avoid unused variable warning.

		return in;
	}
