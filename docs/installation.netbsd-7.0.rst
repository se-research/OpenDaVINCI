Compiling OpenDaVINCI on NetBSD 7.0 (64bit)
-------------------------------------------------------

Install the compiler::

   # export PKG_PATH=http://ftp.NetBSD.org/pub/pkgsrc/packages/NetBSD/amd64/7.0/All
   # pkg_add -v cmake
   # pkg_add -v git
   # pkg_add -v mozilla-rootcerts
   # mozilla-rootcerts install
   # pkg_add -v python27
   # pkg_add -v gcc49
   # pkg_add -v openjdk7
   # pkg_add -v apache-ant
  
Add a symbolic link to python as root user::

   # ln -sf /usr/pkg/bin/python2.7 /usr/pkg/bin/python

Add a symbolic link to Java as root user::

   # ln -sf /usr/pkg/bin/openjdk7-java /usr/pkg/bin/java
   # ln -sf /usr/pkg/bin/openjdk7-javac /usr/pkg/bin/javac
   # ln -sf /usr/pkg/bin/openjdk7-javah /usr/pkg/bin/javah
   # ln -sf /usr/pkg/bin/openjdk7-javadoc /usr/pkg/bin/javadoc
   # ln -sf /usr/pkg/bin/openjdk7-jar /usr/pkg/bin/jar

Add a /usr/pkg/bin to the search path of the local user::

   $ export PATH=/usr/pkg/bin:$PATH
  
Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Change your source folder and create a build directory::

   $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

   $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build, run the tests, and install the OpenDaVINCI::

   $ make all

