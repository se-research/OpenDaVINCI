# testsuite - Sample application
# Copyright (C) 2015 Christian Berger
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (testsuite)

###########################################################################
# Add a local CMake module search path dependent on the desired installation destination.
# Thus, artifacts from the complete source build can be given precendence over any installed versions.
IF(UNIX)
    SET (CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" ${CMAKE_MODULE_PATH})
ENDIF()
IF(WIN32)
    SET (CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/CMake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" ${CMAKE_MODULE_PATH})
ENDIF()

###########################################################################
# Compile flags to enable C++11.
SET (CXX_OPTIONS       "-std=c++11")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC ${CXX_OPTIONS} -pipe")

###########################################################################
# Find Python to generate test runners.
FIND_PACKAGE (PythonInterp 2.7 REQUIRED)
IF(PYTHONINTERP_FOUND)
    SET (CXXTEST_USE_PYTHON true)
    SET (CXXTEST_TESTGEN_ARGS --xunit-printer --have-eh)
    SET (CXXTEST_PYTHON_INTERPRETER "${PYTHON_EXECUTABLE}")
ENDIF()

###########################################################################
# Next, find CxxTest (shipped with the distribution).
SET (CXXTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../cxxtest") 
FIND_PACKAGE(CxxTest)
IF(CXXTEST_FOUND)
    INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIRS})
    ENABLE_TESTING()
    MESSAGE(STATUS "Found CxxTest: Compiling and running test suites enabled.")
ENDIF(CXXTEST_FOUND)

###########################################################################
# Find OpenDaVINCI.
SET(OPENDAVINCI_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (OpenDaVINCI REQUIRED)

###############################################################################
# Set header files from OpenDaVINCI.
INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS})
# Set include directory.
INCLUDE_DIRECTORIES(include)

###############################################################################
# Build this project.
ADD_LIBRARY (ipcsharedmemorylib-static STATIC "ipcsharedmemory.cpp")
ADD_EXECUTABLE (ipcsharedmemory "ipcsharedmemorymain.cpp")
TARGET_LINK_LIBRARIES (ipcsharedmemory ipcsharedmemorylib-static ${OPENDAVINCI_LIBRARIES}) 

###############################################################################
# Add test cases.
IF(CXXTEST_FOUND)
    CXXTEST_ADD_TEST(ipcsharedmemorytestsuite ipcsharedmemorytestsuite.cpp "${CMAKE_CURRENT_SOURCE_DIR}/ipcsharedmemorytestsuite.h")
    TARGET_LINK_LIBRARIES(ipcsharedmemorytestsuite ipcsharedmemorylib-static ${OPENDAVINCI_LIBRARIES})
ENDIF()
###############################################################################
# Install this project.
INSTALL(TARGETS ipcsharedmemory RUNTIME DESTINATION bin COMPONENT tutorials)

