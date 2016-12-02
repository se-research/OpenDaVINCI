/**
 * odrec2fuse - Mounting .rec files via Fuse into a directory.
 * Copyright (C) 2016 Christian Berger
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

#include <opendavinci/odcore/data/Container.h>

#include "Rec2Fuse.h"

namespace odrec2fuse {

    using namespace std;
    using namespace odcore;
    using namespace odcore::base;
    using namespace odcore::data;

    Rec2Fuse::Rec2Fuse() {}

    Rec2Fuse::~Rec2Fuse() {}

    int32_t Rec2Fuse::run(const int32_t &argc, char **argv) {
        enum RETURN_CODE { CORRECT = 0,
                           FILE_COULD_NOT_BE_OPENED = 255 };

        RETURN_CODE retVal = CORRECT;

        if (argc > 1) {
            const string FILENAME(argv[1]);
            fstream fin;
            fin.open(FILENAME.c_str(), ios_base::in|ios_base::binary);

            if (fin.good()) {
                // Determine file size.
                fin.seekg(0, fin.end);
                int32_t length = fin.tellg();
                fin.seekg(0, fin.beg);

                int32_t oldPercentage = -1;

                while (fin.good()) {
                    Container c;
                    fin >> c;

                    if (fin.gcount() > 0) {
                        int32_t currPos = fin.tellg();

                        float percentage = (float)(currPos*100.0)/(float)length;

                        if ( ((int32_t)percentage % 5 == 0) && ((int32_t)percentage != oldPercentage) ) {
                            cout << "[Rec2Fuse]: " << (int32_t)percentage << "% (" << currPos << "/" << length << " bytes processed)." << endl;
                            oldPercentage = (int32_t)percentage;
                        }
                    }
                }
            }
            else {
                retVal = FILE_COULD_NOT_BE_OPENED;
            }
        }

        return retVal;
    }

} // odrec2fuse

