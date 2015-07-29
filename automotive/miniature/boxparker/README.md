# OpenDaVINCI - boxparker example

This example was realized with OpenDaVINCI and demonstrates how to use the
framework in combination with the simulation environment to develop a
self-parking algorithm. The following instructions are tested with Ubuntu
14.04 LTS; further information for other platforms or how to build
OpenDaVINCI are available here: http://opendavinci.readthedocs.org/en/latest.

Further background about this project is provided here: http://arxiv.org/abs/1406.7768


### Adding OpenDaVINCI to your Ubuntu Linux distribution

First, you need to add our .deb repository. We provide packages for x86,
x86_64, and armfh.

Add the public key from our repository:

    $ wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

Add our repository itself to your sources.list:

    $ sudo echo "deb http://opendavinci.cse.chalmers.se/ubuntu/ trusty main" >> /etc/apt/sources.list

Update your package database:

    $ sudo apt-get update



### Installing OpenDaVINCI & automotive data structures library

Next, you need to install the OpenDaVINCI library an the automotive data
structures library: 

Install the OpenDaVINCI library:

    $ sudo apt-get install opendavinci-odlib

Install the automotive data structures:

    $ sudo apt-get install opendavinci-odautomotivedata



## Install the build environment

To build the sources in this repository, you need to install the
build environment, cmake, and git:

Install the build environment:

    $ sudo apt-get install build-essential

Install cmake & git:

    $ sudo apt-get install cmake git



## Build boxparker from sources

Next, boxparker will be built from sources:

Clone this repository:

    $ git clone https://github.com/se-research/OpenDaVINCI.git

Change to boxparker:

    $ cd OpenDaVINCI/automotive/miniature/boxparker

Create a build folder:

    $ mkdir build

Generate the build system:

    $ cd build && cmake ..

Build boxparker:

    $ make

Leave the build directory:

    $ cd ..



## Prepare configuration

The repository contains a configuration file and two test scenarios in
the directory "config". As the simulation environment is provided as a
Docker image, this configuration needs to be prepared so that we can
simply start the Docker image later.

Create a symbolic link in your $HOME folder:

    $ ln -sf $PWD/config $HOME/config



## Run the simulation

Now, the simulation as provided in a Docker image can be started:

Start "odsupercomponent" for the software component lifecycle management (this step will download the Docker image):

    $ docker run --rm=true --net host -v /home/$USER/config:/opt/data -w "/opt/data" -t -i seresearch/odsimulation:latest /opt/sim/bin/odsupercomponent --cid=111 --verbose=1

Next, start the vehicle dynamics simulation "vehicle":

    $ docker run --rm=true --net host -v /home/$USER/config:/opt/data -w "/opt/data" -t -i seresearch/odsimulation:latest /opt/sim/bin/vehicle --cid=111 --freq=10

Now, we start the sensor simulation "irus":

    $ docker run --rm=true --net host -v /home/$USER/config:/opt/data -w "/opt/data" -t -i seresearch/odsimulation:latest /opt/sim/bin/irus --cid=111 --freq=10

Start the visualization environment "cockpit" (the first command grants access to your Xserver):

    $ xhost +

    $ docker run --rm=true --net host -w "/opt/data" -t -i -e DISPLAY=$DISPLAY -e QT_X11_NO_MITSHM=1 -v /home/$USER/config:/opt/data -v /tmp/.X11-unix:/tmp/.X11-unix seresearch/odsimulation:latest /opt/sim/bin/cockpit --cid=111

Start the "BirdsEyeMap" plugin.



## Start boxparker

Next, change the build directory and start the boxparker component:

    $ cd build

    $ ./boxparker --cid=111 --freq=10 --verbose=1

