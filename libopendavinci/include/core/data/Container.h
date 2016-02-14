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

#ifndef OPENDAVINCI_CORE_DATA_CONTAINER_H_
#define OPENDAVINCI_CORE_DATA_CONTAINER_H_

#include <sstream>
#include <string>

#include "core/opendavinci.h"
#include "core/base/Serializable.h"
#include "core/data/TimeStamp.h"

namespace core {
    namespace data {

class SerializableData;

        using namespace std;

        /**
         * Container for all interchangeable data.
         */
        class OPENDAVINCI_API Container : public core::base::Serializable {
            public:
                enum DATATYPE {
                    UNDEFINEDDATA                =  1,
                    CONFIGURATION                =  2,
                    DMCP_DISCOVER                =  3,
                    DMCP_CONNECTION_REQUEST      =  4,
                    DMCP_CONFIGURATION_REQUEST   =  5,
                    DMCP_MODULESTATEMESSAGE      =  6,
                    DMCP_MODULEEXITCODEMESSAGE   =  7,
                    MODULESTATISTICS             =  8,
                    RUNTIMESTATISTIC             =  9,
                    PLAYER_COMMAND               = 10,
                    RECORDER_COMMAND             = 11,
                    TIMESTAMP                    = 12,
                    SHARED_DATA                  = 13,
                    SHARED_IMAGE                 = 14,
                    POSITION                     = 15,
                    COMPRESSED_IMAGE             = 16,
/*
                    POINT3 = 17,
                    GPRMC = 18,
                    CAMERAINTRINSICPARAMETERS = 20,
                    CAMERAEXTRINSICPARAMETERS = 21,
                    CAMERAIMAGEGRABBERID = 22,
                    CAMERAIMAGEGRABBERCALIBRATION = 23,
                    LINE = 24,
                    POLYGON = 25,
                    NAMEDLINE = 26,
                    MEMORYSEGMENT = 29
                    CONTOUREDOBJECT              = 30,
                    POINTSHAPEDOBJECT            = 37,
                    WHEELSPEED                   = 75,
                    FORCECONTROL                 = 33,
                    LMS291MESSAGE                = 34,

                    SCENARIO = 830,
                    SCENARIOIDVERTEX3 = 818,
                    SCENARIOHEIGHTIMAGE = 819,
                    SCENARIOTRAFFICCONTROL = 820,
                    SCENARIOTRAFFICSIGN = 821,
                    SCENARIOTRAFFICLIGHT = 822,
                    SCENARIOSTRAIGHTLINE = 823,
                    SCENARIOPOINTMODEL = 824,
                    SCENARIOCLOTHOID = 825,
                    SCENARIOARC = 826,
                    SCENARIOPOLYGON = 827,
                    SCENARIOCYLINDER = 828,
                    SCENARIOCOMPLEXMODEL = 829,
                    SCENARIOLANE = 831,
                    SCENARIOLANEATTRIBUTE = 832,
                    SCENARIOZONE = 833,
                    SCENARIOHEADER = 834,
                    SCENARIOSURROUNDINGS = 835,
                    SCENARIOCONNECTOR = 836,
                    SCENARIOSPOT = 837,
                    SCENARIOBOUNDINGBOX = 838,
                    SCENARIOLAYER = 839,
                    SCENARIOPOINTID = 840,
                    SCENARIOLANEMODEL = 841,
                    SCENARIOIMAGE = 842,
                    SCENARIOCOORDINATESYSTEM = 843,
                    SCENARIOGROUND = 844,
                    SCENARIOPERIMETER = 845,
                    SCENARIOSHAPE = 846,
                    SCENARIOROAD = 847,
                    SCENARIOWGS84COORDINATESYSTEM = 849,

                    SITUATION = 851,
                    SITUATIONBEHAVIOR = 852,
                    SITUATIONSTARTTYPE = 853,
                    SITUATIONOBJECT = 854,
                    SITUATIONHEADER = 855,
                    SITUATIONBOUNDINGBOX = 856,
                    SITUATIONPOINTID = 857,
                    SITUATIONSTOPTYPE = 858,
                    SITUATIONSHAPE = 859,
                    SITUATIONWARPTOSTART = 860,
                    SITUATIONSTOP = 861,
                    SITUATIONRETURNTOSTART = 862,
                    SITUATIONRECTANGLE = 863,
                    SITUATIONPOLYGON = 864,
                    SITUATIONPOINTIDDRIVER = 865,
                    SITUATIONONMOVING = 866,
                    SITUATIONONENTERINPOLYGON = 867,
                    SITUATIONIMMEDIATELY = 868,
                    SITUATIONEXTERNALDRIVER = 867,
                    SITUATIONCOMPLEXMODEL = 868,

                    USER_BUTTON                  = 999,

*/

