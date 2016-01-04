#****************************************************************************
# Copyright (C) 2001-2010  PEAK System-Technik GmbH
#
# linux@peak-system.com
# www.peak-system.com
#
# Maintainer(s): Klaus Hitschler (klaus.hitschler@gmx.de)
# Contributions: Grant Edwards (gedwards@rivatek.com)
#****************************************************************************

#****************************************************************************
#
# Makefile for Peak CAN interface drivers (ISA, PC/104, PCI, DONGLE, USB, PCCARD)
#
# $Id: Makefile 903 2015-07-29 07:30:40Z stephan $
#
#****************************************************************************

#****************************************************************************
# targets:
# depend		creates dependencies from included header files - not kernel 2.6
# all			does a standard make of the driver
# clean			cleans up, base for a forced new make
# mrproper		make a total clean - not kernel 2.6
# install		run as root, installs the drivers
# message		show info about build environment
#
# make options:
# DBG=DEBUG                 or NO_DEBUG    		  switch debug on and switches Makefile verbosity on
# KERNEL_LOCATION=...       where your kernel sources are located if not standard location (cross-compile)
# MOD=NO_MODVERSIONS        or MODVERSIONS 		  compile for modversions use
# PAR=NO_PARPORT_SUBSYSTEM  or PARPORT_SUBSYSTEM  compile for use without parport subsystem und pcan-dongle
# USB=NO_USB_SUPPORT        or USB_SUPPORT    	  compile for use with USB and pcan-usb
# PCI=NO_PCI_SUPPORT        or PCI_SUPPORT        compile for use with PCAN-PCI or PCAN-PCIe
# PCIEC=NO_PCIEC_SUPPORT    or PCIEC_SUPPORT      compile for use with PCI-Expresscard
# DNG=NO_DONGLE_SUPPORT     or DONGLE_SUPPORT     compile for use with PCAN-DONGLE
# ISA=NO_ISA_SUPPORT        or ISA_SUPPORT        compile for use with PCAN-ISA or PCAN-104
# PCC=NO_PCCARD_SUPPORT     or PCCARD_SUPPORT     compile for use with PCAN-PCCARD
# NET=NO_NETDEV_SUPPORT     or NETDEV_SUPPORT     compile for use as CAN network device (AF_CAN)
#     ... or use AUTO_NETDEV_SUPPORT to enable netdev configuration depending on kernel CONFIG_CAN (kernel 2.6.25+)
# VERBOSE=0                 or 1                  switch Makefile verbosity on
# RT=XENOMAI                or RTAI or NO_RT      compile for use on XENOMAI or RTAI RTOS
#
# please the first time do a make clean; make
#

#****************************************************************************
# please modify only here if your kernel path is elsewhere located
#
KERNEL_LOCATION =

#****************************************************************************
# probe various standard kernel locations
#
ifneq ($(shell if test -n "$(KERNEL_LOCATION)"; then if test -d $(KERNEL_LOCATION); then echo "true"; fi; fi), true)

# ubuntu
ifeq ($(shell if test -d "/usr/src/linux-headers-`uname -r`" ; then echo "true" ; fi), true)
KERNEL_LOCATION = $(shell echo "/usr/src/linux-headers-`uname -r`")
endif

# plain vanilla kernel @ /usr/src
ifeq ($(shell if test -d "/usr/src/linux-`uname -r`" ; then echo "true" ; fi), true)
KERNEL_LOCATION = $(shell echo "/usr/src/linux-`uname -r`")
endif

# install from homebrew kernels symlinking to kernel source in /lib/modules/<kernel>/build
ifeq ($(shell if test -d "/lib/modules/`uname -r`/build" ; then echo "true" ; fi), true)
KERNEL_LOCATION = $(shell echo "/lib/modules/`uname -r`/build")
endif

endif

