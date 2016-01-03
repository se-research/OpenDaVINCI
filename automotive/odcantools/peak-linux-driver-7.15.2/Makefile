#****************************************************************************
# Copyright (C) 2001-2010  PEAK System-Technik GmbH
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
# Contributions: Pablo Yanez Trujillo (yanez@pse.de) cross-compile
#****************************************************************************

#****************************************************************************
#
# Makefile - global Makefile for all components
#
# $Id: Makefile 753 2014-01-21 10:45:03Z stephane $
#
#****************************************************************************

#****************************************************************************
# CROSS-COMPILING SETTINGS
#
# You need a cross-compiler. You can build one with crosstool
# http://www.kegel.com/crosstool/current/doc/crosstool-howto.html
#
# These variables work with the toolchains created by crosstool

# defines the architecture. For example 'arm' for an ARM system
#export ARCH=arm

# the path and prefix of the cross-compiler
#export CROSS_COMPILE=/home/yanez/matrix500/arm-9tdmi-linux-gnu/bin/arm-9tdmi-linux-gnu-

ifneq ($(CROSS_COMPILE),)
  export CC=$(CROSS_COMPILE)gcc
endif

#****************************************************************************
# MACROS AND DEFINES

define make-all
@cd driver; make depend; make; cd ../lib; make; cd ../test; make; cd ..
endef

define make-clean
@cd driver; make clean; cd ../lib; make clean; cd ../test; make clean; cd ..
endef

define make-install
@cd driver; make install; cd ../lib; make install; cd ../test; make install; cd ..
endef

define make-uninstall
@cd driver; make uninstall; cd ../lib; make uninstall; cd ../test; make uninstall; cd ..
endef

define make-rpminstall
@cd driver; make rpminstall; cd ../lib; make rpminstall; cd ../test; make rpminstall; cd ..
endef


#****************************************************************************
# DO IT
all :
	$(make-all)

clean:
	$(make-clean)

install:
	$(make-install)
 
uninstall:
	$(make-uninstall)

# end


# DO NOT DELETE
