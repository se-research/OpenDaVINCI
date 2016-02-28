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

#include <iostream>

#include "opendavinci/odcore/base/LCMSerializerVisitor.h"
#include "opendavinci/odcore/base/Serializer.h"

namespace odcore {
    namespace base {

class Serializable;

        LCMSerializerVisitor::LCMSerializerVisitor() :
            m_channelName(),
            m_hash(0x12345678),
            m_buffer() {}

        LCMSerializerVisitor::~LCMSerializerVisitor() {}

        int64_t LCMSerializerVisitor::getHash() const {
            // Before the final hash is written by LCM, it is shifted around.
            int64_t ourHash = (m_hash << 1) + ( (m_hash >> 63) & 1 );
            return ourHash;
        }

        int64_t LCMSerializerVisitor::calculateHash(int64_t v, const char &c) {
            v = ((v<<8) ^ (v>>55)) + c;
            return v;
        }

        int64_t LCMSerializerVisitor::calculateHash(int64_t v, const string &s) {
            v = calculateHash(v, s.length());

            string::const_iterator it = s.begin();
            while (it != s.end()) {
                const char c = (*it++);
                v = calculateHash(v, c);
            }

            return v;
        }

        void LCMSerializerVisitor::setChannelName(const string &channelName) {
            m_channelName = channelName;
        }

        void LCMSerializerVisitor::getSerializedData(ostream &o) {
            /*
                An LCM message has the following structure:

                MagicNumber SequenceNumber ChannelName '\0' Hash Payload

                The MagicNumber is used to check if the message is actually
                an LCM message sized 4 bytes.

                The SequenceNumber is used to check if a message was split.
                Such fragmented messages are currently not supported by OpenDaVINCI;
                the field is 4 bytes long.

                The ChannelName is the channel which the message will appear in.
                It can be up to 256 bytes big.

                The '\0' character delimits the ChannelName sized 1 byte.

                The 8 bytes Hash is used to validate the decoding. The hash
                value is calculated based on the type name and in the case
                of primitive types on the name of the primitive type (no
                uint??_t are supported!).
            */
            
            // Magic number.
            const int32_t MAGIC_NUMBER_LCM2 = 0x4c433032;
            int32_t fourByteValue = htonl(MAGIC_NUMBER_LCM2);
            o.write(reinterpret_cast<const char*>(&fourByteValue), sizeof(const uint32_t));

            // Sequence number.
            const uint32_t SEQUENCE = 0; // Fragmented messages are not supported.
            fourByteValue = htonl(SEQUENCE);
            o.write(reinterpret_cast<const char*>(&fourByteValue), sizeof(const uint32_t));

            // Limit channel name to 256 bytes.
            if (m_channelName.size() > 255) {
                m_channelName = m_channelName.substr(0, 255);
            }
            o << m_channelName;

            // '\0'.
            const uint8_t ZERO = 0;
            o.write(reinterpret_cast<const char*>(&ZERO), sizeof(const uint8_t));

            // Hash number.
            int64_t eightByteValue = Serializer::__htonll(getHash());
            o.write(reinterpret_cast<const char*>(&eightByteValue), sizeof(const int64_t));

            // Payload.
            o << m_buffer.str();
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const Serializable &/*v*/) {}

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const bool &v) {
            m_buffer.write(reinterpret_cast<const char*>(&v), sizeof(const bool));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const char &v) {
            m_buffer.write(&v, sizeof(const char));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const unsigned char &v) {
            m_buffer.write(reinterpret_cast<const char*>(&v), sizeof(const unsigned char));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const int8_t &v) {
            m_buffer.write(reinterpret_cast<const char*>(&v), sizeof(const int8_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const int16_t &v) {
            int16_t _v = htons(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const int16_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const uint16_t &v) {
            uint16_t _v = htons(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const uint16_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const int32_t &v) {
            int32_t _v = htonl(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const int32_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const uint32_t &v) {
            uint32_t _v = htonl(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const uint32_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const int64_t &v) {
            int64_t _v = Serializer::__htonll(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const int64_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const uint64_t &v) {
            uint64_t _v = Serializer::__htonll(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const uint64_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const float &v) {
            float _v = htonf(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const float));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const double &v) {
            double _v = htond(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const double));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const string &v) {
            uint32_t length = v.length();
            uint32_t _length = htonl(length);
            m_buffer.write(reinterpret_cast<const char *>(&_length), sizeof(const uint32_t));
            m_buffer.write(v.c_str(), length);
        }

        void LCMSerializerVisitor::write(const uint32_t &/*id*/, const void */*data*/, const uint32_t &/*size*/) {}


        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const Serializable &/*v*/) {
            cerr << "[core::base::LCMSerializerVisitor]: write(const uint32_t&, const uint8_t&, const string&, const string&, T&) not implemented!" << endl;
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const bool &v) {
            m_buffer.write(reinterpret_cast<const char*>(&v), sizeof(const bool));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const char &v) {
            m_buffer.write(&v, sizeof(const char));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const unsigned char &v) {
            m_buffer.write(reinterpret_cast<const char*>(&v), sizeof(const unsigned char));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const int8_t &v) {
            m_buffer.write(reinterpret_cast<const char*>(&v), sizeof(const int8_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const int16_t &v) {
            int16_t _v = htons(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const int16_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const uint16_t &v) {
            uint16_t _v = htons(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const uint16_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const int32_t &v) {
            int32_t _v = htonl(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const int32_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const uint32_t &v) {
            uint32_t _v = htonl(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const uint32_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const int64_t &v) {
            int64_t _v = Serializer::__htonll(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const int64_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const uint64_t &v) {
            uint64_t _v = Serializer::__htonll(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const uint64_t));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const float &v) {
            float _v = htonf(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const float));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const double &v) {
            double _v = htond(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const double));
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const string &v) {
            uint32_t length = v.length();
            uint32_t _length = htonl(length);
            m_buffer.write(reinterpret_cast<const char *>(&_length), sizeof(const uint32_t));
            m_buffer.write(v.c_str(), length);
        }

        void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const void */*data*/, const uint32_t &/*size*/) {
            cerr << "[core::base::LCMSerializerVisitor]: write(const uint32_t&, const uint8_t&, const string&, const string&, T&) not implemented!" << endl;
        }


        void LCMSerializerVisitor::visit(const uint32_t &/*longId*/, const uint8_t &/*shortId*/, const string &/*longName*/, const string &/*shortName*/, Serializable &/*v*/) {
            cerr << "[core::base::LCMSerializerVisitor]: LCM for Serializable not implemented!" << endl;
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, bool &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "boolean");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, char &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "char");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, unsigned char &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "unsigned char");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int8_t &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "int8");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int16_t &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "int16");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint16_t &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "uint16");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int32_t &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "int32");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint32_t &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "uint32");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int64_t &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "int64");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint64_t &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "uint64");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, float &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "float");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, double &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "double");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, string &v) {
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, shortName);
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, "string");
            m_hash = LCMSerializerVisitor::calculateHash(m_hash, 0);

            write(longId, shortId, longName, shortName, v);
        }

        void LCMSerializerVisitor::visit(const uint32_t &/*longId*/, const uint8_t &/*shortId*/, const string &/*longName*/, const string &/*shortName*/, void */*data*/, const uint32_t &/*size*/) {
            cerr << "[core::base::LCMSerializerVisitor]: LCM for void* not implemented!" << endl;
        }

    }
} // odcore::base

