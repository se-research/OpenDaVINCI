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
// all parts to handle the interface specific parts of PCAN-PCIExpressCard
//
// $Id: pcan_pciec.c 753 2014-01-21 10:45:03Z stephane $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <src/pcan_common.h>     // must always be the 1st include

#ifdef PCIEC_SUPPORT
#include <src/pcan_pciec.h>
#include <linux/i2c.h>
#include <linux/i2c-algo-bit.h>
#include <linux/io.h>

//****************************************************************************
// DEFINES
#define PITA_GPOUTENABLE_OFFSET 0x1a
#define PITA_GPIN_OFFSET        0x19
#define PITA_GPOUT_OFFSET       0x18

#define PCA9553_1_SLAVEADDR  (0xC4 >> 1)
#define PCA9553_LED0_OFFSET  0
#define PCA9553_LED1_OFFSET  2
#define PCA9553_DCEN_OFFSET  4
#define PCA9553_VCCEN_OFFSET 6

#define PCA9553_LOW          0
#define PCA9553_TRISTATE     1
#define PCA9553_SLOW_BLINK   2
#define PCA9553_FAST_BLINK   3

#define PCA9553_SET_MASK        0x03 // A mask to set, shifted with .._OFFSET
#define PCA9553_LS0_INITIALIZED 0x00 // initial value
#define PCA9553_LS0_NONE        0x45 // off value

//****************************************************************************
// FUNCTIONS
static inline void pita_set_scl_highz(PCAN_PCIEC_CARD *card)
{
	writeb(readb(card->gpoutenable) & ~0x01, card->gpoutenable);
}

static void pita_setscl(void *data, int state)
{
	PCAN_PCIEC_CARD *card = (PCAN_PCIEC_CARD *)data;

	/* set output scl always to 0 */
	writeb(readb(card->gpout) & ~0x01, card->gpout);

	/* control output scl with gpoutenable */
	if (state)
		writeb(readb(card->gpoutenable) & ~0x01, card->gpoutenable);
	else
		writeb(readb(card->gpoutenable) |  0x01, card->gpoutenable);
}

static int pita_getscl(void *data)
{
	PCAN_PCIEC_CARD *card = (PCAN_PCIEC_CARD *)data;

	/* set tristate */
	pita_set_scl_highz(card);

	return readb(card->gpin) & 0x01;
}

static inline void pita_set_sda_highz(PCAN_PCIEC_CARD *card)
{
	writeb(readb(card->gpoutenable) & ~0x04, card->gpoutenable);
}

static void pita_setsda(void *data, int state)
{
	PCAN_PCIEC_CARD *card = (PCAN_PCIEC_CARD *)data;

	/* set output sda always to 0 */
	writeb(readb(card->gpout) & ~0x04, card->gpout);

	/* control output sda with gpoutenable */
	if (state)
		writeb(readb(card->gpoutenable) & ~0x04, card->gpoutenable);
	else
		writeb(readb(card->gpoutenable) |  0x04, card->gpoutenable);
}

static int pita_getsda(void *data)
{
	PCAN_PCIEC_CARD *card = (PCAN_PCIEC_CARD *)data;

	/* set tristate */
	pita_set_sda_highz(card);

	return (readb(card->gpin) & 0x04) ? 1 : 0;
}

static int writeBytePCA9553(PCAN_PCIEC_CARD *card, u8 offset, u8 data)
{
	u8 buffer[2] = {offset, data};
	struct i2c_msg msg[] =  {{ PCA9553_1_SLAVEADDR, 0, 2, buffer }};
	int ret;

	ret = i2c_transfer(&card->adapter, msg, 1);

	return (ret >= 0) ? 0 : ret;
}

