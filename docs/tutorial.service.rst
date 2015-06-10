How to use concurrency in OpenDaVINCI
=====================================

OpenDaVINCI has a built-in platform-independent concurrency engine. Concurrency is
realized on Linux-based and BSD-based operating systems using pthreads and on Windows
by using C++11 features.

In order to use concurrency in a user-supplied module, you will find a simple example
below::

    #include <iostream>
    #include <core/base/Service.h>
    #include <core/base/Thread.h>

    using namespace std;

    // Concurrency is provided by the class core::base::Service.
    class MyService : public core::base::Service {

        // Your class needs to implement the method void beforeStop().
        virtual void beforeStop() {
            // This block is executed right before the thread will be stopped.
            cout << "This method is called right before isRunning will return false." << endl;        
        }

        // Your class needs to implement the method void run().
        virtual void run() {
            // Here, you can do some initialization of resources (e.g. data structures and the like).
            cout << "Here, I can do some initialization as the calling thread, which will start this service, will be blocked until serviceReady() has been called." << endl;

            serviceReady();

            // This is the body of the concurrently executed method.
            while (isRunning()) {
                cout << "This message is printed every second." << endl;        

                const uint32_t ONE_SECOND = 1000 * 1000;
                core::base::Thread::usleepFor(ONE_SECOND);
            }
        }
    };

    int32_t main(int32_t argc, char **argv) {
        MyService s;

        s.start();
        const uint32_t ONE_SECOND = 1000 * 1000;
        core::base::Thread::usleepFor(10 * ONE_SECOND);

        s.stop();
    }

You can compile and link the example assuming the file is called Tutorial-Thread.cpp::

   g++ -I /usr/include/opendavinci -c Tutorial-Thread.cpp -o Tutorial-Thread.o
   g++ -o Tutorial-Thread Tutorial-Thread.o -lopendavinci -lpthread -lrt

Running the example above will print the following on the console::

    $ ./Tutorial-Thread
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
