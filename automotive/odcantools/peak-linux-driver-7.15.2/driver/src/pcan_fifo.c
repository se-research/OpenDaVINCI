//****************************************************************************
// Copyright (C) 2001-2009  PEAK System-Technik GmbH
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
// Contributions: John Privitera  (JohnPrivitera@dciautomation.com)
//****************************************************************************

//****************************************************************************
//
// pcan_fifo.c - manages the ring buffers for read and write data
//
// $Id: pcan_fifo.c 807 2014-12-09 15:34:11Z stephane $
//
//****************************************************************************
#define PCAN_FIFO_FIX_NOT_FULL_TEST

//****************************************************************************
// INCLUDES
#include <src/pcan_common.h>
#include <linux/types.h>
#include <linux/errno.h>    // error codes
#include <linux/string.h>   // memcpy
#include <linux/sched.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 4, 0)
#include <asm/system.h>     // cli(), save_flags(), restore_flags()
#endif
#include <linux/spinlock.h>

#include <src/pcan_fifo.h>

//****************************************************************************
// DEFINES

//****************************************************************************
// GLOBALS

//****************************************************************************
// LOCALS

//****************************************************************************
// CODE
int pcan_fifo_reset(register FIFO_MANAGER *anchor)
{
	DECLARE_SPIN_LOCK_IRQSAVE_FLAGS;

	SPIN_LOCK_IRQSAVE(&anchor->lock);

	anchor->dwTotal = 0;
	anchor->nStored = 0;
	anchor->r = anchor->w = anchor->bufferBegin; // nothing to read

	SPIN_UNLOCK_IRQRESTORE(&anchor->lock);

	// DPRINTK(KERN_DEBUG "%s: pcan_fifo_reset() %d %p %pd\n", DEVICE_NAME, anchor->nStored, anchor->r, anchor->w);

	return 0;
}

int pcan_fifo_init(register FIFO_MANAGER *anchor, void *bufferBegin,
		   void *bufferEnd, int nCount, u16 wCopySize)
{
	anchor->wCopySize = wCopySize;
	anchor->wStepSize = (bufferBegin == bufferEnd) ? 0 : ((bufferEnd - bufferBegin) / (nCount - 1));
	anchor->nCount  = nCount;
	anchor->bufferBegin = bufferBegin;
	anchor->bufferEnd = bufferEnd;

	// check for fatal program errors
	if ((anchor->wStepSize < anchor->wCopySize) ||
		(anchor->bufferBegin > anchor->bufferEnd) || (nCount <= 1))
		return -EINVAL;

	INIT_LOCK(&anchor->lock);

	return pcan_fifo_reset(anchor);
}

int pcan_fifo_put(register FIFO_MANAGER *anchor, void *pvPutData)
{
	int err = 0;
	DECLARE_SPIN_LOCK_IRQSAVE_FLAGS;

	// DPRINTK(KERN_DEBUG "%s: pcan_fifo_put() %d %p %p\n", DEVICE_NAME, anchor->nStored, anchor->r, anchor->w);

	SPIN_LOCK_IRQSAVE(&anchor->lock);

	if (anchor->nStored < anchor->nCount) {
		memcpy(anchor->w, pvPutData, anchor->wCopySize);

		anchor->nStored++;
		anchor->dwTotal++;

		if (anchor->w < anchor->bufferEnd)
			anchor->w += anchor->wStepSize;   // increment to next
		else
			anchor->w = anchor->bufferBegin;  // start from begin
	} else
		err = -ENOSPC;

	SPIN_UNLOCK_IRQRESTORE(&anchor->lock);

	return err;
}

int pcan_fifo_get(register FIFO_MANAGER *anchor, void *pvGetData)
{
	int err = 0;
	DECLARE_SPIN_LOCK_IRQSAVE_FLAGS;

	// DPRINTK(KERN_DEBUG "%s: %s() %d %p %p\n", DEVICE_NAME, __func__, anchor->nStored, anchor->r, anchor->w);

	SPIN_LOCK_IRQSAVE(&anchor->lock);

	if (anchor->nStored > 0) {
		if (pvGetData)
			memcpy(pvGetData, anchor->r, anchor->wCopySize);

		anchor->nStored--;
		if (anchor->r < anchor->bufferEnd)
			anchor->r += anchor->wStepSize;  // increment to next
		else
			anchor->r = anchor->bufferBegin; // start from begin
	} else
		err = -ENODATA;

	SPIN_UNLOCK_IRQRESTORE(&anchor->lock);

	return err;
}

int pcan_fifo_peek(register FIFO_MANAGER *anchor, void *pvGetData)
{
	// DPRINTK(KERN_DEBUG "%s: %s()) %d %p %p\n", DEVICE_NAME, __func__, anchor->nStored, anchor->r, anchor->w);

	if (anchor->nStored > 0) {
		memcpy(pvGetData, anchor->r, anchor->wCopySize);
		return 0;
	}

	return -ENODATA;
}

//----------------------------------------------------------------------------
// returns the current count of elements in fifo
int pcan_fifo_status(FIFO_MANAGER *anchor)
{
	return anchor->nStored;
}

//----------------------------------------------------------------------------
// returns 0 if the fifo is full
int pcan_fifo_not_full(FIFO_MANAGER *anchor)
{
#ifdef PCAN_FIFO_FIX_NOT_FULL_TEST
	int r;
	DECLARE_SPIN_LOCK_IRQSAVE_FLAGS;

	SPIN_LOCK_IRQSAVE(&anchor->lock);
	r = (anchor->nStored < anchor->nCount);
	SPIN_UNLOCK_IRQRESTORE(&anchor->lock);

	return r;
#else
	return (anchor->nStored < (anchor->nCount - 1));
#endif
}

//----------------------------------------------------------------------------
// returns !=0 if the fifo is empty
int pcan_fifo_empty(FIFO_MANAGER *anchor)
{
	return !(anchor->nStored);
}
