/****************************************************************************ble
 * Copyright (C) 2001-2010  PEAK System-Technik GmbH
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Maintainer(s): Klaus Hitschler (klaus.hitschler@gmx.de)
 *
 * Major contributions by:
 *                Edouard Tisserant (edouard.tisserant@lolitech.fr) XENOMAI
 *                Laurent Bessard   (laurent.bessard@lolitech.fr)   XENOMAI
 *                Oliver Hartkopp   (oliver.hartkopp@volkswagen.de) socketCAN
 *                Stephane Grosjean (s.grosjean@peak-system.com)    USB-PRO
 *
 * Contributions: Philipp Baer (philipp.baer@informatik.uni-ulm.de)
 *                Armin Bauer (armin.bauer@desscon.com)
 ****************************************************************************/

/****************************************************************************
 *
 * all parts to handle the interface specific parts of pcan-pci
 *
 * $Id: pcan_pci.c 877 2015-07-20 08:34:48Z stephane $
 *
 ****************************************************************************/
//#define DEBUG
//#undef DEBUG

/*
 * INCLUDES
 */
#include <src/pcan_common.h>     // must always be the 1st include

#include <linux/ioport.h>
#include <linux/pci.h>      // all about pci
#include <asm/io.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <asm/io.h>
#include <src/pcan_pci.h>
#include <src/pcan_sja1000.h>
#include <src/pcan_filter.h>

#ifdef PCIEC_SUPPORT
#include <src/pcan_pciec.h>
#endif

/****************************************************************************
 * DEFINES
 */
/*
 * If defined, driver will first try to enable MSI mode with the device. On
 * any error, it will fall back into normal INTx mode.
 * If not defined, normal INTx mode will be used, as usual.
 * Undefine it if any problem related to MSI does occur.
 */
//#define PCAN_PCI_USES_MSI

#define PCAN_PCI_MINOR_BASE 0        // the base of all pci device minors

/* important PITA registers */
#define PITA_ICR         0x00        // interrupt control register
#define PITA_GPIOICR     0x18        // general purpose IO interface control register
#define PITA_MISC        0x1C        // miscellanoes register

#define PEAK_PCI_VENDOR_ID   0x001C  // the PCI device and vendor IDs
#define PEAK_PCI_DEVICE_ID   0x0001  // ID for PCI / PCIe Slot cards
#define PEAK_PCIE_CARD_ID    0x0002  // ID for PCIExpress Card
#define PEAK_PCIE_DEVICE_ID  0x0003  // ID for new PCIe Slot cards
#define PEAK_CPCI_ID         0x0004  // ID for new cPCI
#define PEAK_MINIPCI_ID      0x0005  // ID for miniPCI
#define PEAK_PC104PLUS_ID    0x0006  // ID for new PC-104 Plus
#define PEAK_PC104E_ID       0x0007  // ID for PC-104 Express
#define PEAK_MINIPCIE_ID     0x0008  // ID for miniPCIe Slot cards
#define PEAK_PCIE_OEM_ID     0x0009  // ID for PCAN-PCI Express OEM
#define PEAK_PCIE_OEM_ID     0x0009  // ID for PCAN-PCI Express OEM
#define PEAK_PCIE34_CARD_ID  0x000a  // ID for PCAN-Express Card 34

#define PCI_CONFIG_PORT_SIZE 0x1000  // size of the config io-memory
#define PCI_PORT_SIZE        0x0400  // size of a channel io-memory

#ifdef LINUX_26
#define pci_find_device(v, d, x) pci_get_device(v, d, x)
#endif

#ifdef PCAN_PCI_USES_MSI
#define VERSION_REG2		0x44
#define VERSION_REG2_MASK	0xfff
#define VERSION_REG2_MSI	0x110
#endif

/****************************************************************************
 * GLOBALS
 */
