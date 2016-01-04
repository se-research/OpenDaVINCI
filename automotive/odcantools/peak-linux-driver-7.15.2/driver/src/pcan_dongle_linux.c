//****************************************************************************
// Copyright (C) 2001-2010 PEAK System-Technik GmbH
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
//                Philipp Baer (philipp.baer@informatik.uni-ulm.de)
//****************************************************************************

//***************************************************************************
//
// all parts to handle the interface specific parts of pcan-dongle
//
// $Id: pcan_dongle_linux.c $
//
//****************************************************************************

#define PARPORT_REGISTER_DEVICE() return pcan_parport_register_device(p, dev)
#define PARPORT_UNREGISTER_DEVICE() parport_unregister_device(dev->port.dng.pardev)

#ifdef PARPORT_SUBSYSTEM

  #define FREE_IRQ()
  #define PARPORT_CLAIM() result = pcan_parport_claim(dev)
  #define PARPORT_RELEASE() parport_release(dev->port.dng.pardev);

#else

  #define FREE_IRQ() free_irq(dev->port.dng.wIrq, dev)
  #define PARPORT_CLAIM()
  #define PARPORT_RELEASE()

#endif // PARPORT_SUBSYSTEM

//****************************************************************************
// CODE
static int pcan_dongle_req_irq(struct pcandev *dev)
{
  if (dev->wInitStep == 3)
  {
    #ifndef PARPORT_SUBSYSTEM
    int err;
    if ((err = request_irq(dev->port.dng.wIrq, sja1000_irqhandler, IRQF_SHARED, "pcan", dev)))
      return err;
    #endif

    dev->wInitStep++;
  }

  return 0;
}

#ifdef PARPORT_SUBSYSTEM
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
static inline void IRQHANDLER(pcan_parport_irq_handler, int irq, void *dev_id, struct pt_regs *pt)
{
	IRQHANDLER(sja1000_irqhandler, irq, dev_id, pt);
}
#else
static void pcan_parport_irq_handler(void *dev_id)
{
	IRQHANDLER(sja1000_irqhandler, 0, dev_id, NULL);
}
#endif

static int pcan_parport_register_device(struct parport *p, struct pcandev *dev)
{
  dev->port.dng.pardev = parport_register_device(p, "pcan", NULL, NULL, 
                                    pcan_parport_irq_handler, 0, (void *)dev);

  if (!dev->port.dng.pardev)
  {
    DPRINTK(KERN_DEBUG "found no parport device\n");
    return -ENODEV;
  }

  return 0;
}

static int pcan_parport_claim(struct pcandev *dev)
{
  int result = parport_claim(dev->port.dng.pardev);

  if (!result)
  {
    if (dev->port.dng.pardev->port->irq == PARPORT_IRQ_NONE)
    {
      printk(KERN_ERR "%s: no irq associated to parport.\n", DEVICE_NAME);
      result = -ENXIO;
    }
  }
  else
    printk(KERN_ERR "%s: can't claim parport.\n", DEVICE_NAME);

  return result;
}
#endif
