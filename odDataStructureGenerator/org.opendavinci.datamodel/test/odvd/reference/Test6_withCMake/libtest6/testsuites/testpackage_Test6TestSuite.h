/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TESTPACKAGE_TEST6_TESTSUITE_H
#define TESTPACKAGE_TEST6_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/strings/StringToolbox.h"

#include "test6/GeneratedHeaders_Test6.h"


class testpackage_Test6_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
			using namespace testpackage;
	
			Test6 obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -12);
			TS_ASSERT(obj1.getAttribute4() == +45);
			TS_ASSERT_DELTA(obj1.getAttribute5(), -0.12, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), +0.45678, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World."));
			TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
	
			obj1.setAttribute1(true);
			obj1.setAttribute2('c');
			obj1.setAttribute3(-3000);
			obj1.setAttribute4(4000);
			obj1.setAttribute5(2.5);
			obj1.setAttribute6(1.0);
			obj1.setAttribute7("Hello World!");
			{
				std::vector<std::string> myExternalList;
				myExternalList.push_back("Hello World!");
				myExternalList.push_back("Hello Solar System!");
				myExternalList.push_back("Hello Milky Way!");
			
				obj1.clear_ListOfMyStringList();
				TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello World!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Solar System!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
				obj1.setListOfMyStringList(myExternalList);
				TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
				TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
				TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
				TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
				obj1.clear_ListOfMyStringList();
				TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello World!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Solar System!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			}
			obj1.addTo_ListOfMyStringList("Hello World!");
			TS_ASSERT(obj1.getListOfMyStringList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
			obj1.addTo_ListOfMyStringList("Hello Solar System!");
			TS_ASSERT(obj1.getListOfMyStringList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
			obj1.insertTo_ListOfMyStringList("Hello Milky Way!");
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
	
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -3000);
			TS_ASSERT(obj1.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj1.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World!"));
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
		}
	
		void testCreateAndCopyObject() {
			using namespace testpackage;
	
			Test6 obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -12);
			TS_ASSERT(obj1.getAttribute4() == +45);
			TS_ASSERT_DELTA(obj1.getAttribute5(), -0.12, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), +0.45678, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World."));
			TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
	
			Test6 obj2(obj1);
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
			TS_ASSERT(obj1.getAttribute2() == obj2.getAttribute2());
			TS_ASSERT(obj1.getAttribute3() == obj2.getAttribute3());
			TS_ASSERT(obj1.getAttribute4() == obj2.getAttribute4());
			TS_ASSERT_DELTA(obj1.getAttribute5(), obj2.getAttribute5(), 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), obj2.getAttribute6(), 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), obj2.getAttribute7()));
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == obj2.getSize_ListOfMyStringList());
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList() == obj2.isEmpty_ListOfMyStringList());
	
			obj1.setAttribute1(true);
			obj1.setAttribute2('c');
			obj1.setAttribute3(-3000);
			obj1.setAttribute4(4000);
			obj1.setAttribute5(2.5);
			obj1.setAttribute6(1.0);
			obj1.setAttribute7("Hello World!");
			{
				std::vector<std::string> myExternalList;
				myExternalList.push_back("Hello World!");
				myExternalList.push_back("Hello Solar System!");
				myExternalList.push_back("Hello Milky Way!");
			
				obj1.clear_ListOfMyStringList();
				TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello World!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Solar System!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
				obj1.setListOfMyStringList(myExternalList);
				TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
				TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
				TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
				TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
				obj1.clear_ListOfMyStringList();
				TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello World!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Solar System!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			}
			obj1.addTo_ListOfMyStringList("Hello World!");
			TS_ASSERT(obj1.getListOfMyStringList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
			obj1.addTo_ListOfMyStringList("Hello Solar System!");
			TS_ASSERT(obj1.getListOfMyStringList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
			obj1.insertTo_ListOfMyStringList("Hello Milky Way!");
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
	
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -3000);
			TS_ASSERT(obj1.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj1.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World!"));
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
	
			Test6 obj3(obj1);
			TS_ASSERT(obj1.getAttribute1() == obj3.getAttribute1());
			TS_ASSERT(obj1.getAttribute2() == obj3.getAttribute2());
			TS_ASSERT(obj1.getAttribute3() == obj3.getAttribute3());
			TS_ASSERT(obj1.getAttribute4() == obj3.getAttribute4());
			TS_ASSERT_DELTA(obj1.getAttribute5(), obj3.getAttribute5(), 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), obj3.getAttribute6(), 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), obj3.getAttribute7()));
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == obj3.getSize_ListOfMyStringList());
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList() == obj3.isEmpty_ListOfMyStringList());
	
			TS_ASSERT(obj3.getAttribute1() == true);
			TS_ASSERT(obj3.getAttribute2() == 'c');
			TS_ASSERT(obj3.getAttribute3() == -3000);
			TS_ASSERT(obj3.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj3.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj3.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj3.getAttribute7(), "Hello World!"));
			TS_ASSERT(obj3.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj3.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj3.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj3.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj3.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj3.contains_ListOfMyStringList("Hello Milky Way!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
			using namespace testpackage;
	
			Test6 obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -12);
			TS_ASSERT(obj1.getAttribute4() == +45);
			TS_ASSERT_DELTA(obj1.getAttribute5(), -0.12, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), +0.45678, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World."));
			TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
	
			Test6 obj2;
			TS_ASSERT(obj2.getAttribute1() == true);
			TS_ASSERT(obj2.getAttribute2() == 'c');
			TS_ASSERT(obj2.getAttribute3() == -12);
			TS_ASSERT(obj2.getAttribute4() == +45);
			TS_ASSERT_DELTA(obj2.getAttribute5(), -0.12, 1e-5);
			TS_ASSERT_DELTA(obj2.getAttribute6(), +0.45678, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute7(), "Hello World."));
			TS_ASSERT(obj2.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyStringList());
	
			obj1.setAttribute1(true);
			obj1.setAttribute2('c');
			obj1.setAttribute3(-3000);
			obj1.setAttribute4(4000);
			obj1.setAttribute5(2.5);
			obj1.setAttribute6(1.0);
			obj1.setAttribute7("Hello World!");
			{
				std::vector<std::string> myExternalList;
				myExternalList.push_back("Hello World!");
				myExternalList.push_back("Hello Solar System!");
				myExternalList.push_back("Hello Milky Way!");
			
				obj1.clear_ListOfMyStringList();
				TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello World!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Solar System!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
				obj1.setListOfMyStringList(myExternalList);
				TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
				TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
				TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
				TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
				obj1.clear_ListOfMyStringList();
				TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello World!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Solar System!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			}
			obj1.addTo_ListOfMyStringList("Hello World!");
			TS_ASSERT(obj1.getListOfMyStringList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
			obj1.addTo_ListOfMyStringList("Hello Solar System!");
			TS_ASSERT(obj1.getListOfMyStringList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
			obj1.insertTo_ListOfMyStringList("Hello Milky Way!");
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
	
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -3000);
			TS_ASSERT(obj1.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj1.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World!"));
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
	
			obj2 = obj1;
			TS_ASSERT(obj1.getAttribute1() == obj2.getAttribute1());
			TS_ASSERT(obj1.getAttribute2() == obj2.getAttribute2());
			TS_ASSERT(obj1.getAttribute3() == obj2.getAttribute3());
			TS_ASSERT(obj1.getAttribute4() == obj2.getAttribute4());
			TS_ASSERT_DELTA(obj1.getAttribute5(), obj2.getAttribute5(), 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), obj2.getAttribute6(), 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), obj2.getAttribute7()));
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == obj2.getSize_ListOfMyStringList());
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList() == obj2.isEmpty_ListOfMyStringList());
	
			TS_ASSERT(obj2.getAttribute1() == true);
			TS_ASSERT(obj2.getAttribute2() == 'c');
			TS_ASSERT(obj2.getAttribute3() == -3000);
			TS_ASSERT(obj2.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj2.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj2.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute7(), "Hello World!"));
			TS_ASSERT(obj2.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello Milky Way!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
			using namespace testpackage;
	
			Test6 obj1;
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -12);
			TS_ASSERT(obj1.getAttribute4() == +45);
			TS_ASSERT_DELTA(obj1.getAttribute5(), -0.12, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), +0.45678, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World."));
			TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
	
			Test6 obj2;
			TS_ASSERT(obj2.getAttribute1() == true);
			TS_ASSERT(obj2.getAttribute2() == 'c');
			TS_ASSERT(obj2.getAttribute3() == -12);
			TS_ASSERT(obj2.getAttribute4() == +45);
			TS_ASSERT_DELTA(obj2.getAttribute5(), -0.12, 1e-5);
			TS_ASSERT_DELTA(obj2.getAttribute6(), +0.45678, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute7(), "Hello World."));
			TS_ASSERT(obj2.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyStringList());
	
			obj1.setAttribute1(true);
			obj1.setAttribute2('c');
			obj1.setAttribute3(-3000);
			obj1.setAttribute4(4000);
			obj1.setAttribute5(2.5);
			obj1.setAttribute6(1.0);
			obj1.setAttribute7("Hello World!");
			{
				std::vector<std::string> myExternalList;
				myExternalList.push_back("Hello World!");
				myExternalList.push_back("Hello Solar System!");
				myExternalList.push_back("Hello Milky Way!");
			
				obj1.clear_ListOfMyStringList();
				TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello World!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Solar System!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
				obj1.setListOfMyStringList(myExternalList);
				TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
				TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
				TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
				TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
				obj1.clear_ListOfMyStringList();
				TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello World!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Solar System!"));
				TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			}
			obj1.addTo_ListOfMyStringList("Hello World!");
			TS_ASSERT(obj1.getListOfMyStringList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
			obj1.addTo_ListOfMyStringList("Hello Solar System!");
			TS_ASSERT(obj1.getListOfMyStringList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(!obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			
			obj1.insertTo_ListOfMyStringList("Hello Milky Way!");
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
	
			TS_ASSERT(obj1.getAttribute1() == true);
			TS_ASSERT(obj1.getAttribute2() == 'c');
			TS_ASSERT(obj1.getAttribute3() == -3000);
			TS_ASSERT(obj1.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj1.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj1.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getAttribute7(), "Hello World!"));
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
	
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
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == obj2.getSize_ListOfMyStringList());
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList() == obj2.isEmpty_ListOfMyStringList());
	
			TS_ASSERT(obj2.getAttribute1() == true);
			TS_ASSERT(obj2.getAttribute2() == 'c');
			TS_ASSERT(obj2.getAttribute3() == -3000);
			TS_ASSERT(obj2.getAttribute4() == 4000);
			TS_ASSERT_DELTA(obj2.getAttribute5(), 2.5, 1e-5);
			TS_ASSERT_DELTA(obj2.getAttribute6(), 1.0, 1e-5);
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj2.getAttribute7(), "Hello World!"));
			TS_ASSERT(obj2.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello Milky Way!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TESTPACKAGE_TEST6_TESTSUITE_H*/
