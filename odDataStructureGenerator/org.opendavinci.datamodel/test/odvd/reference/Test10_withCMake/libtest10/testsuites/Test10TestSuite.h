/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST10_TESTSUITE_H
#define TEST10_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test10.h"

#include "generated/Test10Point.h"
#include "generated/Test10Point.h"

class Test10_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test10 obj1;
			TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.getListOfMyPointList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyPointList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyPointList());
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.getMapOfMyIntPointMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyIntPointMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyIntPointMap());
	
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
			{
				std::map<int32_t, std::string> myExternalMap;
				myExternalMap[-300] = "Hello World!";
				myExternalMap[-400] = "Hello Solar System!";
				myExternalMap[-500] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyIntStringMap();
				TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			
				obj1.setMapOfMyIntStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-400), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-500));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-500), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyIntStringMap();
				TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			}
			obj1.putTo_MapOfMyIntStringMap(-300, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			
			obj1.putTo_MapOfMyIntStringMap(-400, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-400), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			
			obj1.putTo_MapOfMyIntStringMap(-500, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-400), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-500));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-500), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyIntStringMap(-300) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyIntStringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyIntStringMap(-500) == "Hello Milky Way!");
		}
	
		void testCreateAndCopyObject() {
	
			Test10 obj1;
			TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.getListOfMyPointList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyPointList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyPointList());
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.getMapOfMyIntPointMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyIntPointMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyIntPointMap());
	
			Test10 obj2(obj1);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == obj2.getSize_ListOfMyStringList());
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList() == obj2.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.getSize_ListOfMyPointList() == obj2.getSize_ListOfMyPointList());
			TS_ASSERT(obj1.isEmpty_ListOfMyPointList() == obj2.isEmpty_ListOfMyPointList());
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == obj2.getSize_MapOfMyIntStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap() == obj2.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.getSize_MapOfMyIntPointMap() == obj2.getSize_MapOfMyIntPointMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyIntPointMap() == obj2.isEmpty_MapOfMyIntPointMap());
	
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
			{
				std::map<int32_t, std::string> myExternalMap;
				myExternalMap[-300] = "Hello World!";
				myExternalMap[-400] = "Hello Solar System!";
				myExternalMap[-500] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyIntStringMap();
				TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			
				obj1.setMapOfMyIntStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-400), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-500));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-500), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyIntStringMap();
				TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			}
			obj1.putTo_MapOfMyIntStringMap(-300, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			
			obj1.putTo_MapOfMyIntStringMap(-400, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-400), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			
			obj1.putTo_MapOfMyIntStringMap(-500, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-400), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-500));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-500), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyIntStringMap(-300) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyIntStringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyIntStringMap(-500) == "Hello Milky Way!");
	
			Test10 obj3(obj1);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == obj3.getSize_ListOfMyStringList());
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList() == obj3.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.getSize_ListOfMyPointList() == obj3.getSize_ListOfMyPointList());
			TS_ASSERT(obj1.isEmpty_ListOfMyPointList() == obj3.isEmpty_ListOfMyPointList());
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == obj3.getSize_MapOfMyIntStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap() == obj3.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.getSize_MapOfMyIntPointMap() == obj3.getSize_MapOfMyIntPointMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyIntPointMap() == obj3.isEmpty_MapOfMyIntPointMap());
	
			TS_ASSERT(obj3.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj3.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj3.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj3.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj3.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj3.contains_ListOfMyStringList("Hello Milky Way!"));
			TS_ASSERT(obj3.getMapOfMyIntStringMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyIntStringMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyIntStringMap(-300) == "Hello World!");
			TS_ASSERT(obj3.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(obj3.getValueForKey_MapOfMyIntStringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj3.containsKey_MapOfMyIntStringMap(-500));
			TS_ASSERT(obj3.getValueForKey_MapOfMyIntStringMap(-500) == "Hello Milky Way!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test10 obj1;
			TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.getListOfMyPointList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyPointList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyPointList());
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.getMapOfMyIntPointMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyIntPointMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyIntPointMap());
	
			Test10 obj2;
			TS_ASSERT(obj2.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj2.getListOfMyPointList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyPointList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyPointList());
			TS_ASSERT(obj2.getMapOfMyIntStringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyIntStringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj2.getMapOfMyIntPointMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyIntPointMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyIntPointMap());
	
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
			{
				std::map<int32_t, std::string> myExternalMap;
				myExternalMap[-300] = "Hello World!";
				myExternalMap[-400] = "Hello Solar System!";
				myExternalMap[-500] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyIntStringMap();
				TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			
				obj1.setMapOfMyIntStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-400), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-500));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-500), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyIntStringMap();
				TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			}
			obj1.putTo_MapOfMyIntStringMap(-300, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			
			obj1.putTo_MapOfMyIntStringMap(-400, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-400), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			
			obj1.putTo_MapOfMyIntStringMap(-500, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-400), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-500));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-500), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyIntStringMap(-300) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyIntStringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyIntStringMap(-500) == "Hello Milky Way!");
	
			obj2 = obj1;
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == obj2.getSize_ListOfMyStringList());
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList() == obj2.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.getSize_ListOfMyPointList() == obj2.getSize_ListOfMyPointList());
			TS_ASSERT(obj1.isEmpty_ListOfMyPointList() == obj2.isEmpty_ListOfMyPointList());
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == obj2.getSize_MapOfMyIntStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap() == obj2.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.getSize_MapOfMyIntPointMap() == obj2.getSize_MapOfMyIntPointMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyIntPointMap() == obj2.isEmpty_MapOfMyIntPointMap());
	
			TS_ASSERT(obj2.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello Milky Way!"));
			TS_ASSERT(obj2.getMapOfMyIntStringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyIntStringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyIntStringMap(-300) == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(obj2.getValueForKey_MapOfMyIntStringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyIntStringMap(-500));
			TS_ASSERT(obj2.getValueForKey_MapOfMyIntStringMap(-500) == "Hello Milky Way!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test10 obj1;
			TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.getListOfMyPointList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyPointList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyPointList());
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.getMapOfMyIntPointMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyIntPointMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyIntPointMap());
	
			Test10 obj2;
			TS_ASSERT(obj2.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj2.getListOfMyPointList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyPointList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyPointList());
			TS_ASSERT(obj2.getMapOfMyIntStringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyIntStringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj2.getMapOfMyIntPointMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyIntPointMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyIntPointMap());
	
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
			{
				std::map<int32_t, std::string> myExternalMap;
				myExternalMap[-300] = "Hello World!";
				myExternalMap[-400] = "Hello Solar System!";
				myExternalMap[-500] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyIntStringMap();
				TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			
				obj1.setMapOfMyIntStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-400), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-500));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-500), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyIntStringMap();
				TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			}
			obj1.putTo_MapOfMyIntStringMap(-300, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			
			obj1.putTo_MapOfMyIntStringMap(-400, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-400), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyIntStringMap(-500));
			
			obj1.putTo_MapOfMyIntStringMap(-500, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-400), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-500));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyIntStringMap(-500), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
			TS_ASSERT(obj1.getMapOfMyIntStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyIntStringMap(-300) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyIntStringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyIntStringMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyIntStringMap(-500) == "Hello Milky Way!");
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == obj2.getSize_ListOfMyStringList());
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList() == obj2.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.getSize_ListOfMyPointList() == obj2.getSize_ListOfMyPointList());
			TS_ASSERT(obj1.isEmpty_ListOfMyPointList() == obj2.isEmpty_ListOfMyPointList());
			TS_ASSERT(obj1.getSize_MapOfMyIntStringMap() == obj2.getSize_MapOfMyIntStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyIntStringMap() == obj2.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj1.getSize_MapOfMyIntPointMap() == obj2.getSize_MapOfMyIntPointMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyIntPointMap() == obj2.isEmpty_MapOfMyIntPointMap());
	
			TS_ASSERT(obj2.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello Milky Way!"));
			TS_ASSERT(obj2.getMapOfMyIntStringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyIntStringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyIntStringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyIntStringMap(-300) == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyIntStringMap(-400));
			TS_ASSERT(obj2.getValueForKey_MapOfMyIntStringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyIntStringMap(-500));
			TS_ASSERT(obj2.getValueForKey_MapOfMyIntStringMap(-500) == "Hello Milky Way!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST10_TESTSUITE_H*/
