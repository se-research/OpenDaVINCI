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

#include <iostream>

#ifdef HAVE_DL
    #include <dlfcn.h>
    #include <experimental/filesystem>
#endif

#include "opendavinci/odcore/reflection/MessageResolver.h"
#include "opendavinci/odcore/strings/StringToolbox.h"
#include "opendavinci/GeneratedHeaders_OpenDaVINCI_Helper.h"

namespace odcore {
    namespace reflection {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;

        ////////////////////////////////////////////////////////////////////////

        HelperEntry::HelperEntry() : 
             m_library(""),
             m_dynamicObjectHandle(NULL),
             m_helper(NULL)
        {}

        HelperEntry::HelperEntry(const HelperEntry &obj) :
            m_library(obj.m_library),
            m_dynamicObjectHandle(obj.m_dynamicObjectHandle),
            m_helper(obj.m_helper)
        {}

        HelperEntry& HelperEntry::operator=(const HelperEntry &obj) {
            m_library = obj.m_library;
            m_dynamicObjectHandle = obj.m_dynamicObjectHandle;
            m_helper = obj.m_helper;
            return *this;
        }

        HelperEntry::~HelperEntry() {}

        ////////////////////////////////////////////////////////////////////////

        MessageResolver::MessageResolver(const vector<string> &listOfAbsolutePathsToSearch, const string &libraryPrefixToMatch, const string &librarySuffixToMatch) :
            m_libraryPrefixToMatch(libraryPrefixToMatch),
            m_librarySuffixToMatch(librarySuffixToMatch),
            m_listOfLibrariesToLoad(),
            m_listOfHelpers(),
            m_previouslyMatchedHelper() {
            m_listOfLibrariesToLoad = getListOfLibrariesToLoad(listOfAbsolutePathsToSearch);
            findAndLoadSharedLibraries();
        }

        MessageResolver::~MessageResolver() {
            unloadSharedLibraries();
        }

        vector<string> MessageResolver::getListOfLibrariesToLoad(const vector<string> &paths) {
            vector<string> librariesToLoad;
#ifndef HAVE_DL
            (void)paths;
#endif

#ifdef HAVE_DL
            for(auto pathToSearch : paths) {
                try {
                    for(auto &pathElement : std::experimental::filesystem::recursive_directory_iterator(pathToSearch)) {
                        stringstream sstr;
                        sstr << pathElement;
                        string entry = sstr.str();
                        if (entry.find(m_libraryPrefixToMatch) != string::npos) {
                            if (entry.find(m_librarySuffixToMatch) != string::npos) {
                                vector<string> path = odcore::strings::StringToolbox::split(entry, '/');
                                if (path.size() > 0) {
                                    string lib = path[path.size()-1];
                                    if (lib.size() > 0) {
                                        lib = lib.substr(0, lib.size()-1);
                                        librariesToLoad.push_back(lib);
                                    }
                                }
                            }
                        }
                    }
                }
                catch(...) {}
            }
#endif
            return librariesToLoad;
        }

        void MessageResolver::findAndLoadSharedLibraries() {
#ifdef HAVE_DL
            auto it = m_listOfLibrariesToLoad.begin();
            while (it != m_listOfLibrariesToLoad.end()) {
                const string libraryToLoad = *it;

                {
                    HelperEntry e;

                    cout << "[odcore::reflection::MessageResolver] Opening '" + libraryToLoad + "'..." << endl;
                    e.m_dynamicObjectHandle = dlopen(libraryToLoad.c_str(), RTLD_LAZY);

                    if (!e.m_dynamicObjectHandle) {
                        cerr << "[odcore::reflection::MessageResolver] Cannot open library '" + libraryToLoad + "': " << dlerror() << endl;
                    }
                    else {
                        typedef odcore::reflection::Helper *createHelper_t();

                        // Reset errors.
                        dlerror();
                        createHelper_t* getHelper = (createHelper_t*) dlsym(e.m_dynamicObjectHandle, "newHelper");
                        const char *dlsym_error = dlerror();
                        if (dlsym_error) {
                            cerr << "[odcore::reflection::MessageResolver] Cannot load symbol 'newHelper' from '" + libraryToLoad + "': " << dlsym_error << endl;
                            dlclose(e.m_dynamicObjectHandle);
                        }
                        else {
                            // Get pointer to external message handling.
                            e.m_helper = getHelper();
                            e.m_library = libraryToLoad;
                            m_listOfHelpers.push_back(e);
                        }
                    }
                }

                it++;
            }
#endif
        }

        void MessageResolver::unloadSharedLibraries() {
#ifdef HAVE_DL
            auto it = m_listOfHelpers.begin();
            while (it != m_listOfHelpers.end()) {
                HelperEntry e = *it;

                // Type to refer to the destroy method inside the shared library.
                typedef void deleteHelper_t(odcore::reflection::Helper *);

                // Reset error messages from dynamically loading shared object.
                dlerror();
                deleteHelper_t* delHelper = (deleteHelper_t*) dlsym(e.m_dynamicObjectHandle, "deleteHelper");
                const char *dlsym_error = dlerror();
                if (dlsym_error) {
                    cerr << "[odcore::reflection::MessageResolver] Cannot load symbol 'deleteHelper': " << dlsym_error << endl;
                }
                else {
                    cout << "[odcore::reflection::MessageResolver] Closing link to '" + e.m_library + "'" << endl;
                    delHelper(e.m_helper);
                }
                dlclose(e.m_dynamicObjectHandle);

                it++;
            }
#endif
        }

        Message MessageResolver::resolve(Container &c, bool &successfullyMapped) {
            // Assuming that the resolving will fail.
            successfullyMapped = false;
            odcore::reflection::Message retVal;

            // Check if this container type has been resolved successfully previously.
            if (m_previouslyMatchedHelper.count(c.getDataType()) > 0) {
                retVal = m_previouslyMatchedHelper[c.getDataType()].m_helper->map(c, successfullyMapped);
            }
            else {
                // First, try to decode a regular OpenDaVINCI message.
                retVal = GeneratedHeaders_OpenDaVINCI_Helper::__map(c, successfullyMapped);

                if (!successfullyMapped) {
                    // Try dynamically loaded libraries next.
                    auto it = m_listOfHelpers.begin();
                    while ( (!successfullyMapped) && (it != m_listOfHelpers.end())) {
                        HelperEntry e = *it;
                        retVal = e.m_helper->map(c, successfullyMapped);
                        if (successfullyMapped) {
                            m_previouslyMatchedHelper[c.getDataType()] = e;
                        }
                        it++;
                    }
                }
            }

            return retVal;
        }

    }
} // odcore::reflection

