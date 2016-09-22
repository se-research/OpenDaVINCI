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

#ifndef VELODYNE16TESTSUITE_H_
#define VELODYNE16TESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <cmath>
#include <memory>
#include <fstream>
#include <stdlib.h>

#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcore/wrapper/CompressionFactory.h"
#include "opendavinci/odcore/wrapper/DecompressedData.h"
#include "opendavinci/odcore/io/protocol/PCAPProtocol.h"
#include "automotivedata/generated/cartesian/Constants.h"
#include "velodyneListener16.h"

#define toRadian(x) ((x)*cartesian::Constants::PI/180.0)

long mSize=0;
float* segment; 
const uint32_t MAX_POINT_SIZE=125000;//The assumed max number of points per frame
const uint32_t SIZE_PER_COMPONENT = sizeof(float);
const uint8_t NUMBER_OF_COMPONENTS_PER_POINT = 4;
const uint32_t SIZE = MAX_POINT_SIZE * NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT;
const uint32_t BUFFER_SIZE=4000;

using namespace std;
using namespace odcore::base;
using namespace odcore::data;
using namespace odcore::data;
using namespace odcore::io::protocol;

using namespace automotive;
using namespace odcore::wrapper;

class velodyne16TestContainerListener : public odcore::io::conference::ContainerListener {
    public:
         velodyne16TestContainerListener():
         stopDecoding(false),
         pointIndex(0),
         startID(0),
         frameIndex(0),
         previousAzimuth(0.0),
         upperBlock(true),
         distance(0.0){

            //Create memory for temporary storage of point cloud data for each frame
            segment=(float*)malloc(SIZE);
            
            //Load calibration data from the calibration file
            string line;
            ifstream in("VLP-16.xml");
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
        
        ~velodyne16TestContainerListener(){
            free(segment);
        }
       
        virtual void nextContainer(odcore::data::Container &c) {
            if (c.getDataType() == odcore::data::pcap::GlobalHeader::ID()) {
                cout<<"Get the global header"<<endl;
            }
            if (c.getDataType() == odcore::data::pcap::PacketHeader::ID()) {
                //cout<<"Received a packet!"<<endl;
            }
            if (c.getDataType() == odcore::data::pcap::Packet::ID()) {
                // Here, we have a valid packet.
                //cout<<"Get a valid packet"<<endl;
                
                //Decode Velodyne data
                pcap::Packet packet = c.getData<pcap::Packet>();
                pcap::PacketHeader packetHeader = packet.getHeader();
                if(packetHeader.getIncl_len()==1248)
                {
                    if(stopDecoding)
                         return;

                    const string payload = packet.getPayload();
                    uint32_t position=42;//position specifies the starting position to read from the 1248 bytes, skip the 42-byte Ethernet header
                    //A packet consists of 12 blocks with 100 bytes each. Decode each block separately.
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
                        if(rotation<previousAzimuth){
                            if(frameIndex==1){
                                stopDecoding=true;
                                mSize=pointIndex;
                            }
                            frameIndex++;
                            pointIndex=0;
                            startID=0;
                        }
                        
                        previousAzimuth=rotation;
                        position+=4;
                        
                        if(pointIndex<MAX_POINT_SIZE){
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
                                xData=xyDistance*sin(toRadian(rotation-rotCorrection[sensorID]))
                                    -horizOffsetCorrection[sensorID]/100.0*cos(toRadian(rotation-rotCorrection[sensorID]));
                                yData=xyDistance*cos(toRadian(rotation-rotCorrection[sensorID]))
                                    +horizOffsetCorrection[sensorID]/100.0*sin(toRadian(rotation-rotCorrection[sensorID]));
                                zData=distance*sin(toRadian(vertCorrection[sensorID]))+vertOffsetCorrection[sensorID]/100.0;
                                //Decode intensity: 1 byte
                                int intensityInt=(unsigned int)(uint8_t)(payload.at(position+2));
                                intensity=(float)intensityInt;
                              
                                //Store coordinate information of each point to the malloc memory
                                if(!stopDecoding){
                                    segment[startID]=xData;
                                    segment[startID+1]=yData;
                                    segment[startID+2]=zData;
                                    segment[startID+3]=intensity;
                                }
                                
                                startID+=NUMBER_OF_COMPONENTS_PER_POINT;
                                position+=3;
                                pointIndex++;
                                if(pointIndex>=MAX_POINT_SIZE){
                                    position+=3*(31-counter);//Discard the points of the current frame when the preallocated shared memory is full; move the position to be read in the 1248 bytes
                                    break;
                                }
                            } 
                        }
                        else{
                            position+=96;//32*3
                        }
                    }
                }    
            }

        }
    private:
        float rotCorrection[64];
        float vertCorrection[64];
        float distCorrection[64];
        float vertOffsetCorrection[64];
        float horizOffsetCorrection[64]; 
        bool stopDecoding=false;//Stop decoding Velodyne packets       
        long pointIndex;
        int startID;
        long frameIndex;
        float previousAzimuth;
        bool upperBlock;
        float distance;
};

