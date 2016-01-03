#ifndef __PCAN_PCI_H__
#define __PCAN_PCI_H__

//****************************************************************************
// Copyright (C) 2001-2010  PEAK System-Technik GmbH
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
// $Id: pcan_pci.h 634 2010-09-26 20:44:05Z khitschler $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <src/pcan_main.h>

//****************************************************************************
// DEFINES
#ifdef PCIEC_SUPPORT
int  pcan_pci_init(void);
void pcan_pci_deinit(void);
#else
int  pcan_search_and_create_pci_devices(void);
#endif

void pcan_pci_clear_stored_interrupt(struct pcandev *dev);
void pcan_pci_enable_interrupt(struct pcandev *dev);
#endif // __PCAN_PCI_H__