static int initPCA9553(PCAN_PCIEC_CARD *card)
{
	int error;

	// DPRINTK(KERN_DEBUG "%s: initPCA9553()\n", DEVICE_NAME);

	/* prescaler for frequency 0: "SLOW" = 1 Hz = "44" */
	error = writeBytePCA9553(card, 1, 44 / 1);
	if (error)
		goto fail;

	/* duty cycle 0: 50% */
	error = writeBytePCA9553(card, 2, 0x80);
	if (error)
		goto fail;

	/* prescaler for frequency 1: "FAST" = 5 Hz */
	error = writeBytePCA9553(card, 3, 44 / 5);
	if (error)
		goto fail;

	/* duty cycle 1: 50% */
	error = writeBytePCA9553(card, 4, 0x80);
	if (error)
		goto fail;

	card->PCA9553_LS0Shadow = PCA9553_LS0_INITIALIZED;

	/* switch LEDs and ... to initial state */
	error = writeBytePCA9553(card, 5, card->PCA9553_LS0Shadow);
	if (error)
		goto fail;

fail:
	return error;
}

static void deinitPCA9553(PCAN_PCIEC_CARD *card)
{
	/* DPRINTK(KERN_DEBUG "%s: deinitPCA9553()\n", DEVICE_NAME); */

	card->PCA9553_LS0Shadow = PCA9553_LS0_NONE;
	/* switch LEDs and ... to off */
	writeBytePCA9553(card, 5, card->PCA9553_LS0Shadow);
}

static void initPITAGPIO(PCAN_PCIEC_CARD *card)
{
	/* initialize GPIOs to high-Z */
	pita_set_scl_highz(card);
	pita_set_sda_highz(card);
}

/**
 * Initialize the I2C subsystem for one or more CAN channels. 
 * Only call for blinking PCIEC masters.
 * Please note that this function skips hardware initialization for other
 * channels if there is a master channel
 * for multiple CAN channels sharing I2C hardware.
 * @param card The associated card structure
 * @return The error code
 */
static int pcan_initI2C(struct pci_dev *pciDev, PCAN_PCIEC_CARD *card, 
							void *pvVirtConfigPort)
{
	int error = 0;

	DPRINTK(KERN_DEBUG "%s: pcan_initI2C()\n", DEVICE_NAME);

	/* set special card addresses */
	card->gpoutenable = pvVirtConfigPort + PITA_GPOUTENABLE_OFFSET;
	card->gpin        = pvVirtConfigPort + PITA_GPIN_OFFSET;
	card->gpout       = pvVirtConfigPort + PITA_GPOUT_OFFSET;

	/* prepare algo_bit structure since we have a bit banging interface */
	memset(&card->algo_data, 0, sizeof(card->algo_data));
	card->algo_data.data     = card;
	card->algo_data.setscl   = pita_setscl;
	card->algo_data.getscl   = pita_getscl;
	card->algo_data.setsda   = pita_setsda;
	card->algo_data.getsda   = pita_getsda;
	card->algo_data.udelay   = 10; // usec
	card->algo_data.timeout  = HZ;

	/* 
	 * create the card's special i2c_adapter structure with reference to
	 * the bit banging interface
	 */
	memset(&card->adapter, 0, sizeof(card->adapter));
	card->adapter.algo_data  = &card->algo_data;
	card->adapter.algo       = NULL;
	card->adapter.owner      = THIS_MODULE;
	strncpy(card->adapter.name, "pcan_i2c", sizeof(card->adapter.name));
	card->adapter.class      = I2C_CLASS_HWMON;
	card->adapter.retries    = 1;
	card->adapter.timeout    = 2 * HZ;
	card->adapter.dev.parent = &pciDev->dev;

	initPITAGPIO(card);

	error = i2c_bit_add_bus(&card->adapter);
	if (error) {
		printk(KERN_ERR "%s: can't register i2c channel (%d).\n", 
			DEVICE_NAME, error);
		return error;
	}

	error = initPCA9553(card);

	return error;
}

/**
 * Set VCC to external circuit on or off. Please note, setting is done in 
 * background.
 * @param card The associated PCAN-ExpressCard
 * @param On If zero, then it is switched off, else on.
 * @return 0 if the task is put successfully into background.
 */
