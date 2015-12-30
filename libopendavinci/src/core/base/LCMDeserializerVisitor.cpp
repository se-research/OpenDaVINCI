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
 * License along with this library; if not, read to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <iostream>

#include "core/base/LCMDeserializerVisitor.h"
#include "core/base/LCMSerializerVisitor.h"
#include "core/macros.h"

namespace core {
    namespace base {

class Serializable;

        LCMDeserializerVisitor::LCMDeserializerVisitor() :
            m_channelName(),
            m_decodedHash(0),
            m_calculatedHash(0x12345678),
            m_buffer() {}

        LCMDeserializerVisitor::~LCMDeserializerVisitor() {}

        int64_t LCMDeserializerVisitor::getDecodedHash() const {
            return m_decodedHash;
        }

        int64_t LCMDeserializerVisitor::getCalculatedHash() const {
            // Before the final hash is written by LCM, it is shifted around.
            int64_t ourHash = (m_calculatedHash << 1) + ( (m_calculatedHash >> 63) & 1 );

            return ourHash;
        }

        const string LCMDeserializerVisitor::getChannelName() const {
            return m_channelName;
        }

        void LCMDeserializerVisitor::deserializeDataFrom(istream &in) {
            // Reset internal states as this deserializer could be reused.
            m_decodedHash = 0;
            m_calculatedHash = 0x12345678;
            m_buffer.str("");

            const int32_t MAGIC_NUMBER_LCM2 = 0x4c433032;

            // Decode the magic number.
            int32_t magicNumber = 0;
            in.read(reinterpret_cast<char*>(&magicNumber), sizeof(int32_t));
            magicNumber = ntohl(magicNumber);

            if (magicNumber == MAGIC_NUMBER_LCM2) {
                // Decode the sequence number for fragmented messages.
                int32_t sequence = 0;
                in.read(reinterpret_cast<char*>(&sequence), sizeof(int32_t));
                sequence = ntohl(sequence);

                // Decode channel name.
                char channel[256];
                int channelIdx = 0;
                char c = 0;
                do {
                    in.get(c);
                    channel[channelIdx++] = c;
                } while (c != 0);
                m_channelName = string(channel);

                // Decode the hash.
                in.read(reinterpret_cast<char*>(&m_decodedHash), sizeof(int64_t));
                m_decodedHash = __ntohll(m_decodedHash);

                // Transfer the remaining data into our internal buffer.
                while (in.good()) {
                    c = in.get();
                    m_buffer.put(c);
                }
            }
            else {
                // Stream is good but still no matching magic number?
                clog << "[core::base::LCMDeserializerVisitor]: Stream corrupt: magic number not found." << endl;
            }
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, Serializable &/*v*/) {}

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, bool &v) {
            m_buffer.read(reinterpret_cast<char*>(&v), sizeof(bool));
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, char &v) {
            m_buffer.read(&v, sizeof(char));
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, unsigned char &v) {
            m_buffer.read(reinterpret_cast<char*>(&v), sizeof(unsigned char));
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, int8_t &v) {
            m_buffer.read(reinterpret_cast<char*>(&v), sizeof(int8_t));
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, int16_t &v) {
            int16_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(int16_t));
            v = ntohs(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, uint16_t &v) {
            uint16_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(uint16_t));
            v = ntohs(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, int32_t &v) {
            int32_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(int32_t));
            v = ntohl(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, uint32_t &v) {
            uint32_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(uint32_t));
            v = ntohl(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, int64_t &v) {
            int64_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(int64_t));
            v = __ntohll(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, uint64_t &v) {
            uint64_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(uint64_t));
            v = __ntohll(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, float &v) {
            float _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(float));
            v = ntohf(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, double &v) {
            double _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(double));
            v = ntohd(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, string &v) {
            int32_t _length;
            m_buffer.read(reinterpret_cast<char *>(&_length), sizeof(const int32_t));
            int32_t length = ntohl(_length);
            
            char *str = new char[length];
            m_buffer.read(str, length);
            v = string(str, length);
            OPENDAVINCI_CORE_DELETE_ARRAY(str);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*id*/, void */*data*/, const uint32_t &/*size*/) {}


        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, Serializable &/*v*/) {
            cerr << "[core::base::LCMDeserializerVisitor]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, bool &v) {
            m_buffer.read(reinterpret_cast<char*>(&v), sizeof(bool));
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, char &v) {
            m_buffer.read(&v, sizeof(char));
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, unsigned char &v) {
            m_buffer.read(reinterpret_cast<char*>(&v), sizeof(unsigned char));
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, int8_t &v) {
            m_buffer.read(reinterpret_cast<char*>(&v), sizeof(int8_t));
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, int16_t &v) {
            int16_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(int16_t));
            v = ntohs(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, uint16_t &v) {
            uint16_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(uint16_t));
            v = ntohs(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, int32_t &v) {
            int32_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(int32_t));
            v = ntohl(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, uint32_t &v) {
            uint32_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(uint32_t));
            v = ntohl(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, int64_t &v) {
            int64_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(int64_t));
            v = __ntohll(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, uint64_t &v) {
            uint64_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(uint64_t));
            v = __ntohll(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, float &v) {
            float _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(float));
            v = ntohf(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, double &v) {
            double _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(double));
            v = ntohd(_v);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, string &v) {
            int32_t _length;
            m_buffer.read(reinterpret_cast<char *>(&_length), sizeof(const int32_t));
            int32_t length = ntohl(_length);
            
            char *str = new char[length];
            m_buffer.read(str, length);
            v = string(str, length);
            OPENDAVINCI_CORE_DELETE_ARRAY(str);
        }

        void LCMDeserializerVisitor::read(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, void */*data*/, const uint32_t &/*size*/) {
            cerr << "[core::base::LCMDeserializerVisitor]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }


        void LCMDeserializerVisitor::visit(const uint32_t &/*longId*/, const uint8_t &/*shortId*/, const string &/*longName*/, const string &/*shortName*/, Serializable &/*v*/) {
            cerr << "[core::base::LCMDeserializerVisitor]: LCM for Serializable not implemented!" << endl;
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, bool &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "boolean");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, char &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "char");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, unsigned char &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "unsigned char");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int8_t &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "int8");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int16_t &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "int16");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint16_t &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "uint16");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int32_t &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "int32");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint32_t &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "uint32");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, int64_t &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "int64");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, uint64_t &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "uint64");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, float &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "float");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, double &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "double");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &longId, const uint8_t &shortId, const string &longName, const string &shortName, string &v) {
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, shortName);
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, "string");
            m_calculatedHash = LCMSerializerVisitor::calculateHash(m_calculatedHash, 0);

            read(longId, shortId, longName, shortName, v);
        }

        void LCMDeserializerVisitor::visit(const uint32_t &/*longId*/, const uint8_t &/*shortId*/, const string &/*longName*/, const string &/*shortName*/, void */*data*/, const uint32_t &/*size*/) {
            cerr << "[core::base::LCMDeserializerVisitor]: LCM for void* not implemented!" << endl;
        }

    }
} // core::base

