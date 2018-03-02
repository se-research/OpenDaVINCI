#!/usr/bin/env python2
# OpenDaVINCI - Portable middleware for distributed components.
# Copyright (C) 2017 Christian Berger, Julian Scholle
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
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

import cv2

import math
import OD4Listener
import opendavinci_pb2

def onMessage(msg, timeStamps):
    print "sent: " + str(timeStamps[0]) + ", received: " + str(timeStamps[1]) + ", sample time point: "  + str(timeStamps[2])
    print msg

def onSharedPointCloud(msg, spc, timeStamps):
    print "sent: " + str(timeStamps[0]) + ", received: " + str(timeStamps[1]) + ", sample time point: "  + str(timeStamps[2])
    print msg
    
    # componentDataType == 13 --> dataType == FLOAT
    # userInfo == 1 --> polar coordinates
    i = 0
    print "Points = " + str(msg.width/msg.numberOfComponentsPerPoint)
    if (msg.numberOfComponentsPerPoint == 4) and (msg.componentDataType == 13):
        d = spc[0] * math.cos(spc[i + 2] * math.pi/180.0)
        x = d + math.sin(spc[1] * math.pi/180.0)
        y = d + math.cos(spc[1] * math.pi/180.0)
        z = d + math.sin(spc[2] * math.pi/180.0)
        intensity = spc[3]/256.0
        print "d = " + str(d) + ", x = " + str(x) + ", y = " + str(y) + ", z = " + str(z) + ", intensity = " + str(intensity)
        i += 4


# "Main" part.
listener = OD4Listener.OD4Listener(cid=189) # Connect to OpenDaVINCI CID session under CID 189.
#listener.registerMessageCallback(28, onMessage, opendavinci_pb2.odcore_data_SharedPointCloud)
listener.registerSharedPointCloudCallback("velodyne16SM", onSharedPointCloud)
listener.connect()
listener.run()

