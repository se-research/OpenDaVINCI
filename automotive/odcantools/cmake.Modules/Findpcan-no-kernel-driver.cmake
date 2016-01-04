# Findpcan-no-kernel-driver.cmake - CMake module to find the pcan library (without Linux kernel drivers).
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

IF(NOT PCAN_NO_KERNEL_DRIVER_FOUND)
    FIND_PATH(PCAN_NO_KERNEL_DRIVER_INCLUDE_DIR
        NAMES libpcan.h
        PATHS ${LIBPCAN_NO_KERNEL_DRIVER_PATH_DIR}/include/
              /usr/local/include/
              /usr/include/
    )

    FIND_FILE(PCAN_NO_KERNEL_DRIVER_LIBRARIES libpcan-no-kernel-driver.so
        PATHS ${LIBPCAN_NO_KERNEL_DRIVER_PATH_DIR}/lib/
              /usr/local/lib64/
              /usr/local/lib/
              /usr/lib/i386-linux-gnu/
              /usr/lib/x86_64-linux-gnu/
              /usr/lib64/
              /usr/lib/
    )

    IF(PCAN_NO_KERNEL_DRIVER_INCLUDE_DIR AND PCAN_NO_KERNEL_DRIVER_LIBRARIES)
        SET (PCAN_NO_KERNEL_DRIVER_FOUND TRUE)
    ENDIF()

    IF(PCAN_NO_KERNEL_DRIVER_FOUND)
        MESSAGE(STATUS "Found libpcan-no-kernel-driver: ${PCAN_NO_KERNEL_DRIVER_INCLUDE_DIR}, ${PCAN_NO_KERNEL_DRIVER_LIBRARIES}")
    ELSE()
        IF(PCAN_NO_KERNEL_DRIVER_FIND_REQUIRED)
            MESSAGE(FATAL_ERROR "Could not find libpcan-no-kernel-driver, try to setup LIBPCAN_NO_KERNEL_DRIVER_PATH_DIR accordingly.")
        ELSE()
            MESSAGE(STATUS "libpcan-no-kernel-driver library not found.")
        ENDIF()
    ENDIF()
ENDIF()

