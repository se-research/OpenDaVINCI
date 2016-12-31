/**
 * odcomparepointcloud - Tool for comparing data between shared point cloud and 
 * compact point cloud
 * Copyright (C) 2016 Hang
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

#ifndef COMPAREPOINTCLOUD_H_
#define COMPAREPOINTCLOUD_H_

#include <vector>
#include <memory>
#include <fstream>

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/data/Container.h>
#include "opendavinci/generated/odcore/data/CompactPointCloud.h"
#include <opendavinci/generated/odcore/data/SharedPointCloud.h>
#include "opendavinci/odcore/wrapper/SharedMemory.h"

namespace odcomparepointcloud {

    /**
     * This class can be used to inspect recorded data.
     */
    class ComparePointCloud {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            ComparePointCloud(const ComparePointCloud &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            ComparePointCloud& operator=(const ComparePointCloud &/*obj*/);

        public:
            ComparePointCloud();

            virtual ~ComparePointCloud();

            /**
             * This method validates a specified file regarding integrity.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             * @return 0 if specified file is integer, 1 if the file is not integer, and 255 if the file could not be opened.
             */
            int32_t run();
        private:
            bool m_CPCfound;
            bool m_SPCfound;
            uint32_t m_frameNumber;
            odcore::data::SharedPointCloud m_spc;
            odcore::data::CompactPointCloud m_cpc;
            bool m_hasAttachedToSharedImageMemory;
            std::shared_ptr<odcore::wrapper::SharedMemory> m_spcSharedMemory;
            std::vector<float> m_xCpc;
            std::vector<float> m_yCpc;
            std::vector<float> m_zCpc;
            std::vector<float> m_xSpc;
            std::vector<float> m_ySpc;
            std::vector<float> m_zSpc;
            std::ofstream outputData;
            float m_verticalAngles[16];
            uint16_t m_sensorOrderIndex[16];
            uint16_t m_16SortedDistances[16];
            //const float START_V_ANGLE = -15.0;//For each azimuth there are 16 points with unique vertical angles from -15 to 15 degrees
            //const float V_INCREMENT = 2.0;  //The vertical angle increment for the 16 points with the same azimuth is 2 degrees
    };

} // odcomparepointcloud

#endif /*COMPAREPOINTCLOUD_H_*/
