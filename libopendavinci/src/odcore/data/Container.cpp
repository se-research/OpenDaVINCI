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

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/SerializableData.h"

namespace odcore {
    namespace data {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::serialization;

        Container::Container() :
                m_dataType(UNDEFINEDDATA),
                m_serializedData(),
                m_sent(TimeStamp(0, 0)),
                m_received(TimeStamp(0, 0)),
                m_sampleTimeStamp(TimeStamp(0, 0)) {}

        Container::Container(const SerializableData &serializableData) :
                m_dataType(serializableData.getID()),
                m_serializedData(),
                m_sent(TimeStamp(0, 0)),
                m_received(TimeStamp(0, 0)),
                m_sampleTimeStamp(TimeStamp(0, 0)) {
            // Get data for container.
            m_serializedData << serializableData;
        }

        Container::Container(const SerializableData &serializableData, const int32_t &dataType) :
                m_dataType(dataType),
                m_serializedData(),
                m_sent(TimeStamp(0, 0)),
                m_received(TimeStamp(0, 0)),
                m_sampleTimeStamp(TimeStamp(0, 0)) {
            // Get data for container.
            m_serializedData << serializableData;
        }

        Container::Container(const Container &obj) :
                Serializable(),
                m_dataType(obj.getDataType()),
                m_serializedData(),
                m_sent(obj.m_sent),
                m_received(obj.m_received),
                m_sampleTimeStamp(obj.m_sampleTimeStamp) {
            m_serializedData.str(obj.m_serializedData.str());
        }

        Container& Container::operator=(const Container &obj) {
            m_dataType = obj.getDataType();
            m_serializedData.str(obj.m_serializedData.str());
            setSentTimeStamp(obj.getSentTimeStamp());
            setReceivedTimeStamp(obj.getReceivedTimeStamp());
            setSampleTimeStamp(obj.getSampleTimeStamp());

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

        const TimeStamp Container::getSampleTimeStamp() const {
            return m_sampleTimeStamp;
        }

        void Container::setSampleTimeStamp(const TimeStamp &sampleTimeStamp) {
            m_sampleTimeStamp = sampleTimeStamp;
        }

        ostream& Container::operator<<(ostream &out) const {
            stringstream bufferOut;

            // We need a dedicated scope as the writing will take place
            // in the Serializer's destructor.
            {
                SerializationFactory& sf=SerializationFactory::getInstance();
                std::shared_ptr<Serializer> s = sf.getSerializer(bufferOut);

                // Write container data type.
                int32_t dataType = getDataType();
                s->write(1, dataType);

                // Write container data.
                s->write(2, m_serializedData.str());

                // Write sent time stamp data.
                s->write(3, m_sent);

                // Write received time stamp data.
                s->write(4, m_received);

                // Write sample time stamp.
                s->write(5, m_sampleTimeStamp);
            }

            // Write Container header.
            {
                // Write Proto header: 0x0D 0xA4 A B C <payload>.
                // 0xA4 A B C can be read as uint32_t, 0xA4 can be cut and
                // A B C can be read as little endian shifted by 8 bits to
                // the right.
                const char byte0 = 0x0D;
                const uint8_t byte1 = 0xA4;

                const string str_bufferOut = bufferOut.str();
                uint32_t length = (str_bufferOut.size());

                // Shift length by 8 bits to the left to make space
                // for 0xA4 header part.
                length = length << 8;

                // Add 0xA4 as part of OpenDaVINCI container header.
                length |= byte1;

                // Transform value to little endian.
                length = htole32(length);

                // Write header and payload.
                out.write(&byte0, sizeof(byte0));
                out.write((char*)(&length), sizeof(uint32_t));
                out << str_bufferOut;
            }

            return out;
        }

        istream& Container::operator>>(istream &in) {
            string rawData = "";

            // Read Container header.
            vector<char> temporaryBuffer;
            stringstream bufferIn;
            {
                const uint32_t OPENDAVINCI_CONTAINER_HEADER_SIZE = 5;
                bool consumedOpenDaVINCIContainerHeader = false;
                uint32_t bytesRead = 0;
                uint32_t expectedBytes = 0;
                uint32_t bufferPosition = 0;

                while (in.good()) {
                    if (0 == expectedBytes) {
                        // Copy bytes to internal buffer.
                        char c = in.get();
                        bufferIn.put(c);
                        bytesRead++;
                    }
                    else {
                        in.read(&temporaryBuffer[bufferPosition], (expectedBytes > 1024) ? 1024 : expectedBytes);
                        const streamsize extractedBytes = in.gcount();
                        bufferPosition += extractedBytes;
                        if (extractedBytes > 0) {
                            expectedBytes -= extractedBytes;
                        }
                        else {
                            cerr << "[core::base::Container] Failed to read " << expectedBytes << "." << endl;
                        }
                        if (0 == expectedBytes) {
                            // Stop processing and redirect bufferIn's underlying pointer to avoid copying data.
                            bufferIn.rdbuf()->pubsetbuf(&temporaryBuffer[0], bufferPosition);
                            break;
                        }
                    }

                    if ( (bytesRead == OPENDAVINCI_CONTAINER_HEADER_SIZE) && !consumedOpenDaVINCIContainerHeader) {
                        consumedOpenDaVINCIContainerHeader = true;

                        char byte0 = 0;
                        expectedBytes = 0;

                        // Read five bytes OpenDaVINCI Container header.
                        bufferIn.read(&byte0, sizeof(char));
                        bufferIn.read((char*)&expectedBytes, sizeof(uint32_t));

                        // Transform value from little endian to host.
                        expectedBytes = le32toh(expectedBytes);

                        // Extract first byte as part of OpenDaVINCI Container header.
                        unsigned char byte1 = (expectedBytes & 0xFF);
                        expectedBytes = expectedBytes >> 8;

                        // Clear buffer as the remaining bytes are the payload.
                        bufferIn.str("");

                        // Allocate contiguous space to store bytes.
                        temporaryBuffer.resize(expectedBytes);

                        // Check validity of the received bytes.
                        if (!( (0x0D == byte0) && (0xA4 == byte1) )) {
                            std::cerr << "[core::base::Container] Failed to decode OpenDaVINCI container header." << std::endl;
                        }
                    }
                }
            }

            SerializationFactory& sf=SerializationFactory::getInstance();
            std::shared_ptr<Deserializer> d = sf.getDeserializer(bufferIn);

            // Read container data type.
            d->read(1, m_dataType);

            // Read container data.
            d->read(2, rawData);
            m_serializedData.str(rawData);

            // Read sent time stamp data.
            d->read(3, m_sent);

            // Read received time stamp data.
            d->read(4, m_received);

            // Read sample time stamp.
            d->read(5, m_sampleTimeStamp);

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
