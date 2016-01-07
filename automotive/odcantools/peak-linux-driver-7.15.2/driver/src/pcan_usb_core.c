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
// Maintainer: Stephane Grosjean (s.grosjean@peak-system.com)
//
// Major contributions by:
//                Oliver Hartkopp (oliver.hartkopp@volkswagen.de) socketCAN
//                Klaus Hitschler (klaus.hitschler@gmx.de)
//
// Contributions: Philipp Baer (philipp.baer@informatik.uni-ulm.de)
//                Tom Heinrich
//                John Privitera (JohnPrivitera@dciautomation.com)
//****************************************************************************

//****************************************************************************
//
// pcan_usb_core.c - the outer usb parts for pcan-usb and pcan-usb-pro support
//
// $Id: pcan_usb_core.c 626 2010-06-16 21:37:49Z khitschler $
//
//****************************************************************************
//#define DEBUG
//#undef DEBUG

//****************************************************************************
// INCLUDES
#include <src/pcan_common.h>     // must always be the 1st include
#include <linux/stddef.h>        // NULL
#include <linux/errno.h>
#include <linux/slab.h>          // kmalloc()

#include <linux/usb.h>
#include <linux/net.h>

#include <src/pcan_main.h>
#include <src/pcan_fops.h>
#include <src/pcan_usb_core.h>
#include <src/pcan_usb.h>
#ifdef HW_USB_PRO
#include <src/pcan_usbpro.h>
#endif
#if defined(HW_USB_FD) || defined(HW_USB_PRO_FD)
#include <src/pcan_usbfd.h>
#endif
#include <src/pcan_filter.h>

#ifdef NETDEV_SUPPORT
#include <src/pcan_netdev.h>     // for hotplug pcan_netdev_(un)register()
#endif

//****************************************************************************
// DEFINES
#ifdef DEBUG
#define PCAN_USB_DEBUG_WRITE
#define PCAN_USB_DEBUG_DECODE
#endif

/*
 * If defined, the application is notified that the USB device has been
 * unplugged more quickly *BUT* this also might change the can device enum and
 * names when plugged again, especially when there are other non-USB PCAN
 * devices in the host.
 * So, this SHOULD not be defined except for users who know what they're doing.
 */
//#define PCAN_USB_FAST_CLOSE_NMI

#define PCAN_USB_VENDOR_ID		0x0c72
#define PCAN_USB_PRODUCT_ID		0x000c
#define PCAN_USBPRO_PRODUCT_ID		0x000d
#define PCAN_USBFD_PRODUCT_ID		0x0012
#define PCAN_USBPROFD_PRODUCT_ID	0x0011

#define PCAN_USB_READ_BUFFER_SIZE_OLD	64   /* used len for PCAN-USB rev < 6*/
#define PCAN_USB_READ_BUFFER_SIZE	1024 /* buffer for read URB data (IN) */
#define PCAN_USB_READ_PACKET_SIZE	64   /* always 64 (USB1 device) */

#define PCAN_USB_WRITE_BUFFER_SIZE_OLD 64    // used length for PCAN-USB rev < 6
//#define PCAN_USB_WRITE_BUFFER_SIZE     128   // buffer for write URB (OUT)
#define PCAN_USB_WRITE_BUFFER_SIZE     256   // ...says Win driver
#define PCAN_USB_WRITE_PACKET_SIZE     64    // always 64 (USB1 device)

/* Defines the size of one USB message that can be received from the device */
/* Driver allocates one buffer of n x PCAN_USBPRO_READ_BUFFER_SIZE to handle */
/* consecutive reads */
//#define PCAN_USBPRO_READ_BUFFER_SIZE   1024
#define PCAN_USBPRO_READ_BUFFER_SIZE   2048
//#define PCAN_USBPRO_READ_BUFFER_SIZE   4096

#define MAX_CYCLES_TO_WAIT_FOR_RELEASE 100   // max schedules before release

#define STARTUP_WAIT_TIME         0.01 // wait this time in seconds at startup to get first messages

//****************************************************************************
// GLOBALS
static struct usb_device_id pcan_usb_ids[] =
{
	{ USB_DEVICE(PCAN_USB_VENDOR_ID, PCAN_USB_PRODUCT_ID) },
#ifdef HW_USB_PRO
	{ USB_DEVICE(PCAN_USB_VENDOR_ID, PCAN_USBPRO_PRODUCT_ID) },
#endif
#ifdef HW_USB_FD
	{ USB_DEVICE(PCAN_USB_VENDOR_ID, PCAN_USBFD_PRODUCT_ID) },
#endif
#ifdef HW_USB_PRO_FD
	{ USB_DEVICE(PCAN_USB_VENDOR_ID, PCAN_USBPROFD_PRODUCT_ID) },
#endif
	{ }            // Terminating entry
};

MODULE_DEVICE_TABLE(usb, pcan_usb_ids);

#ifdef LINUX_26
static struct usb_class_driver pcan_class =
{
	.name = "pcanusb%d",
	.fops = &pcan_fops,

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,15)
	.mode = S_IFCHR | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH,
#endif

	.minor_base = PCAN_USB_MINOR_BASE,
};
#endif

//****************************************************************************
// LOCALS
static uint16_t usb_devices = 0;        // the number of accepted usb_devices

//****************************************************************************
// CODE

//****************************************************************************
// get cyclic data from endpoint 2

// forward declaration for chardev pcan_usb_write_notitfy()
static int pcan_usb_write(struct pcandev *dev);

//****************************************************************************
// notify functions for read and write data
#ifdef LINUX_26
static void pcan_usb_write_notify(struct urb *purb, struct pt_regs *pregs)
#else
static void pcan_usb_write_notify(purb_t purb)
#endif
{
	int err     = 0;
	uint16_t wwakeup = 0;
	struct pcandev *dev = purb->context;
	struct pcan_usb_interface *usb_if = dev->port.usb.usb_if;

	// DPRINTK(KERN_DEBUG "%s: %s() (%d)\n",
	//         DEVICE_NAME, __func__, purb->status);

#ifdef PCAN_USB_DEBUG_WRITE
	printk(KERN_INFO "%s(): status=%d actual_length=%d\n",
			__func__, purb->status, purb->actual_length);
#endif

	if (!usb_if)
		return;

	// un-register outstanding urb
	atomic_dec(&usb_if->active_urbs);

	// don't count interrupts - count packets
	dev->dwInterruptCounter++;

	// do write
	if (!purb->status) // stop with first error
		err = pcan_usb_write(dev);

	if (err) {
		if (err == -ENODATA)
			wwakeup++;
		else {
			printk(KERN_DEBUG "%s: unexpected error %d from pcan_usb_write()\n",
			       DEVICE_NAME, err);
			dev->nLastError = err;
			dev->dwErrorCounter++;
			dev->wCANStatus |= CAN_ERR_QXMTFULL; // fatal error!
		}
	}

	if (wwakeup) {
		atomic_set(&dev->DataSendReady, 1); // signal to write I'm ready
		wake_up_interruptible(&dev->write_queue);

#ifdef NETDEV_SUPPORT
		netif_wake_queue(dev->netdev);
#endif
	}
}

