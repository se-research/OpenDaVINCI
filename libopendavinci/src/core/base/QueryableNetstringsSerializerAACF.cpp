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

#include "core/base/QueryableNetstringsSerializerAACF.h"
#include "core/base/Serializable.h"

namespace core {
    namespace base {

        using namespace std;

        QueryableNetstringsSerializerAACF::QueryableNetstringsSerializerAACF() :
            m_buffer() {}

        QueryableNetstringsSerializerAACF::~QueryableNetstringsSerializerAACF() {}

        void QueryableNetstringsSerializerAACF::getSerializedData(ostream &o) {
            // Write magic number.
            uint16_t magicNumber = 0xAACF;
            magicNumber = htons(magicNumber);
            o.write(reinterpret_cast<const char *>(&magicNumber), sizeof(uint16_t));

            // Write length.
            uint32_t length = static_cast<uint32_t>(m_buffer.str().length());
            length = htonl(length);
            o.write(reinterpret_cast<const char *>(&length), sizeof(uint32_t));

            // Write payload.
            o << m_buffer.str();

            // Write End-Of-Data for checking corruptness.
            o << ",";
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const Serializable &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const bool &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const char &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const unsigned char &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const int8_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const int16_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const uint16_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const int32_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const uint32_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const int64_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const uint64_t &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const float &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const double &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const string &v) {
            write(id, 0, "", "", v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &id, const void *data, const uint32_t &size) {
            write(id, 0, "", "", data, size);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const Serializable &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            stringstream buffer;
            buffer << v;

            uint32_t size = static_cast<uint32_t>(buffer.str().length());
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            m_buffer << buffer.str();
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const bool &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));
            m_buffer.write(reinterpret_cast<const char *>(&v), sizeof(const bool));
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const char &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));
            m_buffer.write(&v, sizeof(const char));
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const unsigned char &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));
            m_buffer.write(reinterpret_cast<const char *>(&v), sizeof(const unsigned char));
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int8_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            int8_t _i = v;
            m_buffer.write(reinterpret_cast<const char *>(&_i), sizeof(const int8_t));
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int16_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            int16_t _i = v;
            _i = htons(_i);
            m_buffer.write(reinterpret_cast<const char *>(&_i), sizeof(const int16_t));
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint16_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            uint16_t _ui = v;
            _ui = htons(_ui);
            m_buffer.write(reinterpret_cast<const char *>(&_ui), sizeof(const uint16_t));
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int32_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            int32_t _i = v;
            _i = htonl(_i);
            m_buffer.write(reinterpret_cast<const char *>(&_i), sizeof(const int32_t));
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint32_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            uint32_t _ui = v;
            _ui = htonl(_ui);
            m_buffer.write(reinterpret_cast<const char *>(&_ui), sizeof(const uint32_t));
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int64_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            int64_t _i = v;
            _i = __htonll(_i);
            m_buffer.write(reinterpret_cast<const char *>(&_i), sizeof(const int64_t));
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint64_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            uint64_t _ui = v;
            _ui = __htonll(_ui);
            m_buffer.write(reinterpret_cast<const char *>(&_ui), sizeof(const uint64_t));
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const float &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            float _f = v;
            _f = Serializer::htonf(_f);
            m_buffer.write(reinterpret_cast<const char *>(&_f), sizeof(const float));
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const double &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            double _d = v;
            _d = Serializer::htond(_d);
            m_buffer.write(reinterpret_cast<const char *>(&_d), sizeof(const double));
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const string &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t stringLength = v.length();
            uint32_t size = static_cast<uint32_t>(stringLength + sizeof(uint32_t)); // String's length plus the length of the type for (string's length).
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char *>(&size), sizeof(uint32_t));

            uint32_t _stringLength = stringLength;
            _stringLength = htonl(_stringLength);
            m_buffer.write(reinterpret_cast<const char *>(&_stringLength), sizeof(uint32_t));
            m_buffer.write(v.c_str(), stringLength);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const void *data, const uint32_t &size) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t realSize = size;
            realSize = htonl(realSize);
            m_buffer.write(reinterpret_cast<const char*>(&realSize), sizeof(uint32_t));
            m_buffer.write(reinterpret_cast<const char*>(data), size);
        }
    }
} // core::base
