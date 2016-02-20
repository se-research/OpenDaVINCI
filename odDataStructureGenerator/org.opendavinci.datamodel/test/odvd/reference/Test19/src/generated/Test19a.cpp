/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"


#include "test19/generated/Test19a.h"

	using namespace std;
	using namespace odcore::base;

	const uint32_t Test19a::MAGIC_NUMBER = 42;
	const float Test19a::PI = 3.14159;
	const std::string Test19a::HELLOWORLD = "Hello World!";

	Test19a::Test19a() :
	    SerializableData(), Visitable()
	{
	}


	Test19a::Test19a(const Test19a &obj) :
	    SerializableData(), Visitable()
	{
		(void)obj; // Avoid unused parameter warning.
	}
	
	Test19a::~Test19a() {
	}

	Test19a& Test19a::operator=(const Test19a &obj) {
		(void)obj; // Avoid unused parameter warning.
		return (*this);
	}

	int32_t Test19a::ID() {
		return 19;
	}

	const string Test19a::ShortName() {
		return "Test19a";
	}

	const string Test19a::LongName() {
		return "Test19a";
	}


	void Test19a::accept(odcore::base::Visitor &v) {
		(void)v; // Avoid unused parameter warning.
	}

	const string Test19a::toString() const {
		stringstream s;



		return s.str();
	}

	ostream& Test19a::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		odcore::SharedPointer<Serializer> s = sf.getSerializer(out);(void)s; // Avoid unused variable warning.

		return out;
	}

	istream& Test19a::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		odcore::SharedPointer<Deserializer> d = sf.getDeserializer(in);(void)d; // Avoid unused variable warning.

		return in;
	}
