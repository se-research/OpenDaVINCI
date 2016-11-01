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

#ifndef OPENDAVINCI_CORE_STRINGS_STRINGTOOLBOX_H_
#define OPENDAVINCI_CORE_STRINGS_STRINGTOOLBOX_H_

#include "opendavinci/odcore/opendavinci.h"

#include <algorithm>
#include <string>
#include <vector>

namespace odcore {
    namespace strings {

        using namespace std;

        /**
         * This class can be used to perform some useful operations on strings (i.e. remove leading
         * and trailing blanks for example).
         */
        class StringToolbox {
            public:
                virtual ~StringToolbox() {};

                /**
                 * This method removes leading and trailing blanks.
                 *
                 * @param s String to be trimmed.
                 */
                static void trim(string &s);

                /**
                 * This method replaces all occurrences of character FROM
                 * to character TO.
                 *
                 * @param FROM replace any occurrence of this character
                 * @param TO by this character.
                 */
                static string replaceAll(const string &s, const char &FROM, const char &TO);

                /**
                 * This method compares two strings while ignoring case.
                 *
                 * @param s1 String 1
                 * @param s2 String 2
                 * @return true if s1 equals s2
                 */
                static bool equalsIgnoreCase(const string &s1, const string &s2);

                /**
                 * This method splits a string using the delimiter according to
                 * the following semantics:
                 *
                 * split("tokenA", ';').size() == 1.
                 * split("tokenA;", ';').size() == 1.
                 * split(";tokenA", ';').size() == 2.
                 * split(";tokenA;", ';').size() == 2.
                 * split(";tokenA;;", ';').size() == 3.
                 *
                 * @param s String to split.
                 * @param delimiter
                 * @return Vector of tokens.
                 */
                static vector<string> split(const string &s, const char &delimiter);

        };
    }
}

#endif /*OPENDAVINCI_CORE_STRINGS_STRINGTOOLBOX_H_*/
