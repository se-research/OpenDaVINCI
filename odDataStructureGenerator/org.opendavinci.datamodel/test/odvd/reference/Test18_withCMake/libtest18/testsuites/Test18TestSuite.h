/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST18_TESTSUITE_H
#define TEST18_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/strings/StringToolbox.h"

#include "test18/GeneratedHeaders_Test18.h"


class Test18_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test18 obj1;
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == 0);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], 0, 1e-5);
			}
			TS_ASSERT(obj1.getMyAtt1() == 0);
			TS_ASSERT(obj1.getMyAtt2() == 0);
			TS_ASSERT(obj1.getMyAtt3() == 0);
	
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				obj1.getMyArray1()[i] = 4000 + i;
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == 4000 + i);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				obj1.getMyArray2()[i] = 2.5 + (1.0+i);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], 2.5 + (1.0+i), 1e-5);
			}
			obj1.setMyAtt1(4000);
			obj1.setMyAtt2(4000);
			obj1.setMyAtt3(4000);
	
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == 4000 + i);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], 2.5 + (1.0+i), 1e-5);
			}
			TS_ASSERT(obj1.getMyAtt1() == 4000);
			TS_ASSERT(obj1.getMyAtt2() == 4000);
			TS_ASSERT(obj1.getMyAtt3() == 4000);
		}
	
		void testCreateAndCopyObject() {
	
			Test18 obj1;
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == 0);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], 0, 1e-5);
			}
			TS_ASSERT(obj1.getMyAtt1() == 0);
			TS_ASSERT(obj1.getMyAtt2() == 0);
			TS_ASSERT(obj1.getMyAtt3() == 0);
	
			Test18 obj2(obj1);
			TS_ASSERT(obj1.getSize_MyArray1() == obj2.getSize_MyArray1());
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == obj2.getMyArray1()[i]);
			}
			TS_ASSERT(obj1.getSize_MyArray2() == obj2.getSize_MyArray2());
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], obj2.getMyArray2()[i], 1e-5);
			}
			TS_ASSERT(obj1.getMyAtt1() == obj2.getMyAtt1());
			TS_ASSERT(obj1.getMyAtt2() == obj2.getMyAtt2());
			TS_ASSERT(obj1.getMyAtt3() == obj2.getMyAtt3());
	
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				obj1.getMyArray1()[i] = 4000 + i;
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == 4000 + i);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				obj1.getMyArray2()[i] = 2.5 + (1.0+i);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], 2.5 + (1.0+i), 1e-5);
			}
			obj1.setMyAtt1(4000);
			obj1.setMyAtt2(4000);
			obj1.setMyAtt3(4000);
	
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == 4000 + i);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], 2.5 + (1.0+i), 1e-5);
			}
			TS_ASSERT(obj1.getMyAtt1() == 4000);
			TS_ASSERT(obj1.getMyAtt2() == 4000);
			TS_ASSERT(obj1.getMyAtt3() == 4000);
	
			Test18 obj3(obj1);
			TS_ASSERT(obj1.getSize_MyArray1() == obj3.getSize_MyArray1());
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == obj3.getMyArray1()[i]);
			}
			TS_ASSERT(obj1.getSize_MyArray2() == obj3.getSize_MyArray2());
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], obj3.getMyArray2()[i], 1e-5);
			}
			TS_ASSERT(obj1.getMyAtt1() == obj3.getMyAtt1());
			TS_ASSERT(obj1.getMyAtt2() == obj3.getMyAtt2());
			TS_ASSERT(obj1.getMyAtt3() == obj3.getMyAtt3());
	
			for(uint32_t i = 0; i < obj3.getSize_MyArray1(); i++) {
				TS_ASSERT(obj3.getMyArray1()[i] == 4000 + i);
			}
			for(uint32_t i = 0; i < obj3.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj3.getMyArray2()[i], 2.5 + (1.0+i), 1e-5);
			}
			TS_ASSERT(obj3.getMyAtt1() == 4000);
			TS_ASSERT(obj3.getMyAtt2() == 4000);
			TS_ASSERT(obj3.getMyAtt3() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test18 obj1;
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == 0);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], 0, 1e-5);
			}
			TS_ASSERT(obj1.getMyAtt1() == 0);
			TS_ASSERT(obj1.getMyAtt2() == 0);
			TS_ASSERT(obj1.getMyAtt3() == 0);
	
			Test18 obj2;
			for(uint32_t i = 0; i < obj2.getSize_MyArray1(); i++) {
				TS_ASSERT(obj2.getMyArray1()[i] == 0);
			}
			for(uint32_t i = 0; i < obj2.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj2.getMyArray2()[i], 0, 1e-5);
			}
			TS_ASSERT(obj2.getMyAtt1() == 0);
			TS_ASSERT(obj2.getMyAtt2() == 0);
			TS_ASSERT(obj2.getMyAtt3() == 0);
	
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				obj1.getMyArray1()[i] = 4000 + i;
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == 4000 + i);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				obj1.getMyArray2()[i] = 2.5 + (1.0+i);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], 2.5 + (1.0+i), 1e-5);
			}
			obj1.setMyAtt1(4000);
			obj1.setMyAtt2(4000);
			obj1.setMyAtt3(4000);
	
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == 4000 + i);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], 2.5 + (1.0+i), 1e-5);
			}
			TS_ASSERT(obj1.getMyAtt1() == 4000);
			TS_ASSERT(obj1.getMyAtt2() == 4000);
			TS_ASSERT(obj1.getMyAtt3() == 4000);
	
			obj2 = obj1;
			TS_ASSERT(obj1.getSize_MyArray1() == obj2.getSize_MyArray1());
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == obj2.getMyArray1()[i]);
			}
			TS_ASSERT(obj1.getSize_MyArray2() == obj2.getSize_MyArray2());
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], obj2.getMyArray2()[i], 1e-5);
			}
			TS_ASSERT(obj1.getMyAtt1() == obj2.getMyAtt1());
			TS_ASSERT(obj1.getMyAtt2() == obj2.getMyAtt2());
			TS_ASSERT(obj1.getMyAtt3() == obj2.getMyAtt3());
	
			for(uint32_t i = 0; i < obj2.getSize_MyArray1(); i++) {
				TS_ASSERT(obj2.getMyArray1()[i] == 4000 + i);
			}
			for(uint32_t i = 0; i < obj2.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj2.getMyArray2()[i], 2.5 + (1.0+i), 1e-5);
			}
			TS_ASSERT(obj2.getMyAtt1() == 4000);
			TS_ASSERT(obj2.getMyAtt2() == 4000);
			TS_ASSERT(obj2.getMyAtt3() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test18 obj1;
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == 0);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], 0, 1e-5);
			}
			TS_ASSERT(obj1.getMyAtt1() == 0);
			TS_ASSERT(obj1.getMyAtt2() == 0);
			TS_ASSERT(obj1.getMyAtt3() == 0);
	
			Test18 obj2;
			for(uint32_t i = 0; i < obj2.getSize_MyArray1(); i++) {
				TS_ASSERT(obj2.getMyArray1()[i] == 0);
			}
			for(uint32_t i = 0; i < obj2.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj2.getMyArray2()[i], 0, 1e-5);
			}
			TS_ASSERT(obj2.getMyAtt1() == 0);
			TS_ASSERT(obj2.getMyAtt2() == 0);
			TS_ASSERT(obj2.getMyAtt3() == 0);
	
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				obj1.getMyArray1()[i] = 4000 + i;
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == 4000 + i);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				obj1.getMyArray2()[i] = 2.5 + (1.0+i);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], 2.5 + (1.0+i), 1e-5);
			}
			obj1.setMyAtt1(4000);
			obj1.setMyAtt2(4000);
			obj1.setMyAtt3(4000);
	
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == 4000 + i);
			}
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], 2.5 + (1.0+i), 1e-5);
			}
			TS_ASSERT(obj1.getMyAtt1() == 4000);
			TS_ASSERT(obj1.getMyAtt2() == 4000);
			TS_ASSERT(obj1.getMyAtt3() == 4000);
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getSize_MyArray1() == obj2.getSize_MyArray1());
			for(uint32_t i = 0; i < obj1.getSize_MyArray1(); i++) {
				TS_ASSERT(obj1.getMyArray1()[i] == obj2.getMyArray1()[i]);
			}
			TS_ASSERT(obj1.getSize_MyArray2() == obj2.getSize_MyArray2());
			for(uint32_t i = 0; i < obj1.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj1.getMyArray2()[i], obj2.getMyArray2()[i], 1e-5);
			}
			TS_ASSERT(obj1.getMyAtt1() == obj2.getMyAtt1());
			TS_ASSERT(obj1.getMyAtt2() == obj2.getMyAtt2());
			TS_ASSERT(obj1.getMyAtt3() == obj2.getMyAtt3());
	
			for(uint32_t i = 0; i < obj2.getSize_MyArray1(); i++) {
				TS_ASSERT(obj2.getMyArray1()[i] == 4000 + i);
			}
			for(uint32_t i = 0; i < obj2.getSize_MyArray2(); i++) {
				TS_ASSERT_DELTA(obj2.getMyArray2()[i], 2.5 + (1.0+i), 1e-5);
			}
			TS_ASSERT(obj2.getMyAtt1() == 4000);
			TS_ASSERT(obj2.getMyAtt2() == 4000);
			TS_ASSERT(obj2.getMyAtt3() == 4000);
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST18_TESTSUITE_H*/
