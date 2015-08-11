/**
 * odrecintegrity - Tool for checking the integrity of recorded data
 * Copyright (C) 2014 - 2015 Christian Berger
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

#include <iostream>

#include "core/SharedPointer.h"
#include "core/data/Container.h"
#include "core/io/StreamFactory.h"
#include "core/io/URL.h"

#include "GeneratedHeaders_CoreData.h"

#include "RecIntegrity.h"

namespace odrecintegrity {

    using namespace std;
    using namespace core;
    using namespace core::base;
    using namespace core::data;
    using namespace core::io;

    RecIntegrity::RecIntegrity(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odrecintegrity")
        {}

    RecIntegrity::~RecIntegrity() {}

    void RecIntegrity::setUp() {}

    void RecIntegrity::tearDown() {}

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode RecIntegrity::body() {
        // Read the URL of the file to replay.
        URL url(getKeyValueConfiguration().getValue<string>("odrecintegrity.input"));

        // Get the stream using the StreamFactory with the given URL.
        SharedPointer<istream> in = StreamFactory::getInstance().getInputStream(url);

        if (in->good()) {
            // Determine file size.
            in->seekg(0, in->end);
            int32_t length = in->tellg();
            in->seekg(0, in->beg);

            int32_t oldPercentage = -1;
            bool fileNotCorrupt = true;
            uint32_t numberOfSharedImages = 0;
            uint32_t numberOfSharedData = 0;
            while (in->good()) {
                Container c;
                (*in) >> c;

                if (in->gcount() > 0) {
                    int32_t currPos = in->tellg();

                    fileNotCorrupt &= (c.getDataType() != Container::UNDEFINEDDATA) && (currPos > 0);

                    // If the data is from SHARED_IMAGE, skip the raw data from the shared memory segment.
                    if (c.getDataType() == Container::SHARED_IMAGE) {
                        coredata::image::SharedImage si = c.getData<coredata::image::SharedImage>();

                        uint32_t lengthToSkip = si.getSize();

                        in->seekg(currPos + lengthToSkip);
                        cout << "[" << getName() << "(" << getIdentifier() << ")]: Found SHARED_IMAGE '" << si.getName() << "' (" << lengthToSkip << " bytes)" << endl;
                        numberOfSharedImages++;
                    }
                    else if (c.getDataType() == Container::SHARED_DATA) {
                        coredata::SharedData sd = c.getData<coredata::SharedData>();

                        uint32_t lengthToSkip = sd.getSize();

                        in->seekg(currPos + lengthToSkip);
                        cout << "[" << getName() << "(" << getIdentifier() << ")]: Found SHARED_DATA '" << sd.getName() << "' (" << lengthToSkip << " bytes)" << endl;
                        numberOfSharedData++;
                    }

                    float percentage = (float)(currPos*100.0)/(float)length;

                    if ( ((int32_t)percentage % 5 == 0) && ((int32_t)percentage != oldPercentage) ) {
                        cout << "[" << getName() << "(" << getIdentifier() << ")]: " << percentage << "% (" << currPos << "/" << length << " bytes processed)." << endl;
                        oldPercentage = (int32_t)percentage;
                    }
                }
            }
            cout << "[" << getName() << "(" << getIdentifier() << ")]: Input file is " << ((fileNotCorrupt) ? "not " : "") << "corrupt, contains " << numberOfSharedImages << " shared images and " << numberOfSharedData << " shared data segments." << endl;
        }

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // odrecintegrity