#ifdef LINUX_26
static void pcan_usb_read_notify(struct urb *purb, struct pt_regs *pregs)
#else
static void pcan_usb_read_notify(purb_t purb)
#endif
{
	int err = 0;
	struct pcan_usb_interface *usb_if = purb->context;
	struct pcandev *dev = &usb_if->dev[0];

#if 0
	DPRINTK(KERN_DEBUG "%s: %s() status=%d\n",
	        DEVICE_NAME, __func__, purb->status);
#endif

	// un-register outstanding urb
	atomic_dec(&usb_if->active_urbs);

	// do interleaving read
	// stop with first error
	if (!purb->status && dev->ucPhysicallyInstalled) {
		uint8_t *read_buffer_addr = purb->transfer_buffer;
		const int read_buffer_len = purb->actual_length;
		int read_buffer_size;

		// buffer interleave to increase speed
		if (read_buffer_addr == usb_if->read_buffer_addr[0]) {
			FILL_BULK_URB(purb, usb_if->usb_dev,
				           usb_rcvbulkpipe(usb_if->usb_dev,
			                              usb_if->pipe_read.ucNumber),
				           usb_if->read_buffer_addr[1], usb_if->read_buffer_size,
			              pcan_usb_read_notify, usb_if);
		} else {
			FILL_BULK_URB(purb, usb_if->usb_dev,
				           usb_rcvbulkpipe(usb_if->usb_dev,
			                              usb_if->pipe_read.ucNumber),
				           usb_if->read_buffer_addr[0], usb_if->read_buffer_size,
			              pcan_usb_read_notify, usb_if);
		}

		// start next urb
		if ((err = __usb_submit_urb(purb))) {
			dev->nLastError = err;
			dev->dwErrorCounter++;

			printk(KERN_ERR "%s: %s() URB submit failure %d\n",
			       DEVICE_NAME, __func__, err);
		} else
			atomic_inc(&usb_if->active_urbs);

#ifdef PCAN_USB_DEBUG_DECODE
		printk(KERN_INFO "%s: got %u bytes URB, "
		                 "decoding it by packets of %u bytes:\n",
		       DEVICE_NAME, read_buffer_len, usb_if->read_packet_size);
#endif

		for (read_buffer_size=0; read_buffer_size < read_buffer_len; ) {
#ifdef PCAN_USB_DEBUG_DECODE
			printk(KERN_INFO "%s: decoding @offset %u:\n",
			       DEVICE_NAME, read_buffer_size);
#endif
			err = usb_if->device_msg_decode(usb_if,
			                              read_buffer_addr,
			                              usb_if->read_packet_size);
			if (err < 0) {
				dev->nLastError = err;
				dev->wCANStatus |= CAN_ERR_QOVERRUN;
				dev->dwErrorCounter++;

				if (net_ratelimit())
					printk(KERN_DEBUG "%s: @offset %d: message decoding error %d\n",
					       DEVICE_NAME, read_buffer_size, err);
			}

			read_buffer_addr += usb_if->read_packet_size;
			read_buffer_size += usb_if->read_packet_size;
		}
	} else {
		if (purb->status != -ENOENT) {
			printk(KERN_ERR
				"%s: read data stream turned off caused by ",
				DEVICE_NAME);

			if (!dev->ucPhysicallyInstalled) {
				printk("device plug out!\n");
			} else {

				switch (purb->status) {

				case -ESHUTDOWN:
					printk("endpoint shutdown\n");
					break;

#ifdef PCAN_USB_FAST_CLOSE_NMI
				/*
				 * here are cases that have been seen to occur
				 */
				case -EILSEQ:
				case -EOVERFLOW:

				case -EPIPE:
				case -EPROTO:
#endif
				default:
					printk("err %d!\n", purb->status);
					break;
				}

				if (dev->nOpenPaths) {

#ifdef PCAN_USB_FAST_CLOSE_NMI
					/*
					 * seems that this is the most
					 * reasonable thing to do most of the
					 * times...
					 */
					dev->ucPhysicallyInstalled = 0;
#endif
					printk("err %d: considering unplugged device\n", purb->status);
				} else {
					/*
					 * Otherwise, do nothing but wait for
					 * the usb core to disconnect then
					 * reconnect the device.
					 */
				}
			}
		}
	}
}

//****************************************************************************
// USB write functions

static int pcan_usb_write(struct pcandev *dev)
{
	int err = 0;
	USB_PORT *u = &dev->port.usb;
	struct pcan_usb_interface *usb_if = u->usb_if;

#if 1
	uint8_t *write_buffer_addr = u->write_buffer_addr;
	int write_packet_size;
	int write_buffer_size;

	//DPRINTK(KERN_DEBUG "%s: %s(CAN#%d)\n",
	//        DEVICE_NAME, __func__, u->dev_ctrl_index);

	// don't do anything with non-existent hardware
	if (!dev->ucPhysicallyInstalled || !usb_if)
		return -ENODEV;

	for (write_buffer_size=0; write_buffer_size < u->write_buffer_size; ) {
		write_packet_size = u->write_packet_size;
		err = usb_if->device_ctrl_msg_encode(dev,
		                                     write_buffer_addr,
		                                     &write_packet_size);

#ifdef PCAN_USB_DEBUG_WRITE
		printk(KERN_INFO "%s: encoded %u bytes in %u bytes packet\n",
		       DEVICE_NAME, write_packet_size, u->write_packet_size);
#endif
		if (!err) {
			write_buffer_size += u->write_packet_size;
			write_buffer_addr += u->write_packet_size;
			continue;
		}

		switch (err) {
		case -ENODATA:
			write_buffer_size += write_packet_size;
#ifdef PCAN_USB_DEBUG_WRITE
			printk(KERN_INFO "%s: err=-ENODATA: total=%u/%u\n",
			       DEVICE_NAME, write_buffer_size,
			       u->write_buffer_size);
#endif
			break;

		case -EMSGSIZE:
			write_buffer_size += write_packet_size;
			err = 0;
			break;

		default:
#ifdef PCAN_USB_DEBUG_WRITE
			printk(KERN_INFO "%s: err=%d: total=%u/%u\n",
			       DEVICE_NAME,
			       err, write_buffer_size, u->write_buffer_size);
#endif
			break;
		}

		break;
	}

	if (write_buffer_size > 0) {
#ifdef PCAN_USB_DEBUG_WRITE
		dump_mem("message sent to device",
			u->write_buffer_addr, write_buffer_size);

		printk(KERN_INFO
			"%s: submitting %u bytes buffer to usb EP#%d\n",
			DEVICE_NAME, write_buffer_size, u->pipe_write.ucNumber);
#endif

		FILL_BULK_URB(&u->write_data, usb_if->usb_dev,
		              usb_sndbulkpipe(usb_if->usb_dev,
				              u->pipe_write.ucNumber),
		              u->write_buffer_addr, write_buffer_size,
		              pcan_usb_write_notify, dev);

		// start next urb
		if ((err = __usb_submit_urb(&u->write_data))) {
			dev->nLastError = err;
			dev->dwErrorCounter++;

			printk(KERN_ERR "%s: %s() URB submit failure %d\n",
			        DEVICE_NAME, __func__, err);
		} else {
			atomic_inc(&usb_if->active_urbs);
		}
	}

#else

	int nDataLength;
	int read_buffer_len;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __func__);

	// don't do anything with non-existent hardware
	if (!dev->ucPhysicallyInstalled)
		return -ENODEV;

	// improvement to control 128 bytes buffers
	read_buffer_len    = PCAN_USB_WRITE_BUFFER_SIZE_OLD;
	err = pcan_usb_EncodeMessage(dev, u->write_buffer_addr, &read_buffer_len);
	if (err || (u->ucRevision < 7))
		nDataLength = read_buffer_len;
	else
	{
		read_buffer_len     = PCAN_USB_WRITE_BUFFER_SIZE_OLD;
		err = pcan_usb_EncodeMessage(dev, u->write_buffer_addr + 64, &read_buffer_len);
		nDataLength          = PCAN_USB_WRITE_BUFFER_SIZE_OLD + read_buffer_len;
	}

	// fill the URB and submit
	if (nDataLength)
	{
		FILL_BULK_URB(&u->write_data, u->usb_dev,
				          usb_sndbulkpipe(u->usb_dev, u->pipe_write.ucNumber),
				          u->write_buffer_addr, nDataLength, pcan_usb_write_notify, dev);

		// start next urb
		if ((err = __usb_submit_urb(&u->write_data)))
		{
			dev->nLastError = err;
			dev->dwErrorCounter++;
			DPRINTK(KERN_ERR "%s: pcan_usb_write() can't submit! (%d)",DEVICE_NAME, err);
		}
		else
			atomic_inc(&dev->port.usb.active_urbs);
	}

	// it's no error if I can't get more data but still a packet was sent
	if ((err == -ENODATA) && (nDataLength))
		err = 0;

