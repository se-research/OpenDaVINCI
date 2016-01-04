Compiling OpenDaVINCI on Mageia
-------------------------------

Download and install Mageia and install its latest package updates::

   $ sudo urpmi.update -a
  
Install the required development packages for OpenDaVINCI sources::

   $ sudo urpmi cmake gcc gcc-c++ git 
   
.. Install the required development packages for hesperia sources::

   $ sudo urpmi libqt4-devel lib64freeglut3 lib64freeglut-devel lib64boost-devel opencv-devel
   
.. Install qwt5-qt4 for hesperia sources::

   $ sudo urpmi lib64qwt5-devel
   
.. Add two missing symbolic links::

   $ sudo ln -sf /usr/include/qwt /usr/include/qwt-qt4
   $ sudo ln -sf /usr/lib64/libqwt5-qt4.so /usr/lib64/libqwt-qt4.so
  
.. Install the required development packages for host-tools sources::

   $ sudo urpmi libusb1.0-devel
   
Install Java to generate data structures::

   $ sudo urpmi java-1.7.0-openjdk-devel

.. Install the required development packages for the DataStructureGenerator sources:

   $sudo urpmi java-1.7.0-openjdk-devel ant ant-junit
   
Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Change to your source folder and create a build directory::

   $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

   $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build, run the tests, and install the OpenDaVINCI::

   $ make all

