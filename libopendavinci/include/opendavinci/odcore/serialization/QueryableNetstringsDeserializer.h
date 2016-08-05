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

#ifndef OPENDAVINCI_CORE_SERIALIZATION_QUERYABLENETSTRINGSDESERIALIZER_H_
#define OPENDAVINCI_CORE_SERIALIZATION_QUERYABLENETSTRINGSDESERIALIZER_H_

#include <sstream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/QueryableNetstringsDeserializerAACF.h"
#include "opendavinci/odcore/serialization/QueryableNetstringsDeserializerABCF.h"

namespace odcore {
    namespace base {

        using namespace std;


        /**
         * This class implements the interface Serializer for queryable
         * Netstrings. The original version (found at:
         * http://cr.yp.to/proto/netstrings.txt ) has been modified
         * in different implementations:
         *
         * Version 1 of queryable netstrings:
         * QueryableNetstringsDeserializerAACF: '0xAA' '0xCF' 'binary length (as uint32_t)' 'PAYLOAD' ','
         *
         * @See Serializable
         */
        class OPENDAVINCI_API QueryableNetstringsDeserializer : public Deserializer {
            public:
                // Only the SerializationFactory or its subclasses are allowed to create instances of this Deserializer using the non-standard constructor.
                friend class SerializationFactory;

                /**
                 * Constructor.
                 *
                 * @param in Input stream containing the data.
                 */
                QueryableNetstringsDeserializer(istream &in);

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                QueryableNetstringsDeserializer(const QueryableNetstringsDeserializer &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                QueryableNetstringsDeserializer& operator=(const QueryableNetstringsDeserializer &);

            public:
                /**
                 * Default constructor. When a QueryableNetstringsDeserializer is created
                 * using this constructor, the method setSerializedData(istream &in) needs
                 * to be called before any read(...) method will return meaningful data.
                 */
                QueryableNetstringsDeserializer();

                virtual ~QueryableNetstringsDeserializer();

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

            private:
                QueryableNetstringsDeserializerAACF m_aacf;
                QueryableNetstringsDeserializerABCF m_abcf;
                Deserializer* m_deserializer;
        };

    }
} // odcore::base

#endif /*OPENDAVINCI_CORE_SERIALIZATION_QUERYABLENETSTRINGSDESERIALIZER_H_*/
