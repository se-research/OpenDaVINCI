/**
 * odfilter - Tool for filtering container streams in pipes
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

#ifndef FILTER_H_
#define FILTER_H_

#include <string>
#include <vector>

#include "core/platform.h"

namespace odfilter {

    using namespace std;

    /**
     * This class can be used to filter container streams in pipes.
     */
    class Filter {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Filter(const Filter &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Filter& operator=(const Filter &/*obj*/);

        public:
            /**
             * Constructor.
             */
            Filter();

            virtual ~Filter();

            /**
             * This method runs odfilter.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             * @return 0 if the filter is successful, 1 if both, the keep and the drop parameters are specified.
             */
            int32_t run(const int32_t &argc, char **argv);

        private:
            void parseAdditionalCommandLineParameters(const int &argc, char **argv);

            /**
             * This method returns a sorted vector with unique numerical values
             * extracted from a comma-separated list of numbers.
             *
             * @param s Comma-separated list of numbers.
             * @return vector containing sorted unique numerical values.
             */
            vector<uint32_t> getListOfNumbers(const string &s);

        private:
            vector<uint32_t> m_keep;
            vector<uint32_t> m_drop;
    };

} // odfilter

#endif /*FILTER_H_*/
