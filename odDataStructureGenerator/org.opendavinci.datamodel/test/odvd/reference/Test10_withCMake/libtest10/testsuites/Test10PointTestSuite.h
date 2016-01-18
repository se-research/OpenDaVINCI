/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST10POINT_TESTSUITE_H
#define TEST10POINT_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/strings/StringToolbox.h"

#include "test10/GeneratedHeaders_Test10.h"


class Test10Point_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test10Point obj1;
			TS_ASSERT_DELTA(obj1.getX(), 0, 1e-5);
			TS_ASSERT_DELTA(obj1.getY(), 0, 1e-5);
	
			obj1.setX(2.5);
			obj1.setY(2.5);
	
			TS_ASSERT_DELTA(obj1.getX(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj1.getY(), 2.5, 1e-5);
		}
	
		void testCreateAndCopyObject() {
	
			Test10Point obj1;
			TS_ASSERT_DELTA(obj1.getX(), 0, 1e-5);
			TS_ASSERT_DELTA(obj1.getY(), 0, 1e-5);
	
			Test10Point obj2(obj1);
			TS_ASSERT_DELTA(obj1.getX(), obj2.getX(), 1e-5);
			TS_ASSERT_DELTA(obj1.getY(), obj2.getY(), 1e-5);
	
			obj1.setX(2.5);
			obj1.setY(2.5);
	
			TS_ASSERT_DELTA(obj1.getX(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj1.getY(), 2.5, 1e-5);
	
			Test10Point obj3(obj1);
			TS_ASSERT_DELTA(obj1.getX(), obj3.getX(), 1e-5);
			TS_ASSERT_DELTA(obj1.getY(), obj3.getY(), 1e-5);
	
			TS_ASSERT_DELTA(obj3.getX(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj3.getY(), 2.5, 1e-5);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test10Point obj1;
			TS_ASSERT_DELTA(obj1.getX(), 0, 1e-5);
			TS_ASSERT_DELTA(obj1.getY(), 0, 1e-5);
	
			Test10Point obj2;
			TS_ASSERT_DELTA(obj2.getX(), 0, 1e-5);
			TS_ASSERT_DELTA(obj2.getY(), 0, 1e-5);
	
			obj1.setX(2.5);
			obj1.setY(2.5);
	
			TS_ASSERT_DELTA(obj1.getX(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj1.getY(), 2.5, 1e-5);
	
			obj2 = obj1;
			TS_ASSERT_DELTA(obj1.getX(), obj2.getX(), 1e-5);
			TS_ASSERT_DELTA(obj1.getY(), obj2.getY(), 1e-5);
	
			TS_ASSERT_DELTA(obj2.getX(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj2.getY(), 2.5, 1e-5);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test10Point obj1;
			TS_ASSERT_DELTA(obj1.getX(), 0, 1e-5);
			TS_ASSERT_DELTA(obj1.getY(), 0, 1e-5);
	
			Test10Point obj2;
			TS_ASSERT_DELTA(obj2.getX(), 0, 1e-5);
			TS_ASSERT_DELTA(obj2.getY(), 0, 1e-5);
	
			obj1.setX(2.5);
			obj1.setY(2.5);
	
			TS_ASSERT_DELTA(obj1.getX(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj1.getY(), 2.5, 1e-5);
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT_DELTA(obj1.getX(), obj2.getX(), 1e-5);
			TS_ASSERT_DELTA(obj1.getY(), obj2.getY(), 1e-5);
	
			TS_ASSERT_DELTA(obj2.getX(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj2.getY(), 2.5, 1e-5);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST10POINT_TESTSUITE_H*/
