//****************************************************************************
// Copyright (C) 2006-2007  PEAK System-Technik GmbH
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
// Contributions: Oliver Hartkopp (oliver.hartkopp@volkswagen.de)
//****************************************************************************

//****************************************************************************
//
// pcan_netdev.c - CAN network device support functions
//
// $Id: pcan_netdev.c 891 2015-07-21 08:15:14Z stephane $
//
// For CAN netdevice / socketcan specific questions please check the
// Mailing List <socketcan-users@lists.berlios.de>
// Project homepage http://developer.berlios.de/projects/socketcan
//
//****************************************************************************
//#define DEBUG
//#undef DEBUG

#include <src/pcan_common.h>
#include <linux/sched.h>
#include <linux/skbuff.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,9,0)
#include <linux/can/skb.h>
#endif
#include <src/pcan_main.h>
#include <src/pcan_fops.h>  /* pcan_open_path(), pcan_release_path() */
#include <src/pcan_fifo.h>
#include <src/pcan_netdev.h>

/*
 * if defined, fix "Kernel NULL pointer dereference" when creating "canx"
 * interface under high busload conditions (should be defined)
 */
#define BUG_FIX_NULL_NETDEV

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Functions for AF_CAN netdevice adaptation
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// AF_CAN netdevice: open device
//----------------------------------------------------------------------------
static int pcan_netdev_open(struct net_device *dev)
{
  struct pcan_priv *priv = netdev_priv(dev);
  struct pcandev  *pdev = priv->pdev;

  DPRINTK(KERN_DEBUG "%s: %s %s\n", DEVICE_NAME, __FUNCTION__, dev->name);

  if (pcan_open_path(pdev))
    return -ENODEV;

  netif_start_queue(dev);

  return 0;
}


//----------------------------------------------------------------------------
// AF_CAN netdevice: close device
//----------------------------------------------------------------------------
static int pcan_netdev_close(struct net_device *dev)
{
  struct pcan_priv *priv = netdev_priv(dev);
  struct pcandev  *pdev = priv->pdev;

  DPRINTK(KERN_DEBUG "%s: %s %s\n", DEVICE_NAME, __FUNCTION__, dev->name);

  pcan_release_path(pdev);

  netif_stop_queue(dev);

  return 0;
}


//----------------------------------------------------------------------------
// AF_CAN netdevice: get statistics for device
//----------------------------------------------------------------------------
struct net_device_stats *pcan_netdev_get_stats(struct net_device *dev)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,23)
  struct pcan_priv *priv = netdev_priv(dev);

  /* TODO: read statistics from chip */
  return &priv->stats;
#else
  return &dev->stats;
#endif
}


//----------------------------------------------------------------------------
// AF_CAN netdevice: transmit handler for device
//----------------------------------------------------------------------------
static int pcan_netdev_tx(struct sk_buff *skb, struct net_device *dev)
{
  struct pcan_priv *priv = netdev_priv(dev);
  struct pcandev  *pdev = priv->pdev;
  struct net_device_stats *stats = pcan_netdev_get_stats(dev);
  struct can_frame *cf = (struct can_frame*)skb->data;
  int err = 0;
  TPCANMsg msg;

  DPRINTK(KERN_DEBUG "%s: %s %s\n", DEVICE_NAME, __FUNCTION__, dev->name);

  /*
   * PCAN FIFO is full && not ready to write.
   * This is a theoretical problem, when anyone else
   * uses the chardev writing under load in parallel.
   */
  if (!pcan_fifo_not_full(&pdev->writeFifo) && (!atomic_read(&pdev->DataSendReady)))
  {
    stats->tx_dropped++;
    goto free_out;
  }

  // if the device is plugged out
  if (!pdev->ucPhysicallyInstalled)
    goto free_out;

  // convert SocketCAN CAN frame to PCAN FIFO compatible format
  frame2msg(cf, &msg);

  // put data into fifo (mostly stolen from pcan_fops_linux.c ioctl() code)
  err = pcan_fifo_put(&pdev->writeFifo, &msg);
  if (!err)
  {
    // enqueue into FIFO was successful

    // push a new transmission trough this xmit only if interrupt triggered push was stalled
    mb();
    if (atomic_read(&pdev->DataSendReady))
    {
      atomic_set(&pdev->DataSendReady, 0);
      mb();
      err = pdev->device_write(pdev);
      if (err)
      {
	// problems with FIFO read (pcan_fifo_get()) => no data
        atomic_set(&pdev->DataSendReady, 1);
	wake_up_interruptible(&pdev->write_queue);
      }
    }
  }

  // stop netdev queue when PCAN FIFO is full
  if (!pcan_fifo_not_full(&pdev->writeFifo)) {
    stats->tx_fifo_errors++; // just for informational purposes ...
    netif_stop_queue(dev);
  }

  stats->tx_packets++;
  stats->tx_bytes += cf->can_dlc;

  dev->trans_start = jiffies;

free_out:
  dev_kfree_skb(skb);

  return 0;
}


