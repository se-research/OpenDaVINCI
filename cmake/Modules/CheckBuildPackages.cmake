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
# Try to find dpkg to build .deb packages.
FIND_FILE(DPKG_EXECUTABLE NAMES dpkg)
MARK_AS_ADVANCED(DPKG_EXECUTABLE)

IF("${DPKG_EXECUTABLE}" STREQUAL "DPKG_EXECUTABLE-NOTFOUND")
    MESSAGE(WARNING "Could not find dpkg executable to create .deb packages.")
ELSE()
    MESSAGE(STATUS "Found dpkg executable: ${DPKG_EXECUTABLE}")
ENDIF()

###########################################################################
# Try to find rpmbuild to build .rpm packages.
FIND_FILE(RPMBUILD_EXECUTABLE NAMES rpmbuild)
MARK_AS_ADVANCED(RPMBUILD_EXECUTABLE)

IF("${RPMBUILD_EXECUTABLE}" STREQUAL "RPMBUILD_EXECUTABLE-NOTFOUND")
    MESSAGE(WARNING "Could not find rpmbuild executable to create .rpm packages.")
ELSE()
    MESSAGE(STATUS "Found rpmbuild executable: ${RPMBUILD_EXECUTABLE}")
ENDIF()

