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
// Contributions: Philipp Baer (philipp.baer@informatik.uni-ulm.de)
//****************************************************************************

//****************************************************************************
//
// all parts of the isa hardware for pcan-isa devices
//
// $Id: pcan_isa.c 753 2014-01-21 10:45:03Z stephane $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <src/pcan_common.h>     // must always be the 1st include
#include <linux/errno.h>
#include <linux/ioport.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <src/pcan_isa.h>
#include <src/pcan_sja1000.h>
#include <src/pcan_filter.h>

//****************************************************************************
// DEFINES
#define PCAN_ISA_MINOR_BASE 8    // starting point of minors for ISA devices  
#define ISA_PORT_SIZE       0x20 // the address range of the isa-port, enough for PeliCAN mode
#define ISA_DEFAULT_COUNT   2    // count of defaults for init

//****************************************************************************
// GLOBALS

//****************************************************************************
// LOCALS
static u16 isa_ports[] = {0x300, 0x320};  // default values for pcan-isa
static u8  isa_irqs[]  = {10, 5};
static u16 isa_devices = 0;        // the number of accepted isa_devices

//****************************************************************************
// CODE
#ifdef NO_RT
  #include "pcan_isa_linux.c"
#else
  #include "pcan_isa_rt.c"
#endif

static u8 pcan_isa_readreg(struct pcandev *dev, u8 port) // read a register
{
  return inb(dev->port.isa.dwPort + port);
}

static void pcan_isa_writereg(struct pcandev *dev, u8 port, u8 data) // write a register
{
  outb(data, dev->port.isa.dwPort + port);
}

// release and probe function
static int pcan_isa_cleanup(struct pcandev *dev)
{
  DPRINTK(KERN_DEBUG "%s: pcan_isa_cleanup()\n", DEVICE_NAME);

  switch(dev->wInitStep)
  {
    case 4: pcan_isa_free_irq(dev);
    case 3: isa_devices--;
    case 2:
    case 1: release_region(dev->port.isa.dwPort, ISA_PORT_SIZE);
    case 0: pcan_delete_filter_chain(dev->filter);
            dev->filter = NULL;
            dev->wInitStep = 0;
  }
  
  return 0;
}

// interface depended open and close
static int pcan_isa_open(struct pcandev *dev)
{
  return 0;
}

static int pcan_isa_release(struct pcandev *dev)
{
  return 0;
}

static int  pcan_isa_init(struct pcandev *dev, u32 dwPort, u16 wIrq)
{
  int err = 0;
  
  DPRINTK(KERN_DEBUG "%s: pcan_isa_init(), isa_devices = %d\n", DEVICE_NAME, isa_devices);

  // init process wait queues
  init_waitqueue_head(&dev->read_queue);
  init_waitqueue_head(&dev->write_queue);
  
  // set this before any instructions, fill struct pcandev, part 1  
  dev->wInitStep   = 0;           
  dev->readreg     = pcan_isa_readreg;
  dev->writereg    = pcan_isa_writereg;
  dev->cleanup     = pcan_isa_cleanup;
  dev->req_irq     = pcan_isa_req_irq;
  dev->free_irq    = pcan_isa_free_irq;
  dev->open        = pcan_isa_open;
  dev->release     = pcan_isa_release;
  dev->filter      = pcan_create_filter_chain();
  
  // reject illegal combination
  if ((!dwPort && wIrq) || (dwPort && !wIrq))
    return -EINVAL;

  // a default is requested
  if (!dwPort)
  {
    // there's no default available
    if (isa_devices >= ISA_DEFAULT_COUNT)
      return -ENODEV;
    
    dev->port.isa.dwPort = isa_ports[isa_devices];
    dev->port.isa.wIrq   = isa_irqs[isa_devices];    
  }
  else
  {
    dev->port.isa.dwPort = dwPort;
    dev->port.isa.wIrq   = wIrq;    
  } 
   
  dev->nMajor      = pcan_drv.nMajor;
  dev->nMinor      = PCAN_ISA_MINOR_BASE + isa_devices;
   
  // request address range reservation
  err = ___request_region(dev->port.isa.dwPort, ISA_PORT_SIZE, DEVICE_NAME);
  if (err)
    return err;

  dev->wInitStep = 1;
  
  dev->wInitStep = 2; 
  
  INIT_SAME_IRQ_LIST();
  
  isa_devices++; 
  dev->wInitStep = 3;
  
  printk(KERN_INFO "%s: isa device minor %d expected (io=0x%04x,irq=%d)\n", DEVICE_NAME, dev->nMinor, dev->port.isa.dwPort, dev->port.isa.wIrq);
    
  return 0;
}
 
//----------------------------------------------------------------------------
// create all declared isa devices
int pcan_create_isa_devices(char* type, u32 io, u16 irq)
{
  int    result = 0;
  struct pcandev *dev = NULL;

  // create isa devices
  DPRINTK(KERN_DEBUG "%s: pcan_create_isa_devices(0x%x, %d)\n", DEVICE_NAME, io, irq);
  
  if ((dev = (struct pcandev *)kmalloc(sizeof(struct pcandev), GFP_KERNEL)) == NULL)
  {
    result = -ENOMEM;
    goto fail;
  }

  pcan_soft_init(dev, type, HW_ISA_SJA);
  
  dev->device_open    = sja1000_open;
  dev->device_write   = sja1000_write;
  dev->device_release = sja1000_release;

  result = pcan_isa_init(dev, io, irq);
  if (!result)
    result = sja1000_probe(dev);

  if (result)
  {
    dev->cleanup(dev);
    kfree(dev);
    goto fail;
  }
  else
  {
    dev->ucPhysicallyInstalled = 1;

	/* add this device to the list */
	pcan_add_device_in_list(dev);
  }        
  
  fail:
  if (result)
    DPRINTK(KERN_DEBUG "%s: pcan_create_isa_devices() failed!\n", DEVICE_NAME);
  else
    DPRINTK(KERN_DEBUG "%s: pcan_create_isa_devices() is OK\n", DEVICE_NAME);

  return result;
}
