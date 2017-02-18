/**
 * odmongodb - Tool for dumping received containers after message resolving into a MongoDB.
 * Copyright (C) 2017 Christian Berger
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
#include <sstream>

#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/data/TimeStamp.h>
#include <opendavinci/odcore/reflection/Message.h>
#include <opendavinci/odcore/strings/StringToolbox.h>

#include "Dump2MongoDB.h"

namespace odmongodb {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odcore::reflection;

    Dump2MongoDB::Dump2MongoDB(const int32_t &argc, char **argv) :
        DataTriggeredConferenceClientModule(argc, argv, "odmongodb"),
        m_messageResolver({"/opt"}, "libodvd", ".so") {}

    Dump2MongoDB::~Dump2MongoDB() {}

    void Dump2MongoDB::setUp() {
        // TODO: Initialize and open MongoDB.
    }

    void Dump2MongoDB::tearDown() {
        // TODO: Close MongoDB.
    }

    void Dump2MongoDB::nextContainer(odcore::data::Container &c) {
        // Try to extract messages.
        bool successfullyMapped = false;
        odcore::reflection::Message msg = m_messageResolver.resolve(c, successfullyMapped);

        if (successfullyMapped) {
            cout << "Container: " << c.getDataType() << "/" << c.getSenderStamp() << ": " << " Sent: " << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms() << ", sample time: " << c.getSampleTimeStamp().getYYYYMMDD_HHMMSSms() << ": " << msg.getLongName() << endl;
        }
    }

} // odmongodb

