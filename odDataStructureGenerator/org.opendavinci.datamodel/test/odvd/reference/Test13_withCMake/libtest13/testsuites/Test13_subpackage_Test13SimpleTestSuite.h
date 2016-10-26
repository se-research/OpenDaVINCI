/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST13_SUBPACKAGE_TEST13SIMPLE_TESTSUITE_H
#define TEST13_SUBPACKAGE_TEST13SIMPLE_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/strings/StringToolbox.h>

#include "test13/GeneratedHeaders_Test13.h"
#include "test13/generated/Test13/subpackage/Test13Simple.h"


class Test13_subpackage_Test13Simple_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
			using namespace test13::subpackage;
	
			Test13Simple obj1;
	
	
		}
	
		void testCreateAndCopyObject() {
			using namespace test13::subpackage;
	
			Test13Simple obj1;
	
			Test13Simple obj2(obj1);
	
	
	
			Test13Simple obj3(obj1);
	
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace test13::subpackage;
	
			Test13Simple obj1;
	
			Test13Simple obj2;
	
	
	
			obj2 = obj1;
	
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace test13::subpackage;
	
			Test13Simple obj1;
	
			Test13Simple obj2;
	
	
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
	
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST13_SUBPACKAGE_TEST13SIMPLE_TESTSUITE_H*/
