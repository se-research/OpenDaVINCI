//****************************************************************************
// Copyright (C) 2003-2010  PEAK System-Technik GmbH
//
// linux@peak-system.com
// www.peak-system.com
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// Maintainer(s): Stephane Grosjean (s.grosjean@peak-system.com)
//
//****************************************************************************

//****************************************************************************
//
// pcan_usbpro_fw.h - the PCAN-USB-PRO firmware internal structures
//
// $Id: pcan_usbpro_fw.h 615 2010-02-14 22:38:55Z khitschler $
//
//****************************************************************************

#ifndef __pcan_usbpro_fw_h
#define __pcan_usbpro_fw_h

/* 
 * USB Vendor Request Data Types
 */

/* Vendor (other) request */
#define USB_VENDOR_REQUEST_INFO                   0
#define USB_VENDOR_REQUEST_ZERO                   1
#define USB_VENDOR_REQUEST_FKT                    2

/* Vendor Request wValue for XXX_INFO */
#define USB_VENDOR_REQUEST_wVALUE_INFO_BOOTLOADER  0
#define USB_VENDOR_REQUEST_wVALUE_INFO_FIRMWARE    1
#define USB_VENDOR_REQUEST_wVALUE_INFO_uC_CHIPID   2
#define USB_VENDOR_REQUEST_wVALUE_INFO_USB_CHIPID  3
#define USB_VENDOR_REQUEST_wVALUE_INFO_DEVICENR	   4	
#define USB_VENDOR_REQUEST_wVALUE_INFO_CPLD        5
#define USB_VENDOR_REQUEST_wVALUE_INFO_MODE			6	
#define USB_VENDOR_REQUEST_wVALUE_INFO_TIMEMODE		7

/* Vendor Request wValue for XXX_ZERO */
/* Value is Endpoint Number 0-7 */

/* Vendor Request wValue for XXX_FKT */
#define USB_VENDOR_REQUEST_wVALUE_SETFKT_BOOT       0 // set Bootloader Mode
#define USB_VENDOR_REQUEST_wVALUE_SETFKT_DEBUG_CAN  1 // not used
#define USB_VENDOR_REQUEST_wVALUE_SETFKT_DEBUG_LIN  2 // not used
#define USB_VENDOR_REQUEST_wVALUE_SETFKT_DEBUG1     3 // not used
#define USB_VENDOR_REQUEST_wVALUE_SETFKT_DEBUG2     4 // not used
#define USB_VENDOR_REQUEST_wVALUE_SETFKT_INTERFACE_DRIVER_LOADED 5

/* ctrl_type value */
#define INTERN_FIRMWARE_INFO_STRUCT_TYPE 	0x11223322
#define EXT_FIRMWARE_INFO_STRUCT_TYPE 		0x11223344

#define BOOTLOADER_INFO_STRUCT_TYPE 		0x11112222
#define uC_CHIPID_STRUCT_TYPE 				0
#define USB_CHIPID_STRUCT_TYPE 				0
#define DEVICE_NR_STRUCT_TYPE 				0x3738393A
#define CPLD_INFO_STRUCT_TYPE 				0x1A1A2277

/* USB_VENDOR_REQUEST_wVALUE_INFO_BOOTLOADER vendor request record type */
struct pcan_usbpro_bootloader_info_t
{
	uint32_t    ctrl_type;
	uint8_t		version[4];		//[0] -> main [1]-> sub [2]-> debug
	uint8_t 	   day;
	uint8_t 	   month;
	uint8_t 	   year;
	uint8_t 	   dummy;
	uint32_t	   serial_num_high;
	uint32_t	   serial_num_low;
	uint32_t	   hw_type;
	uint32_t	   hw_rev;

}  __attribute__ ((packed));

struct pcan_usbpro_crc_block_t
{
	uint32_t address;
	uint32_t len;
	uint32_t crc;

}  __attribute__ ((packed));

