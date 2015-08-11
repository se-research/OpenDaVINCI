# OpenDaVINCI - Portable middleware for distributed components.
# Copyright (C) 2008 - 2015  Christian Berger
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
# Try to find Java >=1.6.
FIND_PACKAGE(Java)
IF( NOT ( ((${Java_VERSION_MAJOR} GREATER 1) OR (${Java_VERSION_MAJOR} EQUAL 1))
      AND ((${Java_VERSION_MINOR} GREATER 6) OR (${Java_VERSION_MINOR} EQUAL 6)) ) )
    MESSAGE(FATAL_ERROR "At least Java 1.6 is required, found: Java ${Java_VERSION_MAJOR}.${Java_VERSION_MINOR}.")
ENDIF()

IF(NOT("${Java_JAVA_EXECUTABLE}" STREQUAL ""))
    SET(HAVE_JAVA "1")
ENDIF()

IF(NOT("${Java_JAVAC_EXECUTABLE}" STREQUAL ""))
    SET(HAVE_JAVAC "1")
ENDIF()

###########################################################################
# Try to find Ant to build odDataStructureGenerator.
FIND_FILE(ANT_EXECUTABLE NAMES ant)
MARK_AS_ADVANCED(ANT_EXECUTABLE)

IF(NOT ANT_EXECUTABLE)
    MESSAGE(WARNING "Could not find ant executable that is required to build odDataStructureGenerator from sources.")
ELSE()
    MESSAGE(STATUS "Found ant executable: ${ANT_EXECUTABLE}")
ENDIF()