#endif

	return err;
}

//****************************************************************************
// usb resource allocation
//
static int pcan_usb_allocate_resources(struct pcan_usb_interface *usb_if)
{
	struct pcandev *dev;
	USB_PORT *u;
	int err = 0;
	int c;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __func__);

	// make param URB
	usb_init_urb(&usb_if->urb_cmd_sync);
	usb_init_urb(&usb_if->urb_cmd_async);

	usb_if->cout_bsize = 0;

	// allocate write buffer
	// Check revision according to device id.
	switch (usb_if->usb_dev->descriptor.idProduct) {

#ifdef HW_USB_FD
	case PCAN_USBFD_PRODUCT_ID:
		usb_if->cout_bsize = 512;
		usb_if->read_packet_size = 4096;
		usb_if->dev[0].port.usb.write_packet_size = 512;

		usb_if->read_buffer_size = usb_if->read_packet_size;
		usb_if->dev[0].port.usb.write_buffer_size =
				usb_if->dev[0].port.usb.write_packet_size;
		break;
#endif
#ifdef HW_USB_PRO_FD
	case PCAN_USBPROFD_PRODUCT_ID:
		usb_if->cout_bsize = 512;
		usb_if->read_packet_size = 4096;

		usb_if->dev[0].port.usb.write_packet_size =
				usb_if->dev[1].port.usb.write_packet_size = 512;

		usb_if->read_buffer_size = usb_if->read_packet_size;
		usb_if->dev[0].port.usb.write_buffer_size =
				usb_if->dev[0].port.usb.write_packet_size;
		usb_if->dev[1].port.usb.write_buffer_size =
				usb_if->dev[1].port.usb.write_packet_size;
		break;
#endif
#ifdef HW_USB_PRO
	case PCAN_USBPRO_PRODUCT_ID:
		/* Rev 0x00 */

		/*
		 * Copied from Win32 Driver:
		 * DeviceContext->IsDeviceHighSpeed ? 512 : 64
		 * 512 bytes packet size leads to fragmentation issue while
		 * messages are 1024 bytes large
		 */
		if (usb_if->usb_dev->speed == USB_SPEED_HIGH) {
			usb_if->read_packet_size = 1024;
			usb_if->dev[0].port.usb.write_packet_size =
			   usb_if->dev[1].port.usb.write_packet_size = 512;
		} else {
			usb_if->read_packet_size = 64;
			usb_if->dev[0].port.usb.write_packet_size =
			   usb_if->dev[1].port.usb.write_packet_size = 64;
		}

#ifdef PCAN_USBPRO_READ_BUFFER_SIZE
		usb_if->read_buffer_size = PCAN_USBPRO_READ_BUFFER_SIZE;
#else
		usb_if->read_buffer_size = usb_if->read_packet_size;
#endif

#ifdef PCAN_USBPRO_WRITE_BUFFER_SIZE
		usb_if->dev[0].port.usb.write_buffer_size =
				PCAN_USBPRO_WRITE_BUFFER_SIZE;
		usb_if->dev[1].port.usb.write_buffer_size =
				PCAN_USBPRO_WRITE_BUFFER_SIZE;
#else
		usb_if->dev[0].port.usb.write_buffer_size =
                               usb_if->dev[0].port.usb.write_packet_size;
		usb_if->dev[1].port.usb.write_buffer_size =
                               usb_if->dev[1].port.usb.write_packet_size;
#endif

		break;
#endif

	case PCAN_USB_PRODUCT_ID:
		if (usb_if->ucRevision >= 7) {
			usb_if->read_buffer_size = PCAN_USB_READ_BUFFER_SIZE;
			usb_if->dev[0].port.usb.write_buffer_size =
						PCAN_USB_WRITE_BUFFER_SIZE;
			usb_if->read_packet_size = PCAN_USB_READ_PACKET_SIZE;
			usb_if->dev[0].port.usb.write_packet_size =
						PCAN_USB_WRITE_PACKET_SIZE;
			break;
		}
	default:
		usb_if->read_buffer_size = PCAN_USB_READ_BUFFER_SIZE_OLD;
		usb_if->dev[0].port.usb.write_buffer_size =
						PCAN_USB_WRITE_BUFFER_SIZE_OLD;
		usb_if->read_packet_size = PCAN_USB_READ_PACKET_SIZE;
		usb_if->dev[0].port.usb.write_packet_size =
						PCAN_USB_WRITE_PACKET_SIZE;
		break;
	}

	dev = &usb_if->dev[0];
	for (c=0; c < usb_if->dev_ctrl_count; c++, dev++) {
		u = &dev->port.usb;

		u->write_buffer_addr =
				kmalloc(u->write_buffer_size, GFP_KERNEL);
		if (!u->write_buffer_addr) {
			err = -ENOMEM;
			goto fail;
		}

		DPRINTK(KERN_DEBUG
			"%s: %s() allocate %d bytes buffer for writing\n",
		        DEVICE_NAME, __func__, u->write_buffer_size);

		// make write urb
		usb_init_urb(&u->write_data);
	}

	// allocate two read buffers for URB
	usb_if->read_buffer_addr[0] =
			kmalloc(usb_if->read_buffer_size * 2, GFP_KERNEL);
	if (!usb_if->read_buffer_addr[0]) {
		err = -ENOMEM;
		goto fail;
	}

	DPRINTK(KERN_DEBUG
		"%s: %s() allocate %d buffers of %d bytes for reading\n",
	        DEVICE_NAME, __func__, 2, usb_if->read_buffer_size);

	usb_if->read_buffer_addr[1] = usb_if->read_buffer_addr[0]
	                            + usb_if->read_buffer_size;

	if (usb_if->cout_bsize) {
		usb_if->cout_baddr = kmalloc(usb_if->cout_bsize, GFP_KERNEL);
		if (!usb_if->cout_baddr) {
			err = -ENOMEM;
			goto fail;
		}
	} else {
		usb_if->cout_baddr = NULL;
	}

	/* make read urb */
	usb_init_urb(&usb_if->read_data);

fail:
	return err;
}

#if 0
// no more used since USB-PRO: submiting read is done at init time since
// USB-PRO initialization may need some messages exchanges.

//****************************************************************************
// start and stop functions for CAN data IN and OUT
static int pcan_usb_start(struct pcandev *dev)
{
	int err = 0;
	USB_PORT *u = &dev->port.usb;
	struct pcan_usb_interface *usb_if = u->usb_if;

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d), minor = %d.\n",
	        DEVICE_NAME, __func__, u->dev_ctrl_index, dev->nMinor);

	/* if not, wait for packet on the interface */
	if (!atomic_read(&usb_if->read_data.use_count))
	{
		FILL_BULK_URB(&usb_if->read_data, usb_if->usb_dev,
		              usb_rcvbulkpipe(usb_if->usb_dev,
		                              usb_if->pipe_read.ucNumber),
		              usb_if->read_buffer_addr[0], usb_if->read_buffer_size,
		              pcan_usb_read_notify, usb_if);

		// submit urb
		if ((err = __usb_submit_urb(&usb_if->read_data)))
			printk(KERN_ERR "%s: %s() can't submit! (%d)\n",
		          DEVICE_NAME, __func__, err);
		else
			atomic_inc(&usb_if->active_urbs);
	}

	return err;
}
#endif

