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

#include "core/SharedPointer.h"
#include "core/base/Deserializer.h"
#include "core/base/Hash.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/data/Container.h"
#include "core/data/SerializableData.h"

namespace core {
    namespace data {

        using namespace std;
        using namespace base;

        Container::Container() :
                m_dataType(UNDEFINEDDATA),
                m_serializedData(),
                m_sent(TimeStamp(0, 0)),
                m_received(TimeStamp(0, 0)) {}

        Container::Container(const DATATYPE &dataType, const SerializableData &serializableData) :
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

        Container::DATATYPE Container::getDataType() const {
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

            core::SharedPointer<Serializer> s = sf.getSerializer(out);

            // Write container data type.
            uint32_t dataType = getDataType();
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
            core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

            // Read container data type.
            uint32_t dataType = 0;
            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                    1, "Container.id", "id",
                    dataType);

            // Read container data.
            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                    2, "Container.data", "data",
                    rawData);

            // Read sent time stamp data.
            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('s', 'e', 'n', 't') >::RESULT,
                    3, "Container.sent", "sent",
                    m_sent);

            // Read received time stamp data.
            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'e', 'c', 'v', 'd') >::RESULT,
                    4, "Container.received", "received",
                    m_received);

            // Set data.
            m_dataType = static_cast<DATATYPE>(dataType);
            m_serializedData.str(rawData);

            return in;
        }

        const string Container::toString() const {
            switch (getDataType()) {
                case UNDEFINEDDATA:
                    return "undefined data";
                case CONFIGURATION:
                    return "Configuration";
                case DMCP_DISCOVER:
                    return "DMCPDiscoverMessage";
                case DMCP_CONNECTION_REQUEST:
                    return "DMCPConnectionRequest";
                case DMCP_CONFIGURATION_REQUEST:
                    return "DMCPConfigurationRequest";
                case DMCP_MODULESTATEMESSAGE:
                    return "DMCP_MODULESTATEMESSAGE";
                case DMCP_MODULEEXITCODEMESSAGE:
                    return "DMCP_MODULEEXITCODEMESSAGE";
                case MODULESTATISTICS:
                    return "ModuleStatistics";
                case RUNTIMESTATISTIC:
                    return "RuntimeStatistic";
                case PLAYER_COMMAND:
                    return "PlayerCommand";
                case RECORDER_COMMAND:
                    return "RecorderCommand";
                case TIMESTAMP:
                    return "TimeStamp";
                case SHARED_DATA:
                    return "SharedData";
                case SHARED_IMAGE:
                    return "SharedImage";
                case POSITION:
                    return "Position";
                case COMPRESSED_IMAGE:
                    return "CompressedImage";
                case CONTOUREDOBJECT:
                    return "ContouredObject";
                case CONTOUREDOBJECTS:
                    return "ContouredObject";
                case EGOSTATE:
                    return "EgoState";
                case FORCECONTROL:
                    return "ForceControl";
                case LMS291MESSAGE:
                    return "LMS291Message";
                case OBSTACLE:
                    return "Obstacle";
                case OTHERVEHICLESTATE:
                    return "OtherVehicleState";
                case POINTSHAPEDOBJECT:
                    return "PointShapedObject";
                case ROUTE:
                    return "Route";
                case VEHICLEDATA:
                    return "VehicleData";
                case DRAW_LINE:
                    return "Draw line";
                case VEHICLECONTROL:
                    return "VehicleControl";
                case GENERIC_CAN_MESSAGE:
                    return "GenericCANMessage";
                case WHEELSPEED:
                    return "WheelSpeed";
                case USER_BUTTON:
                    return "User Button";
                case LOG_MESSAGE:
                    return "LOG_MESSAGE";
                case DMCP_PULSE_MESSAGE:
                    return "DMCP_PULSE_MESSAGE";
                case DMCP_PULSE_ACK_MESSAGE:
                    return "DMCP_PULSE_ACK_MESSAGE";
                case DMCP_PULSE_ACK_CONTAINERS_MESSAGE:
                    return "DMCP_PULSE_ACK_CONTAINERS_MESSAGE";
                case USER_DATA_0:
                    return "UserData_0";
                case USER_DATA_1:
                    return "UserData_1";
                case USER_DATA_2:
                    return "UserData_2";
                case USER_DATA_3:
                    return "UserData_3";
                case USER_DATA_4:
                    return "UserData_4";
                case USER_DATA_5:
                    return "UserData_5";
                case USER_DATA_6:
                    return "UserData_6";
                case USER_DATA_7:
                    return "UserData_7";
                case USER_DATA_8:
                    return "UserData_8";
                case USER_DATA_9:
                    return "UserData_9";
            }
            return "";
        }
    }
} // core::data
