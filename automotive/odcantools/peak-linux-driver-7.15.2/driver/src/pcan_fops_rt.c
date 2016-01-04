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
//                Stephane Grosjean (s.grosjean@peak-system.com)    USB-PRO
//
// Contributions: Marcel Offermans (marcel.offermans@luminis.nl)
//                Arno (a.vdlaan@hccnet.nl)
//                John Privitera (JohnPrivitera@dciautomation.com)
//****************************************************************************

//****************************************************************************
//
// pcan_fops_rt.c - all file operation functions, exports only struct fops
//
// $Id: pcan_fops_rt.c $
//
//****************************************************************************

//****************************************************************************
// DEFINES

#define PCAN_OPEN_PATH_ARGS struct pcandev *dev, struct rtdm_dev_context *context
#define PCAN_RELEASE_PATH_ARGS struct pcandev *dev, struct pcanctx_rt *ctx
#define REQ_IRQ_ARG context

#if RTDM_API_VER < 6
  #define IOCTL_REQUEST_TYPE int
#else
  #define IOCTL_REQUEST_TYPE unsigned int
#endif

// TODO  wait_until_fifo_empty(dev, MAX_WAIT_UNTIL_CLOSE, ctx);
#define WAIT_UNTIL_FIFO_EMPTY()

//****************************************************************************
// CODE

static int copy_from_user_rt(rtdm_user_info_t *user_info, void *to, void *from, size_t size)
{
  if (user_info)
  {
    if (!rtdm_read_user_ok(user_info, from, size) ||
         rtdm_copy_from_user(user_info, to, from, size))
      return -EFAULT;
  }
  else
    memcpy(to, from, size);

  return 0;
}

static int copy_to_user_rt(rtdm_user_info_t *user_info, void *to, void *from, size_t size)
{
  if (user_info)
  {
    if (!rtdm_rw_user_ok(user_info, to, size) ||
         rtdm_copy_to_user(user_info, to, from, size))
      return -EFAULT;
  }
  else
    memcpy(to, from, size);

  return 0;
}

static void wait_until_fifo_empty(struct pcandev *dev, u32 mTime, struct pcanctx_rt *ctx)
{
  int fifo_not_empty;
  rtdm_lockctx_t lockctx;

  rtdm_lock_get_irqsave(&ctx->out_lock, lockctx);

  fifo_not_empty = !pcan_fifo_empty(&dev->writeFifo);
  if (fifo_not_empty)
    rtdm_event_clear(&ctx->empty_event);

  rtdm_lock_put_irqrestore(&ctx->out_lock, lockctx);

  if(fifo_not_empty)
    rtdm_event_timedwait(&ctx->empty_event, mTime * 1000, NULL);

  atomic_set(&dev->DataSendReady, 1);
}