/* USB_VENDOR_REQUEST_wVALUE_INFO_FIRMWARE vendor request record type */
struct pcan_usbpro_ext_firmware_info_t
{
	uint32_t   	ctrl_type;
	uint8_t		version[4];		//[0] -> main [1]-> sub [2]-> debug
	uint8_t 		day;
	uint8_t 		month;
	uint8_t 		year;
	uint8_t		dummy;
	uint32_t    fw_type;

}  __attribute__ ((packed));

/* USB_VENDOR_REQUEST_wVALUE_INFO_uC_CHIPID vendor request record type */
struct pcan_usbpro_uc_chipid_t
{
	uint32_t   	ctrl_type;
	uint32_t    chip_id;

}  __attribute__ ((packed));

/* USB_VENDOR_REQUEST_wVALUE_INFO_USB_CHIPID vendor request record type */
struct pcan_usbpro_usb_chipid_t
{
	uint32_t   	ctrl_type;
	uint32_t    chip_id;

}  __attribute__ ((packed));

/* USB_VENDOR_REQUEST_wVALUE_INFO_DEVICENR vendor request record type */
struct pcan_usbpro_device_nr_t
{
	uint32_t   	ctrl_type;
	uint32_t    device_nr;

}  __attribute__ ((packed));

/* USB_VENDOR_REQUEST_wVALUE_INFO_CPLD vendor request record type */
struct pcan_usbpro_cpld_info_t
{
	uint32_t   	ctrl_type;
	uint32_t    cpld_nr;

}  __attribute__ ((packed));

/* USB_VENDOR_REQUEST_wVALUE_INFO_MODE vendor request record type */
struct pcan_usbpro_info_mode_t
{
	uint32_t   	ctrl_type;
	uint8_t     mode[16];
	uint8_t     flags[16];

}  __attribute__ ((packed));

/* USB_VENDOR_REQUEST_wVALUE_INFO_TIMEMODE vendor request record type */
struct pcan_usbpro_time_mode_t
{
	uint32_t   	ctrl_type;
	uint16_t    time_mode;
	uint16_t    flags;

}  __attribute__ ((packed));

/* 
 * USB Command Record types 
 */

#define DATA_TYPE_USB2CAN_STRUCT_CANMSG_RX_8                0x80
#define DATA_TYPE_USB2CAN_STRUCT_CANMSG_RX_4                0x81
#define DATA_TYPE_USB2CAN_STRUCT_CANMSG_RX_0                0x82
#define DATA_TYPE_USB2CAN_STRUCT_CANMSG_RTR_RX              0x83
#define DATA_TYPE_USB2CAN_STRUCT_CANMSG_STATUS_ERROR_RX     0x84
#define DATA_TYPE_USB2CAN_STRUCT_CALIBRATION_TIMESTAMP_RX   0x85
#define DATA_TYPE_USB2CAN_STRUCT_BUSLAST_RX                 0x86
#define DATA_TYPE_USB2CAN_STRUCT_CANMSG_TX_8                0x41
#define DATA_TYPE_USB2CAN_STRUCT_CANMSG_TX_4                0x42
#define DATA_TYPE_USB2CAN_STRUCT_CANMSG_TX_0                0x43
#define DATA_TYPE_USB2CAN_STRUCT_FKT_GETBAUDRATE            0x01 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETBAUDRATE            0x02
#define DATA_TYPE_USB2CAN_STRUCT_FKT_GETCANBUSACTIVATE      0x03
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETCANBUSACTIVATE      0x04
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETSILENTMODE          0x05 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETDEVICENR            0x06 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETWARNINGLIMIT        0x07 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETLOOKUP_EXPLICIT     0x08 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETLOOKUP_GROUP        0x09 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETFILTERMODE          0x0a 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETRESET_MODE          0x0b 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETERRORFRAME          0x0c 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_GETCANBUS_ERROR_STATUS 0x0D 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETREGISTER            0x0e 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_GETREGISTER            0x0f 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETGET_CALIBRATION_MSG 0x10 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETGET_BUSLAST_MSG     0x11 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_GETDEVICENR            0x12 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SETSTRING              0x13 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_GETSTRING              0x14 
#define DATA_TYPE_USB2CAN_STRUCT_FKT_STRING                 0x15
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SAVEEEPROM             0x16
#define DATA_TYPE_USB2CAN_STRUCT_FKT_USB_IN_PACKET_DELAY    0x17
#define DATA_TYPE_USB2CAN_STRUCT_FKT_TIMESTAMP_PARAM        0x18
#define DATA_TYPE_USB2CAN_STRUCT_FKT_ERROR_GEN_ID           0x19
#define DATA_TYPE_USB2CAN_STRUCT_FKT_ERROR_GEN_NOW          0x1A
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SET_SOFTFILER          0x1B
#define DATA_TYPE_USB2CAN_STRUCT_FKT_SET_CANLED             0x1C

