/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2015 Christian Berger
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

#include "zlib.h"
#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/wrapper/zlib/Zlib.h"

namespace odcore {
    namespace wrapper {
        namespace zlib {

            using namespace std;

            Zlib::Zlib() {}

            Zlib::~Zlib() {}

            string Zlib::compress(const string &s) {
                string result;
                const uint32_t CHUNK = Zlib::BUFFER_SIZE;
                if (s.size() < CHUNK) {
                    int level = Z_DEFAULT_COMPRESSION;
                    int ret = 0, flush = 0;
                    unsigned int have = 0;
                    z_stream strm;
                    unsigned char out[CHUNK];

                    strm.zalloc = Z_NULL;
                    strm.zfree = Z_NULL;
                    strm.opaque = Z_NULL;
                    ret = deflateInit(&strm, level);
                    if (ret == Z_OK) {
                        strm.avail_in = s.size();
                        flush = Z_FINISH;
                        strm.next_in = (unsigned char*)(s.c_str());

                        strm.avail_out = CHUNK;
                        strm.next_out = out;
                        (void)deflate(&strm, flush);
                        have = CHUNK - strm.avail_out;
                        out[have] = 0;
                        result = string((const char*)out);
                        (void)deflateEnd(&strm);
                    }
                }
                return result;
            }

            string Zlib::decompress(const string &s) {
                string result;
                const uint32_t CHUNK = Zlib::BUFFER_SIZE;
                if (s.size() < CHUNK) {
                    int ret = 0;
                    unsigned int have = 0;
                    z_stream strm;
                    unsigned char out[CHUNK];

                    strm.zalloc = Z_NULL;
                    strm.zfree = Z_NULL;
                    strm.opaque = Z_NULL;
                    strm.avail_in = 0;
                    strm.next_in = Z_NULL;
                    ret = inflateInit(&strm);
                    if (ret == Z_OK) {
                        strm.avail_in = s.size();
                        strm.next_in = (unsigned char*)(s.c_str());
                        strm.avail_out = CHUNK;
                        strm.next_out = out;
                        
                        ret = inflate(&strm, Z_NO_FLUSH);
                        if (ret != Z_STREAM_ERROR) {
                            have = CHUNK - strm.avail_out;
                            out[have] = 0;
                            result = string((const char*)out);
                            (void)inflateEnd(&strm);
                        }
                    }
                }
                return result;
            }

        }
    }
} // odcore::wrapper::zlib

