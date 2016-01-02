/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST20A_TESTSUITE_H
#define TEST20A_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// core/opendavinci.h must be included to setup platform-dependent header files and configurations.
#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test20.h"

#include "core/data/TimeStamp.h"

class Test20a_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test20a obj1;
			TS_ASSERT(obj1.getVal1() == 0);
	
			obj1.setVal1(4000);
	
			TS_ASSERT(obj1.getVal1() == 4000);
		}
	
		void testCreateAndCopyObject() {
	
			Test20a obj1;
			TS_ASSERT(obj1.getVal1() == 0);
	
			Test20a obj2(obj1);
			TS_ASSERT(obj1.getVal1() == obj2.getVal1());
	
			obj1.setVal1(4000);
	
			TS_ASSERT(obj1.getVal1() == 4000);
	
			Test20a obj3(obj1);
			TS_ASSERT(obj1.getVal1() == obj3.getVal1());
	
			TS_ASSERT(obj3.getVal1() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test20a obj1;
			TS_ASSERT(obj1.getVal1() == 0);
	
			Test20a obj2;
			TS_ASSERT(obj2.getVal1() == 0);
	
			obj1.setVal1(4000);
	
			TS_ASSERT(obj1.getVal1() == 4000);
	
			obj2 = obj1;
			TS_ASSERT(obj1.getVal1() == obj2.getVal1());
	
			TS_ASSERT(obj2.getVal1() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test20a obj1;
			TS_ASSERT(obj1.getVal1() == 0);
	
			Test20a obj2;
			TS_ASSERT(obj2.getVal1() == 0);
	
			obj1.setVal1(4000);
	
			TS_ASSERT(obj1.getVal1() == 4000);
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getVal1() == obj2.getVal1());
	
			TS_ASSERT(obj2.getVal1() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST20A_TESTSUITE_H*/
