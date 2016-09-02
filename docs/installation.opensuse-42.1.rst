Compiling OpenDaVINCI on OpenSuSE 42.1
--------------------------------------

Download and install openSuSE 42.1 and install its latest package updates::

    $ sudo zypper --non-interactive --no-gpg-checks refresh
    $ sudo zypper --non-interactive --no-gpg-checks update
  
Install OpenDaVINCI dependencies::

    $ sudo zypper --non-interactive --no-gpg-checks install ant ant-junit boost-devel cmake git freeglut-devel gcc gcc-c++ iproute2 make python opencv-devel psmisc libqt4-devel qwt-devel wget ffmpeg
    
.. Install required development packages for host-tools sources::

    $ sudo zypper install libusb-devel
    
Clean up installation::

    $ sudo zypper clean
  
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
