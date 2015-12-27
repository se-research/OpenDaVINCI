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

#ifndef CORE_ZLIBTESTSUITE_H_
#define CORE_ZLIBTESTSUITE_H_

#include <string>

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "core/strings/StringToolbox.h"
#include "core/wrapper/zlib/Zlib.h"

using namespace std;
using namespace core::wrapper::zlib;

class ZlibTest : public CxxTest::TestSuite {
    public:
        void testCompressionDecompression() {
            string input = "Gallia est omnis divisa in partes tres, quarum unam incolunt Belgae, aliam Aquitani, tertiam qui ipsorum lingua Celtae, nostra Galli appellantur. Hi omnes lingua, institutis, legibus inter se differunt.";

            string compressedOutput = Zlib::compress(input);
            TS_ASSERT(compressedOutput.size() > 0);

            string decompressedOutput = Zlib::decompress(compressedOutput);
            TS_ASSERT(decompressedOutput.size() > 0);

            TS_ASSERT(core::strings::StringToolbox::equalsIgnoreCase(input, decompressedOutput));
        }

};

#endif /*CORE_ZLIBTESTSUITE_H_*/
