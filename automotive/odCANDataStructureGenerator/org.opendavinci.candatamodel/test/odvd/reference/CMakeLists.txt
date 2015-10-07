# DataStructureGenerator- IDL tool to describe exchangeable data.
# Copyright (C) 2014 - 2015 Christian Berger
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

PROJECT (odDataStructureGenerator_reference)

###########################################################################
# Set the search path for .cmake files.
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../cmake.Modules" ${CMAKE_MODULE_PATH})

###########################################################################
# Find and configure CxxTest.
SET (CXXTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../cxxtest") 
INCLUDE (CheckCxxTestEnvironment)

###########################################################################
# Add subdirectories.
ADD_SUBDIRECTORY(Test2_withCMake/libtest2)
ADD_SUBDIRECTORY(Test3_withCMake/libtest3)
ADD_SUBDIRECTORY(Test4_withCMake/libtest4)
ADD_SUBDIRECTORY(Test5_withCMake/libtest5)
ADD_SUBDIRECTORY(Test6_withCMake/libtest6)
ADD_SUBDIRECTORY(Test7_withCMake/libtest7)
ADD_SUBDIRECTORY(Test8_withCMake/libtest8)
ADD_SUBDIRECTORY(Test9_withCMake/libtest9)
ADD_SUBDIRECTORY(Test10_withCMake/libtest10)
ADD_SUBDIRECTORY(Test11_withCMake/libtest11)
ADD_SUBDIRECTORY(Test12_withCMake/libtest12)
ADD_SUBDIRECTORY(Test13_withCMake/libtest13)
ADD_SUBDIRECTORY(Test14_withCMake/libtest14)
ADD_SUBDIRECTORY(Test15_withCMake/libtest15)
ADD_SUBDIRECTORY(Test16_withCMake/libtest16)
ADD_SUBDIRECTORY(Test17_withCMake/libtest17)
ADD_SUBDIRECTORY(Test18_withCMake/libtest18)
ADD_SUBDIRECTORY(Test19_withCMake/libtest19)
ADD_SUBDIRECTORY(Test20_withCMake/libtest20)


