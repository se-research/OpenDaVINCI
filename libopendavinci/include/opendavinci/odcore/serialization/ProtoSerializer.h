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

#ifndef OPENDAVINCI_CORE_BASE_PROTOSERIALIZER_H_
#define OPENDAVINCI_CORE_BASE_PROTOSERIALIZER_H_

#include <sstream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Serializer.h"

namespace odcore {
    namespace base {

class Serializable;

        using namespace std;

        /**
         * This class provides a serialization to encode data
         * in Google's Protobuf format.
         */
        class ProtoSerializer : public Serializer {
            public:
                // Protobuf type specification.
                enum PROTOBUF_TYPE { VARINT           = 0,
                                     EIGHT_BYTES      = 1,
                                     LENGTH_DELIMITED = 2,
                                     UNUSED_3         = 3, // START_GROUP_DEPRECATED
                                     UNUSED_4         = 4, // END_GROUP_DEPRECATED
                                     FOUR_BYTES       = 5,
                                     UNUSED_6         = 6,
                                     UNUSED_7         = 7 };

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ProtoSerializer(const ProtoSerializer &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ProtoSerializer& operator=(const ProtoSerializer &);

            public:
                ProtoSerializer();

                /**
                 * Contructor.
                 *
                 * @param o Stream to serialize data to when the destructor is called.
                 */
                ProtoSerializer(ostream &o);

                virtual ~ProtoSerializer();

                virtual void getSerializedData(ostream &o);

            private:
                /**
                 * This method encodes a given value using the varuint encoding.
                 *
                 * @param out Output stream to be written to.
                 * @param value Value to be encoded.
                 * @return size Number of bytes written.
                 */
                uint8_t encodeVarInt(ostream &out, uint64_t value);

                /**
                 * This method encodes a given value using zigzag8 encoding.
                 *
                 * @param value Value to be encoded.
                 * @return size Encoded value.
                 */
                uint8_t encodeZigZag8(int8_t value);

                /**
                 * This method encodes a given value using zigzag16 encoding.
                 *
                 * @param value Value to be encoded.
                 * @return size Encoded value.
                 */
                uint16_t encodeZigZag16(int16_t value);

                /**
                 * This method encodes a given value using zigzag32 encoding.
                 *
                 * @param value Value to be encoded.
                 * @return size Encoded value.
                 */
                uint32_t encodeZigZag32(int32_t value);

                /**
                 * This method encodes a given value using zigzag64 encoding.
                 *
                 * @param value Value to be encoded.
                 * @return size Encoded value.
                 */
                uint64_t encodeZigZag64(int64_t value);

            public:
                virtual uint32_t writeValue(ostream &o, const Serializable &v);
                virtual uint32_t writeValue(ostream &o, const bool &v);
                virtual uint32_t writeValue(ostream &o, const char &v);
                virtual uint32_t writeValue(ostream &o, const unsigned char &v);
                virtual uint32_t writeValue(ostream &o, const int8_t &v);
                virtual uint32_t writeValue(ostream &o, const int16_t &v);
                virtual uint32_t writeValue(ostream &o, const uint16_t &v);
                virtual uint32_t writeValue(ostream &o, const int32_t &v);
                virtual uint32_t writeValue(ostream &o, const uint32_t &v);
                virtual uint32_t writeValue(ostream &o, const int64_t &v);
                virtual uint32_t writeValue(ostream &o, const uint64_t &v);
                virtual uint32_t writeValue(ostream &o, const float &v);
                virtual uint32_t writeValue(ostream &o, const double &v);
                virtual uint32_t writeValue(ostream &o, const string &v);
                virtual uint32_t writeValue(ostream &o, const void *data, const uint32_t &size);

            public:
                virtual void write(const uint32_t &id, const Serializable &s);
                virtual void write(const uint32_t &id, const bool &b);
                virtual void write(const uint32_t &id, const char &c);
                virtual void write(const uint32_t &id, const unsigned char &uc);
                virtual void write(const uint32_t &id, const int8_t &i);
                virtual void write(const uint32_t &id, const int16_t &i);
                virtual void write(const uint32_t &id, const uint16_t &ui);
                virtual void write(const uint32_t &id, const int32_t &i);
                virtual void write(const uint32_t &id, const uint32_t &ui);
                virtual void write(const uint32_t &id, const int64_t &i);
                virtual void write(const uint32_t &id, const uint64_t &ui);
                virtual void write(const uint32_t &id, const float &f);
                virtual void write(const uint32_t &id, const double &d);
                virtual void write(const uint32_t &id, const string &s);
                virtual void write(const uint32_t &id, const void *data, const uint32_t &size);

            public:
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const Serializable &s);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const bool &b);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const char &c);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const unsigned char &uc);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const int8_t &i);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const int16_t &i);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const uint16_t &ui);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const int32_t &i);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const uint32_t &ui);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const int64_t &i);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const uint64_t &ui);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const float &f);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const double &d);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const string &s);
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const void *data, const uint32_t &size);

            private:
                /**
                 * This method writes a given key/value pair using the provided identifier
                 * and value into the Protobuf format.
                 *
                 * @param id Identifier
                 * @param value to be written
                 */
                template<typename T>
                uint64_t writeKeyValue(const uint32_t &id, T &v) {
                    uint32_t bytesWritten = 0;
                    uint64_t key = getKey(id, ProtoSerializer::VARINT);
                    bytesWritten += encodeVarInt(m_buffer, key);
                    bytesWritten += writeValue(m_buffer, v);
                    return bytesWritten;
                }

                /**
                 * This method creates the key for the Protobuf format.
                 *
                 * @param fieldId Field identifier
                 * @param protoType Protobuf type identifier
                 * @return Protobuf compliant key.
                 */
                uint64_t getKey(const uint32_t &fieldNumber, const uint8_t &protoType);

            private:
                ostream *m_out; // We have a pointer here that we derive from a reference parameter in our non-standard constructor; thus, the other class is responsible for the lifecycle of the variable to which we point to.
                stringstream m_buffer;
        };

    }
} // odcore::base

#endif /*OPENDAVINCI_CORE_BASE_PROTOSERIALIZER_H_*/