void pcan_setVCCEN(PCAN_PCIEC_CARD *card, int On)
{
	card->VCCenable = (On) ? 1 : 0;
}

/**
 * Deinitializes and frees any associated I2C subsystem from the CAN channel. 
 * only call for blinking PCIEC masters.
 * @param card The associated PCAN-ExpressCard
 */
static void pcan_deinitI2C(PCAN_PCIEC_CARD *card)
{
	DPRINTK(KERN_DEBUG "%s: pcan_deinitI2C()\n", DEVICE_NAME);

	deinitPCA9553(card);

	/* init equals deinit */
	initPITAGPIO(card);

	i2c_del_adapter(&card->adapter);
}

/**
 * This function is called cyclic from a delayed work
 */
static void pciec_activity_scanner(struct work_struct *work)
{
	PCAN_PCIEC_CARD *card = 
		container_of(work, PCAN_PCIEC_CARD, activity_timer.work);
	struct pcandev *dev;
	int i;
	u8 tmp;

	if (!card)
		return;

	/* 
	 * DPRINTK(KERN_DEBUG "%s: pciec_activity_scanner(%p)\n",
	 *			DEVICE_NAME, card);
	 */

	tmp = card->PCA9553_LS0Shadow;

	/* move VCCEN into tmp */
	tmp &= ~(PCA9553_SET_MASK << PCA9553_VCCEN_OFFSET);
	if (!card->VCCenable)
		tmp |=   PCA9553_TRISTATE << PCA9553_VCCEN_OFFSET;

	/* first check what is to do */
	for (i = 0; i < PCIEC_CHANNELS; i++) {
		dev = card->dev[i];
		if (dev) {
			u8 state = dev->ucActivityState;
			u8 offset = (dev->port.pci.nChannel) ? 
				PCA9553_LED1_OFFSET : PCA9553_LED0_OFFSET;

			tmp &= ~(PCA9553_SET_MASK   << offset);

			switch(state) {
			case ACTIVITY_XMIT:
				tmp |= PCA9553_FAST_BLINK << offset;
				/* automatic fallback */
				dev->ucActivityState = ACTIVITY_IDLE;
				break;

			case ACTIVITY_IDLE:
				tmp |= PCA9553_SLOW_BLINK << offset;
				break;

			case ACTIVITY_INITIALIZED:
				tmp |= PCA9553_LOW << offset;
				break;

			case ACTIVITY_NONE:
			default:
				break;
			}
		}
	}

	/* check if the LS0 settings have changed, only update i2c if so */
	if (tmp != card->PCA9553_LS0Shadow) {
		card->PCA9553_LS0Shadow = tmp;
		writeBytePCA9553(card, 5, card->PCA9553_LS0Shadow);
	}

	/* restart timer */
	if (card->run_activity_timer_cyclic)
	  schedule_delayed_work(&card->activity_timer, HZ);
}

/**
 * Starts the activity scanner
 * @param card The associated card structure
 */
static void pciec_start_activity_scanner(PCAN_PCIEC_CARD *card)
{
	DPRINTK(KERN_DEBUG "%s: pciec_start_activity_scanner(%p)\n",
			DEVICE_NAME, card);

	INIT_DELAYED_WORK(&card->activity_timer, pciec_activity_scanner);
	card->run_activity_timer_cyclic = 1;
	schedule_delayed_work(&card->activity_timer, HZ);
}

/**
 * Stops the activity scanner
 * @param card The associated card structure
 */
static void pciec_stop_activity_scanner(PCAN_PCIEC_CARD *card)
{
	DPRINTK(KERN_DEBUG "%s: pciec_stop_activity_scanner(%p)\n", 
			DEVICE_NAME, card);

	card->run_activity_timer_cyclic = 0;
	cancel_delayed_work_sync(&card->activity_timer);
}

