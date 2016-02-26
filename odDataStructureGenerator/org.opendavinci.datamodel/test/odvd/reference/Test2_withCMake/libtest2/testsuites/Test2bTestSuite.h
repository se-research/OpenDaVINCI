/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST2B_TESTSUITE_H
#define TEST2B_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/strings/StringToolbox.h"

#include "test2/GeneratedHeaders_Test2.h"


class Test2b_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test2b obj1;
	
	
		}
	
		void testCreateAndCopyObject() {
	
			Test2b obj1;
	
			Test2b obj2(obj1);
	
	
	
			Test2b obj3(obj1);
	
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test2b obj1;
	
			Test2b obj2;
	
	
	
			obj2 = obj1;
	
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test2b obj1;
	
			Test2b obj2;
	
	
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
	
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST2B_TESTSUITE_H*/
