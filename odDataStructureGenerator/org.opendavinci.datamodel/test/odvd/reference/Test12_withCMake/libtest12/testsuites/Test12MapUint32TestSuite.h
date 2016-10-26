/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST12MAPUINT32_TESTSUITE_H
#define TEST12MAPUINT32_TESTSUITE_H

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/strings/StringToolbox.h>

#include "test12/GeneratedHeaders_Test12.h"
#include "test12/generated/Test12MapUint32.h"


class Test12MapUint32_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test12MapUint32 obj1;
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap());
	
			{
				std::map<uint32_t, bool> myExternalMap;
				myExternalMap[600] = true;
				myExternalMap[700] = false;
			
				obj1.clear_MapOfMyUint32BoolMap();
				TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(700));
			
				obj1.setMapOfMyUint32BoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			
				obj1.clear_MapOfMyUint32BoolMap();
				TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(700));
			}
			obj1.putTo_MapOfMyUint32BoolMap(600, true);
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(700));
			
			obj1.putTo_MapOfMyUint32BoolMap(700, false);
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			
			{
				std::map<uint32_t, char> myExternalMap;
				myExternalMap[600] = 'd';
				myExternalMap[700] = 'e';
				myExternalMap[800] = 'f';
			
				obj1.clear_MapOfMyUint32CharMap();
				TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			
				obj1.setMapOfMyUint32CharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(800));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			
				obj1.clear_MapOfMyUint32CharMap();
				TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			}
			obj1.putTo_MapOfMyUint32CharMap(600, 'd');
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			
			obj1.putTo_MapOfMyUint32CharMap(700, 'e');
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			
			obj1.putTo_MapOfMyUint32CharMap(800, 'f');
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			{
				std::map<uint32_t, int32_t> myExternalMap;
				myExternalMap[600] = -300;
				myExternalMap[700] = -400;
				myExternalMap[800] = -500;
			
				obj1.clear_MapOfMyUint32Int32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			
				obj1.setMapOfMyUint32Int32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(800));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			
				obj1.clear_MapOfMyUint32Int32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			}
			obj1.putTo_MapOfMyUint32Int32Map(600, -300);
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			
			obj1.putTo_MapOfMyUint32Int32Map(700, -400);
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			
			obj1.putTo_MapOfMyUint32Int32Map(800, -500);
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			{
				std::map<uint32_t, uint32_t> myExternalMap;
				myExternalMap[600] = 600;
				myExternalMap[700] = 700;
				myExternalMap[800] = 800;
			
				obj1.clear_MapOfMyUint32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			
				obj1.setMapOfMyUint32Uint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(800));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			
				obj1.clear_MapOfMyUint32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			}
			obj1.putTo_MapOfMyUint32Uint32Map(600, 600);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			
			obj1.putTo_MapOfMyUint32Uint32Map(700, 700);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			
			obj1.putTo_MapOfMyUint32Uint32Map(800, 800);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			{
				std::map<uint32_t, float> myExternalMap;
				myExternalMap[600] = 4.5;
				myExternalMap[700] = 5.5;
				myExternalMap[800] = 6.5;
			
				obj1.clear_MapOfMyUint32FloatMap();
				TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			
				obj1.setMapOfMyUint32FloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(800));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			
				obj1.clear_MapOfMyUint32FloatMap();
				TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			}
			obj1.putTo_MapOfMyUint32FloatMap(600, 4.5);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			
			obj1.putTo_MapOfMyUint32FloatMap(700, 5.5);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			
			obj1.putTo_MapOfMyUint32FloatMap(800, 6.5);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			{
				std::map<uint32_t, double> myExternalMap;
				myExternalMap[600] = 1.0;
				myExternalMap[700] = 2.0;
				myExternalMap[800] = 3.0;
			
				obj1.clear_MapOfMyUint32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			
				obj1.setMapOfMyUint32DoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(800));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			
				obj1.clear_MapOfMyUint32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			}
			obj1.putTo_MapOfMyUint32DoubleMap(600, 1.0);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			
			obj1.putTo_MapOfMyUint32DoubleMap(700, 2.0);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			
			obj1.putTo_MapOfMyUint32DoubleMap(800, 3.0);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			{
				std::map<uint32_t, std::string> myExternalMap;
				myExternalMap[600] = "Hello World!";
				myExternalMap[700] = "Hello Solar System!";
				myExternalMap[800] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyUint32StringMap();
				TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			
				obj1.setMapOfMyUint32StringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(700), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(800));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(800), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyUint32StringMap();
				TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			}
			obj1.putTo_MapOfMyUint32StringMap(600, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			
			obj1.putTo_MapOfMyUint32StringMap(700, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(700), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			
			obj1.putTo_MapOfMyUint32StringMap(800, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(700), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(800));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(800), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32StringMap(600) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32StringMap(700) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32StringMap(800) == "Hello Milky Way!");
		}
	
		void testCreateAndCopyObject() {
	
			Test12MapUint32 obj1;
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap());
	
			Test12MapUint32 obj2(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == obj2.getSize_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap() == obj2.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == obj2.getSize_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap() == obj2.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == obj2.getSize_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map() == obj2.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == obj2.getSize_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map() == obj2.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == obj2.getSize_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap() == obj2.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == obj2.getSize_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap() == obj2.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == obj2.getSize_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap() == obj2.isEmpty_MapOfMyUint32StringMap());
	
			{
				std::map<uint32_t, bool> myExternalMap;
				myExternalMap[600] = true;
				myExternalMap[700] = false;
			
				obj1.clear_MapOfMyUint32BoolMap();
				TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(700));
			
				obj1.setMapOfMyUint32BoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			
				obj1.clear_MapOfMyUint32BoolMap();
				TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(700));
			}
			obj1.putTo_MapOfMyUint32BoolMap(600, true);
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(700));
			
			obj1.putTo_MapOfMyUint32BoolMap(700, false);
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			
			{
				std::map<uint32_t, char> myExternalMap;
				myExternalMap[600] = 'd';
				myExternalMap[700] = 'e';
				myExternalMap[800] = 'f';
			
				obj1.clear_MapOfMyUint32CharMap();
				TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			
				obj1.setMapOfMyUint32CharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(800));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			
				obj1.clear_MapOfMyUint32CharMap();
				TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			}
			obj1.putTo_MapOfMyUint32CharMap(600, 'd');
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			
			obj1.putTo_MapOfMyUint32CharMap(700, 'e');
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			
			obj1.putTo_MapOfMyUint32CharMap(800, 'f');
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			{
				std::map<uint32_t, int32_t> myExternalMap;
				myExternalMap[600] = -300;
				myExternalMap[700] = -400;
				myExternalMap[800] = -500;
			
				obj1.clear_MapOfMyUint32Int32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			
				obj1.setMapOfMyUint32Int32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(800));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			
				obj1.clear_MapOfMyUint32Int32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			}
			obj1.putTo_MapOfMyUint32Int32Map(600, -300);
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			
			obj1.putTo_MapOfMyUint32Int32Map(700, -400);
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			
			obj1.putTo_MapOfMyUint32Int32Map(800, -500);
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			{
				std::map<uint32_t, uint32_t> myExternalMap;
				myExternalMap[600] = 600;
				myExternalMap[700] = 700;
				myExternalMap[800] = 800;
			
				obj1.clear_MapOfMyUint32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			
				obj1.setMapOfMyUint32Uint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(800));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			
				obj1.clear_MapOfMyUint32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			}
			obj1.putTo_MapOfMyUint32Uint32Map(600, 600);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			
			obj1.putTo_MapOfMyUint32Uint32Map(700, 700);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			
			obj1.putTo_MapOfMyUint32Uint32Map(800, 800);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			{
				std::map<uint32_t, float> myExternalMap;
				myExternalMap[600] = 4.5;
				myExternalMap[700] = 5.5;
				myExternalMap[800] = 6.5;
			
				obj1.clear_MapOfMyUint32FloatMap();
				TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			
				obj1.setMapOfMyUint32FloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(800));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			
				obj1.clear_MapOfMyUint32FloatMap();
				TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			}
			obj1.putTo_MapOfMyUint32FloatMap(600, 4.5);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			
			obj1.putTo_MapOfMyUint32FloatMap(700, 5.5);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			
			obj1.putTo_MapOfMyUint32FloatMap(800, 6.5);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			{
				std::map<uint32_t, double> myExternalMap;
				myExternalMap[600] = 1.0;
				myExternalMap[700] = 2.0;
				myExternalMap[800] = 3.0;
			
				obj1.clear_MapOfMyUint32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			
				obj1.setMapOfMyUint32DoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(800));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			
				obj1.clear_MapOfMyUint32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			}
			obj1.putTo_MapOfMyUint32DoubleMap(600, 1.0);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			
			obj1.putTo_MapOfMyUint32DoubleMap(700, 2.0);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			
			obj1.putTo_MapOfMyUint32DoubleMap(800, 3.0);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			{
				std::map<uint32_t, std::string> myExternalMap;
				myExternalMap[600] = "Hello World!";
				myExternalMap[700] = "Hello Solar System!";
				myExternalMap[800] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyUint32StringMap();
				TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			
				obj1.setMapOfMyUint32StringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(700), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(800));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(800), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyUint32StringMap();
				TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			}
			obj1.putTo_MapOfMyUint32StringMap(600, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			
			obj1.putTo_MapOfMyUint32StringMap(700, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(700), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			
			obj1.putTo_MapOfMyUint32StringMap(800, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(700), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(800));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(800), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32StringMap(600) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32StringMap(700) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32StringMap(800) == "Hello Milky Way!");
	
			Test12MapUint32 obj3(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == obj3.getSize_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap() == obj3.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == obj3.getSize_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap() == obj3.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == obj3.getSize_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map() == obj3.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == obj3.getSize_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map() == obj3.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == obj3.getSize_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap() == obj3.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == obj3.getSize_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap() == obj3.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == obj3.getSize_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap() == obj3.isEmpty_MapOfMyUint32StringMap());
	
			TS_ASSERT(obj3.getMapOfMyUint32BoolMap().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyUint32BoolMap() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(obj3.containsKey_MapOfMyUint32BoolMap(700));
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			TS_ASSERT(obj3.getMapOfMyUint32CharMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyUint32CharMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj3.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(obj3.containsKey_MapOfMyUint32CharMap(800));
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			TS_ASSERT(obj3.getMapOfMyUint32Int32Map().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyUint32Int32Map() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj3.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(obj3.containsKey_MapOfMyUint32Int32Map(800));
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			TS_ASSERT(obj3.getMapOfMyUint32Uint32Map().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyUint32Uint32Map() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj3.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(obj3.containsKey_MapOfMyUint32Uint32Map(800));
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			TS_ASSERT(obj3.getMapOfMyUint32FloatMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyUint32FloatMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyUint32FloatMap(800));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			TS_ASSERT(obj3.getMapOfMyUint32DoubleMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyUint32DoubleMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyUint32DoubleMap(800));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			TS_ASSERT(obj3.getMapOfMyUint32StringMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyUint32StringMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32StringMap(600) == "Hello World!");
			TS_ASSERT(obj3.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32StringMap(700) == "Hello Solar System!");
			TS_ASSERT(obj3.containsKey_MapOfMyUint32StringMap(800));
			TS_ASSERT(obj3.getValueForKey_MapOfMyUint32StringMap(800) == "Hello Milky Way!");
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test12MapUint32 obj1;
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap());
	
			Test12MapUint32 obj2;
			TS_ASSERT(obj2.getMapOfMyUint32BoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32BoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj2.getMapOfMyUint32CharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32CharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj2.getMapOfMyUint32Int32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32Int32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj2.getMapOfMyUint32Uint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32Uint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj2.getMapOfMyUint32FloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32FloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj2.getMapOfMyUint32DoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32DoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj2.getMapOfMyUint32StringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32StringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32StringMap());
	
			{
				std::map<uint32_t, bool> myExternalMap;
				myExternalMap[600] = true;
				myExternalMap[700] = false;
			
				obj1.clear_MapOfMyUint32BoolMap();
				TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(700));
			
				obj1.setMapOfMyUint32BoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			
				obj1.clear_MapOfMyUint32BoolMap();
				TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(700));
			}
			obj1.putTo_MapOfMyUint32BoolMap(600, true);
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(700));
			
			obj1.putTo_MapOfMyUint32BoolMap(700, false);
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			
			{
				std::map<uint32_t, char> myExternalMap;
				myExternalMap[600] = 'd';
				myExternalMap[700] = 'e';
				myExternalMap[800] = 'f';
			
				obj1.clear_MapOfMyUint32CharMap();
				TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			
				obj1.setMapOfMyUint32CharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(800));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			
				obj1.clear_MapOfMyUint32CharMap();
				TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			}
			obj1.putTo_MapOfMyUint32CharMap(600, 'd');
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			
			obj1.putTo_MapOfMyUint32CharMap(700, 'e');
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			
			obj1.putTo_MapOfMyUint32CharMap(800, 'f');
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			{
				std::map<uint32_t, int32_t> myExternalMap;
				myExternalMap[600] = -300;
				myExternalMap[700] = -400;
				myExternalMap[800] = -500;
			
				obj1.clear_MapOfMyUint32Int32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			
				obj1.setMapOfMyUint32Int32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(800));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			
				obj1.clear_MapOfMyUint32Int32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			}
			obj1.putTo_MapOfMyUint32Int32Map(600, -300);
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			
			obj1.putTo_MapOfMyUint32Int32Map(700, -400);
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			
			obj1.putTo_MapOfMyUint32Int32Map(800, -500);
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			{
				std::map<uint32_t, uint32_t> myExternalMap;
				myExternalMap[600] = 600;
				myExternalMap[700] = 700;
				myExternalMap[800] = 800;
			
				obj1.clear_MapOfMyUint32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			
				obj1.setMapOfMyUint32Uint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(800));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			
				obj1.clear_MapOfMyUint32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			}
			obj1.putTo_MapOfMyUint32Uint32Map(600, 600);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			
			obj1.putTo_MapOfMyUint32Uint32Map(700, 700);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			
			obj1.putTo_MapOfMyUint32Uint32Map(800, 800);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			{
				std::map<uint32_t, float> myExternalMap;
				myExternalMap[600] = 4.5;
				myExternalMap[700] = 5.5;
				myExternalMap[800] = 6.5;
			
				obj1.clear_MapOfMyUint32FloatMap();
				TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			
				obj1.setMapOfMyUint32FloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(800));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			
				obj1.clear_MapOfMyUint32FloatMap();
				TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			}
			obj1.putTo_MapOfMyUint32FloatMap(600, 4.5);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			
			obj1.putTo_MapOfMyUint32FloatMap(700, 5.5);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			
			obj1.putTo_MapOfMyUint32FloatMap(800, 6.5);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			{
				std::map<uint32_t, double> myExternalMap;
				myExternalMap[600] = 1.0;
				myExternalMap[700] = 2.0;
				myExternalMap[800] = 3.0;
			
				obj1.clear_MapOfMyUint32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			
				obj1.setMapOfMyUint32DoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(800));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			
				obj1.clear_MapOfMyUint32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			}
			obj1.putTo_MapOfMyUint32DoubleMap(600, 1.0);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			
			obj1.putTo_MapOfMyUint32DoubleMap(700, 2.0);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			
			obj1.putTo_MapOfMyUint32DoubleMap(800, 3.0);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			{
				std::map<uint32_t, std::string> myExternalMap;
				myExternalMap[600] = "Hello World!";
				myExternalMap[700] = "Hello Solar System!";
				myExternalMap[800] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyUint32StringMap();
				TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			
				obj1.setMapOfMyUint32StringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(700), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(800));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(800), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyUint32StringMap();
				TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			}
			obj1.putTo_MapOfMyUint32StringMap(600, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			
			obj1.putTo_MapOfMyUint32StringMap(700, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(700), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			
			obj1.putTo_MapOfMyUint32StringMap(800, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(700), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(800));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(800), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32StringMap(600) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32StringMap(700) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32StringMap(800) == "Hello Milky Way!");
	
			obj2 = obj1;
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == obj2.getSize_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap() == obj2.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == obj2.getSize_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap() == obj2.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == obj2.getSize_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map() == obj2.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == obj2.getSize_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map() == obj2.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == obj2.getSize_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap() == obj2.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == obj2.getSize_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap() == obj2.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == obj2.getSize_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap() == obj2.isEmpty_MapOfMyUint32StringMap());
	
			TS_ASSERT(obj2.getMapOfMyUint32BoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyUint32BoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32BoolMap(700));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			TS_ASSERT(obj2.getMapOfMyUint32CharMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyUint32CharMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(obj2.containsKey_MapOfMyUint32CharMap(800));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			TS_ASSERT(obj2.getMapOfMyUint32Int32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyUint32Int32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32Int32Map(800));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			TS_ASSERT(obj2.getMapOfMyUint32Uint32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyUint32Uint32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32Uint32Map(800));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			TS_ASSERT(obj2.getMapOfMyUint32FloatMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyUint32FloatMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32FloatMap(800));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyUint32DoubleMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyUint32DoubleMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32DoubleMap(800));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyUint32StringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyUint32StringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32StringMap(600) == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32StringMap(700) == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyUint32StringMap(800));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32StringMap(800) == "Hello Milky Way!");
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test12MapUint32 obj1;
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap());
	
			Test12MapUint32 obj2;
			TS_ASSERT(obj2.getMapOfMyUint32BoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32BoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj2.getMapOfMyUint32CharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32CharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj2.getMapOfMyUint32Int32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32Int32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj2.getMapOfMyUint32Uint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32Uint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj2.getMapOfMyUint32FloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32FloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj2.getMapOfMyUint32DoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32DoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj2.getMapOfMyUint32StringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyUint32StringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyUint32StringMap());
	
			{
				std::map<uint32_t, bool> myExternalMap;
				myExternalMap[600] = true;
				myExternalMap[700] = false;
			
				obj1.clear_MapOfMyUint32BoolMap();
				TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(700));
			
				obj1.setMapOfMyUint32BoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			
				obj1.clear_MapOfMyUint32BoolMap();
				TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(700));
			}
			obj1.putTo_MapOfMyUint32BoolMap(600, true);
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32BoolMap(700));
			
			obj1.putTo_MapOfMyUint32BoolMap(700, false);
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			
			{
				std::map<uint32_t, char> myExternalMap;
				myExternalMap[600] = 'd';
				myExternalMap[700] = 'e';
				myExternalMap[800] = 'f';
			
				obj1.clear_MapOfMyUint32CharMap();
				TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			
				obj1.setMapOfMyUint32CharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(800));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			
				obj1.clear_MapOfMyUint32CharMap();
				TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			}
			obj1.putTo_MapOfMyUint32CharMap(600, 'd');
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			
			obj1.putTo_MapOfMyUint32CharMap(700, 'e');
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32CharMap(800));
			
			obj1.putTo_MapOfMyUint32CharMap(800, 'f');
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			{
				std::map<uint32_t, int32_t> myExternalMap;
				myExternalMap[600] = -300;
				myExternalMap[700] = -400;
				myExternalMap[800] = -500;
			
				obj1.clear_MapOfMyUint32Int32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			
				obj1.setMapOfMyUint32Int32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(800));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			
				obj1.clear_MapOfMyUint32Int32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			}
			obj1.putTo_MapOfMyUint32Int32Map(600, -300);
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			
			obj1.putTo_MapOfMyUint32Int32Map(700, -400);
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Int32Map(800));
			
			obj1.putTo_MapOfMyUint32Int32Map(800, -500);
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			{
				std::map<uint32_t, uint32_t> myExternalMap;
				myExternalMap[600] = 600;
				myExternalMap[700] = 700;
				myExternalMap[800] = 800;
			
				obj1.clear_MapOfMyUint32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			
				obj1.setMapOfMyUint32Uint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(800));
				TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			
				obj1.clear_MapOfMyUint32Uint32Map();
				TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			}
			obj1.putTo_MapOfMyUint32Uint32Map(600, 600);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			
			obj1.putTo_MapOfMyUint32Uint32Map(700, 700);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32Uint32Map(800));
			
			obj1.putTo_MapOfMyUint32Uint32Map(800, 800);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(600));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			{
				std::map<uint32_t, float> myExternalMap;
				myExternalMap[600] = 4.5;
				myExternalMap[700] = 5.5;
				myExternalMap[800] = 6.5;
			
				obj1.clear_MapOfMyUint32FloatMap();
				TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			
				obj1.setMapOfMyUint32FloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(800));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			
				obj1.clear_MapOfMyUint32FloatMap();
				TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			}
			obj1.putTo_MapOfMyUint32FloatMap(600, 4.5);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			
			obj1.putTo_MapOfMyUint32FloatMap(700, 5.5);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32FloatMap(800));
			
			obj1.putTo_MapOfMyUint32FloatMap(800, 6.5);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			{
				std::map<uint32_t, double> myExternalMap;
				myExternalMap[600] = 1.0;
				myExternalMap[700] = 2.0;
				myExternalMap[800] = 3.0;
			
				obj1.clear_MapOfMyUint32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			
				obj1.setMapOfMyUint32DoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(800));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			
				obj1.clear_MapOfMyUint32DoubleMap();
				TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			}
			obj1.putTo_MapOfMyUint32DoubleMap(600, 1.0);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			
			obj1.putTo_MapOfMyUint32DoubleMap(700, 2.0);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32DoubleMap(800));
			
			obj1.putTo_MapOfMyUint32DoubleMap(800, 3.0);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(600));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			{
				std::map<uint32_t, std::string> myExternalMap;
				myExternalMap[600] = "Hello World!";
				myExternalMap[700] = "Hello Solar System!";
				myExternalMap[800] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyUint32StringMap();
				TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			
				obj1.setMapOfMyUint32StringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(700), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(800));
				TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(800), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyUint32StringMap();
				TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(600));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(700));
				TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			}
			obj1.putTo_MapOfMyUint32StringMap(600, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			
			obj1.putTo_MapOfMyUint32StringMap(700, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(700), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyUint32StringMap(800));
			
			obj1.putTo_MapOfMyUint32StringMap(800, "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(600));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(600), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(700), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(800));
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyUint32StringMap(800), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyUint32BoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32BoolMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			TS_ASSERT(obj1.getMapOfMyUint32CharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyUint32CharMap(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			TS_ASSERT(obj1.getMapOfMyUint32Int32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Int32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			TS_ASSERT(obj1.getMapOfMyUint32Uint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32Uint32Map(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			TS_ASSERT(obj1.getMapOfMyUint32FloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32FloatMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyUint32DoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyUint32DoubleMap(800));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyUint32StringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32StringMap(600) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32StringMap(700) == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyUint32StringMap(800));
			TS_ASSERT(obj1.getValueForKey_MapOfMyUint32StringMap(800) == "Hello Milky Way!");
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getSize_MapOfMyUint32BoolMap() == obj2.getSize_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32BoolMap() == obj2.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32CharMap() == obj2.getSize_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32CharMap() == obj2.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32Int32Map() == obj2.getSize_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Int32Map() == obj2.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj1.getSize_MapOfMyUint32Uint32Map() == obj2.getSize_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32Uint32Map() == obj2.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyUint32FloatMap() == obj2.getSize_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32FloatMap() == obj2.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32DoubleMap() == obj2.getSize_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32DoubleMap() == obj2.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyUint32StringMap() == obj2.getSize_MapOfMyUint32StringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyUint32StringMap() == obj2.isEmpty_MapOfMyUint32StringMap());
	
			TS_ASSERT(obj2.getMapOfMyUint32BoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyUint32BoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32BoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32BoolMap(600) == true);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32BoolMap(700));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32BoolMap(700) == false);
			TS_ASSERT(obj2.getMapOfMyUint32CharMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyUint32CharMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32CharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32CharMap(600) == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyUint32CharMap(700));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32CharMap(700) == 'e');
			TS_ASSERT(obj2.containsKey_MapOfMyUint32CharMap(800));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32CharMap(800) == 'f');
			TS_ASSERT(obj2.getMapOfMyUint32Int32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyUint32Int32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32Int32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32Int32Map(600) == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32Int32Map(700));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32Int32Map(700) == -400);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32Int32Map(800));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32Int32Map(800) == -500);
			TS_ASSERT(obj2.getMapOfMyUint32Uint32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyUint32Uint32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32Uint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32Uint32Map(600) == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32Uint32Map(700));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32Uint32Map(700) == 700);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32Uint32Map(800));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32Uint32Map(800) == 800);
			TS_ASSERT(obj2.getMapOfMyUint32FloatMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyUint32FloatMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32FloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyUint32FloatMap(600), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32FloatMap(700));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyUint32FloatMap(700), 5.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32FloatMap(800));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyUint32FloatMap(800), 6.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyUint32DoubleMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyUint32DoubleMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32DoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyUint32DoubleMap(600), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32DoubleMap(700));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyUint32DoubleMap(700), 2.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyUint32DoubleMap(800));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyUint32DoubleMap(800), 3.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyUint32StringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyUint32StringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyUint32StringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32StringMap(600) == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyUint32StringMap(700));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32StringMap(700) == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyUint32StringMap(800));
			TS_ASSERT(obj2.getValueForKey_MapOfMyUint32StringMap(800) == "Hello Milky Way!");
	
			TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST12MAPUINT32_TESTSUITE_H*/