#****************************************************************************
# removed old kernel source path retrival for support of kernels < 2.2.18!
# old KERNSRC = /lib/modules/$(VERSION)/build
#
KERNSRC := $(KERNEL_LOCATION)

#****************************************************************************
# determine where to find the kernel built header files
#
HEADER_PATH := $(shell if test -d $(KERNEL_LOCATION)/include/generated ; \
                 then echo "$(KERNEL_LOCATION)/include/generated" ;      \
                 else echo "$(KERNEL_LOCATION)/include/linux"     ; fi )

#****************************************************************************
# whole makefile is based on availability of version.h file
# do a forced stop if it is not available
#
# >= 3.7: linux/version.h no more in include but in include/generated/uapi
#
VERSION_H_DIR := $(shell if test -d $(HEADER_PATH)/uapi ;    \
                   then echo "$(HEADER_PATH)/uapi";          \
                   else echo "$(KERNEL_LOCATION)/include"; fi)

HASVERSION_H := $(shell if test -f $(VERSION_H_DIR)/linux/version.h ; \
                  then echo yes ; \
                  else echo no; fi )

ifeq ($(HASVERSION_H),no)
$(error "Can't find $(VERSION_H_DIR)/linux/version.h")
else

#****************************************************************************
# removed old version retrival for better cross compile support
# old VERSION := $(shell uname -r)
#
VERSION := $(shell cpp -E -dM -I$(KERNEL_LOCATION)/include \
                              $(VERSION_H_DIR)/linux/version.h | \
                              grep UTS_RELEASE | sed -e 's;[^"]*"\(.*\)";\1;g')

ifeq ($(VERSION),)
VERSION := $(shell cpp -E -dM -I$(KERNEL_LOCATION)/include \
                              $(HEADER_PATH)/utsrelease.h | \
                              grep UTS_RELEASE | sed -e 's;[^"]*"\(.*\)";\1;g')
ifeq ($(VERSION),)
$(error "Unable to read version string from $(KERNEL_LOCATION)")
endif
endif

#****************************************************************************
# where the driver should be installed - change here for cross install
#
INSTALL_LOCATION = $(DESTDIR)/lib/modules/$(VERSION)/misc

#****************************************************************************
# get extracted kernel VERSION and PATCHLEVEL for comparison
#
# VERSION = x.y[.z][-name]
#
# Examples:
# VERSION = 1.2
# VERSION = 1.02
# VERSION = 1.2-name
# VERSION = 1.2.0003
# VERSION = 1.2.3-name
KVERSION    := $(shell echo $(VERSION) | sed -e 's/^\([1-9][0-9]*\)\..*/\1/' )
KPATCHLEVEL := $(shell echo $(VERSION) | sed -e 's/^$(KVERSION)\.0*\([0-9][0-9]*\).*/\1/' )
SUBLEVELTMP := $(shell echo $(VERSION) | sed -e 's/^$(KVERSION)\.0*$(KPATCHLEVEL)\.0*\([0-9][0-9]*\).*/\1/' )

ifeq ($(SUBLEVELTMP),$(VERSION))
SUBLEVEL=0
else
SUBLEVEL=$(SUBLEVELTMP)
endif

#****************************************************************************
# decide to use KBUILD for 2.6.x and 3.x.x kernels
#
USEKBUILD   := $(shell if [ $(KVERSION) -ge 3 ]  ; then echo "yes" ; else echo "no"  ; fi)

ifeq ($(USEKBUILD),no)
USEKBUILD   := $(shell if [ $(KVERSION) -eq 2 ] && [ $(KPATCHLEVEL) -eq 6 ]  ; \
                 then echo "yes" ; else echo "no"  ; fi)
endif

#****************************************************************************
# some common switches and defines
#
DBG     = NO_DEBUG
MOD     = MODVERSIONS
PAR     = PARPORT_SUBSYSTEM
USB     = USB_SUPPORT
PCI     = PCI_SUPPORT
PCIEC   = PCIEC_SUPPORT
DNG     = DONGLE_SUPPORT
ISA     = ISA_SUPPORT
PCC     = PCCARD_SUPPORT
NET     = AUTO_NETDEV_SUPPORT
RT      = NO_RT

