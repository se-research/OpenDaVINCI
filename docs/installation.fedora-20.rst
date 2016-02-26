Compiling OpenDaVINCI on Fedora 20
----------------------------------

Download and install Fedora 20 and install its latest package updates::

    $ sudo yum update
    $ sudo yum upgrade
    $ sudo yum distro-sync
  
Install the required development packages for OpenDaVINCI sources::

    $ sudo yum install cmake gcc gcc-c++ git
    
Install the required development packages for libodsimulation sources::

    $ sudo yum install freeglut qt4 boost boost-devel qt4-devel freeglut-devel opencv-devel qwt5-qt4-devel
    
.. Install the required development packages for host-tools sources::

    $sudo yum install libusb-devel
    
Install the required development packages for the DataStructureGenerator sources::

    $ sudo yum install java-1.7.0-openjdk ant
    
Clean up installation::

    $ sudo yum autoremove
    $ sudo yum clean all
  
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
