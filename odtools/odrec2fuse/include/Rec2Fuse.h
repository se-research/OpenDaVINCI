/**
 * odrec2fuse - Mounting .rec files via Fuse into a directory.
 * Copyright (C) 2016 Christian Berger
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

#ifndef REC2FUSE_H_
#define REC2FUSE_H_

#include <string>
#include <vector>

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/reflection/Helper.h>

namespace odrec2fuse {

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
     * This class can be used to mount a .rec file into a directory.
     */
    class Rec2Fuse {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Rec2Fuse(const Rec2Fuse &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Rec2Fuse& operator=(const Rec2Fuse &/*obj*/);

        public:
            Rec2Fuse();

            virtual ~Rec2Fuse();

            /**
             * This method validates a specified file regarding integrity.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             * @return 0 if specified file is integer, 1 if the file is not integer, and 255 if the file could not be opened.
             */
            int32_t run(const int32_t &argc, char **argv);

        private:
            void findAndLoadSharedLibraries();
            void unloadSharedLibraries();
            vector<string> getListOfLibrariesToLoad(const vector<string> &paths);

        private:
            vector<string> m_listOfLibrariesToLoad;
            vector<HelperEntry> m_listOfHelpers;
    };

} // odrec2fuse

#endif /*REC2FUSE_H_*/
