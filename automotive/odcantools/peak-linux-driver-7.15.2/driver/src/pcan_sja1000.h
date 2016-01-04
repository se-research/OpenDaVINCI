#ifndef __SJA1000_H__
#define __SJA1000_H__

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
// sja1000.h - prototypes for sja1000 access functions
//
// $Id: pcan_sja1000.h 518 2007-08-08 07:40:31Z edouard $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <linux/types.h>
#include <linux/interrupt.h> // 2.6. special
#include <src/pcan_common.h>
#include <src/pcan_main.h>

//****************************************************************************
// DEFINES

int  sja1000_open(struct pcandev *dev, u16 btr0btr1, u8 bExtended, u8 bListenOnly);
void sja1000_release(struct pcandev *dev);

#ifndef NO_RT
int sja1000_write(struct pcandev *dev, struct pcanctx_rt *ctx);
int sja1000_irqhandler_rt(rtdm_irq_t *irq_context);
int sja1000_irqhandler_common(struct pcandev *dev, struct pcanctx_rt *ctx);
#else
int sja1000_write(struct pcandev *dev);
int IRQHANDLER(sja1000_base_irqhandler, int irq, void *dev_id, struct pt_regs *regs);
irqreturn_t IRQHANDLER(sja1000_irqhandler, int irq, void *dev_id, struct pt_regs *regs);
int sja1000_irqhandler_common(struct pcandev *dev);
#endif
int  sja1000_write_frame(struct pcandev *dev, struct can_frame *cf);

int  sja1000_probe(struct pcandev *dev);
u16  sja1000_bitrate(u32 dwBitRate);

#endif //__SJA1000_H__
