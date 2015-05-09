Compiling OpenDaVINCI on Mageia
===============================

Download and install Mageia and install its latest package updates::

   $ sudo urpmi.update -a
  
Install the required development packages for OpenDaVINCI sources::

   $ sudo urpmi cmake gcc gcc-c++ git 
   
.. Install the required development packages for hesperia sources::

   $ sudo urpmi libqt4-devel lib64freeglut3 lib64freeglut-devel lib64boost-devel opencv-devel
   
.. Install qwt5-qt4 for hesperia sources::

   $ sudo urpmi lib64qwt5-devel
   
.. Add two missing symbolic links::

   $ sudo ln -sf /usr/include/qwt /usr/include/qwt-qt4
   $ sudo ln -sf /usr/lib64/libqwt5-qt4.so /usr/lib64/libqwt-qt4.so
  
.. Install the required development packages for host-tools sources::

   $ sudo urpmi libusb1.0-devel
   
Install Java to generate data structures::

   $ sudo urpmi java-1.7.0-openjdk-devel

.. Install the required development packages for the DataStructureGenerator sources:

   $sudo urpmi java-1.7.0-openjdk-devel ant ant-junit
   
Download the latest OpenDaVINCI sources: http://opendavinci.cse.chalmers.se:8000/www/#download

Change your source folder, create a build directory, and create data structures::

   $ cd OpenDaVINCI && mkdir build && ./generateDataStructures.sh

Use cmake to create the build scripts for your build folder::

   $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build the OpenDaVINCI sources::

   $ make all

Run the tests for OpenDaVINCI::

   $ make test

Install the binaries, libraries, and header files to /usr/local::

   $ make install
