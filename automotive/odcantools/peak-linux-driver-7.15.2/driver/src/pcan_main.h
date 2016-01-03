#ifndef __PCAN_MAIN_H__
#define __PCAN_MAIN_H__

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
//                Stephane Grosjean (s.grosjean@peak-system.com)    USB-PRO
//
// Contributions: Marcel Offermans (marcel.offermans@luminis.nl)
//                Philipp Baer (philipp.baer@informatik.uni-ulm.de)
//                Marc Sowen (Marc.Sowen@ibeo-as.com)
//****************************************************************************

//****************************************************************************
//
// pcan_main.h - global defines to include in all files this module is made of
//
// $Id: pcan_main.h 839 2015-03-13 10:44:53Z stephane $
//
//****************************************************************************

//----------------------------------------------------------------------------
// INCLUDES
#include <src/pcan_common.h>

#include <linux/types.h>
#include <linux/list.h>
#include <linux/wait.h>
#include <linux/interrupt.h>
#include <linux/time.h>

#ifdef LINUX_26
#include <linux/device.h>
#endif

#ifdef PCI_SUPPORT
#include <linux/pci.h>
#endif

#include <linux/spinlock.h>

#include <asm/atomic.h>

#ifdef PARPORT_SUBSYSTEM
#include <linux/parport.h>
#endif

#ifdef PCCARD_SUPPORT
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,37)
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
#include <pcmcia/cs_types.h>
#endif
#include <pcmcia/cs.h>
#endif
#include <pcmcia/cistpl.h>
#include <pcmcia/ds.h>
#endif

#ifdef PCIEC_SUPPORT
#include <linux/i2c.h>
#include <linux/i2c-algo-bit.h>
#endif

#ifdef USB_SUPPORT
#include <linux/usb.h>

#if LINUX_VERSION_CODE > KERNEL_VERSION(2,4,19)
typedef struct urb urb_t, *purb_t;
#endif

#define PCAN_USB_MINOR_BASE            32    // USB dev minors starting point

#endif

#ifndef NO_RT
#include <rtdm/rtdm_driver.h>
struct pcanctx_rt;
#endif

/* PF_CAN is part of the Linux Mainline Kernel since v2.6.25 */
/* For older Kernels the PCAN driver includes the needed */
/* defines from private files src/can.h and src/error.h  */

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25)
#include <linux/can.h>
#include <linux/can/error.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#else /* before 2.6.25 pcan netdev contains private includes */
#include <src/can.h>
#include <src/error.h>
#define ARPHRD_CAN	280	/* to be moved to include/linux/if_arp.h */
#define ETH_P_CAN	0x000C	/* to be moved to include/linux/if_ether.h */
#endif

/* fix overlap in namespace between socketcan can/error.h and pcan.h */
#define CAN_ERR_BUSOFF_NETDEV CAN_ERR_BUSOFF
#undef CAN_ERR_BUSOFF

#include <pcan.h>

//----------------------------------------------------------------------------
// DEFINES
#define CHANNEL_SINGLE 0                                   // this is a single channel device
#define CHANNEL_MASTER 1                                   // multi channel device, this device is master
#define CHANNEL_SLAVE  2                                   // multi channel device, this is slave

#define READBUFFER_SIZE      80                            // buffers used in read and write call
#define WRITEBUFFER_SIZE     80
#define PCAN_MAJOR            0                            // use dynamic major allocation, else use 91
#define READ_MESSAGE_COUNT  500                            // max read message count
#define WRITE_MESSAGE_COUNT  50                            // max write message count

// parameter wBTR0BTR1
// bitrate codes of BTR0/BTR1 registers
#define CAN_BAUD_1M     0x0014                             //   1 MBit/s
#define CAN_BAUD_500K   0x001C                             // 500 kBit/s
#define CAN_BAUD_250K   0x011C                             // 250 kBit/s
#define CAN_BAUD_125K   0x031C                             // 125 kBit/s
#define CAN_BAUD_100K   0x432F                             // 100 kBit/s
#define CAN_BAUD_50K    0x472F                             //  50 kBit/s
#define CAN_BAUD_20K    0x532F                             //  20 kBit/s
#define CAN_BAUD_10K    0x672F                             //  10 kBit/s
#define CAN_BAUD_5K     0x7F7F                             //   5 kBit/s

