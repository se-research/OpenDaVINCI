//****************************************************************************
// Copyright (C) 2003-2010  PEAK System-Technik GmbH
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
// Maintainer(s): Stephane Grosjean (s.grosjean@peak-system.com)
//
// Major contributions by:
//                Klaus Hitschler (klaus.hitschler@gmx.de)
//                Oliver Hartkopp (oliver.hartkopp@volkswagen.de) socketCAN
//
//****************************************************************************

//****************************************************************************
//
// pcan_usb.c - the inner parts for pcan-usb support
//
// $Id: pcan_usb.c 845 2015-05-21 08:39:03Z stephane $
//
// 2011-08-22 SGr
// - pcan_usb_cleanup(NEW): add the sending of the bus off request in cleanup
//   callback since this is the last place we may submit urb to the device
//   before driver removal.
//
//****************************************************************************
//#define DEBUG
//#undef DEBUG

//****************************************************************************
// INCLUDES
#include <src/pcan_common.h>
#include <linux/sched.h>
#include <linux/net.h>
#include <src/pcan_main.h>
#include <src/pcan_fifo.h>
#include <src/pcan_usb.h>
#include <asm/byteorder.h>       // because of little / big endian

#ifdef NETDEV_SUPPORT
#include <src/pcan_netdev.h>     // for hotplug pcan_netdev_register()
#endif

//****************************************************************************
// DEFINES
/*
 * if defined, takes into account that DLC field may be > 8.
 * in any case, DLC > 8 means DLC = 8. It also means that applications HAVE TO
 * handle the fact that C struct object lenght field MAY be greater than 8 !!!
 * Should be defined, since PCAN-USB is able to generate such values !
 */
#define HANDLE_DLC_GT_THAN_8

// bit masks for status/length field in a USB message
#define STLN_WITH_TIMESTAMP 0x80
#define STLN_INTERNAL_DATA  0x40
#define STLN_EXTENDED_ID    0x20
#define STLN_RTR            0x10
#define STLN_DATA_LENGTH    0x0F         // mask for length of data bytes

// Error-Flags for PCAN-USB
#define XMT_BUFFER_FULL           0x01
#define CAN_RECEIVE_QUEUE_OVERRUN 0x02
#define BUS_LIGHT                 0x04
#define BUS_HEAVY                 0x08
#define BUS_OFF                   0x10
#define QUEUE_RECEIVE_EMPTY       0x20
#define QUEUE_OVERRUN             0x40
#define QUEUE_XMT_FULL            0x80

/* timestamp calculation stuff:
 * converting ticks into us is done by scaling the number of ticks per us:
 * as one tick duration is 42.666 us, use 42666 us for 1000 ticks.
 * two methods are porposed here:
 * 1. fast: instead of div, use 2^20 shift method:
 *    (tick_number * 44739) >> 20 <~> (tick_number * 42666) / 1000000
 *    this gives same result with a 10^-7 precision
 * 2. accurate: use the 64-bits division
 *    (tick_number * 1024) / 24000
 */
//#define PCAN_USB_TS_DIV_SHIFTER          20  // shift faster than div
#ifdef PCAN_USB_TS_DIV_SHIFTER
//#define PCAN_USB_TS_US_PER_TICK       44739  // error = 5,424e-4%
#define PCAN_USB_TS_US_PER_TICK      44739243
#else
// use MULTIPLIER/DIVISOR to convert ticks into us.
//#define PCAN_USB_TS_SCALE_MULTIPLIER   1024  // multiplier for ts calculation
//#define PCAN_USB_TS_SCALE_DIVISOR     24000  // divisor for ts calc (ms)

/* values above give results in ms. ... why? */
/* using values below gives result in us. */
#define PCAN_USB_TS_SCALE_MULTIPLIER    128  // multiplier for direct calc of ts
#define PCAN_USB_TS_SCALE_DIVISOR         3  // divisor for ts calc (ms)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,8)
#define TICKS(msec) ((msec * HZ) / 1000)     // to calculate ticks from milliseconds
#endif

#define COMMAND_TIMEOUT                1000  // ms timeout for EP0 control urbs

