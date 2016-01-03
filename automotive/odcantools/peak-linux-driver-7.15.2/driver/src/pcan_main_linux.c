//****************************************************************************
// Copyright (C) 2001-2009  PEAK System-Technik GmbH
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
//                Philipp Baer     (philipp.baer@informatik.uni-ulm.de)
//                Garth Zeglin     (garthz@ri.cmu.edu)
//                Harald Koenig    (H.Koenig@science-computing.de)
//****************************************************************************

//****************************************************************************
//
// pcan_main_linux.c - the starting point of the driver,
//               init and cleanup and proc interface
//
// $Id: pcan_main_linux.c 839 2015-03-13 10:44:53Z stephane $
//
//****************************************************************************

//****************************************************************************
// DEFINES
#define DEV_REGISTER()   dev_register()
#define DEV_UNREGISTER() dev_unregister()
#define REMOVE_DEV_LIST  remove_dev_list
#define ISA_SHARED_IRQ_LISTS pcan_create_isa_shared_irq_lists

//----------------------------------------------------------------------------
// put received CAN frame into chardev receive FIFO
// maybe this goes to a new file pcan_chardev.c some day.
int pcan_chardev_rx_ex(struct pcandev *dev, struct can_frame *cf,
		    struct timeval *tv, u32 flags)
{
	int result = 0;

	// filter out extended messages in non extended mode
	if (dev->bExtended || !(cf->can_id & CAN_EFF_FLAG)) {
		if (!pcan_do_filter(dev->filter, cf->can_id)) {
			TPCANRdMsg msg;
			struct timeval tr;

			get_relative_time(tv, &tr);
			timeval2pcan(&tr, &msg.dwTime, &msg.wUsec);

			/*
			 * convert to old style FIFO message until FIFO
			 * supports new
			 */
			/* struct can_frame and error frames */
			frame2msg(cf, &msg.Msg);

			msg.Msg.MSGTYPE |= flags;

			/* step forward in fifo */
			result = pcan_fifo_put(&dev->readFifo, &msg);

			/*
			 * flag to higher layers that a message was put into
			 * fifo or an error occurred
			 */
			result = (result) ? result : 1;
		}
	}

	return result;
}

// create a UDEV allocated device node
void pcan_device_node_create(struct pcandev *dev)
{
#ifdef UDEV_SUPPORT
	char template[15];

	/* tinker my device node name, eg. "pcanpci%d" */
	strncpy(template, "pcan", sizeof(template));
	strncat(template, dev->type, 6); /* max 'pccard' 'usbpro' */
	strncat(template, "%d", 2);
	DPRINTK(KERN_DEBUG "%s: device_create(%s, %d, %d)\n",
		DEVICE_NAME, template, pcan_drv.nMajor, dev->nMinor);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27)
	device_create(pcan_drv.class, NULL,
		MKDEV(pcan_drv.nMajor, dev->nMinor),
		NULL, template, dev->nMinor);
#else
	device_create(pcan_drv.class, NULL,
		MKDEV(pcan_drv.nMajor, dev->nMinor),
		template, dev->nMinor);
#endif

#endif
}

// destroy a UDEV allocated device node
void pcan_device_node_destroy(struct pcandev *dev)
{
#ifdef UDEV_SUPPORT
	device_destroy(pcan_drv.class, MKDEV(pcan_drv.nMajor, dev->nMinor));
#endif
}

// contrary to former implementation this function only registers devices and do register a driver
// nor request a major number in case of dynamic major number allocation
static int dev_register(void)
{
	DPRINTK(KERN_DEBUG "%s: dev_register()\n", DEVICE_NAME);

#ifdef NETDEV_SUPPORT
	{
		struct list_head *ptr;
		struct pcandev   *pdev;

		// create all netdevice entries except those for hotplug-devices
		// USB   : is done by pcan_usb_plugin().
		// PCCARD: is done by pcan_pccard_register_devices() at driver init time
		//         (here & now! - see above) or at plugin t/ime.
		mutex_lock(&pcan_drv.devices_lock);

		for (ptr=pcan_drv.devices.next; ptr != &pcan_drv.devices;
								ptr=ptr->next) {
			pdev = (struct pcandev *)ptr;
			switch (pdev->wType) {
			case HW_USB:
			case HW_USB_FD:
			case HW_USB_PRO:
			case HW_USB_PRO_FD:
			case HW_PCCARD:
				break;
			default:
				pcan_netdev_register(pdev);
			}
		}

		mutex_unlock(&pcan_drv.devices_lock);
	}
#endif

#ifdef UDEV_SUPPORT
	{
		struct list_head *ptr;
		struct pcandev   *dev;

		mutex_lock(&pcan_drv.devices_lock);

		for (ptr = pcan_drv.devices.next; ptr != &pcan_drv.devices;
							ptr = ptr->next) {
			dev = (struct pcandev *)ptr;

			switch (dev->wType) {
			case HW_PCI:
			case HW_ISA:
			case HW_DONGLE_SJA:
				/*
				 * udev events were not generated for ISA.
				 * Thx David Leonard
				 */
			case HW_ISA_SJA:
			case HW_DONGLE_SJA_EPP:
				pcan_device_node_create(dev);
				break;
			case HW_USB:
			case HW_USB_FD:
			case HW_USB_PRO:
			case HW_USB_PRO_FD:
			case HW_PCCARD:
			default:
				/* do nothing, it's handled at hotplug */
				break;
			}
		}

		mutex_unlock(&pcan_drv.devices_lock);
	}
#endif

	return pcan_drv.nMajor; // for compatibility to former implementation it is returned
}

// contrary to former implementation this function only unregisters only devices
void dev_unregister(void)
{
	DPRINTK(KERN_DEBUG "%s: dev_unregister()\n", DEVICE_NAME);

#ifdef UDEV_SUPPORT
	{
		struct list_head *ptr;
		struct pcandev   *dev;

		mutex_lock(&pcan_drv.devices_lock);

		for (ptr=pcan_drv.devices.next; ptr != &pcan_drv.devices;
								ptr=ptr->next) {
			dev = (struct pcandev *)ptr;

			switch(dev->wType) {
			case HW_PCI:
			case HW_ISA:
			case HW_ISA_SJA:
			case HW_DONGLE_SJA:
			case HW_DONGLE_SJA_EPP:
				pcan_device_node_destroy(dev);
				break;
			case HW_USB:
			case HW_USB_FD:
			case HW_USB_PRO:
			case HW_USB_PRO_FD:
			case HW_PCCARD:
			default:
				// do nothing, it's handled at hot(un)plug
				break;
			}
		}

		mutex_unlock(&pcan_drv.devices_lock);
	}
#endif

#ifdef NETDEV_SUPPORT
	{
		struct list_head *ptr;
		struct pcandev   *pdev;
		// remove all netdevice registrations except those for USB-devices
		// which is done by pcan_usb_plugout().
		mutex_lock(&pcan_drv.devices_lock);

		for (ptr=pcan_drv.devices.next; ptr != &pcan_drv.devices;
								ptr=ptr->next) {
			pdev = (struct pcandev *)ptr;
			switch(pdev->wType) {
			case HW_USB:
			case HW_USB_FD:
			case HW_USB_PRO:
			case HW_USB_PRO_FD:
				break;
			default:
				pcan_netdev_unregister(pdev);
			}
		}

		mutex_unlock(&pcan_drv.devices_lock);
	}
#endif
}
