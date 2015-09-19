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

        // Example:
        if (gcm.getIdentifier() == 0x78c) {
            // Position X.
            uint64_t data = gcm.getData();
            stringstream sstr((char*)(&data));
            double positionX = 0;
            sstr >> positionX;
            cout << "PositionX = " << positionX << endl;
        }

        return c;
    }

} // automotive
