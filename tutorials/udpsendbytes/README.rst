How to send bytes to a UDP server
=================================

OpenDaVINCI has a built-in UDP handling engine realized on Linux-based
and BSD-based operating systems using POSIX sockets and on Windows using WinSock.
The sources to this example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/udpsendbytes

In order to send bytes to a UDP server, you will find a simple example
below.

UDPSendBytes.cpp:

.. code-block:: c++
    #include <stdint.h>
    #include <iostream>
    #include <string>
    #include <core/SharedPointer.h>
    #include <core/wrapper/UDPSender.h>
    #include <core/wrapper/UDPFactory.h>

    using namespace std;

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace core;
    using namespace core::wrapper;

    int32_t main(int32_t argc, char **argv) {
        const string RECEIVER = "127.0.0.1";
        const uint32_t PORT = 1234;

        // We are using OpenDaVINCI's SharedPointer to automagically
        // released any acquired resources.
        try {
            SharedPointer<UDPSender> udpsender(UDPFactory::createUDPSender(RECEIVER, PORT));

            udpsender->send("Hello World\r\n");
        }
        catch(string &exception) {
            cerr << "Data could not be sent: " << exception << endl;
        }
    }

To send bytes over UDP to a UDP socket, your application needs to include
``<core/base/UDPSender.h>`` and ``<core/base/UDPFactory.h>`` that encapsulate
the platform-specific implementations.

``UDPFactory`` provides a static method called ``createUDPSender`` that
allows you to send bytes to the specified UDP server. On success, this call will return
a pointer to a ``UDPServer`` instance that is used to handle the data transfer.
On failure, the method ``createUDPSender`` will throw an exception of type
``string`` with an error message.

If the connection could be successfully established, the method ``send`` can be
used to send data of type ``string`` to the specified UDP server.

To conveniently handle the resource management of releasing the acquired system
resources, a ``SharedPointer`` is used that automatically releases memory that
is no longer used.

You can compile and link the example::

   g++ -I /usr/include/opendavinci -c UDPSendBytes.cpp -o UDPSendBytes.o
   g++ -o udpsendbytes UDPSendBytes.o -lopendavinci -lpthread

To test the program, we create a simple UDP server awaiting data by using
the tool ``nc``::

    $ nc -l -p -u 1234

The resulting program can be run::

    $ ./udpsendbytes
    $

The tool ``nc`` will print ``Hello World`` and then terminate as the connection
is closed on exiting ``tcpsendbytes``.

