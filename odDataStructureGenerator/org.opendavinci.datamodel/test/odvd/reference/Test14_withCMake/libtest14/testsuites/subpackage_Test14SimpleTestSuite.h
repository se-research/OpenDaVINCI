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

#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test14.h"


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
	
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace subpackage;
	
			Test14Simple obj1;
	
			Test14Simple obj2;
	
	
	
			obj2 = obj1;
	
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace subpackage;
	
			Test14Simple obj1;
	
			Test14Simple obj2;
	
	
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
	
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*SUBPACKAGE_TEST14SIMPLE_TESTSUITE_H*/
