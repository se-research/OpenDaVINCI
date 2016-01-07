#!/bin/bash
#
# This script checks PCAN USB devices minor before creating their symlink.
# With some kernel configurations (such as CONFIG_USB_DYNAMIC_MINORS=y),
# USB core doesn't take user minor base into account but starts from 0.
# As a result, the original PCAN rule will create a symlink named /dev/pcan0
# instead of /dev/pcan32, for the first PCAN USB device added to the system...
# This may conflict with any other "internal" PCAN device which is also 
# plugged into the same host.
# Thus, workaround here is to check if usb device minor is smaller than 32.
# If it is not, nothing is done (e.g. outputs the given minor).
# Otherwise, the script outputs the first free number, starting from 32 (x is 
# free <=> no /dev/pcanx does exist)
# Next rule key should take "%c" (instead of %m) into its formatted string.
#
# This Bash script is to be executed with the following udev rule:
# KERNEL=="pcanusb*", PROGRAM="pcan_usb_minor_check.bash %m", SYMLINK+="pcan%c", MODE="0666"
# 
# (C) Copyright 2011 Peak-System Gmbh

MAX_USB_MINORS=256      # see drivers/usb/core/file.c
PCAN_USB_MINOR_BASE=32  # see driver/src/pcan_main.h

if [ -n "$1" ] && [ $1 -lt ${PCAN_USB_MINOR_BASE} ]; then
	let "m=${PCAN_USB_MINOR_BASE}+$1"
else
	m=$1
fi

echo $m

exit 0
