The following steps are covered in this manual:

- 0. Testing the current code
- A. Changing the grammar in the .xtext file (e.g., to add mathematical transformations)
- B. Changing the model transformation in the .xtend file
- C. Testing the resulting code


###STEP 0 - Testing the current code:

To test the current code, open Terminal, change directories to OpenDaVinci and run the following commands:

	$ cd automotive/
	$ rm -rf build 
	$ mkdir build && cd build
	$ cmake -D CMAKE_INSTALL_PREFIX=/opt/od ..
	$ make

######Note: *make* will build “odCANDataStructureGenerator” and then generate sources from “CANMessageMapping.can” in the “automotive/libcanmessagemapping” directory.


###STEP A - Changing the grammar (.xtext file):

1) Open Eclipse IDE;
2) Import org.opendavinci.candatamodel into Eclipse as an existing project (it is located in OpenDaVinci/automotive/odCANDataStructureGenerator/; 
3) Open the “CANDataModel.xtext” file by navigating to org.opendavinci.candatamodel/src/org.opendavinci/;
4) Make changes to the file and Save;
5) Right click on org.opendavinci/GenerateCANDataModel.mwe2 (in the navigation menu) and Run As MWE2 Workflow;
6) Right click on the root project and then select Refresh;
7) Build the Java code generator by opening Terminal and doing the following:

	$ cd OpenDaVinci/automotive/odCANDataStructureGenerator/org.opendavinci.candatamodel/
	$ ant -f ant-build.xml clean
	$ ant -f ant-build.xml
	
Then execute the code generator (it will use the “CANMessageMapping.can” file to generate its output)

	$ cd ../..
	$ java -jar odCANDataStructureGenerator/org.opendavinci.candatamodel/odCANDataStructureGenerator-latest.jar --withCMake CANMessageMapping.can


Alternatively to step 7, the complete automotive model can be build by following the procedures in STEP 0, with the same effect.
	


###STEP B - Changing the model transformation (.xtend file):

1) Open Eclipse IDE;
2) If it’s not imported yet, import org.opendavinci.candatamodel into Eclipse as an existing project (it is located in OpenDaVinci/automotive/odCANDataStructureGenerator/; 
3) Open “CANDataModelValidator.xtend” file by navigating to org.opendavinci.candatamodel/src/org.opendavinci/org.opendavinci..validation;
4) Make changes to the file and Save;
5) Build the Java code generator by opening Terminal and doing the following:

	$ cd OpenDaVinci/automotive/odCANDataStructureGenerator/org.opendavinci.candatamodel/
	$ ant -f ant-build.xml clean
	$ ant -f ant-build.xml
	
Then execute the code generator (it will use the “CANMessageMapping.can” file to generate its output)

	$ cd ../..
	$ java -jar odCANDataStructureGenerator/org.opendavinci.candatamodel/odCANDataStructureGenerator-latest.jar --withCMake CANMessageMapping.can


Alternatively to step 5, the complete automotive model can be build by following the procedures in STEP 0, with the same effect.


######Note: in the “.xtend” file, the text in grey background is reported verbatim in the generated files, while text in double angular brackets «...» is interpreted during the code generation, based on the input from the “.can” file.


###STEP C - Testing the result code:

	$ cd /opt/od/bin
	$ ./odsupercomponent --cid=111
	$ ./odcockpit --cid=111 

Then, start the LiveFeed plugin in odcockpit. 

Lastly:

IF you are connected to a real car, run:

	$ ./odcanproxy --cid=111

ELSE if you have recording files, run:

	$ ./odcanascreplay --cid=111 < OpenDaVINCI/automotive/odcantools/odcanascreplay/example/example.asc
	$ LD_LIBRARY_PATH=/opt/od/lib ./odcanmapper --cid=111

