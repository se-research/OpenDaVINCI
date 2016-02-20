/**
 * OpenDaVINCI - Tutorial.
 * Copyright (C) 2015 Christian Berger
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

#include <stdint.h>
#include <iostream>
#include <string>
#include <opendavinci/odcore/SharedPointer.h>
#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/odcore/wrapper/SharedMemory.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>

using namespace std;

// We add some of OpenDaVINCI's namespaces for the sake of readability.
using namespace odcore;
using namespace odcore::wrapper;

int32_t main(int32_t argc, char **argv) {
    const string NAME = "MySharedMemory";

    // We are using OpenDaVINCI's SharedPointer to automatically
    // release any acquired resources.
    try {
        SharedPointer<SharedMemory> sharedMemory(SharedMemoryFactory::attachToSharedMemory(NAME));

        if (sharedMemory->isValid()) {
            uint32_t counter = 10;
            while (counter-- > 0) {
                string s;
                {
                    // Using a scoped lock to lock and automatically unlock a shared memory segment.
                    odcore::base::Lock l(sharedMemory);
                    char *p = static_cast<char*>(sharedMemory->getSharedMemory());
                    s = string(p);
                }

                cout << "Content of shared memory: '" << s << "'" << endl;

                // Sleep some time.
                const uint32_t ONE_SECOND = 1000 * 1000;
                odcore::base::Thread::usleepFor(0.5 * ONE_SECOND);
            }
        }
    }
    catch(string &exception) {
        cerr << "Shared memory could not created: " << exception << endl;
    }
}

