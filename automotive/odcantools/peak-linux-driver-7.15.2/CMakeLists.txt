# CMakeLists.txt for Peak Linux Driver (without Linux kernel driver).
# Copyright (C) 2016  Christian Berger
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

PROJECT (pcan-no-kernel-driver)

###############################################################################
# Set compile flags.
SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -fPIC -DNO_RT -Wall")

###############################################################################
# Include directories.
SET(kerneldriver_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/driver")
SET(userlib_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

INCLUDE_DIRECTORIES (${kerneldriver_SOURCE_DIR})
INCLUDE_DIRECTORIES (${userlib_SOURCE_DIR})
SET (userlib-sources
    ${userlib_SOURCE_DIR}/src/libpcan.c
)

###############################################################################
# Resulting artifacts.
ADD_LIBRARY (${PROJECT_NAME}-core OBJECT ${userlib-sources})
ADD_LIBRARY (${PROJECT_NAME}-static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}-core>)
IF(NOT WIN32)
    ADD_LIBRARY (${PROJECT_NAME}    SHARED $<TARGET_OBJECTS:${PROJECT_NAME}-core>)
ENDIF()

TARGET_LINK_LIBRARIES(${PROJECT_NAME}-static)
IF(NOT WIN32)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME})
ENDIF()

###############################################################################
# Install this project.
INSTALL(TARGETS ${PROJECT_NAME}-static DESTINATION lib COMPONENT odcantools)
IF(NOT WIN32)
    INSTALL(TARGETS ${PROJECT_NAME}    DESTINATION lib COMPONENT odcantools)
ENDIF()

# Install header files.
INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/driver/pcan.h" DESTINATION include/ COMPONENT odcantools)
INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/libpcan.h" DESTINATION include/ COMPONENT odcantools)

