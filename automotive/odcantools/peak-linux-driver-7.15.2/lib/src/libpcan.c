//****************************************************************************
// Copyright (C) 2001-2007 PEAK System-Technik GmbH
//
// linux@peak-system.com
// www.peak-system.com
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// Maintainer(s): Klaus Hitschler (klaus.hitschler@gmx.de)
// Contributions: Mudiaga Obada   (obada@vsi.cs.uni-frankfurt.de)
//                Jörg Diederich  (joerg.diederich@graffiti.net)
//****************************************************************************

//****************************************************************************
//
// libpcan.c
// the shared library to unify the interface to the devices
// PCAN-ISA, PCAN-Dongle, PCAN-PCI, PCAN-PC104, PCAN-USB via their drivers
//
// $Id: libpcan.c 809 2014-12-09 15:36:04Z stephane $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <libpcan.h>      // the interface to the application

#ifndef NO_RT
#include <rtdm/rtdm.h>
#endif

//****************************************************************************
// DEFINES
#define PROCFILE "/proc/pcan"     // where to get information
#define MAX_LINE_LEN 255          // to store a line of text
#define DEVICE_PATH "/dev/pcan"   // + Minor = real device path
#define LOCAL_STRING_LEN 64       // length of internal used strings

#ifndef NO_RT
#define __ioctl(x, y, z)	rt_dev_ioctl(x, y, z)
#define __close(fp)		rt_dev_close(fp)
#else
#define __ioctl(x, y, z)	ioctl(x, y, z)
#define __close(fp)		close(fp)
#endif

//****************************************************************************
// GLOBALS
typedef struct {
	char szVersionString[LOCAL_STRING_LEN];
	char szDevicePath[LOCAL_STRING_LEN];
	int  nFileNo;
} PCAN_DESCRIPTOR;

//****************************************************************************
// LOCALS

//****************************************************************************
// CODE

//----------------------------------------------------------------------------
// merge a device file path
static char *szDeviceName(int nMinor)
{
	static char path[LOCAL_STRING_LEN];

	path[0] = 0;

	if (nMinor <= 64)
		sprintf(path, "%s%d", DEVICE_PATH, nMinor);

	return path;
}

static int resolve(char *buffer, int *nType, unsigned long *dwPort,
			 unsigned short *wIrq, int *nMajor, int *nMinor)
{
	static int m_nMajor = 0;
	char *ptr = buffer;
	char *t;

	if (*ptr == '\n')
		return -1;

	if (*ptr == '*') {
		// search for nMajor
		if ((ptr = strstr(ptr, "major"))) {
			t = strtok(ptr, " ");
			t = strtok(NULL, " ");
			m_nMajor = strtoul(t, NULL, 10);
		}
	} else {
		// skip leading blank
		if (*ptr == ' ')
			ptr++;

		// get minor
		t = strtok(ptr, " ");
		*nMinor = strtoul(ptr, NULL, 10);

		// get type string
		t = strtok(NULL, " ");
		if (!strcmp(t, "pci"))
			*nType = HW_PCI;
		else if (!strcmp(t, "epp"))
			*nType = HW_DONGLE_SJA_EPP;
		else if (!strcmp(t, "isa"))
			*nType = HW_ISA_SJA;
		else if (!strcmp(t, "sp"))
			*nType = HW_DONGLE_SJA;
		else if (!strcmp(t, "usb"))
			*nType = HW_USB;
		else if (!strcmp(t, "usbpro"))
			*nType = HW_USB_PRO;
		else if (!strcmp(t, "usbfd"))
			*nType = HW_USB_FD;
		else if (!strcmp(t, "usbpfd"))
			*nType = HW_USB_PRO_FD;
		else
			*nType = -1;

		// jump over ndev
		while (*t++ == ' ');
		t = strtok(NULL, " ");

		// get port
		t = strtok(NULL, " ");
		*dwPort = strtoul(t, NULL, 16);

		// get irq
		t = strtok(NULL, " ");
		*wIrq = (unsigned short)strtoul(t, NULL, 10);

		// set major
		*nMajor = m_nMajor;

		return 0;
	}

	return -1;
}

