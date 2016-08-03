Compiling OpenDaVINCI on Fedora 21
----------------------------------

Download and install Fedora 21 and install its latest package updates::

    $ sudo yum update
    $ sudo yum upgrade
    $ sudo yum distro-sync
  
Install the required development packages for OpenDaVINCI sources::

    $ sudo yum install cmake gcc gcc-c++ git
    
Install the required development packages for libodsimulation sources::

    $ sudo yum install freeglut qt4 boost boost-devel qt4-devel freeglut-devel opencv-devel qwt5-qt4-devel
    
.. Install the required development packages for host-tools sources::

    $ sudo yum install libusb-devel
    
Install the required development packages for the DataStructureGenerator sources::

    $ sudo yum install java-1.8.0-openjdk ant ant-junit
    
Clean up installation::

    $ sudo yum autoremove
    $ sudo yum clean all

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
