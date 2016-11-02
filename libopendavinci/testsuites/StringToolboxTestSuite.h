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

#include <string>                       // for string
#include <vector>                       // for vector

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/strings/StringToolbox.h"  // for StringToolbox

using namespace std;

class StringToolboxTest : public CxxTest::TestSuite {
    public:
        void testReplace() {
            string s1 = " ABC";
            string s1_out = odcore::strings::StringToolbox::replaceAll(s1, ' ', '_');
            string ref_s1 = "_ABC";
            TS_ASSERT(ref_s1.compare(s1_out) == 0);

            string s2 = " ABC ";
            string s2_out = odcore::strings::StringToolbox::replaceAll(s2, ' ', '_');
            string ref_s2 = "_ABC_";
            TS_ASSERT(ref_s2.compare(s2_out) == 0);

            string s3 = " AB C ";
            string s3_out = odcore::strings::StringToolbox::replaceAll(s3, ' ', '_');
            string ref_s3 = "_AB_C_";
            TS_ASSERT(ref_s3.compare(s3_out) == 0);

            string s4 = " A  B C  ";
            string s4_out = odcore::strings::StringToolbox::replaceAll(s4, ' ', '_');
            string ref_s4 = "_A__B_C__";
            TS_ASSERT(ref_s4.compare(s4_out) == 0);
        }

        void testTrim() {
            string s1 = " ABC";
            odcore::strings::StringToolbox::trim(s1);
            string ref_s1 = "ABC";
            TS_ASSERT(ref_s1.compare(s1) == 0); 

            string s2 = "ABC ";
            odcore::strings::StringToolbox::trim(s2);
            string ref_s2 = "ABC";
            TS_ASSERT(ref_s2.compare(s2) == 0); 

            string s3 = " ABC ";
            odcore::strings::StringToolbox::trim(s3);
            string ref_s3 = "ABC";
            TS_ASSERT(ref_s3.compare(s3) == 0); 

            string s4 = "ABC";
            odcore::strings::StringToolbox::trim(s4);
            string ref_s4 = "ABC";
            TS_ASSERT(ref_s4.compare(s4) == 0); 

            string s5 = "";
            odcore::strings::StringToolbox::trim(s5);
            string ref_s5 = "";
            TS_ASSERT(ref_s5.compare(s5) == 0); 
        }

        void testCompareIgnoreCase() {
            string s1 = "ABC";
            string s2 = "ABC";
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(s1, s2)); 

            string s3 = "abc";
            string s4 = "ABC";
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(s3, s4)); 
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(s4, s3)); 

            string s5 = "abc";
            string s6 = "abc";
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(s5, s6)); 

            string s7 = "abc";
            string s8 = "abd";
            TS_ASSERT(!odcore::strings::StringToolbox::equalsIgnoreCase(s7, s8)); 

            string s9 = "abc";
            string s10 = "abc ";
            TS_ASSERT(!odcore::strings::StringToolbox::equalsIgnoreCase(s9, s10)); 
        }

        void testSplitSemantics() {
            string s1 = "abc";
            vector<string> vs1 = odcore::strings::StringToolbox::split(s1, ',');
            TS_ASSERT(vs1.size() == 1);
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs1.at(0), "abc"));

            string s1a = "abc;";
            vector<string> vs1a = odcore::strings::StringToolbox::split(s1a, ';');
            TS_ASSERT(vs1a.size() == 2);
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs1a.at(0), "abc"));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs1a.at(1), ""));

            string s1b = ";abc";
            vector<string> vs1b = odcore::strings::StringToolbox::split(s1b, ';');
            TS_ASSERT(vs1b.size() == 2);
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs1b.at(0), ""));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs1b.at(1), "abc"));

            string s1c = ";abc;";
            vector<string> vs1c = odcore::strings::StringToolbox::split(s1c, ';');
            TS_ASSERT(vs1c.size() == 3);
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs1c.at(0), ""));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs1c.at(1), "abc"));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs1c.at(2), ""));

            string s1d = ";abc;;";
            vector<string> vs1d = odcore::strings::StringToolbox::split(s1d, ';');
            TS_ASSERT(vs1d.size() == 4);
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs1d.at(0), ""));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs1d.at(1), "abc"));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs1d.at(2), ""));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs1d.at(3), ""));

            string s2 = "abc;def";
            vector<string> vs2_no = odcore::strings::StringToolbox::split(s2, ',');
            TS_ASSERT(vs2_no.size() == 1);
            vector<string> vs2 = odcore::strings::StringToolbox::split(s2, ';');
            TS_ASSERT(vs2.size() == 2);
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs2.at(0), "abc"));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs2.at(1), "def"));

            string s3 = ";abc;def";
            vector<string> vs3 = odcore::strings::StringToolbox::split(s3, ';');
            TS_ASSERT(vs3.size() == 3);
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs3.at(0), ""));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs3.at(1), "abc"));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs3.at(2), "def"));

            string s4 = "abc;def;";
            vector<string> vs4 = odcore::strings::StringToolbox::split(s4, ';');
            TS_ASSERT(vs4.size() == 3);
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs4.at(0), "abc"));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs4.at(1), "def"));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs4.at(2), ""));

            string s5 = ";abc;def;";
            vector<string> vs5 = odcore::strings::StringToolbox::split(s5, ';');
            TS_ASSERT(vs5.size() == 4);
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs5.at(0), ""));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs5.at(1), "abc"));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs5.at(2), "def"));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs5.at(3), ""));

            string s6 = ";abc;def;;";
            vector<string> vs6 = odcore::strings::StringToolbox::split(s6, ';');
            TS_ASSERT(vs6.size() == 5);
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs6.at(0), ""));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs6.at(1), "abc"));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs6.at(2), "def"));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs6.at(3), ""));
            TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(vs6.at(4), ""));
        }

};

#endif /*CORE_STRINGTOOLBOXTESTSUITE_H_*/
