Compiling OpenDaVINCI on Minix3
-------------------------------

Download and install Minix3 and install its latest package updates::

    # pkgin update

Install development packages for OpenDaVINCI sources::

    # pkgin install python27
    # pkgin install cmake
    # pkgin install git-base
    # pkgin install clang

Install development packages for DataStructureGenerator sources::

    # export PKG_PATH=http://ftp.eu.openbsd.org/pub/OpenBSD/5.6/packages/i386/
    # pkg_add -v -i apache-ant
    # pkg_add -v -i jdk
    # pkg_add -v -i jre
    # cd /usr/local/bin && ln -sf /usr/local/jdk-1.7.0/bin/java java
    # cd /usr/local/bin && ln -sf /usr/local/jdk-1.7.0/bin/javac javac
  
Add a symbolic link to python as root user::

    # ln -sf /usr/local/bin/python2.7 /usr/bin/python

Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Change to your source folder and create a build directory::

    $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

    $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build, run the tests, and install the OpenDaVINCI::

    $ make all

