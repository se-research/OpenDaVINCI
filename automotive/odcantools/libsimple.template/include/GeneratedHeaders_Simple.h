/*
 * THIS IS A GENERATED FILE - CHANGES WILL BE OVERWRITTEN.
 */

#ifndef GENERATEDHEADERS_SIMPLE_H_
#define GENERATEDHEADERS_SIMPLE_H_

#include <vector>

#include "generated/WheelSpeed.h"

#include <core/data/Container.h>

#include "GeneratedHeaders_AutomotiveData.h"

namespace simple {

    using namespace std;

    class Simple {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Simple(const Simple &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Simple& operator=(const Simple &/*obj*/);

        public:
            Simple();

            virtual ~Simple();

            /**
             * This method adds the given GenericCANMessage to the internal
             * CAN message decoder. If this message could be decoded (or
             * including the previous sequence, this method returns a valid
             * Container (ie. Container::UNDEFINEDDATA).
             *
             * @param gcm Next GenericCANMessage.
             * @return Container, where the type needs to be checked to determine invalidity (i.e. !Container::UNDEFINEDDATA).
             */
            vector<core::data::Container> mapNext(const automotive::GenericCANMessage &gcm);

        private:
            WheelSpeed m_wheelSpeed;
    };

} // simple

#endif /*GENERATEDHEADERS_SIMPLE_H_*/

