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

#include <sstream>
#include <vector>

#include "core/io/URL.h"
#include "core/io/URLProtocol.h"

namespace core {
    namespace io {

        URL::URL(const string &connection) :
            m_valid(false),
            m_protocol(URLProtocol::UNKNOWNPROTOCOL),
            m_resource(connection) {
            // Parse protocol type and remove it from connection string.
            m_protocol = URLProtocol::getProtocol(m_resource);
            m_valid = (m_resource != connection) && (m_resource.length() > 0) && (m_protocol != URLProtocol::UNKNOWNPROTOCOL);
        }

        URL::URL(const URL &obj) :
            m_valid(obj.m_valid),
            m_protocol(obj.m_protocol),
            m_resource(obj.m_resource) {}

        URL::~URL() {}

        URL& URL::operator=(const URL &obj) {
            m_valid = obj.m_valid;
            m_protocol = obj.m_protocol;
            m_resource = obj.m_resource;

            return (*this);
        }

        bool URL::isValid() const {
            return m_valid;
        }

        URLProtocol::PROTOCOL URL::getProtocol() const {
            return m_protocol;
        }

        const string URL::getResource() const {
            return m_resource;
        }

        const string URL::toString() const {
            if (isValid()) {
                stringstream s;
                switch (getProtocol()) {
                    case URLProtocol::FILEPROTOCOL:
                        s << "file://" << getResource();
                        break;

                    case URLProtocol::UNKNOWNPROTOCOL:
                        // This case is unreachable.
                        break;

                    default:
                        // This case is unreachable.
                        break;
                }
                return s.str();
            }
            return "";
        }

    }
} // core::io
