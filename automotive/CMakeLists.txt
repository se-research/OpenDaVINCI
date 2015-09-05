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
# Setting where to install the binaries.
SET(INSTALL_DIR ${CMAKE_INSTALL_PREFIX})

###########################################################################
# Find and configure CxxTest.
SET (CXXTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../cxxtest") 
INCLUDE (CheckCxxTestEnvironment)

###########################################################################
# Download and build Peak Systems CAN driver and library.
IF(UNIX)
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
            BUILD_COMMAND make
            TEST_COMMAND ""
            INSTALL_COMMAND DESTDIR=${INSTALL_DIR} make install
        )

        ###########################################################################
        # Add subdirectories.
        ADD_SUBDIRECTORY (canproxy)
        ADD_SUBDIRECTORY (canmapper)
    ENDIF()
ENDIF()

