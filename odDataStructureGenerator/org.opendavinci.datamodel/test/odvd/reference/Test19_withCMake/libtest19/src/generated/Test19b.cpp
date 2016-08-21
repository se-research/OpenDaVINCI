/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include <opendavinci/odcore/serialization/Deserializer.h>
#include <opendavinci/odcore/serialization/SerializationFactory.h>
#include <opendavinci/odcore/serialization/Serializer.h>

#include "test19/generated/Test19b.h"

	using namespace std;
	using namespace odcore::base;
	using namespace odcore::serialization;


	Test19b::Test19b() :
	    SerializableData(), Visitable()
	{
	}


	Test19b::Test19b(const Test19b &obj) :
	    SerializableData(), Visitable()
	{
		(void)obj; // Avoid unused parameter warning.
	}
	
	Test19b::~Test19b() {
	}

	Test19b& Test19b::operator=(const Test19b &obj) {
		(void)obj; // Avoid unused parameter warning.
		return (*this);
	}

	int32_t Test19b::ID() {
		return 20;
	}

	const string Test19b::ShortName() {
		return "Test19b";
	}

	const string Test19b::LongName() {
		return "Test19b";
	}

	int32_t Test19b::getID() const {
		return Test19b::ID();
	}

	const string Test19b::getShortName() const {
		return Test19b::ShortName();
	}

	const string Test19b::getLongName() const {
		return Test19b::LongName();
	}


	void Test19b::accept(odcore::base::Visitor &v) {
		v.beginVisit(ID(), ShortName(), LongName());
		v.endVisit();
	}

	const string Test19b::toString() const {
		stringstream s;


		return s.str();
	}

	ostream& Test19b::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);(void)s; // Avoid unused variable warning.

		return out;
	}

	istream& Test19b::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);(void)d; // Avoid unused variable warning.

		return in;
	}
