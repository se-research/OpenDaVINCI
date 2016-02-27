/**
 * OpenDaVINCI - Tutorial.
 * Copyright (C) 2015 Christian Berger
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

#include <stdint.h>
#include <iostream>
#include <string>
#include <memory>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/odcore/io/tcp/TCPAcceptor.h>
#include <opendavinci/odcore/io/tcp/TCPFactory.h>

#include "TCPReceiveBytes.hpp"

using namespace std;

// We add some of OpenDaVINCI's namespaces for the sake of readability.
using namespace odcore;
using namespace odcore::io;
using namespace odcore::io::tcp;

void TCPReceiveBytes::handleConnectionError() {
    cout << "Connection terminated." << endl;
}

void TCPReceiveBytes::nextString(const std::string &s) {
    cout << "Received " << s.length() << " bytes containing '" << s << "'" << endl;
}

void TCPReceiveBytes::onNewConnection(std::shared_ptr<odcore::io::tcp::TCPConnection> connection) {
    if (connection.get()) {
        cout << "Handle a new connection." << endl;

        // Set this class as StringListener to receive
        // data from this connection.
        connection->setStringListener(this);

        // Set this class also as ConnectionListener to
        // handle errors originating from this connection.
        connection->setConnectionListener(this);

        // Start receiving data from this connection.
        connection->start();

        // We keep this connection open only for one
        // second before we close it.
        const uint32_t ONE_SECOND = 1000 * 1000;
        odcore::base::Thread::usleepFor(ONE_SECOND);

        // Stop this connection.
        connection->stop();

        // Unregister the listeners.
        connection->setStringListener(NULL);
        connection->setConnectionListener(NULL);
    }
}

int32_t main(int32_t argc, char **argv) {
    const uint32_t PORT = 1234;

    // We are using OpenDaVINCI's std::shared_ptr to automatically
    // release any acquired resources.
    try {
        std::shared_ptr<TCPAcceptor>
            tcpacceptor(TCPFactory::createTCPAcceptor(PORT));

        // This instance will handle any new connections.
        TCPReceiveBytes handler;
        tcpacceptor->setAcceptorListener(&handler);

        // Start accepting new connections.
        tcpacceptor->start();

        const uint32_t ONE_SECOND = 1000 * 1000;
        odcore::base::Thread::usleepFor(10 * ONE_SECOND);

        // Stop accepting new connections and unregister our handler.
        tcpacceptor->stop();
        tcpacceptor->setAcceptorListener(NULL);
    }
    catch(string &exception) {
        cerr << "Error while creating TCP receiver: " << exception << endl;
    }
}

