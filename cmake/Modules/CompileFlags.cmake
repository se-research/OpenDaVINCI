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

IF(WIN32)
    ADD_DEFINITIONS(-DNOMINMAX)
ENDIF()

IF(UNIX)
    IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
        SET(CMAKE_MACOSX_RPATH 1)
    ENDIF()

    SET (CXX_OPTIONS       "-Wno-deprecated -Wall -Werror -Wshadow -Wextra -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wpacked")
    SET (CXX_OPTION_ANSI   "-ansi")
    SET (CXX_EFFECTIVE_CXX "-Wmissing-format-attribute -Wredundant-decls -Wno-error=effc++ -Weffc++")
    
    SET (CXX_WARNING_ALL    "-Wctor-dtor-privacy -Wcast-align -Wchar-subscripts -Wcomment -Wdisabled-optimization -Wformat -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wfloat-equal -Winit-self -Winline -Winvalid-pch -Wlong-long -Wsign-compare -Wuninitialized -Wunreachable-code -Wunsafe-loop-optimizations -Wunused -Wunused-function -Wunused-label -Wunused-parameter -Wunused-but-set-parameter -Wunused-but-set-variable -Wunused-value -Wunused-variable -Wno-maybe-uninitialized -Wunused-result -Wmissing-braces -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wparentheses -Wsign-compare -Wswitch -Wuninitialized -Wunknown-pragmas -Wunreachable-code -Wtrigraphs  -Wvariadic-macros -Wvolatile-register-var -Wwrite-strings -Wpointer-arith -Wredundant-decls -Wreturn-type -Wsequence-point -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wsync-nand -Wsuggest-attribute=const -Warray-bounds -Wtrampolines -Wlogical-op -Wnormalized=nfc -Wvarargs -Wvector-operation-performance -Wvla -Wtype-limits -Wc++11-compat -Woverloaded-virtual")

    # Remove "-ansi" flag for clang on Darwin.
    IF(    (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin") 
       AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD")
       AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "NetBSD")
       AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly") )
        SET (CXX_OPTIONS "${CXX_OPTIONS} ${CXX_OPTION_ANSI}")
    ENDIF()

    # Additionally, test for Effective C++ warnings except on OpenBSD.
    IF(NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "OpenBSD")
        SET (CXX_OPTIONS "${CXX_OPTIONS} ${CXX_EFFECTIVE_CXX}")

        # Remove "-Wno-maybe-uninitialized -Wno-error=unused-result" flag on FreeBSD and MacOSX or where the GCC is not 4.7+
        IF(    (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
           AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "NetBSD")
           AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD")
           AND (NOT "${ARMHF}" STREQUAL "YES") )

            # Check for GCC version.
            EXECUTE_PROCESS(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)

            IF (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
                SET (CXX_OPTIONS "${CXX_OPTIONS} ${CXX_WARNING_ALL}")
            ENDIF()
        ENDIF()
    ENDIF()

    SET (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} " -fPIC")
    SET (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -fPIC ${CXX_OPTIONS} -pipe")
ENDIF()

