import OpenDaVINCITestData_pb2
import sys
import struct

# Print Container's payload.
def extractAndPrintPayload(identifier, p):
    if identifier == 1002: # TestMessage2
        tm = OpenDaVINCITestData_pb2.TestMessage2()
        tm.ParseFromString(p)
        print "Payload: " + str(tm)

    if identifier == 1005: # TestMessage5
        tm = OpenDaVINCITestData_pb2.TestMessage5()
        tm.ParseFromString(p)
        print "Payload: " + str(tm)

    if identifier == 1006: # TestMessage6
        tm = OpenDaVINCITestData_pb2.TestMessage6()
        tm.ParseFromString(p)
        print "Payload: " + str(tm)

    if identifier == 1007: # TestMessage7
        tm = OpenDaVINCITestData_pb2.TestMessage7()
        tm.ParseFromString(p)
        print "Payload: " + str(tm)

# Print Container's content.
def printContainer(c):
    print "Container ID = " + str(c.dataType)
    print "Container sent = " + str(c.sent)
    print "Container received = " + str(c.received)
    extractAndPrintPayload(c.dataType, c.serializedData)


# Main.
containers = []

if len(sys.argv) != 2:
    print "Display OpenDaVINCI Containers."
    print "  Usage:", sys.argv[0], "recording_file.rec"
    sys.exit(-1)

# Read contents from file.
with open(sys.argv[1], "rb") as f:
    buf = ""
    bytesRead = 0
    expectedBytes = 0
    LENGTH_OPENDAVINCI_HEADER = 5
    consumedOpenDaVINCIContainerHeader = False

    byte = f.read(1)
    while byte != "":
        buf = buf + byte
        bytesRead = bytesRead + 1

        if consumedOpenDaVINCIContainerHeader:
            expectedBytes = expectedBytes - 1
            if expectedBytes == 0:
                container = OpenDaVINCITestData_pb2.Container()
                container.ParseFromString(buf)
                containers = containers + [container]
                # Start over and read next container.
                consumedOpenDaVINCIContainerHeader = False
                bytesRead = 0
                buf = ""

        if not consumedOpenDaVINCIContainerHeader:
            if bytesRead == LENGTH_OPENDAVINCI_HEADER:
                consumedOpenDaVINCIContainerHeader = True
                byte0 = buf[0]
                byte1 = buf[1]

                # Check for OpenDaVINCI header.
                if ord(byte0) == int('0x0D',16) and ord(byte1) == int('0xA4',16):
                    v = struct.unpack('<L', buf[1:5]) # Read uint32_t and convert to little endian.
                    expectedBytes = v[0] >> 8 # The second byte belongs to OpenDaVINCI's Container header.
                    buf = "" # Reset buffer as we will read now the actual serialized data from Protobuf.
                else:
                    print "Failed to consume OpenDaVINCI container."

        # Read next byte.
        byte = f.read(1)
f.close()

# Print containers.
print "Found " + str(len(containers)) + " containers."
for cont in containers:
    printContainer(cont)

