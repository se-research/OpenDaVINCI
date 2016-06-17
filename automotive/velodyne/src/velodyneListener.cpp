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
#include <memory>
#include<fstream>

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
#include "opendavinci/odcore/wrapper/SharedMemory.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"

#include "velodyneListener.h"


//const std::string NAME = "pointCloud";
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
            segment(NULL),
            velodyneFrame(c),
            spc(),
            stopReading(false){
                /*for(int iii=0;iii<READ_FRAME_NO;iii++){
                    segment[iii]=(float*)malloc(SIZE);
                }*/
                segment=(float*)malloc(SIZE);
                string line;
                ifstream in("db.xml");
                int counter[5]={0,0,0,0,0};//corresponds to the index of the five calibration values
	            bool found[5]={false, false, false, false, false};

                while (getline(in,line))
                {
		            string tmp; // strip whitespaces from the beginning
                    for (unsigned int i = 0; i < line.length(); i++)
                    {
                        
			            if ((line[i] == '\t' || line[i]==' ' )&& tmp.size() == 0)
                        {
                        }
                        else
                        {
                            if(line[i]=='<'){
					            if(found[0]){
						            rotCorrection[counter[0]]=atof(tmp.c_str());
						            counter[0]++;
						            found[0]=false;
						            continue;
					            }
					
					            if(found[1]){
						            vertCorrection[counter[1]]=atof(tmp.c_str());
						            counter[1]++;
						            found[1]=false;
						            continue;
					            }
					
					            if(found[2]){
						            distCorrection[counter[2]]=atof(tmp.c_str());
						            counter[2]++;
						            found[2]=false;
						            continue;
					            }
					
					            if(found[3]){
						            vertOffsetCorrection[counter[3]]=atof(tmp.c_str());
						            counter[3]++;
						            found[3]=false;
						            continue;
					            }
					
					            if(found[4]){
						            horizOffsetCorrection[counter[4]]=atof(tmp.c_str());
						            counter[4]++;
						            found[4]=false;
						            continue;
					            }
					            tmp += line[i];
				            }
				            else{
					            tmp += line[i];
				            }
                        }
			
			            if(tmp=="<rotCorrection_>"){
				            found[0]=true;
				            tmp="";
			            }
			            else if(tmp=="<vertCorrection_>"){
				            found[1]=true;
				            tmp="";
			            }
			            else if(tmp=="<distCorrection_>"){
				            found[2]=true;
				            tmp="";
			            }
			            else if(tmp=="<vertOffsetCorrection_>"){
				            found[3]=true;
				            tmp="";
			            }
			            else if(tmp=="<horizOffsetCorrection_>"){
				            found[4]=true;
				            tmp="";
			            }
			            else{
			            }
                    }
	            }
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
                    //if(!frameStore[frameIndex]->isValid()) return;
                    
                    /*if(frameIndex>200){
                        cout<<"Frame overflow!"<<endl;
                        return;
                    }*/
                    
                    if(stopReading)
                         return;
                    
                    // Using a scoped lock to lock and automatically unlock a shared memory segment.
                    //odcore::base::Lock l(frameStore[frameIndex]);
                    //float *velodyneRawData = static_cast<float*>(frameStore[frameIndex]->getSharedMemory());

                    const string payload = packet.getPayload();
                    string dataToDecode=payload.substr(42);
                
                    //A packet consists of 12 blocks with 100 bytes each. Decode each block separately.
                    int firstByte,secondByte,dataValue;
                    for(int index=0;index<12;index++)
                    {   
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
                            //pointNumberPerFrame[frameIndex]=pointIndex;
                            //cout<<"Load frame "<<frameIndex<<endl;
                            //sendSPC(frameIndex);
                            //cout<<"Packet number:"<<packetNr<<endl;
                            Lock l(VelodyneSharedMemory);
                            memcpy(VelodyneSharedMemory->getSharedMemory(),segment,SIZE);
                            spc.setName(VelodyneSharedMemory->getName()); // Name of the shared memory segment with the data.
                            spc.setSize(pointIndex* NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT); // Size in raw bytes.
                            spc.setWidth(pointIndex); // Number of points.
                            spc.setHeight(1); // We have just a sequence of vectors.
                            spc.setNumberOfComponentsPerPoint(NUMBER_OF_COMPONENTS_PER_POINT);
                            spc.setComponentDataType(SharedPointCloud::FLOAT_T); // Data type per component.
                            spc.setUserInfo(SharedPointCloud::XYZ_INTENSITY);
                            
                            Container imageFrame(spc);
                            velodyneFrame.send(imageFrame);
            
                            if(frameIndex>=LOAD_FRAME_NO){
                                stopReading=true;
                                cout<<"Stop reading"<<endl;
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
                                /*odcore::base::Lock l(VelodyneSharedMemory);
                                float *velodyneRawData = static_cast<float*>(VelodyneSharedMemory->getSharedMemory());
                                velodyneRawData[startID]=xData;
                                velodyneRawData[startID+1]=yData;
                                velodyneRawData[startID+2]=zData;
                                velodyneRawData[startID+3]=intensity;*/
                                segment[startID]=xData;
                                segment[startID+1]=yData;
                                segment[startID+2]=zData;
                                segment[startID+3]=intensity;
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
    bool VelodyneListener::getStatus(){
        return stopReading;
    }
} // automotive

