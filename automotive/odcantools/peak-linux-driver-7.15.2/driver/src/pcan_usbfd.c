/*****************************************************************************
 * Copyright (C) 2014 PEAK System-Technik GmbH
 *
 * linux@peak-system.com
 * www.peak-system.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Maintainer(s): Stephane Grosjean (s.grosjean@peak-system.com)
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * pcan_usbfd.c - the inner parts for PCAN-USB (Pro) FD support
 *
 * $Id: pcan_usbfd_fd.c 615 2011-02-10 22:38:55Z stephane $
 *
 *****************************************************************************/
/* #define DEBUG */
/* #undef DEBUG */

/*
 * INCLUDES
 */
#include "src/pcan_common.h"
#include <linux/sched.h>
#include "src/pcan_main.h"
#include "src/pcan_fifo.h"
#include "src/pcan_usbfd.h"

#ifdef NETDEV_SUPPORT
#include "src/pcan_netdev.h"		/* for hotplug pcan_netdev_register() */
#else
#include <linux/can/dev.h>
#endif

#include "src/pcan_usbfd_fw.h"		/* PCAN-USB (Pro) FD fw structures */
#include "src/pcan_usbpro_fw.h"
#include "src/pcan_timing.h"		/* timing conversion */

/*
 * DEFINES
 */

/* if defined, tell how timestamp are handled */
/*#define PCAN_USBFD_DEBUG_TIMESTAMP */

/* if defined, tell how incoming messages and records are handled */
/*#define PCAN_USBFD_DEBUG_DECODE */

#define PCAN_USBFD_PRECISION_MASK	0x7ff

#define PCAN_USBFD_CMD_TIMEOUT		1000	/* ms to for USB requests */
#define TICKS(msec)			((msec * HZ) / 1000)

/* device state flags */
#define PCAN_USBFD_SHOULD_WAKEUP	0x00000001UL

/* pcan_usbfd_send_cmd_ex() flags */
#define PCAN_USBFD_SEND_SYNC_MODE	0x00000001
#define PCAN_USBFD_SEND_GET_TOD		0x00000002

#ifndef get_can_dlc
/* some (very) old Kernels don't #define get_can_dlc() */
#define get_can_dlc(i)			(min_t(__u8, (i), 8))
#endif

/*
 * Private Data Structures
 */
struct pcan_usbfd_fw_info {
	u16	size_of;	/* sizeof this */
	u16	type;		/* type of thsi structure */
	u8	hw_type;	/* Type of hardware (HW_TYPE_xxx) */
	u8	bl_version[3];	/* Bootloader version */
	u8	hw_version;	/* Hardware version (PCB) */
	u8	fw_version[3];	/* Firmware version */
	u32	dev_id[2];	/* "device id" per CAN */
	u32	ser_no;		/* S/N */
	u32	flags;		/* special functions */
} __attribute__ ((packed));

/* Use several things from PCAN-USB Pro */
extern void pcan_usbpro_driver_loaded(struct pcan_usb_interface *usb_if,
					int can_lin, int loaded);
extern int pcan_usbpro_request(struct pcan_usb_interface *usb_if,
				int req_id, int req_value,
				void *req_addr, int req_size);

extern void pcan_usbpro_timestamp_decode(struct pcan_usb_interface *usb_if,
					u32 ts_us, struct timeval *tv);

extern u32 pcan_usbpro_handle_response_rtt(struct pcan_usb_interface *usb_if);
extern void pcan_usbpro_time_sync(struct pcan_usb_interface *usb_if,
			struct timeval *tv, u32 ts_us, u32 dev_frame_nb);

/* Adapter timinig capabilities */
static struct pcan_timing_capabilities pcan_slow_capabilities = {
	.min_tseg1 = 1,
	.max_tseg1 = 64,
	.min_tseg2 = 1,
	.max_tseg2 = 16,
	.min_sjw = 1,
	.max_sjw = 16,
	.min_brp = 1,
	.max_brp = 1024,

	.intern_prescaler = 1
};

/*
 * Private Functions
 */
#define pcan_usbfd_send_cmd(a, b)\
		pcan_usbfd_send_cmd_ex(a, b, PCAN_USBFD_SEND_SYNC_MODE)
#define pcan_usbfd_send_cmd_async(a, b)\
		pcan_usbfd_send_cmd_ex(a, b, 0)

/*
 * URB status (LDD3 p339):
 * 0
 * -ENOENT(2)			The URB was stopped by call to usb_kill_urb()
 * -EOVERFLOW(75)		Too large packet
 * -EINPROGRESS(115)		The URB is always being processed by device
 */

/*
 * static void pcan_usbfd_submit_cmd_end(struct urb *purb,
 *							struct pt_regs *regs)
 *
 * Called when URB has been submitted to hardware
 */
static void pcan_usbfd_submit_cmd_end(struct urb *purb, struct pt_regs *regs)
{
	struct pcan_usb_interface *usb_if = purb->context;

	DPRINTK(KERN_DEBUG "%s: %s() = %d\n",
		 DEVICE_NAME, __func__, purb->status);

	/* un-register outstanding urb */
	atomic_dec(&usb_if->active_urbs);

	if (purb == &usb_if->urb_cmd_async)
		atomic_set(&usb_if->cmd_async_complete, 1);
	else
		atomic_set(&usb_if->cmd_sync_complete, 1);
}

/*
 * static int pcan_usbfd_send_cmd_ex(struct pcan_usb_interface *usb_if,
 *					void *cmd_tail, u32 flags)
 */
