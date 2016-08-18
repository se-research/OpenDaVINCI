# odrecorderh264 - Recorder library with encoding h264 video streams.
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
# Try to find odrecorderh264 library.
#
# The user can specify an additional search path using the CMake variable
# ODRECORDERH264_DIR

# First, search at the specific user path setting.
IF(NOT ("${ODRECORDERH264_DIR}" STREQUAL ""))
    FIND_PATH(ODRECORDERH264_INCLUDE_DIR RecorderH264.h
                 NAMES odrecorderh264
                 PATHS ${ODRECORDERH264_DIR}/include
                 NO_DEFAULT_PATH)

    FIND_LIBRARY(ODRECORDERH264_LIBRARY
                 NAMES odrecorderh264 odrecorderh264-static
                 PATHS ${ODRECORDERH264_DIR}/lib
                 NO_DEFAULT_PATH)
ENDIF()
IF(   ("${ODRECORDERH264_INCLUDE_DIR}" STREQUAL "ODRECORDERH264_INCLUDE_DIR-NOTFOUND")
   OR ("${ODRECORDERH264_DIR}" STREQUAL "") )
    MESSAGE(STATUS "Trying to find odrecorderh264 library in default paths.")
    # If not found, use the system's search paths.
    FIND_PATH(ODRECORDERH264_INCLUDE_DIR RecorderH264.h
                 NAMES odrecorderh264
                 PATHS /usr/include
                       /usr/local/include)

    FIND_LIBRARY(ODRECORDERH264_LIBRARY
                 NAMES odrecorderh264 odrecorderh264-static
                 PATHS /usr/lib
                       /usr/lib64
                       /usr/local/lib
                       /usr/local/lib64)
ENDIF()

IF("${ODRECORDERH264_INCLUDE_DIR}" STREQUAL "")
    MESSAGE(FATAL_ERROR "Could not find odrecorderh264 library.")
ELSE()
    SET (FOUND_ODRECORDERH264 1)
ENDIF()

###########################################################################
# Artifacts based on libopendlv need to link against OpenDaVINCI.
FIND_PACKAGE (OpenDaVINCI REQUIRED)

###########################################################################
# Find FFMPEG modules.
FIND_PACKAGE (FFMPEGMODULES REQUIRED)

###########################################################################
# Set linking libraries.
SET(ODRECORDERH264_LIBRARIES ${OPENDAVINCI_LIBRARIES}
                             ${ODRECORDERH264_LIBRARY}
                             ${FFMPEGMODULES_LIBRARIES})

SET(ODRECORDERH264_INCLUDE_DIRS ${ODRECORDERH264_INCLUDE_DIR})

###########################################################################
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Libodrecorderh264 DEFAULT_MSG
                                  ODRECORDERH264_LIBRARY ODRECORDERH264_INCLUDE_DIR)
MARK_AS_ADVANCED(ODRECORDERH264_INCLUDE_DIR ODRECORDERH264_LIBRARY)

