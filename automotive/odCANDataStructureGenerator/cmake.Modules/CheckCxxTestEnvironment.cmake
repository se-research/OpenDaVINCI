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

FIND_PACKAGE (PythonInterp REQUIRED)

IF(PYTHONINTERP_FOUND)
    SET (CXXTEST_USE_PYTHON true)
    SET (CXXTEST_TESTGEN_ARGS --xunit-printer --have-eh)
    SET (CXXTEST_PYTHON_INTERPRETER "${PYTHON_EXECUTABLE}")
ENDIF()

###########################################################################
# Next, find CxxTest (shipped with the distribution).
FIND_PACKAGE(CxxTest)
IF(CXXTEST_FOUND)
    INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIRS})
    ENABLE_TESTING()
    MESSAGE(STATUS "Found CxxTest: Compiling and running test suites enabled.")
ENDIF(CXXTEST_FOUND)

