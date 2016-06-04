/**
 * velodyneListener is used to 
 *              decode Velodyne data realized
 *              with OpenDaVINCI
 * Copyright (C) 2015 Christian Berger and Hang Yin
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

#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>
//#include <memory>

#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
//#include "opendavinci/odcore/io/URL.h"
//#include "automotivedata/GeneratedHeaders_AutomotiveData.h"
#include "opendavinci/generated/odcore/data/pcap/GlobalHeader.h"
#include "opendavinci/generated/odcore/data/pcap/PacketHeader.h"
#include "opendavinci/generated/odcore/data/pcap/Packet.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/wrapper/Eigen.h"

#include "opendavinci/generated/odcore/data/SharedPointCloud.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"

#include "velodyneListener.h"

const float rotCorrection[64]={-5.3328056,-3.2344019,2.4376695,4.7373252,-1.0502493,1.2386309,-1.8405367,0.4511103,
                                3.2611551,5.4685535,2.4743285,4.7189918,-5.3511744,-3.1158857,-6.1270261,-3.852011,
                                -1.1109436,1.1519098,-1.8682934,0.43604341,3.1763444,5.4284201,2.4024715,4.6698937,
                                -5.3977456,-3.1504908,-6.1759849,-3.8819003,-1.1136208,1.0969903,-1.9088749,0.36758029,
                                -8.3386211,-4.7629819,4.1516571,7.3577185,-1.2630961,2.1595552,-2.6141083,0.95595688,
                                5.5369682,8.9712191,4.4757471,7.8848143,-8.0466499,-4.595552,-9.3918352,-5.9566336,
                                -1.3779737,2.0754263,-2.5654242,0.87227631,5.2989287,8.7970304,4.1742177,7.5869775,
                                -7.8831077,-4.5919614,-9.1805763,-5.7835727,-1.2335371,1.9424959,-2.5727935,0.81118912};
const float vertCorrection[64]={-7.2988362,-6.9644198,0.250889,0.55538797,-6.6410818,-6.2594609,-8.6656351,-8.3104696,
                                5.9352221,5.587399,-7.9891219,-7.644258,-3.2475569,-2.850472,-5.204318,-4.9137921,
                                -2.4998751,-2.184176,-4.5764661,-4.2038751,-1.798143,-1.49388,-1.877563,-3.492661,
                                0.88327599,1.234519,-1.177825,-0.86169797,1.585669,1.925001,-0.486963,-0.123898,
                                -22.597513,-22.397568,-11.576517,-10.877901,-21.935509,-21.409546,-25.066507,-24.458101,
                                -20.777454,-20.243195,-23.863358,-23.352007,-16.629311,-16.230633,-19.788239,-19.21587,
                                -15.754419,-15.166914,-18.828558,-18.312876,-14.641928,-14.048302,-17.687857,-17.16544,
                                -10.436752,-10.085198,-13.484814,-13.107666,-9.5621262,-9.0374413,-12.651329,-12.115005};
const float distCorrection[64]={111.0,146.0,131.76823,138.12656,119.0,135.0,132.0,145.0,
                                116.0,133.99889,117.0,145.0,118.71672,142.90839,120.0,137.0,
                                101.71324,145.31258,130.0,147.0,115.82812,146.0,129.29713,157.97737,
                                124.12312,128.0,133.0,130.0,131.0,131.0,138.48773,137.21994,
                                117.0,100.0,130.0,102.0,106.0,91.0,127.0,95.0,
                                106.0,97.0,115.0,92.0,135.0,108.0,135.0,98.0,
                                116.0,105.0,138.0,105.0,123.0,86.0,135.0,92.0,
                                121.0,103.0,146.0,99.0,123.0,106.0,134.0,104.0,};
const float vertOffsetCorrection[64]={19.736338,19.778963,20.688799,20.727015,19.82012,19.868624,19.561426,19.606993,
                                19.909781,19.953875,19.648148,19.692244,20.249313,20.29929,20.00238,20.039125,
                                20.343384,20.38307,20.081753,20.128786,20.431576,20.469791,20.169943,20.218447,
                                20.768169,20.812265,20.509478,20.549164,20.856361,20.898987,20.596197,20.641764,
                                10.828748,10.854152,12.142142,12.220895,10.912581,10.978632,10.508655,10.588678,
                                11.057385,11.123436,10.666161,10.732212,11.559117,11.606115,11.179325,11.249186,
                                11.662004,11.730595,11.296184,11.358424,11.791565,11.860156,11.433367,11.495607,
                                12.270433,12.30981,11.924937,11.968124,12.368239,12.426669,12.020203,12.081173};
const float horizOffsetCorrection[64]={2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999};

const float PI=3.1415926;
const std::string NAME = "VelodyneSharedPointCloud";
const std::string NAME2 = "PointCloudFrame";
const uint32_t MAX_POINT_SIZE=125000;
const uint8_t NUMBER_OF_COMPONENTS_PER_POINT = 4; // How many components do we have per vector?
const uint32_t SIZE_PER_COMPONENT = sizeof(float);
const uint32_t SIZE = MAX_POINT_SIZE * NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT; // What is the total size of the shared memory? 
#define toRadian(x) ((x)*PI/180.0)

namespace automotive {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace automotive;
        using namespace odcore::wrapper;

        VelodyneListener::VelodyneListener(std::shared_ptr<SharedMemory> m,
        odcore::io::conference::ContainerConference& c):
        //VelodyneListener::VelodyneListener():
            packetNr(0),
            pointIndex(0),
            frameIndex(0),
            previousAzimuth(0.00),
            upperBlock(true),
            VelodyneSharedMemory(m),
            velodyneFrame(c),
            spc(),
            stopReading(false){
                for(int iii=0;iii<200;iii++){
                //memcpy(frameStore[iii]->getSharedMemory(),m->getSharedMemory(),m->getSize());
                    //if(frameStore[iii]->isValid()){
                        //Lock l(frameStore[iii]);
                        frameStore[iii]=SharedMemoryFactory::createSharedMemory(NAME2+to_string(iii), SIZE);
                    /*}
                    else{
                        cout<<"Memory inialization failed."<<endl;
                        return;
                    }*/
                }
                //cout<<frameStore[10]->getName()<<endl;
                //memcpy(frameStore[0]->getSharedMemory(),m->getSharedMemory(),m->getSize());
            }
            

        VelodyneListener::~VelodyneListener() {}
        
        void VelodyneListener::nextContainer(Container &c) {
            if (c.getDataType() == odcore::data::pcap::GlobalHeader::ID()) {
                    cout<<"Get the global header"<<endl;
            }
            if (c.getDataType() == odcore::data::pcap::PacketHeader::ID()) {
                packetNr++;
                //cout<<"Received "<<packetNr<<" packets!"<<endl;
            }
            if (c.getDataType() == odcore::data::pcap::Packet::ID()) {
                // Here, we have a valid packet.
                //cout<<"Get a valid packet"<<endl;
                /*if(packetNr>=400)//We only store data from the first 400 packets
                {
                    cout<<"Enough!"<<endl;
                    cout<<"Frame:"<<frameIndex<<", Number of points: "<<pointIndex<<endl;
                    return;
                }*/
                //Decode Velodyne data
                pcap::Packet packet = c.getData<pcap::Packet>();
                pcap::PacketHeader packetHeader = packet.getHeader();
                if(packetHeader.getIncl_len()==1248)
                {

                    //TimeStamp decodeStart;
                    //TimeStamp packetReceiveTime;
                    //cout<<"Packet receive time: "<<packetReceiveTime.toMicroseconds()<<endl; 
                    if(!frameStore[frameIndex]->isValid()) return;
                    
                    if(frameIndex>200){
                        cout<<"Frame overflow!"<<endl;
                        return;
                    }
                    
                    // Using a scoped lock to lock and automatically unlock a shared memory segment.
                    odcore::base::Lock l(frameStore[frameIndex]);
                    float *velodyneRawData = static_cast<float*>(frameStore[frameIndex]->getSharedMemory());



                    const string payload = packet.getPayload();
                    string dataToDecode=payload.substr(42);
                
                    //A packet consists of 12 blocks with 100 bytes each. Decode each block separately.
                    int firstByte,secondByte,dataValue;
                    for(int index=0;index<12;index++)
                    {   
                        if(stopReading)
                            return;
                        //Decode header information: 2 bytes                    
                        firstByte=(unsigned int)(uint8_t)(dataToDecode.at(0));
                        secondByte=(unsigned int)(uint8_t)(dataToDecode.at(1));
                        dataValue=ntohs(firstByte*256+secondByte);
                        //cout<<"Sensor block ID: "<<hex<<dataValue<<endl;
                        if(dataValue==0xddff)
                        {
                            upperBlock=false;//Lower block
                        }
                        else
                        {
                            upperBlock=true;//upper block
                        }
                        dataToDecode=dataToDecode.substr(2);

                        //Decode rotational information: 2 bytes
                        firstByte=(unsigned int)(uint8_t)(dataToDecode.at(0));
                        secondByte=(unsigned int)(uint8_t)(dataToDecode.at(1));
                        dataValue=ntohs(firstByte*256+secondByte);                        
                        float rotation=static_cast<float>(dataValue/100.00);
                        //cout << "R = " << rotation << ", p = " << previousAzimuth << endl;
                        
                        if(rotation<previousAzimuth)
                        {
                            //if(frameIndex==1){
                                //SharedPointCloud spc;
                                //TimeStamp a;
                                /*spc.setName(NAME); // Name of the shared memory segment with the data.
                                spc.setSize(pointIndex* NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT); // Size in raw bytes.
                                spc.setWidth(pointIndex); // Number of points.
                                spc.setHeight(1); // We have just a sequence of vectors.
                                spc.setNumberOfComponentsPerPoint(NUMBER_OF_COMPONENTS_PER_POINT);
                                spc.setComponentDataType(SharedPointCloud::FLOAT_T); // Data type per component.
                                spc.setUserInfo(SharedPointCloud::XYZ_INTENSITY);*/
                                
                                //Container imageFrame(spc);
                                //velodyneFrame.send(imageFrame);
                                //sendSPC();
                                //TimeStamp b;
                                //cout<<(b-a).toMicroseconds()<<endl; 
                                
                                //stopReading=true;
                                //frameIndex++;
                                //pointIndex=0;
                            //}
                            
                            pointNumberPerFrame[frameIndex]=pointIndex;
                            cout<<"Load frame "<<frameIndex<<endl;
                            if(frameIndex>=45){
                                stopReading=true;
                            }
                            else{
                                frameIndex++;
                            }
                            pointIndex=0;
                            
                        }
                        
                        previousAzimuth=rotation;
                        dataToDecode=dataToDecode.substr(2);

                        //Decode distance information and intensity of each sensor in a block       
                        for(int counter=0;counter<32;counter++)
                        {
                            //Decode distance: 2 bytes
                            int sensorID(0);
                            if(upperBlock)
                                sensorID=counter;
                            else
                                sensorID=counter+32;
                            firstByte=(unsigned int)(uint8_t)(dataToDecode.at(0));
                            secondByte=(unsigned int)(uint8_t)(dataToDecode.at(1));
                            dataValue=ntohs(firstByte*256+secondByte);
                            distance[counter]=static_cast<float>(dataValue*0.200/100.000);
                                distance[counter]=distance[counter]+distCorrection[sensorID]/100;
                            float xyDistance=distance[counter]*cos(toRadian(vertCorrection[sensorID]));
                            float xData,yData,zData,intensity;
                            xData=xyDistance*sin(toRadian(rotation-rotCorrection[sensorID]))
                                -horizOffsetCorrection[sensorID]/100.0*cos(toRadian(rotation-rotCorrection[sensorID]));
                            yData=xyDistance*cos(toRadian(rotation-rotCorrection[sensorID]))
                                +horizOffsetCorrection[sensorID]/100.0*sin(toRadian(rotation-rotCorrection[sensorID]));
                            zData=distance[counter]*sin(toRadian(vertCorrection[sensorID]))+vertOffsetCorrection[sensorID]/100.0;
                            //Decode intensity: 1 byte
                            int intensityInt=(unsigned int)(uint8_t)(dataToDecode.at(2));
                            intensity=(float)intensityInt;

                            {                            
                                // Alignment of Velodyne data: (x0, y0, z0, intensity0), (x1, y1, z1, intensity1), ...
                                long startID=NUMBER_OF_COMPONENTS_PER_POINT*pointIndex;
                                velodyneRawData[startID]=xData;
                                velodyneRawData[startID+1]=yData;
                                velodyneRawData[startID+2]=zData;
                                velodyneRawData[startID+3]=intensity;
                                //(float)x(i, 0) = ValueForX, …
                            }
                            
                            dataToDecode=dataToDecode.substr(3);
                            pointIndex++;
                        } 
                    }
                //TimeStamp decodeEnd;
                //cout<<(decodeEnd-decodeStart).toMicroseconds()<<endl;   
                //TimeStamp packetDecodedTime;
                //cout<<"Packet decoded time: "<<packetDecodedTime.toMicroseconds()<<endl; 
                }    
            }

    }    
    
    void VelodyneListener::sendSPC(int frame){
        if(VelodyneSharedMemory->isValid() && frameStore[frame]->isValid())
        {
            Lock l1(VelodyneSharedMemory);
            Lock l2(frameStore[frame]);
            memcpy(VelodyneSharedMemory->getSharedMemory(),frameStore[frame]->getSharedMemory(),frameStore[frame]->getSize());
            //cout<<"Memory name:"<<VelodyneSharedMemory->getName()<<endl;
            //cout<<frameStore[frame]->getName()<<endl;
            spc.setName(VelodyneSharedMemory->getName()); // Name of the shared memory segment with the data.
            spc.setSize(pointNumberPerFrame[frame]* NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT); // Size in raw bytes.
            spc.setWidth(pointNumberPerFrame[frame]); // Number of points.
            spc.setHeight(1); // We have just a sequence of vectors.
            spc.setNumberOfComponentsPerPoint(NUMBER_OF_COMPONENTS_PER_POINT);
            spc.setComponentDataType(SharedPointCloud::FLOAT_T); // Data type per component.
            spc.setUserInfo(SharedPointCloud::XYZ_INTENSITY);
            
            Container imageFrame(spc);
            velodyneFrame.send(imageFrame);
        }
        else{
            cout<<"Memory copy failed."<<endl;
            return;
        }
    }
    
    bool VelodyneListener::getStatus(){
        return stopReading;
    }
    
    long VelodyneListener::getFrameIndex(){
        return frameIndex;
    }
    
} // automotive