int pcan_kill_sync_urb(struct urb *urb)
{
	int err = 0;

	if (urb->status == -EINPROGRESS)
	{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,10)
		usb_kill_urb(urb);
#else
		err = usb_unlink_urb(urb);
#endif
		DPRINTK(KERN_DEBUG "%s: %s() done...\n", DEVICE_NAME, __func__);
	}

	return err;
}

static int pcan_usb_stop(struct pcandev *dev)
{
	int err = 0;
	USB_PORT *u = &dev->port.usb;
	struct pcan_usb_interface *usb_if = u->usb_if;

	DPRINTK(KERN_DEBUG "%s: %s(CAN#%d), minor=%d\n",
	        DEVICE_NAME, __func__, u->dev_ctrl_index, dev->nMinor);

	if (!usb_if)
		return -ENODEV;

	if (usb_if->device_ctrl_close)
		err = usb_if->device_ctrl_close(dev);

	err = usb_if->device_ctrl_set_bus_off(dev);

	if (usb_if->dev_opened_count > 0)
		u->usb_if->dev_opened_count--;
#if 1
	/* let bus_off handler decide if we should wait or not */
#else
	// wait until all has settled
	mdelay(5);
#endif
	// unlink URBs for device/controller
	pcan_kill_sync_urb(&u->write_data);

	DPRINTK(KERN_ERR "%s: have still %d active URBs on interface\n",
	        DEVICE_NAME, atomic_read(&usb_if->active_urbs));

	return err;
}

//****************************************************************************
// remove device resources
//
static int pcan_usb_cleanup(struct pcandev *dev)
{
	if (dev) {
		USB_PORT *u = &dev->port.usb;

		DPRINTK(KERN_DEBUG "%s: %s(CAN#%d)\n",
			DEVICE_NAME, __func__, u->dev_ctrl_index);

		kfree(u->write_buffer_addr);
		u->write_buffer_addr = NULL;

		switch(dev->wInitStep) {
		case 4:
#if 1
			/* New: unlock any waiting task */
			dev->ucPhysicallyInstalled = 0;
			wake_up_interruptible(&dev->write_queue);
			wake_up_interruptible(&dev->read_queue);
#endif

#ifdef NETDEV_SUPPORT
			pcan_netdev_unregister(dev);
#endif
		case 3:
			usb_devices--;
		case 2:
			pcan_del_device_from_list(dev);
		case 1:
		case 0:
			pcan_delete_filter_chain(dev->filter);
			dev->filter = NULL;
		}

		/* just to be sure not doing twice one of the above */
		dev->wInitStep = 0xff;
	} else {
		DPRINTK(KERN_DEBUG "%s: %s(NULL dev)\n", DEVICE_NAME, __func__);
	}

	return 0;
}

// dummy entries for request and free irq
static int pcan_usb_req_irq(struct pcandev *dev)
{
	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __func__);
	return 0;
}

static void pcan_usb_free_irq(struct pcandev *dev)
{
	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __func__);

	// mis-used here for another purpose
	// pcan_usb_free_irq() calls when the last path to device just closing
	// and the device itself is already plugged out
	if ((dev) && (!dev->ucPhysicallyInstalled))
		pcan_usb_cleanup(dev);
}

// interface depended open and close
static int pcan_usb_open(struct pcandev *dev)
{
	DPRINTK(KERN_DEBUG "%s: %s(), minor = %d.\n",
	        DEVICE_NAME, __func__, dev->nMinor);

	return 0;
}

static int pcan_usb_release(struct pcandev *dev)
{
	DPRINTK(KERN_DEBUG "%s: %s(), minor = %d.\n",
	        DEVICE_NAME, __func__, dev->nMinor);

	return 0;
}

// emulated device access functions
// call is only possible if device exists
static int pcan_usb_device_open(struct pcandev *dev, uint16_t btr0btr1,
                                uint8_t bExtended, uint8_t bListenOnly)
{
	int err = 0;
	USB_PORT *u = &dev->port.usb;

	DPRINTK(KERN_DEBUG "%s: %s(), minor = %d. (nOpenPaths=%d)\n",
	        DEVICE_NAME, __func__, dev->nMinor, dev->nOpenPaths);

	// in general, when second open() occurs
	// remove and unlink urbs, when interface is already running
	if ((dev->nOpenPaths) && (dev->device_release))
		dev->device_release(dev);

	/* otherwise, first action: turn CAN off */
	else if ((err = u->usb_if->device_ctrl_set_bus_off(dev)))
		goto fail;

	memset(&u->usb_time, '\0', sizeof(PCAN_USB_TIME));

#if 0
	if ((err = pcan_usb_start(dev)))
		goto fail;
#endif

	// init hardware specific parts
	if ((err = u->usb_if->device_ctrl_open(dev, btr0btr1, bListenOnly)))
		goto fail;

	u->usb_if->dev_opened_count++;

	// store extended mode (standard still accepted)
	dev->bExtended = bExtended;

	// take a fresh status
	dev->wCANStatus = 0;

#if 1
	/* let bus_off handler decide if we should wait or not */
#else
	// copy from NT driver
	mdelay(20);
#endif
	// last action: turn CAN on
	if ((err = u->usb_if->device_ctrl_set_bus_on(dev)))
		goto fail;

	// delay to get first messages read
	set_current_state(TASK_INTERRUPTIBLE);
	schedule_timeout((int)(STARTUP_WAIT_TIME * HZ + 0.9));

fail:
	return err;
}

static void pcan_usb_device_release(struct pcandev *dev)
{
	DPRINTK(KERN_DEBUG "%s: %s(), minor=%d (nOpenPaths=%d).\n",
	        DEVICE_NAME, __func__, dev->nMinor, dev->nOpenPaths);

#if 1
	/* let device bus_off handler whether to wait or not */
#else
	// do not stop usb immediately, give a chance for the PCAN-USB to send
	// this telegram
	schedule();
	mdelay(100);
#endif

	pcan_usb_stop(dev);
}

//****************************************************************************
// get or set special device related parameters
static int  pcan_usb_device_params(struct pcandev *dev, TPEXTRAPARAMS *params)
{
	int err;
	USB_PORT *u = &dev->port.usb;

	DPRINTK(KERN_DEBUG "%s: %s(%d)\n", DEVICE_NAME, __func__,
	        params->nSubFunction);

	if (!u->usb_if)
		return -ENODEV;

	switch (params->nSubFunction)
	{
	case SF_GET_SERIALNUMBER:
		err = u->usb_if->device_get_snr(u->usb_if, &params->func.dwSerialNumber);
		break;
	case SF_GET_HCDEVICENO:
		/* can cast to uint32_t * since "func" is an union with dwSerialNumber */
		err = u->usb_if->device_ctrl_get_dnr(dev,
		                                //(uint32_t *)&params->func.ucHCDeviceNo);
		                                &params->func.dwSerialNumber);
		break;
	case SF_SET_HCDEVICENO:
		//err = u->usb_if->device_ctrl_set_dnr(dev, params->func.ucHCDeviceNo);
		err = u->usb_if->device_ctrl_set_dnr(dev, params->func.dwSerialNumber);
		/* Should update dev object cache with new value (see /dev/pcan display)*/
		if (err == 0) u->ucHardcodedDevNr = params->func.ucHCDeviceNo;
		break;

	default:
		DPRINTK(KERN_DEBUG "%s: Unknown sub-function %d!\n",
		        DEVICE_NAME, params->nSubFunction);

		return -EINVAL;
	}

	return err;
}

