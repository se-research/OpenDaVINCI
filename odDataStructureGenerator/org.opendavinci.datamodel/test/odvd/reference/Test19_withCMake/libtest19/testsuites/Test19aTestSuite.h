/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST19A_TESTSUITE_H
#define TEST19A_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// core/opendavinci.h must be included to setup platform-dependent header files and configurations.
#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test19.h"


class Test19a_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test19a obj1;
	
	
		}
	
		void testCreateAndCopyObject() {
	
			Test19a obj1;
	
			Test19a obj2(obj1);
	
	
	
			Test19a obj3(obj1);
	
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test19a obj1;
	
			Test19a obj2;
	
	
	
			obj2 = obj1;
	
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test19a obj1;
	
			Test19a obj2;
	
	
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
	
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST19A_TESTSUITE_H*/
