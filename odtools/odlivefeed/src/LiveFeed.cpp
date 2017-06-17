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

#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/data/TimeStamp.h>
#include <opendavinci/odcore/reflection/Message.h>
#include <opendavinci/odcore/strings/StringToolbox.h>

#include "LiveFeed.h"

namespace odlivefeed {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odcore::reflection;

    LiveFeed::LiveFeed(const int32_t &argc, char **argv) :
        DataTriggeredConferenceClientModule(argc, argv, "odlivefeed"),
        m_mainwindow(NULL),
        m_mapOfLastContainers(),
        m_messageResolver({"/opt"}, "libodvd", ".so") {}

    LiveFeed::~LiveFeed() {}

    void LiveFeed::setUp() {
        m_mainwindow = initscr();
        if (NULL == m_mainwindow) {
            cerr << "[odlivefeed] Error initializing ncurses." << endl;
        }
        if (has_colors()) {
            start_color();

            init_pair(1, COLOR_GREEN, COLOR_BLACK);
            init_pair(2, COLOR_YELLOW, COLOR_BLACK);
            init_pair(3, COLOR_RED, COLOR_BLACK);
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
            // Clear screen.
            clear();

            // Update two-dimensional hashmap for (dataType, senderStamp) --> c.
            map<int32_t, odcore::data::Container> entry = m_mapOfLastContainers[c.getDataType()];
            entry[c.getSenderStamp()] = c;
            m_mapOfLastContainers[c.getDataType()] = entry;

            uint16_t row = 0;
            const uint16_t col = 0;
            for (auto it = m_mapOfLastContainers.begin(); it != m_mapOfLastContainers.end(); it++) {
                entry = it->second;
                for (auto jt = entry.begin(); jt != entry.end(); jt++) {
                    Container containerEntry = jt->second;
                    stringstream sstr;

                    // Try to extract messages.
                    bool successfullyMapped = false;
                    odcore::reflection::Message msg = m_messageResolver.resolve(containerEntry, successfullyMapped);

                    if (successfullyMapped) {
                        sstr << "Container: " << containerEntry.getDataType() << "/" << containerEntry.getSenderStamp() << ": " << " Sent: " << containerEntry.getSentTimeStamp().getYYYYMMDD_HHMMSSms() << ", sample time: " << containerEntry.getSampleTimeStamp().getYYYYMMDD_HHMMSSms() << ": " << msg.getLongName();
                    }
                    else {
                        sstr << "Container: " << containerEntry.getDataType() << "/" << containerEntry.getSenderStamp() << ": " << " Sent: " << containerEntry.getSentTimeStamp().getYYYYMMDD_HHMMSSms() << ", sample time: " << containerEntry.getSampleTimeStamp().getYYYYMMDD_HHMMSSms();
                    }

                    const string text = sstr.str();
                    if (has_colors()) {
                        TimeStamp age = (c.getReceivedTimeStamp() - containerEntry.getReceivedTimeStamp());
                        if (age.toMicroseconds() <= 2*1000*1000) color_set(1, 0);
                        if ((age.toMicroseconds() > 2*1000*1000) && (age.toMicroseconds() <= 5*1000*1000)) color_set(2, 0);
                        if (age.toMicroseconds() > 5*1000*1000) color_set(3, 0);
                    }
                    mvaddstr(row++, col, text.c_str());
                }
            }
            refresh();
        }
    }

} // odlivefeed

