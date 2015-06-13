How to use realtime concurrency in OpenDaVINCI
==============================================

OpenDaVINCI has a built-in realtime concurrency engine available only on Linux
platforms with rt-preempt kernels. The sources to this example are available
at https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/realtimeservice

In order to use realtime concurrency in a user-supplied module, you will find
a simple example below.

MyRealtimeService.hpp:

.. code-block:: c++

    #include <core/base/RealtimeService.h>

    // Realtime concurrency is provided by the class core::base::RealtimeService.
    class MyRealtimeService : public core::base::RealtimeService {

        public:
            MyRealtimeService(const enum PERIOD &period);

            // Your class needs to implement the method void nextTimeSlice().
            virtual void nextTimeSlice();

    };

MyRealtimeService.cpp:

.. code-block:: c++

    #include <stdint.h>
    #include <iostream>
    #include <core/base/Thread.h>

    #include "MyRealtimeService.hpp"

    using namespace std;

    MyRealtimeService::MyRealtimeService(const enum PERIOD &period) :
        core::base::RealtimeService(period) {}

    void MyRealtimeService::nextTimeSlice() {
        cout << "This message is printed every 100 ms." << endl;        
    }

    int32_t main(int32_t argc, char **argv) {
        MyRealtimeService rts(core::base::RealtimeService::HUNDREDMILLISECONDS);

        rts.start();

        const uint32_t ONE_SECOND = 1000 * 1000;
        core::base::Thread::usleepFor(5 * ONE_SECOND);

        rts.stop();
    }

Your class needs to derive from ``core::base::RealtimeService``, which is provided in
``#include <core/base/RealtimeService.h>`` in the include directory ``opendavinci``.
This class provides one method that needs to be implemented in deriving classes:
``void nextTimeSlice()``. This method will be called with the specified periodicity.

Furthermore, the deriving class needs to pass the desired periodicity to the superclass ``RealtimeService``.

You can compile and link the example::

   g++ -I /usr/include/opendavinci -c MyRealtimeService.cpp -o MyRealtimeService.o
   g++ -o realtimeservice MyRealtimeService.o -lopendavinci -lpthread -lrt

The resulting program can be run as superuser (as the scheduling properties will be
adjusted) and will print the following on the console::

    $ sudo ./realtimeservice
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
    This message is printed every 100 ms.
