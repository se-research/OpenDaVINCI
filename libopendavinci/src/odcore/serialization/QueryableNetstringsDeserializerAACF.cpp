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

#include "opendavinci/odcore/serialization/QueryableNetstringsDeserializerAACF.h"
#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/base/module/AbstractCIDModule.h"
#include "opendavinci/odcore/opendavinci.h"

namespace odcore {
    namespace base {

        using namespace std;

        QueryableNetstringsDeserializerAACF::QueryableNetstringsDeserializerAACF() :
            m_buffer(),
            m_values() {}

        QueryableNetstringsDeserializerAACF::QueryableNetstringsDeserializerAACF(istream &in) :
            m_buffer(),
            m_values() {
            deserializeDataFrom(in);
        }

        void QueryableNetstringsDeserializerAACF::deserializeDataFrom(istream &in) {
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
            // 0xAACF
            //
            // Length.
            // Payload.
            // ,

            // Checking for magic number.
            uint16_t magicNumber = 0;
            in.read(reinterpret_cast<char*>(&magicNumber), sizeof(uint16_t));
            magicNumber = ntohs(magicNumber);
            if (magicNumber != 0xAACF) {
                if (in.good()) {
                    // Stream is good but still no magic number?
                    CLOG2 << "Stream corrupt: magic number not found." << endl;
                }
                return;
            }

            // Decoding length of the payload.
            uint32_t length = 0;
            in.read(reinterpret_cast<char*>(&length), sizeof(uint32_t));
            length = ntohl(length);

            // Decode payload consisting of: *(ID SIZE PAYLOAD).
            char c = 0;
            uint32_t tokenIdentifier = 0;
            uint32_t lengthOfPayload = 0;
            while (in.good() && (length > 0)) {
                // Start of next token by reading ID.
                in.read(reinterpret_cast<char*>(&tokenIdentifier), sizeof(uint32_t));
                tokenIdentifier = ntohl(tokenIdentifier);
                length -= (sizeof(uint32_t));

                // Read length of payload.
                in.read(reinterpret_cast<char*>(&lengthOfPayload), sizeof(uint32_t));
                lengthOfPayload = ntohl(lengthOfPayload);
                length -= (sizeof(uint32_t));

                // Create new (tokenIdentifier, m_buffer) hashmap entry.
                m_values.insert(make_pair(tokenIdentifier, m_buffer.tellp()));

                // Decode payload.
                for (uint32_t i = 0; i < lengthOfPayload; i++) {
                    in.get(c);
                    m_buffer.put(c);
                    length--;
                }
            }

            // Check for trailing ','
            in.get(c);
            if (c != ',') {
                CLOG2 << "Stream corrupt: trailing ',' missing,  found: '" << c << "'" << endl;
            }
        }

        QueryableNetstringsDeserializerAACF::~QueryableNetstringsDeserializerAACF() {}

        ///////////////////////////////////////////////////////////////////////

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, Serializable &v) {
            // Read string containing the serialized Serializable.
            string str_buffer;
            uint32_t bytesRead = readValue(i, str_buffer);

            // Restore Serializable from string.
            stringstream sstr_str_buffer(str_buffer);
            sstr_str_buffer >> v;

            return bytesRead;
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, bool &v) {
            i.read(reinterpret_cast<char *>(&v), sizeof(bool));

            return sizeof(bool);
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, char &v) {
            i.read(&v, sizeof(char));

            return sizeof(char);
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, unsigned char &v) {
            i.read(reinterpret_cast<char *>(&v), sizeof(unsigned char));

            return sizeof(unsigned char);
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, int8_t &v) {
            i.read(reinterpret_cast<char *>(&v), sizeof(int8_t));

            return sizeof(int8_t);
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, int16_t &v) {
            int16_t _i = 0;
            i.read(reinterpret_cast<char *>(&_i), sizeof(int16_t));
            _i = ntohs(_i);
            v = _i;

            return sizeof(int16_t);
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, uint16_t &v) {
            uint16_t _ui = 0;
            i.read(reinterpret_cast<char *>(&_ui), sizeof(uint16_t));
            _ui = ntohs(_ui);
            v = _ui;

            return sizeof(uint16_t);
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, int32_t &v) {
            int32_t _i = 0;
            i.read(reinterpret_cast<char *>(&_i), sizeof(int32_t));
            _i = ntohl(_i);
            v = _i;

            return sizeof(int32_t);
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, uint32_t &v) {
            uint32_t _ui = 0;
            i.read(reinterpret_cast<char *>(&_ui), sizeof(uint32_t));
            _ui = ntohl(_ui);
            v = _ui;

            return sizeof(uint32_t);
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, int64_t &v) {
            int64_t _i = 0;
            i.read(reinterpret_cast<char *>(&_i), sizeof(int64_t));
            _i = __ntohll(_i);
            v = _i;

            return sizeof(int64_t);
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, uint64_t &v) {
            uint64_t _ui = 0;
            i.read(reinterpret_cast<char *>(&_ui), sizeof(uint64_t));
            _ui = __ntohll(_ui);
            v = _ui;

            return sizeof(uint64_t);
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, float &v) {
            float _f = 0;
            i.read(reinterpret_cast<char *>(&_f), sizeof(float));
            _f = Deserializer::ntohf(_f);
            v = _f;

            return sizeof(float);
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, double &v) {
            double _d = 0;
            i.read(reinterpret_cast<char *>(&_d), sizeof(double));
            _d = Deserializer::ntohd(_d);
            v = _d;

            return sizeof(double);
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, string &v) {
            uint32_t bytesRead = 0;

            uint32_t stringLength = 0;
            i.read(reinterpret_cast<char *>(&stringLength), sizeof(uint32_t));
            bytesRead += sizeof(uint32_t);
            stringLength = ntohl(stringLength);

// Win32 does not deal properly with the iterator.
#ifdef WIN32
            char *str = new char[stringLength+1];
            i.read(str, stringLength);
            bytesRead += stringLength;
            str[stringLength] = '\0';
            // It is absolutely necessary to specify the size of the serialized string, otherwise, s contains only data until the first '\0' is read.
            v = string(str, stringLength);
            OPENDAVINCI_CORE_DELETE_ARRAY(str);
#else
            string data(stringLength, '\0');
            char* begin = &(*data.begin());
            i.read(begin, stringLength);
            bytesRead += stringLength;

            v = data;
#endif
            return bytesRead;
        }

        uint32_t QueryableNetstringsDeserializerAACF::readValue(istream &i, void *data, const uint32_t &size) {
            i.read(reinterpret_cast<char*>(data), size);
            return size;
        }

        ///////////////////////////////////////////////////////////////////////

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, Serializable &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, bool &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, char &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, unsigned char &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, int8_t &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, int16_t &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, uint16_t &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, int32_t &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, uint32_t &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, int64_t &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, uint64_t &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, float &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, double &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, string &v) {
            read(id, "", "", v);
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, void *data, const uint32_t &size) {
            read(id, "", "", data, size);
        }

        ///////////////////////////////////////////////////////////////////////

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, Serializable &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, bool &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, char &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, unsigned char &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, int8_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, int16_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, uint16_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, int32_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, uint32_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, int64_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, uint64_t &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, float &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, double &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, string &v) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, v);
            }
        }

        void QueryableNetstringsDeserializerAACF::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, void *data, const uint32_t &size) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                readValue(m_buffer, data, size);
            }
        }
    }
} // odcore::base
