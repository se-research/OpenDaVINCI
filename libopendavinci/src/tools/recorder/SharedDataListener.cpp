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

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <utility>

#include "core/base/Lock.h"
#include "core/base/module/AbstractCIDModule.h"
#include "core/data/Container.h"
#include "core/macros.h"
#include "core/wrapper/SharedMemory.h"
#include "core/wrapper/SharedMemoryFactory.h"
#include "generated/coredata/buffer/MemorySegment.h"
#include "tools/recorder/SharedDataListener.h"
#include "tools/recorder/SharedDataWriter.h"

namespace tools {
    namespace recorder {

        using namespace core;
        using namespace core::base;
        using namespace core::data;
        using namespace tools;

        SharedDataListener::SharedDataListener(SharedPointer<ostream> out, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments, const bool &threading) :
            m_threading(threading),
            m_sharedDataWriter(NULL),
		    m_mapOfAvailableSharedData(),
		    m_mapOfAvailableSharedImages(),
            m_mapOfMemories(),
            m_bufferIn(),
            m_bufferOut(),
            m_droppedSharedMemories(0),
            m_sharedPointers(),
            m_out(out) {

            CLOG1 << "SharedDataListener: preparing buffer...";
            for(uint16_t id = 0; id < numberOfMemorySegments; id++) {
                coredata::buffer::MemorySegment ms;
                ms.setSize(memorySegmentSize);
                ms.setIdentifier(id);
                void *ptr = ::malloc(ms.getSize());
                m_mapOfMemories[ms.getIdentifier()] = static_cast<char*>(ptr);

                Container c(Container::UNDEFINEDDATA, ms);
                m_bufferIn.enter(c);
            }
            CLOG1 << "done." << endl;

            // Hand over the buffer to the writer.
            m_sharedDataWriter = auto_ptr<SharedDataWriter>(new SharedDataWriter(m_out, m_mapOfMemories, m_bufferIn, m_bufferOut));
            if ( (m_sharedDataWriter.get() != NULL) && (m_threading) ) {
                m_sharedDataWriter->start();
            }
        }

        SharedDataListener::~SharedDataListener() {
            if ( (m_sharedDataWriter.get() != NULL) && (m_threading) ) {
                m_sharedDataWriter->stop();
            }

            // We need to explicitly release our pointer to SharedDataWriter to record the remaining entries.
            m_sharedDataWriter.reset();

            CLOG1 << "SharedDataListener: Cleaning up buffers..." << endl;

            m_out->flush();

            for(map<uint32_t, char*>::iterator it = m_mapOfMemories.begin();
                it != m_mapOfMemories.end(); ++it) {
                CLOG1 << "  Cleaning memory segment " << it->first << endl;
                ::free(it->second);
            }

            m_bufferIn.clear();
            m_bufferOut.clear();

            CLOG1 << "done." << endl;
        }

        bool SharedDataListener::copySharedMemoryToMemorySegment(const string &name, const Container &header) {
            bool copied = false;

            // Check if m_bufferIn has some capacity left to store the new image.
            if (!m_bufferIn.isEmpty()) {
                // Get next usable memory segment.
                Container c = m_bufferIn.leave();
                coredata::buffer::MemorySegment ms = c.getData<coredata::buffer::MemorySegment>();

                // Copy the data.
                SharedPointer<core::wrapper::SharedMemory> memory = m_sharedPointers[name];
                if ( (memory.isValid()) && (memory->isValid()) ) {
                    char *destPtr = m_mapOfMemories[ms.getIdentifier()];

                    // Lock shared memory segment using a scoped lock.
                    {
                        Lock l(memory);
                        if (memory->getSize() < ms.getSize()) {
                            // Get pointer to shared memory segment.
                            char *src = static_cast<char*>(memory->getSharedMemory());

                            // Copy data from shared memory segment into MemorySegment data structure.
                            ::memcpy(destPtr, src, memory->getSize());

                            // Store meta information.
                            ms.setHeader(header);
                            ms.setConsumedSize(memory->getSize());

                            // Save meta information.
                            c = Container(Container::UNDEFINEDDATA, ms);

                            copied = true;
                        }
                    }
                }

                if (copied) {
                    // Enter memory segment to processing queue.
                    m_bufferOut.enter(c);                
                }
            }

            return copied;
        }

        void SharedDataListener::add(const Container &container) {
            bool hasCopied = false;

            if (container.getDataType() == Container::SHARED_DATA) {
                coredata::SharedData sd = const_cast<Container&>(container).getData<coredata::SharedData>();

                map<string, coredata::SharedData>::iterator it = m_mapOfAvailableSharedData.find(sd.getName());
                if (it == m_mapOfAvailableSharedData.end()) {
            		m_mapOfAvailableSharedData[sd.getName()] = sd;

                    CLOG1 << "Connecting to shared memory " << sd.getName() << " at ";
                    
                    SharedPointer<core::wrapper::SharedMemory> sp = core::wrapper::SharedMemoryFactory::attachToSharedMemory(sd.getName());
                    m_sharedPointers[sd.getName()] = sp;

                    CLOG1 << sp->getSharedMemory() << " ";

                    CLOG1 << "done." << endl;
                }
                hasCopied = copySharedMemoryToMemorySegment(sd.getName(), container);
            }

            if (container.getDataType() == Container::SHARED_IMAGE) {
                coredata::image::SharedImage si = const_cast<Container&>(container).getData<coredata::image::SharedImage>();

                // For old recordings containing SharedImage, the attribute size is calculated
                // "on-the-fly". The following four lines set the size attribute in the generated
                // data structure here.
                uint32_t size = si.getSize();
                size = (size > 0) ? size : (si.getWidth() * si.getHeight() * si.getBytesPerPixel());
                si.setSize(size);
                Container c(Container::SHARED_IMAGE, si);
                // Preserve the timestamps from the current container.
                c.setSentTimeStamp(container.getSentTimeStamp());
                c.setReceivedTimeStamp(container.getReceivedTimeStamp());

                map<string, coredata::image::SharedImage>::iterator it = m_mapOfAvailableSharedImages.find(si.getName());
                if (it == m_mapOfAvailableSharedImages.end()) {
            		m_mapOfAvailableSharedImages[si.getName()] = si;

                    CLOG1 << "Connecting to shared image " << si.getName() << " at ";

                    SharedPointer<core::wrapper::SharedMemory> sp = core::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
                    m_sharedPointers[si.getName()] = sp;

                    CLOG1 << sp->getSharedMemory() << " ";

                    CLOG1 << "done." << endl;
                }
                hasCopied = copySharedMemoryToMemorySegment(si.getName(), c);
            }

            // Update the statistics.
            m_droppedSharedMemories = m_droppedSharedMemories + (!hasCopied ? 1 : 0);

            // If we are not running in threading mode, we need to trigger the disk dump manually.
            if ( (m_sharedDataWriter.get() != NULL) && (!m_threading) ) {
                m_sharedDataWriter->recordEntries();
            }

            CLOG2 << "IN: " << m_bufferIn.getSize() << ", " << "OUT: " << m_bufferOut.getSize() << ", " << "DROPPED: " << m_droppedSharedMemories << endl;
        }

        void SharedDataListener::clear() {}

        uint32_t SharedDataListener::getSize() const {
            return m_bufferIn.getSize();
        }

        bool SharedDataListener::isEmpty() const {
            return (getSize() == 0);
        }

    } // recorder
} // tools

