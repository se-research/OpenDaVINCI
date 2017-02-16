/**
 * odlivefeed - Tool for printing content from containers to stdout in a user-readable representation.
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

#include <curses.h>

#include "LiveFeed.h"

namespace odlivefeed {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;

    LiveFeed::LiveFeed(const int32_t &argc, char **argv) :
        DataTriggeredConferenceClientModule(argc, argv, "odlivefeed") {}

    LiveFeed::~LiveFeed() {}

    void LiveFeed::setUp() {}

    void LiveFeed::tearDown() {}

    void LiveFeed::nextContainer(odcore::data::Container &c) {
        cout << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms() << "-->" << c.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms() << " dt = " << (c.getReceivedTimeStamp() - c.getSentTimeStamp()).toString() << " ID = " << c.getDataType() << endl; 
    }

} // odlivefeed
