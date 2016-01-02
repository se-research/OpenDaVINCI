/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TESTPACKAGE_TEST8B_TESTSUITE_H
#define TESTPACKAGE_TEST8B_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// core/opendavinci.h must be included to setup platform-dependent header files and configurations.
#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test8.h"


class testpackage_Test8B_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
			using namespace testpackage;
	
			Test8B obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
	
			obj1.setAttribute1(true);
	
			TS_ASSERT(obj1.getAttribute1() == true);
		}
	
		void testCreateAndCopyObject() {
			using namespace testpackage;
	
			Test8B obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
	
			Test8B obj2(obj1);
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
	
			obj1.setAttribute1(true);
	
			TS_ASSERT(obj1.getAttribute1() == true);
	
			Test8B obj3(obj1);
			TS_ASSERT(obj1.getAttribute1() == obj3.getAttribute1());
	
			TS_ASSERT(obj3.getAttribute1() == true);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace testpackage;
	
			Test8B obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
	
			Test8B obj2;
			TS_ASSERT(obj2.getAttribute1() == true);
	
			obj1.setAttribute1(true);
	
			TS_ASSERT(obj1.getAttribute1() == true);
	
			obj2 = obj1;
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
	
			TS_ASSERT(obj2.getAttribute1() == true);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace testpackage;
	
			Test8B obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
	
			Test8B obj2;
			TS_ASSERT(obj2.getAttribute1() == true);
	
			obj1.setAttribute1(true);
	
			TS_ASSERT(obj1.getAttribute1() == true);
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
	
			TS_ASSERT(obj2.getAttribute1() == true);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TESTPACKAGE_TEST8B_TESTSUITE_H*/
