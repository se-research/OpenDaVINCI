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

#ifndef OPENDAVINCI_CORE_SERIALIZATION_PROTODESERIALIZER_H_
#define OPENDAVINCI_CORE_SERIALIZATION_PROTODESERIALIZER_H_

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/ProtoSerializer.h"
#include "opendavinci/odcore/serialization/ProtoSerializerVisitor.h"

namespace odcore {
    namespace serialization {

        using namespace std;

        /**
         * This class represents an entry for the hash map used by
         * ProtoDeserializer.
         */
        class ProtoKeyValue {
            public:
                ProtoKeyValue();

                /**
                 * Constructor.
                 *
                 * @param key Associated Proto key.
                 * @param type Associated Proto type.
                 * @param length Length of the contained value.
                 * @param value Actual value (represented as vector of char making use of the vector's contiguous storage capability).
                 */
                ProtoKeyValue(const uint32_t &key,
                              const ProtoSerializer::PROTOBUF_TYPE &type,
                              const uint64_t &length,
                              const vector<char> &value);

                /**
                 * Constructor.
                 *
                 * @param key Associated Proto key.
                 * @param type Associated Proto type.
                 * @param length Length of the contained value.
                 * @param value Actual VaInt value.
                 */
                ProtoKeyValue(const uint32_t &key,
                              const uint64_t &value);

                uint32_t getKey() const;
                ProtoSerializer::PROTOBUF_TYPE getType() const;
                uint64_t getLength() const;

                /**
                 * This method returns the contained value
                 * as uint64_t (base type for VarInt).
                 *
                 * @return value as uint64_t.
                 */
                uint64_t getValueAsVarInt() const;

                /**
                 * This method returns the contained value
                 * as float.
                 *
                 * @return value as float.
                 */
                float getValueAsFloat() const;

                /**
                 * This method returns the contained value
                 * as double.
                 *
                 * @return value as double.
                 */
                double getValueAsDouble() const;

                /**
                 * This method returns the contained value
                 * as string.
                 *
                 * @return value as string.
                 */
                string getValueAsString() const;

                /**
                 * This method returns a reference to the contained value.
                 *
                 * @return value as reference.
                 */
                const vector<char>& getValue() const;

            private:
                uint32_t m_key;
                ProtoSerializer::PROTOBUF_TYPE m_type;
                uint64_t m_length;
                vector<char> m_value;
                uint64_t m_varIntValue;
        };

        /**
         * This class provides a deserialization to decode data
         * encoded in Google's Protobuf format.
         */
        class ProtoDeserializer : public Deserializer {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ProtoDeserializer(const ProtoDeserializer &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ProtoDeserializer& operator=(const ProtoDeserializer &);

            public:
                ProtoDeserializer();

                /**
                 * Contructor.
                 *
                 * @param i Stream to deserialize data from upon construction.
                 */
                ProtoDeserializer(istream &i);

                virtual ~ProtoDeserializer();

                virtual void deserializeDataFrom(istream &in);

            private:
                /**
                 * This method decodes a value from a given varint encoding.
                 *
                 * @param in Input stream used for reading from.
                 * @param value Destination variable to be written into.
                 * @return size Number of bytes read.
                 */
                uint8_t decodeVarInt(istream& in, uint64_t &value);

                /**
                 * This method decodes a given value using zigzag8 decoding.
                 *
                 * @param value Value to be decoded.
                 * @return size Decoded value.
                 */
                int8_t decodeZigZag8(uint8_t value);

                /**
                 * This method decodes a given value using zigzag16 decoding.
                 *
                 * @param value Value to be decoded.
                 * @return size Decoded value.
                 */
                int16_t decodeZigZag16(uint16_t value);

                /**
                 * This method decodes a given value using zigzag32 decoding.
                 *
                 * @param value Value to be decoded.
                 * @return size Decoded value.
                 */
                int32_t decodeZigZag32(uint32_t value);

                /**
                 * This method decodes a given value using zigzag64 decoding.
                 *
                 * @param value Value to be decoded.
                 * @return size Decoded value.
                 */
                int64_t decodeZigZag64(uint64_t value);

            public:
                virtual uint32_t readValue(istream &i, Serializable &v);
                virtual uint32_t readValue(istream &i, bool &v);
                virtual uint32_t readValue(istream &i, char &v);
                virtual uint32_t readValue(istream &i, unsigned char &v);
                virtual uint32_t readValue(istream &i, int8_t &v);
                virtual uint32_t readValue(istream &i, int16_t &v);
                virtual uint32_t readValue(istream &i, uint16_t &v);
                virtual uint32_t readValue(istream &i, int32_t &v);
                virtual uint32_t readValue(istream &i, uint32_t &v);
                virtual uint32_t readValue(istream &i, int64_t &v);
                virtual uint32_t readValue(istream &i, uint64_t &v);
                virtual uint32_t readValue(istream &i, float &v);
                virtual uint32_t readValue(istream &i, double &v);
                virtual uint32_t readValue(istream &i, string &v);
                virtual uint32_t readValue(istream &i, void *data, const uint32_t &size);

            public:
                virtual void read(const uint32_t &id, Serializable &s);
                virtual void read(const uint32_t &id, bool &b);
                virtual void read(const uint32_t &id, char &c);
                virtual void read(const uint32_t &id, unsigned char &uc);
                virtual void read(const uint32_t &id, int8_t &i);
                virtual void read(const uint32_t &id, int16_t &i);
                virtual void read(const uint32_t &id, uint16_t &ui);
                virtual void read(const uint32_t &id, int32_t &i);
                virtual void read(const uint32_t &id, uint32_t &ui);
                virtual void read(const uint32_t &id, int64_t &i);
                virtual void read(const uint32_t &id, uint64_t &ui);
                virtual void read(const uint32_t &id, float &f);
                virtual void read(const uint32_t &id, double &d);
                virtual void read(const uint32_t &id, string &s);
                virtual void read(const uint32_t &id, void *data, const uint32_t &size);

            public:
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, Serializable &s);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, bool &b);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, char &c);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, unsigned char &uc);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, int8_t &i);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, int16_t &i);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, uint16_t &ui);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, int32_t &i);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, uint32_t &ui);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, int64_t &i);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, uint64_t &ui);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, float &f);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, double &d);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, string &s);
                virtual void read(const uint32_t &id, const string &longName, const string &shortName, void *data, const uint32_t &size);

            private:
                /**
                 * This method reads and validates the key for the next value.
                 *
                 * @param in Stream to read data from.
                 * @param id Identifier to be matched with the key read from the stream.
                 * @param expectedType Proto type to be expected from the stream.
                 * @return Bytes consumed.
                 */
                uint32_t readAndValidateKey(istream &in, const uint32_t &id, const ProtoSerializer::PROTOBUF_TYPE &expectedType);

            private:
                stringstream m_buffer;
                map<uint32_t, ProtoKeyValue> m_mapOfKeyValues;
        };

    }
} // odcore::serialization

#endif /*OPENDAVINCI_CORE_SERIALIZATION_PROTODESERIALIZER_H_*/