static int pcan_usbfd_send_cmd_ex(struct pcan_usb_interface *usb_if,
					void *cmd_tail, u32 flags)
{
	void *cmd_head = usb_if->cout_baddr;
	struct urb *urb;
	u32 ms_timeout;
	int err = 0, cmd_len;

	DPRINTK(KERN_DEBUG "%s: %s(): ->EP#%02X\n", DEVICE_NAME, __func__,
		 usb_if->pipe_cmd_out.ucNumber);

	/* don't do anything with non-existent hardware */
	if (!usb_if->dev[0].ucPhysicallyInstalled)
		return -ENODEV;

	if (!(flags & PCAN_USBFD_SEND_SYNC_MODE)) {
		if (!atomic_read(&usb_if->cmd_async_complete))
			return -EWOULDBLOCK;

		urb = &usb_if->urb_cmd_async;
	} else {
		urb = &usb_if->urb_cmd_sync;
	}

	/*
	 * if a packet is not filled completely by commands, the command list
	 * is terminated with an "end of collection" record.
	 */
	cmd_len = cmd_tail - cmd_head;
	if (cmd_len < usb_if->cout_bsize) {
		memset(cmd_tail, 0xff, sizeof(u64));
		cmd_len += sizeof(u64);
	}

#ifdef DEBUG
	dump_mem("sent message", cmd_head, cmd_len);
#endif
	/* firmware is not able to re-assemble 512 bytes buffer in full-speed */
	if ((usb_if->usb_dev->speed != USB_SPEED_HIGH) && (cmd_len > 64)) {
		printk(KERN_ERR
		"%s: Warning: too large cmd (%dB) to be sent (discarded!)\n",
			DEVICE_NAME, cmd_len);
		return -EMSGSIZE;
	}

	FILL_BULK_URB(urb, usb_if->usb_dev,
			usb_sndbulkpipe(usb_if->usb_dev,
					usb_if->pipe_cmd_out.ucNumber),
			cmd_head, cmd_len,
			pcan_usbfd_submit_cmd_end, usb_if);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,8)
	urb->timeout = TICKS(PCAN_USBFD_CMD_TIMEOUT);
#endif

	if (flags & PCAN_USBFD_SEND_GET_TOD)
		DO_GETTIMEOFDAY(usb_if->tv_request);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err) {
		printk(KERN_ERR "%s: %s(): usb_submit_urb() failure error %d\n",
			DEVICE_NAME, __func__, err);
		goto fail;
	}

	atomic_inc(&usb_if->active_urbs);

	/* check if we need to wait for completion */
	if (!(flags & PCAN_USBFD_SEND_SYNC_MODE))
		return 0;

	/* wait until submit is finished, either normal or thru timeout */
	ms_timeout = get_mtime() + PCAN_USBFD_CMD_TIMEOUT;
	while (!atomic_read(&usb_if->cmd_sync_complete)) {
		schedule();

		if (get_mtime() >= ms_timeout) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,10)
			usb_kill_urb(urb);
#else
			usb_unlink_urb(urb);
#endif
			break;
		}
	}

fail:
	err = urb->status;

	atomic_set(&usb_if->cmd_sync_complete, 0);

	return err;
}

/*
 * Hardware Callbacks
 */
static int pcan_usbfd_set_can_on(struct pcandev *dev)
{
	USB_PORT *u = &dev->port.usb;
	u8 *pc = u->usb_if->cout_baddr;
	struct pucan_command *cmd;
	struct pucan_wr_err_cnt *prc;

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d)\n", DEVICE_NAME, __func__,
		u->dev_ctrl_index);

	/* 1st, reset error counters */
	prc = (struct pucan_wr_err_cnt *)pc;
	prc->opcode_channel =
		PUCAN_CMD_OPCODE_CHANNEL(u->dev_ctrl_index,
					 PUCAN_CMD_WR_ERR_CNT);
	/* select both counters */
	prc->sel_mask = cpu_to_le16(PUCAN_WRERRCNT_TE|PUCAN_WRERRCNT_RE);

	/* and reset their values */
	prc->tx_counter = 0;
	prc->rx_counter = 0;

	/* moves the pointer forward */
	pc += sizeof(struct pucan_wr_err_cnt);

	/* next, go back to operational mode */
	cmd = (struct pucan_command *)pc;
	cmd->opcode_channel =
		PUCAN_CMD_OPCODE_CHANNEL(u->dev_ctrl_index,
			(dev->ucListenOnly) ? PUCAN_CMD_LISTEN_ONLY_MODE :
					      PUCAN_CMD_NORMAL_MODE);

	/* send the command */
	pc += sizeof(struct pucan_command);
	return pcan_usbfd_send_cmd(u->usb_if, pc);
}

static int pcan_usbfd_set_can_off(struct pcandev *dev)
{
	USB_PORT *u = &dev->port.usb;
	struct pucan_command *cmd = \
			(struct pucan_command *)u->usb_if->cout_baddr;

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d)\n", DEVICE_NAME, __func__,
		u->dev_ctrl_index);

	cmd->opcode_channel = PUCAN_CMD_OPCODE_CHANNEL(u->dev_ctrl_index,
							PUCAN_CMD_RESET_MODE);

	/*
	 * wait a bit for last data to be written on CAN bus
	 * (5 ms is not enough if any dfata buffer was almost filled)
	 * */
	if (dev->dwInterruptCounter > 0)
		mdelay(10);

	/* send the command */
	return pcan_usbfd_send_cmd(u->usb_if, ++cmd);
}

/*
 * int pcan_usbfd_set_filter_std(struct pcandev *dev, int idx, u32 mask)
 */
static int pcan_usbfd_set_filter_std(struct pcandev *dev, int idx, u32 mask)
{
	USB_PORT *u = &dev->port.usb;
	struct pucan_filter_std *cmd = \
			(struct pucan_filter_std *)u->usb_if->cout_baddr;
	int i, n;

	/* not able t set any filtering criteria, according to Win driver */
	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d, idx=%d mask=%08xh)\n",
		DEVICE_NAME, __func__,
		u->dev_ctrl_index, idx, mask);

	/* select all rows when idx is out of range */
	if ((idx < 0) || (idx >= (1 << PUCAN_FLTSTD_ROW_IDX_BITS))) {
		n = 1 << PUCAN_FLTSTD_ROW_IDX_BITS;
		idx = 0;

	/* select the row otherwise */
	} else {
		n = idx + 1;
	}

	for (i = idx; i < n; i++, cmd++) {
		cmd->opcode_channel = \
			PUCAN_CMD_OPCODE_CHANNEL(u->dev_ctrl_index,
						 PUCAN_CMD_FILTER_STD);
		cmd->idx = i;
		cmd->mask = cpu_to_le32(mask);
	}

	/* send the command */
	return pcan_usbfd_send_cmd(u->usb_if, cmd);
}

