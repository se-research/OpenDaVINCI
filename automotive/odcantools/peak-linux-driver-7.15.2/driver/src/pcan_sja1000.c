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
// Maintainer(s): Stephane Grosjean (s.grosjean@peak-system.com)
//
// Major contributions by:
//                Klaus Hitschler   (klaus.hitschler@gmx.de)
//                Edouard Tisserant (edouard.tisserant@lolitech.fr) XENOMAI
//                Laurent Bessard   (laurent.bessard@lolitech.fr)   XENOMAI
//                Oliver Hartkopp   (oliver.hartkopp@volkswagen.de) socketCAN
//
// Contributions: Arnaud Westenberg (arnaud@wanadoo.nl)
//                Matt Waters (Matt.Waters@dynetics.com)
//                Benjamin Kolb (Benjamin.Kolb@bigfoot.de)
//****************************************************************************

//****************************************************************************
//
// pcan_sja1000.c - all about sja1000 init and data handling
//
// $Id: pcan_sja1000.c 786 2014-07-21 13:21:35Z stephane $
//
//****************************************************************************

//#define DEBUG
//#undef DEBUG

//#define PCAN_SJA1000_STATS
#define PCAN_SJA1000_USES_ISR_LOCK
//#define PCAN_SJA1000_DISABLE_IRQ

//****************************************************************************
// INCLUDES
#include <src/pcan_common.h>
#include <linux/sched.h>
#include <asm/errno.h>
#include <asm/byteorder.h>  // because of little / big endian
#include <linux/delay.h>
#include <src/pcan_main.h>
#include <src/pcan_fifo.h>
#include <src/pcan_sja1000.h>

#ifdef NETDEV_SUPPORT
#include <src/pcan_netdev.h>
#endif

//****************************************************************************
// DEFINES

// sja1000 registers, only PELICAN mode - TUX like it
#define MODE                   0      // mode register
#define COMMAND                1
#define CHIPSTATUS             2
#define INTERRUPT_STATUS       3
#define INTERRUPT_ENABLE       4      // acceptance code
#define TIMING0                6      // bus timing 0
#define TIMING1                7      // bus timing 1
#define OUTPUT_CONTROL         8      // output control
#define TESTREG                9

#define ARBIT_LOST_CAPTURE    11      // transmit buffer: Identifier
#define ERROR_CODE_CAPTURE    12      // RTR bit und data length code
#define ERROR_WARNING_LIMIT   13      // start byte of data field
#define RX_ERROR_COUNTER      14
#define TX_ERROR_COUNTER      15

#define ACCEPTANCE_CODE_BASE  16
#define RECEIVE_FRAME_BASE    16
#define TRANSMIT_FRAME_BASE   16

#define ACCEPTANCE_MASK_BASE  20

#define RECEIVE_MSG_COUNTER   29
#define RECEIVE_START_ADDRESS 30

#define CLKDIVIDER            31      // set bit rate and pelican mode

// important sja1000 register contents, MODE register
#define SLEEP_MODE             0x10
#define ACCEPT_FILTER_MODE     0x08
#define SELF_TEST_MODE         0x04
#define LISTEN_ONLY_MODE       0x02
#define RESET_MODE             0x01
#define NORMAL_MODE            0x00

// COMMAND register
#define CLEAR_DATA_OVERRUN     0x08
#define RELEASE_RECEIVE_BUFFER 0x04
#define ABORT_TRANSMISSION     0x02
#define TRANSMISSION_REQUEST   0x01

// CHIPSTATUS register
#define BUS_STATUS             0x80
#define ERROR_STATUS           0x40
#define TRANSMIT_STATUS        0x20
#define RECEIVE_STATUS         0x10
#define TRANS_COMPLETE_STATUS  0x08
#define TRANS_BUFFER_STATUS    0x04
#define DATA_OVERRUN_STATUS    0x02
#define RECEIVE_BUFFER_STATUS  0x01

// INTERRUPT STATUS register
#define BUS_ERROR_INTERRUPT    0x80
#define ARBIT_LOST_INTERRUPT   0x40
#define ERROR_PASSIV_INTERRUPT 0x20
#define WAKE_UP_INTERRUPT      0x10
#define DATA_OVERRUN_INTERRUPT 0x08
#define ERROR_WARN_INTERRUPT   0x04
#define TRANSMIT_INTERRUPT     0x02
#define RECEIVE_INTERRUPT      0x01

// INTERRUPT ENABLE register
#define BUS_ERROR_INTERRUPT_ENABLE    0x80
#define ARBIT_LOST_INTERRUPT_ENABLE   0x40
#define ERROR_PASSIV_INTERRUPT_ENABLE 0x20
#define WAKE_UP_INTERRUPT_ENABLE      0x10
#define DATA_OVERRUN_INTERRUPT_ENABLE 0x08
#define ERROR_WARN_INTERRUPT_ENABLE   0x04
#define TRANSMIT_INTERRUPT_ENABLE     0x02
#define RECEIVE_INTERRUPT_ENABLE      0x01

// OUTPUT CONTROL register
#define OUTPUT_CONTROL_TRANSISTOR_P1  0x80
#define OUTPUT_CONTROL_TRANSISTOR_N1  0x40
#define OUTPUT_CONTROL_POLARITY_1     0x20
#define OUTPUT_CONTROL_TRANSISTOR_P0  0x10
#define OUTPUT_CONTROL_TRANSISTOR_N0  0x08
#define OUTPUT_CONTROL_POLARITY_0     0x04
#define OUTPUT_CONTROL_MODE_1         0x02
#define OUTPUT_CONTROL_MODE_0         0x01

