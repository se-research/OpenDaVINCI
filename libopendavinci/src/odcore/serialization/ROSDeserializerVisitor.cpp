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

#include "opendavinci/odcore/serialization/ROSDeserializerVisitor.h"
#include "opendavinci/odcore/opendavinci.h"

namespace odcore {
    namespace base {

class Serializable;

        ROSDeserializerVisitor::ROSDeserializerVisitor() :
            m_messageId(0),
            m_size(0),
            m_buffer() {}

        ROSDeserializerVisitor::~ROSDeserializerVisitor() {}

        uint8_t ROSDeserializerVisitor::getMessageID() const {
            return m_messageId;
        }

        void ROSDeserializerVisitor::deserializeDataFrom(istream &in) {
            // Reset internal states as this deserializer could be reused.
            m_size = 0;
            m_buffer.str("");

            uint32_t connectionID;
            uint8_t opcode;
            uint16_t blockNumber;

            // Read header values.
            in.read(reinterpret_cast<char*>(&connectionID), sizeof(uint32_t));
            in.read(reinterpret_cast<char*>(&opcode), sizeof(uint8_t));
            in.read(reinterpret_cast<char*>(&m_messageId), sizeof(uint8_t));
            in.read(reinterpret_cast<char*>(&blockNumber), sizeof(uint16_t));

            connectionID = ntohl(connectionID);
            blockNumber = ntohs(blockNumber);

            // Put the remaining bytes into our internal buffer.
            char c = 0;
            while(in.good()){
                c = in.get();
                m_buffer.put(c);
            }
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, Serializable &/*v*/) {}

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, bool &v) {
            m_buffer.read(reinterpret_cast<char*>(&v), sizeof(bool));
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, char &v) {
            m_buffer.read(&v, sizeof(char));
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, unsigned char &v) {
            m_buffer.read(reinterpret_cast<char*>(&v), sizeof(unsigned char));
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, int8_t &v) {
            m_buffer.read(reinterpret_cast<char*>(&v), sizeof(int8_t));
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, int16_t &v) {
            int16_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(int16_t));
            v = ntohs(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, uint16_t &v) {
            uint16_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(uint16_t));
            v = ntohs(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, int32_t &v) {
            int32_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(int32_t));
            v = ntohl(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, uint32_t &v) {
            uint32_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(uint32_t));
            v = ntohl(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, int64_t &v) {
            int64_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(int64_t));
            v = __ntohll(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, uint64_t &v) {
            uint64_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(uint64_t));
            v = __ntohll(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, float &v) {
            float _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(float));
            v = ntohf(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, double &v) {
            double _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(double));
            v = ntohd(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, string &v) {
            int32_t _length;
            m_buffer.read(reinterpret_cast<char *>(&_length), sizeof(const int32_t));
            int32_t length = ntohl(_length);
            
            char *str = new char[length];
            m_buffer.read(str, length);
            v = string(str, length);
            OPENDAVINCI_CORE_DELETE_ARRAY(str);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, void */*data*/, const uint32_t &/*size*/) {}


        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, Serializable &/*v*/) {
            cerr << "[core::serialization::ROSDeserializerVisitor]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, bool &v) {
            m_buffer.read(reinterpret_cast<char*>(&v), sizeof(bool));
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, char &v) {
            m_buffer.read(&v, sizeof(char));
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, unsigned char &v) {
            m_buffer.read(reinterpret_cast<char*>(&v), sizeof(unsigned char));
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, int8_t &v) {
            m_buffer.read(reinterpret_cast<char*>(&v), sizeof(int8_t));
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, int16_t &v) {
            int16_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(int16_t));
            v = ntohs(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, uint16_t &v) {
            uint16_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(uint16_t));
            v = ntohs(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, int32_t &v) {
            int32_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(int32_t));
            v = ntohl(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, uint32_t &v) {
            uint32_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(uint32_t));
            v = ntohl(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, int64_t &v) {
            int64_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(int64_t));
            v = __ntohll(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, uint64_t &v) {
            uint64_t _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(uint64_t));
            v = __ntohll(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, float &v) {
            float _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(float));
            v = ntohf(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, double &v) {
            double _v = 0;
            m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(double));
            v = ntohd(_v);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, string &v) {
            int32_t _length;
            m_buffer.read(reinterpret_cast<char *>(&_length), sizeof(const int32_t));
            int32_t length = ntohl(_length);
            
            char *str = new char[length];
            m_buffer.read(str, length);
            v = string(str, length);
            OPENDAVINCI_CORE_DELETE_ARRAY(str);
        }

        void ROSDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, void *data, const uint32_t &size) {
            (void)data;
            (void)size;
            cerr << "[core::serialization::ROSDeserializerVisitor]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }


        void ROSDeserializerVisitor::beginVisit() {}

        void ROSDeserializerVisitor::endVisit() {}

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, Serializable &v) {
            (void)id;
            (void)v;
            cerr << "[core::serialization::ROSDeserializerVisitor]: ROS for Serializable not implemented!" << endl;
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, bool &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, char &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, unsigned char &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, int8_t &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, int16_t &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, uint16_t &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, int32_t &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, uint32_t &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, int64_t &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, uint64_t &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, float &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, double &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, string &v) {
            read(id, longName, shortName, v);
        }

        void ROSDeserializerVisitor::visit(const uint32_t &id, const string &/*longName*/, const string &/*shortName*/, void *data, const uint32_t &size) {
            (void)id;
            (void)data;
            (void)size;
            cerr << "[core::serialization::ROSSerializerVisitor]: ROS for void* not implemented!" << endl;
        }

    }
} // odcore::base

