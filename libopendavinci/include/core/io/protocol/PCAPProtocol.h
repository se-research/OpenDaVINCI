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

#ifndef OPENDAVINCI_CORE_IO_PROTOCOL_PCAPPROTOCOL_H_
#define OPENDAVINCI_CORE_IO_PROTOCOL_PCAPPROTOCOL_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include <sstream>

#include "core/base/Mutex.h"
#include "core/data/Container.h"
#include "core/io/conference/ContainerListener.h"
#include "core/io/conference/ContainerObserver.h"
#include "core/io/protocol/AbstractProtocol.h"

namespace core {
    namespace io {
        namespace protocol {

            using namespace std;

            /**
             * This class implements the PCAP protocol: https://wiki.wireshark.org/Development/LibpcapFileFormat
             */
            class OPENDAVINCI_API PCAPProtocol : public core::io::protocol::AbstractProtocol,
                                                 public core::io::conference::ContainerObserver {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    PCAPProtocol(const PCAPProtocol &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    PCAPProtocol& operator=(const PCAPProtocol &);

                public:
                    /**
                     * Constructor.
                     */
                    PCAPProtocol();

                    virtual ~PCAPProtocol();

                    virtual void setContainerListener(core::io::conference::ContainerListener *cl);

                    virtual void nextString(const string &s);

                private:
                    bool tryConsumingData();

                    /**
                     * This method is used to pass received data thread-safe
                     * to the registered ContainerListener.
                     */
                    void invokeContainerListener(core::data::Container &c);

                    core::base::Mutex m_containerListenerMutex;
                    core::io::conference::ContainerListener *m_containerListener;

                    core::base::Mutex m_partialDataMutex;
                    stringstream m_partialData;
            };

        }
    }
}

#endif /* OPENDAVINCI_CORE_IO_PROTOCOL_PCAPPROTOCOL_H_ */