// TRANSMIT or RECEIVE BUFFER
#define BUFFER_EFF                    0x80 // set for 29 bit identifier
#define BUFFER_RTR                    0x40 // set for RTR request
#define BUFFER_DLC_MASK               0x0f

// CLKDIVIDER register
#define CAN_MODE                      0x80
#define CAN_BYPASS                    0x40
#define RXINT_OUTPUT_ENABLE           0x20
#define CLOCK_OFF                     0x08
#define CLOCK_DIVIDER_MASK            0x07

// additional informations
#define CLOCK_HZ                  16000000 // crystal frequency

// time for mode register to change mode
#define MODE_REGISTER_SWITCH_TIME 100 // msec

// some CLKDIVIDER register contents, hardware architecture dependend
#define PELICAN_SINGLE  (CAN_MODE | CAN_BYPASS | 0x07 | CLOCK_OFF)
#define PELICAN_MASTER  (CAN_MODE | CAN_BYPASS | 0x07            )
#define PELICAN_DEFAULT (CAN_MODE                                )
#define CHIP_RESET      PELICAN_SINGLE

// hardware depended setup for OUTPUT_CONTROL register
#define OUTPUT_CONTROL_SETUP (OUTPUT_CONTROL_TRANSISTOR_P0 | OUTPUT_CONTROL_TRANSISTOR_N0 | OUTPUT_CONTROL_MODE_1)

// the interrupt enables
#define INTERRUPT_ENABLE_SETUP (RECEIVE_INTERRUPT_ENABLE | TRANSMIT_INTERRUPT_ENABLE | DATA_OVERRUN_INTERRUPT_ENABLE | BUS_ERROR_INTERRUPT_ENABLE | ERROR_PASSIV_INTERRUPT_ENABLE | ERROR_WARN_INTERRUPT_ENABLE)

// the maximum number of handled messages in one interrupt
#define MAX_MESSAGES_PER_INTERRUPT 8

// the maximum number of handled sja1000 interrupts in 1 handler entry
#define MAX_INTERRUPTS_PER_ENTRY   1

// constants from Arnaud Westenberg email:arnaud@wanadoo.nl
#define MAX_TSEG1  15
#define MAX_TSEG2  7
#define BTR1_SAM   (1<<1)

//****************************************************************************
// GLOBALS

//****************************************************************************
// LOCALS
static uint irqmaxloop = MAX_INTERRUPTS_PER_ENTRY;
module_param(irqmaxloop, uint, 0644);
MODULE_PARM_DESC(irqmaxloop, " max loops in ISR per CAN (0=nolimit "__stringify(MAX_INTERRUPTS_PER_ENTRY)"=def)");

static uint irqmaxrmsg = MAX_MESSAGES_PER_INTERRUPT;
module_param(irqmaxrmsg, uint, 0644);
MODULE_PARM_DESC(irqmaxrmsg, " max msgs read per Rx IRQ (0=nolimit "__stringify(MAX_MESSAGES_PER_INTERRUPT)"=def)");

//****************************************************************************
// CODE

#ifdef NO_RT
#include "pcan_sja1000_linux.c"
#else
#include "pcan_sja1000_rt.c"
#endif

#ifdef PCAN_SJA1000_STATS
/* Well, this is only for debugging purpose since this is not attached to a */
/* single device! */
struct pcandev_stats
{
	unsigned long int_count;
	unsigned long int_no_count;
	unsigned long int_tx_count;
	unsigned long int_ovr_count;
	unsigned long int_rx_count;
	unsigned long int_err_count;
	unsigned long wakup_w_count;
	unsigned long wakup_r_count;
	unsigned long write_count;
	unsigned long _write_count;
	unsigned long write_frm_count;
};
static struct pcandev_stats dev_stats;

static void sja1000_print_stats(struct pcandev_stats *s)
{
	printk(KERN_INFO "INT=%lu (NONE=%lu TX=%lu RX=%lu OVR=%lu ERR=%lu)\n", 
	       s->int_count, s->int_no_count, s->int_tx_count, s->int_rx_count, 
	       s->int_ovr_count, s->int_err_count);
	printk(KERN_INFO "WAKEUP_W=%lu WAKEUP_R=%lu\n", 
	       s->wakup_w_count, s->wakup_r_count);
	printk(KERN_INFO "WRITE=%lu _WRITE=%lu WRITE_FRM=%lu\n", 
	       s->write_count, s->_write_count, s->write_frm_count);
}
#endif

//----------------------------------------------------------------------------
// guards writing sja1000's command register in multicore environments
static inline void guarded_write_command(struct pcandev *dev, u8 data)
{
	DECLARE_SPIN_LOCK_IRQSAVE_FLAGS;

	SPIN_LOCK_IRQSAVE(&dev->wlock);
	dev->writereg(dev, COMMAND, data);
	/* draw a breath after writing the command register */
	dev->readreg(dev, CHIPSTATUS);
	SPIN_UNLOCK_IRQRESTORE(&dev->wlock);
	//wmb();
}

