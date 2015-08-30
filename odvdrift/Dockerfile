# Dockerfile to create a Docker image wrapping odvdrift.
#
# Copyright (C) 2015 Christian Berger.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 3
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

# Author: Christian Berger
# Date: 2015-08-30

# Build with:  docker build -t seresearch/odvdrift:v2.0.11 .
# Run with:    xhost + && docker run -ti -e DISPLAY=$DISPLAY --net="host" -v /tmp/.X11-unix:/tmp/.X11-unix -v /home/msv/simulators/vdrift/data:/usr/local/share/games/vdrift/data seresearch/odvdrift:v2.0.11 /odvdrift --cid=111 -benchmark --freq=10

FROM seresearch/opendavinci-ubuntu-amd64:latest
MAINTAINER Christian Berger "christian.berger@gu.se"

# Set the env variable DEBIAN_FRONTEND to noninteractive
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update -y

RUN apt-get install -y libopencv-dev \
                       libbullet-dev \
                       libvorbisfile3 \
                       libcurl3 \
                       libsdl2-dev \
                       libsdl2-image-dev \
                       odsimulation-odsimlib \
                       libcurl4-gnutls-dev \
                       freeglut3 freeglut3-dev

RUN apt-get upgrade -y

RUN apt-get clean
RUN apt-get autoremove

# Set locale (fix the locale warnings)
RUN localedef -v -c -i en_US -f UTF-8 en_US.UTF-8 || :

ADD build/odvdrift /odvdrift

