/**
 * canmapper - Tool for mapping GenericCANMessages to
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

#include "core/data/Container.h"
#include "core/data/TimeStamp.h"
#include "GeneratedHeaders_AutomotiveData.h"

#include "CanMapper.h"

namespace automotive {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    CanMapper::CanMapper(const int32_t &argc, char **argv) :
        DataTriggeredConferenceClientModule(argc, argv, "canmapper") {}

    CanMapper::~CanMapper() {}

    void CanMapper::setUp() {}

    void CanMapper::tearDown() {}

    void CanMapper::nextContainer(Container &c) {
        if (c.getDataType() == Container::GENERIC_CAN_MESSAGE) {
            GenericCANMessage gcm = c.getData<GenericCANMessage>();

            cout << "Received GenericCANMessage" <<
                                      " sent at " << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms() <<
                                  " received at " << c.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms() <<
                    ", " << gcm.toString() << endl;
        }
    }

} // automotive
