How to receive bytes as a UDP server
""""""""""""""""""""""""""""""""""""

OpenDaVINCI has a built-in UDP handling engine realized on Linux-based
and BSD-based operating systems using POSIX sockets and on Windows using WinSock.
The sources for this example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/udpreceivebytes

In order to receive bytes as a UDP server, you will find a simple example
below.

UDPReceiveBytes.hpp:

.. code-block:: c++

    #include <core/wrapper/StringListener.h>

    // This class will handle the bytes received via a UDP socket.
    class UDPReceiveBytes : public core::wrapper::StringListener {

        // Your class needs to implement the method void nextString(const std::string &s).
        virtual void nextString(const std::string &s);
    };

To receive any data, we firstly declare a class that implements the interface
``core::wrapper::StringListener``. This class will be registered as listener to
our UDP socket that we create later.

UDPReceiveBytes.cpp:

.. code-block:: c++

    #include <stdint.h>
    #include <iostream>
    #include <string>
    #include <core/SharedPointer.h>
    #include <core/base/Thread.h>
    #include <core/wrapper/UDPReceiver.h>
    #include <core/wrapper/UDPFactory.h>

    #include "UDPReceiveBytes.hpp"

    using namespace std;

    void UDPReceiveBytes::nextString(const string &s) {
        cout << "Received " << s.length() << " bytes containing '" << s << "'" << endl;
    }

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace core;
    using namespace core::wrapper;

    int32_t main(int32_t argc, char **argv) {
        const string RECEIVER = "0.0.0.0";
        const uint32_t PORT = 1234;

        // We are using OpenDaVINCI's SharedPointer to automatically
        // release any acquired resources.
        try {
            SharedPointer<UDPReceiver>
                udpreceiver(UDPFactory::createUDPReceiver(RECEIVER, PORT));

            // This instance will handle any bytes that are received
            // by our UDP socket.
            UDPReceiveBytes handler;
            udpreceiver->setStringListener(&handler);

            // Start receiving bytes.
            udpreceiver->start();

            const uint32_t ONE_SECOND = 1000 * 1000;
            core::base::Thread::usleepFor(10 * ONE_SECOND);

            // Stop receiving bytes and unregister our handler.
            udpreceiver->stop();
            udpreceiver->setStringListener(NULL);
        }
        catch(string &exception) {
            cerr << "Error while creating UDP receiver: " << exception << endl;
        }
    }

To receive bytes from a UDP socket, your application needs to include
``<core/wrapper/UDPReceiver.h>`` and ``<core/wrapper/UDPFactory.h>`` that encapsulate
the platform-specific implementations.

``UDPFactory`` provides a static method called ``createUDPReceiver`` that allows
you to receive bytes from a listening UDP socket. On success, this call will return
a pointer to a ``UDPReceiver`` instance that is used to handle the data transfer.
On failure, the method ``createUDPReceiver`` will throw an exception of type
``string`` with an error message.

If the UDP socket could be successfully created, we register our ``StringListener``
at the newly created ``UDPReceiver`` to be invoked when new bytes are available.
Handling the bytes between the UDP socket and the ``StringListener`` notification
is separated in different threads to avoid blocking the receiving thread in
``UDPReceiver`` (realizing a concurrent ``StringPipeline``): When new bytes are available, the
``UDPReceiver`` will enqueue them as ``string`` into a FIFO queue; the
``StringPipeline`` class has an own thread sleeping on a condition awaiting new
entries to be entered into the FIFO queue. Whenever a new entry is present, this
thread will be automatically awaken and process all available entries 
by calling the user-supplied ``StringListener`` to deliver the data.
This mechanism ensures that the thread handling the lower level UDP socket is not
unnecessarily delayed by a user-supplied handling function.

Once we have registered our ``StringListener``, the ``UDPReceiver`` is simply
started and the main thread is falling asleep for a while in our example. After some
time, the program will stop receiving bytes, unregister the ``StringListener``,
and release the system resources.

To conveniently handle the resource management of releasing the acquired system
resources, a ``SharedPointer`` is used that automatically releases memory that
is no longer used.

Please note that once you have stopped ``UDPReceiver`` you cannot reuse it and
thus, you need to create a new one.

You can compile and link the example::

   g++ -I /usr/include/opendavinci -c UDPReceiveBytes.cpp -o UDPReceiveBytes.o
   g++ -o udpreceivebytes UDPReceiveBytes.o -lopendavinci -lpthread

The resulting program can be run::

    $ ./udpreceivebytes

To test the program, we pipe a string through the tool ``nc``::

    $ echo "Hello World" | nc -u 127.0.0.1 1234

Our program ``udpreceivebytes`` will print ``Hello World``.

