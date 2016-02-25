/**
 * odrecintegrity - Tool for checking the integrity of recorded data
 * Copyright (C) 2014 - 2015 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef RECINTEGRITY_H_
#define RECINTEGRITY_H_

#include "opendavinci/odcore/opendavinci.h"

namespace odrecintegrity {

    /**
     * This class can be used to inspect the integrity of recorded data.
     */
    class RecIntegrity {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            RecIntegrity(const RecIntegrity &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            RecIntegrity& operator=(const RecIntegrity &/*obj*/);

        public:
            RecIntegrity();

            virtual ~RecIntegrity();

            /**
             * This method validates a specified file regarding integrity.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             * @return 0 if specified file is integer, 1 if the file is not integer, and 255 if the file could not be opened.
             */
            int32_t run(const int32_t &argc, char **argv);
    };

} // odrecintegrity

#endif /*RECINTEGRITY_H_*/
