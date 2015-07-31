How to design a data-triggered software component
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

OpenDaVINCI allows the development of distributed software components. These
components can run on the same machine or on different ones using various
types of communication and scheduling. Both is provided transparently to the
user of the OpenDaVINCI middleware.

This example demonstrates how to design a data-triggered software component.
The sources for this example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/datatrigger

The example consists of two components: ``TimeTriggeredSender`` that is supposed
to send regularly data updates and ``DataTriggeredReceiver``, which will be
notified by any data sent via network. For further explanations about a
time-triggered modules, please see: https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/timetrigger


Time-triggered sender
"""""""""""""""""""""

A time-triggered software component is derived from ``core::base::TimeTriggeredConferenceClientModule``,
provided in ``<core/base/module/TimeTriggeredConferenceClientModule.h>`` to
realize the sending functionality.

TimeTriggeredSender.h:

.. code-block:: c++

    #include <core/base/module/TimeTriggeredConferenceClientModule.h>

    class TimeTriggeredSender : public core::base::module::TimeTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            TimeTriggeredSender(const TimeTriggeredSender &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            TimeTriggeredSender& operator=(const TimeTriggeredSender &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            TimeTriggeredSender(const int32_t &argc, char **argv);

            virtual ~TimeTriggeredSender();

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

        private:
            virtual void setUp();

            virtual void tearDown();
    };

The class ``core::base::module::TimeTriggeredConferenceClientModule`` provides three methods
that need to be implemented by the user: ``setUp()``, ``body()``, and ``tearDown()``.
These methods reflect the basic runtime cycle of a software component: An initialization
phase, followed by a time-triggered execution of an algorithm implemented in the
method ``body()``, before the cycle ends with a call to ``tearDown()`` intended to
clean up any acquired resources.

In addition, this class uses a private and unimplemented copy constructor and
assignment operator so that the compiler can warn if an object of this class is
unintentionally copied or assigned.

The accompanying implementation for this header file is provided in the following.

TimeTriggeredSender.cpp:

.. code-block:: c++

    #include <iostream>

    #include "core/data/TimeStamp.h"

    #include "TimeTriggeredSender.h"

    using namespace std;

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace core::base::module;
    using namespace core::data;

    TimeTriggeredSender::TimeTriggeredSender(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "TimeTriggeredSender")
	    {}

    TimeTriggeredSender::~TimeTriggeredSender() {}

    void TimeTriggeredSender::setUp() {
        cout << "This method is called before the component's body is executed." << endl;
    }

    void TimeTriggeredSender::tearDown() {
        cout << "This method is called after the program flow returns from the component's body." << endl;
    }

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode TimeTriggeredSender::body() {
        uint32_t i = 0;
	    while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
            cout << "Sending " << i << "-th time stamp data...";
            TimeStamp ts(i, 2*i++);
            Container c(Container::TIMESTAMP, ts);
            getConference().send(c);
            cout << "done." << endl;
        }

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

    int32_t main(int32_t argc, char **argv) {
        TimeTriggeredSender tts(argc, argv);

        return tts.runModule();
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
data processing algorithm. The main while-loop is executed based on the specified
runtime frequency of the software component. The send data with OpenDaVINCI, it
must be packed into a ``Container`` that adds additional information like
information about the contained payload, the sent time point when the container
left the sending software computer (for instance a sending computer), and the
time point, when the container was received at the other end (e.g. another computer).

As an example, we simply send an instance of the class ``TimeStamp`` where we
pass some example data to its constructor. Next, we create a ``Container`` by
specifying the containing type and the object to be sent.

To finally send data with OpenDaVINCI, we use the method ``getConference().send(Container &c)``
provided for any class deriving from ``TimeTriggeredConferenceClientModule``.
The main communication principle provided with OpenDaVINCI is publish/subscribe:
https://en.wikipedia.org/wiki/Publish%E2%80%93subscribe_pattern. Depending on
the command line parameters passed to ``odsupercomponent``, the concrete
communication is realized either as packets sent via UDP multicast, or via
``odsupercomponent`` acting as a central communication hub (this functionality
is for instance necessary for distributed simulations). For the user application,
the concrete pattern in use is transparent and our data is simply handed over
to OpenDaVINCI to conduct the necessary steps by calling ``getConference().send(c)``.
The main method returns the return code 0 encoded as ``OKAY``.

The main function is simply instantiating an object of the class ``TimeTriggerExample``
and runs it by calling the method ``runModule()`` that is provided from its
super-classes.

You can compile and link the example::

   $ g++ -I /usr/include/opendavinci -c TimeTriggeredSender.cpp -o TimeTriggeredSender.o
   $ g++ -o timetriggeredsender TimeTriggeredSender.o -lopendavinci -lpthread



Data-triggered receiver
"""""""""""""""""""""""

