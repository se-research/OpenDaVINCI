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

#include "core/base/module/AbstractCIDModule.h"
#include "core/base/QueryableNetstringsDeserializer.h"
#include "core/base/QueryableNetstringsDeserializerAACF.h"
#include "core/base/QueryableNetstringsDeserializerABCF.h"
#include "core/base/Serializable.h"

namespace core {
    namespace base {

        using namespace std;

        QueryableNetstringsDeserializer::QueryableNetstringsDeserializer() :
            m_deserializer() {
            // Create a default deserializer that might be replaced by another one on user's request.
            m_deserializer = SharedPointer<Deserializer>(new QueryableNetstringsDeserializerAACF());
        }

        QueryableNetstringsDeserializer::QueryableNetstringsDeserializer(istream &in) :
            m_deserializer() {
            deserializeDataFrom(in);
        }

        void QueryableNetstringsDeserializer::deserializeDataFrom(istream &in) {
            // Save current position in the stream.
            int32_t currentPosition = in.tellg();

            // Checking for magic number to determine which deserializer needs to be used.
            uint16_t magicNumber = 0;
            in.read(reinterpret_cast<char*>(&magicNumber), sizeof(uint16_t));
            magicNumber = ntohs(magicNumber);

            if (magicNumber == 0xAACF) {
                // Data is encoded in 0xAACF format, representing version 1 of queryable netstrings.
                // Rewind the position and delegate decoding to QueryableNetstringsDeserializerAACF.
                in.seekg(currentPosition);

                // Instantiate AACF deserializer.
                m_deserializer = SharedPointer<Deserializer>(new QueryableNetstringsDeserializerAACF());
                m_deserializer->deserializeDataFrom(in);
            }
            else if (magicNumber == 0xABCF) {
                // Data is encoded in 0xABCF format, representing version 2 of queryable netstrings.
                // Rewind the position and delegate decoding to QueryableNetstringsDeserializerABCF.
                in.seekg(currentPosition);

                // Instantiate ABCF deserializer.
                m_deserializer = SharedPointer<Deserializer>(new QueryableNetstringsDeserializerABCF());
                m_deserializer->deserializeDataFrom(in);
            }
            else {
                if (in.good()) {
                    // Stream is good but still no magic number?
                    CLOG2 << "Stream corrupt: magic number not found." << endl;
                }
            }
        }

        QueryableNetstringsDeserializer::~QueryableNetstringsDeserializer() {}

        void QueryableNetstringsDeserializer::read(const uint32_t &id, Serializable &s) {
            m_deserializer->read(id, s);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, bool &b) {
            m_deserializer->read(id, b);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, char &c) {
            m_deserializer->read(id, c);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, unsigned char &uc) {
            m_deserializer->read(id, uc);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, int8_t &i) {
            m_deserializer->read(id, i);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, int16_t &i) {
            m_deserializer->read(id, i);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, uint16_t &ui) {
            m_deserializer->read(id, ui);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, int32_t &i) {
            m_deserializer->read(id, i);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, uint32_t &ui) {
            m_deserializer->read(id, ui);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, int64_t &i) {
            m_deserializer->read(id, i);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, uint64_t &ui) {
            m_deserializer->read(id, ui);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, float &f) {
            m_deserializer->read(id, f);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, double &d) {
            m_deserializer->read(id, d);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, string &s) {
            m_deserializer->read(id, s);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &id, void *data, const uint32_t &size) {
            m_deserializer->read(id, data, size);
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, Serializable &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, bool &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, char &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, unsigned char &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, int8_t &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, int16_t &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, uint16_t &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, int32_t &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, uint32_t &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, int64_t &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, uint64_t &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, float &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, double &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, string &v) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)v;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }

        void QueryableNetstringsDeserializer::read(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &longName, const string &shortName, void *data, const uint32_t &size) {
            (void)fourByteID;
            (void)oneByteID;
            (void)longName;
            (void)shortName;
            (void)data;
            (void)size;
            cerr << "[core::base::QueryableNetstringsDeserializer]: read(const uint32_t&, const uint8_t&, const string&, const string&, T) not implemented!" << endl;
        }
    }
} // core::base