/*
 * set/unset notifications filter:
 *
 *	onoff	sets(1)/unset(0) notifications
 *	mask	each bit defines a kind of notification to set/unset
 */
static int pcan_usbfd_set_filter_ext(struct pcandev *dev,
					 int onoff, u16 ext_mask, u16 usb_mask)
{
	USB_PORT *u = &dev->port.usb;
	struct pcan_usbfd_filter_ext *cmd = \
			(struct pcan_usbfd_filter_ext *)u->usb_if->cout_baddr;

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d): "
		"ext_mask=0x%08xh usb_mask=0x%08xh\n",
		DEVICE_NAME, __func__,
		u->dev_ctrl_index, ext_mask, usb_mask);

	cmd->opcode_channel = PUCAN_CMD_OPCODE_CHANNEL(u->dev_ctrl_index,
				(onoff) ? PUCAN_CMD_RX_FRAME_ENABLE :
						PUCAN_CMD_RX_FRAME_DISABLE);
	cmd->ext_mask = cpu_to_le16(ext_mask);
	cmd->usb_mask = cpu_to_le16(usb_mask);

	/* send the command */
	return pcan_usbfd_send_cmd(u->usb_if, ++cmd);
}

/*
 * int pcan_usbfd_set_can_led(struct pcandev *dev, u8 mode )
 */
static int pcan_usbfd_set_can_led(struct pcandev *dev, u8 mode)
{
	USB_PORT *u = &dev->port.usb;
	struct pcan_usbfd_led *cmd = \
			(struct pcan_usbfd_led *)u->usb_if->cout_baddr;

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d)\n", DEVICE_NAME, __func__,
		u->dev_ctrl_index);

	cmd->opcode_channel = PUCAN_CMD_OPCODE_CHANNEL(u->dev_ctrl_index,
							PCAN_USBFD_CMD_LED_SET);
	cmd->mode = mode;

	/* send the command */
	return pcan_usbfd_send_cmd(u->usb_if, ++cmd);
}

/*
 * int pcan_usbfd_get_fw_info(struct pcan_usb_interface *usb_if,
 *						int should_print)
 */
static int pcan_usbfd_get_fw_info(struct pcan_usb_interface *usb_if,
					int should_print)
{
	int err;
	struct pcan_usbfd_fw_info *pfi = \
			(struct pcan_usbfd_fw_info *)usb_if->cout_baddr;

	err = pcan_usbpro_request(usb_if,
				USB_VENDOR_REQUEST_INFO,
				USB_VENDOR_REQUEST_wVALUE_INFO_FIRMWARE,
				pfi, sizeof(*pfi));
	if (err >= 0) {

		if (should_print)
			pr_info("%s: %s (%02xh PCB%02Xh) fw v%d.%d.%d\n",
				DEVICE_NAME, usb_if->adapter_name,
				pfi->hw_type, pfi->hw_version,
				pfi->fw_version[0], pfi->fw_version[1],
				pfi->fw_version[2]);

		/* save device id and serial num  info for further read */
		usb_if->dwSerialNumber = le32_to_cpu(pfi->ser_no);
		usb_if->ucRevision = pfi->hw_version;
		usb_if->dev[0].port.usb.ucHardcodedDevNr = pfi->dev_id[0];
		usb_if->dev[1].port.usb.ucHardcodedDevNr = pfi->dev_id[1];

		return 0;
	}

	return  err;
}


/*
 * int pcan_usbfd_get_device_nr(struct pcandev *dev, u32 *p_device_nr)
 */
static int pcan_usbfd_get_device_nr(struct pcandev *dev, u32 *p_device_nr)
{
	USB_PORT *u = &dev->port.usb;
	int err;

	err = pcan_usbfd_get_fw_info(u->usb_if, 0);
	if (!err) {
		struct pcan_usbfd_fw_info *pfi = \
			(struct pcan_usbfd_fw_info *)u->usb_if->cout_baddr;

		u32 tmp32 = le32_to_cpu(pfi->dev_id[u->dev_ctrl_index]);

#ifdef PCAN_DEV_USES_ALT_NUM
		if (tmp32 != 0xffffffff) {
			dev->device_alt_num = tmp32;
			dev->flags |= PCAN_DEV_USES_ALT_NUM;
		}

#endif
		if (p_device_nr)
			*p_device_nr = tmp32;
	}

	return err;
}

/*
 * int pcan_usbfd_set_device_nr(struct pcandev *dev, u32 device_nr)
 */
static int pcan_usbfd_set_device_nr(struct pcandev *dev, u32 device_nr)
{
	USB_PORT *u = &dev->port.usb;
	struct pcan_usbfd_device_id *cmd = \
		(struct pcan_usbfd_device_id *)u->usb_if->cout_baddr;

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d, 0x%x)\n",
		 DEVICE_NAME, __func__, u->dev_ctrl_index, device_nr);

	cmd->opcode_channel = PUCAN_CMD_OPCODE_CHANNEL(u->dev_ctrl_index,
						PCAN_USBFD_CMD_DEVID_SET);
	cmd->device_id = cpu_to_le32(device_nr);

	/* send the command */
	return pcan_usbfd_send_cmd(u->usb_if, ++cmd);
}

/*
 * int pcan_usbfd_get_serial_nr(struct pcan_usb_interface *usb_if,
 *					u32 *p_serial_num)
 *
 * Retrieve serial number from bootloader info
 */
static int pcan_usbfd_get_serial_nr(struct pcan_usb_interface *usb_if,
					u32 *p_serial_num)
{
	int err;

	err = pcan_usbfd_get_fw_info(usb_if, 0);
	if (!err) {
		if (p_serial_num)
			*p_serial_num = usb_if->dwSerialNumber;
	}

	return err;
}

#ifdef PCAN_USBFD_CMD_SN_SET
/*
 * int pcan_usbfd_set_serial_nr(struct pcan_usb_interface *usb_if,
 *					u32 serial_num)
 */
