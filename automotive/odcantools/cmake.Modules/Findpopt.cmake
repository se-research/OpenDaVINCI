# Findpopt.cmake - CMake module to find popt library.
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

IF(NOT POPT_FOUND)
    FIND_PATH(POPT_INCLUDE_DIR
        NAMES popt.h
        PATHS ${LIBPOPT_PATH}/include/
              /usr/local/include/
              /usr/include/
    )

    FIND_FILE(POPT_LIBRARIES libpopt.so
        PATHS ${LIBPOPT_PATH}/lib/
              /usr/local/lib64/
              /usr/local/lib/
              /usr/lib/i386-linux-gnu/
              /usr/lib/x86_64-linux-gnu/
              /usr/lib64/
              /usr/lib/
    )

    IF(POPT_INCLUDE_DIR AND POPT_LIBRARIES)
        SET (POPT_FOUND TRUE)
    ENDIF()

    IF(POPT_FOUND)
        MESSAGE(STATUS "Found popt: ${POPT_INCLUDE_DIR}, ${POPT_LIBRARIES}")
    ELSE()
        IF(POPT_FIND_REQUIRED)
            MESSAGE(FATAL_ERROR "Could not find popt library, try to setup LIBPOPT_PATH accordingly.")
        ELSE()
            MESSAGE(STATUS "popt library not found.")
        ENDIF()
    ENDIF()
ENDIF()

