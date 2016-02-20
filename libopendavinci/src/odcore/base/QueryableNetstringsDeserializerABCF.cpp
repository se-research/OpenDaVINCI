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

#include <iostream>

#include "opendavinci/core/base/QueryableNetstringsDeserializerABCF.h"
#include "opendavinci/core/base/Serializable.h"
#include "opendavinci/core/base/module/AbstractCIDModule.h"
#include "opendavinci/core/opendavinci.h"

namespace core {
    namespace base {

        using namespace std;

        QueryableNetstringsDeserializerABCF::QueryableNetstringsDeserializerABCF() :
            m_buffer(),
            m_values() {}

        QueryableNetstringsDeserializerABCF::QueryableNetstringsDeserializerABCF(istream &in) :
            m_buffer(),
            m_values() {
            deserializeDataFrom(in);
        }

        uint8_t QueryableNetstringsDeserializerABCF::decodeVarInt(istream &in, int64_t &value) {
            uint64_t uvalue = 0;
            uint8_t size = decodeVarUInt(in, uvalue);
            value = static_cast<int64_t>( uvalue & 1 ? ~(uvalue >> 1) : (uvalue >> 1) );
            return size;
        }

        uint8_t QueryableNetstringsDeserializerABCF::decodeVarUInt(istream &in, uint64_t &value) {
            value = 0;
            uint8_t size = 0;
            while (in.good()) {
                char c = 0;
                in.read(&c, sizeof(char));
                value |= static_cast<unsigned int>( (c & 0x7f) << (0x7 * size++) );
                if ( !(c & 0x80) ) break;
            }
            // Decode as little endian like in Protobuf's case.
            value = le64toh(value);

            return size;
        }

        void QueryableNetstringsDeserializerABCF::deserializeDataFrom(istream &in) {
            // Reset any existing data in our hashmap.
            m_values.clear();
            m_buffer.clear();
            m_buffer.str("");

            // Initialize the stringstream for getting valid positions when calling tellp().
            // This MUST be a blank (Win32 has a *special* implementation...)!
            m_buffer << " ";

            // Stream contents:
            // Header:
            //
            // 0xABCF
            //
            // Length.
            // Payload.
            // ,

            // The payload itself is encoded as:
            //
            // ID as varint
            // Length of the payload as varint
            // Value of the payload as varint

            // Checking for magic number.
            uint16_t magicNumber = 0;
            if (in.good()) {
                in.read(reinterpret_cast<char*>(&magicNumber), sizeof(uint16_t));
                magicNumber = ntohs(magicNumber);
                if (magicNumber != 0xABCF) {
                    // Stream is good but still no magic number?
                    CLOG2 << "Stream corrupt: magic number not found." << endl;
                    return;
                }

                // Decoding length of the payload written as varint.
                uint64_t length = 0;
                decodeVarUInt(in, length);

                // Decode payload consisting of: *(ID SIZE PAYLOAD).
                char c = 0;
                uint64_t tokenIdentifier = 0;
                uint64_t lengthOfPayload = 0;

                // Buffer to store payload "en bloc"; length is identical to UDP payload.
                const uint32_t MAX_SIZE_PAYLOAD = 65535;
                char buffer[MAX_SIZE_PAYLOAD];

                while (in.good() && (length > 0)) {
                    // Start of next token by reading ID.
                    length -= decodeVarUInt(in, tokenIdentifier);

                    // Read length of payload and adjust loop.
                    lengthOfPayload = 0;
                    length -= decodeVarUInt(in, lengthOfPayload);

                    // Create new (tokenIdentifier, m_buffer) hashmap entry.
                    m_values.insert(make_pair(tokenIdentifier, m_buffer.tellp()));

                    // Decode payload.
                    if (lengthOfPayload > 0) {
                        // Read data "en bloc".
                        in.read(buffer, lengthOfPayload);
                        m_buffer.write(buffer, lengthOfPayload);

                        // Update amount of processed data.
                        length -= lengthOfPayload;
                    }
                }

                // Check for trailing ','
                in.read(&c, sizeof(char));
                if (c != ',') {
                    CLOG2 << "Stream corrupt: trailing ',' missing,  found: '" << c << "'" << endl;
                }
            }
        }

        QueryableNetstringsDeserializerABCF::~QueryableNetstringsDeserializerABCF() {}

