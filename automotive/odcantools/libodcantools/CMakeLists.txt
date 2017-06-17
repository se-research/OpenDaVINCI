# libodcantools - Library to wrap a CAN interface.
# Copyright (C) 2015 Christian Berger
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (libodcantools)

###########################################################################
# Set the search path for .cmake files.
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake.Modules" ${CMAKE_MODULE_PATH})

# Add a local CMake module search path dependent on the desired installation destination.
# Thus, artifacts from the complete source build can be given precendence over any installed versions.
IF(UNIX)
    SET (CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" ${CMAKE_MODULE_PATH})
ENDIF()
IF(WIN32)
    SET (CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/CMake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" ${CMAKE_MODULE_PATH})
ENDIF()

###########################################################################
# Include flags for compiling.
INCLUDE (CompileFlags)

###########################################################################
# Find and configure CxxTest.
SET (CXXTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../cxxtest") 
INCLUDE (CheckCxxTestEnvironment)

###########################################################################
# Find OpenDaVINCI.
SET(OPENDAVINCI_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (OpenDaVINCI REQUIRED)

###########################################################################
# Find AutomotiveData.
SET(AUTOMOTIVEDATA_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (AutomotiveData REQUIRED)

###############################################################################
# Set header files from OpenDaVINCI.
INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS})
# Set header files from AutomotiveData.
INCLUDE_DIRECTORIES (${AUTOMOTIVEDATA_INCLUDE_DIRS})
# Set include directory.
INCLUDE_DIRECTORIES(include)

###########################################################################
# Set linking libraries to successfully link test suites and binaries.
SET (LIBRARIES ${OPENDAVINCI_LIBRARIES}
               ${AUTOMOTIVEDATA_LIBRARIES})

###############################################################################
# Build this project.
FILE(GLOB_RECURSE thisproject-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

###############################################################################
# Resulting artifacts.
ADD_LIBRARY (odcantools-core   OBJECT ${thisproject-sources})
ADD_LIBRARY (odcantools-static STATIC $<TARGET_OBJECTS:odcantools-core>)
IF(NOT WIN32)
    ADD_LIBRARY (odcantools    SHARED $<TARGET_OBJECTS:odcantools-core>)
ENDIF()

TARGET_LINK_LIBRARIES(odcantools-static ${LIBRARIES})
IF(NOT WIN32)
    TARGET_LINK_LIBRARIES(odcantools    ${LIBRARIES})
ENDIF()

###############################################################################
# Enable CxxTest for all available testsuites.
IF(CXXTEST_FOUND)
    FILE(GLOB thisproject-testsuites "${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h")
    
    FOREACH(testsuite ${thisproject-testsuites})
        STRING(REPLACE "/" ";" testsuite-list ${testsuite})

        LIST(LENGTH testsuite-list len)
        MATH(EXPR lastItem "${len}-1")
        LIST(GET testsuite-list "${lastItem}" testsuite-short)

        SET(CXXTEST_TESTGEN_ARGS ${CXXTEST_TESTGEN_ARGS} --world=${PROJECT_NAME}-${testsuite-short})
        CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})
        IF(UNIX)
            IF( (   ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
                 OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD")
                 OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly") )
                AND (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") )
                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal -Wno-error=suggest-attribute=noreturn")
            ELSE()
                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal")
            ENDIF()
        ENDIF()
        IF(WIN32)
            SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "")
        ENDIF()
        SET_TESTS_PROPERTIES(${testsuite-short}-TestSuite PROPERTIES TIMEOUT 3000)
        TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite odcantools-static ${LIBRARIES})
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)

###############################################################################
# Install this project.
INSTALL(TARGETS odcantools-static DESTINATION lib COMPONENT odcantools)
IF(NOT WIN32)
    INSTALL(TARGETS odcantools    DESTINATION lib COMPONENT odcantools)
ENDIF()

# Install header files.
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION include/odcantools COMPONENT odcantools)

# Install CMake modules locally.
IF(UNIX)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../cmake.Modules/Findodcantools.cmake" DESTINATION share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules COMPONENT odcantools)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../cmake.Modules/Findodcantools.cmake" DESTINATION share/cmake-2.8/Modules COMPONENT odcantools)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../cmake.Modules/Findodcantools.cmake" DESTINATION share/cmake-3.0/Modules COMPONENT odcantools)
ENDIF()
IF(WIN32)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../cmake.Modules/Findodcantools.cmake" DESTINATION CMake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules COMPONENT odcantools)
ENDIF()

