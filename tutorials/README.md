# OpenDaVINCI - Tutorials

This folder contains several examples and descriptions how to use OpenDaVINCI.
The instructions are tested with Ubuntu 14.04 LTS; further information for other
platforms or how to build OpenDaVINCI are available here: http://opendavinci.readthedocs.org/en/latest.

While all examples are also part of the source code distribution for OpenDaVINCI,
the fastest way to start on Ubuntu Linux is to install the OpenDaVINCI middleware
from the pre-compiled binaries as described in the following.



### Adding OpenDaVINCI to your Ubuntu Linux distribution

First, you need to add our .deb repository. We provide packages for x86, x86_64,
and armfh.

Add the public key from our repository:

    $ wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

Add our repository itself to your sources.list:

    $ sudo echo "deb http://opendavinci.cse.chalmers.se/ubuntu/ trusty main" >> /etc/apt/sources.list

Update your package database:

    $ sudo apt-get update



### Installing the OpenDaVINCI library

    $ sudo apt-get install opendavinci-odlib



## Install the build environment

To build the sources in this repository, you need to install the
build environment, cmake, and git:

Install the build environment:

    $ sudo apt-get install build-essential

Install cmake & git:

    $ sudo apt-get install cmake git



### Building the tutorials

Once you have cloned the repository, you can build the tutorials
as follows::

    $ mkdir build && cd build
    $ cmake ..
    $ make

