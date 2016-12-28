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
#include <opendavinci/generated/odcore/data/SharedPointCloud.h>

#include "ComparePointCloud.h"

namespace odcomparepointcloud {

    using namespace std;
    //using namespace odcore;
    //using namespace odcore::base;
    using namespace odcore::data;

    ComparePointCloud::ComparePointCloud() :
        CPCfound(false),
        SPCfound(false) {}

    ComparePointCloud::~ComparePointCloud() {}

    int32_t ComparePointCloud::run() {
        CPCfound=true;
        cout<<CPCfound<<","<<SPCfound<<endl;
        return 0;
    }

} // odcomparepointcloud

