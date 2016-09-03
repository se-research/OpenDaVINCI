Compiling OpenDaVINCI on Fedora 22
----------------------------------

Download and install Fedora 22 and install its latest package updates::

    $ sudo yum -y update
    $ sudo yum -y upgrade
  
Install OpenDaVINCI dependencies::

    $ sudo yum -y install ant ant-junit automake boost-devel cmake freeglut-devel gcc gcc-c++ git python2 iproute kernel-devel make opencv-devel psmisc qt4-devel qwt5-qt4-devel tar wget 
    
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
