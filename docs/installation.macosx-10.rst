Compiling OpenDaVINCI on MacOSX 10
----------------------------------

Install Xcode: https://developer.apple.com/xcode/downloads/

Install CMake: http://www.cmake.org/download/

Install Java to generate data structures: http://java.com/en/download/

Install Python 2.79: https://www.python.org/downloads/mac-osx/
  
Download the latest OpenDaVINCI sources: http://opendavinci.cse.chalmers.se/www/OpenDaVINCI-latest.tar.gz

Change your source folder, create a build directory, and create data structures::

   $ cd OpenDaVINCI && mkdir build && ./generateDataStructures.sh

Use cmake to create the build scripts for your build folder::

   $ cd build && cmake -D CMAKE_C_COMPILER=/usr/bin/cc -D CMAKE_CXX_COMPILER=/usr/bin/c++ -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build the OpenDaVINCI sources::

   $ make all

Run the tests for OpenDaVINCI::

   $ make test

Install the binaries, libraries, and header files to /usr/local::

   $ make install
