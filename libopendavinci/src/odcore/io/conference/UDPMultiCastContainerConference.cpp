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
#include <sstream>

#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/io/conference/UDPMultiCastContainerConference.h"
#include "opendavinci/odcore/io/udp/UDPFactory.h"
#include "opendavinci/odcore/opendavinci.h"

namespace odcore {
    namespace io {
        namespace conference {

            using namespace std;
            using namespace base;
            using namespace data;
            using namespace exceptions;

            UDPMultiCastContainerConference::UDPMultiCastContainerConference(const string &address, const uint32_t &port) throw (ConferenceException) :
                m_sender(NULL),
                m_receiver(NULL) {
                try {
                    m_sender = odcore::io::udp::UDPFactory::createUDPSender(address, port);
                }
                catch (string &s) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(ConferenceException, s);
                }

                try {
                    m_receiver = odcore::io::udp::UDPFactory::createUDPReceiver(address, port);
                }
                catch (string &s) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(ConferenceException, s);
                }

                // Register ourselves as string listeners.
                m_receiver->setStringListener(this);

                // Start receiving.
                m_receiver->start();
            }

            UDPMultiCastContainerConference::~UDPMultiCastContainerConference() {
                // Stop receiving.
                m_receiver->stop();

                // Unregister ourselves.
                m_receiver->setStringListener(NULL);
            }

            void UDPMultiCastContainerConference::nextString(const string &s) {
                if (hasContainerListener()) {
                    Container container;

                    stringstream stringstreamData(s);
                    stringstreamData >> container;

                    container.setReceivedTimeStamp(TimeStamp());

                    // Use superclass to distribute any received containers.
                    receive(container);
                }
            }

            void UDPMultiCastContainerConference::send(Container &container) const {
                // Set sending time stamp.
                container.setSentTimeStamp(TimeStamp());

                // If sample time stamp is unset, use sent time stamp.
                if (container.getSampleTimeStamp().toMicroseconds() == 0) {
                    container.setSampleTimeStamp(container.getSentTimeStamp());
                }

                // If the container's senderStamp field is unset, set it
                // to this conference's senderStamp.
                if (container.getSenderStamp() == 0) {
                    container.setSenderStamp(getSenderStamp());
                }

                stringstream stringstreamValue;
                stringstreamValue << container;

                string stringValue = stringstreamValue.str();

                // Send data.
                m_sender->send(stringValue);
            }

        }
    }
} // odcore::io::conference
