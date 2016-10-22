How to read content from a zip file
"""""""""""""""""""""""""""""""""

OpenDaVINCI has a built-in function for decompressing zip files.

The sources for this example are available at
https://github.com/se-research/OpenDaVINCI/tree/master/tutorials/readzipfile

In order to read content from a zip file, you will find a simple example
below.

readzipfile.cpp:

.. code-block:: c++

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
        fstream fin("velodyneDataPoint.zip", ios::binary | ios::in);
        std::shared_ptr<odcore::wrapper::DecompressedData> dd = odcore::wrapper::CompressionFactory::getContents(fin);  //Decompress the zip file and use a shared pointer to point to the decompressed data
        fin.close();
        vector<string> entries = dd->getListOfEntries();
        //In this example, the decompressed data contains only one entry, which is the name of the csv file before compression
        //entries.at(0) returns the first entry
        cout<<"Number if entries: "<<entries.size()<<"; the name of the first entry: "<<entries.at(0)<<endl; 
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

This example reads a zip file ``velodyneDataPoint.zip`` which is original a csv file ``velodyneDataPoint.csv`` before compression. The csv file contains sample data of a 64-layer Velodyne sensor. It stores the x, y, z coordinate and intensity value of 10 points. Hence, the csv file has 11 rows (one row for each point plus the title row on top) and 4 columns (x, y, z, intensity). All values are represented by float numbers. 

To read content from a zip file, your application needs to include ``<opendavinci/odcore/wrapper/CompressionFactory.h>`` and ``<opendavinci/odcore/wrapper/DecompressedData.h>`` that encapsulate the platform-specific implementations.

``CompressionFactory`` provides a static method called ``getContents`` that allows you to decompress a zip file. To conveniently handle the resource management of releasing the acquired system resources, a ``std::shared_ptr`` is used that automatically releases memory that is no longer used.

A ``getListOfEntries`` method is used to return the list of entries in the decompressed data. A zip file containing multiple files has multiple entries, one entry for each file. ``velodyneDataPoint.zip`` contains 1 entry, which is the name of the csv file before compression: velodyneDataPoint.csv, which is returned by ``entries.at(0)`` in this example. Then ``getInputStreamFor(entries.at(0))`` prepares an input stream from the csv file to fill a buffer ``decompressedData`` that stores all the information of the csv file. ``decompressedData`` will be used to extract rows and columns from the csv file.

You can compile and link the example::

   g++ -std=c++11 -I /usr/include -c readzipfile.cpp -o readzipfile.o
   g++ -o readzipfile readzipfile.o -lopendavinci -lpthread
   
To test the program, run::

    $ ./readzipfile
    $
    
The x, y, z coordinate and intensity of the 10 points extracted from the csv file will be printed to the console::
    
    Number of entries: 1; the name of the first entry: velodyneDataPoint.csv
    Number of rows read: 89105
    x: 1.24821, y: 13.424, z: -1.52942, intensity: 22
    x: 0.851616, y: 14.2127, z: -1.54146, intensity: 28
    x: -0.777795, y: 18.337, z: 0.287256, intensity: 102
    x: -1.46898, y: 18.3918, z: 0.386122, intensity: 69
    x: 0.26113, y: 14.4262, z: -1.48172, intensity: 34
    x: -0.272345, y: 14.8803, z: -1.43373, intensity: 40
    x: 0.38511, y: 12.197, z: -1.66423, intensity: 32
    x: -0.0547113, y: 12.806, z: -1.67453, intensity: 27
    x: -0.86384, y: 15.1217, z: -1.37554, intensity: 37
    x: -1.45687, y: 15.7513, z: -1.34796, intensity: 44


