//****************************************************************************
// Copyright (C) 2001-2007  PEAK System-Technik GmbH
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
// Maintainer(s): Klaus Hitschler (klaus.hitschler@gmx.de)
//
// Major contributions by:
//                Edouard Tisserant (edouard.tisserant@lolitech.fr) XENOMAI
//                Laurent Bessard   (laurent.bessard@lolitech.fr)   XENOMAI
//                Oliver Hartkopp   (oliver.hartkopp@volkswagen.de) socketCAN
//
// Contributions: Marcel Offermans (marcel.offermans@luminis.nl)
//                Arno (a.vdlaan@hccnet.nl)
//                John Privitera (JohnPrivitera@dciautomation.com)
//****************************************************************************

//****************************************************************************
//
// pcan_fops.c - all file operation functions, exports only struct fops
//
// $Id: pcan_fops.c 807 2014-12-09 15:34:11Z stephane $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <src/pcan_common.h>// must always be the 1st include
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,16)
#include <linux/config.h>
#else
#ifndef AUTOCONF_INCLUDED
#include <linux/autoconf.h>
#endif
#endif

#include <linux/kernel.h>   // DPRINTK()
#include <linux/slab.h>     // kmalloc()
#include <linux/fs.h>       // everything...
#include <linux/errno.h>    // error codes
#include <linux/types.h>    // size_t
#include <linux/proc_fs.h>  // proc
#include <linux/fcntl.h>    // O_ACCMODE
#include <linux/pci.h>      // all about pci
#include <linux/capability.h> // all about restrictions
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 4, 0)
#include <asm/system.h>     // cli(), *_flags
#endif
#include <asm/uaccess.h>    // copy_...
#include <linux/delay.h>    // mdelay()
#include <linux/poll.h>     // poll() and select()

#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,13)
#include <linux/moduleparam.h>
#endif

#include <src/pcan_main.h>
#include <src/pcan_pci.h>
#include <src/pcan_isa.h>
#include <src/pcan_dongle.h>
#include <src/pcan_sja1000.h>
#include <src/pcan_fifo.h>
#include <src/pcan_fops.h>
#include <src/pcan_parse.h>
#include <src/pcan_usb.h>
#include <src/pcan_filter.h>

//****************************************************************************
// DEFINES
// this was'nt present before
#ifndef MODULE_LICENSE
#define MODULE_LICENSE(x)
#endif
#ifndef MODULE_VERSION
#define MODULE_VERSION(x)
#endif

MODULE_AUTHOR("klaus.hitschler@gmx.de");
MODULE_DESCRIPTION("Driver for PEAK-System CAN interfaces");
MODULE_VERSION(CURRENT_RELEASE);
MODULE_SUPPORTED_DEVICE("PCAN-ISA, PCAN-PC/104, PCAN-Dongle, PCAN-PCI(e), PCAN-ExpressCard, PCAN-PCCard, PCAN-USB (compilation dependent)");
MODULE_LICENSE("GPL");

#if defined(module_param_array) && LINUX_VERSION_CODE > KERNEL_VERSION(2,6,13)
extern char   *type[8];
extern ushort io[8];
extern char   irq[8];
extern ushort bitrate;
extern char   *assign;

module_param_array(type, charp,  NULL, 0444);
module_param_array(io,   ushort, NULL, 0444);
module_param_array(irq,  byte,   NULL, 0444);
module_param(bitrate, ushort, 0444);
module_param(assign,  charp,  0444);
#else
MODULE_PARM(type,    "0-8s");
MODULE_PARM(io,      "0-8h");
MODULE_PARM(irq,     "0-8b");
MODULE_PARM(bitrate, "h");
MODULE_PARM(assign,  "s");
#endif

MODULE_PARM_DESC(type,    "The type of PCAN interface (isa, sp, epp)");
MODULE_PARM_DESC(io,      "The io-port address for either PCAN-ISA, PC/104 or Dongle");
MODULE_PARM_DESC(irq,     "The interrupt number for either PCAN-ISA, PC/104 or Dongle");
MODULE_PARM_DESC(bitrate, "The initial bitrate (BTR0BTR1) for all channels");
MODULE_PARM_DESC(assign,  "The assignment for netdevice names to CAN devices");


// wait this time in msec at max after releasing the device - give fifo a chance to flush
#define MAX_WAIT_UNTIL_CLOSE 1000

