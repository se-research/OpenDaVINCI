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

    ////////////////////////////////////////////////////////////////////////////

    ContainerEntry::ContainerEntry() :
        m_numberOfContainersPerType(0),
        m_latestContainersPerType(),
        m_numberOfContainersInIncorrectTemporalOrderPerType(0),
        m_minDurationBetweenSamplesPerType(0),
        m_avgDurationBetweenSamplesPerType(),
        m_maxDurationBetweenSamplesPerType(0) {}

    ContainerEntry::~ContainerEntry() {}

    ContainerEntry::ContainerEntry(const ContainerEntry &ce) :
        m_numberOfContainersPerType(ce.m_numberOfContainersPerType),
        m_latestContainersPerType(ce.m_latestContainersPerType),
        m_numberOfContainersInIncorrectTemporalOrderPerType(ce.m_numberOfContainersInIncorrectTemporalOrderPerType),
        m_minDurationBetweenSamplesPerType(ce.m_minDurationBetweenSamplesPerType),
        m_avgDurationBetweenSamplesPerType(ce.m_avgDurationBetweenSamplesPerType),
        m_maxDurationBetweenSamplesPerType(ce.m_maxDurationBetweenSamplesPerType) {}

    ContainerEntry& ContainerEntry::operator=(const ContainerEntry &ce) {
        m_numberOfContainersPerType = ce.m_numberOfContainersPerType;
        m_latestContainersPerType = ce.m_latestContainersPerType;
        m_numberOfContainersInIncorrectTemporalOrderPerType = ce.m_numberOfContainersInIncorrectTemporalOrderPerType;
        m_minDurationBetweenSamplesPerType = ce.m_minDurationBetweenSamplesPerType;
        m_avgDurationBetweenSamplesPerType = ce.m_avgDurationBetweenSamplesPerType;
        m_maxDurationBetweenSamplesPerType = ce.m_maxDurationBetweenSamplesPerType;
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////

    RecInspect::RecInspect() :
        m_overview(),
        m_numberOfContainersPerType(),
        m_latestContainersPerType(),
        m_numberOfContainersInIncorrectTemporalOrderPerType(),
        m_minDurationBetweenSamplesPerType(),
        m_avgDurationBetweenSamplesPerType(),
        m_maxDurationBetweenSamplesPerType(),
        m_processingTimePerContainer(0) {}

    RecInspect::~RecInspect() {}

    int32_t RecInspect::run(const int32_t &argc, char **argv) {
        enum RETURN_CODE { CORRECT = 0,
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
                uint32_t numberOfContainersInIncorrectTemporalOrder = 0;
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

                            numberOfContainersInIncorrectTemporalOrder += ((c.getSampleTimeStamp().toMicroseconds() - lastContainer.getSampleTimeStamp().toMicroseconds()) < 0);
                        }
                        lastContainer = c;
                    }

                    if (fin.gcount() > 0) {
                        int32_t currPos = fin.tellg();

                        {
                            // Compute durations between containers of a specific type.
                            map<uint32_t, ContainerEntry> e;
                            // Was this container seen before?
                            if (m_overview.count(c.getDataType()) == 0) {
                                e[c.getSenderStamp()].m_numberOfContainersPerType = 0;
                                e[c.getSenderStamp()].m_minDurationBetweenSamplesPerType = 1000 * 1000 * 60;
                                e[c.getSenderStamp()].m_maxDurationBetweenSamplesPerType = 0;
                                m_overview[c.getDataType()] = e;
                            }
                            // Was this container's sender stamp seen before?
                            e = m_overview[c.getDataType()];
                            if (e.count(c.getSenderStamp()) == 0) {
                                e[c.getSenderStamp()].m_numberOfContainersPerType = 0;
                                e[c.getSenderStamp()].m_minDurationBetweenSamplesPerType = 1000 * 1000 * 60;
                                e[c.getSenderStamp()].m_maxDurationBetweenSamplesPerType = 0;
                                m_overview[c.getDataType()] = e;
                            }
                            // Adjust data for ContainerEntry for (DataType, SenderStamp).
                            e = m_overview[c.getDataType()];
                            e[c.getSenderStamp()].m_numberOfContainersPerType++;

                            if (e[c.getSenderStamp()].m_latestContainersPerType.getDataType() > 0) {
                                TimeStamp duration = c.getSampleTimeStamp() - e[c.getSenderStamp()].m_latestContainersPerType.getSampleTimeStamp();
                                const uint64_t durationInMicroseconds = abs(duration.toMicroseconds());
                                const double d = durationInMicroseconds / 1000.0;

                                e[c.getSenderStamp()].m_minDurationBetweenSamplesPerType = (e[c.getSenderStamp()].m_minDurationBetweenSamplesPerType > d) ? d : e[c.getSenderStamp()].m_minDurationBetweenSamplesPerType;

                                vector<uint64_t> l = e[c.getSenderStamp()].m_avgDurationBetweenSamplesPerType;
                                l.push_back(durationInMicroseconds);
                                e[c.getSenderStamp()].m_avgDurationBetweenSamplesPerType = l;

cout << "1 = " << e[c.getSenderStamp()].m_maxDurationBetweenSamplesPerType << " ";
                                e[c.getSenderStamp()].m_maxDurationBetweenSamplesPerType = (e[c.getSenderStamp()].m_maxDurationBetweenSamplesPerType < d) ? d : e[c.getSenderStamp()].m_maxDurationBetweenSamplesPerType;
cout << "2 = " << e[c.getSenderStamp()].m_maxDurationBetweenSamplesPerType << endl;

                                e[c.getSenderStamp()].m_numberOfContainersInIncorrectTemporalOrderPerType += ((c.getSampleTimeStamp().toMicroseconds() - e[c.getSenderStamp()].m_latestContainersPerType.getSampleTimeStamp().toMicroseconds()) < 0);
                            }
                            else {
                                e[c.getSenderStamp()].m_numberOfContainersInIncorrectTemporalOrderPerType = 0;
                                vector<uint64_t> l;
                                e[c.getSenderStamp()].m_avgDurationBetweenSamplesPerType = l;
                            }
                            e[c.getSenderStamp()].m_latestContainersPerType = c;


                            // Save overview.
                            m_overview[c.getDataType()] = e;
                        }




{
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
                        if (m_latestContainersPerType.count(c.getDataType()) > 0) {
                            m_numberOfContainersInIncorrectTemporalOrderPerType[c.getDataType()] += ((c.getSampleTimeStamp().toMicroseconds() - m_latestContainersPerType[c.getDataType()].getSampleTimeStamp().toMicroseconds()) < 0);
                        }
                        else {
                            m_numberOfContainersInIncorrectTemporalOrderPerType[c.getDataType()] = 0;
                        }
                        m_latestContainersPerType[c.getDataType()] = c;
}

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
                const double lengthInMB = (static_cast<double>(length)/(1000.0*1000.0));
                const double durationInSeconds = (static_cast<double>(durationProcessing.toMicroseconds())/(1000.0*1000.0));
                cout << "[RecInspect]: Processing took " << durationProcessing.toMicroseconds()/1000 << " ms (" << (lengthInMB/durationInSeconds) << " MB/s)." << endl;

                {
                    uint32_t numberOfTotalContainers = 0;
                    for(auto it = m_overview.begin(); it != m_overview.end(); it++) {
                        map<uint32_t, ContainerEntry> e = it->second;
                        for(auto jt = e.begin(); jt != e.end(); jt++) {
                            // Compute average and stddev:
                            const double average = accumulate(jt->second.m_avgDurationBetweenSamplesPerType.begin(), jt->second.m_avgDurationBetweenSamplesPerType.end(), 0.0)/jt->second.m_avgDurationBetweenSamplesPerType.size();

                            vector<double> diff(jt->second.m_avgDurationBetweenSamplesPerType.size());
                            transform(jt->second.m_avgDurationBetweenSamplesPerType.begin(), jt->second.m_avgDurationBetweenSamplesPerType.end(), diff.begin(), bind2nd(minus<double>(), average));
                            const double sqSum = inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
                            const double stddev = sqrt(sqSum/static_cast<double>(jt->second.m_avgDurationBetweenSamplesPerType.size()));

                            cout << "[RecInspect]: Container type " << it->first << "/" << jt->first << ", entries = " << jt->second.m_numberOfContainersPerType;
                            if (jt->second.m_numberOfContainersInIncorrectTemporalOrderPerType > 0) {
                                cout << " (" << jt->second.m_numberOfContainersInIncorrectTemporalOrderPerType << " containers in non-monotonically increasing temporal order)";
                            }
                            cout << ", min = " << jt->second.m_minDurationBetweenSamplesPerType << " ms, avg = " << average/1000.0 << " ms, stddev = " << stddev/1000.0 << " ms, max = " << jt->second.m_maxDurationBetweenSamplesPerType << " ms." << endl;

                            numberOfTotalContainers += jt->second.m_numberOfContainersPerType;
                        }
                    }
                    cout << "[RecInspect]: Found " << numberOfTotalContainers << " containers in total." << endl;
//                    cout << "[RecInspect]: Found " << numberOfTotalContainers << " containers in total (" << numberOfContainersInIncorrectTemporalOrder << " containers with different Container IDs in non-monotonically increasing temporal order); average duration for reading one container = " << m_processingTimePerContainer/static_cast<double>(numberOfTotalContainers) << " ms." << endl;
                }
                {
                    uint32_t numberOfTotalContainers = 0;
                    for(auto it = m_numberOfContainersPerType.begin(); it != m_numberOfContainersPerType.end(); ++it) {
                        // Compute average and stddev:
                        const double average = accumulate(m_avgDurationBetweenSamplesPerType[it->first].begin(), m_avgDurationBetweenSamplesPerType[it->first].end(), 0.0)/m_avgDurationBetweenSamplesPerType[it->first].size();

                        vector<double> diff(m_avgDurationBetweenSamplesPerType[it->first].size());
                        transform(m_avgDurationBetweenSamplesPerType[it->first].begin(), m_avgDurationBetweenSamplesPerType[it->first].end(), diff.begin(), bind2nd(minus<double>(), average));
                        const double sqSum = inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
                        const double stddev = sqrt(sqSum/static_cast<double>(m_avgDurationBetweenSamplesPerType[it->first].size()));

                        cout << "[RecInspect]: Container type " << it->first << ", entries = " << it->second;
                        if (m_numberOfContainersInIncorrectTemporalOrderPerType[it->first] > 0) {
                            cout << " (" << m_numberOfContainersInIncorrectTemporalOrderPerType[it->first] << " containers in non-monotonically increasing temporal order)";
                        }
                        cout << ", min = " << m_minDurationBetweenSamplesPerType[it->first] << " ms, avg = " << average/1000.0 << " ms, stddev = " << stddev/1000.0 << " ms, max = " << m_maxDurationBetweenSamplesPerType[it->first] << " ms." << endl;
                        numberOfTotalContainers += it->second;
                    }
                    cout << "[RecInspect]: Found " << numberOfTotalContainers << " containers in total (" << numberOfContainersInIncorrectTemporalOrder << " containers with different Container IDs in non-monotonically increasing temporal order); average duration for reading one container = " << m_processingTimePerContainer/static_cast<double>(numberOfTotalContainers) << " ms." << endl;
                }

            }
            else {
                retVal = FILE_COULD_NOT_BE_OPENED;
            }
        }

        return retVal;
    }

} // odrecinspect

