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

#ifndef CORE_SHAREDPOINTERTESTSUITE_H_
#define CORE_SHAREDPOINTERTESTSUITE_H_

#include <memory>
#include <iostream>                     // for clog, endl, ostream, etc
#include <vector>                       // for vector, vector<>::iterator

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"

using namespace std;

class SharedPointerTestData {
    public:
        SharedPointerTestData() :
                val(0) {
            clog << "c'tor." << endl;
        };

        virtual ~SharedPointerTestData() {
            clog << "d'tor." << endl;
        };
        int32_t val;
};

class DerivedSharedPointerTestData : public SharedPointerTestData {
    public:
        DerivedSharedPointerTestData() :
                SharedPointerTestData(),
                val2(0) {
            clog << "c'tor derived class." << endl;
        };

        virtual ~DerivedSharedPointerTestData() {
            clog << "d'tor derived class." << endl;
        };
        double val2;
};


class SharedPointerTest : public CxxTest::TestSuite {
    public:
        void testCreate_shared_ptr() {
            {
                SharedPointerTestData *sptd = new SharedPointerTestData();
                shared_ptr<SharedPointerTestData> p1(sptd);
                p1->val = 10;

                TS_ASSERT(sptd->val == 10);
                TS_ASSERT(sptd->val == p1->val);
                TS_ASSERT(sptd == p1.operator->());
            }
            clog << endl;
        }

        void testCreateDestroy_shared_ptr() {
            {
                SharedPointerTestData *sptd = new SharedPointerTestData();
                shared_ptr<SharedPointerTestData> p1(sptd);
                p1->val = 10;

                TS_ASSERT(sptd->val == 10);
                TS_ASSERT(sptd->val == p1->val);
                TS_ASSERT(sptd == p1.operator->());

                p1.reset();
                TS_ASSERT(!p1.get());

                // shared_ptr does not have ! X.isValid(); must be replaced with !X.get().
                // shared_ptr does not have .release(); must be replaced with .reset().
            }
            clog << endl;
        }

        void testCreateDestroy_shared_ptr_UsingCopyConstructor() {
            // Create instance.
            shared_ptr<SharedPointerTestData> p1(new SharedPointerTestData());
            {
                // Handover instance.
                shared_ptr<SharedPointerTestData> p2(p1);
                p1->val = 11;

                TS_ASSERT(p1->val == 11);
                TS_ASSERT(p2->val == p1->val);
                TS_ASSERT(p1.operator ->() == p2.operator->());

                // Remove first instance.
                p1 = shared_ptr<SharedPointerTestData>();
                TS_ASSERT(!p1.get());

                TS_ASSERT(p2->val == 11);
            }
            TS_ASSERT(!p1.get());
            clog << endl;
        }

        void testCreateDestroy_shared_ptr_UsingAssignmentOperator() {
            // Create instance.
            shared_ptr<SharedPointerTestData> p1(new SharedPointerTestData());
            {
                // Handover instance.
                shared_ptr<SharedPointerTestData> p2 = p1;
                p1->val = 12;

                TS_ASSERT(p1->val == 12);
                TS_ASSERT(p2->val == p1->val);
                TS_ASSERT(p1.operator ->() == p2.operator->());

                // Remove first instance.
                p1 = shared_ptr<SharedPointerTestData>();
                TS_ASSERT(!p1.get());

                TS_ASSERT(p2->val == 12);
            }
            TS_ASSERT(!p1.get());
            clog << endl;
        }

        void testCreateAndKeep_shared_ptr_UsingCopyConstructor() {
            // Create empty instance.
            shared_ptr<SharedPointerTestData> p1;
            TS_ASSERT(!p1.get());
            {
                shared_ptr<SharedPointerTestData> p2(new SharedPointerTestData());
                p2->val = 13;

                TS_ASSERT(p2->val == 13);

                // Hand over to first instance.
                p1 = shared_ptr<SharedPointerTestData>(p2);
                TS_ASSERT(p1->val == 13);
                TS_ASSERT(p2->val == 13);

                // Remove second instance.
                p2 = shared_ptr<SharedPointerTestData>();
                TS_ASSERT(p1->val == 13);
                TS_ASSERT(!p2.get());
            }
            TS_ASSERT(p1.get());
            TS_ASSERT(p1->val == 13);
            clog << endl;
        }

        void testCreateAndKeep_shared_ptr_UsingAssignmentOperator() {
            // Create empty instance.
            shared_ptr<SharedPointerTestData> p1;
            TS_ASSERT(!p1.get());
            {
                // Handover instance.
                shared_ptr<SharedPointerTestData> p2(new SharedPointerTestData());
                p2->val = 14;

                TS_ASSERT(p2->val == 14);

                // Hand over to first instance.
                p1 = p2;
                TS_ASSERT(p1->val == 14);
                TS_ASSERT(p2->val == 14);

                // Remove second instance.
                p2 = shared_ptr<SharedPointerTestData>();
                TS_ASSERT(p1->val == 14);
                TS_ASSERT(!p2.get());
            }
            TS_ASSERT(p1.get());
            TS_ASSERT(p1->val == 14);
            clog << endl;
        }

