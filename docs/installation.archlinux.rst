Compiling OpenDaVINCI on ArchLinux
----------------------------------

Download and install ArchLinux and install using the following instructions: https://wiki.archlinux.org/index.php/Installation_guide

.. Install some core packages::

    $ pacman -S net-tools openssh sudo

Update the keys and the package database::

	$ pacman-key --init
	$ yes | pacman --noconfirm -Sc
	$ yes | pacman --noconfirm -Sy pacman
	$ pacman-db-upgrade
	$ yes | pacman --noconfirm -S archlinux-keyring
	$ pacman-key --init
	$ yes | pacman --noconfirm -Syu

Install OpenDaVINCI dependencies::

    $ sudo pacman --no-confirm -S apache-ant jdk8-openjdk boost cmake ffmpeg2.8 freeglut gcc git junit make opencv python2 qt4 qwt5

.. Install the required development packages for host-tools sources:

    $ sudo pacman -S libusb

.. Add a missing symbolic link:

    $ sudo ln -sf /usr/include/libusb-1.0/libusb.h /usr/include/usb.h

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
