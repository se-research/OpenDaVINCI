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
#include <opendavinci/core/SharedPointer.h>
#include <opendavinci/core/base/Thread.h>
#include <opendavinci/core/wrapper/SerialPort.h>
#include <opendavinci/core/wrapper/SerialPortFactory.h>

#include "SerialReceiveBytes.hpp"

using namespace std;

void SerialReceiveBytes::nextString(const string &s) {
    cout << "Received " << s.length() << " bytes containing '" << s << "'" << endl;
}

// We add some of OpenDaVINCI's namespaces for the sake of readability.
using namespace core;
using namespace core::wrapper;

int32_t main(int32_t argc, char **argv) {
    const string SERIAL_PORT = "/dev/pts/20";
    const uint32_t BAUD_RATE = 19200;

    // We are using OpenDaVINCI's SharedPointer to automatically
    // release any acquired resources.
    try {
        SharedPointer<SerialPort>
            serial(SerialPortFactory::createSerialPort(SERIAL_PORT, BAUD_RATE));

        // This instance will handle any bytes that are received
        // from our serial port.
        SerialReceiveBytes handler;
        serial->setStringListener(&handler);

        // Start receiving bytes.
        serial->start();

        const uint32_t ONE_SECOND = 1000 * 1000;
        core::base::Thread::usleepFor(10 * ONE_SECOND);

        // Stop receiving bytes and unregister our handler.
        serial->stop();
        serial->setStringListener(NULL);
    }
    catch(string &exception) {
        cerr << "Error while creating serial port: " << exception << endl;
    }
}

