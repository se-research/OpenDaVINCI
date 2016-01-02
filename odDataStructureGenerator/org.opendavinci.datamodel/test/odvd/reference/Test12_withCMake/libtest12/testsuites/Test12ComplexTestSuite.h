/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST12COMPLEX_TESTSUITE_H
#define TEST12COMPLEX_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// core/opendavinci.h must be included to setup platform-dependent header files and configurations.
#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test12.h"


class Test12Complex_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test12Complex obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -12);
			TS_ASSERT(obj1.getAttribute4() == +45);
			TS_ASSERT_DELTA(obj1.getAttribute5(), -0.12, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), +0.45678, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World."));
	
			obj1.setAttribute1(true);
			obj1.setAttribute2('c');
			obj1.setAttribute3(-3000);
			obj1.setAttribute4(4000);
			obj1.setAttribute5(2.5);
			obj1.setAttribute6(1.0);
			obj1.setAttribute7("Hello World!");
	
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -3000);
			TS_ASSERT(obj1.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj1.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World!"));
		}
	
		void testCreateAndCopyObject() {
	
			Test12Complex obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -12);
			TS_ASSERT(obj1.getAttribute4() == +45);
			TS_ASSERT_DELTA(obj1.getAttribute5(), -0.12, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), +0.45678, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World."));
	
			Test12Complex obj2(obj1);
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
			TS_ASSERT(obj1.getAttribute2() == obj2.getAttribute2());
			TS_ASSERT(obj1.getAttribute3() == obj2.getAttribute3());
			TS_ASSERT(obj1.getAttribute4() == obj2.getAttribute4());
			TS_ASSERT_DELTA(obj1.getAttribute5(), obj2.getAttribute5(), 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), obj2.getAttribute6(), 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), obj2.getAttribute7()));
	
			obj1.setAttribute1(true);
			obj1.setAttribute2('c');
			obj1.setAttribute3(-3000);
			obj1.setAttribute4(4000);
			obj1.setAttribute5(2.5);
			obj1.setAttribute6(1.0);
			obj1.setAttribute7("Hello World!");
	
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -3000);
			TS_ASSERT(obj1.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj1.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World!"));
	
			Test12Complex obj3(obj1);
			TS_ASSERT(obj1.getAttribute1() == obj3.getAttribute1());
			TS_ASSERT(obj1.getAttribute2() == obj3.getAttribute2());
			TS_ASSERT(obj1.getAttribute3() == obj3.getAttribute3());
			TS_ASSERT(obj1.getAttribute4() == obj3.getAttribute4());
			TS_ASSERT_DELTA(obj1.getAttribute5(), obj3.getAttribute5(), 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), obj3.getAttribute6(), 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), obj3.getAttribute7()));
	
			TS_ASSERT(obj3.getAttribute1() == true);
			TS_ASSERT(obj3.getAttribute2() == 'c');
			TS_ASSERT(obj3.getAttribute3() == -3000);
			TS_ASSERT(obj3.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj3.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj3.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj3.getAttribute7(), "Hello World!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test12Complex obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -12);
			TS_ASSERT(obj1.getAttribute4() == +45);
			TS_ASSERT_DELTA(obj1.getAttribute5(), -0.12, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), +0.45678, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World."));
	
			Test12Complex obj2;
			TS_ASSERT(obj2.getAttribute1() == true);
			TS_ASSERT(obj2.getAttribute2() == 'c');
			TS_ASSERT(obj2.getAttribute3() == -12);
			TS_ASSERT(obj2.getAttribute4() == +45);
			TS_ASSERT_DELTA(obj2.getAttribute5(), -0.12, 1e-5);
			TS_ASSERT_DELTA(obj2.getAttribute6(), +0.45678, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute7(), "Hello World."));
	
			obj1.setAttribute1(true);
			obj1.setAttribute2('c');
			obj1.setAttribute3(-3000);
			obj1.setAttribute4(4000);
			obj1.setAttribute5(2.5);
			obj1.setAttribute6(1.0);
			obj1.setAttribute7("Hello World!");
	
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -3000);
			TS_ASSERT(obj1.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj1.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World!"));
	
			obj2 = obj1;
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
			TS_ASSERT(obj1.getAttribute2() == obj2.getAttribute2());
			TS_ASSERT(obj1.getAttribute3() == obj2.getAttribute3());
			TS_ASSERT(obj1.getAttribute4() == obj2.getAttribute4());
			TS_ASSERT_DELTA(obj1.getAttribute5(), obj2.getAttribute5(), 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), obj2.getAttribute6(), 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), obj2.getAttribute7()));
	
			TS_ASSERT(obj2.getAttribute1() == true);
			TS_ASSERT(obj2.getAttribute2() == 'c');
			TS_ASSERT(obj2.getAttribute3() == -3000);
			TS_ASSERT(obj2.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj2.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj2.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute7(), "Hello World!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test12Complex obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -12);
			TS_ASSERT(obj1.getAttribute4() == +45);
			TS_ASSERT_DELTA(obj1.getAttribute5(), -0.12, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), +0.45678, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World."));
	
			Test12Complex obj2;
			TS_ASSERT(obj2.getAttribute1() == true);
			TS_ASSERT(obj2.getAttribute2() == 'c');
			TS_ASSERT(obj2.getAttribute3() == -12);
			TS_ASSERT(obj2.getAttribute4() == +45);
			TS_ASSERT_DELTA(obj2.getAttribute5(), -0.12, 1e-5);
			TS_ASSERT_DELTA(obj2.getAttribute6(), +0.45678, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute7(), "Hello World."));
	
			obj1.setAttribute1(true);
			obj1.setAttribute2('c');
			obj1.setAttribute3(-3000);
			obj1.setAttribute4(4000);
			obj1.setAttribute5(2.5);
			obj1.setAttribute6(1.0);
			obj1.setAttribute7("Hello World!");
	
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -3000);
			TS_ASSERT(obj1.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj1.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World!"));
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
			TS_ASSERT(obj1.getAttribute2() == obj2.getAttribute2());
			TS_ASSERT(obj1.getAttribute3() == obj2.getAttribute3());
			TS_ASSERT(obj1.getAttribute4() == obj2.getAttribute4());
			TS_ASSERT_DELTA(obj1.getAttribute5(), obj2.getAttribute5(), 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), obj2.getAttribute6(), 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), obj2.getAttribute7()));
	
			TS_ASSERT(obj2.getAttribute1() == true);
			TS_ASSERT(obj2.getAttribute2() == 'c');
			TS_ASSERT(obj2.getAttribute3() == -3000);
			TS_ASSERT(obj2.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj2.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj2.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute7(), "Hello World!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST12COMPLEX_TESTSUITE_H*/