//----------------------------------------------------------------------------
// is called when the path is opened
int pcan_open_rt(struct rtdm_dev_context *context, rtdm_user_info_t *user_info, int oflags)
{
  struct pcandev *dev;
  int err = 0;
  struct pcanctx_rt *ctx;
  int _major = MAJOR(context->device->device_id);
  int _minor = MINOR(context->device->device_id);

  DPRINTK(KERN_DEBUG "%s: pcan_open_rt(), minor = %d.\n", DEVICE_NAME, _minor);

  ctx = (struct pcanctx_rt *)context->dev_private;

  /* IPC initialisation - cannot fail with used parameters */
  rtdm_event_init(&ctx->in_event, 0);
  rtdm_event_init(&ctx->out_event, 1);
  rtdm_event_init(&ctx->empty_event, 1);
  rtdm_lock_init(&ctx->in_lock);
  rtdm_lock_init(&ctx->out_lock);
  rtdm_lock_init(&ctx->sja_lock);

  /* TBD: get the device major number from xenomai structure... */
  dev = pcan_search_dev(_major, _minor);
  if (!dev)
    return -ENODEV;

  ctx->dev = dev;
  ctx->nReadRest = 0;
  ctx->nTotalReadCount = 0;
  ctx->pcReadPointer = ctx->pcReadBuffer;
  ctx->nWriteCount = 0;
  ctx->pcWritePointer = ctx->pcWriteBuffer;

  if (dev->wType == HW_PCI)
    ctx->irq = dev->port.pci.wIrq;
  if (dev->wType == HW_ISA_SJA)
    ctx->irq = dev->port.isa.wIrq;
  if (dev->wType == HW_DONGLE_SJA || dev->wType == HW_DONGLE_SJA_EPP)
    ctx->irq = dev->port.dng.wIrq;

  err = pcan_open_path(dev, context);
  if (err)
    return err;

  /* enable IRQ interrupts */
  err = rtdm_irq_enable(&ctx->irq_handle);
  if (err)
  {
    DPRINTK(KERN_DEBUG "%s: can't enable interrupt\n", DEVICE_NAME);
    return err;
  }

  DPRINTK(KERN_DEBUG "%s: pcan_open_rt() is OK\n", DEVICE_NAME);

  return err;
}

//----------------------------------------------------------------------------
// is called when the path is closed
int pcan_close_rt(struct rtdm_dev_context *context, rtdm_user_info_t *user_info)
{
  struct pcandev *dev;
  struct pcanctx_rt *ctx;

  DPRINTK(KERN_DEBUG "%s: pcan_close_rt()\n", DEVICE_NAME);

  ctx = (struct pcanctx_rt *)context->dev_private;

  dev = ctx->dev;

  // first, prevent pending fops to act if unblocked
  dev->ucPhysicallyInstalled = 0;

  // then remove IRQ
  //rtdm_irq_disable(&ctx->irq_handle);

  pcan_release_path(dev, ctx);

  rtdm_irq_free(&ctx->irq_handle);

  // will unblock pending fops
  rtdm_event_destroy(&ctx->out_event);
  rtdm_event_destroy(&ctx->in_event);

  rtdm_event_destroy(&ctx->empty_event);

  // restore device presence
  dev->ucPhysicallyInstalled = 1;

  // as wait_until_fifo_empty is not called in RT,
  // have to fix DataSendReady here,
  // so that device can transmit again
  atomic_set(&dev->DataSendReady, 1);

  return 0;
}

//----------------------------------------------------------------------------
// is called at user ioctl() with cmd = PCAN_READ_MSG
int pcan_ioctl_read_rt(rtdm_user_info_t *user_info, struct pcanctx_rt *ctx, TPCANRdMsg *usr)
{
  int err = 0;
  TPCANRdMsg msg;

  struct pcandev *dev;
  rtdm_lockctx_t lockctx;

  DPRINTK(KERN_DEBUG "%s: pcan_ioctl_rt(PCAN_READ_MSG)\n", DEVICE_NAME);

  dev = ctx->dev;

  // if the device is plugged out
  if (!dev->ucPhysicallyInstalled)
    return -ENODEV;

  do{
	  rtdm_lock_get_irqsave(&ctx->in_lock, lockctx);

	   // get data out of fifo
	  err = pcan_fifo_get(&dev->readFifo, (void *)&msg);

	  rtdm_lock_put_irqrestore(&ctx->in_lock, lockctx);
  }while(err == -ENODATA && !(err = rtdm_event_wait(&ctx->in_event)));

  if (err){
    goto fail;
  }

  if (copy_to_user_rt(user_info, usr, &msg, sizeof(*usr)))
    err = -EFAULT;

  fail:
  return err;
}

