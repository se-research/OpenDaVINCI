Compiling OpenDaVINCI on Ubuntu 15.04
-------------------------------------

Download and install Ubuntu 15.04 and install its latest package updates::

    $ sudo apt-get update
    $ sudo apt-get upgrade
    $ sudo apt-get dist-upgrade

Install development packages for OpenDaVINCI sources::

    $ sudo apt-get install build-essential cmake git

Install development packages for libodsimulation sources::

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

Change to your source folder and create a build directory::

    $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

    $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build, run the tests, and install the OpenDaVINCI::

    $ sudo make all
    
Note that sudo is used here because installing software to system-wide directories (e.g., /usr/local) requires superuser (root) privileges. If OpenDaVINCI is installed in a different directory, e.g., /opt/od, then there is no need to use sudo. Instead, write permission should be given::

    $ sudo chown $USER:$USER /opt/od
