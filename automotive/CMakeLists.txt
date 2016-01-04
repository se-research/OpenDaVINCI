# OpenDaVINCI - Portable middleware for distributed components.
# Copyright (C) 2015  Christian Berger
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

PROJECT (automotive)

###########################################################################
# Set the search path for .cmake files.
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules" ${CMAKE_MODULE_PATH})

###########################################################################
# Enable the configuration of external projects.
INCLUDE (ExternalProject)

###########################################################################
# Check for ant and Java.
INCLUDE (CheckJavaBuildEnvironment)

###########################################################################
# Check for the possibility to build .deb and .rpm packages.
INCLUDE (CheckBuildPackages)

###########################################################################
# Find and configure CxxTest.
SET (CXXTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../cxxtest") 
INCLUDE (CheckCxxTestEnvironment)

###########################################################################
# If dpkg and rpmbuild are available, .deb and .rpm packages will be
# created. Otherwise, the software is simply installed.
IF(     NOT("${DPKG_EXECUTABLE}" STREQUAL "DPKG_EXECUTABLE-NOTFOUND")
    AND NOT("${RPMBUILD_EXECUTABLE}" STREQUAL "RPMBUILD_EXECUTABLE-NOTFOUND") )
    MESSAGE(STATUS "Enabling building .deb and .rpm packages.")
    SET(MAKE_PACKAGE package)
ELSE()
    # If the platform does not provide dpkg and rpmbuild, make package is
    # replaced with make install.
    SET(MAKE_PACKAGE install)
ENDIF()
SET(MAKE_PACKAGE install)

###########################################################################
# Setting where to install the binaries.
SET(INSTALL_DIR ${CMAKE_INSTALL_PREFIX})

MESSAGE(STATUS "Installing artifacts to:    ${INSTALL_DIR}")
MESSAGE("")

###########################################################################
# First, display everything that is required to model and generate code from data structures.
SET(BUILD_ODCANDATASTRUCTUREGENERATOR 0)
IF(NOT("${ANT_EXECUTABLE}" STREQUAL "ANT_EXECUTABLE-NOTFOUND"))
    IF(${HAVE_JAVAC})
        MESSAGE(STATUS "Found working Java compiler and ant build tool: Building odCANDataStructureGenerator")
        SET(BUILD_ODCANDATASTRUCTUREGENERATOR 1)
    ENDIF()
ENDIF()
SET(ODCANDATASTRUCTUREGENERATOR_EXECUTABLE ${INSTALL_DIR}/bin/odCANDataStructureGenerator-latest.jar)
MESSAGE(STATUS "Using ${ODCANDATASTRUCTUREGENERATOR_EXECUTABLE} to generate code from CAN data structure models.")

###########################################################################
# Build odCANDataStructureGenerator.
IF(${BUILD_ODCANDATASTRUCTUREGENERATOR})
    ExternalProject_Add (odCANDataStructureGenerator
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odCANDataStructureGenerator"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odCANDataStructureGenerator-prefix/src/odCANDataStructureGenerator-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odCANDataStructureGenerator-prefix/src/odCANDataStructureGenerator-build --target ${MAKE_PACKAGE})

    # This "external project" simply deletes the existing libcanmessagemapping.
    ExternalProject_Add (libcanmessagemapping-cleanup
        DEPENDS odCANDataStructureGenerator
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/libcanmessagemapping
        PATCH_COMMAND ""
        SOURCE_DIR ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        TEST_COMMAND ""
        INSTALL_COMMAND "")

    ExternalProject_Add (libcanmessagemapping
        DEPENDS libcanmessagemapping-cleanup
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && ${Java_JAVA_EXECUTABLE} -jar ${ODCANDATASTRUCTUREGENERATOR_EXECUTABLE} --withCMake ${CMAKE_CURRENT_SOURCE_DIR}/CANMessageMapping.can
        PATCH_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libcanmessagemapping"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        TEST_BEFORE_INSTALL 1
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/libcanmessagemapping-prefix/src/libcanmessagemapping-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/libcanmessagemapping-prefix/src/libcanmessagemapping-build --target ${MAKE_PACKAGE})
ENDIF()

###########################################################################
# Download and build Peak Systems CAN driver and library on amd64.
IF(    (UNIX)
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly")
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD")
   AND (NOT ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")) ) # Do not build Peak driver on i386 systems.
    ###########################################################################
    # Find popt library.
    FIND_PACKAGE (popt REQUIRED)

    IF(POPT_FOUND)
        ###########################################################################
        # Add subdirectories.
        ExternalProject_Add (odcantools
            DEPENDS libcanmessagemapping
            DOWNLOAD_COMMAND ""
            UPDATE_COMMAND ""
            SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odcantools"
            CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
            TEST_BEFORE_INSTALL 1
            INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcantools-prefix/src/odcantools-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcantools-prefix/src/odcantools-build --target ${MAKE_PACKAGE})
    ENDIF()
ENDIF()