VERBOSE = 0

SRC     = src
TEMP    = /tmp
PWD     = $(shell pwd)       # called from inside IDEs it differs from the used working directory

PARMS   = type=isa,sp        # only for installer: please modify the install parameters according to your configuration

#****************************************************************************
# switch make verbosity on
#
ifeq ($(DBG),DEBUG)
VERBOSE = 1
endif

#****************************************************************************
# switch make verbosity on
#
ifneq ($(PCI),PCI_SUPPORT)      # no pci means no PCAN-Expresscard support
PCIEC = NO_PCIEC_SUPPORT
endif

#****************************************************************************
# bo PCAN-Expresscard support for kernels 2.4.x
#
ifeq ($(USEKBUILD),no)         # not for kernel 2.4.x
PCIEC = NO_PCIEC_SUPPORT
endif

#****************************************************************************
# Test current system for UDEV support influence only for installation
#
UDEV   := $(shell if test -d $(DESTDIR)/etc/udev/rules.d ; then echo yes ; else echo no; fi )

ifeq ($(RT), XENOMAI)
#****************************************************************************
# Define flags for XENOMAI installation only
#
USB   = NO_USB_SUPPORT
PCC   = NO_PCCARD_SUPPORT
NET   = NO_NETDEV_SUPPORT
PCIEC = NO_PCIEC_SUPPORT
UDEV  = no

SKIN = xeno
RT_DIR          ?= /usr/xenomai
RT_CONFIG       ?= $(RT_DIR)/bin/xeno-config
RT_LIB_DIR      ?= $(shell $(RT_CONFIG) --library-dir)
RT_CFLAGS       ?= $(shell $(RT_CONFIG) --$(SKIN)-cflags)
endif

#****************************************************************************

ifeq ($(RT), RTAI)
#****************************************************************************
# Define flags for RTAI installation only
#
USB   = NO_USB_SUPPORT
PCC   = NO_PCCARD_SUPPORT
NET   = NO_NETDEV_SUPPORT
PCIEC = NO_PCIEC_SUPPORT
UDEV  = no

SKIN = module
RT_DIR          ?= /usr/realtime
RT_CONFIG       ?= $(RT_DIR)/bin/rtai-config
RT_LIB_DIR      ?= $(shell $(RT_CONFIG) --library-dir)
RT_CFLAGS       ?= $(shell $(RT_CONFIG) --$(SKIN)-cflags)
endif

#****************************************************************************

ifeq ($(NET), AUTO_NETDEV_SUPPORT)
#****************************************************************************
# Auto configure netdev support when kernel is compiled with CONFIG_CAN
#

HASAUTOCONF_H := $(shell if test -f $(HEADER_PATH)/autoconf.h ; then echo yes ; else echo no; fi )

ifeq ($(HASAUTOCONF_H),no)
$(error "AUTO_NETDEV_SUPPORT: Can't find $(HEADER_PATH)/autoconf.h !")
else

SOCKETCAN := $(shell cpp -dM -I$(KERNEL_LOCATION)/include $(HEADER_PATH)/autoconf.h | grep -c CONFIG_CAN)

ifeq ($(SOCKETCAN),0)
NET = NO_NETDEV_SUPPORT
else
NET = NETDEV_SUPPORT
endif

endif
endif

#****************************************************************************


#****************************************************************************
# preparation what to build or what to KBUILD
#
pcan-objs := $(SRC)/pcan_main.o $(SRC)/pcan_fops.o $(SRC)/pcan_fifo.o $(SRC)/pcan_filter.o 
pcan-objs += $(SRC)/pcan_parse.o $(SRC)/pcan_sja1000.o $(SRC)/pcan_common.o