#ifdef UDEV_SUPPORT
static const struct pci_device_id pcan_pci_tbl[] =
{
	{PEAK_PCI_VENDOR_ID, PEAK_PCI_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID, 0, 0},
	{PEAK_PCI_VENDOR_ID, PEAK_PCIE_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID, 0, 0},
	{PEAK_PCI_VENDOR_ID, PEAK_CPCI_ID, PCI_ANY_ID, PCI_ANY_ID, 0, 0},
	{PEAK_PCI_VENDOR_ID, PEAK_MINIPCI_ID, PCI_ANY_ID, PCI_ANY_ID, 0, 0},
	{PEAK_PCI_VENDOR_ID, PEAK_PC104PLUS_ID, PCI_ANY_ID, PCI_ANY_ID, 0, 0},
	{PEAK_PCI_VENDOR_ID, PEAK_PC104E_ID, PCI_ANY_ID, PCI_ANY_ID, 0, 0},
	{PEAK_PCI_VENDOR_ID, PEAK_MINIPCIE_ID, PCI_ANY_ID, PCI_ANY_ID, 0, 0},
#ifdef PCIEC_SUPPORT
	{PEAK_PCI_VENDOR_ID, PEAK_PCIE_CARD_ID,  PCI_ANY_ID, PCI_ANY_ID, 0, 0},
	{PEAK_PCI_VENDOR_ID, PEAK_PCIE34_CARD_ID, PCI_ANY_ID, PCI_ANY_ID, 0, 0},
#endif
#ifdef PEAK_PCIE_OEM_ID
	{PEAK_PCI_VENDOR_ID, PEAK_PCIE_OEM_ID,  PCI_ANY_ID, PCI_ANY_ID, 0, 0},
#endif
	{0, }
};

#ifndef PCIEC_SUPPORT
static int pcan_pci_register_driver(struct pci_driver *p_pci_drv)
{
	p_pci_drv->name     = DEVICE_NAME;
	p_pci_drv->id_table = pcan_pci_tbl;

	return pci_register_driver(p_pci_drv);
}

static void pcan_pci_unregister_driver(struct pci_driver *p_pci_drv)
{
	pci_unregister_driver(p_pci_drv);
}
#endif

MODULE_DEVICE_TABLE(pci, pcan_pci_tbl);
#endif

/****************************************************************************
 * LOCALS
 */
static u16 _pci_devices = 0; // count the number of pci devices
static u16 _pci_driver_registered = 0;

/****************************************************************************
 * CODE
 */
#ifdef NO_RT
#include "pcan_pci_linux.c"
#else
#include "pcan_pci_rt.c"
#endif

/* read a register */
static u8 pcan_pci_readreg(struct pcandev *dev, u8 port)
{
	u32 lPort = port << 2;
	return readb(dev->port.pci.pvVirtPort + lPort);
}

/* write a register */
static void pcan_pci_writereg(struct pcandev *dev, u8 port, u8 data)
{
	u32 lPort = port << 2;
	writeb(data, dev->port.pci.pvVirtPort + lPort);
}

static const u16 pita_icr_masks[] = { 0x0002, 0x0001, 0x0040, 0x0080 };

/* select and clear in Pita stored interrupt */
void pcan_pci_clear_stored_interrupt(struct pcandev *dev)
{
	u16 pita_icr_mask = pita_icr_masks[dev->port.pci.nChannel];
	u16 pita_icr_low = readw(dev->port.pci.pvVirtConfigPort + PITA_ICR);

	if (pita_icr_low & pita_icr_mask) {
		writew(pita_icr_mask, 
				dev->port.pci.pvVirtConfigPort + PITA_ICR);
#if 0//ndef PCAN_PCI_USES_MSI
		/* 
		 * PCIe: in order to be sure that the PCIe message 
		 * "deassert INTx" has been received, issue a dummy read 
		 * instruction next.
		 *
		 * (useless with MSI)
		 */
		readw(dev->port.pci.pvVirtConfigPort + PITA_ICR);
#endif
	}
}

/* enable interrupt again */
void pcan_pci_enable_interrupt(struct pcandev *dev)
{
	u16 pita_icr_mask = pita_icr_masks[dev->port.pci.nChannel];
	u16 pita_icr_high = 
		readw(dev->port.pci.pvVirtConfigPort + PITA_ICR + 2);

	DPRINTK(KERN_DEBUG "%s: %s(%u): PITA ICR=%04Xh\n",
			DEVICE_NAME, __func__,
			dev->nMinor, pita_icr_high);

	pita_icr_high |= pita_icr_mask;
	writew(pita_icr_high, dev->port.pci.pvVirtConfigPort + PITA_ICR + 2);

	dev->wInitStep++;
}

