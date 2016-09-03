Compiling OpenDaVINCI on Debian Jessie
-----------------------------------

Download and install Debian Jessie and install its latest package updates::

    $ sudo apt-get update -y
    $ sudo apt-get upgrade -y
    $ sudo apt-get dist-upgrade -y

Install OpenDaVINCI dependencies::

    $ sudo apt-get install -y --no-install-recommends ant build-essential cmake default-jre default-jdk freeglut3 freeglut3-dev git libboost-dev libopencv-dev libopencv-core-dev libopencv-highgui-dev libopencv-imgproc-dev libqt4-dev libqt4-opengl-dev libqwt5-qt4-dev libqwt5-qt4 qt4-dev-tools rpm psmisc wget

Clean up installation::

    $ sudo apt-get clean
    $ sudo apt-get autoremove

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