ifeq ($(PCI),PCI_SUPPORT)
pcan-objs += $(SRC)/pcan_pci.o
endif

ifeq ($(PCIEC),PCIEC_SUPPORT)
pcan-objs += $(SRC)/pcan_pciec.o 
endif

ifeq ($(ISA),ISA_SUPPORT)
pcan-objs += $(SRC)/pcan_isa.o
endif

ifeq ($(DNG),DONGLE_SUPPORT)
pcan-objs += $(SRC)/pcan_dongle.o
endif

ifeq ($(PCC),PCCARD_SUPPORT)
pcan-objs += $(SRC)/pcan_pccard_kernel.o $(SRC)/pcan_pccard.o 
endif

ifeq ($(USB),USB_SUPPORT)
pcan-objs += $(SRC)/pcan_usb_core.o $(SRC)/pcan_usb.o
pcan-objs += $(SRC)/pcan_usbpro.o $(SRC)/pcan_timing.o
pcan-objs += $(SRC)/pcan_usbfd.o
endif

ifeq ($(NET),NETDEV_SUPPORT)
pcan-objs += $(SRC)/pcan_netdev.o
endif

ifeq ($(USEKBUILD),yes) # <<<<< USEKBUILD >>>>>>

#****************************************************************************
# for local installation only: sometimes /etc/modprobe.conf.local is used
#
MODCONF := $(shell if test -d "$(DESTDIR)/etc/modprobe.d" ; then echo "$(DESTDIR)/etc/modprobe.d/pcan.conf" ; else echo "$(DESTDIR)/etc/modules.conf.local" ; fi)
ifeq ($(UDEV), yes)
MODINST  = "install pcan /sbin/modprobe --ignore-install pcan"
else
MODINST  = "install pcan /sbin/modprobe --ignore-install pcan; /usr/local/bin/pcan_make_devices 2"
endif

#****************************************************************************
# what's the target
#
TARGET = pcan.ko
obj-m := pcan.o

#****************************************************************************
# add flags to standard flags
#
# Note: to get listing from Kernel module compilation:
# edit scripts/Makefile.build
# -cmd_cc_o_c = $(CC) $(c_flags) -c -o $(@D)/.tmp_$(@F) $<
# +cmd_cc_o_c = $(CC) $(c_flags) -c -Wa,-adhln=$<.lst -o $(@D)/.tmp_$(@F) $<
#
EXTRA_CFLAGS += -I$(PWD) -D$(DBG) -D$(MOD) -D$(PAR) -D$(USB) -D$(PCI) -D$(PCIEC) -D$(ISA) -D$(DNG) -D$(PCC) -D$(NET) -D$(RT) $(RT_CFLAGS)

# gcc 4.9: warning has became an error
GCC_VERMAJ := $(shell gcc -dumpversion | cut -d. -f1)
GCC_VERMIN := $(shell gcc -dumpversion | cut -d. -f2)

DATE_TIME_WARNING := $(shell if [ $(GCC_VERMAJ) -gt 4 ]; then echo "y"; else echo "n"; fi)
ifeq ($(DATE_TIME_WARNING),n)
DATE_TIME_WARNING := $(shell if [ $(GCC_VERMAJ) -eq 4 ] && [ $(GCC_VERMIN) -ge 9 ]; then echo "y"; else echo "n"; fi)
endif
ifeq ($(DATE_TIME_WARNING),y)
EXTRA_CFLAGS += -Wno-error=date-time
endif

#****************************************************************************
# do it in another way for kernels less than 2.6.5
#
USESUBDIRS  := $(shell if [ $(KVERSION) -eq 2 ] && [ $(KPATCHLEVEL) -eq 6 ] && [ $(SUBLEVEL) -lt 5 ]  ; \
                 then echo "yes" ; else echo "no"  ; fi)

