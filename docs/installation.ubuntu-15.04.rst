Compiling OpenDaVINCI on Ubuntu 15.04
=====================================

Download and install Ubuntu 15.04 and install its latest package updates::

   $ sudo apt-get update
   $ sudo apt-get upgrade
   $ sudo apt-get dist-upgrade

Install development packages for OpenDaVINCI sources::

   $ sudo apt-get install build-essential cmake git

.. Install development packages for hesperia sources::

   $ sudo apt-get install libcv-dev libhighgui-dev freeglut3 libqt4-dev libqwt5-qt4-dev libqwt5-qt4 libqt4-opengl-dev freeglut3-dev qt4-dev-tools libboost-dev libopencv-photo-dev libopencv-contrib-dev

.. Install development packages for host-tools sources::

   $ sudo apt-get install libusb-dev

.. Install development packages for DataStructureGenerator sources::

   $ sudo apt-get install ant openjdk-7-jdk

Install Java to generate data structures::

   $ sudo apt-get install ant openjdk-7-jre

Clean up installation::

   $ sudo apt-get clean
   $ sudo apt-get autoremove

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
