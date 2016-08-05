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

#include <algorithm>
#include <iostream>

#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/base/module/AbstractCIDModule.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/dmcp/discoverer/Server.h"
#include "opendavinci/odcore/io/udp/UDPFactory.h"
#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/generated/odcore/data/dmcp/DiscoverMessage.h"

namespace odcore {
    namespace dmcp {
        namespace discoverer {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odcore::data::dmcp;

            Server::Server(const ServerInformation &serverInformation,
                           const std::string &group,
                           const uint32_t &serverPort,
                           const uint32_t &clientPort,
                           const vector<string> &modulesToIgnore) :
                m_sender(odcore::io::udp::UDPFactory::createUDPSender(group, clientPort)),
                m_receiver(odcore::io::udp::UDPFactory::createUDPReceiver(group, serverPort)),
                m_serverInformation(serverInformation),
                m_modulesToIgnore(modulesToIgnore) {
                m_receiver->start();
            }

            Server::~Server() {
                m_receiver->setStringListener(NULL);
                m_receiver->stop();
            }

            void Server::nextString(const string &s) {
                Container container;
                stringstream ss(s);
                ss >> container;

                if (container.getDataType() == DiscoverMessage::ID()) {
                    DiscoverMessage msg = container.getData<DiscoverMessage>();
                    if (msg.getType() == DiscoverMessage::DISCOVER) {
                        onRequest();
                        sendResponseMessage(msg.getModuleName());
                    }
                }
                else {
                    CLOG1 << "[core::dmcp::DiscovererServer] received unkown message: " << container.toString() << endl;
                }
            }

            void Server::sendResponseMessage(const string &s) {
                const string MODULE_NAME = "core::dmcp::DiscovererServer";
                Container c;

                // Check whether the connected module will receive the ordinary response from supercomponent
                // or if we need to send the default response to bypass any managed_level configuration (e.g.
                // for cockpit for example).
                string s2(s);
                transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

                vector<string>::iterator it = find(m_modulesToIgnore.begin(), m_modulesToIgnore.end(), s2);
                if (it == m_modulesToIgnore.end()) {
                    CLOG1 << "[core::dmcp::DiscovererServer] responding to DMCP_DISCOVER" << endl;
                    DiscoverMessage msg(DiscoverMessage::RESPONSE, m_serverInformation, MODULE_NAME);
                    c = Container(msg);
                }
                else {
                    CLOG1 << "[core::dmcp::DiscovererServer] responding to DMCP_DISCOVER for module '" << s << "' excluded from managed level " << m_serverInformation.getManagedLevel() << endl;
                    ServerInformation si(m_serverInformation.getIP(), m_serverInformation.getPort(), ServerInformation::ML_NONE);
                    DiscoverMessage msg(DiscoverMessage::RESPONSE, si, MODULE_NAME);
                    c = Container(msg);
                }

                stringstream ss;
                ss << c;
                m_sender->send(ss.str());
            }

            void Server::startResponding() {
                m_receiver->setStringListener(this);
            }

            void Server::stopResponding() {
                m_receiver->setStringListener(NULL);
            }

            void Server::onRequest() {}

        }
    }
}
