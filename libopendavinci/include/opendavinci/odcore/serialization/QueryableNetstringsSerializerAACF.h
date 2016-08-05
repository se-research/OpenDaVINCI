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

#ifndef OPENDAVINCI_CORE_BASE_QUERYABLENETSTRINGSSERIALIZERAACF_H_
#define OPENDAVINCI_CORE_BASE_QUERYABLENETSTRINGSSERIALIZERAACF_H_

#include <sstream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Serializer.h"

namespace odcore {
    namespace base {

class Serializable;

        using namespace std;


        /**
         * This class implements the interface Serializer for queryable
         * Netstrings. The original version (found at:
         * http://cr.yp.to/proto/netstrings.txt ) has been modified:
         *
         * '0xAA' '0xCF' 'binary length (as uint32_t)' 'PAYLOAD' ','
         *
         * @See Serializable
         */
        class QueryableNetstringsSerializerAACF : public Serializer {
            private:
                // Only the QueryableNetstringsSerializer is allowed to create instances of this Serializer using the non-standard constructor.
                friend class QueryableNetstringsSerializer;

                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                QueryableNetstringsSerializerAACF(const QueryableNetstringsSerializerAACF &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                QueryableNetstringsSerializerAACF& operator=(const QueryableNetstringsSerializerAACF &);

            public:
                QueryableNetstringsSerializerAACF();

                virtual ~QueryableNetstringsSerializerAACF();

                virtual void getSerializedData(ostream &o);

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
                stringstream m_buffer;
        };

    }
} // odcore::base

#endif /*OPENDAVINCI_CORE_BASE_QUERYABLENETSTRINGSSERIALIZERAACF_H_*/