//----------------------------------------------------------------------------
// AF_CAN netdevice: receive function (put can_frame to netdev queue)
//----------------------------------------------------------------------------
int pcan_netdev_rx(struct pcandev *dev, struct can_frame *cf, struct timeval *tv)
{
	struct net_device *ndev = dev->netdev;
	struct net_device_stats *stats;
	struct sk_buff *skb;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,9,0)
	struct can_frame *pcf;
#endif

#ifdef BUG_FIX_NULL_NETDEV
	/*
	 * under high busload condtions, interrupts may occur before everything
	 * has been completed.
	 */
	if (!ndev)
		return 0;
#endif

	DPRINTK(KERN_DEBUG "%s: %s %s\n",
		DEVICE_NAME, __FUNCTION__, ndev->name);

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,9,0)
  skb = dev_alloc_skb(sizeof(struct can_frame));

  if (skb == NULL)
    return -ENOMEM;

  /* mandatory for Kernel 4.1+ */
  __net_timestamp(skb);

  skb->dev = ndev;
  skb->protocol = htons(ETH_P_CAN);
  skb->pkt_type = PACKET_BROADCAST;
  skb->ip_summed = CHECKSUM_UNNECESSARY;

#if 0
  /*
   * Currently the driver only supports timestamp setting at host arrival time.
   * Therefore the netdev support can used the timestamp provided by netif_rx()
   * which is set when there is no given timestamp (and when network timestamps
   * are not disabled by default in the host). So we just use the mechanics
   * like any other network device does ...
   */
  if (tv)
    #ifdef LINUX_26
    skb_set_timestamp(skb, tv);
    #else
    skb->stamp = *tv;
    #endif
#endif

  memcpy(skb_put(skb, sizeof(struct can_frame)), cf, sizeof(struct can_frame));

#else
	skb = alloc_can_skb(ndev, &pcf);
	if (!skb)
		return -ENOMEM;

	memcpy(pcf, cf, sizeof(struct can_frame));
#endif

#if LINUX_VERSION_CODE == KERNEL_VERSION(4,1,0) || \
    LINUX_VERSION_CODE == KERNEL_VERSION(4,1,1)
	/* mandatory for Kernels 4.1.[01] */
	__net_timestamp(skb);
#endif

  netif_rx(skb);

  ndev->last_rx = jiffies;

  stats = pcan_netdev_get_stats(ndev);
  stats->rx_packets++;
  stats->rx_bytes += cf->can_dlc;

  return 0;
}

#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,28)
static const struct net_device_ops pcan_netdev_ops = {
	.ndo_open	= pcan_netdev_open,
	.ndo_start_xmit	= pcan_netdev_tx,
	.ndo_stop	= pcan_netdev_close,
	.ndo_get_stats	= pcan_netdev_get_stats,
};
#endif