static void pcan_pci_free_irq(struct pcandev *dev)
{
	if (dev->wInitStep == 6) {

		/* disable interrupt */
		u16 pita_icr_mask = pita_icr_masks[dev->port.pci.nChannel];
		u16 pita_icr_high = 
			readw(dev->port.pci.pvVirtConfigPort + PITA_ICR + 2);

		DPRINTK(KERN_DEBUG "%s: %s(%u): PITA ICR=%04Xh\n",
				DEVICE_NAME, __func__,
				dev->nMinor, pita_icr_high);

		pita_icr_high &= ~pita_icr_mask;
		writew(pita_icr_high, 
				dev->port.pci.pvVirtConfigPort + PITA_ICR + 2);

		/* read it again, to wait for write command to complete */
		//readw(dev->port.pci.pvVirtConfigPort + PITA_ICR + 2);

		PCI_FREE_IRQ();

		dev->wInitStep--;
	}
}

/* release and probe */
static int pcan_pci_cleanup(struct pcandev *dev)
{
	DPRINTK(KERN_DEBUG "%s: pcan_pci_cleanup()\n", DEVICE_NAME);

	switch(dev->wInitStep) {
	case 6:
		pcan_pci_free_irq(dev);
	case 5:
#ifdef PCIEC_SUPPORT
		pcan_pciec_delete_card(dev);
#endif
		_pci_devices--;
	case 4:
		iounmap(dev->port.pci.pvVirtPort);
	case 3:
		release_mem_region(dev->port.pci.dwPort, PCI_PORT_SIZE);
	case 2:
		if (dev->port.pci.nChannel == 0)
			iounmap(dev->port.pci.pvVirtConfigPort);
	case 1:
		if (dev->port.pci.nChannel == 0)
			release_mem_region(dev->port.pci.dwConfigPort,
							PCI_CONFIG_PORT_SIZE);
	case 0:
		pcan_delete_filter_chain(dev->filter);
		dev->filter = NULL;
		dev->wInitStep = 0;
#ifdef UDEV_SUPPORT
#ifndef PCIEC_SUPPORT
		if (_pci_devices == 0 && _pci_driver_registered)
			pcan_pci_unregister_driver(&pcan_drv.pci_drv);
#endif
#endif
	}

	return 0;
}

/* interface depended open and close */
static int pcan_pci_open(struct pcandev *dev)
{
	dev->ucActivityState = ACTIVITY_IDLE;
	return 0;
}

static int pcan_pci_release(struct pcandev *dev)
{
	dev->ucActivityState = ACTIVITY_INITIALIZED;
	return 0;
}

#ifdef PCAN_PCI_USES_MSI
static int pcan_pci_enable_msi(struct pci_dev *pci_dev, struct pcan_msi *msi)
{
	int err = -EINVAL;

	int nvec = msi->msi_requested;

	DPRINTK(KERN_DEBUG
		"%s: %s():msi_requested=%d msi_enabled=%d msix_enabled=%d\n",
		DEVICE_NAME, __func__,
		msi->msi_requested,
		pci_dev->msi_enabled, pci_dev->msix_enabled);

	/*
	 * should test before: some config runs with msi aloread enabled for
	 * PCI device. This test removes ugly WARNING in logs for 3.0.0.
	 */
	if (pci_dev_msi_enabled(pci_dev))
		return 0;
#ifdef DEBUG
	{
		int pos = pci_find_capability(pci_dev, PCI_CAP_ID_MSI);

		if (!pos) {
			pr_warn("%s: pci_find_capability() failure\n",
				DEVICE_NAME);
		} else {
			u16 msgctl;
			int maxvec;

			pci_read_config_word(pci_dev,
						pos + PCI_MSI_FLAGS, &msgctl);
			maxvec = 1 << ((msgctl & PCI_MSI_FLAGS_QMASK) >> 1);
			pr_info("%s: maxvec=%d\n", DEVICE_NAME, maxvec);
		}
	}
#endif

	while (1) {
		err = pci_enable_msi_block(pci_dev, nvec);

#ifdef DEBUG
		pr_info("%s: pci_enable_msi_block(%d) status=%d\n",
			DEVICE_NAME, nvec, err);
#endif
		if (!err) {
			/* disable PCI INTx for device */
			pci_intx(pci_dev, 0);
			msi->msi_assigned = nvec;
			break;
		}

		if (err < 0) {
			pr_warn("%s: enabling MSI mode err=%d\n",
				DEVICE_NAME, err);
			break;
		}

		nvec = err;
	}

	return err;
}
#endif /* PCAN_PCI_USES_MSI */

