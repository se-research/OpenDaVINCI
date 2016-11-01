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

#include "opendavinci/odcore/strings/StringToolbox.h"

namespace odcore {
    namespace strings {

        void StringToolbox::trim(string &s) {
            string::size_type pos = s.find_last_not_of(' ');
            if(pos != string::npos) {
                s.erase(pos + 1);

                pos = s.find_first_not_of(' ');
                if(pos != string::npos) {
                    s.erase(0, pos);
                }
            } else {
                s.erase(s.begin(), s.end());
            }
        }

        string StringToolbox::replaceAll(const string &s, const char &FROM, const char &TO) {
            string retVal = s;
            // Use algorithm toolbox to replace occurrences.
            std::replace(retVal.begin(), retVal.end(), FROM, TO);
            return retVal;
        }

        bool StringToolbox::equalsIgnoreCase(const string &s1, const string &s2) {
            if (s1.size() != s2.size()) {
                return false;
            }
            for (string::const_iterator c1 = s1.begin(), c2 = s2.begin(); c1 != s1.end(); ++c1, ++c2) {
                if (tolower(*c1) != tolower(*c2)) {
                    return false;
                }
            }
            return true;
        }

        vector<string> StringToolbox::split(const string &s, const char &delimiter) {
            vector<string> v;
            string::size_type start = 0;
            string::size_type pos = s.find_first_of(delimiter, start);
            while (pos != string::npos) {
                v.push_back(s.substr(start, pos - start));
                start = pos + 1;
                pos = s.find_first_of(delimiter, start);
            }
            if (start < s.length()) {
                v.push_back(s.substr(start, s.length() - start));
            }
            return v;
        }

    }
} // odcore::wrapper
