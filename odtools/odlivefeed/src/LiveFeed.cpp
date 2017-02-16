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

#ifdef HAVE_DL
    #include <dlfcn.h>
    #include <experimental/filesystem>
#endif

#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/reflection/Field.h>
#include <opendavinci/odcore/reflection/Message.h>
#include <opendavinci/odcore/strings/StringToolbox.h>
#include <opendavinci/GeneratedHeaders_OpenDaVINCI_Helper.h>
#include <automotivedata/GeneratedHeaders_AutomotiveData_Helper.h>

#include "LiveFeed.h"

namespace odlivefeed {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odcore::reflection;

    ////////////////////////////////////////////////////////////////////////////

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

    ////////////////////////////////////////////////////////////////////////////


    LiveFeed::LiveFeed(const int32_t &argc, char **argv) :
        DataTriggeredConferenceClientModule(argc, argv, "odlivefeed"),
        m_mainwindow(NULL),
        m_mapOfLastContainers(),
        m_listOfLibrariesToLoad(),
        m_listOfHelpers() {
        const string SEARCH_PATH = "/opt";
        const vector<string> paths = odcore::strings::StringToolbox::split(SEARCH_PATH, ',');
        m_listOfLibrariesToLoad = getListOfLibrariesToLoad(paths);

        findAndLoadSharedLibraries();
    }

    LiveFeed::~LiveFeed() {
        unloadSharedLibraries();
    }


    vector<string> LiveFeed::getListOfLibrariesToLoad(const vector<string> &paths) {
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
                    if (entry.find("libodvd") != string::npos) {
                        if (entry.find(".so") != string::npos) {
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

    void LiveFeed::findAndLoadSharedLibraries() {
#ifdef HAVE_DL
        auto it = m_listOfLibrariesToLoad.begin();
        while (it != m_listOfLibrariesToLoad.end()) {
            const string libraryToLoad = *it;

            {
                HelperEntry e;

                cout << "[LiveFeed] Opening '" + libraryToLoad + "'..." << endl;
                e.m_dynamicObjectHandle = dlopen(libraryToLoad.c_str(), RTLD_LAZY);

                if (!e.m_dynamicObjectHandle) {
                    cerr << "[LiveFeed] Cannot open library '" + libraryToLoad + "': " << dlerror() << endl;
                }
                else {
                    typedef odcore::reflection::Helper *createHelper_t();

                    // reset errors
                    dlerror();
                    createHelper_t* getHelper = (createHelper_t*) dlsym(e.m_dynamicObjectHandle, "newHelper");
                    const char *dlsym_error = dlerror();
                    if (dlsym_error) {
                        cerr << "[LiveFeed] Cannot load symbol 'newHelper' from '" + libraryToLoad + "': " << dlsym_error << endl;
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

    void LiveFeed::unloadSharedLibraries() {
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
                cerr << "[LiveFeed] Cannot load symbol 'deleteHelper': " << dlsym_error << endl;
            }
            else {
                cout << "[LiveFeed] Closing link to '" + e.m_library + "'" << endl;
                delHelper(e.m_helper);
            }
            dlclose(e.m_dynamicObjectHandle);

            it++;
        }
#endif
    }

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
            clear();
            m_mapOfLastContainers[c.getDataType()] = c;

            uint16_t row = 0;
            const uint16_t col = 0;
            for (auto it = m_mapOfLastContainers.begin(); it != m_mapOfLastContainers.end(); it++) {
                Container entry = it->second;
                stringstream sstr;

                // Try to extract messages.
                bool successfullyMapped = false;
                // First, try to decode a regular OpenDaVINCI message.
                odcore::reflection::Message msg = GeneratedHeaders_OpenDaVINCI_Helper::__map(entry, successfullyMapped);

                // Next, try to decode a regular OpenDaVINCI message.
                if (!successfullyMapped) {
                    msg = GeneratedHeaders_AutomotiveData_Helper::__map(entry, successfullyMapped);
                }

                // Try dynamically loaded libraries next.
                auto jt = m_listOfHelpers.begin();
                while ( (!successfullyMapped) && (jt != m_listOfHelpers.end())) {
                    HelperEntry e = *jt;
                    msg = e.m_helper->map(entry, successfullyMapped);
                    jt++;
                }

                if (successfullyMapped) {
                    sstr << "Container: " << entry.getDataType() << "/" << c.getSenderStamp() << ": " << " Sent: " << entry.getSentTimeStamp().getYYYYMMDD_HHMMSSms() << ", sample time: " << entry.getSampleTimeStamp().getYYYYMMDD_HHMMSSms() << ": " << msg.getLongName();
                }
                else {
                    sstr << "Container: " << entry.getDataType() << "/" << c.getSenderStamp() << ": " << " Sent: " << entry.getSentTimeStamp().getYYYYMMDD_HHMMSSms() << ", sample time: " << entry.getSampleTimeStamp().getYYYYMMDD_HHMMSSms();
                }

                const string text = sstr.str();
                mvaddstr(row++, col, text.c_str());
            }
            refresh();
        }
    }

} // odlivefeed
