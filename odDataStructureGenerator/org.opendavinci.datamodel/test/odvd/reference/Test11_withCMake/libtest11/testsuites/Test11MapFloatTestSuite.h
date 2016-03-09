/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST11MAPFLOAT_TESTSUITE_H
#define TEST11MAPFLOAT_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/strings/StringToolbox.h"

#include "test11/GeneratedHeaders_Test11.h"
#include "test11/generated/Test11MapFloat.h"


class Test11MapFloat_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test11MapFloat obj1;
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap());
	
			{
				std::map<float, bool> myExternalMap;
				myExternalMap[4.5] = true;
				myExternalMap[5.5] = false;
			
				obj1.clear_MapOfMyFloatBoolMap();
				TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			
				obj1.setMapOfMyFloatBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			
				obj1.clear_MapOfMyFloatBoolMap();
				TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			}
			obj1.putTo_MapOfMyFloatBoolMap(4.5, true);
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			
			obj1.putTo_MapOfMyFloatBoolMap(5.5, false);
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			
			{
				std::map<float, char> myExternalMap;
				myExternalMap[4.5] = 'd';
				myExternalMap[5.5] = 'e';
				myExternalMap[6.5] = 'f';
			
				obj1.clear_MapOfMyFloatCharMap();
				TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			
				obj1.setMapOfMyFloatCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(6.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			
				obj1.clear_MapOfMyFloatCharMap();
				TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			}
			obj1.putTo_MapOfMyFloatCharMap(4.5, 'd');
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			
			obj1.putTo_MapOfMyFloatCharMap(5.5, 'e');
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			
			obj1.putTo_MapOfMyFloatCharMap(6.5, 'f');
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			{
				std::map<float, int32_t> myExternalMap;
				myExternalMap[4.5] = -300;
				myExternalMap[5.5] = -400;
				myExternalMap[6.5] = -500;
			
				obj1.clear_MapOfMyFloatInt32Map();
				TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			
				obj1.setMapOfMyFloatInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(6.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			
				obj1.clear_MapOfMyFloatInt32Map();
				TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			}
			obj1.putTo_MapOfMyFloatInt32Map(4.5, -300);
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			
			obj1.putTo_MapOfMyFloatInt32Map(5.5, -400);
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			
			obj1.putTo_MapOfMyFloatInt32Map(6.5, -500);
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			{
				std::map<float, uint32_t> myExternalMap;
				myExternalMap[4.5] = 600;
				myExternalMap[5.5] = 700;
				myExternalMap[6.5] = 800;
			
				obj1.clear_MapOfMyFloatUint32Map();
				TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			
				obj1.setMapOfMyFloatUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(6.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			
				obj1.clear_MapOfMyFloatUint32Map();
				TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			}
			obj1.putTo_MapOfMyFloatUint32Map(4.5, 600);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			
			obj1.putTo_MapOfMyFloatUint32Map(5.5, 700);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			
			obj1.putTo_MapOfMyFloatUint32Map(6.5, 800);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			{
				std::map<float, float> myExternalMap;
				myExternalMap[4.5] = 4.5;
				myExternalMap[5.5] = 5.5;
				myExternalMap[6.5] = 6.5;
			
				obj1.clear_MapOfMyFloatFloatMap();
				TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			
				obj1.setMapOfMyFloatFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(6.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			
				obj1.clear_MapOfMyFloatFloatMap();
				TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			}
			obj1.putTo_MapOfMyFloatFloatMap(4.5, 4.5);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			
			obj1.putTo_MapOfMyFloatFloatMap(5.5, 5.5);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			
			obj1.putTo_MapOfMyFloatFloatMap(6.5, 6.5);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			{
				std::map<float, double> myExternalMap;
				myExternalMap[4.5] = 1.0;
				myExternalMap[5.5] = 2.0;
				myExternalMap[6.5] = 3.0;
			
				obj1.clear_MapOfMyFloatDoubleMap();
				TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			
				obj1.setMapOfMyFloatDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			
				obj1.clear_MapOfMyFloatDoubleMap();
				TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			}
			obj1.putTo_MapOfMyFloatDoubleMap(4.5, 1.0);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			
			obj1.putTo_MapOfMyFloatDoubleMap(5.5, 2.0);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			
			obj1.putTo_MapOfMyFloatDoubleMap(6.5, 3.0);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			{
				std::map<float, std::string> myExternalMap;
				myExternalMap[4.5] = "Hello World!";
				myExternalMap[5.5] = "Hello Solar System!";
				myExternalMap[6.5] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyFloatStringMap();
				TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			
				obj1.setMapOfMyFloatStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(5.5), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(6.5));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(6.5), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyFloatStringMap();
				TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			}
			obj1.putTo_MapOfMyFloatStringMap(4.5, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			
			obj1.putTo_MapOfMyFloatStringMap(5.5, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(5.5), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			
			obj1.putTo_MapOfMyFloatStringMap(6.5, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(5.5), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(6.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(6.5), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatStringMap(4.5) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatStringMap(5.5) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatStringMap(6.5) == "Hello Milky Way!");
		}
	
		void testCreateAndCopyObject() {
	
			Test11MapFloat obj1;
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap());
	
			Test11MapFloat obj2(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == obj2.getSize_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap() == obj2.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == obj2.getSize_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap() == obj2.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == obj2.getSize_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map() == obj2.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == obj2.getSize_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map() == obj2.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == obj2.getSize_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap() == obj2.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == obj2.getSize_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap() == obj2.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == obj2.getSize_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap() == obj2.isEmpty_MapOfMyFloatStringMap());
	
			{
				std::map<float, bool> myExternalMap;
				myExternalMap[4.5] = true;
				myExternalMap[5.5] = false;
			
				obj1.clear_MapOfMyFloatBoolMap();
				TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			
				obj1.setMapOfMyFloatBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			
				obj1.clear_MapOfMyFloatBoolMap();
				TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			}
			obj1.putTo_MapOfMyFloatBoolMap(4.5, true);
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			
			obj1.putTo_MapOfMyFloatBoolMap(5.5, false);
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			
			{
				std::map<float, char> myExternalMap;
				myExternalMap[4.5] = 'd';
				myExternalMap[5.5] = 'e';
				myExternalMap[6.5] = 'f';
			
				obj1.clear_MapOfMyFloatCharMap();
				TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			
				obj1.setMapOfMyFloatCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(6.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			
				obj1.clear_MapOfMyFloatCharMap();
				TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			}
			obj1.putTo_MapOfMyFloatCharMap(4.5, 'd');
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			
			obj1.putTo_MapOfMyFloatCharMap(5.5, 'e');
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			
			obj1.putTo_MapOfMyFloatCharMap(6.5, 'f');
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			{
				std::map<float, int32_t> myExternalMap;
				myExternalMap[4.5] = -300;
				myExternalMap[5.5] = -400;
				myExternalMap[6.5] = -500;
			
				obj1.clear_MapOfMyFloatInt32Map();
				TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			
				obj1.setMapOfMyFloatInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(6.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			
				obj1.clear_MapOfMyFloatInt32Map();
				TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			}
			obj1.putTo_MapOfMyFloatInt32Map(4.5, -300);
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			
			obj1.putTo_MapOfMyFloatInt32Map(5.5, -400);
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			
			obj1.putTo_MapOfMyFloatInt32Map(6.5, -500);
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			{
				std::map<float, uint32_t> myExternalMap;
				myExternalMap[4.5] = 600;
				myExternalMap[5.5] = 700;
				myExternalMap[6.5] = 800;
			
				obj1.clear_MapOfMyFloatUint32Map();
				TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			
				obj1.setMapOfMyFloatUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(6.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			
				obj1.clear_MapOfMyFloatUint32Map();
				TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			}
			obj1.putTo_MapOfMyFloatUint32Map(4.5, 600);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			
			obj1.putTo_MapOfMyFloatUint32Map(5.5, 700);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			
			obj1.putTo_MapOfMyFloatUint32Map(6.5, 800);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			{
				std::map<float, float> myExternalMap;
				myExternalMap[4.5] = 4.5;
				myExternalMap[5.5] = 5.5;
				myExternalMap[6.5] = 6.5;
			
				obj1.clear_MapOfMyFloatFloatMap();
				TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			
				obj1.setMapOfMyFloatFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(6.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			
				obj1.clear_MapOfMyFloatFloatMap();
				TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			}
			obj1.putTo_MapOfMyFloatFloatMap(4.5, 4.5);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			
			obj1.putTo_MapOfMyFloatFloatMap(5.5, 5.5);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			
			obj1.putTo_MapOfMyFloatFloatMap(6.5, 6.5);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			{
				std::map<float, double> myExternalMap;
				myExternalMap[4.5] = 1.0;
				myExternalMap[5.5] = 2.0;
				myExternalMap[6.5] = 3.0;
			
				obj1.clear_MapOfMyFloatDoubleMap();
				TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			
				obj1.setMapOfMyFloatDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			
				obj1.clear_MapOfMyFloatDoubleMap();
				TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			}
			obj1.putTo_MapOfMyFloatDoubleMap(4.5, 1.0);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			
			obj1.putTo_MapOfMyFloatDoubleMap(5.5, 2.0);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			
			obj1.putTo_MapOfMyFloatDoubleMap(6.5, 3.0);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			{
				std::map<float, std::string> myExternalMap;
				myExternalMap[4.5] = "Hello World!";
				myExternalMap[5.5] = "Hello Solar System!";
				myExternalMap[6.5] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyFloatStringMap();
				TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			
				obj1.setMapOfMyFloatStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(5.5), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(6.5));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(6.5), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyFloatStringMap();
				TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			}
			obj1.putTo_MapOfMyFloatStringMap(4.5, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			
			obj1.putTo_MapOfMyFloatStringMap(5.5, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(5.5), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			
			obj1.putTo_MapOfMyFloatStringMap(6.5, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(5.5), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(6.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(6.5), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatStringMap(4.5) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatStringMap(5.5) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatStringMap(6.5) == "Hello Milky Way!");
	
			Test11MapFloat obj3(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == obj3.getSize_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap() == obj3.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == obj3.getSize_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap() == obj3.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == obj3.getSize_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map() == obj3.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == obj3.getSize_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map() == obj3.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == obj3.getSize_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap() == obj3.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == obj3.getSize_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap() == obj3.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == obj3.getSize_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap() == obj3.isEmpty_MapOfMyFloatStringMap());
	
			TS_ASSERT(obj3.getMapOfMyFloatBoolMap().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyFloatBoolMap() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(obj3.containsKey_MapOfMyFloatBoolMap(5.5));
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			TS_ASSERT(obj3.getMapOfMyFloatCharMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyFloatCharMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj3.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(obj3.containsKey_MapOfMyFloatCharMap(6.5));
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			TS_ASSERT(obj3.getMapOfMyFloatInt32Map().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyFloatInt32Map() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj3.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(obj3.containsKey_MapOfMyFloatInt32Map(6.5));
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			TS_ASSERT(obj3.getMapOfMyFloatUint32Map().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyFloatUint32Map() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj3.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(obj3.containsKey_MapOfMyFloatUint32Map(6.5));
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			TS_ASSERT(obj3.getMapOfMyFloatFloatMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyFloatFloatMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyFloatFloatMap(6.5));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			TS_ASSERT(obj3.getMapOfMyFloatDoubleMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyFloatDoubleMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyFloatDoubleMap(6.5));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			TS_ASSERT(obj3.getMapOfMyFloatStringMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyFloatStringMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatStringMap(4.5) == "Hello World!");
			TS_ASSERT(obj3.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatStringMap(5.5) == "Hello Solar System!");
			TS_ASSERT(obj3.containsKey_MapOfMyFloatStringMap(6.5));
			TS_ASSERT(obj3.getValueForKey_MapOfMyFloatStringMap(6.5) == "Hello Milky Way!");
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test11MapFloat obj1;
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap());
	
			Test11MapFloat obj2;
			TS_ASSERT(obj2.getMapOfMyFloatBoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatBoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj2.getMapOfMyFloatCharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatCharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj2.getMapOfMyFloatInt32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatInt32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj2.getMapOfMyFloatUint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatUint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj2.getMapOfMyFloatFloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatFloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj2.getMapOfMyFloatDoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatDoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj2.getMapOfMyFloatStringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatStringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatStringMap());
	
			{
				std::map<float, bool> myExternalMap;
				myExternalMap[4.5] = true;
				myExternalMap[5.5] = false;
			
				obj1.clear_MapOfMyFloatBoolMap();
				TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			
				obj1.setMapOfMyFloatBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			
				obj1.clear_MapOfMyFloatBoolMap();
				TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			}
			obj1.putTo_MapOfMyFloatBoolMap(4.5, true);
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			
			obj1.putTo_MapOfMyFloatBoolMap(5.5, false);
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			
			{
				std::map<float, char> myExternalMap;
				myExternalMap[4.5] = 'd';
				myExternalMap[5.5] = 'e';
				myExternalMap[6.5] = 'f';
			
				obj1.clear_MapOfMyFloatCharMap();
				TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			
				obj1.setMapOfMyFloatCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(6.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			
				obj1.clear_MapOfMyFloatCharMap();
				TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			}
			obj1.putTo_MapOfMyFloatCharMap(4.5, 'd');
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			
			obj1.putTo_MapOfMyFloatCharMap(5.5, 'e');
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			
			obj1.putTo_MapOfMyFloatCharMap(6.5, 'f');
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			{
				std::map<float, int32_t> myExternalMap;
				myExternalMap[4.5] = -300;
				myExternalMap[5.5] = -400;
				myExternalMap[6.5] = -500;
			
				obj1.clear_MapOfMyFloatInt32Map();
				TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			
				obj1.setMapOfMyFloatInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(6.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			
				obj1.clear_MapOfMyFloatInt32Map();
				TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			}
			obj1.putTo_MapOfMyFloatInt32Map(4.5, -300);
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			
			obj1.putTo_MapOfMyFloatInt32Map(5.5, -400);
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			
			obj1.putTo_MapOfMyFloatInt32Map(6.5, -500);
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			{
				std::map<float, uint32_t> myExternalMap;
				myExternalMap[4.5] = 600;
				myExternalMap[5.5] = 700;
				myExternalMap[6.5] = 800;
			
				obj1.clear_MapOfMyFloatUint32Map();
				TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			
				obj1.setMapOfMyFloatUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(6.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			
				obj1.clear_MapOfMyFloatUint32Map();
				TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			}
			obj1.putTo_MapOfMyFloatUint32Map(4.5, 600);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			
			obj1.putTo_MapOfMyFloatUint32Map(5.5, 700);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			
			obj1.putTo_MapOfMyFloatUint32Map(6.5, 800);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			{
				std::map<float, float> myExternalMap;
				myExternalMap[4.5] = 4.5;
				myExternalMap[5.5] = 5.5;
				myExternalMap[6.5] = 6.5;
			
				obj1.clear_MapOfMyFloatFloatMap();
				TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			
				obj1.setMapOfMyFloatFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(6.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			
				obj1.clear_MapOfMyFloatFloatMap();
				TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			}
			obj1.putTo_MapOfMyFloatFloatMap(4.5, 4.5);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			
			obj1.putTo_MapOfMyFloatFloatMap(5.5, 5.5);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			
			obj1.putTo_MapOfMyFloatFloatMap(6.5, 6.5);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			{
				std::map<float, double> myExternalMap;
				myExternalMap[4.5] = 1.0;
				myExternalMap[5.5] = 2.0;
				myExternalMap[6.5] = 3.0;
			
				obj1.clear_MapOfMyFloatDoubleMap();
				TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			
				obj1.setMapOfMyFloatDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			
				obj1.clear_MapOfMyFloatDoubleMap();
				TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			}
			obj1.putTo_MapOfMyFloatDoubleMap(4.5, 1.0);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			
			obj1.putTo_MapOfMyFloatDoubleMap(5.5, 2.0);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			
			obj1.putTo_MapOfMyFloatDoubleMap(6.5, 3.0);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			{
				std::map<float, std::string> myExternalMap;
				myExternalMap[4.5] = "Hello World!";
				myExternalMap[5.5] = "Hello Solar System!";
				myExternalMap[6.5] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyFloatStringMap();
				TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			
				obj1.setMapOfMyFloatStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(5.5), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(6.5));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(6.5), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyFloatStringMap();
				TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			}
			obj1.putTo_MapOfMyFloatStringMap(4.5, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			
			obj1.putTo_MapOfMyFloatStringMap(5.5, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(5.5), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			
			obj1.putTo_MapOfMyFloatStringMap(6.5, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(5.5), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(6.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(6.5), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatStringMap(4.5) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatStringMap(5.5) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatStringMap(6.5) == "Hello Milky Way!");
	
			obj2 = obj1;
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == obj2.getSize_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap() == obj2.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == obj2.getSize_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap() == obj2.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == obj2.getSize_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map() == obj2.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == obj2.getSize_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map() == obj2.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == obj2.getSize_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap() == obj2.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == obj2.getSize_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap() == obj2.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == obj2.getSize_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap() == obj2.isEmpty_MapOfMyFloatStringMap());
	
			TS_ASSERT(obj2.getMapOfMyFloatBoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyFloatBoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatBoolMap(5.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			TS_ASSERT(obj2.getMapOfMyFloatCharMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyFloatCharMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(obj2.containsKey_MapOfMyFloatCharMap(6.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			TS_ASSERT(obj2.getMapOfMyFloatInt32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyFloatInt32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatInt32Map(6.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			TS_ASSERT(obj2.getMapOfMyFloatUint32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyFloatUint32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatUint32Map(6.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			TS_ASSERT(obj2.getMapOfMyFloatFloatMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyFloatFloatMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatFloatMap(6.5));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyFloatDoubleMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyFloatDoubleMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatDoubleMap(6.5));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyFloatStringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyFloatStringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatStringMap(4.5) == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatStringMap(5.5) == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyFloatStringMap(6.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatStringMap(6.5) == "Hello Milky Way!");
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test11MapFloat obj1;
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap());
	
			Test11MapFloat obj2;
			TS_ASSERT(obj2.getMapOfMyFloatBoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatBoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj2.getMapOfMyFloatCharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatCharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj2.getMapOfMyFloatInt32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatInt32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj2.getMapOfMyFloatUint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatUint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj2.getMapOfMyFloatFloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatFloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj2.getMapOfMyFloatDoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatDoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj2.getMapOfMyFloatStringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyFloatStringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyFloatStringMap());
	
			{
				std::map<float, bool> myExternalMap;
				myExternalMap[4.5] = true;
				myExternalMap[5.5] = false;
			
				obj1.clear_MapOfMyFloatBoolMap();
				TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			
				obj1.setMapOfMyFloatBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			
				obj1.clear_MapOfMyFloatBoolMap();
				TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			}
			obj1.putTo_MapOfMyFloatBoolMap(4.5, true);
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			
			obj1.putTo_MapOfMyFloatBoolMap(5.5, false);
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			
			{
				std::map<float, char> myExternalMap;
				myExternalMap[4.5] = 'd';
				myExternalMap[5.5] = 'e';
				myExternalMap[6.5] = 'f';
			
				obj1.clear_MapOfMyFloatCharMap();
				TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			
				obj1.setMapOfMyFloatCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(6.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			
				obj1.clear_MapOfMyFloatCharMap();
				TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			}
			obj1.putTo_MapOfMyFloatCharMap(4.5, 'd');
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			
			obj1.putTo_MapOfMyFloatCharMap(5.5, 'e');
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatCharMap(6.5));
			
			obj1.putTo_MapOfMyFloatCharMap(6.5, 'f');
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			{
				std::map<float, int32_t> myExternalMap;
				myExternalMap[4.5] = -300;
				myExternalMap[5.5] = -400;
				myExternalMap[6.5] = -500;
			
				obj1.clear_MapOfMyFloatInt32Map();
				TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			
				obj1.setMapOfMyFloatInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(6.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			
				obj1.clear_MapOfMyFloatInt32Map();
				TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			}
			obj1.putTo_MapOfMyFloatInt32Map(4.5, -300);
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			
			obj1.putTo_MapOfMyFloatInt32Map(5.5, -400);
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			
			obj1.putTo_MapOfMyFloatInt32Map(6.5, -500);
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			{
				std::map<float, uint32_t> myExternalMap;
				myExternalMap[4.5] = 600;
				myExternalMap[5.5] = 700;
				myExternalMap[6.5] = 800;
			
				obj1.clear_MapOfMyFloatUint32Map();
				TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			
				obj1.setMapOfMyFloatUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(6.5));
				TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			
				obj1.clear_MapOfMyFloatUint32Map();
				TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			}
			obj1.putTo_MapOfMyFloatUint32Map(4.5, 600);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			
			obj1.putTo_MapOfMyFloatUint32Map(5.5, 700);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			
			obj1.putTo_MapOfMyFloatUint32Map(6.5, 800);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(4.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			{
				std::map<float, float> myExternalMap;
				myExternalMap[4.5] = 4.5;
				myExternalMap[5.5] = 5.5;
				myExternalMap[6.5] = 6.5;
			
				obj1.clear_MapOfMyFloatFloatMap();
				TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			
				obj1.setMapOfMyFloatFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(6.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			
				obj1.clear_MapOfMyFloatFloatMap();
				TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			}
			obj1.putTo_MapOfMyFloatFloatMap(4.5, 4.5);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			
			obj1.putTo_MapOfMyFloatFloatMap(5.5, 5.5);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			
			obj1.putTo_MapOfMyFloatFloatMap(6.5, 6.5);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			{
				std::map<float, double> myExternalMap;
				myExternalMap[4.5] = 1.0;
				myExternalMap[5.5] = 2.0;
				myExternalMap[6.5] = 3.0;
			
				obj1.clear_MapOfMyFloatDoubleMap();
				TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			
				obj1.setMapOfMyFloatDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			
				obj1.clear_MapOfMyFloatDoubleMap();
				TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			}
			obj1.putTo_MapOfMyFloatDoubleMap(4.5, 1.0);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			
			obj1.putTo_MapOfMyFloatDoubleMap(5.5, 2.0);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			
			obj1.putTo_MapOfMyFloatDoubleMap(6.5, 3.0);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(4.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			{
				std::map<float, std::string> myExternalMap;
				myExternalMap[4.5] = "Hello World!";
				myExternalMap[5.5] = "Hello Solar System!";
				myExternalMap[6.5] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyFloatStringMap();
				TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			
				obj1.setMapOfMyFloatStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(5.5), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(6.5));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(6.5), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyFloatStringMap();
				TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(4.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(5.5));
				TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			}
			obj1.putTo_MapOfMyFloatStringMap(4.5, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			
			obj1.putTo_MapOfMyFloatStringMap(5.5, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(5.5), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyFloatStringMap(6.5));
			
			obj1.putTo_MapOfMyFloatStringMap(6.5, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(4.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(4.5), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(5.5), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(6.5));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyFloatStringMap(6.5), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyFloatBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatBoolMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			TS_ASSERT(obj1.getMapOfMyFloatCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyFloatCharMap(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			TS_ASSERT(obj1.getMapOfMyFloatInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatInt32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			TS_ASSERT(obj1.getMapOfMyFloatUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatUint32Map(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			TS_ASSERT(obj1.getMapOfMyFloatFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatFloatMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyFloatDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyFloatDoubleMap(6.5));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyFloatStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatStringMap(4.5) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatStringMap(5.5) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyFloatStringMap(6.5));
			TS_ASSERT(obj1.getValueForKey_MapOfMyFloatStringMap(6.5) == "Hello Milky Way!");
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getSize_MapOfMyFloatBoolMap() == obj2.getSize_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatBoolMap() == obj2.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatCharMap() == obj2.getSize_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatCharMap() == obj2.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatInt32Map() == obj2.getSize_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatInt32Map() == obj2.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyFloatUint32Map() == obj2.getSize_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatUint32Map() == obj2.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyFloatFloatMap() == obj2.getSize_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatFloatMap() == obj2.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatDoubleMap() == obj2.getSize_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatDoubleMap() == obj2.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyFloatStringMap() == obj2.getSize_MapOfMyFloatStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyFloatStringMap() == obj2.isEmpty_MapOfMyFloatStringMap());
	
			TS_ASSERT(obj2.getMapOfMyFloatBoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyFloatBoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatBoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatBoolMap(4.5) == true);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatBoolMap(5.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatBoolMap(5.5) == false);
			TS_ASSERT(obj2.getMapOfMyFloatCharMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyFloatCharMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatCharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatCharMap(4.5) == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyFloatCharMap(5.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatCharMap(5.5) == 'e');
			TS_ASSERT(obj2.containsKey_MapOfMyFloatCharMap(6.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatCharMap(6.5) == 'f');
			TS_ASSERT(obj2.getMapOfMyFloatInt32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyFloatInt32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatInt32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatInt32Map(4.5) == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatInt32Map(5.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatInt32Map(5.5) == -400);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatInt32Map(6.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatInt32Map(6.5) == -500);
			TS_ASSERT(obj2.getMapOfMyFloatUint32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyFloatUint32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatUint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatUint32Map(4.5) == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatUint32Map(5.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatUint32Map(5.5) == 700);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatUint32Map(6.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatUint32Map(6.5) == 800);
			TS_ASSERT(obj2.getMapOfMyFloatFloatMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyFloatFloatMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatFloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyFloatFloatMap(4.5), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatFloatMap(5.5));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyFloatFloatMap(5.5), 5.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatFloatMap(6.5));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyFloatFloatMap(6.5), 6.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyFloatDoubleMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyFloatDoubleMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatDoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyFloatDoubleMap(4.5), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatDoubleMap(5.5));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyFloatDoubleMap(5.5), 2.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyFloatDoubleMap(6.5));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyFloatDoubleMap(6.5), 3.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyFloatStringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyFloatStringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyFloatStringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatStringMap(4.5) == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyFloatStringMap(5.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatStringMap(5.5) == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyFloatStringMap(6.5));
			TS_ASSERT(obj2.getValueForKey_MapOfMyFloatStringMap(6.5) == "Hello Milky Way!");
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST11MAPFLOAT_TESTSUITE_H*/
