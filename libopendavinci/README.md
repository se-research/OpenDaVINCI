# OpenDaVINCI - Open Source Development Architecture for Virtual, Networked, and Cyber-Physical System Infrastructures

This is the source code for OpenDaVINCI, the Open Source Development Architecture for Virtual,
Networked, and Cyber-Physical System Infrastructures. The following instructions
are tested with Ubuntu 14.04 LTS; further information for other platforms or
how to build OpenDaVINCI are available here: http://opendavinci.readthedocs.org/en/latest.

Further background about this project is provided here: http://www.christianberger.net/Ber10.pdf

The following 3rd party software is included:

* Eigen-3.2.4: "This software is based in part on the work for Eigen, a lightweight C++ template library for linear algebra, copyright 2008 Gael Guennebaud and 2007-2011 Benoit Jacob."
* jpeg9a: "This software is based in part on the work of the Independent JPEG Group."
* libzip-0.9: "This software is based in part on the work for lib zip, a library to manipulate ZIP archives."
* wjwwood-serial-1.2.1: "This software is based in part on the work for wjwwood-serial, a library to provide a cross platform interface for interacting with Serial Ports, copyright 2012 William Woodall and John Harrison."
* zlib-1.2.8: "This software is based in part on the work for zlib, copyright 1995-2004 Jean-loup Gailly and Mark Adler."


### Adding OpenDaVINCI to your Ubuntu Linux distribution

First, you need to add our .deb repository. We provide packages for x86,
x86_64, and armfh.

Add the public key from our repository:

    $ wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

Add our repository itself to your sources.list:

    $ sudo echo "deb http://opendavinci.cse.chalmers.se/ubuntu/ trusty main" >> /etc/apt/sources.list

Update your package database:

    $ sudo apt-get update


### Installing OpenDaVINCI

Next, you need to install the OpenDaVINCI library: 

Install the OpenDaVINCI library:

    $ sudo apt-get install opendavinci-lib


