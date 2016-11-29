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

#include <cstring>
#include <iostream>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/ProtoDeserializer.h"
#include "opendavinci/odcore/serialization/ProtoDeserializerVisitor.h"
#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/reflection/MessageFromVisitableVisitor.h"
#include "opendavinci/odcore/reflection/Message.h"

namespace odcore {
    namespace serialization {

class Serializable;

        ProtoKeyValue::ProtoKeyValue() :
            m_key(0),
            m_type(ProtoSerializer::UNUSED_7),
            m_length(0),
            m_value(),
            m_varIntValue(0) {}

        ProtoKeyValue::ProtoKeyValue(const uint32_t &key,
                                     const ProtoSerializer::PROTOBUF_TYPE &type,
                                     const uint64_t &length) :
            m_key(key),
            m_type(type),
            m_length(length),
            m_value(length),
            m_varIntValue(0) {}

        ProtoKeyValue::ProtoKeyValue(const uint32_t &key,
                                     const ProtoSerializer::PROTOBUF_TYPE &type,
                                     const uint64_t &length,
                                     const vector<char> &value) :
            m_key(key),
            m_type(type),
            m_length(length),
            m_value(value),
            m_varIntValue(0) {}

        ProtoKeyValue::ProtoKeyValue(const uint32_t &key,
                                     const uint64_t &value) :
            m_key(key),
            m_type(ProtoSerializer::VARINT),
            m_length(0),
            m_value(),
            m_varIntValue(value) {}

        uint32_t ProtoKeyValue::getKey() const {
            return m_key;
        }

        ProtoSerializer::PROTOBUF_TYPE ProtoKeyValue::getType() const {
            return m_type;
        }

        uint64_t ProtoKeyValue::getLength() const {
            return m_length;
        }

        uint64_t ProtoKeyValue::getValueAsVarInt() const {
            uint64_t retVal = 0;
            if (m_type == ProtoSerializer::VARINT) {
                retVal = m_varIntValue;
            }
            return retVal;
        }

        float ProtoKeyValue::getValueAsFloat() const {
            float retVal = 0;
            if ( (m_value.size() > 0) && (m_length == sizeof(float)) && (m_value.size() == sizeof(float)) && (m_type == ProtoSerializer::FOUR_BYTES) ) {
                memcpy(&retVal, &m_value[0], sizeof(float));
            }
            return retVal;
        }

        double ProtoKeyValue::getValueAsDouble() const {
            double retVal = 0;
            if ( (m_value.size() > 0) && (m_length == sizeof(double)) && (m_value.size() == sizeof(double)) && (m_type == ProtoSerializer::EIGHT_BYTES) ) {
                memcpy(&retVal, &m_value[0], sizeof(double));
            }
            return retVal;
        }

        string ProtoKeyValue::getValueAsString() const {
            string retVal = "";
            if ( (m_value.size() > 0) && (m_length > 0) && (m_type == ProtoSerializer::LENGTH_DELIMITED) ) {
                // Create string from buffer.
                retVal = string(&m_value[0], &m_value[m_length]);
            }
            return retVal;
        }

        const vector<char>& ProtoKeyValue::getValue() const {
            return m_value;
        }

        vector<char>& ProtoKeyValue::getRawBuffer() {
            return m_value;
        }

        ///////////////////////////////////////////////////////////////////////

        ProtoDeserializer::ProtoDeserializer() :
            m_buffer(),
            m_mapOfKeyValues() {}

        ProtoDeserializer::ProtoDeserializer(istream &i) :
            m_buffer(),
            m_mapOfKeyValues() {
            deserializeDataFrom(i);
        }

        ProtoDeserializer::~ProtoDeserializer() {}

