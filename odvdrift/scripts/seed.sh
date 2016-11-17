#!/bin/bash
clear
clear

# May required adjusting
vdriftTracksDir="/usr/local/share/games/vdrift/data/tracks"
vdriftPath="/home/se/OpenDaVINCI/odvdrift/build"

# Check number of arguments
if [ "$#" -ne 4 ]; then
  echo "Usage: seed <detect|extract> <track> <cid> <auto|manual>"
  exit 1
fi

if [ $1 != "detect" ]; then
  if [ $1 != "extract" ]; then
    echo "Usage: seed <detect|extract> <track> <cid> <auto|manual>"
    exit
  fi
fi

if [ ! -f ./configuration ]; then
    echo "This script expects to be run from the directory containing the OD configuration."
    exit
fi

if [ $1 == "extract" ]; then
  if [ $4 == "auto" ]; then
    echo "The combination of -extract and -auto is not supported, as extract does not calculate VPs"
    exit
  fi
fi

cid=$3
automatedDriver=false
extract=false
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

if [ $4 == "auto" ]; then
  automatedDriver=true
else $4 == "manual"
  automatedDriver=false
fi

echo "automated driver = $automatedDriver"
echo "extract mode     = $extract"
echo "cid              = $3"
echo "trackName        = $2"
echo "workingDirectory = $workingDirectory"

# Create command with Boolean flags
line="odvdrift --freq=10 --cid=$cid -trackName $trackName -workingDirectory $workingDirectory"
if [ $automatedDriver = true ]; then
  line+=" -automatedDriver"
fi

if [ $extract = true ]; then
  line+=" -extractMode"
fi

echo ""
echo "Starting: $line"
echo "--------------------------------------------------------------------------------"

# exit 1 # debug

gnome-terminal -e "odsupercomponent --cid=$cid --verbose=1"
gnome-terminal -e "odsimvehicle     --cid=$cid --verbose=1 --freq=10 "
gnome-terminal -e "odsimirus        --cid=$cid --verbose=1 --freq=10 "
gnome-terminal -e "odcockpit        --cid=$cid --verbose=1"

#exit 1 # debug

sleep 2  # Waits 2 seconds.
gnome-terminal -e "$vdriftPath/$line"

# /home/se/OpenDaVINCI/odvdrift/build/odvdrift --freq=10 --cid=200 -trackName a1ring -workingDirectory /home/se/config -manual -extract

# /home/se/OpenDaVINCI/odvdrift/build/odvdrift --freq=10 --cid=200 -trackName a1ring -workingDirectory /home/se/config -manual -detect

# /home/se/OpenDaVINCI/odvdrift/build/odvdrift --freq=10 --cid=200 -trackName a1ring -workingDirectory /home/se/config -auto -extract => Kombination sinnlos

# /home/se/OpenDaVINCI/odvdrift/build/odvdrift --freq=10 --cid=100 -trackName a1ring -workingDirectory /home/se/config -auto -detect