/* older kernels don't define it */
#ifndef pr_err
#define pr_err(fmt, ...) \
	printk(KERN_ERR pr_fmt(fmt), ##__VA_ARGS__)
#endif

// pcan-usb parameter get an set function
typedef struct
{
	u8  Function;
	u8  Number;
	u8  Param[14];
} __attribute__ ((packed)) PCAN_USB_PARAM;

//****************************************************************************
// GLOBALS
extern int pcan_kill_sync_urb(struct urb *urb);

//****************************************************************************
// LOCALS

//****************************************************************************
// CODE

//****************************************************************************
// functions to handle time construction
static void pcan_reset_timestamp(struct pcandev *dev)
{
	PCAN_USB_TIME *t = &dev->port.usb.usb_time;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	// reset time stamp information
	memset(t, '\0', sizeof(PCAN_USB_TIME));
}

// take the timestamp from ticks * (42 + 2/3) usecs of PCAN-USB
static void pcan_calcTimevalFromTicks(struct pcandev *dev, struct timeval *tv)
{
	register PCAN_USB_TIME *t = &dev->port.usb.usb_time;
	u64 llx;
	uint32_t nb_s, nb_us;

	llx = t->ullCumulatedTicks - t->wStartTicks;    // subtract initial offset

#ifdef PCAN_USB_TS_DIV_SHIFTER
	llx *= PCAN_USB_TS_US_PER_TICK;
	// unscale, shift runs faster than divide
	llx >>= PCAN_USB_TS_DIV_SHIFTER;
#else
	llx *= PCAN_USB_TS_SCALE_MULTIPLIER;

#ifndef CONFIG_64BITS
	do_div(llx, PCAN_USB_TS_SCALE_DIVISOR);
#else
	llx /= PCAN_USB_TS_SCALE_DIVISOR;
#endif
#endif

	/* now, llx contains the number of us. that corresponds to the number of */
	/* ticks added since t->StartTime */
	/* => add that number of us. to StartTime: */
#ifndef CONFIG_64BITS
	nb_us = do_div(llx, 1000000);
	nb_s = (uint32_t )llx;
#else
	nb_s = llx / 1000000;
	nb_us = llx - (nb_s * 1000000);
#endif
	
	tv->tv_usec = t->StartTime.tv_usec + nb_us;
	if (tv->tv_usec > 1000000)
	{
		tv->tv_usec -= 1000000;
		nb_s++;
	}
	
	tv->tv_sec = t->StartTime.tv_sec + nb_s;

#if 0
	DPRINTK(KERN_DEBUG "%s: %s(): tv_sec=%us.%uus.\n", 
	        DEVICE_NAME, __FUNCTION__, 
	        (uint32_t )tv->tv_sec, (uint32_t )tv->tv_usec);
#endif
}

static void pcan_updateTimeStampFromWord(struct pcandev *dev, u16 wTimeStamp, u8 ucStep)
{
	register PCAN_USB_TIME *t = &dev->port.usb.usb_time;

#if 0
	DPRINTK(KERN_DEBUG "%s: %s() ts=%u prev=%u cum=%llu\n", 
	        DEVICE_NAME, __FUNCTION__,
	        wTimeStamp, t->wLastTickValue, t->ullCumulatedTicks);
#endif

	if ((!t->StartTime.tv_sec) && (!t->StartTime.tv_usec))
	{
#if 0
		/* get time (in struct timeval) relative to the moment the driver */
		/* starts */
		get_relative_time(NULL, &t->StartTime);
#else
		/* since get_relative_time() is done in pcan_chardev_rx(), use */
		/* DO_GETTIMEOFDAY() instead */
		DO_GETTIMEOFDAY(t->StartTime);
#endif
		t->wStartTicks          = wTimeStamp;
		t->wOldLastTickValue    = wTimeStamp;
		t->ullCumulatedTicks    = wTimeStamp;
		t->ullOldCumulatedTicks = wTimeStamp;
	}

	// correction for status timestamp in the same telegram which is more recent, restore old contents
	if (ucStep)
	{
		t->ullCumulatedTicks = t->ullOldCumulatedTicks;
		t->wLastTickValue    = t->wOldLastTickValue;
	}

	// store current values for old ...
	t->ullOldCumulatedTicks = t->ullCumulatedTicks;
	t->wOldLastTickValue    = t->wLastTickValue;

	if (wTimeStamp < t->wLastTickValue)  // handle wrap, enhance tolerance
		t->ullCumulatedTicks += 0x10000LL;

	t->ullCumulatedTicks &= ~0xFFFFLL;   // mask in new 16 bit value - do not cumulate cause of error propagation
	t->ullCumulatedTicks |= wTimeStamp;

	t->wLastTickValue   = wTimeStamp;      // store for wrap recognition
	t->ucLastTickValue  = (u8)(wTimeStamp & 0xff); // each update for 16 bit tick updates the 8 bit tick, too
}

static void pcan_updateTimeStampFromByte(struct pcandev *dev, u8 ucTimeStamp)
{
	register PCAN_USB_TIME *t = &dev->port.usb.usb_time;

#if 0
	DPRINTK(KERN_DEBUG "%s: %s() ts=%u prev=%u cum = %llu\n", 
	        DEVICE_NAME, __FUNCTION__, 
	        ucTimeStamp, t->ucLastTickValue, t->ullCumulatedTicks);
#endif

	if (ucTimeStamp < t->ucLastTickValue)  // handle wrap
	{
		t->ullCumulatedTicks += 0x100;
		t->wLastTickValue    += 0x100;
	}

	t->ullCumulatedTicks &= ~0xFFULL;      // mask in new 8 bit value - do not cumulate cause of error propagation
	t->ullCumulatedTicks |= ucTimeStamp;

	t->wLastTickValue    &= ~0xFF;         // correction for word timestamp, too
	t->wLastTickValue    |= ucTimeStamp;

	t->ucLastTickValue    = ucTimeStamp;   // store for wrap recognition
}

//****************************************************************************
// get and set parameters to or from device
//
#ifdef LINUX_26
static void pcan_usb_param_xmit_notify(struct urb *purb, struct pt_regs *regs)
#else
static void pcan_usb_param_xmit_notify(purb_t purb)
#endif
{
	//struct pcandev *dev = purb->context;
	//struct pcan_usb_interface *usb_if = dev->port.usb.usb_if;
	struct pcan_usb_interface *usb_if = purb->context;

	DPRINTK(KERN_DEBUG "%s: %s() = %d\n", 
	        DEVICE_NAME, __FUNCTION__, purb->status);

	// un-register outstanding urb
	atomic_dec(&usb_if->active_urbs);

	atomic_set(&usb_if->cmd_sync_complete, 1);
}

static int pcan_usb_setcontrol_urb(struct pcandev *dev, u8 function, u8 number,
                                   u8 param0, u8 param1, u8 param2, u8 param3,
                                   u8 param4, u8 param5, u8 param6, u8 param7, 
                                   u8 param8, u8 param9, u8 param10, u8 param11,
                                   u8 param12, u8 param13)
{
	struct pcan_usb_interface *usb_if = dev->port.usb.usb_if;
	PCAN_USB_PARAM myParameter;
	int nResult = 0;
	register purb_t pt;
	u32 startTime;

	DPRINTK(KERN_DEBUG "%s: %s(): ->EP#%02X\n", DEVICE_NAME, __FUNCTION__, 
	        usb_if->pipe_cmd_out.ucNumber);

	// don't do anything with non-existent hardware
	if (!dev->ucPhysicallyInstalled)
		return -ENODEV;

	myParameter.Function = function;
	myParameter.Number   = number;
	myParameter.Param[0]   = param0;
	myParameter.Param[1]   = param1;
	myParameter.Param[2]   = param2;
	myParameter.Param[3]   = param3;
	myParameter.Param[4]   = param4;
	myParameter.Param[5]   = param5;
	myParameter.Param[6]   = param6;
	myParameter.Param[7]   = param7;
	myParameter.Param[8]   = param8;
	myParameter.Param[9]   = param9;
	myParameter.Param[10]  = param10;
	myParameter.Param[11]  = param11;
	myParameter.Param[12]  = param12;
	myParameter.Param[13]  = param13;

	pt = &usb_if->urb_cmd_sync;

	FILL_BULK_URB(pt, usb_if->usb_dev,
	              usb_sndbulkpipe(usb_if->usb_dev,
	                              usb_if->pipe_cmd_out.ucNumber),
                 &myParameter, sizeof(myParameter), 
	              pcan_usb_param_xmit_notify, usb_if);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,8)
	pt->timeout = TICKS(COMMAND_TIMEOUT);
#endif

	if (__usb_submit_urb(pt))
	{
		DPRINTK(KERN_ERR "%s: %s() can't submit!\n",DEVICE_NAME, __FUNCTION__);
		nResult = pt->status;
		goto fail;
	}
	else
		atomic_inc(&usb_if->active_urbs);

	// wait until submit is finished, either normal or thru timeout
	startTime = get_mtime();
	while (!atomic_read(&usb_if->cmd_sync_complete)) {
		schedule();

		/* check if we're waiting too long for urb submission */
		if ((get_mtime() - startTime) >= COMMAND_TIMEOUT) {
			/*
			 * yes we are, so kill it: the urb status will contain
			 * the error
			 */
			usb_kill_urb(pt);
			break;
		}
	}

	// remove urb
	nResult = pt->status;
	if (nResult) 
		pr_err("%s: error %d submitting command\n", 
		       DEVICE_NAME, nResult);

fail:
	atomic_set(&usb_if->cmd_sync_complete, 0);

	return nResult;
}

