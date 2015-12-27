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

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sstream>

#include "core/exceptions/Exceptions.h"

namespace core {
    namespace exceptions {

        using namespace std;

        Exceptions::Exceptions(const string &exceptionMessage, const string &fileName, const uint32_t &lineNumber) :
            m_message(exceptionMessage),
            m_fileName(fileName),
            m_lineNumber(lineNumber),
            m_whatMessage(NULL) {
            if (exceptionMessage.size() == 0) {
                m_message = "unknown exception message";
            }

            // Try to get the error's reason.
            if (errno != 0) {
#ifdef WIN32
                char buffer[1024];
                strerror_s(buffer, 1024, errno);
                string errorMessage(buffer);
#else
                string errorMessage(strerror(errno));
#endif
                m_message += ": " + errorMessage;
            }
        }

        Exceptions::~Exceptions() throw () {
            OPENDAVINCI_CORE_FREE_POINTER(m_whatMessage);
        }

        Exceptions::Exceptions(const Exceptions& obj) :
            exception(obj),
            m_message(obj.getMessage()),
            m_fileName(obj.getFileName()),
            m_lineNumber(obj.getLineNumber()),
            m_whatMessage(NULL) {}

        Exceptions& Exceptions::operator=(const Exceptions& obj) {
            exception::operator=(obj);
            OPENDAVINCI_CORE_FREE_POINTER(m_whatMessage);

            m_message = obj.getMessage();
            m_fileName = obj.getFileName();
            m_lineNumber = obj.getLineNumber();

            return *this;
        }

        const char* Exceptions::what() const throw () {
            if (m_whatMessage == NULL) {
                // strdup creates a pointer to NEW memory area.
#ifdef WIN32
                m_whatMessage = ::_strdup(toString().c_str());
#else
                m_whatMessage = ::strdup(toString().c_str());
#endif
            }
            return m_whatMessage;
        }

        const string Exceptions::toString() const {
            ostringstream out;
            out << getExceptionName() << ": " << getMessage() << " at " << getFileName() << ": " << getLineNumber();
            return out.str();
        }

        const string Exceptions::getMessage() const {
            return m_message;
        }

        const string Exceptions::getFileName() const {
            return m_fileName;
        }

        uint32_t Exceptions::getLineNumber() const {
            return m_lineNumber;
        }

    }
} // core::exceptions
