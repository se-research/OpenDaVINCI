How to receive bytes from a serial connection
"""""""""""""""""""""""""""""""""""""""""""""

OpenDaVINCI has a built-in serial port handling engine based on
https://github.com/wjwwood/serial. This library realizes serial communication on
Linux- and BSD-based platforms as well as on Windows. The sources for this
example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/serialreceivebytes

In order to receive bytes over a serial link, you will find a simple example below.

SerialReceiveBytes.hpp:

.. code-block:: c++

    #include <opendavinci/odcore/io/StringListener.h>

    // This class will handle the bytes received via a serial link.
    class SerialReceiveBytes : public odcore::io::StringListener {

        // Your class needs to implement the method void nextString(const std::string &s).
        virtual void nextString(const std::string &s);
    };

To receive any data, we firstly declare a class that implements the interface
``core::io::StringListener``. This method will handle any bytes received
from the low level ``SerialPort``. Here, your application should realize an
application-specific protocol.

SerialReceiveBytes.cpp:

.. code-block:: c++

    #include <stdint.h>
    #include <iostream>
    #include <string>
#include <memory>
    #include <opendavinci/odcore/base/Thread.h>
    #include <opendavinci/odcore/wrapper/SerialPort.h>
    #include <opendavinci/odcore/wrapper/SerialPortFactory.h>

    #include "SerialReceiveBytes.hpp"

    using namespace std;

    void SerialReceiveBytes::nextString(const string &s) {
        cout << "Received " << s.length() << " bytes containing '" << s << "'" << endl;
    }

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace odcore;
    using namespace odcore::wrapper;

    int32_t main(int32_t argc, char **argv) {
        const string SERIAL_PORT = "/dev/pts/20";
        const uint32_t BAUD_RATE = 19200;

        // We are using OpenDaVINCI's std::shared_ptr to automatically
        // release any acquired resources.
        try {
            std::shared_ptr<SerialPort>
                serial(SerialPortFactory::createSerialPort(SERIAL_PORT, BAUD_RATE));

            // This instance will handle any bytes that are received
            // from our serial port.
            SerialReceiveBytes handler;
            serial->setStringListener(&handler);

            // Start receiving bytes.
            serial->start();

            const uint32_t ONE_SECOND = 1000 * 1000;
            odcore::base::Thread::usleepFor(10 * ONE_SECOND);

            // Stop receiving bytes and unregister our handler.
            serial->stop();
            serial->setStringListener(NULL);
        }
        catch(string &exception) {
            cerr << "Error while creating serial port: " << exception << endl;
        }
    }

To receive bytes from a serial link, your application needs to include
``<opendavinci/odcore/wrapper/SerialPort.h>`` and ``<opendavinci/odcore/wrapper/SerialPortFactory.h>`` that
encapsulate the platform-specific implementations.

``SerialPortFactory`` provides a static method called ``createSerialPort`` that allows
you to receive bytes from a serial link. On success, this call will return
a pointer to a ``SerialPort`` instance that is used to handle the data transfer.
On failure, the method ``createSerialPort`` will throw an exception of type
``string`` with an error message.

If the serial port could be successfully created, we register our ``StringListener``
at the newly created ``SerialPort`` to be invoked when new bytes are available to
be interpreted by a user-supplied protocol.

Once we have registered our ``StringListener``, the ``SerialPort`` is simply
started and the main thread is falling asleep for a while in our example. After some
time, the program will stop receiving bytes, unregister the ``StringListener``,
and release the system resources.

To conveniently handle the resource management of releasing the acquired system
resources, a ``std::shared_ptr`` is used that automatically releases memory that
is no longer used.

Please note that once you have stopped ``SerialPort`` you cannot reuse it and
thus, you need to create a new one.

You can compile and link the example::

   g++ -I /usr/include -c SerialReceiveBytes.cpp -o SerialReceiveBytes.o
   g++ -o serialreceivebytes SerialReceiveBytes.o -lopendavinci -lpthread

To test the program, we create a simple virtual serial port on Linux using the
tool ``socat``::

    $ socat -d -d pty,raw,echo=0 pty,raw,echo=0
    2015/06/13 11:17:17 socat[2737] N PTY is /dev/pts/19
    2015/06/13 11:17:17 socat[2737] N PTY is /dev/pts/20
    2015/06/13 11:17:17 socat[2737] N starting data transfer loop with FDs [3,3] and [5,5]

Please note that the tutorial program uses ``/dev/pts/20`` to send data to; in
the case that your setup has a different ``pts`` from ``socat``, you need to adjust
the source code.

Now, you can start the resulting program to listen for data::

    $ ./serialreceivebytes

Next, we simply pipe some data through the other end of the virtual port::

    $ echo "Hello World" > /dev/pts/19

The resulting program will print::

    Received partial string of length 12 bytes containing 'Hello World
    '

