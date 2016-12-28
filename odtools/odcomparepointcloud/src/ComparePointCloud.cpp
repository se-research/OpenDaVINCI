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

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "opendavinci/odtools/player/Player.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"

#include "ComparePointCloud.h"

namespace odcomparepointcloud {

    using namespace std;
    using namespace odcore::data;
    using namespace odtools::player;

    ComparePointCloud::ComparePointCloud() :
        m_CPCfound(false),
        m_SPCfound(false),
        m_frameNumber(0),
        m_spc(),
        m_cpc(),
        m_hasAttachedToSharedImageMemory(false),
        m_spcSharedMemory(NULL),
        m_xCpc(),
        m_yCpc(),
        m_zCpc(),
        m_xSpc(),
        m_ySpc(),
        m_zSpc() {}

    ComparePointCloud::~ComparePointCloud() {}

    int32_t ComparePointCloud::run() {
        odcore::io::URL url("file://recording.rec");
        unique_ptr<Player> player;
        //player = unique_ptr<Player>(new Player(url, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING));
        player = unique_ptr<Player>(new Player(url, 0, 2800000, 20, false));
        Container c;
            
        /*if(c.getDataType() == odcore::data::CompactPointCloud::ID()){
            cout<<"CPC container found!"<<endl;
        }
        
        c = player->getNextContainerToBeSent();
        
        if(c.getDataType() == odcore::data::SharedPointCloud::ID()){
            cout<<"SPC container found!"<<endl;
        }*/

        //while (player->hasMoreData()){
        //Compare x, y, z of the first frame between CPC and SPC
            c = player->getNextContainerToBeSent();
            if(c.getDataType() == odcore::data::CompactPointCloud::ID()){
                //cout<<"CPC container found!"<<endl;
                m_cpc = c.getData<CompactPointCloud>();  
                float startAzimuth = m_cpc.getStartAzimuth();
                float endAzimuth = m_cpc.getEndAzimuth();
                uint8_t entriesPerAzimuth = m_cpc.getEntriesPerAzimuth();
                string distances = m_cpc.getDistances();
                uint32_t numberOfPoints = distances.size()/2;
                uint32_t numberOfAzimuths = numberOfPoints/entriesPerAzimuth;
                float azimuthIncrement = (endAzimuth-startAzimuth)/numberOfAzimuths;//Calculate the azimuth increment
                stringstream sstr(distances);
                //const float toRadian = static_cast<float>(cartesian::Constants::PI) / 180.0f;
                const float toRadian = static_cast<float>(M_PI) / 180.0f;
                uint16_t distance_integer(0);
                float xyDistance = 0;
                float azimuth = startAzimuth;
                for (uint32_t azimuthIndex = 0; azimuthIndex < numberOfAzimuths; azimuthIndex++) {
                    float verticalAngle = START_V_ANGLE;
                    for (uint8_t sensorIndex = 0; sensorIndex<entriesPerAzimuth; sensorIndex++) {
                        sstr.read((char*)(&distance_integer), 2); // Read distance value from the string in a CPC container point by point
                        float distance = static_cast<float>(distance_integer/100.0f); //convert cm to meter
                        // Compute x, y, z coordinate based on distance, azimuth, and vertical angle
                        xyDistance = distance * cos(verticalAngle * toRadian);
                        m_xCpc.push_back(xyDistance * sin(azimuth * toRadian));
                        m_yCpc.push_back(xyDistance * cos(azimuth * toRadian));
                        m_zCpc.push_back(distance * sin(verticalAngle * toRadian));
                        verticalAngle += V_INCREMENT;
                    }
                    azimuth+=azimuthIncrement;
                }
            }
            
            c = player->getNextContainerToBeSent();
            
            if(c.getDataType() == odcore::data::SharedPointCloud::ID()){
                //cout<<"SPC container found!"<<endl;
                m_spc = c.getData<SharedPointCloud>();
                if (!m_hasAttachedToSharedImageMemory) {
                    m_spcSharedMemory=odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(m_spc.getName()); // Attach the shared point cloud to the shared memory.
                    m_hasAttachedToSharedImageMemory = true; 
                } 
                if (m_spcSharedMemory.get() != NULL && m_spcSharedMemory->isValid()) {
                    // Using a scoped lock to lock and automatically unlock a shared memory segment.
                    odcore::base::Lock lv(m_spcSharedMemory);
                    float *spcData = static_cast<float*>(m_spcSharedMemory->getSharedMemory());
                    uint32_t startID=0;
                    for(uint32_t counter=0;counter<m_spc.getWidth();counter++){
                        m_xSpc.push_back(spcData[counter]);
                        m_ySpc.push_back(spcData[counter+1]);
                        m_zSpc.push_back(spcData[counter+2]);
                        startID+=4;
                    }
                }
            }
            

        //}
        
        
        m_frameNumber=m_frameNumber / 2;
        cout<<"Number of frames:"<<m_frameNumber<<endl;
        
        
        return 0;
    }

} // odcomparepointcloud