//----------------------------------------------------------------------------
// AF_CAN netdevice: initialize data structure
//----------------------------------------------------------------------------
void pcan_netdev_init(struct net_device *dev)
{
  /* Fill in the the fields of the device structure with AF_CAN generic values */

  if (!dev)
    return;

  /* should be superfluos as struct netdevice is zeroed at malloc time */
#if 0
  dev->change_mtu           = NULL;
  dev->set_mac_address      = NULL;
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
  dev->hard_header          = NULL;
  dev->rebuild_header       = NULL;
  dev->hard_header_cache    = NULL;
  dev->header_cache_update  = NULL;
  dev->hard_header_parse    = NULL;
#else
  dev->header_ops           = NULL;
#endif
#endif

  dev->type             = ARPHRD_CAN;
  dev->hard_header_len  = 0;
  dev->mtu              = sizeof(struct can_frame);
  dev->addr_len         = 0;
  dev->tx_queue_len     = 10;

  dev->flags            = IFF_NOARP;

#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,28)
  dev->netdev_ops       = &pcan_netdev_ops;
#else
  dev->open             = pcan_netdev_open;
  dev->stop             = pcan_netdev_close;
  dev->hard_start_xmit  = pcan_netdev_tx;
  dev->get_stats        = pcan_netdev_get_stats;
#endif
}

