Compiling OpenDaVINCI on DragonFlyBSD 4.0.5 (64bit)
---------------------------------------------------

Download and install DragonFlyBSD 4.0.5 and update the packages list as root::

   # pkg update
  
Install the bash shell::

   # pkg install shells/bash
  
Change the shell by running::

   $ chsh
  
Install the compiler::

   # pkg install lang/gcc
   # pkg install devel/cmake
   # pkg install devel/git
   # pkg install lang/python

Install Java to generate data structures::

   # pkg install java/openjdk7

.. Install Java to generate data structures::
   # pkg install devel/apache-ant
   # pkg install java/openjdk7
  
Add the following lines to /etc/fstab::

   fdesc   /dev/fd     fdescfs     rw  0   0
   proc    /proc       procfs      rw  0   0
  
Add a symbolic link to python as root user::

   # ln -sf /usr/local/bin/python /usr/bin/python
  
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
