/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2015 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef CORE_FIELDTESTSUITE_H_
#define CORE_FIELDTESTSUITE_H_

#include <cmath>                        // for fabs

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/data/TimeStamp.h"        // for TimeStamp
#include "opendavinci/core/reflection/Field.h"      // for Field
#include "opendavinci/core/strings/StringToolbox.h"  // for StringToolbox
#include "opendavinci/generated/coredata/reflection/AbstractField.h"

using namespace std;
using namespace core::data;
using namespace core::reflection;
using namespace coredata::reflection;

class FieldTest : public CxxTest::TestSuite {
    public:
        void testField1() {
            Field<uint32_t> f1;
            f1.setLongIdentifier(0x10203040);
            f1.setShortIdentifier(1);
            f1.setLongName("testField.myUint32");
            f1.setShortName("myUint32");
            f1.setFieldDataType(coredata::reflection::AbstractField::UINT32_T);
            f1.setValue(1234);
            f1.setSize(sizeof(uint32_t));

            TS_ASSERT(f1.getLongIdentifier() == 0x10203040);
            TS_ASSERT(f1.getShortIdentifier() == 1);
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(f1.getLongName(), "testField.myUint32"));
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(f1.getShortName(), "myUint32"));
            TS_ASSERT(f1.getFieldDataType() == coredata::reflection::AbstractField::UINT32_T);
            TS_ASSERT(f1.getValue() == 1234);
            TS_ASSERT(f1.getSize() == sizeof(uint32_t));
        }

        void testField2() {
            Field<double> f1;
            f1.setLongIdentifier(0x10203041);
            f1.setShortIdentifier(2);
            f1.setLongName("testField.myDouble");
            f1.setShortName("myDouble");
            f1.setFieldDataType(coredata::reflection::AbstractField::DOUBLE_T);
            f1.setValue(1.234);
            f1.setSize(sizeof(double));

            TS_ASSERT(f1.getLongIdentifier() == 0x10203041);
            TS_ASSERT(f1.getShortIdentifier() == 2);
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(f1.getLongName(), "testField.myDouble"));
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(f1.getShortName(), "myDouble"));
            TS_ASSERT(f1.getFieldDataType() == coredata::reflection::AbstractField::DOUBLE_T);
            TS_ASSERT(fabs(f1.getValue() - 1.234) < 1e-4);
            TS_ASSERT(f1.getSize() == sizeof(double));
        }

        void testFiel32() {
            Field<TimeStamp> f1;
            f1.setLongIdentifier(0x10203042);
            f1.setShortIdentifier(3);
            f1.setLongName("testField.myTimeStamp");
            f1.setShortName("myTimeStamp");
            f1.setFieldDataType(coredata::reflection::AbstractField::SERIALIZABLE_T);
            f1.setValue(TimeStamp(1, 2));

            TS_ASSERT(f1.getLongIdentifier() == 0x10203042);
            TS_ASSERT(f1.getShortIdentifier() == 3);
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(f1.getLongName(), "testField.myTimeStamp"));
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(f1.getShortName(), "myTimeStamp"));
            TS_ASSERT(f1.getFieldDataType() == coredata::reflection::AbstractField::SERIALIZABLE_T);
            TimeStamp ts = f1.getValue();
            TS_ASSERT(ts.getSeconds() == 1);
            TS_ASSERT(ts.getFractionalMicroseconds() == 2);
            TS_ASSERT(f1.getSize() == -1);
        }
};

#endif /*CORE_FIELDTESTSUITE_H_*/
