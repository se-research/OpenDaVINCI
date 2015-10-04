/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Header file for: WheelSpeed

#ifndef WHEELSPEED_H_
#define WHEELSPEED_H_

#include "generated/WheelSpeed.h"

#include <core/data/Container.h>

#include "GeneratedHeaders_AutomotiveData.h"

namespace simple {

    using namespace std;

    class WheelSpeed {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            WheelSpeed(const WheelSpeed &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            WheelSpeed& operator=(const WheelSpeed &/*obj*/);

        public:
            WheelSpeed();

            virtual ~WheelSpeed();

            core::data::Container decode(const automotive::GenericCANMessage &gcm);
    };

} // simple

#endif /*WHEELSPEED_H_*/

