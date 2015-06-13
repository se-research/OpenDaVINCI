How to receive packets as a UDP server
======================================

OpenDaVINCI has a built-in UDP handling engine realized on Linux-based
and BSD-based operating systems using POSIX sockets and on Windows using WinSock.
The sources to this example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/udpreceivebytes

In order to receive packets as a UDP server, you will find a simple example
below.

UDPReceivePackets.hpp:

.. code-block:: c++
   :linenos:

    #include <core/wrapper/PacketListener.h>

    // This class will handle packets received via a UDP socket.
    class UDPReceivePackets : public core::wrapper::PacketListener {

        // Your class needs to implement the method void void nextPacket(const core::wrapper::Packet &p).
        virtual void nextPacket(const core::wrapper::Packet &p);
    };

To receive any packets, we firstly declare a class that implements the interface
``core::wrapper::PacketListener``. This class will be registered as listener to
our UDP socket that we create later.

UDPReceivePackets.cpp:

.. code-block:: c++
   :linenos:

    #include <stdint.h>
    #include <iostream>
    #include <string>
    #include <core/SharedPointer.h>
    #include <core/base/Thread.h>
    #include <core/wrapper/UDPReceiver.h>
    #include <core/wrapper/UDPFactory.h>

    #include "UDPReceivePackets.hpp"

    using namespace std;

    void UDPReceivePackets::nextPacket(const core::wrapper::Packet &p) {
        cout << "Received a packet from " << p.getSender() << ", "
             << "with " << p.getData().length() << " bytes containing '"
             << p.getData() << "'" << endl;
    }

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace core;
    using namespace core::wrapper;

    int32_t main(int32_t argc, char **argv) {
        const string RECEIVER = "0.0.0.0";
        const uint32_t PORT = 1234;

        // We are using OpenDaVINCI's SharedPointer to automagically
        // released any acquired resources.
        try {
            SharedPointer<UDPReceiver>
                udpreceiver(UDPFactory::createUDPReceiver(RECEIVER, PORT));

            // This instance will handle any packets that are received
            // by our UDP socket.
            UDPReceivePackets handler;
            udpreceiver->setPacketListener(&handler);

            // Start receiving bytes.
            udpreceiver->start();

            const uint32_t ONE_SECOND = 1000 * 1000;
            core::base::Thread::usleepFor(10 * ONE_SECOND);

            // Stop receiving bytes and unregister our handler.
            udpreceiver->stop();
            udpreceiver->setPacketListener(NULL);
        }
        catch(string &exception) {
            cerr << "Error while creating UDP receiver: " << exception << endl;
        }
    }

To receive a packet from a UDP socket, your application needs to include
``<core/base/UDPReceiver.h>`` and ``<core/base/UDPFactory.h>`` that encapsulate
the platform-specific implementations.

``UDPFactory`` provides a static method called ``createUDPReceiver`` that allows
you to receive bytes from a listening UDP socket. On success, this call will return
a pointer to a ``UDPReceiver`` instance that is used to handle the data transfer.
On failure, the method ``createUDPReceiver`` will throw an exception of type
``string`` with an error message.

If the UDP socket could be successfully created, we register our ``PacketListener``
at the newly created ``UDPReceiver`` to be invoked when a new packet is available.
In contrast to the ``StringListener``, the data processing for handling ``Packets``
is not decoupled between the low level UDP socket and the user-supplied handler.

Once we have registered our ``PacketListener``, the ``UDPReceiver`` is simply
started and the main thread is falling asleep for a while in our example. After some
time, the program will stop receiving bytes, unregister the ``PacketListener``,
and release the system resources.

To conveniently handle the resource management of releasing the acquired system
resources, a ``SharedPointer`` is used that automatically releases memory that
is no longer used.

Please note that once you have stopped ``UDPReceiver`` you cannot reuse it and
thus, you need to create a new one.

You can compile and link the example::

   g++ -I /usr/include/opendavinci -c UDPReceivePackets.cpp -o UDPReceivePackets.o
   g++ -o udpreceivepackets UDPReceivePackets.o -lopendavinci -lpthread

The resulting program can be run::

    $ ./udpreceivepackets

To test the program, we pipe a string through the tool ``nc``::

    $ echo "Hello World" | nc -u 127.0.0.1 1234

Our program ``udpreceivepackets`` will print::

    Received a packet from 127.0.0.1, with 13 bytes containing 'Hello World!
    '


