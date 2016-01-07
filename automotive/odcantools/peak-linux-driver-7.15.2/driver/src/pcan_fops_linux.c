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
// Maintainer(s): Stephane Grosjean (s.grosjean@peak-system.com)
//
// Major contributions by:
//                Klaus Hitschler (klaus.hitschler@gmx.de)
//                Edouard Tisserant (edouard.tisserant@lolitech.fr) XENOMAI
//                Laurent Bessard   (laurent.bessard@lolitech.fr)   XENOMAI
//                Oliver Hartkopp   (oliver.hartkopp@volkswagen.de) socketCAN
//
// Contributions: Marcel Offermans (marcel.offermans@luminis.nl)
//                Arno (a.vdlaan@hccnet.nl)
//                John Privitera (JohnPrivitera@dciautomation.com)
//****************************************************************************

/*****************************************************************************
 *
 * pcan_fops_linux.c - all file operation functions, exports only struct fops
 *
 * $Id: pcan_fops_linux.c $
 *
 *****************************************************************************/

#define PCAN_OPEN_PATH_ARGS		struct pcandev *dev
#define PCAN_RELEASE_PATH_ARGS		struct pcandev *dev
#define REQ_IRQ_ARG dev
#define WAIT_UNTIL_FIFO_EMPTY()		wait_until_fifo_empty(dev, \
							MAX_WAIT_UNTIL_CLOSE)

/*
 * wait until write fifo is empty, max time in msec
 */
static void wait_until_fifo_empty(struct pcandev *dev, u32 mTime)
{
	u32 dwStart = get_mtime();

	/* not need to wait for anything if device not plugged! */
	if (!dev->ucPhysicallyInstalled)
		return;

	while (!atomic_read(&dev->DataSendReady) &&
				((get_mtime() - dwStart) < mTime))
		schedule();

	/* force it */
	atomic_set(&dev->DataSendReady, 1);
}

/*
 * is called when the path is opened
 */
static int pcan_open(struct inode *inode, struct file *filep)
{
	struct pcandev *dev;
	int err = 0;
	struct fileobj *fobj = (struct fileobj *)NULL;
	int _minor = minor(inode->i_rdev);
	int _major = MAJOR(inode->i_rdev);

	DPRINTK(KERN_DEBUG "%s: pcan_open(), major/minor = %d/%d.\n",
			               DEVICE_NAME, _major, _minor);

	dev = pcan_search_dev(_major, _minor);
	if (!dev)
		return -ENODEV;

	/* create file object */
	fobj = kmalloc(sizeof(struct fileobj), GFP_KERNEL);
	if (!fobj) {
		DPRINTK(KERN_DEBUG "%s: can't allocate kernel memory!\n",
								DEVICE_NAME);
		return -ENOMEM;
	}

	/* fill file object and init read and write method buffers */
	fobj->dev = dev;
	if (filep->f_mode & FMODE_READ) {
		fobj->nReadRest = 0;
		fobj->nTotalReadCount = 0;
		fobj->pcReadPointer = fobj->pcReadBuffer;
	}

	if (filep->f_mode & FMODE_WRITE) {
		fobj->nWriteCount = 0;
		fobj->pcWritePointer = fobj->pcWriteBuffer;
	}

	filep->private_data = (void *)fobj;

	err = pcan_open_path(dev);

	if (err && fobj) /* oops */
		kfree(fobj);

	return err;
}

static int pcan_release(struct inode *inode, struct file *filep)
{
	struct fileobj *fobj = (struct fileobj *)filep->private_data;

	DPRINTK(KERN_DEBUG "%s: pcan_release()\n", DEVICE_NAME);

	/* free the associated irq and allocated memory */
	if (fobj) {
		if (fobj->dev)
			pcan_release_path(fobj->dev);

		kfree(fobj);
	}
	return 0;
}

/*
 * is called at user ioctl() with cmd = PCAN_READ_MSG
 */
