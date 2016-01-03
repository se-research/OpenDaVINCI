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
// pcan_main.c - the starting point of the driver,
//               init and cleanup and proc interface
//
// $Id: pcan_main.c 820 2015-01-28 16:17:32Z stephane $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <src/pcan_common.h>     // must always be the 1st include
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,16)
#include <linux/config.h>

#elif !defined(AUTOCONF_INCLUDED)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,38)
#include <generated/autoconf.h>
#else
#include <linux/autoconf.h>
#endif
#define AUTOCONF_INCLUDED
#endif

// #define KBUILD_MODNAME pcan

#include <linux/kernel.h>   // DPRINTK()
#include <linux/slab.h>     // kmalloc()
#include <linux/fs.h>       // everything...
#include <linux/errno.h>    // error codes
#include <linux/types.h>    // size_t
#include <linux/proc_fs.h>  // proc
#include <linux/fcntl.h>    // O_ACCMODE
#include <linux/capability.h> // all about restrictions
#include <linux/param.h>    // because of HZ
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 4, 0)
#include <asm/system.h>     // cli(), *_flags
#endif
#include <asm/uaccess.h>    // copy_...

#if LINUX_VERSION_CODE > KERNEL_VERSION(3,9,0)
/* if defined, create_proc_entry() is not used to create /proc/pcan */
#define CREATE_PROC_ENTRY_DEPRECATED
#endif

#include <src/pcan_main.h>

#ifdef PCI_SUPPORT
#include <src/pcan_pci.h>   // get support for PCAN-PCI
#endif
#ifdef ISA_SUPPORT
#include <src/pcan_isa.h>   // get support for PCAN-ISA and PCAN-104
#endif
#ifdef DONGLE_SUPPORT
#include <src/pcan_dongle.h> // get support for PCAN-Dongle
#endif
#ifdef USB_SUPPORT
#include <src/pcan_usb_core.h>   // get support for PCAN-USB
#endif
#ifdef PCCARD_SUPPORT
#include <src/pcan_pccard.h>
#endif
#ifdef NETDEV_SUPPORT
#include <src/pcan_netdev.h>
#endif

#include <src/pcan_fops.h>
#include <src/pcan_fifo.h>
#include <src/pcan_filter.h>

//****************************************************************************
// DEFINES
#define DEFAULT_BTR0BTR1    CAN_BAUD_500K  // defaults to 500 kbit/sec
#define DEFAULT_EXTENDED    1              // catch all frames
#define DEFAULT_LISTENONLY  0

//****************************************************************************
// GLOBALS

