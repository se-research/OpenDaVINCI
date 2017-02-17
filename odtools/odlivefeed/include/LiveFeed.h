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

#ifndef LIVEFEED_H_
#define LIVEFEED_H_

#include <curses.h>

#include <map>
#include <string>
#include <vector>

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/reflection/Helper.h>
#include <opendavinci/odcore/base/module/DataTriggeredConferenceClientModule.h>

namespace odlivefeed {

    using namespace std;

    class HelperEntry {
        public:
            HelperEntry(const HelperEntry &/*obj*/);
            HelperEntry& operator=(const HelperEntry &/*obj*/);

        public:
            HelperEntry();
            virtual ~HelperEntry();

        public:
            string m_library;
            void *m_dynamicObjectHandle;
            odcore::reflection::Helper *m_helper;
    };

    /**
     * This class can be used to simply display data distributed using a conference.
     */
    class LiveFeed : public odcore::base::module::DataTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            LiveFeed(const LiveFeed &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            LiveFeed& operator=(const LiveFeed &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            LiveFeed(const int32_t &argc, char **argv);

            virtual ~LiveFeed();

            virtual void nextContainer(odcore::data::Container &c);

        private:
            virtual void setUp();

            virtual void tearDown();

        private:
            WINDOW *m_mainwindow;
            map<int32_t, map<int32_t, odcore::data::Container> > m_mapOfLastContainers;

        private:
            void findAndLoadSharedLibraries();
            void unloadSharedLibraries();
            vector<string> getListOfLibrariesToLoad(const vector<string> &paths);

        private:
            vector<string> m_listOfLibrariesToLoad;
            vector<HelperEntry> m_listOfHelpers;

    };

} // odlivefeed

#endif /*LIVEFEED_H_*/