#ifndef LINUX_26
//****************************************************************************
// special assignment of minors due to PuP
//
static int assignMinorNumber(struct pcandev *dev)
{
	int searchedMinor;
	uint8_t occupied;
	struct pcandev   *devWork = (struct pcandev *)NULL;
	struct list_head *ptr;

	DPRINTK(KERN_DEBUG "%s: assignMinorNumber()\n", DEVICE_NAME);

	for (searchedMinor = PCAN_USB_MINOR_BASE; searchedMinor < (PCAN_USB_MINOR_BASE + 8); searchedMinor++)
	{
		occupied = 0;

		// loop trough my devices
		for (ptr = pcan_drv.devices.next; ptr != &pcan_drv.devices; ptr = ptr->next)
		{
			devWork = (struct pcandev *)ptr;

			// stop if it is occupied
			if (devWork->nMinor == searchedMinor)
			{
				occupied = 1;
				break;
			}
		}

		// jump out when the first available number is found
		if (!occupied)
			break;
	}

	if (!occupied)
	{
		dev->nMinor = searchedMinor;
		return 0;
	}
	else
	{
		dev->nMinor = -1;
		return -ENXIO;
	}
}
#endif

//****************************************************************************
// things to do after plugin or plugout of device (and power on too)
//
#ifdef LINUX_26

#ifdef PCAN_DEV_USES_ALT_NUM

#define PCAN_DEVICE_ATTR(_v, _name, _show) \
	struct device_attribute pcan_dev_attr_##_v = \
					__ATTR(_name, S_IRUGO, _show, NULL)

static struct pcandev *pcan_usb_to_pcan(struct device *dev)
{
	struct usb_interface *interface = to_usb_interface(dev->parent);
	struct pcan_usb_interface *usb_if = usb_get_intfdata(interface);
	return (struct pcandev *)&usb_if->dev[0];
}

static ssize_t show_dev_pcan_hwtype_x(int can_idx, struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	struct pcandev *pdev = pcan_usb_to_pcan(dev) + can_idx;

	return snprintf(buf, PAGE_SIZE, "%u\n", pdev->wType);
}

static ssize_t show_dev_pcan_devid_x(int can_idx, struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	struct pcandev *pdev = pcan_usb_to_pcan(dev) + can_idx;

	return snprintf(buf, PAGE_SIZE, "%u\n", pdev->device_alt_num);
}

static ssize_t show_dev_pcan_minor_x(int can_idx, struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	struct pcandev *pdev = pcan_usb_to_pcan(dev) + can_idx;

	return snprintf(buf, PAGE_SIZE, "%d\n", pdev->nMinor);
}

static ssize_t show_dev_pcan_hwtype0(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	return show_dev_pcan_hwtype_x(0, dev, attr, buf);
}

static ssize_t show_dev_pcan_devid0(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	return show_dev_pcan_devid_x(0, dev, attr, buf);
}

static ssize_t show_dev_pcan_minor0(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	return show_dev_pcan_minor_x(0, dev, attr, buf);
}

static PCAN_DEVICE_ATTR(devid0, pcan_devid, show_dev_pcan_devid0);
static PCAN_DEVICE_ATTR(minor0, pcan_minor, show_dev_pcan_minor0);
static PCAN_DEVICE_ATTR(hwtype0, pcan_hwtype, show_dev_pcan_hwtype0);

static ssize_t show_dev_pcan_hwtype1(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	return show_dev_pcan_hwtype_x(1, dev, attr, buf);
}

static ssize_t show_dev_pcan_devid1(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	return show_dev_pcan_devid_x(1, dev, attr, buf);
}

static ssize_t show_dev_pcan_minor1(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	return show_dev_pcan_minor_x(1, dev, attr, buf);
}

static PCAN_DEVICE_ATTR(devid1, pcan_devid, show_dev_pcan_devid1);
static PCAN_DEVICE_ATTR(minor1, pcan_minor, show_dev_pcan_minor1);
static PCAN_DEVICE_ATTR(hwtype1, pcan_hwtype, show_dev_pcan_hwtype1);

static struct attribute *pcan_usb_sysfs_attrs[][4] = {
	{
		&pcan_dev_attr_devid0.attr,
		&pcan_dev_attr_minor0.attr,
		&pcan_dev_attr_hwtype0.attr,
		NULL
	},
	{
		&pcan_dev_attr_devid1.attr,
		&pcan_dev_attr_minor1.attr,
		&pcan_dev_attr_hwtype1.attr,
		NULL
	},
};
#endif /* PCAN_DEV_USES_ALT_NUM */

static int pcan_usb_create_dev(struct pcan_usb_interface *usb_if,
                               int ctrl_index)
{
	int err, retry;
	struct pcandev *dev;
	struct usb_device *usb_dev = usb_if->usb_dev;
	USB_PORT *u;
	void *h;

	dev = (struct pcandev *)&usb_if->dev[ctrl_index];

	u = &dev->port.usb;
	u->usb_if = usb_if;
	u->dev_ctrl_index = ctrl_index;

	switch (usb_dev->descriptor.idProduct) {

#ifdef HW_USB_FD
	case PCAN_USBFD_PRODUCT_ID:

		/* init structure elements to defaults */
		pcan_soft_init(dev, "usbfd", HW_USB_FD);
		break;
#endif
#ifdef HW_USB_PRO_FD
	case PCAN_USBPROFD_PRODUCT_ID:

		/* init structure elements to defaults */
		pcan_soft_init(dev, "usbpfd", HW_USB_PRO_FD);
		break;
#endif
#ifdef HW_USB_PRO
	case PCAN_USBPRO_PRODUCT_ID:

		/* init structure elements to defaults */
		pcan_soft_init(dev, "usbpro", HW_USB_PRO);
		break;
#endif

	case PCAN_USB_PRODUCT_ID:
	default:

		// init structure elements to defaults
		pcan_soft_init(dev, "usb", HW_USB);
		break;
	}

	// override standard device access functions
	dev->device_open = pcan_usb_device_open;
	dev->device_write = pcan_usb_write;
	dev->device_release = pcan_usb_device_release;

	// init process wait queues
	init_waitqueue_head(&dev->read_queue);
	init_waitqueue_head(&dev->write_queue);

	// set this before any instructions, fill struct pcandev, part 1
	dev->readreg     = NULL;
	dev->writereg    = NULL;
	dev->cleanup     = pcan_usb_cleanup;
	dev->req_irq     = pcan_usb_req_irq;
	dev->free_irq    = pcan_usb_free_irq;
	dev->open        = pcan_usb_open;
	dev->release     = pcan_usb_release;
	dev->filter      = pcan_create_filter_chain();
	dev->device_params = pcan_usb_device_params;

	printk(KERN_INFO "%s: usb hardware revision = %d\n", DEVICE_NAME,
	       usb_if->ucRevision);

	dev->wInitStep = 1;

	dev->nMajor = USB_MAJOR;
	dev->nMinor = -1;

	/* assign the device as plugged in */
	dev->ucPhysicallyInstalled = 1;

	/* add this device to the list */
	pcan_add_device_in_list(dev);
	dev->wInitStep = 2;

	usb_devices++;
	dev->wInitStep = 3;

#ifdef PCAN_DEV_USES_ALT_NUM
	/* get serial number as soon as possible */
	usb_if->device_get_snr(usb_if, &usb_if->dwSerialNumber);

	/* Get device number early too (sometimes, need to retry...) */
	for (retry=3; retry; retry--) {
		uint32_t device_nr32;
		err = usb_if->device_ctrl_get_dnr(dev, &device_nr32);
		if (!err) {

			u->ucHardcodedDevNr = (uint8_t )device_nr32;

#ifdef DEBUG
			pr_info("%s(): CAN%u devid=%xh (%u)\n",
				__func__, ctrl_index, device_nr32, device_nr32);
#endif
			break;
		}
	}
#endif

	/* Handle controller list per interface */
	h = usb_get_intfdata(usb_if->usb_intf);

	/* must tell that this interface is not in use for all controllers, */
	/* especially for controllers > 0 (kernel>2.6.26) */
	usb_if->usb_intf->minor = -1;
	if ((err = usb_register_dev(usb_if->usb_intf, &pcan_class)) < 0)
	{
		printk(KERN_ERR "%s: unable to register usb device for CAN#%u (err=%d)\n",
		       DEVICE_NAME, ctrl_index, err);

		usb_set_intfdata(usb_if->usb_intf, h);
		goto reject;
	}

	dev->nMinor = usb_if->usb_intf->minor;

#ifdef PCAN_DEV_USES_ALT_NUM
	dev->mapped_dev = usb_if->usb_intf->usb_dev;
	pcan_sysfs_add_attrs(dev->mapped_dev, pcan_usb_sysfs_attrs[ctrl_index]);
#endif

	// set device in inactive state to prevent violating the bus
	usb_if->device_ctrl_set_bus_off(dev);

#ifndef PCAN_DEV_USES_ALT_NUM
	// get serial number early
	usb_if->device_get_snr(usb_if, &usb_if->dwSerialNumber);

	/* Get device number early too */
	/* sometimes, need to retry... */
	for (retry=3; retry; retry--)
	{
		uint32_t device_nr32;
		err = usb_if->device_ctrl_get_dnr(dev, &device_nr32);
		if (!err)
		{
			u->ucHardcodedDevNr = (uint8_t )device_nr32;
			break;
		}
	}
#endif

	/* Call hardware supplied own callback to do some private init */
	if (usb_if->device_ctrl_init)
	{
		err = usb_if->device_ctrl_init(dev);
		if (err)
			printk(KERN_ERR "%s: CAN#%u initialization not complete (err=%d)\n",
			       DEVICE_NAME, ctrl_index, err);
	}

#ifdef NETDEV_SUPPORT
	pcan_netdev_register(dev);
#endif

	dev->wInitStep = 4;

	printk(KERN_INFO "%s: usb device minor %d found\n",
	       DEVICE_NAME, dev->nMinor);

	return 0;

reject:
	pcan_usb_cleanup(dev);

	printk(KERN_ERR "%s: %s() failed! (%d)\n", DEVICE_NAME, __func__, err);

	return err;
}

