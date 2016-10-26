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

#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/odcore/wrapper/SharedMemory.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>

#include "ipcsharedmemory.h"

using namespace std;

// We add some of OpenDaVINCI's namespaces for the sake of readability.
using namespace odcore;
using namespace odcore::wrapper;

SharedMemoryExample::SharedMemoryExample(const string &name, const uint32_t &size) :
    m_sharedMemory(),
    m_name(name),
    m_size(size)
    {}

void SharedMemoryExample::createSharedMemory() {
    if (!m_sharedMemory.get()) {
        m_sharedMemory = SharedMemoryFactory::createSharedMemory(m_name, m_size);
    }
}

void SharedMemoryExample::releaseSharedMemory() {
    m_sharedMemory.reset();
}

void SharedMemoryExample::writeSharedMemory() {
    if (m_sharedMemory.get()) {
        char *p = static_cast<char*>(m_sharedMemory->getSharedMemory());
        for (uint32_t i = 0; i < m_sharedMemory->getSize(); i++) {
            char c = (char) (65 + (i%26));
            p[i] = c;
        }
    }
}

