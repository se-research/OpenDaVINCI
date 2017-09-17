/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2016 Christian Berger
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

#ifndef CORE_CSVFROMVISITABLEVISITORTESTSUITE_H_
#define CORE_CSVFROMVISITABLEVISITORTESTSUITE_H_

#include <cmath>                        // for fabs
#include <cstdlib>                      // for calloc
#include <cstring>                      // for strcmp
#include <iosfwd>                       // for stringstream, istream, etc
#include <memory>
#include <string>                       // for string

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"     // for Deserializer
#include "opendavinci/odcore/serialization/Serializable.h"     // for Serializable
#include "opendavinci/odcore/serialization/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/odcore/serialization/Serializer.h"       // for Serializer
#include "opendavinci/odcore/base/Visitable.h"        // for Visitable
#include "opendavinci/odcore/base/Visitor.h"          // for Visitor
#include "opendavinci/odcore/reflection/CSVFromVisitableVisitor.h"
#include "opendavinci/odcore/strings/StringToolbox.h"  // for StringToolbox

#include "opendavincitestdata/generated/odcore/testdata/TestMessage1.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage5.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage10.h"
#include "opendavincitestdata/generated/odcore/testdata/TestMessage11.h"

using namespace std;
using namespace odcore;
using namespace odcore::base;
using namespace odcore::reflection;
using namespace odcore::serialization;
using namespace odcore::testdata;

class MyVisitable : public Serializable, public Visitable {
    public:
        MyVisitable() :
            Serializable(),
            Visitable(),
            m_att1(0),
            m_att2(0),
            m_att3(0),
            m_att4("") {}

        MyVisitable(const MyVisitable &obj) :
            Serializable(obj),
            Visitable(obj),
            m_att1(obj.m_att1),
            m_att2(obj.m_att2),
            m_att3(obj.m_att3),
            m_att4(obj.m_att4) {}

        ~MyVisitable() {}

        MyVisitable& operator=(const MyVisitable &obj) {
            m_att1 = obj.m_att1;
            m_att2 = obj.m_att2;
            m_att3 = obj.m_att3;
            m_att4 = obj.m_att4;
            return *this;
        }

        virtual ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();
        
            std::shared_ptr<Serializer> s = sf.getSerializer(out);
        
            s->write(1,
                    m_att1);

            s->write(2,
                    m_att2);

            s->write(3,
                    m_att3);

            s->write(4,
                    m_att4);

            return out;
        }

        virtual istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();
        
            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);
        
            d->read(1,
                    m_att1);

            d->read(2,
                    m_att2);

            d->read(3,
                    m_att3);

            d->read(4,
                    m_att4);

            return in;
        }

        virtual void accept(odcore::base::Visitor &v) {
            v.beginVisit(1, "MyVisitable", "MyVisitable");
            v.visit(1, "MyVisitable::att1", "att1", m_att1);
            v.visit(2, "MyVisitable::att2", "att2", m_att2);
            v.visit(3, "MyVisitable::att3", "att3", m_att3);
            v.visit(4, "MyVisitable::att4", "att4", m_att4);
            v.endVisit();
        }

    public:
        uint32_t m_att1;
        float m_att2;
        double m_att3;
        string m_att4;
};

class FieldTest : public CxxTest::TestSuite {
    public:
        void testCSV_noheader() {
            MyVisitable mv;
            mv.m_att1 = 1;
            mv.m_att2 = -1.234;
            mv.m_att3 = 12.3456;
            mv.m_att4 = "Hello World";

            stringstream expected;
            expected << "1%-1.234%12.3456%Hello World%" << endl;

            stringstream output;
            const bool ADD_HEADER = false;
            const char DELIMITER = '%';

            CSVFromVisitableVisitor csv(output, ADD_HEADER, DELIMITER);
            mv.accept(csv);

            TS_ASSERT(output.str() == expected.str());
        }

