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

#ifndef OPENDAVINCI_CORE_BASE_PROTODESERIALIZERVISITOR_H_
#define OPENDAVINCI_CORE_BASE_PROTODESERIALIZERVISITOR_H_

#include <sstream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/ProtoSerializerVisitor.h"
#include "opendavinci/odcore/base/Visitor.h"

namespace odcore {
    namespace base {

        using namespace std;

        /**
         * This class provides a deserialization visitor to decode data
         * encoded in Google's Protobuf format.
         */
        class ProtoDeserializerVisitor : public Deserializer, public Visitor {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ProtoDeserializerVisitor(const ProtoDeserializerVisitor &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ProtoDeserializerVisitor& operator=(const ProtoDeserializerVisitor &);

            public:
                ProtoDeserializerVisitor();

                virtual ~ProtoDeserializerVisitor();

                virtual void deserializeDataFrom(istream &in);

                /**
                 * This method deserializes a Proto stream where
                 * additional header information is preceding the
                 * serialized data.
                 *
                 * @param in Stream to serialize from.
                 */
                void deserializeDataFromWithHeader(istream &in);

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

            private:
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

            private:
                virtual void beginVisit();
                virtual void endVisit();

                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, Serializable &s);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, bool &b);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, char &c);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, unsigned char &uc);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, int8_t &i);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, int16_t &i);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, uint16_t &ui);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, int32_t &i);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, uint32_t &ui);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, int64_t &i);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, uint64_t &ui);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, float &f);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, double &d);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, string &s);
                virtual void read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, void *data, const uint32_t &size);

            public:
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, Serializable &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, bool &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, char &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, unsigned char &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int8_t &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int16_t &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint16_t &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int32_t &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint32_t &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int64_t &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint64_t &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, float &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, double &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, string &v);
                virtual void visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, void *data, const uint32_t &size);

            private:
                /**
                 * This method reads and validates the key for the next value.
                 *
                 * @param id Identifier to be matched with the key read from the stream.
                 * @return Bytes consumed.
                 */
                uint32_t readAndValidateKey(const uint32_t &id, const ProtoSerializerVisitor::PROTOBUF_TYPE &expectedType);

            private:
                uint32_t m_size;
                stringstream m_buffer;
        };

    }
} // odcore::base

#endif /*OPENDAVINCI_CORE_BASE_PROTODESERIALIZERVISITOR_H_*/
