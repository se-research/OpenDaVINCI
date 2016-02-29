How to design a time-triggered software component
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

OpenDaVINCI allows the development of distributed software components. These
components can run on the same machine or on different ones using various
types of communication and scheduling. Both are provided transparently to the
user of the OpenDaVINCI middleware.

This example demonstrates how to design a time-triggered software component.
The sources for this example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/timetrigger

"Hello World" example
"""""""""""""""""""""

A time-triggered software component is derived from ``odcore::base::TimeTriggeredConferenceClientModule``,
provided in ``<opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h>``.

TimeTriggerExample.h:

.. code-block:: c++

    #include <opendavinci/odcore/base/TimeTriggeredConferenceClientModule.h>

    class TimeTriggerExample : public odcore::base::module::TimeTriggeredConferenceClientModule {
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

            odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

        private:
            virtual void setUp();

            virtual void tearDown();
    };

The class ``odcore::base::module::TimeTriggeredConferenceClientModule`` provides three methods
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
    using namespace odcore::base::module;

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

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode TimeTriggerExample::body() {
        cout << "Hello OpenDaVINCI World!" << endl;

        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
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
is the name of this module, which is used to structure the centrally maintained
configuration file.

The implementation of the methods ``setUp()`` and ``tearDown()`` simply contain
explanatory text. They are meant to be used to acquire system resources or to
open peripheral components like cameras or sensors.

The main method ``body()`` is meant to be used for the implementation of the main
data processing algorithm. In this example, it simply prints an explanatory message.
The main method returns the return code 0 encoded as ``OKAY``.

The main function is simply instantiating an object of the class ``TimeTriggerExample``
and runs it by calling the method ``runModule()`` that is provided from its
super-classes.

You can compile and link the example::

   $ g++ -std=c++11 -I /usr/include -c TimeTriggerExample.cpp -o TimeTriggerExample.o
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

   $ odsupercomponent --cid=111 --configuration=/path/to/configuration

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

   terminate called after throwing an instance of 'odcore::exceptions::InvalidArgumentException'
     what():  InvalidArgumentException: Invalid number of arguments. At least a conference group id (--cid=) needed. at /home/berger/GITHUB/Mini-Smart-Vehicles/sources/OpenDaVINCI-msv/libopendavinci/src/core/base/AbstractCIDModule.cpp: 53
   Aborted

If no ``odsupercomponent`` is running, the application will exit with return code 4.



Adding configuration parameters
"""""""""""""""""""""""""""""""

The next example demonstrates how to specify and use configuration parameters.
Therefore, the implementation of ``body()`` is changed to firstly print further
information about the runtime configuration and secondly, to access configuration
data.

TimeTriggerExample.cpp:

.. code-block:: c++

    #include <iostream>

    #include "TimeTriggerExample.h"

    using namespace std;

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace odcore::base;

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

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode TimeTriggerExample::body() {
        cout << "Hello OpenDaVINCI World!" << endl;

        cout << "This is my name: " << getName() << endl;
        cout << "This is my execution frequency: " << getFrequency() << endl;
        cout << "This is my identifier: " << getIdentifier() << endl;

        cout << "  " << getKeyValueConfiguration().getValue<string>("timetriggerexample.key1") << endl;
        cout << "  " << getKeyValueConfiguration().getValue<uint32_t>("timetriggerexample.key2") << endl;
        cout << "  " << getKeyValueConfiguration().getValue<float>("timetriggerexample.key3") << endl;
        cout << "  " << getKeyValueConfiguration().getValue<string>("timetriggerexample.key4") << endl;
        cout << "  " << (getKeyValueConfiguration().getValue<bool>("timetriggerexample.key5") == 1) << endl;

        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

    int32_t main(int32_t argc, char **argv) {
        TimeTriggerExample tte(argc, argv);

        return tte.runModule();
    }

The super-classes provide methods to get information about the runtime configuration
of a software component. ``getName()`` simply returns the name as specified to the
constructor ``TimeTriggeredConferenceClientModule``. ``getFrequency()`` returns the
execution frequency for the software component; its value can be adjusted by specifying
the commandline parameter ``--freq=`` to the software component. The last method
``getIdentifier()`` returns a unique identifier that can be specified at commandline
by using the parameter ``--id=`` to distinguish several instances of the same software
component; its use is shown for the configuration parameter ``timetriggerexample.key4``
below.

The configuration file is adjusted as follows as an example::

    # This is an example configuration file.
    timetriggerexample.key1 = value1
    timetriggerexample.key2 = 1234
    timetriggerexample.key3 = 42.32

    timetriggerexample.key4 = Default
    timetriggerexample:1.key4 = ValueForComponent1
    timetriggerexample:2.key4 = ValueForComponent2

    timetriggerexample.key5 = 1

This configuration file is parsed by ``odsupercomponent`` and used to provide
component-dependent subsets from this file. The general format is::

    <application name> . <key> [:<identifier>] = <value>

The application name is used to structure the content of the file; in this example,
``timetriggerexample`` specifies all parameters that are provided from ``odsupercomponent``
to our application. The application itself uses the template method
``getKeyValueConfiguration().getValue<T>(const string &key)`` to retrieve values
provided in the required data type. To access the numerical value for the second
key, the application would access the value as follows:

.. code-block:: c++

    uint32_t value = getKeyValueConfiguration().getValue<uint32_t>("timetriggerexample.key2");

The object handling the application-specific key-value-configuration is case-insensitive
regarding the keys; in any case, the application's name needs to precede a key's name.

In the configuration, a special section can be specified using the name ``global.`` preceding
a set of keys. All keys with this preceding name are provided to all applications and thus,
shared among them.

If the same software component needs to be used with different configuration parameters,
OpenDaVINCI offers the commandline parameter ``--id=`` so that different instances of the
same application can be distinguished in the configuration. In our example, the key named
``timetriggerexample.key4`` provides different values regarding the commandline parameters.
For example, if the application is started as follows::

    $ ./timetriggerexample --cid=111

the following request::

    cout << "  " << getKeyValueConfiguration().getValue<string>("timetriggerexample.key4") << endl;

would return the value ``Default``. If, in contrast, the application is started by specifying
the identifier 1::

    $ ./timetriggerexample --cid=111 --id=2

the request would return the value ``ValueForComponent2``.



Adding time-based algorithm triggering
""""""""""""""""""""""""""""""""""""""

The next example demonstrates how to use frequency-based algorithm execution. Therefore,
the implementation of ``body()`` is changed to add a loop that is intended to be executed
until the module is stopped.

TimeTriggerExample.cpp:

.. code-block:: c++

    #include <iostream>

    #include "TimeTriggerExample.h"

    using namespace std;

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace odcore::base;

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

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode TimeTriggerExample::body() {
        cout << "Hello OpenDaVINCI World!" << endl;

        cout << "This is my name: " << getName() << endl;
        cout << "This is my execution frequency: " << getFrequency() << endl;
        cout << "This is my identifier: " << getIdentifier() << endl;

        cout << "  " << getKeyValueConfiguration().getValue<string>("timetriggerexample.key1") << endl;
        cout << "  " << getKeyValueConfiguration().getValue<uint32_t>("timetriggerexample.key2") << endl;
        cout << "  " << getKeyValueConfiguration().getValue<float>("timetriggerexample.key3") << endl;
        cout << "  " << getKeyValueConfiguration().getValue<string>("timetriggerexample.key4") << endl;
        cout << "  " << (getKeyValueConfiguration().getValue<bool>("timetriggerexample.key5") == 1) << endl;

        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
            cout << "Inside the main processing loop." << endl;
        }

        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

    int32_t main(int32_t argc, char **argv) {
        TimeTriggerExample tte(argc, argv);

        return tte.runModule();
    }

The method ``getModuleStateAndWaitForRemainingTimeInTimeslice()`` is provided from
the super-classes and enforces a specific runtime execution frequency. The frequency
can be specified by the commandline parameter ``--freq=`` in Hertz. For example, running
the program as follows::

    $ ./timetriggerexample --cid=111 --freq=2

would print ``Inside the main processing loop.`` two times per second. Thus, the method
``getModuleStateAndWaitForRemainingTimeInTimeslice()`` calculates how much time from the
current time slice has been consumed (in this case, 500ms would be available per time
slice) from the algorithm in the while-loop body, and would simply sleep for the rest of
the current time slice.

The program can be terminated by pressing Ctrl-C, which would result in setting the
module state to not running, leaving the while-loop body, and calling the method
``tearDown()``. Furthermore, stopping ``odsupercomponent`` would also result in
stopping automatically all dependent software components.



Real-time scheduling
""""""""""""""""""""

The standard Linux kernel can meet soft real-time requirements. For time-critical
algorithms requiring hard real-time, the Linux kernel with the CONFIG_PREEMPT_RT
configuration item enabled can be used. More information is available here:
https://rt.wiki.kernel.org/index.php/RT_PREEMPT_HOWTO.

To run an application with real-time prioritization, it must be linked with the
real-time library ``rt``::

   $ g++ -std=c++11 -I /usr/include -c TimeTriggerExample.cpp -o TimeTriggerExample.o
   $ g++ -o timetriggerexample TimeTriggerExample.o -lopendavinci -lpthread -lrt

On execution, simply specify the parameter ``--realtime=`` from within the range
[1,49] to enable real-time scheduling transparently. In addition, you need to run
the application with superuser privileges to allow the configuration of the correct
scheduling priority as follows::

    $ sudo ./timetriggerexample --cid=111 --freq=10 --realtime=20 --verbose=1

The output of the application would look like::

    Creating multicast UDP receiver at 225.0.0.111:12175.
    Creating multicast UDP receiver at 225.0.0.111:19751.
    (ClientModule) discovering supercomponent...
    (ClientModule) supercomponent found at IP: 10.0.2.15, Port: 19866, managedLevel: 0
    (ClientModule) connecting to supercomponent...
    (DMCP-ConnectionClient) sending configuration request...IP: 10.0.2.15, Port: 19866, managedLevel: 0
    (DMCP-Client) Received Configuration
    timetriggerexample.key1=value1
    timetriggerexample.key2=1234
    timetriggerexample.key3=42.32
    timetriggerexample.key4=Default
    timetriggerexample.key5=1

    (ClientModule) connecting to supercomponent...done - managed level: 0
    This method is called before the component's body is executed.
    Hello OpenDaVINCI World!
    This is my name: TimeTriggerExample
    This is my execution frequency: 10
    This is my identifier: 
      value1
      1234
      42.32
      Default
    Starting next cycle at 1437420074s/101149us.
    Inside the main processing loop.
    Starting next cycle at 1437420074s/201230us.
    Inside the main processing loop.
    Starting next cycle at 1437420074s/301194us.
    Inside the main processing loop.
    Starting next cycle at 1437420074s/400376us.
    Inside the main processing loop.
    Starting next cycle at 1437420074s/501003us.
    Inside the main processing loop.
    Starting next cycle at 1437420074s/601151us.
    Inside the main processing loop.
    Starting next cycle at 1437420074s/700427us.
    Inside the main processing loop.
    Starting next cycle at 1437420074s/800241us.
    Inside the main processing loop.
    Starting next cycle at 1437420074s/900387us.
    Inside the main processing loop.
    Starting next cycle at 1437420075s/209us.
    Inside the main processing loop.
    ...

Please observe that your implementation within the ``body()`` shall not allocate
further memory to avoid unexpected page faults resulting in a risk to miss deadlines.


