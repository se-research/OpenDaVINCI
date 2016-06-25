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
            //packetNr(0),
            pointIndex(0),
            startID(0),
            frameIndex(0),
            previousAzimuth(0.0),
            upperBlock(true),
            distance(0.0),
            VelodyneSharedMemory(m),
            segment(NULL),
            velodyneFrame(c),
            spc(),
            stopReading(false){
                //Initial setup of the shared point cloud
                spc.setName(VelodyneSharedMemory->getName()); // Name of the shared memory segment with the data.
                //spc.setSize(pointIndex* NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT); // Size in raw bytes.
                //spc.setWidth(pointIndex); // Number of points.
                spc.setHeight(1); // We have just a sequence of vectors.
                spc.setNumberOfComponentsPerPoint(NUMBER_OF_COMPONENTS_PER_POINT);
                spc.setComponentDataType(SharedPointCloud::FLOAT_T); // Data type per component.
                spc.setUserInfo(SharedPointCloud::XYZ_INTENSITY);
                
                //Create memory for temporary storage of point cloud data for each frame
                segment=(float*)malloc(SIZE);
                
                //Load calibration data from the calibration file
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
                //packetNr++;
                //cout<<"Received "<<packetNr<<" packets!"<<endl;
            }
            if (c.getDataType() == odcore::data::pcap::Packet::ID()) {
                // Here, we have a valid packet.
                //cout<<"Get a valid packet"<<endl;
                
                //Decode Velodyne data
                pcap::Packet packet = c.getData<pcap::Packet>();
                pcap::PacketHeader packetHeader = packet.getHeader();
                if(packetHeader.getIncl_len()==1248)
                {

                    //TimeStamp decodeStart;
                    //TimeStamp packetReceiveTime;
                    //cout<<"Packet receive time: "<<packetReceiveTime.toMicroseconds()<<endl; 
                    
                    if(stopReading)
                         return;

                    const string payload = packet.getPayload();
                    uint32_t position=42;
                
                    //A packet consists of 12 blocks with 100 bytes each. Decode each block separately.
                    //int firstByte,secondByte,dataValue;
                    static int firstByte,secondByte,dataValue;
                    for(int index=0;index<12;index++)
                    {   
                        //Decode header information: 2 bytes                    
                        firstByte=(unsigned int)(uint8_t)(payload.at(position));
                        secondByte=(unsigned int)(uint8_t)(payload.at(position+1));
                        dataValue=ntohs(firstByte*256+secondByte);
                        if(dataValue==0xddff){
                            upperBlock=false;//Lower block
                        }
                        else{
                            upperBlock=true;//upper block
                        }

                        //Decode rotational information: 2 bytes
                        firstByte=(unsigned int)(uint8_t)(payload.at(position+2));
                        secondByte=(unsigned int)(uint8_t)(payload.at(position+3));
                        dataValue=ntohs(firstByte*256+secondByte);                        
                        float rotation=static_cast<float>(dataValue/100.0);
                        
                        //Update the shared point cloud when a complete scan is completed.
                        //Discard points when the preallocated shared memory is full.
                        if(rotation<previousAzimuth||pointIndex>MAX_POINT_SIZE){
                            Lock l(VelodyneSharedMemory);
                            memcpy(VelodyneSharedMemory->getSharedMemory(),segment,SIZE);
                            //spc.setName(VelodyneSharedMemory->getName()); // Name of the shared memory segment with the data.
                            spc.setSize(pointIndex* NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT); // Size in raw bytes.
                            spc.setWidth(pointIndex); // Number of points.
                            //spc.setHeight(1); // We have just a sequence of vectors.
                            //spc.setNumberOfComponentsPerPoint(NUMBER_OF_COMPONENTS_PER_POINT);
                            //spc.setComponentDataType(SharedPointCloud::FLOAT_T); // Data type per component.
                            //spc.setUserInfo(SharedPointCloud::XYZ_INTENSITY);
                            
                            Container imageFrame(spc);
                            velodyneFrame.send(imageFrame);
            
                            if(frameIndex>=LOAD_FRAME_NO){
                                stopReading=true;
                                cout<<"Stop reading"<<endl;
                            }
                            else{
                                frameIndex++;
                            }
                            //cout<<pointIndex<<endl;
                            pointIndex=0;
                            startID=0;
                        }
                        
                        previousAzimuth=rotation;
                        position+=4;

                        //Decode distance information and intensity of each sensor in a block       
                        for(int counter=0;counter<32;counter++)
                        {
                            //Decode distance: 2 bytes
                            static int sensorID(0);
                            if(upperBlock)
                                sensorID=counter;
                            else
                                sensorID=counter+32;
                            firstByte=(unsigned int)(uint8_t)(payload.at(position));
                            secondByte=(unsigned int)(uint8_t)(payload.at(position+1));
                            dataValue=ntohs(firstByte*256+secondByte);
                            distance=static_cast<float>(dataValue*0.2/100.0)+distCorrection[sensorID]/100.0;
                            static float xyDistance,xData,yData,zData,intensity;
                            xyDistance=distance*cos(toRadian(vertCorrection[sensorID]));
                            //float xData,yData,zData,intensity;
                            xData=xyDistance*sin(toRadian(rotation-rotCorrection[sensorID]))
                                -horizOffsetCorrection[sensorID]/100.0*cos(toRadian(rotation-rotCorrection[sensorID]));
                            yData=xyDistance*cos(toRadian(rotation-rotCorrection[sensorID]))
                                +horizOffsetCorrection[sensorID]/100.0*sin(toRadian(rotation-rotCorrection[sensorID]));
                            zData=distance*sin(toRadian(vertCorrection[sensorID]))+vertOffsetCorrection[sensorID]/100.0;
                            //Decode intensity: 1 byte
                            int intensityInt=(unsigned int)(uint8_t)(payload.at(position+2));
                            intensity=(float)intensityInt;
                          
                            //Store coordinate information of each point to the malloc memory
                            //long startID=NUMBER_OF_COMPONENTS_PER_POINT*pointIndex;
                            segment[startID]=xData;
                            segment[startID+1]=yData;
                            segment[startID+2]=zData;
                            segment[startID+3]=intensity;
                            
                            startID+=NUMBER_OF_COMPONENTS_PER_POINT;
                            position+=3;
                            pointIndex++;
                        } 
                    }
                }    
            }

    }    
    bool VelodyneListener::getStatus(){
        return stopReading;
    }
} // automotive