static int pcan_set_function(struct pcandev *dev, u8 function, u8 number)
{
	DPRINTK(KERN_DEBUG "%s: %s(%d, %d)\n", DEVICE_NAME, __FUNCTION__, 
	        function, number);

	return pcan_usb_setcontrol_urb(dev, function, number, 
	                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

// in opposition to WIN method this performs the complete write and read cycle!
static int pcan_usb_getcontrol_urb(struct pcandev *dev, u8 function, u8 number,
                                 u8 *param0, u8 *param1, u8 *param2, u8 *param3,
                                 u8 *param4, u8 *param5, u8 *param6, u8 *param7)
{
	struct pcan_usb_interface *usb_if = dev->port.usb.usb_if;
	PCAN_USB_PARAM myParameter;
	int nResult = 0;
	register purb_t pt;

	DPRINTK(KERN_DEBUG "%s: %s(): <-EP#%02X\n", DEVICE_NAME, __FUNCTION__, 
	        usb_if->pipe_cmd_in.ucNumber);

	// don't do anything with non-existent hardware
	if (!dev->ucPhysicallyInstalled)
		return -ENODEV;

	// first write function and number to device
	nResult = pcan_set_function(dev, function, number);

#if 0
	// heuristic result - wait a little bit (not useful)
	mdelay(5);
#endif
	if (!nResult)
	{
		u32 startTime;

		pt = &usb_if->urb_cmd_sync;

		FILL_BULK_URB(pt, usb_if->usb_dev,
					      usb_rcvbulkpipe(usb_if->usb_dev, 
		                              usb_if->pipe_cmd_in.ucNumber),
					      &myParameter, sizeof(myParameter), 
		              pcan_usb_param_xmit_notify, usb_if);

		myParameter.Function = function;
		myParameter.Number   = number;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,8)
		pt->timeout = TICKS(COMMAND_TIMEOUT);
#endif

		if (__usb_submit_urb (pt))
		{
			printk(KERN_ERR "%s: pcan_get_parameter() can't submit!\n",DEVICE_NAME);
			nResult = pt->status;
			goto fail;
		}
		else
			atomic_inc(&usb_if->active_urbs);

		startTime = get_mtime();
		while (    !atomic_read(&usb_if->cmd_sync_complete) 
		        && ((get_mtime() - startTime) < COMMAND_TIMEOUT))
			schedule();

		if (!atomic_read(&usb_if->cmd_sync_complete))
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,10)
			usb_kill_urb(pt);
#else
			usb_unlink_urb(pt); /* any better solution here for Kernel 2.4 ? */
#endif

		if (!pt->status)
		{
			*param0 = myParameter.Param[0];
			*param1 = myParameter.Param[1];
			*param2 = myParameter.Param[2];
			*param3 = myParameter.Param[3];
			*param4 = myParameter.Param[4];
			*param5 = myParameter.Param[5];
			*param6 = myParameter.Param[6];
			*param7 = myParameter.Param[7];
		}

		nResult = pt->status;
	}

fail:
	atomic_set(&usb_if->cmd_sync_complete, 0);

	return nResult;
}

//****************************************************************************
// specialized high level hardware access functions
//
static int pcan_usb_setBTR0BTR1(struct pcandev *dev, u16 wBTR0BTR1)
{
	u8  dummy  = 0;
	u8  param0 = (u8)(wBTR0BTR1 & 0xff);
	u8  param1 = (u8)((wBTR0BTR1 >> 8) & 0xff);

	DPRINTK(KERN_DEBUG "%s: %s(0x%04x)\n", DEVICE_NAME, __FUNCTION__, wBTR0BTR1);

	return pcan_usb_setcontrol_urb(dev, 1, 2, param0, param1,
	                              dummy, dummy, dummy, dummy, dummy, dummy,
	                              dummy, dummy, dummy, dummy, dummy, dummy);
}

static int pcan_usb_setCANOn(struct pcandev *dev)
{
	u8  dummy  = 0;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	return pcan_usb_setcontrol_urb(dev, 3, 2, 1, dummy,
	                   dummy, dummy, dummy, dummy, dummy, dummy,
	                   dummy, dummy, dummy, dummy, dummy, dummy);
}

