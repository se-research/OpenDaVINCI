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
#include <core/SharedPointer.h>
#include <core/base/Thread.h>
#include <core/wrapper/SharedMemory.h>
#include <core/wrapper/SharedMemoryFactory.h>

using namespace std;

// We add some of OpenDaVINCI's namespaces for the sake of readability.
using namespace core;
using namespace core::wrapper;

int32_t main(int32_t argc, char **argv) {
    const string NAME = "MySharedMemory";
    const uint32_t SIZE = 26;

    // We are using OpenDaVINCI's SharedPointer to automatically
    // release any acquired resources.
    try {
        SharedPointer<SharedMemory> sharedMemory(SharedMemoryFactory::createSharedMemory(NAME, SIZE));

        if (sharedMemory->isValid()) {
            uint32_t counter = 20;
            while (counter-- > 0) {
                // Lock shared memory.
                sharedMemory->lock();
                    char *p = static_cast<char*>(sharedMemory->getSharedMemory());
                    for (uint32_t i = 0; i < sharedMemory->getSize(); i++) {
                        char c = (char) (65 + ((i+counter)%26));
                        p[i] = c;
                    }
                // Unlock memory.
                sharedMemory->unlock();

                // Sleep some time.
                const uint32_t ONE_SECOND = 1000 * 1000;
                core::base::Thread::usleepFor(ONE_SECOND);
            }
        }
    }
    catch(string &exception) {
        cerr << "Shared memory could not created: " << exception << endl;
    }
}

