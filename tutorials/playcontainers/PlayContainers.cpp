/**
 * OpenDaVINCI - Tutorial.
 * Copyright (C) 2017 Christian Berger
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

#include <iostream>

#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/io/URL.h>
#include <opendavinci/odtools/player/Player.h>

#include <opendavinci/odcore/wrapper/SharedMemory.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>

#include <opendavinci/generated/odcore/data/SharedPointCloud.h>

using namespace std;

int32_t main(int32_t argc, char **argv) {
    if (2 != argc) {
        cerr << "Use with: " << argv[0] << " file.rec" << endl;
        return -1;
    }
    else {
        // Setting file for playback.
        odcore::io::URL url("file://" + string(argv[1]));
        // Size of the memory buffer (should be large enough to hold point clouds for example).
        const uint32_t MEMORY_SEGMENT_SIZE = 3*1024*1024;
        // Number of memory segments.
        const uint32_t NUMBER_OF_SEGMENTS = 3;
        // If AUTO_REWIND is true, the file will be played endlessly.
        const bool AUTO_REWIND = false;
        // For sequential playback, THREADING must be set to false.
        const bool TRHEADING = false;
        // Construct the player.
        odtools::player::Player player(url, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, TRHEADING);

        std::shared_ptr<odcore::wrapper::SharedMemory> spcSharedMemory;

        while (player.hasMoreData()) {
            // Read the next container from file.
            odcore::data::Container c = player.getNextContainerToBeSent();

            cout << "Found Container " << c.getDataType()
                                       << ", sent " << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms()
                                       << ", received " << c.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms()
                                       << ", sample time stamp " << c.getSampleTimeStamp().getYYYYMMDD_HHMMSSms() << endl;

            if (c.getDataType() == odcore::data::SharedPointCloud::ID()) {
                odcore::data::SharedPointCloud spc = c.getData<odcore::data::SharedPointCloud>();
                cout << spc.toString() << endl;

                if (spcSharedMemory.get() != NULL) {
                    // Attach the shared point cloud to the shared memory.
                    spcSharedMemory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(spc.getName());
                }
                else {
                    odcore::base::Lock l(spcSharedMemory);
                    // TODO: Do something with the raw data in memory; cf. https://github.com/se-research/OpenDaVINCI/blob/master/odcockpit/src/plugins/environmentviewer/EnvironmentViewerGLWidget.cpp#L489-L558
                }
            }
        }

    }
}