static int pcan_usb_setCANOff(struct pcandev *dev)
{
	int err;
	u8  dummy  = 0;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

#if 0
	/* wait a bit if we sent any outgoinf CAN frames */
	if (dev->dwInterruptCounter > 0)
		mdelay(10);
#endif
	err = pcan_usb_setcontrol_urb(dev, 3, 2, 0, dummy,
	                  dummy, dummy, dummy, dummy, dummy, dummy,
	                  dummy, dummy, dummy, dummy, dummy, dummy);

	/* or if (err != -ENODEV) { */
	if (dev->ucPhysicallyInstalled) {
		struct pcan_usb_interface *usb_if = dev->port.usb.usb_if;

		//pr_err("%s: PCAN-USB fw 2.8 workaround\n", DEVICE_NAME);
		DPRINTK(KERN_DEBUG "%s: %s fw 2.8 workaround\n",
				DEVICE_NAME, usb_if->adapter_name);
		err = usb_clear_halt(usb_if->usb_dev,
				usb_sndbulkpipe(usb_if->usb_dev,
						usb_if->pipe_cmd_out.ucNumber));
#ifdef DEBUG
		if (err)
			pr_err("%s: %s(): usb_clear_halt(1) failed err %d\n",
				DEVICE_NAME, __FUNCTION__, err);
#endif

		err = usb_clear_halt(usb_if->usb_dev,
				usb_rcvbulkpipe(usb_if->usb_dev,
						usb_if->pipe_cmd_in.ucNumber));
		if (err) {
			DPRINTK(KERN_DEBUG
				"%s: %s(): usb_clear_halt(2) failed err %d\n",
				DEVICE_NAME, __FUNCTION__, err);
			return err;
		}

		mdelay(50);
	}

	//Set SJA1000 in init mode
	err = pcan_usb_setcontrol_urb(dev, 9, 2, 0, 1,
	                  dummy, dummy, dummy, dummy, dummy, dummy,
	                  dummy, dummy, dummy, dummy, dummy, dummy);
	return err;
}

static int pcan_usb_setCANSilentOn(struct pcandev *dev)
{
	u8  dummy  = 0;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	return pcan_usb_setcontrol_urb(dev, 3, 3, 1, dummy,
	                 dummy, dummy, dummy, dummy, dummy, dummy,
	                 dummy, dummy, dummy, dummy, dummy, dummy);
}

static int pcan_usb_setCANSilentOff(struct pcandev *dev)
{
	u8  dummy  = 0;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	return pcan_usb_setcontrol_urb(dev, 3, 3, 0, dummy,
	                 dummy, dummy, dummy, dummy, dummy, dummy,
	                 dummy, dummy, dummy, dummy, dummy, dummy);
}

#if 0
/* not used */
static int pcan_usb_getBTR0BTR1(struct pcandev *dev, u16 *pwBTR0BTR1)
{
	int err;
	u8  dummy  = 0;
	u8  param0 = 0;
	u8  param1 = 0;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	err = pcan_usb_getcontrol_urb(dev, 1, 1, &param0, &param1, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy);

	*pwBTR0BTR1 = param1;
	*pwBTR0BTR1 <<= 8;
	*pwBTR0BTR1 |= param0;

	DPRINTK(KERN_DEBUG "%s: BTR0BTR1 = 0x%04x\n", DEVICE_NAME, *pwBTR0BTR1);

	return err;
}

static int pcan_usb_getQuartz(struct pcandev *dev, u32 *pdwQuartzHz)
{
	int err = 0;
	u8  dummy  = 0;
	u8  param0 = 0;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	err = pcan_usb_getcontrol_urb(dev, 2, 1, &param0, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy);

	*pdwQuartzHz = param0;
	*pdwQuartzHz *= 1000000L;

	DPRINTK(KERN_DEBUG "%s: Frequenz = %u\n", DEVICE_NAME, *pdwQuartzHz);

	return err;
}

static int pcan_usb_getAnything(struct pcandev *dev, u8 ucFunction, u8 ucNumber)
{
	int err = 0;
	u8  dummy[8];
	int i;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	for (i = 0; i < 7; i++)
		dummy[i] = 0;

	err = pcan_usb_getcontrol_urb(dev, ucFunction, ucNumber,
					                &dummy[0], &dummy[1], &dummy[2], &dummy[3], &dummy[4], &dummy[5], &dummy[6], &dummy[7]);

	DPRINTK(KERN_DEBUG "%s: Fun/Num:%d/%d  0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n", DEVICE_NAME,
					ucFunction, ucNumber, dummy[0], dummy[1], dummy[2], dummy[3], dummy[4], dummy[5], dummy[6], dummy[7]);

	return err;
}

static int pcan_usb_setExtVCCOn(struct pcandev *dev)
{
	u8  dummy  = 0;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	return pcan_usb_setcontrol_urb(dev, 0xA, 2, 1, dummy,
					                 dummy, dummy, dummy, dummy, dummy, dummy,
					                 dummy, dummy, dummy, dummy, dummy, dummy);
}

#endif

static int pcan_usb_getDeviceNr(struct pcandev *dev, u32 *pdwDeviceNr)
{
	int err;
	u8  dummy  = 0;
	u8 *pucDeviceNr = (u8 *)pdwDeviceNr;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	*pdwDeviceNr = 0;
	err = pcan_usb_getcontrol_urb(dev, 4, 1, pucDeviceNr, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &dummy);

	DPRINTK(KERN_DEBUG "%s: DeviceNr = 0x%x\n", DEVICE_NAME, *pdwDeviceNr);

#ifdef PCAN_DEV_USES_ALT_NUM
        if (!err && (*pucDeviceNr != 255)) {
		dev->device_alt_num = *pucDeviceNr;
		dev->flags |= PCAN_DEV_USES_ALT_NUM;
	}
#endif

	return err;
}

static int pcan_usb_setDeviceNr(struct pcandev *dev, u32 dwDeviceNr)
{
	u8  dummy  = 0;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	return pcan_usb_setcontrol_urb(dev, 4, 2, (u8 )dwDeviceNr, dummy,
	                 dummy, dummy, dummy, dummy, dummy, dummy,
	                 dummy, dummy, dummy, dummy, dummy, dummy);
}

