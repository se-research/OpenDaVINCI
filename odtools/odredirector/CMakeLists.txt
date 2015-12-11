# odredirector - Tool for dumping data to stdout or reading back from stdin
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

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (odredirector)

###########################################################################
# Set the search path for .cmake files.
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake.Modules" ${CMAKE_MODULE_PATH})

# Add a local CMake module search path dependent on the desired installation destination.
# Thus, artifacts from the complete source build can be given precendence over any installed versions.
IF(UNIX)
    SET (CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" ${CMAKE_MODULE_PATH})
ENDIF()
IF(WIN32)
    SET (CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/CMake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" ${CMAKE_MODULE_PATH})
ENDIF()

###########################################################################
# Include flags for compiling.
INCLUDE (CompileFlags)

###########################################################################
# Find and configure CxxTest.
SET (CXXTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../cxxtest") 
INCLUDE (CheckCxxTestEnvironment)

###########################################################################
# Find OpenDaVINCI.
SET(OPENDAVINCI_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (OpenDaVINCI REQUIRED)

###############################################################################
# Include directories for shipped 3rd party libraries.
SET(jpeg9a_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/jpeg-9a")

INCLUDE_DIRECTORIES (${jpeg9a_SOURCE_DIR})
SET (jpeg9a-headers
    ${jpeg9a_SOURCE_DIR}/cderror.h
    ${jpeg9a_SOURCE_DIR}/cdjpeg.h
    ${jpeg9a_SOURCE_DIR}/jconfig.h
    ${jpeg9a_SOURCE_DIR}/jdct.h
    ${jpeg9a_SOURCE_DIR}/jerror.h
    ${jpeg9a_SOURCE_DIR}/jinclude.h
    ${jpeg9a_SOURCE_DIR}/jmemsys.h
    ${jpeg9a_SOURCE_DIR}/jmorecfg.h
    ${jpeg9a_SOURCE_DIR}/jpegint.h
    ${jpeg9a_SOURCE_DIR}/jpeglib.h
    ${jpeg9a_SOURCE_DIR}/jversion.h
    ${jpeg9a_SOURCE_DIR}/transupp.h
)
SET (jpeg9a-sources
    ${jpeg9a_SOURCE_DIR}/jaricom.c
    ${jpeg9a_SOURCE_DIR}/jcapimin.c
    ${jpeg9a_SOURCE_DIR}/jcapistd.c
    ${jpeg9a_SOURCE_DIR}/jcarith.c
    ${jpeg9a_SOURCE_DIR}/jccoefct.c
    ${jpeg9a_SOURCE_DIR}/jccolor.c
    ${jpeg9a_SOURCE_DIR}/jcdctmgr.c
    ${jpeg9a_SOURCE_DIR}/jchuff.c
    ${jpeg9a_SOURCE_DIR}/jcinit.c
    ${jpeg9a_SOURCE_DIR}/jcmainct.c
    ${jpeg9a_SOURCE_DIR}/jcmarker.c
    ${jpeg9a_SOURCE_DIR}/jcmaster.c
    ${jpeg9a_SOURCE_DIR}/jcomapi.c
    ${jpeg9a_SOURCE_DIR}/jcparam.c
    ${jpeg9a_SOURCE_DIR}/jcprepct.c
    ${jpeg9a_SOURCE_DIR}/jcsample.c
    ${jpeg9a_SOURCE_DIR}/jctrans.c
    ${jpeg9a_SOURCE_DIR}/jdapimin.c
    ${jpeg9a_SOURCE_DIR}/jdapistd.c
    ${jpeg9a_SOURCE_DIR}/jdarith.c
    ${jpeg9a_SOURCE_DIR}/jdatadst.c
    ${jpeg9a_SOURCE_DIR}/jdatasrc.c
    ${jpeg9a_SOURCE_DIR}/jdcoefct.c
    ${jpeg9a_SOURCE_DIR}/jdcolor.c
    ${jpeg9a_SOURCE_DIR}/jddctmgr.c
    ${jpeg9a_SOURCE_DIR}/jdhuff.c
    ${jpeg9a_SOURCE_DIR}/jdinput.c
    ${jpeg9a_SOURCE_DIR}/jdmainct.c
    ${jpeg9a_SOURCE_DIR}/jdmarker.c
    ${jpeg9a_SOURCE_DIR}/jdmaster.c
    ${jpeg9a_SOURCE_DIR}/jdmerge.c
    ${jpeg9a_SOURCE_DIR}/jdpostct.c
    ${jpeg9a_SOURCE_DIR}/jdsample.c
    ${jpeg9a_SOURCE_DIR}/jdtrans.c
    ${jpeg9a_SOURCE_DIR}/jerror.c
    ${jpeg9a_SOURCE_DIR}/jfdctflt.c
    ${jpeg9a_SOURCE_DIR}/jfdctfst.c
    ${jpeg9a_SOURCE_DIR}/jfdctint.c
    ${jpeg9a_SOURCE_DIR}/jidctflt.c
    ${jpeg9a_SOURCE_DIR}/jidctfst.c
    ${jpeg9a_SOURCE_DIR}/jidctint.c
    ${jpeg9a_SOURCE_DIR}/jquant1.c
    ${jpeg9a_SOURCE_DIR}/jquant2.c
    ${jpeg9a_SOURCE_DIR}/jutils.c
    ${jpeg9a_SOURCE_DIR}/jmemmgr.c
    ${jpeg9a_SOURCE_DIR}/jmemnobs.c 
)

###############################################################################
# Set header files from OpenDaVINCI.
INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS}/opendavinci)
# Set header files from OpenDaVINCI (jpeg-9a).
INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS}/opendavinci/jpeg-9a)
# Set include directory.
INCLUDE_DIRECTORIES(include)

###############################################################################
# Build this project.
FILE(GLOB_RECURSE thisproject-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (${PROJECT_NAME}lib-static STATIC ${thisproject-sources} ${jpeg9a-sources})
ADD_EXECUTABLE (${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/apps/${PROJECT_NAME}.cpp")
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${PROJECT_NAME}lib-static ${OPENDAVINCI_LIBRARIES}) 

###############################################################################
# Enable CxxTest for all available testsuites.
IF(CXXTEST_FOUND)
    FILE(GLOB thisproject-testsuites "${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h")
    
    FOREACH(testsuite ${thisproject-testsuites})
        STRING(REPLACE "/" ";" testsuite-list ${testsuite})

        LIST(LENGTH testsuite-list len)
        MATH(EXPR lastItem "${len}-1")
        LIST(GET testsuite-list "${lastItem}" testsuite-short)

        SET(CXXTEST_TESTGEN_ARGS ${CXXTEST_TESTGEN_ARGS} --world=${PROJECT_NAME}-${testsuite-short})
        CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})
        IF(UNIX)        
            IF(   ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
               OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD")
               OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly") )
                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal -Wno-error=suggest-attribute=noreturn")
            ELSE()
                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal")
            ENDIF()
        ENDIF()
        IF(WIN32)
            SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "")
        ENDIF()
        SET_TESTS_PROPERTIES(${testsuite-short}-TestSuite PROPERTIES TIMEOUT 3000)
        TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite ${PROJECT_NAME}lib-static ${OPENDAVINCI_LIBRARIES})
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)

###############################################################################
# Install this project.
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin COMPONENT odtools)
INSTALL(FILES man/${PROJECT_NAME}.1 DESTINATION man/man1 COMPONENT odtools)

