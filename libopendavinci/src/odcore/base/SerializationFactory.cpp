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

#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/QueryableNetstringsDeserializer.h"
#include "opendavinci/odcore/base/QueryableNetstringsSerializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"

namespace odcore {
    namespace base {

        using namespace std;

        Mutex SerializationFactory::m_singletonMutex;
        SerializationFactory* SerializationFactory::m_singleton = NULL;

        void SerializationFactory::setSingleton(SerializationFactory *singleton) {
            if (SerializationFactory::m_singleton != NULL)
                delete SerializationFactory::m_singleton;

            SerializationFactory::m_singleton = singleton;
        }

        SerializationFactory& SerializationFactory::getInstance() {
            // Double-Checked Locking
            {
                if (SerializationFactory::m_singleton == NULL) {
                    Lock l(SerializationFactory::m_singletonMutex);
                    if (SerializationFactory::m_singleton == NULL) {
                        SerializationFactory::setSingleton(new SerializationFactory());
                    }
                }
            }

            return (*SerializationFactory::m_singleton);
        }

        SerializationFactory::SerializationFactory() {}

        SerializationFactory::~SerializationFactory() {
            setSingleton(NULL);
        }

        std::shared_ptr<Serializer> SerializationFactory::getSerializer(ostream &out) const {
            return std::shared_ptr<Serializer>(new QueryableNetstringsSerializer(out));
        }

        std::shared_ptr<Deserializer> SerializationFactory::getDeserializer(istream &in) const {
            return std::shared_ptr<Deserializer>(new QueryableNetstringsDeserializer(in));
        }

    }
} // odcore::base
