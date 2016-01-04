/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <ctype.h>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include <sstream>

#include "zip.h"
#include "core/opendavinci.h"
#include "core/SharedPointer.h"
#include "core/base/module/AbstractCIDModule.h"
#include "core/wrapper/Zip/ZipDecompressedData.h"

namespace core {
    namespace wrapper {
        namespace Zip {

            using namespace std;
            using namespace core;
            using namespace core::strings;

            ZipDecompressedData::ZipDecompressedData(istream &in) :
                m_mapOfDecompressedEntries() {
                decompressData(in);
            }

            ZipDecompressedData::~ZipDecompressedData() {
                // Cleaning up the decompressed data entries.
                m_mapOfDecompressedEntries.clear();
            }

            void ZipDecompressedData::decompressData(istream &in) {
                // TODO: libzip needs a file to read from. Therefore, we need to buffer the istream...
                char *tempFileName;
#ifdef WIN32
                tempFileName = _tempnam("test", NULL);
#else
                tempFileName = strdup("tmpfileXXXXXX");
                if (mkstemp(tempFileName) == -1) {
                    CLOG3 << "ZipDecompressedData: temporary file cannot be created" << endl;
                }
#endif
                fstream fout(tempFileName, ios::binary | ios::out);

                if (fout.good()) {
                    char c = 0;
                    while (in.get(c)) {
                        fout << c;
                    }
                    fout.flush();
                    fout.close();

                    // Do decompression.
                    struct zip *zipArchive = NULL;

                    // Open the ZIP archive.
                    zipArchive = zip_open(tempFileName, 0, NULL);
                    if (zipArchive != NULL) {

                        // Get the number of compressed entries.
                        int32_t numberOfEntries = zip_get_num_files(zipArchive);
                        if (numberOfEntries > 0) {

                            // Allocate memory for decompression.
                            char *buffer = new char[ZipDecompressedData::BUFFER_SIZE];
                            if (buffer != NULL) {

                                // Start decompression.
                                for (int32_t i = 0; i < numberOfEntries; i++) {

                                    // Get i-th entry.
                                    const char *nameOfEntry = zip_get_name(zipArchive, i, 0);
                                    if (nameOfEntry != NULL) {
                                        string name(nameOfEntry);

                                        // Remove leading ./
                                        if ( (name.length() > 2) && (name.at(0) == '.') && (name.at(1) == '/') ) {
                                            name = string(nameOfEntry+2);
                                        }

                                        // Transform to lower case for case insensitive searches.
                                        transform(name.begin(), name.end(), name.begin(), ptr_fun(::tolower));

                                        // Get entry from zip file.
                                        struct zip_file *entry = zip_fopen_index(zipArchive, i, ZIP_FL_NOCASE);
                                        if (entry != NULL) {

                                            // Create stream for storing content.
                                            stringstream *stream = new stringstream();
                                            if (stream != NULL) {

                                                // Decompress data.
                                                int32_t nbytes = 0;
                                                while ( (nbytes = zip_fread(entry, buffer, ZipDecompressedData::BUFFER_SIZE)) > 0) {
                                                    string s(buffer, nbytes);
                                                    (*stream) << s;
                                                }

                                                // Store read content into map.
                                                m_mapOfDecompressedEntries[name] = SharedPointer<istream>(stream);
                                            }

                                            // Close entry.
                                            zip_fclose(entry);
                                        }
                                    }
                                }

                                // De-allocate memory.
                                delete [] buffer;
                            }
                        }

                        // Close given archive.
                        zip_close(zipArchive);
                    }
                }

#ifdef WIN32
                _unlink(tempFileName);
#else
                unlink(tempFileName);
#endif
                free(tempFileName);
            }

            vector<string> ZipDecompressedData::getListOfEntries() {
                vector<string> listOfEntries;

                map<string, SharedPointer<istream>, StringComparator>::const_iterator it = m_mapOfDecompressedEntries.begin();
                while (it != m_mapOfDecompressedEntries.end()) {
                    listOfEntries.push_back(it->first);
                    ++it;
                }

                return listOfEntries;
            }

            SharedPointer<istream> ZipDecompressedData::getInputStreamFor(const string &entry) {
                SharedPointer<istream> stream;

                string key = entry;
                // Transform key name to lower case for case insensitive lookups.
                transform(key.begin(), key.end(), key.begin(), ptr_fun(::tolower));

                // Try to find the key/value.
                map<string, SharedPointer<istream>, StringComparator>::const_iterator it = m_mapOfDecompressedEntries.find(key);
                if (it != m_mapOfDecompressedEntries.end()) {
                    stream = it->second;
                }

                return stream;
            }

        }
    }
} // core::wrapper::Zip
