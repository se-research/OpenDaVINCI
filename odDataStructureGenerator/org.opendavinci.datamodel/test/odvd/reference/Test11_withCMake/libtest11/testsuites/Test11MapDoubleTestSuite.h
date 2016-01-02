/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST11MAPDOUBLE_TESTSUITE_H
#define TEST11MAPDOUBLE_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// core/opendavinci.h must be included to setup platform-dependent header files and configurations.
#include "core/opendavinci.h"
#include "core/strings/StringToolbox.h"

#include "GeneratedHeaders_Test11.h"


class Test11MapDouble_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test11MapDouble obj1;
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap());
	
			{
				std::map<double, bool> myExternalMap;
				myExternalMap[1.0] = true;
				myExternalMap[2.0] = false;
			
				obj1.clear_MapOfMyDoubleBoolMap();
				TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			
				obj1.setMapOfMyDoubleBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			
				obj1.clear_MapOfMyDoubleBoolMap();
				TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			}
			obj1.putTo_MapOfMyDoubleBoolMap(1.0, true);
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			
			obj1.putTo_MapOfMyDoubleBoolMap(2.0, false);
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			
			{
				std::map<double, char> myExternalMap;
				myExternalMap[1.0] = 'd';
				myExternalMap[2.0] = 'e';
				myExternalMap[3.0] = 'f';
			
				obj1.clear_MapOfMyDoubleCharMap();
				TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			
				obj1.setMapOfMyDoubleCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(3.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			
				obj1.clear_MapOfMyDoubleCharMap();
				TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleCharMap(1.0, 'd');
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			
			obj1.putTo_MapOfMyDoubleCharMap(2.0, 'e');
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			
			obj1.putTo_MapOfMyDoubleCharMap(3.0, 'f');
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			{
				std::map<double, int32_t> myExternalMap;
				myExternalMap[1.0] = -300;
				myExternalMap[2.0] = -400;
				myExternalMap[3.0] = -500;
			
				obj1.clear_MapOfMyDoubleInt32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			
				obj1.setMapOfMyDoubleInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			
				obj1.clear_MapOfMyDoubleInt32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			}
			obj1.putTo_MapOfMyDoubleInt32Map(1.0, -300);
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleInt32Map(2.0, -400);
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleInt32Map(3.0, -500);
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			{
				std::map<double, uint32_t> myExternalMap;
				myExternalMap[1.0] = 600;
				myExternalMap[2.0] = 700;
				myExternalMap[3.0] = 800;
			
				obj1.clear_MapOfMyDoubleUint32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			
				obj1.setMapOfMyDoubleUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			
				obj1.clear_MapOfMyDoubleUint32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			}
			obj1.putTo_MapOfMyDoubleUint32Map(1.0, 600);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleUint32Map(2.0, 700);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleUint32Map(3.0, 800);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			{
				std::map<double, float> myExternalMap;
				myExternalMap[1.0] = 4.5;
				myExternalMap[2.0] = 5.5;
				myExternalMap[3.0] = 6.5;
			
				obj1.clear_MapOfMyDoubleFloatMap();
				TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			
				obj1.setMapOfMyDoubleFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			
				obj1.clear_MapOfMyDoubleFloatMap();
				TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleFloatMap(1.0, 4.5);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			
			obj1.putTo_MapOfMyDoubleFloatMap(2.0, 5.5);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			
			obj1.putTo_MapOfMyDoubleFloatMap(3.0, 6.5);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			{
				std::map<double, double> myExternalMap;
				myExternalMap[1.0] = 1.0;
				myExternalMap[2.0] = 2.0;
				myExternalMap[3.0] = 3.0;
			
				obj1.clear_MapOfMyDoubleDoubleMap();
				TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			
				obj1.setMapOfMyDoubleDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			
				obj1.clear_MapOfMyDoubleDoubleMap();
				TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleDoubleMap(1.0, 1.0);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			
			obj1.putTo_MapOfMyDoubleDoubleMap(2.0, 2.0);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			
			obj1.putTo_MapOfMyDoubleDoubleMap(3.0, 3.0);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			{
				std::map<double, std::string> myExternalMap;
				myExternalMap[1.0] = "Hello World!";
				myExternalMap[2.0] = "Hello Solar System!";
				myExternalMap[3.0] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyDoubleStringMap();
				TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			
				obj1.setMapOfMyDoubleStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(3.0));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(3.0), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyDoubleStringMap();
				TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleStringMap(1.0, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			
			obj1.putTo_MapOfMyDoubleStringMap(2.0, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			
			obj1.putTo_MapOfMyDoubleStringMap(3.0, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(3.0), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleStringMap(3.0) == "Hello Milky Way!");
		}
	
		void testCreateAndCopyObject() {
	
			Test11MapDouble obj1;
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap());
	
			Test11MapDouble obj2(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == obj2.getSize_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap() == obj2.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == obj2.getSize_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap() == obj2.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == obj2.getSize_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map() == obj2.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == obj2.getSize_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map() == obj2.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == obj2.getSize_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap() == obj2.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == obj2.getSize_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap() == obj2.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == obj2.getSize_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap() == obj2.isEmpty_MapOfMyDoubleStringMap());
	
			{
				std::map<double, bool> myExternalMap;
				myExternalMap[1.0] = true;
				myExternalMap[2.0] = false;
			
				obj1.clear_MapOfMyDoubleBoolMap();
				TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			
				obj1.setMapOfMyDoubleBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			
				obj1.clear_MapOfMyDoubleBoolMap();
				TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			}
			obj1.putTo_MapOfMyDoubleBoolMap(1.0, true);
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			
			obj1.putTo_MapOfMyDoubleBoolMap(2.0, false);
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			
			{
				std::map<double, char> myExternalMap;
				myExternalMap[1.0] = 'd';
				myExternalMap[2.0] = 'e';
				myExternalMap[3.0] = 'f';
			
				obj1.clear_MapOfMyDoubleCharMap();
				TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			
				obj1.setMapOfMyDoubleCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(3.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			
				obj1.clear_MapOfMyDoubleCharMap();
				TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleCharMap(1.0, 'd');
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			
			obj1.putTo_MapOfMyDoubleCharMap(2.0, 'e');
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			
			obj1.putTo_MapOfMyDoubleCharMap(3.0, 'f');
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			{
				std::map<double, int32_t> myExternalMap;
				myExternalMap[1.0] = -300;
				myExternalMap[2.0] = -400;
				myExternalMap[3.0] = -500;
			
				obj1.clear_MapOfMyDoubleInt32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			
				obj1.setMapOfMyDoubleInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			
				obj1.clear_MapOfMyDoubleInt32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			}
			obj1.putTo_MapOfMyDoubleInt32Map(1.0, -300);
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleInt32Map(2.0, -400);
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleInt32Map(3.0, -500);
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			{
				std::map<double, uint32_t> myExternalMap;
				myExternalMap[1.0] = 600;
				myExternalMap[2.0] = 700;
				myExternalMap[3.0] = 800;
			
				obj1.clear_MapOfMyDoubleUint32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			
				obj1.setMapOfMyDoubleUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			
				obj1.clear_MapOfMyDoubleUint32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			}
			obj1.putTo_MapOfMyDoubleUint32Map(1.0, 600);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleUint32Map(2.0, 700);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleUint32Map(3.0, 800);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			{
				std::map<double, float> myExternalMap;
				myExternalMap[1.0] = 4.5;
				myExternalMap[2.0] = 5.5;
				myExternalMap[3.0] = 6.5;
			
				obj1.clear_MapOfMyDoubleFloatMap();
				TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			
				obj1.setMapOfMyDoubleFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			
				obj1.clear_MapOfMyDoubleFloatMap();
				TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleFloatMap(1.0, 4.5);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			
			obj1.putTo_MapOfMyDoubleFloatMap(2.0, 5.5);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			
			obj1.putTo_MapOfMyDoubleFloatMap(3.0, 6.5);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			{
				std::map<double, double> myExternalMap;
				myExternalMap[1.0] = 1.0;
				myExternalMap[2.0] = 2.0;
				myExternalMap[3.0] = 3.0;
			
				obj1.clear_MapOfMyDoubleDoubleMap();
				TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			
				obj1.setMapOfMyDoubleDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			
				obj1.clear_MapOfMyDoubleDoubleMap();
				TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleDoubleMap(1.0, 1.0);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			
			obj1.putTo_MapOfMyDoubleDoubleMap(2.0, 2.0);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			
			obj1.putTo_MapOfMyDoubleDoubleMap(3.0, 3.0);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			{
				std::map<double, std::string> myExternalMap;
				myExternalMap[1.0] = "Hello World!";
				myExternalMap[2.0] = "Hello Solar System!";
				myExternalMap[3.0] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyDoubleStringMap();
				TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			
				obj1.setMapOfMyDoubleStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(3.0));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(3.0), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyDoubleStringMap();
				TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleStringMap(1.0, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			
			obj1.putTo_MapOfMyDoubleStringMap(2.0, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			
			obj1.putTo_MapOfMyDoubleStringMap(3.0, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(3.0), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleStringMap(3.0) == "Hello Milky Way!");
	
			Test11MapDouble obj3(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == obj3.getSize_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap() == obj3.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == obj3.getSize_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap() == obj3.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == obj3.getSize_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map() == obj3.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == obj3.getSize_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map() == obj3.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == obj3.getSize_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap() == obj3.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == obj3.getSize_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap() == obj3.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == obj3.getSize_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap() == obj3.isEmpty_MapOfMyDoubleStringMap());
	
			TS_ASSERT(obj3.getMapOfMyDoubleBoolMap().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyDoubleBoolMap() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleBoolMap(2.0));
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			TS_ASSERT(obj3.getMapOfMyDoubleCharMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyDoubleCharMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleCharMap(3.0));
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			TS_ASSERT(obj3.getMapOfMyDoubleInt32Map().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyDoubleInt32Map() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleInt32Map(3.0));
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			TS_ASSERT(obj3.getMapOfMyDoubleUint32Map().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyDoubleUint32Map() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleUint32Map(3.0));
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			TS_ASSERT(obj3.getMapOfMyDoubleFloatMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyDoubleFloatMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleFloatMap(3.0));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			TS_ASSERT(obj3.getMapOfMyDoubleDoubleMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyDoubleDoubleMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleDoubleMap(3.0));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			TS_ASSERT(obj3.getMapOfMyDoubleStringMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyDoubleStringMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleStringMap(1.0) == "Hello World!");
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleStringMap(2.0) == "Hello Solar System!");
			TS_ASSERT(obj3.containsKey_MapOfMyDoubleStringMap(3.0));
			TS_ASSERT(obj3.getValueForKey_MapOfMyDoubleStringMap(3.0) == "Hello Milky Way!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test11MapDouble obj1;
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap());
	
			Test11MapDouble obj2;
			TS_ASSERT(obj2.getMapOfMyDoubleBoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleBoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj2.getMapOfMyDoubleCharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleCharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj2.getMapOfMyDoubleInt32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleInt32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj2.getMapOfMyDoubleUint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleUint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj2.getMapOfMyDoubleFloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleFloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj2.getMapOfMyDoubleDoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleDoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj2.getMapOfMyDoubleStringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleStringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleStringMap());
	
			{
				std::map<double, bool> myExternalMap;
				myExternalMap[1.0] = true;
				myExternalMap[2.0] = false;
			
				obj1.clear_MapOfMyDoubleBoolMap();
				TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			
				obj1.setMapOfMyDoubleBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			
				obj1.clear_MapOfMyDoubleBoolMap();
				TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			}
			obj1.putTo_MapOfMyDoubleBoolMap(1.0, true);
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			
			obj1.putTo_MapOfMyDoubleBoolMap(2.0, false);
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			
			{
				std::map<double, char> myExternalMap;
				myExternalMap[1.0] = 'd';
				myExternalMap[2.0] = 'e';
				myExternalMap[3.0] = 'f';
			
				obj1.clear_MapOfMyDoubleCharMap();
				TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			
				obj1.setMapOfMyDoubleCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(3.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			
				obj1.clear_MapOfMyDoubleCharMap();
				TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleCharMap(1.0, 'd');
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			
			obj1.putTo_MapOfMyDoubleCharMap(2.0, 'e');
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			
			obj1.putTo_MapOfMyDoubleCharMap(3.0, 'f');
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			{
				std::map<double, int32_t> myExternalMap;
				myExternalMap[1.0] = -300;
				myExternalMap[2.0] = -400;
				myExternalMap[3.0] = -500;
			
				obj1.clear_MapOfMyDoubleInt32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			
				obj1.setMapOfMyDoubleInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			
				obj1.clear_MapOfMyDoubleInt32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			}
			obj1.putTo_MapOfMyDoubleInt32Map(1.0, -300);
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleInt32Map(2.0, -400);
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleInt32Map(3.0, -500);
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			{
				std::map<double, uint32_t> myExternalMap;
				myExternalMap[1.0] = 600;
				myExternalMap[2.0] = 700;
				myExternalMap[3.0] = 800;
			
				obj1.clear_MapOfMyDoubleUint32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			
				obj1.setMapOfMyDoubleUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			
				obj1.clear_MapOfMyDoubleUint32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			}
			obj1.putTo_MapOfMyDoubleUint32Map(1.0, 600);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleUint32Map(2.0, 700);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleUint32Map(3.0, 800);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			{
				std::map<double, float> myExternalMap;
				myExternalMap[1.0] = 4.5;
				myExternalMap[2.0] = 5.5;
				myExternalMap[3.0] = 6.5;
			
				obj1.clear_MapOfMyDoubleFloatMap();
				TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			
				obj1.setMapOfMyDoubleFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			
				obj1.clear_MapOfMyDoubleFloatMap();
				TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleFloatMap(1.0, 4.5);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			
			obj1.putTo_MapOfMyDoubleFloatMap(2.0, 5.5);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			
			obj1.putTo_MapOfMyDoubleFloatMap(3.0, 6.5);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			{
				std::map<double, double> myExternalMap;
				myExternalMap[1.0] = 1.0;
				myExternalMap[2.0] = 2.0;
				myExternalMap[3.0] = 3.0;
			
				obj1.clear_MapOfMyDoubleDoubleMap();
				TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			
				obj1.setMapOfMyDoubleDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			
				obj1.clear_MapOfMyDoubleDoubleMap();
				TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleDoubleMap(1.0, 1.0);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			
			obj1.putTo_MapOfMyDoubleDoubleMap(2.0, 2.0);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			
			obj1.putTo_MapOfMyDoubleDoubleMap(3.0, 3.0);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			{
				std::map<double, std::string> myExternalMap;
				myExternalMap[1.0] = "Hello World!";
				myExternalMap[2.0] = "Hello Solar System!";
				myExternalMap[3.0] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyDoubleStringMap();
				TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			
				obj1.setMapOfMyDoubleStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(3.0));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(3.0), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyDoubleStringMap();
				TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleStringMap(1.0, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			
			obj1.putTo_MapOfMyDoubleStringMap(2.0, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			
			obj1.putTo_MapOfMyDoubleStringMap(3.0, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(3.0), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleStringMap(3.0) == "Hello Milky Way!");
	
			obj2 = obj1;
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == obj2.getSize_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap() == obj2.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == obj2.getSize_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap() == obj2.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == obj2.getSize_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map() == obj2.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == obj2.getSize_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map() == obj2.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == obj2.getSize_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap() == obj2.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == obj2.getSize_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap() == obj2.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == obj2.getSize_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap() == obj2.isEmpty_MapOfMyDoubleStringMap());
	
			TS_ASSERT(obj2.getMapOfMyDoubleBoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleBoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleBoolMap(2.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			TS_ASSERT(obj2.getMapOfMyDoubleCharMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleCharMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleCharMap(3.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			TS_ASSERT(obj2.getMapOfMyDoubleInt32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleInt32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleInt32Map(3.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			TS_ASSERT(obj2.getMapOfMyDoubleUint32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleUint32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleUint32Map(3.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			TS_ASSERT(obj2.getMapOfMyDoubleFloatMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleFloatMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleFloatMap(3.0));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyDoubleDoubleMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleDoubleMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleDoubleMap(3.0));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyDoubleStringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleStringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleStringMap(1.0) == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleStringMap(2.0) == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleStringMap(3.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleStringMap(3.0) == "Hello Milky Way!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test11MapDouble obj1;
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap());
	
			Test11MapDouble obj2;
			TS_ASSERT(obj2.getMapOfMyDoubleBoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleBoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj2.getMapOfMyDoubleCharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleCharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj2.getMapOfMyDoubleInt32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleInt32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj2.getMapOfMyDoubleUint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleUint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj2.getMapOfMyDoubleFloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleFloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj2.getMapOfMyDoubleDoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleDoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj2.getMapOfMyDoubleStringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleStringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyDoubleStringMap());
	
			{
				std::map<double, bool> myExternalMap;
				myExternalMap[1.0] = true;
				myExternalMap[2.0] = false;
			
				obj1.clear_MapOfMyDoubleBoolMap();
				TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			
				obj1.setMapOfMyDoubleBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			
				obj1.clear_MapOfMyDoubleBoolMap();
				TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			}
			obj1.putTo_MapOfMyDoubleBoolMap(1.0, true);
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			
			obj1.putTo_MapOfMyDoubleBoolMap(2.0, false);
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			
			{
				std::map<double, char> myExternalMap;
				myExternalMap[1.0] = 'd';
				myExternalMap[2.0] = 'e';
				myExternalMap[3.0] = 'f';
			
				obj1.clear_MapOfMyDoubleCharMap();
				TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			
				obj1.setMapOfMyDoubleCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(3.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			
				obj1.clear_MapOfMyDoubleCharMap();
				TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleCharMap(1.0, 'd');
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			
			obj1.putTo_MapOfMyDoubleCharMap(2.0, 'e');
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			
			obj1.putTo_MapOfMyDoubleCharMap(3.0, 'f');
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			{
				std::map<double, int32_t> myExternalMap;
				myExternalMap[1.0] = -300;
				myExternalMap[2.0] = -400;
				myExternalMap[3.0] = -500;
			
				obj1.clear_MapOfMyDoubleInt32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			
				obj1.setMapOfMyDoubleInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			
				obj1.clear_MapOfMyDoubleInt32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			}
			obj1.putTo_MapOfMyDoubleInt32Map(1.0, -300);
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleInt32Map(2.0, -400);
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleInt32Map(3.0, -500);
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			{
				std::map<double, uint32_t> myExternalMap;
				myExternalMap[1.0] = 600;
				myExternalMap[2.0] = 700;
				myExternalMap[3.0] = 800;
			
				obj1.clear_MapOfMyDoubleUint32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			
				obj1.setMapOfMyDoubleUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
				TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			
				obj1.clear_MapOfMyDoubleUint32Map();
				TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			}
			obj1.putTo_MapOfMyDoubleUint32Map(1.0, 600);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleUint32Map(2.0, 700);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			
			obj1.putTo_MapOfMyDoubleUint32Map(3.0, 800);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(1.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			{
				std::map<double, float> myExternalMap;
				myExternalMap[1.0] = 4.5;
				myExternalMap[2.0] = 5.5;
				myExternalMap[3.0] = 6.5;
			
				obj1.clear_MapOfMyDoubleFloatMap();
				TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			
				obj1.setMapOfMyDoubleFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			
				obj1.clear_MapOfMyDoubleFloatMap();
				TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleFloatMap(1.0, 4.5);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			
			obj1.putTo_MapOfMyDoubleFloatMap(2.0, 5.5);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			
			obj1.putTo_MapOfMyDoubleFloatMap(3.0, 6.5);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			{
				std::map<double, double> myExternalMap;
				myExternalMap[1.0] = 1.0;
				myExternalMap[2.0] = 2.0;
				myExternalMap[3.0] = 3.0;
			
				obj1.clear_MapOfMyDoubleDoubleMap();
				TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			
				obj1.setMapOfMyDoubleDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			
				obj1.clear_MapOfMyDoubleDoubleMap();
				TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleDoubleMap(1.0, 1.0);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			
			obj1.putTo_MapOfMyDoubleDoubleMap(2.0, 2.0);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			
			obj1.putTo_MapOfMyDoubleDoubleMap(3.0, 3.0);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(1.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			{
				std::map<double, std::string> myExternalMap;
				myExternalMap[1.0] = "Hello World!";
				myExternalMap[2.0] = "Hello Solar System!";
				myExternalMap[3.0] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyDoubleStringMap();
				TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			
				obj1.setMapOfMyDoubleStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(3.0));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(3.0), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyDoubleStringMap();
				TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(1.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(2.0));
				TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			}
			obj1.putTo_MapOfMyDoubleStringMap(1.0, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			
			obj1.putTo_MapOfMyDoubleStringMap(2.0, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			
			obj1.putTo_MapOfMyDoubleStringMap(3.0, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(1.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyDoubleStringMap(3.0), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyDoubleBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleBoolMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			TS_ASSERT(obj1.getMapOfMyDoubleCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleCharMap(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			TS_ASSERT(obj1.getMapOfMyDoubleInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleInt32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			TS_ASSERT(obj1.getMapOfMyDoubleUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleUint32Map(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			TS_ASSERT(obj1.getMapOfMyDoubleFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleFloatMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyDoubleDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleDoubleMap(3.0));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyDoubleStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleStringMap(1.0) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleStringMap(2.0) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyDoubleStringMap(3.0));
			TS_ASSERT(obj1.getValueForKey_MapOfMyDoubleStringMap(3.0) == "Hello Milky Way!");
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getSize_MapOfMyDoubleBoolMap() == obj2.getSize_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleBoolMap() == obj2.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleCharMap() == obj2.getSize_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleCharMap() == obj2.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleInt32Map() == obj2.getSize_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleInt32Map() == obj2.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleUint32Map() == obj2.getSize_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleUint32Map() == obj2.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleFloatMap() == obj2.getSize_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleFloatMap() == obj2.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleDoubleMap() == obj2.getSize_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleDoubleMap() == obj2.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyDoubleStringMap() == obj2.getSize_MapOfMyDoubleStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyDoubleStringMap() == obj2.isEmpty_MapOfMyDoubleStringMap());
	
			TS_ASSERT(obj2.getMapOfMyDoubleBoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleBoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleBoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleBoolMap(1.0) == true);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleBoolMap(2.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleBoolMap(2.0) == false);
			TS_ASSERT(obj2.getMapOfMyDoubleCharMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleCharMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleCharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleCharMap(1.0) == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleCharMap(2.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleCharMap(2.0) == 'e');
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleCharMap(3.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleCharMap(3.0) == 'f');
			TS_ASSERT(obj2.getMapOfMyDoubleInt32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleInt32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleInt32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleInt32Map(1.0) == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleInt32Map(2.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleInt32Map(2.0) == -400);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleInt32Map(3.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleInt32Map(3.0) == -500);
			TS_ASSERT(obj2.getMapOfMyDoubleUint32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleUint32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleUint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleUint32Map(1.0) == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleUint32Map(2.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleUint32Map(2.0) == 700);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleUint32Map(3.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleUint32Map(3.0) == 800);
			TS_ASSERT(obj2.getMapOfMyDoubleFloatMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleFloatMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleFloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyDoubleFloatMap(1.0), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleFloatMap(2.0));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyDoubleFloatMap(2.0), 5.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleFloatMap(3.0));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyDoubleFloatMap(3.0), 6.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyDoubleDoubleMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleDoubleMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleDoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyDoubleDoubleMap(1.0), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleDoubleMap(2.0));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyDoubleDoubleMap(2.0), 2.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleDoubleMap(3.0));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyDoubleDoubleMap(3.0), 3.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyDoubleStringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyDoubleStringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyDoubleStringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleStringMap(1.0) == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleStringMap(2.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleStringMap(2.0) == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyDoubleStringMap(3.0));
			TS_ASSERT(obj2.getValueForKey_MapOfMyDoubleStringMap(3.0) == "Hello Milky Way!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST11MAPDOUBLE_TESTSUITE_H*/
