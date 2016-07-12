/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2015 Christian Berger
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
#include <sstream>

#include "opendavinci/odcore/base/ProtoSerializer.h"
#include "opendavinci/odcore/base/ProtoSerializerVisitor.h"
#include "opendavinci/odcore/base/Visitable.h"

namespace odcore {
    namespace base {

class Serializable;

        ProtoSerializer::ProtoSerializer() :
            m_out(NULL),
            m_size(0),
            m_buffer() {}

        ProtoSerializer::ProtoSerializer(ostream &o) :
            m_out(&o),
            m_size(0),
            m_buffer() {}

        ProtoSerializer::~ProtoSerializer() {
            if (m_out != NULL) {
                getSerializedDataWithHeader(*m_out);
            }
        }

        void ProtoSerializer::getSerializedData(ostream &o) {
            o << m_buffer.str();
        }

        void ProtoSerializer::getSerializedDataWithHeader(ostream &o) {
            uint16_t magicNumber = 0x0DA4;
            encodeVarInt(o, magicNumber);
            encodeVarInt(o, m_size);
            getSerializedData(o);
        }

        uint32_t ProtoSerializer::getKey(const uint32_t &fieldNumber, const uint8_t &protoType) {
            return (fieldNumber << 3) | protoType;
        }

        uint32_t ProtoSerializer::writeValue(const uint32_t &id, const ProtoSerializer::PROTOBUF_TYPE &type, uint64_t value) {
            uint32_t size = 0;
            uint32_t key = getKey(id, type);
            size += encodeVarInt(m_buffer, key);
            size += encodeVarInt(m_buffer, value);
            return size;
        }

        uint8_t ProtoSerializer::encodeZigZag8(int8_t value) {
            return static_cast<uint8_t>((value << 1) ^ (value >> 7));
        }

        uint16_t ProtoSerializer::encodeZigZag16(int16_t value) {
            return static_cast<uint16_t>((value << 1) ^ (value >> 15));
        }

        uint32_t ProtoSerializer::encodeZigZag32(int32_t value) {
            return static_cast<uint32_t>((value << 1) ^ (value >> 31));
        }

        uint64_t ProtoSerializer::encodeZigZag64(int64_t value) {
            return static_cast<uint64_t>((value << 1) ^ (value >> 63));
        }

        uint8_t ProtoSerializer::encodeVarInt(ostream &out, uint64_t value) {
            // We will write at least one byte.
            uint8_t size = 1;

            // Protobuf's VarInt is based on little endian.
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

        ///////////////////////////////////////////////////////////////////////

        void ProtoSerializer::write(const uint32_t &id, const Serializable &v) {
            uint32_t key = getKey(id, ProtoSerializer::LENGTH_DELIMITED);
            m_size += encodeVarInt(m_buffer, key);

            // Buffer for serialized data.
            stringstream buffer;

            // Check whether v is from type Visitable to use ProtoSerializer.
            try {
                const Visitable &v2 = dynamic_cast<const Visitable&>(v);

                // Cast succeeded, visited nested class using a ProtoSerializer.
                ProtoSerializerVisitor nestedVisitor;
                const_cast<Visitable&>(v2).accept(nestedVisitor);

                // Get serialized data.
                nestedVisitor.getSerializedData(buffer);
            }
            catch(...) {
                // Serialize v using the default way as it is not of type Visitable.
                buffer << v;
            }

            // Get serialized value.
            const string tmp = buffer.str();

            // Write length of v into m_buffer.
            uint64_t size = static_cast<uint32_t>(tmp.length());
            m_size += encodeVarInt(m_buffer, size);

            // Write actual value.
            m_buffer.write(tmp.c_str(), size);
            m_size += size;
        }

        void ProtoSerializer::write(const uint32_t &id, const bool &v) {
            m_size += writeValue(id, ProtoSerializer::VARINT, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const char &v) {
            m_size += writeValue(id, ProtoSerializer::VARINT, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const unsigned char &v) {
            m_size += writeValue(id, ProtoSerializer::VARINT, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const int8_t &v) {
            m_size += writeValue(id, ProtoSerializer::VARINT, encodeZigZag8(v));
        }

        void ProtoSerializer::write(const uint32_t &id, const int16_t &v) {
            m_size += writeValue(id, ProtoSerializer::VARINT, encodeZigZag16(v));
        }

        void ProtoSerializer::write(const uint32_t &id, const uint16_t &v) {
            m_size += writeValue(id, ProtoSerializer::VARINT, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const int32_t &v) {
            m_size += writeValue(id, ProtoSerializer::VARINT, encodeZigZag32(v));
        }

        void ProtoSerializer::write(const uint32_t &id, const uint32_t &v) {
            m_size += writeValue(id, ProtoSerializer::VARINT, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const int64_t &v) {
            m_size += writeValue(id, ProtoSerializer::VARINT, encodeZigZag64(v));
        }

        void ProtoSerializer::write(const uint32_t &id, const uint64_t &v) {
            m_size += writeValue(id, ProtoSerializer::VARINT, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const float &v) {
            uint32_t key = getKey(id, ProtoSerializer::FOUR_BYTES);
            m_size += encodeVarInt(m_buffer, key);

            float _v = htonf(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const float));
            m_size += sizeof(const float);
        }

        void ProtoSerializer::write(const uint32_t &id, const double &v) {
            uint32_t key = getKey(id, ProtoSerializer::EIGHT_BYTES);
            m_size += encodeVarInt(m_buffer, key);

            double _v = htond(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const double));
            m_size += sizeof(const double);
        }

        void ProtoSerializer::write(const uint32_t &id, const string &v) {
            uint32_t key = getKey(id, ProtoSerializer::LENGTH_DELIMITED);
            m_size += encodeVarInt(m_buffer, key);

            const uint32_t size = v.length();
            m_size += encodeVarInt(m_buffer, size);

            m_buffer.write(v.c_str(), size);
            m_size += size;
        }

        void ProtoSerializer::write(const uint32_t &id, const void *data, const uint32_t &size) {
            uint32_t key = getKey(id, ProtoSerializer::LENGTH_DELIMITED);
            m_size += encodeVarInt(m_buffer, key);

            m_size += encodeVarInt(m_buffer, size);

            m_buffer.write(reinterpret_cast<const char*>(data), size);
            m_size += size;
        }

        ///////////////////////////////////////////////////////////////////////

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const Serializable &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const bool &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const char &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const unsigned char &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int8_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int16_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint16_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int32_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint32_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int64_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint64_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const float &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const double &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const string &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializer::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const void *data, const uint32_t &size) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , data, size);
        }

    }
} // odcore::base