        void ProtoDeserializer::deserializeDataFrom(istream &in) {
            // Reset internal states as this deserializer could be reused.
            m_buffer.str("");
            m_mapOfKeyValues.clear();

            while (in.good()) {
                // First stage: Read keyFieldType (encoded as VarInt).
                uint64_t keyFieldType = 0;
                uint8_t bytesRead = decodeVarInt(in, keyFieldType);

                if (bytesRead > 0) {
                    // Succeeded to read keyFieldType entry; extract information.
                    const uint32_t fieldId = static_cast<uint32_t>(keyFieldType >> 3);
                    const ProtoSerializer::PROTOBUF_TYPE protoType = static_cast<ProtoSerializer::PROTOBUF_TYPE>(keyFieldType & 0x7);

                    if (protoType == ProtoSerializer::VARINT) {
                        // Read VarInt value directly.
                        uint64_t value = 0;
                        bytesRead = decodeVarInt(in, value);
                        ProtoKeyValue pkv(fieldId, value);
                        m_mapOfKeyValues[fieldId] = pkv;
                    }

                    if (protoType == ProtoSerializer::EIGHT_BYTES) {
                        const uint8_t BYTES_TO_READ_INTO_BUFFER = sizeof(double);
                        uint8_t bytesToRead = BYTES_TO_READ_INTO_BUFFER;
                        uint32_t bufferPosition = 0;

                        // Create map entry here...
                        ProtoKeyValue pkv(fieldId, ProtoSerializer::EIGHT_BYTES, BYTES_TO_READ_INTO_BUFFER);
                        // ...to avoid copying data later.
                        vector<char> &buffer = pkv.getRawBuffer();

                        while (in.good() && (bytesToRead > 0)) {
                            in.read(&buffer[bufferPosition], (bytesToRead > BYTES_TO_READ_INTO_BUFFER) ? BYTES_TO_READ_INTO_BUFFER : bytesToRead);
                            const streamsize extractedBytes = in.gcount();
                            bufferPosition += extractedBytes;
                            bytesToRead -= extractedBytes;
                        }

                        // Store map entry.
                        m_mapOfKeyValues[fieldId] = pkv;
                    }

                    if (protoType == ProtoSerializer::FOUR_BYTES) {
                        const uint8_t BYTES_TO_READ_INTO_BUFFER = sizeof(float);
                        uint8_t bytesToRead = BYTES_TO_READ_INTO_BUFFER;
                        uint32_t bufferPosition = 0;

                        // Create map entry here...
                        ProtoKeyValue pkv(fieldId, ProtoSerializer::FOUR_BYTES, BYTES_TO_READ_INTO_BUFFER);
                        // ...to avoid copying data later.
                        vector<char> &buffer = pkv.getRawBuffer();

                        while (in.good() && (bytesToRead > 0)) {
                            in.read(&buffer[bufferPosition], (bytesToRead > BYTES_TO_READ_INTO_BUFFER) ? BYTES_TO_READ_INTO_BUFFER : bytesToRead);
                            const streamsize extractedBytes = in.gcount();
                            bufferPosition += extractedBytes;
                            bytesToRead -= extractedBytes;
                        }

                        // Store map entry.
                        m_mapOfKeyValues[fieldId] = pkv;
                    }

                    if (protoType == ProtoSerializer::LENGTH_DELIMITED) {
                        const uint16_t BYTES_TO_READ_INTO_BUFFER = 1024;

                        uint64_t length = 0;
                        bytesRead = decodeVarInt(in, length);
                        uint64_t bytesToRead = length;

                        uint32_t bufferPosition = 0;

                        // Create map entry here...
                        ProtoKeyValue pkv(fieldId, ProtoSerializer::LENGTH_DELIMITED, length);
                        // ...to avoid copying data later.
                        vector<char> &buffer = pkv.getRawBuffer();

                        while (in.good() && (bytesToRead > 0)) {
                            in.read(&buffer[bufferPosition], (bytesToRead > BYTES_TO_READ_INTO_BUFFER) ? BYTES_TO_READ_INTO_BUFFER : bytesToRead);
                            const streamsize extractedBytes = in.gcount();
                            bufferPosition += extractedBytes;
                            bytesToRead -= extractedBytes;
                        }

                        // Store map entry.
                        m_mapOfKeyValues[fieldId] = pkv;
                    }
                }
            }
        }

        uint8_t ProtoDeserializer::decodeVarInt(istream &in, uint64_t &value) {
            value = 0;
            uint8_t size = 0;
            char c = 0;
            while (in.good()) {
                c = in.get();
                value |= static_cast<unsigned int>( (c & 0x7f) << (0x7 * size++) );
                if ( !(c & 0x80) ) break;
            }

            // Protobuf's VarInt is based on little endian.
            value = le64toh(value);

            return size;
        }

        ///////////////////////////////////////////////////////////////////////

        uint32_t ProtoDeserializer::readAndValidateKey(istream &in, const uint32_t &id, const ProtoSerializer::PROTOBUF_TYPE &expectedType) {
            uint64_t key = 0;
            const uint32_t size = decodeVarInt(in, key);
            const uint32_t fieldId = static_cast<uint32_t>(key >> 3);
            const ProtoSerializer::PROTOBUF_TYPE protoType = static_cast<ProtoSerializer::PROTOBUF_TYPE>(key & 0x7);

            if (fieldId != id) {
                clog << "[core::serialization::ProtoDeserializer]: ERROR! Field ids do not match: Found " << fieldId << ", expected: " << id << endl;
            }
            if (protoType != expectedType) {
                clog << "[core::serialization::ProtoDeserializer]: ERROR! Expected type does not match: Found " << protoType << ", expected " << expectedType << endl;
            }

            return size;
        }

