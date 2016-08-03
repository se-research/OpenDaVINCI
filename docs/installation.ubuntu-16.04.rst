Compiling OpenDaVINCI on Ubuntu 16.04
-------------------------------------

Download and install Ubuntu 16.04 and install its latest package updates::

    $ sudo apt-get update
    $ sudo apt-get upgrade
    $ sudo apt-get dist-upgrade

Install development packages for OpenDaVINCI sources::

    $ sudo apt-get install --no-install-recommends build-essential python cmake git

Install development packages for libodsimulation sources::

    $ sudo apt-get install --no-install-recommends libpopt-dev libopencv-dev ant ant-junit openjdk-8-jdk-headless libqt4-dev rpm libboost-dev freeglut3-dev libqwt5-qt4-dev libqt4-opengl-dev

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
