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

#include <fstream>
#include <iostream>
#include <string>

#include "RecIntegrity.h"
#include "opendavinci/core/base/Serializable.h"
#include "opendavinci/core/data/Container.h"
#include "opendavinci/generated/coredata/SharedData.h"
#include "opendavinci/generated/coredata/image/SharedImage.h"

namespace odrecintegrity {

    using namespace std;
    using namespace core;
    using namespace core::base;
    using namespace core::data;

    RecIntegrity::RecIntegrity() {}

    RecIntegrity::~RecIntegrity() {}

    int32_t RecIntegrity::run(const int32_t &argc, char **argv) {
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
                while (fin.good()) {
                    Container c;
                    fin >> c;

                    if (fin.gcount() > 0) {
                        int32_t currPos = fin.tellg();

                        fileNotCorrupt &= (c.getDataType() != Container::UNDEFINEDDATA) && (currPos > 0);

                        // If the data is from SHARED_IMAGE, skip the raw data from the shared memory segment.
                        if (c.getDataType() == coredata::image::SharedImage::ID()) {
                            coredata::image::SharedImage si = c.getData<coredata::image::SharedImage>();

                            uint32_t lengthToSkip = si.getSize();
                            if (lengthToSkip == 0) {
                                lengthToSkip = si.getWidth() * si.getHeight() * si.getBytesPerPixel();
                            }

                            fin.seekg(currPos + lengthToSkip);
                            cout << "[RecIntegrity]: Found SHARED_IMAGE '" << si.getName() << "' (" << lengthToSkip << " bytes)" << endl;
                            numberOfSharedImages++;
                        }
                        else if (c.getDataType() == coredata::SharedData::ID()) {
                            coredata::SharedData sd = c.getData<coredata::SharedData>();

                            uint32_t lengthToSkip = sd.getSize();

                            fin.seekg(currPos + lengthToSkip);
                            cout << "[RecIntegrity]: Found SHARED_DATA '" << sd.getName() << "' (" << lengthToSkip << " bytes)" << endl;
                            numberOfSharedData++;
                        }
                        else {
                            cout << "[RecIntegrity]: Found data type '" << c.getDataType() << "'." << endl;
                        }

                        float percentage = (float)(currPos*100.0)/(float)length;

                        if ( ((int32_t)percentage % 5 == 0) && ((int32_t)percentage != oldPercentage) ) {
                            cout << "[RecIntegrity]: " << percentage << "% (" << currPos << "/" << length << " bytes processed)." << endl;
                            oldPercentage = (int32_t)percentage;
                        }
                    }
                }
                cout << "[RecIntegrity]: Input file is " << ((fileNotCorrupt) ? "not " : "") << "corrupt, contains " << numberOfSharedImages << " shared images and " << numberOfSharedData << " shared data segments." << endl;

                retVal = ((fileNotCorrupt) ? CORRECT : FILE_CORRUPT);
            }
            else {
                retVal = FILE_COULD_NOT_BE_OPENED;
            }
        }

        return retVal;
    }

} // odrecintegrity

