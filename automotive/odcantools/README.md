# OpenDaVINCI - Odcantools instruction

This folder contains several CAN related tools for recording and replaying raw CAN data, mapping raw CAN data to high-level data representation, and replaying raw CAN data in asc format. The following instructions are tested with Ubuntu 14.04 LTS; further information for other platforms or how to build OpenDaVINCI are available here: http://opendavinci.readthedocs.org/en/latest.

In order to play with odcantools, you need to install Git, and compile the latest OpenDaVINCI as follows:

### Compile OpenDaVINCI in your Ubuntu Linux distribution

First, clone OpenDaVINCI from our GitHub repository:

    $ git clone https://github.com/se-research/OpenDaVINCI.git

Go to the OpenDaVINCI folder, create a build folder and go to the build folder:

    $ cd OpenDaVINCI
    $ mkdir build && cd build

Prepare a folder /opt/od for installing OpenDaVINCI binaries:

    $ sudo mkdir /opt/od
   
Give your user account write permission in the folder /opt/od:

    $ sudo chown $USER:$USER /opt/od

Generate the build system:

    $ cmake -D CMAKE_INSTALL_PREFIX=/opt/od ..
    
Build OpenDaVINCI:

    $ make
    
After a successful compilation, all the OpenDaVINCI binaries will be found in /opt/od/bin/.

### Install third-party packages for odcockpit

Some tools in this folder require the odcockpit visualization environment, which is dependent on a number of third-party packages. Run
    $ sudo apt-get install libcv-dev libhighgui-dev freeglut3 libqt4-dev libqwt5-qt4-dev libqwt5-qt4 libqt4-opengl-dev freeglut3-dev qt4-dev-tools libboost-dev

### Replay raw CAN data in asc format using odcanascreplay

In /odcanascreplay/example, there is an example from a real CAN dump for the four wheel speed encoders based on data provided by Jeremy Daily: http://tucrrc.utulsa.edu/ToyotaCAN.html. For convenience purposes, two individual CAN messages in the original example are merged into a single one to have an 8 byte payload. The raw CAN data has been transformed to asc format.

Go to /opt/od/bin/ and start odsupercomponent. The execution of odsupercomponent requires a configuration file. Create the configuration file if it does not exist:

    $ touch configuration
    
Then start odsupercomponent:

    $ ./odsupercomponent --cid=111
    
Open a new terminal and start odcanasreplay:

    $ ./odcanascreplay --cid=111 --freq=10 < path/to/the/example/file/stated/above/example.asc
    
Open a new terminal and start odcanmapper:

    $ ./odcanmapper --cid=111
    
Open a new terminal and start odcockpit:

    $ ./odcockpit --cid=111
    
Open the plugin "spy" in odcockpit and you should be able to see the replayed CAN messages.

### Record diagnostic CAN messages using odcanproxy

odcanproxy is an application that opens a concrete CAN device, maps the low-level CAN message to a generic presentation. It also produces recording files. Recording raw CAN data requires a CAN adapter. The following instructions are tested with PCAN-USB from PEAK System (http://www.peak-system.com/Home.59.0.html?&L=1).

First, connect your laptop with the diagnostic interface of a car via a CAN adapter. If you use virtual machine, e.g. VirtualBox, go to the menu Devices->USB->... And then tick the CAN adapter to get it mounted in the guest operating system.

Open the configuration file in /opt/od/bin/. At the last line add:

    $  odcanproxy.devicenode=/dev/pcan32
    
Then the CAN adapter will appear in the folder /dev/pcan32 every time it is mounted.

Download the driver of the CAN adapter: http://www.peak-system.com/fileadmin/media/linux/files/peak-linux-driver-7.15.2.tar.gz Unpack the archive, disable the network and make (The network has to be disabled to make the recording work for this driver):

    $ make NET=NO
    
Go to /opt/od/bin and start odsupercomponent:

    $ ./odsupercomponent --cid=111
    
Open a new terminal and start odcanproxy:

    $ ./odcanproxy --cid=111 --verbose=1
    
Open a new terminal and start odcockpit:

    $ ./odcockpit --cid=111
    
Open the Spy window. If CAN messages are successfully received, they will be displayed in the Spy window. odcanproxy is closed either by stopping odcamproxy or stopping odsupercomponent. After odcanproxy is stopped, recording files in rec and rec.mem format will be found in /opt/od/bin.

### Replay a recording file

Go to /opt/od/bin and start odsupercomponent:

    $ ./odsupercomponent --cid=111
    
Open a new terminal and start odcockpit:

    $ ./odcockpit --cid=111
    
Open the Player window. Click "Load recording" to load a rec file which will can then be replayed.