        void testCSV_withheader() {
            MyVisitable mv;
            mv.m_att1 = 1;
            mv.m_att2 = -1.234;
            mv.m_att3 = 12.3456;
            mv.m_att4 = "Hello World";

            stringstream expected;
            expected << "att1%att2%att3%att4%" << endl;
            expected << "1%-1.234%12.3456%Hello World%" << endl;

            stringstream output;
            const bool ADD_HEADER = true;
            const char DELIMITER = '%';

            CSVFromVisitableVisitor csv(output, ADD_HEADER, DELIMITER);
            mv.accept(csv);

            TS_ASSERT(csv.getHeader() == "att1%att2%att3%att4%");
            TS_ASSERT(csv.getEntry() == "1%-1.234%12.3456%Hello World%");

            TS_ASSERT(output.str() == expected.str());
        }

        void testCSV_default_twice() {
            MyVisitable mv;
            mv.m_att1 = 1;
            mv.m_att2 = -1.234;
            mv.m_att3 = 12.3456;
            mv.m_att4 = "Hello World";

            stringstream expected;
            expected << "att1,att2,att3,att4," << endl;
            expected << "1,-1.234,12.3456,Hello World," << endl;
            expected << "2,-2.234,24.3456,Hello Galaxy," << endl;

            stringstream output;

            CSVFromVisitableVisitor csv(output);
            mv.accept(csv);

            // Second line.
            mv.m_att1 = 2;
            mv.m_att2 = -2.234;
            mv.m_att3 = 24.3456;
            mv.m_att4 = "Hello Galaxy";
            mv.accept(csv);

            TS_ASSERT(output.str() == expected.str());
        }

        void testCSV_NestedMessage() {
            TestMessage5 tm;
            TS_ASSERT(tm.getField1() == 1);
            TS_ASSERT(tm.getField2() == -1);
            TS_ASSERT(tm.getField3() == 100);
            TS_ASSERT(tm.getField4() == -100);
            TS_ASSERT(tm.getField5() == 10000);
            TS_ASSERT(tm.getField6() == -10000);
            TS_ASSERT(tm.getField7() == 12345);
            TS_ASSERT(tm.getField8() == -12345);
            TS_ASSERT_DELTA(tm.getField9(), -1.2345, 1e-4);
            TS_ASSERT_DELTA(tm.getField10(), -10.2345, 1e-4);
            TS_ASSERT(tm.getField11() == "Hello World!");
            TS_ASSERT(tm.getField12().getField1() == 12);

            TestMessage1 tmEmbedded;
            tmEmbedded.setField1(150);
            tm.setField12(tmEmbedded);

            tm.setField1(3);
            tm.setField2(-3);
            tm.setField3(103);
            tm.setField4(-103);
            tm.setField5(10003);
            tm.setField6(-10003);
            tm.setField7(54321);
            tm.setField8(-54321);
            tm.setField9(-5.4321);
            tm.setField10(-50.4321);
            tm.setField11("Hello OpenDaVINCI World!");

            stringstream output;
            const bool ADD_HEADER = true;
            const char DELIMITER = '%';

            stringstream expected;
            expected << "field1%field2%field3%field4%field5%field6%field7%field8%field9%field10%field11%field12.field1%" << endl;
            expected << "3%-3%103%-103%10003%-10003%54321%-54321%-5.4321%-50.4321%Hello OpenDaVINCI World!%150%" << endl;

            CSVFromVisitableVisitor csv(output, ADD_HEADER, DELIMITER);
            tm.accept(csv);

            TS_ASSERT(output.str() == expected.str());
        }

