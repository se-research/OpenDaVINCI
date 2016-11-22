/**
 * odrecinspect - Tool for inspecting recorded data
 * Copyright (C) 2014 - 2016 Christian Berger
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

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>

#include <opendavinci/odcore/data/TimeStamp.h>
#include <opendavinci/generated/odcore/data/SharedData.h>
#include <opendavinci/generated/odcore/data/image/SharedImage.h>
#include <opendavinci/generated/odcore/data/SharedPointCloud.h>

#include "RecInspect.h"

namespace odrecinspect {

    using namespace std;
    using namespace odcore;
    using namespace odcore::base;
    using namespace odcore::data;

    RecInspect::RecInspect() :
        m_numberOfContainersPerType(),
        m_latestContainersPerType(),
        m_minDurationBetweenSamplesPerType(),
        m_avgDurationBetweenSamplesPerType(),
        m_maxDurationBetweenSamplesPerType(),
        m_processingTimePerContainer(0) {}

    RecInspect::~RecInspect() {}

    int32_t RecInspect::run(const int32_t &argc, char **argv) {
        enum RETURN_CODE { CORRECT = 0,
                           FILE_CORRUPT = 1,
                           FILE_COULD_NOT_BE_OPENED = 255 };

        RETURN_CODE retVal = CORRECT;

        if (argc == 2) {
            const string FILENAME(argv[1]);
            fstream fin;
            fin.open(FILENAME.c_str(), ios_base::in|ios_base::binary);

            if (fin.good()) {
                // Determine file size.
                fin.seekg(0, fin.end);
                int32_t length = fin.tellg();
                fin.seekg(0, fin.beg);

                int32_t oldPercentage = -1;
                bool fileNotCorrupt = true;
                uint32_t numberOfSharedImages = 0;
                uint32_t numberOfSharedData = 0;
                uint32_t numberOfSharedPointCloud = 0;

                stringstream streamBuffer;

                Container lastContainer;
                TimeStamp beforeProcessing;
                while (fin.good()) {
                    Container c;

                    {
                        TimeStamp b;
                            fin >> c;
                        TimeStamp a;

                        if (lastContainer.getDataType() != 0) {
                            m_processingTimePerContainer += (a - b).toMicroseconds()/1000.0;
                        }
                        lastContainer = c;
                    }

                    if (fin.gcount() > 0) {
                        int32_t currPos = fin.tellg();

                        fileNotCorrupt &= (c.getDataType() != Container::UNDEFINEDDATA) && (currPos > 0);

                        // Compute durations between containers of a specific type.
                        if (m_numberOfContainersPerType.count(c.getDataType()) > 0) {
                            TimeStamp duration = c.getSampleTimeStamp() - m_latestContainersPerType[c.getDataType()].getSampleTimeStamp();
                            const uint64_t durationInMicroseconds = abs(duration.toMicroseconds());
                            const double d = durationInMicroseconds / 1000.0;
                            m_minDurationBetweenSamplesPerType[c.getDataType()] = (m_minDurationBetweenSamplesPerType[c.getDataType()] > d) ? d : m_minDurationBetweenSamplesPerType[c.getDataType()];
                            m_avgDurationBetweenSamplesPerType[c.getDataType()].push_back(durationInMicroseconds);
                            m_maxDurationBetweenSamplesPerType[c.getDataType()] = (m_maxDurationBetweenSamplesPerType[c.getDataType()] < d) ? d : m_maxDurationBetweenSamplesPerType[c.getDataType()];
                        }
                        if (m_numberOfContainersPerType.count(c.getDataType()) == 0) {
                            m_numberOfContainersPerType[c.getDataType()] = 0;
                            m_minDurationBetweenSamplesPerType[c.getDataType()] = 1000 * 1000 * 60;
                            m_maxDurationBetweenSamplesPerType[c.getDataType()] = 0;
                        }
                        m_numberOfContainersPerType[c.getDataType()] = m_numberOfContainersPerType[c.getDataType()] + 1;
                        m_latestContainersPerType[c.getDataType()] = c;

                        // If the data is from SHARED_IMAGE, skip the raw data from the shared memory segment.
                        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
                            odcore::data::image::SharedImage si = c.getData<odcore::data::image::SharedImage>();

                            uint32_t lengthToSkip = si.getSize();
                            if (lengthToSkip == 0) {
                                lengthToSkip = si.getWidth() * si.getHeight() * si.getBytesPerPixel();
                            }

                            fin.seekg(currPos + lengthToSkip);
                            numberOfSharedImages++;
                        }
                        else if (c.getDataType() == odcore::data::SharedData::ID()) {
                            odcore::data::SharedData sd = c.getData<odcore::data::SharedData>();

                            uint32_t lengthToSkip = sd.getSize();

                            fin.seekg(currPos + lengthToSkip);
                            numberOfSharedData++;
                        }
                        else if (c.getDataType() == odcore::data::SharedPointCloud::ID()) {
                            odcore::data::SharedPointCloud spc = c.getData<odcore::data::SharedPointCloud>();

                            uint32_t lengthToSkip = spc.getSize();

                            fin.seekg(currPos + lengthToSkip);
                            numberOfSharedPointCloud++;
                        }

                        float percentage = (float)(currPos*100.0)/(float)length;

                        if ( ((int32_t)percentage % 5 == 0) && ((int32_t)percentage != oldPercentage) ) {
                            cout << "[RecInspect]: " << (int32_t)percentage << "% (" << currPos << "/" << length << " bytes processed)." << endl;
                            oldPercentage = (int32_t)percentage;
                        }
                    }
                }
                TimeStamp afterProcessing;
                TimeStamp durationProcessing = (afterProcessing - beforeProcessing);
                cout << "[RecInspect]: 100% (" << length << "/" << length << " bytes processed)." << endl;
                cout << "[RecInspect]: Input file is " << ((fileNotCorrupt) ? "not " : "") << "corrupt." << endl;
                const double lengthInMB = (static_cast<double>(length)/(1000.0*1000.0));
                const double durationInSeconds = (static_cast<double>(durationProcessing.toMicroseconds())/(1000.0*1000.0));
                cout << "[RecInspect]: Processing took " << durationProcessing.toMicroseconds()/1000 << " ms (" << (lengthInMB/durationInSeconds) << " MB/s)." << endl;

                uint32_t numberOfTotalContainers = 0;
                for(auto it = m_numberOfContainersPerType.begin(); it != m_numberOfContainersPerType.end(); ++it) {
                    // Compute average and stddev:
                    const double average = accumulate(m_avgDurationBetweenSamplesPerType[it->first].begin(), m_avgDurationBetweenSamplesPerType[it->first].end(), 0.0)/m_avgDurationBetweenSamplesPerType[it->first].size();

                    vector<double> diff(m_avgDurationBetweenSamplesPerType[it->first].size());
                    transform(m_avgDurationBetweenSamplesPerType[it->first].begin(), m_avgDurationBetweenSamplesPerType[it->first].end(), diff.begin(), bind2nd(minus<double>(), average));
                    const double sqSum = inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
                    const double stddev = sqrt(sqSum/static_cast<double>(m_avgDurationBetweenSamplesPerType[it->first].size()));

                    cout << "[RecInspect]: Container type " << it->first << ", entries = " << it->second << ", min = " << m_minDurationBetweenSamplesPerType[it->first] << " ms, avg = " << average/1000.0 << " ms, stddev = " << stddev/1000.0 << " ms, max = " << m_maxDurationBetweenSamplesPerType[it->first] << " ms." << endl;
                    numberOfTotalContainers += it->second;
                }
                cout << "[RecInspect]: Found " << numberOfTotalContainers << " containers in total; average duration for reading one container = " << m_processingTimePerContainer/static_cast<double>(numberOfTotalContainers) << " ms." << endl;

                retVal = ((fileNotCorrupt) ? CORRECT : FILE_CORRUPT);
            }
            else {
                retVal = FILE_COULD_NOT_BE_OPENED;
            }
        }

        return retVal;
    }

} // odrecinspect

