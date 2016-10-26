/**
 * OpenDaVINCI - Tutorial.
 * Copyright (C) 2016 Hang Yin
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

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <opendavinci/odcore/wrapper/CompressionFactory.h>
#include <opendavinci/odcore/wrapper/DecompressedData.h>

using namespace std;

int32_t main(int32_t argc, char **argv) {
    // Read a zip file in binary form. It is originally a csv file containing sample data of a 64-layer Velodyne sensor.
    //The csv file stores the data of 10 points, including the x, y, z coordinate and intensity value of each point. All values are represented by float numbers.
    fstream fin("../velodyneDataPoint.zip", ios::binary | ios::in);
    std::shared_ptr<odcore::wrapper::DecompressedData> dd = odcore::wrapper::CompressionFactory::getContents(fin);  //Decompress the zip file and use a shared pointer to point to the decompressed data
    fin.close();
    vector<string> entries = dd->getListOfEntries();
    //In this example, the decompressed data contains only one entry, which is the name of the csv file before compression
    //entries.at(0) returns the first entry
    cout<<"Number of entries: "<<entries.size()<<"; the name of the first entry: "<<entries.at(0)<<endl; 
    std::shared_ptr<istream> stream = dd->getInputStreamFor(entries.at(0));//Prepare an input stream from the csv file to fill a buffer
    stringstream decompressedData;  //a buffer storing all the information of the csv file
    if(stream.get()){
        char c;
        while(stream->get(c)){
            decompressedData<<c;  //Fill the buffer
        }
    }
    //Now decompressedData contains all the data from the original csv file. Use decompressedData to extract information from the csv file
    string value;
    getline(decompressedData,value); //Skip the title row of the csv file
    vector<float> xDataV;
    vector<float> yDataV;
    vector<float> zDataV;
    vector<float> intensityV;
    while(getline(decompressedData,value)){  //Read the csv file row by row
        stringstream lineStream(value);
        string cell;
        getline(lineStream,cell,',');  //Read the x, y, z coordinate and intensity of each point
        xDataV.push_back(stof(cell));
        getline(lineStream,cell,',');
        yDataV.push_back(stof(cell));
        getline(lineStream,cell,',');
        zDataV.push_back(stof(cell));
        getline(lineStream,cell,',');
        intensityV.push_back(stof(cell));
    }
    cout<<"Number of rows read: "<<xDataV.size()<<endl;  //Display the number of points extracted from the csv file
    for(uint32_t i=0;i<10;i++){
        cout<<"x: "<<xDataV[i]<<", y: "<<yDataV[i]<<", z: "<<zDataV[i]<<", intensity: "<<intensityV[i]<<endl;  //List the x, y, z coordinate and intensity of the 10 points
    }
}
