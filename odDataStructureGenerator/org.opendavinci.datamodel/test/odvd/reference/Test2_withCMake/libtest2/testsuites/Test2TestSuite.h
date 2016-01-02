/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST2_TESTSUITE_H
#define TEST2_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// core/opendavinci.h must be included to setup platform-dependent header files and configurations.
#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test2.h"


class Test2_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test2 obj1;
			TS_ASSERT(obj1.getAttribute1() == 0);
	
			obj1.setAttribute1(4000);
	
			TS_ASSERT(obj1.getAttribute1() == 4000);
		}
	
		void testCreateAndCopyObject() {
	
			Test2 obj1;
			TS_ASSERT(obj1.getAttribute1() == 0);
	
			Test2 obj2(obj1);
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
	
			obj1.setAttribute1(4000);
	
			TS_ASSERT(obj1.getAttribute1() == 4000);
	
			Test2 obj3(obj1);
			TS_ASSERT(obj1.getAttribute1() == obj3.getAttribute1());
	
			TS_ASSERT(obj3.getAttribute1() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test2 obj1;
			TS_ASSERT(obj1.getAttribute1() == 0);
	
			Test2 obj2;
			TS_ASSERT(obj2.getAttribute1() == 0);
	
			obj1.setAttribute1(4000);
	
			TS_ASSERT(obj1.getAttribute1() == 4000);
	
			obj2 = obj1;
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
	
			TS_ASSERT(obj2.getAttribute1() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test2 obj1;
			TS_ASSERT(obj1.getAttribute1() == 0);
	
			Test2 obj2;
			TS_ASSERT(obj2.getAttribute1() == 0);
	
			obj1.setAttribute1(4000);
	
			TS_ASSERT(obj1.getAttribute1() == 4000);
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
	
			TS_ASSERT(obj2.getAttribute1() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST2_TESTSUITE_H*/
