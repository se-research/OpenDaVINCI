How to show live Containers and Images with Python
""""""""""""""""""""""""""""""""""""""""""""""""""

OpenDaVINCI's data structure generator is emitting Protobuf-compatible
message descriptors. In this folder, an example is provided to demonstrate
how to connect to a running CID session with Python and process containers
using the Python/Protobuf interface. As Linux distribution, Ubuntu 16.04 is used. 
This tutorial assumes that cmake and Python are installed.

First, install the Protobuf compiler::

    $ sudo apt-get install --no-install-recommends protobuf-compiler
    
Install Python related package::

    $ sudo apt-get install python-posix-ipc python-sysv-ipc python-opencv python-protobuf
   
Next, pull the latest OpenDaVINCI Docker image::
    
    $ docker pull seresearch/opendavinci-ubuntu-16.04-complete

Assume that there is a recording file in .rec format along with an associated .H264 video file in ~/recordings. Go to OpenDaVINCI/odsupercomponent, and run the OpenDaVINCI software component lifecycle management module odsupercomponent::

    $ docker run -ti --rm --net=host -v `pwd`:/opt/example -w /opt/example seresearch/opendavinci-ubuntu-16.04-complete:latest /opt/od4/bin/odsupercomponent --cid=189 --configuration=/opt/example/configuration

In a new terminal, grant Docker access to X11 server::

    $ xhost +
    
Run the visualization module odcockpit::

    $ docker run -ti --rm --net=host --ipc=host --user=odv -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v ~/recordings:/opt/recordings -v seresearch/opendavinci-ubuntu-16.04-complete:latest /opt/od4/bin/odcockpit --cid=189

In odcockpit, open plugins Player, LiveFeed, and SharedImageViewer. In Player, load the .rec recording file from /opt/recordings and tick the checkbox "Relay Containers to Conference".

In a new terminal, go to OpenDaVINCI/tutorials/Python_ShowImage. Make sure that the camera name in the field odcore.data.image.SharedImage/0 in LiveFeed of odcockpit is the same as the name XX specified in the line listener.registerImageCallback(?XX", onImage) in the Python script ShowImage.py. If they are different, change XX in ShowImage.py accordingly. Then generate the Protobuf data structures and execute the Python script::

    $ make clean all

The script will activate a pop-up window showing the same video that is played in SharedImageViewer of odcockpit.

