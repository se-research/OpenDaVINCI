# example-boxparker - Example for a simulation using
#                     libopendlv to realize an automated
#                     test for vehicle parking in a box.
# Copyright (C) 2012 - 2016  Christian Berger
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

PROJECT (example-boxparker)

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
# Find and configure CxxTest.
SET (CXXTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../cxxtest") 
INCLUDE (CheckCxxTestEnvironment)

###########################################################################
# Find OpenDaVINCI.
SET(OPENDAVINCI_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (OpenDaVINCI REQUIRED)

###########################################################################
# Find AutomotiveData.
SET(AUTOMOTIVEDATA_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (AutomotiveData REQUIRED)

###########################################################################
# Find OpenDLV.
SET(OPENDLV_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (OpenDLV REQUIRED)

###########################################################################
# Set linking libraries to successfully link simulations.
SET (LIBRARIES ${OPENDAVINCI_LIBRARIES}
               ${AUTOMOTIVEDATA_LIBRARIES}
               ${OPENDLV_LIBRARIES})

###########################################################################
# Set header files from OpenDaVINCI.
INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS})
# Set header files from AutomotiveData.
INCLUDE_DIRECTORIES (${AUTOMOTIVEDATA_INCLUDE_DIRS})
# Set header files from OpenDLV.
INCLUDE_DIRECTORIES (${OPENDLV_INCLUDE_DIRS})
# Set include directory.
INCLUDE_DIRECTORIES(include)

###########################################################################
# Set include directories and libaries for the systems-under-test.
SET (BOXPARKER boxparker)

INCLUDE_DIRECTORIES(../../${BOXPARKER}/include)

SET (BOXPARKER_LIB ${BOXPARKER}lib-static)
SET (LIBRARIES ${LIBRARIES} ${BOXPARKER_LIB})

###########################################################################
# Build this project.
FILE(GLOB_RECURSE thisproject-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (${PROJECT_NAME}lib-static STATIC ${thisproject-sources})
ADD_EXECUTABLE (${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/apps/${PROJECT_NAME}.cpp")
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${PROJECT_NAME}lib-static ${LIBRARIES}) 

###########################################################################
# Enable CxxTest for all available simulations to run simulation by
# executing make test.
#
# This custom command copies the "Parking_boxes.scnx" scenario to where
# the test suites are generated (more correctly to the parent folder) so
# that the test suite "ExampleDriverTestSuite2.h" can open it during
# exection.
ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Parking_boxes.scnx
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/resources/Parking_boxes.scnx ${CMAKE_BINARY_DIR}
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resources/Parking_boxes.scnx)
ADD_CUSTOM_TARGET(${PROJECT_NAME}-CopyScenarioForSimulations DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Parking_boxes.scnx)

# Here, the actual simulation runners are generated. Depending on the
# availability of libodsimulation, either all or only the ones that are
# not depending thereon are generated.
IF(CXXTEST_FOUND)
    FILE(GLOB thisproject-simulations "${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h")

    FOREACH(simulation ${thisproject-simulations})
        STRING(REPLACE "/" ";" simulation-list ${simulation})

        LIST(LENGTH simulation-list len)
        MATH(EXPR lastItem "${len}-1")
        LIST(GET simulation-list "${lastItem}" simulation-short)

        SET(CXXTEST_TESTGEN_ARGS ${CXXTEST_TESTGEN_ARGS} --world=${PROJECT_NAME}-${testsuite-short})
        CXXTEST_ADD_TEST(${simulation-short}-TestSuite ${simulation-short}-Simulation.cpp ${simulation})
        IF(UNIX)        
            IF(   ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
               OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD")
               OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly") )
                SET_SOURCE_FILES_PROPERTIES(${simulation-short}-Simulation.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal -Wno-error=suggest-attribute=noreturn")
            ELSE()
                SET_SOURCE_FILES_PROPERTIES(${simulation-short}-Simulation.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal")
            ENDIF()
        ENDIF()
        IF(WIN32)
            SET_SOURCE_FILES_PROPERTIES(${simulation-short}-Simulation.cpp PROPERTIES COMPILE_FLAGS "")
        ENDIF()

        SET_TESTS_PROPERTIES(${simulation-short}-TestSuite PROPERTIES TIMEOUT 3000)
        TARGET_LINK_LIBRARIES(${simulation-short}-TestSuite ${PROJECT_NAME}lib-static ${LIBRARIES})

        # For the test suites that use an SCNX scenario, we are additionally copying
        # the required scenarios to where the simulation runners are going to be executed.
        ADD_DEPENDENCIES(${simulation-short}-TestSuite ${PROJECT_NAME}-CopyScenarioForSimulations)
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)

###########################################################################
# This project will not be installed.

