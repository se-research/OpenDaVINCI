/**
 * DataMapper - Tool for mapping GenericCANMessages to
 *             high-level C++ data structures and vice-versa
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

#include "DataMapper.h"

namespace automotive {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    DataMapper::DataMapper() {}

    DataMapper::~DataMapper() {}

    Container DataMapper::mapNext(const GenericCANMessage &gcm) {
        Container c;

        cout << "Received GenericCANMessage" <<
                                  " sent at " << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms() <<
                              " received at " << c.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms() <<
                ", " << gcm.toString() << endl;

        // TODO: Serve internal state machines and return valid container (i.e. Container::UNDEFINEDDATA)
        //       or just the incomplete Container as default.

        // Wheel speed example.
        if (gcm.getIdentifier() == 0x123) {
            uint64_t data = gcm.getData();

//            uint64_t data2 = data;
//            uint8_t val2[8];
//            for (uint8_t i = 0; i < gcm.getLength(); i++) {
//                val2[i] = (data2 & 0xFF);
//                data2 = data2 >> 8;
//            }
//            cout << "Data2: " << hex << (int)val2[0] << " "
//                              << hex << (int)val2[1] << " "
//                              << hex << (int)val2[2] << " "
//                              << hex << (int)val2[3] << " "
//                              << hex << (int)val2[4] << " "
//                              << hex << (int)val2[5] << " "
//                              << hex << (int)val2[6] << " "
//                              << hex << (int)val2[7] << endl;

            // Map uin64_t value to 8 byte char array.
            string value((char*)(&data), 8);
            stringstream sstr(value);
            uint16_t _wheel1 = 0; double wheel1 = 0.01;
            uint16_t _wheel2 = 0; double wheel2 = 0.01;
            uint16_t _wheel3 = 0; double wheel3 = 0.01;
            uint16_t _wheel4 = 0; double wheel4 = 0.01;

            sstr.read((char*)&_wheel1, sizeof(uint16_t));
            _wheel1 = ntohs(_wheel1); wheel1 *= _wheel1;

            sstr.read((char*)&_wheel2, sizeof(uint16_t));
            _wheel2 = ntohs(_wheel2); wheel2 *= _wheel2;

            sstr.read((char*)&_wheel3, sizeof(uint16_t));
            _wheel3 = ntohs(_wheel3); wheel3 *= _wheel3;

            sstr.read((char*)&_wheel4, sizeof(uint16_t));
            _wheel4 = ntohs(_wheel4); wheel4 *= _wheel4;

            cout << "wheel1 = " << wheel1 << ", wheel2 = " << wheel2 << ", wheel3 = " << wheel3 << ", wheel4 = " << wheel4 << endl;
        }

        return c;
    }

} // automotive
