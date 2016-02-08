How to send bytes to a TCP server
"""""""""""""""""""""""""""""""""

OpenDaVINCI has a built-in TCP connection handling engine realized on Linux-based
and BSD-based operating systems using POSIX sockets and on Windows using WinSock.
The sources for this example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/tcpsendbytes

In order to send bytes to an existing TCP server, you will find a simple example
below.

TCPSendBytes.cpp:

.. code-block:: c++

    #include <stdint.h>
    #include <iostream>
    #include <string>
    #include <opendavinci/core/SharedPointer.h>
    #include <opendavinci/core/io/tcp/TCPConnection.h>
    #include <opendavinci/core/io/tcp/TCPFactory.h>

    using namespace std;

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace core;
    using namespace core::io::tcp;

    int32_t main(int32_t argc, char **argv) {
        const string RECEIVER = "127.0.0.1";
        const uint32_t PORT = 1234;

        // We are using OpenDaVINCI's SharedPointer to automatically
        // release any acquired resources.
        try {
            SharedPointer<TCPConnection>
                connection(TCPFactory::createTCPConnectionTo(RECEIVER, PORT));

            connection->send("Hello World\r\n");
        }
        catch(string &exception) {
            cerr << "Data could not be sent: " << exception << endl;
        }
    }

To send bytes over a TCP link to a TCP server, your application needs to include
``<opendavinci/core/io/tcp/TCPConnection.h>`` and ``<opendavinci/core/io/tcp/TCPFactory.h>`` that encapsulate
the platform-specific implementations.

``TCPFactory`` provides a static method called ``createTCPConnectionTo`` that
tries to connect to the specified TCP server. On success, this call will return
a pointer to a ``TCPConnection`` instance that is used to handle the data transfer.
On failure, the method ``createTCPConnectionTo`` will throw an exception of type
``string`` with an error message.

If the connection could be successfully established, the method ``send`` can be
used to send data of type ``string`` to the other end of the TCP link.

To conveniently handle the resource management of releasing the acquired system
resources, a ``SharedPointer`` is used that automatically releases memory that
is no longer used.

You can compile and link the example::

   g++ -I /usr/include -c TCPSendBytes.cpp -o TCPSendBytes.o
   g++ -o tcpsendbytes TCPSendBytes.o -lopendavinci -lpthread

To test the program, we create a simple TCP server awaiting connection by using
the tool ``nc``::

    $ nc -l -p 1234

The resulting program can be run::

    $ ./tcpsendbytes
    $

The tool ``nc`` will print ``Hello World`` and then terminate as the connection
is closed on exiting ``tcpsendbytes``.

In the case of a failed connection attempt, the following exception will be printed
on the console::

    $ ./tcpsendbytes
    Data could not be sent: [PosixTCPConnection] Error connecting to socket

