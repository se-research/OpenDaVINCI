/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef SUB_STRUCTURE2_TEST20C_TESTSUITE_H
#define SUB_STRUCTURE2_TEST20C_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test20.h"

#include "generated/sub/structure/Test20b.h"

class sub_structure2_Test20c_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
			using namespace sub::structure2;
	
			Test20c obj1;
			TS_ASSERT(obj1.getVal3() == 0);
	
			obj1.setVal3(4000);
	
			TS_ASSERT(obj1.getVal3() == 4000);
		}
	
		void testCreateAndCopyObject() {
			using namespace sub::structure2;
	
			Test20c obj1;
			TS_ASSERT(obj1.getVal3() == 0);
	
			Test20c obj2(obj1);
			TS_ASSERT(obj1.getVal3() == obj2.getVal3());
	
			obj1.setVal3(4000);
	
			TS_ASSERT(obj1.getVal3() == 4000);
	
			Test20c obj3(obj1);
			TS_ASSERT(obj1.getVal3() == obj3.getVal3());
	
			TS_ASSERT(obj3.getVal3() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace sub::structure2;
	
			Test20c obj1;
			TS_ASSERT(obj1.getVal3() == 0);
	
			Test20c obj2;
			TS_ASSERT(obj2.getVal3() == 0);
	
			obj1.setVal3(4000);
	
			TS_ASSERT(obj1.getVal3() == 4000);
	
			obj2 = obj1;
			TS_ASSERT(obj1.getVal3() == obj2.getVal3());
	
			TS_ASSERT(obj2.getVal3() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace sub::structure2;
	
			Test20c obj1;
			TS_ASSERT(obj1.getVal3() == 0);
	
			Test20c obj2;
			TS_ASSERT(obj2.getVal3() == 0);
	
			obj1.setVal3(4000);
	
			TS_ASSERT(obj1.getVal3() == 4000);
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getVal3() == obj2.getVal3());
	
			TS_ASSERT(obj2.getVal3() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*SUB_STRUCTURE2_TEST20C_TESTSUITE_H*/
