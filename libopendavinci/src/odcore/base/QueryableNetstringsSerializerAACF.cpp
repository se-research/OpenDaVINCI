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

#include "opendavinci/odcore/base/QueryableNetstringsSerializerAACF.h"
#include "opendavinci/odcore/base/Serializable.h"

namespace odcore {
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

        ///////////////////////////////////////////////////////////////////////

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const Serializable &v) {
            // Serialize the Serializable.
            stringstream buffer;
            buffer << v;
            const string buffer_str = buffer.str();

            return writeValue(o, buffer_str);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const bool &v) {
            o.write(reinterpret_cast<const char *>(&v), sizeof(const bool));
            return sizeof(const bool);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const char &v) {
            o.write(&v, sizeof(const char));
            return sizeof(const char);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const unsigned char &v) {
            o.write(reinterpret_cast<const char *>(&v), sizeof(const unsigned char));
            return sizeof(const unsigned char);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const int8_t &v) {
            int8_t _i = v;
            o.write(reinterpret_cast<const char *>(&_i), sizeof(const int8_t));
            return sizeof(const int8_t);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const int16_t &v) {
            int16_t _i = v;
            _i = htons(_i);
            o.write(reinterpret_cast<const char *>(&_i), sizeof(const int16_t));
            return sizeof(const int16_t);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const uint16_t &v) {
            uint16_t _ui = v;
            _ui = htons(_ui);
            o.write(reinterpret_cast<const char *>(&_ui), sizeof(const uint16_t));
            return sizeof(const uint16_t);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const int32_t &v) {
            int32_t _i = v;
            _i = htonl(_i);
            o.write(reinterpret_cast<const char *>(&_i), sizeof(const int32_t));
            return sizeof(const int32_t);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const uint32_t &v) {
            uint32_t _ui = v;
            _ui = htonl(_ui);
            o.write(reinterpret_cast<const char *>(&_ui), sizeof(const uint32_t));
            return sizeof(const uint32_t);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const int64_t &v) {
            int64_t _i = v;
            _i = __htonll(_i);
            o.write(reinterpret_cast<const char *>(&_i), sizeof(const int64_t));
            return sizeof(const int64_t);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const uint64_t &v) {
            uint64_t _ui = v;
            _ui = __htonll(_ui);
            o.write(reinterpret_cast<const char *>(&_ui), sizeof(const uint64_t));
            return sizeof(const uint64_t);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const float &v) {
            float _f = v;
            _f = Serializer::htonf(_f);
            o.write(reinterpret_cast<const char *>(&_f), sizeof(const float));
            return sizeof(const float);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const double &v) {
            double _d = v;
            _d = Serializer::htond(_d);
            o.write(reinterpret_cast<const char *>(&_d), sizeof(const double));
            return sizeof(const double);
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const string &v) {
            uint32_t bytesWritten = 0;

            uint32_t _stringLength = v.length();
            _stringLength = htonl(_stringLength);
            o.write(reinterpret_cast<const char *>(&_stringLength), sizeof(uint32_t));
            bytesWritten += sizeof(uint32_t);

            o.write(v.c_str(), v.length());
            bytesWritten += v.length();

            return bytesWritten;
        }

        uint32_t QueryableNetstringsSerializerAACF::writeValue(ostream &o, const void *data, const uint32_t &size) {
            uint32_t bytesWritten = 0;

            o.write(reinterpret_cast<const char*>(data), size);
            bytesWritten += size;

            return bytesWritten;
        }

        ///////////////////////////////////////////////////////////////////////

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

        ///////////////////////////////////////////////////////////////////////

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const Serializable &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            // Serialize the Serializable.
            stringstream buffer;
            buffer << v;

            const string buffer_str = buffer.str();
            uint32_t serializableLength = buffer_str.length();
            uint32_t size = static_cast<uint32_t>(serializableLength + sizeof(uint32_t)); // Serializable's length plus the length of the type for (serializableLength).
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char *>(&size), sizeof(uint32_t));

            // Reuse string serialization function (cf. string dump).
            writeValue(m_buffer, buffer_str);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const bool &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const char &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const unsigned char &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int8_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int16_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint16_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int32_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint32_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const int64_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const uint64_t &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const float &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const double &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(v));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const string &v) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t stringLength = v.length();
            uint32_t size = static_cast<uint32_t>(stringLength + sizeof(uint32_t)); // String's length plus the length of the type for (string's length).
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char *>(&size), sizeof(uint32_t));

            writeValue(m_buffer, v);
        }

        void QueryableNetstringsSerializerAACF::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const void *data, const uint32_t &size) {
            uint32_t _id = (oneByteID > 0 ? oneByteID : fourByteID);
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t realSize = size;
            realSize = htonl(realSize);
            m_buffer.write(reinterpret_cast<const char*>(&realSize), sizeof(uint32_t));

            writeValue(m_buffer, data, size);
        }
    }
} // odcore::base
