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

#include "opendavinci/odcore/serialization/ROSSerializerVisitor.h"

namespace odcore {
    namespace serialization {

class Serializable;

        ROSSerializerVisitor::ROSSerializerVisitor() :
            m_messageId(0),
            m_size(0),
            m_buffer() {}

        ROSSerializerVisitor::~ROSSerializerVisitor() {}

        void ROSSerializerVisitor::setMessageID(const uint8_t &messageId) {
            m_messageId = messageId;
        }

        void ROSSerializerVisitor::getSerializedData(ostream &o) {
            uint32_t connectionID = 0; // container.getDataType();
            uint8_t opcode = 0;
            uint16_t blockNumber = 1;

            connectionID = htonl(connectionID);
            blockNumber = htons(blockNumber);

            o.write(reinterpret_cast<const char*>(&connectionID), sizeof(const uint32_t));
            o.write(reinterpret_cast<const char*>(&opcode), sizeof(const uint8_t));
            o.write(reinterpret_cast<const char*>(&m_messageId), sizeof(const uint8_t));
            o.write(reinterpret_cast<const char*>(&blockNumber), sizeof(const uint16_t));

            o << m_buffer.str();
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const Serializable &/*v*/) {}

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const bool &v) {
            m_size += sizeof(const bool);
            m_buffer.write(reinterpret_cast<const char*>(&v), sizeof(const bool));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const char &v) {
            m_size += sizeof(const char);
            m_buffer.write(&v, sizeof(const char));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const unsigned char &v) {
            m_size += sizeof(const unsigned char);
            m_buffer.write(reinterpret_cast<const char*>(&v), sizeof(const unsigned char));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const int8_t &v) {
            m_size += sizeof(const int8_t);
            m_buffer.write(reinterpret_cast<const char*>(&v), sizeof(const int8_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const int16_t &v) {
            m_size += sizeof(const int16_t);
            int16_t _v = htons(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const int16_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const uint16_t &v) {
            m_size += sizeof(const uint16_t);
            uint16_t _v = htons(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const uint16_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const int32_t &v) {
            m_size += sizeof(const int32_t);
            int32_t _v = htonl(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const int32_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const uint32_t &v) {
            m_size += sizeof(const uint32_t);
            uint32_t _v = htonl(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const uint32_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const int64_t &v) {
            m_size += sizeof(const int64_t);
            int64_t _v = Serializer::__htonll(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const int64_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const uint64_t &v) {
            m_size += sizeof(const uint64_t);
            uint64_t _v = Serializer::__htonll(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const uint64_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const float &v) {
            m_size += sizeof(const float);
            float _v = htonf(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const float));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const double &v) {
            m_size += sizeof(const double);
            double _v = htond(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const double));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &v) {
            // The length field for string will consume 4 bytes.
            m_size += sizeof(uint32_t);

            uint32_t length = v.length();
            m_size += length;

            uint32_t _length = htonl(length);
            m_buffer.write(reinterpret_cast<const char *>(&_length), sizeof(const uint32_t));
            m_buffer.write(v.c_str(), length);
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const void */*data*/, const uint32_t &/*size*/) {}

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const Serializable &/*v*/) {
            cerr << "[core::serialization::ROSSerializerVisitor]: write(const uint32_t&, const uint8_t&, const string&, const string&, T&) not implemented!" << endl;
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const bool &v) {
            m_size += sizeof(const bool);
            m_buffer.write(reinterpret_cast<const char*>(&v), sizeof(const bool));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const char &v) {
            m_size += sizeof(const char);
            m_buffer.write(&v, sizeof(const char));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const unsigned char &v) {
            m_size += sizeof(const unsigned char);
            m_buffer.write(reinterpret_cast<const char*>(&v), sizeof(const unsigned char));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const int8_t &v) {
            m_size += sizeof(const int8_t);
            m_buffer.write(reinterpret_cast<const char*>(&v), sizeof(const int8_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const int16_t &v) {
            m_size += sizeof(const int16_t);
            int16_t _v = htons(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const int16_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const uint16_t &v) {
            m_size += sizeof(const uint16_t);
            uint16_t _v = htons(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const uint16_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const int32_t &v) {
            m_size += sizeof(const int32_t);
            int32_t _v = htonl(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const int32_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const uint32_t &v) {
            m_size += sizeof(const uint32_t);
            uint32_t _v = htonl(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const uint32_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const int64_t &v) {
            m_size += sizeof(const int64_t);
            int64_t _v = Serializer::__htonll(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const int64_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const uint64_t &v) {
            m_size += sizeof(const uint64_t);
            uint64_t _v = Serializer::__htonll(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const uint64_t));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const float &v) {
            m_size += sizeof(const float);
            float _v = htonf(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const float));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const double &v) {
            m_size += sizeof(const double);
            double _v = htond(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const double));
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const string &v) {
            // The length field for string will consume 4 bytes.
            m_size += sizeof(uint32_t);

            uint32_t length = v.length();
            m_size += length;

            uint32_t _length = htonl(length);
            m_buffer.write(reinterpret_cast<const char *>(&_length), sizeof(const uint32_t));
            m_buffer.write(v.c_str(), length);
        }

        void ROSSerializerVisitor::write(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, const void *data, const uint32_t &size) {
            (void)data;
            (void)size;
            cerr << "[core::serialization::ROSSerializerVisitor]: write(const uint32_t&, const uint8_t&, const string&, const string&, T&) not implemented!" << endl;
        }


        void ROSSerializerVisitor::beginVisit(const int32_t &/*id*/, const string &/*shortName*/, const string &/*longName*/) {}

        void ROSSerializerVisitor::endVisit() {}

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, Serializable &v) {
            (void)id;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::serialization::ROSSerializerVisitor]: ROS for Serializable not implemented!" << endl;
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, bool &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, char &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, unsigned char &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, int8_t &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, int16_t &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, uint16_t &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, int32_t &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, uint32_t &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, int64_t &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, uint64_t &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, float &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, double &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, string &v) {
            write(id, longName, shortName, v);
        }

        void ROSSerializerVisitor::visit(const uint32_t &id, const string &longName, const string &shortName, void *data, const uint32_t &size) {
            (void)id;
            (void)longName;
            (void)shortName;
            (void)data;
            (void)size;
            cerr << "[core::serialization::ROSSerializerVisitor]: ROS for void* not implemented!" << endl;
        }

        void ROSSerializerVisitor::visitArray(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, void */*data*/, const uint32_t &/*count*/, const odcore::TYPE_ &/*t*/) {
            std::cerr << "core::serialization::ROSSerializerVisitor::visitArray not implemented." << std::endl;
        }

    }
} // odcore::serialization