static int pcan_pci_channel_init(struct pcandev *dev, struct pci_dev *pciDev,
				u32 dwConfigPort, u32 dwPort, u16 wIrq,
				struct pcandev *mastr_dev)
{
#if LINUX_VERSION_CODE <= KERNEL_VERSION(4,0,0)
	int err;
#endif

	DPRINTK(KERN_DEBUG "%s: %s(), irq=%d _pci_devices = %d\n",
		DEVICE_NAME, __func__, wIrq, _pci_devices);

	/* obsolete - will be removed soon */
	dev->props.ucMasterDevice = CHANNEL_MASTER;

	/* init process wait queues */
	init_waitqueue_head(&dev->read_queue);
	init_waitqueue_head(&dev->write_queue);

	/* set this before any instructions, fill struct pcandev, part 1 */
	dev->wInitStep   = 0;
	dev->readreg     = pcan_pci_readreg;
	dev->writereg    = pcan_pci_writereg;
#ifndef PCIEC_SUPPORT
	dev->cleanup     = pcan_pci_cleanup;
#endif
	dev->req_irq     = pcan_pci_req_irq;
	dev->free_irq    = pcan_pci_free_irq;
	dev->open        = pcan_pci_open;
	dev->release     = pcan_pci_release;
	dev->nMajor      = pcan_drv.nMajor;
	dev->nMinor      = PCAN_PCI_MINOR_BASE + _pci_devices;
	dev->filter      = pcan_create_filter_chain();

	/* fill struct pcandev, part 1 */
	dev->port.pci.dwConfigPort = dwConfigPort;
	dev->port.pci.dwPort = dwPort;
	dev->port.pci.wIrq = wIrq;

	/* reject illegal combination */
	if (!dwPort || !wIrq) {
		pr_info("%s: %s(): illegal combination dwPort=%d wIrq=%d\n",
			DEVICE_NAME, __func__, dwPort, wIrq);
		return -EINVAL;
	}

	/*
	 * do it only if the device is channel master,
	 * and channel 0 is it always
	 */
	if (dev->port.pci.nChannel == 0) {
#ifdef PCAN_PCI_USES_MSI
		u32 v2;
#endif

#if LINUX_VERSION_CODE <= KERNEL_VERSION(4,0,0)
		err = check_mem_region(dev->port.pci.dwConfigPort,
							PCI_CONFIG_PORT_SIZE);
		if (err) {
			pr_info("%s: %s(@%d) "
				"check_mem_region(%xh, %d) err=%d\n",
				DEVICE_NAME, __func__, __LINE__,
				dev->port.pci.dwConfigPort,
				PCI_CONFIG_PORT_SIZE, err);
			return -EBUSY;
		}
#endif

		request_mem_region(dev->port.pci.dwConfigPort,
						PCI_CONFIG_PORT_SIZE, "pcan");

		dev->wInitStep = 1;

		dev->port.pci.pvVirtConfigPort =
				ioremap(dwConfigPort, PCI_CONFIG_PORT_SIZE);
		if (dev->port.pci.pvVirtConfigPort == NULL) {
			pr_info("%s: %s(@%d) ioremap(%d, %d) failure\n",
				DEVICE_NAME, __func__, __LINE__,
				dwConfigPort, PCI_CONFIG_PORT_SIZE);
			return -ENODEV;
		}

		dev->wInitStep = 2;

		/* configuration of the PCI chip, part 2: */

		/* set GPIO control register */
		writew(0x0005,
			dev->port.pci.pvVirtConfigPort + PITA_GPIOICR + 2);

		/* enable all channels */
		writeb(0x00, dev->port.pci.pvVirtConfigPort + PITA_GPIOICR);

		/* toggle reset */
		writeb(0x05, dev->port.pci.pvVirtConfigPort + PITA_MISC + 3);
		mdelay(5);

		/* leave parport mux mode */
		writeb(0x04, dev->port.pci.pvVirtConfigPort + PITA_MISC + 3);
		wmb();

#ifdef PCAN_PCI_USES_MSI
		/* read MSI ability of the board */
		v2 = readl(dev->port.pci.pvVirtConfigPort + VERSION_REG2);
		if (((v2 >> 4) & VERSION_REG2_MASK) >= VERSION_REG2_MSI) {
			dev->port.pci.msi.msi_requested = 4;
			dev->port.pci.msi.msi_assigned = 0;
			pcan_pci_enable_msi(pciDev, &dev->port.pci.msi);
			dev->port.pci.wIrq = pciDev->irq;
		}
#endif
	} else {
		dev->port.pci.pvVirtConfigPort =
				mastr_dev->port.pci.pvVirtConfigPort;

#ifdef PCAN_PCI_USES_MSI
		/* adjust MSI/INTA irq from master device IRQ value */
		dev->port.pci.wIrq = mastr_dev->port.pci.wIrq +
			(dev->port.pci.nChannel * \
				mastr_dev->port.pci.msi.msi_assigned) /
					mastr_dev->port.pci.msi.msi_requested;
#endif
	}

#if LINUX_VERSION_CODE <= KERNEL_VERSION(4,0,0)
	err = check_mem_region(dev->port.pci.dwPort, PCI_PORT_SIZE);
	if (err) {
		pr_info("%s: %s(@%d) check_mem_region(%d, %d) err=%d\n",
			DEVICE_NAME, __func__, __LINE__, dev->port.pci.dwPort,
			PCI_PORT_SIZE, err);

		return -EBUSY;
	}
#endif
	request_mem_region(dev->port.pci.dwPort, PCI_PORT_SIZE, "pcan");

