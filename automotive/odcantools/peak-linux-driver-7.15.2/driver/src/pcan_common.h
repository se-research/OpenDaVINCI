#ifndef __PCAN_COMMON_H__
#define __PCAN_COMMON_H__

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
// global defines to include in all files this module is made of
// ! this must always the 1st include in all files !
//
// $Id: pcan_common.h 904 2015-07-29 07:44:53Z stephan $
//
//****************************************************************************

//****************************************************************************
// DEFINES
#ifndef __KERNEL__
  #define __KERNEL__
#endif
#ifndef MODULE
  #define MODULE
#endif

#include <linux/version.h>  // if this file is not found: please look @ /boot/vmlinuz.version.h and make a symlink

#include <linux/module.h>
#include <linux/stringify.h>

// support for MODVERSIONS
#ifndef AUTOCONF_INCLUDED
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,38)
#include <generated/autoconf.h>
#else
#include <linux/autoconf.h>
#endif
#define AUTOCONF_INCLUDED
#endif

#if defined(CONFIG_MODVERSIONS) && !defined(MODVERSIONS)
  #define MODVERSIONS
#endif

#ifdef MODVERSIONS
  #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
    #if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,10)
      #include <config/modversions.h>
  #endif
  #else
    #include <linux/modversions.h>
  #endif
#endif

#ifndef NO_RT
  #include <rtdm/rtdm_driver.h>
  #include <asm/div64.h>
  #if RTDM_API_VER < 5
    typedef nanosecs_abs_t uint64_t;
  #endif

  static inline void rt_gettimeofday(struct timeval *tv)
  {
      nanosecs_abs_t current_time = rtdm_clock_read();
      tv->tv_usec = (do_div(current_time, 1000000000) / 1000);
      tv->tv_sec = current_time;

  }
  #define DO_GETTIMEOFDAY(tv) rt_gettimeofday(&tv)
#else
  #define DO_GETTIMEOFDAY(tv) do_gettimeofday(&tv)
#endif

// support for PARPORT_SUBSYSTEM
#if !defined(CONFIG_PARPORT_MODULE) && !defined(CONFIG_PARPORT) && defined(PARPORT_SUBSYSTEM)
  #undef PARPORT_SUBSYSTEM
#endif

// support for USB
#if !defined(CONFIG_USB_MODULE) && !defined(CONFIG_USB) && defined(USB_SUPPORT)
  #undef USB_SUPPORT
#endif

// support for PCCARD
#if !defined(CONFIG_PCMCIA_MODULE) && !defined(CONFIG_PCMCIA) && !defined(CONFIG_PCCARD) && defined(PCCARD_SUPPORT)
  #undef PCCARD_SUPPORT
#endif

// support for PCIe (need I2C algo)
#if !defined(CONFIG_I2C_ALGOBIT) && !defined(CONFIG_I2C_ALGOBIT_MODULE)
#undef PCIEC_SUPPORT
#endif

// support only versions 2.4.x and 2.6.x
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0)
#error "This kernel is too old and not supported"
#else
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,5,0)
#define LINUX_24 // >= LINUX 2.4.x && < LINUX 2.6
#else
#define LINUX_26 // >= LINUX 2.6
#endif
#endif

// some preparative definitions for kernel 2.6.x
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,23)
typedef void irqreturn_t;
#define IRQ_NONE
#define IRQ_HANDLED
#define IRQ_RETVAL(x)
#endif

// IRQ's return val for Linux and RealTime
#ifndef NO_RT
#define PCAN_IRQ_RETVAL(x) x

#define INIT_LOCK(lock)
#define DECLARE_SPIN_LOCK_IRQSAVE_FLAGS
#define SPIN_LOCK_IRQSAVE(lock)
#define SPIN_UNLOCK_IRQRESTORE(lock)
#else
#define PCAN_IRQ_RETVAL(x) IRQ_RETVAL(x)

#define INIT_LOCK(lock) spin_lock_init(lock)
#define DECLARE_SPIN_LOCK_IRQSAVE_FLAGS unsigned long flags
#define SPIN_LOCK_IRQSAVE(lock) spin_lock_irqsave(lock, flags)
#define SPIN_UNLOCK_IRQRESTORE(lock) spin_unlock_irqrestore(lock, flags)
#endif

// count of function variables changed from 2.6.19
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,19)
#define IRQHANDLER(name, p1, p2, p3)	name(p1, p2, p3)
#else
#define IRQHANDLER(name, p1, p2, p3)	name(p1, p2)
#endif

// switch to disable all printks for not debugging
#ifdef DEBUG
#define DPRINTK				printk
#else
#define DPRINTK(stuff...)
#endif

// to manage differences between kernel versions
int ___request_region(unsigned long from, unsigned long length,
		      const char *name);

// to get smoothly into udev
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,17)
#define UDEV_SUPPORT
#endif

// follow current interrupt definition changes
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18)
#define IRQF_DISABLED			SA_INTERRUPT
#define IRQF_SHARED			SA_SHIRQ
#endif

/* different data sink alternatives */
#ifdef NETDEV_SUPPORT
#define pcan_xxxdev_rx(d, f, t)		pcan_netdev_rx(d, f, t)
#define pcan_xxxdev_rx_ex(d, f, t, x)	pcan_netdev_rx(d, f, t)
#else
#define pcan_xxxdev_rx(d, f, t)		pcan_chardev_rx(d, f, t)
#define pcan_xxxdev_rx_ex(d, f, t, x)	pcan_chardev_rx_ex(d, f, t, x)
#endif

#define DEVICE_NAME      "pcan"	/* the name of the module and the proc entry */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
/*
 * This has been added in 2.6.24
 */
#define list_for_each_prev_safe(pos, n, head) \
   for (pos = (head)->prev, n = pos->prev; \
        prefetch(pos->prev), pos != (head); \
        pos = n, n = pos->prev)
#endif

//----------------------------------------------------------------------------
// set here the current release of the driver 'Release_date_nr' synchronous
// with SVN
#define CURRENT_RELEASE "Release_20150729_n"  // $name$
#define PCAN_VERSION_MAJOR             7
#define PCAN_VERSION_MINOR             15
#define PCAN_VERSION_SUBMINOR          2
#define CURRENT_VERSIONSTRING          __stringify(PCAN_VERSION_MAJOR)"."__stringify(PCAN_VERSION_MINOR)"."__stringify(PCAN_VERSION_SUBMINOR)


#endif // __PCAN_COMMON_H__
