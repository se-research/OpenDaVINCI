#!/bin/bash
clear
clear
echo $1
echo $2

if [ $2 == "-textured" ]
then
  echo "Animated Textures"
  cp /usr/local/share/games/vdrift/data/tracks/a1ring/objects/old/* /usr/local/share/games/vdrift/data/tracks/a1ring/objects/
else
  echo "VP detection"
  cp /usr/local/share/games/vdrift/data/tracks/a1ring/objects/new/* /usr/local/share/games/vdrift/data/tracks/a1ring/objects/
fi

cd ~/OpenDaVINCI/automotive/miniature/config
gnome-terminal -e "/opt/od/bin/odsupercomponent --cid=$1 --freq=10 --verbose=1"
sleep 1  # Waits 2 seconds.
gnome-terminal -e "/opt/od/bin/odsimvehicle --cid=$1 --freq=10 --verbose=1"
#sleep 1  # Waits 2 seconds.
#gnome-terminal -e "/opt/od/bin/odsimirus --cid=$1 --freq=10 --verbose=1"
sleep 1  # Waits 2 seconds.
gnome-terminal -e "/opt/od/bin/odcockpit --cid=$1 --verbose=1 --freq=10"

sleep 1  # Waits 2 seconds.
echo "/home/evgeny/OpenDaVINCI/odvdrift/build3/odvdrift --cid=$1 --freq=10 $2> vdrift.txt"
gnome-terminal -e "/home/evgeny/OpenDaVINCI/odvdrift/build3/odvdrift --cid=$1 --freq=10 $2 > vdrift.txt"