	dev->wInitStep = 3;

	dev->port.pci.pvVirtPort = ioremap(dwPort, PCI_PORT_SIZE);

	if (dev->port.pci.pvVirtPort == NULL) {
		pr_info("%s: %s(@%d) ioremap(%d, %d) failure\n",
			DEVICE_NAME, __func__, __LINE__, dwPort, PCI_PORT_SIZE);

		return -ENODEV;
	}

	dev->wInitStep = 4;

	_pci_devices++;
	dev->wInitStep = 5;

	pr_info("%s: pci device minor %d found\n", DEVICE_NAME, dev->nMinor);

	return 0;
}

/*----------------------------------------------------------------------------
 * create one pci based devices from peak
 * - this may be one of multiple from a card
 */
static int create_one_pci_device(struct pci_dev *pciDev, int nChannel,
					struct pcandev *mastr_dev,
					struct pcandev **dev)
{
	struct pcandev *local_dev = NULL;
	int err = 0;

	DPRINTK(KERN_DEBUG "%s: %s(nChannel=%d)\n",
		DEVICE_NAME, __func__, nChannel);

	/* make the first device on board */
	local_dev = (struct pcandev *)kmalloc(sizeof(struct pcandev),
								GFP_KERNEL);
	if (!local_dev) {
		err = -ENOMEM;
		goto fail;
	}

	pcan_soft_init(local_dev, "pci", HW_PCI);

	local_dev->device_open       = sja1000_open;
	local_dev->device_write      = sja1000_write;
	local_dev->device_release    = sja1000_release;
	local_dev->port.pci.nChannel = nChannel;
	local_dev->port.pci.pciDev   = NULL;

	local_dev->props.ucExternalClock = 1;

#ifdef PCIEC_SUPPORT
	/* card pointer must be NULL for all but PCAN-Expresscard */
	local_dev->port.pci.card = NULL;
#endif

	err = pcan_pci_channel_init(local_dev, pciDev,
			(u32)pciDev->resource[0].start,
			(u32)pciDev->resource[1].start + nChannel * 0x400,
			(u16)pciDev->irq,
			mastr_dev);

	if (!err)
		err = sja1000_probe(local_dev);

	if (err) {
#ifndef PCIEC_SUPPORT
		/* Thanks Hardi! */
		local_dev->cleanup(local_dev);
#endif
		kfree(local_dev);
		*dev = NULL;
	} else {
		local_dev->ucPhysicallyInstalled = 1;
		local_dev->port.pci.pciDev = pciDev;

#ifdef PCIEC_SUPPORT
		/* we have a card with i2c controlled blinking LED */
		if ((pciDev->device == PEAK_PCIE_CARD_ID) ||
			(pciDev->device == PEAK_PCIE34_CARD_ID)) {
			/* master channel */
			if (local_dev->port.pci.nChannel == 0)
				local_dev->port.pci.card =
					pcan_pciec_create_card(pciDev,
								local_dev);
			else
				local_dev->port.pci.card =
					pcan_pciec_locate_card(pciDev,
								local_dev);
		}
#endif

		/* add this device to the list */
		list_add_tail(&local_dev->list, &pcan_drv.devices);
		pcan_drv.wDeviceCount++;
		*dev = local_dev;
	}

fail:
	if (err) {
		pr_err("%s: %s(nChannel=%d) discarded - %d\n",
			DEVICE_NAME, __func__, nChannel, err);
	}

