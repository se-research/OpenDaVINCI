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

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"  // for KeyValueConfiguration
#include "opendavinci/odcore/exceptions/Exceptions.h"

using namespace std;
using namespace odcore::base;
using namespace odcore::exceptions;

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

            // test getValue<T>(...)
            string value1 = "";
            int32_t value2 = 0;
            float value3 = 0;
            double value4 = 0;

            value1 = kvc.getValue<string>("Section1.key1");
            value2 = kvc.getValue<int>("Section1.key2");
            value3 = kvc.getValue<float>("Section1.key3");
            value4 = kvc.getValue<double>("Section1.key4");

            TS_ASSERT(value1 == "String1");
            TS_ASSERT(value2 == 10);
            TS_ASSERT_DELTA(value3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(value4, 3.1415, 1e-3);

            // test getOptionalValue<T>(...)
            bool if1,if2,if3,if4;
            if1=if2=if3=if4=false;
            string value1o = "";
            int32_t value2o = 0;
            float value3o = 0;
            double value4o = 0;

            value1o = kvc.getOptionalValue<string>("Section1.key1", if1);
            value2o = kvc.getOptionalValue<int>("Section1.key2", if2);
            value3o = kvc.getOptionalValue<float>("Section1.key3", if3);
            value4o = kvc.getOptionalValue<double>("Section1.key4", if4);

            TS_ASSERT(if1);
            TS_ASSERT(if2);
            TS_ASSERT(if3);
            TS_ASSERT(if4);
            TS_ASSERT(value1o == "String1");
            TS_ASSERT(value2o == 10);
            TS_ASSERT_DELTA(value3o, 3.1415, 1e-3);
            TS_ASSERT_DELTA(value4o, 3.1415, 1e-3);

            string value1nf = "xyz";
            int32_t value2nf = 123;
            float value3nf = 12.3;
            double value4nf = 1.23;

            value1nf = kvc.getOptionalValue<string>("Section1.key91", if1);
            value2nf = kvc.getOptionalValue<int>("Section1.key92", if2);
            value3nf = kvc.getOptionalValue<float>("Section1.key93", if3);
            value4nf = kvc.getOptionalValue<double>("Section1.key94", if4);

            TS_ASSERT(! if1);
            TS_ASSERT(! if2);
            TS_ASSERT(! if3);
            TS_ASSERT(! if4);
            TS_ASSERT(value1nf != "xyz");
            TS_ASSERT(value2nf != 123);
            TS_ASSERT(abs(value3nf-12.3) > 1e-3);
            TS_ASSERT(abs(value4nf-1.23) > 1e-3);

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

            string value1 = "";
            int32_t value2 = 0;
            float value3 = 0;
            double value4 = 0;

            value1 = kvc.getValue<string>("Section1.key1");
            value2 = kvc.getValue<int>("Section1.key2");
            value3 = kvc.getValue<float>("Section1.key3");
            value4 = kvc.getValue<double>("Section1.key4");

            TS_ASSERT(value1 == "String1");
            TS_ASSERT(value2 == 10);
            TS_ASSERT_DELTA(value3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(value4, 3.1415, 1e-3);

            // test getOptionalValue<T>(...)
            bool if1,if2,if3,if4;
            if1=if2=if3=if4=false;
            string value1o = "";
            int32_t value2o = 0;
            float value3o = 0;
            double value4o = 0;

            value1o = kvc.getOptionalValue<string>("Section1.key1", if1);
            value2o = kvc.getOptionalValue<int>("Section1.key2", if2);
            value3o = kvc.getOptionalValue<float>("Section1.key3", if3);
            value4o = kvc.getOptionalValue<double>("Section1.key4", if4);

            TS_ASSERT(if1);
            TS_ASSERT(if2);
            TS_ASSERT(if3);
            TS_ASSERT(if4);
            TS_ASSERT(value1o == "String1");
            TS_ASSERT(value2o == 10);
            TS_ASSERT_DELTA(value3o, 3.1415, 1e-3);
            TS_ASSERT_DELTA(value4o, 3.1415, 1e-3);

            string value1nf = "xyz";
            int32_t value2nf = 123;
            float value3nf = 12.3;
            double value4nf = 1.23;

            value1nf = kvc.getOptionalValue<string>("Section1.key91", if1);
            value2nf = kvc.getOptionalValue<int>("Section1.key92", if2);
            value3nf = kvc.getOptionalValue<float>("Section1.key93", if3);
            value4nf = kvc.getOptionalValue<double>("Section1.key94", if4);

            TS_ASSERT(! if1);
            TS_ASSERT(! if2);
            TS_ASSERT(! if3);
            TS_ASSERT(! if4);
            TS_ASSERT(value1nf != "xyz");
            TS_ASSERT(value2nf != 123);
            TS_ASSERT(abs(value3nf-12.3) > 1e-3);
            TS_ASSERT(abs(value4nf-1.23) > 1e-3);

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

            string value1 = "";
            int32_t value2 = 0;
            float value3 = 0;
            double value4 = 0;

            value1 = kvc.getValue<string>("Section1.key1");
            value2 = kvc.getValue<int>("Section1.key2");
            value3 = kvc.getValue<float>("Section1.key3");
            value4 = kvc.getValue<double>("Section1.key4");

            TS_ASSERT(value1 == "String1");
            TS_ASSERT(value2 == 10);
            TS_ASSERT_DELTA(value3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(value4, 3.1415, 1e-3);

            // test getOptionalValue<T>(...)
            bool if1,if2,if3,if4;
            if1=if2=if3=if4=false;
            string value1o = "";
            int32_t value2o = 0;
            float value3o = 0;
            double value4o = 0;

            value1o = kvc.getOptionalValue<string>("Section1.key1", if1);
            value2o = kvc.getOptionalValue<int>("Section1.key2", if2);
            value3o = kvc.getOptionalValue<float>("Section1.key3", if3);
            value4o = kvc.getOptionalValue<double>("Section1.key4", if4);

            TS_ASSERT(if1);
            TS_ASSERT(if2);
            TS_ASSERT(if3);
            TS_ASSERT(if4);
            TS_ASSERT(value1o == "String1");
            TS_ASSERT(value2o == 10);
            TS_ASSERT_DELTA(value3o, 3.1415, 1e-3);
            TS_ASSERT_DELTA(value4o, 3.1415, 1e-3);

            string value1nf = "xyz";
            int32_t value2nf = 123;
            float value3nf = 12.3;
            double value4nf = 1.23;

            value1nf = kvc.getOptionalValue<string>("Section1.key91", if1);
            value2nf = kvc.getOptionalValue<int>("Section1.key92", if2);
            value3nf = kvc.getOptionalValue<float>("Section1.key93", if3);
            value4nf = kvc.getOptionalValue<double>("Section1.key94", if4);

            TS_ASSERT(! if1);
            TS_ASSERT(! if2);
            TS_ASSERT(! if3);
            TS_ASSERT(! if4);
            TS_ASSERT(value1nf != "xyz");
            TS_ASSERT(value2nf != 123);
            TS_ASSERT(abs(value3nf-12.3) > 1e-3);
            TS_ASSERT(abs(value4nf-1.23) > 1e-3);

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

            string value1 = "";
            int32_t value2 = 0;
            float value3 = 0;
            double value4 = 0;

            bool value1NotFound = false;
            try {
                value1 = kvc.getValue<string>("Section1.key1");
            } catch (ValueForKeyNotFoundException &vfknfe) {
                TS_ASSERT(vfknfe.getMessage() == "Value for key 'Section1.key1' not found.");
                value1NotFound = true;
            }
            value2 = kvc.getValue<int>("Section1.key2");
            value3 = kvc.getValue<float>("Section1.key3");
            value4 = kvc.getValue<double>("Section3.key4");

            TS_ASSERT(value1NotFound);
            TS_ASSERT(value2 == 10);
            TS_ASSERT_DELTA(value3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(value4, 3.1415, 1e-3);

            // test getOptionalValue<T>(...)
            // the retrieval of parameters not affected by comments has been tested in the previous tests and it is now skipped
            bool if1,if3;
            if1=true;
            if3=false;
            string value1o = "";
            float value3o = 0;

            value1o = kvc.getOptionalValue<string>("Section1.key1", if1);
            value3o = kvc.getOptionalValue<float>("Section1.key3", if3);

            TS_ASSERT(! if1);
            TS_ASSERT(if3);
            TS_ASSERT_DELTA(value3o, 3.1415, 1e-3);

            string value1nf = "xyz";
            float value3nf = 12.3;

            value1nf = kvc.getOptionalValue<string>("Section1.key91", if1);
            value3nf = kvc.getOptionalValue<float>("Section1.key93", if3);

            TS_ASSERT(value1nf != "xyz");
            TS_ASSERT(abs(value3nf-12.3) > 1e-3);
            TS_ASSERT(! if1);
            TS_ASSERT(! if3);

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

            string value1 = "";
            int32_t value2 = 0;
            float value3 = 0;
            double value4 = 0;

            bool value1NotFound = false;
            try {
                value1 = kvc.getValue<string>("SeCtIoN1.key1");
            } catch (ValueForKeyNotFoundException &vfknfe) {
                TS_ASSERT(vfknfe.getMessage() == "Value for key 'SeCtIoN1.key1' not found.");
                value1NotFound = true;
            }
            value2 = kvc.getValue<int>("Section1.key2");
            value3 = kvc.getValue<float>("SeCtIoN1.KEy3");
            value4 = kvc.getValue<double>("SectION3.kEY4");

            TS_ASSERT(value1NotFound);
            TS_ASSERT(value2 == 10);
            TS_ASSERT_DELTA(value3, 3.1415, 1e-3);
            TS_ASSERT_DELTA(value4, 3.1415, 1e-3);
            
            // test getOptionalValue<T>(...)
            bool if1,if2,if3,if4;
            if1=true;
            if2=if3=if4=false;
            string value1nf = "";
            int32_t value2o = 0;
            float value3o = 0;
            double value4o = 0;

            value1nf = kvc.getOptionalValue<string>("sEcTiON1.kEY1", if1);
            value2o = kvc.getOptionalValue<int>("sEcTiON1.KEy2", if2);
            value3o = kvc.getOptionalValue<float>("SecTIoN1.keY3", if3);
            value4o = kvc.getOptionalValue<double>("SeCTion3.kEy4", if4);

            TS_ASSERT(! if1);
            TS_ASSERT(if2);
            TS_ASSERT(if3);
            TS_ASSERT(if4);
            TS_ASSERT(value1nf != "String1");
            TS_ASSERT(value2o == 10);
            TS_ASSERT_DELTA(value3o, 3.1415, 1e-3);
            TS_ASSERT_DELTA(value4o, 3.1415, 1e-3);
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
            double value4 = 0;

            value4 = kvc.getValue<double>("Section3.key4");

            TS_ASSERT_DELTA(value4, 3.1415, 1e-3);
            
            // test getOptionalValue<T>(...)
            bool if4,if5;
            if4=false;
            if5=true;
            double value4o = 0;
            double value5nf = 1.618;

            value4o = kvc.getOptionalValue<double>("sEcTiON3.Key4", if4);
            value5nf = kvc.getOptionalValue<double>("sEcTiOn3.kEY5", if5);

            TS_ASSERT(if4);
            TS_ASSERT_DELTA(value4o, 3.1415, 1e-3);
            TS_ASSERT(! if5);
            TS_ASSERT(abs(value5nf-1.618) > 1e-3);
        }
};

#endif /*CORE_KEYVALUECONFIGURATIONTESTSUITE_H_*/
