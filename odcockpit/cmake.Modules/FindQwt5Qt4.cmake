# FindQwt5Qt4 - CMake script to find libqwt-qt4.
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

IF(NOT QWT5QT4_FOUND)
    FIND_PATH(QWT5QT4_INCLUDE_DIR qwt.h
        PATHS ${LIBQWT5QT4_PATH}/include
              /usr/local/include/
              /usr/include/
        PATH_SUFFIXES qwt qwt5 qwt-qt4 qwt5-qt4 ENV PATH
    )

    FIND_FILE(QWT5QT4_LIBRARIES
        NAMES libqwt-qt4.so
              libqwt5-qt4.so
              libqwt5.so
              libqwt.so
        PATHS ${LIBQWT5QT4_PATH}/lib/
              /usr/local/lib64/
              /usr/local/lib/
              /usr/lib/i386-linux-gnu/
              /usr/lib/x86_64-linux-gnu/
              /usr/lib64/
              /usr/lib/
              NO_DEFAULT_PATH
    )

    IF(QWT5QT4_INCLUDE_DIR AND QWT5QT4_LIBRARIES)
        SET (QWT5QT4_FOUND TRUE)
    ENDIF()

    IF(QWT5QT4_FOUND)
        MESSAGE(STATUS "Found qwt5-qt4 library: ${QWT5QT4_INCLUDE_DIR}, ${QWT5QT4_LIBRARIES}")
        SET (QWT5QT4_INCLUDE_DIRS ${QWT5QT4_INCLUDE_DIR})
    ELSE()
        IF(Qwt5Qt4_FIND_REQUIRED)
            MESSAGE(FATAL_ERROR "Could not find qwt5-qt4 library, try to setup LIBQWT5QT4_PATH accordingly.")
        ELSE()
            MESSAGE(STATUS "qwt5-qt4 library not found.")
        ENDIF()
    ENDIF()
ENDIF()
