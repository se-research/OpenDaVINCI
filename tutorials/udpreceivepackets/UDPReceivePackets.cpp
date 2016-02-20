/**
 * OpenDaVINCI - Tutorial.
 * Copyright (C) 2015 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdint.h>
#include <iostream>
#include <string>
#include <opendavinci/odcore/SharedPointer.h>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/odcore/io/Packet.h>
#include <opendavinci/odcore/io/udp/UDPReceiver.h>
#include <opendavinci/odcore/io/udp/UDPFactory.h>

#include "UDPReceivePackets.hpp"

using namespace std;

void UDPReceivePackets::nextPacket(const odcore::io::Packet &p) {
    cout << "Received a packet from " << p.getSender() << ", "
         << "with " << p.getData().length() << " bytes containing '"
         << p.getData() << "'" << endl;
}

// We add some of OpenDaVINCI's namespaces for the sake of readability.
using namespace odcore;
using namespace odcore::io;
using namespace odcore::io::udp;

int32_t main(int32_t argc, char **argv) {
    const string RECEIVER = "0.0.0.0";
    const uint32_t PORT = 1234;

    // We are using OpenDaVINCI's SharedPointer to automatically
    // release any acquired resources.
    try {
        SharedPointer<UDPReceiver>
            udpreceiver(UDPFactory::createUDPReceiver(RECEIVER, PORT));

        // This instance will handle any packets that are received
        // by our UDP socket.
        UDPReceivePackets handler;
        udpreceiver->setPacketListener(&handler);

        // Start receiving bytes.
        udpreceiver->start();

        const uint32_t ONE_SECOND = 1000 * 1000;
        odcore::base::Thread::usleepFor(10 * ONE_SECOND);

        // Stop receiving bytes and unregister our handler.
        udpreceiver->stop();
        udpreceiver->setPacketListener(NULL);
    }
    catch(string &exception) {
        cerr << "Error while creating UDP receiver: " << exception << endl;
    }
}

