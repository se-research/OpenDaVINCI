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

#ifdef HAVE_DL
    #include <dlfcn.h>
    #include <experimental/filesystem>
#endif

#define FUSE_USE_VERSION 26
#include <fuse.h>
#include <cstring>
#include <cerrno>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/GeneratedHeaders_OpenDaVINCI_Helper.h>
#include <opendavinci/odcore/reflection/Message.h>
#include <opendavinci/odcore/reflection/MessagePrettyPrinterVisitor.h>
#include <opendavinci/odcore/strings/StringToolbox.h>

#include "Rec2Fuse.h"

////////////////////////////////////////////////////////////////////////////////

std::map<int32_t, uint32_t> mapOfEntrySizes;
std::map<int32_t, std::string> mapOfEntries;

//static const char *filepath = "/file";
//static const char *filename = "file";
static const char *filecontent = "I'm the content of the only file available there\n";

static int getattr_callback(const char *path, struct stat *stbuf) {
  memset(stbuf, 0, sizeof(struct stat));

  if (strcmp(path, "/") == 0) {
    stbuf->st_mode = S_IFDIR | 0755;
    stbuf->st_nlink = 2;
    return 0;
  }

  std::string FQDN = "/19.data";
  if (strcmp(path, FQDN.c_str()) == 0) {
    stbuf->st_mode = S_IFREG | 0777;
    stbuf->st_nlink = 1;
    stbuf->st_size = strlen(filecontent);//mapOfEntrySizes[19];
    return 0;
  }

  return -ENOENT;
}

static int readdir_callback(const char */*path*/, void *buf, fuse_fill_dir_t filler,
    off_t offset, struct fuse_file_info *fi) {
  (void) offset;
  (void) fi;

  filler(buf, ".", NULL, 0);
  filler(buf, "..", NULL, 0);

  std::string FQDN = "/19.data";
  filler(buf, FQDN.c_str()+1, NULL, 0);

  return 0;
}

static int open_callback(const char */*path*/, struct fuse_file_info */*fi*/) {
  return 0;
}

static int read_callback(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info */*fi*/) {

  std::string FQDN = "/19.data";
  if (strcmp(path, FQDN.c_str()) == 0) {
    size_t len = strlen(filecontent);
    if (offset >= static_cast<int32_t>(len)) {
      return 0;
    }

    if (offset + size > len) {
      memcpy(buf, filecontent + offset, len - offset);
      return len - offset;
    }

    memcpy(buf, filecontent + offset, size);
    return size;
  }

  return -ENOENT;
}


static struct fuse_operations fuse_example_operations;

////////////////////////////////////////////////////////////////////////////////

namespace odrec2fuse {

    using namespace std;
    using namespace odcore;
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

    Rec2Fuse::Rec2Fuse() :
        m_listOfLibrariesToLoad(),
        m_listOfHelpers() {
        const string SEARCH_PATH = "/opt";
        const vector<string> paths = odcore::strings::StringToolbox::split(SEARCH_PATH, ',');
        m_listOfLibrariesToLoad = getListOfLibrariesToLoad(paths);

        findAndLoadSharedLibraries();
    }

    Rec2Fuse::~Rec2Fuse() {
        unloadSharedLibraries();
    }