static int pcan_usbfd_set_serial_nr(struct pcan_usb_interface *usb_if,
					u32 serial_nr)
{
	struct pcan_usbfd_serial_num *cmd = \
		(struct pcan_usbfd_serial_num *)usb_if->cout_baddr;

	DPRINTK(KERN_DEBUG "%s: %s(): 0x%x\n",
		 DEVICE_NAME, __func__, serial_nr);

	cmd->opcode_channel = PUCAN_CMD_OPCODE_CHANNEL(0,
							PCAN_USBFD_CMD_SN_SET);
	cmd->serial_num = cpu_to_le32(serial_nr);

	/* send the command */
	return pcan_usbfd_send_cmd(usb_if, ++cmd);
}
#endif

/*
 */
static int pcan_usbfd_set_clock_domain(struct pcandev *dev, u8 clk_mode)
{
	USB_PORT *u = &dev->port.usb;
	struct pcan_usb_pro_fd_clock *cmd = \
		(struct pcan_usb_pro_fd_clock *)u->usb_if->cout_baddr;

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d, 0x%x)\n",
		 DEVICE_NAME, __func__, u->dev_ctrl_index, clk_mode);

	cmd->opcode_channel = PUCAN_CMD_OPCODE_CHANNEL(u->dev_ctrl_index,
							PCAN_USBFD_CMD_CLK_SET);
	cmd->mode = clk_mode;

	/* send the command */
	return pcan_usbfd_send_cmd(u->usb_if, ++cmd);
}

/*
 * int pcan_usbfd_set_timing_slow(struct pcandev *dev,
 *					struct pcan_timing_baudrate *pbr)
 */
static int pcan_usbfd_set_timing_slow(struct pcandev *dev,
					struct pcan_timing_baudrate *pbr)
{
	USB_PORT *u = &dev->port.usb;
	struct pucan_timing_slow *cmd = \
			(struct pucan_timing_slow *)u->usb_if->cout_baddr;

#ifdef DEBUG
	printk(KERN_DEBUG "%s: "
		"%s(CAN#%d): sjw=%u tseg1=%u tseg2=%u brp=%u sam=%u clk=%u\n",
		DEVICE_NAME, __func__, u->dev_ctrl_index,
		pbr->SJW, pbr->TSEG1, pbr->TSEG2, pbr->BRP, pbr->SAM,
		pbr->can_systemclock);
#endif

	cmd->opcode_channel = PUCAN_CMD_OPCODE_CHANNEL(u->dev_ctrl_index,
							PUCAN_CMD_TIMING_SLOW);

	cmd->sjw_t = PUCAN_TSLOW_SJW_T(pbr->SJW - 1, pbr->SAM);
	cmd->tseg1 = PUCAN_TSLOW_TSEG1(pbr->TSEG1 - 1);
	cmd->tseg2 = PUCAN_TSLOW_TSEG2(pbr->TSEG2 - 1);
	cmd->brp = PUCAN_TSLOW_BRP(pbr->BRP - 1);

	cmd->ewl = 96;	/* default */

	/* send the command */
	return pcan_usbfd_send_cmd(u->usb_if, ++cmd);
}

static int pcan_usbfd_convert_16MHzBTR0BTR1(u16 btr0btr1,
					struct pcan_timing_capabilities *pcap,
					struct pcan_timing_baudrate *pbr)
{
	struct pcan_timing_abstract at_original, at_convert;
	const u32 chip_quartz_frequency = 80*MHz;

	pcan_BTR0BTR1_to_abstract(btr0btr1, &at_original);

	if (!pcan_timing_convert_br_settings(pcap, &at_original,
					chip_quartz_frequency, &at_convert))
		return -EINVAL;

	return pcan_abstract_to_sja(pcap,
				&at_convert,
				chip_quartz_frequency,
				pbr);
}

#if 0
#define BTR0BTR1_1MBPS		0x0014
#define BTR0BTR1_500KBPS	0x001c
#define BTR0BTR1_250KBPS	0x011c
#endif
/*
 * int pcan_usbfd_set_BTR0BTR1(struct pcandev *dev, u16 btr0btr1)
 */
static int pcan_usbfd_set_BTR0BTR1(struct pcandev *dev, u16 btr0btr1)
{
	USB_PORT *u = &dev->port.usb;
	struct pcan_timing_baudrate bitrate;
	int err;

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d, 0x%04x)\n",
		 DEVICE_NAME, __func__, u->dev_ctrl_index, btr0btr1);

	switch (btr0btr1) {

#ifdef BTR0BTR1_1MBPS
	case BTR0BTR1_1MBPS:
		bitrate.SAM = 0;
		bitrate.SJW = 1;
		bitrate.TSEG1 = 29;
		bitrate.TSEG2 = 10;
		bitrate.BRP = 2;
		break;
#endif
#ifdef BTR0BTR1_500KBPS
	case BTR0BTR1_500KBPS:
		bitrate.SAM = 0;
		bitrate.SJW = 1;
		bitrate.TSEG1 = 34;
		bitrate.TSEG2 = 5;
		bitrate.BRP = 4;
		break;
#endif
	default:

		/* Need to convert this value for PCAN-USB (Pro) FD */
		if (!pcan_usbfd_convert_16MHzBTR0BTR1(btr0btr1,
					&pcan_slow_capabilities, &bitrate)) {
			printk(KERN_ERR "%s: "
				"unable to convert BTR0BTR1 0x%04x\n",
				DEVICE_NAME, btr0btr1);
			printk(KERN_ERR "%s: "
				"won't be able to transfer data on CAN#%d\n",
				DEVICE_NAME, u->dev_ctrl_index);

			return -EINVAL;
		}
	}

	err = pcan_usbfd_set_timing_slow(dev, &bitrate);
	return err;
}

/*
 * int pcan_usbfd_open(struct pcandev *dev, u16 btr0btr1, u8 listen_only)
 */