static int pcan_usb_plugin(struct usb_interface *interface,
                           const struct usb_device_id *id)
{
	int err;
	int i, dev_ctrl_count, sizeof_if;
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	struct usb_device *usb_dev = interface_to_usbdev(interface);
	struct pcan_usb_interface *usb_if;
	int (*device_init)(struct pcan_usb_interface *);

	DPRINTK(KERN_DEBUG "%s: %s(0x%04x, 0x%04x, 0x%04x)\n",
	        DEVICE_NAME, __func__,
	        usb_dev->descriptor.idVendor, usb_dev->descriptor.idProduct,
	        usb_dev->descriptor.bcdDevice);

	/* check endpoint addresses (numbers) and associated max data length */
	/* (only from setting 0) */
	/* Since USB-PRO defines also a LIN interface, should reject it when */
	/* adapter plugged: make use of endpoint addresses (no other way...) */
	iface_desc = &interface->altsetting[0];

	DPRINTK(KERN_DEBUG "%s: %s(): bNumEndpoints=%d\n",
	        DEVICE_NAME, __func__, iface_desc->desc.bNumEndpoints);

	for (i=0; i < iface_desc->desc.bNumEndpoints; i++) {
		struct usb_endpoint_descriptor *endpoint =
					&iface_desc->endpoint[i].desc;

		/*
		 * Below is the list of valid ep addreses. Any other ep address
		 * is considered as not-CAN interface address => no dev createdi
		 */
		switch (endpoint->bEndpointAddress) {
		case 0x01:
		case 0x81:
		case 0x02:
		case 0x82:
		case 0x03:
		case 0x83:
			break;
		default:
#ifdef DEBUG
			printk(KERN_INFO
			       "%s: %s(): EP address %02x not in CAN range.\n",
			       DEVICE_NAME, __func__,
			       endpoint->bEndpointAddress);
			printk(KERN_INFO
			       "%s: %s(): ignoring the whole USB interface\n",
			       DEVICE_NAME, __func__);
#endif
			return -ENODEV;
		}
	}

	/*
	 * Does not work with PCAN-USB FD (and 3.14-rc2 ...)
	 *
	 * TODO: check if we could remove this call, because according to
	 * drivers/usb/core/message.c:
	 *
	 * "Instead, the driver [..] may use usb_set_interface() on the
	 * interface it claims"
	 */
	if (usb_dev->descriptor.idProduct != PCAN_USBFD_PRODUCT_ID) {

		/* take the 1st configuration (it's default) */
		if ((err = usb_reset_configuration(usb_dev)) < 0) {
			printk(KERN_ERR
			       "%s: usb_reset_configuration() failed!\n",
			       DEVICE_NAME);
			return err;
		}
	}

	// only 1 interface is supported
	// Note: HW_USB_PRO: interface#0 for CAN, #1 for LIN
	if ((err = usb_set_interface(usb_dev, 0, 0)) < 0) {
		printk(KERN_ERR "%s: usb_set_interface() failed!\n",
		       DEVICE_NAME);
		return err;
	}

	/*
	 * Now, according to device id, create as many device as CAN
	 * controllers
	 */
	switch (usb_dev->descriptor.idProduct) {

#ifdef HW_USB_FD
	case PCAN_USBFD_PRODUCT_ID:
		dev_ctrl_count = 1;
		device_init = pcan_usbfd_init;
		break;
#endif
#ifdef HW_USB_PRO_FD
	case PCAN_USBPROFD_PRODUCT_ID:
		dev_ctrl_count = 2;
		device_init = pcan_usbfd_init;
		break;
#endif
#ifdef HW_USB_PRO
	case PCAN_USBPRO_PRODUCT_ID:
		dev_ctrl_count = 2;
		device_init = pcan_usbpro_init;
		break;
#endif
	case PCAN_USB_PRODUCT_ID:
	default:
		dev_ctrl_count = 1;
		device_init = pcan_usb_init;
		break;
	}

	printk(KERN_INFO "%s: new ", DEVICE_NAME);
	if (usb_dev->speed == USB_SPEED_HIGH)
		printk("high speed ");
	printk("usb adapter with %u CAN controller(s) detected\n",
		dev_ctrl_count);

	/* create our interface object for the USB device */
	sizeof_if = sizeof(struct pcan_usb_interface) + \
				sizeof(struct pcandev) * (dev_ctrl_count-1);

	usb_if = (struct pcan_usb_interface *)kmalloc(sizeof_if, GFP_KERNEL);
	if (!usb_if) {
		printk(KERN_ERR
		       "%s: kmalloc(%d) failed!\n", DEVICE_NAME, sizeof_if);
		return err;
	}

	memset(usb_if, '\0', sizeof_if);

	// store pointer to kernel supplied usb_dev
	usb_if->usb_dev = usb_dev;
	usb_if->usb_intf = interface;
	usb_if->dev_ctrl_count = dev_ctrl_count;

	// preset finish flags
	atomic_set(&usb_if->cmd_sync_complete, 0);
	atomic_set(&usb_if->cmd_async_complete, 1);

	// preset active URB counter
	atomic_set(&usb_if->active_urbs, 0);

	init_waitqueue_head(&usb_if->usb_wait_queue);

	/* get endpoint addresses (numbers) and associated max data length */
	/* (only from setting 0) */
#ifdef HW_USB_PRO
/*
 *      Function   Interface   Endpoints            DeviceId
 *      ---------  ---------   -----------------------------------------
 *      Control                0
 *      CAN        0                                "CAN-Device",
 *                                                  USB\VID_0c72&PID_000d&MI_00
 *                             1=Command,           bidi for both CAN_Ctrller
 *                             2=CAN-Controller 0,  rcv (IN) both CAN-Ctrller,
 *                                                  transmit (OUT) CAN-Ctrl#0,
 *                             3=CAN-Controller 1   transmit (OUT) CAN-Ctrl#1
 *      LIN        1                                "LIN-Device",
 *                                                  USB\VID_0c72&PID_000d&MI_01
 *                             4=Command,
 *                             5=Controller 0,
 *                             6=Controller 1
 */
#endif
	for (i=0; i < iface_desc->desc.bNumEndpoints; i++) {
		PCAN_ENDPOINT *pipe_addr = NULL;

		endpoint = &iface_desc->endpoint[i].desc;

		DPRINTK(KERN_DEBUG "%s: %s(): EP[%d]={addr=%d max=%d}\n",
		        DEVICE_NAME, __func__, i, endpoint->bEndpointAddress,
		        endpoint->wMaxPacketSize);

		switch (endpoint->bEndpointAddress) {
		case 0x01:
			pipe_addr = &usb_if->pipe_cmd_out;
			break;

		case 0x81:
			pipe_addr = &usb_if->pipe_cmd_in;
			break;

		case 0x02:
			switch (usb_dev->descriptor.idProduct) {
#ifdef HW_USB_FD
			case PCAN_USBFD_PRODUCT_ID:
#endif
#ifdef HW_USB_PRO_FD
			case PCAN_USBPROFD_PRODUCT_ID:
#endif
#ifdef HW_USB_PRO
			case PCAN_USBPRO_PRODUCT_ID:
#endif
			case PCAN_USB_PRODUCT_ID:
			default:
				pipe_addr = &usb_if->dev[0].port.usb.pipe_write;
				break;
			}
			break;

		case 0x82:
			pipe_addr = &usb_if->pipe_read;
			break;

		case 0x03:
			switch (usb_dev->descriptor.idProduct) {
#ifdef HW_USB_FD
			case PCAN_USBFD_PRODUCT_ID:
#endif
#ifdef HW_USB_PRO_FD
			case PCAN_USBPROFD_PRODUCT_ID:
#endif
#ifdef HW_USB_PRO
			case PCAN_USBPRO_PRODUCT_ID:
#endif
				pipe_addr = &usb_if->dev[1].port.usb.pipe_write;
				break;
			}

		case 0x83:
			/* Unused pipe for PCAN-USB-PRO */
			/* But seems that need to be reset too... */
			/* TBD */
			break;

		default:
			continue;
		}

		if (pipe_addr) {
			pipe_addr->ucNumber = endpoint->bEndpointAddress;
			pipe_addr->wDataSz  = le16_to_cpu(endpoint->wMaxPacketSize);
		}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30)
		usb_reset_endpoint(usb_dev, endpoint->bEndpointAddress);
#endif
	}

	/* ucRevision needs to be defined before allocating resources (PCAN-USB) */