//----------------------------------------------------------------------------
// is called at user ioctl() with cmd = PCAN_WRITE_MSG
int pcan_ioctl_write_rt(rtdm_user_info_t *user_info, struct pcanctx_rt *ctx, TPCANMsg *usr)
{
  int err = 0;
  TPCANMsg msg;
  struct pcandev *dev;
  rtdm_lockctx_t lockctx;

  DPRINTK(KERN_DEBUG "%s: pcan_ioctl_rt(PCAN_WRITE_MSG)\n", DEVICE_NAME);

  dev = ctx->dev;

  // sleep until space is available
  err = rtdm_event_wait(&ctx->out_event);
  if (err)
    goto fail;

  // if the device is plugged out
  if (!dev->ucPhysicallyInstalled)
    return -ENODEV;

  // get from user space
  if (copy_from_user_rt(user_info, &msg, usr, sizeof(msg)))
  {
    err = -EFAULT;
    goto fail;
  }

  // filter extended data if initialized to standard only
  if (!(dev->bExtended) && ((msg.MSGTYPE & MSGTYPE_EXTENDED) || (msg.ID > 2047)))
  {
    err = -EINVAL;
    goto fail;
  }

  rtdm_lock_get_irqsave(&ctx->out_lock, lockctx);

  // put data into fifo
  err = pcan_fifo_put(&dev->writeFifo, &msg);

  // if fifo not full or can device ready to send
  if (pcan_fifo_not_full(&dev->writeFifo) || atomic_read(&dev->DataSendReady))
    rtdm_event_signal(&ctx->out_event);
  rtdm_lock_put_irqrestore(&ctx->out_lock, lockctx);

  if (!err)
  {
    // push a new transmission trough ioctl() only if interrupt triggered push was stalled
    mb();
    if (atomic_read(&dev->DataSendReady))
    {
      atomic_set(&dev->DataSendReady, 0);
      mb();
      rtdm_lock_get_irqsave(&ctx->sja_lock, lockctx);
      err = dev->device_write(dev,ctx);
      rtdm_lock_put_irqrestore(&ctx->sja_lock, lockctx);
      if (err)
        atomic_set(&dev->DataSendReady, 1);
    }
    else
    {
      // DPRINTK(KERN_DEBUG "%s: pushed %d items into Fifo\n", DEVICE_NAME, dev->writeFifo.nStored);
    }
  }

  fail:
  return err;
}

//----------------------------------------------------------------------------
// is called at user ioctl() with cmd = PCAN_GET_EXT_STATUS
int pcan_ioctl_extended_status_rt(rtdm_user_info_t *user_info, struct pcanctx_rt *ctx, TPEXTENDEDSTATUS *status)
{
  int err = 0;
  struct pcandev *dev;
  TPEXTENDEDSTATUS local;

  DPRINTK(KERN_DEBUG "%s: pcan_ioctl_rt(PCAN_GET_EXT_STATUS)\n", DEVICE_NAME);

  dev = ctx->dev;
  pcan_ioctl_extended_status_common(dev, &local);

  if (copy_to_user_rt(user_info, status, &local, sizeof(local)))
  {
    err = -EFAULT;
    goto fail;
  }

  dev->wCANStatus = 0;
  dev->nLastError = 0;

  fail:
  return err;
}

//----------------------------------------------------------------------------
// is called at user ioctl() with cmd = PCAN_GET_STATUS
int pcan_ioctl_status_rt(rtdm_user_info_t *user_info, struct pcanctx_rt *ctx, TPSTATUS *status)
{
  int err = 0;
  struct pcandev *dev;
  TPSTATUS local;

  DPRINTK(KERN_DEBUG "%s: pcan_ioctl_rt(PCAN_GET_STATUS)\n", DEVICE_NAME);

  dev = ctx->dev;
  pcan_ioctl_status_common(dev, &local);

  if (copy_to_user_rt(user_info, status, &local, sizeof(local)))
  {
    err = -EFAULT;
    goto fail;
  }

  dev->wCANStatus = 0;
  dev->nLastError = 0;

  fail:
  return err;
}