	return err;
}

#ifdef PCIEC_SUPPORT
/* move to event driven creation of devices, not for kernels 2.4.x */
static int pcan_pci_probe(struct pci_dev *pciDev,
				const struct pci_device_id *ent)
{
	int err = 0;
	struct pcandev *dev = NULL;
	struct pcandev *mastr_dev = NULL;
	u16 wSubSysID;

	DPRINTK(KERN_DEBUG "%s: %s(%p)\n", DEVICE_NAME, __func__, pciDev);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,10)
	//err = pci_enable_device(pciDev);
	err = pcim_enable_device(pciDev);
	if (err)
		goto fail;
#endif

	/* get the PCI Subsystem-ID */
	err = pci_read_config_word(pciDev, PCI_SUBSYSTEM_ID, &wSubSysID);
	if (err)
		goto fail;

	/* configure the PCI chip, part 1 */
	err = pci_write_config_word(pciDev, PCI_COMMAND, 2);
	if (err)
		goto fail;

	err = pci_write_config_word(pciDev, 0x44, 0);
	if (err)
		goto fail;
	wmb();

	/* add the 1st channel per card */
	err = create_one_pci_device(pciDev, 0, NULL, &dev);
	if (err)
		goto fail;

	mastr_dev = dev;

	if (wSubSysID >= 4) {

		/* add a 2nd channel per card */
		err = create_one_pci_device(pciDev, 1, mastr_dev, &dev);
		if (err)
			goto fail;

		if (wSubSysID >= 10) {

			/* add a 3rd channel per card */
			err = create_one_pci_device(pciDev, 2, mastr_dev, &dev);
			if (err)
				goto fail;

			if (wSubSysID >= 12) {

				/* add the 4th channel per card */
				err = create_one_pci_device(pciDev,
							3, mastr_dev, &dev);
				if (err)
					goto fail;
			}
		}
	}

	_pci_driver_registered = 1;
	return 0;

fail:
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,10)
#ifdef PCAN_PCI_USES_MSI
	pci_disable_msi(pciDev);
#endif
	pci_disable_device(pciDev);
#endif

	return err;
}

static void pcan_pci_remove(struct pci_dev *pciDev)
{
	struct pcandev *dev;
	struct list_head *pos;
	struct list_head *n;

	DPRINTK(KERN_DEBUG "%s: pcan_pci_remove(%p)\n", DEVICE_NAME, pciDev);

	mutex_lock(&pcan_drv.devices_lock);

	list_for_each_prev_safe(pos, n, &pcan_drv.devices) {
		dev = list_entry(pos, struct pcandev, list);
		if ((dev->wType == HW_PCI) && (dev->port.pci.pciDev == pciDev)) {
			pcan_pci_cleanup(dev);
			list_del(&dev->list);
			pcan_drv.wDeviceCount--;

			/*
			 * TODO: a much better hack to address plugging out
			 * while a path to the device is open
			 */
			dev->ucPhysicallyInstalled = 0;

			/* free all device allocated memory */
			kfree(dev);
		}
	}

	mutex_unlock(&pcan_drv.devices_lock);

#ifdef PCAN_PCI_USES_MSI
	pci_disable_msi(pciDev);
#endif
	pci_disable_device(pciDev);
	_pci_driver_registered = 0;
}

int pcan_pci_init(void)
{
	DPRINTK(KERN_DEBUG "%s: pcan_pci_init()\n", DEVICE_NAME);

	pcan_drv.pci_drv.name     = DEVICE_NAME;
	pcan_drv.pci_drv.id_table = pcan_pci_tbl;
	pcan_drv.pci_drv.probe    = pcan_pci_probe;
	pcan_drv.pci_drv.remove   = pcan_pci_remove;

	return pci_register_driver(&pcan_drv.pci_drv);
}

void pcan_pci_deinit(void)
{
	DPRINTK(KERN_DEBUG "%s: pcan_pci_deinit()\n", DEVICE_NAME);

	pci_unregister_driver(&pcan_drv.pci_drv);
}
#else
/*----------------------------------------------------------------------------
 * search all pci based devices from peak
 */
