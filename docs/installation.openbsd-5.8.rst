Compiling OpenDaVINCI on OpenBSD 5.8 (32bit and 64bit)
------------------------------------------------------

Download and install OpenBSD 5.8.

Set the PKG_PATH (32bit version)::

   # export PKG_PATH=http://ftp.eu.openbsd.org/pub/OpenBSD/5.8/packages/i386/

Set the PKG_PATH (64bit version)::

   # export PKG_PATH=http://ftp.eu.openbsd.org/pub/OpenBSD/5.8/packages/amd64/

Install the bash shell::

   # pkg_add -v -i bash
  
You can change the shell by running::

   $ chsh
  
Install the compiler::

   # pkg_add -v -i bash
   # pkg_add -v -i python # (choose version 2.7)
   # pkg_add -v -i cmake
   # pkg_add -v -i git
   # pkg_add -v -i gcc # (should be installed automatically via comp58.tgz)
  
.. Install the Java::

   # pkg_add -v -i apache-ant
   # pkg_add -v -i jdk
   # pkg_add -v -i jre
   # cd /usr/local/bin && ln -sf /usr/local/jdk-1.8.0/bin/javac javac
   # cd /usr/local/bin && ln -sf /usr/local/jdk-1.8.0/bin/javah javah
   # cd /usr/local/bin && ln -sf /usr/local/jdk-1.8.0/bin/java java
   # cd /usr/local/bin && ln -sf /usr/local/jdk-1.8.0/bin/jar jar
   # cd /usr/local/bin && ln -sf /usr/local/jdk-1.8.0/bin/javadoc javadoc
  
Add a symbolic link to python as root user::

   # ln -sf /usr/local/bin/python2.7 /usr/bin/python

Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Change your source folder and create a build directory::

   $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

   $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build, run the tests, and install the OpenDaVINCI::

   $ make all

