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

#include "core/io/URLProtocol.h"
#include "core/strings/StringToolbox.h"

namespace core {
    namespace io {

        using namespace std;

        URLProtocol::URLProtocol() {}

        URLProtocol::~URLProtocol() {}

        URLProtocol::PROTOCOL URLProtocol::getProtocol(string &connection) {
            string connectionString = connection;

            // Transform to lower case for case insensitive searches.
            transform(connectionString.begin(), connectionString.end(), connectionString.begin(), ptr_fun(::tolower));
            core::strings::StringToolbox::trim(connectionString);

            // Trying to parse "file://" at position 0.
            if (connectionString.length() >= 7) {
                string::size_type pos = connectionString.find("file://");

                if (pos == 0) {
                    // Remove "file://" - part.
                    connection = connection.substr(7);
                    return FILEPROTOCOL;
                }
            }

            return UNKNOWNPROTOCOL;
        }

    }
} // core::io
