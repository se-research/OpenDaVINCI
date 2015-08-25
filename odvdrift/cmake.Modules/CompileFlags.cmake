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

IF(WIN32)
    ADD_DEFINITIONS(-DNOMINMAX)
ENDIF()

IF(UNIX)
    IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
        SET(CMAKE_MACOSX_RPATH 1)
    ENDIF()

    SET (CXX_OPTIONS "-std=c++11 -Wall -Wextra -O3 -pipe -D_REENTRANT")

    SET (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} " ")
    SET (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " ${CXX_OPTIONS}")
ENDIF()

