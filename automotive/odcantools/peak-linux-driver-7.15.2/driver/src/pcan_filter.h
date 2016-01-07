#ifndef __PCAN_FILTER_H__
#define __PCAN_FILTER_H__
//****************************************************************************
// Copyright (C) 2007  PEAK System-Technik GmbH
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
//****************************************************************************

//****************************************************************************
//
// pcan_filter.h - all about CAN message filtering - interface
//
// $Id: pcan_filter.h 461 2007-02-21 23:06:52Z khitschler $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <linux/types.h>

//****************************************************************************
// DEFINES
void *pcan_create_filter_chain(void); // returns a handle pointer
int   pcan_add_filter(void *handle, u32 FromID, u32 ToID, u8 MSGTYPE);
void  pcan_delete_filter_all(void *handle);
int   pcan_do_filter(void *handle, u32 can_id); // take the netdev can_id as input
void  pcan_delete_filter_chain(void *handle);

#endif // __PCAN_FILTER_H__
