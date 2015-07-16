#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

FIND_PATH(AUTOMOTIVEDATA_INCLUDE_DIR opendavinci/automotivedata/GeneratedHeaders_AutomotiveData.h
             NAMES automotivedata
             PATHS /usr/include
                   /usr/local/include)

FIND_LIBRARY(AUTOMOTIVEDATA_LIBRARY
             NAMES automotivedata
             PATHS /usr/lib
                   /usr/lib64
                   /usr/local/lib
                   /usr/local/lib64)

SET(AUTOMOTIVEDATA_LIBRARIES ${AUTOMOTIVEDATA_LIBRARY})
SET(AUTOMOTIVEDATA_INCLUDE_DIRS ${AUTOMOTIVEDATA_INCLUDE_DIR})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibAutomotiveData DEFAULT_MSG
                                  AUTOMOTIVEDATA_LIBRARY AUTOMOTIVEDATA_INCLUDE_DIR)
MARK_AS_ADVANCED(AUTOMOTIVEDATA_INCLUDE_DIR AUTOMOTIVEDATA_LIBRARY )