static int pcan_usb_setExtVCCOff(struct pcandev *dev)
{
	u8  dummy  = 0;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	return pcan_usb_setcontrol_urb(dev, 0xA, 2, 0, dummy,
		                 dummy, dummy, dummy, dummy, dummy, dummy,
		                 dummy, dummy, dummy, dummy, dummy, dummy);
}

static int pcan_usb_getSNR(struct pcan_usb_interface *usb_if, uint32_t *pdwSNR)
{
	struct pcandev *dev = &usb_if->dev[0];
	int err = 0;
	ULCONV SNR;
	u8  dummy;
	int i = 1;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	memset(&SNR, 0, sizeof(SNR));

	// sometimes the hardware won't provide the number - so try twice
	do
		err = pcan_usb_getcontrol_urb(dev, 6, 1, 
		                             &SNR.uc[3], &SNR.uc[2], &SNR.uc[1], 
		                             &SNR.uc[0], &dummy, &dummy, &dummy, &dummy);
	while ((i--) && (err == -2));

	*pdwSNR = SNR.ul;

	DPRINTK(KERN_DEBUG "%s: SNR = 0x%08x\n", DEVICE_NAME, *pdwSNR);

	return err;
}


//****************************************************************************
// init hardware parts
static int pcan_usb_Init(struct pcandev *dev, u16 btr0btr1, u8 bListenOnly)
{
	int err = 0;

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __FUNCTION__);

	err = pcan_usb_setBTR0BTR1(dev, btr0btr1);
	if (err)
		goto fail;

	if (dev->port.usb.usb_if->ucRevision > 3)
	{
		// set listen only
		if (bListenOnly)
			err = pcan_usb_setCANSilentOn(dev);
		else
			err = pcan_usb_setCANSilentOff(dev);
		if (err)
			goto fail;
	}
	else
	{
		// generate err if one tries to set bListenOnly
		if (bListenOnly)
		{
			err = -EINVAL;
			goto fail;
		}
	}

	// don't know how to handle - walk the save way
	err = pcan_usb_setExtVCCOff(dev);

	// prepare for new start of timestamp calculation
	pcan_reset_timestamp(dev);

fail:
	return err;
}