// filled by module initialisation
char *type[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
u16  io[8]    = {0, 0, 0, 0, 0, 0, 0, 0};
u8   irq[8]   = {0, 0, 0, 0, 0, 0, 0, 0};
u16  bitrate  = DEFAULT_BTR0BTR1;
char *assign  = NULL;

//----------------------------------------------------------------------------
// the global driver object, create it
struct driverobj pcan_drv = {};

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
//----------------------------------------------------------------------------
// some stuff to support SysFS coming with kernel 2.6
#include <linux/device.h>
#endif

// build current driver config string for output in kernel log and procfs
const char current_config[] = " "
#ifdef DEBUG
"[dbg] "
#endif
#ifdef MODVERSIONS
"[mod] "
#endif
#ifdef ISA_SUPPORT
"[isa] "
#endif
#ifdef PCI_SUPPORT
"[pci] "
#endif
#ifdef PCIEC_SUPPORT
"[pec] "
#endif
#ifdef DONGLE_SUPPORT
"[dng] "
#endif
#ifdef PARPORT_SUBSYSTEM
"[par] "
#endif
#ifdef USB_SUPPORT
"[usb] "
#endif
#ifdef PCCARD_SUPPORT
"[pcc] "
#endif
#ifdef NETDEV_SUPPORT
"[net] "
#endif
#ifndef NO_RT
"[rt] "
#endif
;

// for procfs output the current_config is copied into this string (centered!)
char config[] = "*----------------------------------------------------------------------------";

//****************************************************************************
// LOCALS

//****************************************************************************
// CODE
#ifdef NO_RT
  #include "pcan_main_linux.c"
#else
  #include "pcan_main_rt.c"
#endif

//****************************************************************************
// debug utility
void buffer_dump(u8 *pucBuffer, u16 wLineCount)
{
  #ifdef DEBUG
  int i, j;

  for (i = 0; i < wLineCount; i++)
  {
    printk(KERN_DEBUG "%s: %04x ", DEVICE_NAME, i * 16);

    for (j = 0; j < 8; j++)
      printk(" %02x", *pucBuffer++);

    printk(" ");

    for (j = 0; j < 8; j++)
      printk(" %02x", *pucBuffer++);

    printk("\n");
  }
  #endif
}

/*
 * void dump_mem(char *prompt, void *p, int l)
 *
 */
void dump_mem(char *prompt, void *p, int l)
{
#ifdef DEBUG
	char *kern = KERN_DEBUG;
#else
	char *kern = KERN_INFO;
#endif
	uint8_t *pc = (uint8_t *)p;
	int i;

	printk("%s%s: Dumping %s (%d bytes):\n",
	       kern, DEVICE_NAME, prompt?prompt:"memory", l);
	for (i=0; i < l; )
	{
		if ((i % 16) == 0) printk("%s", kern);
		printk("%02X ", *pc++);
		if ((++i % 16) == 0) printk("\n");
	}
	if (i % 16) printk("\n");
}

//----------------------------------------------------------------------------
// convert struct can_frame to struct TPCANMsg
// To reduce the complexity (and CPU usage) there are no checks (e.g. for dlc)
// here as it is assumed that the creator of the source struct has done this work
void frame2msg(struct can_frame *cf, TPCANMsg *msg)
{
  if (cf->can_id & CAN_ERR_FLAG)
  {
    memset(msg, 0, sizeof(*msg));
    msg->MSGTYPE = MSGTYPE_STATUS;
    msg->LEN     = 4;

    if (cf->can_id & CAN_ERR_CRTL)
    {
      // handle data overrun
      if (cf->data[1] & CAN_ERR_CRTL_RX_OVERFLOW)
        msg->DATA[3] |= CAN_ERR_OVERRUN;

      // handle CAN_ERR_BUSHEAVY
      if (cf->data[1] & CAN_ERR_CRTL_RX_WARNING)
        msg->DATA[3] |= CAN_ERR_BUSHEAVY;
    }

    if (cf->can_id & CAN_ERR_BUSOFF_NETDEV)
      msg->DATA[3] |= CAN_ERR_BUSOFF;

    return;
  }

  if (cf->can_id & CAN_RTR_FLAG)
    msg->MSGTYPE = MSGTYPE_RTR;
  else
    msg->MSGTYPE = MSGTYPE_STANDARD;

  if (cf->can_id & CAN_EFF_FLAG)
    msg->MSGTYPE |= MSGTYPE_EXTENDED;

  msg->ID  = cf->can_id & CAN_EFF_MASK; /* remove EFF/RTR/ERR flags */
  msg->LEN = cf->can_dlc; /* no need to check value range here */

  memcpy(&msg->DATA[0], &cf->data[0], 8); /* also copy trailing zeros */
}

//----------------------------------------------------------------------------
// convert struct TPCANMsg to struct can_frame
// To reduce the complexity (and CPU usage) there are no checks (e.g. for dlc)
// here as it is assumed that the creator of the source struct has done this work
void msg2frame(struct can_frame *cf, TPCANMsg *msg)
{
  cf->can_id = msg->ID;

  if (msg->MSGTYPE & MSGTYPE_RTR)
    cf->can_id |= CAN_RTR_FLAG;

  if (msg->MSGTYPE & MSGTYPE_EXTENDED)
    cf->can_id |= CAN_EFF_FLAG;

  // if (msg->MSGTYPE & MSGTYPE_??????)
  //   cf->can_id |= CAN_ERR_FLAG;

  cf->can_dlc = msg->LEN; /* no need to check value range here */

  memcpy(&cf->data[0], &msg->DATA[0], 8); /* also copy trailing zeros */
}

//----------------------------------------------------------------------------
// request time in msec, fast
u32 get_mtime(void)
{
	//return (jiffies / HZ) * 1000;
	return jiffies_to_msecs(jiffies);
}

// x = (x >= y) ? x - y : 0;
static void subtract_timeval(struct timeval *x, struct timeval *y)
{
  if (x->tv_usec >= y->tv_usec)
    x->tv_usec -= y->tv_usec;
  else
  {
    if (x->tv_sec)
    {
      x->tv_sec--;
      x->tv_usec += (1000000 - y->tv_usec);
    }
    else
      goto fail;
  }

  if (x->tv_sec >= y->tv_sec)
  {
    x->tv_sec -= y->tv_sec;
    return;
  }

  fail:
  x->tv_sec = x->tv_usec = 0;
}

// get relative time to start of driver
void get_relative_time(struct timeval *tv, struct timeval *tr)
{
  if (!tv)
    DO_GETTIMEOFDAY((*tr));
  else
    memcpy(tr, tv, sizeof(*tr));

  subtract_timeval(tr, &pcan_drv.sInitTime);
}

// convert timeval to pcan used milliseconds / microseconds notation
void timeval2pcan(struct timeval *tv, u32 *msecs, u16 *usecs)
{
  *msecs = (u32)(tv->tv_sec * 1000 + tv->tv_usec / 1000);
  *usecs = (u16)(tv->tv_usec % 1000);
}

/*
 * Safe add a new device to the driver registered devices list
 */
void pcan_add_device_in_list(struct pcandev *dev)
{
#ifdef DEBUG
	pr_info("%s: %s(%p)\n", DEVICE_NAME, __func__, dev);
#endif
	mutex_lock(&pcan_drv.devices_lock);
	list_add_tail(&dev->list, &pcan_drv.devices);
	pcan_drv.wDeviceCount++;
	mutex_unlock(&pcan_drv.devices_lock);
}

/*
 * Safe remove a device from the driver registered devices list
 */
void pcan_del_device_from_list(struct pcandev *dev)
{
#ifdef DEBUG
	pr_info("%s: %s(%p)\n", DEVICE_NAME, __func__, dev);
#endif
	mutex_lock(&pcan_drv.devices_lock);
	if (pcan_drv.wDeviceCount)
		pcan_drv.wDeviceCount--;
	list_del(&dev->list);
	mutex_unlock(&pcan_drv.devices_lock);
}

/*
 * Safe check whether a device is linked in the pcan driver devices list.
 */
int pcan_is_device_in_list(struct pcandev *dev)
{
	struct list_head *ptr;
	int found = 0;

#ifdef DEBUG
	pr_info("%s: %s(%p)\n", DEVICE_NAME, __func__, dev);
#endif
	mutex_lock(&pcan_drv.devices_lock);
	list_for_each(ptr, &pcan_drv.devices)
		if (dev == (struct pcandev *)ptr) {
			found = 1;
			break;
		}

	mutex_unlock(&pcan_drv.devices_lock);

	return found;
}

//----------------------------------------------------------------------------
// is called when 'cat /proc/pcan' invoked
#ifdef CREATE_PROC_ENTRY_DEPRECATED
static int pcan_read_procmem(struct seq_file *m, void *v)
{
#else
static int pcan_read_procmem(char *page, char **start, off_t offset, int count,
							int *eof, void *data)
{
	int len = 0;
#endif
	struct pcandev *dev;
	struct list_head *ptr;

	//DPRINTK(KERN_DEBUG "%s: pcan_read_procmem()\n", DEVICE_NAME);

#ifdef CREATE_PROC_ENTRY_DEPRECATED
	seq_printf(m, "\n");
	seq_printf(m,
		"*------------- PEAK-System CAN interfaces (www.peak-system.com) -------------\n");
  	seq_printf(m,
		"*------------- %s (%s) %s %s --------------\n",
		pcan_drv.szVersionString, CURRENT_VERSIONSTRING,
		__DATE__, __TIME__);
	seq_printf(m, "%s\n", config);
	seq_printf(m, "*--------------------- %d interfaces @ major %03d found -----------------------\n",
		pcan_drv.wDeviceCount, pcan_drv.nMajor);
	seq_printf(m,
		"*n -type- -ndev- --base-- irq --btr- --read-- --write- --irqs-- -errors- status\n");
#else
	len += sprintf(page + len, "\n");
	len += sprintf(page + len,
		"*------------- PEAK-System CAN interfaces (www.peak-system.com) -------------\n");
	len += sprintf(page + len,
		"*------------- %s (%s) %s %s --------------\n",
		pcan_drv.szVersionString, CURRENT_VERSIONSTRING,
		__DATE__, __TIME__);
	len += sprintf(page + len, "%s\n", config);
	len += sprintf(page + len,
		"*--------------------- %d interfaces @ major %03d found -----------------------\n",
		pcan_drv.wDeviceCount, pcan_drv.nMajor);
	len += sprintf(page + len,
		"*n -type- -ndev- --base-- irq --btr- --read-- --write- --irqs-- -errors- status\n");
#endif
	/* enter critical section (get mutex) */
	mutex_lock(&pcan_drv.devices_lock);

	/* loop trough my devices */
	for (ptr = pcan_drv.devices.next; ptr != &pcan_drv.devices;
							ptr = ptr->next) {
		u32 dwPort = 0;
		u16 wIrq   = 0;
		int minor;
#ifdef NETDEV_SUPPORT
		struct net_device_stats *stats; /* rx/tx stats */
#endif

		dev = (struct pcandev *)ptr;
		minor = dev->nMinor;

		switch (dev->wType) {
		case HW_ISA_SJA:
			dwPort = dev->port.isa.dwPort;
			wIrq = dev->port.isa.wIrq;
			break;
		case HW_DONGLE_SJA:
		case HW_DONGLE_SJA_EPP:
			dwPort = dev->port.dng.dwPort;
			wIrq = dev->port.dng.wIrq;
			break;
		case HW_PCI:
			dwPort = dev->port.pci.dwPort;
			wIrq = dev->port.pci.wIrq;
			break;
		case HW_USB:
		case HW_USB_FD:
		case HW_USB_PRO:
		case HW_USB_PRO_FD:
#ifdef USB_SUPPORT
			/* get serial number of device */
			if (dev->ucPhysicallyInstalled) {
				dwPort = dev->port.usb.usb_if->dwSerialNumber;
				wIrq = dev->port.usb.ucHardcodedDevNr;
			} else {
				dwPort = 0x00dead00;  /* it is dead */
				wIrq = 0;
			}
#ifdef CONFIG_USB_DYNAMIC_MINORS
			minor += PCAN_USB_MINOR_BASE;
#endif
#endif
			break;
		case HW_PCCARD:
#ifdef PCCARD_SUPPORT
			dwPort = dev->port.pccard.dwPort;
			wIrq = dev->port.pccard.wIrq;
#endif
			break;
		}

#ifdef NETDEV_SUPPORT
		stats = (dev->netdev) ?
				pcan_netdev_get_stats(dev->netdev) : NULL;
#endif
#ifdef CREATE_PROC_ENTRY_DEPRECATED
		seq_printf(m,
#else
		len += sprintf(page + len,
#endif
		"%2d %6s %6s %08x %03d 0x%04x %08lx %08lx %08x %08x 0x%04x\n",
			minor,
			dev->type,
#ifdef NETDEV_SUPPORT
			(dev->netdev) ? (dev->netdev->name) : "can?",
#else
			"-NA-",
#endif
			dwPort,
			wIrq,
			dev->wBTR0BTR1,
#ifdef NETDEV_SUPPORT
			(stats) ? stats->rx_packets : 0,
			dev->writeFifo.dwTotal +
					((stats) ? stats->tx_packets : 0),
#else
			(unsigned long)dev->readFifo.dwTotal,
			(unsigned long)dev->writeFifo.dwTotal,
#endif
			dev->dwInterruptCounter,
			dev->dwErrorCounter,
			dev->wCANStatus);
	}

	/* release mutex */
	mutex_unlock(&pcan_drv.devices_lock);

#ifdef CREATE_PROC_ENTRY_DEPRECATED
	return 0;
#else
	len += sprintf(page + len, "\n");

	*eof = 1;
	return len;
#endif
}

#ifdef CONFIG_SYSFS
int pcan_sysfs_add_attr(struct device *dev, struct attribute *attr)
{
	return sysfs_add_file_to_group(&dev->kobj, attr, NULL);
}

int pcan_sysfs_add_attrs(struct device *dev, struct attribute **attrs)
{
	int err = 0;
	struct attribute **ppa;

#ifdef DEBUG
	printk(KERN_INFO "%s(%p=\"%s\")\n", __func__, dev, dev->kobj.name);
#endif
	for (ppa = attrs; *ppa; ppa++) {
		err = pcan_sysfs_add_attr(dev, *ppa);
		if (err) {
			printk(KERN_ERR
				"failed to add \"%s\" to \"%s\" (err %d)\n",
				(*ppa)->name, dev->kobj.name, err);
			break;
		}
	}

	return err;
}

void pcan_sysfs_del_attr(struct device *dev, struct attribute *attr)
{
	sysfs_remove_file_from_group(&dev->kobj, attr, NULL);
}

void pcan_sysfs_del_attrs(struct device *dev, struct attribute **attrs)
{
	struct attribute **ppa;

#ifdef DEBUG
	printk(KERN_INFO "%s(%p=\"%s\")\n", __func__, dev, dev->kobj.name);
#endif
	for (ppa = attrs; *ppa; ppa++)
		pcan_sysfs_del_attr(dev, *ppa);
}
#else
int pcan_sysfs_add_attrs(struct device *dev, struct attribute **attrs)
{
	return 0;
}
void pcan_sysfs_del_attrs(struct device *dev, struct attribute **attrs) {}
#endif

#ifdef CREATE_PROC_ENTRY_DEPRECATED
static int open_callback(struct inode *inode, struct file *file)
{
	return single_open(file, pcan_read_procmem, NULL);
}

static struct proc_dir_entry *proc_file_entry;

static const struct file_operations proc_file_fops = {
	.owner = THIS_MODULE,
	.open  = open_callback,
	.read  = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};
#else
#define proc_file_entry		NULL
#endif

void remove_dev_list(void)
{
	struct pcandev *dev;
	struct list_head *pos;
	struct list_head *n;

	mutex_lock(&pcan_drv.devices_lock);

	list_for_each_prev_safe(pos, n, &pcan_drv.devices) {
		dev = list_entry(pos, struct pcandev, list);
		if (dev->cleanup)
			dev->cleanup(dev);

		list_del(&dev->list);
		/* free all device allocated memory */
		kfree(dev);
	}

	mutex_unlock(&pcan_drv.devices_lock);
}

/*----------------------------------------------------------------------------
 * is called when the device is removed 'rmmod pcan'
 */
void cleanup_module(void)
{
	DPRINTK(KERN_DEBUG "%s: cleanup_module()\n", DEVICE_NAME);

	switch (pcan_drv.wInitStep) {

	case 4:
		remove_proc_entry(DEVICE_NAME, NULL);
	case 3:
		DEV_UNREGISTER();
	case 2:
#ifdef USB_SUPPORT
		pcan_usb_deinit();
#endif

#ifdef PCCARD_SUPPORT
		pcan_pccard_deinit();
#endif

#ifdef PCIEC_SUPPORT
		pcan_pci_deinit();
#endif
	case 1:
#ifdef UDEV_SUPPORT
		class_destroy(pcan_drv.class);
#endif

#ifdef NO_RT
		unregister_chrdev(pcan_drv.nMajor, DEVICE_NAME);
#endif
		REMOVE_DEV_LIST();

		/* destroy mutex used to access pcan devices list */
		mutex_destroy(&pcan_drv.devices_lock);

	case 0:
		pcan_drv.wInitStep = 0;
	}

	printk(KERN_INFO "%s: removed.\n", DEVICE_NAME);
}

/*----------------------------------------------------------------------------
 * init some equal parts of dev
 */
void pcan_soft_init(struct pcandev *dev, char *szType, u16 wType)
{
	dev->wType            = wType;
	dev->type             = szType;

	dev->nOpenPaths       = 0;
	dev->nLastError       = 0;
	dev->busStatus        = CAN_ERROR_ACTIVE;
	dev->dwErrorCounter   = 0;
	dev->dwInterruptCounter = 0;
	dev->wCANStatus       = 0;
	dev->bExtended        = 1;   /* accept all frames */
	dev->wBTR0BTR1        = bitrate;
	dev->ucCANMsgType     = DEFAULT_EXTENDED;
	dev->ucListenOnly     = DEFAULT_LISTENONLY;

	memset(&dev->props, 0, sizeof(dev->props));

	/* set default access functions */
	dev->device_open      = NULL;
	dev->device_release   = NULL;
	dev->device_write     = NULL;
	dev->cleanup          = NULL;

	dev->device_params    = NULL;    /* the default */

	dev->ucPhysicallyInstalled = 0;  /* assume the device's not installed */
	dev->ucActivityState       = ACTIVITY_NONE;

	atomic_set(&dev->DataSendReady, 1);

	/* init fifos */
	pcan_fifo_init(&dev->readFifo, &dev->rMsg[0],
			&dev->rMsg[READ_MESSAGE_COUNT - 1],
			READ_MESSAGE_COUNT,  sizeof(TPCANRdMsg));
	pcan_fifo_init(&dev->writeFifo, &dev->wMsg[0],
			&dev->wMsg[WRITE_MESSAGE_COUNT - 1],
			WRITE_MESSAGE_COUNT, sizeof(TPCANMsg) );

	INIT_LOCK(&dev->wlock);
	INIT_LOCK(&dev->isr_lock);

#ifdef PCAN_DEV_USES_ALT_NUM
	dev->flags &= ~PCAN_DEV_USES_ALT_NUM;
#endif
}

/*----------------------------------------------------------------------------
 * create all declared Peak legacy devices
 */
static int make_legacy_devices(void)
{
	int result = 0;
	int i;

	DPRINTK(KERN_DEBUG "%s: make_legacy_devices()\n", DEVICE_NAME);

	for (i = 0; ((i < 8) && (type[i] != NULL)); i++) {
#ifdef ISA_SUPPORT
		if (!strncmp(type[i], "isa", 4))
			result = pcan_create_isa_devices(type[i],
								io[i], irq[i]);
#endif

#ifdef DONGLE_SUPPORT
		if (!strncmp(type[i], "sp", 4) || !strncmp(type[i], "epp", 4))
			result = pcan_create_dongle_devices(type[i],
								io[i], irq[i]);
#endif

		if (result)
			break;
	}

#ifdef ISA_SUPPORT
	/* create lists of devices with the same irqs */
	ISA_SHARED_IRQ_LISTS();
#endif

	return result;
}

/*----------------------------------------------------------------------------
 * is called when the device is installed 'insmod pcan.o' or 'insmod pcan.ko'
 */
int init_module(void)
{
	int result = 0;

	memset(&pcan_drv, 0, sizeof(pcan_drv));
	pcan_drv.wInitStep = 0;

	/* store time for timestamp relation, increments in usec */
	DO_GETTIMEOFDAY(pcan_drv.sInitTime);

	/* get the release name global */
	pcan_drv.szVersionString = CURRENT_RELEASE;
	pcan_drv.nMajor = PCAN_MAJOR;

	printk(KERN_INFO "%s: %s ", DEVICE_NAME, pcan_drv.szVersionString);
#if defined(__BIG_ENDIAN)
	printk("(be)\n");
#elif defined(__LITTLE_ENDIAN)
	printk("(le)\n");
#else
#error Endian not set
#endif
	printk(KERN_INFO "%s: driver config%s\n", DEVICE_NAME, current_config);
#ifdef DEBUG
	printk(KERN_INFO "%s: DEBUG is switched on\n", DEVICE_NAME);
#endif

	/*
	 * Copy the centered string only one time and use sizeof() for
	 * compiletime value calculation and optimisation. Also ensure
	 * to have a valid current_config and that it fits into config[]
	 */
	if ((sizeof(current_config) > 3) &&
				(sizeof(config) > sizeof(current_config)))
		strncpy(config + (sizeof(config)-sizeof(current_config))/2,
				current_config, sizeof(current_config)-1);

	INIT_LIST_HEAD(&pcan_drv.devices);
	pcan_drv.wDeviceCount = 0;

	/* initialize mutex used to access pcan devices list */
	mutex_init(&pcan_drv.devices_lock);

#ifndef NO_RT
	INIT_LIST_HEAD(&device_list);
#endif

	/* register the driver by the OS */
#ifdef NO_RT
	result = register_chrdev(pcan_drv.nMajor, DEVICE_NAME, &pcan_fops);
	if (result < 0)
		goto fail;
	else if (!pcan_drv.nMajor)
		pcan_drv.nMajor = result;
#endif

#ifdef UDEV_SUPPORT
	pcan_drv.class = class_create(THIS_MODULE , "pcan");
#endif

	pcan_drv.wInitStep = 1;

#ifdef PCI_SUPPORT
#ifdef PCIEC_SUPPORT
	if ((result = pcan_pci_init()))
		goto fail;
#else
	if ((result = pcan_search_and_create_pci_devices()))
		goto fail;
#endif
	/* search pci devices */
#endif

	/* create isa and dongle devices */
	if ((result = make_legacy_devices()))
		goto fail;

#ifdef USB_SUPPORT
	/* register usb devices only */
	if ((result = pcan_usb_register_devices()))
		goto fail;
#endif

#ifdef PCCARD_SUPPORT
	if ((result = pcan_pccard_register_devices()))
		goto fail;
#endif

#if !defined USB_SUPPORT && !defined PCCARD_SUPPORT
	/* no device found, stop all */
	if (!pcan_drv.wDeviceCount)
		goto fail;
#endif

	pcan_drv.wInitStep = 2;

	result = DEV_REGISTER();
	if (result < 0)
		goto fail;

	if (!pcan_drv.nMajor)
		pcan_drv.nMajor = result;

	pcan_drv.wInitStep = 3;

#ifdef CREATE_PROC_ENTRY_DEPRECATED
	proc_file_entry = proc_create(DEVICE_NAME, 0, NULL, &proc_file_fops);
	if (!proc_file_entry) {
		result = -ENOMEM;
		goto fail;
	}
#else
	/* create the proc entry */
	if (create_proc_read_entry(DEVICE_NAME, 0, NULL,
					pcan_read_procmem, NULL) == NULL) {
		/* maybe wrong if there is no proc filesystem configured */
		result = -ENODEV;
		goto fail;
	}
#endif
	pcan_drv.wInitStep = 4;

	printk(KERN_INFO "%s: major %d.\n", DEVICE_NAME, pcan_drv.nMajor);

	/* succeed */
	return 0;

fail:
	cleanup_module();
	return result;
}
