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

#ifndef HALFFLOATTESTSUITE_H_
#define HALFFLOATTESTSUITE_H_

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include <sstream>

#include "opendavinci/odcore/wrapper/half_float.h"

using namespace std;

class HalfFloatTest : public CxxTest::TestSuite {
    public:
        void testHalf() {
            // Do some multiplications:
            half a(3.4);
            half b(5);
            half c = a * b;

            // Convert from float to half:
            half d = static_cast<half>(7.5f);

            // Convert from half to float:
            float f = c;
            //cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << ", e = " << f << endl;

            // Write data to string.
            stringstream sstr;
            sstr.write((char*)(&a), 2);

            const string s = sstr.str();

            // Read back from string.
            stringstream sstr2(s);

            half g;
            sstr.read((char*)(&g), 2);

            TS_ASSERT_DELTA(a, 3.4f, 0.01);
            TS_ASSERT_DELTA(b, 5.0f, 0.01);
            TS_ASSERT_DELTA(c, 17.0f, 0.02);
            TS_ASSERT_DELTA(d, 7.5f, 0.01);
            TS_ASSERT_DELTA(f, 17.0f, 0.02);
            TS_ASSERT_DELTA(g, 3.4f, 0.01);
        }

        void testHalfDelta() {
            float a = 7.1234;
            float b = 7.2545;
            float c = 7.3956;
            float d = 7.4067;

            float d_ba = b-a;
            float d_cb = c-b;
            float d_dc = d-c;

            half d_ba_h = static_cast<half>(d_ba);
            half d_cb_h = static_cast<half>(d_cb);
            half d_dc_h = static_cast<half>(d_dc);

            half a_h = static_cast<half>(a);
            half b_h = static_cast<half>(b);
            half c_h = static_cast<half>(c);
            half d_h = static_cast<half>(d);

            half b2_h = a_h + d_ba_h;
            half c2_h = b_h + d_cb_h;
            half d2_h = c_h + d_dc_h;

            cout << endl
                 << "a = " << a 
                 << ", b = " << b
                 << ", c = " << c
                 << ", d = " << d << endl
                 << ", d_ba = " << d_ba
                 << ", d_cb = " << d_cb
                 << ", d_dc = " << d_dc << endl
                 << ", a_h = " << a_h
                 << ", b_h = " << b_h
                 << ", c_h = " << c_h
                 << ", d_h = " << d_h << endl
                 << ", d_ba_h = " << d_ba_h
                 << ", d_cb_h = " << d_cb_h
                 << ", d_dc_h = " << d_dc_h << endl
                 << ", b2_h = " << b2_h
                 << ", c2_h = " << c2_h
                 << ", d2_h = " << d2_h << endl;
        }
};

#endif /*HALFFLOATTESTSUITE_H_*/
