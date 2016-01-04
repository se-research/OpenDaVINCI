//****************************************************************************
// Copyright (C) 2001-2010  PEAK System-Technik GmbH
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
// Contributions: Philipp Baer (philipp.baer@informatik.uni-ulm.de)
//****************************************************************************

//****************************************************************************
//
// all parts of the isa hardware for pcan-isa devices
//
// $Id: pcan_isa_linux.c $
//
//****************************************************************************

//****************************************************************************
// DEFINES
#define INIT_SAME_IRQ_LIST() init_same_irq_list(dev)

//----------------------------------------------------------------------------
// init shared interrupt linked lists
static inline void init_same_irq_list(struct pcandev *dev)
{
  DPRINTK(KERN_DEBUG "%s: init_same_irq_list(%p)\n", DEVICE_NAME, dev);

  INIT_LIST_HEAD(&dev->port.isa.anchor.same_irq_items); // init to no content
  dev->port.isa.anchor.same_irq_count  = 0;             // no element in list
  dev->port.isa.anchor.same_irq_active = 0;             // no active element
  dev->port.isa.same.dev               = dev;           // points to me
  dev->port.isa.my_anchor              = NULL;          // point to nowhere
}

//----------------------------------------------------------------------------
// create lists of devices with the same irq - base for shared irq handling
void pcan_create_isa_shared_irq_lists(void)
{
  struct pcandev *outer_dev;
  struct pcandev *inner_dev;
  struct list_head *outer_ptr, *inner_ptr;

  DPRINTK(KERN_DEBUG "%s: pcan_create_isa_shared_irq_lists()\n", DEVICE_NAME);

  // loop over all devices for a ISA port with same irq level and not myself
  for (outer_ptr = pcan_drv.devices.next; outer_ptr != &pcan_drv.devices; outer_ptr = outer_ptr->next)
  {
    outer_dev = (struct pcandev *)outer_ptr;

    // if it is a ISA device and still not associated
    if ((outer_dev->wType == HW_ISA_SJA) && (outer_dev->port.isa.my_anchor == NULL))
    {
      outer_dev->port.isa.my_anchor = &outer_dev->port.isa.anchor; // then it is the root of a new list
      outer_dev->port.isa.my_anchor->same_irq_count++;             // I'm the first and - maybe - the only one
      list_add_tail(&outer_dev->port.isa.same.item, &outer_dev->port.isa.my_anchor->same_irq_items); // add to list

      DPRINTK(KERN_DEBUG "%s: main Irq=%d, dev=%p, count=%d\n", DEVICE_NAME,
                         outer_dev->port.isa.wIrq, outer_dev, outer_dev->port.isa.my_anchor->same_irq_count);

      // now search for other devices with the same irq
      for (inner_ptr = outer_ptr->next; inner_ptr != &pcan_drv.devices; inner_ptr = inner_ptr->next)
      {
        inner_dev = (struct pcandev *)inner_ptr;

        // if it is a ISA device and the irq level is the same and it is still not associated
        if ((inner_dev->wType == HW_ISA_SJA) && (inner_dev->port.isa.my_anchor == NULL) && (inner_dev->port.isa.wIrq == outer_dev->port.isa.wIrq))
        {
          inner_dev->port.isa.my_anchor = outer_dev->port.isa.my_anchor; // point and associate to the first with the same irq level
          inner_dev->port.isa.my_anchor->same_irq_count++;               // no - there are more
          list_add_tail(&inner_dev->port.isa.same.item, &inner_dev->port.isa.my_anchor->same_irq_items); // add to list

          DPRINTK(KERN_DEBUG "%s: sub  Irq=%d, dev=%p, count=%d\n", DEVICE_NAME, 
                             inner_dev->port.isa.wIrq, inner_dev, inner_dev->port.isa.my_anchor->same_irq_count);
        }
      }
    }
  }
}

//----------------------------------------------------------------------------
// only one irq-handler per irq level for ISA shared interrupts
static irqreturn_t IRQHANDLER(pcan_isa_irqhandler, int irq, void *dev_id, struct pt_regs *regs)
{
  // loop the list of irq-handlers for all devices with the same 
  // irq-level until at least all devices are one time idle.

  SAME_IRQ_LIST *my_anchor = (SAME_IRQ_LIST *)dev_id;
  struct list_head *ptr;
  struct pcandev *dev;
  int ret        = 0;
  u16 loop_count = 0;
  u16 stop_count = 100;

  // DPRINTK(KERN_DEBUG "%s: pcan_isa_irqhandler(%p)\n", DEVICE_NAME, my_anchor);

  // loop over all ISA devices with same irq level
  for (ptr = my_anchor->same_irq_items.next; loop_count < my_anchor->same_irq_count; ptr = ptr->next)
  {
    if (ptr != &my_anchor->same_irq_items)
    {
      dev = ((SAME_IRQ_ITEM *)ptr)->dev;

      // DPRINTK(KERN_DEBUG "%s: dev=%p\n", DEVICE_NAME, dev);

      if (!IRQHANDLER(sja1000_base_irqhandler, irq, dev, regs))
        loop_count++;
      else
      {
        ret = 1;
        loop_count = 0; // reset, I need at least my_anchor->same_irq_count loops without a pending request
      }

      if (!stop_count--)
      {
        printk(KERN_ERR "%s: Too much ISA interrupt load, processing halted!\n", DEVICE_NAME);
        break;
      }
    }
  }

  return PCAN_IRQ_RETVAL(ret);
}

static int pcan_isa_req_irq(struct pcandev *dev)
{
  int err;

  DPRINTK(KERN_DEBUG "%s: pcan_isa_req_irq(%p)\n", DEVICE_NAME, dev);

  if (dev->wInitStep == 3) // init has finished completly 
  {
    if (!dev->port.isa.my_anchor->same_irq_active) // the first device
    {
      if ((err = request_irq(dev->port.isa.wIrq, pcan_isa_irqhandler, 0, "pcan", dev->port.isa.my_anchor)))
        return err;
    }

    dev->port.isa.my_anchor->same_irq_active++;  // count all ISA devices with same irq
    dev->wInitStep++;
  }

  return 0;
}

static void pcan_isa_free_irq(struct pcandev *dev)
{
  DPRINTK(KERN_DEBUG "%s: pcan_isa_free_irq(%p)\n", DEVICE_NAME, dev);

  if (dev->wInitStep == 4) // irq was installed
  {
    dev->port.isa.my_anchor->same_irq_active--;

    if (!dev->port.isa.my_anchor->same_irq_active) // the last device
      free_irq(dev->port.isa.wIrq, dev->port.isa.my_anchor);

    dev->wInitStep--;
  }
}
