/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef SUBPACKAGE_TEST14SIMPLE_TESTSUITE_H
#define SUBPACKAGE_TEST14SIMPLE_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/strings/StringToolbox.h>

#include "test14/GeneratedHeaders_Test14.h"
#include "test14/generated/subpackage/Test14Simple.h"


class subpackage_Test14Simple_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
			using namespace subpackage;
	
			Test14Simple obj1;
	
	
		}
	
		void testCreateAndCopyObject() {
			using namespace subpackage;
	
			Test14Simple obj1;
	
			Test14Simple obj2(obj1);
	
	
	
			Test14Simple obj3(obj1);
	
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace subpackage;
	
			Test14Simple obj1;
	
			Test14Simple obj2;
	
	
	
			obj2 = obj1;
	
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace subpackage;
	
			Test14Simple obj1;
	
			Test14Simple obj2;
	
	
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
	
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*SUBPACKAGE_TEST14SIMPLE_TESTSUITE_H*/
