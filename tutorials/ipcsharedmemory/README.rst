How to exchange data between processes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

OpenDaVINCI has a built-in interprocess communication engine realized with
shared memory and semaphores. The sources for this example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/ipcsharedmemory

In order to use shared memory to exchange data between your processes on a
local machine, you will find a simple example below. To share data between
two processes on the same machine, the example is split into a producer and a
consumer example. The former will create the shared memory segment, while the
latter is attaching to the shared memory segment to consume the data.

ipcsharedmemoryproducer.cpp:

.. code-block:: c++

    #include <stdint.h>
    #include <iostream>
    #include <string>
    #include <core/SharedPointer.h>
    #include <core/base/Thread.h>
    #include <core/wrapper/SharedMemory.h>
    #include <core/wrapper/SharedMemoryFactory.h>

    using namespace std;

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace core;
    using namespace core::wrapper;

    int32_t main(int32_t argc, char **argv) {
        const string NAME = "MySharedMemory";
        const uint32_t SIZE = 26;

        // We are using OpenDaVINCI's SharedPointer to automatically
        // release any acquired resources.
        try {
            SharedPointer<SharedMemory> sharedMemory(SharedMemoryFactory::createSharedMemory(NAME, SIZE));

            if (sharedMemory->isValid()) {
                uint32_t counter = 20;
                while (counter-- > 0) {
                    // Lock shared memory.
                    sharedMemory->lock();
                        char *p = static_cast<char*>(sharedMemory->getSharedMemory());
                        for (uint32_t i = 0; i < sharedMemory->getSize(); i++) {
                            char c = (char) (65 + ((i+counter)%26));
                            p[i] = c;
                        }
                    // Unlock memory.
                    sharedMemory->unlock();

                    // Sleep some time.
                    const uint32_t ONE_SECOND = 1000 * 1000;
                    core::base::Thread::usleepFor(ONE_SECOND);
                }
            }
        }
        catch(string &exception) {
            cerr << "Shared memory could not created: " << exception << endl;
        }
    }

The producer process needs to include ``<core/wrapper/SharedMemory.h>`` and
``<core/wrapper/SharedMemoryFactory.h>`` that encapsulate the platform-specific
implementations.

``SharedMemoryFactory`` provides a static method called ``createSharedMemory`` that
allows you to create a shared memory segment that is automatically protected with
a system semaphore. Therefore, a name and the size in bytes for the shared memory
segment need to be provided.

``SharedMemoryFactory`` returns the ``SharedMemory`` automatically wrapped into
a ``SharedPointer`` that takes care of releasing system resources when exiting
your program.

Once you have the ``SharedPointer`` at hand, you can check its validity by calling
``bool isValid()``. If the shared memory is valid, you can request exclusive access
to it by calling ``void lock()``, which blocks until the shared memory is available.
As soon as it gets available, you can access it by calling ``getSharedMemory()``
returning a ``char*``.

You can compile and link the producer example as follows::

   g++ -I /usr/include/opendavinci -c ipcsharedmemoryproducer.cpp -o ipcsharedmemoryproducer.o
   g++ -o ipcsharedmemoryproducer ipcsharedmemoryproducer.o -lopendavinci -lpthread

ipcsharedmemoryconsumer.cpp:

.. code-block:: c++

    #include <stdint.h>
    #include <iostream>
    #include <string>
    #include <core/SharedPointer.h>
    #include <core/base/Thread.h>
    #include <core/wrapper/SharedMemory.h>
    #include <core/wrapper/SharedMemoryFactory.h>

    using namespace std;

    // We add some of OpenDaVINCI's namespaces for the sake of readability.
    using namespace core;
    using namespace core::wrapper;

    int32_t main(int32_t argc, char **argv) {
        const string NAME = "MySharedMemory";

        // We are using OpenDaVINCI's SharedPointer to automatically
        // release any acquired resources.
        try {
            SharedPointer<SharedMemory> sharedMemory(SharedMemoryFactory::attachToSharedMemory(NAME));

            if (sharedMemory->isValid()) {
                uint32_t counter = 10;
                while (counter-- > 0) {
                    // Lock shared memory.
                    sharedMemory->lock();
                        char *p = static_cast<char*>(sharedMemory->getSharedMemory());
                        string s(p, sharedMemory->getSize());
                    // Unlock memory.
                    sharedMemory->unlock();

                    cout << "Content of shared memory: '" << s << "'" << endl;

                    // Sleep some time.
                    const uint32_t ONE_SECOND = 1000 * 1000;
                    core::base::Thread::usleepFor(0.5 * ONE_SECOND);
                }
            }
        }
        catch(string &exception) {
            cerr << "Shared memory could not created: " << exception << endl;
        }
    }

The consumer process needs to include ``<core/wrapper/SharedMemory.h>`` and
``<core/wrapper/SharedMemoryFactory.h>`` that encapsulate the platform-specific
implementations as well.

On the consumer side, ``SharedMemoryFactory`` provides a static method called
``attachToSharedMemory`` that allows you to attach to an existing shared memory
segment. Thus, only the name needs to be provided as OpenDaVINCI automatically
encodes the the size of the shared memory additionally into the shared memory
segment.

``SharedMemoryFactory`` returns the ``SharedMemory`` automatically wrapped into
a ``SharedPointer`` that takes care of releasing system resources when exiting
your program.

Once you have the ``SharedPointer`` at hand, you can check its validity by calling
``bool isValid()``. If the shared memory is valid, you can request exclusive access
to it by calling ``void lock()``, which blocks until the shared memory is available.
As soon as it gets available, you can access it by calling ``getSharedMemory()``
returning a ``char*``.

You can compile and link the consumer example as follows::

   g++ -I /usr/include/opendavinci -c ipcsharedmemoryconsumer.cpp -o ipcsharedmemoryconsumer.o
   g++ -o ipcsharedmemoryconsumer ipcsharedmemoryconsumer.o -lopendavinci -lpthread

To test the program, simply run the producer::

    $ ./ipcsharedmemoryproducer

followed by running the consumer that is printing to the console::

    $ ./ipcsharedmemoryconsumer
    Content of shared memory: 'QRSTUVWXYZABCDEFGHIJKLMNOP'
    Content of shared memory: 'PQRSTUVWXYZABCDEFGHIJKLMNO'
    Content of shared memory: 'PQRSTUVWXYZABCDEFGHIJKLMNO'
    Content of shared memory: 'OPQRSTUVWXYZABCDEFGHIJKLMN'
    Content of shared memory: 'OPQRSTUVWXYZABCDEFGHIJKLMN'
    Content of shared memory: 'NOPQRSTUVWXYZABCDEFGHIJKLM'
    Content of shared memory: 'NOPQRSTUVWXYZABCDEFGHIJKLM'
    Content of shared memory: 'MNOPQRSTUVWXYZABCDEFGHIJKL'
    Content of shared memory: 'MNOPQRSTUVWXYZABCDEFGHIJKL'
    Content of shared memory: 'LMNOPQRSTUVWXYZABCDEFGHIJK'

You can inspect the system resources when running ``ipcsharedmemoryconsumer``::

    $ ipcs 
    ------ Shared Memory Segments --------
    key        shmid      owner      perms      bytes      nattch     status
    ...
    0x0000006a 1900559    odv        600        30         1                       

    ------ Semaphore Arrays --------
    key        semid      owner      perms      nsems     

    ------ Message Queues --------
    key        msqid      owner      perms      used-bytes   messages    


