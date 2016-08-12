# CANDataStructureGenerator - IDL tool to describe mapping from
#                             CAN data to high-level messages.
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

PROJECT (ODCANDATASTRUCTUREGENERATOR)

###########################################################################
# Set the search path for .cmake files.
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules" ${CMAKE_MODULE_PATH})

###########################################################################
# Add further .cmake files.
INCLUDE (ExternalProject)
INCLUDE (CheckJavaBuildEnvironment)

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

MESSAGE(STATUS "Installing artifacts to:    ${INSTALL_DIR}")
MESSAGE("")

###########################################################################
# As this project uses ant to build the binary, we simply delegate
# the actual compilation, test, and packaging to ant.
ExternalProject_Add (odCANDataStructureGenerator
    DOWNLOAD_COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/org.opendavinci.candatamodel ${CMAKE_BINARY_DIR}/org.opendavinci.candatamodel
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/org.opendavinci.candatamodel"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${ANT_EXECUTABLE} -lib lib -f ant-build.xml compile-java
    BUILD_IN_SOURCE 1
#    TEST_COMMAND ${ANT_EXECUTABLE} -lib lib -f ant-build.xml test-java
#    TEST_BEFORE_INSTALL 1
    TEST_COMMAND ""
    INSTALL_COMMAND ${ANT_EXECUTABLE} -lib lib -f ant-build.xml create-runnable-jar
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/org.opendavinci.candatamodel/odCANDataStructureGenerator-latest.jar ${CMAKE_BINARY_DIR})

# Install odCANDataStructureGenerator.
INSTALL(FILES "${CMAKE_BINARY_DIR}/odCANDataStructureGenerator-latest.jar" DESTINATION bin COMPONENT odCANDataStructureGenerator)

# Install CMake modules locally.
IF(UNIX)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindodCANDataStructureGenerator.cmake" DESTINATION share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules COMPONENT odCANDataStructureGenerator)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindodCANDataStructureGenerator.cmake" DESTINATION share/cmake-2.8/Modules COMPONENT odCANDataStructureGenerator)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindodCANDataStructureGenerator.cmake" DESTINATION share/cmake-3.0/Modules COMPONENT odCANDataStructureGenerator)
ENDIF()
IF(WIN32)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindodCANDataStructureGenerator.cmake" DESTINATION CMake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules COMPONENT odCANDataStructureGenerator)
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

IF(    (UNIX)
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly")
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "OpenBSD")
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "NetBSD") )
    SET(CPACK_GENERATOR "DEB;RPM")

    SET(CPACK_PACKAGE_CONTACT "Christian Berger")
    SET(CPACK_PACKAGE_VENDOR "${CPACK_PACKAGE_CONTACT}")
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "odCANDataStructureGenerator contains a runnable jar-archive to map low-level CAN data structures and to high-level messages to be used with OpenDaVINCI.")
    SET(CPACK_PACKAGE_NAME "opendavinci")
    SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR}")
    SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR}")
    SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH}")
    SET(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
    SET(CPACK_COMPONENTS_ALL odCANDataStructureGenerator)

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

    # Resulting package name:
    SET(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${ARCH})
ENDIF()

INCLUDE(CPack)