// Activity states
#define ACTIVITY_NONE        0          // LED off           - set when the channel is created or deleted
#define ACTIVITY_INITIALIZED 1          // LED on            - set when the channel is initialized
#define ACTIVITY_IDLE        2          // LED slow blinking - set when the channel is ready to receive or transmit
#define ACTIVITY_XMIT        3          // LED fast blinking - set when the channel has received or transmitted

#define CAN_ERROR_ACTIVE     0          // CAN-Bus error states for busStatus - initial and normal state
#define CAN_ERROR_PASSIVE    1          // receive only state
#define CAN_BUS_OFF          2          // switched off from Bus

typedef struct chn_props                // this structure holds various channel properties
{
	u8 ucExternalClock : 1;               // this device is supplied with a external clock
	u8 ucMasterDevice  : 2;               // this channel is a clock master, slave, single
} CHN_PROPS;

// a helper for fast conversion between 'SJA1000' data ordering and host data order
typedef union
{
	u8  uc[4];
	u32 ul;
} ULCONV;

typedef union
{
	u8  uc[2];
	u16 uw;
} UWCONV;


typedef struct
{
	u16        wStepSize;                                    // size of bytes to step to next entry
	u16        wCopySize;                                    // size of bytes to copy
	void       *bufferBegin;                                 // points to first element
	void       *bufferEnd;                                   // points to the last element
	u32        nCount;                                       // max count of elements in fifo
	u32        nStored;                                      // count of currently received and stored messages
	u32        dwTotal;                                      // received messages
	void       *r;                                           // points to the next Msg to read into the read buffer
	void       *w;                                           // points to the next Msg to write into read buffer
	spinlock_t lock;                                         // mutual exclusion lock
} FIFO_MANAGER;

#ifdef PCIEC_SUPPORT
#define PCIEC_CHANNELS 2                                   // maximum PCAN-PCIExpressCard channel number

typedef struct
{
	void       *gpoutenable;                                 // virtual adresses for bit-banging interface
	void       *gpin;
	void       *gpout;
	struct     pcandev *dev[PCIEC_CHANNELS];                 // point to associated channels
	struct     i2c_adapter adapter;                          // associated i2c adapter for PCAN-Expresscard
	struct     i2c_algo_bit_data algo_data;                  // we have a bit banging interface with PCAN-Expresscard
	u8         VCCenable;                                    // reflection of VCCEN
	u8         PCA9553_LS0Shadow;                            // Shadow register to hold the state of the LEDs
	int        run_activity_timer_cyclic;                    // a flag to synchronize stop conditions
	struct     delayed_work activity_timer;                  // to scan for activity, set the time
} PCAN_PCIEC_CARD;
#endif

struct pcan_msi {
	int	msi_requested;
	int	msi_assigned;
};

typedef struct
{
	u32  dwPort;                                             // the port of the transport layer
	u32  dwConfigPort;                                       // the confiuration port, PCI only
	void *pvVirtPort;                                        // virtual address of port
	void *pvVirtConfigPort;                                  // only PCI, the virtual address of the config port
	u16  wIrq;                                               // the associated irq level
	int  nChannel;                                           // associated channel of the card - channel #0 is special
	struct pci_dev *pciDev;                                  // remember the hosting PCI card
	struct pcan_msi msi;
#ifdef PCIEC_SUPPORT
	PCAN_PCIEC_CARD *card;                                   // point to a card structure
#endif
} PCI_PORT;

