How to dynamically interact and monitor a software component at runtime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

How to dynamically configure a software component at runtime
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

During the development of a software module, it might be needed to dynamically
reconfigure or adjust its behavior at runtime. As software components typically
get their parameters and configuration data supplied by odsupercomponent at
start-up, there is a need for a different way of dynamically passing adjusted
parameters to a software components.

To interactively change parameters for a software modules, the graphical user
interface ``odcockpit`` provides a plugin called ``RuntimeConfiguration``
(please see the screenshot below). This plugin provides a table for key/value
pairs that can be sent as the message ``odcockpit::RuntimeConfiguration`` inside
a ``Container`` to the running software modules. The message
``odcockpit::RuntimeConfiguration`` provides a map of ``std::string`` and ``double``
pairs that can be queried from a software module as shown below:

.. code-block:: c++

    // Try to read interactively updated values from RuntimeConfiguration object sent from odcockpit.
    odcore::data::Container c = getKeyValueDataStore().get(odcockpit::RuntimeConfiguration::ID());
    odcockpit::RuntimeConfiguration rc = c.getData<odcockpit::RuntimeConfiguration>();

    if (rc.containsKey_MapOfParameters("input")) {
        input = rc.getValueForKey_MapOfParameters("input");
    }

The method ``getKeyValueDataStore()`` returns direct access to the most recently
received containers of a specific type. In the example above, the most recently
received container carrying a ``odcockpit::RuntimeConfiguration`` is requested.
Next, the map in ``odcockpit::RuntimeConfiguration`` is queried for a specific
key to obtain its value, which is of type ``double``.

It is also possible to send different ``odcockpit::RuntimeConfiguration``
messages to several software components by starting the plugin several times
and using different values for ``senderStamp`` (cf. the example in the source
code in this folder).


How to monitor values from a software component at runtime
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Next to adjust parameters of a software module at runtime, it might also be
necessary to show or plot values to observe a software component's behavior.
To send values for displaying in ``odcockpit``, a software module can use the
message ``odcockpit::SimplePlot`` as shown below:

.. code-block:: c++
    // Send "debug" values to odcockpit for display or plotting.
    odcockpit::SimplePlot sp;
    sp.putTo_MapOfValues("result", result);
    sp.putTo_MapOfValues("kP", kP);
    sp.putTo_MapOfValues("kI", kI);
    sp.putTo_MapOfValues("kD", kD);
    sp.putTo_MapOfValues("input", input);

    odcore::data::Container c(sp);
    getConference().send(c);

In ``odcockpit``, the plugin ``livefeed`` is listing the entry
``odcockpit::SimplePlot/0``, which can be unfolded and enabled to show the
contained values.

If a plot of the values over time is desired, simply double-clicking on a
field. A new window will open and plot the values of that field over time.
The last 10,000 entries will be kept in a ring-buffer; in addition, the buffered
values can be saved as .csv file for later processing.

.. figure:: https://github.com/se-research/OpenDaVINCI/blob/master/tutorials/simpleplot/Plot.png

