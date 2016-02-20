/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

#include "opendavinci/odcore/base/FIFOQueue.h"
#include "opendavinci/odcore/base/Serializable.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/base/module/AbstractCIDModule.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/generated/coredata/buffer/MemorySegment.h"
#include "opendavinci/odtools/recorder/SharedDataWriter.h"

namespace odtools {
    namespace recorder {

        using namespace odcore;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odtools;

        SharedDataWriter::SharedDataWriter(SharedPointer<ostream> out, map<uint32_t, char*> &mapOfMemories, FIFOQueue &bufferIn, FIFOQueue &bufferOut) :
            m_out(out),
            m_mapOfMemories(mapOfMemories),
            m_bufferIn(bufferIn),
            m_bufferOut(bufferOut)
            {}

        SharedDataWriter::~SharedDataWriter() {
            CLOG1 << "SharedDataWriter: Cleaning queue... ";
            recordEntries();
            CLOG1 << "done." << endl;
        }

        void SharedDataWriter::beforeStop() {}

        void SharedDataWriter::recordEntries() {
            while (!m_bufferOut.isEmpty()) {
                if (m_out->good()) {
                    // Get next entry to process from output queue.
                    Container c = m_bufferOut.leave();
                    coredata::buffer::MemorySegment ms = c.getData<coredata::buffer::MemorySegment>();

                    // Get meta data to be written as header.
                    Container header = ms.getHeader();

                    // Get pointer to memory with the data.
                    char *ptrToMemory = m_mapOfMemories[ms.getIdentifier()];

                    (*m_out) << header;
                    m_out->write(ptrToMemory, ms.getConsumedSize());

                    // Reset meta information.
                    ms.setConsumedSize(0);

                    // Save meta information.
                    c = Container(Container::UNDEFINEDDATA, ms);

                    // After processing, put memory segment back into input queue.
                    m_bufferIn.enter(c);

                    // Write to disk to not loose the content.
                    m_out->flush();
                }

                // Allow rescheduling between processing the different containers.
                Thread::usleepFor(500);
            }
        }

        void SharedDataWriter::run() {
            serviceReady();

            while (isRunning()) {
                recordEntries();

                // Allow rescheduling for 5ms between the next cycle.
                Thread::usleepFor(5000);
            }
        }

    } // recorder
} // tools