#if defined(__LITTLE_ENDIAN)
	usb_if->ucHardcodedDevNr = (uint8_t)(usb_if->usb_dev->descriptor.bcdDevice & 0xff);
	usb_if->ucRevision = (uint8_t)(usb_if->usb_dev->descriptor.bcdDevice >> 8);
#elif defined(__BIG_ENDIAN)
	usb_if->ucHardcodedDevNr = (uint8_t)(usb_if->usb_dev->descriptor.bcdDevice >> 8);
	usb_if->ucRevision = (uint8_t)(usb_if->usb_dev->descriptor.bcdDevice & 0xff);
#else
#error "Please fix the endianness defines in <asm/byteorder.h>"
#endif

	DPRINTK(KERN_DEBUG "%s(): ucHardcodedDevNr=0x%02x ucRevision=0x%02X\n", __func__, usb_if->ucHardcodedDevNr, usb_if->ucRevision);

	if ((err = pcan_usb_allocate_resources(usb_if)))
		goto reject;

	usb_set_intfdata(interface, usb_if);

	/* call initialisation callback for entire device */
	device_init(usb_if);

	/* install the reception part for the interface */
	if (!atomic_read(&usb_if->read_data.use_count)) {
		FILL_BULK_URB(&usb_if->read_data, usb_if->usb_dev,
		              usb_rcvbulkpipe(usb_if->usb_dev,
		                              usb_if->pipe_read.ucNumber),
		              usb_if->read_buffer_addr[0],
			      usb_if->read_buffer_size,
		              pcan_usb_read_notify, usb_if);

		// submit urb
		if ((err = __usb_submit_urb(&usb_if->read_data))) {
			printk(KERN_ERR "%s: %s() can't submit! (%d)\n",
		          DEVICE_NAME, __func__, err);
			goto reject;
		}

		atomic_inc(&usb_if->active_urbs);
	}

	/* next, initialize each controller */
	for (i=0; i < usb_if->dev_ctrl_count; i++) {
		err = pcan_usb_create_dev(usb_if, i);
		if (err) {
			for (; i > 0; i--) {
				// TBD pcan_usb_delete_dev();
			}
			break;
		}
	}

reject:
	return err;
}
#else
#if defined(HW_USB_PRO) || defined(HW_USB_PRO_FD) || defined(HW_USB_FD)
#error "Unsupported adapter"
#endif
#ifdef LINUX_24
static void *pcan_usb_plugin(struct usb_device *usb_dev, unsigned int interface,
			     const struct usb_device_id *id_table)
#else
static void *pcan_usb_plugin(struct usb_device *usb_dev, unsigned int interface)
#endif
{
	struct pcandev *dev = NULL;
	int    err = 0;
	int    i;
	USB_PORT *u;
	struct usb_interface_descriptor *current_interface_setting;

	DPRINTK(KERN_DEBUG "%s: pcan_usb_plugin(0x%04x, 0x%04x, %d)\n",
		DEVICE_NAME,
		usb_dev->descriptor.idVendor, usb_dev->descriptor.idProduct,xi
		interface);

	// take the 1st configuration (it's default)
	if (usb_set_configuration (usb_dev, usb_dev->config[0].bConfigurationValue) < 0)
	{
		printk(KERN_ERR "%s: usb_set_configuration() failed!\n", DEVICE_NAME);
		goto reject;
	}

	// only 1 interface is supported
	if (usb_set_interface (usb_dev, 0, 0) < 0) {
		printk(KERN_ERR "%s: usb_set_interface() failed!\n", DEVICE_NAME);
		goto reject;
	}

	// allocate memory for my device
	if ((dev = (struct pcandev *)kmalloc(sizeof(struct pcandev), GFP_ATOMIC)) == NULL)
	{
		printk(KERN_ERR "%s: pcan_usb_plugin - memory allocation failed!\n", DEVICE_NAME);
		goto reject;
	}

	dev->wInitStep = 0;

	u = &dev->port.usb;

	// init structure elements to defaults
	pcan_soft_init(dev, "usb", HW_USB);

	// preset finish flags
	atomic_set(&u->cmd_sync_complete, 0);

	// preset active URB counter
	atomic_set(&u->active_urbs, 0);

	// override standard device access functions
	dev->device_open      = pcan_usb_device_open;
	dev->device_release   = pcan_usb_device_release;
	dev->device_write     = pcan_usb_write;

	// init process wait queues
	init_waitqueue_head(&dev->read_queue);
	init_waitqueue_head(&dev->write_queue);

	// set this before any instructions, fill struct pcandev, part 1
	dev->wInitStep   = 0;
	dev->readreg     = NULL;
	dev->writereg    = NULL;
	dev->cleanup     = pcan_usb_cleanup;
	dev->req_irq     = pcan_usb_req_irq;
	dev->free_irq    = pcan_usb_free_irq;
	dev->open        = pcan_usb_open;
	dev->release     = pcan_usb_release;
	dev->filter      = pcan_create_filter_chain();
	dev->device_params = pcan_usb_device_params;

	if ((err = assignMinorNumber(dev)))
		goto reject;

	// store pointer to kernel supplied usb_dev
	u->usb_dev          = usb_dev;
	u->ucHardcodedDevNr = (uint8_t)(usb_dev->descriptor.bcdDevice & 0xff);
	u->ucRevision       = (uint8_t)(usb_dev->descriptor.bcdDevice >> 8);

	printk(KERN_INFO "%s: usb hardware revision = %d\n", DEVICE_NAME, u->ucRevision);

	// get endpoint addresses (numbers) and associated max data length
	current_interface_setting = &usb_dev->actconfig->interface->altsetting[usb_dev->actconfig->interface->act_altsetting];
	for (i = 0; i < 4; i++) {
		u->Endpoint[i].ucNumber = current_interface_setting->endpoint[i].bEndpointAddress;
		u->Endpoint[i].wDataSz  = current_interface_setting->endpoint[i].wMaxPacketSize;
	}

	init_waitqueue_head(&u->usb_wait_queue);

	dev->wInitStep = 1;

	/* add this device to the list */
	pcan_add_device_in_list(dev);
	dev->wInitStep = 2;

	// assign the device as plugged in
	dev->ucPhysicallyInstalled = 1;

	usb_devices++;
	dev->wInitStep = 3;

	if ((err = pcan_usb_allocate_resources(dev)))
		goto reject;

	dev->wInitStep = 4;

	printk(KERN_INFO "%s: usb device minor %d found\n", DEVICE_NAME, dev->nMinor);

#ifdef NETDEV_SUPPORT
	pcan_netdev_register(dev);
#endif

	return (void *)dev;

reject:
	pcan_usb_cleanup(dev);

	printk(KERN_ERR "%s: pcan_usb_plugin() failed! (%d)\n", DEVICE_NAME, err);

	return NULL;
}
#endif