//----------------------------------------------------------------------------
// switches the chip into reset mode
static int set_reset_mode(struct pcandev *dev)
{
	u32 dwStart = get_mtime();
	u8 tmp;

	tmp = dev->readreg(dev, MODE);
	while (!(tmp & RESET_MODE) && ((get_mtime() - dwStart) < MODE_REGISTER_SWITCH_TIME)) {
		/* force into reset mode */
		dev->writereg(dev, MODE, RESET_MODE);
		wmb();
		udelay(1);
		//schedule();
		tmp = dev->readreg(dev, MODE);
	}

	if (!(tmp & RESET_MODE))
		return -EIO;

	return 0;
}

//----------------------------------------------------------------------------
// switches the chip back from reset mode
static int set_normal_mode(struct pcandev *dev, u8 ucModifier)
{
	u32 dwStart = get_mtime();
	u8  tmp;

	tmp = dev->readreg(dev, MODE);
	while ((tmp != ucModifier) && ((get_mtime() - dwStart) < MODE_REGISTER_SWITCH_TIME)) {
		/* force into normal mode */
		dev->writereg(dev, MODE, ucModifier);
		wmb();
		udelay(1);
		//schedule();
		tmp = dev->readreg(dev, MODE);
	}

	if (tmp != ucModifier)
		return -EIO;

	return 0;
}

//----------------------------------------------------------------------------
// interrupt enable and disable
static inline void sja1000_irq_enable_mask(struct pcandev *dev, u8 mask)
{
	DPRINTK(KERN_DEBUG "%s: %s(%u, mask=%02xh)\n", 
		DEVICE_NAME, __func__, dev->nMinor, mask);

	dev->writereg(dev, INTERRUPT_ENABLE, mask);
}

static inline void sja1000_irq_disable_mask(struct pcandev *dev, u8 mask)
{
	DPRINTK(KERN_DEBUG "%s: %s(%u, mask=%02xh)\n", 
		DEVICE_NAME, __func__, dev->nMinor, mask);

	dev->writereg(dev, INTERRUPT_ENABLE, ~mask);
}

static inline void sja1000_irq_enable(struct pcandev *dev)
{
	DPRINTK(KERN_DEBUG "%s: %s(%u)\n", DEVICE_NAME, __func__, dev->nMinor);

	//dev->writereg(dev, INTERRUPT_ENABLE, INTERRUPT_ENABLE_SETUP);
	sja1000_irq_enable_mask(dev, INTERRUPT_ENABLE_SETUP);
}

static inline void sja1000_irq_disable(struct pcandev *dev)
{
	DPRINTK(KERN_DEBUG "%s: %s(%u)\n", DEVICE_NAME, __func__, dev->nMinor);

	//dev->writereg(dev, INTERRUPT_ENABLE, 0);
	sja1000_irq_disable_mask(dev, 0xff);
}

//----------------------------------------------------------------------------
// find the proper clock divider
static inline u8 clkdivider(struct pcandev *dev)
{
	if (!dev->props.ucExternalClock)  // crystal based
		return PELICAN_DEFAULT;

	// configure clock divider register, switch into pelican mode, depended of of type
	switch (dev->props.ucMasterDevice)
	{
	case CHANNEL_SLAVE:
	case CHANNEL_SINGLE:
		return PELICAN_SINGLE;  // neither a slave nor a single device distribute the clock ...

	default:
		return PELICAN_MASTER;  // ... but a master does
	}
}

//----------------------------------------------------------------------------
// init CAN-chip
int sja1000_open(struct pcandev *dev, u16 btr0btr1, u8 bExtended, u8 bListenOnly)
{
	int result      = 0;
	u8  _clkdivider = clkdivider(dev);
	u8  ucModifier  = (bListenOnly) ? LISTEN_ONLY_MODE : NORMAL_MODE;

	DPRINTK(KERN_DEBUG "%s: %s(%u)\n", DEVICE_NAME, __func__, dev->nMinor);

	// switch to reset
	result = set_reset_mode(dev);
	if (result)
		goto fail;

	// take a fresh status
	dev->wCANStatus = 0;

	// store extended mode (standard still accepted)
	dev->bExtended = bExtended;

	// configure clock divider register, switch into pelican mode, depended of of type
	dev->writereg(dev, CLKDIVIDER, _clkdivider);

	// configure acceptance code registers
	dev->writereg(dev, ACCEPTANCE_CODE_BASE,     0);
	dev->writereg(dev, ACCEPTANCE_CODE_BASE + 1, 0);
	dev->writereg(dev, ACCEPTANCE_CODE_BASE + 2, 0);
	dev->writereg(dev, ACCEPTANCE_CODE_BASE + 3, 0);

	// configure all acceptance mask registers to don't care
	dev->writereg(dev, ACCEPTANCE_MASK_BASE,     0xff);
	dev->writereg(dev, ACCEPTANCE_MASK_BASE + 1, 0xff);
	dev->writereg(dev, ACCEPTANCE_MASK_BASE + 2, 0xff);
	dev->writereg(dev, ACCEPTANCE_MASK_BASE + 3, 0xff);

	// configure bus timing registers
	dev->writereg(dev, TIMING0, (u8)((btr0btr1 >> 8) & 0xff));
	dev->writereg(dev, TIMING1, (u8)((btr0btr1     ) & 0xff));

	// configure output control registers
	dev->writereg(dev, OUTPUT_CONTROL, OUTPUT_CONTROL_SETUP);

	// clear any pending interrupt
	dev->readreg(dev, INTERRUPT_STATUS);

	// enter normal operating mode
	result = set_normal_mode(dev, ucModifier);
	if (result)
		goto fail;

#ifdef PCAN_SJA1000_STATS
	memset(&dev_stats, 0, sizeof(dev_stats));
#endif

	// enable CAN interrupts
	sja1000_irq_enable(dev);

fail:
	return result;
}

