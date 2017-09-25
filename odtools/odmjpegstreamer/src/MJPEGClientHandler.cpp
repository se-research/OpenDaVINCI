/**
 * odmjpegstreamer - Tool to stream a given SharedImage as HTTP encapsulated MJPEG stream
 * Copyright (C) 2017 Christian Berger
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

#include <iostream>

#include <opendavinci/odcore/base/Lock.h>

#include "MJPEGClientHandler.h"

namespace odmjpegstreamer {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::io::tcp;

    MJPEGClientHandler::MJPEGClientHandler(shared_ptr<odcore::io::tcp::TCPConnection> connection) :
        m_connectionClosedMutex(),
        m_connectionClosed(false),
        m_connection(connection) {}

    MJPEGClientHandler::~MJPEGClientHandler() {}

    void MJPEGClientHandler::nextString(const std::string &/*data*/) {
        stringstream sstr;
        sstr << "HTTP/1.1 200 OK\r\n"
             << "Server: odmjpegstreamer\r\n"
             << "Connection: close\r\n"
             << "Max-Age: 0\r\n"
             << "Expires: 0\r\n"
             << "Cache-Control: no-cache, private\r\n"
             << "Pragma: no-cache\r\n"
             << "Content-Type: multipart/x-mixed-replace; boundary=--odmjpegstream \r\n";

        {
            Lock l(m_connectionClosedMutex);
            if (!m_connectionClosed) {
                const string s = sstr.str();
                m_connection->send(s);
            }
        }
    }

    void MJPEGClientHandler::sendImage(char *buffer, const uint32_t &length) {
        Lock l(m_connectionClosedMutex);
        if (!m_connectionClosed) {
            stringstream sstr;
            sstr << "\r\n--odmjpegstream\r\n"
                 << "Content-Type: image/jpeg\r\n"
                 << "Content-Length: " << length << "\r\n\r\n";
            sstr.write(buffer, length);

            const string s = sstr.str();
            m_connection->send(s);
        }
    }

    void MJPEGClientHandler::handleConnectionError() {
        Lock l(m_connectionClosedMutex);
        m_connectionClosed = true;
    }

} // odmjpegstreamer

