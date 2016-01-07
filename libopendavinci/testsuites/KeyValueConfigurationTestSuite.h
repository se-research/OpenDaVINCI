/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#ifndef CORE_KEYVALUECONFIGURATIONTESTSUITE_H_
#define CORE_KEYVALUECONFIGURATIONTESTSUITE_H_

#include <sstream>                      // for operator<<, basic_ostream, etc
#include <string>                       // for string, operator==, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "core/opendavinci.h"
#include "core/base/KeyValueConfiguration.h"  // for KeyValueConfiguration
#include "core/exceptions/Exceptions.h"

using namespace std;
using namespace core::base;
using namespace core::exceptions;

class ConfigurationTest : public CxxTest::TestSuite {
    public:
        void testReadSimpleData() {
            stringstream s;
            s << "Section1.key1=String1" << endl
            << "Section1.key2=10" << endl
            << "Section1.key3=3.1415" << endl
            << "Section1.key4=3.1415" << endl;

            KeyValueConfiguration kvc;
            kvc.readFrom(s);
            stringstream s2;
            kvc.writeTo(s2);

            string key1 = "";
            int32_t key2 = 0;
            float key3 = 0;
            double key4 = 0;

            key1 = kvc.getValue<string>("Section1.key1");
            key2 = kvc.getValue<int>("Section1.key2");
            key3 = kvc.getValue<float>("Section1.key3");
            key4 = kvc.getValue<double>("Section1.key4");

            TS_ASSERT(key1 == "String1");
            TS_ASSERT(key2 == 10);
            TS_ASSERT_DELTA(key3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);

            stringstream s3;
            s3 << "section1.key1=String1" << endl
            << "section1.key2=10" << endl
            << "section1.key3=3.1415" << endl
            << "section1.key4=3.1415" << endl;
            TS_ASSERT(s3.str() == s2.str());
        }

        void testReadSimpleDataCopyConstructor() {
            stringstream s;
            s << "Section1.key1=String1" << endl
            << "Section1.key2=10" << endl
            << "Section1.key3=3.1415" << endl
            << "Section1.key4=3.1415" << endl;

            KeyValueConfiguration kvcOriginal;
            kvcOriginal.readFrom(s);

            KeyValueConfiguration kvc(kvcOriginal);
            stringstream s2;
            kvc.writeTo(s2);

            string key1 = "";
            int32_t key2 = 0;
            float key3 = 0;
            double key4 = 0;

            key1 = kvc.getValue<string>("Section1.key1");
            key2 = kvc.getValue<int>("Section1.key2");
            key3 = kvc.getValue<float>("Section1.key3");
            key4 = kvc.getValue<double>("Section1.key4");

            TS_ASSERT(key1 == "String1");
            TS_ASSERT(key2 == 10);
            TS_ASSERT_DELTA(key3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);

            stringstream s3;
            s3 << "section1.key1=String1" << endl
            << "section1.key2=10" << endl
            << "section1.key3=3.1415" << endl
            << "section1.key4=3.1415" << endl;
            TS_ASSERT(s3.str() == s2.str());
        }

        void testReadSimpleDataAssignmentOperator() {
            stringstream s;
            s << "Section1.key1=String1" << endl
            << "Section1.key2=10" << endl
            << "Section1.key3=3.1415" << endl
            << "Section1.key4=3.1415" << endl;

            KeyValueConfiguration kvcOriginal;
            kvcOriginal.readFrom(s);

            KeyValueConfiguration kvc;
            kvc = kvcOriginal;
            stringstream s2;
            kvc.writeTo(s2);

            string key1 = "";
            int32_t key2 = 0;
            float key3 = 0;
            double key4 = 0;

            key1 = kvc.getValue<string>("Section1.key1");
            key2 = kvc.getValue<int>("Section1.key2");
            key3 = kvc.getValue<float>("Section1.key3");
            key4 = kvc.getValue<double>("Section1.key4");

            TS_ASSERT(key1 == "String1");
            TS_ASSERT(key2 == 10);
            TS_ASSERT_DELTA(key3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);

            stringstream s3;
            s3 << "section1.key1=String1" << endl
            << "section1.key2=10" << endl
            << "section1.key3=3.1415" << endl
            << "section1.key4=3.1415" << endl;
            TS_ASSERT(s3.str() == s2.str());
        }

        void testReadCommentedData() {
            stringstream s;
            s << "#Section1.key1=String1" << endl
            << "Section1.key2=10" << endl
            << "Section1.key3=3.1415 # Comment" << endl
            << "Section3.key4=3.1415" << endl;

            KeyValueConfiguration kvc;
            kvc.readFrom(s);
            stringstream s2;
            kvc.writeTo(s2);

            string key1 = "";
            int32_t key2 = 0;
            float key3 = 0;
            double key4 = 0;

            bool key1NotFound = false;
            try {
                key1 = kvc.getValue<string>("Section1.key1");
            } catch (ValueForKeyNotFoundException &vfknfe) {
                TS_ASSERT(vfknfe.getMessage() == "Value for key 'Section1.key1' not found.");
                key1NotFound = true;
            }
            key2 = kvc.getValue<int>("Section1.key2");
            key3 = kvc.getValue<float>("Section1.key3");
            key4 = kvc.getValue<double>("Section3.key4");

            TS_ASSERT(key1NotFound);
            TS_ASSERT(key2 == 10);
            TS_ASSERT_DELTA(key3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);

            stringstream s3;
            s3 << "section1.key2=10" << endl
            << "section1.key3=3.1415" << endl
            << "section3.key4=3.1415" << endl;
            TS_ASSERT(s3.str() == s2.str());
        }

        void testReadCommentedDataCaseInsensitive() {
            stringstream s;
            s << "#Section1.key1=String1" << endl
            << "Section1.key2=10" << endl
            << "Section1.key3=3.1415 # Comment" << endl
            << "Section3.key4=3.1415" << endl;

            KeyValueConfiguration kvc;
            kvc.readFrom(s);

            string key1 = "";
            int32_t key2 = 0;
            float key3 = 0;
            double key4 = 0;

            bool key1NotFound = false;
            try {
                key1 = kvc.getValue<string>("SeCtIoN1.key1");
            } catch (ValueForKeyNotFoundException &vfknfe) {
                TS_ASSERT(vfknfe.getMessage() == "Value for key 'SeCtIoN1.key1' not found.");
                key1NotFound = true;
            }
            key2 = kvc.getValue<int>("Section1.kEY2");
            key3 = kvc.getValue<float>("SeCtIoN1.key3");
            key4 = kvc.getValue<double>("Section3.KeY4");

            TS_ASSERT(key1NotFound);
            TS_ASSERT(key2 == 10);
            TS_ASSERT_DELTA(key3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);
        }

        void testReadCommentedDataSubset() {
            stringstream s;
            s << "#Section1.key1=String1" << endl
            << "Section1.key2=10" << endl
            << "Section1.key3=3.1415 # Comment" << endl
            << "Section3.key4=3.1415" << endl;

            KeyValueConfiguration kvcOriginal;
            kvcOriginal.readFrom(s);

            KeyValueConfiguration kvc = kvcOriginal.getSubsetForSection("Section3");
            double key4 = 0;

            key4 = kvc.getValue<double>("Section3.KeY4");

            TS_ASSERT_DELTA(key4, 3.1415, 1e-3);
        }
};

#endif /*CORE_KEYVALUECONFIGURATIONTESTSUITE_H_*/
