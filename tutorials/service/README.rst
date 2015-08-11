How to use concurrency
^^^^^^^^^^^^^^^^^^^^^^

OpenDaVINCI has a built-in platform-independent concurrency engine. Concurrency is
realized on Linux-based and BSD-based operating systems using pthreads and on Windows
by using C++11 features. The sources for this example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/service

In order to use concurrency in a user-supplied module, you will find a simple example
below.

MyService.hpp:

.. code-block:: c++

    #include <core/base/Service.h>

    // Concurrency is provided by the class core::base::Service.
    class MyService : public core::base::Service {

        // Your class needs to implement the method void beforeStop().
        virtual void beforeStop();

        // Your class needs to implement the method void run().
        virtual void run();

    };

MyService.cpp:

.. code-block:: c++

    #include <stdint.h>
    #include <iostream>
    #include <core/base/Thread.h>

    #include "MyService.hpp"

    using namespace std;

    // Your class needs to implement the method void beforeStop().
    void MyService::beforeStop() {
        // This block is executed right before
        // the thread will be stopped.
        cout << "This method is called right before "
             << "isRunning will return false." << endl;        
    }

    // Your class needs to implement the method void run().
    void MyService::run() {
        // Here, you can do some initialization of
        // resources (e.g. data structures and the like).
        cout << "Here, I can do some initialization as the "
             << "calling thread, which will start this service, "
             << "will be blocked until serviceReady() has been called." << endl;

        serviceReady();

        // This is the body of the concurrently executed method.
        while (isRunning()) {
            cout << "This message is printed every second." << endl;        

            const uint32_t ONE_SECOND = 1000 * 1000;
            core::base::Thread::usleepFor(ONE_SECOND);
        }
    }

    int32_t main(int32_t argc, char **argv) {
        MyService s;

        s.start();
        const uint32_t ONE_SECOND = 1000 * 1000;
        core::base::Thread::usleepFor(10 * ONE_SECOND);

        s.stop();
    }

Your class needs to derive from ``core::base::Service``, which is provided in
``#include <core/base/Service.h>`` in the include directory ``opendavinci``.
This class provides two methods that need to be implemented in deriving classes:
``void beforeStop()`` and ``void run()``. The former method is called
from an outside thread intending to stop the concurrently executing thread; thus
any shared resources can be released properly for example. The latter method will
be executed in a new thread running concurrently to the calling thread.

To detach the execution of the newly created thread from the calling one, the
method ``serviceReady()`` needs to be called to signal to the calling thread that
the new thread is initialized and will now enter, e.g., its main processing loop; the calling thread is blocked
from any further execution until this method is called. This synchronization dependency
ensures that both any resources that need to be provided by the operating system
to run a thread are available and ready, and any shared resources like data
structures that are needed from a deriving class are set up and ready.

You can compile and link the example assuming the file is called Tutorial-Thread.cpp::

   g++ -I /usr/include/opendavinci -c MyService.cpp -o MyService.o
   g++ -o service MyService.o -lopendavinci -lpthread

Running the example above will print the following on the console::

    $ ./service
    Here, I can do some initialization as the calling thread, which will start this service, will be blocked until serviceReady() has been called.
    This message is printed every second.
    This message is printed every second.
    This message is printed every second.
    This message is printed every second.
    This message is printed every second.
    This message is printed every second.
    This message is printed every second.
    This message is printed every second.
    This message is printed every second.
    This message is printed every second.
    This method is called right before isRunning will return false.
