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
#include <sstream>

#include "LiveFeed.h"

namespace odlivefeed {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;

    LiveFeed::LiveFeed(const int32_t &argc, char **argv) :
        DataTriggeredConferenceClientModule(argc, argv, "odlivefeed"),
        m_mainwindow(NULL),
        m_mapOfLastContainers() {}

    LiveFeed::~LiveFeed() {}

    void LiveFeed::setUp() {
        m_mainwindow = initscr();
        if (NULL == m_mainwindow) {
            cerr << "[odlivefeed] Error initializing ncurses." << endl;
        }
    }

    void LiveFeed::tearDown() {
        if (NULL != m_mainwindow) {
            delwin(m_mainwindow);
            endwin();
            refresh();
        }
    }

    void LiveFeed::nextContainer(odcore::data::Container &c) {
        if (NULL != m_mainwindow) {
            m_mapOfLastContainers[c.getDataType()] = c;

            uint16_t row = 0;
            const uint16_t col = 0;
            for (auto it = m_mapOfLastContainers.begin(); it != m_mapOfLastContainers.end(); it++) {
                Container entry = it->second;
                stringstream sstr;
                sstr << "Container: " << entry.getDataType() << ", sent: " << entry.getSentTimeStamp().getYYYYMMDD_HHMMSSms() << ", received: " << entry.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms() << ", sample time: " << entry.getSampleTimeStamp().getYYYYMMDD_HHMMSSms();
                const string text = sstr.str();
                mvaddstr(row++, col, text.c_str());
            }

            refresh();
        }
    }

} // odlivefeed