//----------------------------------------------------------------------------
// release CAN-chip
void sja1000_release(struct pcandev *dev)
{
	DPRINTK(KERN_DEBUG "%s: %s(%u)\n", DEVICE_NAME, __func__, dev->nMinor);

	// abort pending transmissions
	guarded_write_command(dev, ABORT_TRANSMISSION);

	// disable CAN interrupts and set chip in reset mode
	sja1000_irq_disable(dev);
	set_reset_mode(dev);

#ifdef PCAN_SJA1000_STATS
	sja1000_print_stats(&dev_stats);
#endif
}

//----------------------------------------------------------------------------
// read CAN-data from chip, supposed a message is available
static int sja1000_read_frames(SJA1000_METHOD_ARGS)
{
	int msgs = irqmaxrmsg;
	u8 fi;
	u8 dreg;
	u8 dlc;
	ULCONV localID;
	struct can_frame frame;
	struct timeval tv;

	int i;
	int result = 0;

	// DPRINTK(KERN_DEBUG "%s: %s(%u)\n", 
	//	DEVICE_NAME, __func__, dev->nMinor);

	do {
		DO_GETTIMEOFDAY(tv); /* create timestamp */

		fi  = dev->readreg(dev, RECEIVE_FRAME_BASE);
		dlc = fi & BUFFER_DLC_MASK;

		if (dlc > 8)
			dlc = 8;

		if (fi & BUFFER_EFF) {
			/* extended frame format (EFF) */
			dreg = RECEIVE_FRAME_BASE + 5;

#if defined(__LITTLE_ENDIAN)
			localID.uc[3] = dev->readreg(dev, RECEIVE_FRAME_BASE + 1);
			localID.uc[2] = dev->readreg(dev, RECEIVE_FRAME_BASE + 2);
			localID.uc[1] = dev->readreg(dev, RECEIVE_FRAME_BASE + 3);
			localID.uc[0] = dev->readreg(dev, RECEIVE_FRAME_BASE + 4);
#elif defined(__BIG_ENDIAN)
			localID.uc[0] = dev->readreg(dev, RECEIVE_FRAME_BASE + 1);
			localID.uc[1] = dev->readreg(dev, RECEIVE_FRAME_BASE + 2);
			localID.uc[2] = dev->readreg(dev, RECEIVE_FRAME_BASE + 3);
			localID.uc[3] = dev->readreg(dev, RECEIVE_FRAME_BASE + 4);
#else
#error  "Please fix the endianness defines in <asm/byteorder.h>"
#endif

			frame.can_id = (localID.ul >> 3) | CAN_EFF_FLAG;
		} else {
			/* standard frame format (EFF) */
			dreg = RECEIVE_FRAME_BASE + 3;

			localID.ul    = 0;
#if defined(__LITTLE_ENDIAN)
			localID.uc[3] = dev->readreg(dev, RECEIVE_FRAME_BASE + 1);
			localID.uc[2] = dev->readreg(dev, RECEIVE_FRAME_BASE + 2);
#elif defined(__BIG_ENDIAN)
			localID.uc[0] = dev->readreg(dev, RECEIVE_FRAME_BASE + 1);
			localID.uc[1] = dev->readreg(dev, RECEIVE_FRAME_BASE + 2);
#else
#error  "Please fix the endianness defines in <asm/byteorder.h>"
#endif

			frame.can_id = (localID.ul >> 21);
		}

		if (fi & BUFFER_RTR)
			frame.can_id |= CAN_RTR_FLAG;

		/* clear aligned data section */
		*(__u64 *) &frame.data[0] = (__u64) 0;

		for (i = 0; i < dlc; i++)
			frame.data[i] = dev->readreg(dev, dreg++);

		frame.can_dlc = dlc;

		SJA1000_LOCK_IRQSAVE(in_lock);

		if ((i = pcan_xxxdev_rx(dev, &frame, &tv))) // put into specific data sink
			result = i; // save the last result

		SJA1000_UNLOCK_IRQRESTORE(in_lock);

		/* 
		 * Any error processing on result =! 0 here?
		 * Indeed we have to read from the controller as long as we
		 * receive data to unblock the controller. If we have problems
		 * to fill the CAN frames into the receive queues, this cannot
		 * be handled inside the interrupt.
		 */

		/* release the receive buffer */
		guarded_write_command(dev, RELEASE_RECEIVE_BUFFER);

		/* give time to settle */
		udelay(1);

	} while (dev->readreg(dev, CHIPSTATUS) & RECEIVE_BUFFER_STATUS && 
								(msgs--));

	return result;
}