//----------------------------------------------------------------------------
// do a unix like open of the device
HANDLE LINUX_CAN_Open(const char *szDeviceName, int nFlag)
{
	PCAN_DESCRIPTOR *desc = NULL;

	errno = 0;

	if ((desc = (PCAN_DESCRIPTOR *)malloc(sizeof(*desc))) == NULL)
		goto fail;

	desc->szVersionString[0] = 0;
	desc->szDevicePath[0] = 0;

#ifndef NO_RT
	char DeviceName[15];
	sscanf(szDeviceName, "/dev/%s", DeviceName);
	if ((desc->nFileNo = rt_dev_open(DeviceName, nFlag)) == -1)
#else
	if ((desc->nFileNo = open(szDeviceName, nFlag)) == -1)
#endif
		goto fail;

	strncpy(desc->szDevicePath, szDeviceName, LOCAL_STRING_LEN);

	return (HANDLE)desc;

fail:
	if (desc) {
		if (desc->nFileNo > -1)
			__close(desc->nFileNo);
		free(desc);
	}

	return NULL;
}

//----------------------------------------------------------------------------
// do a peak like open of the device
HANDLE CAN_Open(WORD wHardwareType, ...)
{
	HANDLE handle = NULL;
	FILE *f = NULL;
	char *m = NULL;
	char *p = NULL;
	char *ptr;
	int found = 0;

	va_list args;
	unsigned long m_dwPort = 0;
	unsigned short m_wIrq = 0;

	int nMinor = 0;
	int nMajor = 0;
	unsigned long dwPort;
	unsigned short wIrq;
	int nType;

	errno = ENODEV;

	// read variable length and type argument list
	va_start(args, wHardwareType);
	switch(wHardwareType) {
	case HW_DONGLE_SJA:
	case HW_DONGLE_SJA_EPP:
	case HW_ISA_SJA:
		m_dwPort = va_arg(args, unsigned long);
		m_wIrq = (unsigned short)va_arg(args, unsigned long);
		va_end(args);
		break;

	case HW_PCI:
		m_dwPort = va_arg(args, int);
		va_end(args);
		break;

	case HW_USB:
	case HW_USB_FD:
	case HW_USB_PRO:
	case HW_USB_PRO_FD:
		m_dwPort = va_arg(args, unsigned long);
		m_wIrq = (unsigned short)va_arg(args, unsigned long);
		va_end(args);
		break;

	default:
		va_end(args);
		goto fail;
	}

	if ((f = fopen(PROCFILE, "r")) == NULL)
		goto fail;

	if ((m = malloc(MAX_LINE_LEN)) == NULL)
		goto fail;

	// read an interpret proc entry contents
	do {
		ptr = m;
		p = fgets(ptr, MAX_LINE_LEN, f);
		if (!p)
			break;

		if (resolve(p, &nType, &dwPort, &wIrq, &nMajor, &nMinor))
			continue;

		if (wHardwareType != nType)
			continue;

		switch (wHardwareType) {
		case HW_DONGLE_SJA:
		case HW_DONGLE_SJA_EPP:
		case HW_ISA_SJA:
			found = (((m_dwPort == dwPort) && (m_wIrq == wIrq)) ||
				((!m_dwPort) && (!m_wIrq)));
			break;

		case HW_PCI:
			/* enumerate 1..8 (not 0 .. 7) */
			found = (((m_dwPort - 1) == nMinor) || (!m_dwPort));
			break;
		case HW_USB:
		case HW_USB_FD:
		case HW_USB_PRO:
		case HW_USB_PRO_FD:
			/* enumerate 1..8 (not 32 .. 39) */
			found = (((m_dwPort + 31) == nMinor) || (!m_dwPort));
			break;
		}
	} while ((p) && (!found));

	if (found)
		handle = LINUX_CAN_Open(szDeviceName(nMinor), O_RDWR);

fail:
	if (m)
		free(m);
	if (f)
		fclose(f);

	return handle;
}

