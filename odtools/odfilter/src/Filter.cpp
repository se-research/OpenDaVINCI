/**
 * odfilter - Tool for filtering container streams in pipes
 * Copyright (C) 2015 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <algorithm>
#include <iostream>
#include <sstream>

#include "opendavinci/odcore/base/CommandLineParser.h"
#include "opendavinci/odcore/serialization/QueryableNetstringsDeserializerABCF.h"
#include "opendavinci/odcore/strings/StringToolbox.h"
#include "opendavinci/odcore/data/Container.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

#include "Filter.h"

namespace odfilter {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;

    Filter::Filter() :
        m_keep(),
        m_drop() {}

    Filter::~Filter() {}

    void Filter::parseAdditionalCommandLineParameters(const int &argc, char **argv) {
        CommandLineParser cmdParser;
        cmdParser.addCommandLineArgument("keep");
        cmdParser.addCommandLineArgument("drop");

        cmdParser.parse(argc, argv);

        CommandLineArgument cmdArgumentKEEP = cmdParser.getCommandLineArgument("keep");
        CommandLineArgument cmdArgumentDROP = cmdParser.getCommandLineArgument("drop");

        if (cmdArgumentKEEP.isSet()) {
            string toKeep = cmdArgumentKEEP.getValue<string>();
            m_keep = getListOfNumbers(toKeep);
        }

        if (cmdArgumentDROP.isSet()) {
            string toDrop = cmdArgumentDROP.getValue<string>();
            m_drop = getListOfNumbers(toDrop);
        }
    }

    vector<uint32_t> Filter::getListOfNumbers(const string &s) {
        vector<uint32_t> listOfNumbers;
        vector<string> listOfStringNumbers = odcore::strings::StringToolbox::split(s, ',');
        if (listOfStringNumbers.size() == 0) {
            // If only one ID was specified, simply add s to listOfStringNumbers.
            listOfStringNumbers.push_back(s);
        }

        vector<string>::iterator it = listOfStringNumbers.begin();
        while (it != listOfStringNumbers.end()) {
            int32_t value = 0;
            stringstream sstr;

            sstr << (*it);
            sstr >> value;

            if (value > 0) {
                uint32_t v = static_cast<uint32_t>(value);
                vector<uint32_t>::iterator jt = find(listOfNumbers.begin(), listOfNumbers.end(), v);
                if (jt == listOfNumbers.end()) {
                    listOfNumbers.push_back(v);
                }
            }

            it++;
        }

        sort(listOfNumbers.begin(), listOfNumbers.end());
        return listOfNumbers;
    }


    int32_t Filter::run(const int32_t &argc, char **argv) {
        enum RETURN_CODE { CORRECT = 0,
                           BOTH_KEEP_DROP = 1 };

        RETURN_CODE retVal = CORRECT;

        // Parse command line arguments.
        parseAdditionalCommandLineParameters(argc, argv);

        if ( (m_keep.size() > 0) && (m_drop.size() > 0) ) {
            cerr << "[odfilter] Error: You cannot specify --keep and --drop at the same time." << endl;
            retVal = BOTH_KEEP_DROP;
        }
        else {
            // Please note that reading from stdin does not evaluate sending latencies.
            while (cin.good()) {
                // Buffer from cin.
                stringstream containerBuffer;
                // Fill buffer.
                QueryableNetstringsDeserializerABCF::fillBuffer(cin, containerBuffer);

                // Decode container from buffer.
                Container c;
                containerBuffer >> c;

                uint32_t id = c.getDataType();

                if (c.getDataType() > 0) {
                    if (m_keep.size() > 0) {
                        vector<uint32_t>::iterator jt = find(m_keep.begin(), m_keep.end(), id);
                        if (jt != m_keep.end()) {
                            // Container is to keep, push it to stdout.
                            std::cout << c;
                        }
                    }
                    if (m_drop.size() > 0) {
                        vector<uint32_t>::iterator jt = find(m_drop.begin(), m_drop.end(), id);
                        if (jt == m_drop.end()) {
                            // Container ID is not in dropping list, push it to stdout.
                            std::cout << c;
                        }
                    }
                    std::cout.rdbuf()->pubsync();
                    std::cout.flush();
                }

            }
        }

        return retVal;
    }

} // odfilter