//----------------------------------------------------------------------------
// write CAN-data to chip,
static int __sja1000_write_frame(struct pcandev *dev, struct can_frame *cf)
{
	u8 fi;
	u8 dlc;
	canid_t id;
	ULCONV localID;
	u8 dreg;
	int i;

	fi = dlc = cf->can_dlc;
	id = localID.ul = cf->can_id;

#ifdef PCAN_SJA1000_STATS
	dev_stats.write_frm_count++;
#endif

	if (id & CAN_RTR_FLAG)
		fi |= BUFFER_RTR;

	if (id & CAN_EFF_FLAG) {
		dreg  = TRANSMIT_FRAME_BASE + 5;
		fi   |= BUFFER_EFF;

		localID.ul   <<= 3;

		dev->writereg(dev, TRANSMIT_FRAME_BASE, fi);

#if defined(__LITTLE_ENDIAN)
		dev->writereg(dev, TRANSMIT_FRAME_BASE + 1, localID.uc[3]);
		dev->writereg(dev, TRANSMIT_FRAME_BASE + 2, localID.uc[2]);
		dev->writereg(dev, TRANSMIT_FRAME_BASE + 3, localID.uc[1]);
		dev->writereg(dev, TRANSMIT_FRAME_BASE + 4, localID.uc[0]);
#elif defined(__BIG_ENDIAN)
		dev->writereg(dev, TRANSMIT_FRAME_BASE + 1, localID.uc[0]);
		dev->writereg(dev, TRANSMIT_FRAME_BASE + 2, localID.uc[1]);
		dev->writereg(dev, TRANSMIT_FRAME_BASE + 3, localID.uc[2]);
		dev->writereg(dev, TRANSMIT_FRAME_BASE + 4, localID.uc[3]);
#else
#error  "Please fix the endianness defines in <asm/byteorder.h>"
#endif
	} else {
		dreg = TRANSMIT_FRAME_BASE + 3;

		localID.ul   <<= 21;

		dev->writereg(dev, TRANSMIT_FRAME_BASE, fi);

#if defined(__LITTLE_ENDIAN)
		dev->writereg(dev, TRANSMIT_FRAME_BASE + 1, localID.uc[3]);
		dev->writereg(dev, TRANSMIT_FRAME_BASE + 2, localID.uc[2]);
#elif defined(__BIG_ENDIAN)
		dev->writereg(dev, TRANSMIT_FRAME_BASE + 1, localID.uc[0]);
		dev->writereg(dev, TRANSMIT_FRAME_BASE + 2, localID.uc[1]);
#else
#error  "Please fix the endianness defines in <asm/byteorder.h>"
#endif
	}

	for (i = 0; i < dlc; i++)
		dev->writereg(dev, dreg++, cf->data[i]);

	/* request a transmission */
	guarded_write_command(dev, TRANSMISSION_REQUEST);

	return 0;
}

/* Called by isr */
static int __sja1000_write(SJA1000_METHOD_ARGS)
{
	int result;
	TPCANMsg msg;
	struct can_frame cf;

#ifdef PCAN_SJA1000_STATS
	dev_stats._write_count++;
#endif

	// DPRINTK(KERN_DEBUG "%s: %s(%u) %d\n", 
	//	DEVICE_NAME, __func__, dev>nMinor, dev->writeFifo.nStored);

	SJA1000_LOCK_IRQSAVE(out_lock);

	/* get a fifo element and step forward */
	result = pcan_fifo_get(&dev->writeFifo, &msg);

	SJA1000_WAKEUP_EMPTY();

	SJA1000_UNLOCK_IRQRESTORE(out_lock);

	if (result)
		return result;

	/* 
	 * convert from old style FIFO message until FIFO supports new
	 * struct can_frame and error frames
	 */	
	msg2frame(&cf, &msg);

	__sja1000_write_frame(dev, &cf);

	return 0;
}

//----------------------------------------------------------------------------
// write CAN-data from FIFO to chip
int sja1000_write(SJA1000_METHOD_ARGS)
{
	int err = 0;
#ifdef PCAN_SJA1000_USES_ISR_LOCK
	DECLARE_SPIN_LOCK_IRQSAVE_FLAGS;

	SPIN_LOCK_IRQSAVE(&dev->isr_lock);
#endif

#ifdef PCAN_SJA1000_STATS
	dev_stats.write_count++;
#endif

	// DPRINTK(KERN_DEBUG "%s: %s(%u) %d\n",
	//	DEVICE_NAME, __func__, dev->nMinor, dev->writeFifo.nStored);

	/* Check if Tx buffer is empty before writing on */
	if (dev->readreg(dev, CHIPSTATUS) & TRANS_BUFFER_STATUS) {
#ifdef NO_RT
		err = __sja1000_write(dev);
#else
		err = __sja1000_write(dev, ctx);
#endif
	}

#ifdef PCAN_SJA1000_USES_ISR_LOCK
	SPIN_UNLOCK_IRQRESTORE(&dev->isr_lock);
#endif

	return err;
}

