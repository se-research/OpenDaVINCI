/**
 * OpenDaVINCI - Portable middleware for distributed components.
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

#ifndef MESSAGE_RESOLVER_H_
#define MESSAGE_RESOLVER_H_

#include <map>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/reflection/Helper.h"
#include "opendavinci/odcore/reflection/Message.h"

namespace odcore {
    namespace reflection {

        using namespace std;

        /**
         * Internal class to describe a .so helper.
         */
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
        class OPENDAVINCI_API MessageResolver {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                MessageResolver(const MessageResolver &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                MessageResolver& operator=(const MessageResolver &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param listOfAbsolutePathsToSearch List of absolute pathts to search for libraries.
                 * @param libraryPrefixToMatch Prefix to be matched for libraries to load, e.g. "libodvd".
                 * @param librarySuffixToMatch Suffix to be matched for libraries to load, e.g. ".so".
                 */
                MessageResolver(const vector<string> &listOfAbsolutePathsToSearch, const string &libraryPrefixToMatch, const string &librarySuffixToMatch);

                virtual ~MessageResolver();

                /**
                 * This methods tries to resolve the provided Container into a message.
                 *
                 * @param c Container to be resolved.
                 * @param successfullyMapped Boolean flag to indicate whether the mapping succeeded.
                 * @return Resolved message or empty message structure.
                 */
                odcore::reflection::Message resolve(odcore::data::Container &c, bool &successfullyMapped);

            private:
                void findAndLoadSharedLibraries();
                void unloadSharedLibraries();
                vector<string> getListOfLibrariesToLoad(const vector<string> &paths);

            private:
                string m_libraryPrefixToMatch;
                string m_librarySuffixToMatch;
                vector<string> m_listOfLibrariesToLoad;
                vector<HelperEntry> m_listOfHelpers;
                map<int32_t, HelperEntry> m_previouslyMatchedHelper;
        };

    }
} // odcore::reflection

#endif /*MESSAGE_RESOLVER_H_*/
