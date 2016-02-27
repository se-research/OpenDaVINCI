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

#ifndef CORE_ZIPTESTSUITE_H_
#define CORE_ZIPTESTSUITE_H_

#include <fstream>                      // for stringstream, operator<<, etc
#include <string>                       // for string, operator==, etc
#include <vector>                       // for vector

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/wrapper/CompressionFactory.h"  // for CompressionFactory
#include "opendavinci/odcore/wrapper/DecompressedData.h"  // for DecompressedData

using namespace std;
using namespace odcore;

class ZipTest : public CxxTest::TestSuite {
    public:
        void testDecompression() {
            // Create zip file.
            stringstream archiveData;
            archiveData.str("80 75 3 4 10 0 0 0 0 0 -114 100 87 57 0 0 0 0 0 0 0 0 0 0 0 0 10 0 21 0 100 105 114 101 99 116 111 114 121 47 85 84 9 0 3 -85 83 0 73 -64 83 0 73 85 120 4 0 -24 3 -24 3 80 75 3 4 20 0 0 0 8 0 -114 100 87 57 -97 -108 -57 22 57 0 0 0 76 0 0 0 15 0 21 0 100 105 114 101 99 116 111 114 121 47 70 105 76 101 50 85 84 9 0 3 -85 83 0 73 -89 83 0 73 85 120 4 0 -24 3 -24 3 115 -55 76 45 86 -56 44 46 81 72 -51 -52 83 -88 42 79 -51 44 73 45 82 8 73 45 46 -47 -29 114 65 -110 74 -123 -54 41 68 -91 102 -26 -92 42 0 -43 -90 0 -43 65 -60 -14 20 92 18 75 82 51 -11 -72 0 80 75 3 4 20 0 0 0 8 0 118 100 87 57 3 -1 -119 86 40 0 0 0 47 0 0 0 5 0 21 0 102 105 108 101 49 85 84 9 0 3 127 83 0 73 127 83 0 73 85 120 4 0 -24 3 -24 3 115 -55 76 45 86 -56 44 46 81 72 -51 -52 83 8 73 45 46 -47 -29 114 65 18 74 85 -88 42 79 -51 44 73 85 -120 74 -51 -52 73 -43 -29 2 0 80 75 1 2 23 3 10 0 0 0 0 0 -114 100 87 57 0 0 0 0 0 0 0 0 0 0 0 0 10 0 13 0 0 0 0 0 0 0 16 0 -19 65 0 0 0 0 100 105 114 101 99 116 111 114 121 47 85 84 5 0 3 -85 83 0 73 85 120 0 0 80 75 1 2 23 3 20 0 0 0 8 0 -114 100 87 57 -97 -108 -57 22 57 0 0 0 76 0 0 0 15 0 13 0 0 0 0 0 1 0 0 0 -92 -127 61 0 0 0 100 105 114 101 99 116 111 114 121 47 70 105 76 101 50 85 84 5 0 3 -85 83 0 73 85 120 0 0 80 75 1 2 23 3 20 0 0 0 8 0 118 100 87 57 3 -1 -119 86 40 0 0 0 47 0 0 0 5 0 13 0 0 0 0 0 1 0 0 0 -92 -127 -72 0 0 0 102 105 108 101 49 85 84 5 0 3 127 83 0 73 85 120 0 0 80 75 5 6 0 0 0 0 3 0 3 0 -49 0 0 0 24 1 0 0 0 0");
            int32_t data = 0;
            fstream fout("ZipTest.zip", ios::binary | ios::out);
            while (archiveData.good()) {
                archiveData >> data;
                fout << (char)data;
            }
            fout.close();

            fstream fin("ZipTest.zip", ios::binary | ios::in);
            std::shared_ptr<odcore::wrapper::DecompressedData> dd = odcore::wrapper::CompressionFactory::getContents(fin);
            TS_ASSERT(dd.get());
            fin.close();

            vector<string> entries = dd->getListOfEntries();
            TS_ASSERT(entries.size() == 3);

            TS_ASSERT(entries.at(0) == "directory/");
            TS_ASSERT(entries.at(1) == "directory/file2");
            TS_ASSERT(entries.at(2) == "file1");

            std::shared_ptr<istream> stream = dd->getInputStreamFor("file1");
            TS_ASSERT(stream.get());
            if (stream.get()) {
                char c;
                stringstream decompressedData;
                while (stream->get(c)) {
                    decompressedData << c;
                }
                stringstream originalData;
                originalData << "Dies ist ein Test." << endl
                             << "Dies ist eine zweite Zeile." << endl;

                TS_ASSERT(decompressedData.str() == originalData.str());
            }

            stream = dd->getInputStreamFor("directory/file2");
            TS_ASSERT(stream.get());
            if (stream.get()) {
                char c;
                stringstream decompressedData;
                while (stream->get(c)) {
                    decompressedData << c;
                }
                stringstream originalData;
                originalData << "Dies ist ein zweiter Test." << endl
                             << "Dies ist eine zweite Zeile in der zweiten Datei." << endl;

                TS_ASSERT(decompressedData.str() == originalData.str());
            }

            stream = dd->getInputStreamFor("directory/non-existing-file");
            TS_ASSERT(!stream.get());

            UNLINK("ZipTest.zip");
        }

};

#endif /*CORE_ZIPTESTSUITE_H_*/
