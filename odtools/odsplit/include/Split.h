/**
 * odsplit - Tool for splitting recorded data
 * Copyright (C) 2015 Christian Berger
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

#ifndef SPLIT_H_
#define SPLIT_H_

#include <string>

#include "core/platform.h"

namespace odsplit {

    using namespace std;

    /**
     * This class can be used to split recorded data.
     */
    class Split {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Split(const Split &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Split& operator=(const Split &/*obj*/);

        public:
            /**
             * Constructor.
             */
            Split();

            virtual ~Split();

            /**
             * This method splits a specified file.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             * @return 0 if the split is successful, 1 if the end is not behind the start.
             */
            int32_t run(const int32_t &argc, char **argv);

        private:
            void parseAdditionalCommandLineParameters(const int &argc, char **argv);

        private:
            string m_source;
            string m_range;
            int32_t m_memorySegmentSize;
    };

} // odsplit

#endif /*SPLIT_H_*/
