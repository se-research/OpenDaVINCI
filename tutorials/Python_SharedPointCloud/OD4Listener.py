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

import datetime
import numpy
import posix_ipc
import signal
import socket
import struct
import sysv_ipc
import thread

import opendavinci_pb2

# This class provides an OpenDaVINCI4 listener to receive live messages from a
# running conference. This class helps to access unstructured data like
# SharedImages.
class OD4Listener:
    @staticmethod
    def __getCRC32(string):
        retVal = 0
        for char in string:
            retVal = retVal ^ ord(char) ^ 0x04C11DB7  # The CRC32 polynomial.
        return retVal

    @staticmethod
    def run():
        signal.pause()


    def __init__(self, cid, port=12175):
        assert cid <= 255

        self.MULTICAST_PORT = port
        self.MULTICAST_GROUP = "225.0.0." + str(cid)
        self.isRunning = False
        self.isConnected = False
        self.callbacks = dict()
        self.imageCallbacks = dict()
        self.spcCallbacks = dict()
        self.sock = None


    def connect(self):
        assert not self.isConnected

        # Create UDP multicast socket.
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(('', self.MULTICAST_PORT))
        req = struct.pack("4sl", socket.inet_aton(self.MULTICAST_GROUP), socket.INADDR_ANY)
        self.sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, req)
        self.isConnected = True
        if not self.isRunning:
            thread.start_new_thread(self.__runner, ())
            self.isRunning = True


    def registerMessageCallback(self, msgID, func, msgType, params=()):
        assert hasattr(func, '__call__')
        self.callbacks[msgID] = (func, msgType, params)

    def registerImageCallback(self, name, func, params=()):
        assert hasattr(func, '__call__')
        self.imageCallbacks[str(name)] = (func, params)

    def registerSharedPointCloudCallback(self, name, func, params=()):
        assert hasattr(func, '__call__')
        print name
        self.spcCallbacks[str(name)] = (func, params)

    def __threadedImageConverter(self, msg, timestamps, callback):
        # Semaphore is limited to 14 characters.
        name = "/" + msg.name.replace("/", "_")
        name = name[:14]

        __semaphore = posix_ipc.Semaphore(str(name))
        __sharedmemory = sysv_ipc.SharedMemory(self.__getCRC32(name))
        __semaphore.acquire()
        try:
            image = __sharedmemory.read(msg.size + 4)[4:]
        finally:
            __sharedmemory.detach()
            __semaphore.release()
            __semaphore.close()

        tmp = numpy.frombuffer(image, numpy.uint8).reshape(msg.height, msg.width, msg.bytesPerPixel)
        callback[0](msg, tmp, timestamps, *callback[1])

    def __threadedSharedPointCloudConverter(self, msg, timestamps, callback):
        # Semaphore is limited to 14 characters.
        name = "/" + msg.name.replace("/", "_")
        name = name[:14]
        print name

        __semaphore = posix_ipc.Semaphore(str(name))
        __sharedmemory = sysv_ipc.SharedMemory(self.__getCRC32(name))
        __semaphore.acquire()
        try:
            spc = __sharedmemory.read(msg.size + 4)[4:]
        finally:
            __sharedmemory.detach()
            __semaphore.release()
            __semaphore.close()

        tmp = numpy.frombuffer(spc, numpy.float32)
        callback[0](msg, tmp, timestamps, *callback[1])


    def __process(self, c):
        DATA_TYPE_SHAREDIMAGE = 14
        DATA_TYPE_SHAREDPOINTCLOUD = 28
        print "Container ID = " + str(c.dataType)

        # Extract sent, received, and sample time point.
        sent = datetime.datetime.fromtimestamp(timestamp=c.sent.seconds) + datetime.timedelta(microseconds=c.sent.microseconds)
        received = datetime.datetime.fromtimestamp(timestamp=c.received.seconds) + datetime.timedelta(microseconds=c.received.microseconds)
        sampleTimeStamp = datetime.datetime.fromtimestamp(timestamp=c.sampleTimeStamp.seconds) + datetime.timedelta(microseconds=c.sampleTimeStamp.microseconds)
        timestamps = [sent, received, sampleTimeStamp]

        # Extract image from shared memory.
        if c.dataType == DATA_TYPE_SHAREDIMAGE:
            msg = opendavinci_pb2.odcore_data_image_SharedImage()
            msg.ParseFromString(c.serializedData)
            if msg.name in self.imageCallbacks.keys():
                thread.start_new_thread(self.__threadedImageConverter, (msg, timestamps, self.imageCallbacks[msg.name]))

        # Extract data from shared memory.
        if c.dataType == DATA_TYPE_SHAREDPOINTCLOUD:
            msg = opendavinci_pb2.odcore_data_SharedPointCloud()
            msg.ParseFromString(c.serializedData)
            if msg.name in self.spcCallbacks.keys():
                thread.start_new_thread(self.__threadedSharedPointCloudConverter, (msg, timestamps, self.spcCallbacks[msg.name]))

        # Check for callback in other case.
        if c.dataType in self.callbacks.keys():
            msg = self.callbacks[c.dataType][1]()
            msg.ParseFromString(c.serializedData)
            thread.start_new_thread(self.callbacks[c.dataType][0], (msg, timestamps) + (self.callbacks[c.dataType][2]))


    def __runner(self):
        buf = ""
        expectedBytes = 0
        LENGTH_OPENDAVINCI_HEADER = 5
        consumedOpenDaVINCIContainerHeader = False

        while True:
            if consumedOpenDaVINCIContainerHeader:
                if len(buf) >= expectedBytes:
                    container = opendavinci_pb2.odcore_data_MessageContainer()
                    container.ParseFromString(buf)
                    self.__process(container)
                    # Start over and read next container.
                    consumedOpenDaVINCIContainerHeader = False
                    buf = buf[expectedBytes:]
                    expectedBytes = 0

            if not consumedOpenDaVINCIContainerHeader:
                if len(buf) >= LENGTH_OPENDAVINCI_HEADER:
                    consumedOpenDaVINCIContainerHeader = True
                    byte0 = buf[0]
                    byte1 = buf[1]

                    # Check for OpenDaVINCI header.
                    if ord(byte0) == int('0x0D',16) and ord(byte1) == int('0xA4',16):
                        v = struct.unpack('<L', buf[1:5]) # Read uint32_t and convert to little endian.
                        expectedBytes = v[0] >> 8 # The second byte belongs to OpenDaVINCI's Container header.
                        buf = buf[5:] # Remove header.
                    else:
                        print "Failed to consume OpenDaVINCI container."

            # Receive data from UDP socket.
            data = self.sock.recv(2048)
            if len(data) != 2048:
                # Avoid corrupt packets.
                buf = buf + data

