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

//#include <algorithm>
//#include <numeric>

//#include <opendavinci/odcore/data/TimeStamp.h>
//#include <opendavinci/generated/odcore/data/SharedData.h>
//#include <opendavinci/generated/odcore/data/image/SharedImage.h>
#include "opendavinci/odtools/player/Player.h"
#include "opendavinci/generated/odcore/data/CompactPointCloud.h"
#include <opendavinci/generated/odcore/data/SharedPointCloud.h>

#include "ComparePointCloud.h"

namespace odcomparepointcloud {

    using namespace std;
    //using namespace odcore;
    //using namespace odcore::base;
    using namespace odcore::data;
    using namespace odtools::player;

    ComparePointCloud::ComparePointCloud() :
        CPCfound(false),
        SPCfound(false),
        frameNumber(0) {}

    ComparePointCloud::~ComparePointCloud() {}

    int32_t ComparePointCloud::run() {
        odcore::io::URL url("file://recording.rec");
        unique_ptr<Player> player;
        player = unique_ptr<Player>(new Player(url, 0, 2800000, 20, false));
        Container c;
            
        /*if(c.getDataType() == odcore::data::CompactPointCloud::ID()){
            cout<<"CPC container found!"<<endl;
        }
        
        c = player->getNextContainerToBeSent();
        
        if(c.getDataType() == odcore::data::SharedPointCloud::ID()){
            cout<<"SPC container found!"<<endl;
        }*/

        while (player->hasMoreData()){
            c = player->getNextContainerToBeSent();
            if(c.getDataType() == odcore::data::CompactPointCloud::ID() || c.getDataType() == odcore::data::SharedPointCloud::ID()){
                frameNumber++;
                cout<<"Frame number="<<frameNumber<<endl;
            }
            else{
                break;
            }
        }
        
        
        frameNumber=frameNumber / 2;
        cout<<"Number of frames:"<<frameNumber<<endl;
        
        
        return 0;
    }

} // odcomparepointcloud

