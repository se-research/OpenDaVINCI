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

#ifndef OPENDAVINCI_CORE_BASE_QUERYABLENETSTRINGSSERIALIZERABCF_H_
#define OPENDAVINCI_CORE_BASE_QUERYABLENETSTRINGSSERIALIZERABCF_H_

#include <sstream>
#include <string>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/base/Serializer.h"

namespace core {
    namespace base {

class Serializable;

        using namespace std;


        /**
         * This class implements the interface Serializer for queryable
         * Netstrings. The original version (found at:
         * http://cr.yp.to/proto/netstrings.txt ) has been modified:
         *
         * '0xAB' '0xCF' 'binary length encoded as varint' 'PAYLOAD' ','
         *
         * @See Serializable
         */
        class QueryableNetstringsSerializerABCF : public Serializer {
            private:
                // Only the QueryableNetstringsSerializer is allowed to create instances of this Serializer using the non-standard constructor.
                friend class QueryableNetstringsSerializer;

                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                QueryableNetstringsSerializerABCF(const QueryableNetstringsSerializerABCF &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                QueryableNetstringsSerializerABCF& operator=(const QueryableNetstringsSerializerABCF &);

            public:
                QueryableNetstringsSerializerABCF();

                virtual ~QueryableNetstringsSerializerABCF();

                virtual void getSerializedData(ostream &o);

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
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const Serializable &s);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const bool &b);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const char &c);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const unsigned char &uc);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const int8_t &i);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const int16_t &i);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const uint16_t &ui);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const int32_t &i);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const uint32_t &ui);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const int64_t &i);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const uint64_t &ui);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const float &f);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const double &d);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const string &s);
                virtual void write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, const void *data, const uint32_t &size);

            private:
                /**
                 * This method encodes a given unsigned value using the varint encoding.
                 *
                 * @param out Output stream to be written to.
                 * @param value Value to be encoded.
                 * @return size Number of bytes written.
                 */
                uint8_t encodeVarUInt(ostream &out, uint64_t value);

                /**
                 * This method encodes a given signed value using the varint encoding.
                 *
                 * @param out Output stream to be written to.
                 * @param value Value to be encoded.
                 * @return size Number of bytes written.
                 */
                uint8_t encodeVarInt(ostream &out, int64_t value);

            private:
                stringstream m_buffer;
        };

    }
} // core::base

#endif /*OPENDAVINCI_CORE_BASE_QUERYABLENETSTRINGSSERIALIZERABCF_H_*/
