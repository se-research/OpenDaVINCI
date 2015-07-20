#
# Miniature smart vehicles.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (boxparker)

# Add further modules to cmake.
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake.modules" ${CMAKE_MODULE_PATH})

# Add link libraries.
SET (LIBS pthread rt)

# Find OpenDaVINCI.
FIND_PACKAGE(OpenDaVINCI REQUIRED)

# Find OpenDaVINCI/AutomotiveData.
FIND_PACKAGE(AutomotiveData REQUIRED)

# Include directories.
INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS}/opendavinci)
INCLUDE_DIRECTORIES (${AUTOMOTIVEDATA_INCLUDE_DIRS}/opendavinci/automotivedata)
INCLUDE_DIRECTORIES (include)

# Recipe for building "boxparker".
FILE (GLOB_RECURSE boxparker-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (boxparkerlib STATIC ${boxparker-sources})
ADD_EXECUTABLE (boxparker "${CMAKE_CURRENT_SOURCE_DIR}/apps/MainModule.cpp")
TARGET_LINK_LIBRARIES (boxparker boxparkerlib ${OPENDAVINCI_LIBRARIES} ${AUTOMOTIVEDATA_LIBRARIES} ${LIBS}) 

