Compiling OpenDaVINCI on OpenSuSE 13.2
--------------------------------------

Download and install openSuSE 13.2 and install its latest package updates::

    $ sudo zypper refresh
    $ sudo zypper update
  
Install required development packages for OpenDaVINCI sources::

    $ sudo zypper install cmake gcc gcc-c++ git
    
Install required development packages for libodsimulation sources::

    $ sudo zypper install opencv-devel boost-devel freeglut-devel libqt4-devel ant ant-junit qwt-devel
    
.. Install required development packages for host-tools sources::

    $ sudo zypper install libusb-devel
    
Install and configure Oracle's Java according to the following guide http://tutorialforlinux.com/2013/12/12/how-to-install-oracle-java-jdk-7-on-opensuse-13-1-gnome3-3264bit-easy-guide/ ::

    $ sudo apt-get install ant openjdk-7-jdk

Install required development packages for DataStructureGenerator sources::

    $sudo zypper install ant
    
Clean up installation::

    $ sudo zypper clean
  
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