static int pcan_usbfd_open(struct pcandev *dev, u16 btr0btr1,
				u8 listen_only)
{
	USB_PORT *u = &dev->port.usb;
	u16 usb_mask = 0;
	int err = 0;

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d, btr0btr1=0x%04x, listen_only=%d)\n",
		 DEVICE_NAME, __func__, u->dev_ctrl_index, btr0btr1,
		listen_only);

	err = pcan_usbfd_set_BTR0BTR1(dev, btr0btr1);
	if (err)
		goto fail;

	/* Set filter mode: accept all */
	err = pcan_usbfd_set_filter_std(dev, -1, 0xffffffff);
	if (err)
		goto fail;

	/* if first device opened, ask for being notified of calibration msgs */
	if (u->usb_if->dev_opened_count < 1)
		usb_mask |= PCAN_USBFD_FLTEXT_CALIBRATION;

	/* ask for being notified of error messages */
	err = pcan_usbfd_set_filter_ext(dev, 1,
						PUCAN_FLTEXT_ERROR, usb_mask);
fail:
	return err;
}

/*
 * int pcan_usbfd_close(struct pcandev *dev)
 */
static int pcan_usbfd_close(struct pcandev *dev)
{
	USB_PORT *u = &dev->port.usb;
	u16 usb_mask = 0;

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d): opened_count=%d\n",
		 DEVICE_NAME, __func__,
		u->dev_ctrl_index, u->usb_if->dev_opened_count);

	/* if last device opened, disable calibration msgs */
	if (u->usb_if->dev_opened_count <= 1)
		usb_mask |= PCAN_USBFD_FLTEXT_CALIBRATION;

	/* turn off notfications */
	pcan_usbfd_set_filter_ext(dev, 0, PUCAN_FLTEXT_ERROR, usb_mask);

	return 0;
}

/*
 * void pcan_usbfd_timestamp_decode(struct pcan_usb_interface *usb_if,
 *						u32 ts_us,
 *						struct timeval *tv)
 */
static void pcan_usbfd_timestamp_decode(struct pcan_usb_interface *usb_if,
						u32 ts_us, struct timeval *tv)
{
	pcan_usbpro_timestamp_decode(usb_if, ts_us, tv);
}

static int pcan_usbfd_decode_canmsg(struct pcan_usb_interface *usb_if,
					struct pucan_msg *rx_msg)
{
	struct pucan_rx_msg *rm = (struct pucan_rx_msg *)rx_msg;
	struct pcandev *dev = &usb_if->dev[PUCAN_MSG_CHANNEL(rm)];
	struct can_frame cf;
	struct timeval tv;
	u32 flags = 0;
	int err;

#if 1//def DEBUG
	printk(KERN_DEBUG "%s: %s(): "
		"rx=[flags=0x%02x len=0x%02x ts32=0x%08x id=0x%08x]\n",
			DEVICE_NAME,__func__, rm->flags, PUCAN_MSG_DLC(rm),
		 le32_to_cpu(rm->ts_low), le32_to_cpu(rm->can_id));
#endif
	dev->dwInterruptCounter++;

	/* Don't send any message when device not opened */
	if (dev->nOpenPaths <= 0) {
		pr_info("%s: incoming message 0x%x (flags=%x) discarded: "
			 "CAN#%d not yet opened\n",
			 DEVICE_NAME, le32_to_cpu(rm->can_id), rm->flags,
			PUCAN_MSG_CHANNEL(rm));
		return 0;
	}

	memset(&cf, '\0', sizeof(cf));

	/* CAN 2.0 frame case */
	cf.can_dlc = get_can_dlc(PUCAN_MSG_DLC(rm));
	cf.can_id = le32_to_cpu(rm->can_id);

	if (rm->flags & PUCAN_MSG_EXT_ID)
		cf.can_id |= CAN_EFF_FLAG;

	if (rm->flags & PUCAN_MSG_RTR)
		cf.can_id |= CAN_RTR_FLAG;
	else
		memcpy(cf.data, rm->d, cf.can_dlc);

	if (rm->flags & PUCAN_MSG_HW_SRR)
		flags |= MSGTYPE_SELFRECEIVE;

	pcan_usbfd_timestamp_decode(usb_if, le32_to_cpu(rm->ts_low), &tv);
#ifdef DEBUG
	dump_mem("received CAN frame", &cf, sizeof(struct can_frame));
#endif
	err = pcan_xxxdev_rx_ex(dev, (struct can_frame *)&cf, &tv, flags);
	if (err >= 0)
		dev->port.usb.state |= PCAN_USBFD_SHOULD_WAKEUP;
	else {
		printk(KERN_ERR
			"%s: CAN frame lost: failed to deliver msg (err %d)\n",
			DEVICE_NAME, err);
	}

	return err;
}

/* handle uCAN status message */
static int pcan_usbfd_decode_status(struct pcan_usb_interface *usb_if,
					 struct pucan_msg *rx_msg)
{
	struct pucan_status_msg *st = (struct pucan_status_msg *)rx_msg;
	struct pcandev *dev = &usb_if->dev[PUCAN_STMSG_CHANNEL(st)];
	struct can_frame cf;
	struct timeval tv;
	int err;

	DPRINTK(KERN_DEBUG "%s: %s(): "
		"ts32=0x%08x EP=%u EW=%u BO=%u]\n",
		DEVICE_NAME,__func__,
		le32_to_cpu(st->ts_low), !!PUCAN_STMSG_PASSIVE(st),
		!!PUCAN_STMSG_WARNING(st), !!PUCAN_STMSG_BUSOFF(st));

	memset(&cf, '\0', sizeof(struct can_frame));

	if (PUCAN_STMSG_BUSOFF(st)) {
		cf.can_id |= CAN_ERR_BUSOFF;
	} else if (PUCAN_STMSG_PASSIVE(st)) {
		cf.can_id |= CAN_ERR_CRTL;
		if (dev->rx_error_counter > 127)
			cf.data[1] |= CAN_ERR_CRTL_RX_PASSIVE;
		if (dev->tx_error_counter > 127)
			cf.data[1] |= CAN_ERR_CRTL_TX_PASSIVE;
	} else if (PUCAN_STMSG_WARNING(st)) {
		cf.can_id |= CAN_ERR_CRTL;
		if (dev->rx_error_counter > 96)
			cf.data[1] |= CAN_ERR_CRTL_RX_WARNING;
		if (dev->tx_error_counter > 96)
			cf.data[1] |= CAN_ERR_CRTL_TX_WARNING;
	} else {
		/* no error bit (so, no error, back to active state) */
		dev->tx_error_counter = dev->rx_error_counter = 0;
		atomic_set(&dev->DataSendReady, 1);
		return 0;
	}

