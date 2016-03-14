/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST12MAPSTRING_TESTSUITE_H
#define TEST12MAPSTRING_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/strings/StringToolbox.h"

#include "test12/GeneratedHeaders_Test12.h"
#include "test12/generated/Test12MapString.h"


class Test12MapString_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test12MapString obj1;
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap());
	
			{
				std::map<std::string, bool> myExternalMap;
				myExternalMap["Hello World!"] = true;
				myExternalMap["Hello Solar System!"] = false;
			
				obj1.clear_MapOfMyStringBoolMap();
				TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			
				obj1.setMapOfMyStringBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
				TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			
				obj1.clear_MapOfMyStringBoolMap();
				TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			}
			obj1.putTo_MapOfMyStringBoolMap("Hello World!", true);
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			
			obj1.putTo_MapOfMyStringBoolMap("Hello Solar System!", false);
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			
			{
				std::map<std::string, char> myExternalMap;
				myExternalMap["Hello World!"] = 'd';
				myExternalMap["Hello Solar System!"] = 'e';
				myExternalMap["Hello Milky Way!"] = 'f';
			
				obj1.clear_MapOfMyStringCharMap();
				TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			
				obj1.clear_MapOfMyStringCharMap();
				TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringCharMap("Hello World!", 'd');
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringCharMap("Hello Solar System!", 'e');
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringCharMap("Hello Milky Way!", 'f');
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			{
				std::map<std::string, int32_t> myExternalMap;
				myExternalMap["Hello World!"] = -300;
				myExternalMap["Hello Solar System!"] = -400;
				myExternalMap["Hello Milky Way!"] = -500;
			
				obj1.clear_MapOfMyStringInt32Map();
				TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			
				obj1.setMapOfMyStringInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			
				obj1.clear_MapOfMyStringInt32Map();
				TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringInt32Map("Hello World!", -300);
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringInt32Map("Hello Solar System!", -400);
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringInt32Map("Hello Milky Way!", -500);
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			{
				std::map<std::string, uint32_t> myExternalMap;
				myExternalMap["Hello World!"] = 600;
				myExternalMap["Hello Solar System!"] = 700;
				myExternalMap["Hello Milky Way!"] = 800;
			
				obj1.clear_MapOfMyStringUint32Map();
				TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			
				obj1.setMapOfMyStringUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			
				obj1.clear_MapOfMyStringUint32Map();
				TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringUint32Map("Hello World!", 600);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringUint32Map("Hello Solar System!", 700);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringUint32Map("Hello Milky Way!", 800);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			{
				std::map<std::string, float> myExternalMap;
				myExternalMap["Hello World!"] = 4.5;
				myExternalMap["Hello Solar System!"] = 5.5;
				myExternalMap["Hello Milky Way!"] = 6.5;
			
				obj1.clear_MapOfMyStringFloatMap();
				TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			
				obj1.clear_MapOfMyStringFloatMap();
				TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringFloatMap("Hello World!", 4.5);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringFloatMap("Hello Solar System!", 5.5);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringFloatMap("Hello Milky Way!", 6.5);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			{
				std::map<std::string, double> myExternalMap;
				myExternalMap["Hello World!"] = 1.0;
				myExternalMap["Hello Solar System!"] = 2.0;
				myExternalMap["Hello Milky Way!"] = 3.0;
			
				obj1.clear_MapOfMyStringDoubleMap();
				TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			
				obj1.clear_MapOfMyStringDoubleMap();
				TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringDoubleMap("Hello World!", 1.0);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringDoubleMap("Hello Solar System!", 2.0);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringDoubleMap("Hello Milky Way!", 3.0);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			{
				std::map<std::string, std::string> myExternalMap;
				myExternalMap["Hello World!"] = "Hello World!";
				myExternalMap["Hello Solar System!"] = "Hello Solar System!";
				myExternalMap["Hello Milky Way!"] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyStringStringMap();
				TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!"), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!"), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyStringStringMap();
				TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringStringMap("Hello World!", "Hello World!");
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringStringMap("Hello Solar System!", "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!"), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringStringMap("Hello Milky Way!", "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!"), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!"), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!") == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!") == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!") == "Hello Milky Way!");
		}
	
		void testCreateAndCopyObject() {
	
			Test12MapString obj1;
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap());
	
			Test12MapString obj2(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == obj2.getSize_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap() == obj2.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == obj2.getSize_MapOfMyStringCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap() == obj2.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == obj2.getSize_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map() == obj2.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == obj2.getSize_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map() == obj2.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == obj2.getSize_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap() == obj2.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == obj2.getSize_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap() == obj2.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == obj2.getSize_MapOfMyStringStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap() == obj2.isEmpty_MapOfMyStringStringMap());
	
			{
				std::map<std::string, bool> myExternalMap;
				myExternalMap["Hello World!"] = true;
				myExternalMap["Hello Solar System!"] = false;
			
				obj1.clear_MapOfMyStringBoolMap();
				TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			
				obj1.setMapOfMyStringBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
				TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			
				obj1.clear_MapOfMyStringBoolMap();
				TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			}
			obj1.putTo_MapOfMyStringBoolMap("Hello World!", true);
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			
			obj1.putTo_MapOfMyStringBoolMap("Hello Solar System!", false);
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			
			{
				std::map<std::string, char> myExternalMap;
				myExternalMap["Hello World!"] = 'd';
				myExternalMap["Hello Solar System!"] = 'e';
				myExternalMap["Hello Milky Way!"] = 'f';
			
				obj1.clear_MapOfMyStringCharMap();
				TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			
				obj1.clear_MapOfMyStringCharMap();
				TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringCharMap("Hello World!", 'd');
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringCharMap("Hello Solar System!", 'e');
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringCharMap("Hello Milky Way!", 'f');
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			{
				std::map<std::string, int32_t> myExternalMap;
				myExternalMap["Hello World!"] = -300;
				myExternalMap["Hello Solar System!"] = -400;
				myExternalMap["Hello Milky Way!"] = -500;
			
				obj1.clear_MapOfMyStringInt32Map();
				TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			
				obj1.setMapOfMyStringInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			
				obj1.clear_MapOfMyStringInt32Map();
				TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringInt32Map("Hello World!", -300);
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringInt32Map("Hello Solar System!", -400);
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringInt32Map("Hello Milky Way!", -500);
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			{
				std::map<std::string, uint32_t> myExternalMap;
				myExternalMap["Hello World!"] = 600;
				myExternalMap["Hello Solar System!"] = 700;
				myExternalMap["Hello Milky Way!"] = 800;
			
				obj1.clear_MapOfMyStringUint32Map();
				TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			
				obj1.setMapOfMyStringUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			
				obj1.clear_MapOfMyStringUint32Map();
				TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringUint32Map("Hello World!", 600);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringUint32Map("Hello Solar System!", 700);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringUint32Map("Hello Milky Way!", 800);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			{
				std::map<std::string, float> myExternalMap;
				myExternalMap["Hello World!"] = 4.5;
				myExternalMap["Hello Solar System!"] = 5.5;
				myExternalMap["Hello Milky Way!"] = 6.5;
			
				obj1.clear_MapOfMyStringFloatMap();
				TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			
				obj1.clear_MapOfMyStringFloatMap();
				TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringFloatMap("Hello World!", 4.5);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringFloatMap("Hello Solar System!", 5.5);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringFloatMap("Hello Milky Way!", 6.5);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			{
				std::map<std::string, double> myExternalMap;
				myExternalMap["Hello World!"] = 1.0;
				myExternalMap["Hello Solar System!"] = 2.0;
				myExternalMap["Hello Milky Way!"] = 3.0;
			
				obj1.clear_MapOfMyStringDoubleMap();
				TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			
				obj1.clear_MapOfMyStringDoubleMap();
				TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringDoubleMap("Hello World!", 1.0);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringDoubleMap("Hello Solar System!", 2.0);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringDoubleMap("Hello Milky Way!", 3.0);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			{
				std::map<std::string, std::string> myExternalMap;
				myExternalMap["Hello World!"] = "Hello World!";
				myExternalMap["Hello Solar System!"] = "Hello Solar System!";
				myExternalMap["Hello Milky Way!"] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyStringStringMap();
				TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!"), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!"), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyStringStringMap();
				TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringStringMap("Hello World!", "Hello World!");
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringStringMap("Hello Solar System!", "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!"), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringStringMap("Hello Milky Way!", "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!"), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!"), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!") == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!") == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!") == "Hello Milky Way!");
	
			Test12MapString obj3(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == obj3.getSize_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap() == obj3.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == obj3.getSize_MapOfMyStringCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap() == obj3.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == obj3.getSize_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map() == obj3.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == obj3.getSize_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map() == obj3.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == obj3.getSize_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap() == obj3.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == obj3.getSize_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap() == obj3.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == obj3.getSize_MapOfMyStringStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap() == obj3.isEmpty_MapOfMyStringStringMap());
	
			TS_ASSERT(obj3.getMapOfMyStringBoolMap().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyStringBoolMap() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(obj3.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			TS_ASSERT(obj3.getMapOfMyStringCharMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyStringCharMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj3.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(obj3.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			TS_ASSERT(obj3.getMapOfMyStringInt32Map().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyStringInt32Map() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj3.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(obj3.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			TS_ASSERT(obj3.getMapOfMyStringUint32Map().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyStringUint32Map() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj3.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(obj3.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			TS_ASSERT(obj3.getMapOfMyStringFloatMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyStringFloatMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			TS_ASSERT(obj3.getMapOfMyStringDoubleMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyStringDoubleMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			TS_ASSERT(obj3.getMapOfMyStringStringMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyStringStringMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringStringMap("Hello World!") == "Hello World!");
			TS_ASSERT(obj3.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringStringMap("Hello Solar System!") == "Hello Solar System!");
			TS_ASSERT(obj3.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			TS_ASSERT(obj3.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!") == "Hello Milky Way!");
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test12MapString obj1;
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap());
	
			Test12MapString obj2;
			TS_ASSERT(obj2.getMapOfMyStringBoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringBoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj2.getMapOfMyStringCharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringCharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj2.getMapOfMyStringInt32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringInt32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj2.getMapOfMyStringUint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringUint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj2.getMapOfMyStringFloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringFloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj2.getMapOfMyStringDoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringDoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj2.getMapOfMyStringStringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringStringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringStringMap());
	
			{
				std::map<std::string, bool> myExternalMap;
				myExternalMap["Hello World!"] = true;
				myExternalMap["Hello Solar System!"] = false;
			
				obj1.clear_MapOfMyStringBoolMap();
				TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			
				obj1.setMapOfMyStringBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
				TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			
				obj1.clear_MapOfMyStringBoolMap();
				TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			}
			obj1.putTo_MapOfMyStringBoolMap("Hello World!", true);
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			
			obj1.putTo_MapOfMyStringBoolMap("Hello Solar System!", false);
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			
			{
				std::map<std::string, char> myExternalMap;
				myExternalMap["Hello World!"] = 'd';
				myExternalMap["Hello Solar System!"] = 'e';
				myExternalMap["Hello Milky Way!"] = 'f';
			
				obj1.clear_MapOfMyStringCharMap();
				TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			
				obj1.clear_MapOfMyStringCharMap();
				TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringCharMap("Hello World!", 'd');
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringCharMap("Hello Solar System!", 'e');
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringCharMap("Hello Milky Way!", 'f');
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			{
				std::map<std::string, int32_t> myExternalMap;
				myExternalMap["Hello World!"] = -300;
				myExternalMap["Hello Solar System!"] = -400;
				myExternalMap["Hello Milky Way!"] = -500;
			
				obj1.clear_MapOfMyStringInt32Map();
				TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			
				obj1.setMapOfMyStringInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			
				obj1.clear_MapOfMyStringInt32Map();
				TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringInt32Map("Hello World!", -300);
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringInt32Map("Hello Solar System!", -400);
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringInt32Map("Hello Milky Way!", -500);
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			{
				std::map<std::string, uint32_t> myExternalMap;
				myExternalMap["Hello World!"] = 600;
				myExternalMap["Hello Solar System!"] = 700;
				myExternalMap["Hello Milky Way!"] = 800;
			
				obj1.clear_MapOfMyStringUint32Map();
				TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			
				obj1.setMapOfMyStringUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			
				obj1.clear_MapOfMyStringUint32Map();
				TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringUint32Map("Hello World!", 600);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringUint32Map("Hello Solar System!", 700);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringUint32Map("Hello Milky Way!", 800);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			{
				std::map<std::string, float> myExternalMap;
				myExternalMap["Hello World!"] = 4.5;
				myExternalMap["Hello Solar System!"] = 5.5;
				myExternalMap["Hello Milky Way!"] = 6.5;
			
				obj1.clear_MapOfMyStringFloatMap();
				TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			
				obj1.clear_MapOfMyStringFloatMap();
				TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringFloatMap("Hello World!", 4.5);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringFloatMap("Hello Solar System!", 5.5);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringFloatMap("Hello Milky Way!", 6.5);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			{
				std::map<std::string, double> myExternalMap;
				myExternalMap["Hello World!"] = 1.0;
				myExternalMap["Hello Solar System!"] = 2.0;
				myExternalMap["Hello Milky Way!"] = 3.0;
			
				obj1.clear_MapOfMyStringDoubleMap();
				TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			
				obj1.clear_MapOfMyStringDoubleMap();
				TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringDoubleMap("Hello World!", 1.0);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringDoubleMap("Hello Solar System!", 2.0);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringDoubleMap("Hello Milky Way!", 3.0);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			{
				std::map<std::string, std::string> myExternalMap;
				myExternalMap["Hello World!"] = "Hello World!";
				myExternalMap["Hello Solar System!"] = "Hello Solar System!";
				myExternalMap["Hello Milky Way!"] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyStringStringMap();
				TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!"), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!"), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyStringStringMap();
				TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringStringMap("Hello World!", "Hello World!");
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringStringMap("Hello Solar System!", "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!"), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringStringMap("Hello Milky Way!", "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!"), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!"), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!") == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!") == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!") == "Hello Milky Way!");
	
			obj2 = obj1;
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == obj2.getSize_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap() == obj2.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == obj2.getSize_MapOfMyStringCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap() == obj2.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == obj2.getSize_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map() == obj2.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == obj2.getSize_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map() == obj2.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == obj2.getSize_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap() == obj2.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == obj2.getSize_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap() == obj2.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == obj2.getSize_MapOfMyStringStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap() == obj2.isEmpty_MapOfMyStringStringMap());
	
			TS_ASSERT(obj2.getMapOfMyStringBoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyStringBoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(obj2.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			TS_ASSERT(obj2.getMapOfMyStringCharMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyStringCharMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(obj2.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			TS_ASSERT(obj2.getMapOfMyStringInt32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyStringInt32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(obj2.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			TS_ASSERT(obj2.getMapOfMyStringUint32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyStringUint32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(obj2.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			TS_ASSERT(obj2.getMapOfMyStringFloatMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyStringFloatMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyStringDoubleMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyStringDoubleMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyStringStringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyStringStringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringStringMap("Hello World!") == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringStringMap("Hello Solar System!") == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!") == "Hello Milky Way!");
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test12MapString obj1;
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap());
	
			Test12MapString obj2;
			TS_ASSERT(obj2.getMapOfMyStringBoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringBoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj2.getMapOfMyStringCharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringCharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj2.getMapOfMyStringInt32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringInt32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj2.getMapOfMyStringUint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringUint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj2.getMapOfMyStringFloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringFloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj2.getMapOfMyStringDoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringDoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj2.getMapOfMyStringStringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyStringStringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyStringStringMap());
	
			{
				std::map<std::string, bool> myExternalMap;
				myExternalMap["Hello World!"] = true;
				myExternalMap["Hello Solar System!"] = false;
			
				obj1.clear_MapOfMyStringBoolMap();
				TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			
				obj1.setMapOfMyStringBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
				TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			
				obj1.clear_MapOfMyStringBoolMap();
				TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			}
			obj1.putTo_MapOfMyStringBoolMap("Hello World!", true);
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			
			obj1.putTo_MapOfMyStringBoolMap("Hello Solar System!", false);
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			
			{
				std::map<std::string, char> myExternalMap;
				myExternalMap["Hello World!"] = 'd';
				myExternalMap["Hello Solar System!"] = 'e';
				myExternalMap["Hello Milky Way!"] = 'f';
			
				obj1.clear_MapOfMyStringCharMap();
				TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			
				obj1.clear_MapOfMyStringCharMap();
				TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringCharMap("Hello World!", 'd');
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringCharMap("Hello Solar System!", 'e');
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringCharMap("Hello Milky Way!", 'f');
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			{
				std::map<std::string, int32_t> myExternalMap;
				myExternalMap["Hello World!"] = -300;
				myExternalMap["Hello Solar System!"] = -400;
				myExternalMap["Hello Milky Way!"] = -500;
			
				obj1.clear_MapOfMyStringInt32Map();
				TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			
				obj1.setMapOfMyStringInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			
				obj1.clear_MapOfMyStringInt32Map();
				TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringInt32Map("Hello World!", -300);
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringInt32Map("Hello Solar System!", -400);
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringInt32Map("Hello Milky Way!", -500);
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			{
				std::map<std::string, uint32_t> myExternalMap;
				myExternalMap["Hello World!"] = 600;
				myExternalMap["Hello Solar System!"] = 700;
				myExternalMap["Hello Milky Way!"] = 800;
			
				obj1.clear_MapOfMyStringUint32Map();
				TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			
				obj1.setMapOfMyStringUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
				TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			
				obj1.clear_MapOfMyStringUint32Map();
				TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringUint32Map("Hello World!", 600);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringUint32Map("Hello Solar System!", 700);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringUint32Map("Hello Milky Way!", 800);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello World!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			{
				std::map<std::string, float> myExternalMap;
				myExternalMap["Hello World!"] = 4.5;
				myExternalMap["Hello Solar System!"] = 5.5;
				myExternalMap["Hello Milky Way!"] = 6.5;
			
				obj1.clear_MapOfMyStringFloatMap();
				TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			
				obj1.clear_MapOfMyStringFloatMap();
				TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringFloatMap("Hello World!", 4.5);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringFloatMap("Hello Solar System!", 5.5);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringFloatMap("Hello Milky Way!", 6.5);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			{
				std::map<std::string, double> myExternalMap;
				myExternalMap["Hello World!"] = 1.0;
				myExternalMap["Hello Solar System!"] = 2.0;
				myExternalMap["Hello Milky Way!"] = 3.0;
			
				obj1.clear_MapOfMyStringDoubleMap();
				TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			
				obj1.clear_MapOfMyStringDoubleMap();
				TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringDoubleMap("Hello World!", 1.0);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringDoubleMap("Hello Solar System!", 2.0);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringDoubleMap("Hello Milky Way!", 3.0);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello World!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			{
				std::map<std::string, std::string> myExternalMap;
				myExternalMap["Hello World!"] = "Hello World!";
				myExternalMap["Hello Solar System!"] = "Hello Solar System!";
				myExternalMap["Hello Milky Way!"] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyStringStringMap();
				TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			
				obj1.setMapOfMyStringStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!"), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!"), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyStringStringMap();
				TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
				TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			}
			obj1.putTo_MapOfMyStringStringMap("Hello World!", "Hello World!");
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringStringMap("Hello Solar System!", "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!"), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			
			obj1.putTo_MapOfMyStringStringMap("Hello Milky Way!", "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello World!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!"), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!"), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!"), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyStringBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(obj1.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			TS_ASSERT(obj1.getMapOfMyStringCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			TS_ASSERT(obj1.getMapOfMyStringInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			TS_ASSERT(obj1.getMapOfMyStringUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			TS_ASSERT(obj1.getMapOfMyStringFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyStringDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyStringStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringStringMap("Hello World!") == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringStringMap("Hello Solar System!") == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			TS_ASSERT(obj1.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!") == "Hello Milky Way!");
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getSize_MapOfMyStringBoolMap() == obj2.getSize_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringBoolMap() == obj2.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringCharMap() == obj2.getSize_MapOfMyStringCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringCharMap() == obj2.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringInt32Map() == obj2.getSize_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringInt32Map() == obj2.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyStringUint32Map() == obj2.getSize_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringUint32Map() == obj2.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyStringFloatMap() == obj2.getSize_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringFloatMap() == obj2.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringDoubleMap() == obj2.getSize_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringDoubleMap() == obj2.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyStringStringMap() == obj2.getSize_MapOfMyStringStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyStringStringMap() == obj2.isEmpty_MapOfMyStringStringMap());
	
			TS_ASSERT(obj2.getMapOfMyStringBoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyStringBoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringBoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringBoolMap("Hello World!") == true);
			TS_ASSERT(obj2.containsKey_MapOfMyStringBoolMap("Hello Solar System!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringBoolMap("Hello Solar System!") == false);
			TS_ASSERT(obj2.getMapOfMyStringCharMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyStringCharMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringCharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringCharMap("Hello World!") == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyStringCharMap("Hello Solar System!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringCharMap("Hello Solar System!") == 'e');
			TS_ASSERT(obj2.containsKey_MapOfMyStringCharMap("Hello Milky Way!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringCharMap("Hello Milky Way!") == 'f');
			TS_ASSERT(obj2.getMapOfMyStringInt32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyStringInt32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringInt32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringInt32Map("Hello World!") == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyStringInt32Map("Hello Solar System!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringInt32Map("Hello Solar System!") == -400);
			TS_ASSERT(obj2.containsKey_MapOfMyStringInt32Map("Hello Milky Way!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringInt32Map("Hello Milky Way!") == -500);
			TS_ASSERT(obj2.getMapOfMyStringUint32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyStringUint32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringUint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringUint32Map("Hello World!") == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyStringUint32Map("Hello Solar System!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringUint32Map("Hello Solar System!") == 700);
			TS_ASSERT(obj2.containsKey_MapOfMyStringUint32Map("Hello Milky Way!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringUint32Map("Hello Milky Way!") == 800);
			TS_ASSERT(obj2.getMapOfMyStringFloatMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyStringFloatMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringFloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyStringFloatMap("Hello World!"), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyStringFloatMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyStringFloatMap("Hello Solar System!"), 5.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyStringFloatMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyStringFloatMap("Hello Milky Way!"), 6.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyStringDoubleMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyStringDoubleMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringDoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyStringDoubleMap("Hello World!"), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyStringDoubleMap("Hello Solar System!"));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyStringDoubleMap("Hello Solar System!"), 2.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyStringDoubleMap("Hello Milky Way!"));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyStringDoubleMap("Hello Milky Way!"), 3.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyStringStringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyStringStringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyStringStringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringStringMap("Hello World!") == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyStringStringMap("Hello Solar System!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringStringMap("Hello Solar System!") == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyStringStringMap("Hello Milky Way!"));
			TS_ASSERT(obj2.getValueForKey_MapOfMyStringStringMap("Hello Milky Way!") == "Hello Milky Way!");
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST12MAPSTRING_TESTSUITE_H*/