//----------------------------------------------------------------------------
// is called at user ioctl() with cmd = PCAN_DIAG
int pcan_ioctl_diag_rt(rtdm_user_info_t *user_info, struct pcanctx_rt *ctx, TPDIAG *diag)
{
  int err = 0;
  struct pcandev *dev;
  TPDIAG local;

  DPRINTK(KERN_DEBUG "%s: pcan_ioctl_rt(PCAN_DIAG)\n", DEVICE_NAME);

  dev = ctx->dev;

  pcan_ioctl_diag_common(dev, &local);

  if (copy_to_user_rt(user_info, diag, &local, sizeof(local)))
    err = -EFAULT;

  return err;
}

//----------------------------------------------------------------------------
// is called at user ioctl() with cmd = PCAN_INIT
int pcan_ioctl_init_rt(rtdm_user_info_t *user_info, struct pcanctx_rt *ctx, TPCANInit *Init)
{
  int err = 0;
  TPCANInit local;
  struct pcandev *dev;
  rtdm_lockctx_t lockctx;

  DPRINTK(KERN_DEBUG "%s: pcan_ioctl_rt(PCAN_INIT)\n", DEVICE_NAME);

  dev = ctx->dev;

  if (copy_from_user_rt(user_info, &local, Init, sizeof(local)))
  {
    err = -EFAULT;
    goto fail;
  }

  // flush fifo contents
  rtdm_lock_get_irqsave(&ctx->out_lock, lockctx);
  err = pcan_fifo_reset(&dev->writeFifo);
  rtdm_lock_put_irqrestore(&ctx->out_lock, lockctx);
  if (err)
    goto fail;

  rtdm_lock_get_irqsave(&ctx->in_lock, lockctx);
  err = pcan_fifo_reset(&dev->readFifo);
  rtdm_lock_put_irqrestore(&ctx->in_lock, lockctx);
  if (err)
    goto fail;

  wait_until_fifo_empty(dev, MAX_WAIT_UNTIL_CLOSE, ctx);

  // release the device
  dev->device_release(dev);

  // init again
  err = dev->device_open(dev, local.wBTR0BTR1, local.ucCANMsgType, local.ucListenOnly);
  if (!err)
  {
    dev->wBTR0BTR1    = local.wBTR0BTR1;
    dev->ucCANMsgType = local.ucCANMsgType;
    dev->ucListenOnly = local.ucListenOnly;
  }

  fail:
  return err;
}

//----------------------------------------------------------------------------
// get BTR0BTR1 init values
int pcan_ioctl_BTR0BTR1_rt(rtdm_user_info_t *user_info, struct pcanctx_rt *ctx, TPBTR0BTR1 *BTR0BTR1)
{
  int err = 0;
  TPBTR0BTR1 local;

  DPRINTK(KERN_DEBUG "%s: pcan_ioctl_rt(PCAN_BTR0BTR1)\n", DEVICE_NAME);

  if (copy_from_user_rt(user_info, &local, BTR0BTR1, sizeof(local)))
  {
    err = -EFAULT;
    goto fail;
  }

  // this does not influence hardware settings, only BTR0BTR1 values are calculated
  local.wBTR0BTR1 = sja1000_bitrate(local.dwBitRate);

  if (!local.wBTR0BTR1)
  {
    err = -EFAULT;
    goto fail;
  }

  if (copy_to_user_rt(user_info, BTR0BTR1, &local, sizeof(*BTR0BTR1)))
    err = -EFAULT;

  fail:
  return err;
}

