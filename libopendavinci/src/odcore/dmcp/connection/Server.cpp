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

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/module/AbstractCIDModule.h"
#include "opendavinci/odcore/dmcp/connection/ConnectionHandler.h"
#include "opendavinci/odcore/dmcp/connection/ModuleConnection.h"
#include "opendavinci/odcore/dmcp/connection/Server.h"
#include "opendavinci/odcore/io/Connection.h"
#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/generated/coredata/dmcp/ServerInformation.h"

namespace odcore { namespace dmcp { class ModuleConfigurationProvider; } }

namespace odcore {
    namespace dmcp {
        namespace connection {

            using namespace std;
            using namespace odcore;
            using namespace odcore::base;
            using namespace odcore::exceptions;
            using namespace coredata::dmcp;

            Server::Server(const ServerInformation &serverInformation, ModuleConfigurationProvider &configProvider) :
                m_configProviderMutex(),
                m_configProvider(configProvider),
                m_connectionHandlerMutex(),
                m_connectionHandler(NULL),
                m_acceptor(serverInformation.getPort()) {
                m_acceptor.setConnectionAcceptorListener(this);
                m_acceptor.start();
            }

            Server::~Server() {
                m_acceptor.stop();
            }

            void Server::setConnectionHandler(ConnectionHandler* connectionHandler) {
                Lock l(m_connectionHandlerMutex);
                m_connectionHandler = connectionHandler;
            }

            void Server::onNewConnection(odcore::SharedPointer<odcore::io::Connection> connection) {
                Lock l(m_configProviderMutex);
                SharedPointer<ModuleConnection> mc;

                try {
                    mc = SharedPointer<ModuleConnection>(new ModuleConnection(connection, m_configProvider));
                }
                catch (...) {
                    CLOG1 << "[core::dmcp::ConnectionServer] cannot create ModuleConnection for new request!" << endl;
                }

                if (m_connectionHandler != NULL) {
                    m_connectionHandler->onNewModule(mc);
                }
                else {
                    CLOG1 << "[core::dmcp::ConnectionServer] received a module connection without set ModuleConnectionHandler" << endl;
                    // As we cannot forward the newly created ModuleConnection mc, it will be deleted by SharedPointer automatically.
                }
            }

        }
    }
} // odcore::dmcp
