//****************************************************************************
// Copyright (C) 2007-2009  PEAK System-Technik GmbH
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
// pcan_filter.c - all about CAN message filtering
//
// $Id: pcan_filter.c 819 2015-01-28 16:16:46Z stephane $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <src/pcan_common.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/spinlock.h>
#include <linux/slab.h>

#include <src/pcan_filter.h>
#include <src/can.h>          // pcan_add_filter uses netdev's can_id as input
#include <pcan.h>

//****************************************************************************
// DEFINES
#define PCAN_MAX_FILTER_PER_CHAIN 8  // take care since it is user allocated

typedef struct filter_element {
	struct list_head list;   // anchor for a linked list of filter_elements
	u32 FromID;              // all messages lower than FromID are rejected
	u32 ToID;                // all messages higher than ToID are rejected
	u8  MSGTYPE;             // MSGTYPE_STANDARD excludes MSGTYPE_EXTENDED
				                   // MSGTYPE_RTR excludes all non RTR messages
} filter_element;

typedef struct filter_chain {
	struct list_head anchor; // anchor for a linked list of filter_elements
	int    count;            // counts the number of filters in this chain
	spinlock_t lock;         // mutual exclusion lock for this filter chain
} filter_chain;

//****************************************************************************
// GLOBALS

//****************************************************************************
// LOCALS

//****************************************************************************
// CODE

// create the base for a list of filters - returns a handle
void *pcan_create_filter_chain(void)
{
	struct filter_chain *chain = NULL;

	DPRINTK(KERN_DEBUG "%s: pcan_create_filter_chain()\n", DEVICE_NAME);

	// alloc a new filter_element
	chain = (struct filter_chain *)kmalloc(sizeof(struct filter_chain),
						GFP_KERNEL);
	if (!chain)
		printk(KERN_ERR "%s: Cant't create filter chain!\n",
		       DEVICE_NAME);
	else {
		INIT_LIST_HEAD(&chain->anchor);
		chain->count = -1;       // initial no blocking of messages to provide compatibilty
		INIT_LOCK(&chain->lock);
	}

	return (void *)chain;
}

// add a filter element to the filter chain pointed by handle
// return 0 if it is OK, else return error
int pcan_add_filter(void *handle, u32 FromID, u32 ToID, u8 ucMSGTYPE)
{
	struct filter_chain   *chain = (struct filter_chain *)handle;
	struct filter_element *pfilter;
	struct list_head      *ptr, *tmp;

	DPRINTK(KERN_DEBUG
		"%s: pcan_add_filter(0x%p, 0x%08x, 0x%08x, 0x%02x)\n",
		DEVICE_NAME, handle, FromID, ToID, ucMSGTYPE);

	// if chain isn't set ignore it
	if (chain) {
		DECLARE_SPIN_LOCK_IRQSAVE_FLAGS;   // used by spin_lock_irqsave(..);

		// test for doubly set entries
		list_for_each_safe(ptr, tmp, &chain->anchor) {
			pfilter = list_entry(ptr, struct filter_element, list);
			if ((pfilter->FromID == FromID) &&
			    (pfilter->ToID == ToID) &&
			    (pfilter->MSGTYPE == ucMSGTYPE))
				return 0;
		}

		// limit count of filters since filters are user allocated
		if (chain->count >= PCAN_MAX_FILTER_PER_CHAIN)
			return -ENOMEM;

		// alloc a new filter_element
		pfilter = (struct filter_element *)kmalloc(sizeof(struct filter_element), GFP_KERNEL);
		if (!pfilter) {
			printk(KERN_ERR "%s: Cant't create filter element!\n",
			       DEVICE_NAME);
			return -ENOMEM;
		}

		// init filter element
		pfilter->FromID  = FromID;
		pfilter->ToID    = ToID;
		pfilter->MSGTYPE = ucMSGTYPE;

		// add this entry to chain
		SPIN_LOCK_IRQSAVE(&chain->lock);
		list_add_tail(&pfilter->list, &chain->anchor);
		if (chain->count < 0) // get first start for compatibility mode
			chain->count = 1;
		else
			chain->count++;
		SPIN_UNLOCK_IRQRESTORE(&chain->lock);
	}

	return 0;
}

