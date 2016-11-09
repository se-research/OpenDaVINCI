# OpenDaVINCI-odvdrift - Integration of VDrift with OpenDaVINCI.
# Copyright (C) 2015  Christian Berger
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 3
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

PROJECT (odvdrift)

###########################################################################
# Set the search path for .cmake files.
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules" ${CMAKE_MODULE_PATH})

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
# Check for a working threading and potential realtime library environment.
FIND_PACKAGE (Threads REQUIRED)

###########################################################################
# Find OpenDaVINCI.
SET(OPENDAVINCI_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (OpenDaVINCI REQUIRED)

###########################################################################
# Find AutomotiveData.
SET(AUTOMOTIVEDATA_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (AutomotiveData REQUIRED)

###########################################################################
# Find OpenCV.
SET(OpenCV_DIR "/usr")
FIND_PACKAGE (OpenCV REQUIRED)

###########################################################################
# Find OpenDLV.
SET(OPENDLV_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (OpenDLV REQUIRED)

###########################################################################
# Find Bullet library.
FIND_PACKAGE (Bullet REQUIRED)

###########################################################################
# Find SDL library.
FIND_PACKAGE (SDL2 REQUIRED)

###########################################################################
# Find SDL_image library.
FIND_PACKAGE (SDL2_image REQUIRED)

###########################################################################
# Find OpenGL.
FIND_PACKAGE (OpenGL REQUIRED)

###########################################################################
# Find Curl.
FIND_PACKAGE (CURL REQUIRED)

###########################################################################
# Find VorbisFile.
FIND_PACKAGE (VorbisFile REQUIRED)

###########################################################################
# Set linking libraries to successfully link test suites and binaries.
SET (LIBRARIES ${OPENDAVINCI_LIBRARIES}
               ${AUTOMOTIVEDATA_LIBRARIES}
               ${OPENDLV_LIBRARIES}
               ${BULLET_LIBRARIES}
               ${SDL2_LIBRARY}
               ${SDL2_IMAGE_LIBRARY}
               ${OPENGL_gl_LIBRARY}
               ${CURL_LIBRARIES}
               ${VorbisFile_LIBRARIES})

###########################################################################
# Set header files from OpenDaVINCI.
INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS})
# Set header files from AutomotiveData.
INCLUDE_DIRECTORIES (${AUTOMOTIVEDATA_INCLUDE_DIRS})
# Set header files from OpenDLV.
INCLUDE_DIRECTORIES (${OPENDLV_INCLUDE_DIRS})
# Set header files from Bullet library.
INCLUDE_DIRECTORIES (${BULLET_INCLUDE_DIRS})
# Set header files from SDL library.
INCLUDE_DIRECTORIES (${SDL_INCLUDE_DIR})
# Set header files from SDL_image library.
INCLUDE_DIRECTORIES (${SDL_IMAGE_INCLUDE_DIRS})
# Set header files from OpenGL.
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
# Set header files from Curl.
INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIRS})
# Set header files from VorbisFile.
INCLUDE_DIRECTORIES(${VorbisFile_INCLUDE_DIRS})
# Set include directory.
INCLUDE_DIRECTORIES(src)

###########################################################################
# Build this project.
FILE(GLOB_RECURSE thisproject-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (${PROJECT_NAME}lib-static STATIC ${thisproject-sources})
ADD_EXECUTABLE (${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/apps/${PROJECT_NAME}.cpp")
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${PROJECT_NAME}lib-static ${LIBRARIES} ${OpenCV_LIBS}) 

###########################################################################
# Install this project.
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin COMPONENT odvdrift)
# This project does not have a manual page so far.
#INSTALL(FILES man/${PROJECT_NAME}.1 DESTINATION man/man1 COMPONENT odvdrift)

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
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "odvdrift combines the open source racing simulation VDrift with OpenDaVINCI.")
    SET(CPACK_PACKAGE_NAME "opendavinci")
    SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR}")
    SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR}")
    SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH}")
    SET(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
    SET(CPACK_COMPONENTS_ALL odvdrift)

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
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "opendavinci-odlib,odsimulation-odsimlib,libautomotivedata")

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
    SET(CPACK_RPM_PACKAGE_REQUIRES "opendavinci-odlib, odsimulation-odsimlib, libautomotivedata")

    # Resulting package name:
    SET(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${ARCH})
ENDIF()

INCLUDE(CPack)

