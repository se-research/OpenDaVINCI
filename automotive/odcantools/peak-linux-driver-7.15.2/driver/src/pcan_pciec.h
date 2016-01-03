#ifndef __PCAN_PCIEC_H__
#define __PCAN_PCIEC_H__

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
//****************************************************************************

//****************************************************************************
//
// all parts to handle device interface specific for PCAN-PCIExpressCard
//
// $Id: pcan_pciec.h 635 2010-09-26 20:47:38Z khitschler $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <src/pcan_main.h>

//****************************************************************************
// PROTOTYPES
PCAN_PCIEC_CARD *pcan_pciec_create_card(struct pci_dev *pciDev, struct pcandev *dev);
PCAN_PCIEC_CARD *pcan_pciec_locate_card(struct pci_dev *pciDev, struct pcandev *dev);
void             pcan_pciec_delete_card(struct pcandev *dev);

void pcan_setVCCEN(PCAN_PCIEC_CARD *card, int On);

#endif // __PCAN_PCIEC_H__

