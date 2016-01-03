//****************************************************************************
// Copyright (C) 2001-2007 PEAK System-Technik GmbH
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
// $Id: pcan_dongle_rt.c $
//
//****************************************************************************

//****************************************************************************
// DEFINES
#define PARPORT_REGISTER_DEVICE()
#define PARPORT_UNREGISTER_DEVICE()
#define FREE_IRQ()
#define PARPORT_CLAIM()
#define PARPORT_RELEASE()

//****************************************************************************
// CODE
static int pcan_dongle_req_irq(struct rtdm_dev_context *context)
{
  struct pcanctx_rt *ctx;
  struct pcandev *dev;
  
  ctx = (struct pcanctx_rt *)context->dev_private;
  dev = ctx->dev;

  if (dev->wInitStep == 3)
  {
    int err;
    if ((err = rtdm_irq_request(&ctx->irq_handle, ctx->irq, sja1000_irqhandler_rt,
            RTDM_IRQTYPE_SHARED | RTDM_IRQTYPE_EDGE, context->device->proc_name, ctx)))
    return err;
    dev->wInitStep++;
  }

  return 0;
}
