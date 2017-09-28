# OpenDaVINCI - Portable middleware for distributed components.
# Copyright (C) 2008 - 2016  Christian Berger
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
# Find libavcodec.
FIND_PATH(FFMPEG_AVCODEC_INCLUDE_DIR
          NAMES libavcodec/avcodec.h
          PATHS /usr/local/include
                /usr/pkg/include/ffmpeg2
                /usr/include)
MARK_AS_ADVANCED(FFMPEG_AVCODEC_INCLUDE_DIR)
FIND_LIBRARY(FFMPEG_AVCODEC_LIBRARY
             NAMES avcodec
             PATHS ${LIBAVCODECDIR}/lib/
                    /usr/lib/x86_64-linux-gnu/
                    /usr/local/lib64/
                    /usr/lib64/
                    /usr/lib/)
MARK_AS_ADVANCED(FFMPEG_AVCODEC_LIBRARY)

###########################################################################
# Find libavutil.
FIND_PATH(FFMPEG_AVUTIL_INCLUDE_DIR
          NAMES libavutil/avutil.h
          PATHS /usr/local/include
                /usr/pkg/include/ffmpeg2
                /usr/include)
MARK_AS_ADVANCED(FFMPEG_AVUTIL_INCLUDE_DIR)
FIND_LIBRARY(FFMPEG_AVUTIL_LIBRARY
             NAMES avutil
             PATHS ${LIBAVUTILDIR}/lib/
                    /usr/lib/x86_64-linux-gnu/
                    /usr/local/lib64/
                    /usr/lib64/
                    /usr/lib/)
MARK_AS_ADVANCED(FFMPEG_AVUTIL_LIBRARY)

###########################################################################
# Find libswscale.
FIND_PATH(FFMPEG_SWSCALE_INCLUDE_DIR
          NAMES libswscale/swscale.h
          PATHS /usr/local/include
                /usr/pkg/include/ffmpeg2
                /usr/include)
MARK_AS_ADVANCED(FFMPEG_SWSCALE_INCLUDE_DIR)
FIND_LIBRARY(FFMPEG_SWSCALE_LIBRARY
             NAMES swscale
             PATHS ${LIBSWSCALEDIR}/lib/
                    /usr/lib/x86_64-linux-gnu/
                    /usr/local/lib64/
                    /usr/lib64/
                    /usr/lib/)
MARK_AS_ADVANCED(FFMPEG_SWSCALE_LIBRARY)

###########################################################################
IF (FFMPEG_AVCODEC_INCLUDE_DIR
    AND FFMPEG_AVUTIL_INCLUDE_DIR
    AND FFMPEG_SWSCALE_INCLUDE_DIR
    AND FFMPEG_AVCODEC_LIBRARY
    AND FFMPEG_AVUTIL_LIBRARY
    AND FFMPEG_SWSCALE_LIBRARY)
    SET(FFMPEGMODULES_FOUND 1)
    SET(FFMPEGMODULES_LIBRARIES ${FFMPEG_AVCODEC_LIBRARY} ${FFMPEG_AVUTIL_LIBRARY} ${FFMPEG_SWSCALE_LIBRARY})
    SET(FFMPEGMODULES_INCLUDE_DIRS ${FFMPEG_AVCODEC_INCLUDE_DIR} ${FFMPEG_AVUTIL_INCLUDE_DIR} ${FFMPEG_SWSCALE_INCLUDE_DIR})
ENDIF()

MARK_AS_ADVANCED(FFMPEGMODULES_LIBRARIES)
MARK_AS_ADVANCED(FFMPEGMODULES_INCLUDE_DIRS)

IF (FFMPEGMODULES_FOUND)
    MESSAGE(STATUS "Found FFMEG modules: ${FFMPEGMODULES_INCLUDE_DIRS}, ${FFMPEGMODULES_LIBRARIES}")
ELSE ()
    MESSAGE(STATUS "Could not find FFMEG modules; disabling h.264 encoding/decoding")
ENDIF()

