/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2012 - 2015 Christian Berger
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

#include <cstdlib>

#include "core/base/Lock.h"
#include "core/io/StringListener.h"
#include "core/io/protocol/NetstringsProtocol.h"

namespace core {
    namespace io {
        namespace protocol {

            using namespace core::base;

            NetstringsProtocol::NetstringsProtocol() :
                AbstractProtocol(),
                m_stringListenerMutex(),
                m_stringListener(NULL),
                m_partialDataMutex(),
                m_partialData() {}

            NetstringsProtocol::~NetstringsProtocol() {
                setStringListener(NULL);
            }

            void NetstringsProtocol::setStringListener(StringListener* listener) {
                Lock l(m_stringListenerMutex);
                m_stringListener = listener;
            }

            void NetstringsProtocol::send(const string& data) {
                if (data.length() > 0) {
                    stringstream netstring;

                    netstring << static_cast<uint32_t>(data.length()) << ":" << data << ",";

                    sendByStringSender(netstring.str());
                }
            }

            void NetstringsProtocol::nextString(const string &s) {
                Lock l(m_partialDataMutex);
                m_partialData.write(s.c_str(), s.length());
                decodeNetstring();

                // After using str() to set the remaining string, the write pointer
                // points to the beginning of the stream and further receivedString() calls
                // would override existing data. So the write pointer has to point to the
                // end of the stream.
                m_partialData.seekp(0, ios_base::end);
            }

            void NetstringsProtocol::decodeNetstring(void) {
                // Netstrings have the following format:
                // ASCII Number representing the length of the payload + ':' + payload + ','

                bool checkForMoreNetstrings = true;
                while (checkForMoreNetstrings) {
                    m_partialData.seekg(0, ios_base::end);
                    uint32_t lengthOfBuffer = m_partialData.tellg();
                    m_partialData.seekg(0, ios_base::beg);

                    if (lengthOfBuffer >= 3) {
                        // On WIN32, the .str() returns a temporary object that is destroyed after the expression.
                        // The reference keeps its existence instead.
                        const string &m_partialDataString = m_partialData.str();
                        const char *receiveBuffer = m_partialDataString.c_str();
                        char *colonSign = NULL;
                        uint32_t lengthOfPayload = strtol(receiveBuffer, &colonSign, 10);
                        if (lengthOfPayload == 0) {
                            // Remove empty Netstring: "0:," (size is 3).
                            m_partialData.str(m_partialData.str().substr(3));
                            checkForMoreNetstrings = true;
                            continue; // Try to decode next Netstring if any.
                        }

                        if (lengthOfPayload > lengthOfBuffer) {
                            // Incomplete Netstring received. Wait for more data.
                            checkForMoreNetstrings = false;
                            continue;
                        }

                        // Check for colon.
                        if (*colonSign == ':') {
                            // Found colon sign. Now, check if (receiveBuffer + 1 + lengthOfPayload) == ','.
                            if ((colonSign[1 + lengthOfPayload]) == ',') {
                                // Successfully found a complete Netstring.
                                string receivedPayload = m_partialData.str().substr((colonSign + 1) - receiveBuffer, lengthOfPayload);

                                invokeStringListener(receivedPayload);

                                // Calculate size of decoded Netstring: "<lengthOfPayload> : <payload> ,"
                                const uint32_t lengthOfNetstring = (colonSign + 1 + lengthOfPayload + 1) - receiveBuffer;

                                // Remove the decoded Netstring from the buffer.
                                m_partialData.str(m_partialData.str().substr(lengthOfNetstring));

                                checkForMoreNetstrings = true;
                                continue;
                            }
                        }

                        // We should never get here as the received data might be corrupted; reset buffer.
                        m_partialData.str("");
                        checkForMoreNetstrings = false;
                    }
                    else {
                        // We need to wait for more data.
                        checkForMoreNetstrings = false;
                    }
                }
            }

            void NetstringsProtocol::invokeStringListener(const string& data) {
                Lock l(m_stringListenerMutex);
                if (m_stringListener != NULL) {
                    m_stringListener->nextString(data);
                }
            }

        }
    }
}