typedef struct
{
	u32  dwPort;                                             // the port of the transport layer
	u16  wIrq;                                               // the associated irq
#ifdef PARPORT_SUBSYSTEM
	struct pardevice *pardev;                                // points to the associated parallel port (PARPORT subsytem)
#endif
	u16  wEcr;                                               // ECR register in case of EPP
	u8   ucOldDataContent;                                   // the overwritten contents of the port registers
	u8   ucOldControlContent;
	u8   ucOldECRContent;
	spinlock_t lock;                                         // a helper to manage interfering access to chip registers
} DONGLE_PORT;

#ifdef NO_RT
typedef struct
{
	struct list_head item;                                   // link anchor for a item with the same irq level
	struct pcandev   *dev;                                   // points to the device to be handled with the same irq level
} SAME_IRQ_ITEM;

typedef struct
{
	struct list_head same_irq_items;                         // base of list of SAME_IRQ_ITEM's
	u16  same_irq_count;                                     // count of devices with the same irq level to handle
	u16  same_irq_active;                                    // count of armed (active) irqs
} SAME_IRQ_LIST;
#endif

typedef struct
{
	u32  dwPort;                                             // the port of the transport layer
	u16  wIrq;                                               // the associated irq level
#ifdef NO_RT
	SAME_IRQ_ITEM same;                                      // each ISA_PORT should belong to one SAME_IRQ_LIST
	SAME_IRQ_LIST anchor;                                    // the anchor for one irq level (not used with every ISA_PORT)
	SAME_IRQ_LIST *my_anchor;                                // points to the list of items for the same irq (SAME_IRQ_LIST)
#endif
} ISA_PORT;

#ifdef PCCARD_SUPPORT
struct pcan_pccard;                    // forward declaration to ease inclusion
typedef struct
{
	u32  dwPort;                        // the port of the transport layer
	u16  wIrq;                          // the associated irq
	int  nChannel;                      // associated channel of the card
	struct pcan_pccard *card;           // points to the associated pccard
} PCCARD_PORT;
#endif

#ifdef USB_SUPPORT

typedef struct
{
	u64      ullCumulatedTicks;         // sum of all ticks
	u64      ullOldCumulatedTicks;      // old ...
	struct   timeval StartTime;         // time of first receive
	u16      wStartTicks;               // ticks at first init
	u16      wLastTickValue;            // Last aquired tick count
	u16      wOldLastTickValue;         // old ...
	u8       ucLastTickValue;           // the same for byte tick counts
} PCAN_USB_TIME;

typedef struct
{
	u8  ucNumber;                       // number (or address) of endpoint
	u16 wDataSz;                        // supported max data transfer length
} PCAN_ENDPOINT;

#define PCAN_DEV_USES_ALT_NUM	0x00000001

struct pcan_usb_interface;
typedef struct pcan_usb_port
{
	struct pcan_usb_interface *usb_if;

	int  dev_ctrl_index;                             // in case os multi-CAN 
	                                                 // controller for a device 
	                                                 // (PCAN-USB-PRO for ex)
	u8       ucHardcodedDevNr;

	u32      dwTelegramCount;                        // counter for telegrams

	PCAN_USB_TIME usb_time;                          // PCAN_USB_TIME

	struct urb write_data;                           // pointer to write data urb
	int      write_packet_size;                      // packet write buffer size
	int      write_buffer_size;
	u8       *write_buffer_addr;                     // buffer for to write data
	                                                 // (OUT)
	PCAN_ENDPOINT pipe_write;

	uint32_t	state;

} USB_PORT;
#endif // USB_SUPPORT

