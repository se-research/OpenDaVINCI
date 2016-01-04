//****************************************************************************
// Copyright (C) 2006-2009  PEAK System-Technik GmbH
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

//***************************************************************************
//
// system dependend parts to handle pcan-pccard
//
// $Id: pcan_pccard.c 753 2014-01-21 10:45:03Z stephane $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <src/pcan_common.h>     // must always be the 1st include

/* SGr on 19-07-2011: PCCARD_SUPPORT may be undefined in pcan_common.h if */
/* kernel support not configured, even if PCCARD_SUPPORT is defined on command*/
/* line. */
#ifdef PCCARD_SUPPORT

#include <linux/slab.h>
#include <linux/string.h>
#include <linux/ioport.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,37)
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
#include <pcmcia/cs_types.h>
#endif
#include <pcmcia/cs.h>
#endif
#include <pcmcia/cistpl.h>
#include <pcmcia/ds.h>
#include <pcmcia/cisreg.h>
#include <pcmcia/ciscode.h>

#include <src/pcan_pccard_kernel.h>

//****************************************************************************
// DEFINES
#define PCCARD_MANF_ID     0x0377           // manufacturer PEAK System GmbH
#define PCCARD_CARD_ID     0x0001           // card id

//****************************************************************************
// helper macros
#define CS_CHECK(fn, ret) do { last_fn = (fn); if ((last_ret = (ret)) != 0) goto cs_failed; } while (0)

#define CS_PREPARE(tpl) { tuple.DesiredTuple = tpl;  tuple.TupleData = buf; tuple.TupleOffset = 0; \
                          tuple.TupleDataMax = CISTPL_END; tuple.Attributes   = 0; }


//****************************************************************************
// CODE
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,13)
static struct pcmcia_device_id pccard_id_table[] =
{
  PCMCIA_DEVICE_MANF_CARD(PCCARD_MANF_ID, PCCARD_CARD_ID),
  PCMCIA_DEVICE_NULL,
};

MODULE_DEVICE_TABLE(pcmcia, pccard_id_table);
#endif

//****************************************************************************
// unfortunately to get readable code all the code was put into 2 files
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,17)
#include "src/pcan_pccard-2.6.17.c"
#else
#include "src/pcan_pccard-2.6.16.c"
#endif

//****************************************************************************
// fill struct pcmcia_driver and register it
static int pccard_init(void)
{
  DPRINTK(KERN_DEBUG "%s: pccard_init()\n", DEVICE_NAME);

#ifdef LINUX_24
  register_pccard_driver(&pccard_info, &pccard_attach, &pccard_detach);
  return 0;
#else

  memset (&pcan_drv.pccarddrv, 0, sizeof(pcan_drv.pccarddrv));

  pcan_drv.pccarddrv.owner      = THIS_MODULE;
  pcan_drv.pccarddrv.drv.name   = DEVICE_NAME;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,13)
  pcan_drv.pccarddrv.attach     = pccard_attach;
  pcan_drv.pccarddrv.detach     = pccard_detach;
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,13) && LINUX_VERSION_CODE < KERNEL_VERSION(2,6,16)
  pcan_drv.pccarddrv.id_table   = pccard_id_table;
  pcan_drv.pccarddrv.event      = pccard_event;
  pcan_drv.pccarddrv.attach     = pccard_attach;
  pcan_drv.pccarddrv.detach     = pccard_detach;
  #endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,16)
  pcan_drv.pccarddrv.id_table   = pccard_id_table;
  pcan_drv.pccarddrv.probe      = pccard_probe;
  pcan_drv.pccarddrv.remove     = pccard_detach;
  pcan_drv.pccarddrv.suspend    = pccard_suspend;
  pcan_drv.pccarddrv.resume     = pccard_resume;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37)
  /* this version sets pccarddrv->drv.name with pccarddrv.name => */
  /* it must be a valid pointer too */
  pcan_drv.pccarddrv.name       = DEVICE_NAME;
#endif
#endif

  return pcmcia_register_driver(&pcan_drv.pccarddrv);
#endif
}

//****************************************************************************
// small interface to rest of driver, only register and deinit
void pcan_pccard_deinit(void)
{
  DPRINTK(KERN_DEBUG "%s: pcan_pccard_deinit()\n", DEVICE_NAME);

  #if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,16)
  pcan_unlink_pccard();
  #endif

	#ifdef LINUX_24
  unregister_pccard_driver(&pccard_info);
	#else
  if (pcan_drv.pccarddrv.drv.name)
  {
    // then it was registered
    // unregister pccard parts, makes a plugout of registered devices
    pcmcia_unregister_driver(&pcan_drv.pccarddrv);
  }
	#endif
}

int  pcan_pccard_register_devices(void)
{
  int ret;

  DPRINTK(KERN_DEBUG "%s: pcan_pccard_register_devices()\n", DEVICE_NAME);

  if (!(ret = pccard_init()))
  {
    DPRINTK(KERN_DEBUG "%s: pcan_pccard_register_devices() is OK\n", DEVICE_NAME);
  }

  return ret;
}
// finish
#endif /* PCCARD_SUPPORT */