//****************************************************************************
// takes USB-message frames out of ucMsgPtr, decodes and packs them into readFifo
static int pcan_usb_DecodeMessage(struct pcan_usb_interface *usb_if, u8 *ucMsgPtr, int lCurrentLength)
{
	int err = 0;
	int i, j;
	u8 ucMsgPrefix;
	u8 ucMsgLen;         // number of frames in one USB packet
	u8 ucStatusLen = 0;  // storage for the status/length entry leading each data frame
	u8 ucLen;            // len in bytes of received (CAN) data
	UWCONV       wTimeStamp;
	u8           *ucMsgStart = ucMsgPtr; // store start of buffer for overflow compare
	int rwakeup = 0;
	u8  *org = ucMsgPtr;
	u8  dataPacketCounter = 0;
	struct pcandev *dev = &usb_if->dev[0];

	// pcan usb core now waits for incoming message before the device being
	// opened by any user (USB-PRO needs handling such messages)
	// Thus, MUST check here if any path has been opened before posting any
	// messages
	if (dev->nOpenPaths <= 0) {
		DPRINTK(KERN_DEBUG "%s: pcan_usb_DecodeMessage(%p, %d): ignored (nOpenPaths=%d)\n", DEVICE_NAME, ucMsgPtr, lCurrentLength, dev->nOpenPaths);
		buffer_dump(ucMsgPtr, lCurrentLength/16+1);
		return 0;
	}

	//DPRINTK(KERN_DEBUG "%s: pcan_usb_DecodeMessage(%p, %d)\n", DEVICE_NAME, ucMsgPtr, lCurrentLength);
	//dump_mem("received buffer", ucMsgPtr, lCurrentLength);

	// don't count interrupts - count packets
	dev->dwInterruptCounter++;

	// sometimes is nothing to do
	if (!lCurrentLength)
		return err;

	// get prefix of message and step over
	ucMsgPrefix = *ucMsgPtr++;

	// get length of message and step over
	ucMsgLen    = *ucMsgPtr++;

	for (i = 0; i < ucMsgLen; i++) {
		ULCONV localID;
		struct timeval tv;
		TPCANRdMsg msg;
		struct can_frame frame;

		ucStatusLen = *ucMsgPtr++;

#if 0
		// TODO: take timestamp from PCAN-USB
		DO_GETTIMEOFDAY(tv);
#endif

		/* normal CAN message are always with timestamp */
		if (!(ucStatusLen & STLN_INTERNAL_DATA)) {
			int nRtrFrame;

			ucLen = ucStatusLen & STLN_DATA_LENGTH;
#ifndef HANDLE_DLC_GT_THAN_8
			if (ucLen > 8)
				ucLen = 8;
			frame.can_dlc = ucLen;
#else
			/* temporary, MUST check if lib and user app support */
			//frame.can_dlc = ucLen;
			frame.can_dlc = (ucLen > 8) ? 8 : ucLen;
#endif

			nRtrFrame = ucStatusLen & STLN_RTR;
			if (nRtrFrame)
				frame.can_id = CAN_RTR_FLAG;
			else
				frame.can_id = 0;

			msg.Msg.MSGTYPE = MSGTYPE_STANDARD;

#ifdef MSGTYPE_SELFRECEIVE
			/* check fw version if SR is supported */
			if (dev->port.usb.usb_if->ucRevision >= 41) {
				if (*ucMsgPtr & 0x01)
					msg.Msg.MSGTYPE |= MSGTYPE_SELFRECEIVE;
			}
#endif

			if (ucStatusLen & STLN_EXTENDED_ID) {
				frame.can_id |= CAN_EFF_FLAG;

#if defined(__LITTLE_ENDIAN)
				localID.uc[0] = *ucMsgPtr++;
				localID.uc[1] = *ucMsgPtr++;
				localID.uc[2] = *ucMsgPtr++;
				localID.uc[3] = *ucMsgPtr++;
#elif defined(__BIG_ENDIAN)
				localID.uc[3] = *ucMsgPtr++;
				localID.uc[2] = *ucMsgPtr++;
				localID.uc[1] = *ucMsgPtr++;
				localID.uc[0] = *ucMsgPtr++;
#else
#error  "Please fix the endianness defines in <asm/byteorder.h>"
#endif

				localID.ul   >>= 3;
			} else {
				localID.ul    = 0;

#if defined(__LITTLE_ENDIAN)
				localID.uc[0] = *ucMsgPtr++;
				localID.uc[1] = *ucMsgPtr++;
#elif defined(__BIG_ENDIAN)
				localID.uc[3] = *ucMsgPtr++;
				localID.uc[2] = *ucMsgPtr++;
#else
#error  "Please fix the endianness defines in <asm/byteorder.h>"
#endif

				localID.ul   >>= 5;
			}

			frame.can_id |= localID.ul;
			msg.Msg.ID = localID.ul;

			/* read timestamp, first timestamp in packet is 16 bit
			 * AND data, following timestamps are 8 bit in length */
			if (!dataPacketCounter) {
#if defined(__LITTLE_ENDIAN)
				wTimeStamp.uc[0] = *ucMsgPtr++;
				wTimeStamp.uc[1] = *ucMsgPtr++;
#elif defined(__BIG_ENDIAN)
				wTimeStamp.uc[1] = *ucMsgPtr++;
				wTimeStamp.uc[0] = *ucMsgPtr++;
#else
#error  "Please fix the endianness defines in <asm/byteorder.h>"
#endif

				pcan_updateTimeStampFromWord(dev, wTimeStamp.uw, i);
			} else
				pcan_updateTimeStampFromByte(dev, *ucMsgPtr++);

#ifndef HANDLE_DLC_GT_THAN_8
#else
			/* SGr FIX: 
			 * save in DATA array at most 8 bytes, ignore
			 * all others but ALWAYS increment msg ptr
			 * according to ucLen */
#endif
			/* read data */
			j = 0;
			if (!nRtrFrame) {
				while (ucLen--) {
					if (j < 8)
						frame.data[j++] = *ucMsgPtr;
					ucMsgPtr++;
				}
			}

#ifdef MSGTYPE_SELFRECEIVE
			/* there's another byte when SR flag is set
			 * (client handle) */
			if (msg.Msg.MSGTYPE & MSGTYPE_SELFRECEIVE)
				ucMsgPtr++;
#endif
			/* only for beauty */
			while (j < 8)
				frame.data[j++] = 0;

			pcan_calcTimevalFromTicks(dev, &tv);

			if ((err = pcan_xxxdev_rx_ex(dev, &frame,
						&tv, msg.Msg.MSGTYPE)) < 0) {
				if (net_ratelimit())
					pr_err("%s: pcan_xxxdev_rx(1) failed\n",
						DEVICE_NAME);
				//dump_mem(DEVICE_NAME, frame.data, j);
				goto fail;
			}

			/* successfully enqueued into chardev FIFO */
			if (err > 0)
				rwakeup++;

			dataPacketCounter++;

		/* Status Daten */
		} else {
			u8 ucFunction;
			u8 ucNumber;
			u8 dummy;

			memset(&frame, 0, sizeof(struct can_frame));

			/* declare as status Msg */
			msg.Msg.MSGTYPE = MSGTYPE_STATUS;

			/* prepare length of data */
			ucLen = ucStatusLen & STLN_DATA_LENGTH;
#ifndef HANDLE_DLC_GT_THAN_8
			if (ucLen > 8)
				ucLen = 8;
			msg.Msg.LEN = ucLen;
#else
			/* temporary, MUST check if lib and user app support */
			//msg.Msg.LEN = ucLen;
			msg.Msg.LEN = (ucLen > 8) ? 8 : ucLen;
#endif

			// get function and number
			ucFunction = *ucMsgPtr++;
			ucNumber   = *ucMsgPtr++;

			if (ucStatusLen & STLN_WITH_TIMESTAMP) {
				// only the first packet supplies a word timestamp
				if (!i) {
#if defined(__LITTLE_ENDIAN)
					wTimeStamp.uc[0] = *ucMsgPtr++;
					wTimeStamp.uc[1] = *ucMsgPtr++;
#elif defined(__BIG_ENDIAN)
					wTimeStamp.uc[1] = *ucMsgPtr++;
					wTimeStamp.uc[0] = *ucMsgPtr++;
#else
#error  "Please fix the endianness defines in <asm/byteorder.h>"
#endif

					pcan_updateTimeStampFromWord(dev, wTimeStamp.uw, i);
				}
				else
					pcan_updateTimeStampFromByte(dev, *ucMsgPtr++);
			}

			switch (ucFunction) {
			case 1: // can_error. number = flags, special decoding in PCAN-USB
				if ((ucNumber & CAN_RECEIVE_QUEUE_OVERRUN) ||
						(ucNumber & QUEUE_OVERRUN)) {
					dev->wCANStatus |= CAN_ERR_OVERRUN;
					frame.can_id  |= CAN_ERR_CRTL;
					frame.data[1]|=CAN_ERR_CRTL_RX_OVERFLOW;
					dev->dwErrorCounter++;
				}

				if (ucNumber & BUS_OFF) {
					dev->wCANStatus |=  CAN_ERR_BUSOFF;
					frame.can_id |= CAN_ERR_BUSOFF_NETDEV;
					dev->dwErrorCounter++;
				}

				if (ucNumber & BUS_HEAVY) {
					dev->wCANStatus |=  CAN_ERR_BUSHEAVY;
					frame.can_id  |= CAN_ERR_CRTL;
					frame.data[1]|= CAN_ERR_CRTL_RX_WARNING;
					dev->dwErrorCounter++;
				}

				if (ucNumber & BUS_LIGHT)
					dev->wCANStatus |= CAN_ERR_BUSLIGHT;

				/* version 3: sometimes the telegram carries 3
				 * additional data without note in ucStatusLen.
				 * */
#ifndef HANDLE_DLC_GT_THAN_8
				/* Don't know what to do ?? */
#else
				/* SGr FIX: 
				 * save in DATA array at most 8 bytes, ignore
				 * all others but ALWAYS increment msg ptr
				 * according to ucLen */
#endif
				j = 0;
				while (ucLen--) {
					if (j < 8)
						msg.Msg.DATA[j++] = *ucMsgPtr;
					ucMsgPtr++;
				}
				break;
			case 2: // get_analog_value, remove bytes
				dummy = *ucMsgPtr++;
				dummy = *ucMsgPtr++;
				break;
			case 3: // get_bus_load, remove byte
				dummy = *ucMsgPtr++;
				break;
			case 4: // only timestamp
#if defined(__LITTLE_ENDIAN)
				wTimeStamp.uc[0] = *ucMsgPtr++;
				wTimeStamp.uc[1] = *ucMsgPtr++;
#elif defined(__BIG_ENDIAN)
				wTimeStamp.uc[1] = *ucMsgPtr++;
				wTimeStamp.uc[0] = *ucMsgPtr++;
#else
#error  "Please fix the endianness defines in <asm/byteorder.h>"
#endif

				pcan_updateTimeStampFromWord(dev,
							wTimeStamp.uw, i);
				break;
			case 5: // ErrorFrame/ErrorBusEvent.
				if (ucNumber & QUEUE_XMT_FULL) {
					printk(KERN_ERR
						"%s: QUEUE_XMT_FULL signaled, ucNumber = 0x%02x\n", DEVICE_NAME, ucNumber);
					/* fatal error! */
					dev->wCANStatus |= CAN_ERR_QXMTFULL;
					dev->dwErrorCounter++;
				}

#ifdef HANDLE_DLC_GT_THAN_8
				/* SGr FIX: 
				 * save in DATA array at most 8 bytes, ignore
				 * all others but ALWAYS increment msg ptr
				 * according to ucLen */
#endif
				j = 0;
				while (ucLen--) {
					if (j < 8)
						msg.Msg.DATA[j++] = *ucMsgPtr;
					ucMsgPtr++;
				}
				break;
			case 10: // prepared for future
				break;
			default:
				printk(KERN_ERR "%s: unexpected function, i = %d, ucStatusLen = 0x%02x\n", DEVICE_NAME,
					      i, ucStatusLen);
				buffer_dump(org, 4);
			}

			/* if an error condition occurred, send an error frame
			 * to the userspace */
			if (frame.can_id) {
				frame.can_id |= CAN_ERR_FLAG;
				frame.can_dlc = CAN_ERR_DLC;

				pcan_calcTimevalFromTicks(dev, &tv);

				if ((err = pcan_xxxdev_rx(dev, &frame, &tv)) < 0) {// put into data sink
					if (net_ratelimit())
						pr_err("%s: pcan_xxxdev_rx(2) failure\n", DEVICE_NAME);
					//dump_mem(DEVICE_NAME, msg.Msg.DATA, msg.Msg.LEN);
					goto fail;
				}

				/* successfully enqueued into chardev FIFO */
				if (err > 0)
					rwakeup++;
			}
		}

		/* check for 'read from'-buffer overrun
		 * must be <= dev->port.usb.pipe_read.wDataSz) */
		if ((ucMsgPtr - ucMsgStart) > lCurrentLength) {

			/* sometimes v 3 overrides the buffer by 1 byte */
			if ((dev->port.usb.usb_if->ucRevision > 3) ||
				   ((dev->port.usb.usb_if->ucRevision <= 3)
				&& ((ucMsgPtr - ucMsgStart) > (lCurrentLength + 1)))) {
				err = -EFAULT;
#ifdef __LP64__
				printk(KERN_ERR "%s: Internal Error = %d (%ld, %d)\n", DEVICE_NAME, err, (ucMsgPtr - ucMsgStart), lCurrentLength);
#else
				printk(KERN_ERR "%s: Internal Error = %d (%d, %d)\n", DEVICE_NAME, err, (ucMsgPtr - ucMsgStart), lCurrentLength);
#endif
				buffer_dump(org, 4);
				goto fail;
			}
		}
	}

	if (rwakeup)
		wake_up_interruptible(&dev->read_queue);

fail:
	return err;
}

