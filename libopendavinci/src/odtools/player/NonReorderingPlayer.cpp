/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/base/module/AbstractCIDModule.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/image/CompressedImage.h"
#include "opendavinci/odcore/io/StreamFactory.h"
#include "opendavinci/odcore/io/URL.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"
#include "opendavinci/odcore/wrapper/jpg/JPG.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

#include "opendavinci/odtools/player/NonReorderingPlayer.h"
#include "opendavinci/odtools/player/PlayerCache.h"
#include "opendavinci/odtools/player/PlayerDelegate.h"

namespace odtools {
    namespace player {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::io;

        NonReorderingPlayer::NonReorderingPlayer(const URL &url, const bool &autoRewind, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments, const bool &threading) :
            m_threading(threading),
            m_autoRewind(autoRewind),
            m_inFile(NULL),
            m_inSharedMemoryFile(NULL),
            m_playerCache(),
            m_actual(),
            m_successor(),
            m_successorProcessed(true),
            m_seekToTheBeginning(true),
            m_noMoreData(false),
            m_delay(0),
            m_mapOfSharedMemoriesForCompressedImages(),
            m_mapOfPlayerDelegatesMutex(),
            m_mapOfPlayerDelegates() {

            // Get the stream using the StreamFactory with the given URL.
            m_inFile = StreamFactory::getInstance().getInputStream(url);

            // Try to load the data storage for data from the shared memory.
            if (url.getResource().compare("/dev/stdin") != 0) {
                URL urlSharedMemoryFile("file://" + url.getResource() + ".mem");
                try {
                    m_inSharedMemoryFile = StreamFactory::getInstance().getInputStream(urlSharedMemoryFile);
                    CLOG1 << "NonReorderingPlayer: Found shared memory dump file '" << urlSharedMemoryFile.toString() << "'" << endl;
                }
                catch (const odcore::exceptions::InvalidArgumentException &iae) {
                    clog << "NonReorderingPlayer: Warning: " << iae.toString() << endl;
                } 
            }

            // Setup cache.
            m_playerCache = unique_ptr<PlayerCache>(new PlayerCache(numberOfMemorySegments, memorySegmentSize, m_autoRewind, m_inFile, m_inSharedMemoryFile));
            if (m_playerCache.get() != NULL) {
                // First, fill the cache...
                m_playerCache->updateCache();

                if (m_threading) {
                    // ...and if running concurrently, start the thread.
                    m_playerCache->start();
                }
            }
        }

        NonReorderingPlayer::~NonReorderingPlayer() {
            if ( (m_playerCache.get() != NULL) && (m_threading) ) {
                m_playerCache->stop();
            }

            // Next, clean up any PlayerDelegates that might have deferred playback.
            {
                Lock l(m_mapOfPlayerDelegatesMutex);
                m_mapOfPlayerDelegates.clear();
            }


            // Clear shared memories created for compressed images.
            m_mapOfSharedMemoriesForCompressedImages.clear();
        }

        void NonReorderingPlayer::registerPlayerDelegate(const uint32_t &containerID, PlayerDelegate *p) {
            Lock l(m_mapOfPlayerDelegatesMutex);

            // First, check if we have registered an existing PlayerDelegate for the given ID.
            auto delegate = m_mapOfPlayerDelegates.find(containerID);
            if (delegate != m_mapOfPlayerDelegates.end()) {
                m_mapOfPlayerDelegates.erase(delegate);
            }

            if (p != NULL) {
                m_mapOfPlayerDelegates[containerID] = p;
            }
        }

