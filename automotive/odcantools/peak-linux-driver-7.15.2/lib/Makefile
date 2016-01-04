#****************************************************************************
# Copyright (C) 2001-2007  PEAK System-Technik GmbH
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
# Makefile - Makefile for the shared library libpcan.so.x.x
#
# $Id: Makefile 857 2015-06-22 15:26:54Z stephane $
#
#****************************************************************************

PCANDRV_DIR := ../driver

SRC     := src
INC     := -I. -I$(PCANDRV_DIR)
FILES   := $(SRC)/libpcan.c
DBG     := -g
RT      ?= NO_RT

ifeq ($(RT), XENOMAI)
# Define flags for XENOMAI installation only
USB := NO_USB_SUPPORT
PCC := NO_PCCARD_SUPPORT

# Usage of "--skin" is now deprecated in Xenomai.
# Remove this comment for older versions
#SKIN := xeno
RT_DIR          ?= /usr/xenomai

RT_CONFIG       ?= $(RT_DIR)/bin/xeno-config

ifneq ($(SKIN),)
RT_CFLAGS       ?= $(shell $(RT_CONFIG) --$(SKIN)-cflags)
RT_LIB_DIR      ?= $(shell $(RT_CONFIG) --library-dir) -Wl,-rpath $(shell $(RT_CONFIG) --library-dir)
else
RT_CFLAGS       ?= $(shell $(RT_CONFIG) --skin rtdm --cflags)
RT_LDFLAGS       ?= -Wl,-rpath $(shell $(RT_CONFIG) --library-dir) $(shell $(RT_CONFIG) --skin rtdm --ldflags)
endif
endif

ifeq ($(RT), RTAI)
# Define flags for RTAI installation only
USB := NO_USB_SUPPORT
PCC := NO_PCCARD_SUPPORT

SKIN := lxrt
RT_DIR          ?= /usr/realtime

RT_CONFIG       ?= $(RT_DIR)/bin/rtai-config
RT_LIB_DIR      ?= $(shell $(RT_CONFIG) --library-dir) -Wl,-rpath $(shell $(RT_CONFIG) --library-dir)
RT_CFLAGS       ?= $(shell $(RT_CONFIG) --$(SKIN)-cflags)
endif

ifeq ($(HOSTTYPE),x86_64)
LIBPATH := /usr/lib64
else
LIBPATH := /usr/lib
endif
INCPATH := /usr/include

LDNAME  := libpcan.so
SONAME  := $(LDNAME).0
TARGET  := $(SONAME).6

CFLAGS := -D$(RT) $(INC) -fPIC -shared -O2 -Wall $(RT_CFLAGS)
LDFLAGS := -Wl,-soname,$(SONAME) -lc $(RT_LDFLAGS)

all: $(TARGET)

$(TARGET) : $(FILES)
	$(CC) $(FILES) $(CFLAGS) $(LDFLAGS) -o $@
	ln -sf $@ $(LDNAME)

clean:
	rm -f $(SRC)/*~ $(SRC)/*.o *~ *.so.* *.so

#********** these entries are reserved for root access only *******************
install:
	mkdir -p $(DESTDIR)$(LIBPATH)
	cp $(TARGET) $(DESTDIR)$(LIBPATH)/$(TARGET)
	ln -sf $(DESTDIR)$(LIBPATH)/$(TARGET) $(DESTDIR)$(LIBPATH)/$(SONAME)
	ln -sf $(DESTDIR)$(LIBPATH)/$(SONAME) $(DESTDIR)$(LIBPATH)/$(LDNAME)
	mkdir -p $(DESTDIR)$(INCPATH)
	cp libpcan.h $(PCANDRV_DIR)/pcan.h $(DESTDIR)$(INCPATH)
	chmod 644 $(DESTDIR)$(INCPATH)/libpcan.h $(DESTDIR)$(INCPATH)/pcan.h
ifeq ($(DESTDIR),)
	/sbin/ldconfig
endif

uninstall:
	-rm -f $(DESTDIR)$(LIBPATH)/$(TARGET)
	-rm -f $(DESTDIR)$(LIBPATH)/$(SONAME) $(DESTDIR)$(LIBPATH)/$(LDNAME)
	-rm -f $(DESTDIR)$(INCPATH)/libpcan.h $(DESTDIR)$(INCPATH)/pcan.h
ifeq ($(DESTDIR),)
	/sbin/ldconfig
endif
