How to read Containers from a .rec file
"""""""""""""""""""""""""""""""""""""""

OpenDaVINCI provides tools to process recordings (.rec, .rec.mem, and .h264
files). The sources for this example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/playcontainers

In order to read ``Containers``, which hold messages that are exchanged among
distributed software components.

PlayContainers.cpp:

.. code-block:: c++

    #include <iostream>

    #include <opendavinci/odcore/base/Lock.h>
    #include <opendavinci/odcore/data/Container.h>
    #include <opendavinci/odcore/io/URL.h>
    #include <opendavinci/odtools/player/Player.h>

    #include <opendavinci/odcore/wrapper/SharedMemory.h>
    #include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>

    #include <opendavinci/generated/odcore/data/SharedPointCloud.h>

    using namespace std;

    int32_t main(int32_t argc, char **argv) {
        if (2 != argc) {
            cerr << "Use with: " << argv[0] << " file.rec" << endl;
            return -1;
        }
        else {
            // Setting file for playback.
            odcore::io::URL url("file://" + string(argv[1]));
            // Size of the memory buffer (should be large enough to hold point clouds for example).
            const uint32_t MEMORY_SEGMENT_SIZE = 3*1024*1024;
            // Number of memory segments.
            const uint32_t NUMBER_OF_SEGMENTS = 3;
            // If AUTO_REWIND is true, the file will be played endlessly.
            const bool AUTO_REWIND = false;
            // For sequential playback, THREADING must be set to false.
            const bool TRHEADING = false;
            // Construct the player.
            odtools::player::Player player(url, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, TRHEADING);

            std::shared_ptr<odcore::wrapper::SharedMemory> spcSharedMemory;

            while (player.hasMoreData()) {
                // Read the next container from file.
                odcore::data::Container c = player.getNextContainerToBeSent();

                cout << "Found Container " << c.getDataType()
                                           << ", sent " << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms()
                                           << ", received " << c.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms()
                                           << ", sample time stamp " << c.getSampleTimeStamp().getYYYYMMDD_HHMMSSms() << endl;

                if (c.getDataType() == odcore::data::SharedPointCloud::ID()) {
                    odcore::data::SharedPointCloud spc = c.getData<odcore::data::SharedPointCloud>();
                    cout << spc.toString() << endl;

                    if (spcSharedMemory.get() != NULL) {
                        // Attach the shared point cloud to the shared memory.
                        spcSharedMemory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(spc.getName());
                    }
                    else {
                        odcore::base::Lock l(spcSharedMemory);
                        // TODO: Do something with the raw data in memory; cf. https://github.com/se-research/OpenDaVINCI/blob/master/odcockpit/src/plugins/environmentviewer/EnvironmentViewerGLWidget.cpp#L489-L558
                    }
                }
            }

        }
    }

To read ``Containers``, your application needs to include
``<opendavinci/odtools/player/Player.h>``.

``Player`` handles the processing of .rec and .rec.mem files; the former simply
contain the dump of any ``Container`` that is received during a recording session.
A ``Container`` is a Protobuf-encoded message prepended with the byte sequence
0x0D 0xA4 0xXX 0xYY 0xZZ; the last three bytes encode the length of the following
Protobuf-encoded message in little-endian encoding. The .rec.mem file contain a
dump of shared memory area at a given point in time as described by the meta
data structures ``SharedImage`` or ``SharedPointCloud``. These data structures
do not contain any useful payload but describe the actual payload that is stored
in a shared memory area.

In the example code, the instance of class ``Player`` is looping once through
all entries in a given .rec file and .rec.mem file. If the next ``Container``
to be handled is one of the meta-data structures, the example code is testing
for ``SharedPointCloud`` data and attaching to the shared memory area where
the payload data is available.

You can compile and link the example::

   g++ -std=c++11 -I /usr/include -c PlayContainers.cpp -o PlayContainers.o
   g++ -o playcontainers PlayContainers.o -lopendavinci -lpthread

To test the program, simply run it as follows::

    $ ./playcontainers MyFile.rec