// delete all filter elements in the filter chain pointed by handle
void pcan_delete_filter_all(void *handle)
{
	struct filter_chain   *chain = (struct filter_chain *)handle;
	struct filter_element *pfilter;
	struct list_head      *ptr, *tmp;

	DPRINTK(KERN_DEBUG "%s: pcan_delete_filter_all(0x%p)\n",
		DEVICE_NAME, handle);

	if (chain) {
		DECLARE_SPIN_LOCK_IRQSAVE_FLAGS;   // used by spin_lock_irqsave(..);

		SPIN_LOCK_IRQSAVE(&chain->lock);
		list_for_each_safe(ptr, tmp, &chain->anchor) {
			pfilter = list_entry(ptr, struct filter_element, list);
			list_del(ptr);
			kfree(pfilter);
		}
		chain->count = 0;
		SPIN_UNLOCK_IRQRESTORE(&chain->lock);
	}
}

// do the filtering with all filter elements pointed by handle
// returns 0 when the message should be passed
int pcan_do_filter(void *handle, u32 can_id)
{
	struct filter_chain   *chain = (struct filter_chain *)handle;
	struct filter_element *pfilter;
	struct list_head      *ptr, *tmp;

	// DPRINTK(KERN_DEBUG "%s: pcan_filter(0x%p, 0x%08x)\n", DEVICE_NAME, handle, can_id);

	// pass always when no filter reset has been done before
	if ((!chain) || (chain->count <= 0))
		return 0;

	// status is always passed
	// TODO: is this conform to MS-Windows driver behaviour?
	if (can_id & CAN_ERR_FLAG)
		return 0;

	{
		int throw;
		u32 rtr_message = can_id & CAN_RTR_FLAG;
		u32 ext_message = can_id & CAN_EFF_FLAG;

		if (ext_message)
			can_id &= CAN_EFF_MASK;
		else
			can_id &= CAN_SFF_MASK;

		list_for_each_safe(ptr, tmp, &chain->anchor) {
			pfilter = list_entry(ptr, struct filter_element, list);

#define RTR_FILTER (pfilter->MSGTYPE & MSGTYPE_RTR     )
#define EXT_FILTER (pfilter->MSGTYPE & MSGTYPE_EXTENDED)
#define RTR_IN     (rtr_message)
#define EXT_IN     (ext_message)
			// truth table for throw
			//
			//             RTR_FILTER | /RTR_FILTER
			//            ------------|------------
			//  EXT_FILTER|  1  |  0  |  0  |  0  |/EXT_IN
			//            |-----------|--------------
			//            |  1  |  0  |  0  |  0  |
			//         ---------------------------| EXT_IN
			//            |  1  |  1  |  1  |  1  |
			//            |-----------|--------------
			// /EXT_FILTER|  1  |  0  |  0  |  0  |/EXT_IN
			//            |-----|-----------|------
			//           /RTR_IN|  RTR_IN   |/RTR_IN
			//
			throw = ((RTR_FILTER && !RTR_IN) || (!EXT_FILTER && EXT_IN));

			if ((!throw) && (can_id >= pfilter->FromID) && 
					(can_id <= pfilter->ToID))
				return 0;
		}
	}

	// no pass criteria was found
	return 1;
}

// remove the whole filter chain (and potential filter elements) pointed b handle
void pcan_delete_filter_chain(void *handle)
{
	struct filter_chain *chain = (struct filter_chain *)handle;

	DPRINTK(KERN_DEBUG "%s: pcan_delete_filter_chain(0x%p)\n",
		DEVICE_NAME, handle);

	pcan_delete_filter_all(handle);

	if (chain)
		kfree(chain);
}
