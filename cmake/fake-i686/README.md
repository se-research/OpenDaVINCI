## Setting up an i686 fake-cross compiler on Ubuntu 14.04 LTS 64 bit

To compile i686 (32 bit) binaries on a 64 bit, just follow the following instructions::

    $ sudo apt-get install gcc-multilib g++-multilib

Create fake build environment::

    $ mkdir cmake/fake-i686/bin
    $ cat < cmake/fake-i686/bin/i686-linux-gnu-gcc
    #!/bin/bash
    /usr/bin/gcc -m32 "$@"
    EOF
    $ cat < cmake/fake-i686/bin/i686-linux-gnu-g++
    #!/bin/bash
    /usr/bin/g++ -m32 "$@"
    EOF
    $ cat < cmake/fake-i686/bin/i686-linux-gnu-ar
    #!/bin/bash
    /usr/bin/ar "$@"
    EOF
    $ chmod 755 cmake/fake-i686/bin/i686-linux-gnu-*

Create a toolchain file::

    $ cat < i686-Toolchain.cmake
    SET(CMAKE_SYSTEM_NAME Linux)

    # This flag sets further include and library paths in dependent CMakeLists.txt
    SET(i686FAKE YES)

    # Specify the cross compiler.
    SET(CMAKE_C_COMPILER ${CMAKE_SOURCE_DIR}/cmake/fake-i686/bin/i686-linux-gnu-gcc)
    SET(CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/cmake/fake-i686/bin/i686-linux-gnu-g++)
    EOF

Create the cross build environment::

    $ mkdir build.i686
    $ cd build.i686
    $ cmake -DCMAKE_TOOLCHAIN_FILE=../i686-Toolchain.cmake ..

Build the binaries::

    $ PATH=../cmake/fake-i686/bin:$PATH make
