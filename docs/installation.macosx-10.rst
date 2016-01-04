Compiling OpenDaVINCI on MacOSX 10
----------------------------------

Install Xcode: https://developer.apple.com/xcode/downloads/

Install CMake: http://www.cmake.org/download/

Install Java to generate data structures: http://java.com/en/download/

Install Python 2.79: https://www.python.org/downloads/mac-osx/
  
Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Change to your source folder and create a build directory::

   $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

   $ cd build && cmake -D CMAKE_C_COMPILER=/usr/bin/cc -D CMAKE_CXX_COMPILER=/usr/bin/c++ -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build, run the tests, and install the OpenDaVINCI::

   $ make all