        uint32_t QueryableNetstringsDeserializerABCF::fillBuffer(istream& in, stringstream& buffer) {
            char _c = 0;
            uint32_t bytesRead = 0;

            // Peek Container's header: 2 bytes (0xABCF) followed by maximum 8 bytes (uint64_t) length of payload information.
            uint32_t bytesToRead = sizeof(uint16_t) + sizeof(uint64_t);

            // Read Container header + size of payload.
            while (in.good() && (bytesToRead > 0)) {
                // Read next byte.
                in.read(&_c, sizeof(char));
                bytesToRead--; bytesRead++;

                // Add new byte at the end of the buffer.
                buffer.write(&_c, sizeof(char));
            }

            // Decode Container's magic number.
            uint16_t magicNumber = 0;
            buffer.read(reinterpret_cast<char*>(&magicNumber), sizeof(uint16_t));
            magicNumber = ntohs(magicNumber);

            if (magicNumber == 0xABCF) {
                // Decode size of payload (encoded as varint).
                uint64_t value = 0;
                uint8_t size = 0;
                {
                    while (buffer.good()) {
                        char c = 0;
                        buffer.read(&c, sizeof(char));
                        value |= static_cast<unsigned int>( (c & 0x7f) << (0x7 * size++) );
                        if ( !(c & 0x80) ) break;
                    }
                    // Decode as little endian like in Protobuf's case.
                    value = le64toh(value);
                }

                bytesToRead = (value // This is the length of the payload.
                               - (sizeof(uint64_t) // We have already read this amount of bytes while peeking the header.
                                  - size) // This amount of bytes was consumed to encode the length of the payload in the varint field.
                                 )
                               + 1; // And we need to consume the final ','.

                // Add the data at the end of the buffer.
                buffer.seekg(0, ios_base::end);

                // Read remainder of the container.
                while (in.good() && (bytesToRead > 0)) {
                    // Read next byte.
                    in.read(&_c, sizeof(char));
                    bytesToRead--; bytesRead++;

                    // Add new byte at the end of the buffer.
                    buffer.write(&_c, sizeof(char));
                }

                // Move read pointer to the beginning to read container.
                buffer.seekg(0, ios_base::beg);
            }

            return bytesRead;
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, Serializable &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, bool &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, char &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, unsigned char &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, int8_t &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, int16_t &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, uint16_t &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, int32_t &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, uint32_t &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, int64_t &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, uint64_t &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, float &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, double &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, string &v) {
            read(id, 0, "", "", v);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &id, void *data, const uint32_t &size) {
            read(id, 0, "", "", data, size);
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, Serializable &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                m_buffer >> v;
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, bool &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                uint64_t tmp = 0;
                decodeVarUInt(m_buffer, tmp);
                v = static_cast<bool>(tmp);
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, char &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                int64_t tmp = 0;
                decodeVarInt(m_buffer, tmp);
                v = static_cast<char>(tmp);
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, unsigned char &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                uint64_t tmp = 0;
                decodeVarUInt(m_buffer, tmp);
                v = static_cast<unsigned char>(tmp);
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, int8_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                int64_t tmp = 0;
                decodeVarInt(m_buffer, tmp);
                v = static_cast<int8_t>(tmp);
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, int16_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                int64_t tmp = 0;
                decodeVarInt(m_buffer, tmp);
                v = static_cast<int16_t>(tmp);
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, uint16_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                uint64_t tmp = 0;
                decodeVarUInt(m_buffer, tmp);
                v = static_cast<uint16_t>(tmp);
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, int32_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                int64_t tmp = 0;
                decodeVarInt(m_buffer, tmp);
                v = static_cast<int32_t>(tmp);
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, uint32_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                uint64_t tmp = 0;
                decodeVarUInt(m_buffer, tmp);
                v = static_cast<uint32_t>(tmp);
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, int64_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                int64_t tmp = 0;
                decodeVarInt(m_buffer, tmp);
                v = static_cast<int64_t>(tmp);
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, uint64_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                uint64_t tmp = 0;
                decodeVarUInt(m_buffer, tmp);
                v = static_cast<uint64_t>(tmp);
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, float &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);

                float _f = 0;
                m_buffer.read(reinterpret_cast<char *>(&_f), sizeof(float));
                _f = Deserializer::ntohf(_f);
                v = _f;
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, double &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);

                double _d = 0;
                m_buffer.read(reinterpret_cast<char *>(&_d), sizeof(double));
                _d = Deserializer::ntohd(_d);
                v = _d;
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, string &v) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);

                uint64_t stringLength = 0;
                decodeVarUInt(m_buffer, stringLength);

#ifdef WIN32
                char *str = new char[stringLength+1];
                m_buffer.read(str, stringLength);
                str[stringLength] = '\0';
                // It is absolutely necessary to specify the size of the serialized string, otherwise, s contains only data until the first '\0' is read.
                v = string(str, stringLength);
                OPENDAVINCI_CORE_DELETE_ARRAY(str);
#else
                string data(stringLength, '\0');
                char* begin = &(*data.begin());
                m_buffer.read(begin, stringLength);

                v = data;
#endif
            }
        }

        void QueryableNetstringsDeserializerABCF::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, void *data, const uint32_t &size) {
            map<uint32_t, streampos>::iterator it = m_values.find( (oneByteID > 0 ? oneByteID : fourByteID) );

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                m_buffer.read(reinterpret_cast<char*>(data), size);
            }
        }
    }
} // core::base