static int pcan_ioctl_read(struct file *filep, struct pcandev *dev,
								TPCANRdMsg *usr)
{
	int err = 0;
	TPCANRdMsg msg;

	//DPRINTK(KERN_DEBUG "%s: pcan_ioctl(PCAN_READ_MSG)\n", DEVICE_NAME);

	/* support nonblocking read if requested */
	if ((filep->f_flags & O_NONBLOCK) && (pcan_fifo_empty(&dev->readFifo)))
		return -EAGAIN;

	/* sleep until data are available */
	err = wait_event_interruptible(dev->read_queue,
					!dev->ucPhysicallyInstalled ||
					!pcan_fifo_empty(&dev->readFifo));
	if (err)
		goto fail;

	/* if the device is plugged out */
	if (!dev->ucPhysicallyInstalled)
		return -ENODEV;

	/* get data out of fifo */
	err = pcan_fifo_get(&dev->readFifo, (void *)&msg);
	if (err)
		goto fail;

	if (copy_to_user(usr, &msg, sizeof(*usr)))
		err = -EFAULT;

fail:
	return err;
}

/*
 * is called at user ioctl() with cmd = PCAN_WRITE_MSG
 */
static int pcan_ioctl_write(struct file *filep, struct pcandev *dev, TPCANMsg *usr)
{
	int err = 0;
	TPCANMsg msg;

	DPRINTK(KERN_DEBUG "%s: pcan_ioctl(PCAN_WRITE_MSG)\n", DEVICE_NAME);

	/* support nonblocking write if requested */
	if ((filep->f_flags & O_NONBLOCK) &&
		(!pcan_fifo_not_full(&dev->writeFifo)) &&
				(!atomic_read(&dev->DataSendReady)))
		return -EAGAIN;

	/* sleep until space is available */
	err = wait_event_interruptible(dev->write_queue,
					!dev->ucPhysicallyInstalled ||
					pcan_fifo_not_full(&dev->writeFifo) ||
					atomic_read(&dev->DataSendReady));
	if (err)
		goto fail;

	/* not need to wait for anything if device not plugged! */
	if (!dev->ucPhysicallyInstalled)
		return -ENODEV;

	/* get from user space */
	if (copy_from_user(&msg, usr, sizeof(msg))) {
		err = -EFAULT;
		goto fail;
	}

	/* filter extended data if initialized to standard only */
	if (!(dev->bExtended) && ((msg.MSGTYPE & MSGTYPE_EXTENDED) ||
							(msg.ID > 2047))) {
		err = -EINVAL;
		goto fail;
	}

	/* put data into fifo */
	err = pcan_fifo_put(&dev->writeFifo, &msg);
	if (!err) {
		/*
		 * push a new transmission trough ioctl() only if interrupt
		 * triggered push was stalled
		 */
		mb();
		if (atomic_read(&dev->DataSendReady)) {
			atomic_set(&dev->DataSendReady, 0);
			mb();
			err = dev->device_write(dev);
			if (err) {
				atomic_set(&dev->DataSendReady, 1);

				/* ignore only if the fifo is already empty */
				if (err == -ENODATA)
					err = 0;
			}
		} else {
			// DPRINTK(KERN_DEBUG "%s: pushed %d items into Fifo\n", DEVICE_NAME, dev->writeFifo.nStored);
		}
	}

fail:
	return err;
}

/*
 * is called at user ioctl() with cmd = PCAN_GET_EXT_STATUS
 */
int pcan_ioctl_extended_status(struct pcandev *dev, TPEXTENDEDSTATUS *status)
{
	int err = 0;
	TPEXTENDEDSTATUS local;

	DPRINTK(KERN_DEBUG "%s: pcan_ioctl(PCAN_GET_EXT_STATUS)\n", DEVICE_NAME);
	pcan_ioctl_extended_status_common(dev, &local);

	if (copy_to_user(status, &local, sizeof(local))) {
		err = -EFAULT;
		goto fail;
	}

	dev->wCANStatus = 0;
	dev->nLastError = 0;

fail:
	return err;
}

/*
 * is called at user ioctl() with cmd = PCAN_GET_STATUS
 */
static int pcan_ioctl_status(struct pcandev *dev, TPSTATUS *status)
{
	int err = 0;
	TPSTATUS local;

	//DPRINTK(KERN_DEBUG "%s: pcan_ioctl(PCAN_GET_STATUS)\n", DEVICE_NAME);

	pcan_ioctl_status_common(dev, &local);

	if (copy_to_user(status, &local, sizeof(local))) {
		err = -EFAULT;
		goto fail;
	}

	dev->wCANStatus = 0;
	dev->nLastError = 0;

fail:
	return err;
}

