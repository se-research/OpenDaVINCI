#ifndef __PCAN_FIFO_H__
#define __PCAN_FIFO_H__

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
// pcan_fifo.h - all about fifo buffer management
//
// $Id: pcan_fifo.h 807 2014-12-09 15:34:11Z stephane $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <src/pcan_main.h>

//****************************************************************************
// DEFINES

//****************************************************************************
// PROTOTYPES
int pcan_fifo_reset(register FIFO_MANAGER *anchor);
int pcan_fifo_init(register FIFO_MANAGER *anchor, void *bufferBegin,
		   void *bufferEnd, int nCount, u16 wCopySize);
int pcan_fifo_put(register FIFO_MANAGER *anchor, void *pvPutData);
int pcan_fifo_get(register FIFO_MANAGER *anchor, void *pvPutData);
int pcan_fifo_peek(register FIFO_MANAGER *anchor, void *pvGetData);
int pcan_fifo_status(FIFO_MANAGER *anchor);
int pcan_fifo_not_full(FIFO_MANAGER *anchor);
int pcan_fifo_empty(FIFO_MANAGER *anchor);

#endif // __PCAN_FIFO_H__

