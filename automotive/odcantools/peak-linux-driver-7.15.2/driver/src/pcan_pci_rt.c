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
// all parts to handle device interface specific for pcan-pci
//
// $Id: pcan_pci_rt.c $
//
//****************************************************************************

//****************************************************************************
// DEFINES
#define PCI_FREE_IRQ()

//****************************************************************************
// CODE

// a special frame around the default irq handler
static int pcan_pci_irqhandler_rt(rtdm_irq_t *irq_context)
{
  struct pcanctx_rt *ctx;
  struct pcandev *dev;
  int ret;

  ctx = rtdm_irq_get_arg(irq_context, struct pcanctx_rt);
  dev = ctx->dev;

  ret = sja1000_irqhandler_rt(irq_context);

  pcan_pci_clear_stored_interrupt(dev);

  return PCAN_IRQ_RETVAL(ret);
}

// all about interrupt handling
static int pcan_pci_req_irq(struct rtdm_dev_context *context)
{
  struct pcanctx_rt *ctx;
  struct pcandev *dev = (struct pcandev *)NULL;
  int err;

  ctx = (struct pcanctx_rt *)context->dev_private;
  dev = ctx->dev;

  if (dev->wInitStep == 5)
  {
    if ((err = rtdm_irq_request(&ctx->irq_handle, ctx->irq, pcan_pci_irqhandler_rt, RTDM_IRQTYPE_SHARED | RTDM_IRQTYPE_EDGE, context->device->proc_name, ctx)))
    {
      return err;
    }
    pcan_pci_enable_interrupt(dev);
  }

  return 0;
}