/*
 * is called at user ioctl() with cmd = PCAN_DIAG
 */
static int pcan_ioctl_diag(struct pcandev *dev, TPDIAG *diag)
{
	int err = 0;
	TPDIAG local;

	DPRINTK(KERN_DEBUG "%s: pcan_ioctl(PCAN_DIAG)\n", DEVICE_NAME);

	pcan_ioctl_diag_common(dev, &local);

	if (copy_to_user(diag, &local, sizeof(local)))
		err = -EFAULT;

	return err;
}

/*
 * is called at user ioctl() with cmd = PCAN_INIT
 */
static int pcan_ioctl_init(struct pcandev *dev, TPCANInit *Init)
{
	int err = 0;
	TPCANInit local;

	DPRINTK(KERN_DEBUG "%s: pcan_ioctl(PCAN_INIT)\n", DEVICE_NAME);

	if (copy_from_user(&local, Init, sizeof(local))) {
		err = -EFAULT;
		goto fail;
	}

	/* flush fifo contents */
	err = pcan_fifo_reset(&dev->writeFifo);
	if (err)
		goto fail;

	err = pcan_fifo_reset(&dev->readFifo);
	if (err)
		goto fail;

	/* wait until fifo is empty or MAX_WAIT_UNTIL_CLOSE time is elapsed */
	wait_until_fifo_empty(dev, MAX_WAIT_UNTIL_CLOSE);

	/* release the device */
	dev->device_release(dev);

	/* init again */
	err = dev->device_open(dev, local.wBTR0BTR1, local.ucCANMsgType,
							local.ucListenOnly);
	if (!err) {
		dev->wBTR0BTR1 = local.wBTR0BTR1;
		dev->ucCANMsgType = local.ucCANMsgType;
		dev->ucListenOnly = local.ucListenOnly;
	}

fail:
	return err;
}

/*
 * get BTR0BTR1 init values
 */
static int pcan_ioctl_BTR0BTR1(struct pcandev *dev, TPBTR0BTR1 *BTR0BTR1)
{
	int err = 0;
	TPBTR0BTR1 local;

	DPRINTK(KERN_DEBUG "%s: pcan_ioctl(PCAN_BTR0BTR1)\n", DEVICE_NAME);

	if (copy_from_user(&local, BTR0BTR1, sizeof(local))) {
		err = -EFAULT;
		goto fail;
	}

	/*
	 * this does not influence hardware settings, only BTR0BTR1 values
	 * are calculated
	 */
	local.wBTR0BTR1 = sja1000_bitrate(local.dwBitRate);
	if (!local.wBTR0BTR1) {
		err = -EFAULT;
		goto fail;
	}

	if (copy_to_user(BTR0BTR1, &local, sizeof(*BTR0BTR1)))
		err = -EFAULT;

fail:
	return err;
}

/*
 * add a message filter_element into the filter chain or delete all i
 * filter_elements
 */
static int pcan_ioctl_msg_filter(struct pcandev *dev, TPMSGFILTER *filter)
{
	TPMSGFILTER local_filter;

	DPRINTK(KERN_DEBUG "%s: pcan_ioctl(PCAN_MSG_FILTER)\n", DEVICE_NAME);

	/* filter == NULL -> delete the filter_elements in the chain */
	if (!filter) {
		pcan_delete_filter_all(dev->filter);
		return 0;
	}

	if (copy_from_user(&local_filter, filter, sizeof(local_filter)))
		return -EFAULT;

	return pcan_add_filter(dev->filter, local_filter.FromID,
				local_filter.ToID, local_filter.MSGTYPE);
}

/*
 * set or get extra parameters from the devices
 */
static int pcan_ioctl_extra_parameters(struct pcandev *dev,
						TPEXTRAPARAMS *params)
{
	int err = 0;
	TPEXTRAPARAMS local;

	DPRINTK(KERN_DEBUG "%s: pcan_ioctl_extra_parameters()\n", DEVICE_NAME);

	if (copy_from_user(&local, params, sizeof(local))) {
		err = -EFAULT;
		goto fail;
	}

	if (!dev->device_params) {
		err = -EINVAL;
		goto fail;
	}

	err = dev->device_params(dev, &local);
	if (err)
		goto fail;

	if (copy_to_user(params, &local, sizeof(*params)))
		err = -EFAULT;

fail:
	return err;
}

