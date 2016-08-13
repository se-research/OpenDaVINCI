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

#ifndef CORE_MEMORYARRAYTESTSUITE_H_
#define CORE_MEMORYARRAYTESTSUITE_H_

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

class MemoryArrayTest : public CxxTest::TestSuite {
    public:
        void testEigenDataMappingTwoBytesUsingSharedPointCloud() {
            // Prepare constants to describe the PointCloud
            // stored in shared memory.
            const int FRAME_NUMBER=30;
            const string NAME = "pointCloud";
            const string NAME2 = "Hang";
            const uint32_t SIZE_PER_COMPONENT = sizeof(float);
            const uint8_t NUMBER_OF_COMPONENTS_PER_POINT = 4; // How many components do we have per vector?
            const uint32_t LENGTH = 3; // How many points (i.e. vectors with (x,y,z,intensity)) are stored in the shared memory segment?
            const uint32_t SIZE = LENGTH * NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT; // What is the total size of the shared memory?
            //const uint32_t SIZE = LENGTH * SIZE_PER_COMPONENT;
            /*const float sampleData[3][12]={
                {1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.10,11.11,12.12},
                {13.1,14.1,15.1,16.1,17.1,18.1,19.1,20.1,21.1,22.1,23.1,24.1},
                {25.2,26.2,27.2,28.2,29.2,30.2,31.2,32.2,33.2,34.2,35.2,36.2}};*/
            float sampleData[FRAME_NUMBER][12];
            for(int i=0;i<FRAME_NUMBER;i++){
                for(int j=0;j<12;j++){
                    sampleData[i][j]=i+(float)j*0.1;
			        cout<<sampleData[i][j]<<" , ";
		        }
		        cout<<endl;
	        }
            Container toReceiver[FRAME_NUMBER];
            Container fromSender[FRAME_NUMBER];
            
            std::shared_ptr<SharedMemory> VelodyneSharedMemory;
            std::shared_ptr<SharedMemory> frameStore[FRAME_NUMBER];

            try {
                // This pointer would need to be created once from the sender at startup.
                VelodyneSharedMemory=SharedMemoryFactory::createSharedMemory(NAME, SIZE);
                for(int iii=0;iii<FRAME_NUMBER;iii++){
                    frameStore[iii]=SharedMemoryFactory::createSharedMemory(to_string(iii)+NAME2, SIZE);
                }
                /*cout<<frameStore[0]->getSharedMemory()<<endl;
                cout<<frameStore[1]->getSharedMemory()<<endl;
                cout<<frameStore[2]->getSharedMemory()<<endl;*/
                
                // Sender side.
                cout << "Write to memory:" << endl;
                {
                    for(int iii=0;iii<FRAME_NUMBER;iii++){
                        if (frameStore[iii]->isValid()) {
                            // Using a scoped lock to lock and automatically unlock a shared memory segment.
                            odcore::base::Lock l(frameStore[iii]);
                            float *velodyneRawData = static_cast<float*>(frameStore[iii]->getSharedMemory());

                            // Alignment of Velodyne data: (x0, y0, z0, intensity0), (x1, y1, z1, intensity1), ...
                            // Add some example data.
                            for(int jjj=0;jjj<12;jjj++){
                                velodyneRawData[jjj]=sampleData[iii][jjj];
                            }

                            //cout << "Test" << endl;
                            for(unsigned int i = 0; i < LENGTH * NUMBER_OF_COMPONENTS_PER_POINT; i++) {
                                cout << (float) velodyneRawData[i] << " , ";
                            }
                            cout << endl;
                        }
                    }
                    cout<<"From memory to point cloud:"<<endl;
                    for(int counter=0;counter<FRAME_NUMBER;counter++){
                    //if(VelodyneSharedMemory->isValid() && frameStore[1]->isValid()){
                        if(frameStore[counter]->isValid()){
                            //Lock l1(VelodyneSharedMemory);
                            Lock l2(frameStore[counter]);
                            //memcpy(VelodyneSharedMemory->getSharedMemory(),frameStore[1]->getSharedMemory(),frameStore[1]->getSize());
                            float *readFrame = static_cast<float*>(frameStore[counter]->getSharedMemory());
                            for(unsigned int i = 0; i < LENGTH * NUMBER_OF_COMPONENTS_PER_POINT; i++) {
                                cout << (float) readFrame[i] << " , ";
                            }
                            cout << endl;
                            
                            SharedPointCloud spc;
                            spc.setName(frameStore[counter]->getName()); // Name of the shared memory segment with the data.
                            spc.setSize(frameStore[counter]->getSize()); // Size in raw bytes.
                            spc.setWidth(LENGTH); // Number of points.
                            spc.setHeight(1); // We have just a sequence of vectors.
                            spc.setNumberOfComponentsPerPoint(NUMBER_OF_COMPONENTS_PER_POINT);
                            spc.setComponentDataType(SharedPointCloud::FLOAT_T); // Data type per component.
                            spc.setUserInfo(SharedPointCloud::XYZ_INTENSITY);
                            
                            toReceiver[counter] = Container(spc);
                        } 
                    }
                }
                
                cout<<"Read from point cloud:"<<endl;
                     // Receiver side.
                {
                    // Let's assume we have received the container
                    // (would typically happen via the ContainerConference).
                    for(int frame=0;frame<FRAME_NUMBER;frame++){
                        fromSender[frame] = toReceiver[frame];

                        // Is it from the correct type?
                        if (fromSender[frame].getDataType() == SharedPointCloud::ID()) {
                            SharedPointCloud senderSharedPointCloud = fromSender[frame].getData<SharedPointCloud>();
                            //cout << senderSharedPointCloud.toString() << endl;

                            // Attach ourselves to the same shared memory segment (would be needed just once).
                            std::shared_ptr<SharedMemory> receiverSharedMemory(SharedMemoryFactory::attachToSharedMemory(senderSharedPointCloud.getName()));

                            if (receiverSharedMemory->isValid()) {
                                // Using a scoped lock to lock and automatically unlock a shared memory segment.
                                odcore::base::Lock l(receiverSharedMemory);
                                // We need to check (a) are we using the correct type (float)
                                // and is the number of components per vector correct (4)
                                // as Eigen is a compile-time type and thus, we cannot
                                // define dynamic sizes for the InnerStride.
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
                }
            }   

            catch(string &exception) {
                cerr << "Shared memory could not created: " << exception << endl;
                TS_ASSERT(false);
            }
        }
};

#endif /*CORE_MEMORYARRAYTESTSUITE_H_*/
