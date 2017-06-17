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
#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/base/module/AbstractCIDModule.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/dmcp/discoverer/Client.h"
#include "opendavinci/odcore/io/udp/UDPFactory.h"
#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/generated/odcore/data/dmcp/Constants.h"
#include "opendavinci/generated/odcore/data/dmcp/DiscoverMessage.h"

namespace odcore {
    namespace dmcp {
        namespace discoverer {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odcore::exceptions;

            using namespace odcore::data::dmcp;

            Client::Client(const string &group,
                           const uint32_t &serverPort,
                           const uint32_t &clientPort,
                           const string &name) :
                m_sender(odcore::io::udp::UDPFactory::createUDPSender(group, serverPort)),
                m_receiver(odcore::io::udp::UDPFactory::createUDPReceiver(group, clientPort)),
                m_responseCondition(),
                m_response(false),
                m_serverInformation(),
                m_moduleName(name) {
                m_receiver->setPacketListener(this);
                m_receiver->start();
            }

            Client::~Client() {
                m_receiver->setPacketListener(NULL);
                m_receiver->stop();
            }

            bool Client::existsServer() {
                m_response = false;
                sendDiscoverMessage();
                waitForResponse();

                return m_response;
            }

            ServerInformation Client::getServerInformation() const {
                return m_serverInformation;
            }

            void Client::onResponse() {}

            void Client::sendDiscoverMessage() {
                stringstream sstr;

                DiscoverMessage d(DiscoverMessage::DISCOVER, m_serverInformation, m_moduleName);
                Container discover = Container(d);
                sstr << discover;

                m_sender->send(sstr.str());
            }

            void Client::nextPacket(const odcore::data::Packet &p) {
                Container container;
                stringstream sstr(p.getData());
                sstr >> container;

                if (container.getDataType() == DiscoverMessage::ID()) {
                    DiscoverMessage msg = container.getData<DiscoverMessage>();
                    if (msg.getType() == DiscoverMessage::RESPONSE) {
                        Lock l(m_responseCondition);

                        if (!m_response) {
                            ServerInformation tmp = msg.getServerInformation();
                            // Use the IP address from the received UDP packet.
                            m_serverInformation = ServerInformation(p.getSender(), tmp.getPort(), tmp.getManagedLevel());
                            m_response = true;
                            onResponse();
                            m_responseCondition.wakeAll();
                        }
                    }
                }
                else {
                    CLOG1 << "[odcore::dmcp::DiscovererServer] received unknown message: " << container.toString() << endl;
                }
            }

            void Client::waitForResponse() {
                Lock  l(m_responseCondition);
                if (!m_response) {
                    m_responseCondition.waitOnSignalWithTimeout(odcore::data::dmcp::Constants::DISCOVER_TIMEOUT);
                }
            }
        }
    }
}