ifeq ($(USESUBDIRS),yes)
CMDLINE = $(MAKE) -C $(KERNSRC) M=$(PWD)                                V=$(VERBOSE) modules
else
CMDLINE = $(MAKE) -C $(KERNSRC) SUBDIRS=$(PWD) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" V=$(VERBOSE) modules
endif # <<<<< USESUBDIRS >>>>>>

#****************************************************************************
# do it
#
all : message
	$(CMDLINE)

else # <<<<< USEKBUILD >>>>>>

#****************************************************************************
# additional common switches and defines
#
CC      = gcc
LD      = ld
INC     = $(KERNSRC)/include

DEP     = .depend

#****************************************************************************
# for local installation only: sometimes /etc/modules.conf.local is used
#
MODCONF = "$(DESTDIR)/etc/modules.conf"
MODINST = "post-install pcan /usr/local/bin/pcan_make_devices 2"

#****************************************************************************
# what's the target
#
TARGET = pcan.o

#****************************************************************************
# compile flags
#
CFLAGS  = -O2 -D__KERNEL__ -DMODULE -Wall -I$(INC) -I. -D$(DBG) -D$(MOD) -D$(PAR) -D$(USB) -D$(PCI) -D$(PCIEC) -D$(ISA) -D$(DNG) -D$(PCC) -D$(NET) -D$(RT) $(RT_CFLAGS)

#****************************************************************************
# do it
#
all: message $(TARGET)

$(TARGET)  : $(pcan-objs)
	$(LD) -r $^ -o $@

#********** catch include file depencies ************************************
ifeq ($(DEP),$(wildcard $(DEP)))

depend:
	makedepend -f$(DEP) -- $(CFLAGS) -- $(addsuffix .c, $(basename $(pcan-objs))) -I$(INC)

include $(DEP)

else

depend:
	touch $(DEP)
	makedepend -f$(DEP) -- $(CFLAGS) -- $(addsuffix .c, $(basename $(pcan-objs))) -I$(INC)
endif

endif # <<<<< USEKBUILD >>>>>>

