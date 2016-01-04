Compiling OpenDaVINCI on Scientific Linux 7
-------------------------------------------

Download and install Scientific Linux 7 and install its latest package updates::

   $ sudo yum update
   $ sudo yum upgrade
   $ sudo yum distro-sync
  
Install the required development packages for OpenDaVINCI sources::

   $ sudo yum install cmake gcc gcc-c++ git
   
.. Install the required development packages for hesperia sources::

   $ sudo yum install freeglut qt4 boost boost-devel qt4-devel freeglut-devel opencv-devel
   
.. Install qwt5-qt4::

   $ sudo yum install bzip2
   $ wget http://downloads.sourceforge.net/project/qwt/qwt/5.2.3/qwt-5.2.3.tar.bz2
   $ tar -xvjf qwt-5.2.3.tar.bz2
   $ sudo ln -sf /usr/bin/qmake-qt4 /usr/bin/qmake
   $ cd qwt-5.2.3 && qmake qwt.pro && make
   $ sudo make install

.. Add two missing symbolic links::

   $ sudo ln -sf /usr/local/qwt-5.2.3/include /usr/include/qwt-qt4
   $ sudo ln -sf /usr/local/qwt-5.2.3/lib/libqwt.so.5.2.3 /usr/include/libqwt-qt4.so

.. Install the required development packages for host-tools sources::

   $ sudo yum install libusb-devel
   
Install Java to generate data structures::

   $sudo yum install java-1.7.0-openjdk

.. Install the required development packages for the DataStructureGenerator sources::

   $sudo yum install java-1.7.0-openjdk ant ant-junit
   
Clean up installation::

   $sudo yum autoremove
   $sudo yum clean all
  
Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Change to your source folder and create a build directory::

   $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

   $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build, run the tests, and install the OpenDaVINCI::

   $ make all