	dev->dwErrorCounter++;
	dev->wCANStatus = le16_to_cpu(st->type);

	pcan_usbfd_timestamp_decode(usb_if, le32_to_cpu(st->ts_low), &tv);

	err = pcan_xxxdev_rx(dev, &cf, &tv);
	if (err >= 0)
		dev->port.usb.state |= PCAN_USBFD_SHOULD_WAKEUP;

	return err;
}

/* handle uCAN error message */
static int pcan_usbfd_decode_error(struct pcan_usb_interface *usb_if,
					struct pucan_msg *rx_msg)
{
	struct pucan_error_msg *er = (struct pucan_error_msg *)rx_msg;
	struct pcandev *dev = &usb_if->dev[PUCAN_ERMSG_CHANNEL(er)];

#ifdef DEBUG
	printk(KERN_DEBUG "%s: %s(): "
		"rx=[type=0x%02x ts32=0x%08x d=%u g=%u code=0x%02x "
		"err_cnt[rx=%u tx=%u]]\n",
		DEVICE_NAME, __func__,
		PUCAN_ERMSG_ERRTYPE(er), le32_to_cpu(er->ts_low),
		PUCAN_ERMSG_D(er)?1:0,
		PUCAN_ERMSG_G(er)?1:0,
		PUCAN_ERMSG_ERRCODE(er),
		er->rx_err_cnt, er->tx_err_cnt);
#endif

	if ((dev->tx_error_counter == er->tx_err_cnt) &&
				(dev->rx_error_counter == er->rx_err_cnt))
		return 0;

	/* keep a trace of tx and rx error counters for later use */
	dev->tx_error_counter = er->tx_err_cnt;
	dev->rx_error_counter = er->rx_err_cnt;

	return 0;
}

/* handle uCAN overrun message */
static int pcan_usbfd_decode_overrun(struct pcan_usb_interface *usb_if,
						struct pucan_msg *rx_msg)
{
	struct pcan_usbfd_ovr_msg *ov = (struct pcan_usbfd_ovr_msg *)rx_msg;
	struct pcandev *dev = &usb_if->dev[PCAN_USBFD_OVMSG_CHANNEL(ov)];
	struct can_frame cf;
	struct timeval tv;
	int err;

	DPRINTK(KERN_DEBUG "%s: %s(): "
		"ts_low=0x%08x ts_high=0x%08x\n",
		DEVICE_NAME, __func__,
		le32_to_cpu(ov->ts_low), le32_to_cpu(ov->ts_high));

	dev->dwInterruptCounter++;

	/* Don't send any message when device not opened */
	if (dev->nOpenPaths <= 0) {
		pr_info("%s: ovr	msg status discarded: "
			"CAN#%d not yet opened\n",
			DEVICE_NAME, PCAN_USBFD_OVMSG_CHANNEL(ov));
		return 0;
	}

	memset(&cf, '\0', sizeof(struct can_frame));
	cf.can_id = CAN_ERR_FLAG|CAN_ERR_CRTL;
	cf.can_dlc = CAN_ERR_DLC;
	cf.data[1] |= CAN_ERR_CRTL_RX_OVERFLOW;
	dev->dwErrorCounter++;

	pcan_usbfd_timestamp_decode(usb_if, le32_to_cpu(ov->ts_low), &tv);

	err = pcan_xxxdev_rx(dev, &cf, &tv);
	if (err >= 0)
		dev->port.usb.state |= PCAN_USBFD_SHOULD_WAKEUP;

	return err;
}

/* handle USB calibration message */
static void pcan_usbfd_decode_ts(struct pcan_usb_interface *usb_if,
					struct pucan_msg *rx_msg)
{
	struct pcan_usbfd_ts_msg *ts = (struct pcan_usbfd_ts_msg *)rx_msg;
	const u16 raw_frame_index = le16_to_cpu(ts->usb_frame_index);
	u16 dev_frame_nb;

	DPRINTK(KERN_DEBUG
		"%s: got calibration message: ts=0x%08x-%08x fr=%u/0x%x\n",
		DEVICE_NAME,
		le32_to_cpu(ts->ts_low), le32_to_cpu(ts->ts_high),
		raw_frame_index, raw_frame_index);

	/* should wait until clock is stabilized */
	if (usb_if->cm_ignore_count > 0) {
		usb_if->cm_ignore_count--;
		return;
	}

	/*
	 * use this message to compute RTT (here time diff between tv_request &
	 * tv_response) before doing synchronization
	 */
	pcan_usbpro_handle_response_rtt(usb_if);

	dev_frame_nb = raw_frame_index & PCAN_USBFD_PRECISION_MASK;

	pcan_usbpro_time_sync(usb_if, &usb_if->tv_response,
				 le32_to_cpu(ts->ts_low), dev_frame_nb);
}

/*
 * int pcan_usbfd_msg_decode(struct pcan_usb_interface *usb_if,
 *				u8 *msg_addr, int msg_len)
 *
 * Decode a message from PCAN-USB (Pro) FD
 */
