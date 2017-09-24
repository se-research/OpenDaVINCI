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

#ifndef OPENDAVINCI_CORE_SERIALIZATION_LCMDESERIALIZERVISITOR_H_
#define OPENDAVINCI_CORE_SERIALIZATION_LCMDESERIALIZERVISITOR_H_

#include <sstream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/base/Visitor.h"

namespace odcore {
    namespace serialization {

        using namespace std;

        /**
         * This class provides a deserialization visitor to decode data
         * encoded in LCM format (cf. https://github.com/lcm-proj/lcm).
         */
        class LCMDeserializerVisitor : public Deserializer, public odcore::base::Visitor {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                LCMDeserializerVisitor(const LCMDeserializerVisitor &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                LCMDeserializerVisitor& operator=(const LCMDeserializerVisitor &);

            public:
                LCMDeserializerVisitor();

                virtual ~LCMDeserializerVisitor();

                virtual void deserializeDataFrom(istream &in);

                /**
                 * This method returns the channel name under which the payload
                 * of in the stream was serialized.
                 *
                 * @return Channel name.
                 */
                const string getChannelName() const;

                /**
                 * This method returns the decoded hash value.
                 *
                 * @return Decoded hash.
                 */
                int64_t getDecodedHash() const;

                /**
                 * This method returns the calculated hash value.
                 *
                 * @return Calculated hash.
                 */
                int64_t getCalculatedHash() const;

            private:
                virtual uint32_t readValue(istream &i, Serializable &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, bool &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, char &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, unsigned char &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, int8_t &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, int16_t &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, uint16_t &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, int32_t &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, uint32_t &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, int64_t &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, uint64_t &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, float &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, double &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, string &v) { (void)i; (void)v; return 0; }
                virtual uint32_t readValue(istream &i, void *data, const uint32_t &size) { (void)i; (void)data; (void)size; return 0; }

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
                virtual void beginVisit(const int32_t &id, const string &shortName, const string &longName);
                virtual void endVisit();

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
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, Serializable &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, bool &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, char &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, unsigned char &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, int8_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, int16_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, uint16_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, int32_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, uint32_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, int64_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, uint64_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, float &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, double &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, string &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, void *data, const uint32_t &size);
                virtual void visitArray(const uint32_t &id, const string &longName, const string &shortName, void *data, const uint32_t &count, const odcore::TYPE_ &t);

            private:
                string m_channelName;
                int64_t m_decodedHash;
                int64_t m_calculatedHash;
                stringstream m_buffer;
        };

    }
} // odcore::serialization

#endif /*OPENDAVINCI_CORE_SERIALIZATION_LCMDESERIALIZERVISITOR_H_*/