//----------------------------------------------------------------------------
// handle a interrupt request
int sja1000_irqhandler_common(SJA1000_METHOD_ARGS)
{
	int ret = SJA1000_IRQ_NONE;
	u8 irqstatus;
	int err;
	u16 rwakeup = 0;
	u16 wwakeup = 0;
	/* except the Rx flag, but this is processed by polling the Rx BUFFER */
	/* STATUS reg bit*/ 
	int j = irqmaxloop;
#ifdef PCAN_SJA1000_USES_ISR_LOCK
	DECLARE_SPIN_LOCK_IRQSAVE_FLAGS;
#endif
#ifdef PCAN_SJA1000_DISABLE_IRQ
	int int_disabled = 0;
#endif
	struct can_frame ef;

	memset(&ef, 0, sizeof(ef));

#ifdef PCAN_SJA1000_USES_ISR_LOCK
	SPIN_LOCK_IRQSAVE(&dev->isr_lock);
#endif

#ifdef PCAN_SJA1000_STATS
	dev_stats.int_count++;
#endif

	SJA1000_LOCK_IRQSAVE(sja_lock);

	while ((j--) && (irqstatus = dev->readreg(dev, INTERRUPT_STATUS))) {

#ifdef PCAN_SJA1000_DISABLE_IRQ
		if (!int_disabled) {
			sja1000_irq_disable_mask(dev, INTERRUPT_ENABLE_SETUP);
			int_disabled = 1;
		}
#endif
		dev->dwInterruptCounter++;
		err = 0;

		/*
		 * quick hack to badly workaround write stall
		 * if ((irqstatus & TRANSMIT_INTERRUPT) || 
		 *     (!atomic_read(&dev->DataSendReady) && 
		 *      !pcan_fifo_empty(&dev->writeFifo) && 
		 *      (dev->readreg(dev, CHIPSTATUS) & TRANS_BUFFER_STATUS)))
		 */
		if (irqstatus & TRANSMIT_INTERRUPT) {
#ifdef PCAN_SJA1000_STATS
			dev_stats.int_tx_count++;
#endif
			/* handle transmission */
			if ((err = SJA1000_FUNCTION_CALL(__sja1000_write))) {
				if (err == -ENODATA) {
					wwakeup++;
				} else {
					dev->nLastError = err;
					dev->dwErrorCounter++;
					dev->wCANStatus |= CAN_ERR_QXMTFULL;
				}
			}

			/* reset to ACTIVITY_IDLE by cyclic timer */
			dev->ucActivityState = ACTIVITY_XMIT;
		}

		if (irqstatus & DATA_OVERRUN_INTERRUPT) {
#ifdef PCAN_SJA1000_STATS
			dev_stats.int_ovr_count++;
#endif
			/* handle data overrun */
			dev->wCANStatus |= CAN_ERR_OVERRUN;
			ef.can_id |= CAN_ERR_CRTL;
			ef.data[1] |= CAN_ERR_CRTL_RX_OVERFLOW;
			rwakeup++;
			dev->dwErrorCounter++;

			guarded_write_command(dev, CLEAR_DATA_OVERRUN);

#if 0
			DPRINTK(KERN_DEBUG "%s: %s(%d), DATA_OVR\n", 
				DEVICE_NAME, __func__, dev->nMinor);
#endif
			/* reset to ACTIVITY_IDLE by cyclic time */
			dev->ucActivityState = ACTIVITY_XMIT;
		}

		if (irqstatus & RECEIVE_INTERRUPT) {
#ifdef PCAN_SJA1000_STATS
			dev_stats.int_rx_count++;
#endif
			/* handle reception */
			err = SJA1000_FUNCTION_CALL(sja1000_read_frames);

			/* put to input queues */
			if (err < 0) {
				dev->nLastError = err;
				dev->dwErrorCounter++;
				dev->wCANStatus |= CAN_ERR_QOVERRUN;

				/*
				 * throw away last message which was refused by
				 * fifo
				 */
				guarded_write_command(dev, 
							RELEASE_RECEIVE_BUFFER);
			}

			/* successfully enqueued into chardev FIFO */
			if (err > 0)
				rwakeup++;

			/* reset to ACTIVITY_IDLE by cyclic timer */
			dev->ucActivityState = ACTIVITY_XMIT;
		}

#if 0
		DPRINTK(KERN_DEBUG "%s: %s(%d), irqstatus=%02Xh\n",
			DEVICE_NAME, __func__, dev->nMinor, irqstatus);
#endif
		if (irqstatus & (ERROR_PASSIV_INTERRUPT|ERROR_WARN_INTERRUPT)) {

			u8 chipstatus = dev->readreg(dev, CHIPSTATUS);

#if 0
			DPRINTK(KERN_DEBUG "%s: %s(%u), chipstatus=0x%02x\n", 
				DEVICE_NAME, __func__, dev->nMinor, chipstatus);
#endif
			switch (chipstatus & (BUS_STATUS | ERROR_STATUS)) {
			case 0x00:
				/* error active, clear only local status */
				dev->busStatus = CAN_ERROR_ACTIVE;
				DPRINTK(KERN_DEBUG "%s: %s(%u) "
					"CAN_ERROR_ACTIVE(1)\n",
					DEVICE_NAME, __func__, dev->nMinor);
				dev->wCANStatus &= ~(CAN_ERR_BUSOFF | 
							CAN_ERR_BUSHEAVY | 
							CAN_ERR_BUSLIGHT);
				break;
			case BUS_STATUS:
			case BUS_STATUS | ERROR_STATUS:
				/* bus-off */
				dev->busStatus = CAN_BUS_OFF;
				dev->wCANStatus |= CAN_ERR_BUSOFF;
				ef.can_id |= CAN_ERR_BUSOFF_NETDEV;
				DPRINTK(KERN_DEBUG "%s: %s(%u) CAN_BUS_OFF\n",
					DEVICE_NAME, __func__, dev->nMinor);
				break;
			case ERROR_STATUS:
				if (irqstatus & ERROR_PASSIV_INTERRUPT) {
					/* 
					 * either enter or leave error passive
					 * status
					 */
					if (dev->busStatus == CAN_ERROR_PASSIVE) {
						/* go back to error active */
						dev->busStatus = CAN_ERROR_ACTIVE;
						dev->wCANStatus &= ~(CAN_ERR_BUSOFF | CAN_ERR_BUSHEAVY);
						dev->wCANStatus |= CAN_ERR_BUSLIGHT;
						DPRINTK(KERN_DEBUG "%s: %s(%u) "
							"CAN_ERROR_ACTIVE(2)\n",
							DEVICE_NAME,
							__func__, dev->nMinor);
					} else {
						/* enter error passive state */
						dev->busStatus = CAN_ERROR_PASSIVE;
						dev->wCANStatus &= ~CAN_ERR_BUSOFF;
						dev->wCANStatus |=  CAN_ERR_BUSHEAVY;
						ef.can_id |= CAN_ERR_CRTL;
						ef.data[1] |= (CAN_ERR_CRTL_RX_PASSIVE | CAN_ERR_CRTL_TX_PASSIVE);
						DPRINTK(KERN_DEBUG "%s: %s(%u) "
							"CAN_ERROR_PASSIVE\n",
							DEVICE_NAME,
							__func__, dev->nMinor);
					}
				} else {
					/* warning limit reached event */
					dev->busStatus = CAN_ERROR_ACTIVE;
					dev->wCANStatus |= CAN_ERR_BUSLIGHT;
					ef.can_id |= CAN_ERR_CRTL;
					ef.data[1] |= (CAN_ERR_CRTL_RX_WARNING |
						CAN_ERR_CRTL_TX_WARNING);
					DPRINTK(KERN_DEBUG "%s: %s(%u) "
						"CAN_ERROR_ACTIVE(3)\n",
						DEVICE_NAME,
						__func__, dev->nMinor);
				}
				break;
			}

			/* simply to enter into next confition */
			irqstatus |= BUS_ERROR_INTERRUPT;

		} else 	if (irqstatus & BUS_ERROR_INTERRUPT) {
#ifdef PCAN_SJA1000_STATS
			dev_stats.int_err_count++;
#endif
			DPRINTK(KERN_DEBUG "%s: %s(%u) BUS_ERROR\n",
				DEVICE_NAME, __func__, dev->nMinor);
		}

		if (irqstatus & BUS_ERROR_INTERRUPT) {
#ifdef PCAN_SJA1000_STATS
			dev_stats.int_err_count++;
#endif
			/* 
			 * count each error signal even if it does not change
			 * any bus nor error state
			 */
			dev->dwErrorCounter++;

			/* wake up pending reads or writes */
			rwakeup++;
			wwakeup++;

			/* reset to ACTIVITY_IDLE by cyclic timer */
			dev->ucActivityState = ACTIVITY_XMIT;
		}

		/* 
		 * if any error condition occurred, send an error frame to 
		 * userspace
		 */
		if (ef.can_id) {
			struct timeval tv;

			DO_GETTIMEOFDAY(tv); /* create timestamp */

			ef.can_id |= CAN_ERR_FLAG;
			ef.can_dlc = CAN_ERR_DLC;

			SJA1000_LOCK_IRQSAVE(in_lock);

			/* put into specific data sink */
			if (pcan_xxxdev_rx(dev, &ef, &tv) > 0)
				rwakeup++;

			SJA1000_UNLOCK_IRQRESTORE(in_lock);

			/* clear for next loop */
			memset(&ef, 0, sizeof(ef));
		}

		ret = SJA1000_IRQ_HANDLED;
	}

#ifdef PCAN_SJA1000_DISABLE_IRQ
	if (int_disabled)
		sja1000_irq_enable_mask(dev, INTERRUPT_ENABLE_SETUP);
#endif

	SJA1000_UNLOCK_IRQRESTORE(sja_lock);

	if (wwakeup) {
#ifdef PCAN_SJA1000_STATS
		dev_stats.wakup_w_count++;
#endif
		/* signal I'm ready to write */
		atomic_set(&dev->DataSendReady, 1);
		//wmb();
		SJA1000_WAKEUP_WRITE();
#ifdef NETDEV_SUPPORT
		if (dev->netdev)
			netif_wake_queue(dev->netdev);
#endif
	}

	if (rwakeup) {
#ifdef PCAN_SJA1000_STATS
		dev_stats.wakup_r_count++;
#endif
		SJA1000_WAKEUP_READ();
	}

#ifdef PCAN_SJA1000_USES_ISR_LOCK
	SPIN_UNLOCK_IRQRESTORE(&dev->isr_lock);
#endif

	return ret;
}