typedef struct pcandev
{
	struct list_head list;                                   // link anchor for list of devices
	int  nOpenPaths;                                         // number of open paths linked to the device
	u16  wInitStep;                                          // device specific init state
	int  nMajor;                                             // the device major (USB devices have their own major USB_MAJOR!!!)
	int  nMinor;                                             // the associated minor
	char *type;                                              // the literal type of the device, info only
	u16  wType;                                              // (number type) to distinguish sp and epp

#ifdef PCAN_DEV_USES_ALT_NUM
	u32	flags;
	u32	device_alt_num;
	struct device *mapped_dev;
#endif

#ifdef NETDEV_SUPPORT
	struct net_device *netdev;                               // reference to net device for AF_CAN
#endif

	union
	{
	  DONGLE_PORT dng;                                       // private data of the various ports
	  ISA_PORT    isa;
	  PCI_PORT    pci;
#ifdef PCCARD_SUPPORT
	  PCCARD_PORT pccard;
#endif
#ifdef USB_SUPPORT
	  USB_PORT    usb;
#endif
	} port;

	struct chn_props props;                                  // various channel properties

	u8   (*readreg)(struct pcandev *dev, u8 port);           // read a register
	void (*writereg)(struct pcandev *dev, u8 port, u8 data); // write a register
	int  (*cleanup)(struct pcandev *dev);                    // cleanup the interface
	int  (*open)(struct pcandev *dev);                       // called at open of a path
	int  (*release)(struct pcandev *dev);                    // called at release of a path
#ifndef NO_RT
	int  (*req_irq)(struct rtdm_dev_context *context);       // install the interrupt handler
#else
	int  (*req_irq)(struct pcandev *dev);                    // install the interrupt handler
#endif
	void (*free_irq)(struct pcandev *dev);                   // release the interrupt

	int  (*device_open)(struct pcandev *dev, u16 btr0btr1, u8 bExtended, u8 bListenOnly); // open the device itself
	void (*device_release)(struct pcandev *dev);             // release the device itself
#ifndef NO_RT
	int  (*device_write)(struct pcandev *dev, struct pcanctx_rt *ctx);               // write the device
#else
	int  (*device_write)(struct pcandev *dev);               // write the device
#endif

	int  (*device_params)(struct pcandev *dev, TPEXTRAPARAMS *params); // a generalized interface to set
	                                                         // or get special parameters from the device

	wait_queue_head_t read_queue;                            // read process wait queue anchor
	wait_queue_head_t write_queue;                           // write process wait queue anchor

	u16  bus_load;
	u8   bExtended;                                          // if 0, no extended frames are accepted
	int  nLastError;                                         // last error written
	int  busStatus;                                          // follows error status of CAN-Bus
	u32  dwErrorCounter;                                     // counts all fatal errors
	u32  dwInterruptCounter;                                 // counts all interrupts
	u16  wCANStatus;                                         // status of CAN chip
	u16  wBTR0BTR1;                                          // the persistent storage for BTR0 and BTR1
	u8   ucCANMsgType;                                       // the persistent storage for 11 or 29 bit identifier
	u8   ucListenOnly;                                       // the persistent storage for listen-only mode
	u8   ucPhysicallyInstalled;                              // the device is PhysicallyInstalled
	u8   ucActivityState;                                    // follow the state of a channel activity
	atomic_t DataSendReady;                                  // !=0 if all data are send

	FIFO_MANAGER readFifo;                                   // manages the read fifo
	FIFO_MANAGER writeFifo;                                  // manages the write fifo
	TPCANRdMsg   rMsg[READ_MESSAGE_COUNT];                   // all read messages
	TPCANMsg     wMsg[WRITE_MESSAGE_COUNT];                  // all write messages
	void *filter;                                            // a ID filter - currently associated to device
	spinlock_t wlock;                                        // mutual exclusion lock for write invocation
	spinlock_t isr_lock;                                     // in isr

	uint32_t	tx_error_counter;	/* Tx errors counter */
	uint32_t	rx_error_counter;	/* Rx errors counter */
} PCANDEV;

#ifdef USB_SUPPORT
struct pcan_usb_interface
{
	struct usb_device *usb_dev;                      // the origin pointer to my
	                                                 // USB device from kernel
	                                                 // and sizes
	char *	adapter_name;
	struct usb_interface *usb_intf;

	uint32_t              state;
	int	cm_ignore_count;	/* nb of CM to ignore before handling */

	u8     ucHardcodedDevNr;
	u32    dwSerialNumber;                           // Serial number of device
	u8     ucRevision;                               // the revision number of 

