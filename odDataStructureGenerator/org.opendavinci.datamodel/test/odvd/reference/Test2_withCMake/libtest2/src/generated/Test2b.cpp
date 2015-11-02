/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"


#include "generated/Test2b.h"

	using namespace std;
	using namespace core::base;


	Test2b::Test2b() :
	    SerializableData(), Visitable()
	{
	}


	Test2b::Test2b(const Test2b &obj) :
	    SerializableData(), Visitable()
	{
		(void)obj; // Avoid unused parameter warning.
	}
	
	Test2b::~Test2b() {
	}

	Test2b& Test2b::operator=(const Test2b &obj) {
		(void)obj; // Avoid unused parameter warning.
		return (*this);
	}

	int32_t Test2b::ID() {
		return 2;
	}

	const string Test2b::ShortName() {
		return "Test2b";
	}

	const string Test2b::LongName() {
		return "Test2b";
	}

	int32_t Test2b::getID() const {
		return Test2b::ID();
	}

	const string Test2b::getShortName() const {
		return Test2b::ShortName();
	}

	const string Test2b::getLongName() const {
		return Test2b::LongName();
	}


	void Test2b::accept(core::base::Visitor &v) {
		(void)v; // Avoid unused parameter warning.
	}

	const string Test2b::toString() const {
		stringstream s;



		return s.str();
	}

	ostream& Test2b::operator<<(ostream &out) const {

		return out;
	}

	istream& Test2b::operator>>(istream &in) {

		return in;
	}
