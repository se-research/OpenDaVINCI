/**
 * odrecinspect - Tool for inspecting recorded data
 * Copyright (C) 2014 - 2016 Christian Berger
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

#ifndef RECINSPECT_H_
#define RECINSPECT_H_

#include <map>
#include <vector>

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/data/Container.h>

namespace odrecinspect {

    /**
     * This class can be used to inspect recorded data.
     */
    class RecInspect {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            RecInspect(const RecInspect &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            RecInspect& operator=(const RecInspect &/*obj*/);

        public:
            RecInspect();

            virtual ~RecInspect();

            /**
             * This method validates a specified file regarding integrity.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             * @return 0 if specified file is integer, 1 if the file is not integer, and 255 if the file could not be opened.
             */
            int32_t run(const int32_t &argc, char **argv);

        private:
            std::map<int32_t, uint64_t> m_numberOfContainersPerType;
            std::map<int32_t, odcore::data::Container> m_latestContainersPerType;

            std::map<int32_t, double> m_minDurationBetweenSamplesPerType;
            std::map<int32_t, std::vector<uint64_t> > m_avgDurationBetweenSamplesPerType;
            std::map<int32_t, double> m_maxDurationBetweenSamplesPerType;

            double m_processingTimePerContainer;
    };

} // odrecinspect

#endif /*RECINSPECT_H_*/