	wait_queue_head_t  usb_wait_queue;               // wait queue for usb 
	                                                 // transactions concerning 
	                                                 // this device
	atomic_t active_urbs;                            // note all active urbs for
	                                                 // this device

	struct urb   urb_cmd_async;                      // async. cmd URB
	atomic_t     cmd_async_complete;                 // flag set when async cmd 
	struct urb   urb_cmd_sync;                       // sync cmd URB
	atomic_t     cmd_sync_complete;                  // flag set when sync cmd 
	                                                 // finished

	struct urb read_data;                            // pointer to read data urb
	int        read_packet_size;                     // packet read buffer size
	int        read_buffer_size;
	uint8_t *  read_buffer_addr[2];                  // read data transfer buffer
	                                                 // for toggle
	uint8_t *	cout_baddr;		/* command buffer address */
	int		cout_bsize;		/* command buffer size */

	/* USB pipes to/from CAN controller(s) */
	PCAN_ENDPOINT pipe_cmd_in;
	PCAN_ENDPOINT pipe_cmd_out;
	PCAN_ENDPOINT pipe_read;

	int  (*device_init)(struct pcan_usb_interface *);

	int  (*device_get_snr)(struct pcan_usb_interface *, uint32_t *);
	int  (*device_msg_decode)(struct pcan_usb_interface *, uint8_t *, int );
	void (*device_free)(struct pcan_usb_interface *);

	int  (*device_ctrl_init)(struct pcandev *dev);
	void (*device_ctrl_cleanup)(struct pcandev *dev);
	int  (*device_ctrl_open)(struct pcandev *dev, uint16_t, uint8_t );
	int  (*device_ctrl_close)(struct pcandev *dev);
	int  (*device_ctrl_set_bus_on)(struct pcandev *dev);
	int  (*device_ctrl_set_bus_off)(struct pcandev *dev);
	int  (*device_ctrl_set_dnr)(struct pcandev *dev, uint32_t);
	int  (*device_ctrl_get_dnr)(struct pcandev *dev, uint32_t *);
	int  (*device_ctrl_msg_encode)(struct pcandev *dev, uint8_t *, int *);

	uint32_t       rx0_sync;                         // 1: should sync tv vs. ts
	struct timeval rx0_tv;                           // time of the 1st rx frame
	uint32_t       rx0_ts;                           // timestamp of 1st rx frame

	/* fields to compute time from usb adapter to driver: */
	/* time of usb transmission = (time of the reception of a response */
	/*                           - time of the sending of a request) / 2 */
	struct timeval tv_request;
	struct timeval tv_response;
	uint32_t       rtt;

	struct timer_list calibration_timer;

	int    frag_rec_offset;

	int    dev_ctrl_count;                           // number of CAN ctrlrs
	int    dev_opened_count;

	struct pcandev dev[1];                           // the real devices for each
                                                    // CAN controller
};
#endif

#ifndef NO_RT
struct pcanctx_rt
{
	struct pcandev  *dev;                                   // pointer to related device
	u8     pcReadBuffer[READBUFFER_SIZE];                    // buffer used in read() call
	u8     *pcReadPointer;                                   // points into current read data rest
	int    nReadRest;                                        // rest of data left to read
	int    nTotalReadCount;                                  // for test only
	u8     pcWriteBuffer[WRITEBUFFER_SIZE];                  // buffer used in write() call
	u8     *pcWritePointer;                                  // work pointer into buffer
	int    nWriteCount;

