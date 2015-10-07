/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef SUB_STRUCTURE_TEST20B_TESTSUITE_H
#define SUB_STRUCTURE_TEST20B_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test20.h"


class sub_structure_Test20b_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
			using namespace sub::structure;
	
			Test20b obj1;
			TS_ASSERT(obj1.getVal2() == 0);
	
			obj1.setVal2(4000);
	
			TS_ASSERT(obj1.getVal2() == 4000);
		}
	
		void testCreateAndCopyObject() {
			using namespace sub::structure;
	
			Test20b obj1;
			TS_ASSERT(obj1.getVal2() == 0);
	
			Test20b obj2(obj1);
			TS_ASSERT(obj1.getVal2() == obj2.getVal2());
	
			obj1.setVal2(4000);
	
			TS_ASSERT(obj1.getVal2() == 4000);
	
			Test20b obj3(obj1);
			TS_ASSERT(obj1.getVal2() == obj3.getVal2());
	
			TS_ASSERT(obj3.getVal2() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace sub::structure;
	
			Test20b obj1;
			TS_ASSERT(obj1.getVal2() == 0);
	
			Test20b obj2;
			TS_ASSERT(obj2.getVal2() == 0);
	
			obj1.setVal2(4000);
	
			TS_ASSERT(obj1.getVal2() == 4000);
	
			obj2 = obj1;
			TS_ASSERT(obj1.getVal2() == obj2.getVal2());
	
			TS_ASSERT(obj2.getVal2() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace sub::structure;
	
			Test20b obj1;
			TS_ASSERT(obj1.getVal2() == 0);
	
			Test20b obj2;
			TS_ASSERT(obj2.getVal2() == 0);
	
			obj1.setVal2(4000);
	
			TS_ASSERT(obj1.getVal2() == 4000);
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getVal2() == obj2.getVal2());
	
			TS_ASSERT(obj2.getVal2() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*SUB_STRUCTURE_TEST20B_TESTSUITE_H*/
