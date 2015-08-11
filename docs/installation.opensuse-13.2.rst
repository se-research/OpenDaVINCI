Compiling OpenDaVINCI on OpenSuSE 13.2
--------------------------------------

Download and install openSuSE 13.2 and install its latest package updates::

   $ sudo zypper refresh
   $ sudo zypper update
  
Install required development packages for OpenDaVINCI sources::

   $ sudo zypper install cmake gcc gcc-c++ git
   
.. Install required development packages for hesperia sources::

   $ sudo zypper install opencv-devel boost-devel freeglut-devel libqt4-devel ant ant-junit qwt-devel
   
.. Install required development packages for host-tools sources::

   $ sudo zypper install libusb-devel
   
Install and configure Oracle's Java according to the following guide http://tutorialforlinux.com/2013/12/12/how-to-install-oracle-java-jdk-7-on-opensuse-13-1-gnome3-3264bit-easy-guide/

.. Add two missing symbolic links::

   $ sudo ln -sf /usr/include/qwt5 /usr/include/qwt-qt4
   $ sudo ln -sf /usr/lib64/libqwt.so /usr/lib64/libqwt-qt4.so

   $ sudo apt-get install ant openjdk-7-jre

.. Install required development packages for DataStructureGenerator sources::

   $sudo zypper install ant
   
Clean up installation::

   $ sudo zypper clean
  
Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Change your source folder and create a build directory::

   $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

   $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build the OpenDaVINCI sources::

   $ make all

Run the tests for OpenDaVINCI::

   $ make test

Install the binaries, libraries, and header files to /usr/local::

   $ make install
