/**
 * OpenDaVINCI - Portable middleware for distributed components.
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

#ifndef OPENDAVINCI_CORE_IO_PACKETPIPELINE_H_
#define OPENDAVINCI_CORE_IO_PACKETPIPELINE_H_

#include <queue>

#include "opendavinci/odcore/base/Condition.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/base/Service.h"
#include "opendavinci/odcore/io/PacketListener.h"
#include "opendavinci/odcore/io/PacketObserver.h"
#include "opendavinci/generated/odcore/data/Packet.h"

namespace odcore {
    namespace io {

        using namespace std;

        /**
         * This class distributes odcore::data::Packets using an asynchronous pipeline
         * to decouple the processing of the data when invoking a PacketListener at higher levels.
         */
        class PacketPipeline : public odcore::base::Service, public PacketObserver, public PacketListener {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                PacketPipeline(const PacketPipeline &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                PacketPipeline& operator=(const PacketPipeline &);

            public:
                PacketPipeline();

                virtual ~PacketPipeline();

                virtual void setPacketListener(PacketListener *pl);

                virtual void nextPacket(const odcore::data::Packet &p);

            private:
                virtual void beforeStop();

                virtual void run();

                /**
                 * This method is processing the entries in the queue.
                 */
                void processQueue();

            private:
                odcore::base::Condition m_queueCondition;
                odcore::base::Mutex m_queueMutex;
                queue<odcore::data::Packet> m_queue;

                odcore::base::Mutex m_packetListenerMutex;
                PacketListener *m_packetListener;
        };

    }
} // odcore::io

#endif /*OPENDAVINCI_CORE_IO_PACKETPIPELINE_H_*/