        Container NonReorderingPlayer::getNextContainerToBeSent() {
            Container retVal;

            // Update cache in the sychronous case.
            if ( (m_playerCache.get() != NULL) && (!m_threading) ) {
                m_playerCache->updateCache();
            }

            // Check, if we are "at the beginning".
            if (m_seekToTheBeginning) {
                // Read the "actual" (first) container.
                if (m_playerCache->getNumberOfEntries() > 0) {
                    m_actual = m_playerCache->getNextContainer();
                }

                // Disable this state.
                m_seekToTheBeginning = false;

                // Don't skip reading successor.
                m_successorProcessed = true;
            }

            // While there are more containers, read the "successor" of the "actual" container.
            if (m_successorProcessed) {
                if (m_playerCache->getNumberOfEntries() > 0) {
                    m_successor = m_playerCache->getNextContainer();

                    if (m_successor.getDataType() != Container::UNDEFINEDDATA) {
                        // Indicate that the successor needs to be processed.
                        m_successorProcessed = false;
                    }
                    else {
                        // If the container contains undefined data and autorewind is chosen, seek to the beginning.
                        if (m_autoRewind) {
                            // Change internal state to "at the beginning".
                            m_seekToTheBeginning = true;
                        }
                    }
                }
                else {
                    m_noMoreData = true;
                }
            }

            // Here, the time gap between two containers is calculated.
            if ( (m_actual.getDataType() != Container::UNDEFINEDDATA) &&
                 (m_successor.getDataType() != Container::UNDEFINEDDATA) ) {
                TimeStamp delta = m_successor.getSampleTimeStamp() - m_actual.getSampleTimeStamp();
                if (!(delta.toMicroseconds() < 0)) {
                    m_delay = static_cast<long>(delta.toMicroseconds());
                }
            }

            // First, check if we need to delegate storing this container.
            bool wasContainerDelegated = false;
            {
                Lock l(m_mapOfPlayerDelegatesMutex);
                auto delegate = m_mapOfPlayerDelegates.find(m_actual.getDataType());
                if (delegate != m_mapOfPlayerDelegates.end()) {
                    Container replacementContainer = delegate->second->process(m_actual);

                    wasContainerDelegated = true;

                    // Replace m_actual with the replacement Container.
                    m_actual = replacementContainer;
                }
            }


            if (!wasContainerDelegated) {
                // If the actual container is a SharedImage then copy next entry into the shared memory before sending the actual container.
                if (m_actual.getDataType() == odcore::data::image::SharedImage::ID()) {
                    m_playerCache->copyMemoryToSharedMemory(m_actual);
                }

                // If the actual container is a SharedData then copy next entry into the shared memory before sending the actual container.
                if (m_actual.getDataType() == odcore::data::SharedData::ID()) {
                    m_playerCache->copyMemoryToSharedMemory(m_actual);
                }

                // If the actual container is a SharedPointCloud then copy next entry into the shared memory before sending the actual container.
                if (m_actual.getDataType() == odcore::data::SharedPointCloud::ID()) {
                    m_playerCache->copyMemoryToSharedMemory(m_actual);
                }
            }

            // Return the m_actual container as retVal in the case of a
            // non-compressed image container as compressed images will
            // be replaced by shared images below.
            retVal = m_actual;

            // If the actual container is a COMPRESSED_IMAGE then decode it and replace the container with a shared image before sending the actual container.
            if (m_actual.getDataType() == odcore::data::image::CompressedImage::ID()) {
                odcore::data::image::CompressedImage ci = m_actual.getData<odcore::data::image::CompressedImage>();

                // Check, whether a shared memory was already created for this compressed image; otherwise, create it and save it for later.
                map<string, std::shared_ptr<odcore::wrapper::SharedMemory> >::iterator it = m_mapOfSharedMemoriesForCompressedImages.find(ci.getName());
                if (it == m_mapOfSharedMemoriesForCompressedImages.end()) {
                    std::shared_ptr<odcore::wrapper::SharedMemory> sp = odcore::wrapper::SharedMemoryFactory::createSharedMemory(ci.getName(), ci.getSize());
                    m_mapOfSharedMemoriesForCompressedImages[ci.getName()] = sp;
                }

                // Get the shared memory to put the uncompressed image into.
                std::shared_ptr<odcore::wrapper::SharedMemory> sp = m_mapOfSharedMemoriesForCompressedImages[ci.getName()];

                int width = 0;
                int height = 0;
                int bpp = 0;

                // Decompress image data.
                unsigned char *imageData = odcore::wrapper::jpg::JPG::decompress(ci.getRawData(), ci.getCompressedSize(), &width, &height, &bpp, ci.getBytesPerPixel());

                if ( (imageData != NULL) &&
                     (width > 0) &&
                     (height > 0) &&
                     (bpp > 0) ) {
                    // Lock shared memory to store the uncompressed data.
                    if (sp->isValid()) {
                        Lock l(sp);
                        ::memcpy(sp->getSharedMemory(), imageData, width * height * bpp);
                    }

                    // As we have now the decompressed image data in memory, create a SharedMemory data structure to describe it.
                    odcore::data::image::SharedImage si;
                    si.setName(ci.getName());
                    si.setWidth(ci.getWidth());
                    si.setHeight(ci.getHeight());
                    si.setBytesPerPixel(ci.getBytesPerPixel());
                    si.setSize(ci.getWidth() * ci.getHeight() * ci.getBytesPerPixel());

                    // Distribute the SharedImage information in the UDP multicast session.
                    retVal = Container(si);
                    retVal.setSentTimeStamp(m_actual.getSentTimeStamp());
                    retVal.setReceivedTimeStamp(m_actual.getReceivedTimeStamp());
                    retVal.setSampleTimeStamp(m_actual.getSampleTimeStamp());
                }

                OPENDAVINCI_CORE_FREE_POINTER(imageData);
            }

            // Process the "successor" container as the next "actual" one.
            m_actual = m_successor;

            // The actual container has been sent, therefore, the successor becomes the next actual container.
            m_successorProcessed = true;

            return retVal;
        }

        uint32_t NonReorderingPlayer::getDelay() const {
            return m_delay;
        }

        void NonReorderingPlayer::rewind() {
            // Clear cache and wait for new data.
            m_playerCache->clearQueueRewindInputStreams();

            // Reset our own states.
            m_seekToTheBeginning = true;
            m_noMoreData = false;
        }

        bool NonReorderingPlayer::hasMoreData() const {
            return !m_noMoreData;
        }

    } // player
} // tools
