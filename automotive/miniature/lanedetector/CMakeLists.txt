#
# Miniature smart vehicles.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (lanedetector)

# Add further modules to cmake.
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake.modules" ${CMAKE_MODULE_PATH})

# OpenCV libraries.
SET (OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)

# Add link libraries.
SET (LIBS ${OpenCV_LIBS} pthread rt)

# Find OpenDaVINCI.
FIND_PACKAGE(OpenDaVINCI REQUIRED)

# Find OpenDaVINCI/AutomotiveData.
FIND_PACKAGE(AutomotiveData REQUIRED)

# Include directories.
INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS}/opendavinci)
INCLUDE_DIRECTORIES (${AUTOMOTIVEDATA_INCLUDE_DIRS}/opendavinci/automotivedata)
INCLUDE_DIRECTORIES (include)

# Recipe for building "lanedetector".
FILE (GLOB_RECURSE lanedetector-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (lanedetectorlib STATIC ${lanedetector-sources})
ADD_EXECUTABLE (lanedetector "${CMAKE_CURRENT_SOURCE_DIR}/apps/MainModule.cpp")
TARGET_LINK_LIBRARIES (lanedetector lanedetectorlib ${OPENDAVINCI_LIBRARIES} ${AUTOMOTIVEDATA_LIBRARIES} ${LIBS}) 