#********** clean all for a rebuild *****************************************
clean:
	rm -f $(SRC)/*o $(SRC)/*~ $(SRC)/.*cmd *o *ko *~ .*cmd  pcan.mod.c

#********** make totally clean **********************************************
ifneq ($(USEKBUILD),yes) # <<<<< USEKBUILD >>>>>>
mrproper: clean
	rm -f $(DEP)
endif # <<<<< USEKBUILD >>>>>>

#********** this entry is reserved for root access only *********************
compat:
	@if [ -f /etc/modprobe.d/pcan ] ; then \
		mv /etc/modprobe.d/pcan /etc/modprobe.d/pcan.conf ; \
		echo "Info: Moved /etc/modprobe.d/pcan to /etc/modprobe.d/pcan.conf for compatibility reason."; \
	fi

install: compat
	@if test -d $(INSTALL_LOCATION); then\
		echo "Info: $(INSTALL_LOCATION) exists.";\
	else\
		mkdir -p $(INSTALL_LOCATION);\
	fi
	@mkdir -p $(DESTDIR)/usr/local/bin
	@cp -f $(TARGET) $(INSTALL_LOCATION)/$(TARGET)
	@cp -f pcan_make_devices $(DESTDIR)/usr/local/bin
	@chmod 744 $(DESTDIR)/usr/local/bin/pcan_make_devices
	@if [ ! -f $(MODCONF) ] || test -z $(shell grep -ls pcan $(MODCONF)) ; then\
		mkdir -p $(shell dirname $(MODCONF));\
		cp $(MODCONF) $(MODCONF)~ 2> /dev/null;\
		echo ""                                               >> $(MODCONF);\
		echo "# pcan - automatic made entry, begin --------"  >> $(MODCONF);\
		echo "# if required add options and remove comment "  >> $(MODCONF);\
		echo "# options pcan $(PARMS)                      "  >> $(MODCONF);\
		echo $(MODINST)                                       >> $(MODCONF);\
		echo "# pcan - automatic made entry, end ----------"  >> $(MODCONF);\
		echo ""                                               >> $(MODCONF);\
	else\
		echo "Info: Left current 'pcan'-entry in $(MODCONF) untouched.";\
	fi
# can't rmmod peak_pci for kernel versions < 3.4 (crash)
	@if [ $(UDEV) = "yes" ]; then\
		mkdir -p $(DESTDIR)/usr/local/bin;\
		cp -f udev/pcan_usb_minor_check.bash $(DESTDIR)/usr/local/bin;\
		chmod 744 $(DESTDIR)/usr/local/bin/pcan_usb_minor_check.bash;\
		cp -f udev/45-pcan.rules $(DESTDIR)/etc/udev/rules.d;\
		echo "Info: Copied 45-pcan.rules to $(DESTDIR)/etc/udev/rules.d.";\
		peak_pci=0;\
		kvernum=$$(($(KVERSION)*10000+$(KPATCHLEVEL)*100+$(SUBLEVEL)));\
		for m in $(shell awk '/^blacklist/ { print $$2 }' udev/blacklist-peak.conf); do \
			if [ $$m = "peak_pci" ] && [ $$kvernum -lt 30400 ]; then\
				peak_pci=`lsmod | grep -ce peak_pci`;\
			else\
				rmmod $$m 2> /dev/null;\
			fi\
		done;\
		cp -f udev/blacklist-peak.conf $(shell dirname $(MODCONF));\
		chmod 644 $(shell dirname $(MODCONF))/blacklist-peak.conf;\
		echo "Info: mainline drivers removed and blacklisted in";\
		echo "      $(shell dirname $(MODCONF))/blacklist-peak.conf";\
		if [ $$peak_pci -ne 0 ]; then\
			echo "Info: peak_pci can't be removed from the Kernel";\
			echo "      You should reboot to complete the installation.";\
	 	fi\
	 else\
		echo "Info: No UDEV installation found.";\
	 fi
	@mkdir -p $(DESTDIR)/usr/include
	@cp -f pcan.h $(DESTDIR)/usr/include/pcan.h
	@chmod 644 $(DESTDIR)/usr/include/pcan.h
ifeq ($(DESTDIR),)
	@if [ $(UDEV) = "yes" ]; then\
		/sbin/udevadm control --reload-rules; \
	 fi
	@/sbin/depmod
endif

.PHONY : uninstall
uninstall:
	@-rmmod pcan 2> /dev/null
	@rm -f $(INSTALL_LOCATION)/$(TARGET)
	@rm -f $(DESTDIR)/usr/include/pcan.h
	@rm -f $(DESTDIR)/usr/local/bin/pcan_make_devices
	@rm -f $(DESTDIR)/etc/udev/rules.d/45-pcan.rules
	@rm -f $(DESTDIR)/usr/local/bin/pcan_usb_minor_check.bash
	@rm -f $(shell dirname $(MODCONF))/blacklist-peak.conf
	@rm -f $(MODCONF)
ifeq ($(DESTDIR),)
	@/sbin/depmod
endif

#********** informations during build of driver *****************************
.PHONY : message
message:
	@ echo "***"
	@ echo "*** Host machine kernel version=$(shell uname -r)"
	@ echo "*** Driver kernel version=$(VERSION)"
	@ echo "*** Path to kernel sources=$(KERNSRC)"
	@ echo "*** use KBUILD=$(USEKBUILD)"
	@ echo "*** $(CC) version=$(shell $(CC) -dumpversion)"
	@ echo "***"

endif  # <<<<< HASVERSION_H >>>>>>

debug_kernel_version:
	@echo "Major=$(KVERSION) Minor=$(KPATCHLEVEL) Subminor=$(SUBLEVEL)"
# DO NOT DELETE

