# CANDataStructureGenerator- IDL tool to describe exchangeable data.
# Copyright (C) 2014 - 2015  Christian Berger
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
# Try to find the executable odCANDataStructureGenerator-latest.jar.
#
# The user can specify an additional search path using the CMake variable
# ODCANDATASTRUCTUREGENERATOR_PATH

# First, search at the specific user path setting.
FIND_FILE(ODCANDATASTRUCTUREGENERATOR_EXECUTABLE
          NAMES odCANDataStructureGenerator-latest.jar
          PATHS ${ODCANDATASTRUCTUREGENERATOR_PATH}/bin
                ${ODCANDATASTRUCTUREGENERATOR_PATH}
          NO_DEFAULT_PATH)

# If not found, use the system's search paths.
IF(NOT ODCANDATASTRUCTUREGENERATOR_EXECUTABLE)
    FIND_FILE(ODCANDATASTRUCTUREGENERATOR_EXECUTABLE
              NAMES odCANDataStructureGenerator-latest.jar)
ENDIF()

MARK_AS_ADVANCED(ODCANDATASTRUCTUREGENERATOR_EXECUTABLE)

IF(NOT ODCANDATASTRUCTUREGENERATOR_EXECUTABLE)
    MESSAGE(FATAL_ERROR "Could not find odCANDataStructureGenerator executable to generate data structures.")
ELSE()
    MESSAGE(STATUS "Found odCANDataStructureGenerator executable: ${ODCANDATASTRUCTUREGENERATOR_EXECUTABLE}")
ENDIF()