#ifdef NETDEV_SUPPORT
static void pcan_usb_plugout_netdev(struct pcandev *dev)
{
	struct net_device *ndev = dev->netdev;

	if (ndev)
	{
		netif_stop_queue(ndev);
		pcan_netdev_unregister(dev);
	}
}
#endif

//****************************************************************************
// is called at plug out of device
//
#ifdef LINUX_26
static void pcan_usb_plugout(struct usb_interface *interface)
{
	struct pcan_usb_interface *usb_if = usb_get_intfdata(interface);

	DPRINTK(KERN_DEBUG "%s: %s(): usb_if=%p\n",
					DEVICE_NAME, __func__, usb_if);
	if (usb_if) {
		int c;
		struct pcandev *dev;

		for (dev=&usb_if->dev[c=0]; c < usb_if->dev_ctrl_count;
								c++, dev++) {
			DPRINTK(KERN_DEBUG "%s: %s(%d)\n",
			        DEVICE_NAME, __func__, dev->nMinor);

#ifdef PCAN_DEV_USES_ALT_NUM
			pcan_sysfs_del_attrs(dev->mapped_dev,
						pcan_usb_sysfs_attrs[c]);
#endif

#ifdef NETDEV_SUPPORT
			pcan_usb_plugout_netdev(dev);
#endif

			// mark this device as plugged out
			dev->ucPhysicallyInstalled = 0;

#if 0
			// do not remove resources if the device is still in use
			if (!dev->nOpenPaths)
				pcan_usb_cleanup(dev);
#else
			/*
			 * Should close all dev resources EVEN if the device is
			 * in use, otherwise application may not be noticed
			 * that the device was removed:
			 * CAN_Open(); while (1) CAN_Read(h);
			 */
			pcan_usb_cleanup(dev);

#endif
			/*
			 * don't forget to remove link to USB interface object
			 * from the device object (the USB interface will be
			 * freed next)
			 */
			dev->port.usb.usb_if = NULL;

			pcan_kill_sync_urb(&dev->port.usb.write_data);

			interface->minor = dev->nMinor;
			usb_deregister_dev(interface, &pcan_class);
		}

		pcan_kill_sync_urb(&usb_if->urb_cmd_sync);
		pcan_kill_sync_urb(&usb_if->urb_cmd_async);
		pcan_kill_sync_urb(&usb_if->read_data);

		kfree(usb_if->read_buffer_addr[0]);

		kfree(usb_if->cout_baddr);

		if (usb_if->device_free)
			usb_if->device_free(usb_if);

		usb_reset_device(usb_if->usb_dev);

		kfree(usb_if);

		usb_set_intfdata(interface, NULL);
	}
}

#else

static void pcan_usb_plugout_no_more_used(struct usb_device *usb_dev, void *drv_context)
{
	struct pcandev *dev = (struct pcandev *)drv_context;

	if (dev)
	{
		DPRINTK(KERN_DEBUG "%s: pcan_usb_plugout(%d)\n", DEVICE_NAME, dev->nMinor);

#ifdef NETDEV_SUPPORT
		pcan_usb_plugout_netdev(dev);
#endif

		// mark this device as plugged out
		dev->ucPhysicallyInstalled = 0;

		// do not remove resources if the device is still in use
		if (!dev->nOpenPaths)
			pcan_usb_cleanup(dev);
	}
}
#endif

//****************************************************************************
// small interface to rest of driver, only init and deinit
//
static int pcan_usb_core_init(void)
{
	DPRINTK(KERN_DEBUG "%s: %s() -------------------------------------------\n",
	        DEVICE_NAME, __func__);

	memset (&pcan_drv.usbdrv, 0, sizeof(pcan_drv.usbdrv));

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,24) && LINUX_VERSION_CODE < KERNEL_VERSION(2,6,16)
	pcan_drv.usbdrv.owner       = THIS_MODULE;
#endif

	pcan_drv.usbdrv.probe       = pcan_usb_plugin;
	pcan_drv.usbdrv.disconnect  = pcan_usb_plugout;
	pcan_drv.usbdrv.name        = DEVICE_NAME;
	pcan_drv.usbdrv.id_table    = pcan_usb_ids;

	return usb_register(&pcan_drv.usbdrv);
}

static int pcan_usb_do_cleanup(struct device *dev, void *arg)
{
	struct usb_interface *intf;
	struct pcan_usb_interface *usb_if;
	struct pcandev *pdev;
	int c;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __func__);

	intf = to_usb_interface(dev);
	usb_if = (struct pcan_usb_interface *)usb_get_intfdata(intf);

	/* Browse controllers list */
	for (pdev=&usb_if->dev[c=0]; c < usb_if->dev_ctrl_count; c++, pdev++)
	{
		if (pdev->ucPhysicallyInstalled)

			/* Last chance for URB submitting */
			if (usb_if->device_ctrl_cleanup)
				usb_if->device_ctrl_cleanup(pdev);
	}

	return 0;
}

void pcan_usb_deinit(void)
{
	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __func__);

	if (pcan_drv.usbdrv.probe == pcan_usb_plugin)
	{
		/* Added this since it is the last chance for URB submitting */
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,18)
		int err = driver_for_each_device(&pcan_drv.usbdrv.drvwrap.driver,
		                                 NULL, NULL, pcan_usb_do_cleanup);
#else
		int err = driver_for_each_device(&pcan_drv.usbdrv.driver,
		                                 NULL, NULL, pcan_usb_do_cleanup);
#endif

		/* driver_for_each_device() is declared with "must_check" attribute */
		/* so check err here, knowing that drv is not NULL (1st arg) and that */
		/* pcan_usb_do_cleanup() always return 0... */
		if (err) err = 0;

		// then it was registered
		// unregister usb parts, makes a plugout of registered devices
		usb_deregister(&pcan_drv.usbdrv);
	}
}

//----------------------------------------------------------------------------
// init for usb based devices from peak
int pcan_usb_register_devices(void)
{
	int err;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __func__);

	if (!(err = pcan_usb_core_init()))
	{
		DPRINTK(KERN_DEBUG "%s: %s() is OK\n", DEVICE_NAME, __func__);
	}

	return err;
}
