Compiling OpenDaVINCI on Fedora 22
----------------------------------

Download and install Fedora 22 and install its latest package updates::

   $ sudo dnf update
   $ sudo dnf upgrade
   $ sudo dnf distro-sync
  
Install the required development packages for OpenDaVINCI sources::

   $ sudo dnf install cmake gcc gcc-c++ git
   
.. Install the required development packages for hesperia sources::

   $ sudo dnf install freeglut qt4 boost boost-devel qt4-devel freeglut-devel opencv-devel qwt5-qt4-devel
   
.. Install the required development packages for host-tools sources::

   $ sudo dnf install libusb-devel
   
Install Java to generate data structures::
   
   $ sudo dnf install java-1.8.0-openjdk

.. Install the required development packages for the DataStructureGenerator sources::

   $sudo dnf install java-1.8.0-openjdk ant ant-junit
   
Clean up installation::

   $ sudo dnf autoremove
   $ sudo dnf clean all
  
.. Add two missing symbolic links::

   $sudo ln -sf /usr/include/qwt5-qt4 /usr/include/qwt-qt4
   $sudo ln -sf /usr/lib64/libqwt5-qt4.so /usr/lib64/libqwt-qt4.so
    
Download the latest OpenDaVINCI sources: http://opendavinci.cse.chalmers.se/www/OpenDaVINCI-latest.tar.gz

Change your source folder, create a build directory, and create data structures::

   $ cd OpenDaVINCI && mkdir build && ./generateDataStructures.sh

Use cmake to create the build scripts for your build folder::

   $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build the OpenDaVINCI sources::

   $ make all

Run the tests for OpenDaVINCI::

   $ make test

Install the binaries, libraries, and header files to /usr/local::

   $ make install
