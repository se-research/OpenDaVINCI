Compiling OpenDaVINCI on ArchLinux
----------------------------------

Download and install ArchLinux and install using the following instructions: https://wiki.archlinux.org/index.php/Installation_guide

.. Install some core packages::

    # pacman -S net-tools openssh sudo

Install some core packages::

    # pacman -S net-tools sudo

Install the required development packages for OpenDaVINCI sources::

    $ sudo pacman -S cmake gcc git make python2

Add a missing symbolic link::

    $ sudo ln -sf /usr/bin/python2.7 /usr/bin/python

Install development packages for libodsimulation sources::

    $ sudo pacman -S freeglut
    $ sudo pacman -S qt4
    $ sudo pacman -S boost
    $ sudo pacman -S opencv-devel

Install qwt5-qt4::

    $ sudo pacman -S qwt5

Add two missing symbolic links::

    $ sudo ln -sf /usr/include/qwt5 /usr/include/qwt-qt4
    $ sudo ln -sf /usr/local/qwt-5.2.3/lib/libqwt.so.5.2.3 /usr/include/libqwt-qt4.so

.. Install the required development packages for host-tools sources:

    $ sudo pacman -S libusb

.. Add a missing symbolic link:

    $ sudo ln -sf /usr/include/libusb-1.0/libusb.h /usr/include/usb.h

Install the required development packages for the DataStructureGenerator sources::

    $ sudo pacman -S jdk8-openjdk
    $ sudo pacman -S apache-ant
    $ sudo pacman -S junit

Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Change to your source folder and create a build directory::

    $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

    $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..

Build, run the tests, and install the OpenDaVINCI::

    $ sudo make all
    
Note that sudo is used here because installing software to system-wide directories (e.g., /usr/local) requires superuser (root) privileges. If OpenDaVINCI is installed in a different directory, e.g., /opt/od, then there is no need to use sudo. Instead, write permission should be given::

    $ sudo chown $USER:$USER /opt/od
