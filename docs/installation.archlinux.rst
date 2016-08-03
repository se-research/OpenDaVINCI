Compiling OpenDaVINCI on ArchLinux
----------------------------------

Download and install ArchLinux and install using the following instructions: https://wiki.archlinux.org/index.php/Installation_guide

.. Install some core packages::

    # pacman -S net-tools openssh sudo

Install some core packages::

    # pacman -S net-tools sudo

Install the required development packages for OpenDaVINCI sources::

    $ sudo pacman -S cmake gcc git make python2

Install development packages for libodsimulation sources::

    $ sudo pacman -S freeglut qt4 boost opencv

Install qwt5-qt4::

    $ sudo pacman -S qwt5

.. Install the required development packages for host-tools sources:

    $ sudo pacman -S libusb

.. Add a missing symbolic link:

    $ sudo ln -sf /usr/include/libusb-1.0/libusb.h /usr/include/usb.h

Install the required development packages for the DataStructureGenerator sources::

    $ sudo pacman -S jdk8-openjdk apache-ant junit

Clone the latest OpenDaVINCI sources from https://github.com/se-research/OpenDaVINCI or download
the latest OpenDaVINCI sources as zip file: https://github.com/se-research/OpenDaVINCI/archive/master.zip.

Create an installation folder::

    $ sudo mkdir -p /opt/od && sudo chown $USER:$USER /opt/od

Change to your source folder and create a build directory::

    $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder::

    $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/opt/od ..

Build, run the tests, and install the OpenDaVINCI::

    $ make
