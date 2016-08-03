Compiling OpenDaVINCI on Linux Mint 17 (32bit and 64bit)
--------------------------------------------------------

Download and install Linux Mint 17 and install its latest package updates::

    $ sudo apt-get update
    $ sudo apt-get upgrade
    $ sudo apt-get dist-upgrade

Install development packages for OpenDaVINCI sources::

    $ sudo apt-get install build-essential cmake git

Install the required development packages for libodsimulation sources::

    $ sudo apt-get install libcv-dev libhighgui-dev freeglut3 libqt4-dev libqwt5-qt4-dev libqwt5-qt4 libqt4-opengl-dev freeglut3-dev qt4-dev-tools libboost-dev libopencv-photo-dev libopencv-contrib-dev

.. Install development packages for host-tools sources::

    $ sudo apt-get install libusb-dev

Install development packages for DataStructureGenerator sources::

    $ sudo apt-get install ant openjdk-7-jdk

Clean up installation::

    $ sudo apt-get clean
    $ sudo apt-get autoremove

Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Create an installation folder::

    $ sudo mkdir -p /opt/od && sudo chown $USER:$USER /opt/od

Change to your source folder and create a build directory::

    $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

    $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/opt/od ..

Build, run the tests, and install the OpenDaVINCI::

    $ make
