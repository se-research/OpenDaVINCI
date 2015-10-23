# odcantools - Tools and libraries to wrap CAN busses
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

###########################################################################
# Try to find odcantools library.
#
# The user can specify an additional search path using the CMake variable
# ODCANTOOLS_DIR

# First, search at the specific user path setting.
IF(NOT ("${ODCANTOOLS_DIR}" STREQUAL ""))
    FIND_PATH(ODCANTOOLS_INCLUDE_DIR CANDevice.h
                 NAMES odcantools
                 PATHS ${ODCANTOOLS_DIR}/include
                 NO_DEFAULT_PATH)

    FIND_LIBRARY(ODCANTOOLS_LIBRARY
                 NAMES odcantools odcantools-static
                 PATHS ${ODCANTOOLS_DIR}/lib
                 NO_DEFAULT_PATH)
ENDIF()
IF(   ("${ODCANTOOLS_INCLUDE_DIR}" STREQUAL "ODCANTOOLS_INCLUDE_DIR-NOTFOUND")
   OR ("${ODCANTOOLS_DIR}" STREQUAL "") )
    MESSAGE(STATUS "Trying to find odcantools library in default paths.")
    # If not found, use the system's search paths.
    FIND_PATH(ODCANTOOLS_INCLUDE_DIR CANDevice.h
                 NAMES odcantools
                 PATHS /usr/include
                       /usr/local/include)

    FIND_LIBRARY(ODCANTOOLS_LIBRARY
                 NAMES odcantools odcantools-static
                 PATHS /usr/lib
                       /usr/lib64
                       /usr/local/lib
                       /usr/local/lib64)
ENDIF()

IF("${ODCANTOOLS_INCLUDE_DIR}" STREQUAL "")
    MESSAGE(FATAL_ERROR "Could not find odcantools.")
ELSE()
    SET (FOUND_ODCANTOOLS 1)
ENDIF()

###########################################################################
# Artifacts based on libodsimulation need to link against OpenDaVINCI.
FIND_PACKAGE (OpenDaVINCI REQUIRED)

###########################################################################
# Find AutomotiveData.
FIND_PACKAGE (AutomotiveData REQUIRED)

###########################################################################
# Set linking libraries.
SET(ODCANTOOLS_LIBRARIES ${OPENDAVINCI_LIBRARIES}
                         ${AUTOMOTIVEDATA_LIBRARIES})
SET(ODCANTOOLS_INCLUDE_DIRS ${ODCANTOOLS_INCLUDE_DIR})

###########################################################################
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Libodcantools DEFAULT_MSG
                                  ODCANTOOLS_LIBRARY ODCANTOOLS_INCLUDE_DIR)
MARK_AS_ADVANCED(ODCANTOOLS_INCLUDE_DIR ODCANTOOLS_LIBRARY)

