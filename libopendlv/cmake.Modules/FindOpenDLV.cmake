# libopendlv - Portable toolkit for automotive applications
#              supporting simulation and visualization.
# Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
# Copyright (C) 2016 Christian Berger
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

###########################################################################
# Try to find OpenDLV library.
#
# The user can specify an additional search path using the CMake variable
# OPENDLV_DIR

# First, search at the specific user path setting.
IF(NOT ("${OPENDLV_DIR}" STREQUAL ""))
    FIND_PATH(OPENDLV_INCLUDE_DIR core/wrapper/HesperiaLibraries.h
                 NAMES opendlv
                 PATHS ${OPENDLV_DIR}/include
                 NO_DEFAULT_PATH)

    FIND_LIBRARY(OPENDLV_LIBRARY
                 NAMES opendlv
                 PATHS ${OPENDLV_DIR}/lib
                 NO_DEFAULT_PATH)

    FIND_LIBRARY(OPENDLV_LIBRARY_STATIC
                 NAMES opendlv-static
                 PATHS ${OPENDLV_DIR}/lib
                 NO_DEFAULT_PATH)
ENDIF()
IF(   ("${OPENDLV_INCLUDE_DIR}" STREQUAL "OPENDLV_INCLUDE_DIR-NOTFOUND")
   OR ("${OPENDLV_DIR}" STREQUAL "") )
    MESSAGE(STATUS "Trying to find OpenDLV library in default paths.")
    # If not found, use the system's search paths.
    FIND_PATH(OPENDLV_INCLUDE_DIR core/wrapper/HesperiaLibraries.h
                 NAMES opendlv
                 PATHS /usr/include
                       /usr/local/include)

    FIND_LIBRARY(OPENDLV_LIBRARY
                 NAMES opendlv
                 PATHS /usr/lib
                       /usr/lib64
                       /usr/local/lib
                       /usr/local/lib64)

    FIND_LIBRARY(OPENDLV_LIBRARY_STATIC
                 NAMES opendlv-static
                 PATHS /usr/lib
                       /usr/lib64
                       /usr/local/lib
                       /usr/local/lib64)
ENDIF()

IF("${OPENDLV_INCLUDE_DIR}" STREQUAL "")
    MESSAGE(FATAL_ERROR "Could not find OpenDLV library.")
ELSE()
    SET (FOUND_OPENDLV 1)
ENDIF()

###########################################################################
# Artifacts based on libopendlv need to link against OpenDaVINCI.
FIND_PACKAGE (OpenDaVINCI REQUIRED)

###########################################################################
# Find OpenGL.
FIND_PACKAGE (OpenGL REQUIRED)

###########################################################################
# Find GLUT.
FIND_PACKAGE (GLUT REQUIRED)

###########################################################################
# Find OpenCV.
SET(OPENCV_ROOT_DIR "/usr")
IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    SET(OPENCV_ROOT_DIR "/usr/local")
ENDIF()
FIND_PACKAGE (OpenCV REQUIRED)

###########################################################################
# Set linking libraries.
IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    SET(OPENDLV_LIBRARIES ${OPENDAVINCI_LIBRARIES}
                               ${OPENDLV_LIBRARY}
                               ${OPENGL_gl_LIBRARY}
                               ${OPENGL_glu_LIBRARY}
                               ${OPENCV_LIBRARIES}
                               ${GLUT_glut_LIBRARY}
                               /usr/X11/lib/libglut.3.dylib)
ELSE()
    SET(OPENDLV_LIBRARIES ${OPENDAVINCI_LIBRARIES}
                               ${OPENDLV_LIBRARY}
                               ${OPENGL_gl_LIBRARY}
                               ${OPENGL_glu_LIBRARY}
                               ${OPENCV_LIBRARIES}
                               ${GLUT_glut_LIBRARY})
    SET(OPENDLV_LIBRARIES_STATIC ${OPENDAVINCI_LIBRARIES_STATIC}
                               ${OPENDLV_LIBRARY_STATIC}
                               ${OPENGL_gl_LIBRARY}
                               ${OPENGL_glu_LIBRARY}
                               ${OPENCV_LIBRARIES}
                               ${GLUT_glut_LIBRARY})
ENDIF()

SET(OPENDLV_INCLUDE_DIRS ${OPENDLV_INCLUDE_DIR})

###########################################################################
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibOpenDLV DEFAULT_MSG
                                  OPENDLV_LIBRARY OPENDLV_INCLUDE_DIR)
MARK_AS_ADVANCED(OPENDLV_INCLUDE_DIR OPENDLV_LIBRARY)