	rtdm_irq_t        irq_handle;
	rtdm_event_t      in_event;
	rtdm_event_t      out_event;
	rtdm_event_t      empty_event;
	rtdm_lock_t      in_lock;                               // read mutual exclusion lock
	rtdm_lock_t      out_lock;                              // write mutual exclusion lock
	rtdm_lock_t      sja_lock;                              // sja mutual exclusion lock
	unsigned int      irq;                                   // the associated irq level
};
#else
typedef struct fileobj
{
	struct pcandev *dev;                                     // pointer to related device
	u8     pcReadBuffer[READBUFFER_SIZE];                    // buffer used in read() call
	u8     *pcReadPointer;                                   // points into current read data rest
	int    nReadRest;                                        // rest of data left to read
	int    nTotalReadCount;                                  // for test only
	u8     pcWriteBuffer[WRITEBUFFER_SIZE];                  // buffer used in write() call
	u8     *pcWritePointer;                                  // work pointer into buffer
	int    nWriteCount;                                      // count of written data bytes
} FILEOBJ;
#endif

typedef struct driverobj
{
	int nMajor;                                              // the major number of Pcan interfaces
	u16 wDeviceCount;                                        // count of found devices
	u16 wInitStep;                                           // driver specific init state
	struct timeval sInitTime;                                // time in usec when init was called
	struct list_head devices;                                // base of list of devices
	struct mutex devices_lock;	/* mutex to access devices list */
	u8  *szVersionString;                                    // pointer to the driver version string

#ifdef PCCARD_SUPPORT
#ifndef LINUX_24
	struct pcmcia_driver pccarddrv;                         // pccard driver structure
#endif
#endif

#ifdef USB_SUPPORT
	struct usb_driver usbdrv;                                // usb driver structure
#endif

#ifdef UDEV_SUPPORT

#ifdef PCI_SUPPORT
	struct pci_driver pci_drv;                               // pci driver structure
#endif

#ifdef ISA_SUPPORT
	struct device_driver legacy_driver_isa;                  // legacy platform driver
#endif

#ifdef DONGLE_SUPPORT
	struct device_driver legacy_driver_dongle;               // legacy platform driver
#endif

	struct class *class;                                     // the associated class of pcan devices
#endif // UDEV_SUPPORT
} DRIVEROBJ;

#ifndef NO_RT
typedef struct rt_device
{
	struct list_head list;
	struct rtdm_device *device;
} RT_DEVICE;
#endif

//----------------------------------------------------------------------------
// the global driver object
extern struct driverobj pcan_drv;
#ifndef NO_RT
extern struct list_head device_list;
#endif

//----------------------------------------------------------------------------
// exported functions - not to Linux kernel!
u32  get_mtime(void);                                           // request time in msec, fast
void get_relative_time(struct timeval *tv, struct timeval *tr); // request time from drivers start
void timeval2pcan(struct timeval *tv, u32 *msecs, u16 *usecs);  // convert to pcan time

void pcan_add_device_in_list(struct pcandev *dev);
void pcan_del_device_from_list(struct pcandev *dev);
int pcan_is_device_in_list(struct pcandev *dev);

void pcan_soft_init(struct pcandev *dev, char *szType, u16 wType);
void buffer_dump(u8 *pucBuffer, u16 wLineCount);
void dump_mem(char *prompt, void *p, int l);
void frame2msg(struct can_frame *cf, TPCANMsg *msg);
void msg2frame(struct can_frame *cf, TPCANMsg *msg);
int  pcan_chardev_rx_ex(struct pcandev *dev, struct can_frame *cf,
			struct timeval *tv, u32 flags);

static inline int pcan_chardev_rx(struct pcandev *dev, struct can_frame *cf,
		struct timeval *tv)
{
	return pcan_chardev_rx_ex(dev, cf, tv, 0);
}

void dev_unregister(void);
#ifdef NO_RT
void pcan_device_node_create(struct pcandev *dev);
void pcan_device_node_destroy(struct pcandev *dev);
#endif

void remove_dev_list(void);

int pcan_sysfs_add_attr(struct device *dev, struct attribute *attrs);
int pcan_sysfs_add_attrs(struct device *dev, struct attribute **attrs);
void pcan_sysfs_del_attr(struct device *dev, struct attribute *attrs);
void pcan_sysfs_del_attrs(struct device *dev, struct attribute **attrs);

#endif // __PCAN_MAIN_H__
