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

#include <stddef.h>
#include <ostream>

#include "core/SharedPointer.h"
#include "core/base/Lock.h"
#include "core/base/module/AbstractCIDModule.h"
#include "core/dmcp/connection/ConnectionHandler.h"
#include "core/dmcp/connection/ModuleConnection.h"
#include "core/dmcp/connection/Server.h"
#include "core/io/Connection.h"
#include "core/macros.h"
#include "generated/coredata/dmcp/ServerInformation.h"

namespace core { namespace dmcp { class ModuleConfigurationProvider; } }

namespace core {
    namespace dmcp {
        namespace connection {

            using namespace std;
            using namespace core;
            using namespace core::base;
            using namespace core::exceptions;
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

            void Server::onNewConnection(core::SharedPointer<core::io::Connection> connection) {
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
} // core::dmcp
