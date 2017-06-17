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
    using namespace odcore::serialization;

    Filter::Filter() :
        m_keep(),
        m_drop(),
        m_downsampling(),
        m_downsamplingCounter(),
        m_sampleTimeStampToSentTimeStampDifference(-1) {}

    Filter::~Filter() {}

    void Filter::parseAdditionalCommandLineParameters(const int &argc, char **argv) {
        CommandLineParser cmdParser;
        cmdParser.addCommandLineArgument("keep");
        cmdParser.addCommandLineArgument("drop");
        cmdParser.addCommandLineArgument("downsample");
        cmdParser.addCommandLineArgument("replaceSampleTimeWithSentTimeIfGreaterThan");

        cmdParser.parse(argc, argv);

        CommandLineArgument cmdArgumentKEEP = cmdParser.getCommandLineArgument("keep");
        CommandLineArgument cmdArgumentDROP = cmdParser.getCommandLineArgument("drop");
        CommandLineArgument cmdArgumentDOWNSAMPLE = cmdParser.getCommandLineArgument("downsample");
        CommandLineArgument cmdArgumentREPLACESAMPLETS = cmdParser.getCommandLineArgument("replaceSampleTimeWithSentTimeIfGreaterThan");

        if (cmdArgumentKEEP.isSet()) {
            string toKeep = cmdArgumentKEEP.getValue<string>();
            m_keep = getListOfNumbers(toKeep);
        }

        if (cmdArgumentDROP.isSet()) {
            string toDrop = cmdArgumentDROP.getValue<string>();
            m_drop = getListOfNumbers(toDrop);
        }

        if (cmdArgumentDOWNSAMPLE.isSet()) {
            string toDownSample = cmdArgumentDOWNSAMPLE.getValue<string>();
            m_downsampling = getMapOfDownSampling(toDownSample);
            m_downsamplingCounter = m_downsampling;
        }

        if (cmdArgumentREPLACESAMPLETS.isSet()) {
            m_sampleTimeStampToSentTimeStampDifference = cmdArgumentREPLACESAMPLETS.getValue<int64_t>();
        }
    }

    vector<uint32_t> Filter::getListOfNumbers(const string &s) {
        vector<uint32_t> listOfNumbers;

        vector<string> listOfStringNumbers = odcore::strings::StringToolbox::split(s, ',');
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

    map<int32_t, uint32_t> Filter::getMapOfDownSampling(const string &s) {
        map<int32_t, uint32_t> mapOfDownSampledContainers;

        vector<string> listOfColonPairs = odcore::strings::StringToolbox::split(s, ',');
        vector<string>::iterator it = listOfColonPairs.begin();
        while (it != listOfColonPairs.end()) {
            vector<string> downSamplingPair = odcore::strings::StringToolbox::split(*it, ':');
            if (downSamplingPair.size() == 2) {
                int32_t container = 0;
                uint32_t sampling = 0;

                {
                    stringstream sstr;
                    sstr << downSamplingPair[0];
                    sstr >> container;
                }
                {
                    stringstream sstr;
                    sstr << downSamplingPair[1];
                    sstr >> sampling;
                }

                mapOfDownSampledContainers[container] = sampling;
            }

            it++;
        }

        return mapOfDownSampledContainers;
    }

    int32_t Filter::run(const int32_t &argc, char **argv) {
        enum RETURN_CODE { CORRECT = 0,
                           BOTH_KEEP_DROP = 1,
                           NONE_GIVEN = 2 };

        RETURN_CODE retVal = CORRECT;

        // Parse command line arguments.
        parseAdditionalCommandLineParameters(argc, argv);

        if ( (m_keep.size() > 0) && (m_drop.size() > 0) ) {
            cerr << "[odfilter] Error: You cannot specify --keep and --drop at the same time." << endl;
            retVal = BOTH_KEEP_DROP;
        }
        else if ( (m_keep.size() == 0) && (m_drop.size() == 0) && (m_downsampling.size() == 0) && (m_sampleTimeStampToSentTimeStampDifference == -1) ) {
            cerr << "[odfilter] Error: You must specify either --keep, --downsample, --drop, or --replaceSampleTimeWithSentTimeIfGreaterThan." << endl;
            retVal = NONE_GIVEN;
        }
        else {
            // Please note that reading from stdin does not evaluate sending latencies.
            while (cin.good()) {
                // Read next Container.
                Container c;
                cin >> c;

                // Check whether the sampleTimeStamp needs to be fixed.
                if (m_sampleTimeStampToSentTimeStampDifference > 0) {
                    int64_t differenceSampleTimeStampVsSentTimeStamp = abs(c.getSentTimeStamp().toMicroseconds() - c.getSampleTimeStamp().toMicroseconds());
                    if (differenceSampleTimeStampVsSentTimeStamp > m_sampleTimeStampToSentTimeStampDifference) {
                        c.setSampleTimeStamp(c.getSentTimeStamp());
                    }
                }

                uint32_t id = c.getDataType();

                if (c.getDataType() > 0) {
                    if (m_downsampling.count(id) > 0) {
                        m_downsamplingCounter[id] = m_downsamplingCounter[id] - 1;
                        if (m_downsamplingCounter[id] == 0) {
                            // Reset counter and emit container.
                            m_downsamplingCounter[id] = m_downsampling[id];
                            cout << c;
                        }
                    }
                    else {
                        if (m_keep.size() > 0) {
                            vector<uint32_t>::iterator jt = find(m_keep.begin(), m_keep.end(), id);
                            if (jt != m_keep.end()) {
                                // Container is to keep, push it to stdout.
                                cout << c;
                            }
                        }
                        if (m_drop.size() > 0) {
                            vector<uint32_t>::iterator jt = find(m_drop.begin(), m_drop.end(), id);
                            if (jt == m_drop.end()) {
                                // Container ID is not in dropping list, push it to stdout.
                                cout << c;
                            }
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

