#****************************************************************************
# Copyright (C) 2001-2006  PEAK System-Technik GmbH
#
# linux@peak-system.com
# www.peak-system.com
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
# Maintainer(s): Klaus Hitschler (klaus.hitschler@gmx.de)
#****************************************************************************

#****************************************************************************
#
# Makefile - Makefile for receivetest and transmittest programs
#
# $Id: Makefile 518 2007-08-08 07:40:31Z edouard $
#
#****************************************************************************

PCANDRV_DIR := ../../driver
PCANLIB_DIR := ../../lib

SRC     := .
INC     := -I. -I$(PCANLIB_DIR) -I$(PCANDRV_DIR)
RT      ?= XENOMAI

USERAPP_LIBS := -lpcan

ifeq ($(RT), XENOMAI)
# Usage of "--skin" is now deprecated in Xenomai.
# Remove this comment for older versions
#SKIN = xeno
### Xenomai directory, xeno-config and library directory ###########
RT_DIR          ?= /usr/xenomai
RT_CONFIG       ?= $(RT_DIR)/bin/xeno-config
### User space application compile options #########################
ifneq ($(SKIN),)
USERAPP_CFLAGS    ?= $(shell $(RT_CONFIG) --$(SKIN)-cflags)
RT_LIB_DIR        ?= $(shell $(RT_CONFIG) --library-dir) -Wl,-rpath $(shell $(RT_CONFIG) --library-dir)
USERAPP_LDFLAGS   ?= $(shell $(RT_CONFIG) --$(SKIN)-ldflags) -L$(RT_LIB_DIR)
else
RT_LIB_DIR        ?= $(shell $(RT_CONFIG) --library-dir)
USERAPP_CFLAGS    ?= $(shell $(RT_CONFIG) --skin native --cflags)
USERAPP_LDFLAGS   ?= -Wl,-rpath $(RT_LIB_DIR) $(shell $(RT_CONFIG) --skin native --ldflags)
endif
endif

ifeq ($(RT), RTAI)
SKIN = lxrt
### Rtai directory, rtai-config and library directory ###########
RT_DIR          ?= /usr/realtime
RT_CONFIG       ?= $(RT_DIR)/bin/rtai-config
RT_LIB_DIR      ?= $(shell $(RT_CONFIG) --library-dir) -Wl,-rpath $(shell $(RT_CONFIG) --library-dir)
### User space application compile options #########################
USERAPP_LIBS      := -llxrt $(USERAPP_LIBS)
USERAPP_LDFLAGS   ?= $(shell $(RT_CONFIG) --$(SKIN)-ldflags) -L$(RT_LIB_DIR)
USERAPP_CFLAGS    ?= $(shell $(RT_CONFIG) --$(SKIN)-cflags)
endif

LDLIBS := -L$(PCANLIB_DIR)

ifeq ($(HOSTTYPE),x86_64)
LDLIBS := $(LDLIBS) -L/lib64 -L/usr/lib64 -L/usr/local/lib64
else
LDLIBS := $(LDLIBS) -L/lib -L/usr/lib -L/usr/local/lib
endif

ifneq ($(RT), NO_RT)
DBGFLAGS :=
else
DBGFLAGS := -g
endif

CFLAGS := -D$(RT) $(DBGFLAGS) $(INC) $(USERAPP_CFLAGS)
LDFLAGS := $(USERAPP_LDFLAGS) $(LDLIBS) $(USERAPP_LIBS)

TARGET1 = xenomai_transmit_test
FILES1  = $(TARGET1).c
TARGET2 = xenomai_receive_test
FILES2  = $(TARGET2).c

ALL = $(TARGET1) $(TARGET2)

all: $(ALL)

$(TARGET1): $(FILES1)
	$(CC) $(CFLAGS) $? $(LDFLAGS) -o $@

$(TARGET2): $(FILES2)
	$(CC) $(CFLAGS) $? $(LDFLAGS) -o $@

clean:
	rm -f $(SRC)/*~ $(SRC)/*.o $(ALL)
	
install:
	cp $(ALL) /usr/local/bin

uninstall:
	-rm -f /usr/local/bin/$(TARGET1)
	-rm -f /usr/local/bin/$(TARGET2)