#ifdef PCAN_DEV_USES_ALT_NUM
static void pcan_check_ifname(char *name)
{
	/* check wanted assigned 'name' against existing device names */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
	if (__dev_get_by_name(name)) {
#else
	if (__dev_get_by_name(&init_net, name)) {
#endif
		printk(KERN_INFO "%s: assigned netdevice %s already exists\n",
				DEVICE_NAME, name);

		*name = 0; /* mark for auto assignment */
	}
}
#endif

//----------------------------------------------------------------------------
// AF_CAN netdevice: try to reassign netdev name according to user needs
//----------------------------------------------------------------------------
void pcan_netdev_create_name(char *name, struct pcandev *pdev)
{
  extern char *assign; /* module param: assignment for netdevice names */
  int minor = pdev->nMinor;
  char *pa = assign;

	DPRINTK(KERN_DEBUG "%s: %s(): minor=%d major=%d (usb major=%d) assign=\"%s\"\n", DEVICE_NAME, __FUNCTION__, minor, pdev->nMajor, USB_MAJOR, assign);

  if (!assign) /* auto assignment */
    return;

#ifdef USB_SUPPORT
#ifdef CONFIG_USB_DYNAMIC_MINORS
  if (pdev->nMajor == USB_MAJOR)
    minor += PCAN_USB_MINOR_BASE;
#endif
#endif

#ifdef PCAN_DEV_USES_ALT_NUM
	if (!strncmp(pa, "devid", 5)) {

		/* 
		 * if device defines an alternate number, use it instead of 
		 * its minor
		 */
		if (pdev->flags & PCAN_DEV_USES_ALT_NUM) {
			snprintf(name, IFNAMSIZ-1, CAN_NETDEV_NAME, 
					(int )pdev->device_alt_num);
			pcan_check_ifname(name);
			if (*name)
				return;
		}

		pa += 5;
		if (*pa++ != ',')
			return;
	}
#endif

  if (!strncmp(pa, "peak", 4)) {

    // assign=peak
    snprintf(name, IFNAMSIZ-1, CAN_NETDEV_NAME, minor); /* easy: /dev/pcanXX -> canXX */

  } else {

    // e.g. assign=pcan32:can1,pcan41:can2

    int peaknum, netnum;
    char *ptr = pa;

    while (ptr < (pa + strlen(pa))) {
      ptr = strchr(ptr, 'p'); /* search first 'p' from pcanXX */
      if (!ptr)
        return; /* no match => quit */

      if (sscanf(ptr, "pcan%d:can%d", &peaknum, &netnum) != 2) {
        printk(KERN_INFO "%s: bad parameter format in netdevice assignment.\n", DEVICE_NAME);
        return; /* bad parameter format => quit */
      }

      if (peaknum == minor) {
        snprintf(name, IFNAMSIZ-1, CAN_NETDEV_NAME, netnum);
        break; /* done */
      }
      ptr++; /* search for next 'p' */
    }
  }

#ifdef PCAN_DEV_USES_ALT_NUM
	if (*name)
		pcan_check_ifname(name);
#else
  if (name[0]) {
    /* check wanted assigned 'name' against existing device names */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
    if (__dev_get_by_name(name)) {
#else
    if (__dev_get_by_name(&init_net, name)) {
#endif
      printk(KERN_INFO "%s: netdevice name %s to be assigned exists already.\n",
             DEVICE_NAME, name);
      name[0] = 0; /* mark for auto assignment */
    }
  }
#endif
}

//----------------------------------------------------------------------------
// AF_CAN netdevice: register network device
//----------------------------------------------------------------------------
int pcan_netdev_register(struct pcandev *pdev)
{
  struct net_device *ndev;
  struct pcan_priv *priv;
  char name[IFNAMSIZ] = {0};

  pcan_netdev_create_name(name, pdev);

  if (!name[0])
    strncpy(name, CAN_NETDEV_NAME, IFNAMSIZ-1); /* use the default: autoassignment */

#ifdef LINUX_26

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,17,0)
  ndev = alloc_netdev(sizeof(struct pcan_priv), name, pcan_netdev_init);
#else
  ndev = alloc_netdev(sizeof(struct pcan_priv), name, NET_NAME_UNKNOWN,
		  pcan_netdev_init);
#endif

  if (!ndev) {
    printk(KERN_ERR "%s: out of memory\n", DEVICE_NAME);
    return 1;
  }
  priv = netdev_priv(ndev);

  if (register_netdev(ndev)) {
    printk(KERN_INFO "%s: Failed registering netdevice\n", DEVICE_NAME);
    free_netdev(ndev);
    return 1;
  }

#else

  ndev = (struct net_device*)kmalloc(sizeof(struct net_device), GFP_KERNEL);

  if (!ndev) {
    printk(KERN_ERR "%s: out of memory\n", DEVICE_NAME);
    return 1;
  }

  memset(ndev, 0, sizeof(struct net_device));

  priv = (struct pcan_priv*)kmalloc(sizeof(struct pcan_priv), GFP_KERNEL);

  if (!priv) {
    printk(KERN_ERR "%s: out of memory\n", DEVICE_NAME);
    kfree(ndev);
    return 1;
  }

  memset(priv, 0, sizeof(struct pcan_priv));
  ndev->priv = priv;

  /* fill net_device structure */
  pcan_netdev_init(ndev);

  strncpy(ndev->name, name, IFNAMSIZ-1); /* name the device */
  SET_MODULE_OWNER(ndev);

  if (register_netdev(ndev)) {
    printk(KERN_INFO "%s: Failed registering netdevice\n", DEVICE_NAME);
    kfree(priv);
    kfree(ndev);
    return 1;
  }

#endif

  // Make references between pcan device and netdevice
  priv->pdev   = pdev;
  pdev->netdev = ndev;

  printk(KERN_INFO "%s: registered netdevice %s for %s hw (major,minor %d,%d)\n",
         DEVICE_NAME, ndev->name, pdev->type, pdev->nMajor, pdev->nMinor);

  return 0;
}

//----------------------------------------------------------------------------
// AF_CAN netdevice: unregister network device
//----------------------------------------------------------------------------
int pcan_netdev_unregister(struct pcandev *pdev)
{
  struct net_device *ndev = pdev->netdev;
  struct pcan_priv *priv;

  if (!ndev)
    return 1;

  DPRINTK(KERN_DEBUG "%s: %s %s\n", DEVICE_NAME, __FUNCTION__, ndev->name);

  /* mark as unregistered to be sure not to loop here again */
  pdev->netdev = NULL;
  
  priv = netdev_priv(ndev);

  unregister_netdev(ndev);

#ifndef LINUX_26
  if (priv)
    kfree(priv);
#endif
  
  return 0;
}

//----------------------------------------------------------------------------
// End of functions for AF_CAN netdevice adaptation
//----------------------------------------------------------------------------
 
