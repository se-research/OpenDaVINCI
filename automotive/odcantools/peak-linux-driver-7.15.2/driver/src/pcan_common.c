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
// global defines to include in all files this module is made of
// common compatibilty sources
//
// $Id: pcan_common.c 448 2007-01-30 22:41:50Z khitschler $
//
//****************************************************************************

//****************************************************************************
// DEFINES
#include <src/pcan_common.h>
#include <linux/errno.h>
#include <linux/ioport.h>

int ___request_region(unsigned long from, unsigned long length, const char *name)
{
  if (!request_region(from, length, name))
    return -EBUSY;
  
  return 0;
}



