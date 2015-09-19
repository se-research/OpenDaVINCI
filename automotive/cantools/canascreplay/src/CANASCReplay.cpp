/**
 * canascreplay - Tool to replay from an ASC file.
 * Copyright (C) 2015 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <iostream>

#include <core/data/Container.h>
#include <core/strings/StringToolbox.h>
#include <GeneratedHeaders_AutomotiveData.h>

#include "CANASCReplay.h"

namespace automotive {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace core::strings;

    CANASCReplay::CANASCReplay(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "canascreplay") {}

    CANASCReplay::~CANASCReplay() {}

    void CANASCReplay::setUp() {}

    void CANASCReplay::tearDown() {}

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode CANASCReplay::body() {
        // Structure of an ASC entry: 'Timestamp Channel  ID             Rx   d Length 00 11 22 33 44 55 66 77'
        char buffer[100];
        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
            // Read next line from STDIN.
            cin.getline(buffer, 100);

            // Tokenize the read line.
            vector<string> tokens = StringToolbox::split(string(buffer), ' ');

            // Do we have a valid line?
            if ( (tokens.size() >= 7) &&
                 (StringToolbox::equalsIgnoreCase(tokens[3], "rx")) ) {
                // Read CAN identifier.
                stringstream _identifier;
                uint64_t identifier = 0;
                _identifier << tokens[2]; _identifier >> hex >> identifier;

                // Read payload length (1-8).
                stringstream _length;
                uint16_t length = 0;
                _length << tokens[5]; _length >> dec >> length;

                // Read payload.
                uint64_t data = 0;
                for (uint16_t i = 0; i < length; i++) {
                    // Put next data byte into stringstream.
                    stringstream _data;
                    _data << tokens[6 + i];

                    // Read next data byte.
                    uint16_t value = 0;
                    _data >> hex >> value;
                    data |= (static_cast<uint64_t>(value) << (i*8));
                }

                // Create GenericCANMessage.
                GenericCANMessage gcm;
                gcm.setIdentifier(identifier);
                gcm.setLength(length);
                gcm.setData(data);
                cout << gcm.toString() << endl;

                uint64_t data2 = gcm.getData();
                uint8_t val2[8];
                for (uint8_t i = 0; i < length; i++) {
                    val2[i] = (data2 & 0xFF);
                    data2 = data2 >> 8;
                }
                cout << "Data2: " << hex << (int)val2[0] << " "
                                  << hex << (int)val2[1] << " "
                                  << hex << (int)val2[2] << " "
                                  << hex << (int)val2[3] << " "
                                  << hex << (int)val2[4] << " "
                                  << hex << (int)val2[5] << " "
                                  << hex << (int)val2[6] << " "
                                  << hex << (int)val2[7] << endl;
            }
        }

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // automotive