        void testCSV_DoubleNestedMessage() {
            TestMessage5 tm;
            TS_ASSERT(tm.getField1() == 1);
            TS_ASSERT(tm.getField2() == -1);
            TS_ASSERT(tm.getField3() == 100);
            TS_ASSERT(tm.getField4() == -100);
            TS_ASSERT(tm.getField5() == 10000);
            TS_ASSERT(tm.getField6() == -10000);
            TS_ASSERT(tm.getField7() == 12345);
            TS_ASSERT(tm.getField8() == -12345);
            TS_ASSERT_DELTA(tm.getField9(), -1.2345, 1e-4);
            TS_ASSERT_DELTA(tm.getField10(), -10.2345, 1e-4);
            TS_ASSERT(tm.getField11() == "Hello World!");
            TS_ASSERT(tm.getField12().getField1() == 12);

            TestMessage1 tmEmbedded;
            tmEmbedded.setField1(150);
            tm.setField12(tmEmbedded);

            tm.setField1(3);
            tm.setField2(-3);
            tm.setField3(103);
            tm.setField4(-103);
            tm.setField5(10003);
            tm.setField6(-10003);
            tm.setField7(54321);
            tm.setField8(-54321);
            tm.setField9(-5.4321);
            tm.setField10(-50.4321);
            tm.setField11("Hello OpenDaVINCI World!");

            TestMessage11 tm11;
            tm11.setMyField1(123);
            tm11.setField2(tm);

            stringstream output;
            const bool ADD_HEADER = true;
            const char DELIMITER = '%';

            stringstream expected;
            expected << "myField1%field2.field1%field2.field2%field2.field3%field2.field4%field2.field5%field2.field6%field2.field7%field2.field8%field2.field9%field2.field10%field2.field11%field2.field12.field1%" << endl;
            expected << "123%3%-3%103%-103%10003%-10003%54321%-54321%-5.4321%-50.4321%Hello OpenDaVINCI World!%150%" << endl;

            CSVFromVisitableVisitor csv(output, ADD_HEADER, DELIMITER);
            tm11.accept(csv);

            TS_ASSERT(output.str() == expected.str());
        }

        void testCSV_Message() {
            TestMessage10 tm1;
            TS_ASSERT(tm1.getSize_MyArray1() == 2);
            TS_ASSERT(tm1.getSize_MyArray2() == 3);

            uint32_t *tm1_arr1 = tm1.getMyArray1();
            tm1_arr1[0] = 1; tm1_arr1[1] = 2;
            float *tm1_arr2 = tm1.getMyArray2();
            tm1_arr2[0] = -1.2345; tm1_arr2[1] = -2.3456; tm1_arr2[2] = -3.4567;

            TS_ASSERT(tm1.getSize_MyArray1() == 2);
            TS_ASSERT(tm1.getSize_MyArray2() == 3);
            TS_ASSERT(tm1_arr1[0] == 1);
            TS_ASSERT(tm1_arr1[1] == 2);
            TS_ASSERT_DELTA(tm1_arr2[0], -1.2345, 1e-4);
            TS_ASSERT_DELTA(tm1_arr2[1], -2.3456, 1e-4);
            TS_ASSERT_DELTA(tm1_arr2[2], -3.4567, 1e-4);

            TS_ASSERT(tm1.getMyArray1()[0] == 1);
            TS_ASSERT(tm1.getMyArray1()[1] == 2);
            TS_ASSERT_DELTA(tm1.getMyArray2()[0], -1.2345, 1e-4);
            TS_ASSERT_DELTA(tm1.getMyArray2()[1], -2.3456, 1e-4);
            TS_ASSERT_DELTA(tm1.getMyArray2()[2], -3.4567, 1e-4);

            stringstream output;
            const bool ADD_HEADER = true;
            const char DELIMITER = '%';

//            stringstream expected;
//            expected << "field1%field2%field3%field4%field5%field6%field7%field8%field9%field10%field11%field12.field1%" << endl;
//            expected << "3%-3%103%-103%10003%-10003%54321%-54321%-5.4321%-50.4321%Hello OpenDaVINCI World!%150%" << endl;


            CSVFromVisitableVisitor csv(output, ADD_HEADER, DELIMITER);
            tm1.accept(csv);

cout << "'" << output.str() << "'" << endl;
//            TS_ASSERT(output.str() == expected.str());
        }

};

#endif /*CORE_CSVFROMVISITABLEVISITORTESTSUITE_H_*/
