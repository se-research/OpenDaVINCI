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

#ifndef OPENDAVINCI_DMCP_DISCOVER_CLIENT_H_
#define OPENDAVINCI_DMCP_DISCOVER_CLIENT_H_

#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Condition.h"
#include "opendavinci/odcore/io/PacketListener.h"
#include "opendavinci/odcore/io/udp/UDPReceiver.h"
#include "opendavinci/odcore/io/udp/UDPSender.h"
#include "opendavinci/generated/odcore/data/dmcp/ServerInformation.h"

namespace odcore { namespace io { class Packet; } }

namespace odcore {
    namespace dmcp {
        namespace discoverer {

            using namespace std;

            class OPENDAVINCI_API Client : protected odcore::io::PacketListener {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    Client(const Client &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    Client& operator=(const Client &);

                public:
                    Client(const std::string& group,
                           const uint32_t &serverPort,
                           const uint32_t &clientPort,
                           const string &name);
                    virtual ~Client();

                    bool existsServer();

                    odcore::data::dmcp::ServerInformation getServerInformation() const;

                    virtual void onResponse();

                protected:
                    void sendDiscoverMessage();
                    void waitForResponse();
                    virtual void nextPacket(const odcore::io::Packet &p);

                    odcore::SharedPointer<odcore::io::udp::UDPSender> m_sender;
                    odcore::SharedPointer<odcore::io::udp::UDPReceiver> m_receiver;

                    odcore::base::Condition m_responseCondition;
                    bool m_response;

                    odcore::data::dmcp::ServerInformation m_serverInformation;
                    string m_moduleName;
            };
        }
    }
}
#endif //OPENDAVINCI_DMCP_DISCOVER_CLIENT_H_
