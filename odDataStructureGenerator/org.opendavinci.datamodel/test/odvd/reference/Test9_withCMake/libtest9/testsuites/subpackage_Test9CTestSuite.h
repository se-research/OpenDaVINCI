/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef SUBPACKAGE_TEST9C_TESTSUITE_H
#define SUBPACKAGE_TEST9C_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test9.h"


class subpackage_Test9C_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
			using namespace subpackage;
	
			Test9C obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), ""));
	
			obj1.setAttribute1("Hello World!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), "Hello World!"));
		}
	
		void testCreateAndCopyObject() {
			using namespace subpackage;
	
			Test9C obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), ""));
	
			Test9C obj2(obj1);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), obj2.getAttribute1()));
	
			obj1.setAttribute1("Hello World!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), "Hello World!"));
	
			Test9C obj3(obj1);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), obj3.getAttribute1()));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj3.getAttribute1(), "Hello World!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace subpackage;
	
			Test9C obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), ""));
	
			Test9C obj2;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute1(), ""));
	
			obj1.setAttribute1("Hello World!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), "Hello World!"));
	
			obj2 = obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), obj2.getAttribute1()));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute1(), "Hello World!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace subpackage;
	
			Test9C obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), ""));
	
			Test9C obj2;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute1(), ""));
	
			obj1.setAttribute1("Hello World!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), "Hello World!"));
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), obj2.getAttribute1()));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute1(), "Hello World!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*SUBPACKAGE_TEST9C_TESTSUITE_H*/
