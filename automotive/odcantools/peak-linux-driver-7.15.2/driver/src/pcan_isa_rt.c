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
// Contributions: Philipp Baer (philipp.baer@informatik.uni-ulm.de)
//****************************************************************************

//****************************************************************************
//
// all parts of the isa hardware for pcan-isa devices
//
// $Id: pcan_isa_rt.c $
//
//****************************************************************************

//****************************************************************************
// DEFINES
#define INIT_SAME_IRQ_LIST()

static int pcan_isa_req_irq(struct rtdm_dev_context *context)
{
  struct pcanctx_rt *ctx;
  struct pcandev *dev = (struct pcandev *)NULL;
  int err;

  DPRINTK(KERN_DEBUG "%s: pcan_isa_req_irq(%p)\n", DEVICE_NAME, dev);

  ctx = (struct pcanctx_rt *)context->dev_private;
  dev = ctx->dev;
  if (dev->wInitStep == 3) // init has finished completly 
  {
    if ((err = rtdm_irq_request(&ctx->irq_handle, ctx->irq, sja1000_irqhandler_rt, 0, context->device->proc_name, ctx)))
      return err;
    dev->wInitStep++;
  }

  return 0;
}

static void pcan_isa_free_irq(struct pcandev *dev)
{
  DPRINTK(KERN_DEBUG "%s: pcan_isa_free_irq(%p)\n", DEVICE_NAME, dev);

  if (dev->wInitStep == 4) // irq was installed
    dev->wInitStep--;
}
