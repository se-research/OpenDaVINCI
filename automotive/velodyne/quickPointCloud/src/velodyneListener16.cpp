/**
 * velodyneListener16 is used to decode VLP-16 data realized with OpenDaVINCI
 * Copyright (C) 2016 Hang Yin
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
#include <cstring>
#include <string>
#include <iostream>
//#include <memory>
#include <fstream>

#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/generated/odcore/data/pcap/GlobalHeader.h"
#include "opendavinci/generated/odcore/data/pcap/PacketHeader.h"
#include "opendavinci/generated/odcore/data/pcap/Packet.h"
//#include "opendavinci/odcore/base/Lock.h"

//#include "opendavinci/generated/odcore/data/SharedPointCloud.h"
#include "opendavinci/generated/odcore/data/QuickPointCloud.h"
//#include "opendavinci/odcore/wrapper/SharedMemory.h"
//#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"

#include "velodyneListener16.h"


#define toRadian(x) ((x)*cartesian::Constants::PI/180.0)

namespace automotive {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace automotive;
        using namespace odcore::wrapper;

        VelodyneListener16::VelodyneListener16(odcore::io::conference::ContainerConference& c):
            //packetNr(0),
            pointIndex(0),
            startID(0),
            frameIndex(0),
            previousAzimuth(0.0),
            deltaAzimuth(0.0),
            distance(0.0),
            velodyneFrame(c),
            stopReading(false),
            startAzimuth(0.0),
            distanceStringStream(""),
            isStartAzimuth(true){
            
            //Load calibration data from the calibration file
            //VLP-16 has 16 channels/sensors. Each sensor has a specific vertical angle, which can be read from
            //vertCorrection[sensor ID] specified in the calibration file.
            sensorOrderIndex[0]=0;
            sensorOrderIndex[1]=2;
            sensorOrderIndex[2]=4;
            sensorOrderIndex[3]=6;
            sensorOrderIndex[4]=8;
            sensorOrderIndex[5]=10;
            sensorOrderIndex[6]=12;
            sensorOrderIndex[7]=14;
            sensorOrderIndex[8]=1;
            sensorOrderIndex[9]=3;
            sensorOrderIndex[10]=5;
            sensorOrderIndex[11]=7;
            sensorOrderIndex[12]=9;
            sensorOrderIndex[13]=11;
            sensorOrderIndex[14]=13;
            sensorOrderIndex[15]=15;
            
            string line;
            ifstream in("VLP-16.xml");
            uint8_t counter=0;//corresponds to the index of the vertical angle of each beam
            bool found=false;

            while (getline(in,line) && counter<16)
            {
                string tmp; // strip whitespaces from the beginning
                for (uint8_t i = 0; i < line.length(); i++)
                {
                    
                    if ((line[i] == '\t' || line[i]==' ' )&& tmp.size() == 0)
                    {
                    }
                    else
                    {
                        if(line[i]=='<'){
                
                            if(found){
                                vertCorrection[counter]=atof(tmp.c_str());
                                
                                counter++;
                                found=false;
                                continue;
                            }
                            tmp += line[i];
                        }                   
                        else{
                            tmp += line[i];
                        }
                    }
        
                    if(tmp=="<vertCorrection_>"){
                        found=true;
                        tmp="";
                    }
                    else{
                    }
                }
            }
            /*for(uint8_t iii=0;iii<16;iii++){
                cout<<vertCorrection[iii]<<endl;
            }*/
        }            

        VelodyneListener16::~VelodyneListener16() {}
        
        //Update the shared point cloud when a complete scan is completed.
        void VelodyneListener16::sendQPC(const float &oldAzimuth, const float &newAzimuth){
            if(newAzimuth<oldAzimuth){
                //cout<<"startAzimuth:"<<startAzimuth<<",endAzimuth:"<<oldAzimuth<<", stringSize"<<distanceStringStream.str().size()<<endl;
                
                QuickPointCloud qpc(startAzimuth,oldAzimuth,entriesPerAzimuth,distanceStringStream.str());    
                Container c(qpc);
                velodyneFrame.send(c);
                
                //Stop reading the file after a predefined number of frames
                if(frameIndex>=LOAD_FRAME_NO){
                    stopReading=true;
                    cout<<"Stop reading"<<endl;
                }
                else{
                    frameIndex++;
                }
                pointIndex=0;
                startID=0;
                startAzimuth=newAzimuth;
                isStartAzimuth=false;
                distanceStringStream.str("");
            }
        }
        
        void VelodyneListener16::nextContainer(Container &c) {
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
                
                //Decode VLP-16 data
                pcap::Packet packet = c.getData<pcap::Packet>();
                pcap::PacketHeader packetHeader = packet.getHeader();
                if(packetHeader.getIncl_len()==1248)
                {
                    
                    if(stopReading)
                         return;

                    const string payload = packet.getPayload();
                    uint32_t position=42;//position specifies the starting position to read from the 1248 bytes, skip the 42-byte Ethernet header
                    
                    //A packet consists of 12 blocks with 100 bytes each. Decode each block separately.
                    static uint8_t firstByte,secondByte;
                    static uint32_t dataValue;
                    for(uint8_t blockID=0;blockID<12;blockID++)
                    {   
                        //Skip the flag: 0xFFEE(2 bytes)                    
                        position+=2;

                        //Decode azimuth information: 2 bytes. Swap the two bytes, change to decimal, and divide it by 100
                        firstByte=(uint8_t)(payload.at(position));
                        secondByte=(uint8_t)(payload.at(position+1));
                        dataValue=ntohs(firstByte*256+secondByte);                        
                        float azimuth=static_cast<float>(dataValue/100.0);
                        if(isStartAzimuth){
                            startAzimuth=azimuth;
                            isStartAzimuth=false;
                        }
                            
                        sendQPC(previousAzimuth,azimuth);
                        
                        previousAzimuth=azimuth;
                        position+=2;
                        
                        //Only decode the data if the maximum number of points of the current frame has not been reached
                        if(pointIndex<MAX_POINT_SIZE){
                            //Decode distance information and intensity of each beam/channel in a block, which contains two firing sequences       
                            for(int counter=0;counter<32;counter++)
                            {
                                //Interpolate azimuth value
                                if(counter==16){
                                    if(blockID<11){
                                        position+=50; //3*16+2, move the pointer to the azimuth bytes of the next data block
                                        firstByte=(uint8_t)(payload.at(position));
                                        secondByte=(uint8_t)(payload.at(position+1));
                                        dataValue=ntohs(firstByte*256+secondByte);                        
                                        float nextAzimuth=static_cast<float>(dataValue/100.0);
                                        position-=50; //reset pointer
                                        if(nextAzimuth<azimuth){
                                            nextAzimuth+=360.0;
                                        }
                                        deltaAzimuth=(nextAzimuth-azimuth)/2.0;
                                        azimuth+=deltaAzimuth;
                                    }
                                    else{
                                        azimuth+=deltaAzimuth;
                                    }
                                    if(azimuth>360.0){
                                        azimuth-=360.0;
                                    }
                                    
                                    sendQPC(previousAzimuth,azimuth);
                                    previousAzimuth=azimuth;
                                }
                                
                                uint8_t sensorID=counter;
                                if(counter>15){
                                    sensorID=counter-16;
                                }
                                //Decode distance: 2 bytes. Swap the bytes, change to decimal, and divide it by 500
                                firstByte=(uint8_t)(payload.at(position));
                                secondByte=(uint8_t)(payload.at(position+1));
                                dataValue=ntohs(firstByte*256+secondByte);
                                distance=dataValue/500.0; //*2mm-->/1000 for meter
                                ordered16Sensors[sensorID]=static_cast<half>(distance);
                                
                                if(sensorID==15){
                                    for(uint8_t index=0;index<16;index++){
                                        distanceStringStream.write((char*)(&ordered16Sensors[sensorOrderIndex[index]]),entriesPerAzimuth);
                                        /*if(frameIndex==1){
                                            cout<<ordered16Sensors[index]<<endl;
                                        }*/
                                    }
                                }

                                /*static float xyDistance,xData,yData,zData,intensity;
                                //Compute x, y, z cooridnate
                                xyDistance=distance*cos(toRadian(vertCorrection[sensorID]));
                                xData=xyDistance*sin(toRadian(azimuth));
                                yData=xyDistance*cos(toRadian(azimuth));
                                zData=distance*sin(toRadian(vertCorrection[sensorID]));
                              
                                //Store coordinate information of each point to the malloc memory
                                segment[startID]=xData;
                                segment[startID+1]=yData;
                                segment[startID+2]=zData; */                      
                                
                                pointIndex++;
                                startID+=NUMBER_OF_COMPONENTS_PER_POINT;
                                position+=3;
                                
                                if(pointIndex>=MAX_POINT_SIZE){
                                    position+=3*(31-counter);//Discard the points of the current frame when the preallocated shared memory is full; move the position to be read in the 1248 bytes
                                    //cout<<"Point overflow!"<<endl;
                                    break;
                                }
                            } 
                        }
                        else{
                            position+=96;//32*3(bytes), skip one block
                        }
                    }
                    //Ignore the last 6 bytes: 4 bytes timestamp and 2 factory bytes
                }    
            }

    }    
    bool VelodyneListener16::getStatus(){
        return stopReading;
    }
} // automotive

