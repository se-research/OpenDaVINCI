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
#include <opendavinci/odcore/wrapper/SerialPort.h>
#include <opendavinci/odcore/wrapper/SerialPortFactory.h>

using namespace std;

// We add some of OpenDaVINCI's namespaces for the sake of readability.
using namespace odcore;
using namespace odcore::wrapper;

int32_t main(int32_t argc, char **argv) {
    const string SERIAL_PORT = "/dev/pts/19";
    const uint32_t BAUD_RATE = 19200;

    // We are using OpenDaVINCI's SharedPointer to automatically
    // release any acquired resources.
    try {
        SharedPointer<SerialPort> serial(SerialPortFactory::createSerialPort(SERIAL_PORT, BAUD_RATE));

        serial->send("Hello World\r\n");
    }
    catch(string &exception) {
        cerr << "Serial port could not be created: " << exception << endl;
    }
}

