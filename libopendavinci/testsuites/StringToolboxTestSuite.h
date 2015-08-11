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

#ifndef CORE_STRINGTOOLBOXTESTSUITE_H_
#define CORE_STRINGTOOLBOXTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <string>

#include "core/strings/StringToolbox.h"

using namespace std;

class StringToolboxTest : public CxxTest::TestSuite {
    public:
        void testTrim() {
            string s1 = " ABC";
            core::strings::StringToolbox::trim(s1);
            string ref_s1 = "ABC";
            TS_ASSERT(ref_s1.compare(s1) == 0); 

            string s2 = "ABC ";
            core::strings::StringToolbox::trim(s2);
            string ref_s2 = "ABC";
            TS_ASSERT(ref_s2.compare(s2) == 0); 

            string s3 = " ABC ";
            core::strings::StringToolbox::trim(s3);
            string ref_s3 = "ABC";
            TS_ASSERT(ref_s3.compare(s3) == 0); 

            string s4 = "ABC";
            core::strings::StringToolbox::trim(s4);
            string ref_s4 = "ABC";
            TS_ASSERT(ref_s4.compare(s4) == 0); 

            string s5 = "";
            core::strings::StringToolbox::trim(s5);
            string ref_s5 = "";
            TS_ASSERT(ref_s5.compare(s5) == 0); 
        }

        void testCompareIgnoreCase() {
            string s1 = "ABC";
            string s2 = "ABC";
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(s1, s2)); 

            string s3 = "abc";
            string s4 = "ABC";
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(s3, s4)); 
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(s4, s3)); 

            string s5 = "abc";
            string s6 = "abc";
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(s5, s6)); 

            string s7 = "abc";
            string s8 = "abd";
            TS_ASSERT(!core::strings::StringToolbox::equalsIgnoreCase(s7, s8)); 

            string s9 = "abc";
            string s10 = "abc ";
            TS_ASSERT(!core::strings::StringToolbox::equalsIgnoreCase(s9, s10)); 
        }

        void testSplit() {
            string s1 = "abc";
            vector<string> vs1 = core::strings::StringToolbox::split(s1, ',');
            TS_ASSERT(vs1.size() == 0);

            string s2 = "abc;def";
            vector<string> vs2_no = core::strings::StringToolbox::split(s2, ',');
            TS_ASSERT(vs2_no.size() == 0);
            vector<string> vs2 = core::strings::StringToolbox::split(s2, ';');
            TS_ASSERT(vs2.size() == 2);
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(vs2.at(0), "abc"));
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(vs2.at(1), "def"));

            string s3 = ";abc;def";
            vector<string> vs3 = core::strings::StringToolbox::split(s3, ';');
            TS_ASSERT(vs3.size() == 2);
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(vs3.at(0), "abc"));
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(vs3.at(1), "def"));

            string s4 = "abc;def;";
            vector<string> vs4 = core::strings::StringToolbox::split(s4, ';');
            TS_ASSERT(vs4.size() == 2);
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(vs4.at(0), "abc"));
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(vs4.at(1), "def"));

            string s5 = ";abc;def;";
            vector<string> vs5 = core::strings::StringToolbox::split(s5, ';');
            TS_ASSERT(vs5.size() == 2);
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(vs5.at(0), "abc"));
            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(vs5.at(1), "def"));
        }

};

#endif /*CORE_STRINGTOOLBOXTESTSUITE_H_*/
