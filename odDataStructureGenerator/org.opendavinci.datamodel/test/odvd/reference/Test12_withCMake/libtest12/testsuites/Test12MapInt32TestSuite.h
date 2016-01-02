/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST12MAPINT32_TESTSUITE_H
#define TEST12MAPINT32_TESTSUITE_H

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


class Test12MapInt32_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test12MapInt32 obj1;
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap());
	
			{
				std::map<int32_t, bool> myExternalMap;
				myExternalMap[-300] = true;
				myExternalMap[-400] = false;
			
				obj1.clear_MapOfMyInt32BoolMap();
				TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-400));
			
				obj1.setMapOfMyInt32BoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			
				obj1.clear_MapOfMyInt32BoolMap();
				TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-400));
			}
			obj1.putTo_MapOfMyInt32BoolMap(-300, true);
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-400));
			
			obj1.putTo_MapOfMyInt32BoolMap(-400, false);
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			
			{
				std::map<int32_t, char> myExternalMap;
				myExternalMap[-300] = 'd';
				myExternalMap[-400] = 'e';
				myExternalMap[-500] = 'f';
			
				obj1.clear_MapOfMyInt32CharMap();
				TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			
				obj1.setMapOfMyInt32CharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-500));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			
				obj1.clear_MapOfMyInt32CharMap();
				TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			}
			obj1.putTo_MapOfMyInt32CharMap(-300, 'd');
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			
			obj1.putTo_MapOfMyInt32CharMap(-400, 'e');
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			
			obj1.putTo_MapOfMyInt32CharMap(-500, 'f');
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			{
				std::map<int32_t, int32_t> myExternalMap;
				myExternalMap[-300] = -300;
				myExternalMap[-400] = -400;
				myExternalMap[-500] = -500;
			
				obj1.clear_MapOfMyInt32Int32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			
				obj1.setMapOfMyInt32Int32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-500));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			
				obj1.clear_MapOfMyInt32Int32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			}
			obj1.putTo_MapOfMyInt32Int32Map(-300, -300);
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			
			obj1.putTo_MapOfMyInt32Int32Map(-400, -400);
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			
			obj1.putTo_MapOfMyInt32Int32Map(-500, -500);
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			{
				std::map<int32_t, uint32_t> myExternalMap;
				myExternalMap[-300] = 600;
				myExternalMap[-400] = 700;
				myExternalMap[-500] = 800;
			
				obj1.clear_MapOfMyInt32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			
				obj1.setMapOfMyInt32Uint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-500));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			
				obj1.clear_MapOfMyInt32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			}
			obj1.putTo_MapOfMyInt32Uint32Map(-300, 600);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			
			obj1.putTo_MapOfMyInt32Uint32Map(-400, 700);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			
			obj1.putTo_MapOfMyInt32Uint32Map(-500, 800);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			{
				std::map<int32_t, float> myExternalMap;
				myExternalMap[-300] = 4.5;
				myExternalMap[-400] = 5.5;
				myExternalMap[-500] = 6.5;
			
				obj1.clear_MapOfMyInt32FloatMap();
				TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			
				obj1.setMapOfMyInt32FloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-500));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			
				obj1.clear_MapOfMyInt32FloatMap();
				TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			}
			obj1.putTo_MapOfMyInt32FloatMap(-300, 4.5);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			
			obj1.putTo_MapOfMyInt32FloatMap(-400, 5.5);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			
			obj1.putTo_MapOfMyInt32FloatMap(-500, 6.5);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			{
				std::map<int32_t, double> myExternalMap;
				myExternalMap[-300] = 1.0;
				myExternalMap[-400] = 2.0;
				myExternalMap[-500] = 3.0;
			
				obj1.clear_MapOfMyInt32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			
				obj1.setMapOfMyInt32DoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-500));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			
				obj1.clear_MapOfMyInt32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			}
			obj1.putTo_MapOfMyInt32DoubleMap(-300, 1.0);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			
			obj1.putTo_MapOfMyInt32DoubleMap(-400, 2.0);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			
			obj1.putTo_MapOfMyInt32DoubleMap(-500, 3.0);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			{
				std::map<int32_t, std::string> myExternalMap;
				myExternalMap[-300] = "Hello World!";
				myExternalMap[-400] = "Hello Solar System!";
				myExternalMap[-500] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyInt32StringMap();
				TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			
				obj1.setMapOfMyInt32StringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-400), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-500));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-500), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyInt32StringMap();
				TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			}
			obj1.putTo_MapOfMyInt32StringMap(-300, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			
			obj1.putTo_MapOfMyInt32StringMap(-400, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-400), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			
			obj1.putTo_MapOfMyInt32StringMap(-500, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-400), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-500));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-500), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32StringMap(-300) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32StringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32StringMap(-500) == "Hello Milky Way!");
		}
	
		void testCreateAndCopyObject() {
	
			Test12MapInt32 obj1;
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap());
	
			Test12MapInt32 obj2(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == obj2.getSize_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap() == obj2.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == obj2.getSize_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap() == obj2.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == obj2.getSize_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map() == obj2.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == obj2.getSize_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map() == obj2.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == obj2.getSize_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap() == obj2.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == obj2.getSize_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap() == obj2.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == obj2.getSize_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap() == obj2.isEmpty_MapOfMyInt32StringMap());
	
			{
				std::map<int32_t, bool> myExternalMap;
				myExternalMap[-300] = true;
				myExternalMap[-400] = false;
			
				obj1.clear_MapOfMyInt32BoolMap();
				TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-400));
			
				obj1.setMapOfMyInt32BoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			
				obj1.clear_MapOfMyInt32BoolMap();
				TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-400));
			}
			obj1.putTo_MapOfMyInt32BoolMap(-300, true);
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-400));
			
			obj1.putTo_MapOfMyInt32BoolMap(-400, false);
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			
			{
				std::map<int32_t, char> myExternalMap;
				myExternalMap[-300] = 'd';
				myExternalMap[-400] = 'e';
				myExternalMap[-500] = 'f';
			
				obj1.clear_MapOfMyInt32CharMap();
				TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			
				obj1.setMapOfMyInt32CharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-500));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			
				obj1.clear_MapOfMyInt32CharMap();
				TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			}
			obj1.putTo_MapOfMyInt32CharMap(-300, 'd');
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			
			obj1.putTo_MapOfMyInt32CharMap(-400, 'e');
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			
			obj1.putTo_MapOfMyInt32CharMap(-500, 'f');
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			{
				std::map<int32_t, int32_t> myExternalMap;
				myExternalMap[-300] = -300;
				myExternalMap[-400] = -400;
				myExternalMap[-500] = -500;
			
				obj1.clear_MapOfMyInt32Int32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			
				obj1.setMapOfMyInt32Int32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-500));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			
				obj1.clear_MapOfMyInt32Int32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			}
			obj1.putTo_MapOfMyInt32Int32Map(-300, -300);
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			
			obj1.putTo_MapOfMyInt32Int32Map(-400, -400);
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			
			obj1.putTo_MapOfMyInt32Int32Map(-500, -500);
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			{
				std::map<int32_t, uint32_t> myExternalMap;
				myExternalMap[-300] = 600;
				myExternalMap[-400] = 700;
				myExternalMap[-500] = 800;
			
				obj1.clear_MapOfMyInt32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			
				obj1.setMapOfMyInt32Uint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-500));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			
				obj1.clear_MapOfMyInt32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			}
			obj1.putTo_MapOfMyInt32Uint32Map(-300, 600);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			
			obj1.putTo_MapOfMyInt32Uint32Map(-400, 700);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			
			obj1.putTo_MapOfMyInt32Uint32Map(-500, 800);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			{
				std::map<int32_t, float> myExternalMap;
				myExternalMap[-300] = 4.5;
				myExternalMap[-400] = 5.5;
				myExternalMap[-500] = 6.5;
			
				obj1.clear_MapOfMyInt32FloatMap();
				TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			
				obj1.setMapOfMyInt32FloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-500));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			
				obj1.clear_MapOfMyInt32FloatMap();
				TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			}
			obj1.putTo_MapOfMyInt32FloatMap(-300, 4.5);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			
			obj1.putTo_MapOfMyInt32FloatMap(-400, 5.5);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			
			obj1.putTo_MapOfMyInt32FloatMap(-500, 6.5);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			{
				std::map<int32_t, double> myExternalMap;
				myExternalMap[-300] = 1.0;
				myExternalMap[-400] = 2.0;
				myExternalMap[-500] = 3.0;
			
				obj1.clear_MapOfMyInt32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			
				obj1.setMapOfMyInt32DoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-500));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			
				obj1.clear_MapOfMyInt32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			}
			obj1.putTo_MapOfMyInt32DoubleMap(-300, 1.0);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			
			obj1.putTo_MapOfMyInt32DoubleMap(-400, 2.0);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			
			obj1.putTo_MapOfMyInt32DoubleMap(-500, 3.0);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			{
				std::map<int32_t, std::string> myExternalMap;
				myExternalMap[-300] = "Hello World!";
				myExternalMap[-400] = "Hello Solar System!";
				myExternalMap[-500] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyInt32StringMap();
				TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			
				obj1.setMapOfMyInt32StringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-400), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-500));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-500), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyInt32StringMap();
				TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			}
			obj1.putTo_MapOfMyInt32StringMap(-300, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			
			obj1.putTo_MapOfMyInt32StringMap(-400, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-400), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			
			obj1.putTo_MapOfMyInt32StringMap(-500, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-400), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-500));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-500), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32StringMap(-300) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32StringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32StringMap(-500) == "Hello Milky Way!");
	
			Test12MapInt32 obj3(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == obj3.getSize_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap() == obj3.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == obj3.getSize_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap() == obj3.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == obj3.getSize_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map() == obj3.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == obj3.getSize_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map() == obj3.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == obj3.getSize_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap() == obj3.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == obj3.getSize_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap() == obj3.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == obj3.getSize_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap() == obj3.isEmpty_MapOfMyInt32StringMap());
	
			TS_ASSERT(obj3.getMapOfMyInt32BoolMap().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyInt32BoolMap() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(obj3.containsKey_MapOfMyInt32BoolMap(-400));
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			TS_ASSERT(obj3.getMapOfMyInt32CharMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyInt32CharMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj3.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(obj3.containsKey_MapOfMyInt32CharMap(-500));
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			TS_ASSERT(obj3.getMapOfMyInt32Int32Map().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyInt32Int32Map() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj3.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(obj3.containsKey_MapOfMyInt32Int32Map(-500));
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			TS_ASSERT(obj3.getMapOfMyInt32Uint32Map().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyInt32Uint32Map() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj3.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(obj3.containsKey_MapOfMyInt32Uint32Map(-500));
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			TS_ASSERT(obj3.getMapOfMyInt32FloatMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyInt32FloatMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyInt32FloatMap(-500));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			TS_ASSERT(obj3.getMapOfMyInt32DoubleMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyInt32DoubleMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyInt32DoubleMap(-500));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			TS_ASSERT(obj3.getMapOfMyInt32StringMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyInt32StringMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32StringMap(-300) == "Hello World!");
			TS_ASSERT(obj3.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32StringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj3.containsKey_MapOfMyInt32StringMap(-500));
			TS_ASSERT(obj3.getValueForKey_MapOfMyInt32StringMap(-500) == "Hello Milky Way!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test12MapInt32 obj1;
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap());
	
			Test12MapInt32 obj2;
			TS_ASSERT(obj2.getMapOfMyInt32BoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32BoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj2.getMapOfMyInt32CharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32CharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj2.getMapOfMyInt32Int32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32Int32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj2.getMapOfMyInt32Uint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32Uint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj2.getMapOfMyInt32FloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32FloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj2.getMapOfMyInt32DoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32DoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj2.getMapOfMyInt32StringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32StringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32StringMap());
	
			{
				std::map<int32_t, bool> myExternalMap;
				myExternalMap[-300] = true;
				myExternalMap[-400] = false;
			
				obj1.clear_MapOfMyInt32BoolMap();
				TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-400));
			
				obj1.setMapOfMyInt32BoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			
				obj1.clear_MapOfMyInt32BoolMap();
				TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-400));
			}
			obj1.putTo_MapOfMyInt32BoolMap(-300, true);
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-400));
			
			obj1.putTo_MapOfMyInt32BoolMap(-400, false);
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			
			{
				std::map<int32_t, char> myExternalMap;
				myExternalMap[-300] = 'd';
				myExternalMap[-400] = 'e';
				myExternalMap[-500] = 'f';
			
				obj1.clear_MapOfMyInt32CharMap();
				TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			
				obj1.setMapOfMyInt32CharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-500));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			
				obj1.clear_MapOfMyInt32CharMap();
				TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			}
			obj1.putTo_MapOfMyInt32CharMap(-300, 'd');
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			
			obj1.putTo_MapOfMyInt32CharMap(-400, 'e');
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			
			obj1.putTo_MapOfMyInt32CharMap(-500, 'f');
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			{
				std::map<int32_t, int32_t> myExternalMap;
				myExternalMap[-300] = -300;
				myExternalMap[-400] = -400;
				myExternalMap[-500] = -500;
			
				obj1.clear_MapOfMyInt32Int32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			
				obj1.setMapOfMyInt32Int32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-500));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			
				obj1.clear_MapOfMyInt32Int32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			}
			obj1.putTo_MapOfMyInt32Int32Map(-300, -300);
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			
			obj1.putTo_MapOfMyInt32Int32Map(-400, -400);
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			
			obj1.putTo_MapOfMyInt32Int32Map(-500, -500);
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			{
				std::map<int32_t, uint32_t> myExternalMap;
				myExternalMap[-300] = 600;
				myExternalMap[-400] = 700;
				myExternalMap[-500] = 800;
			
				obj1.clear_MapOfMyInt32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			
				obj1.setMapOfMyInt32Uint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-500));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			
				obj1.clear_MapOfMyInt32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			}
			obj1.putTo_MapOfMyInt32Uint32Map(-300, 600);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			
			obj1.putTo_MapOfMyInt32Uint32Map(-400, 700);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			
			obj1.putTo_MapOfMyInt32Uint32Map(-500, 800);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			{
				std::map<int32_t, float> myExternalMap;
				myExternalMap[-300] = 4.5;
				myExternalMap[-400] = 5.5;
				myExternalMap[-500] = 6.5;
			
				obj1.clear_MapOfMyInt32FloatMap();
				TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			
				obj1.setMapOfMyInt32FloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-500));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			
				obj1.clear_MapOfMyInt32FloatMap();
				TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			}
			obj1.putTo_MapOfMyInt32FloatMap(-300, 4.5);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			
			obj1.putTo_MapOfMyInt32FloatMap(-400, 5.5);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			
			obj1.putTo_MapOfMyInt32FloatMap(-500, 6.5);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			{
				std::map<int32_t, double> myExternalMap;
				myExternalMap[-300] = 1.0;
				myExternalMap[-400] = 2.0;
				myExternalMap[-500] = 3.0;
			
				obj1.clear_MapOfMyInt32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			
				obj1.setMapOfMyInt32DoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-500));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			
				obj1.clear_MapOfMyInt32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			}
			obj1.putTo_MapOfMyInt32DoubleMap(-300, 1.0);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			
			obj1.putTo_MapOfMyInt32DoubleMap(-400, 2.0);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			
			obj1.putTo_MapOfMyInt32DoubleMap(-500, 3.0);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			{
				std::map<int32_t, std::string> myExternalMap;
				myExternalMap[-300] = "Hello World!";
				myExternalMap[-400] = "Hello Solar System!";
				myExternalMap[-500] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyInt32StringMap();
				TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			
				obj1.setMapOfMyInt32StringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-400), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-500));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-500), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyInt32StringMap();
				TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			}
			obj1.putTo_MapOfMyInt32StringMap(-300, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			
			obj1.putTo_MapOfMyInt32StringMap(-400, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-400), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			
			obj1.putTo_MapOfMyInt32StringMap(-500, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-400), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-500));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-500), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32StringMap(-300) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32StringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32StringMap(-500) == "Hello Milky Way!");
	
			obj2 = obj1;
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == obj2.getSize_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap() == obj2.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == obj2.getSize_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap() == obj2.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == obj2.getSize_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map() == obj2.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == obj2.getSize_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map() == obj2.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == obj2.getSize_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap() == obj2.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == obj2.getSize_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap() == obj2.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == obj2.getSize_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap() == obj2.isEmpty_MapOfMyInt32StringMap());
	
			TS_ASSERT(obj2.getMapOfMyInt32BoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyInt32BoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32BoolMap(-400));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			TS_ASSERT(obj2.getMapOfMyInt32CharMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyInt32CharMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(obj2.containsKey_MapOfMyInt32CharMap(-500));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			TS_ASSERT(obj2.getMapOfMyInt32Int32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyInt32Int32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32Int32Map(-500));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			TS_ASSERT(obj2.getMapOfMyInt32Uint32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyInt32Uint32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32Uint32Map(-500));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			TS_ASSERT(obj2.getMapOfMyInt32FloatMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyInt32FloatMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32FloatMap(-500));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyInt32DoubleMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyInt32DoubleMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32DoubleMap(-500));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyInt32StringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyInt32StringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32StringMap(-300) == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32StringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyInt32StringMap(-500));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32StringMap(-500) == "Hello Milky Way!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test12MapInt32 obj1;
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap());
	
			Test12MapInt32 obj2;
			TS_ASSERT(obj2.getMapOfMyInt32BoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32BoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj2.getMapOfMyInt32CharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32CharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj2.getMapOfMyInt32Int32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32Int32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj2.getMapOfMyInt32Uint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32Uint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj2.getMapOfMyInt32FloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32FloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj2.getMapOfMyInt32DoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32DoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj2.getMapOfMyInt32StringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyInt32StringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyInt32StringMap());
	
			{
				std::map<int32_t, bool> myExternalMap;
				myExternalMap[-300] = true;
				myExternalMap[-400] = false;
			
				obj1.clear_MapOfMyInt32BoolMap();
				TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-400));
			
				obj1.setMapOfMyInt32BoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			
				obj1.clear_MapOfMyInt32BoolMap();
				TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-400));
			}
			obj1.putTo_MapOfMyInt32BoolMap(-300, true);
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32BoolMap(-400));
			
			obj1.putTo_MapOfMyInt32BoolMap(-400, false);
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			
			{
				std::map<int32_t, char> myExternalMap;
				myExternalMap[-300] = 'd';
				myExternalMap[-400] = 'e';
				myExternalMap[-500] = 'f';
			
				obj1.clear_MapOfMyInt32CharMap();
				TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			
				obj1.setMapOfMyInt32CharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-500));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			
				obj1.clear_MapOfMyInt32CharMap();
				TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			}
			obj1.putTo_MapOfMyInt32CharMap(-300, 'd');
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			
			obj1.putTo_MapOfMyInt32CharMap(-400, 'e');
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32CharMap(-500));
			
			obj1.putTo_MapOfMyInt32CharMap(-500, 'f');
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			{
				std::map<int32_t, int32_t> myExternalMap;
				myExternalMap[-300] = -300;
				myExternalMap[-400] = -400;
				myExternalMap[-500] = -500;
			
				obj1.clear_MapOfMyInt32Int32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			
				obj1.setMapOfMyInt32Int32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-500));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			
				obj1.clear_MapOfMyInt32Int32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			}
			obj1.putTo_MapOfMyInt32Int32Map(-300, -300);
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			
			obj1.putTo_MapOfMyInt32Int32Map(-400, -400);
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Int32Map(-500));
			
			obj1.putTo_MapOfMyInt32Int32Map(-500, -500);
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			{
				std::map<int32_t, uint32_t> myExternalMap;
				myExternalMap[-300] = 600;
				myExternalMap[-400] = 700;
				myExternalMap[-500] = 800;
			
				obj1.clear_MapOfMyInt32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			
				obj1.setMapOfMyInt32Uint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-500));
				TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			
				obj1.clear_MapOfMyInt32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			}
			obj1.putTo_MapOfMyInt32Uint32Map(-300, 600);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			
			obj1.putTo_MapOfMyInt32Uint32Map(-400, 700);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			
			obj1.putTo_MapOfMyInt32Uint32Map(-500, 800);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-300));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			{
				std::map<int32_t, float> myExternalMap;
				myExternalMap[-300] = 4.5;
				myExternalMap[-400] = 5.5;
				myExternalMap[-500] = 6.5;
			
				obj1.clear_MapOfMyInt32FloatMap();
				TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			
				obj1.setMapOfMyInt32FloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-500));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			
				obj1.clear_MapOfMyInt32FloatMap();
				TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			}
			obj1.putTo_MapOfMyInt32FloatMap(-300, 4.5);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			
			obj1.putTo_MapOfMyInt32FloatMap(-400, 5.5);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32FloatMap(-500));
			
			obj1.putTo_MapOfMyInt32FloatMap(-500, 6.5);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			{
				std::map<int32_t, double> myExternalMap;
				myExternalMap[-300] = 1.0;
				myExternalMap[-400] = 2.0;
				myExternalMap[-500] = 3.0;
			
				obj1.clear_MapOfMyInt32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			
				obj1.setMapOfMyInt32DoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-500));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			
				obj1.clear_MapOfMyInt32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			}
			obj1.putTo_MapOfMyInt32DoubleMap(-300, 1.0);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			
			obj1.putTo_MapOfMyInt32DoubleMap(-400, 2.0);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			
			obj1.putTo_MapOfMyInt32DoubleMap(-500, 3.0);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-300));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			{
				std::map<int32_t, std::string> myExternalMap;
				myExternalMap[-300] = "Hello World!";
				myExternalMap[-400] = "Hello Solar System!";
				myExternalMap[-500] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyInt32StringMap();
				TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			
				obj1.setMapOfMyInt32StringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-400), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-500));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-500), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyInt32StringMap();
				TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-300));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-400));
				TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			}
			obj1.putTo_MapOfMyInt32StringMap(-300, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			
			obj1.putTo_MapOfMyInt32StringMap(-400, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-400), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyInt32StringMap(-500));
			
			obj1.putTo_MapOfMyInt32StringMap(-500, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-300));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-300), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-400), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-500));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyInt32StringMap(-500), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyInt32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32BoolMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			TS_ASSERT(obj1.getMapOfMyInt32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyInt32CharMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			TS_ASSERT(obj1.getMapOfMyInt32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Int32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			TS_ASSERT(obj1.getMapOfMyInt32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32Uint32Map(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			TS_ASSERT(obj1.getMapOfMyInt32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32FloatMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyInt32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyInt32DoubleMap(-500));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyInt32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32StringMap(-300) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32StringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyInt32StringMap(-500));
			TS_ASSERT(obj1.getValueForKey_MapOfMyInt32StringMap(-500) == "Hello Milky Way!");
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getSize_MapOfMyInt32BoolMap() == obj2.getSize_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32BoolMap() == obj2.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32CharMap() == obj2.getSize_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32CharMap() == obj2.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32Int32Map() == obj2.getSize_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Int32Map() == obj2.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj1.getSize_MapOfMyInt32Uint32Map() == obj2.getSize_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32Uint32Map() == obj2.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyInt32FloatMap() == obj2.getSize_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32FloatMap() == obj2.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32DoubleMap() == obj2.getSize_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32DoubleMap() == obj2.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyInt32StringMap() == obj2.getSize_MapOfMyInt32StringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyInt32StringMap() == obj2.isEmpty_MapOfMyInt32StringMap());
	
			TS_ASSERT(obj2.getMapOfMyInt32BoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyInt32BoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32BoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32BoolMap(-300) == true);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32BoolMap(-400));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32BoolMap(-400) == false);
			TS_ASSERT(obj2.getMapOfMyInt32CharMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyInt32CharMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32CharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32CharMap(-300) == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyInt32CharMap(-400));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32CharMap(-400) == 'e');
			TS_ASSERT(obj2.containsKey_MapOfMyInt32CharMap(-500));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32CharMap(-500) == 'f');
			TS_ASSERT(obj2.getMapOfMyInt32Int32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyInt32Int32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32Int32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32Int32Map(-300) == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32Int32Map(-400));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32Int32Map(-400) == -400);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32Int32Map(-500));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32Int32Map(-500) == -500);
			TS_ASSERT(obj2.getMapOfMyInt32Uint32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyInt32Uint32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32Uint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32Uint32Map(-300) == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32Uint32Map(-400));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32Uint32Map(-400) == 700);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32Uint32Map(-500));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32Uint32Map(-500) == 800);
			TS_ASSERT(obj2.getMapOfMyInt32FloatMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyInt32FloatMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32FloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyInt32FloatMap(-300), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32FloatMap(-400));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyInt32FloatMap(-400), 5.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32FloatMap(-500));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyInt32FloatMap(-500), 6.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyInt32DoubleMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyInt32DoubleMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32DoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyInt32DoubleMap(-300), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32DoubleMap(-400));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyInt32DoubleMap(-400), 2.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyInt32DoubleMap(-500));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyInt32DoubleMap(-500), 3.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyInt32StringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyInt32StringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyInt32StringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32StringMap(-300) == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyInt32StringMap(-400));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32StringMap(-400) == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyInt32StringMap(-500));
			TS_ASSERT(obj2.getValueForKey_MapOfMyInt32StringMap(-500) == "Hello Milky Way!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST12MAPINT32_TESTSUITE_H*/