//----------------------------------------------------------------------------
// add a message filter_element into the filter chain or delete all filter_elements
int pcan_ioctl_msg_filter_rt(rtdm_user_info_t *user_info, struct pcanctx_rt *ctx, TPMSGFILTER *filter)
{
  TPMSGFILTER local_filter;
  struct pcandev *dev;

  DPRINTK(KERN_DEBUG "%s: pcan_ioctl_rt(PCAN_MSG_FILTER)\n", DEVICE_NAME);

  dev = ctx->dev;

  // filter == NULL -> delete the filter_elements in the chain
  if (!filter)
  {
    pcan_delete_filter_all(dev->filter);
    return 0;
  }

  if (copy_from_user_rt(user_info, &local_filter, filter, sizeof(local_filter)))
    return -EFAULT;

  return pcan_add_filter(dev->filter, local_filter.FromID, local_filter.ToID, local_filter.MSGTYPE);
}

//----------------------------------------------------------------------------
// is called at user ioctl() call
int pcan_ioctl_rt(struct rtdm_dev_context *context, rtdm_user_info_t *user_info, IOCTL_REQUEST_TYPE request, void *arg)
{
  int err;
  struct pcanctx_rt *ctx;
  struct pcandev *dev;

  ctx = (struct pcanctx_rt *)context->dev_private;
  dev = ctx->dev;

  // if the device is plugged out
  if (!dev->ucPhysicallyInstalled)
    return -ENODEV;

  switch(request)
  {
    case PCAN_READ_MSG:
      err = pcan_ioctl_read_rt(user_info, ctx, (TPCANRdMsg *)arg); // support blocking and nonblocking IO
      break;
    case PCAN_WRITE_MSG:
      err = pcan_ioctl_write_rt(user_info, ctx, (TPCANMsg *)arg);  // support blocking and nonblocking IO
      break;
    case PCAN_GET_EXT_STATUS:
      err = pcan_ioctl_extended_status_rt(user_info, ctx, (TPEXTENDEDSTATUS *)arg);
     break;
    case PCAN_GET_STATUS:
      err = pcan_ioctl_status_rt(user_info, ctx, (TPSTATUS *)arg);
      break;
    case PCAN_DIAG:
      err = pcan_ioctl_diag_rt(user_info, ctx, (TPDIAG *)arg);
      break;
    case PCAN_INIT:
      err = pcan_ioctl_init_rt(user_info, ctx, (TPCANInit *)arg);
      break;
    case PCAN_BTR0BTR1:
      err = pcan_ioctl_BTR0BTR1_rt(user_info, ctx, (TPBTR0BTR1 *)arg);
      break;
    case PCAN_MSG_FILTER:
      err = pcan_ioctl_msg_filter_rt(user_info, ctx, (TPMSGFILTER *)arg);
      break;

    default:
      DPRINTK(KERN_DEBUG "%s: pcan_ioctl_rt(%d)\n", DEVICE_NAME, request);
      err = -ENOTTY;
      break;
  }

  DPRINTK(KERN_DEBUG "%s: pcan_ioctl()_rt = %d\n", DEVICE_NAME, err);
  return err;
}

//****************************************************************************
// GLOBALS

//----------------------------------------------------------------------------
// this structure is used in init_module(void)
struct rtdm_device pcandev_rt =
{
  struct_version:     RTDM_DEVICE_STRUCT_VER,

  device_flags:       RTDM_NAMED_DEVICE,
  context_size:       sizeof(struct pcanctx_rt),
  device_name:        "",

  open_rt:            NULL,
  open_nrt:           pcan_open_rt,

  ops: {
    close_rt:         NULL,
    close_nrt:        pcan_close_rt,

    ioctl_rt:         pcan_ioctl_rt,
    ioctl_nrt:        pcan_ioctl_rt,

    read_rt:          NULL,
    read_nrt:         NULL,

    write_rt:         NULL,
    write_nrt:        NULL,

    recvmsg_rt:       NULL,
    recvmsg_nrt:      NULL,

    sendmsg_rt:       NULL,
    sendmsg_nrt:      NULL,
  },

  device_class:       RTDM_CLASS_CAN,
  driver_name:        "pcan_driver",
  provider_name:      "PEAK System-Technik GmbH",
  proc_name:          pcandev_rt.device_name,
};

// end of file

