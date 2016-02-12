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
# Enable the configuration of external projects.
INCLUDE (ExternalProject)

###########################################################################
# Include flags for compiling.
INCLUDE (CompileFlags)

###########################################################################
# Find and configure CxxTest.
INCLUDE (CheckCxxTestEnvironment)

###########################################################################
# Check for a working Java and ant environment.
INCLUDE (CheckJavaBuildEnvironment)

###########################################################################
# Check for the possibility to build .deb and .rpm packages.
INCLUDE (CheckBuildPackages)

###########################################################################
# Check for a working threading and potential realtime library environment.
FIND_PACKAGE (Threads REQUIRED)
FIND_PACKAGE (LibRT)

###########################################################################
# Find and configure OpenCV.
SET(OpenCV_DIR "/usr")
FIND_PACKAGE (OpenCV)

###########################################################################
# Find Boost (required for libodsimulation).
FIND_PACKAGE (Boost)

###########################################################################
# Find OpenGL (required for libodsimulation).
FIND_PACKAGE (OpenGL)

###########################################################################
# Find GLUT (required for libodsimulation).
FIND_PACKAGE (GLUT)

###########################################################################
# Find Qt (required for odcockpit).
FIND_PACKAGE (Qt4)

###########################################################################
# Find Qwt5Qt4 (required for odcockpit).
FIND_PACKAGE (Qwt5Qt4)

###########################################################################
# Find popt-dev (required for automotive/cantools).
FIND_PACKAGE (popt)