    vector<string> Rec2Fuse::getListOfLibrariesToLoad(const vector<string> &paths) {
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

    void Rec2Fuse::findAndLoadSharedLibraries() {
#ifdef HAVE_DL
        auto it = m_listOfLibrariesToLoad.begin();
        while (it != m_listOfLibrariesToLoad.end()) {
            const string libraryToLoad = *it;

            {
                HelperEntry e;

                cout << "[Rec2Fuse] Opening '" + libraryToLoad + "'..." << endl;
                e.m_dynamicObjectHandle = dlopen(libraryToLoad.c_str(), RTLD_LAZY);

                if (!e.m_dynamicObjectHandle) {
                    cerr << "[Rec2Fuse] Cannot open library '" + libraryToLoad + "': " << dlerror() << endl;
                }
                else {
                    typedef odcore::reflection::Helper *createHelper_t();

                    // reset errors
                    dlerror();
                    createHelper_t* getHelper = (createHelper_t*) dlsym(e.m_dynamicObjectHandle, "newHelper");
                    const char *dlsym_error = dlerror();
                    if (dlsym_error) {
                        cerr << "[Rec2Fuse] Cannot load symbol 'newHelper' from '" + libraryToLoad + "': " << dlsym_error << endl;
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

    void Rec2Fuse::unloadSharedLibraries() {
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
                cerr << "[Rec2Fuse] Cannot load symbol 'deleteHelper': " << dlsym_error << endl;
            }
            else {
                cout << "[Rec2Fuse] Closing link to '" + e.m_library + "'" << endl;
                delHelper(e.m_helper);
            }
            dlclose(e.m_dynamicObjectHandle);

            it++;
        }
#endif
    }

    int32_t Rec2Fuse::run(const int32_t &argc, char **argv) {
        uint32_t mappedContainers = 0;

        ::mapOfEntrySizes.clear();
        ::mapOfEntries.clear();

        if (argc > 1) {
            const string FILENAME(argv[1]);
            fstream fin;
            fin.open(FILENAME.c_str(), ios_base::in|ios_base::binary);

            if (fin.good()) {
                // Determine file size.
                fin.seekg(0, fin.end);
                int32_t length = fin.tellg();
                fin.seekg(0, fin.beg);

                int32_t oldPercentage = -1;

                while (fin.good()) {
                    Container c;
                    fin >> c;

                    if (fin.gcount() > 0) {
                        int32_t currPos = fin.tellg();
                        float percentage = (float)(currPos*100.0)/(float)length;

                        if ( ((int32_t)percentage % 5 == 0) && ((int32_t)percentage != oldPercentage) ) {
                            cout << "[Rec2Fuse]: " << (int32_t)percentage << "% (" << currPos << "/" << length << " bytes processed)." << endl;
                            oldPercentage = (int32_t)percentage;
                        }

                        bool successfullyMapped = false;
                        odcore::reflection::Message msg;
                        auto it = m_listOfHelpers.begin();
                        while ( (!successfullyMapped) && (it != m_listOfHelpers.end())) {
                            HelperEntry e = *it;
                            msg = e.m_helper->map(c, successfullyMapped);
                            it++;

                            if (successfullyMapped) {
                                cout << "Mapped " << c.getDataType() << " using " << e.m_library << endl;
                                mappedContainers++;

                                stringstream sstr;

                                MessagePrettyPrinterVisitor mppv;
                                msg.accept(mppv);
                                mppv.getOutput(sstr);

                                string s = mapOfEntries[c.getDataType()] + sstr.str();
                                mapOfEntries[c.getDataType()] = s;
                                mapOfEntrySizes[c.getDataType()] = s.size();
                            }
                        }
                        if (mappedContainers > 20) {
                            break;
                        }
                    }
                }
            }
        }

        for(auto entry : mapOfEntries) {
            cout << "K = " << entry.first << ", V = " << entry.second << endl;
        }

        fuse_example_operations.getattr = getattr_callback;
        fuse_example_operations.open = open_callback;
        fuse_example_operations.read = read_callback;
        fuse_example_operations.readdir = readdir_callback;

        vector<string> args;
        for (int32_t i = 0; i < argc; i++) {
            if (i != 1) {
                args.push_back(string(argv[i]));
            }
        }

        char **argv2 = new char*[args.size()];
        for (uint32_t i = 0; i < args.size(); i++) {
            argv2[i] = const_cast<char*>(args[i].c_str());
        }

        return fuse_main(argc-1, argv2, &fuse_example_operations, NULL);
    }

} // odrec2fuse

