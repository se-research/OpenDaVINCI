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

Create an installation folder::

    $ sudo mkdir -p /opt/od && sudo chown $USER:$USER /opt/od

Change to your source folder and create a build directory::

    $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

    $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/opt/od ..

Build, run the tests, and install the OpenDaVINCI::

    $ make
