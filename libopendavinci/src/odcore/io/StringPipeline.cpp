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

#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/io/StringPipeline.h"

namespace odcore {
    namespace io {

        using namespace std;
        using namespace odcore::base;

        StringPipeline::StringPipeline() :
            Service(),
            StringObserver(),
            StringListener(),
            m_queueCondition(),
            m_queueMutex(),
            m_queue(),
            m_stringListenerMutex(),
            m_stringListener(NULL) {}

        StringPipeline::~StringPipeline() {
            // Stop the queue.
            stop();
        }

        void StringPipeline::setStringListener(StringListener *sl) {
            Lock l(m_stringListenerMutex);

            // Prevent listening by ourselves!
            if (sl != this) {
                m_stringListener = sl;
            }
        }

        void StringPipeline::nextString(const string &s) {
// Read all entries and distribute using the stringListener.
{
    Lock l(m_stringListenerMutex);
    if (m_stringListener != NULL) {
std::cout << __FILE__ << " " << __LINE__ << std::endl;
        // Distribute entry to connected listeners while NOT locking the queue.
        m_stringListener->nextString(s);
std::cout << __FILE__ << " " << __LINE__ << std::endl;
    }
}

//std::cout << __FILE__ << " " << __LINE__ << std::endl;
//            Lock l(m_queueCondition);
//std::cout << __FILE__ << " " << __LINE__ << std::endl;

//            // Enter new data.
//            {
//                Lock l2(m_queueMutex);
//                m_queue.push(s);
//            }

//            // Wake awaiting threads.
//            m_queueCondition.wakeAll();
//std::cout << __FILE__ << " " << __LINE__ << std::endl;
        }

        void StringPipeline::processQueue() {
std::cout << __FILE__ << " " << __LINE__ << std::endl;
            uint32_t numberOfEntries = 0;

            // Determine the amount of current entries.
            {
                Lock l(m_queueMutex);
                numberOfEntries = static_cast<uint32_t>(m_queue.size());
            }

std::cout << __FILE__ << " " << __LINE__ << ", clearing = " << numberOfEntries << std::endl;
            string entry;
            for (uint32_t i = 0; i < numberOfEntries; i++) {
                // Acquire and remove next entry.
                {
                    Lock l2(m_queueMutex);
                    entry = m_queue.front();
                    m_queue.pop();
                }

                // Read all entries and distribute using the stringListener.
                {
                    Lock l(m_stringListenerMutex);
                    if (m_stringListener != NULL) {
std::cout << __FILE__ << " " << __LINE__ << std::endl;
                        // Distribute entry to connected listeners while NOT locking the queue.
                        m_stringListener->nextString(entry);
std::cout << __FILE__ << " " << __LINE__ << std::endl;
                    }
                }
            }
std::cout << __FILE__ << " " << __LINE__ << std::endl;
        }

        void StringPipeline::beforeStop() {
            // Wake awaiting threads.
            Lock l(m_queueCondition);
            m_queueCondition.wakeAll();
        }

        void StringPipeline::run() {
            serviceReady();

            while (isRunning()) {
                Lock l(m_queueCondition);
                m_queueCondition.waitOnSignal();

                if (isRunning()) {
//                    processQueue();
                }
            }

            // Procee the queue to release any further waiting entries before shutting down.
//            processQueue();
        }

    }
} // odcore::io
