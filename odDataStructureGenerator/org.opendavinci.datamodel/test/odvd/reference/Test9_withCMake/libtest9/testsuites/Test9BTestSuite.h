/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST9B_TESTSUITE_H
#define TEST9B_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/strings/StringToolbox.h"

#include "test9/GeneratedHeaders_Test9.h"


class Test9B_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test9B obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
	
			obj1.setAttribute1(true);
	
			TS_ASSERT(obj1.getAttribute1() == true);
		}
	
		void testCreateAndCopyObject() {
	
			Test9B obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
	
			Test9B obj2(obj1);
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
	
			obj1.setAttribute1(true);
	
			TS_ASSERT(obj1.getAttribute1() == true);
	
			Test9B obj3(obj1);
			TS_ASSERT(obj1.getAttribute1() == obj3.getAttribute1());
	
			TS_ASSERT(obj3.getAttribute1() == true);
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test9B obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
	
			Test9B obj2;
			TS_ASSERT(obj2.getAttribute1() == true);
	
			obj1.setAttribute1(true);
	
			TS_ASSERT(obj1.getAttribute1() == true);
	
			obj2 = obj1;
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
	
			TS_ASSERT(obj2.getAttribute1() == true);
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test9B obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
	
			Test9B obj2;
			TS_ASSERT(obj2.getAttribute1() == true);
	
			obj1.setAttribute1(true);
	
			TS_ASSERT(obj1.getAttribute1() == true);
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
	
			TS_ASSERT(obj2.getAttribute1() == true);
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST9B_TESTSUITE_H*/
