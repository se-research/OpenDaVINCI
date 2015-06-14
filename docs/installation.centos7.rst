Compiling OpenDaVINCI on CentOS7
--------------------------------

Download and install CentOS 7 and install its latest package updates::

   $ sudo yum update
   $ sudo yum upgrade
   $ sudo yum distro-sync
  
Install the required development packages for OpenDaVINCI sources::

   $ sudo yum install cmake gcc gcc-c++ git net-tools
   
.. Install the required development packages for hesperia sources::

   $ sudo yum install freeglut qt4 boost boost-devel qt4-devel freeglut-devel opencv-devel
   
.. Install qwt5-qt4 for hesperia sources::

   $ sudo yum install wget
   $ wget http://li.nux.ro/download/nux/dextop/el7/x86_64/qwt5-qt4-5.2.2-26.el7.nux.x86_64.rpm
   $ wget http://li.nux.ro/download/nux/dextop/el7/x86_64/qwt5-qt4-devel-5.2.2-26.el7.nux.x86_64.rpm
   $ sudo rpm --install qwt5*.rpm
   
.. Add two missing symbolic links::

   $ sudo ln -sf /usr/include/qwt5-qt4 /usr/include/qwt-qt4
   $ sudo ln -sf /usr/lib64/libqwt5-qt4.so /usr/lib64/libqwt-qt4.so
  
.. Install the required development packages for host-tools sources::

   $ sudo yum install libusb-devel
   
Install Java to generate data structures::

   $ sudo yum install java-1.8.0-openjdk

.. Install the required development packages for the DataStructureGenerator sources::

   $sudo yum install java-1.8.0-openjdk ant ant-junit
   
Clean up installation::

   $ sudo yum autoremove
   $ sudo yum clean all

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
  
