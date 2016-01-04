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
//                Stephane Grosjean (s.grosjean@peak-system.com)    USB-PRO
//                     
// Contributions: Marcel Offermans (marcel.offermans@luminis.nl)
//                Philipp Baer     (philipp.baer@informatik.uni-ulm.de)
//                Garth Zeglin     (garthz@ri.cmu.edu)
//                Harald Koenig    (H.Koenig@science-computing.de)
//****************************************************************************

//****************************************************************************
//
// pcan_main_rt.c - the starting point of the driver,
//               init and cleanup and proc interface
//
// $Id: pcan_main_rt.c $
//
//****************************************************************************

/*
 * DEFINES
 */
#define DEV_REGISTER		rt_dev_register
#define DEV_UNREGISTER		rt_dev_unregister
#define REMOVE_DEV_LIST		rt_remove_dev_list
#define ISA_SHARED_IRQ_LISTS()

/*
 * GLOBALS
 */
struct list_head device_list;	/* the global driver object, create it */

/*
 * CODE
 */
static int rt_dev_register(void)
{
	struct list_head *ptr;
	struct pcandev *dev;
	struct rtdm_device *rtdmdev;
	struct rt_device *rt_dev;
	int result = 0;

	for (ptr = pcan_drv.devices.next; ptr != &pcan_drv.devices;
							ptr = ptr->next) {
		dev = (struct pcandev *)ptr;

		rtdmdev = (struct rtdm_device *)kmalloc(sizeof(struct rtdm_device), GFP_KERNEL);
		if (!rtdmdev)
			return -ENOMEM;

		rt_dev = (struct rt_device *)kmalloc(sizeof(struct rt_device), GFP_KERNEL);
		if (!rt_dev) {
			kfree(rtdmdev);
			return -ENOMEM;
		}

		memcpy(rtdmdev, &pcandev_rt, sizeof(struct rtdm_device));
		rtdmdev->device_id = MKDEV(dev->nMajor,dev->nMinor);
		snprintf(rtdmdev->device_name, RTDM_MAX_DEVNAME_LEN,
							"pcan%d", dev->nMinor);
		rtdmdev->proc_name = rtdmdev->device_name;
		result = rtdm_dev_register(rtdmdev);

		if (!result) {
			rt_dev->device = rtdmdev;
			list_add_tail(&rt_dev->list, &device_list);
		} else {
			kfree(rtdmdev);
			kfree(rt_dev);
			return result;
		}

	}
	return result;
}

void rt_dev_unregister(void)
{
	struct list_head *ptr = NULL;

	/* unregister all registered devices */
	for (ptr = device_list.next; ptr != &device_list; ptr = ptr->next) {
		rtdm_dev_unregister(((struct rt_device *)ptr)->device, 1000);
	}
}

void rt_remove_dev_list(void)
{
	struct rt_device *rt_dev;

	/* cycle through the list of devices and remove them */
	while (!list_empty(&device_list)) {
		/* empty in reverse order */
		rt_dev = (struct rt_device *)device_list.prev;
		list_del(&rt_dev->list);
		/* free all device allocted memory */
		kfree(rt_dev->device);
		kfree(rt_dev);
	}
	remove_dev_list();
}

int pcan_chardev_rx_ex(struct pcandev *dev, struct can_frame *cf,
			struct timeval *tv, u32 flags)
{
	int result = 0;

	// filter out extended messages in non extended mode
	if (dev->bExtended || !(cf->can_id & CAN_EFF_FLAG)) {
		TPCANRdMsg msg;
		struct timeval tr;
		get_relative_time(tv, &tr);
		timeval2pcan(&tr, &msg.dwTime, &msg.wUsec);

		/* convert to old style FIFO message until FIFO supports new 
		 * struct can_frame and error frames */
		frame2msg(cf, &msg.Msg);

		msg.Msg.MSGTYPE |= flags;

		/* step forward in fifo */
		result = pcan_fifo_put(&dev->readFifo, &msg);

		/* flag to higher layers that a msg was put into fifo or an 
		 * error occurred */
		result = (result) ? result : 1;
	}

	return result;
}
