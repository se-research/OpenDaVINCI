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
 * License along with this library; if not, read to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OPENDAVINCI_CORE_SERIALIZATION_QUERYABLENETSTRINGSDESERIALIZERABCF_H_
#define OPENDAVINCI_CORE_SERIALIZATION_QUERYABLENETSTRINGSDESERIALIZERABCF_H_

#include <map>
#include <sstream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendavinci/odcore/serialization/Deserializer.h"

namespace odcore {
    namespace seriaization {

        using namespace std;


        /**
         * This class implements the interface Deserializer for queryable
         * Netstrings. The original version (found at:
         * http://cr.yp.to/proto/netstrings.txt ) has been modified:
         *
         * '0xAB' '0xCF' 'binary length encoded as varint' 'PAYLOAD' ','
         *
         * @See Serializable
         */
        class OPENDAVINCI_API QueryableNetstringsDeserializerABCF : public Deserializer {
            private:
                // Only the QueryableNetstringsDeserializer is allowed to create instances of this Deserializer using the non-standard constructor.
                friend class QueryableNetstringsDeserializer;

                /**
                 * Constructor.
                 *
                 * @param in Input stream containing the data.
                 */
                QueryableNetstringsDeserializerABCF(istream &in);

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                QueryableNetstringsDeserializerABCF(const QueryableNetstringsDeserializerABCF &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                QueryableNetstringsDeserializerABCF& operator=(const QueryableNetstringsDeserializerABCF &);


            public:
                /**
                 * Default constructor. When a QueryableNetstringsDeserializerABCF is created
                 * using this constructor, the method setSerializedData(istream &in) needs
                 * to be called before any read(...) method will return meaningful data.
                 */
                QueryableNetstringsDeserializerABCF();

                virtual ~QueryableNetstringsDeserializerABCF();

                virtual void deserializeDataFrom(istream &in);

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

            public:
                /**
                 * This method copies the minimum amount of bytes that are
                 * required to successfully decode using this decoder.
                 *
                 * @param in Input stream used for reading from.
                 * @param buffer Buffer to copy bytes to.
                 * @return size Number of bytes read.
                 */
                static uint32_t fillBuffer(istream& in, stringstream& buffer);

            private:
                /**
                 * This method decodes an unsigned value from a given varint encoding.
                 *
                 * @param in Input stream used for reading from.
                 * @param value Destination variable to be written into.
                 * @return size Number of bytes read.
                 */
                uint8_t decodeVarUInt(istream& in, uint64_t &value);

                /**
                 * This method decodes a signed value from a given varint encoding.
                 *
                 * @param in Input stream used for reading from.
                 * @param value Destination variable to be written into.
                 * @return size Number of bytes read.
                 */
                uint8_t decodeVarInt(istream& in, int64_t &value);

            private:
                stringstream m_buffer;
                map<uint32_t, streampos> m_values;
        };

    }
} // odcore::base

#endif /*OPENDAVINCI_CORE_SERIALIZATION_QUERYABLENETSTRINGSDESERIALIZERABCF_H_*/