// gets messages out of write-fifo, encodes and puts them into USB buffer ucMsgPtr
// returns -ENODATA and *pnDataLength > 0 if I made a telegram and no more data are available
//         -ENODATA and *pnDataLength == 0 if I made no telegram and no more data are available
//         any ERROR else if something happend
//         no ERROR if I made a telegram and there are more data available
static int pcan_usb_EncodeMessage(struct pcandev *dev, u8 *ucMsgPtr, int *pnDataLength)
{
	int err         = 0;
	int nMsgCounter = 0;          // counts the messages stored in this URB packet
	u8  *ptr        = ucMsgPtr;   // work pointer into write buffer
	u8  ucLen;                    // CAN data length
	ULCONV localID;               // for easy endian conversion
	u8    *pucStatusLen;          // pointer to ucStatusLen byte in URB message buffer
	u8    *pucMsgCountPtr;        // pointer to MsgCount byte in URB message buffer
	int   j;                      // working counter
	u8    bFinish = 0;
	int   nDataLength = *pnDataLength;
	int   nBufferTop  = nDataLength - 14;  // buffer fill high water mark

	// DPRINTK(KERN_DEBUG "%s: %s() %d %d\n", DEVICE_NAME, __FUNCTION__, dev->writeFifo.nStored, pcan_fifo_empty(&dev->writeFifo));

	// indicate no packet
	*pnDataLength = 0;

	// put packet type information
	*ptr++ = 2;
	pucMsgCountPtr = ptr++;  // fill later the count of messages

	// pack packet
	while (!bFinish && ((ptr - ucMsgPtr) < nBufferTop)) {
		int nRtrFrame;
		TPCANMsg msg;                // pointer to supplied CAN message

		// release fifo buffer and step forward in fifo
		if ((err = pcan_fifo_get(&dev->writeFifo, &msg))) {
			bFinish = 1;

			if (err != -ENODATA) {
				DPRINTK(KERN_DEBUG "%s: can't get data out of writeFifo, avail data: %d, err: %d\n", DEVICE_NAME, dev->writeFifo.nStored, err);
			}

			continue;
		}

#ifdef MSGTYPE_SELFRECEIVE
		/* check fw version if SR is supported */
		if (dev->port.usb.usb_if->ucRevision < 41)
			msg.MSGTYPE &= ~MSGTYPE_SELFRECEIVE;
#endif

		// get ptr to ucStatusLen byte
		pucStatusLen = ptr++;

		*pucStatusLen = ucLen = msg.LEN & STLN_DATA_LENGTH;

		nRtrFrame = msg.MSGTYPE & MSGTYPE_RTR;
		if (nRtrFrame)
			*pucStatusLen |= STLN_RTR;  // add RTR flag

		j = 0;
		localID.ul = msg.ID;

		//dump_mem("sending Msg:", &msg, sizeof(TPCANMsg));

		if (msg.MSGTYPE & MSGTYPE_EXTENDED) {
			*pucStatusLen |= STLN_EXTENDED_ID;
			localID.ul   <<= 3;

#ifdef MSGTYPE_SELFRECEIVE
			if (msg.MSGTYPE & MSGTYPE_SELFRECEIVE)
				localID.ul |= 0x01;	/* SRR flag SJA1000 */
#endif
#if defined(__LITTLE_ENDIAN)
			*ptr++ = localID.uc[0];
			*ptr++ = localID.uc[1];
			*ptr++ = localID.uc[2];
			*ptr++ = localID.uc[3];
#elif defined(__BIG_ENDIAN)
			*ptr++ = localID.uc[3];
			*ptr++ = localID.uc[2];
			*ptr++ = localID.uc[1];
			*ptr++ = localID.uc[0];
#else
#error  "Please fix the endianness defines in <asm/byteorder.h>"
#endif
		} else {
			localID.ul   <<= 5;

#ifdef MSGTYPE_SELFRECEIVE
			if (msg.MSGTYPE & MSGTYPE_SELFRECEIVE)
				localID.ul |= 0x01;	/* SRR flag SJA1000 */
#endif
#if defined(__LITTLE_ENDIAN)
			*ptr++ = localID.uc[0];
			*ptr++ = localID.uc[1];
#elif defined(__BIG_ENDIAN)
			*ptr++ = localID.uc[3];
			*ptr++ = localID.uc[2];
#else
#error  "Please fix the endianness defines in <asm/byteorder.h>"
#endif
		}

		if (!nRtrFrame) {
			// put data
#ifdef HANDLE_DLC_GT_THAN_8
			/* SGr NOTE: copy *ONLY* 8 bytes max */
#endif
			j = 0;
			while (ucLen--)
				*ptr++ = (j < 8) ? msg.DATA[j++] : 0;
		}

#ifdef MSGTYPE_SELFRECEIVE
		if (msg.MSGTYPE & MSGTYPE_SELFRECEIVE)
			*ptr++ = 0x80;
#endif

		nMsgCounter++;
	}

	// generate external nDataLength if I carry payload
	if ((ptr - ucMsgPtr) > 2) {
		*pnDataLength = nDataLength;

		// set count of telegrams
		ptr = ucMsgPtr + nDataLength - 1;
		*ptr = (u8)(dev->port.usb.dwTelegramCount++ & 0xff);

		// last to do: put count of messages
		*pucMsgCountPtr = nMsgCounter;
	} else {
		*pnDataLength   = 0;
		*pucMsgCountPtr = 0;
	}

	//dump_mem("Tx buffer:", ucMsgPtr, *pnDataLength);
	return err;
}

