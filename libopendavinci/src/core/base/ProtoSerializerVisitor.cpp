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

#include <endian.h>
#include <iostream>

#include "core/base/ProtoSerializerVisitor.h"

namespace core {
    namespace base {

class Serializable;

        ProtoSerializerVisitor::ProtoSerializerVisitor() :
            m_size(0),
            m_buffer() {}

        ProtoSerializerVisitor::~ProtoSerializerVisitor() {}

        void ProtoSerializerVisitor::getSerializedDataNoHeader(ostream &o) {
            o << m_buffer.str();
        }

        void ProtoSerializerVisitor::getSerializedData(ostream &o) {
            uint16_t magicNumber = 0xAABB;
            encodeVarInt(o, magicNumber);
            encodeVarInt(o, m_size);
            getSerializedDataNoHeader(o);
        }

        uint32_t ProtoSerializerVisitor::getKey(const uint32_t &fieldNumber, const uint8_t &protoType) {
            return (fieldNumber << 3) | protoType;
        }

        uint32_t ProtoSerializerVisitor::write(const uint32_t &id, const ProtoSerializerVisitor::PROTOBUF_TYPE &type, uint64_t value) {
            uint32_t size = 0;
            uint32_t key = getKey(id, type);
            size += encodeVarInt(m_buffer, key);
            size += encodeVarInt(m_buffer, value);
            return size;
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

        void ProtoSerializerVisitor::write(const uint32_t &/*id*/, const Serializable &/*v*/) {}

        void ProtoSerializerVisitor::write(const uint32_t &id, const bool &v) {
            m_size += write(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const char &v) {
            m_size += write(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const unsigned char &v) {
            m_size += write(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const int8_t &v) {
            m_size += write(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const int16_t &v) {
            m_size += write(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const uint16_t &v) {
            m_size += write(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const int32_t &v) {
            m_size += write(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const uint32_t &v) {
            m_size += write(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const int64_t &v) {
            m_size += write(id, ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &id, const uint64_t &v) {
            m_size += write(id, ProtoSerializerVisitor::VARINT, v);
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

        void ProtoSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const Serializable &/*v*/) {
            cerr << "[core::base::ProtoSerializerVisitor]: write(const uint32_t&, const uint8_t&, const string&, const string&, Serializable&) not implemented!" << endl;
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const bool &v) {
            m_size += write( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const char &v) {
            m_size += write( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const unsigned char &v) {
            m_size += write( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int8_t &v) {
            m_size += write( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int16_t &v) {
            m_size += write( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint16_t &v) {
            m_size += write( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int32_t &v) {
            m_size += write( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint32_t &v) {
            m_size += write( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int64_t &v) {
            m_size += write( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint64_t &v) {
            m_size += write( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::VARINT, v);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const float &v) {
            uint32_t key = getKey( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::FOUR_BYTES);
            m_size += encodeVarInt(m_buffer, key);

            float _v = htonf(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const float));
            m_size += sizeof(const float);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const double &v) {
            uint32_t key = getKey( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::EIGHT_BYTES);
            m_size += encodeVarInt(m_buffer, key);

            double _v = htond(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const double));
            m_size += sizeof(const double);
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const string &v) {
            uint32_t key = getKey( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::LENGTH_DELIMITED);
            m_size += encodeVarInt(m_buffer, key);

            const uint32_t size = v.length();
            m_size += encodeVarInt(m_buffer, size);

            m_buffer.write(v.c_str(), size);
            m_size += size;
        }

        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const void *data, const uint32_t &size) {
            uint32_t key = getKey( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::LENGTH_DELIMITED);
            m_size += encodeVarInt(m_buffer, key);

            m_size += encodeVarInt(m_buffer, size);

            m_buffer.write(reinterpret_cast<const char*>(data), size);
            m_size += size;
        }


        void ProtoSerializerVisitor::visit(const uint32_t &/*longId*/, const uint8_t &/*shortId*/, const string &/*longName*/, const string &/*shortName*/, Serializable &/*v*/) {
            cerr << "[core::base::ProtoSerializerVisitor]: Proto for Serializable not implemented!" << endl;
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
} // core::base

