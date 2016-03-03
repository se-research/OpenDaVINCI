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

#include "ipcsharedmemory.h"

using namespace std;

int32_t main(int32_t argc, char **argv) {
    const string NAME = "MySharedMemory";
    const uint32_t SIZE = 26;
    int i;

    try {
        SharedMemoryExample sme(NAME, SIZE);
        i = 10;
        sme.createSharedMemory();
        sme.writeSharedMemory();
        sme.releaseSharedMemory();
    }
    catch(string &exception) {
        cerr << "Shared memory could not created: " << exception << endl;
    }
}