/*
 * is called at user ioctl() call
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
int pcan_ioctl(struct inode *inode, struct file *filep, unsigned int cmd,
							unsigned long arg)
#else
long pcan_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
#endif
{
	int err;
	struct fileobj *fobj = (struct fileobj *)filep->private_data;
	struct pcandev *dev  = fobj->dev;

	//DPRINTK(KERN_DEBUG "%s: pcan_ioctl(cmd=%u)\n", DEVICE_NAME, cmd);

	/* check whether this device is always linked. */
	if (!pcan_is_device_in_list(dev))
		return -ENODEV;

	/* if the device is plugged out */
	if (!dev->ucPhysicallyInstalled)
		return -ENODEV;

	switch(cmd) {
	case PCAN_READ_MSG:
		/* support blocking and nonblocking IO */
		err = pcan_ioctl_read(filep, dev, (TPCANRdMsg *)arg);
		break;
	case PCAN_WRITE_MSG:
		/* support blocking and nonblocking IO */
		err = pcan_ioctl_write(filep, dev, (TPCANMsg *)arg);
		break;
	case PCAN_GET_EXT_STATUS:
		err = pcan_ioctl_extended_status(dev, (TPEXTENDEDSTATUS *)arg);
		break;
	case PCAN_GET_STATUS:
		err = pcan_ioctl_status(dev, (TPSTATUS *)arg);
		break;
	case PCAN_DIAG:
		err = pcan_ioctl_diag(dev, (TPDIAG *)arg);
		break;
	case PCAN_INIT:
		err = pcan_ioctl_init(dev, (TPCANInit *)arg);
		break;
	case PCAN_BTR0BTR1:
		err = pcan_ioctl_BTR0BTR1(dev, (TPBTR0BTR1 *)arg);
		break;
	case PCAN_MSG_FILTER:
		err = pcan_ioctl_msg_filter(dev, (TPMSGFILTER *)arg);
		break;
	case PCAN_EXTRA_PARAMS:
		err = pcan_ioctl_extra_parameters(dev, (TPEXTRAPARAMS *)arg);
		break;

	default:
		DPRINTK(KERN_DEBUG "%s: pcan_ioctl(%d)\n", DEVICE_NAME, cmd);
		err = -ENOTTY;
		break;
	}

	// DPRINTK(KERN_DEBUG "%s: pcan_ioctl() = %d\n", DEVICE_NAME, err);
	return err;
}

/*
 * is called when read from the path
 */
static ssize_t pcan_read(struct file *filep, char *buf, size_t count,
								loff_t *f_pos)
{
	int err;
	int len = 0;
	TPCANRdMsg msg;
	struct fileobj *fobj = (struct fileobj *)filep->private_data;
	struct pcandev *dev = fobj->dev;

	// DPRINTK(KERN_DEBUG "%s: pcan_read().\n", DEVICE_NAME);

	/* check whether this device is always linked. */
	if (!pcan_is_device_in_list(dev))
		return -ENODEV;

	/* if the device is plugged out */
	if (!dev->ucPhysicallyInstalled)
		return -ENODEV;

	if (fobj->nReadRest <= 0) {

		/* support nonblocking read if requested */
		if ((filep->f_flags & O_NONBLOCK) &&
					(pcan_fifo_empty(&dev->readFifo)))
			return -EAGAIN;

		/* sleep until data are available */
		err = wait_event_interruptible(dev->read_queue,
					!dev->ucPhysicallyInstalled ||
					!pcan_fifo_empty(&dev->readFifo));
		if (err)
			return err;

		/* if the device is plugged out */
		if (!dev->ucPhysicallyInstalled)
			return -ENODEV;

		/* get read data out of FIFO */
		err = pcan_fifo_get(&dev->readFifo, &msg);
		if (err)
			return err;

		fobj->nReadRest = pcan_make_output(fobj->pcReadBuffer, &msg);
		fobj->pcReadPointer = fobj->pcReadBuffer;
	}

	/* give the data to the user */
	if (count > fobj->nReadRest) {
		/* put all data to user */
		len = fobj->nReadRest;
		fobj->nReadRest = 0;
		if (copy_to_user(buf, fobj->pcReadPointer, len))
			return -EFAULT;
		fobj->pcReadPointer = fobj->pcReadBuffer;
	} else {
		/* put only partial data to user */
		len = count;
		fobj->nReadRest -= count;
		if (copy_to_user(buf, fobj->pcReadPointer, len))
			return -EFAULT;
		fobj->pcReadPointer = (u8 *)((u8*)fobj->pcReadPointer + len);
	}

	*f_pos += len;
	fobj->nTotalReadCount += len;

	// DPRINTK(KERN_DEBUG "%s: pcan_read() is OK\n", DEVICE_NAME);

	return len;
}