                    WGS84COORDINATE              = 19,

                    CONTOUREDOBJECTS             = 31,
                    EGOSTATE                     = 32,
                    OBSTACLE                     = 35,
                    OTHERVEHICLESTATE            = 36,
                    ROUTE                        = 38,
                    VEHICLEDATA                  = 39,
                    DRAW_LINE                    = 40,
                    VEHICLECONTROL               = 41,

                    GENERIC_CAN_MESSAGE          = 71,

                    LOG_MESSAGE                  = 100,
                    DMCP_PULSE_MESSAGE           = 101,
                    DMCP_PULSE_ACK_MESSAGE       = 102,
                    DMCP_PULSE_ACK_CONTAINERS_MESSAGE = 103,
                };

            public:
                Container();

                /**
                 * Constructor.
                 *
                 * @param serializableData Data to be serialized.
                 */
                Container(const SerializableData &serializableData);

                /**
                 * Constructor.
                 *
                 * @param serializableData Data to be serialized.
                 * @param dataType Type of data inside this container.
                 */
                Container(const SerializableData &serializableData, const int32_t &dataType);

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                Container(const Container &obj);

                virtual ~Container();

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                Container& operator=(const Container &obj);

                /**
                 * This method returns the data type inside this container.
                 *
                 * @return Data type of the data contained in this container.
                 */
                int32_t getDataType() const;

                virtual ostream& operator<<(ostream &out) const;
                virtual istream& operator>>(istream &in);

                /**
                 * This method returns a usable object:
                 *
                 * @code
                 * Container c;
                 * ...
                 * T t = c.getData<T>();
                 * @endcode
                 *
                 * @return Usable object.
                 */
                template<class T>
                inline T getData() {
                    T containerData;
                    // Read from beginning.
                    m_serializedData.seekg(ios::beg);
                    m_serializedData >> containerData;
                    return containerData;
                }

                /**
                 * This method returns the time stamp when this
                 * container was sent.
                 *
                 * @return Time stamp when this container was sent.
                 */
                const TimeStamp getSentTimeStamp() const;

                /**
                 * This method sets the time stamp when this
                 * container was sent.
                 *
                 * @param sentTimeStamp Time stamp when this container was sent.
                 */
                void setSentTimeStamp(const TimeStamp &sentTimeStamp);

                /**
                 * This method returns the time stamp when this
                 * container was received.
                 *
                 * @return Time stamp when this container was received.
                 */
                const TimeStamp getReceivedTimeStamp() const;

                /**
                 * This method sets the time stamp when this
                 * container was received.
                 *
                 * @param receivedTimeStamp Time stamp when this container was received.
                 */
                void setReceivedTimeStamp(const TimeStamp &receivedTimeStamp);

                /**
                 * This method returns the data type as String.
                 *
                 * @return The data type.
                 */
                const string toString() const;

            private:
                int32_t m_dataType;
                stringstream m_serializedData;

                TimeStamp m_sent;
                TimeStamp m_received;
        };

    }
} // core::data

#endif /*OPENDAVINCI_CORE_DATA_CONTAINER_H_*/
