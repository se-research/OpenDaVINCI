How to design a time-triggered software component
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

OpenDaVINCI allows the development of distributed software components. These
components can run on the same machine or on different ones using various
types of communication and scheduling. Both is provided transparently to the
user of the OpenDaVINCI middleware.

This example demonstrates how to design a time-triggered software component.
The sources for this example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/timetrigger

"Hello World" example
"""""""""""""""""""""

A time-triggered software component is derived from ``core::base::TimeTriggeredConferenceClientModule``,
provided in ``<core/base/TimeTriggeredConferenceClientModule.h>``.

TimeTriggerExample.h:

.. code-block:: c++

    #include <core/base/TimeTriggeredConferenceClientModule.h>

    class TimeTriggerExample : public core::base::TimeTriggeredConferenceClientModule {
        private:
            TimeTriggerExample(const TimeTriggerExample &/*obj*/);
            TimeTriggerExample& operator=(const TimeTriggerExample &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            TimeTriggerExample(const int32_t &argc, char **argv);

            virtual ~TimeTriggerExample();

            core::base::ModuleState::MODULE_EXITCODE body();

        private:
            virtual void setUp();

            virtual void tearDown();
    };

The class ``core::base::TimeTriggeredConferenceClientModule`` provides three methods
that need to be implemented by the user: ``setUp()``, ``body()``, and ``tearDown()``.
These methods reflect the basic runtime cycle of a software component: An initialization
phase, followed by a time-triggered execution of an algorithm implemented in the
method ``body()``, before the cycle ends with a call to ``tearDown()`` intended to
clean up any acquired resources.

In addition, this class uses a private and unimplemented copy constructor and
assignment operator so that the compiler can warn if an object of this class is
unintentionally copied or assigned.

The accompanying implementation for this header file is provided in the following.

TimeTriggerExample.cpp:

.. code-block:: c++

    #include <iostream>

    #include "TimeTriggerExample.h"

    using namespace std;

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace core::base;

    TimeTriggerExample::TimeTriggerExample(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "TimeTriggerExample")
        {}

    TimeTriggerExample::~TimeTriggerExample() {}

    void TimeTriggerExample::setUp() {
        cout << "This method is called before the component's body is executed." << endl;
    }

    void TimeTriggerExample::tearDown() {
        cout << "This method is called after the program flow returns from the component's body." << endl;
    }

    ModuleState::MODULE_EXITCODE TimeTriggerExample::body() {
        cout << "Hello OpenDaVINCI World!" << endl;

        return ModuleState::OKAY;
    }

    int32_t main(int32_t argc, char **argv) {
        TimeTriggerExample tte(argc, argv);

        return tte.runModule();
    }

Firstly, the constructor is implemented, delegating any commandline arguments to the
constructor of the class ``TimeTriggeredConferenceClientModule`` to obey the design
principle:

**Design Principle "Single-Point-of-Truth - SPoT": Favor a centrally maintained
configuration over distributed and undocumented commandline parameters**

The third parameter to the constructor of ``TimeTriggeredConferenceClientModule``
is the name of this module, which is used structure the centrally maintained
configuration file.

The implementation of the methods ``setUp()`` and ``tearDown()`` simply contain
explanatory text. They are meant to be used to acquire system resources or to
open peripheral components like cameras or sensors.

The main method ``body()`` is meant to be used for the implementation of the main
data processing algorithm. In this example, it simply prints an explanatory message.
The main method returns the return code 0 encoded as ``ModuleState::OKAY``.

The main function is simply instantiating an object of the class ``TimeTriggerExample``
and runs it by calling the method ``runModule()`` that is provided from its
super-classes.

You can compile and link the example::

   $ g++ -I /usr/include/opendavinci -c TimeTriggerExample.cpp -o TimeTriggerExample.o
   $ g++ -o timetriggerexample TimeTriggerExample.o -lopendavinci -lpthread

To test the program, we need to run the software component life-cycle management
tool ``odsupercomponent``; details for that tool are provided in its accompanying
manual page (man odsupercomponent). To use this tool it is required to provide a
configuration file. As the aforementioned example application does not use any
configuration data, we simply create an empty file::

   $ touch configuration

If OpenDaVINCI is used on a Linux host **without** a network connection, the local
loopback device ``lo`` needs to be configured to allow UDP multicast sessions
before ``odsupercomponent`` can be started::

   $ sudo ifconfig lo multicast

   $ sudo route add -net 224.0.0.0 netmask 240.0.0.0 dev lo

Next, we can run the life-cycle management application ``odsupercomponent``::

   $ odsupercomponent --cid=111 --configuration=./path/to/configuration

The first parameter specifies a unique container conference session identifier
from within the range [2,254]. Thus, it is possible to host several sessions
on the same host.

Now, you can start the example application providing the same container
conference session identifier::

   $ ./timetriggerexample --cid=111

The application will print the following on the console::

   This method is called before the component's body is executed.
   Hello OpenDaVINCI World!
   This method is called after the program flow returns from the component's body.

If the container conference session identifier is omitted, the following exception
will be thrown::

   terminate called after throwing an instance of 'core::exceptions::InvalidArgumentException'
     what():  InvalidArgumentException: Invalid number of arguments. At least a conference group id (--cid=) needed. at /home/berger/GITHUB/Mini-Smart-Vehicles/sources/OpenDaVINCI-msv/libopendavinci/src/core/base/AbstractCIDModule.cpp: 53
   Aborted

If no ``odsupercomponent`` is running, the application will exit with return code 4.

