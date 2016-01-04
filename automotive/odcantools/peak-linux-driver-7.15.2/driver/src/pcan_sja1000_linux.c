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
//****************************************************************************

//****************************************************************************
//
// pcan_sja1000_linux.c - all about sja1000 init and data handling
//
// $Id: pcan_sja1000_linux.c $
//
//****************************************************************************

//****************************************************************************
// DEFINES
//#define SJA1000_IRQ_HANDLED 1
#define SJA1000_IRQ_HANDLED            IRQ_HANDLED 
//#define SJA1000_IRQ_NONE 0
#define SJA1000_IRQ_NONE               IRQ_NONE

#define SJA1000_METHOD_ARGS struct pcandev *dev

#define SJA1000_LOCK_IRQSAVE(type)
#define SJA1000_UNLOCK_IRQRESTORE(type)

#define SJA1000_WAKEUP_READ() wake_up_interruptible(&dev->read_queue)
#define SJA1000_WAKEUP_WRITE() wake_up_interruptible(&dev->write_queue)
#define SJA1000_WAKEUP_EMPTY()

#define SJA1000_FUNCTION_CALL(name) name(dev)

//****************************************************************************
// CODE

int IRQHANDLER(sja1000_base_irqhandler, int irq, void *dev_id, struct pt_regs *regs)
{
  register struct pcandev *dev = (struct pcandev *)dev_id;

  return sja1000_irqhandler_common(dev);
}

irqreturn_t IRQHANDLER(sja1000_irqhandler, int irq, void *dev_id, struct pt_regs *regs)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,5,0)
  IRQHANDLER(sja1000_base_irqhandler, irq, dev_id, regs);
#else
  return IRQHANDLER(sja1000_base_irqhandler, irq, dev_id, regs);
#endif
}