int pcan_search_and_create_pci_devices(void)
{
	int err = 0;
	struct pcandev *dev = NULL;
	struct pcandev *mastr_dev = NULL;

	int n = sizeof(pcan_pci_tbl) / sizeof(pcan_pci_tbl[0]) - 1;
	int i;

	/* search pci devices */
	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __func__);

#ifdef LINUX_26
	if (!CONFIG_PCI)
#else
	if (!pci_present())
#endif
		return 0;

	/* for each device id... */
	for (i = 0; i < n; i++) {
		struct pci_dev *from = NULL;
		struct pci_dev *pciDev;

		/* ...loop looking for all the same adapters */
		do {
			u16 wSubSysID;

			pciDev = pci_find_device(pcan_pci_tbl[i].vendor,
						 pcan_pci_tbl[i].device,
						 from);

			/* 
			 * no (more) device found with that device id.:
			 * break the current device loop to search for any
			 * other PEAK devices...
			 */
			if (!pciDev) {
				DPRINTK(KERN_DEBUG "%s: %s(): i=%d (%04x.%04x) "
					"pciDev=NULL from=%p\n",
					DEVICE_NAME, __func__, i,
					pcan_pci_tbl[i].vendor,
					pcan_pci_tbl[i].device,
					from);
				break;
			}

			/*
			 * a PCI device with PCAN_PCI_VENDOR_ID and
			 * PCAN_PCI_DEVICE_ID was found
			 */
			from = pciDev;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,10)
			err = pci_enable_device(pciDev);
			//err = pcim_enable_device(pciDev);
			if (err) {
				pr_err("%s: %s(): i=%d (%04x.%04x) "
					"pci_enable_device() failed err%d\n",
					DEVICE_NAME, __func__, i,
					pcan_pci_tbl[i].vendor,
					pcan_pci_tbl[i].device,
					err);

				continue;
			}
#endif
			/* get the PCI Subsystem-ID */
			err = pci_read_config_word(pciDev, PCI_SUBSYSTEM_ID,
								&wSubSysID);
			if (err) {
				pr_err("%s: %s(): i=%d (%04x.%04x) "
					"pci_read_config_word() failed err%d\n",
					DEVICE_NAME, __func__, i,
					pcan_pci_tbl[i].vendor,
					pcan_pci_tbl[i].device,
					err);

				goto fail;
			}

			/* configure the PCI chip, part 1 */
			err = pci_write_config_word(pciDev, PCI_COMMAND, 2);
			if (err) {
				pr_err("%s: %s(): i=%d (%04x.%04x) "
				      "pci_write_config_word(1) failed err%d\n",
					DEVICE_NAME, __func__, i,
					pcan_pci_tbl[i].vendor,
					pcan_pci_tbl[i].device,
					err);

				goto fail;
			}

			err = pci_write_config_word(pciDev, 0x44, 0);
			if (err) {
				pr_err("%s: %s(): i=%d (%04x.%04x) "
				      "pci_write_config_word(2) failed err%d\n",
					DEVICE_NAME, __func__, i,
					pcan_pci_tbl[i].vendor,
					pcan_pci_tbl[i].device,
					err);

				goto fail;
			}

			wmb();

			/* 1 channel per card */
			err = create_one_pci_device(pciDev, 0, NULL, &dev);
			if (err)
				goto fail;

			mastr_dev = dev;

			if (wSubSysID < 4)
				goto fail;

			/* add a 2nd channel per card */
			err = create_one_pci_device(pciDev, 1, mastr_dev, &dev);
			if (err || wSubSysID < 10)
				goto fail;

			/* add a 3rd channel per card */
			err = create_one_pci_device(pciDev, 2, mastr_dev, &dev);
			if (err || wSubSysID < 12)
				goto fail;

			/* add the 4th channel per card */
			err = create_one_pci_device(pciDev, 3, mastr_dev, &dev);

fail:
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,10)
			if (err) {
#ifdef PCAN_PCI_USES_MSI
				pci_disable_msi(pciDev);
#endif
				pci_disable_device(pciDev);
			}
#endif
		} while (!err);
	}

	DPRINTK(KERN_DEBUG "%s: %s() status=%d\n", DEVICE_NAME, __func__, err);

#ifdef UDEV_SUPPORT
	/* register only if at least one channel was found */
	if (!err && mastr_dev)
		pcan_pci_register_driver(&pcan_drv.pci_drv);
#endif

	return err;
}
#endif