static int pcan_usbfd_msg_decode(struct pcan_usb_interface *usb_if,
					u8 *msg_addr, int msg_len)
{
	struct pucan_msg *rx_msg;
	u8 *msg_ptr = msg_addr;
	u8 *msg_end = msg_addr + msg_len;
	int err = 0, d;

	DPRINTK(KERN_DEBUG "%s: %s(%d)\n", DEVICE_NAME, __func__, msg_len);
	//dump_mem("received msg", msg_addr, msg_len);

	/* do some init for each controller */
	for (d=0; d < usb_if->dev_ctrl_count; d++ )
		usb_if->dev[d].port.usb.state &= ~PCAN_USBFD_SHOULD_WAKEUP;

	/* loop reading all the records from the incoming message */
	for (; msg_ptr < msg_end;) {
		u16 rx_msg_type, rx_msg_size;

		rx_msg = (struct pucan_msg *)msg_ptr;
		if (!rx_msg->size) {
			/* null packet found: end of list */
			break;
		}

		rx_msg_size = le16_to_cpu(rx_msg->size);
		rx_msg_type = le16_to_cpu(rx_msg->type);

#ifdef DEBUG
		switch (rx_msg_type) {
		case PCAN_USBFD_MSG_CALIBRATION:
			break;
		default:
			dump_mem("received msg", rx_msg, rx_msg_size);
		}
#endif

		/* check if the record goes out of current packet */
		if (msg_ptr + rx_msg_size > msg_end) {
#if 0
			/*
			 * yes, it does:
			 * donot handle fragmentation => increase usb rx
			 * message size
			 */
#endif
			printk(KERN_ERR
			       "%s: got frag rec: should inc usb rx buf size\n",
			       DEVICE_NAME);
			err = -EBADMSG;
			break;
		}

		switch (rx_msg_type) {
		case PUCAN_MSG_CAN_RX:
			err = pcan_usbfd_decode_canmsg(usb_if, rx_msg);
			if (err < 0)
				goto fail;
			break;

		case PCAN_USBFD_MSG_CALIBRATION:
			pcan_usbfd_decode_ts(usb_if, rx_msg);
			break;

		case PUCAN_MSG_ERROR:
			err = pcan_usbfd_decode_error(usb_if, rx_msg);
			if (err < 0)
				goto fail;
			break;

		case PUCAN_MSG_STATUS:
			err = pcan_usbfd_decode_status(usb_if, rx_msg);
			if (err < 0)
				goto fail;
			break;

		case PCAN_USBFD_MSG_OVERRUN:
			err = pcan_usbfd_decode_overrun(usb_if, rx_msg);
			if (err < 0)
				goto fail;
			break;

		case PUCAN_MSG_BUSLOAD:
		case PCAN_USBFD_MSG_DEBUG:
			printk(KERN_ERR
				"%s: unhandled msg type 0x%02x (%d): ignored\n",
				DEVICE_NAME, rx_msg_type, rx_msg_type);
			break;

		default:
			printk(KERN_ERR
				"%s: unknow msg type 0x%02x (%d): ignored\n",
				DEVICE_NAME, rx_msg_type, rx_msg_type);
			break;
		}

		msg_ptr += rx_msg_size;
	}

fail:
	if (err < 0)
		dump_mem("received msg", msg_addr, msg_len);

	/* check if something is to be waken up */
	for (d=0; d < usb_if->dev_ctrl_count; d++ ) {
		if (usb_if->dev[d].port.usb.state & PCAN_USBFD_SHOULD_WAKEUP) {
#ifdef PCAN_USBPRO_DEBUG_DECODE
			printk(KERN_INFO "wakeup task reading CAN#%u\n", d);
#endif
			wake_up_interruptible(&usb_if->dev[d].read_queue);
		}
	}

	return err;
}

/*
 * int pcan_usbfd_msg_encode(struct pcandev *dev,
 *				u8 *buffer_addr, int *buffer_size)
 *
 * Reads into CAN fifo and encode data in USB messages.
 *
 *	-ENODATA	if no more data in CAN fifo,
 *	-EMSGSIZE	if *buffer_size is not large enough to store a TX_x
 *			record
 *	0		if output buffer is full of TX_x records,
 *			any other -ERR.
 */
static int pcan_usbfd_msg_encode(struct pcandev *dev,
				 u8 *buffer_addr, int *buffer_size)
{
	struct pucan_tx_msg *tx_msg = (struct pucan_tx_msg *)buffer_addr;
	USB_PORT *u = &dev->port.usb;
	u16 tx_msg_size;
	int msg_len;
	int err = 0;

	DPRINTK(KERN_DEBUG "%s: %s(%d)\n", DEVICE_NAME, __func__);

	for (msg_len = 0; msg_len < *buffer_size; ) {
		TPCANMsg can_msg;

		/* first get the size of the enqueued CAN message */
		err = pcan_fifo_peek(&dev->writeFifo, &can_msg);
		if (err) {
			if (err != -ENODATA) {
				printk(KERN_ERR "%s: %s(): "
					"can't get data out of writeFifo, "
					"available data: %d, err: %d\n",
					DEVICE_NAME, __func__,
					dev->writeFifo.nStored, err);
			}
			break;
		}

		tx_msg_size = ALIGN(sizeof(struct pucan_tx_msg) + can_msg.LEN,
				    4);

		/* if not enough room to entirely copy it, break this loop */
		if (msg_len + tx_msg_size > *buffer_size)
			break;

		/* really read the message (NULL avoid 2nd useless memcpy()) */
		pcan_fifo_get(&dev->writeFifo, NULL);

#ifdef MSGTYPE_PARAMETER
		if (can_msg.MSGTYPE & (MSGTYPE_STATUS | MSGTYPE_PARAMETER)) {
#else
		if (can_msg.MSGTYPE & MSGTYPE_STATUS) {
#endif
			printk(KERN_INFO "%s: %s(): "
				"CAN msg type %02Xh ignored\n",
				DEVICE_NAME, __func__, can_msg.MSGTYPE);
			continue;
		}

		tx_msg->type = cpu_to_le16(PUCAN_MSG_CAN_TX);
		tx_msg->size = cpu_to_le16(tx_msg_size);

		tx_msg->flags = 0;
		if (can_msg.MSGTYPE & MSGTYPE_EXTENDED) {
			tx_msg->flags |= PUCAN_MSG_EXT_ID;
			tx_msg->can_id = cpu_to_le32(can_msg.ID & CAN_EFF_MASK);
		} else {
			tx_msg->can_id = cpu_to_le32(can_msg.ID & CAN_SFF_MASK);
		}

		/* CAN 2.0 frames */
		if (can_msg.MSGTYPE & MSGTYPE_RTR)
			tx_msg->flags |= PUCAN_MSG_RTR;

		if (can_msg.MSGTYPE & MSGTYPE_SELFRECEIVE)
			tx_msg->flags |= PUCAN_MSG_HW_SRR;

		tx_msg->channel_dlc =
			PUCAN_MSG_CHANNEL_DLC(u->dev_ctrl_index, can_msg.LEN);

		memcpy(tx_msg->d, can_msg.DATA, can_msg.LEN);

		msg_len += tx_msg_size;
		tx_msg = (struct pucan_tx_msg *)(buffer_addr + msg_len);
	}

	if (!msg_len) {
		*buffer_size = 0;
		return -ENODATA;
	}

	/*
	 * if the entire packet is not filled, set the size of last msg to 0
	 * to mark end-of-rec
	 */
	if (msg_len < *buffer_size) {
		msg_len += sizeof(u32);
		tx_msg->type = cpu_to_le16(PUCAN_CMD_NOP);
		tx_msg->size = 0;
	}

	/* set the whole size of the USB packet to send */
	*buffer_size = msg_len;

#ifdef DEBUG
	dump_mem("sent msg", buffer_addr, *buffer_size);
#endif

	return err;
}

/*
 * void pcan_usbfd_cleanup(struct pcandev *dev)
 *
 * Last chance to submit URB before driver removal.
 */
static void pcan_usbfd_cleanup(struct pcandev *dev)
{
	USB_PORT *u = &dev->port.usb;

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d)\n",
		 DEVICE_NAME, __func__, u->dev_ctrl_index);

	/*
	 * Sometimes, bus off request can't be submit when driver is removed
	 * so, when the device was not properly closed. So, move the bus off
	 * request here to be sure it is sent.
	 */
	pcan_usbfd_set_can_off(dev);