        int8_t ProtoDeserializer::decodeZigZag8(uint8_t value) {
            return static_cast<int64_t>((value >> 1) ^ -(value & 1));
        }

        int16_t ProtoDeserializer::decodeZigZag16(uint16_t value) {
            return static_cast<int64_t>((value >> 1) ^ -(value & 1));
        }

        int32_t ProtoDeserializer::decodeZigZag32(uint32_t value) {
            return static_cast<int64_t>((value >> 1) ^ -(value & 1));
        }

        int64_t ProtoDeserializer::decodeZigZag64(uint64_t value) {
            return static_cast<int64_t>((value >> 1) ^ -(value & 1));
        }

        ///////////////////////////////////////////////////////////////////////

        uint32_t ProtoDeserializer::readValue(istream &i, Serializable &v) {
            uint32_t bytesRead = 0;

            // Read length.
            uint64_t length = 0;
            bytesRead += decodeVarInt(i, length);

            // Create contiguous buffer.
            vector<char> buffer(length);

            // Read data from stream.
            i.read(&buffer[0], length);
            bytesRead += length;

            // Read Serializable from buffer.
            stringstream sstr;
            sstr.rdbuf()->pubsetbuf(&buffer[0], length);
            sstr >> v;

            return bytesRead;
        }

        uint32_t ProtoDeserializer::readValue(istream &i, bool &v) {
            uint64_t _v = 0;
            uint32_t bytesRead = decodeVarInt(i, _v);
            v = static_cast<bool>(_v);
            return bytesRead;
        }

        uint32_t ProtoDeserializer::readValue(istream &i, char &v) {
            uint64_t _v = 0;
            uint32_t bytesRead = decodeVarInt(i, _v);
            v = static_cast<char>(_v);
            return bytesRead;
        }

        uint32_t ProtoDeserializer::readValue(istream &i, unsigned char &v) {
            uint64_t _v = 0;
            uint32_t bytesRead = decodeVarInt(i, _v);
            v = static_cast<unsigned char>(_v);
            return bytesRead;
        }

        uint32_t ProtoDeserializer::readValue(istream &i, int8_t &v) {
            uint64_t _v = 0;
            uint32_t bytesRead = decodeVarInt(i, _v);
            v = static_cast<int8_t>(decodeZigZag8(_v));
            return bytesRead;
        }

        uint32_t ProtoDeserializer::readValue(istream &i, int16_t &v) {
            uint64_t _v = 0;
            uint32_t bytesRead = decodeVarInt(i, _v);
            v = static_cast<int16_t>(decodeZigZag16(_v));
            return bytesRead;
        }

        uint32_t ProtoDeserializer::readValue(istream &i, uint16_t &v) {
            uint64_t _v = 0;
            uint32_t bytesRead = decodeVarInt(i, _v);
            v = static_cast<uint16_t>(_v);
            return bytesRead;
        }

        uint32_t ProtoDeserializer::readValue(istream &i, int32_t &v) {
            uint64_t _v = 0;
            uint32_t bytesRead = decodeVarInt(i, _v);
            v = static_cast<int32_t>(decodeZigZag32(_v));
            return bytesRead;
        }

        uint32_t ProtoDeserializer::readValue(istream &i, uint32_t &v) {
            uint64_t _v = 0;
            uint32_t bytesRead = decodeVarInt(i, _v);
            v = static_cast<uint32_t>(_v);
            return bytesRead;
        }

        uint32_t ProtoDeserializer::readValue(istream &i, int64_t &v) {
            uint64_t _v = 0;
            uint32_t bytesRead = decodeVarInt(i, _v);
            v = static_cast<int64_t>(decodeZigZag64(_v));
            return bytesRead;
        }

        uint32_t ProtoDeserializer::readValue(istream &i, uint64_t &v) {
            uint64_t _v = 0;
            uint32_t bytesRead = decodeVarInt(i, _v);
            v = _v;
            return bytesRead;
        }

        uint32_t ProtoDeserializer::readValue(istream &i, float &v) {
            // 4 bytes values need to obey little endian encoding.
            uint32_t _v = 0;
            i.read(reinterpret_cast<char*>(&_v), sizeof(uint32_t));
            _v = le32toh(_v);
            v = *(reinterpret_cast<float*>(&_v));
            return sizeof(const uint32_t);
        }

