/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST11SIMPLE_TESTSUITE_H
#define TEST11SIMPLE_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/strings/StringToolbox.h"

#include "test11/GeneratedHeaders_Test11.h"


class Test11Simple_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test11Simple obj1;
			TS_ASSERT(obj1.getData1() == 0);
			TS_ASSERT(obj1.getData2() == 0);
	
			obj1.setData1(4000);
			obj1.setData2(4000);
	
			TS_ASSERT(obj1.getData1() == 4000);
			TS_ASSERT(obj1.getData2() == 4000);
		}
	
		void testCreateAndCopyObject() {
	
			Test11Simple obj1;
			TS_ASSERT(obj1.getData1() == 0);
			TS_ASSERT(obj1.getData2() == 0);
	
			Test11Simple obj2(obj1);
			TS_ASSERT(obj1.getData1() == obj2.getData1());
			TS_ASSERT(obj1.getData2() == obj2.getData2());
	
			obj1.setData1(4000);
			obj1.setData2(4000);
	
			TS_ASSERT(obj1.getData1() == 4000);
			TS_ASSERT(obj1.getData2() == 4000);
	
			Test11Simple obj3(obj1);
			TS_ASSERT(obj1.getData1() == obj3.getData1());
			TS_ASSERT(obj1.getData2() == obj3.getData2());
	
			TS_ASSERT(obj3.getData1() == 4000);
			TS_ASSERT(obj3.getData2() == 4000);
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test11Simple obj1;
			TS_ASSERT(obj1.getData1() == 0);
			TS_ASSERT(obj1.getData2() == 0);
	
			Test11Simple obj2;
			TS_ASSERT(obj2.getData1() == 0);
			TS_ASSERT(obj2.getData2() == 0);
	
			obj1.setData1(4000);
			obj1.setData2(4000);
	
			TS_ASSERT(obj1.getData1() == 4000);
			TS_ASSERT(obj1.getData2() == 4000);
	
			obj2 = obj1;
			TS_ASSERT(obj1.getData1() == obj2.getData1());
			TS_ASSERT(obj1.getData2() == obj2.getData2());
	
			TS_ASSERT(obj2.getData1() == 4000);
			TS_ASSERT(obj2.getData2() == 4000);
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test11Simple obj1;
			TS_ASSERT(obj1.getData1() == 0);
			TS_ASSERT(obj1.getData2() == 0);
	
			Test11Simple obj2;
			TS_ASSERT(obj2.getData1() == 0);
			TS_ASSERT(obj2.getData2() == 0);
	
			obj1.setData1(4000);
			obj1.setData2(4000);
	
			TS_ASSERT(obj1.getData1() == 4000);
			TS_ASSERT(obj1.getData2() == 4000);
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getData1() == obj2.getData1());
			TS_ASSERT(obj1.getData2() == obj2.getData2());
	
			TS_ASSERT(obj2.getData1() == 4000);
			TS_ASSERT(obj2.getData2() == 4000);
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST11SIMPLE_TESTSUITE_H*/
