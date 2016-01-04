/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef SUB_STRUCTURE_TEST17CHILD_TESTSUITE_H
#define SUB_STRUCTURE_TEST17CHILD_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test17.h"


class sub_structure_Test17Child_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
			using namespace sub::structure;
	
			Test17Child obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getMyName(), "ABC"));
	
			obj1.setMyName("Hello World!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getMyName(), "Hello World!"));
		}
	
		void testCreateAndCopyObject() {
			using namespace sub::structure;
	
			Test17Child obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getMyName(), "ABC"));
	
			Test17Child obj2(obj1);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getMyName(), obj2.getMyName()));
	
			obj1.setMyName("Hello World!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getMyName(), "Hello World!"));
	
			Test17Child obj3(obj1);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getMyName(), obj3.getMyName()));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj3.getMyName(), "Hello World!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace sub::structure;
	
			Test17Child obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getMyName(), "ABC"));
	
			Test17Child obj2;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getMyName(), "ABC"));
	
			obj1.setMyName("Hello World!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getMyName(), "Hello World!"));
	
			obj2 = obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getMyName(), obj2.getMyName()));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getMyName(), "Hello World!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace sub::structure;
	
			Test17Child obj1;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getMyName(), "ABC"));
	
			Test17Child obj2;
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getMyName(), "ABC"));
	
			obj1.setMyName("Hello World!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getMyName(), "Hello World!"));
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getMyName(), obj2.getMyName()));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getMyName(), "Hello World!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*SUB_STRUCTURE_TEST17CHILD_TESTSUITE_H*/
