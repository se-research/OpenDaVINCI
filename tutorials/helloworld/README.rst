How to setup the build environment for your software system
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This example demonstrates how to setup your build environment.

"Hello World" example - compiling manually
""""""""""""""""""""""""""""""""""""""""""

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


"Hello World" example - compiling using CMake
"""""""""""""""""""""""""""""""""""""""""""""

Next, we are going to extend the previous example and introduce CMake as
the build system. The advantage of CMake is that you describe the build
of your software independent from the build tools like make, KDevelop,
or the like.

We create a file named CMakeLists.txt to describe the actual source code
artifacts that comprise our final binary. After the definition of the
CMake version that is required (2.8) in our example, we name the project
that we are building. Next, we need to declare the dependency to
OpenDaVINCI (cf. (1)). As OpenDaVINCI can be either installed to /usr
from the pre-compiled packages or in a specific directory, we need to
adjust this possibility accordingly in the CMakeLists.txt. Therefore,
OpenDaVINCI provides a CMake-script to determine the correct settings
for locating OpenDaVINCI's include headers and linker settings. This
script considers the parameter OPENDAVINCI_DIR where we can specify
at commandline where CMake shall search for OpenDaVINCI. If this
parameter is left unset, OpenDaVINCI is assumed to be installed in
your distributions default locations, like /usr or /usr/local.
Next, FIND_PACKAGE(...) is called to actually find OpenDaVINCI.

If the FIND_PACKAGE(...) succeeds, the variables OPENDAVINCI_INCLUDE_DIRS
and OPENDAVINCI_LIBRARIES. We are using the former to refer to the
include headers so that HelloWorldExample.h can be compiled using the
OpenDaVINCI classes.

Next, we specify the sources (cf. (3)) that are required to create
the binary. Afterwards, we define the executable and the libraries
that are required to link. The last line specifies where the resulting
shall be installed to.

.. code-block::

    CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

    PROJECT (helloworldexample)

    # (1) Find OpenDaVINCI.
    IF("${OPENDAVINCI_DIR}" STREQUAL "")
        SET(OPENDAVINCI_DIR "${CMAKE_INSTALL_PREFIX}")
    ELSE()
        SET (CMAKE_MODULE_PATH "${OPENDAVINCI_DIR}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" ${CMAKE_MODULE_PATH})
    ENDIF()
    FIND_PACKAGE (OpenDaVINCI REQUIRED)

    # (2) Set header files from OpenDaVINCI.
    INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS}/opendavinci)

    # (3) Build the project.
    SET(SOURCES HelloWorldExample.cpp HelloWorldExampleMain.cpp)
    ADD_EXECUTABLE (helloworldexample ${SOURCES})
    TARGET_LINK_LIBRARIES (helloworldexample ${OPENDAVINCI_LIBRARIES}) 

    # (4) Install the binary.
    INSTALL(TARGETS helloworldexample RUNTIME DESTINATION bin COMPONENT tutorials)

