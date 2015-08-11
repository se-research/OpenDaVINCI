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

#include "core/base/ProtoSerializerVisitor.h"
#include "core/base/ProtoDeserializerVisitor.h"

namespace core {
    namespace base {

        ProtoDeserializerVisitor::ProtoDeserializerVisitor() :
            m_size(0),
            m_buffer() {}

        ProtoDeserializerVisitor::~ProtoDeserializerVisitor() {}

        void ProtoDeserializerVisitor::deserializeDataFrom(istream &in) {
            // Reset internal states as this deserializer could be reused.
            m_size = 0;
            m_buffer.str("");

            // Read magic number.
            uint64_t value = 0;
            decodeVarInt(in, value);
            uint16_t magicNumber = static_cast<uint16_t>(value);
            if (magicNumber == 0xAABB) {
                // Read message size and put remaining bytes into m_buffer.
                decodeVarInt(in, value);
                m_size = static_cast<uint32_t>(value);

                while (in.good()) {
                    char c = in.get();
                    m_buffer.put(c);            
                }
            }
            else {
                // Stream is good but still no matching magic number?
                clog << "[core::base::ProtoDeserializerVisitor]: Stream corrupt: magic number not found." << endl;
            }
        }

        uint32_t ProtoDeserializerVisitor::readAndValidateKey(const uint32_t &id, const ProtoSerializerVisitor::PROTOBUF_TYPE &expectedType) {
            uint64_t key = 0;
            const uint32_t size = decodeVarInt(m_buffer, key);
            const uint32_t fieldId = static_cast<uint32_t>(key >> 3);
            const ProtoSerializerVisitor::PROTOBUF_TYPE protoType = static_cast<ProtoSerializerVisitor::PROTOBUF_TYPE>(key & 0x7);

            if (fieldId != id) {
                clog << "[core::base::ProtoDeserializerVisitor]: ERROR! Field ids do not match: Found " << fieldId << ", expected: " << id << endl;
            }
            if (protoType != expectedType) {
                clog << "[core::base::ProtoDeserializerVisitor]: ERROR! Expected type does not match: Found " << protoType << ", expected " << expectedType << endl;
            }

            return size;
        }

        uint32_t ProtoDeserializerVisitor::decodeVarInt(istream &in, uint64_t &value) {
            value = 0;
            uint8_t size = 0;
            while (in.good()) {
                char c = in.get();
                value |= (c & 0x7f) << (0x7 * size++);
                if ( !(c & 0x80) ) break;
            }

            // Protobuf's VarInt is based on little endian.            
            value = le64toh(value);

            return size;
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, Serializable &v) {
            (void)id;
            (void)v;
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, bool &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::VARINT);

            uint64_t _v = 0;
            m_size -= decodeVarInt(m_buffer, _v);
            v = static_cast<bool>(_v);
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, char &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::VARINT);

            uint64_t _v = 0;
            m_size -= decodeVarInt(m_buffer, _v);
            v = static_cast<char>(_v);
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, unsigned char &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::VARINT);

            uint64_t _v = 0;
            m_size -= decodeVarInt(m_buffer, _v);
            v = static_cast<unsigned char>(_v);
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, int8_t &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::VARINT);

            uint64_t _v = 0;
            m_size -= decodeVarInt(m_buffer, _v);
            v = static_cast<int8_t>(_v);
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, int16_t &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::VARINT);

            uint64_t _v = 0;
            m_size -= decodeVarInt(m_buffer, _v);
            v = static_cast<int16_t>(_v);
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, uint16_t &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::VARINT);

            uint64_t _v = 0;
            m_size -= decodeVarInt(m_buffer, _v);
            v = static_cast<uint16_t>(_v);
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, int32_t &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::VARINT);

            uint64_t _v = 0;
            m_size -= decodeVarInt(m_buffer, _v);
            v = static_cast<int32_t>(_v);
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, uint32_t &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::VARINT);

            uint64_t _v = 0;
            m_size -= decodeVarInt(m_buffer, _v);
            v = static_cast<uint32_t>(_v);
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, int64_t &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::VARINT);

            uint64_t _v = 0;
            m_size -= decodeVarInt(m_buffer, _v);
            v = static_cast<int64_t>(_v);
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, uint64_t &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::VARINT);

            uint64_t _v = 0;
            m_size -= decodeVarInt(m_buffer, _v);
            v = _v;
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, float &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::FOUR_BYTES);

            float _f =0;
            m_buffer.read(reinterpret_cast<char *>(&_f), sizeof(float));
            v = Deserializer::ntohf(_f);
            m_size -= sizeof(float);
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, double &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::EIGHT_BYTES);

            double _d =0;
            m_buffer.read(reinterpret_cast<char*>(&_d), sizeof(double));
            v = Deserializer::ntohd(_d);
            m_size -= sizeof(double);
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, string &v) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::LENGTH_DELIMITED);

            // Read length.
            uint64_t length = 0;
            m_size -= decodeVarInt(m_buffer, length);

            // Read string.
            char *str = new char[length+1];
            m_buffer.read(str, length);
            m_size -= length;

            // Create string.
            str[length] = 0;
            v = string(str, length);
            OPENDAVINCI_CORE_DELETE_ARRAY(str);
        }

        void ProtoDeserializerVisitor::read(const uint32_t &id, void *data, const uint32_t &size) {
            m_size -= readAndValidateKey(id, ProtoSerializerVisitor::LENGTH_DELIMITED);

            // Read length.
            uint64_t length = 0;
            m_size -= decodeVarInt(m_buffer, length);

            // Read data.
            char *_data = new char[length];
            m_buffer.read(_data, length);
            m_size -= length;

            // Move data.
            memset(data, 0, size);
            memcpy(data, _data, (size < length ? size : length));
            OPENDAVINCI_CORE_DELETE_ARRAY(_data);
        }


        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,Serializable &v) {
            (void)longId;
            (void)shortId;
            (void)v;
            cerr << "[core::base::ProtoDeserializerVisitor]: Proto for Serializable not implemented!" << endl;
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,bool &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,char &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,unsigned char &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,int8_t &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,int16_t &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,uint16_t &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,int32_t &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,uint32_t &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,int64_t &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,uint64_t &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,float &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,double &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,string &v) {
            read( (shortId > 0 ? shortId : longId), v);
        }

        void ProtoDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &/*longName*/, const string &/*shortName*/,void *data, const uint32_t &size) {
            read( (shortId > 0 ? shortId : longId), data, size);
        }

    }
} // core::base

