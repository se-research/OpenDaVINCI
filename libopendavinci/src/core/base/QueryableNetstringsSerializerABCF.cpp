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

        uint8_t QueryableNetstringsSerializerABCF::shortenID(const uint32_t &value) {
            // Inspired by: https://chromium.googlesource.com/chromiumos/platform/vboot_reference/+/master/firmware/lib/crc8.c
            uint16_t _value = 0;
            uint32_t mask = 0xff000000;
            for(uint8_t i = 0; i < 4; i++) {
                mask >>= i*8;
                _value ^= value & mask;
                for(uint8_t j = 8; j; j--) {
                    if (_value & 0x8000) {
                        _value ^= (0x1070 << 3);
                    }
                    _value <<= 1;
                }
            }
            return static_cast<uint8_t>(_value >> 8);
        }

        void QueryableNetstringsSerializerABCF::getSerializedData(ostream &o) {
            // Write magic number.
            uint16_t magicNumber = 0xABCF;
            magicNumber = htons(magicNumber);
            o.write(reinterpret_cast<const char *>(&magicNumber), sizeof(uint16_t));

            // Write length.
            const string s = m_buffer.str();
            uint64_t length = static_cast<uint32_t>(s.length());
            encodeVarInt(o, length);

            // Write payload.
            o << s;

            // Write End-Of-Data for checking corruptness.
            o << ",";
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const Serializable &s) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));

            stringstream buffer;
            buffer << s;

            const string tmp = buffer.str();
            uint64_t size = static_cast<uint32_t>(tmp.length());
            encodeVarInt(m_buffer, size);

            m_buffer << tmp;
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const bool &b) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = encodeVarInt(tmp, b);

            // Write the length of the payload.
            encodeVarInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const char &c) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = encodeVarInt(tmp, c);

            // Write the length of the payload.
            encodeVarInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const unsigned char &uc) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = encodeVarInt(tmp, uc);

            // Write the length of the payload.
            encodeVarInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const int8_t &i) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = encodeVarInt(tmp, i);

            // Write the length of the payload.
            encodeVarInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const int16_t &i) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = encodeVarInt(tmp, i);

            // Write the length of the payload.
            encodeVarInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const uint16_t &ui) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = encodeVarInt(tmp, ui);

            // Write the length of the payload.
            encodeVarInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const int32_t &i) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = encodeVarInt(tmp, i);

            // Write the length of the payload.
            encodeVarInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const uint32_t &ui) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = encodeVarInt(tmp, ui);

            // Write the length of the payload.
            encodeVarInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const int64_t &i) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = encodeVarInt(tmp, i);

            // Write the length of the payload.
            encodeVarInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const uint64_t &ui) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = encodeVarInt(tmp, ui);

            // Write the length of the payload.
            encodeVarInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const float &f) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));
            encodeVarInt(m_buffer, sizeof(float));

            float _f = f;
            _f = Serializer::htonf(_f);
            m_buffer.write(reinterpret_cast<const char *>(&_f), sizeof(const float));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const double &d) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));
            encodeVarInt(m_buffer, sizeof(double));

            double _d = d;
            _d = Serializer::htond(_d);
            m_buffer.write(reinterpret_cast<const char *>(&_d), sizeof(const double));
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const string &s) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));

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
            m_buffer << tmp.str();

            // Write the raw bytes from the string.
            m_buffer.write(s.c_str(), stringLength);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const void *data, const uint32_t &size) {
            encodeVarInt(m_buffer, QueryableNetstringsSerializerABCF::shortenID(id));
            encodeVarInt(m_buffer, size);

            m_buffer.write(reinterpret_cast<const char*>(data), size);
        }

    }
} // core::base
