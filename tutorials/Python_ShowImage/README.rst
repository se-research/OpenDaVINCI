How to show live Containers and Images with Python
""""""""""""""""""""""""""""""""""""""""""""""""""

OpenDaVINCI's data structure generator is emitting Protobuf-compatible
message descriptors. In this folder, an example is provided to demonstrate
how to connect to a running CID session with Python and process containers
using the Python/Protobuf interface. As Linux distribution, Ubuntu 16.04 is used.

First, install the Protobuf compiler::

    $ sudo apt-get install --no-install-recommends protobuf-compiler

Next, simply run make to generate the Protobuf data structures and to
execute the Python scipt::

    $ make

