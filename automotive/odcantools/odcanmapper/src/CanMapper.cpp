/**
 * odcanmapper - Tool for mapping GenericCANMessages to
 *               high-level C++ data structures and vice-versa
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
#include <vector>

#include "CanMapper.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/base/module/DataTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/data/Container.h"
#include "automotivedata/generated/automotive/GenericCANMessage.h"

namespace automotive {
    namespace odcantools {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;

        CanMapper::CanMapper(const int32_t &argc, char **argv) :
            DataTriggeredConferenceClientModule(argc, argv, "odcanmapper"),
            m_canMapping() {}

        CanMapper::~CanMapper() {}

        void CanMapper::setUp() {}

        void CanMapper::tearDown() {}

        void CanMapper::printPayload(uint64_t payload) const {
            const uint16_t LENGTH = 8;
            uint8_t val[LENGTH];
            for (uint8_t i = 0; i < LENGTH; i++) {
                val[i] = (payload & 0xFF);
                payload = payload >> 8;
            }
            cout << "Payload: " << hex << (int)val[0] << " "
                                << hex << (int)val[1] << " "
                                << hex << (int)val[2] << " "
                                << hex << (int)val[3] << " "
                                << hex << (int)val[4] << " "
                                << hex << (int)val[5] << " "
                                << hex << (int)val[6] << " "
                                << hex << (int)val[7] << endl;
        }
        void CanMapper::nextContainer(Container &c) {
            if (c.getDataType() == Container::GENERIC_CAN_MESSAGE) {
                GenericCANMessage gcm = c.getData<GenericCANMessage>();

                // Optionally: print payload for debug purposes.
                uint64_t data = gcm.getData();
                printPayload(data);

                vector<Container> listOfContainers = m_canMapping.mapNext(gcm);
                if (listOfContainers.size() > 0) {
                    vector<Container>::iterator it = listOfContainers.begin();
                    while (it != listOfContainers.end()) {
                        Container container = (*it++);
                        getConference().send(container);
                        Thread::usleepFor(100);
                    }
                }
            }
        }

    } // odcantools
} // automotive
