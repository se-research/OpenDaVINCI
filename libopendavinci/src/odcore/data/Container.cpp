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

#include <iosfwd>

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/SerializableData.h"

namespace odcore {
    namespace data {

        using namespace std;
        using namespace base;

        Container::Container() :
                m_dataType(UNDEFINEDDATA),
                m_serializedData(),
                m_sent(TimeStamp(0, 0)),
                m_received(TimeStamp(0, 0)) {}

        Container::Container(const SerializableData &serializableData) :
                m_dataType(serializableData.getID()),
                m_serializedData(),
                m_sent(TimeStamp(0, 0)),
                m_received(TimeStamp(0, 0)) {
            // Get data for container.
            m_serializedData << serializableData;
        }

        Container::Container(const SerializableData &serializableData, const int32_t &dataType) :
                m_dataType(dataType),
                m_serializedData(),
                m_sent(TimeStamp(0, 0)),
                m_received(TimeStamp(0, 0)) {
            // Get data for container.
            m_serializedData << serializableData;
        }

        Container::Container(const Container &obj) :
                Serializable(),
                m_dataType(obj.getDataType()),
                m_serializedData(),
                m_sent(obj.m_sent),
                m_received(obj.m_received) {
            m_serializedData.str(obj.m_serializedData.str());
        }

        Container& Container::operator=(const Container &obj) {
            m_dataType = obj.getDataType();
            m_serializedData.str(obj.m_serializedData.str());
            setSentTimeStamp(obj.getSentTimeStamp());
            setReceivedTimeStamp(obj.getReceivedTimeStamp());

            return (*this);
        }

        Container::~Container() {}

        int32_t Container::getDataType() const {
            return m_dataType;
        }

        const TimeStamp Container::getSentTimeStamp() const {
            return m_sent;
        }

        void Container::setSentTimeStamp(const TimeStamp &sentTimeStamp) {
            m_sent = sentTimeStamp;
        }

        const TimeStamp Container::getReceivedTimeStamp() const {
            return m_received;
        }

        void Container::setReceivedTimeStamp(const TimeStamp &receivedTimeStamp) {
            m_received = receivedTimeStamp;
        }

        ostream& Container::operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();;

            odcore::SharedPointer<Serializer> s = sf.getSerializer(out);

            // Write container data type.
            int32_t dataType = getDataType();
            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                     1, "Container.id", "id",
                     dataType);

            // Write container data.
            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                     2, "Container.data", "data",
                     m_serializedData.str());

            // Write sent time stamp data.
            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('s', 'e', 'n', 't') >::RESULT,
                     3, "Container.sent", "sent",
                     m_sent);

            // Write received time stamp data.
            s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'e', 'c', 'v', 'd') >::RESULT,
                     4, "Container.received", "received",
                     m_received);

            return out;
        }

        istream& Container::operator>>(istream &in) {
            string rawData = "";

            SerializationFactory& sf=SerializationFactory::getInstance();;
            odcore::SharedPointer<Deserializer> d = sf.getDeserializer(in);

            // Read container data type.
            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                    1, "Container.id", "id",
                    m_dataType);

            // Read container data.
            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                    2, "Container.data", "data",
                    rawData);
            m_serializedData.str(rawData);

            // Read sent time stamp data.
            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('s', 'e', 'n', 't') >::RESULT,
                    3, "Container.sent", "sent",
                    m_sent);

            // Read received time stamp data.
            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'e', 'c', 'v', 'd') >::RESULT,
                    4, "Container.received", "received",
                    m_received);

            return in;
        }

        const string Container::toString() const {
            switch (getDataType()) {
                case UNDEFINEDDATA:
                    return "undefined data";
                case DMCP_CONFIGURATION_REQUEST:
                    return "DMCPConfigurationRequest";
            }
            return "";
        }
    }
} // odcore::data