static int pcan_write_line(struct file *filep, u8 *ptr, size_t count)
{
	struct fileobj *fobj = (struct fileobj *)filep->private_data;
	struct pcandev *dev = fobj->dev;
	u32 amount = (u32)(fobj->pcWritePointer - ptr - 1);
	u32 offset = (u32)(ptr - fobj->pcWriteBuffer + 1);
	int err;

	if ((amount > WRITEBUFFER_SIZE) || (offset > WRITEBUFFER_SIZE)) {
#ifdef __LP64__
#warning "Compiling for __LP64__"
#endif
		printk(KERN_ERR "%s: fault in pcan_write() %zu %u, %u: \n",
					DEVICE_NAME, count, amount, offset);
		return -EFAULT;
	}

	if (pcan_parse_input_idle(fobj->pcWriteBuffer)) {
		TPCANMsg msg;

		if (pcan_parse_input_message(fobj->pcWriteBuffer, &msg)) {
			TPCANInit Init;

			err = pcan_parse_input_init(fobj->pcWriteBuffer, &Init);
			if (err)
				return err;
#if 0
			DPRINTK(KERN_DEBUG
				"%s: ***** Init 0x%04x 0x%02x 0x%02x\n",
				DEVICE_NAME, Init.wBTR0BTR1, Init.ucCANMsgType,
				Init.ucListenOnly);
#endif
			/*
			 * init the associated chip and the fifos again
			 * with new parameters
			 */
			err = dev->device_open(dev, Init.wBTR0BTR1,
							Init.ucCANMsgType,
							Init.ucListenOnly);
			if (err)
				return err;

			dev->wBTR0BTR1 = Init.wBTR0BTR1;
			dev->ucCANMsgType = Init.ucCANMsgType;
			dev->ucListenOnly = Init.ucListenOnly;

			err = pcan_fifo_reset(&dev->writeFifo);
			if (err)
				return err;

			err = pcan_fifo_reset(&dev->readFifo);
			if (err)
				return err;
		} else {
#if 0 // ------- print out message, begin -----------
			int i = 0;

			DPRINTK(KERN_DEBUG "%s: *** 0x%08x 0x%02x %d . ",
				DEVICE_NAME, msg.ID, Message.MSGTYPE, msg.LEN);

			while (i++ < Message.LEN)
				DPRINTK(KERN_DEBUG "0x%02x ", msg.DATA[i]);

			DPRINTK(KERN_DEBUG " ***\n");
#endif // ------- print out message, end ------------

			/*
			 * support nonblocking write if requested
			 */
			if ((filep->f_flags & O_NONBLOCK) &&
				(!pcan_fifo_not_full(&dev->writeFifo)) &&
				(!atomic_read(&dev->DataSendReady)))
				return -EAGAIN;

			/* if the device is plugged out */
			if (!dev->ucPhysicallyInstalled)
				return -ENODEV;

			/* sleep until space is available */
			err = wait_event_interruptible(dev->write_queue,
					!dev->ucPhysicallyInstalled ||
					pcan_fifo_not_full(&dev->writeFifo) ||
					atomic_read(&dev->DataSendReady));
			if (err)
				return err;

			/* if the device is plugged out */
			if (!dev->ucPhysicallyInstalled)
				return -ENODEV;

			/* filter extended data if initialized to std only */
			if (!(dev->bExtended) &&
				((msg.MSGTYPE & MSGTYPE_EXTENDED) ||
					(msg.ID > 2047)))
				return -EINVAL;

			err = pcan_fifo_put(&dev->writeFifo, &msg);
			if (err)
				return err;

			/*
			 * push a new transmission trough ioctl() only if
			 * interrupt triggered push was stalled
			 */
			mb();
			if (atomic_read(&dev->DataSendReady)) {
				atomic_set(&dev->DataSendReady, 0);
				mb();
				err = dev->device_write(dev);
				if (err) {
					atomic_set(&dev->DataSendReady, 1);

					/*
					 * ignore only if the fifo is already
					 * empty
					 */
					if (err != -ENODATA)
						return err;
				}
			} else {
				// DPRINTK(KERN_DEBUG "%s: pushed %d items into Fifo\n", DEVICE_NAME, dev->writeFifo.nStored);
			}
		}
	}

	/* move rest of amount data in buffer offset steps to left */
	memmove(fobj->pcWriteBuffer, ptr + 1, amount);
	fobj->pcWritePointer -= offset;

	return 0;
}

