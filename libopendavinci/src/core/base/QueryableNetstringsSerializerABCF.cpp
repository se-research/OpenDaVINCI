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

#include "core/base/QueryableNetstringsSerializerABCF.h"
#include "core/base/Serializable.h"

namespace core {
    namespace base {

        using namespace std;

        QueryableNetstringsSerializerABCF::QueryableNetstringsSerializerABCF() :
            m_buffer() {}

        QueryableNetstringsSerializerABCF::~QueryableNetstringsSerializerABCF() {}


        uint8_t QueryableNetstringsSerializerABCF::encodeVarInt(ostream &out, uint64_t value) {
            // We will write at least one byte.
            uint8_t size = 1;

            // Encode as little endian like in Protobuf's case.
            value = htole64(value);

            char byte = 0;
            while (value > 0x7f) {
                // If the value to be written occupies more than 7 bits, we need to encode it using the MSB flag.
                byte = (static_cast<uint8_t>(value & 0x7f)) | 0x80;
                out.put(byte);
                // Remove the seven bits that we have already written.
                value >>= 7;
                // Start next byte.
                size++;
            }
            // Write final value.
            byte = (static_cast<uint8_t>(value)) & 0x7f;
            out.put(byte);

            return size;
        }

        void QueryableNetstringsSerializerABCF::getSerializedData(ostream &o) {
            // Write magic number.
            uint16_t magicNumber = 0xABCF;
            magicNumber = htons(magicNumber);
            o.write(reinterpret_cast<const char *>(&magicNumber), sizeof(uint16_t));

            // Write length.
            uint64_t length = static_cast<uint32_t>(m_buffer.str().length());
            encodeVarInt(o, length);
cerr << "Length = " << length << endl;
            // Write payload.
            o << m_buffer.str();

            // Write End-Of-Data for checking corruptness.
            o << ",";
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const Serializable &s) {
            encodeVarInt(m_buffer, id);

            stringstream buffer;
            buffer << s;

            uint64_t size = static_cast<uint32_t>(buffer.str().length());
            encodeVarInt(m_buffer, size);

            m_buffer << buffer.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const bool &b) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, sizeof(bool));

            m_buffer.write(reinterpret_cast<const char *>(&b), sizeof(const bool));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const char &c) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, sizeof(const char));

            m_buffer.write(&c, sizeof(const char));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const unsigned char &uc) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, sizeof(const unsigned char));

            m_buffer.write(reinterpret_cast<const char *>(&uc), sizeof(const unsigned char));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const int8_t &i) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, sizeof(const int8_t));

            int8_t _i = i;
            m_buffer.write(reinterpret_cast<const char *>(&_i), sizeof(const int8_t));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const int16_t &i) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, sizeof(const int16_t));

            int16_t _i = i;
            _i = htons(_i);
            m_buffer.write(reinterpret_cast<const char *>(&_i), sizeof(const int16_t));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const uint16_t &ui) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, sizeof(const uint16_t));

            uint16_t _ui = ui;
            _ui = htons(_ui);
            m_buffer.write(reinterpret_cast<const char *>(&_ui), sizeof(const uint16_t));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const int32_t &i) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, sizeof(const int32_t));

            int32_t _i = i;
            _i = htonl(_i);
            m_buffer.write(reinterpret_cast<const char *>(&_i), sizeof(const int32_t));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const uint32_t &ui) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, sizeof(const uint32_t));

            uint32_t _ui = ui;
            _ui = htonl(_ui);
            m_buffer.write(reinterpret_cast<const char *>(&_ui), sizeof(const uint32_t));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const int64_t &i) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, sizeof(const int64_t));

            int64_t _i = i;
            _i = __htonll(_i);
            m_buffer.write(reinterpret_cast<const char *>(&_i), sizeof(const int64_t));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const uint64_t &ui) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, sizeof(const uint64_t));

            uint64_t _ui = ui;
            _ui = __htonll(_ui);
            m_buffer.write(reinterpret_cast<const char *>(&_ui), sizeof(const uint64_t));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const float &f) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, sizeof(float));

            float _f = f;
            _f = Serializer::htonf(_f);
            m_buffer.write(reinterpret_cast<const char *>(&_f), sizeof(const float));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const double &d) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, sizeof(double));

            double _d = d;
            _d = Serializer::htond(_d);
            m_buffer.write(reinterpret_cast<const char *>(&_d), sizeof(const double));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const string &s) {
            encodeVarInt(m_buffer, id);

            // Length of the raw string.
            const uint32_t stringLength = s.length();

            // Get the varint-encoded length of the string length that will be part of the payload.
            stringstream tmp;
            uint32_t size = encodeVarInt(tmp, stringLength);

            // Add the actual string length.
            size += stringLength;

            // Write the total length of the payload containing the varint-encoded string length + the raw string.
            encodeVarInt(m_buffer, size);

            // Write the string length (which is actually part of the payload).
            encodeVarInt(m_buffer, stringLength);

            // Write the raw bytes from the string.
            m_buffer.write(s.c_str(), stringLength);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const void *data, const uint32_t &size) {
            encodeVarInt(m_buffer, id);
            encodeVarInt(m_buffer, size);

            m_buffer.write(reinterpret_cast<const char*>(data), size);
        }

    }
} // core::base
