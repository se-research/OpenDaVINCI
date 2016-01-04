/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TESTPACKAGE_SUBPACKAGE_TEST8C_TESTSUITE_H
#define TESTPACKAGE_SUBPACKAGE_TEST8C_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test8.h"


class testpackage_subpackage_Test8C_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
			using namespace testpackage::subpackage;
	
			Test8C obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), ""));
	
			obj1.setAttribute1("Hello World!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), "Hello World!"));
		}
	
		void testCreateAndCopyObject() {
			using namespace testpackage::subpackage;
	
			Test8C obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), ""));
	
			Test8C obj2(obj1);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), obj2.getAttribute1()));
	
			obj1.setAttribute1("Hello World!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), "Hello World!"));
	
			Test8C obj3(obj1);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), obj3.getAttribute1()));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj3.getAttribute1(), "Hello World!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace testpackage::subpackage;
	
			Test8C obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), ""));
	
			Test8C obj2;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute1(), ""));
	
			obj1.setAttribute1("Hello World!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), "Hello World!"));
	
			obj2 = obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), obj2.getAttribute1()));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute1(), "Hello World!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace testpackage::subpackage;
	
			Test8C obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute1(), ""));
	
			Test8C obj2;
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

#endif /*TESTPACKAGE_SUBPACKAGE_TEST8C_TESTSUITE_H*/
