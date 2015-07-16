#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

FIND_PATH(OPENDAVINCI_INCLUDE_DIR opendavinci/include/core/platform.h
             NAMES opendavinci
             PATHS /usr/include
                   /usr/local/include)

FIND_LIBRARY(OPENDAVINCI_LIBRARY
             NAMES opendavinci
             PATHS /usr/lib
                   /usr/lib64
                   /usr/local/lib
                   /usr/local/lib64)

SET(OPENDAVINCI_LIBRARIES ${OPENDAVINCI_LIBRARY})
SET(OPENDAVINCI_INCLUDE_DIRS ${OPENDAVINCI_INCLUDE_DIR})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibOpenDaVINCI DEFAULT_MSG
                                  OPENDAVINCI_LIBRARY OPENDAVINCI_INCLUDE_DIR)
MARK_AS_ADVANCED(OPENDAVINCI_INCLUDE_DIR OPENDAVINCI_LIBRARY )
