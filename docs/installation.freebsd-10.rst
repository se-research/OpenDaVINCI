Compiling OpenDaVINCI on FreeBSD 10.1 (32bit and 64bit)
-------------------------------------------------------

Download and install FreeBSD 10.1 and update the packages list as root (FreeBSD will install automatically the package management tool, simply press 'y' to accept)::

    # pkg update
  
Install the bash shell for more convenient typing::

    # pkg install shells/bash
  
Add the following line to /etc/fstab as indicated by the installer::

    fdesc    /dev/fd      fdescfs      rw  0    0


Change the shell by running::

    $ chsh
  
Install the compiler::

    # pkg install lang/gcc
    # pkg install devel/cmake
    # pkg install devel/git
    # pkg install lang/python
  
Add a symbolic link to python as root user::

    # ln -sf /usr/local/bin/python /usr/bin/python

Install Java to generate data structures::

    # pkg install devel/apache-ant
    # pkg install openjdk

Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Change to your source folder and create a build directory::

    $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

    $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build, run the tests, and install the OpenDaVINCI::

    $ make all

