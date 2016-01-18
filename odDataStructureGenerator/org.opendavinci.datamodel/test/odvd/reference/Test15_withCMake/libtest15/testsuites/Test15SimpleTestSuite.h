/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST15SIMPLE_TESTSUITE_H
#define TEST15SIMPLE_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/strings/StringToolbox.h"

#include "test15/GeneratedHeaders_Test15.h"


class Test15Simple_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test15Simple obj1;
	
	
		}
	
		void testCreateAndCopyObject() {
	
			Test15Simple obj1;
	
			Test15Simple obj2(obj1);
	
	
	
			Test15Simple obj3(obj1);
	
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test15Simple obj1;
	
			Test15Simple obj2;
	
	
	
			obj2 = obj1;
	
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test15Simple obj1;
	
			Test15Simple obj2;
	
	
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
	
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST15SIMPLE_TESTSUITE_H*/
