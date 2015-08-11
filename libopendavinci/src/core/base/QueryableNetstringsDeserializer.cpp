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

#include "core/base/module/AbstractCIDModule.h"
#include "core/base/QueryableNetstringsDeserializer.h"
#include "core/base/Serializable.h"

namespace core {
    namespace base {

        using namespace std;

        QueryableNetstringsDeserializer::QueryableNetstringsDeserializer() :
            m_buffer(),
            m_values() {}

        QueryableNetstringsDeserializer::QueryableNetstringsDeserializer(istream &in) :
            m_buffer(),
            m_values() {
            deserializeDataFrom(in);
        }

        void QueryableNetstringsDeserializer::deserializeDataFrom(istream &in) {
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

        QueryableNetstringsDeserializer::~QueryableNetstringsDeserializer() {}

        void QueryableNetstringsDeserializer::read(const uint32_t &id, Serializable &s) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                m_buffer >> s;
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, bool &b) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                m_buffer.read(reinterpret_cast<char *>(&b), sizeof(bool));
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, char &c) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                m_buffer.read(&c, sizeof(char));
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, unsigned char &uc) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                m_buffer.read(reinterpret_cast<char *>(&uc), sizeof(unsigned char));
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, int8_t &i) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                m_buffer.read(reinterpret_cast<char *>(&i), sizeof(int8_t));
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, int16_t &i) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                int16_t _i = 0;
                m_buffer.read(reinterpret_cast<char *>(&_i), sizeof(int16_t));
                _i = ntohs(_i);
                i = _i;
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, uint16_t &ui) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);

                uint16_t _ui = 0;
                m_buffer.read(reinterpret_cast<char *>(&_ui), sizeof(uint16_t));
                _ui = ntohs(_ui);
                ui = _ui;
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, int32_t &i) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                int32_t _i = 0;
                m_buffer.read(reinterpret_cast<char *>(&_i), sizeof(int32_t));
                _i = ntohl(_i);
                i = _i;
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, uint32_t &ui) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);

                uint32_t _ui = 0;
                m_buffer.read(reinterpret_cast<char *>(&_ui), sizeof(uint32_t));
                _ui = ntohl(_ui);
                ui = _ui;
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, int64_t &i) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                int64_t _i = 0;
                m_buffer.read(reinterpret_cast<char *>(&_i), sizeof(int64_t));
                _i = __ntohll(_i);
                i = _i;
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, uint64_t &ui) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);

                uint64_t _ui = 0;
                m_buffer.read(reinterpret_cast<char *>(&_ui), sizeof(uint64_t));
                _ui = __ntohll(_ui);
                ui = _ui;
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, float &f) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);

                float _f = 0;
                m_buffer.read(reinterpret_cast<char *>(&_f), sizeof(float));
                _f = Deserializer::ntohf(_f);
                f = _f;
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, double &d) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);

                double _d = 0;
                m_buffer.read(reinterpret_cast<char *>(&_d), sizeof(double));
                _d = Deserializer::ntohd(_d);
                d = _d;
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, string &s) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                uint32_t stringLength = 0;
                m_buffer.read(reinterpret_cast<char *>(&stringLength), sizeof(uint32_t));
                stringLength = ntohl(stringLength);
                char *str = new char[stringLength+1];
                m_buffer.read(str, stringLength);
                str[stringLength] = '\0';
                // It is absolutely necessary to specify the size of the serialized string, otherwise, s contains only data until the first '\0' is read.
                s = string(str, stringLength);
                OPENDAVINCI_CORE_DELETE_ARRAY(str);
            }
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, void *data, const uint32_t &size) {
            map<uint32_t, streampos>::iterator it = m_values.find(id);

            if (it != m_values.end()) {
                m_buffer.seekg(it->second);
                m_buffer.read(reinterpret_cast<char*>(data), size);
            }
        }

    }
} // core::base
