/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TESTPACKAGE_TEST7A_TESTSUITE_H
#define TESTPACKAGE_TEST7A_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/strings/StringToolbox.h"

#include "test7/GeneratedHeaders_Test7.h"


class testpackage_Test7A_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
			using namespace testpackage;
	
			Test7A obj1;
			TS_ASSERT(obj1.getAttribute1() == false);
			TS_ASSERT(obj1.getAttribute2() == '\0');
			TS_ASSERT(obj1.getAttribute3() == 0);
	
			obj1.setAttribute1(true);
			obj1.setAttribute2('c');
			obj1.setAttribute3(-3000);
	
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -3000);
		}
	
		void testCreateAndCopyObject() {
			using namespace testpackage;
	
			Test7A obj1;
			TS_ASSERT(obj1.getAttribute1() == false);
			TS_ASSERT(obj1.getAttribute2() == '\0');
			TS_ASSERT(obj1.getAttribute3() == 0);
	
			Test7A obj2(obj1);
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
			TS_ASSERT(obj1.getAttribute2() == obj2.getAttribute2());
			TS_ASSERT(obj1.getAttribute3() == obj2.getAttribute3());
	
			obj1.setAttribute1(true);
			obj1.setAttribute2('c');
			obj1.setAttribute3(-3000);
	
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -3000);
	
			Test7A obj3(obj1);
			TS_ASSERT(obj1.getAttribute1() == obj3.getAttribute1());
			TS_ASSERT(obj1.getAttribute2() == obj3.getAttribute2());
			TS_ASSERT(obj1.getAttribute3() == obj3.getAttribute3());
	
			TS_ASSERT(obj3.getAttribute1() == true);
			TS_ASSERT(obj3.getAttribute2() == 'c');
			TS_ASSERT(obj3.getAttribute3() == -3000);
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace testpackage;
	
			Test7A obj1;
			TS_ASSERT(obj1.getAttribute1() == false);
			TS_ASSERT(obj1.getAttribute2() == '\0');
			TS_ASSERT(obj1.getAttribute3() == 0);
	
			Test7A obj2;
			TS_ASSERT(obj2.getAttribute1() == false);
			TS_ASSERT(obj2.getAttribute2() == '\0');
			TS_ASSERT(obj2.getAttribute3() == 0);
	
			obj1.setAttribute1(true);
			obj1.setAttribute2('c');
			obj1.setAttribute3(-3000);
	
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -3000);
	
			obj2 = obj1;
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
			TS_ASSERT(obj1.getAttribute2() == obj2.getAttribute2());
			TS_ASSERT(obj1.getAttribute3() == obj2.getAttribute3());
	
			TS_ASSERT(obj2.getAttribute1() == true);
			TS_ASSERT(obj2.getAttribute2() == 'c');
			TS_ASSERT(obj2.getAttribute3() == -3000);
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace testpackage;
	
			Test7A obj1;
			TS_ASSERT(obj1.getAttribute1() == false);
			TS_ASSERT(obj1.getAttribute2() == '\0');
			TS_ASSERT(obj1.getAttribute3() == 0);
	
			Test7A obj2;
			TS_ASSERT(obj2.getAttribute1() == false);
			TS_ASSERT(obj2.getAttribute2() == '\0');
			TS_ASSERT(obj2.getAttribute3() == 0);
	
			obj1.setAttribute1(true);
			obj1.setAttribute2('c');
			obj1.setAttribute3(-3000);
	
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -3000);
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
			TS_ASSERT(obj1.getAttribute2() == obj2.getAttribute2());
			TS_ASSERT(obj1.getAttribute3() == obj2.getAttribute3());
	
			TS_ASSERT(obj2.getAttribute1() == true);
			TS_ASSERT(obj2.getAttribute2() == 'c');
			TS_ASSERT(obj2.getAttribute3() == -3000);
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TESTPACKAGE_TEST7A_TESTSUITE_H*/
