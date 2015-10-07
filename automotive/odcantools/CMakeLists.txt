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
SET (CXXTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../cxxtest") 
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
        UPDATE_COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/libsimple
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
# Download and build Peak Systems CAN driver and library.
IF(    (UNIX)
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly")
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD") )
    ###########################################################################
    # Find popt library.
    FIND_PACKAGE (popt REQUIRED)

    IF(POPT_FOUND)
        # This library requires "libpopt-dev" to be installed.
        ExternalProject_Add (peak-linux-driver
            URL http://www.peak-system.com/fileadmin/media/linux/files/peak-linux-driver-7.15.2.tar.gz
            UPDATE_COMMAND ""
            PATCH_COMMAND ""
            CONFIGURE_COMMAND ""
            BUILD_IN_SOURCE 1
            BUILD_COMMAND make NET=NO
            TEST_COMMAND ""
            INSTALL_COMMAND DESTDIR=${INSTALL_DIR} make install
        )

        ###########################################################################
        # Add subdirectories.
        ExternalProject_Add (odcanproxy
            DEPENDS peak-linux-driver
            DOWNLOAD_COMMAND ""
            UPDATE_COMMAND ""
            SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odcanproxy"
            CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
            TEST_BEFORE_INSTALL 1
            INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcanproxy-prefix/src/odcanproxy-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcanproxy-prefix/src/odcanproxy-build --target ${MAKE_PACKAGE})

        ExternalProject_Add (odcanascreplay
            DEPENDS libcanmessagemapping
            DOWNLOAD_COMMAND ""
            UPDATE_COMMAND ""
            SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odcanascreplay"
            CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
            TEST_BEFORE_INSTALL 1
            INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcanascreplay-prefix/src/odcanascreplay-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcanascreplay-prefix/src/odcanascreplay-build --target ${MAKE_PACKAGE})

        ExternalProject_Add (odcanmapper
            DEPENDS libcanmessagemapping
            DOWNLOAD_COMMAND ""
            UPDATE_COMMAND ""
            SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odcanmapper"
            CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
            TEST_BEFORE_INSTALL 1
            INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcanmapper-prefix/src/odcanmapper-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcanmapper-prefix/src/odcanmapper-build --target ${MAKE_PACKAGE})

#        ExternalProject_Add (odcanbridge
#            DEPENDS odcanproxy odcanmapper
#            DOWNLOAD_COMMAND ""
#            UPDATE_COMMAND ""
#            SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odcanbridge"
#            CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
#            TEST_BEFORE_INSTALL 1
#            INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcanbridge-prefix/src/odcanbridge-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcanbridge-prefix/src/odcanbridge-build --target ${MAKE_PACKAGE})

#        ExternalProject_Add (odcanproxymapper
#            DEPENDS odcanproxy odcanmapper
#            DOWNLOAD_COMMAND ""
#            UPDATE_COMMAND ""
#            SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/odcanbridge"
#            CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"
#            TEST_BEFORE_INSTALL 1
#            INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcanproxymapper-prefix/src/odcanproxymapper-build --target install COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/odcanproxymapper-prefix/src/odcanproxymapper-build --target ${MAKE_PACKAGE})
    ENDIF()
ENDIF()

###########################################################################
# Enable CPack to create .deb and .rpm.
#
# Read version from first line of ChangeLog
FILE (STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog" BUILD_NUMBER)
MACRO (setup_package_version_variables _packageName)
        STRING (REGEX MATCHALL "[0-9]+" _versionComponents "${_packageName}")
        LIST (LENGTH _versionComponents _len)
        IF (${_len} GREATER 0)
            LIST(GET _versionComponents 0 MAJOR)
        ENDIF()
        IF (${_len} GREATER 1)
            LIST(GET _versionComponents 1 MINOR)
        ENDIF()
        IF (${_len} GREATER 2)
            LIST(GET _versionComponents 2 PATCH)
        ENDIF()
ENDMACRO()
setup_package_version_variables(${BUILD_NUMBER})

IF(UNIX)
    SET(CPACK_GENERATOR "DEB;RPM")

    SET(CPACK_PACKAGE_CONTACT "Christian Berger")
    SET(CPACK_PACKAGE_VENDOR "${CPACK_PACKAGE_CONTACT}")
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "odcantools contains a set of commandline tools to handle CAN packages with OpenDaVINCI.")
    SET(CPACK_PACKAGE_NAME "opendavinci")
    SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR}")
    SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR}")
    SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH}")
    SET(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
    SET(CPACK_COMPONENTS_ALL odcantools)

    # Debian packages:
    SET(CPACK_DEBIAN_PACKAGE_SECTION "devel")
    SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
    IF("${ARMHF}" STREQUAL "YES")
        SET(ARCH "armhf")
    ELSE()
        IF("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
            SET(ARCH "amd64")
        ELSE()
            SET(ARCH "i386")
        ENDIF()
    ENDIF()
    SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${ARCH}")
    SET(CPACK_DEB_COMPONENT_INSTALL ON)
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "opendavinci-odlib,opendavinci-odsupercomponent")

    # RPM packages:
    IF("${ARMHF}" STREQUAL "YES")
        SET(ARCH "armhf")
    ELSE()
        IF("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
            SET(ARCH "x86_64")
        ELSE()
            SET(ARCH "i686")
        ENDIF()
    ENDIF()
    SET(CPACK_RPM_PACKAGE_BUILDARCH "Buildarch: ${CPACK_RPM_PACKAGE_ARCHITECTURE}")
    SET(CPACK_RPM_COMPONENT_INSTALL ON)
    SET(CPACK_RPM_PACKAGE_LICENSE "GPL")
    SET(CPACK_RPM_PACKAGE_REQUIRES "opendavinci-odlib,opendavinci-odsupercomponent")

    # Resulting package name:
    SET(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${ARCH})
ENDIF()

INCLUDE(CPack)

