#ifndef __PCAN_USB_H__
#define __PCAN_USB_H__
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
// Maintainer(s): Stephane Grosjean (s.grosjean@peak-system.com)
//
// Major contributions by:
//                Klaus Hitschler (klaus.hitschler@gmx.de)
//                Oliver Hartkopp   (oliver.hartkopp@volkswagen.de) socketCAN
//                     
//****************************************************************************

//****************************************************************************
//
// pcan_usb.h - the inner usb parts header for pcan-usb support
//
// $Id: pcan_usb.h 753 2014-01-21 10:45:03Z stephane $
//
//****************************************************************************


//****************************************************************************
// DEFINES

//****************************************************************************
// INCLUDES
#include <linux/types.h>
#include <linux/usb.h>

#include <src/pcan_main.h>

//****************************************************************************
// DEFINES
#ifdef LINUX_26
#define __usb_submit_urb(x) usb_submit_urb(x, GFP_ATOMIC)
#define __usb_alloc_urb(x)  usb_alloc_urb(x, GFP_ATOMIC)
#define FILL_BULK_URB(a, b, c, d, e, f, g) usb_fill_bulk_urb(a, b, c, d, e, (usb_complete_t)f, (void *)g)
#else
#define __usb_submit_urb(x) usb_submit_urb(x)
#define __usb_alloc_urb(x)  usb_alloc_urb(x)
#endif

//****************************************************************************
// External API
#ifdef __cplusplus__
extern "C" {
#endif

#ifdef USB_SUPPORT
int pcan_usb_init(struct pcan_usb_interface *dev);
#endif

#ifdef __cplusplus__
};
#endif

#endif // __PCAN_USB_H__

