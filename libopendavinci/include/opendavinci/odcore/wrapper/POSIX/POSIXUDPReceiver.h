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

#ifndef OPENDAVINCI_CORE_WRAPPER_POSIX_POSIXUDPRECEIVER_H_
#define OPENDAVINCI_CORE_WRAPPER_POSIX_POSIXUDPRECEIVER_H_

#include <netinet/in.h>
#include <sys/socket.h>

#include <map>
#include <memory>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/io/udp/UDPReceiver.h"
#include "opendavinci/odcore/wrapper/NetworkLibraryProducts.h"
#include "opendavinci/odcore/wrapper/Runnable.h"

namespace odcore { namespace wrapper { class Thread; } }
namespace odcore { namespace wrapper { template <odcore::wrapper::NetworkLibraryProducts product> class UDPFactoryWorker; } }

namespace odcore {
    namespace wrapper {
        namespace POSIX {

            using namespace std;

            /**
             * This class implements a UDP receiver for receiving data using POSIX.
             *
             * @See UDPReceiver
             */
            class POSIXUDPReceiver : public Runnable, public odcore::io::udp::UDPReceiver {
                private:
                    friend class UDPFactoryWorker<NetworkLibraryPosix>;

                    /**
                        * Constructor.
                        *
                        * @param address Address to bind on.
                        * @param port Port.
                        * @param isMulticast true, if this receiver is part of the UDP multicast group specified by address:port.
                        */
                    POSIXUDPReceiver(const string &address, const uint32_t &port, const bool &isMulticast);

                private:
                    enum {
                        BUFFER_SIZE = 65535
                    };

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    POSIXUDPReceiver(const POSIXUDPReceiver &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    POSIXUDPReceiver& operator=(const POSIXUDPReceiver &);

                public:
                    virtual ~POSIXUDPReceiver();

                    virtual void start();

                    virtual void stop();

                    virtual void setSenderPortToIgnore(const uint16_t &portToIgnore);

                private:
                    map<unsigned long, bool> m_mapOfIPAddresses;
                    uint16_t m_portToIgnore;
                    bool m_isMulticast;
                    struct sockaddr_in m_address;
                    struct ip_mreq m_mreq;
                    int32_t m_fd;
                    char *m_buffer;
                    unique_ptr<Thread> m_thread;

                    virtual void run();

                    virtual bool isRunning();

                    void getIPAddresses();
            };

        }
    }
} // odcore::wrapper::POSIX

#endif /*OPENDAVINCI_CORE_WRAPPER_POSIX_POSIXUDPRECEIVER_H_*/