static ssize_t pcan_write(struct file *filep, const char *buf, size_t count,
								loff_t *f_pos)
{
	struct fileobj *fobj = (struct fileobj *)filep->private_data;
	struct pcandev *dev = fobj->dev;
	int err = 0;
	u32 dwRest;
	u8 *ptr;

	// DPRINTK(KERN_DEBUG "%s: pcan_write().\n", DEVICE_NAME);

	/* check whether this device is always linked. */
	if (!pcan_is_device_in_list(dev))
		return -ENODEV;

	/* if the device is plugged out	*/
	if (!dev->ucPhysicallyInstalled)
		return -ENODEV;

	/* calculate remaining buffer space */
	dwRest = WRITEBUFFER_SIZE -
		(fobj->pcWritePointer - fobj->pcWriteBuffer); /* nRest > 0! */
	count  = (count > dwRest) ? dwRest : count;

	if (copy_from_user(fobj->pcWritePointer, buf, count))
		return -EFAULT;

	/* adjust working pointer to end */
	fobj->pcWritePointer += count;

	/* iterate search blocks ending with '\n' */
	while (1) {

		/* search first '\n' from begin of buffer */
		ptr = fobj->pcWriteBuffer;
		while ((*ptr != '\n') && (ptr < fobj->pcWritePointer))
			ptr++;

		/* parse input when a CR was found */
		if ((*ptr == '\n') && (ptr < fobj->pcWritePointer)) {

			err = pcan_write_line(filep, ptr, count);
			if (err)
				return err;
		}
		else
			break; /* no CR found */
	}

	if (fobj->pcWritePointer >= (fobj->pcWriteBuffer + WRITEBUFFER_SIZE)) {
		fobj->pcWritePointer = fobj->pcWriteBuffer; /* reject all */
		return -EFAULT;
	}

	// DPRINTK(KERN_DEBUG "%s: pcan_write() is OK\n", DEVICE_NAME);

	return count;
}

/*
 * is called at poll or select
 */
static unsigned int pcan_poll(struct file *filep, poll_table *wait)
{
	struct fileobj *fobj = (struct fileobj *)filep->private_data;
	struct pcandev *dev = fobj->dev;
	unsigned int mask = 0;

	/* if the device is plugged out	*/
	if (!dev->ucPhysicallyInstalled)
		return 0;

	poll_wait(filep, &dev->read_queue, wait);
	poll_wait(filep, &dev->write_queue, wait);

	/* return on ops that could be performed without blocking */
	if (!pcan_fifo_empty(&dev->readFifo))
		mask |= (POLLIN  | POLLRDNORM);

	if (pcan_fifo_not_full(&dev->writeFifo))
		mask |= (POLLOUT | POLLWRNORM);

	return mask;
}

/*
 * this structure is used in init_module(void)
 */
struct file_operations pcan_fops =
{
	/*
	 * marrs:  added owner, which is used to implement a use count that
	 *         disallows rmmod calls when the driver is still in use (as
	 *         suggested by Duncan Sands on the linux-kernel mailinglist)
	 */
	owner:      THIS_MODULE,
	open:       pcan_open,
	release:    pcan_release,
	read:       pcan_read,
	write:      pcan_write,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	ioctl:      pcan_ioctl,
#else
	unlocked_ioctl: pcan_ioctl,
#endif
	poll:       pcan_poll,
};
