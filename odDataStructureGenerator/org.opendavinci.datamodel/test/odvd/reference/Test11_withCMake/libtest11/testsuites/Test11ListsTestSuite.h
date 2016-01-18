/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST11LISTS_TESTSUITE_H
#define TEST11LISTS_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/strings/StringToolbox.h"

#include "test11/GeneratedHeaders_Test11.h"


class Test11Lists_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test11Lists obj1;
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.getListOfMyCharList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
	
			{
				std::vector<bool> myExternalList;
				myExternalList.push_back(true);
				myExternalList.push_back(false);
			
				obj1.clear_ListOfMyBoolList();
				TS_ASSERT(obj1.getListOfMyBoolList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyBoolList());
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(true));
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(false));
			
				obj1.setListOfMyBoolList(myExternalList);
				TS_ASSERT(obj1.getListOfMyBoolList().size() == 2);
				TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 2);
				TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
				TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
				TS_ASSERT(obj1.contains_ListOfMyBoolList(false));
			
				obj1.clear_ListOfMyBoolList();
				TS_ASSERT(obj1.getListOfMyBoolList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyBoolList());
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(true));
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(false));
			}
			obj1.addTo_ListOfMyBoolList(true);
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
			TS_ASSERT(!obj1.contains_ListOfMyBoolList(false));
			
			obj1.addTo_ListOfMyBoolList(false);
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
			TS_ASSERT(obj1.contains_ListOfMyBoolList(false));
			
			{
				std::vector<char> myExternalList;
				myExternalList.push_back('d');
				myExternalList.push_back('e');
				myExternalList.push_back('f');
			
				obj1.clear_ListOfMyCharList();
				TS_ASSERT(obj1.getListOfMyCharList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyCharList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyCharList());
				TS_ASSERT(!obj1.contains_ListOfMyCharList('d'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('e'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			
				obj1.setListOfMyCharList(myExternalList);
				TS_ASSERT(obj1.getListOfMyCharList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyCharList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
				TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
				TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
				TS_ASSERT(obj1.contains_ListOfMyCharList('f'));
			
				obj1.clear_ListOfMyCharList();
				TS_ASSERT(obj1.getListOfMyCharList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyCharList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyCharList());
				TS_ASSERT(!obj1.contains_ListOfMyCharList('d'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('e'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			}
			obj1.addTo_ListOfMyCharList('d');
			TS_ASSERT(obj1.getListOfMyCharList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(!obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			
			obj1.addTo_ListOfMyCharList('e');
			TS_ASSERT(obj1.getListOfMyCharList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			
			obj1.insertTo_ListOfMyCharList('f');
			TS_ASSERT(obj1.getListOfMyCharList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('f'));
			{
				std::vector<int32_t> myExternalList;
				myExternalList.push_back(-300);
				myExternalList.push_back(-400);
				myExternalList.push_back(-500);
			
				obj1.clear_ListOfMyInt32List();
				TS_ASSERT(obj1.getListOfMyInt32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyInt32List());
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-300));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-400));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			
				obj1.setListOfMyInt32List(myExternalList);
				TS_ASSERT(obj1.getListOfMyInt32List().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
				TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
				TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
				TS_ASSERT(obj1.contains_ListOfMyInt32List(-500));
			
				obj1.clear_ListOfMyInt32List();
				TS_ASSERT(obj1.getListOfMyInt32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyInt32List());
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-300));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-400));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			}
			obj1.addTo_ListOfMyInt32List(-300);
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(!obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			
			obj1.addTo_ListOfMyInt32List(-400);
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			
			obj1.insertTo_ListOfMyInt32List(-500);
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-500));
			{
				std::vector<uint32_t> myExternalList;
				myExternalList.push_back(600);
				myExternalList.push_back(700);
				myExternalList.push_back(800);
			
				obj1.clear_ListOfMyUint32List();
				TS_ASSERT(obj1.getListOfMyUint32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyUint32List());
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(600));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(700));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			
				obj1.setListOfMyUint32List(myExternalList);
				TS_ASSERT(obj1.getListOfMyUint32List().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
				TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
				TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
				TS_ASSERT(obj1.contains_ListOfMyUint32List(800));
			
				obj1.clear_ListOfMyUint32List();
				TS_ASSERT(obj1.getListOfMyUint32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyUint32List());
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(600));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(700));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			}
			obj1.addTo_ListOfMyUint32List(600);
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(!obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			
			obj1.addTo_ListOfMyUint32List(700);
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			
			obj1.insertTo_ListOfMyUint32List(800);
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(800));
			{
				std::vector<float> myExternalList;
				myExternalList.push_back(4.5);
				myExternalList.push_back(5.5);
				myExternalList.push_back(6.5);
			
				obj1.clear_ListOfMyFloatList();
				TS_ASSERT(obj1.getListOfMyFloatList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyFloatList());
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(4.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(5.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			
				obj1.setListOfMyFloatList(myExternalList);
				TS_ASSERT(obj1.getListOfMyFloatList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
				TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
				TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
				TS_ASSERT(obj1.contains_ListOfMyFloatList(6.5));
			
				obj1.clear_ListOfMyFloatList();
				TS_ASSERT(obj1.getListOfMyFloatList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyFloatList());
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(4.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(5.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			}
			obj1.addTo_ListOfMyFloatList(4.5);
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(!obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			
			obj1.addTo_ListOfMyFloatList(5.5);
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			
			obj1.insertTo_ListOfMyFloatList(6.5);
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(6.5));
			{
				std::vector<double> myExternalList;
				myExternalList.push_back(1.0);
				myExternalList.push_back(2.0);
				myExternalList.push_back(3.0);
			
				obj1.clear_ListOfMyDoubleList();
				TS_ASSERT(obj1.getListOfMyDoubleList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList());
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(1.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(2.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			
				obj1.setListOfMyDoubleList(myExternalList);
				TS_ASSERT(obj1.getListOfMyDoubleList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
				TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
				TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
				TS_ASSERT(obj1.contains_ListOfMyDoubleList(3.0));
			
				obj1.clear_ListOfMyDoubleList();
				TS_ASSERT(obj1.getListOfMyDoubleList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList());
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(1.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(2.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			}
			obj1.addTo_ListOfMyDoubleList(1.0);
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(!obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			
			obj1.addTo_ListOfMyDoubleList(2.0);
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			
			obj1.insertTo_ListOfMyDoubleList(3.0);
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(3.0));
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
	
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
			TS_ASSERT(obj1.contains_ListOfMyBoolList(false));
			TS_ASSERT(obj1.getListOfMyCharList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('f'));
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-500));
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(800));
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(6.5));
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(3.0));
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
		}
	
		void testCreateAndCopyObject() {
	
			Test11Lists obj1;
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.getListOfMyCharList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
	
			Test11Lists obj2(obj1);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == obj2.getSize_ListOfMyBoolList());
			TS_ASSERT(obj1.isEmpty_ListOfMyBoolList() == obj2.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == obj2.getSize_ListOfMyCharList());
			TS_ASSERT(obj1.isEmpty_ListOfMyCharList() == obj2.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == obj2.getSize_ListOfMyInt32List());
			TS_ASSERT(obj1.isEmpty_ListOfMyInt32List() == obj2.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == obj2.getSize_ListOfMyUint32List());
			TS_ASSERT(obj1.isEmpty_ListOfMyUint32List() == obj2.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == obj2.getSize_ListOfMyFloatList());
			TS_ASSERT(obj1.isEmpty_ListOfMyFloatList() == obj2.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == obj2.getSize_ListOfMyDoubleList());
			TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList() == obj2.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == obj2.getSize_ListOfMyStringList());
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList() == obj2.isEmpty_ListOfMyStringList());
	
			{
				std::vector<bool> myExternalList;
				myExternalList.push_back(true);
				myExternalList.push_back(false);
			
				obj1.clear_ListOfMyBoolList();
				TS_ASSERT(obj1.getListOfMyBoolList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyBoolList());
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(true));
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(false));
			
				obj1.setListOfMyBoolList(myExternalList);
				TS_ASSERT(obj1.getListOfMyBoolList().size() == 2);
				TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 2);
				TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
				TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
				TS_ASSERT(obj1.contains_ListOfMyBoolList(false));
			
				obj1.clear_ListOfMyBoolList();
				TS_ASSERT(obj1.getListOfMyBoolList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyBoolList());
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(true));
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(false));
			}
			obj1.addTo_ListOfMyBoolList(true);
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
			TS_ASSERT(!obj1.contains_ListOfMyBoolList(false));
			
			obj1.addTo_ListOfMyBoolList(false);
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
			TS_ASSERT(obj1.contains_ListOfMyBoolList(false));
			
			{
				std::vector<char> myExternalList;
				myExternalList.push_back('d');
				myExternalList.push_back('e');
				myExternalList.push_back('f');
			
				obj1.clear_ListOfMyCharList();
				TS_ASSERT(obj1.getListOfMyCharList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyCharList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyCharList());
				TS_ASSERT(!obj1.contains_ListOfMyCharList('d'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('e'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			
				obj1.setListOfMyCharList(myExternalList);
				TS_ASSERT(obj1.getListOfMyCharList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyCharList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
				TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
				TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
				TS_ASSERT(obj1.contains_ListOfMyCharList('f'));
			
				obj1.clear_ListOfMyCharList();
				TS_ASSERT(obj1.getListOfMyCharList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyCharList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyCharList());
				TS_ASSERT(!obj1.contains_ListOfMyCharList('d'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('e'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			}
			obj1.addTo_ListOfMyCharList('d');
			TS_ASSERT(obj1.getListOfMyCharList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(!obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			
			obj1.addTo_ListOfMyCharList('e');
			TS_ASSERT(obj1.getListOfMyCharList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			
			obj1.insertTo_ListOfMyCharList('f');
			TS_ASSERT(obj1.getListOfMyCharList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('f'));
			{
				std::vector<int32_t> myExternalList;
				myExternalList.push_back(-300);
				myExternalList.push_back(-400);
				myExternalList.push_back(-500);
			
				obj1.clear_ListOfMyInt32List();
				TS_ASSERT(obj1.getListOfMyInt32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyInt32List());
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-300));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-400));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			
				obj1.setListOfMyInt32List(myExternalList);
				TS_ASSERT(obj1.getListOfMyInt32List().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
				TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
				TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
				TS_ASSERT(obj1.contains_ListOfMyInt32List(-500));
			
				obj1.clear_ListOfMyInt32List();
				TS_ASSERT(obj1.getListOfMyInt32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyInt32List());
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-300));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-400));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			}
			obj1.addTo_ListOfMyInt32List(-300);
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(!obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			
			obj1.addTo_ListOfMyInt32List(-400);
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			
			obj1.insertTo_ListOfMyInt32List(-500);
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-500));
			{
				std::vector<uint32_t> myExternalList;
				myExternalList.push_back(600);
				myExternalList.push_back(700);
				myExternalList.push_back(800);
			
				obj1.clear_ListOfMyUint32List();
				TS_ASSERT(obj1.getListOfMyUint32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyUint32List());
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(600));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(700));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			
				obj1.setListOfMyUint32List(myExternalList);
				TS_ASSERT(obj1.getListOfMyUint32List().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
				TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
				TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
				TS_ASSERT(obj1.contains_ListOfMyUint32List(800));
			
				obj1.clear_ListOfMyUint32List();
				TS_ASSERT(obj1.getListOfMyUint32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyUint32List());
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(600));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(700));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			}
			obj1.addTo_ListOfMyUint32List(600);
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(!obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			
			obj1.addTo_ListOfMyUint32List(700);
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			
			obj1.insertTo_ListOfMyUint32List(800);
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(800));
			{
				std::vector<float> myExternalList;
				myExternalList.push_back(4.5);
				myExternalList.push_back(5.5);
				myExternalList.push_back(6.5);
			
				obj1.clear_ListOfMyFloatList();
				TS_ASSERT(obj1.getListOfMyFloatList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyFloatList());
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(4.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(5.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			
				obj1.setListOfMyFloatList(myExternalList);
				TS_ASSERT(obj1.getListOfMyFloatList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
				TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
				TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
				TS_ASSERT(obj1.contains_ListOfMyFloatList(6.5));
			
				obj1.clear_ListOfMyFloatList();
				TS_ASSERT(obj1.getListOfMyFloatList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyFloatList());
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(4.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(5.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			}
			obj1.addTo_ListOfMyFloatList(4.5);
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(!obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			
			obj1.addTo_ListOfMyFloatList(5.5);
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			
			obj1.insertTo_ListOfMyFloatList(6.5);
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(6.5));
			{
				std::vector<double> myExternalList;
				myExternalList.push_back(1.0);
				myExternalList.push_back(2.0);
				myExternalList.push_back(3.0);
			
				obj1.clear_ListOfMyDoubleList();
				TS_ASSERT(obj1.getListOfMyDoubleList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList());
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(1.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(2.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			
				obj1.setListOfMyDoubleList(myExternalList);
				TS_ASSERT(obj1.getListOfMyDoubleList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
				TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
				TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
				TS_ASSERT(obj1.contains_ListOfMyDoubleList(3.0));
			
				obj1.clear_ListOfMyDoubleList();
				TS_ASSERT(obj1.getListOfMyDoubleList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList());
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(1.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(2.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			}
			obj1.addTo_ListOfMyDoubleList(1.0);
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(!obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			
			obj1.addTo_ListOfMyDoubleList(2.0);
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			
			obj1.insertTo_ListOfMyDoubleList(3.0);
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(3.0));
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
	
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
			TS_ASSERT(obj1.contains_ListOfMyBoolList(false));
			TS_ASSERT(obj1.getListOfMyCharList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('f'));
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-500));
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(800));
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(6.5));
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(3.0));
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
	
			Test11Lists obj3(obj1);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == obj3.getSize_ListOfMyBoolList());
			TS_ASSERT(obj1.isEmpty_ListOfMyBoolList() == obj3.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == obj3.getSize_ListOfMyCharList());
			TS_ASSERT(obj1.isEmpty_ListOfMyCharList() == obj3.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == obj3.getSize_ListOfMyInt32List());
			TS_ASSERT(obj1.isEmpty_ListOfMyInt32List() == obj3.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == obj3.getSize_ListOfMyUint32List());
			TS_ASSERT(obj1.isEmpty_ListOfMyUint32List() == obj3.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == obj3.getSize_ListOfMyFloatList());
			TS_ASSERT(obj1.isEmpty_ListOfMyFloatList() == obj3.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == obj3.getSize_ListOfMyDoubleList());
			TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList() == obj3.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == obj3.getSize_ListOfMyStringList());
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList() == obj3.isEmpty_ListOfMyStringList());
	
			TS_ASSERT(obj3.getListOfMyBoolList().size() == 2);
			TS_ASSERT(obj3.getSize_ListOfMyBoolList() == 2);
			TS_ASSERT(!obj3.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj3.contains_ListOfMyBoolList(true));
			TS_ASSERT(obj3.contains_ListOfMyBoolList(false));
			TS_ASSERT(obj3.getListOfMyCharList().size() == 3);
			TS_ASSERT(obj3.getSize_ListOfMyCharList() == 3);
			TS_ASSERT(!obj3.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj3.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj3.contains_ListOfMyCharList('e'));
			TS_ASSERT(obj3.contains_ListOfMyCharList('f'));
			TS_ASSERT(obj3.getListOfMyInt32List().size() == 3);
			TS_ASSERT(obj3.getSize_ListOfMyInt32List() == 3);
			TS_ASSERT(!obj3.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj3.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj3.contains_ListOfMyInt32List(-400));
			TS_ASSERT(obj3.contains_ListOfMyInt32List(-500));
			TS_ASSERT(obj3.getListOfMyUint32List().size() == 3);
			TS_ASSERT(obj3.getSize_ListOfMyUint32List() == 3);
			TS_ASSERT(!obj3.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj3.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj3.contains_ListOfMyUint32List(700));
			TS_ASSERT(obj3.contains_ListOfMyUint32List(800));
			TS_ASSERT(obj3.getListOfMyFloatList().size() == 3);
			TS_ASSERT(obj3.getSize_ListOfMyFloatList() == 3);
			TS_ASSERT(!obj3.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj3.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj3.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(obj3.contains_ListOfMyFloatList(6.5));
			TS_ASSERT(obj3.getListOfMyDoubleList().size() == 3);
			TS_ASSERT(obj3.getSize_ListOfMyDoubleList() == 3);
			TS_ASSERT(!obj3.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj3.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj3.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(obj3.contains_ListOfMyDoubleList(3.0));
			TS_ASSERT(obj3.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj3.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj3.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj3.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj3.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj3.contains_ListOfMyStringList("Hello Milky Way!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test11Lists obj1;
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.getListOfMyCharList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
	
			Test11Lists obj2;
			TS_ASSERT(obj2.getListOfMyBoolList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyBoolList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj2.getListOfMyCharList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyCharList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj2.getListOfMyInt32List().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyInt32List() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj2.getListOfMyUint32List().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyUint32List() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj2.getListOfMyFloatList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyFloatList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj2.getListOfMyDoubleList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyDoubleList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj2.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyStringList());
	
			{
				std::vector<bool> myExternalList;
				myExternalList.push_back(true);
				myExternalList.push_back(false);
			
				obj1.clear_ListOfMyBoolList();
				TS_ASSERT(obj1.getListOfMyBoolList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyBoolList());
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(true));
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(false));
			
				obj1.setListOfMyBoolList(myExternalList);
				TS_ASSERT(obj1.getListOfMyBoolList().size() == 2);
				TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 2);
				TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
				TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
				TS_ASSERT(obj1.contains_ListOfMyBoolList(false));
			
				obj1.clear_ListOfMyBoolList();
				TS_ASSERT(obj1.getListOfMyBoolList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyBoolList());
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(true));
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(false));
			}
			obj1.addTo_ListOfMyBoolList(true);
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
			TS_ASSERT(!obj1.contains_ListOfMyBoolList(false));
			
			obj1.addTo_ListOfMyBoolList(false);
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
			TS_ASSERT(obj1.contains_ListOfMyBoolList(false));
			
			{
				std::vector<char> myExternalList;
				myExternalList.push_back('d');
				myExternalList.push_back('e');
				myExternalList.push_back('f');
			
				obj1.clear_ListOfMyCharList();
				TS_ASSERT(obj1.getListOfMyCharList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyCharList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyCharList());
				TS_ASSERT(!obj1.contains_ListOfMyCharList('d'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('e'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			
				obj1.setListOfMyCharList(myExternalList);
				TS_ASSERT(obj1.getListOfMyCharList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyCharList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
				TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
				TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
				TS_ASSERT(obj1.contains_ListOfMyCharList('f'));
			
				obj1.clear_ListOfMyCharList();
				TS_ASSERT(obj1.getListOfMyCharList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyCharList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyCharList());
				TS_ASSERT(!obj1.contains_ListOfMyCharList('d'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('e'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			}
			obj1.addTo_ListOfMyCharList('d');
			TS_ASSERT(obj1.getListOfMyCharList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(!obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			
			obj1.addTo_ListOfMyCharList('e');
			TS_ASSERT(obj1.getListOfMyCharList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			
			obj1.insertTo_ListOfMyCharList('f');
			TS_ASSERT(obj1.getListOfMyCharList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('f'));
			{
				std::vector<int32_t> myExternalList;
				myExternalList.push_back(-300);
				myExternalList.push_back(-400);
				myExternalList.push_back(-500);
			
				obj1.clear_ListOfMyInt32List();
				TS_ASSERT(obj1.getListOfMyInt32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyInt32List());
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-300));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-400));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			
				obj1.setListOfMyInt32List(myExternalList);
				TS_ASSERT(obj1.getListOfMyInt32List().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
				TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
				TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
				TS_ASSERT(obj1.contains_ListOfMyInt32List(-500));
			
				obj1.clear_ListOfMyInt32List();
				TS_ASSERT(obj1.getListOfMyInt32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyInt32List());
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-300));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-400));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			}
			obj1.addTo_ListOfMyInt32List(-300);
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(!obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			
			obj1.addTo_ListOfMyInt32List(-400);
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			
			obj1.insertTo_ListOfMyInt32List(-500);
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-500));
			{
				std::vector<uint32_t> myExternalList;
				myExternalList.push_back(600);
				myExternalList.push_back(700);
				myExternalList.push_back(800);
			
				obj1.clear_ListOfMyUint32List();
				TS_ASSERT(obj1.getListOfMyUint32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyUint32List());
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(600));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(700));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			
				obj1.setListOfMyUint32List(myExternalList);
				TS_ASSERT(obj1.getListOfMyUint32List().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
				TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
				TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
				TS_ASSERT(obj1.contains_ListOfMyUint32List(800));
			
				obj1.clear_ListOfMyUint32List();
				TS_ASSERT(obj1.getListOfMyUint32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyUint32List());
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(600));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(700));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			}
			obj1.addTo_ListOfMyUint32List(600);
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(!obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			
			obj1.addTo_ListOfMyUint32List(700);
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			
			obj1.insertTo_ListOfMyUint32List(800);
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(800));
			{
				std::vector<float> myExternalList;
				myExternalList.push_back(4.5);
				myExternalList.push_back(5.5);
				myExternalList.push_back(6.5);
			
				obj1.clear_ListOfMyFloatList();
				TS_ASSERT(obj1.getListOfMyFloatList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyFloatList());
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(4.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(5.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			
				obj1.setListOfMyFloatList(myExternalList);
				TS_ASSERT(obj1.getListOfMyFloatList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
				TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
				TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
				TS_ASSERT(obj1.contains_ListOfMyFloatList(6.5));
			
				obj1.clear_ListOfMyFloatList();
				TS_ASSERT(obj1.getListOfMyFloatList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyFloatList());
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(4.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(5.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			}
			obj1.addTo_ListOfMyFloatList(4.5);
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(!obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			
			obj1.addTo_ListOfMyFloatList(5.5);
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			
			obj1.insertTo_ListOfMyFloatList(6.5);
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(6.5));
			{
				std::vector<double> myExternalList;
				myExternalList.push_back(1.0);
				myExternalList.push_back(2.0);
				myExternalList.push_back(3.0);
			
				obj1.clear_ListOfMyDoubleList();
				TS_ASSERT(obj1.getListOfMyDoubleList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList());
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(1.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(2.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			
				obj1.setListOfMyDoubleList(myExternalList);
				TS_ASSERT(obj1.getListOfMyDoubleList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
				TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
				TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
				TS_ASSERT(obj1.contains_ListOfMyDoubleList(3.0));
			
				obj1.clear_ListOfMyDoubleList();
				TS_ASSERT(obj1.getListOfMyDoubleList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList());
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(1.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(2.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			}
			obj1.addTo_ListOfMyDoubleList(1.0);
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(!obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			
			obj1.addTo_ListOfMyDoubleList(2.0);
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			
			obj1.insertTo_ListOfMyDoubleList(3.0);
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(3.0));
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
	
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
			TS_ASSERT(obj1.contains_ListOfMyBoolList(false));
			TS_ASSERT(obj1.getListOfMyCharList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('f'));
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-500));
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(800));
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(6.5));
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(3.0));
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
	
			obj2 = obj1;
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == obj2.getSize_ListOfMyBoolList());
			TS_ASSERT(obj1.isEmpty_ListOfMyBoolList() == obj2.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == obj2.getSize_ListOfMyCharList());
			TS_ASSERT(obj1.isEmpty_ListOfMyCharList() == obj2.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == obj2.getSize_ListOfMyInt32List());
			TS_ASSERT(obj1.isEmpty_ListOfMyInt32List() == obj2.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == obj2.getSize_ListOfMyUint32List());
			TS_ASSERT(obj1.isEmpty_ListOfMyUint32List() == obj2.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == obj2.getSize_ListOfMyFloatList());
			TS_ASSERT(obj1.isEmpty_ListOfMyFloatList() == obj2.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == obj2.getSize_ListOfMyDoubleList());
			TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList() == obj2.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == obj2.getSize_ListOfMyStringList());
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList() == obj2.isEmpty_ListOfMyStringList());
	
			TS_ASSERT(obj2.getListOfMyBoolList().size() == 2);
			TS_ASSERT(obj2.getSize_ListOfMyBoolList() == 2);
			TS_ASSERT(!obj2.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj2.contains_ListOfMyBoolList(true));
			TS_ASSERT(obj2.contains_ListOfMyBoolList(false));
			TS_ASSERT(obj2.getListOfMyCharList().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyCharList() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj2.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj2.contains_ListOfMyCharList('e'));
			TS_ASSERT(obj2.contains_ListOfMyCharList('f'));
			TS_ASSERT(obj2.getListOfMyInt32List().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyInt32List() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj2.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj2.contains_ListOfMyInt32List(-400));
			TS_ASSERT(obj2.contains_ListOfMyInt32List(-500));
			TS_ASSERT(obj2.getListOfMyUint32List().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyUint32List() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj2.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj2.contains_ListOfMyUint32List(700));
			TS_ASSERT(obj2.contains_ListOfMyUint32List(800));
			TS_ASSERT(obj2.getListOfMyFloatList().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyFloatList() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj2.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj2.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(obj2.contains_ListOfMyFloatList(6.5));
			TS_ASSERT(obj2.getListOfMyDoubleList().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyDoubleList() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj2.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj2.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(obj2.contains_ListOfMyDoubleList(3.0));
			TS_ASSERT(obj2.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello Milky Way!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test11Lists obj1;
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.getListOfMyCharList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList());
	
			Test11Lists obj2;
			TS_ASSERT(obj2.getListOfMyBoolList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyBoolList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj2.getListOfMyCharList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyCharList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj2.getListOfMyInt32List().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyInt32List() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj2.getListOfMyUint32List().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyUint32List() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj2.getListOfMyFloatList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyFloatList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj2.getListOfMyDoubleList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyDoubleList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj2.getListOfMyStringList().size() == 0);
			TS_ASSERT(obj2.getSize_ListOfMyStringList() == 0);
			TS_ASSERT(obj2.isEmpty_ListOfMyStringList());
	
			{
				std::vector<bool> myExternalList;
				myExternalList.push_back(true);
				myExternalList.push_back(false);
			
				obj1.clear_ListOfMyBoolList();
				TS_ASSERT(obj1.getListOfMyBoolList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyBoolList());
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(true));
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(false));
			
				obj1.setListOfMyBoolList(myExternalList);
				TS_ASSERT(obj1.getListOfMyBoolList().size() == 2);
				TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 2);
				TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
				TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
				TS_ASSERT(obj1.contains_ListOfMyBoolList(false));
			
				obj1.clear_ListOfMyBoolList();
				TS_ASSERT(obj1.getListOfMyBoolList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyBoolList());
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(true));
				TS_ASSERT(!obj1.contains_ListOfMyBoolList(false));
			}
			obj1.addTo_ListOfMyBoolList(true);
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
			TS_ASSERT(!obj1.contains_ListOfMyBoolList(false));
			
			obj1.addTo_ListOfMyBoolList(false);
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
			TS_ASSERT(obj1.contains_ListOfMyBoolList(false));
			
			{
				std::vector<char> myExternalList;
				myExternalList.push_back('d');
				myExternalList.push_back('e');
				myExternalList.push_back('f');
			
				obj1.clear_ListOfMyCharList();
				TS_ASSERT(obj1.getListOfMyCharList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyCharList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyCharList());
				TS_ASSERT(!obj1.contains_ListOfMyCharList('d'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('e'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			
				obj1.setListOfMyCharList(myExternalList);
				TS_ASSERT(obj1.getListOfMyCharList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyCharList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
				TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
				TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
				TS_ASSERT(obj1.contains_ListOfMyCharList('f'));
			
				obj1.clear_ListOfMyCharList();
				TS_ASSERT(obj1.getListOfMyCharList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyCharList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyCharList());
				TS_ASSERT(!obj1.contains_ListOfMyCharList('d'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('e'));
				TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			}
			obj1.addTo_ListOfMyCharList('d');
			TS_ASSERT(obj1.getListOfMyCharList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(!obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			
			obj1.addTo_ListOfMyCharList('e');
			TS_ASSERT(obj1.getListOfMyCharList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(!obj1.contains_ListOfMyCharList('f'));
			
			obj1.insertTo_ListOfMyCharList('f');
			TS_ASSERT(obj1.getListOfMyCharList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('f'));
			{
				std::vector<int32_t> myExternalList;
				myExternalList.push_back(-300);
				myExternalList.push_back(-400);
				myExternalList.push_back(-500);
			
				obj1.clear_ListOfMyInt32List();
				TS_ASSERT(obj1.getListOfMyInt32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyInt32List());
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-300));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-400));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			
				obj1.setListOfMyInt32List(myExternalList);
				TS_ASSERT(obj1.getListOfMyInt32List().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
				TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
				TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
				TS_ASSERT(obj1.contains_ListOfMyInt32List(-500));
			
				obj1.clear_ListOfMyInt32List();
				TS_ASSERT(obj1.getListOfMyInt32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyInt32List());
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-300));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-400));
				TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			}
			obj1.addTo_ListOfMyInt32List(-300);
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(!obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			
			obj1.addTo_ListOfMyInt32List(-400);
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(!obj1.contains_ListOfMyInt32List(-500));
			
			obj1.insertTo_ListOfMyInt32List(-500);
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-500));
			{
				std::vector<uint32_t> myExternalList;
				myExternalList.push_back(600);
				myExternalList.push_back(700);
				myExternalList.push_back(800);
			
				obj1.clear_ListOfMyUint32List();
				TS_ASSERT(obj1.getListOfMyUint32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyUint32List());
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(600));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(700));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			
				obj1.setListOfMyUint32List(myExternalList);
				TS_ASSERT(obj1.getListOfMyUint32List().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
				TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
				TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
				TS_ASSERT(obj1.contains_ListOfMyUint32List(800));
			
				obj1.clear_ListOfMyUint32List();
				TS_ASSERT(obj1.getListOfMyUint32List().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyUint32List());
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(600));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(700));
				TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			}
			obj1.addTo_ListOfMyUint32List(600);
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(!obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			
			obj1.addTo_ListOfMyUint32List(700);
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(!obj1.contains_ListOfMyUint32List(800));
			
			obj1.insertTo_ListOfMyUint32List(800);
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(800));
			{
				std::vector<float> myExternalList;
				myExternalList.push_back(4.5);
				myExternalList.push_back(5.5);
				myExternalList.push_back(6.5);
			
				obj1.clear_ListOfMyFloatList();
				TS_ASSERT(obj1.getListOfMyFloatList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyFloatList());
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(4.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(5.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			
				obj1.setListOfMyFloatList(myExternalList);
				TS_ASSERT(obj1.getListOfMyFloatList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
				TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
				TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
				TS_ASSERT(obj1.contains_ListOfMyFloatList(6.5));
			
				obj1.clear_ListOfMyFloatList();
				TS_ASSERT(obj1.getListOfMyFloatList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyFloatList());
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(4.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(5.5));
				TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			}
			obj1.addTo_ListOfMyFloatList(4.5);
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(!obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			
			obj1.addTo_ListOfMyFloatList(5.5);
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(!obj1.contains_ListOfMyFloatList(6.5));
			
			obj1.insertTo_ListOfMyFloatList(6.5);
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(6.5));
			{
				std::vector<double> myExternalList;
				myExternalList.push_back(1.0);
				myExternalList.push_back(2.0);
				myExternalList.push_back(3.0);
			
				obj1.clear_ListOfMyDoubleList();
				TS_ASSERT(obj1.getListOfMyDoubleList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList());
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(1.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(2.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			
				obj1.setListOfMyDoubleList(myExternalList);
				TS_ASSERT(obj1.getListOfMyDoubleList().size() == 3);
				TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 3);
				TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
				TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
				TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
				TS_ASSERT(obj1.contains_ListOfMyDoubleList(3.0));
			
				obj1.clear_ListOfMyDoubleList();
				TS_ASSERT(obj1.getListOfMyDoubleList().size() == 0);
				TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 0);
				TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList());
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(1.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(2.0));
				TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			}
			obj1.addTo_ListOfMyDoubleList(1.0);
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 1);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 1);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(!obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			
			obj1.addTo_ListOfMyDoubleList(2.0);
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(!obj1.contains_ListOfMyDoubleList(3.0));
			
			obj1.insertTo_ListOfMyDoubleList(3.0);
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(3.0));
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
	
			TS_ASSERT(obj1.getListOfMyBoolList().size() == 2);
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == 2);
			TS_ASSERT(!obj1.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.contains_ListOfMyBoolList(true));
			TS_ASSERT(obj1.contains_ListOfMyBoolList(false));
			TS_ASSERT(obj1.getListOfMyCharList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('e'));
			TS_ASSERT(obj1.contains_ListOfMyCharList('f'));
			TS_ASSERT(obj1.getListOfMyInt32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-400));
			TS_ASSERT(obj1.contains_ListOfMyInt32List(-500));
			TS_ASSERT(obj1.getListOfMyUint32List().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(700));
			TS_ASSERT(obj1.contains_ListOfMyUint32List(800));
			TS_ASSERT(obj1.getListOfMyFloatList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(obj1.contains_ListOfMyFloatList(6.5));
			TS_ASSERT(obj1.getListOfMyDoubleList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(obj1.contains_ListOfMyDoubleList(3.0));
			TS_ASSERT(obj1.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj1.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj1.contains_ListOfMyStringList("Hello Milky Way!"));
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getSize_ListOfMyBoolList() == obj2.getSize_ListOfMyBoolList());
			TS_ASSERT(obj1.isEmpty_ListOfMyBoolList() == obj2.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj1.getSize_ListOfMyCharList() == obj2.getSize_ListOfMyCharList());
			TS_ASSERT(obj1.isEmpty_ListOfMyCharList() == obj2.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj1.getSize_ListOfMyInt32List() == obj2.getSize_ListOfMyInt32List());
			TS_ASSERT(obj1.isEmpty_ListOfMyInt32List() == obj2.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj1.getSize_ListOfMyUint32List() == obj2.getSize_ListOfMyUint32List());
			TS_ASSERT(obj1.isEmpty_ListOfMyUint32List() == obj2.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj1.getSize_ListOfMyFloatList() == obj2.getSize_ListOfMyFloatList());
			TS_ASSERT(obj1.isEmpty_ListOfMyFloatList() == obj2.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj1.getSize_ListOfMyDoubleList() == obj2.getSize_ListOfMyDoubleList());
			TS_ASSERT(obj1.isEmpty_ListOfMyDoubleList() == obj2.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj1.getSize_ListOfMyStringList() == obj2.getSize_ListOfMyStringList());
			TS_ASSERT(obj1.isEmpty_ListOfMyStringList() == obj2.isEmpty_ListOfMyStringList());
	
			TS_ASSERT(obj2.getListOfMyBoolList().size() == 2);
			TS_ASSERT(obj2.getSize_ListOfMyBoolList() == 2);
			TS_ASSERT(!obj2.isEmpty_ListOfMyBoolList());
			TS_ASSERT(obj2.contains_ListOfMyBoolList(true));
			TS_ASSERT(obj2.contains_ListOfMyBoolList(false));
			TS_ASSERT(obj2.getListOfMyCharList().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyCharList() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyCharList());
			TS_ASSERT(obj2.contains_ListOfMyCharList('d'));
			TS_ASSERT(obj2.contains_ListOfMyCharList('e'));
			TS_ASSERT(obj2.contains_ListOfMyCharList('f'));
			TS_ASSERT(obj2.getListOfMyInt32List().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyInt32List() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyInt32List());
			TS_ASSERT(obj2.contains_ListOfMyInt32List(-300));
			TS_ASSERT(obj2.contains_ListOfMyInt32List(-400));
			TS_ASSERT(obj2.contains_ListOfMyInt32List(-500));
			TS_ASSERT(obj2.getListOfMyUint32List().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyUint32List() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyUint32List());
			TS_ASSERT(obj2.contains_ListOfMyUint32List(600));
			TS_ASSERT(obj2.contains_ListOfMyUint32List(700));
			TS_ASSERT(obj2.contains_ListOfMyUint32List(800));
			TS_ASSERT(obj2.getListOfMyFloatList().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyFloatList() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyFloatList());
			TS_ASSERT(obj2.contains_ListOfMyFloatList(4.5));
			TS_ASSERT(obj2.contains_ListOfMyFloatList(5.5));
			TS_ASSERT(obj2.contains_ListOfMyFloatList(6.5));
			TS_ASSERT(obj2.getListOfMyDoubleList().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyDoubleList() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyDoubleList());
			TS_ASSERT(obj2.contains_ListOfMyDoubleList(1.0));
			TS_ASSERT(obj2.contains_ListOfMyDoubleList(2.0));
			TS_ASSERT(obj2.contains_ListOfMyDoubleList(3.0));
			TS_ASSERT(obj2.getListOfMyStringList().size() == 3);
			TS_ASSERT(obj2.getSize_ListOfMyStringList() == 3);
			TS_ASSERT(!obj2.isEmpty_ListOfMyStringList());
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello World!"));
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello Solar System!"));
			TS_ASSERT(obj2.contains_ListOfMyStringList("Hello Milky Way!"));
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST11LISTS_TESTSUITE_H*/
