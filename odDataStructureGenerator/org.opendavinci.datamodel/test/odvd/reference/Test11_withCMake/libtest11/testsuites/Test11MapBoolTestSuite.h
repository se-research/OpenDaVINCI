/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST11MAPBOOL_TESTSUITE_H
#define TEST11MAPBOOL_TESTSUITE_H

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


class Test11MapBool_TestSuite : public CxxTest::TestSuite {

	public:
		void testCreateObject() {
	
			Test11MapBool obj1;
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap());
	
			{
				std::map<bool, bool> myExternalMap;
				myExternalMap[true] = true;
				myExternalMap[false] = false;
			
				obj1.clear_MapOfMyBoolBoolMap();
				TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(false));
			
				obj1.setMapOfMyBoolBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			
				obj1.clear_MapOfMyBoolBoolMap();
				TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(false));
			}
			obj1.putTo_MapOfMyBoolBoolMap(true, true);
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(false));
			
			obj1.putTo_MapOfMyBoolBoolMap(false, false);
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			
			{
				std::map<bool, char> myExternalMap;
				myExternalMap[true] = 'd';
				myExternalMap[false] = 'e';
			
				obj1.clear_MapOfMyBoolCharMap();
				TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(false));
			
				obj1.setMapOfMyBoolCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			
				obj1.clear_MapOfMyBoolCharMap();
				TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(false));
			}
			obj1.putTo_MapOfMyBoolCharMap(true, 'd');
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(false));
			
			obj1.putTo_MapOfMyBoolCharMap(false, 'e');
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			
			{
				std::map<bool, int32_t> myExternalMap;
				myExternalMap[true] = -300;
				myExternalMap[false] = -400;
			
				obj1.clear_MapOfMyBoolInt32Map();
				TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(false));
			
				obj1.setMapOfMyBoolInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			
				obj1.clear_MapOfMyBoolInt32Map();
				TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(false));
			}
			obj1.putTo_MapOfMyBoolInt32Map(true, -300);
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(false));
			
			obj1.putTo_MapOfMyBoolInt32Map(false, -400);
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			
			{
				std::map<bool, uint32_t> myExternalMap;
				myExternalMap[true] = 600;
				myExternalMap[false] = 700;
			
				obj1.clear_MapOfMyBoolUint32Map();
				TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(false));
			
				obj1.setMapOfMyBoolUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			
				obj1.clear_MapOfMyBoolUint32Map();
				TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(false));
			}
			obj1.putTo_MapOfMyBoolUint32Map(true, 600);
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(false));
			
			obj1.putTo_MapOfMyBoolUint32Map(false, 700);
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			
			{
				std::map<bool, float> myExternalMap;
				myExternalMap[true] = 4.5;
				myExternalMap[false] = 5.5;
			
				obj1.clear_MapOfMyBoolFloatMap();
				TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(false));
			
				obj1.setMapOfMyBoolFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(true));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(false));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			
				obj1.clear_MapOfMyBoolFloatMap();
				TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(false));
			}
			obj1.putTo_MapOfMyBoolFloatMap(true, 4.5);
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(false));
			
			obj1.putTo_MapOfMyBoolFloatMap(false, 5.5);
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			
			{
				std::map<bool, double> myExternalMap;
				myExternalMap[true] = 1.0;
				myExternalMap[false] = 2.0;
			
				obj1.clear_MapOfMyBoolDoubleMap();
				TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(false));
			
				obj1.setMapOfMyBoolDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(true));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(false));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			
				obj1.clear_MapOfMyBoolDoubleMap();
				TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(false));
			}
			obj1.putTo_MapOfMyBoolDoubleMap(true, 1.0);
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(false));
			
			obj1.putTo_MapOfMyBoolDoubleMap(false, 2.0);
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			
			{
				std::map<bool, std::string> myExternalMap;
				myExternalMap[true] = "Hello World!";
				myExternalMap[false] = "Hello Solar System!";
			
				obj1.clear_MapOfMyBoolStringMap();
				TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(false));
			
				obj1.setMapOfMyBoolStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(true));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(true), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(false));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(false), "Hello Solar System!"));
			
				obj1.clear_MapOfMyBoolStringMap();
				TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(false));
			}
			obj1.putTo_MapOfMyBoolStringMap(true, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(true));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(true), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(false));
			
			obj1.putTo_MapOfMyBoolStringMap(false, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(true));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(true), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(false));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(false), "Hello Solar System!"));
			
	
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolStringMap(true) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolStringMap(false) == "Hello Solar System!");
		}
	
		void testCreateAndCopyObject() {
	
			Test11MapBool obj1;
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap());
	
			Test11MapBool obj2(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == obj2.getSize_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap() == obj2.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == obj2.getSize_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap() == obj2.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == obj2.getSize_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map() == obj2.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == obj2.getSize_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map() == obj2.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == obj2.getSize_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap() == obj2.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == obj2.getSize_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap() == obj2.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == obj2.getSize_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap() == obj2.isEmpty_MapOfMyBoolStringMap());
	
			{
				std::map<bool, bool> myExternalMap;
				myExternalMap[true] = true;
				myExternalMap[false] = false;
			
				obj1.clear_MapOfMyBoolBoolMap();
				TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(false));
			
				obj1.setMapOfMyBoolBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			
				obj1.clear_MapOfMyBoolBoolMap();
				TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(false));
			}
			obj1.putTo_MapOfMyBoolBoolMap(true, true);
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(false));
			
			obj1.putTo_MapOfMyBoolBoolMap(false, false);
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			
			{
				std::map<bool, char> myExternalMap;
				myExternalMap[true] = 'd';
				myExternalMap[false] = 'e';
			
				obj1.clear_MapOfMyBoolCharMap();
				TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(false));
			
				obj1.setMapOfMyBoolCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			
				obj1.clear_MapOfMyBoolCharMap();
				TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(false));
			}
			obj1.putTo_MapOfMyBoolCharMap(true, 'd');
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(false));
			
			obj1.putTo_MapOfMyBoolCharMap(false, 'e');
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			
			{
				std::map<bool, int32_t> myExternalMap;
				myExternalMap[true] = -300;
				myExternalMap[false] = -400;
			
				obj1.clear_MapOfMyBoolInt32Map();
				TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(false));
			
				obj1.setMapOfMyBoolInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			
				obj1.clear_MapOfMyBoolInt32Map();
				TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(false));
			}
			obj1.putTo_MapOfMyBoolInt32Map(true, -300);
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(false));
			
			obj1.putTo_MapOfMyBoolInt32Map(false, -400);
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			
			{
				std::map<bool, uint32_t> myExternalMap;
				myExternalMap[true] = 600;
				myExternalMap[false] = 700;
			
				obj1.clear_MapOfMyBoolUint32Map();
				TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(false));
			
				obj1.setMapOfMyBoolUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			
				obj1.clear_MapOfMyBoolUint32Map();
				TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(false));
			}
			obj1.putTo_MapOfMyBoolUint32Map(true, 600);
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(false));
			
			obj1.putTo_MapOfMyBoolUint32Map(false, 700);
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			
			{
				std::map<bool, float> myExternalMap;
				myExternalMap[true] = 4.5;
				myExternalMap[false] = 5.5;
			
				obj1.clear_MapOfMyBoolFloatMap();
				TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(false));
			
				obj1.setMapOfMyBoolFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(true));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(false));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			
				obj1.clear_MapOfMyBoolFloatMap();
				TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(false));
			}
			obj1.putTo_MapOfMyBoolFloatMap(true, 4.5);
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(false));
			
			obj1.putTo_MapOfMyBoolFloatMap(false, 5.5);
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			
			{
				std::map<bool, double> myExternalMap;
				myExternalMap[true] = 1.0;
				myExternalMap[false] = 2.0;
			
				obj1.clear_MapOfMyBoolDoubleMap();
				TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(false));
			
				obj1.setMapOfMyBoolDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(true));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(false));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			
				obj1.clear_MapOfMyBoolDoubleMap();
				TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(false));
			}
			obj1.putTo_MapOfMyBoolDoubleMap(true, 1.0);
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(false));
			
			obj1.putTo_MapOfMyBoolDoubleMap(false, 2.0);
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			
			{
				std::map<bool, std::string> myExternalMap;
				myExternalMap[true] = "Hello World!";
				myExternalMap[false] = "Hello Solar System!";
			
				obj1.clear_MapOfMyBoolStringMap();
				TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(false));
			
				obj1.setMapOfMyBoolStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(true));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(true), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(false));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(false), "Hello Solar System!"));
			
				obj1.clear_MapOfMyBoolStringMap();
				TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(false));
			}
			obj1.putTo_MapOfMyBoolStringMap(true, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(true));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(true), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(false));
			
			obj1.putTo_MapOfMyBoolStringMap(false, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(true));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(true), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(false));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(false), "Hello Solar System!"));
			
	
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolStringMap(true) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolStringMap(false) == "Hello Solar System!");
	
			Test11MapBool obj3(obj1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == obj3.getSize_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap() == obj3.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == obj3.getSize_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap() == obj3.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == obj3.getSize_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map() == obj3.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == obj3.getSize_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map() == obj3.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == obj3.getSize_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap() == obj3.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == obj3.getSize_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap() == obj3.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == obj3.getSize_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap() == obj3.isEmpty_MapOfMyBoolStringMap());
	
			TS_ASSERT(obj3.getMapOfMyBoolBoolMap().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyBoolBoolMap() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(obj3.containsKey_MapOfMyBoolBoolMap(false));
			TS_ASSERT(obj3.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			TS_ASSERT(obj3.getMapOfMyBoolCharMap().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyBoolCharMap() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(obj3.containsKey_MapOfMyBoolCharMap(false));
			TS_ASSERT(obj3.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			TS_ASSERT(obj3.getMapOfMyBoolInt32Map().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyBoolInt32Map() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(obj3.containsKey_MapOfMyBoolInt32Map(false));
			TS_ASSERT(obj3.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			TS_ASSERT(obj3.getMapOfMyBoolUint32Map().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyBoolUint32Map() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj3.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(obj3.containsKey_MapOfMyBoolUint32Map(false));
			TS_ASSERT(obj3.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			TS_ASSERT(obj3.getMapOfMyBoolFloatMap().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyBoolFloatMap() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyBoolFloatMap(false));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			TS_ASSERT(obj3.getMapOfMyBoolDoubleMap().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyBoolDoubleMap() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(obj3.containsKey_MapOfMyBoolDoubleMap(false));
			TS_ASSERT_DELTA(obj3.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			TS_ASSERT(obj3.getMapOfMyBoolStringMap().size() == 2);
			TS_ASSERT(obj3.getSize_MapOfMyBoolStringMap() == 2);
			TS_ASSERT(!obj3.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj3.getValueForKey_MapOfMyBoolStringMap(true) == "Hello World!");
			TS_ASSERT(obj3.containsKey_MapOfMyBoolStringMap(false));
			TS_ASSERT(obj3.getValueForKey_MapOfMyBoolStringMap(false) == "Hello Solar System!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj3.toString()));
		}
	
		void testCreateAndAssignObject() {
	
			Test11MapBool obj1;
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap());
	
			Test11MapBool obj2;
			TS_ASSERT(obj2.getMapOfMyBoolBoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolBoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj2.getMapOfMyBoolCharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolCharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj2.getMapOfMyBoolInt32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolInt32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj2.getMapOfMyBoolUint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolUint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj2.getMapOfMyBoolFloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolFloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj2.getMapOfMyBoolDoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolDoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj2.getMapOfMyBoolStringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolStringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolStringMap());
	
			{
				std::map<bool, bool> myExternalMap;
				myExternalMap[true] = true;
				myExternalMap[false] = false;
			
				obj1.clear_MapOfMyBoolBoolMap();
				TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(false));
			
				obj1.setMapOfMyBoolBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			
				obj1.clear_MapOfMyBoolBoolMap();
				TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(false));
			}
			obj1.putTo_MapOfMyBoolBoolMap(true, true);
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(false));
			
			obj1.putTo_MapOfMyBoolBoolMap(false, false);
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			
			{
				std::map<bool, char> myExternalMap;
				myExternalMap[true] = 'd';
				myExternalMap[false] = 'e';
			
				obj1.clear_MapOfMyBoolCharMap();
				TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(false));
			
				obj1.setMapOfMyBoolCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			
				obj1.clear_MapOfMyBoolCharMap();
				TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(false));
			}
			obj1.putTo_MapOfMyBoolCharMap(true, 'd');
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(false));
			
			obj1.putTo_MapOfMyBoolCharMap(false, 'e');
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			
			{
				std::map<bool, int32_t> myExternalMap;
				myExternalMap[true] = -300;
				myExternalMap[false] = -400;
			
				obj1.clear_MapOfMyBoolInt32Map();
				TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(false));
			
				obj1.setMapOfMyBoolInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			
				obj1.clear_MapOfMyBoolInt32Map();
				TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(false));
			}
			obj1.putTo_MapOfMyBoolInt32Map(true, -300);
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(false));
			
			obj1.putTo_MapOfMyBoolInt32Map(false, -400);
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			
			{
				std::map<bool, uint32_t> myExternalMap;
				myExternalMap[true] = 600;
				myExternalMap[false] = 700;
			
				obj1.clear_MapOfMyBoolUint32Map();
				TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(false));
			
				obj1.setMapOfMyBoolUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			
				obj1.clear_MapOfMyBoolUint32Map();
				TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(false));
			}
			obj1.putTo_MapOfMyBoolUint32Map(true, 600);
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(false));
			
			obj1.putTo_MapOfMyBoolUint32Map(false, 700);
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			
			{
				std::map<bool, float> myExternalMap;
				myExternalMap[true] = 4.5;
				myExternalMap[false] = 5.5;
			
				obj1.clear_MapOfMyBoolFloatMap();
				TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(false));
			
				obj1.setMapOfMyBoolFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(true));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(false));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			
				obj1.clear_MapOfMyBoolFloatMap();
				TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(false));
			}
			obj1.putTo_MapOfMyBoolFloatMap(true, 4.5);
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(false));
			
			obj1.putTo_MapOfMyBoolFloatMap(false, 5.5);
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			
			{
				std::map<bool, double> myExternalMap;
				myExternalMap[true] = 1.0;
				myExternalMap[false] = 2.0;
			
				obj1.clear_MapOfMyBoolDoubleMap();
				TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(false));
			
				obj1.setMapOfMyBoolDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(true));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(false));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			
				obj1.clear_MapOfMyBoolDoubleMap();
				TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(false));
			}
			obj1.putTo_MapOfMyBoolDoubleMap(true, 1.0);
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(false));
			
			obj1.putTo_MapOfMyBoolDoubleMap(false, 2.0);
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			
			{
				std::map<bool, std::string> myExternalMap;
				myExternalMap[true] = "Hello World!";
				myExternalMap[false] = "Hello Solar System!";
			
				obj1.clear_MapOfMyBoolStringMap();
				TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(false));
			
				obj1.setMapOfMyBoolStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(true));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(true), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(false));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(false), "Hello Solar System!"));
			
				obj1.clear_MapOfMyBoolStringMap();
				TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(false));
			}
			obj1.putTo_MapOfMyBoolStringMap(true, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(true));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(true), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(false));
			
			obj1.putTo_MapOfMyBoolStringMap(false, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(true));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(true), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(false));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(false), "Hello Solar System!"));
			
	
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolStringMap(true) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolStringMap(false) == "Hello Solar System!");
	
			obj2 = obj1;
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == obj2.getSize_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap() == obj2.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == obj2.getSize_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap() == obj2.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == obj2.getSize_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map() == obj2.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == obj2.getSize_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map() == obj2.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == obj2.getSize_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap() == obj2.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == obj2.getSize_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap() == obj2.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == obj2.getSize_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap() == obj2.isEmpty_MapOfMyBoolStringMap());
	
			TS_ASSERT(obj2.getMapOfMyBoolBoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolBoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(obj2.containsKey_MapOfMyBoolBoolMap(false));
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			TS_ASSERT(obj2.getMapOfMyBoolCharMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolCharMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyBoolCharMap(false));
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			TS_ASSERT(obj2.getMapOfMyBoolInt32Map().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolInt32Map() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyBoolInt32Map(false));
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			TS_ASSERT(obj2.getMapOfMyBoolUint32Map().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolUint32Map() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyBoolUint32Map(false));
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			TS_ASSERT(obj2.getMapOfMyBoolFloatMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolFloatMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyBoolFloatMap(false));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyBoolDoubleMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolDoubleMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyBoolDoubleMap(false));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyBoolStringMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolStringMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolStringMap(true) == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyBoolStringMap(false));
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolStringMap(false) == "Hello Solar System!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}
	
		void testCreateAndSerializeObject() {
	
			Test11MapBool obj1;
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 0);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 0);
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap());
	
			Test11MapBool obj2;
			TS_ASSERT(obj2.getMapOfMyBoolBoolMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolBoolMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj2.getMapOfMyBoolCharMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolCharMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj2.getMapOfMyBoolInt32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolInt32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj2.getMapOfMyBoolUint32Map().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolUint32Map() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj2.getMapOfMyBoolFloatMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolFloatMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj2.getMapOfMyBoolDoubleMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolDoubleMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj2.getMapOfMyBoolStringMap().size() == 0);
			TS_ASSERT(obj2.getSize_MapOfMyBoolStringMap() == 0);
			TS_ASSERT(obj2.isEmpty_MapOfMyBoolStringMap());
	
			{
				std::map<bool, bool> myExternalMap;
				myExternalMap[true] = true;
				myExternalMap[false] = false;
			
				obj1.clear_MapOfMyBoolBoolMap();
				TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(false));
			
				obj1.setMapOfMyBoolBoolMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			
				obj1.clear_MapOfMyBoolBoolMap();
				TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(false));
			}
			obj1.putTo_MapOfMyBoolBoolMap(true, true);
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolBoolMap(false));
			
			obj1.putTo_MapOfMyBoolBoolMap(false, false);
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			
			{
				std::map<bool, char> myExternalMap;
				myExternalMap[true] = 'd';
				myExternalMap[false] = 'e';
			
				obj1.clear_MapOfMyBoolCharMap();
				TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(false));
			
				obj1.setMapOfMyBoolCharMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
				TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			
				obj1.clear_MapOfMyBoolCharMap();
				TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(false));
			}
			obj1.putTo_MapOfMyBoolCharMap(true, 'd');
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolCharMap(false));
			
			obj1.putTo_MapOfMyBoolCharMap(false, 'e');
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			
			{
				std::map<bool, int32_t> myExternalMap;
				myExternalMap[true] = -300;
				myExternalMap[false] = -400;
			
				obj1.clear_MapOfMyBoolInt32Map();
				TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(false));
			
				obj1.setMapOfMyBoolInt32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			
				obj1.clear_MapOfMyBoolInt32Map();
				TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(false));
			}
			obj1.putTo_MapOfMyBoolInt32Map(true, -300);
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolInt32Map(false));
			
			obj1.putTo_MapOfMyBoolInt32Map(false, -400);
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			
			{
				std::map<bool, uint32_t> myExternalMap;
				myExternalMap[true] = 600;
				myExternalMap[false] = 700;
			
				obj1.clear_MapOfMyBoolUint32Map();
				TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(false));
			
				obj1.setMapOfMyBoolUint32Map(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(true));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(false));
				TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			
				obj1.clear_MapOfMyBoolUint32Map();
				TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(false));
			}
			obj1.putTo_MapOfMyBoolUint32Map(true, 600);
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolUint32Map(false));
			
			obj1.putTo_MapOfMyBoolUint32Map(false, 700);
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(true));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			
			{
				std::map<bool, float> myExternalMap;
				myExternalMap[true] = 4.5;
				myExternalMap[false] = 5.5;
			
				obj1.clear_MapOfMyBoolFloatMap();
				TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(false));
			
				obj1.setMapOfMyBoolFloatMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(true));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(false));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			
				obj1.clear_MapOfMyBoolFloatMap();
				TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(false));
			}
			obj1.putTo_MapOfMyBoolFloatMap(true, 4.5);
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolFloatMap(false));
			
			obj1.putTo_MapOfMyBoolFloatMap(false, 5.5);
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			
			{
				std::map<bool, double> myExternalMap;
				myExternalMap[true] = 1.0;
				myExternalMap[false] = 2.0;
			
				obj1.clear_MapOfMyBoolDoubleMap();
				TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(false));
			
				obj1.setMapOfMyBoolDoubleMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(true));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
				TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(false));
				TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			
				obj1.clear_MapOfMyBoolDoubleMap();
				TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(false));
			}
			obj1.putTo_MapOfMyBoolDoubleMap(true, 1.0);
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolDoubleMap(false));
			
			obj1.putTo_MapOfMyBoolDoubleMap(false, 2.0);
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(true));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			
			{
				std::map<bool, std::string> myExternalMap;
				myExternalMap[true] = "Hello World!";
				myExternalMap[false] = "Hello Solar System!";
			
				obj1.clear_MapOfMyBoolStringMap();
				TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(false));
			
				obj1.setMapOfMyBoolStringMap(myExternalMap);
				TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 2);
				TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 2);
				TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
				TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(true));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(true), "Hello World!"));
				TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(false));
				TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(false), "Hello Solar System!"));
			
				obj1.clear_MapOfMyBoolStringMap();
				TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 0);
				TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 0);
				TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap());
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(true));
				TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(false));
			}
			obj1.putTo_MapOfMyBoolStringMap(true, "Hello World!");
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 1);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 1);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(true));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(true), "Hello World!"));
			TS_ASSERT(!obj1.containsKey_MapOfMyBoolStringMap(false));
			
			obj1.putTo_MapOfMyBoolStringMap(false, "Hello Solar System!");
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(true));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(true), "Hello World!"));
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(false));
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.getValueForKey_MapOfMyBoolStringMap(false), "Hello Solar System!"));
			
	
			TS_ASSERT(obj1.getMapOfMyBoolBoolMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolBoolMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			TS_ASSERT(obj1.getMapOfMyBoolCharMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(obj1.containsKey_MapOfMyBoolCharMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			TS_ASSERT(obj1.getMapOfMyBoolInt32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolInt32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			TS_ASSERT(obj1.getMapOfMyBoolUint32Map().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolUint32Map(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			TS_ASSERT(obj1.getMapOfMyBoolFloatMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolFloatMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			TS_ASSERT(obj1.getMapOfMyBoolDoubleMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(obj1.containsKey_MapOfMyBoolDoubleMap(false));
			TS_ASSERT_DELTA(obj1.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			TS_ASSERT(obj1.getMapOfMyBoolStringMap().size() == 2);
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == 2);
			TS_ASSERT(!obj1.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolStringMap(true) == "Hello World!");
			TS_ASSERT(obj1.containsKey_MapOfMyBoolStringMap(false));
			TS_ASSERT(obj1.getValueForKey_MapOfMyBoolStringMap(false) == "Hello Solar System!");
	
			stringstream sstr;
			sstr << obj1;
			sstr >> obj2;
	
			TS_ASSERT(obj1.getSize_MapOfMyBoolBoolMap() == obj2.getSize_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolBoolMap() == obj2.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolCharMap() == obj2.getSize_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolCharMap() == obj2.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolInt32Map() == obj2.getSize_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolInt32Map() == obj2.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj1.getSize_MapOfMyBoolUint32Map() == obj2.getSize_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolUint32Map() == obj2.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj1.getSize_MapOfMyBoolFloatMap() == obj2.getSize_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolFloatMap() == obj2.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolDoubleMap() == obj2.getSize_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolDoubleMap() == obj2.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT(obj1.getSize_MapOfMyBoolStringMap() == obj2.getSize_MapOfMyBoolStringMap());
			TS_ASSERT(obj1.isEmpty_MapOfMyBoolStringMap() == obj2.isEmpty_MapOfMyBoolStringMap());
	
			TS_ASSERT(obj2.getMapOfMyBoolBoolMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolBoolMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolBoolMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolBoolMap(true) == true);
			TS_ASSERT(obj2.containsKey_MapOfMyBoolBoolMap(false));
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolBoolMap(false) == false);
			TS_ASSERT(obj2.getMapOfMyBoolCharMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolCharMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolCharMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolCharMap(true) == 'd');
			TS_ASSERT(obj2.containsKey_MapOfMyBoolCharMap(false));
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolCharMap(false) == 'e');
			TS_ASSERT(obj2.getMapOfMyBoolInt32Map().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolInt32Map() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolInt32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolInt32Map(true) == -300);
			TS_ASSERT(obj2.containsKey_MapOfMyBoolInt32Map(false));
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolInt32Map(false) == -400);
			TS_ASSERT(obj2.getMapOfMyBoolUint32Map().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolUint32Map() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolUint32Map());
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolUint32Map(true) == 600);
			TS_ASSERT(obj2.containsKey_MapOfMyBoolUint32Map(false));
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolUint32Map(false) == 700);
			TS_ASSERT(obj2.getMapOfMyBoolFloatMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolFloatMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolFloatMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyBoolFloatMap(true), 4.5, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyBoolFloatMap(false));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyBoolFloatMap(false), 5.5, 1e-5);
			TS_ASSERT(obj2.getMapOfMyBoolDoubleMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolDoubleMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolDoubleMap());
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyBoolDoubleMap(true), 1.0, 1e-5);
			TS_ASSERT(obj2.containsKey_MapOfMyBoolDoubleMap(false));
			TS_ASSERT_DELTA(obj2.getValueForKey_MapOfMyBoolDoubleMap(false), 2.0, 1e-5);
			TS_ASSERT(obj2.getMapOfMyBoolStringMap().size() == 2);
			TS_ASSERT(obj2.getSize_MapOfMyBoolStringMap() == 2);
			TS_ASSERT(!obj2.isEmpty_MapOfMyBoolStringMap());
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolStringMap(true) == "Hello World!");
			TS_ASSERT(obj2.containsKey_MapOfMyBoolStringMap(false));
			TS_ASSERT(obj2.getValueForKey_MapOfMyBoolStringMap(false) == "Hello Solar System!");
	
			TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(obj1.toString(), obj2.toString()));
		}

};

#endif /*TEST11MAPBOOL_TESTSUITE_H*/
