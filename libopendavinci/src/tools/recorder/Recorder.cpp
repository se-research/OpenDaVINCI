/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#include "opendavinci/core/base/Serializable.h"
#include "opendavinci/core/base/module/AbstractCIDModule.h"
#include "opendavinci/core/data/Container.h"
#include "opendavinci/core/io/StreamFactory.h"
#include "opendavinci/core/io/URL.h"
#include "opendavinci/core/opendavinci.h"
#include "opendavinci/tools/recorder/Recorder.h"
#include "opendavinci/tools/recorder/SharedDataListener.h"

namespace tools {

    namespace recorder {

        using namespace std;
        using namespace core::base;
        using namespace core::data;
        using namespace core::io;

        Recorder::Recorder(const string &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfSegments, const bool &threading, const bool &dumpSharedData) :
            m_fifo(),
            m_sharedDataListener(NULL),
            m_out(NULL),
            m_outSharedMemoryFile(NULL),
            m_dumpSharedData(dumpSharedData) {

            // Get output file.
            URL _url(url);
            m_out = StreamFactory::getInstance().getOutputStream(_url);

            // Add a specific listener for SharedData type.
            URL urlSharedMemoryFile("file://" + _url.getResource() + ".mem");
            m_outSharedMemoryFile = StreamFactory::getInstance().getOutputStream(urlSharedMemoryFile);

            // Create data store for shared memory.
            m_sharedDataListener = auto_ptr<SharedDataListener>(new SharedDataListener(m_outSharedMemoryFile, memorySegmentSize, numberOfSegments, threading));
        }

        Recorder::~Recorder() {
            // Record remaining entries.
            CLOG1 << "Clearing queue... ";
                recordQueueEntries();
                if (m_out.isValid()) {
                    m_out->flush();
                }
            CLOG1 << "done." << endl;
        }

        FIFOQueue& Recorder::getFIFO() {
            return m_fifo;
        }

        SharedDataListener& Recorder::getDataStoreForSharedData() {
            return *m_sharedDataListener;
        }

        void Recorder::store(core::data::Container c) {
            // Check if the container to be stored is a "regular" data type.
            if ( (c.getDataType() != Container::UNDEFINEDDATA) &&
                 (c.getDataType() != coredata::recorder::RecorderCommand::ID())  &&
                 (c.getDataType() != coredata::SharedData::ID())  &&
                 (c.getDataType() != coredata::image::SharedImage::ID()) ) {
                getFIFO().enter(c);
                recordQueueEntries();
            }

            if (m_dumpSharedData) {
                // ... or a container that describes a shared memory segment.
                if ( (c.getDataType() == coredata::SharedData::ID())  ||
                     (c.getDataType() == coredata::image::SharedImage::ID()) ) {
                    getDataStoreForSharedData().add(c);
                }
            }
        }

        void Recorder::recordQueueEntries() {
            if (!m_fifo.isEmpty()) {
                uint32_t numberOfEntries = m_fifo.getSize();
                for (uint32_t i = 0; i < numberOfEntries; i++) {
                    Container c = m_fifo.leave();
                    // Filter undefined data as well as recorder commands.
                    if ( (c.getDataType() != Container::UNDEFINEDDATA) &&
                         (c.getDataType() != coredata::recorder::RecorderCommand::ID())  &&
                         (c.getDataType() != coredata::SharedData::ID())  &&
                         (c.getDataType() != coredata::image::SharedImage::ID()) ) {
                        if (m_out.isValid()) {
                            (*m_out) << c;
                        }
                    }
                }

                if (m_out.isValid()) {
                    m_out->flush();
                }
            }
        }

    } // recorder
} // tools
