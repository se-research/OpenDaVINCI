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

#include "opendavinci/odcore/base/QueryableNetstringsSerializerABCF.h"
#include "opendavinci/odcore/base/Serializable.h"

namespace odcore {
    namespace base {

        using namespace std;

        QueryableNetstringsSerializerABCF::QueryableNetstringsSerializerABCF() :
            m_buffer() {}

        QueryableNetstringsSerializerABCF::~QueryableNetstringsSerializerABCF() {}

        uint8_t QueryableNetstringsSerializerABCF::encodeVarInt(ostream &out, int64_t value) {
            uint64_t uvalue = static_cast<uint64_t>( value < 0 ? ~(value << 1) : (value << 1) );
            return encodeVarUInt(out, uvalue);
        }

        uint8_t QueryableNetstringsSerializerABCF::encodeVarUInt(ostream &out, uint64_t value) {
            // We will write at least one byte.
            uint8_t size = 1;

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
            const string s = m_buffer.str();
            uint64_t length = static_cast<uint32_t>(s.length());
            encodeVarUInt(o, length);

            // Write payload.
            o << s;

            // Write End-Of-Data for checking corruptness.
            o << ",";
        }

        ///////////////////////////////////////////////////////////////////////

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const Serializable &v) {
            // Serialize Serializable into a string.
            stringstream buffer;
            buffer << v;

            // Delegate data dump to string serialization.
            const string str_buffer = buffer.str();
            return writeValue(o, str_buffer);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const bool &v) {
            return encodeVarUInt(o, v);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const char &v) {
            return encodeVarInt(o, v);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const unsigned char &v) {
            return encodeVarUInt(o, v);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const int8_t &v) {
            return encodeVarInt(o, v);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const int16_t &v) {
            return encodeVarInt(o, v);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const uint16_t &v) {
            return encodeVarUInt(o, v);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const int32_t &v) {
            return encodeVarInt(o, v);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const uint32_t &v) {
            return encodeVarUInt(o, v);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const int64_t &v) {
            return encodeVarInt(o, v);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const uint64_t &v) {
            return encodeVarUInt(o, v);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const float &v) {
            float _f = v;
            _f = Serializer::htonf(_f);
            o.write(reinterpret_cast<const char *>(&_f), sizeof(const float));

            return sizeof(const float);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const double &v) {
            double _d = v;
            _d = Serializer::htond(_d);
            o.write(reinterpret_cast<const char *>(&_d), sizeof(const double));

            return sizeof(const double);
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const string &v) {
            uint32_t bytesWritten = 0;

            // Length of the raw string.
            const uint32_t stringLength = v.length();

            // Get the varint-encoded length of the string length that will be part of the payload.
            bytesWritten += encodeVarUInt(o, stringLength);

            // Write the raw bytes from the string.
            o.write(v.c_str(), stringLength);
            bytesWritten += stringLength;

            return bytesWritten;
        }

        uint32_t QueryableNetstringsSerializerABCF::writeValue(ostream &o, const void *data, const uint32_t &size) {
            o.write(reinterpret_cast<const char*>(data), size);
            return size;
        }

        ///////////////////////////////////////////////////////////////////////

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const Serializable &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const bool &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const char &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const unsigned char &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const int8_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const int16_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const uint16_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const int32_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const uint32_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const int64_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const uint64_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const float &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const double &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const string &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &id, const void *data, const uint32_t &size) {
            write(id, 0, "", "", data, size);
        }

        ///////////////////////////////////////////////////////////////////////

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const Serializable &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));


            stringstream buffer;
            buffer << v;

            const string tmp = buffer.str();
            uint64_t size = static_cast<uint32_t>(tmp.length());
            encodeVarUInt(m_buffer, size);

            m_buffer << tmp;
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const bool &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = writeValue(tmp, v);

            // Write the length of the payload.
            encodeVarUInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const char &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = writeValue(tmp, v);

            // Write the length of the payload.
            encodeVarUInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const unsigned char &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = writeValue(tmp, v);

            // Write the length of the payload.
            encodeVarUInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int8_t &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = writeValue(tmp, v);

            // Write the length of the payload.
            encodeVarUInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int16_t &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = writeValue(tmp, v);

            // Write the length of the payload.
            encodeVarUInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint16_t &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = writeValue(tmp, v);

            // Write the length of the payload.
            encodeVarUInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int32_t &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = writeValue(tmp, v);

            // Write the length of the payload.
            encodeVarUInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint32_t &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = writeValue(tmp, v);

            // Write the length of the payload.
            encodeVarUInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int64_t &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = writeValue(tmp, v);

            // Write the length of the payload.
            encodeVarUInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint64_t &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));

            // Get the varint-encoded length of the value and save the varint-encoded payload.
            stringstream tmp;
            uint32_t size = writeValue(tmp, v);

            // Write the length of the payload.
            encodeVarUInt(m_buffer, size);

            // Write the payload.
            m_buffer << tmp.str();
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const float &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));
            encodeVarUInt(m_buffer, sizeof(float));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const double &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));
            encodeVarUInt(m_buffer, sizeof(double));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const string &v) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));

            // Length of the raw string.
            const uint32_t stringLength = v.length();

            // Get the varint-encoded length of the string length that will be part of the payload.
            stringstream tmp;
            uint32_t size = encodeVarUInt(tmp, stringLength);

            // Add the actual string length.
            size += stringLength;

            // Write the total length of the payload containing the varint-encoded string length + the raw string.
            encodeVarUInt(m_buffer, size);

            // Write the string length (which is actually part of the payload).
            m_buffer << tmp.str();

            // Write the raw bytes from the string.
            m_buffer.write(v.c_str(), stringLength);
        }

        void QueryableNetstringsSerializerABCF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const void *data, const uint32_t &size) {
            encodeVarUInt(m_buffer, (oneByteID > 0 ? oneByteID : fourByteID));
            encodeVarUInt(m_buffer, size);

            writeValue(m_buffer, data, size);
        }

    }
} // odcore::base
