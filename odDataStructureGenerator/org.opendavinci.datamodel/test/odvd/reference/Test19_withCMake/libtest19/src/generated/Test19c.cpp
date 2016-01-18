/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"


#include "test19/generated/Test19c.h"

	using namespace std;
	using namespace core::base;

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


	void Test19c::accept(core::base::Visitor &v) {
		(void)v; // Avoid unused parameter warning.
	}

	const string Test19c::toString() const {
		stringstream s;



		return s.str();
	}

	ostream& Test19c::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Serializer> s = sf.getSerializer(out);(void)s; // Avoid unused variable warning.

		return out;
	}

	istream& Test19c::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Deserializer> d = sf.getDeserializer(in);(void)d; // Avoid unused variable warning.

		return in;
	}