        uint32_t ProtoDeserializer::readValue(istream &i, double &v) {
            // 8 bytes values need to obey little endian encoding.
            uint64_t _v = 0;
            i.read(reinterpret_cast<char*>(&_v), sizeof(uint64_t));
            _v = le64toh(_v);
            v = *(reinterpret_cast<double*>(&_v));
            return sizeof(const uint64_t);
        }

        uint32_t ProtoDeserializer::readValue(istream &i, string &v) {
            uint32_t bytesRead = 0;

            // Read length.
            uint64_t length = 0;
            bytesRead += decodeVarInt(i, length);

            // Create contiguous buffer.
            vector<char> buffer(length);

            // Read data from stream.
            i.read(&buffer[0], length);
            bytesRead += length;

            // Create string from buffer.
            v = string(&buffer[0], &buffer[length]);

            return bytesRead;
        }

        uint32_t ProtoDeserializer::readValue(istream &i, void *data, const uint32_t &size) {
            uint32_t bytesRead = 0;

            // Read length.
            uint64_t length = 0;
            bytesRead += decodeVarInt(i, length);

            // Read data.
            char *_data = new char[length];
            i.read(_data, length);
            bytesRead += length;

            // Move data.
            memset(data, 0, size);
            memcpy(data, _data, (size < length ? size : length));
            OPENDAVINCI_CORE_DELETE_ARRAY(_data);

            return bytesRead;
        }

        ///////////////////////////////////////////////////////////////////////

        void ProtoDeserializer::read(const uint32_t &id, Serializable &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                vector<char> &value = const_cast<vector<char>&>(m_mapOfKeyValues[id].getValue());
                stringstream sstr;
                sstr.rdbuf()->pubsetbuf(&value[0], value.size());
                sstr >> v;
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, bool &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                uint64_t _v = m_mapOfKeyValues[id].getValueAsVarInt();
                v = static_cast<bool>(_v);
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, char &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                uint64_t _v = m_mapOfKeyValues[id].getValueAsVarInt();
                v = static_cast<char>(_v);
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, unsigned char &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                uint64_t _v = m_mapOfKeyValues[id].getValueAsVarInt();
                v = static_cast<unsigned char>(_v);
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, int8_t &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                uint64_t _v = m_mapOfKeyValues[id].getValueAsVarInt();
                v = static_cast<int8_t>(decodeZigZag8(_v));
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, int16_t &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                uint64_t _v = m_mapOfKeyValues[id].getValueAsVarInt();
                v = static_cast<int16_t>(decodeZigZag16(_v));
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, uint16_t &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                uint64_t _v = m_mapOfKeyValues[id].getValueAsVarInt();
                v = static_cast<uint16_t>(_v);
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, int32_t &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                uint64_t _v = m_mapOfKeyValues[id].getValueAsVarInt();
                v = static_cast<int32_t>(decodeZigZag32(_v));
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, uint32_t &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                uint64_t _v = m_mapOfKeyValues[id].getValueAsVarInt();
                v = static_cast<uint32_t>(_v);
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, int64_t &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                uint64_t _v = m_mapOfKeyValues[id].getValueAsVarInt();
                v = static_cast<int64_t>(decodeZigZag64(_v));
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, uint64_t &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                v = m_mapOfKeyValues[id].getValueAsVarInt();
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, float &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                v = m_mapOfKeyValues[id].getValueAsFloat();
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, double &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                v = m_mapOfKeyValues[id].getValueAsDouble();
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, string &v) {
            if (m_mapOfKeyValues.count(id) > 0) {
                v = m_mapOfKeyValues[id].getValueAsString();
            }
        }

        void ProtoDeserializer::read(const uint32_t &id, void *data, const uint32_t &size) {
            if (m_mapOfKeyValues.count(id) > 0) {
                const vector<char> &value = m_mapOfKeyValues[id].getValue();
                memcpy(data, &value[0], (size < value.size() ? size : value.size()));
                if (size > value.size()) {
                    memset((char*)data + value.size(), 0, (size - value.size()));
                }
            }
        }

        ///////////////////////////////////////////////////////////////////////

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, Serializable &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, bool &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, char &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, unsigned char &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, int8_t &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, int16_t &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, uint16_t &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, int32_t &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, uint32_t &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, int64_t &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, uint64_t &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, float &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, double &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, string &v) {
            read(id, v);
        }

        void ProtoDeserializer::read(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, void *data, const uint32_t &size) {
            read(id, data, size);
        }

    }
} // odcore::serialization