#ifdef USB_VENDOR_REQUEST_wVALUE_SETFKT_INTERFACE_DRIVER_LOADED
	/*
	 * No more need to switch off the LEDs by ourselves!
	 * Fw does it when we notify it from driver unload!
	 */
#else
	/* Switch LED off */
	pcan_usbfd_set_can_led(dev, PCAN_USBFD_LED_OFF);
#endif

	/* If last device, tell module that driver is unloaded */
	if (u->dev_ctrl_index == (u->usb_if->dev_ctrl_count-1)) {

		/* Tell module the CAN driver is unloaded */
		pcan_usbpro_driver_loaded(u->usb_if, 0, 0);
	}
}

/*
 * int pcan_usbfd_ctrl_init(struct pcandev *dev)
 *
 * Do CAN controller specific initialization.
 */
static int pcan_usbfd_ctrl_init(struct pcandev *dev)
{
	USB_PORT *u = &dev->port.usb;
#ifndef PCAN_DEV_USES_ALT_NUM
	u32 device_nr;
	int err;
#endif

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d)\n",
		 DEVICE_NAME, __func__, u->dev_ctrl_index);

#ifndef PCAN_DEV_USES_ALT_NUM
	err = pcan_usbfd_get_device_nr(dev, &device_nr);
	if (!err)
		pr_info("%s: %s channel %d device number=0x%x\n",
			 DEVICE_NAME, u->usb_if->adapter_name,
			 u->dev_ctrl_index+1, device_nr);
#else
	pr_info("%s: %s channel %d device number=%u\n",
		DEVICE_NAME, u->usb_if->adapter_name,
		u->dev_ctrl_index+1, dev->device_alt_num);
#endif

	/* set 80MHz clock domain */
	pcan_usbfd_set_clock_domain(dev, PCAN_USBFD_CLK_80MHZ);

	/* set LED in default state (end of init phase) */
	pcan_usbfd_set_can_led(dev, PCAN_USBFD_LED_DEF);

	/* sending data is not allowed for the moment */
	atomic_set(&dev->DataSendReady, 0);

	return 0;
}

/*
 * void pcan_usbfd_free(struct pcan_usb_interface *usb_if)
 */
static void pcan_usbfd_free(struct pcan_usb_interface *usb_if)
{
	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __func__);
}

/*
 * int pcan_usbfd_init(struct pcan_usb_interface *usb_if)
 *
 * Do device specifc initialization.
 */
int pcan_usbfd_init(struct pcan_usb_interface *usb_if)
{
#ifdef PCAN_DEV_USES_ALT_NUM
	int c;
#endif

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __func__);

	switch (usb_if->usb_dev->descriptor.idProduct) {
	case PCAN_USBPROFD_PRODUCT_ID:
		usb_if->adapter_name = "PCAN-USB Pro FD";
		break;

	case PCAN_USBFD_PRODUCT_ID:
		usb_if->adapter_name = "PCAN-USB FD";
		break;
	}

	/* Set PCAN-USB (Pro) FD hardware specific callbacks */
	usb_if->device_ctrl_init = pcan_usbfd_ctrl_init;
	usb_if->device_get_snr = pcan_usbfd_get_serial_nr;
	usb_if->device_msg_decode = pcan_usbfd_msg_decode;
	usb_if->device_free = pcan_usbfd_free;

	usb_if->device_ctrl_cleanup = pcan_usbfd_cleanup;
	usb_if->device_ctrl_open = pcan_usbfd_open;
	usb_if->device_ctrl_close = pcan_usbfd_close;
	usb_if->device_ctrl_set_bus_on = pcan_usbfd_set_can_on;
	usb_if->device_ctrl_set_bus_off = pcan_usbfd_set_can_off;
	usb_if->device_ctrl_set_dnr = pcan_usbfd_set_device_nr;
	usb_if->device_ctrl_get_dnr = pcan_usbfd_get_device_nr;
	usb_if->device_ctrl_msg_encode = pcan_usbfd_msg_encode;

#ifdef PCAN_DEV_USES_ALT_NUM
	/*
	 * MUST initialize alt_num here (before creating devices) for Udev rules
	 */
	for (c = 0; c < usb_if->dev_ctrl_count; c++)
		usb_if->dev[c].device_alt_num = 0xffffffff;
#endif

	usb_if->cm_ignore_count = 5;

	/* Tell module the CAN driver is loaded */
	pcan_usbpro_driver_loaded(usb_if, 0, 1);

	/* read fw info */
	pcan_usbfd_get_fw_info(usb_if, 1);

	return 0;
}
