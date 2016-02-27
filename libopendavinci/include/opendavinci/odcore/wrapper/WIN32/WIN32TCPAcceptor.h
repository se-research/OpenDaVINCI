/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

#ifndef OPENDAVINCI_CORE_WRAPPER_WIN32IMPL_WIN32TCPACCEPTOR_H_
#define OPENDAVINCI_CORE_WRAPPER_WIN32IMPL_WIN32TCPACCEPTOR_H_

#include <memory>

#include "opendavinci/odcore/opendavinci.h"

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/io/tcp/TCPAcceptor.h"
#include "opendavinci/odcore/io/tcp/TCPAcceptorListener.h"
#include "opendavinci/odcore/io/tcp/TCPConnection.h"
#include "opendavinci/odcore/wrapper/Runnable.h"
#include "opendavinci/odcore/wrapper/Thread.h"
#include "opendavinci/odcore/wrapper/Mutex.h"

namespace odcore {
    namespace wrapper {
        namespace WIN32Impl {

            using namespace std;

            class WIN32TCPAcceptor : public odcore::io::tcp::TCPAcceptor, public Runnable {
                private:
                    static const int32_t BACKLOG = 100;

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    WIN32TCPAcceptor(const WIN32TCPAcceptor &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    WIN32TCPAcceptor& operator=(const WIN32TCPAcceptor &);

                public:
                    WIN32TCPAcceptor(const uint32_t& port);
                    virtual ~WIN32TCPAcceptor();

                    virtual void setAcceptorListener(odcore::io::tcp::TCPAcceptorListener* listener);

                    virtual void start();
                    virtual void stop();

                    virtual bool isRunning();
                    virtual void run();

                protected:
                    void invokeAcceptorListener(odcore::SharedPointer<odcore::io::tcp::TCPConnection> connection);

                    unique_ptr<Thread> m_thread;

                    unique_ptr<Mutex> m_listenerMutex;
                    odcore::io::tcp::TCPAcceptorListener* m_listener;

                    int32_t m_fileDescriptor;
                    int32_t m_port;
            };
        }
    }
}
#endif /* OPENDAVINCI_CORE_WRAPPER_WIN32IMPL_WIN32TCPACCEPTOR_H_ */
