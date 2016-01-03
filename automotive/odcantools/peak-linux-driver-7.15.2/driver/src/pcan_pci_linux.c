/*****************************************************************************
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
 *
 ****************************************************************************/

/*****************************************************************************
 *
 * all parts to handle device interface specific for pcan-pci
 *
 *  $Id: pcan_pci_linux.c $
 *
 *****************************************************************************/

#define PCI_FREE_IRQ() free_irq(dev->port.pci.wIrq, dev)

/* a special frame around the default irq handler */
static irqreturn_t IRQHANDLER(pcan_pci_irqhandler, int irq, void *dev_id, 
							struct pt_regs *regs)
{
	struct pcandev *dev = (struct pcandev *)dev_id;
	int ret;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,5,0)
	ret = IRQHANDLER(sja1000_irqhandler, irq, dev_id, regs);
#else
	IRQHANDLER(sja1000_irqhandler, irq, dev_id, regs);
	ret = 0; /* supress warning about unused variable */
#endif

	pcan_pci_clear_stored_interrupt(dev);

	return PCAN_IRQ_RETVAL(ret);
}

/* all about interrupt handling */
static int pcan_pci_req_irq(struct pcandev *dev)
{
	int err = 0;

	if (dev->wInitStep == 5) {
		err = request_irq(dev->port.pci.wIrq, pcan_pci_irqhandler,
						IRQF_SHARED, "pcan", dev);
		if (!err)
			pcan_pci_enable_interrupt(dev);
	}

	return err;
}
