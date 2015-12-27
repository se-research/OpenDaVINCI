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

#include <stddef.h>
#include <ostream>
#include <string>

#include "core/base/Lock.h"
#include "core/exceptions/Exceptions.h"
#include "core/io/StreamFactory.h"
#include "core/io/URLProtocol.h"
#include "core/macros.h"

namespace core {
    namespace io {

        using namespace std;
        using namespace core;
        using namespace core::base;
        using namespace core::exceptions;

        // Initialize singleton instance.
        Mutex StreamFactory::m_singletonMutex;
        StreamFactory* StreamFactory::m_singleton = NULL;

        StreamFactory::StreamFactory() :
            m_listOfInputStreams(),
            m_listOfOutputStreams() {}

        StreamFactory::~StreamFactory() {
            // Clean up input streams.
            m_listOfInputStreams.clear();

            // Clean up output streams.
            m_listOfOutputStreams.clear();

            StreamFactory::m_singleton = NULL;
        }

        StreamFactory& StreamFactory::getInstance() {
            {
                Lock l(StreamFactory::m_singletonMutex);
                if (StreamFactory::m_singleton == NULL) {
                    StreamFactory::m_singleton = new StreamFactory();
                }
            }

            return (*StreamFactory::m_singleton);
        }

        SharedPointer<istream> StreamFactory::getInputStream(const URL &url) throw (InvalidArgumentException) {
            if (!url.isValid()) {
                stringstream s;
                s << "Given URL: " << url.toString() << " is invalid.";
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, s.str());
            }

            istream *in = NULL;
            if (url.getProtocol() == URLProtocol::FILEPROTOCOL) {
                in = new fstream(url.getResource().c_str(), ios::in | ios::binary);

                if (!in->good()) {
                    (dynamic_cast<fstream*>(in))->close();
                    OPENDAVINCI_CORE_DELETE_POINTER(in);
                }
            }

            if (in == NULL) {
                stringstream s;
                s << "No input stream created for the given URL: " << url.toString() << ".";
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, s.str());
            }

            SharedPointer<istream> streamIn(in);
            m_listOfInputStreams.push_back(streamIn);
            return streamIn;
        }

        SharedPointer<ostream> StreamFactory::getOutputStream(const URL &url) throw (InvalidArgumentException) {
            if (!url.isValid()) {
                stringstream s;
                s << "Given URL: " << url.toString() << " is invalid.";
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, s.str());
            }

            ostream *out = NULL;
            if (url.getProtocol() == URLProtocol::FILEPROTOCOL) {
                out = new fstream(url.getResource().c_str(), ios::out | ios::binary | ios::trunc);

                if (!out->good()) {
                    (dynamic_cast<fstream*>(out))->close();
                    OPENDAVINCI_CORE_DELETE_POINTER(out);
                }
            }

            if (out == NULL) {
                stringstream s;
                s << "No output stream created for the given URL: " << url.toString() << ".";
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, s.str());
            }

            SharedPointer<ostream> streamOut(out);
            m_listOfOutputStreams.push_back(streamOut);
            return streamOut;
        }

    }
} // core::io
