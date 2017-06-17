# odcockpit - odcockpit is visualization tool for distributed
#             software systems realized with OpenDaVINCI
# Copyright (C) 2008 - 2015  Christian Berger, Bernhard Rumpe
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

PROJECT (odcockpit)

###########################################################################
# Set the search path for .cmake files.
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules" ${CMAKE_MODULE_PATH})

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
SET (CXXTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../cxxtest")
INCLUDE (CheckCxxTestEnvironment)

###########################################################################
# Find OpenDaVINCI.
SET(OPENDAVINCI_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (OpenDaVINCI REQUIRED)

###########################################################################
# Find AutomotiveData.
SET(AUTOMOTIVEDATA_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (AutomotiveData REQUIRED)

###########################################################################
# Find ODVDOpenDLV.
SET(ODVDOPENDLV_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (ODVDOpenDLV REQUIRED)

###########################################################################
# Find OpenDLV.
SET(OPENDLV_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (OpenDLV REQUIRED)

###########################################################################
# Find odplayerh264.
SET(ODPLAYERH264_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (odplayerh264)

###########################################################################
# Find Qt.
FIND_PACKAGE(Qt4 4.0.0 REQUIRED QtCore QtGui QtOpenGL QtNetwork)
INCLUDE (${QT_USE_FILE})

###########################################################################
# Find Qwt5-Qt4.
FIND_PACKAGE (Qwt5Qt4)

###########################################################################
# Set linking libraries to successfully link test suites and binaries.
# Adjust compile flags on Mac OS
IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    SET (CMAKE_CXX_FLAGS " -O2 -std=c++11 -Wall -Wextra -Weffc++")
ENDIF()

SET (LIBRARIES ${OPENDAVINCI_LIBRARIES}
               ${AUTOMOTIVEDATA_LIBRARIES}
               ${OPENDLV_LIBRARIES}
               ${QT_LIBRARIES}
               ${ODVDOPENDLV_LIBRARIES})

IF(QWT5QT4_FOUND)
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_QWT5QT4")
    SET (LIBRARIES ${LIBRARIES}
                   ${QWT5QT4_LIBRARIES})
ENDIF()

IF(ODPLAYERH264_FOUND)
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_ODPLAYERH264")
    SET (LIBRARIES ${LIBRARIES}
                   ${ODPLAYERH264_LIBRARIES})
    INCLUDE_DIRECTORIES (${ODPLAYERH264_INCLUDE_DIRS})
ENDIF()

###########################################################################
# Set header files from OpenDaVINCI.
INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS})
# Set header files from AutomotiveData.
INCLUDE_DIRECTORIES (${AUTOMOTIVEDATA_INCLUDE_DIRS})
# Set header files from ODVDOpenDLV.
INCLUDE_DIRECTORIES (${ODVDOPENDLV_INCLUDE_DIRS})
# Set header files from OpenDLV.
INCLUDE_DIRECTORIES (${OPENDLV_INCLUDE_DIRS})
# Set header files from Qwt5-Qt4.
IF(QWT5QT4_FOUND)
    # Marking this with SYSTEM tells CMake to count this as a system library.
    # Used to suppress warnings from Qwt5-Qt4.
    INCLUDE_DIRECTORIES (SYSTEM ${QWT5QT4_INCLUDE_DIRS})
ENDIF()
# Set include directory.
INCLUDE_DIRECTORIES(include)

###########################################################################
# Build this project.
FILE(GLOB_RECURSE thisproject-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

IF(NOT QWT5QT4_FOUND)
    # Exclude all sources that use libqwt5qt4 if it is not present.
    FOREACH(item ${thisproject-sources})
      IF(${item} MATCHES "LoadPlot.cpp")
        LIST(REMOVE_ITEM thisproject-sources ${item})
      ENDIF()
      IF(${item} MATCHES "LoadPerModule.cpp")
        LIST(REMOVE_ITEM thisproject-sources ${item})
      ENDIF()
      IF(${item} MATCHES "ModuleStatisticsViewerPlugIn.cpp")
        LIST(REMOVE_ITEM thisproject-sources ${item})
      ENDIF()
      IF(${item} MATCHES "ModuleStatisticsViewerWidget.cpp")
        LIST(REMOVE_ITEM thisproject-sources ${item})
      ENDIF()
      IF(${item} MATCHES "IrUsChartData.cpp")
        LIST(REMOVE_ITEM thisproject-sources ${item})
      ENDIF()
      IF(${item} MATCHES "IrUsChartsPlugIn.cpp")
        LIST(REMOVE_ITEM thisproject-sources ${item})
      ENDIF()
      IF(${item} MATCHES "IrUsChartsWidget.cpp")
        LIST(REMOVE_ITEM thisproject-sources ${item})
      ENDIF()
    ENDFOREACH()
ENDIF()

###########################################################################
# Recipe for generating MOC files.
FILE(GLOB_RECURSE odcockpit-headers "${CMAKE_CURRENT_SOURCE_DIR}/include" *.h)
QT4_WRAP_CPP(odcockpit-headers-moc ${odcockpit-headers})

# Translations.
SET(myapp_TRANSLATIONS
    odcockpit_de_DE.ts
    odcockpit_en_US.ts
)

SET(FILES_TO_TRANSLATE
    ${thisproject-sources}
    ${odcockpit-headers-moc}
)

QT4_CREATE_TRANSLATION(QM_FILES ${FILES_TO_TRANSLATE} ${myapp_TRANSLATIONS})
QT4_ADD_TRANSLATION(QM ${myapp_TRANSLATIONS})

###########################################################################
# Artifacts from this project.
ADD_LIBRARY (${PROJECT_NAME}lib-static STATIC ${thisproject-sources} ${odcockpit-headers-moc})
ADD_EXECUTABLE (${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/apps/${PROJECT_NAME}.cpp")
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${PROJECT_NAME}lib-static ${LIBRARIES})

###########################################################################
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
            IF( (   ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
                 OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD")
                 OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly") )
                AND (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") )
                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal -Wno-error=suggest-attribute=noreturn -Wno-inline")
            ELSE()
                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal")
            ENDIF()
        ENDIF()
        IF(WIN32)
            SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "")
        ENDIF()
        SET_TESTS_PROPERTIES(${testsuite-short}-TestSuite PROPERTIES TIMEOUT 3000)
        TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite ${PROJECT_NAME}lib-static ${LIBRARIES})
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)

###########################################################################
# Install this project.
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin COMPONENT odcockpit)
# This project does not have a manual page so far.
#INSTALL(FILES man/${PROJECT_NAME}.1 DESTINATION man/man1 COMPONENT odcockpit)

###########################################################################
# Enable CPack to create .deb and .rpm.
#
# Read version from first line of ChangeLog
FILE (STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog" BUILD_NUMBER)
MACRO (setup_package_version_variables _packageName)
        STRING (REGEX MATCHALL "[0-9]+" _versionComponents "${_packageName}")
        LIST (LENGTH _versionComponents _len)
        IF (${_len} GREATER 0)
            LIST(GET _versionComponents 0 MAJOR)
        ENDIF()
        IF (${_len} GREATER 1)
            LIST(GET _versionComponents 1 MINOR)
        ENDIF()
        IF (${_len} GREATER 2)
            LIST(GET _versionComponents 2 PATCH)
        ENDIF()
ENDMACRO()
setup_package_version_variables(${BUILD_NUMBER})

IF(    (UNIX)
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly")
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "OpenBSD")
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "NetBSD") )
    SET(CPACK_GENERATOR "DEB;RPM")

    SET(CPACK_PACKAGE_CONTACT "Christian Berger")
    SET(CPACK_PACKAGE_VENDOR "${CPACK_PACKAGE_CONTACT}")
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "odcockpit is visualization tool for distributed software systems realized with OpenDaVINCI.")
    SET(CPACK_PACKAGE_NAME "opendavinci")
    SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR}")
    SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR}")
    SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH}")
    SET(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
    SET(CPACK_COMPONENTS_ALL odcockpit)

    # Debian packages:
    SET(CPACK_DEBIAN_PACKAGE_SECTION "devel")
    SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
    IF("${ARMHF}" STREQUAL "YES")
        SET(ARCH "armhf")
    ELSE()
        IF("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
            SET(ARCH "amd64")
        ELSE()
            SET(ARCH "i386")
        ENDIF()
    ENDIF()
    SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${ARCH}")
    SET(CPACK_DEB_COMPONENT_INSTALL ON)
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "opendavinci-lib,opendlv-lib,libautomotivedata,libqt4-dev,libqwt5-qt4-dev,libqwt5-qt4,libqt4-opengl-dev,qt4-dev-tools")

    # RPM packages:
    IF("${ARMHF}" STREQUAL "YES")
        SET(ARCH "armhf")
    ELSE()
        IF("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
            SET(ARCH "x86_64")
        ELSE()
            SET(ARCH "i686")
        ENDIF()
    ENDIF()
    SET(CPACK_RPM_PACKAGE_BUILDARCH "Buildarch: ${CPACK_RPM_PACKAGE_ARCHITECTURE}")
    SET(CPACK_RPM_COMPONENT_INSTALL ON)
    SET(CPACK_RPM_PACKAGE_LICENSE "GPL")
    SET(CPACK_RPM_PACKAGE_REQUIRES "opendavinci-lib, opendlv-lib, libautomotivedata, qt4-devel, qwt-devel")

    # Resulting package name:
    SET(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${ARCH})
ENDIF()

INCLUDE(CPack)