/* Record structures */
struct pcan_usbpro_canmsg_rx_t
{
	uint8_t	data_type;
	uint8_t	client;
	uint8_t	flags;
	uint8_t	len;
	uint32_t timestamp32;
	uint32_t id;

	uint8_t  data[8];

}  __attribute__ ((packed));

/* Defines for status */
#define FW_USBPRO_STATUS_MASK_ERROR_S     0x0001
#define FW_USBPRO_STATUS_MASK_BUS_S       0x0002
#define FW_USBPRO_STATUS_MASK_OVERRUN_S   0x0004
#define FW_USBPRO_STATUS_MASK_QOVERRUN_S  0x0008

struct pcan_usbpro_canmsg_status_error_rx_t
{
	uint8_t	data_type;
	uint8_t	channel;
	uint16_t	status;
	uint32_t	timestamp32;
	uint32_t	error_frame;

}  __attribute__ ((packed));

struct pcan_usbpro_calibration_ts_rx_t
{
	uint8_t	data_type;
	uint8_t	dummy[3];
	uint32_t timestamp64[2];

}  __attribute__ ((packed));

struct pcan_usbpro_buslast_rx_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	buslast_val;
	uint32_t timestamp32;

}  __attribute__ ((packed));

struct pcan_usbpro_canmsg_tx_t
{
	uint8_t	data_type;
	uint8_t	client;
	uint8_t	flags;
	uint8_t	len;
	uint32_t id;

	uint8_t  data[8];

}  __attribute__ ((packed));

struct pcan_usbpro_baudrate_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	dummy;
	uint32_t CCBT;

}  __attribute__ ((packed));

struct pcan_usbpro_bus_activity_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	onoff;                     /* 0->off  1->on */

}  __attribute__ ((packed));

struct pcan_usbpro_silent_mode_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	onoff;                     /* 0->off  1->on */
	
}  __attribute__ ((packed));

struct pcan_usbpro_dev_nr_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	dummy;
	uint32_t serial_num;
	
}  __attribute__ ((packed));

struct pcan_usbpro_warning_limit_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	warning_limit; 

}  __attribute__ ((packed));

struct pcan_usbpro_lookup_explicit_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	id_type; 
	uint32_t	id; 

}  __attribute__ ((packed));

struct pcan_usbpro_lookup_group_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	id_type; 
	uint32_t	id_start; 
	uint32_t	id_end; 

}  __attribute__ ((packed));

struct pcan_usbpro_filter_mode_t
{
	uint8_t	data_type;
	uint8_t	dummy;
	uint16_t	filter_mode; 

}  __attribute__ ((packed));

struct pcan_usbpro_reset_mode_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	reset; 

}  __attribute__ ((packed));

struct pcan_usbpro_error_frame_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	mode; 

}  __attribute__ ((packed));

struct pcan_usbpro_error_status_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	status; 

}  __attribute__ ((packed));

struct pcan_usbpro_set_register_t
{
	uint8_t	data_type;
	uint8_t	irq_off;
	uint16_t	dummy;
	uint32_t address;
	uint32_t value;
	uint32_t mask;

}  __attribute__ ((packed));

struct pcan_usbpro_get_register_t
{
	uint8_t	data_type;
	uint8_t	irq_off;
	uint16_t	dummy;
	uint32_t address;
	uint32_t value;

}  __attribute__ ((packed));

