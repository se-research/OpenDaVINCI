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

#ifndef OPENDAVINCI_CORE_SERIALIZATION_SERIALIZATIONFACTORY_H_
#define OPENDAVINCI_CORE_SERIALIZATION_SERIALIZATIONFACTORY_H_

#include <iosfwd>

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/base/Mutex.h"

class SerializationFactoryTestCase;

namespace odcore {
    namespace base {

class Deserializer;
class Serializer;

        using namespace std;

        /**
         * This class is the factory for providing serializers and
         * deserializers.
         *
         * @See Serializable
         */
        class OPENDAVINCI_API SerializationFactory {
            protected:
                friend class SerializationFactoryTestCase;
                SerializationFactory();

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                SerializationFactory(const SerializationFactory &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                SerializationFactory& operator=(const SerializationFactory &);

            public:
                static SerializationFactory& getInstance();

                virtual ~SerializationFactory();

                /**
                 * This method returns a serializer.
                 *
                 * @param out Output stream for serialization.
                 * @return Serializer.
                 */
                virtual std::shared_ptr<Serializer> getSerializer(ostream &out) const;

                /**
                 * This method returns a deserializer.
                 *
                 * @param in Input stream for deserialization.
                 * @return Deserializer.
                 */
                virtual std::shared_ptr<Deserializer> getDeserializer(istream &in) const;

                /**
                 * This method returns a QueryableNetstringsSerializer.
                 *
                 * @param out Output stream for serialization.
                 * @return Serializer.
                 */
                std::shared_ptr<Serializer> getQueryableNetstringsSerializer(ostream &out) const;

                /**
                 * This method returns a QueryableNetstringsDeserializer.
                 *
                 * @param in Input stream for deserialization.
                 * @return Deserializer.
                 */
                std::shared_ptr<Deserializer> getQueryableNetstringsDeserializer(istream &in) const;

            protected:
                /**
                 * This method sets the singleton pointer.
                 *
                 * @param singleton Singleton to be used.
                 */
                static void setSingleton(SerializationFactory* singleton);

            private:
                static base::Mutex m_singletonMutex;

            protected:
                static SerializationFactory* m_singleton;
        };

    }
} // odcore::base

#endif /*OPENDAVINCI_CORE_SERIALIZATION_SERIALIZATIONFACTORY_H_*/
