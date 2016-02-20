How to receive bytes as a TCP server
""""""""""""""""""""""""""""""""""""

OpenDaVINCI has a built-in TCP handling engine realized on Linux-based
and BSD-based operating systems using POSIX sockets and on Windows using WinSock.
The sources for this example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/tcpreceivebytes

In order to receive bytes as a TCP server, you will find a simple example
below.

TCPReceiveBytes.hpp:

.. code-block:: c++

    #include <opendavinci/odcore/io/ConnectionListener.h>
    #include <opendavinci/odcore/io/StringListener.h>
    #include <opendavinci/odcore/io/TCPAcceptorListener.h>
    #include <opendavinci/odcore/io/TCPConnection.h>

    // This class will handle newly accepted TCP connections.
    class TCPReceiveBytes : 
        public odcore::io::ConnectionListener,
        public odcore::io::StringListener,
        public odcore::io::tcp::TCPAcceptorListener {

        // Your class needs to implement the method void nextString(const std::string &s).
        virtual void nextString(const std::string &s);

        // Your class needs to implement the method void onNewConnection(odcore::SharedPointer<odcore::io::tcp::TCPConnection> connection).
        virtual void onNewConnection(odcore::SharedPointer<odcore::io::tcp::TCPConnection> connection);

        // Your class should implement the method void handleConnectionError() to handle connection errors (like terminated connections).
        virtual void handleConnectionError();
    };

To receive any data, we firstly declare a class that implements the interfaces
``core::io::StringListener`` to receive bytes and
``core::io::tcp::TCPAcceptorListener`` where any newly accepted connections will
be reported to. This class will be registered as listener to our accepting TCP
socket that we create later. In addition, we also register a ``core::io::ConnectionLister``
that is invoked in the case of any connection error like the connecting client
has closed the connection.

TCPReceiveBytes.cpp:

.. code-block:: c++

    #include <stdint.h>
    #include <iostream>
    #include <string>
    #include <opendavinci/odcore/SharedPointer.h>
    #include <opendavinci/odcore/base/Thread.h>
    #include <opendavinci/odcore/io/tcp/TCPAcceptor.h>
    #include <opendavinci/odcore/io/tcp/TCPFactory.h>

    #include "TCPReceiveBytes.hpp"

    using namespace std;

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace odcore;
    using namespace odcore::io;
    using namespace odcore::io:tcp;

    void TCPReceiveBytes::handleConnectionError() {
        cout << "Connection terminated." << endl;
    }

    void TCPReceiveBytes::nextString(const std::string &s) {
        cout << "Received " << s.length() << " bytes containing '" << s << "'" << endl;
    }

    void TCPReceiveBytes::onNewConnection(odcore::SharedPointer<odcore::io::tcp::TCPConnection> connection) {
        if (connection.isValid()) {
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

        // We are using OpenDaVINCI's SharedPointer to automatically
        // release any acquired resources.
        try {
            SharedPointer<TCPAcceptor>
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

The outlined implementation will provide an overview of how to get notified
about newly connecting clients using TCP; your application should track
new connections in a ``vector`` for instance and manage their individual
connection status properly.
 
To receive bytes from a TCP socket, your application needs to include
``<opendavinci/odcore/io/tcp/TCPAcceptor.h>`` and ``<opendavinci/odcore/io/tcp/TCPFactory.h>`` that encapsulate
the platform-specific implementations.

``TCPFactory`` provides a static method called ``createTCPAcceptor`` that allows
you to accept new TCP connections. Every new connection is wrapped into a pointer
to an instance of ``TCPConnection`` that needs to be handled by a ``TCPAcceptorListener``.
The task for the ``TCPAcceptorListener`` is to get the new ``TCPConnection``,
register a ``StringListener`` to receive bytes and a ``ConnectionListener``
that is called when an error for this TCP connection occurs, e.g. the client
closes the connection.

``TCPFactory`` will return a pointer to the ``TCPAcceptor``, where our
``TCPReceiveBytes`` handler in turn is registered to handle incoming connection.
On failure, the method ``createTCPAcceptor`` will throw an exception of type
``string`` with an error message.

If the ``TCPAcceptor`` could be successfully created, we register our ``TCPReceiveBytes``
to handle new connections. Afterwards, we start our ``TCPAcceptor`` to wait for
incoming TCP connections. After some time, the program will stop waiting for new
connections, unregister the ``TCPReceiveBytes``, and release the system resources.

To conveniently handle the resource management of releasing the acquired system
resources, a ``SharedPointer`` is used that automatically releases memory that
is no longer used.

Please note that once you have stopped ``TCPAcceptor`` you cannot reuse it and
thus, you need to create a new one.

You can compile and link the example::

   g++ -I /usr/include -c TCPReceiveBytes.cpp -o TCPReceiveBytes.o
   g++ -o tcpreceivebytes TCPReceiveBytes.o -lopendavinci -lpthread

The resulting program can be run::

    $ ./tcpreceivebytes

To test the program, we use the test program ``tcpsendbytes`` as described here
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/tcpsendbytes::

    $ ./tcpsendbytes

Our program ``tcpreceivebytes`` will print::

    Handle a new connection.
    Received 13 bytes containing 'Hello World
    '
    Connection terminated.


