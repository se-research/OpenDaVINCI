/**
 * odcomparepointcloud - Tool for comparing data between shared point cloud and 
 * compact point cloud
 * Copyright (C) 2017 Hang
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

#ifndef COMPAREPOINTCLOUDMODULE_H_
#define COMPAREPOINTCLOUDMODULE_H_

#include <cmath>
#include <vector>
#include <memory>
#include <fstream>
#include <string>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/data/Container.h>
#include "opendavinci/generated/odcore/data/CompactPointCloud.h"
#include <opendavinci/generated/odcore/data/SharedPointCloud.h>
#include "opendavinci/odcore/wrapper/SharedMemory.h"

namespace odcomparepointcloud {

    /**
     * This class can be used to inspect recorded data.
     */
    class ComparePointCloudModule : public odcore::base::module::TimeTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            ComparePointCloudModule(const ComparePointCloudModule &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            ComparePointCloudModule& operator=(const ComparePointCloudModule &/*obj*/);

        public:
            ComparePointCloudModule(const int32_t &argc, char **argv);

            virtual ~ComparePointCloudModule();

            odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();
            /**
             * This method validates a specified file regarding integrity.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             * @return 0 if specified file is integer, 1 if the file is not integer, and 255 if the file could not be opened.
             */

        private:
            virtual void setUp();
            virtual void tearDown();
            int16_t distanceStatistics(odcore::data::Container &);
            void readCPC(odcore::data::Container &, const uint8_t &);
            void readSPC(odcore::data::Container &);
            inline void clearVectors(const uint8_t &, const bool &);
        private:
            bool m_CPCfound;
            bool m_SPCfound;
            uint32_t m_frameNumber;
            odcore::data::SharedPointCloud m_spc;
            odcore::data::CompactPointCloud m_cpc;
            bool m_hasAttachedToSharedImageMemory;
            std::shared_ptr<odcore::wrapper::SharedMemory> m_spcSharedMemory;
            uint8_t m_compareOption; //0: compare azimuth and distance; 1: compare xyz
            std::vector<float> m_distanceCpc;
            std::vector<float> m_azimuthCpc;
            std::vector<float> m_verticalAngleCpc;
            std::vector<float> m_xCpc;
            std::vector<float> m_yCpc;
            std::vector<float> m_zCpc;
            std::vector<float> m_distanceSpc;
            std::vector<float> m_azimuthSpc;
            std::vector<float> m_verticalAngleSpc;
            std::vector<float> m_xSpc;
            std::vector<float> m_ySpc;
            std::vector<float> m_zSpc;
            //If the SPC has "xyz+intensity" structure, m_Error1, m_Error2, and m_Error3 represent the differences in xyz, respectively.
            //Otherwise, they represent the differences in distance, azimuth, and vertical angle, respectively.
            std::vector<float> m_Error1;
            std::vector<float> m_Error2;
            std::vector<float> m_Error3;
            std::ofstream m_outputData;
            std::ofstream m_cpcFrame;
            std::ofstream m_spcFrame;
            float m_verticalAngles[16];
            uint16_t m_sensorOrderIndex[16];
            uint16_t m_16SortedDistances[16];
            std::string m_recordingFile;
            bool m_allFrames;
            bool m_distanceHistogram;
            uint64_t m_chosenFrame;
            uint8_t m_sendPointCloudOption; //0: send SPC only; 1: send CPC only; 2: send both
            uint64_t m_currentFrame;
            const float m_toRadian = static_cast< float >(M_PI) / 180.0f;
            
            const uint16_t m_MIN_DISTANCE = 500; //resolution 2mm
            const uint16_t m_STEP = 100; //20cm
            //There are (50000-500)/100=495 distance intervals from 1m (500 * 2mm) to 100m (50000 * 2mm) with step 100 (20cm)
            const uint16_t m_MAX_INDEX = 494;
            uint64_t m_distanceIntervals[495];//count the number of distance values in each interval
            
    };

} // odcomparepointcloud

#endif /*COMPAREPOINTCLOUDMODULE_H_*/
