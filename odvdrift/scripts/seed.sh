#!/bin/bash
clear
clear

# May required adjusting
vdriftTracksDir="/usr/local/share/games/vdrift/data/tracks"

# Check number of arguments
if [ "$#" -ne 3 ]; then
  echo "Usage: seed <detect|extract> <track> <cid> "
  exit 1
fi

if [ $1 != "detect" ]; then
  if [ $1 != "extract" ]; then
    echo "seed (detect|extract) <track> <cid> "
    exit
  fi
fi

if [ ! -f ./configuration ]; then
    echo "This script expects to be run from the directory containing the OD configuration."
    exit
fi

cid=$3
extract=true
workingDirectory=$(pwd)
trackName=$2
outputDir="$workingDirectory/$trackName/png"

# Create output directories
mkdir -p $outputDir

echo "--------------------------------------------------------------------------------"
echo "Ensure to be owner of $vdriftTracksDir"
echo "Ensure the original textures are in "
echo " - $vdriftTracksDir/$2/objects-original"
echo "Ensure the B/W textures are in "
echo " - $vdriftTracksDir/$2/objects-bw"
echo ""

if [ $1 == "extract" ]; then
  extract=true
  # Copy original textures to track objects folder
  echo "Copied original textures to track textures"
  cp -r $vdriftTracksDir/$2/objects-original/* $vdriftTracksDir/$2/objects/
else # $1 == "detect"
  extract=false
  # Copy bw textures to track objects folder
  echo "Copied B/W textures to track textures"
  cp -r $vdriftTracksDir/$2/objects-bw/* $vdriftTracksDir/$2/objects/
fi
echo ""

echo "extract mode     = $extract"
echo "cid              = $3"
echo "trackName        = $2"
echo "workingDirectory = $workingDirectory"
echo "--------------------------------------------------------------------------------"

# exit 1 # debug

gnome-terminal -e "odsupercomponent --cid=$cid --verbose=1"
gnome-terminal -e "odsimvehicle     --cid=$cid --verbose=1 --freq=10 "
gnome-terminal -e "odsimirus        --cid=$cid --verbose=1 --freq=10 "
gnome-terminal -e "odcockpit        --cid=$cid --verbose=1"

sleep 2  # Waits 2 seconds.
echo "Starting: odvdrift --freq=10 --cid=100 -trackName $trackName -workingDirectory $workingDirectory -extractMode $extract"
gnome-terminal -e "/home/se/OpenDaVINCI/odvdrift/build/odvdrift --freq=10 --cid=100 -trackName $trackName -workingDirectory $workingDirectory -extractMode $extract"

# /home/se/OpenDaVINCI/odvdrift/build/odvdrift --freq=10 --cid=100 -trackName a1ring -workingDirectory /home/se/config -extractMode false