/**
 * Creates and activates a card infrastructure to handle ExpressCard's LEDs
 * @param pci_Dev The pci device structure as parent for the card's I2C device
 * @param dev The associated pcan device structure
 * @return A pointer to a card structure
 */
PCAN_PCIEC_CARD *pcan_pciec_create_card(struct pci_dev *pciDev, struct pcandev *dev)
{
	PCAN_PCIEC_CARD *card = NULL;

	DPRINTK(KERN_DEBUG "%s: pcan_pciec_create_card(%p, %d)\n", 
			DEVICE_NAME, dev, dev->port.pci.nChannel);

	if ((card = (PCAN_PCIEC_CARD *)kmalloc(sizeof(PCAN_PCIEC_CARD), 
							GFP_KERNEL)) == NULL) {
		/* TODO error check */
		return NULL;
	}

	memset(card, 0, sizeof(PCAN_PCIEC_CARD));

	dev->port.pci.card = card;
	card->dev[0] = dev;

	/* TODO error check */
	pcan_initI2C(pciDev, card, dev->port.pci.pvVirtConfigPort);

	pciec_start_activity_scanner(card);

	/* driver is loaded */
	dev->ucActivityState = ACTIVITY_INITIALIZED;

	return card;
}

/**
 * Creates and activates a card infrastructure to handle ExpressCard's LEDs
 * @param pci_Dev The pci device structure as parent for the card's I2C device
 * @param dev The associated pcan device structure
 * @return A pointer to a card structure
 */
PCAN_PCIEC_CARD *pcan_pciec_locate_card(struct pci_dev *pciDev, 
							struct pcandev *dev)
{
	PCAN_PCIEC_CARD *card = NULL;
	struct list_head *ptr;
	struct pcandev *local_dev = NULL;

	DPRINTK(KERN_DEBUG "%s: pcan_pciec_locate_card(%p, %d)\n", 
			DEVICE_NAME, dev, dev->port.pci.nChannel);

	mutex_lock(&pcan_drv.devices_lock);

	/* 
	 * it is a bit complicated to get the master channel association since
	 * the device did not know its sibling
	 */
	for (ptr = pcan_drv.devices.prev; ptr != &pcan_drv.devices; 
							ptr = ptr->prev) {
		local_dev = (struct pcandev *)ptr;

		if ((local_dev != NULL) && (local_dev != dev)  &&
		    (local_dev->port.pci.nChannel == 0) &&
		    (local_dev->port.pci.dwConfigPort == 
		    			dev->port.pci.dwConfigPort)) {
			card = local_dev->port.pci.card;
			break;
		}
	}

	mutex_unlock(&pcan_drv.devices_lock);

	if (card) {
		/* reverse lookup initialization */
		dev->port.pci.card = card;
		card->dev[dev->port.pci.nChannel] = dev;

		/* driver is loaded */
		dev->ucActivityState = ACTIVITY_INITIALIZED;
	}

	return card;
}

/**
 * Removes the card infrastructure to handle ExpressCard's LEDs, only cards will be deleted
 * @param dev The associated pcan device structure
 */
void pcan_pciec_delete_card(struct pcandev *dev)
{
	DPRINTK(KERN_DEBUG "%s: pcan_pciec_delete_card(%p)\n",
			DEVICE_NAME, dev);

	dev->ucActivityState = ACTIVITY_NONE;

	if (dev->port.pci.card) {
		if (!dev->port.pci.nChannel) {
			pciec_stop_activity_scanner(dev->port.pci.card);

			pcan_deinitI2C(dev->port.pci.card);

			kfree(dev->port.pci.card);
		} else {
			PCAN_PCIEC_CARD *card = dev->port.pci.card;

			/* remove card's association to device */
			card->dev[dev->port.pci.nChannel] = NULL;
    		}

		/* remove device's association to card */
		dev->port.pci.card = NULL;
	}
}

#endif /* PCIEC_SUPPORT */
