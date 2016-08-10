/**
 * odrecorderh264 - Tool for recording data and encoding video streams with h264.
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

#ifndef RECORDERH264CHILDHANDLER_H_
#define RECORDERH264CHILDHANDLER_H_

#include <unistd.h>

#include <memory>

#include "opendavinci/odcore/base/Condition.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odtools/recorder/RecorderDelegate.h"

#include <opendavinci/odcore/io/ConnectionListener.h>
#include <opendavinci/odcore/io/StringListener.h>
#include <opendavinci/odcore/io/tcp/TCPAcceptorListener.h>
#include <opendavinci/odcore/io/tcp/TCPConnection.h>
#include <opendavinci/odcore/io/tcp/TCPAcceptor.h>

namespace odrecorderh264 {

    using namespace std;

    /**
     * This class is handling connections to the spawned child processes.
     */
    class RecorderH264ChildHandler : public odtools::recorder::RecorderDelegate,
                                     public odcore::io::tcp::TCPAcceptorListener,
                                     public odcore::io::ConnectionListener,
                                     public odcore::io::StringListener {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            RecorderH264ChildHandler(const RecorderH264ChildHandler &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            RecorderH264ChildHandler& operator=(const RecorderH264ChildHandler &/*obj*/);

        public:
            /**
             * Constructor.
             */
            RecorderH264ChildHandler();

            /**
             * Constructor.
             *
             * @param port Port to be used to connect to the parent process.
             */
            RecorderH264ChildHandler(const uint32_t &port);

            virtual ~RecorderH264ChildHandler();

            virtual void onNewConnection(std::shared_ptr<odcore::io::tcp::TCPConnection> connection);

            virtual void nextString(const std::string &s);

            virtual void handleConnectionError();

            virtual odcore::data::Container process(odcore::data::Container &c);

            /**
             * This method is blocking the parent to let the child connect
             * to the parent process.
             */
            void waitForClientToConnect();

            /**
             * This method sets the actual TCP connection.
             *
             * @param c TCP connection.
             */
            void setConnection(shared_ptr<odcore::io::tcp::TCPConnection> c);

            /**
             * This method returns the actual TCP connection.
             *
             * @return TCP connection.
             */
            shared_ptr<odcore::io::tcp::TCPConnection> getConnection() const;

            /**
             * This method sets the child's PID.
             *
             * @param pid.
             */
            void setPID(pid_t pid);

            /**
             * This method returns the child's PID.
             *
             * @return Child's PID.
             */
            pid_t getPID() const;

        private:
            pid_t m_PID;
            shared_ptr<odcore::io::tcp::TCPAcceptor> m_tcpacceptor;
            shared_ptr<odcore::io::tcp::TCPConnection> m_connection;
            odcore::base::Condition m_condition;
            odcore::base::Mutex m_hasResponseMutex;
            bool m_hasResponse;
            odcore::data::Container m_response;
    };

} // odrecorderh264

#endif /*RECORDERH264CHILDHANDLER_H_*/
