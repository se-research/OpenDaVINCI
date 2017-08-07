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

#include <opendavinci/odcore/base/Mutex.h>
#include <opendavinci/odcore/io/ConnectionListener.h>
#include <opendavinci/odcore/io/StringListener.h>
#include <opendavinci/odcore/io/tcp/TCPAcceptorListener.h>
#include <opendavinci/odcore/io/tcp/TCPConnection.h>

namespace odmjpegstreamer {

    using namespace std;

    /**
     * This class will handle newly accepted TCP connections.
     */
    class MJPEGClientHandler : public odcore::io::ConnectionListener,
                               public odcore::io::StringListener {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            MJPEGClientHandler(const MJPEGClientHandler &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            MJPEGClientHandler& operator=(const MJPEGClientHandler &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param connection TCP connection for this handler.
             */
            MJPEGClientHandler(shared_ptr<odcore::io::tcp::TCPConnection> connection);

            virtual ~MJPEGClientHandler();

        public:
            virtual void nextString(const std::string &s);
            virtual void handleConnectionError();

            void sendImage(char *buffer, const uint32_t &length);

        private:
            odcore::base::Mutex m_connectionClosedMutex;
            bool m_connectionClosed;
            shared_ptr<odcore::io::tcp::TCPConnection> m_connection;
    };

} // odmjpegstreamer