//----------------------------------------------------------------------------
// probe for a sja1000 - use it only in reset mode!
int  sja1000_probe(struct pcandev *dev)
{
	u8  tmp;
	u8  _clkdivider= clkdivider(dev);

	DPRINTK(KERN_DEBUG "%s: %s()\n", DEVICE_NAME, __func__);

	// trace the clockdivider register to test for sja1000 / 82c200
	tmp = dev->readreg(dev, CLKDIVIDER);
	DPRINTK(KERN_DEBUG "%s: CLKDIVIDER traced (0x%02x)\n", DEVICE_NAME, tmp);
	if (tmp & 0x10)
		goto fail;

	// until here, it's either a 82c200 or a sja1000
	if (set_reset_mode(dev))
		goto fail;

	dev->writereg(dev, CLKDIVIDER, _clkdivider); // switch to PeliCAN mode
	sja1000_irq_disable(dev);                    // precautionary disable interrupts
	//wmb();
	DPRINTK(KERN_DEBUG "%s: Hopefully switched to PeliCAN mode\n", DEVICE_NAME);

	/*
	 * new 7.5: PELICAN mode takes sometimes longer: adding some delay
	 * solves the problem (many thanks to Hardi Stengelin)
	 */
	udelay(10);  // Wait until the pelican mode is activ

	tmp = dev->readreg(dev, CHIPSTATUS);
	DPRINTK(KERN_DEBUG "%s: CHIPSTATUS traced (0x%02x)\n", DEVICE_NAME, tmp);
	if ((tmp & 0x30) != 0x30)
		goto fail;

	tmp = dev->readreg(dev, INTERRUPT_STATUS);
	DPRINTK(KERN_DEBUG "%s: INTERRUPT_STATUS traced (0x%02x)\n", DEVICE_NAME, tmp);
	if (tmp & 0xfb)
		goto fail;

	tmp = dev->readreg(dev, RECEIVE_MSG_COUNTER);
	DPRINTK(KERN_DEBUG "%s: RECEIVE_MSG_COUNTER traced (0x%02x)\n", DEVICE_NAME, tmp);
	if (tmp)
		goto fail;

	DPRINTK(KERN_DEBUG "%s: %s() is OK\n", DEVICE_NAME, __func__);
	return 0;

fail:
	DPRINTK(KERN_DEBUG "%s: %s() failed\n", DEVICE_NAME, __func__);

	return -ENXIO; // no such device or address
}