class velodyne16Test : public CxxTest::TestSuite {
    public:         
        void readCsvFile(){
            fstream fin("RevereFrame0.zip", ios::binary | ios::in);
            std::shared_ptr<odcore::wrapper::DecompressedData> dd = odcore::wrapper::CompressionFactory::getContents(fin);
            fin.close();
            vector<string> entries = dd->getListOfEntries();
            std::shared_ptr<istream> stream = dd->getInputStreamFor(entries.at(0));
            stringstream decompressedData;
            if(stream.get()){
                char c;
                while(stream->get(c)){
                    decompressedData<<c;
                }
            }
            string value;
            getline(decompressedData,value);
            while(getline(decompressedData,value)){
                stringstream lineStream(value);
                string cell;
                getline(lineStream,cell,',');
                xDataV.push_back(stof(cell));
                getline(lineStream,cell,',');
                yDataV.push_back(stof(cell));
                getline(lineStream,cell,',');
                zDataV.push_back(stof(cell));
                getline(lineStream,cell,',');
                intensityV.push_back(stof(cell));
            }
        }

        void testVelodyne16DecodingFromFile(){
            readCsvFile();
            mIndex=0;
            compare=0;
            velodyne16TestContainerListener ptcl;
            PCAPProtocol pcap;
            pcap.setContainerListener(&ptcl);

            fstream lidarStream("Revere.pcap", ios::binary|ios::in);
            char *buffer = new char[BUFFER_SIZE+1];
            while (lidarStream.good()) {
                lidarStream.read(buffer, BUFFER_SIZE * sizeof(char));
                string s(buffer,BUFFER_SIZE);
                pcap.nextString(s);
            }
            lidarStream.close();
            
            cout<<"File read complete."<<endl;
            delete [] buffer;
            
            cout<<"Before comparing:"<<compare<<","<<mIndex<<endl;
            for(unsigned long vCounter=0;vCounter<xDataV.size();vCounter++){
                for(long mCounter=mIndex;mCounter<mSize*4;mCounter+=4){
                    if((abs(segment[mCounter]-xDataV[vCounter])<0.1)&&((abs(segment[mCounter+1]-yDataV[vCounter]))<0.1)&&
                    ((abs(segment[mCounter+2]-zDataV[vCounter]))<0.1)&&((abs(segment[mCounter+3]-intensityV[vCounter]))<=1.0)){
                        compare++;
                        mIndex=mCounter+4;
                        break;
                    }      
                }
            }
            cout<<"Number of points from VeloView: "<<xDataV.size()<<endl;
            cout<<"Number of points matched from our Velodyne decoder: "<<compare<<endl;
            
            TS_ASSERT(compare==xDataV.size());//All points from VeloView must be included by the data from our Velodyne decoder
        }

private:
    vector<float> xDataV;
    vector<float> yDataV;
    vector<float> zDataV;
    vector<float> intensityV;
    long mIndex; 
    unsigned long compare;//Number of points matched between VeloView and our Velodyne decoder
};

#endif /*VELODYNE16TESTSUITE_H_*/
