How to setup the build environment for your software system
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This example demonstrates how to setup your build environment.

"Hello World" example
"""""""""""""""""""""

Let's assume you have implemented a basic "Hello World" application
to start with as shown in the following.

HelloWorldExample.h:

.. code-block:: c++

    #include <core/base/TimeTriggeredConferenceClientModule.h>

    class HelloWorldExample : public core::base::module::TimeTriggeredConferenceClientModule {
        private:
            HelloWorldExample(const HelloWorldExample &/*obj*/);
            HelloWorldExample& operator=(const HelloWorldExample &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            HelloWorldExample(const int32_t &argc, char **argv);

            virtual ~HelloWorldExample();

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

        private:
            virtual void setUp();

            virtual void tearDown();
    };

The accompanying implementation for this header file is provided in the following.

HelloWorldExample.cpp:

.. code-block:: c++

    #include <iostream>

    #include "HelloWorldExample.h"

    using namespace std;

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace core::base::module;

    HelloWorldExample::HelloWorldExample(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "HelloWorldExample")
        {}

    HelloWorldExample::~HelloWorldExample() {}

    void HelloWorldExample::setUp() {
        cout << "This method is called before the component's body is executed." << endl;
    }

    void HelloWorldExample::tearDown() {
        cout << "This method is called after the program flow returns from the component's body." << endl;
    }

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode HelloWorldExample::body() {
        cout << "Hello OpenDaVINCI World!" << endl;

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

To start the component, we define the main() function in a separate file.

HelloWorldExampleMain.cpp:

.. code-block:: c++

    #include "HelloWorldExample.h"

    int32_t main(int32_t argc, char **argv) {
        HelloWorldExample hwe(argc, argv);

        return hwe.runModule();
    }

Now, we have three files, HelloWorldExample.h, HelloWorldExample.cpp, and
HelloWorldExampleMain.cpp. The first two files contain the software component for
the "Hello World" example, the latter file is simply starting the component.

Now, you can compile and link the example manually::

   $ g++ -I /usr/include/opendavinci -c HelloWorldExample.cpp -o HelloWorldExample.o
   $ g++ -I /usr/include/opendavinci -c HelloWorldExampleMain.cpp -o HelloWorldExampleMain.o
   $ g++ -o helloworldexample HelloWorldExampleMain.o HelloWorldExample.o -lopendavinci -lpthread

