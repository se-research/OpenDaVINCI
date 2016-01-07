/*
 * PCAN-USB Pro / PCAN-USB Pro FD firmware objects
 *
 * Copyright (C) 2003-2014 PEAK System-Technik GmbH
 * Copyright (C) 2014 Stephane Grosjean <s.grosjean@peak-system.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published
 * by the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the GNU
 * General Public License for more details.
 */
#ifndef PCAN_USBFD_H
#define PCAN_USBFD_H

#include "pcan_ucan.h"

/*
 * Extended commands (non uCAN commands):
 *
 * Clock Modes command
 */
#define PCAN_USBFD_CMD_CLK_SET		0x80

#define PCAN_USBFD_CLK_80MHZ		0x0
#define PCAN_USBFD_CLK_60MHZ		0x1
#define PCAN_USBFD_CLK_40MHZ		0x2
#define PCAN_USBFD_CLK_30MHZ		0x3
#define PCAN_USBFD_CLK_24MHZ		0x4
#define PCAN_USBFD_CLK_20MHZ		0x5
#define PCAN_USBFD_CLK_DEF		PCAN_USBFD_CLK_80MHZ

struct __packed pcan_usb_pro_fd_clock {
	u16	opcode_channel;

	u8	mode;
	u8	unused[5];
};

/* LED control command */
#define PCAN_USBFD_CMD_LED_SET		0x86

#define PCAN_USBFD_LED_DEV		0x00
#define PCAN_USBFD_LED_FAST		0x01
#define PCAN_USBFD_LED_SLOW		0x02
#define PCAN_USBFD_LED_FIXED		0x03
#define PCAN_USBFD_LED_OFF		0x04
#define PCAN_USBFD_LED_DEF		PCAN_USBFD_LED_DEV

struct __packed pcan_usbfd_led {
	u16	opcode_channel;

	u8	mode;
	u16	unused[5];
};

/* Extended usage of uCAN commands CMD_RX_FRAME_xxxABLE for PCAN-USB Pro FD */
#define PCAN_USBFD_FLTEXT_CALIBRATION	0x8000
#define PCAN_USBFD_FLTEXT_DEBUG		0x4000

struct __packed pcan_usbfd_filter_ext {
	u16	opcode_channel;

	u16	ext_mask;
	u16	unused;
	u16	usb_mask;
};

/* Extended usage of uCAN messages for PCAN-USB Pro FD */
#define PCAN_USBFD_MSG_CALIBRATION	0x100

struct __packed pcan_usbfd_ts_msg {
	__le16	size;
	__le16	type;
	__le32	ts_low;
	__le32	ts_high;
	__le16	usb_frame_index;
	u16	unused;
};

#define PCAN_USBFD_MSG_OVERRUN		0x101

#define PCAN_USBFD_OVMSG_CHANNEL(o)	((o)->channel & 0xf)

struct __packed pcan_usbfd_ovr_msg {
	__le16	size;
	__le16	type;
	__le32	ts_low;
	__le32	ts_high;
	u8	channel;
	u8	unused[3];
};

#define PCAN_USBFD_CMD_DEVID_SET	0x81

struct __packed pcan_usbfd_device_id {
	u16	opcode_channel;

	u16	unused;
	__le32	device_id;
};

#define PCAN_USBFD_CMD_LOCINFO_SET	0x83
#define PCAN_USBFD_CMD_LOCINFO_GET	0x84
#define PCAN_USBFD_CMD_LOCINFO_RSP	0x85

struct __packed pcan_usbfd_location_info {
	u16	opcode_channel;

	u8	index;
	u8	w;
	u16	unused;
	u8	d0;
	u8	d1;
};

#define PCAN_USBFD_LOCINFO_LEN		250

#define PCAN_USBFD_MSG_DEBUG		0x200

struct __packed pcan_usbfd_dbg_msg {
	__le16	size;
	__le16	type;
	u8	d[64];
};

#endif
