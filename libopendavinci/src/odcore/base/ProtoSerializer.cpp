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
            m_buffer() {}

        ProtoSerializer::ProtoSerializer(ostream &o) :
            m_out(&o),
            m_buffer() {}

        ProtoSerializer::~ProtoSerializer() {
            if (m_out != NULL) {
                getSerializedData(*m_out);
            }
        }

        void ProtoSerializer::getSerializedData(ostream &o) {
            o << m_buffer.str();
        }

        uint64_t ProtoSerializer::getKey(const uint32_t &fieldNumber, const uint8_t &protoType) {
            return (fieldNumber << 3) | protoType;
        }

        ///////////////////////////////////////////////////////////////////////

        uint32_t ProtoSerializer::writeValue(ostream &o, const Serializable &v) {
            // Buffer for serialized data.
            stringstream buffer;

//            // Check whether v is from type Visitable to use ProtoSerializer.
//            try {
//                const Visitable &v2 = dynamic_cast<const Visitable&>(v);

//                // Cast succeeded, visited nested class using a ProtoSerializer.
//                ProtoSerializerVisitor nestedVisitor;
//                const_cast<Visitable&>(v2).accept(nestedVisitor);

//                // Get serialized data.
//                nestedVisitor.getSerializedData(buffer);
//            }
//            catch(...) {
//                // Serialize v using the default way as it is not of type Visitable.
//                buffer << v;
//            }

cout << __FILE__ << " " << __LINE__ << endl;
            buffer << v;
cout << __FILE__ << " " << __LINE__ << endl;

            // Get serialized value.
            const string tmp = buffer.str();
const string s = tmp;
for(unsigned int i = 0; i < s.size(); i++) {
    cout << hex << (uint32_t)(uint8_t)s.at(i) << " ";
}
cout << dec << endl;

cout << __FILE__ << " " << __LINE__ << endl;
            return writeValue(o, tmp);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const bool &v) {
            uint64_t value = v;
            return encodeVarInt(o, value);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const char &v) {
            uint64_t value = v;
            return encodeVarInt(o, value);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const unsigned char &v) {
            uint64_t value = v;
            return encodeVarInt(o, value);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const int8_t &v) {
            uint64_t value = encodeZigZag8(v);
            return encodeVarInt(o, value);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const int16_t &v) {
            uint64_t value = encodeZigZag16(v);
            return encodeVarInt(o, value);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const uint16_t &v) {
            uint64_t value = v;
            return encodeVarInt(o, value);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const int32_t &v) {
            uint64_t value = encodeZigZag32(v);
            return encodeVarInt(o, value);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const uint32_t &v) {
            uint64_t value = v;
            return encodeVarInt(o, value);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const int64_t &v) {
            uint64_t value = encodeZigZag64(v);
            return encodeVarInt(o, value);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const uint64_t &v) {
            uint64_t value = v;
            return encodeVarInt(o, value);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const float &v) {
            // 4 bytes values need to obey little endian encoding.
            uint32_t _v = htole32(*(reinterpret_cast<const uint32_t*>(&v)));
            o.write(reinterpret_cast<const char*>(&_v), sizeof(const uint32_t));
            return sizeof(const uint32_t);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const double &v) {
            // 8 bytes values need to obey little endian encoding.
            uint64_t _v = htole64(*(reinterpret_cast<const uint64_t*>(&v)));
            o.write(reinterpret_cast<const char*>(&_v), sizeof(const uint64_t));
            return sizeof(const uint64_t);
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const string &v) {
            uint32_t bytesWritten = 0;

cout << __FILE__ << " " << __LINE__ << endl;
            const uint32_t size = v.length();
            bytesWritten += encodeVarInt(o, size);

            o.write(v.c_str(), size);
            bytesWritten += size;
cout << __FILE__ << " " << __LINE__ << endl;

            return bytesWritten;
        }

        uint32_t ProtoSerializer::writeValue(ostream &o, const void *data, const uint32_t &size) {
            uint32_t bytesWritten = 0;

            bytesWritten += encodeVarInt(m_buffer, size);

            o.write(reinterpret_cast<const char*>(data), size);
            bytesWritten += size;

            return bytesWritten;
        }

        ///////////////////////////////////////////////////////////////////////

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
            encodeVarInt(m_buffer, key);
            writeValue(m_buffer, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const bool &v) {
            writeKeyValue<const bool>(id, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const char &v) {
            writeKeyValue<const char>(id, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const unsigned char &v) {
            writeKeyValue<const unsigned>(id, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const int8_t &v) {
            writeKeyValue<const int8_t>(id, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const int16_t &v) {
            writeKeyValue<const int16_t>(id, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const uint16_t &v) {
            writeKeyValue<const uint16_t>(id, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const int32_t &v) {
            writeKeyValue<const int32_t>(id, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const uint32_t &v) {
            writeKeyValue<const uint32_t>(id, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const int64_t &v) {
            writeKeyValue<const int64_t>(id, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const uint64_t &v) {
            writeKeyValue<const uint64_t>(id, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const float &v) {
            uint32_t key = getKey(id, ProtoSerializer::FOUR_BYTES);
            encodeVarInt(m_buffer, key);
            writeValue(m_buffer, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const double &v) {
            uint32_t key = getKey(id, ProtoSerializer::EIGHT_BYTES);
            encodeVarInt(m_buffer, key);
            writeValue(m_buffer, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const string &v) {
            uint32_t key = getKey(id, ProtoSerializer::LENGTH_DELIMITED);
            encodeVarInt(m_buffer, key);
            writeValue(m_buffer, v);
        }

        void ProtoSerializer::write(const uint32_t &id, const void *data, const uint32_t &size) {
            uint32_t key = getKey(id, ProtoSerializer::LENGTH_DELIMITED);
            encodeVarInt(m_buffer, key);
            writeValue(m_buffer, data, size);
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

