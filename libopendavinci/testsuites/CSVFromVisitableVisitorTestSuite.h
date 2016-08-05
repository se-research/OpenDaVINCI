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
#include "opendavinci/odcore/base/Serializable.h"     // for Serializable
#include "opendavinci/odcore/base/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/odcore/base/Serializer.h"       // for Serializer
#include "opendavinci/odcore/base/Visitable.h"        // for Visitable
#include "opendavinci/odcore/base/Visitor.h"          // for Visitor
#include "opendavinci/odcore/reflection/CSVFromVisitableVisitor.h"
#include "opendavinci/odcore/strings/StringToolbox.h"  // for StringToolbox

using namespace std;
using namespace odcore;
using namespace odcore::base;
using namespace odcore::reflection;

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
            v.beginVisit();
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
};

#endif /*CORE_CSVFROMVISITABLEVISITORTESTSUITE_H_*/