        void test_shared_ptr_InsideSTL() {
            vector<shared_ptr<SharedPointerTestData> > listOfPtrs;
            TS_ASSERT(listOfPtrs.empty());

            {
                shared_ptr<SharedPointerTestData> p1(new SharedPointerTestData());
                listOfPtrs.push_back(p1);
                p1->val = 42;

                shared_ptr<SharedPointerTestData> p2(new SharedPointerTestData());
                listOfPtrs.push_back(p2);
                p2->val = 43;

                shared_ptr<SharedPointerTestData> p3(new SharedPointerTestData());
                listOfPtrs.push_back(p3);
                p3->val = 44;

                shared_ptr<SharedPointerTestData> p4(new SharedPointerTestData());
                listOfPtrs.push_back(p4);
                p4->val = 45;
            }

            TS_ASSERT(!listOfPtrs.empty());

            vector<shared_ptr<SharedPointerTestData> >::iterator it = listOfPtrs.begin();
            int32_t counter = 42;
            while (it != listOfPtrs.end()) {
                TS_ASSERT( (*it++)->val == counter );
                counter++;
            }
            clog << endl;
        }

        void test_shared_ptr_InsideSTLAndCopy() {
            vector<shared_ptr<SharedPointerTestData> > listOfPtrs;
            TS_ASSERT(listOfPtrs.empty());

            vector<shared_ptr<SharedPointerTestData> > listOfPtrs2;
            TS_ASSERT(listOfPtrs2.empty());

            {
                shared_ptr<SharedPointerTestData> p1(new SharedPointerTestData());
                listOfPtrs.push_back(p1);
                p1->val = 42;

                shared_ptr<SharedPointerTestData> p2(new SharedPointerTestData());
                listOfPtrs.push_back(p2);
                p2->val = 43;

                shared_ptr<SharedPointerTestData> p3(new SharedPointerTestData());
                listOfPtrs.push_back(p3);
                p3->val = 44;

                shared_ptr<SharedPointerTestData> p4(new SharedPointerTestData());
                listOfPtrs.push_back(p4);
                p4->val = 45;
            }

            TS_ASSERT(!listOfPtrs.empty());

            vector<shared_ptr<SharedPointerTestData> >::iterator it = listOfPtrs.begin();
            int32_t counter = 42;
            while (it != listOfPtrs.end()) {
                TS_ASSERT( (*it++)->val == counter );
                counter++;
            }

            listOfPtrs2 = listOfPtrs;

            TS_ASSERT(!listOfPtrs2.empty());

            vector<shared_ptr<SharedPointerTestData> >::iterator jt = listOfPtrs2.begin();
            counter = 42;
            while (jt != listOfPtrs2.end()) {
                TS_ASSERT( (*jt++)->val == counter );
                counter++;
            }

            TS_ASSERT((*(listOfPtrs.begin()))->val == 42);
            TS_ASSERT((*(listOfPtrs2.begin()))->val == 42);

            // Change first entry of first list.
            // The first entry of the second list should have changed too.
            (*(listOfPtrs.begin()))->val = 24;
            TS_ASSERT((*(listOfPtrs.begin()))->val == 24);
            TS_ASSERT((*(listOfPtrs2.begin()))->val == 24);
        }

        void testCreate_shared_ptr_FromDerivedClass() {
            {
                SharedPointerTestData *sptd = new SharedPointerTestData();
                shared_ptr<SharedPointerTestData> p1(sptd);
                p1->val = 10;

                TS_ASSERT(sptd->val == 10);
                TS_ASSERT(sptd->val == p1->val);
                TS_ASSERT(sptd == p1.operator->());

                DerivedSharedPointerTestData *dsptd = new DerivedSharedPointerTestData();
                shared_ptr<DerivedSharedPointerTestData> p2(dsptd);
                p2->val2 = 2.5;

                TS_ASSERT((dsptd->val2 - 2.5) < 1e-8);
                TS_ASSERT((dsptd->val2 - p2->val2) < 1e-8);
                TS_ASSERT(dsptd == p2.operator->());

                // Test assignment operator.
                shared_ptr<SharedPointerTestData> p3 = p2;
                TS_ASSERT(dynamic_cast<DerivedSharedPointerTestData*>(p3.operator->()));
                dynamic_cast<DerivedSharedPointerTestData*>(p3.operator->())->val2 = 2.5;

                TS_ASSERT((dsptd->val2 - 2.5) < 1e-8);
                TS_ASSERT((dsptd->val2 - dynamic_cast<DerivedSharedPointerTestData*>(p3.operator->())->val2) < 1e-8);
                TS_ASSERT(dsptd == p3.operator->());

                // Test copy constructor operator.
                shared_ptr<SharedPointerTestData> p4(p2);
                TS_ASSERT(dynamic_cast<DerivedSharedPointerTestData*>(p4.operator->()));
                dynamic_cast<DerivedSharedPointerTestData*>(p4.operator->())->val2 = 2.5;

                TS_ASSERT((dsptd->val2 - 2.5) < 1e-8);
                TS_ASSERT((dsptd->val2 - dynamic_cast<DerivedSharedPointerTestData*>(p4.operator->())->val2) < 1e-8);
                TS_ASSERT(dsptd == p4.operator->());
            }
            clog << endl;
        }
};

#endif /*CORE_SHAREDPOINTERTESTSUITE_H_*/
