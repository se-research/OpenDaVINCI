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

#ifndef OPENDAVINCI_CORE_WRAPPER_POSIXTCPACCEPTOR_H_
#define OPENDAVINCI_CORE_WRAPPER_POSIXTCPACCEPTOR_H_

#include <memory>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/io/tcp/TCPAcceptor.h"
#include "opendavinci/odcore/wrapper/Runnable.h"

namespace odcore { namespace io { namespace tcp { class TCPAcceptorListener; } } }
namespace odcore { namespace io { namespace tcp { class TCPConnection; } } }
namespace odcore { namespace wrapper { class Mutex; } }
namespace odcore { namespace wrapper { class Thread; } }
namespace odcore { template <class T> class SharedPointer; }

namespace odcore {
    namespace wrapper {
        namespace POSIX {

            using namespace std;

            class POSIXTCPAcceptor : public odcore::io::tcp::TCPAcceptor, public Runnable {
                private:
                    static const int32_t BACKLOG = 100;

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    POSIXTCPAcceptor(const POSIXTCPAcceptor &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    POSIXTCPAcceptor& operator=(const POSIXTCPAcceptor &);

                public:
                    POSIXTCPAcceptor(const uint32_t& port);
                    virtual ~POSIXTCPAcceptor();

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
#endif /* OPENDAVINCI_CORE_WRAPPER_POSIXTCPACCEPTOR_H_ */
