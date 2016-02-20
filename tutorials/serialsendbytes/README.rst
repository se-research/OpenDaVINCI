How to send bytes over a serial link
""""""""""""""""""""""""""""""""""""

OpenDaVINCI has a built-in serial port handling engine based on
https://github.com/wjwwood/serial. This library realizes serial communication on
Linux- and BSD-based platforms as well as on Windows. The sources for this
example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/serialsendbytes

In order to send bytes over a serial link, you will find a simple example below.

SerialSendBytes.cpp:

.. code-block:: c++

    #include <stdint.h>
    #include <iostream>
    #include <string>
    #include <opendavinci/odcore/SharedPointer.h>
    #include <opendavinci/odcore/wrapper/SerialPort.h>
    #include <opendavinci/odcore/wrapper/SerialPortFactory.h>

    using namespace std;

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace odcore;
    using namespace odcore::wrapper;

    int32_t main(int32_t argc, char **argv) {
        const string SERIAL_PORT = "/dev/pts/19";
        const uint32_t BAUD_RATE = 19200;

        // We are using OpenDaVINCI's SharedPointer to automatically
        // release any acquired resources.
        try {
            SharedPointer<SerialPort> serial(SerialPortFactory::createSerialPort(SERIAL_PORT, BAUD_RATE));

            serial->send("Hello World\r\n");
        }
        catch(string &exception) {
            cerr << "Serial port could not be created: " << exception << endl;
        }
    }

To send bytes over a serial link, your application needs to include
``<opendavinci/odcore/wrapper/SerialPort.h>`` and ``<opendavinci/odcore/wrapper/SerialPortFactory.h>`` that
encapsulate the platform-specific implementations.

``SerialPortFactory`` provides a static method called ``createSerialPort`` that
tries to connect to the specified serial port. On success, this call will return
a pointer to a ``SerialPort`` instance that is used to handle the data transfer.
On failure, the method ``createSerialPort`` will throw an exception of type
``string`` with an error message.

If the connection could be successfully established, the method ``send`` can be
used to send data of type ``string`` to the other end of the serial link.

To conveniently handle the resource management of releasing the acquired system
resources, a ``SharedPointer`` is used that automatically releases memory that
is no longer used.

You can compile and link the example::

   g++ -I /usr/include -c SerialSendBytes.cpp -o SerialSendBytes.o
   g++ -o serialsendbytes SerialSendBytes.o -lopendavinci -lpthread

To test the program, we create a simple virtual serial port on Linux using the
tool ``socat``::

    $ socat -d -d pty,raw,echo=0 pty,raw,echo=0
    2015/06/13 11:17:17 socat[2737] N PTY is /dev/pts/19
    2015/06/13 11:17:17 socat[2737] N PTY is /dev/pts/20
    2015/06/13 11:17:17 socat[2737] N starting data transfer loop with FDs [3,3] and [5,5]

Please note that the tutorial program uses ``/dev/pts/19`` to send data to; in
the case that your setup has a different ``pts`` from ``socat``, you need to adjust
the source code.

Next, start a ``screen`` session on the other end of the serial connection::

    $ screen /dev/pts/20

Now, you can run the resulting program::

    $ ./serialsendbytes
    $

The tool ``screen`` will print ``Hello World``.