//----------------------------------------------------------------------------
// init the CAN chip of this device
DWORD CAN_Init(HANDLE hHandle, WORD wBTR0BTR1, int nCANMsgType)
{
	PCAN_DESCRIPTOR *desc = (PCAN_DESCRIPTOR *)hHandle;
	int err = EBADF;

	errno = err;
	if (desc) {
		TPCANInit init;

		init.wBTR0BTR1 = wBTR0BTR1;    // combined BTR0 and BTR1 register of the SJA100
		init.ucCANMsgType = (nCANMsgType) ? 
			MSGTYPE_EXTENDED : MSGTYPE_STANDARD;  // 11 or 29 bits
		init.ucListenOnly = 0;            // listen only mode when != 0

		err = __ioctl(desc->nFileNo, PCAN_INIT, &init);
	}

	return err;
}

DWORD CAN_Close(HANDLE hHandle)
{
	PCAN_DESCRIPTOR *desc = (PCAN_DESCRIPTOR *)hHandle;

	if (desc) {
		if (desc->nFileNo > -1) {
			__close(desc->nFileNo);
			desc->nFileNo = -1;
		}
		free(desc);
	}
	return 0;
}

DWORD CAN_Status(HANDLE hHandle)
{
	PCAN_DESCRIPTOR *desc = (PCAN_DESCRIPTOR *)hHandle;
	int err = EBADF;

	errno = err;
	if (desc) {
		TPSTATUS status;

		err = __ioctl(desc->nFileNo, PCAN_GET_STATUS, &status);
		if (err >= 0)
			return status.wErrorFlag;
	}

	return err;
}

DWORD CAN_Write(HANDLE hHandle, TPCANMsg* pMsgBuff)
{
	PCAN_DESCRIPTOR *desc = (PCAN_DESCRIPTOR *)hHandle;
	int err = EBADF;

	errno = err;
	if (desc)
		err = __ioctl(desc->nFileNo, PCAN_WRITE_MSG, pMsgBuff);

	return err;
}

DWORD CAN_Read(HANDLE hHandle, TPCANMsg* pMsgBuff)
{
	PCAN_DESCRIPTOR *desc = (PCAN_DESCRIPTOR *)hHandle;
	int err = EBADF;

	errno = err;
	if (desc) {
		TPCANRdMsg m;

		err = __ioctl(desc->nFileNo, PCAN_READ_MSG, &m);
		if (err >= 0)
			memcpy(pMsgBuff, &m.Msg, sizeof(* pMsgBuff));
	}

	return err;
}

DWORD LINUX_CAN_Read(HANDLE hHandle, TPCANRdMsg* pMsgBuff)
{
	PCAN_DESCRIPTOR *desc = (PCAN_DESCRIPTOR *)hHandle;
	int err = EBADF;

	errno = err;
	if (desc)
		err = __ioctl(desc->nFileNo, PCAN_READ_MSG, pMsgBuff);

	return err;
}

int LINUX_CAN_FileHandle(HANDLE hHandle)
{
	PCAN_DESCRIPTOR *desc = (PCAN_DESCRIPTOR *)hHandle;

	if (!desc)
		return -EBADF;

	return desc->nFileNo;
}

DWORD LINUX_CAN_Statistics(HANDLE hHandle, TPDIAG *diag)
{
	PCAN_DESCRIPTOR *desc = (PCAN_DESCRIPTOR *)hHandle;
	int err = EBADF;

	errno = err;
	if (desc)
		err = __ioctl(desc->nFileNo, PCAN_DIAG, diag);

	return err;
}

WORD LINUX_CAN_BTR0BTR1(HANDLE hHandle, DWORD dwBitRate)
{
	PCAN_DESCRIPTOR *desc = (PCAN_DESCRIPTOR *)hHandle;
	int err = EBADF;
	TPBTR0BTR1 ratix;

	ratix.dwBitRate = dwBitRate;
	ratix.wBTR0BTR1 = 0;

	errno = err;
	if (desc) {
		err = __ioctl(desc->nFileNo, PCAN_BTR0BTR1, &ratix);
		if (!err)
			return ratix.wBTR0BTR1;
	}

	return 0;
}

