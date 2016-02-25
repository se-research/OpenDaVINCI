/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef SUB_STRUCTURE_TEST16SIMPLE_TESTSUITE_H
#define SUB_STRUCTURE_TEST16SIMPLE_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/strings/StringToolbox.h"

#include "test16/GeneratedHeaders_Test16.h"


class sub_structure_Test16Simple_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
			using namespace sub::structure;
	
			Test16Simple obj1;
			TS_ASSERT_DELTA(obj1.getMyData(), 4.6, 1e-5);
			TS_ASSERT(obj1.getMyValue() == 1);
	
			obj1.setMyData(1.0);
			obj1.setMyValue(-3000);
	
			TS_ASSERT_DELTA(obj1.getMyData(), 1.0, 1e-5);
			TS_ASSERT(obj1.getMyValue() == -3000);
		}
	
		void testCreateAndCopyObject() {
			using namespace sub::structure;
	
			Test16Simple obj1;
			TS_ASSERT_DELTA(obj1.getMyData(), 4.6, 1e-5);
			TS_ASSERT(obj1.getMyValue() == 1);
	
			Test16Simple obj2(obj1);
			TS_ASSERT_DELTA(obj1.getMyData(), obj2.getMyData(), 1e-5);
			TS_ASSERT(obj1.getMyValue() == obj2.getMyValue());
	
			obj1.setMyData(1.0);
			obj1.setMyValue(-3000);
	
			TS_ASSERT_DELTA(obj1.getMyData(), 1.0, 1e-5);
			TS_ASSERT(obj1.getMyValue() == -3000);
	
			Test16Simple obj3(obj1);
			TS_ASSERT_DELTA(obj1.getMyData(), obj3.getMyData(), 1e-5);
			TS_ASSERT(obj1.getMyValue() == obj3.getMyValue());
	
			TS_ASSERT_DELTA(obj3.getMyData(), 1.0, 1e-5);
			TS_ASSERT(obj3.getMyValue() == -3000);
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace sub::structure;
	
			Test16Simple obj1;
			TS_ASSERT_DELTA(obj1.getMyData(), 4.6, 1e-5);
			TS_ASSERT(obj1.getMyValue() == 1);
	
			Test16Simple obj2;
			TS_ASSERT_DELTA(obj2.getMyData(), 4.6, 1e-5);
			TS_ASSERT(obj2.getMyValue() == 1);
	
			obj1.setMyData(1.0);
			obj1.setMyValue(-3000);
	
			TS_ASSERT_DELTA(obj1.getMyData(), 1.0, 1e-5);
			TS_ASSERT(obj1.getMyValue() == -3000);
	
			obj2 = obj1;
			TS_ASSERT_DELTA(obj1.getMyData(), obj2.getMyData(), 1e-5);
			TS_ASSERT(obj1.getMyValue() == obj2.getMyValue());
	
			TS_ASSERT_DELTA(obj2.getMyData(), 1.0, 1e-5);
			TS_ASSERT(obj2.getMyValue() == -3000);
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace sub::structure;
	
			Test16Simple obj1;
			TS_ASSERT_DELTA(obj1.getMyData(), 4.6, 1e-5);
			TS_ASSERT(obj1.getMyValue() == 1);
	
			Test16Simple obj2;
			TS_ASSERT_DELTA(obj2.getMyData(), 4.6, 1e-5);
			TS_ASSERT(obj2.getMyValue() == 1);
	
			obj1.setMyData(1.0);
			obj1.setMyValue(-3000);
	
			TS_ASSERT_DELTA(obj1.getMyData(), 1.0, 1e-5);
			TS_ASSERT(obj1.getMyValue() == -3000);
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT_DELTA(obj1.getMyData(), obj2.getMyData(), 1e-5);
			TS_ASSERT(obj1.getMyValue() == obj2.getMyValue());
	
			TS_ASSERT_DELTA(obj2.getMyData(), 1.0, 1e-5);
			TS_ASSERT(obj2.getMyValue() == -3000);
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*SUB_STRUCTURE_TEST16SIMPLE_TESTSUITE_H*/
