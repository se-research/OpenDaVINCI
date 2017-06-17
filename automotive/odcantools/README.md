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

### Replay raw CAN data in asc format using odcanascreplay

In /odcanascreplay/example, there is an example "example.asc" from a real CAN dump for the four wheel speed encoders based on data provided by Jeremy Daily: http://tucrrc.utulsa.edu/ToyotaCAN.html. For convenience purposes, two individual CAN messages in the original example are merged into a single one to have an 8 byte payload. The raw CAN data has been transformed to asc format.
    
First go to /opt/od/bin, start odsupercomponent:

    $ LD_LIBRARY_PATH=/opt/od/lib ./odsupercomponent --cid=111

Note that the execution of odsupercomponent requires a configuration file. Create the configuration file if it does not exist in your current directory:

    $ touch configuration
    
While odsupercomponent is running, open a new terminal and start odcanasreplay:

    $ LD_LIBRARY_PATH=/opt/od/lib ./odcanascreplay --cid=111 --freq=10 < path/to/the/example/file/stated/above/example.asc
    
Open a new terminal and start odcanmapper:

    $ LD_LIBRARY_PATH=/opt/od/lib ./odcanmapper --cid=111
    
Open a new terminal and start odcockpit:

    $ LD_LIBRARY_PATH=/opt/od/lib ./odcockpit --cid=111
    
Open the plugin "spy" in odcockpit and you should be able to see the replayed CAN messages.

### Record diagnostic CAN messages using odcanproxy

odcanproxy is an application that opens a concrete CAN device, maps the low-level CAN message to a generic presentation. It also produces recording files. Recording raw CAN data requires a CAN adapter. The following instructions are tested with PCAN-USB from PEAK System (http://www.peak-system.com/Home.59.0.html?&L=1).

First, connect your laptop with the diagnostic interface of a car via a CAN adapter. If you use virtual machine, e.g. VirtualBox, go to the menu Devices->USB->... And then tick the CAN adapter to get it mounted in the guest operating system.

Check if the device driver has successfully detected the CAN adapter:

    $ dmesg
    
Check the correct device number of the CAN adapter:

    $ ifconfig -a

Go to /opt/od/bin and start odsupercomponent:

    $ LD_LIBRARY_PATH=/opt/od/lib ./odsupercomponent --cid=111
    
Open a new terminal and start odcanproxy:

    $ LD_LIBRARY_PATH=/opt/od/lib ./odcanproxy --cid=111 --verbose=1
    
Open a new terminal and start odcockpit:

    $ LD_LIBRARY_PATH=/opt/od/lib ./odcockpit --cid=111
    
Open the Spy window. If CAN messages are successfully received, they will be displayed in the Spy window. odcanproxy is closed either by stopping odcamproxy or stopping odsupercomponent. After odcanproxy is stopped, recording files in rec and rec.mem format will be found in /opt/od/bin.

### Replay a recording file

Go to /opt/od/bin and start odsupercomponent:

    $ LD_LIBRARY_PATH=/opt/od/lib ./odsupercomponent --cid=111
    
Open a new terminal and start odcockpit:

    $ LD_LIBRARY_PATH=/opt/od/lib ./odcockpit --cid=111
    
Open the Player window. Click "Load recording" to load a rec file which will can then be replayed.