//****************************************************************************
// GLOBALS
#if defined(LINUX_24)
EXPORT_NO_SYMBOLS;
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,18) || LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
#define minor(x) MINOR(x)
#endif

//****************************************************************************
// LOCALS

//****************************************************************************
// CODE
#ifdef NO_RT
	#include "pcan_fops_linux.c"
#else
	#include "pcan_fops_rt.c"
#endif

//----------------------------------------------------------------------------
// is called by pcan_open() and pcan_netdev_open()
int pcan_open_path(PCAN_OPEN_PATH_ARGS)
{
	int err = 0;

	DPRINTK(KERN_DEBUG "%s: pcan_open_path, minor = %d, path = %d.\n",
		DEVICE_NAME, dev->nMinor, dev->nOpenPaths);

	// only the 1st open to this device makes a default init on this device
	if (!dev->nOpenPaths) {
		// empty all FIFOs
		err = pcan_fifo_reset(&dev->writeFifo);
		if (err)
			return err;
		err = pcan_fifo_reset(&dev->readFifo);
		if (err)
			return err;

		// open the interface special parts
		err = dev->open(dev);
		if (err) {
			DPRINTK(KERN_DEBUG
				"%s: can't open interface special parts!\n",
				DEVICE_NAME);
			return err;
		}

		/*
		 * special handling: probe here only for dongle devices,
		 * connect after init is possible
		 */
		if ((dev->wType == HW_DONGLE_SJA) ||
				(dev->wType == HW_DONGLE_SJA_EPP)) {
			err = sja1000_probe(dev); // no usb here, generic sja1000 call for dongle
			if (err) {
				DPRINTK(KERN_ERR
					"%s: %s-dongle device minor %d not found (io=0x%04x,irq=%d)\n",
					DEVICE_NAME, dev->type, dev->nMinor,
					dev->port.dng.dwPort,
					dev->port.dng.wIrq);
				dev->release(dev);
				return err;
			}
		}

		// install irq
		err = dev->req_irq(REQ_IRQ_ARG);

		if (err) {
			DPRINTK(KERN_DEBUG
				"%s: can't request irq from device!\n",
				DEVICE_NAME);
			return err;
		}

		// open the device itself
		err = dev->device_open(dev, dev->wBTR0BTR1, dev->ucCANMsgType,
				       dev->ucListenOnly);
		if (err) {
			DPRINTK(KERN_DEBUG
				"%s: can't open device hardware itself!\n",
				DEVICE_NAME);
			return err;
		}
	}

	dev->nOpenPaths++;

	DPRINTK(KERN_DEBUG "%s: pcan_open_path() is OK\n", DEVICE_NAME);

	return 0;
}

//----------------------------------------------------------------------------
// find the pcandev according to given major,minor numbers
// returns NULL pointer in the case of no success
struct pcandev* pcan_search_dev(int major, int minor)
{
	struct pcandev *dev = (struct pcandev *)NULL;
	struct list_head *ptr;

	DPRINTK(KERN_DEBUG "%s: pcan_search_dev(), major,minor = %d,%d.\n", 
		DEVICE_NAME, major, minor);

	mutex_lock(&pcan_drv.devices_lock);

	if (list_empty(&pcan_drv.devices)) {
		mutex_unlock(&pcan_drv.devices_lock);
		DPRINTK(KERN_DEBUG "%s: no devices to select from!\n",
			DEVICE_NAME);
		return NULL;
	}

	/* loop through my devices */
	for (ptr = pcan_drv.devices.next; ptr != &pcan_drv.devices; 
							ptr = ptr->next) {
		dev = (struct pcandev *)ptr;

		if (dev->nMajor == major)
			if (dev->nMinor == minor)
				break;
	}

	mutex_unlock(&pcan_drv.devices_lock);

	if (ptr == &pcan_drv.devices) {
		printk(KERN_DEBUG "%s: didn't find any pcan devices (%d,%d)\n", 
			DEVICE_NAME, major, minor);
		return NULL;
	}

	return dev;
}

