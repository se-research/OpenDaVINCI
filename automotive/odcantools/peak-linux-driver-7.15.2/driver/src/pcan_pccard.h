#ifndef __PCAN_PCCARD_H__
#define __PCAN_PCCARD_H__

//****************************************************************************
// Copyright (C) 2006-2007  PEAK System-Technik GmbH
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
// system dependend parts to handle pcan-pccard
//
// $Id: pcan_pccard.h 447 2007-01-28 14:05:50Z khitschler $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <src/pcan_main.h>

//****************************************************************************
// DEFINES
int  pcan_pccard_register_devices(void);
void pcan_pccard_deinit(void);

#endif // __PCAN_PCCARD_H__
