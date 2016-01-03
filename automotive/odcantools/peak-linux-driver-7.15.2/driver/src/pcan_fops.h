#ifndef __PCAN_FOPS_H__
#define __PCAN_FOPS_H__

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
//                Stephane Grosjean (s.grosjean@peak-system.com)    USB-PRO
//                     
//****************************************************************************

//****************************************************************************
//
// pcan_fops.h - header for struct fops only
//
// $Id: pcan_fops.h 753 2014-01-21 10:45:03Z stephane $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <linux/kernel.h>   // printk()
#include <linux/fs.h>       // everything...

#ifndef NO_RT
  #include <rtdm/rtdm_driver.h>
#endif

//****************************************************************************
// DEFINES
#ifndef NO_RT
int pcan_open_path(struct pcandev *dev, struct rtdm_dev_context *context);
void pcan_release_path(struct pcandev *dev, struct pcanctx_rt *ctx);
#else
int pcan_open_path(struct pcandev *dev);
void pcan_release_path(struct pcandev *dev);
#endif
struct pcandev* pcan_search_dev(int major, int minor);

int pcan_ioctl_extended_status_common(struct pcandev *dev, TPEXTENDEDSTATUS *pes);
int pcan_ioctl_status_common(struct pcandev *dev, TPSTATUS *ps);
int pcan_ioctl_diag_common(struct pcandev *dev, TPDIAG *pd);

//****************************************************************************
// GLOBALS

#ifndef NO_RT
extern struct rtdm_device pcandev_rt;
#else
extern struct file_operations pcan_fops;
#endif

#endif // __PCAN_FOPS_H__
