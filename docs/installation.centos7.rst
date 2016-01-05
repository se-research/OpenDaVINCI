Compiling OpenDaVINCI on CentOS7
--------------------------------

Download and install CentOS 7 and install its latest package updates::

    $ sudo yum update
    $ sudo yum upgrade
    $ sudo yum distro-sync
  
Install the required development packages for OpenDaVINCI sources::

    $ sudo yum install cmake gcc gcc-c++ git net-tools
    
Install the required development packages for libodsimulation sources::

    $ sudo yum install freeglut qt4 boost boost-devel qt4-devel freeglut-devel opencv-devel
    
Install qwt5-qt4 for hesperia sources::

    $ sudo yum install wget
    $ wget http://li.nux.ro/download/nux/dextop/el7/x86_64/qwt5-qt4-5.2.2-26.el7.nux.x86_64.rpm
    $ wget http://li.nux.ro/download/nux/dextop/el7/x86_64/qwt5-qt4-devel-5.2.2-26.el7.nux.x86_64.rpm
    $ sudo rpm --install qwt5*.rpm
    
Add two missing symbolic links::

    $ sudo ln -sf /usr/include/qwt5-qt4 /usr/include/qwt-qt4
    $ sudo ln -sf /usr/lib64/libqwt5-qt4.so /usr/lib64/libqwt-qt4.so
  
.. Install the required development packages for host-tools sources::

    $ sudo yum install libusb-devel
    
Install the required development packages for the DataStructureGenerator sources::

    $sudo yum install java-1.8.0-openjdk ant ant-junit
    
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

    $ make all