struct pcan_usbpro_calibration_t
{
	uint8_t	data_type;
	uint8_t	dummy;
	uint16_t	mode;

}  __attribute__ ((packed));

struct pcan_usbpro_buslast_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint8_t	dummy; 
	uint8_t	mode;
	uint16_t	prescaler;
	uint16_t	sampletimequanta;

}  __attribute__ ((packed));

struct pcan_usbpro_set_string_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint8_t	offset; 
	uint8_t	len;
	uint8_t	data[60];

}  __attribute__ ((packed));

struct pcan_usbpro_get_string_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	dummy;

}  __attribute__ ((packed));

struct pcan_usbpro_string_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	dummy;
	uint8_t	data[250];

}  __attribute__ ((packed));

struct pcan_usbpro_save_eeprom_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	dummy;

}  __attribute__ ((packed));

struct pcan_usbpro_packet_delay_t
{
	uint8_t	data_type;
	uint8_t	dummy;
	uint16_t	delay;

}  __attribute__ ((packed));

struct pcan_usbpro_timestamp_param_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	start_or_end;

}  __attribute__ ((packed));

struct pcan_usbpro_error_gen_id_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	bit_pos;
	uint32_t	id;
	uint16_t	ok_counter;
	uint16_t	error_counter;

}  __attribute__ ((packed));

struct pcan_usbpro_error_gen_now_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	bit_pos;

}  __attribute__ ((packed));

struct pcan_usbpro_softfiler_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	dummy;
	uint32_t	accmask;
	uint32_t	acccode;

}  __attribute__ ((packed));

struct pcan_usbpro_set_can_led_t
{
	uint8_t	data_type;
	uint8_t	channel;                   /* Bit(3..0)-> can channel */
	uint16_t	mode;
	uint32_t	timeout;

}  __attribute__ ((packed));

union pcan_usbpro_rec_t
{
	uint8_t	                           data_type;
	struct pcan_usbpro_canmsg_rx_t      canmsg_rx;
	struct pcan_usbpro_canmsg_status_error_rx_t canmsg_status_error_rx;
	struct pcan_usbpro_calibration_ts_rx_t calibration_ts_rx;
	struct pcan_usbpro_buslast_rx_t     buslast_rx;
	struct pcan_usbpro_canmsg_tx_t      canmsg_tx;
	struct pcan_usbpro_baudrate_t       baudrate;
	struct pcan_usbpro_bus_activity_t   bus_activity;
	struct pcan_usbpro_silent_mode_t    silent_mode;
	struct pcan_usbpro_dev_nr_t         dev_nr;
	struct pcan_usbpro_warning_limit_t  warning_limit;
	struct pcan_usbpro_lookup_explicit_t lookup_explicit;
	struct pcan_usbpro_lookup_group_t   lookup_group;
	struct pcan_usbpro_filter_mode_t    filer_mode;
	struct pcan_usbpro_reset_mode_t     reset_mode;
	struct pcan_usbpro_error_frame_t    error_frame;
	struct pcan_usbpro_error_status_t   error_status;
	struct pcan_usbpro_set_register_t	set_register;
	struct pcan_usbpro_get_register_t   get_register;
	struct pcan_usbpro_calibration_t    calibration;
	struct pcan_usbpro_buslast_t        buslast;
	struct pcan_usbpro_set_string_t     set_string;
	struct pcan_usbpro_get_string_t     get_string;
	struct pcan_usbpro_string_t         string;
	struct pcan_usbpro_save_eeprom_t    save_eeprom;
	struct pcan_usbpro_packet_delay_t   packet_delay;
	struct pcan_usbpro_timestamp_param_t timestamp_param;
	struct pcan_usbpro_error_gen_id_t   error_gen_id;
	struct pcan_usbpro_error_gen_now_t  error_gen_now;
	struct pcan_usbpro_softfiler_t      softfiler;
	struct pcan_usbpro_set_can_led_t    set_can_led;

}  __attribute__ ((packed));

#endif /* __pcan_usbpro_fw_h */