DWORD CAN_VersionInfo(HANDLE hHandle, LPSTR szTextBuff)
{
	int err;
	TPDIAG diag;

	*szTextBuff = 0;

	err = (int)LINUX_CAN_Statistics(hHandle, &diag);
	if (err)
		return err;

	strncpy(szTextBuff, diag.szVersionString, VERSIONSTRING_LEN);

	return err;
}

DWORD LINUX_CAN_Read_Timeout(HANDLE hHandle, TPCANRdMsg* pMsgBuff,
				   int nMicroSeconds)
{
	int err = EBADF;
	PCAN_DESCRIPTOR *desc;

	if (nMicroSeconds < 0)
		return LINUX_CAN_Read(hHandle, pMsgBuff);

	desc = (PCAN_DESCRIPTOR *)hHandle;
	if (desc) {
		fd_set fdRead;
		struct timeval t;

		// calculate timeout values
		t.tv_sec  = nMicroSeconds / 1000000L;
		t.tv_usec = nMicroSeconds % 1000000L;

		FD_ZERO(&fdRead);
		FD_SET(desc->nFileNo, &fdRead);

		// wait until timeout or a message is ready to read
		err = select(desc->nFileNo + 1, &fdRead, NULL, NULL, &t);

		// the only one file descriptor is ready for read
		if (err  > 0)
			return LINUX_CAN_Read(hHandle, pMsgBuff);

		// nothing is ready, timeout occured
		if (err == 0)
			return CAN_ERR_QRCVEMPTY;
	}

	// any else error
	return err;
}

DWORD LINUX_CAN_Write_Timeout(HANDLE hHandle, TPCANMsg* pMsgBuff,
			      int nMicroSeconds)
{
	int err = EBADF;
	PCAN_DESCRIPTOR *desc;

	if (nMicroSeconds < 0)
		return CAN_Write(hHandle, pMsgBuff);

	desc = (PCAN_DESCRIPTOR *)hHandle;
	if (desc) {
		fd_set fdWrite;
		struct timeval t;

		// calculate timeout values
		t.tv_sec  = nMicroSeconds / 1000000L;
		t.tv_usec = nMicroSeconds % 1000000L;

		FD_ZERO(&fdWrite);
		FD_SET(desc->nFileNo, &fdWrite);

		// wait until timeout or a message is ready to get written
		err = select(desc->nFileNo + 1,  NULL, &fdWrite,NULL, &t);

		// the only one file descriptor is ready for write
		if (err > 0)
			return CAN_Write(hHandle, pMsgBuff);

		// nothing is ready, timeout occured
		if (err == 0)
			return CAN_ERR_QXMTFULL;
	}

	// any else error
	return err;
}

DWORD LINUX_CAN_Extended_Status(HANDLE hHandle, int *nPendingReads,
				int *nPendingWrites)
{
	PCAN_DESCRIPTOR *desc = (PCAN_DESCRIPTOR *)hHandle;
	int err = EBADF;

	errno = err;
	if (desc) {
		TPEXTENDEDSTATUS status;

		err = __ioctl(desc->nFileNo, PCAN_GET_EXT_STATUS, &status);
		if (err >= 0) {
			*nPendingReads  = status.nPendingReads;
			*nPendingWrites = status.nPendingWrites;

			return status.wErrorFlag;
		}
	}

	return err;
}

int nGetLastError(void)
{
	return errno;
}

DWORD CAN_MsgFilter(HANDLE hHandle, DWORD FromID, DWORD ToID, int nCANMsgType)
{
	PCAN_DESCRIPTOR *desc = (PCAN_DESCRIPTOR *)hHandle;
	TPMSGFILTER filter;

	filter.FromID  = FromID;
	filter.ToID = ToID;
	filter.MSGTYPE = (BYTE )nCANMsgType;

	if (desc)
		return __ioctl(desc->nFileNo, PCAN_MSG_FILTER, &filter);

	return EBADF;
}

// for compatibility to MS-Windows only
DWORD CAN_ResetFilter(HANDLE hHandle)
{
	PCAN_DESCRIPTOR *desc = (PCAN_DESCRIPTOR *)hHandle;

	if (desc)
		return __ioctl(desc->nFileNo, PCAN_MSG_FILTER, NULL);

	return EBADF;
}

// end
