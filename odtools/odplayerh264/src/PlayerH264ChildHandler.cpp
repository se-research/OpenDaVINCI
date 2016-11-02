/**
 * odplayerh264 - Tool for replaying video streams encoded with h264.
 * Copyright (C) 2016 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <unistd.h>

#include <iostream>

#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/base/Thread.h>

#include <opendavinci/odcore/io/tcp/TCPFactory.h>
#include <opendavinci/odcore/io/tcp/TCPConnection.h>

#include "PlayerH264ChildHandler.h"

namespace odplayerh264 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odcore::io::tcp;

    PlayerH264ChildHandler::PlayerH264ChildHandler() :
        m_PID(0),
        m_tcpacceptor(),
        m_connection(),
        m_condition(),
        m_hasResponseMutex(),
        m_hasResponse(false),
        m_response() {}

    PlayerH264ChildHandler::PlayerH264ChildHandler(const uint32_t &port) :
        m_PID(0),
        m_tcpacceptor(),
        m_connection(),
        m_condition(),
        m_hasResponseMutex(),
        m_hasResponse(false),
        m_response() {

        try {
            m_tcpacceptor = odcore::io::tcp::TCPFactory::createTCPAcceptor(port);
            m_tcpacceptor->setAcceptorListener(this);
            // Start accepting new connections to receive data.
            m_tcpacceptor->start();
        }
        catch(string &exception) {
            cerr << "Error while creating TCP receiver: " << exception << endl;
        }
    }

    PlayerH264ChildHandler::~PlayerH264ChildHandler() {
        try {
            // Stop accepting new connections and unregister our handler.
            m_tcpacceptor->stop();
            m_tcpacceptor->setAcceptorListener(NULL);
        }
        catch(string &exception) {
            cerr << "[odplayerh264] Error while creating TCP receiver: " << exception << endl;
        }
    }

    void PlayerH264ChildHandler::closeConnection() {
        m_connection.reset();
    }

    void PlayerH264ChildHandler::setConnection(shared_ptr<odcore::io::tcp::TCPConnection> c) {
        m_connection = c;
    }

    shared_ptr<odcore::io::tcp::TCPConnection> PlayerH264ChildHandler::getConnection() const {
        return m_connection;
    }

    void PlayerH264ChildHandler::setPID(pid_t pid) {
        m_PID = pid;
    }

    pid_t PlayerH264ChildHandler::getPID() const {
        return m_PID;
    }

    void PlayerH264ChildHandler::waitForClientToConnect() {
        // Wait for the connecting client.
        cout << "[odplayerh264] Waiting for client to connect...";
        Lock l(m_condition);
        m_condition.waitOnSignal();
        cout << " Client connected." << endl;
    }

    void PlayerH264ChildHandler::handleConnectionError() {
        // Stop this connection.
        m_connection->stop();

        // Unregister the listeners.
        m_connection->setStringListener(NULL);
        m_connection->setConnectionListener(NULL);
    }

    void PlayerH264ChildHandler::nextString(const std::string &s) {
        Lock l(m_hasResponseMutex);
        stringstream sstr(s);
        sstr >> m_response;
        m_hasResponse = true;
    }

    void PlayerH264ChildHandler::onNewConnection(shared_ptr<TCPConnection> connection) {
        if (connection.get()) {
            m_connection = connection;
            m_connection->setStringListener(this);
            m_connection->setConnectionListener(this);

            // Start receiving data from this connection.
            m_connection->start();

            // Indicate that we have a valid connection.
            Lock l(m_condition);
            m_condition.wakeAll();
        }
    }

    Container PlayerH264ChildHandler::process(Container &c) {
        {
            Lock l(m_hasResponseMutex);
            m_hasResponse = false;
        }

        // First, send the container to the child process.
        stringstream sstr;
        sstr << c;
        m_connection->send(sstr.str());

        // Wait for the child's response.
        bool hasResponse = false;
        while (!hasResponse) {
            Lock l(m_hasResponseMutex);
            hasResponse = m_hasResponse;

            // Avoid busy waiting.
            Thread::usleepFor(10);
        }

        // The child's response is in m_response.
        return m_response;
    }

} // odplayerh264
