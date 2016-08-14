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

PROJECT (BUILD_COMPLETE_SOURCE_TREE)

###########################################################################
# Set the search path for .cmake files.
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})

###########################################################################
# Check properties of the platform we are going to be compiled on.
SET (CXXTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cxxtest") 
INCLUDE (CheckPlatform)

###########################################################################
# Setting where to install the binaries.
SET(INSTALL_DIR ${CMAKE_INSTALL_PREFIX})

###########################################################################
# Display configuration.
MESSAGE("")
MESSAGE("Platform configuration for building the complete source tree:")

# First, display everything that is required to model and generate code from data structures.
IF("${ANT_EXECUTABLE}" STREQUAL "ANT_EXECUTABLE-NOTFOUND")
    # As we could not find ant, we cannot build odDataStructureGenerator-latest.jar from sources.
    SET(BUILD_ODDATASTRUCTUREGENERATOR 0)
    IF(${HAVE_JAVA})
        # Try to find the executable odDataStructureGenerator-latest.jar as fallback.
        INCLUDE(FindodDataStructureGenerator)
        IF(NOT ODDATASTRUCTUREGENERATOR_EXECUTABLE)
            MESSAGE(FATAL_ERROR "Could not find a working Java compiler and not ant build tool either. Please install odDataStructureGenerator-latest.jar from http://opendavinci.cse.chalmers.se/www to /usr/local/bin.")
        ELSE()
            MESSAGE(STATUS "Found ODDATASTRUCTUREGENERATOR executable: ${ODDATASTRUCTUREGENERATOR_EXECUTABLE}")
        ENDIF()
    ENDIF()
ELSE()
    IF(${HAVE_JAVAC})
        MESSAGE(STATUS "Found working Java compiler and ant build tool: Building odDataStructureGenerator")
        SET(BUILD_ODDATASTRUCTUREGENERATOR 1)
    ENDIF()
ENDIF()
SET(ODDATASTRUCTUREGENERATOR_EXECUTABLE ${INSTALL_DIR}/bin/odDataStructureGenerator-latest.jar)
MESSAGE(STATUS "Using ${ODDATASTRUCTUREGENERATOR_EXECUTABLE} to generate code from data structure models.")
SET(ODCANDATASTRUCTUREGENERATOR_EXECUTABLE ${INSTALL_DIR}/bin/odCANDataStructureGenerator-latest.jar)
MESSAGE(STATUS "Using ${ODCANDATASTRUCTUREGENERATOR_EXECUTABLE} to generate code from CAN data structure models.")

# Next, if we get here, we have all the requirements to to model and generate code from data structures.
IF(     NOT("${CMAKE_C_COMPILER}" STREQUAL "")
    AND NOT("${CMAKE_CXX_COMPILER}" STREQUAL "") )
    SET(BUILD_LIBOPENDLV 0)
    SET(BUILD_ODSIMULATION 0)
    SET(BUILD_ODCOCKPIT 0)
    SET(BUILD_AUTOMOTIVE_MINIATURE 0)
    SET(BUILD_AUTOMOTIVE_ODCANTOOLS 0)

    MESSAGE(STATUS "Found C and C++ compiler:   Building opendavinci-lib")
    SET(BUILD_OPENDAVINCI 1)

    MESSAGE(STATUS "Found C++ compiler:         Building opendavinci-odsupercomponent")
    SET(BUILD_ODSUPERCOMPONENT 1)

    MESSAGE(STATUS "Found C++ compiler:         Building opendavinci-odtools")
    SET(BUILD_ODTOOLS 1)

    MESSAGE(STATUS "Found C++ compiler:         Building automotivedata")
    SET(BUILD_AUTOMOTIVEDATA 1)

    MESSAGE(STATUS "Found C++ compiler:         Building ODVDCommaAI")
    SET(BUILD_ODVDCOMMAAI 1)
    MESSAGE(STATUS "Found C++ compiler:         Building ODVDOpenDLV")
    SET(BUILD_ODVDOPENDLV 1)

    MESSAGE(STATUS "Found C++ compiler:         Building opendavinci-tutorials")
    SET(BUILD_TUTORIALS 1)

    IF (OPENCV_FOUND)
        IF (    OPENGL_FOUND
            AND GLUT_FOUND
            AND Boost_FOUND)
            MESSAGE(STATUS "Found C++ compiler, OpenCV, OpenGL, GLUT, and Boost: Building libopendlv")
            SET(BUILD_LIBOPENDLV 1)

            MESSAGE(STATUS "Found C++ compiler, OpenCV, OpenGL, GLUT, and Boost: Building odsimulation")
            SET(BUILD_ODSIMULATION 1)

            MESSAGE(STATUS "Found C++ compiler, OpenCV, OpenGL, GLUT, and Boost: Building automotive/miniature")
            SET(BUILD_AUTOMOTIVE_MINIATURE 1)

            IF (Qt4_FOUND)
                IF (QWT5QT4_FOUND)
                    MESSAGE(STATUS "Found C++ compiler, OpenCV, OpenGL, GLUT, Boost, QT4, and Qwt: Building odcockpit")
                    SET(BUILD_ODCOCKPIT 1)
                ENDIF()
            ENDIF()
        ENDIF()
    ENDIF()

    IF(    (UNIX)
       AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly")
       AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD")
       AND (NOT ("${ARMHF}" STREQUAL "YES"))
       AND (NOT ("${i686}" STREQUAL "YES")) )
        IF(POPT_FOUND)
            MESSAGE(STATUS "Found popt-dev:             Building automotive/odcantools")
            SET(BUILD_AUTOMOTIVE_ODCANTOOLS 1)
        ENDIF()
    ENDIF()
ENDIF()

# Set parameters to ctest; for example, test cases are not executed on arm-hf cross compile build.
SET(CTEST_PARAMETERS "--output-on-failure") # Display output from a failing test case.
IF(     (UNIX)
    AND ("${ARMHF}" STREQUAL "YES") )
    SET(CTEST_PARAMETERS "--show-only") # Do not run test cases on arm-hf cross compile build.
ENDIF()
MESSAGE("Test command: \"${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}\"")

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

###########################################################################
IF(NOT("${CMAKE_TOOLCHAIN_FILE}" STREQUAL ""))
    SET(TOOLCHAIN_FILE "${CMAKE_TOOLCHAIN_FILE}")
ELSE()
    SET(TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/default-Toolchain.cmake")
ENDIF()
MESSAGE(STATUS "Using toolchain:            ${TOOLCHAIN_FILE}")

###########################################################################
MESSAGE(STATUS "Installing artifacts to:    ${INSTALL_DIR}")
MESSAGE("")

###########################################################################
# Next, all projects for a complete build of the sources tree are listed.

###########################################################################
# Build data structure generator.
IF(${BUILD_ODDATASTRUCTUREGENERATOR})
    ExternalProject_Add (odDataStructureGenerator
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odDataStructureGenerator"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odDataStructureGenerator-prefix/src/odDataStructureGenerator-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odDataStructureGenerator-prefix/src/odDataStructureGenerator-build --target ${MAKE_PACKAGE})
ENDIF()

# Next, build libopendavinci.
IF(${BUILD_OPENDAVINCI})
    ExternalProject_Add (libopendavinci
        DEPENDS odDataStructureGenerator
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libopendavinci"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/libopendavinci-prefix/src/libopendavinci-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/libopendavinci-prefix/src/libopendavinci-build --target ${MAKE_PACKAGE})

    # Build the reference projects in odDataStructureGenerator to check validity of the code generator.
    ExternalProject_Add (odDataStructureGenerator-reference
        DEPENDS libopendavinci
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odDataStructureGenerator/org.opendavinci.datamodel/test/odvd/reference"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND "")
ENDIF()

# Next, build tutorials.
IF(${BUILD_TUTORIALS})
    ExternalProject_Add (tutorials
        DEPENDS libopendavinci
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorials"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_COMMAND ""
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/tutorials-prefix/src/tutorials-build --target install)
ENDIF()

# Next, build odsupercomponent.
IF(${BUILD_ODSUPERCOMPONENT})
    ExternalProject_Add (odsupercomponent
        DEPENDS libopendavinci
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odsupercomponent"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odsupercomponent-prefix/src/odsupercomponent-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odsupercomponent-prefix/src/odsupercomponent-build --target ${MAKE_PACKAGE})
ENDIF()

# Next, build odtools.
IF(${BUILD_ODTOOLS})
    ExternalProject_Add (odtools
        DEPENDS libopendavinci
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odtools"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odtools-prefix/src/odtools-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odtools-prefix/src/odtools-build --target ${MAKE_PACKAGE})
ENDIF()

# Next, the project for the automotive data structures is built.
IF(${BUILD_AUTOMOTIVEDATA})
    # This "external project" simply deletes the existing libautomotivedata.
    ExternalProject_Add (libautomotivedata-cleanup
        DEPENDS libopendavinci
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/libautomotivedata
        PATCH_COMMAND ""
        SOURCE_DIR ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        TEST_COMMAND ""
        INSTALL_COMMAND "")

    ExternalProject_Add (libautomotivedata
        DEPENDS libautomotivedata-cleanup
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND cd ${CMAKE_CURRENT_BINARY_DIR} && ${Java_JAVA_EXECUTABLE} -jar ${ODDATASTRUCTUREGENERATOR_EXECUTABLE} --withCMake ${CMAKE_CURRENT_SOURCE_DIR}/AutomotiveData.odvd
        PATCH_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/libautomotivedata"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/libautomotivedata-prefix/src/libautomotivedata-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/libautomotivedata-prefix/src/libautomotivedata-build --target ${MAKE_PACKAGE})
ENDIF()

# Next, the project for the CommaAI data structures is built.
IF(${BUILD_ODVDCOMMAAI})
    # This "external project" simply deletes the existing libodvdcommaai.
    ExternalProject_Add (libodvdcommaai-cleanup
        DEPENDS libopendavinci
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/libodvdcommaai
        PATCH_COMMAND ""
        SOURCE_DIR ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        TEST_COMMAND ""
        INSTALL_COMMAND "")

    ExternalProject_Add (libodvdcommaai
        DEPENDS libodvdcommaai-cleanup
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND cd ${CMAKE_CURRENT_BINARY_DIR} && ${Java_JAVA_EXECUTABLE} -jar ${ODDATASTRUCTUREGENERATOR_EXECUTABLE} --withCMake ${CMAKE_CURRENT_SOURCE_DIR}/ODVDCommaAI.odvd
        PATCH_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/libodvdcommaai"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/libodvdcommaai-prefix/src/libodvdcommaai-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/libodvdcommaai-prefix/src/libodvdcommaai-build --target ${MAKE_PACKAGE})
ENDIF()

# Next, the project for the OpenDLV data structures is built.
IF(${BUILD_ODVDOPENDLV})
    # This "external project" simply deletes the existing libodvdopendlv.
    ExternalProject_Add (libodvdopendlv-cleanup
        DEPENDS libopendavinci
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/libodvdopendlv
        PATCH_COMMAND ""
        SOURCE_DIR ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        TEST_COMMAND ""
        INSTALL_COMMAND "")

    ExternalProject_Add (libodvdopendlv
        DEPENDS libodvdopendlv-cleanup
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND cd ${CMAKE_CURRENT_BINARY_DIR} && ${Java_JAVA_EXECUTABLE} -jar ${ODDATASTRUCTUREGENERATOR_EXECUTABLE} --withCMake ${CMAKE_CURRENT_SOURCE_DIR}/ODVDOpenDLV.odvd
        PATCH_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/libodvdopendlv"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/libodvdopendlv-prefix/src/libodvdopendlv-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/libodvdopendlv-prefix/src/libodvdopendlv-build --target ${MAKE_PACKAGE})
ENDIF()

# Next, build libopendlv.
IF(${BUILD_LIBOPENDLV})
    ExternalProject_Add (libopendlv
        DEPENDS libautomotivedata
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libopendlv"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/libopendlv-prefix/src/libopendlv-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/libopendlv-prefix/src/libopendlv-build --target ${MAKE_PACKAGE})
ENDIF()

# Next, build odsimulation.
IF(${BUILD_ODSIMULATION})
    ExternalProject_Add (odsimulation
        DEPENDS libopendlv
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odsimulation"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odsimulation-prefix/src/odsimulation-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odsimulation-prefix/src/odsimulation-build --target ${MAKE_PACKAGE})
ENDIF()

# Next, build odcockpit.
IF(${BUILD_ODCOCKPIT})
    ExternalProject_Add (odcockpit
        DEPENDS libopendlv
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odcockpit"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcockpit-prefix/src/odcockpit-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcockpit-prefix/src/odcockpit-build --target ${MAKE_PACKAGE})
ENDIF()

# Next, build automotive/odcantools.
IF(${BUILD_AUTOMOTIVE_ODCANTOOLS})
    ExternalProject_Add (automotive-odCANDataStructureGenerator
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/automotive/odCANDataStructureGenerator"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/automotive-odCANDataStructureGenerator-prefix/src/automotive-odCANDataStructureGenerator-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/automotive-odCANDataStructureGenerator-prefix/src/automotive-odCANDataStructureGenerator-build --target ${MAKE_PACKAGE})

    # This "external project" simply deletes the existing libcanmessagemapping.
    ExternalProject_Add (automotive-libcanmessagemapping-cleanup
        DEPENDS automotive-odCANDataStructureGenerator
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/libcanmessagemapping
        PATCH_COMMAND ""
        SOURCE_DIR ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        TEST_COMMAND ""
        INSTALL_COMMAND "")

    ExternalProject_Add (automotive-libcanmessagemapping
        DEPENDS libopendavinci libautomotivedata automotive-libcanmessagemapping-cleanup
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND cd ${CMAKE_CURRENT_BINARY_DIR} && ${Java_JAVA_EXECUTABLE} -jar ${ODCANDATASTRUCTUREGENERATOR_EXECUTABLE} --withCMake ${CMAKE_CURRENT_SOURCE_DIR}/automotive/CANMessageMapping.can
        PATCH_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/libcanmessagemapping"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/automotive-libcanmessagemapping-prefix/src/automotive-libcanmessagemapping-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/automotive-libcanmessagemapping-prefix/src/automotive-libcanmessagemapping-build --target ${MAKE_PACKAGE})

    ExternalProject_Add (automotive-odcantools
        DEPENDS automotive-libcanmessagemapping
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/automotive/odcantools"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/automotive-odcantools-prefix/src/automotive-odcantools-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/automotive-odcantools-prefix/src/automotive-odcantools-build --target ${MAKE_PACKAGE})
ENDIF()

# Next, build automotive/miniature.
IF(${BUILD_AUTOMOTIVE_MINIATURE})
    ExternalProject_Add (automotive-miniature
        DEPENDS libopendlv
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/automotive/miniature"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
        CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}"
        CMAKE_ARGS "-DCXXTEST_INCLUDE_DIR=${CXXTEST_INCLUDE_DIR}"
        TEST_BEFORE_INSTALL 1
        TEST_COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_PARAMETERS}
        INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/automotive-miniature-prefix/src/automotive-miniature-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/automotive-miniature-prefix/src/automotive-miniature-build --target ${MAKE_PACKAGE})
ENDIF()

