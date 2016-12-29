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

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/data/TimeStamp.h"

namespace odcore {
    namespace data {

class SerializableData;

        using namespace std;

        /**
         * Container for all interchangeable data.
         */
        class OPENDAVINCI_API Container : public odcore::serialization::Serializable {
            public:
                enum DATATYPE {
                    UNDEFINEDDATA                =  1,
                    DMCP_CONFIGURATION_REQUEST   =  5,
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
                    // Reset failbit as some Deserializer fully consume the entire stream.
                    m_serializedData.clear();
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
                 * This method returns the time stamp when the sample 
                 * contained in this container was created.
                 *
                 * @return Time stamp when the content for this container was created.
                 */
                const TimeStamp getSampleTimeStamp() const;

                /**
                 * This method sets the time stamp for the contained sample.
                 *
                 * @param sampleTimeStamp Time stamp for the content.
                 */
                void setSampleTimeStamp(const TimeStamp &sampleTimeStamp);

                /**
                 * This method returns the data type as String.
                 *
                 * @return The data type.
                 */
                const string toString() const;

                /**
                 * This method sets a user-defined attribute.
                 *
                 * @param senderStamp User-defined attribute.
                 */
                void setSenderStamp(const int32_t &senderStamp);

                /**
                 * This methods returns the user-defined attribute.
                 *
                 * @return user-defined attribute.
                 */
                int32_t getSenderStamp() const;

            private:
                int32_t m_dataType;
                stringstream m_serializedData;

                TimeStamp m_sent;
                TimeStamp m_received;
                TimeStamp m_sampleTimeStamp;

                int32_t m_senderStamp;
        };

    }
} // odcore::data

#endif /*OPENDAVINCI_CORE_DATA_CONTAINER_H_*/
