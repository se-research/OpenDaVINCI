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

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/wrapper/Eigen.h"
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
        void testEigenDataMappingOneByte() {
            const string NAME = "MySharedMemory";
            const uint32_t SIZE = 12 * sizeof(unsigned char);

            try {
                SharedPointer<SharedMemory> sharedMemory(SharedMemoryFactory::createSharedMemory(NAME, SIZE));

                if (sharedMemory->isValid()) {
                    {
                        // Using a scoped lock to lock and automatically unlock a shared memory segment.
                        odcore::base::Lock l(sharedMemory);
                        unsigned char *velodyneRawData = static_cast<unsigned char*>(sharedMemory->getSharedMemory());

                        // Alignment of Velodyne data: (x0, y0, z0, intensity0), (x1, y1, z1, intensity1), ...
                        velodyneRawData[0] = 1;
                        velodyneRawData[1] = 2;
                        velodyneRawData[2] = 3;
                        velodyneRawData[3] = 90;

                        velodyneRawData[4] = 4;
                        velodyneRawData[5] = 5;
                        velodyneRawData[6] = 6;
                        velodyneRawData[7] = 91;

                        velodyneRawData[8] = 7;
                        velodyneRawData[9] = 8;
                        velodyneRawData[10] = 9;
                        velodyneRawData[11] = 92;

                        cout << "Test 1" << endl;
                        for(int i = 0; i < 12; i++) {
                            cout << (int) velodyneRawData[i] << " ";
                        }
                        cout << endl;

                        int numberOfPoints = 3;
                        typedef Map<Matrix<unsigned char, Dynamic, Dynamic>, 0, InnerStride<4> > Slice;
                        Slice x(velodyneRawData, numberOfPoints, 1);
                        Slice y(velodyneRawData+1, numberOfPoints, 1);
                        Slice z(velodyneRawData+2, numberOfPoints, 1);
                        Slice intensity(velodyneRawData+3, numberOfPoints, 1);
                        cout << " ";
                        for(int i = 0; i < numberOfPoints; i++) {
                            cout << "x = " << (int)x(i, 0)
                                 << ", y = " << (int)y(i, 0)
                                 << ", z = " << (int)z(i, 0)
                                 << ", intensity = " << (int)intensity(i, 0) << endl;
                        }

                        TS_ASSERT(x(0,0) == 1);
                        TS_ASSERT(y(0,0) == 2);
                        TS_ASSERT(z(0,0) == 3);
                        TS_ASSERT(intensity(0,0) == 90);

                        TS_ASSERT(x(1,0) == 4);
                        TS_ASSERT(y(1,0) == 5);
                        TS_ASSERT(z(1,0) == 6);
                        TS_ASSERT(intensity(1,0) == 91);

                        TS_ASSERT(x(2,0) == 7);
                        TS_ASSERT(y(2,0) == 8);
                        TS_ASSERT(z(2,0) == 9);
                        TS_ASSERT(intensity(2,0) == 92);
                    }
                }
            }
            catch(string &exception) {
                cerr << "Shared memory could not created: " << exception << endl;
                TS_ASSERT(false);
            }
        }

        void testEigenDataMappingTwoBytes() {
            const string NAME = "MySharedMemory";
            const uint32_t SIZE = 12 * sizeof(float);

            try {
                SharedPointer<SharedMemory> sharedMemory(SharedMemoryFactory::createSharedMemory(NAME, SIZE));

                if (sharedMemory->isValid()) {
                    {
                        // Using a scoped lock to lock and automatically unlock a shared memory segment.
                        odcore::base::Lock l(sharedMemory);
                        float *velodyneRawData = static_cast<float*>(sharedMemory->getSharedMemory());

                        // Alignment of Velodyne data: (x0, y0, z0, intensity0), (x1, y1, z1, intensity1), ...
                        velodyneRawData[0] = 1.1;
                        velodyneRawData[1] = 2.2;
                        velodyneRawData[2] = 3.3;
                        velodyneRawData[3] = 90.4;

                        velodyneRawData[4] = 4.5;
                        velodyneRawData[5] = 5.6;
                        velodyneRawData[6] = 6.7;
                        velodyneRawData[7] = 91.8;

                        velodyneRawData[8] = 7.9;
                        velodyneRawData[9] = 8.1;
                        velodyneRawData[10] = 9.2;
                        velodyneRawData[11] = 92.3;

                        cout << "Test 2" << endl;
                        for(int i = 0; i < 12; i++) {
                            cout << (float) velodyneRawData[i] << " ";
                        }
                        cout << endl;

                        int numberOfPoints = 3;
                        typedef Map<Matrix<float, Dynamic, Dynamic>, 0, InnerStride<4> > Slice;
                        Slice x((float*)velodyneRawData, numberOfPoints, 1);
                        Slice y((float*)velodyneRawData+1, numberOfPoints, 1);
                        Slice z((float*)velodyneRawData+2, numberOfPoints, 1);
                        Slice intensity((float*)velodyneRawData+3, numberOfPoints, 1);
                        cout << " ";
                        for(int i = 0; i < numberOfPoints; i++) {
                            cout << "x = " << (float)x(i, 0)
                                 << ", y = " << (float)y(i, 0)
                                 << ", z = " << (float)z(i, 0)
                                 << ", intensity = " << (float)intensity(i, 0) << endl;
                        }

                        TS_ASSERT_DELTA(x(0,0), 1.1, 1e-1);
                        TS_ASSERT_DELTA(y(0,0), 2.2, 1e-1);
                        TS_ASSERT_DELTA(z(0,0), 3.3, 1e-1);
                        TS_ASSERT_DELTA(intensity(0,0), 90.4, 1e-1);

                        TS_ASSERT_DELTA(x(1,0), 4.5, 1e-1);
                        TS_ASSERT_DELTA(y(1,0), 5.6, 1e-1);
                        TS_ASSERT_DELTA(z(1,0), 6.7, 1e-1);
                        TS_ASSERT_DELTA(intensity(1,0), 91.8, 1e-1);

                        TS_ASSERT_DELTA(x(2,0), 7.9, 1e-1);
                        TS_ASSERT_DELTA(y(2,0), 8.1, 1e-1);
                        TS_ASSERT_DELTA(z(2,0), 9.2, 1e-1);
                        TS_ASSERT_DELTA(intensity(2,0), 92.3, 1e-1);
                    }
                }
            }
            catch(string &exception) {
                cerr << "Shared memory could not created: " << exception << endl;
                TS_ASSERT(false);
            }
        }


        void testEigenDataMappingTwoBytesUsingSharedPointCloud() {
            // Prepare constants to describe the PointCloud
            // stored in shared memory.
            const string NAME = "MySharedPointCloud";
            const uint32_t SIZE_PER_COMPONENT = sizeof(float);
            const uint8_t NUMBER_OF_COMPONENTS_PER_POINT = 4; // How many components do we have per vector?
            const uint32_t LENGTH = 3; // How many points (i.e. vectors with (x,y,z,intensity)) are stored in the shared memory segment?
            const uint32_t SIZE = LENGTH * SIZE_PER_COMPONENT; // What is the total size of the shared memory?

            try {
                // This pointer would need to be created once from the sender at startup.
                SharedPointer<SharedMemory> sharedMemory(SharedMemoryFactory::createSharedMemory(NAME, SIZE));
                Container toReceiver;
                // Sender side.
                {
                    if (sharedMemory->isValid()) {
                        {
                            // Using a scoped lock to lock and automatically unlock a shared memory segment.
                            odcore::base::Lock l(sharedMemory);
                            float *velodyneRawData = static_cast<float*>(sharedMemory->getSharedMemory());

                            // Alignment of Velodyne data: (x0, y0, z0, intensity0), (x1, y1, z1, intensity1), ...
                            // Add some example data.
                            velodyneRawData[0] = 1.1;
                            velodyneRawData[1] = 2.2;
                            velodyneRawData[2] = 3.3;
                            velodyneRawData[3] = 90.4;

                            velodyneRawData[4] = 4.5;
                            velodyneRawData[5] = 5.6;
                            velodyneRawData[6] = 6.7;
                            velodyneRawData[7] = 91.8;

                            velodyneRawData[8] = 7.9;
                            velodyneRawData[9] = 8.1;
                            velodyneRawData[10] = 9.2;
                            velodyneRawData[11] = 92.3;

                            cout << "Test 3" << endl;
                            for(unsigned int i = 0; i < LENGTH * NUMBER_OF_COMPONENTS_PER_POINT; i++) {
                                cout << (float) velodyneRawData[i] << " ";
                            }
                            cout << endl;

                            // Summarize meta-information about shared memory
                            // holding information about our point cloud.
                            SharedPointCloud spc;
                            spc.setName(NAME); // Name of the shared memory segment with the data.
                            spc.setSize(SIZE); // Size in raw bytes.
                            spc.setWidth(LENGTH); // Number of points.
                            spc.setHeight(1); // We have just a sequence of vectors.
                            spc.setNumberOfComponentsPerPoint(NUMBER_OF_COMPONENTS_PER_POINT);
                            spc.setComponentDataType(SharedPointCloud::FLOAT_T); // Data type per component.
                            spc.setUserInfo(SharedPointCloud::XYZ_INTENSITY);

                            // Prepare container for receiver.
                            toReceiver = Container(spc);
                            // In the real application, we would send the container
                            // using getConference().send(toReceiver);
                        }
                    }
                }


                // Receiver side.
                {
                    // Let's assume we have received the container
                    // (would typically happen via the ContainerConference).
                    Container fromSender = toReceiver;

                    // Is it from the correct type?
                    if (fromSender.getDataType() == SharedPointCloud::ID()) {
                        SharedPointCloud senderSharedPointCloud = fromSender.getData<SharedPointCloud>();
                        cout << senderSharedPointCloud.toString() << endl;

                        // Attach ourselves to the same shared memory segment (would be needed just once).
                        SharedPointer<SharedMemory> receiverSharedMemory(SharedMemoryFactory::attachToSharedMemory(senderSharedPointCloud.getName()));

                        if (receiverSharedMemory->isValid()) {
                            {
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

                                    // Setup the Eigen mapping, where
                                    // 4 == senderSharedPointCloud.getNumberOfComponentsPerPoint()
                                    // that cannot be dynamic due to Eigen's design of being a
                                    // compile-time library.
                                    typedef Map<Matrix<float, Dynamic, Dynamic>, 0, InnerStride<4> > Slice;
                                    Slice x((float*)velodyneRawData, senderSharedPointCloud.getWidth(), senderSharedPointCloud.getHeight());
                                    Slice y((float*)velodyneRawData+1, senderSharedPointCloud.getWidth(), senderSharedPointCloud.getHeight());
                                    Slice z((float*)velodyneRawData+2, senderSharedPointCloud.getWidth(), senderSharedPointCloud.getHeight());
                                    Slice intensity((float*)velodyneRawData+3, senderSharedPointCloud.getWidth(), senderSharedPointCloud.getHeight());

                                    cout << " ";
                                    for(unsigned int i = 0; i < senderSharedPointCloud.getWidth(); i++) {
                                        cout << "x = " << (float)x(i, 0)
                                             << ", y = " << (float)y(i, 0)
                                             << ", z = " << (float)z(i, 0)
                                             << ", intensity = " << (float)intensity(i, 0) << endl;
                                    }

                                    TS_ASSERT_DELTA(x(0,0), 1.1, 1e-1);
                                    TS_ASSERT_DELTA(y(0,0), 2.2, 1e-1);
                                    TS_ASSERT_DELTA(z(0,0), 3.3, 1e-1);
                                    TS_ASSERT_DELTA(intensity(0,0), 90.4, 1e-1);

                                    TS_ASSERT_DELTA(x(1,0), 4.5, 1e-1);
                                    TS_ASSERT_DELTA(y(1,0), 5.6, 1e-1);
                                    TS_ASSERT_DELTA(z(1,0), 6.7, 1e-1);
                                    TS_ASSERT_DELTA(intensity(1,0), 91.8, 1e-1);

                                    TS_ASSERT_DELTA(x(2,0), 7.9, 1e-1);
                                    TS_ASSERT_DELTA(y(2,0), 8.1, 1e-1);
                                    TS_ASSERT_DELTA(z(2,0), 9.2, 1e-1);
                                    TS_ASSERT_DELTA(intensity(2,0), 92.3, 1e-1);
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

#endif /*CORE_EIGENEXAMPLESTESTSUITE_H_*/
