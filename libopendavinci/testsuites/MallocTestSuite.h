/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2016 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef CORE_EIGENEXAMPLESTESTSUITE_H_
#define CORE_EIGENEXAMPLESTESTSUITE_H_

#include <iostream>
#include <string>

#include "cxxtest/TestSuite.h"

#include <memory>
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/data/Container.h"
//#include "opendavinci/odcore/wrapper/Eigen.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"

#include "opendavinci/generated/odcore/data/SharedPointCloud.h"

using namespace std;
using namespace odcore;
using namespace odcore::base;
using namespace odcore::data;
using namespace odcore::wrapper;

class EigenExamplesTest : public CxxTest::TestSuite {
    public:
        void testEigenDataMappingTwoBytesUsingSharedPointCloud() {
            // Prepare constants to describe the PointCloud
            // stored in shared memory.
            const int FRAME_NUMBER=30;
            const string NAME = "pointCloud";
            //const string NAME2 = "Hang";
            const uint32_t SIZE_PER_COMPONENT = sizeof(float);
            const uint8_t NUMBER_OF_COMPONENTS_PER_POINT = 4; // How many components do we have per vector?
            const uint32_t LENGTH = 3; // How many points (i.e. vectors with (x,y,z,intensity)) are stored in the shared memory segment?
            const uint32_t SIZE = LENGTH * SIZE_PER_COMPONENT * SIZE_PER_COMPONENT; // What is the total size of the shared memory?
            float sampleData[FRAME_NUMBER][12];
            for(int i=0;i<FRAME_NUMBER;i++){
                for(int j=0;j<12;j++){
                    sampleData[i][j]=i+(float)j*0.1;
			        cout<<sampleData[i][j]<<" , ";
		        }
		        cout<<endl;
	        }
	        //float sampleData[12]={1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.10,11.11,12.12};
            //Container toReceiver[FRAME_NUMBER];
            //Container fromSender[FRAME_NUMBER];
            Container toReceiver;
            Container fromSender;
            
            std::shared_ptr<SharedMemory> VelodyneSharedMemory;
            //std::shared_ptr<SharedMemory> frameStore[FRAME_NUMBER];

            try {
                // This pointer would need to be created once from the sender at startup.
                float* segment[FRAME_NUMBER];
                for(int iii=0;iii<FRAME_NUMBER;iii++){
                    segment[iii]=(float*)malloc(SIZE);
                }
                VelodyneSharedMemory=SharedMemoryFactory::createSharedMemory(NAME, SIZE);

                // Sender side.
                cout << "Write to memory:" << endl;
                    for(int iii=0;iii<FRAME_NUMBER;iii++){
                       

                            // Alignment of Velodyne data: (x0, y0, z0, intensity0), (x1, y1, z1, intensity1), ...
                            // Add some example data.
                            for(int jjj=0;jjj<12;jjj++){
                                segment[iii][jjj]=sampleData[iii][jjj];
                                cout<<segment[iii][jjj]<<" , ";
                            }
                            cout << endl;
                    }
                    cout<<"From memory to point cloud:"<<endl;
                    for(int counter=0;counter<FRAME_NUMBER;counter++){
                        if(VelodyneSharedMemory->isValid()){
                            Lock l(VelodyneSharedMemory);
                            memcpy(VelodyneSharedMemory->getSharedMemory(),segment[counter],SIZE);
                            float *readFrame = static_cast<float*>(VelodyneSharedMemory->getSharedMemory());
                            for(unsigned int i = 0; i < LENGTH * NUMBER_OF_COMPONENTS_PER_POINT; i++) {
                                cout<<readFrame[i]<<" , ";
                            }
                            cout << endl;
                            }
                            SharedPointCloud spc;
                            spc.setName(VelodyneSharedMemory->getName()); // Name of the shared memory segment with the data.
                            spc.setSize(SIZE); // Size in raw bytes.
                            spc.setWidth(LENGTH); // Number of points.
                            spc.setHeight(1); // We have just a sequence of vectors.
                            spc.setNumberOfComponentsPerPoint(NUMBER_OF_COMPONENTS_PER_POINT);
                            spc.setComponentDataType(SharedPointCloud::FLOAT_T); // Data type per component.
                            spc.setUserInfo(SharedPointCloud::XYZ_INTENSITY);
                            
                            toReceiver = Container(spc); 
                            //toReceiver[counter] = Container(spc);
                
                cout<<"Read from point cloud:"<<endl;
                     // Receiver side.
                        //fromSender[frame] = toReceiver[frame];
                        fromSender = toReceiver;

                        // Is it from the correct type?
                        if (fromSender.getDataType() == SharedPointCloud::ID()) {
                            SharedPointCloud senderSharedPointCloud = fromSender.getData<SharedPointCloud>();
                            //cout << senderSharedPointCloud.toString() << endl;

                            // Attach ourselves to the same shared memory segment (would be needed just once).
                            std::shared_ptr<SharedMemory> receiverSharedMemory(SharedMemoryFactory::attachToSharedMemory(senderSharedPointCloud.getName()));

                            if (receiverSharedMemory->isValid()) {
                                // Using a scoped lock to lock and automatically unlock a shared memory segment.
                                odcore::base::Lock l(receiverSharedMemory);
                                if (senderSharedPointCloud.getComponentDataType() == SharedPointCloud::FLOAT_T
                                    && (senderSharedPointCloud.getNumberOfComponentsPerPoint() == 4)
                                    && (senderSharedPointCloud.getUserInfo() == SharedPointCloud::XYZ_INTENSITY)) {
                                    // Get pointer to the beginning of the data.
                                    float *velodyneRawData = static_cast<float*>(receiverSharedMemory->getSharedMemory());
                                    int startID=0;
                                    for(unsigned int i = 0; i < senderSharedPointCloud.getWidth(); i++) {
                                         cout<<velodyneRawData[startID]<<" , "<<velodyneRawData[startID+1]<<" , "<<velodyneRawData[startID+2]<<" , "<<velodyneRawData[startID+3]<<endl;
                                         startID=senderSharedPointCloud.getNumberOfComponentsPerPoint()*(i+1);
                                     }
                                }
                            }
                        }

                    }
                cout<<"Free all memory segments."<<endl;
                for(int iii=0;iii<FRAME_NUMBER;iii++){
                    free(segment[iii]);
                }
            }   

            catch(string &exception) {
                cerr << "Shared memory could not created: " << exception << endl;
                TS_ASSERT(false);
            }
        }
};

#endif /*CORE_EIGENEXAMPLESTESTSUITE_H_*/