To receive the sent data, a data-triggered software component is derived from
``core::base::DataTriggeredConferenceClientModule``, provided in
``<core/base/module/DataTriggeredConferenceClientModule.h>`` to realize the
receiving functionality.

DataTriggeredSender.h:

.. code-block:: c++

    #include <core/base/module/DataTriggeredConferenceClientModule.h>

    class DataTriggeredReceiver : public core::base::module::DataTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            DataTriggeredReceiver(const DataTriggeredReceiver &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            DataTriggeredReceiver& operator=(const DataTriggeredReceiver &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            DataTriggeredReceiver(const int32_t &argc, char **argv);

            virtual ~DataTriggeredReceiver();

            virtual void nextContainer(core::data::Container &c);

        private:
            virtual void setUp();

            virtual void tearDown();
    };

The class ``core::base::module::DataTriggeredConferenceClientModule`` provides three methods
that need to be implemented by the user: ``setUp()``, ``body()``, and ``nextContainer(core::data::Container &c)``.
These methods reflect the basic runtime cycle of a software component: An initialization
phase, followed by a data-triggered execution of an algorithm implemented in the
method ``nextContainer()``, before the cycle ends with a call to ``tearDown()`` intended to
clean up any acquired resources.

In addition, this class uses a private and unimplemented copy constructor and
assignment operator so that the compiler can warn if an object of this class is
unintentionally copied or assigned.

The accompanying implementation for this header file is provided in the following.

DataTriggeredSender.cpp:

.. code-block:: c++

    #include <iostream>

    #include "DataTriggeredReceiver.h"
    #include "core/data/TimeStamp.h"

    using namespace std;

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace core::base::module;
    using namespace core::data;

    DataTriggeredReceiver::DataTriggeredReceiver(const int32_t &argc, char **argv) :
        DataTriggeredConferenceClientModule(argc, argv, "DataTriggeredReceiver")
	    {}

    DataTriggeredReceiver::~DataTriggeredReceiver() {}

    void DataTriggeredReceiver::setUp() {
        cout << "This method is called before the component's body is executed." << endl;
    }

    void DataTriggeredReceiver::tearDown() {
        cout << "This method is called after the program flow returns from the component's body." << endl;
    }

    void DataTriggeredReceiver::nextContainer(Container &c) {
        cout << "Received container of type " << c.getDataType() <<
                                  " sent at " << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms() <<
                              " received at " << c.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms() << endl;

        if (c.getDataType() == Container::TIMESTAMP) {
            TimeStamp ts = c.getData<TimeStamp>();
            cout << "Received the following time stamp: " << ts.toString() << endl;
        }
    }

    int32_t main(int32_t argc, char **argv) {
        DataTriggeredReceiver dtr(argc, argv);

        return dtr.runModule();
    }

Firstly, the constructor is implemented, delegating any commandline arguments to the
constructor of the class ``DataTriggeredConferenceClientModule`` to obey the design
principle:

**Design Principle "Single-Point-of-Truth - SPoT": Favor a centrally maintained
configuration over distributed and undocumented commandline parameters**

The third parameter to the constructor of ``DataTriggeredConferenceClientModule``
is the name of this module, which is used structure the centrally maintained
configuration file.

The implementation of the methods ``setUp()`` and ``tearDown()`` simply contain
explanatory text. They are meant to be used to acquire system resources or to
open peripheral components like cameras or sensors.

The data-triggered method ``nextContainer(core::data::Container &c)`` is called
whenever a new ``Container`` is received. The first lines simply print some
meta-information about received container like contained data type as an
enum-encoded number, time stamp when the container left the sending software
component, and the time stamp when it was received at our end. As we are interested
in data of type ``Container::TIMESTAMP``, we are checking for that type.

Once we have received the data of interest, the contents of the container is
unpacked by using the template method ``Container::getData<T>()`` where we
specify with T the desired type. In our case, we access its content by specifying
the type ``TimeStamp``. Finally, the values of ``TimeStamp`` are printed to
stdout by using the data structure's method ``toString()``.

The main function is simply instantiating an object of the class ``TimeTriggerExample``
and runs it by calling the method ``runModule()`` that is provided from its
super-classes.

You can compile and link the example::

   $ g++ -I /usr/include/opendavinci -c DataTriggeredReceiver.cpp -o DataTriggeredReceiver.o
   $ g++ -o datatriggeredreceiver DataTriggeredReceiver.o -lopendavinci -lpthread



Running the example program
"""""""""""""""""""""""""""

To test the programs, we need to run the software component life-cycle management
tool ``odsupercomponent``; details for that tool are provided in its accompanying
manual page (man odsupercomponent). To use this tool it is required to provide a
configuration file. As the aforementioned example applications do not use any
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

Now, you can start the data triggered receiver application providing the same
container conference session identifier::

   $ ./datatriggeredreceiver --cid=111

The application will start to print something similar to the following on the console::

    Received container of type 8 sent at 2015-07-31 13:53:23.847738 received at 2015-07-31 13:53:23.848420
    Received container of type 8 sent at 2015-07-31 13:53:25.849773 received at 2015-07-31 13:53:25.850541
    Received container of type 8 sent at 2015-07-31 13:53:27.851393 received at 2015-07-31 13:53:27.851924
    Received container of type 8 sent at 2015-07-31 13:53:29.852550 received at 2015-07-31 13:53:29.853406
    Received container of type 8 sent at 2015-07-31 13:53:31.854014 received at 2015-07-31 13:53:31.854474
    ...

Containers of this type carry information about ``ModuleStatistics`` that are used and
evaluated by ``odsupercomponent``.

Next, we start the time triggered sender providing the same container conference
session identifier::

   $ ./timetriggeredsender --cid=111

The application will start to print the following on the console::

    Sending 0-th time stamp data...done.
    Sending 1-th time stamp data...done.
    Sending 2-th time stamp data...done.
    Sending 3-th time stamp data...done.
    ...

The data-triggered application in turn will print the following on the console::

    ...
    Received container of type 12 sent at 2015-07-31 13:53:33.68143 received at 2015-07-31 13:53:33.68858
    Received the following time stamp: 1s/0us.
    Received container of type 8 sent at 2015-07-31 13:53:33.855026 received at 2015-07-31 13:53:33.855697
    Received container of type 12 sent at 2015-07-31 13:53:34.67304 received at 2015-07-31 13:53:34.67797
    Received the following time stamp: 2s/2us.
    Received container of type 12 sent at 2015-07-31 13:53:35.68291 received at 2015-07-31 13:53:35.69396
    Received the following time stamp: 3s/4us.
    Received container of type 8 sent at 2015-07-31 13:53:35.856238 received at 2015-07-31 13:53:35.856762
    Received container of type 12 sent at 2015-07-31 13:53:36.68194 received at 2015-07-31 13:53:36.69174
    Received the following time stamp: 4s/6us.
    Received container of type 12 sent at 2015-07-31 13:53:37.67420 received at 2015-07-31 13:53:37.68540
    Received the following time stamp: 5s/8us.
    Received container of type 8 sent at 2015-07-31 13:53:37.858281 received at 2015-07-31 13:53:37.858938
    Received container of type 12 sent at 2015-07-31 13:53:38.67384 received at 2015-07-31 13:53:38.67959
    Received the following time stamp: 6s/10us.
    Received container of type 12 sent at 2015-07-31 13:53:39.67400 received at 2015-07-31 13:53:39.68423
    Received the following time stamp: 7s/12us.
    ...

If the container conference session identifier is omitted, the following exception
will be thrown::

   terminate called after throwing an instance of 'core::exceptions::InvalidArgumentException'
     what():  InvalidArgumentException: Invalid number of arguments. At least a conference group id (--cid=) needed. at /home/berger/GITHUB/Mini-Smart-Vehicles/sources/OpenDaVINCI/libopendavinci/src/core/base/module/AbstractCIDModule.cpp: 53
   Aborted

If no ``odsupercomponent`` is running, the application will exit with return code 4.