//----------------------------------------------------------------------------
// is called by pcan_release() and pcan_netdev_close()
void pcan_release_path(PCAN_RELEASE_PATH_ARGS)
{
	DPRINTK(KERN_DEBUG "%s: pcan_release_path, minor = %d, path = %d.\n",
		DEVICE_NAME, dev->nMinor, dev->nOpenPaths);

	/* if it's the last release: init the chip for non-intrusive operation*/
	if (dev->nOpenPaths > 1) {
		dev->nOpenPaths--;

	} else  {

		WAIT_UNTIL_FIFO_EMPTY();

		/* release the device itself */
		dev->device_release(dev);

		dev->release(dev);
		dev->nOpenPaths = 0;

		/*
		 * release the interface depended irq, after this 'dev' is not
		 * valid
		 */
		dev->free_irq(dev);
	}
}

//----------------------------------------------------------------------------
// is called at user ioctl() with cmd = PCAN_GET_EXT_STATUS
int pcan_ioctl_extended_status_common(struct pcandev *dev, 
					TPEXTENDEDSTATUS *local)
{
	local->wErrorFlag = dev->wCANStatus;

	local->nPendingReads = dev->readFifo.nStored;

	// get infos for friends of polling operation
	if (pcan_fifo_empty(&dev->readFifo))
		local->wErrorFlag |= CAN_ERR_QRCVEMPTY;

	local->nPendingWrites = (dev->writeFifo.nStored + \
				((atomic_read(&dev->DataSendReady)) ? 0 : 1));

	if (!pcan_fifo_not_full(&dev->writeFifo))
		local->wErrorFlag |= CAN_ERR_QXMTFULL;

	local->nLastError = dev->nLastError;

	return 0;
}

//----------------------------------------------------------------------------
// is called at user ioctl() with cmd = PCAN_GET_STATUS
int pcan_ioctl_status_common(struct pcandev *dev, TPSTATUS *local)
{
	local->wErrorFlag = dev->wCANStatus;

	// get infos for friends of polling operation
	if (pcan_fifo_empty(&dev->readFifo))
		local->wErrorFlag |= CAN_ERR_QRCVEMPTY;

	if (!pcan_fifo_not_full(&dev->writeFifo))
		local->wErrorFlag |= CAN_ERR_QXMTFULL;

	local->nLastError = dev->nLastError;

	return 0;
}

//----------------------------------------------------------------------------
// is called at user ioctl() with cmd = PCAN_DIAG
int pcan_ioctl_diag_common(struct pcandev *dev, TPDIAG *local)
{
	local->wType = dev->wType;

	switch (dev->wType) {
	case HW_ISA_SJA:
		local->dwBase = dev->port.isa.dwPort;
		local->wIrqLevel = dev->port.isa.wIrq;
		break;
	case HW_DONGLE_SJA:
	case HW_DONGLE_SJA_EPP:
		local->dwBase = dev->port.dng.dwPort;
		local->wIrqLevel = dev->port.dng.wIrq;
		break;
	case HW_PCI:
		local->dwBase = dev->port.pci.dwPort;
		local->wIrqLevel = dev->port.pci.wIrq;
		break;
	case HW_USB:
	case HW_USB_FD:
	case HW_USB_PRO:
	case HW_USB_PRO_FD:
#ifdef USB_SUPPORT
		local->dwBase = dev->port.usb.usb_if->dwSerialNumber;
		local->wIrqLevel = dev->port.usb.ucHardcodedDevNr;
#endif
		break;
	case HW_PCCARD:
#ifdef PCCARD_SUPPORT
		local->dwBase = dev->port.pccard.dwPort;
		local->wIrqLevel = dev->port.pccard.wIrq;
#endif
		break;
	}

	local->dwReadCounter = dev->readFifo.dwTotal;
	local->dwWriteCounter = dev->writeFifo.dwTotal;
	local->dwIRQcounter = dev->dwInterruptCounter;
	local->dwErrorCounter = dev->dwErrorCounter;
	local->wErrorFlag = dev->wCANStatus;

	// get infos for friends of polling operation
	if (pcan_fifo_empty(&dev->readFifo))
		local->wErrorFlag |= CAN_ERR_QRCVEMPTY;

	if (!pcan_fifo_not_full(&dev->writeFifo))
		local->wErrorFlag |= CAN_ERR_QXMTFULL;

	local->nLastError = dev->nLastError;
	local->nOpenPaths = dev->nOpenPaths;

	strncpy(local->szVersionString,
			pcan_drv.szVersionString, VERSIONSTRING_LEN);
	return 0;
}
