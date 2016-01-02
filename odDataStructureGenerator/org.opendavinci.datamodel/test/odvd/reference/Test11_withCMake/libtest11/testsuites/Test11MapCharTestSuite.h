/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST11MAPCHAR_TESTSUITE_H
#define TEST11MAPCHAR_TESTSUITE_H

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


class Test11MapChar_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test11MapChar obj1;
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap());
	
			{
				std::map<char, bool> myExternalMap;
				myExternalMap['d'] = true;
				myExternalMap['e'] = false;
			
				obj1.clear_MapOfMyCharBoolMap();
				TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('e'));
			
				obj1.setMapOfMyCharBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
				TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('e') == false);
			
				obj1.clear_MapOfMyCharBoolMap();
				TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('e'));
			}
			obj1.putTo_MapOfMyCharBoolMap('d', true);
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('e'));
			
			obj1.putTo_MapOfMyCharBoolMap('e', false);
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('e') == false);
			
			{
				std::map<char, char> myExternalMap;
				myExternalMap['d'] = 'd';
				myExternalMap['e'] = 'e';
				myExternalMap['f'] = 'f';
			
				obj1.clear_MapOfMyCharCharMap();
				TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			
				obj1.setMapOfMyCharCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('f'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			
				obj1.clear_MapOfMyCharCharMap();
				TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			}
			obj1.putTo_MapOfMyCharCharMap('d', 'd');
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			
			obj1.putTo_MapOfMyCharCharMap('e', 'e');
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			
			obj1.putTo_MapOfMyCharCharMap('f', 'f');
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			{
				std::map<char, int32_t> myExternalMap;
				myExternalMap['d'] = -300;
				myExternalMap['e'] = -400;
				myExternalMap['f'] = -500;
			
				obj1.clear_MapOfMyCharInt32Map();
				TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			
				obj1.setMapOfMyCharInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('f'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			
				obj1.clear_MapOfMyCharInt32Map();
				TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			}
			obj1.putTo_MapOfMyCharInt32Map('d', -300);
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			
			obj1.putTo_MapOfMyCharInt32Map('e', -400);
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			
			obj1.putTo_MapOfMyCharInt32Map('f', -500);
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			{
				std::map<char, uint32_t> myExternalMap;
				myExternalMap['d'] = 600;
				myExternalMap['e'] = 700;
				myExternalMap['f'] = 800;
			
				obj1.clear_MapOfMyCharUint32Map();
				TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			
				obj1.setMapOfMyCharUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('f'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			
				obj1.clear_MapOfMyCharUint32Map();
				TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			}
			obj1.putTo_MapOfMyCharUint32Map('d', 600);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			
			obj1.putTo_MapOfMyCharUint32Map('e', 700);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			
			obj1.putTo_MapOfMyCharUint32Map('f', 800);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			{
				std::map<char, float> myExternalMap;
				myExternalMap['d'] = 4.5;
				myExternalMap['e'] = 5.5;
				myExternalMap['f'] = 6.5;
			
				obj1.clear_MapOfMyCharFloatMap();
				TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			
				obj1.setMapOfMyCharFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('f'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			
				obj1.clear_MapOfMyCharFloatMap();
				TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			}
			obj1.putTo_MapOfMyCharFloatMap('d', 4.5);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			
			obj1.putTo_MapOfMyCharFloatMap('e', 5.5);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			
			obj1.putTo_MapOfMyCharFloatMap('f', 6.5);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			{
				std::map<char, double> myExternalMap;
				myExternalMap['d'] = 1.0;
				myExternalMap['e'] = 2.0;
				myExternalMap['f'] = 3.0;
			
				obj1.clear_MapOfMyCharDoubleMap();
				TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			
				obj1.setMapOfMyCharDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('f'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			
				obj1.clear_MapOfMyCharDoubleMap();
				TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			}
			obj1.putTo_MapOfMyCharDoubleMap('d', 1.0);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			
			obj1.putTo_MapOfMyCharDoubleMap('e', 2.0);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			
			obj1.putTo_MapOfMyCharDoubleMap('f', 3.0);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			{
				std::map<char, std::string> myExternalMap;
				myExternalMap['d'] = "Hello World!";
				myExternalMap['e'] = "Hello Solar System!";
				myExternalMap['f'] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyCharStringMap();
				TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			
				obj1.setMapOfMyCharStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('e'), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('f'));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('f'), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyCharStringMap();
				TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			}
			obj1.putTo_MapOfMyCharStringMap('d', "Hello World!");
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			
			obj1.putTo_MapOfMyCharStringMap('e', "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('e'), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			
			obj1.putTo_MapOfMyCharStringMap('f', "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('e'), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('f'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('f'), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('e') == false);
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharStringMap('d') == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharStringMap('e') == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharStringMap('f') == "Hello Milky Way!");
		}
	
		void testCreateAndCopyObject() {
	
			Test11MapChar obj1;
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap());
	
			Test11MapChar obj2(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == obj2.getSize_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap() == obj2.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == obj2.getSize_MapOfMyCharCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap() == obj2.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == obj2.getSize_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map() == obj2.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == obj2.getSize_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map() == obj2.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == obj2.getSize_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap() == obj2.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == obj2.getSize_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap() == obj2.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == obj2.getSize_MapOfMyCharStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap() == obj2.isEmpty_MapOfMyCharStringMap());
	
			{
				std::map<char, bool> myExternalMap;
				myExternalMap['d'] = true;
				myExternalMap['e'] = false;
			
				obj1.clear_MapOfMyCharBoolMap();
				TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('e'));
			
				obj1.setMapOfMyCharBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
				TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('e') == false);
			
				obj1.clear_MapOfMyCharBoolMap();
				TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('e'));
			}
			obj1.putTo_MapOfMyCharBoolMap('d', true);
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('e'));
			
			obj1.putTo_MapOfMyCharBoolMap('e', false);
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('e') == false);
			
			{
				std::map<char, char> myExternalMap;
				myExternalMap['d'] = 'd';
				myExternalMap['e'] = 'e';
				myExternalMap['f'] = 'f';
			
				obj1.clear_MapOfMyCharCharMap();
				TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			
				obj1.setMapOfMyCharCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('f'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			
				obj1.clear_MapOfMyCharCharMap();
				TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			}
			obj1.putTo_MapOfMyCharCharMap('d', 'd');
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			
			obj1.putTo_MapOfMyCharCharMap('e', 'e');
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			
			obj1.putTo_MapOfMyCharCharMap('f', 'f');
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			{
				std::map<char, int32_t> myExternalMap;
				myExternalMap['d'] = -300;
				myExternalMap['e'] = -400;
				myExternalMap['f'] = -500;
			
				obj1.clear_MapOfMyCharInt32Map();
				TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			
				obj1.setMapOfMyCharInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('f'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			
				obj1.clear_MapOfMyCharInt32Map();
				TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			}
			obj1.putTo_MapOfMyCharInt32Map('d', -300);
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			
			obj1.putTo_MapOfMyCharInt32Map('e', -400);
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			
			obj1.putTo_MapOfMyCharInt32Map('f', -500);
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			{
				std::map<char, uint32_t> myExternalMap;
				myExternalMap['d'] = 600;
				myExternalMap['e'] = 700;
				myExternalMap['f'] = 800;
			
				obj1.clear_MapOfMyCharUint32Map();
				TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			
				obj1.setMapOfMyCharUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('f'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			
				obj1.clear_MapOfMyCharUint32Map();
				TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			}
			obj1.putTo_MapOfMyCharUint32Map('d', 600);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			
			obj1.putTo_MapOfMyCharUint32Map('e', 700);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			
			obj1.putTo_MapOfMyCharUint32Map('f', 800);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			{
				std::map<char, float> myExternalMap;
				myExternalMap['d'] = 4.5;
				myExternalMap['e'] = 5.5;
				myExternalMap['f'] = 6.5;
			
				obj1.clear_MapOfMyCharFloatMap();
				TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			
				obj1.setMapOfMyCharFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('f'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			
				obj1.clear_MapOfMyCharFloatMap();
				TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			}
			obj1.putTo_MapOfMyCharFloatMap('d', 4.5);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			
			obj1.putTo_MapOfMyCharFloatMap('e', 5.5);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			
			obj1.putTo_MapOfMyCharFloatMap('f', 6.5);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			{
				std::map<char, double> myExternalMap;
				myExternalMap['d'] = 1.0;
				myExternalMap['e'] = 2.0;
				myExternalMap['f'] = 3.0;
			
				obj1.clear_MapOfMyCharDoubleMap();
				TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			
				obj1.setMapOfMyCharDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('f'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			
				obj1.clear_MapOfMyCharDoubleMap();
				TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			}
			obj1.putTo_MapOfMyCharDoubleMap('d', 1.0);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			
			obj1.putTo_MapOfMyCharDoubleMap('e', 2.0);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			
			obj1.putTo_MapOfMyCharDoubleMap('f', 3.0);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			{
				std::map<char, std::string> myExternalMap;
				myExternalMap['d'] = "Hello World!";
				myExternalMap['e'] = "Hello Solar System!";
				myExternalMap['f'] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyCharStringMap();
				TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			
				obj1.setMapOfMyCharStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('e'), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('f'));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('f'), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyCharStringMap();
				TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			}
			obj1.putTo_MapOfMyCharStringMap('d', "Hello World!");
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			
			obj1.putTo_MapOfMyCharStringMap('e', "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('e'), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			
			obj1.putTo_MapOfMyCharStringMap('f', "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('e'), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('f'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('f'), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('e') == false);
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharStringMap('d') == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharStringMap('e') == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharStringMap('f') == "Hello Milky Way!");
	
			Test11MapChar obj3(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == obj3.getSize_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap() == obj3.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == obj3.getSize_MapOfMyCharCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap() == obj3.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == obj3.getSize_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map() == obj3.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == obj3.getSize_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map() == obj3.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == obj3.getSize_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap() == obj3.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == obj3.getSize_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap() == obj3.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == obj3.getSize_MapOfMyCharStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap() == obj3.isEmpty_MapOfMyCharStringMap());
	
			TS_ASSERT(obj3.getMapOfMyCharBoolMap().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyCharBoolMap() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(obj3.containsKey_MapOfMyCharBoolMap('e'));
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharBoolMap('e') == false);
			TS_ASSERT(obj3.getMapOfMyCharCharMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyCharCharMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj3.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(obj3.containsKey_MapOfMyCharCharMap('f'));
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			TS_ASSERT(obj3.getMapOfMyCharInt32Map().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyCharInt32Map() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj3.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(obj3.containsKey_MapOfMyCharInt32Map('f'));
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			TS_ASSERT(obj3.getMapOfMyCharUint32Map().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyCharUint32Map() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj3.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(obj3.containsKey_MapOfMyCharUint32Map('f'));
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			TS_ASSERT(obj3.getMapOfMyCharFloatMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyCharFloatMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyCharFloatMap('f'));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			TS_ASSERT(obj3.getMapOfMyCharDoubleMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyCharDoubleMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyCharDoubleMap('f'));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			TS_ASSERT(obj3.getMapOfMyCharStringMap().size() == 3);
			TS_ASSERT(obj3.getSize_MapOfMyCharStringMap() == 3);
			TS_ASSERT(!obj3.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharStringMap('d') == "Hello World!");
			TS_ASSERT(obj3.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharStringMap('e') == "Hello Solar System!");
			TS_ASSERT(obj3.containsKey_MapOfMyCharStringMap('f'));
			TS_ASSERT(obj3.getValueForKey_MapOfMyCharStringMap('f') == "Hello Milky Way!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test11MapChar obj1;
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap());
	
			Test11MapChar obj2;
			TS_ASSERT(obj2.getMapOfMyCharBoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharBoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj2.getMapOfMyCharCharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharCharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj2.getMapOfMyCharInt32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharInt32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj2.getMapOfMyCharUint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharUint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj2.getMapOfMyCharFloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharFloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj2.getMapOfMyCharDoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharDoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj2.getMapOfMyCharStringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharStringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharStringMap());
	
			{
				std::map<char, bool> myExternalMap;
				myExternalMap['d'] = true;
				myExternalMap['e'] = false;
			
				obj1.clear_MapOfMyCharBoolMap();
				TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('e'));
			
				obj1.setMapOfMyCharBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
				TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('e') == false);
			
				obj1.clear_MapOfMyCharBoolMap();
				TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('e'));
			}
			obj1.putTo_MapOfMyCharBoolMap('d', true);
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('e'));
			
			obj1.putTo_MapOfMyCharBoolMap('e', false);
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('e') == false);
			
			{
				std::map<char, char> myExternalMap;
				myExternalMap['d'] = 'd';
				myExternalMap['e'] = 'e';
				myExternalMap['f'] = 'f';
			
				obj1.clear_MapOfMyCharCharMap();
				TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			
				obj1.setMapOfMyCharCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('f'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			
				obj1.clear_MapOfMyCharCharMap();
				TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			}
			obj1.putTo_MapOfMyCharCharMap('d', 'd');
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			
			obj1.putTo_MapOfMyCharCharMap('e', 'e');
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			
			obj1.putTo_MapOfMyCharCharMap('f', 'f');
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			{
				std::map<char, int32_t> myExternalMap;
				myExternalMap['d'] = -300;
				myExternalMap['e'] = -400;
				myExternalMap['f'] = -500;
			
				obj1.clear_MapOfMyCharInt32Map();
				TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			
				obj1.setMapOfMyCharInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('f'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			
				obj1.clear_MapOfMyCharInt32Map();
				TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			}
			obj1.putTo_MapOfMyCharInt32Map('d', -300);
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			
			obj1.putTo_MapOfMyCharInt32Map('e', -400);
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			
			obj1.putTo_MapOfMyCharInt32Map('f', -500);
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			{
				std::map<char, uint32_t> myExternalMap;
				myExternalMap['d'] = 600;
				myExternalMap['e'] = 700;
				myExternalMap['f'] = 800;
			
				obj1.clear_MapOfMyCharUint32Map();
				TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			
				obj1.setMapOfMyCharUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('f'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			
				obj1.clear_MapOfMyCharUint32Map();
				TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			}
			obj1.putTo_MapOfMyCharUint32Map('d', 600);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			
			obj1.putTo_MapOfMyCharUint32Map('e', 700);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			
			obj1.putTo_MapOfMyCharUint32Map('f', 800);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			{
				std::map<char, float> myExternalMap;
				myExternalMap['d'] = 4.5;
				myExternalMap['e'] = 5.5;
				myExternalMap['f'] = 6.5;
			
				obj1.clear_MapOfMyCharFloatMap();
				TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			
				obj1.setMapOfMyCharFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('f'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			
				obj1.clear_MapOfMyCharFloatMap();
				TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			}
			obj1.putTo_MapOfMyCharFloatMap('d', 4.5);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			
			obj1.putTo_MapOfMyCharFloatMap('e', 5.5);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			
			obj1.putTo_MapOfMyCharFloatMap('f', 6.5);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			{
				std::map<char, double> myExternalMap;
				myExternalMap['d'] = 1.0;
				myExternalMap['e'] = 2.0;
				myExternalMap['f'] = 3.0;
			
				obj1.clear_MapOfMyCharDoubleMap();
				TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			
				obj1.setMapOfMyCharDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('f'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			
				obj1.clear_MapOfMyCharDoubleMap();
				TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			}
			obj1.putTo_MapOfMyCharDoubleMap('d', 1.0);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			
			obj1.putTo_MapOfMyCharDoubleMap('e', 2.0);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			
			obj1.putTo_MapOfMyCharDoubleMap('f', 3.0);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			{
				std::map<char, std::string> myExternalMap;
				myExternalMap['d'] = "Hello World!";
				myExternalMap['e'] = "Hello Solar System!";
				myExternalMap['f'] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyCharStringMap();
				TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			
				obj1.setMapOfMyCharStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('e'), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('f'));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('f'), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyCharStringMap();
				TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			}
			obj1.putTo_MapOfMyCharStringMap('d', "Hello World!");
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			
			obj1.putTo_MapOfMyCharStringMap('e', "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('e'), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			
			obj1.putTo_MapOfMyCharStringMap('f', "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('e'), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('f'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('f'), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('e') == false);
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharStringMap('d') == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharStringMap('e') == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharStringMap('f') == "Hello Milky Way!");
	
			obj2 = obj1;
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == obj2.getSize_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap() == obj2.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == obj2.getSize_MapOfMyCharCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap() == obj2.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == obj2.getSize_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map() == obj2.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == obj2.getSize_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map() == obj2.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == obj2.getSize_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap() == obj2.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == obj2.getSize_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap() == obj2.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == obj2.getSize_MapOfMyCharStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap() == obj2.isEmpty_MapOfMyCharStringMap());
	
			TS_ASSERT(obj2.getMapOfMyCharBoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyCharBoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(obj2.containsKey_MapOfMyCharBoolMap('e'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharBoolMap('e') == false);
			TS_ASSERT(obj2.getMapOfMyCharCharMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyCharCharMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(obj2.containsKey_MapOfMyCharCharMap('f'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			TS_ASSERT(obj2.getMapOfMyCharInt32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyCharInt32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(obj2.containsKey_MapOfMyCharInt32Map('f'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			TS_ASSERT(obj2.getMapOfMyCharUint32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyCharUint32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(obj2.containsKey_MapOfMyCharUint32Map('f'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			TS_ASSERT(obj2.getMapOfMyCharFloatMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyCharFloatMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyCharFloatMap('f'));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyCharDoubleMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyCharDoubleMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyCharDoubleMap('f'));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyCharStringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyCharStringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharStringMap('d') == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharStringMap('e') == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyCharStringMap('f'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharStringMap('f') == "Hello Milky Way!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test11MapChar obj1;
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap());
	
			Test11MapChar obj2;
			TS_ASSERT(obj2.getMapOfMyCharBoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharBoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj2.getMapOfMyCharCharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharCharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj2.getMapOfMyCharInt32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharInt32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj2.getMapOfMyCharUint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharUint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj2.getMapOfMyCharFloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharFloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj2.getMapOfMyCharDoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharDoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj2.getMapOfMyCharStringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyCharStringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyCharStringMap());
	
			{
				std::map<char, bool> myExternalMap;
				myExternalMap['d'] = true;
				myExternalMap['e'] = false;
			
				obj1.clear_MapOfMyCharBoolMap();
				TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('e'));
			
				obj1.setMapOfMyCharBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
				TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('e') == false);
			
				obj1.clear_MapOfMyCharBoolMap();
				TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('e'));
			}
			obj1.putTo_MapOfMyCharBoolMap('d', true);
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharBoolMap('e'));
			
			obj1.putTo_MapOfMyCharBoolMap('e', false);
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('e') == false);
			
			{
				std::map<char, char> myExternalMap;
				myExternalMap['d'] = 'd';
				myExternalMap['e'] = 'e';
				myExternalMap['f'] = 'f';
			
				obj1.clear_MapOfMyCharCharMap();
				TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			
				obj1.setMapOfMyCharCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
				TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('f'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			
				obj1.clear_MapOfMyCharCharMap();
				TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			}
			obj1.putTo_MapOfMyCharCharMap('d', 'd');
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			
			obj1.putTo_MapOfMyCharCharMap('e', 'e');
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(!obj1.containsKey_MapOfMyCharCharMap('f'));
			
			obj1.putTo_MapOfMyCharCharMap('f', 'f');
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			{
				std::map<char, int32_t> myExternalMap;
				myExternalMap['d'] = -300;
				myExternalMap['e'] = -400;
				myExternalMap['f'] = -500;
			
				obj1.clear_MapOfMyCharInt32Map();
				TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			
				obj1.setMapOfMyCharInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
				TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('f'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			
				obj1.clear_MapOfMyCharInt32Map();
				TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			}
			obj1.putTo_MapOfMyCharInt32Map('d', -300);
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			
			obj1.putTo_MapOfMyCharInt32Map('e', -400);
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharInt32Map('f'));
			
			obj1.putTo_MapOfMyCharInt32Map('f', -500);
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			{
				std::map<char, uint32_t> myExternalMap;
				myExternalMap['d'] = 600;
				myExternalMap['e'] = 700;
				myExternalMap['f'] = 800;
			
				obj1.clear_MapOfMyCharUint32Map();
				TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			
				obj1.setMapOfMyCharUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
				TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('f'));
				TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			
				obj1.clear_MapOfMyCharUint32Map();
				TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			}
			obj1.putTo_MapOfMyCharUint32Map('d', 600);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			
			obj1.putTo_MapOfMyCharUint32Map('e', 700);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharUint32Map('f'));
			
			obj1.putTo_MapOfMyCharUint32Map('f', 800);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('d'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			{
				std::map<char, float> myExternalMap;
				myExternalMap['d'] = 4.5;
				myExternalMap['e'] = 5.5;
				myExternalMap['f'] = 6.5;
			
				obj1.clear_MapOfMyCharFloatMap();
				TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			
				obj1.setMapOfMyCharFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('f'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			
				obj1.clear_MapOfMyCharFloatMap();
				TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			}
			obj1.putTo_MapOfMyCharFloatMap('d', 4.5);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			
			obj1.putTo_MapOfMyCharFloatMap('e', 5.5);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharFloatMap('f'));
			
			obj1.putTo_MapOfMyCharFloatMap('f', 6.5);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			{
				std::map<char, double> myExternalMap;
				myExternalMap['d'] = 1.0;
				myExternalMap['e'] = 2.0;
				myExternalMap['f'] = 3.0;
			
				obj1.clear_MapOfMyCharDoubleMap();
				TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			
				obj1.setMapOfMyCharDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('f'));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			
				obj1.clear_MapOfMyCharDoubleMap();
				TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			}
			obj1.putTo_MapOfMyCharDoubleMap('d', 1.0);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			
			obj1.putTo_MapOfMyCharDoubleMap('e', 2.0);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyCharDoubleMap('f'));
			
			obj1.putTo_MapOfMyCharDoubleMap('f', 3.0);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('d'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			{
				std::map<char, std::string> myExternalMap;
				myExternalMap['d'] = "Hello World!";
				myExternalMap['e'] = "Hello Solar System!";
				myExternalMap['f'] = "Hello Milky Way!";
			
				obj1.clear_MapOfMyCharStringMap();
				TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			
				obj1.setMapOfMyCharStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 3);
				TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 3);
				TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('e'), "Hello Solar System!"));
				TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('f'));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('f'), "Hello Milky Way!"));
			
				obj1.clear_MapOfMyCharStringMap();
				TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('d'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('e'));
				TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			}
			obj1.putTo_MapOfMyCharStringMap('d', "Hello World!");
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			
			obj1.putTo_MapOfMyCharStringMap('e', "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('e'), "Hello Solar System!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyCharStringMap('f'));
			
			obj1.putTo_MapOfMyCharStringMap('f', "Hello Milky Way!");
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('d'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('d'), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('e'), "Hello Solar System!"));
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('f'));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyCharStringMap('f'), "Hello Milky Way!"));
	
			TS_ASSERT(obj1.getMapOfMyCharBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(obj1.containsKey_MapOfMyCharBoolMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharBoolMap('e') == false);
			TS_ASSERT(obj1.getMapOfMyCharCharMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(obj1.containsKey_MapOfMyCharCharMap('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			TS_ASSERT(obj1.getMapOfMyCharInt32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(obj1.containsKey_MapOfMyCharInt32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			TS_ASSERT(obj1.getMapOfMyCharUint32Map().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(obj1.containsKey_MapOfMyCharUint32Map('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			TS_ASSERT(obj1.getMapOfMyCharFloatMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharFloatMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyCharDoubleMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyCharDoubleMap('f'));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyCharStringMap().size() == 3);
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == 3);
			TS_ASSERT(!obj1.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharStringMap('d') == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharStringMap('e') == "Hello Solar System!");
			TS_ASSERT(obj1.containsKey_MapOfMyCharStringMap('f'));
			TS_ASSERT(obj1.getValueForKey_MapOfMyCharStringMap('f') == "Hello Milky Way!");
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getSize_MapOfMyCharBoolMap() == obj2.getSize_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharBoolMap() == obj2.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharCharMap() == obj2.getSize_MapOfMyCharCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharCharMap() == obj2.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharInt32Map() == obj2.getSize_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharInt32Map() == obj2.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyCharUint32Map() == obj2.getSize_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharUint32Map() == obj2.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyCharFloatMap() == obj2.getSize_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharFloatMap() == obj2.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharDoubleMap() == obj2.getSize_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharDoubleMap() == obj2.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyCharStringMap() == obj2.getSize_MapOfMyCharStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyCharStringMap() == obj2.isEmpty_MapOfMyCharStringMap());
	
			TS_ASSERT(obj2.getMapOfMyCharBoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyCharBoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharBoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharBoolMap('d') == true);
			TS_ASSERT(obj2.containsKey_MapOfMyCharBoolMap('e'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharBoolMap('e') == false);
			TS_ASSERT(obj2.getMapOfMyCharCharMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyCharCharMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharCharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharCharMap('d') == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyCharCharMap('e'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharCharMap('e') == 'e');
			TS_ASSERT(obj2.containsKey_MapOfMyCharCharMap('f'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharCharMap('f') == 'f');
			TS_ASSERT(obj2.getMapOfMyCharInt32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyCharInt32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharInt32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharInt32Map('d') == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyCharInt32Map('e'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharInt32Map('e') == -400);
			TS_ASSERT(obj2.containsKey_MapOfMyCharInt32Map('f'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharInt32Map('f') == -500);
			TS_ASSERT(obj2.getMapOfMyCharUint32Map().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyCharUint32Map() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharUint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharUint32Map('d') == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyCharUint32Map('e'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharUint32Map('e') == 700);
			TS_ASSERT(obj2.containsKey_MapOfMyCharUint32Map('f'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharUint32Map('f') == 800);
			TS_ASSERT(obj2.getMapOfMyCharFloatMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyCharFloatMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharFloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyCharFloatMap('d'), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyCharFloatMap('e'));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyCharFloatMap('e'), 5.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyCharFloatMap('f'));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyCharFloatMap('f'), 6.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyCharDoubleMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyCharDoubleMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharDoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyCharDoubleMap('d'), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyCharDoubleMap('e'));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyCharDoubleMap('e'), 2.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyCharDoubleMap('f'));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyCharDoubleMap('f'), 3.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyCharStringMap().size() == 3);
			TS_ASSERT(obj2.getSize_MapOfMyCharStringMap() == 3);
			TS_ASSERT(!obj2.isEmpty_MapOfMyCharStringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharStringMap('d') == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyCharStringMap('e'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharStringMap('e') == "Hello Solar System!");
			TS_ASSERT(obj2.containsKey_MapOfMyCharStringMap('f'));
			TS_ASSERT(obj2.getValueForKey_MapOfMyCharStringMap('f') == "Hello Milky Way!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST11MAPCHAR_TESTSUITE_H*/
