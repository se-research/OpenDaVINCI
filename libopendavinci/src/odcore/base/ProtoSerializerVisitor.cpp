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

#include "opendavinci/odcore/base/ProtoSerializerVisitor.h"

namespace odcore {
    namespace base {

class Serializable;

        ProtoSerializerVisitor::ProtoSerializerVisitor() :
            m_size(0),
            m_buffer() {}

        ProtoSerializerVisitor::~ProtoSerializerVisitor() {}

        void ProtoSerializerVisitor::getSerializedData(ostream &o) {
            o << m_buffer.str();
        }

        void ProtoSerializerVisitor::getSerializedDataWithHeader(ostream &o) {
            uint16_t magicNumber = 0xAABB;
            encodeVarInt(o, magicNumber);
            encodeVarInt(o, m_size);
            getSerializedData(o);
        }

        uint32_t ProtoSerializerVisitor::getKey(const uint32_t &fieldNumber, const uint8_t &protoType) {
            return (fieldNumber << 3) | protoType;
        }

        uint32_t ProtoSerializerVisitor::writeValue(const uint32_t &id, const ProtoSerializerVisitor::PROTOBUF_TYPE &type, uint64_t value) {
            uint32_t size = 0;
            uint32_t key = getKey(id, type);
            size += encodeVarInt(m_buffer, key);
            size += encodeVarInt(m_buffer, value);
            return size;
        }

        uint8_t ProtoSerializerVisitor::encodeZigZag8(int8_t value) {
            return static_cast<uint8_t>((value << 1) ^ (value >> 7));
        }

        uint16_t ProtoSerializerVisitor::encodeZigZag16(int16_t value) {
            return static_cast<uint16_t>((value << 1) ^ (value >> 15));
        }

        uint32_t ProtoSerializerVisitor::encodeZigZag32(int32_t value) {
            return static_cast<uint32_t>((value << 1) ^ (value >> 31));
        }

        uint64_t ProtoSerializerVisitor::encodeZigZag64(int64_t value) {
            return static_cast<uint64_t>((value << 1) ^ (value >> 63));
        }

        uint8_t ProtoSerializerVisitor::encodeVarInt(ostream &out, uint64_t value) {
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

        void ProtoSerializerVisitor::write(const uint32_t &id, const Serializable &v) {
            uint32_t key = getKey(id, ProtoSerializerVisitor::LENGTH_DELIMITED);
            m_size += encodeVarInt(m_buffer, key);

            // Serialize v.
            stringstream buffer;
            buffer << v;

            // Get serialized value.
            const string tmp = buffer.str();

            // Write length of v into m_buffer.
            uint64_t size = static_cast<uint32_t>(tmp.length());
            m_size += encodeVarInt(m_buffer, size);

            // Write actual value.
            m_buffer.write(tmp.c_str(), size);
            m_size += size;
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const bool &v) {
            m_size += writeValue(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const char &v) {
            m_size += writeValue(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const unsigned char &v) {
            m_size += writeValue(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const int8_t &v) {
            m_size += writeValue(id, ProtoSerializerVisitor::VARINT, encodeZigZag8(v));
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const int16_t &v) {
            m_size += writeValue(id, ProtoSerializerVisitor::VARINT, encodeZigZag16(v));
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const uint16_t &v) {
            m_size += writeValue(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const int32_t &v) {
            m_size += writeValue(id, ProtoSerializerVisitor::VARINT, encodeZigZag32(v));
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const uint32_t &v) {
            m_size += writeValue(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const int64_t &v) {
            m_size += writeValue(id, ProtoSerializerVisitor::VARINT, encodeZigZag64(v));
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const uint64_t &v) {
            m_size += writeValue(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const float &v) {
            uint32_t key = getKey(id, ProtoSerializerVisitor::FOUR_BYTES);
            m_size += encodeVarInt(m_buffer, key);

            float _v = htonf(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const float));
            m_size += sizeof(const float);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const double &v) {
            uint32_t key = getKey(id, ProtoSerializerVisitor::EIGHT_BYTES);
            m_size += encodeVarInt(m_buffer, key);

            double _v = htond(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const double));
            m_size += sizeof(const double);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const string &v) {
            uint32_t key = getKey(id, ProtoSerializerVisitor::LENGTH_DELIMITED);
            m_size += encodeVarInt(m_buffer, key);

            const uint32_t size = v.length();
            m_size += encodeVarInt(m_buffer, size);

            m_buffer.write(v.c_str(), size);
            m_size += size;
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const void *data, const uint32_t &size) {
            uint32_t key = getKey(id, ProtoSerializerVisitor::LENGTH_DELIMITED);
            m_size += encodeVarInt(m_buffer, key);

            m_size += encodeVarInt(m_buffer, size);

            m_buffer.write(reinterpret_cast<const char*>(data), size);
            m_size += size;
        }

        ///////////////////////////////////////////////////////////////////////

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const Serializable &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const bool &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const char &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const unsigned char &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int8_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int16_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint16_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int32_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint32_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int64_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint64_t &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const float &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const double &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const string &v) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const void *data, const uint32_t &size) {
            write( (oneByteID > 0 ? oneByteID : fourByteID) , data, size);
        }

        ///////////////////////////////////////////////////////////////////////

        void ProtoSerializerVisitor::beginVisit() {}

        void ProtoSerializerVisitor::endVisit() {}

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, Serializable &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, bool &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, char &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, unsigned char &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int8_t &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int16_t &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint16_t &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int32_t &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint32_t &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int64_t &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint64_t &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, float &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, double &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, string &v) {
            write(longId, shortId, longName, shortName, v);
        }

        void ProtoSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, void *data, const uint32_t &size) {
            write(longId, shortId, longName, shortName, data, size);
        }

    }
} // odcore::base