/*
 * void pcan_usb_cleanup(struct pcandev *dev)
 *
 * Last chance to submit URB before drievr removal.
 */
static void pcan_usb_cleanup(struct pcandev *dev)
{
	/* Set CAN bus off here now since we're sure that the request will be */
	/* sent to the usb module */
	pcan_usb_setCANOff(dev);
}

#ifdef PCAN_DEV_USES_ALT_NUM
static int pcan_usb_ctrl_init(struct pcandev *dev)
{
	struct pcan_usb_interface *usb_if = dev->port.usb.usb_if;

	pr_info("%s: %s channel device number=%u\n", 
		DEVICE_NAME, usb_if->adapter_name, dev->device_alt_num);
	return 0;
}
#endif

/*
 * int pcan_usb_init(struct pcan_usb_interface *usb_if)
 *
 * Do the initialization part of a PCAN-USB adapter.
 */
int pcan_usb_init(struct pcan_usb_interface *usb_if)
{
	usb_if->adapter_name = "PCAN-USB";
#ifdef PCAN_DEV_USES_ALT_NUM
	usb_if->device_ctrl_init = pcan_usb_ctrl_init;
#endif
	usb_if->device_ctrl_cleanup = pcan_usb_cleanup;
	usb_if->device_ctrl_open = pcan_usb_Init;
	usb_if->device_ctrl_set_bus_on = pcan_usb_setCANOn;
	usb_if->device_ctrl_set_bus_off = pcan_usb_setCANOff;
	usb_if->device_get_snr = pcan_usb_getSNR;
	usb_if->device_ctrl_set_dnr = pcan_usb_setDeviceNr;
	usb_if->device_ctrl_get_dnr = pcan_usb_getDeviceNr;
	usb_if->device_ctrl_msg_encode = pcan_usb_EncodeMessage;
	usb_if->device_msg_decode = pcan_usb_DecodeMessage;

#ifdef PCAN_DEV_USES_ALT_NUM
	/*
	 * MUST initialize alt_num here (before creating devices) for Udev rules
	 */
	usb_if->dev[0].device_alt_num = 0xff;
#endif

#if 0
	/* check do_div() macro */
	{
		uint64_t q, dd = (0xFULL << 34) + 1;
		uint32_t r, dr = 2;

		q = dd;
		r = do_div(q, dr);

		printk(KERN_INFO "%s(): %llu / %u = %llu (r=%u)\n", __FUNCTION__,
		       dd, dr, q, r);
	}
#endif

	return 0;
}
