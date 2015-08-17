# libodsimulation - Portable simulation and visualization libary
# Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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
# Try to find odSimulation library.
#
# The user can specify an additional search path using the CMake variable
# ODSIMULATION_DIR

# First, search at the specific user path setting.
IF(NOT ("${ODSIMULATION_DIR}" STREQUAL ""))
    FIND_PATH(ODSIMULATION_INCLUDE_DIR core/wrapper/HesperiaLibraries.h
                 NAMES odsimulation
                 PATHS ${ODSIMULATION_DIR}/include
                 NO_DEFAULT_PATH)

    FIND_LIBRARY(ODSIMULATION_LIBRARY
                 NAMES odsimulation odsimulation-static
                 PATHS ${ODSIMULATION_DIR}/lib
                 NO_DEFAULT_PATH)
ENDIF()
IF(   ("${ODSIMULATION_INCLUDE_DIR}" STREQUAL "ODSIMULATION_INCLUDE_DIR-NOTFOUND")
   OR ("${ODSIMULATION_DIR}" STREQUAL "") )
    MESSAGE(STATUS "Trying to find odSimulation library in default paths.")
    # If not found, use the system's search paths.
    FIND_PATH(ODSIMULATION_INCLUDE_DIR core/wrapper/HesperiaLibraries.h
                 NAMES odsimulation
                 PATHS /usr/include
                       /usr/local/include)

    FIND_LIBRARY(ODSIMULATION_LIBRARY
                 NAMES odsimulation odsimulation-static
                 PATHS /usr/lib
                       /usr/lib64
                       /usr/local/lib
                       /usr/local/lib64)
ENDIF()

IF("${ODSIMULATION_INCLUDE_DIR}" STREQUAL "")
    MESSAGE(FATAL_ERROR "Could not find odSimulation library.")
ELSE()
    SET (FOUND_ODSIMULATION 1)
ENDIF()

###########################################################################
# Artifacts based on libodsimulation need to link against OpenDaVINCI.
FIND_PACKAGE (OpenDaVINCI REQUIRED)

###########################################################################
# Find OpenGL.
FIND_PACKAGE (OpenGL REQUIRED)

###########################################################################
# Find GLUT.
FIND_PACKAGE (GLUT REQUIRED)

###########################################################################
# Set linking libraries.
SET(ODSIMULATION_LIBRARIES ${OPENDAVINCI_LIBRARIES}
                           ${ODSIMULATION_LIBRARY}
                           ${OPENGL_gl_LIBRARY}
                           ${OPENGL_glu_LIBRARY}
                           ${GLUT_glut_LIBRARY})
SET(ODSIMULATION_INCLUDE_DIRS ${ODSIMULATION_INCLUDE_DIR})

###########################################################################
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibodSimulation DEFAULT_MSG
                                  ODSIMULATION_LIBRARY ODSIMULATION_INCLUDE_DIR)
MARK_AS_ADVANCED(ODSIMULATION_INCLUDE_DIR ODSIMULATION_LIBRARY)