//----------------------------------------------------------------------------
// calculate BTR0BTR1 for odd bitrates
//
// most parts of this code is from Arnaud Westenberg email:arnaud@wanadoo.nl
// www.home.wanadoo.nl/arnaud
//
// Set communication parameters.
// param rate baud rate in Hz
// param clock frequency of sja1000 clock in Hz
// param sjw synchronization jump width (0-3) prescaled clock cycles
// param sampl_pt sample point in % (0-100) sets (TSEG1+2)/(TSEG1+TSEG2+3) ratio
// param flags fields BTR1_SAM, OCMODE, OCPOL, OCTP, OCTN, CLK_OFF, CBP
//
static int sja1000_baud_rate(int rate, int flags)
{
	int best_error = 1000000000;
	int error;
	int best_tseg=0, best_brp=0, best_rate=0, brp=0;
	int tseg=0, tseg1=0, tseg2=0;
	int clock = CLOCK_HZ / 2;
	u16 wBTR0BTR1;
	int sjw = 0;
	int sampl_pt = 90;

	// some heuristic specials
	if (rate > ((1000000 + 500000) / 2))
		sampl_pt = 75;

	if (rate < ((12500 + 10000) / 2))
		sampl_pt = 75;

	if (rate < ((100000 + 125000) / 2))
		sjw = 1;

	// tseg even = round down, odd = round up
	for (tseg = (0 + 0 + 2) * 2; tseg <= (MAX_TSEG2 + MAX_TSEG1 + 2) * 2 + 1; tseg++)
	{
		brp = clock / ((1 + tseg / 2) * rate) + tseg % 2;
		if ((brp == 0) || (brp > 64))
			continue;

		error = rate - clock / (brp * (1 + tseg / 2));
		if (error < 0)
			error = -error;

		if (error <= best_error)
		{
			best_error = error;
			best_tseg = tseg/2;
			best_brp = brp-1;
			best_rate = clock/(brp*(1+tseg/2));
		}
	}

	if (best_error && (rate / best_error < 10))
	{
		DPRINTK(KERN_ERR "%s: bitrate %d is not possible with %d Hz clock\n", DEVICE_NAME, rate, 2 * clock);

		return 0;
	}

	tseg2 = best_tseg - (sampl_pt * (best_tseg + 1)) / 100;

	if (tseg2 < 0)
		tseg2 = 0;

	if (tseg2 > MAX_TSEG2)
		tseg2 = MAX_TSEG2;

	tseg1 = best_tseg - tseg2 - 2;

	if (tseg1 > MAX_TSEG1)
	{
		tseg1 = MAX_TSEG1;
		tseg2 = best_tseg-tseg1-2;
	}

	wBTR0BTR1 = ((sjw<<6 | best_brp) << 8) | (((flags & BTR1_SAM) != 0)<<7 | tseg2<<4 | tseg1);

	return wBTR0BTR1;
}

//----------------------------------------------------------------------------
// get BTR0BTR1 init values
u16 sja1000_bitrate(u32 dwBitRate)
{
	u16 wBTR0BTR1 = 0;;

	// get default const values
	switch (dwBitRate)
	{
	case 1000000: wBTR0BTR1 = CAN_BAUD_1M;   break;
	case  500000: wBTR0BTR1 = CAN_BAUD_500K; break;
	case  250000: wBTR0BTR1 = CAN_BAUD_250K; break;
	case  125000: wBTR0BTR1 = CAN_BAUD_125K; break;
	case  100000: wBTR0BTR1 = CAN_BAUD_100K; break;
	case   50000: wBTR0BTR1 = CAN_BAUD_50K;  break;
	case   20000: wBTR0BTR1 = CAN_BAUD_20K;  break;
	case   10000: wBTR0BTR1 = CAN_BAUD_10K;  break;
	case    5000: wBTR0BTR1 = CAN_BAUD_5K;   break;
	case       0: wBTR0BTR1 = 0;             break;

	default:
		 // calculate for exotic values
		 wBTR0BTR1 = sja1000_baud_rate(dwBitRate, 0);
	}

	DPRINTK(KERN_DEBUG "%s: %s() %u = 0x%04x\n", 
		DEVICE_NAME, __func__, dwBitRate, wBTR0BTR1);

	return wBTR0BTR1;
}
